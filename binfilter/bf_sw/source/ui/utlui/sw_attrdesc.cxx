/*************************************************************************
 *
 *  $RCSfile: sw_attrdesc.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 19:32:00 $
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

// auto strip #ifndef _SFXITEMITER_HXX //autogen
// auto strip #include <svtools/itemiter.hxx>
// auto strip #endif
// auto strip #ifndef _SV_SVAPP_HXX //autogen wg. Application
// auto strip #include <vcl/svapp.hxx>
// auto strip #endif
// auto strip #ifndef _SVX_ITEMTYPE_HXX
// auto strip #include <bf_svx/itemtype.hxx>
// auto strip #endif

// auto strip #ifndef _GRFMGR_HXX
// auto strip #include <goodies/grfmgr.hxx>
// auto strip #endif

// auto strip #ifndef _UNOTOOLS_INTLWRAPPER_HXX
// auto strip #include <unotools/intlwrapper.hxx>
// auto strip #endif
// auto strip #ifndef _COMPHELPER_PROCESSFACTORY_HXX_
// auto strip #include <comphelper/processfactory.hxx>
// auto strip #endif

// auto strip #ifndef _FMTANCHR_HXX //autogen
// auto strip #include <fmtanchr.hxx>
// auto strip #endif
// auto strip #ifndef _FMTFSIZE_HXX //autogen
// auto strip #include <fmtfsize.hxx>
// auto strip #endif
// auto strip #ifndef _FMTINFMT_HXX //autogen
// auto strip #include <fmtinfmt.hxx>
// auto strip #endif
#ifndef _FCHRFMT_HXX //autogen
#include <fchrfmt.hxx>
#endif
// auto strip #ifndef _FMTSRND_HXX //autogen
// auto strip #include <fmtsrnd.hxx>
// auto strip #endif

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

// auto strip #ifndef _FMTORNT_HXX //autogen
// auto strip #include <fmtornt.hxx>
// auto strip #endif
// auto strip #ifndef _FMTTSPLT_HXX //autogen
// auto strip #include <fmtlsplt.hxx>
// auto strip #endif
// auto strip #ifndef _FMTPDSC_HXX //autogen
// auto strip #include <fmtpdsc.hxx>
// auto strip #endif
#ifndef _FMTCLDS_HXX //autogen
#include <fmtclds.hxx>
#endif
// auto strip #ifndef _FMTEIRO_HXX //autogen
// auto strip #include <fmteiro.hxx>
// auto strip #endif
// auto strip #ifndef _FMTURL_HXX //autogen
// auto strip #include <fmturl.hxx>
// auto strip #endif
// auto strip #ifndef _FMTHDFT_HXX //autogen
// auto strip #include <fmthdft.hxx>
// auto strip #endif
// auto strip #ifndef _FMTCNCT_HXX //autogen
// auto strip #include <fmtcnct.hxx>
// auto strip #endif
// auto strip #ifndef _FMTLINE_HXX
// auto strip #include <fmtline.hxx>
// auto strip #endif
// auto strip #ifndef SW_TGRDITEM_HXX
// auto strip #include <tgrditem.hxx>
// auto strip #endif
#ifndef _SW_HF_EAT_SPACINGITEM_HXX
#include <hfspacingitem.hxx>
#endif
// auto strip #ifndef _FMTRUBY_HXX
// auto strip #include <fmtruby.hxx>
// auto strip #endif
// auto strip #ifndef _SWATRSET_HXX
// auto strip #include <swatrset.hxx>
// auto strip #endif
#ifndef _PARATR_HXX
#include <paratr.hxx>
#endif
// auto strip #ifndef _GRFATR_HXX
// auto strip #include <grfatr.hxx>
// auto strip #endif
#ifndef _PAGEDESC_HXX
#include <pagedesc.hxx>
#endif
// auto strip #ifndef _CHARFMT_HXX
// auto strip #include <charfmt.hxx>
// auto strip #endif
// auto strip #ifndef _FMTCOL_HXX
// auto strip #include <fmtcol.hxx>
// auto strip #endif
// auto strip #ifndef _TOX_HXX
// auto strip #include <tox.hxx>
// auto strip #endif
#ifndef _ATTRDESC_HRC
#include <attrdesc.hrc>
#endif
// auto strip #ifndef _FMTFTNTX_HXX //autogen
// auto strip #include <fmtftntx.hxx>
// auto strip #endif
// auto strip #ifndef _LEGACYBINFILTERMGR_HXX
// auto strip #include <legacysmgr/legacy_binfilters_smgr.hxx>  //STRIP002
// auto strip #endif
namespace binfilter {

/*N*/ TYPEINIT2(SwFmtCharFmt,SfxPoolItem,SwClient);

// erfrage die Attribut-Beschreibung
/*N*/ void SwAttrSet::GetPresentation(
/*N*/       SfxItemPresentation ePres,
/*N*/       SfxMapUnit eCoreMetric,
/*N*/       SfxMapUnit ePresMetric,
/*N*/       String &rText ) const
/*N*/ {
DBG_BF_ASSERT(0, "STRIP"); //STRIP001 static sal_Char __READONLY_DATA sKomma[] = ", ";
//STRIP001
//STRIP001  rText.Erase();
//STRIP001  String aStr;
//STRIP001  if( Count() )
//STRIP001  {
//STRIP001      SfxItemIter aIter( *this );
//STRIP001         const IntlWrapper rInt( ::legacy_binfilters::getLegacyProcessServiceFactory(),
//STRIP001                                  GetAppLanguage() );
//STRIP001      while( TRUE )
//STRIP001      {
//STRIP001          aIter.GetCurItem()->GetPresentation( ePres, eCoreMetric,
//STRIP001                                               ePresMetric, aStr,
//STRIP001                                               &rInt );
//STRIP001          if( rText.Len() && aStr.Len() )
//STRIP001              rText += String::CreateFromAscii(sKomma);
//STRIP001          rText += aStr;
//STRIP001          if( aIter.IsAtEnd() )
//STRIP001              break;
//STRIP001          aIter.NextItem();
//STRIP001      }
//STRIP001  }
}


/*N*/ void SwPageDesc::GetPresentation(
/*N*/       SfxItemPresentation ePres,
/*N*/       SfxMapUnit eCoreMetric,
/*N*/       SfxMapUnit ePresMetric,
/*N*/       String &rText ) const
/*N*/ {
/*N*/   rText = GetName();
/*N*/ }


// ATT_CHARFMT *********************************************


