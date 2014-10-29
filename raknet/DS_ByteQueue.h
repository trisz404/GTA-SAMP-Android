/*
 *  Copyright (c) 2014, Oculus VR, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  LICENSE file in the root directory of this source tree. An additional grant 
 *  of patent rights can be found in the PATENTS file in the same directory.
 *
 */

/// \file DS_ByteQueue.h
/// \internal
/// \brief Byte queue
///

#ifndef __BYTE_QUEUE_H
#define __BYTE_QUEUE_H

#include "Export.h"

/// The namespace DataStructures was only added to avoid compiler errors for commonly named data structures
/// As these data structures are stand-alone, you can use them outside of RakNet for your own projects if you wish.
namespace DataStructures
{
	class ByteQueue
	{
	public:
		ByteQueue();
		~ByteQueue();
		void WriteBytes(const char *in, unsigned length);
		bool ReadBytes(char *out, unsigned length, bool peek);
		unsigned GetBytesWritten(void) const;
		void IncrementReadOffset(unsigned length);
		void Clear(void);
		void Print(void);

	protected:
		char *data;
		unsigned readOffset, writeOffset, lengthAllocated;
	};
}

#endif
