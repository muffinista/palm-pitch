/**
 * \file 68K/Libraries/Telephony/HsPhoneMisc.h
 *
 * Header File for Phone Library API ---- MISC CATEGORY
 *
 * All implementations of the Handspring Phone Library support a common API. 
 * This API is broken up into various categories for easier management.  This file
 * defines the SMS category.  These API calls are Miscellaneous calls that don't
 * fit into any other category.  Many of them are device control.
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

#ifndef HS_PHONEMISC_H
#define HS_PHONEMISC_H
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

/**
 * Vibrate mode while ringing.
 **/
typedef enum
  {
    phnVibrateOff,
    phnVibrateOn
  }
PhnVibrateType;

#define isValidPhnVibrateType(t) ((t >= phnVibrateOff) && (t <= phnVibrateOn)) 


// Phone Connection Type
/**
 * Item description here
 **/
typedef enum {
  voiceConnection	= 1,
  csdConnection		= 2,
  gprsConnection    = 3,
  oneXConnection    = 4
} PhnConnectionEnum;

#define isValidPhnConnectionEnum(e) ((e >= voiceConnection) && (e <= oneXConnection))

/**
 * Item description here
 **/
typedef enum
{
  phnHandsetMode, //sets default mode to handset mode
  phnHeadsetMode, //sets default mode to headdset mode
  phnSpeakerPhoneMode, //sets default mode to speaker phone mode
  phnCarKitMode, //set carkit mode
  phnHandsetLidCloseMode,
  phnAutoMode	//automatic mode where modem internaly decides the mode

}PhnEquipmentMode;

#define isValidPhnEquipmentMode(m) (m <= phnAutoMode)


/**
 * Radio state
 **/
typedef struct
  {
    UInt16 version;
    UInt32 size;
    UInt16 maxConnections;
    Boolean alsSupported; // GSM only feature. if False activeLineNumber should always be 1
    Int16 activeLineNumber;
  }
PhnRadioStateType,* PhnRadioStatePtr;

#define kRadioStateVersion 1

/** 
 *  Line State
 **/
typedef struct
  {
    UInt16 version;
    UInt16 size;    
    Boolean activeLine;
    Boolean divertIndicator;
    Boolean voiceMailIndicator;
  }
PhnLineStateType, * PhnLineStatePtr;
#define kLineStateVersion 1

 extern Err PhnLibGetLineState(UInt16 refNum, UInt16 line, PhnLineStatePtr lineState)
        PHN_LIB_TRAP(PhnLibTrapGetLineState);

 extern Err PhnLibGetRadioState(UInt16 refNum, PhnRadioStatePtr radioState)
            PHN_LIB_TRAP(PhnLibTrapGetRadioState);


 extern Boolean PhnLibCardInfo (UInt16 refNum, CharPtr* manufacturer, CharPtr* model, CharPtr* version, CharPtr* serial)
					PHN_LIB_TRAP(PhnLibTrapCardInfo);

 extern Boolean  PhnLibCardInfoEx (UInt16 refNum, CharPtr * manufacturer,
                                  CharPtr * model, CharPtr * modemSWRev,
                                  CharPtr * esn, CharPtr * prlRev, CharPtr * hostSWRev, CharPtr * modemHWRev, CharPtr *priChecksum)
                  PHN_LIB_TRAP (PhnLibTrapCardInfoEx);

  // <chg 09-10-2002 TRS> prototype changed.  NOTE that previously was declared to
  // return Err, but code returned Boolean, so didn't work anyway.
  extern Err PhnLibConnectionAvailable(UInt16 refNum, PhnConnectionEnum connection, Boolean * pAvailable)
					PHN_LIB_TRAP(PhnLibTrapConnectionAvailable);
	
  extern Err	PhnLibStartVibrate (UInt16 refNum, Boolean pulse, Boolean repeat)
					PHN_LIB_TRAP(PhnLibTrapStartVibrate);   		

  extern Err	PhnLibStopVibrate (UInt16 refNum)
					PHN_LIB_TRAP(PhnLibTrapStopVibrate);

  extern Err	PhnLibErrorRate (UInt16 refNum, WordPtr errorRate)
					PHN_LIB_TRAP(PhnLibTrapErrorRate);

  extern void PhnLibGetErrorText (UInt16 refNum, Err error, CharPtr buffer, UInt16 bufferLen)
					PHN_LIB_TRAP(PhnLibTrapGetErrorText);

  extern UInt16     PhnLibGetCallCountByService (UInt16 refNum,
                                               PhoneServiceClassType service)
                  PHN_LIB_TRAP (PhnLibTrapGetCallCountByService);

  extern Err PhnLibGetEchoCancellation(UInt16 refNum, Boolean* echoCancellationOn)
				PHN_LIB_TRAP(PhnLibTrapGetEchoCancellation);
				
  extern Err PhnLibSetEchoCancellation(UInt16 refNum, Boolean echoCancellationOn)
				PHN_LIB_TRAP(PhnLibTrapSetEchoCancellation);


  extern Err PhnLibGetEquipmentMode(UInt16 refNum, PhnEquipmentMode* equipmentMode)
				PHN_LIB_TRAP(PhnLibTrapGetEquipmentMode);
				
  extern Err PhnLibSetEquipmentMode(UInt16 refNum, PhnEquipmentMode equipmentMode)
				PHN_LIB_TRAP(PhnLibTrapSetEquipmentMode);

 extern Err      PhnLibGetHeadsetConnectedInfo (UInt16 refNum, Boolean * headsetConnected)
      PHN_LIB_TRAP (PhnLibTrapGetHeadsetConnectedInfo);

  extern Err	PhnLibGetMicrophone (UInt16 refNum, Int16* gain)
					PHN_LIB_TRAP(PhnLibTrapGetMicrophone);

  extern Err    PhnLibSetMicrophone (UInt16 refNum, Int16 gain)
				PHN_LIB_TRAP(PhnLibTrapSetMicrophone);

  extern Err PhnLibGetPhoneCallStatus(UInt16 refNum, UInt32* phnFlags)
					PHN_LIB_TRAP(PhnLibTrapGetPhoneCallStatus);

  extern Err      PhnLibMute (UInt16 refNum, Boolean toMute)
                  PHN_LIB_TRAP (PhnLibTrapMute);

  extern Err      PhnLibIsCallMuted (UInt16 refNum, Boolean * isMute)
                  PHN_LIB_TRAP (PhnLibTrapIsCallMuted);

  extern Boolean  PhnLibIsPhoneActivated (UInt16 refNum)
                  PHN_LIB_TRAP (PhnLibTrapIsPhoneActivated);

  extern Err      PhnLibMiscDebugInfo (UInt16 refNum, Boolean bSet, VoidPtr
                                       debugInfoP, UInt16 infoLen)
                  PHN_LIB_TRAP (PhnLibTrapMiscDebugInfo);




#endif
