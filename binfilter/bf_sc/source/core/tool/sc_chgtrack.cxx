/*************************************************************************
 *
 *  $RCSfile: sc_chgtrack.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:26:26 $
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

#ifndef _TOOLS_DEBUG_HXX //autogen
#include <tools/debug.hxx>
#endif
#ifndef _SHL_HXX //autogen
#include <tools/shl.hxx>        // SHL_CALC
#endif
#ifndef _STACK_HXX //autogen
#include <tools/stack.hxx>
#endif
#ifndef _RTTI_HXX //autogen
#include <tools/rtti.hxx>
#endif
#ifndef _ZFORLIST_HXX //autogen
#include <svtools/zforlist.hxx>
#endif
#ifndef _SFXITEMSET_HXX //autogen
#include <svtools/itemset.hxx>
#endif
#ifndef _SFXISETHINT_HXX //autogen
#include <svtools/isethint.hxx>
#endif
#ifndef _SFXITEMPOOL_HXX //autogen
#include <svtools/itempool.hxx>
#endif
#ifndef _SFXAPP_HXX //autogen
#include <bf_sfx2/app.hxx>
#endif
#ifndef INCLUDED_SVTOOLS_USEROPTIONS_HXX
#include <svtools/useroptions.hxx>
#endif
#ifndef _SFXSIDS_HRC //autogen
#include <bf_sfx2/sfxsids.hrc>
#endif
#ifndef _SVX_ADRITEM_HXX //autogen
#include <bf_svx/adritem.hxx>
#endif

#include "cell.hxx"
#include "document.hxx"
#include "dociter.hxx"
#include "global.hxx"
#include "rechead.hxx"
#include "scerrors.hxx"
#include "scmod.hxx"        // SC_MOD
#include "inputopt.hxx"     // GetExpandRefs
#include "patattr.hxx"
#include "hints.hxx"

#include "globstr.hrc"

#define SC_CHGTRACK_CXX
#include "chgtrack.hxx"
namespace binfilter {

//STRIP001 DECLARE_STACK( ScChangeActionStack, ScChangeAction* );

const USHORT nMemPoolChangeActionCellListEntry = (0x2000 - 64) / sizeof(ScChangeActionCellListEntry);
/*N*/ IMPL_FIXEDMEMPOOL_NEWDEL( ScChangeActionCellListEntry, nMemPoolChangeActionCellListEntry, nMemPoolChangeActionCellListEntry )//STRIP008 ;

const USHORT nMemPoolChangeActionLinkEntry = (0x8000 - 64) / sizeof(ScChangeActionLinkEntry);
/*N*/ IMPL_FIXEDMEMPOOL_NEWDEL( ScChangeActionLinkEntry, nMemPoolChangeActionLinkEntry, nMemPoolChangeActionLinkEntry )//STRIP008 ;

// loaded MSB > eigenes => inkompatibel
#define SC_CHGTRACK_FILEFORMAT_FIRST    0x0001
#define SC_CHGTRACK_FILEFORMAT  0x0001

// --- ScChangeAction ------------------------------------------------------

/*N*/  ScChangeAction::ScChangeAction( ScChangeActionType eTypeP, const ScRange& rRange )
/*N*/       :
/*N*/       aBigRange( rRange ),
/*N*/       pNext( NULL ),
/*N*/       pPrev( NULL ),
/*N*/       pLinkAny( NULL ),
/*N*/       pLinkDeletedIn( NULL ),
/*N*/       pLinkDeleted( NULL ),
/*N*/       pLinkDependent( NULL ),
/*N*/       nAction( 0 ),
/*N*/       nRejectAction( 0 ),
/*N*/       eType( eTypeP ),
/*N*/       eState( SC_CAS_VIRGIN )
/*N*/  {
/*N*/   aDateTime.ConvertToUTC();
/*N*/  }

/*N*/  ScChangeAction::ScChangeAction( ScChangeActionType eTypeP, const ScBigRange& rRange,
/*N*/                       const ULONG nTempAction, const ULONG nTempRejectAction,
/*N*/                       const ScChangeActionState eTempState, const DateTime& aTempDateTime,
/*N*/                       const String& aTempUser,  const String& aTempComment)
/*N*/       :
/*N*/       aBigRange( rRange ),
/*N*/       pNext( NULL ),
/*N*/       pPrev( NULL ),
/*N*/       pLinkAny( NULL ),
/*N*/       pLinkDeletedIn( NULL ),
/*N*/       pLinkDeleted( NULL ),
/*N*/       pLinkDependent( NULL ),
/*N*/       nAction( nTempAction ),
/*N*/       nRejectAction( nTempRejectAction ),
/*N*/       eType( eTypeP ),
/*N*/       eState( eTempState ),
/*N*/       aDateTime( aTempDateTime ),
/*N*/       aUser( aTempUser ),
/*N*/       aComment( aTempComment )
/*N*/  {
/*N*/  }

/*N*/  ScChangeAction::ScChangeAction( ScChangeActionType eTypeP, const ScBigRange& rRange,
/*N*/                       const ULONG nTempAction)
/*N*/       :
/*N*/       aBigRange( rRange ),
/*N*/       pNext( NULL ),
/*N*/       pPrev( NULL ),
/*N*/       pLinkAny( NULL ),
/*N*/       pLinkDeletedIn( NULL ),
/*N*/       pLinkDeleted( NULL ),
/*N*/       pLinkDependent( NULL ),
/*N*/       nAction( nTempAction ),
/*N*/       nRejectAction( 0 ),
/*N*/       eType( eTypeP ),
/*N*/       eState( SC_CAS_VIRGIN )
/*N*/  {
/*N*/   aDateTime.ConvertToUTC();
/*N*/  }

/*N*/  ScChangeAction::ScChangeAction( SvStream& rStrm, ScMultipleReadHeader& rHdr,
/*N*/           ScChangeTrack* pTrack )
/*N*/       :
/*N*/       pNext( NULL ),
/*N*/       pPrev( NULL ),
/*N*/       pLinkAny( NULL ),
/*N*/       pLinkDeletedIn( NULL ),
/*N*/       pLinkDeleted( NULL ),
/*N*/       pLinkDependent( NULL )
/*N*/  {
/*N*/   // ScChangeTrack speichert aUser als Index auf Collection und eType selber
/*N*/   UINT32 n32;
/*N*/   UINT16 n16;
/*N*/   rStrm >> aBigRange;
/*N*/   rStrm >> n32; aDateTime.SetDate( n32 );
/*N*/   rStrm >> n32; aDateTime.SetTime( n32 );
/*N*/   rStrm >> n32; nAction = n32;
/*N*/   rStrm >> n32; nRejectAction = n32;
/*N*/   rStrm >> n16; eState = (ScChangeActionState) n16;
/*N*/   rStrm.ReadByteString( aComment, rStrm.GetStreamCharSet() );
/*N*/   // LinkEntries in zweiter Runde
/*N*/  }


/*N*/  ScChangeAction::~ScChangeAction()
/*N*/  {
/*N*/   RemoveAllLinks();
/*N*/  }


//STRIP001 BOOL ScChangeAction::Store( SvStream& rStrm, ScMultipleWriteHeader& rHdr ) const
//STRIP001 {
//STRIP001  // ScChangeTrack speichert aUser als Index auf Collection und eType selber
//STRIP001  rStrm << aBigRange;
//STRIP001  rStrm << (UINT32) aDateTime.GetDate();
//STRIP001  rStrm << (UINT32) aDateTime.GetTime();
//STRIP001  rStrm << (UINT32) nAction;
//STRIP001  rStrm << (UINT32) nRejectAction;
//STRIP001  rStrm << (UINT16) eState;
//STRIP001  rStrm.WriteByteString( aComment, rStrm.GetStreamCharSet() );
//STRIP001  // LinkEntries in zweiter Runde
//STRIP001
//STRIP001  return TRUE;
//STRIP001 }


//STRIP001 BOOL ScChangeAction::StoreLinks( SvStream& rStrm ) const
//STRIP001 {
//STRIP001  BOOL bOk = ScChangeAction::StoreLinkChain( pLinkDeleted, rStrm );
//STRIP001  bOk &= ScChangeAction::StoreLinkChain( pLinkDependent, rStrm );
//STRIP001  return bOk;
//STRIP001 }


//STRIP001 BOOL ScChangeAction::LoadLinks( SvStream& rStrm, ScChangeTrack* pTrack )
//STRIP001 {
//STRIP001  BOOL bOk = ScChangeAction::LoadLinkChain( this, &pLinkDeleted, rStrm,
//STRIP001      pTrack, TRUE );
//STRIP001  bOk &= ScChangeAction::LoadLinkChain( this, &pLinkDependent, rStrm,
//STRIP001      pTrack, FALSE );
//STRIP001  return bOk;
//STRIP001 }


//STRIP001 BOOL ScChangeAction::IsVisible() const
//STRIP001 {
//STRIP001  //! sequence order of execution is significant
//STRIP001  if ( IsRejected() || GetType() == SC_CAT_DELETE_TABS || IsDeletedIn() )
//STRIP001      return FALSE;
//STRIP001  if ( GetType() == SC_CAT_CONTENT )
//STRIP001      return ((ScChangeActionContent*)this)->IsTopContent();
//STRIP001  return TRUE;
//STRIP001 }


//STRIP001 BOOL ScChangeAction::IsTouchable() const
//STRIP001 {
//STRIP001  //! sequence order of execution is significant
//STRIP001  if ( IsRejected() || GetType() == SC_CAT_REJECT || IsDeletedIn() )
//STRIP001      return FALSE;
//STRIP001  // content may reject and be touchable if on top
//STRIP001  if ( GetType() == SC_CAT_CONTENT )
//STRIP001      return ((ScChangeActionContent*)this)->IsTopContent();
//STRIP001  if ( IsRejecting() )
//STRIP001      return FALSE;
//STRIP001  return TRUE;
//STRIP001 }


//STRIP001 BOOL ScChangeAction::IsClickable() const
//STRIP001 {
//STRIP001  //! sequence order of execution is significant
//STRIP001  if ( !IsVirgin() )
//STRIP001      return FALSE;
//STRIP001  if ( IsDeletedIn() )
//STRIP001      return FALSE;
//STRIP001  if ( GetType() == SC_CAT_CONTENT )
//STRIP001  {
//STRIP001      ScChangeActionContentCellType eCCT =
//STRIP001          ScChangeActionContent::GetContentCellType(
//STRIP001          ((ScChangeActionContent*)this)->GetNewCell() );
//STRIP001      if ( eCCT == SC_CACCT_MATREF )
//STRIP001          return FALSE;
//STRIP001      if ( eCCT == SC_CACCT_MATORG )
//STRIP001      {   // no Accept-Select if one of the references is in a deleted col/row
//STRIP001          const ScChangeActionLinkEntry* pL =
//STRIP001              ((ScChangeActionContent*)this)->GetFirstDependentEntry();
//STRIP001          while ( pL )
//STRIP001          {
//STRIP001              ScChangeAction* p = (ScChangeAction*) pL->GetAction();
//STRIP001              if ( p && p->IsDeletedIn() )
//STRIP001                  return FALSE;
//STRIP001              pL = pL->GetNext();
//STRIP001          }
//STRIP001      }
//STRIP001      return TRUE;    // for Select() a content doesn't have to be touchable
//STRIP001  }
//STRIP001  return IsTouchable();   // Accept()/Reject() only on touchables
//STRIP001 }


//STRIP001 BOOL ScChangeAction::IsRejectable() const
//STRIP001 {
//STRIP001  //! sequence order of execution is significant
//STRIP001  if ( !IsClickable() )
//STRIP001      return FALSE;
//STRIP001  if ( GetType() == SC_CAT_CONTENT )
//STRIP001  {
//STRIP001      if ( ((ScChangeActionContent*)this)->IsOldMatrixReference() )
//STRIP001          return FALSE;
//STRIP001      ScChangeActionContent* pNextContent =
//STRIP001          ((ScChangeActionContent*)this)->GetNextContent();
//STRIP001      if ( pNextContent == NULL )
//STRIP001          return TRUE;        // *this is TopContent
//STRIP001      return pNextContent->IsRejected();      // *this is next rejectable
//STRIP001  }
//STRIP001  return IsTouchable();
//STRIP001 }


//STRIP001 BOOL ScChangeAction::IsInternalRejectable() const
//STRIP001 {
//STRIP001  //! sequence order of execution is significant
//STRIP001  if ( !IsVirgin() )
//STRIP001      return FALSE;
//STRIP001  if ( IsDeletedIn() )
//STRIP001      return FALSE;
//STRIP001  if ( GetType() == SC_CAT_CONTENT )
//STRIP001  {
//STRIP001      ScChangeActionContent* pNextContent =
//STRIP001          ((ScChangeActionContent*)this)->GetNextContent();
//STRIP001      if ( pNextContent == NULL )
//STRIP001          return TRUE;        // *this is TopContent
//STRIP001      return pNextContent->IsRejected();      // *this is next rejectable
//STRIP001  }
//STRIP001  return IsTouchable();
//STRIP001 }


//STRIP001 BOOL ScChangeAction::IsDialogRoot() const
//STRIP001 {
//STRIP001  return IsInternalRejectable();      // only rejectables in root
//STRIP001 }


//STRIP001 BOOL ScChangeAction::IsDialogParent() const
//STRIP001 {
//STRIP001  //! sequence order of execution is significant
//STRIP001  if ( GetType() == SC_CAT_CONTENT )
//STRIP001  {
//STRIP001      if ( !IsDialogRoot() )
//STRIP001          return FALSE;
//STRIP001      if ( ((ScChangeActionContent*)this)->IsMatrixOrigin() && HasDependent() )
//STRIP001          return TRUE;
//STRIP001      ScChangeActionContent* pPrevContent =
//STRIP001          ((ScChangeActionContent*)this)->GetPrevContent();
//STRIP001      return pPrevContent && pPrevContent->IsVirgin();
//STRIP001  }
//STRIP001  if ( HasDependent() )
//STRIP001      return IsDeleteType() ? TRUE : !IsDeletedIn();
//STRIP001  if ( HasDeleted() )
//STRIP001  {
//STRIP001      if ( IsDeleteType() )
//STRIP001      {
//STRIP001          if ( IsDialogRoot() )
//STRIP001              return TRUE;
//STRIP001          ScChangeActionLinkEntry* pL = pLinkDeleted;
//STRIP001          while ( pL )
//STRIP001          {
//STRIP001              ScChangeAction* p = pL->GetAction();
//STRIP001              if ( p && p->GetType() != eType )
//STRIP001                  return TRUE;
//STRIP001              pL = pL->GetNext();
//STRIP001          }
//STRIP001      }
//STRIP001      else
//STRIP001          return TRUE;
//STRIP001  }
//STRIP001  return FALSE;
//STRIP001 }


//STRIP001 BOOL ScChangeAction::IsMasterDelete() const
//STRIP001 {
//STRIP001  if ( !IsDeleteType() )
//STRIP001      return FALSE;
//STRIP001  ScChangeActionDel* pDel = (ScChangeActionDel*) this;
//STRIP001  return pDel->IsMultiDelete() && (pDel->IsTopDelete() || pDel->IsRejectable());
//STRIP001 }


/*N*/ void ScChangeAction::RemoveAllLinks()
/*N*/ {
DBG_ASSERT(0, "STRIP"); //STRIP001  RemoveAllAnyLinks();
//STRIP001  RemoveAllDeletedIn();
//STRIP001  RemoveAllDeleted();
//STRIP001  RemoveAllDependent();
/*N*/ }


//STRIP001 void ScChangeAction::RemoveLink( ScChangeAction* p )
//STRIP001 {
//STRIP001  ScChangeActionLinkEntry* pL = pLinkAny;
//STRIP001  while ( pL )
//STRIP001  {
//STRIP001      ScChangeActionLinkEntry* pNextLink = pL->GetNext();
//STRIP001      if ( pL->GetAction() == p )
//STRIP001          delete pL;
//STRIP001      pL = pNextLink;
//STRIP001  }
//STRIP001 }


//STRIP001 void ScChangeAction::RemoveAllAnyLinks()
//STRIP001 {
//STRIP001  while ( pLinkAny )
//STRIP001      delete pLinkAny;        // rueckt sich selbst hoch
//STRIP001 }


//STRIP001 BOOL ScChangeAction::DependsOn( ScChangeAction* p ) const
//STRIP001 {
//STRIP001  ScChangeActionLinkEntry* pL = pLinkAny;
//STRIP001  while ( pL )
//STRIP001  {
//STRIP001      if ( pL->GetAction() == p )
//STRIP001          return TRUE;
//STRIP001      pL = pL->GetNext();
//STRIP001  }
//STRIP001  return FALSE;
//STRIP001 }


//STRIP001 BOOL ScChangeAction::RemoveDeletedIn( const ScChangeAction* p )
//STRIP001 {
//STRIP001  BOOL bRemoved = FALSE;
//STRIP001  ScChangeActionLinkEntry* pL = GetDeletedIn();
//STRIP001  while ( pL )
//STRIP001  {
//STRIP001      ScChangeActionLinkEntry* pNextLink = pL->GetNext();
//STRIP001      if ( pL->GetAction() == p )
//STRIP001      {
//STRIP001          delete pL;
//STRIP001          bRemoved = TRUE;
//STRIP001      }
//STRIP001      pL = pNextLink;
//STRIP001  }
//STRIP001  return bRemoved;
//STRIP001 }


//STRIP001 BOOL ScChangeAction::IsDeletedIn( const ScChangeAction* p ) const
//STRIP001 {
//STRIP001  ScChangeActionLinkEntry* pL = GetDeletedIn();
//STRIP001  while ( pL )
//STRIP001  {
//STRIP001      if ( pL->GetAction() == p )
//STRIP001          return TRUE;
//STRIP001      pL = pL->GetNext();
//STRIP001  }
//STRIP001  return FALSE;
//STRIP001 }


//STRIP001 void ScChangeAction::RemoveAllDeletedIn()
//STRIP001 {
//STRIP001  //! nicht vom evtl. TopContent sondern wirklich dieser
//STRIP001  while ( pLinkDeletedIn )
//STRIP001      delete pLinkDeletedIn;      // rueckt sich selbst hoch
//STRIP001 }


//STRIP001 BOOL ScChangeAction::IsDeletedInDelType( ScChangeActionType eDelType ) const
//STRIP001 {
//STRIP001  ScChangeAction* p;
//STRIP001  ScChangeActionLinkEntry* pL = GetDeletedIn();
//STRIP001  if ( pL )
//STRIP001  {
//STRIP001      // InsertType fuer MergePrepare/MergeOwn
//STRIP001      ScChangeActionType eInsType;
//STRIP001      switch ( eDelType )
//STRIP001      {
//STRIP001          case SC_CAT_DELETE_COLS :
//STRIP001              eInsType = SC_CAT_INSERT_COLS;
//STRIP001          break;
//STRIP001          case SC_CAT_DELETE_ROWS :
//STRIP001              eInsType = SC_CAT_INSERT_ROWS;
//STRIP001          break;
//STRIP001          case SC_CAT_DELETE_TABS :
//STRIP001              eInsType = SC_CAT_INSERT_TABS;
//STRIP001          break;
//STRIP001          default:
//STRIP001              eInsType = SC_CAT_NONE;
//STRIP001      }
//STRIP001      while ( pL )
//STRIP001      {
//STRIP001          if ( (p = pL->GetAction()) &&
//STRIP001                  (p->GetType() == eDelType || p->GetType() == eInsType) )
//STRIP001              return TRUE;
//STRIP001          pL = pL->GetNext();
//STRIP001      }
//STRIP001  }
//STRIP001  return FALSE;
//STRIP001 }


//STRIP001 void ScChangeAction::SetDeletedIn( ScChangeAction* p )
//STRIP001 {
//STRIP001  ScChangeActionLinkEntry* pLink1 = AddDeletedIn( p );
//STRIP001  ScChangeActionLinkEntry* pLink2;
//STRIP001  if ( GetType() == SC_CAT_CONTENT )
//STRIP001      pLink2 = p->AddDeleted( ((ScChangeActionContent*)this)->GetTopContent() );
//STRIP001  else
//STRIP001      pLink2 = p->AddDeleted( this );
//STRIP001  pLink1->SetLink( pLink2 );
//STRIP001 }


//STRIP001 BOOL ScChangeAction::RemoveDeleted( const ScChangeAction* p )
//STRIP001 {
//STRIP001  BOOL bRemoved = FALSE;
//STRIP001  ScChangeActionLinkEntry* pL = pLinkDeleted;
//STRIP001  while ( pL )
//STRIP001  {
//STRIP001      ScChangeActionLinkEntry* pNextLink = pL->GetNext();
//STRIP001      if ( pL->GetAction() == p )
//STRIP001      {
//STRIP001          delete pL;
//STRIP001          bRemoved = TRUE;
//STRIP001      }
//STRIP001      pL = pNextLink;
//STRIP001  }
//STRIP001  return bRemoved;
//STRIP001 }


//STRIP001 void ScChangeAction::RemoveAllDeleted()
//STRIP001 {
//STRIP001  while ( pLinkDeleted )
//STRIP001      delete pLinkDeleted;        // rueckt sich selbst hoch
//STRIP001 }


//STRIP001 void ScChangeAction::RemoveDependent( ScChangeAction* p )
//STRIP001 {
//STRIP001  ScChangeActionLinkEntry* pL = pLinkDependent;
//STRIP001  while ( pL )
//STRIP001  {
//STRIP001      ScChangeActionLinkEntry* pNextLink = pL->GetNext();
//STRIP001      if ( pL->GetAction() == p )
//STRIP001          delete pL;
//STRIP001      pL = pNextLink;
//STRIP001  }
//STRIP001 }


//STRIP001 void ScChangeAction::RemoveAllDependent()
//STRIP001 {
//STRIP001  while ( pLinkDependent )
//STRIP001      delete pLinkDependent;      // rueckt sich selbst hoch
//STRIP001 }


//STRIP001 DateTime ScChangeAction::GetDateTime() const
//STRIP001 {
//STRIP001  DateTime aDT( aDateTime );
//STRIP001  aDT.ConvertToLocalTime();
//STRIP001  return aDT;
//STRIP001 }


//STRIP001 void ScChangeAction::UpdateReference( const ScChangeTrack* pTrack,
//STRIP001      UpdateRefMode eMode, const ScBigRange& rRange,
//STRIP001      INT32 nDx, INT32 nDy, INT32 nDz )
//STRIP001 {
//STRIP001  ScRefUpdate::Update( eMode, rRange, nDx, nDy, nDz, GetBigRange() );
//STRIP001 }


//STRIP001 String ScChangeAction::GetRefString( const ScBigRange& rRange,
//STRIP001      ScDocument* pDoc, BOOL bFlag3D ) const
//STRIP001 {
//STRIP001  String aStr;
//STRIP001  USHORT nFlags = ( rRange.IsValid( pDoc ) ? SCA_VALID : 0 );
//STRIP001  if ( !nFlags )
//STRIP001      aStr = ScGlobal::GetRscString( STR_NOREF_STR );
//STRIP001  else
//STRIP001  {
//STRIP001      ScRange aTmpRange( rRange.MakeRange() );
//STRIP001      switch ( GetType() )
//STRIP001      {
//STRIP001          case SC_CAT_INSERT_COLS :
//STRIP001          case SC_CAT_DELETE_COLS :
//STRIP001              if ( bFlag3D )
//STRIP001              {
//STRIP001                  pDoc->GetName( aTmpRange.aStart.Tab(), aStr );
//STRIP001                  aStr += '.';
//STRIP001              }
//STRIP001              aStr += ::ColToAlpha( aTmpRange.aStart.Col() );
//STRIP001              aStr += ':';
//STRIP001              aStr += ::ColToAlpha( aTmpRange.aEnd.Col() );
//STRIP001          break;
//STRIP001          case SC_CAT_INSERT_ROWS :
//STRIP001          case SC_CAT_DELETE_ROWS :
//STRIP001              if ( bFlag3D )
//STRIP001              {
//STRIP001                  pDoc->GetName( aTmpRange.aStart.Tab(), aStr );
//STRIP001                  aStr += '.';
//STRIP001              }
//STRIP001              aStr += String::CreateFromInt32( aTmpRange.aStart.Row() + 1 );
//STRIP001              aStr += ':';
//STRIP001              aStr += String::CreateFromInt32( aTmpRange.aEnd.Row() + 1 );
//STRIP001          break;
//STRIP001          default:
//STRIP001              if ( bFlag3D || GetType() == SC_CAT_INSERT_TABS )
//STRIP001                  nFlags |= SCA_TAB_3D;
//STRIP001              aTmpRange.Format( aStr, nFlags, pDoc );
//STRIP001      }
//STRIP001      if ( (bFlag3D && IsDeleteType()) || IsDeletedIn() )
//STRIP001      {
//STRIP001          aStr.Insert( '(', 0 );
//STRIP001          aStr += ')';
//STRIP001      }
//STRIP001  }
//STRIP001  return aStr;
//STRIP001 }


//STRIP001 void ScChangeAction::GetRefString( String& rStr, ScDocument* pDoc,
//STRIP001      BOOL bFlag3D ) const
//STRIP001 {
//STRIP001  rStr = GetRefString( GetBigRange(), pDoc, bFlag3D );
//STRIP001 }


//STRIP001 void ScChangeAction::Accept()
//STRIP001 {
//STRIP001  if ( IsVirgin() )
//STRIP001  {
//STRIP001      SetState( SC_CAS_ACCEPTED );
//STRIP001      DeleteCellEntries();
//STRIP001  }
//STRIP001 }


//STRIP001 void ScChangeAction::SetRejected()
//STRIP001 {
//STRIP001  if ( IsVirgin() )
//STRIP001  {
//STRIP001      SetState( SC_CAS_REJECTED );
//STRIP001      RemoveAllLinks();
//STRIP001      DeleteCellEntries();
//STRIP001  }
//STRIP001 }


//STRIP001 void ScChangeAction::RejectRestoreContents( ScChangeTrack* pTrack,
//STRIP001      short nDx, short nDy )
//STRIP001 {
//STRIP001  // Liste der Contents aufbauen
//STRIP001  ScChangeActionCellListEntry* pListContents = NULL;
//STRIP001  for ( ScChangeActionLinkEntry* pL = pLinkDeleted; pL; pL = pL->GetNext() )
//STRIP001  {
//STRIP001      ScChangeAction* p = pL->GetAction();
//STRIP001      if ( p && p->GetType() == SC_CAT_CONTENT )
//STRIP001      {
//STRIP001          ScChangeActionCellListEntry* pE = new ScChangeActionCellListEntry(
//STRIP001              (ScChangeActionContent*) p, pListContents );
//STRIP001          pListContents = pE;
//STRIP001      }
//STRIP001  }
//STRIP001  SetState( SC_CAS_REJECTED );        // vor UpdateReference fuer Move
//STRIP001  pTrack->UpdateReference( this, TRUE );      // LinkDeleted freigeben
//STRIP001  DBG_ASSERT( !pLinkDeleted, "ScChangeAction::RejectRestoreContents: pLinkDeleted != NULL" );
//STRIP001  // Liste der Contents abarbeiten und loeschen
//STRIP001  ScDocument* pDoc = pTrack->GetDocument();
//STRIP001  ScChangeActionCellListEntry* pE = pListContents;
//STRIP001  while ( pE )
//STRIP001  {
//STRIP001      if ( !pE->pContent->IsDeletedIn() &&
//STRIP001              pE->pContent->GetBigRange().aStart.IsValid( pDoc ) )
//STRIP001          pE->pContent->PutNewValueToDoc( pDoc, nDx, nDy );
//STRIP001      ScChangeActionCellListEntry* pNext;
//STRIP001      pNext = pE->pNext;
//STRIP001      delete pE;
//STRIP001      pE = pNext;
//STRIP001  }
//STRIP001  DeleteCellEntries();        // weg mit den generierten
//STRIP001 }


// static
//STRIP001 void ScChangeAction::StoreCell( ScBaseCell* pCell, SvStream& rStrm,
//STRIP001      ScMultipleWriteHeader& rHdr )
//STRIP001 {
//STRIP001  if ( pCell )
//STRIP001  {
//STRIP001      CellType eCellType = pCell->GetCellType();
//STRIP001      switch( eCellType )
//STRIP001      {
//STRIP001          case CELLTYPE_VALUE:
//STRIP001              rStrm << (BYTE) eCellType;
//STRIP001              ((ScValueCell*)pCell)->Save( rStrm );
//STRIP001          break;
//STRIP001          case CELLTYPE_STRING:
//STRIP001              rStrm << (BYTE) eCellType;
//STRIP001              ((ScStringCell*)pCell)->Save( rStrm );
//STRIP001          break;
//STRIP001          case CELLTYPE_EDIT:
//STRIP001              rStrm << (BYTE) eCellType;
//STRIP001              ((ScEditCell*)pCell)->Save( rStrm );
//STRIP001          break;
//STRIP001          case CELLTYPE_FORMULA:
//STRIP001              rStrm << (BYTE) eCellType;
//STRIP001              rStrm << ((ScFormulaCell*)pCell)->aPos;
//STRIP001              ((ScFormulaCell*)pCell)->Save( rStrm, rHdr );
//STRIP001          break;
//STRIP001          default:
//STRIP001              DBG_ERROR( "ScChangeAction::StoreCell: unknown CellType" );
//STRIP001              rStrm << (BYTE) CELLTYPE_NONE;
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001      rStrm << (BYTE) CELLTYPE_NONE;
//STRIP001 }


