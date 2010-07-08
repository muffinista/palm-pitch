/** 
 * \file 68K/System/HsNav.h
 *
 * Header file that 68K programs include to access 
 * HsNav functionality.
 *
 * \license
 * 
 * Copyright (c) 2002 Handspring Inc., All Rights Reserved
 *
 * $Id:$
 *
 ****************************************************************/

#ifndef	  __HS_NAV_68K_H__
#define	  __HS_NAV_68K_H__

// Most of the definitions for HsNav are in HsNavCommon.h so that 
// they can be shared by both 68K and ARM programs...
#include <Common/System/HsNavCommon.h>
#include <CoreTraps.h>

// SYS_SEL_TRAP technically should be defined here as it is defined at the
//	beginning of HsExt.h.  However, since HsNav.h is always included with
//	HsExt.h (Hs.h and HsInt.h include both), we are fine.  If HsNav.h is ever
//	included without HsExt.h, then we'll have to do something different.


UInt16
FrmCountObjectsInNavOrder (const FormType * formP)
		SYS_SEL_TRAP (sysTrapNavSelector, NavSelectorFrmCountObjectsInNavOrder);

Err
FrmGetNavOrder (const FormType* formP, FrmNavHeaderType* navHeaderP,
				FrmNavOrderEntryType* navOrderP, UInt16* numObjectsP)
		SYS_SEL_TRAP (sysTrapNavSelector, NavSelectorFrmGetNavOrder);

Err
FrmSetNavOrder (FormType* formP, FrmNavHeaderType* navHeaderP,
				FrmNavOrderEntryType* navOrderP)
		SYS_SEL_TRAP (sysTrapNavSelector, NavSelectorFrmSetNavOrder);

Err
FrmGetNavEntry (const FormType* formP, UInt16 targetObjectID,
				UInt16* afterObjectIDP, UInt16* aboveObjectIDP,
				UInt16* belowObjectIDP, FrmNavObjectFlagsType* objectFlagsP)
		SYS_SEL_TRAP (sysTrapNavSelector, NavSelectorFrmGetNavEntry);

Err
FrmSetNavEntry (FormType* formP, UInt16 targetObjectID, 
				UInt16 afterObjectID, UInt16 aboveObjectID, 
				UInt16 belowObjectID, FrmNavObjectFlagsType objectFlags)
		SYS_SEL_TRAP (sysTrapNavSelector, NavSelectorFrmSetNavEntry);

Err
FrmGetNavState (const FormType* formP, FrmNavStateFlagsType* stateFlagsP)
		SYS_SEL_TRAP (sysTrapNavSelector, NavSelectorFrmGetNavState);

Err
FrmSetNavState (FormType* formP, FrmNavStateFlagsType stateFlags)
		SYS_SEL_TRAP (sysTrapNavSelector, NavSelectorFrmSetNavState);


void
HsNavGetFocusColor (HsNavFocusColorEnum color, RGBColorType* rgbColorP)
		SYS_SEL_TRAP (sysTrapHsSelector, hsSelNavGetFocusColor);

void
HsNavSetFocusColor (HsNavFocusColorEnum color, RGBColorType* rgbColorP,
					RGBColorType* oldRgbColorP)
		SYS_SEL_TRAP (sysTrapHsSelector, hsSelNavSetFocusColor);

Err
HsNavGetFocusRingInfo (const FormType* formP, UInt16* objectIDP, 
					   Int16* extraInfoP, RectangleType* boundsInsideRingP,
					   HsNavFocusRingStyleEnum* ringStyleP)
		SYS_SEL_TRAP (sysTrapHsSelector, hsSelNavGetFocusRingInfo);

Err
HsNavDrawFocusRing (FormType* formP, UInt16 objectID, Int16 extraInfo,
				    RectangleType* boundsInsideRingP,
					HsNavFocusRingStyleEnum ringStyle, Boolean forceRestore)
		SYS_SEL_TRAP (sysTrapHsSelector, hsSelNavDrawFocusRing);

Err
HsNavRemoveFocusRing (FormType* formP)
		SYS_SEL_TRAP (sysTrapHsSelector, hsSelNavRemoveFocusRing);

Int16
HsNavLstGetTempSelection (const FormType* formP, UInt16 listID)
		SYS_SEL_TRAP (sysTrapHsSelector, hsSelNavLstGetTempSelection);

void 
HsNavLstSetTempSelection (const FormType* formP, UInt16 listID, Int16 itemNum)
		SYS_SEL_TRAP (sysTrapHsSelector, hsSelNavLstSetTempSelection);

void
HsNavObjectTakeFocus (const FormType* formP, UInt16 objID)
		SYS_SEL_TRAP (sysTrapHsSelector, hsSelNavObjectTakeFocus);


#endif	  // __HS_NAV_68K_H__
