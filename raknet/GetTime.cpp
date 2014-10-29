/*
 *  Copyright (c) 2014, Oculus VR, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  LICENSE file in the root directory of this source tree. An additional grant 
 *  of patent rights can be found in the PATENTS file in the same directory.
 *
 */

/// \file
///

#include "GetTime.h"
#ifdef _COMPATIBILITY_1
#include "Compatibility1Includes.h" // Developers of a certain platform will know what to do here.
#elif defined(_WIN32)
#include <windows.h>
#elif defined(_COMPATIBILITY_2)
#include "Compatibility2Includes.h"
#include <sys/time.h>
#include <unistd.h>
#else
#include <sys/time.h>
#include <unistd.h>
#endif

static bool initialized=false;
#ifdef _WIN32
static LARGE_INTEGER yo;
#else
static timeval tp, initialTime;
#endif

RakNetTime RakNet::GetTime( void )
{
	if ( initialized == false )
	{
#ifdef _WIN32
		QueryPerformanceFrequency( &yo );
		// The original code shifted right 10 bits
		//counts = yo.QuadPart >> 10;
		// It gives the wrong value since 2^10 is not 1000
	//	counts = yo.QuadPart;// / 1000;
#else
		gettimeofday( &initialTime, 0 );
#endif
		
		initialized = true;
	}
	
#ifdef _WIN32
	LARGE_INTEGER PerfVal;
	
	QueryPerformanceCounter( &PerfVal );
	
	return (RakNetTime)(PerfVal.QuadPart*1000 / yo.QuadPart);
#else
	gettimeofday( &tp, 0 );
	
	// Seconds to ms and microseconds to ms
	return ( tp.tv_sec - initialTime.tv_sec ) * 1000 + ( tp.tv_usec - initialTime.tv_usec ) / 1000;
	
#endif
}


RakNetTimeNS RakNet::GetTimeNS( void )
{
	if ( initialized == false )
	{
#ifdef _WIN32
		QueryPerformanceFrequency( &yo );
		// The original code shifted right 10 bits
		//counts = yo.QuadPart >> 10;
		// It gives the wrong value since 2^10 is not 1000
		//	counts = yo.QuadPart;// / 1000;
#else
		gettimeofday( &initialTime, 0 );
#endif

		initialized = true;
	}

#ifdef _WIN32
	LARGE_INTEGER PerfVal;

	QueryPerformanceCounter( &PerfVal );

	__int64 quotient, remainder;
	quotient=((PerfVal.QuadPart*1000) / yo.QuadPart);
	remainder=((PerfVal.QuadPart*1000) % yo.QuadPart);
	//return (PerfVal.QuadPart*1000 / (yo.QuadPart/1000));
	return quotient*1000 + (remainder*1000 / yo.QuadPart);

#else
	gettimeofday( &tp, 0 );

	return ( tp.tv_sec - initialTime.tv_sec ) * (RakNetTimeNS) 1000000 + ( tp.tv_usec - initialTime.tv_usec );

#endif
}
