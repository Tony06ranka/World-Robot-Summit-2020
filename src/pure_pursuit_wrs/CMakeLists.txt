cmake_minimum_required(VERSION 2.8.3)
project(pure_pursuit_wrs)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  std_msgs
  nav_msgs
  roscpp
  tf
)

catkin_package(
  INCLUDE_DIRS include 
  CATKIN_DEPENDS geometry_msgs roscpp std_msgs tf nav_msgs
# DEPENDS system_lib
)


include_directories(
  include 
  ${catkin_INCLUDE_DIRS}
)

add_executable(pure_pursuit_wrs_node src/pure_pursuit_wrs_node.cpp src/pure_pursuit_wrs.cpp)
target_link_libraries(pure_pursuit_wrs_node ${catkin_LIBRARIES})
