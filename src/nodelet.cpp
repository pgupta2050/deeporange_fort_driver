/*********************************************************************
Written for use in Deep Orange 13 for FORT Robotics Joystick
 *********************************************************************/

#include <pluginlib/class_list_macros.h>
#include <nodelet/nodelet.h>

#include "fortjoy_handler.h"

namespace do_fortrobotics_can
{

class CanNodelet : public nodelet::Nodelet
{
public:
  CanNodelet()
  {
  }
  ~CanNodelet()
  {
  }

  void onInit(void)
  {
    node_.reset(new FortJoyNode(getNodeHandle(), getPrivateNodeHandle()));
  }

private:
  boost::shared_ptr<FortJoyNode> node_;
};

} // do_fortrobotics_can

// Register this plugin with pluginlib.  Names must match nodelets.xml.
//
// parameters: class type, base class type
PLUGINLIB_EXPORT_CLASS(do_fortrobotics_can::CanNodelet, nodelet::Nodelet);
