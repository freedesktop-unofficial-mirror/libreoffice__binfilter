/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_docruby.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-27 22:25:09 $
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

#include <string.h>         // fuer strchr()


#ifndef _COM_SUN_STAR_I18N_UNICODETYPE_HDL
#include <com/sun/star/i18n/UnicodeType.hdl>
#endif
#ifndef _COM_SUN_STAR_I18N_WORDTYPE_HDL
#include <com/sun/star/i18n/WordType.hdl>
#endif

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif
#ifndef _ERRHDL_HXX
#include <errhdl.hxx>
#endif

#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _RUBYLIST_HXX
#include <rubylist.hxx>
#endif
#ifndef _PAM_HXX
#include <pam.hxx>
#endif
namespace binfilter {

/*N*/ SV_IMPL_PTRARR( SwRubyList, SwRubyListEntryPtr )

using namespace ::com::sun::star::i18n;


/*
 * Members in the list:
 *   - String - the orig text
 *   - SwFmtRuby - the ruby attribut
 *
 *
 */
/*N*/ USHORT SwDoc::FillRubyList( const SwPaM& rPam, SwRubyList& rList,
/*N*/                           USHORT nMode )
/*N*/ {
/*N*/   const SwPaM *_pStartCrsr = (SwPaM*)rPam.GetNext(),
/*N*/               *__pStartCrsr = _pStartCrsr;
/*N*/   BOOL bCheckEmpty = &rPam != _pStartCrsr;
/*N*/   do {
/*N*/       const SwPosition* pStt = _pStartCrsr->Start(),
/*N*/                       * pEnd = pStt == _pStartCrsr->GetPoint()
/*N*/                                               ? _pStartCrsr->GetMark()
/*N*/                                               : _pStartCrsr->GetPoint();
/*N*/       if( !bCheckEmpty || ( pStt != pEnd && *pStt != *pEnd ))
/*N*/       {
/*N*/           SwPaM aPam( *pStt );
/*N*/           do {
/*N*/               SwRubyListEntry* pNew = new SwRubyListEntry;
/*N*/               if( pEnd != pStt )
/*N*/               {
/*N*/                   aPam.SetMark();
/*N*/                   *aPam.GetMark() = *pEnd;
/*N*/               }
/*N*/               if( _SelectNextRubyChars( aPam, *pNew, nMode ))
/*N*/               {
/*N*/                   rList.Insert( pNew, rList.Count() );
/*N*/                   aPam.DeleteMark();
/*N*/               }
/*N*/               else
/*N*/               {
/*N*/                   delete pNew;
/*N*/                   if( *aPam.GetPoint() < *pEnd )
/*N*/                   {
/*N*/                       // goto next paragraph
/*N*/                       aPam.DeleteMark();
/*N*/                       aPam.Move( fnMoveForward, fnGoNode );
/*N*/                   }
/*N*/                   else
/*N*/                       break;
/*N*/               }
/*N*/           } while( 30 > rList.Count() && *aPam.GetPoint() < *pEnd );
/*N*/       }
/*N*/   } while( 30 > rList.Count() &&
/*N*/       (_pStartCrsr=(SwPaM *)_pStartCrsr->GetNext()) != __pStartCrsr );
/*N*/
/*N*/   return rList.Count();
/*N*/ }

/*N*/ USHORT SwDoc::SetRubyList( const SwPaM& rPam, const SwRubyList& rList,
/*N*/                           USHORT nMode )
/*N*/ {
/*?*/   DBG_BF_ASSERT(0, "STRIP"); return 0;//STRIP001 StartUndo( UNDO_SETRUBYATTR );
/*N*/ }

/*N*/ BOOL SwDoc::_SelectNextRubyChars( SwPaM& rPam, SwRubyListEntry& rEntry,
/*N*/                                   USHORT nMode )
/*N*/ {
    DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001 // Point must be the startposition, Mark is optional the end position
/*N*/ }

/*N*/SwRubyListEntry::~SwRubyListEntry()
/*N*/{
/*N*/}
}
