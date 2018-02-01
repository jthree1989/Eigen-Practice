/**
* Problem:
* Find the eigenvalues and eigen vectors of
*		10	-9
* A = 		
*		4	-2
*		
* 		3	4	-1
* B =  -1  -2	 1
*		3	9	0
*/
#include <iostream>
// Include Matrix and Array classes, basic linear algebra (including triangular and selfadjoint products), array manipulation
#include <Eigen/Core>
// Include eigenvalue, eigenvector decompositions (EigenSolver, SelfAdjointEigenSolver, ComplexEigenSolver)
#include <Eigen/Eigenvalues>
using namespace Eigen;
using namespace std;
int main(int argc, char ** argv)
{
	Matrix2d A;
	Matrix3d B;
	// Construct matrix A and B
	A << 10, -9,
		  4, -2;
	
	B << 3,  4, -1,
		-1, -2,	 1,
		 3,	 9,	 0;
	// Find eigenvalues and eigen vectors of A and B
	EigenSolver<MatrixXd> eigenSolver_A(A), eigenSolver_B(B);	
	// Print out the results
	cout << "The eigen values of A is " << endl << eigenSolver_A.eigenvalues() << endl;
	cout << "The eigen vectors of A is " << endl << eigenSolver_A.eigenvectors() << endl;
	cout << "The eigen values of B is " << endl << eigenSolver_B.eigenvalues() << endl;
	cout << "The eigen vectors of B is " << endl << eigenSolver_B.eigenvectors() << endl;

	return 0;
}