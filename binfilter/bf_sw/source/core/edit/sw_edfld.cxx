/*************************************************************************
 *
 *  $RCSfile: sw_edfld.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:49:28 $
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

#ifndef _UNOTOOLS_CHARCLASS_HXX
#include <unotools/charclass.hxx>
#endif

#ifndef _EDITSH_HXX
#include <editsh.hxx>
#endif
#ifndef _FLDBAS_HXX
#include <fldbas.hxx>
#endif
#ifndef _NDTXT_HXX
#include <ndtxt.hxx>        // GetCurFld
#endif
#ifndef _HINTS_HXX
#include <hints.hxx>        // SwRefMarkFldUpdate
#endif
#ifndef _DOCARY_HXX
#include <docary.hxx>
#endif
#ifndef _FMTFLD_HXX //autogen
#include <fmtfld.hxx>
#endif
#ifndef _TXTFLD_HXX //autogen
#include <txtfld.hxx>
#endif
#ifndef _EDIMP_HXX
#include <edimp.hxx>
#endif
#ifndef _DBFLD_HXX
#include <dbfld.hxx>
#endif
#ifndef _EXPFLD_HXX
#include <expfld.hxx>
#endif
#ifndef _FLDDAT_HXX
#include <flddat.hxx>
#endif
#ifndef _SWUNDO_HXX
#include <swundo.hxx>
#endif
#ifndef _DBMGR_HXX
#include <dbmgr.hxx>
#endif
#ifndef _SWDDETBL_HXX
#include <swddetbl.hxx>
#endif
#ifndef _COM_SUN_STAR_CONTAINER_XNAMEACCESS_HPP_
#include <com/sun/star/container/XNameAccess.hpp>
#endif
#ifndef _COMPHELPER_PROCESSFACTORY_HXX_
#include <comphelper/processfactory.hxx>
#endif
#ifndef _COM_SUN_STAR_LANG_XMULTISERVICEFACTORY_HPP_
#include <com/sun/star/lang/XMultiServiceFactory.hpp>
#endif
#ifndef _LEGACYBINFILTERMGR_HXX
#include <legacysmgr/legacy_binfilters_smgr.hxx>    //STRIP002
#endif
namespace binfilter {
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::container;
using namespace ::com::sun::star::lang;
using namespace ::rtl;


// wenn Selektion groesser Max Nodes oder mehr als Max Selektionen
// => keine Attribute
static const USHORT nMaxLookup = 40;

/*--------------------------------------------------------------------
    Beschreibung: Feldtypen zu einer ResId zaehlen
                  wenn 0 alle zaehlen
 --------------------------------------------------------------------*/

//STRIP001 USHORT SwEditShell::GetFldTypeCount(USHORT nResId, BOOL bUsed ) const
//STRIP001 {
//STRIP001  const SwFldTypes* pFldTypes = GetDoc()->GetFldTypes();
//STRIP001  const USHORT nSize = pFldTypes->Count();
//STRIP001
//STRIP001  if(nResId == USHRT_MAX)
//STRIP001  {
//STRIP001      if(!bUsed)
//STRIP001          return nSize;
//STRIP001      else
//STRIP001      {
//STRIP001          USHORT nUsed = 0;
//STRIP001          for ( USHORT i = 0; i < nSize; i++ )
//STRIP001          {
//STRIP001              if(IsUsed(*(*pFldTypes)[i]))
//STRIP001                  nUsed++;
//STRIP001          }
//STRIP001          return nUsed;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  // Alle Typen mit gleicher ResId
//STRIP001  USHORT nIdx  = 0;
//STRIP001  for(USHORT i = 0; i < nSize; ++i)
//STRIP001  {   // Gleiche ResId -> Index erhoehen
//STRIP001      SwFieldType& rFldType = *((*pFldTypes)[i]);
//STRIP001      if(rFldType.Which() == nResId)
//STRIP001          nIdx++;
//STRIP001  }
//STRIP001  return nIdx;
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung: Feldtypen zu einer ResId finden
                  wenn 0 alle finden
 --------------------------------------------------------------------*/
