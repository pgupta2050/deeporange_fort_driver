#ifndef _FORTJOY_NODE_H_
#define _FORTJOY_NODE_H_

#include <string.h>
#include <ros/ros.h>

// ROS messages
#include <can_msgs/Frame.h>
#include <sensor_msgs/Imu.h>
#include <sensor_msgs/JointState.h>
#include <sensor_msgs/Joy.h>
#include <geometry_msgs/TwistStamped.h>
#include <std_msgs/Empty.h>
#include <std_msgs/Bool.h>
#include <std_msgs/String.h>

// Can dbc parser mackage
#include <can_dbc_parser/DbcMessage.h>
#include <can_dbc_parser/DbcSignal.h>
#include <can_dbc_parser/Dbc.h>
#include <can_dbc_parser/DbcBuilder.h>

// Dispatch file
#include <deeporange_fort_driver/dispatch_FortRobotics.h>

namespace do_fortrobotics_can

{
    class FortJoyNode
    {
        public:
        FortJoyNode(ros::NodeHandle &node, ros::NodeHandle &priv_nh);
        ~FortJoyNode();

        private:
        void recvCAN(const can_msgs::Frame::ConstPtr& msg);
        void tester(const std_msgs::String msg);
        void publish_estop(const ros::TimerEvent& event);
        ros::Timer timer_;

        // Frame ID
        std::string frame_id_;

        // Published topics
        ros::Publisher pub_joy_;
        //ros::Publisher pub_chat_;
        ros::Publisher pub_estop_;
        // Subscribed topics
        ros::Subscriber sub_can_;

        // variables
        NewEagle::Dbc joystickDbc_;
        std::string dbcFile_;
        sensor_msgs::Joy joyMsgfromFort;
        //std_msgs::Header joyHeader;

        // axes and button value variables
        float lx, ly, rx, ry, lz, rz;
        int lb1, lb2, lb3, lb4, rb1, rb2, rb3, rb4;

        // E-stop indicator
        int estop_;
        int autonomy_mode_;
        int vsc_mode_;

    };
} // do_fortrobotics_can

#endif // _FORTJOY_NODE_H_