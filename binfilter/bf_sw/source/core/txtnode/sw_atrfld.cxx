/*************************************************************************
 *
 *  $RCSfile: sw_atrfld.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2004-05-05 16:41:09 $
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

#include "doc.hxx"          // Update fuer UserFields
#include "fldbas.hxx"          // fuer FieldType

#ifndef _FMTFLD_HXX //autogen
#include <fmtfld.hxx>
#endif
#ifndef _TXTFLD_HXX //autogen
#include <txtfld.hxx>
#endif
#include "reffld.hxx"
#include "ddefld.hxx"
#include "usrfld.hxx"
#include "expfld.hxx"
#include "swfont.hxx"       // fuer GetFldsColor
#include "ndtxt.hxx"        // SwTxtNode
#include "calc.hxx"         // Update fuer UserFields
#include "hints.hxx"
namespace binfilter {

/*N*/ TYPEINIT2( SwFmtFld, SfxPoolItem, SwClient )

/****************************************************************************
 *
 *  class SwFmtFld
 *
 ****************************************************************************/

    // Konstruktor fuers Default vom Attribut-Pool
/*N*/ SwFmtFld::SwFmtFld()
/*N*/   : SfxPoolItem( RES_TXTATR_FIELD ),
/*N*/   SwClient( 0 ),
/*N*/   pField( 0 ),
/*N*/   pTxtAttr( 0 )
/*N*/ {
/*N*/ }

/*N*/ SwFmtFld::SwFmtFld( const SwField &rFld )
/*N*/   : SfxPoolItem( RES_TXTATR_FIELD ),
/*N*/   SwClient( rFld.GetTyp() ),
/*N*/   pTxtAttr( 0 )
/*N*/ {
/*N*/   pField = rFld.Copy();
/*N*/ }

/*N*/ SwFmtFld::SwFmtFld( const SwFmtFld& rAttr )
/*N*/   : SfxPoolItem( RES_TXTATR_FIELD ),
/*N*/   SwClient( rAttr.GetFld()->GetTyp() ),
/*N*/   pTxtAttr( 0 )
/*N*/ {
/*N*/   pField = rAttr.GetFld()->Copy();
/*N*/ }

/*N*/ SwFmtFld::~SwFmtFld()
/*N*/ {
/*N*/   SwFieldType* pType = pField ? pField->GetTyp() : 0;
/*N*/
/*N*/   if (pType && pType->Which() == RES_DBFLD)
/*N*/       pType = 0;  // DB-Feldtypen zerstoeren sich selbst
/*N*/
/*N*/   delete pField;
/*N*/
/*N*/   // bei einige FeldTypen muessen wir den FeldTypen noch loeschen
/*N*/   if( pType && pType->IsLastDepend() )
/*N*/   {
/*N*/       BOOL bDel = FALSE;
/*N*/       switch( pType->Which() )
/*N*/       {
/*N*/       case RES_USERFLD:
/*N*/           bDel = ((SwUserFieldType*)pType)->IsDeleted();
/*N*/           break;
/*N*/
/*N*/       case RES_SETEXPFLD:
/*N*/           bDel = ((SwSetExpFieldType*)pType)->IsDeleted();
/*N*/           break;
/*N*/
/*N*/       case RES_DDEFLD:
/*N*/           bDel = ((SwDDEFieldType*)pType)->IsDeleted();
/*N*/           break;
/*N*/       }
/*N*/
/*N*/       if( bDel )
/*N*/       {
/*N*/           // vorm loeschen erstmal austragen
/*?*/           pType->Remove( this );
/*?*/           delete pType;
/*N*/       }
/*N*/   }
/*N*/ }

int SwFmtFld::operator==( const SfxPoolItem& rAttr ) const
{
        DBG_BF_ASSERT(0, "STRIP"); return 0; //STRIP001     ASSERT( SfxPoolItem::operator==( rAttr ), "keine gleichen Attribute" );
//STRIP001  return pField->GetTyp() == ((SwFmtFld&)rAttr).GetFld()->GetTyp() &&
//STRIP001         pField->GetFormat() == ((SwFmtFld&)rAttr).GetFld()->GetFormat();
}

/*N*/ SfxPoolItem* SwFmtFld::Clone( SfxItemPool* ) const
/*N*/ {
/*N*/   return new SwFmtFld( *this );
/*N*/ }

