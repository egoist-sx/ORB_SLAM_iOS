//
//  Map.cpp
//  ORB_SLAM_iOS
//
//  Created by Xin Sun on 14/10/2015.
//  Copyright © 2015 Xin Sun. All rights reserved.
//

#include "Map.hpp"

namespace ORB_SLAM
{
    
    Map::Map()
    {
        mbMapUpdated= false;
        mnMaxKFid = 0;
    }
    
    void Map::AddKeyFrame(KeyFrame *pKF)
    {
        boost::mutex::scoped_lock lock(mMutexMap);
        mspKeyFrames.insert(pKF);
        if(pKF->mnId>mnMaxKFid)
            mnMaxKFid=pKF->mnId;
        mbMapUpdated=true;
    }
    
    void Map::AddMapPoint(MapPoint *pMP)
    {
        boost::mutex::scoped_lock lock(mMutexMap);
        mspMapPoints.insert(pMP);
        mbMapUpdated=true;
    }
    
    void Map::EraseMapPoint(MapPoint *pMP)
    {
        boost::mutex::scoped_lock lock(mMutexMap);
        mspMapPoints.erase(pMP);
        mbMapUpdated=true;
    }
    
    void Map::EraseKeyFrame(KeyFrame *pKF)
    {
        boost::mutex::scoped_lock lock(mMutexMap);
        mspKeyFrames.erase(pKF);
        mbMapUpdated=true;
    }
    
    void Map::SetReferenceMapPoints(const vector<MapPoint *> &vpMPs)
    {
        boost::mutex::scoped_lock lock(mMutexMap);
        mvpReferenceMapPoints = vpMPs;
        mbMapUpdated=true;
    }
    
    vector<KeyFrame*> Map::GetAllKeyFrames()
    {
        boost::mutex::scoped_lock lock(mMutexMap);
        return vector<KeyFrame*>(mspKeyFrames.begin(),mspKeyFrames.end());
    }
    
    vector<MapPoint*> Map::GetAllMapPoints()
    {
        boost::mutex::scoped_lock lock(mMutexMap);
        return vector<MapPoint*>(mspMapPoints.begin(),mspMapPoints.end());
    }
    
    int Map::MapPointsInMap()
    {
        boost::mutex::scoped_lock lock(mMutexMap);
        return mspMapPoints.size();
    }
    
    int Map::KeyFramesInMap()
    {
        boost::mutex::scoped_lock lock(mMutexMap);
        return mspKeyFrames.size();
    }
    
    vector<MapPoint*> Map::GetReferenceMapPoints()
    {
        boost::mutex::scoped_lock lock(mMutexMap);
        return mvpReferenceMapPoints;
    }
    
    bool Map::isMapUpdated()
    {
        boost::mutex::scoped_lock lock(mMutexMap);
        return mbMapUpdated;
    }
    
    void Map::SetFlagAfterBA()
    {
        boost::mutex::scoped_lock lock(mMutexMap);
        mbMapUpdated=true;
        
    }
    
    void Map::ResetUpdated()
    {
        boost::mutex::scoped_lock lock(mMutexMap);
        mbMapUpdated=false;
    }
    
    unsigned int Map::GetMaxKFid()
    {
        boost::mutex::scoped_lock lock(mMutexMap);
        return mnMaxKFid;
    }
    
    void Map::clear()
    {
        for(set<MapPoint*>::iterator sit=mspMapPoints.begin(), send=mspMapPoints.end(); sit!=send; sit++)
            delete *sit;
        
        for(set<KeyFrame*>::iterator sit=mspKeyFrames.begin(), send=mspKeyFrames.end(); sit!=send; sit++)
            delete *sit;
        
        mspMapPoints.clear();
        mspKeyFrames.clear();
        mnMaxKFid = 0;
        mvpReferenceMapPoints.clear();
    }
    
} //namespace ORB_SLAM