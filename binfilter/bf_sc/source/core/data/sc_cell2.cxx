/*************************************************************************
 *
 *  $RCSfile: sc_cell2.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:25:57 $
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

#ifdef PCH
#include "core_pch.hxx"
#endif

#pragma hdrstop

// INCLUDE ---------------------------------------------------------------

#ifndef _SV_MAPMOD_HXX //autogen
#include <vcl/mapmod.hxx>
#endif
#ifndef _EDITOBJ_HXX //autogen
#include <bf_svx/editobj.hxx>
#endif
#ifndef _EDITSTAT_HXX //autogen
#include <bf_svx/editstat.hxx>
#endif

#include "cell.hxx"
#include "compiler.hxx"
#include "document.hxx"
#include "rangenam.hxx"
#include "rechead.hxx"
#include "refupdat.hxx"
#include "scmatrix.hxx"
#include "editutil.hxx"
#include "chgtrack.hxx"
#include "indexmap.hxx"
namespace binfilter {


// STATIC DATA -----------------------------------------------------------

#pragma code_seg("SCSTATICS")

#ifdef USE_MEMPOOL
const USHORT nMemPoolEditCell = (0x1000 - 64) / sizeof(ScNoteCell);
/*N*/ IMPL_FIXEDMEMPOOL_NEWDEL( ScEditCell, nMemPoolEditCell, nMemPoolEditCell )
#endif

#pragma code_seg()

// -----------------------------------------------------------------------

/*N*/ ScEditCell::ScEditCell( ScDocument* pDocP ) :
/*N*/       ScBaseCell( CELLTYPE_EDIT ),
/*N*/       pData( NULL ),
/*N*/       pString( NULL ),
/*N*/       pDoc( pDocP )
/*N*/ {
/*N*/ }

/*N*/ ScEditCell::ScEditCell( const EditTextObject* pObject, ScDocument* pDocP,
/*N*/           const SfxItemPool* pFromPool )  :
/*N*/       ScBaseCell( CELLTYPE_EDIT ),
/*N*/       pString( NULL ),
/*N*/       pDoc( pDocP )
/*N*/ {
/*N*/   SetTextObject( pObject, pFromPool );
/*N*/ }

/*N*/ ScEditCell::ScEditCell( const ScEditCell& rEditCell, ScDocument* pDocP )  :
/*N*/       ScBaseCell( CELLTYPE_EDIT ),
/*N*/       pString( NULL ),
/*N*/       pDoc( pDocP )
/*N*/ {
/*N*/   SetTextObject( rEditCell.pData, rEditCell.pDoc->GetEditPool() );
/*N*/ }

/*N*/ ScEditCell::ScEditCell( SvStream& rStream, USHORT nVer, ScDocument* pDocP ) :
/*N*/       ScBaseCell( CELLTYPE_EDIT ),
/*N*/       pString( NULL ),
/*N*/       pDoc( pDocP )
/*N*/ {
/*N*/   if( nVer >= SC_DATABYTES2 )
/*N*/   {
/*N*/       BYTE cData;
/*N*/       rStream >> cData;
/*N*/       if( cData & 0x0F )
/*?*/           rStream.SeekRel( cData & 0x0F );
/*N*/   }
/*N*/   if ( nVer < SC_VERSION_EDITPOOL )
/*N*/   {   // jedes hat seinen eigenen Pool, dem neuen zuordnen
/*?*/       EditTextObject* pTmp = EditTextObject::Create( rStream );
/*?*/       SetTextObject( pTmp, NULL );
/*?*/       delete pTmp;
/*N*/   }
/*N*/   else
/*N*/       pData = EditTextObject::Create( rStream, pDoc->GetEditPool() );
/*N*/ }

/*N*/ ScEditCell::ScEditCell( const String& rString, ScDocument* pDocP )  :
/*N*/       ScBaseCell( CELLTYPE_EDIT ),
/*N*/       pString( NULL ),
/*N*/       pDoc( pDocP )
/*N*/ {
/*N*/   DBG_ASSERT( rString.Search('\n') != STRING_NOTFOUND ||
/*N*/               rString.Search(CHAR_CR) != STRING_NOTFOUND,
/*N*/               "EditCell mit einfachem Text !?!?" );
/*N*/
/*N*/   EditEngine& rEngine = pDoc->GetEditEngine();
/*N*/   rEngine.SetText( rString );
/*N*/   pData = rEngine.CreateTextObject();
/*N*/ }

/*N*/ ScEditCell::~ScEditCell()
/*N*/ {
/*N*/   delete pData;
/*N*/   delete pString;
/*N*/
/*N*/ #ifdef DBG_UTIL
/*N*/   eCellType = CELLTYPE_DESTROYED;
/*N*/ #endif
/*N*/ }

//STRIP001 ScBaseCell* ScEditCell::Clone( ScDocument* pNewDoc ) const
//STRIP001 {
//STRIP001  return new ScEditCell( *this, pNewDoc );
//STRIP001 }

//STRIP001 void ScEditCell::SetData( const EditTextObject* pObject,
//STRIP001          const SfxItemPool* pFromPool )
//STRIP001 {
//STRIP001  if ( pString )
//STRIP001  {
//STRIP001      delete pString;
//STRIP001      pString = NULL;
//STRIP001  }
//STRIP001  delete pData;
//STRIP001  SetTextObject( pObject, pFromPool );
//STRIP001 }

/*N*/ void ScEditCell::GetData( const EditTextObject*& rpObject ) const
/*N*/ {
/*N*/   rpObject = pData;
/*N*/ }

/*N*/ void ScEditCell::GetString( String& rString ) const
/*N*/ {
/*N*/   if ( pString )
/*N*/       rString = *pString;
/*N*/   else if ( pData )
/*N*/   {
/*N*/       // auch Text von URL-Feldern, Doc-Engine ist eine ScFieldEditEngine
/*N*/       EditEngine& rEngine = pDoc->GetEditEngine();
/*N*/       rEngine.SetText( *pData );
/*N*/       rString = ScEditUtil::GetSpaceDelimitedString(rEngine);     // space between paragraphs
/*N*/       // kurze Strings fuer Formeln merken
/*N*/       if ( rString.Len() < MAXSTRLEN )
/*N*/           ((ScEditCell*)this)->pString = new String( rString );   //! non-const
/*N*/   }
/*N*/   else
/*N*/       rString.Erase();
/*N*/ }

/*N*/ void ScEditCell::Save( SvStream& rStream ) const
/*N*/ {
/*N*/   DBG_ASSERT(pData,"StoreTextObject(NULL)");
/*N*/   rStream << (BYTE) 0x00;
/*N*/   if ( rStream.GetVersion() < SOFFICE_FILEFORMAT_50 )
/*N*/   {   // jedem seinen eigenen Pool
/*?*/       ScEditEngineDefaulter aEngine( EditEngine::CreatePool(), TRUE );
/*?*/       // #52396# richtige Metric schreiben
/*?*/       aEngine.SetRefMapMode( MAP_100TH_MM );
/*?*/       aEngine.SetText( *pData );
/*?*/       EditTextObject* pTmp = aEngine.CreateTextObject();
/*?*/       pTmp->Store( rStream );
/*?*/       delete pTmp;
/*N*/   }
/*N*/   else
/*N*/       pData->Store( rStream );
/*N*/ }

/*N*/ void ScEditCell::SetTextObject( const EditTextObject* pObject,
/*N*/           const SfxItemPool* pFromPool )
/*N*/ {
/*N*/   if ( pObject )
/*N*/   {
/*N*/       if ( pFromPool && pDoc->GetEditPool() == pFromPool )
/*N*/           pData = pObject->Clone();
/*N*/       else
/*N*/       {   //! anderer Pool
/*?*/           // Leider gibt es keinen anderen Weg, um den Pool umzuhaengen,
/*?*/       DBG_ASSERT(0, "STRIP"); //STRIP001  // als das Object durch eine entsprechende Engine zu schleusen..
//STRIP001 /*?*/            EditEngine& rEngine = pDoc->GetEditEngine();
//STRIP001 /*?*/            if ( pObject->HasOnlineSpellErrors() )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                ULONG nControl = rEngine.GetControlWord();
//STRIP001 /*?*/                const ULONG nSpellControl = EE_CNTRL_ONLINESPELLING | EE_CNTRL_ALLOWBIGOBJS;
//STRIP001 /*?*/                BOOL bNewControl = ( (nControl & nSpellControl) != nSpellControl );
//STRIP001 /*?*/                if ( bNewControl )
//STRIP001 /*?*/                    rEngine.SetControlWord( nControl | nSpellControl );
//STRIP001 /*?*/                rEngine.SetText( *pObject );
//STRIP001 /*?*/                pData = rEngine.CreateTextObject();
//STRIP001 /*?*/                if ( bNewControl )
//STRIP001 /*?*/                    rEngine.SetControlWord( nControl );
//STRIP001 /*?*/            }
//STRIP001 /*?*/            else
//STRIP001 /*?*/            {
//STRIP001 /*?*/                rEngine.SetText( *pObject );
//STRIP001 /*?*/                pData = rEngine.CreateTextObject();
//STRIP001 /*?*/            }
/*N*/       }
/*N*/   }
/*N*/   else
/*N*/       pData = NULL;
/*N*/ }

//---------------------------------------------------------------------

