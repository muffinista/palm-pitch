/**
 * \file Common/Libraries/ComChannelProvider/Prv/HsSoundLibTraps.h
 * HsSoundLib traps
 *
 * . 
 *
 * \license
 *
 *    Copyright (c) 2003 Handspring Inc., All Rights Reserved
 *
 * \author Scott Vail
 *
 * $Id:$
 *
 *****************************************************************************/

// INCLUDE ONCE
#ifndef __HSSOUNDLIB_TRAPS__H__
#define __HSSOUNDLIB_TRAPS__H__

#include <PalmTypes.h>

#if 0
#pragma mark -------- Constants -------- 
#endif


#define kHsSoundLibTrapOpen			  (sysLibTrapOpen)
#define kHsSoundLibTrapClose		  (sysLibTrapClose)

#define kHsSoundLibTrapGetVersion     (sysLibTrapCustom + 0)
#define kHsSoundLibTrapPortGetInfo	  (sysLibTrapCustom + 1)
#define kHsSoundLibTrapPortSetParam	  (sysLibTrapCustom + 2)
#define kHsSoundLibTrapSwitchGetPort  (sysLibTrapCustom + 3)
#define kHsSoundLibTrapSwitchSetPort  (sysLibTrapCustom + 4)
#define kHsSoundLibTrapTonePlay		  (sysLibTrapCustom + 5)
#define kHsSoundLibTrapToneStop		  (sysLibTrapCustom + 6)
#define kHsSoundLibTrapFormatPlay	  (sysLibTrapCustom + 7)
#define kHsSoundLibTrapFormatRecord	  (sysLibTrapCustom + 8)
#define kHsSoundLibTrapGetUserVolume  (sysLibTrapCustom + 9)
#define kHsSoundLibTrapSetUserVolume  (sysLibTrapCustom + 10)

#endif // INCLUDE ONCE -- __HSSOUNDLIB_TRAPS__H__