//STRIP001 SwFieldType* SwEditShell::GetFldType(USHORT nFld, USHORT nResId, BOOL bUsed ) const
//STRIP001 {
//STRIP001  const SwFldTypes* pFldTypes = GetDoc()->GetFldTypes();
//STRIP001  const USHORT nSize = pFldTypes->Count();
//STRIP001
//STRIP001  if(nResId == USHRT_MAX && nFld < nSize)
//STRIP001  {
//STRIP001      if(!bUsed)
//STRIP001          return (*pFldTypes)[nFld];
//STRIP001      else
//STRIP001      {
//STRIP001          USHORT i, nUsed = 0;
//STRIP001          for ( i = 0; i < nSize; i++ )
//STRIP001          {
//STRIP001              if(IsUsed(*(*pFldTypes)[i]))
//STRIP001              {
//STRIP001                  if(nUsed == nFld)
//STRIP001                      break;
//STRIP001                  nUsed++;
//STRIP001              }
//STRIP001          }
//STRIP001          return i < nSize ? (*pFldTypes)[i] : 0;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  USHORT nIdx = 0;
//STRIP001  for(USHORT i = 0; i < nSize; ++i)
//STRIP001  {   // Gleiche ResId -> Index erhoehen
//STRIP001      SwFieldType* pFldType = (*pFldTypes)[i];
//STRIP001      if(pFldType->Which() == nResId)
//STRIP001      {
//STRIP001          if (!bUsed || IsUsed(*pFldType))
//STRIP001          {
//STRIP001              if(nIdx == nFld)
//STRIP001                  return pFldType;
//STRIP001              nIdx++;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  return 0;
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung: Den ersten Typen mit ResId und Namen finden
 --------------------------------------------------------------------*/
//STRIP001 SwFieldType* SwEditShell::GetFldType(USHORT nResId, const String& rName) const
//STRIP001 {
//STRIP001  return GetDoc()->GetFldType( nResId, rName );
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung: Feldtypen loeschen
 --------------------------------------------------------------------*/
//STRIP001 void SwEditShell::RemoveFldType(USHORT nFld, USHORT nResId)
//STRIP001 {
//STRIP001  if( USHRT_MAX == nResId )
//STRIP001  {
//STRIP001      GetDoc()->RemoveFldType(nFld);
//STRIP001      return;
//STRIP001  }
//STRIP001
//STRIP001  const SwFldTypes* pFldTypes = GetDoc()->GetFldTypes();
//STRIP001  const USHORT nSize = pFldTypes->Count();
//STRIP001  USHORT nIdx = 0;
//STRIP001  for( USHORT i = 0; i < nSize; ++i )
//STRIP001      // Gleiche ResId -> Index erhoehen
//STRIP001      if( (*pFldTypes)[i]->Which() == nResId &&
//STRIP001          nIdx++ == nFld )
//STRIP001      {
//STRIP001          GetDoc()->RemoveFldType( i );
//STRIP001          return;
//STRIP001      }
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung: FieldType ueber Name loeschen
 --------------------------------------------------------------------*/
//STRIP001 void SwEditShell::RemoveFldType(USHORT nResId, const String& rStr)
//STRIP001 {
//STRIP001  const SwFldTypes* pFldTypes = GetDoc()->GetFldTypes();
//STRIP001  const USHORT nSize = pFldTypes->Count();
//STRIP001  const CharClass& rCC = GetAppCharClass();
//STRIP001
//STRIP001  String aTmp( rCC.lower( rStr ));
//STRIP001
//STRIP001  for(USHORT i = 0; i < nSize; ++i)
//STRIP001  {
//STRIP001      // Gleiche ResId -> Index erhoehen
//STRIP001      SwFieldType* pFldType = (*pFldTypes)[i];
//STRIP001      if( pFldType->Which() == nResId )
//STRIP001      {
//STRIP001          if( aTmp.Equals( rCC.lower( pFldType->GetName() ) ))
//STRIP001          {
//STRIP001              GetDoc()->RemoveFldType(i);
//STRIP001              return;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 }


