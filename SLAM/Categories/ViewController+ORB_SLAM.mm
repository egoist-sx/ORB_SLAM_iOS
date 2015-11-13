//
//  ViewController+ORB_SLAM.m
//  SLAM
//
//  Created by Xin Sun on 18/10/2015.
//  Copyright © 2015 Xin Sun. All rights reserved.
//

#import "ViewController+ORB_SLAM.h"
#import "ViewController+InfoDisplay.h"
#import "ImageUtility.h"

#include <iostream>
#include <boost/thread.hpp>
#include "../ORB_SLAM/LocalMapping.hpp"
#include "../ORB_SLAM/LoopClosing.hpp"
#include "../ORB_SLAM/KeyFrameDatabase.hpp"
#include "../ORB_SLAM/ORBVocabulary.hpp"
#include "../ORB_SLAM/Converter.hpp"

using namespace cv;

@implementation ViewController (ORB_SLAM)

ORB_SLAM::Map* _World;
ORB_SLAM::Tracking* _Tracker;
ORB_SLAM::ORBVocabulary* _Vocabulary;
ORB_SLAM::KeyFrameDatabase* _Database;
ORB_SLAM::LocalMapping* _LocalMapper;
ORB_SLAM::LoopClosing* _LoopCloser;

bool loadVocab = true;
    
- (void) initORB_SLAM {
    
    [self.stateLabel setText:@"state: Loading Vocab"];
    [self.startBtn setEnabled:false];
    [self.recordBtn setEnabled:false];
    [self.resetBtn setEnabled:false];
    [self.fileBtn setEnabled:false];
    
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        //ORB_SLAM::ORBVocabulary Vocabulary;
        const char *ORBvoc = [[[NSBundle mainBundle]pathForResource:@"ORBvoc" ofType:@"txt"] cStringUsingEncoding:[NSString defaultCStringEncoding]];
        _Vocabulary = new ORB_SLAM::ORBVocabulary();
        if (loadVocab) {
            bool bVocLoad = _Vocabulary->loadFromTextFile(ORBvoc);
            
            if(!bVocLoad)
            {
                cerr << "Wrong path to vocabulary. Path must be absolut or relative to ORB_SLAM package directory." << endl;
            }
        }
        
        _Database = new ORB_SLAM::KeyFrameDatabase(*_Vocabulary);
        
        dispatch_async(dispatch_get_main_queue(), ^{
            
            [self.stateLabel setText:@"state: Vocab loaded"];
            [self.startBtn setEnabled:true];
            [self.recordBtn setEnabled:true];
            [self.resetBtn setEnabled:true];
            [self.fileBtn setEnabled:true];
            //Initialize the Tracking Thread and launch
            
            _World = new ORB_SLAM::Map();
            
            const char *settings = [[[NSBundle mainBundle]pathForResource:@"Settings" ofType:@"yaml"] cStringUsingEncoding:[NSString defaultCStringEncoding]];
            _Tracker = new ORB_SLAM::Tracking(_Vocabulary, _World, settings);
            boost::thread trackingThread(&ORB_SLAM::Tracking::Run, _Tracker);
            
            _Tracker->SetKeyFrameDatabase(_Database);
            
            //Initialize the Local Mapping Thread and launch
            _LocalMapper = new ORB_SLAM::LocalMapping(_World);
            boost::thread localMappingThread(&ORB_SLAM::LocalMapping::Run, _LocalMapper);
            
            //Initialize the Loop Closing Thread and launch
            _LoopCloser = new ORB_SLAM::LoopClosing(_World, _Database, _Vocabulary);
            boost::thread loopClosingThread(&ORB_SLAM::LoopClosing::Run, _LoopCloser);
            
            //Set pointers between threads
            _Tracker->SetLocalMapper(_LocalMapper);
            _Tracker->SetLoopClosing(_LoopCloser);
            
            _LocalMapper->SetTracker(_Tracker);
            _LocalMapper->SetLoopCloser(_LoopCloser);
            
            _LoopCloser->SetTracker(_Tracker);
            _LoopCloser->SetLocalMapper(_LocalMapper);
        });
    });
}

- (void) trackFrame:(Mat&)colorImage andDepth:(Mat&) depthImage {
    
    _Tracker->GrabImage(colorImage, depthImage);
}

- (Mat) getCurrentPose_R {
    return _Tracker->GetPose_R();
}

- (Mat) getCurrentPose_T {
    return _Tracker->GetPose_T();
}

- (int) getTrackingState {
    return _Tracker->mState;
}

- (int) getnKF {
    return _World->KeyFramesInMap();
}

- (int) getnMP {
    return _World->MapPointsInMap();
}

- (void) requestSLAMReset {
    _Tracker->Reset();
}

@end
