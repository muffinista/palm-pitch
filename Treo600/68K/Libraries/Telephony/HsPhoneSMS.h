/**
 * \file 68K/Libraries/Telephony/HsPhoneSMS.h
 *
 * Header File for Phone Library API ---- SMS CATEGORY
 *
 * All implementations of the Handspring Phone Library support a common API. 
 * This API is broken up into various categories for easier management.  This file
 * defines the SMS category.  These API calls are used to send/receive Short Message 
 * Service (SMS) messages.
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

#ifndef HS_PHONESMS_H
#define HS_PHONESMS_H
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
 * Palm OS address book functions
 **/
enum AddressAppRecordFieldEnum {
	kName, kFirstName, kCompany, kPhone1, kPhone2, kPhone3, kPhone4,
	kPhone5, kAddress, kCity, kState, kZipCode, kCountry, kTitle,
	kCustom1, kCustom2, kCustom3, kCustom4, kNote,
	kRecordFieldEnumCount // must be the last field
};

#ifndef __cplusplus
typedef enum AddressAppRecordFieldEnum AddressAppRecordFieldEnum;
#endif


#define isValidAddressAppRecordFieldEnum(x) ((x >= kName) && (x < kRecordFieldEnumCount))

/**
 * Item description here
 **/
typedef enum  {
	addrWorkLabel, addrHomeLabel, addrFaxLabel, addrOtherLabel, addrEmailLabel, addrMainLabel,
	addrPagerLabel, addrMobileLabel, addrNoLabel
}AddressAppPhoneLabel;

/**
 * Item description here
 * This should probably be private to the library
 **/
struct Address {
  // All fields should be considered read-only.
  AddressAppPhoneLabel kind;
  char filler;
  UInt32 uniqueID;
  UInt16 phoneBookIndex;
  UInt16 count[3];
  // immediately followed by address data
};


/**
 * Item description here
 **/
struct AddrDescriptor {
  UInt16 count; // Length of list
	// immediately followed by count pairs of (UInt16,Address)
};

#ifndef _cplusplus
typedef struct Address Address;
typedef struct AddrDescriptor AddrDescriptor;
#endif


struct AddressType {
  UInt16 addressSize;
  Address address;
};

#ifndef _cplusplus
typedef struct AddressType AddressType;
#endif

/**
 * Item description here
 **/
struct AddressAppRecordHeader {
	UInt32 options;
	UInt32 flags;
	UInt8 companyOffset;
	char data;
};

#ifndef _cplusplus
typedef struct AddressAppRecordHeader AddressAppRecordHeader;
#endif

/**
 * Item description here
 **/
struct AddressAppRecord {
// private:
	// Fields within an address.
	
	// Header of an address. This is immediately followed by the address
	// data. The first database is part of the following structure.
	// (See AddressDB.h for a detailled explanation of the structure.)

	MemHandle mData;
	UInt32 mID;
	Boolean mLocked;
	AddressAppRecordHeader* mHeader;
};

// NBS defines
/* Identifier elements definitions */
#define NBSHeaderID            0x00  /**< NBS fragment header information identifier */
#define NBSHeaderIDLen         0x03  /**< three bytes */

#define Addressing8bitID       0x04  /**< 8-bit address information identifier */
#define Addressing8bitIDLen    0x02  /**< 2 bytes... src port(1), dest port(1) */

#define Addressing16bitID      0x05  /**< 16-bit address information identifier */
#define Addressing16bitIDLen   0x04  /**< 4 bytes... src port(2), dest port(2) */

/* Text Header elements */
#define NBSHeaderEscapeSeq     "//"      /**< start sequence of the header */
#define NBSTextHeader          "//SCK"   /**< beginning of an NBS text header */
#define NBSTextHeaderLength    5         /**< length of the header */

/* 8bit addressing text header lengths, not including the //SCK */
#define Full8bitTextHeader     0x0A  /**< length for full header with 8-bit addressing    //SCKddoorrttnn */
#define Minimum8bitTextHeader  0x02  /**< length for minimum header with 8-bit addressing //SCKdd */

/**
 * 16bit addressing text header lengths, not including the //SCKL
 **/
#define Full16bitTextHeader    0x0F  /**< length for full header with 16-bit addressing    //SCKLddddoooorrttnn */
#define Minimum16bitTextHeader 0x05  /**< length for minimum header with 16-bit addressing //SCKLdddd */

#define TextHeaderTerminator   ' ' /**< text based headers terminate at the next space */

#define phnNBSEvent         'Hnbs'

// NBS Port Numbers (Nokia Smart Messaging Spec)
#define NBSPort_MimeVCard     0xE2
#define NBSPort_MimeVCalendar 0xE4