// static
//STRIP001 ScBaseCell* ScChangeAction::LoadCell( SvStream& rStrm,
//STRIP001      ScMultipleReadHeader& rHdr, ScDocument* pDoc, USHORT nVer )
//STRIP001 {
//STRIP001  ScBaseCell* pCell;
//STRIP001  BYTE nByte;
//STRIP001  rStrm >> nByte;
//STRIP001  switch ( (CellType) nByte )
//STRIP001  {
//STRIP001      case CELLTYPE_VALUE:
//STRIP001      {
//STRIP001          pCell = new ScValueCell( rStrm, nVer );
//STRIP001      }
//STRIP001      break;
//STRIP001      case CELLTYPE_STRING:
//STRIP001      {
//STRIP001          pCell = new ScStringCell( rStrm, nVer );
//STRIP001      }
//STRIP001      break;
//STRIP001      case CELLTYPE_EDIT:
//STRIP001      {
//STRIP001          pCell = new ScEditCell( rStrm, nVer, pDoc );
//STRIP001      }
//STRIP001      break;
//STRIP001      case CELLTYPE_FORMULA:
//STRIP001      {
//STRIP001          ScAddress aPos;
//STRIP001          rStrm >> aPos;
//STRIP001          pCell = new ScFormulaCell( pDoc, aPos, rStrm, rHdr );
//STRIP001          ((ScFormulaCell*)pCell)->SetInChangeTrack( TRUE );
//STRIP001      }
//STRIP001      break;
//STRIP001      case CELLTYPE_NONE :
//STRIP001          pCell = NULL;
//STRIP001      break;
//STRIP001      default:
//STRIP001          DBG_ERROR( "ScChangeAction::LoadCell: unknown CellType" );
//STRIP001          rStrm.SetError( SVSTREAM_FILEFORMAT_ERROR );
//STRIP001          pCell = NULL;
//STRIP001  }
//STRIP001  return pCell;
//STRIP001 }


// static
//STRIP001 BOOL ScChangeAction::StoreLinkChain( ScChangeActionLinkEntry* pLinkFirst,
//STRIP001      SvStream& rStrm )
//STRIP001 {
//STRIP001  BOOL bOk = TRUE;
//STRIP001  UINT32 nCount = 0;
//STRIP001  if ( pLinkFirst )
//STRIP001  {
//STRIP001      // rueckwaerts speichern, damit onLoad mit Insert die Reihenfolge wieder stimmt
//STRIP001      Stack* pStack = new Stack;
//STRIP001      for ( ScChangeActionLinkEntry* pL = pLinkFirst; pL; pL = pL->GetNext() )
//STRIP001      {
//STRIP001          ++nCount;
//STRIP001          pStack->Push( pL );
//STRIP001      }
//STRIP001      rStrm << nCount;
//STRIP001      ScChangeActionLinkEntry* pHere;
//STRIP001      while ( pHere = (ScChangeActionLinkEntry*) pStack->Pop() )
//STRIP001      {
//STRIP001          ScChangeAction* p = pHere->GetAction();
//STRIP001          rStrm << (UINT32) ( p ? p->GetActionNumber() : 0 );
//STRIP001      }
//STRIP001      delete pStack;
//STRIP001  }
//STRIP001  else
//STRIP001      rStrm << nCount;
//STRIP001  return bOk;
//STRIP001 }


