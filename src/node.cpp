/*********************************************************************
Written for use in Deep Orange 13 for FORT Robotics Joystick
Makes use of New Eagle package: can_dbc_parser (https://github.com/NewEagleRaptor/raptor-dbw-ros/tree/master/can_dbc_parser)

 *********************************************************************/

#include <ros/ros.h>
#include "fortjoy_handler.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "FortJoyCan");
  ros::NodeHandle node;
  ros::NodeHandle priv_nh("~");

  // create FortJoyNode class
  do_fortrobotics_can::FortJoyNode n(node, priv_nh);

  // handle callbacks until shut down
  ros::spin();

  return 0;
}