/*N*/ SfxItemPresentation SwFmtCharFmt::GetPresentation
/*N*/ (
/*N*/   SfxItemPresentation ePres,
/*N*/   SfxMapUnit          eCoreUnit,
/*N*/   SfxMapUnit          ePresUnit,
/*N*/   String&             rText,
/*N*/     const IntlWrapper*        pIntl
/*N*/ ) const
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  switch ( ePres )
//STRIP001  {
//STRIP001      case SFX_ITEM_PRESENTATION_NONE:
//STRIP001          rText.Erase();
//STRIP001          break;
//STRIP001      case SFX_ITEM_PRESENTATION_NAMELESS:
//STRIP001      case SFX_ITEM_PRESENTATION_COMPLETE:
//STRIP001      {
//STRIP001          const SwCharFmt *pCharFmt = GetCharFmt();
//STRIP001          if ( pCharFmt )
//STRIP001          {
//STRIP001              String aStr;
//STRIP001              rText = SW_RESSTR(STR_CHARFMT );
//STRIP001              pCharFmt->GetPresentation( ePres, eCoreUnit, ePresUnit, aStr );
//STRIP001              rText += '(';
//STRIP001              rText += aStr;
//STRIP001              rText += ')';
//STRIP001          }
//STRIP001          else
//STRIP001              rText = SW_RESSTR( STR_NO_CHARFMT );
//STRIP001          return ePres;
//STRIP001      }
//STRIP001  }
/*N*/   return SFX_ITEM_PRESENTATION_NONE;
/*N*/ }

// ATT_INETFMT *********************************************


//STRIP001 SfxItemPresentation SwFmtINetFmt::GetPresentation
//STRIP001 (
//STRIP001  SfxItemPresentation ePres,
//STRIP001  SfxMapUnit          eCoreUnit,
//STRIP001  SfxMapUnit          ePresUnit,
//STRIP001  String&             rText,
//STRIP001     const IntlWrapper*        pIntl
//STRIP001 )    const
//STRIP001 {
//STRIP001  switch ( ePres )
//STRIP001  {
//STRIP001      case SFX_ITEM_PRESENTATION_NONE:
//STRIP001          rText.Erase();
//STRIP001          break;
//STRIP001      case SFX_ITEM_PRESENTATION_NAMELESS:
//STRIP001      case SFX_ITEM_PRESENTATION_COMPLETE:
//STRIP001      {
//STRIP001          rText = GetValue();
//STRIP001          return ePres;
//STRIP001      }
//STRIP001  }
//STRIP001  return SFX_ITEM_PRESENTATION_NONE;
//STRIP001 }

//STRIP001 SfxItemPresentation SwFmtRuby::GetPresentation( SfxItemPresentation ePres,
//STRIP001                          SfxMapUnit eCoreMetric, SfxMapUnit ePresMetric,
//STRIP001                             String &rText, const IntlWrapper* pIntl ) const
//STRIP001 {
//STRIP001  switch ( ePres )
//STRIP001  {
//STRIP001  case SFX_ITEM_PRESENTATION_NONE:
//STRIP001      rText.Erase();
//STRIP001      break;
//STRIP001  case SFX_ITEM_PRESENTATION_NAMELESS:
//STRIP001  case SFX_ITEM_PRESENTATION_COMPLETE:
//STRIP001  {
//STRIP001      rText = aEmptyStr;
//STRIP001      return ePres;
//STRIP001  }
//STRIP001  }
//STRIP001  return SFX_ITEM_PRESENTATION_NONE;
//STRIP001 }

/*************************************************************************
|*    class     SwFmtDrop
*************************************************************************/


//STRIP001 SfxItemPresentation SwFmtDrop::GetPresentation
//STRIP001 (
//STRIP001  SfxItemPresentation ePres,
//STRIP001  SfxMapUnit          eCoreUnit,
//STRIP001  SfxMapUnit          ePresUnit,
//STRIP001  String&             rText,
//STRIP001     const IntlWrapper*        pIntl
//STRIP001 )    const
//STRIP001 {
//STRIP001  rText.Erase();
//STRIP001  switch ( ePres )
//STRIP001  {
//STRIP001      case SFX_ITEM_PRESENTATION_NONE:
//STRIP001          break;
//STRIP001      case SFX_ITEM_PRESENTATION_NAMELESS:
//STRIP001      case SFX_ITEM_PRESENTATION_COMPLETE:
//STRIP001      {
//STRIP001          if ( GetLines() > 1 )
//STRIP001          {
//STRIP001              if ( GetChars() > 1 )
//STRIP001              {
//STRIP001                  rText = String::CreateFromInt32( GetChars() );
//STRIP001                  rText += ' ';
//STRIP001              }
//STRIP001              rText += SW_RESSTR( STR_DROP_OVER );
//STRIP001              rText += ' ';
//STRIP001              rText += String::CreateFromInt32( GetLines() );
//STRIP001              rText += ' ';
//STRIP001              rText += SW_RESSTR( STR_DROP_LINES );
//STRIP001          }
//STRIP001          else
//STRIP001              rText = SW_RESSTR( STR_NO_DROP_LINES );
//STRIP001          return ePres;
//STRIP001      }
//STRIP001  }
//STRIP001  return SFX_ITEM_PRESENTATION_NONE;
//STRIP001 }

/*************************************************************************
|*    class     SwRegisterItem
*************************************************************************/


//STRIP001 SfxItemPresentation SwRegisterItem::GetPresentation
//STRIP001 (
//STRIP001  SfxItemPresentation ePres,
//STRIP001  SfxMapUnit          eCoreUnit,
//STRIP001  SfxMapUnit          ePresUnit,
//STRIP001  XubString&          rText,
//STRIP001     const IntlWrapper*        pIntl
//STRIP001 )    const
//STRIP001 {
//STRIP001  switch ( ePres )
//STRIP001  {
//STRIP001      case SFX_ITEM_PRESENTATION_NONE:
//STRIP001          rText.Erase();
//STRIP001          return SFX_ITEM_PRESENTATION_NONE;
//STRIP001      case SFX_ITEM_PRESENTATION_NAMELESS:
//STRIP001      case SFX_ITEM_PRESENTATION_COMPLETE:
//STRIP001      {
//STRIP001          USHORT nId = GetValue() ? STR_REGISTER_ON : STR_REGISTER_OFF;
//STRIP001          rText = SW_RESSTR( nId );
//STRIP001          return ePres;
//STRIP001      }
//STRIP001  }
//STRIP001  return SFX_ITEM_PRESENTATION_NONE;
//STRIP001 }

/*************************************************************************
|*    class     SwNumRuleItem
*************************************************************************/


//STRIP001 SfxItemPresentation SwNumRuleItem::GetPresentation
//STRIP001 (
//STRIP001  SfxItemPresentation ePres,
//STRIP001  SfxMapUnit          eCoreUnit,
//STRIP001  SfxMapUnit          ePresUnit,
//STRIP001  XubString&          rText,
//STRIP001     const IntlWrapper*        pIntl
//STRIP001 )    const
//STRIP001 {
//STRIP001  switch ( ePres )
//STRIP001  {
//STRIP001      case SFX_ITEM_PRESENTATION_NONE:
//STRIP001          rText.Erase();
//STRIP001          return SFX_ITEM_PRESENTATION_NONE;
//STRIP001      case SFX_ITEM_PRESENTATION_NAMELESS:
//STRIP001      case SFX_ITEM_PRESENTATION_COMPLETE:
//STRIP001      {
//STRIP001          if( GetValue().Len() )
//STRIP001              (((rText = SW_RESSTR( STR_NUMRULE_ON )) +=
//STRIP001                  '(' ) += GetValue() ) += ')';
//STRIP001          else
//STRIP001              rText = SW_RESSTR( STR_NUMRULE_OFF );
//STRIP001          return ePres;
//STRIP001      }
//STRIP001  }
//STRIP001  return SFX_ITEM_PRESENTATION_NONE;
//STRIP001 }
/*************************************************************************
|*    class     SwParaConnectBorderItem
*************************************************************************/

