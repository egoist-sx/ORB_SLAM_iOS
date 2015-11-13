//
//  Transforms.m
//  UpAndRunning3D
//
//  Created by Warren Moore on 9/12/14.
//  Copyright (c) 2014 Metal By Example. All rights reserved.
//

#include "Transforms.h"

simd::float4x4 Identity()
{
    simd::float4 X = { 1, 0, 0, 0 };
    simd::float4 Y = { 0, 1, 0, 0 };
    simd::float4 Z = { 0, 0, 1, 0 };
    simd::float4 W = { 0, 0, 0, 1 };
    simd::float4x4 mat = { X, Y, Z, W };
    return mat;
}

simd::float4x4 PerspectiveProjection(float aspect, float fovy, float near, float far)
{
    float yScale = 1 / tan(fovy * 0.5);
    float xScale = yScale / aspect;
    float zRange = far - near;
    float zScale = -(far + near) / zRange;
    float wzScale = -2 * far * near / zRange;
    
    simd::float4 P = { xScale, 0, 0, 0 };
    simd::float4 Q = { 0, yScale, 0, 0 };
    simd::float4 R = { 0, 0, zScale, -1 };
    simd::float4 S = { 0, 0, wzScale, 0 };
    
    simd::float4x4 mat = { P, Q, R, S };
    return mat;
}

simd::float4x4 Rotation(simd::float3 axis, float angle)
{
    float c = cos(angle);
    float s = sin(angle);
    
    simd::float4 X;
    X.x = axis.x * axis.x + (1 - axis.x * axis.x) * c;
    X.y = axis.x * axis.y * (1 - c) - axis.z*s;
    X.z = axis.x * axis.z * (1 - c) + axis.y * s;
    X.w = 0.0;
    
    simd::float4 Y;
    Y.x = axis.x * axis.y * (1 - c) + axis.z * s;
    Y.y = axis.y * axis.y + (1 - axis.y * axis.y) * c;
    Y.z = axis.y * axis.z * (1 - c) - axis.x * s;
    Y.w = 0.0;
    
    simd::float4 Z;
    Z.x = axis.x * axis.z * (1 - c) - axis.y * s;
    Z.y = axis.y * axis.z * (1 - c) + axis.x * s;
    Z.z = axis.z * axis.z + (1 - axis.z * axis.z) * c;
    Z.w = 0.0;
    
    simd::float4 W;
    W.x = 0.0;
    W.y = 0.0;
    W.z = 0.0;
    W.w = 1.0;
    
    simd::float4x4 mat = { X, Y, Z, W };
    return mat;
}

simd::float4x4 matrix_uniform_scale(float s) {
    
    simd::float4 X = { s, 0, 0, 0 };
    simd::float4 Y = { 0, s, 0, 0 };
    simd::float4 Z = { 0, 0, s, 0 };
    simd::float4 W = { 0, 0, 0, 1 };
    
    simd::float4x4 mat = { X, Y, Z, W };
    
    return mat;
}
