/*************************************************************************
 *
 *  $RCSfile: sw_docfld.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: pjunck $ $Date: 2004-10-27 13:33:37 $
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

// auto strip #ifndef _HINTIDS_HXX
// auto strip #include <hintids.hxx>
// auto strip #endif

#include <string.h>
#include <float.h>

// auto strip #ifndef _DATETIME_HXX //autogen
// auto strip #include <tools/datetime.hxx>
// auto strip #endif
#ifndef _SVSTDARR_HXX
#define _SVSTDARR_ULONGS
// auto strip #include <svtools/svarray.hxx>
#endif
// auto strip #ifndef _APP_HXX //autogen
// auto strip #include <vcl/svapp.hxx>
// auto strip #endif
#ifndef _APP_HXX //autogen
#include <vcl/svapp.hxx>
#endif
#ifndef _SO2REF_HXX //autogen
#include <so3/so2ref.hxx>
#endif
// auto strip #ifndef _UNOTOOLS_CHARCLASS_HXX
// auto strip #include <unotools/charclass.hxx>
// auto strip #endif
// auto strip #ifndef _UNOTOOLS_TRANSLITERATIONWRAPPER_HXX
// auto strip #include <unotools/transliterationwrapper.hxx>
// auto strip #endif

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif
// auto strip #ifndef _ERRHDL_HXX
// auto strip #include <errhdl.hxx>
// auto strip #endif

// auto strip #ifndef _DOC_HXX
// auto strip #include <doc.hxx>
// auto strip #endif
#ifndef _CNTFRM_HXX
#include <cntfrm.hxx>
#endif
// auto strip #ifndef _PAM_HXX
// auto strip #include <pam.hxx>
// auto strip #endif
#ifndef _NDTXT_HXX
#include <ndtxt.hxx>
#endif
#ifndef _HINTS_HXX
#include <hints.hxx>
#endif
#ifndef _SWTABLE_HXX
#include <swtable.hxx>
#endif
// auto strip #ifndef _CALC_HXX
// auto strip #include <calc.hxx>
// auto strip #endif
// auto strip #ifndef _ERRHDL_HXX
// auto strip #include <errhdl.hxx>
// auto strip #endif
#ifndef _TXTFLD_HXX //autogen
#include <txtfld.hxx>
#endif
#ifndef _FMTFLD_HXX //autogen
#include <fmtfld.hxx>
#endif
// auto strip #ifndef _TOX_HXX
// auto strip #include <tox.hxx>
// auto strip #endif
#ifndef _TXTTXMRK_HXX //autogen
#include <txttxmrk.hxx>
#endif
#ifndef _DOCFLD_HXX
#include <docfld.hxx>   // fuer Expression-Felder
#endif
#ifndef _DOCUFLD_HXX
#include <docufld.hxx>
#endif
#ifndef _DDEFLD_HXX
#include <ddefld.hxx>
#endif
#ifndef _USRFLD_HXX
#include <usrfld.hxx>
#endif
#ifndef _EXPFLD_HXX
#include <expfld.hxx>
#endif
#ifndef _DBFLD_HXX
#include <dbfld.hxx>
#endif
#ifndef _FLDDAT_HXX
#include <flddat.hxx>
#endif
#ifndef _CHPFLD_HXX
#include <chpfld.hxx>
#endif
#ifndef _REFFLD_HXX
#include <reffld.hxx>
#endif
#ifndef _FLDDROPDOWN_HXX
#include <flddropdown.hxx>
#endif
#ifndef _DBMGR_HXX
#include <dbmgr.hxx>
#endif
#ifndef _SECTION_HXX
#include <section.hxx>
#endif
#ifndef _CELLATR_HXX
#include <cellatr.hxx>
#endif
#ifndef _DOCARY_HXX
#include <docary.hxx>
#endif
#ifndef _AUTHFLD_HXX
#include <authfld.hxx>
#endif
// auto strip #ifndef _FMTCNTNT_HXX
// auto strip #include <fmtcntnt.hxx>
// auto strip #endif
#ifndef _TXTINET_HXX
#include <txtinet.hxx>
#endif

#ifndef _POOLFMT_HRC
#include <poolfmt.hrc>      // fuer InitFldTypes
#endif
namespace binfilter {


#ifndef SO2_DECL_SVLINKNAME_DEFINED
#define SO2_DECL_SVLINKNAME_DEFINED
SO2_DECL_REF(SvLinkName)
#endif

extern BOOL IsFrameBehind( const SwTxtNode& rMyNd, USHORT nMySttPos,
                        const SwTxtNode& rBehindNd, USHORT nSttPos );

/*N*/ SV_IMPL_OP_PTRARR_SORT( _SetGetExpFlds, _SetGetExpFldPtr )


/*--------------------------------------------------------------------
    Beschreibung: Feldtypen einfuegen
 --------------------------------------------------------------------*/
/*
 *  Implementierung der Feldfunktionen am Doc
 *  Return immer einen gueltigen Pointer auf den Typ. Wenn er also neu
 *  zugefuegt oder schon vorhanden ist.
 */

/*N*/ SwFieldType* SwDoc::InsertFldType(const SwFieldType &rFldTyp)
/*N*/ {
/*N*/   USHORT nSize = pFldTypes->Count(),
/*N*/           nFldWhich = rFldTyp.Which();
/*N*/
/*N*/   USHORT i = INIT_FLDTYPES;
/*N*/
/*N*/   switch( nFldWhich )
/*N*/   {
/*N*/   case RES_SETEXPFLD:
/*N*/           //JP 29.01.96: SequenceFelder beginnen aber bei INIT_FLDTYPES - 3!!
/*N*/           //             Sonst gibt es doppelte Nummernkreise!!
/*N*/           //MIB 14.03.95: Ab sofort verlaesst sich auch der SW3-Reader
/*N*/           //beim Aufbau der String-Pools und beim Einlesen von SetExp-Feldern
/*N*/           //hierauf
/*N*/           if( GSE_SEQ & ((SwSetExpFieldType&)rFldTyp).GetType() )
/*N*/               i -= INIT_SEQ_FLDTYPES;
/*N*/       // kein break;
/*N*/   case RES_DBFLD:
/*N*/   case RES_USERFLD:
/*N*/   case RES_DDEFLD:
/*N*/       {
/*N*/           const ::utl::TransliterationWrapper& rSCmp = GetAppCmpStrIgnore();
/*N*/           String sFldNm( rFldTyp.GetName() );
/*N*/           for( ; i < nSize; ++i )
/*N*/               if( nFldWhich == (*pFldTypes)[i]->Which() &&
/*N*/                   rSCmp.isEqual( sFldNm, (*pFldTypes)[i]->GetName() ))
/*N*/                       return (*pFldTypes)[i];
/*N*/       }
/*N*/       break;
/*N*/
/*N*/   case RES_AUTHORITY:
/*?*/       for( ; i < nSize; ++i )
/*?*/           if( nFldWhich == (*pFldTypes)[i]->Which() )
/*?*/               return (*pFldTypes)[i];
/*?*/       break;
/*?*/
/*?*/   default:
/*?*/       for( i = 0; i < nSize; ++i )
/*?*/           if( nFldWhich == (*pFldTypes)[i]->Which() )
/*?*/               return (*pFldTypes)[i];
/*N*/   }
/*N*/
/*N*/   SwFieldType* pNew = rFldTyp.Copy();
/*N*/   switch( nFldWhich )
/*N*/   {
/*N*/   case RES_DDEFLD:
/*N*/       ((SwDDEFieldType*)pNew)->SetDoc( this );
/*N*/       break;
/*N*/
/*N*/   case RES_DBFLD:
/*N*/   case RES_TABLEFLD:
/*N*/   case RES_DATETIMEFLD:
/*N*/   case RES_GETEXPFLD:
/*N*/       ((SwValueFieldType*)pNew)->SetDoc( this );
/*N*/       break;
/*N*/
/*N*/   case RES_USERFLD:
/*N*/   case RES_SETEXPFLD:
/*N*/       ((SwValueFieldType*)pNew)->SetDoc( this );
/*N*/       // JP 29.07.96: opt. FeldListe fuer den Calculator vorbereiten:
/*N*/       pUpdtFlds->InsertFldType( *pNew );
/*N*/       break;
/*N*/   case RES_AUTHORITY :
/*?*/       ((SwAuthorityFieldType*)pNew)->SetDoc( this );
/*?*/       break;
/*N*/   }
/*N*/
/*N*/   pFldTypes->Insert( pNew, nSize );
/*N*/   SetModified();
/*N*/
/*N*/   return (*pFldTypes)[ nSize ];
/*N*/ }

//STRIP001 void SwDoc::InsDeletedFldType( SwFieldType& rFldTyp )
//STRIP001 {
//STRIP001  // der FeldTyp wurde als geloescht gekennzeichnet und aus dem
//STRIP001  // Array entfernt. Nun muss man nach diesem wieder suchen.
//STRIP001  // - Ist der nicht vorhanden, dann kann er eingefuegt werden.
//STRIP001  // - Wird genau der gleiche Typ gefunden, dann muss der geloeschte
//STRIP001  //   einen anderen Namen erhalten.
//STRIP001
//STRIP001  USHORT nSize = pFldTypes->Count(), nFldWhich = rFldTyp.Which();
//STRIP001  USHORT i = INIT_FLDTYPES;
//STRIP001
//STRIP001  ASSERT( RES_SETEXPFLD == nFldWhich ||
//STRIP001          RES_USERFLD == nFldWhich ||
//STRIP001          RES_DDEFLD == nFldWhich, "Falscher FeldTyp" );
//STRIP001
//STRIP001  const ::utl::TransliterationWrapper& rSCmp = GetAppCmpStrIgnore();
//STRIP001  const String& rFldNm = rFldTyp.GetName();
//STRIP001  SwFieldType* pFnd;
//STRIP001
//STRIP001  for( ; i < nSize; ++i )
//STRIP001      if( nFldWhich == (pFnd = (*pFldTypes)[i])->Which() &&
//STRIP001          rSCmp.isEqual( rFldNm, pFnd->GetName() ) )
//STRIP001      {
//STRIP001          // neuen Namen suchen
//STRIP001          USHORT nNum = 1;
//STRIP001          do {
//STRIP001              String sSrch( rFldNm );
//STRIP001              sSrch.Append( String::CreateFromInt32( nNum ));
//STRIP001              for( i = INIT_FLDTYPES; i < nSize; ++i )
//STRIP001                  if( nFldWhich == (pFnd = (*pFldTypes)[i])->Which() &&
//STRIP001                      rSCmp.isEqual( sSrch, pFnd->GetName() ) )
//STRIP001                      break;
//STRIP001
//STRIP001              if( i >= nSize )        // nicht gefunden
//STRIP001              {
//STRIP001                  ((String&)rFldNm) = sSrch;
//STRIP001                  break;      // raus aus der While-Schleife
//STRIP001              }
//STRIP001              ++nNum;
//STRIP001          } while( TRUE );
//STRIP001          break;
//STRIP001      }
//STRIP001
//STRIP001  // nicht gefunden, also eintragen und Flag loeschen
//STRIP001  pFldTypes->Insert( &rFldTyp, nSize );
//STRIP001  switch( nFldWhich )
//STRIP001  {
//STRIP001  case RES_SETEXPFLD:
//STRIP001      ((SwSetExpFieldType&)rFldTyp).SetDeleted( FALSE );
//STRIP001      break;
//STRIP001  case RES_USERFLD:
//STRIP001      ((SwUserFieldType&)rFldTyp).SetDeleted( FALSE );
//STRIP001      break;
//STRIP001  case RES_DDEFLD:
//STRIP001      ((SwDDEFieldType&)rFldTyp).SetDeleted( FALSE );
//STRIP001      break;
//STRIP001  }
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung: Feldtypen loeschen
 --------------------------------------------------------------------*/