//STRIP001 void SwEditShell::FieldToText( SwFieldType* pType )
//STRIP001 {
//STRIP001  if( !pType->GetDepends() )
//STRIP001      return;
//STRIP001
//STRIP001  SET_CURR_SHELL( this );
//STRIP001  StartAllAction();
//STRIP001  StartUndo( UNDO_DELETE );
//STRIP001  Push();
//STRIP001  SwPaM* pPaM = GetCrsr();
//STRIP001
//STRIP001  BOOL bDDEFld = RES_DDEFLD == pType->Which();
//STRIP001  // Modify-Object gefunden, trage alle Felder ins Array ein
//STRIP001  SwClientIter aIter( *pType );
//STRIP001  SwClient * pLast = aIter.GoStart();
//STRIP001
//STRIP001  if( pLast )     // konnte zum Anfang gesprungen werden ??
//STRIP001      do {
//STRIP001          pPaM->DeleteMark();
//STRIP001          const SwFmtFld* pFmtFld = bDDEFld
//STRIP001                      ? PTR_CAST( SwFmtFld, pLast )
//STRIP001                      : (SwFmtFld*)pLast;
//STRIP001
//STRIP001          if( pFmtFld )
//STRIP001          {
//STRIP001              if( !pFmtFld->GetTxtFld() )
//STRIP001                  continue;
//STRIP001
//STRIP001              // kann keine DDETabelle sein
//STRIP001              const SwTxtNode& rTxtNode = pFmtFld->GetTxtFld()->GetTxtNode();
//STRIP001              pPaM->GetPoint()->nNode = rTxtNode;
//STRIP001              pPaM->GetPoint()->nContent.Assign( (SwTxtNode*)&rTxtNode,
//STRIP001                                   *pFmtFld->GetTxtFld()->GetStart() );
//STRIP001
//STRIP001              // Feldinhalt durch Text ersetzen
//STRIP001              String aEntry( pFmtFld->GetFld()->Expand() );
//STRIP001              pPaM->SetMark();
//STRIP001              pPaM->Move( fnMoveForward );
//STRIP001              GetDoc()->Delete( *pPaM );
//STRIP001              GetDoc()->Insert( *pPaM, aEntry );
//STRIP001          }
//STRIP001          else if( bDDEFld )
//STRIP001          {
//STRIP001              // DDETabelle
//STRIP001              SwDepend* pDep = (SwDepend*)pLast;
//STRIP001              SwDDETable* pDDETbl = (SwDDETable*)pDep->GetToTell();
//STRIP001              pDDETbl->NoDDETable();
//STRIP001          }
//STRIP001
//STRIP001      } while( 0 != ( pLast = aIter++ ));
//STRIP001
//STRIP001  Pop( FALSE );
//STRIP001  EndAllAction();
//STRIP001  EndUndo( UNDO_DELETE );
//STRIP001 }

/*************************************************************************
|*
|*                  SwEditShell::Insert( SwField )
|*
|*    Beschreibung  an der Cursorposition ein Feld einfuegen
|*    Quelle:       vgl. SwEditShell::Insert( String )
|*
*************************************************************************/
//STRIP001 void SwEditShell::Insert(SwField& rFld)
//STRIP001 {
//STRIP001  SET_CURR_SHELL( this );
//STRIP001  StartAllAction();
//STRIP001  SwFmtFld aFld( rFld );
//STRIP001
//STRIP001  FOREACHPAM_START(this)                      // fuer jeden PaM
//STRIP001      if( !GetDoc()->Insert( *PCURCRSR, aFld ) )
//STRIP001          ASSERT( FALSE, "Doc->Insert(Field) failed");
//STRIP001  FOREACHPAM_END()                      // fuer jeden PaM
//STRIP001
//STRIP001  EndAllAction();
//STRIP001 }

/*************************************************************************
|*
|*                  SwEditShell::GetCurFld()
|*
|*    Beschreibung  Stehen die PaMs auf Feldern ?
|*    Quelle:       edtfrm.cxx:
|*
*************************************************************************/

/*N*/ inline SwTxtFld *GetDocTxtFld( const SwPosition* pPos )
/*N*/ {
/*N*/   SwTxtNode *pNode = pPos->nNode.GetNode().GetTxtNode();
/*N*/   if( pNode )
/*N*/       return pNode->GetTxtFld( pPos->nContent );
/*N*/   else
/*N*/       return 0;
/*N*/ }

