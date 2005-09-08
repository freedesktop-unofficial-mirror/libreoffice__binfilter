/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_edredln.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-08 09:01:32 $
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


#pragma hdrstop

// auto strip #ifndef _DOCARY_HXX
// auto strip #include <docary.hxx>
// auto strip #endif
// auto strip #ifndef _SV_WINDOW_HXX //autogen
// auto strip #include <vcl/window.hxx>
// auto strip #endif

#ifndef _ERRHDL_HXX
#include <errhdl.hxx>
#endif

// auto strip #include "redline.hxx"

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

#include "doc.hxx"
// auto strip #include "swundo.hxx"
#include "editsh.hxx"
// auto strip #include "edimp.hxx"
// auto strip #include "frmtool.hxx"
namespace binfilter {


//STRIP001 USHORT SwEditShell::GetRedlineMode() const
//STRIP001 {
//STRIP001  return GetDoc()->GetRedlineMode();
//STRIP001 }

//STRIP001 void SwEditShell::SetRedlineMode( USHORT eMode )
//STRIP001 {
//STRIP001  if( eMode != GetDoc()->GetRedlineMode() )
//STRIP001  {
//STRIP001      SET_CURR_SHELL( this );
//STRIP001      StartAllAction();
//STRIP001      GetDoc()->SetRedlineMode( eMode );
//STRIP001      EndAllAction();
//STRIP001  }
//STRIP001 }

/*N*/ BOOL SwEditShell::IsRedlineOn() const
/*N*/ {
/*N*/   return GetDoc()->IsRedlineOn();
/*N*/ }

//STRIP001 USHORT SwEditShell::GetRedlineCount() const
//STRIP001 {
//STRIP001  return GetDoc()->GetRedlineTbl().Count();
//STRIP001 }

//STRIP001 const SwRedline& SwEditShell::GetRedline( USHORT nPos ) const
//STRIP001 {
//STRIP001  return *GetDoc()->GetRedlineTbl()[ nPos ];
//STRIP001 }

//STRIP001 void lcl_InvalidateAll( ViewShell* pSh )
//STRIP001 {
//STRIP001  ViewShell *pStop = pSh;
//STRIP001  do
//STRIP001  {
//STRIP001      if ( pSh->GetWin() )
//STRIP001          pSh->GetWin()->Invalidate();
//STRIP001      pSh = (ViewShell*)pSh->GetNext();
//STRIP001
//STRIP001  } while ( pSh != pStop );
//STRIP001 }

//STRIP001 BOOL SwEditShell::AcceptRedline( USHORT nPos )
//STRIP001 {
//STRIP001  SET_CURR_SHELL( this );
//STRIP001  StartAllAction();
//STRIP001  BOOL bRet = GetDoc()->AcceptRedline( nPos );
//STRIP001  if( !nPos && !::IsExtraData( GetDoc() ) )
//STRIP001      lcl_InvalidateAll( this );
//STRIP001  EndAllAction();
//STRIP001  return bRet;
//STRIP001 }

//STRIP001 BOOL SwEditShell::AcceptRedline()
//STRIP001 {
//STRIP001  SET_CURR_SHELL( this );
//STRIP001  StartAllAction();
//STRIP001
//STRIP001  GetDoc()->StartUndo();
//STRIP001  BOOL bRet = FALSE;
//STRIP001  FOREACHPAM_START(this)
//STRIP001      if( PCURCRSR->HasMark() && GetDoc()->AcceptRedline( *PCURCRSR ) )
//STRIP001          bRet = TRUE;
//STRIP001  FOREACHPAM_END()
//STRIP001  GetDoc()->EndUndo();
//STRIP001  if( !::IsExtraData( GetDoc() ) )
//STRIP001      lcl_InvalidateAll( this );
//STRIP001
//STRIP001  EndAllAction();
//STRIP001  return bRet;
//STRIP001 }

//STRIP001 BOOL SwEditShell::RejectRedline( USHORT nPos )
//STRIP001 {
//STRIP001  SET_CURR_SHELL( this );
//STRIP001  StartAllAction();
//STRIP001  BOOL bRet = GetDoc()->RejectRedline( nPos );
//STRIP001  if( !nPos && !::IsExtraData( GetDoc() ) )
//STRIP001      lcl_InvalidateAll( this );
//STRIP001  EndAllAction();
//STRIP001  return bRet;
//STRIP001 }

//STRIP001 BOOL SwEditShell::RejectRedline()
//STRIP001 {
//STRIP001  SET_CURR_SHELL( this );
//STRIP001  StartAllAction();
//STRIP001
//STRIP001  GetDoc()->StartUndo();
//STRIP001  BOOL bRet = FALSE;
//STRIP001  FOREACHPAM_START(this)
//STRIP001      if( PCURCRSR->HasMark() && GetDoc()->RejectRedline( *PCURCRSR ) )
//STRIP001          bRet = TRUE;
//STRIP001  FOREACHPAM_END()
//STRIP001  GetDoc()->EndUndo();
//STRIP001  if( !::IsExtraData( GetDoc() ) )
//STRIP001      lcl_InvalidateAll( this );
//STRIP001
//STRIP001  EndAllAction();
//STRIP001  return bRet;
//STRIP001 }

// Kommentar am Redline setzen
//STRIP001 BOOL SwEditShell::SetRedlineComment( const String& rS )
//STRIP001 {
//STRIP001  BOOL bRet = FALSE;
//STRIP001  FOREACHPAM_START(this)
//STRIP001      bRet = bRet || GetDoc()->SetRedlineComment( *PCURCRSR, rS );
//STRIP001  FOREACHPAM_END()
//STRIP001
//STRIP001  return bRet;
//STRIP001 }

//STRIP001 const SwRedline* SwEditShell::GetCurrRedline() const
//STRIP001 {
//STRIP001  return GetDoc()->GetRedline( *GetCrsr()->GetPoint() );
//STRIP001 }

//STRIP001 void SwEditShell::UpdateRedlineAttr()
//STRIP001 {
//STRIP001  if( ( REDLINE_SHOW_INSERT | REDLINE_SHOW_DELETE ) ==
//STRIP001      ( REDLINE_SHOW_MASK & GetDoc()->GetRedlineMode() ))
//STRIP001  {
//STRIP001      SET_CURR_SHELL( this );
//STRIP001      StartAllAction();
//STRIP001
//STRIP001      GetDoc()->UpdateRedlineAttr();
//STRIP001
//STRIP001      EndAllAction();
//STRIP001  }
//STRIP001 }

    // suche das Redline zu diesem Data und returne die Pos im Array
    // USHRT_MAX wird returnt, falls nicht vorhanden
//STRIP001 USHORT SwEditShell::FindRedlineOfData( const SwRedlineData& rData ) const
//STRIP001 {
//STRIP001  const SwRedlineTbl& rTbl = GetDoc()->GetRedlineTbl();
//STRIP001
//STRIP001  for( USHORT i = 0, nCnt = rTbl.Count(); i < nCnt; ++i )
//STRIP001      if( &rTbl[ i ]->GetRedlineData() == &rData )
//STRIP001          return i;
//STRIP001  return USHRT_MAX;
//STRIP001 }



}
