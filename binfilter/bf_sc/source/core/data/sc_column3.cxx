/*************************************************************************
 *
 *  $RCSfile: sc_column3.cxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 11:03:32 $
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
// INCLUDE ---------------------------------------------------------------

#ifdef PCH
// auto strip #include "core_pch.hxx"
#endif

#pragma hdrstop

#include <bf_sfx2/objsh.hxx>
#include <svtools/zforlist.hxx>

#include "scitems.hxx"
// auto strip #include "column.hxx"
#include "cell.hxx"
#include "document.hxx"
#include "attarray.hxx"
// auto strip #include "patattr.hxx"
#include "cellform.hxx"
// auto strip #include "collect.hxx"
// auto strip #include "compiler.hxx"
// auto strip #include "brdcst.hxx"
// auto strip #include "docoptio.hxx"           // GetStdPrecision fuer GetMaxStringLen
// auto strip #include "subtotal.hxx"
// auto strip #include "markdata.hxx"
#include "detfunc.hxx"          // fuer Notizen bei DeleteRange
namespace binfilter {

// Err527 Workaround
extern const ScFormulaCell* pLastFormulaTreeTop;    // in cellform.cxx

// STATIC DATA -----------------------------------------------------------

/*N*/ BOOL ScColumn::bDoubleAlloc = FALSE;  // fuer Import: Groesse beim Allozieren verdoppeln
/*N*/
/*N*/
/*N*/ void ScColumn::Insert( USHORT nRow, ScBaseCell* pNewCell )
/*N*/ {
/*N*/   BOOL bIsAppended = FALSE;
/*N*/   if (pItems && nCount)
/*N*/   {
/*N*/       if (pItems[nCount-1].nRow < nRow)
/*N*/       {
/*N*/           Append(nRow, pNewCell );
/*N*/           bIsAppended = TRUE;
/*N*/       }
/*N*/   }
/*N*/   if ( !bIsAppended )
/*N*/   {
/*N*/       USHORT  nIndex;
/*N*/       if (Search(nRow, nIndex))
/*N*/       {
/*N*/           ScBaseCell* pOldCell = pItems[nIndex].pCell;
/*N*/           ScBroadcasterList* pBC = pOldCell->GetBroadcaster();
/*N*/           if (pBC && !pNewCell->GetBroadcaster())
/*N*/           {
/*N*/               pNewCell->SetBroadcaster( pBC );
/*N*/               pOldCell->ForgetBroadcaster();
/*N*/           }
/*N*/           if (pOldCell->GetNotePtr() && !pNewCell->GetNotePtr())
/*?*/               pNewCell->SetNote( *pOldCell->GetNotePtr() );
/*N*/           if ( pOldCell->GetCellType() == CELLTYPE_FORMULA && !pDocument->IsClipOrUndo() )
/*N*/           {
/*?*/               pOldCell->EndListeningTo( pDocument );
/*?*/               // falls in EndListening NoteCell in gleicher Col zerstoert
/*?*/               if ( nIndex >= nCount || pItems[nIndex].nRow != nRow )
/*?*/                   Search(nRow, nIndex);
/*N*/           }
/*N*/           pOldCell->Delete();
/*N*/           pItems[nIndex].pCell = pNewCell;
/*N*/       }
/*N*/       else
/*N*/       {
/*N*/           if (nCount + 1 > nLimit)
/*N*/           {
/*N*/               if (bDoubleAlloc)
/*N*/               {
/*N*/                   if (nLimit < COLUMN_DELTA)
/*N*/                       nLimit = COLUMN_DELTA;
/*N*/                   else
/*N*/                   {
/*N*/                       nLimit *= 2;
/*N*/                       if ( nLimit > MAXROW+1 )
/*N*/                           nLimit = MAXROW+1;
/*N*/                   }
/*N*/               }
/*N*/               else
/*N*/                   nLimit += COLUMN_DELTA;
/*N*/
/*N*/               ColEntry* pNewItems = new ColEntry[nLimit];
/*N*/               if (pItems)
/*N*/               {
/*N*/                   memmove( pNewItems, pItems, nCount * sizeof(ColEntry) );
/*N*/                   delete[] pItems;
/*N*/               }
/*N*/               pItems = pNewItems;
/*N*/           }
/*N*/           memmove( &pItems[nIndex + 1], &pItems[nIndex], (nCount - nIndex) * sizeof(ColEntry) );
/*N*/           pItems[nIndex].pCell = pNewCell;
/*N*/           pItems[nIndex].nRow  = nRow;
/*N*/           ++nCount;
/*N*/       }
/*N*/   }
/*N*/   // Bei aus Clipboard sind hier noch falsche (alte) Referenzen!
/*N*/   // Werden in CopyBlockFromClip per UpdateReference umgesetzt,
/*N*/   // danach StartListeningFromClip und BroadcastFromClip gerufen.
/*N*/   // Wird ins Clipboard/UndoDoc gestellt, wird kein Broadcast gebraucht.
/*N*/   // Nach Import wird CalcAfterLoad gerufen, dort Listening.
/*N*/   if ( !(pDocument->IsClipOrUndo() || pDocument->IsInsertingFromOtherDoc()) )
/*N*/   {
/*N*/       pNewCell->StartListeningTo( pDocument );
/*N*/       CellType eCellType = pNewCell->GetCellType();
/*N*/       // Notizzelle entsteht beim Laden nur durch StartListeningCell,
/*N*/       // ausloesende Formelzelle muss sowieso dirty sein.
/*N*/       if ( !(pDocument->IsCalcingAfterLoad() && eCellType == CELLTYPE_NOTE) )
/*N*/       {
/*N*/           if ( eCellType == CELLTYPE_FORMULA )
/*N*/               ((ScFormulaCell*)pNewCell)->SetDirty();
/*N*/           else
/*N*/               pDocument->Broadcast( ScHint( SC_HINT_DATACHANGED,
/*N*/                   ScAddress( nCol, nRow, nTab ), pNewCell ) );
/*N*/       }
/*N*/   }
/*N*/ }


/*N*/ void ScColumn::Insert( USHORT nRow, ULONG nNumberFormat, ScBaseCell* pCell )
/*N*/ {
/*N*/   Insert(nRow, pCell);
/*N*/   short eOldType = pDocument->GetFormatTable()->
/*N*/                       GetType( (ULONG)
/*N*/                           ((SfxUInt32Item*)GetAttr( nRow, ATTR_VALUE_FORMAT ))->
/*N*/                               GetValue() );
/*N*/   short eNewType = pDocument->GetFormatTable()->GetType(nNumberFormat);
/*N*/   if (!pDocument->GetFormatTable()->IsCompatible(eOldType, eNewType))
/*N*/       ApplyAttr( nRow, SfxUInt32Item( ATTR_VALUE_FORMAT, (UINT32) nNumberFormat) );
/*N*/ }


/*N*/ void ScColumn::Append( USHORT nRow, ScBaseCell* pCell )
/*N*/ {
/*N*/   if (nCount + 1 > nLimit)
/*N*/   {
/*N*/       if (bDoubleAlloc)
/*N*/       {
/*N*/           if (nLimit < COLUMN_DELTA)
/*N*/               nLimit = COLUMN_DELTA;
/*N*/           else
/*N*/           {
/*N*/               nLimit *= 2;
/*N*/               if ( nLimit > MAXROW+1 )
/*N*/                   nLimit = MAXROW+1;
/*N*/           }
/*N*/       }
/*N*/       else
/*N*/           nLimit += COLUMN_DELTA;
/*N*/
/*N*/       ColEntry* pNewItems = new ColEntry[nLimit];
/*N*/       if (pItems)
/*N*/       {
/*N*/           memmove( pNewItems, pItems, nCount * sizeof(ColEntry) );
/*N*/           delete[] pItems;
/*N*/       }
/*N*/       pItems = pNewItems;
/*N*/   }
/*N*/   pItems[nCount].pCell = pCell;
/*N*/   pItems[nCount].nRow  = nRow;
/*N*/   ++nCount;
/*N*/ }


/*N*/ void ScColumn::Delete( USHORT nRow )
/*N*/ {
/*N*/   USHORT  nIndex;
/*N*/
/*N*/   if (Search(nRow, nIndex))
/*N*/   {
/*N*/       ScBaseCell* pCell = pItems[nIndex].pCell;
/*N*/       ScNoteCell* pNoteCell = new ScNoteCell;
/*N*/       pItems[nIndex].pCell = pNoteCell;       // Dummy fuer Interpret
/*N*/       pDocument->Broadcast( ScHint( SC_HINT_DYING,
/*N*/           ScAddress( nCol, nRow, nTab ), pCell ) );
/*N*/       ScBroadcasterList* pBC = pCell->GetBroadcaster();
/*N*/       if ( pBC )
/*N*/       {
/*N*/           pNoteCell->SetBroadcaster( pBC );
/*N*/           pCell->ForgetBroadcaster();
/*N*/       }
/*N*/       else
/*N*/       {
/*N*/           delete pNoteCell;
/*N*/           --nCount;
/*N*/           memmove( &pItems[nIndex], &pItems[nIndex + 1], (nCount - nIndex) * sizeof(ColEntry) );
/*N*/           pItems[nCount].nRow = 0;
/*N*/           pItems[nCount].pCell = NULL;
/*N*/           //  Soll man hier den Speicher freigeben (delta)? Wird dann langsamer!
/*N*/       }
/*N*/       pCell->EndListeningTo( pDocument );
/*N*/       pCell->Delete();
/*N*/   }
/*N*/ }


/*N*/ void ScColumn::DeleteAtIndex( USHORT nIndex )
/*N*/ {
/*N*/   ScBaseCell* pCell = pItems[nIndex].pCell;
/*N*/   ScNoteCell* pNoteCell = new ScNoteCell;
/*N*/   pItems[nIndex].pCell = pNoteCell;       // Dummy fuer Interpret
/*N*/   pDocument->Broadcast( ScHint( SC_HINT_DYING,
/*N*/       ScAddress( nCol, pItems[nIndex].nRow, nTab ), pCell ) );
/*N*/   delete pNoteCell;
/*N*/   --nCount;
/*N*/   memmove( &pItems[nIndex], &pItems[nIndex + 1], (nCount - nIndex) * sizeof(ColEntry) );
/*N*/   pItems[nCount].nRow = 0;
/*N*/   pItems[nCount].pCell = NULL;
/*N*/   pCell->EndListeningTo( pDocument );
/*N*/   pCell->Delete();
/*N*/ }


/*N*/ void ScColumn::FreeAll()
/*N*/ {
/*N*/   if (pItems)
/*N*/   {
/*N*/       for (USHORT i = 0; i < nCount; i++)
/*N*/           pItems[i].pCell->Delete();
/*N*/       delete[] pItems;
/*N*/       pItems = NULL;
/*N*/   }
/*N*/   nCount = 0;
/*N*/   nLimit = 0;
/*N*/ }


