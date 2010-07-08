/**
 * \file HsExgMgr.h
 *
 * Extensions to the Exchange Manager.  
 *
 * These functions are not currently supported by Palm, but the plan to
 * in future releases. They gave us these functions in sample code, and
 * we are moving into the system for OS 5 products so applications can
 * take advantage of them.
 *
 * \license
 *
 *    Copyright (c) 2002 Handspring Inc., All Rights Reserved
 *
 * \author Arun Mathias
 *
 * $Id:$
 *
 *****************************************************************************/
  

#ifndef HS_EXG_MGR__H
#define HS_EXG_MGR__H

Err HsExtExgSelectTarget( UInt16 id, const Char *dataTypeP, UInt32 *targetP)
                SYS_SEL_TRAP (sysTrapHsSelector, hsSelExgSelectTarget);


Err HsExtExgLocalAccept(ExgSocketPtr exgSocketP)
                SYS_SEL_TRAP (sysTrapHsSelector, hsSelExgLocalAccept);


Err HsExtExgLocalDisconnect(ExgSocketPtr exgSocketP, Err err)
                SYS_SEL_TRAP (sysTrapHsSelector, hsSelExgLocalDisconnect);
#endif
