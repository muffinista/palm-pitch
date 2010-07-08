/*========================================================================*/
/* Project: 															  */
/*	  Smart Text Rendering Engine										 */
/*																		  */
/* Copyright (c) 2002 Handspring, Inc. All rights reserved. 			  */
/*																		  */
/*	  This program is distributed in the hope that it will be useful,	  */
/*	  but WITHOUT ANY WARRANTY; without even the implied warranty of	  */
/*	  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.				  */
/*																		  */
/* FileName:															  */
/*	  SmartTextEngineTraps.h											 */
/*																		  */
/* Description: 														  */
/*	  Trap definitions for the Smart Text Engine shared library.		 */
/*																		  */
/* History: 															  */
/*	 15-Jul-2002 RJD Created by Rick Donald 							  */
/*========================================================================*/


#ifndef _SMARTTEXTENGINETRAPS_H_
#define _SMARTTEXTENGINETRAPS_H_


// Trap IDs for the Smart Text Engine Library's public functions. The order of the traps
// must be the same as the routines are listed in SmartTextEngineDispatchTable.c.
#define STETrapOpen 						sysLibTrapOpen
#define STETrapClose						sysLibTrapClose

#define STETrapGetAPIVersion				(sysLibTrapCustom + 0)
#define STETrapInitializeEngine 			(sysLibTrapCustom + 1)
#define STETrapResetEngine					(sysLibTrapCustom + 2)
#define STETrapReinitializeEngine			(sysLibTrapCustom + 3)
#define STETrapAppendTextToEngine			(sysLibTrapCustom + 4)
#define STETrapRemoveLastRecordFromEngine	(sysLibTrapCustom + 5)
#define STETrapRenderList					(sysLibTrapCustom + 6)
#define STETrapRerenderList 				(sysLibTrapCustom + 7)
#define STETrapHandleEvent					(sysLibTrapCustom + 8)
#define STETrapHandleSclRepeatEvent 		(sysLibTrapCustom + 9)
#define STETrapHandlePenDownEvent			(sysLibTrapCustom + 10)
#define STETrapHandlePenMoveEvent			(sysLibTrapCustom + 11)
#define STETrapHandlePenUpEvent 			(sysLibTrapCustom + 12)
#define STETrapHandleKeyDownEvent			(sysLibTrapCustom + 13)
#define STETrapGetScroll					(sysLibTrapCustom + 14)
#define STETrapSetScroll					(sysLibTrapCustom + 15)
#define STETrapGetScrollPct 				(sysLibTrapCustom + 16)
#define STETrapSetScrollPct 				(sysLibTrapCustom + 17)
#define STETrapSetScrollToRecordNum 		(sysLibTrapCustom + 18)
#define STETrapSetFlags 					(sysLibTrapCustom + 19)
#define STETrapGetNumLines					(sysLibTrapCustom + 20)
#define STETrapGetNumRecords				(sysLibTrapCustom + 21)
#define STETrapHasHotRectSelection			(sysLibTrapCustom + 22)
#define STETrapHasTextSelection 			(sysLibTrapCustom + 23)
#define STETrapClearCurrentSelection		(sysLibTrapCustom + 24)
#define STETrapSetCurrentTextSelection		(sysLibTrapCustom + 25)
#define STETrapGetCurrentTextSelection		(sysLibTrapCustom + 26)
#define STETrapGetSelectedText				(sysLibTrapCustom + 27)
#define STETrapCopySelectionToClipboard 	(sysLibTrapCustom + 28)
#define STETrapGetLastTapInfo				(sysLibTrapCustom + 29)
#define STETrapSetCustomHyperlinkCallback	(sysLibTrapCustom + 30)
#define STETrapGetFlags						(sysLibTrapCustom + 31)
#define STEDepracated4						(sysLibTrapCustom + 32)
#define STETrapGetParsedInformation 		(sysLibTrapCustom + 33)
#define STETrapAppendParsedInfo 			(sysLibTrapCustom + 34)
#define STEDepracated5						(sysLibTrapCustom + 35)
#define STETrapQuickRender					(sysLibTrapCustom + 36)

#endif /* _SMARTTEXTENGINETRAPS_H_ */
