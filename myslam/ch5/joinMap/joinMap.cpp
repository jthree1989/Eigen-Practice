#include <vector>
#include <fstream>
#include <iostream>
#include <boost/format.hpp>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <Eigen/Core>
#include <Eigen/Geometry>

using namespace std;
using namespace cv;
using namespace Eigen;
using namespace boost;

int main(int argc, char** argv)
{
  vector<Mat> colorImages, depthImages;
  vector<Isometry3d, aligned_allocator<Isometry3d>> poses;	// Poses of camera
  
  ifstream fin("./pose.txt");
  if(!fin){
    cout << "Please run this code in the directory contains pose.txt." << endl;
    return -1;
  }
  
  for(auto i =0; i < 5; i++){
    boost::format fmt("./%s%d.%s");
    colorImages.push_back(imread((fmt%"color"%(i+1)%"png").str()));
    depthImages.push_back(imread((fmt%"depth"%(i+1)%"png").str(), -1)); // Read raw data with second para(-1)
    
    double data[7] = {0};
    for(auto& d:data)	// Use reference not copy value  
      fin >> d;
    
    Quaterniond q(data[6],data[3], data[4], data[5]);
    Isometry3d T(q);
    T.pretranslate<double>(Vector3d(data[0], data[1], data[2]));
    poses.push_back(T);
  }
  
  
  return 0;
  
}