/*N*/ SfxItemPresentation SwParaConnectBorderItem::GetPresentation
/*N*/ (
/*N*/     SfxItemPresentation ePres,
/*N*/     SfxMapUnit          eCoreUnit,
/*N*/     SfxMapUnit          ePresUnit,
/*N*/     XubString&          rText,
/*N*/     const IntlWrapper*        pIntl
/*N*/ )   const
/*N*/ {
/*N*/     // no UI support available
/*N*/     return SfxBoolItem::GetPresentation( ePres, eCoreUnit, ePresUnit, rText, pIntl );
/*    switch ( ePres )
    {
        case SFX_ITEM_PRESENTATION_NONE:
            rText.Erase();
            return SFX_ITEM_PRESENTATION_NONE;
        case SFX_ITEM_PRESENTATION_NAMELESS:
        case SFX_ITEM_PRESENTATION_COMPLETE:
        {
            USHORT nId = GetValue() ? STR_CONNECT_BORDER_ON : STR_CONNECT_BORDER_OFF;
            rText = SW_RESSTR( nId );
            return ePres;
        }
    }
    return SFX_ITEM_PRESENTATION_NONE;
 */
/*N*/ }



/******************************************************************************
 *  Frame-Attribute:
 ******************************************************************************/


//STRIP001 SfxItemPresentation SwFmtFrmSize::GetPresentation
//STRIP001 (
//STRIP001  SfxItemPresentation ePres,
//STRIP001  SfxMapUnit          eCoreUnit,
//STRIP001  SfxMapUnit          ePresUnit,
//STRIP001  String&             rText,
//STRIP001     const IntlWrapper*        pIntl
//STRIP001 )    const
//STRIP001 {
//STRIP001  switch ( ePres )
//STRIP001  {
//STRIP001      case SFX_ITEM_PRESENTATION_NONE:
//STRIP001      {
//STRIP001          rText.Erase();
//STRIP001          break;
//STRIP001      }
//STRIP001      case SFX_ITEM_PRESENTATION_NAMELESS:
//STRIP001      case SFX_ITEM_PRESENTATION_COMPLETE:
//STRIP001      {
//STRIP001          rText = SW_RESSTR( STR_FRM_WIDTH );
//STRIP001          rText += ' ';
//STRIP001          if ( GetWidthPercent() )
//STRIP001          {
//STRIP001              rText += String::CreateFromInt32(GetWidthPercent());
//STRIP001              rText += '%';
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              rText += ::GetMetricText( GetWidth(), eCoreUnit, ePresUnit, pIntl );
//STRIP001              rText += ::GetSvxString( ::GetMetricId( ePresUnit ) );
//STRIP001          }
//STRIP001          if ( ATT_VAR_SIZE != GetSizeType() )
//STRIP001          {
//STRIP001              rText += ',';
//STRIP001              rText += ' ';
//STRIP001              const USHORT nId = ATT_FIX_SIZE == eFrmSize ?
//STRIP001                                      STR_FRM_FIXEDHEIGHT : STR_FRM_MINHEIGHT;
//STRIP001              rText += SW_RESSTR( nId );
//STRIP001              rText += ' ';
//STRIP001              if ( GetHeightPercent() )
//STRIP001              {
//STRIP001                  rText += String::CreateFromInt32(GetHeightPercent());
//STRIP001                  rText += '%';
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  rText += ::GetMetricText( GetHeight(), eCoreUnit, ePresUnit, pIntl );
//STRIP001                  rText += ::GetSvxString( ::GetMetricId( ePresUnit ) );
//STRIP001              }
//STRIP001          }
//STRIP001          return ePres;
//STRIP001      }
//STRIP001  }
//STRIP001  return SFX_ITEM_PRESENTATION_NONE;
//STRIP001 }

//Kopfzeile, fuer Seitenformate
//Client von FrmFmt das den Header beschreibt.


//STRIP001 SfxItemPresentation SwFmtHeader::GetPresentation
//STRIP001 (
//STRIP001  SfxItemPresentation ePres,
//STRIP001  SfxMapUnit          eCoreUnit,
//STRIP001  SfxMapUnit          ePresUnit,
//STRIP001  String&             rText,
//STRIP001     const IntlWrapper*        pIntl
//STRIP001 )    const
//STRIP001 {
//STRIP001  switch ( ePres )
//STRIP001  {
//STRIP001      case SFX_ITEM_PRESENTATION_NONE:
//STRIP001          rText.Erase();
//STRIP001          break;
//STRIP001      case SFX_ITEM_PRESENTATION_NAMELESS:
//STRIP001      case SFX_ITEM_PRESENTATION_COMPLETE:
//STRIP001      {
//STRIP001          const USHORT nId = GetHeaderFmt() ? STR_HEADER : STR_NO_HEADER;
//STRIP001          rText = SW_RESSTR( nId );
//STRIP001          return ePres;
//STRIP001      }
//STRIP001  }
//STRIP001  return SFX_ITEM_PRESENTATION_NONE;
//STRIP001 }

//Fusszeile, fuer Seitenformate
//Client von FrmFmt das den Footer beschreibt.


//STRIP001 SfxItemPresentation SwFmtFooter::GetPresentation
//STRIP001 (
//STRIP001  SfxItemPresentation ePres,
//STRIP001  SfxMapUnit          eCoreUnit,
//STRIP001  SfxMapUnit          ePresUnit,
//STRIP001  String&             rText,
//STRIP001     const IntlWrapper*        pIntl
//STRIP001 )    const
//STRIP001 {
//STRIP001  switch ( ePres )
//STRIP001  {
//STRIP001      case SFX_ITEM_PRESENTATION_NONE:
//STRIP001          rText.Erase();
//STRIP001          break;
//STRIP001      case SFX_ITEM_PRESENTATION_NAMELESS:
//STRIP001      case SFX_ITEM_PRESENTATION_COMPLETE:
//STRIP001      {
//STRIP001          const USHORT nId = GetFooterFmt() ? STR_FOOTER : STR_NO_FOOTER;
//STRIP001          rText = SW_RESSTR( nId );
//STRIP001          return ePres;
//STRIP001      }
//STRIP001  }
//STRIP001  return SFX_ITEM_PRESENTATION_NONE;
//STRIP001 }


