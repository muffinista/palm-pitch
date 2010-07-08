/***************************************************************
 *
 *  Project:
 *	  Camera Library
 *
 * Copyright info:
 *
 *	  Copyright (c) Handspring 2003 -- All Rights Reserved
 *
 *
 *  FileName:
 *	  CameraLibCommon.h
 * 
 *  Description:
 *	  This is the common header file for the Camera Library.
 *
 *	Note:
 *
 ****************************************************************/

#ifndef CAMERA_LIB_COMMON_H
#define CAMERA_LIB_COMMON_H
/********************************************************************
 * Constants
 ********************************************************************/

#define kCameraLibType		sysFileTLibrary
#define kCameraLibCreator	'HsCa'
#define kCameraLibName		"CameraLib"	


#define kCameraImageFormatRGB1		  1
#define kCameraImageFormatRGB4		  2
#define kCameraImageFormatRGB8		  3
#define kCameraImageFormatRGB16		  4
#define kCameraImageFormatRGB24		  5
#define kCameraImageFormatRGB32		  6
#define kCameraImageFormatYCrCb		  7
#define kCameraImageLittleEndian	  0x8000

#define kCameraImageFormatYCbCr		  kCameraImageFormatYCrCb // zzz remove



// Error codes
#define errCam						  0xaf00
#define	errCamNoFrame 				  (errCam + 0)
#define errInPreviewMode			  (errCam + 1)
#define errCamOverflow				  (errCam + 2)
#define errInvalidAddress			  (errCam + 3)
#define errCamWriteFailed			  (errCam + 4)





/********************************************************************
 * Traps
 ********************************************************************/

#define kCameraLibTrapOpen					sysLibTrapOpen
#define kCameraLibTrapClose					sysLibTrapClose
#define kCameraLibTrapSleep					sysLibTrapSleep
#define kCameraLibTrapWake					sysLibTrapWake
#define kCameraLibTrapCameraLibCapture		(sysLibTrapCustom)
#define kCameraLibTrapCameraLibPreview		(sysLibTrapCustom+1)
#define kCameraLibTrapCameraLibPreviewStart	(sysLibTrapCustom+2)
#define kCameraLibTrapCameraLibPreviewStop	(sysLibTrapCustom+3)
#define kCameraLibTrapCameraLibRegisterGet	(sysLibTrapCustom+4)
#define kCameraLibTrapCameraLibRegisterSet	(sysLibTrapCustom+5)

#endif