/*N*/ SwField* SwEditShell::GetCurFld() const
/*N*/ {
/*N*/   // Wenn es keine Selektionen gibt, gilt der Wert der aktuellen
/*N*/   // Cursor-Position.
/*N*/
/*N*/   SwPaM* pCrsr = GetCrsr();
/*N*/   SwTxtFld *pTxtFld = GetDocTxtFld( pCrsr->Start() );
/*N*/   SwField *pCurFld = NULL;
/*N*/
    /* #108536# Field was only recognized if no selection was
        present. Now it is recognized if either the cursor is in the
        field or the selection spans exactly over the field. */
/*N*/   if( pTxtFld &&
/*N*/         pCrsr->GetNext() == pCrsr &&
/*N*/         pCrsr->Start()->nNode == pCrsr->End()->nNode &&
/*N*/         (pCrsr->End()->nContent.GetIndex() -
/*N*/          pCrsr->Start()->nContent.GetIndex()) <= 1)
/*N*/   {
/*?*/       pCurFld = (SwField*)pTxtFld->GetFld().GetFld();
/*?*/       // TabellenFormel ? wandel internen in externen Namen um
/*?*/       if( RES_TABLEFLD == pCurFld->GetTyp()->Which() )
/*?*/       {
/*?*/           const SwTableNode* pTblNd = IsCrsrInTbl();
/*?*/           ((SwTblField*)pCurFld)->PtrToBoxNm( pTblNd ? &pTblNd->GetTable() : 0 );
/*?*/       }
/*?*/
/*N*/   }

    /* #108536# removed handling of multi-selections */

/*N*/   return pCurFld;
/*N*/ }


/*************************************************************************
|*
|*                  SwEditShell::UpdateFlds()
|*
|*    Beschreibung  Stehen die PaMs auf Feldern ?
|*                  BP 12.05.92
|*
*************************************************************************/
//STRIP001 SwTxtFld* lcl_FindInputFld( SwDoc* pDoc, SwField& rFld )
//STRIP001 {
//STRIP001  // suche das Feld ueber seine Addresse. Muss fuer InputFelder in
//STRIP001  // geschuetzten Feldern erfolgen
//STRIP001  SwTxtFld* pTFld = 0;
//STRIP001  if( RES_INPUTFLD == rFld.Which() || ( RES_SETEXPFLD == rFld.Which() &&
//STRIP001      ((SwSetExpField&)rFld).GetInputFlag() ) )
//STRIP001  {
//STRIP001      const SfxPoolItem* pItem;
//STRIP001      USHORT n, nMaxItems = pDoc->GetAttrPool().GetItemCount( RES_TXTATR_FIELD );
//STRIP001      for( n = 0; n < nMaxItems; ++n )
//STRIP001          if( 0 != (pItem = pDoc->GetAttrPool().GetItem( RES_TXTATR_FIELD, n ) )
//STRIP001              && ((SwFmtFld*)pItem)->GetFld() == &rFld )
//STRIP001          {
//STRIP001              pTFld = ((SwFmtFld*)pItem)->GetTxtFld();
//STRIP001              break;
//STRIP001          }
//STRIP001  }
//STRIP001  return pTFld;
//STRIP001 }

