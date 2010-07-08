/*========================================================================*/
/* Project:                                                               */
/*    Styled Text Rendering Engine                                        */
/*                                                                        */
/* Copyright (c) 2002 Handspring, Inc. All rights reserved.               */
/*                                                                        */
/*    This program is distributed in the hope that it will be useful,     */
/*    but WITHOUT ANY WARRANTY; without even the implied warranty of      */
/*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                */
/*                                                                        */
/* FileName:                                                              */
/*    SmartTextEngineErrors.h                                             */
/*                                                                        */
/* Description:                                                           */
/*	  Error codes for Smart Text Engine shared library                    */
/*                                                                        */
/* History:                                                               */
/*   15-Jul-2002 RJD Created by Rick Donald                               */
/*========================================================================*/


#ifndef _SMARTTEXTENGINEERRORS_H_
#define _SMARTTEXTENGINEERRORS_H_

//#include "Hs.h"

typedef UInt32 STEErr;

// Maybe one day I will implement all of these different errors
#define steErrBase                  hsSTEErrorClass
#define steErrUnimplemented         (steErrBase + 1)    // Functionality not currently implemented
#define steErrInternal              (steErrBase + 2)    // Unspecified internal error */
#define steErrDynamicMemory         (steErrBase + 3)    // Dynamic memory allocation failed */
#define steErrStorageMemory         (steErrBase + 4)    // Storage memory allocation failed */
#define steErrOperationNotAllowed   (steErrBase + 5)    // Operation cannot be performed at this time */
#define steErrInvalidArguments      (steErrBase + 6)    // Bad arguments */
#define steErrSTEInit			    (steErrBase + 7)    // STE initialization failed */

#endif // _SMARTTEXTENGINEERRORS_H_
