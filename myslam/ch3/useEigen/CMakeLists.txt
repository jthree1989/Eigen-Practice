cmake_minimum_required( VERSION 2.8 )
project( useEigen )

set( CMAKE_BUILD_TYPE "Release" )
# 将编译器优化程度调到最高
set( CMAKE_CXX_FLAGS "-O3" )

# 添加Eigen头文件
include_directories( "/usr/include/eigen3" )
add_executable( eigenMatrix eigenMatrix.cpp )
add_executable( eigenTutorial eigenTutorial.cpp)
add_executable( eigenProblemSet1_1 eigenProblemSet1_1.cpp)
add_executable( eigenProblemSet1_2 eigenProblemSet1_2.cpp)
add_executable( eigenProblemSet1_3 eigenProblemSet1_3.cpp)