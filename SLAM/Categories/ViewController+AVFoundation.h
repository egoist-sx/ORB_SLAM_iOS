//
//  ViewController+AVFoundation.h
//  SLAM
//
//  Created by Xin Sun on 19/10/2015.
//  Copyright © 2015 Xin Sun. All rights reserved.
//

#import "ViewController.h"
#import <AVFoundation/AVFoundation.h>

@interface ViewController (AVFoundation)<AVCaptureVideoDataOutputSampleBufferDelegate>

- (void) initDataInput;
- (void) StartDataStream;
- (void) TurnOnRecording;

@end