/*N*/ void SwFmtFld::Modify( SfxPoolItem* pOld, SfxPoolItem* pNew )
/*N*/ {
/*N*/   if( !pTxtAttr )
/*N*/       return;
/*N*/
/*N*/   SwTxtNode* pTxtNd = (SwTxtNode*)&pTxtAttr->GetTxtNode();
/*N*/   ASSERT( pTxtNd, "wo ist denn mein Node?" );
/*N*/   if( pNew )
/*N*/   {
/*N*/       switch( pNew->Which() )
/*N*/       {
/*?*/       case RES_TXTATR_FLDCHG:
/*?*/               // "Farbe hat sich geaendert !"
/*?*/               // this, this fuer "nur Painten"
/*?*/               pTxtNd->Modify( this, this );
/*?*/               return;
/*?*/       case RES_REFMARKFLD_UPDATE:
/*?*/               // GetReferenz-Felder aktualisieren
/*?*/               if( RES_GETREFFLD == GetFld()->GetTyp()->Which() )
/*?*/                   ((SwGetRefField*)GetFld())->UpdateField();
/*?*/               break;
/*N*/       case RES_DOCPOS_UPDATE:
/*N*/               // Je nach DocPos aktualisieren (SwTxtFrm::Modify())
/*N*/               pTxtNd->Modify( pNew, this );
/*N*/               return;
/*N*/
/*N*/       case RES_ATTRSET_CHG:
/*N*/       case RES_FMT_CHG:
/*?*/               pTxtNd->Modify( pOld, pNew );
/*?*/               return;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   switch (GetFld()->GetTyp()->Which())
/*N*/   {
/*?*/       case RES_HIDDENPARAFLD:
/*?*/           if( !pOld || RES_HIDDENPARA_PRINT != pOld->Which() )
/*?*/               break;
/*?*/       case RES_DBSETNUMBERFLD:
/*?*/       case RES_DBNUMSETFLD:
/*?*/       case RES_DBNEXTSETFLD:
/*?*/       case RES_DBNAMEFLD:
/*?*/           pTxtNd->Modify( 0, pNew);
/*?*/           return;
/*N*/   }
/*N*/
/*N*/   if( RES_USERFLD == GetFld()->GetTyp()->Which() )
/*N*/   {
/*?*/       SwUserFieldType* pType = (SwUserFieldType*)GetFld()->GetTyp();
/*?*/       if(!pType->IsValid())
/*?*/       {
/*?*/           DBG_BF_ASSERT(0, "STRIP"); //STRIP001 SwCalc aCalc( *pTxtNd->GetDoc() );
//STRIP001 /*?*/            pType->GetValue( aCalc );
/*?*/       }
/*N*/   }
/*N*/   pTxtAttr->Expand();
/*N*/ }

/*N*/ BOOL SwFmtFld::GetInfo( SfxPoolItem& rInfo ) const
/*N*/ {
/*N*/   const SwTxtNode* pTxtNd;
/*N*/   if( RES_AUTOFMT_DOCNODE != rInfo.Which() ||
/*N*/       !pTxtAttr || 0 == ( pTxtNd = pTxtAttr->GetpTxtNode() ) ||
/*N*/       &pTxtNd->GetNodes() != ((SwAutoFmtGetDocNode&)rInfo).pNodes )
/*N*/       return TRUE;
/*N*/
/*N*/   ((SwAutoFmtGetDocNode&)rInfo).pCntntNode = pTxtNd;
/*N*/   return FALSE;
/*N*/ }


/*N*/ BOOL SwFmtFld::IsFldInDoc() const
/*N*/ {
/*N*/   const SwTxtNode* pTxtNd;
/*N*/   return pTxtAttr && 0 != ( pTxtNd = pTxtAttr->GetpTxtNode() ) &&
/*N*/           pTxtNd->GetNodes().IsDocNodes();
/*N*/ }

//STRIP001 BOOL SwFmtFld::IsProtect() const
//STRIP001 {
//STRIP001  const SwTxtNode* pTxtNd;
//STRIP001  return pTxtAttr && 0 != ( pTxtNd = pTxtAttr->GetpTxtNode() ) &&
//STRIP001          pTxtNd->IsProtect();
//STRIP001 }

/*************************************************************************
|*
|*                SwTxtFld::SwTxtFld()
|*
|*    Beschreibung      Attribut fuer automatischen Text, Ctor
|*    Ersterstellung    BP 30.04.92
|*    Letzte Aenderung  JP 15.08.94
|*
*************************************************************************/

/*N*/ SwTxtFld::SwTxtFld( const SwFmtFld& rAttr, xub_StrLen nStart )
/*N*/   : SwTxtAttr( rAttr, nStart ),
/*N*/   aExpand( rAttr.GetFld()->Expand() ),
/*N*/   pMyTxtNd( 0 )
/*N*/ {
/*N*/   ((SwFmtFld&)rAttr).pTxtAttr = this;
/*N*/ }

/*N*/ SwTxtFld::~SwTxtFld( )
/*N*/ {
/*N*/ }

/*************************************************************************
|*
|*                SwTxtFld::Expand()
|*
|*    Beschreibung      exandiert das Feld und tauscht den Text im Node
|*    Ersterstellung    BP 30.04.92
|*    Letzte Aenderung  JP 15.08.94
|*
*************************************************************************/

/*N*/ void SwTxtFld::Expand()
/*N*/ {
/*N*/   // Wenn das expandierte Feld sich nicht veraendert hat, wird returnt
/*N*/   ASSERT( pMyTxtNd, "wo ist denn mein Node?" );
/*N*/
/*N*/   const SwField* pFld = GetFld().GetFld();
/*N*/   XubString aNewExpand( pFld->Expand() );
/*N*/
/*N*/   if( aNewExpand == aExpand )
/*N*/   {
/*N*/       // Bei Seitennummernfeldern
/*N*/       const USHORT nWhich = pFld->GetTyp()->Which();
/*N*/       if( RES_CHAPTERFLD != nWhich && RES_PAGENUMBERFLD != nWhich &&
/*N*/           RES_REFPAGEGETFLD != nWhich &&
/*N*/           ( RES_GETEXPFLD != nWhich ||
/*N*/               ((SwGetExpField*)pFld)->IsInBodyTxt() ) )
/*N*/       {
/*N*/           // BP: das muesste man noch optimieren!
/*N*/           //JP 12.06.97: stimmt, man sollte auf jedenfall eine Status-
/*N*/           //              aenderung an die Frames posten
/*N*/           if( pMyTxtNd->CalcVisibleFlag() )
/*?*/               pMyTxtNd->Modify( 0, 0 );
/*N*/           return;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   aExpand = aNewExpand;
/*N*/
/*N*/   // 0, this fuer Formatieren
/*N*/   pMyTxtNd->Modify( 0, (SfxPoolItem*)&GetFld() );
/*N*/ }

/*************************************************************************
 *                      SwTxtFld::CopyFld()
 *************************************************************************/

//STRIP001 void SwTxtFld::CopyFld( SwTxtFld *pDest ) const
//STRIP001 {
//STRIP001  ASSERT( pMyTxtNd, "wo ist denn mein Node?" );
//STRIP001  ASSERT( pDest->pMyTxtNd, "wo ist denn mein Node?" );
//STRIP001
//STRIP001  SwDoc *pDoc = pMyTxtNd->GetDoc();
//STRIP001  SwDoc *pDestDoc = pDest->pMyTxtNd->GetDoc();
//STRIP001
//STRIP001  SwFmtFld& rFmtFld = (SwFmtFld&)pDest->GetFld();
//STRIP001  const USHORT nFldWhich = rFmtFld.GetFld()->GetTyp()->Which();
//STRIP001
//STRIP001  if( pDoc != pDestDoc )
//STRIP001  {
//STRIP001      // Die Hints stehen in unterschiedlichen Dokumenten,
//STRIP001      // der Feldtyp muss im neuen Dokument angemeldet werden.
//STRIP001      // Z.B: Kopieren ins ClipBoard.
//STRIP001      SwFieldType* pFldType;
//STRIP001      if( nFldWhich != RES_DBFLD && nFldWhich != RES_USERFLD &&
//STRIP001          nFldWhich != RES_SETEXPFLD && nFldWhich != RES_DDEFLD &&
//STRIP001          RES_AUTHORITY != nFldWhich )
//STRIP001          pFldType = pDestDoc->GetSysFldType( (const RES_FIELDS)nFldWhich );
//STRIP001      else
//STRIP001          pFldType = pDestDoc->InsertFldType( *rFmtFld.GetFld()->GetTyp() );
//STRIP001
//STRIP001      // Sonderbehandlung fuer DDE-Felder
//STRIP001      if( RES_DDEFLD == nFldWhich )
//STRIP001      {
//STRIP001          if( rFmtFld.GetTxtFld() )
//STRIP001              ((SwDDEFieldType*)rFmtFld.GetFld()->GetTyp())->DecRefCnt();
//STRIP001          ((SwDDEFieldType*)pFldType)->IncRefCnt();
//STRIP001      }
//STRIP001
//STRIP001      ASSERT( pFldType, "unbekannter FieldType" );
//STRIP001      pFldType->Add( &rFmtFld );          // ummelden
//STRIP001      rFmtFld.GetFld()->ChgTyp( pFldType );
//STRIP001  }
//STRIP001
//STRIP001  // Expressionfelder Updaten
//STRIP001  if( nFldWhich == RES_SETEXPFLD || nFldWhich == RES_GETEXPFLD ||
//STRIP001      nFldWhich == RES_HIDDENTXTFLD )
//STRIP001  {
//STRIP001      SwTxtFld* pFld = (SwTxtFld*)this;
//STRIP001      pDestDoc->UpdateExpFlds( pFld );
//STRIP001  }
//STRIP001  // Tabellenfelder auf externe Darstellung
//STRIP001  else if( RES_TABLEFLD == nFldWhich &&
//STRIP001      ((SwTblField*)rFmtFld.GetFld())->IsIntrnlName() )
//STRIP001  {
//STRIP001      // erzeuge aus der internen (fuer CORE) die externe (fuer UI) Formel
//STRIP001      const SwTableNode* pTblNd = pMyTxtNd->FindTableNode();
//STRIP001      if( pTblNd )        // steht in einer Tabelle
//STRIP001          ((SwTblField*)rFmtFld.GetFld())->PtrToBoxNm( &pTblNd->GetTable() );
//STRIP001  }
//STRIP001 }


}
