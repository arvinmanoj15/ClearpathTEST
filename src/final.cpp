#include <ros/ros.h>
#include <geometry_msgs/Twist.h>

// Callback function for the "/cmd_vel" topic
void cmdVelCallback(const geometry_msgs::Twist::ConstPtr& msg)
{
  ROS_INFO("Received cmd_vel message:");
  ROS_INFO("linear.x = %f", msg->linear.x);
  ROS_INFO("linear.y = %f", msg->linear.y);
  ROS_INFO("linear.z = %f", msg->linear.z);
  ROS_INFO("angular.x = %f", msg->angular.x);
  ROS_INFO("angular.y = %f", msg->angular.y);
  ROS_INFO("angular.z = %f", msg->angular.z);
}

int main(int argc, char** argv)
{
  // Initialize the ROS node
  ros::init(argc, argv, "cmd_vel_subscriber");
  ros::NodeHandle nh;

  // Create a subscriber for the "/cmd_vel" topic
  ros::Subscriber cmd_vel_sub = nh.subscribe<geometry_msgs::Twist>("/cmd_vel", 10, cmdVelCallback);

  // Spin and process callbacks
  ros::spin();

  return 0;
}
