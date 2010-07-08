/***************************************************************
 *
 *  Project:
 *	  Carrier Customization Library
 *
 * Copyright info:
 *
 *	  Copyright (c) Handspring 2002 -- All Rights Reserved
 *
 *
 *  FileName:
 *	  CarrierCustomizationLibraryTypes.h
 *
 *  Description:
 *	  This file contains public data types exported by the
 *    Carrier Customization Library
 *
 *	Note:
 *
 *	History:
 *	  11-Dec-2002	dla		Created
 *    16-Dec-2003   dla     Numerous additions for CDMA carrier support
 *
 ****************************************************************/

#ifndef __CARRIER_CUSTOMIZATION_LIBRARY_TYPES_H__
#define __CARRIER_CUSTOMIZATION_LIBRARY_TYPES_H__


#if 0
#pragma mark -------- Constants -------- 
#endif

#define kCCLibType					  'libr'
#define kCarrierCustomizationCLibName "CarrierCustomization.lib"
#define kCarrierListDBName            "CarrierProfiles"
#define kNetworkListDBName            "NetworkProfiles"


// Current library API version number
//  Returned by NetPrefLibVersionGet()
#define CCSMVersionMajor	  0
#define	CCSMVersionMinor	  5
#define CCSMVersionBugFix	  0

#define kSprintMCCMNC         "310000"
#define kVerizonMCCMNC        "310555"
#define kBellMobilityMCCMNC   "310505"


typedef void *CCSMCarrierHandle;  /* pointer type to hold the carrier object */

/**
 * Enumeration for the type of carrier settings.
 * The following are applicable to CDMA as well.
 *
 *
 * We want to keep the groups together.
 * This helps keep track of which structure the setting resides in.
 */
enum
{
  kCCSMSettingsSystemReserved,         /**< system settings place holder */

  //                                         <Data type returned> description
  // phone settings
  kCCSMSettingsShowNetworkSelect,      /**< <Boolean> enable/disable network select */
  kCCSMSettingsIndicateRoaming,        /**< <Boolean> enable/disable roaming indicator */
  kCCSMSettingsEditableMSISDN,         /**< <Boolean> User editable MSISDN */
  kCCSMSettingsShowEmergencyMode,      /**< <Boolean> enable/disable emergency mode indicator */
  kCCSMSettingsCarrierMSISDN,          /**< <char *>  carrier MSISDN */
  kCCSMSettingsRadioBand,              /**< <UInt32>  radio band to start search with */
  kCCSMSettingsVoiceMailNumber,        /**< <char *>  carriers voice mail number */

  // Messaging settings
  kCCSMSettingsPOP3Server,             /**< <char *>  pop3 server -- will be deprecated */
  kCCSMSettingsSMTPServer,             /**< <char *>  smtp server -- will be deprecated */
  kCCSMSettingsSMSCNumber,             /**< <char *>  smsc number */
  kCCSMSettingsSMSEmailGateway,        /**< <char *>  sms email gateway */
  kCCSMSettingsMMSURL,                 /**< <char *>  MMS URL */
  kCCSMSettingsMMSWAPGateway,          /**< <char *>  MMS WAP gateway */
  kCCSMSettingsMMSPort,                /**< <UInt32>  MMS port number */
  kCCSMSettingsMMSMaxMsgSize,          /**< <UInt32> max MMS message size (kbytes) */

  // Browser settings
  kCCSMSettingsPrimaryProxyServer,          /**< <char *>  Proxy server */
  kCCSMSettingsPrimaryProxyPort,            /**< <UInt32>  Proxy port */
  kCCSMSettingsPrimarySecureProxyServer,    /**< <char *>  Secure proxy server */
  kCCSMSettingsPrimarySecureProxyPort,      /**< <UInt32>  Secure proxy port */
  kCCSMSettingsSecondaryProxyServer,        /**< <char *>  Proxy server */
  kCCSMSettingsSecondaryProxyPort,          /**< <UInt32>  Proxy port */
  kCCSMSettingsSecondarySecureProxyServer,  /**< <char *>  Secure proxy server */
  kCCSMSettingsSecondarySecureProxyPort,    /**< <UInt32>  Secure proxy port */
  kCCMSSettingsPrimaryTrustedDomain,        /**< <char *>  GSM:  Primary trusted domain */
                                            /**< <char *>  CDMA: phone:downloadserver.url */

  kCCMSSettingsSecondaryTrustedDomain,      /**< <char *>  GSM Only: Secondary trusted domain */
  kCCMSSettingsUAProfilingURL,              /**< <char *>  UA Profiling URL */
  kCCSMSettingsHTTPHeaders,                 /**< <char *>  carrier specific HTTP headers to send */
  kCCSMSettingsNAIHeaderFormat,             /**< <char *>  header format to send NAI (see sprintf format) */
  kCCSMSettingsMSISDNHeaderFormat,          /**< <char *>  header format to send MSISDN (see sprintf format) */
  kCCSMSettingsEncryptMSISDN,               /**< <Boolean> encrypt MSISDN header */
  kCCSMSettingsHomepageURL,                 /**< <char *> home page string */

  // network settings
  kCCSMSettingsGPRSAutoAttach,              /**< <Boolean> flag whether or not to display the GPRS attached icon  */

