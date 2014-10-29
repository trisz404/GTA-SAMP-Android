/*
 *  Copyright (c) 2014, Oculus VR, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  LICENSE file in the root directory of this source tree. An additional grant 
 *  of patent rights can be found in the PATENTS file in the same directory.
 *
 */

/// \file GetTime.h
/// \brief Returns the value from QueryPerformanceCounter.  This is the function RakNet uses to represent time. This time won't match the time returned by GetTimeCount(). See http://www.jenkinssoftware.com/forum/index.php?topic=2798.0
///

#ifndef __GET_TIME_H
#define __GET_TIME_H

#include "Export.h"
#include "NetworkTypes.h" // For RakNetTime

/// The namespace RakNet is not consistently used.  It's only purpose is to avoid compiler errors for classes whose names are very common.
/// For the most part I've tried to avoid this simply by using names very likely to be unique for my classes.
namespace RakNet
{
	/// Returns the value from QueryPerformanceCounter.  This is the function RakNet uses to represent time.
	RakNetTime RAK_DLL_EXPORT GetTime( void );
	RakNetTimeNS RAK_DLL_EXPORT GetTimeNS( void );
}

#endif
