/*************************************************************************
 *
 *  $RCSfile: sfx2_frmdescr.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: aw $ $Date: 2003-11-18 19:23:21 $
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

#include <sot/object.hxx>

#ifndef _STREAM_HXX //autogen
#include <tools/stream.hxx>
#endif
#ifndef _SV_SPLITWIN_HXX //autogen
#include <vcl/splitwin.hxx>
#endif
#ifndef _SFXITEMSET_HXX //autogen
#include <svtools/itemset.hxx>
#endif
#pragma hdrstop

#include "frmdescr.hxx"
#include "app.hxx"
namespace binfilter {

/*N*/ DBG_NAME(SfxFrameSetDescriptor)
/*N*/ DBG_NAME(SfxFrameDescriptor)

#define VERSION (USHORT) 3

/*N*/ struct SfxFrameSetDescriptor_Impl
/*N*/ {
/*N*/   Wallpaper*  pWallpaper;
/*N*/   Bitmap*     pBitmap;
/*N*/   BOOL        bNetscapeCompat;
/*N*/ };

/*N*/ struct SfxFrameDescriptor_Impl
/*N*/ {
/*N*/   Wallpaper*  pWallpaper;
/*N*/   SfxItemSet* pArgs;
/*N*/   BOOL        bEditable;
/*N*/
/*N*/   SfxFrameDescriptor_Impl() : pWallpaper( NULL ), pArgs( NULL ), bEditable( TRUE ) {}
/*N*/   ~SfxFrameDescriptor_Impl()
/*N*/   {
/*N*/       delete pWallpaper;
/*N*/       delete pArgs;
/*N*/   }
/*N*/ };

/*N*/ SfxFrameSetDescriptor::SfxFrameSetDescriptor(SfxFrameDescriptor *pFrame) :
/*N*/   pParentFrame( pFrame ),
/*N*/   nFrameSpacing( SPACING_NOT_SET ),
/*N*/   bIsRoot( pParentFrame ? (pParentFrame->pParentFrameSet == 0) : TRUE ),
/*N*/   bRowSet( FALSE ),
/*N*/   nMaxId( 0 ),
/*N*/   nHasBorder( BORDER_YES )
/*N*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  DBG_CTOR(SfxFrameSetDescriptor, 0);
//STRIP001
//STRIP001  pImp = new SfxFrameSetDescriptor_Impl;
//STRIP001  pImp->pBitmap = NULL;
//STRIP001  pImp->pWallpaper = NULL;
//STRIP001  pImp->bNetscapeCompat = TRUE;
//STRIP001  if ( pParentFrame )
//STRIP001      pParentFrame->pFrameSet = this;
//STRIP001  if ( bIsRoot )
//STRIP001      nHasBorder |= BORDER_SET;
/*N*/ }

//STRIP001 SfxFrameSetDescriptor::~SfxFrameSetDescriptor()
//STRIP001 {
//STRIP001  DBG_DTOR(SfxFrameSetDescriptor, 0);
//STRIP001
//STRIP001  for ( USHORT n=0; n<aFrames.Count(); n++ )
//STRIP001  {
//STRIP001      SfxFrameDescriptor *pFrame = aFrames[n];
//STRIP001      pFrame->pParentFrameSet = NULL;
//STRIP001      delete pFrame;
//STRIP001  }
//STRIP001  if ( pParentFrame )
//STRIP001      pParentFrame->pFrameSet = NULL;
//STRIP001  delete pImp;
//STRIP001 }
//STRIP001
//STRIP001 SfxFrameDescriptor* SfxFrameSetDescriptor::SearchFrame( USHORT nId )
//STRIP001 {
//STRIP001  for ( USHORT n=0; n<aFrames.Count(); n++ )
//STRIP001  {
//STRIP001      SfxFrameDescriptor *pFrame = aFrames[n];
//STRIP001      if ( pFrame->nItemId == nId )
//STRIP001          return pFrame;
//STRIP001      if ( pFrame->GetFrameSet() )
//STRIP001      {
//STRIP001          pFrame = pFrame->GetFrameSet()->SearchFrame( nId );
//STRIP001          if ( pFrame )
//STRIP001              return pFrame;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  return NULL;
//STRIP001 }
//STRIP001
//STRIP001 SfxFrameDescriptor* SfxFrameSetDescriptor::SearchFrame( const String& rName )
//STRIP001 {
//STRIP001  for ( USHORT n=0; n<aFrames.Count(); n++ )
//STRIP001  {
//STRIP001      SfxFrameDescriptor *pFrame = aFrames[n];
//STRIP001      if ( pFrame->aName == rName )
//STRIP001          return pFrame;
//STRIP001      if ( pFrame->GetFrameSet() )
//STRIP001      {
//STRIP001          pFrame = pFrame->GetFrameSet()->SearchFrame( rName );
//STRIP001          if ( pFrame )
//STRIP001              return pFrame;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  return NULL;
//STRIP001 }
//STRIP001
//STRIP001 void SfxFrameSetDescriptor::InsertFrame
//STRIP001 (
//STRIP001  SfxFrameDescriptor* pFrame,
//STRIP001  USHORT nPos
//STRIP001 )
//STRIP001 {
//STRIP001  // complicated SvPtrArrs ...
//STRIP001  if ( nPos == 0xFFFF )
//STRIP001      nPos = aFrames.Count();
//STRIP001
//STRIP001  aFrames.Insert( pFrame, nPos );
//STRIP001  pFrame->pParentFrameSet = this;
//STRIP001 }
//STRIP001
//STRIP001 void SfxFrameSetDescriptor::RemoveFrame( SfxFrameDescriptor* pFrame )
//STRIP001 {
//STRIP001  USHORT nPos = aFrames.GetPos( pFrame );
//STRIP001  DBG_ASSERT( nPos != 0xFFFF, "Unbekannter Frame!" );
//STRIP001  aFrames.Remove( nPos );
//STRIP001  pFrame->pParentFrameSet = 0L;
//STRIP001 }
//STRIP001
/*N*/ BOOL SfxFrameSetDescriptor::HasFrameBorder() const
/*N*/ {DBG_ASSERT(0, "STRIP");return FALSE; //STRIP001
//STRIP001  if ( pImp->bNetscapeCompat && !GetFrameSpacing() )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  if ( ( nHasBorder & BORDER_SET ) || bIsRoot )
//STRIP001      return (nHasBorder & BORDER_YES) != 0;
//STRIP001  else
//STRIP001      return pParentFrame->HasFrameBorder();
/*N*/ }

