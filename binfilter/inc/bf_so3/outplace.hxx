/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: outplace.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: vg $ $Date: 2007-10-23 14:26:06 $
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

#ifndef _OUTPLACE_HXX
#define _OUTPLACE_HXX

#ifndef _COM_SUN_STAR_LANG_XCOMPONENT_HPP_
#include <com/sun/star/lang/XComponent.hpp>
#endif

#ifndef _COM_SUN_STAR_DATATRANSFER_XTRANSFERABLE_HPP_
#include <com/sun/star/datatransfer/XTransferable.hpp>
#endif

#include <bf_so3/ipobj.hxx>

#ifndef INCLUDED_SO3DLLAPI_H
#include "bf_so3/so3dllapi.h"
#endif

//=========================================================================
struct SvOutPlace_Impl;
namespace so3
{
    class SvObjectServer;
}

class SO3_DLLPUBLIC SvOutPlaceObject : public SvInPlaceObject
/*  [Beschreibung]

    Die Klasse SvOutPlaceObject ist ein Wrapper fuer alle Windows Ole-Objekte

    [Probleme]
*/
{
private:
    SvOutPlace_Impl *   pImpl;

    SO3_DLLPRIVATE void         DataChanged_Impl( BOOL bOnlyEmbedSource );
    SO3_DLLPRIVATE void         LoadSO_Cont();
    SO3_DLLPRIVATE BOOL         MakeWorkStorageWrap_Impl( SvStorage * pStor );

protected:
    SO3_DLLPRIVATE virtual void    FillClass( SvGlobalName * pClassName,
                               ULONG * pFormat,
                               String * pAppName,
                               String * pFullTypeName,
                               String * pShortTypeName,
                               long nFileFormat = SOFFICE_FILEFORMAT_CURRENT ) const;
                    // Protokoll
    SO3_DLLPRIVATE virtual void    Open( BOOL bOpen );
    SO3_DLLPRIVATE virtual void    Embed( BOOL bEmbedded );
    SO3_DLLPRIVATE virtual ErrCode Verb( long, SvEmbeddedClient * pCallerClient,
                        Window * pWin, const Rectangle * pWorkRectPixel );

                    // Datenaustausch
    SO3_DLLPRIVATE virtual void    Draw( OutputDevice *,
                          const JobSetup & rSetup,
                          USHORT nAspect = ASPECT_CONTENT );

                    // Laden speichern
    SO3_DLLPRIVATE virtual BOOL    InitNew( SvStorage * );
    SO3_DLLPRIVATE virtual BOOL    Load( SvStorage * );
    SO3_DLLPRIVATE virtual BOOL    Save();
    SO3_DLLPRIVATE virtual BOOL    SaveAs( SvStorage * );
    SO3_DLLPRIVATE virtual void    HandsOff();
    SO3_DLLPRIVATE virtual BOOL    SaveCompleted( SvStorage * );

    SO3_DLLPRIVATE              ~SvOutPlaceObject();
public:
                    SO2_DECL_BASIC_CLASS(SvOutPlaceObject)
//                  SO2_DECL_BASIC_CLASS_DLL(SvOutPlaceObject,SOAPP)
                    SvOutPlaceObject();
    static SvInPlaceObjectRef   InsertObject( Window *, SvStorage * pIStorage,
                                                BOOL & bOut, String & rTypeName, String & rFileName,
                                                BOOL & bInternal, SvGlobalName & rInternalClassName );
    static SvInPlaceObjectRef   InsertObject( Window *, SvStorage * pIStorage,
                                            BOOL & bOut, const SvGlobalName & rName, String & rFileName );
    static SvInPlaceObjectRef   CreateFromClipboard( SvStorage * );
    static SvInPlaceObjectRef   CreateFromData( const ::com::sun::star::uno::Reference<
                                                ::com::sun::star::datatransfer::XTransferable>&,
                                                SvStorage*);
    static SvGlobalName         GetCLSID( const String & rFileName );
    static SvInPlaceObjectRef   CreateFromFile( SvStorage * pStor, const String & rFileName );

    static const ::so3::SvObjectServer* GetInternalServer_Impl( const SvGlobalName& aGlobName );

    void            ClearCache();
    SotStorage *    GetWorkingStorage();
    virtual void    SetVisArea( const Rectangle & rVisArea );
    using SvEmbeddedObject::GetVisArea;
    Rectangle       GetVisArea( USHORT dwAspect ) const;
    void            ViewChanged( USHORT nAspects );
    virtual const SvVerbList & GetVerbList() const;

    virtual UINT32      GetViewAspect() const;
    ::com::sun::star::uno::Reference < ::com::sun::star::lang::XComponent > GetUnoComponent() const;
    SvGlobalName        GetObjectCLSID();
    void    DrawObject( OutputDevice *,
                          const JobSetup & rSetup,
                          const Size& rSize,
                          USHORT nAspect = ASPECT_CONTENT );

};

SO2_DECL_IMPL_REF(SvOutPlaceObject)

#endif // _OUTPLACE_HXX

