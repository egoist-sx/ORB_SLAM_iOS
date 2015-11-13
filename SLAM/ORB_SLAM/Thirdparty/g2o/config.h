//
//  config.h
//  ORB_SLAM_iOS
//
//  Created by Xin Sun on 14/10/2015.
//  Copyright © 2015 Xin Sun. All rights reserved.
//

#ifndef config_h
#define config_h

//#define G2O_HAVE_OPENGL 1
//#define G2O_OPENGL_FOUND 1
/* #undef G2O_OPENMP */
#define G2O_SHARED_LIBS 1
#define G2O_LGPL_SHARED_LIBS 1

// available sparse matrix libraries
#define G2O_HAVE_CHOLMOD 0
#define G2O_HAVE_CSPARSE 0

//#define G2O_CXX_COMPILER "GNU /usr/bin/c++"

// give a warning if Eigen defaults to row-major matrices.
// We internally assume column-major matrices throughout the code.
#ifdef EIGEN_DEFAULT_TO_ROW_MAJOR
#  error "g2o requires column major Eigen matrices (see http://eigen.tuxfamily.org/bz/show_bug.cgi?id=422)"
#endif

#endif /* config_h */
