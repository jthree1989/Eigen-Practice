#include <iostream>
#include <opencv2/core/core.hpp>
#include <ceres/ceres.h>
#include <chrono>

using namespace std;
using namespace cv;
using namespace ceres;
using namespace chrono;

// Define cost function
class CURVE_FITTING_COST
{
public:
  CURVE_FITTING_COST(double x, double y):_x(x),_y(y){}
  template<typename T>
  bool operator()(const T* abc, T* residual) const
  {
    residual[0] = T(_y) - exp(abc[0] * T(_x) * T(_x) + abc[1] * T(_x) + abc[2]);
    return true;
  }
private:
  const double _x, _y;
};

int main(int argc, char** argv)
{
  double a=1.0, b=2.0, c=1.0;		// Real coefficient
  const int N = 100;			// Sample points
  double wSigma = 1.0;			// Noise value
  RNG rng;				// OpenCV random number generator
  double abc[3] = {0, 0, 0};		// Estimation of abc values
  
  vector<double> xData, yData;		// x,y xData
  
  cout << "Generating data:" << endl;
  for(int i = 0; i < N; i++)
  {
    double x = i / 100.0;
    xData.push_back(x);
    yData.push_back(
      exp(a * x * x + b * x + c) + rng.gaussian(wSigma)
    );
    cout << xData[i] << "	" << yData[i] << endl;
  }
  
  // Construct the Least Square problem
  Problem problem;
  for(size_t i = 0; i < N ; i++)
  {
    problem.AddResidualBlock(
      new AutoDiffCostFunction<CURVE_FITTING_COST, 1, 3>(
	new CURVE_FITTING_COST(xData[i], yData[i])
      ),
      nullptr,
      abc
    );
  }
  
  // Configrtion of solver
  Solver::Options options;
  options.linear_solver_type = ceres::DENSE_QR;	// QR method
  options.minimizer_progress_to_stdout = true;	// Print to cout
  
  Solver::Summary summary;			// Information of optimization 
  steady_clock::time_point t1 = steady_clock::now();
  Solve(options, &problem, &summary);
  steady_clock::time_point t2 = steady_clock::now();
  duration<double> usedTime = duration_cast<duration<double>>(t2 -t1);
  cout << "Solve time cost = " << usedTime.count() << " seconds." << endl;
  
  // Print result
  cout << summary.BriefReport() << endl;
  cout << "Estimated ,b,c = ";
  for(auto a: abc) cout << a << " ";
  cout << endl;
  
  return 0;
}