// static
//STRIP001 BOOL ScChangeAction::LoadLinkChain( ScChangeAction* pOfAction,
//STRIP001      ScChangeActionLinkEntry** ppLinkFirst, SvStream& rStrm,
//STRIP001      ScChangeTrack* pTrack, BOOL bLinkDeleted )
//STRIP001 {
//STRIP001  BOOL bOk = TRUE;
//STRIP001  UINT32 nCount;
//STRIP001  rStrm >> nCount;
//STRIP001  for ( UINT32 j = 0; j < nCount; j++ )
//STRIP001  {
//STRIP001      ScChangeAction* pAct = NULL;
//STRIP001      UINT32 nAct;
//STRIP001      rStrm >> nAct;
//STRIP001      if ( nAct )
//STRIP001      {
//STRIP001          pAct = pTrack->GetActionOrGenerated( nAct );
//STRIP001          DBG_ASSERT( pAct, "ScChangeAction::LoadLinkChain: missing Action" );
//STRIP001      }
//STRIP001      if ( bLinkDeleted )
//STRIP001      {
//STRIP001          if ( pAct )
//STRIP001              pAct->SetDeletedIn( pOfAction );
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          ScChangeActionLinkEntry* pLink = new ScChangeActionLinkEntry(
//STRIP001              ppLinkFirst, pAct );
//STRIP001          if ( pAct )
//STRIP001              pAct->AddLink( pOfAction, pLink );
//STRIP001      }
//STRIP001  }
//STRIP001  return bOk;
//STRIP001 }


/*N*/  void ScChangeAction::SetDeletedInThis( ULONG nActionNumber,
/*N*/       const ScChangeTrack* pTrack )
/*N*/  {
DBG_ASSERT(0, "STRIP"); //STRIP001  if ( nActionNumber )
//STRIP001  {
//STRIP001      ScChangeAction* pAct = pTrack->GetActionOrGenerated( nActionNumber );
//STRIP001      DBG_ASSERT( pAct, "ScChangeAction::SetDeletedInThis: missing Action" );
//STRIP001      if ( pAct )
//STRIP001          pAct->SetDeletedIn( this );
//STRIP001  }
/*N*/ }


/*N*/ void ScChangeAction::AddDependent( ULONG nActionNumber,
/*N*/       const ScChangeTrack* pTrack )
/*N*/ {
DBG_ASSERT(0, "STRIP"); //STRIP001      if ( nActionNumber )
//STRIP001  {
//STRIP001      ScChangeAction* pAct = pTrack->GetActionOrGenerated( nActionNumber );
//STRIP001      DBG_ASSERT( pAct, "ScChangeAction::AddDependent: missing Action" );
//STRIP001      if ( pAct )
//STRIP001      {
//STRIP001          ScChangeActionLinkEntry* pLink = AddDependent( pAct );
//STRIP001          pAct->AddLink( this, pLink );
//STRIP001      }
//STRIP001  }
/*N*/ }

// static
//STRIP001 BOOL ScChangeAction::StoreCellList( ScChangeActionCellListEntry* pFirstCell,
//STRIP001      SvStream& rStrm )
//STRIP001 {
//STRIP001  UINT32 nCount = 0;
//STRIP001  for ( const ScChangeActionCellListEntry* pE = pFirstCell; pE;
//STRIP001          pE = pE->pNext )
//STRIP001      ++nCount;
//STRIP001  rStrm << nCount;
//STRIP001
//STRIP001  if ( nCount )
//STRIP001  {
//STRIP001      for ( const ScChangeActionCellListEntry* pE = pFirstCell; pE;
//STRIP001              pE = pE->pNext )
//STRIP001      {   // Store/Load vertauscht die Reihenfolge, aber das ist hierbei egal
//STRIP001          rStrm << (UINT32) pE->pContent->GetActionNumber();
//STRIP001      }
//STRIP001  }
//STRIP001  return TRUE;
//STRIP001 }


//STRIP001 BOOL ScChangeAction::LoadCellList( ScChangeAction* pOfAction,
//STRIP001      ScChangeActionCellListEntry*& pFirstCell, SvStream& rStrm,
//STRIP001      ScChangeTrack* pTrack )
//STRIP001 {
//STRIP001  UINT32 nCount;
//STRIP001  rStrm >> nCount;
//STRIP001  if ( nCount )
//STRIP001  {
//STRIP001      for ( UINT32 j = 0; j < nCount; j++ )
//STRIP001      {
//STRIP001          ScChangeActionContent* pContent;
//STRIP001          UINT32 nContent;
//STRIP001          rStrm >> nContent;
//STRIP001          pContent = (ScChangeActionContent*) pTrack->GetActionOrGenerated( nContent );
//STRIP001          if ( pContent )
//STRIP001              pOfAction->AddContent( pContent );
//STRIP001          else
//STRIP001              DBG_ERROR( "ScChangeActionDel::LoadLinks: missing Content" );
//STRIP001      }
//STRIP001  }
//STRIP001  return TRUE;
//STRIP001 }


// --- ScChangeActionIns ---------------------------------------------------

/*N*/ ScChangeActionIns::ScChangeActionIns( const ScRange& rRange )
/*N*/       : ScChangeAction( SC_CAT_NONE, rRange )
/*N*/ {
        DBG_ASSERT(0, "STRIP"); //STRIP001 if ( rRange.aStart.Col() == 0 && rRange.aEnd.Col() == MAXCOL )
//STRIP001  {
//STRIP001      aBigRange.aStart.SetCol( nInt32Min );
//STRIP001      aBigRange.aEnd.SetCol( nInt32Max );
//STRIP001      if ( rRange.aStart.Row() == 0 && rRange.aEnd.Row() == MAXROW )
//STRIP001      {
//STRIP001          SetType( SC_CAT_INSERT_TABS );
//STRIP001          aBigRange.aStart.SetRow( nInt32Min );
//STRIP001          aBigRange.aEnd.SetRow( nInt32Max );
//STRIP001      }
//STRIP001      else
//STRIP001          SetType( SC_CAT_INSERT_ROWS );
//STRIP001  }
//STRIP001  else if ( rRange.aStart.Row() == 0 && rRange.aEnd.Row() == MAXROW )
//STRIP001  {
//STRIP001      SetType( SC_CAT_INSERT_COLS );
//STRIP001      aBigRange.aStart.SetRow( nInt32Min );
//STRIP001      aBigRange.aEnd.SetRow( nInt32Max );
//STRIP001  }
//STRIP001  else
//STRIP001      DBG_ERROR( "ScChangeActionIns: Block not supported!" );
/*N*/ }


/*N*/ ScChangeActionIns::ScChangeActionIns( SvStream& rStrm,
/*N*/           ScMultipleReadHeader& rHdr, ScChangeTrack* pTrack )
/*N*/       :
/*N*/       ScChangeAction( rStrm, rHdr, pTrack )
/*N*/ {
/*N*/ }

/*N*/ ScChangeActionIns::ScChangeActionIns(const ULONG nActionNumber, const ScChangeActionState eState, const ULONG nRejectingNumber,
/*N*/                                               const ScBigRange& aBigRange, const String& aUser, const DateTime& aDateTime, const String& sComment,
/*N*/                                               const ScChangeActionType eType)
/*N*/       :
/*N*/       ScChangeAction(eType, aBigRange, nActionNumber, nRejectingNumber, eState, aDateTime, aUser, sComment)
/*N*/ {
/*N*/ }

/*N*/  ScChangeActionIns::~ScChangeActionIns()
/*N*/  {
/*N*/  }


//STRIP001 BOOL ScChangeActionIns::Store( SvStream& rStrm, ScMultipleWriteHeader& rHdr ) const
//STRIP001 {
//STRIP001  BOOL bOk = ScChangeAction::Store( rStrm, rHdr );
//STRIP001  return bOk;
//STRIP001 }


//STRIP001 void ScChangeActionIns::GetDescription( String& rStr, ScDocument* pDoc,
//STRIP001      BOOL bSplitRange ) const
//STRIP001 {
//STRIP001  USHORT nWhatId;
//STRIP001  switch ( GetType() )
//STRIP001  {
//STRIP001      case SC_CAT_INSERT_COLS :
//STRIP001          nWhatId = STR_COLUMN;
//STRIP001      break;
//STRIP001      case SC_CAT_INSERT_ROWS :
//STRIP001          nWhatId = STR_ROW;
//STRIP001      break;
//STRIP001      default:
//STRIP001          nWhatId = STR_AREA;
//STRIP001  }
//STRIP001
//STRIP001  String aRsc( ScGlobal::GetRscString( STR_CHANGED_INSERT ) );
//STRIP001  xub_StrLen nPos = aRsc.SearchAscii( "#1" );
//STRIP001  rStr += aRsc.Copy( 0, nPos );
//STRIP001  rStr += ScGlobal::GetRscString( nWhatId );
//STRIP001  rStr += ' ';
//STRIP001  rStr += GetRefString( GetBigRange(), pDoc );
//STRIP001  rStr += aRsc.Copy( nPos+2 );
//STRIP001 }


//STRIP001 BOOL ScChangeActionIns::Reject( ScDocument* pDoc )
//STRIP001 {
//STRIP001  if ( !aBigRange.IsValid( pDoc ) )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  ScRange aRange( aBigRange.MakeRange() );
//STRIP001  if ( !pDoc->IsBlockEditable( aRange.aStart.Tab(), aRange.aStart.Col(),
//STRIP001          aRange.aStart.Row(), aRange.aEnd.Col(), aRange.aEnd.Row() ) )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  switch ( GetType() )
//STRIP001  {
//STRIP001      case SC_CAT_INSERT_COLS :
//STRIP001          pDoc->DeleteCol( aRange );
//STRIP001      break;
//STRIP001      case SC_CAT_INSERT_ROWS :
//STRIP001          pDoc->DeleteRow( aRange );
//STRIP001      break;
//STRIP001      case SC_CAT_INSERT_TABS :
//STRIP001          pDoc->DeleteTab( aRange.aStart.Tab() );
//STRIP001      break;
//STRIP001  }
//STRIP001  SetState( SC_CAS_REJECTED );
//STRIP001  RemoveAllLinks();
//STRIP001  return TRUE;
//STRIP001 }


// --- ScChangeActionDel ---------------------------------------------------

/*N*/ ScChangeActionDel::ScChangeActionDel( const ScRange& rRange,
/*N*/           short nDxP, short nDyP, ScChangeTrack* pTrackP )
/*N*/       :
/*N*/       ScChangeAction( SC_CAT_NONE, rRange ),
/*N*/       pTrack( pTrackP ),
/*N*/       pFirstCell( NULL ),
/*N*/       pLinkMove( NULL ),
/*N*/       pCutOff( NULL ),
/*N*/       nCutOff( 0 ),
/*N*/       nDx( nDxP ),
/*N*/       nDy( nDyP )
/*N*/ {
    DBG_ASSERT(0, "STRIP"); //STRIP001 if ( rRange.aStart.Col() == 0 && rRange.aEnd.Col() == MAXCOL )
//STRIP001  {
//STRIP001      aBigRange.aStart.SetCol( nInt32Min );
//STRIP001      aBigRange.aEnd.SetCol( nInt32Max );
//STRIP001      if ( rRange.aStart.Row() == 0 && rRange.aEnd.Row() == MAXROW )
//STRIP001      {
//STRIP001          SetType( SC_CAT_DELETE_TABS );
//STRIP001          aBigRange.aStart.SetRow( nInt32Min );
//STRIP001          aBigRange.aEnd.SetRow( nInt32Max );
//STRIP001      }
//STRIP001      else
//STRIP001          SetType( SC_CAT_DELETE_ROWS );
//STRIP001  }
//STRIP001  else if ( rRange.aStart.Row() == 0 && rRange.aEnd.Row() == MAXROW )
//STRIP001  {
//STRIP001      SetType( SC_CAT_DELETE_COLS );
//STRIP001      aBigRange.aStart.SetRow( nInt32Min );
//STRIP001      aBigRange.aEnd.SetRow( nInt32Max );
//STRIP001  }
//STRIP001  else
//STRIP001      DBG_ERROR( "ScChangeActionDel: Block not supported!" );
/*N*/ }


/*N*/ ScChangeActionDel::ScChangeActionDel( SvStream& rStrm,
/*N*/           ScMultipleReadHeader& rHdr, ScDocument* pDoc, USHORT nVer,
/*N*/           ScChangeTrack* pTrackP )
/*N*/       :
/*N*/       ScChangeAction( rStrm, rHdr, pTrackP ),
/*N*/       pTrack( pTrackP ),
/*N*/       pFirstCell( NULL ),
/*N*/       pLinkMove( NULL )
/*N*/ {
    DBG_ASSERT(0, "STRIP"); //STRIP001 UINT32 n32;
//STRIP001  INT16 n16s;
//STRIP001  rStrm >> n32; pCutOff = (ScChangeActionIns*)(ULONG) n32;
//STRIP001  rStrm >> n16s; nCutOff = n16s;
//STRIP001  rStrm >> n16s; nDx = n16s;
//STRIP001  rStrm >> n16s; nDy = n16s;
/*N*/ }

/*N*/ ScChangeActionDel::ScChangeActionDel(const ULONG nActionNumber, const ScChangeActionState eState, const ULONG nRejectingNumber,
/*N*/                                   const ScBigRange& aBigRange, const String& aUser, const DateTime& aDateTime, const String &sComment,
/*N*/                                   const ScChangeActionType eType, const short nD, ScChangeTrack* pTrackP) // wich of nDx and nDy is set is depend on the type
/*N*/       :
/*N*/       ScChangeAction(eType, aBigRange, nActionNumber, nRejectingNumber, eState, aDateTime, aUser, sComment),
/*N*/       pTrack( pTrackP ),
/*N*/       pFirstCell( NULL ),
/*N*/       pLinkMove( NULL ),
/*N*/       pCutOff( NULL ),
/*N*/       nCutOff( 0 ),
/*N*/       nDx( 0 ),
/*N*/       nDy( 0 )
/*N*/ {
    DBG_ASSERT(0, "STRIP"); //STRIP001 if (eType == SC_CAT_DELETE_COLS)
//STRIP001      nDx = nD;
//STRIP001  else if (eType == SC_CAT_DELETE_ROWS)
//STRIP001      nDy = nD;
/*N*/ }

//STRIP001 ScChangeActionDel::~ScChangeActionDel()
//STRIP001 {
//STRIP001  DeleteCellEntries();
//STRIP001  while ( pLinkMove )
//STRIP001      delete pLinkMove;
//STRIP001 }


//STRIP001 BOOL ScChangeActionDel::Store( SvStream& rStrm, ScMultipleWriteHeader& rHdr ) const
//STRIP001 {
//STRIP001  BOOL bOk = ScChangeAction::Store( rStrm, rHdr );
//STRIP001  rStrm << (UINT32) ( pCutOff ? pCutOff->GetActionNumber() : 0 );
//STRIP001  rStrm << (INT16) nCutOff;
//STRIP001  rStrm << (INT16) nDx;
//STRIP001  rStrm << (INT16) nDy;
//STRIP001  return bOk;
//STRIP001 }


//STRIP001 BOOL ScChangeActionDel::StoreLinks( SvStream& rStrm ) const
//STRIP001 {
//STRIP001  BOOL bOk = ScChangeAction::StoreLinks( rStrm );
//STRIP001  UINT32 nCount = 0;
//STRIP001  if ( pLinkMove )
//STRIP001  {
//STRIP001      // rueckwaerts speichern, damit onLoad mit Insert die Reihenfolge wieder stimmt
//STRIP001      Stack* pStack = new Stack;
//STRIP001      for ( ScChangeActionDelMoveEntry* pL = pLinkMove; pL; pL = pL->GetNext() )
//STRIP001      {
//STRIP001          ++nCount;
//STRIP001          pStack->Push( pL );
//STRIP001      }
//STRIP001      rStrm << nCount;
//STRIP001      ScChangeActionDelMoveEntry* pHere;
//STRIP001      while ( pHere = (ScChangeActionDelMoveEntry*) pStack->Pop() )
//STRIP001      {
//STRIP001          ScChangeAction* p = pHere->GetAction();
//STRIP001          rStrm << (UINT32) ( p ? p->GetActionNumber() : 0 );
//STRIP001          rStrm << (INT16) pHere->GetCutOffFrom();
//STRIP001          rStrm << (INT16) pHere->GetCutOffTo();
//STRIP001      }
//STRIP001      delete pStack;
//STRIP001  }
//STRIP001  else
//STRIP001      rStrm << nCount;
//STRIP001
//STRIP001  bOk &= ScChangeAction::StoreCellList( pFirstCell, rStrm );
//STRIP001
//STRIP001  return bOk;
//STRIP001 }


//STRIP001 BOOL ScChangeActionDel::LoadLinks( SvStream& rStrm, ScChangeTrack* pTrack )
//STRIP001 {
//STRIP001  BOOL bOk = ScChangeAction::LoadLinks( rStrm, pTrack );
//STRIP001  UINT32 nCount;
//STRIP001  rStrm >> nCount;
//STRIP001  for ( UINT32 j = 0; j < nCount; j++ )
//STRIP001  {
//STRIP001      ScChangeActionMove* pAct = NULL;
//STRIP001      UINT32 nAct;
//STRIP001      rStrm >> nAct;
//STRIP001      if ( nAct )
//STRIP001      {
//STRIP001          pAct = (ScChangeActionMove*) pTrack->GetAction( nAct );
//STRIP001          DBG_ASSERT( pAct, "ScChangeActionDel::LoadLinks: missing Move" );
//STRIP001      }
//STRIP001      INT16 nFrom, nTo;
//STRIP001      rStrm >> nFrom >> nTo;
//STRIP001      ScChangeActionDelMoveEntry* pLink = new ScChangeActionDelMoveEntry(
//STRIP001          &pLinkMove, pAct, nFrom, nTo );
//STRIP001      if ( pAct )
//STRIP001          pAct->AddLink( this, pLink );
//STRIP001  }
//STRIP001  if ( pCutOff )
//STRIP001  {
//STRIP001      pCutOff = (ScChangeActionIns*) pTrack->GetAction( (ULONG) pCutOff );
//STRIP001      DBG_ASSERT( pCutOff, "ScChangeActionDel::LoadLinks: missing Insert" );
//STRIP001  }
//STRIP001
//STRIP001  bOk &= ScChangeAction::LoadCellList( this, pFirstCell, rStrm, pTrack );
//STRIP001
//STRIP001  return bOk;
//STRIP001 }

//STRIP001 void ScChangeActionDel::AddContent( ScChangeActionContent* pContent )
//STRIP001 {
//STRIP001  ScChangeActionCellListEntry* pE = new ScChangeActionCellListEntry(
//STRIP001      pContent, pFirstCell );
//STRIP001  pFirstCell = pE;
//STRIP001 }


//STRIP001 void ScChangeActionDel::DeleteCellEntries()
//STRIP001 {
//STRIP001  pTrack->DeleteCellEntries( pFirstCell, this );
//STRIP001 }


//STRIP001 BOOL ScChangeActionDel::IsBaseDelete() const
//STRIP001 {
//STRIP001  return !GetDx() && !GetDy();
//STRIP001 }


//STRIP001 BOOL ScChangeActionDel::IsTopDelete() const
//STRIP001 {
//STRIP001  const ScChangeAction* p = GetNext();
//STRIP001  if ( !p || p->GetType() != GetType() )
//STRIP001      return TRUE;
//STRIP001  return ((ScChangeActionDel*)p)->IsBaseDelete();
//STRIP001 }


//STRIP001 BOOL ScChangeActionDel::IsMultiDelete() const
//STRIP001 {
//STRIP001  if ( GetDx() || GetDy() )
//STRIP001      return TRUE;
//STRIP001  const ScChangeAction* p = GetNext();
//STRIP001  if ( !p || p->GetType() != GetType() )
//STRIP001      return FALSE;
//STRIP001  const ScChangeActionDel* pDel = (const ScChangeActionDel*) p;
//STRIP001  if ( (pDel->GetDx() > GetDx() || pDel->GetDy() > GetDy()) &&
//STRIP001          pDel->GetBigRange() == aBigRange )
//STRIP001      return TRUE;
//STRIP001  return FALSE;
//STRIP001 }


//STRIP001 BOOL ScChangeActionDel::IsTabDeleteCol() const
//STRIP001 {
//STRIP001  if ( GetType() != SC_CAT_DELETE_COLS )
//STRIP001      return FALSE;
//STRIP001  const ScChangeAction* p = this;
//STRIP001  while ( p && p->GetType() == SC_CAT_DELETE_COLS &&
//STRIP001          !((const ScChangeActionDel*)p)->IsTopDelete() )
//STRIP001      p = p->GetNext();
//STRIP001  return p && p->GetType() == SC_CAT_DELETE_TABS;
//STRIP001 }


//STRIP001 void ScChangeActionDel::UpdateReference( const ScChangeTrack* pTrack,
//STRIP001      UpdateRefMode eMode, const ScBigRange& rRange,
//STRIP001      INT32 nDx, INT32 nDy, INT32 nDz )
//STRIP001 {
//STRIP001  ScRefUpdate::Update( eMode, rRange, nDx, nDy, nDz, GetBigRange() );
//STRIP001  if ( !IsDeletedIn() )
//STRIP001      return ;
//STRIP001  // evtl. in "druntergerutschten" anpassen
//STRIP001  for ( ScChangeActionLinkEntry* pL = pLinkDeleted; pL; pL = pL->GetNext() )
//STRIP001  {
//STRIP001      ScChangeAction* p = pL->GetAction();
//STRIP001      if ( p && p->GetType() == SC_CAT_CONTENT &&
//STRIP001              !GetBigRange().In( p->GetBigRange() ) )
//STRIP001      {
//STRIP001          switch ( GetType() )
//STRIP001          {
//STRIP001              case SC_CAT_DELETE_COLS :
//STRIP001                  p->GetBigRange().aStart.SetCol( GetBigRange().aStart.Col() );
//STRIP001                  p->GetBigRange().aEnd.SetCol( GetBigRange().aStart.Col() );
//STRIP001              break;
//STRIP001              case SC_CAT_DELETE_ROWS :
//STRIP001                  p->GetBigRange().aStart.SetRow( GetBigRange().aStart.Row() );
//STRIP001                  p->GetBigRange().aEnd.SetRow( GetBigRange().aStart.Row() );
//STRIP001              break;
//STRIP001              case SC_CAT_DELETE_TABS :
//STRIP001                  p->GetBigRange().aStart.SetTab( GetBigRange().aStart.Tab() );
//STRIP001                  p->GetBigRange().aEnd.SetTab( GetBigRange().aStart.Tab() );
//STRIP001              break;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 }


//STRIP001 ScBigRange ScChangeActionDel::GetOverAllRange() const
//STRIP001 {
//STRIP001  ScBigRange aTmpRange( GetBigRange() );
//STRIP001  aTmpRange.aEnd.SetCol( aTmpRange.aEnd.Col() + GetDx() );
//STRIP001  aTmpRange.aEnd.SetRow( aTmpRange.aEnd.Row() + GetDy() );
//STRIP001  return aTmpRange;
//STRIP001 }


//STRIP001 void ScChangeActionDel::GetDescription( String& rStr, ScDocument* pDoc,
//STRIP001      BOOL bSplitRange ) const
//STRIP001 {
//STRIP001  USHORT nWhatId;
//STRIP001  switch ( GetType() )
//STRIP001  {
//STRIP001      case SC_CAT_DELETE_COLS :
//STRIP001          nWhatId = STR_COLUMN;
//STRIP001      break;
//STRIP001      case SC_CAT_DELETE_ROWS :
//STRIP001          nWhatId = STR_ROW;
//STRIP001      break;
//STRIP001      default:
//STRIP001          nWhatId = STR_AREA;
//STRIP001  }
//STRIP001
//STRIP001  ScBigRange aTmpRange( GetBigRange() );
//STRIP001  if ( !IsRejected() )
//STRIP001  {
//STRIP001      if ( bSplitRange )
//STRIP001      {
//STRIP001          aTmpRange.aStart.SetCol( aTmpRange.aStart.Col() + GetDx() );
//STRIP001          aTmpRange.aStart.SetRow( aTmpRange.aStart.Row() + GetDy() );
//STRIP001      }
//STRIP001      aTmpRange.aEnd.SetCol( aTmpRange.aEnd.Col() + GetDx() );
//STRIP001      aTmpRange.aEnd.SetRow( aTmpRange.aEnd.Row() + GetDy() );
//STRIP001  }
//STRIP001
//STRIP001  String aRsc( ScGlobal::GetRscString( STR_CHANGED_DELETE ) );
//STRIP001  xub_StrLen nPos = aRsc.SearchAscii( "#1" );
//STRIP001  rStr += aRsc.Copy( 0, nPos );
//STRIP001  rStr += ScGlobal::GetRscString( nWhatId );
//STRIP001  rStr += ' ';
//STRIP001  rStr += GetRefString( aTmpRange, pDoc );
//STRIP001  rStr += aRsc.Copy( nPos+2 );
//STRIP001 }


//STRIP001 BOOL ScChangeActionDel::Reject( ScDocument* pDoc )
//STRIP001 {
//STRIP001  if ( !aBigRange.IsValid( pDoc ) && GetType() != SC_CAT_DELETE_TABS )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  BOOL bOk = TRUE;
//STRIP001
//STRIP001  if ( IsTopDelete() )
//STRIP001  {   // den kompletten Bereich in einem Rutsch restaurieren
//STRIP001      ScBigRange aTmpRange( GetOverAllRange() );
//STRIP001      if ( !aTmpRange.IsValid( pDoc ) )
//STRIP001      {
//STRIP001          if ( GetType() == SC_CAT_DELETE_TABS )
//STRIP001          {   // wird Tab angehaengt?
//STRIP001              if ( aTmpRange.aStart.Tab() > pDoc->GetMaxTableNumber() )
//STRIP001                  bOk = FALSE;
//STRIP001          }
//STRIP001          else
//STRIP001              bOk = FALSE;
//STRIP001      }
//STRIP001      if ( bOk )
//STRIP001      {
//STRIP001          ScRange aRange( aTmpRange.MakeRange() );
//STRIP001          // InDelete... fuer Formel UpdateReference in Document
//STRIP001          pTrack->SetInDeleteRange( aRange );
//STRIP001          pTrack->SetInDeleteTop( TRUE );
//STRIP001          pTrack->SetInDeleteUndo( TRUE );
//STRIP001          pTrack->SetInDelete( TRUE );
//STRIP001          switch ( GetType() )
//STRIP001          {
//STRIP001              case SC_CAT_DELETE_COLS :
//STRIP001                  if ( !(aRange.aStart.Col() == 0 && aRange.aEnd.Col() == MAXCOL) )
//STRIP001                  {   // nur wenn nicht TabDelete
//STRIP001                      if ( bOk = pDoc->CanInsertCol( aRange ) )
//STRIP001                          bOk = pDoc->InsertCol( aRange );
//STRIP001                  }
//STRIP001              break;
//STRIP001              case SC_CAT_DELETE_ROWS :
//STRIP001                  if ( bOk = pDoc->CanInsertRow( aRange ) )
//STRIP001                      bOk = pDoc->InsertRow( aRange );
//STRIP001              break;
//STRIP001              case SC_CAT_DELETE_TABS :
//STRIP001              {
//STRIP001 //2do: Tabellennamen merken?
//STRIP001                  String aName;
//STRIP001                  pDoc->CreateValidTabName( aName );
//STRIP001                  if ( bOk = pDoc->ValidNewTabName( aName ) )
//STRIP001                      bOk = pDoc->InsertTab( aRange.aStart.Tab(), aName );
//STRIP001              }
//STRIP001              break;
//STRIP001          }
//STRIP001          pTrack->SetInDelete( FALSE );
//STRIP001          pTrack->SetInDeleteUndo( FALSE );
//STRIP001      }
//STRIP001      if ( !bOk )
//STRIP001      {
//STRIP001          pTrack->SetInDeleteTop( FALSE );
//STRIP001          return FALSE;
//STRIP001      }
//STRIP001      // InDeleteTop fuer UpdateReference-Undo behalten
//STRIP001  }
//STRIP001
//STRIP001  // setzt rejected und ruft UpdateReference-Undo und DeleteCellEntries
//STRIP001  RejectRestoreContents( pTrack, GetDx(), GetDy() );
//STRIP001
//STRIP001  pTrack->SetInDeleteTop( FALSE );
//STRIP001  RemoveAllLinks();
//STRIP001  return TRUE;
//STRIP001 }


//STRIP001 void ScChangeActionDel::UndoCutOffMoves()
//STRIP001 {    // abgeschnittene Moves wiederherstellen, Entries/Links deleten
//STRIP001  while ( pLinkMove )
//STRIP001  {
//STRIP001      ScChangeActionMove* pMove = pLinkMove->GetMove();
//STRIP001      short nFrom = pLinkMove->GetCutOffFrom();
//STRIP001      short nTo = pLinkMove->GetCutOffTo();
//STRIP001      switch ( GetType() )
//STRIP001      {
//STRIP001          case SC_CAT_DELETE_COLS :
//STRIP001              if ( nFrom > 0 )
//STRIP001                  pMove->GetFromRange().aStart.IncCol( -nFrom );
//STRIP001              else if ( nFrom < 0 )
//STRIP001                  pMove->GetFromRange().aEnd.IncCol( -nFrom );
//STRIP001              if ( nTo > 0 )
//STRIP001                  pMove->GetBigRange().aStart.IncCol( -nTo );
//STRIP001              else if ( nTo < 0 )
//STRIP001                  pMove->GetBigRange().aEnd.IncCol( -nTo );
//STRIP001          break;
//STRIP001          case SC_CAT_DELETE_ROWS :
//STRIP001              if ( nFrom > 0 )
//STRIP001                  pMove->GetFromRange().aStart.IncRow( -nFrom );
//STRIP001              else if ( nFrom < 0 )
//STRIP001                  pMove->GetFromRange().aEnd.IncRow( -nFrom );
//STRIP001              if ( nTo > 0 )
//STRIP001                  pMove->GetBigRange().aStart.IncRow( -nTo );
//STRIP001              else if ( nTo < 0 )
//STRIP001                  pMove->GetBigRange().aEnd.IncRow( -nTo );
//STRIP001          break;
//STRIP001          case SC_CAT_DELETE_TABS :
//STRIP001              if ( nFrom > 0 )
//STRIP001                  pMove->GetFromRange().aStart.IncTab( -nFrom );
//STRIP001              else if ( nFrom < 0 )
//STRIP001                  pMove->GetFromRange().aEnd.IncTab( -nFrom );
//STRIP001              if ( nTo > 0 )
//STRIP001                  pMove->GetBigRange().aStart.IncTab( -nTo );
//STRIP001              else if ( nTo < 0 )
//STRIP001                  pMove->GetBigRange().aEnd.IncTab( -nTo );
//STRIP001          break;
//STRIP001      }
//STRIP001      delete pLinkMove;       // rueckt sich selbst hoch
//STRIP001  }
//STRIP001 }

//STRIP001 void ScChangeActionDel::UndoCutOffInsert()
//STRIP001 {    // abgeschnittenes Insert wiederherstellen
//STRIP001  if ( pCutOff )
//STRIP001  {
//STRIP001      switch ( pCutOff->GetType() )
//STRIP001      {
//STRIP001          case SC_CAT_INSERT_COLS :
//STRIP001              if ( nCutOff < 0 )
//STRIP001                  pCutOff->GetBigRange().aEnd.IncCol( -nCutOff );
//STRIP001              else
//STRIP001                  pCutOff->GetBigRange().aStart.IncCol( -nCutOff );
//STRIP001          break;
//STRIP001          case SC_CAT_INSERT_ROWS :
//STRIP001              if ( nCutOff < 0 )
//STRIP001                  pCutOff->GetBigRange().aEnd.IncRow( -nCutOff );
//STRIP001              else
//STRIP001                  pCutOff->GetBigRange().aStart.IncRow( -nCutOff );
//STRIP001          break;
//STRIP001          case SC_CAT_INSERT_TABS :
//STRIP001              if ( nCutOff < 0 )
//STRIP001                  pCutOff->GetBigRange().aEnd.IncTab( -nCutOff );
//STRIP001              else
//STRIP001                  pCutOff->GetBigRange().aStart.IncTab( -nCutOff );
//STRIP001          break;
//STRIP001      }
//STRIP001      SetCutOffInsert( NULL, 0 );
//STRIP001  }
//STRIP001 }


// --- ScChangeActionMove --------------------------------------------------

/*N*/ ScChangeActionMove::ScChangeActionMove( SvStream& rStrm,
/*N*/           ScMultipleReadHeader& rHdr, ScChangeTrack* pTrackP )
/*N*/       :
/*N*/       ScChangeAction( rStrm, rHdr, pTrackP ),
/*N*/       pTrack( pTrackP ),
/*N*/       pFirstCell( NULL ),
/*N*/       nStartLastCut(0),
/*N*/       nEndLastCut(0)
/*N*/ {
    DBG_ASSERT(0, "STRIP"); //STRIP001 rStrm >> aFromRange;
/*N*/ }

/*N*/ ScChangeActionMove::ScChangeActionMove(const ULONG nActionNumber, const ScChangeActionState eState, const ULONG nRejectingNumber,
/*N*/                                   const ScBigRange& aToBigRange, const String& aUser, const DateTime& aDateTime, const String &sComment,
/*N*/                                   const ScBigRange& aFromBigRange, ScChangeTrack* pTrackP) // wich of nDx and nDy is set is depend on the type
/*N*/       :
/*N*/       ScChangeAction(SC_CAT_MOVE, aToBigRange, nActionNumber, nRejectingNumber, eState, aDateTime, aUser, sComment),
/*N*/       aFromRange(aFromBigRange),
/*N*/       pTrack( pTrackP ),
/*N*/       pFirstCell( NULL ),
/*N*/       nStartLastCut(0),
/*N*/       nEndLastCut(0)
/*N*/ { DBG_ASSERT(0, "STRIP"); //STRIP001
/*N*/ }

//STRIP001 ScChangeActionMove::~ScChangeActionMove()
//STRIP001 {
//STRIP001  DeleteCellEntries();
//STRIP001 }


//STRIP001 BOOL ScChangeActionMove::Store( SvStream& rStrm, ScMultipleWriteHeader& rHdr ) const
//STRIP001 {
//STRIP001  BOOL bOk = ScChangeAction::Store( rStrm, rHdr );
//STRIP001  rStrm << aFromRange;
//STRIP001  return bOk;
//STRIP001 }


//STRIP001 BOOL ScChangeActionMove::StoreLinks( SvStream& rStrm ) const
//STRIP001 {
//STRIP001  BOOL bOk = ScChangeAction::StoreLinks( rStrm );
//STRIP001  bOk &= ScChangeAction::StoreCellList( pFirstCell, rStrm );
//STRIP001  return bOk;
//STRIP001 }


//STRIP001 BOOL ScChangeActionMove::LoadLinks( SvStream& rStrm, ScChangeTrack* pTrack )
//STRIP001 {
//STRIP001  BOOL bOk = ScChangeAction::LoadLinks( rStrm, pTrack );
//STRIP001  bOk &= ScChangeAction::LoadCellList( this, pFirstCell, rStrm, pTrack );
//STRIP001  return bOk;
//STRIP001 }


//STRIP001 void ScChangeActionMove::AddContent( ScChangeActionContent* pContent )
//STRIP001 {
//STRIP001  ScChangeActionCellListEntry* pE = new ScChangeActionCellListEntry(
//STRIP001      pContent, pFirstCell );
//STRIP001  pFirstCell = pE;
//STRIP001 }


//STRIP001 void ScChangeActionMove::DeleteCellEntries()
//STRIP001 {
//STRIP001  pTrack->DeleteCellEntries( pFirstCell, this );
//STRIP001 }


//STRIP001 void ScChangeActionMove::UpdateReference( const ScChangeTrack* pTrack,
//STRIP001      UpdateRefMode eMode, const ScBigRange& rRange,
//STRIP001      INT32 nDx, INT32 nDy, INT32 nDz )
//STRIP001 {
//STRIP001  ScRefUpdate::Update( eMode, rRange, nDx, nDy, nDz, aFromRange );
//STRIP001  ScRefUpdate::Update( eMode, rRange, nDx, nDy, nDz, GetBigRange() );
//STRIP001 }


//STRIP001 void ScChangeActionMove::GetDelta( INT32& nDx, INT32& nDy, INT32& nDz ) const
//STRIP001 {
//STRIP001  const ScBigAddress& rToPos = GetBigRange().aStart;
//STRIP001  const ScBigAddress& rFromPos = GetFromRange().aStart;
//STRIP001  nDx = rToPos.Col() - rFromPos.Col();
//STRIP001  nDy = rToPos.Row() - rFromPos.Row();
//STRIP001  nDz = rToPos.Tab() - rFromPos.Tab();
//STRIP001 }


//STRIP001 void ScChangeActionMove::GetDescription( String& rStr, ScDocument* pDoc,
//STRIP001      BOOL bSplitRange ) const
//STRIP001 {
//STRIP001  BOOL bFlag3D = ( GetFromRange().aStart.Tab() != GetBigRange().aStart.Tab() );
//STRIP001
//STRIP001  String aRsc( ScGlobal::GetRscString( STR_CHANGED_MOVE ) );
//STRIP001
//STRIP001  xub_StrLen nPos = 0;
//STRIP001  String aTmpStr = ScChangeAction::GetRefString( GetFromRange(), pDoc, bFlag3D );
//STRIP001  nPos = aRsc.SearchAscii( "#1", nPos );
//STRIP001  aRsc.Erase( nPos, 2 );
//STRIP001  aRsc.Insert( aTmpStr, nPos );
//STRIP001  nPos += aTmpStr.Len();
//STRIP001
//STRIP001  aTmpStr = ScChangeAction::GetRefString( GetBigRange(), pDoc, bFlag3D );
//STRIP001  nPos = aRsc.SearchAscii( "#2", nPos );
//STRIP001  aRsc.Erase( nPos, 2 );
//STRIP001  aRsc.Insert( aTmpStr, nPos );
//STRIP001  nPos += aTmpStr.Len();
//STRIP001
//STRIP001  rStr += aRsc;
//STRIP001 }


//STRIP001 void ScChangeActionMove::GetRefString( String& rStr, ScDocument* pDoc,
//STRIP001      BOOL bFlag3D ) const
//STRIP001 {
//STRIP001  if ( !bFlag3D )
//STRIP001      bFlag3D = ( GetFromRange().aStart.Tab() != GetBigRange().aStart.Tab() );
//STRIP001  rStr = ScChangeAction::GetRefString( GetFromRange(), pDoc, bFlag3D );
//STRIP001  rStr += ',';
//STRIP001  rStr += ' ';
//STRIP001  rStr += ScChangeAction::GetRefString( GetBigRange(), pDoc, bFlag3D );
//STRIP001 }


//STRIP001 BOOL ScChangeActionMove::Reject( ScDocument* pDoc )
//STRIP001 {
//STRIP001  if ( !(aBigRange.IsValid( pDoc ) && aFromRange.IsValid( pDoc )) )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  ScRange aToRange( aBigRange.MakeRange() );
//STRIP001  ScRange aFrmRange( aFromRange.MakeRange() );
//STRIP001
//STRIP001  BOOL bOk = pDoc->IsBlockEditable( aToRange.aStart.Tab(),
//STRIP001      aToRange.aStart.Col(), aToRange.aStart.Row(),
//STRIP001      aToRange.aEnd.Col(), aToRange.aEnd.Row() );
//STRIP001  if ( bOk )
//STRIP001      bOk = pDoc->IsBlockEditable( aFrmRange.aStart.Tab(),
//STRIP001          aFrmRange.aStart.Col(), aFrmRange.aStart.Row(),
//STRIP001          aFrmRange.aEnd.Col(), aFrmRange.aEnd.Row() );
//STRIP001  if ( !bOk )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  pTrack->LookUpContents( aToRange, pDoc, 0, 0, 0 );  // zu movende Contents
//STRIP001
//STRIP001  pDoc->DeleteAreaTab( aToRange, IDF_ALL );
//STRIP001  pDoc->DeleteAreaTab( aFrmRange, IDF_ALL );
//STRIP001  // Formeln im Dokument anpassen
//STRIP001  pDoc->UpdateReference( URM_MOVE,
//STRIP001      aFrmRange.aStart.Col(), aFrmRange.aStart.Row(), aFrmRange.aStart.Tab(),
//STRIP001      aFrmRange.aEnd.Col(), aFrmRange.aEnd.Row(), aFrmRange.aEnd.Tab(),
//STRIP001      (short) aFrmRange.aStart.Col() - aToRange.aStart.Col(),
//STRIP001      (short) aFrmRange.aStart.Row() - aToRange.aStart.Row(),
//STRIP001      (short) aFrmRange.aStart.Tab() - aToRange.aStart.Tab(), NULL );
//STRIP001
//STRIP001  // LinkDependent freigeben, nachfolgendes UpdateReference-Undo setzt
//STRIP001  // ToRange->FromRange Dependents
//STRIP001  RemoveAllDependent();
//STRIP001
//STRIP001  // setzt rejected und ruft UpdateReference-Undo und DeleteCellEntries
//STRIP001  RejectRestoreContents( pTrack, 0, 0 );
//STRIP001
//STRIP001  while ( pLinkDependent )
//STRIP001  {
//STRIP001      ScChangeAction* p = pLinkDependent->GetAction();
//STRIP001      if ( p && p->GetType() == SC_CAT_CONTENT )
//STRIP001      {
//STRIP001          ScChangeActionContent* pContent = (ScChangeActionContent*) p;
//STRIP001          if ( !pContent->IsDeletedIn() &&
//STRIP001                  pContent->GetBigRange().aStart.IsValid( pDoc ) )
//STRIP001              pContent->PutNewValueToDoc( pDoc, 0, 0 );
//STRIP001          // in LookUpContents generierte loeschen
//STRIP001          if ( pTrack->IsGenerated( pContent->GetActionNumber() ) &&
//STRIP001                  !pContent->IsDeletedIn() )
//STRIP001          {
//STRIP001              pLinkDependent->UnLink();       //! sonst wird der mitgeloescht
//STRIP001              pTrack->DeleteGeneratedDelContent( pContent );
//STRIP001          }
//STRIP001      }
//STRIP001      delete pLinkDependent;
//STRIP001  }
//STRIP001
//STRIP001  RemoveAllLinks();
//STRIP001  return TRUE;
//STRIP001 }


// --- ScChangeActionContent -----------------------------------------------

const USHORT nMemPoolChangeActionContent = (0x8000 - 64) / sizeof(ScChangeActionContent);
/*N*/ IMPL_FIXEDMEMPOOL_NEWDEL( ScChangeActionContent, nMemPoolChangeActionContent, nMemPoolChangeActionContent )//STRIP008 ;


/*N*/ ScChangeActionContent::ScChangeActionContent( SvStream& rStrm,
/*N*/           ScMultipleReadHeader& rHdr, ScDocument* pDoc, USHORT nVer,
/*N*/           ScChangeTrack* pTrack )
/*N*/       :
/*N*/       ScChangeAction( rStrm, rHdr, pTrack ),
/*N*/       pNextInSlot( NULL ),
/*N*/       ppPrevInSlot( NULL )
/*N*/ {
    DBG_ASSERT(0, "STRIP"); //STRIP001 UINT32 n32;
//STRIP001  rStrm.ReadByteString( aOldValue, rStrm.GetStreamCharSet() );
//STRIP001  rStrm.ReadByteString( aNewValue, rStrm.GetStreamCharSet() );
//STRIP001  rStrm >> n32; pNextContent = (ScChangeActionContent*)(ULONG) n32;
//STRIP001  rStrm >> n32; pPrevContent = (ScChangeActionContent*)(ULONG) n32;
//STRIP001
//STRIP001  {
//STRIP001      ScMultipleReadHeader aDataHdr( rStrm );
//STRIP001      pOldCell = ScChangeAction::LoadCell( rStrm, aDataHdr, pDoc, nVer );
//STRIP001      pNewCell = ScChangeAction::LoadCell( rStrm, aDataHdr, pDoc, nVer );
//STRIP001  }
/*N*/ }

/*N*/ ScChangeActionContent::ScChangeActionContent( const ULONG nActionNumber,
/*N*/           const ScChangeActionState eState, const ULONG nRejectingNumber,
/*N*/           const ScBigRange& aBigRange, const String& aUser,
/*N*/           const DateTime& aDateTime, const String& sComment,
/*N*/           ScBaseCell* pTempOldCell, ScDocument* pDoc, const String& sResult )
/*N*/       :
/*N*/       ScChangeAction(SC_CAT_CONTENT, aBigRange, nActionNumber, nRejectingNumber, eState, aDateTime, aUser, sComment),
/*N*/       pOldCell(pTempOldCell),
/*N*/       pNewCell(NULL),
/*N*/       pNextContent(NULL),
/*N*/       pPrevContent(NULL),
/*N*/       pNextInSlot(NULL),
/*N*/       ppPrevInSlot(NULL),
/*N*/       aOldValue(sResult)
/*N*/
/*N*/ {
    DBG_ASSERT(0, "STRIP"); //STRIP001 if (pOldCell)
//STRIP001      ScChangeActionContent::SetCell( aOldValue, pOldCell, 0, pDoc );
/*N*/ }

/*N*/ ScChangeActionContent::ScChangeActionContent( const ULONG nActionNumber,
/*N*/           ScBaseCell* pTempNewCell, const ScBigRange& aBigRange,
/*N*/           ScDocument* pDoc )
/*N*/       :
/*N*/       ScChangeAction(SC_CAT_CONTENT, aBigRange, nActionNumber),
/*N*/       pNewCell(pTempNewCell),
/*N*/       pOldCell(NULL),
/*N*/       pNextContent(NULL),
/*N*/       pPrevContent(NULL),
/*N*/       pNextInSlot(NULL),
/*N*/       ppPrevInSlot(NULL)
/*N*/ {
    DBG_ASSERT(0, "STRIP"); //STRIP001 if (pNewCell)
//STRIP001      ScChangeActionContent::SetCell( aNewValue, pNewCell, 0, pDoc );
/*N*/ }

//STRIP001 ScChangeActionContent::~ScChangeActionContent()
//STRIP001 {
//STRIP001  ClearTrack();
//STRIP001 }


//STRIP001 void ScChangeActionContent::ClearTrack()
//STRIP001 {
//STRIP001  RemoveFromSlot();
//STRIP001  if ( pPrevContent )
//STRIP001      pPrevContent->pNextContent = pNextContent;
//STRIP001  if ( pNextContent )
//STRIP001      pNextContent->pPrevContent = pPrevContent;
//STRIP001 }


//STRIP001 BOOL ScChangeActionContent::Store( SvStream& rStrm, ScMultipleWriteHeader& rHdr ) const
//STRIP001 {
//STRIP001  BOOL bOk = ScChangeAction::Store( rStrm, rHdr );
//STRIP001  rStrm.WriteByteString( aOldValue, rStrm.GetStreamCharSet() );
//STRIP001  rStrm.WriteByteString( aNewValue, rStrm.GetStreamCharSet() );
//STRIP001  rStrm << (UINT32) ( pNextContent ? pNextContent->GetActionNumber() : 0 );
//STRIP001  rStrm << (UINT32) ( pPrevContent ? pPrevContent->GetActionNumber() : 0 );
//STRIP001
//STRIP001  {
//STRIP001      ScMultipleWriteHeader aDataHdr( rStrm );
//STRIP001      ScChangeAction::StoreCell( pOldCell, rStrm, aDataHdr );
//STRIP001      ScChangeAction::StoreCell( pNewCell, rStrm, aDataHdr );
//STRIP001  }
//STRIP001
//STRIP001  return bOk;
//STRIP001 }


//STRIP001 BOOL ScChangeActionContent::StoreLinks( SvStream& rStrm ) const
//STRIP001 {
//STRIP001  BOOL bOk = ScChangeAction::StoreLinks( rStrm );
//STRIP001  return bOk;
//STRIP001 }


//STRIP001 BOOL ScChangeActionContent::LoadLinks( SvStream& rStrm, ScChangeTrack* pTrack )
//STRIP001 {
//STRIP001  BOOL bOk = ScChangeAction::LoadLinks( rStrm, pTrack );
//STRIP001  if ( pNextContent )
//STRIP001  {
//STRIP001      pNextContent = (ScChangeActionContent*) pTrack->GetAction(
//STRIP001          (ULONG) pNextContent );
//STRIP001      DBG_ASSERT( pNextContent,
//STRIP001          "ScChangeActionContent::LoadLinks: missing NextContent" );
//STRIP001  }
//STRIP001  if ( pPrevContent )
//STRIP001  {
//STRIP001      pPrevContent = (ScChangeActionContent*) pTrack->GetAction(
//STRIP001          (ULONG) pPrevContent );
//STRIP001      DBG_ASSERT( pPrevContent,
//STRIP001          "ScChangeActionContent::LoadLinks: missing PrevContent" );
//STRIP001  }
//STRIP001  return bOk;
//STRIP001 }


//STRIP001 ScChangeActionContent* ScChangeActionContent::GetTopContent() const
//STRIP001 {
//STRIP001  if ( pNextContent )
//STRIP001  {
//STRIP001      ScChangeActionContent* pContent = pNextContent;
//STRIP001      while ( pContent->pNextContent )
//STRIP001          pContent = pContent->pNextContent;
//STRIP001      return pContent;
//STRIP001  }
//STRIP001  return (ScChangeActionContent*) this;
//STRIP001 }


//STRIP001 ScChangeActionLinkEntry* ScChangeActionContent::GetDeletedIn() const
//STRIP001 {
//STRIP001  if ( pNextContent )
//STRIP001      return GetTopContent()->pLinkDeletedIn;
//STRIP001  return pLinkDeletedIn;
//STRIP001 }


//STRIP001 ScChangeActionLinkEntry** ScChangeActionContent::GetDeletedInAddress()
//STRIP001 {
//STRIP001  if ( pNextContent )
//STRIP001      return GetTopContent()->GetDeletedInAddress();
//STRIP001  return &pLinkDeletedIn;
//STRIP001 }


//STRIP001 void ScChangeActionContent::SetOldValue( const ScBaseCell* pCell,
//STRIP001      const ScDocument* pFromDoc, ScDocument* pToDoc, ULONG nFormat )
//STRIP001 {
//STRIP001  ScChangeActionContent::SetValue( aOldValue, pOldCell,
//STRIP001      nFormat, pCell, pFromDoc, pToDoc );
//STRIP001 }


//STRIP001 void ScChangeActionContent::SetOldValue( const ScBaseCell* pCell,
//STRIP001      const ScDocument* pFromDoc, ScDocument* pToDoc )
//STRIP001 {
//STRIP001  ScChangeActionContent::SetValue( aOldValue, pOldCell,
//STRIP001      aBigRange.aStart.MakeAddress(), pCell, pFromDoc, pToDoc );
//STRIP001 }


//STRIP001 void ScChangeActionContent::SetNewValue( const ScBaseCell* pCell,
//STRIP001      ScDocument* pDoc )
//STRIP001 {
//STRIP001  ScChangeActionContent::SetValue( aNewValue, pNewCell,
//STRIP001      aBigRange.aStart.MakeAddress(), pCell, pDoc, pDoc );
//STRIP001 }


//STRIP001 void ScChangeActionContent::SetOldNewCells( ScBaseCell* pOldCellP,
//STRIP001                      ULONG nOldFormat, ScBaseCell* pNewCellP,
//STRIP001                      ULONG nNewFormat, ScDocument* pDoc )
//STRIP001 {
//STRIP001  pOldCell = pOldCellP;
//STRIP001  pNewCell = pNewCellP;
//STRIP001  ScChangeActionContent::SetCell( aOldValue, pOldCell, nOldFormat, pDoc );
//STRIP001  ScChangeActionContent::SetCell( aNewValue, pNewCell, nNewFormat, pDoc );
//STRIP001 }

/*N*/  void ScChangeActionContent::SetNewCell( ScBaseCell* pCell, ScDocument* pDoc )
/*N*/  {
DBG_ASSERT(0, "STRIP"); //STRIP001  DBG_ASSERT( !pNewCell, "ScChangeActionContent::SetNewCell: overwriting existing cell" );
//STRIP001  pNewCell = pCell;
//STRIP001  ScChangeActionContent::SetCell( aNewValue, pNewCell, 0, pDoc );
/*N*/ }

//STRIP001 void ScChangeActionContent::SetValueString( String& rValue, ScBaseCell*& pCell,
//STRIP001      const String& rStr, ScDocument* pDoc )
//STRIP001 {
//STRIP001  if ( pCell )
//STRIP001  {
//STRIP001      pCell->Delete();
//STRIP001      pCell = NULL;
//STRIP001  }
//STRIP001  if ( rStr.Len() > 1 && rStr.GetChar(0) == '=' )
//STRIP001  {
//STRIP001      rValue.Erase();
//STRIP001      pCell = new ScFormulaCell(
//STRIP001          pDoc, aBigRange.aStart.MakeAddress(), rStr );
//STRIP001      ((ScFormulaCell*)pCell)->SetInChangeTrack( TRUE );
//STRIP001  }
//STRIP001  else
//STRIP001      rValue = rStr;
//STRIP001 }


//STRIP001 void ScChangeActionContent::SetOldValue( const String& rOld, ScDocument* pDoc )
//STRIP001 {
//STRIP001  SetValueString( aOldValue, pOldCell, rOld, pDoc );
//STRIP001 }


//STRIP001 void ScChangeActionContent::SetNewValue( const String& rNew, ScDocument* pDoc )
//STRIP001 {
//STRIP001  SetValueString( aNewValue, pNewCell, rNew, pDoc );
//STRIP001 }


//STRIP001 void ScChangeActionContent::GetOldString( String& rStr ) const
//STRIP001 {
//STRIP001  GetValueString( rStr, aOldValue, pOldCell );
//STRIP001 }


//STRIP001 void ScChangeActionContent::GetNewString( String& rStr ) const
//STRIP001 {
//STRIP001  GetValueString( rStr, aNewValue, pNewCell );
//STRIP001 }


//STRIP001 void ScChangeActionContent::GetDescription( String& rStr, ScDocument* pDoc,
//STRIP001      BOOL bSplitRange ) const
//STRIP001 {
//STRIP001
//STRIP001  String aRsc( ScGlobal::GetRscString( STR_CHANGED_CELL ) );
//STRIP001
//STRIP001  String aTmpStr;
//STRIP001  GetRefString( aTmpStr, pDoc );
//STRIP001
//STRIP001  xub_StrLen nPos = 0;
//STRIP001  nPos = aRsc.SearchAscii( "#1", nPos );
//STRIP001  aRsc.Erase( nPos, 2 );
//STRIP001  aRsc.Insert( aTmpStr, nPos );
//STRIP001  nPos += aTmpStr.Len();
//STRIP001
//STRIP001  GetOldString( aTmpStr );
//STRIP001  if ( !aTmpStr.Len() )
//STRIP001      aTmpStr = ScGlobal::GetRscString( STR_CHANGED_BLANK );
//STRIP001  nPos = aRsc.SearchAscii( "#2", nPos );
//STRIP001  aRsc.Erase( nPos, 2 );
//STRIP001  aRsc.Insert( aTmpStr, nPos );
//STRIP001  nPos += aTmpStr.Len();
//STRIP001
//STRIP001  GetNewString( aTmpStr );
//STRIP001  if ( !aTmpStr.Len() )
//STRIP001      aTmpStr = ScGlobal::GetRscString( STR_CHANGED_BLANK );
//STRIP001  nPos = aRsc.SearchAscii( "#3", nPos );
//STRIP001  aRsc.Erase( nPos, 2 );
//STRIP001  aRsc.Insert( aTmpStr, nPos );
//STRIP001
//STRIP001  rStr += aRsc;
//STRIP001 }


//STRIP001 void ScChangeActionContent::GetRefString( String& rStr, ScDocument* pDoc,
//STRIP001      BOOL bFlag3D ) const
//STRIP001 {
//STRIP001  USHORT nFlags = ( GetBigRange().IsValid( pDoc ) ? SCA_VALID : 0 );
//STRIP001  if ( nFlags )
//STRIP001  {
//STRIP001      const ScBaseCell* pCell = GetNewCell();
//STRIP001      if ( ScChangeActionContent::GetContentCellType( pCell ) == SC_CACCT_MATORG )
//STRIP001      {
//STRIP001          ScBigRange aBigRange( GetBigRange() );
//STRIP001          USHORT nC, nR;
//STRIP001          ((const ScFormulaCell*)pCell)->GetMatColsRows( nC, nR );
//STRIP001          aBigRange.aEnd.IncCol( nC-1 );
//STRIP001          aBigRange.aEnd.IncRow( nR-1 );
//STRIP001          rStr = ScChangeAction::GetRefString( aBigRange, pDoc, bFlag3D );
//STRIP001
//STRIP001          return ;
//STRIP001      }
//STRIP001
//STRIP001      ScAddress aTmpAddress( GetBigRange().aStart.MakeAddress() );
//STRIP001      if ( bFlag3D )
//STRIP001          nFlags |= SCA_TAB_3D;
//STRIP001      aTmpAddress.Format( rStr, nFlags, pDoc );
//STRIP001      if ( IsDeletedIn() )
//STRIP001      {
//STRIP001          rStr.Insert( '(', 0 );
//STRIP001          rStr += ')';
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001      rStr = ScGlobal::GetRscString( STR_NOREF_STR );
//STRIP001 }


//STRIP001 BOOL ScChangeActionContent::Reject( ScDocument* pDoc )
//STRIP001 {
//STRIP001  if ( !aBigRange.IsValid( pDoc ) )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  PutOldValueToDoc( pDoc, 0, 0 );
//STRIP001
//STRIP001  SetState( SC_CAS_REJECTED );
//STRIP001  RemoveAllLinks();
//STRIP001
//STRIP001  return TRUE;
//STRIP001 }


//STRIP001 BOOL ScChangeActionContent::Select( ScDocument* pDoc, ScChangeTrack* pTrack,
//STRIP001      BOOL bOldest, Stack* pRejectActions )
//STRIP001 {
//STRIP001  if ( !aBigRange.IsValid( pDoc ) )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  ScChangeActionContent* pContent = this;
//STRIP001  // accept previous contents
//STRIP001  while ( pContent = pContent->pPrevContent )
//STRIP001  {
//STRIP001      if ( pContent->IsVirgin() )
//STRIP001          pContent->SetState( SC_CAS_ACCEPTED );
//STRIP001  }
//STRIP001  ScChangeActionContent* pEnd = pContent = this;
//STRIP001  // reject subsequent contents
//STRIP001  while ( pContent = pContent->pNextContent )
//STRIP001  {
//STRIP001      // MatrixOrigin may have dependents, no dependency recursion needed
//STRIP001      const ScChangeActionLinkEntry* pL = pContent->GetFirstDependentEntry();
//STRIP001      while ( pL )
//STRIP001      {
//STRIP001          ScChangeAction* p = (ScChangeAction*) pL->GetAction();
//STRIP001          if ( p )
//STRIP001              p->SetRejected();
//STRIP001          pL = pL->GetNext();
//STRIP001      }
//STRIP001      pContent->SetRejected();
//STRIP001      pEnd = pContent;
//STRIP001  }
//STRIP001
//STRIP001  if ( bOldest || pEnd != this )
//STRIP001  {   // wenn nicht aeltester: ist es ueberhaupt ein anderer als der letzte?
//STRIP001      ScRange aRange( aBigRange.aStart.MakeAddress() );
//STRIP001      const ScAddress& rPos = aRange.aStart;
//STRIP001
//STRIP001      ScChangeActionContent* pNew = new ScChangeActionContent( aRange );
//STRIP001      pNew->SetOldValue( pDoc->GetCell( rPos ), pDoc, pDoc );
//STRIP001
//STRIP001      if ( bOldest )
//STRIP001          PutOldValueToDoc( pDoc, 0, 0 );
//STRIP001      else
//STRIP001          PutNewValueToDoc( pDoc, 0, 0 );
//STRIP001
//STRIP001      pNew->SetRejectAction( bOldest ? GetActionNumber() : pEnd->GetActionNumber() );
//STRIP001      pNew->SetState( SC_CAS_ACCEPTED );
//STRIP001      if ( pRejectActions )
//STRIP001          pRejectActions->Push( pNew );
//STRIP001      else
//STRIP001      {
//STRIP001          pNew->SetNewValue( pDoc->GetCell( rPos ), pDoc );
//STRIP001          pTrack->Append( pNew );
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if ( bOldest )
//STRIP001      SetRejected();
//STRIP001  else
//STRIP001      SetState( SC_CAS_ACCEPTED );
//STRIP001
//STRIP001  return TRUE;
//STRIP001 }


// static
//STRIP001 void ScChangeActionContent::GetStringOfCell( String& rStr,
//STRIP001      const ScBaseCell* pCell, const ScDocument* pDoc, const ScAddress& rPos )
//STRIP001 {
//STRIP001  if ( pCell )
//STRIP001  {
//STRIP001      if ( ScChangeActionContent::NeedsNumberFormat( pCell ) )
//STRIP001          GetStringOfCell( rStr, pCell, pDoc, pDoc->GetNumberFormat( rPos ) );
//STRIP001      else
//STRIP001          GetStringOfCell( rStr, pCell, pDoc, 0 );
//STRIP001  }
//STRIP001  else
//STRIP001      rStr.Erase();
//STRIP001 }


// static
//STRIP001 void ScChangeActionContent::GetStringOfCell( String& rStr,
//STRIP001      const ScBaseCell* pCell, const ScDocument* pDoc, ULONG nFormat )
//STRIP001 {
//STRIP001  if ( ScChangeActionContent::GetContentCellType( pCell ) )
//STRIP001  {
//STRIP001      switch ( pCell->GetCellType() )
//STRIP001      {
//STRIP001          case CELLTYPE_VALUE :
//STRIP001          {
//STRIP001              double nValue = ((ScValueCell*)pCell)->GetValue();
//STRIP001              pDoc->GetFormatTable()->GetInputLineString( nValue, nFormat,
//STRIP001                  rStr );
//STRIP001          }
//STRIP001          break;
//STRIP001          case CELLTYPE_STRING :
//STRIP001              ((ScStringCell*)pCell)->GetString( rStr );
//STRIP001          break;
//STRIP001          case CELLTYPE_EDIT :
//STRIP001              ((ScEditCell*)pCell)->GetString( rStr );
//STRIP001          break;
//STRIP001          case CELLTYPE_FORMULA :
//STRIP001              ((ScFormulaCell*)pCell)->GetFormula( rStr );
//STRIP001          break;
//STRIP001          default:
//STRIP001              rStr.Erase();
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001      rStr.Erase();
//STRIP001 }


// static
//STRIP001 ScChangeActionContentCellType ScChangeActionContent::GetContentCellType( const ScBaseCell* pCell )
//STRIP001 {
//STRIP001  if ( pCell )
//STRIP001  {
//STRIP001      switch ( pCell->GetCellType() )
//STRIP001      {
//STRIP001          case CELLTYPE_VALUE :
//STRIP001          case CELLTYPE_STRING :
//STRIP001          case CELLTYPE_EDIT :
//STRIP001              return SC_CACCT_NORMAL;
//STRIP001          break;
//STRIP001          case CELLTYPE_FORMULA :
//STRIP001              switch ( ((const ScFormulaCell*)pCell)->GetMatrixFlag() )
//STRIP001              {
//STRIP001                  case MM_NONE :
//STRIP001                      return SC_CACCT_NORMAL;
//STRIP001                  break;
//STRIP001                  case MM_FORMULA :
//STRIP001                  case MM_FAKE :
//STRIP001                      return SC_CACCT_MATORG;
//STRIP001                  break;
//STRIP001                  case MM_REFERENCE :
//STRIP001                      return SC_CACCT_MATREF;
//STRIP001                  break;
//STRIP001              }
//STRIP001              return SC_CACCT_NORMAL;
//STRIP001          break;
//STRIP001          default:
//STRIP001              return SC_CACCT_NONE;
//STRIP001      }
//STRIP001  }
//STRIP001  return SC_CACCT_NONE;
//STRIP001 }


// static
//STRIP001 BOOL ScChangeActionContent::NeedsNumberFormat( const ScBaseCell* pCell )
//STRIP001 {
//STRIP001  return pCell && pCell->GetCellType() == CELLTYPE_VALUE;
//STRIP001 }


// static
//STRIP001 void ScChangeActionContent::SetValue( String& rStr, ScBaseCell*& pCell,
//STRIP001      const ScAddress& rPos, const ScBaseCell* pOrgCell,
//STRIP001      const ScDocument* pFromDoc, ScDocument* pToDoc )
//STRIP001 {
//STRIP001  if ( ScChangeActionContent::NeedsNumberFormat( pOrgCell ) )
//STRIP001      ScChangeActionContent::SetValue( rStr, pCell,
//STRIP001          pFromDoc->GetNumberFormat( rPos ), pOrgCell, pFromDoc, pToDoc );
//STRIP001  else
//STRIP001      ScChangeActionContent::SetValue( rStr, pCell,
//STRIP001          0, pOrgCell, pFromDoc, pToDoc );
//STRIP001 }


// static
//STRIP001 void ScChangeActionContent::SetValue( String& rStr, ScBaseCell*& pCell,
//STRIP001      ULONG nFormat, const ScBaseCell* pOrgCell,
//STRIP001      const ScDocument* pFromDoc, ScDocument* pToDoc )
//STRIP001 {
//STRIP001  rStr.Erase();
//STRIP001  if ( pCell )
//STRIP001      pCell->Delete();
//STRIP001  if ( ScChangeActionContent::GetContentCellType( pOrgCell ) )
//STRIP001  {
//STRIP001      pCell = pOrgCell->Clone( pToDoc );
//STRIP001      switch ( pOrgCell->GetCellType() )
//STRIP001      {
//STRIP001          case CELLTYPE_VALUE :
//STRIP001          {   // z.B. Datum auch als solches merken
//STRIP001              double nValue = ((ScValueCell*)pOrgCell)->GetValue();
//STRIP001              pFromDoc->GetFormatTable()->GetInputLineString( nValue,
//STRIP001                  nFormat, rStr );
//STRIP001          }
//STRIP001          break;
//STRIP001          case CELLTYPE_FORMULA :
//STRIP001              ((ScFormulaCell*)pCell)->SetInChangeTrack( TRUE );
//STRIP001          break;
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001      pCell = NULL;
//STRIP001 }


// static
//STRIP001 void ScChangeActionContent::SetCell( String& rStr, ScBaseCell* pCell,
//STRIP001      ULONG nFormat, const ScDocument* pDoc )
//STRIP001 {
//STRIP001  rStr.Erase();
//STRIP001  if ( pCell )
//STRIP001  {
//STRIP001      switch ( pCell->GetCellType() )
//STRIP001      {
//STRIP001          case CELLTYPE_VALUE :
//STRIP001          {   // e.g. remember date as date string
//STRIP001              double nValue = ((ScValueCell*)pCell)->GetValue();
//STRIP001              pDoc->GetFormatTable()->GetInputLineString( nValue,
//STRIP001                  nFormat, rStr );
//STRIP001          }
//STRIP001          break;
//STRIP001          case CELLTYPE_FORMULA :
//STRIP001              ((ScFormulaCell*)pCell)->SetInChangeTrack( TRUE );
//STRIP001          break;
//STRIP001      }
//STRIP001  }
//STRIP001 }


//STRIP001 void ScChangeActionContent::GetValueString( String& rStr,
//STRIP001      const String& rValue, const ScBaseCell* pCell ) const
//STRIP001 {
//STRIP001  if ( !rValue.Len() )
//STRIP001  {
//STRIP001      if ( pCell )
//STRIP001      {
//STRIP001          switch ( pCell->GetCellType() )
//STRIP001          {
//STRIP001              case CELLTYPE_STRING :
//STRIP001                  ((ScStringCell*)pCell)->GetString( rStr );
//STRIP001              break;
//STRIP001              case CELLTYPE_EDIT :
//STRIP001                  ((ScEditCell*)pCell)->GetString( rStr );
//STRIP001              break;
//STRIP001              case CELLTYPE_VALUE :   // ist immer in rValue
//STRIP001                  rStr = rValue;
//STRIP001              break;
//STRIP001              case CELLTYPE_FORMULA :
//STRIP001                  GetFormulaString( rStr, (ScFormulaCell*) pCell );
//STRIP001              break;
//STRIP001          }
//STRIP001      }
//STRIP001      else
//STRIP001          rStr.Erase();
//STRIP001  }
//STRIP001  else
//STRIP001      rStr = rValue;
//STRIP001 }


//STRIP001 void ScChangeActionContent::GetFormulaString( String& rStr,
//STRIP001      const ScFormulaCell* pCell ) const
//STRIP001 {
//STRIP001  ScAddress aPos( aBigRange.aStart.MakeAddress() );
//STRIP001  if ( aPos == pCell->aPos || IsDeletedIn() )
//STRIP001      pCell->GetFormula( rStr );
//STRIP001  else
//STRIP001  {
//STRIP001      DBG_ERROR( "ScChangeActionContent::GetFormulaString: aPos != pCell->aPos" );
//STRIP001      ScFormulaCell* pNew = (ScFormulaCell*) pCell->Clone(
//STRIP001          pCell->GetDocument(), aPos, TRUE );     // TRUE: bNoListening
//STRIP001      pNew->GetFormula( rStr );
//STRIP001      delete pNew;
//STRIP001  }
//STRIP001 }


//STRIP001 void ScChangeActionContent::PutOldValueToDoc( ScDocument* pDoc,
//STRIP001      short nDx, short nDy ) const
//STRIP001 {
//STRIP001  PutValueToDoc( pOldCell, aOldValue, pDoc, nDx, nDy );
//STRIP001 }


//STRIP001 void ScChangeActionContent::PutNewValueToDoc( ScDocument* pDoc,
//STRIP001      short nDx, short nDy ) const
//STRIP001 {
//STRIP001  PutValueToDoc( pNewCell, aNewValue, pDoc, nDx, nDy );
//STRIP001 }


//STRIP001 void ScChangeActionContent::PutValueToDoc( ScBaseCell* pCell,
//STRIP001      const String& rValue, ScDocument* pDoc, short nDx, short nDy ) const
//STRIP001 {
//STRIP001  ScAddress aPos( aBigRange.aStart.MakeAddress() );
//STRIP001  if ( nDx )
//STRIP001      aPos.IncCol( nDx );
//STRIP001  if ( nDy )
//STRIP001      aPos.IncRow( nDy );
//STRIP001  if ( !rValue.Len() )
//STRIP001  {
//STRIP001      if ( pCell )
//STRIP001      {
//STRIP001          switch ( pCell->GetCellType() )
//STRIP001          {
//STRIP001              case CELLTYPE_VALUE :   // ist immer in rValue
//STRIP001                  pDoc->SetString( aPos.Col(), aPos.Row(), aPos.Tab(), rValue );
//STRIP001              break;
//STRIP001              default:
//STRIP001                  switch ( ScChangeActionContent::GetContentCellType( pCell ) )
//STRIP001                  {
//STRIP001                      case SC_CACCT_MATORG :
//STRIP001                      {
//STRIP001                          USHORT nC, nR;
//STRIP001                          ((const ScFormulaCell*)pCell)->GetMatColsRows( nC, nR );
//STRIP001                          DBG_ASSERT( nC>0 && nR>0, "ScChangeActionContent::PutValueToDoc: MatColsRows?" );
//STRIP001                          ScRange aRange( aPos );
//STRIP001                          if ( nC > 1 )
//STRIP001                              aRange.aEnd.IncCol( nC-1 );
//STRIP001                          if ( nR > 1 )
//STRIP001                              aRange.aEnd.IncRow( nR-1 );
//STRIP001                          ScMarkData aDestMark;
//STRIP001                          aDestMark.SelectOneTable( aPos.Tab() );
//STRIP001                          aDestMark.SetMarkArea( aRange );
//STRIP001                          pDoc->InsertMatrixFormula( aPos.Col(), aPos.Row(),
//STRIP001                              aRange.aEnd.Col(), aRange.aEnd.Row(),
//STRIP001                              aDestMark, EMPTY_STRING,
//STRIP001                              ((const ScFormulaCell*)pCell)->GetCode() );
//STRIP001                      }
//STRIP001                      break;
//STRIP001                      case SC_CACCT_MATREF :
//STRIP001                          // nothing
//STRIP001                      break;
//STRIP001                      default:
//STRIP001                          pDoc->PutCell( aPos, pCell->Clone( pDoc ) );
//STRIP001                  }
//STRIP001          }
//STRIP001      }
//STRIP001      else
//STRIP001          pDoc->PutCell( aPos, NULL );
//STRIP001  }
//STRIP001  else
//STRIP001      pDoc->SetString( aPos.Col(), aPos.Row(), aPos.Tab(), rValue );
//STRIP001 }


//STRIP001 void lcl_InvalidateReference( ScToken& rTok, const ScBigAddress& rPos )
//STRIP001 {
//STRIP001  SingleRefData& rRef1 = rTok.GetSingleRef();
//STRIP001  if ( rPos.Col() < 0 || MAXCOL < rPos.Col() )
//STRIP001  {
//STRIP001      rRef1.nCol = (INT16)(~0);
//STRIP001      rRef1.nRelCol = (INT16)(~0);
//STRIP001      rRef1.SetColDeleted( TRUE );
//STRIP001  }
//STRIP001  if ( rPos.Row() < 0 || MAXROW < rPos.Row() )
//STRIP001  {
//STRIP001      rRef1.nRow = (INT16)(~0);
//STRIP001      rRef1.nRelRow = (INT16)(~0);
//STRIP001      rRef1.SetRowDeleted( TRUE );
//STRIP001  }
//STRIP001  if ( rPos.Tab() < 0 || MAXTAB < rPos.Tab() )
//STRIP001  {
//STRIP001      rRef1.nTab = (INT16)(~0);
//STRIP001      rRef1.nRelTab = (INT16)(~0);
//STRIP001      rRef1.SetTabDeleted( TRUE );
//STRIP001  }
//STRIP001  if ( rTok.GetType() == svDoubleRef )
//STRIP001  {
//STRIP001      SingleRefData& rRef2 = rTok.GetDoubleRef().Ref2;
//STRIP001      if ( rPos.Col() < 0 || MAXCOL < rPos.Col() )
//STRIP001      {
//STRIP001          rRef2.nCol = (INT16)(~0);
//STRIP001          rRef2.nRelCol = (INT16)(~0);
//STRIP001          rRef2.SetColDeleted( TRUE );
//STRIP001      }
//STRIP001      if ( rPos.Row() < 0 || MAXROW < rPos.Row() )
//STRIP001      {
//STRIP001          rRef2.nRow = (INT16)(~0);
//STRIP001          rRef2.nRelRow = (INT16)(~0);
//STRIP001          rRef2.SetRowDeleted( TRUE );
//STRIP001      }
//STRIP001      if ( rPos.Tab() < 0 || MAXTAB < rPos.Tab() )
//STRIP001      {
//STRIP001          rRef2.nTab = (INT16)(~0);
//STRIP001          rRef2.nRelTab = (INT16)(~0);
//STRIP001          rRef2.SetTabDeleted( TRUE );
//STRIP001      }
//STRIP001  }
//STRIP001 }


//STRIP001 void ScChangeActionContent::UpdateReference( const ScChangeTrack* pTrack,
//STRIP001      UpdateRefMode eMode, const ScBigRange& rRange,
//STRIP001      INT32 nDx, INT32 nDy, INT32 nDz )
//STRIP001 {
//STRIP001  USHORT nOldSlot = ScChangeTrack::ComputeContentSlot( aBigRange.aStart.Row() );
//STRIP001  ScRefUpdate::Update( eMode, rRange, nDx, nDy, nDz, aBigRange );
//STRIP001  USHORT nNewSlot = ScChangeTrack::ComputeContentSlot( aBigRange.aStart.Row() );
//STRIP001  if ( nNewSlot != nOldSlot )
//STRIP001  {
//STRIP001      RemoveFromSlot();
//STRIP001      InsertInSlot( &(pTrack->GetContentSlots()[nNewSlot]) );
//STRIP001  }
//STRIP001
//STRIP001  if ( pTrack->IsInDelete() && !pTrack->IsInDeleteTop() )
//STRIP001      return ;        // Formeln nur kompletten Bereich updaten
//STRIP001
//STRIP001  BOOL bOldFormula = ( pOldCell && pOldCell->GetCellType() == CELLTYPE_FORMULA );
//STRIP001  BOOL bNewFormula = ( pNewCell && pNewCell->GetCellType() == CELLTYPE_FORMULA );
//STRIP001  if ( bOldFormula || bNewFormula )
//STRIP001  {   // via ScFormulaCell UpdateReference anpassen (dort)
//STRIP001      if ( pTrack->IsInDelete() )
//STRIP001      {
//STRIP001          const ScRange& rDelRange = pTrack->GetInDeleteRange();
//STRIP001          if ( nDx > 0 )
//STRIP001              nDx = rDelRange.aEnd.Col() - rDelRange.aStart.Col() + 1;
//STRIP001          else if ( nDx < 0 )
//STRIP001              nDx = -(rDelRange.aEnd.Col() - rDelRange.aStart.Col() + 1);
//STRIP001          if ( nDy > 0 )
//STRIP001              nDy = rDelRange.aEnd.Row() - rDelRange.aStart.Row() + 1;
//STRIP001          else if ( nDy < 0 )
//STRIP001              nDy = -(rDelRange.aEnd.Row() - rDelRange.aStart.Row() + 1);
//STRIP001          if ( nDz > 0 )
//STRIP001              nDz = rDelRange.aEnd.Tab() - rDelRange.aStart.Tab() + 1;
//STRIP001          else if ( nDz < 0 )
//STRIP001              nDz = -(rDelRange.aEnd.Tab() - rDelRange.aStart.Tab() + 1);
//STRIP001      }
//STRIP001      ScBigRange aTmpRange( rRange );
//STRIP001      switch ( eMode )
//STRIP001      {
//STRIP001          case URM_INSDEL :
//STRIP001              if ( nDx < 0 || nDy < 0 || nDz < 0 )
//STRIP001              {   // Delete startet dort hinter geloeschtem Bereich,
//STRIP001                  // Position wird dort angepasst.
//STRIP001                  if ( nDx )
//STRIP001                      aTmpRange.aStart.IncCol( -nDx );
//STRIP001                  if ( nDy )
//STRIP001                      aTmpRange.aStart.IncRow( -nDy );
//STRIP001                  if ( nDz )
//STRIP001                      aTmpRange.aStart.IncTab( -nDz );
//STRIP001              }
//STRIP001          break;
//STRIP001          case URM_MOVE :
//STRIP001              // Move ist hier Quelle, dort Ziel,
//STRIP001              // Position muss vorher angepasst sein.
//STRIP001              if ( bOldFormula )
//STRIP001                  ((ScFormulaCell*)pOldCell)->aPos = aBigRange.aStart.MakeAddress();
//STRIP001              if ( bNewFormula )
//STRIP001                  ((ScFormulaCell*)pNewCell)->aPos = aBigRange.aStart.MakeAddress();
//STRIP001              if ( nDx )
//STRIP001              {
//STRIP001                  aTmpRange.aStart.IncCol( nDx );
//STRIP001                  aTmpRange.aEnd.IncCol( nDx );
//STRIP001              }
//STRIP001              if ( nDy )
//STRIP001              {
//STRIP001                  aTmpRange.aStart.IncRow( nDy );
//STRIP001                  aTmpRange.aEnd.IncRow( nDy );
//STRIP001              }
//STRIP001              if ( nDz )
//STRIP001              {
//STRIP001                  aTmpRange.aStart.IncTab( nDz );
//STRIP001                  aTmpRange.aEnd.IncTab( nDz );
//STRIP001              }
//STRIP001          break;
//STRIP001      }
//STRIP001      ScRange aRange( aTmpRange.MakeRange() );
//STRIP001      if ( bOldFormula )
//STRIP001          ((ScFormulaCell*)pOldCell)->UpdateReference( eMode, aRange,
//STRIP001              (short) nDx, (short) nDy, (short) nDz, NULL );
//STRIP001      if ( bNewFormula )
//STRIP001          ((ScFormulaCell*)pNewCell)->UpdateReference( eMode, aRange,
//STRIP001              (short) nDx, (short) nDy, (short) nDz, NULL );
//STRIP001      if ( !aBigRange.aStart.IsValid( pTrack->GetDocument() ) )
//STRIP001      {   //! HACK!
//STRIP001          //! UpdateReference kann nicht mit Positionen ausserhalb des
//STRIP001          //! Dokuments umgehen, deswegen alles auf #REF! setzen
//STRIP001 //2do: make it possible! das bedeutet grossen Umbau von ScAddress etc.!
//STRIP001          const ScBigAddress& rPos = aBigRange.aStart;
//STRIP001          if ( bOldFormula )
//STRIP001          {
//STRIP001              ScToken* t;
//STRIP001              ScTokenArray* pArr = ((ScFormulaCell*)pOldCell)->GetCode();
//STRIP001              pArr->Reset();
//STRIP001              while ( t = pArr->GetNextReference() )
//STRIP001                  lcl_InvalidateReference( *t, rPos );
//STRIP001              pArr->Reset();
//STRIP001              while ( t = pArr->GetNextReferenceRPN() )
//STRIP001                  lcl_InvalidateReference( *t, rPos );
//STRIP001          }
//STRIP001          if ( bNewFormula )
//STRIP001          {
//STRIP001              ScToken* t;
//STRIP001              ScTokenArray* pArr = ((ScFormulaCell*)pNewCell)->GetCode();
//STRIP001              pArr->Reset();
//STRIP001              while ( t = pArr->GetNextReference() )
//STRIP001                  lcl_InvalidateReference( *t, rPos );
//STRIP001              pArr->Reset();
//STRIP001              while ( t = pArr->GetNextReferenceRPN() )
//STRIP001                  lcl_InvalidateReference( *t, rPos );
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 }


