#include "dquat2mat.h"
#include <iostream>
namespace g2o {
  namespace internal {
    using namespace std;

      void  compute_dq_dR_w ( Eigen::Matrix<double, 3 , 9 >&  dq_dR_w , const double&  qw , const double&  r00 , const double&  r10 , const double&  r20 , const double&  r01 , const double&  r11 , const double&  r21 , const double&  r02 , const double&  r12 , const double&  r22 ) {
          (void) r00;
          (void) r11;
          (void) r22;
          double  _aux1 = 1/pow(qw,3) ;
          double  _aux2 = -0.03125*(r21-r12)*_aux1 ;
          double  _aux3 = 1/qw ;
          double  _aux4 = 0.25*_aux3 ;
          double  _aux5 = -0.25*_aux3 ;
          double  _aux6 = 0.03125*(r20-r02)*_aux1 ;
          double  _aux7 = -0.03125*(r10-r01)*_aux1 ;
          dq_dR_w ( 0 , 0 ) = _aux2 ;
          dq_dR_w ( 0 , 1 ) = 0 ;
          dq_dR_w ( 0 , 2 ) = 0 ;
          dq_dR_w ( 0 , 3 ) = 0 ;
          dq_dR_w ( 0 , 4 ) = _aux2 ;
          dq_dR_w ( 0 , 5 ) = _aux4 ;
          dq_dR_w ( 0 , 6 ) = 0 ;
          dq_dR_w ( 0 , 7 ) = _aux5 ;
          dq_dR_w ( 0 , 8 ) = _aux2 ;
          dq_dR_w ( 1 , 0 ) = _aux6 ;
          dq_dR_w ( 1 , 1 ) = 0 ;
          dq_dR_w ( 1 , 2 ) = _aux5 ;
          dq_dR_w ( 1 , 3 ) = 0 ;
          dq_dR_w ( 1 , 4 ) = _aux6 ;
          dq_dR_w ( 1 , 5 ) = 0 ;
          dq_dR_w ( 1 , 6 ) = _aux4 ;
          dq_dR_w ( 1 , 7 ) = 0 ;
          dq_dR_w ( 1 , 8 ) = _aux6 ;
          dq_dR_w ( 2 , 0 ) = _aux7 ;
          dq_dR_w ( 2 , 1 ) = _aux4 ;
          dq_dR_w ( 2 , 2 ) = 0 ;
          dq_dR_w ( 2 , 3 ) = _aux5 ;
          dq_dR_w ( 2 , 4 ) = _aux7 ;
          dq_dR_w ( 2 , 5 ) = 0 ;
          dq_dR_w ( 2 , 6 ) = 0 ;
          dq_dR_w ( 2 , 7 ) = 0 ;
          dq_dR_w ( 2 , 8 ) = _aux7 ;
      }
      void  compute_dq_dR_x ( Eigen::Matrix<double, 3 , 9 >&  dq_dR_x , const double&  qx , const double&  r00 , const double&  r10 , const double&  r20 , const double&  r01 , const double&  r11 , const double&  r21 , const double&  r02 , const double&  r12 , const double&  r22 ) {
          (void) r00;
          (void) r11;
          (void) r21;
          (void) r12;
          (void) r22;
          double  _aux1 = 1/qx ;
          double  _aux2 = -0.125*_aux1 ;
          double  _aux3 = 1/pow(qx,3) ;
          double  _aux4 = r10+r01 ;
          double  _aux5 = 0.25*_aux1 ;
          double  _aux6 = 0.03125*_aux3*_aux4 ;
          double  _aux7 = r20+r02 ;
          double  _aux8 = 0.03125*_aux3*_aux7 ;
          dq_dR_x ( 0 , 0 ) = 0.125*_aux1 ;
          dq_dR_x ( 0 , 1 ) = 0 ;
          dq_dR_x ( 0 , 2 ) = 0 ;
          dq_dR_x ( 0 , 3 ) = 0 ;
          dq_dR_x ( 0 , 4 ) = _aux2 ;
          dq_dR_x ( 0 , 5 ) = 0 ;
          dq_dR_x ( 0 , 6 ) = 0 ;
          dq_dR_x ( 0 , 7 ) = 0 ;
          dq_dR_x ( 0 , 8 ) = _aux2 ;
          dq_dR_x ( 1 , 0 ) = -0.03125*_aux3*_aux4 ;
          dq_dR_x ( 1 , 1 ) = _aux5 ;
          dq_dR_x ( 1 , 2 ) = 0 ;
          dq_dR_x ( 1 , 3 ) = _aux5 ;
          dq_dR_x ( 1 , 4 ) = _aux6 ;
          dq_dR_x ( 1 , 5 ) = 0 ;
          dq_dR_x ( 1 , 6 ) = 0 ;
          dq_dR_x ( 1 , 7 ) = 0 ;
          dq_dR_x ( 1 , 8 ) = _aux6 ;
          dq_dR_x ( 2 , 0 ) = -0.03125*_aux3*_aux7 ;
          dq_dR_x ( 2 , 1 ) = 0 ;
          dq_dR_x ( 2 , 2 ) = _aux5 ;
          dq_dR_x ( 2 , 3 ) = 0 ;
          dq_dR_x ( 2 , 4 ) = _aux8 ;
          dq_dR_x ( 2 , 5 ) = 0 ;
          dq_dR_x ( 2 , 6 ) = _aux5 ;
          dq_dR_x ( 2 , 7 ) = 0 ;
          dq_dR_x ( 2 , 8 ) = _aux8 ;
      }
      void  compute_dq_dR_y ( Eigen::Matrix<double, 3 , 9 >&  dq_dR_y , const double&  qy , const double&  r00 , const double&  r10 , const double&  r20 , const double&  r01 , const double&  r11 , const double&  r21 , const double&  r02 , const double&  r12 , const double&  r22 ) {
          (void) r00;
          (void) r20;
          (void) r11;
          (void) r02;
          (void) r22;
          double  _aux1 = 1/pow(qy,3) ;
          double  _aux2 = r10+r01 ;
          double  _aux3 = 0.03125*_aux1*_aux2 ;
          double  _aux4 = 1/qy ;
          double  _aux5 = 0.25*_aux4 ;
          double  _aux6 = -0.125*_aux4 ;
          double  _aux7 = r21+r12 ;
          double  _aux8 = 0.03125*_aux1*_aux7 ;
          dq_dR_y ( 0 , 0 ) = _aux3 ;
          dq_dR_y ( 0 , 1 ) = _aux5 ;
          dq_dR_y ( 0 , 2 ) = 0 ;
          dq_dR_y ( 0 , 3 ) = _aux5 ;
          dq_dR_y ( 0 , 4 ) = -0.03125*_aux1*_aux2 ;
          dq_dR_y ( 0 , 5 ) = 0 ;
          dq_dR_y ( 0 , 6 ) = 0 ;
          dq_dR_y ( 0 , 7 ) = 0 ;
          dq_dR_y ( 0 , 8 ) = _aux3 ;
          dq_dR_y ( 1 , 0 ) = _aux6 ;
          dq_dR_y ( 1 , 1 ) = 0 ;
          dq_dR_y ( 1 , 2 ) = 0 ;
          dq_dR_y ( 1 , 3 ) = 0 ;
          dq_dR_y ( 1 , 4 ) = 0.125*_aux4 ;
          dq_dR_y ( 1 , 5 ) = 0 ;
          dq_dR_y ( 1 , 6 ) = 0 ;
          dq_dR_y ( 1 , 7 ) = 0 ;
          dq_dR_y ( 1 , 8 ) = _aux6 ;
          dq_dR_y ( 2 , 0 ) = _aux8 ;
          dq_dR_y ( 2 , 1 ) = 0 ;
          dq_dR_y ( 2 , 2 ) = 0 ;
          dq_dR_y ( 2 , 3 ) = 0 ;
          dq_dR_y ( 2 , 4 ) = -0.03125*_aux1*_aux7 ;
          dq_dR_y ( 2 , 5 ) = _aux5 ;
          dq_dR_y ( 2 , 6 ) = 0 ;
          dq_dR_y ( 2 , 7 ) = _aux5 ;
          dq_dR_y ( 2 , 8 ) = _aux8 ;
      }
      void  compute_dq_dR_z ( Eigen::Matrix<double, 3 , 9 >&  dq_dR_z , const double&  qz , const double&  r00 , const double&  r10 , const double&  r20 , const double&  r01 , const double&  r11 , const double&  r21 , const double&  r02 , const double&  r12 , const double&  r22 ) {
          (void) r00;
          (void) r10;
          (void) r01;
          (void) r11;
          (void) r22;
          double  _aux1 = 1/pow(qz,3) ;
          double  _aux2 = r20+r02 ;
          double  _aux3 = 0.03125*_aux1*_aux2 ;
          double  _aux4 = 1/qz ;
          double  _aux5 = 0.25*_aux4 ;
          double  _aux6 = r21+r12 ;
          double  _aux7 = 0.03125*_aux1*_aux6 ;
          double  _aux8 = -0.125*_aux4 ;
          dq_dR_z ( 0 , 0 ) = _aux3 ;
          dq_dR_z ( 0 , 1 ) = 0 ;
          dq_dR_z ( 0 , 2 ) = _aux5 ;
          dq_dR_z ( 0 , 3 ) = 0 ;
          dq_dR_z ( 0 , 4 ) = _aux3 ;
          dq_dR_z ( 0 , 5 ) = 0 ;
          dq_dR_z ( 0 , 6 ) = _aux5 ;
          dq_dR_z ( 0 , 7 ) = 0 ;
          dq_dR_z ( 0 , 8 ) = -0.03125*_aux1*_aux2 ;
          dq_dR_z ( 1 , 0 ) = _aux7 ;
          dq_dR_z ( 1 , 1 ) = 0 ;
          dq_dR_z ( 1 , 2 ) = 0 ;
          dq_dR_z ( 1 , 3 ) = 0 ;
          dq_dR_z ( 1 , 4 ) = _aux7 ;
          dq_dR_z ( 1 , 5 ) = _aux5 ;
          dq_dR_z ( 1 , 6 ) = 0 ;
          dq_dR_z ( 1 , 7 ) = _aux5 ;
          dq_dR_z ( 1 , 8 ) = -0.03125*_aux1*_aux6 ;
          dq_dR_z ( 2 , 0 ) = _aux8 ;
          dq_dR_z ( 2 , 1 ) = 0 ;
          dq_dR_z ( 2 , 2 ) = 0 ;
          dq_dR_z ( 2 , 3 ) = 0 ;
          dq_dR_z ( 2 , 4 ) = _aux8 ;
          dq_dR_z ( 2 , 5 ) = 0 ;
          dq_dR_z ( 2 , 6 ) = 0 ;
          dq_dR_z ( 2 , 7 ) = 0 ;
          dq_dR_z ( 2 , 8 ) = 0.125*_aux4 ;
      }
      void  compute_dR_dq ( Eigen::Matrix<double, 9 , 3 >&  dR_dq , const double&  qx , const double&  qy , const double&  qz , const double&  qw ) {
          double  _aux1 = -4*qy ;
          double  _aux2 = -4*qz ;
          double  _aux3 = 1/qw ;
          double  _aux4 = 2*qx*qz ;
          double  _aux5 = -_aux3*(_aux4-2*qw*qy) ;
          double  _aux6 = 2*qy*qz ;
          double  _aux7 = -_aux3*(_aux6-2*qw*qx) ;
          double  _aux8 = -2*pow(qw,2) ; 
          double  _aux9 = _aux8+2*pow(qz,2) ; 
          double  _aux10 = 2*qw*qz ; 
          double  _aux11 = (_aux10+2*qx*qy)*_aux3 ; 
          double  _aux12 = _aux8+2*pow(qy,2) ; 
          double  _aux13 = _aux3*(_aux6+2*qw*qx) ; 
          double  _aux14 = _aux3*(_aux4+2*qw*qy) ; 
          double  _aux15 = -4*qx ; 
          double  _aux16 = _aux8+2*pow(qx,2) ; 
          double  _aux17 = (_aux10-2*qx*qy)*_aux3 ; 
          dR_dq ( 0 , 0 ) = 0 ; 
          dR_dq ( 0 , 1 ) = _aux1 ; 
          dR_dq ( 0 , 2 ) = _aux2 ; 
          dR_dq ( 1 , 0 ) = _aux5 ; 
          dR_dq ( 1 , 1 ) = _aux7 ; 
          dR_dq ( 1 , 2 ) = -_aux3*_aux9 ; 
          dR_dq ( 2 , 0 ) = _aux11 ; 
          dR_dq ( 2 , 1 ) = _aux12*_aux3 ; 
          dR_dq ( 2 , 2 ) = _aux13 ; 
          dR_dq ( 3 , 0 ) = _aux14 ; 
          dR_dq ( 3 , 1 ) = _aux13 ; 
          dR_dq ( 3 , 2 ) = _aux3*_aux9 ; 
          dR_dq ( 4 , 0 ) = _aux15 ; 
          dR_dq ( 4 , 1 ) = 0 ; 
          dR_dq ( 4 , 2 ) = _aux2 ; 
          dR_dq ( 5 , 0 ) = -_aux16*_aux3 ; 
          dR_dq ( 5 , 1 ) = _aux17 ; 
          dR_dq ( 5 , 2 ) = _aux5 ; 
          dR_dq ( 6 , 0 ) = _aux17 ; 
          dR_dq ( 6 , 1 ) = -_aux12*_aux3 ; 
          dR_dq ( 6 , 2 ) = _aux7 ; 
          dR_dq ( 7 , 0 ) = _aux16*_aux3 ; 
          dR_dq ( 7 , 1 ) = _aux11 ; 
          dR_dq ( 7 , 2 ) = _aux14 ; 
          dR_dq ( 8 , 0 ) = _aux15 ; 
          dR_dq ( 8 , 1 ) = _aux1 ; 
          dR_dq ( 8 , 2 ) = 0 ; 
      }

