//
//  ViewController.m
//  ORB_SLAM_iOS
//
//  Created by Xin Sun on 12/10/2015.
//  Copyright © 2015 Xin Sun. All rights reserved.
//

#import "ViewController.h"

#import "Categories/ViewController+RGBSource.h"
//#import "Categories/ViewController+AVFoundation.h"
//#import "Categories/ViewController+ImageFile.h"

#import "Categories/ViewController+InfoDisplay.h"
#import "Categories/ViewController+MetalRendering.h"
#import "Categories/ViewController+ORB_SLAM.h"
#import "Categories/ViewController+PoseGraph.h"

using namespace std;
using namespace cv;

@implementation ViewController

- (void)viewDidLoad {
    
    [super viewDidLoad];
    
    [self initProfiler];
    //[self initDataInput];
    [self initRendering];
    [self initORB_SLAM];
    [self sceneSetup];
}

-(IBAction) StartSLAM:(id)sender {
    //[self StartDataStream];
    [self RunFromAVFoundation];
}

- (IBAction)StartFromFile:(id)sender {
    [self RunFromFile];
}

- (IBAction)ResetSLAM:(id)sender {
    [self requestSLAMReset];
    [self resetSceneView];
}

- (IBAction)StartRecoding:(id)sender {
    [self TurnOnRecording];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


@end