//STRIP001 void SwEditShell::UpdateFlds( SwField &rFld )
//STRIP001 {
//STRIP001  SET_CURR_SHELL( this );
//STRIP001  StartAllAction();
//STRIP001  {
//STRIP001      SwField *pCurFld = 0;
//STRIP001
//STRIP001      // Wenn es keine Selektionen gibt, gilt der Wert der aktuellen
//STRIP001      // Cursor-Position.
//STRIP001      SwMsgPoolItem* pMsgHnt = 0;
//STRIP001      SwRefMarkFldUpdate aRefMkHt( GetOut() );
//STRIP001      USHORT nFldWhich = rFld.GetTyp()->Which();
//STRIP001      if( RES_GETREFFLD == nFldWhich )
//STRIP001          pMsgHnt = &aRefMkHt;
//STRIP001
//STRIP001      SwPaM* pCrsr = GetCrsr();
//STRIP001      SwTxtFld *pTxtFld;
//STRIP001      SwFmtFld *pFmtFld;
//STRIP001      if( pCrsr->GetNext() == pCrsr && !pCrsr->HasMark() &&
//STRIP001          ( 0 != ( pTxtFld = GetDocTxtFld( pCrsr->Start() ) ) ||
//STRIP001            0 != ( pTxtFld = lcl_FindInputFld( GetDoc(), rFld ) ) ) &&
//STRIP001          ( pFmtFld = (SwFmtFld*)&pTxtFld->GetFld())->GetFld()
//STRIP001              ->GetTyp()->Which() == rFld.GetTyp()->Which() )
//STRIP001      {
//STRIP001          // Das gefundene Feld wird angepasst ...
//STRIP001          pFmtFld->GetFld()->ChangeFormat( rFld.GetFormat() );
//STRIP001          pFmtFld->GetFld()->SetLanguage( rFld.GetLanguage() );
//STRIP001          switch( nFldWhich )
//STRIP001          {
//STRIP001          case RES_SETEXPFLD:
//STRIP001          case RES_GETEXPFLD:
//STRIP001          case RES_HIDDENTXTFLD:
//STRIP001          case RES_HIDDENPARAFLD:
//STRIP001              GetDoc()->UpdateExpFlds( pTxtFld );
//STRIP001              break;
//STRIP001
//STRIP001          case RES_TABLEFLD:
//STRIP001              {
//STRIP001                  const SwTableNode* pTblNd = GetDoc()->IsIdxInTbl(
//STRIP001                                          pCrsr->GetPoint()->nNode );
//STRIP001                  if( pTblNd )
//STRIP001                  {
//STRIP001                      SwTableFmlUpdate aTblUpdate( &pTblNd->GetTable() );
//STRIP001                      GetDoc()->UpdateTblFlds( &aTblUpdate );
//STRIP001                  }
//STRIP001              }
//STRIP001              break;
//STRIP001
//STRIP001          case RES_MACROFLD:
//STRIP001              if( pTxtFld->GetpTxtNode() )
//STRIP001                  ((SwTxtNode*)pTxtFld->GetpTxtNode())->Modify( 0, pFmtFld );
//STRIP001              break;
//STRIP001
//STRIP001          case RES_DBFLD:
//STRIP001              {
//STRIP001                  // JP 10.02.96: ChgValue aufrufen, damit die Format-
//STRIP001                  //              aenderung den ContentString richtig setzt
//STRIP001                  SwDBField* pDBFld = (SwDBField*)pFmtFld->GetFld();
//STRIP001                  if (pDBFld->IsInitialized())
//STRIP001                      pDBFld->ChgValue( pDBFld->GetValue(), TRUE );
//STRIP001              }
//STRIP001              // kein break;
//STRIP001
//STRIP001          default:
//STRIP001              pFmtFld->Modify( 0, pMsgHnt );
//STRIP001          }
//STRIP001
//STRIP001          // Die Felder die wir berechnen koennen werden hier expli.
//STRIP001          // zum Update angestossen.
//STRIP001          if( nFldWhich == RES_USERFLD )
//STRIP001              GetDoc()->UpdateUsrFlds();
//STRIP001      }
//STRIP001
//STRIP001      // bOkay (statt return wg. EndAllAction) wird FALSE,
//STRIP001      // 1) wenn nur ein Pam mehr als ein Feld enthaelt oder
//STRIP001      // 2) bei gemischten Feldtypen
//STRIP001      BOOL bOkay = TRUE;
//STRIP001      BOOL bTblSelBreak = FALSE;
//STRIP001
//STRIP001      SwMsgPoolItem aHint( RES_TXTATR_FIELD );  // Such-Hint
//STRIP001      FOREACHPAM_START(this)                      // fuer jeden PaM
//STRIP001          if( PCURCRSR->HasMark() && bOkay )      // ... mit Selektion
//STRIP001          {
//STRIP001              // Kopie des PaM
//STRIP001              SwPaM aCurPam( *PCURCRSR->GetMark(), *PCURCRSR->GetPoint() );
//STRIP001              SwPaM aPam( *PCURCRSR->GetPoint() );
//STRIP001
//STRIP001              SwPosition *pCurStt = aCurPam.Start(), *pCurEnd = aCurPam.End();
//STRIP001              /*
//STRIP001               * Fuer den Fall, dass zwei aneinanderliegende Felder in einem
//STRIP001               * PaM liegen, hangelt sich aPam portionsweise bis zum Ende.
//STRIP001               * aCurPam wird dabei nach jeder Schleifenrunde verkuerzt.
//STRIP001               * Wenn aCurPam vollstaendig durchsucht wurde, ist Start = End
//STRIP001               * und die Schleife terminiert.
//STRIP001               */
//STRIP001
//STRIP001              // Suche nach SwTxtFld ...
//STRIP001              while(  bOkay
//STRIP001                   && pCurStt->nContent != pCurEnd->nContent
//STRIP001                   && aPam.Find( aHint, FALSE, fnMoveForward, &aCurPam ) )
//STRIP001              {
//STRIP001                  //  wenn nur ein Pam mehr als ein Feld enthaelt ...
//STRIP001                  if( aPam.Start()->nContent != pCurStt->nContent )
//STRIP001                      bOkay = FALSE;
//STRIP001
//STRIP001                  if( 0 != (pTxtFld = GetDocTxtFld( pCurStt )) )
//STRIP001                  {
//STRIP001                      pFmtFld = (SwFmtFld*)&pTxtFld->GetFld();
//STRIP001                      pCurFld = pFmtFld->GetFld();
//STRIP001
//STRIP001                      // bei gemischten Feldtypen
//STRIP001                      if( pCurFld->GetTyp()->Which() != rFld.GetTyp()->Which() )
//STRIP001                          bOkay = FALSE;
//STRIP001
//STRIP001                      // Das gefundene selektierte Feld wird angepasst ...
//STRIP001                      pCurFld->ChangeFormat( rFld.GetFormat() );
//STRIP001                      if( RES_SETEXPFLD == nFldWhich ||
//STRIP001                          RES_GETEXPFLD == nFldWhich ||
//STRIP001                          RES_HIDDENTXTFLD == nFldWhich )
//STRIP001                          GetDoc()->UpdateExpFlds( pTxtFld );
//STRIP001                      else if( RES_TABLEFLD == nFldWhich )
//STRIP001                      {
//STRIP001                          SwPaM* pPam = IsTableMode() ? GetTblCrs() : &aCurPam;
//STRIP001                          const SwTableNode* pTblNd = GetDoc()->IsIdxInTbl(
//STRIP001                                                  pPam->GetPoint()->nNode );
//STRIP001                          if( pTblNd )
//STRIP001                          {
//STRIP001                              SwTableFmlUpdate aTblUpdate( &pTblNd->GetTable() );
//STRIP001                              pCurFld->GetTyp()->Modify( 0, &aTblUpdate );
//STRIP001                          }
//STRIP001                          // bei Tabellen-SSelection ist hier Ende !!
//STRIP001                          if( IsTableMode() )
//STRIP001                          {
//STRIP001                              bTblSelBreak = TRUE;
//STRIP001                              break;
//STRIP001                          }
//STRIP001                      }
//STRIP001                      else
//STRIP001                          pFmtFld->Modify( 0, pMsgHnt );
//STRIP001
//STRIP001                      // Die Felder die wir berechnen koennen werden hier
//STRIP001                      //  expli. zum Update angestossen.
//STRIP001                      if( nFldWhich == RES_USERFLD )
//STRIP001                          GetDoc()->UpdateUsrFlds();
//STRIP001                  }
//STRIP001                  // Der Suchbereich wird um den gefundenen Bereich verkuerzt.
//STRIP001                  pCurStt->nContent++;
//STRIP001              }
//STRIP001          }
//STRIP001
//STRIP001          if( bTblSelBreak )      // wenn Tabellen Selektion und Tabellen-
//STRIP001              break;              // Formel aktualisiert wurde -> beenden
//STRIP001
//STRIP001      FOREACHPAM_END()                      // fuer jeden PaM
//STRIP001  }
//STRIP001  GetDoc()->SetModified();
//STRIP001  EndAllAction();
//STRIP001 }