// --- ScChangeActionReject ------------------------------------------------

/*N*/ ScChangeActionReject::ScChangeActionReject( SvStream& rStrm,
/*N*/           ScMultipleReadHeader& rHdr, ScChangeTrack* pTrack )
/*N*/       :
/*N*/       ScChangeAction( rStrm, rHdr, pTrack )
/*N*/ {     DBG_ASSERT(0, "STRIP"); //STRIP001
/*N*/ }

/*N*/ ScChangeActionReject::ScChangeActionReject(const ULONG nActionNumber, const ScChangeActionState eState, const ULONG nRejectingNumber,
/*N*/                                               const ScBigRange& aBigRange, const String& aUser, const DateTime& aDateTime, const String& sComment)
/*N*/       :
/*N*/       ScChangeAction(SC_CAT_CONTENT, aBigRange, nActionNumber, nRejectingNumber, eState, aDateTime, aUser, sComment)
/*N*/ { DBG_ASSERT(0, "STRIP"); //STRIP001
/*N*/ }

//STRIP001 BOOL ScChangeActionReject::Store( SvStream& rStrm, ScMultipleWriteHeader& rHdr ) const
//STRIP001 {
//STRIP001  BOOL bOk = ScChangeAction::Store( rStrm, rHdr );
//STRIP001  return TRUE;
//STRIP001 }


// --- ScChangeTrack -------------------------------------------------------

/*N*/ IMPL_FIXEDMEMPOOL_NEWDEL( ScChangeTrackMsgInfo, 16, 16 )//STRIP008 ;

const USHORT ScChangeTrack::nContentRowsPerSlot = InitContentRowsPerSlot();
const USHORT ScChangeTrack::nContentSlots =
    (MAXROW+1) / InitContentRowsPerSlot() + 2;

// static
/*N*/ USHORT ScChangeTrack::InitContentRowsPerSlot()
/*N*/ {
/*N*/   const USHORT nMaxSlots = 0xffe0 / sizeof( ScChangeActionContent* ) - 2;
/*N*/   USHORT nRowsPerSlot = (MAXROW+1) / nMaxSlots;
/*N*/   if ( nRowsPerSlot * nMaxSlots < (MAXROW+1) )
/*N*/       ++nRowsPerSlot;
/*N*/   return nRowsPerSlot;
/*N*/ }


//STRIP001 ScChangeTrack::ScChangeTrack( ScDocument* pDocP ) :
//STRIP001      pDoc( pDocP )
//STRIP001 {
//STRIP001 Init();
//STRIP001  StartListening( *SfxGetpApp() );
//STRIP001  ppContentSlots = new ScChangeActionContent* [ nContentSlots ];
//STRIP001  memset( ppContentSlots, 0, nContentSlots * sizeof( ScChangeActionContent* ) );
//STRIP001 }

//STRIP001 ScChangeTrack::ScChangeTrack( ScDocument* pDocP, const StrCollection& aTempUserCollection) :
//STRIP001      pDoc( pDocP ),
//STRIP001      aUserCollection(aTempUserCollection)
//STRIP001 {
//STRIP001 Init();
//STRIP001  StartListening( *SfxGetpApp() );
//STRIP001  ppContentSlots = new ScChangeActionContent* [ nContentSlots ];
//STRIP001  memset( ppContentSlots, 0, nContentSlots * sizeof( ScChangeActionContent* ) );
//STRIP001 }

//STRIP001 ScChangeTrack::~ScChangeTrack()
//STRIP001 {
//STRIP001  DtorClear();
//STRIP001  delete [] ppContentSlots;
//STRIP001 }


//STRIP001 void ScChangeTrack::Init()
//STRIP001 {
//STRIP001  pFirst = NULL;
//STRIP001  pLast = NULL;
//STRIP001  pFirstGeneratedDelContent = NULL;
//STRIP001  pLastCutMove = NULL;
//STRIP001  pLinkInsertCol = NULL;
//STRIP001  pLinkInsertRow = NULL;
//STRIP001  pLinkInsertTab = NULL;
//STRIP001  pLinkMove = NULL;
//STRIP001  pBlockModifyMsg = NULL;
//STRIP001  nActionMax = 0;
//STRIP001  nGeneratedMin = SC_CHGTRACK_GENERATED_START;
//STRIP001  nMarkLastSaved = 0;
//STRIP001  nStartLastCut = 0;
//STRIP001  nEndLastCut = 0;
//STRIP001  nLastMerge = 0;
//STRIP001  eMergeState = SC_CTMS_NONE;
//STRIP001  nLoadedFileFormatVersion = SC_CHGTRACK_FILEFORMAT;
//STRIP001  bLoadSave = FALSE;
//STRIP001  bInDelete = FALSE;
//STRIP001  bInDeleteTop = FALSE;
//STRIP001  bInDeleteUndo = FALSE;
//STRIP001  bInPasteCut = FALSE;
//STRIP001  bUseFixDateTime = FALSE;
//STRIP001     bTime100thSeconds = TRUE;
//STRIP001
//STRIP001  SvtUserOptions aUserOpt;
//STRIP001  aUser = aUserOpt.GetFirstName();
//STRIP001  aUser += ' ';
//STRIP001  aUser += aUserOpt.GetLastName();
//STRIP001  aUserCollection.Insert( new StrData( aUser ) );
//STRIP001 }


//STRIP001 void ScChangeTrack::DtorClear()
//STRIP001 {
//STRIP001  ScChangeAction* p;
//STRIP001  ScChangeAction* pNext;
//STRIP001  for ( p = GetFirst(); p; p = pNext )
//STRIP001  {
//STRIP001      pNext = p->GetNext();
//STRIP001      delete p;
//STRIP001  }
//STRIP001  for ( p = pFirstGeneratedDelContent; p; p = pNext )
//STRIP001  {
//STRIP001      pNext = p->GetNext();
//STRIP001      delete p;
//STRIP001  }
//STRIP001  for ( p = aPasteCutTable.First(); p; p = aPasteCutTable.Next() )
//STRIP001  {
//STRIP001      delete p;
//STRIP001  }
//STRIP001  delete pLastCutMove;
//STRIP001  ClearMsgQueue();
//STRIP001 }


//STRIP001 void ScChangeTrack::ClearMsgQueue()
//STRIP001 {
//STRIP001  if ( pBlockModifyMsg )
//STRIP001  {
//STRIP001      delete pBlockModifyMsg;
//STRIP001      pBlockModifyMsg = NULL;
//STRIP001  }
//STRIP001  ScChangeTrackMsgInfo* pMsgInfo;
//STRIP001  while ( pMsgInfo = aMsgStackTmp.Pop() )
//STRIP001      delete pMsgInfo;
//STRIP001  while ( pMsgInfo = aMsgStackFinal.Pop() )
//STRIP001      delete pMsgInfo;
//STRIP001  while ( pMsgInfo = aMsgQueue.Get() )
//STRIP001      delete pMsgInfo;
//STRIP001 }


