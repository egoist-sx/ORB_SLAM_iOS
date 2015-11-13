//
//  OBJModel.mm
//  UpAndRunning3D
//
//  Created by Warren Moore on 9/11/14.
//  Copyright (c) 2014 Metal By Example. All rights reserved.
//

#import "OBJModel.h"
#include <map>
#include <vector>

// "Face vertices" are tuples of indices into file-wide lists of positions, normals, and texture coordinates.
// We maintain a mapping from these triples to the indices they will eventually occupy in the group that
// is currently being constructed.
struct FaceVertex
{
    FaceVertex() :
        vi(0), ti(0), ni(0)
    {
    }
    
    uint16_t vi, ti, ni;
};

static bool operator <(const FaceVertex &v0, const FaceVertex &v1)
{
    if (v0.vi < v1.vi)
        return true;
    else if (v0.vi > v1.vi)
        return false;
    else if (v0.ti < v1.ti)
        return true;
    else if (v0.ti > v1.ti)
        return false;
    else if (v0.ni < v1.ni)
        return true;
    else if (v0.ni > v1.ni)
        return false;
    else
        return false;
}

@interface OBJModel ()
{
    std::vector<simd::float4> vertices;
    std::vector<simd::float4> normals;
    std::vector<simd::float2> texCoords;
    std::vector<OBJGroup *> groups;
    std::vector<Vertex> groupVertices;
    std::vector<IndexType> groupIndices;
    std::map<FaceVertex, IndexType> vertexToGroupIndexMap;
    OBJGroup *currentGroup;
}
@end

@implementation OBJModel

- (instancetype)initWithContentsOfURL:(NSURL *)fileURL
{
    if ((self = [super init]))
    {
        [self parseModelAtURL:fileURL];
    }
    return self;
}

- (void)dealloc
{
    for (auto g : groups)
    {
        delete g;
    }
}

- (size_t)groupCount
{
    return groups.size();
}

- (OBJGroup *)groupAtIndex:(size_t)index
{
    if (index < groups.size())
    {
        return groups[index];
    }

    return nullptr;
}

- (void)parseModelAtURL:(NSURL *)url
{
    NSError *error = nil;
    NSString *contents = [NSString stringWithContentsOfURL:url
                                                  encoding:NSASCIIStringEncoding
                                                     error:&error];
    if (!contents)
    {
        return;
    }
    
    NSScanner *scanner = [NSScanner scannerWithString:contents];
    
    NSCharacterSet *skipSet = [NSCharacterSet whitespaceAndNewlineCharacterSet];
    NSCharacterSet *consumeSet = [skipSet invertedSet];
    
    scanner.charactersToBeSkipped = skipSet;
    
    NSCharacterSet *endlineCharacters = [NSCharacterSet newlineCharacterSet];
    
    [self beginGroupWithName:@"(unnamed)"];
    
    while (![scanner isAtEnd])
    {
        NSString *token = nil;
        if (![scanner scanCharactersFromSet:consumeSet intoString:&token])
        {
            break;
        }
        
        if ([token isEqualToString:@"v"])
        {
            float x, y, z;
            [scanner scanFloat:&x];
            [scanner scanFloat:&y];
            [scanner scanFloat:&z];
            
            simd::float4 v = { x, y, z, 1 };
            vertices.push_back(v);
        }
        else if ([token isEqualToString:@"vt"])
        {
            float u = 0, v = 0;
            [scanner scanFloat:&u];
            [scanner scanFloat:&v];
            
            simd::float2 vt = { u, v };
            texCoords.push_back(vt);
        }
        else if ([token isEqualToString:@"vn"])
        {
            float nx = 0, ny = 0, nz = 0;
            [scanner scanFloat:&nx];
            [scanner scanFloat:&ny];
            [scanner scanFloat:&nz];
            
            simd::float4 vn = { nx, ny, nz, 0 };
            normals.push_back(vn);
        }
        else if ([token isEqualToString:@"f"])
        {
            std::vector<FaceVertex> faceVertices;
            faceVertices.reserve(4);
            
            while (1)
            {
                int32_t vi, ti, ni;
                if(![scanner scanInt:&vi])
                {
                    break;
                }

                if ([scanner scanString:@"/" intoString:NULL])
                {
                    [scanner scanInt:&ti];
                    
                    if ([scanner scanString:@"/" intoString:NULL])
                    {
                        [scanner scanInt:&ni];
                    }
                }
                
                FaceVertex faceVertex;
                
                // OBJ format allows relative vertex references in the form of negative indices, and
                // dictates that indices are 1-based. Below, we simultaneously fix up negative indices
                // and offset everything by -1 to allow 0-based indexing later on.
                
                faceVertex.vi = (vi < 0) ? (vertices.size() + vi - 1) : (vi - 1);
                faceVertex.ti = (ti < 0) ? (texCoords.size() + ti - 1) : (ti - 1);
                faceVertex.ni = (ni < 0) ? (vertices.size() + ni - 1) : (ni - 1);

                faceVertices.push_back(faceVertex);
            }
            
            [self addFaceWithFaceVertices:faceVertices];
        }
        else if ([token isEqualToString:@"g"])
        {
            NSString *groupName = nil;
            if ([scanner scanUpToCharactersFromSet:endlineCharacters intoString:&groupName])
            {
                [self beginGroupWithName:groupName];
            }
        }
    }
    
    [self endCurrentGroup];
}