//STRIP001 //------------------------------------------------------------------------
//STRIP001
//STRIP001 void SfxFrameSetDescriptor::SetNetscapeCompatibility( BOOL bCompat )
//STRIP001 // Frame-Spacing Verhalten wenn kein Border
//STRIP001 {
//STRIP001  pImp->bNetscapeCompat = bCompat;
//STRIP001 }
//STRIP001
//STRIP001 //------------------------------------------------------------------------
//STRIP001
//STRIP001 BOOL SfxFrameSetDescriptor::GetNetscapeCompatibility() const
//STRIP001 // Frame-Spacing Verhalten wenn kein Border
//STRIP001 {
//STRIP001  return pImp->bNetscapeCompat;
//STRIP001 }
//STRIP001
//STRIP001 //------------------------------------------------------------------------
//STRIP001
//STRIP001 long SfxFrameSetDescriptor::GetFrameSpacing() const
//STRIP001 {
//STRIP001  if ( nFrameSpacing == SPACING_NOT_SET && !bIsRoot &&
//STRIP001          pParentFrame && pParentFrame->pParentFrameSet )
//STRIP001  {
//STRIP001      return pParentFrame->pParentFrameSet->GetFrameSpacing();
//STRIP001  }
//STRIP001  else
//STRIP001      return nFrameSpacing;
//STRIP001 }
//STRIP001
//STRIP001 BOOL SfxFrameSetDescriptor::Store( SvStream& rStream ) const
//STRIP001 {
//STRIP001  // Die "0" ist wg. Kompatibilit"at zu alten Versionen n"otig. Diese
//STRIP001  // glauben dann, ein leeres Frameset zu lesen und st"urzen dann
//STRIP001  // wenigstens nicht ab.
//STRIP001  long lLength = 20;
//STRIP001  rStream << VERSION << lLength << (USHORT) 0 << (USHORT) 0;
//STRIP001  rStream << nHasBorder
//STRIP001          << nFrameSpacing
//STRIP001          << (USHORT) bRowSet
//STRIP001          << aFrames.Count();
//STRIP001
//STRIP001  for ( USHORT n=0; n<aFrames.Count(); n++ )
//STRIP001  {
//STRIP001      SfxFrameDescriptor* pFrame = aFrames[n];
//STRIP001      pFrame->Store( rStream );
//STRIP001  }
//STRIP001  return TRUE;
//STRIP001 }
//STRIP001
//STRIP001 BOOL SfxFrameSetDescriptor::Load( SvStream& rStream )
//STRIP001 {
//STRIP001  long lPos = rStream.Tell();             // aktuelle Position merken
//STRIP001  USHORT nCount=0, nHorizontal;
//STRIP001  rStream >> nHasBorder
//STRIP001          >> nFrameSpacing
//STRIP001          >> nHorizontal
//STRIP001          >> nCount;
//STRIP001
//STRIP001  if ( nCount == 0 )
//STRIP001  {
//STRIP001      // Das mu\s ein neues Format sein, da ein Frame normalerweise immer
//STRIP001      // dabei ist
//STRIP001      USHORT nVersion = nHasBorder;
//STRIP001      rStream.Seek( lPos );
//STRIP001      return Load( rStream, nVersion );
//STRIP001  }
//STRIP001
//STRIP001  bRowSet = (BOOL) nHorizontal;
//STRIP001  for ( USHORT n=0; n<nCount; n++ )
//STRIP001  {
//STRIP001      SfxFrameDescriptor *pFrame = new SfxFrameDescriptor( this );
//STRIP001      pFrame->Load( rStream, 2 );
//STRIP001  }
//STRIP001  return TRUE;
//STRIP001 }
//STRIP001
//STRIP001 BOOL SfxFrameSetDescriptor::Load( SvStream& rStream, USHORT nVersion )
//STRIP001 {
//STRIP001  long lLength = 10;                      // in Version 2
//STRIP001  long lPos = rStream.Tell();             // aktuelle Position merken
//STRIP001
//STRIP001  USHORT nCount=0, nHorizontal, nDummy1, nDummy2;
//STRIP001  if ( nVersion > 2 )
//STRIP001      // In der final Version
//STRIP001      rStream >> nVersion >> lLength >> nDummy1 >> nDummy2;
//STRIP001
//STRIP001  rStream >> nHasBorder
//STRIP001          >> nFrameSpacing
//STRIP001          >> nHorizontal
//STRIP001          >> nCount;
//STRIP001
//STRIP001  rStream.Seek( lPos + lLength );
//STRIP001
//STRIP001  bRowSet = (BOOL) nHorizontal;
//STRIP001  for ( USHORT n=0; n<nCount; n++ )
//STRIP001  {
//STRIP001      SfxFrameDescriptor *pFrame = new SfxFrameDescriptor( this );
//STRIP001      pFrame->Load( rStream, nVersion );
//STRIP001  }
//STRIP001  return TRUE;
//STRIP001 }
//STRIP001
//STRIP001 void SfxFrameSetDescriptor::SetWallpaper( const Wallpaper& rWallpaper )
//STRIP001 {
//STRIP001  DELETEZ( pImp->pWallpaper );
//STRIP001
//STRIP001  if ( rWallpaper.GetStyle() != WALLPAPER_NULL )
//STRIP001      pImp->pWallpaper = new Wallpaper( rWallpaper );
//STRIP001 }
//STRIP001
//STRIP001 const Wallpaper* SfxFrameSetDescriptor::GetWallpaper() const
//STRIP001 {
//STRIP001  return pImp->pWallpaper;
//STRIP001 }
//STRIP001
//STRIP001 SfxFrameSetDescriptor* SfxFrameSetDescriptor::Clone(
//STRIP001  SfxFrameDescriptor *pFrame, BOOL bWithIds ) const
//STRIP001 {
//STRIP001  SfxFrameSetDescriptor *pSet = new SfxFrameSetDescriptor( pFrame );
//STRIP001
//STRIP001  for ( USHORT n=0; n<aFrames.Count(); n++ )
//STRIP001      SfxFrameDescriptor* pFrame = aFrames[n]->Clone( pSet, bWithIds );
//STRIP001
//STRIP001  pSet->aDocumentTitle = aDocumentTitle;
//STRIP001  pSet->nFrameSpacing = nFrameSpacing;
//STRIP001  pSet->nHasBorder = nHasBorder;
//STRIP001  pSet->nMaxId = nMaxId;
//STRIP001  pSet->bIsRoot = bIsRoot;
//STRIP001  pSet->bRowSet = bRowSet;
//STRIP001  if ( pImp->pWallpaper )
//STRIP001      pSet->pImp->pWallpaper = new Wallpaper( *pImp->pWallpaper );
//STRIP001  pSet->pImp->bNetscapeCompat = pImp->bNetscapeCompat;
//STRIP001
//STRIP001  return pSet;
//STRIP001 }
//STRIP001
//STRIP001 BOOL SfxFrameSetDescriptor::CheckContent() const
//STRIP001 {
//STRIP001  BOOL bRet=FALSE;
//STRIP001  for ( USHORT n=0; n<aFrames.Count(); n++ )
//STRIP001      if ( bRet = aFrames[n]->CheckContent() )
//STRIP001          break;
//STRIP001  return bRet;
//STRIP001 }
//STRIP001
//STRIP001 BOOL SfxFrameSetDescriptor::CompareOriginal(
//STRIP001  SfxFrameSetDescriptor& rDescr ) const
//STRIP001 {
//STRIP001  if( aFrames.Count() != rDescr.aFrames.Count() )
//STRIP001      return FALSE;
//STRIP001  else
//STRIP001      for( USHORT nPos = aFrames.Count(); nPos--; )
//STRIP001          if( !aFrames[ nPos ]->CompareOriginal(
//STRIP001              *rDescr.aFrames[ nPos ] ) )
//STRIP001              return FALSE;
//STRIP001  return TRUE;
//STRIP001 }
//STRIP001
//STRIP001
//STRIP001 void SfxFrameSetDescriptor::UnifyContent( BOOL bTakeActual )
//STRIP001 {
//STRIP001  for ( USHORT n=0; n<aFrames.Count(); n++ )
//STRIP001      aFrames[n]->UnifyContent( bTakeActual );
//STRIP001 }
//STRIP001
//STRIP001 void SfxFrameSetDescriptor::CutRootSet()
//STRIP001 {
//STRIP001  for ( USHORT n=0; n<aFrames.Count(); n++ )
//STRIP001  {
//STRIP001      SfxFrameDescriptor* pFrame = aFrames[n];
//STRIP001      SfxFrameSetDescriptor *pSet = pFrame->GetFrameSet();
//STRIP001      if ( pSet )
//STRIP001      {
//STRIP001          if ( pSet->bIsRoot )
//STRIP001          {
//STRIP001              delete pSet;
//STRIP001              pFrame->pFrameSet = NULL;
//STRIP001          }
//STRIP001          else
//STRIP001              pSet->CutRootSet();
//STRIP001      }
//STRIP001  }
//STRIP001 }
//STRIP001
//STRIP001 USHORT SfxFrameSetDescriptor::MakeItemId()
//STRIP001 {
//STRIP001  if ( pParentFrame && pParentFrame->pParentFrameSet )
//STRIP001      return pParentFrame->pParentFrameSet->MakeItemId();
//STRIP001  else
//STRIP001      return ++nMaxId;
//STRIP001 }

