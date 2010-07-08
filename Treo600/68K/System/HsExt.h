/** 
 * \file 68K/System/HsExt.h
 *
 * Header file that 68K programs include to access 
 * HsExtensions functionality.
 *
 * \license
 * 
 * Copyright (c) 2002 Handspring Inc., All Rights Reserved
 *
 * $Id:$
 *
 ****************************************************************/

#ifndef	  __HS_EXT_68K_H__
#define	  __HS_EXT_68K_H__

// Most of the definitions for HsExtensions are now in HsExtCommon.h so that 
// they can be shared by both 68K and ARM programs...
#include <Common/System/HsExtCommon.h>
#include <Common/System/HsCreators.h>
#include <68K/System/HsExtTraps.h>

#if (!(defined NO_HSEXT_TRAPS)) && (defined __GNUC__) && (EMULATION_LEVEL == EMULATION_NONE)
  #if __GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ >= 95)

	#ifndef _Str
	#define _Str(X)  #X
	#endif

	#define _OS_CALL_WITH_UNPOPPED_16BIT_SELECTOR(table, vector, selector)	\
		__attribute__ ((__callseq__ (										\
			"move.w #" _Str(selector) ",-(%%sp); "							\
			"trap #" _Str(table) "; dc.w " _Str(vector))))
	
	#define SYS_SEL_TRAP(trapNum, selector) \
		_OS_CALL_WITH_UNPOPPED_16BIT_SELECTOR(sysDispatchTrapNum, trapNum, selector)	
	    

  #else // GNUC < 2.95

	#define SYS_SEL_TRAP(trapNum, selector) \
	    __attribute__ ((inline (0x3f3c, selector, m68kTrapInstr+sysDispatchTrapNum,trapNum)))

  #endif // GNUC < 2.95

#elif (!(defined NO_HSEXT_TRAPS)) && (defined (__MWERKS__))

	#define SYS_SEL_TRAP(trapNum, selector) \
		= {0x3f3c, selector, m68kTrapInstr+sysDispatchTrapNum,trapNum}

#else
  	#define SYS_SEL_TRAP(trapNum, selector) 

#endif

void	
HsAboutHandspringApp (UInt16 appCardNo, LocalID appDbId,
					  Char* copyrightYearStrP, Char* extraCreditsStrP)
				SYS_SEL_TRAP (sysTrapHsSelector, hsSelAboutHandspringApp);

//ported from HsExt.h from the Visor-4.0 tree - VSB
// <chg 30-Jun-99 dia> Defined macros to make about box easier to call.
#define HsAboutHandspringAppWithYearId(yearId)								\
	do																		\
	  {																		\
		UInt16	appCardNo;													\
		LocalID	appDbId;													\
		MemHandle	yearStrH;												\
		Char* 	yearStrP;													\
																			\
		yearStrH = DmGetResource (strRsc, yearId);							\
		yearStrP = MemHandleLock (yearStrH);								\
		SysCurAppDatabase(&appCardNo, &appDbId);							\
		HsAboutHandspringApp (appCardNo, appDbId, yearStrP, NULL);			\
		MemPtrUnlock (yearStrP);											\
		DmReleaseResource (yearStrH);										\
	  }																		\
	while (0)
		
#define HsAboutHandspringAppWithYearCredId(yearId, creditsId)				\
	do																		\
	  {																		\
		UInt16	appCardNo;													\
		LocalID	appDbId;													\
		MemHandle	yearStrH, extraStrH;									\
		Char* 	yearStrP;													\
		Char*	extraStrP;													\
																			\
		yearStrH = DmGetResource (strRsc, yearId);							\
		yearStrP = MemHandleLock (yearStrH);								\
		extraStrH = DmGetResource (strRsc, creditsId);						\
		extraStrP = MemHandleLock (extraStrH);								\
		SysCurAppDatabase(&appCardNo, &appDbId);							\
		HsAboutHandspringApp (appCardNo, appDbId, yearStrP, extraStrP);		\
		MemPtrUnlock (extraStrP);											\
		DmReleaseResource (extraStrH);										\
		MemPtrUnlock (yearStrP);											\
		DmReleaseResource (yearStrH);										\
	  }																		\
	while (0)