//STRIP001 void ScChangeTrack::Clear()
//STRIP001 {
//STRIP001  DtorClear();
//STRIP001  aTable.Clear();
//STRIP001  aGeneratedTable.Clear();
//STRIP001  aPasteCutTable.Clear();
//STRIP001  aUserCollection.FreeAll();
//STRIP001  aUser.Erase();
//STRIP001  Init();
//STRIP001 }


//STRIP001 void __EXPORT ScChangeTrack::Notify( SfxBroadcaster& rBC, const SfxHint& rHint )
//STRIP001 {
//STRIP001  if ( !pDoc->IsInDtorClear() )
//STRIP001  {
//STRIP001      const SfxItemSetHint* pHint = PTR_CAST( SfxItemSetHint, &rHint );
//STRIP001      if ( pHint )
//STRIP001      {
//STRIP001          const SfxItemSet& rSet = pHint->GetItemSet();
//STRIP001          const SfxPoolItem* pItem;
//STRIP001          if ( rSet.GetItemState(
//STRIP001                  rSet.GetPool()->GetWhich( SID_ATTR_ADDRESS ),
//STRIP001                  TRUE, &pItem ) == SFX_ITEM_SET )
//STRIP001          {
//STRIP001              USHORT nOldCount = aUserCollection.GetCount();
//STRIP001
//STRIP001              String aStr( ((SvxAddressItem*)pItem)->GetFirstName() );
//STRIP001              aStr += ' ';
//STRIP001              aStr += ((SvxAddressItem*)pItem)->GetName();
//STRIP001              SetUser( aStr );
//STRIP001
//STRIP001              if ( aUserCollection.GetCount() != nOldCount )
//STRIP001              {
//STRIP001                  //  New user in collection -> have to repaint because
//STRIP001                  //  colors may be different now (#106697#).
//STRIP001                  //  (Has to be done in the Notify handler, to be sure
//STRIP001                  //  the user collection has already been updated)
//STRIP001
//STRIP001                  SfxObjectShell* pDocSh = pDoc->GetDocumentShell();
//STRIP001                  if (pDocSh)
//STRIP001                      pDocSh->Broadcast( ScPaintHint( ScRange(0,0,0,MAXCOL,MAXROW,MAXTAB), PAINT_GRID ) );
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 }


//STRIP001 void ScChangeTrack::SetUser( const String& rUser )
//STRIP001 {
//STRIP001  if ( IsLoadSave() )
//STRIP001      return ;        // nicht die Collection zerschiessen
//STRIP001
//STRIP001  aUser = rUser;
//STRIP001  StrData* pStrData = new StrData( aUser );
//STRIP001  if ( !aUserCollection.Insert( pStrData ) )
//STRIP001      delete pStrData;
//STRIP001 }


//STRIP001 void ScChangeTrack::StartBlockModify( ScChangeTrackMsgType eMsgType,
//STRIP001      ULONG nStartAction )
//STRIP001 {
//STRIP001  if ( aModifiedLink.IsSet() )
//STRIP001  {
//STRIP001      if ( pBlockModifyMsg )
//STRIP001          aMsgStackTmp.Push( pBlockModifyMsg );   // Block im Block
//STRIP001      pBlockModifyMsg = new ScChangeTrackMsgInfo;
//STRIP001      pBlockModifyMsg->eMsgType = eMsgType;
//STRIP001      pBlockModifyMsg->nStartAction = nStartAction;
//STRIP001  }
//STRIP001 }


//STRIP001 void ScChangeTrack::EndBlockModify( ULONG nEndAction )
//STRIP001 {
//STRIP001  if ( aModifiedLink.IsSet() )
//STRIP001  {
//STRIP001      if ( pBlockModifyMsg )
//STRIP001      {
//STRIP001          if ( pBlockModifyMsg->nStartAction <= nEndAction )
//STRIP001          {
//STRIP001              pBlockModifyMsg->nEndAction = nEndAction;
//STRIP001              // Blocks in Blocks aufgeloest
//STRIP001              aMsgStackFinal.Push( pBlockModifyMsg );
//STRIP001          }
//STRIP001          else
//STRIP001              delete pBlockModifyMsg;
//STRIP001          pBlockModifyMsg = aMsgStackTmp.Pop();   // evtl. Block im Block
//STRIP001      }
//STRIP001      if ( !pBlockModifyMsg )
//STRIP001      {
//STRIP001          BOOL bNew = FALSE;
//STRIP001          ScChangeTrackMsgInfo* pMsg;
//STRIP001          while ( pMsg = aMsgStackFinal.Pop() )
//STRIP001          {
//STRIP001              aMsgQueue.Put( pMsg );
//STRIP001              bNew = TRUE;
//STRIP001          }
//STRIP001          if ( bNew )
//STRIP001              aModifiedLink.Call( this );
//STRIP001      }
//STRIP001  }
//STRIP001 }


//STRIP001 void ScChangeTrack::NotifyModified( ScChangeTrackMsgType eMsgType,
//STRIP001      ULONG nStartAction, ULONG nEndAction )
//STRIP001 {
//STRIP001  if ( aModifiedLink.IsSet() )
//STRIP001  {
//STRIP001      if ( !pBlockModifyMsg || pBlockModifyMsg->eMsgType != eMsgType ||
//STRIP001              (IsGenerated( nStartAction ) &&
//STRIP001              (eMsgType == SC_CTM_APPEND || eMsgType == SC_CTM_REMOVE)) )
//STRIP001      {   // Append innerhalb von Append z.B. nicht
//STRIP001          StartBlockModify( eMsgType, nStartAction );
//STRIP001          EndBlockModify( nEndAction );
//STRIP001      }
//STRIP001  }
//STRIP001 }


//STRIP001 void lcl_EnsureSorting( StrCollection& rCollection )
//STRIP001 {
//STRIP001  BOOL bSorted = TRUE;
//STRIP001  USHORT nCount = rCollection.GetCount();
//STRIP001  USHORT i;
//STRIP001  for (i=0; i+1<nCount; i++)
//STRIP001      if ( rCollection.Compare( rCollection[i], rCollection[i+1] ) != -1 )
//STRIP001          bSorted = FALSE;
//STRIP001
//STRIP001  if ( !bSorted )
//STRIP001  {
//STRIP001      //  if not sorted, rebuild collection
//STRIP001      StrCollection aNewColl;
//STRIP001      for (i=0; i<nCount; i++)
//STRIP001      {
//STRIP001          DataObject* pNewObj = rCollection[i]->Clone();
//STRIP001          if (!aNewColl.Insert(pNewObj))
//STRIP001              delete pNewObj;
//STRIP001      }
//STRIP001      rCollection = aNewColl;
//STRIP001  }
//STRIP001 }


//STRIP001 BOOL ScChangeTrack::Load( SvStream& rStrm, USHORT nVer )
//STRIP001 {
//STRIP001  BOOL bOk = TRUE;
//STRIP001  SetLoadSave( TRUE );
//STRIP001
//STRIP001  ScReadHeader aGlobalHdr( rStrm );
//STRIP001
//STRIP001  BYTE n8;
//STRIP001  UINT16 n16;
//STRIP001  UINT32 n32;
//STRIP001
//STRIP001  rStrm >> n16; nLoadedFileFormatVersion = n16;
//STRIP001  if ( (nLoadedFileFormatVersion & 0xFF00) > (SC_CHGTRACK_FILEFORMAT & 0xFF00) )
//STRIP001  {   // inkompatible neuere Version
//STRIP001      Clear();
//STRIP001      rStrm.SetError( SCWARN_IMPORT_INFOLOST );
//STRIP001      return FALSE;
//STRIP001  }
//STRIP001
//STRIP001  aUserCollection.Load( rStrm );
//STRIP001
//STRIP001  ULONG nCount, nLastAction, nGeneratedCount;
//STRIP001  rStrm >> n32; nCount = n32;
//STRIP001  rStrm >> n32; nActionMax = n32;
//STRIP001  rStrm >> n32; nLastAction = n32;
//STRIP001
//STRIP001  rStrm >> n32; nGeneratedCount = n32;
//STRIP001
//STRIP001  // GeneratedDelContents laden
//STRIP001  {
//STRIP001      ScMultipleReadHeader aHdr( rStrm );
//STRIP001      for ( ULONG j = 0; j < nGeneratedCount && bOk; j++ )
//STRIP001      {
//STRIP001          ScChangeActionContent* pAct;
//STRIP001
//STRIP001          aHdr.StartEntry();
//STRIP001
//STRIP001          ScChangeActionType eType;
//STRIP001          rStrm >> n8; eType = (ScChangeActionType) n8;
//STRIP001
//STRIP001          switch ( eType )
//STRIP001          {
//STRIP001              case SC_CAT_CONTENT :
//STRIP001                  pAct = new ScChangeActionContent( rStrm, aHdr, pDoc, nVer, this );
//STRIP001              break;
//STRIP001              default:
//STRIP001                  DBG_ERROR( "ScChangeTrack::Load: unknown GeneratedType" );
//STRIP001                  pAct = NULL;
//STRIP001                  bOk = FALSE;
//STRIP001          }
//STRIP001
//STRIP001          aHdr.EndEntry();
//STRIP001
//STRIP001          if ( pAct )
//STRIP001          {
//STRIP001              pAct->SetType( eType );
//STRIP001              if ( pFirstGeneratedDelContent )
//STRIP001                  pFirstGeneratedDelContent->pPrev = pAct;
//STRIP001              pAct->pNext = pFirstGeneratedDelContent;
//STRIP001              pFirstGeneratedDelContent = pAct;
//STRIP001              aGeneratedTable.Insert( pAct->GetActionNumber(), pAct );
//STRIP001          }
//STRIP001      }
//STRIP001      rStrm >> n32; nGeneratedMin = n32;
//STRIP001  }
//STRIP001
//STRIP001  if ( bOk )
//STRIP001      bOk = ( nGeneratedCount == aGeneratedTable.Count() );
//STRIP001  DBG_ASSERT( bOk, "ScChangeTrack::Load: Generated failed" );
//STRIP001
//STRIP001
//STRIP001  // erste Runde: Actions laden
//STRIP001  {
//STRIP001      ScMultipleReadHeader aHdr( rStrm );
//STRIP001      for ( ULONG j = 0; j < nCount && bOk; j++ )
//STRIP001      {
//STRIP001          ScChangeAction* pAct;
//STRIP001
//STRIP001          aHdr.StartEntry();
//STRIP001
//STRIP001          USHORT nUserIndex;
//STRIP001          rStrm >> n16; nUserIndex = n16;
//STRIP001
//STRIP001          ScChangeActionType eType;
//STRIP001          rStrm >> n8; eType = (ScChangeActionType) n8;
//STRIP001
//STRIP001          switch ( eType )
//STRIP001          {
//STRIP001              case SC_CAT_INSERT_COLS :
//STRIP001              case SC_CAT_INSERT_ROWS :
//STRIP001              case SC_CAT_INSERT_TABS :
//STRIP001                  pAct = new ScChangeActionIns( rStrm, aHdr, this );
//STRIP001              break;
//STRIP001              case SC_CAT_DELETE_COLS :
//STRIP001              case SC_CAT_DELETE_ROWS :
//STRIP001              case SC_CAT_DELETE_TABS :
//STRIP001                  pAct = new ScChangeActionDel( rStrm, aHdr, pDoc, nVer, this );
//STRIP001              break;
//STRIP001              case SC_CAT_MOVE :
//STRIP001                  pAct = new ScChangeActionMove( rStrm, aHdr, this );
//STRIP001              break;
//STRIP001              case SC_CAT_CONTENT :
//STRIP001                  pAct = new ScChangeActionContent( rStrm, aHdr, pDoc, nVer, this );
//STRIP001              break;
//STRIP001              case SC_CAT_REJECT :
//STRIP001                  pAct = new ScChangeActionReject( rStrm, aHdr, this );
//STRIP001              break;
//STRIP001              default:
//STRIP001                  DBG_ERROR( "ScChangeTrack::Load: unknown ScChangeActionType" );
//STRIP001                  pAct = NULL;
//STRIP001                  bOk = FALSE;
//STRIP001          }
//STRIP001
//STRIP001          aHdr.EndEntry();
//STRIP001
//STRIP001          if ( pAct )
//STRIP001          {
//STRIP001              pAct->SetType( eType );
//STRIP001              if ( nUserIndex != 0xffff )
//STRIP001              {
//STRIP001                  StrData* pUser = (StrData*) aUserCollection.At( nUserIndex );
//STRIP001                  if ( pUser )
//STRIP001                      pAct->SetUser( pUser->GetString() );
//STRIP001              }
//STRIP001              AppendLoaded( pAct );
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if ( pLast )
//STRIP001      nMarkLastSaved = pLast->GetActionNumber();
//STRIP001
//STRIP001  if ( bOk )
//STRIP001      bOk = ( nMarkLastSaved == nLastAction && nCount == aTable.Count() );
//STRIP001  DBG_ASSERT( bOk, "ScChangeTrack::Load: failed" );
//STRIP001
//STRIP001  // zweite Runde: Links laden und alles verpointern
//STRIP001  {
//STRIP001      ScMultipleReadHeader aHdr( rStrm );
//STRIP001      for ( ScChangeAction* p = GetFirst(); p && bOk; p = p->GetNext() )
//STRIP001      {
//STRIP001          aHdr.StartEntry();
//STRIP001          bOk = p->LoadLinks( rStrm, this );
//STRIP001          aHdr.EndEntry();
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  SetLoadSave( FALSE );
//STRIP001
//STRIP001  // versions between 583 and 633 had the sorting wrong -> correct (after loading the actions)
//STRIP001  lcl_EnsureSorting( aUserCollection );
//STRIP001
//STRIP001  // den aktuellen User erst einfuegen, wenn die Actions bereits ihre User haben
//STRIP001  SetUser( aUser );
//STRIP001
//STRIP001  if ( !bOk )
//STRIP001  {
//STRIP001      Clear();        // eindeutiger Zustand
//STRIP001      rStrm.SetError( SCWARN_IMPORT_INFOLOST );
//STRIP001  }
//STRIP001
//STRIP001  return bOk;
//STRIP001 }


//STRIP001 BOOL ScChangeTrack::Store( SvStream& rStrm )
//STRIP001 {
//STRIP001  BOOL bOk = TRUE;
//STRIP001  SetLoadSave( TRUE );
//STRIP001
//STRIP001  ScWriteHeader aGlobalHdr( rStrm );
//STRIP001
//STRIP001  rStrm << (UINT16) SC_CHGTRACK_FILEFORMAT;
//STRIP001
//STRIP001  aUserCollection.Store( rStrm );
//STRIP001
//STRIP001  ULONG nCount = aTable.Count();
//STRIP001  ULONG nLastAction = ( pLast ? pLast->GetActionNumber() : 0 );
//STRIP001  ULONG nGeneratedCount = aGeneratedTable.Count();
//STRIP001  rStrm << (UINT32) nCount << (UINT32) nActionMax << (UINT32) nLastAction;
//STRIP001  rStrm << (UINT32) nGeneratedCount;
//STRIP001
//STRIP001  // GeneratedDelContents speichern
//STRIP001  ULONG nSave = 0;
//STRIP001  {
//STRIP001      ScMultipleWriteHeader aHdr( rStrm );
//STRIP001      ULONG nNewGeneratedMin = SC_CHGTRACK_GENERATED_START;
//STRIP001      for ( ScChangeAction* p = pFirstGeneratedDelContent; p && bOk;
//STRIP001              p = p->GetNext() )
//STRIP001      {
//STRIP001          ++nSave;
//STRIP001          aHdr.StartEntry();
//STRIP001          rStrm << (BYTE) p->GetType();
//STRIP001          bOk = p->Store( rStrm, aHdr );
//STRIP001          aHdr.EndEntry();
//STRIP001          ULONG nAct = p->GetActionNumber();
//STRIP001          if ( nNewGeneratedMin > nAct )
//STRIP001              nNewGeneratedMin = nAct;
//STRIP001      }
//STRIP001      nGeneratedMin = nNewGeneratedMin;   // evtl. unbenutzten Bereich freigeben
//STRIP001      rStrm << (UINT32) nGeneratedMin;
//STRIP001  }
//STRIP001
//STRIP001  if ( bOk )
//STRIP001      bOk = ( nGeneratedCount == nSave );
//STRIP001  DBG_ASSERT( bOk, "ScChangeTrack::Store: failed" );
//STRIP001
//STRIP001  // erste Runde: Actions speichern
//STRIP001  nSave = 0;
//STRIP001  {
//STRIP001      ScMultipleWriteHeader aHdr( rStrm );
//STRIP001      StrData* pUserSearch = new StrData( aUser );
//STRIP001      USHORT nUserIndex;
//STRIP001      for ( ScChangeAction* p = GetFirst(); p && bOk; p = p->GetNext() )
//STRIP001      {
//STRIP001          ++nSave;
//STRIP001          aHdr.StartEntry();
//STRIP001
//STRIP001          pUserSearch->SetString( p->GetUser() );
//STRIP001          if ( aUserCollection.Search( pUserSearch, nUserIndex ) )
//STRIP001              rStrm << (UINT16) nUserIndex;
//STRIP001          else
//STRIP001              rStrm << (UINT16) 0xffff;
//STRIP001          rStrm << (BYTE) p->GetType();
//STRIP001
//STRIP001          bOk = p->Store( rStrm, aHdr );
//STRIP001
//STRIP001          aHdr.EndEntry();
//STRIP001      }
//STRIP001      delete pUserSearch;
//STRIP001  }
//STRIP001
//STRIP001  if ( pLast )
//STRIP001      nMarkLastSaved = pLast->GetActionNumber();
//STRIP001
//STRIP001  if ( bOk )
//STRIP001      bOk = ( nCount == nSave );
//STRIP001  DBG_ASSERT( bOk, "ScChangeTrack::Store: failed" );
//STRIP001
//STRIP001  // zweite Runde: Links speichern
//STRIP001  {
//STRIP001      ScMultipleWriteHeader aHdr( rStrm );
//STRIP001      for ( ScChangeAction* p = GetFirst(); p && bOk; p = p->GetNext() )
//STRIP001      {
//STRIP001          aHdr.StartEntry();
//STRIP001          bOk = p->StoreLinks( rStrm );
//STRIP001          aHdr.EndEntry();
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  SetLoadSave( FALSE );
//STRIP001  return bOk;
//STRIP001 }


//STRIP001 void ScChangeTrack::MasterLinks( ScChangeAction* pAppend )
//STRIP001 {
//STRIP001  ScChangeActionType eType = pAppend->GetType();
//STRIP001
//STRIP001  if ( eType == SC_CAT_CONTENT )
//STRIP001  {
//STRIP001      if ( !IsGenerated( pAppend->GetActionNumber() ) )
//STRIP001      {
//STRIP001          USHORT nSlot = ComputeContentSlot(
//STRIP001              pAppend->GetBigRange().aStart.Row() );
//STRIP001          ((ScChangeActionContent*)pAppend)->InsertInSlot(
//STRIP001              &ppContentSlots[nSlot] );
//STRIP001      }
//STRIP001      return ;
//STRIP001  }
//STRIP001
//STRIP001  if ( pAppend->IsRejecting() )
//STRIP001      return ;        // Rejects haben keine Abhaengigkeiten
//STRIP001
//STRIP001  switch ( eType )
//STRIP001  {
//STRIP001      case SC_CAT_INSERT_COLS :
//STRIP001      {
//STRIP001          ScChangeActionLinkEntry* pLink = new ScChangeActionLinkEntry(
//STRIP001              &pLinkInsertCol, pAppend );
//STRIP001          pAppend->AddLink( NULL, pLink );
//STRIP001      }
//STRIP001      break;
//STRIP001      case SC_CAT_INSERT_ROWS :
//STRIP001      {
//STRIP001          ScChangeActionLinkEntry* pLink = new ScChangeActionLinkEntry(
//STRIP001              &pLinkInsertRow, pAppend );
//STRIP001          pAppend->AddLink( NULL, pLink );
//STRIP001      }
//STRIP001      break;
//STRIP001      case SC_CAT_INSERT_TABS :
//STRIP001      {
//STRIP001          ScChangeActionLinkEntry* pLink = new ScChangeActionLinkEntry(
//STRIP001              &pLinkInsertTab, pAppend );
//STRIP001          pAppend->AddLink( NULL, pLink );
//STRIP001      }
//STRIP001      break;
//STRIP001      case SC_CAT_MOVE :
//STRIP001      {
//STRIP001          ScChangeActionLinkEntry* pLink = new ScChangeActionLinkEntry(
//STRIP001              &pLinkMove, pAppend );
//STRIP001          pAppend->AddLink( NULL, pLink );
//STRIP001      }
//STRIP001      break;
//STRIP001  }
//STRIP001 }


/*N*/ void ScChangeTrack::AppendLoaded( ScChangeAction* pAppend )
/*N*/ {
DBG_ASSERT(0, "STRIP"); //STRIP001  aTable.Insert( pAppend->GetActionNumber(), pAppend );
//STRIP001  if ( !pLast )
//STRIP001      pFirst = pLast = pAppend;
//STRIP001  else
//STRIP001  {
//STRIP001      pLast->pNext = pAppend;
//STRIP001      pAppend->pPrev = pLast;
//STRIP001      pLast = pAppend;
//STRIP001  }
//STRIP001  MasterLinks( pAppend );
/*N*/ }


//STRIP001 void ScChangeTrack::Append( ScChangeAction* pAppend, ULONG nAction )
//STRIP001 {
//STRIP001  if ( nActionMax < nAction )
//STRIP001      nActionMax = nAction;
//STRIP001  pAppend->SetUser( aUser );
//STRIP001  if ( bUseFixDateTime )
//STRIP001      pAppend->SetDateTimeUTC( aFixDateTime );
//STRIP001  pAppend->SetActionNumber( nAction );
//STRIP001  aTable.Insert( nAction, pAppend );
//STRIP001  // UpdateReference Inserts vor Dependencies.
//STRIP001  // Delete rejectendes Insert hatte UpdateReference mit Delete-Undo.
//STRIP001  // UpdateReference auch wenn pLast==NULL, weil pAppend ein Delete sein
//STRIP001  // kann, dass DelContents generiert haben kann
//STRIP001  if ( pAppend->IsInsertType() && !pAppend->IsRejecting() )
//STRIP001      UpdateReference( pAppend, FALSE );
//STRIP001  if ( !pLast )
//STRIP001      pFirst = pLast = pAppend;
//STRIP001  else
//STRIP001  {
//STRIP001      pLast->pNext = pAppend;
//STRIP001      pAppend->pPrev = pLast;
//STRIP001      pLast = pAppend;
//STRIP001      Dependencies( pAppend );
//STRIP001  }
//STRIP001  // UpdateReference Inserts nicht nach Dependencies.
//STRIP001  // Move rejectendes Move hatte UpdateReference mit Move-Undo, Inhalt in
//STRIP001  // ToRange nicht deleten.
//STRIP001  if ( !pAppend->IsInsertType() &&
//STRIP001          !(pAppend->GetType() == SC_CAT_MOVE && pAppend->IsRejecting()) )
//STRIP001      UpdateReference( pAppend, FALSE );
//STRIP001  MasterLinks( pAppend );
//STRIP001
//STRIP001  if ( aModifiedLink.IsSet() )
//STRIP001  {
//STRIP001      NotifyModified( SC_CTM_APPEND, nAction, nAction );
//STRIP001      if ( pAppend->GetType() == SC_CAT_CONTENT )
//STRIP001      {
//STRIP001          ScChangeActionContent* pContent = (ScChangeActionContent*) pAppend;
//STRIP001          if ( pContent = pContent->GetPrevContent() )
//STRIP001          {
//STRIP001              ULONG nMod = pContent->GetActionNumber();
//STRIP001              NotifyModified( SC_CTM_CHANGE, nMod, nMod );
//STRIP001          }
//STRIP001      }
//STRIP001      else
//STRIP001          NotifyModified( SC_CTM_CHANGE, pFirst->GetActionNumber(),
//STRIP001              pLast->GetActionNumber() );
//STRIP001  }
//STRIP001 }


//STRIP001 void ScChangeTrack::Append( ScChangeAction* pAppend )
//STRIP001 {
//STRIP001  Append( pAppend, ++nActionMax );
//STRIP001 }


//STRIP001 void ScChangeTrack::AppendDeleteRange( const ScRange& rRange,
//STRIP001      ScDocument* pRefDoc, ULONG& nStartAction, ULONG& nEndAction, short nDz )
//STRIP001 {
//STRIP001  nStartAction = GetActionMax() + 1;
//STRIP001  AppendDeleteRange( rRange, pRefDoc, nDz, 0 );
//STRIP001  nEndAction = GetActionMax();
//STRIP001 }


//STRIP001 void ScChangeTrack::AppendDeleteRange( const ScRange& rRange,
//STRIP001      ScDocument* pRefDoc, short nDz, ULONG nRejectingInsert )
//STRIP001 {
//STRIP001  SetInDeleteRange( rRange );
//STRIP001  StartBlockModify( SC_CTM_APPEND, GetActionMax() + 1 );
//STRIP001  USHORT nCol1, nRow1, nTab1, nCol2, nRow2, nTab2;
//STRIP001  rRange.GetVars( nCol1, nRow1, nTab1, nCol2, nRow2, nTab2 );
//STRIP001  for ( USHORT nTab = nTab1; nTab <= nTab2; nTab++ )
//STRIP001  {
//STRIP001      if ( !pRefDoc || nTab < pRefDoc->GetTableCount() )
//STRIP001      {
//STRIP001          if ( nCol1 == 0 && nCol2 == MAXCOL )
//STRIP001          {   // ganze Zeilen und/oder Tabellen
//STRIP001              if ( nRow1 == 0 && nRow2 == MAXROW )
//STRIP001              {   // ganze Tabellen
//STRIP001 //2do: geht nicht auch komplette Tabelle als ganzes?
//STRIP001                  ScRange aRange( 0, 0, nTab, 0, MAXROW, nTab );
//STRIP001                  for ( USHORT nCol = nCol1; nCol <= nCol2; nCol++ )
//STRIP001                  {   // spaltenweise ist weniger als zeilenweise
//STRIP001                      aRange.aStart.SetCol( nCol );
//STRIP001                      aRange.aEnd.SetCol( nCol );
//STRIP001                      if ( nCol == nCol2 )
//STRIP001                          SetInDeleteTop( TRUE );
//STRIP001                      AppendOneDeleteRange( aRange, pRefDoc, nCol-nCol1, 0,
//STRIP001                          nTab-nTab1 + nDz, nRejectingInsert );
//STRIP001                  }
//STRIP001                  //! immer noch InDeleteTop
//STRIP001                  AppendOneDeleteRange( rRange, pRefDoc, 0, 0,
//STRIP001                      nTab-nTab1 + nDz, nRejectingInsert );
//STRIP001              }
//STRIP001              else
//STRIP001              {   // ganze Zeilen
//STRIP001                  ScRange aRange( 0, 0, nTab, MAXCOL, 0, nTab );
//STRIP001                  for ( USHORT nRow = nRow1; nRow <= nRow2; nRow++ )
//STRIP001                  {
//STRIP001                      aRange.aStart.SetRow( nRow );
//STRIP001                      aRange.aEnd.SetRow( nRow );
//STRIP001                      if ( nRow == nRow2 )
//STRIP001                          SetInDeleteTop( TRUE );
//STRIP001                      AppendOneDeleteRange( aRange, pRefDoc, 0, nRow-nRow1,
//STRIP001                          0, nRejectingInsert );
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001          else if ( nRow1 == 0 && nRow2 == MAXROW )
//STRIP001          {   // ganze Spalten
//STRIP001              ScRange aRange( 0, 0, nTab, 0, MAXROW, nTab );
//STRIP001              for ( USHORT nCol = nCol1; nCol <= nCol2; nCol++ )
//STRIP001              {
//STRIP001                  aRange.aStart.SetCol( nCol );
//STRIP001                  aRange.aEnd.SetCol( nCol );
//STRIP001                  if ( nCol == nCol2 )
//STRIP001                      SetInDeleteTop( TRUE );
//STRIP001                  AppendOneDeleteRange( aRange, pRefDoc, nCol-nCol1, 0,
//STRIP001                      0, nRejectingInsert );
//STRIP001              }
//STRIP001          }
//STRIP001          else
//STRIP001              DBG_ERROR( "ScChangeTrack::AppendDeleteRange: Block not supported!" );
//STRIP001          SetInDeleteTop( FALSE );
//STRIP001      }
//STRIP001  }
//STRIP001  EndBlockModify( GetActionMax() );
//STRIP001 }


//STRIP001 void ScChangeTrack::AppendOneDeleteRange( const ScRange& rOrgRange,
//STRIP001      ScDocument* pRefDoc, short nDx, short nDy, short nDz,
//STRIP001      ULONG nRejectingInsert )
//STRIP001 {
//STRIP001  ScRange aTrackRange( rOrgRange );
//STRIP001  if ( nDx )
//STRIP001  {
//STRIP001      aTrackRange.aStart.IncCol( -nDx );
//STRIP001      aTrackRange.aEnd.IncCol( -nDx );
//STRIP001  }
//STRIP001  if ( nDy )
//STRIP001  {
//STRIP001      aTrackRange.aStart.IncRow( -nDy );
//STRIP001      aTrackRange.aEnd.IncRow( -nDy );
//STRIP001  }
//STRIP001  if ( nDz )
//STRIP001  {
//STRIP001      aTrackRange.aStart.IncTab( -nDz );
//STRIP001      aTrackRange.aEnd.IncTab( -nDz );
//STRIP001  }
//STRIP001  ScChangeActionDel* pAct = new ScChangeActionDel( aTrackRange, nDx, nDy,
//STRIP001      this );
//STRIP001  // TabDelete keine Contents, sind in einzelnen Spalten
//STRIP001  if ( !(rOrgRange.aStart.Col() == 0 && rOrgRange.aStart.Row() == 0 &&
//STRIP001          rOrgRange.aEnd.Col() == MAXCOL && rOrgRange.aEnd.Row() == MAXROW) )
//STRIP001      LookUpContents( rOrgRange, pRefDoc, -nDx, -nDy, -nDz );
//STRIP001  if ( nRejectingInsert )
//STRIP001  {
//STRIP001      pAct->SetRejectAction( nRejectingInsert );
//STRIP001      pAct->SetState( SC_CAS_ACCEPTED );
//STRIP001  }
//STRIP001  Append( pAct );
//STRIP001 }


