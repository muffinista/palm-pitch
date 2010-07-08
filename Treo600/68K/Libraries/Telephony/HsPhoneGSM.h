/**
 * \file 68K/Libraries/Telephony/HsPhoneGSM.h
 *
 * Header File for Phone Library API ---- GSM CATEGORY
 *
 * All implementations of the Handspring Phone Library support a common API. 
 * This API is broken up into various categories for easier management.  This file
 * defines the SMS category.  These API calls are used for features that only apply
 * to GSM networks.
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

#ifndef HS_PHONEGSM_H
#define HS_PHONEGSM_H
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

#define		GSMLockSelectorOperatorLock		('PN')  /**< Description  */
#define		GSMLockSelectorProviderLock		('PP')  /**< Description  */


//<chg 09-16-2002 TRS> moved from gsmlibrary.h
#define phnNetPrefGPRSPDPContextID  1

// <chg 09-12-2002 TRS> DUO CLEANUP - moved from gsmlibrary.h (for now)
// This is a prebuilt database.  So if this name changes, need to make
// sure that the following references to the Ring Tone database name
// are updated as well:
// 1. In the Viewer/Prebuilt directory, update the actual name
//	  of the pdb file
// 2. In the GSMLibrary Makefile, update ringTonePdbName
// 3. In GSMLibraryCommon.rcp, update the DATA 'dflt' 1 resource
// 4. In PhoneLib.h
#define GSMLibRingsDbName			"System Ring Tones"  /**< Name of GSM Ring
														   Tone DB  */

// Return if the lineNumber is unknown.  Maybe returned from the PhnLibGetRadioState
// if the activeLineNumber as not been determined yet.
#define kLineNumberUnknown 0

/**
 * Item description here
 **/
typedef struct  {
	UInt16	firstEntry;
	UInt16	lastEntry;
	UInt16	maxNameLength;
	UInt16	maxNumberLength;
} PhnPhoneBookInfoType, *PhnPhoneBookInfoPtr;


// SIM Application Toolkit's data types
// type of request/respond we are sending
/**
 * Item description here
 **/
typedef enum {
	kSATSelectMainMenuItem,
	kSATClearText,
	kSATSetInkey,
	kSATSetInput,
	kSATMakeCall,
	kSATSelectItem = 6,
	kSATCancel	   = 95,
	kSATUnknownNotification,
	kSATApplicationBusy,
	kSATUserNotResponse,
	kSATEndSession
} SATRequestType;

// decision we are sending to SIM
/**
 * Item description here
 **/
typedef enum {
	kSATSessionAborted,
	kSATItemSelected,
	kSATHelpRequested,
	kSATNavigateBack
} SATDecisionType;

// type of notification sent by SAT
/**
 * Item description here
 **/
typedef enum {
	kSATMainMenuAvailable,
	kSATDisplayText,
	kSATGetInkey,
	kSATGetInput,
	kSATSetupCall,
	kSATPlayTone,
	kSATDisplaySubmenus,
	kSATRefresh,			// application do not get this notification
	kSATSendSS,
	kSATSendSMS,
	kSATSendUSSD,
	kSATTimeout		= 98,
	kSATSessionEnd	= 99
} SATNotificationType;

#define isValidSATNotificationType(s) (((s >= kSATMainMenuAvailable) && (s <= kSATSendUSSD)) \
              || (s == kSATTimeout) || (s == kSATSessionEnd))

/**
 * Item description here
 **/
typedef enum PhnGPRSPDPType
{
  phnGPRSPDPTypeIP = 1,
  phnGPRSPDPTypePPP = 2
} PhnGPRSPDPType;

#define isValidPhnGPRSPDPType(t) ((t >= phnGPRSPDPTypeIP) && (t <= phnGPRSPDPTypePPP)) 

/**
 * Item description here
 **/
typedef enum PhnGPRSQOSType
{
  kGPRSQOSTypeRequired = 1,
  kGPRSQOSTypeMinimum = 2
} PhnGPRSQOSType;

#define isValidPhnGPRSQOSType(t) ((t >= kGPRSQOSTypeRequired) && (t <= kGPRSQOSTypeMinimum))

/**
 * Used when we get a list of context that are currently
 * stored on the radio.
 **/
typedef struct PhnGPRSPDPContextType
{
  UInt16 contextId;
  PhnGPRSPDPType pdpType;
  char*	 apn;
  char*	 pdpAddr;
  UInt16 pdpDataCompression;  /**< 0 means OFF, 1 means ON  */
  UInt16 pdpHdrCompression;
} PhnGPRSPDPContextType;

