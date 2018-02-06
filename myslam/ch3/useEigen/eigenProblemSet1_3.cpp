/**
* Problem:
* Suppose we have a large matrix A, which is lager than 3x3.
* How to extract the top left corner(3x3) of A, and set it identity matrix I(3x3)?
*/
#include <iostream>
#include <stdint.h>
// Include Matrix and Array classes, basic linear algebra (including triangular and selfadjoint products), array manipulation
#include <Eigen/Core>
using namespace std;
using namespace Eigen;
int main()
{
	// Construct a random large matrix A, which is larger than 3x3
	uint32_t matrixSize = 0;
	cout << "Please input a number larger than 3:"<<endl;
	while(cin >> matrixSize && matrixSize <= 3);
	MatrixXd A = MatrixXd::Random(matrixSize,matrixSize);
	// Print out A
	cout << "Matrix A: "<< endl << A << endl;
	// Extract the top left corner(3x3) of A, and set it to I(3x3)
	Matrix3d A_topleft = A.block<3,3>(0,0);
	cout << "The top left corner(3x3) of A: " << endl << A_topleft << endl;
	cout << "Set top left corner(3x3) of A to identity matrix..." << endl;
	A.block<3,3>(0,0) = Matrix3d::Identity();
	// Print out modified A
	cout << "Modified matrix A: "<< endl << A << endl;
	return 0;
}
