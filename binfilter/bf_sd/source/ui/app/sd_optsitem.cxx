/*************************************************************************
 *
 *  $RCSfile: sd_optsitem.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:34:45 $
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

#ifndef _SVDMODEL_HXX //autogen
#include <bf_svx/svdmodel.hxx>
#endif
#ifndef _SFXAPP_HXX //autogen
#include <bf_sfx2/app.hxx>
#endif
#ifndef _SFX_HRC //autogen
#include <bf_sfx2/sfx.hrc>
#endif
#ifndef _SV_SALBTYPE_HRC //autogen
#include <vcl/salbtype.hxx>
#endif
#ifndef INCLUDED_SVTOOLS_SYSLOCALE_HXX
#include <svtools/syslocale.hxx>
#endif

#include "app.hxx"
#include "optsitem.hxx"
#include "cfgids.hxx"
#include "frmview.hxx"
namespace binfilter {

using namespace ::rtl;
using namespace ::utl;
using namespace ::com::sun::star::uno;

#define B2U(_def_aStr) (OUString::createFromAscii(_def_aStr))


// -----------------
// - SdOptionsItem -
// -----------------

/*N*/ SdOptionsItem::SdOptionsItem( const SdOptionsGeneric& rParent, const OUString rSubTree ) :
/*N*/   ConfigItem  ( rSubTree ),
/*N*/   mrParent    ( rParent )
/*N*/ {
/*N*/ }

// -----------------------------------------------------------------------------

/*N*/ SdOptionsItem::~SdOptionsItem()
/*N*/ {
/*N*/ }

// -----------------------------------------------------------------------------

//STRIP001 void SdOptionsItem::Commit()
//STRIP001 {
//STRIP001  if( IsModified() )
//STRIP001      mrParent.Commit( *this );
//STRIP001 };

// -----------------------------------------------------------------------------

/*N*/ Sequence< Any >   SdOptionsItem::GetProperties( const Sequence< OUString >& rNames )
/*N*/ {
/*N*/   return ConfigItem::GetProperties( rNames );
/*N*/ }

// -----------------------------------------------------------------------------

//STRIP001 sal_Bool SdOptionsItem::PutProperties( const Sequence< OUString >& rNames, const Sequence< Any>& rValues )
//STRIP001 {
//STRIP001  return ConfigItem::PutProperties( rNames, rValues );
//STRIP001 }

// -----------------------------------------------------------------------------

/*N*/ void SdOptionsItem::SetModified()
/*N*/ {
/*N*/   ConfigItem::SetModified();
/*N*/ }

// --------------------
// - SdOptionsGeneric -
// --------------------

/*N*/ SdOptionsGeneric::SdOptionsGeneric( USHORT nConfigId, const OUString& rSubTree ) :
/*N*/   maSubTree   ( rSubTree ),
/*N*/   mpCfgItem   ( NULL ),
/*N*/   mnConfigId  ( nConfigId ),
/*N*/   mbInit      ( rSubTree.getLength() == 0 )
/*N*/ {
/*N*/ }

// -----------------------------------------------------------------------------

/*N*/ void SdOptionsGeneric::Init() const
/*N*/ {
/*N*/   if( !mbInit )
/*N*/   {
/*N*/       SdOptionsGeneric* pThis = (SdOptionsGeneric*) this;
/*N*/
/*N*/       if( !mpCfgItem )
/*N*/           pThis->mpCfgItem = new SdOptionsItem( *this, maSubTree );
/*N*/
/*N*/       const Sequence< OUString >  aNames( GetPropertyNames() );
/*N*/       const Sequence< Any >       aValues = mpCfgItem->GetProperties( aNames );
/*N*/
/*N*/       if( aNames.getLength() && ( aValues.getLength() == aNames.getLength() ) )
/*N*/       {
/*N*/           const Any* pValues = aValues.getConstArray();
/*N*/
/*N*/           pThis->EnableModify( FALSE );
/*N*/           pThis->mbInit = pThis->ReadData( pValues );
/*N*/           pThis->EnableModify( TRUE );
/*N*/       }
/*N*/       else
/*?*/           pThis->mbInit = TRUE;
/*N*/   }
/*N*/ }

// -----------------------------------------------------------------------------

/*N*/ SdOptionsGeneric::~SdOptionsGeneric()
/*N*/ {
/*N*/   if( mpCfgItem )
/*N*/       delete mpCfgItem;
/*N*/ }

// -----------------------------------------------------------------------------

//STRIP001 void SdOptionsGeneric::Commit( SdOptionsItem& rCfgItem ) const
//STRIP001 {
//STRIP001  const Sequence< OUString >  aNames( GetPropertyNames() );
//STRIP001  Sequence< Any >             aValues( aNames.getLength() );
//STRIP001
//STRIP001  if( aNames.getLength() && ( aValues.getLength() == aNames.getLength() ) )
//STRIP001  {
//STRIP001      if( ( (SdOptionsGeneric*) this )->WriteData( aValues.getArray() ) )
//STRIP001          rCfgItem.PutProperties( aNames, aValues );
//STRIP001      else
//STRIP001      {
//STRIP001          DBG_ERROR( "PutProperties failed" );
//STRIP001      }
//STRIP001  }
//STRIP001 }

// -----------------------------------------------------------------------------

/*N*/ Sequence< OUString > SdOptionsGeneric::GetPropertyNames() const
/*N*/ {
/*N*/   ULONG           nCount;
/*N*/   const char**    ppPropNames;
/*N*/
/*N*/   GetPropNameArray( ppPropNames, nCount );
/*N*/
/*N*/   Sequence< OUString > aNames( nCount );
/*N*/   OUString*            pNames = aNames.getArray();
/*N*/
/*N*/   for( ULONG i = 0; i < nCount; i++ )
/*N*/       pNames[ i ] = OUString::createFromAscii( ppPropNames[ i ] );
/*N*/
/*N*/   return aNames;
/*N*/ }

// -----------------------------------------------------------------------------

//STRIP001 void SdOptionsGeneric::Store()
//STRIP001 {
//STRIP001  if( mpCfgItem )
//STRIP001      mpCfgItem->Commit();
//STRIP001 }

// -----------------------------------------------------------------------------

/*N*/ bool SdOptionsGeneric::isMetricSystem()
/*N*/ {
/*N*/   SvtSysLocale aSysLocale;
/*N*/     MeasurementSystem eSys = aSysLocale.GetLocaleDataPtr()->getMeasurementSystemEnum();
/*N*/
/*N*/   return ( eSys == MEASURE_METRIC );
/*N*/ }

/*************************************************************************
|*
|* SdOptionsLayout
|*
\************************************************************************/

/*N*/ SdOptionsLayout::SdOptionsLayout(  USHORT nConfigId, BOOL bUseConfig ) :
/*N*/   SdOptionsGeneric( nConfigId, bUseConfig ?
/*N*/                     ( ( SDCFG_DRAW == nConfigId ) ?
/*N*/                       B2U( "Office.Draw/Layout" ) :
/*N*/                       B2U( "Office.Impress/Layout" ) ) :
/*N*/                     OUString() )
/*N*/ {
/*N*/   EnableModify( FALSE );
/*N*/   SetDefaults();
/*N*/   EnableModify( TRUE );
/*N*/ }

// -----------------------------------------------------------------------------

/*N*/ void SdOptionsLayout::SetDefaults()
/*N*/ {
/*N*/   SetRulerVisible( TRUE );
/*N*/   SetHelplines( TRUE );
/*N*/   SetHandlesBezier( FALSE );
/*N*/   SetMoveOutline( TRUE );
/*N*/   SetDragStripes( FALSE );
/*N*/   if ( isMetricSystem() )
/*N*/       SetMetric( FUNIT_CM );              // default for countries with metric system
/*N*/   else
/*N*/       SetMetric( FUNIT_INCH );            // default for others
/*N*/   SetDefTab( 1250 );
/*N*/ }

// -----------------------------------------------------------------------------

//STRIP001 BOOL SdOptionsLayout::operator==( const SdOptionsLayout& rOpt ) const
//STRIP001 {
//STRIP001  return( IsRulerVisible() == rOpt.IsRulerVisible() &&
//STRIP001          IsMoveOutline() == rOpt.IsMoveOutline() &&
//STRIP001          IsDragStripes() == rOpt.IsDragStripes() &&
//STRIP001          IsHandlesBezier() == rOpt.IsHandlesBezier() &&
//STRIP001          IsHelplines() == rOpt.IsHelplines() &&
//STRIP001          GetMetric() == rOpt.GetMetric() &&
//STRIP001          GetDefTab() == rOpt.GetDefTab() );
//STRIP001 }

// -----------------------------------------------------------------------------

/*N*/ void SdOptionsLayout::GetPropNameArray( const char**& ppNames, ULONG& rCount ) const
/*N*/ {
/*N*/   static const char* aPropNamesMetric[] =
/*N*/   {
/*N*/       "Display/Ruler",
/*N*/       "Display/Bezier",
/*N*/       "Display/Contour",
/*N*/       "Display/Guide",
/*N*/       "Display/Helpline",
/*N*/       "Other/MeasureUnit/Metric",
/*N*/       "Other/TabStop/Metric"
/*N*/   };
/*N*/
/*N*/   static const char* aPropNamesNonMetric[] =
/*N*/   {
/*N*/       "Display/Ruler",
/*N*/       "Display/Bezier",
/*N*/       "Display/Contour",
/*N*/       "Display/Guide",
/*N*/       "Display/Helpline",
/*N*/       "Other/MeasureUnit/NonMetric",
/*N*/       "Other/TabStop/NonMetric"
/*N*/   };
/*N*/
/*N*/   rCount = 7;
/*N*/
/*N*/   if( isMetricSystem() )
/*N*/       ppNames = aPropNamesMetric;
/*N*/   else
/*N*/       ppNames = aPropNamesNonMetric;
/*N*/ }

// -----------------------------------------------------------------------------