//STRIP001 SfxItemPresentation SwFmtSurround::GetPresentation
//STRIP001 (
//STRIP001  SfxItemPresentation ePres,
//STRIP001  SfxMapUnit          eCoreUnit,
//STRIP001  SfxMapUnit          ePresUnit,
//STRIP001  String&             rText,
//STRIP001     const IntlWrapper*        pIntl
//STRIP001 )    const
//STRIP001 {
//STRIP001  switch ( ePres )
//STRIP001  {
//STRIP001      case SFX_ITEM_PRESENTATION_NONE:
//STRIP001          rText.Erase();
//STRIP001          break;
//STRIP001      case SFX_ITEM_PRESENTATION_NAMELESS:
//STRIP001      case SFX_ITEM_PRESENTATION_COMPLETE:
//STRIP001      {
//STRIP001          USHORT nId = 0;
//STRIP001          switch ( (SwSurround)GetValue() )
//STRIP001          {
//STRIP001              case SURROUND_NONE:
//STRIP001                  nId = STR_SURROUND_NONE;
//STRIP001              break;
//STRIP001              case SURROUND_THROUGHT:
//STRIP001                  nId = STR_SURROUND_THROUGHT;
//STRIP001              break;
//STRIP001              case SURROUND_PARALLEL:
//STRIP001                  nId = STR_SURROUND_PARALLEL;
//STRIP001              break;
//STRIP001              case SURROUND_IDEAL:
//STRIP001                  nId = STR_SURROUND_IDEAL;
//STRIP001              break;
//STRIP001              case SURROUND_LEFT:
//STRIP001                  nId = STR_SURROUND_LEFT;
//STRIP001              break;
//STRIP001              case SURROUND_RIGHT:
//STRIP001                  nId = STR_SURROUND_RIGHT;
//STRIP001              break;
//STRIP001          }
//STRIP001          if ( nId )
//STRIP001              rText = SW_RESSTR( nId );
//STRIP001
//STRIP001          if ( IsAnchorOnly() )
//STRIP001          {
//STRIP001              rText += ' ';
//STRIP001              rText += SW_RESSTR( STR_SURROUND_ANCHORONLY );
//STRIP001          }
//STRIP001          return ePres;
//STRIP001      }
//STRIP001  }
//STRIP001  return SFX_ITEM_PRESENTATION_NONE;
//STRIP001 }


//VertOrientation, wie und woran orientiert --
//  sich der FlyFrm in der Vertikalen -----------


//STRIP001 SfxItemPresentation SwFmtVertOrient::GetPresentation
//STRIP001 (
//STRIP001  SfxItemPresentation ePres,
//STRIP001  SfxMapUnit          eCoreUnit,
//STRIP001  SfxMapUnit          ePresUnit,
//STRIP001  String&             rText,
//STRIP001     const IntlWrapper*        pIntl
//STRIP001 )    const
//STRIP001 {
//STRIP001  switch ( ePres )
//STRIP001  {
//STRIP001      case SFX_ITEM_PRESENTATION_NONE:
//STRIP001          rText.Erase();
//STRIP001          break;
//STRIP001      case SFX_ITEM_PRESENTATION_NAMELESS:
//STRIP001      case SFX_ITEM_PRESENTATION_COMPLETE:
//STRIP001      {
//STRIP001          USHORT nId = 0;
//STRIP001          switch ( GetVertOrient() )
//STRIP001          {
//STRIP001              case VERT_NONE:
//STRIP001              {
//STRIP001                  rText += SW_RESSTR( STR_POS_Y );
//STRIP001                  rText += ' ';
//STRIP001                  rText += ::GetMetricText( GetPos(), eCoreUnit, ePresUnit, pIntl );
//STRIP001                  rText += ::GetSvxString( ::GetMetricId( ePresUnit ) );
//STRIP001              }
//STRIP001              break;
//STRIP001              case VERT_TOP:
//STRIP001                  nId = STR_VERT_TOP;
//STRIP001                  break;
//STRIP001              case VERT_CENTER:
//STRIP001                  nId = STR_VERT_CENTER;
//STRIP001                  break;
//STRIP001              case VERT_BOTTOM:
//STRIP001                  nId = STR_VERT_BOTTOM;
//STRIP001                  break;
//STRIP001              case VERT_LINE_TOP:
//STRIP001                  nId = STR_LINE_TOP;
//STRIP001                  break;
//STRIP001              case VERT_LINE_CENTER:
//STRIP001                  nId = STR_LINE_CENTER;
//STRIP001                  break;
//STRIP001              case VERT_LINE_BOTTOM:
//STRIP001                  nId = STR_LINE_BOTTOM;
//STRIP001                  break;
//STRIP001          }
//STRIP001          if ( nId )
//STRIP001              rText += SW_RESSTR( nId );
//STRIP001          return ePres;
//STRIP001      }
//STRIP001  }
//STRIP001  return SFX_ITEM_PRESENTATION_NONE;
//STRIP001 }

//HoriOrientation, wie und woran orientiert --
//  sich der FlyFrm in der Hoizontalen ----------


//STRIP001 SfxItemPresentation SwFmtHoriOrient::GetPresentation
//STRIP001 (
//STRIP001  SfxItemPresentation ePres,
//STRIP001  SfxMapUnit          eCoreUnit,
//STRIP001  SfxMapUnit          ePresUnit,
//STRIP001  String&             rText,
//STRIP001     const IntlWrapper*        pIntl
//STRIP001 )    const
//STRIP001 {
//STRIP001  switch ( ePres )
//STRIP001  {
//STRIP001      case SFX_ITEM_PRESENTATION_NONE:
//STRIP001          rText.Erase();
//STRIP001          break;
//STRIP001      case SFX_ITEM_PRESENTATION_NAMELESS:
//STRIP001      case SFX_ITEM_PRESENTATION_COMPLETE:
//STRIP001      {
//STRIP001          USHORT nId = 0;
//STRIP001          switch ( GetHoriOrient() )
//STRIP001          {
//STRIP001              case HORI_NONE:
//STRIP001              {
//STRIP001                  rText += SW_RESSTR( STR_POS_X );
//STRIP001                  rText += ' ';
//STRIP001                  rText += ::GetMetricText( GetPos(), eCoreUnit, ePresUnit, pIntl );
//STRIP001                  rText += ::GetSvxString( ::GetMetricId( ePresUnit ) );
//STRIP001              }
//STRIP001              break;
//STRIP001              case HORI_RIGHT:
//STRIP001                  nId = STR_HORI_RIGHT;
//STRIP001              break;
//STRIP001              case HORI_CENTER:
//STRIP001                  nId = STR_HORI_CENTER;
//STRIP001              break;
//STRIP001              case HORI_LEFT:
//STRIP001                  nId = STR_HORI_LEFT;
//STRIP001              break;
//STRIP001              case HORI_INSIDE:
//STRIP001                  nId = STR_HORI_INSIDE;
//STRIP001              break;
//STRIP001              case HORI_OUTSIDE:
//STRIP001                  nId = STR_HORI_OUTSIDE;
//STRIP001              break;
//STRIP001              case HORI_FULL:
//STRIP001                  nId = STR_HORI_FULL;
//STRIP001              break;
//STRIP001          }
//STRIP001          if ( nId )
//STRIP001              rText += SW_RESSTR( nId );
//STRIP001          return ePres;
//STRIP001      }
//STRIP001  }
//STRIP001  return SFX_ITEM_PRESENTATION_NONE;
//STRIP001 }

//FlyAnchor, Anker des Freifliegenden Rahmen ----