//STRIP001 void ScChangeTrack::LookUpContents( const ScRange& rOrgRange,
//STRIP001      ScDocument* pRefDoc, short nDx, short nDy, short nDz )
//STRIP001 {
//STRIP001  if ( pRefDoc )
//STRIP001  {
//STRIP001      ScAddress aPos;
//STRIP001      ScBigAddress aBigPos;
//STRIP001      ScCellIterator aIter( pRefDoc, rOrgRange );
//STRIP001      ScBaseCell* pCell = aIter.GetFirst();
//STRIP001      while ( pCell )
//STRIP001      {
//STRIP001          if ( ScChangeActionContent::GetContentCellType( pCell ) )
//STRIP001          {
//STRIP001              aBigPos.Set( aIter.GetCol() + nDx, aIter.GetRow() + nDy,
//STRIP001                  aIter.GetTab() + nDz );
//STRIP001              ScChangeActionContent* pContent = SearchContentAt( aBigPos, NULL );
//STRIP001              if ( !pContent )
//STRIP001              {   // nicht getrackte Contents
//STRIP001                  aPos.Set( aIter.GetCol() + nDx, aIter.GetRow() + nDy,
//STRIP001                      aIter.GetTab() + nDz );
//STRIP001                  GenerateDelContent( aPos, pCell, pRefDoc );
//STRIP001                  //! der Content wird hier _nicht_ per AddContent hinzugefuegt,
//STRIP001                  //! sondern in UpdateReference, um z.B. auch kreuzende Deletes
//STRIP001                  //! korrekt zu erfassen
//STRIP001              }
//STRIP001          }
//STRIP001          pCell = aIter.GetNext();
//STRIP001      }
//STRIP001  }
//STRIP001 }


//STRIP001 void ScChangeTrack::AppendMove( const ScRange& rFromRange,
//STRIP001      const ScRange& rToRange, ScDocument* pRefDoc )
//STRIP001 {
//STRIP001  ScChangeActionMove* pAct = new ScChangeActionMove( rFromRange, rToRange, this );
//STRIP001  LookUpContents( rToRange, pRefDoc, 0, 0, 0 );   // ueberschriebene Contents
//STRIP001  Append( pAct );
//STRIP001 }


// static
//STRIP001 BOOL ScChangeTrack::IsMatrixFormulaRangeDifferent( const ScBaseCell* pOldCell,
//STRIP001      const ScBaseCell* pNewCell )
//STRIP001 {
//STRIP001  USHORT nC1, nR1, nC2, nR2;
//STRIP001  nC1 = nR1 = nC2 = nR2 = 0;
//STRIP001  if ( pOldCell && (pOldCell->GetCellType() == CELLTYPE_FORMULA) &&
//STRIP001          ((const ScFormulaCell*)pOldCell)->GetMatrixFlag() == MM_FORMULA )
//STRIP001      ((const ScFormulaCell*)pOldCell)->GetMatColsRows( nC1, nR1 );
//STRIP001  if ( pNewCell && (pNewCell->GetCellType() == CELLTYPE_FORMULA) &&
//STRIP001          ((const ScFormulaCell*)pNewCell)->GetMatrixFlag() == MM_FORMULA )
//STRIP001      ((const ScFormulaCell*)pNewCell)->GetMatColsRows( nC1, nR1 );
//STRIP001  return nC1 != nC2 || nR1 != nR2;
//STRIP001 }


//STRIP001 void ScChangeTrack::AppendContent( const ScAddress& rPos,
//STRIP001      const String& rNewValue )
//STRIP001 {
//STRIP001  ScBaseCell* pCell = pDoc->GetCell( rPos );
//STRIP001  AppendContent( rPos, rNewValue, pCell );
//STRIP001 }


//STRIP001 void ScChangeTrack::AppendContent( const ScAddress& rPos,
//STRIP001      const String& rNewValue, ScBaseCell* pOldCell )
//STRIP001 {
//STRIP001  String aOldValue;
//STRIP001  ScChangeActionContent::GetStringOfCell( aOldValue, pOldCell, pDoc, rPos );
//STRIP001  if ( aOldValue != rNewValue ||
//STRIP001          IsMatrixFormulaRangeDifferent( pOldCell, NULL ) )
//STRIP001  {   // nur wirkliche Aenderung tracken
//STRIP001      ScRange aRange( rPos );
//STRIP001      ScChangeActionContent* pAct = new ScChangeActionContent( aRange );
//STRIP001      pAct->SetOldValue( pOldCell, pDoc, pDoc );
//STRIP001      pAct->SetNewValue( rNewValue, pDoc );
//STRIP001      Append( pAct );
//STRIP001  }
//STRIP001 }


//STRIP001 void ScChangeTrack::AppendContent( const ScAddress& rPos,
//STRIP001      const ScBaseCell* pOldCell, ULONG nOldFormat, ScDocument* pRefDoc )
//STRIP001 {
//STRIP001  if ( !pRefDoc )
//STRIP001      pRefDoc = pDoc;
//STRIP001  String aOldValue;
//STRIP001  ScChangeActionContent::GetStringOfCell( aOldValue, pOldCell, pRefDoc, nOldFormat );
//STRIP001  String aNewValue;
//STRIP001  ScBaseCell* pNewCell = pDoc->GetCell( rPos );
//STRIP001  ScChangeActionContent::GetStringOfCell( aNewValue, pNewCell, pDoc, rPos );
//STRIP001  if ( aOldValue != aNewValue ||
//STRIP001          IsMatrixFormulaRangeDifferent( pOldCell, pNewCell ) )
//STRIP001  {   // nur wirkliche Aenderung tracken
//STRIP001      ScRange aRange( rPos );
//STRIP001      ScChangeActionContent* pAct = new ScChangeActionContent( aRange );
//STRIP001      pAct->SetOldValue( pOldCell, pRefDoc, pDoc, nOldFormat );
//STRIP001      pAct->SetNewValue( pNewCell, pDoc );
//STRIP001      Append( pAct );
//STRIP001  }
//STRIP001 }


//STRIP001 void ScChangeTrack::AppendContent( const ScAddress& rPos,
//STRIP001      ScDocument* pRefDoc )
//STRIP001 {
//STRIP001  String aOldValue;
//STRIP001  ScBaseCell* pOldCell = pRefDoc->GetCell( rPos );
//STRIP001  ScChangeActionContent::GetStringOfCell( aOldValue, pOldCell, pRefDoc, rPos );
//STRIP001  String aNewValue;
//STRIP001  ScBaseCell* pNewCell = pDoc->GetCell( rPos );
//STRIP001  ScChangeActionContent::GetStringOfCell( aNewValue, pNewCell, pDoc, rPos );
//STRIP001  if ( aOldValue != aNewValue ||
//STRIP001          IsMatrixFormulaRangeDifferent( pOldCell, pNewCell ) )
//STRIP001  {   // nur wirkliche Aenderung tracken
//STRIP001      ScRange aRange( rPos );
//STRIP001      ScChangeActionContent* pAct = new ScChangeActionContent( aRange );
//STRIP001      pAct->SetOldValue( pOldCell, pRefDoc, pDoc );
//STRIP001      pAct->SetNewValue( pNewCell, pDoc );
//STRIP001      Append( pAct );
//STRIP001  }
//STRIP001 }


//STRIP001 void ScChangeTrack::AppendContent( const ScAddress& rPos,
//STRIP001      const ScBaseCell* pOldCell )
//STRIP001 {
//STRIP001  if ( ScChangeActionContent::NeedsNumberFormat( pOldCell ) )
//STRIP001      AppendContent( rPos, pOldCell, pDoc->GetNumberFormat( rPos ), pDoc );
//STRIP001  else
//STRIP001      AppendContent( rPos, pOldCell, 0, pDoc );
//STRIP001 }


//STRIP001 void ScChangeTrack::AppendContent( const ScAddress& rPos,
//STRIP001      const ScBaseCell* pOldCell, ScDocument* pRefDoc )
//STRIP001 {
//STRIP001  if ( ScChangeActionContent::NeedsNumberFormat( pOldCell ) )
//STRIP001      AppendContent( rPos, pOldCell, pRefDoc->GetNumberFormat( rPos ), pRefDoc );
//STRIP001  else
//STRIP001      AppendContent( rPos, pOldCell, 0, pRefDoc );
//STRIP001 }


//STRIP001 void ScChangeTrack::SetLastCutMoveRange( const ScRange& rRange,
//STRIP001      ScDocument* pRefDoc )
//STRIP001 {
//STRIP001  if ( pLastCutMove )
//STRIP001  {
//STRIP001      // ToRange nicht mit Deletes linken und nicht in der Groesse aendern,
//STRIP001      // eigentlich unnoetig, da ein Delete vorher in
//STRIP001      // ScViewFunc::PasteFromClip ein ResetLastCut ausloest
//STRIP001      ScBigRange& r = pLastCutMove->GetBigRange();
//STRIP001      r.aEnd.SetCol( -1 );
//STRIP001      r.aEnd.SetRow( -1 );
//STRIP001      r.aEnd.SetTab( -1 );
//STRIP001      r.aStart.SetCol( -1 - (rRange.aEnd.Col() - rRange.aStart.Col()) );
//STRIP001      r.aStart.SetRow( -1 - (rRange.aEnd.Row() - rRange.aStart.Row()) );
//STRIP001      r.aStart.SetTab( -1 - (rRange.aEnd.Tab() - rRange.aStart.Tab()) );
//STRIP001      // zu ueberschreibende Contents im FromRange
//STRIP001      LookUpContents( rRange, pRefDoc, 0, 0, 0 );
//STRIP001  }
//STRIP001 }


//STRIP001 void ScChangeTrack::AppendContentRange( const ScRange& rRange,
//STRIP001      ScDocument* pRefDoc, ULONG& nStartAction, ULONG& nEndAction,
//STRIP001      ScChangeActionClipMode eClipMode )
//STRIP001 {
//STRIP001  if ( eClipMode == SC_CACM_CUT )
//STRIP001  {
//STRIP001      ResetLastCut();
//STRIP001      pLastCutMove = new ScChangeActionMove( rRange, rRange, this );
//STRIP001      SetLastCutMoveRange( rRange, pRefDoc );
//STRIP001  }
//STRIP001  USHORT nCol1, nRow1, nTab1, nCol2, nRow2, nTab2;
//STRIP001  rRange.GetVars( nCol1, nRow1, nTab1, nCol2, nRow2, nTab2 );
//STRIP001  BOOL bDoContents;
//STRIP001  if ( eClipMode == SC_CACM_PASTE && HasLastCut() )
//STRIP001  {
//STRIP001      bDoContents = FALSE;
//STRIP001      SetInPasteCut( TRUE );
//STRIP001      // Paste und Cut abstimmen, Paste kann groesserer Range sein
//STRIP001      ScRange aRange( rRange );
//STRIP001      ScBigRange& r = pLastCutMove->GetBigRange();
//STRIP001      USHORT nTmp;
//STRIP001      if ( (nTmp = (USHORT) (r.aEnd.Col() - r.aStart.Col())) != (nCol2 - nCol1) )
//STRIP001      {
//STRIP001          aRange.aEnd.SetCol( aRange.aStart.Col() + nTmp );
//STRIP001          nCol1 += nTmp + 1;
//STRIP001          bDoContents = TRUE;
//STRIP001      }
//STRIP001      if ( (nTmp = (USHORT) (r.aEnd.Row() - r.aStart.Row())) != (nRow2 - nRow1) )
//STRIP001      {
//STRIP001          aRange.aEnd.SetRow( aRange.aStart.Row() + nTmp );
//STRIP001          nRow1 += nTmp + 1;
//STRIP001          bDoContents = TRUE;
//STRIP001      }
//STRIP001      if ( (nTmp = (USHORT) (r.aEnd.Tab() - r.aStart.Tab())) != (nTab2 - nTab1) )
//STRIP001      {
//STRIP001          aRange.aEnd.SetTab( aRange.aStart.Tab() + nTmp );
//STRIP001          nTab1 += nTmp + 1;
//STRIP001          bDoContents = TRUE;
//STRIP001      }
//STRIP001      r = aRange;
//STRIP001      Undo( nStartLastCut, nEndLastCut ); // hier werden sich die Cuts gemerkt
//STRIP001      //! StartAction erst nach Undo
//STRIP001      nStartAction = GetActionMax() + 1;
//STRIP001      StartBlockModify( SC_CTM_APPEND, nStartAction );
//STRIP001      // zu ueberschreibende Contents im ToRange
//STRIP001      LookUpContents( aRange, pRefDoc, 0, 0, 0 );
//STRIP001      pLastCutMove->SetStartLastCut( nStartLastCut );
//STRIP001      pLastCutMove->SetEndLastCut( nEndLastCut );
//STRIP001      Append( pLastCutMove );
//STRIP001      pLastCutMove = NULL;
//STRIP001      ResetLastCut();
//STRIP001      SetInPasteCut( FALSE );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      bDoContents = TRUE;
//STRIP001      nStartAction = GetActionMax() + 1;
//STRIP001      StartBlockModify( SC_CTM_APPEND, nStartAction );
//STRIP001  }
//STRIP001  if ( bDoContents )
//STRIP001  {
//STRIP001      ScAddress aPos;
//STRIP001      for ( USHORT nTab = nTab1; nTab <= nTab2; nTab++ )
//STRIP001      {
//STRIP001          aPos.SetTab( nTab );
//STRIP001          for ( USHORT nCol = nCol1; nCol <= nCol2; nCol++ )
//STRIP001          {
//STRIP001              aPos.SetCol( nCol );
//STRIP001              for ( USHORT nRow = nRow1; nRow <= nRow2; nRow++ )
//STRIP001              {
//STRIP001                  aPos.SetRow( nRow );
//STRIP001                  AppendContent( aPos, pRefDoc );
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  nEndAction = GetActionMax();
//STRIP001  EndBlockModify( nEndAction );
//STRIP001  if ( eClipMode == SC_CACM_CUT )
//STRIP001  {
//STRIP001      nStartLastCut = nStartAction;
//STRIP001      nEndLastCut = nEndAction;
//STRIP001  }
//STRIP001 }


//STRIP001 void ScChangeTrack::AppendContentsIfInRefDoc( ScDocument* pRefDoc,
//STRIP001          ULONG& nStartAction, ULONG& nEndAction )
//STRIP001 {
//STRIP001  ScDocumentIterator aIter( pRefDoc, 0, MAXTAB );
//STRIP001  if ( aIter.GetFirst() )
//STRIP001  {
//STRIP001      nStartAction = GetActionMax() + 1;
//STRIP001      StartBlockModify( SC_CTM_APPEND, nStartAction );
//STRIP001      SvNumberFormatter* pFormatter = pRefDoc->GetFormatTable();
//STRIP001      do
//STRIP001      {
//STRIP001          USHORT nCol, nRow, nTab;
//STRIP001          aIter.GetPos( nCol, nRow, nTab );
//STRIP001          ScAddress aPos( nCol, nRow, nTab );
//STRIP001          AppendContent( aPos, aIter.GetCell(),
//STRIP001              aIter.GetPattern()->GetNumberFormat( pFormatter ), pRefDoc );
//STRIP001      } while ( aIter.GetNext() );
//STRIP001      nEndAction = GetActionMax();
//STRIP001      EndBlockModify( nEndAction );
//STRIP001  }
//STRIP001  else
//STRIP001      nStartAction = nEndAction = 0;
//STRIP001 }


//STRIP001 ScChangeActionContent* ScChangeTrack::AppendContentOnTheFly(
//STRIP001      const ScAddress& rPos, ScBaseCell* pOldCell, ScBaseCell* pNewCell,
//STRIP001      ULONG nOldFormat, ULONG nNewFormat )
//STRIP001 {
//STRIP001  ScRange aRange( rPos );
//STRIP001  ScChangeActionContent* pAct = new ScChangeActionContent( aRange );
//STRIP001  pAct->SetOldNewCells( pOldCell, nOldFormat, pNewCell, nNewFormat, pDoc );
//STRIP001  Append( pAct );
//STRIP001  return pAct;
//STRIP001 }


//STRIP001 void ScChangeTrack::AppendInsert( const ScRange& rRange )
//STRIP001 {
//STRIP001  ScChangeActionIns* pAct = new ScChangeActionIns( rRange );
//STRIP001  Append( pAct );
//STRIP001 }


//STRIP001 void ScChangeTrack::DeleteCellEntries( ScChangeActionCellListEntry*& pCellList,
//STRIP001      ScChangeAction* pDeletor )
//STRIP001 {
//STRIP001  ScChangeActionCellListEntry* pE = pCellList;
//STRIP001  while ( pE )
//STRIP001  {
//STRIP001      ScChangeActionCellListEntry* pNext = pE->pNext;
//STRIP001      pE->pContent->RemoveDeletedIn( pDeletor );
//STRIP001      if ( IsGenerated( pE->pContent->GetActionNumber() ) &&
//STRIP001              !pE->pContent->IsDeletedIn() )
//STRIP001          DeleteGeneratedDelContent( pE->pContent );
//STRIP001      delete pE;
//STRIP001      pE = pNext;
//STRIP001  }
//STRIP001  pCellList = NULL;
//STRIP001 }


//STRIP001 ScChangeActionContent* ScChangeTrack::GenerateDelContent(
//STRIP001      const ScAddress& rPos, const ScBaseCell* pCell,
//STRIP001      const ScDocument* pFromDoc )
//STRIP001 {
//STRIP001  ScChangeActionContent* pContent = new ScChangeActionContent(
//STRIP001      ScRange( rPos ) );
//STRIP001  pContent->SetActionNumber( --nGeneratedMin );
//STRIP001  // nur NewValue
//STRIP001  ScChangeActionContent::SetValue( pContent->aNewValue, pContent->pNewCell,
//STRIP001      rPos, pCell, pFromDoc, pDoc );
//STRIP001  // pNextContent und pPrevContent werden nicht gesetzt
//STRIP001  if ( pFirstGeneratedDelContent )
//STRIP001  {   // vorne reinhaengen
//STRIP001      pFirstGeneratedDelContent->pPrev = pContent;
//STRIP001      pContent->pNext = pFirstGeneratedDelContent;
//STRIP001  }
//STRIP001  pFirstGeneratedDelContent = pContent;
//STRIP001  aGeneratedTable.Insert( nGeneratedMin, pContent );
//STRIP001  NotifyModified( SC_CTM_APPEND, nGeneratedMin, nGeneratedMin );
//STRIP001  return pContent;
//STRIP001 }


//STRIP001 void ScChangeTrack::DeleteGeneratedDelContent( ScChangeActionContent* pContent )
//STRIP001 {
//STRIP001  ULONG nAct = pContent->GetActionNumber();
//STRIP001  aGeneratedTable.Remove( nAct );
//STRIP001  if ( pFirstGeneratedDelContent == pContent )
//STRIP001      pFirstGeneratedDelContent = (ScChangeActionContent*) pContent->pNext;
//STRIP001  if ( pContent->pNext )
//STRIP001      pContent->pNext->pPrev = pContent->pPrev;
//STRIP001  if ( pContent->pPrev )
//STRIP001      pContent->pPrev->pNext = pContent->pNext;
//STRIP001  delete pContent;
//STRIP001  NotifyModified( SC_CTM_REMOVE, nAct, nAct );
//STRIP001  if ( nAct == nGeneratedMin )
//STRIP001      ++nGeneratedMin;        //! erst nach NotifyModified wg. IsGenerated
//STRIP001 }


//STRIP001 ScChangeActionContent* ScChangeTrack::SearchGeneratedDelContentAt(
//STRIP001      const ScBigAddress& rPos, ScChangeActionType eNotInDelType ) const
//STRIP001 {
//STRIP001  for ( ScChangeAction* p = pFirstGeneratedDelContent; p; p = p->GetNext() )
//STRIP001  {
//STRIP001      if ( p->GetType() == SC_CAT_CONTENT && p->GetBigRange().aStart == rPos
//STRIP001              && !p->IsDeletedInDelType( eNotInDelType ) )
//STRIP001      {
//STRIP001          return (ScChangeActionContent*) p;
//STRIP001      }
//STRIP001  }
//STRIP001  return NULL;
//STRIP001 }


//STRIP001 ScChangeActionContent* ScChangeTrack::SearchContentAt(
//STRIP001      const ScBigAddress& rPos, ScChangeAction* pButNotThis ) const
//STRIP001 {
//STRIP001  USHORT nSlot = ComputeContentSlot( rPos.Row() );
//STRIP001  for ( ScChangeActionContent* p = ppContentSlots[nSlot]; p;
//STRIP001          p = p->GetNextInSlot() )
//STRIP001  {
//STRIP001      if ( p != pButNotThis && !p->IsDeletedIn() &&
//STRIP001              p->GetBigRange().aStart == rPos )
//STRIP001      {
//STRIP001          ScChangeActionContent* pContent = p->GetTopContent();
//STRIP001          if ( !pContent->IsDeletedIn() )
//STRIP001              return pContent;
//STRIP001      }
//STRIP001  }
//STRIP001  return NULL;
//STRIP001 }


//STRIP001 void ScChangeTrack::AddDependentWithNotify( ScChangeAction* pParent,
//STRIP001      ScChangeAction* pDependent )
//STRIP001 {
//STRIP001  ScChangeActionLinkEntry* pLink = pParent->AddDependent( pDependent );
//STRIP001  pDependent->AddLink( pParent, pLink );
//STRIP001  if ( aModifiedLink.IsSet() )
//STRIP001  {
//STRIP001      ULONG nMod = pParent->GetActionNumber();
//STRIP001      NotifyModified( SC_CTM_PARENT, nMod, nMod );
//STRIP001  }
//STRIP001 }