  // NVRAM settings.
  kCCSMSettingsNAI,                         /**< <char *> Slot 1 username.  CDMA only */

  // new items
  kCCSMSettingsBrowserFlags,                /**< <UInt32> flags that controls browser behaviour */
  kCCSMSettingsBrowserProxyFlags,           /**< <UInt32> flags that controls browser behaviour */

  kCCSMSettingsProxyUsername,               /**< <char *> proxy username */
  kCCSMSettingsProxyPassword,               /**< <char *> password for the proxy */
  kCCSMSettingsMessagingFlags,              /**< <UInt32> messaging flags */
  kCCSMSettingsSMSMaxMsgSize,               /**< <UInt32> max SMS message size (bytes) */
  kCCSMSettingsSMSValidityPeriod,           /**< <UInt32> SMS validity period network specific value */
  kCCSMSettingsE911Timeout,                 /**< <UInt32> E911 timeout value (seconds) */

  kCCSMSettingsReserved = 0x8000      /**< reserved */
};
typedef UInt16 CCSMSettingsType;  // used for the settingsTypeEnum


/** system settings
 *
 */
typedef UInt32 CCSMSystemFlagsType;
typedef enum
{
  kCCSMSystemSettingReserved  = 0x00000000  /**< reserved setting */
}
CCSMSystemFlagsEnum;


/** enumeration for the phone settings flags
 *
 */
typedef UInt32 CCSMPhoneFlagsType;
typedef enum
{
  kCCSMPhoneSettingsReserved          = 0x00000000,  /**< reserved setting */
  kCCSMPhoneSettingsNetworkSelect     = 0x00000001,  /**< Network Select disable/enable */
  kCCSMPhoneSettingsRoamingIndicator  = 0x00000002,  /**< Roaming indicator yes/no */
  kCCSMPhoneSettingsEditMSISDN        = 0x00000004,  /**< Editable MSISDN */
  kCCSMPhoneSettingsShowEmergencyMode = 0x00000008,  /**< use Emergency mode */
  kCCSMPhoneSettingsEnableTTY         = 0x00000010   /**< enable TTY */
}
CCSMPhoneFlagsEnum;


/** enumeration for the radio band
 *  Used to optimize which band the radio starts scanning on.
 */
typedef UInt32 CCSMRadioBandType;
typedef enum
{
  kCCSMRadioBandUnknown,        /**< unknown radio band */
  kCCSMRadioBandEurope,         /**< european radio */
  kCCSMRadioBandNorthAmerica    /**< north american radio */
}
CCSMRadioBandEnum;


/** enumeration for the messaging settings flags
 *
 */
typedef UInt32 CCSMMessagingFlagsType;
typedef enum
{
  kCCSMMessagingSettingsReserved              = 0x00000000,  /**< reserved setting */
  kCCSMMessagingSettingsStripPhonePlus        = 0x00000001,  /**< does the network require the phone number to be stripped */
  kCCSMMessagingSettings11DigitRecipient      = 0x00000002,  /**< flag if a number requires 10 or 11 digits (I assume US only) */
  kCCSMMessagingSettingsNormaliseMMSAddress   = 0x00000004,  /**< Flag if MMS address should be normalised or not */
  kCCSMMessagingSettingsWAPProtocol20         = 0x00000008,  /**< *internal* Use WAP 2.0 for MMS? */
  kCCSMMessagingSettingsDisableMMSFallback    = 0x00000010   /**< Flag to disable the fallback account when connecting */

  //  kCCSMMessagingSettingsCameraProtocol        = 0x00000020,  /**< *internal* Use lightsurf or not */
}
CCSMMessagingSettingsEnum;



/** enumeration for the browser settings flags
 *
 */
typedef UInt32 CCSMBrowserFlagsType;
typedef enum
{
  kCCSMBrowserSettingsReserved              = 0x00000000,  /**< reserved setting */
  kCCSMBrowserSettingsEncryptMSISDN         = 0x00000001,  /**< send encrypted MSISDN */
  kCCSMBrowserSettingsCSDDisconnectOnExit   = 0x00000002,  /**< disconnect on exit for CSD connections */
  kCCSMBrowserSettingsPDataDisconnectOnExit = 0x00000004,  /**< disconnect on exit for packet data connections */
  kCCSMBrowserSettingsDormantOnExit         = 0x00000008,  /**< force dormancy on exit */

  kCCSMBrowserSettingsHideDisconnect        = 0x00000010,  /**< hide disconnect button */
  kCCSMBrowserSettingsVersionInWAPProfile   = 0x00000020,  /**< Add version in WAP profile header */


  /** proxy properties */
  kCCSMPrimaryProxyAuthenticate             = 0x00000001,
  kCCSMPrimaryProxyLocked                   = 0x00000002,
  kCCSMPrimaryProxyHide                     = 0x00000004,

  kCCSMSecondaryProxyAuthenticate           = 0x00010000,
  kCCSMSecondaryProxyLocked                 = 0x00020000,
  kCCSMSecondaryProxyHide                   = 0x00040000
}
CCSMBrowserSettingsEnum;


struct CCSMContextTypeTag;

#endif // __CARRIER_CUSTOMIZATION_LIBRARY_TYPES_H__
