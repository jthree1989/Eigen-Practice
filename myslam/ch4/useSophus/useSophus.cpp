#include <iostream>
#include <cmath>
using namespace std; 

#include <Eigen/Core>
#include <Eigen/Geometry>
using namespace Eigen;

#include "sophus/so3.h"
#include "sophus/se3.h"
using namespace Sophus;

int main( int argc, char** argv )
{
    // Construct rotation matrix
    Matrix3d R = AngleAxisd(M_PI/2, Vector3d(0,0,1)).toRotationMatrix();
    cout << "Rotation matrix is \n" << R << endl;
    // Construct special orthogonal group
    SO3 SO3_R(R);               // From rotation matrix
    SO3 SO3_v( 0, 0, M_PI/2 );  // From rotation angles(X-Y-Z)
    Quaterniond q(R);    	// From quaternion
    SO3 SO3_q( q );
    // Output SO(3)
    cout<<"SO(3) from matrix: "<<SO3_R<<endl;
    cout<<"SO(3) from vector: "<<SO3_v<<endl;
    cout<<"SO(3) from quaternion :"<<SO3_q<<endl;
    
    // Get Lie algrebra by log
    Vector3d so3 = SO3_R.log();	// based on Atan-based log
    cout<<"so3 = "<<so3.transpose()<<endl;
    
    // hat convert so3 to skew symmetric matrix
    cout<<"so3 hat=\n"<<SO3::hat(so3)<<endl;
    cout << "Rotation matrix from so(3) is \n" << SO3::exp(so3).matrix() << endl;
    
    // Respectively, vee convert skew symmetric matrix to so(3)
    cout<<"so3 hat vee= "<<SO3::vee( Sophus::SO3::hat(so3) ).transpose()<<endl; 
    
    // Incremental disturbance model update
    Eigen::Vector3d update_so3(1e-4, 0, 0); //disturbance update
    SO3 SO3_updated = SO3::exp(update_so3) * SO3_R;
    cout<<"SO3 updated = "<<SO3_updated.matrix()<<endl;
    
    cout<<"************SE(3)*************"<<endl;
    Vector3d t(1,0,0);           	// Translate 1 along X-axis
    Sophus::SE3 SE3_Rt(R, t);           // Construct SE(3) from R,t
    Sophus::SE3 SE3_qt(q,t);            // Construct SE(3) from q,t
    cout<<"SE3 from R,t= "<<endl<<SE3_Rt<<endl;
    cout<<"SE3 from q,t= "<<endl<<SE3_qt<<endl;

    // se(3) is 6-vector, typedef for simplity
    typedef Matrix<double,6,1> Vector6d;
    Vector6d se3 = SE3_Rt.log();
    cout<<"se3 = "<<se3.transpose()<<endl;

    // 观察输出，会发现在Sophus中，se(3)的平移在前，旋转在后.
    // 同样的，有hat和vee两个算符
    cout<<"se3 hat = "<<endl<<SE3::hat(se3)<<endl;
    cout<<"se3 hat vee = "<<SE3::vee( SE3::hat(se3) )<<endl;
    
    // 最后，演示一下更新
    Vector6d update_se3; //更新量
    update_se3.setZero();
    update_se3(0,0) = 1e-4d;
    Sophus::SE3 SE3_updated = Sophus::SE3::exp(update_se3)*SE3_Rt;
    cout<<"SE3 updated = "<<endl<<SE3_updated.matrix()<<endl;
    
    return 0;
}