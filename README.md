# World-Robot-Summit-2020

## HOW TO LAUNCH 

```
rosrun map_server map_server //any map here
rosrun amcl amcl 
roslaunch waypoint_loader_wrs waypoint_loader_wrs.launch
roslaunch waypoint_selector waypoint_selector.launch
roslaunch pure_pursuit_wrs pure_pursuit_wrs.launch
roslaunch dummy_localizer dummy_localizer.launch 
```

## HOW TO CREATE A MAP AND WAYPOINT
```
rosrun amcl amcl
rosrun gmapping slam_gmapping scan:=base_scan
roslaunch waypoint_saver_wrs waypoint_saver_wrs.launch
roslaunch dummy_localizer dummy_localizer.launch 
```