/*N*/ SfxFrameDescriptor::SfxFrameDescriptor( SfxFrameSetDescriptor *pParSet ) :
/*N*/   aMargin( -1, -1 ),
/*N*/   nWidth( 0L ),
/*N*/   nItemId( 0 ),
/*N*/   pFrameSet( 0L ),
/*N*/   pParentFrameSet( pParSet ),
/*N*/   eScroll( ScrollingAuto ),
/*N*/   eSizeSelector( SIZE_ABS ),
/*N*/   nHasBorder( BORDER_YES ),
/*N*/   bResizeHorizontal( TRUE ),
/*N*/   bResizeVertical( TRUE ),
/*N*/   bHasUI( TRUE ),
/*N*/   bReadOnly( FALSE )
/*N*/ {
/*N*/   DBG_CTOR(SfxFrameDescriptor, 0);
/*N*/
/*N*/   pImp = new SfxFrameDescriptor_Impl;
/*N*/   if ( pParentFrameSet )
/*?*/   {DBG_ASSERT(0, "STRIP"); }//STRIP001    pParentFrameSet->InsertFrame( this );
/*N*/ }

/*N*/ SfxFrameDescriptor::~SfxFrameDescriptor()
/*N*/ {
/*N*/   DBG_DTOR(SfxFrameDescriptor, 0);
/*N*/
/*N*/   if ( pFrameSet )
/*N*/       delete pFrameSet;
/*N*/   if ( pParentFrameSet )
/*?*/       {DBG_ASSERT(0, "STRIP");} //STRIP001 pParentFrameSet->RemoveFrame( this );
/*N*/   delete pImp;
/*N*/ }

/*N*/ SfxItemSet* SfxFrameDescriptor::GetArgs()
/*N*/ {
/*N*/   if( !pImp->pArgs )
/*N*/       pImp->pArgs = new SfxAllItemSet( SFX_APP()->GetPool() );
/*N*/   return pImp->pArgs;
/*N*/ }

/*?*/ void SfxFrameDescriptor::SetURL( const String& rURL )
/*?*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  aURL = rURL;
//STRIP001  SetActualURL( aURL );
//STRIP001 }
//STRIP001
//STRIP001 void SfxFrameDescriptor::SetURL( const INetURLObject& rURL )
//STRIP001 {
//STRIP001  aURL = rURL.GetMainURL( INetURLObject::DECODE_TO_IURI );
//STRIP001  SetActualURL( aURL );
/*?*/ }

/*N*/ void SfxFrameDescriptor::SetActualURL( const String& rURL )
/*N*/ {
/*N*/   aActualURL = rURL;
/*N*/   if ( pImp->pArgs )
/*?*/       pImp->pArgs->ClearItem();
/*N*/ }

/*?*/ void SfxFrameDescriptor::SetActualURL( const INetURLObject& rURL )
/*?*/ {
/*?*/   SetActualURL( rURL.GetMainURL( INetURLObject::DECODE_TO_IURI ) );
/*?*/ }

/*N*/ void SfxFrameDescriptor::SetEditable( BOOL bSet )
/*N*/ {
/*N*/   pImp->bEditable = bSet;
/*N*/ }