/*N*/ BOOL SdOptionsLayout::ReadData( const Any* pValues )
/*N*/ {
/*N*/   if( pValues[0].hasValue() ) SetRulerVisible( *(sal_Bool*) pValues[ 0 ].getValue() );
/*N*/   if( pValues[1].hasValue() ) SetHandlesBezier( *(sal_Bool*) pValues[ 1 ].getValue() );
/*N*/   if( pValues[2].hasValue() ) SetMoveOutline( *(sal_Bool*) pValues[ 2 ].getValue() );
/*N*/   if( pValues[3].hasValue() ) SetDragStripes( *(sal_Bool*) pValues[ 3 ].getValue() );
/*N*/   if( pValues[4].hasValue() ) SetHelplines( *(sal_Bool*) pValues[ 4 ].getValue() );
/*N*/   if( pValues[5].hasValue() ) SetMetric( (UINT16) *(sal_Int32*) pValues[ 5 ].getValue() );
/*N*/   if( pValues[6].hasValue() ) SetDefTab( (UINT16) *(sal_Int32*) pValues[ 6 ].getValue() );
/*N*/
/*N*/   return TRUE;
/*N*/ }

// -----------------------------------------------------------------------------

/*N*/ BOOL SdOptionsLayout::WriteData( Any* pValues ) const
/*N*/ {
/*N*/   pValues[ 0 ] <<= IsRulerVisible();
/*N*/   pValues[ 1 ] <<= IsHandlesBezier();
/*N*/   pValues[ 2 ] <<= IsMoveOutline();
/*N*/   pValues[ 3 ] <<= IsDragStripes();
/*N*/   pValues[ 4 ] <<= IsHelplines();
/*N*/   pValues[ 5 ] <<= (sal_Int32) GetMetric();
/*N*/   pValues[ 6 ] <<= (sal_Int32) GetDefTab();
/*N*/
/*N*/   return TRUE;
/*N*/ }

/*************************************************************************
|*
|* SdOptionsLayoutItem
|*
\************************************************************************/

//STRIP001 SdOptionsLayoutItem::SdOptionsLayoutItem( USHORT nWhich ) :
//STRIP001  SfxPoolItem     ( nWhich ),
//STRIP001  SdOptionsLayout ( 0, FALSE )
//STRIP001 {
//STRIP001 }

// ----------------------------------------------------------------------

//STRIP001 SdOptionsLayoutItem::SdOptionsLayoutItem( USHORT nWhich, SdOptions* pOpts, FrameView* pView ) :
//STRIP001  SfxPoolItem     ( nWhich ),
//STRIP001  SdOptionsLayout ( 0, FALSE )
//STRIP001 {
//STRIP001  SetMetric( pOpts->GetMetric() );
//STRIP001  SetDefTab( pOpts->GetDefTab() );
//STRIP001
//STRIP001  if( pView )
//STRIP001  {
//STRIP001      SetRulerVisible( pView->HasRuler() );
//STRIP001      SetMoveOutline( !pView->IsNoDragXorPolys() );
//STRIP001      SetDragStripes( pView->IsDragStripes() );
//STRIP001      SetHandlesBezier( pView->IsPlusHandlesAlwaysVisible() );
//STRIP001      SetHelplines( pView->IsHlplVisible() );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      SetRulerVisible( pOpts->IsRulerVisible() );
//STRIP001      SetMoveOutline( pOpts->IsMoveOutline() );
//STRIP001      SetDragStripes( pOpts->IsDragStripes() );
//STRIP001      SetHandlesBezier( pOpts->IsHandlesBezier() );
//STRIP001      SetHelplines( pOpts->IsHelplines() );
//STRIP001  }
//STRIP001 }

// ----------------------------------------------------------------------

//STRIP001 SfxPoolItem* SdOptionsLayoutItem::Clone( SfxItemPool* ) const
//STRIP001 {
//STRIP001  return new SdOptionsLayoutItem( *this );
//STRIP001 }


// ----------------------------------------------------------------------

//STRIP001 int SdOptionsLayoutItem::operator==( const SfxPoolItem& rAttr ) const
//STRIP001 {
//STRIP001  DBG_ASSERT( SfxPoolItem::operator==( rAttr ), "unterschiedliche Typen" );
//STRIP001  return( (SdOptionsLayout&) *this == (const SdOptionsLayout&)(const SdOptionsLayoutItem&) rAttr );
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 void SdOptionsLayoutItem::SetOptions( SdOptions* pOpts ) const
//STRIP001 {
//STRIP001  pOpts->SetRulerVisible( IsRulerVisible() );
//STRIP001  pOpts->SetMoveOutline( IsMoveOutline() );
//STRIP001  pOpts->SetDragStripes( IsDragStripes() );
//STRIP001  pOpts->SetHandlesBezier( IsHandlesBezier() );
//STRIP001  pOpts->SetHelplines( IsHelplines() );
//STRIP001  pOpts->SetMetric( GetMetric() );
//STRIP001  pOpts->SetDefTab( GetDefTab() );
//STRIP001 }

/*************************************************************************
|*
|* SdOptionsContents
|*
\************************************************************************/

/*N*/ SdOptionsContents::SdOptionsContents( USHORT nConfigId, BOOL bUseConfig ) :
/*N*/   SdOptionsGeneric( nConfigId, bUseConfig ?
/*N*/                     ( ( SDCFG_DRAW == nConfigId ) ?
/*N*/                       B2U( "Office.Draw/Content" ) :
/*N*/                       B2U( "Office.Impress/Content" ) ) :
/*N*/                     OUString() )
/*N*/ {
/*N*/   EnableModify( FALSE );
/*N*/   SetDefaults();
/*N*/   EnableModify( TRUE );
/*N*/ }

// -----------------------------------------------------------------------------

/*N*/ void SdOptionsContents::SetDefaults()
/*N*/ {
/*N*/   SetExternGraphic( FALSE );
/*N*/   SetOutlineMode( FALSE );
/*N*/   SetHairlineMode( FALSE);
/*N*/   SetNoText( FALSE );
/*N*/ }

// -----------------------------------------------------------------------------

//STRIP001 BOOL SdOptionsContents::operator==( const SdOptionsContents& rOpt ) const
//STRIP001 {
//STRIP001  return( IsExternGraphic() == rOpt.IsExternGraphic() &&
//STRIP001          IsOutlineMode() == rOpt.IsOutlineMode() &&
//STRIP001          IsHairlineMode() == rOpt.IsHairlineMode() &&
//STRIP001          IsNoText() == rOpt.IsNoText() );
//STRIP001 }

// -----------------------------------------------------------------------------

/*N*/ void SdOptionsContents::GetPropNameArray( const char**& ppNames, ULONG& rCount ) const
/*N*/ {
/*N*/   static const char* aPropNames[] =
/*N*/   {
/*N*/       "Display/PicturePlaceholder",
/*N*/       "Display/ContourMode",
/*N*/       "Display/LineContour",
/*N*/       "Display/TextPlaceholder"
/*N*/   };
/*N*/
/*N*/   rCount = 4;
/*N*/   ppNames = aPropNames;
/*N*/ }

// -----------------------------------------------------------------------------

/*N*/ BOOL SdOptionsContents::ReadData( const Any* pValues )
/*N*/ {
/*N*/   if( pValues[0].hasValue() ) SetExternGraphic( *(sal_Bool*) pValues[ 0 ].getValue() );
/*N*/   if( pValues[1].hasValue() ) SetOutlineMode( *(sal_Bool*)pValues[ 1 ].getValue() );
/*N*/   if( pValues[2].hasValue() ) SetHairlineMode( *(sal_Bool*) pValues[ 2 ].getValue() );
/*N*/   if( pValues[3].hasValue() ) SetNoText( *(sal_Bool*) pValues[ 3 ].getValue() );
/*N*/
/*N*/   return TRUE;
/*N*/ }

// -----------------------------------------------------------------------------

/*N*/ BOOL SdOptionsContents::WriteData( Any* pValues ) const
/*N*/ {
/*N*/   pValues[ 0 ] <<= IsExternGraphic();
/*N*/   pValues[ 1 ] <<= IsOutlineMode();
/*N*/   pValues[ 2 ] <<= IsHairlineMode();
/*N*/   pValues[ 3 ] <<= IsNoText();
/*N*/
/*N*/   return TRUE;
/*N*/ }

/*************************************************************************
|*
|* SdOptionsContentsItem
|*
\************************************************************************/

//STRIP001 SdOptionsContentsItem::SdOptionsContentsItem( USHORT nWhich ) :
//STRIP001  SfxPoolItem         ( nWhich ),
//STRIP001  SdOptionsContents   ( 0, FALSE )
//STRIP001 {
//STRIP001 }

// ----------------------------------------------------------------------

//STRIP001 SdOptionsContentsItem::SdOptionsContentsItem( USHORT nWhich, SdOptions* pOpts, FrameView* pView ) :
//STRIP001  SfxPoolItem         ( nWhich ),
//STRIP001  SdOptionsContents   ( 0, FALSE )
//STRIP001 {
//STRIP001  if( pView )
//STRIP001  {
//STRIP001      SetExternGraphic( pView->IsGrafDraft() );
//STRIP001      SetOutlineMode( pView->IsFillDraft() );
//STRIP001      SetHairlineMode( pView->IsLineDraft() );
//STRIP001      SetNoText( pView->IsTextDraft() );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      SetExternGraphic( pOpts->IsExternGraphic() );
//STRIP001      SetOutlineMode( pOpts->IsOutlineMode() );
//STRIP001      SetHairlineMode( pOpts->IsHairlineMode() );
//STRIP001      SetNoText( pOpts->IsNoText() );
//STRIP001  }
//STRIP001 }

// ----------------------------------------------------------------------

//STRIP001 SfxPoolItem* SdOptionsContentsItem::Clone( SfxItemPool* ) const
//STRIP001 {
//STRIP001  return new SdOptionsContentsItem( *this );
//STRIP001 }

// ----------------------------------------------------------------------

//STRIP001 int SdOptionsContentsItem::operator==( const SfxPoolItem& rAttr ) const
//STRIP001 {
//STRIP001  DBG_ASSERT( SfxPoolItem::operator==(rAttr), "unterschiedliche Typen" );
//STRIP001  return( (SdOptionsContents&) *this == (const SdOptionsContents&)(const SdOptionsContentsItem&) rAttr );
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 void SdOptionsContentsItem::SetOptions( SdOptions* pOpts ) const
//STRIP001 {
//STRIP001  pOpts->SetExternGraphic( IsExternGraphic() );
//STRIP001  pOpts->SetOutlineMode( IsOutlineMode() );
//STRIP001  pOpts->SetHairlineMode(IsHairlineMode() );
//STRIP001  pOpts->SetNoText( IsNoText() );
//STRIP001 }

