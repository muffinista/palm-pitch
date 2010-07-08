/**
 * \file 68K/Libraries/Telephony/HsPhoneSecurity.h
 *
 * Header File for Phone Library API ---- SECURITY CATEGORY
 *
 * All implementations of the Handspring Phone Library support a common API. 
 * This API is broken up into various categories for easier management.  This file
 * defines the public portion of the Security category.  These API calls are used 
 * to protect access to device and phone features.
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

#ifndef HS_PHONESECURITY_H
#define HS_PHONESECURITY_H
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

// Phone password types
/**
 * Item description here
 **/
typedef enum {
	phnPasswordUnknown,					// FAULT or none of the strings below
	// See GSM 07.07, section 8.3 for a list of passwords. The following
	// list is based on on version 6.2.0 of the recommendation.
	phnPasswordNone,					// READY
	phnPasswordSIMPIN,					// SIM PIN
	phnPasswordSIMPUK,					// SIM PUK
	phnPasswordPhSIMPIN,				// PH-SIM PIN
	phnPasswordPh1SIMPIN,				// PH-FSIM PIN
	phnPasswordPh1SIMPUK,				// PH-FSIM PUK
	phnPasswordSIMPIN2,					// SIM PIN2
	phnPasswordSIMPUK2,					// SIM PUK2
		// It is assumed that all PINs and PUKs below are network-based
		// PINS and PUKs. Function Change() uses a different timeout for
		// such PINs and/or PUKs.
	phnPasswordNetworkPIN,				// PH-NET PIN
	phnPasswordNetworkPUK,				// PH-NET PUK
	phnPasswordNetworkSubsetPIN,		// PH-NETSUB PIN
	phnPasswordNetworkSubsetPUK,		// PH-NETSUB PUK
	phnPasswordServiceProviderPIN,		// PH-SP PIN
	phnPasswordServiceProviderPUK,		// PH-SP PUK
	phnPasswordCorporatePIN,			// PH-CORP PIN
	phnPasswordCorporatePUK,			// PH-CORP PUK
		// The passwords below are supported by the +CPWD command. See GSM 07.07
		// section 7.4 and 7.5 for a list of facility-specific passwords.
	phnPasswordBarrAO,				// all outgoing call
	phnPasswordBarrOI,				// outgoing int’l calls
	phnPasswordBarrOX,				// outgoing int’l calls except to home country
	phnPasswordBarrAI,				// all incoming calls
	phnPasswordBarrIR,				// incoming calls when roaming outside home country
	phnPasswordBarrAB,				// all barring services
	phnPasswordBarrAG,				// all outgoing barring services
	phnPasswordBarrAC					// all incoming barring services
} PhnPasswordType;

#define isValidPhnPasswordType(p) (p <= phnPasswordBarrAC)
//#define isValidPhnPasswordType(p) ((p >= phnPasswordUnknown) && (p <= phnPasswordBarrAC))

extern Err PhnLibGetPhoneLock (UInt16 refNum, Boolean * lock, Boolean * autoLockCheckBoxState)
  PHN_LIB_TRAP(PhnLibTrapGetPhoneLock);


#endif
