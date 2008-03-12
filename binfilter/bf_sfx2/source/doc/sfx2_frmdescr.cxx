/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sfx2_frmdescr.cxx,v $
 *
 *  $Revision: 1.12 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 08:05:40 $
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


#ifndef _SV_SPLITWIN_HXX //autogen
#include <vcl/splitwin.hxx>
#endif
#ifndef _SFXITEMSET_HXX //autogen
#include <bf_svtools/itemset.hxx>
#endif
#ifdef _MSC_VER
#pragma hdrstop
#endif

#include "frmdescr.hxx"
#include "app.hxx"
#include "bf_so3/staticbaseurl.hxx"
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
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/ }

/*N*/ BOOL SfxFrameSetDescriptor::HasFrameBorder() const
/*N*/ {DBG_BF_ASSERT(0, "STRIP");return FALSE; //STRIP001
/*N*/ }


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
/*?*/   {DBG_BF_ASSERT(0, "STRIP"); }//STRIP001     pParentFrameSet->InsertFrame( this );
/*N*/ }

/*N*/ SfxFrameDescriptor::~SfxFrameDescriptor()
/*N*/ {
/*N*/   DBG_DTOR(SfxFrameDescriptor, 0);
/*N*/
/*N*/   if ( pFrameSet )
/*N*/       delete pFrameSet;
/*N*/   if ( pParentFrameSet )
/*?*/       {DBG_BF_ASSERT(0, "STRIP");} //STRIP001 pParentFrameSet->RemoveFrame( this );
/*N*/   delete pImp;
/*N*/ }

/*N*/ SfxItemSet* SfxFrameDescriptor::GetArgs()
/*N*/ {
/*N*/   if( !pImp->pArgs )
/*N*/       pImp->pArgs = new SfxAllItemSet( SFX_APP()->GetPool() );
/*N*/   return pImp->pArgs;
/*N*/ }

/*?*/ void SfxFrameDescriptor::SetURL( const String& rURL )
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*?*/ }

/*N*/ void SfxFrameDescriptor::SetActualURL( const String& rURL )
/*N*/ {
/*N*/   aActualURL = INetURLObject(rURL);
/*N*/   if ( pImp->pArgs )
/*?*/       pImp->pArgs->ClearItem();
/*N*/ }

/*?*/ void SfxFrameDescriptor::SetActualURL( const INetURLObject& rURL )
/*?*/ {
/*?*/   SetActualURL(String(rURL.GetMainURL( INetURLObject::DECODE_TO_IURI )));
/*?*/ }

/*N*/ void SfxFrameDescriptor::SetEditable( BOOL bSet )
/*N*/ {
/*N*/   pImp->bEditable = bSet;
/*N*/ }

/*N*/ BOOL SfxFrameDescriptor::IsEditable() const
/*N*/ {
/*N*/   return pImp->bEditable;
/*N*/ }


/*N*/ BOOL SfxFrameDescriptor::Store( SvStream& rStream ) const
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/   return TRUE;
/*N*/ }

/*N*/ BOOL SfxFrameDescriptor::Load( SvStream& rStream, USHORT nVersion )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/   return TRUE;
/*N*/ }

/*N*/ SfxFrameDescriptor* SfxFrameDescriptor::Clone(
/*N*/   SfxFrameSetDescriptor *pSet, BOOL bWithIds ) const
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); return 0;//STRIP001
/*N*/ }



/*N*/ BOOL SfxFrameDescriptor::HasFrameBorder() const
/*N*/ {DBG_BF_ASSERT(0, "STRIP");return FALSE; //STRIP001
/*N*/ }


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
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
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
/*?*/     const ::IntlWrapper *
/*?*/ ) const
/*?*/ {
/*?*/   rText.Erase();
/*?*/   return SFX_ITEM_PRESENTATION_NONE;
/*?*/ }


}
