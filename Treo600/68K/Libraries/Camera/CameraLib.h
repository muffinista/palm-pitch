/******************************************************************************
 *
 * Copyright (c) 2002 Handspring, Inc. All rights reserved.
 *
 * File: CameraLib68K.h
 *
 * Release: Palm OS 5.0
 *
 * Description:
 *              Public API of CameraLib Library used by 68K applications
 *
 * History:
 *		Oct 22, 2001	Created by Art Lamb
 *
 *****************************************************************************/

#ifndef __CAMERALIB68K_H__
#define	__CAMERALIB68K_H__

#include <PalmTypes.h>
#include <LibTraps.h>
#include <Common/HsCommon.h>




/********************************************************************
 * Prototypes
 ********************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

// Open up an instance of the PIClacLib library.
Err CameraLibOpen(UInt16 refnum)
			SYS_TRAP(kCameraLibTrapOpen);

// Close down an instance of the PIClacLib.
Err CameraLibClose(UInt16 refnum)
			SYS_TRAP(kCameraLibTrapClose);

Err CameraLibSleep (UInt16 refnum)
			SYS_TRAP(kCameraLibTrapSleep);

Err CameraLibWake (UInt16 refnum)
			SYS_TRAP(kCameraLibTrapWake);


Err CameraLibCapture (UInt16 refnum, void * buffer, UInt16 format)
			SYS_TRAP(kCameraLibTrapCameraLibCapture);

Err CameraLibPreview (UInt16 refnum, void * buffer, UInt16 format, UInt32 width, UInt32 height)
			SYS_TRAP(kCameraLibTrapCameraLibPreview);

Err CameraLibPreviewStart (UInt16 refnum, WinHandle windowH, UInt32 x, UInt32 y)
			SYS_TRAP(kCameraLibTrapCameraLibPreviewStart);

Err CameraLibPreviewStop (UInt16 refnum)
			SYS_TRAP(kCameraLibTrapCameraLibPreviewStop);

Err CameraLibRegisterGet (UInt16 refnum, UInt32 reg, UInt32 * valueP)
			SYS_TRAP(kCameraLibTrapCameraLibRegisterGet);

Err CameraLibRegisterSet (UInt16 refnum, UInt32 reg, UInt32 value)
			SYS_TRAP(kCameraLibTrapCameraLibRegisterSet);





#ifdef __cplusplus 
}
#endif

#endif 	//__CAMERALIB68K_H__