/*-----------------13.05.92 10:54-------------------
 Liefert den logischen fuer die Datenbank zurueck
 --------------------------------------------------*/

//STRIP001 SwDBData SwEditShell::GetDBData() const
//STRIP001 {
//STRIP001  return GetDoc()->GetDBData();
//STRIP001 }

/*N*/ const SwDBData& SwEditShell::GetDBDesc() const
/*N*/ {
/*N*/   return GetDoc()->GetDBDesc();
/*N*/ }

//STRIP001 void SwEditShell::ChgDBData(const SwDBData& rNewData)
//STRIP001 {
//STRIP001  GetDoc()->ChgDBData(rNewData);
//STRIP001 }

//STRIP001 void SwEditShell::GetAllUsedDB( SvStringsDtor& rDBNameList,
//STRIP001                              SvStringsDtor* pAllDBNames )
//STRIP001 {
//STRIP001  GetDoc()->GetAllUsedDB( rDBNameList, pAllDBNames );
//STRIP001 }

//STRIP001 void SwEditShell::ChangeDBFields( const SvStringsDtor& rOldNames,
//STRIP001                                  const String& rNewName )
//STRIP001 {
//STRIP001  GetDoc()->ChangeDBFields( rOldNames, rNewName );
//STRIP001 }

//STRIP001 BOOL SwEditShell::RenameUserFields(const String& rOldName, const String& rNewName)
//STRIP001 {
//STRIP001  return GetDoc()->RenameUserFields(rOldName, rNewName);
//STRIP001 }


