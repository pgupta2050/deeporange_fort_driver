#  Fort Robotics Joystick driver for Deep Orange 

## About
This package unpacks the can messages that are over ROS topics (over /can0/can_tx), and with the use of the can_dbc_parser ROS package, converts them to meaningful values mapping to each of the inputs from the joystick. This includes the left and right joy axes, the 8 buttons and estop button on the Fort Robotics SRC.

## Demo functionality
![Video](/media/VDR6_JoyHusky_Kartech_1.mp4)

## Prerequisite packages
In order to use this driver, following ROS packages are needed:
1. kvaser_interface (https://github.com/astuff/kvaser_interface) 
2. can_dbc_parser (https://github.com/NewEagleRaptor/raptor-dbw-ros/tree/master/can_dbc_parser)

## Subscribed Topics 
(as remapped in given launch file)
1. /can0/can_tx:- can_msgs::Frame - CAN messages from CAN bus

## Published Topics
(Cuurrent launch files uses "/vehicle" namespace for launchin the node)
1. /fort_estop:- std_msgs::Bool - Bool for E-stop enabled/disabled
2. /fort_joy:- sensor_msgs::Joy - Joy message
3. /fort_joyMisc:- deeporange_fort_driver::JoyMisc - Info on SRC's battery status, connection strength to VSC, current VSC operation mode etc.


## Dependencies
To be updated

