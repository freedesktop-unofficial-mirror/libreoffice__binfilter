/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: protocol.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: vg $ $Date: 2007-10-23 14:26:49 $
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

#ifndef _PROTOCOL_HXX
#define _PROTOCOL_HXX

#ifndef _ERRCODE_HXX //autogen
#include <tools/errcode.hxx>
#endif
#ifndef _SOLAR_H
#include <tools/solar.h>
#endif
#ifndef _TOOLS_STRING_HXX
#include <tools/string.hxx>
#endif

#ifndef INCLUDED_SO3DLLAPI_H
#include "bf_so3/so3dllapi.h"
#endif

/*************************************************************************
*************************************************************************/
class  SvEmbeddedObject;
class  SvInPlaceObject;
class  SvEmbeddedClient;
class  SvInPlaceClient;
class  SoDll;
class  ImplSvEditObjectProtocol;
class  String;

class SO3_DLLPUBLIC SvEditObjectProtocol
{
friend class SoDll;
private:
    ImplSvEditObjectProtocol * pImp;
    SO3_DLLPRIVATE static void         Imp_DeleteDefault();
    SO3_DLLPRIVATE BOOL                Release();
public:
    SvEditObjectProtocol();
    SvEditObjectProtocol( SvEmbeddedObject *, SvEmbeddedClient * );
    SvEditObjectProtocol( const SvEditObjectProtocol & );
    SO3_DLLPRIVATE SvEditObjectProtocol & operator = ( const SvEditObjectProtocol & );
    ~SvEditObjectProtocol();

    // Objekte
    SvEmbeddedObject * GetObj() const;
    SvInPlaceObject *  GetIPObj() const;
    SvEmbeddedClient * GetClient() const;
    SvInPlaceClient *  GetIPClient() const;

    // Zustandsabfragen
    BOOL IsConnect() const;
    BOOL IsOpen() const;
    BOOL IsEmbed() const;
    BOOL IsPlugIn() const;
    BOOL IsInPlaceActive() const;
    BOOL IsUIActive() const;
    BOOL IsTopWinActive() const;
    BOOL IsDocWinActive() const;
    BOOL IsInClosed() const;

    // Protokolle
    ErrCode EmbedProtocol();
    ErrCode PlugInProtocol();
    ErrCode IPProtocol();
    ErrCode UIProtocol();

    // Welche Protokolle werden unterstuetzt
    BOOL CanEmbedProtocol() const;
    BOOL CanPlugInProtocol() const;
    BOOL CanInPlaceProtocol() const;
    BOOL CanUIProtocol() const;

    // Protokoll zurueckfahren
    BOOL Reset();
    BOOL Reset2Connect();
    BOOL Reset2Open();
    BOOL Reset2Embed();
    BOOL Reset2PlugIn();
    BOOL Reset2InPlaceActive();
    BOOL Reset2UIActive();

    // Einzelschritte der Protokolle
    void Connected( BOOL bOpen );
    void Opened( BOOL bOpen );
    void Embedded( BOOL bEmbed );
    void PlugIn( BOOL bPlugIn );
    void InPlaceActivate( BOOL bActivate );
    void UIActivate( BOOL bActivate );
    void TopWinActivate( BOOL bActivate );
    void DocWinActivate( BOOL bActivate );
    void SetInClosed( BOOL bInClosed );
    void DocNameChanged( const String & rName );
};

#endif // _PROTOCOL_HXX
