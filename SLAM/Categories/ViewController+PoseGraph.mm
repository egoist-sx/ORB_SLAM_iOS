//
//  ViewController+PoseGraph.m
//  SLAM
//
//  Created by Xin Sun on 21/10/2015.
//  Copyright © 2015 Xin Sun. All rights reserved.
//

#import "ViewController+PoseGraph.h"

@implementation ViewController (PoseGraph)

SCNNode *geometryNode;
SCNVector3 prevPoint;
bool initialPose = true;
int poseCount = 0;

- (void) sceneSetup {
    
    SCNScene *scene = [SCNScene scene];
    
    SCNNode *ambientLightNode = [SCNNode node];
    ambientLightNode.light = [SCNLight light];
    ambientLightNode.light.type = SCNLightTypeAmbient;
    ambientLightNode.light.color = [UIColor colorWithWhite:0.67 alpha:1.0];
    [scene.rootNode addChildNode:ambientLightNode];
    
    SCNNode *omniLightNode = [SCNNode node];
    omniLightNode.light = [SCNLight light];
    omniLightNode.light.type = SCNLightTypeOmni;
    omniLightNode.light.color = [UIColor colorWithWhite:0.75 alpha:1.0];
    omniLightNode.position = SCNVector3Make(0, 10, 10);
    [scene.rootNode addChildNode:omniLightNode];
    
    SCNNode *cameraNode = [SCNNode node];
    cameraNode.camera = [SCNCamera camera];
    cameraNode.position = SCNVector3Make(0, 0, 3);
    [scene.rootNode addChildNode:cameraNode];
    
    self.sceneView.scene = scene;
    self.sceneView.allowsCameraControl = true;
    self.sceneView.backgroundColor = [UIColor blackColor];
    geometryNode = [SCNNode node];
}

- (void) updateGeometry {
    [geometryNode removeFromParentNode];
    [self.sceneView.scene.rootNode addChildNode:geometryNode];
}

- (SCNNode *)lineBetweenX:(SCNVector3)X Y:(SCNVector3)Y {
    // Positions
    SCNVector3 positions[] = {X, Y};
    int indices[] = {0, 1};
    SCNGeometrySource *vertexSource = [SCNGeometrySource geometrySourceWithVertices:positions
                                                                              count:2];
    NSData *indexData = [NSData dataWithBytes:indices
                                       length:sizeof(indices)];
    SCNGeometryElement *element = [SCNGeometryElement geometryElementWithData:indexData
                                                                primitiveType:SCNGeometryPrimitiveTypeLine
                                                               primitiveCount:1
                                                                bytesPerIndex:sizeof(int)];
    SCNGeometry *line = [SCNGeometry geometryWithSources:@[vertexSource]
                                                elements:@[element]];
    SCNNode *lineNode = [SCNNode nodeWithGeometry:line];;
    return lineNode;
}

- (void) addPose:(SCNVector3) point {
    
    if (!initialPose)
        [geometryNode addChildNode:[self lineBetweenX:prevPoint Y:point]];
    else
        initialPose = false;
    prevPoint = point;
    poseCount++;
    if (poseCount%100==0) {
        geometryNode = [geometryNode flattenedClone];
        poseCount = 0;
    }
    [self updateGeometry];
}

- (void) resetSceneView {
    initialPose = true;
    geometryNode = [SCNNode node];
    [self updateGeometry];
}

@end
