/**
 * \file Common/Libraries/TonesLibrary/FavoritesDBLibTypes.h
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

#ifndef FAVORITESDB_LIB_TYPES__H__
#define FAVORITESDB_LIB_TYPES__H__

#define      favoritesDBLibName				"FavoritesDB Library"

#define      favoritesDBLibCreator			'HsFD'

#define      favoritesDBLibType				sysFileTLibrary 

#define      favoritesDBLibErrClass			0x9000

#define      favoritesDBLibErrCreateDBFailed  (favoritesDBLibErrClass | 1)

#define      favoritesDBLibErrNoMemory        (favoritesDBLibErrClass | 2)

#define      favoritesDBLibErrDBNotFound      (favoritesDBLibErrClass | 4)

#define      favoritesDBLibErrDBWriteFailed   (favoritesDBLibErrClass | 5)

#define      favoritesDBLibErrUserCancel      (favoritesDBLibErrClass | 6)

#define      favoritesDBLibErrBadParams       (favoritesDBLibErrClass | 7)

/**
 * Trap id for the function that creates a new application favorite
 **/
#define       favoritesDBLibTrapNewAppFavorite		sysLibTrapCustom 

/**
 * Trap id for the function that creates a new phone favorite
 **/
#define       favoritesDBLibTrapNewPhoneFavorite	sysLibTrapCustom+1

/**
 * Trap id for the function that creates a new message favorite
 **/
#define       favoritesDBLibTrapNewMsgFavorite		sysLibTrapCustom+2

/**
 * Trap id for the function that creates a new web link favorite
 **/
#define       favoritesDBLibTrapNewWebFavorite		sysLibTrapCustom+3

#endif  // FAVORITESDB_LIB_TYPES__H__