// SMS stuff
//// Enumeration types
/**
 * Item description here
 **/
typedef enum {
  kMTIncoming, kMTOutgoing
} SMSMessageType;

#define isValidSMSMessageType(m) ((m >= kMTIncoming) && (m <= kMTOutgoing))

/**
 * Item description here
 **/
typedef enum  {
  kNone,
  kReceiving, kReceived,
  kPending, kSending, kSent
}SMSMessageStatus;

#define isValidSMSMessageStatus(m) ((m >= kNone) && (m <= kSent))

/**
 * CDMA SMS Preference ?
 **/
typedef struct
  {
    Boolean         audioAlertEnable;
    Boolean         confirmDeletion;
  }
PhnSMSPrefType ,* PhnSMSPrefPtr;



/**
 * Item description here
 **/
typedef enum  {
  kGreekSymbols = 1L << 0,
  kMissingPart =	1L << 1,
  kAutoDelete =	1L << 2,
  kNotification = 1L << 3,
  kDontEncode =	1L << 4,
  kSubstitution = 1L << 5,
  kFailed =		1L << 6,
  kStatusReport = 1L << 7,
  kFreeReply =	1L << 8,
  kInternetEMail =1L << 9,
  kTextSegments =	1L << 10,
  kSMSErrorType1 = 1L << 11,
  kSMSErrorType2 = 1L << 12,
  kSMSErrorType3 = 1L << 13,
  kSMSHighPriority = 1L << 14,
  kSMSLowPriority = 1L << 15,
		// application-level flags
  kRead = 1L << 16
}SMSMessageFlags;

/**
 * Item description here
 **/
typedef enum  {
  smsFmtIgnoreKind = 0,
  smsFmtMatchKind = 8,
  smsFmtExceptKind = 16,
  smsFmtAllKinds = 24,
  smsFmtLastNameFirst = 32,
  smsFmtShortLabel = 64
}SMSAddressFormat;

/**
 * Item description here
 **/
typedef struct  {
  Boolean freeReply;
  Boolean statusReport;
  unsigned char validity;
}SMSSendOptions;

/**
 * Item description here
 **/
typedef struct  {
  UInt32 owner;	// application owning this message
  SMSMessageType type;		// message type
  SMSMessageStatus status;	// message status
  UInt32 date;		// date of sending or receipt
  UInt32 flags;	// miscellaneous flags
  UInt8 validity;	// validity period
  UInt8 segments;	// number of segments (incoming message)
  // Size of field Addresses. If there is segmentation information for
  // a message this field contains also the sizes of the parts. The array
  // is therefore a variable-size array.
  UInt16 size[1];
}SmsHeader;


/**
 * Structure passed to the callbacks registered for incoming NBS notifications
 **/
struct NBSNotificationEventType
{
	UInt16 version;  /* version number to provide future backwards compatibility */

	/* helper fields */
	Boolean NBSdatagram;  /**< flag if it is an NBS datagram */
	Boolean binary;       /**< true if binary data */

	void *headerP;    /**< pointer to raw header */
	UInt8 headerLen;  /**< length of headerP */
	void *dataP;      /**< pointer to data body */
	UInt8 dataLen;    /**< length of dataP */

	/* NBS datagram fields */
	UInt8 refNum;    /**< NBS reference number */
	UInt8 maxNum;    /**< max segment number 1-255 */
	UInt8 seqNum;    /**< sequence number    1-255, no more than maxNum */
	Int8  reserved1; /**< padding */

	UInt32 srcPort;  /**< source port */
	UInt32 dstPort;  /**< destination port */

	/* SMS related fields */
	UInt32 msgID; /**< ID into the SMS database to reference this
                  * message this ID is not gauranteed to be
                  * valid once the notification callback
                  * returns.  Users should make a copy of the
                  * msg if they want to work on it after the
                  * callback returns.
                  */

	char   *senderP;   /**< sender number - null terminated */
	UInt32 datetime;   /**< date/time stamp */
	Int32  reserved2;  /**< reserved*/
	Int32  reserved3;  /**< reserved*/
};

#ifndef _cplusplus
typedef struct NBSNotificationEventType NBSNotificationEventType;
#endif

/**
 * NBS 
 **/
enum { kParseError = -1, kDoneParsing=0, kParseInformationID, kParseInformationLength, kParseInformationData };

/**
 * SMS length information
 **/