/*N*/ void ScFormulaCell::GetEnglishFormula( String& rFormula, BOOL bCompileXML ) const
/*N*/ {
/*N*/   //! mit GetFormula zusammenfassen !!!
/*N*/
/*N*/   if( pCode->GetError() && !pCode->GetLen() )
/*N*/   {
/*N*/       rFormula = ScGlobal::GetErrorString( pCode->GetError() ); return;
/*N*/   }
/*N*/   else if( cMatrixFlag == MM_REFERENCE )
/*N*/   {
/*N*/       // Referenz auf eine andere Zelle, die eine Matrixformel enthaelt
/*N*/       pCode->Reset();
/*N*/       ScToken* p = pCode->GetNextReferenceRPN();
/*N*/       if( p )
/*N*/       {
/*N*/           ScBaseCell* pCell;
/*N*/           SingleRefData& rRef = p->GetSingleRef();
/*N*/           rRef.CalcAbsIfRel( aPos );
/*N*/           if ( rRef.Valid() )
/*N*/               pCell = pDocument->GetCell( ScAddress( rRef.nCol,
/*N*/                   rRef.nRow, rRef.nTab ) );
/*N*/           else
/*N*/               pCell = NULL;
/*N*/           if (pCell && pCell->GetCellType() == CELLTYPE_FORMULA)
/*N*/           {
/*N*/               ((ScFormulaCell*)pCell)->GetEnglishFormula(rFormula, bCompileXML);
/*N*/               return;
/*N*/           }
/*N*/           else
/*N*/           {
/*N*/               ScCompiler aComp( pDocument, aPos, *pCode );
/*N*/               aComp.SetCompileEnglish( TRUE );
/*N*/               aComp.SetCompileXML( bCompileXML );
/*N*/               aComp.CreateStringFromTokenArray( rFormula );
/*N*/           }
/*N*/       }
/*N*/       else
/*N*/       {
/*N*/           DBG_ERROR("ScFormulaCell::GetEnglishFormula: Keine Matrix");
/*N*/       }
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       ScCompiler aComp( pDocument, aPos, *pCode );
/*N*/       aComp.SetCompileEnglish( TRUE );
/*N*/       aComp.SetCompileXML( bCompileXML );
/*N*/       aComp.CreateStringFromTokenArray( rFormula );
/*N*/   }
/*N*/
/*N*/   rFormula.Insert( '=',0 );
/*N*/   if( cMatrixFlag )
/*N*/   {
/*N*/       rFormula.Insert('{', 0);
/*N*/       rFormula += '}';
/*N*/   }
/*N*/ }

/*N*/ void ScFormulaCell::GetEnglishFormula( ::rtl::OUStringBuffer& rBuffer, BOOL bCompileXML ) const
/*N*/ {
/*N*/   //! mit GetFormula zusammenfassen !!!
/*N*/
/*N*/   if( pCode->GetError() && !pCode->GetLen() )
/*N*/   {
/*?*/       rBuffer = ::rtl::OUStringBuffer(ScGlobal::GetErrorString( pCode->GetError() )); return;
/*N*/   }
/*N*/   else if( cMatrixFlag == MM_REFERENCE )
/*N*/   {
/*?*/       // Referenz auf eine andere Zelle, die eine Matrixformel enthaelt
/*?*/       pCode->Reset();
/*?*/       ScToken* p = pCode->GetNextReferenceRPN();
/*?*/       if( p )
/*?*/       {
/*?*/           ScBaseCell* pCell;
/*?*/           SingleRefData& rRef = p->GetSingleRef();
/*?*/           rRef.CalcAbsIfRel( aPos );
/*?*/           if ( rRef.Valid() )
/*?*/               pCell = pDocument->GetCell( ScAddress( rRef.nCol,
/*?*/                   rRef.nRow, rRef.nTab ) );
/*?*/           else
/*?*/               pCell = NULL;
/*?*/           if (pCell && pCell->GetCellType() == CELLTYPE_FORMULA)
/*?*/           {
/*?*/               ((ScFormulaCell*)pCell)->GetEnglishFormula(rBuffer, bCompileXML);
/*?*/               return;
/*?*/           }
/*?*/           else
/*?*/           {
/*?*/               ScCompiler aComp( pDocument, aPos, *pCode );
/*?*/               aComp.SetCompileEnglish( TRUE );
/*?*/               aComp.SetCompileXML( bCompileXML );
/*?*/               aComp.CreateStringFromTokenArray( rBuffer );
/*?*/           }
/*?*/       }
/*?*/       else
/*?*/       {
/*?*/           DBG_ERROR("ScFormulaCell::GetEnglishFormula: Keine Matrix");
/*?*/       }
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       ScCompiler aComp( pDocument, aPos, *pCode );
/*N*/       aComp.SetCompileEnglish( TRUE );
/*N*/       aComp.SetCompileXML( bCompileXML );
/*N*/       aComp.CreateStringFromTokenArray( rBuffer );
/*N*/   }
/*N*/
/*N*/   sal_Unicode ch('=');
/*N*/   rBuffer.insert( 0, &ch, 1 );
/*N*/   if( cMatrixFlag )
/*N*/   {
/*N*/       sal_Unicode ch2('{');
/*N*/       rBuffer.insert(0, &ch2, 1);
/*N*/       rBuffer.append(sal_Unicode('}'));
/*N*/   }
/*N*/ }

/*N*/ BOOL ScFormulaCell::IsValue()
/*N*/ {
/*N*/   if (IsDirtyOrInTableOpDirty() && pDocument->GetAutoCalc())
/*N*/       Interpret();
/*N*/   return bIsValue;
/*N*/ }

/*N*/ double ScFormulaCell::GetValue()
/*N*/ {
/*N*/   if (IsDirtyOrInTableOpDirty() && pDocument->GetAutoCalc())
/*?*/       Interpret();
/*N*/   if ( !pCode->GetError() || pCode->GetError() == errDoubleRef)
/*N*/       return nErgValue;
/*N*/   return 0.0;
/*N*/ }

/*N*/ double ScFormulaCell::GetValueAlways()
/*N*/ {
/*N*/   // for goal seek: return result value even if error code is set
/*N*/
/*N*/   if (IsDirtyOrInTableOpDirty() && pDocument->GetAutoCalc())
/*N*/       Interpret();
/*N*/   return nErgValue;
/*N*/ }

/*N*/ void ScFormulaCell::GetString( String& rString )
/*N*/ {
/*N*/   if (IsDirtyOrInTableOpDirty() && pDocument->GetAutoCalc())
/*?*/       Interpret();
/*N*/   if ( !pCode->GetError() || pCode->GetError() == errDoubleRef)
/*N*/       rString = aErgString;
/*N*/   else
/*?*/       rString.Erase();
/*N*/ }

/*N*/ void ScFormulaCell::GetMatrix(ScMatrix** ppMat)
/*N*/ {
/*N*/   if ( pDocument->GetAutoCalc() )
/*N*/   {
/*N*/       // war !bDirty gespeichert aber zugehoerige Matrixzelle bDirty?
/*N*/       // => wir brauchen pMatrix
/*N*/       if ( !pMatrix && cMatrixFlag == MM_FORMULA )
/*N*/           bDirty = TRUE;
/*N*/       if ( IsDirtyOrInTableOpDirty() )
/*N*/           Interpret();
/*N*/   }
/*N*/   if (!pCode->GetError())
/*N*/       *ppMat = pMatrix;
/*N*/   else
/*N*/       *ppMat = NULL;
/*N*/ }

