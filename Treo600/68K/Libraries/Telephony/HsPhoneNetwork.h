/**
 * \file 68K/Libraries/Telephony/HsPhoneNetwork.h
 *
 * Header File for Phone Library API ---- NETWORK CATEGORY
 *
 * All implementations of the Handspring Phone Library support a common API. 
 * This API is broken up into various categories for easier management.  This file
 * defines the SMS category.  These API calls are used to interact with the wireless network.
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

#ifndef HS_PHONENETWORK_H
#define HS_PHONENETWORK_H
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

#define	kMaxPhoneNumberLen	16  /**< Max length of phone number  */

#define minPasswordLen					4   /**< Phone password/PIN minimum length  */
/** \todo {AGM : DOLATER CDMA max password is 4, so we should have a CDMA and
GSM max passwordText} */
#define maxPasswordLen					8  /**< Phone password/PIN maximum length  */


#define phnEnhancedRoamIndMaxLength  40

/**
 * GSM CLIP Subscription Status
 **/
typedef enum {
	gsmCLIPNotProvisioned,
	gsmCLIPProvisioned,
	gsmCLIPUnknown
} GSMCLIPStatus;


/**
 * Item description here
 **/
typedef enum {
	clirNotProvisioned,			// sent: restricted presentation of the calling line
	clirProvisioned,			// not sent: don't restrict presentation of the calling line
	clirUnknown,				// status not available
	clirTemporaryRestricted,	// not sent, override allowed
	clirTemporaryAllowed		// sent: override allowed
} PhnCLIRStatus;

#define isValidPhnCLIRStatus(s) ((s >= clirNotProvisioned) && (s <= clirTemporaryAllowed))


/**
 * GSM CLIR Display Status
 **/
typedef enum {
  gsmCLIRSubscription,    //presentation indicator is used according to the subscription of the CLIR service
  gsmCLIRInvocation,
  gsmCLIRSuppression
} GSMCLIRDisplayStatus;

#define isValidGSMDialClirStatus(d) ((d >= gsmDialCLIRNotProvisioned) && (d <= gsmDialCLIRTemporaryAllowed))

/**
 * Phone operator status
 **/
typedef enum {
	phnOpUnknown, 
	phnOpAvailable, 
	phnOpCurrent, 
	phnOpForbidden
} PhnOperatorStatus;

#define isValidPhnOperatorStatus(s) ((s >= phnOpUnknown) && (s <= phnOpForbidden))



/**
 * Item description here
 **/
typedef enum
  {
    kBoxVoice, kBoxTelefax, kBoxEMail, kBoxOther, kBoxData,
    PhnMsgBoxTypeMAX      // THIS MUST BE LAST ENTRY.... NOT A VALID VALUE
    // other values reserved for future expansion
  }
PhnMsgBoxType;

#define isValidPhnMsgBoxType(n) (n < PhnMsgBoxTypeMAX)

/**
 * Item description here
 **/
typedef struct
  {
    Boolean         indicatorOn;
    PhnMsgBoxType   type;
    Int16           messageCount;
    Int16           lineNumber;
  }
PhnMsgBoxDataType;




/**
 * Operator info
 **/
#define MAX_LONGOPERATORNAME_LENGTH 24
#define MAX_SHORTOPERATORNAME_LENGTH 16
typedef struct
  {
	PhnOperatorStatus	status;
  PhnOperatorID   id;         /**< Not really used since CDMA just allows one service provider */
  char longname[MAX_LONGOPERATORNAME_LENGTH+1];     // name + terminating NULL char
  char shortname[MAX_SHORTOPERATORNAME_LENGTH+1];   // name + terminating NULL char
  Boolean         isRoaming;  /**< in sync with the current roaming status */
  }
PhnOperatorType;

/**
 * Operator list
 **/
typedef struct
  {
    short           count;
    PhnOperatorType opData[1];
  }
PhnOperatorListType,* PhnOperatorListPtr;

/**
 * Item description here
 **/
typedef enum {
	gsmRegModeAutomatic, gsmRegModeManual, gsmRegModeDeregister, gsmRegModeFormat,
	gsmRegModeManualAutomatic
} GSMRegistrationMode;

#define isValidGSMRegistrationMode(r) (r <= gsmRegModeManualAutomatic)

// Phone call forwarding reason
/**
 * Item description here
 **/
typedef enum {
	phnForwardUnconditional,
	phnForwardOnBusy,
	phnForwardOnNoReplay,
	phnForwardOnNotReachable,
	phnForwardTelefax,
	phnForwardData,
	phnForwardCancelAll,
	phnForwardConditionalAll,
	phnForwardLast
} PhnForwardType;

