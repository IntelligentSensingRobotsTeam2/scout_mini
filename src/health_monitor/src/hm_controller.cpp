#include "ros/ros.h"
#include "std_msgs/String.h"
#include "pump_sender.h"

void pump_state_cb(const std_msgs::String::ConstPtr& msg)
{
  ROS_INFO("I heard: [%s]", msg->data.c_str());
}

void camera_angle_cb(const std_msgs::String::ConstPtr& msg)
{
  ROS_INFO("**I heard: [%s]", msg->data.c_str());
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "hm_controller");

  ros::NodeHandle n;
  ros::Subscriber sub_pump_state = n.subscribe("pump_state", 1000, pump_state_cb);
  ros::Subscriber sub_camera_angle = n.subscribe("camera_angle", 1000, camera_angle_cb);

  ros::spin();

  return 0;
}