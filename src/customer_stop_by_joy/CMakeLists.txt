cmake_minimum_required(VERSION 2.8.3)
project(customer_stop_by_joy)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  geometry_msgs
  std_msgs
)

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES customer_stop_by_joy
  CATKIN_DEPENDS roscpp geometry_msgs std_msgs
#  DEPENDS system_lib
)
include_directories(
 include
 ${catkin_INCLUDE_DIRS}
)

add_executable(customer_stop_by_joy_node src/customer_stop_by_joy_node.cpp src/customer_stop_by_joy.cpp)
target_link_libraries(customer_stop_by_joy_node ${catkin_LIBRARIES})