/*************************************************************************
|*
|* SdOptionsMisc
|*
\************************************************************************/

/*N*/ SdOptionsMisc::SdOptionsMisc( USHORT nConfigId, BOOL bUseConfig ) :
/*N*/   SdOptionsGeneric( nConfigId, bUseConfig ?
/*N*/                     ( ( SDCFG_DRAW == nConfigId ) ?
/*N*/                       B2U( "Office.Draw/Misc" ) :
/*N*/                       B2U( "Office.Impress/Misc" ) ) :
/*N*/                     OUString() )
/*N*/ {
/*N*/   EnableModify( FALSE );
/*N*/   SetDefaults();
/*N*/   EnableModify( TRUE );
/*N*/ }

// -----------------------------------------------------------------------------

/*N*/ void SdOptionsMisc::SetDefaults()
/*N*/ {
/*N*/   SetStartWithTemplate( TRUE );
/*N*/   SetMarkedHitMovesAlways( TRUE );
/*N*/   SetMoveOnlyDragging( FALSE );
/*N*/   SetCrookNoContortion( FALSE );
/*N*/   SetQuickEdit( GetConfigId() != SDCFG_DRAW );
/*N*/   SetMasterPagePaintCaching( TRUE );
/*N*/   SetDragWithCopy( FALSE );
/*N*/   SetPickThrough( TRUE );
/*N*/   SetBigHandles( FALSE );
/*N*/   SetDoubleClickTextEdit( TRUE );
/*N*/   SetClickChangeRotation( FALSE );
/*N*/   SetStartWithActualPage( FALSE );
/*N*/   SetSummationOfParagraphs( FALSE );
/*N*/   SetPreviewQuality( DRAWMODE_DEFAULT );
/*N*/   SetSolidDragging( FALSE );
/*N*/   SetSolidMarkHdl( TRUE );
/*N*/   // #90356#
/*N*/   SetShowUndoDeleteWarning( TRUE );
    // The default for 6.1-and-above documents is to use printer-independent
    // formatting.
/*N*/   SetPrinterIndependentLayout (1);
/*N*/   // #97016#
/*N*/   SetDefaultObjectSizeWidth(8000);
/*N*/   SetDefaultObjectSizeHeight(5000);
/*N*/ }

// -----------------------------------------------------------------------------

//STRIP001 BOOL SdOptionsMisc::operator==( const SdOptionsMisc& rOpt ) const
//STRIP001 {
//STRIP001  return( IsStartWithTemplate() == rOpt.IsStartWithTemplate() &&
//STRIP001          IsMarkedHitMovesAlways() == rOpt.IsMarkedHitMovesAlways() &&
//STRIP001          IsMoveOnlyDragging() == rOpt.IsMoveOnlyDragging() &&
//STRIP001          IsCrookNoContortion() == rOpt.IsCrookNoContortion() &&
//STRIP001          IsQuickEdit() == rOpt.IsQuickEdit() &&
//STRIP001          IsMasterPagePaintCaching() == rOpt.IsMasterPagePaintCaching() &&
//STRIP001          IsDragWithCopy() == rOpt.IsDragWithCopy() &&
//STRIP001          IsPickThrough() == rOpt.IsPickThrough() &&
//STRIP001          IsBigHandles() == rOpt.IsBigHandles() &&
//STRIP001          IsDoubleClickTextEdit() == rOpt.IsDoubleClickTextEdit() &&
//STRIP001          IsClickChangeRotation() == rOpt.IsClickChangeRotation() &&
//STRIP001          IsStartWithActualPage() == rOpt.IsStartWithActualPage() &&
//STRIP001          IsSummationOfParagraphs() == rOpt.IsSummationOfParagraphs() &&
//STRIP001          GetPreviewQuality() == rOpt.GetPreviewQuality() &&
//STRIP001          IsSolidDragging() == rOpt.IsSolidDragging() &&
//STRIP001          IsSolidMarkHdl() == rOpt.IsSolidMarkHdl() &&
//STRIP001          // #90356#
//STRIP001          IsShowUndoDeleteWarning() == rOpt.IsShowUndoDeleteWarning() &&
//STRIP001          GetPrinterIndependentLayout() == rOpt.GetPrinterIndependentLayout() &&
//STRIP001          // #97016#
//STRIP001          GetDefaultObjectSizeWidth() == rOpt.GetDefaultObjectSizeWidth() &&
//STRIP001          GetDefaultObjectSizeHeight() == rOpt.GetDefaultObjectSizeHeight()
//STRIP001      );
//STRIP001 }

// -----------------------------------------------------------------------------

/*N*/ void SdOptionsMisc::GetPropNameArray( const char**& ppNames, ULONG& rCount ) const
/*N*/ {
/*N*/   static const char* aPropNames[] =
/*N*/   {
/*N*/       "ObjectMoveable",
/*N*/       "NoDistort",
/*N*/       "TextObject/QuickEditing",
/*N*/       "BackgroundCache",
/*N*/       "CopyWhileMoving",
/*N*/       "TextObject/Selectable",
/*N*/       "BigHandles",
/*N*/       "DclickTextedit",
/*N*/       "RotateClick",
/*N*/       "Preview",
/*N*/       "CreateWithAttributes",
/*N*/       "SimpleHandles",
/*N*/       // #97016#
/*N*/       "DefaultObjectSize/Width",
/*N*/       "DefaultObjectSize/Height",
/*N*/
/*N*/         "Compatibility/PrinterIndependentLayout",
/*N*/
/*N*/       // just for impress
/*N*/       "NewDoc/AutoPilot",
/*N*/       "Start/CurrentPage",
/*N*/       "Compatibility/AddBetween",
/*N*/       // #90356#
/*N*/       "ShowUndoDeleteWarning"
/*N*/   };
/*N*/
/*N*/   // #90356# rCount = ( ( GetConfigId() == SDCFG_IMPRESS ) ? 15 : 12 );
/*N*/   // #97016# rCount = ( ( GetConfigId() == SDCFG_IMPRESS ) ? 16 : 12 );
/*N*/   rCount = ( ( GetConfigId() == SDCFG_IMPRESS ) ? 19 : 15 );
/*N*/   ppNames = aPropNames;
/*N*/ }

// -----------------------------------------------------------------------------

/*N*/ BOOL SdOptionsMisc::ReadData( const Any* pValues )
/*N*/ {
/*N*/   if( pValues[0].hasValue() ) SetMarkedHitMovesAlways( *(sal_Bool*) pValues[ 0 ].getValue() );
/*N*/   if( pValues[1].hasValue() ) SetCrookNoContortion( *(sal_Bool*) pValues[ 1 ].getValue() );
/*N*/   if( pValues[2].hasValue() ) SetQuickEdit( *(sal_Bool*)pValues[ 2 ].getValue() );
/*N*/   if( pValues[3].hasValue() ) SetMasterPagePaintCaching( *(sal_Bool*) pValues[ 3 ].getValue() );
/*N*/   if( pValues[4].hasValue() ) SetDragWithCopy( *(sal_Bool*) pValues[ 4 ].getValue() );
/*N*/   if( pValues[5].hasValue() ) SetPickThrough( *(sal_Bool*) pValues[ 5 ].getValue() );
/*N*/   if( pValues[6].hasValue() ) SetBigHandles( *(sal_Bool*) pValues[ 6 ].getValue() );
/*N*/   if( pValues[7].hasValue() ) SetDoubleClickTextEdit( *(sal_Bool*) pValues[ 7 ].getValue() );
/*N*/   if( pValues[8].hasValue() ) SetClickChangeRotation( *(sal_Bool*) pValues[ 8 ].getValue() );
/*N*/   if( pValues[9].hasValue() ) SetPreviewQuality( FRound( *(double*) pValues[ 9 ].getValue() ) );
/*N*/   if( pValues[10].hasValue() ) SetSolidDragging( *(sal_Bool*) pValues[ 10 ].getValue() );
/*N*/   if( pValues[11].hasValue() ) SetSolidMarkHdl( *(sal_Bool*) pValues[ 11 ].getValue() );
/*N*/   // #97016#
/*N*/   if( pValues[12].hasValue() ) SetDefaultObjectSizeWidth( *(sal_uInt32*) pValues[ 12 ].getValue() );
/*N*/   if( pValues[13].hasValue() ) SetDefaultObjectSizeHeight( *(sal_uInt32*) pValues[ 13 ].getValue() );
/*N*/   if( pValues[14].hasValue() ) SetPrinterIndependentLayout( *(sal_uInt16*) pValues[ 14 ].getValue() );
/*N*/
/*N*/   // just for Impress
/*N*/   if( GetConfigId() == SDCFG_IMPRESS )
/*N*/   {
/*N*/       if( pValues[15].hasValue() )
/*N*/           SetStartWithTemplate( *(sal_Bool*) pValues[ 15 ].getValue() );
/*N*/       if( pValues[16].hasValue() )
/*N*/           SetStartWithActualPage( *(sal_Bool*) pValues[ 16 ].getValue() );
/*N*/       if( pValues[17].hasValue() )
/*N*/           SetSummationOfParagraphs( *(sal_Bool*) pValues[ 17 ].getValue() );
/*N*/       // #90356#
/*N*/       if( pValues[18].hasValue() )
/*N*/           SetShowUndoDeleteWarning( *(sal_Bool*) pValues[ 18 ].getValue() );
/*N*/   }
/*N*/
/*N*/   return TRUE;
/*N*/ }

// -----------------------------------------------------------------------------

