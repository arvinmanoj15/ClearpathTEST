#include "ros/ros.h"
#include "std_msgs/String.h"
#include <termios.h>

// Non-blocking keyboard read function
int getch()
{
    static struct termios oldt, newt;
    tcgetattr( STDIN_FILENO, &oldt);           // save old settings
    newt = oldt;
    newt.c_lflag &= ~(ICANON);                 // disable buffering      
    tcsetattr( STDIN_FILENO, TCSANOW, &newt);  // apply new settings

    int c = getchar();  // read character (non-blocking)

    tcsetattr( STDIN_FILENO, TCSANOW, &oldt);  // restore old settings
    return c;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "keyboard_publisher");
    ros::NodeHandle nh;

    ros::Publisher keyboard_pub = nh.advertise<std_msgs::String>("keyboard", 10);

    ros::Rate loop_rate(10); // 10 Hz

    while (ros::ok())
    {
        int ch = getch(); // Non-blocking read

        std_msgs::String msg;

        if (ch == 'w' || ch == 'W')
        {
            msg.data = "up";
        }
        else if (ch == 's' || ch == 'S')
        {
            msg.data = "down";
        }
        else if (ch == 'a' || ch == 'A')
        {
            msg.data = "left";
        }
        else if (ch == 'd' || ch == 'D')
        {
            msg.data = "right";
        }
        else
        {
            continue; // Skip if no relevant key was pressed
        }

        keyboard_pub.publish(msg);

        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}

