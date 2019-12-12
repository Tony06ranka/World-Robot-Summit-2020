# World-Robot-Summit-2020

## REQUIREMENT
1.Install Dependecies
```
sudo apt install ros-$ROS_DISTRO-gmapping ros-$ROS_DISTRO-amcl ros-$ROS_DISTRO-map-server 
```

## HOW TO LAUNCH 
```
roslaunch ca_driver create_2.launch
rosrun urg_node urg_node
rosrun map_server map_server home/any_map
rosrun amcl amcl 
roslaunch dummy_localizer dummy_localizer.launch 
roslaunch rostate_machine mission_state_machine.launch
roslaunch waypoint_loader_wrs waypoint_loader_wrs.launch
roslaunch waypoint_selector waypoint_selector.launch
roslaunch pure_pursuit_wrs pure_pursuit_wrs.launch
```

## HOW TO CREATE WAYPOINT
```
roslaunch ca_driver create_2.launch
rosrun urg_node urg_node 
rosrun amcl amcl
rosrun map_server map_server home/happy_mini/any_map
roslaunch dummy_localizer dummy_localizer.launch
roslaunch waypoint_saver_wrs waypoint_saver_wrs.launch 
```

## HOW TO CREATE A MAP
```
roslaunch ca_driver create_2.launch
rosrun urg_node urg_node 
rosrun gmapping slam_gmapping 
rosrun tf transformation 
```