/*N*/ BOOL SfxFrameDescriptor::IsEditable() const
/*N*/ {
/*N*/   return pImp->bEditable;
/*N*/ }

//STRIP001 BOOL SfxFrameDescriptor::CompareOriginal( SfxFrameDescriptor& rDescr ) const
//STRIP001 {
//STRIP001  if( aURL != rDescr.aURL )
//STRIP001      return FALSE;
//STRIP001  else
//STRIP001      // Zwei Descriptoren sind kompatibel, wenn einer keinen SetDescriptor
//STRIP001      // und der andere einen RootDescriptor hat,
//STRIP001      // wenn beide SetDescriptoren haben
//STRIP001      // und diese kompatibel sind oder wenn beide keine
//STRIP001      // SetDescriptoren haben.
//STRIP001      return
//STRIP001          !pFrameSet &&
//STRIP001          ( !rDescr.pFrameSet || rDescr.pFrameSet->IsRootFrameSet() ) ||
//STRIP001          !rDescr.pFrameSet && pFrameSet->IsRootFrameSet() ||
//STRIP001          pFrameSet && rDescr.pFrameSet && pFrameSet->CompareOriginal(
//STRIP001              *rDescr.pFrameSet );
//STRIP001 }
//STRIP001
//STRIP001 BOOL SfxFrameDescriptor::CheckContent() const
//STRIP001 {
//STRIP001  BOOL bRet = !( aURL == aActualURL );
//STRIP001  if ( !bRet && pFrameSet )
//STRIP001      bRet = pFrameSet->CheckContent();
//STRIP001  return bRet;
//STRIP001 }
//STRIP001
//STRIP001 void SfxFrameDescriptor::UnifyContent( BOOL bTakeActual )
//STRIP001 {
//STRIP001  if ( bTakeActual )
//STRIP001      aURL = aActualURL;
//STRIP001  else
//STRIP001      aActualURL = aURL;
//STRIP001  if ( pFrameSet )
//STRIP001      pFrameSet->UnifyContent( bTakeActual );
//STRIP001 }

/*N*/ BOOL SfxFrameDescriptor::Store( SvStream& rStream ) const
/*N*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  long lPos = rStream.Tell();
//STRIP001  long lLength = 0L;
//STRIP001  rStream << lLength << VERSION;
//STRIP001
//STRIP001  USHORT nFlags1 = 0;
//STRIP001  USHORT nFlags2 = 0;
//STRIP001  if ( bResizeHorizontal )
//STRIP001      nFlags1 |= 0x01;
//STRIP001  if ( bResizeVertical )
//STRIP001      nFlags2 |= 0x01;
//STRIP001  if ( !bHasUI )              // anders herum, damit kompatibel
//STRIP001      nFlags1 |= 0x02;
//STRIP001  if ( bReadOnly )
//STRIP001      nFlags1 |= 0x04;
//STRIP001
//STRIP001  if ( aURL.GetMainURL(INetURLObject::DECODE_TO_IURI).Len() )
//STRIP001  {
//STRIP001      rStream.WriteByteString( INetURLObject::AbsToRel( aURL.GetMainURL(
//STRIP001                  INetURLObject::DECODE_TO_IURI ) ), RTL_TEXTENCODING_UTF8 );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      rStream.WriteByteString( String(), RTL_TEXTENCODING_UTF8 );
//STRIP001  }
//STRIP001
//STRIP001  rStream.WriteByteString( aName, RTL_TEXTENCODING_UTF8 );
//STRIP001  rStream << aMargin
//STRIP001          << nWidth
//STRIP001          << (USHORT) eSizeSelector
//STRIP001          << (USHORT) eScroll
//STRIP001          << (USHORT) nFlags1
//STRIP001          << (USHORT) nFlags2
//STRIP001          << (USHORT) (pFrameSet != 0)
//STRIP001          << nHasBorder;
//STRIP001
//STRIP001  long lActPos = rStream.Tell();
//STRIP001  lLength = lActPos - lPos;
//STRIP001  rStream.Seek( lPos );
//STRIP001  rStream << lLength;
//STRIP001  rStream.Seek( lActPos );
//STRIP001
//STRIP001  if ( pFrameSet )
//STRIP001      pFrameSet->Store(rStream);
//STRIP001
/*N*/   return TRUE;
/*N*/ }

/*N*/ BOOL SfxFrameDescriptor::Load( SvStream& rStream, USHORT nVersion )
/*N*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  String aURLName;
//STRIP001  USHORT nFlags1, nFlags2, nScroll, nSet, nSelector;
//STRIP001
//STRIP001  long lLength = 0L;
//STRIP001  long lPos = rStream.Tell();     // aktuelle Position merken
//STRIP001
//STRIP001  if ( nVersion > 2 )
//STRIP001      rStream >> lLength >> nVersion;
//STRIP001
//STRIP001  rStream.ReadByteString( aURLName, RTL_TEXTENCODING_UTF8 );
//STRIP001  rStream.ReadByteString( aName, RTL_TEXTENCODING_UTF8 );
//STRIP001  rStream >> aMargin
//STRIP001          >> nWidth
//STRIP001          >> nSelector
//STRIP001          >> nScroll
//STRIP001          >> nFlags1
//STRIP001          >> nFlags2
//STRIP001          >> nSet
//STRIP001          >> nHasBorder;
//STRIP001
//STRIP001  if ( nVersion > 2 )
//STRIP001      rStream.Seek( lPos + lLength );
//STRIP001
//STRIP001  bResizeHorizontal = ( nFlags1 & 0x01 ) != 0;
//STRIP001  bResizeVertical = ( nFlags2 & 0x01 ) != 0;
//STRIP001  bHasUI = ( nFlags1 & 0x02 ) == 0;
//STRIP001  bReadOnly = ( nFlags1 & 0x04 ) != 0;
//STRIP001  eSizeSelector = (SizeSelector) nSelector;
//STRIP001  aURL = INetURLObject::RelToAbs( aURLName );
//STRIP001  eScroll = (ScrollingMode) nScroll;
//STRIP001  aActualURL = aURL;
//STRIP001
//STRIP001  if ( nSet )
//STRIP001  {
//STRIP001      pFrameSet = new SfxFrameSetDescriptor( this );
//STRIP001      pFrameSet->Load( rStream, nVersion );
//STRIP001  }
//STRIP001
/*N*/   return TRUE;
/*N*/ }

