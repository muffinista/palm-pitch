/***************************************************************
 *
 *  Project:
 *	  Carrier Customization library
 *
 * Copyright info:
 *
 *	  Copyright (c) Handspring 2002 -- All Rights Reserved
 *
 *
 *  FileName:
 *	  CarrierCustomizationLibraryTraps.h
 * 
 *  Description:
 *	  Trap definitions for the Carrier Customization Library.
 *
 *	Note:
 *
 *	History:
 *	  11-Dec-2002	dla	  Created
 *
 ****************************************************************/


#ifndef __CARRIER_CUSTOMIZATION_LIBRARY_TRAPS_H__
#define __CARRIER_CUSTOMIZATION_LIBRARY_TRAPS_H__


// Trap IDs for the Carrier Customization Library's public functions. The order of the traps
// must be the same as the routines are listed in NetPrefLibDispatchTable.c.
#define CCustomLibTrapVersionGet                   (sysLibTrapCustom + 0)
#define CCustomLibTrapGetCarrierSetting            (sysLibTrapCustom + 1)
#define CCustomLibTrapGetProfileSetting            (sysLibTrapCustom + 2)
#define CCustomLibTrapGetCarrierProfile            (sysLibTrapCustom + 3)
#define CCustomLibTrapReleaseCarrierProfile        (sysLibTrapCustom + 4)
#define CCustomLibTrapGetCarrierCode               (sysLibTrapCustom + 5)
#define CCustomLibTrapGetCarrierCodeLength         (sysLibTrapCustom + 6)
#define CCustomLibTrapRefresh                      (sysLibTrapCustom + 7)
#define CCustomLibTrapRetrieveNVSetting            (sysLibTrapCustom + 8)

#endif // __CARRIER_CUSTOMIZATION_LIBRARY_TRAPS_H__
