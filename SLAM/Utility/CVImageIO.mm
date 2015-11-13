//
//  CVImageIO.m
//  SLAM
//
//  Created by Xin Sun on 19/10/2015.
//  Copyright © 2015 Xin Sun. All rights reserved.
//

#import "CVImageIO.h"

@implementation CVImageIO

static char documentsPath[2000], *docsPath;

+ (void) initialize {
    if (self == [CVImageIO class]) {
        // Once-only initializion
        NSArray *dirPaths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
        docsPath = (char*)[[dirPaths objectAtIndex:0]cStringUsingEncoding:[NSString defaultCStringEncoding]];
        memcpy(documentsPath, docsPath, strlen(docsPath));
        
        NSError *error;
        NSString *dataPath = [[dirPaths objectAtIndex:0] stringByAppendingPathComponent:@"/Output"];
        if (![[NSFileManager defaultManager] fileExistsAtPath:dataPath])
            [[NSFileManager defaultManager] createDirectoryAtPath:dataPath withIntermediateDirectories:NO attributes:nil error:&error];
    }
}

+ (void) SaveCvMat:(cv::Mat&)mat withName:(const char*) name {
    char path[2000];
    std::vector<int> compression_params;
    compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
    compression_params.push_back(0);
    sprintf(path, "%s/Output/%s", documentsPath, name);
    cv::imwrite(path, mat, compression_params);
}

+ (cv::Mat) LoadCvMatWithName: (const char*) name {
    char path[2000];
    sprintf(path, "%s/Output/%s", documentsPath, name);
    return cv::imread(path).clone();
}

@end