/*N*/ SfxFrameDescriptor* SfxFrameDescriptor::Clone(
/*N*/   SfxFrameSetDescriptor *pSet, BOOL bWithIds ) const
/*N*/ {DBG_ASSERT(0, "STRIP"); return 0;//STRIP001
//STRIP001  SfxFrameDescriptor *pFrame =
//STRIP001      new SfxFrameDescriptor( pSet );
//STRIP001
//STRIP001  pFrame->aURL = aURL;
//STRIP001  pFrame->aActualURL = aActualURL;
//STRIP001  pFrame->aName = aName;
//STRIP001  pFrame->aMargin = aMargin;
//STRIP001  pFrame->nWidth = nWidth;
//STRIP001  pFrame->eSizeSelector = eSizeSelector;
//STRIP001  pFrame->eScroll = eScroll;
//STRIP001  pFrame->bResizeHorizontal = bResizeHorizontal;
//STRIP001  pFrame->bResizeVertical = bResizeVertical;
//STRIP001  pFrame->nHasBorder = nHasBorder;
//STRIP001  pFrame->bHasUI = bHasUI;
//STRIP001  pFrame->SetReadOnly( IsReadOnly() );
//STRIP001  pFrame->SetEditable( IsEditable() );
//STRIP001  if ( pImp->pWallpaper )
//STRIP001      pFrame->pImp->pWallpaper = new Wallpaper( *pImp->pWallpaper );
//STRIP001  if( pImp->pArgs )
//STRIP001  {
//STRIP001      // Aktuell ist im Clone von SfxAllItemSets noch ein Bug...
//STRIP001      pFrame->pImp->pArgs = new SfxAllItemSet( SFX_APP()->GetPool() );
//STRIP001      pFrame->pImp->pArgs->Put(*pImp->pArgs);
//STRIP001  }
//STRIP001
//STRIP001  if ( bWithIds )
//STRIP001      pFrame->nItemId = nItemId;
//STRIP001  else
//STRIP001      pFrame->nItemId = 0;
//STRIP001
//STRIP001  if ( pFrameSet )
//STRIP001      pFrame->pFrameSet = pFrameSet->Clone( pFrame, bWithIds );
//STRIP001
//STRIP001  return pFrame;
/*N*/ }


