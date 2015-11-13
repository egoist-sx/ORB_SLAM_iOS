//
//  MapPoint.hpp
//  ORB_SLAM_iOS
//
//  Created by Xin Sun on 14/10/2015.
//  Copyright © 2015 Xin Sun. All rights reserved.
//

#ifndef MapPoint_hpp
#define MapPoint_hpp

#include<opencv2/core/core.hpp>
#include"KeyFrame.hpp"
#include"Map.hpp"
#include<boost/thread.hpp>

namespace ORB_SLAM
{
    
    class ImageFeature;
    class KeyFrame;
    class Map;
    
    
    class MapPoint
    {
    public:
        MapPoint(const cv::Mat &Pos, KeyFrame* pRefKF, Map* pMap);
        
        void SetWorldPos(const cv::Mat &Pos);
        cv::Mat GetWorldPos();
        
        cv::Mat GetNormal();
        KeyFrame* GetReferenceKeyFrame();
        
        std::map<KeyFrame*,size_t> GetObservations();
        int Observations();
        
        void AddObservation(KeyFrame* pKF,size_t idx);
        void EraseObservation(KeyFrame* pKF);
        
        int GetIndexInKeyFrame(KeyFrame* pKF);
        bool IsInKeyFrame(KeyFrame* pKF);
        
        void SetBadFlag();
        bool isBad();
        
        void Replace(MapPoint* pMP);
        
        void IncreaseVisible();
        void IncreaseFound();
        float GetFoundRatio();
        
        void ComputeDistinctiveDescriptors();
        
        cv::Mat GetDescriptor();
        
        void UpdateNormalAndDepth();
        
        float GetMinDistanceInvariance();
        float GetMaxDistanceInvariance();
        
    public:
        long unsigned int mnId;
        static long unsigned int nNextId;
        long int mnFirstKFid;
        
        // Variables used by the tracking
        float mTrackProjX;
        float mTrackProjY;
        bool mbTrackInView;
        int mnTrackScaleLevel;
        float mTrackViewCos;
        long unsigned int mnTrackReferenceForFrame;
        long unsigned int mnLastFrameSeen;
        
        // Variables used by local mapping
        long unsigned int mnBALocalForKF;
        long unsigned int mnFuseCandidateForKF;
        
        // Variables used by loop closing
        long unsigned int mnLoopPointForKF;
        long unsigned int mnCorrectedByKF;
        long unsigned int mnCorrectedReference;
        
    protected:
        
        // Position in absolute coordinates
        cv::Mat mWorldPos;
        
        // Keyframes observing the point and associated index in keyframe
        std::map<KeyFrame*,size_t> mObservations;
        
        // Mean viewing direction
        cv::Mat mNormalVector;
        
        // Best descriptor to fast matching
        cv::Mat mDescriptor;
        
        // Reference KeyFrame
        KeyFrame* mpRefKF;
        
        // Tracking counters
        int mnVisible;
        int mnFound;
        
        // Bad flag (we do not currently erase MapPoint from memory)
        bool mbBad;
        
        // Scale invariance distances
        float mfMinDistance;
        float mfMaxDistance;
        
        Map* mpMap;
        
        boost::mutex mMutexPos;
        boost::mutex mMutexFeatures;
    };
    
} //namespace ORB_SLAM

#endif /* MapPoint_hpp */
