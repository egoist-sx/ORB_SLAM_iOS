//
//  MetalView.m
//  UpAndRunning3D
//
//  Created by Warren Moore on 8/27/14.
//  Copyright (c) 2014 Metal By Example. All rights reserved.
//

#import "MetalView.h"

@implementation MetalView

+ (Class)layerClass
{
    return [CAMetalLayer class];
}

- (instancetype)initWithCoder:(NSCoder *)aDecoder
{
    if ((self = [super initWithCoder:aDecoder]))
    {
        _metalLayer = (CAMetalLayer *)[self layer];
        _metalLayer.backgroundColor = [UIColor clearColor].CGColor;
        CGFloat scale = [UIScreen mainScreen].scale;
        _metalLayer.drawableSize = CGSizeMake(self.bounds.size.width * scale,
                                              self.bounds.size.height * scale);
    }
    
    return self;
}

@end