/*N*/ void SwDoc::RemoveFldType(USHORT nFld)
/*N*/ {
/*N*/   ASSERT( INIT_FLDTYPES <= nFld,  "keine InitFields loeschen" );
    /*
      * Abheangige Felder vorhanden -> ErrRaise
     */
/*N*/   USHORT nSize = pFldTypes->Count();
/*N*/   if(nFld < nSize)
/*N*/   {
/*N*/       SwFieldType* pTmp = (*pFldTypes)[nFld];
/*N*/
/*N*/       // JP 29.07.96: opt. FeldListe fuer den Calculator vorbereiten:
/*N*/       USHORT nWhich = pTmp->Which();
/*N*/       switch( nWhich )
/*N*/       {
/*N*/       case RES_SETEXPFLD:
/*N*/       case RES_USERFLD:
/*?*/           {DBG_BF_ASSERT(0, "STRIP"); }//STRIP001 pUpdtFlds->RemoveFldType( *pTmp );
/*?*/           // kein break;
/*N*/       case RES_DDEFLD:
/*?*/           if( pTmp->GetDepends() && !IsUsed( *pTmp ) )
/*?*/           {
/*?*/               if( RES_SETEXPFLD == nWhich )
/*?*/                   ((SwSetExpFieldType*)pTmp)->SetDeleted( TRUE );
/*?*/               else if( RES_USERFLD == nWhich )
/*?*/                   ((SwUserFieldType*)pTmp)->SetDeleted( TRUE );
/*?*/               else
/*?*/                   ((SwDDEFieldType*)pTmp)->SetDeleted( TRUE );
/*?*/               nWhich = 0;
/*?*/           }
/*?*/           break;
/*?*/       }
/*?*/
/*N*/       if( nWhich )
/*N*/       {
/*?*/           ASSERT( !pTmp->GetDepends(), "Abhaengige vorh.!" );
/*?*/           // Feldtype loschen
/*?*/           delete pTmp;
/*N*/       }
/*N*/       pFldTypes->Remove( nFld );
/*N*/       SetModified();
/*N*/   }
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung: Den ersten Typen mit ResId und Namen finden
 --------------------------------------------------------------------*/

/*N*/ SwFieldType* SwDoc::GetFldType( USHORT nResId, const String& rName ) const
/*N*/ {
/*N*/   USHORT nSize = pFldTypes->Count(), i = 0;
/*N*/   const ::utl::TransliterationWrapper& rSCmp = GetAppCmpStrIgnore();
/*N*/
/*N*/   switch( nResId )
/*N*/   {
/*N*/   case RES_SETEXPFLD:
/*N*/           //JP 29.01.96: SequenceFelder beginnen aber bei INIT_FLDTYPES - 3!!
/*N*/           //             Sonst gibt es doppelte Nummernkreise!!
/*N*/           //MIB 14.03.95: Ab sofort verlaesst sich auch der SW3-Reader
/*N*/           //beim Aufbau der String-Pools und beim Einlesen von SetExp-Feldern
/*N*/           //hierauf
/*N*/       i = INIT_FLDTYPES - INIT_SEQ_FLDTYPES;
/*N*/       break;
/*N*/
/*N*/   case RES_DBFLD:
/*N*/   case RES_USERFLD:
/*N*/   case RES_DDEFLD:
/*N*/   case RES_AUTHORITY:
/*N*/       i = INIT_FLDTYPES;
/*N*/       break;
/*N*/   }
/*N*/
/*N*/   SwFieldType* pRet = 0;
/*N*/   for( ; i < nSize; ++i )
/*N*/   {
/*N*/       SwFieldType* pFldType = (*pFldTypes)[i];
/*N*/       if( nResId == pFldType->Which() &&
/*N*/           rSCmp.isEqual( rName, pFldType->GetName() ))
/*N*/       {
/*N*/           pRet = pFldType;
/*N*/           break;
/*N*/       }
/*N*/   }
/*N*/   return pRet;
/*N*/ }


/*************************************************************************
|*                SwDoc::UpdateFlds()
|*    Beschreibung      Felder updaten
*************************************************************************/
/*
 *    Alle sollen neu evaluiert werden.
 */

/*N*/ void SwDoc::UpdateFlds( SfxPoolItem *pNewHt, BOOL bCloseDB )
/*N*/ {
/*?*/     DBG_BF_ASSERT(0, "STRIP"); //STRIP001 // Modify() fuer jeden Feldtypen rufen,
//STRIP001  // abhaengige SwTxtFld werden benachrichtigt ...
//STRIP001
//STRIP001  for( USHORT i=0; i < pFldTypes->Count(); ++i)
//STRIP001  {
//STRIP001      switch( (*pFldTypes)[i]->Which() )
//STRIP001      {
//STRIP001          // Tabellen-Felder als vorletztes Updaten
//STRIP001          // Referenzen als letztes Updaten
//STRIP001      case RES_GETREFFLD:
//STRIP001      case RES_TABLEFLD:
//STRIP001      case RES_DBFLD:
//STRIP001      case RES_JUMPEDITFLD:
//STRIP001      case RES_REFPAGESETFLD:     // werden nie expandiert!
//STRIP001          break;
//STRIP001
//STRIP001      case RES_DDEFLD:
//STRIP001      {
//STRIP001          if( !pNewHt )
//STRIP001          {
//STRIP001              SwMsgPoolItem aUpdateDDE( RES_UPDATEDDETBL );
//STRIP001              (*pFldTypes)[i]->Modify( 0, &aUpdateDDE );
//STRIP001          }
//STRIP001          else
//STRIP001              (*pFldTypes)[i]->Modify( 0, pNewHt );
//STRIP001          break;
//STRIP001      }
//STRIP001      case RES_GETEXPFLD:
//STRIP001      case RES_SETEXPFLD:
//STRIP001      case RES_HIDDENTXTFLD:
//STRIP001      case RES_HIDDENPARAFLD:
//STRIP001          // Expression-Felder werden gesondert behandelt
//STRIP001          if( !pNewHt )
//STRIP001              break;
//STRIP001      default:
//STRIP001          (*pFldTypes)[i]->Modify( 0, pNewHt );
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if( !IsExpFldsLocked() )
//STRIP001      UpdateExpFlds( 0, FALSE );      // Expression-Felder Updaten
//STRIP001
//STRIP001  // Tabellen
//STRIP001  UpdateTblFlds(pNewHt);
//STRIP001
//STRIP001  // Referenzen
//STRIP001  UpdateRefFlds(pNewHt);
//STRIP001
//STRIP001  if( bCloseDB )
//STRIP001      GetNewDBMgr()->CloseAll();
//STRIP001
//STRIP001  // Nur bei KomplettUpdate evaluieren
//STRIP001  SetModified();
/*N*/ }

/******************************************************************************
 *                      void SwDoc::UpdateUsrFlds()
 ******************************************************************************/

//STRIP001 void SwDoc::UpdateUsrFlds()
//STRIP001 {
//STRIP001  SwCalc* pCalc = 0;
//STRIP001  const SwFieldType* pFldType;
//STRIP001  for( USHORT i = INIT_FLDTYPES; i < pFldTypes->Count(); ++i )
//STRIP001      if( RES_USERFLD == ( pFldType = (*pFldTypes)[i] )->Which() )
//STRIP001      {
//STRIP001          if( !pCalc )
//STRIP001              pCalc = new SwCalc( *this );
//STRIP001          ((SwUserFieldType*)pFldType)->GetValue( *pCalc );
//STRIP001      }
//STRIP001
//STRIP001  if( pCalc )
//STRIP001  {
//STRIP001      delete pCalc;
//STRIP001      SetModified();
//STRIP001  }
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung: Referenzfelder und TableFelder erneuern
 --------------------------------------------------------------------*/

/*N*/ void SwDoc::UpdateRefFlds( SfxPoolItem* pHt )
/*N*/ {
/*N*/   SwFieldType* pFldType;
/*N*/   for( USHORT i = 0; i < pFldTypes->Count(); ++i )
/*N*/       if( RES_GETREFFLD == ( pFldType = (*pFldTypes)[i] )->Which() )
/*N*/           pFldType->Modify( 0, pHt );
/*N*/ }

/*N*/ void SwDoc::UpdateTblFlds( SfxPoolItem* pHt )
/*N*/ {
/*N*/   ASSERT( !pHt || RES_TABLEFML_UPDATE  == pHt->Which(),
/*N*/           "Was ist das fuer ein MessageItem?" );
/*N*/
/*N*/   SwFieldType* pFldType;
        USHORT i=0;
/*N*/   for( i = 0; i < pFldTypes->Count(); ++i )
/*N*/   {
/*N*/       if( RES_TABLEFLD == ( pFldType = (*pFldTypes)[i] )->Which() )
/*N*/       {
/*N*/           SwTableFmlUpdate* pUpdtFld = 0;
/*N*/           if( pHt && RES_TABLEFML_UPDATE == pHt->Which() )
/*N*/               pUpdtFld = (SwTableFmlUpdate*)pHt;
/*N*/
/*N*/           SwClientIter aIter( *pFldType );
/*N*/           for( SwFmtFld* pFmtFld = (SwFmtFld*)aIter.First( TYPE( SwFmtFld ));
/*N*/                   pFmtFld; pFmtFld = (SwFmtFld*)aIter.Next() )
/*N*/               if( pFmtFld->GetTxtFld() )
/*N*/               {
/*N*/                   SwTblField* pFld = (SwTblField*)pFmtFld->GetFld();
/*N*/
/*N*/                   if( pUpdtFld )
/*N*/                   {
/*?*/                       // bestimme Tabelle, in der das Feld steht
/*?*/                       const SwTableNode* pTblNd;
/*?*/                       const SwTxtNode& rTxtNd = pFmtFld->GetTxtFld()->GetTxtNode();
/*?*/                       if( !rTxtNd.GetNodes().IsDocNodes() ||
/*?*/                           0 == ( pTblNd = rTxtNd.FindTableNode() ) )
/*?*/                           continue;
/*?*/
/*?*/                       switch( pUpdtFld->eFlags )
/*?*/                       {
/*?*/                       case TBL_CALC:
/*?*/                           // setze das Value-Flag zurueck
/*?*/                           // JP 17.06.96: interne Darstellung auf alle Formeln
/*?*/                           //              (Referenzen auf andere Tabellen!!!)
/*?*/                           if( SUB_CMD & pFld->GetSubType() )
/*?*/                               pFld->PtrToBoxNm( pUpdtFld->pTbl );
/*?*/                           else
/*?*/                               pFld->ChgValid( FALSE );
/*?*/                           break;
/*?*/                       case TBL_BOXNAME:
/*?*/                           // ist es die gesuchte Tabelle ??
/*?*/                           if( &pTblNd->GetTable() == pUpdtFld->pTbl )
/*?*/                               // zur externen Darstellung
/*?*/                               pFld->PtrToBoxNm( pUpdtFld->pTbl );
/*?*/                           break;
/*?*/                       case TBL_BOXPTR:
/*?*/                           // zur internen Darstellung
/*?*/                           // JP 17.06.96: interne Darstellung auf alle Formeln
/*?*/                           //              (Referenzen auf andere Tabellen!!!)
/*?*/                           pFld->BoxNmToPtr( pUpdtFld->pTbl );
/*?*/                           break;
/*?*/                       case TBL_RELBOXNAME:
/*?*/                           // ist es die gesuchte Tabelle ??
/*?*/                           if( &pTblNd->GetTable() == pUpdtFld->pTbl )
/*?*/                               // zur relativen Darstellung
/*?*/                               {DBG_BF_ASSERT(0, "STRIP"); }//STRIP001 pFld->ToRelBoxNm( pUpdtFld->pTbl );
/*?*/                           break;
/*?*/                       }
/*N*/                   }
/*N*/                   else
/*?*/                       // setze bei allen das Value-Flag zurueck
/*?*/                       pFld->ChgValid( FALSE );
/*N*/               }
/*N*/
/*N*/           break;
/*N*/       }
/*N*/       pFldType = 0;
/*N*/   }

    // und dann noch alle Tabellen Box Formeln abklappern
/*N*/   const SfxPoolItem* pItem;
/*N*/   USHORT nMaxItems = GetAttrPool().GetItemCount( RES_BOXATR_FORMULA );
/*N*/   for( i = 0; i < nMaxItems; ++i )
/*N*/       if( 0 != (pItem = GetAttrPool().GetItem( RES_BOXATR_FORMULA, i ) ) &&
/*N*/           ((SwTblBoxFormula*)pItem)->GetDefinedIn() )
/*?*/       {
/*?*/       DBG_BF_ASSERT(0, "STRIP"); //STRIP001   ((SwTblBoxFormula*)pItem)->ChangeState( pHt );
/*?*/       }
/*?*/
/*?*/
/*?*/   // alle Felder/Boxen sind jetzt invalide, also kann das Rechnen anfangen
/*?*/   if( pHt && ( RES_TABLEFML_UPDATE != pHt->Which() ||
/*?*/               TBL_CALC != ((SwTableFmlUpdate*)pHt)->eFlags ))
/*?*/       return ;
/*N*/
/*N*/   SwCalc* pCalc = 0;
/*N*/
/*N*/   if( pFldType )
/*N*/   {
/*N*/       SwClient* pLast;
/*N*/       SwClientIter aIter( *pFldType );
/*N*/       // dann rechne mal schoen
/*N*/       // JP 27.03.97: Beim Berechnen am Ende anfangen - weil neue
/*N*/       //              Felder immer am Anfang der Modifykette eingefuegt
/*N*/       //              werden. Beim Import haben wir damit eine bessere/
/*N*/       //              schnellere Berechnung bei "Kettenformeln"
/*N*/       if( 0 != ( pLast = aIter.GoEnd() ))
/*N*/           do {
/*N*/               SwFmtFld* pFmtFld = (SwFmtFld*)pLast;
/*N*/               SwTblField* pFld;
/*N*/               if( !pFmtFld->GetTxtFld() || (SUB_CMD &
/*N*/                   (pFld = (SwTblField*)pFmtFld->GetFld())->GetSubType() ))
/*N*/                   continue;
/*N*/
/*N*/               // muss neu berechnet werden (und ist keine textuelle Anzeige)
/*N*/               if( !pFld->IsValid() )
/*N*/               {
/*N*/                   // bestimme Tabelle, in der das Feld steht
/*N*/                   const SwTxtNode& rTxtNd = pFmtFld->GetTxtFld()->GetTxtNode();
/*N*/                   if( !rTxtNd.GetNodes().IsDocNodes() )
/*N*/                       continue;
/*N*/                   const SwTableNode* pTblNd = rTxtNd.FindTableNode();
/*N*/                   if( !pTblNd )
/*N*/                       continue;
/*N*/
/*N*/                   // falls dieses Feld nicht in der zu updatenden
/*N*/                   // Tabelle steht, ueberspringen !!
/*N*/                   if( pHt && &pTblNd->GetTable() !=
/*N*/                                           ((SwTableFmlUpdate*)pHt)->pTbl )
/*N*/                       continue;
/*N*/
/*N*/                   if( !pCalc )
/*N*/                       pCalc = new SwCalc( *this );
/*N*/
/*N*/                   // bestimme die Werte aller SetExpresion Felder, die
/*N*/                   // bis zur Tabelle gueltig sind
/*N*/                   SwFrm* pFrm = 0;
/*N*/                   if( pTblNd->GetIndex() < GetNodes().GetEndOfExtras().GetIndex() )
/*N*/                   {
/*N*/                       DBG_BF_ASSERT(0, "STRIP"); //STRIP001 // steht im Sonderbereich, wird teuer !!
//STRIP001 /*?*/                        Point aPt;      // den im Layout 1. Frame returnen - Tab.Kopfzeile !!
//STRIP001 /*?*/                        pFrm = rTxtNd.GetFrm( &aPt );
//STRIP001 /*?*/                        if( pFrm )
//STRIP001 /*?*/                        {
//STRIP001 /*?*/                            SwPosition aPos( *pTblNd );
//STRIP001 /*?*/                            if( GetBodyTxtNode( *this, aPos, *pFrm ) )
//STRIP001 /*?*/                                FldsToCalc( *pCalc, _SetGetExpFld(
//STRIP001 /*?*/                                    aPos.nNode, pFmtFld->GetTxtFld(),
//STRIP001 /*?*/                                    &aPos.nContent ));
//STRIP001 /*?*/                            else
//STRIP001 /*?*/                                pFrm = 0;
//STRIP001 /*?*/                        }
/*N*/                   }
/*N*/                   if( !pFrm )
/*N*/                   {
/*N*/                       // einen Index fuers bestimmen vom TextNode anlegen
/*N*/                       SwNodeIndex aIdx( rTxtNd );
/*N*/                       FldsToCalc( *pCalc,
/*N*/                           _SetGetExpFld( aIdx, pFmtFld->GetTxtFld() ));
/*N*/                   }
/*N*/
/*N*/                   SwTblCalcPara aPara( *pCalc, pTblNd->GetTable() );
/*N*/                   pFld->CalcField( aPara );
/*N*/                   if( aPara.IsStackOverFlow() )
/*N*/                   {
/*?*/                   DBG_BF_ASSERT(0, "STRIP"); //STRIP001   if( aPara.CalcWithStackOverflow() )
//STRIP001 /*?*/                            pFld->CalcField( aPara );
//STRIP001 /*?*/ #ifndef PRODUCT
//STRIP001 /*?*/                        else
//STRIP001 /*?*/                        {
//STRIP001 /*?*/                            // mind. ein ASSERT
//STRIP001 /*?*/                            ASSERT( !this, "die Kettenformel konnte nicht errechnet werden" );
//STRIP001 /*?*/                        }
//STRIP001 /*?*/ #endif
/*N*/                   }
/*N*/                   pCalc->SetCalcError( CALC_NOERR );
/*N*/               }
/*N*/               pFmtFld->Modify( 0, pHt );
/*N*/           } while( 0 != ( pLast = aIter-- ));
/*N*/   }
/*N*/
/*N*/   // dann berechene noch die Formeln an den Boxen
/*N*/   for( i = 0; i < nMaxItems; ++i )
/*N*/       if( 0 != (pItem = GetAttrPool().GetItem( RES_BOXATR_FORMULA, i ) ) &&
/*N*/           ((SwTblBoxFormula*)pItem)->GetDefinedIn() &&
/*N*/           !((SwTblBoxFormula*)pItem)->IsValid() )
/*?*/       {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/            SwTblBoxFormula* pFml = (SwTblBoxFormula*)pItem;
//STRIP001 /*?*/            SwTableBox* pBox = pFml->GetTableBox();
//STRIP001 /*?*/            if( pBox && pBox->GetSttNd() &&
//STRIP001 /*?*/                pBox->GetSttNd()->GetNodes().IsDocNodes() )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                const SwTableNode* pTblNd = pBox->GetSttNd()->FindTableNode();
//STRIP001 /*?*/                if( !pHt || &pTblNd->GetTable() ==
//STRIP001 /*?*/                                            ((SwTableFmlUpdate*)pHt)->pTbl )
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    double nValue;
//STRIP001 /*?*/                    if( !pCalc )
//STRIP001 /*?*/                        pCalc = new SwCalc( *this );
//STRIP001 /*?*/
//STRIP001 /*?*/                    // bestimme die Werte aller SetExpresion Felder, die
//STRIP001 /*?*/                    // bis zur Tabelle gueltig sind
//STRIP001 /*?*/                    SwFrm* pFrm = 0;
//STRIP001 /*?*/                    if( pTblNd->GetIndex() < GetNodes().GetEndOfExtras().GetIndex() )
//STRIP001 /*?*/                    {
//STRIP001 /*?*/                        // steht im Sonderbereich, wird teuer !!
//STRIP001 /*?*/                        Point aPt;      // den im Layout 1. Frame returnen - Tab.Kopfzeile !!
//STRIP001 /*?*/                        SwNodeIndex aCNdIdx( *pTblNd, +2 );
//STRIP001 /*?*/                        SwCntntNode* pCNd = aCNdIdx.GetNode().GetCntntNode();
//STRIP001 /*?*/                        if( !pCNd )
//STRIP001 /*?*/                            pCNd = GetNodes().GoNext( &aCNdIdx );
//STRIP001 /*?*/
//STRIP001 /*?*/                        if( pCNd && 0 != (pFrm = pCNd->GetFrm( &aPt )) )
//STRIP001 /*?*/                        {
//STRIP001 /*?*/                            SwPosition aPos( *pCNd );
//STRIP001 /*?*/                            if( GetBodyTxtNode( *this, aPos, *pFrm ) )
//STRIP001 /*?*/                                FldsToCalc( *pCalc, _SetGetExpFld( aPos.nNode ));
//STRIP001 /*?*/                            else
//STRIP001 /*?*/                                pFrm = 0;
//STRIP001 /*?*/                        }
//STRIP001 /*?*/                    }
//STRIP001 /*?*/                    if( !pFrm )
//STRIP001 /*?*/                    {
//STRIP001 /*?*/                        // einen Index fuers bestimmen vom TextNode anlegen
//STRIP001 /*?*/                        SwNodeIndex aIdx( *pTblNd );
//STRIP001 /*?*/                        FldsToCalc( *pCalc, _SetGetExpFld( aIdx ));
//STRIP001 /*?*/                    }
//STRIP001 /*?*/
//STRIP001 /*?*/                    SwTblCalcPara aPara( *pCalc, pTblNd->GetTable() );
//STRIP001 /*?*/                    pFml->Calc( aPara, nValue );
//STRIP001 /*?*/
//STRIP001 /*?*/                    if( aPara.IsStackOverFlow() )
//STRIP001 /*?*/                    {
//STRIP001 /*?*/                        if( aPara.CalcWithStackOverflow() )
//STRIP001 /*?*/                            pFml->Calc( aPara, nValue );
//STRIP001 /*?*/ #ifndef PRODUCT
//STRIP001 /*?*/                        else
//STRIP001 /*?*/                        {
//STRIP001 /*?*/                            // mind. ein ASSERT
//STRIP001 /*?*/                            ASSERT( !this, "die Kettenformel konnte nicht errechnet werden" );
//STRIP001 /*?*/                        }
//STRIP001 /*?*/ #endif
//STRIP001 /*?*/                    }
//STRIP001 /*?*/
//STRIP001 /*?*/                    SwFrmFmt* pFmt = pBox->ClaimFrmFmt();
//STRIP001 /*?*/                    SfxItemSet aTmp( GetAttrPool(),
//STRIP001 /*?*/                                    RES_BOXATR_BEGIN,RES_BOXATR_END-1 );
//STRIP001 /*?*/
//STRIP001 /*?*/                    if( pCalc->IsCalcError() )
//STRIP001 /*?*/                        nValue = DBL_MAX;
//STRIP001 /*?*/                    aTmp.Put( SwTblBoxValue( nValue ));
//STRIP001 /*?*/                    if( SFX_ITEM_SET != pFmt->GetItemState( RES_BOXATR_FORMAT ))
//STRIP001 /*?*/                        aTmp.Put( SwTblBoxNumFormat( 0 ));
//STRIP001 /*?*/                    pFmt->SetAttr( aTmp );
//STRIP001 /*?*/
//STRIP001 /*?*/                    pCalc->SetCalcError( CALC_NOERR );
//STRIP001 /*?*/                }
//STRIP001 /*?*/            }
/*?*/       }
/*?*/
/*N*/   if( pCalc )
/*N*/       delete pCalc;
/*N*/ }

/*N*/ void SwDoc::UpdatePageFlds( SfxPoolItem* pMsgHnt )
/*N*/ {
/*N*/   SwFieldType* pFldType;
/*N*/   for( USHORT i = 0; i < INIT_FLDTYPES; ++i )
/*N*/       switch( ( pFldType = (*pFldTypes)[ i ] )->Which() )
/*N*/       {
/*N*/       case RES_PAGENUMBERFLD:
/*N*/       case RES_CHAPTERFLD:
/*N*/       case RES_GETEXPFLD:
/*N*/       case RES_REFPAGEGETFLD:
/*N*/           pFldType->Modify( 0, pMsgHnt );
/*N*/           break;
/*N*/       case RES_DOCSTATFLD:
/*N*/           pFldType->Modify( 0, 0 );
/*N*/           break;
/*N*/       }
/*N*/   SetNewFldLst();
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung:
 --------------------------------------------------------------------*/

// ---- Loesche alle nicht referenzierten FeldTypen eines Dokumentes --
//STRIP001 void SwDoc::GCFieldTypes()
//STRIP001 {
//STRIP001  for( register USHORT n = pFldTypes->Count(); n > INIT_FLDTYPES; )
//STRIP001      if( !(*pFldTypes)[ --n ]->GetDepends() )
//STRIP001          RemoveFldType( n );
//STRIP001 }


//----------------------------------------------------------------------

// der StartIndex kann optional mit angegeben werden (z.B. wenn dieser
// zuvor schon mal erfragt wurde - ist sonst eine virtuelle Methode !!)

/*N*/ _SetGetExpFld::_SetGetExpFld( const SwNodeIndex& rNdIdx, const SwTxtFld* pFld,
/*N*/                           const SwIndex* pIdx )
/*N*/ {
/*N*/   eSetGetExpFldType = TEXTFIELD;
/*N*/   CNTNT.pTxtFld = pFld;
/*N*/   nNode = rNdIdx.GetIndex();
/*N*/   if( pIdx )
/*N*/       nCntnt = pIdx->GetIndex();
/*N*/   else if( pFld )
/*N*/       nCntnt = *pFld->GetStart();
/*N*/   else
/*N*/       nCntnt = 0;
/*N*/ }

/*N*/ _SetGetExpFld::_SetGetExpFld( const SwNodeIndex& rNdIdx,
/*N*/                           const SwTxtINetFmt& rINet, const SwIndex* pIdx )
/*N*/ {
/*N*/   eSetGetExpFldType = TEXTINET;
/*N*/   CNTNT.pTxtINet = &rINet;
/*N*/   nNode = rNdIdx.GetIndex();
/*N*/   if( pIdx )
/*N*/       nCntnt = pIdx->GetIndex();
/*N*/   else
/*N*/       nCntnt = *rINet.GetStart();
/*N*/ }

    //Erweiterung fuer Sections:
    //  diese haben immer als Content-Position 0xffff !!
    //  Auf dieser steht nie ein Feld, maximal bis STRING_MAXLEN moeglich
/*N*/ _SetGetExpFld::_SetGetExpFld( const SwSectionNode& rSectNd,
/*N*/                               const SwPosition* pPos )
/*N*/ {
/*N*/   eSetGetExpFldType = SECTIONNODE;
/*N*/   CNTNT.pSection = &rSectNd.GetSection();
/*N*/
/*N*/   if( pPos )
/*N*/   {
/*N*/       nNode = pPos->nNode.GetIndex();
/*N*/       nCntnt = pPos->nContent.GetIndex();
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       nNode = rSectNd.GetIndex();
/*N*/       nCntnt = 0;
/*N*/   }
/*N*/ }

/*N*/ _SetGetExpFld::_SetGetExpFld( const SwTableBox& rTBox, const SwPosition* pPos )
/*N*/ {
/*N*/   eSetGetExpFldType = TABLEBOX;
/*N*/   CNTNT.pTBox = &rTBox;
/*N*/
/*N*/   if( pPos )
/*N*/   {
/*N*/       nNode = pPos->nNode.GetIndex();
/*N*/       nCntnt = pPos->nContent.GetIndex();
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       nNode = 0;
/*N*/       nCntnt = 0;
/*N*/       if( rTBox.GetSttNd() )
/*N*/       {
/*N*/           SwNodeIndex aIdx( *rTBox.GetSttNd() );
/*N*/           const SwCntntNode* pNd = aIdx.GetNode().GetNodes().GoNext( &aIdx );
/*N*/           if( pNd )
/*N*/               nNode = pNd->GetIndex();
/*N*/       }
/*N*/   }
/*N*/ }

/*N*/ _SetGetExpFld::_SetGetExpFld( const SwNodeIndex& rNdIdx,
/*N*/                               const SwTxtTOXMark& rTOX,
/*N*/                               const SwIndex* pIdx )
/*N*/ {
/*N*/   eSetGetExpFldType = TEXTTOXMARK;
/*N*/   CNTNT.pTxtTOX = &rTOX;
/*N*/   nNode = rNdIdx.GetIndex();
/*N*/   if( pIdx )
/*N*/       nCntnt = pIdx->GetIndex();
/*N*/   else
/*N*/       nCntnt = *rTOX.GetStart();
/*N*/ }

/*N*/ _SetGetExpFld::_SetGetExpFld( const SwPosition& rPos )
/*N*/ {
/*N*/   eSetGetExpFldType = CRSRPOS;
/*N*/   CNTNT.pPos = &rPos;
/*N*/   nNode = rPos.nNode.GetIndex();
/*N*/   nCntnt = rPos.nContent.GetIndex();
/*N*/ }

/*N*/ _SetGetExpFld::_SetGetExpFld( const SwFlyFrmFmt& rFlyFmt,
/*N*/                               const SwPosition* pPos  )
/*N*/ {
/*N*/   eSetGetExpFldType = FLYFRAME;
/*N*/   CNTNT.pFlyFmt = &rFlyFmt;
/*N*/   if( pPos )
/*N*/   {
/*N*/       nNode = pPos->nNode.GetIndex();
/*N*/       nCntnt = pPos->nContent.GetIndex();
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       const SwFmtCntnt& rCntnt = rFlyFmt.GetCntnt();
/*N*/       nNode = rCntnt.GetCntntIdx()->GetIndex() + 1;
/*N*/       nCntnt = 0;
/*N*/   }
/*N*/ }

//STRIP001 void _SetGetExpFld::GetPos( SwPosition& rPos ) const
//STRIP001 {
//STRIP001  rPos.nNode = nNode;
//STRIP001  rPos.nContent.Assign( rPos.nNode.GetNode().GetCntntNode(), nCntnt );
//STRIP001 }

//STRIP001 void _SetGetExpFld::GetPosOfContent( SwPosition& rPos ) const
//STRIP001 {
//STRIP001  const SwNode* pNd = GetNodeFromCntnt();
//STRIP001  if( pNd )
//STRIP001      pNd = pNd->GetCntntNode();
//STRIP001
//STRIP001  if( pNd )
//STRIP001  {
//STRIP001      rPos.nNode = *pNd;
//STRIP001      rPos.nContent.Assign( (SwCntntNode*)pNd,GetCntPosFromCntnt() );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      rPos.nNode = nNode;
//STRIP001      rPos.nContent.Assign( rPos.nNode.GetNode().GetCntntNode(), nCntnt );
//STRIP001  }
//STRIP001 }

//STRIP001 void _SetGetExpFld::SetBodyPos( const SwCntntFrm& rFrm )
//STRIP001 {
//STRIP001  if( !rFrm.IsInDocBody() )
//STRIP001  {
//STRIP001      SwNodeIndex aIdx( *rFrm.GetNode() );
//STRIP001      SwDoc& rDoc = *aIdx.GetNodes().GetDoc();
//STRIP001      SwPosition aPos( aIdx );
//STRIP001 #ifndef PRODUCT
//STRIP001      ASSERT( ::GetBodyTxtNode( rDoc, aPos, rFrm ), "wo steht das Feld" );
//STRIP001 #else
//STRIP001      ::GetBodyTxtNode( rDoc, aPos, rFrm );
//STRIP001 #endif
//STRIP001      nNode = aPos.nNode.GetIndex();
//STRIP001      nCntnt = aPos.nContent.GetIndex();
//STRIP001  }
//STRIP001 }

/*N*/ BOOL _SetGetExpFld::operator<( const _SetGetExpFld& rFld ) const
/*N*/ {
/*N*/   if( nNode < rFld.nNode || ( nNode == rFld.nNode && nCntnt < rFld.nCntnt ))
/*N*/       return TRUE;
/*N*/   else if( nNode != rFld.nNode || nCntnt != rFld.nCntnt )
/*N*/       return FALSE;
/*N*/
/*N*/   const SwNode *pFirst = GetNodeFromCntnt(),
/*N*/                *pNext = rFld.GetNodeFromCntnt();
/*N*/
/*N*/   // Position gleich: nur weiter wenn beide FeldPointer besetzt sind !!
/*N*/   if( !pFirst || !pNext )
/*N*/       return FALSE;
/*N*/
/*N*/   // gleiche Section ??
/*N*/   if( pFirst->StartOfSectionNode() != pNext->StartOfSectionNode() )
/*N*/   {
/*N*/       // sollte einer in der Tabelle stehen ?
/*N*/       const SwNode *pFirstStt, *pNextStt;
/*N*/       const SwTableNode* pTblNd = pFirst->FindTableNode();
/*N*/       if( pTblNd )
/*N*/           pFirstStt = pTblNd->StartOfSectionNode();
/*N*/       else
/*N*/           pFirstStt = pFirst->StartOfSectionNode();
/*N*/
/*N*/       if( 0 != ( pTblNd = pNext->FindTableNode() ) )
/*N*/           pNextStt = pTblNd->StartOfSectionNode();
/*N*/       else
/*N*/           pNextStt = pNext->StartOfSectionNode();
/*N*/
/*N*/       if( pFirstStt != pNextStt )
/*N*/       {
/*N*/           if( pFirst->IsTxtNode() && pNext->IsTxtNode() &&
/*N*/               ( pFirst->FindFlyStartNode() || pNext->FindFlyStartNode() ))
/*N*/           {
/*?*/               DBG_BF_ASSERT(0, "STRIP"); //STRIP001 return ::IsFrameBehind( *(SwTxtNode*)pNext, nCntnt,
//STRIP001 /*?*/                                        *(SwTxtNode*)pFirst, nCntnt );
/*N*/           }
/*N*/           return pFirstStt->GetIndex() < pNextStt->GetIndex();
/*N*/       }
/*N*/   }
/*N*/
/*N*/   // ist gleiche Section, dann Feld im gleichen Node ?
/*N*/   if( pFirst != pNext )
/*N*/       return pFirst->GetIndex() < pNext->GetIndex();
/*N*/
/*N*/   // gleicher Node in der Section, dann Position im Node
/*N*/   return GetCntPosFromCntnt() < rFld.GetCntPosFromCntnt();
/*N*/ }

/*N*/ const SwNode* _SetGetExpFld::GetNodeFromCntnt() const
/*N*/ {
/*N*/   const SwNode* pRet = 0;
/*N*/   if( CNTNT.pTxtFld )
/*N*/       switch( eSetGetExpFldType )
/*N*/       {
/*N*/       case TEXTFIELD:
/*N*/           pRet = &CNTNT.pTxtFld->GetTxtNode();
/*N*/           break;
/*N*/
/*N*/       case TEXTINET:
/*N*/           pRet = &CNTNT.pTxtINet->GetTxtNode();
/*N*/           break;
/*N*/
/*N*/       case SECTIONNODE:
/*N*/           pRet = CNTNT.pSection->GetFmt()->GetSectionNode();
/*N*/           break;
/*N*/
/*N*/       case CRSRPOS:
/*N*/           pRet = &CNTNT.pPos->nNode.GetNode();
/*N*/           break;
/*N*/
/*N*/       case TEXTTOXMARK:
/*N*/           pRet = &CNTNT.pTxtTOX->GetTxtNode();
/*N*/           break;
/*N*/
/*N*/       case TABLEBOX:
/*N*/           if( CNTNT.pTBox->GetSttNd() )
/*N*/           {
/*N*/               SwNodeIndex aIdx( *CNTNT.pTBox->GetSttNd() );
/*N*/               pRet = aIdx.GetNode().GetNodes().GoNext( &aIdx );
/*N*/           }
/*N*/           break;
/*N*/
/*N*/       case FLYFRAME:
/*N*/           {
/*N*/               SwNodeIndex aIdx( *CNTNT.pFlyFmt->GetCntnt().GetCntntIdx() );
/*N*/               pRet = aIdx.GetNode().GetNodes().GoNext( &aIdx );
/*N*/           }
/*N*/           break;
/*N*/       }
/*N*/   return pRet;
/*N*/ }

/*N*/ xub_StrLen _SetGetExpFld::GetCntPosFromCntnt() const
/*N*/ {
/*N*/   USHORT nRet = 0;
/*N*/   if( CNTNT.pTxtFld )
/*N*/       switch( eSetGetExpFldType )
/*N*/       {
/*N*/       case TEXTFIELD:
/*N*/       case TEXTINET:
/*N*/       case TEXTTOXMARK:
/*N*/           nRet = *CNTNT.pTxtFld->GetStart();
/*N*/           break;
/*N*/       case CRSRPOS:
/*N*/           nRet =  CNTNT.pPos->nContent.GetIndex();
/*N*/           break;
/*N*/       }
/*N*/   return nRet;
/*N*/ }

/*N*/ _HashStr::_HashStr( const String& rName, const String& rText,
/*N*/                   _HashStr* pNxt )
/*N*/   : SwHash( rName ), aSetStr( rText )
/*N*/ {
/*N*/   pNext = pNxt;
/*N*/ }

// suche nach dem Namen, ist er vorhanden, returne seinen String, sonst
// einen LeerString
/*N*/ void LookString( SwHash** ppTbl, USHORT nSize, const String& rName,
/*N*/                   String& rRet, USHORT* pPos )
/*N*/ {
/*N*/   rRet = rName;
/*N*/   rRet.EraseLeadingChars().EraseTrailingChars();
/*N*/   SwHash* pFnd = Find( rRet, ppTbl, nSize, pPos );
/*N*/   if( pFnd )
/*N*/       rRet = ((_HashStr*)pFnd)->aSetStr;
/*N*/   else
/*N*/       rRet.Erase();
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung:
 --------------------------------------------------------------------*/

/*?*/ String lcl_GetDBVarName( SwDoc& rDoc, SwDBNameInfField& rDBFld )
/*?*/ {
/*?*/   SwDBData aDBData( rDBFld.GetDBData( &rDoc ));
/*?*/   String sDBNumNm;
/*?*/   SwDBData aDocData = rDoc.GetDBData();
/*?*/
/*?*/   if( aDBData != aDocData )
/*?*/   {
/*?*/       sDBNumNm = aDBData.sDataSource;
/*?*/       sDBNumNm += DB_DELIM;
/*?*/       sDBNumNm += String(aDBData.sCommand);
/*?*/       sDBNumNm += DB_DELIM;
/*?*/   }
/*?*/   sDBNumNm += SwFieldType::GetTypeStr(TYP_DBSETNUMBERFLD);
/*?*/
/*?*/   return sDBNumNm;
/*?*/ }

/*--------------------------------------------------------------------
    Beschreibung:
 --------------------------------------------------------------------*/

/*N*/ void lcl_CalcFld( SwDoc& rDoc, SwCalc& rCalc, const _SetGetExpFld& rSGEFld,
/*N*/                       SwNewDBMgr* pMgr )
/*N*/ {
/*N*/   const SwTxtFld* pTxtFld = rSGEFld.GetFld();
/*N*/   if( !pTxtFld )
/*N*/       return ;
/*N*/
/*N*/   const SwField* pFld = pTxtFld->GetFld().GetFld();
/*N*/   const USHORT nFldWhich = pFld->GetTyp()->Which();
/*N*/
/*N*/   if( RES_SETEXPFLD == nFldWhich )
/*N*/   {
/*?*/       DBG_BF_ASSERT(0, "STRIP"); //STRIP001 SwSbxValue aValue;
//STRIP001 /*?*/        if( GSE_EXPR & pFld->GetSubType() )
//STRIP001 /*?*/            aValue.PutDouble( ((SwSetExpField*)pFld)->GetValue() );
//STRIP001 /*?*/        else
//STRIP001 /*?*/            // Erweiterung fuers Rechnen mit Strings
//STRIP001 /*?*/            aValue.PutString( ((SwSetExpField*)pFld)->GetExpStr() );
//STRIP001 /*?*/
//STRIP001 /*?*/        // setze im Calculator den neuen Wert
//STRIP001 /*?*/        rCalc.VarChange( pFld->GetTyp()->GetName(), aValue );
/*?*/   }
/*?*/   else if( pMgr )
/*?*/   {
//STRIP001 /*?*/        switch( nFldWhich )
//STRIP001 /*?*/        {
//STRIP001 /*?*/        case RES_DBNUMSETFLD:
//STRIP001 /*?*/            {
//STRIP001 /*?*/                SwDBNumSetField* pDBFld = (SwDBNumSetField*)pFld;
//STRIP001 /*?*/
//STRIP001 /*?*/                SwDBData aDBData(pDBFld->GetDBData(&rDoc));
//STRIP001 /*?*/
//STRIP001 /*?*/                if( pDBFld->IsCondValid() &&
//STRIP001 /*?*/                    pMgr->OpenDataSource( aDBData.sDataSource, aDBData.sCommand ))
//STRIP001 /*?*/                    rCalc.VarChange( lcl_GetDBVarName( rDoc, *pDBFld),
//STRIP001 /*?*/                                    pDBFld->GetFormat() );
//STRIP001 /*?*/            }
//STRIP001 /*?*/            break;
//STRIP001 /*?*/        case RES_DBNEXTSETFLD:
//STRIP001 /*?*/            {
//STRIP001 /*?*/                SwDBNextSetField* pDBFld = (SwDBNextSetField*)pFld;
//STRIP001 /*?*/                SwDBData aDBData(pDBFld->GetDBData(&rDoc));
//STRIP001 /*?*/                if( !pDBFld->IsCondValid() ||
//STRIP001 /*?*/                    !pMgr->OpenDataSource( aDBData.sDataSource, aDBData.sCommand ))
//STRIP001 /*?*/                    break;
//STRIP001 /*?*/
//STRIP001 /*?*/                String sDBNumNm(lcl_GetDBVarName( rDoc, *pDBFld));
//STRIP001 /*?*/                SwCalcExp* pExp = rCalc.VarLook( sDBNumNm );
//STRIP001 /*?*/                if( pExp )
//STRIP001 /*?*/                    rCalc.VarChange( sDBNumNm, pExp->nValue.GetLong() + 1 );
//STRIP001 /*?*/            }
//STRIP001 /*?*/            break;
//STRIP001 /*?*/
//STRIP001 /*?*/        }
/*N*/   }
/*N*/ }

/*N*/ void SwDoc::FldsToCalc( SwCalc& rCalc, const _SetGetExpFld& rToThisFld )
/*N*/ {
/*N*/   // erzeuge die Sortierteliste aller SetFelder
/*N*/   pUpdtFlds->MakeFldList( *this, bNewFldLst, GETFLD_CALC );
/*N*/   bNewFldLst = FALSE;
/*N*/
/*N*/   SwNewDBMgr* pMgr = GetNewDBMgr();
/*N*/   pMgr->CloseAll(FALSE);
/*N*/
/*N*/   if( pUpdtFlds->GetSortLst()->Count() )
/*N*/   {
/*N*/       USHORT nLast;
/*N*/       _SetGetExpFld* pFld = (_SetGetExpFld*)&rToThisFld;
/*N*/       if( pUpdtFlds->GetSortLst()->Seek_Entry( pFld, &nLast ) )
/*N*/           ++nLast;
/*N*/
/*N*/       const _SetGetExpFldPtr* ppSortLst = pUpdtFlds->GetSortLst()->GetData();
/*N*/       for( USHORT n = 0; n < nLast; ++n, ++ppSortLst )
/*N*/           lcl_CalcFld( *this, rCalc, **ppSortLst, pMgr );
/*N*/   }
/*N*/
/*N*/   pMgr->CloseAll(FALSE);
/*N*/ }

//STRIP001 void SwDoc::FldsToCalc( SwCalc& rCalc, ULONG nLastNd, USHORT nLastCnt )
//STRIP001 {
//STRIP001  // erzeuge die Sortierteliste aller SetFelder
//STRIP001  pUpdtFlds->MakeFldList( *this, bNewFldLst, GETFLD_CALC );
//STRIP001  bNewFldLst = FALSE;
//STRIP001
//STRIP001  SwNewDBMgr* pMgr = GetNewDBMgr();
//STRIP001  pMgr->CloseAll(FALSE);
//STRIP001
//STRIP001  const _SetGetExpFldPtr* ppSortLst = pUpdtFlds->GetSortLst()->GetData();
//STRIP001
//STRIP001  for( USHORT n = pUpdtFlds->GetSortLst()->Count();
//STRIP001         n &&
//STRIP001         ( (*ppSortLst)->GetNode() < nLastNd ||
//STRIP001           ( (*ppSortLst)->GetNode() == nLastNd && (*ppSortLst)->GetCntnt() <= nLastCnt )
//STRIP001         );
//STRIP001      --n, ++ppSortLst )
//STRIP001      lcl_CalcFld( *this, rCalc, **ppSortLst, pMgr );
//STRIP001
//STRIP001  pMgr->CloseAll(FALSE);
//STRIP001 }

//STRIP001 void SwDoc::FldsToExpand( SwHash**& ppHashTbl, USHORT& rTblSize,
//STRIP001                          const _SetGetExpFld& rToThisFld )
//STRIP001 {
//STRIP001  // erzeuge die Sortierteliste aller SetFelder
//STRIP001  pUpdtFlds->MakeFldList( *this, bNewFldLst, GETFLD_EXPAND );
//STRIP001  bNewFldLst = FALSE;
//STRIP001
//STRIP001  // HashTabelle fuer alle String Ersetzungen, wird "one the fly" gefuellt
//STRIP001  // (versuche eine "ungerade"-Zahl zu erzeugen)
//STRIP001  rTblSize = (( pUpdtFlds->GetSortLst()->Count() / 7 ) + 1 ) * 7;
//STRIP001  ppHashTbl = new SwHash*[ rTblSize ];
//STRIP001  memset( ppHashTbl, 0, sizeof( _HashStr* ) * rTblSize );
//STRIP001
//STRIP001  USHORT nLast;
//STRIP001  {
//STRIP001      _SetGetExpFld* pTmp = (_SetGetExpFld*)&rToThisFld;
//STRIP001      if( pUpdtFlds->GetSortLst()->Seek_Entry( pTmp, &nLast ) )
//STRIP001          ++nLast;
//STRIP001  }
//STRIP001
//STRIP001  USHORT nPos;
//STRIP001  SwHash* pFnd;
//STRIP001  String aNew;
//STRIP001  const _SetGetExpFldPtr* ppSortLst = pUpdtFlds->GetSortLst()->GetData();
//STRIP001  for( ; nLast; --nLast, ++ppSortLst )
//STRIP001  {
//STRIP001      const SwTxtFld* pTxtFld = (*ppSortLst)->GetFld();
//STRIP001      if( !pTxtFld )
//STRIP001          continue;
//STRIP001
//STRIP001      const SwField* pFld = pTxtFld->GetFld().GetFld();
//STRIP001      switch( pFld->GetTyp()->Which() )
//STRIP001      {
//STRIP001      case RES_SETEXPFLD:
//STRIP001          if( GSE_STRING & pFld->GetSubType() )
//STRIP001          {
//STRIP001              // setze in der HashTabelle den neuen Wert
//STRIP001              // ist die "Formel" ein Feld ??
//STRIP001              SwSetExpField* pSFld = (SwSetExpField*)pFld;
//STRIP001              LookString( ppHashTbl, rTblSize, pSFld->GetFormula(), aNew );
//STRIP001
//STRIP001                          if( !aNew.Len() )               // nichts gefunden, dann ist
//STRIP001                     aNew = pSFld->GetFormula(); // die Formel der neue Wert
//STRIP001
//STRIP001                 // OD 11.02.2003 #i3141# - update expression of field as in
//STRIP001                 // method <SwDoc::UpdateExpFlds(..)> for string/text fields
//STRIP001                 pSFld->ChgExpStr( aNew );
//STRIP001
//STRIP001              // suche den Namen vom Feld
//STRIP001              aNew = ((SwSetExpFieldType*)pSFld->GetTyp())->GetSetRefName();
//STRIP001              // Eintrag vorhanden ?
//STRIP001              pFnd = Find( aNew, ppHashTbl, rTblSize, &nPos );
//STRIP001              if( pFnd )
//STRIP001                  // Eintrag in der HashTabelle aendern
//STRIP001                  ((_HashStr*)pFnd)->aSetStr = pSFld->GetExpStr();
//STRIP001              else
//STRIP001                  // neuen Eintrag einfuegen
//STRIP001                  *(ppHashTbl + nPos ) = new _HashStr( aNew,
//STRIP001                          pSFld->GetExpStr(), (_HashStr*)*(ppHashTbl + nPos) );
//STRIP001          }
//STRIP001          break;
//STRIP001      case RES_DBFLD:
//STRIP001          {
//STRIP001              const String& rName = pFld->GetTyp()->GetName();
//STRIP001
//STRIP001              // Eintrag in den HashTable eintragen
//STRIP001              // Eintrag vorhanden ?
//STRIP001              pFnd = Find( rName, ppHashTbl, rTblSize, &nPos );
//STRIP001              if( pFnd )
//STRIP001                  // Eintrag in der HashTabelle aendern
//STRIP001                  ((_HashStr*)pFnd)->aSetStr = pFld->Expand();
//STRIP001              else
//STRIP001                  // neuen Eintrag einfuegen
//STRIP001                  *(ppHashTbl + nPos ) = new _HashStr( rName,
//STRIP001                              pFld->Expand(), (_HashStr*)*(ppHashTbl + nPos));
//STRIP001          }
//STRIP001          break;
//STRIP001      }
//STRIP001  }
//STRIP001 }


/*N*/ void SwDoc::UpdateExpFlds( SwTxtFld* pUpdtFld, BOOL bUpdRefFlds )
/*N*/ {
/*N*/     if( IsExpFldsLocked() || IsInReading() )
/*N*/       return;
/*N*/
/*N*/   BOOL bOldInUpdateFlds = pUpdtFlds->IsInUpdateFlds();
/*N*/   pUpdtFlds->SetInUpdateFlds( TRUE );
/*N*/
/*N*/   pUpdtFlds->MakeFldList( *this, TRUE, GETFLD_ALL );
/*N*/   bNewFldLst = FALSE;
/*N*/
/*N*/   if( !pUpdtFlds->GetSortLst()->Count() )
/*N*/   {
/*N*/       if( bUpdRefFlds )
/*N*/           UpdateRefFlds();
/*N*/
/*N*/       pUpdtFlds->SetInUpdateFlds( bOldInUpdateFlds );
/*N*/       pUpdtFlds->SetFieldsDirty( FALSE );
/*N*/       return ;
/*N*/   }
/*N*/
/*N*/   USHORT nWhich, n;
/*N*/
/*N*/   // HashTabelle fuer alle String Ersetzungen, wird "one the fly" gefuellt
/*N*/   // (versuche eine "ungerade"-Zahl zu erzeugen)
/*N*/   USHORT nStrFmtCnt = (( pFldTypes->Count() / 7 ) + 1 ) * 7;
/*N*/   SwHash** pHashStrTbl = new SwHash*[ nStrFmtCnt ];
/*N*/   memset( pHashStrTbl, 0, sizeof( _HashStr* ) * nStrFmtCnt );
/*N*/
/*N*/   {
/*N*/       const SwFieldType* pFldType;
/*N*/       // gesondert behandeln:
/*N*/       for( n = pFldTypes->Count(); n; )
/*N*/           switch( ( pFldType = (*pFldTypes)[ --n ] )->Which() )
/*N*/           {
/*N*/           case RES_USERFLD:
/*N*/               {
/*N*/                   // Eintrag vorhanden ?
/*N*/                   USHORT nPos;
/*N*/                   const String& rNm = pFldType->GetName();
/*N*/                   String sExpand(((SwUserFieldType*)pFldType)->Expand(GSE_STRING, 0, 0));
/*N*/                   SwHash* pFnd = Find( rNm, pHashStrTbl, nStrFmtCnt, &nPos );
/*N*/                   if( pFnd )
/*N*/                       // Eintrag in der HashTabelle aendern ??
/*?*/                       ((_HashStr*)pFnd)->aSetStr = sExpand;
/*N*/                   else
/*N*/                       // neuen Eintrag einfuegen
/*N*/                       *(pHashStrTbl + nPos ) = new _HashStr( rNm, sExpand,
/*N*/                                               (_HashStr*)*(pHashStrTbl + nPos) );
/*N*/               }
/*N*/               break;
/*N*/           case RES_SETEXPFLD:
/*N*/               ((SwSetExpFieldType*)pFldType)->SetOutlineChgNd( 0 );
/*N*/               break;
/*N*/           }
/*N*/   }
/*N*/
/*N*/   // Ok, das Array ist soweit mit allen Feldern gefuellt, dann rechne mal
/*N*/   SwCalc aCalc( *this );
/*N*/
/*N*/   String sDBNumNm( SwFieldType::GetTypeStr( TYP_DBSETNUMBERFLD ) );
/*N*/
/*N*/   // aktuelle Datensatznummer schon vorher einstellen
/*N*/   SwNewDBMgr* pMgr = GetNewDBMgr();
/*N*/   pMgr->CloseAll(FALSE);
/*
     if(pMgr && pMgr->OpenDB(DBMGR_STD, GetDBDesc(), FALSE))
     {
         if(!pMgr->IsInMerge() )
             pMgr->ToFirstSelectedRecord(DBMGR_STD);

         aCalc.VarChange( sDBNumNm, pMgr->GetCurSelectedRecordId(DBMGR_STD));
     }
 */
/*N*/
/*N*/   String aNew;
/*N*/   const _SetGetExpFldPtr* ppSortLst = pUpdtFlds->GetSortLst()->GetData();
/*N*/   for( n = pUpdtFlds->GetSortLst()->Count(); n; --n, ++ppSortLst )
/*N*/   {
/*N*/       SwSection* pSect = (SwSection*)(*ppSortLst)->GetSection();
/*N*/       if( pSect )
/*N*/       {
/*N*/           //!SECTION
/*N*/
/*N*/ //            if( pGFld->IsInBodyTxt() )
/*N*/               pSect->SetCondHidden( aCalc.Calculate(
/*N*/                                       pSect->GetCondition() ).GetBool() );
/*N*/           continue;
/*N*/       }
/*N*/
/*N*/       SwTxtFld* pTxtFld = (SwTxtFld*)(*ppSortLst)->GetFld();
/*N*/       if( !pTxtFld )
/*N*/       {
/*N*/           ASSERT( !this, "was ist es denn nun" );
/*N*/           continue;
/*N*/       }
/*N*/
/*N*/       SwFmtFld* pFmtFld = (SwFmtFld*)&pTxtFld->GetFld();
/*N*/       SwField* pFld = pFmtFld->GetFld();
/*N*/
/*N*/       switch( nWhich = pFld->GetTyp()->Which() )
/*N*/       {
/*N*/       case RES_HIDDENTXTFLD:
/*N*/       {
/*?*/           SwHiddenTxtField* pHFld = (SwHiddenTxtField*)pFld;
/*?*/           pHFld->SetValue( !aCalc.Calculate( pHFld->GetPar1() ).GetBool());
/*?*/           // Feld Evaluieren
/*?*/           pHFld->Evaluate(this);
/*N*/       }
/*N*/       break;
/*N*/       case RES_HIDDENPARAFLD:
/*N*/       {
/*?*/           SwHiddenParaField* pHPFld = (SwHiddenParaField*)pFld;
/*?*/           pHPFld->SetHidden( aCalc.Calculate( pHPFld->GetPar1() ).GetBool());
/*N*/       }
/*N*/       break;
/*N*/       case RES_DBSETNUMBERFLD:
/*N*/       {
/*?*/           ((SwDBSetNumberField*)pFld)->Evaluate(this);
/*?*/           aCalc.VarChange( sDBNumNm, ((SwDBSetNumberField*)pFld)->GetSetNumber());
/*N*/       }
/*N*/       break;
/*N*/       case RES_DBNEXTSETFLD:
/*N*/       case RES_DBNUMSETFLD:
/*N*/           UpdateDBNumFlds( *(SwDBNameInfField*)pFld, aCalc );
/*N*/       break;
/*N*/       case RES_DBFLD:
/*N*/       {
/*N*/           // Feld Evaluieren
/*N*/           ((SwDBField*)pFld)->Evaluate();
/*N*/
/*N*/               SwDBData aDBData(((SwDBField*)pFld)->GetDBData());
/*N*/
/*N*/             if( pMgr->IsDataSourceOpen(aDBData.sDataSource, aDBData.sCommand, sal_False))
/*?*/                 {DBG_BF_ASSERT(0, "STRIP"); }//STRIP001 aCalc.VarChange( sDBNumNm, pMgr->GetSelectedRecordId(aDBData.sDataSource, aDBData.sCommand, aDBData.nCommandType));
/*N*/
/*N*/           const String& rName = pFld->GetTyp()->GetName();
/*N*/
/*N*/           // Wert fuer den Calculator setzen
/*N*/ //JP 10.02.96: GetValue macht hier doch keinen Sinn
/*N*/ //            ((SwDBField*)pFld)->GetValue();
/*N*/
/*N*/ //!OK         aCalc.VarChange(aName, ((SwDBField*)pFld)->GetValue(aCalc));
/*N*/
/*N*/           // Eintrag in den HashTable eintragen
/*N*/           // Eintrag vorhanden ?
/*N*/           USHORT nPos;
/*N*/           SwHash* pFnd = Find( rName, pHashStrTbl, nStrFmtCnt, &nPos );
/*N*/           if( pFnd )
/*N*/               // Eintrag in der HashTabelle aendern
/*?*/               ((_HashStr*)pFnd)->aSetStr = pFld->Expand();
/*N*/           else
/*N*/               // neuen Eintrag einfuegen
/*N*/               *(pHashStrTbl + nPos ) = new _HashStr( rName,
/*N*/                           pFld->Expand(), (_HashStr*)*(pHashStrTbl + nPos));
/*N*/       }
/*N*/       break;
/*N*/       case RES_GETEXPFLD:
/*N*/       case RES_SETEXPFLD:
/*N*/       {
/*N*/           if( GSE_STRING & pFld->GetSubType() )       // String Ersetzung
/*?*/           {
/*?*/               if( RES_GETEXPFLD == nWhich )
/*?*/               {
/*?*/                   SwGetExpField* pGFld = (SwGetExpField*)pFld;
/*?*/
/*?*/                   if( (!pUpdtFld || pUpdtFld == pTxtFld )
/*?*/                       && pGFld->IsInBodyTxt() )
/*?*/                   {
/*?*/                       LookString( pHashStrTbl, nStrFmtCnt,
/*?*/                                   pGFld->GetFormula(), aNew );
/*?*/                       pGFld->ChgExpStr( aNew );
/*?*/                   }
/*?*/               }
/*?*/               else
/*?*/               {
/*?*/                   SwSetExpField* pSFld = (SwSetExpField*)pFld;
/*?*/                   // ist die "Formel" ein Feld ??
/*?*/                   LookString( pHashStrTbl, nStrFmtCnt,
/*?*/                               pSFld->GetFormula(), aNew );
/*?*/
/*?*/                   if( !aNew.Len() )               // nichts gefunden, dann ist die
/*?*/                       aNew = pSFld->GetFormula();     // Formel der neue Wert
/*?*/
/*?*/                   // nur ein spezielles FeldUpdaten ?
/*?*/                   if( !pUpdtFld || pUpdtFld == pTxtFld )
/*?*/                       pSFld->ChgExpStr( aNew );
/*?*/
/*?*/                   // suche den Namen vom Feld
/*?*/                   aNew = ((SwSetExpFieldType*)pSFld->GetTyp())->GetSetRefName();
/*?*/                   // Eintrag vorhanden ?
/*?*/                   USHORT nPos;
/*?*/                   SwHash* pFnd = Find( aNew, pHashStrTbl, nStrFmtCnt, &nPos );
/*?*/                   if( pFnd )
/*?*/                       // Eintrag in der HashTabelle aendern
/*?*/                       ((_HashStr*)pFnd)->aSetStr = pSFld->GetExpStr();
/*?*/                   else
/*?*/                       // neuen Eintrag einfuegen
/*?*/                       *(pHashStrTbl + nPos ) = pFnd = new _HashStr( aNew,
/*?*/                                       pSFld->GetExpStr(),
/*?*/                                       (_HashStr*)*(pHashStrTbl + nPos) );
/*?*/
/*?*/                   // Erweiterung fuers Rechnen mit Strings
/*?*/                   SwSbxValue aValue;
/*?*/                   aValue.PutString( ((_HashStr*)pFnd)->aSetStr );
/*?*/                   aCalc.VarChange( aNew, aValue );
/*?*/               }
/*?*/           }
/*N*/           else            // Formel neu berechnen
/*N*/           {
/*N*/               if( RES_GETEXPFLD == nWhich )
/*N*/               {
/*?*/                   SwGetExpField* pGFld = (SwGetExpField*)pFld;
/*?*/
/*?*/                   if( (!pUpdtFld || pUpdtFld == pTxtFld )
/*?*/                       && pGFld->IsInBodyTxt() )
/*?*/                   {
/*?*/                       pGFld->SetValue(aCalc.Calculate(
/*?*/                                       pGFld->GetFormula() ).GetDouble() );
/*?*/                   }
/*?*/               }
/*N*/               else
/*N*/               {
/*N*/                   SwSetExpField* pSFld = (SwSetExpField*)pFld;
/*N*/                   SwSetExpFieldType* pSFldTyp = (SwSetExpFieldType*)pFld->GetTyp();
/*N*/                   aNew = pSFldTyp->GetName();
/*N*/
/*N*/                   SwNode* pSeqNd = 0;
/*N*/
/*N*/                   if( pSFld->IsSequenceFld() )
/*N*/                   {
/*N*/                       BYTE nLvl = pSFldTyp->GetOutlineLvl();
/*N*/                       if( MAXLEVEL > nLvl )
/*N*/                       {
/*N*/                           DBG_BF_ASSERT(0, "STRIP"); //STRIP001 // dann teste, ob die Nummer neu aufsetzen muss
//STRIP001 /*?*/                            pSeqNd = GetNodes()[ (*ppSortLst)->GetNode() ];
//STRIP001 /*?*/
//STRIP001 /*?*/                            const SwTxtNode* pOutlNd = pSeqNd->
//STRIP001 /*?*/                                    FindOutlineNodeOfLevel( nLvl );
//STRIP001 /*?*/                            if( pSFldTyp->GetOutlineChgNd() != pOutlNd )
//STRIP001 /*?*/                            {
//STRIP001 /*?*/                                pSFldTyp->SetOutlineChgNd( pOutlNd );
//STRIP001 /*?*/                                aCalc.VarChange( aNew, 0 );
//STRIP001 /*?*/                            }
/*?*/                       }
/*N*/                   }
/*N*/
/*N*/                   aNew += '=';
/*N*/                   aNew += pSFld->GetFormula();
/*N*/
/*N*/                   double nErg = aCalc.Calculate( aNew ).GetDouble();
/*N*/                   // nur ein spezielles Feld updaten ?
/*N*/                   if( !pUpdtFld || pUpdtFld == pTxtFld )
/*N*/                   {
/*N*/                       pSFld->SetValue( nErg );
/*N*/
/*N*/                       if( pSeqNd )
/*?*/                       {DBG_BF_ASSERT(0, "STRIP"); }//STRIP001     pSFldTyp->SetChapter( *pSFld, *pSeqNd );
/*N*/                   }
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/       } // switch
/*N*/
/*N*/       pFmtFld->Modify( 0, 0 );        // Formatierung anstossen
/*N*/
/*N*/       if( pUpdtFld == pTxtFld )       // sollte nur dieses geupdatet werden
/*N*/       {
/*?*/           if( RES_GETEXPFLD == nWhich ||      // nur GetFeld oder
/*?*/               RES_HIDDENTXTFLD == nWhich ||   // HiddenTxt?
/*?*/               RES_HIDDENPARAFLD == nWhich)    // HiddenParaFld?
/*?*/               break;                          // beenden
/*?*/           pUpdtFld = 0;                       // ab jetzt alle Updaten
/*N*/       }
/*N*/   }
/*N*/
/*N*/   pMgr->CloseAll(FALSE);
/*N*/   // HashTabelle wieder loeschen
/*N*/   ::binfilter::DeleteHashTable( pHashStrTbl, nStrFmtCnt );
/*N*/
/*N*/   // Referenzfelder updaten
/*N*/   if( bUpdRefFlds )
/*?*/       UpdateRefFlds();
/*N*/
/*N*/   pUpdtFlds->SetInUpdateFlds( bOldInUpdateFlds );
/*N*/   pUpdtFlds->SetFieldsDirty( FALSE );
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung:
 --------------------------------------------------------------------*/

/*N*/ void SwDoc::UpdateDBNumFlds( SwDBNameInfField& rDBFld, SwCalc& rCalc )
/*N*/ {
/*N*/   SwNewDBMgr* pMgr = GetNewDBMgr();
/*?*/
/*?*/   USHORT nFldType = rDBFld.Which();
/*?*/
/*?*/   BOOL bPar1 = rCalc.Calculate( rDBFld.GetPar1() ).GetBool();
/*?*/
/*?*/   if( RES_DBNEXTSETFLD == nFldType )
/*?*/       ((SwDBNextSetField&)rDBFld).SetCondValid( bPar1 );
/*?*/   else
/*?*/       ((SwDBNumSetField&)rDBFld).SetCondValid( bPar1 );
/*?*/
/*?*/   if( rDBFld.GetRealDBData().sDataSource.getLength() )
/*?*/   {
/*?*/       // Eine bestimmte Datenbank bearbeiten
/*?*/       if( RES_DBNEXTSETFLD == nFldType )
/*?*/           ((SwDBNextSetField&)rDBFld).Evaluate(this);
/*?*/       else
/*?*/           ((SwDBNumSetField&)rDBFld).Evaluate(this);
/*?*/
/*?*/       SwDBData aDBData( rDBFld.GetDBData(this) );
/*?*/
/*?*/       if( pMgr->OpenDataSource( aDBData.sDataSource, aDBData.sCommand ))
/*?*/           rCalc.VarChange( lcl_GetDBVarName( *this, rDBFld),
/*?*/                         pMgr->GetSelectedRecordId(aDBData.sDataSource, aDBData.sCommand, aDBData.nCommandType) );
/*?*/   }
/*?*/   else
/*?*/   {
/*?*/       DBG_ERROR("TODO: what should happen with unnamed DBFields?")
/*?*/   }
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung:
 --------------------------------------------------------------------*/

/*N*/ void SwDoc::_InitFieldTypes()     // wird vom CTOR gerufen!!
/*N*/ {
/*N*/   // Feldtypen
/*N*/   USHORT nFldType = 0;
/*N*/   pFldTypes->Insert( new SwDateTimeFieldType(this), nFldType++ );
/*N*/   pFldTypes->Insert( new SwChapterFieldType, nFldType++ );
/*N*/   pFldTypes->Insert( new SwPageNumberFieldType, nFldType++ );
/*N*/   pFldTypes->Insert( new SwAuthorFieldType, nFldType++ );
/*N*/   pFldTypes->Insert( new SwFileNameFieldType(this), nFldType++ );
/*N*/   pFldTypes->Insert( new SwDBNameFieldType(this), nFldType++);
/*N*/   pFldTypes->Insert( new SwGetExpFieldType(this), nFldType++ );
/*N*/   pFldTypes->Insert( new SwGetRefFieldType( this ), nFldType++ );
/*N*/   pFldTypes->Insert( new SwHiddenTxtFieldType, nFldType++ );
/*N*/   pFldTypes->Insert( new SwPostItFieldType, nFldType++ );
/*N*/   pFldTypes->Insert( new SwDocStatFieldType(this), nFldType++);
/*N*/   pFldTypes->Insert( new SwDocInfoFieldType(this), nFldType++);
/*N*/   pFldTypes->Insert( new SwInputFieldType( this ), nFldType++ );
/*N*/   pFldTypes->Insert( new SwTblFieldType( this ), nFldType++);
/*N*/   pFldTypes->Insert( new SwMacroFieldType(this), nFldType++ );
/*N*/   pFldTypes->Insert( new SwHiddenParaFieldType, nFldType++ );
/*N*/   pFldTypes->Insert( new SwDBNextSetFieldType, nFldType++ );
/*N*/   pFldTypes->Insert( new SwDBNumSetFieldType, nFldType++ );
/*N*/   pFldTypes->Insert( new SwDBSetNumberFieldType, nFldType++ );
/*N*/   pFldTypes->Insert( new SwTemplNameFieldType(this), nFldType++);
/*N*/   pFldTypes->Insert( new SwTemplNameFieldType(this),nFldType++);
/*N*/   pFldTypes->Insert( new SwExtUserFieldType, nFldType++ );
/*N*/   pFldTypes->Insert( new SwRefPageSetFieldType, nFldType++ );
/*N*/   pFldTypes->Insert( new SwRefPageGetFieldType( this ), nFldType++ );
/*N*/   pFldTypes->Insert( new SwJumpEditFieldType( this ), nFldType++ );
/*N*/   pFldTypes->Insert( new SwScriptFieldType( this ), nFldType++ );
/*N*/   pFldTypes->Insert( new SwCombinedCharFieldType, nFldType++ );
/*N*/   pFldTypes->Insert( new SwDropDownFieldType, nFldType++ );
/*N*/
/*N*/   // Types muessen am Ende stehen !!
/*N*/   // Im InsertFldType wird davon ausgegangen !!!!
/*N*/   // MIB 14.04.95: Im Sw3StringPool::Setup (sw3imp.cxx) und
/*N*/   //               lcl_sw3io_InSetExpField (sw3field.cxx) jetzt auch
/*N*/   pFldTypes->Insert( new SwSetExpFieldType(this,
/*N*/               SW_RESSTR(STR_POOLCOLL_LABEL_ABB), GSE_SEQ), nFldType++);
/*N*/   pFldTypes->Insert( new SwSetExpFieldType(this,
/*N*/               SW_RESSTR(STR_POOLCOLL_LABEL_TABLE), GSE_SEQ),nFldType++);
/*N*/   pFldTypes->Insert( new SwSetExpFieldType(this,
/*N*/               SW_RESSTR(STR_POOLCOLL_LABEL_FRAME), GSE_SEQ),nFldType++);
/*N*/   pFldTypes->Insert( new SwSetExpFieldType(this,
/*N*/               SW_RESSTR(STR_POOLCOLL_LABEL_DRAWING), GSE_SEQ),nFldType++);
/*N*/
/*N*/   ASSERT( nFldType == INIT_FLDTYPES, "Bad initsize: SwFldTypes" );
/*N*/ }

/*N*/ void SwDoc::InsDelFldInFldLst( BOOL bIns, const SwTxtFld& rFld )
/*N*/ {
/*N*/   if( !bNewFldLst || !IsInDtor() )
/*N*/       pUpdtFlds->InsDelFldInFldLst( bIns, rFld );
/*N*/ }

/*N*/ SwDBData SwDoc::GetDBData()
/*N*/ {
/*N*/   return GetDBDesc();
/*N*/ }

/*N*/ const SwDBData& SwDoc::GetDBDesc()
/*N*/ {
/*N*/       if(!aDBData.sDataSource.getLength())
/*N*/     {
/*N*/         const USHORT nSize = pFldTypes->Count();
/*N*/         for(USHORT i = 0; i < nSize && !aDBData.sDataSource.getLength(); ++i)
/*N*/         {
/*N*/             SwFieldType& rFldType = *((*pFldTypes)[i]);
/*N*/             USHORT nWhich = rFldType.Which();
/*N*/             if(IsUsed(rFldType))
/*N*/             {
/*N*/                 switch(nWhich)
/*N*/                 {
/*N*/                     case RES_DBFLD:
/*N*/                     case RES_DBNEXTSETFLD:
/*N*/                     case RES_DBNUMSETFLD:
/*N*/                     case RES_DBSETNUMBERFLD:
/*N*/                     {
/*N*/                         SwClientIter aIter( rFldType );
/*N*/                         SwFmtFld* pFld = (SwFmtFld*)aIter.First( TYPE( SwFmtFld ));
/*N*/                         while(pFld)
/*N*/                         {
/*N*/                             if(pFld->IsFldInDoc())
/*N*/                             {
/*N*/                                 if(RES_DBFLD == nWhich)
/*N*/                                     aDBData =
/*N*/                                         (static_cast < SwDBFieldType * > (pFld->GetFld()->GetTyp()))
/*N*/                                             ->GetDBData();
/*N*/                                 else
/*N*/                                     aDBData = (static_cast < SwDBNameInfField* > (pFld->GetFld()))->GetRealDBData();
/*N*/                                 break;
/*N*/                             }
/*N*/                             pFld = (SwFmtFld*)aIter.Next();
/*N*/                         }
/*N*/                     }
/*N*/                     break;
/*N*/                 }
/*N*/             }
/*N*/         }
/*N*/     }
/*N*/     if(!aDBData.sDataSource.getLength())
/*N*/       aDBData = GetNewDBMgr()->GetAddressDBName();
/*N*/   return aDBData;
/*N*/ }

/*N*/ void SwDoc::SetInitDBFields( BOOL b )
/*N*/ {
/*N*/   GetNewDBMgr()->SetInitDBFields( b );
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung: Alle von Feldern verwendete Datenbanken herausfinden
 --------------------------------------------------------------------*/
/*N*/ String lcl_DBDataToString(const SwDBData& rData)
/*N*/ {
/*N*/   String sRet = rData.sDataSource;
/*N*/   sRet += DB_DELIM;
/*N*/   sRet += (String)rData.sCommand;
/*N*/   sRet += DB_DELIM;
/*N*/   sRet += String::CreateFromInt32(rData.nCommandType);
/*N*/   return sRet;
/*N*/ }
/*N*/ void SwDoc::GetAllUsedDB( SvStringsDtor& rDBNameList,
/*N*/                           const SvStringsDtor* pAllDBNames )
/*N*/ {
/*N*/   USHORT n;
/*N*/   SvStringsDtor aUsedDBNames;
/*N*/   SvStringsDtor aAllDBNames;
/*N*/
/*N*/   if( !pAllDBNames )
/*N*/   {
/*N*/       GetAllDBNames( aAllDBNames );
/*N*/       pAllDBNames = &aAllDBNames;
/*N*/   }
/*N*/
/*N*/   SwSectionFmts& rArr = GetSections();
/*N*/   for( n = rArr.Count(); n; )
/*N*/   {
/*N*/       SwSection* pSect = rArr[ --n ]->GetSection();
/*N*/
/*N*/       if( pSect )
/*N*/       {
/*N*/           String aCond( pSect->GetCondition() );
/*N*/           AddUsedDBToList( rDBNameList, FindUsedDBs( *pAllDBNames,
/*N*/                                               aCond, aUsedDBNames ) );
/*N*/           aUsedDBNames.DeleteAndDestroy( 0, aUsedDBNames.Count() );
/*N*/       }
/*N*/   }
/*N*/
/*N*/   const SfxPoolItem* pItem;
/*N*/   USHORT nMaxItems = GetAttrPool().GetItemCount( RES_TXTATR_FIELD );
/*N*/   for( n = 0; n < nMaxItems; ++n )
/*N*/   {
/*N*/       if( 0 == (pItem = GetAttrPool().GetItem( RES_TXTATR_FIELD, n ) ))
/*N*/           continue;
/*N*/
/*N*/       const SwFmtFld* pFmtFld = (SwFmtFld*)pItem;
/*N*/       const SwTxtFld* pTxtFld = pFmtFld->GetTxtFld();
/*N*/       if( !pTxtFld || !pTxtFld->GetTxtNode().GetNodes().IsDocNodes() )
/*N*/           continue;
/*N*/
/*N*/       const SwField* pFld = pFmtFld->GetFld();
/*N*/       switch( pFld->GetTyp()->Which() )
/*N*/       {
/*N*/           case RES_DBFLD:
/*N*/               AddUsedDBToList( rDBNameList,
/*N*/                               lcl_DBDataToString(((SwDBField*)pFld)->GetDBData() ));
/*N*/               break;
/*N*/
/*N*/           case RES_DBSETNUMBERFLD:
/*N*/           case RES_DBNAMEFLD:
/*N*/               AddUsedDBToList( rDBNameList,
/*N*/                               lcl_DBDataToString(((SwDBNameInfField*)pFld)->GetRealDBData() ));
/*N*/               break;
/*N*/
/*N*/           case RES_DBNUMSETFLD:
/*N*/           case RES_DBNEXTSETFLD:
/*N*/               AddUsedDBToList( rDBNameList,
/*N*/                               lcl_DBDataToString(((SwDBNameInfField*)pFld)->GetRealDBData() ));
/*N*/               // kein break  // JP: ist das so richtig ??
/*N*/
/*N*/           case RES_HIDDENTXTFLD:
/*N*/           case RES_HIDDENPARAFLD:
/*N*/               AddUsedDBToList(rDBNameList, FindUsedDBs( *pAllDBNames,
/*N*/                                           pFld->GetPar1(), aUsedDBNames ));
/*N*/               aUsedDBNames.DeleteAndDestroy( 0, aUsedDBNames.Count() );
/*N*/               break;
/*N*/
/*N*/           case RES_SETEXPFLD:
/*N*/           case RES_GETEXPFLD:
/*N*/           case RES_TABLEFLD:
/*N*/               AddUsedDBToList(rDBNameList, FindUsedDBs( *pAllDBNames,
/*N*/                                       pFld->GetFormula(), aUsedDBNames ));
/*N*/               aUsedDBNames.DeleteAndDestroy( 0, aUsedDBNames.Count() );
/*N*/               break;
/*N*/       }
/*N*/   }
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung:
 --------------------------------------------------------------------*/

/*N*/ void SwDoc::GetAllDBNames( SvStringsDtor& rAllDBNames )
/*N*/ {
/*N*/   SwNewDBMgr* pMgr = GetNewDBMgr();
/*N*/
/*N*/   const SwDSParamArr& rArr = pMgr->GetDSParamArray();
/*N*/   for(USHORT i = 0; i < rArr.Count(); i++)
/*N*/   {
/*N*/       SwDSParam* pParam = rArr[i];
/*N*/       String* pStr = new String( pParam->sDataSource );
/*N*/       (*pStr) += DB_DELIM;
/*N*/         (*pStr) += (String)pParam->sCommand;
/*N*/       rAllDBNames.Insert( pStr, rAllDBNames.Count() );
/*N*/   }
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung:
 --------------------------------------------------------------------*/

/*N*/ SvStringsDtor& SwDoc::FindUsedDBs( const SvStringsDtor& rAllDBNames,
/*N*/                                   const String& rFormel,
/*N*/                                   SvStringsDtor& rUsedDBNames )
/*N*/ {
/*N*/   const CharClass& rCC = GetAppCharClass();
/*N*/   String  sFormel( rFormel);
/*N*/ #ifndef UNX
/*N*/   rCC.toUpper( sFormel );
/*N*/ #endif
/*N*/
/*N*/   xub_StrLen nPos;
/*N*/   for (USHORT i = 0; i < rAllDBNames.Count(); ++i )
/*N*/   {
/*N*/       const String* pStr = rAllDBNames.GetObject(i);
/*N*/
/*N*/       if( STRING_NOTFOUND != (nPos = sFormel.Search( *pStr )) &&
/*N*/           sFormel.GetChar( nPos + pStr->Len() ) == '.' &&
/*N*/           (!nPos || !rCC.isLetterNumeric( sFormel, nPos - 1 )))
/*N*/       {
/*N*/           // Tabellenname suchen
/*?*/           xub_StrLen nEndPos;
/*?*/           nPos += pStr->Len() + 1;
/*?*/           if( STRING_NOTFOUND != (nEndPos = sFormel.Search('.', nPos)) )
/*?*/           {
/*?*/               String* pDBNm = new String( *pStr );
/*?*/               pDBNm->Append( DB_DELIM );
/*?*/               pDBNm->Append( sFormel.Copy( nPos, nEndPos - nPos ));
/*?*/               rUsedDBNames.Insert( pDBNm, rUsedDBNames.Count() );
/*?*/           }
/*?*/       }
/*N*/   }
/*N*/   return rUsedDBNames;
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung:
 --------------------------------------------------------------------*/

/*N*/ void SwDoc::AddUsedDBToList( SvStringsDtor& rDBNameList,
/*N*/                            const SvStringsDtor& rUsedDBNames )
/*N*/ {
/*N*/   for (USHORT i = 0; i < rUsedDBNames.Count(); i++)
/*?*/       AddUsedDBToList( rDBNameList, *rUsedDBNames.GetObject(i) );
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung:
 --------------------------------------------------------------------*/

/*N*/ void SwDoc::AddUsedDBToList( SvStringsDtor& rDBNameList, const String& rDBName)
/*N*/ {
/*N*/   if( !rDBName.Len() )
/*N*/       return;
/*N*/
/*N*/ #ifdef UNX
/*N*/   for( USHORT i = 0; i < rDBNameList.Count(); ++i )
/*N*/       if( rDBName == rDBNameList.GetObject(i)->GetToken(0) )
/*N*/           return;
/*N*/ #else
/*N*/   const ::utl::TransliterationWrapper& rSCmp = GetAppCmpStrIgnore();
/*N*/   for( USHORT i = 0; i < rDBNameList.Count(); ++i )
/*N*/       if( rSCmp.isEqual( rDBName, rDBNameList.GetObject(i)->GetToken(0) ) )
/*N*/           return;
/*N*/ #endif
/*N*/
/*N*/     SwDBData aData;
/*N*/     aData.sDataSource = rDBName.GetToken(0, DB_DELIM);
/*N*/     aData.sCommand = rDBName.GetToken(1, DB_DELIM);
/*N*/     aData.nCommandType = -1;
/*N*/     const SwDSParam* pParam = GetNewDBMgr()->CreateDSData(aData);
/*N*/   String* pNew = new String( rDBName );
/*N*/   rDBNameList.Insert( pNew, rDBNameList.Count() );
/*N*/ }

/*--------------------------------------------------------------------
     Beschreibung:
 --------------------------------------------------------------------*/

//STRIP001 BOOL SwDoc::RenameUserFields( const String& rOldName, const String& rNewName )
//STRIP001 {
//STRIP001  USHORT n;
//STRIP001  BOOL bRet = FALSE;
//STRIP001  String sFormel;
//STRIP001
//STRIP001  SwSectionFmts& rArr = GetSections();
//STRIP001  for( n = rArr.Count(); n; )
//STRIP001  {
//STRIP001      SwSection* pSect = rArr[ --n ]->GetSection();
//STRIP001
//STRIP001      if( pSect )
//STRIP001      {
//STRIP001          sFormel = pSect->GetCondition();
//STRIP001          RenameUserFld( rOldName, rNewName, sFormel );
//STRIP001          pSect->SetCondition( sFormel );
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  const SfxPoolItem* pItem;
//STRIP001  USHORT nMaxItems = GetAttrPool().GetItemCount( RES_TXTATR_FIELD );
//STRIP001  const ::utl::TransliterationWrapper& rSCmp = GetAppCmpStrIgnore();
//STRIP001
//STRIP001  for( n = 0; n < nMaxItems; ++n )
//STRIP001  {
//STRIP001      if( 0 == (pItem = GetAttrPool().GetItem( RES_TXTATR_FIELD, n ) ))
//STRIP001          continue;
//STRIP001
//STRIP001      SwFmtFld* pFmtFld = (SwFmtFld*)pItem;
//STRIP001      SwTxtFld* pTxtFld = pFmtFld->GetTxtFld();
//STRIP001      if( !pTxtFld || !pTxtFld->GetTxtNode().GetNodes().IsDocNodes() )
//STRIP001          continue;
//STRIP001
//STRIP001      SwField* pFld = pFmtFld->GetFld();
//STRIP001      BOOL bExpand = FALSE;
//STRIP001
//STRIP001      switch( pFld->GetTyp()->Which() )
//STRIP001      {
//STRIP001      case RES_USERFLD:
//STRIP001          if( rSCmp.isEqual( rOldName, pFld->GetTyp()->GetName() ))
//STRIP001          {
//STRIP001              SwUserFieldType* pOldTyp = (SwUserFieldType*)pFld->GetTyp();
//STRIP001
//STRIP001              SwUserFieldType* pTyp = (SwUserFieldType*)InsertFldType(
//STRIP001                      SwUserFieldType(this, rNewName));
//STRIP001
//STRIP001              pTyp->SetContent(pOldTyp->GetContent());
//STRIP001              pTyp->SetType(pOldTyp->GetType());
//STRIP001              pTyp->Add(pFmtFld); // Feld auf neuen Typ umhaengen
//STRIP001              pFld->ChgTyp(pTyp);
//STRIP001
//STRIP001              bExpand = TRUE;
//STRIP001          }
//STRIP001          break;
//STRIP001
//STRIP001      case RES_DBNUMSETFLD:
//STRIP001      case RES_DBNEXTSETFLD:
//STRIP001      case RES_HIDDENTXTFLD:
//STRIP001      case RES_HIDDENPARAFLD:
//STRIP001          sFormel = pFld->GetPar1();
//STRIP001          RenameUserFld( rOldName, rNewName, sFormel );
//STRIP001          pFld->SetPar1( sFormel );
//STRIP001          bExpand = TRUE;
//STRIP001          break;
//STRIP001
//STRIP001      case RES_SETEXPFLD:
//STRIP001          if( rSCmp.isEqual( rOldName, pFld->GetTyp()->GetName() ))
//STRIP001          {
//STRIP001              SwSetExpFieldType* pOldTyp = (SwSetExpFieldType*)pFld->GetTyp();
//STRIP001
//STRIP001              SwSetExpFieldType* pTyp = (SwSetExpFieldType*)InsertFldType(
//STRIP001                      SwSetExpFieldType(this, rNewName, pOldTyp->GetType()));
//STRIP001              pTyp->Add( pFmtFld );   // Feld auf neuen Typ umhaengen
//STRIP001              pFld->ChgTyp( pTyp );
//STRIP001
//STRIP001              bExpand = TRUE;
//STRIP001          }
//STRIP001          // Kein break!!!
//STRIP001
//STRIP001      case RES_GETEXPFLD:
//STRIP001      case RES_TABLEFLD:
//STRIP001          sFormel = pFld->GetFormula();
//STRIP001          RenameUserFld( rOldName, rNewName, sFormel );
//STRIP001          pFld->SetPar2( sFormel );
//STRIP001          bExpand = TRUE;
//STRIP001          break;
//STRIP001      }
//STRIP001
//STRIP001      if( bExpand )
//STRIP001      {
//STRIP001          pTxtFld->ExpandAlways();
//STRIP001          bRet = TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001  SetModified();
//STRIP001
//STRIP001  return bRet;
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung:
 --------------------------------------------------------------------*/

//STRIP001 void SwDoc::RenameUserFld( const String& rOldName, const String& rNewName,
//STRIP001                          String& rFormel )
//STRIP001 {
//STRIP001  const CharClass& rCC = GetAppCharClass();
//STRIP001
//STRIP001  String  sFormel( rCC.upper( rFormel ));
//STRIP001  String  sOldName( rCC.upper( rOldName ));
//STRIP001  xub_StrLen nPos;
//STRIP001
//STRIP001  if( !::binfilter::FindOperator( rOldName ) &&
//STRIP001      !sOldName.Equals( rCC.upper( rNewName ) ) )
//STRIP001  {
//STRIP001      nPos = 0;
//STRIP001
//STRIP001      while ((nPos = sFormel.Search(sOldName, nPos)) != STRING_NOTFOUND)
//STRIP001      {
//STRIP001          if(!nPos || !rCC.isLetterNumeric( sFormel, nPos - 1 ))
//STRIP001          {
//STRIP001              rFormel.Erase( nPos, rOldName.Len() );
//STRIP001              rFormel.Insert( rNewName, nPos );
//STRIP001              sFormel = rCC.upper( rFormel );
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 }

/*--------------------------------------------------------------------
     Beschreibung:
 --------------------------------------------------------------------*/

//STRIP001 void SwDoc::ChangeDBFields( const SvStringsDtor& rOldNames,
//STRIP001                          const String& rNewName )
//STRIP001 {
//STRIP001  SwDBData aNewDBData;
//STRIP001  aNewDBData.sDataSource = rNewName.GetToken(0, DB_DELIM);
//STRIP001  aNewDBData.sCommand = rNewName.GetToken(1, DB_DELIM);
//STRIP001  aNewDBData.nCommandType = (short)rNewName.GetToken(2, DB_DELIM).ToInt32();
//STRIP001
//STRIP001  String sFormel;
//STRIP001  USHORT n;
//STRIP001
//STRIP001  SwSectionFmts& rArr = GetSections();
//STRIP001  for( n = rArr.Count(); n; )
//STRIP001  {
//STRIP001      SwSection* pSect = rArr[ --n ]->GetSection();
//STRIP001
//STRIP001      if( pSect )
//STRIP001      {
//STRIP001          sFormel = pSect->GetCondition();
//STRIP001          ReplaceUsedDBs( rOldNames, rNewName, sFormel);
//STRIP001          pSect->SetCondition(sFormel);
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  const SfxPoolItem* pItem;
//STRIP001  USHORT nMaxItems = GetAttrPool().GetItemCount( RES_TXTATR_FIELD );
//STRIP001
//STRIP001  for( n = 0; n < nMaxItems; ++n )
//STRIP001  {
//STRIP001      if( 0 == (pItem = GetAttrPool().GetItem( RES_TXTATR_FIELD, n ) ))
//STRIP001          continue;
//STRIP001
//STRIP001      SwFmtFld* pFmtFld = (SwFmtFld*)pItem;
//STRIP001      SwTxtFld* pTxtFld = pFmtFld->GetTxtFld();
//STRIP001      if( !pTxtFld || !pTxtFld->GetTxtNode().GetNodes().IsDocNodes() )
//STRIP001          continue;
//STRIP001
//STRIP001      SwField* pFld = pFmtFld->GetFld();
//STRIP001      BOOL bExpand = FALSE;
//STRIP001
//STRIP001      switch( pFld->GetTyp()->Which() )
//STRIP001      {
//STRIP001          case RES_DBFLD:
//STRIP001              if( IsNameInArray( rOldNames, lcl_DBDataToString(((SwDBField*)pFld)->GetDBData())))
//STRIP001              {
//STRIP001                  SwDBFieldType* pOldTyp = (SwDBFieldType*)pFld->GetTyp();
//STRIP001
//STRIP001                  SwDBFieldType* pTyp = (SwDBFieldType*)InsertFldType(
//STRIP001                          SwDBFieldType(this, pOldTyp->GetColumnName(), aNewDBData));
//STRIP001
//STRIP001                  pTyp->Add(pFmtFld); // Feld auf neuen Typ umhaengen
//STRIP001                  pFld->ChgTyp(pTyp);
//STRIP001
//STRIP001                  ((SwDBField*)pFld)->ClearInitialized();
//STRIP001                  ((SwDBField*)pFld)->InitContent();
//STRIP001
//STRIP001                  bExpand = TRUE;
//STRIP001              }
//STRIP001              break;
//STRIP001
//STRIP001          case RES_DBSETNUMBERFLD:
//STRIP001          case RES_DBNAMEFLD:
//STRIP001              if( IsNameInArray( rOldNames,
//STRIP001                              lcl_DBDataToString(((SwDBNameInfField*)pFld)->GetRealDBData())))
//STRIP001              {
//STRIP001                  ((SwDBNameInfField*)pFld)->SetDBData(aNewDBData);
//STRIP001                  bExpand = TRUE;
//STRIP001              }
//STRIP001              break;
//STRIP001
//STRIP001          case RES_DBNUMSETFLD:
//STRIP001          case RES_DBNEXTSETFLD:
//STRIP001              if( IsNameInArray( rOldNames,
//STRIP001                              lcl_DBDataToString(((SwDBNameInfField*)pFld)->GetRealDBData())))
//STRIP001              {
//STRIP001                  ((SwDBNameInfField*)pFld)->SetDBData(aNewDBData);
//STRIP001                  bExpand = TRUE;
//STRIP001              }
//STRIP001              // kein break;
//STRIP001          case RES_HIDDENTXTFLD:
//STRIP001          case RES_HIDDENPARAFLD:
//STRIP001              sFormel = pFld->GetPar1();
//STRIP001              ReplaceUsedDBs( rOldNames, rNewName, sFormel);
//STRIP001              pFld->SetPar1( sFormel );
//STRIP001              bExpand = TRUE;
//STRIP001              break;
//STRIP001
//STRIP001          case RES_SETEXPFLD:
//STRIP001          case RES_GETEXPFLD:
//STRIP001          case RES_TABLEFLD:
//STRIP001              sFormel = pFld->GetFormula();
//STRIP001              ReplaceUsedDBs( rOldNames, rNewName, sFormel);
//STRIP001              pFld->SetPar2( sFormel );
//STRIP001              bExpand = TRUE;
//STRIP001              break;
//STRIP001      }
//STRIP001
//STRIP001      if (bExpand)
//STRIP001          pTxtFld->ExpandAlways();
//STRIP001  }
//STRIP001  SetModified();
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung:
 --------------------------------------------------------------------*/

//STRIP001 void SwDoc::ReplaceUsedDBs( const SvStringsDtor& rUsedDBNames,
//STRIP001                          const String& rNewName, String& rFormel )
//STRIP001 {
//STRIP001  const CharClass& rCC = GetAppCharClass();
//STRIP001  String  sFormel(rFormel);
//STRIP001  String  sNewName( rNewName );
//STRIP001  sNewName.SearchAndReplace( DB_DELIM, '.');
//STRIP001  //the command type is not part of the condition
//STRIP001  sNewName = sNewName.GetToken(0, DB_DELIM);
//STRIP001  String sUpperNewNm( sNewName );
//STRIP001
//STRIP001
//STRIP001  for( USHORT i = 0; i < rUsedDBNames.Count(); ++i )
//STRIP001  {
//STRIP001      String  sDBName( *rUsedDBNames.GetObject( i ) );
//STRIP001
//STRIP001      sDBName.SearchAndReplace( DB_DELIM, '.');
//STRIP001              //cut off command type
//STRIP001      sDBName = sDBName.GetToken(0, DB_DELIM);
//STRIP001      if( !sDBName.Equals( sUpperNewNm ))
//STRIP001      {
//STRIP001          xub_StrLen nPos = 0;
//STRIP001
//STRIP001          while ((nPos = sFormel.Search(sDBName, nPos)) != STRING_NOTFOUND)
//STRIP001          {
//STRIP001              if( sFormel.GetChar( nPos + sDBName.Len() ) == '.' &&
//STRIP001                  (!nPos || !rCC.isLetterNumeric( sFormel, nPos - 1 )))
//STRIP001              {
//STRIP001                  rFormel.Erase( nPos, sDBName.Len() );
//STRIP001                  rFormel.Insert( sNewName, nPos );
//STRIP001                  //prevent re-searching - this is useless and provokes
//STRIP001                  //endless loops when names containing each other and numbers are exchanged
//STRIP001                  //e.g.: old ´12345.12345  new: i12345.12345
//STRIP001                  nPos += sNewName.Len();
//STRIP001                  sFormel = rFormel;
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 }

/*--------------------------------------------------------------------
     Beschreibung:
 --------------------------------------------------------------------*/

//STRIP001 BOOL SwDoc::IsNameInArray( const SvStringsDtor& rArr, const String& rName )
//STRIP001 {
//STRIP001 #ifdef UNX
//STRIP001  for( USHORT i = 0; i < rArr.Count(); ++i )
//STRIP001      if( rName == *rArr[ i ] )
//STRIP001          return TRUE;
//STRIP001 #else
//STRIP001  const ::utl::TransliterationWrapper& rSCmp = GetAppCmpStrIgnore();
//STRIP001  for( USHORT i = 0; i < rArr.Count(); ++i )
//STRIP001      if( rSCmp.isEqual( rName, *rArr[ i] ))
//STRIP001          return TRUE;
//STRIP001 #endif
//STRIP001  return FALSE;
//STRIP001 }

/*N*/ void SwDoc::SetFixFields( BOOL bOnlyTimeDate, const DateTime* pNewDateTime )
/*N*/ {
DBG_BF_ASSERT(0, "STRIP"); //STRIP001   BOOL bIsModified = IsModified();
//STRIP001
//STRIP001  ULONG nDate, nTime;
//STRIP001  if( pNewDateTime )
//STRIP001  {
//STRIP001      nDate = pNewDateTime->GetDate();
//STRIP001      nTime = pNewDateTime->GetTime();
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      nDate = Date().GetDate();
//STRIP001      nTime = Time().GetTime();
//STRIP001  }
//STRIP001
//STRIP001  USHORT aTypes[5] = {
//STRIP001      /*0*/   RES_DOCINFOFLD,
//STRIP001      /*1*/   RES_AUTHORFLD,
//STRIP001      /*2*/   RES_EXTUSERFLD,
//STRIP001      /*3*/   RES_FILENAMEFLD,
//STRIP001      /*4*/   RES_DATETIMEFLD };  // MUSS am Ende stehen!!
//STRIP001
//STRIP001  USHORT nStt = bOnlyTimeDate ? 4 : 0;
//STRIP001
//STRIP001  for( ; nStt < 5; ++nStt )
//STRIP001  {
//STRIP001      SwFieldType* pFldType = GetSysFldType( aTypes[ nStt ] );
//STRIP001      SwClientIter aDocInfIter( *pFldType );
//STRIP001
//STRIP001      for( SwFmtFld* pFld = (SwFmtFld*)aDocInfIter.First( TYPE( SwFmtFld ));
//STRIP001              pFld; pFld = (SwFmtFld*)aDocInfIter.Next() )
//STRIP001      {
//STRIP001          if( pFld && pFld->GetTxtFld() )
//STRIP001          {
//STRIP001              BOOL bChgd = FALSE;
//STRIP001              switch( aTypes[ nStt ] )
//STRIP001              {
//STRIP001              case RES_DOCINFOFLD:
//STRIP001                  if( ((SwDocInfoField*)pFld->GetFld())->IsFixed() )
//STRIP001                  {
//STRIP001                      bChgd = TRUE;
//STRIP001                      SwDocInfoField* pDocInfFld = (SwDocInfoField*)pFld->GetFld();
//STRIP001                      pDocInfFld->SetExpansion( ((SwDocInfoFieldType*)
//STRIP001                                  pDocInfFld->GetTyp())->Expand(
//STRIP001                                      pDocInfFld->GetSubType(),
//STRIP001                                      pDocInfFld->GetFormat(),
//STRIP001                                      pDocInfFld->GetLanguage() ) );
//STRIP001                  }
//STRIP001                  break;
//STRIP001
//STRIP001              case RES_AUTHORFLD:
//STRIP001                  if( ((SwAuthorField*)pFld->GetFld())->IsFixed() )
//STRIP001                  {
//STRIP001                      bChgd = TRUE;
//STRIP001                      SwAuthorField* pAuthorFld = (SwAuthorField*)pFld->GetFld();
//STRIP001                      pAuthorFld->SetExpansion( ((SwAuthorFieldType*)
//STRIP001                                  pAuthorFld->GetTyp())->Expand(
//STRIP001                                              pAuthorFld->GetFormat() ) );
//STRIP001                  }
//STRIP001                  break;
//STRIP001
//STRIP001              case RES_EXTUSERFLD:
//STRIP001                  if( ((SwExtUserField*)pFld->GetFld())->IsFixed() )
//STRIP001                  {
//STRIP001                      bChgd = TRUE;
//STRIP001                      SwExtUserField* pExtUserFld = (SwExtUserField*)pFld->GetFld();
//STRIP001                      pExtUserFld->SetExpansion( ((SwExtUserFieldType*)
//STRIP001                                  pExtUserFld->GetTyp())->Expand(
//STRIP001                                          pExtUserFld->GetSubType(),
//STRIP001                                          pExtUserFld->GetFormat()));
//STRIP001                  }
//STRIP001                  break;
//STRIP001
//STRIP001              case RES_DATETIMEFLD:
//STRIP001                  if( ((SwDateTimeField*)pFld->GetFld())->IsFixed() )
//STRIP001                  {
//STRIP001                      bChgd = TRUE;
//STRIP001                      ((SwDateTimeField*)pFld->GetFld())->SetDateTime(
//STRIP001                                            DateTime(Date(nDate), Time(nTime)) );
//STRIP001                  }
//STRIP001                  break;
//STRIP001
//STRIP001              case RES_FILENAMEFLD:
//STRIP001                  if( ((SwFileNameField*)pFld->GetFld())->IsFixed() )
//STRIP001                  {
//STRIP001                      bChgd = TRUE;
//STRIP001                      SwFileNameField* pFileNameFld =
//STRIP001                          (SwFileNameField*)pFld->GetFld();
//STRIP001                      pFileNameFld->SetExpansion( ((SwFileNameFieldType*)
//STRIP001                                  pFileNameFld->GetTyp())->Expand(
//STRIP001                                          pFileNameFld->GetFormat() ) );
//STRIP001                  }
//STRIP001                  break;
//STRIP001              }
//STRIP001
//STRIP001              // Formatierung anstossen
//STRIP001              if( bChgd )
//STRIP001                  pFld->Modify( 0, 0 );
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if( !bIsModified )
//STRIP001      ResetModified();
/*N*/ }

/*N*/ BOOL SwDoc::SetFieldsDirty( BOOL b, const SwNode* pChk, ULONG nLen )
/*N*/ {
/*N*/   // teste ggfs. mal, ob die angegbenen Nodes ueberhaupt Felder beinhalten.
/*N*/   // wenn nicht, braucht das Flag nicht veraendert werden.
/*N*/   BOOL bFldsFnd = FALSE;
/*N*/   if( b && pChk && !GetUpdtFlds().IsFieldsDirty() && !IsInDtor()
/*N*/       // ?? was ist mit Undo, da will man es doch auch haben !!
/*N*/       /*&& &pChk->GetNodes() == &GetNodes()*/ )
/*N*/   {
/*N*/       b = FALSE;
/*N*/       if( !nLen )
/*N*/           ++nLen;
/*N*/       ULONG nStt = pChk->GetIndex();
/*N*/       const SwNodes& rNds = pChk->GetNodes();
/*N*/       while( nLen-- )
/*N*/       {
/*N*/           const SwTxtNode* pTNd = rNds[ nStt++ ]->GetTxtNode();
/*N*/           if( pTNd )
/*N*/           {
/*N*/               if( pTNd->GetFmtColl() &&
/*N*/                   MAXLEVEL > pTNd->GetTxtColl()->GetOutlineLevel() )
/*N*/                   // Kapitelfelder aktualisieren
/*N*/                   b = TRUE;
/*N*/               else if( pTNd->GetpSwpHints() && pTNd->GetSwpHints().Count() )
/*N*/                   for( USHORT n = 0, nEnd = pTNd->GetSwpHints().Count();
/*N*/                           n < nEnd; ++n )
/*N*/                   {
/*N*/                       const SwTxtAttr* pAttr = pTNd->GetSwpHints()[ n ];
/*N*/                       if( RES_TXTATR_FIELD == pAttr->Which() )
/*N*/                       {
/*N*/                           b = TRUE;
/*N*/                           break;
/*N*/                       }
/*N*/                   }
/*N*/
/*N*/               if( b )
/*N*/                   break;
/*N*/           }
/*N*/       }
/*N*/       bFldsFnd = b;
/*N*/   }
/*N*/   GetUpdtFlds().SetFieldsDirty( b );
/*N*/   return bFldsFnd;
/*N*/ }
/* -----------------------------21.12.99 12:55--------------------------------

 ---------------------------------------------------------------------------*/
//STRIP001 void SwDoc::ChangeAuthorityData( const SwAuthEntry* pNewData )
//STRIP001 {
//STRIP001  const USHORT nSize = pFldTypes->Count();
//STRIP001
//STRIP001  for( USHORT i = INIT_FLDTYPES; i < nSize; ++i )
//STRIP001  {
//STRIP001      SwFieldType* pFldType = (*pFldTypes)[i];
//STRIP001      if( RES_AUTHORITY  == pFldType->Which() )
//STRIP001      {
//STRIP001          SwAuthorityFieldType* pAuthType = (SwAuthorityFieldType*)pFldType;
//STRIP001          pAuthType->ChangeEntryContent(pNewData);
//STRIP001          break;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001 }
/*--------------------------------------------------------------------
    Beschreibung:
 --------------------------------------------------------------------*/

/*N*/ void SwDocUpdtFld::InsDelFldInFldLst( BOOL bIns, const SwTxtFld& rFld )
/*N*/ {
/*N*/   USHORT nWhich = rFld.GetFld().GetFld()->GetTyp()->Which();
/*N*/   switch( nWhich )
/*N*/   {
/*N*/   case RES_DBFLD:
/*N*/   case RES_SETEXPFLD:
/*N*/   case RES_HIDDENPARAFLD:
/*N*/   case RES_HIDDENTXTFLD:
/*N*/   case RES_DBNUMSETFLD:
/*N*/   case RES_DBNEXTSETFLD:
/*N*/   case RES_DBSETNUMBERFLD:
/*N*/   case RES_GETEXPFLD:
/*N*/       break;          // diese muessen ein-/ausgetragen werden!
/*N*/
/*N*/   default:
/*N*/       return;
/*N*/   }
/*N*/
/*N*/   SetFieldsDirty( TRUE );
/*N*/   if( !pFldSortLst )
/*N*/   {
/*?*/       if( !bIns )             // keine Liste vorhanden und loeschen
/*?*/           return;             // dann nichts tun
/*?*/       pFldSortLst = new _SetGetExpFlds( 64, 16 );
/*N*/   }
/*N*/
/*N*/   if( bIns )      // neu einfuegen:
/*N*/       GetBodyNode( rFld, nWhich );
/*N*/   else
/*N*/   {
/*?*/       // ueber den pTxtFld Pointer suchen. Ist zwar eine Sortierte
/*?*/       // Liste, aber nach Node-Positionen sortiert. Bis dieser
/*?*/       // bestimmt ist, ist das Suchen nach dem Pointer schon fertig
/*?*/       for( USHORT n = 0; n < pFldSortLst->Count(); ++n )
/*?*/           if( &rFld == (*pFldSortLst)[ n ]->GetPointer() )
/*?*/               pFldSortLst->DeleteAndDestroy( n--, 1 );
/*?*/               // ein Feld kann mehrfach vorhanden sein!
/*N*/   }
/*N*/ }

/*M*/ void SwDocUpdtFld::_MakeFldList( SwDoc& rDoc, int eGetMode )
/*M*/ {
/*M*/   // neue Version: gehe ueber alle Felder vom Attribut-Pool
/*M*/   if( pFldSortLst )
/*M*/       delete pFldSortLst;
/*M*/   pFldSortLst = new _SetGetExpFlds( 64, 16 );
/*M*/
/*M*/     /// OD 09.08.2002 [#101207#,#101216#,#101778#] - consider and unhide sections
/*M*/     ///     with hide condition, only in mode GETFLD_ALL (<eGetMode == GETFLD_ALL>)
/*M*/     ///     notes by OD:
/*M*/     ///         eGetMode == GETFLD_CALC in call from methods SwDoc::FldsToCalc
/*M*/     ///         eGetMode == GETFLD_EXPAND in call from method SwDoc::FldsToExpand
/*M*/     ///         eGetMode == GETFLD_ALL in call from method SwDoc::UpdateExpFlds
/*M*/     ///         I figured out that hidden section only have to be shown,
/*M*/     ///         if fields have updated (call by SwDoc::UpdateExpFlds) and thus
/*M*/     ///         the hide conditions of section have to be updated.
/*M*/     ///         For correct updating the hide condition of a section, its position
/*M*/     ///         have to be known in order to insert the hide condition as a new
/*M*/     ///         expression field into the sorted field list (<pFldSortLst>).
/*M*/     if ( eGetMode == GETFLD_ALL )
/*M*/   // zuerst die Bereiche einsammeln. Alle die ueber Bedingung
/*M*/   // gehiddet sind, wieder mit Frames versorgen, damit die darin
/*M*/   // enthaltenen Felder richtig einsortiert werden!!!
/*M*/     {
/*M*/       // damit die Frames richtig angelegt werden, muessen sie in der
/*M*/       // Reihenfolgen von oben nach unten expandiert werden
/*M*/       SvULongs aTmpArr;
/*M*/       SwSectionFmts& rArr = rDoc.GetSections();
/*M*/       SwSectionNode* pSectNd;
/*M*/       USHORT nArrStt = 0;
/*M*/       ULONG nSttCntnt = rDoc.GetNodes().GetEndOfExtras().GetIndex();
            USHORT n=0;
/*M*/       for( n = rArr.Count(); n; )
/*M*/       {
/*M*/           SwSection* pSect = rArr[ --n ]->GetSection();
/*M*/           if( pSect->IsHidden() && pSect->GetCondition().Len() &&
/*M*/               0 != ( pSectNd = pSect->GetFmt()->GetSectionNode() ))
/*M*/           {
/*M*/               ULONG nIdx = pSectNd->GetIndex();
                    USHORT i=0;
/*M*/               for( i = 0;
/*M*/                   i < aTmpArr.Count() && aTmpArr[ i ] < nIdx;
/*M*/                   ++i )
/*M*/                   ;
/*M*/               aTmpArr.Insert( nIdx, i );
/*M*/               if( nIdx < nSttCntnt )
/*M*/                   ++nArrStt;
/*M*/           }
/*M*/       }
/*M*/
/*M*/         // erst alle anzeigen, damit die Frames vorhanden sind. Mit deren
/*M*/         // Position wird das BodyAnchor ermittelt.
/*M*/         // Dafuer erst den ContentBereich, dann die Sonderbereiche!!!
/*M*/         for( n = nArrStt; n < aTmpArr.Count(); ++n )
/*M*/         {
/*M*/             pSectNd = rDoc.GetNodes()[ aTmpArr[ n ] ]->GetSectionNode();
/*M*/             ASSERT( pSectNd, "Wo ist mein SectionNode" );
/*M*/             pSectNd->GetSection().SetCondHidden( FALSE );
/*M*/         }
/*M*/         for( n = 0; n < nArrStt; ++n )
/*M*/         {
/*M*/             pSectNd = rDoc.GetNodes()[ aTmpArr[ n ] ]->GetSectionNode();
/*M*/             ASSERT( pSectNd, "Wo ist mein SectionNode" );
/*M*/             pSectNd->GetSection().SetCondHidden( FALSE );
/*M*/         }
/*M*/
/*M*/         // so, erst jetzt alle sortiert in die Liste eintragen
/*M*/         for( n = 0; n < aTmpArr.Count(); ++n )
/*?*/             GetBodyNode( *rDoc.GetNodes()[ aTmpArr[ n ] ]->GetSectionNode() );
/*M*/     }
/*M*/
/*M*/   String sTrue( String::CreateFromAscii(
/*M*/                                   RTL_CONSTASCII_STRINGPARAM( "TRUE" ))),
/*M*/          sFalse( String::CreateFromAscii(
/*M*/                                   RTL_CONSTASCII_STRINGPARAM( "FALSE" )));
/*M*/
/*M*/   BOOL bIsDBMgr = 0 != rDoc.GetNewDBMgr();
/*M*/   USHORT nWhich, n;
/*M*/   const String* pFormel = 0;
/*M*/   const SfxPoolItem* pItem;
/*M*/   USHORT nMaxItems = rDoc.GetAttrPool().GetItemCount( RES_TXTATR_FIELD );
/*M*/   for( n = 0; n < nMaxItems; ++n )
/*M*/   {
/*M*/       if( 0 == (pItem = rDoc.GetAttrPool().GetItem( RES_TXTATR_FIELD, n )) )
/*M*/           continue;
/*M*/
/*M*/       const SwFmtFld* pFmtFld = (SwFmtFld*)pItem;
/*M*/       const SwTxtFld* pTxtFld = pFmtFld->GetTxtFld();
/*M*/       if( !pTxtFld || !pTxtFld->GetTxtNode().GetNodes().IsDocNodes() )
/*M*/           continue;
/*M*/
/*M*/       const SwField* pFld = pFmtFld->GetFld();
/*M*/       switch( nWhich = pFld->GetTyp()->Which() )
/*M*/       {
/*M*/           case RES_DBSETNUMBERFLD:
/*M*/           case RES_GETEXPFLD:
/*M*/               if( GETFLD_ALL == eGetMode )
/*M*/                   pFormel = &sTrue;
/*M*/               break;
/*M*/
/*M*/           case RES_DBFLD:
/*M*/               if( GETFLD_EXPAND & eGetMode )
/*M*/                   pFormel = &sTrue;
/*M*/               break;
/*M*/
/*M*/           case RES_SETEXPFLD:
/*M*/                           /// OD 04.10.2002 #102894#
/*N*/                 /// fields of subtype <string> have also been add
/*N*/                 /// for calculation (eGetMode == GETFLD_CALC).
/*N*/                 /// Thus, add fields of subtype <string> in all modes
/*N*/                 ///     (eGetMode == GETFLD_EXPAND||GETFLD_CALC||GETFLD_ALL)
/*N*/                 /// and fields of other subtypes only in the modes
/*N*/                 ///     (eGetMode == GETFLD_CALC||GETFLD_ALL)
                /* "old" if construct - not deleted for history and code review
                if( ( GSE_STRING & pFld->GetSubType()
                    ? GETFLD_EXPAND : GETFLD_CALC )
                        & eGetMode )
                */
/*N*/                 if ( !(eGetMode == GETFLD_EXPAND) ||
/*N*/                      (GSE_STRING & pFld->GetSubType()) )
/*N*/                 {
/*N*/                   pFormel = &sTrue;
/*N*/                 }
/*M*/               break;
/*M*/
/*M*/           case RES_HIDDENPARAFLD:
/*M*/               if( GETFLD_ALL == eGetMode )
/*M*/               {
/*M*/                   pFormel = &pFld->GetPar1();
/*M*/                   if( !pFormel->Len() || pFormel->Equals( sFalse ))
/*M*/                       ((SwHiddenParaField*)pFld)->SetHidden( FALSE );
/*M*/                   else if( pFormel->Equals( sTrue ))
/*M*/                       ((SwHiddenParaField*)pFld)->SetHidden( TRUE );
/*M*/                   else
/*M*/                       break;
/*M*/
/*M*/                   pFormel = 0;
/*M*/                   // Formatierung anstossen
/*M*/                   ((SwFmtFld*)pFmtFld)->Modify( 0, 0 );
/*M*/               }
/*M*/               break;
/*M*/
/*M*/           case RES_HIDDENTXTFLD:
/*M*/               if( GETFLD_ALL == eGetMode )
/*M*/               {
/*M*/                   pFormel = &pFld->GetPar1();
/*M*/                   if( !pFormel->Len() || pFormel->Equals( sFalse ))
/*M*/                       ((SwHiddenTxtField*)pFld)->SetValue( TRUE );
/*M*/                   else if( pFormel->Equals( sTrue ))
/*M*/                       ((SwHiddenTxtField*)pFld)->SetValue( FALSE );
/*M*/                   else
/*M*/                       break;
/*M*/
/*M*/                   pFormel = 0;
/*M*/
/*M*/                   // Feld Evaluieren
/*M*/                   ((SwHiddenTxtField*)pFld)->Evaluate(&rDoc);
/*M*/                   // Formatierung anstossen
/*M*/                   ((SwFmtFld*)pFmtFld)->Modify( 0, 0 );
/*M*/               }
/*M*/               break;
/*M*/
/*M*/           case RES_DBNUMSETFLD:
/*M*/           {
/*N*/               SwDBData aDBData(((SwDBNumSetField*)pFld)->GetDBData(&rDoc));
/*N*/
/*N*/               if( bIsDBMgr &&
/*N*/                   rDoc.GetNewDBMgr()->OpenDataSource( aDBData.sDataSource, aDBData.sCommand )&&
/*N*/                   GETFLD_ALL == eGetMode ||
/*N*/                   ( GETFLD_CALC & eGetMode &&
/*N*/                       ((SwDBNumSetField*)pFld)->IsCondValid()))
/*N*/                   pFormel = &pFld->GetPar1();
/*M*/           }
/*M*/           break;
/*M*/           case RES_DBNEXTSETFLD:
/*M*/           {
/*N*/               SwDBData aDBData(((SwDBNextSetField*)pFld)->GetDBData(&rDoc));
/*N*/
/*N*/               if( bIsDBMgr &&
/*N*/                   rDoc.GetNewDBMgr()->OpenDataSource( aDBData.sDataSource, aDBData.sCommand )&&
/*N*/                   GETFLD_ALL == eGetMode ||
/*N*/                   ( GETFLD_CALC & eGetMode &&
/*N*/                       ((SwDBNextSetField*)pFld)->IsCondValid() ))
/*N*/                   pFormel = &pFld->GetPar1();
/*M*/           }
/*M*/           break;
/*M*/       }
/*M*/
/*M*/       if( pFormel && pFormel->Len() )
/*M*/       {
/*M*/           GetBodyNode( *pTxtFld, nWhich );
/*M*/           pFormel = 0;
/*M*/       }
/*M*/   }
/*M*/   nFldLstGetMode = eGetMode;
/*M*/   nNodes = rDoc.GetNodes().Count();
/*M*/
/*M*/ #ifdef JP_DEBUG
/*M*/   {
/*M*/   SvFileStream sOut( "f:\\x.x", STREAM_STD_WRITE );
/*M*/   sOut.Seek( STREAM_SEEK_TO_END );
/*M*/   sOut << "------------------" << endl;
/*M*/   const _SetGetExpFldPtr* pSortLst = pFldSortLst->GetData();
/*M*/   for( USHORT n = pFldSortLst->Count(); n; --n, ++pSortLst )
/*M*/   {
/*M*/       String sStr( (*pSortLst)->GetNode() );
/*M*/       sStr += "\t, ";
/*M*/       sStr += (*pSortLst)->GetCntnt();
/*M*/       sStr += "\tNode: ";
/*M*/       sStr += (*pSortLst)->GetFld()->GetTxtNode().StartOfSectionIndex();
/*M*/       sStr += "\tPos: ";
/*M*/       sStr += *(*pSortLst)->GetFld()->GetStart();
/*M*/       sStr += "\tType: ";
/*M*/       sStr += (*pSortLst)->GetFld()->GetFld().GetFld()->GetTyp()->Which();
/*M*/
/*M*/       sOut << sStr.GetStr() << endl;
/*M*/   }
/*M*/   }
/*M*/ #endif
/*M*/   // JP_DEBUG
/*M*/ }

/*--------------------------------------------------------------------
    Beschreibung:
 --------------------------------------------------------------------*/

/*N*/ void SwDocUpdtFld::GetBodyNode( const SwTxtFld& rTFld, USHORT nFldWhich )
/*N*/ {
/*N*/   const SwTxtNode& rTxtNd = rTFld.GetTxtNode();
/*N*/   const SwDoc& rDoc = *rTxtNd.GetDoc();
/*N*/
/*N*/   // immer den ersten !! (in Tab-Headline, Kopf-/Fuss )
/*N*/   Point aPt;
/*N*/   const SwCntntFrm* pFrm = rTxtNd.GetFrm( &aPt, 0, FALSE );
/*N*/
/*N*/   _SetGetExpFld* pNew = NULL;
/*N*/   BOOL bIsInBody = FALSE;
/*N*/
/*N*/   if( !pFrm || pFrm->IsInDocBody() )
/*N*/   {
/*N*/       // einen Index fuers bestimmen vom TextNode anlegen
/*N*/       SwNodeIndex aIdx( rTxtNd );
/*N*/       bIsInBody = rDoc.GetNodes().GetEndOfExtras().GetIndex() < aIdx.GetIndex();
/*N*/
/*N*/         // #104291# dvo: We don't want to update fields in redlines, or those
/*N*/         // in frames whose anchor is in redline. However, we do want to update
/*N*/         // fields in hidden sections. So: In order to be updated, a field 1)
/*N*/         // must have a frame, or 2) it must be in the document body.
/*N*/       if( (pFrm != NULL) || bIsInBody )
/*N*/           pNew = new _SetGetExpFld( aIdx, &rTFld );
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       // einen Index fuers bestimmen vom TextNode anlegen
/*N*/       SwPosition aPos( rDoc.GetNodes().GetEndOfPostIts() );
/*N*/ #ifndef PRODUCT
/*N*/       ASSERT( GetBodyTxtNode( rDoc, aPos, *pFrm ), "wo steht das Feld" );
/*N*/ #else
/*N*/       GetBodyTxtNode( rDoc, aPos, *pFrm );
/*N*/ #endif
/*N*/       pNew = new _SetGetExpFld( aPos.nNode, &rTFld, &aPos.nContent );
/*N*/   }
/*N*/
/*N*/   // bei GetExp.-/DB.-Felder immer das BodyTxtFlag setzen
/*N*/   if( RES_GETEXPFLD == nFldWhich )
/*N*/   {
/*?*/       SwGetExpField* pGetFld = (SwGetExpField*)rTFld.GetFld().GetFld();
/*?*/       pGetFld->ChgBodyTxtFlag( bIsInBody );
/*N*/   }
/*N*/   else if( RES_DBFLD == nFldWhich )
/*N*/   {
/*N*/       SwDBField* pDBFld = (SwDBField*)rTFld.GetFld().GetFld();
/*N*/       pDBFld->ChgBodyTxtFlag( bIsInBody );
/*N*/   }
/*N*/
/*N*/   if( pNew != NULL )
/*N*/       if( !pFldSortLst->Insert( pNew ))
/*?*/           delete pNew;
/*N*/ }

void SwDocUpdtFld::GetBodyNode( const SwSectionNode& rSectNd )
{
    const SwDoc& rDoc = *rSectNd.GetDoc();
    _SetGetExpFld* pNew = 0;

    if( rSectNd.GetIndex() < rDoc.GetNodes().GetEndOfExtras().GetIndex() )
    {
        do {            // middle check loop

            // dann muessen wir uns mal den Anker besorgen!
            // einen Index fuers bestimmen vom TextNode anlegen
            SwPosition aPos( rSectNd );
            SwCntntNode* pCNd = rDoc.GetNodes().GoNext( &aPos.nNode ); // zum naechsten ContentNode

            if( !pCNd || !pCNd->IsTxtNode() )
                break;

            // immer den ersten !! (in Tab-Headline, Kopf-/Fuss )
            Point aPt;
            const SwCntntFrm* pFrm = pCNd->GetFrm( &aPt, 0, FALSE );
            if( !pFrm )
                break;

#ifndef PRODUCT
            ASSERT( GetBodyTxtNode( rDoc, aPos, *pFrm ), "wo steht das Feld" );
#else
            GetBodyTxtNode( rDoc, aPos, *pFrm );
#endif
            pNew = new _SetGetExpFld( rSectNd, &aPos );

        } while( FALSE );
    }

    if( !pNew )
        pNew = new _SetGetExpFld( rSectNd );

    if( !pFldSortLst->Insert( pNew ))
        delete pNew;
}

/*N*/ void SwDocUpdtFld::InsertFldType( const SwFieldType& rType )
/*N*/ {
/*N*/   String sFldName;
/*N*/   switch( rType.Which() )
/*N*/   {
/*N*/   case RES_USERFLD :
/*N*/       sFldName = ((SwUserFieldType&)rType).GetName();
/*N*/       break;
/*N*/   case RES_SETEXPFLD:
/*N*/       sFldName = ((SwSetExpFieldType&)rType).GetName();
/*N*/       break;
/*N*/   default:
/*N*/       ASSERT( !this, "kein gueltiger FeldTyp" );
/*N*/   }
/*N*/
/*N*/   if( sFldName.Len() )
/*N*/   {
/*N*/       SetFieldsDirty( TRUE );
/*N*/       // suchen und aus der HashTabelle entfernen
/*N*/       GetAppCharClass().toLower( sFldName );
/*N*/       USHORT n;
/*N*/
/*N*/       SwHash* pFnd = Find( sFldName, GetFldTypeTable(), TBLSZ, &n );
/*N*/
/*N*/       if( !pFnd )
/*N*/       {
/*N*/           SwCalcFldType* pNew = new SwCalcFldType( sFldName, &rType );
/*N*/           pNew->pNext = aFldTypeTable[ n ];
/*N*/           aFldTypeTable[ n ] = pNew;
/*N*/       }
/*N*/   }
/*N*/ }

//STRIP001 void SwDocUpdtFld::RemoveFldType( const SwFieldType& rType )
//STRIP001 {
//STRIP001  String sFldName;
//STRIP001  switch( rType.Which() )
//STRIP001  {
//STRIP001  case RES_USERFLD :
//STRIP001      sFldName = ((SwUserFieldType&)rType).GetName();
//STRIP001      break;
//STRIP001  case RES_SETEXPFLD:
//STRIP001      sFldName = ((SwSetExpFieldType&)rType).GetName();
//STRIP001      break;
//STRIP001  }
//STRIP001
//STRIP001  if( sFldName.Len() )
//STRIP001  {
//STRIP001      SetFieldsDirty( TRUE );
//STRIP001      // suchen und aus der HashTabelle entfernen
//STRIP001      GetAppCharClass().toLower( sFldName );
//STRIP001      USHORT n;
//STRIP001
//STRIP001      SwHash* pFnd = Find( sFldName, GetFldTypeTable(), TBLSZ, &n );
//STRIP001      if( pFnd )
//STRIP001      {
//STRIP001          if( aFldTypeTable[ n ] == pFnd )
//STRIP001              aFldTypeTable[ n ] = (SwCalcFldType*)pFnd->pNext;
//STRIP001          else
//STRIP001          {
//STRIP001              SwHash* pPrev = aFldTypeTable[ n ];
//STRIP001              while( pPrev->pNext != pFnd )
//STRIP001                  pPrev = pPrev->pNext;
//STRIP001              pPrev->pNext = pFnd->pNext;
//STRIP001          }
//STRIP001          pFnd->pNext = 0;
//STRIP001          delete pFnd;
//STRIP001      }
//STRIP001  }
//STRIP001 }

/*N*/ SwDocUpdtFld::SwDocUpdtFld()
/*N*/   : pFldSortLst( 0 ), nFldLstGetMode( 0 ), nFldUpdtPos( LONG_MAX )
/*N*/ {
/*N*/   bInUpdateFlds = bFldsDirty = FALSE;
/*N*/   memset( aFldTypeTable, 0, sizeof( aFldTypeTable ) );
/*N*/ }

/*N*/ SwDocUpdtFld::~SwDocUpdtFld()
/*N*/ {
/*N*/   delete pFldSortLst;
/*N*/
/*N*/   for( USHORT n = 0; n < TBLSZ; ++n )
/*N*/       delete aFldTypeTable[n];
/*N*/ }




}