//STRIP001 SfxFrameDescriptor* SfxFrameDescriptor::Split( BOOL bHorizontal, BOOL bParent )
//STRIP001 {
//STRIP001  DBG_ASSERT( pParentFrameSet, "Frames ohne Set koennen nicht gesplittet werden!" );
//STRIP001
//STRIP001  // Die Root holen, um neue Ids erzeugen zu k"onnen
//STRIP001  SfxFrameSetDescriptor *pRoot = pParentFrameSet;
//STRIP001  while ( pRoot->pParentFrame && pRoot->pParentFrame->pParentFrameSet )
//STRIP001      pRoot = pRoot->pParentFrame->pParentFrameSet;
//STRIP001
//STRIP001  // Der Frame, hinter dem ein neuer eingef"ugt werden soll
//STRIP001  SfxFrameDescriptor *pPrev = this;
//STRIP001
//STRIP001  // Dieser Descriptor soll gesplittet werden ...
//STRIP001  SfxFrameDescriptor *pSplit = this;
//STRIP001  SfxFrameSetDescriptor *pSplitSet = pParentFrameSet;
//STRIP001
//STRIP001  if ( bParent )
//STRIP001  {
//STRIP001      // Ein FrameSet suchen, das die gleiche Orientierung hat wie
//STRIP001      // die "ubergebene
//STRIP001      pSplit = pSplitSet->bIsRoot ? NULL : pSplitSet->pParentFrame;
//STRIP001      while ( pSplit && pSplit->pParentFrameSet )
//STRIP001      {
//STRIP001          pSplitSet = pSplit->pParentFrameSet;
//STRIP001          if ( pSplitSet->bRowSet == bHorizontal )
//STRIP001              break;
//STRIP001          pSplit = pSplitSet->pParentFrame;
//STRIP001      }
//STRIP001
//STRIP001      // pSplit ist NULL oder TopLevel, wenn das Set das RootSet ist
//STRIP001      pPrev = pSplit;
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      // Wenn das aktuelle FrameSet eine andere Orientierung hat, der
//STRIP001      // zu splittende Frame aber der einzige ist, wird einfach die
//STRIP001      // Orientierung des Sets umgedreht( k"urzt den Baum)
//STRIP001      if ( pSplitSet->GetFrameCount() == 1 )
//STRIP001          pSplitSet->bRowSet = bHorizontal;
//STRIP001  }
//STRIP001
//STRIP001  if ( pSplitSet->bRowSet != bHorizontal )
//STRIP001  {
//STRIP001      BOOL bCreated = FALSE;
//STRIP001      if ( !pSplit || !pSplit->pParentFrameSet )
//STRIP001      {
//STRIP001          // RootSet splitten: das Alignment wechselt
//STRIP001          pSplitSet->bRowSet = bHorizontal;
//STRIP001          bHorizontal = !bHorizontal;
//STRIP001          pSplit = new SfxFrameDescriptor( pSplitSet );
//STRIP001          bCreated = TRUE;
//STRIP001      }
//STRIP001
//STRIP001      if ( bParent )
//STRIP001      {
//STRIP001          // "Unter pSplit wird ein FrameSet eingef"ugt
//STRIP001          SfxFrameSetDescriptor *pSet = new SfxFrameSetDescriptor( NULL );
//STRIP001          pSet->bIsRoot = FALSE;
//STRIP001          pSet->bRowSet = bHorizontal;
//STRIP001
//STRIP001          // Die Frames unterhalb des alten Sets umh"angen
//STRIP001          USHORT nCount = pSplitSet->aFrames.Count();
//STRIP001          USHORT nPos = 0;
//STRIP001          for ( USHORT n=0; n<nCount; n++ )
//STRIP001          {
//STRIP001              SfxFrameDescriptor *pCur = pSplitSet->aFrames[0];
//STRIP001              if ( pCur != pSplit )
//STRIP001              {
//STRIP001                  pSplitSet->aFrames.Remove(nPos);
//STRIP001                  pSet->InsertFrame( pCur );
//STRIP001                  pCur->pParentFrameSet = pSet;
//STRIP001              }
//STRIP001              else
//STRIP001                  nPos++;
//STRIP001          }
//STRIP001
//STRIP001          pPrev = pSplit;
//STRIP001
//STRIP001          if ( bCreated )
//STRIP001          {
//STRIP001              USHORT nID = pRoot->MakeItemId();
//STRIP001              pSplit->SetItemId( nID );
//STRIP001
//STRIP001              // Neuer Frame erh"alt ganzen Platz
//STRIP001              pPrev->nWidth = 100;
//STRIP001              pPrev->eSizeSelector = SIZE_PERCENT;
//STRIP001
//STRIP001              // Verkettung herstellen
//STRIP001              pSplit->pFrameSet = pSet;
//STRIP001              pSet->pParentFrame = pSplit;
//STRIP001          }
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          // Den gesplitteten Frame kopieren und moven
//STRIP001          USHORT nPos = pSplitSet->aFrames.GetPos( pPrev );
//STRIP001          pSplit = pPrev->Clone( pSplitSet );
//STRIP001          pSplitSet->RemoveFrame( pSplit );
//STRIP001          pSplitSet->InsertFrame( pSplit, nPos );
//STRIP001
//STRIP001          // Unter dem neuen Frame wird ein FrameSet eingef"ugt, das den
//STRIP001          // alten Frame enth"alt, der anschlie\send geteilt wird
//STRIP001          SfxFrameSetDescriptor *pSet = new SfxFrameSetDescriptor( pSplit );
//STRIP001          pSet->bIsRoot = FALSE;
//STRIP001          pSet->bRowSet = bHorizontal;
//STRIP001
//STRIP001          // Attribute des neu eingef"ugten Frames zur"ucksetzen und eine
//STRIP001          // Id erzeugen
//STRIP001          pSplit->aName.Erase();
//STRIP001          pSplit->aMargin = Size( -1, -1 );
//STRIP001          pSplit->aURL.SetURL( "" );
//STRIP001          pSplit->aActualURL.SetURL( "" );
//STRIP001          pSplit->SetItemId( pRoot->MakeItemId() );
//STRIP001          bCreated = TRUE;
//STRIP001
//STRIP001          // Alter Frame erh"alt ganzen Platz im neu eingef"ugten Frameset
//STRIP001          pPrev->nWidth = 100;
//STRIP001          pPrev->eSizeSelector = SIZE_PERCENT;
//STRIP001
//STRIP001          // Alten Frame umh"angen
//STRIP001          pSplitSet->RemoveFrame( pPrev );
//STRIP001          pSet->InsertFrame( pPrev );
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if ( !pPrev || !pPrev->pParentFrameSet )
//STRIP001      return NULL;
//STRIP001
//STRIP001  // Hinter pPrev einen neuen Frame einf"ugen
//STRIP001  SfxFrameDescriptor *pFrame = new SfxFrameDescriptor( NULL );
//STRIP001  pSplitSet = pPrev->pParentFrameSet;
//STRIP001  pSplitSet->InsertFrame( pFrame, pSplitSet->aFrames.GetPos( pPrev ) + 1 );
//STRIP001  pFrame->pParentFrameSet = pSplitSet;
//STRIP001
//STRIP001  // Size und ID setzen
//STRIP001  USHORT n = pRoot->MakeItemId();
//STRIP001  pFrame->SetItemId( n );
//STRIP001
//STRIP001  // Platz zwischen beiden Frames aufteilen
//STRIP001  long nSize = pPrev->nWidth / 2L;
//STRIP001  pPrev->nWidth = nSize ? nSize : 1L;
//STRIP001  pFrame->nWidth = pPrev->nWidth;
//STRIP001  pFrame->eSizeSelector = pPrev->eSizeSelector;
//STRIP001
//STRIP001  return pFrame;
//STRIP001 }
//STRIP001
//STRIP001 BOOL SfxFrameDescriptor::CanSplit( BOOL bHorizontal, BOOL bParent ) const
//STRIP001 {
//STRIP001  DBG_ASSERT( pParentFrameSet, "Frames ohne Set koennen nicht gesplittet werden!" );
//STRIP001
//STRIP001  // Die Root holen, um neue Ids erzeugen zu k"onnen
//STRIP001  const SfxFrameSetDescriptor *pRoot = pParentFrameSet;
//STRIP001  while ( pRoot->pParentFrame && pRoot->pParentFrame->pParentFrameSet )
//STRIP001      pRoot = pRoot->pParentFrame->pParentFrameSet;
//STRIP001
//STRIP001  // Der Frame, hinter dem ein neuer eingef"ugt werden soll
//STRIP001  const SfxFrameDescriptor *pPrev = this;
//STRIP001
//STRIP001  // Dieser Descriptor soll gesplittet werden ...
//STRIP001  const SfxFrameDescriptor *pSplit = this;
//STRIP001  const SfxFrameSetDescriptor *pSplitSet = pParentFrameSet;
//STRIP001  BOOL bRowSet = pSplitSet->bRowSet;
//STRIP001
//STRIP001  if ( bParent )
//STRIP001  {
//STRIP001      // Ein FrameSet suchen, das die gleiche Orientierung hat wie
//STRIP001      // die "ubergebene
//STRIP001      pSplit = pSplitSet->bIsRoot ? NULL : pSplitSet->pParentFrame;
//STRIP001      while ( pSplit && pSplit->pParentFrameSet )
//STRIP001      {
//STRIP001          pSplitSet = pSplit->pParentFrameSet;
//STRIP001          if ( pSplitSet->bRowSet == bHorizontal )
//STRIP001              break;
//STRIP001          pSplit = pSplitSet->pParentFrame;
//STRIP001      }
//STRIP001
//STRIP001      // pSplit ist jetzt NULL oder TopLevel, wenn das Set das RootSet ist
//STRIP001      pPrev = pSplit;
//STRIP001      bRowSet = pSplitSet->bRowSet;
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      // Wenn das aktuelle FrameSet eine andere Orientierung hat, der
//STRIP001      // zu splittende Frame aber der einzige ist, wird einfach die
//STRIP001      // Orientierung des Sets umgedreht( k"urzt den Baum)
//STRIP001      if ( pSplitSet->GetFrameCount() == 1 )
//STRIP001          bRowSet = bHorizontal;
//STRIP001  }
//STRIP001
//STRIP001  if ( bRowSet == bHorizontal && ( !pPrev || !pPrev->pParentFrameSet ) )
//STRIP001      return FALSE;
//STRIP001  return TRUE;
//STRIP001 }
//STRIP001
//STRIP001 SfxFrameDescriptor* SfxFrameDescriptor::Next() const
//STRIP001 {
//STRIP001  if ( !pParentFrameSet )
//STRIP001      return NULL;
//STRIP001
//STRIP001  USHORT nPos = pParentFrameSet->aFrames.GetPos( (SfxFrameDescriptor*) this );
//STRIP001  if ( nPos < pParentFrameSet->aFrames.Count() - 1 )
//STRIP001      return pParentFrameSet->aFrames[nPos+1];
//STRIP001  else
//STRIP001      return NULL;
//STRIP001 }
//STRIP001
//STRIP001 SfxFrameDescriptor* SfxFrameDescriptor::Prev() const
//STRIP001 {
//STRIP001  if ( !pParentFrameSet )
//STRIP001      return NULL;
//STRIP001
//STRIP001  USHORT nPos = pParentFrameSet->aFrames.GetPos( (SfxFrameDescriptor*) this );
//STRIP001  if ( nPos > 0 )
//STRIP001      return pParentFrameSet->aFrames[nPos-1];
//STRIP001  else
//STRIP001      return NULL;
//STRIP001 }
//STRIP001
//STRIP001 USHORT SfxFrameDescriptor::GetParentSetId() const
//STRIP001 {
//STRIP001  if ( !pParentFrameSet )
//STRIP001      return USHRT_MAX;
//STRIP001
//STRIP001  SfxFrameDescriptor *pFrame = pParentFrameSet->pParentFrame;
//STRIP001  if ( pFrame )
//STRIP001      return pFrame->nItemId;
//STRIP001  else
//STRIP001      return 0;
//STRIP001 }
//STRIP001
//STRIP001 USHORT SfxFrameDescriptor::GetWinBits() const
//STRIP001 {
//STRIP001  USHORT nBits = 0;
//STRIP001  if ( eSizeSelector == SIZE_REL )
//STRIP001      nBits |= SWIB_RELATIVESIZE;
//STRIP001  if ( eSizeSelector == SIZE_PERCENT )
//STRIP001      nBits |= SWIB_PERCENTSIZE;
//STRIP001  if ( !IsResizable() )
//STRIP001      nBits |= SWIB_FIXED;
//STRIP001  if ( pFrameSet && pFrameSet->IsColSet() )
//STRIP001      nBits |= SWIB_COLSET;
//STRIP001  if ( !nWidth )
//STRIP001      nBits |= SWIB_INVISIBLE;
//STRIP001  return nBits;
//STRIP001 }

