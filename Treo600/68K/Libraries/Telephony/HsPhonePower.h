/**
 * \file 68K/Libraries/Telephony/HsPhonePower.h
 *
 * Header File for Phone Library API ---- POWER CATEGORY
 *
 * All implementations of the Handspring Phone Library support a common API. 
 * This API is broken up into various categories for easier management.  This file
 * defines the POWER category.  This category provides routines to query & manage
 * the radio power.  
 * 
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

#ifndef HS_PHONEPOWER_H
#define HS_PHONEPOWER_H
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



  extern Err PhnLibSetModulePower (UInt16 refNum, Boolean on)
      PHN_LIB_TRAP(PhnLibTrapSetModulePower);

  extern PhnPowerType PhnLibModulePowered (UInt16 refNum)
      PHN_LIB_TRAP (PhnLibTrapModulePowered);


#endif