#define isValidPhnForwardType(f) (f < phnForwardLast)

/**
 * Phone call barring options
 **/
typedef enum {
	phnBarOutNone,
	phnBarOutAll,
	phnBarOutInternational,
	phnBarOutInternationalExceptHome,

	phnBarInNone,
	phnBarInAll,
	phnBarInWhenRoaming,
	phnBarAll

} PhnBarFacilityType, * PhnBarFacilityPtr;

#define isValidPhnBarFacilityType(b) (b <= phnBarAll)

/**
 * CDMA Roam Preferences
 **/
typedef struct
  {
    Boolean         roamCallGuardEnable;
    Boolean         roamRingerEnable;
    UInt8           roamRingerID;
  }
PhnRoamPrefInfoType,* PhnRoamPrefInfoPtr;

/**
 * Item description here
 **/
typedef enum  {
	registrationNone, registrationHome, registrationSearch, registrationDenied,
	registrationUnknown, registrationRoaming
} PhnRegistrationStatus;

#define isValidPhnRegistrationStatus(r) (r <= registrationRoaming)
//#define isValidPhnRegistrationStatus(r) ((r >= registrationNone) && (r <= registrationRoaming))

/**
 *  Phone call forwarding mode
 **/
typedef enum {
	phnForwardModeDisable,
	phnForwardModeEnable,
	phnForwardModeInterrogate,
	phnForwardModeRegistration,
	phnForwardModeErasure
} PhnForwardModeType;

#define isValidPhnForwardModeType(f) (f <= phnForwardModeErasure)
/**
 * MMI Action Code
 **/
typedef enum
{
  mmiActionNoAction     = 0,
  mmiActionActivate     = 0x01,
  mmiActionDeactivate   = 0x02,
  mmiActionInterrogate  = 0x04,
  mmiActionRegister     = 0x08,
  mmiActionErasure      = 0x10,
  mmiActionUnlock       = 0x20,    
  mmiActionHandspring   = 0x40
}
PhnMMIActionCode;

/**
 * MMI Service Code
 **/
typedef enum
{
	mmiServiceInvalid = 0,
	mmiServiceChangePIN,
	mmiServiceChangePIN2,
	mmiServiceUnlockPIN,
	mmiServiceUnlockPIN2,
	mmiServiceIMEI,
	mmiServiceCallerId,
	mmiServiceNumberSent,
	mmiServiceCOLP,
	mmiServiceCOLR,
	mmiServiceCallWaiting,
	mmiServiceForwardUnconditional,
	mmiServiceForwardBusy,
	mmiServiceForwardNoReply,
	mmiServiceForwardNotReachable,
	mmiServiceForwardAll,	
	mmiServiceForwardConditionalAll,	
	mmiServiceBAOC,				            // bar all outging calls
	mmiServiceBAOIC,				          // bar all outging international calls
	mmiServiceBAOICX,				          // bar all outging international calls expect home 
	mmiServiceBAIC,				            // bar all incoming calls
	mmiServiceBAICR,				          // bar all incoming calls while roaming
	mmiServiceAllBarringServ,		      // bar all services
	mmiServiceAllOutBarringServ,      // bar all outgoing services
	mmiServiceAllInBarringServ,       // bar all incoming services
	mmiServiceChangeBarPwd,		        // Change barring password
	mmiServiceUSSD,
	mmiServicePhoneNumber,
	mmiServiceCallControl,
	mmiServiceSelectorOperatorLock,
	mmiServiceSelectorProviderLock,
	mmiServiceUnimplemented		        // defined by GSM standard but not implemented in our phone
}
PhnMMIServiceCode;

/**
 * Call Control Codes
 **/
typedef enum {
  mmiControlReleaseAllHeld = 0,
  mmiControlReleaseAllActive,
  mmiControlReleaseCallx,
  mmiControlSwap,
  mmiControlActivateCallx,
  mmiControlConference,
  mmiControlTransfer
}PhnCallControlType;

/************************************************************
 *  Structs
 *************************************************************/

#define kMaxMMISequenceLen 64

/**
 * Telephone Service Types
 **/
typedef enum {
  phnTeleserviceUnknown = 0,
	phnTeleserviceVoice = 1,
	phnTeleserviceData = 2,
	phnTeleserviceFax = 4,
	phnTeleserviceSMS = 8,	
  phnTeleserviceDataCircSync = 16,
  phnTeleserviceDataCircAsync = 32,
  phnTeleserviceDedicatedPack = 64,
  phnTeleserviceDedicatedPAD = 128
} PhnTeleserviceType;


