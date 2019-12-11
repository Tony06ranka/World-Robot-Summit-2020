#include <search_object_arround/search_object_arround.h>

SearchObjectArround::SearchObjectArround(ros::NodeHandle nh, ros::NodeHandle pnh) : nh_(nh), pnh_(pnh)
{



}


SearchObjectArround::~SearchObjectArround()
{

}

void SearchObjectArround::CurrentPoseCallback_(const geometry_msgs::PoseStamped::ConstPtr msg)
{
    current_pose_ = *msg;
    return;
}

void SearchObjectArround::WaypointsRawCallback_(const nav_msgs::Path::ConstPtr msg)
{
    wps_ = *msg;
    return;
}

void ObjectJudgeCallback_(const std_msgs::Bool::ConstPtr msg)
{
    object_judge_ = *msg;
    return;
}

void PublishCmdVel_(void)
{
    ros::Rate loop_late(10);
    
    while(ros::ok())
    {
        int target_index;
        double     
}



