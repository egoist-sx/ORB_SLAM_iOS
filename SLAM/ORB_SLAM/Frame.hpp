//
//  Frame.hpp
//  ORB_SLAM_iOS
//
//  Created by Xin Sun on 14/10/2015.
//  Copyright © 2015 Xin Sun. All rights reserved.
//

#ifndef Frame_hpp
#define Frame_hpp

#include "MapPoint.hpp"
#include "Thirdparty/DBoW2/DBoW2/BowVector.h"
#include "Thirdparty/DBoW2/DBoW2/FeatureVector.h"
#include "ORBVocabulary.hpp"
#include "KeyFrame.hpp"
#include "ORBextractor.hpp"

#include <opencv2/opencv.hpp>

namespace ORB_SLAM
{
#define FRAME_GRID_ROWS 48
#define FRAME_GRID_COLS 64
    
    class tracking;
    class MapPoint;
    class KeyFrame;
    class KeyFrameDatabase;
    
    class Frame
    {
    public:
        Frame();
        Frame(const Frame &frame);
        Frame(cv::Mat &im, const double &timeStamp, ORBextractor* extractor, ORBVocabulary* voc, cv::Mat &K, cv::Mat &distCoef);
        
        ORBVocabulary* mpORBvocabulary;
        ORBextractor* mpORBextractor;
        
        // Frame image
        cv::Mat im;
        //cv::Mat depth;
        
        // Frame timestamp
        double mTimeStamp;
        
        // Calibration Matrix and k1,k2,p1,p2 Distortion Parameters
        cv::Mat mK;
        static float fx;
        static float fy;
        static float cx;
        static float cy;
        cv::Mat mDistCoef;
        
        // Number of KeyPoints
        int N;
        
        // Vector of keypoints (original for visualization) and undistorted (actually used by the system)
        std::vector<cv::KeyPoint> mvKeys;
        std::vector<cv::KeyPoint> mvKeysUn;
        
        // Bag of Words Vector structures
        DBoW2::BowVector mBowVec;
        DBoW2::FeatureVector mFeatVec;
        
        // ORB descriptor, each row associated to a keypoint
        cv::Mat mDescriptors;
        
        // MapPoints associated to keypoints, NULL pointer if not association
        std::vector<MapPoint*> mvpMapPoints;
        
        // Flag to identify outlier associations
        std::vector<bool> mvbOutlier;
        
        // Keypoints are assigned to cells in a grid to reduce matching complexity when projecting MapPoints
        float mfGridElementWidthInv;
        float mfGridElementHeightInv;
        std::vector<std::size_t> mGrid[FRAME_GRID_COLS][FRAME_GRID_ROWS];
        
        // Camera Pose
        cv::Mat mTcw;
        
        // Current and Next Frame id
        static long unsigned int nNextId;
        long unsigned int mnId;
        
        KeyFrame* mpReferenceKF;
        
        void ComputeBoW();
        
        void UpdatePoseMatrices();
        
        // Check if a MapPoint is in the frustum of the camera and also fills variables of the MapPoint to be used by the tracking
        bool isInFrustum(MapPoint* pMP, float viewingCosLimit);
        
        // Compute the cell of a keypoint (return false if outside the grid)
        bool PosInGrid(cv::KeyPoint &kp, int &posX, int &posY);
        
        vector<size_t> GetFeaturesInArea(const float &x, const float  &y, const float  &r, const int minLevel=-1, const int maxLevel=-1) const;
        
        // Scale Pyramid Info
        int mnScaleLevels;
        float mfScaleFactor;
        vector<float> mvScaleFactors;
        vector<float> mvLevelSigma2;
        vector<float> mvInvLevelSigma2;
        
        // Undistorted Image Bounds (computed once)
        static int mnMinX;
        static int mnMaxX;
        static int mnMinY;
        static int mnMaxY;
        
        static bool mbInitialComputations;
        
        
    private:
        
        void UndistortKeyPoints();
        void ComputeImageBounds();
        
        // Call UpdatePoseMatrices(), before using
        cv::Mat mOw;
        cv::Mat mRcw;
        cv::Mat mtcw;
    };
    
}// namespace ORB_SLAM

#endif /* Frame_hpp */
