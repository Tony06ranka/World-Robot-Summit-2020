#include <pure_pursuit/pure_pursuit.h>

PurePursuit::PurePursuit(ros::NodeHandle nh, ros::NodeHandle pnh) : nh_(nh),pnh_(pnh)
{
    pnh.param<std::string>("twist_topic", twist_topic_, "cmd_vel");
    pnh.param<std::string>("path_topic", path_topic_, "waypoints_raw");
    pnh.param<std::string>("current_pose_topic", current_pose_topic_, "current_pose");
    pnh.param<std::string>("map_frame", map_frame_, "map");
    pnh.param<std::string>("get_back_topic", get_back_topic_, "get_back_waypoint");
    pnh.param<std::string>("object_detected_topic", object_detected_topic_, "object_detected");
    pnh.param<double>("linear_velocity", linear_velocity_, 0.3);
    pnh.param<double>("lookahead_distance", lookahead_dist_, 0.5);
    twist_pub_ = nh.advertise<geometry_msgs::Twist>(twist_topic_, 1);
    path_sub_ = nh.subscribe(path_topic_, 1, &PurePursuit::WaypointRawCallback_, this);
    object_detected_sub_ = nh.subscribe(object_detected_topic_, 1, &PurePursuit::ObjectDetectedCallback_, this);
    get_back_sub_ = nh.subscribe(get_back_topic_, 1, &PurePursuit::GetBackWaypointCallback_, this);
    current_pose_sub_ = nh.subscribe(current_pose_topic_, 1, &PurePursuit::CurrentPoseCallback_, this);
    boost::thread publish_thread(boost::bind(&PurePursuit::PublishCmdVel_, this));

}


PurePursuit::~PurePursuit()
{

}

void PurePursuit::WaypointRawCallback_(const nav_msgs::Path::ConstPtr msg)
{
    wps_ = *msg;
    return;
}

void PurePursuit::CurrentPoseCallback_(const geometry_msgs::PoseStamped::ConstPtr msg)
{
    current_pose_ = *msg;
    return;
}

void PurePursuit::ObjectDetectedCallback_(const std_msgs::Bool msg)
{
    object_detected_ = msg.data;
    return;
}

void PurePursuit::GetBackWaypointCallback_(const std_msgs::Bool msg)
{
    get_back_done_ = msg.data;
    return;
}

void PurePursuit::PublishCmdVel_(void)
{
    ros::Rate loop_rate(10);
    while(ros::ok())
    {
        int target_index;
        double target_relative_dist, target_relative_angle;
        geometry_msgs::Point target_relative_pos;

        for(target_index=0; target_index<wps_.poses.size(); target_index++)
        {
            target_relative_pos.x = wps_.poses[target_index].pose.position.x - current_pose_.pose.position.x;
            target_relative_pos.y = wps_.poses[target_index].pose.position.y - current_pose_.pose.position.y;
            target_relative_pos.z = wps_.poses[target_index].pose.position.z - current_pose_.pose.position.z;

            target_relative_dist = std::sqrt(std::pow(target_relative_pos.x, 2) + std::pow(target_relative_pos.y, 2) + std::pow(target_relative_pos.z, 2));
            target_relative_angle = std::atan2(target_relative_pos.y, target_relative_pos.x) - tf::getYaw(current_pose_.pose.orientation);

            if(target_relative_angle < M_PI/2)
            {
                if(lookahead_dist_ > target_relative_dist) break;
            }


        }
        if(object_detected_ != true)
        {
            geometry_msgs::Twist cmd_vel;
            cmd_vel.linear.x = linear_velocity_;
            cmd_vel.angular.z = (2.0 * linear_velocity_ * sin(target_relative_angle)) / target_relative_dist;
            twist_pub_.publish(cmd_vel);
        }
        else
        {
                if(get_back_done_ == false) 
                {
                    loop_rate.sleep();
                }
                continue;
        }
        
        loop_rate.sleep();
    }
    return;
}

