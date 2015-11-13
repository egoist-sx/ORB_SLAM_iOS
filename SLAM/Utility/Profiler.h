//
//  Profiler.h
//  ORB_SLAM_iOS
//
//  Created by Xin Sun on 14/10/2015.
//  Copyright © 2015 Xin Sun. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface Profiler : NSObject

@property int count;
@property float totalTimeInterval;
@property float lastInterval;
@property NSDate* time;

-(float) getAverageTime;
-(long) getLastTime;
-(void) start;
-(void) end;
-(id) init;

@end
