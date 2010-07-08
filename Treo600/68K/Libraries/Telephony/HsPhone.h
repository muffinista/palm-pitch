/**
 * \file 68K/Libraries/Telephony/HsPhone.h
 *
 * Header file for the phone library (CDMA or GSM)
 *
 * This is the generic header file that should be used by any code that
 * uses the CDMA or GSM phone libraries. If you add a function to this file
 * please makes sure you update both the CDMA and GSM libraries with this
 * function and update the ARM wrapper library if appropriate.
 *
 * \license
 *
 *    Copyright (c) 2002 Handspring Inc., All Rights Reserved
 *
 * \author Arun Mathias
 *
 * $Id:$
 *
 **************************************************************/

#ifndef HS_PHONE_H
#define HS_PHONE_H
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

// ------------------------------------------------------------------
// Defines
// ------------------------------------------------------------------

#include "HsPhoneLibrary.h"         // CATEGORY:  LIBRARY
#include "HsPhoneMisc.h"            // CATEGORY:  MISC
#include "HsPhoneAudio.h"           // CATEGORY:  AUDIO
#include "HsPhoneSMS.h"             // CATEGORY:  SMS
#include "HsPhoneNetwork.h"         // CATEGORY:  NETWORK
#include "HsPhoneGSM.h"             // CATEGORY:  GSM
#include "HsPhoneSecurity.h"        // CATEGORY:  SECURITY
#include "HsPhoneCDMA.h"            // CATEGORY:  CDMA
#include "HsPhoneIOTA.h"            // CATEGORY:  IOTA
#include "HsPhonePower.h"           // CATEGORY:  POWER

#include "HsPhoneEvent.h"           // CATEGORY:  NOTIFICATIONS & EVENTS


#endif
