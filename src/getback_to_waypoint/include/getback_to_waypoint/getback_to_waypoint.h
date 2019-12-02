#ifndef GETBACK_TO_WAYPOINT_GETBACK_TO_WAYPOINT_H_INCLUDED 
#define GETBACK_TO_WAYPOINT_GETBACK_TO_WAYPOINT_H_INCLUDED

#include <ros/ros.h>
#include <std_msgs/Bool.h>
#include <nav_msgs/Path.h>
#include <geometry_msgs/PoseStamped.h>
#include <tf/tf.h>

//boost thread
#include <boost/thread.hpp>
#include <boost/bind.hpp>

class GetBackToWaypoint
{
public:
    GetBackToWaypoint(ros::NodeHandle nh, ros::NodeHandle pnh);
    ~GetBackToWaypoint();

private:
    void PublishCmdVel_(void);
    void CurrentPoseCallback_(const geometry_msgs::PoseStamped::ConstPtr msg);
    void ObjectDetectedCallback_(const std_msgs::Bool msg);
    void DoneCollectCallback_(const std_msgs::Bool msg);

    ros::NodeHandle nh_;
    ros::NodeHandle pnh_;

    std::string path_topic_;
    std::string map_frame_;
    std::string twist_topic_;
    std::string current_pose_topic_;
    std::string object_detected_topic_;
    std::string done_collect_topic_;
    std::string getback_done_topic_;
 
    geometry_msgs::PoseStamped current_pose_;
    nav_msgs::Path gbwps_;
    std::vector<geometry_msgs::PoseStamped> current_pose_index_;
    
    bool object_detected_;
    bool done_collect_;
    double lookahead_dist_;
    double linear_velocity_;

    ros::Publisher twist_pub_;
    ros::Publisher getback_done_pub_;
    ros::Subscriber current_pose_sub_;
    ros::Subscriber object_detected_sub_;
    ros::Subscriber done_collect_sub_;
};
#endif //GETBACK_TO_WAYPOINT_GETBACK_TO_WAYPOINT_H_INCLUDED

