#ifndef CUSTOMER_STOP_BY_JOY_H_CUSTOMER_STOP_BY_JOY_INCLUDED
#define CUSTOMER_STOP_BY_JOY_H_CUSTOMER_STOP_BY_JOY_INCLUDED

#include <ros/ros.h>
#include <geometry_msgs/TwistStamped.h>
#include <sensor_msgs/Joy.h>

//headers in Boost
#include <boost/thread.hpp>
#include <boost/bind.hpp>


class CustomerStopByJoy
{
public:
    CustomerStopByJoy(ros::NodeHandle nh,ros::NodeHandle pnh);
    ~CustomerStopByJoy();
private:
    void SensorJoyCallback_(const sensor_msgs::Joy::ConstPtr msg);
    void StopBehaveByJoy_(sensor_msgs::Joy joy);
    void JoyPublisher_();    
    ros::NodeHandle nh_;
    ros::NodeHandle pnh_;
        
    ros::Time current_time_;
       
    std::string joy_sub_topic_;
    std::string twist_topic_;    
 
    sensor_msgs::Joy sub_joy_msg_;
    geometry_msgs::TwistStamped joy_twist_;

    int push_the_buttons[1];

    ros::Subscriber joy_sub_;
    ros::Publisher joy_pub_;
};

#endif //CUSTOMER_STOP_BY_JOY_H_CUSTOMER_STOP_BY_JOY_INCLUDED
