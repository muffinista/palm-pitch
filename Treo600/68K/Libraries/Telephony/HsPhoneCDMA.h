/**
 * \file 68K/Libraries/Telephony/HsPhoneCDMA.h
 *
 * Header File for Phone Library API ---- CDMA CATEGORY
 *
 * All implementations of the Handspring Phone Library support a common API. 
 * This API is broken up into various categories for easier management.  This file
 * defines the public portion of the CDMA category.  These API calls are used for features specific to
 * CDMA networks.
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

#ifndef HS_PHONECDMA_H
#define HS_PHONECDMA_H

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
 * Item description here
 **/
typedef enum  {
    phnOneXFailPrev=0,    /**< current used PREV does not support the type of data call attempted */
    phnOneXFailNoSrv=1,   /**< modem did not have service when the data call was attempted */
    phnOneXFailNetworkSORej=2, /**< The network rejected the service option for the data call */
    phnOneXFailModemSORej=3,   /**< The modem does not support or restricts the service option for the data call */
    phnOneXFailNetworkBusy=4,  /**< The network was busy */
	phnOneXFailUnknown=5
} PhnOneXDataFailType;

#define isValidPhnOneXDataFailType(d) ((d >= phnOneXFailPrev) && (d <= phnOneXFailUnknown))


typedef enum{
    PhnPDPAUncert0_5_M = 0x00,
     /**< Standard deviation of 0.5 meters */
    PhnPDPAUncert0_75_M,
     /**< Standard deviation of 0.75 meters */
    PhnPDPAUncert1_M,
     /**< Standard deviation of 1 meter */
    PhnPDPAUncert1_5_M,
     /**< Standard deviation of 1.5 meters */
    PhnPDPAUncert2_M,
     /**< Standard deviation of 2 meters */
    PhnPDPAUncert3_M,
     /**< Standard deviation of 3 meters */
    PhnPDPAUncert4_M,
     /**< Standard deviation of 4 meters */
    PhnPDPAUncert6_M,
     /**< Standard deviation of 6 meters */
    PhnPDPAUncert8_M,
     /**< Standard deviation of 8 meters */
    PhnPDPAUncert12_M,
     /**< Standard deviation of 12 meters */
    PhnPDPAUncert16_M,
     /**< Standard deviation of 16 meters */
    PhnPDPAUncert24_M,
     /**< Standard deviation of 24 meters */
    PhnPDPAUncert32_M,
     /**< Standard deviation of 32 meters */
    PhnPDPAUncert48_M,
     /**< Standard deviation of 48 meters */
    PhnPDPAUncert64_M,
     /**< Standard deviation of 64 meters */
    PhnPDPAUncert96_M,
     /**< Standard deviation of 96 meters */
    PhnPDPAUncert128_M,
     /**< Standard deviation of 128 meters */
    PhnPDPAUncert192_M,
     /**< Standard deviation of 192 meters */
    PhnPDPAUncert256_M,
     /**< Standard deviation of 256 meters */
    PhnPDPAUncert384_M,
     /**< Standard deviation of 384 meters */
    PhnPDPAUncert512_M,
     /**< Standard deviation of 512 meters */
    PhnPDPAUncert768_M,
     /**< Standard deviation of 768 meters */
    PhnPDPAUncert1024_M,
     /**< Standard deviation of 1,024 meters */
    PhnPDPAUncert1536_M,
     /**< Standard deviation of 1,536 meters */
    PhnPDPAUncert2048_M,
     /**< Standard deviation of 2,048 meters */
    PhnPDPAUncert3072_M,
     /**< Standard deviation of 3,072 meters */
    PhnPDPAUncert4096_M,
     /**< Standard deviation of 4,096 meters */
    PhnPDPAUncert6144_M,
     /**< Standard deviation of 6,144 meters */
    PhnPDPAUncert8192_M,
     /**< Standard deviation of 8,192 meters */
    PhnPDPAUncert12288_M,
     /**< Standard deviation of 12,2288 meters */
    PhnPDPAUncertGREATER_12288_M,
     /**< Standard deviation that is greater than 12,288 meters */
    PhnPDPAUncertNOT_COMPUTABLE_M,
     /**< Standard deviation is not computable */
    PhnPDPAUncertMAX
} PhnPDPAUncerttype;


/**
 * Item description here
 **/
typedef enum {
	
	phnOneXStatusPRevNoSvc,  /**< Service is not available. */
    phnOneXStatusPRev1, /**< J-STD-008 service is in use. */
	phnOneXStatusPRev3, /**< IS-95A service is in use. */
	phnOneXStatusPRev4, /**< IS-95B service is in use. */
	phnOneXStatusPRev6, /**< IS-2000 release 0 service is in use. */
	phnOneXStatusPRev7	/**< IS-2000 release A service is in use. */
} PhnOneXProtRevType;

#define isValidPhnOneXProtRevType(p) (p <= phnOneXStatusPRev7)


/**
 * Item description here
 **/
typedef enum {

  phnPacketDataSessionNone,   /**< No packet data session exists. */
  phnPacketDataSessionDormant,
  phnPacketDataSessionActive
  
} PhnPacketDataSessionType;

#define isValidPhnPacketDataSessionType(p) (p <= phnPacketDataSessionActive)

/**
 * Item description here
 **/
typedef enum {

    phnMIPSessionNone,
    phnMIPSession     /**< A Mobile IP session exists. */   

} PhnMIPSessionType;

#define isValidPhnMIPSessionType(m) (m <= phnMIPSession)


/**
 * Item description here
 **/
