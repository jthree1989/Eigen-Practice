#include <iostream>
#include <chrono>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
  // Read given image
  Mat image;
  image = imread(argv[1]);
  // Check if image is read successfully
  if(nullptr == image.data){
    cerr << "File " << argv[1] << " doesn't exist." << endl;
    return 0;
  }
  // Output some basic infomation about image
  cout << "Width of image: " << image.cols 
       << ", height of image: " << image.rows 
       << ", channels of image: " << image.channels() << endl;
  imshow("image", image);
  waitKey(0);
  
  // Check the type of image
  if(CV_8UC1 != image.type() && CV_8UC3 != image.type())
  {
    cout << "Please input a color image or a grayscale image." << endl;
    return 0;
  }
  
  // Traverse image, use std::chrono to keep time
  chrono::steady_clock::time_point t1 = chrono::steady_clock::now();

  return 0;
}