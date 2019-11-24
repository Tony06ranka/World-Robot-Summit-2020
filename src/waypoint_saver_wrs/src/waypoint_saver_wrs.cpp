#include <waypoint_saver_wrs/waypoint_saver_wrs.h>

WaypointSaver::WaypointSaver(ros::NodeHandle nh,ros::NodeHandle pnh ) : nh_(nh),pnh_(pnh)
{
    pnh_.param<std::string>("current_pose_topic", current_pose_topic_, "current_pose");
    pnh_.param<std::string>("waypoint_saver_pub", waypoint_saver_topic_, "waypoint_saver_pub");
    pnh_.param<std::string>("waypoint_csv", waypoint_path_, "/tmp/saved_waypoints.csv");
    pnh_.param<std::string>("map_frame", map_frame_, "map");
    pnh_.param<double>("dist_interval", dist_interval_, 1.0);
    waypoint_saver_pub_ = nh_.advertise<visualization_msgs::MarkerArray>(waypoint_saver_topic_, 1);

    init_pose_received_ = false;
    WaypointSaver::InitializeWaypointSaver_(); 
    
    current_pose_sub_ = nh_.subscribe(current_pose_topic_, 10, &WaypointSaver::CurrentPoseCallback_, this); 
}


WaypointSaver::~WaypointSaver()
{
    ofs_.close();
}

void WaypointSaver::InitializeWaypointSaver_()
{
    ofs_.open(waypoint_path_, std::ios::app);
    ofs_ << "x,y,z,yaw,velocity" << std::endl;
}

void WaypointSaver::PublishWaypointMarkerArray_(geometry_msgs::PoseStamped pose)
{   
    static visualization_msgs::MarkerArray marray;
    static int id = 0;

    // initialize marker
    visualization_msgs::Marker marker;
    marker.id = id;
    marker.header.frame_id = map_frame_;
    marker.header.stamp = ros::Time();
    marker.frame_locked = true;

    // create saved waypoint marker
    marker.scale.x = 0.3;
    marker.scale.y = 0.1;
    marker.scale.z = 0.2;
    marker.color.a = 1.0;
    marker.color.r = 0.0;
    marker.color.g = 1.0;
    marker.color.b = 0.0;
    marker.ns = "saved_waypoints_arrow";
    marker.type = visualization_msgs::Marker::ARROW;
    marker.action = visualization_msgs::Marker::ADD;
    marker.pose = pose.pose;
    marray.markers.push_back(marker);
        
    waypoint_saver_pub_.publish(marray);
    id++;
}

void WaypointSaver::CurrentPoseCallback_(const geometry_msgs::PoseStamped::ConstPtr msg)
{
    geometry_msgs::PoseStamped current_pose = *msg;
    
    if(!init_pose_received_)
    {
        ofs_ << std::fixed << std::setprecision(4) <<current_pose.pose.position.x << "," << current_pose.pose.position.y << "," << current_pose.pose.position.z << "," << tf::getYaw(current_pose.pose.orientation) << ",0,0" << std::endl;
        PublishWaypointMarkerArray_(current_pose);
        previous_pose_ = current_pose;
        init_pose_received_ = true;
    }

    else
    {
        double distance = sqrt(pow((current_pose.pose.position.x - previous_pose_.pose.position.x), 2) + pow((current_pose.pose.position.y - previous_pose_.pose.position.y), 2));
        
        if(distance > dist_interval_)
        {
            ofs_ << std::fixed << std::setprecision(4) <<current_pose.pose.position.x << "," << current_pose.pose.position.y << "," << current_pose.pose.position.z << "," << tf::getYaw(current_pose.pose.orientation) << ",0,0" << std::endl;
            PublishWaypointMarkerArray_(current_pose);
            previous_pose_ = current_pose;
        }
    }        
}