//STRIP001 SfxItemPresentation SwFmtAnchor::GetPresentation
//STRIP001 (
//STRIP001  SfxItemPresentation ePres,
//STRIP001  SfxMapUnit          eCoreUnit,
//STRIP001  SfxMapUnit          ePresUnit,
//STRIP001  String&             rText,
//STRIP001     const IntlWrapper*        pIntl
//STRIP001 )    const
//STRIP001 {
//STRIP001  switch ( ePres )
//STRIP001  {
//STRIP001      case SFX_ITEM_PRESENTATION_NONE:
//STRIP001          rText.Erase();
//STRIP001          break;
//STRIP001      case SFX_ITEM_PRESENTATION_NAMELESS:
//STRIP001      case SFX_ITEM_PRESENTATION_COMPLETE:
//STRIP001      {
//STRIP001          USHORT nId = 0;
//STRIP001          switch ( GetAnchorId() )
//STRIP001          {
//STRIP001              case FLY_AT_CNTNT:      //Absatzgebundener Rahmen
//STRIP001                  nId = STR_FLY_AT_CNTNT;
//STRIP001                  break;
//STRIP001              case FLY_IN_CNTNT:      //Zeichengebundener Rahmen
//STRIP001                  nId = STR_FLY_IN_CNTNT;
//STRIP001                  break;
//STRIP001              case FLY_PAGE:          //Seitengebundener Rahmen
//STRIP001                  nId = STR_FLY_PAGE;
//STRIP001                  break;
//STRIP001          }
//STRIP001          if ( nId )
//STRIP001              rText += SW_RESSTR( nId );
//STRIP001          return ePres;
//STRIP001      }
//STRIP001  }
//STRIP001  return SFX_ITEM_PRESENTATION_NONE;
//STRIP001 }


//STRIP001 SfxItemPresentation SwFmtPageDesc::GetPresentation
//STRIP001 (
//STRIP001  SfxItemPresentation ePres,
//STRIP001  SfxMapUnit          eCoreUnit,
//STRIP001  SfxMapUnit          ePresUnit,
//STRIP001  String&             rText,
//STRIP001     const IntlWrapper*        pIntl
//STRIP001 )    const
//STRIP001 {
//STRIP001  switch ( ePres )
//STRIP001  {
//STRIP001      case SFX_ITEM_PRESENTATION_NONE:
//STRIP001          rText.Erase();
//STRIP001          break;
//STRIP001      case SFX_ITEM_PRESENTATION_NAMELESS:
//STRIP001      case SFX_ITEM_PRESENTATION_COMPLETE:
//STRIP001      {
//STRIP001          const SwPageDesc *pPageDesc = GetPageDesc();
//STRIP001          if ( pPageDesc )
//STRIP001              rText = pPageDesc->GetName();
//STRIP001          else
//STRIP001              rText = SW_RESSTR( STR_NO_PAGEDESC );
//STRIP001          return ePres;
//STRIP001      }
//STRIP001  }
//STRIP001  return SFX_ITEM_PRESENTATION_NONE;
//STRIP001 }

//Der ColumnDescriptor --------------------------


//STRIP001 SfxItemPresentation SwFmtCol::GetPresentation
//STRIP001 (
//STRIP001  SfxItemPresentation ePres,
//STRIP001  SfxMapUnit          eCoreUnit,
//STRIP001  SfxMapUnit          ePresUnit,
//STRIP001  String&             rText,
//STRIP001     const IntlWrapper*        pIntl
//STRIP001 )    const
//STRIP001 {
//STRIP001  switch ( ePres )
//STRIP001  {
//STRIP001      case SFX_ITEM_PRESENTATION_NONE:
//STRIP001          rText.Erase();
//STRIP001          break;
//STRIP001      case SFX_ITEM_PRESENTATION_NAMELESS:
//STRIP001      case SFX_ITEM_PRESENTATION_COMPLETE:
//STRIP001      {
//STRIP001          USHORT nCnt = GetNumCols();
//STRIP001          if ( nCnt > 1 )
//STRIP001          {
//STRIP001              rText = String::CreateFromInt32(nCnt);
//STRIP001              rText += ' ';
//STRIP001              rText += SW_RESSTR( STR_COLUMNS );
//STRIP001              if ( COLADJ_NONE != GetLineAdj() )
//STRIP001              {
//STRIP001                  USHORT nWdth = USHORT(GetLineWidth());
//STRIP001                  rText += ' ';
//STRIP001                  rText += SW_RESSTR( STR_LINE_WIDTH );
//STRIP001                  rText += ' ';
//STRIP001                  rText += ::GetMetricText( nWdth, eCoreUnit,
//STRIP001                                               SFX_MAPUNIT_POINT, pIntl );
//STRIP001              }
//STRIP001          }
//STRIP001          else
//STRIP001              rText.Erase();
//STRIP001          return ePres;
//STRIP001      }
//STRIP001  }
//STRIP001  return SFX_ITEM_PRESENTATION_NONE;
//STRIP001 }

//URL's und Maps


//STRIP001 SfxItemPresentation SwFmtURL::GetPresentation
//STRIP001 (
//STRIP001  SfxItemPresentation ePres,
//STRIP001  SfxMapUnit          eCoreUnit,
//STRIP001  SfxMapUnit          ePresUnit,
//STRIP001  String&             rText,
//STRIP001     const IntlWrapper*        pIntl
//STRIP001 )    const
//STRIP001 {
//STRIP001  rText.Erase();
//STRIP001  switch ( ePres )
//STRIP001  {
//STRIP001      case SFX_ITEM_PRESENTATION_NONE:
//STRIP001          break;
//STRIP001      case SFX_ITEM_PRESENTATION_NAMELESS:
//STRIP001      case SFX_ITEM_PRESENTATION_COMPLETE:
//STRIP001      {
//STRIP001          if ( pMap )
//STRIP001              rText.AppendAscii( RTL_CONSTASCII_STRINGPARAM("Client-Map"));
//STRIP001          if ( sURL.Len() )
//STRIP001          {
//STRIP001              if ( pMap )
//STRIP001                  rText.AppendAscii( RTL_CONSTASCII_STRINGPARAM(" - "));
//STRIP001              rText.AppendAscii( RTL_CONSTASCII_STRINGPARAM("URL: "));
//STRIP001              rText += sURL;
//STRIP001              if ( bIsServerMap )
//STRIP001                  rText.AppendAscii( RTL_CONSTASCII_STRINGPARAM(" (Server-Map)"));
//STRIP001          }
//STRIP001          if ( sTargetFrameName.Len() )
//STRIP001          {
//STRIP001              rText.AppendAscii( RTL_CONSTASCII_STRINGPARAM(", Target: "));
//STRIP001              rText += sTargetFrameName;
//STRIP001          }
//STRIP001          return ePres;
//STRIP001      }
//STRIP001  }
//STRIP001  return SFX_ITEM_PRESENTATION_NONE;
//STRIP001 }


//SwFmtEditInReadonly


//STRIP001 SfxItemPresentation SwFmtEditInReadonly::GetPresentation
//STRIP001 (
//STRIP001  SfxItemPresentation ePres,
//STRIP001  SfxMapUnit          eCoreUnit,
//STRIP001  SfxMapUnit          ePresUnit,
//STRIP001  String&             rText,
//STRIP001     const IntlWrapper*        pIntl
//STRIP001 )    const
//STRIP001 {
//STRIP001  rText.Erase();
//STRIP001  switch ( ePres )
//STRIP001  {
//STRIP001      case SFX_ITEM_PRESENTATION_NONE:
//STRIP001          rText.Erase();
//STRIP001          break;
//STRIP001      case SFX_ITEM_PRESENTATION_NAMELESS:
//STRIP001      case SFX_ITEM_PRESENTATION_COMPLETE:
//STRIP001      {
//STRIP001          if ( GetValue() )
//STRIP001              rText = SW_RESSTR(STR_EDIT_IN_READONLY);
//STRIP001          return ePres;
//STRIP001      }
//STRIP001  }
//STRIP001  return SFX_ITEM_PRESENTATION_NONE;
//STRIP001 }