/**
 * This is a list node that is returened when we
 * retreive the current list of PDP contexts stored
 * on the device
 **/
typedef struct PhnGPRSPDPContextListNodeType
{
  struct PhnGPRSPDPContextType type;
  struct PhnGPRSPDPContextListNodeType* nextP;
} PhnGPRSPDPContextListNodeType;

/**
 * Item description here
 **/
typedef enum  {
	gsmMessagesConfirmMove, gsmMessagesCantReceive
} GSMSIMMessagesDialogKind;

#define isValidGSMSIMMessagesDialogKind(d) ((d >= gsmMessagesConfirmMove) && (d <= gsmMessagesCantReceive))

/**
 * Item description here
 **/
enum GSMSATEventMenuFlag {
	phnSATEventMenuFlagHelp		= 1,// help is available
	phnSATEventMenuFlagNextAct	= 2	// nextAction is valid 
};

// Possible values of format for PhnSATEventGetInkey and PhnSATEventGetInput
/**
 * Item description here
 **/
enum GSMSATEventInputFormatEnum {
	phnSATEventInputFormatDigit		= 0,  // Get Inkey or Get Input
										  //   0-9, #, *, or +
	phnSATEventInputFormatSMSChar	= 1,  // Get Inkey or Get Input
										  //   SMS character set
	phnSATEventInputFormatUCS2		= 2,  // Get Inkey or Get Input
	phnSATEventInputFormatUnpacked	= 3,  // Get Input only
	phnSATEventInputFormatPacked	= 4,  // Get Input only

	phnSATEventInputFormatYesNo		= 5,  // Get Inkey or Get Input


	// KEEP THIS ONE AT THE END
	phnSATEventInputFormatUnknown	= 255
};


enum GSMATEventInputEchoModeEnum {
	// Show input as entered
	phnSATEventInputEchoModeShowInput = 0,

	// Display bullets or boxes instead of entered characters
	phnSATEventInputEchoModeHideInput = 1
};


/**
 * Special response values for PhnSATEventGetInkey (besides a single
 * character)
 **/
#define phnSATInkeyResponseValueYes		((UInt32)'YES_')
#define phnSATInkeyResponseValueNo		((UInt32)'NO__')


// Possible values of timeUnit for PhnSATEventPlayTone
/**
 * Item description here
 **/
enum GSMSATEventToneTimeUnitEnum {
	phnSATEventToneTimeUnitMinutes		= 0,  // Duration specified in minutes
	phnSATEventToneTimeUnitSeconds		= 1,  // Duration specified in seconds
	phnSATEventToneTimeUnitDeciSeconds	= 2   // Duration specified in 1/10 seconds
};

// Possible values of toneType for PhnSATEventPlayTone
/**
 * Item description here
 **/
enum GSMSATEventToneTypeEnum {
	phnSATEventToneTypeNoneSpecified = 0xFFFF,	  // Meand just do a normal beep...
	phnSATEventToneTypeDial = 0,
	phnSATEventToneTypeBusy = 1,
	phnSATEventToneTypeCongestion = 2,
	phnSATEventToneTypeRadioAck = 3,
	phnSATEventToneTypeDropped = 4,
	phnSATEventToneTypeError = 5,
	phnSATEventToneTypeCallWaiting = 6,
	phnSATEventToneTypeRinging = 7,
	phnSATEventToneTypeGeneralBeep = 8,
	phnSATEventToneTypePositiveBeep = 9,
	phnSATEventToneTypeNegativeBeep = 10
};

#define isValidGSMSATEventToneTypeEnum(x) (((x >= phnSATEventToneTypeDial) && (x <= phnSATEventToneTypeNegativeBeep)) || (x == phnSATEventToneTypeNoneSpecified))


/**
 * Possible values of callType for PhnSATEventSetupCall
 **/
enum GSMSATEventSetupCallCallTypeEnum {
	phnSATEventSetupCallCallTypeVoice = 0,  /**<  SIM wants to set up a voice call  */
	phnSATEventSetupCallCallTypeData  = 1,  /**<  SIM wants to set up a data call */
	phnSATEventSetupCallCallTypeFax	  = 2   /**<  SIM wants to set up a fax  */
};

