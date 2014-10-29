/*
 *  Copyright (c) 2014, Oculus VR, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  LICENSE file in the root directory of this source tree. An additional grant 
 *  of patent rights can be found in the PATENTS file in the same directory.
 *
 */
#if defined(_WIN32) && !(defined(__GNUC__)  || defined(__GCCXML__)) && !defined(_RAKNET_LIB) && defined(_RAKNET_DLL)
#define RAK_DLL_EXPORT __declspec(dllexport)
#else
#define RAK_DLL_EXPORT  
#endif
