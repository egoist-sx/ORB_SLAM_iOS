//
//  ImageUtility.h
//  SLAM
//
//  Created by Xin Sun on 18/10/2015.
//  Copyright © 2015 Xin Sun. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Structure/Structure.h>
#import <opencv2/highgui/cap_ios.h>

@interface ImageUtility : NSObject

+ (UIImage *) UIImageFromCVMat:(cv::Mat&)cvMat;
+ (cv::Mat) cvMatGrayFromUIImage:(UIImage *)image;
+ (cv::Mat) cvMatFromCMSampleBufferRef:(CMSampleBufferRef)sampleBuffer;
+ (cv::Mat) cvMatFromPointer:(float*)data withSize:(cv::Size) size;

@end
