// INCLUDE ONCE
#ifndef __HSSOUNDLIB__H__
#define __HSSOUNDLIB__H__

#include <PalmOS.h>


#ifdef __cplusplus
extern "C" {
#endif

Err	  HsSndOpen (UInt16 libRef)
		  SYS_TRAP (kHsSoundLibTrapOpen);

Err	  HsSndClose (UInt16 libRef)
		  SYS_TRAP (kHsSoundLibTrapClose);

//
// Library Version
//
UInt32  HsSndGetVersion (UInt16 libRef)
		  SYS_TRAP (kHsSoundLibTrapGetVersion);
	
//
// Port API
//
Err   HsSndPortGetInfo (UInt16 libRef, HsSndPortID portID, HsSndPortInfo * portInfoP)
		  SYS_TRAP (kHsSoundLibTrapPortGetInfo);

Err   HsSndPortSetParam (UInt16 libRef, HsSndPortID portID, HsSndParam paramSel, Int16 value, Int16 * returnValue)
		  SYS_TRAP (kHsSoundLibTrapPortSetParam);

//
// Switch API
//
Err   HsSndSwitchGetPort (UInt16 libRef, HsSndSwitchID switchID, HsSndPortID * portIDP, HsSndPortClass portClass)
		  SYS_TRAP (kHsSoundLibTrapSwitchGetPort);

Err   HsSndSwitchSetPort (UInt16 libRef, HsSndSwitchID switchID, HsSndPortID portID, HsSndPortClass portClass)
		  SYS_TRAP (kHsSoundLibTrapSwitchSetPort);

//
// Play API
//
Err   HsSndTonePlay (UInt16 libRef, UInt32 freq, UInt16 amp, UInt32 duration, UInt32 toneType)
		  SYS_TRAP (kHsSoundLibTrapTonePlay);

Err   HsSndToneStop (UInt16 libRef)
		  SYS_TRAP (kHsSoundLibTrapToneStop);

Err   HsSndFormatPlay (UInt16 libRef, HsSndFormatType format, HsSndCmdType command, void * commandData, UInt32 commandFlags)
		  SYS_TRAP (kHsSoundLibTrapFormatPlay);

Err   HsSndFormatRecord (UInt16 libRef, HsSndFormatType format, HsSndCmdType command, void * commandData, UInt32 commandFlags)
		  SYS_TRAP (kHsSoundLibTrapFormatRecord);

//
// User API
//
Err   HsSndGetUserVolume (UInt16 libRef, HsSndMode mode, Int16 * volumeP)
		  SYS_TRAP (kHsSoundLibTrapGetUserVolume);


Err   HsSndSetUserVolume (UInt16 libRef, HsSndMode mode, Int16 volume)
		  SYS_TRAP (kHsSoundLibTrapSetUserVolume);


#ifdef __cplusplus
}
#endif

#endif // __HSSOUNDLIB__H__
