//
//  ViewController+MetalRendering.m
//  SLAM
//
//  Created by Xin Sun on 18/10/2015.
//  Copyright © 2015 Xin Sun. All rights reserved.
//

#import "ViewController+MetalRendering.h"
#import "OBJModel.h"
#import "Shared.h"
#import "Transforms.h"

using namespace cv;


@implementation ViewController (MetalRendering)

    Renderer *_renderer;
    id<MTLBuffer> _vertexBuffer;
    id<MTLBuffer> _indexBuffer;
    id<MTLBuffer> _uniformBuffer;
    simd::float4x4 _projectionMatrix;


static float DegToRad(float deg)
{
    return deg * (M_PI / 180);
}

- (void)initRendering {
    _renderer = [[Renderer alloc] initWithLayer:(CAMetalLayer *)self.metalView.layer];
    _renderer.vertexFunctionName = @"vertex_main";
    _renderer.fragmentFunctionName = @"fragment_main";
    [self loadModel];
}

- (void)loadModel {
    NSURL *modelURL = [[NSBundle mainBundle] URLForResource:@"teapot" withExtension:@"obj"];
    OBJModel *teapot = [[OBJModel alloc] initWithContentsOfURL:modelURL];
    
    OBJGroup *baseGroup = [teapot groupAtIndex:1];
    if (baseGroup)
    {
        _vertexBuffer = [_renderer newBufferWithBytes:baseGroup->vertices
                                                       length:sizeof(Vertex) * baseGroup->vertexCount];
        _indexBuffer = [_renderer newBufferWithBytes:baseGroup->indices
                                                      length:sizeof(IndexType) * baseGroup->indexCount];
    }
}

- (void)drawObjectWith:(const Mat&)R andT:(const Mat&)T {
    
    float qx,qy,qz,qw;
    qw = sqrt(1.0 + R.at<float>(0,0) + R.at<float>(1,1) + R.at<float>(2,2)) / 2.0;
    qx = (R.at<float>(2,1) - R.at<float>(1,2)) / (4*qw) ;
    qy = -(R.at<float>(0,2) - R.at<float>(2,0)) / (4*qw) ;
    qz = -(R.at<float>(1,0) - R.at<float>(0,1)) / (4*qw) ;
    
    //Mat T_p = R.t()*T;
    
    //simd::float4 r1 = { 1 - 2*qy*qy - 2*qz*qz, 2*qx*qy - 2*qz*qw, 2*qx*qz + 2*qy*qw, 0 };
    //simd::float4 r2 = { 2*qx*qy + 2*qz*qw, 1 - 2*qx*qx - 2*qz*qz, 2*qy*qz - 2*qx*qw, 0 };
    //simd::float4 r3 = { 2*qx*qz - 2*qy*qw, 2*qy*qz + 2*qx*qw, 1 - 2*qx*qx - 2*qy*qy, 0 };
    simd::float4 r1 = { 1 - 2*qy*qy - 2*qz*qz, 2*qx*qy + 2*qz*qw, 2*qx*qz - 2*qy*qw, 0 };
    simd::float4 r2 = { 2*qx*qy - 2*qz*qw, 1 - 2*qx*qx - 2*qz*qz, 2*qy*qz + 2*qx*qw, 0 };
    simd::float4 r3 = { 2*qx*qz + 2*qy*qw, 2*qy*qz - 2*qx*qw, 1 - 2*qx*qx - 2*qy*qy, 0 };
    simd::float4 r4 = { T.at<float>(0), -T.at<float>(1), -T.at<float>(2), 1 };
    
    //simd::float4 r1 = { R.at<float>(0,0), R.at<float>(0,1), R.at<float>(0,2), 0 };
    //simd::float4 r2 = { R.at<float>(1,0), R.at<float>(1,1), R.at<float>(1,2), 0 };
    //simd::float4 r3 = { R.at<float>(2,0), R.at<float>(2,1), R.at<float>(2,2), 0 };
    //simd::float4 r4 = { -T.at<float>(0), T.at<float>(1), T.at<float>(2), 1 };
    
    simd::float4x4 poseMatrix = {r1, r2, r3, r4};
    simd::float4x4 modelMatrix = poseMatrix*matrix_uniform_scale(0.3);
    
    simd::float4x4 viewMatrix = Identity();
    //viewMatrix.columns[3].z = -0.5; // translate camera back along Z axis
    
    const float near = 0.02;
    const float far = 100;
    const float aspect = self.metalView.bounds.size.width / self.metalView.bounds.size.height;
    simd::float4x4 projectionMatrix = PerspectiveProjection(aspect, DegToRad(75), near, far);
    
    Uniforms uniforms;
    
    simd::float4x4 modelView =  viewMatrix*modelMatrix;
    uniforms.modelViewMatrix = modelView;
    
    simd::float4x4 modelViewProj = projectionMatrix * modelView;
    uniforms.modelViewProjectionMatrix = modelViewProj;
    
    simd::float3x3 normalMatrix = { modelView.columns[0].xyz, modelView.columns[1].xyz, modelView.columns[2].xyz };
    uniforms.normalMatrix = simd::transpose(simd::inverse(normalMatrix));
    
    _uniformBuffer = [_renderer newBufferWithBytes:(void *)&uniforms length:sizeof(Uniforms)];
    
    [self redraw];
}

- (void)redraw
{
    
    [_renderer startFrame];
    
    [_renderer drawTrianglesWithInterleavedBuffer:_vertexBuffer indexBuffer:_indexBuffer uniformBuffer:_uniformBuffer indexCount:[_indexBuffer length]/sizeof(IndexType)];
    
    [_renderer endFrame];
}

@end
