/**
 * \file 68K/Libraries/FavoritesDBLibrary/FavoritesDBLib.h
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

Err FavDBLibOpen (UInt16 refNum)
                 SYS_TRAP (sysLibTrapOpen);

Err FavDBLibClose (UInt16 refNum)
                 SYS_TRAP (sysLibTrapClose);

Err FavDBLibWake (UInt16 refNum) 
                 SYS_TRAP (sysLibTrapWake);

Err FavDBLibSleep (UInt16 refNum)
                 SYS_TRAP (sysLibTrapSleep);

Err FavDBLibNewAppFavorite (UInt16 refNum,
							Word position, 
							CharPtr labelP,
							WChar quickKey,
							Word flags,
							UInt32 appCreator,
							WordPtr indexP)
                 SYS_TRAP (favoritesDBLibTrapNewAppFavorite);

Err FavDBLibNewPhoneFavorite (UInt16 refNum,
							  Word position, 
							  CharPtr labelP,
							  WChar quickKey,
							  Word flags,
							  CharPtr numberP,
							  CharPtr extraDigitsP,
							  Boolean autoDialExtraDigits,
							  UInt32 ringID,
							  WordPtr indexP)
                 SYS_TRAP (favoritesDBLibTrapNewPhoneFavorite);

Err FavDBLibNewMsgFavorite (UInt16 refNum,
							Word position, 
							CharPtr labelP,
							WChar quickKey,
							Word flags,		
							CharPtr contactIdP,
							WordPtr indexP)
				 SYS_TRAP (favoritesDBLibTrapNewMsgFavorite);

Err FavDBLibNewWebFavorite (UInt16 refNum,
							Word position, 
							CharPtr labelP,
							WChar quickKey,
							Word flags,		
							CharPtr urlP,
							WordPtr indexP)
				 SYS_TRAP (favoritesDBLibTrapNewWebFavorite);