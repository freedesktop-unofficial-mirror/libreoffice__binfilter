/*************************************************************************
 *
 *  $RCSfile: progress.hxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:23:28 $
 *
 *  The Contents of this file are made available subject to the terms of
 *  either of the following licenses
 *
 *         - GNU Lesser General Public License Version 2.1
 *         - Sun Industry Standards Source License Version 1.1
 *
 *  Sun Microsystems Inc., October, 2000
 *
 *  GNU Lesser General Public License Version 2.1
 *  =============================================
 *  Copyright 2000 by Sun Microsystems, Inc.
 *  901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License version 2.1, as published by the Free Software Foundation.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *  MA  02111-1307  USA
 *
 *
 *  Sun Industry Standards Source License Version 1.1
 *  =================================================
 *  The contents of this file are subject to the Sun Industry Standards
 *  Source License Version 1.1 (the "License"); You may not use this file
 *  except in compliance with the License. You may obtain a copy of the
 *  License at http://www.openoffice.org/license.html.
 *
 *  Software provided under this License is provided on an "AS IS" basis,
 *  WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING,
 *  WITHOUT LIMITATION, WARRANTIES THAT THE SOFTWARE IS FREE OF DEFECTS,
 *  MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE, OR NON-INFRINGING.
 *  See the License for the specific provisions governing your rights and
 *  obligations concerning the Software.
 *
 *  The Initial Developer of the Original Code is: Sun Microsystems, Inc.
 *
 *  Copyright: 2000 by Sun Microsystems, Inc.
 *
 *  All Rights Reserved.
 *
 *  Contributor(s): _______________________________________
 *
 *
 ************************************************************************/
#ifndef _SFX_PROGRESS_HXX
#define _SFX_PROGRESS_HXX

#include <tools/solar.h>

#ifndef _LINK_HXX
#include <tools/link.hxx>
#endif

class String;
class SfxObjectShell;
class SfxStatusBarManager;
class INetHint;
class SvDispatch;
struct SfxProgress_Impl;
struct PlugInLoadStatus;
struct SvProgressArg;

//=======================================================================

class SfxProgress
{
    SfxProgress_Impl*       pImp;
    ULONG                   nVal;
    BOOL                    bSuspended;

public:
#if SUPD>=349
                            SfxProgress( SfxObjectShell* pObjSh,
                                         const String& rText,
                                         ULONG nRange, BOOL bAllDocs = FALSE,
                                         BOOL bWait = TRUE );
#else
                            SfxProgress( SfxObjectShell* pObjSh,
                                         const String& rText,
                                         ULONG nRange, BOOL bAllDocs = FALSE );
#endif
    virtual                 ~SfxProgress();

    virtual void            SetText( const String& rText );
//STRIP001  BOOL                    SetStateText( ULONG nVal, const String &rVal, ULONG nNewRange = 0 );
    virtual BOOL            SetState( ULONG nVal, ULONG nNewRange = 0 );
    ULONG                   GetState() const { return nVal; }

    void                    Resume();
    void                    Suspend();
    BOOL                    IsSuspended() const { return bSuspended; }

    void                    Lock();
//STRIP001  void                    UnLock();
    void                    Reschedule();

    void                    Stop();

//STRIP001  void                    SetWaitMode( BOOL bWait );
//STRIP001  BOOL                    GetWaitMode() const;

    static SfxProgress*     GetActiveProgress( SfxObjectShell *pDocSh = 0 );
//STRIP001  static void             EnterLock();
//STRIP001  static void             LeaveLock();

#if _SOLAR__PRIVATE
    DECL_STATIC_LINK( SfxProgress, SetStateHdl, PlugInLoadStatus* );
    DECL_STATIC_LINK( SfxProgress, DefaultBindingProgress, SvProgressArg* );
    FASTBOOL                StatusBarManagerGone_Impl(SfxStatusBarManager*pStb);
//STRIP001  const String&           GetStateText_Impl() const;
#endif
};

#endif