/*N*/ void ScColumn::DeleteRow( USHORT nStartRow, USHORT nSize )
/*N*/ {
/*N*/   pAttrArray->DeleteRow( nStartRow, nSize );
/*N*/
/*N*/   if ( !pItems || !nCount )
/*N*/       return ;
/*N*/
/*N*/   USHORT nFirstIndex;
/*N*/   Search( nStartRow, nFirstIndex );
/*N*/   if ( nFirstIndex >= nCount )
/*N*/       return ;
/*N*/
/*N*/   BOOL bOldAutoCalc = pDocument->GetAutoCalc();
/*N*/   pDocument->SetAutoCalc( FALSE );    // Mehrfachberechnungen vermeiden
/*N*/
/*N*/   BOOL bFound=FALSE;
/*N*/   USHORT nEndRow = nStartRow + nSize - 1;
/*N*/   USHORT nStartIndex;
/*N*/   USHORT nEndIndex;
/*N*/   USHORT i;
/*N*/
/*N*/   for ( i = nFirstIndex; i < nCount && pItems[i].nRow <= nEndRow; i++ )
/*N*/   {
/*N*/       if (!bFound)
/*N*/       {
/*N*/           nStartIndex = i;
/*N*/           bFound = TRUE;
/*N*/       }
/*N*/       nEndIndex = i;
/*N*/
/*N*/       ScBaseCell* pCell = pItems[i].pCell;
/*N*/       ScBroadcasterList* pBC = pCell->GetBroadcaster();
/*N*/       if (pBC)
/*N*/       {
/*N*/ // gibt jetzt invalid reference, kein Aufruecken der direkten Referenzen
/*N*/ //            MoveListeners( *pBC, nRow+nSize );
/*N*/           pCell->SetBroadcaster(NULL);
/*N*/           //  in DeleteRange werden leere Broadcaster geloescht
/*N*/       }
/*N*/   }
/*N*/   if (bFound)
/*N*/   {
/*N*/       DeleteRange( nStartIndex, nEndIndex, IDF_CONTENTS );
/*N*/       Search( nStartRow, i );
/*N*/       if ( i >= nCount )
/*N*/       {
/*N*/           pDocument->SetAutoCalc( bOldAutoCalc );
/*N*/           return ;
/*N*/       }
/*N*/   }
/*N*/   else
/*N*/       i = nFirstIndex;
/*N*/
/*N*/   ScAddress aAdr( nCol, 0, nTab );
/*N*/     ScHint aHint( SC_HINT_DATACHANGED, aAdr, NULL );    // only areas (ScBaseCell* == NULL)
/*N*/     ScAddress& rAddress = aHint.GetAddress();
/*N*/     // for sparse occupation use single broadcasts, not ranges
/*N*/     BOOL bSingleBroadcasts = (((pItems[nCount-1].nRow - pItems[i].nRow) /
/*N*/                 (nCount - i)) > 1);
/*N*/     if ( bSingleBroadcasts )
/*N*/     {
/*N*/         USHORT nLastBroadcast = MAXROW+1;
/*N*/         for ( ; i < nCount; i++ )
/*N*/         {
/*N*/             USHORT nOldRow = pItems[i].nRow;
/*N*/             // #43940# Aenderung Quelle broadcasten
/*N*/             rAddress.SetRow( nOldRow );
/*N*/             pDocument->AreaBroadcast( aHint );
/*N*/             USHORT nNewRow = (pItems[i].nRow -= nSize);
/*N*/             // #43940# Aenderung Ziel broadcasten
/*N*/             if ( nLastBroadcast != nNewRow )
/*N*/             {   // direkt aufeinanderfolgende nicht doppelt broadcasten
/*N*/                 rAddress.SetRow( nNewRow );
/*N*/                 pDocument->AreaBroadcast( aHint );
/*N*/             }
/*N*/             nLastBroadcast = nOldRow;
/*N*/             ScBaseCell* pCell = pItems[i].pCell;
/*N*/             if ( pCell->GetCellType() == CELLTYPE_FORMULA )
/*N*/                 ((ScFormulaCell*)pCell)->aPos.SetRow( nNewRow );
/*N*/         }
/*N*/     }
/*N*/     else
/*N*/     {
/*N*/         rAddress.SetRow( pItems[i].nRow );
/*N*/         ScRange aRange( rAddress );
/*N*/         aRange.aEnd.SetRow( pItems[nCount-1].nRow );
/*N*/         for ( ; i < nCount; i++ )
/*N*/         {
/*N*/             USHORT nNewRow = (pItems[i].nRow -= nSize);
/*N*/             ScBaseCell* pCell = pItems[i].pCell;
/*N*/             if ( pCell->GetCellType() == CELLTYPE_FORMULA )
/*N*/                 ((ScFormulaCell*)pCell)->aPos.SetRow( nNewRow );
/*N*/         }
/*N*/         pDocument->AreaBroadcastInRange( aRange, aHint );
/*N*/     }
/*N*/
/*N*/   pDocument->SetAutoCalc( bOldAutoCalc );
/*N*/ }