    int _q2m(double& S, double& qw, const double&  r00 , const double&  r10 , const double&  r20 , const double&  r01 , const double&  r11 , const double&  r21 , const double&  r02 , const double&  r12 , const double&  r22 ){
      double tr=r00 + r11 + r22;
      if (tr > 0) { 
	S = sqrt(tr + 1.0) * 2; // S=4*qw 
	qw = 0.25 * S;
	// qx = (r21 - r12) / S;
	// qy = (r02 - r20) / S; 
	// qz = (r10 - r01) / S; 
	return 0;
      } else if ((r00 > r11)&(r00 > r22)) { 
	S = sqrt(1.0 + r00 - r11 - r22) * 2; // S=4*qx 
	qw = (r21 - r12) / S;
	// qx = 0.25 * S;
	// qy = (r01 + r10) / S; 
	// qz = (r02 + r20) / S; 
	return 1;
      } else if (r11 > r22) { 
	S = sqrt(1.0 + r11 - r00 - r22) * 2; // S=4*qy
	qw = (r02 - r20) / S;
	// qx = (r01 + r10) / S; 
	// qy = 0.25 * S;
	// qz = (r12 + r21) / S; 
	return 2;
      } else { 
	S = sqrt(1.0 + r22 - r00 - r11) * 2; // S=4*qz
	qw = (r10 - r01) / S;
	// qx = (r02 + r20) / S;
	// qy = (r12 + r21) / S;
	// qz = 0.25 * S;
	return 3;
      }
    }
    
