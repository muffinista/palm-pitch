/*========================================================================*/
/* Project: 															  */
/*	  Smart Text Engine 												  */
/*																		  */
/* Copyright(c) 2002-2003 Handspring, Inc. All rights reserved.			  */
/*																		  */
/*	  This program is distributed in the hope that it will be useful,	  */
/*	  but WITHOUT ANY WARRANTY; without even the implied warranty of	  */
/*	  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.				  */
/*																		  */
/* FileName:															  */
/*	  StyledTextEngine.h												  */
/*																		  */
/* Description: 														  */
/*	  Public 68K include file for Smart Text Engine shared library	 	  */
/*																		  */
/* Notes:																  */
/*	  The calling application should always load this library with		  */
/*	  SysLibLoad() before use, even if it is already open by another	  */
/*	  application(ie, SysLibFind() returns a valid refnum). When		  */
/*	  the application is done with the library, it should be			  */
/*	  unloaded with SysLibRemove(). We do this because there is 		  */
/*	  no good way to synchronize loading and unloading of libraries 	  */
/*	  among multiple applications. It also greatly simplifies internal	  */
/*	  synchronization.													  */
/*																		  */
/* History: 															  */
/*	 15-Jul-2002 RJD Created by Rick Donald 							  */
/*========================================================================*/

#ifndef __SMARTTEXTENGINE68K_H__
#define __SMARTTEXTENGINE68K_H__

#include <PalmTypes.h>
#include <LibTraps.h>

#include <Common/Libraries/SmartTextEngine/SmartTextEngineTraps.h>
#include <Common/Libraries/SmartTextEngine/SmartTextEngineDef.h>
#include <Common/Libraries/SmartTextEngine/SmartTextEngineErrors.h>


