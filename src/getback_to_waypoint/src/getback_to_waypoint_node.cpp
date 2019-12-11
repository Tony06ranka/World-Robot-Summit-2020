#include <getback_to_waypoint/getback_to_waypoint.h>

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "getback_to_waypoint_node");
    ros::NodeHandle nh;
    ros::NodeHandle pnh;
    GetBackToWaypoint getback_to_waypoint(nh,pnh);
    ros::spin();
    return 0;
}
