#include <getback_to_waypoint/getback_to_waypoint.h>

GetBackToWaypoint::GetBackToWaypoint(ros::NodeHandle nh, ros::NodeHandle pnh) : nh_(nh), pnh_(pnh)
{
    pnh_.param<std::string>("path_topic", path_topic_, "/getback_waypoint/getback_waypoint_raw");
    pnh_.param<std::string>("twist_topic", twist_topic_, "/getback_waypoint/cmd_vel");
    pnh_.param<std::string>("map_frame", map_frame_, "map");
    pnh_.param<std::string>("current_pose_topic", current_pose_topic_, "/current_pose");
    pnh_.param<std::string>("object_detected_topic", object_detected_topic_, "/object_detected");
    pnh_.param<std::string>("done_collect_topic", done_collect_topic_, "/done_collect");
    pnh_.param<std::string>("getback_done_topic", getback_done_topic_, "/getback_done");
    pnh_.param<double>("linear_velocity", linear_velocity_, 0.3);
    pnh_.param<double>("lookahead_distance", lookahead_dist_, 0.5); 
    twist_pub_ = nh_.advertise<geometry_msgs::Twist>(twist_topic_, 1);
    getback_done_pub_ = nh_.advertise<std_msgs::Bool>(getback_done_topic_, 1);
    current_pose_sub_ = nh_.subscribe(current_pose_topic_, 1, &GetBackToWaypoint::CurrentPoseCallback_, this);
    object_detected_sub_ = nh_.subscribe(object_detected_topic_, 1, &GetBackToWaypoint::ObjectDetectedCallback_, this);
    done_collect_sub_ = nh_.subscribe(done_collect_topic_, 1, &GetBackToWaypoint::DoneCollectCallback_, this);
    boost::thread publish_thread(boost::bind(&GetBackToWaypoint::PublishCmdVel_, this));
}

GetBackToWaypoint::~GetBackToWaypoint()
{

}

void GetBackToWaypoint::CurrentPoseCallback_(const geometry_msgs::PoseStamped::ConstPtr msg)
{
    current_pose_ = *msg;
    return;
}

void GetBackToWaypoint::ObjectDetectedCallback_(const std_msgs::Bool msg)
{
    object_detected_ = msg.data;
    return;
}

void GetBackToWaypoint::DoneCollectCallback_(const std_msgs::Bool msg)
{
    done_collect_ = msg.data;
    return;
}

void GetBackToWaypoint::PublishCmdVel_(void)
{
    ros::Rate loop_rate(10);
    while(ros::ok())
    {
        if(object_detected_ == true)
        {
            current_pose_index_.push_back(current_pose_);

            int pose_index;

            for(pose_index=0; pose_index<current_pose_index_.size(); pose_index++)
            {
                gbwps_.poses[pose_index].pose.position.x = current_pose_.pose.position.x;
                gbwps_.poses[pose_index].pose.position.y = current_pose_.pose.position.y;
                gbwps_.poses[pose_index].pose.position.z = current_pose_.pose.position.z;
            }

            if(done_collect_ == true)
            {
                int target_index;
                double target_relative_dist, target_relative_angle;
                geometry_msgs::Point target_relative_pos;

                for(target_index=0; target_index<gbwps_.poses.size(); target_index++)
                {
                    target_relative_pos.x = gbwps_.poses[target_index].pose.position.x - current_pose_.pose.position.x;
                    target_relative_pos.y = gbwps_.poses[target_index].pose.position.y - current_pose_.pose.position.y;
                    target_relative_pos.z = gbwps_.poses[target_index].pose.position.z - current_pose_.pose.position.z;

                    target_relative_dist = std::sqrt(std::pow(target_relative_pos.x, 2) + std::pow(target_relative_pos.y, 2) + std::pow(target_relative_pos.z, 2));
                    target_relative_angle = std::atan2(target_relative_pos.y, target_relative_pos.x) - tf::getYaw(current_pose_.pose.orientation);

                    if(target_relative_angle < M_PI/2)
                    {
                        if(lookahead_dist_ > target_relative_dist) 
                        {
                            std_msgs::Bool getback_done;
                            getback_done.data = true;
                            getback_done_pub_.publish(getback_done);
                            break;
                        }
                    }

                }
                geometry_msgs::Twist cmd_vel;
                cmd_vel.linear.x = linear_velocity_;
                cmd_vel.angular.z = (2.0 * linear_velocity_ * sin(target_relative_angle)) / target_relative_dist;
                twist_pub_.publish(cmd_vel);
                return;
            }
            else
            {
                continue;
            }
            return;
        }
        else
        {
            continue;
        }
    }   
}