/*N*/ BOOL SdOptionsMisc::WriteData( Any* pValues ) const
/*N*/ {
/*N*/   pValues[ 0 ] <<= IsMarkedHitMovesAlways();
/*N*/   pValues[ 1 ] <<= IsCrookNoContortion();
/*N*/   pValues[ 2 ] <<= IsQuickEdit();
/*N*/   pValues[ 3 ] <<= IsMasterPagePaintCaching();
/*N*/   pValues[ 4 ] <<= IsDragWithCopy();
/*N*/   pValues[ 5 ] <<= IsPickThrough();
/*N*/   pValues[ 6 ] <<= IsBigHandles();
/*N*/   pValues[ 7 ] <<= IsDoubleClickTextEdit();
/*N*/   pValues[ 8 ] <<= IsClickChangeRotation();
/*N*/   pValues[ 9 ] <<= (double) GetPreviewQuality();
/*N*/   pValues[ 10 ] <<= IsSolidDragging();
/*N*/   pValues[ 11 ] <<= IsSolidMarkHdl();
/*N*/   // #97016#
/*N*/   pValues[ 12 ] <<= GetDefaultObjectSizeWidth();
/*N*/   pValues[ 13 ] <<= GetDefaultObjectSizeHeight();
/*N*/   pValues[ 14 ] <<= GetPrinterIndependentLayout();
/*N*/
/*N*/   // just for Impress
/*N*/   if( GetConfigId() == SDCFG_IMPRESS )
/*N*/   {
/*N*/       pValues[ 15 ] <<= IsStartWithTemplate();
/*N*/       pValues[ 16 ] <<= IsStartWithActualPage();
/*N*/       pValues[ 17 ] <<= IsSummationOfParagraphs();
/*N*/       // #90356#
/*N*/       pValues[ 18 ] <<= IsShowUndoDeleteWarning();
/*N*/   }
/*N*/
/*N*/   return TRUE;
/*N*/ }

/*************************************************************************
|*
|* SdOptionsMiscItem
|*
\************************************************************************/

//STRIP001 SdOptionsMiscItem::SdOptionsMiscItem( USHORT nWhich ) :
//STRIP001  SfxPoolItem     ( nWhich ),
//STRIP001  SdOptionsMisc   ( 0, FALSE )
//STRIP001 {
//STRIP001 }

// ----------------------------------------------------------------------

//STRIP001 SdOptionsMiscItem::SdOptionsMiscItem( USHORT nWhich, SdOptions* pOpts, FrameView* pView ) :
//STRIP001  SfxPoolItem     ( nWhich ),
//STRIP001  SdOptionsMisc   ( 0, FALSE )
//STRIP001 {
//STRIP001  SetStartWithTemplate( pOpts->IsStartWithTemplate() );
//STRIP001  SetStartWithActualPage( pOpts->IsStartWithActualPage() );
//STRIP001  SetSummationOfParagraphs( pOpts->IsSummationOfParagraphs() );
//STRIP001  // #90356#
//STRIP001  SetShowUndoDeleteWarning( pOpts->IsShowUndoDeleteWarning() );
//STRIP001  SetPrinterIndependentLayout( pOpts->GetPrinterIndependentLayout() );
//STRIP001  // #97016#
//STRIP001  SetDefaultObjectSizeWidth( pOpts->GetDefaultObjectSizeWidth() );
//STRIP001  SetDefaultObjectSizeHeight( pOpts->GetDefaultObjectSizeHeight() );
//STRIP001
//STRIP001  if( pView )
//STRIP001  {
//STRIP001      SetMarkedHitMovesAlways( pView->IsMarkedHitMovesAlways() );
//STRIP001      SetMoveOnlyDragging( pView->IsMoveOnlyDragging() );
//STRIP001      SetCrookNoContortion( pView->IsCrookNoContortion() );
//STRIP001      SetQuickEdit( pView->IsQuickEdit() );
//STRIP001      SetMasterPagePaintCaching(pView->IsMasterPagePaintCaching() );
//STRIP001      SetDragWithCopy( pView->IsDragWithCopy() );
//STRIP001      SetPickThrough( pView->GetModel()->IsPickThroughTransparentTextFrames() );
//STRIP001      SetBigHandles( pView->IsBigHandles() );
//STRIP001      SetDoubleClickTextEdit( pView->IsDoubleClickTextEdit() );
//STRIP001      SetClickChangeRotation( pView->IsClickChangeRotation() );
//STRIP001      SetPreviewQuality( pView->GetPreviewDrawMode() );
//STRIP001      SetSolidDragging( pView->IsSolidDragging() );
//STRIP001      SetSolidMarkHdl( pView->IsSolidMarkHdl() );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      SetMarkedHitMovesAlways( pOpts->IsMarkedHitMovesAlways() );
//STRIP001      SetMoveOnlyDragging( pOpts->IsMoveOnlyDragging() );
//STRIP001      SetCrookNoContortion( pOpts->IsCrookNoContortion() );
//STRIP001      SetQuickEdit( pOpts->IsQuickEdit() );
//STRIP001      SetMasterPagePaintCaching( pOpts->IsMasterPagePaintCaching() );
//STRIP001      SetDragWithCopy( pOpts->IsDragWithCopy() );
//STRIP001      SetPickThrough( pOpts->IsPickThrough() );
//STRIP001      SetBigHandles( pOpts->IsBigHandles() );
//STRIP001      SetDoubleClickTextEdit( pOpts->IsDoubleClickTextEdit() );
//STRIP001      SetClickChangeRotation( pOpts->IsClickChangeRotation() );
//STRIP001      SetPreviewQuality( pOpts->GetPreviewQuality() );
//STRIP001      SetSolidDragging( pOpts->IsSolidDragging() );
//STRIP001      SetSolidMarkHdl( pOpts->IsSolidMarkHdl() );
//STRIP001  }
//STRIP001 }

// ----------------------------------------------------------------------

//STRIP001 SfxPoolItem* SdOptionsMiscItem::Clone( SfxItemPool* ) const
//STRIP001 {
//STRIP001  return new SdOptionsMiscItem( *this );
//STRIP001 }


// ----------------------------------------------------------------------

//STRIP001 int SdOptionsMiscItem::operator==( const SfxPoolItem& rAttr ) const
//STRIP001 {
//STRIP001  DBG_ASSERT( SfxPoolItem::operator==(rAttr), "unterschiedliche Typen" );
//STRIP001  return( (SdOptionsMisc&) *this == (const SdOptionsMisc&)(const SdOptionsMiscItem&) rAttr );
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 void SdOptionsMiscItem::SetOptions( SdOptions* pOpts ) const
//STRIP001 {
//STRIP001  pOpts->SetStartWithTemplate( IsStartWithTemplate() );
//STRIP001  pOpts->SetMarkedHitMovesAlways( IsMarkedHitMovesAlways() );
//STRIP001  pOpts->SetMoveOnlyDragging( IsMoveOnlyDragging() );
//STRIP001  pOpts->SetCrookNoContortion( IsCrookNoContortion() );
//STRIP001  pOpts->SetQuickEdit( IsQuickEdit() );
//STRIP001  pOpts->SetMasterPagePaintCaching( IsMasterPagePaintCaching() );
//STRIP001  pOpts->SetDragWithCopy( IsDragWithCopy() );
//STRIP001  pOpts->SetPickThrough( IsPickThrough() );
//STRIP001  pOpts->SetBigHandles( IsBigHandles() );
//STRIP001  pOpts->SetDoubleClickTextEdit( IsDoubleClickTextEdit() );
//STRIP001  pOpts->SetClickChangeRotation( IsClickChangeRotation() );
//STRIP001  pOpts->SetStartWithActualPage( IsStartWithActualPage() );
//STRIP001  pOpts->SetSummationOfParagraphs( IsSummationOfParagraphs() );
//STRIP001  pOpts->SetPreviewQuality( GetPreviewQuality() );
//STRIP001  pOpts->SetSolidDragging( IsSolidDragging() );
//STRIP001  pOpts->SetSolidMarkHdl( IsSolidMarkHdl() );
//STRIP001  // #90356#
//STRIP001  pOpts->SetShowUndoDeleteWarning( IsShowUndoDeleteWarning() );
//STRIP001  pOpts->SetPrinterIndependentLayout( GetPrinterIndependentLayout() );
//STRIP001  // #97016#
//STRIP001  pOpts->SetDefaultObjectSizeWidth( GetDefaultObjectSizeWidth() );
//STRIP001  pOpts->SetDefaultObjectSizeHeight( GetDefaultObjectSizeHeight() );
//STRIP001 }

/*************************************************************************
|*
|* SdOptionsSnap
|*
\************************************************************************/

/*N*/ SdOptionsSnap::SdOptionsSnap( USHORT nConfigId, BOOL bUseConfig ) :
/*N*/   SdOptionsGeneric( nConfigId, bUseConfig ?
/*N*/                     ( ( SDCFG_DRAW == nConfigId ) ?
/*N*/                       B2U( "Office.Draw/Snap" ) :
/*N*/                       B2U( "Office.Impress/Snap" ) ) :
/*N*/                     OUString() )
/*N*/ {
/*N*/   EnableModify( FALSE );
/*N*/   SetDefaults();
/*N*/   EnableModify( TRUE );
/*N*/ }

// -----------------------------------------------------------------------------

/*N*/ void SdOptionsSnap::SetDefaults()
/*N*/ {
/*N*/   SetSnapHelplines( TRUE );
/*N*/   SetSnapBorder( TRUE );
/*N*/   SetSnapFrame( FALSE );
/*N*/   SetSnapPoints( FALSE );
/*N*/   SetOrtho( FALSE );
/*N*/   SetBigOrtho( TRUE );
/*N*/   SetRotate( FALSE );
/*N*/   SetSnapArea( 5 );
/*N*/   SetAngle( 1500 );
/*N*/   SetEliminatePolyPointLimitAngle( 1500 );
/*N*/ }

// -----------------------------------------------------------------------------

//STRIP001 BOOL SdOptionsSnap::operator==( const SdOptionsSnap& rOpt ) const
//STRIP001 {
//STRIP001  return( IsSnapHelplines() == rOpt.IsSnapHelplines() &&
//STRIP001          IsSnapBorder() == rOpt.IsSnapBorder() &&
//STRIP001          IsSnapFrame() == rOpt.IsSnapFrame() &&
//STRIP001          IsSnapPoints() == rOpt.IsSnapPoints() &&
//STRIP001          IsOrtho() == rOpt.IsOrtho() &&
//STRIP001          IsBigOrtho() == rOpt.IsBigOrtho() &&
//STRIP001          IsRotate() == rOpt.IsRotate() &&
//STRIP001          GetSnapArea() == rOpt.GetSnapArea() &&
//STRIP001          GetAngle() == rOpt.GetAngle() &&
//STRIP001          GetEliminatePolyPointLimitAngle() == rOpt.GetEliminatePolyPointLimitAngle() );
//STRIP001 }

