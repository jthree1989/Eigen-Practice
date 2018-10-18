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
  for(size_t y = 0; y < image.rows; y++){
    for(size_t x = 0; x < image.cols; x++){
      // Get pixel at (x,y)
      // Use Mat::ptr to the row pointer
      unsigned char* rowPtr = image.ptr<unsigned char>(y);
      unsigned char* dataPtr = &rowPtr[x * image.channels()];
      // Output each element in channels
      for(auto c = 0; c != image.channels(); c++){
	auto data = dataPtr[c];
      }
    }
  }
  chrono::steady_clock::time_point t2 = chrono::steady_clock::now();
  chrono::duration<double> usedTime = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
  cout << "Time to traverse image : " << usedTime.count() << " s." << endl;
  
  // The truth about copy Mat
  // Assignment directly doesn't copy data
  Mat anotherImage = image;
  // Modifying antherImage will change the image
  anotherImage(Rect(0, 0, 100, 100)).setTo(0); // Set the pixels in left-up corner(100 * 100) to 0
  imshow("image", image);
  waitKey(0);
  
  // Use clone to copy data
  Mat cloneImage = image.clone();
  cloneImage(Rect(0 ,0, 100, 100)).setTo(255);
  imshow("image", image);
  imshow("cloneImage", cloneImage);
  waitKey(0);
  
  destroyAllWindows();
  
  return 0;
}