/*N*/ BOOL ScFormulaCell::GetMatrixOrigin( ScAddress& rPos ) const
/*N*/ {
/*N*/   switch ( cMatrixFlag )
/*N*/   {
/*N*/       case MM_FORMULA :
/*N*/           rPos = aPos;
/*N*/           return TRUE;
/*N*/       break;
/*N*/       case MM_REFERENCE :
/*N*/       {
/*N*/           pCode->Reset();
/*N*/           ScToken* t = pCode->GetNextReferenceRPN();
/*N*/           if( t )
/*N*/           {
/*N*/               SingleRefData& rRef = t->GetSingleRef();
/*N*/               rRef.CalcAbsIfRel( aPos );
/*N*/               if ( rRef.Valid() )
/*N*/               {
/*N*/                   rPos.Set( rRef.nCol, rRef.nRow, rRef.nTab );
/*N*/                   return TRUE;
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/       break;
/*N*/   }
/*N*/   return FALSE;
/*N*/ }


/*
 Edge-Values:

   8
 4   16
   2

 innerhalb: 1
 ausserhalb: 0
 (reserviert: offen: 32)
 */

/*N*/ USHORT ScFormulaCell::GetMatrixEdge( ScAddress& rOrgPos )
/*N*/ {
/*N*/   switch ( cMatrixFlag )
/*N*/   {
/*N*/       case MM_FORMULA :
/*N*/       case MM_REFERENCE :
/*N*/       {
/*N*/           static USHORT nC, nR;
/*N*/           ScAddress aOrg;
/*N*/           if ( !GetMatrixOrigin( aOrg ) )
/*N*/               return 0;               // dumm gelaufen..
/*N*/           if ( aOrg != rOrgPos )
/*N*/           {   // erstes Mal oder andere Matrix als letztes Mal
/*N*/               rOrgPos = aOrg;
/*N*/               ScFormulaCell* pFCell;
/*N*/               if ( cMatrixFlag == MM_REFERENCE )
/*N*/                   pFCell = (ScFormulaCell*) pDocument->GetCell( aOrg );
/*N*/               else
/*N*/                   pFCell = this;      // this MM_FORMULA
/*N*/               // this gibt's nur einmal, kein Vergleich auf pFCell==this
/*N*/               if ( pFCell && pFCell->GetCellType() == CELLTYPE_FORMULA
/*N*/                 && pFCell->cMatrixFlag == MM_FORMULA )
/*N*/               {
/*N*/                   pFCell->GetMatColsRows( nC, nR );
/*N*/                   if ( nC == 0 || nR == 0 )
/*N*/                   {   // aus altem Dokument geladen, neu erzeugen
/*?*/                       nC = nR = 1;
/*?*/                       ScAddress aTmpOrg;
/*?*/                       ScBaseCell* pCell;
/*?*/                       ScAddress aAdr( aOrg );
/*?*/                       aAdr.IncCol();
/*?*/                       BOOL bCont = TRUE;
/*?*/                       do
/*?*/                       {
/*?*/                           pCell = pDocument->GetCell( aAdr );
/*?*/                           if ( pCell && pCell->GetCellType() == CELLTYPE_FORMULA
/*?*/                             && ((ScFormulaCell*)pCell)->cMatrixFlag == MM_REFERENCE
/*?*/                             && GetMatrixOrigin( aTmpOrg ) && aTmpOrg == aOrg )
/*?*/                           {
/*?*/                               nC++;
/*?*/                               aAdr.IncCol();
/*?*/                           }
/*?*/                           else
/*?*/                               bCont = FALSE;
/*?*/                       } while ( bCont );
/*?*/                       aAdr = aOrg;
/*?*/                       aAdr.IncRow();
/*?*/                       bCont = TRUE;
/*?*/                       do
/*?*/                       {
/*?*/                           pCell = pDocument->GetCell( aAdr );
/*?*/                           if ( pCell && pCell->GetCellType() == CELLTYPE_FORMULA
/*?*/                             && ((ScFormulaCell*)pCell)->cMatrixFlag == MM_REFERENCE
/*?*/                             && GetMatrixOrigin( aTmpOrg ) && aTmpOrg == aOrg )
/*?*/                           {
/*?*/                               nR++;
/*?*/                               aAdr.IncRow();
/*?*/                           }
/*?*/                           else
/*?*/                               bCont = FALSE;
/*?*/                       } while ( bCont );
/*?*/                       pFCell->SetMatColsRows( nC, nR );
/*N*/                   }
/*N*/               }
/*N*/               else
/*N*/               {
/*N*/ #ifndef PRODUCT
/*N*/                   String aTmp;
/*N*/                   ByteString aMsg( "broken Matrix, no MatFormula at origin, Pos: " );
/*N*/                   aPos.Format( aTmp, SCA_VALID_COL | SCA_VALID_ROW, pDocument );
/*N*/                   aMsg += ByteString( aTmp, RTL_TEXTENCODING_ASCII_US );
/*N*/                   aMsg += ", MatOrg: ";
/*N*/                   aOrg.Format( aTmp, SCA_VALID_COL | SCA_VALID_ROW, pDocument );
/*N*/                   aMsg += ByteString( aTmp, RTL_TEXTENCODING_ASCII_US );
/*N*/                   DBG_ERRORFILE( aMsg.GetBuffer() );
/*N*/ #endif
/*N*/                   return 0;           // bad luck ...
/*N*/               }
/*N*/           }
/*N*/           // here we are, healthy and clean, somewhere in between
/*N*/           short dC = aPos.Col() - aOrg.Col();
/*N*/           short dR = aPos.Row() - aOrg.Row();
/*N*/           USHORT nEdges = 0;
/*N*/           if ( dC >= 0 && dR >= 0 && dC < nC && dR < nR )
/*N*/           {
/*N*/               if ( dC == 0 )
/*N*/                   nEdges |= 4;            // linke Kante
/*N*/               if ( dC+1 == nC )
/*N*/                   nEdges |= 16;           // rechte Kante
/*N*/               if ( dR == 0 )
/*N*/                   nEdges |= 8;            // obere Kante
/*N*/               if ( dR+1 == nR )
/*N*/                   nEdges |= 2;            // untere Kante
/*N*/               if ( !nEdges )
/*N*/                   nEdges = 1;             // mittendrin
/*N*/           }
/*N*/ #ifndef PRODUCT
/*N*/           else
/*N*/           {
/*?*/               String aTmp;
/*?*/               ByteString aMsg( "broken Matrix, Pos: " );
/*?*/               aPos.Format( aTmp, SCA_VALID_COL | SCA_VALID_ROW, pDocument );
/*?*/               aMsg += ByteString( aTmp, RTL_TEXTENCODING_ASCII_US );
/*?*/               aMsg += ", MatOrg: ";
/*?*/               aOrg.Format( aTmp, SCA_VALID_COL | SCA_VALID_ROW, pDocument );
/*?*/               aMsg += ByteString( aTmp, RTL_TEXTENCODING_ASCII_US );
/*?*/               aMsg += ", MatCols: ";
/*?*/               aMsg += ByteString::CreateFromInt32( nC );
/*?*/               aMsg += ", MatRows: ";
/*?*/               aMsg += ByteString::CreateFromInt32( nR );
/*?*/               aMsg += ", DiffCols: ";
/*?*/               aMsg += ByteString::CreateFromInt32( dC );
/*?*/               aMsg += ", DiffRows: ";
/*?*/               aMsg += ByteString::CreateFromInt32( dR );
/*?*/               DBG_ERRORFILE( aMsg.GetBuffer() );
/*N*/           }
/*N*/ #endif
/*N*/           return nEdges;
/*N*/           break;
/*N*/       }
/*N*/       default:
/*N*/           return 0;
/*N*/   }
/*N*/ }

/*N*/ USHORT ScFormulaCell::GetErrCode()
/*N*/ {
/*N*/   if (IsDirtyOrInTableOpDirty() && pDocument->GetAutoCalc())
/*N*/       Interpret();
/*N*/   return pCode->GetError();
/*N*/ }

/*N*/  BOOL ScFormulaCell::HasOneReference( ScRange& r ) const
/*N*/  {
/*N*/   pCode->Reset();
/*N*/   ScToken* p = pCode->GetNextReferenceRPN();
/*N*/   if( p && !pCode->GetNextReferenceRPN() )        // nur eine!
/*N*/   {
/*N*/       p->CalcAbsIfRel( aPos );
/*N*/       SingleDoubleRefProvider aProv( *p );
/*N*/       r.aStart.Set( aProv.Ref1.nCol,
/*N*/                     aProv.Ref1.nRow,
/*N*/                     aProv.Ref1.nTab );
/*N*/       r.aEnd.Set( aProv.Ref2.nCol,
/*N*/                   aProv.Ref2.nRow,
/*N*/                   aProv.Ref2.nTab );
/*N*/       return TRUE;
/*N*/   }
/*N*/   else
/*N*/       return FALSE;
/*N*/  }

/*N*/  BOOL ScFormulaCell::HasRelNameReference() const
/*N*/  {
/*N*/   pCode->Reset();
/*N*/   for( ScToken* t = pCode->GetNextReferenceRPN(); t;
/*N*/                 t = pCode->GetNextReferenceRPN() )
/*N*/   {
/*N*/       if ( t->GetSingleRef().IsRelName() ||
/*N*/               (t->GetType() == svDoubleRef &&
/*N*/               t->GetDoubleRef().Ref2.IsRelName()) )
/*N*/           return TRUE;
/*N*/   }
/*N*/   return FALSE;
/*N*/  }

/*N*/  BOOL ScFormulaCell::HasDBArea() const
/*N*/  {
/*N*/   pCode->Reset();
/*N*/   return (pCode->GetNextDBArea() != NULL);
/*N*/  }

/*N*/  BOOL ScFormulaCell::HasColRowName() const
/*N*/  {
/*N*/   pCode->Reset();
/*N*/   return (pCode->GetNextColRowName() != NULL);
/*N*/  }

/*N*/  void ScFormulaCell::UpdateReference(UpdateRefMode eUpdateRefMode,
/*N*/                                   const ScRange& r,
/*N*/                                   short nDx, short nDy, short nDz,
/*N*/                                   ScDocument* pUndoDoc )
/*N*/  {DBG_ASSERT(0, "STRIP");//STRIP001
//STRIP001 /*N*/    USHORT nCol1 = r.aStart.Col();
//STRIP001 /*N*/    USHORT nRow1 = r.aStart.Row();
//STRIP001 /*N*/    USHORT nTab1 = r.aStart.Tab();
//STRIP001 /*N*/    USHORT nCol2 = r.aEnd.Col();
//STRIP001 /*N*/    USHORT nRow2 = r.aEnd.Row();
//STRIP001 /*N*/    USHORT nTab2 = r.aEnd.Tab();
//STRIP001 /*N*/    USHORT nCol = aPos.Col();
//STRIP001 /*N*/    USHORT nRow = aPos.Row();
//STRIP001 /*N*/    USHORT nTab = aPos.Tab();
//STRIP001 /*N*/      ScAddress aUndoPos( aPos );         // position for undo cell in pUndoDoc
//STRIP001 /*N*/      ScAddress aOldPos( aPos );
//STRIP001 /*N*/  //  BOOL bPosChanged = FALSE;           // ob diese Zelle bewegt wurde
//STRIP001 /*N*/    BOOL bIsInsert = FALSE;
//STRIP001 /*N*/    if (eUpdateRefMode == URM_INSDEL)
//STRIP001 /*N*/    {
//STRIP001 /*N*/        bIsInsert = (nDx >= 0 && nDy >= 0 && nDz >= 0);
//STRIP001 /*N*/        if ( nDx && nRow >= nRow1 && nRow <= nRow2 &&
//STRIP001 /*N*/            nTab >= nTab1 && nTab <= nTab2 )
//STRIP001 /*N*/        {
//STRIP001 /*N*/            if (nCol >= nCol1)
//STRIP001 /*N*/            {
//STRIP001 /*N*/                nCol += nDx;
//STRIP001 /*N*/                if ((short) nCol < 0)
//STRIP001 /*N*/                    nCol = 0;
//STRIP001 /*N*/                else if ( nCol > MAXCOL )
//STRIP001 /*N*/                    nCol = MAXCOL;
//STRIP001 /*N*/                aPos.SetCol( nCol );
//STRIP001 /*N*/  //                bPosChanged = TRUE;
//STRIP001 /*N*/            }
//STRIP001 /*N*/        }
//STRIP001 /*N*/        if ( nDy && nCol >= nCol1 && nCol <= nCol2 &&
//STRIP001 /*N*/            nTab >= nTab1 && nTab <= nTab2 )
//STRIP001 /*N*/        {
//STRIP001 /*N*/            if (nRow >= nRow1)
//STRIP001 /*N*/            {
//STRIP001 /*N*/                nRow += nDy;
//STRIP001 /*N*/                if ((short) nRow < 0)
//STRIP001 /*N*/                    nRow = 0;
//STRIP001 /*N*/                else if ( nRow > MAXROW )
//STRIP001 /*N*/                    nRow = MAXROW;
//STRIP001 /*N*/                aPos.SetRow( nRow );
//STRIP001 /*N*/  //                bPosChanged = TRUE;
//STRIP001 /*N*/            }
//STRIP001 /*N*/        }
//STRIP001 /*N*/        if ( nDz && nCol >= nCol1 && nCol <= nCol2 &&
//STRIP001 /*N*/            nRow >= nRow1 && nRow <= nRow2 )
//STRIP001 /*N*/        {
//STRIP001 /*N*/            if (nTab >= nTab1)
//STRIP001 /*N*/            {
//STRIP001 /*N*/                USHORT nMaxTab = pDocument->GetTableCount() - 1;
//STRIP001 /*N*/                nTab += nDz;
//STRIP001 /*N*/                if ((short) nTab < 0)
//STRIP001 /*N*/                    nTab = 0;
//STRIP001 /*N*/                else if ( nTab > nMaxTab )
//STRIP001 /*N*/                    nTab = nMaxTab;
//STRIP001 /*N*/                aPos.SetTab( nTab );
//STRIP001 /*N*/  //                bPosChanged = TRUE;
//STRIP001 /*N*/            }
//STRIP001 /*N*/        }
//STRIP001 /*N*/    }
//STRIP001 /*N*/    else if ( r.In( aPos ) )
//STRIP001 /*N*/    {
//STRIP001 /*N*/        aOldPos.Set( nCol - nDx, nRow - nDy, nTab - nDz );
//STRIP001 /*N*/  //        bPosChanged = TRUE;
//STRIP001 /*N*/    }
//STRIP001 /*N*/
//STRIP001 /*N*/    BOOL bHasRefs = FALSE;
//STRIP001 /*N*/      BOOL bHasColRowNames = FALSE;
//STRIP001 /*N*/    BOOL bOnRefMove = FALSE;
//STRIP001 /*N*/    if ( !pDocument->IsClipOrUndo() )
//STRIP001 /*N*/    {
//STRIP001 /*N*/        pCode->Reset();
//STRIP001 /*N*/        bHasRefs = (pCode->GetNextReferenceRPN() != NULL);
//STRIP001 /*N*/          if ( !bHasRefs || eUpdateRefMode == URM_COPY )
//STRIP001 /*N*/          {
//STRIP001 /*N*/              pCode->Reset();
//STRIP001 /*N*/              bHasColRowNames = (pCode->GetNextColRowName() != NULL);
//STRIP001 /*N*/              bHasRefs = bHasRefs || bHasColRowNames;
//STRIP001 /*N*/          }
//STRIP001 /*N*/        bOnRefMove = pCode->IsRecalcModeOnRefMove();
//STRIP001 /*N*/    }
//STRIP001 /*N*/    if( bHasRefs || bOnRefMove )
//STRIP001 /*N*/    {
//STRIP001 /*N*/        ScTokenArray* pOld = pUndoDoc ? pCode->Clone() : NULL;
//STRIP001 /*N*/        BOOL bValChanged;
//STRIP001 /*N*/        ScRangeData* pRangeData;
//STRIP001 /*N*/        BOOL bRangeModified;            // beliebiger Range (nicht nur shared Formula)
//STRIP001 /*N*/        if ( bHasRefs )
//STRIP001 /*N*/        {
//STRIP001 /*N*/            ScCompiler aComp(pDocument, aPos, *pCode);
//STRIP001 /*N*/            pRangeData = aComp.UpdateReference(eUpdateRefMode, aOldPos, r,
//STRIP001 /*N*/                                             nDx, nDy, nDz,
//STRIP001 /*N*/                                             bValChanged);
//STRIP001 /*N*/            bRangeModified = aComp.HasModifiedRange();
//STRIP001 /*N*/        }
//STRIP001 /*N*/        else
//STRIP001 /*N*/        {
//STRIP001 /*N*/            bValChanged = FALSE;
//STRIP001 /*N*/            pRangeData = NULL;
//STRIP001 /*N*/            bRangeModified = FALSE;
//STRIP001 /*N*/        }
//STRIP001 /*N*/        if ( bOnRefMove )
//STRIP001 /*N*/            bOnRefMove = (bValChanged || (aPos != aOldPos));
//STRIP001 /*N*/            // Zelle referiert sich evtl. selbst, z.B. ocColumn, ocRow ohne Parameter
//STRIP001 /*N*/
//STRIP001 /*N*/        BOOL bColRowNameCompile, bHasRelName, bNewListening, bNewRelName,
//STRIP001 /*N*/              bInDeleteUndo;
//STRIP001 /*N*/        if ( bHasRefs )
//STRIP001 /*N*/        {
//STRIP001 /*N*/            // Bei Insert muessen ColRowNames neu kompiliert werden, falls genau
//STRIP001 /*N*/            // am Beginn des Bereiches inserted wird.
//STRIP001 /*N*/            bColRowNameCompile =
//STRIP001 /*N*/                (eUpdateRefMode == URM_INSDEL && (nDx > 0 || nDy > 0));
//STRIP001 /*N*/            if ( bColRowNameCompile )
//STRIP001 /*N*/            {
//STRIP001 /*N*/                bColRowNameCompile = FALSE;
//STRIP001 /*N*/                ScToken* t;
//STRIP001 /*N*/                ScRangePairList* pColList = pDocument->GetColNameRanges();
//STRIP001 /*N*/                ScRangePairList* pRowList = pDocument->GetRowNameRanges();
//STRIP001 /*N*/                pCode->Reset();
//STRIP001 /*N*/                while ( !bColRowNameCompile && (t = pCode->GetNextColRowName()) )
//STRIP001 /*N*/                {
//STRIP001 /*N*/                    SingleRefData& rRef = t->GetSingleRef();
//STRIP001 /*N*/                    if ( nDy > 0 && rRef.IsColRel() )
//STRIP001 /*N*/                    {   // ColName
//STRIP001 /*N*/                        rRef.CalcAbsIfRel( aPos );
//STRIP001 /*N*/                        ScAddress aAdr( rRef.nCol, rRef.nRow, rRef.nTab );
//STRIP001 /*N*/                        ScRangePair* pR = pColList->Find( aAdr );
//STRIP001 /*N*/                        if ( pR )
//STRIP001 /*N*/                        {   // definiert
//STRIP001 /*N*/                            if ( pR->GetRange(1).aStart.Row() == nRow1 )
//STRIP001 /*N*/                                bColRowNameCompile = TRUE;
//STRIP001 /*N*/                        }
//STRIP001 /*N*/                        else
//STRIP001 /*N*/                        {   // on the fly
//STRIP001 /*N*/                            if ( rRef.nRow + 1 == nRow1 )
//STRIP001 /*N*/                                bColRowNameCompile = TRUE;
//STRIP001 /*N*/                        }
//STRIP001 /*N*/                    }
//STRIP001 /*N*/                    if ( nDx > 0 && rRef.IsRowRel() )
//STRIP001 /*N*/                    {   // RowName
//STRIP001 /*N*/                        rRef.CalcAbsIfRel( aPos );
//STRIP001 /*N*/                        ScAddress aAdr( rRef.nCol, rRef.nRow, rRef.nTab );
//STRIP001 /*N*/                        ScRangePair* pR = pRowList->Find( aAdr );
//STRIP001 /*N*/                        if ( pR )
//STRIP001 /*N*/                        {   // definiert
//STRIP001 /*N*/                            if ( pR->GetRange(1).aStart.Col() == nCol1 )
//STRIP001 /*N*/                                bColRowNameCompile = TRUE;
//STRIP001 /*N*/                        }
//STRIP001 /*N*/                        else
//STRIP001 /*N*/                        {   // on the fly
//STRIP001 /*N*/                            if ( rRef.nCol + 1 == nCol1 )
//STRIP001 /*N*/                                bColRowNameCompile = TRUE;
//STRIP001 /*N*/                        }
//STRIP001 /*N*/                    }
//STRIP001 /*N*/                }
//STRIP001 /*N*/            }
//STRIP001 /*N*/            else if ( eUpdateRefMode == URM_MOVE )
//STRIP001 /*N*/            {   // bei Move/D&D neu kompilieren wenn ColRowName verschoben wurde
//STRIP001 /*N*/                // oder diese Zelle auf einen zeigt und verschoben wurde
//STRIP001 /*N*/                bColRowNameCompile = bCompile;      // evtl. aus Copy-ctor
//STRIP001 /*N*/                if ( !bColRowNameCompile )
//STRIP001 /*N*/                {
//STRIP001 /*N*/                    BOOL bMoved = (aPos != aOldPos);
//STRIP001 /*N*/                    pCode->Reset();
//STRIP001 /*N*/                    ScToken* t = pCode->GetNextColRowName();
//STRIP001 /*N*/                    if ( t && bMoved )
//STRIP001 /*N*/                        bColRowNameCompile = TRUE;
//STRIP001 /*N*/                    while ( t && !bColRowNameCompile )
//STRIP001 /*N*/                    {
//STRIP001 /*N*/                        SingleRefData& rRef = t->GetSingleRef();
//STRIP001 /*N*/                        rRef.CalcAbsIfRel( aPos );
//STRIP001 /*N*/                        if ( rRef.Valid() )
//STRIP001 /*N*/                        {
//STRIP001 /*N*/                            ScAddress aAdr( rRef.nCol, rRef.nRow, rRef.nTab );
//STRIP001 /*N*/                            if ( r.In( aAdr ) )
//STRIP001 /*N*/                                bColRowNameCompile = TRUE;
//STRIP001 /*N*/                        }
//STRIP001 /*N*/                        t = pCode->GetNextColRowName();
//STRIP001 /*N*/                    }
//STRIP001 /*N*/                }
//STRIP001 /*N*/            }
//STRIP001 /*N*/              else if ( eUpdateRefMode == URM_COPY && bHasColRowNames && bValChanged )
//STRIP001 /*N*/              {
//STRIP001 /*N*/                  bColRowNameCompile = TRUE;
//STRIP001 /*N*/              }
//STRIP001 /*N*/            ScChangeTrack* pChangeTrack = pDocument->GetChangeTrack();
//STRIP001 /*N*/            if ( pChangeTrack && pChangeTrack->IsInDeleteUndo() )
//STRIP001 /*N*/                bInDeleteUndo = TRUE;
//STRIP001 /*N*/            else
//STRIP001 /*N*/                bInDeleteUndo = FALSE;
//STRIP001 /*N*/            // Referenz geaendert und neues Listening noetig?
//STRIP001 /*N*/            // ausser Insert/Delete ohne Spezialitaeten
//STRIP001 /*N*/            bNewListening = ( bRangeModified || pRangeData || bColRowNameCompile
//STRIP001 /*N*/                || (bValChanged && (eUpdateRefMode != URM_INSDEL ||
//STRIP001 /*N*/                    bInDeleteUndo)) );
//STRIP001 /*N*/            bHasRelName = HasRelNameReference();
//STRIP001 /*N*/            bNewRelName = (bHasRelName && eUpdateRefMode != URM_COPY);
//STRIP001 /*N*/            if ( bNewListening )
//STRIP001 /*N*/                  EndListeningTo( pDocument, 0, pOld, aOldPos );
//STRIP001 /*N*/            else if ( bNewRelName )
//STRIP001 /*N*/                  EndListeningTo( pDocument, SC_LISTENING_NAMES_REL, pOld, aOldPos );
//STRIP001 /*N*/                // RelNameRefs werden immer mitverschoben
//STRIP001 /*N*/        }
//STRIP001 /*N*/        else
//STRIP001 /*N*/        {
//STRIP001 /*N*/            bColRowNameCompile = bHasRelName = bNewListening = bNewRelName =
//STRIP001 /*N*/                  bInDeleteUndo = FALSE;
//STRIP001 /*N*/        }
//STRIP001 /*N*/
//STRIP001 /*N*/        BOOL bNeedDirty;
//STRIP001 /*N*/        // NeedDirty bei Aenderungen ausser Copy und Move/Insert ohne RelNames
//STRIP001 /*N*/        if ( bRangeModified || pRangeData || bColRowNameCompile
//STRIP001 /*N*/          || (bValChanged && eUpdateRefMode != URM_COPY
//STRIP001 /*N*/                && (eUpdateRefMode != URM_MOVE || bHasRelName)
//STRIP001 /*N*/                && (!bIsInsert || bHasRelName || bInDeleteUndo)) || bOnRefMove )
//STRIP001 /*N*/            bNeedDirty = TRUE;
//STRIP001 /*N*/        else
//STRIP001 /*N*/            bNeedDirty = FALSE;
//STRIP001 /*N*/          if (pUndoDoc && (bValChanged || pRangeData || bOnRefMove))
//STRIP001 /*N*/          {
//STRIP001 /*N*/              //  Copy the cell to aUndoPos, which is its current position in the document,
//STRIP001 /*N*/              //  so this works when UpdateReference is called before moving the cells
//STRIP001 /*N*/              //  (InsertCells/DeleteCells - aPos is changed above) as well as when UpdateReference
//STRIP001 /*N*/              //  is called after moving the cells (MoveBlock/PasteFromClip - aOldPos is changed).
//STRIP001 /*N*/
//STRIP001 /*N*/              ScFormulaCell* pFCell = new ScFormulaCell( pUndoDoc, aUndoPos, pOld, cMatrixFlag );
//STRIP001 /*N*/              pFCell->nErgValue = MINDOUBLE;      // to recognize it as changed later (Cut/Paste!)
//STRIP001 /*N*/              pUndoDoc->PutCell( aUndoPos, pFCell );
//STRIP001 /*N*/          }
//STRIP001 /*N*/          bValChanged = FALSE;
//STRIP001 /*N*/          if ( pRangeData )
//STRIP001 /*N*/          {   // Replace shared formula with own formula
//STRIP001 /*N*/              pDocument->RemoveFromFormulaTree( this );   // update formula count
//STRIP001 /*N*/              delete pCode;
//STRIP001 /*N*/              pCode = pRangeData->GetCode()->Clone();
//STRIP001 /*N*/              pCode->SetReplacedSharedFormula( TRUE );
//STRIP001 /*N*/              ScCompiler aComp2(pDocument, aPos, *pCode);
//STRIP001 /*N*/              aComp2.MoveRelWrap();
//STRIP001 /*N*/              aComp2.UpdateSharedFormulaReference( eUpdateRefMode, aOldPos, r,
//STRIP001 /*N*/                  nDx, nDy, nDz );
//STRIP001 /*N*/              bValChanged = TRUE;
//STRIP001 /*N*/              bNeedDirty = TRUE;
//STRIP001 /*N*/          }
//STRIP001 /*N*/          if ( ( bCompile = (bCompile || bValChanged || bRangeModified || bColRowNameCompile) ) != 0 )
//STRIP001 /*N*/          {
//STRIP001 /*N*/              CompileTokenArray( bNewListening ); // kein Listening
//STRIP001 /*N*/              bNeedDirty = TRUE;
//STRIP001 /*N*/          }
//STRIP001 /*N*/          if ( !bInDeleteUndo )
//STRIP001 /*N*/          {   // In ChangeTrack Delete-Reject listeners are established in
//STRIP001 /*N*/              // InsertCol/InsertRow
//STRIP001 /*N*/              if ( bNewListening )
//STRIP001 /*N*/              {
//STRIP001 /*N*/                  if ( pRangeData && eUpdateRefMode == URM_INSDEL )
//STRIP001 /*N*/                  {
//STRIP001 /*N*/                      // All replaced shared formula listeners have to be
//STRIP001 /*N*/                      // established after an Insert or Delete. Do nothing here.
//STRIP001 /*N*/                  }
//STRIP001 /*N*/                  else if ( eUpdateRefMode == URM_INSDEL && !bIsInsert )
//STRIP001 /*N*/                  {
//STRIP001 /*N*/                      // Deletes establish listeners on names _after_
//STRIP001 /*N*/                      // UpdateReference and the following Delete.
//STRIP001 /*N*/                      StartListeningTo( pDocument, SC_LISTENING_EXCEPT |
//STRIP001 /*N*/                              SC_LISTENING_NAMES_ABS | SC_LISTENING_NAMES_REL );
//STRIP001 /*N*/                  }
//STRIP001 /*N*/                  else
//STRIP001 /*N*/                      StartListeningTo( pDocument, 0 );
//STRIP001 /*N*/              }
//STRIP001 /*N*/              else if ( bNewRelName && eUpdateRefMode != URM_INSDEL )
//STRIP001 /*N*/                  StartListeningTo( pDocument, SC_LISTENING_NAMES_REL );
//STRIP001 /*N*/                  // Insert/Delete RelNameListening/SetDirty follows later
//STRIP001 /*N*/          }
//STRIP001 /*N*/          if ( bNeedDirty && (!(eUpdateRefMode == URM_INSDEL && bHasRelName) || pRangeData) )
//STRIP001 /*N*/          {   // Referenzen abgeschnitten, ungueltig o.ae.?
//STRIP001 /*N*/              BOOL bOldAutoCalc = pDocument->GetAutoCalc();
//STRIP001 /*N*/              // kein Interpret in SubMinimalRecalc wegen evtl. falscher Referenzen
//STRIP001 /*N*/              pDocument->SetAutoCalc( FALSE );
//STRIP001 /*N*/              SetDirty();
//STRIP001 /*N*/              pDocument->SetAutoCalc( bOldAutoCalc );
//STRIP001 /*N*/          }
//STRIP001 /*N*/
//STRIP001 /*N*/          delete pOld;
//STRIP001 /*N*/      }
/*N*/  }

/*N*/ void ScFormulaCell::UpdateInsertTab(USHORT nTable)
/*N*/ {
/*N*/   BOOL bPosChanged = ( aPos.Tab() >= nTable ? TRUE : FALSE );
/*N*/   pCode->Reset();
/*N*/   if( pCode->GetNextReferenceRPN() && !pDocument->IsClipOrUndo() )
/*N*/   {
/*N*/       EndListeningTo( pDocument );
/*N*/       // IncTab _nach_ EndListeningTo und _vor_ Compiler UpdateInsertTab !
/*N*/       if ( bPosChanged )
/*?*/           aPos.IncTab();
/*N*/       ScRangeData* pRangeData;
/*N*/       ScCompiler aComp(pDocument, aPos, *pCode);
/*N*/       pRangeData = aComp.UpdateInsertTab( nTable, FALSE );
/*N*/       if (pRangeData)                     // Shared Formula gegen echte Formel
/*N*/       {                                   // austauschen
/*?*/           BOOL bChanged;
/*?*/           pDocument->RemoveFromFormulaTree( this );   // update formula count
/*?*/           delete pCode;
/*?*/           pCode = new ScTokenArray( *pRangeData->GetCode() );
/*M*/             pCode->SetReplacedSharedFormula( TRUE );
/*?*/           ScCompiler aComp2(pDocument, aPos, *pCode);
/*?*/           aComp2.MoveRelWrap();
/*?*/           aComp2.UpdateInsertTab( nTable, FALSE );
/*?*/             // If the shared formula contained a named range/formula containing
/*?*/             // an absolute reference to a sheet, those have to be readjusted.
/*?*/           aComp2.UpdateDeleteTab( nTable, FALSE, TRUE, bChanged );
/*?*/           bCompile = TRUE;
/*N*/       }
/*N*/       // kein StartListeningTo weil pTab[nTab] noch nicht existiert!
/*N*/   }
/*N*/   else if ( bPosChanged )
/*?*/       aPos.IncTab();
/*N*/ }

/*N*/  BOOL ScFormulaCell::UpdateDeleteTab(USHORT nTable, BOOL bIsMove)
/*N*/  {
/*N*/   BOOL bChanged = FALSE;
/*N*/   BOOL bPosChanged = ( aPos.Tab() > nTable ? TRUE : FALSE );
/*N*/   pCode->Reset();
/*N*/   if( pCode->GetNextReferenceRPN() && !pDocument->IsClipOrUndo() )
/*N*/   {
/*N*/       EndListeningTo( pDocument );
/*N*/       // IncTab _nach_ EndListeningTo und _vor_ Compiler UpdateDeleteTab !
/*N*/       if ( bPosChanged )
/*N*/           aPos.IncTab(-1);
/*N*/       ScRangeData* pRangeData;
/*N*/       ScCompiler aComp(pDocument, aPos, *pCode);
/*N*/       pRangeData = aComp.UpdateDeleteTab(nTable, bIsMove, FALSE, bChanged);
/*N*/       if (pRangeData)                     // Shared Formula gegen echte Formel
/*N*/       {                                   // austauschen
/*N*/           pDocument->RemoveFromFormulaTree( this );   // update formula count
/*N*/           delete pCode;
/*N*/           pCode = pRangeData->GetCode()->Clone();
/*N*/              pCode->SetReplacedSharedFormula( TRUE );
/*N*/           ScCompiler aComp2(pDocument, aPos, *pCode);
/*N*/           aComp2.CompileTokenArray();
/*N*/           aComp2.MoveRelWrap();
/*N*/           aComp2.UpdateDeleteTab( nTable, FALSE, FALSE, bChanged );
/*N*/              // If the shared formula contained a named range/formula containing
/*N*/              // an absolute reference to a sheet, those have to be readjusted.
/*N*/           aComp2.UpdateInsertTab( nTable,TRUE );
/*N*/           // bChanged kann beim letzten UpdateDeleteTab zurueckgesetzt worden sein
/*N*/           bChanged = TRUE;
/*N*/           bCompile = TRUE;
/*N*/       }
/*N*/       // kein StartListeningTo weil pTab[nTab] noch nicht korrekt!
/*N*/   }
/*N*/   else if ( bPosChanged )
/*N*/       aPos.IncTab(-1);
/*N*/
/*N*/   return bChanged;
/*N*/  }

/*N*/  void ScFormulaCell::UpdateMoveTab( USHORT nOldPos, USHORT nNewPos, USHORT nTabNo )
/*N*/  {
/*N*/   pCode->Reset();
/*N*/   if( pCode->GetNextReferenceRPN() && !pDocument->IsClipOrUndo() )
/*N*/   {
/*N*/       EndListeningTo( pDocument );
/*N*/       // SetTab _nach_ EndListeningTo und _vor_ Compiler UpdateMoveTab !
/*N*/       aPos.SetTab( nTabNo );
/*N*/       ScRangeData* pRangeData;
/*N*/       ScCompiler aComp(pDocument, aPos, *pCode);
/*N*/       pRangeData = aComp.UpdateMoveTab( nOldPos, nNewPos, FALSE );
/*N*/       if (pRangeData)                     // Shared Formula gegen echte Formel
/*N*/       {                                   // austauschen
/*N*/           pDocument->RemoveFromFormulaTree( this );   // update formula count
/*N*/           delete pCode;
/*N*/           pCode = pRangeData->GetCode()->Clone();
/*N*/              pCode->SetReplacedSharedFormula( TRUE );
/*N*/           ScCompiler aComp2(pDocument, aPos, *pCode);
/*N*/           aComp2.CompileTokenArray();
/*N*/           aComp2.MoveRelWrap();
/*N*/           aComp2.UpdateMoveTab( nOldPos, nNewPos, TRUE );
/*N*/           bCompile = TRUE;
/*N*/       }
/*N*/       // kein StartListeningTo weil pTab[nTab] noch nicht korrekt!
/*N*/   }
/*N*/   else
/*N*/       aPos.SetTab( nTabNo );
/*N*/  }

/*N*/  void ScFormulaCell::UpdateInsertTabAbs(USHORT nTable)
/*N*/  {
/*N*/   if( !pDocument->IsClipOrUndo() )
/*N*/   {
/*N*/       pCode->Reset();
/*N*/       ScToken* p = pCode->GetNextReferenceRPN();
/*N*/       while( p )
/*N*/       {
/*N*/           SingleRefData& rRef1 = p->GetSingleRef();
/*N*/           if( !rRef1.IsTabRel() && (short) nTable <= rRef1.nTab )
/*N*/               rRef1.nTab++;
/*N*/           if( p->GetType() == svDoubleRef )
/*N*/           {
/*N*/               SingleRefData& rRef2 = p->GetDoubleRef().Ref2;
/*N*/               if( !rRef2.IsTabRel() && (short) nTable <= rRef2.nTab )
/*N*/                   rRef2.nTab++;
/*N*/           }
/*N*/           p = pCode->GetNextReferenceRPN();
/*N*/       }
/*N*/   }
/*N*/  }

/*N*/ BOOL ScFormulaCell::TestTabRefAbs(USHORT nTable)
/*N*/ {
/*N*/   BOOL bRet = FALSE;
DBG_ASSERT(0, "STRIP"); /*N*/   if( !pDocument->IsClipOrUndo() )
/*N*/   {
/*N*/       pCode->Reset();
/*N*/       ScToken* p = pCode->GetNextReferenceRPN();
/*N*/       while( p )
/*N*/       {
/*N*/           SingleRefData& rRef1 = p->GetSingleRef();
/*N*/           if( !rRef1.IsTabRel() )
/*N*/           {
/*N*/               if( (short) nTable != rRef1.nTab )
/*N*/                   bRet = TRUE;
/*N*/               else if (nTable != aPos.Tab())
/*N*/                   rRef1.nTab = aPos.Tab();
/*N*/           }
/*N*/           if( p->GetType() == svDoubleRef )
/*N*/           {
/*N*/               SingleRefData& rRef2 = p->GetDoubleRef().Ref2;
/*N*/               if( !rRef2.IsTabRel() )
/*N*/               {
/*N*/                   if( (short) nTable != rRef2.nTab )
/*N*/                       bRet = TRUE;
/*N*/                   else if (nTable != aPos.Tab())
/*N*/                       rRef2.nTab = aPos.Tab();
/*N*/               }
/*N*/           }
/*N*/           p = pCode->GetNextReferenceRPN();
/*N*/       }
/*N*/   }
/*N*/   return bRet;
/*N*/ }

/*N*/ void ScFormulaCell::UpdateCompile( BOOL bForceIfNameInUse )
/*N*/ {
/*N*/   if ( bForceIfNameInUse && !bCompile )
/*?*/      { DBG_ASSERT(0, "STRIP");} /*N*/    bCompile = pCode->HasNameOrColRowName();
/*N*/   if ( bCompile )
/*?*/       pCode->SetError( 0 );   // damit auch wirklich kompiliert wird
/*N*/   CompileTokenArray();
/*N*/ }

//  Referenzen transponieren - wird nur in Clipboard-Dokumenten aufgerufen

/*N*/  void ScFormulaCell::TransposeReference()
/*N*/  {
/*N*/   BOOL bFound = FALSE;
/*N*/   pCode->Reset();
/*N*/   for( ScToken* t = pCode->GetNextReference(); t;
/*N*/                 t = pCode->GetNextReference() )
/*N*/   {
/*N*/       SingleRefData& rRef1 = t->GetSingleRef();
/*N*/       if ( rRef1.IsColRel() && rRef1.IsRowRel() )
/*N*/       {
/*N*/           BOOL bDouble = (t->GetType() == svDoubleRef);
/*N*/           SingleRefData& rRef2 = (bDouble ? t->GetDoubleRef().Ref2 : rRef1);
/*N*/           if ( !bDouble || (rRef2.IsColRel() && rRef2.IsRowRel()) )
/*N*/           {
/*N*/               INT16 nTemp;
/*N*/
/*N*/               nTemp = rRef1.nRelCol;
/*N*/               rRef1.nRelCol = rRef1.nRelRow;
/*N*/               rRef1.nRelRow = nTemp;
/*N*/
/*N*/               if ( bDouble )
/*N*/               {
/*N*/                   nTemp = rRef2.nRelCol;
/*N*/                   rRef2.nRelCol = rRef2.nRelRow;
/*N*/                   rRef2.nRelRow = nTemp;
/*N*/               }
/*N*/
/*N*/               bFound = TRUE;
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/
/*N*/   if (bFound)
/*N*/       bCompile = TRUE;
/*N*/  }

/*N*/  void ScFormulaCell::UpdateTranspose( const ScRange& rSource, const ScAddress& rDest,
/*N*/                                       ScDocument* pUndoDoc )
/*N*/  {
/*N*/   EndListeningTo( pDocument );
/*N*/
/*N*/   ScAddress aOldPos = aPos;
/*N*/   BOOL bPosChanged = FALSE;           // ob diese Zelle bewegt wurde
/*N*/
/*N*/   ScRange aDestRange( rDest, ScAddress(
/*N*/               rDest.Col() + rSource.aEnd.Row() - rSource.aStart.Row(),
/*N*/               rDest.Row() + rSource.aEnd.Col() - rSource.aStart.Col(),
/*N*/               rDest.Tab() + rSource.aEnd.Tab() - rSource.aStart.Tab() ) );
/*N*/   if ( aDestRange.In( aOldPos ) )
/*N*/   {
/*N*/       //  Position zurueckrechnen
/*N*/       short nRelPosX = aOldPos.Col();
/*N*/       short nRelPosY = aOldPos.Row();
/*N*/       short nRelPosZ = aOldPos.Tab();
/*N*/       ScRefUpdate::DoTranspose( nRelPosX, nRelPosY, nRelPosZ, pDocument, aDestRange, rSource.aStart );
/*N*/       aOldPos.Set( nRelPosX, nRelPosY, nRelPosZ );
/*N*/       bPosChanged = TRUE;
/*N*/   }
/*N*/
/*N*/   ScTokenArray* pOld = pUndoDoc ? pCode->Clone() : NULL;
/*N*/   BOOL bChanged = FALSE;
/*N*/   ScToken* t;
/*N*/
/*N*/   ScRangeData* pShared = NULL;
/*N*/   pCode->Reset();
/*N*/   for( t = pCode->GetNextReferenceOrName(); t; t = pCode->GetNextReferenceOrName() )
/*N*/   {
/*N*/       if( t->GetOpCode() == ocName )
/*N*/       {
/*N*/           ScRangeData* pName = pDocument->GetRangeName()->FindIndex( t->GetIndex() );
/*N*/           if (pName)
/*N*/           {
/*N*/               if (pName->IsModified())
/*N*/                   bChanged = TRUE;
/*N*/               if (pName->HasType(RT_SHAREDMOD))
/*N*/                   pShared = pName;
/*N*/           }
/*N*/       }
/*N*/       else if( t->GetType() != svIndex )
/*N*/       {
/*N*/           t->CalcAbsIfRel( aOldPos );
/*N*/           BOOL bMod;
/*N*/           {   // own scope for SingleDoubleRefModifier dtor if SingleRef
/*N*/                 SingleDoubleRefModifier aMod( *t );
/*N*/                 ComplRefData& rRef = aMod.Ref();
/*N*/               bMod = (ScRefUpdate::UpdateTranspose( pDocument, rSource,
/*N*/                   rDest, rRef ) != UR_NOTHING || bPosChanged);
/*N*/           }
/*N*/           if ( bMod )
/*N*/           {
/*N*/               t->CalcRelFromAbs( aPos );
/*N*/               bChanged = TRUE;
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/
/*N*/   if (pShared)            // Shared Formula gegen echte Formel austauschen
/*N*/   {
/*N*/       pDocument->RemoveFromFormulaTree( this );   // update formula count
/*N*/       delete pCode;
/*N*/       pCode = new ScTokenArray( *pShared->GetCode() );
/*N*/       bChanged = TRUE;
/*N*/       pCode->Reset();
/*N*/       for( t = pCode->GetNextReference(); t; t = pCode->GetNextReference() )
/*N*/       {
/*N*/           if( t->GetType() != svIndex )
/*N*/           {
/*N*/               t->CalcAbsIfRel( aOldPos );
/*N*/               BOOL bMod;
/*N*/               {   // own scope for SingleDoubleRefModifier dtor if SingleRef
/*N*/                     SingleDoubleRefModifier aMod( *t );
/*N*/                     ComplRefData& rRef = aMod.Ref();
/*N*/                   bMod = (ScRefUpdate::UpdateTranspose( pDocument, rSource,
/*N*/                       rDest, rRef ) != UR_NOTHING || bPosChanged);
/*N*/               }
/*N*/               if ( bMod )
/*N*/                   t->CalcRelFromAbs( aPos );
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/
/*N*/   if (bChanged)
/*N*/   {
/*N*/       if (pUndoDoc)
/*N*/       {
/*N*/           ScFormulaCell* pFCell = new ScFormulaCell( pUndoDoc, aPos, pOld, cMatrixFlag );
/*N*/           pFCell->nErgValue = MINDOUBLE;      // damit spaeter changed (Cut/Paste!)
/*N*/           pUndoDoc->PutCell( aPos.Col(), aPos.Row(), aPos.Tab(), pFCell );
/*N*/       }
/*N*/
/*N*/       bCompile = TRUE;
/*N*/       CompileTokenArray();                // ruft auch StartListeningTo
/*N*/       SetDirty();
/*N*/   }
/*N*/   else
/*N*/       StartListeningTo( pDocument );      // Listener wie vorher
/*N*/
/*N*/   delete pOld;
/*N*/  }

/*N*/  void ScFormulaCell::UpdateGrow( const ScRange& rArea, USHORT nGrowX, USHORT nGrowY )
/*N*/  {
/*N*/   EndListeningTo( pDocument );
/*N*/
/*N*/   BOOL bChanged = FALSE;
/*N*/   ScToken* t;
/*N*/   ScRangeData* pShared = NULL;
/*N*/
/*N*/   pCode->Reset();
/*N*/   for( t = pCode->GetNextReferenceOrName(); t; t = pCode->GetNextReferenceOrName() )
/*N*/   {
/*N*/       if( t->GetOpCode() == ocName )
/*N*/       {
/*N*/           ScRangeData* pName = pDocument->GetRangeName()->FindIndex( t->GetIndex() );
/*N*/           if (pName)
/*N*/           {
/*N*/               if (pName->IsModified())
/*N*/                   bChanged = TRUE;
/*N*/               if (pName->HasType(RT_SHAREDMOD))
/*N*/                   pShared = pName;
/*N*/           }
/*N*/       }
/*N*/       else if( t->GetType() != svIndex )
/*N*/       {
/*N*/           t->CalcAbsIfRel( aPos );
/*N*/           BOOL bMod;
/*N*/           {   // own scope for SingleDoubleRefModifier dtor if SingleRef
/*N*/                 SingleDoubleRefModifier aMod( *t );
/*N*/                 ComplRefData& rRef = aMod.Ref();
/*N*/               bMod = (ScRefUpdate::UpdateGrow( rArea,nGrowX,nGrowY,
/*N*/                   rRef ) != UR_NOTHING);
/*N*/           }
/*N*/           if ( bMod )
/*N*/           {
/*N*/               t->CalcRelFromAbs( aPos );
/*N*/               bChanged = TRUE;
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/
/*N*/   if (pShared)            // Shared Formula gegen echte Formel austauschen
/*N*/   {
/*N*/       pDocument->RemoveFromFormulaTree( this );   // update formula count
/*N*/       delete pCode;
/*N*/       pCode = new ScTokenArray( *pShared->GetCode() );
/*N*/       bChanged = TRUE;
/*N*/       pCode->Reset();
/*N*/       for( t = pCode->GetNextReference(); t; t = pCode->GetNextReference() )
/*N*/       {
/*N*/           if( t->GetType() != svIndex )
/*N*/           {
/*N*/               t->CalcAbsIfRel( aPos );
/*N*/               BOOL bMod;
/*N*/               {   // own scope for SingleDoubleRefModifier dtor if SingleRef
/*N*/                     SingleDoubleRefModifier aMod( *t );
/*N*/                     ComplRefData& rRef = aMod.Ref();
/*N*/                   bMod = (ScRefUpdate::UpdateGrow( rArea,nGrowX,nGrowY,
/*N*/                       rRef ) != UR_NOTHING);
/*N*/               }
/*N*/               if ( bMod )
/*N*/                   t->CalcRelFromAbs( aPos );
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/
/*N*/   if (bChanged)
/*N*/   {
/*N*/       bCompile = TRUE;
/*N*/       CompileTokenArray();                // ruft auch StartListeningTo
/*N*/       SetDirty();
/*N*/   }
/*N*/   else
/*N*/       StartListeningTo( pDocument );      // Listener wie vorher
/*N*/  }

/*N*/ BOOL lcl_IsRangeNameInUse(USHORT nIndex, ScTokenArray* pCode, ScRangeName* pNames)
/*N*/ {
/*N*/   for (ScToken* p = pCode->First(); p; p = pCode->Next())
/*N*/   {
/*N*/       if (p->GetOpCode() == ocName)
/*N*/       {
/*N*/           if (p->GetIndex() == nIndex)
/*N*/               return TRUE;
/*N*/           else
/*N*/           {
/*N*/               //  RangeData kann Null sein in bestimmten Excel-Dateien (#31168#)
/*N*/               ScRangeData* pSubName = pNames->FindIndex(p->GetIndex());
/*N*/               if (pSubName && lcl_IsRangeNameInUse(nIndex,
/*N*/                                   pSubName->GetCode(), pNames))
/*N*/                   return TRUE;
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/   return FALSE;
/*N*/ }

/*N*/ BOOL ScFormulaCell::IsRangeNameInUse(USHORT nIndex) const
/*N*/ {
/*N*/   return lcl_IsRangeNameInUse( nIndex, pCode, pDocument->GetRangeName() );
/*N*/ }

/*N*/  void ScFormulaCell::ReplaceRangeNamesInUse( const ScIndexMap& rMap )
/*N*/  {
/*N*/   for( ScToken* p = pCode->First(); p; p = pCode->Next() )
/*N*/   {
/*N*/       if( p->GetOpCode() == ocName )
/*N*/       {
/*N*/           USHORT nIndex = p->GetIndex();
/*N*/           USHORT nNewIndex = rMap.Find( nIndex );
/*N*/           if ( nIndex != nNewIndex )
/*N*/           {
/*N*/               p->SetIndex( nNewIndex );
/*N*/               bCompile = TRUE;
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/   if( bCompile )
/*N*/       CompileTokenArray();
/*N*/  }

/*N*/  void ScFormulaCell::CompileDBFormula()
/*N*/  {
/*N*/   for( ScToken* p = pCode->First(); p; p = pCode->Next() )
/*N*/   {
/*N*/       if ( p->GetOpCode() == ocDBArea
/*N*/           || (p->GetOpCode() == ocName && p->GetIndex() >= SC_START_INDEX_DB_COLL) )
/*N*/       {
/*N*/           bCompile = TRUE;
/*N*/           CompileTokenArray();
/*N*/           SetDirty();
/*N*/           break;
/*N*/       }
/*N*/   }
/*N*/  }

/*N*/ void ScFormulaCell::CompileDBFormula( BOOL bCreateFormulaString )
/*N*/ {
/*N*/   // zwei Phasen, muessen (!) nacheinander aufgerufen werden:
/*N*/   // 1. FormelString mit alten Namen erzeugen
/*N*/   // 2. FormelString mit neuen Namen kompilieren
/*N*/   if ( bCreateFormulaString )
/*N*/   {
/*N*/       BOOL bRecompile = FALSE;
/*N*/       pCode->Reset();
/*N*/       for ( ScToken* p = pCode->First(); p && !bRecompile; p = pCode->Next() )
/*N*/       {
/*N*/           switch ( p->GetOpCode() )
/*N*/           {
/*N*/               case ocBad:             // DB-Bereich evtl. zugefuegt
/*N*/               case ocColRowName:      // #36762# falls Namensgleichheit
/*N*/               case ocDBArea:          // DB-Bereich
/*N*/                   bRecompile = TRUE;
/*N*/               break;
/*N*/               case ocName:
/*?*/                   if ( p->GetIndex() >= SC_START_INDEX_DB_COLL )
/*?*/                       bRecompile = TRUE;  // DB-Bereich
/*N*/           }
/*N*/       }
/*N*/       if ( bRecompile )
/*N*/       {
/*N*/           String aFormula;
/*N*/           GetFormula( aFormula );
/*N*/           if ( GetMatrixFlag() != MM_NONE && aFormula.Len() )
/*N*/           {
/*?*/               if ( aFormula.GetChar( aFormula.Len()-1 ) == '}' )
/*?*/                   aFormula.Erase( aFormula.Len()-1 , 1 );
/*?*/               if ( aFormula.GetChar(0) == '{' )
/*?*/                   aFormula.Erase( 0, 1 );
/*N*/           }
/*N*/           EndListeningTo( pDocument );
/*N*/           pDocument->RemoveFromFormulaTree( this );
/*N*/           pCode->Clear();
/*N*/           aErgString = aFormula;
/*N*/       }
/*N*/   }
/*N*/   else if ( !pCode->GetLen() && aErgString.Len() )
/*N*/   {
/*N*/       Compile( aErgString );
/*N*/       aErgString.Erase();
/*N*/       SetDirty();
/*N*/   }
/*N*/ }

/*N*/ void ScFormulaCell::CompileNameFormula( BOOL bCreateFormulaString )
/*N*/ {
/*N*/   // zwei Phasen, muessen (!) nacheinander aufgerufen werden:
/*N*/   // 1. FormelString mit alten RangeNames erzeugen
/*N*/   // 2. FormelString mit neuen RangeNames kompilieren
/*N*/   if ( bCreateFormulaString )
/*N*/   {
/*N*/       BOOL bRecompile = FALSE;
/*N*/       pCode->Reset();
/*N*/       for ( ScToken* p = pCode->First(); p && !bRecompile; p = pCode->Next() )
/*N*/       {
/*N*/           switch ( p->GetOpCode() )
/*N*/           {
/*N*/               case ocBad:             // RangeName evtl. zugefuegt
/*N*/               case ocColRowName:      // #36762# falls Namensgleichheit
/*N*/                   bRecompile = TRUE;
/*N*/               break;
/*N*/               default:
/*N*/                   if ( p->GetType() == svIndex )
/*N*/                       bRecompile = TRUE;  // RangeName
/*N*/           }
/*N*/       }
/*N*/       if ( bRecompile )
/*N*/       {
/*N*/           String aFormula;
/*N*/           GetFormula( aFormula );
/*N*/           if ( GetMatrixFlag() != MM_NONE && aFormula.Len() )
/*N*/           {
/*?*/               if ( aFormula.GetChar( aFormula.Len()-1 ) == '}' )
/*?*/                   aFormula.Erase( aFormula.Len()-1 , 1 );
/*?*/               if ( aFormula.GetChar(0) == '{' )
/*?*/                   aFormula.Erase( 0, 1 );
/*N*/           }
/*N*/           EndListeningTo( pDocument );
/*N*/           pDocument->RemoveFromFormulaTree( this );
/*N*/           pCode->Clear();
/*N*/           aErgString = aFormula;
/*N*/       }
/*N*/   }
/*N*/   else if ( !pCode->GetLen() && aErgString.Len() )
/*N*/   {
/*N*/       Compile( aErgString );
/*N*/       aErgString.Erase();
/*N*/       SetDirty();
/*N*/   }
/*N*/ }

/*N*/ void ScFormulaCell::CompileColRowNameFormula()
/*N*/ {
/*N*/   pCode->Reset();
/*N*/   for ( ScToken* p = pCode->First(); p; p = pCode->Next() )
/*N*/   {
/*N*/       if ( p->GetOpCode() == ocColRowName )
/*N*/       {
/*N*/           bCompile = TRUE;
/*N*/           CompileTokenArray();
/*N*/           SetDirty();
/*N*/           break;
/*N*/       }
/*N*/   }
/*N*/ }

/*N*/ ScValueCell::ScValueCell( SvStream& rStream, USHORT nVer ) :
/*N*/   ScBaseCell( CELLTYPE_VALUE )
/*N*/ {
/*N*/   if( nVer >= SC_DATABYTES2 )
/*N*/   {
/*N*/       BYTE cData;
/*N*/       rStream >> cData;
/*N*/       if( cData & 0x0F )
/*?*/           rStream.SeekRel( cData & 0x0F );
/*N*/   }
/*N*/   rStream >> aValue;
/*N*/ }

/*N*/ void ScValueCell::Save( SvStream& rStream ) const
/*N*/ {
/*N*/   rStream << (BYTE) 0x00 << aValue;
/*N*/ }

/*N*/ ScStringCell::ScStringCell( SvStream& rStream, USHORT nVer ) :
/*N*/   ScBaseCell( CELLTYPE_STRING )
/*N*/ {
/*N*/   if( nVer >= SC_DATABYTES2 )
/*N*/   {
/*N*/       BYTE cData;
/*N*/       rStream >> cData;
/*N*/       if( cData & 0x0F )
/*?*/           rStream.SeekRel( cData & 0x0F );
/*N*/   }
/*N*/   rStream.ReadByteString( aString, rStream.GetStreamCharSet() );
/*N*/ }

/*N*/ void ScStringCell::Save( SvStream& rStream, FontToSubsFontConverter hConv ) const
/*N*/ {
/*N*/   rStream << (BYTE) 0x00;
/*N*/     if ( !hConv )
/*N*/         rStream.WriteByteString( aString, rStream.GetStreamCharSet() );
/*N*/     else
/*N*/     {
/*N*/         String aTmp( aString );
/*N*/         sal_Unicode* p = aTmp.GetBufferAccess();
/*N*/         sal_Unicode const * const pStop = p + aTmp.Len();
/*N*/         for ( ; p < pStop; ++p )
/*N*/         {
/*N*/             *p = ConvertFontToSubsFontChar( hConv, *p );
/*N*/         }
/*N*/         aTmp.ReleaseBufferAccess();
/*N*/         rStream.WriteByteString( aTmp, rStream.GetStreamCharSet() );
/*N*/     }
/*N*/ }

/*N*/ void ScStringCell::ConvertFont( FontToSubsFontConverter hConv )
/*N*/ {
/*N*/     if ( hConv )
/*N*/     {
/*N*/         sal_Unicode* p = aString.GetBufferAccess();
/*N*/         sal_Unicode const * const pStop = p + aString.Len();
/*N*/         for ( ; p < pStop; ++p )
/*N*/         {
/*N*/             *p = ConvertFontToSubsFontChar( hConv, *p );
/*N*/         }
/*N*/         aString.ReleaseBufferAccess();
/*N*/     }
/*N*/ }

/*N*/ ScNoteCell::ScNoteCell( SvStream& rStream, USHORT nVer ) :
/*N*/   ScBaseCell( CELLTYPE_NOTE )
/*N*/ {
/*N*/   if( nVer >= SC_DATABYTES2 )
/*N*/   {
/*N*/       BYTE cData;
/*N*/       rStream >> cData;
/*N*/       if( cData & 0x0F )
/*?*/           rStream.SeekRel( cData & 0x0F );
/*N*/   }
/*N*/ }

/*N*/ void ScNoteCell::Save( SvStream& rStream ) const
/*N*/ {
/*N*/   rStream << (BYTE) 0x00;
/*N*/ }





}