// -----------------------------------------------------------------------------

/*N*/ void SdOptionsSnap::GetPropNameArray( const char**& ppNames, ULONG& rCount ) const
/*N*/ {
/*N*/   static const char* aPropNames[] =
/*N*/   {
/*N*/       "Object/SnapLine",
/*N*/       "Object/PageMargin",
/*N*/       "Object/ObjectFrame",
/*N*/       "Object/ObjectPoint",
/*N*/       "Position/CreatingMoving",
/*N*/       "Position/ExtendEdges",
/*N*/       "Position/Rotating",
/*N*/       "Object/Range",
/*N*/       "Position/RotatingValue",
/*N*/       "Position/PointReduction"
/*N*/   };
/*N*/
/*N*/   rCount = 10;
/*N*/   ppNames = aPropNames;
/*N*/ }

// -----------------------------------------------------------------------------

/*N*/ BOOL SdOptionsSnap::ReadData( const Any* pValues )
/*N*/ {
/*N*/   if( pValues[0].hasValue() ) SetSnapHelplines( *(sal_Bool*) pValues[ 0 ].getValue() );
/*N*/   if( pValues[1].hasValue() ) SetSnapBorder( *(sal_Bool*)pValues[ 1 ].getValue() );
/*N*/   if( pValues[2].hasValue() ) SetSnapFrame( *(sal_Bool*) pValues[ 2 ].getValue() );
/*N*/   if( pValues[3].hasValue() ) SetSnapPoints( *(sal_Bool*) pValues[ 3 ].getValue() );
/*N*/   if( pValues[4].hasValue() ) SetOrtho( *(sal_Bool*) pValues[ 4 ].getValue() );
/*N*/   if( pValues[5].hasValue() ) SetBigOrtho( *(sal_Bool*) pValues[ 5 ].getValue() );
/*N*/   if( pValues[6].hasValue() ) SetRotate( *(sal_Bool*) pValues[ 6 ].getValue() );
/*N*/   if( pValues[7].hasValue() ) SetSnapArea( (INT16) *(sal_Int32*) pValues[ 7 ].getValue() );
/*N*/   if( pValues[8].hasValue() ) SetAngle( (INT16) *(sal_Int32*) pValues[ 8 ].getValue() );
/*N*/   if( pValues[9].hasValue() ) SetEliminatePolyPointLimitAngle( (INT16) *(sal_Int32*) pValues[ 9 ].getValue() );
/*N*/
/*N*/   return TRUE;
/*N*/ }

// -----------------------------------------------------------------------------

/*N*/ BOOL SdOptionsSnap::WriteData( Any* pValues ) const
/*N*/ {
/*N*/   pValues[ 0 ] <<= IsSnapHelplines();
/*N*/   pValues[ 1 ] <<= IsSnapBorder();
/*N*/   pValues[ 2 ] <<= IsSnapFrame();
/*N*/   pValues[ 3 ] <<= IsSnapPoints();
/*N*/   pValues[ 4 ] <<= IsOrtho();
/*N*/   pValues[ 5 ] <<= IsBigOrtho();
/*N*/   pValues[ 6 ] <<= IsRotate();
/*N*/   pValues[ 7 ] <<= (sal_Int32) GetSnapArea();
/*N*/   pValues[ 8 ] <<= (sal_Int32) GetAngle();
/*N*/   pValues[ 9 ] <<= (sal_Int32) GetEliminatePolyPointLimitAngle();
/*N*/
/*N*/   return TRUE;
/*N*/ }

/*************************************************************************
|*
|* SdOptionsSnapItem
|*
\************************************************************************/

//STRIP001 SdOptionsSnapItem::SdOptionsSnapItem( USHORT nWhich ) :
//STRIP001  SfxPoolItem     ( nWhich ),
//STRIP001  SdOptionsSnap   ( 0, FALSE )
//STRIP001 {
//STRIP001 }

// ----------------------------------------------------------------------

//STRIP001 SdOptionsSnapItem::SdOptionsSnapItem( USHORT nWhich, SdOptions* pOpts, FrameView* pView ) :
//STRIP001  SfxPoolItem     ( nWhich ),
//STRIP001  SdOptionsSnap   ( 0, FALSE )
//STRIP001 {
//STRIP001  if( pView )
//STRIP001  {
//STRIP001      SetSnapHelplines( pView->IsHlplSnap() );
//STRIP001      SetSnapBorder( pView->IsBordSnap() );
//STRIP001      SetSnapFrame( pView->IsOFrmSnap() );
//STRIP001      SetSnapPoints( pView->IsOPntSnap() );
//STRIP001      SetOrtho( pView->IsOrtho() );
//STRIP001      SetBigOrtho( pView->IsBigOrtho() );
//STRIP001      SetRotate( pView->IsAngleSnapEnabled() );
//STRIP001      SetSnapArea( pView->GetSnapMagneticPixel() );
//STRIP001      SetAngle( (INT16) pView->GetSnapAngle() );
//STRIP001      SetEliminatePolyPointLimitAngle( (INT16) pView->GetEliminatePolyPointLimitAngle() );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      SetSnapHelplines( pOpts->IsSnapHelplines() );
//STRIP001      SetSnapBorder( pOpts->IsSnapBorder() );
//STRIP001      SetSnapFrame( pOpts->IsSnapFrame() );
//STRIP001      SetSnapPoints( pOpts->IsSnapPoints() );
//STRIP001      SetOrtho( pOpts->IsOrtho() );
//STRIP001      SetBigOrtho( pOpts->IsBigOrtho() );
//STRIP001      SetRotate( pOpts->IsRotate() );
//STRIP001      SetSnapArea( pOpts->GetSnapArea() );
//STRIP001      SetAngle( pOpts->GetAngle() );
//STRIP001      SetEliminatePolyPointLimitAngle( pOpts->GetEliminatePolyPointLimitAngle() );
//STRIP001  }
//STRIP001 }

// ----------------------------------------------------------------------

//STRIP001 SfxPoolItem* SdOptionsSnapItem::Clone( SfxItemPool* ) const
//STRIP001 {
//STRIP001  return new SdOptionsSnapItem( *this );
//STRIP001 }


// ----------------------------------------------------------------------

//STRIP001 int SdOptionsSnapItem::operator==( const SfxPoolItem& rAttr ) const
//STRIP001 {
//STRIP001  DBG_ASSERT( SfxPoolItem::operator==(rAttr), "unterschiedliche Typen" );
//STRIP001  return( (SdOptionsSnap&) *this == (const SdOptionsSnap&)(const SdOptionsSnapItem&) rAttr );
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 void SdOptionsSnapItem::SetOptions( SdOptions* pOpts ) const
//STRIP001 {
//STRIP001  pOpts->SetSnapHelplines( IsSnapHelplines() );
//STRIP001  pOpts->SetSnapBorder( IsSnapBorder() );
//STRIP001  pOpts->SetSnapFrame( IsSnapFrame() );
//STRIP001  pOpts->SetSnapPoints( IsSnapPoints() );
//STRIP001  pOpts->SetOrtho( IsOrtho() );
//STRIP001  pOpts->SetBigOrtho( IsBigOrtho() );
//STRIP001  pOpts->SetRotate( IsRotate() );
//STRIP001  pOpts->SetSnapArea( GetSnapArea() );
//STRIP001  pOpts->SetAngle( GetAngle() );
//STRIP001  pOpts->SetEliminatePolyPointLimitAngle( GetEliminatePolyPointLimitAngle() );
//STRIP001 }

/*************************************************************************
|*
|* SdOptionsZoom
|*
\************************************************************************/

/*N*/ SdOptionsZoom::SdOptionsZoom( USHORT nConfigId, BOOL bUseConfig ) :
/*N*/   SdOptionsGeneric( nConfigId, ( bUseConfig &&  ( SDCFG_DRAW == nConfigId ) ) ?
/*N*/                                B2U( "Office.Draw/Zoom" ) :
/*N*/                                OUString() )
/*N*/ {
/*N*/   EnableModify( FALSE );
/*N*/   SetDefaults();
/*N*/   EnableModify( TRUE );
/*N*/ }

// -----------------------------------------------------------------------------

/*N*/ void SdOptionsZoom::SetDefaults()
/*N*/ {
/*N*/   SetScale( 1, 1 );
/*N*/ }

// -----------------------------------------------------------------------------

//STRIP001 BOOL SdOptionsZoom::operator==( const SdOptionsZoom& rOpt ) const
//STRIP001 {
//STRIP001  INT32 nX1, nX2, nY1, nY2;
//STRIP001
//STRIP001  GetScale( nX1, nY1 );
//STRIP001  rOpt.GetScale( nX2, nY2 );
//STRIP001
//STRIP001  return( ( nX1 == nX2 ) &&
//STRIP001          ( nY1 == nY2 ) );
//STRIP001 }

// -----------------------------------------------------------------------------

/*N*/ void SdOptionsZoom::GetPropNameArray( const char**& ppNames, ULONG& rCount ) const
/*N*/ {
/*N*/   static const char* aPropNames[] =
/*N*/   {
/*N*/       "ScaleX",
/*N*/       "ScaleY"
/*N*/   };
/*N*/
/*N*/   rCount = ( GetConfigId() == SDCFG_DRAW ) ? 2 : 0;
/*N*/   ppNames = aPropNames;
/*N*/ }

// -----------------------------------------------------------------------------

/*N*/ BOOL SdOptionsZoom::ReadData( const Any* pValues )
/*N*/ {
/*N*/   INT32 nX = 1, nY = 1;
/*N*/
/*N*/   if( pValues[0].hasValue() ) nX = ( *(sal_Int32*) pValues[ 0 ].getValue() );
/*N*/   if( pValues[1].hasValue() ) nY = ( *(sal_Int32*) pValues[ 1 ].getValue() );
/*N*/
/*N*/   SetScale( nX, nY );
/*N*/
/*N*/   return TRUE;
/*N*/ }

// -----------------------------------------------------------------------------

/*N*/ BOOL SdOptionsZoom::WriteData( Any* pValues ) const
/*N*/ {
/*N*/   INT32 nX, nY;
/*N*/
/*N*/   GetScale( nX, nY );
/*N*/
/*N*/   pValues[ 0 ] <<= (sal_Int32) nX;
/*N*/   pValues[ 1 ] <<= (sal_Int32) nY;
/*N*/
/*N*/   return TRUE;
/*N*/ }

