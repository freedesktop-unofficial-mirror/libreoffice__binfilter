/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: ddefld.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: vg $ $Date: 2007-10-23 14:31:03 $
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
#ifndef _DDEFLD_HXX
#define _DDEFLD_HXX

#ifndef _LNKBASE_HXX //autogen
#include <bf_so3/lnkbase.hxx>
#endif
#include "fldbas.hxx"
namespace binfilter {

class SwDoc;

/*--------------------------------------------------------------------
    Beschreibung: FieldType fuer DDE
 --------------------------------------------------------------------*/

class SwDDEFieldType : public SwFieldType
{
    String aName;
    String aExpansion;

    ::so3::SvBaseLinkRef refLink;
    SwDoc* pDoc;

    USHORT nRefCnt;
    BOOL bCRLFFlag : 1;
    BOOL bDeleted : 1;

    void _RefCntChgd();
public:
    SwDDEFieldType( const String& rName, const String& rCmd,
                    USHORT = ::so3::LINKUPDATE_ONCALL );
    ~SwDDEFieldType();

    const String& GetExpansion() const          { return aExpansion; }
    void SetExpansion( const String& rStr )     { aExpansion = rStr,
                                                  bCRLFFlag = FALSE; }

    virtual SwFieldType* Copy() const;
    virtual const String& GetName() const;

    virtual BOOL        QueryValue( ::com::sun::star::uno::Any& rVal, BYTE nMId ) const;
    virtual BOOL        PutValue( const ::com::sun::star::uno::Any& rVal, BYTE nMId );

    String GetCmd() const;
    void SetCmd( const String& rStr );

    USHORT GetType() const          { return refLink->GetUpdateMode();  }
    void SetType( USHORT nType )    { refLink->SetUpdateMode( nType );  }

    BOOL IsDeleted() const          { return bDeleted; }
    void SetDeleted( BOOL b )       { bDeleted = b; }

    BOOL IsConnected() const        { return 0 != refLink->GetObj(); }
    void UpdateNow()                { refLink->Update(); }
    void Disconnect()               { refLink->Disconnect(); }

    const ::so3::SvBaseLink& GetBaseLink() const    { return *refLink; }
          ::so3::SvBaseLink& GetBaseLink()          { return *refLink; }

    const SwDoc* GetDoc() const     { return pDoc; }
          SwDoc* GetDoc()           { return pDoc; }
    void SetDoc( SwDoc* pDoc );

    void IncRefCnt() {  if( !nRefCnt++ && pDoc ) _RefCntChgd(); }
    void DecRefCnt() {  if( !--nRefCnt && pDoc ) _RefCntChgd(); }

    void SetCRLFDelFlag( BOOL bFlag = TRUE )    { bCRLFFlag = bFlag; }
    BOOL IsCRLFDelFlag() const                  { return bCRLFFlag; }
};

/*--------------------------------------------------------------------
    Beschreibung: DDE-Feld
 --------------------------------------------------------------------*/

class SwDDEField : public SwField
{
public:
    SwDDEField(SwDDEFieldType*);
    ~SwDDEField();

    virtual String   Expand() const;
    virtual SwField* Copy() const;

    // ueber Typen Parameter ermitteln
    // Name kann nicht geaendert werden
    virtual const String& GetPar1() const;

    // Commando
    virtual String  GetPar2() const;
    virtual void    SetPar2(const String& rStr);
};


} //namespace binfilter
#endif // _DDEFLD_HXX