//STRIP001 void ScChangeTrack::Dependencies( ScChangeAction* pAct )
//STRIP001 {
//STRIP001  // Finde die letzte Abhaengigkeit fuer jeweils Col/Row/Tab.
//STRIP001  // Content an gleicher Position verketten.
//STRIP001  // Move Abhaengigkeiten.
//STRIP001  ScChangeActionType eActType = pAct->GetType();
//STRIP001  if ( eActType == SC_CAT_REJECT ||
//STRIP001          (eActType == SC_CAT_MOVE && pAct->IsRejecting()) )
//STRIP001      return ;        // diese Rejects sind nicht abhaengig
//STRIP001
//STRIP001  if ( eActType == SC_CAT_CONTENT )
//STRIP001  {
//STRIP001      if ( !(((ScChangeActionContent*)pAct)->GetNextContent() ||
//STRIP001          ((ScChangeActionContent*)pAct)->GetPrevContent()) )
//STRIP001      {   // Contents an gleicher Position verketten
//STRIP001          ScChangeActionContent* pContent = SearchContentAt(
//STRIP001              pAct->GetBigRange().aStart, pAct );
//STRIP001          if ( pContent )
//STRIP001          {
//STRIP001              pContent->SetNextContent( (ScChangeActionContent*) pAct );
//STRIP001              ((ScChangeActionContent*)pAct)->SetPrevContent( pContent );
//STRIP001          }
//STRIP001      }
//STRIP001      const ScBaseCell* pCell = ((ScChangeActionContent*)pAct)->GetNewCell();
//STRIP001      if ( ScChangeActionContent::GetContentCellType( pCell ) == SC_CACCT_MATREF )
//STRIP001      {
//STRIP001          ScAddress aOrg;
//STRIP001          ((const ScFormulaCell*)pCell)->GetMatrixOrigin( aOrg );
//STRIP001          ScChangeActionContent* pContent = SearchContentAt( aOrg, pAct );
//STRIP001          if ( pContent && pContent->IsMatrixOrigin() )
//STRIP001          {
//STRIP001              AddDependentWithNotify( pContent, pAct );
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              DBG_ERRORFILE( "ScChangeTrack::Dependencies: MatOrg not found" );
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if ( !(pLinkInsertCol || pLinkInsertRow || pLinkInsertTab || pLinkMove) )
//STRIP001      return ;        // keine Dependencies
//STRIP001  if ( pAct->IsRejecting() )
//STRIP001      return ;        // ausser Content keine Dependencies
//STRIP001
//STRIP001  // Insert in einem entsprechenden Insert haengt davon ab, sonst muesste
//STRIP001  // der vorherige Insert gesplittet werden.
//STRIP001  // Sich kreuzende Inserts und Deletes sind nicht abhaengig.
//STRIP001  // Alles andere ist abhaengig.
//STRIP001
//STRIP001  // Der zuletzt eingelinkte Insert steht am Anfang einer Kette,
//STRIP001  // also genau richtig
//STRIP001
//STRIP001  const ScBigRange& rRange = pAct->GetBigRange();
//STRIP001  BOOL bActNoInsert = !pAct->IsInsertType();
//STRIP001  BOOL bActColDel = ( eActType == SC_CAT_DELETE_COLS );
//STRIP001  BOOL bActRowDel = ( eActType == SC_CAT_DELETE_ROWS );
//STRIP001  BOOL bActTabDel = ( eActType == SC_CAT_DELETE_TABS );
//STRIP001
//STRIP001  if ( pLinkInsertCol && (eActType == SC_CAT_INSERT_COLS ||
//STRIP001          (bActNoInsert && !bActRowDel && !bActTabDel)) )
//STRIP001  {
//STRIP001      for ( ScChangeActionLinkEntry* pL = pLinkInsertCol; pL; pL = pL->GetNext() )
//STRIP001      {
//STRIP001          ScChangeActionIns* pTest = (ScChangeActionIns*) pL->GetAction();
//STRIP001          if ( !pTest->IsRejected() &&
//STRIP001                  pTest->GetBigRange().Intersects( rRange ) )
//STRIP001          {
//STRIP001              AddDependentWithNotify( pTest, pAct );
//STRIP001              break;  // for
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  if ( pLinkInsertRow && (eActType == SC_CAT_INSERT_ROWS ||
//STRIP001          (bActNoInsert && !bActColDel && !bActTabDel)) )
//STRIP001  {
//STRIP001      for ( ScChangeActionLinkEntry* pL = pLinkInsertRow; pL; pL = pL->GetNext() )
//STRIP001      {
//STRIP001          ScChangeActionIns* pTest = (ScChangeActionIns*) pL->GetAction();
//STRIP001          if ( !pTest->IsRejected() &&
//STRIP001                  pTest->GetBigRange().Intersects( rRange ) )
//STRIP001          {
//STRIP001              AddDependentWithNotify( pTest, pAct );
//STRIP001              break;  // for
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  if ( pLinkInsertTab && (eActType == SC_CAT_INSERT_TABS ||
//STRIP001          (bActNoInsert && !bActColDel &&  !bActRowDel)) )
//STRIP001  {
//STRIP001      for ( ScChangeActionLinkEntry* pL = pLinkInsertTab; pL; pL = pL->GetNext() )
//STRIP001      {
//STRIP001          ScChangeActionIns* pTest = (ScChangeActionIns*) pL->GetAction();
//STRIP001          if ( !pTest->IsRejected() &&
//STRIP001                  pTest->GetBigRange().Intersects( rRange ) )
//STRIP001          {
//STRIP001              AddDependentWithNotify( pTest, pAct );
//STRIP001              break;  // for
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if ( pLinkMove )
//STRIP001  {
//STRIP001      if ( eActType == SC_CAT_CONTENT )
//STRIP001      {   // Content ist von FromRange abhaengig
//STRIP001          const ScBigAddress& rPos = rRange.aStart;
//STRIP001          for ( ScChangeActionLinkEntry* pL = pLinkMove; pL; pL = pL->GetNext() )
//STRIP001          {
//STRIP001              ScChangeActionMove* pTest = (ScChangeActionMove*) pL->GetAction();
//STRIP001              if ( !pTest->IsRejected() &&
//STRIP001                      pTest->GetFromRange().In( rPos ) )
//STRIP001              {
//STRIP001                  AddDependentWithNotify( pTest, pAct );
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001      else if ( eActType == SC_CAT_MOVE )
//STRIP001      {   // Move FromRange ist von ToRange abhaengig
//STRIP001          const ScBigRange& rFromRange = ((ScChangeActionMove*)pAct)->GetFromRange();
//STRIP001          for ( ScChangeActionLinkEntry* pL = pLinkMove; pL; pL = pL->GetNext() )
//STRIP001          {
//STRIP001              ScChangeActionMove* pTest = (ScChangeActionMove*) pL->GetAction();
//STRIP001              if ( !pTest->IsRejected() &&
//STRIP001                      pTest->GetBigRange().Intersects( rFromRange ) )
//STRIP001              {
//STRIP001                  AddDependentWithNotify( pTest, pAct );
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001      else
//STRIP001      {   // Inserts und Deletes sind abhaengig, sobald sie FromRange oder
//STRIP001          // ToRange kreuzen
//STRIP001          for ( ScChangeActionLinkEntry* pL = pLinkMove; pL; pL = pL->GetNext() )
//STRIP001          {
//STRIP001              ScChangeActionMove* pTest = (ScChangeActionMove*) pL->GetAction();
//STRIP001              if ( !pTest->IsRejected() &&
//STRIP001                      (pTest->GetFromRange().Intersects( rRange ) ||
//STRIP001                      pTest->GetBigRange().Intersects( rRange )) )
//STRIP001              {
//STRIP001                  AddDependentWithNotify( pTest, pAct );
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 }


//STRIP001 void ScChangeTrack::Remove( ScChangeAction* pRemove )
//STRIP001 {
//STRIP001  // aus Track ausklinken
//STRIP001  ULONG nAct = pRemove->GetActionNumber();
//STRIP001  aTable.Remove( nAct );
//STRIP001  if ( nAct == nActionMax )
//STRIP001      --nActionMax;
//STRIP001  if ( pRemove == pLast )
//STRIP001      pLast = pRemove->pPrev;
//STRIP001  if ( pRemove == pFirst )
//STRIP001      pFirst = pRemove->pNext;
//STRIP001  if ( nAct == nMarkLastSaved )
//STRIP001      nMarkLastSaved =
//STRIP001          ( pRemove->pPrev ? pRemove->pPrev->GetActionNumber() : 0 );
//STRIP001
//STRIP001  // aus der globalen Kette ausklinken
//STRIP001  if ( pRemove->pNext )
//STRIP001      pRemove->pNext->pPrev = pRemove->pPrev;
//STRIP001  if ( pRemove->pPrev )
//STRIP001      pRemove->pPrev->pNext = pRemove->pNext;
//STRIP001
//STRIP001  // Dependencies nicht loeschen, passiert on delete automatisch durch
//STRIP001  // LinkEntry, ohne Listen abzuklappern
//STRIP001
//STRIP001  if ( aModifiedLink.IsSet() )
//STRIP001  {
//STRIP001      NotifyModified( SC_CTM_REMOVE, nAct, nAct );
//STRIP001      if ( pRemove->GetType() == SC_CAT_CONTENT )
//STRIP001      {
//STRIP001          ScChangeActionContent* pContent = (ScChangeActionContent*) pRemove;
//STRIP001          if ( pContent = pContent->GetPrevContent() )
//STRIP001          {
//STRIP001              ULONG nMod = pContent->GetActionNumber();
//STRIP001              NotifyModified( SC_CTM_CHANGE, nMod, nMod );
//STRIP001          }
//STRIP001      }
//STRIP001      else if ( pLast )
//STRIP001          NotifyModified( SC_CTM_CHANGE, pFirst->GetActionNumber(),
//STRIP001              pLast->GetActionNumber() );
//STRIP001  }
//STRIP001
//STRIP001  if ( IsInPasteCut() && pRemove->GetType() == SC_CAT_CONTENT )
//STRIP001  {   //! Content wird wiederverwertet
//STRIP001      ScChangeActionContent* pContent = (ScChangeActionContent*) pRemove;
//STRIP001      pContent->RemoveAllLinks();
//STRIP001      pContent->ClearTrack();
//STRIP001      pContent->pNext = pContent->pPrev = NULL;
//STRIP001      pContent->pNextContent = pContent->pPrevContent = NULL;
//STRIP001  }
//STRIP001 }


//STRIP001 void ScChangeTrack::Undo( ULONG nStartAction, ULONG nEndAction )
//STRIP001 {
//STRIP001  if ( nStartAction == 0 )
//STRIP001      ++nStartAction;
//STRIP001  if ( nEndAction > nActionMax )
//STRIP001      nEndAction = nActionMax;
//STRIP001  if ( nEndAction && nStartAction <= nEndAction )
//STRIP001  {
//STRIP001      if ( nStartAction == nStartLastCut && nEndAction == nEndLastCut &&
//STRIP001              !IsInPasteCut() )
//STRIP001          ResetLastCut();
//STRIP001      StartBlockModify( SC_CTM_REMOVE, nStartAction );
//STRIP001      for ( ULONG j = nEndAction; j >= nStartAction; --j )
//STRIP001      {   // rueckwaerts um evtl. nActionMax zu recyclen und schnelleren
//STRIP001          // Zugriff via pLast, Deletes in richtiger Reihenfolge
//STRIP001          ScChangeAction* pAct = ( (j == nActionMax && pLast &&
//STRIP001              pLast->GetActionNumber() == j) ? pLast : GetAction( j ) );
//STRIP001          if ( pAct )
//STRIP001          {
//STRIP001              if ( pAct->IsDeleteType() )
//STRIP001              {
//STRIP001                  if ( j == nEndAction || (pAct != pLast &&
//STRIP001                          ((ScChangeActionDel*)pAct)->IsTopDelete()) )
//STRIP001                  {
//STRIP001                      SetInDeleteTop( TRUE );
//STRIP001                      SetInDeleteRange( ((ScChangeActionDel*)pAct)->
//STRIP001                          GetOverAllRange().MakeRange() );
//STRIP001                  }
//STRIP001              }
//STRIP001              UpdateReference( pAct, TRUE );
//STRIP001              SetInDeleteTop( FALSE );
//STRIP001              Remove( pAct );
//STRIP001              if ( IsInPasteCut() )
//STRIP001                  aPasteCutTable.Insert( pAct->GetActionNumber(), pAct );
//STRIP001              else
//STRIP001              {
//STRIP001                  if ( j == nStartAction && pAct->GetType() == SC_CAT_MOVE )
//STRIP001                  {
//STRIP001                      ScChangeActionMove* pMove = (ScChangeActionMove*) pAct;
//STRIP001                      ULONG nStart = pMove->GetStartLastCut();
//STRIP001                      ULONG nEnd = pMove->GetEndLastCut();
//STRIP001                      if ( nStart && nStart <= nEnd )
//STRIP001                      {   // LastCut wiederherstellen
//STRIP001                          //! Links vor Cut-Append aufloesen
//STRIP001                          pMove->RemoveAllLinks();
//STRIP001                          StartBlockModify( SC_CTM_APPEND, nStart );
//STRIP001                          for ( ULONG nCut = nStart; nCut <= nEnd; nCut++ )
//STRIP001                          {
//STRIP001                              ScChangeAction* pCut = aPasteCutTable.Remove( nCut );
//STRIP001                              if ( pCut )
//STRIP001                              {
//STRIP001                                  DBG_ASSERT( !aTable.Get( nCut ), "ScChangeTrack::Undo: nCut dup" );
//STRIP001                                  Append( pCut, nCut );
//STRIP001                              }
//STRIP001                              else
//STRIP001                                  DBG_ERROR( "ScChangeTrack::Undo: nCut not found" );
//STRIP001                          }
//STRIP001                          EndBlockModify( nEnd );
//STRIP001                          ResetLastCut();
//STRIP001                          nStartLastCut = nStart;
//STRIP001                          nEndLastCut = nEnd;
//STRIP001                          pLastCutMove = pMove;
//STRIP001                          SetLastCutMoveRange(
//STRIP001                              pMove->GetFromRange().MakeRange(), pDoc );
//STRIP001                      }
//STRIP001                      else
//STRIP001                          delete pMove;
//STRIP001                  }
//STRIP001                  else
//STRIP001                      delete pAct;
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001      EndBlockModify( nEndAction );
//STRIP001  }
//STRIP001 }


// static
//STRIP001 BOOL ScChangeTrack::MergeIgnore( const ScChangeAction& rAction, ULONG nFirstMerge )
//STRIP001 {
//STRIP001  if ( rAction.IsRejected() )
//STRIP001      return TRUE;                // da kommt noch eine passende Reject-Action
//STRIP001
//STRIP001  if ( rAction.IsRejecting() && rAction.GetRejectAction() >= nFirstMerge )
//STRIP001      return TRUE;                // da ist sie
//STRIP001
//STRIP001  return FALSE;                   // alles andere
//STRIP001 }


//STRIP001 void ScChangeTrack::MergePrepare( ScChangeAction* pFirstMerge )
//STRIP001 {
//STRIP001  SetMergeState( SC_CTMS_PREPARE );
//STRIP001  ULONG nFirstMerge = pFirstMerge->GetActionNumber();
//STRIP001  ScChangeAction* pAct = GetLast();
//STRIP001  if ( pAct )
//STRIP001  {
//STRIP001      SetLastMerge( pAct->GetActionNumber() );
//STRIP001      while ( pAct )
//STRIP001      {   // rueckwaerts, Deletes in richtiger Reihenfolge
//STRIP001          if ( !ScChangeTrack::MergeIgnore( *pAct, nFirstMerge ) )
//STRIP001          {
//STRIP001              if ( pAct->IsDeleteType() )
//STRIP001              {
//STRIP001                  if ( ((ScChangeActionDel*)pAct)->IsTopDelete() )
//STRIP001                  {
//STRIP001                      SetInDeleteTop( TRUE );
//STRIP001                      SetInDeleteRange( ((ScChangeActionDel*)pAct)->
//STRIP001                          GetOverAllRange().MakeRange() );
//STRIP001                  }
//STRIP001              }
//STRIP001              UpdateReference( pAct, TRUE );
//STRIP001              SetInDeleteTop( FALSE );
//STRIP001              pAct->DeleteCellEntries();      // sonst GPF bei Track Clear()
//STRIP001          }
//STRIP001          pAct = ( pAct == pFirstMerge ? NULL : pAct->GetPrev() );
//STRIP001      }
//STRIP001  }
//STRIP001  SetMergeState( SC_CTMS_OTHER );     //! nachfolgende per default MergeOther
//STRIP001 }


//STRIP001 void ScChangeTrack::MergeOwn( ScChangeAction* pAct, ULONG nFirstMerge )
//STRIP001 {
//STRIP001  if ( !ScChangeTrack::MergeIgnore( *pAct, nFirstMerge ) )
//STRIP001  {
//STRIP001      SetMergeState( SC_CTMS_OWN );
//STRIP001      if ( pAct->IsDeleteType() )
//STRIP001      {
//STRIP001          if ( ((ScChangeActionDel*)pAct)->IsTopDelete() )
//STRIP001          {
//STRIP001              SetInDeleteTop( TRUE );
//STRIP001              SetInDeleteRange( ((ScChangeActionDel*)pAct)->
//STRIP001                  GetOverAllRange().MakeRange() );
//STRIP001          }
//STRIP001      }
//STRIP001      UpdateReference( pAct, FALSE );
//STRIP001      SetInDeleteTop( FALSE );
//STRIP001      SetMergeState( SC_CTMS_OTHER );     //! nachfolgende per default MergeOther
//STRIP001  }
//STRIP001 }


//STRIP001 void ScChangeTrack::UpdateReference( ScChangeAction* pAct, BOOL bUndo )
//STRIP001 {
//STRIP001  ScChangeActionType eActType = pAct->GetType();
//STRIP001  if ( eActType == SC_CAT_CONTENT || eActType == SC_CAT_REJECT )
//STRIP001      return ;
//STRIP001
//STRIP001  //! Formelzellen haengen nicht im Dokument
//STRIP001  BOOL bOldAutoCalc = pDoc->GetAutoCalc();
//STRIP001  pDoc->SetAutoCalc( FALSE );
//STRIP001  BOOL bOldNoListening = pDoc->GetNoListening();
//STRIP001  pDoc->SetNoListening( TRUE );
//STRIP001  //! Formelzellen ExpandRefs synchronisiert zu denen im Dokument
//STRIP001  BOOL bOldExpandRefs = pDoc->IsExpandRefs();
//STRIP001  if ( (!bUndo && pAct->IsInsertType()) || (bUndo && pAct->IsDeleteType()) )
//STRIP001      pDoc->SetExpandRefs( SC_MOD()->GetInputOptions().GetExpandRefs() );
//STRIP001
//STRIP001  if ( pAct->IsDeleteType() )
//STRIP001  {
//STRIP001      SetInDeleteUndo( bUndo );
//STRIP001      SetInDelete( TRUE );
//STRIP001  }
//STRIP001  else if ( GetMergeState() == SC_CTMS_OWN )
//STRIP001  {
//STRIP001      // Referenzen von Formelzellen wiederherstellen,
//STRIP001      // vorheriges MergePrepare war bei einem Insert wie ein Delete
//STRIP001      if ( pAct->IsInsertType() )
//STRIP001          SetInDeleteUndo( TRUE );
//STRIP001  }
//STRIP001
//STRIP001  //! erst die generated, als waeren sie vorher getrackt worden
//STRIP001  if ( pFirstGeneratedDelContent )
//STRIP001      UpdateReference( (ScChangeAction**)&pFirstGeneratedDelContent, pAct,
//STRIP001          bUndo );
//STRIP001  UpdateReference( &pFirst, pAct, bUndo );
//STRIP001
//STRIP001  SetInDelete( FALSE );
//STRIP001  SetInDeleteUndo( FALSE );
//STRIP001
//STRIP001  pDoc->SetExpandRefs( bOldExpandRefs );
//STRIP001  pDoc->SetNoListening( bOldNoListening );
//STRIP001  pDoc->SetAutoCalc( bOldAutoCalc );
//STRIP001 }


//STRIP001 void ScChangeTrack::UpdateReference( ScChangeAction** ppFirstAction,
//STRIP001      ScChangeAction* pAct, BOOL bUndo )
//STRIP001 {
//STRIP001  ScChangeActionType eActType = pAct->GetType();
//STRIP001  BOOL bGeneratedDelContents =
//STRIP001      ( ppFirstAction == (ScChangeAction**)&pFirstGeneratedDelContent );
//STRIP001  const ScBigRange& rOrgRange = pAct->GetBigRange();
//STRIP001  ScBigRange aRange( rOrgRange );
//STRIP001  ScBigRange aDelRange( rOrgRange );
//STRIP001  INT32 nDx, nDy, nDz;
//STRIP001  nDx = nDy = nDz = 0;
//STRIP001  UpdateRefMode eMode = URM_INSDEL;
//STRIP001  BOOL bDel = FALSE;
//STRIP001  switch ( eActType )
//STRIP001  {
//STRIP001      case SC_CAT_INSERT_COLS :
//STRIP001          aRange.aEnd.SetCol( nInt32Max );
//STRIP001          nDx = rOrgRange.aEnd.Col() - rOrgRange.aStart.Col() + 1;
//STRIP001      break;
//STRIP001      case SC_CAT_INSERT_ROWS :
//STRIP001          aRange.aEnd.SetRow( nInt32Max );
//STRIP001          nDy = rOrgRange.aEnd.Row() - rOrgRange.aStart.Row() + 1;
//STRIP001      break;
//STRIP001      case SC_CAT_INSERT_TABS :
//STRIP001          aRange.aEnd.SetTab( nInt32Max );
//STRIP001          nDz = rOrgRange.aEnd.Tab() - rOrgRange.aStart.Tab() + 1;
//STRIP001      break;
//STRIP001      case SC_CAT_DELETE_COLS :
//STRIP001          aRange.aEnd.SetCol( nInt32Max );
//STRIP001          nDx = -(rOrgRange.aEnd.Col() - rOrgRange.aStart.Col() + 1);
//STRIP001          aDelRange.aEnd.SetCol( aDelRange.aStart.Col() - nDx - 1 );
//STRIP001          bDel = TRUE;
//STRIP001      break;
//STRIP001      case SC_CAT_DELETE_ROWS :
//STRIP001          aRange.aEnd.SetRow( nInt32Max );
//STRIP001          nDy = -(rOrgRange.aEnd.Row() - rOrgRange.aStart.Row() + 1);
//STRIP001          aDelRange.aEnd.SetRow( aDelRange.aStart.Row() - nDy - 1 );
//STRIP001          bDel = TRUE;
//STRIP001      break;
//STRIP001      case SC_CAT_DELETE_TABS :
//STRIP001          aRange.aEnd.SetTab( nInt32Max );
//STRIP001          nDz = -(rOrgRange.aEnd.Tab() - rOrgRange.aStart.Tab() + 1);
//STRIP001          aDelRange.aEnd.SetTab( aDelRange.aStart.Tab() - nDz - 1 );
//STRIP001          bDel = TRUE;
//STRIP001      break;
//STRIP001      case SC_CAT_MOVE :
//STRIP001          eMode = URM_MOVE;
//STRIP001          ((ScChangeActionMove*)pAct)->GetDelta( nDx, nDy, nDz );
//STRIP001      break;
//STRIP001      default:
//STRIP001          DBG_ERROR( "ScChangeTrack::UpdateReference: unknown Type" );
//STRIP001  }
//STRIP001  if ( bUndo )
//STRIP001  {
//STRIP001      nDx = -nDx;
//STRIP001      nDy = -nDy;
//STRIP001      nDz = -nDz;
//STRIP001  }
//STRIP001  if ( bDel )
//STRIP001  {   //! fuer diesen Mechanismus gilt:
//STRIP001      //! es gibt nur ganze, einfache geloeschte Spalten/Zeilen
//STRIP001      ScChangeActionDel* pActDel = (ScChangeActionDel*) pAct;
//STRIP001      if ( !bUndo )
//STRIP001      {   // Delete
//STRIP001          ScChangeActionType eInsType;        // fuer Insert-Undo-"Deletes"
//STRIP001          switch ( eActType )
//STRIP001          {
//STRIP001              case SC_CAT_DELETE_COLS :
//STRIP001                  eInsType = SC_CAT_INSERT_COLS;
//STRIP001              break;
//STRIP001              case SC_CAT_DELETE_ROWS :
//STRIP001                  eInsType = SC_CAT_INSERT_ROWS;
//STRIP001              break;
//STRIP001              case SC_CAT_DELETE_TABS :
//STRIP001                  eInsType = SC_CAT_INSERT_TABS;
//STRIP001              break;
//STRIP001          }
//STRIP001          for ( ScChangeAction* p = *ppFirstAction; p; p = p->GetNext() )
//STRIP001          {
//STRIP001              if ( p == pAct )
//STRIP001                  continue;   // for
//STRIP001              BOOL bUpdate = TRUE;
//STRIP001              if ( GetMergeState() == SC_CTMS_OTHER &&
//STRIP001                      p->GetActionNumber() <= GetLastMerge() )
//STRIP001              {   // Delete in mergendem Dokument, Action im zu mergenden
//STRIP001                  if ( p->IsInsertType() )
//STRIP001                  {
//STRIP001                      // Bei Insert Referenzen nur anpassen, wenn das Delete
//STRIP001                      // das Insert nicht schneidet.
//STRIP001                      if ( !aDelRange.Intersects( p->GetBigRange() ) )
//STRIP001                          p->UpdateReference( this, eMode, aRange, nDx, nDy, nDz );
//STRIP001                      bUpdate = FALSE;
//STRIP001                  }
//STRIP001                  else if ( p->GetType() == SC_CAT_CONTENT &&
//STRIP001                          p->IsDeletedInDelType( eInsType ) )
//STRIP001                  {   // Content in Insert-Undo-"Delete"
//STRIP001                      // Nicht anpassen, wenn dieses Delete in dem
//STRIP001                      // Insert-"Delete" sein wuerde (ist nur verschoben).
//STRIP001                      if ( aDelRange.In( p->GetBigRange().aStart ) )
//STRIP001                          bUpdate = FALSE;
//STRIP001                      else
//STRIP001                      {
//STRIP001                          const ScChangeActionLinkEntry* pLink = p->GetDeletedIn();
//STRIP001                          while ( pLink && bUpdate )
//STRIP001                          {
//STRIP001                              const ScChangeAction* pDel = pLink->GetAction();
//STRIP001                              if ( pDel && pDel->GetType() == eInsType &&
//STRIP001                                      pDel->GetBigRange().In( aDelRange ) )
//STRIP001                                  bUpdate = FALSE;
//STRIP001                              pLink = pLink->GetNext();
//STRIP001                          }
//STRIP001                      }
//STRIP001                  }
//STRIP001                  if ( !bUpdate )
//STRIP001                      continue;   // for
//STRIP001              }
//STRIP001              if ( aDelRange.In( p->GetBigRange() ) )
//STRIP001              {
//STRIP001                  // Innerhalb eines gerade geloeschten Bereiches nicht
//STRIP001                  // anpassen, stattdessen dem Bereich zuordnen.
//STRIP001                  // Mehrfache geloeschte Bereiche "stapeln".
//STRIP001                  // Kreuzende Deletes setzen mehrfach geloescht.
//STRIP001                  if ( !p->IsDeletedInDelType( eActType ) )
//STRIP001                  {
//STRIP001                      p->SetDeletedIn( pActDel );
//STRIP001                      // GeneratedDelContent in zu loeschende Liste aufnehmen
//STRIP001                      if ( bGeneratedDelContents )
//STRIP001                          pActDel->AddContent( (ScChangeActionContent*) p );
//STRIP001                  }
//STRIP001                  bUpdate = FALSE;
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  // Eingefuegte Bereiche abschneiden, wenn Start/End im
//STRIP001                  // Delete liegt, aber das Insert nicht komplett innerhalb
//STRIP001                  // des Delete liegt bzw. das Delete nicht komplett im
//STRIP001                  // Insert. Das Delete merkt sich, welchem Insert es was
//STRIP001                  // abgeschnitten hat, es kann auch nur ein einziges Insert
//STRIP001                  // sein (weil Delete einspaltig/einzeilig ist).
//STRIP001                  // Abgeschnittene Moves kann es viele geben.
//STRIP001                  //! Ein Delete ist immer einspaltig/einzeilig, deswegen 1
//STRIP001                  //! ohne die Ueberlappung auszurechnen.
//STRIP001                  switch ( p->GetType() )
//STRIP001                  {
//STRIP001                      case SC_CAT_INSERT_COLS :
//STRIP001                          if ( eActType == SC_CAT_DELETE_COLS )
//STRIP001                          {
//STRIP001                              if ( aDelRange.In( p->GetBigRange().aStart ) )
//STRIP001                              {
//STRIP001                                  pActDel->SetCutOffInsert(
//STRIP001                                      (ScChangeActionIns*) p, 1 );
//STRIP001                                  p->GetBigRange().aStart.IncCol( 1 );
//STRIP001                              }
//STRIP001                              else if ( aDelRange.In( p->GetBigRange().aEnd ) )
//STRIP001                              {
//STRIP001                                  pActDel->SetCutOffInsert(
//STRIP001                                      (ScChangeActionIns*) p, -1 );
//STRIP001                                  p->GetBigRange().aEnd.IncCol( -1 );
//STRIP001                              }
//STRIP001                          }
//STRIP001                      break;
//STRIP001                      case SC_CAT_INSERT_ROWS :
//STRIP001                          if ( eActType == SC_CAT_DELETE_ROWS )
//STRIP001                          {
//STRIP001                              if ( aDelRange.In( p->GetBigRange().aStart ) )
//STRIP001                              {
//STRIP001                                  pActDel->SetCutOffInsert(
//STRIP001                                      (ScChangeActionIns*) p, 1 );
//STRIP001                                  p->GetBigRange().aStart.IncRow( 1 );
//STRIP001                              }
//STRIP001                              else if ( aDelRange.In( p->GetBigRange().aEnd ) )
//STRIP001                              {
//STRIP001                                  pActDel->SetCutOffInsert(
//STRIP001                                      (ScChangeActionIns*) p, -1 );
//STRIP001                                  p->GetBigRange().aEnd.IncRow( -1 );
//STRIP001                              }
//STRIP001                          }
//STRIP001                      break;
//STRIP001                      case SC_CAT_INSERT_TABS :
//STRIP001                          if ( eActType == SC_CAT_DELETE_TABS )
//STRIP001                          {
//STRIP001                              if ( aDelRange.In( p->GetBigRange().aStart ) )
//STRIP001                              {
//STRIP001                                  pActDel->SetCutOffInsert(
//STRIP001                                      (ScChangeActionIns*) p, 1 );
//STRIP001                                  p->GetBigRange().aStart.IncTab( 1 );
//STRIP001                              }
//STRIP001                              else if ( aDelRange.In( p->GetBigRange().aEnd ) )
//STRIP001                              {
//STRIP001                                  pActDel->SetCutOffInsert(
//STRIP001                                      (ScChangeActionIns*) p, -1 );
//STRIP001                                  p->GetBigRange().aEnd.IncTab( -1 );
//STRIP001                              }
//STRIP001                          }
//STRIP001                      break;
//STRIP001                      case SC_CAT_MOVE :
//STRIP001                      {
//STRIP001                          ScChangeActionMove* pMove = (ScChangeActionMove*) p;
//STRIP001                          short nFrom = 0;
//STRIP001                          short nTo = 0;
//STRIP001                          if ( aDelRange.In( pMove->GetBigRange().aStart ) )
//STRIP001                              nTo = 1;
//STRIP001                          else if ( aDelRange.In( pMove->GetBigRange().aEnd ) )
//STRIP001                              nTo = -1;
//STRIP001                          if ( aDelRange.In( pMove->GetFromRange().aStart ) )
//STRIP001                              nFrom = 1;
//STRIP001                          else if ( aDelRange.In( pMove->GetFromRange().aEnd ) )
//STRIP001                              nFrom = -1;
//STRIP001                          if ( nFrom )
//STRIP001                          {
//STRIP001                              switch ( eActType )
//STRIP001                              {
//STRIP001                                  case SC_CAT_DELETE_COLS :
//STRIP001                                      if ( nFrom > 0 )
//STRIP001                                          pMove->GetFromRange().aStart.IncCol( nFrom );
//STRIP001                                      else
//STRIP001                                          pMove->GetFromRange().aEnd.IncCol( nFrom );
//STRIP001                                  break;
//STRIP001                                  case SC_CAT_DELETE_ROWS :
//STRIP001                                      if ( nFrom > 0 )
//STRIP001                                          pMove->GetFromRange().aStart.IncRow( nFrom );
//STRIP001                                      else
//STRIP001                                          pMove->GetFromRange().aEnd.IncRow( nFrom );
//STRIP001                                  break;
//STRIP001                                  case SC_CAT_DELETE_TABS :
//STRIP001                                      if ( nFrom > 0 )
//STRIP001                                          pMove->GetFromRange().aStart.IncTab( nFrom );
//STRIP001                                      else
//STRIP001                                          pMove->GetFromRange().aEnd.IncTab( nFrom );
//STRIP001                                  break;
//STRIP001                              }
//STRIP001                          }
//STRIP001                          if ( nTo )
//STRIP001                          {
//STRIP001                              switch ( eActType )
//STRIP001                              {
//STRIP001                                  case SC_CAT_DELETE_COLS :
//STRIP001                                      if ( nTo > 0 )
//STRIP001                                          pMove->GetBigRange().aStart.IncCol( nTo );
//STRIP001                                      else
//STRIP001                                          pMove->GetBigRange().aEnd.IncCol( nTo );
//STRIP001                                  break;
//STRIP001                                  case SC_CAT_DELETE_ROWS :
//STRIP001                                      if ( nTo > 0 )
//STRIP001                                          pMove->GetBigRange().aStart.IncRow( nTo );
//STRIP001                                      else
//STRIP001                                          pMove->GetBigRange().aEnd.IncRow( nTo );
//STRIP001                                  break;
//STRIP001                                  case SC_CAT_DELETE_TABS :
//STRIP001                                      if ( nTo > 0 )
//STRIP001                                          pMove->GetBigRange().aStart.IncTab( nTo );
//STRIP001                                      else
//STRIP001                                          pMove->GetBigRange().aEnd.IncTab( nTo );
//STRIP001                                  break;
//STRIP001                              }
//STRIP001                          }
//STRIP001                          if ( nFrom || nTo )
//STRIP001                          {
//STRIP001                              ScChangeActionDelMoveEntry* pLink =
//STRIP001                                  pActDel->AddCutOffMove( pMove, nFrom, nTo );
//STRIP001                              pMove->AddLink( pActDel, pLink );
//STRIP001                          }
//STRIP001                      }
//STRIP001                      break;
//STRIP001                  }
//STRIP001              }
//STRIP001              if ( bUpdate )
//STRIP001              {
//STRIP001                  p->UpdateReference( this, eMode, aRange, nDx, nDy, nDz );
//STRIP001                  if ( p->GetType() == eActType && !p->IsRejected() &&
//STRIP001                          !pActDel->IsDeletedIn() &&
//STRIP001                          p->GetBigRange().In( aDelRange ) )
//STRIP001                      pActDel->SetDeletedIn( p );     // "druntergerutscht"
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001      else
//STRIP001      {   // Undo Delete
//STRIP001          ScChangeAction* pNextAction = NULL;
//STRIP001          for ( ScChangeAction* p = *ppFirstAction; p; p = p->GetNext() )
//STRIP001          {
//STRIP001              if ( p == pAct )
//STRIP001                  continue;   // for
//STRIP001              BOOL bUpdate = TRUE;
//STRIP001              if ( aDelRange.In( p->GetBigRange() ) )
//STRIP001              {
//STRIP001                  if ( p->IsDeletedInDelType( eActType ) )
//STRIP001                  {
//STRIP001                      if ( p->IsDeletedIn( pActDel ) )
//STRIP001                      {
//STRIP001                          if ( p->GetType() != SC_CAT_CONTENT ||
//STRIP001                                  ((ScChangeActionContent*)p)->IsTopContent() )
//STRIP001                          {   // erst der TopContent wird wirklich entfernt
//STRIP001                              p->RemoveDeletedIn( pActDel );
//STRIP001                              // GeneratedDelContent _nicht_ aus Liste loeschen,
//STRIP001                              // wir brauchen ihn evtl. noch fuer Reject,
//STRIP001                              // geloescht wird in DeleteCellEntries
//STRIP001                          }
//STRIP001                      }
//STRIP001                      bUpdate = FALSE;
//STRIP001                  }
//STRIP001                  else if ( eActType != SC_CAT_DELETE_TABS &&
//STRIP001                          p->IsDeletedInDelType( SC_CAT_DELETE_TABS ) )
//STRIP001                  {   // in geloeschten Tabellen nicht updaten,
//STRIP001                      // ausser wenn Tabelle verschoben wird
//STRIP001                      bUpdate = FALSE;
//STRIP001                  }
//STRIP001                  if ( p->GetType() == eActType && pActDel->IsDeletedIn( p ) )
//STRIP001                  {
//STRIP001                      pActDel->RemoveDeletedIn( p );  // "druntergerutscht"
//STRIP001                      bUpdate = TRUE;
//STRIP001                  }
//STRIP001              }
//STRIP001              if ( bUpdate )
//STRIP001                  p->UpdateReference( this, eMode, aRange, nDx, nDy, nDz );
//STRIP001          }
//STRIP001          if ( !bGeneratedDelContents )
//STRIP001          {   // die werden sonst noch fuer das echte Undo gebraucht
//STRIP001              pActDel->UndoCutOffInsert();
//STRIP001              pActDel->UndoCutOffMoves();
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  else if ( eActType == SC_CAT_MOVE )
//STRIP001  {
//STRIP001      ScChangeActionMove* pActMove = (ScChangeActionMove*) pAct;
//STRIP001      BOOL bLastCutMove = ( pActMove == pLastCutMove );
//STRIP001      const ScBigRange& rTo = pActMove->GetBigRange();
//STRIP001      const ScBigRange& rFrom = pActMove->GetFromRange();
//STRIP001      if ( !bUndo )
//STRIP001      {   // Move
//STRIP001          for ( ScChangeAction* p = *ppFirstAction; p; p = p->GetNext() )
//STRIP001          {
//STRIP001              if ( p == pAct )
//STRIP001                  continue;   // for
//STRIP001              if ( p->GetType() == SC_CAT_CONTENT )
//STRIP001              {
//STRIP001                  // Inhalt in Ziel deleten (Inhalt in Quelle moven)
//STRIP001                  if ( rTo.In( p->GetBigRange() ) )
//STRIP001                  {
//STRIP001                      if ( !p->IsDeletedIn( pActMove ) )
//STRIP001                      {
//STRIP001                          p->SetDeletedIn( pActMove );
//STRIP001                          // GeneratedDelContent in zu loeschende Liste aufnehmen
//STRIP001                          if ( bGeneratedDelContents )
//STRIP001                              pActMove->AddContent( (ScChangeActionContent*) p );
//STRIP001                      }
//STRIP001                  }
//STRIP001                  else if ( bLastCutMove &&
//STRIP001                          p->GetActionNumber() > nEndLastCut &&
//STRIP001                          rFrom.In( p->GetBigRange() ) )
//STRIP001                  {   // Paste Cut: neuer Content nach Cut eingefuegt, bleibt.
//STRIP001                      // Aufsplitten der ContentChain
//STRIP001                      ScChangeActionContent *pHere, *pTmp;
//STRIP001                      pHere = (ScChangeActionContent*) p;
//STRIP001                      while ( (pTmp = pHere->GetPrevContent()) &&
//STRIP001                              pTmp->GetActionNumber() > nEndLastCut )
//STRIP001                          pHere = pTmp;
//STRIP001                      if ( pTmp )
//STRIP001                      {   // wird TopContent des Move
//STRIP001                          pTmp->SetNextContent( NULL );
//STRIP001                          pHere->SetPrevContent( NULL );
//STRIP001                      }
//STRIP001                      do
//STRIP001                      {   // Abhaengigkeit vom FromRange herstellen
//STRIP001                          AddDependentWithNotify( pActMove, pHere );
//STRIP001                      } while ( pHere = pHere->GetNextContent() );
//STRIP001                  }
//STRIP001                  else
//STRIP001                      p->UpdateReference( this, eMode, rFrom, nDx, nDy, nDz );
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001      else
//STRIP001      {   // Undo Move
//STRIP001          BOOL bActRejected = pActMove->IsRejected();
//STRIP001          for ( ScChangeAction* p = *ppFirstAction; p; p = p->GetNext() )
//STRIP001          {
//STRIP001              if ( p == pAct )
//STRIP001                  continue;   // for
//STRIP001              if ( p->GetType() == SC_CAT_CONTENT )
//STRIP001              {
//STRIP001                  // Inhalt in Ziel moven, wenn nicht deleted, sonst undelete
//STRIP001                  if ( p->IsDeletedIn( pActMove ) )
//STRIP001                  {
//STRIP001                      if ( ((ScChangeActionContent*)p)->IsTopContent() )
//STRIP001                      {   // erst der TopContent wird wirklich entfernt
//STRIP001                          p->RemoveDeletedIn( pActMove );
//STRIP001                          // GeneratedDelContent _nicht_ aus Liste loeschen,
//STRIP001                          // wir brauchen ihn evtl. noch fuer Reject,
//STRIP001                          // geloescht wird in DeleteCellEntries
//STRIP001                      }
//STRIP001                  }
//STRIP001                  else
//STRIP001                      p->UpdateReference( this, eMode, rTo, nDx, nDy, nDz );
//STRIP001                  if ( bActRejected &&
//STRIP001                          ((ScChangeActionContent*)p)->IsTopContent() &&
//STRIP001                          rFrom.In( p->GetBigRange() ) )
//STRIP001                  {   // Abhaengigkeit herstellen, um Content zu schreiben
//STRIP001                      ScChangeActionLinkEntry* pLink =
//STRIP001                          pActMove->AddDependent( p );
//STRIP001                      p->AddLink( pActMove, pLink );
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001  {   // Insert / Undo Insert
//STRIP001      switch ( GetMergeState() )
//STRIP001      {
//STRIP001          case SC_CTMS_NONE :
//STRIP001          case SC_CTMS_OTHER :
//STRIP001          {
//STRIP001              for ( ScChangeAction* p = *ppFirstAction; p; p = p->GetNext() )
//STRIP001              {
//STRIP001                  if ( p == pAct )
//STRIP001                      continue;   // for
//STRIP001                  p->UpdateReference( this, eMode, aRange, nDx, nDy, nDz );
//STRIP001              }
//STRIP001          }
//STRIP001          break;
//STRIP001          case SC_CTMS_PREPARE :
//STRIP001          {
//STRIP001              // in Insert-Undo "Deleten"
//STRIP001              const ScChangeActionLinkEntry* pLink = pAct->GetFirstDependentEntry();
//STRIP001              while ( pLink )
//STRIP001              {
//STRIP001                  ScChangeAction* p = (ScChangeAction*) pLink->GetAction();
//STRIP001                  if ( p )
//STRIP001                      p->SetDeletedIn( pAct );
//STRIP001                  pLink = pLink->GetNext();
//STRIP001              }
//STRIP001              for ( ScChangeAction* p = *ppFirstAction; p; p = p->GetNext() )
//STRIP001              {
//STRIP001                  if ( p == pAct )
//STRIP001                      continue;   // for
//STRIP001                  if ( !p->IsDeletedIn( pAct ) )
//STRIP001                      p->UpdateReference( this, eMode, aRange, nDx, nDy, nDz );
//STRIP001              }
//STRIP001          }
//STRIP001          break;
//STRIP001          case SC_CTMS_OWN :
//STRIP001          {
//STRIP001              for ( ScChangeAction* p = *ppFirstAction; p; p = p->GetNext() )
//STRIP001              {
//STRIP001                  if ( p == pAct )
//STRIP001                      continue;   // for
//STRIP001                  if ( !p->IsDeletedIn( pAct ) )
//STRIP001                      p->UpdateReference( this, eMode, aRange, nDx, nDy, nDz );
//STRIP001              }
//STRIP001              // in Insert-Undo "Delete" rueckgaengig
//STRIP001              const ScChangeActionLinkEntry* pLink = pAct->GetFirstDependentEntry();
//STRIP001              while ( pLink )
//STRIP001              {
//STRIP001                  ScChangeAction* p = (ScChangeAction*) pLink->GetAction();
//STRIP001                  if ( p )
//STRIP001                      p->RemoveDeletedIn( pAct );
//STRIP001                  pLink = pLink->GetNext();
//STRIP001              }
//STRIP001          }
//STRIP001          break;
//STRIP001      }
//STRIP001  }
//STRIP001 }


//STRIP001 void ScChangeTrack::GetDependents( ScChangeAction* pAct,
//STRIP001      ScChangeActionTable& rTable, BOOL bListMasterDelete, BOOL bAllFlat )
//STRIP001 {
//STRIP001  //! bAllFlat==TRUE: intern aus Accept oder Reject gerufen,
//STRIP001  //! => Generated werden nicht aufgenommen
//STRIP001
//STRIP001  BOOL bIsDelete = pAct->IsDeleteType();
//STRIP001  BOOL bIsMasterDelete = ( bListMasterDelete && pAct->IsMasterDelete() );
//STRIP001
//STRIP001  ScChangeAction* pCur = pAct;
//STRIP001  ScChangeActionStack* pStack = new ScChangeActionStack;
//STRIP001  do
//STRIP001  {
//STRIP001      if ( pCur->IsInsertType() )
//STRIP001      {
//STRIP001          const ScChangeActionLinkEntry* pL = pCur->GetFirstDependentEntry();
//STRIP001          while ( pL )
//STRIP001          {
//STRIP001              ScChangeAction* p = (ScChangeAction*) pL->GetAction();
//STRIP001              if ( p != pAct )
//STRIP001              {
//STRIP001                  if ( bAllFlat )
//STRIP001                  {
//STRIP001                      ULONG n = p->GetActionNumber();
//STRIP001                      if ( !IsGenerated( n ) && rTable.Insert( n, p ) )
//STRIP001                          if ( p->HasDependent() )
//STRIP001                              pStack->Push( p );
//STRIP001                  }
//STRIP001                  else
//STRIP001                  {
//STRIP001                      if ( p->GetType() == SC_CAT_CONTENT )
//STRIP001                      {
//STRIP001                          if ( ((ScChangeActionContent*)p)->IsTopContent() )
//STRIP001                              rTable.Insert( p->GetActionNumber(), p );
//STRIP001                      }
//STRIP001                      else
//STRIP001                          rTable.Insert( p->GetActionNumber(), p );
//STRIP001                  }
//STRIP001              }
//STRIP001              pL = pL->GetNext();
//STRIP001          }
//STRIP001      }
//STRIP001      else if ( pCur->IsDeleteType() )
//STRIP001      {
//STRIP001          if ( bIsDelete )
//STRIP001          {   // Inhalte geloeschter Bereiche interessieren nur bei Delete
//STRIP001              ScChangeActionDel* pDel = (ScChangeActionDel*) pCur;
//STRIP001              if ( !bAllFlat && bIsMasterDelete && pCur == pAct )
//STRIP001              {
//STRIP001                  // zu diesem Delete gehoerende Deletes in gleiche Ebene,
//STRIP001                  // wenn dieses Delete das momentan oberste einer Reihe ist,
//STRIP001                  ScChangeActionType eType = pDel->GetType();
//STRIP001                  ScChangeAction* p = pDel;
//STRIP001                  while ( (p = p->GetPrev()) && p->GetType() == eType &&
//STRIP001                          !((ScChangeActionDel*)p)->IsTopDelete() )
//STRIP001                      rTable.Insert( p->GetActionNumber(), p );
//STRIP001                  // dieses Delete auch in Table!
//STRIP001                  rTable.Insert( pAct->GetActionNumber(), pAct );
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  const ScChangeActionLinkEntry* pL = pCur->GetFirstDeletedEntry();
//STRIP001                  while ( pL )
//STRIP001                  {
//STRIP001                      ScChangeAction* p = (ScChangeAction*) pL->GetAction();
//STRIP001                      if ( p != pAct )
//STRIP001                      {
//STRIP001                          if ( bAllFlat )
//STRIP001                          {
//STRIP001                              // nur ein TopContent einer Kette ist in LinkDeleted
//STRIP001                              ULONG n = p->GetActionNumber();
//STRIP001                              if ( !IsGenerated( n ) && rTable.Insert( n, p ) )
//STRIP001                                  if ( p->HasDeleted() ||
//STRIP001                                          p->GetType() == SC_CAT_CONTENT )
//STRIP001                                      pStack->Push( p );
//STRIP001                          }
//STRIP001                          else
//STRIP001                          {
//STRIP001                              if ( p->IsDeleteType() )
//STRIP001                              {   // weiteres TopDelete in gleiche Ebene,
//STRIP001                                  // es ist nicht rejectable
//STRIP001                                  if ( ((ScChangeActionDel*)p)->IsTopDelete() )
//STRIP001                                      rTable.Insert( p->GetActionNumber(), p );
//STRIP001                              }
//STRIP001                              else
//STRIP001                                  rTable.Insert( p->GetActionNumber(), p );
//STRIP001                          }
//STRIP001                      }
//STRIP001                      pL = pL->GetNext();
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001      else if ( pCur->GetType() == SC_CAT_MOVE )
//STRIP001      {
//STRIP001          // geloeschte Contents im ToRange
//STRIP001          const ScChangeActionLinkEntry* pL = pCur->GetFirstDeletedEntry();
//STRIP001          while ( pL )
//STRIP001          {
//STRIP001              ScChangeAction* p = (ScChangeAction*) pL->GetAction();
//STRIP001              if ( p != pAct && rTable.Insert( p->GetActionNumber(), p ) )
//STRIP001              {
//STRIP001                  // nur ein TopContent einer Kette ist in LinkDeleted
//STRIP001                  if ( bAllFlat && (p->HasDeleted() ||
//STRIP001                          p->GetType() == SC_CAT_CONTENT) )
//STRIP001                      pStack->Push( p );
//STRIP001              }
//STRIP001              pL = pL->GetNext();
//STRIP001          }
//STRIP001          // neue Contents im FromRange oder neuer FromRange im ToRange
//STRIP001          // oder Inserts/Deletes in FromRange/ToRange
//STRIP001          pL = pCur->GetFirstDependentEntry();
//STRIP001          while ( pL )
//STRIP001          {
//STRIP001              ScChangeAction* p = (ScChangeAction*) pL->GetAction();
//STRIP001              if ( p != pAct )
//STRIP001              {
//STRIP001                  if ( bAllFlat )
//STRIP001                  {
//STRIP001                      ULONG n = p->GetActionNumber();
//STRIP001                      if ( !IsGenerated( n ) && rTable.Insert( n, p ) )
//STRIP001                          if ( p->HasDependent() || p->HasDeleted() )
//STRIP001                              pStack->Push( p );
//STRIP001                  }
//STRIP001                  else
//STRIP001                  {
//STRIP001                      if ( p->GetType() == SC_CAT_CONTENT )
//STRIP001                      {
//STRIP001                          if ( ((ScChangeActionContent*)p)->IsTopContent() )
//STRIP001                              rTable.Insert( p->GetActionNumber(), p );
//STRIP001                      }
//STRIP001                      else
//STRIP001                          rTable.Insert( p->GetActionNumber(), p );
//STRIP001                  }
//STRIP001              }
//STRIP001              pL = pL->GetNext();
//STRIP001          }
//STRIP001      }
//STRIP001      else if ( pCur->GetType() == SC_CAT_CONTENT )
//STRIP001      {   // alle Aenderungen an gleicher Position
//STRIP001          ScChangeActionContent* pContent = (ScChangeActionContent*) pCur;
//STRIP001          // alle vorherigen
//STRIP001          while ( pContent = pContent->GetPrevContent() )
//STRIP001          {
//STRIP001              if ( !pContent->IsRejected() )
//STRIP001                  rTable.Insert( pContent->GetActionNumber(), pContent );
//STRIP001          }
//STRIP001          pContent = (ScChangeActionContent*) pCur;
//STRIP001          // alle nachfolgenden
//STRIP001          while ( pContent = pContent->GetNextContent() )
//STRIP001          {
//STRIP001              if ( !pContent->IsRejected() )
//STRIP001                  rTable.Insert( pContent->GetActionNumber(), pContent );
//STRIP001          }
//STRIP001          // all MatrixReferences of a MatrixOrigin
//STRIP001          const ScChangeActionLinkEntry* pL = pCur->GetFirstDependentEntry();
//STRIP001          while ( pL )
//STRIP001          {
//STRIP001              ScChangeAction* p = (ScChangeAction*) pL->GetAction();
//STRIP001              if ( p != pAct )
//STRIP001              {
//STRIP001                  if ( bAllFlat )
//STRIP001                  {
//STRIP001                      ULONG n = p->GetActionNumber();
//STRIP001                      if ( !IsGenerated( n ) && rTable.Insert( n, p ) )
//STRIP001                          if ( p->HasDependent() )
//STRIP001                              pStack->Push( p );
//STRIP001                  }
//STRIP001                  else
//STRIP001                      rTable.Insert( p->GetActionNumber(), p );
//STRIP001              }
//STRIP001              pL = pL->GetNext();
//STRIP001          }
//STRIP001      }
//STRIP001      else if ( pCur->GetType() == SC_CAT_REJECT )
//STRIP001      {
//STRIP001          if ( bAllFlat )
//STRIP001          {
//STRIP001              ScChangeAction* p = GetAction(
//STRIP001                      ((ScChangeActionReject*)pCur)->GetRejectAction() );
//STRIP001              if ( p != pAct && !rTable.Get( p->GetActionNumber() ) )
//STRIP001                  pStack->Push( p );
//STRIP001          }
//STRIP001      }
//STRIP001  } while ( pCur = pStack->Pop() );
//STRIP001  delete pStack;
//STRIP001 }


//STRIP001 BOOL ScChangeTrack::SelectContent( ScChangeAction* pAct, BOOL bOldest )
//STRIP001 {
//STRIP001  if ( pAct->GetType() != SC_CAT_CONTENT )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  ScChangeActionContent* pContent = (ScChangeActionContent*) pAct;
//STRIP001  if ( bOldest )
//STRIP001  {
//STRIP001      pContent = pContent->GetTopContent();
//STRIP001      ScChangeActionContent* pPrevContent;
//STRIP001      while ( (pPrevContent = pContent->GetPrevContent()) &&
//STRIP001              pPrevContent->IsVirgin() )
//STRIP001          pContent = pPrevContent;
//STRIP001  }
//STRIP001
//STRIP001  if ( !pContent->IsClickable() )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  ScBigRange aBigRange( pContent->GetBigRange() );
//STRIP001  const ScBaseCell* pCell = (bOldest ? pContent->GetOldCell() :
//STRIP001      pContent->GetNewCell());
//STRIP001  if ( ScChangeActionContent::GetContentCellType( pCell ) == SC_CACCT_MATORG )
//STRIP001  {
//STRIP001      USHORT nC, nR;
//STRIP001      ((const ScFormulaCell*)pCell)->GetMatColsRows( nC, nR );
//STRIP001      aBigRange.aEnd.IncCol( nC-1 );
//STRIP001      aBigRange.aEnd.IncRow( nR-1 );
//STRIP001  }
//STRIP001
//STRIP001  if ( !aBigRange.IsValid( pDoc ) )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  ScRange aRange( aBigRange.MakeRange() );
//STRIP001  if ( !pDoc->IsBlockEditable( aRange.aStart.Tab(), aRange.aStart.Col(),
//STRIP001          aRange.aStart.Row(), aRange.aEnd.Col(), aRange.aEnd.Row() ) )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  if ( pContent->HasDependent() )
//STRIP001  {
//STRIP001      BOOL bOk = TRUE;
//STRIP001      Stack aRejectActions;
//STRIP001      const ScChangeActionLinkEntry* pL = pContent->GetFirstDependentEntry();
//STRIP001      while ( pL )
//STRIP001      {
//STRIP001          ScChangeAction* p = (ScChangeAction*) pL->GetAction();
//STRIP001          if ( p != pContent )
//STRIP001          {
//STRIP001              if ( p->GetType() == SC_CAT_CONTENT )
//STRIP001              {
//STRIP001                  // we don't need no recursion here, do we?
//STRIP001                  bOk &= ((ScChangeActionContent*)p)->Select( pDoc, this,
//STRIP001                      bOldest, &aRejectActions );
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  DBG_ERRORFILE( "ScChangeTrack::SelectContent: content dependent no content" );
//STRIP001              }
//STRIP001          }
//STRIP001          pL = pL->GetNext();
//STRIP001      }
//STRIP001
//STRIP001      bOk &= pContent->Select( pDoc, this, bOldest, NULL );
//STRIP001      // now the matrix is inserted and new content values are ready
//STRIP001
//STRIP001      ScChangeActionContent* pNew;
//STRIP001      while ( pNew = (ScChangeActionContent*) aRejectActions.Pop() )
//STRIP001      {
//STRIP001          ScAddress aPos( pNew->GetBigRange().aStart.MakeAddress() );
//STRIP001          pNew->SetNewValue( pDoc->GetCell( aPos ), pDoc );
//STRIP001          Append( pNew );
//STRIP001      }
//STRIP001      return bOk;
//STRIP001  }
//STRIP001  else
//STRIP001      return pContent->Select( pDoc, this, bOldest, NULL );
//STRIP001 }


//STRIP001 void ScChangeTrack::AcceptAll()
//STRIP001 {
//STRIP001  for ( ScChangeAction* p = GetFirst(); p; p = p->GetNext() )
//STRIP001  {
//STRIP001      p->Accept();
//STRIP001  }
//STRIP001 }


//STRIP001 BOOL ScChangeTrack::Accept( ScChangeAction* pAct )
//STRIP001 {
//STRIP001  if ( !pAct->IsClickable() )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  if ( pAct->IsDeleteType() || pAct->GetType() == SC_CAT_CONTENT )
//STRIP001  {
//STRIP001      ScChangeActionTable* pTable = new ScChangeActionTable;
//STRIP001      GetDependents( pAct, *pTable, FALSE, TRUE );
//STRIP001      for ( ScChangeAction* p = pTable->First(); p; p = pTable->Next() )
//STRIP001      {
//STRIP001          p->Accept();
//STRIP001      }
//STRIP001      delete pTable;
//STRIP001  }
//STRIP001  pAct->Accept();
//STRIP001  return TRUE;
//STRIP001 }


//STRIP001 BOOL ScChangeTrack::RejectAll()
//STRIP001 {
//STRIP001  BOOL bOk = TRUE;
//STRIP001  for ( ScChangeAction* p = GetLast(); p && bOk; p = p->GetPrev() )
//STRIP001  {   //! rueckwaerts, weil abhaengige hinten und RejectActions angehaengt
//STRIP001      if ( p->IsInternalRejectable() )
//STRIP001          bOk = Reject( p );
//STRIP001  }
//STRIP001  return bOk;
//STRIP001 }


//STRIP001 BOOL ScChangeTrack::Reject( ScChangeAction* pAct )
//STRIP001 {
//STRIP001  if ( !pAct->IsRejectable() )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  ScChangeActionTable* pTable = NULL;
//STRIP001  if ( pAct->HasDependent() )
//STRIP001  {
//STRIP001      pTable = new ScChangeActionTable;
//STRIP001      GetDependents( pAct, *pTable, FALSE, TRUE );
//STRIP001  }
//STRIP001  BOOL bRejected = Reject( pAct, pTable, FALSE );
//STRIP001  if ( pTable )
//STRIP001      delete pTable;
//STRIP001  return bRejected;
//STRIP001 }


//STRIP001 BOOL ScChangeTrack::Reject( ScChangeAction* pAct, ScChangeActionTable* pTable,
//STRIP001      BOOL bRecursion )
//STRIP001 {
//STRIP001  if ( !pAct->IsInternalRejectable() )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  BOOL bOk = TRUE;
//STRIP001  BOOL bRejected = FALSE;
//STRIP001  if ( pAct->IsInsertType() )
//STRIP001  {
//STRIP001      if ( pAct->HasDependent() && !bRecursion )
//STRIP001      {
//STRIP001          const ScBigRange& rRange = pAct->GetBigRange();
//STRIP001          DBG_ASSERT( pTable, "ScChangeTrack::Reject: Insert ohne Table" );
//STRIP001          for ( ScChangeAction* p = pTable->Last(); p && bOk; p = pTable->Prev() )
//STRIP001          {
//STRIP001              // keine Contents restoren, die eh geloescht werden wuerden
//STRIP001              if ( p->GetType() == SC_CAT_CONTENT )
//STRIP001                  p->SetRejected();
//STRIP001              else if ( p->IsDeleteType() )
//STRIP001                  p->Accept();        // geloeschtes ins Nirvana
//STRIP001              else
//STRIP001                  bOk = Reject( p, NULL, TRUE );      //! rekursiv
//STRIP001          }
//STRIP001      }
//STRIP001      if ( bOk && (bRejected = pAct->Reject( pDoc )) )
//STRIP001      {
//STRIP001          // pRefDoc NULL := geloeschte Zellen nicht speichern
//STRIP001          AppendDeleteRange( pAct->GetBigRange().MakeRange(), NULL, (short) 0,
//STRIP001              pAct->GetActionNumber() );
//STRIP001      }
//STRIP001  }
//STRIP001  else if ( pAct->IsDeleteType() )
//STRIP001  {
//STRIP001      DBG_ASSERT( !pTable, "ScChangeTrack::Reject: Delete mit Table" );
//STRIP001      ScBigRange aDelRange;
//STRIP001      ULONG nRejectAction = pAct->GetActionNumber();
//STRIP001      BOOL bTabDel, bTabDelOk;
//STRIP001      if ( pAct->GetType() == SC_CAT_DELETE_TABS )
//STRIP001      {
//STRIP001          bTabDel = TRUE;
//STRIP001          aDelRange = pAct->GetBigRange();
//STRIP001          bOk = bTabDelOk = pAct->Reject( pDoc );
//STRIP001          if ( bOk )
//STRIP001          {
//STRIP001              pAct = pAct->GetPrev();
//STRIP001              bOk = ( pAct && pAct->GetType() == SC_CAT_DELETE_COLS );
//STRIP001          }
//STRIP001      }
//STRIP001      else
//STRIP001          bTabDel = bTabDelOk = FALSE;
//STRIP001      ScChangeActionDel* pDel = (ScChangeActionDel*) pAct;
//STRIP001      if ( bOk )
//STRIP001      {
//STRIP001          aDelRange = pDel->GetOverAllRange();
//STRIP001          bOk = aDelRange.IsValid( pDoc );
//STRIP001      }
//STRIP001      BOOL bOneOk = FALSE;
//STRIP001      if ( bOk )
//STRIP001      {
//STRIP001          ScChangeActionType eActType = pAct->GetType();
//STRIP001          switch ( eActType )
//STRIP001          {
//STRIP001              case SC_CAT_DELETE_COLS :
//STRIP001                  aDelRange.aStart.SetCol( aDelRange.aEnd.Col() );
//STRIP001              break;
//STRIP001              case SC_CAT_DELETE_ROWS :
//STRIP001                  aDelRange.aStart.SetRow( aDelRange.aEnd.Row() );
//STRIP001              break;
//STRIP001              case SC_CAT_DELETE_TABS :
//STRIP001                  aDelRange.aStart.SetTab( aDelRange.aEnd.Tab() );
//STRIP001              break;
//STRIP001          }
//STRIP001          ScChangeAction* p = pAct;
//STRIP001          BOOL bLoop = TRUE;
//STRIP001          do
//STRIP001          {
//STRIP001              pDel = (ScChangeActionDel*) p;
//STRIP001              bOk = pDel->Reject( pDoc );
//STRIP001              if ( bOk )
//STRIP001              {
//STRIP001                  if ( bOneOk )
//STRIP001                  {
//STRIP001                      switch ( pDel->GetType() )
//STRIP001                      {
//STRIP001                          case SC_CAT_DELETE_COLS :
//STRIP001                              aDelRange.aStart.IncCol( -1 );
//STRIP001                          break;
//STRIP001                          case SC_CAT_DELETE_ROWS :
//STRIP001                              aDelRange.aStart.IncRow( -1 );
//STRIP001                          break;
//STRIP001                          case SC_CAT_DELETE_TABS :
//STRIP001                              aDelRange.aStart.IncTab( -1 );
//STRIP001                          break;
//STRIP001                      }
//STRIP001                  }
//STRIP001                  else
//STRIP001                      bOneOk = TRUE;
//STRIP001              }
//STRIP001              if ( pDel->IsBaseDelete() )
//STRIP001                  bLoop = FALSE;
//STRIP001              else
//STRIP001                  p = p->GetPrev();
//STRIP001          } while ( bOk && bLoop && p && p->GetType() == eActType &&
//STRIP001              !((ScChangeActionDel*)p)->IsTopDelete() );
//STRIP001      }
//STRIP001      bRejected = bOk;
//STRIP001      if ( bOneOk || (bTabDel && bTabDelOk) )
//STRIP001      {
//STRIP001          // Delete-Reject machte UpdateReference Undo
//STRIP001          ScChangeActionIns* pReject = new ScChangeActionIns(
//STRIP001              aDelRange.MakeRange() );
//STRIP001          pReject->SetRejectAction( nRejectAction );
//STRIP001          pReject->SetState( SC_CAS_ACCEPTED );
//STRIP001          Append( pReject );
//STRIP001      }
//STRIP001  }
//STRIP001  else if ( pAct->GetType() == SC_CAT_MOVE )
//STRIP001  {
//STRIP001      if ( pAct->HasDependent() && !bRecursion )
//STRIP001      {
//STRIP001          const ScBigRange& rRange = pAct->GetBigRange();
//STRIP001          DBG_ASSERT( pTable, "ScChangeTrack::Reject: Move ohne Table" );
//STRIP001          for ( ScChangeAction* p = pTable->Last(); p && bOk; p = pTable->Prev() )
//STRIP001          {
//STRIP001              bOk = Reject( p, NULL, TRUE );      //! rekursiv
//STRIP001          }
//STRIP001      }
//STRIP001      if ( bOk && (bRejected = pAct->Reject( pDoc )) )
//STRIP001      {
//STRIP001          ScChangeActionMove* pReject = new ScChangeActionMove(
//STRIP001              pAct->GetBigRange().MakeRange(),
//STRIP001              ((ScChangeActionMove*)pAct)->GetFromRange().MakeRange(), this );
//STRIP001          pReject->SetRejectAction( pAct->GetActionNumber() );
//STRIP001          pReject->SetState( SC_CAS_ACCEPTED );
//STRIP001          Append( pReject );
//STRIP001      }
//STRIP001  }
//STRIP001  else if ( pAct->GetType() == SC_CAT_CONTENT )
//STRIP001  {
//STRIP001      ScRange aRange;
//STRIP001      ScChangeActionContent* pReject;
//STRIP001      if ( bRecursion )
//STRIP001          pReject = NULL;
//STRIP001      else
//STRIP001      {
//STRIP001          aRange = pAct->GetBigRange().aStart.MakeAddress();
//STRIP001          pReject = new ScChangeActionContent( aRange );
//STRIP001          pReject->SetOldValue( pDoc->GetCell( aRange.aStart ), pDoc, pDoc );
//STRIP001      }
//STRIP001      if ( (bRejected = pAct->Reject( pDoc )) && !bRecursion )
//STRIP001      {
//STRIP001          pReject->SetNewValue( pDoc->GetCell( aRange.aStart ), pDoc );
//STRIP001          pReject->SetRejectAction( pAct->GetActionNumber() );
//STRIP001          pReject->SetState( SC_CAS_ACCEPTED );
//STRIP001          Append( pReject );
//STRIP001      }
//STRIP001      else if ( pReject )
//STRIP001          delete pReject;
//STRIP001  }
//STRIP001  else
//STRIP001      DBG_ERROR( "ScChangeTrack::Reject: say what?" );
//STRIP001
//STRIP001  return bRejected;
//STRIP001 }


ULONG ScChangeTrack::AddLoadedGenerated(ScBaseCell* pNewCell, const ScBigRange& aBigRange )
{
DBG_ASSERT(0, "STRIP"); //STRIP001      ScChangeActionContent* pAct = new ScChangeActionContent( --nGeneratedMin, pNewCell, aBigRange, pDoc );
//STRIP001  if ( pAct )
//STRIP001  {
//STRIP001      if ( pFirstGeneratedDelContent )
//STRIP001          pFirstGeneratedDelContent->pPrev = pAct;
//STRIP001      pAct->pNext = pFirstGeneratedDelContent;
//STRIP001      pFirstGeneratedDelContent = pAct;
//STRIP001      aGeneratedTable.Insert( pAct->GetActionNumber(), pAct );
//STRIP001      return pAct->GetActionNumber();
//STRIP001  }
/*N*/   return 0;
/*N*/ }

}
