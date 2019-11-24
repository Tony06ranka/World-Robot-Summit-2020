#include <customer_stop_by_joy/customer_stop_by_joy.h>

CustomerStopByJoy::CustomerStopByJoy(ros::NodeHandle nh,ros::NodeHandle pnh) : nh_(nh), pnh_(pnh)
{
    pnh_.param<std::string>("twist_topic", twist_topic_, "/joy_pub_topic");
    pnh_.param<std::string>("joy_sub_topic", joy_sub_topic_, "/joy_sub_topic");
    joy_sub_ = nh.subscribe("/joy", 1, &CustomerStopByJoy::SensorJoyCallback_, this); 
    joy_pub_ = nh.advertise<geometry_msgs::TwistStamped>(twist_topic_, 1);
    boost::thread publish_thread(boost::bind(&CustomerStopByJoy::JoyPublisher_, this));
}
CustomerStopByJoy::~CustomerStopByJoy()
{

}

void CustomerStopByJoy::SensorJoyCallback_(const sensor_msgs::Joy::ConstPtr msg)
{
    sub_joy_msg_ = *msg;
    StopBehaveByJoy_(sub_joy_msg_);
    return;
}

void CustomerStopByJoy::StopBehaveByJoy_(sensor_msgs::Joy joy)
{
    geometry_msgs::TwistStamped twist;
    current_time_ = ros::Time::now();
    joy.header.stamp = current_time_;
	
	if(joy.buttons[0] == 1)
    {
		push_the_buttons[0] = 1;
	}
    else if(joy.buttons[2] == 1)
	{
		push_the_buttons[0] = 0;
	}
	
	if(push_the_buttons[0] == 1)
    {
		twist.twist.linear.x = 0;
        twist.twist.linear.y = 0;
        twist.twist.linear.z = 0;
	}
    else
    {
		twist.twist.linear.x = 0;
        twist.twist.linear.y = 0;
        twist.twist.linear.z = 0;
	}

	joy_twist_.header.stamp = current_time_;
	joy_twist_.twist.linear.x = twist.twist.linear.x;
	joy_twist_.twist.linear.y = twist.twist.linear.y;
	joy_twist_.twist.linear.z = twist.twist.linear.z;
}

void CustomerStopByJoy::JoyPublisher_()
{
    ros::Rate loop_late(10);
    while(ros::ok())
    {
        joy_pub_.publish(joy_twist_);
        loop_late.sleep();
    }
    return;
}

