/*************************************************************************
 *
 *  $RCSfile: sw_ddefld.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: os $ $Date: 2004-04-22 15:41:17 $
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


#pragma hdrstop

#ifndef _SVXLINKMGR_HXX
#include <bf_svx/linkmgr.hxx>
#endif

#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _EDITSH_HXX
#include <editsh.hxx>
#endif
#ifndef _ERRHDL_HXX
#include <errhdl.hxx>
#endif
#ifndef _NDTXT_HXX
#include <ndtxt.hxx>
#endif
#ifndef _HINTS_HXX
#include <hints.hxx>
#endif
#ifndef _FMTFLD_HXX //autogen
#include <fmtfld.hxx>
#endif
#ifndef _TXTFLD_HXX //autogen
#include <txtfld.hxx>
#endif
#ifndef _DDEFLD_HXX
#include <ddefld.hxx>
#endif
#ifndef _SWTABLE_HXX
#include <swtable.hxx>
#endif
#ifndef _SWBASLNK_HXX
#include <swbaslnk.hxx>
#endif
#ifndef _SWDDETBL_HXX
#include <swddetbl.hxx>
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
//STRIP001  virtual void Closed();
//STRIP001  virtual void DataChanged( const String& rMimeType,
//STRIP001                              const ::com::sun::star::uno::Any & rValue );

//STRIP001  virtual const SwNode* GetAnchor() const;
//STRIP001  virtual BOOL IsInRange( ULONG nSttNd, ULONG nEndNd, xub_StrLen nStt = 0,
//STRIP001                          xub_StrLen nEnd = STRING_NOTFOUND ) const;
/*N*/ };


//STRIP001 void SwIntrnlRefLink::DataChanged( const String& rMimeType,
//STRIP001                              const ::com::sun::star::uno::Any & rValue )
//STRIP001 {
//STRIP001  switch( SotExchange::GetFormatIdFromMimeType( rMimeType ) )
//STRIP001  {
//STRIP001  case FORMAT_STRING:
//STRIP001      if( !IsNoDataFlag() )
//STRIP001      {
//STRIP001          ::com::sun::star::uno::Sequence< sal_Int8 > aSeq;
//STRIP001          rValue >>= aSeq;
//STRIP001          String sStr( (sal_Char*)aSeq.getConstArray(), aSeq.getLength(),
//STRIP001                             DDE_TXT_ENCODING  );
//STRIP001
//STRIP001          // CR-LF am Ende entfernen, ist ueberfluessig!
//STRIP001          xub_StrLen n = sStr.Len();
//STRIP001          while( n && 0 == sStr.GetChar( n-1 ) )
//STRIP001              --n;
//STRIP001          if( n && 0x0a == sStr.GetChar( n-1 ) )
//STRIP001              --n;
//STRIP001          if( n && 0x0d == sStr.GetChar( n-1 ) )
//STRIP001              --n;
//STRIP001
//STRIP001          BOOL bDel = n != sStr.Len();
//STRIP001          if( bDel )
//STRIP001              sStr.Erase( n );
//STRIP001
//STRIP001          rFldType.SetExpansion( sStr );
//STRIP001          // erst Expansion setzen! (sonst wird das Flag geloescht!)
//STRIP001          rFldType.SetCRLFDelFlag( bDel );
//STRIP001      }
//STRIP001      break;
//STRIP001
//STRIP001  // weitere Formate ...
//STRIP001  default:
//STRIP001      return;
//STRIP001  }
//STRIP001
//STRIP001  ASSERT( rFldType.GetDoc(), "Kein pDoc" );
//STRIP001
//STRIP001  // keine Abhaengigen mehr?
//STRIP001  if( rFldType.GetDepends() && !rFldType.IsModifyLocked() && !ChkNoDataFlag() )
//STRIP001  {
//STRIP001      ViewShell* pSh;
//STRIP001      SwEditShell* pESh = rFldType.GetDoc()->GetEditShell( &pSh );
//STRIP001
//STRIP001      // dann suchen wir uns mal alle Felder. Wird kein gueltiges
//STRIP001      // gefunden, dann Disconnecten wir uns!
//STRIP001      SwMsgPoolItem aUpdateDDE( RES_UPDATEDDETBL );
//STRIP001      int bCallModify = FALSE;
//STRIP001      rFldType.LockModify();
//STRIP001
//STRIP001      SwClientIter aIter( rFldType );
//STRIP001      SwClient * pLast = aIter.GoStart();
//STRIP001      if( pLast )     // konnte zum Anfang gesprungen werden ??
//STRIP001          do {
//STRIP001              // eine DDE-Tabelle oder ein DDE-FeldAttribut im Text
//STRIP001              if( !pLast->IsA( TYPE( SwFmtFld ) ) ||
//STRIP001                  ((SwFmtFld*)pLast)->GetTxtFld() )
//STRIP001              {
//STRIP001                  if( !bCallModify )
//STRIP001                  {
//STRIP001                      if( pESh )
//STRIP001                          pESh->StartAllAction();
//STRIP001                      else if( pSh )
//STRIP001                          pSh->StartAction();
//STRIP001                  }
//STRIP001                  pLast->Modify( 0, &aUpdateDDE );
//STRIP001                  bCallModify = TRUE;
//STRIP001              }
//STRIP001          } while( 0 != ( pLast = aIter++ ));
//STRIP001
//STRIP001      rFldType.UnlockModify();
//STRIP001
//STRIP001      if( bCallModify )
//STRIP001      {
//STRIP001          if( pESh )
//STRIP001              pESh->EndAllAction();
//STRIP001          else if( pSh )
//STRIP001              pSh->EndAction();
//STRIP001
//STRIP001          if( pSh )
//STRIP001              pSh->GetDoc()->SetModified();
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 void SwIntrnlRefLink::Closed()
//STRIP001 {
//STRIP001  if( rFldType.GetDoc() && !rFldType.GetDoc()->IsInDtor() )
//STRIP001  {
//STRIP001      // Advise verabschiedet sich, alle Felder in Text umwandeln ?
//STRIP001      ViewShell* pSh;
//STRIP001      SwEditShell* pESh = rFldType.GetDoc()->GetEditShell( &pSh );
//STRIP001      if( pESh )
//STRIP001      {
//STRIP001          pESh->StartAllAction();
//STRIP001          pESh->FieldToText( &rFldType );
//STRIP001          pESh->EndAllAction();
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          pSh->StartAction();
//STRIP001          // am Doc aufrufen ??
//STRIP001          pSh->EndAction();
//STRIP001      }
//STRIP001  }
//STRIP001  SvBaseLink::Closed();
//STRIP001 }