/*************************************************************************
|*
|* SdOptionsZoomItem
|*
\************************************************************************/

//STRIP001 SdOptionsZoomItem::SdOptionsZoomItem( USHORT nWhich ) :
//STRIP001  SfxPoolItem     ( nWhich ),
//STRIP001  SdOptionsZoom   ( 0, FALSE )
//STRIP001 {
//STRIP001 }

// ----------------------------------------------------------------------

//STRIP001 SdOptionsZoomItem::SdOptionsZoomItem( USHORT nWhich, SdOptions* pOpts, FrameView* pView ) :
//STRIP001  SfxPoolItem     ( nWhich ),
//STRIP001  SdOptionsZoom   ( 0, FALSE )
//STRIP001 {
//STRIP001  INT32 nX, nY;
//STRIP001
//STRIP001  pOpts->GetScale( nX, nY );
//STRIP001  SetScale( nX, nY );
//STRIP001 }

// ----------------------------------------------------------------------

//STRIP001 SfxPoolItem* SdOptionsZoomItem::Clone( SfxItemPool* ) const
//STRIP001 {
//STRIP001  return new SdOptionsZoomItem( *this );
//STRIP001 }


// ----------------------------------------------------------------------

//STRIP001 int SdOptionsZoomItem::operator==( const SfxPoolItem& rAttr ) const
//STRIP001 {
//STRIP001  DBG_ASSERT( SfxPoolItem::operator==(rAttr), "unterschiedliche Typen" );
//STRIP001  return( (SdOptionsZoom&) *this == (const SdOptionsZoom&)(const SdOptionsZoomItem&) rAttr );
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 void SdOptionsZoomItem::SetOptions( SdOptions* pOpts ) const
//STRIP001 {
//STRIP001  INT32 nX, nY;
//STRIP001
//STRIP001  GetScale( nX, nY );
//STRIP001  pOpts->SetScale( nX, nY );
//STRIP001 }

/*************************************************************************
|*
|* SdOptionsGrid
|*
\************************************************************************/

/*N*/ SdOptionsGrid::SdOptionsGrid( USHORT nConfigId, BOOL bUseConfig ) :
/*N*/   SdOptionsGeneric( nConfigId, bUseConfig ?
/*N*/                     ( ( SDCFG_DRAW == nConfigId ) ?
/*N*/                       B2U( "Office.Draw/Grid" ) :
/*N*/                       B2U( "Office.Impress/Grid" ) ) :
/*N*/                     OUString() )
/*N*/ {
/*N*/   EnableModify( FALSE );
/*N*/   SetDefaults();
/*N*/   EnableModify( TRUE );
/*N*/ }

// -----------------------------------------------------------------------------

/*N*/ SdOptionsGrid::~SdOptionsGrid()
/*N*/ {
/*N*/ }

// -----------------------------------------------------------------------------

/*N*/ void SdOptionsGrid::SetDefaults()
/*N*/ {
/*N*/   const UINT32 nVal = 1000;
/*N*/
/*N*/   SetFldDivisionX( nVal );
/*N*/   SetFldDivisionY( nVal );
/*N*/   SetFldDrawX( nVal );
/*N*/   SetFldDrawY( nVal );
/*N*/   SetFldSnapX( nVal );
/*N*/   SetFldSnapY( nVal );
/*N*/   SetUseGridSnap( FALSE );
/*N*/   SetSynchronize( TRUE );
/*N*/   SetGridVisible( FALSE );
/*N*/   SetEqualGrid( TRUE );
/*N*/ }

// -----------------------------------------------------------------------------

//STRIP001 BOOL SdOptionsGrid::operator==( const SdOptionsGrid& rOpt ) const
//STRIP001 {
//STRIP001  return( GetFldDrawX() == rOpt.GetFldDrawX() &&
//STRIP001          GetFldDivisionX() == rOpt.GetFldDivisionX() &&
//STRIP001          GetFldDrawY() == rOpt.GetFldDrawY() &&
//STRIP001          GetFldDivisionY() == rOpt.GetFldDivisionY() &&
//STRIP001          GetFldSnapX() == rOpt.GetFldSnapX() &&
//STRIP001          GetFldSnapY() == rOpt.GetFldSnapY() &&
//STRIP001          IsUseGridSnap() == rOpt.IsUseGridSnap() &&
//STRIP001          IsSynchronize() == rOpt.IsSynchronize() &&
//STRIP001          IsGridVisible() == rOpt.IsGridVisible() &&
//STRIP001          IsEqualGrid() == rOpt.IsEqualGrid() );
//STRIP001 }

// -----------------------------------------------------------------------------

/*N*/ void SdOptionsGrid::GetPropNameArray( const char**& ppNames, ULONG& rCount ) const
/*N*/ {
/*N*/   static const char* aPropNamesMetric[] =
/*N*/   {
/*N*/       "Resolution/XAxis/Metric",
/*N*/       "Resolution/YAxis/Metric",
/*N*/       "Subdivision/XAxis",
/*N*/       "Subdivision/YAxis",
/*N*/       "SnapGrid/XAxis/Metric",
/*N*/       "SnapGrid/YAxis/Metric",
/*N*/       "Option/SnapToGrid",
/*N*/       "Option/Synchronize",
/*N*/       "Option/VisibleGrid",
/*N*/       "SnapGrid/Size"
/*N*/   };
/*N*/
/*N*/   static const char* aPropNamesNonMetric[] =
/*N*/   {
/*N*/       "Resolution/XAxis/NonMetric",
/*N*/       "Resolution/YAxis/NonMetric",
/*N*/       "Subdivision/XAxis",
/*N*/       "Subdivision/YAxis",
/*N*/       "SnapGrid/XAxis/NonMetric",
/*N*/       "SnapGrid/YAxis/NonMetric",
/*N*/       "Option/SnapToGrid",
/*N*/       "Option/Synchronize",
/*N*/       "Option/VisibleGrid",
/*N*/       "SnapGrid/Size"
/*N*/   };
/*N*/
/*N*/   rCount = 10;
/*N*/
/*N*/   if( isMetricSystem() )
/*N*/       ppNames = aPropNamesMetric;
/*N*/   else
/*N*/       ppNames = aPropNamesNonMetric;
/*N*/ }

// -----------------------------------------------------------------------------

/*N*/ BOOL SdOptionsGrid::ReadData( const Any* pValues )
/*N*/ {
/*N*/   if( pValues[0].hasValue() ) SetFldDrawX( *(sal_Int32*) pValues[ 0 ].getValue() );
/*N*/   if( pValues[1].hasValue() ) SetFldDrawY( *(sal_Int32*) pValues[ 1 ].getValue() );
/*N*/
/*N*/   if( pValues[2].hasValue() )
/*N*/   {
/*N*/       const UINT32 nDivX = FRound( *(double*) pValues[ 2 ].getValue() );
/*N*/       SetFldDivisionX( SvxOptionsGrid::GetFldDrawX() / ( nDivX + 1 ) );
/*N*/   }
/*N*/
/*N*/   if( pValues[3].hasValue() )
/*N*/   {
/*N*/       const UINT32 nDivY = FRound( *(double*) pValues[ 3 ].getValue() );
/*N*/       SetFldDivisionY( SvxOptionsGrid::GetFldDrawY() / ( nDivY + 1 ) );
/*N*/   }
/*N*/
/*N*/   if( pValues[4].hasValue() ) SetFldSnapX( *(sal_Int32*) pValues[ 4 ].getValue() );
/*N*/   if( pValues[5].hasValue() ) SetFldSnapY( *(sal_Int32*) pValues[ 5 ].getValue() );
/*N*/   if( pValues[6].hasValue() ) SetUseGridSnap( *(sal_Bool*) pValues[ 6 ].getValue() );
/*N*/   if( pValues[7].hasValue() ) SetSynchronize( *(sal_Bool*) pValues[ 7 ].getValue() );
/*N*/   if( pValues[8].hasValue() ) SetGridVisible( *(sal_Bool*) pValues[ 8 ].getValue() );
/*N*/   if( pValues[9].hasValue() ) SetEqualGrid( *(sal_Bool*) pValues[ 9 ].getValue() );
/*N*/
/*N*/   return TRUE;
/*N*/ }

// -----------------------------------------------------------------------------

/*N*/ BOOL SdOptionsGrid::WriteData( Any* pValues ) const
/*N*/ {
/*N*/   pValues[ 0 ] <<= (sal_Int32) GetFldDrawX();
/*N*/   pValues[ 1 ] <<= (sal_Int32) GetFldDrawY();
/*N*/   pValues[ 2 ] <<= ( GetFldDivisionX() ? ( (double) GetFldDrawX() / GetFldDivisionX() - 1.0 ) : (double) 0 );
/*N*/   pValues[ 3 ] <<= ( GetFldDivisionY() ? ( (double) GetFldDrawY() / GetFldDivisionY() - 1.0 ) : (double) 0 );
/*N*/   pValues[ 4 ] <<= (sal_Int32) GetFldSnapX();
/*N*/   pValues[ 5 ] <<= (sal_Int32) GetFldSnapY();
/*N*/   pValues[ 6 ] <<= IsUseGridSnap();
/*N*/   pValues[ 7 ] <<= IsSynchronize();
/*N*/   pValues[ 8 ] <<= IsGridVisible();
/*N*/   pValues[ 9 ] <<= IsEqualGrid();
/*N*/
/*N*/   return TRUE;
/*N*/ }

/*************************************************************************
|*
|* SdOptionsGridItem
|*
\************************************************************************/

//STRIP001 SdOptionsGridItem::SdOptionsGridItem( USHORT nWhich ) :
//STRIP001  SvxGridItem( nWhich )
//STRIP001 {
//STRIP001 }

// -----------------------------------------------------------------------------

