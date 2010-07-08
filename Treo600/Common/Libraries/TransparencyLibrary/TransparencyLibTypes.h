/**
 * \file TransparencyLibTypesInt.h
 *
 * Common types of the Transparency Library.
 *
 * This file contains definitions for types exported by the transparency
 * Library. This file should never have to be included directly and it for
 * internal Handspring use. 
 *
 * \license
 *
 *    Copyright (c) 2002 Handspring Inc., All Rights Reserved
 *
 * \author Arun Mathias
 *
 *****************************************************************************/

#ifndef __TRANSPARENCY_LIB_TYPES_INT__H__

#define __TRANSPARENCY_LIB_TYPES_INT__H__

/**
 * Item description here
 **/
#define  transLibName                   "Transparency Library"

/**
 * Creator ID of Transparency Library - 'HsTL'
 **/
#define  transLibCreator                hsFileCTransparencyLib

/**
 * Type ID of transparency library
 **/
#define  transLibType                   sysFileTLibrary


/**
 * Trap id for openConnection function
 **/
#define transLibTrapOpenConnection      sysLibTrapCustom

/**
 * Trap id for closeConnection function 
 **/
#define transLibTrapCloseConnection     sysLibTrapCustom+1


/**
 * \defgroup Error codes
 */
/*@{*/

/**
 * Error class for the transparency library
 **/
#define   transLibErrorClass  0x5000

/**
 *  Unkown command requested. For example, an unknown channel type was passed as
 *  a port.
 **/
#define   transLibErrUnknown  (transLibErrorClass | 1)

/**
 *  No connection is open.
 **/
#define   transLibErrNotOpen  (transLibErrorClass | 2)

/**
 *  Trans Lib already Open 
 **/
#define   transLibErrAlreadyOpen  (transLibErrorClass | 3)

/**
 *  Trans Lib Error when there is cradle not attached to the bottom port
 **/
#define   transLibErrDockNotAttached (transLibErrorClass | 4)


/*@}*/

#endif
