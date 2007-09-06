/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_ddefld.cxx,v $
 *
 *  $Revision: 1.7 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 12:12:37 $
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


#ifdef _MSC_VER
#pragma hdrstop
#endif

#ifndef _SVXLINKMGR_HXX
#include <bf_svx/linkmgr.hxx>
#endif

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _ERRHDL_HXX
#include <errhdl.hxx>
#endif
#ifndef _DDEFLD_HXX
#include <ddefld.hxx>
#endif
#ifndef _SWBASLNK_HXX
#include <swbaslnk.hxx>
#endif
#ifndef _UNOFLDMID_H
#include <unofldmid.h>
#endif
namespace binfilter {

extern String& GetString( const ::com::sun::star::uno::Any& rAny, String& rStr ); //STRIP008

using namespace rtl;

#ifdef PM2
#define DDE_TXT_ENCODING    RTL_TEXTENCODING_IBM_850
#else
#define DDE_TXT_ENCODING    RTL_TEXTENCODING_MS_1252
#endif

/*--------------------------------------------------------------------
    Beschreibung: Globale Variablen
 --------------------------------------------------------------------*/

/*N*/ class SwIntrnlRefLink : public SwBaseLink
/*N*/ {
/*N*/   SwDDEFieldType& rFldType;
/*N*/ public:
/*N*/   SwIntrnlRefLink( SwDDEFieldType& rType, USHORT nUpdateType, USHORT nFmt )
/*N*/       : SwBaseLink( nUpdateType, nFmt ),
/*N*/       rFldType( rType )
/*N*/   {}
/*N*/

/*N*/ };






/*N*/ SwDDEFieldType::SwDDEFieldType(const String& rName,
/*N*/                               const String& rCmd, USHORT nUpdateType )
/*N*/   : SwFieldType( RES_DDEFLD ),
/*N*/   aName( rName ), pDoc( 0 ), nRefCnt( 0 )
/*N*/ {
/*N*/   bCRLFFlag = bDeleted = FALSE;
/*N*/   refLink = new SwIntrnlRefLink( *this, nUpdateType, FORMAT_STRING );
/*N*/   SetCmd( rCmd );
/*N*/ }

/*N*/ SwDDEFieldType::~SwDDEFieldType()
/*N*/ {
/*N*/   if( pDoc && !pDoc->IsInDtor() )
/*?*/       pDoc->GetLinkManager().Remove( refLink );
/*N*/   refLink->Disconnect();
/*N*/ }


/*N*/ SwFieldType* SwDDEFieldType::Copy() const
/*N*/ {
/*N*/   SwDDEFieldType* pType = new SwDDEFieldType( aName, GetCmd(), GetType() );
/*N*/   pType->aExpansion = aExpansion;
/*N*/   pType->bCRLFFlag = bCRLFFlag;
/*N*/   pType->bDeleted = bDeleted;
/*N*/   pType->SetDoc( pDoc );
/*N*/   return pType;
/*N*/ }

/*N*/ const String& SwDDEFieldType::GetName() const
/*N*/ {
/*N*/   return aName;
/*N*/ }

/*N*/ void SwDDEFieldType::SetCmd( const String& rStr )
/*N*/ {
/*N*/   String sCmd( rStr );
/*N*/   xub_StrLen nPos;
/*N*/   while( STRING_NOTFOUND != (nPos = sCmd.SearchAscii( "  " )) )
/*?*/       sCmd.Erase( nPos, 1 );
/*N*/   refLink->SetLinkSourceName( sCmd );
/*N*/ }

/*N*/ String SwDDEFieldType::GetCmd() const
/*N*/ {
/*N*/   return refLink->GetLinkSourceName();
/*N*/ }

/*N*/ void SwDDEFieldType::SetDoc( SwDoc* pNewDoc )
/*N*/ {
/*N*/   if( pNewDoc == pDoc )
/*N*/       return;
/*N*/
/*N*/   if( pDoc && refLink.Is() )
/*N*/   {
/*?*/       ASSERT( !nRefCnt, "wie kommen die Referenzen rueber?" );
/*?*/       pDoc->GetLinkManager().Remove( refLink );
/*N*/   }
/*N*/
/*N*/   pDoc = pNewDoc;
/*N*/   if( pDoc && nRefCnt )
/*N*/   {
/*?*/       refLink->SetVisible( pDoc->IsVisibleLinks() );
/*?*/       pDoc->GetLinkManager().InsertDDELink( refLink );
/*N*/   }
/*N*/ }


/*N*/ void SwDDEFieldType::_RefCntChgd()
/*N*/ {
/*N*/   if( nRefCnt )
/*N*/   {
/*N*/       refLink->SetVisible( pDoc->IsVisibleLinks() );
/*N*/       pDoc->GetLinkManager().InsertDDELink( refLink );
/*N*/       if( pDoc->GetRootFrm() )
/*?*/           UpdateNow();
/*N*/   }
/*N*/   else
/*N*/   {
/*?*/       Disconnect();
/*?*/       pDoc->GetLinkManager().Remove( refLink );
/*N*/   }
/*N*/ }
/* -----------------------------28.08.00 16:23--------------------------------

 ---------------------------------------------------------------------------*/
BOOL SwDDEFieldType::QueryValue( ::com::sun::star::uno::Any& rVal, BYTE nMId ) const
{
    BYTE nPart = 0;
    nMId &= ~CONVERT_TWIPS;
    switch( nMId )
    {
    case FIELD_PROP_PAR2:      nPart = 3; break;
    case FIELD_PROP_PAR4:      nPart = 2; break;
    case FIELD_PROP_SUBTYPE:   nPart = 1; break;
    case FIELD_PROP_BOOL1:
        {
            sal_Bool bSet = GetType() == ::so3::LINKUPDATE_ALWAYS ? TRUE : FALSE;
            rVal.setValue(&bSet, ::getBooleanCppuType());
        }
        break;
    default:
        DBG_ERROR("illegal property");
    }
    if( nPart )
        rVal <<= OUString(GetCmd().GetToken(nPart-1, ::so3::cTokenSeperator));
    return TRUE;
}
/* -----------------------------28.08.00 16:23--------------------------------

 ---------------------------------------------------------------------------*/
BOOL SwDDEFieldType::PutValue( const ::com::sun::star::uno::Any& rVal, BYTE nMId )
{
    BYTE nPart = 0;
    nMId &= ~CONVERT_TWIPS;
    switch( nMId )
    {
    case FIELD_PROP_PAR2:      nPart = 3; break;
    case FIELD_PROP_PAR4:      nPart = 2; break;
    case FIELD_PROP_SUBTYPE:   nPart = 1; break;
    case FIELD_PROP_BOOL1:
        SetType( *(sal_Bool*)rVal.getValue() ? ::so3::LINKUPDATE_ALWAYS
                                             : ::so3::LINKUPDATE_ONCALL );
        break;
    default:
        DBG_ERROR("illegal property");
    }
    if( nPart )
    {
        String sTmp, sCmd( GetCmd() );
        while(3 > sCmd.GetTokenCount(so3::cTokenSeperator))
            sCmd += ::so3::cTokenSeperator;
        sCmd.SetToken( nPart-1, ::so3::cTokenSeperator, ::binfilter::GetString( rVal, sTmp ) );
        SetCmd( sCmd );
    }
    return TRUE;
}
/* ---------------------------------------------------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ SwDDEField::SwDDEField( SwDDEFieldType* pType )
/*N*/   : SwField(pType)
/*N*/ {
/*N*/ }

/*N*/ SwDDEField::~SwDDEField()
/*N*/ {
/*N*/   if( GetTyp()->IsLastDepend() )                      // der Letzte mach das
/*N*/       ((SwDDEFieldType*)GetTyp())->Disconnect();      // Licht aus
/*N*/ }

/*N*/ String SwDDEField::Expand() const
/*N*/ {
/*N*/   xub_StrLen nPos;
/*N*/   String aStr( ((SwDDEFieldType*)GetTyp())->GetExpansion() );
/*N*/
/*N*/   aStr.EraseAllChars( '\r' );
/*N*/   while( (nPos = aStr.Search( '\t' )) != STRING_NOTFOUND )
/*?*/       aStr.SetChar( nPos, ' ' );
/*N*/   while( (nPos = aStr.Search( '\n' )) != STRING_NOTFOUND )
/*?*/       aStr.SetChar( nPos, '|' );
/*N*/   if( aStr.Len() && ( aStr.GetChar( aStr.Len()-1 ) == '|') )
/*?*/       aStr.Erase( aStr.Len()-1, 1 );
/*N*/   return aStr;
/*N*/ }

/*N*/ SwField* SwDDEField::Copy() const
/*N*/ {
/*N*/   return new SwDDEField((SwDDEFieldType*)GetTyp());
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung: Parameter des Typen erfragen
                  Name
 --------------------------------------------------------------------*/
const String& SwDDEField::GetPar1() const
{
    return ((SwDDEFieldType*)GetTyp())->GetName();
}

/*--------------------------------------------------------------------
    Beschreibung: Parameter des Typen erfragen
                  Commando
 --------------------------------------------------------------------*/
String SwDDEField::GetPar2() const
{
    return ((SwDDEFieldType*)GetTyp())->GetCmd();
}

void SwDDEField::SetPar2(const String& rStr)
{
    ((SwDDEFieldType*)GetTyp())->SetCmd(rStr);
}

}