//STRIP001 SdOptionsGridItem::SdOptionsGridItem( USHORT nWhich, SdOptions* pOpts, FrameView* pView ) :
//STRIP001  SvxGridItem( nWhich )
//STRIP001 {
//STRIP001  SetSynchronize( pOpts->IsSynchronize() );
//STRIP001  SetEqualGrid( pOpts->IsEqualGrid() );
//STRIP001
//STRIP001  if( pView )
//STRIP001  {
//STRIP001      SetFldDrawX( pView->GetGridCoarse().Width() );
//STRIP001      SetFldDrawY( pView->GetGridCoarse().Height() );
//STRIP001      SetFldDivisionX( pView->GetGridFine().Width() ? ( GetFldDrawX() / pView->GetGridFine().Width() - 1 ) : 0 );
//STRIP001      SetFldDivisionY( pView->GetGridFine().Height() ? ( GetFldDrawY() / pView->GetGridFine().Height() - 1 ) : 0 );
//STRIP001      SetFldSnapX( pView->GetSnapGrid().Width() );
//STRIP001      SetFldSnapY( pView->GetSnapGrid().Height() );
//STRIP001      SetUseGridSnap( pView->IsGridSnap() );
//STRIP001      SetGridVisible( pView->IsGridVisible() );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      SetFldDrawX( pOpts->GetFldDrawX() );
//STRIP001      SetFldDrawY( pOpts->GetFldDrawY() );
//STRIP001      SetFldDivisionX( pOpts->GetFldDivisionX() ? ( pOpts->GetFldDrawX() / pOpts->GetFldDivisionX() - 1 ) : 0 );
//STRIP001      SetFldDivisionY( pOpts->GetFldDivisionY() ? ( pOpts->GetFldDrawY() / pOpts->GetFldDivisionY() - 1 ) : 0 );
//STRIP001      SetFldSnapX( pOpts->GetFldSnapX() );
//STRIP001      SetFldSnapY( pOpts->GetFldSnapY() );
//STRIP001      SetUseGridSnap( pOpts->IsUseGridSnap() );
//STRIP001      SetGridVisible( pOpts->IsGridVisible() );
//STRIP001  }
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 void SdOptionsGridItem::SetOptions( SdOptions* pOpts ) const
//STRIP001 {
//STRIP001  pOpts->SetFldDrawX( GetFldDrawX() );
//STRIP001  pOpts->SetFldDivisionX( GetFldDrawX() / ( GetFldDivisionX() + 1 ) );
//STRIP001  pOpts->SetFldDrawY( GetFldDrawY() );
//STRIP001  pOpts->SetFldDivisionY( GetFldDrawY() / ( GetFldDivisionY() + 1 ) );
//STRIP001  pOpts->SetFldSnapX( GetFldSnapX() );
//STRIP001  pOpts->SetFldSnapY( GetFldSnapY() );
//STRIP001  pOpts->SetUseGridSnap( GetUseGridSnap() );
//STRIP001  pOpts->SetSynchronize( GetSynchronize() );
//STRIP001  pOpts->SetGridVisible( GetGridVisible() );
//STRIP001  pOpts->SetEqualGrid( GetEqualGrid() );
//STRIP001 }

/*************************************************************************
|*
|* SdOptionsPrint
|*
\************************************************************************/

/*N*/ SdOptionsPrint::SdOptionsPrint( USHORT nConfigId, BOOL bUseConfig ) :
/*N*/   SdOptionsGeneric( nConfigId, bUseConfig ?
/*N*/                     ( ( SDCFG_DRAW == nConfigId ) ?
/*N*/                       B2U( "Office.Draw/Print" ) :
/*N*/                       B2U( "Office.Impress/Print" ) ) :
/*N*/                     OUString() )
/*N*/ {
/*N*/   EnableModify( FALSE );
/*N*/   SetDefaults();
/*N*/   EnableModify( TRUE );
/*N*/ }

// -----------------------------------------------------------------------------

/*N*/ void SdOptionsPrint::SetDefaults()
/*N*/ {
/*N*/   SetDraw( TRUE );
/*N*/   SetNotes( FALSE );
/*N*/   SetHandout( FALSE );
/*N*/   SetOutline( FALSE );
/*N*/   SetDate( FALSE );
/*N*/   SetTime( FALSE );
/*N*/   SetPagename( FALSE );
/*N*/   SetHiddenPages( TRUE );
/*N*/   SetPagesize( FALSE );
/*N*/   SetPagetile( FALSE );
/*N*/   SetWarningPrinter( TRUE );
/*N*/   SetWarningSize( FALSE );
/*N*/   SetWarningOrientation( FALSE );
/*N*/   SetBooklet( FALSE );
/*N*/   SetFrontPage( TRUE );
/*N*/   SetBackPage( TRUE );
/*N*/   SetCutPage( FALSE );
/*N*/   SetPaperbin( FALSE );
/*N*/   SetOutputQuality( 0 );
/*N*/ }

// -----------------------------------------------------------------------------

/*N*/ BOOL SdOptionsPrint::operator==( const SdOptionsPrint& rOpt ) const
/*N*/ {
/*N*/   return( IsDraw() == rOpt.IsDraw() &&
/*N*/           IsNotes() == rOpt.IsNotes() &&
/*N*/           IsHandout() == rOpt.IsHandout() &&
/*N*/           IsOutline() == rOpt.IsOutline() &&
/*N*/           IsDate() == rOpt.IsDate() &&
/*N*/           IsTime() == rOpt.IsTime() &&
/*N*/           IsPagename() == rOpt.IsPagename() &&
/*N*/           IsHiddenPages() == rOpt.IsHiddenPages() &&
/*N*/           IsPagesize() == rOpt.IsPagesize() &&
/*N*/           IsPagetile() == rOpt.IsPagetile() &&
/*N*/           IsWarningPrinter() == rOpt.IsWarningPrinter() &&
/*N*/           IsWarningSize() == rOpt.IsWarningSize() &&
/*N*/           IsWarningOrientation() == rOpt.IsWarningOrientation() &&
/*N*/           IsBooklet() == rOpt.IsBooklet() &&
/*N*/           IsFrontPage() == rOpt.IsFrontPage() &&
/*N*/           IsBackPage() == rOpt.IsBackPage() &&
/*N*/           IsCutPage() == rOpt.IsCutPage() &&
/*N*/           IsPaperbin() == rOpt.IsPaperbin() &&
/*N*/           GetOutputQuality() == rOpt.GetOutputQuality() );
/*N*/ }

// -----------------------------------------------------------------------------

/*N*/ void SdOptionsPrint::GetPropNameArray( const char**& ppNames, ULONG& rCount ) const
/*N*/ {
/*N*/   static const char* aDrawPropNames[] =
/*N*/   {
/*N*/       "Other/Date",
/*N*/       "Other/Time",
/*N*/       "Other/PageName",
/*N*/       "Other/HiddenPage",
/*N*/       "Page/PageSize",
/*N*/       "Page/PageTile",
/*N*/       // bWarningPrinter
/*N*/       // bWarningSize
/*N*/       // bWarningOrientation
/*N*/       "Page/Booklet",
/*N*/       "Page/BookletFront",
/*N*/       "Page/BookletBack",
/*N*/       // bCutPage
/*N*/       "Other/FromPrinterSetup",
/*N*/       "Other/Quality",
/*N*/       "Content/Drawing",
/*N*/   };
/*N*/   static const char* aImpressPropNames[] =
/*N*/   {
/*N*/       "Other/Date",
/*N*/       "Other/Time",
/*N*/       "Other/PageName",
/*N*/       "Other/HiddenPage",
/*N*/       "Page/PageSize",
/*N*/       "Page/PageTile",
/*N*/       // bWarningPrinter
/*N*/       // bWarningSize
/*N*/       // bWarningOrientation
/*N*/       "Page/Booklet",
/*N*/       "Page/BookletFront",
/*N*/       "Page/BookletBack",
/*N*/       // bCutPage
/*N*/       "Other/FromPrinterSetup",
/*N*/       "Other/Quality",
/*N*/       "Content/Presentation",
/*N*/       "Content/Note",
/*N*/       "Content/Handout",
/*N*/       "Content/Outline"
/*N*/   };
/*N*/
/*N*/   if( GetConfigId() == SDCFG_IMPRESS )
/*N*/   {
/*N*/       rCount = 15;
/*N*/       ppNames = aImpressPropNames;
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       rCount = 12;
/*N*/       ppNames = aDrawPropNames;
/*N*/   }
/*N*/ }

// -----------------------------------------------------------------------------

/*N*/ BOOL SdOptionsPrint::ReadData( const Any* pValues )
/*N*/ {
/*N*/   if( pValues[0].hasValue() ) SetDate( *(sal_Bool*) pValues[ 0 ].getValue() );
/*N*/   if( pValues[1].hasValue() ) SetTime( *(sal_Bool*) pValues[ 1 ].getValue() );
/*N*/   if( pValues[2].hasValue() ) SetPagename( *(sal_Bool*) pValues[ 2 ].getValue() );
/*N*/   if( pValues[3].hasValue() ) SetHiddenPages( *(sal_Bool*) pValues[ 3 ].getValue() );
/*N*/   if( pValues[4].hasValue() ) SetPagesize( *(sal_Bool*) pValues[ 4 ].getValue() );
/*N*/   if( pValues[5].hasValue() ) SetPagetile( *(sal_Bool*) pValues[ 5 ].getValue() );
/*N*/   if( pValues[6].hasValue() ) SetBooklet( *(sal_Bool*) pValues[ 6 ].getValue() );
/*N*/   if( pValues[7].hasValue() ) SetFrontPage( *(sal_Bool*) pValues[ 7 ].getValue() );
/*N*/   if( pValues[8].hasValue() ) SetBackPage( *(sal_Bool*) pValues[ 8 ].getValue() );
/*N*/   if( pValues[9].hasValue() ) SetPaperbin( *(sal_Bool*) pValues[ 9 ].getValue() );
/*N*/   if( pValues[10].hasValue() ) SetOutputQuality( (UINT16) *(sal_Int32*) pValues[ 10 ].getValue() );
/*N*/   if( pValues[11].hasValue() ) SetDraw( *(sal_Bool*) pValues[ 11 ].getValue() );
/*N*/
/*N*/   // just for impress
/*N*/   if( GetConfigId() == SDCFG_IMPRESS )
/*N*/   {
/*N*/       if( pValues[12].hasValue() ) SetNotes( *(sal_Bool*) pValues[ 12 ].getValue() );
/*N*/       if( pValues[13].hasValue() ) SetHandout( *(sal_Bool*) pValues[ 13 ].getValue() );
/*N*/       if( pValues[14].hasValue() ) SetOutline( *(sal_Bool*) pValues[ 14 ].getValue() );
/*N*/   }
/*N*/
/*N*/   return TRUE;
/*N*/ }