#define isValidGSMSATEventSetupCallCallTypeEnum(x) ((x >= phnSATEventSetupCallCallTypeVoice) && (x <= phnSATEventSetupCallCallTypeFax))



  extern Err PhnLibSetActiveLine(UInt16 refNum, Int16 line)
          PHN_LIB_TRAP(PhnLibTrapSetActiveLine);

  extern Err PhnLibGetFDNList(UInt16 refNum, PhnAddressList* aList, PhnPhoneBookInfoPtr info)
          PHN_LIB_TRAP(PhnLibTrapGetFDNList);

  extern Err PhnLibSetFDNEntry (UInt16 refnum, UInt16 index, char* name, char * number)
				PHN_LIB_TRAP(PhnLibTrapSetFDNEntry);

  extern Err PhnLibGetPhoneBook (UInt16 refNum, PhnAddressList* numbers, PhnPhoneBookInfoPtr info)
				PHN_LIB_TRAP(PhnLibTrapGetPhoneBook);

  extern Err PhnLibSetPhoneBook (UInt16 refnum, PhnAddressList numbers)
				PHN_LIB_TRAP(PhnLibTrapSetPhoneBook);

  extern Err PhnLibSetPhoneBookEntry (UInt16 refnum, UInt16 index, char* name, char * number)
				PHN_LIB_TRAP(PhnLibTrapSetPhoneBookEntry);

  extern UInt32 PhnLibGetPhoneBookIndex(UInt16, PhnAddressHandle address)
					PHN_LIB_TRAP(PhnLibTrapGetPhoneBookIndex);

  extern Err	PhnLibSendUSSD (UInt16 refNum, CharPtr cmd)
					PHN_LIB_TRAP(PhnLibTrapSendUSSD);


  // SIM Application Toolkit
  extern Err PhnLibSATGetMainMenu(UInt16 refNum, MemHandle* menuHandlePtr)
				PHN_LIB_TRAP(PhnLibTrapSATGetMainMenu);

  extern Err PhnLibSATSendRequest(UInt16 refNum, SATRequestType request, SATDecisionType decision, UInt32 data, UInt32 length)
				PHN_LIB_TRAP(PhnLibTrapSATSendRequest);

  extern Err PhnLibSATEndSession(UInt16 refNum)
				PHN_LIB_TRAP(PhnLibTrapSATEndSession);



  extern Boolean PhnLibSIMInfo (UInt16 refNum, CharPtr* imsi)
				PHN_LIB_TRAP(PhnLibTrapSIMInfo);

  extern GSMSIMStatus PhnLibGetSIMStatus(UInt16 refNum)
				PHN_LIB_TRAP(PhnLibTrapGetSIMStatus);

  extern Boolean PhnLibGPRSAttached (UInt16 refNum)
					PHN_LIB_TRAP(PhnLibTrapGPRSAttached);

  extern Err PhnLibGPRSPDPContextDefine(UInt16 refNum, 
	UInt16 contextId, 
	PhnGPRSPDPType pdpType, const char* apn, UInt16 apnLen, 
	const char* pdpAddr, UInt16 pdpAddrLen, 
	UInt16 pdpDataCompression, UInt16 pdpHdrCompression)
				PHN_LIB_TRAP(PhnLibTrapGPRSPDPContextDefine);

  extern Err PhnLibGPRSPDPContextListConstruct(UInt16 refNum, struct PhnGPRSPDPContextListNodeType** listHeadPP)
			    PHN_LIB_TRAP(PhnLibTrapGPRSPDPContextListConstruct);

  extern Err PhnLibGPRSPDPContextListDestruct(UInt16 refNum, struct PhnGPRSPDPContextListNodeType** headNodePP)
				PHN_LIB_TRAP(PhnLibTrapGPRSPDPContextListDestruct);

  extern Err PhnLibGPRSQualityOfServiceGet(UInt16 refNum, PhnGPRSQOSType qosType, UInt16 contextId, 
	UInt16* precedence, UInt16* delay, UInt16* reliability, UInt16* peakThroughput,
	UInt16* meanThroughput)
				PHN_LIB_TRAP(PhnLibTrapGPRSQualityOfServiceGet);

  extern Err PhnLibGPRSQualityOfServiceSet(UInt16 refNum, PhnGPRSQOSType qosType, UInt16 contextId, 
	UInt16 precedence, UInt16 delay, UInt16 reliability, UInt16 peakThroughput,
	UInt16 meanThroughput)
				PHN_LIB_TRAP(PhnLibTrapGPRSQualityOfServiceSet);




#endif
