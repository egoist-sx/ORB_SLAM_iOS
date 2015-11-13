//
//  ViewController+ORB_SLAM.h
//  SLAM
//
//  Created by Xin Sun on 18/10/2015.
//  Copyright © 2015 Xin Sun. All rights reserved.
//

#import "ViewController.h"

@interface ViewController (ORB_SLAM)
    
- (void) initORB_SLAM;
- (void) trackFrame:(cv::Mat&)colorImage andDepth:(cv::Mat&) depthImage;
- (int) getTrackingState;
- (cv::Mat) getCurrentPose_R;
- (cv::Mat) getCurrentPose_T;
- (int) getnKF;
- (int) getnMP;
- (void) requestSLAMReset;

@end
