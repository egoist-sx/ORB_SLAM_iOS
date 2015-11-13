//
//  Map.hpp
//  ORB_SLAM_iOS
//
//  Created by Xin Sun on 14/10/2015.
//  Copyright © 2015 Xin Sun. All rights reserved.
//

#ifndef Map_hpp
#define Map_hpp

#include "MapPoint.hpp"
#include "KeyFrame.hpp"
#include <set>

#include<boost/thread.hpp>

namespace ORB_SLAM
{
    
    class MapPoint;
    class KeyFrame;
    
    class Map
    {
    public:
        Map();
        
        void AddKeyFrame(KeyFrame* pKF);
        void AddMapPoint(MapPoint* pMP);
        void EraseMapPoint(MapPoint* pMP);
        void EraseKeyFrame(KeyFrame* pKF);
        void SetCurrentCameraPose(cv::Mat Tcw);
        void SetReferenceKeyFrames(const std::vector<KeyFrame*> &vpKFs);
        void SetReferenceMapPoints(const std::vector<MapPoint*> &vpMPs);
        
        std::vector<KeyFrame*> GetAllKeyFrames();
        std::vector<MapPoint*> GetAllMapPoints();
        cv::Mat GetCameraPose();
        std::vector<KeyFrame*> GetReferenceKeyFrames();
        std::vector<MapPoint*> GetReferenceMapPoints();
        
        int MapPointsInMap();
        int KeyFramesInMap();
        
        void SetFlagAfterBA();
        bool isMapUpdated();
        void ResetUpdated();
        
        unsigned int GetMaxKFid();
        
        void clear();
        
    protected:
        std::set<MapPoint*> mspMapPoints;
        std::set<KeyFrame*> mspKeyFrames;
        
        std::vector<MapPoint*> mvpReferenceMapPoints;
        
        unsigned int mnMaxKFid;
        
        boost::mutex mMutexMap;
        bool mbMapUpdated;
    };
    
} //namespace ORB_SLAM

#endif /* Map_hpp */
