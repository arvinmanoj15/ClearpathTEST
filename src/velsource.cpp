#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"

ros::Publisher pub;

void keyboardCallback(const std_msgs::String::ConstPtr& msg)
{
  geometry_msgs::Twist twist;

  if (msg->data == "up")
  {
    twist.linear.x = 0.5;
  }
  else if (msg->data == "down")
  {
    twist.linear.x = -0.5;
  }
  else if (msg->data == "left")
  {
    twist.angular.z = 0.5;
  }
  else if (msg->data == "right")
  {
    twist.angular.z = -0.5;
  }

  pub.publish(twist);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "example_publisher");
  ros::NodeHandle nh;

  pub = nh.advertise<geometry_msgs::Twist>("/example", 10);
  ros::Subscriber sub = nh.subscribe("keyboard", 10, keyboardCallback);

  ros::spin();

  return 0;
}
