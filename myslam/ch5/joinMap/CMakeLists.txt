cmake_minimum_required(VERSION 2.8)
project(joinMap)
# Support C++11 standard
set(CMAKE_CXX_FLAGS -std=c++11)
# Find OpenCV library
find_package(OpenCV 4 REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
# Find PCL library
find_package(PCL REQUIRED common io)
include_directories(${PCL_INCLUDE_DIRS})
add_definitions(${PCL_DEFINITIONS})
# Find Eigen library
include_directories( "/usr/include/eigen3" )

add_executable(${CMAKE_PROJECT_NAME} joinMap.cpp)
target_link_libraries(${CMAKE_PROJECT_NAME}
		      ${OpenCV_LIBS}
		      ${PCL_LIBRARIES}
)

file(COPY ${CMAKE_SOURCE_DIR}/pose.txt 
	  ${CMAKE_SOURCE_DIR}/color
	  ${CMAKE_SOURCE_DIR}/depth
     DESTINATION ${CMAKE_BINARY_DIR}
    )