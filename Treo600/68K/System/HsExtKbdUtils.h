/** 
 * \file 68K/System/Prv/HsExtKbdUtils.h
 *
 * \license
 * 
 * Copyright (c) 2002 Handspring Inc., All Rights Reserved
 *
 * \author    Debbie Chyi
 * $Id:$
 *
 ****************************************************************/

#ifndef _HS_EXT_KBD_UTILS_H
#define _HS_EXT_KBD_UTILS_H

#include <Hs.h>

Int16
HsPostProcessPopupList (Boolean overrideFont, FontID overrideFontID)
		  SYS_SEL_TRAP (sysTrapHsSelector, hsSelPostProcessPopupList);


#endif // _HS_EXT_KBD_UTILS_H