#ifdef __cplusplus
extern "C" {
#endif


// Standard library open routine.
// Library should always be loaded with SysLibLoad()(not SysLibFind())
// before calling STEOpen(). See note at top of file.
// 
// @param refnum		  IN  Library reference number
// @retval STEErr				 Library error code
extern STEErr STEOpen(UInt16 refNum)
	SYS_TRAP(sysLibTrapOpen);

// Standard library close routine.
// Library should always be unloaded with SysLibRemove() after
// STEClose() is called. See note at top of file.
// 
// @param refnum		  IN  Library reference number
// @retval STEErr				 Library error code
extern STEErr STEClose(UInt16 refNum)
	SYS_TRAP(sysLibTrapClose);


// Get Library API Version number.
// 
// @param refnum		  IN  Library reference number
// @param majVerP		  OUT Major version number
// @param minVerP		  OUT Minor version number
// @retval STEErr		  Styled Text Engine error code
extern STEErr STEGetAPIVersion(UInt16 refNum, UInt32* majVerP, UInt32* minVerP)
	SYS_TRAP(STETrapGetAPIVersion);



// Styled Text Engine initialization functions

// Function:	STEInitializeEngine
//
// Summary: 	Before most of the STE can be used, it must be initialized.  This function will return
//				an engineRefNum which is to be used in the STE functions that require the STE
//				to be initialized.
//
// Note:		There are some functions that do not require the STE to be initialized.  They are noted below.
//
// Parameters:
//	  refNum:			IN:   The STE refNum
//	  engineRefNum: 	OUT:  The STE engine refNum to be used in subsequent calls to the STE
//	  listBounds:		IN:   The bounds of the STE list that will be displayed
//	  scrollBarID:		IN:   The ID of the scroll used by the STE list.  If this is 0, the list will not
//							  scroll.  If there is more text than can be displayed, an ellipsis will be
//							  appended to the end.
//	  flags:			IN:   The flags for the STE
//	  phoneNumberColor: IN:   The color of the phone number hyperlinks
//	  urlColor: 		IN:   The color of the URL hyperlinks
//	  emailColor:		IN:   The color of the email hyperlinks
//
// Returns: 	0 if success, else the error number.
//	  
extern STEErr STEInitializeEngine(UInt16 refNum, UInt16* engineRefNum, RectangleType* listBounds, UInt16 scrollBarID, UInt32 flags, 
								  UInt8 phoneNumberColor, UInt8 urlColor, UInt8 emailColor)
	SYS_TRAP(STETrapInitializeEngine);

// Function:	STEResetEngine
//
// Summary: 	Frees up the STE engine refNum.  For each STEInitializeEngine, there must be a corresponding
//				STEResetEngine.
//
// Parameters:
//	  refNum:			IN:   The STE refNum
//	  engineRefNum: 	IN:   The STE engine refNum
//
// Returns: 	0 if success, else the error number.
//	  
extern STEErr STEResetEngine(UInt16 refNum, UInt16 engineRefNum)
	SYS_TRAP(STETrapResetEngine);

// Function:	STEReinitializeEngine
//
// Summary: 	Initializes the STE to the initial state right after initializing it.  This frees up any text that
//				has been entered into the STE.
//
// Parameters:
//	  refNum:			IN:   The STE refNum
//	  engineRefNum: 	IN:   The STE engine refNum
//
// Returns: 	0 if success, else the error number.
//	  
extern STEErr STEReinitializeEngine(UInt16 refNum, UInt16 engineRefNum)
	SYS_TRAP(STETrapReinitializeEngine);


// Styled Text Engine main functions

// Function:	STEAppendTextToEngine
//
// Summary: 	This is the function that is used to add text to the STE.  Each text string that is appended
//				is called a record.  Record numbers are 1 based, meaning the first record is record 1.
//
// Parameters:
//	  refNum:			IN:   The STE refNum
//	  engineRefNum: 	IN:   The STE engine refNum
//	  textP:			IN:   The text to append to the STE, including any STE delimiters
//	  renderImmediate:	IN:   If true, the text will be displayed immediately.	If false, it
//							  will not be displayed until STERenderList is called.
//	  
extern void STEAppendTextToEngine(UInt16 refNum, UInt16 engineRefNum, Char* textP, Boolean renderImmediate)
	SYS_TRAP(STETrapAppendTextToEngine);

// Function:	STERemoveLastRecordFromEngine
//
// Summary: 	Removes the last text that was appended to the engine.
//
// Note:		You must call STERenderList to update the display after removing the text.
//
// Parameters:
//	  refNum:			IN:   The STE refNum
//	  engineRefNum: 	IN:   The STE engine refNum
//	  
extern void STERemoveLastRecordFromEngine(UInt16 refNum, UInt16 engineRefNum)
	SYS_TRAP(STETrapRemoveLastRecordFromEngine);

// Function:	STERenderList
//
// Summary: 	Renders the text that is currently in the STE.
//
// Parameters:
//	  refNum:			IN:   The STE refNum
//	  engineRefNum: 	IN:   The STE engine refNum
//	  
extern void STERenderList(UInt16 refNum, UInt16 engineRefNum)
	SYS_TRAP(STETrapRenderList);

// Function:	STERerenderList
//
// Summary: 	Rerenders the text that is currently in the STE.  This routine should be used if a change is made
//				that can change the formatting (i.e. font size).
//
// Parameters:
//	  refNum:			IN:   The STE refNum
//	  engineRefNum: 	IN:   The STE engine refNum
//	  
extern void STERerenderList(UInt16 refNum, UInt16 engineRefNum)
	SYS_TRAP(STETrapRerenderList);


// event handlers

// Function:	STEHandleEvent
//
// Summary: 	This routine should be called in the form's event handler.	If there is no special handling of
//				events, then this routine can be used to handle all the different events that can affect the STE.
//
// Parameters:
//	  refNum:			IN:   The STE refNum
//	  engineRefNum: 	IN:   The STE engine refNum
//	  eventP:			IN:   A pointer to the event record.
//	  
extern Boolean STEHandleEvent(UInt16 refNum, UInt16 engineRefNum, EventPtr eventP)
	SYS_TRAP(STETrapHandleEvent);

// Function:	STEHandleSclRepeatEvent
//
// Summary: 	This routine handles only the sclRepeat event.	This routine should be used if there is special
//				handling of the events by the application before (or after) the STE handles the event.
//
// Parameters:
//	  refNum:			IN:   The STE refNum
//	  engineRefNum: 	IN:   The STE engine refNum
//	  eventP:			IN:   A pointer to the event record.
//	  
extern Boolean STEHandleSclRepeatEvent(UInt16 refNum, UInt16 engineRefNum, EventPtr eventP)
	SYS_TRAP(STETrapHandleSclRepeatEvent);

// Function:	STEHandlePenDownEvent
//
// Summary: 	This routine handles only the penDown event.  This routine should be used if there is special
//				handling of the events by the application before (or after) the STE handles the event.
//
// Parameters:
//	  refNum:			IN:   The STE refNum
//	  engineRefNum: 	IN:   The STE engine refNum
//	  eventP:			IN:   A pointer to the event record.
//	  
extern Boolean STEHandlePenDownEvent(UInt16 refNum, UInt16 engineRefNum, EventPtr eventP)
	SYS_TRAP(STETrapHandlePenDownEvent);

// Function:	STEHandlePenMoveEvent
//
// Summary: 	This routine handles only the penMove event.  This routine should be used if there is special
//				handling of the events by the application before (or after) the STE handles the event.
//
// Parameters:
//	  refNum:			IN:   The STE refNum
//	  engineRefNum: 	IN:   The STE engine refNum
//	  eventP:			IN:   A pointer to the event record.
//	  
extern Boolean STEHandlePenMoveEvent(UInt16 refNum, UInt16 engineRefNum, EventPtr eventP)
	SYS_TRAP(STETrapHandlePenMoveEvent);

// Function:	STEHandlePenUpEvent
//
// Summary: 	This routine handles only the penUp event.	This routine should be used if there is special
//				handling of the events by the application before (or after) the STE handles the event.
//
// Parameters:
//	  refNum:			IN:   The STE refNum
//	  engineRefNum: 	IN:   The STE engine refNum
//	  eventP:			IN:   A pointer to the event record.
//	  
extern Boolean STEHandlePenUpEvent(UInt16 refNum, UInt16 engineRefNum, EventPtr eventP)
	SYS_TRAP(STETrapHandlePenUpEvent);

// Function:	STEHandleKeyDownEvent
//
// Summary: 	This routine handles only the keyDown event.  This routine should be used if there is special
//				handling of the events by the application before (or after) the STE handles the event.
//
// Parameters:
//	  refNum:			IN:   The STE refNum
//	  engineRefNum: 	IN:   The STE engine refNum
//	  eventP:			IN:   A pointer to the event record.
//	  
extern Boolean STEHandleKeyDownEvent(UInt16 refNum, UInt16 engineRefNum, EventPtr eventP)
	SYS_TRAP(STETrapHandleKeyDownEvent);


// Accessor functions

// Function:	STEGetScroll
//
// Summary: 	This routine returns the current scroll position of the STE's scroll bar.
//
// Parameters:
//	  refNum:			IN:   The STE refNum
//	  engineRefNum: 	IN:   The STE engine refNum
//
// Returns: 	The position of the scroll bar.
//	  
extern UInt16 STEGetScroll(UInt16 refNum, UInt16 engineRefNum)
	SYS_TRAP(STETrapGetScroll);

// Function:	STESetScroll
//
// Summary: 	This routine sets the current scroll position of the STE's scroll bar.
//
// Parameters:
//	  refNum:			IN:   The STE refNum
//	  engineRefNum: 	IN:   The STE engine refNum
//	  scrollValue:		IN:   The position to set the scroll bar
//	  
extern void STESetScroll(UInt16 refNum, UInt16 engineRefNum, UInt16 scrollValue)
	SYS_TRAP(STETrapSetScroll);

// Function:	STEGetScrollPct
//
// Summary: 	This routine returns the current scroll position of the STE's scroll bar as a percentage
//				of the entire scroll bar.
//
// Parameters:
//	  refNum:			IN:   The STE refNum
//	  engineRefNum: 	IN:   The STE engine refNum
//
// Returns: 	The position of the scroll bar in percentage.
//	  
extern UInt16 STEGetScrollPct(UInt16 refNum, UInt16 engineRefNum)
	SYS_TRAP(STETrapGetScrollPct);

// Function:	STESetScrollPct
//
// Summary: 	This routine sets the current scroll position percentage of the STE's scroll bar.
//
// Parameters:
//	  refNum:			IN:   The STE refNum
//	  engineRefNum: 	IN:   The STE engine refNum
//	  scrollPct:		IN:   The position to set the scroll bar in percentage
//	  
extern void STESetScrollPct(UInt16 refNum, UInt16 engineRefNum, UInt16 scrollPct)
	SYS_TRAP(STETrapSetScrollPct);

// Function:	STESetScrollToRecordNum
//
// Summary: 	This routine sets the current scroll bar position so that the specified record
//				appears at the top of the list.
//
// Parameters:
//	  refNum:			IN:   The STE refNum
//	  engineRefNum: 	IN:   The STE engine refNum
//	  recordNum:		IN:   The record number to display at the top of the list.
//	  
extern void STESetScrollToRecordNum(UInt16 refNum, UInt16 engineRefNum, UInt16 recordNum)
	SYS_TRAP(STETrapSetScrollToRecordNum);

// Function:	STESetFlags
//
// Summary: 	This routine sets the STE flags
//
// Parameters:
//	  refNum:			IN:   The STE refNum
//	  engineRefNum: 	IN:   The STE engine refNum
//	  flagsToSet:		IN:   Bitmap representing the flags to set
//	  flagsToClear: 	IN:   Bitmap representing the flags to clear
//	  
extern void STESetFlags(UInt16 refNum, UInt16 engineRefNum, UInt32 flagsToSet, UInt32 flagsToClear)
	SYS_TRAP(STETrapSetFlags);

// Function:	STEGetFlags
//
// Summary: 	This routine returns the current STE flags
//
// Parameters:
//	  refNum:			IN:   The STE refNum
//	  engineRefNum: 	IN:   The STE engine refNum
//
// Returns: 	The STE flags
//	  
extern UInt32 STEGetFlags(UInt16 refNum, UInt16 engineRefNum)
	SYS_TRAP(STETrapGetFlags);

// Function:	STEGetNumLines
//
// Summary: 	This routine returns the number of lines in the STE.
//
// Parameters:
//	  refNum:			IN:   The STE refNum
//	  engineRefNum: 	IN:   The STE engine refNum
//
// Returns: 	Number of lines in the STE
//	  
extern UInt16 STEGetNumLines(UInt16 refNum, UInt16 engineRefNum)
	SYS_TRAP(STETrapGetNumLines);

// Function:	STEGetNumRecords
//
// Summary: 	This routine returns the number of records in the STE.
//
// Parameters:
//	  refNum:			IN:   The STE refNum
//	  engineRefNum: 	IN:   The STE engine refNum
//
// Returns: 	Number of records in the STE
//	  
extern UInt16 STEGetNumRecords(UInt16 refNum, UInt16 engineRefNum)
	SYS_TRAP(STETrapGetNumRecords);

// Function:	STEHasHotRectSelection
//
// Summary: 	This routine checks if there is a current hot rect selection.  A hot rect
//				is a hyperlink that has been selected with the keyboard.
//
// Parameters:
//	  refNum:			IN:   The STE refNum
//	  engineRefNum: 	IN:   The STE engine refNum
//
// Returns: 	True if there is a current hot rect selected
//	  
extern Boolean STEHasHotRectSelection(UInt16 refNum, UInt16 engineRefNum)
	SYS_TRAP(STETrapHasHotRectSelection);

// Function:	STEHasTextSelection
//
// Summary: 	This routine checks if there is any text currently selected.
//
// Parameters:
//	  refNum:			IN:   The STE refNum
//	  engineRefNum: 	IN:   The STE engine refNum
//
// Returns: 	True if there is any text selected
//	  
extern Boolean STEHasTextSelection(UInt16 refNum, UInt16 engineRefNum)
	SYS_TRAP(STETrapHasTextSelection);

// Function:	STEClearCurrentSelection
//
// Summary: 	This routine clears any currently selected text or hot rect.
//
// Parameters:
//	  refNum:			IN:   The STE refNum
//	  engineRefNum: 	IN:   The STE engine refNum
//	  
extern void STEClearCurrentSelection(UInt16 refNum, UInt16 engineRefNum)
	SYS_TRAP(STETrapClearCurrentSelection);

// Function:	STESetCurrentTextSelection
//
// Summary: 	This routine will select the specified text selection.	The display will be updated
//				to show the selected text as highlighted.
//
// Parameters:
//	  refNum:			IN:   The STE refNum
//	  engineRefNum: 	IN:   The STE engine refNum
//	  messageNumber:	IN:   The record number to start the selection
//	  startLocation:	IN:   The byte offset to start the text selection
//	  selectionLength:	IN:   The number of bytes in the text selection
//
// Returns: 	Returns the line number of the topmost line of the selection
//	  
extern UInt16 STESetCurrentTextSelection(UInt16 refNum, UInt16 engineRefNum, UInt16 messageNumber, UInt32 startLocation, UInt32 selectionLength)
	SYS_TRAP(STETrapSetCurrentTextSelection);

// Function:	STEGetCurrentTextSelection
//
// Summary: 	This routine will select the specified text selection.	The display will be updated
//				to show the selected text as highlighted.
//
// Parameters:
//	  refNum:			IN:   The STE refNum
//	  engineRefNum: 	IN:   The STE engine refNum
//	  messageNumber:	OUT:  The record number of the start the selection
//	  startLocation:	OUT:  The byte offset of the start the text selection
//	  selectionLength:	OUT:  The number of bytes in the text selection
//	  
extern void STEGetCurrentTextSelection(UInt16 refNum, UInt16 engineRefNum, UInt16* messageNumber, UInt16* startLocation, UInt16* selectionLength)
	SYS_TRAP(STETrapGetCurrentTextSelection);

// Function:	STEGetSelectedText
//
// Summary: 	This routine returns a copy of the actual text that is currently selected.
//
// Parameters:
//	  refNum:			IN:   The STE refNum
//	  engineRefNum: 	IN:   The STE engine refNum
//
// Returns: 	Returns a copy of the current text selection.  This must be freed by the caller.
//	  
extern Char* STEGetSelectedText(UInt16 refNum, UInt16 engineRefNum)
	SYS_TRAP(STETrapGetSelectedText);

// Function:	STECopySelectionToClipboard
//
// Summary: 	This routine copies the selected text to the system's clipboard.
//
// Parameters:
//	  refNum:			IN:   The STE refNum
//	  engineRefNum: 	IN:   The STE engine refNum
//
extern void STECopySelectionToClipboard(UInt16 refNum, UInt16 engineRefNum)
	SYS_TRAP(STETrapCopySelectionToClipboard);

// Function:	STEGetLastTapInfo
//
// Summary: 	This routine returns the location of the last tap.	If the user drags the stylus, it is not a tap.
//
// Parameters:
//	  refNum:			IN:   The STE refNum
//	  engineRefNum: 	IN:   The STE engine refNum
//	  messageNumber:	OUT:  The record number of the text that was tapped
//	  tapLocation:		OUT:  The number of bytes offset from the start of the text to the location tapped
//
extern void STEGetLastTapInfo(UInt16 refNum, UInt16 engineRefNum, UInt16* messageNumber, UInt16* tapLocation)
	SYS_TRAP(STETrapGetLastTapInfo);

// Function:	STESetCustomHyperlinkCallback
//
// Summary: 	This routine sets the procedure to call as a result of tapping a custom hyperlink
//
// Parameters:
//	  refNum:			IN:   The STE refNum
//	  engineRefNum: 	IN:   The STE engine refNum
//	  callback: 		IN:   The routine to call
//	  armCallback:		IN:   True if the callback routine is ARM code, false if it is 68K code
//
extern void STESetCustomHyperlinkCallback(UInt16 refNum, UInt16 engineRefNum, STECallbackType callback, Boolean armCallback)
	SYS_TRAP(STETrapSetCustomHyperlinkCallback);


// Cool helper function that does not require the engine to be initialized

// Function:	STEQuickRender
//
// Summary: 	This routine will render the specified text as a "one shot deal".  The text will
//				not respond to any events, and hyperlinks do not work.	This can be used to display
//				rich text with graphics easily in your application.
//
// Note:		This does NOT require the STE to be initialized.
//
// Parameters:
//	  refNum:			IN:   The STE refNum
//	  listBounds:		IN:   The bounds of the STE list that will be displayed
//	  flags:			IN:   The flags for the STE
//	  phoneNumberColor: IN:   The color of the phone number hyperlinks
//	  urlColor: 		IN:   The color of the URL hyperlinks
//	  emailColor:		IN:   The color of the email hyperlinks
//	  msgP: 			IN:   The text to display
//
extern void STEQuickRender(UInt16 refNum, RectangleType* listBounds, UInt32 flags,
						   UInt8 phoneNumberColor, UInt8 urlColor, UInt8 emailColor, Char* msgP)
	SYS_TRAP(STETrapQuickRender);



// These are parsing functions that do not require the engine to be initialized

// Function:	STEGetParsedInformation
//
// Summary: 	This routine will parse the text string for URLs, email addresses, and/or phone numbers.
//
// Note:		This does NOT require the STE to be initialized.
//
// Parameters:
//	  refNum:			IN:   The STE refNum
//	  textP:			IN:   The text string to parse
//	  msgNumber:		IN:   The message number of this text string  (Used internally by the STE)
//	  replaceLineFeeds: IN:   If true, any line feed will be replaced with a space, but a parsed item will be create
//							  that specifies a line feed to be at that location
//	  flags:			IN:   The flags indicating what type of item to parse out
//
// Returns: 	A parsed info list that has each of the parsed items found in the text string.
//
extern ParsedInfoList* STEGetParsedInformation(UInt16 refNum, Char* textP, UInt16 msgNumber, Boolean replaceLineFeeds, UInt32 flags)
	SYS_TRAP(STETrapGetParsedInformation);

// Function:	STEAppendParsedInfo
//
// Summary: 	This routine append a ParsedInfoList to another ParsedInfoList.
//
// Note:		This does NOT require the STE to be initialized.
//
// Parameters:
//	  refNum:			IN:   The STE refNum
//	  destParsedInfoH:	IN:   A handle to the destination parsed info list
//	  sourceParsedInfoP:IN:   The source parsed info list.
//
// Note:		This is used internally by the STE.  You probably will not use this function.
//
extern void STEAppendParsedInfo(UInt16 refNum, MemHandle destParsedInfoH, ParsedInfoList* sourceParsedInfoP)
	SYS_TRAP(STETrapAppendParsedInfo);



#ifdef __cplusplus 
}
#endif




#endif	//__SMARTTEXTENGINE68K_H__
