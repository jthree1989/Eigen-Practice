/**
* Problem:
* Find the eigen values and eigen vectors of A and of the stated power of A.
*
* 		-1	-2	-2
* A = 	 1	 2	 1	, and A^25;
*		-1	-1	 0
*/
#include <iostream>
#include <ctime>

// Include Matrix and Array classes, basic linear algebra (including triangular and selfadjoint products), array manipulation
#include <Eigen/Core>
// Include eigenvalue, eigenvector decompositions (EigenSolver, SelfAdjointEigenSolver, ComplexEigenSolver)
#include <Eigen/Eigenvalues>
// This module aims to provide various methods for the computation of matrix functions.
#include <unsupported/Eigen/MatrixFunctions>

using namespace std;
using namespace Eigen;

int main(int argc, char ** argv)
{
	// Construct Matrix
	Matrix3d A;
	A << -1, -2, -2,
		  1,  2,  1,
		 -1, -1,  0;
	
	// Compute eigen values and eigen vectors of A^25
	//1. Method One: direct compute A^25, then compute eigen values and vectors.
	clock_t  time_stt = clock();
	Matrix3d A25 = A.pow(25);
	EigenSolver<Matrix3d> eigenSolver_A25(A25);
	EigenSolver<Matrix3d>::EigenvalueType eigenValues_A25 = eigenSolver_A25.eigenvalues();
	EigenSolver<Matrix3d>::EigenvectorsType eigenVectors_A25 = eigenSolver_A25.eigenvectors();
	cout <<"Time use in Method One is " << 1000* (clock() - time_stt)/(double)CLOCKS_PER_SEC << "ms"<< endl;
	//2. Method Two: use some conclusion in Linear Algreba.
	time_stt = clock();
	EigenSolver<Matrix3d> eigenSolver_A(A);
	EigenSolver<Matrix3d>::EigenvalueType eigenValues_A = eigenSolver_A.eigenvalues();
	EigenSolver<Matrix3d>::EigenvectorsType eigenVectors_A = eigenSolver_A.eigenvectors();
	EigenSolver<Matrix3d>::EigenvalueType eigenValues_A25_2 = eigenSolver_A.eigenvalues();
	for(int i = 0; i < eigenVectors_A.rows(); i++)
		eigenValues_A25_2.col(0)[i] = pow(eigenValues_A.col(0)[i],25);
	cout <<"Time use in Method Two is " << 1000* (clock() - time_stt)/(double)CLOCKS_PER_SEC << "ms"<< endl;
	// Print results
	cout << "The eigen values of A25 is " << endl << eigenValues_A25 << endl;
	cout << "The eigen vectors of A25 is " << endl << eigenVectors_A25  << endl;
	cout << "The eigen values of A25_2 is " << endl << eigenValues_A25_2 << endl;
	cout << "The eigen vectors of A25_2 is " << endl << eigenVectors_A  << endl;

	return 0;
}