/**
 * MMI Decode struct
 **/
typedef struct
{
  UInt16  size;
  PhnMMIActionCode  actionCode;
  PhnMMIServiceCode  serviceCode;
  Boolean sendHit;
  char text[kMaxMMISequenceLen+1];
  union
  {
    struct
    {      
      char	number[kMaxPhoneNumberLen+1];
      PhnTeleserviceType type;
      UInt16  time;
    } mmiForwarding;
    struct
    {
      PhnTeleserviceType type;
      char pwd[maxPasswordLen+1];
    } mmiBarring;
    struct
    {
      PhnTeleserviceType type;
    } mmiCallWaiting;
    struct
    {
      char oldPwd[maxPasswordLen+1];
      char newPwd[maxPasswordLen+1];
      char repeatNewPwd[maxPasswordLen+1];
    } mmiPassword;
    struct
    {
      PhnCallControlType action;
      PhnConnectionID id;
    } mmiCallControl;
    struct
    {
      char	number[kMaxPhoneNumberLen+1];
      GSMDialCLIRMode mode;
    } mmiPhoneNumber;

  } data;
  
}
PhnMMIEntryType, *PhnMMIEntryPtr;

#define kMaxImeiLen 24

/**
 * MMI result struct
 **/
typedef struct
{
  UInt16 size;
  PhnMMIServiceCode  serviceCode;
  union
  {
    struct
    {      
      Boolean enabled;
      char	number[kMaxPhoneNumberLen+1];
      PhnTeleserviceType type;
      UInt16  time;
    } mmiForwarding;
    struct
    {
      Boolean enabled;
      PhnTeleserviceType type;      
    } mmiBarring;
    struct
    {
      Boolean enabled;
      PhnTeleserviceType type;
    } mmiCallWaiting;
    struct
    {
      Boolean enabled;
    } mmiCallerID;
    struct
    {
      GSMCLIRDisplayStatus displayStatus;
      PhnCLIRStatus subscriptionStatus;
    } mmiNumberSent;
    struct
    {
      Boolean enabled;
    } mmiColp;
		struct
    {
      Boolean enabled;
    } mmiColr;
    struct
    {
      char imei[kMaxImeiLen+1];
    } mmiIMEI;
    
  } data;  
}
PhnMMIResultType, *PhnMMIResultPtr;


// Phone Library functions



extern Err PhnLibBoxInformation(UInt16 refNum, PhnMsgBoxDataType* data)
			PHN_LIB_TRAP(PhnLibTrapBoxInformation);

extern Err PhnLibBoxInformationEx (UInt16 refNum, PhnMsgBoxDataType *
                                data, Boolean bGetInfo)
			PHN_LIB_TRAP (PhnLibTrapBoxInformationEx);

extern Err PhnLibGetBoxNumber(UInt16 refNum, PhnMsgBoxType type, UInt16 line, CharPtr * number)
			PHN_LIB_TRAP(PhnLibTrapGetBoxNumber);

extern Err PhnLibHomeOperatorID (UInt16 refNum, char *buffer, Int16* bufferSizeP)
			PHN_LIB_TRAP(PhnLibTrapHomeOperatorID);

