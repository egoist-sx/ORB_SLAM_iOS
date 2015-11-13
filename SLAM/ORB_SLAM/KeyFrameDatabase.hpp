//
//  KeyFrameDatabase.hpp
//  ORB_SLAM_iOS
//
//  Created by Xin Sun on 14/10/2015.
//  Copyright © 2015 Xin Sun. All rights reserved.
//

#ifndef KeyFrameDatabase_hpp
#define KeyFrameDatabase_hpp

#include <vector>
#include <list>
#include <set>

#include "KeyFrame.hpp"
#include "Frame.hpp"
#include "ORBVocabulary.hpp"

#include<boost/thread.hpp>


namespace ORB_SLAM
{
    
    class KeyFrame;
    class Frame;
    
    class KeyFrameDatabase
    {
    public:
        
        KeyFrameDatabase(const ORBVocabulary &voc);
        KeyFrameDatabase();
        
        void add(KeyFrame* pKF);
        
        void erase(KeyFrame* pKF);
        
        void clear();
        
        // Loop Detection
        std::vector<KeyFrame *> DetectLoopCandidates(KeyFrame* pKF, float minScore);
        
        // Relocalisation
        std::vector<KeyFrame*> DetectRelocalisationCandidates(Frame* F);
        
    protected:
        
        // Associated vocabulary
        const ORBVocabulary* mpVoc;
        
        // Inverted file
        std::vector<list<KeyFrame*> > mvInvertedFile;
        
        // Mutex
        boost::mutex mMutex;
    };
    
} //namespace ORB_SLAM

#endif /* KeyFrameDatabase_hpp */
