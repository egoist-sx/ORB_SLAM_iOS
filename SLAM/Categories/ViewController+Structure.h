//
//  ViewController+ImageInput.h
//  SLAM
//
//  Created by Xin Sun on 18/10/2015.
//  Copyright © 2015 Xin Sun. All rights reserved.
//

#import "ViewController.h"
#import <AVFoundation/AVFoundation.h>

@interface ViewController (Structure)<STSensorControllerDelegate, AVCaptureVideoDataOutputSampleBufferDelegate>

- (void) initDataInput;
- (void) StartDataStream;

@end
