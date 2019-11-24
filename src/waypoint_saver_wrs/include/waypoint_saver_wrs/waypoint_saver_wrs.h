#ifndef WAYPOINT_SAVER_WRS_WAYPOINT__SAVER_WRS_H_INCLUDED
#define WAYPOINT_SAVER_WRS_WAYPOINT_SAVER_WRS_H_INCLUDED

#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <tf/tf.h>
#include <visualization_msgs/MarkerArray.h>
#include <visualization_msgs/Marker.h>

#include <fstream>
#include <sstream>

class WaypointSaver
{
public:
    WaypointSaver(ros::NodeHandle nh,ros::NodeHandle pnh);
    ~WaypointSaver();

private:
    void PublishWaypointMarkerArray_(geometry_msgs::PoseStamped pose);
    void InitializeWaypointSaver_();
    void CurrentPoseCallback_(const geometry_msgs::PoseStamped::ConstPtr msg);

    ros::NodeHandle nh_;
    ros::NodeHandle pnh_;

    std::string current_pose_topic_;
    std::string waypoint_saver_topic_;
    std::string waypoint_path_;
    std::string map_frame_;
    double dist_interval_;
     
    std::ofstream ofs_;
    bool init_pose_received_;
    geometry_msgs::PoseStamped previous_pose_;
     
    ros::Publisher waypoint_saver_pub_;
    ros::Subscriber current_pose_sub_;
       
};

#endif //WAYPOINT_SAVER_WRS_H_WAYPOINT_SAVER_WRS_H_INCLUDED
