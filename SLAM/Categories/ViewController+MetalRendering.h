//
//  ViewController+MetalRendering.h
//  SLAM
//
//  Created by Xin Sun on 18/10/2015.
//  Copyright © 2015 Xin Sun. All rights reserved.
//

#import "Renderer.h"
#import "ViewController.h"

@interface ViewController (MetalRendering)


- (void) initRendering;
- (void) loadModel;
- (void) drawObjectWith:(const cv::Mat&)R andT:(const cv::Mat&)T;

@end
