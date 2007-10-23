/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: interno.hxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: vg $ $Date: 2007-10-23 14:22:04 $
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
#ifndef _SFX_INTERNO_HXX
#define _SFX_INTERNO_HXX

#ifndef _IPOBJ_HXX //autogen
#include <bf_so3/ipobj.hxx>
#endif
#include "bf_sfx2/objsh.hxx"
#include "bf_sfx2/sfx.hrc"

namespace binfilter {

struct SfxInPlaceObject_Impl;
class SfxObjectShell;
class INote;


//=========================================================================

class SfxInPlaceObject : public SvInPlaceObject
{
    SfxObjectShell*     pObjShell;
    INote*              pNote;
    BOOL                bTriggerLinkTimer : 1;
    BOOL                bDisableViewScaling : 1;

#if _SOLAR__PRIVATE
private:

public:
#endif
                        SO2_DECL_STANDARD_CLASS(SfxInPlaceObject)
public:
    SfxObjectShell*     GetObjectShell() const { return pObjShell; }

protected:
    void                SetShell( SfxObjectShell *pObjSh );

    virtual void        FillClass( SvGlobalName * pClassName,
                                   ULONG * pClipFormat,
                                   String * pAppName,
                                   String * pLongUserName,
                                   String * pUserName,
                                   long nVersion = SOFFICE_FILEFORMAT_CURRENT
    ) const;

    virtual BOOL        InitNew( SvStorage * );         // Rekursiv
    virtual BOOL        Load( SvStorage * );            // Rekursiv
    virtual BOOL        Save();                         // Rekursiv
    virtual BOOL        SaveAs( SvStorage * pNewStg );  // Rekursiv
    virtual void        HandsOff();                     // Rekursiv
    virtual BOOL        SaveCompleted( SvStorage * );   // Rekursiv

    virtual ErrCode     Verb( long nVerbPos,
                            SvEmbeddedClient *pCaller,
                            Window *pWin,
                            const Rectangle *pWorkAreaPixel );
    virtual BOOL        Verb( long nVerbPos, const Rectangle *pWorkAreaPixel );
    virtual void        Embed( BOOL bEmbedded );
    virtual void        Open( BOOL bOpen );
    virtual void        InPlaceActivate( BOOL );
    virtual void        DocumentNameChanged( const String & rDocName );

    virtual             ~SfxInPlaceObject();

public:
                        SfxInPlaceObject();

    void                SetTriggerLinkTimer( BOOL bSet )
                        { bTriggerLinkTimer = bSet; }
    void                UpdateLinks();

    virtual void        SetVisArea( const Rectangle & rVisArea );

    void                SetModified( BOOL bSet );
    void                DisableViewScaling( BOOL bSet )
                        { bDisableViewScaling = bSet; }
    BOOL                IsViewScalingDisabled()
                        { return bDisableViewScaling; }
};

#ifndef SFX_DECL_INTERNALOBJECT_DEFINED
#define SFX_DECL_INTERNALOBJECT_DEFINED
SO2_DECL_REF(SfxInPlaceObject)
#endif
SO2_IMPL_REF(SfxInPlaceObject)

#if _SOLAR__PRIVATE
class SfxForceLinkTimer_Impl
{
    SfxInPlaceObject *pInObj;

public:
    SfxForceLinkTimer_Impl( SfxObjectShell *pObj );
    ~SfxForceLinkTimer_Impl()
    { if( pInObj ) pInObj->SetTriggerLinkTimer( TRUE ); }
};
#endif


}//end of namespace binfilter
#endif

