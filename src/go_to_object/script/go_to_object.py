#!/usr/bin/python
# -*- coding: utf-8 -*-

import rospy
import math
import threading 
import pyrealsense2 as rs
from std_msgs.msg import Bool 
from sensor_msgs.msg import Image
from geometry_msgs.msg import Twist
from darknet_ros_msgs.msg import BoundingBoxes

class GoToObject():
    def __init__(self):
        self.rs_middle_w = 0
        self.rs_middle_h = 0
        self.target_middle_w = 0
        self.target_middle_h = 0
        self.near_object = False
        self.twist_pub = rospy.Publisher("/cmd_vel", Twist, queue_size=10)
        self.near_object_pub = rospy.Publisher("/near_object", Bool, queue_size=10) 
        self.object_detected_pub = rospy.Publisher("/object_detected", Bool, queue_size=10)
        self.realsense_sub = rospy.Subscriber("/camera/depth/image_rect_raw", Image, self.RealSenseCallback, queue_size=1)
        self.darknet_sub = rospy.Subscriber("/darknet_ros/bounding_boxes", BoundingBoxes, self.DarkNetRosCallback, queue_size=1)
        
    def RealSenseCallback(self, msg):
        self.depth_image = msg
        
    def DarkNetRosCallback(self, msg):
        for target_size in range(len(msg.bounding_boxes)):
            if(msg.bounding_boxes[target_size].Class == "cup"):
                object_detected = True
                target_width = msg.bounding_box.bounding_boxes.xmax - msg.bounding_box.bounding_boxes.xmin
                target_height = msg.bounding_box.bounding_boxes.ymax - msg.bounding_box.bounding_boxes.ymin
                
                self.target_middle_w = target_width / 2
                self.target_middle_h = target_height / 2
            
                self.rs_middle_w = 640 / 2
                self.rs_middle_h = 480 / 2

                print "target_middle_w="+str(self.target_middle_w)+"target_middle_h="+str(self.target_middle_h) 
                print "rs_middle_w="+str(self.rs_middle_w)+"rs_middle_h="+str(self.rs_middle_h)
                
                object_detected_pub.publish(object_detected)

            elif(msg.bounding_boxes[target_size].Class == "core"):
                object_detected = True
                target_width = msg.bounding_box.bounding_boxes.xmax - msg.bounding_box.bounding_boxes.xmin
                target_height = msg.bounding_box.bounding_boxes.ymax - msg.bounding_box.bounding_boxes.ymin
                
                self.target_middle_w = target_width / 2
                self.target_middle_h = target_height / 2
            
                self.rs_middle_w = 640 / 2 
                self.rs_middle_h = 480 / 2
                #print "target_middle_x =%d target_middle_y =%d"%(self.target_middle_w, self.target_middle_h)
                print "target_middle_w="+str(self.target_middle_w)+"target_middle_h="+str(self.target_middle_h) 
                print "rs_middle_w="+str(self.rs_middle_w)+"rs_middle_h="+str(self.rs_middle_h)
                
                object_detected_pub.publish(object_detected)
            
            else:
                object_detected = False
                object_detected_pub.publish(object_detected)
    
    def GoAheadObject(self):
        cmd_vel = Twist()
        depth_w = self.depth_image.width
        depth_h = self.depth_image.height
        depth_middle_w = depth_w / 2
        depth_middle_h = depth_h / 2
        per_pixel_angle = 91.2 / 640
        error_width = abs(self.rs_middle_w - self.target_middle_w) 
        
        target_dist = rs.depth_frame.get_distance(depth_middle_w, depth_middle_h)
                
        while(target_dist > 10):
            if(self.target_middle_w < self.rs_middle_w):
                cmd_vel.linear.x = 0.01
                cmd_vel.angular.z = error_width * per_pixel_angle 
            elif(self.target_middle_w > self.rs_middle_w): 
                cmd_vel.linear.x = 0.01
                cmd_vel.angular.z = error_width * per_pixel_angle 
            elif(self.target_middle_w == self.rs_middle_w):
                cmd_vel.linear.x = 0.01
                cmd_vel.angular.z = error_width * per_pixel_angle 

            twist_pub.publish(cmd_vel)
        
        if(target_dist <= 10):
            cmd_vel.linear.x = 0
            cmd_vel.angular.z = 0
                            
            near_object = True
            near_object_pub.publisher(near_object) 
            twist_pub.publish(cmd_vel)

if __name__ == '__main__':
    rospy.init_node('GoToObject', anonymous=True)

    gotoobject = GoToObject()
    
    rate = rospy.Rate(10)

    while not rospy.is_shutdown():
        nowTime = rospy.get_rostime()
        rate.sleep()
