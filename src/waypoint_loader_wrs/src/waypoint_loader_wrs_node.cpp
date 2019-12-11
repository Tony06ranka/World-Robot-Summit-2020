#include <waypoint_loader_wrs/waypoint_loader_wrs.h>

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "waypoint_loader_wrs_node");
    ros::NodeHandle nh;
    ros::NodeHandle pnh("~");
    WaypointLoader waypoint_loader(nh,pnh);
    ros::spin();
    return 0;
}
