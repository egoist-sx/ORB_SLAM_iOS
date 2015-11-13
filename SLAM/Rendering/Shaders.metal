//
//  Shaders.metal
//  MetalTriangles
//
//  Created by Warren Moore on 8/26/14.
//  Copyright (c) 2014 Metal By Example. All rights reserved.
//

#include <metal_stdlib>
#include <metal_matrix>
#include "Shared.h"

using namespace metal;

struct Light
{
    float3 direction;
    float3 ambientColor;
    float3 diffuseColor;
    float3 specularColor;
};

constant Light light = {
    .direction = { 0.13, 0.72, 0.68 },
    .ambientColor = { 0.05, 0.05, 0.05 },
    .diffuseColor = { 0.9, 0.9, 0.9 },
    .specularColor = { 1, 1, 1 }
};

struct Material
{
    float3 ambientColor;
    float3 diffuseColor;
    float3 specularColor;
    float specularPower;
};

constant Material material = {
    .ambientColor = { 0.9, 0.1, 0 },
    .diffuseColor = { 0.9, 0.1, 0 },
    .specularColor = { 1, 1, 1 },
    .specularPower = 100
};

struct Vertex
{
    float4 position [[attribute(0)]];
    float3 normal [[attribute(1)]];
};

struct ProjectedVertex
{
    float4 position [[position]];
    float3 eye;
    float3 normal;
};

vertex ProjectedVertex vertex_main(Vertex vert [[stage_in]],
                                   constant Uniforms &uniforms [[buffer(1)]])
{
    ProjectedVertex outVert;
    outVert.position = uniforms.modelViewProjectionMatrix * vert.position;
    outVert.eye =  -(uniforms.modelViewMatrix * vert.position).xyz;
    outVert.normal = uniforms.normalMatrix * vert.normal;

    return outVert;
}

fragment float4 fragment_main(ProjectedVertex vert [[stage_in]],
                              constant Uniforms &uniforms [[buffer(0)]])
{
    float3 ambientTerm = light.ambientColor * material.ambientColor;
    
    float3 normal = normalize(vert.normal);
    float diffuseIntensity = saturate(dot(normal, light.direction));
    float3 diffuseTerm = light.diffuseColor * material.diffuseColor * diffuseIntensity;
    
    float3 specularTerm(0);
    if (diffuseIntensity > 0)
    {
        float3 eyeDirection = normalize(vert.eye);
        float3 halfway = normalize(light.direction + eyeDirection);
        float specularFactor = pow(saturate(dot(normal, halfway)), material.specularPower);
        specularTerm = light.specularColor * material.specularColor * specularFactor;
    }
    
    return float4(ambientTerm + diffuseTerm + specularTerm, 1);
}
