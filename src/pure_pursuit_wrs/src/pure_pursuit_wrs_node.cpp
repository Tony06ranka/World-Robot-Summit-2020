#include <pure_pursuit_wrs/pure_pursuit_wrs.h>

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "pure_pursuit_wrs_node");
    ros::NodeHandle nh;
    ros::NodeHandle pnh("~");
    PurePursuit pure_pursuit(nh,pnh);
    ros::spin();
    return 0;
}