//STRIP001 SfxItemPresentation SwFmtLayoutSplit::GetPresentation
//STRIP001 (
//STRIP001  SfxItemPresentation ePres,
//STRIP001  SfxMapUnit          eCoreUnit,
//STRIP001  SfxMapUnit          ePresUnit,
//STRIP001  String&             rText,
//STRIP001     const IntlWrapper*        pIntl
//STRIP001 )    const
//STRIP001 {
//STRIP001  switch ( ePres )
//STRIP001  {
//STRIP001      case SFX_ITEM_PRESENTATION_NONE:
//STRIP001          rText.Erase();
//STRIP001          return SFX_ITEM_PRESENTATION_NONE;
//STRIP001      case SFX_ITEM_PRESENTATION_NAMELESS:
//STRIP001      case SFX_ITEM_PRESENTATION_COMPLETE:
//STRIP001      {
//STRIP001          if ( GetValue() )
//STRIP001              rText = SW_RESSTR(STR_LAYOUT_SPLIT);
//STRIP001          return ePres;
//STRIP001      }
//STRIP001  }
//STRIP001  return SFX_ITEM_PRESENTATION_NONE;
//STRIP001 }

//STRIP001 SfxItemPresentation SwFmtFtnEndAtTxtEnd::GetPresentation
//STRIP001 (
//STRIP001  SfxItemPresentation ePres,
//STRIP001  SfxMapUnit          eCoreUnit,
//STRIP001  SfxMapUnit          ePresUnit,
//STRIP001  String&             rText,
//STRIP001     const IntlWrapper*        pIntl
//STRIP001 )    const
//STRIP001 {
//STRIP001  switch ( ePres )
//STRIP001  {
//STRIP001      case SFX_ITEM_PRESENTATION_NONE:
//STRIP001          rText.Erase();
//STRIP001          break;
//STRIP001
//STRIP001      case SFX_ITEM_PRESENTATION_NAMELESS:
//STRIP001      case SFX_ITEM_PRESENTATION_COMPLETE:
//STRIP001          {
//STRIP001              switch( GetValue() )
//STRIP001              {
//STRIP001              case FTNEND_ATPGORDOCEND:
//STRIP001 //                   rText = SW_RESSTR( STR_LAYOUT_FTN );
//STRIP001                  break;
//STRIP001
//STRIP001              case FTNEND_ATTXTEND:
//STRIP001                  break;
//STRIP001
//STRIP001              case FTNEND_ATTXTEND_OWNNUMSEQ:
//STRIP001                  {
//STRIP001 //   String      sPrefix;
//STRIP001 //   String      sSuffix;
//STRIP001 //   SvxNumberType   aFmt;
//STRIP001 //   USHORT      nOffset;
//STRIP001 //                       rText +=
//STRIP001                  }
//STRIP001                  break;
//STRIP001              }
//STRIP001          }
//STRIP001          break;
//STRIP001
//STRIP001      default:
//STRIP001          ePres = SFX_ITEM_PRESENTATION_NONE;
//STRIP001          break;
//STRIP001  }
//STRIP001  return ePres;
//STRIP001 }

//STRIP001 SfxItemPresentation SwFmtChain::GetPresentation
//STRIP001 (
//STRIP001  SfxItemPresentation ePres,
//STRIP001  SfxMapUnit          eCoreUnit,
//STRIP001  SfxMapUnit          ePresUnit,
//STRIP001  String&             rText,
//STRIP001     const IntlWrapper*        pIntl
//STRIP001 )    const
//STRIP001 {
//STRIP001  switch ( ePres )
//STRIP001  {
//STRIP001      case SFX_ITEM_PRESENTATION_NONE:
//STRIP001          rText.Erase();
//STRIP001          return SFX_ITEM_PRESENTATION_NONE;
//STRIP001      case SFX_ITEM_PRESENTATION_NAMELESS:
//STRIP001      case SFX_ITEM_PRESENTATION_COMPLETE:
//STRIP001      {
//STRIP001          if ( GetPrev() || GetNext() )
//STRIP001          {
//STRIP001              rText = SW_RESSTR(STR_CONNECT1);
//STRIP001              if ( GetPrev() )
//STRIP001              {
//STRIP001                  rText += GetPrev()->GetName();
//STRIP001                  if ( GetNext() )
//STRIP001                      rText += SW_RESSTR(STR_CONNECT2);
//STRIP001              }
//STRIP001              if ( GetNext() )
//STRIP001                  rText += GetNext()->GetName();
//STRIP001          }
//STRIP001          return ePres;
//STRIP001      }
//STRIP001  }
//STRIP001  return SFX_ITEM_PRESENTATION_NONE;
//STRIP001 }


//STRIP001 SfxItemPresentation SwFmtLineNumber::GetPresentation
//STRIP001 (
//STRIP001  SfxItemPresentation ePres,
//STRIP001  SfxMapUnit          eCoreUnit,
//STRIP001  SfxMapUnit          ePresUnit,
//STRIP001  String&             rText,
//STRIP001     const IntlWrapper*    pIntl
//STRIP001 )    const
//STRIP001 {
//STRIP001  switch ( ePres )
//STRIP001  {
//STRIP001      case SFX_ITEM_PRESENTATION_NONE:
//STRIP001          rText.Erase();
//STRIP001          return SFX_ITEM_PRESENTATION_NONE;
//STRIP001      case SFX_ITEM_PRESENTATION_NAMELESS:
//STRIP001      case SFX_ITEM_PRESENTATION_COMPLETE:
//STRIP001      {
//STRIP001          if ( IsCount() )
//STRIP001              rText += SW_RESSTR(STR_LINECOUNT);
//STRIP001          else
//STRIP001              rText += SW_RESSTR(STR_DONTLINECOUNT);
//STRIP001          if ( GetStartValue() )
//STRIP001          {
//STRIP001              rText += ' ';
//STRIP001              rText += SW_RESSTR(STR_LINCOUNT_START);
//STRIP001              rText += String::CreateFromInt32(GetStartValue());
//STRIP001          }
//STRIP001          return ePres;
//STRIP001      }
//STRIP001  }
//STRIP001  return SFX_ITEM_PRESENTATION_NONE;
//STRIP001 }

