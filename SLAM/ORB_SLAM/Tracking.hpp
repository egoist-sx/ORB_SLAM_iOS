/**
* This file is part of ORB-SLAM.
*
* Copyright (C) 2014 Raúl Mur-Artal <raulmur at unizar dot es> (University of Zaragoza)
* For more information see <http://webdiis.unizar.es/~raulmur/orbslam/>
*
* ORB-SLAM is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* ORB-SLAM is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with ORB-SLAM. If not, see <http://www.gnu.org/licenses/>.
*/

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
