/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: progress.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 03:06:35 $
 *
 *  The Contents of this file are made available subject to
 *  the terms of GNU Lesser General Public License Version 2.1.
 *
 *
 *    GNU Lesser General Public License Version 2.1
 *    =============================================
 *    Copyright 2005 by Sun Microsystems, Inc.
 *    901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *    This library is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License version 2.1, as published by the Free Software Foundation.
 *
 *    This library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with this library; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *    MA  02111-1307  USA
 *
 ************************************************************************/
#ifndef _SFX_PROGRESS_HXX
#define _SFX_PROGRESS_HXX

#include <tools/solar.h>

#ifndef _LINK_HXX
#include <tools/link.hxx>
#endif
class String;
namespace binfilter {

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
    virtual BOOL            SetState( ULONG nVal, ULONG nNewRange = 0 );
    ULONG                   GetState() const { return nVal; }

    void                    Resume();
    void                    Suspend();
    BOOL                    IsSuspended() const { return bSuspended; }

    void                    Lock();
    void                    Reschedule();

    void                    Stop();


    static SfxProgress*     GetActiveProgress( SfxObjectShell *pDocSh = 0 );

#if _SOLAR__PRIVATE
    DECL_STATIC_LINK( SfxProgress, SetStateHdl, PlugInLoadStatus* );
    DECL_STATIC_LINK( SfxProgress, DefaultBindingProgress, SvProgressArg* );
    FASTBOOL                StatusBarManagerGone_Impl(SfxStatusBarManager*pStb);
#endif
};

}//end of namespace binfilter
#endif

