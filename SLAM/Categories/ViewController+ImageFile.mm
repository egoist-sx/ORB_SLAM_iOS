//
//  ViewController+ImageFile.m
//  SLAM
//
//  Created by Xin Sun on 19/10/2015.
//  Copyright © 2015 Xin Sun. All rights reserved.
//

#import "ViewController+ImageFile.h"
#import "ViewController+ORB_SLAM.h"
#import "ViewController+InfoDisplay.h"
#import "CVImageIO.h"
#include <iostream>

@implementation ViewController (ImageFile)

using namespace cv;
using namespace std;

int imageCount_IF = 1;
dispatch_queue_t trackingQueue_IF;
Mat tempColorImage_IF;
char tempName_IF[2000];
bool isDone_IF = true;

- (void) initDataInput {
    [self.recordBtn setAlpha:0];
    trackingQueue_IF = dispatch_queue_create("tracking", DISPATCH_QUEUE_SERIAL);
}

- (void) TurnOnRecording {
    
}

- (void) StartDataStream {
    dispatch_async(trackingQueue_IF, ^{
        while (true) {
            sprintf(tempName_IF, "%04d.png", imageCount_IF);
            tempColorImage_IF = [CVImageIO LoadCvMatWithName:tempName_IF];
            if (tempColorImage_IF.empty()) {
                break;
            }
            imageCount_IF++;
            Mat dummyDepth(cv::Size(320, 240), CV_32FC1, Scalar(-1.0f));
            [self.profiler start];
            [self trackFrame:tempColorImage_IF andDepth:dummyDepth];
            [self.profiler end];
            [self showColorImage: tempColorImage_IF];
            [self updateInfoDisplay];
            // This is used to control speed
            [NSThread sleepForTimeInterval:0.1];
        }
    });
}

@end