// -----------------------------------------------------------------------------

/*N*/ BOOL SdOptionsPrint::WriteData( Any* pValues ) const
/*N*/ {
/*N*/   pValues[ 0 ] <<= IsDate();
/*N*/   pValues[ 1 ] <<= IsTime();
/*N*/   pValues[ 2 ] <<= IsPagename();
/*N*/   pValues[ 3 ] <<= IsHiddenPages();
/*N*/   pValues[ 4 ] <<= IsPagesize();
/*N*/   pValues[ 5 ] <<= IsPagetile();
/*N*/   pValues[ 6 ] <<= IsBooklet();
/*N*/   pValues[ 7 ] <<= IsFrontPage();
/*N*/   pValues[ 8 ] <<= IsBackPage();
/*N*/   pValues[ 9 ] <<= IsPaperbin();
/*N*/   pValues[ 10 ] <<= (sal_Int32) GetOutputQuality();
/*N*/   pValues[ 11 ] <<= IsDraw();
/*N*/
/*N*/   // just for impress
/*N*/   if( GetConfigId() == SDCFG_IMPRESS )
/*N*/   {
/*N*/       pValues[ 12 ] <<= IsNotes();
/*N*/       pValues[ 13 ] <<= IsHandout();
/*N*/       pValues[ 14 ] <<= IsOutline();
/*N*/   }
/*N*/
/*N*/   return TRUE;
/*N*/ }

/*N*/ void SdOptionsPrint::SetPrinterOptions( const SdOptionsPrint* pOptions )
/*N*/ {
/*N*/   bDraw = pOptions->bDraw;
/*N*/   bNotes = pOptions->bNotes;
/*N*/   bHandout = pOptions->bHandout;
/*N*/   bOutline = pOptions->bOutline;
/*N*/   bDate = pOptions->bDate;
/*N*/   bTime = pOptions->bTime;
/*N*/   bPagename = pOptions->bPagename;
/*N*/   bHiddenPages = pOptions->bHiddenPages;
/*N*/   bPagesize = pOptions->bPagesize;
/*N*/   bPagetile = pOptions->bPagetile;
/*N*/   bWarningPrinter = pOptions->bWarningPrinter;
/*N*/   bWarningSize = pOptions->bWarningSize;
/*N*/   bWarningOrientation = pOptions->bWarningOrientation;
/*N*/   bBooklet = pOptions->bBooklet;
/*N*/   bFront = pOptions->bFront;
/*N*/   bBack = pOptions->bBack;
/*N*/   bCutPage = pOptions->bCutPage;
/*N*/   bPaperbin = pOptions->bPaperbin;
/*N*/   nQuality = pOptions->nQuality;
/*N*/ }

/*************************************************************************
|*
|* SdOptionsPrintItem
|*
\************************************************************************/

/*N*/ SdOptionsPrintItem::SdOptionsPrintItem( USHORT nWhich ) :
/*N*/   SfxPoolItem     ( nWhich ),
/*N*/   SdOptionsPrint  ( 0, FALSE )
/*N*/ {
/*N*/ }

// ----------------------------------------------------------------------

/*N*/ SdOptionsPrintItem::SdOptionsPrintItem( USHORT nWhich, SdOptions* pOpts, FrameView* pView ) :
/*N*/   SfxPoolItem     ( nWhich ),
/*N*/   SdOptionsPrint  ( 0, FALSE )
/*N*/ {
/*N*/   SetDraw( pOpts->IsDraw() );
/*N*/   SetNotes( pOpts->IsNotes() );
/*N*/   SetHandout( pOpts->IsHandout() );
/*N*/   SetOutline( pOpts->IsOutline() );
/*N*/   SetDate( pOpts->IsDate() );
/*N*/   SetTime( pOpts->IsTime() );
/*N*/   SetPagename( pOpts->IsPagename() );
/*N*/   SetHiddenPages( pOpts->IsHiddenPages() );
/*N*/   SetPagesize( pOpts->IsPagesize() );
/*N*/   SetPagetile( pOpts->IsPagetile() );
/*N*/   SetWarningPrinter( pOpts->IsWarningPrinter() );
/*N*/   SetWarningSize( pOpts->IsWarningSize() );
/*N*/   SetWarningOrientation( pOpts->IsWarningOrientation() );
/*N*/   SetBooklet( pOpts->IsBooklet() );
/*N*/   SetFrontPage( pOpts->IsFrontPage() );
/*N*/   SetBackPage( pOpts->IsBackPage() );
/*N*/   SetCutPage( pOpts->IsCutPage() );
/*N*/   SetPaperbin( pOpts->IsPaperbin() );
/*N*/   SetOutputQuality( pOpts->GetOutputQuality() );
/*N*/ }

// ----------------------------------------------------------------------

/*N*/ SfxPoolItem* SdOptionsPrintItem::Clone( SfxItemPool* ) const
/*N*/ {
/*N*/   return new SdOptionsPrintItem( *this );
/*N*/ }

// ----------------------------------------------------------------------

/*N*/ int SdOptionsPrintItem::operator==( const SfxPoolItem& rAttr ) const
/*N*/ {
/*N*/   DBG_ASSERT( SfxPoolItem::operator==(rAttr), "unterschiedliche Typen" );
/*N*/   return( (SdOptionsPrint&) *this == (const SdOptionsPrint&)(const SdOptionsPrintItem&) rAttr );
/*N*/ }

// -----------------------------------------------------------------------

//STRIP001 void SdOptionsPrintItem::SetOptions( SdOptions* pOpts ) const
//STRIP001 {
//STRIP001  pOpts->SetDraw( IsDraw() );
//STRIP001  pOpts->SetNotes( IsNotes() );
//STRIP001  pOpts->SetHandout( IsHandout() );
//STRIP001  pOpts->SetOutline( IsOutline() );
//STRIP001  pOpts->SetDate( IsDate() );
//STRIP001  pOpts->SetTime( IsTime() );
//STRIP001  pOpts->SetPagename( IsPagename() );
//STRIP001  pOpts->SetHiddenPages( IsHiddenPages() );
//STRIP001  pOpts->SetPagesize( IsPagesize() );
//STRIP001  pOpts->SetPagetile( IsPagetile() );
//STRIP001  pOpts->SetWarningPrinter( IsWarningPrinter() );
//STRIP001  pOpts->SetWarningSize( IsWarningSize() );
//STRIP001  pOpts->SetWarningOrientation( IsWarningOrientation() );
//STRIP001  pOpts->SetBooklet( IsBooklet() );
//STRIP001  pOpts->SetFrontPage( IsFrontPage() );
//STRIP001  pOpts->SetBackPage( IsBackPage() );
//STRIP001  pOpts->SetCutPage( IsCutPage() );
//STRIP001  pOpts->SetPaperbin( IsPaperbin() );
//STRIP001  pOpts->SetOutputQuality( GetOutputQuality() );
//STRIP001 }

/*************************************************************************
|*
|* SdOptions
|*
\************************************************************************/

/*N*/ SdOptions::SdOptions( USHORT nConfigId ) :
/*N*/   SdOptionsLayout( nConfigId, TRUE ),
/*N*/   SdOptionsContents( nConfigId, TRUE ),
/*N*/   SdOptionsMisc( nConfigId, TRUE ),
/*N*/   SdOptionsSnap( nConfigId, TRUE ),
/*N*/   SdOptionsZoom( nConfigId, TRUE ),
/*N*/   SdOptionsGrid( nConfigId, TRUE ),
/*N*/   SdOptionsPrint( nConfigId, TRUE )
/*N*/ {
/*N*/ }

// ----------------------------------------------------------------------

/*N*/ SdOptions::~SdOptions()
/*N*/ {
/*N*/ }

// ----------------------------------------------------------------------

//STRIP001 void SdOptions::SetDefaults( ULONG nOptionsRange )
//STRIP001 {
//STRIP001  if( nOptionsRange & SD_OPTIONS_LAYOUT )
//STRIP001      SdOptionsLayout::SetDefaults();
//STRIP001
//STRIP001  if( nOptionsRange & SD_OPTIONS_CONTENTS )
//STRIP001      SdOptionsContents::SetDefaults();
//STRIP001
//STRIP001  if( nOptionsRange & SD_OPTIONS_MISC )
//STRIP001      SdOptionsMisc::SetDefaults();
//STRIP001
//STRIP001  if( nOptionsRange & SD_OPTIONS_SNAP )
//STRIP001      SdOptionsSnap::SetDefaults();
//STRIP001
//STRIP001  if( nOptionsRange & SD_OPTIONS_ZOOM )
//STRIP001      SdOptionsZoom::SetDefaults();
//STRIP001
//STRIP001  if( nOptionsRange & SD_OPTIONS_GRID )
//STRIP001      SdOptionsGrid::SetDefaults();
//STRIP001
//STRIP001  if( nOptionsRange & SD_OPTIONS_PRINT )
//STRIP001      SdOptionsPrint::SetDefaults();
//STRIP001 }

// ----------------------------------------------------------------------

//STRIP001 void SdOptions::StoreConfig( ULONG nOptionsRange )
//STRIP001 {
//STRIP001  if( nOptionsRange & SD_OPTIONS_LAYOUT )
//STRIP001      SdOptionsLayout::Store();
//STRIP001
//STRIP001  if( nOptionsRange & SD_OPTIONS_CONTENTS )
//STRIP001      SdOptionsContents::Store();
//STRIP001
//STRIP001  if( nOptionsRange & SD_OPTIONS_MISC )
//STRIP001      SdOptionsMisc::Store();
//STRIP001
//STRIP001  if( nOptionsRange & SD_OPTIONS_SNAP )
//STRIP001      SdOptionsSnap::Store();
//STRIP001
//STRIP001  if( nOptionsRange & SD_OPTIONS_ZOOM )
//STRIP001      SdOptionsZoom::Store();
//STRIP001
//STRIP001  if( nOptionsRange & SD_OPTIONS_GRID )
//STRIP001      SdOptionsGrid::Store();
//STRIP001
//STRIP001  if( nOptionsRange & SD_OPTIONS_PRINT )
//STRIP001      SdOptionsPrint::Store();
//STRIP001 }
}
