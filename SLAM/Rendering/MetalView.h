//
//  MetalView.h
//  UpAndRunning3D
//
//  Created by Warren Moore on 8/27/14.
//  Copyright (c) 2014 Metal By Example. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <QuartzCore/CAMetalLayer.h>
#import <Metal/Metal.h>

@interface MetalView : UIView

@property(nonatomic, strong) CAMetalLayer *metalLayer;

@end
