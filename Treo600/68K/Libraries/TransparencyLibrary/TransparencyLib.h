/**
 * \file 68K/Libraries/TransparencyLib/Prv/TransparencyLib.h
 *
 * Transparency Library that couples a Ccp channel and a serial port
 *
 * This library can be used to couple data between a Ccp channel and a serial
 * port. It is meant to be used for diagnostics and tethered mode. Since it is a
 * library, it can work without being in a certain application.
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
#ifndef __TRANSPARENCY_LIB_INT__H__

#define __TRANSPARENCY_LIB_INT__H__


Err TransLibOpenConnection (UInt16 refNum, CcpChannelType portAChannel, UInt32 portB)
                                               SYS_TRAP (transLibTrapOpenConnection);


Err TransLibCloseConnection (UInt16 refNum)
                           SYS_TRAP (transLibTrapCloseConnection);

#endif