/*N*/ void ScColumn::DeleteRange( USHORT nStartIndex, USHORT nEndIndex, USHORT nDelFlag )
/*N*/ {
/*N*/   USHORT nDelCount = 0;
/*N*/   ScBaseCell** ppDelCells = new ScBaseCell*[nEndIndex-nStartIndex+1];
/*N*/
/*N*/   BOOL bSimple = ((nDelFlag & IDF_CONTENTS) == IDF_CONTENTS);
/*N*/   USHORT i;
/*N*/
/*N*/       //  Notiz-Zeichenobjekte
/*N*/   if (nDelFlag & IDF_NOTE)
/*N*/   {
/*N*/       for ( i = nStartIndex; i <= nEndIndex; i++ )
/*N*/       {
/*N*/           const ScPostIt* pNote = pItems[i].pCell->GetNotePtr();
/*N*/           if ( pNote && pNote->IsShown() )
/*N*/           {
/*?*/               ScDetectiveFunc( pDocument, nTab ).HideComment( nCol, pItems[i].nRow );
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/
/*N*/       //  Broadcaster stehenlassen
/*N*/   if (bSimple)
/*N*/   {
/*N*/       for (i = nStartIndex; i <= nEndIndex && bSimple; i++)
/*N*/           if (pItems[i].pCell->GetBroadcaster())
/*N*/               bSimple = FALSE;
/*N*/   }
/*N*/
/*N*/     ScHint aHint( SC_HINT_DYING, ScAddress( nCol, 0, nTab ), NULL );
/*N*/
/*N*/   if (bSimple)            // Bereich komplett loeschen
/*N*/   {
/*N*/       ScBaseCell* pOldCell;
/*N*/       ScNoteCell* pNoteCell = new ScNoteCell;     // Dummy
/*N*/       for (i = nStartIndex; i <= nEndIndex; i++)
/*N*/       {
/*N*/           pOldCell = pItems[i].pCell;
/*N*/           if (pOldCell->GetCellType() == CELLTYPE_FORMULA)        // Formeln spaeter loeschen
/*N*/               ppDelCells[nDelCount++] = pOldCell;
/*N*/           else
/*N*/           {
/*N*/               // Interpret in Broadcast darf kein Value finden
/*N*/               pItems[i].pCell = pNoteCell;
/*N*/                 aHint.GetAddress().SetRow( pItems[i].nRow );
/*N*/                 aHint.SetCell( pOldCell );
/*N*/               pDocument->Broadcast( aHint );
/*N*/               pOldCell->Delete();
/*N*/           }
/*N*/       }
/*N*/       delete pNoteCell;
/*N*/       memmove( &pItems[nStartIndex], &pItems[nEndIndex + 1], (nCount - nEndIndex - 1) * sizeof(ColEntry) );
/*N*/       nCount -= nEndIndex-nStartIndex+1;
/*N*/   }
/*N*/   else                    // Zellen einzeln durchgehen
/*N*/   {
/*N*/       USHORT j = nStartIndex;
/*N*/       for (USHORT i = nStartIndex; i <= nEndIndex; i++)
/*N*/       {
/*N*/           BOOL bDelete = FALSE;
/*N*/           ScBaseCell* pOldCell = pItems[j].pCell;
/*N*/           CellType eCellType = pOldCell->GetCellType();
/*N*/           switch ( eCellType )
/*N*/           {
/*N*/               case CELLTYPE_VALUE:
/*N*/                   if ( ( nDelFlag & (IDF_DATETIME|IDF_VALUE) ) == (IDF_DATETIME|IDF_VALUE) )
/*N*/                       bDelete = TRUE;
/*N*/                   else
/*N*/                   {
/*?*/                       ULONG nIndex = (ULONG)((SfxUInt32Item*)GetAttr( pItems[j].nRow, ATTR_VALUE_FORMAT ))->GetValue();
/*?*/                       short nTyp = pDocument->GetFormatTable()->GetType(nIndex);
/*?*/                       if ((nTyp == NUMBERFORMAT_DATE) || (nTyp == NUMBERFORMAT_TIME) || (nTyp == NUMBERFORMAT_DATETIME))
/*?*/                           bDelete = ((nDelFlag & IDF_DATETIME) != 0);
/*?*/                       else
/*?*/                           bDelete = ((nDelFlag & IDF_VALUE) != 0);
/*N*/                   }
/*N*/                   break;
/*?*/               case CELLTYPE_STRING:
/*N*/               case CELLTYPE_EDIT:     bDelete = ((nDelFlag & IDF_STRING) != 0); break;
/*?*/               case CELLTYPE_FORMULA:  bDelete = ((nDelFlag & IDF_FORMULA) != 0); break;
/*?*/               case CELLTYPE_NOTE:
/*?*/                   bDelete = ((nDelFlag & IDF_NOTE) != 0) &&
/*?*/                               (pOldCell->GetBroadcaster() == NULL);
/*?*/                   break;
/*N*/           }
/*N*/
/*N*/           if (bDelete)
/*N*/           {
/*N*/               ScNoteCell* pNoteCell = NULL;
/*N*/               if (eCellType != CELLTYPE_NOTE)
/*N*/               {
/*N*/                   if ((nDelFlag & IDF_NOTE) == 0)
/*N*/                   {
/*?*/                       const ScPostIt* pNote = pOldCell->GetNotePtr();
/*?*/                       if (pNote)
/*?*/                           pNoteCell = new ScNoteCell(*pNote);
/*N*/                   }
/*N*/                   ScBroadcasterList* pBC = pOldCell->GetBroadcaster();
/*N*/                   if (pBC)
/*N*/                   {
/*N*/                       if (!pNoteCell)
/*N*/                           pNoteCell = new ScNoteCell;
/*N*/                       pNoteCell->SetBroadcaster(pBC);
/*N*/                   }
/*N*/               }
/*N*/
/*N*/               USHORT nOldRow = pItems[j].nRow;
/*N*/               if (pNoteCell)
/*N*/               {
/*N*/                   pItems[j].pCell = pNoteCell;
/*N*/                   ++j;
/*N*/               }
/*N*/               else
/*N*/               {
/*N*/                   --nCount;
/*N*/                   memmove( &pItems[j], &pItems[j + 1], (nCount - j) * sizeof(ColEntry) );
/*N*/                   pItems[nCount].nRow = 0;
/*N*/                   pItems[nCount].pCell = NULL;
/*N*/               }
/*N*/               // ACHTUNG! pItems bereits verschoben!
/*N*/               // Interpret in Broadcast muss neue/keine Zelle finden
/*N*/               if (eCellType == CELLTYPE_FORMULA)          // Formeln spaeter loeschen
/*N*/               {
/*N*/                   ppDelCells[nDelCount++] = pOldCell;
/*N*/               }
/*N*/               else
/*N*/               {
/*N*/                     aHint.GetAddress().SetRow( nOldRow );
/*N*/                     aHint.SetCell( pOldCell );
/*N*/                   pDocument->Broadcast( aHint );
/*N*/                   if (eCellType != CELLTYPE_NOTE)
/*N*/                       pOldCell->ForgetBroadcaster();
/*N*/                   pOldCell->Delete();
/*N*/               }
/*N*/           }
/*N*/           else
/*N*/           {
/*?*/               if (nDelFlag & IDF_NOTE)
/*?*/                   if (pItems[j].pCell->GetNotePtr())
/*?*/                       pItems[j].pCell->DeleteNote();
/*?*/               ++j;
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/
/*N*/   // erst Listener abhaengen kann Neuberechnungen sparen
/*N*/   // eventuell werden dabei vorher entstandene NoteCell mitsamt
/*N*/   // ihren Broadcaster deleted!
/*N*/   for (i=0; i<nDelCount; i++)
/*N*/   {
/*?*/       ((ScFormulaCell*) ppDelCells[i])->EndListeningTo( pDocument );
/*N*/   }
/*N*/   // gibts die NoteCell und damit den Broadcaster noch?
/*N*/   // If not, discard them all before broadcasting takes place!
/*N*/   for (i=0; i<nDelCount; i++)
/*N*/   {
/*?*/       ScFormulaCell* pOldCell = (ScFormulaCell*) ppDelCells[i];
/*?*/       USHORT nIndex;
/*?*/       if ( !Search( pOldCell->aPos.Row(), nIndex ) )
/*?*/           pOldCell->ForgetBroadcaster();
/*N*/   }
/*N*/   for (i=0; i<nDelCount; i++)
/*N*/   {
/*?*/       ScFormulaCell* pOldCell = (ScFormulaCell*) ppDelCells[i];
/*?*/         aHint.SetAddress( pOldCell->aPos );
/*?*/         aHint.SetCell( pOldCell );
/*?*/       pDocument->Broadcast( aHint );
/*?*/       pOldCell->ForgetBroadcaster();
/*?*/       pOldCell->Delete();
/*N*/   }
/*N*/
/*N*/   delete[] ppDelCells;
/*N*/ }


/*N*/ void ScColumn::DeleteArea(USHORT nStartRow, USHORT nEndRow, USHORT nDelFlag)
/*N*/ {
/*N*/   //  FreeAll darf hier nicht gerufen werden wegen Broadcastern
/*N*/
/*N*/   //  Attribute erst am Ende, damit vorher noch zwischen Zahlen und Datum
/*N*/   //  unterschieden werden kann (#47901#)
/*N*/
/*N*/   USHORT nContFlag = nDelFlag & IDF_CONTENTS;
/*N*/   if (pItems && nCount && nContFlag)
/*N*/   {
/*N*/       if (nStartRow==0 && nEndRow==MAXROW)
/*N*/           DeleteRange( 0, nCount-1, nContFlag );
/*N*/       else
/*N*/       {
/*?*/           BOOL bFound=FALSE;
/*?*/           USHORT nStartIndex;
/*?*/           USHORT nEndIndex;
/*?*/           for (USHORT i = 0; i < nCount; i++)
/*?*/               if ((pItems[i].nRow >= nStartRow) && (pItems[i].nRow <= nEndRow))
/*?*/               {
/*?*/                   if (!bFound)
/*?*/                   {
/*?*/                       nStartIndex = i;
/*?*/                       bFound = TRUE;
/*?*/                   }
/*?*/                   nEndIndex = i;
/*?*/               }
/*?*/           if (bFound)
/*?*/               DeleteRange( nStartIndex, nEndIndex, nContFlag );
/*N*/       }
/*N*/   }
/*N*/
/*N*/   if ( nDelFlag & IDF_EDITATTR )
/*N*/   {
/*?*/       DBG_ASSERT( nContFlag == 0, "DeleteArea: falsche Flags" );
DBG_BF_ASSERT(0, "STRIP"); //STRIP001 /*?*/         RemoveEditAttribs( nStartRow, nEndRow );
/*N*/   }
/*N*/
/*N*/   //  Attribute erst hier
/*N*/   if ((nDelFlag & IDF_ATTRIB) == IDF_ATTRIB) pAttrArray->DeleteArea( nStartRow, nEndRow );
/*N*/   else if ((nDelFlag & IDF_ATTRIB) != 0) pAttrArray->DeleteHardAttr( nStartRow, nEndRow );
/*N*/ }


//STRIP001 ScFormulaCell* ScColumn::CreateRefCell( ScDocument* pDestDoc, const ScAddress& rDestPos,
//STRIP001                                          USHORT nIndex, USHORT nFlags ) const
//STRIP001 {
//STRIP001  USHORT nContFlags = nFlags & IDF_CONTENTS;
//STRIP001  if (!nContFlags)
//STRIP001      return NULL;
//STRIP001
//STRIP001  //  Testen, ob Zelle kopiert werden soll
//STRIP001  //  auch bei IDF_CONTENTS komplett, wegen Notes / Broadcastern
//STRIP001
//STRIP001  BOOL bMatch = FALSE;
//STRIP001  ScBaseCell* pCell = pItems[nIndex].pCell;
//STRIP001  CellType eCellType = pCell->GetCellType();
//STRIP001  switch ( eCellType )
//STRIP001  {
//STRIP001      case CELLTYPE_VALUE:
//STRIP001          {
//STRIP001              USHORT nValFlags = nFlags & (IDF_DATETIME|IDF_VALUE);
//STRIP001
//STRIP001              if ( nValFlags == (IDF_DATETIME|IDF_VALUE) )
//STRIP001                  bMatch = TRUE;
//STRIP001              else if ( nValFlags )
//STRIP001              {
//STRIP001                  ULONG nNumIndex = (ULONG)((SfxUInt32Item*)GetAttr(
//STRIP001                                  pItems[nIndex].nRow, ATTR_VALUE_FORMAT ))->GetValue();
//STRIP001                  short nTyp = pDocument->GetFormatTable()->GetType(nNumIndex);
//STRIP001                  if ((nTyp == NUMBERFORMAT_DATE) || (nTyp == NUMBERFORMAT_TIME) || (nTyp == NUMBERFORMAT_DATETIME))
//STRIP001                      bMatch = ((nFlags & IDF_DATETIME) != 0);
//STRIP001                  else
//STRIP001                      bMatch = ((nFlags & IDF_VALUE) != 0);
//STRIP001              }
//STRIP001          }
//STRIP001          break;
//STRIP001      case CELLTYPE_STRING:
//STRIP001      case CELLTYPE_EDIT:     bMatch = ((nFlags & IDF_STRING) != 0); break;
//STRIP001      case CELLTYPE_FORMULA:  bMatch = ((nFlags & IDF_FORMULA) != 0); break;
//STRIP001  }
//STRIP001  if (!bMatch)
//STRIP001      return NULL;
//STRIP001
//STRIP001
//STRIP001  //  Referenz einsetzen
//STRIP001  SingleRefData aRef;
//STRIP001  aRef.nCol = nCol;
//STRIP001  aRef.nRow = pItems[nIndex].nRow;
//STRIP001  aRef.nTab = nTab;
//STRIP001  aRef.InitFlags();                           // -> alles absolut
//STRIP001  aRef.SetFlag3D(TRUE);
//STRIP001
//STRIP001  //! 3D(FALSE) und TabRel(TRUE), wenn die endgueltige Position auf der selben Tabelle ist?
//STRIP001  //! (bei TransposeClip ist die Zielposition noch nicht bekannt)
//STRIP001
//STRIP001  aRef.CalcRelFromAbs( rDestPos );
//STRIP001
//STRIP001  ScTokenArray aArr;
//STRIP001  aArr.AddSingleReference( aRef );
//STRIP001
//STRIP001  return new ScFormulaCell( pDestDoc, rDestPos, &aArr );
//STRIP001 }


//  rColumn = Quelle
//  nRow1, nRow2 = Zielposition

//STRIP001 void ScColumn::CopyFromClip(USHORT nRow1, USHORT nRow2, short nDy,
//STRIP001                              USHORT nInsFlag, BOOL bAsLink, BOOL bSkipAttrForEmpty,
//STRIP001                              ScColumn& rColumn)
//STRIP001 {
//STRIP001  if ((nInsFlag & IDF_ATTRIB) != 0)
//STRIP001  {
//STRIP001      if ( bSkipAttrForEmpty )
//STRIP001      {
//STRIP001          //  copy only attributes for non-empty cells
//STRIP001          //  (notes are not counted as non-empty here, to match the content behavior)
//STRIP001
//STRIP001          USHORT nStartIndex;
//STRIP001          rColumn.Search( nRow1-nDy, nStartIndex );
//STRIP001          while ( nStartIndex < rColumn.nCount && rColumn.pItems[nStartIndex].nRow <= nRow2-nDy )
//STRIP001          {
//STRIP001              USHORT nEndIndex = nStartIndex;
//STRIP001              if ( rColumn.pItems[nStartIndex].pCell->GetCellType() != CELLTYPE_NOTE )
//STRIP001              {
//STRIP001                  USHORT nStartRow = rColumn.pItems[nStartIndex].nRow;
//STRIP001                  USHORT nEndRow = nStartRow;
//STRIP001
//STRIP001                  //  find consecutive non-empty cells
//STRIP001
//STRIP001                  while ( nEndRow < nRow2-nDy &&
//STRIP001                          nEndIndex+1 < rColumn.nCount &&
//STRIP001                          rColumn.pItems[nEndIndex+1].nRow == nEndRow+1 &&
//STRIP001                          rColumn.pItems[nEndIndex+1].pCell->GetCellType() != CELLTYPE_NOTE )
//STRIP001                  {
//STRIP001                      ++nEndIndex;
//STRIP001                      ++nEndRow;
//STRIP001                  }
//STRIP001
//STRIP001                  rColumn.pAttrArray->CopyAreaSafe( nStartRow+nDy, nEndRow+nDy, nDy, *pAttrArray );
//STRIP001              }
//STRIP001              nStartIndex = nEndIndex + 1;
//STRIP001          }
//STRIP001      }
//STRIP001      else
//STRIP001          rColumn.pAttrArray->CopyAreaSafe( nRow1, nRow2, nDy, *pAttrArray );
//STRIP001  }
//STRIP001  if ((nInsFlag & IDF_CONTENTS) == 0)
//STRIP001      return;
//STRIP001
//STRIP001  if ( bAsLink && nInsFlag == IDF_ALL )
//STRIP001  {
//STRIP001      //  bei "alles" werden auch leere Zellen referenziert
//STRIP001      //! IDF_ALL muss immer mehr Flags enthalten, als bei "Inhalte Einfuegen"
//STRIP001      //! einzeln ausgewaehlt werden koennen!
//STRIP001
//STRIP001      Resize( nCount + (nRow2-nRow1+1) );
//STRIP001
//STRIP001      ScAddress aDestPos( nCol, 0, nTab );        // Row wird angepasst
//STRIP001
//STRIP001      //  Referenz erzeugen (Quell-Position)
//STRIP001      SingleRefData aRef;
//STRIP001      aRef.nCol = rColumn.nCol;
//STRIP001      //  nRow wird angepasst
//STRIP001      aRef.nTab = rColumn.nTab;
//STRIP001      aRef.InitFlags();                           // -> alles absolut
//STRIP001      aRef.SetFlag3D(TRUE);
//STRIP001
//STRIP001      for (USHORT nDestRow = nRow1; nDestRow <= nRow2; nDestRow++)
//STRIP001      {
//STRIP001          aRef.nRow = nDestRow - nDy;             // Quell-Zeile
//STRIP001          aDestPos.SetRow( nDestRow );
//STRIP001
//STRIP001          aRef.CalcRelFromAbs( aDestPos );
//STRIP001          ScTokenArray aArr;
//STRIP001          aArr.AddSingleReference( aRef );
//STRIP001          Insert( nDestRow, new ScFormulaCell( pDocument, aDestPos, &aArr ) );
//STRIP001      }
//STRIP001
//STRIP001      return;
//STRIP001  }
//STRIP001
//STRIP001  USHORT nColCount = rColumn.nCount;
//STRIP001  if ((nInsFlag & IDF_CONTENTS) == IDF_CONTENTS && nRow2-nRow1 >= 64)
//STRIP001  {
//STRIP001      //! Resize immer aussen, wenn die Wiederholungen bekannt sind
//STRIP001      //! (dann hier gar nicht mehr)
//STRIP001
//STRIP001      USHORT nNew = nCount + nColCount;
//STRIP001      if ( nLimit < nNew )
//STRIP001          Resize( nNew );
//STRIP001  }
//STRIP001
//STRIP001  BOOL bAtEnd = FALSE;
//STRIP001  for (USHORT i = 0; i < nColCount && !bAtEnd; i++)
//STRIP001  {
//STRIP001      short nDestRow = rColumn.pItems[i].nRow + nDy;
//STRIP001      if ( nDestRow > (short) nRow2 )
//STRIP001          bAtEnd = TRUE;
//STRIP001      else if ( nDestRow >= (short) nRow1 )
//STRIP001      {
//STRIP001          //  rows at the beginning may be skipped if filtered rows are left out,
//STRIP001          //  nDestRow may be negative then
//STRIP001
//STRIP001          ScBaseCell* pOld = rColumn.pItems[i].pCell;
//STRIP001          ScBaseCell* pNew;
//STRIP001
//STRIP001          if ( bAsLink )
//STRIP001          {
//STRIP001              pNew = rColumn.CreateRefCell( pDocument,
//STRIP001                      ScAddress( nCol, (USHORT)nDestRow, nTab ), i, nInsFlag );
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              pNew = rColumn.CloneCell( i, nInsFlag, pDocument, ScAddress(nCol,(USHORT)nDestRow,nTab) );
//STRIP001
//STRIP001              if ( pNew && pNew->GetNotePtr() && (nInsFlag & IDF_NOTE) == 0 )
//STRIP001                  pNew->DeleteNote();
//STRIP001          }
//STRIP001
//STRIP001          if (pNew)
//STRIP001              Insert((USHORT)nDestRow, pNew);
//STRIP001      }
//STRIP001  }
//STRIP001 }


    //  Formelzellen werden jetzt schon hier kopiert,
    //  Notizen muessen aber evtl. noch geloescht werden

/*N*/ ScBaseCell* ScColumn::CloneCell(USHORT nIndex, USHORT nFlags,
/*N*/                                   ScDocument* pDestDoc, const ScAddress& rDestPos)
/*N*/ {
/*N*/   ScBaseCell* pNew = 0;
/*N*/   ScBaseCell* pSource = pItems[nIndex].pCell;
/*N*/   switch (pSource->GetCellType())
/*N*/   {
/*?*/       case CELLTYPE_NOTE:
/*?*/           if (nFlags & IDF_NOTE)
/*?*/               pNew = new ScNoteCell(*(ScNoteCell*)pSource);
/*?*/           break;
/*?*/       case CELLTYPE_EDIT:
/*?*/           if (nFlags & IDF_STRING)
/*?*/               pNew = new ScEditCell( *(ScEditCell*)pSource, pDestDoc );
/*?*/           break;
/*N*/       case CELLTYPE_STRING:
/*N*/           if (nFlags & IDF_STRING)
/*N*/               pNew = new ScStringCell(*(ScStringCell*)pSource);
/*N*/           break;
/*N*/       case CELLTYPE_VALUE:
/*N*/           {
/*N*/               BOOL bDoIns = FALSE;
/*N*/               USHORT nMask = nFlags & ( IDF_DATETIME | IDF_VALUE );
/*N*/               if ( nMask == (IDF_DATETIME | IDF_VALUE) )
/*N*/                   bDoIns = TRUE;
/*N*/               else if ( nMask )
/*N*/               {
/*?*/                   ULONG nNumIndex = (ULONG)((SfxUInt32Item*) GetAttr(
/*?*/                           pItems[nIndex].nRow, ATTR_VALUE_FORMAT ))->GetValue();
/*?*/                   short nTyp = pDocument->GetFormatTable()->GetType(nNumIndex);
/*?*/                   if (nTyp == NUMBERFORMAT_DATE || nTyp == NUMBERFORMAT_TIME || nTyp == NUMBERFORMAT_DATETIME)
/*?*/                       bDoIns = (nFlags & IDF_DATETIME)!=0;
/*?*/                   else
/*?*/                       bDoIns = (nFlags & IDF_VALUE)!=0;
/*N*/               }
/*N*/               if (bDoIns)
/*N*/                   pNew = new ScValueCell(*(ScValueCell*)pSource);
/*N*/           }
/*N*/           break;
/*?*/       case CELLTYPE_FORMULA:
/*?*/           {
/*?*/               ScFormulaCell* pForm = (ScFormulaCell*)pSource;
/*?*/               if (nFlags & IDF_FORMULA)
/*?*/               {
DBG_BF_ASSERT(0, "STRIP"); //STRIP001 /*?*/                     pNew = pForm->Clone( pDestDoc, rDestPos, TRUE );
/*?*/               }
/*?*/               else if ( (nFlags & (IDF_VALUE | IDF_DATETIME | IDF_STRING)) &&
/*?*/                           !pDestDoc->IsUndo() )
/*?*/               {
/*?*/                   //  #48491# ins Undo-Dokument immer nur die Original-Zelle kopieren,
/*?*/                   //  aus Formeln keine Value/String-Zellen erzeugen
/*?*/
/*?*/                   USHORT nErr = pForm->GetErrCode();
/*?*/                   if ( nErr )
/*?*/                   {
/*?*/                       //  Fehler werden immer mit "Zahlen" kopiert
/*?*/                       //  (Das ist hiermit willkuerlich so festgelegt)
/*?*/
/*?*/                       if ( nFlags & IDF_VALUE )
/*?*/                       {
DBG_BF_ASSERT(0, "STRIP"); //STRIP001 /*?*/                             ScFormulaCell* pErrCell = new ScFormulaCell( pDestDoc, rDestPos );
//STRIP001 /*?*/                            pErrCell->SetErrCode( nErr );
//STRIP001 /*?*/                            pNew = pErrCell;
/*?*/                       }
/*?*/                   }
/*?*/                   else if ( pForm->IsValue() )
/*?*/                   {
/*?*/                       BOOL bDoIns = FALSE;
/*?*/                       USHORT nMask = nFlags & ( IDF_DATETIME | IDF_VALUE );
/*?*/                       if ( nMask == (IDF_DATETIME | IDF_VALUE) )
/*?*/                           bDoIns = TRUE;
/*?*/                       else if ( nMask )
/*?*/                       {
/*?*/                           ULONG nNumIndex = (ULONG)((SfxUInt32Item*) GetAttr(
/*?*/                                   pItems[nIndex].nRow, ATTR_VALUE_FORMAT ))->GetValue();
/*?*/                           short nTyp = pDocument->GetFormatTable()->GetType(nNumIndex);
/*?*/                           if (nTyp == NUMBERFORMAT_DATE || nTyp == NUMBERFORMAT_TIME || nTyp == NUMBERFORMAT_DATETIME)
/*?*/                               bDoIns = (nFlags & IDF_DATETIME)!=0;
/*?*/                           else
/*?*/                               bDoIns = (nFlags & IDF_VALUE)!=0;
/*?*/                       }
/*?*/
/*?*/                       if (bDoIns)
/*?*/                       {
/*?*/                           double nVal = pForm->GetValue();
/*?*/                           pNew = new ScValueCell(nVal);
/*?*/                       }
/*?*/                   }
/*?*/                   else
/*?*/                   {
/*?*/                       if (nFlags & IDF_STRING)
/*?*/                       {
/*?*/                           String aString;
/*?*/                           pForm->GetString(aString);
/*?*/                           if ( aString.Len() )
/*?*/                               pNew = new ScStringCell(aString);
/*?*/                               // #33224# LeerStrings nicht kopieren
/*?*/                       }
/*?*/                   }
/*?*/                   if ( pNew && pSource->GetNotePtr() && ( nFlags & IDF_NOTE ) )
/*?*/                       pNew->SetNote(*pSource->GetNotePtr());
/*?*/               }
/*?*/           }
/*?*/           break;
/*N*/   }
/*N*/
/*N*/   if ( !pNew && pSource->GetNotePtr() && ( nFlags & IDF_NOTE ) )
/*?*/       pNew = new ScNoteCell(*pSource->GetNotePtr());
/*N*/
/*N*/   return pNew;
/*N*/ }


//STRIP001 void ScColumn::MixMarked( const ScMarkData& rMark, USHORT nFunction,
//STRIP001                          BOOL bSkipEmpty, ScColumn& rSrcCol )
//STRIP001 {
//STRIP001  USHORT nRow1, nRow2;
//STRIP001
//STRIP001  if (rMark.IsMultiMarked())
//STRIP001  {
//STRIP001      ScMarkArrayIter aIter( rMark.GetArray()+nCol );
//STRIP001      while (aIter.Next( nRow1, nRow2 ))
//STRIP001          MixData( nRow1, nRow2, nFunction, bSkipEmpty, rSrcCol );
//STRIP001  }
//STRIP001 }


//  Ergebnis in rVal1

//STRIP001 BOOL lcl_DoFunction( double& rVal1, double nVal2, USHORT nFunction )
//STRIP001 {
//STRIP001  BOOL bOk = FALSE;
//STRIP001  switch (nFunction)
//STRIP001  {
//STRIP001      case PASTE_ADD:
//STRIP001          bOk = SubTotal::SafePlus( rVal1, nVal2 );
//STRIP001          break;
//STRIP001      case PASTE_SUB:
//STRIP001          nVal2 = -nVal2;     //! geht das immer ohne Fehler?
//STRIP001          bOk = SubTotal::SafePlus( rVal1, nVal2 );
//STRIP001          break;
//STRIP001      case PASTE_MUL:
//STRIP001          bOk = SubTotal::SafeMult( rVal1, nVal2 );
//STRIP001          break;
//STRIP001      case PASTE_DIV:
//STRIP001          bOk = SubTotal::SafeDiv( rVal1, nVal2 );
//STRIP001          break;
//STRIP001  }
//STRIP001  return bOk;
//STRIP001 }


//STRIP001 void lcl_AddCode( ScTokenArray& rArr, ScFormulaCell* pCell )
//STRIP001 {
//STRIP001  rArr.AddOpCode(ocOpen);
//STRIP001
//STRIP001  ScTokenArray* pCode = pCell->GetCode();
//STRIP001  if (pCode)
//STRIP001  {
//STRIP001      ScToken* pToken = pCode->First();
//STRIP001      while (pToken)
//STRIP001      {
//STRIP001          rArr.AddToken(*pToken);
//STRIP001          pToken = pCode->Next();
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  rArr.AddOpCode(ocClose);
//STRIP001 }


//STRIP001 void ScColumn::MixData( USHORT nRow1, USHORT nRow2,
//STRIP001                          USHORT nFunction, BOOL bSkipEmpty,
//STRIP001                          ScColumn& rSrcCol )
//STRIP001 {
//STRIP001  USHORT nSrcCount = rSrcCol.nCount;
//STRIP001
//STRIP001  USHORT nIndex;
//STRIP001  Search( nRow1, nIndex );
//STRIP001
//STRIP001 //   USHORT nSrcIndex = 0;
//STRIP001  USHORT nSrcIndex;
//STRIP001  rSrcCol.Search( nRow1, nSrcIndex );         //! Testen, ob Daten ganz vorne
//STRIP001
//STRIP001  USHORT nNextThis = MAXROW+1;
//STRIP001  if ( nIndex < nCount )
//STRIP001      nNextThis = pItems[nIndex].nRow;
//STRIP001  USHORT nNextSrc = MAXROW+1;
//STRIP001  if ( nSrcIndex < nSrcCount )
//STRIP001      nNextSrc = rSrcCol.pItems[nSrcIndex].nRow;
//STRIP001
//STRIP001  while ( nNextThis <= nRow2 || nNextSrc <= nRow2 )
//STRIP001  {
//STRIP001      USHORT nRow = Min( nNextThis, nNextSrc );
//STRIP001
//STRIP001      ScBaseCell* pSrc = NULL;
//STRIP001      ScBaseCell* pDest = NULL;
//STRIP001      ScBaseCell* pNew = NULL;
//STRIP001      BOOL bDelete = FALSE;
//STRIP001
//STRIP001      if ( nSrcIndex < nSrcCount && nNextSrc == nRow )
//STRIP001          pSrc = rSrcCol.pItems[nSrcIndex].pCell;
//STRIP001
//STRIP001      if ( nIndex < nCount && nNextThis == nRow )
//STRIP001          pDest = pItems[nIndex].pCell;
//STRIP001
//STRIP001      DBG_ASSERT( pSrc || pDest, "Nanu ??!?" );
//STRIP001
//STRIP001      CellType eSrcType  = pSrc  ? pSrc->GetCellType()  : CELLTYPE_NONE;
//STRIP001      CellType eDestType = pDest ? pDest->GetCellType() : CELLTYPE_NONE;
//STRIP001
//STRIP001      BOOL bSrcEmpty = ( eSrcType == CELLTYPE_NONE || eSrcType == CELLTYPE_NOTE );
//STRIP001      BOOL bDestEmpty = ( eDestType == CELLTYPE_NONE || eDestType == CELLTYPE_NOTE );
//STRIP001
//STRIP001      if ( bSkipEmpty && bDestEmpty )     // Originalzelle wiederherstellen
//STRIP001      {
//STRIP001          if ( pSrc )                     // war da eine Zelle?
//STRIP001          {
//STRIP001              pNew = pSrc->Clone( pDocument );
//STRIP001          }
//STRIP001      }
//STRIP001      else if ( nFunction )               // wirklich Rechenfunktion angegeben
//STRIP001      {
//STRIP001          double nVal1;
//STRIP001          double nVal2;
//STRIP001          if ( eSrcType == CELLTYPE_VALUE )
//STRIP001              nVal1 = ((ScValueCell*)pSrc)->GetValue();
//STRIP001          else
//STRIP001              nVal1 = 0.0;
//STRIP001          if ( eDestType == CELLTYPE_VALUE )
//STRIP001              nVal2 = ((ScValueCell*)pDest)->GetValue();
//STRIP001          else
//STRIP001              nVal2 = 0.0;
//STRIP001
//STRIP001          //  leere Zellen werden als Werte behandelt
//STRIP001
//STRIP001          BOOL bSrcVal  = ( bSrcEmpty || eSrcType == CELLTYPE_VALUE );
//STRIP001          BOOL bDestVal  = ( bDestEmpty || eDestType == CELLTYPE_VALUE );
//STRIP001
//STRIP001          BOOL bSrcText = ( eSrcType == CELLTYPE_STRING ||
//STRIP001                              eSrcType == CELLTYPE_EDIT );
//STRIP001          BOOL bDestText = ( eDestType == CELLTYPE_STRING ||
//STRIP001                              eDestType == CELLTYPE_EDIT );
//STRIP001
//STRIP001          //  sonst bleibt nur Formel...
//STRIP001
//STRIP001          if ( bSrcEmpty && bDestEmpty )
//STRIP001          {
//STRIP001              //  beide leer -> nix
//STRIP001          }
//STRIP001          else if ( bSrcVal && bDestVal )
//STRIP001          {
//STRIP001              //  neuen Wert eintragen, oder Fehler bei Ueberlauf
//STRIP001
//STRIP001              BOOL bOk = lcl_DoFunction( nVal1, nVal2, nFunction );
//STRIP001
//STRIP001              if (bOk)
//STRIP001                  pNew = new ScValueCell( nVal1 );
//STRIP001              else
//STRIP001              {
//STRIP001                  ScFormulaCell* pFC = new ScFormulaCell( pDocument,
//STRIP001                                              ScAddress( nCol, nRow, nTab ) );
//STRIP001                  pFC->SetErrCode( errNoValue );
//STRIP001                  //! oder NOVALUE, dann auch in consoli,
//STRIP001                  //! sonst in Interpreter::GetCellValue die Abfrage auf errNoValue raus
//STRIP001                  //! (dann geht Stringzelle+Wertzelle nicht mehr)
//STRIP001                  pNew = pFC;
//STRIP001              }
//STRIP001          }
//STRIP001          else if ( bSrcText || bDestText )
//STRIP001          {
//STRIP001              //  mit Texten wird nicht gerechnet - immer "alte" Zelle, also pSrc
//STRIP001
//STRIP001              if (pSrc)
//STRIP001                  pNew = pSrc->Clone( pDocument );
//STRIP001              else if (pDest)
//STRIP001                  bDelete = TRUE;
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              //  Kombination aus Wert und mindestens einer Formel -> Formel erzeugen
//STRIP001
//STRIP001              ScTokenArray aArr;
//STRIP001
//STRIP001              //  erste Zelle
//STRIP001              if ( eSrcType == CELLTYPE_FORMULA )
//STRIP001                  lcl_AddCode( aArr, (ScFormulaCell*)pSrc );
//STRIP001              else
//STRIP001                  aArr.AddDouble( nVal1 );
//STRIP001
//STRIP001              //  Operator
//STRIP001              OpCode eOp = ocAdd;
//STRIP001              switch ( nFunction )
//STRIP001              {
//STRIP001                  case PASTE_ADD: eOp = ocAdd; break;
//STRIP001                  case PASTE_SUB: eOp = ocSub; break;
//STRIP001                  case PASTE_MUL: eOp = ocMul; break;
//STRIP001                  case PASTE_DIV: eOp = ocDiv; break;
//STRIP001              }
//STRIP001              aArr.AddOpCode(eOp);                // Funktion
//STRIP001
//STRIP001              //  zweite Zelle
//STRIP001              if ( eDestType == CELLTYPE_FORMULA )
//STRIP001                  lcl_AddCode( aArr, (ScFormulaCell*)pDest );
//STRIP001              else
//STRIP001                  aArr.AddDouble( nVal2 );
//STRIP001
//STRIP001              pNew = new ScFormulaCell( pDocument, ScAddress( nCol, nRow, nTab ), &aArr );
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001
//STRIP001      if ( pNew || bDelete )          // neues Ergebnis ?
//STRIP001      {
//STRIP001          if (pDest && !pNew)                     // alte Zelle da ?
//STRIP001          {
//STRIP001              if ( pDest->GetBroadcaster() )
//STRIP001                  pNew = new ScNoteCell;          // Broadcaster uebernehmen
//STRIP001              else
//STRIP001                  Delete(nRow);                   // -> loeschen
//STRIP001          }
//STRIP001          if (pNew)
//STRIP001              Insert(nRow, pNew);     // neue einfuegen
//STRIP001
//STRIP001          Search( nRow, nIndex );     // alles kann sich verschoben haben
//STRIP001          if (pNew)
//STRIP001              nNextThis = nRow;       // nIndex zeigt jetzt genau auf nRow
//STRIP001          else
//STRIP001              nNextThis = ( nIndex < nCount ) ? pItems[nIndex].nRow : MAXROW+1;
//STRIP001      }
//STRIP001
//STRIP001      if ( nNextThis == nRow )
//STRIP001      {
//STRIP001          ++nIndex;
//STRIP001          nNextThis = ( nIndex < nCount ) ? pItems[nIndex].nRow : MAXROW+1;
//STRIP001      }
//STRIP001      if ( nNextSrc == nRow )
//STRIP001      {
//STRIP001          ++nSrcIndex;
//STRIP001          nNextSrc = ( nSrcIndex < nSrcCount ) ?
//STRIP001                          rSrcCol.pItems[nSrcIndex].nRow :
//STRIP001                          MAXROW+1;
//STRIP001      }
//STRIP001  }
//STRIP001 }


/*N*/ ScAttrIterator* ScColumn::CreateAttrIterator( USHORT nStartRow, USHORT nEndRow ) const
/*N*/ {
/*N*/   return new ScAttrIterator( pAttrArray, nStartRow, nEndRow );
/*N*/ }


/*N*/ void ScColumn::StartAllListeners()
/*N*/ {
/*N*/   if (pItems)
/*N*/       for (USHORT i = 0; i < nCount; i++)
/*N*/       {
/*N*/           ScBaseCell* pCell = pItems[i].pCell;
/*N*/           if ( pCell->GetCellType() == CELLTYPE_FORMULA )
/*N*/           {
/*N*/               USHORT nRow = pItems[i].nRow;
/*N*/               ((ScFormulaCell*)pCell)->StartListeningTo( pDocument );
/*N*/               if ( nRow != pItems[i].nRow )
/*N*/                   Search( nRow, i );      // Listener eingefuegt?
/*N*/           }
/*N*/       }
/*N*/ }


/*N*/ void ScColumn::StartNameListeners( BOOL bOnlyRelNames )
/*N*/ {
/*N*/   if (pItems)
/*N*/     {
/*N*/         USHORT nNameListening = (bOnlyRelNames ? SC_LISTENING_NAMES_REL :
/*N*/             SC_LISTENING_NAMES_REL | SC_LISTENING_NAMES_ABS);
/*N*/       for (USHORT i = 0; i < nCount; i++)
/*N*/       {
/*N*/           ScBaseCell* pCell = pItems[i].pCell;
/*N*/           if ( pCell->GetCellType() == CELLTYPE_FORMULA )
/*N*/           {
/*N*/               USHORT nRow = pItems[i].nRow;
/*N*/                 ((ScFormulaCell*)pCell)->StartListeningTo( pDocument, nNameListening );
/*N*/               if ( nRow != pItems[i].nRow )
/*N*/                   Search( nRow, i );      // Listener eingefuegt?
/*N*/           }
/*N*/       }
/*N*/     }
/*N*/ }


//STRIP001 void ScColumn::BroadcastInArea( USHORT nRow1, USHORT nRow2 )
//STRIP001 {
//STRIP001  if ( pItems )
//STRIP001  {
//STRIP001      USHORT nIndex, nRow;
//STRIP001      Search( nRow1, nIndex );
//STRIP001      while ( nIndex < nCount && (nRow = pItems[nIndex].nRow) <= nRow2 )
//STRIP001      {
//STRIP001          ScBaseCell* pCell = pItems[nIndex].pCell;
//STRIP001          if ( pCell->GetCellType() == CELLTYPE_FORMULA )
//STRIP001              ((ScFormulaCell*)pCell)->SetDirty();
//STRIP001          else
//STRIP001              pDocument->Broadcast( ScHint( SC_HINT_DATACHANGED,
//STRIP001                  ScAddress( nCol, nRow, nTab ), pCell ) );
//STRIP001          nIndex++;
//STRIP001      }
//STRIP001  }
//STRIP001 }


//STRIP001 void ScColumn::StartListeningInArea( USHORT nRow1, USHORT nRow2 )
//STRIP001 {
//STRIP001  if ( pItems )
//STRIP001  {
//STRIP001      USHORT nIndex, nRow;
//STRIP001      Search( nRow1, nIndex );
//STRIP001      while ( nIndex < nCount && (nRow = pItems[nIndex].nRow) <= nRow2 )
//STRIP001      {
//STRIP001          ScBaseCell* pCell = pItems[nIndex].pCell;
//STRIP001          if ( pCell->GetCellType() == CELLTYPE_FORMULA )
//STRIP001              ((ScFormulaCell*)pCell)->StartListeningTo( pDocument );
//STRIP001          if ( nRow != pItems[nIndex].nRow )
//STRIP001              Search( nRow, nIndex );     // durch Listening eingefuegt
//STRIP001          nIndex++;
//STRIP001      }
//STRIP001  }
//STRIP001 }


//  TRUE = Zahlformat gesetzt
/*N*/ BOOL ScColumn::SetString( USHORT nRow, USHORT nTab, const String& rString )
/*N*/ {
/*N*/   BOOL bNumFmtSet = FALSE;
/*N*/   if (VALIDROW(nRow))
/*N*/   {
/*N*/       ScBaseCell* pNewCell = NULL;
/*N*/       BOOL bIsLoading = FALSE;
/*N*/       if (rString.Len() > 0)
/*N*/       {
/*N*/           double nVal;
/*N*/           ULONG nIndex, nOldIndex;
/*N*/           sal_Unicode cFirstChar;
/*N*/           SvNumberFormatter* pFormatter = pDocument->GetFormatTable();
/*N*/           SfxObjectShell* pDocSh = pDocument->GetDocumentShell();
/*N*/           if ( pDocSh )
/*N*/               bIsLoading = pDocSh->IsLoading();
/*N*/           // IsLoading bei ConvertFrom Import
/*N*/           if ( !bIsLoading )
/*N*/           {
/*N*/               nIndex = nOldIndex = GetNumberFormat( nRow );
/*N*/               if ( rString.Len() > 1
/*N*/                       && pFormatter->GetType(nIndex) != NUMBERFORMAT_TEXT )
/*N*/                   cFirstChar = rString.GetChar(0);
/*N*/               else
/*N*/                   cFirstChar = 0;                             // Text
/*N*/           }
/*N*/           else
/*N*/           {   // waehrend ConvertFrom Import gibt es keine gesetzten Formate
/*N*/               cFirstChar = rString.GetChar(0);
/*N*/           }
/*N*/
/*N*/           if ( cFirstChar == '=' )
/*N*/           {
/*?*/               if ( rString.Len() == 1 )                       // = Text
/*?*/                   pNewCell = new ScStringCell( rString );
/*?*/               else                                            // =Formel
/*?*/                   pNewCell = new ScFormulaCell( pDocument,
/*?*/                       ScAddress( nCol, nRow, nTab ), rString, 0 );
/*N*/           }
/*N*/           else if ( cFirstChar == '\'')                       // 'Text
/*?*/               pNewCell = new ScStringCell( rString.Copy(1) );
/*N*/           else
/*N*/           {
/*N*/               BOOL bIsText = FALSE;
/*N*/               if ( bIsLoading )
/*N*/               {
/*N*/                   if ( pItems && nCount )
/*N*/                   {
/*?*/                       String aStr;
/*?*/                       USHORT i = nCount;
/*?*/                       USHORT nStop = (i >= 3 ? i - 3 : 0);
/*?*/                       // die letzten Zellen vergleichen, ob gleicher String
/*?*/                       // und IsNumberFormat eingespart werden kann
/*?*/                       do
/*?*/                       {
/*?*/                           i--;
/*?*/                           ScBaseCell* pCell = pItems[i].pCell;
/*?*/                           switch ( pCell->GetCellType() )
/*?*/                           {
/*?*/                               case CELLTYPE_STRING :
/*?*/                                   ((ScStringCell*)pCell)->GetString( aStr );
/*?*/                                   if ( rString == aStr )
/*?*/                                       bIsText = TRUE;
/*?*/                               break;
/*?*/                               case CELLTYPE_NOTE :    // durch =Formel referenziert
/*?*/                               break;
/*?*/                               default:
/*?*/                                   if ( i == nCount - 1 )
/*?*/                                       i = 0;
/*?*/                                       // wahrscheinlich ganze Spalte kein String
/*?*/                           }
/*?*/                       } while ( i && i > nStop && !bIsText );
/*N*/                   }
/*N*/                   // nIndex fuer IsNumberFormat vorbelegen
/*N*/                   if ( !bIsText )
/*N*/                       nIndex = nOldIndex = pFormatter->GetStandardIndex();
/*N*/               }
/*N*/               if ( !bIsText &&
/*N*/                       pFormatter->IsNumberFormat(rString, nIndex, nVal) )
/*N*/               {                                               // Zahl
/*?*/                   pNewCell = new ScValueCell( nVal );
/*?*/                   if ( nIndex != nOldIndex)
/*?*/                   {
/*?*/                       ApplyAttr( nRow, SfxUInt32Item( ATTR_VALUE_FORMAT,
/*?*/                           (UINT32) nIndex) );
/*?*/                       bNumFmtSet = TRUE;
/*?*/                   }
/*N*/               }
/*N*/               else                                            // Text
/*N*/                   pNewCell = new ScStringCell( rString );
/*N*/           }
/*N*/       }
/*N*/
/*N*/       if ( bIsLoading && (!nCount || nRow > pItems[nCount-1].nRow) )
/*N*/       {   // Search einsparen und ohne Umweg ueber Insert, Listener aufbauen
/*N*/           // und Broadcast kommt eh erst nach dem Laden
/*N*/           if ( pNewCell )
/*N*/               Append( nRow, pNewCell );
/*N*/       }
/*N*/       else
/*N*/       {
/*N*/           USHORT i;
/*N*/           if (Search(nRow, i))
/*N*/           {
/*?*/               ScBaseCell* pOldCell = pItems[i].pCell;
/*?*/               const ScPostIt* pNote = pOldCell->GetNotePtr();
/*?*/               ScBroadcasterList* pBC = pOldCell->GetBroadcaster();
/*?*/               if (pNewCell || pNote || pBC)
/*?*/               {
/*?*/                   if (!pNewCell)
/*?*/                       pNewCell = new ScNoteCell();
/*?*/                   if (pNote)
/*?*/                       pNewCell->SetNote(*pNote);
/*?*/                   if (pBC)
/*?*/                   {
/*?*/                       pNewCell->SetBroadcaster(pBC);
/*?*/                       pOldCell->ForgetBroadcaster();
/*?*/                       pLastFormulaTreeTop = 0;    // Err527 Workaround
/*?*/                   }
/*?*/
/*?*/                   if ( pOldCell->GetCellType() == CELLTYPE_FORMULA )
/*?*/                   {
/*?*/                       pOldCell->EndListeningTo( pDocument );
/*?*/                       // falls in EndListening NoteCell in gleicher Col zerstoert
/*?*/                       if ( i >= nCount || pItems[i].nRow != nRow )
/*?*/                           Search(nRow, i);
/*?*/                   }
/*?*/                   pOldCell->Delete();
/*?*/                   pItems[i].pCell = pNewCell;         // ersetzen
/*?*/                   if ( pNewCell->GetCellType() == CELLTYPE_FORMULA )
/*?*/                   {
/*?*/                       pNewCell->StartListeningTo( pDocument );
/*?*/                       ((ScFormulaCell*)pNewCell)->SetDirty();
/*?*/                   }
/*?*/                   else
/*?*/                       pDocument->Broadcast( ScHint( SC_HINT_DATACHANGED,
/*?*/                           ScAddress( nCol, nRow, nTab ), pNewCell ) );
/*?*/               }
/*?*/               else
/*?*/               {
/*?*/                   DeleteAtIndex(i);                   // loeschen und Broadcast
/*?*/               }
/*N*/           }
/*N*/           else if (pNewCell)
/*N*/           {
/*N*/               Insert(nRow, pNewCell);                 // neu eintragen und Broadcast
/*N*/           }
/*N*/       }
/*N*/
/*N*/       //  hier keine Formate mehr fuer Formeln setzen!
/*N*/       //  (werden bei der Ausgabe abgefragt)
/*N*/
/*N*/   }
/*N*/   return bNumFmtSet;
/*N*/ }


//STRIP001 void ScColumn::GetFilterEntries(USHORT nStartRow, USHORT nEndRow, TypedStrCollection& rStrings)
//STRIP001 {
//STRIP001  SvNumberFormatter* pFormatter = pDocument->GetFormatTable();
//STRIP001  String aString;
//STRIP001  USHORT nRow;
//STRIP001  USHORT nIndex;
//STRIP001
//STRIP001  Search( nStartRow, nIndex );
//STRIP001
//STRIP001  while ( (nIndex < nCount) ? ((nRow=pItems[nIndex].nRow) <= nEndRow) : FALSE )
//STRIP001  {
//STRIP001      ScBaseCell*          pCell    = pItems[nIndex].pCell;
//STRIP001      TypedStrData*        pData;
//STRIP001      ULONG                nFormat  = GetNumberFormat( nRow );
//STRIP001
//STRIP001      ScCellFormat::GetInputString( pCell, nFormat, aString, *pFormatter );
//STRIP001
//STRIP001      if ( pDocument->HasStringData( nCol, nRow, nTab ) )
//STRIP001          pData = new TypedStrData( aString );
//STRIP001      else
//STRIP001      {
//STRIP001          double nValue;
//STRIP001
//STRIP001          switch ( pCell->GetCellType() )
//STRIP001          {
//STRIP001              case CELLTYPE_VALUE:
//STRIP001                  nValue = ((ScValueCell*)pCell)->GetValue();
//STRIP001                  break;
//STRIP001
//STRIP001              case CELLTYPE_FORMULA:
//STRIP001                  nValue = ((ScFormulaCell*)pCell)->GetValue();
//STRIP001                  break;
//STRIP001
//STRIP001              default:
//STRIP001                  nValue = 0.0;
//STRIP001          }
//STRIP001
//STRIP001          pData = new TypedStrData( aString, nValue, SC_STRTYPE_VALUE );
//STRIP001      }
//STRIP001
//STRIP001      if ( !rStrings.Insert( pData ) )
//STRIP001          delete pData;                               // doppelt
//STRIP001
//STRIP001      ++nIndex;
//STRIP001  }
//STRIP001 }

//
//  GetDataEntries - Strings aus zusammenhaengendem Bereich um nRow
//

//  DATENT_MAX      - max. Anzahl Eintrage in Liste fuer Auto-Eingabe
//  DATENT_SEARCH   - max. Anzahl Zellen, die durchsucht werden - neu: nur Strings zaehlen
#define DATENT_MAX      200
#define DATENT_SEARCH   2000


//STRIP001 BOOL ScColumn::GetDataEntries(USHORT nStartRow, TypedStrCollection& rStrings, BOOL bLimit)
//STRIP001 {
//STRIP001  BOOL bFound = FALSE;
//STRIP001  USHORT nThisIndex;
//STRIP001  BOOL bThisUsed = Search( nStartRow, nThisIndex );
//STRIP001  String aString;
//STRIP001  USHORT nCells = 0;
//STRIP001
//STRIP001  //  Die Beschraenkung auf angrenzende Zellen (ohne Luecken) ist nicht mehr gewollt
//STRIP001  //  (Featurekommission zur 5.1), stattdessen abwechselnd nach oben und unten suchen,
//STRIP001  //  damit naheliegende Zellen wenigstens zuerst gefunden werden.
//STRIP001  //! Abstaende der Zeilennummern vergleichen? (Performance??)
//STRIP001
//STRIP001  USHORT nUpIndex = nThisIndex;       // zeigt hinter die Zelle
//STRIP001  USHORT nDownIndex = nThisIndex;     // zeigt auf die Zelle
//STRIP001  if (bThisUsed)
//STRIP001      ++nDownIndex;                   // Startzelle ueberspringen
//STRIP001
//STRIP001  while ( nUpIndex || nDownIndex < nCount )
//STRIP001  {
//STRIP001      if ( nUpIndex )                 // nach oben
//STRIP001      {
//STRIP001          ScBaseCell* pCell = pItems[nUpIndex-1].pCell;
//STRIP001          CellType eType = pCell->GetCellType();
//STRIP001          if (eType == CELLTYPE_STRING || eType == CELLTYPE_EDIT)     // nur Strings interessieren
//STRIP001          {
//STRIP001              if (eType == CELLTYPE_STRING)
//STRIP001                  ((ScStringCell*)pCell)->GetString(aString);
//STRIP001              else
//STRIP001                  ((ScEditCell*)pCell)->GetString(aString);
//STRIP001
//STRIP001              TypedStrData* pData = new TypedStrData(aString);
//STRIP001              if ( !rStrings.Insert( pData ) )
//STRIP001                  delete pData;                                           // doppelt
//STRIP001              else if ( bLimit && rStrings.GetCount() >= DATENT_MAX )
//STRIP001                  break;                                                  // Maximum erreicht
//STRIP001              bFound = TRUE;
//STRIP001
//STRIP001              if ( bLimit )
//STRIP001                  if (++nCells >= DATENT_SEARCH)
//STRIP001                      break;                                  // genug gesucht
//STRIP001          }
//STRIP001          --nUpIndex;
//STRIP001      }
//STRIP001
//STRIP001      if ( nDownIndex < nCount )      // nach unten
//STRIP001      {
//STRIP001          ScBaseCell* pCell = pItems[nDownIndex].pCell;
//STRIP001          CellType eType = pCell->GetCellType();
//STRIP001          if (eType == CELLTYPE_STRING || eType == CELLTYPE_EDIT)     // nur Strings interessieren
//STRIP001          {
//STRIP001              if (eType == CELLTYPE_STRING)
//STRIP001                  ((ScStringCell*)pCell)->GetString(aString);
//STRIP001              else
//STRIP001                  ((ScEditCell*)pCell)->GetString(aString);
//STRIP001
//STRIP001              TypedStrData* pData = new TypedStrData(aString);
//STRIP001              if ( !rStrings.Insert( pData ) )
//STRIP001                  delete pData;                                           // doppelt
//STRIP001              else if ( bLimit && rStrings.GetCount() >= DATENT_MAX )
//STRIP001                  break;                                                  // Maximum erreicht
//STRIP001              bFound = TRUE;
//STRIP001
//STRIP001              if ( bLimit )
//STRIP001                  if (++nCells >= DATENT_SEARCH)
//STRIP001                      break;                                  // genug gesucht
//STRIP001          }
//STRIP001          ++nDownIndex;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  return bFound;
//STRIP001 }

#undef DATENT_MAX
#undef DATENT_SEARCH


//STRIP001 void ScColumn::RemoveProtected( USHORT nStartRow, USHORT nEndRow )
//STRIP001 {
//STRIP001  ScAttrIterator aAttrIter( pAttrArray, nStartRow, nEndRow );
//STRIP001  USHORT nTop;
//STRIP001  USHORT nBottom;
//STRIP001  USHORT nIndex;
//STRIP001  const ScPatternAttr* pPattern = aAttrIter.Next( nTop, nBottom );
//STRIP001  while (pPattern)
//STRIP001  {
//STRIP001      const ScProtectionAttr* pAttr = (const ScProtectionAttr*)&pPattern->GetItem(ATTR_PROTECTION);
//STRIP001      if ( pAttr->GetHideCell() )
//STRIP001          DeleteArea( nTop, nBottom, IDF_CONTENTS );
//STRIP001      else if ( pAttr->GetHideFormula() )
//STRIP001      {
//STRIP001          Search( nTop, nIndex );
//STRIP001          while ( nIndex<nCount && pItems[nIndex].nRow<=nBottom )
//STRIP001          {
//STRIP001              if ( pItems[nIndex].pCell->GetCellType() == CELLTYPE_FORMULA )
//STRIP001              {
//STRIP001                  ScFormulaCell* pFormula = (ScFormulaCell*)pItems[nIndex].pCell;
//STRIP001                  if (pFormula->IsValue())
//STRIP001                  {
//STRIP001                      double nVal = pFormula->GetValue();
//STRIP001                      pItems[nIndex].pCell = new ScValueCell( nVal );
//STRIP001                  }
//STRIP001                  else
//STRIP001                  {
//STRIP001                      String aString;
//STRIP001                      pFormula->GetString(aString);
//STRIP001                      pItems[nIndex].pCell = new ScStringCell( aString );
//STRIP001                  }
//STRIP001                  delete pFormula;
//STRIP001              }
//STRIP001              ++nIndex;
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      pPattern = aAttrIter.Next( nTop, nBottom );
//STRIP001  }
//STRIP001 }


/*N*/ void ScColumn::SetError( USHORT nRow, const USHORT nError)
/*N*/ {
/*N*/   if (VALIDROW(nRow))
/*N*/   {
/*N*/       ScFormulaCell* pCell = new ScFormulaCell
/*N*/           ( pDocument, ScAddress( nCol, nRow, nTab ) );
/*N*/       pCell->SetErrCode( nError );
/*N*/       Insert( nRow, pCell );
/*N*/   }
/*N*/ }


/*N*/ void ScColumn::SetValue( USHORT nRow, const double& rVal)
/*N*/ {
/*N*/   if (VALIDROW(nRow))
/*N*/   {
/*N*/       ScBaseCell* pCell = new ScValueCell(rVal);
/*N*/       Insert( nRow, pCell );
/*N*/   }
/*N*/ }


/*N*/ void ScColumn::SetNote( USHORT nRow, const ScPostIt& rNote)
/*N*/ {
/*N*/   BOOL bEmpty = !rNote.GetText().Len();
/*N*/
/*N*/   USHORT nIndex;
/*N*/   if (Search(nRow, nIndex))
/*N*/   {
/*N*/       ScBaseCell* pCell = pItems[nIndex].pCell;
/*N*/       if (bEmpty && pCell->GetCellType() == CELLTYPE_NOTE && !pCell->GetBroadcaster())
/*?*/           DeleteAtIndex(nIndex);
/*N*/       else
/*N*/           pCell->SetNote(rNote);
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       if (!bEmpty)
/*N*/           Insert(nRow, new ScNoteCell(rNote));
/*N*/   }
/*N*/ }


/*N*/ void ScColumn::GetString( USHORT nRow, String& rString ) const
/*N*/ {
/*N*/   USHORT  nIndex;
/*N*/   Color* pColor;
/*N*/   if (Search(nRow, nIndex))
/*N*/   {
/*N*/       ScBaseCell* pCell = pItems[nIndex].pCell;
/*N*/       if (pCell->GetCellType() != CELLTYPE_NOTE)
/*N*/       {
/*N*/           ULONG nFormat = GetNumberFormat( nRow );
/*N*/           ScCellFormat::GetString( pCell, nFormat, rString, &pColor, *(pDocument->GetFormatTable()) );
/*N*/       }
/*N*/       else
/*N*/           rString.Erase();
/*N*/   }
/*N*/   else
/*N*/       rString.Erase();
/*N*/ }


/*N*/ void ScColumn::GetInputString( USHORT nRow, String& rString ) const
/*N*/ {
/*N*/   USHORT  nIndex;
/*N*/   if (Search(nRow, nIndex))
/*N*/   {
/*?*/       ScBaseCell* pCell = pItems[nIndex].pCell;
/*?*/       if (pCell->GetCellType() != CELLTYPE_NOTE)
/*?*/       {
/*?*/           ULONG nFormat = GetNumberFormat( nRow );
/*?*/           ScCellFormat::GetInputString( pCell, nFormat, rString, *(pDocument->GetFormatTable()) );
/*?*/       }
/*?*/       else
/*?*/           rString.Erase();
/*N*/   }
/*N*/   else
/*N*/       rString.Erase();
/*N*/ }


/*N*/ double ScColumn::GetValue( USHORT nRow ) const
/*N*/ {
/*N*/   USHORT  nIndex;
/*N*/   if (Search(nRow, nIndex))
/*N*/   {
/*N*/       ScBaseCell* pCell = pItems[nIndex].pCell;
/*N*/       switch (pCell->GetCellType())
/*N*/       {
/*N*/           case CELLTYPE_VALUE:
/*N*/               return ((ScValueCell*)pCell)->GetValue();
/*N*/               break;
/*N*/           case CELLTYPE_FORMULA:
/*N*/               {
/*N*/                   if (((ScFormulaCell*)pCell)->IsValue())
/*N*/                       return ((ScFormulaCell*)pCell)->GetValue();
/*N*/                   else
/*N*/                       return 0.0;
/*N*/               }
/*N*/               break;
/*N*/           default:
/*N*/               return 0.0;
/*N*/               break;
/*N*/       }
/*N*/   }
/*N*/   return 0.0;
/*N*/ }


/*N*/ void ScColumn::GetFormula( USHORT nRow, String& rFormula, BOOL ) const
/*N*/ {
/*N*/   USHORT  nIndex;
/*N*/   if (Search(nRow, nIndex))
/*N*/   {
/*N*/       ScBaseCell* pCell = pItems[nIndex].pCell;
/*N*/       if (pCell->GetCellType() == CELLTYPE_FORMULA)
/*N*/           ((ScFormulaCell*)pCell)->GetFormula( rFormula );
/*N*/       else
/*N*/           rFormula.Erase();
/*N*/   }
/*N*/   else
/*N*/       rFormula.Erase();
/*N*/ }


/*N*/ BOOL ScColumn::GetNote( USHORT nRow, ScPostIt& rNote) const
/*N*/ {
/*N*/   BOOL    bHasNote = FALSE;
/*N*/   USHORT  nIndex;
/*N*/   if (Search(nRow, nIndex))
/*N*/       bHasNote = pItems[nIndex].pCell->GetNote(rNote);
/*N*/   else
/*?*/       rNote.Clear();
/*N*/
/*N*/   return bHasNote;
/*N*/ }


/*N*/ CellType ScColumn::GetCellType( USHORT nRow ) const
/*N*/ {
/*N*/   USHORT  nIndex;
/*N*/   if (Search(nRow, nIndex))
/*N*/       return pItems[nIndex].pCell->GetCellType();
/*N*/   return CELLTYPE_NONE;
/*N*/ }


/*N*/ USHORT ScColumn::GetErrCode( USHORT nRow ) const
/*N*/ {
/*N*/   USHORT  nIndex;
/*N*/   if (Search(nRow, nIndex))
/*N*/   {
/*N*/       ScBaseCell* pCell = pItems[nIndex].pCell;
/*N*/       if (pCell->GetCellType() == CELLTYPE_FORMULA)
/*N*/           return ((ScFormulaCell*)pCell)->GetErrCode();
/*N*/   }
/*N*/   return 0;
/*N*/ }


/*N*/ BOOL ScColumn::HasStringData( USHORT nRow ) const
/*N*/ {
/*N*/   USHORT  nIndex;
/*N*/   if (Search(nRow, nIndex))
/*N*/       return (pItems[nIndex].pCell)->HasStringData();
/*N*/   return FALSE;
/*N*/ }


/*N*/ BOOL ScColumn::HasValueData( USHORT nRow ) const
/*N*/ {
/*N*/   USHORT  nIndex;
/*N*/   if (Search(nRow, nIndex))
/*N*/       return (pItems[nIndex].pCell)->HasValueData();
/*N*/   return FALSE;
/*N*/ }

//STRIP001 BOOL ScColumn::HasStringCells( USHORT nStartRow, USHORT nEndRow ) const
//STRIP001 {
//STRIP001  //  TRUE, wenn String- oder Editzellen im Bereich
//STRIP001
//STRIP001  if ( pItems )
//STRIP001  {
//STRIP001      USHORT nIndex;
//STRIP001      Search( nStartRow, nIndex );
//STRIP001      while ( nIndex < nCount && pItems[nIndex].nRow <= nEndRow )
//STRIP001      {
//STRIP001          CellType eType = pItems[nIndex].pCell->GetCellType();
//STRIP001          if ( eType == CELLTYPE_STRING || eType == CELLTYPE_EDIT )
//STRIP001              return TRUE;
//STRIP001          ++nIndex;
//STRIP001      }
//STRIP001  }
//STRIP001  return FALSE;
//STRIP001 }


//STRIP001 xub_StrLen ScColumn::GetMaxStringLen( USHORT nRowStart, USHORT nRowEnd ) const
//STRIP001 {
//STRIP001  xub_StrLen nStringLen = 0;
//STRIP001  if ( pItems )
//STRIP001  {
//STRIP001      String aString;
//STRIP001      SvNumberFormatter* pNumFmt = pDocument->GetFormatTable();
//STRIP001      USHORT nIndex, nRow;
//STRIP001      Search( nRowStart, nIndex );
//STRIP001      while ( nIndex < nCount && (nRow = pItems[nIndex].nRow) <= nRowEnd )
//STRIP001      {
//STRIP001          ScBaseCell* pCell = pItems[nIndex].pCell;
//STRIP001          if ( pCell->GetCellType() != CELLTYPE_NOTE )
//STRIP001          {
//STRIP001              Color* pColor;
//STRIP001              ULONG nFormat = (ULONG) ((SfxUInt32Item*) GetAttr(
//STRIP001                  nRow, ATTR_VALUE_FORMAT ))->GetValue();
//STRIP001              ScCellFormat::GetString( pCell, nFormat, aString, &pColor,
//STRIP001                  *pNumFmt );
//STRIP001              if ( nStringLen < aString.Len() )
//STRIP001                  nStringLen = aString.Len();
//STRIP001          }
//STRIP001          nIndex++;
//STRIP001      }
//STRIP001  }
//STRIP001  return nStringLen;
//STRIP001 }


//STRIP001 xub_StrLen ScColumn::GetMaxNumberStringLen( USHORT& nPrecision,
//STRIP001      USHORT nRowStart, USHORT nRowEnd ) const
//STRIP001 {
//STRIP001  xub_StrLen nStringLen = 0;
//STRIP001  nPrecision = pDocument->GetDocOptions().GetStdPrecision();
//STRIP001  if ( pItems )
//STRIP001  {
//STRIP001      String aString;
//STRIP001      SvNumberFormatter* pNumFmt = pDocument->GetFormatTable();
//STRIP001      USHORT nIndex, nRow;
//STRIP001      Search( nRowStart, nIndex );
//STRIP001      while ( nIndex < nCount && (nRow = pItems[nIndex].nRow) <= nRowEnd )
//STRIP001      {
//STRIP001          ScBaseCell* pCell = pItems[nIndex].pCell;
//STRIP001          CellType eType = pCell->GetCellType();
//STRIP001          if ( eType == CELLTYPE_VALUE || (eType == CELLTYPE_FORMULA
//STRIP001                  && ((ScFormulaCell*)pCell)->IsValue()) )
//STRIP001          {
//STRIP001              ULONG nFormat = (ULONG) ((SfxUInt32Item*) GetAttr(
//STRIP001                  nRow, ATTR_VALUE_FORMAT ))->GetValue();
//STRIP001              ScCellFormat::GetInputString( pCell, nFormat, aString, *pNumFmt );
//STRIP001              xub_StrLen nLen = aString.Len();
//STRIP001              if ( nLen )
//STRIP001              {
//STRIP001                  if ( nFormat )
//STRIP001                  {   // more decimals than standard?
//STRIP001                      USHORT nPrec = pNumFmt->GetFormatPrecision( nFormat );
//STRIP001                      if ( nPrec > nPrecision )
//STRIP001                          nPrecision = nPrec;
//STRIP001                  }
//STRIP001                  if ( nPrecision )
//STRIP001                  {   // less than nPrecision in string => widen it
//STRIP001                      // more => shorten it
//STRIP001                      String aSep = pNumFmt->GetFormatDecimalSep( nFormat );
//STRIP001                      xub_StrLen nTmp = aString.Search( aSep );
//STRIP001                      if ( nTmp == STRING_NOTFOUND )
//STRIP001                          nLen += nPrecision + aSep.Len();
//STRIP001                      else
//STRIP001                      {
//STRIP001                          nTmp = aString.Len() - (nTmp + aSep.Len());
//STRIP001                          if ( nTmp != nPrecision )
//STRIP001                              nLen += nPrecision - nTmp;
//STRIP001                              // nPrecision > nTmp : nLen + Diff
//STRIP001                              // nPrecision < nTmp : nLen - Diff
//STRIP001                      }
//STRIP001                  }
//STRIP001                  if ( nStringLen < nLen )
//STRIP001                      nStringLen = nLen;
//STRIP001              }
//STRIP001          }
//STRIP001          nIndex++;
//STRIP001      }
//STRIP001  }
//STRIP001  return nStringLen;
//STRIP001 }

}
