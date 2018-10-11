#include <iostream>

// Eigen 核心部分
#include <Eigen/Core>
// Eigen/Geometry 模块提供了各种旋转和平移的表示
#include <Eigen/Geometry>

using namespace std;
using namespace Eigen;

int main(int argc, char** argv)
{
  // Construct a rotation matrix
  Matrix3d rotationMatrix = Matrix3d::Identity();
  cout << "rotationMatrix:\n" << rotationMatrix << endl;
  
  // Construct a axis-angle vector
  // AngleAxisd rotationVector(M_PI/4, Vector3d(0, 0, 1));
  AngleAxisd rotationVector(M_PI/4, Vector3d::UnitZ());
  cout.precision(3);
  cout << "rotationVector:\n" << rotationVector.matrix() << endl;
  
  // Convert axis-angle vector to rotation matrix
  rotationMatrix = rotationVector.toRotationMatrix();
  cout << "rotationMatrix:\n" << rotationMatrix << endl;
  
  // Rotate vector with axis-angle vector 
  Vector3d v(1, 0, 0);
  Vector3d rotatedVector = rotationVector * v;
  cout << "rotated vector:\n" << rotatedVector.transpose() << endl;
  
  // Rotate vector with rotation matrix
  Vector3d rotatedVector2 = rotationMatrix * v;
  cout << "rotated vector with matrix:\n" << rotatedVector2.transpose()<<endl;
  
  // 
  Vector3d eulerAngles = rotationMatrix.eulerAngles(2,1,0);	// Z-Y-X, i.e.roll-pitch-yaw against fixed axis
  cout << "roll pitch yaw angles:\n" << eulerAngles.transpose() << endl;
  
  // Construct transform matrix
  Isometry3d T = Isometry3d::Identity();
  T.rotate(rotationVector);
  T.pretranslate(Vector3d(1, 3, 4));
  cout << "transform matrix:\n" << T.matrix() << endl;
  
  // Transform vector with transform matrix
  Vector3d transformedVector = T * v;
  cout << "transformed vector:\n" << transformedVector.transpose() << endl;
  
  // as for affine and projective transformation, use Affine3d and Projective3d
  
  //
  Quaterniond q(rotationVector);
  cout << "quaternion:\n" << q.coeffs() << endl;
  Vector3d qRotatedVector = q * v;
  cout << "quanternion rotation:\n" << qRotatedVector << endl; 
  return 0;
}