//STRIP001 SfxItemPresentation SwTextGridItem::GetPresentation
//STRIP001 (
//STRIP001     SfxItemPresentation ePres,
//STRIP001  SfxMapUnit          eCoreUnit,
//STRIP001  SfxMapUnit          ePresUnit,
//STRIP001  String&             rText,
//STRIP001     const IntlWrapper*  pIntl
//STRIP001 )    const
//STRIP001 {
//STRIP001  switch ( ePres )
//STRIP001  {
//STRIP001      case SFX_ITEM_PRESENTATION_NONE:
//STRIP001          rText.Erase();
//STRIP001          return SFX_ITEM_PRESENTATION_NONE;
//STRIP001      case SFX_ITEM_PRESENTATION_NAMELESS:
//STRIP001      case SFX_ITEM_PRESENTATION_COMPLETE:
//STRIP001      {
//STRIP001          USHORT nId = 0;
//STRIP001
//STRIP001             switch ( GetGridType() )
//STRIP001             {
//STRIP001             case GRID_NONE :
//STRIP001                 nId = STR_GRID_NONE;
//STRIP001                 break;
//STRIP001             case GRID_LINES_ONLY :
//STRIP001                 nId = STR_GRID_LINES_ONLY;
//STRIP001                 break;
//STRIP001             case GRID_LINES_CHARS :
//STRIP001                 nId = STR_GRID_LINES_CHARS;
//STRIP001                 break;
//STRIP001             }
//STRIP001          if ( nId )
//STRIP001                 rText += SW_RESSTR( nId );
//STRIP001          return ePres;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001     return SFX_ITEM_PRESENTATION_NONE;
//STRIP001 }


//SwHeaderAndFooterEatSpacingItem


/*M*/ SfxItemPresentation SwHeaderAndFooterEatSpacingItem::GetPresentation
/*M*/ (
/*M*/   SfxItemPresentation ePres,
/*M*/   SfxMapUnit          eCoreUnit,
/*M*/   SfxMapUnit          ePresUnit,
/*M*/   String&             rText,
/*M*/     const IntlWrapper*        pIntl
/*M*/ ) const
/*M*/ {
//    rText.Erase();
//    switch ( ePres )
//    {
//        case SFX_ITEM_PRESENTATION_NONE:
//            rText.Erase();
//            break;
//        case SFX_ITEM_PRESENTATION_NAMELESS:
//        case SFX_ITEM_PRESENTATION_COMPLETE:
//        {
//            if ( GetValue() )
//                rText = SW_RESSTR(STR_EDIT_IN_READONLY);
//            return ePres;
//        }
//    }
/*M*/   return SFX_ITEM_PRESENTATION_NONE;
/*M*/ }


// ---------------------- Grafik-Attribute --------------------------

//STRIP001 SfxItemPresentation SwMirrorGrf::GetPresentation(
//STRIP001  SfxItemPresentation ePres, SfxMapUnit eCoreUnit, SfxMapUnit ePresUnit,
//STRIP001     String& rText, const IntlWrapper* pIntl ) const
//STRIP001 {
//STRIP001  switch ( ePres )
//STRIP001  {
//STRIP001  case SFX_ITEM_PRESENTATION_NAMELESS:
//STRIP001  case SFX_ITEM_PRESENTATION_COMPLETE:
//STRIP001      {
//STRIP001          USHORT nId;
//STRIP001          switch( GetValue() )
//STRIP001          {
//STRIP001          case RES_DONT_MIRROR_GRF:   nId = STR_NO_MIRROR;    break;
//STRIP001          case RES_MIRROR_GRF_VERT:   nId = STR_VERT_MIRROR;  break;
//STRIP001          case RES_MIRROR_GRF_HOR:    nId = STR_HORI_MIRROR;  break;
//STRIP001          case RES_MIRROR_GRF_BOTH:   nId = STR_BOTH_MIRROR;  break;
//STRIP001          default:                    nId = 0;    break;
//STRIP001          }
//STRIP001          if ( nId )
//STRIP001          {
//STRIP001              rText = SW_RESSTR( nId );
//STRIP001              if (bGrfToggle)
//STRIP001                  rText += SW_RESSTR( STR_MIRROR_TOGGLE );
//STRIP001          }
//STRIP001      }
//STRIP001      break;
//STRIP001  default:
//STRIP001      ePres = SFX_ITEM_PRESENTATION_NONE;
//STRIP001      rText.Erase();
//STRIP001      break;
//STRIP001  }
//STRIP001  return ePres;
//STRIP001 }


//STRIP001 SfxItemPresentation SwRotationGrf::GetPresentation(
//STRIP001  SfxItemPresentation ePres, SfxMapUnit eCoreUnit, SfxMapUnit ePresUnit,
//STRIP001     String &rText, const IntlWrapper* pIntl) const
//STRIP001 {
//STRIP001  switch( ePres )
//STRIP001  {
//STRIP001  case SFX_ITEM_PRESENTATION_NAMELESS:
//STRIP001  case SFX_ITEM_PRESENTATION_COMPLETE:
//STRIP001      if( SFX_ITEM_PRESENTATION_COMPLETE == ePres )
//STRIP001          rText = SW_RESSTR( STR_ROTATION );
//STRIP001      else if( rText.Len() )
//STRIP001          rText.Erase();
//STRIP001      ( rText += UniString::CreateFromInt32( GetValue() )) += '°';
//STRIP001      break;
//STRIP001
//STRIP001  default:
//STRIP001      ePres = SFX_ITEM_PRESENTATION_NONE;
//STRIP001      rText.Erase();
//STRIP001      break;
//STRIP001  }
//STRIP001  return ePres;
//STRIP001 }

//STRIP001 SfxItemPresentation SwLuminanceGrf::GetPresentation(
//STRIP001  SfxItemPresentation ePres, SfxMapUnit eCoreUnit, SfxMapUnit ePresUnit,
//STRIP001     String &rText, const IntlWrapper* pIntl) const
//STRIP001 {
//STRIP001  switch( ePres )
//STRIP001  {
//STRIP001  case SFX_ITEM_PRESENTATION_NAMELESS:
//STRIP001  case SFX_ITEM_PRESENTATION_COMPLETE:
//STRIP001      if( SFX_ITEM_PRESENTATION_COMPLETE == ePres )
//STRIP001          rText = SW_RESSTR( STR_LUMINANCE );
//STRIP001      else if( rText.Len() )
//STRIP001          rText.Erase();
//STRIP001      ( rText += UniString::CreateFromInt32( GetValue() )) += '%';
//STRIP001      break;
//STRIP001
//STRIP001  default:
//STRIP001      ePres = SFX_ITEM_PRESENTATION_NONE;
//STRIP001      rText.Erase();
//STRIP001      break;
//STRIP001  }
//STRIP001  return ePres;
//STRIP001 }

//STRIP001 SfxItemPresentation SwContrastGrf::GetPresentation(
//STRIP001  SfxItemPresentation ePres, SfxMapUnit eCoreUnit, SfxMapUnit ePresUnit,
//STRIP001     String &rText, const IntlWrapper* pIntl) const
//STRIP001 {
//STRIP001  switch( ePres )
//STRIP001  {
//STRIP001  case SFX_ITEM_PRESENTATION_NAMELESS:
//STRIP001  case SFX_ITEM_PRESENTATION_COMPLETE:
//STRIP001      if( SFX_ITEM_PRESENTATION_COMPLETE == ePres )
//STRIP001          rText = SW_RESSTR( STR_CONTRAST );
//STRIP001      else if( rText.Len() )
//STRIP001          rText.Erase();
//STRIP001      ( rText += UniString::CreateFromInt32( GetValue() )) += '%';
//STRIP001      break;
//STRIP001
//STRIP001  default:
//STRIP001      ePres = SFX_ITEM_PRESENTATION_NONE;
//STRIP001      rText.Erase();
//STRIP001      break;
//STRIP001  }
//STRIP001  return ePres;
//STRIP001 }

