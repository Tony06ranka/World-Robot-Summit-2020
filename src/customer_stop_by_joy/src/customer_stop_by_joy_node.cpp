#include <customer_stop_by_joy/customer_stop_by_joy.h>

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "customer_stop_by_joy_node");
    ros::NodeHandle nh;
    ros::NodeHandle pnh;
    CustomerStopByJoy CustomerStopByJoy(nh,pnh);
    ros::spin();
    return 0;
}
