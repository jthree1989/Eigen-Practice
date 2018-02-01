#include <iostream>
#include <Eigen/Dense>
using namespace Eigen;
using namespace std;
int main()
{
#if 0
  MatrixXd m(2,2);
  m(0,0) = 3;
  m(1,0) = 2.5;
  m(0,1) = -1;
  m(1,1) = m(1,0) + m(0,1);
  std::cout << m << std::endl;
#endif
	MatrixXd m = MatrixXd::Random(3,3);
	MatrixXd constant = MatrixXd::Constant(3,3,1.2);
	m = (m + constant) * 50;
	cout << "constant = " << endl << constant << endl;
	cout << "m =" << endl << m << endl;
	VectorXd v(3);
  	v << 1, 2, 3;
  	cout << "m * v =" << endl << m * v << endl;
}

