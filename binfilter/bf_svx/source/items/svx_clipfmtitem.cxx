/*************************************************************************
 *
 *  $RCSfile: svx_clipfmtitem.cxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:22:02 $
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

#define _SVSTDARR_ULONGS
#define _SVSTDARR_STRINGSDTOR

#include <svtools/svstdarr.hxx>
#include <clipfmtitem.hxx>



struct SvxClipboardFmtItem_Impl
{
    SvStringsDtor aFmtNms;
    SvULongs aFmtIds;
    static String sEmptyStr;

    SvxClipboardFmtItem_Impl() : aFmtNms( 8, 8 ), aFmtIds( 8, 8 ) {}
    SvxClipboardFmtItem_Impl( const SvxClipboardFmtItem_Impl& );
};

String SvxClipboardFmtItem_Impl::sEmptyStr;

/*N*/ TYPEINIT1( SvxClipboardFmtItem, SfxPoolItem );

/*N*/ SvxClipboardFmtItem_Impl::SvxClipboardFmtItem_Impl(
/*N*/                           const SvxClipboardFmtItem_Impl& rCpy )
/*N*/ {
/*N*/   aFmtIds.Insert( &rCpy.aFmtIds, 0 );
/*N*/   for( USHORT n = 0, nEnd = rCpy.aFmtNms.Count(); n < nEnd; ++n )
/*N*/   {
/*N*/       String* pStr = rCpy.aFmtNms[ n ];
/*N*/       if( pStr )
/*N*/           pStr = new String( *pStr );
/*N*/       aFmtNms.Insert( pStr, n );
/*N*/   }
/*N*/ }

/*N*/ SvxClipboardFmtItem::SvxClipboardFmtItem( USHORT nId )
/*N*/   : SfxPoolItem( nId ), pImpl( new SvxClipboardFmtItem_Impl )
/*N*/ {
/*N*/ }

/*N*/ SvxClipboardFmtItem::SvxClipboardFmtItem( const SvxClipboardFmtItem& rCpy )
/*N*/   : SfxPoolItem( rCpy.Which() ),
/*N*/   pImpl( new SvxClipboardFmtItem_Impl( *rCpy.pImpl ) )
/*N*/ {
/*N*/ }

/*N*/ SvxClipboardFmtItem::~SvxClipboardFmtItem()
/*N*/ {
/*N*/   delete pImpl;
/*N*/ }

/*N*/ int SvxClipboardFmtItem::operator==( const SfxPoolItem& rComp ) const
/*N*/ {
/*N*/   int nRet = 0;
/*N*/   const SvxClipboardFmtItem& rCmp = (SvxClipboardFmtItem&)rComp;
/*N*/   if( rCmp.pImpl->aFmtNms.Count() == pImpl->aFmtNms.Count() )
/*N*/   {
/*N*/       nRet = 1;
/*N*/       const String* pStr1, *pStr2;
/*N*/       for( USHORT n = 0, nEnd = rCmp.pImpl->aFmtNms.Count(); n < nEnd; ++n )
/*N*/       {
/*N*/           if( pImpl->aFmtIds[ n ] != rCmp.pImpl->aFmtIds[ n ] ||
/*N*/               ( (0 == ( pStr1 = pImpl->aFmtNms[ n ] )) ^
/*N*/                 (0 == ( pStr2 = rCmp.pImpl->aFmtNms[ n ] ) )) ||
/*N*/               ( pStr1 && *pStr1 != *pStr2 ))
/*N*/           {
/*N*/               nRet = 0;
/*N*/               break;
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/   return nRet;
/*N*/ }

/*N*/ SfxPoolItem* SvxClipboardFmtItem::Clone( SfxItemPool *pPool ) const
/*N*/ {
/*N*/   return new SvxClipboardFmtItem( *this );
/*N*/ }

/*N*/ void SvxClipboardFmtItem::AddClipbrdFormat( ULONG nId, USHORT nPos )
/*N*/ {
/*N*/   if( nPos > pImpl->aFmtNms.Count() )
/*N*/       nPos = pImpl->aFmtNms.Count();
/*N*/   String* pStr = 0;
/*N*/   pImpl->aFmtNms.Insert( pStr, nPos );
/*N*/   pImpl->aFmtIds.Insert( nId, nPos );
/*N*/ }

/*N*/ void SvxClipboardFmtItem::AddClipbrdFormat( ULONG nId, const String& rName,
/*N*/                           USHORT nPos )
/*N*/ {
/*N*/   if( nPos > pImpl->aFmtNms.Count() )
/*N*/       nPos = pImpl->aFmtNms.Count();
/*N*/   String* pStr = new String( rName );
/*N*/   pImpl->aFmtNms.Insert( pStr, nPos );
/*N*/   pImpl->aFmtIds.Insert( nId, nPos );
/*N*/ }

/*N*/ USHORT SvxClipboardFmtItem::Count() const
/*N*/ {
/*N*/   return pImpl->aFmtIds.Count();
/*N*/ }

//STRIP001 ULONG SvxClipboardFmtItem::GetClipbrdFormatId( USHORT nPos ) const
//STRIP001 {
//STRIP001  return pImpl->aFmtIds[ nPos ];
//STRIP001 }

//STRIP001 const String& SvxClipboardFmtItem::GetClipbrdFormatName( USHORT nPos ) const
//STRIP001 {
//STRIP001  const String* pS = pImpl->aFmtNms[ nPos ];
//STRIP001  return pS ? *pS : SvxClipboardFmtItem_Impl::sEmptyStr;
//STRIP001 }


