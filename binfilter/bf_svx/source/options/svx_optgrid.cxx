/*************************************************************************
 *
 *  $RCSfile: svx_optgrid.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:45:46 $
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

#ifndef _SHL_HXX
#include <tools/shl.hxx>
#endif
#ifndef _SFXAPP_HXX //autogen
#include <bf_sfx2/app.hxx>
#endif
#ifndef _SFXMODULE_HXX //autogen
#include <bf_sfx2/module.hxx>
#endif
#pragma hdrstop

#define _SVX_OPTGRID_CXX

#include "svxids.hrc"
#include "dialmgr.hxx"
#include "optgrid.hxx"
#include "dialogs.hrc"
#include "optgrid.hrc"
#include "dlgutil.hxx"
namespace binfilter {

/* -----------------18.08.98 17:41-------------------
 * local functions
 * --------------------------------------------------*/
//STRIP001 void lcl_GetMinMax(MetricField& rField, long& nFirst, long& nLast, long& nMin, long& nMax)
//STRIP001 {
//STRIP001  nFirst  = rField.Denormalize( rField.GetFirst( FUNIT_TWIP ) );
//STRIP001  nLast = rField.Denormalize( rField.GetLast( FUNIT_TWIP ) );
//STRIP001  nMin = rField.Denormalize( rField.GetMin( FUNIT_TWIP ) );
//STRIP001  nMax = rField.Denormalize( rField.GetMax( FUNIT_TWIP ) );
//STRIP001 }

//STRIP001 void lcl_SetMinMax(MetricField& rField, long nFirst, long nLast, long nMin, long nMax)
//STRIP001 {
//STRIP001  rField.SetFirst( rField.Normalize( nFirst ), FUNIT_TWIP );
//STRIP001  rField.SetLast( rField.Normalize( nLast ), FUNIT_TWIP );
//STRIP001  rField.SetMin( rField.Normalize( nMin ), FUNIT_TWIP );
//STRIP001  rField.SetMax( rField.Normalize( nMax ), FUNIT_TWIP );
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung: Rastereinstellungen Ctor
 --------------------------------------------------------------------*/

