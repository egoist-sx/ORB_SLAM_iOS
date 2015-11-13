//
//  OBJModel.h
//  UpAndRunning3D
//
//  Created by Warren Moore on 9/11/14.
//  Copyright (c) 2014 Metal By Example. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <simd/simd.h>

struct Vertex
{
    simd::float4 position;
    simd::float4 normal;
};

typedef uint16_t IndexType;

struct OBJGroup
{
    OBJGroup() :
        name(nullptr),
        vertices(nullptr),
        indices(nullptr),
        vertexCount(0),
        indexCount(0)
    {
    }
    
    ~OBJGroup()
    {
        free(name);
        free(vertices);
        free(indices);
    }

    char *name;
    Vertex *vertices;
    IndexType *indices;
    size_t vertexCount;
    size_t indexCount;
};

@interface OBJModel : NSObject

- (instancetype)initWithContentsOfURL:(NSURL *)url;

// The count of groups in this OBJ file. For valid files, this will always be at least 1.
- (size_t)groupCount;

// Index 0 corresponds to an unnamed group that collects all the geometry
// declared outside of explicit "g" statements. Therefore, if your file
// contains explicit groups, you'll probably want to start from index 1,
// which will be the group defined starting at the first group statement.
- (OBJGroup *)groupAtIndex:(size_t)index;

@end
