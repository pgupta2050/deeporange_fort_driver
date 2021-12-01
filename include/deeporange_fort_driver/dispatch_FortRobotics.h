/*********************************************************************
 Refer to FORT SRC Manual for description
 *********************************************************************/

#ifndef _DO_FORT_DISPATCH_H
#define _DO_FORT_DISPATCH_H
#include <stdint.h>

namespace do_fortrobotics_can
{
// typedef enum {
//   VIN_MUX_VIN0  = 0x00,
//   VIN_MUX_VIN1  = 0x01,
//   VIN_MUX_VIN2  = 0x02,
// } VinMux;

// typedef enum {
//   WHEEL_SPEED_MUX0  = 0x00,
//   WHEEL_SPEED_MUX1  = 0x01,
//   WHEEL_SPEED_MUX2  = 0x02,
// } WheelSpeedMux;

#undef BUILD_ASSERT

enum {
  ID_LEFT_JOY_BASIC                = 0xCFDD633,
  ID_LEFT_JOY_EXT                  = 0xCFDD934,
  ID_RIGHT_JOY_BASIC               = 0xCFDD834,
  ID_RIGHT_JOY_EXT                 = 0xCFDD733,
  ID_HEARTBEAT                     = 0xCFDE801,
  ID_REMOTE_STATUS                 = 0xCFDE861,
  ID_USER_VAL                      = 0xCFDE900,
  ID_USER_STRING                   = 0xCFDEA00,
};

} //do_fortrobotics_can

#endif // _DO_FORT_DISPATCH_H
