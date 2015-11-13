//
//  ORBextractor.hpp
//  ORB_SLAM_iOS
//
//  Created by Xin Sun on 14/10/2015.
//  Copyright © 2015 Xin Sun. All rights reserved.
//

#ifndef ORBextractor_hpp
#define ORBextractor_hpp

#include <vector>
#include <list>
#include <opencv2/opencv.hpp>


namespace ORB_SLAM
{
    
    class ORBextractor
    {
    public:
        
        enum {HARRIS_SCORE=0, FAST_SCORE=1 };
        
        ORBextractor(int nfeatures = 1000, float scaleFactor = 1.2f, int nlevels = 8, int scoreType=FAST_SCORE, int fastTh = 20);
        
        ~ORBextractor(){}
        
        // Compute the ORB features and descriptors on an image
        void operator()( cv::InputArray image, cv::InputArray mask,
                        std::vector<cv::KeyPoint>& keypoints,
                        cv::OutputArray descriptors);
        
        int inline GetLevels(){
            return nlevels;}
        
        float inline GetScaleFactor(){
            return scaleFactor;}
        
        
    protected:
        
        void ComputePyramid(cv::Mat image, cv::Mat Mask=cv::Mat());
        void ComputeKeyPoints(std::vector<std::vector<cv::KeyPoint> >& allKeypoints);
        
        std::vector<cv::Point> pattern;
        
        int nfeatures;
        double scaleFactor;
        int nlevels;
        int scoreType;
        int fastTh;
        
        std::vector<int> mnFeaturesPerLevel;
        
        std::vector<int> umax;
        
        std::vector<float> mvScaleFactor;
        std::vector<float> mvInvScaleFactor;
        
        std::vector<cv::Mat> mvImagePyramid;
        std::vector<cv::Mat> mvMaskPyramid;
        
    };
    
} //namespace ORB_SLAM

#endif /* ORBextractor_hpp */
