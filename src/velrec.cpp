#include <ros/ros.h>
#include <geometry_msgs/Twist.h>

// Callback function for the "/example" topic
void exampleCallback(const geometry_msgs::Twist::ConstPtr& msg)
{
  // Create a publisher for the "/cmd_vel" topic
  ros::NodeHandle nh;
  ros::Publisher cmd_vel_pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 10);
  
  ROS_INFO("11\n");
  

  geometry_msgs::Twist cmd_vel_msg;
  cmd_vel_msg.linear.x = msg->linear.x;
  cmd_vel_msg.angular.z = msg->angular.z;

  ROS_INFO("18\n");

  // Publish the twist message to the "/cmd_vel" topic
  cmd_vel_pub.publish(cmd_vel_msg);
  
  ROS_INFO("23\n");
  
}

int main(int argc, char** argv)
{
  // Initialize the ROS node
  ros::init(argc, argv, "example_to_cmd_vel");

  // Create a subscriber for the "/example" topic
  ros::NodeHandle nh;
  ros::Subscriber example_sub = nh.subscribe("/example", 10, exampleCallback);

  // Spin and process callbacks
  ros::spin();

  return 0;
}
