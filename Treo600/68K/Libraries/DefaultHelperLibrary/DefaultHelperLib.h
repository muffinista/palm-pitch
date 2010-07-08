/**
 * \file 68K/Libraries/DefaultHelperLibrary/DefaultHelperLib.h
 *
 * Default Helper library owns control over the Default Helpers database. 
 *
 * \license
 *
 *    Copyright (c) 2003 Handspring Inc., All Rights Reserved
 *
 * \author Priscilla Cinque
 *
 *****************************************************************************/



Err DefaultHelperLibOpen (UInt16 refNum)
                 SYS_TRAP (sysLibTrapOpen);

Err DefaultHelperLibClose (UInt16 refNum)
                 SYS_TRAP (sysLibTrapClose);

Err DefaultHelperLibWake (UInt16 refNum) 
                 SYS_TRAP (sysLibTrapWake);

Err DefaultHelperLibSleep (UInt16 refNum)
                 SYS_TRAP (sysLibTrapSleep);

Err DefaultHelperLibGetDefaultHelper (UInt16 refNum, 
									  UInt32 serviceID, 
									  UInt32* defaultAppCreatorP)
                 SYS_TRAP (defaultHelperLibTrapGetDefaultHelper);

Err DefaultHelperLibSetDefaultHelper (UInt16 refNum, 
									  UInt32 serviceID, 
									  UInt32 defaultAppCreator)
                 SYS_TRAP (defaultHelperLibTrapSetDefaultHelper);

