/*************************************************************************
 *
 *  $RCSfile: svx_writingmodeitem.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 16:06:24 $
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


#ifndef _XDEF_HXX
#include <bf_svx/xdef.hxx>
#endif

#ifndef _SVX_WRITINGMODEITEM_HXX
#include "writingmodeitem.hxx"
#endif

// auto strip #ifndef _SVX_DIALMGR_HXX
// auto strip #include "dialmgr.hxx"
// auto strip #endif

#ifndef _SVXITEMS_HRC
#include "svxitems.hrc"
#endif
namespace binfilter {

using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::text;

// class SvxWritingModeItem -------------------------------------------------

/*N*/ TYPEINIT1_AUTOFACTORY(SvxWritingModeItem, SfxUInt16Item);

/*N*/ SvxWritingModeItem::SvxWritingModeItem( WritingMode eValue, USHORT nWhich )
/*N*/   : SfxUInt16Item( nWhich, (sal_uInt16)eValue )
/*N*/ {
/*N*/ }

/*N*/ SvxWritingModeItem::~SvxWritingModeItem()
/*N*/ {
/*N*/ }

/*N*/ int SvxWritingModeItem::operator==( const SfxPoolItem& rCmp ) const
/*N*/ {
/*N*/   DBG_ASSERT( SfxPoolItem::operator==(rCmp), "unequal types" );
/*N*/
/*N*/   return GetValue() == ((SvxWritingModeItem&)rCmp).GetValue();
/*N*/ }

/*N*/ SfxPoolItem* SvxWritingModeItem::Clone( SfxItemPool * ) const
/*N*/ {
/*N*/   return new SvxWritingModeItem( *this );
/*N*/ }

//STRIP001 SfxPoolItem* SvxWritingModeItem::Create( SvStream & rStrm, USHORT nVer ) const
//STRIP001 {
//STRIP001  DBG_ERROR("SvxWritingModeItem should not be streamed!");
//STRIP001  return NULL;
//STRIP001 }

//STRIP001 SvStream& SvxWritingModeItem::Store( SvStream & rStrm, USHORT nIVer ) const
//STRIP001 {
//STRIP001  DBG_ERROR("SvxWritingModeItem should not be streamed!");
//STRIP001  return rStrm;
//STRIP001 }

/*N*/ USHORT SvxWritingModeItem::GetVersion( USHORT nFVer ) const
/*N*/ {
/*N*/   return USHRT_MAX;
/*N*/ }

//STRIP001 SfxItemPresentation SvxWritingModeItem::GetPresentation( SfxItemPresentation ePres, SfxMapUnit eCoreMetric, SfxMapUnit ePresMetric, String &rText, const IntlWrapper *  ) const
//STRIP001 {
//STRIP001  SfxItemPresentation eRet = ePres;
//STRIP001     switch( ePres )
//STRIP001     {
//STRIP001     case SFX_ITEM_PRESENTATION_NONE:
//STRIP001         rText.Erase();
//STRIP001      break;
//STRIP001
//STRIP001     case SFX_ITEM_PRESENTATION_NAMELESS:
//STRIP001     case SFX_ITEM_PRESENTATION_COMPLETE:
//STRIP001      rText = SVX_RESSTR( RID_SVXITEMS_FRMDIR_BEGIN + GetValue() );
//STRIP001      break;
//STRIP001
//STRIP001  default:
//STRIP001      eRet = SFX_ITEM_PRESENTATION_NONE;
//STRIP001     }
//STRIP001     return eRet;
//STRIP001 }

//STRIP001 sal_Bool SvxWritingModeItem::PutValue( const ::com::sun::star::uno::Any& rVal, BYTE )
//STRIP001 {
//STRIP001     sal_Int32 nVal;
//STRIP001     sal_Bool bRet = ( rVal >>= nVal );
//STRIP001
//STRIP001  if( !bRet )
//STRIP001  {
//STRIP001      WritingMode eMode;
//STRIP001      bRet = rVal >>= eMode;
//STRIP001
//STRIP001      if( bRet )
//STRIP001      {
//STRIP001          nVal = (sal_Int32)eMode;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001     if( bRet )
//STRIP001     {
//STRIP001         switch( nVal )
//STRIP001         {
//STRIP001          case WritingMode_LR_TB:
//STRIP001          case WritingMode_RL_TB:
//STRIP001          case WritingMode_TB_RL:
//STRIP001              SetValue( (sal_uInt16)nVal );
//STRIP001              bRet = true;
//STRIP001                 break;
//STRIP001             default:
//STRIP001                 bRet = false;
//STRIP001                 break;
//STRIP001         }
//STRIP001     }
//STRIP001
//STRIP001  return bRet;
//STRIP001 }

/*N*/ sal_Bool SvxWritingModeItem::QueryValue( ::com::sun::star::uno::Any& rVal,
/*N*/                                           BYTE ) const
/*N*/ {
/*N*/   rVal <<= (WritingMode)GetValue();
/*N*/   return true;
/*N*/ }

/*N*/ SvxWritingModeItem& SvxWritingModeItem::operator=( const SvxWritingModeItem& rItem )
/*N*/ {
/*N*/   SetValue( rItem.GetValue() );
/*N*/   return *this;
/*N*/ }
}
