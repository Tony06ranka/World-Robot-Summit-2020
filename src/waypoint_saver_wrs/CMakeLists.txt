cmake_minimum_required(VERSION 2.8.3)
project(waypoint_saver_wrs)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  roscpp
  tf
)

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES waypoint_saver_wrs
  CATKIN_DEPENDS geometry_msgs roscpp tf 
#  DEPENDS system_lib
)

include_directories(
 include
 ${catkin_INCLUDE_DIRS}
)

add_executable(waypoint_saver_wrs_node src/waypoint_saver_wrs_node.cpp src/waypoint_saver_wrs.cpp)
target_link_libraries(waypoint_saver_wrs_node ${catkin_LIBRARIES})
