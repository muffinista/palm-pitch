/**
 * \file 68K/Libraries/Telephony/HsPhoneLibrary.h
 *
 * Header File for Phone Library API ---- LIBRARY CATEGORY
 *
 * All implementations of the Handspring Phone Library support a common API. 
 * This API is broken up into various categories for easier management.  This file
 * defines the LIBRARY category.  These API calls are used for basic Palm Library
 * operation.
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

#ifndef HS_PHONELIBRARY_H
#define HS_PHONELIBRARY_H
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


// Open and initialize the phone library.
  extern Err      PhnLibOpen (UInt16 refNum)
                  SYS_TRAP (sysLibTrapOpen);

// Closes the phone library.
  extern Err      PhnLibClose (UInt16 refNum)
                  SYS_TRAP (sysLibTrapClose);

// Puts phone library to sleep
  extern Err      PhnLibSleep (UInt16 refNum)
                  SYS_TRAP (sysLibTrapSleep);

// Wake phone library
  extern Err      PhnLibWake (UInt16 refNum)
                  SYS_TRAP (sysLibTrapWake);

  extern Err      PhnLibGetLibAPIVersion (UInt16 refNum, UInt32* dwVerP)
                  PHN_LIB_TRAP (PhnLibTrapGetLibAPIVersion);

  // We should probably return "Not supported" on this function
  extern void     PhnLibUninstall (UInt16 refNum)
                  PHN_LIB_TRAP (PhnLibTrapUninstall);

  extern Err      PhnLibRegister (UInt16 refNum, DWord creator, UInt16 services)
                  PHN_LIB_TRAP (PhnLibTrapRegister);

#endif