Err
HsGetVersionString (UInt16 /*HsVerStrEnum*/selector, Char* outStrP,
					UInt16* sizeP)
				SYS_SEL_TRAP (sysTrapHsSelector, hsSelGetVersionString);

Err		
HsAttrGet (UInt16 /*HsAttrEnum*/ attr, UInt32 param, UInt32* valueP)
				SYS_SEL_TRAP (sysTrapHsSelector, hsSelAttrGet);

Err		
HsAttrSet (UInt16 /*HsAttrEnum*/ attr, UInt32 param, UInt32* valueP)
				SYS_SEL_TRAP (sysTrapHsSelector, hsSelAttrSet);

Err		
HsPrefGet (UInt16 /*HsPrefEnum*/ pref, void* bufP,
					UInt32* prefSizeP)
				SYS_SEL_TRAP (sysTrapHsSelector, hsSelPrefGet);

Err		
HsPrefSet (UInt16 /*HsPrefEnum*/ pref, void* bufP,
					UInt32 prefSize)
				SYS_SEL_TRAP (sysTrapHsSelector, hsSelPrefSet);


Err		
HsGetPhoneLibrary (UInt16 * refNum)
				SYS_SEL_TRAP (sysTrapHsSelector, hsSelGetPhoneLibrary);
Err		
HsStatusSetGadgetType (void* frmP, UInt16 gadgetID, 
								   UInt16 /*HsStatusGadgetTypeEnum*/ type)
				SYS_SEL_TRAP (sysTrapHsSelector, hsSelStatusSetGadgetType);

void	
HsStatusUpdateGadgets (void)
				SYS_SEL_TRAP (sysTrapHsSelector, hsSelStatusUpdateGadgets);

Err	
HsGrfSetStateExt (Boolean capsLock, Boolean numLock, Boolean optLock, 
				  Boolean upperShift, Boolean optShift, Boolean autoShift)
				SYS_SEL_TRAP (sysTrapHsSelector, hsSelGrfSetStateExt);

Err	
HsGrfGetStateExt (Boolean* capsLockP, Boolean* numLockP, Boolean* optLockP,
				  UInt16* tempShiftP, Boolean* autoShiftedP)
				SYS_SEL_TRAP (sysTrapHsSelector, hsSelGrfGetStateExt);

Boolean	HsPutObjectAfterTitle (void* voidFrmP, UInt16 objID, UInt8 titleOffset)
				SYS_SEL_TRAP (sysTrapHsSelector, hsSelPutObjectAfterTitle);


//HsInfo, HsEvtMetaEvent and HsSpringboardNotSupported are nop functions that are
//included for backwards compatibility
UInt32	
HsInfo (UInt16 item, UInt16 paramSize,  void* paramP)
				SYS_SEL_TRAP (sysTrapHsSelector, hsSelInfo);

UInt16	
HsEvtMetaEvent (EventPtr eventP)
				SYS_SEL_TRAP (sysTrapHsSelector, hsSelEvtMetaEvent);

Err		
HsSpringboardNotSupported (void)
				SYS_SEL_TRAP (sysTrapHsSelector, hsSelSpringboardNotSupported);

void*	
HsGetTrapAddress (UInt16 trapNum)
				SYS_SEL_TRAP (sysTrapHsSelector, hsSelHsGetTrapAddress);

// Disconnects all open NetLib connections.  ***IMPORTANT*** This function MUST
//  be called only from the context of the UI task!
Err		
HsNetworkDropConnection (void)
				SYS_SEL_TRAP (sysTrapHsSelector, hsSelNetworkDropConnection);


//will display a fatal error message since this trap number will not be handled by
//the trap dispatcher
void	
HsUnimplemented (void)
				SYS_SEL_TRAP (sysTrapHsSelector, hsSelUnimplemented);


// Returns the pointer to the ARM form. We need this because the 68K
// form might be deleted.
void*	
HsGetARMActiveFormPtr (void)
                SYS_SEL_TRAP (sysTrapHsSelector, hsSelGetARMActiveFormPtr);


