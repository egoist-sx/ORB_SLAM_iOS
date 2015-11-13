//
//  Profiler.m
//  ORB_SLAM_iOS
//
//  Created by Xin Sun on 14/10/2015.
//  Copyright © 2015 Xin Sun. All rights reserved.
//
#import "Profiler.h"

@implementation Profiler

-(id) init {
    self = [super init];
    if (self) {
        _count = 0;
        _totalTimeInterval = 0;
        _lastInterval = -1;
    }
    return self;
}

-(void) start {
    _time = [NSDate date];
}

-(void) end {
    _count++;
    _lastInterval = -[_time timeIntervalSinceNow];
    _totalTimeInterval += _lastInterval;
}

-(long) getLastTime {
    return _lastInterval;
}

-(float) getAverageTime {
    if (_count == 0)
        return -1;
    else
        return static_cast<float>(_totalTimeInterval/static_cast<float>(_count));
}

@end