//STRIP001 const SwNode* SwIntrnlRefLink::GetAnchor() const
//STRIP001 {
//STRIP001  // hier sollte irgend ein Anchor aus dem normalen Nodes-Array reichen
//STRIP001  const SwNode* pNd = 0;
//STRIP001  SwClientIter aIter( rFldType );
//STRIP001  SwClient * pLast = aIter.GoStart();
//STRIP001  if( pLast )     // konnte zum Anfang gesprungen werden ??
//STRIP001      do {
//STRIP001          // eine DDE-Tabelle oder ein DDE-FeldAttribut im Text
//STRIP001          if( !pLast->IsA( TYPE( SwFmtFld ) ))
//STRIP001          {
//STRIP001              SwDepend* pDep = (SwDepend*)pLast;
//STRIP001              SwDDETable* pDDETbl = (SwDDETable*)pDep->GetToTell();
//STRIP001              pNd = pDDETbl->GetTabSortBoxes()[0]->GetSttNd();
//STRIP001          }
//STRIP001          else if( ((SwFmtFld*)pLast)->GetTxtFld() )
//STRIP001              pNd = ((SwFmtFld*)pLast)->GetTxtFld()->GetpTxtNode();
//STRIP001
//STRIP001          if( pNd && &rFldType.GetDoc()->GetNodes() == &pNd->GetNodes() )
//STRIP001              break;
//STRIP001          pNd = 0;
//STRIP001      } while( 0 != ( pLast = aIter++ ));
//STRIP001
//STRIP001  return pNd;
//STRIP001 }

//STRIP001 BOOL SwIntrnlRefLink::IsInRange( ULONG nSttNd, ULONG nEndNd,
//STRIP001                              xub_StrLen nStt, xub_StrLen nEnd ) const
//STRIP001 {
//STRIP001  // hier sollte irgend ein Anchor aus dem normalen Nodes-Array reichen
//STRIP001  SwNodes* pNds = &rFldType.GetDoc()->GetNodes();
//STRIP001  SwClientIter aIter( rFldType );
//STRIP001  SwClient * pLast = aIter.GoStart();
//STRIP001  if( pLast )     // konnte zum Anfang gesprungen werden ??
//STRIP001      do {
//STRIP001          // eine DDE-Tabelle oder ein DDE-FeldAttribut im Text
//STRIP001          if( !pLast->IsA( TYPE( SwFmtFld ) ))
//STRIP001          {
//STRIP001              SwDepend* pDep = (SwDepend*)pLast;
//STRIP001              SwDDETable* pDDETbl = (SwDDETable*)pDep->GetToTell();
//STRIP001              const SwTableNode* pTblNd = pDDETbl->GetTabSortBoxes()[0]->
//STRIP001                              GetSttNd()->FindTableNode();
//STRIP001              if( pTblNd->GetNodes().IsDocNodes() &&
//STRIP001                  nSttNd < pTblNd->EndOfSectionIndex() &&
//STRIP001                  nEndNd > pTblNd->GetIndex() )
//STRIP001                  return TRUE;
//STRIP001          }
//STRIP001          else if( ((SwFmtFld*)pLast)->GetTxtFld() )
//STRIP001          {
//STRIP001              const SwTxtFld* pTFld = ((SwFmtFld*)pLast)->GetTxtFld();
//STRIP001              const SwTxtNode* pNd = pTFld->GetpTxtNode();
//STRIP001              if( pNd && pNds == &pNd->GetNodes() )
//STRIP001              {
//STRIP001                  ULONG nNdPos = pNd->GetIndex();
//STRIP001                  if( nSttNd <= nNdPos && nNdPos <= nEndNd &&
//STRIP001                      ( nNdPos != nSttNd || *pTFld->GetStart() >= nStt ) &&
//STRIP001                      ( nNdPos != nEndNd || *pTFld->GetStart() < nEnd ))
//STRIP001                      return TRUE;
//STRIP001              }
//STRIP001          }
//STRIP001      } while( 0 != ( pLast = aIter++ ));
//STRIP001
//STRIP001  return FALSE;
//STRIP001 }

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