/*N*/ SvxOptionsGrid::SvxOptionsGrid() :
/*N*/   nFldDrawX       ( 100 ),
/*N*/   nFldDivisionX   ( 0 ),
/*N*/   nFldDrawY       ( 100 ),
/*N*/   nFldDivisionY   ( 0 ),
/*N*/   nFldSnapX       ( 100 ),
/*N*/   nFldSnapY       ( 100 ),
/*N*/   bUseGridsnap    ( 0 ),
/*N*/   bSynchronize    ( 1 ),
/*N*/   bGridVisible    ( 0 ),
/*N*/   bEqualGrid      ( 1 )
/*N*/ {
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung: Rastereinstellungen Dtor
 --------------------------------------------------------------------*/

/*N*/ SvxOptionsGrid::~SvxOptionsGrid()
/*N*/ {
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung: Item fuer Rastereinstellungen
 --------------------------------------------------------------------*/

//STRIP001 SvxGridItem::SvxGridItem( const SvxGridItem& rItem ):
//STRIP001          SfxPoolItem(rItem)
//STRIP001 {
//STRIP001  bUseGridsnap = rItem.bUseGridsnap ;
//STRIP001  bSynchronize = rItem.bSynchronize ;
//STRIP001  bGridVisible = rItem.bGridVisible ;
//STRIP001  bEqualGrid   = rItem.bEqualGrid   ;
//STRIP001  nFldDrawX    = rItem.nFldDrawX    ;
//STRIP001  nFldDivisionX= rItem.nFldDivisionX;
//STRIP001  nFldDrawY    = rItem.nFldDrawY    ;
//STRIP001  nFldDivisionY= rItem.nFldDivisionY;
//STRIP001  nFldSnapX    = rItem.nFldSnapX    ;
//STRIP001  nFldSnapY    = rItem.nFldSnapY    ;
//STRIP001
//STRIP001 };

/*--------------------------------------------------------------------
    Beschreibung:
 --------------------------------------------------------------------*/

//STRIP001 SfxPoolItem*  SvxGridItem::Clone( SfxItemPool* ) const
//STRIP001 {
//STRIP001  return new SvxGridItem( *this );
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung:
 --------------------------------------------------------------------*/

//STRIP001 int SvxGridItem::operator==( const SfxPoolItem& rAttr ) const
//STRIP001 {
//STRIP001  DBG_ASSERT( SfxPoolItem::operator==(rAttr), "unterschiedliche Typen" );
//STRIP001
//STRIP001  const SvxGridItem& rItem = (const SvxGridItem&) rAttr;
//STRIP001
//STRIP001  return (    bUseGridsnap == rItem.bUseGridsnap &&
//STRIP001              bSynchronize == rItem.bSynchronize &&
//STRIP001              bGridVisible == rItem.bGridVisible &&
//STRIP001              bEqualGrid   == rItem.bEqualGrid   &&
//STRIP001              nFldDrawX    == rItem.nFldDrawX    &&
//STRIP001              nFldDivisionX== rItem.nFldDivisionX&&
//STRIP001              nFldDrawY    == rItem.nFldDrawY    &&
//STRIP001              nFldDivisionY== rItem.nFldDivisionY&&
//STRIP001              nFldSnapX    == rItem.nFldSnapX    &&
//STRIP001              nFldSnapY    == rItem.nFldSnapY     );
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung:
 --------------------------------------------------------------------*/

//STRIP001 SfxItemPresentation  SvxGridItem::GetPresentation
//STRIP001 (
//STRIP001  SfxItemPresentation ePres,
//STRIP001  SfxMapUnit          /*eCoreUnit*/,
//STRIP001  SfxMapUnit          /*ePresUnit*/,
//STRIP001     String&             rText, const IntlWrapper *
//STRIP001 )    const
//STRIP001 {
//STRIP001  switch ( ePres )
//STRIP001  {
//STRIP001      case SFX_ITEM_PRESENTATION_NONE:
//STRIP001          rText.Erase();
//STRIP001          return SFX_ITEM_PRESENTATION_NONE;
//STRIP001      case SFX_ITEM_PRESENTATION_NAMELESS:
//STRIP001      case SFX_ITEM_PRESENTATION_COMPLETE:
//STRIP001          rText = String::CreateFromAscii("SvxGridItem");
//STRIP001          return ePres;
//STRIP001  }
//STRIP001  return SFX_ITEM_PRESENTATION_NONE;
//STRIP001 }


/*----------------- OS 23.02.95  -----------------------
 TabPage Rastereinstellungen
-------------------------------------------------------*/

//STRIP001 SvxGridTabPage::SvxGridTabPage( Window* pParent, const SfxItemSet& rCoreSet) :
//STRIP001
//STRIP001  SfxTabPage( pParent, SVX_RES( RID_SVXPAGE_GRID ), rCoreSet ),
//STRIP001
//STRIP001     aFlResolution   ( this, ResId( FL_RESOLUTION ) ),
//STRIP001
//STRIP001     aFtDrawX        ( this, ResId( FT_DRAW_X ) ),
//STRIP001  aMtrFldDrawX    ( this, ResId( MTR_FLD_DRAW_X ) ),
//STRIP001
//STRIP001     aFtDrawY        ( this, ResId( FT_DRAW_Y ) ),
//STRIP001  aMtrFldDrawY    ( this, ResId( MTR_FLD_DRAW_Y ) ),
//STRIP001
//STRIP001     aFlDivision     ( this, ResId( FL_DIVISION ) ),
//STRIP001
//STRIP001     aFtDivisionX(     this, ResId( FT_DIVISION_X) ),
//STRIP001     aNumFldDivisionX( this, ResId( NUM_FLD_DIVISION_X ) ),
//STRIP001     aDivisionPointX(  this, ResId( FT_HORZ_POINTS) ),
//STRIP001
//STRIP001     aFtDivisionY(     this, ResId( FT_DIVISION_Y) ),
//STRIP001     aNumFldDivisionY( this, ResId( NUM_FLD_DIVISION_Y ) ),
//STRIP001     aDivisionPointY(  this, ResId( FT_VERT_POINTS) ),
//STRIP001
//STRIP001     aGrpDrawGrid    ( this, ResId( GRP_DRAWGRID ) ),
//STRIP001  aCbxUseGridsnap ( this, ResId( CBX_USE_GRIDSNAP ) ),
//STRIP001  aCbxSynchronize ( this, ResId( CBX_SYNCHRONIZE ) ),
//STRIP001  aCbxGridVisible ( this, ResId( CBX_GRID_VISIBLE ) ),
//STRIP001     aCbxSnapHelplines   ( this, ResId( CBX_SNAP_HELPLINES ) ),
//STRIP001     aCbxSnapBorder      ( this, ResId( CBX_SNAP_BORDER ) ),
//STRIP001     aCbxSnapFrame       ( this, ResId( CBX_SNAP_FRAME ) ),
//STRIP001     aCbxSnapPoints      ( this, ResId( CBX_SNAP_POINTS ) ),
//STRIP001     aFtSnapArea         ( this, ResId( FT_SNAP_AREA ) ),
//STRIP001     aMtrFldSnapArea     ( this, ResId( MTR_FLD_SNAP_AREA ) ),
//STRIP001     aGrpSnap            ( this, ResId( GRP_SNAP ) ),
//STRIP001     aSeparatorFL        ( this, ResId( FL_SEPARATOR ) ),
//STRIP001     aCbxOrtho           ( this, ResId( CBX_ORTHO ) ),
//STRIP001     aCbxBigOrtho        ( this, ResId( CBX_BIGORTHO ) ),
//STRIP001     aCbxRotate          ( this, ResId( CBX_ROTATE ) ),
//STRIP001     aMtrFldAngle        ( this, ResId( MTR_FLD_ANGLE ) ),
//STRIP001     aFtBezAngle         ( this, ResId( FT_BEZ_ANGLE ) ),
//STRIP001     aMtrFldBezAngle     ( this, ResId( MTR_FLD_BEZ_ANGLE ) ),
//STRIP001     aGrpOrtho           ( this, ResId( GRP_ORTHO ) ),
//STRIP001     bAttrModified( FALSE )
//STRIP001 {
//STRIP001  // diese Page braucht ExchangeSupport
//STRIP001  SetExchangeSupport();
//STRIP001
//STRIP001  FreeResource();
//STRIP001
//STRIP001     aDivisionPointY.SetText(aDivisionPointX.GetText());
//STRIP001  // Metrik einstellen
//STRIP001  FieldUnit eFUnit = GetModuleFieldUnit( &rCoreSet );
//STRIP001  long nFirst, nLast, nMin, nMax;
//STRIP001
//STRIP001  lcl_GetMinMax(aMtrFldDrawX, nFirst, nLast, nMin, nMax);
//STRIP001  SetFieldUnit( aMtrFldDrawX, eFUnit, TRUE );
//STRIP001  lcl_SetMinMax(aMtrFldDrawX, nFirst, nLast, nMin, nMax);
//STRIP001
//STRIP001  lcl_GetMinMax(aMtrFldDrawY, nFirst, nLast, nMin, nMax);
//STRIP001  SetFieldUnit( aMtrFldDrawY, eFUnit, TRUE );
//STRIP001  lcl_SetMinMax(aMtrFldDrawY, nFirst, nLast, nMin, nMax);
//STRIP001
//STRIP001
//STRIP001     aCbxRotate.SetClickHdl( LINK( this, SvxGridTabPage, ClickRotateHdl_Impl ) );
//STRIP001     Link aLink = LINK( this, SvxGridTabPage, ChangeGridsnapHdl_Impl );
//STRIP001  aCbxUseGridsnap.SetClickHdl( aLink );
//STRIP001  aCbxSynchronize.SetClickHdl( aLink );
//STRIP001  aCbxGridVisible.SetClickHdl( aLink );
//STRIP001  aMtrFldDrawX.SetModifyHdl(
//STRIP001         LINK( this, SvxGridTabPage, ChangeDrawHdl_Impl ) );
//STRIP001  aMtrFldDrawY.SetModifyHdl(
//STRIP001         LINK( this, SvxGridTabPage, ChangeDrawHdl_Impl ) );
//STRIP001     aNumFldDivisionX.SetModifyHdl(
//STRIP001         LINK( this, SvxGridTabPage, ChangeDivisionHdl_Impl ) );
//STRIP001     aNumFldDivisionY.SetModifyHdl(
//STRIP001         LINK( this, SvxGridTabPage, ChangeDivisionHdl_Impl ) );
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 SfxTabPage* SvxGridTabPage::Create( Window* pParent, const SfxItemSet& rAttrSet )
//STRIP001 {
//STRIP001  return ( new SvxGridTabPage( pParent, rAttrSet ) );
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 BOOL SvxGridTabPage::FillItemSet( SfxItemSet& rCoreSet )
//STRIP001 {
//STRIP001  if ( bAttrModified )
//STRIP001  {
//STRIP001      SvxGridItem aGridItem( SID_ATTR_GRID_OPTIONS );
//STRIP001
//STRIP001      aGridItem.bUseGridsnap  = aCbxUseGridsnap.IsChecked();
//STRIP001      aGridItem.bSynchronize  = aCbxSynchronize.IsChecked();
//STRIP001      aGridItem.bGridVisible  = aCbxGridVisible.IsChecked();
//STRIP001
//STRIP001      SfxMapUnit eUnit =
//STRIP001          rCoreSet.GetPool()->GetMetric( GetWhich( SID_ATTR_GRID_OPTIONS ) );
//STRIP001      long nX =GetCoreValue(  aMtrFldDrawX, eUnit );
//STRIP001      long nY = GetCoreValue( aMtrFldDrawY, eUnit );
//STRIP001
//STRIP001      aGridItem.nFldDrawX    = (UINT32) nX;
//STRIP001      aGridItem.nFldDrawY    = (UINT32) nY;
//STRIP001         aGridItem.nFldDivisionX = aNumFldDivisionX.GetValue();
//STRIP001         aGridItem.nFldDivisionY = aNumFldDivisionY.GetValue();
//STRIP001
//STRIP001      rCoreSet.Put( aGridItem );
//STRIP001  }
//STRIP001  return bAttrModified;
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 void SvxGridTabPage::Reset( const SfxItemSet& rSet )
//STRIP001 {
//STRIP001  const SfxPoolItem* pAttr = 0;
//STRIP001
//STRIP001  if( SFX_ITEM_SET == rSet.GetItemState( SID_ATTR_GRID_OPTIONS , FALSE,
//STRIP001                                  (const SfxPoolItem**)&pAttr ))
//STRIP001  {
//STRIP001      const SvxGridItem* pGridAttr = (SvxGridItem*)pAttr;
//STRIP001      aCbxUseGridsnap.Check( pGridAttr->bUseGridsnap == 1 );
//STRIP001      aCbxSynchronize.Check( pGridAttr->bSynchronize == 1 );
//STRIP001      aCbxGridVisible.Check( pGridAttr->bGridVisible == 1 );
//STRIP001
//STRIP001      SfxMapUnit eUnit =
//STRIP001          rSet.GetPool()->GetMetric( GetWhich( SID_ATTR_GRID_OPTIONS ) );
//STRIP001      SetMetricValue( aMtrFldDrawX , pGridAttr->nFldDrawX, eUnit );
//STRIP001      SetMetricValue( aMtrFldDrawY , pGridAttr->nFldDrawY, eUnit );
//STRIP001
//STRIP001 //       UINT32 nFineX = pGridAttr->nFldDivisionX;
//STRIP001 //       UINT32 nFineY = pGridAttr->nFldDivisionY;
//STRIP001 //      aNumFldDivisionX.SetValue( nFineX ? (pGridAttr->nFldDrawX / nFineX - 1) : 0 );
//STRIP001 //      aNumFldDivisionY.SetValue( nFineY ? (pGridAttr->nFldDrawY / nFineY - 1) : 0 );
//STRIP001         aNumFldDivisionX.SetValue( pGridAttr->nFldDivisionX );
//STRIP001         aNumFldDivisionY.SetValue( pGridAttr->nFldDivisionY );
//STRIP001  }
//STRIP001
//STRIP001  ChangeGridsnapHdl_Impl( &aCbxUseGridsnap );
//STRIP001  bAttrModified = FALSE;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 void SvxGridTabPage::ActivatePage( const SfxItemSet& rSet )
//STRIP001 {
//STRIP001  const SfxPoolItem* pAttr = NULL;
//STRIP001  if( SFX_ITEM_SET == rSet.GetItemState( SID_ATTR_GRID_OPTIONS , FALSE,
//STRIP001                                  (const SfxPoolItem**)&pAttr ))
//STRIP001  {
//STRIP001      const SvxGridItem* pGridAttr = (SvxGridItem*) pAttr;
//STRIP001      aCbxUseGridsnap.Check( pGridAttr->bUseGridsnap == 1 );
//STRIP001
//STRIP001      ChangeGridsnapHdl_Impl( &aCbxUseGridsnap );
//STRIP001  }
//STRIP001
//STRIP001  // Metrik ggfs. aendern (da TabPage im Dialog liegt,
//STRIP001  // wo die Metrik eingestellt werden kann
//STRIP001  //USHORT nWhich = GetWhich( SID_ATTR_METRIC );
//STRIP001  //if( rSet.GetItemState( GetWhich( SID_ATTR_METRIC ) ) >= SFX_ITEM_AVAILABLE )
//STRIP001  if( SFX_ITEM_SET == rSet.GetItemState( SID_ATTR_METRIC , FALSE,
//STRIP001                                  (const SfxPoolItem**)&pAttr ))
//STRIP001  {
//STRIP001      const SfxUInt16Item* pItem = (SfxUInt16Item*) pAttr;
//STRIP001
//STRIP001      FieldUnit eFUnit = (FieldUnit)(long)pItem->GetValue();
//STRIP001
//STRIP001      if( eFUnit != aMtrFldDrawX.GetUnit() )
//STRIP001      {
//STRIP001          // Metriken einstellen
//STRIP001          long nFirst, nLast, nMin, nMax;
//STRIP001          long nVal = aMtrFldDrawX.Denormalize( aMtrFldDrawX.GetValue( FUNIT_TWIP ) );
//STRIP001
//STRIP001          lcl_GetMinMax(aMtrFldDrawX, nFirst, nLast, nMin, nMax);
//STRIP001          SetFieldUnit( aMtrFldDrawX, eFUnit, TRUE );
//STRIP001          lcl_SetMinMax(aMtrFldDrawX, nFirst, nLast, nMin, nMax);
//STRIP001
//STRIP001          aMtrFldDrawX.SetValue( aMtrFldDrawX.Normalize( nVal ), FUNIT_TWIP );
//STRIP001
//STRIP001          nVal = aMtrFldDrawY.Denormalize( aMtrFldDrawY.GetValue( FUNIT_TWIP ) );
//STRIP001          lcl_GetMinMax(aMtrFldDrawY, nFirst, nLast, nMin, nMax);
//STRIP001          SetFieldUnit( aMtrFldDrawY, eFUnit, TRUE );
//STRIP001          lcl_SetMinMax(aMtrFldDrawY, nFirst, nLast, nMin, nMax);
//STRIP001          aMtrFldDrawY.SetValue( aMtrFldDrawY.Normalize( nVal ), FUNIT_TWIP );
//STRIP001
//STRIP001      }
//STRIP001  }
//STRIP001 }

// -----------------------------------------------------------------------
//STRIP001 int SvxGridTabPage::DeactivatePage( SfxItemSet* pSet )
//STRIP001 {
//STRIP001  if ( pSet )
//STRIP001      FillItemSet( *pSet );
//STRIP001  return( LEAVE_PAGE );
//STRIP001 }
//------------------------------------------------------------------------
//STRIP001 IMPL_LINK( SvxGridTabPage, ChangeDrawHdl_Impl, MetricField *, pField )
//STRIP001 {
//STRIP001  bAttrModified = TRUE;
//STRIP001  if( aCbxSynchronize.IsChecked() )
//STRIP001  {
//STRIP001         if(pField == &aMtrFldDrawX)
//STRIP001             aMtrFldDrawY.SetValue( aMtrFldDrawX.GetValue() );
//STRIP001         else
//STRIP001             aMtrFldDrawX.SetValue( aMtrFldDrawY.GetValue() );
//STRIP001     }
//STRIP001  return 0;
//STRIP001 }
//------------------------------------------------------------------------

//STRIP001 IMPL_LINK( SvxGridTabPage, ClickRotateHdl_Impl, void *, p )
//STRIP001 {
//STRIP001  if( aCbxRotate.IsChecked() )
//STRIP001      aMtrFldAngle.Enable();
//STRIP001  else
//STRIP001      aMtrFldAngle.Disable();
//STRIP001
//STRIP001  return( 0L );
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 IMPL_LINK( SvxGridTabPage, ChangeDivisionHdl_Impl, NumericField *, pField )
//STRIP001 {
//STRIP001  bAttrModified = TRUE;
//STRIP001  if( aCbxSynchronize.IsChecked() )
//STRIP001  {
//STRIP001         if(&aNumFldDivisionX == pField)
//STRIP001             aNumFldDivisionY.SetValue( aNumFldDivisionX.GetValue() );
//STRIP001         else
//STRIP001             aNumFldDivisionX.SetValue( aNumFldDivisionY.GetValue() );
//STRIP001     }
//STRIP001  return 0;
//STRIP001 }
//------------------------------------------------------------------------

//STRIP001 IMPL_LINK( SvxGridTabPage, ChangeGridsnapHdl_Impl, void *, p )
//STRIP001 {
//STRIP001  bAttrModified = TRUE;
//STRIP001  return 0;
//STRIP001 }


}