    void  compute_dq_dR ( Eigen::Matrix<double, 3 , 9 >&  dq_dR , const double&  r11 , const double&  r21 , const double&  r31 , const double&  r12 , const double&  r22 , const double&  r32 , const double&  r13 , const double&  r23 , const double&  r33 ){
      double qw;
      double S;
      int whichCase=_q2m( S, qw, r11 ,  r21 ,  r31 ,  r12 ,  r22 ,  r32 ,  r13 ,  r23 ,  r33 );
      S*=.25;
      switch(whichCase){
      case 0: compute_dq_dR_w(dq_dR, S, r11 ,  r21 ,  r31 ,  r12 ,  r22 ,  r32 ,  r13 ,  r23 ,  r33 ); 
	break;
      case 1: compute_dq_dR_x(dq_dR, S, r11 ,  r21 ,  r31 ,  r12 ,  r22 ,  r32 ,  r13 ,  r23 ,  r33 ); 
	break;
      case 2: compute_dq_dR_y(dq_dR, S, r11 ,  r21 ,  r31 ,  r12 ,  r22 ,  r32 ,  r13 ,  r23 ,  r33 ); 
	break;
      case 3: compute_dq_dR_z(dq_dR, S, r11 ,  r21 ,  r31 ,  r12 ,  r22 ,  r32 ,  r13 ,  r23 ,  r33 ); 
	break;
      }
      if (qw<=0)
	dq_dR *= -1;
    }
  }
}
