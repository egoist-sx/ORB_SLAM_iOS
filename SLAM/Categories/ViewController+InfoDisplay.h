//
//  ViewController+InfoDisplay.h
//  SLAM
//
//  Created by Xin Sun on 18/10/2015.
//  Copyright © 2015 Xin Sun. All rights reserved.
//

#import "ViewController.h"

@interface ViewController (InfoDisplay)

- (void) initProfiler;
- (void) updateInfoDisplay;
- (void) showDepthImage:(cv::Mat&)image;
- (void) showColorImage:(cv::Mat&)image;
- (void) displayLogInfo:(NSString*) str;

@end