typedef struct
{
  PhnOneXProtRevType		oneXStatusPRev;
  PhnPacketDataSessionType	pdSessionStatus; 
  PhnMIPSessionType			mipSessionType;

}PhnOneXStatus;


/**
 * Item description here
 **/
typedef enum {

    phnMIPSuccess,
	phnMIPNoSimBindings,
    phnMIPFaReasonUnspecified=64,
    phnMIPFaAdminProhibited=65,
    phnMIPFaInsufficientResources=66,
    phnMIPFaMobileNodeAuth=67,
    phnMIPFaHomeAgentAuth=68,
    phnMIPFaReqLifetimeTooLong=69,
    phnMIPFaPoorlyFormedReq=70,
    phnMIPFaPoorlyFormedReply=71,
    phnMIPFaReqedEncapUnavail=72,
    phnMIPFaReservedNUnavail=73,
    phnMIPFaCantRevTun=74,
    phnMIPFaMustRevTun=75,
    phnMIPFaBadTtl=76,
    phnMIPFaInvalidCareOfAddr=77,
    phnMIPFaRegistration_Timeout=78,
	PhnMIPFADelvStyleUnsupported=79,
    phnMIPFaHome_Network_Unreachable=80,
    phnMIPFaHa_Host_Unreachable=81,
    phnMIPFaHa_Port_Unreachable=82,
    phnMIPFaHa_Unreachable=88,
	PhnMIPFANonzeroHomeAddrReq=96,
	PhnMIPFAMissingNai=97,
    phnMIPFaForeign_Agent=98,
	PhnMIPFAMissingHomeAddr=99,
    PhnMIPFAError1=100,     
    PhnMIPFAError2 =101,
    phnMIPFaUnknown_Challenge=104,
    phnMIPFaMissing_Challenge=105,
    phnMIPFaStale_Challenge=106,
    phnMIPHaReasonUnspecified=128,
    phnMIPHaAdminProhibited=129,
    phnMIPHaInsufficientResources=130,
    phnMIPHaMobileNodeAuth=131,
    phnMIPHaForeignAgentAuth=132,
    phnMIPHaRegIdMismatch=133,
    phnMIPHaPoorlyFormedReq=134,     
    phnMIPHaTooManySimMobBindings=135,     
    phnMIPHaUnknownHaAddr=136,     
    phnMIPHaCantRevTun=137,     
    phnMIPHaMustRevTun=138,     
    phnMIPHaReqEncapNotAvail=139,
	phnMIPHAError1=140,
	phnMIPHAError2=141

} PhnMIPFailType;



/**
 * Item description here
 **/
typedef struct
  {
    DWord                       lat;
     /**< Two's complement value of the latitude of the modem, in units of
         360/2^25 degrees. */

    DWord                       lon;
     /**< Two's complement value of the longitude of the modem, in units of
         360/2^26 degrees. */

    DWord                       time_stamp;
     /**< CDMA system time, in seconds, at the time the solution was valid. */

    UInt8                        loc_uncertainty_ang;
     /**< Angle of axis with respect to True North for position uncertainty,
         in units of 5.625 degrees, in the range from 0 to 84.375 degrees,
         where 0 degrees is True North and the angle increases towards the
         East. */

    PhnPDPAUncerttype         loc_uncertainty_a;
     /**< Standard deviation of axis along angle specified for position
         uncertainty. */

    PhnPDPAUncerttype         loc_uncertainty_p;
     /**< Standard deviation of axis perpendicular to angle specified for
         position uncertainty. */

    UInt8                        phn_pd_svc_mask;
     /**< Bit mask indicating which of the following optional fields contain
         valid data. */

    UInt16                        altitude;
     /**< Height of the modem, in units of 1 meter, in the range from -500 m
         to 15883 m, where the binary value of the field conveys the height
         plus 500 m.  Valid if OPT_FIELD_MASK field has
         PDSM_PD_ALTITUDE_VALID bit set. */

    UInt16                        heading;
     /**< Direction of the modem, in units of 360/2^10 degrees, in the range 
         from 0 to 360x(1-2^10) degrees (where 0 degrees is True North and
         the angle increases towards the East.  Valid if OPT_FIELD_MASK
         field has PDSM_PD_VELOCITY_VALID bit set. */

    UInt16                        velocity_hor;
     /**< Horizontal component of the velocity of the modem, in units of
         0.25 m/s, in the range from 0 to 127.75 m/s.  Valid if
         OPT_FIELD_MASK field has PDSM_PD_VELOCITY_VALID bit set. */

    Boolean                     fix_t;
     /**< Boolean indicating fixed type.  0 means 2D fix and 1 means 3D
         fix. */

    UInt16                        velocity_ver;
     /**< Two's complement value of the vertical component of the velocity of
         the modem, in units of 0.5 m/s, in the range from -64m/s to
         +63.5m/s.  Valid if OPT_FIELD_MASK field has
         PDSM_PD_VELOCITY_VALID bit set and FIX_T is set to TRUE. */

    PhnPDPAUncerttype         loc_uncertainty_v;
     /**< Standard deviation of vertical error for position uncertainty.
         Valid if OPT_FIELD_MASK field has PDSM_PD_VELOCITY_VALID bit
         set. */
  }
PhnPDDataType, *PhnPDDataPtr;

extern CharPtr  PhnLibAPGetField (UInt16 refNum, PhnAddressHandle address, PhnAddressField field)
  PHN_LIB_TRAP (PhnLibTrapAPGetField);

#endif  //HS_PHONECDMA_H