/*N*/ BOOL SfxFrameDescriptor::HasFrameBorder() const
/*N*/ {DBG_ASSERT(0, "STRIP");return FALSE; //STRIP001
//STRIP001  if ( pParentFrameSet )
//STRIP001  {
//STRIP001      if ( pParentFrameSet->pImp->bNetscapeCompat && !pParentFrameSet->GetFrameSpacing() )
//STRIP001          return FALSE;
//STRIP001      else if ( ( nHasBorder & BORDER_SET ) )
//STRIP001          return (nHasBorder & BORDER_YES) != 0;
//STRIP001      else
//STRIP001          return pParentFrameSet->HasFrameBorder();
//STRIP001  }
//STRIP001  else
//STRIP001      return (nHasBorder & BORDER_YES) != 0;
/*N*/ }

//STRIP001 long SfxFrameDescriptor::GetSize() const
//STRIP001 {
//STRIP001  return nWidth;
//STRIP001 }
//STRIP001
//STRIP001 void SfxFrameDescriptor::TakeProperties( const SfxFrameProperties& rProp )
//STRIP001 {
//STRIP001  aURL = aActualURL = rProp.aURL;
//STRIP001  aName = rProp.aName;
//STRIP001  aMargin.Width() = rProp.lMarginWidth;
//STRIP001  aMargin.Height() = rProp.lMarginHeight;
//STRIP001  nWidth = rProp.lSize;
//STRIP001  eScroll = rProp.eScroll;
//STRIP001  eSizeSelector = rProp.eSizeSelector;
//STRIP001  nHasBorder = rProp.bHasBorder ? BORDER_YES : BORDER_NO;
//STRIP001  if ( rProp.bBorderSet )
//STRIP001      nHasBorder |= BORDER_SET;
//STRIP001  bResizeHorizontal = bResizeVertical = rProp.bResizable;
//STRIP001  if ( pParentFrameSet )
//STRIP001  {
//STRIP001      SfxFrameDescriptor *pParent = pParentFrameSet->pParentFrame;
//STRIP001      if ( pParent )
//STRIP001      {
//STRIP001          pParent->nWidth = rProp.lSetSize;
//STRIP001          pParent->eSizeSelector = rProp.eSetSizeSelector;
//STRIP001          pParent->bResizeHorizontal = pParent->bResizeVertical = rProp.bSetResizable;
//STRIP001      }
//STRIP001
//STRIP001      pParentFrameSet->nFrameSpacing = rProp.lFrameSpacing;
//STRIP001  }
//STRIP001 }
//STRIP001
//STRIP001 void SfxFrameDescriptor::SetWallpaper( const Wallpaper& rWallpaper )
//STRIP001 {
//STRIP001  DELETEZ( pImp->pWallpaper );
//STRIP001
//STRIP001  if ( rWallpaper.GetStyle() != WALLPAPER_NULL )
//STRIP001      pImp->pWallpaper = new Wallpaper( rWallpaper );
//STRIP001 }
//STRIP001
//STRIP001 const Wallpaper* SfxFrameDescriptor::GetWallpaper() const
//STRIP001 {
//STRIP001  return pImp->pWallpaper;
//STRIP001 }
//STRIP001
//STRIP001 USHORT SfxFrameDescriptor::GetItemPos() const
//STRIP001 {
//STRIP001  if ( pParentFrameSet )
//STRIP001  {
//STRIP001      USHORT nRet = pParentFrameSet->aFrames.GetPos((SfxFrameDescriptor*)this);
//STRIP001      for ( USHORT n=0; n<nRet; n++ )
//STRIP001          if ( !pParentFrameSet->GetFrame(n)->nWidth )
//STRIP001              nRet--;
//STRIP001      return nRet;
//STRIP001  }
//STRIP001
//STRIP001  return USHRT_MAX;
//STRIP001 }
//STRIP001

