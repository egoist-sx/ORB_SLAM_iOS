//
//  LocalMapping.hpp
//  ORB_SLAM_iOS
//
//  Created by Xin Sun on 14/10/2015.
//  Copyright © 2015 Xin Sun. All rights reserved.
//

#ifndef LocalMapping_hpp
#define LocalMapping_hpp

#include "KeyFrame.hpp"
#include "Map.hpp"
#include "LoopClosing.hpp"
#include "Tracking.hpp"
#include <boost/thread.hpp>
#include "KeyFrameDatabase.hpp"

namespace ORB_SLAM
{
    
    class Tracking;
    class LoopClosing;
    class Map;
    
    class LocalMapping
    {
    public:
        LocalMapping(Map* pMap);
        LocalMapping();
        
        void SetLoopCloser(LoopClosing* pLoopCloser);
        
        void SetTracker(Tracking* pTracker);
        
        void Run();
        
        void InsertKeyFrame(KeyFrame* pKF);
        
        // Thread Synch
        void RequestStop();
        void RequestReset();
        
        void Stop();
        
        void Release();
        
        bool isStopped();
        
        bool stopRequested();
        
        bool AcceptKeyFrames();
        void SetAcceptKeyFrames(bool flag);
        
        void InterruptBA();
        
    protected:
        
        bool CheckNewKeyFrames();
        void ProcessNewKeyFrame();
        void CreateNewMapPoints();
        
        void MapPointCulling();
        void SearchInNeighbors();
        
        void KeyFrameCulling();
        
        cv::Mat ComputeF12(KeyFrame* &pKF1, KeyFrame* &pKF2);
        
        cv::Mat SkewSymmetricMatrix(const cv::Mat &v);
        
        void ResetIfRequested();
        bool mbResetRequested;
        boost::mutex mMutexReset;
        
        Map* mpMap;
        
        LoopClosing* mpLoopCloser;
        Tracking* mpTracker;
        
        std::list<KeyFrame*> mlNewKeyFrames;
        
        KeyFrame* mpCurrentKeyFrame;
        
        std::list<MapPoint*> mlpRecentAddedMapPoints;
        
        boost::mutex mMutexNewKFs;    
        
        bool mbAbortBA;
        
        bool mbStopped;
        bool mbStopRequested;
        boost::mutex mMutexStop;
        
        bool mbAcceptKeyFrames;
        boost::mutex mMutexAccept;
    };
    
} //namespace ORB_SLAM

#endif /* LocalMapping_hpp */