typedef struct 
{
  UInt16 size;
  Boolean  substitution;
  UInt16	 length;
  UInt16  segmentCount;  
}PhnLibLengthInfoType;


  extern PhnAddressHandle PhnLibNewAddress (UInt16 refNum, const CharPtr number, PhnDatabaseID id)
				  PHN_LIB_TRAP(PhnLibTrapNewAddress);


  extern CharPtr PhnLibGetField (UInt16 refNum, PhnAddressHandle address, PhnAddressField field)
				  PHN_LIB_TRAP(PhnLibTrapGetField);

  extern PhnDatabaseID PhnLibGetID(UInt16 refNum, PhnAddressHandle address)
				PHN_LIB_TRAP(PhnLibTrapGetID);
				
  extern Err PhnLibSetField(UInt16 refNum, PhnAddressHandle address, PhnAddressField field, const char* data)
				PHN_LIB_TRAP(PhnLibTrapSetField);

  extern Err PhnLibSetNumber(UInt16 refNum, PhnAddressHandle address, const char* number)
				PHN_LIB_TRAP(PhnLibTrapSetNumber);

  extern Err PhnLibSetID(UInt16 refNum, PhnAddressHandle address, PhnDatabaseID id)
				PHN_LIB_TRAP(PhnLibTrapSetID);

  extern char* PhnLibAddressToText(UInt16 refNum, PhnAddressHandle address ,SMSAddressFormat format)
			  PHN_LIB_TRAP(PhnLibTrapAddressToText);
  
  extern Boolean PhnLibHasName(UInt16 refNum, PhnAddressHandle address)
				PHN_LIB_TRAP(PhnLibTrapHasName);

  extern Boolean PhnLibEqual(UInt16 refNum, PhnAddressHandle a, PhnAddressHandle b)
				PHN_LIB_TRAP(PhnLibTrapEqual);

  extern DmOpenRef PhnLibGetDBRef(UInt16 refNum)
				PHN_LIB_TRAP(PhnLibTrapGetDBRef);
  
  extern Err PhnLibReleaseDBRef(UInt16 refNum, DmOpenRef db)
				PHN_LIB_TRAP(PhnLibTrapReleaseDBRef);

  extern PhnDatabaseID PhnLibNewMessage(UInt16 refNum, SMSMessageType type)
				PHN_LIB_TRAP(PhnLibTrapNewMessage);
  
  extern Err PhnLibDeleteMessage(UInt16 refNum, PhnDatabaseID msgID, Boolean archive)
				PHN_LIB_TRAP(PhnLibTrapDeleteMessage);
  
  extern Err PhnLibSendMessage(UInt16 refNum, PhnDatabaseID msgID, Boolean progress)
				PHN_LIB_TRAP(PhnLibTrapSendMessage);
  
  extern Err PhnLibSendPendingMessages(UInt16 refNum)
				PHN_LIB_TRAP(PhnLibTrapSendPendingMessages);

  extern Err PhnLibSetText(UInt16 refNum, PhnDatabaseID msgID, const char* data, Int16 size)
				PHN_LIB_TRAP(PhnLibTrapSetText);
  
  extern Err PhnLibSetDate(UInt16 refNum, PhnDatabaseID msgID, UInt32 date)
				PHN_LIB_TRAP(PhnLibTrapSetDate);
  
  extern Err PhnLibSetOptions(UInt16 refNum, PhnDatabaseID msgID, const SMSSendOptions* options)
				PHN_LIB_TRAP(PhnLibTrapSetOptions);
  
  extern Err PhnLibSetAddresses(UInt16 refNum, PhnDatabaseID msgID, const PhnAddressList list)
				PHN_LIB_TRAP(PhnLibTrapSetAddresses);
  
  extern Err PhnLibSetStatus(UInt16 refNum, PhnDatabaseID msgID, SMSMessageStatus status)
				PHN_LIB_TRAP(PhnLibTrapSetStatus);
  
  extern Err PhnLibSetFlags(UInt16 refNum, PhnDatabaseID msgID, UInt32 flags)
				PHN_LIB_TRAP(PhnLibTrapSetFlags);
  
  extern Err PhnLibSetOwner(UInt16 refNum, PhnDatabaseID msgID, UInt32 owner)
				PHN_LIB_TRAP(PhnLibTrapSetOwner);

  extern Err PhnLibGetText(UInt16 refNum, PhnDatabaseID msgID, MemHandle* data)
				PHN_LIB_TRAP(PhnLibTrapGetText);

  extern Err PhnLibGetDate(UInt16 refNum, PhnDatabaseID msgID, UInt32* date)
				PHN_LIB_TRAP(PhnLibTrapGetDate);
  
  extern Err PhnLibGetOptions(UInt16 refNum, PhnDatabaseID msgID, SMSSendOptions* options)
				PHN_LIB_TRAP(PhnLibTrapGetOptions);
  
  extern Err PhnLibGetAddresses(UInt16 refNum, PhnDatabaseID msgID, PhnAddressList* list)
				PHN_LIB_TRAP(PhnLibTrapGetAddresses);
  
  extern Err PhnLibGetStatus(UInt16 refNum, PhnDatabaseID msgID, SMSMessageStatus* status)
				PHN_LIB_TRAP(PhnLibTrapGetStatus);
  
  extern Err PhnLibGetFlags(UInt16 refNum, PhnDatabaseID msgID, UInt32* flags)
				PHN_LIB_TRAP(PhnLibTrapGetFlags);
  
  extern Err PhnLibGetOwner(UInt16 refNum, PhnDatabaseID msgID, UInt32* owner)
				PHN_LIB_TRAP(PhnLibTrapGetOwner);

  extern Err PhnLibGetType(UInt16 refNum, PhnDatabaseID msgID, SMSMessageType* type)
				PHN_LIB_TRAP(PhnLibTrapGetType);

  extern Boolean PhnLibIsLegalCharacter(UInt16 refNum, char c)
				PHN_LIB_TRAP(PhnLibTrapIsLegalCharacter);

  extern char PhnLibMapCharacter(UInt16 refNum, char c)
				PHN_LIB_TRAP(PhnLibTrapMapCharacter);
  
  extern Err PhnLibSetServiceCentreAddress(UInt16 refNum, const PhnAddressHandle address)
				PHN_LIB_TRAP(PhnLibTrapSetServiceCentreAddress);
  extern Err PhnLibGetServiceCentreAddress(UInt16 refNum, PhnAddressHandle* address)
				PHN_LIB_TRAP(PhnLibTrapGetServiceCentreAddress);

  extern Int16 PhnLibLength(UInt16 refNum, const char* text, Boolean inMessages, Boolean substitution)
				PHN_LIB_TRAP(PhnLibTrapLength);
  
  extern Err PhnLibGetLengthDetails(UInt16 refNum, const char* text, const char* address, PhnLibLengthInfoType* info)
        PHN_LIB_TRAP(PhnLibTrapGetLengthDetails);

  extern const char* PhnLibGetSubstitution(UInt16 refNum, char c)
				PHN_LIB_TRAP(PhnLibTrapGetSubstitution);

  extern PhnAddressList PhnLibNewAddressList(UInt16 refNum)
				PHN_LIB_TRAP(PhnLibTrapNewAddressList);
  extern Err PhnLibDisposeAddressList(UInt16 refNum, PhnAddressList list)
				PHN_LIB_TRAP(PhnLibTrapDisposeAddressList);
  
  extern Err PhnLibAddAddress(UInt16 refNum, PhnAddressList list, const PhnAddressHandle address)
				PHN_LIB_TRAP(PhnLibTrapAddAddress);
  
  extern Err PhnLibGetNth(UInt16 refNum, const PhnAddressList list, Int16 index, PhnAddressHandle* address)
				PHN_LIB_TRAP(PhnLibTrapGetNth);
  
  extern Err PhnLibSetNth(UInt16 refNum, PhnAddressList list, Int16 index, const PhnAddressHandle address)
				PHN_LIB_TRAP(PhnLibTrapSetNth);

  extern Err PhnLibCount(UInt16 refNum, PhnAddressList list, UInt16* count)
				PHN_LIB_TRAP(PhnLibTrapCount);

  extern Err	PhnLibGetSMSRingInfo (UInt16 refNum, PhnRingingInfoPtr info)
				PHN_LIB_TRAP(PhnLibTrapGetSMSRingInfo);

  extern Err	PhnLibSetSMSRingInfo (UInt16 refNum, PhnRingingInfoPtr info)
					PHN_LIB_TRAP(PhnLibTrapSetSMSRingInfo);

  extern Err	PhnLibGetSMSGateway (UInt16 refNum, char** smsGateway)
					PHN_LIB_TRAP(PhnLibTrapGetSMSGateway);

  extern Err      PhnLibGetSMSPreference (UInt16 refNum, PhnSMSPrefPtr prefP)
                  PHN_LIB_TRAP (PhnLibTrapGetSMSPreference);

  extern Err      PhnLibSetSMSPreference (UInt16 refNum, PhnSMSPrefPtr prefP)
                  PHN_LIB_TRAP (PhnLibTrapSetSMSPreference);

  extern Err      PhnLibAPGetNth (UInt16 refNum, PhnAddressList list, Int16 index,
                                PhnAddressHandle * address)
                  PHN_LIB_TRAP (PhnLibTrapAPGetNth);

  extern Err      PhnLibSendSMSMTAck (UInt16 refNum, UInt8 transactionId,
                                      Boolean ack)
                  PHN_LIB_TRAP (PhnLibTrapSendSMSMTAck);

  extern Err      PhnLibQuerySMSMT (UInt16 refNum)
                  PHN_LIB_TRAP (PhnLibTrapQuerySMSMT);


#endif