- (void)beginGroupWithName:(NSString *)name
{
    [self endCurrentGroup];
    
    currentGroup = new OBJGroup;
    currentGroup->name = strdup([name UTF8String]);
    groups.push_back(currentGroup);
}

- (void)endCurrentGroup
{
    if (currentGroup == nullptr)
    {
        return;
    }
    
    // Once we've read a complete group, we copy the packed vertices that have been referenced by the group
    // into the final group struct. Because it's fairly uncommon to have cross-group shared vertices, this
    // essentially divides up the vertices into disjoint sets by group.

    currentGroup->vertexCount = groupVertices.size();
    if (currentGroup->vertexCount > 0)
    {
        currentGroup->vertices = (Vertex *)malloc(sizeof(Vertex) * currentGroup->vertexCount);
        memcpy(currentGroup->vertices, groupVertices.data(), sizeof(Vertex) * currentGroup->vertexCount);
    }

    currentGroup->indexCount = groupIndices.size();
    if (currentGroup->indexCount > 0)
    {
        currentGroup->indices = (IndexType *)malloc(sizeof(IndexType) * currentGroup->indexCount);
        memcpy(currentGroup->indices, groupIndices.data(), sizeof(IndexType) * currentGroup->indexCount);
    }
    
    groupVertices.clear();
    groupIndices.clear();
    vertexToGroupIndexMap.clear();

    currentGroup = nullptr;
}

- (void)addFaceWithFaceVertices:(const std::vector<FaceVertex> &)faceVertices
{
    // Transform polygonal faces into "fans" of triangles, three vertices at a time
    for (size_t i = 0; i < faceVertices.size() - 2; ++i)
    {
        [self addVertexToCurrentGroup:faceVertices[0]];
        [self addVertexToCurrentGroup:faceVertices[i + 1]];
        [self addVertexToCurrentGroup:faceVertices[i + 2]];
    }
}

- (void)addVertexToCurrentGroup:(FaceVertex)fv
{
    static const simd::float4 UP = { 0, 1, 0, 0 };
    
    uint16_t groupIndex;

    auto it = vertexToGroupIndexMap.find(fv);
    if (it != vertexToGroupIndexMap.end())
    {
        groupIndex = (*it).second;
    }
    else
    {
        Vertex vertex;
        vertex.position = vertices[fv.vi];
        vertex.normal = fv.ni > 0 ? normals[fv.ni] : UP;
        // If we were storing texture coordinates, we'd copy them here.

        groupVertices.push_back(vertex);
        groupIndex = groupVertices.size() - 1;
        vertexToGroupIndexMap[fv] = groupIndex;
    }
    
    groupIndices.push_back(groupIndex);
}

@end