//STRIP001 SfxItemPresentation SwChannelGrf::GetPresentation(
//STRIP001  SfxItemPresentation ePres, SfxMapUnit eCoreUnit, SfxMapUnit ePresUnit,
//STRIP001     String &rText, const IntlWrapper* pIntl) const
//STRIP001 {
//STRIP001  switch( ePres )
//STRIP001  {
//STRIP001  case SFX_ITEM_PRESENTATION_NAMELESS:
//STRIP001  case SFX_ITEM_PRESENTATION_COMPLETE:
//STRIP001      if( SFX_ITEM_PRESENTATION_COMPLETE == ePres )
//STRIP001      {
//STRIP001          USHORT nId;
//STRIP001          switch ( Which() )
//STRIP001          {
//STRIP001          case RES_GRFATR_CHANNELR:   nId = STR_CHANNELR; break;
//STRIP001          case RES_GRFATR_CHANNELG:   nId = STR_CHANNELG; break;
//STRIP001          case RES_GRFATR_CHANNELB:   nId = STR_CHANNELB; break;
//STRIP001          default:                    nId = 0; break;
//STRIP001          }
//STRIP001          if( nId )
//STRIP001              rText = SW_RESSTR( nId );
//STRIP001          else if( rText.Len() )
//STRIP001              rText.Erase();
//STRIP001      }
//STRIP001      else if( rText.Len() )
//STRIP001          rText.Erase();
//STRIP001      ( rText += UniString::CreateFromInt32( GetValue() )) += '%';
//STRIP001      break;
//STRIP001
//STRIP001  default:
//STRIP001      ePres = SFX_ITEM_PRESENTATION_NONE;
//STRIP001      rText.Erase();
//STRIP001      break;
//STRIP001  }
//STRIP001  return ePres;
//STRIP001 }

//STRIP001 SfxItemPresentation SwGammaGrf::GetPresentation(
//STRIP001  SfxItemPresentation ePres, SfxMapUnit eCoreUnit, SfxMapUnit ePresUnit,
//STRIP001     String &rText, const IntlWrapper* pIntl) const
//STRIP001 {
//STRIP001  switch( ePres )
//STRIP001  {
//STRIP001  case SFX_ITEM_PRESENTATION_NAMELESS:
//STRIP001  case SFX_ITEM_PRESENTATION_COMPLETE:
//STRIP001      if( SFX_ITEM_PRESENTATION_COMPLETE == ePres )
//STRIP001          rText = SW_RESSTR( STR_GAMMA );
//STRIP001      else if( rText.Len() )
//STRIP001          rText.Erase();
//STRIP001      ( rText += UniString::CreateFromDouble( GetValue() )) += '%';
//STRIP001      break;
//STRIP001
//STRIP001  default:
//STRIP001      ePres = SFX_ITEM_PRESENTATION_NONE;
//STRIP001      rText.Erase();
//STRIP001      break;
//STRIP001  }
//STRIP001  return ePres;
//STRIP001 }

//STRIP001 SfxItemPresentation SwInvertGrf::GetPresentation(
//STRIP001  SfxItemPresentation ePres, SfxMapUnit eCoreUnit, SfxMapUnit ePresUnit,
//STRIP001     String &rText, const IntlWrapper* pIntl) const
//STRIP001 {
//STRIP001  rText.Erase();
//STRIP001  switch( ePres )
//STRIP001  {
//STRIP001  case SFX_ITEM_PRESENTATION_NAMELESS:
//STRIP001  case SFX_ITEM_PRESENTATION_COMPLETE:
//STRIP001      if( SFX_ITEM_PRESENTATION_COMPLETE == ePres )
//STRIP001      {
//STRIP001          USHORT nId = 0 != GetValue() ? STR_INVERT : STR_INVERT_NOT;
//STRIP001          rText = SW_RESSTR( nId );
//STRIP001      }
//STRIP001      break;
//STRIP001
//STRIP001  default:
//STRIP001      ePres = SFX_ITEM_PRESENTATION_NONE;
//STRIP001      break;
//STRIP001  }
//STRIP001  return ePres;
//STRIP001 }

//STRIP001 SfxItemPresentation SwTransparencyGrf::GetPresentation(
//STRIP001  SfxItemPresentation ePres, SfxMapUnit eCoreUnit, SfxMapUnit ePresUnit,
//STRIP001     String &rText, const IntlWrapper* pIntl) const
//STRIP001 {
//STRIP001  switch( ePres )
//STRIP001  {
//STRIP001  case SFX_ITEM_PRESENTATION_NAMELESS:
//STRIP001  case SFX_ITEM_PRESENTATION_COMPLETE:
//STRIP001      if( SFX_ITEM_PRESENTATION_COMPLETE == ePres )
//STRIP001          rText = SW_RESSTR( STR_TRANSPARENCY );
//STRIP001      else if( rText.Len() )
//STRIP001          rText.Erase();
//STRIP001      ( rText += UniString::CreateFromInt32( GetValue() )) += '%';
//STRIP001      break;
//STRIP001
//STRIP001  default:
//STRIP001      ePres = SFX_ITEM_PRESENTATION_NONE;
//STRIP001      rText.Erase();
//STRIP001      break;
//STRIP001  }
//STRIP001  return ePres;
//STRIP001 }

//STRIP001 SfxItemPresentation SwDrawModeGrf::GetPresentation(
//STRIP001  SfxItemPresentation ePres, SfxMapUnit eCoreUnit, SfxMapUnit ePresUnit,
//STRIP001     String &rText, const IntlWrapper* pIntl) const
//STRIP001 {
//STRIP001  rText.Erase();
//STRIP001  switch( ePres )
//STRIP001  {
//STRIP001  case SFX_ITEM_PRESENTATION_NAMELESS:
//STRIP001  case SFX_ITEM_PRESENTATION_COMPLETE:
//STRIP001      if( SFX_ITEM_PRESENTATION_COMPLETE == ePres )
//STRIP001      {
//STRIP001          USHORT nId;
//STRIP001          switch ( GetValue() )
//STRIP001          {
//STRIP001
//STRIP001          case GRAPHICDRAWMODE_GREYS:     nId = STR_DRAWMODE_GREY; break;
//STRIP001          case GRAPHICDRAWMODE_MONO:      nId = STR_DRAWMODE_BLACKWHITE; break;
//STRIP001          case GRAPHICDRAWMODE_WATERMARK: nId = STR_DRAWMODE_WATERMARK; break;
//STRIP001          default:                        nId = STR_DRAWMODE_STD; break;
//STRIP001          }
//STRIP001          (rText = SW_RESSTR( STR_DRAWMODE ) ) += SW_RESSTR( nId );
//STRIP001      }
//STRIP001      break;
//STRIP001
//STRIP001  default:
//STRIP001      ePres = SFX_ITEM_PRESENTATION_NONE;
//STRIP001      break;
//STRIP001  }
//STRIP001  return ePres;
//STRIP001 }


}
