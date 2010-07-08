/**
 * \file Common/Libraries/ComChannelProvider/ComChannelProviderTypes.h
 * Communication channel Public constants and structs
 *
 * Contstants and structs that are used by both the ARM and 68K function calls. 
 *
 * \license
 *
 *    Copyright (c) 2002 Handspring Inc., All Rights Reserved
 *
 * \author Robert Gosselin
 *
 * $Id:$
 *
 *****************************************************************************/

// INCLUDE ONCE
#ifndef __COM_CHANNEL_PROVIDER_PUBLIC_COMMON__H__

#define __COM_CHANNEL_PROVIDER_PUBLIC_COMMON__H__

#if 0
#pragma mark -------- Structures -------- 
#endif

/**
 * There are the different types of channels that can be opened. They are passed
 * as the paramater to the CcpOpenChannel function call.
 **/
enum
{
  kCcpChannelTypeControl = 0,  /**< Open a channel to send/rcv control messages */
  kCcpChannelTypeModem,  /**< Open a channel to send/rcv modem type messages */
  kCcpChannelTypeDebug,  /**< Open a channel to rcv debug messages. */
  kCcpChannelTypeUpdate,  /**< Open a channle to update the firmare of the radio */
  kCcpChannelTypePassThrough  /**< Open a channle to do no MUX Passthrough
								 direct to the radio.*/
};
typedef UInt16 CcpChannelType;



#endif // INCLUDE ONCE -- __COM_CHANNEL_PROVIDER_PUBLIC_COMMON__H__
