//
//  ViewController.h
//  ORB_SLAM_iOS
//
//  Created by Xin Sun on 12/10/2015.
//  Copyright © 2015 Xin Sun. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <opencv2/highgui/cap_ios.h>
#import "MetalView.h"
#import "Profiler.h"
#import <SceneKit/SceneKit.h>


@interface ViewController : UIViewController

@property (nonatomic, retain) IBOutlet UILabel* fpsLabel;
@property (nonatomic, retain) IBOutlet UILabel* stateLabel;
@property (nonatomic, retain) IBOutlet UILabel* nKFLabel;
@property (nonatomic, retain) IBOutlet UILabel* nMPLabel;
@property (nonatomic, retain) IBOutlet UILabel* logLabel;
@property (nonatomic, retain) IBOutlet UIImageView* imageView;
@property (nonatomic, retain) IBOutlet UIImageView* depthView;
@property (nonatomic, retain) IBOutlet UIButton* startBtn;
@property (strong, nonatomic) IBOutlet UIButton *fileBtn;
@property (nonatomic, retain) IBOutlet UIButton* resetBtn;
@property (nonatomic, retain) IBOutlet UIButton* recordBtn;
@property (nonatomic, retain) IBOutlet MetalView* metalView;
@property (strong, nonatomic) IBOutlet SCNView *sceneView;
@property (nonatomic, retain) Profiler* profiler;

- (IBAction)StartSLAM:(id)sender;
- (IBAction)ResetSLAM:(id)sender;
- (IBAction)StartRecoding:(id)sender;
- (IBAction)StartFromFile:(id)sender;

@end

