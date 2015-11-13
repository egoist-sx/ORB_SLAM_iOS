//
//  Optimizer.hpp
//  ORB_SLAM_iOS
//
//  Created by Xin Sun on 14/10/2015.
//  Copyright © 2015 Xin Sun. All rights reserved.
//

#ifndef Optimizer_hpp
#define Optimizer_hpp

#include "Map.hpp"
#include "MapPoint.hpp"
#include "KeyFrame.hpp"
#include "LoopClosing.hpp"
#include "Frame.hpp"

#include "Thirdparty/g2o/g2o/types/sim3/types_seven_dof_expmap.h"

namespace ORB_SLAM
{
    
    class LoopClosing;
    
    class Optimizer
    {
    public:
        void static BundleAdjustment(const std::vector<KeyFrame*> &vpKF, const std::vector<MapPoint*> &vpMP, int nIterations = 5, bool *pbStopFlag=NULL);
        void static GlobalBundleAdjustemnt(Map* pMap, int nIterations=5, bool *pbStopFlag=NULL);
        void static LocalBundleAdjustment(KeyFrame* pKF, bool *pbStopFlag=NULL);
        int static PoseOptimization(Frame* pFrame);
        
        void static OptimizeEssentialGraph(Map* pMap, KeyFrame* pLoopKF, KeyFrame* pCurKF, g2o::Sim3 &Scurw,
                                           LoopClosing::KeyFrameAndPose &NonCorrectedSim3,
                                           LoopClosing::KeyFrameAndPose &CorrectedSim3,
                                           std::map<KeyFrame*, set<KeyFrame*> > &LoopConnections);
        
        
        static int OptimizeSim3(KeyFrame* pKF1, KeyFrame* pKF2, std::vector<MapPoint *> &vpMatches1, g2o::Sim3 &g2oS12, float th2 = 10);
    };
    
} //namespace ORB_SLAM

#endif /* Optimizer_hpp */
