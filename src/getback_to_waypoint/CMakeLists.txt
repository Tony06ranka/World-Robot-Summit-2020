cmake_minimum_required(VERSION 2.8.3)
project(getback_to_waypoint)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  roscpp
  tf
  nav_msgs
  std_msgs
)

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES getback_to_waypoint
  CATKIN_DEPENDS geometry_msgs roscpp tf nav_msgs std_msgs
#  DEPENDS system_lib
)

include_directories(
 include
 ${catkin_INCLUDE_DIRS}
)

add_executable(getback_to_waypoint_node src/getback_to_waypoint_node.cpp src/getback_to_waypoint.cpp)
target_link_libraries(getback_to_waypoint_node ${catkin_LIBRARIES})
