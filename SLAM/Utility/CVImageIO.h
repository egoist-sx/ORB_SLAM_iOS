//
//  CVImageIO.h
//  SLAM
//
//  Created by Xin Sun on 19/10/2015.
//  Copyright © 2015 Xin Sun. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <opencv2/opencv.hpp>

@interface CVImageIO : NSObject

+ (void)SaveCvMat:(cv::Mat&)mat withName:(const char*) name;
+ (cv::Mat) LoadCvMatWithName: (const char*) name;

@end
