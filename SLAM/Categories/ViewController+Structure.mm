//
//  ViewController+ImageInput.m
//  SLAM
//
//  Created by Xin Sun on 18/10/2015.
//  Copyright © 2015 Xin Sun. All rights reserved.
//

#import "ViewController+Structure.h"
#import "ViewController+ORB_SLAM.h"
#import "ViewController+InfoDisplay.h"
#import "ImageUtility.h"

@implementation ViewController (Structure)

using namespace cv;

STSensorController *_sensorController;
AVCaptureSession *_avCaptureSession_Structure;
AVCaptureDevice *_videoDevice_Structure;

- (void) initDataInput {
    
    _sensorController = [STSensorController sharedController];
    _sensorController.delegate = self;
    
    [self setupColorCamera];
}

- (void) StartDataStream {
    [self startColorCamera];
    [self startDepthCamera];
}

- (void) startColorCamera {
    [_avCaptureSession_Structure startRunning];
}

- (void) startDepthCamera {
    
    STSensorControllerInitStatus result = [_sensorController initializeSensorConnection];
    
    BOOL didSucceed = (result == STSensorControllerInitStatusSuccess || result == STSensorControllerInitStatusAlreadyInitialized);
    if (didSucceed)
    {
        // There's no status about the sensor that we need to display anymore
        
        // Set sensor stream quality
        STStreamConfig streamConfig = STStreamConfigRegisteredDepth320x240;
        
        // Request that we receive depth frames with synchronized color pairs
        // After this call, we will start to receive frames through the delegate methods
        NSError* error = nil;
        BOOL optionsAreValid = [_sensorController startStreamingWithOptions:@{kSTStreamConfigKey : @(streamConfig),
                                                                              kSTFrameSyncConfigKey : @(STFrameSyncDepthAndRgb),
                                                                              kSTColorCameraFixedLensPositionKey:@(0.75)}
                                                                      error:&error];
        if (!optionsAreValid)
        {
            NSLog(@"Error during streaming start: %s", [[error localizedDescription] UTF8String]);
        }
    }
}

- (void) setupColorCamera {
    
    NSString *sessionPreset = AVCaptureSessionPreset640x480;
    
    // Set up Capture Session.
    _avCaptureSession_Structure = [[AVCaptureSession alloc] init];
    [_avCaptureSession_Structure beginConfiguration];
    
    // Set preset session size.
    [_avCaptureSession_Structure setSessionPreset:sessionPreset];
    
    // Create a video device and input from that Device.  Add the input to the capture session.
    _videoDevice_Structure = [AVCaptureDevice defaultDeviceWithMediaType:AVMediaTypeVideo];
    if (_videoDevice_Structure == nil)
        assert(0);
    
    // Configure Focus, Exposure, and White Balance
    NSError *error;
    
    // Use auto-exposure, and auto-white balance and set the focus to infinity.
    if([_videoDevice_Structure lockForConfiguration:&error])
    {
        // Allow exposure to change
        if ([_videoDevice_Structure isExposureModeSupported:AVCaptureExposureModeContinuousAutoExposure])
            [_videoDevice_Structure setExposureMode:AVCaptureExposureModeContinuousAutoExposure];
        
        // Allow white balance to change
        if ([_videoDevice_Structure isWhiteBalanceModeSupported:AVCaptureWhiteBalanceModeContinuousAutoWhiteBalance])
            [_videoDevice_Structure setWhiteBalanceMode:AVCaptureWhiteBalanceModeContinuousAutoWhiteBalance];
        
        // Set focus at the maximum position allowable (e.g. "near-infinity") to get the
        // best color/depth alignment.
        [_videoDevice_Structure setFocusModeLockedWithLensPosition:1.0f completionHandler:nil];
        
        [_videoDevice_Structure unlockForConfiguration];
    }
    
    //  Add the device to the session.
    AVCaptureDeviceInput *input = [AVCaptureDeviceInput deviceInputWithDevice:_videoDevice_Structure error:&error];
    if (error)
    {
        NSLog(@"Cannot initialize AVCaptureDeviceInput");
        assert(0);
    }
    
    [_avCaptureSession_Structure addInput:input]; // After this point, captureSession captureOptions are filled.
    
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
    
    [_avCaptureSession_Structure addOutput:dataOutput];
    
    if([_videoDevice_Structure lockForConfiguration:&error])
    {
        [_videoDevice_Structure setActiveVideoMaxFrameDuration:CMTimeMake(1, 30)];
        [_videoDevice_Structure setActiveVideoMinFrameDuration:CMTimeMake(1, 30)];
        [_videoDevice_Structure unlockForConfiguration];
    }
    
    [_avCaptureSession_Structure commitConfiguration];
}

- (void)captureOutput:(AVCaptureOutput *)captureOutput didOutputSampleBuffer:(CMSampleBufferRef)sampleBuffer fromConnection:(AVCaptureConnection *)connection
{
    // Pass into the driver. The sampleBuffer will return later with a synchronized depth or IR pair.
    [_sensorController frameSyncNewColorBuffer:sampleBuffer];
}

- (void)sensorDidOutputSynchronizedDepthFrame:(STDepthFrame *)depthFrame
                                andColorFrame:(STColorFrame *)colorFrame
{
    
    Mat depthMat = [ImageUtility cvMatFromPointer:depthFrame.depthInMillimeters withSize:cv::Size(320, 240)];
    
    Mat colorMat = [ImageUtility cvMatFromCMSampleBufferRef: colorFrame.sampleBuffer];
    [self.profiler start];
    [self trackFrame:colorMat andDepth:depthMat];
    [self.profiler end];
    
    
    Mat depthDisplay;
    depthMat.convertTo(depthDisplay, CV_8UC1, 255.f/5000.f);
    
    [self showDepthImage: depthDisplay];
    [self showColorImage: colorMat];
    [self updateInfoDisplay];
}

- (void)sensorDidDisconnect
{
}

- (void)sensorDidConnect
{
}

 (void)sensorDidLeaveLowPowerMode
{
}

- (void)sensorBatteryNeedsCharging
{
}

- (void)sensorDidStopStreaming:(STSensorControllerDidStopStreamingReason)reason
{
}

@end
