/*************************************************************************
 *
 *  $RCSfile: svx_postattr.cxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:22:03 $
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

// include ---------------------------------------------------------------

#pragma hdrstop

#define _SVX_POSTATTR_CXX
#define ITEMID_AUTHOR   0
#define ITEMID_DATE     0
#define ITEMID_TEXT     0

#include "postattr.hxx"
#include "itemtype.hxx"

// -----------------------------------------------------------------------

/*N*/ TYPEINIT1_AUTOFACTORY(SvxPostItAuthorItem, SfxStringItem);
/*N*/ TYPEINIT1_AUTOFACTORY(SvxPostItDateItem, SfxStringItem);
/*N*/ TYPEINIT1_AUTOFACTORY(SvxPostItTextItem, SfxStringItem);

// class SvxPostItAuthorItem ---------------------------------------------

//STRIP001 SvxPostItAuthorItem::SvxPostItAuthorItem( sal_uInt16 nWhich )
//STRIP001 {
//STRIP001  SetWhich( nWhich );
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 SvxPostItAuthorItem::SvxPostItAuthorItem( const XubString& rAuthor,
//STRIP001                                        sal_uInt16 nWhich ) :
//STRIP001  SfxStringItem( nWhich, rAuthor )
//STRIP001 {
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 SfxItemPresentation SvxPostItAuthorItem::GetPresentation
//STRIP001 (
//STRIP001  SfxItemPresentation ePres,
//STRIP001  SfxMapUnit          eCoreUnit,
//STRIP001  SfxMapUnit          ePresUnit,
//STRIP001     XubString&          rText, const IntlWrapper *
//STRIP001 )    const
//STRIP001 {
//STRIP001  switch ( ePres )
//STRIP001  {
//STRIP001      case SFX_ITEM_PRESENTATION_NONE:
//STRIP001          rText.Erase();
//STRIP001          return SFX_ITEM_PRESENTATION_NONE;
//STRIP001      case SFX_ITEM_PRESENTATION_NAMELESS:
//STRIP001          rText = GetValue();
//STRIP001          return SFX_ITEM_PRESENTATION_NAMELESS;
//STRIP001      case SFX_ITEM_PRESENTATION_COMPLETE:
//STRIP001          rText = SVX_RESSTR(RID_SVXITEMS_AUTHOR_COMPLETE);
//STRIP001          rText += GetValue();
//STRIP001          return SFX_ITEM_PRESENTATION_COMPLETE;
//STRIP001  }
//STRIP001  return SFX_ITEM_PRESENTATION_NONE;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 SfxPoolItem* __EXPORT SvxPostItAuthorItem::Clone( SfxItemPool * ) const
//STRIP001 {
//STRIP001  return new SvxPostItAuthorItem( *this );
//STRIP001 }

// class SvxPostItDateItem -----------------------------------------------

//STRIP001 SvxPostItDateItem::SvxPostItDateItem( sal_uInt16 nWhich )
//STRIP001 {
//STRIP001  SetWhich( nWhich );
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 SvxPostItDateItem::SvxPostItDateItem( const XubString& rDate, sal_uInt16 nWhich ) :
//STRIP001
//STRIP001  SfxStringItem( nWhich, rDate )
//STRIP001 {
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 SfxItemPresentation SvxPostItDateItem::GetPresentation
//STRIP001 (
//STRIP001  SfxItemPresentation ePres,
//STRIP001  SfxMapUnit          eCoreUnit,
//STRIP001  SfxMapUnit          ePresUnit,
//STRIP001     XubString&          rText, const IntlWrapper *
//STRIP001 )    const
//STRIP001 {
//STRIP001  switch ( ePres )
//STRIP001  {
//STRIP001      case SFX_ITEM_PRESENTATION_NONE:
//STRIP001          rText.Erase();
//STRIP001          return SFX_ITEM_PRESENTATION_NONE;
//STRIP001      case SFX_ITEM_PRESENTATION_NAMELESS:
//STRIP001          rText = GetValue();
//STRIP001          return SFX_ITEM_PRESENTATION_NAMELESS;
//STRIP001      case SFX_ITEM_PRESENTATION_COMPLETE:
//STRIP001          rText = SVX_RESSTR(RID_SVXITEMS_DATE_COMPLETE);
//STRIP001          rText += GetValue();
//STRIP001          return SFX_ITEM_PRESENTATION_COMPLETE;
//STRIP001  }
//STRIP001  return SFX_ITEM_PRESENTATION_NONE;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 SfxPoolItem* __EXPORT SvxPostItDateItem::Clone( SfxItemPool * ) const
//STRIP001 {
//STRIP001  return new SvxPostItDateItem( *this );
//STRIP001 }

// class SvxPostItTextItem -----------------------------------------------

//STRIP001 SvxPostItTextItem::SvxPostItTextItem( sal_uInt16 nWhich )
//STRIP001 {
//STRIP001  SetWhich( nWhich );
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 SvxPostItTextItem::SvxPostItTextItem( const XubString& rText, sal_uInt16 nWhich ) :
//STRIP001
//STRIP001  SfxStringItem( nWhich, rText )
//STRIP001 {
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 SfxItemPresentation SvxPostItTextItem::GetPresentation
//STRIP001 (
//STRIP001  SfxItemPresentation ePres,
//STRIP001  SfxMapUnit          eCoreUnit,
//STRIP001  SfxMapUnit          ePresUnit,
//STRIP001     XubString&          rText, const IntlWrapper *
//STRIP001 )    const
//STRIP001 {
//STRIP001  switch ( ePres )
//STRIP001  {
//STRIP001      case SFX_ITEM_PRESENTATION_NONE:
//STRIP001          rText.Erase();
//STRIP001          return SFX_ITEM_PRESENTATION_NONE;
//STRIP001      case SFX_ITEM_PRESENTATION_NAMELESS:
//STRIP001          rText = GetValue();
//STRIP001          return SFX_ITEM_PRESENTATION_NAMELESS;
//STRIP001      case SFX_ITEM_PRESENTATION_COMPLETE:
//STRIP001          rText = SVX_RESSTR(RID_SVXITEMS_TEXT_COMPLETE);
//STRIP001          rText += GetValue();
//STRIP001          return SFX_ITEM_PRESENTATION_COMPLETE;
//STRIP001  }
//STRIP001  return SFX_ITEM_PRESENTATION_NONE;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 SfxPoolItem* __EXPORT SvxPostItTextItem::Clone( SfxItemPool * ) const
//STRIP001 {
//STRIP001  return new SvxPostItTextItem( *this );
//STRIP001 }