FontID	
HsTwoFontSelect(FontID originalFont)
                SYS_SEL_TRAP (sysTrapHsSelector, hsSelTwoFontSelect);


void	
HsOpenDialNumberDialog(char* numberP, char* nameP, Boolean callerID)
                SYS_SEL_TRAP (sysTrapHsSelector, hsSelOpenDialNumberDialog);


Err		
HsTurnRadioOn(void)
                SYS_SEL_TRAP (sysTrapHsSelector, hsSelTurnRadioOn);


Err		
HsCreateNewMessage(char* addressP, char* nameP, char* msgP)
                SYS_SEL_TRAP (sysTrapHsSelector, hsSelCreateNewMessage);

Err		
HsCreateNewEmail(char* addressP, char* ccP, char* subjectP, char* msgP)
                SYS_SEL_TRAP (sysTrapHsSelector, hsSelCreateNewEmail);

Err		
HsBrowseUrl(char* urlP)
                SYS_SEL_TRAP (sysTrapHsSelector, hsSelBrowseUrl);

Err		
HsIndicatorState (UInt16 count, UInt16 indicatorType, UInt16* stateP)
                SYS_SEL_TRAP (sysTrapHsSelector, hsSelIndicatorState);

Err		
HsLightMode (Boolean set, UInt16* modeP)
                SYS_SEL_TRAP (sysTrapHsSelector, hsSelLightMode);

Err		
HsLightCircumstance (Boolean add, UInt16 circumstance)
                SYS_SEL_TRAP (sysTrapHsSelector, hsSelLightCircumstance);

void	
HsKeyCurrentStateExt (UInt32 keys[3])
                SYS_SEL_TRAP (sysTrapHsSelector, hsSelKeyCurrentStateExt);

void	
HsKeySetMaskExt (const UInt32 keyMaskNew[3], UInt32 keyMaskOld[3])
                SYS_SEL_TRAP (sysTrapHsSelector, hsSelKeySetMaskExt);

UInt16	
HsKeysPressed (UInt16 count, const UInt16 keyCodes[], Boolean pressed[])
                SYS_SEL_TRAP (sysTrapHsSelector, hsSelKeysPressed);

Err	
HsKeyStop (UInt16 keyCode)
                SYS_SEL_TRAP (sysTrapHsSelector, hsSelKeyStop);

Boolean 
HsKeyEnableKey (UInt16 keyCode, Boolean enabled)
                SYS_SEL_TRAP (sysTrapHsSelector, hsSelKeyEnableKey);

UInt16	
HsKeyChrCodeToKeyCode (UInt16 chrCode)
                SYS_SEL_TRAP (sysTrapHsSelector, hsSelKeyChrCodeToKeyCode);

void	
HsKeyKeyCodeToChrCode (UInt16 keyCode, UInt16 modifiersIn,
					   UInt16* chrP, UInt16* modifiersOutP)
                SYS_SEL_TRAP (sysTrapHsSelector, hsSelKeyKeyCodeToChrCode);

Boolean
HsKeyEventIsFromKeyboard (EventPtr eventP)
                SYS_SEL_TRAP (sysTrapHsSelector, hsSelKeyEventIsFromKeyboard);

Boolean 
HsExtDoSaveAsDialog (Char * name)
                SYS_SEL_TRAP (sysTrapHsSelector, hsSelDoSaveAsDialog);

UInt16
HsTxtPrepFindString(const Char* inSrcP, UInt16 inSrcLen,
						Char* outDstP, UInt16 inDstSize)
                SYS_SEL_TRAP (sysTrapHsSelector, hsSelTxtPrepFindString);

// These are convenient multi-byte friendly text routines
UInt32
HsTxtNumChars(Char const* textP)
                SYS_SEL_TRAP (sysTrapHsSelector, hsSelTxtNumChars);

void
HsTxtTruncateString(Char* textP, UInt16 maxPixels, Boolean keepLabel)
                SYS_SEL_TRAP (sysTrapHsSelector, hsSelTxtTruncateString);

Boolean
HsTxtIsAscii(Char* textP, UInt16 textLen)
                SYS_SEL_TRAP (sysTrapHsSelector, hsSelTxtIsAscii);

#endif	  // __HS_EXT_68K_H__