/*N*/ SfxFrameProperties::SfxFrameProperties( const SfxFrameDescriptor *pD )
/*N*/   : aURL( pD->GetURL().GetMainURL( INetURLObject::DECODE_TO_IURI ) )
/*N*/   , aName( pD->GetName() )
/*N*/   , lMarginWidth( pD->GetMargin().Width() )
/*N*/   , lMarginHeight( pD->GetMargin().Height() )
/*N*/   , lSize( pD->GetWidth() )
/*N*/   , lSetSize( SIZE_NOT_SET )
/*N*/   , lFrameSpacing( SPACING_NOT_SET )
/*N*/   , lInheritedFrameSpacing( SPACING_NOT_SET )
/*N*/   , eScroll( pD->GetScrollingMode() )
/*N*/   , eSizeSelector( pD->GetSizeSelector() )
/*N*/   , eSetSizeSelector( SIZE_REL )
/*N*/   , bHasBorder( pD->HasFrameBorder() )
/*N*/   , bHasBorderInherited( FALSE )
/*N*/   , bBorderSet( pD->IsFrameBorderSet() )
/*N*/   , bResizable( pD->IsResizable() )
/*N*/   , bIsInColSet( FALSE )
/*N*/   , bSetResizable( FALSE )
/*N*/   , bIsRootSet( FALSE )
/*N*/   , pFrame( pD->Clone() )
/*N*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  SfxFrameSetDescriptor *pSet = pD->GetParent();
//STRIP001  if ( pSet )
//STRIP001  {
//STRIP001      bIsRootSet = ( pSet->IsRootFrameSet() );
//STRIP001      lFrameSpacing = pSet->GetFrameSpacing();
//STRIP001      lSetSize = bIsRootSet ? SIZE_NOT_SET : pSet->GetParentFrame()->GetWidth();
//STRIP001      eSetSizeSelector = bIsRootSet ? SIZE_ABS : pSet->GetParentFrame()->GetSizeSelector();
//STRIP001      bSetResizable = bIsRootSet ? FALSE : pSet->GetParentFrame()->IsResizable();
//STRIP001      bIsInColSet = pSet->IsColSet();
//STRIP001      bHasBorderInherited = pSet->HasFrameBorder();
//STRIP001      lInheritedFrameSpacing = bIsRootSet ? SPACING_NOT_SET : pSet->GetParentFrame()->GetParent()->GetFrameSpacing();
//STRIP001  }
//STRIP001  else
//STRIP001      bBorderSet = TRUE;
/*N*/ }

/*N*/ SfxFrameProperties&   SfxFrameProperties::operator =(
/*N*/   const SfxFrameProperties &rProp )
/*N*/ {
/*N*/   aURL = rProp.aURL;
/*N*/   aName = rProp.aName;
/*N*/   lMarginWidth = rProp.lMarginWidth;
/*N*/   lMarginHeight = rProp.lMarginHeight;
/*N*/   lSize = rProp.lSize;
/*N*/   lSetSize = rProp.lSetSize;
/*N*/   lFrameSpacing = rProp.lFrameSpacing;
/*N*/   lInheritedFrameSpacing = rProp.lInheritedFrameSpacing;
/*N*/   eScroll = rProp.eScroll;
/*N*/   eSizeSelector = rProp.eSizeSelector;
/*N*/   eSetSizeSelector = rProp.eSetSizeSelector;
/*N*/   bHasBorder = rProp.bHasBorder;
/*N*/   bBorderSet = rProp.bBorderSet;
/*N*/   bResizable = rProp.bResizable;
/*N*/   bSetResizable = rProp.bSetResizable;
/*N*/   bIsRootSet = rProp.bIsRootSet;
/*N*/   bIsInColSet = rProp.bIsInColSet;
/*N*/   bHasBorderInherited = rProp.bHasBorderInherited;
/*N*/   pFrame = rProp.pFrame->Clone();
/*N*/   return *this;
/*N*/ }

/*N*/ int SfxFrameProperties::operator ==( const SfxFrameProperties& rProp ) const
/*N*/ {
/*N*/   return aURL == rProp.aURL && aName == rProp.aName && lMarginWidth == rProp.lMarginWidth && lMarginHeight == rProp.lMarginHeight &&
/*N*/           lSize == rProp.lSize && eScroll == rProp.eScroll && eSizeSelector == rProp.eSizeSelector &&
/*N*/           lSetSize == rProp.lSetSize && lFrameSpacing == rProp.lFrameSpacing && eSetSizeSelector == rProp.eSetSizeSelector &&
/*N*/           bHasBorder == rProp.bHasBorder && bBorderSet == rProp.bBorderSet &&
/*N*/           bResizable == rProp.bResizable && bSetResizable == rProp.bSetResizable;
/*N*/ }

/*?*/ TYPEINIT1(SfxFrameDescriptorItem, SfxPoolItem);

/*?*/ SfxFrameDescriptorItem::~SfxFrameDescriptorItem()
/*?*/ {}

/*?*/ int SfxFrameDescriptorItem::operator==( const SfxPoolItem& rAttr ) const
/*?*/ {
/*?*/   DBG_ASSERT( SfxPoolItem::operator==(rAttr), "unequal types" );
/*?*/
/*?*/   return aProperties == ((SfxFrameDescriptorItem&)rAttr).aProperties;
/*?*/ }

// -----------------------------------------------------------------------

/*?*/ SfxPoolItem* SfxFrameDescriptorItem::Clone( SfxItemPool* ) const
/*?*/ {
/*?*/   return new SfxFrameDescriptorItem( *this );
/*?*/ }

//------------------------------------------------------------------------

/*?*/ SfxItemPresentation SfxFrameDescriptorItem::GetPresentation
/*?*/ (
/*?*/   SfxItemPresentation ePres,
/*?*/   SfxMapUnit          eCoreUnit,
/*?*/   SfxMapUnit          ePresUnit,
/*?*/   XubString&          rText,
/*?*/     const IntlWrapper *
/*?*/ ) const
/*?*/ {
/*?*/   rText.Erase();
/*?*/   return SFX_ITEM_PRESENTATION_NONE;
/*?*/ }


}
