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
 *	  CarrierCustomizationLibraryErrors.h
 *
 *  Description:
 *	  This file contains the error codes
 *
 *	Note:
 *
 *	History:
 *	  17-Dec-2002	dla		Created
 *
 ****************************************************************/

#ifndef __CARRIER_CUSTOMIZATION_LIBRARY_ERRORS_H__
#define __CARRIER_CUSTOMIZATION_LIBRARY_ERRORS_H__


#define ccsmErrClass	  0x9000  // 0x9000

#define ccsmErrUnknownCarrier       ccsmErrClass + 0x01  /**< 0x9001 carrier code on SIM card not recognized */
#define ccsmErrMemory               ccsmErrClass + 0x02  /**< 0x9002 memory error */
#define ccsmErrPhoneLibLoad         ccsmErrClass + 0x03  /**< 0x9003 phone library not loaded */
#define ccsmErrPhoneNotPowered      ccsmErrClass + 0x04  /**< 0x9004 phone is not powered */
#define ccsmErrInvalidArg           ccsmErrClass + 0x05  /**< 0x9005 invalid arguement error */
#define ccsmErrUnknownSetting       ccsmErrClass + 0x06  /**< 0x9006 unknown setting requested error */
#define ccsmErrBufferTooSmall       ccsmErrClass + 0x07  /**< 0x9007 need more space in buffer */
#define ccsmErrNotRegistered        ccsmErrClass + 0x08  /**< 0x9008 radio is not registered */
#define ccsmErrUnknownField         ccsmErrClass + 0x09  /**< 0x9009 requested field not in database record */
#define ccsmErrLibUninitialized     ccsmErrClass + 0x0A  /**< 0x900A library was not initialized */
#define ccsmErrUndefinedField       ccsmErrClass + 0x0B  /**< 0x900B the field did not have a value specified */

#define ccsmErrProfileUnspecified   ccsmErrClass + 0x50  /**< 0x9050 requested profile is not specified */
#define ccsmErrUnspecified          ccsmErrClass + 0x51  /**< 0x9051 settings is not specified for carrier */
#define ccsmErrUnimplemented        ccsmErrClass + 0xA5  /**< 0x90F5 Unimplemented feature */

#endif // __CARRIER_CUSTOMIZATION_LIBRARY_ERRORS_H__
