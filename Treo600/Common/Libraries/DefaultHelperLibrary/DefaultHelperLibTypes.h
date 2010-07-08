/**
 * \file Common/Libraries/TonesLibrary/DefaultHelperLibTypes.h
 *
 * <Brief description here>
 *
 * <Full description here>
 *
 * \license
 *
 *    Copyright (c) 2003 Handspring Inc., All Rights Reserved
 *
 * \author Priscilla Cinque
 *
 *****************************************************************************/

#ifndef DEFAULT_HELPER_LIB_TYPES__H__
#define DEFAULT_HELPER_LIB_TYPES__H__

#define      defaultHelperLibName				"Default Helper Library"

#define      defaultHelperLibCreator			'HsDh'

#define      defaultHelperLibType				sysFileTLibrary 

#define      defaultHelperLibErrClass			0x9000

#define      defaultHelperLibErrCreateDBFailed  (defaultHelperLibErrClass | 1)

#define      defaultHelperLibErrNoMemory        (defaultHelperLibErrClass | 2)

#define      defaultHelperLibErrNoHelperApp     (defaultHelperLibErrClass | 3)

#define      defaultHelperLibErrDBNotFound      (defaultHelperLibErrClass | 4)

#define      defaultHelperLibErrDBWriteFailed   (defaultHelperLibErrClass | 5)

#define      defaultHelperLibErrUserCancel      (defaultHelperLibErrClass | 6)

#define      defaultHelperLibErrBadParams       (defaultHelperLibErrClass | 7)

/**
 * Trap id for the function that gets the default helper for a specified service ID
 **/
#define       defaultHelperLibTrapGetDefaultHelper		sysLibTrapCustom 

/**
 * Trap id for the function that sets the default helper for a specified service ID
 **/
#define       defaultHelperLibTrapSetDefaultHelper		sysLibTrapCustom+1

#endif  // DEFAULT_HELPER_LIB_TYPES__H__