extern Err PhnLibCurrentOperatorID (UInt16 refNum, char *buffer, Int16* bufferSizeP)
			PHN_LIB_TRAP(PhnLibTrapCurrentOperatorID);

    // Used only by the phone app, so change CDMA function to match this prototype -- ignore mode parameter 
  extern Err PhnLibCurrentOperator (UInt16 refNum, PhnOperatorID* id, CharPtr* name, GSMRegistrationMode* mode)
				PHN_LIB_TRAP(PhnLibTrapCurrentOperator);
  
  				
  // Use this as base -- CDMA function just returns phnErrNotSupported
  extern Err PhnLibSetOperator (UInt16 refNum, PhnOperatorType* op, GSMRegistrationMode	regMode)
				PHN_LIB_TRAP(PhnLibTrapSetOperator);

    // Change to return err, and add PhnRoamStatus parameter 
  extern Err PhnLibRoaming(UInt16 refNum, PhnRoamStatus * roamStatus)
				PHN_LIB_TRAP(PhnLibTrapRoaming);

  extern Boolean PhnLibRegistered (UInt16 refNum)
					PHN_LIB_TRAP(PhnLibTrapRegistered);

  extern Err	PhnLibSignalQuality (UInt16 refNum, UInt16 * quality)
					PHN_LIB_TRAP(PhnLibTrapSignalQuality);

  extern Err   PhnLibSignalQualityEx (UInt16 refNum, UInt16 * quality, Boolean *bEcio, UInt16 *ecioLvl)
          PHN_LIB_TRAP (PhnLibTrapSignalQualityEx);  

  extern Err PhnLibCurrentProvider(UInt16 refNum, char** name)
				PHN_LIB_TRAP(PhnLibTrapCurrentProvider);

  extern Err PhnLibGetOperatorList (UInt16 refNum, PhnOperatorListPtr * list)
				PHN_LIB_TRAP(PhnLibTrapGetOperatorList);

  extern Err PhnLibGetOwnNumbers (UInt16 refNum, PhnAddressList* ownNumbers)
				PHN_LIB_TRAP(PhnLibTrapGetOwnNumbers);

  extern Err PhnLibSetOwnNumbers (UInt16 refnum, PhnAddressList ownNumbers)
				PHN_LIB_TRAP(PhnLibTrapSetOwnNumbers);

  extern Err	PhnLibSetCallWaiting (UInt16 refNum, Boolean enabled)
					PHN_LIB_TRAP(PhnLibTrapSetCallWaiting);

  extern Err	PhnLibGetCallWaiting (UInt16 refNum, BooleanPtr enabled)
					PHN_LIB_TRAP(PhnLibTrapGetCallWaiting);

  extern Err PhnLibSetCLIP (UInt16 refNum, Boolean enable)
				PHN_LIB_TRAP(PhnLibTrapSetCLIP);

  extern Err PhnLibGetCLIP(UInt16 refNum, Boolean* enabled)
				PHN_LIB_TRAP(PhnLibTrapGetCLIP);

    // Used only by the phone app, so change CDMA function to match this prototype
  extern Err	PhnLibGetForwarding (UInt16 refNum, PhnForwardType condition, PhnAddressHandle * destination)
					PHN_LIB_TRAP(PhnLibTrapGetForwarding);

  extern Err PhnLibSetCLIR (UInt16 refNum, GSMDialCLIRMode mode)
				PHN_LIB_TRAP(PhnLibTrapSetCLIR);

  extern Err PhnLibGetCLIR (UInt16 refNum, GSMDialCLIRMode* mode, PhnCLIRStatus* status)
				PHN_LIB_TRAP(PhnLibTrapGetCLIR);

  extern Err PhnLibSetBarring (UInt16 refNum, PhnBarFacilityType facility, CharPtr password)
					PHN_LIB_TRAP(PhnLibTrapSetBarring);

  extern Err PhnLibGetBarring (UInt16 refNum, PhnBarFacilityType facility, Boolean* enabled)
					PHN_LIB_TRAP(PhnLibTrapGetBarring);

  extern Err PhnLibDeactivateBarring (UInt16 refNum, PhnBarFacilityType facility, CharPtr password)
					PHN_LIB_TRAP(PhnLibTrapDeactivateBarring);

  extern Err PhnLibGetEnhancedRoamIndicator (UInt16 refNum, char * roamTxt)
                PHN_LIB_TRAP(PhnLibTrapEnhancedRoamIndicator);

  extern Err PhnLibGetRoamPrefMode (UInt16 refNum, Boolean * Mode)
                  PHN_LIB_TRAP (PhnLibTrapGetRoamPrefMode);

  extern Err PhnLibSetRoamPrefMode (UInt16 refNum, Boolean Mode)
                  PHN_LIB_TRAP (PhnLibTrapSetRoamPrefMode);

  extern Err PhnLibSetRoamPrefInfo (UInt16 refNum, PhnRoamPrefInfoPtr pInfo)
                  PHN_LIB_TRAP (PhnLibTrapSetRoamPrefInfo);

  extern Err PhnLibGetOperatorLock(UInt16 refNum, UInt16 facilityType, Boolean* enabled)
				PHN_LIB_TRAP(PhnLibTrapGetOperatorLock);

  extern Boolean PhnLibNetworkAvailable (UInt16 refNum)
					PHN_LIB_TRAP(PhnLibTrapNetworkAvailable);

  // GSM and CDMA differ
  // Used only by the phone app, so change CDMA function to match this prototype
  extern Err	PhnLibSetForwarding (UInt16 refNum, PhnForwardType condition, PhnForwardModeType mode, PhnAddressHandle destination)
					PHN_LIB_TRAP(PhnLibTrapSetForwarding);

  extern Err	PhnLibUsableSignalStrengthThreshold (UInt16 refNum, WordPtr threshold)
					PHN_LIB_TRAP(PhnLibTrapUsableSignalStrengthThreshold);

#endif
