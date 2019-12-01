#ifndef PURE_PURSUIT_PURE_PURSUIT_H_INCLUDED
#define PURE_PURSUIT_PURE_PURSUIT_H_INCLUDED

#include <ros/ros.h>
#include <nav_msgs/Path.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/PoseStamped.h>
#include <tf/tf.h>
#include <std_msgs/Bool.h>

//boost thread 
#include <boost/thread.hpp>
#include <boost/bind.hpp>

class PurePursuit
{
public:
    PurePursuit(ros::NodeHandle nh, ros::NodeHandle pnh);
    ~PurePursuit();
private:
    void PublishCmdVel_(void);
    void WaypointRawCallback_(const nav_msgs::Path::ConstPtr msg);
    void CurrentPoseCallback_(const geometry_msgs::PoseStamped::ConstPtr msg);
    void ObjectDetectedCallback_(const std_msgs::Bool msg);
    void GetBackWaypointCallback_(const std_msgs::Bool msg);

    ros::NodeHandle nh_;
    ros::NodeHandle pnh_;

    std::string path_topic_;
    std::string twist_topic_;
    std::string current_pose_topic_;
    std::string map_frame_;
    std::string get_back_topic_;
    std::string object_detected_topic_;

    geometry_msgs::PoseStamped current_pose_;
    nav_msgs::Path wps_;
    bool object_detected_;
    bool get_back_done_;
    
    
    ros::Publisher twist_pub_;
    ros::Subscriber path_sub_;
    ros::Subscriber object_detected_sub_;
    ros::Subscriber get_back_sub_;
    ros::Subscriber current_pose_sub_;

    double lookahead_dist_;
    double linear_velocity_;

}; 

#endif //PURE_PURSUIT_PURE_PURSUIT_H_INCLUDED


