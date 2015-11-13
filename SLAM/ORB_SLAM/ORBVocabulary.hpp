//
//  ORBVocabulary.hpp
//  ORB_SLAM_iOS
//
//  Created by Xin Sun on 14/10/2015.
//  Copyright © 2015 Xin Sun. All rights reserved.
//

#ifndef ORBVocabulary_hpp
#define ORBVocabulary_hpp

#include "Thirdparty/DBoW2/DBoW2/FORB.h"
#include "Thirdparty/DBoW2/DBoW2/TemplatedVocabulary.h"

namespace ORB_SLAM
{
    
    typedef DBoW2::TemplatedVocabulary<DBoW2::FORB::TDescriptor, DBoW2::FORB>
    ORBVocabulary;
    
} //namespace ORB_SLAM

#endif /* ORBVocabulary_hpp */
