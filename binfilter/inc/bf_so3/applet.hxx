/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: applet.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 11:41:07 $
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

#ifndef _APPLET_HXX
#define _APPLET_HXX

#include <bf_so3/ipobj.hxx>
#include <bf_svtools/ownlist.hxx>

#ifndef INCLUDED_SO3DLLAPI_H
#include "bf_so3/so3dllapi.h"
#endif
//=========================================================================
class INetURLObject;
class SjApplet;
class RmAppletObject;

namespace binfilter {

struct SvAppletData_Impl;

class SO3_DLLPUBLIC SvAppletObject : public SvInPlaceObject
/*  [Beschreibung]

    Die Klasse AppletObject ist die Abbildung eines InPlace-Objektes
    auf einen Applet-Server. Dieses Objekt kann nur InPlace- und
    nicht UI-Aktiviert werden.

    [Probleme]
    Es handelt sich bei diesem Objekt immer um einen Link. Dieser Link
    kann allerdings InPlace aktiviert werden.
*/
{
friend class SvAppletEnvironment;

private:
    SvAppletData_Impl * pImpl;

    SO3_DLLPRIVATE void         DataChanged_Impl( BOOL bOnlyEmbedSource );

protected:
    SO3_DLLPRIVATE BOOL         StartApplet();
    SO3_DLLPRIVATE virtual void    FillClass( SvGlobalName * pClassName,
                               ULONG * pFormat,
                               String * pAppName,
                               String * pFullTypeName,
                               String * pShortTypeName,
                               long nFileFormat = SOFFICE_FILEFORMAT_CURRENT ) const;
                    // Protokoll
    SO3_DLLPRIVATE virtual void    Open( BOOL bOpen );
    SO3_DLLPRIVATE virtual void    InPlaceActivate( BOOL );
    SO3_DLLPRIVATE virtual ErrCode Verb( long, SvEmbeddedClient * pCallerClient,
                        Window * pWin, const Rectangle * pWorkRectPixel );

                    // Datenaustausch
    SO3_DLLPRIVATE virtual void    SetVisArea( const Rectangle & rVisArea );
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

    SO3_DLLPRIVATE              ~SvAppletObject();
public:
                    SO2_DECL_BASIC_CLASS_DLL(SvAppletObject,SOAPP)
                    SvAppletObject();

    virtual ULONG   GetMiscStatus() const;
    virtual BOOL    IsLink() const;

#ifdef MRJ_JAVA
    SdApplet_MRJ *  GetApplet() const;
#elif defined( REMOTE_VERSION )
    RmAppletObject *GetApplet() const;
#else
    SjApplet *      GetApplet() const;
#endif

                    // spezielle Internet Methoden
    void            SetCommandList( const SvCommandList & rList );
    const SvCommandList & GetCommandList() const;
    void            SetClass( const String & rClass );
    const String &  GetClass()const;
    void            SetName( const XubString & rClass );
    const XubString &GetName() const;
    void            SetDocBase( const INetURLObject & );
    void            SetCodeBase( const INetURLObject & );
    void            SetCodeBase( const XubString & );
    const XubString & GetCodeBase() const;
    void            SetMayScript( BOOL bMayScript );
    BOOL            IsMayScript() const;
};

SO2_DECL_IMPL_REF(SvAppletObject)

}

#endif // _Applet_HXX
