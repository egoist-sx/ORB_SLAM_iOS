//
//  ViewController+AVFoundation.m
//  SLAM
//
//  Created by Xin Sun on 19/10/2015.
//  Copyright © 2015 Xin Sun. All rights reserved.
//

#import "ViewController+AVFoundation.h"
#import "ViewController+ORB_SLAM.h"
#import "ViewController+InfoDisplay.h"
#import "ImageUtility.h"
#import "CVImageIO.h"
#include <iostream>

@implementation ViewController (AVFoundation)

using namespace cv;

AVCaptureSession *_avCaptureSession_AVFoundation;
AVCaptureDevice *_videoDevice_AVFoundation;
dispatch_queue_t trackingQueue;
//dispatch_queue_t recordingQueue;
int imageCount_AV = 0;
bool isDone = true;
bool isRecording = false;
Mat colorImage;

- (void) initDataInput {
    
    [self setupColorCamera];
    trackingQueue = dispatch_queue_create("tracking", DISPATCH_QUEUE_SERIAL);
    //recordingQueue = dispatch_queue_create("recording", DISPATCH_QUEUE_SERIAL);
}

- (void) TurnOnRecording {
    isRecording = true;
}

- (void) StartDataStream {
    [_avCaptureSession_AVFoundation startRunning];
}

- (void) setupColorCamera {
    
    NSString *sessionPreset = AVCaptureSessionPreset640x480;
    
    // Set up Capture Session.
    _avCaptureSession_AVFoundation = [[AVCaptureSession alloc] init];
    [_avCaptureSession_AVFoundation beginConfiguration];
    
    // Set preset session size.
    [_avCaptureSession_AVFoundation setSessionPreset:sessionPreset];
    
    // Create a video device and input from that Device.  Add the input to the capture session.
    _videoDevice_AVFoundation = [AVCaptureDevice defaultDeviceWithMediaType:AVMediaTypeVideo];
    if (_videoDevice_AVFoundation == nil)
        assert(0);
    
    // Configure Focus, Exposure, and White Balance
    NSError *error;
    
    // Use auto-exposure, and auto-white balance and set the focus to infinity.
    if([_videoDevice_AVFoundation lockForConfiguration:&error])
    {
        // Allow exposure to change
        if ([_videoDevice_AVFoundation isExposureModeSupported:AVCaptureExposureModeContinuousAutoExposure])
            [_videoDevice_AVFoundation setExposureMode:AVCaptureExposureModeContinuousAutoExposure];
        
        // Allow white balance to change
        if ([_videoDevice_AVFoundation isWhiteBalanceModeSupported:AVCaptureWhiteBalanceModeContinuousAutoWhiteBalance])
            [_videoDevice_AVFoundation setWhiteBalanceMode:AVCaptureWhiteBalanceModeContinuousAutoWhiteBalance];
        
        // Set focus at the maximum position allowable (e.g. "near-infinity") to get the
        // best color/depth alignment.
        [_videoDevice_AVFoundation setFocusModeLockedWithLensPosition:1.0f completionHandler:nil];
        
        [_videoDevice_AVFoundation unlockForConfiguration];
    }
    
    //  Add the device to the session.
    AVCaptureDeviceInput *input = [AVCaptureDeviceInput deviceInputWithDevice:_videoDevice_AVFoundation error:&error];
    if (error)
    {
        NSLog(@"Cannot initialize AVCaptureDeviceInput");
        assert(0);
    }
    
    [_avCaptureSession_AVFoundation addInput:input]; // After this point, captureSession captureOptions are filled.
    
    //  Create the output for the capture session.
    AVCaptureVideoDataOutput* dataOutput = [[AVCaptureVideoDataOutput alloc] init];
    
    // We don't want to process late frames.
    [dataOutput setAlwaysDiscardsLateVideoFrames:YES];
    
    // Use BGRA pixel format.
    [dataOutput setVideoSettings:[NSDictionary
                                  dictionaryWithObject:[NSNumber numberWithInt:kCVPixelFormatType_32BGRA]
                                  forKey:(id)kCVPixelBufferPixelFormatTypeKey]];
    
    // Set dispatch to be on the main thread so OpenGL can do things with the data
    [dataOutput setSampleBufferDelegate:self queue:dispatch_get_main_queue()];
    
    [_avCaptureSession_AVFoundation addOutput:dataOutput];
    
    if([_videoDevice_AVFoundation lockForConfiguration:&error])
    {
        [_videoDevice_AVFoundation setActiveVideoMaxFrameDuration:CMTimeMake(1, 30)];
        [_videoDevice_AVFoundation setActiveVideoMinFrameDuration:CMTimeMake(1, 30)];
        [_videoDevice_AVFoundation unlockForConfiguration];
    }
    
    [_avCaptureSession_AVFoundation commitConfiguration];
}

- (void)captureOutput:(AVCaptureOutput *)captureOutput didOutputSampleBuffer:(CMSampleBufferRef)sampleBuffer fromConnection:(AVCaptureConnection *)connection
{
    if (isDone) {
        isDone = false;
        colorImage = [ImageUtility cvMatFromCMSampleBufferRef: sampleBuffer];
        
        dispatch_async(trackingQueue, ^{
            Mat dummyDepth(cv::Size(320, 240), CV_32FC1, Scalar(-1.0f));
            Mat colorInput;
            resize(colorImage, colorInput, cv::Size(320, 240));
            if (isRecording) {
                //dispatch_async(recordingQueue, ^{
                char name[2000];
                sprintf(name, "%04d.png", imageCount_AV);
                imageCount_AV++;
                [CVImageIO SaveCvMat:colorInput withName:name];
                //});
            }
            cvtColor(colorInput, colorInput, CV_BGRA2GRAY);
    
            [self.profiler start];
            [self trackFrame:colorInput andDepth:dummyDepth];
            [self.profiler end];
            [self showColorImage: colorImage];
            [self updateInfoDisplay];
            isDone = true;
        });
    }
}

@end

