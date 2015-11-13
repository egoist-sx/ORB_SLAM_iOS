//
//  LoopClosing.hpp
//  ORB_SLAM_iOS
//
//  Created by Xin Sun on 14/10/2015.
//  Copyright © 2015 Xin Sun. All rights reserved.
//

#ifndef LoopClosing_hpp
#define LoopClosing_hpp

#include "KeyFrame.hpp"
#include "LocalMapping.hpp"
#include "Map.hpp"
#include "ORBVocabulary.hpp"
#include "Tracking.hpp"
#include <boost/thread.hpp>
#include "KeyFrameDatabase.hpp"
#include "Thirdparty/g2o/g2o/types/sim3/types_seven_dof_expmap.h"

namespace ORB_SLAM
{
    
    class Tracking;
    class LocalMapping;
    class KeyFrameDatabase;
    
    class LoopClosing
    {
    public:
        
        typedef pair<set<KeyFrame*>,int> ConsistentGroup;
        typedef map<KeyFrame*,g2o::Sim3,std::less<KeyFrame*>,
        Eigen::aligned_allocator<std::pair<const KeyFrame*, g2o::Sim3> > > KeyFrameAndPose;
        
    public:
        
        LoopClosing(Map* pMap, KeyFrameDatabase* pDB, ORBVocabulary* pVoc);
        LoopClosing();
        
        void SetTracker(Tracking* pTracker);
        
        void SetLocalMapper(LocalMapping* pLocalMapper);
        
        void Run();
        
        void InsertKeyFrame(KeyFrame *pKF);
        
        void RequestReset();
        
    protected:
        
        bool CheckNewKeyFrames();
        
        bool DetectLoop();
        
        bool ComputeSim3();
        
        void SearchAndFuse(KeyFrameAndPose &CorrectedPosesMap);
        
        void CorrectLoop();
        
        void ResetIfRequested();
        bool mbResetRequested;
        boost::mutex mMutexReset;
        
        Map* mpMap;
        Tracking* mpTracker;
        
        KeyFrameDatabase* mpKeyFrameDB;
        ORBVocabulary* mpORBVocabulary;
        
        LocalMapping *mpLocalMapper;
        
        std::list<KeyFrame*> mlpLoopKeyFrameQueue;
        
        boost::mutex mMutexLoopQueue;
        
        std::vector<float> mvfLevelSigmaSquare;
        
        // Loop detector parameters
        float mnCovisibilityConsistencyTh;
        
        // Loop detector variables
        KeyFrame* mpCurrentKF;
        KeyFrame* mpMatchedKF;
        std::vector<ConsistentGroup> mvConsistentGroups;
        std::vector<KeyFrame*> mvpEnoughConsistentCandidates;
        std::vector<KeyFrame*> mvpCurrentConnectedKFs;
        std::vector<MapPoint*> mvpCurrentMatchedPoints;
        std::vector<MapPoint*> mvpLoopMapPoints;
        cv::Mat mScw;
        g2o::Sim3 mg2oScw;
        double mScale_cw;
        
        long unsigned int mLastLoopKFid;
    };
    
} //namespace ORB_SLAM

#endif /* LoopClosing_hpp */
