#include <vector>
#include <fstream>
#include <iostream>

#include <boost/format.hpp>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <Eigen/Core>
#include <Eigen/Geometry>

#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>

using namespace std;
using namespace cv;
using namespace Eigen;
using namespace boost;
using namespace pcl;

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
    boost::format fmt("./%s/%d.%s");
    colorImages.push_back(imread((fmt%"color"%(i+1)%"png").str()));
    depthImages.push_back(imread((fmt%"depth"%(i+1)%"pgm").str(), -1)); // Read raw data with second para(-1)
    
    double data[7] = {0};
    for(auto& d:data)	// Use reference not copy value  
      fin >> d;
    
    Quaterniond q(data[6],data[3], data[4], data[5]);
    Isometry3d T(q);
    T.pretranslate(Vector3d(data[0], data[1], data[2]));
    poses.push_back(T);
  }
  
  // Intrinsic parameters
  double cx = 325.5;
  double cy = 253.5;
  double fx = 518.0;
  double fy = 519.0;
  double depthScale = 1000.0; 
  
  //
  cout << "Try to convert to point cloud..." << endl;
  typedef PointXYZRGB PointT;
  typedef PointCloud<PointT> PointCloud;
  // Construct a new point cloud
  PointCloud::Ptr pointCloud(new PointCloud);
  for(size_t i = 0; i < 5; i++){
    cout << "Convering image: " << i+1 << endl;
    Mat color = colorImages[i];
    Mat depth = depthImages[i];
    Isometry3d T = poses[i];
    // Traverse color image and depth image
    for(size_t v = 0; v < color.rows; v++){
      for(size_t u =0; u < color.cols; u++){
	uint16_t d = depth.ptr<uint16_t>(v)[u]; // Depth value
	if(!d) continue; // Filter out empty depth point
      
	Vector3d point;
	point[2] = double(d)/depthScale;
	point[0] = (u - cx) * point[2] / fx;
	point[1] = (v - cy) * point[2] / fy;
	Vector3d worldPoint = T * point;
	
	PointT p;
	p.x = worldPoint[0];
	p.y = worldPoint[1];
	p.z = worldPoint[2];
	p.b = color.data[v * color.step + u * color.channels()];
	p.g = color.data[v * color.step + u * color.channels() + 1];
	p.r = color.data[v * color.step + u * color.channels() + 2];
	pointCloud->points.push_back(p);
      }
    }
  }  
  
  pointCloud->is_dense = false;
  cout << "There are " << pointCloud->size() << " points in point cloud." << endl;
  pcl::io::savePCDFileBinary("map.pcd", *pointCloud);
  
  return 0;
  
}