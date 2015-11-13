//
//  Tracking.hpp
//  ORB_SLAM_iOS
//
//  Created by Xin Sun on 14/10/2015.
//  Copyright © 2015 Xin Sun. All rights reserved.
//

#ifndef Tracking_hpp
#define Tracking_hpp

#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>

#include "Map.hpp"
#include "LocalMapping.hpp"
#include "LoopClosing.hpp"
#include "Frame.hpp"
#include "ORBVocabulary.hpp"
#include "KeyFrameDatabase.hpp"
#include "ORBextractor.hpp"
#include "Initializer.hpp"

namespace ORB_SLAM
{
    
    class Map;
    class LocalMapping;
    class LoopClosing;
    
    class Tracking
    {
        
    public:
        Tracking(ORBVocabulary* pVoc,  Map* pMap, string strSettingPath);
        Tracking();
        
        enum eTrackingState{
            SYSTEM_NOT_READY=-1,
            NO_IMAGES_YET=0,
            NOT_INITIALIZED=1,
            INITIALIZING=2,
            WORKING=3,
            LOST=4
        };
        
        void SetLocalMapper(LocalMapping* pLocalMapper);
        void SetLoopClosing(LoopClosing* pLoopClosing);
        void SetKeyFrameDatabase(KeyFrameDatabase* pKFDB);
        void GrabImage(cv::Mat &rgb, cv::Mat &depth);
        cv::Mat GetPose_R();
        cv::Mat GetPose_T();
        void Reset();
        
        // This is the main function of the Tracking Thread
        void Run();
        
        void ForceRelocalisation();
        
        eTrackingState mState;
        eTrackingState mLastProcessedState;
        
        // Current Frame
        Frame mCurrentFrame;
        
        // Initialization Variables
        std::vector<int> mvIniLastMatches;
        std::vector<int> mvIniMatches;
        std::vector<cv::Point2f> mvbPrevMatched;
        std::vector<cv::Point3f> mvIniP3D;
        Frame mInitialFrame;
        
        
        // to be deleted
        //int indexX, indexY;
        //float depthScale;
        //float medianDepthLog;
        
    protected:
        
        void FirstInitialization();
        void Initialize();
        void CreateInitialMap(cv::Mat &Rcw, cv::Mat &tcw);
        
        bool TrackPreviousFrame();
        bool TrackWithMotionModel();
        
        bool RelocalisationRequested();
        bool Relocalisation();
        
        void UpdateReference();
        void UpdateReferencePoints();
        void UpdateReferenceKeyFrames();
        
        bool TrackLocalMap();
        void SearchReferencePointsInFrustum();
        
        bool NeedNewKeyFrame();
        void CreateNewKeyFrame();
        
        
        //Other Thread Pointers
        LocalMapping* mpLocalMapper;
        LoopClosing* mpLoopClosing;
        
        //ORB
        ORBextractor* mpORBextractor;
        ORBextractor* mpIniORBextractor;
        
        //BoW
        ORBVocabulary* mpORBVocabulary;
        KeyFrameDatabase* mpKeyFrameDB;
        
        // Initalization
        Initializer* mpInitializer;
        
        //Local Map
        KeyFrame* mpReferenceKF;
        std::vector<KeyFrame*> mvpLocalKeyFrames;
        std::vector<MapPoint*> mvpLocalMapPoints;
        
        //Map
        Map* mpMap;
        
        //Calibration matrix
        cv::Mat mK;
        cv::Mat mDistCoef;
        
        //New KeyFrame rules (according to fps)
        int mMinFrames;
        int mMaxFrames;
        
        //Current matches in frame
        int mnMatchesInliers;
        
        //Last Frame, KeyFrame and Relocalisation Info
        KeyFrame* mpLastKeyFrame;
        Frame mLastFrame;
        unsigned int mnLastKeyFrameId;
        unsigned int mnLastRelocFrameId;
        
        //Mutex
        boost::mutex mMutexTrack;
        boost::mutex mMutexForceRelocalisation;
        
        //Reset
        bool mbPublisherStopped;
        bool mbReseting;
        boost::mutex mMutexReset;
        
        //Is relocalisation requested by an external thread? (loop closing)
        bool mbForceRelocalisation;
        
        //Motion Model
        bool mbMotionModel;
        cv::Mat mVelocity;
        
        //Color order (true RGB, false BGR, ignored if grayscale)
        bool mbRGB;
        
        boost::mutex mMutexPose;
        cv::Mat pose_R;
        cv::Mat pose_T;
    };
    
} //namespace ORB_SLAM

#endif /* Tracking_hpp */
