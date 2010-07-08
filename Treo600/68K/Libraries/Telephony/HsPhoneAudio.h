/**
 * \file 68K/Libraries/Telephony/HsPhoneAudio.h
 *
 * Header File for Phone Library API ---- AUDIO CATEGORY
 *
 * All implementations of the Handspring Phone Library support a common API. 
 * This API is broken up into various categories for easier management.  This file
 * defines the Audio category.  These API calls are used to play tones and other audio
 * on an active phone connection.
 *
 * \license
 *
 *    Copyright (c) 2003 Handspring Inc., All Rights Reserved
 *
 * \author Arun Mathias
 *
 * $Id:$
 *
 **************************************************************/

#ifndef HS_PHONEAUDIO_H
#define HS_PHONEAUDIO_H
#include <PalmOS.h>
#include <PalmTypes.h>
#ifndef __CORE_COMPATIBILITY_H__
#include <PalmCompatibility.h>
	// workaround for differing header files in sdk-3.5 and sdk-internal
	#ifndef __CORE_COMPATIBILITY_H__
	#define __CORE_COMPATIBILITY_H__
	#endif 
#endif 
#include <Common/Libraries/Telephony/HsPhoneTraps.h>     // trap table definition for phone library calls
#include <Common/Libraries/Telephony/HsPhoneErrors.h>    // error codes returned by phone library functions
#include <Common/Libraries/Telephony/HsPhoneTypes.h>


// Phone slider switch
#define kSliderLow			0
#define kSliderHigh			1
#define kSliderPositions	2

typedef struct
  {
    UInt8            ringerID;
    UInt16            volume;
    Boolean         vibrate;
    Boolean         msgAlert;
    Boolean         svcAlert;
  }
PhnRingingProfileType;

/**
 * Item description here
 **/
typedef struct {
	PhnRingingProfileType profiles[kSliderPositions];
} PhnRingingInfoType, * PhnRingingInfoPtr;


#endif
