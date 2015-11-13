//
//  ViewController+InfoDisplay.m
//  SLAM
//
//  Created by Xin Sun on 18/10/2015.
//  Copyright © 2015 Xin Sun. All rights reserved.
//

#import "ViewController+InfoDisplay.h"
#import "ViewController+ORB_SLAM.h"
#import "ViewController+MetalRendering.h"
#import "ViewController+PoseGraph.h"
#import "ImageUtility.h"

using namespace cv;

@implementation ViewController (InfoDisplay)

- (void)initProfiler {
    self.profiler = [[Profiler alloc] init];
}

- (void) updateInfoDisplay {
    
        dispatch_async(dispatch_get_main_queue(), ^{
            
            [self.fpsLabel setText:[NSString stringWithFormat:@"fps: %f", 1.f/[self.profiler getAverageTime]]];
            {
                switch([self getTrackingState]) {
                    case -1 :
                        [self.stateLabel setText:[NSString stringWithFormat:@"state: %@", @"SYSTEM_NOT_READY"]];
                        break;
                    case 0 :
                        [self.stateLabel setText:[NSString stringWithFormat:@"state: %@", @"NO_IMAGES_YET"]];
                        break;
                    case 1 :
                        [self.stateLabel setText:[NSString stringWithFormat:@"state: %@", @"NOT_INITIALIZED"]];
                        break;
                    case 2 :
                        [self.stateLabel setText:[NSString stringWithFormat:@"state: %@", @"INITIALIZING"]];
                        break;
                    case 3 : {
                        [self.stateLabel setText:[NSString stringWithFormat:@"state: %@", @"WORKING"]];
                        Mat R = [self getCurrentPose_R];
                        Mat T = [self getCurrentPose_T];
                        Mat center = -R.t()*T;
                        [self addPose:SCNVector3Make(-center.at<float>(0), center.at<float>(1), center.at<float>(2))];
                        [self drawObjectWith:R andT:T];
                        [self.nKFLabel setText:[NSString stringWithFormat:@"nKF: %d", [self getnKF]]];
                        [self.nMPLabel setText:[NSString stringWithFormat:@"nMP: %d", [self getnMP]]];
                        break;
                    }
                    case 4 :
                        [self.stateLabel setText:[NSString stringWithFormat:@"state: %@", @"LOST"]];
                        break;
                    default: {
                        break;
                    }
                }
            }
        });
    
}

- (void) showDepthImage:(Mat&)image {
    
    UIImage* depthImage = [ImageUtility UIImageFromCVMat:image];
    dispatch_async(dispatch_get_main_queue(), ^{
        self.depthView.image = depthImage;;
    });
}

- (void) showColorImage:(Mat&)image {
    
    UIImage* colorImage = [ImageUtility UIImageFromCVMat:image];
    dispatch_async(dispatch_get_main_queue(), ^{
        self.imageView.image = colorImage;;
    });
}

- (void) displayLogInfo:(NSString*) str {
    dispatch_async(dispatch_get_main_queue(), ^{
        [self.logLabel setText:str];
    });
}

@end
