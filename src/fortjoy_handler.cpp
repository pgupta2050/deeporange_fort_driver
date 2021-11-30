#include "fortjoy_handler.h"
// Dispatch file
#include <deeporange_fort_driver/dispatch_FortRobotics.h>

namespace do_fortrobotics_can
{

FortJoyNode::FortJoyNode(ros::NodeHandle &node, ros::NodeHandle &priv_nh)
{
    priv_nh.getParam("jostick_dbc_file", dbcFile_);
    
    // Initialise joystick vals
    estop_ = 1; // start with e stop on by default and wait to be set to 0
    lx = ly = lz = rx = ry = rz = 0;
    lb1 = lb2 = lb3 = lb4 = 0;
    rb1 = rb2 = rb3 = rb4 = 0;
    autonomy_mode_ = 2;
    vsc_mode_ = 2;

    // Subscribers and publishers
    pub_joy_ = node.advertise<sensor_msgs::Joy>("fort_joy",10);
    sub_can_ = node.subscribe("can_rx", 100, &FortJoyNode::recvCAN, this, ros::TransportHints().tcpNoDelay(true));
    pub_estop_ = node.advertise<std_msgs::Bool>("fort_estop", 100);

    // for debugging - pub and sub for chatter
    //pub_chat_ = node.advertise<std_msgs::String>("chatter1", 1000);
    //sub_can_ = node.subscribe("/chatter", 10 , &FortJoyNode::tester, this, ros::TransportHints().tcpNoDelay(true));
    
    joystickDbc_ = NewEagle::DbcBuilder().NewDbc(dbcFile_);

    // Frame ID
    frame_id_ = "base_footprint";
    priv_nh.getParam("frame_id", frame_id_);

    // Publish
    joyMsgfromFort.header.frame_id = frame_id_;

    // Set up Timer
    timer_ = node.createTimer(ros::Duration(1 / 20.0), &FortJoyNode::publish_estop, this);

}

FortJoyNode::~FortJoyNode()
{ 
}

// void FortJoyNode::tester(const std_msgs::String msg)
// {
//     // function for debugging
//     std_msgs::String chatmsg;
//     chatmsg.data = "hello";
//     pub_chat_.publish(chatmsg);
//     joyMsgfromFort.header.frame_id = frame_id_;
//     pub_joy_.publish(joyMsgfromFort);
// }

void FortJoyNode::recvCAN(const can_msgs::Frame::ConstPtr& msg)
{
    int rx_sign, ry_sign, lx_sign, ly_sign;
    float lx_magnitude, ly_magnitude, rx_magnitude, ry_magnitude;

    if (!msg->is_rtr && !msg->is_error)
    {
        switch (msg->id)
        {
            case ID_LEFT_JOY_BASIC:
            {
                NewEagle::DbcMessage* message = joystickDbc_.GetMessageById(ID_LEFT_JOY_BASIC);
                if (msg->dlc >= message->GetDlc())
                {
                    message->SetFrame(msg);
                    joyMsgfromFort.header.stamp = msg->header.stamp;
                    
                    if (message->GetSignal("Left_X_NeutralStatus")->GetResult() == 1)
                    // Positive X input on left joystick
                    {
                        lx_sign = 0;
                    }
                    else if (message->GetSignal("Left_X_PositiveStatus")->GetResult() == 1)
                    // Positive X input on left joystick
                    {
                        lx_sign = 1;
                    }
                    else if (message->GetSignal("Left_X_NegativeStatus")->GetResult() == 1)
                    // Positive X input on left joystick
                    {
                        lx_sign = -1;
                    }
                    lx_magnitude = message->GetSignal("Left_X_Magnitude")->GetResult();
                    lx = lx_magnitude*(float)lx_sign;
                    //int lx_p = message->GetSignal("Left_X_PositiveStatus")->GetResult();
                    //int lx_n = message->GetSignal("Left_X_NegativeStatus")->GetResult();
                    //int lx_neu = message->GetSignal("Left_X_NeutralStatus")->GetResult();
                    //ROS_WARN("Mag, neg, neutral, pos: %f %d %d %d",lx_magnitude, lx_n, lx_neu, lx_p);
                    //ROS_WARN_THROTTLE(10,"Received left joy");

                    if (message->GetSignal("Left_Y_NeutralStatus")->GetResult() == 1)
                    // no X input on left joystick
                    {
                        ly_sign = 0;
                    }
                    else if (message->GetSignal("Left_Y_PositiveStatus")->GetResult() == 1)
                    // Positive X input on left joystick
                    {
                        ly_sign = 1;
                    }
                    else if (message->GetSignal("Left_Y_NegativeStatus")->GetResult() == 1)
                    // negative X input on left joystick
                    {
                        ly_sign = -1;
                    }
                    ly_magnitude = message->GetSignal("Left_Y_Magnitude")->GetResult();
                    ly = ly_magnitude*(float)ly_sign;

                    lb1 = message->GetSignal("Left_ButtonDown")->GetResult();
                    lb2 = message->GetSignal("Left_ButtonRight")->GetResult();
                    lb3 = message->GetSignal("Left_ButtonUp")->GetResult();
                    lb4 = message->GetSignal("Left_ButtonLeft")->GetResult();

                    joyMsgfromFort.axes = {lx,ly,lz,rx,ry,rz};
                    joyMsgfromFort.buttons = {lb1, lb2, lb3, lb4, rb1, rb2, rb3, rb4};
                    //ROS_WARN("lx %f", lx);
                    pub_joy_.publish(joyMsgfromFort);
                    
                }
            }
            break;

            case ID_RIGHT_JOY_BASIC:
            {
                NewEagle::DbcMessage* message = joystickDbc_.GetMessageById(ID_RIGHT_JOY_BASIC);
                if (msg->dlc >= message->GetDlc())
                {
                    message->SetFrame(msg);
                    joyMsgfromFort.header.stamp = msg->header.stamp;
                    
                    if (message->GetSignal("Right_X_NeutralStatus")->GetResult() == 1)
                    // no y input on right joystick
                    {
                        rx_sign = 0;
                    }
                    else if (message->GetSignal("Right_X_PositiveStatus")->GetResult() == 1)
                    // Positive y input on right joystick
                    {
                        rx_sign = 1;
                    }
                    else if (message->GetSignal("Right_X_NegativeStatus")->GetResult() == 1)
                    // negative y input on right joystick
                    {
                        rx_sign = -1;
                    }
                    rx_magnitude = message->GetSignal("Right_X_Magnitude")->GetResult();
                    rx = rx_magnitude*(float)rx_sign;

                    if (message->GetSignal("Right_Y_NeutralStatus")->GetResult() == 1)
                    // no y input on right joystick
                    {
                        ry_sign = 0;
                    }
                    else if (message->GetSignal("Right_Y_PositiveStatus")->GetResult() == 1)
                    // Positive y input on right joystick
                    {
                        ry_sign = 1;
                    }
                    else if (message->GetSignal("Right_Y_NegativeStatus")->GetResult() == 1)
                    // negative y input on right joystick
                    {
                        ry_sign = -1;
                    }
                    ry_magnitude = message->GetSignal("Right_Y_Magnitude")->GetResult();
                    ry = ry_magnitude*(float)ry_sign;

                    rb1 = message->GetSignal("Right_Button1")->GetResult();
                    rb2 = message->GetSignal("Right_Button2")->GetResult();
                    rb3 = message->GetSignal("Right_Button3")->GetResult();
                    rb4 = message->GetSignal("Right_Button4")->GetResult();

                    joyMsgfromFort.axes = {lx,ly,lz,rx,ry,rz};
                    joyMsgfromFort.buttons = {lb1, lb2, lb3, lb4, rb1, rb2, rb3, rb4};
                    pub_joy_.publish(joyMsgfromFort);
                }
            }
            break;

            case ID_HEARTBEAT:
            {
                NewEagle::DbcMessage* message = joystickDbc_.GetMessageById(ID_HEARTBEAT);
                if (msg->dlc >= message->GetDlc())
                {
                    estop_ = message->GetSignal("E_stop_indication")->GetResult();
                    //autonomy_mode_ = message->GetSignal("Autonomy_Mode")->GetResult();
                    //vsc_mode_ = message->GetSignal("VSC_Mode")->GetResult();
                    vsc_mode_ = 2;
                    //ROS_WARN_THROTTLE(5.0,"estop, auto, vsc %d %d %d",estop_,autonomy_mode_ ,vsc_mode_ );
                }
            }
            break;

        }
    }
}

void FortJoyNode::publish_estop(const ros::TimerEvent&)
{
    std_msgs::Bool estopMsg;
    if (estop_ != 0)
    {
        estopMsg.data = 1;
        pub_estop_.publish(estopMsg);
    }
    else
    {
        estopMsg.data = 0;
        pub_estop_.publish(estopMsg);
    }
}

} // do_fortrobotics_can
