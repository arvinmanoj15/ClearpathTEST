#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <iostream>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>

ros::Publisher cmd_vel_pub;
geometry_msgs::Twist cmd_vel_msg;
bool deadman_pressed = false;

void exampleCallback(const geometry_msgs::Twist::ConstPtr& msg) {
  // Process the received message here
  if (deadman_pressed) {
    cmd_vel_msg.linear.x = msg->linear.x;
    cmd_vel_msg.angular.z = msg->angular.z;
    cmd_vel_pub.publish(cmd_vel_msg);
  }
  //ROS_INFO("In exampleCallback\n");
}

int getch() {
  static struct termios oldt, newt;
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);

  int ch = getchar();

  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  return ch;
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "deadman_switch");
  ros::NodeHandle nh;
  cmd_vel_pub = nh.advertise<geometry_msgs::Twist>("/ridgeback_velocity_controller/cmd_vel", 10);
  ros::Subscriber sub = nh.subscribe("/example", 10, &exampleCallback);

  cmd_vel_msg.linear.x = 0.0;
  cmd_vel_msg.angular.z = 0.0;

  while (ros::ok()) {
    // check for spacebar key press
    if (getch() == 32) { // ASCII value of spacebar is 32
      deadman_pressed = true;
      ROS_INFO("DEADMAN switch pressed\n");
    } else {
      deadman_pressed = false;
    }

    if (!deadman_pressed) {
      cmd_vel_msg.linear.x = 0.0;
      cmd_vel_msg.angular.z = 0.0;
    }

    cmd_vel_pub.publish(cmd_vel_msg);

    ros::spinOnce();
  }

  return 0;
}
