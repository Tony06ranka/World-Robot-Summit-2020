#include <waypoint_saver_wrs/waypoint_saver_wrs.h>

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "waypoint_saver_wrs_node");
    ros::NodeHandle nh;
    ros::NodeHandle pnh("~");
    WaypointSaver waypoint_saver(nh,pnh);
    ros::spin();
    return 0;
}

