cmake_minimum_required(VERSION 2.8)
project(imageBasics)

# Support C++11 standard
set(OpenCV_DIR "/usr/local/opencv3/share/OpenCV")
set(CMAKE_CXX_FLAGS -"-std=c++11")
# Find OpenCV3
find_package(OpenCV 4 REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(${CMAKE_PROJECT_NAME} imageBasics.cpp)
target_link_libraries(${CMAKE_PROJECT_NAME} ${OpenCV_LIBS})