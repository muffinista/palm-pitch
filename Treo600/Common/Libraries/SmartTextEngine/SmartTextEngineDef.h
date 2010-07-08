/*========================================================================*/
/* Project: 															  */
/*	  Smart Text Rendering Engine										  */
/*																		  */
/* Copyright(c) 2002 Handspring, Inc. All rights reserved.				  */
/*																		  */
/*	  This program is distributed in the hope that it will be useful,	  */
/*	  but WITHOUT ANY WARRANTY; without even the implied warranty of	  */
/*	  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.				  */
/*																		  */
/* FileName:															  */
/*	  SmartTextEngine.h 												  */
/*																		  */
/* Description: 														  */
/*	  Public include file for Smart Text Engine shared library			  */
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

#ifndef _SMARTTEXTENGINEDEF_H_
#define _SMARTTEXTENGINEDEF_H_

#include <PalmOS.h>

#include "SmartTextEngineErrors.h"


#ifdef __cplusplus
extern "C" {
#endif





#define steLibName			"SmartTextEngine.lib"	   // Internal library name which can(but shouldn't) 
														// be passed to SysLibFind() */
#define steLibDBName		"Smart Text Engine" 	   // Name used for DmFindDatabase */


// Parsed types

#define kParsedPhoneNumber		  1
#define kParsedURL				  2
#define kParsedEmail			  3


// Link colors (from the CLUT)
#define kSTECurrent 		254 		// taking a chance no one will use this index
#define kSTEBlack			255
#define kSTEBlue			95
#define kSTERed 			125
#define kSTEGreen			210
#define kSTEYellow			120
#define kSTEPurple			23
#define kSTEOrange			116
#define kSTEGray			220

// Color inverses
#define kSTEBlackInverse	0
#define kSTEBlueInverse 	114
#define kSTERedInverse		8
#define kSTEGreenInverse	18
#define kSTEYellowInverse	6
#define kSTEPurpleInverse	1
#define kSTEOrangeInverse	30
#define kSTEGrayInverse 	25



// Smart Text delimiters

// Use standard or bold font?
#define steStdFont			"//STESTDFONT//"
#define steBoldFont 		"//STEBOLDFONT//"

// Font colors
#define steCurrentFont		"//STECURRENTFONT//"
#define steBlackFont		"//STEBLACKFONT//"
#define steBlueFont 		"//STEBLUEFONT//"
#define steRedFont			"//STEREDFONT//"
#define steGreenFont		"//STEGREENFONT//"
#define steYellowFont		"//STEYELLOWFONT//"
#define stePurpleFont		"//STEPURPLEFONT//"
#define steOrangeFont		"//STEORANGEFONT//"
#define steGrayFont 		"//STEGRAYFONT//"

// Used for formatting
#define steLeftIndent		"//STELEFTINDENT="
#define steRightAlign		"//STERIGHTALIGN="
#define steCenterAlign		"//STECENTERALIGN//"

// Graphics support
#define steBitmap			"//STEBITMAP="
#define steSmileyBitmap 	"//STESMBITMAP="

// Miscellaneous
#define steHorizontalLine	"//STEHORIZONTALLINE//"
#define steLineBreak		"//STELINEBREAK//"

// Custom link that calls a callback procedure when selected
#define steHyperlink		"//STEHYPERLINK="




// use this parameter to scroll to the end of the list
#define kScrollToEnd				0xFFFF

// use these parameters when selecting text
#define kSelectUntilEndOfRecord		0xFFFFFFFE
#define kSelectUntilEnd 			0xFFFFFFFF

// use these when initializing the STE
#define steParsePhoneNumbers		0x00000001
#define steParseURLs				0x00000002
#define steParseEmail				0x00000004
#define steParseEmoticons			0x00000008
#define steLargeFont			    0x00000010
#define steCannotSelectText 		0x00000020
#define steParseMoreEmoticons	    0x00000040
#define steScrollWalksLinks 		0x00000080
#define steInvertHighlighting		0x00000100
#define steNoLinksBeforeColon		0x00000200
#define steAcceleratedScrolling		0x00000400
#define steAllowShortPhoneNumbers	0x00000800
#define steParseGSMGreekChars		0x00001000
#define steDoNotCenterVertically	0x00002000


// Used for custom hyperlinks
typedef void (*STECallbackType) (UInt32 refNum);


// This structure holds the parsed item information.  Given a message, or list of messages,
// this structure gives the locations of all parsed items.
typedef struct
{
  UInt16  parsedType;		  // what kind of data did we find?
  UInt16  startLocation;	  // the starting location of the parsed data we found
  UInt16  itemLength;		  // the character length of the parsed data we found
  UInt16  msgNumber;		  // when parsing a list of message, this is the message number, otherwise 0
  UInt16  color;			  // used to store the font color (for custom hyperlinks)
  UInt16  nameLength;		  // used to store the length of the link name (for custom hyperlinks)
  UInt32  miscData; 		  // used now to store left indentation and other info.  Adapt as needed.
} ParsedInfo;

typedef struct
{
  UInt16		size;		  // how many items did we find in the text?
  UInt16		maxSize;	  // maximum number of items that can be added without resizing
  // parsing info follows
  ParsedInfo	info[1];
} ParsedInfoList;



#ifdef __cplusplus 
}
#endif


#endif // _SMARTTEXTENGINEDEF_H_
