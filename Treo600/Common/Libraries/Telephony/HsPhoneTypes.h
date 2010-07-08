/**
 * \file HsPhoneTypes.h
 *
 * Telephony data types that are common between ARM and 68K
 *
 * \license
 *
 *    Copyright (c) 2002 Handspring Inc., All Rights Reserved
 *
 * \author Arun Mathias
 *
 * $Id:$
 *
 *****************************************************************************/
#ifndef __HS_PHONE_TYPES_H__

#define __HS_PHONE_TYPES_H__

#include <PalmTypes.h>
/******************************************************************************
 * Defines 
 *****************************************************************************/
/* Type and creator of CDMA and GSM phone libraries.  */
#define phnLibDbType			'libr'       /**< Phone Library type  */

#define phnLibCDMADbCreator		hsFileCCDMAPhoneLib      /**< CDMA Library creator  */
#define phnLibCDMADbName			"Phone Library"      /**< CDMA Library database name  */
#define phnLibCDMAName				"PhoneLib.prc"       /**< CDMA Library name  */

#define phnLibGSMDbCreator		hsFileCGSMPhoneLib             /**< GSM Library creator  */
#define phnLibGSMDbName			"Phone Library"                /**< GSM Library database name  */
#define phnLibGSMName				"GSMLibrary.lib"        /**< GSM Library name  */


#define phnVoiceCall1Active	  0x0001 /**< There is a voice call active on line1  */
#define phnVoiceCall2Active	  0x0002 /**< There is a voice call active on line2 */
#define phnCSDCallActive	  0x0004 /**< There is a data call currently active */
										 // Note: Actually the virtual modem has
										 //	control but does not neccessarily
										 //	have an active data call
#define phnGPRSCallActive	  0x0008 /**< There is a GPRS (GSM) session active  */
#define phnPacketDataCallActive   0x0008 /**< There is an active 1X (CDMA) call  */
#define phnPacketDataCallDormant  0x0010 /**< There is a dormany 1X (CDMA) call  */


/* CDMA Threshold level for signal bar (based on Generic Handset requirement)*/
#define maxDBm4signalLevel0     105	/**<  will display no bar, mid percent = 10 */
#define maxDBm4signalLevel1     95	/**<  will display 1 bar, mid percent = 30 */
#define maxDBm4signalLevel2     85	/**<  will display 2 bars, mid percent = 50 */
#define maxDBm4signalLevel3     75	/**<  will display 3 bars, mid percent = 70 */ 

/* if below maxDBm4signalLevel3 then display 4 bars, mid percent = 90
Threshold ecio level for signal bar (based on Generic Handset requirement) */
#define maxDB4ecioLevel0     15	/**<  will display no bar */
#define maxDB4ecioLevel1     13	/**<  will display 1 bar */
#define maxDB4ecioLevel2     11	/**<  will display 2 bars */
#define maxDB4ecioLevel3     9	/**<  will display 3 bars */

#define phnVolumeMin		0       /**< Minimum volume level */
#define phnVolumeMax		7       /**< Maximum volume level */


/************************************************************
 * Enumerations and Typedefs
 *************************************************************/
#define phnLibUnknownID		    0xff000000  /**< Description  */
#define phnLibNoLookupNeededID	0xff000001  /**< Description  */
#define phnLibFtrNumResetFlag   10


typedef UInt16		PhnConnectionID;   /**< Connection ID  */
typedef UInt32		PhnDatabaseID;     /**< Database ID  */
typedef VoidHand	PhnAddressHandle;  /**< Description  */
typedef VoidHand	PhnAddressList;    /**< Description  */
typedef UInt32		PhnOperatorID;     /**< Description  */


/******************************************************************************
 * Enumerations
 *****************************************************************************/
/**
 * Classes of service for which applications can register
 **/
enum _PhoneServiceClassType
  {
    phnServiceVoice = 1,		// 0x0001
    phnServiceSMS = 2,			// 0x0002
    phnServiceActivation = 4,	// 0x0004
    phnServiceData = 8,			// 0x0008
    phnServiceIOTA = 16,		// 0x0010
	phnServiceSIMToolkit = 32,  // 0x0020
    phnServiceAFLT = 64,		// 0x0040
    phnServiceMisc = 128,		// 0x0080
	phnServiceEssentials = 256,	// 0x0100
    phnServiceMMS = 512,      // 0x200
    phnServiceAll = phnServiceVoice | phnServiceSMS | phnServiceAFLT |
                    phnServiceData | phnServiceActivation | phnServiceMisc | phnServiceIOTA |
					phnServiceEssentials | phnServiceSIMToolkit | phnServiceMMS,
    phnServiceMax = 0xFFFF        // Reserved.
  };

typedef UInt16 PhoneServiceClassType;

#define isValidPhoneServiceClassType(s) ((s & phnServiceAll) != 0)

/**
 * Phone address fields
 **/
typedef enum {
	phnAddrFldPhone,
	phnAddrFldFirstName,
	phnAddrFldLastName
} _PhnAddressField;

#define isValidPhnAddressField(a) ((a >= phnAddrFldPhone) && (a <= phnAddrFldLastName))

// make sure that size of enum is same across all compilers
typedef UInt8 PhnAddressField;

/**
 * GSM CLIR Mode
 **/
typedef enum  {
	gsmDialCLIRDefault, 
	gsmDialCLIRTemporaryInvocation, 
	gsmDialCLIRTemporarySuppression
} _GSMDialCLIRMode;

#define isValidGSMDialCLIRMode(d) ((d >= gsmDialCLIRDefault) && (d <= gsmDialCLIRTemporarySuppression))

// make sure that size of enum is same across all compilers
typedef UInt8 GSMDialCLIRMode;


/**
 * Power state of the radio
 **/
enum _PhnPowerType
  {
    phnPowerOff,
    phnPowerOn,
	phnPowerStartCharging, 
	phnPowerStopCharging, 
	phnPowerLow,
    phnPowerSave                // Modem goes to deep sleep after failing to search for service
  };

typedef UInt8 PhnPowerType;

#define isValidPhnPowerType(p) (p <= phnPowerSave)
//#define isValidPhnPowerType(p) ((p >= phnPowerOff) && (p <= phnPowerSave))

/**
 * Status of the SIM on GSM radio only
 **/
enum _GSMSIMStatus {
	simMissing, simFailure, simWrong, simNotReady, simReady,
	simUnknown, simPresent			// <chg 05-05-2002 TRS> bug # 13072
};

typedef UInt8 GSMSIMStatus;


// LifeTimer Enums
enum
{
  lifeTimeVoice,
  lifeTimeData
};

typedef UInt8 PhnLifeTimer;

/**
 *  Possible roaming status'
 *  GSM devices only use first two 
 **/
typedef enum 
  {
    PhnRoamStatusOff,
    PhnRoamStatusOn,
    PhnRoamStatusBlink,
    PhnRoamStatusEnhancedIndicator  /**< If this is the roaming status, call
					  PhnLibGetEnhancedRoamIndicator  */
  }  
PhnRoamStatus;

// Currently on the GSM side there is no way for the control channel to know
// that a data call has gone active. To resolove this issue there are two
// posibble solutions. 
//
// 1. Have the radio send an unoslicted event accorss all channels to indicate a
//    data call has gone active
// 2. Have the NetLib post a notification to the GSM Library that a data call is
//	  going active. 

#endif // ifndef __HS_PHONE_TYPES_H__