/*--------------------------------------------------------------------
    Beschreibung:  Alle Expression-Felder erneuern
 --------------------------------------------------------------------*/
//STRIP001 void SwEditShell::UpdateExpFlds(BOOL bCloseDB)
//STRIP001 {
//STRIP001  SET_CURR_SHELL( this );
//STRIP001  StartAllAction();
//STRIP001  GetDoc()->UpdateExpFlds();
//STRIP001  if (bCloseDB)
//STRIP001      GetDoc()->GetNewDBMgr()->CloseAll();    // Alle Datenbankverbindungen dichtmachen
//STRIP001  EndAllAction();
//STRIP001 }

/*N*/ SwNewDBMgr* SwEditShell::GetNewDBMgr() const
/*N*/ {
/*N*/   return GetDoc()->GetNewDBMgr();
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung: Feldtypen einfuegen
 --------------------------------------------------------------------*/
//STRIP001 SwFieldType* SwEditShell::InsertFldType(const SwFieldType& rFldType)
//STRIP001 {
//STRIP001  return GetDoc()->InsertFldType(rFldType);
//STRIP001 }

//STRIP001 void SwEditShell::LockExpFlds()
//STRIP001 {
//STRIP001  GetDoc()->LockExpFlds();
//STRIP001 }

//STRIP001 void SwEditShell::UnlockExpFlds()
//STRIP001 {
//STRIP001  GetDoc()->UnlockExpFlds();
//STRIP001 }

//STRIP001 BOOL SwEditShell::IsExpFldsLocked() const
//STRIP001 {
//STRIP001  return GetDoc()->IsExpFldsLocked();
//STRIP001 }

//STRIP001 void SwEditShell::SetFldUpdateFlags( USHORT eFlags )
//STRIP001 {
//STRIP001  GetDoc()->SetFldUpdateFlags( eFlags );
//STRIP001 }

//STRIP001 USHORT SwEditShell::GetFldUpdateFlags(BOOL bDocSettings) const
//STRIP001 {
//STRIP001  return bDocSettings ? GetDoc()->_GetFldUpdateFlags() : GetDoc()->GetFldUpdateFlags();
//STRIP001 }

//STRIP001 void SwEditShell::SetFixFields( BOOL bOnlyTimeDate,
//STRIP001                              const DateTime* pNewDateTime )
//STRIP001 {
//STRIP001  SET_CURR_SHELL( this );
//STRIP001  BOOL bUnLockView = !IsViewLocked();
//STRIP001  LockView( TRUE );
//STRIP001  StartAllAction();
//STRIP001  GetDoc()->SetFixFields( bOnlyTimeDate, pNewDateTime );
//STRIP001  EndAllAction();
//STRIP001  if( bUnLockView )
//STRIP001      LockView( FALSE );
//STRIP001 }

//STRIP001 void SwEditShell::SetLabelDoc( BOOL bFlag )
//STRIP001 {
//STRIP001  GetDoc()->SetLabelDoc( bFlag );
//STRIP001 }

/*N*/ BOOL SwEditShell::IsLabelDoc() const
/*N*/ {
/*N*/   return GetDoc()->IsLabelDoc();
/*N*/ }
/* -----------------------------21.12.99 12:53--------------------------------

 ---------------------------------------------------------------------------*/
//STRIP001 void SwEditShell::ChangeAuthorityData(const SwAuthEntry* pNewData)
//STRIP001 {
//STRIP001  GetDoc()->ChangeAuthorityData(pNewData);
//STRIP001 }
/* -----------------------------03.08.2001 12:04------------------------------

 ---------------------------------------------------------------------------*/
//STRIP001 BOOL SwEditShell::IsAnyDatabaseFieldInDoc()const
//STRIP001 {
//STRIP001     const SwFldTypes * pFldTypes = GetDoc()->GetFldTypes();
//STRIP001     const USHORT nSize = pFldTypes->Count();
//STRIP001     for(USHORT i = 0; i < nSize; ++i)
//STRIP001     {
//STRIP001         SwFieldType& rFldType = *((*pFldTypes)[i]);
//STRIP001         USHORT nWhich = rFldType.Which();
//STRIP001         if(IsUsed(rFldType))
//STRIP001         {
//STRIP001             switch(nWhich)
//STRIP001             {
//STRIP001                 case RES_DBFLD:
//STRIP001                 case RES_DBNEXTSETFLD:
//STRIP001                 case RES_DBNUMSETFLD:
//STRIP001                 case RES_DBSETNUMBERFLD:
//STRIP001                 {
//STRIP001                     SwClientIter aIter( rFldType );
//STRIP001                     SwFmtFld* pFld = (SwFmtFld*)aIter.First( TYPE( SwFmtFld ));
//STRIP001                     while(pFld)
//STRIP001                     {
//STRIP001                         if(pFld->IsFldInDoc())
//STRIP001                             return TRUE;
//STRIP001                         pFld = (SwFmtFld*)aIter.Next();
//STRIP001                     }
//STRIP001                 }
//STRIP001                 break;
//STRIP001             }
//STRIP001         }
//STRIP001     }
//STRIP001     return FALSE;
//STRIP001 }
/* -----------------28.11.2002 17:53-----------------
 *
 * --------------------------------------------------*/
//STRIP001 BOOL SwEditShell::IsFieldDataSourceAvailable(String& rUsedDataSource) const
//STRIP001 {
//STRIP001     const SwFldTypes * pFldTypes = GetDoc()->GetFldTypes();
//STRIP001     const USHORT nSize = pFldTypes->Count();
//STRIP001     Reference< XMultiServiceFactory > xMgr( ::legacy_binfilters::getLegacyProcessServiceFactory() );
//STRIP001     if( !xMgr.is() )
//STRIP001         return FALSE;
//STRIP001     Reference<XInterface> xInstance = xMgr->createInstance( OUString::createFromAscii( "com.sun.star.sdb.DatabaseContext" ));
//STRIP001     Reference<XNameAccess>  xDBContext = Reference<XNameAccess>(xInstance, UNO_QUERY) ;
//STRIP001     if(!xDBContext.is())
//STRIP001         return FALSE;
//STRIP001     for(USHORT i = 0; i < nSize; ++i)
//STRIP001     {
//STRIP001         SwFieldType& rFldType = *((*pFldTypes)[i]);
//STRIP001         USHORT nWhich = rFldType.Which();
//STRIP001         if(IsUsed(rFldType))
//STRIP001         {
//STRIP001             switch(nWhich)
//STRIP001             {
//STRIP001                 case RES_DBFLD:
//STRIP001                 {
//STRIP001                     SwClientIter aIter( rFldType );
//STRIP001                     SwFmtFld* pFld = (SwFmtFld*)aIter.First( TYPE( SwFmtFld ));
//STRIP001                     while(pFld)
//STRIP001                     {
//STRIP001                         if(pFld->IsFldInDoc())
//STRIP001                         {
//STRIP001                             const SwDBData& rData =
//STRIP001                                     ((SwDBFieldType*)pFld->GetFld()->GetTyp())->GetDBData();
//STRIP001                             if(xDBContext->hasByName(rData.sDataSource))
//STRIP001                                 return TRUE;
//STRIP001                             else
//STRIP001                             {
//STRIP001                                 rUsedDataSource = rData.sDataSource;
//STRIP001                                 return FALSE;
//STRIP001                             }
//STRIP001                         }
//STRIP001                         pFld = (SwFmtFld*)aIter.Next();
//STRIP001                     }
//STRIP001                 }
//STRIP001                 break;
//STRIP001             }
//STRIP001         }
//STRIP001     }
//STRIP001     return TRUE;
//STRIP001 }

}
