#ifndef SEARCH_OBJECT_ARROUND_SEARCH_OBJECT_ARROUND_H_INCLUDED
#define SEARCH_OBJECT_ARROUND_SEARCH_OBJECT_ARROUND_H_INCLUDED

#include <ros/ros.h>
#include <tf/tf.h> 
#include <nav_path/Path.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/PoseStamped.h>

#include <boost/thread.hpp>
#include <boost/bind.hpp>

class SearchObjectArround
{
public:
    SearchObjectArround(ros::NoldeHandle nh, ros::NodeHandle pnh);
    ~SearchObjectArround();

private:
    void CurrentPoseCallback_(const geometry_msgs::PoseStamped::ConstPtr msg);
    void WaypointsRawCallback_(const nav_msgs::Path::ConstPtr msg);
    void PublishCmdVel_(void);
    void ObjectJudgeCallback_(const std_msgs::Bool::ConstPtr msg);
    
    std::string twist_topic_;
    std::string path_topic_;
    std::string current_pose_topic_;
    std::string object_topic_;

    double linear_vel_;
    double lookahead_dist_;
    
    nav_msgs::Path wps_;
    std_msgs::Bool object_judge_;
    geometry_msgs::PoseStamped current_pose_;
    

    ros::Publisher twist_pub_;
    ros::Subscriber path_sub_;
    ros::Subscriber current_pose_sub_;
    ros::Subscriber object_judge_sub_;
};

#endif //SEARCH_OBJECT_ARROUND_SEARCH_OBJECT_ARROUND_H_INCLUDED
