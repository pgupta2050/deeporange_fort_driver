/*********************************************************************
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2018-2019 New Eagle 
 *  Copyright (c) 2015-2018, Dataspeed Inc.
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of Dataspeed Inc. nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *********************************************************************/

#ifndef _DO_FORT_DISPATCH_H
#define _DO_FORT_DISPATCH_H
#include <stdint.h>

namespace do_fortrobotics_can
{
typedef enum {
  VIN_MUX_VIN0  = 0x00,
  VIN_MUX_VIN1  = 0x01,
  VIN_MUX_VIN2  = 0x02,
} VinMux;

typedef enum {
  WHEEL_SPEED_MUX0  = 0x00,
  WHEEL_SPEED_MUX1  = 0x01,
  WHEEL_SPEED_MUX2  = 0x02,
} WheelSpeedMux;

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
