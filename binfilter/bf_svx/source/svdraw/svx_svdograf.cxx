/*************************************************************************
 *
 *  $RCSfile: svx_svdograf.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: aw $ $Date: 2004-02-13 14:30:46 $
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

#define _ANIMATION
#define ITEMID_GRF_CROP 0

#ifndef SVX_LIGHT
#include <so3/lnkbase.hxx>
#else
#include <svtools/pathoptions.hxx>
#endif

#include <math.h>
#include <vcl/salbtype.hxx>
#include <sot/formats.hxx>
#include <so3/svstor.hxx>
#include <unotools/ucbstreamhelper.hxx>
#include <unotools/localfilehelper.hxx>
#include <svtools/style.hxx>
#include <svtools/filter.hxx>
#include <svtools/urihelper.hxx>
#include <goodies/grfmgr.hxx>
#include "linkmgr.hxx"
#include "svdxout.hxx"
#include "svdio.hxx"
#include "svdetc.hxx"
#include "svdglob.hxx"
#include "svdstr.hrc"
#include "svdpool.hxx"
#include "svdmodel.hxx"
#include "svdpage.hxx"
#include "svdmrkv.hxx"
#include "svdpagv.hxx"
#include "svdviter.hxx"
#include "svdview.hxx"
#include "impgrf.hxx"
#include "svdograf.hxx"
#include "svdogrp.hxx"
#include "xbitmap.hxx"
#include "xbtmpit.hxx"
#include "xflbmtit.hxx"
#include "svdundo.hxx"
#include "svdfmtf.hxx"
#include "sdgcpitm.hxx"

#ifndef _EEITEM_HXX
#include "eeitem.hxx"
#endif
namespace binfilter {

// -----------
// - Defines -
// -----------

#define GRAFSTREAMPOS_INVALID 0xffffffff

#ifndef SVX_LIGHT

// ------------------
// - SdrGraphicLink -
// ------------------

/*N*/ class SdrGraphicLink : public ::so3::SvBaseLink
/*N*/ {
/*N*/   SdrGrafObj*         pGrafObj;
/*N*/
/*N*/ public:
/*N*/                       SdrGraphicLink(SdrGrafObj* pObj);
/*N*/   virtual             ~SdrGraphicLink();
/*N*/
/*N*/   virtual void        Closed();
/*N*/   virtual void        DataChanged( const String& rMimeType,
/*N*/                               const ::com::sun::star::uno::Any & rValue );
/*N*/
/*N*/   BOOL                Connect() { return 0 != GetRealObject(); }
/*N*/   void                UpdateSynchron();
/*N*/ };

// -----------------------------------------------------------------------------

/*N*/ SdrGraphicLink::SdrGraphicLink(SdrGrafObj* pObj):
/*N*/   ::so3::SvBaseLink( ::so3::LINKUPDATE_ONCALL, SOT_FORMATSTR_ID_SVXB ),
/*N*/   pGrafObj(pObj)
/*N*/ {
/*N*/   SetSynchron( FALSE );
/*N*/ }

// -----------------------------------------------------------------------------

/*N*/ SdrGraphicLink::~SdrGraphicLink()
/*N*/ {
/*N*/ }

// -----------------------------------------------------------------------------

/*N*/ void SdrGraphicLink::DataChanged( const String& rMimeType,
/*N*/                               const ::com::sun::star::uno::Any & rValue )
/*N*/ {
/*N*/   SdrModel*       pModel      = pGrafObj ? pGrafObj->GetModel() : 0;
/*N*/   SvxLinkManager* pLinkManager= pModel  ? pModel->GetLinkManager() : 0;
/*N*/
/*N*/   if( pLinkManager && rValue.hasValue() )
/*N*/   {
/*N*/       pLinkManager->GetDisplayNames( this, 0, &pGrafObj->aFileName, 0, &pGrafObj->aFilterName );
/*N*/
/*N*/       Graphic aGraphic;
/*N*/       if( SvxLinkManager::GetGraphicFromAny( rMimeType, rValue, aGraphic ))
/*N*/       {
/*?*/           GraphicType eOldGraphicType = pGrafObj->GetGraphicType();  // kein Hereinswappen
/*?*/           BOOL bIsChanged = pModel->IsChanged();
/*?*/
/*?*/           pGrafObj->SetGraphic( aGraphic );
/*?*/           if( GRAPHIC_NONE != eOldGraphicType )
/*?*/               pGrafObj->SetChanged();
/*?*/           else
/*?*/               pModel->SetChanged( bIsChanged );
/*N*/       }
/*N*/       else if( SotExchange::GetFormatIdFromMimeType( rMimeType ) !=
/*N*/                   SvxLinkManager::RegisterStatusInfoId() )
/*?*/           pGrafObj->SendRepaintBroadcast();
/*N*/   }
/*N*/ }

// -----------------------------------------------------------------------------

/*N*/ void SdrGraphicLink::Closed()
/*N*/ {
/*N*/   // Die Verbindung wird aufgehoben; pLink des Objekts auf NULL setzen, da die Link-Instanz ja gerade destruiert wird.
/*N*/   pGrafObj->ForceSwapIn();
/*N*/   pGrafObj->pGraphicLink=NULL;
/*N*/   pGrafObj->ReleaseGraphicLink();
/*N*/   SvBaseLink::Closed();
/*N*/ }

// -----------------------------------------------------------------------------

/*N*/ void SdrGraphicLink::UpdateSynchron()
/*N*/ {
/*N*/   if( GetObj() )
/*N*/   {
/*N*/       String aMimeType( SotExchange::GetFormatMimeType( GetContentType() ));
/*N*/       ::com::sun::star::uno::Any aValue;
/*N*/       GetObj()->GetData( aValue, aMimeType, TRUE );
/*N*/       DataChanged( aMimeType, aValue );
/*N*/   }
/*N*/ }

#else

/*?*/ GraphicFilter* SVX_LIGHT_pGrapicFilter = NULL;
/*?*/
/*?*/ GraphicFilter* GetGrfFilter()
/*?*/ {
/*?*/   if( !SVX_LIGHT_pGrapicFilter )
/*?*/     {
/*?*/       const SvtPathOptions aPathOptions;
/*?*/
/*?*/         SVX_LIGHT_pGrapicFilter = new GraphicFilter( FALSE );
/*?*/         SVX_LIGHT_pGrapicFilter->SetFilterPath( aPathOptions.GetFilterPath() );
/*?*/     }
/*?*/
/*?*/   return SVX_LIGHT_pGrapicFilter;
/*?*/ }


#endif // SVX_LIGHT

// --------------
// - SdrGrafObj -
// --------------

/*N*/ TYPEINIT1(SdrGrafObj,SdrRectObj);

// -----------------------------------------------------------------------------

/*N*/ SdrGrafObj::SdrGrafObj():
/*N*/   bMirrored       ( FALSE ),
/*N*/   pGraphicLink    ( NULL )
/*N*/ {
/*N*/   pGraphic = new GraphicObject;
/*N*/   pGraphic->SetSwapStreamHdl( LINK( this, SdrGrafObj, ImpSwapHdl ), 20000 );
/*N*/   nGrafStreamPos = GRAFSTREAMPOS_INVALID;
/*N*/   bNoShear = TRUE;
/*N*/   bCopyToPoolOnAfterRead = FALSE;
/*N*/ }

// -----------------------------------------------------------------------------

/*?*/ SdrGrafObj::SdrGrafObj(const Graphic& rGrf, const Rectangle& rRect):
/*?*/   SdrRectObj      ( rRect ),
/*?*/   bMirrored       ( FALSE ),
/*?*/   pGraphicLink    ( NULL )
/*?*/ {
/*?*/   pGraphic = new GraphicObject( rGrf );
/*?*/   pGraphic->SetSwapStreamHdl( LINK( this, SdrGrafObj, ImpSwapHdl ), 20000 );
/*?*/   nGrafStreamPos = GRAFSTREAMPOS_INVALID;
/*?*/   bNoShear = TRUE;
/*?*/   bCopyToPoolOnAfterRead = FALSE;
/*?*/ }

// -----------------------------------------------------------------------------

/*?*/ SdrGrafObj::SdrGrafObj( const Graphic& rGrf ):
/*?*/   bMirrored       ( FALSE ),
/*?*/   pGraphicLink    ( NULL )
/*?*/ {
/*?*/   pGraphic = new GraphicObject( rGrf );
/*?*/   pGraphic->SetSwapStreamHdl( LINK( this, SdrGrafObj, ImpSwapHdl ), 20000 );
/*?*/   nGrafStreamPos = GRAFSTREAMPOS_INVALID;
/*?*/   bNoShear = TRUE;
/*?*/   bCopyToPoolOnAfterRead = FALSE;
/*?*/ }

// -----------------------------------------------------------------------------

/*N*/ SdrGrafObj::~SdrGrafObj()
/*N*/ {
/*N*/   delete pGraphic;
/*N*/   ImpLinkAbmeldung();
/*N*/ }

// -----------------------------------------------------------------------------

/*N*/ void SdrGrafObj::SetGraphicObject( const GraphicObject& rGrfObj )
/*N*/ {
/*N*/   *pGraphic = rGrfObj;
/*N*/   pGraphic->SetSwapStreamHdl( LINK( this, SdrGrafObj, ImpSwapHdl ), 20000 );
/*N*/   pGraphic->SetUserData();
/*N*/   nGrafStreamPos = GRAFSTREAMPOS_INVALID;
/*N*/   SetChanged();
/*N*/   SendRepaintBroadcast();
/*N*/ }

// -----------------------------------------------------------------------------

/*N*/ const GraphicObject& SdrGrafObj::GetGraphicObject() const
/*N*/ {
/*N*/   ForceSwapIn();
/*N*/   return *pGraphic;
/*N*/ }

// -----------------------------------------------------------------------------

/*N*/ void SdrGrafObj::SetGraphic( const Graphic& rGrf )
/*N*/ {
/*N*/   pGraphic->SetGraphic( rGrf );
/*N*/   pGraphic->SetUserData();
/*N*/   nGrafStreamPos = GRAFSTREAMPOS_INVALID;
/*N*/   SetChanged();
/*N*/   SendRepaintBroadcast();
/*N*/ }

// -----------------------------------------------------------------------------

/*N*/ const Graphic& SdrGrafObj::GetGraphic() const
/*N*/ {
/*N*/   ForceSwapIn();
/*N*/   return pGraphic->GetGraphic();
/*N*/ }

// -----------------------------------------------------------------------------

/*N*/ Graphic SdrGrafObj::GetTransformedGraphic( ULONG nTransformFlags ) const
/*N*/ {DBG_ASSERT(0, "STRIP"); Graphic          aTransGraphic( GetGraphic() );return aTransGraphic;//STRIP001
//STRIP001     // #107947# Refactored most of the code to GraphicObject, where
//STRIP001     // everybody can use e.g. the cropping functionality
//STRIP001
//STRIP001  GraphicType     eType = GetGraphicType();
//STRIP001     MapMode          aDestMap( pModel->GetScaleUnit(), Point(), pModel->GetScaleFraction(), pModel->GetScaleFraction() );
//STRIP001     const Size      aDestSize( GetLogicRect().GetSize() );
//STRIP001     const BOOL      bMirror = ( nTransformFlags & SDRGRAFOBJ_TRANSFORMATTR_MIRROR ) != 0;
//STRIP001     const BOOL      bRotate = ( ( nTransformFlags & SDRGRAFOBJ_TRANSFORMATTR_ROTATE ) != 0 ) &&
//STRIP001         ( aGeo.nDrehWink && aGeo.nDrehWink != 18000 ) && ( GRAPHIC_NONE != eType );
//STRIP001
//STRIP001     // #104115# Need cropping info earlier
//STRIP001     ( (SdrGrafObj*) this )->ImpSetAttrToGrafInfo();
//STRIP001     GraphicAttr aActAttr;
//STRIP001
//STRIP001  if( SDRGRAFOBJ_TRANSFORMATTR_NONE != nTransformFlags &&
//STRIP001         GRAPHIC_NONE != eType )
//STRIP001  {
//STRIP001         // actually transform the graphic only in this case. On the
//STRIP001         // other hand, cropping will always happen
//STRIP001         aActAttr = aGrafInfo;
//STRIP001
//STRIP001         if( bMirror )
//STRIP001      {
//STRIP001          USHORT      nMirrorCase = ( aGeo.nDrehWink == 18000 ) ? ( bMirrored ? 3 : 4 ) : ( bMirrored ? 2 : 1 );
//STRIP001          FASTBOOL    bHMirr = nMirrorCase == 2 || nMirrorCase == 4;
//STRIP001          FASTBOOL    bVMirr = nMirrorCase == 3 || nMirrorCase == 4;
//STRIP001
//STRIP001          aActAttr.SetMirrorFlags( ( bHMirr ? BMP_MIRROR_HORZ : 0 ) | ( bVMirr ? BMP_MIRROR_VERT : 0 ) );
//STRIP001      }
//STRIP001
//STRIP001      if( bRotate )
//STRIP001          aActAttr.SetRotation( aGeo.nDrehWink / 10 );
//STRIP001  }
//STRIP001
//STRIP001     // #107947# Delegate to moved code in GraphicObject
//STRIP001     return GetGraphicObject().GetTransformedGraphic( aDestSize, aDestMap, aActAttr );
/*N*/ }

// -----------------------------------------------------------------------------

/*N*/ GraphicType SdrGrafObj::GetGraphicType() const
/*N*/ {
/*N*/   return pGraphic->GetType();
/*N*/ }

// -----------------------------------------------------------------------------

//STRIP001 FASTBOOL SdrGrafObj::IsAnimated() const
//STRIP001 {
//STRIP001  return pGraphic->IsAnimated();
//STRIP001 }

// -----------------------------------------------------------------------------

//STRIP001 FASTBOOL SdrGrafObj::IsTransparent() const
//STRIP001 {
//STRIP001  return pGraphic->IsTransparent();
//STRIP001 }

// -----------------------------------------------------------------------------

//STRIP001 FASTBOOL SdrGrafObj::IsEPS() const
//STRIP001 {
//STRIP001  return pGraphic->IsEPS();
//STRIP001 }

// -----------------------------------------------------------------------------

//STRIP001 const MapMode& SdrGrafObj::GetGrafPrefMapMode() const
//STRIP001 {
//STRIP001  return pGraphic->GetPrefMapMode();
//STRIP001 }

// -----------------------------------------------------------------------------

//STRIP001 const Size& SdrGrafObj::GetGrafPrefSize() const
//STRIP001 {
//STRIP001  return pGraphic->GetPrefSize();
//STRIP001 }

// -----------------------------------------------------------------------------

/*N*/ void SdrGrafObj::SetGrafStreamURL( const String& rGraphicStreamURL )
/*N*/ {
/*N*/   if( !rGraphicStreamURL.Len() )
/*N*/   {
/*N*/       pGraphic->SetUserData();
/*N*/       nGrafStreamPos = GRAFSTREAMPOS_INVALID;
/*N*/   }
/*N*/   else if( pModel->IsSwapGraphics() )
/*N*/   {
/*N*/       pGraphic->SetUserData( rGraphicStreamURL );
/*N*/       nGrafStreamPos = GRAFSTREAMPOS_INVALID;
/*N*/
/*N*/       // set state of graphic object to 'swapped out'
/*N*/       if( pGraphic->GetType() == GRAPHIC_NONE )
/*?*/           pGraphic->SetSwapState();
/*N*/   }
/*N*/ }

// -----------------------------------------------------------------------------

/*N*/ String SdrGrafObj::GetGrafStreamURL() const
/*N*/ {DBG_ASSERT(0, "STRIP"); String aString; return aString;//STRIP001
//STRIP001  return pGraphic->GetUserData();
/*N*/ }

// -----------------------------------------------------------------------------

//STRIP001 void SdrGrafObj::SetFileName(const String& rFileName)
//STRIP001 {
//STRIP001  aFileName = rFileName;
//STRIP001  SetChanged();
//STRIP001 }

// -----------------------------------------------------------------------------

//STRIP001 void SdrGrafObj::SetFilterName(const String& rFilterName)
//STRIP001 {
//STRIP001  aFilterName = rFilterName;
//STRIP001  SetChanged();
//STRIP001 }

// -----------------------------------------------------------------------------

//STRIP001 FASTBOOL SdrGrafObj::HasSetName() const
//STRIP001 {
//STRIP001  return TRUE;
//STRIP001 }

// -----------------------------------------------------------------------------

/*N*/ void SdrGrafObj::SetName(const XubString& rStr)
/*N*/ {
/*N*/   aName = rStr;
/*N*/   SetChanged();
/*N*/ }

// -----------------------------------------------------------------------------

/*N*/ XubString SdrGrafObj::GetName() const
/*N*/ {
/*N*/   return aName;
/*N*/ }

// -----------------------------------------------------------------------------

/*N*/ void SdrGrafObj::ForceSwapIn() const
/*N*/ {
/*N*/   pGraphic->FireSwapInRequest();
/*N*/
/*N*/   if( pGraphic->IsSwappedOut() ||
/*N*/       ( pGraphic->GetType() == GRAPHIC_NONE ) ||
/*N*/       ( pGraphic->GetType() == GRAPHIC_DEFAULT ) )
/*N*/   {
/*N*/       Graphic aDefaultGraphic;
/*N*/       aDefaultGraphic.SetDefaultType();
/*N*/       pGraphic->SetGraphic( aDefaultGraphic );
/*N*/   }
/*N*/ }

// -----------------------------------------------------------------------------

/*N*/ void SdrGrafObj::ForceSwapOut() const
/*N*/ {
/*N*/   pGraphic->FireSwapOutRequest();
/*N*/ }

// -----------------------------------------------------------------------------

/*N*/ void SdrGrafObj::ImpLinkAnmeldung()
/*N*/ {
/*N*/ #ifndef SVX_LIGHT
/*N*/
/*N*/   SvxLinkManager* pLinkManager = pModel != NULL ? pModel->GetLinkManager() : NULL;
/*N*/
/*N*/   if( pLinkManager != NULL && pGraphicLink == NULL )
/*N*/   {
/*N*/       if( aFileName.Len() )
/*N*/       {
/*N*/           pGraphicLink = new SdrGraphicLink( this );
/*N*/           pLinkManager->InsertFileLink( *pGraphicLink, OBJECT_CLIENT_GRF, aFileName, ( aFilterName.Len() ? &aFilterName : NULL ), NULL );
/*N*/           pGraphicLink->Connect();
/*N*/       }
/*N*/   }
/*N*/
/*N*/ #endif // SVX_LIGHT
/*N*/ }

// -----------------------------------------------------------------------------

/*N*/ void SdrGrafObj::ImpLinkAbmeldung()
/*N*/ {
/*N*/ #ifndef SVX_LIGHT
/*N*/
/*N*/   SvxLinkManager* pLinkManager = pModel != NULL ? pModel->GetLinkManager() : NULL;
/*N*/
/*N*/   if( pLinkManager != NULL && pGraphicLink!=NULL)
/*N*/   {
/*?*/       // Bei Remove wird *pGraphicLink implizit deleted
/*?*/       pLinkManager->Remove( pGraphicLink );
/*?*/       pGraphicLink=NULL;
/*N*/   }
/*N*/
/*N*/ #endif // SVX_LIGHT
/*N*/ }

// -----------------------------------------------------------------------------

/*N*/ void SdrGrafObj::SetGraphicLink( const String& rFileName, const String& rFilterName )
/*N*/ {
/*N*/   ImpLinkAbmeldung();
/*N*/   aFileName = rFileName;
/*N*/   aFilterName = rFilterName;
/*N*/   ImpLinkAnmeldung();
/*N*/   pGraphic->SetUserData();
/*N*/
/*N*/     // #92205# A linked graphic is per definition swapped out (has to be loaded)
/*N*/     pGraphic->SetSwapState();
/*N*/ }

// -----------------------------------------------------------------------------

/*N*/ void SdrGrafObj::ReleaseGraphicLink()
/*N*/ {
/*N*/   ImpLinkAbmeldung();
/*N*/   aFileName = String();
/*N*/   aFilterName = String();
/*N*/ }

// -----------------------------------------------------------------------------

//STRIP001 void SdrGrafObj::TakeObjInfo(SdrObjTransformInfoRec& rInfo) const
//STRIP001 {
//STRIP001  FASTBOOL bTrans = pGraphic->IsTransparent();
//STRIP001  FASTBOOL bAnim = pGraphic->IsAnimated();
//STRIP001  FASTBOOL bNoPresGrf = ( pGraphic->GetType() != GRAPHIC_NONE ) && !bEmptyPresObj;
//STRIP001
//STRIP001  rInfo.bResizeFreeAllowed = aGeo.nDrehWink % 9000 == 0 ||
//STRIP001                             aGeo.nDrehWink % 18000 == 0 ||
//STRIP001                             aGeo.nDrehWink % 27000 == 0;
//STRIP001
//STRIP001  rInfo.bResizePropAllowed = TRUE;
//STRIP001  rInfo.bRotateFreeAllowed = bNoPresGrf && !bAnim;
//STRIP001  rInfo.bRotate90Allowed = bNoPresGrf && !bAnim;
//STRIP001  rInfo.bMirrorFreeAllowed = bNoPresGrf && !bAnim;
//STRIP001  rInfo.bMirror45Allowed = bNoPresGrf && !bAnim;
//STRIP001  rInfo.bMirror90Allowed = !bEmptyPresObj;
//STRIP001  rInfo.bTransparenceAllowed = FALSE;
//STRIP001  rInfo.bGradientAllowed = FALSE;
//STRIP001  rInfo.bShearAllowed = FALSE;
//STRIP001  rInfo.bEdgeRadiusAllowed=FALSE;
//STRIP001  rInfo.bCanConvToPath = FALSE;
//STRIP001  rInfo.bCanConvToPathLineToArea = FALSE;
//STRIP001  rInfo.bCanConvToPolyLineToArea = FALSE;
//STRIP001  rInfo.bCanConvToPoly = !IsEPS();
//STRIP001  rInfo.bCanConvToContour = (rInfo.bCanConvToPoly || LineGeometryUsageIsNecessary());
//STRIP001 }

// -----------------------------------------------------------------------------

/*N*/ UINT16 SdrGrafObj::GetObjIdentifier() const
/*N*/ {
/*N*/   return UINT16( OBJ_GRAF );
/*N*/ }

// -----------------------------------------------------------------------------

/*N*/ sal_Bool SdrGrafObj::ImpUpdateGraphicLink() const
/*N*/ {
/*N*/     sal_Bool  bRet = sal_False;
/*N*/
/*N*/ #ifndef SVX_LIGHT
/*N*/     if( pGraphicLink )
/*N*/     {
/*N*/         BOOL bIsChanged = pModel->IsChanged();
/*N*/         pGraphicLink->UpdateSynchron();
/*N*/         pModel->SetChanged( bIsChanged );
/*N*/
/*N*/         bRet = sal_True;
/*N*/     }
/*N*/ #else
/*N*/     if( aFileName.Len() )
/*N*/     {
/*N*/         // #92205# Load linked graphics for player
/*N*/         SvStream* pIStm = ::utl::UcbStreamHelper::CreateStream( aFileName, STREAM_READ | STREAM_SHARE_DENYNONE );
/*N*/
/*N*/         if( pIStm )
/*N*/         {
/*N*/             Graphic           aGraphic;
/*N*/             GraphicFilter*    pFilter = GetGrfFilter();
/*N*/             USHORT            nError = pFilter->ImportGraphic( aGraphic, aFileName, *pIStm );
/*N*/
/*N*/             pGraphic->SetGraphic( aGraphic );
/*N*/
/*N*/             delete pIStm;
/*N*/         }
/*N*/
/*N*/         bRet = sal_True;
/*N*/     }
/*N*/ #endif
/*N*/
/*N*/     return bRet;
/*N*/ }

// -----------------------------------------------------------------------------

// Liefert FALSE, wenn die Pres-Bitmap zu gross ist
//STRIP001 FASTBOOL SdrGrafObj::ImpPaintEmptyPres( OutputDevice* pOutDev ) const
//STRIP001 {
//STRIP001  const MapMode   aDstMapMode( pOutDev->GetMapMode().GetMapUnit() );
//STRIP001  Point           aPos( aRect.Center() );
//STRIP001  Size            aSize;
//STRIP001     FASTBOOL        bRet;
//STRIP001
//STRIP001  if( pGraphic->GetPrefMapMode().GetMapUnit() == MAP_PIXEL )
//STRIP001      aSize = pOutDev->PixelToLogic( pGraphic->GetPrefSize(), aDstMapMode );
//STRIP001  else
//STRIP001      aSize = pOutDev->LogicToLogic( pGraphic->GetPrefSize(), pGraphic->GetPrefMapMode(), aDstMapMode );
//STRIP001
//STRIP001  aPos.X() -= ( aSize.Width() >> 1 );
//STRIP001  aPos.Y() -= ( aSize.Height() >> 1 );
//STRIP001
//STRIP001     if( aPos.X() >= aRect.Left() && aPos.Y() >= aRect.Top() )
//STRIP001  {
//STRIP001      const Graphic& rGraphic = pGraphic->GetGraphic();
//STRIP001
//STRIP001      if( pGraphic->GetType() == GRAPHIC_BITMAP )
//STRIP001          pGraphic->Draw( pOutDev, aPos, aSize, NULL );
//STRIP001      else
//STRIP001      {
//STRIP001          const ULONG nOldDrawMode = pOutDev->GetDrawMode();
//STRIP001
//STRIP001          if( ( nOldDrawMode & DRAWMODE_GRAYBITMAP ) != 0 )
//STRIP001          {
//STRIP001              // Falls Modus GRAYBITMAP, wollen wir auch Mtf's als Graustufen darstellen
//STRIP001              ULONG nNewDrawMode = nOldDrawMode;
//STRIP001              nNewDrawMode &= ~( DRAWMODE_BLACKLINE | DRAWMODE_BLACKFILL | DRAWMODE_WHITEFILL | DRAWMODE_NOFILL );
//STRIP001              pOutDev->SetDrawMode( nNewDrawMode |= DRAWMODE_GRAYLINE | DRAWMODE_GRAYFILL  );
//STRIP001          }
//STRIP001
//STRIP001          rGraphic.Draw( pOutDev, aPos, aSize );
//STRIP001          pOutDev->SetDrawMode( nOldDrawMode );
//STRIP001      }
//STRIP001
//STRIP001      bRet = TRUE;
//STRIP001  }
//STRIP001  else
//STRIP001      bRet = FALSE;
//STRIP001
//STRIP001  return bRet;
//STRIP001 }

// -----------------------------------------------------------------------------

/*N*/ void SdrGrafObj::ImpPaintReplacement(OutputDevice* pOutDev, const XubString& rText, const Bitmap* pBmp, FASTBOOL bFill) const
/*N*/ {
/*N*/     Size aPixelSize( 1, 1 );
/*N*/     Size aBmpSize;
/*N*/
/*N*/     aPixelSize = Application::GetDefaultDevice()->PixelToLogic( aPixelSize, pOutDev->GetMapMode() );
/*N*/
/*N*/   if( bFill )
/*N*/   {
/*?*/       pOutDev->SetLineColor();
/*?*/       pOutDev->SetFillColor( COL_LIGHTGRAY );
/*N*/   }
/*N*/
/*N*/   Rectangle   aRect1( aRect );
/*N*/   Rectangle   aRect2( aRect1 );
/*N*/   Rectangle   aTextRect( aRect1 );
/*N*/   Point       aTopLeft( aRect1.TopLeft() );
/*N*/   Point       aBmpPos( aTopLeft );
/*N*/
/*N*/     aRect2.Left() += aPixelSize.Width();
/*N*/     aRect2.Top() += aPixelSize.Height();
/*N*/     aRect2.Right() -= aPixelSize.Width();
/*N*/     aRect2.Bottom() -= aPixelSize.Height();
/*N*/
/*N*/   if( pBmp != NULL )
/*N*/   {
/*N*/       aBmpSize = Size( Application::GetDefaultDevice()->PixelToLogic( pBmp->GetSizePixel(), pOutDev->GetMapMode() ) );
/*N*/
/*N*/       long        nRectWdt = aTextRect.Right() - aTextRect.Left();
/*N*/       long        nRectHgt = aTextRect.Bottom() - aTextRect.Top();
/*N*/       long        nBmpWdt = aBmpSize.Width();
/*N*/       long        nBmpHgt = aBmpSize.Height();
/*N*/       long        nMinWdt = nBmpWdt;
/*N*/       long        nMinHgt = nBmpHgt;
/*N*/       BOOL        bText = rText.Len() > 0;
/*N*/
/*N*/       if( bText )
/*N*/       {
/*N*/           nMinWdt= 2 * nBmpWdt + 5 * aPixelSize.Width();
/*N*/           nMinHgt= 2 * nBmpHgt + 5 * aPixelSize.Height();
/*N*/       }
/*N*/
/*N*/       if( nRectWdt < nMinWdt || nRectHgt < nMinHgt )
/*N*/           pBmp=NULL;
/*N*/       else
/*N*/       {
/*N*/           aTextRect.Left() += nBmpWdt;
/*N*/
/*N*/           if( bText )
/*N*/               aTextRect.Left() += 5 * aPixelSize.Width();
/*N*/       }
/*N*/
/*N*/       aBmpPos.X() += 2 * aPixelSize.Width();
/*N*/       aBmpPos.Y() += 2 * aPixelSize.Height();
/*N*/
/*N*/       if( aGeo.nDrehWink != 0 )
/*N*/       {
/*N*/           Point   aRef( aBmpPos.X() - aBmpSize.Width() / 2 + 2 * aPixelSize.Width(),
/*N*/                         aBmpPos.Y() - aBmpSize.Height() / 2 + 2 * aPixelSize.Height() );
/*N*/           double  nSin = sin( aGeo.nDrehWink * nPi180 );
/*N*/           double  nCos = cos( aGeo.nDrehWink * nPi180 );
/*N*/
/*N*/           RotatePoint( aBmpPos, aRef, nSin, nCos );
/*N*/       }
/*N*/   }
/*N*/
/*N*/   if( aGeo.nDrehWink == 0 && aGeo.nShearWink == 0 )
/*N*/   {
/*N*/       const StyleSettings& rStyleSettings = pOutDev->GetSettings().GetStyleSettings();
/*N*/
/*N*/       if( bFill )
/*N*/           pOutDev->DrawRect( aRect );
/*N*/
/*N*/       if( pBmp!=NULL )
/*N*/           pOutDev->DrawBitmap( aBmpPos, aBmpSize, *pBmp );
/*N*/
/*N*/       pOutDev->SetFillColor();
/*N*/       pOutDev->SetLineColor( rStyleSettings.GetShadowColor() );
/*N*/       pOutDev->DrawLine( aRect1.TopLeft(), aRect1.TopRight() );
/*N*/       pOutDev->DrawLine( aRect1.TopLeft(), aRect1.BottomLeft() );
/*N*/
/*N*/       pOutDev->SetLineColor( rStyleSettings.GetLightColor() );
/*N*/       pOutDev->DrawLine( aRect1.TopRight(), aRect1.BottomRight() );
/*N*/       pOutDev->DrawLine( aRect1.BottomLeft(), aRect1.BottomRight() );
/*N*/
/*N*/       pOutDev->SetLineColor( rStyleSettings.GetLightColor() );
/*N*/       pOutDev->DrawLine( aRect2.TopLeft(), aRect2.TopRight() );
/*N*/       pOutDev->DrawLine( aRect2.TopLeft(), aRect2.BottomLeft() );
/*N*/
/*N*/       pOutDev->SetLineColor( rStyleSettings.GetShadowColor() );
/*N*/       pOutDev->DrawLine( aRect2.TopRight(), aRect2.BottomRight() );
/*N*/       pOutDev->DrawLine( aRect2.BottomLeft(), aRect2.BottomRight() );
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       Polygon aPoly1( Rect2Poly( aRect1, aGeo ) );
/*N*/       Polygon aPoly2(5);
/*N*/
/*N*/       aPoly2[0] = aRect2.TopLeft();
/*N*/       aPoly2[1] = aRect2.TopRight();
/*N*/       aPoly2[2] = aRect2.BottomRight();
/*N*/       aPoly2[3] = aRect2.BottomLeft();
/*N*/       aPoly2[4] = aRect2.TopLeft();
/*N*/
/*N*/       if( aGeo.nShearWink != 0 )
/*?*/           ShearPoly( aPoly2, aTopLeft, aGeo.nTan );
/*N*/
/*N*/       if( aGeo.nDrehWink != 0 )
/*N*/           RotatePoly( aPoly2, aTopLeft, aGeo.nSin, aGeo.nCos );
/*N*/
/*N*/       if( bFill )
/*?*/           pOutDev->DrawPolygon( aPoly1 );
/*N*/
/*N*/       if( pBmp != NULL )
/*N*/           pOutDev->DrawBitmap( aBmpPos, aBmpSize, *pBmp );
/*N*/
/*N*/       pOutDev->SetFillColor();
/*N*/
/*N*/       const StyleSettings&    rStyleSettings = pOutDev->GetSettings().GetStyleSettings();
/*N*/       Color                   a3DLightColor( rStyleSettings.GetLightColor() );
/*N*/       Color                   a3DShadowColor( rStyleSettings.GetShadowColor() );
/*N*/       long                    nHWink=NormAngle360( aGeo.nDrehWink );
/*N*/       long                    nVWink=NormAngle360( aGeo.nDrehWink-aGeo.nShearWink );
/*N*/       FASTBOOL                bHorzChg=nHWink>13500 && nHWink<=31500;
/*N*/       FASTBOOL                bVertChg=nVWink>4500 && nVWink<=22500;
/*N*/
/*N*/       pOutDev->SetLineColor( bHorzChg ? a3DShadowColor : a3DLightColor);
/*N*/       pOutDev->DrawLine( aPoly2[0], aPoly2[1] );
/*N*/
/*N*/       pOutDev->SetLineColor( bHorzChg ? a3DLightColor  : a3DShadowColor);
/*N*/       pOutDev->DrawLine( aPoly2[2], aPoly2[3] );
/*N*/
/*N*/       pOutDev->SetLineColor( bVertChg ? a3DLightColor  : a3DShadowColor);
/*N*/       pOutDev->DrawLine( aPoly2[1], aPoly2[2] );
/*N*/
/*N*/       pOutDev->SetLineColor( bVertChg ? a3DShadowColor : a3DLightColor);
/*N*/       pOutDev->DrawLine( aPoly2[3], aPoly2[4] );
/*N*/
/*N*/       pOutDev->SetLineColor( bHorzChg ? a3DLightColor  : a3DShadowColor);
/*N*/       pOutDev->DrawLine( aPoly1[0], aPoly1[1] );
/*N*/
/*N*/       pOutDev->SetLineColor( bHorzChg ? a3DShadowColor : a3DLightColor);
/*N*/       pOutDev->DrawLine( aPoly1[2], aPoly1[3] );
/*N*/
/*N*/       pOutDev->SetLineColor( bVertChg ? a3DShadowColor : a3DLightColor);
/*N*/       pOutDev->DrawLine( aPoly1[1], aPoly1[2] );
/*N*/
/*N*/       pOutDev->SetLineColor( bVertChg ? a3DLightColor  : a3DShadowColor);
/*N*/       pOutDev->DrawLine( aPoly1[3], aPoly1[4] );
/*N*/   }
/*N*/
/*N*/   XubString aNam( rText );
/*N*/
/*N*/   if( aNam.Len() )
/*N*/   {
/*?*/       Size aOutSize( aTextRect.GetWidth() - 6 * aPixelSize.Width(),
/*?*/                      aTextRect.GetHeight() - 6 * aPixelSize.Height() );
/*?*/
/*?*/       if( aOutSize.Width() >= ( 4 * aPixelSize.Width() ) ||
/*?*/           aOutSize.Height() >=  ( 4 * aPixelSize.Height() ) )
/*?*/       {
/*?*/           Point   aOutPos( aTextRect.Left() + 3 * aPixelSize.Width(),
/*?*/                            aTextRect.Top() + 3 * aPixelSize.Height() );
/*?*/           long    nMaxOutY = aOutPos.Y() + aOutSize.Height();
/*?*/           Font    aFontMerk( pOutDev->GetFont() );
/*?*/           Font    aFont( OutputDevice::GetDefaultFont( DEFAULTFONT_SANS_UNICODE, LANGUAGE_SYSTEM, DEFAULTFONT_FLAGS_ONLYONE ) );
/*?*/
/*?*/           aFont.SetColor( COL_LIGHTRED );
/*?*/           aFont.SetTransparent( TRUE );
/*?*/           aFont.SetOrientation( USHORT( NormAngle360( aGeo.nDrehWink ) / 10 ) );
/*?*/
/*?*/           if( IsLinkedGraphic() )
/*?*/               aFont.SetUnderline( UNDERLINE_SINGLE );
/*?*/
/*?*/           Size aFontSize( 0, ( aGeo.nDrehWink % 9000 == 0 ? 12 : 14 ) * aPixelSize.Height() );
/*?*/
/*?*/           if( aFontSize.Height() > aOutSize.Height() )
/*?*/               aFontSize.Height() = aOutSize.Height();
/*?*/
/*?*/           aFont.SetSize( aFontSize );
/*?*/           pOutDev->SetFont( aFont );
/*?*/           String aOutStr( aNam );
/*?*/
/*?*/           while( aOutStr.Len() && aOutPos.Y() <= nMaxOutY )
/*?*/           {
/*?*/               String  aStr1( aOutStr );
/*?*/               INT32   nTextWidth = pOutDev->GetTextWidth( aStr1 );
/*?*/               INT32   nTextHeight = pOutDev->GetTextHeight();
/*?*/
/*?*/               while( aStr1.Len() && nTextWidth > aOutSize.Width() )
/*?*/               {
/*?*/                   aStr1.Erase( aStr1.Len() - 1 );
/*?*/                   nTextWidth = pOutDev->GetTextWidth( aStr1 );
/*?*/                   nTextHeight = pOutDev->GetTextHeight();
/*?*/               }
/*?*/
/*?*/               Point aPos( aOutPos );
/*?*/               aOutPos.Y() += nTextHeight;
/*?*/
/*?*/               if( aOutPos.Y() <= nMaxOutY )
/*?*/               {
/*?*/                   if( aGeo.nShearWink != 0 )
/*?*/                       ShearPoint( aPos, aTopLeft, aGeo.nTan );
/*?*/
/*?*/                   if( aGeo.nDrehWink != 0 )
/*?*/                       RotatePoint( aPos, aTopLeft, aGeo.nSin, aGeo.nCos );
/*?*/
/*?*/                   pOutDev->DrawText( aPos, aStr1 );
/*?*/                   aOutStr.Erase( 0, aStr1.Len() );
/*?*/               }
/*?*/           }
/*?*/
/*?*/           pOutDev->SetFont( aFontMerk );
/*N*/       }
/*N*/   }
/*N*/ }

// -----------------------------------------------------------------------------

/*N*/ FASTBOOL SdrGrafObj::Paint( ExtOutputDevice& rOut, const SdrPaintInfoRec& rInfoRec ) const
/*N*/ {
/*N*/   // Hidden objects on masterpages, draw nothing
/*N*/   if( ( ( rInfoRec.nPaintMode & SDRPAINTMODE_MASTERPAGE ) && bNotVisibleAsMaster ) ||
/*N*/       ( ( OUTDEV_PRINTER == rOut.GetOutDev()->GetOutDevType() ) && bEmptyPresObj ) )
/*N*/   {
/*?*/       return TRUE;
/*N*/   }
/*N*/
/*N*/   FASTBOOL        bDraft = ( 0 != ( rInfoRec.nPaintMode & SDRPAINTMODE_DRAFTGRAF ) );
/*N*/   FASTBOOL        bSwappedOut = pGraphic->IsSwappedOut() || ( pGraphic->GetType() == GRAPHIC_NONE );
/*N*/   FASTBOOL        bLoading = FALSE;
/*N*/   OutputDevice*   pOutDev = rOut.GetOutDev();
/*N*/   GDIMetaFile*    pRecMetaFile = pOutDev->GetConnectMetaFile();
/*N*/   FASTBOOL        bMtfRecording = ( pRecMetaFile && pRecMetaFile->IsRecord() && !pRecMetaFile->IsPause() );
/*N*/   const SdrView*  pView = ( rInfoRec.pPV ? &rInfoRec.pPV->GetView() : NULL );
/*N*/
/*N*/   if( bSwappedOut && !bDraft )
/*N*/   {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/        if( !ImpUpdateGraphicLink() )
//STRIP001 /*?*/        {
//STRIP001 /*?*/            if( ( OUTDEV_WINDOW == pOutDev->GetOutDevType() ) && !bMtfRecording && pView && pView->IsSwapAsynchron() )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                ( (SdrView*) pView )->ImpAddAsyncObj( this, pOutDev );
//STRIP001 /*?*/                bLoading = TRUE;
//STRIP001 /*?*/            }
//STRIP001 /*?*/            else
//STRIP001 /*?*/                ForceSwapIn();
//STRIP001 /*?*/        }
/*N*/   }

/*N*/   if( pGraphic->IsSwappedOut() || ( pGraphic->GetType() == GRAPHIC_NONE ) || ( pGraphic->GetType() == GRAPHIC_DEFAULT ) )
/*?*/       bDraft=TRUE;
/*N*/
/*N*/   long          nDrehWink = aGeo.nDrehWink, nShearWink = aGeo.nShearWink;
/*N*/   FASTBOOL      bRotate = ( nDrehWink != 0 && nDrehWink != 18000 );
/*N*/   FASTBOOL      bShear = ( nShearWink != 0 );
/*N*/   FASTBOOL      bRota180 = nDrehWink == 18000;
/*N*/   USHORT        nMirrorCase = ( bRota180 ? ( bMirrored ? 3 : 4 ) : ( bMirrored ? 2 : 1 ) );   //  4 | 3   H&V gespiegelt | nur Vertikal
/*N*/   FASTBOOL      bHMirr = ( ( 2 == nMirrorCase ) || ( 4 == nMirrorCase ) );                    // ---+---  ---------------+-----------------
/*N*/   FASTBOOL      bVMirr = ( ( 3 == nMirrorCase ) || ( 4 == nMirrorCase ) );                    //  2 | 1   nur Horizontal | nicht gespiegelt
/*N*/
/*N*/   if( !bEmptyPresObj && !bDraft )
/*N*/   {
/*?*/       Point       aLogPos( aRect.TopLeft() );
/*?*/       Size        aLogSize( pOutDev->PixelToLogic( pOutDev->LogicToPixel( aRect ).GetSize() ) );
/*?*/       GraphicAttr aAttr( aGrafInfo );
/*?*/       const ULONG nGraphicManagerDrawMode = ( pView ? pView->GetGraphicManagerDrawMode() : GRFMGR_DRAW_STANDARD );
/*?*/
/*?*/       aAttr.SetMirrorFlags( ( bHMirr ? BMP_MIRROR_HORZ : 0 ) | ( bVMirr ? BMP_MIRROR_VERT : 0 ) );
/*?*/
/*?*/       if( bRota180 )
/*?*/       {
/*?*/           aLogPos.X() -= ( aLogSize.Width() - 1L );
/*?*/           aLogPos.Y() -= ( aLogSize.Height() - 1L );
/*?*/       }
/*?*/
/*?*/         bool bDidPaint( false );
/*?*/
/*?*/       if( pGraphic->GetType() == GRAPHIC_BITMAP )
/*?*/       {
/*?*/           if( pGraphic->IsAnimated() )
/*?*/           {
/*?*/               SdrAnimationMode    eAnimMode = SDR_ANIMATION_ANIMATE;
/*?*/               FASTBOOL            bEnable = TRUE;
/*?*/
/*?*/               if( pView )
/*?*/               {
/*?*/                   eAnimMode= pView->GetAnimationMode();
/*?*/                   bEnable = ( eAnimMode != SDR_ANIMATION_DISABLE );
/*?*/
/*?*/                   if( bEnable )
/*?*/                   {{DBG_ASSERT(0, "STRIP"); }//STRIP001
//STRIP001 /*?*/                        const SvtAccessibilityOptions& rOpt = const_cast< SdrView* >( pView )->getAccessibilityOptions();
//STRIP001 /*?*/                        sal_Bool bIsAllowedAnimatedGraphics = rOpt.GetIsAllowAnimatedGraphics();
//STRIP001 /*?*/
//STRIP001 /*?*/                        if( !bIsAllowedAnimatedGraphics )
//STRIP001 /*?*/                        {
//STRIP001 /*?*/                            pGraphic->StopAnimation();
//STRIP001 /*?*/                            pGraphic->Draw( pOutDev, aLogPos, aLogSize, &aAttr, nGraphicManagerDrawMode );
//STRIP001 /*?*/                            bEnable = FALSE;
//STRIP001 /*?*/                             bDidPaint = true;
//STRIP001 /*?*/                        }
/*?*/                   }
/*?*/               }
/*?*/
/*?*/               if( bEnable )
/*?*/               {
/*?*/                   if( eAnimMode == SDR_ANIMATION_ANIMATE )
/*?*/                   {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/                        pGraphic->SetAnimationNotifyHdl( LINK( this, SdrGrafObj, ImpAnimationHdl ) );
//STRIP001 /*?*/                        pGraphic->StartAnimation( pOutDev, aLogPos, aLogSize, 0, &aAttr );
/*?*/                   }
/*?*/                   else if( eAnimMode == SDR_ANIMATION_DONT_ANIMATE )
/*?*/                       pGraphic->Draw( pOutDev, aLogPos, aLogSize, &aAttr, nGraphicManagerDrawMode );
/*?*/
/*?*/                     bDidPaint = true;
/*?*/               }
/*?*/           }
/*?*/           else
/*?*/           {
/*?*/               if( bRotate && !bRota180 )
/*?*/                   aAttr.SetRotation( nDrehWink / 10 );
/*?*/
/*?*/               pGraphic->Draw( pOutDev, aLogPos, aLogSize, &aAttr, nGraphicManagerDrawMode );
/*?*/                 bDidPaint = true;
/*?*/           }
/*?*/       }
/*?*/       else
/*?*/       {
/*?*/           // MetaFiles
/*?*/           const ULONG nOldDrawMode = pOutDev->GetDrawMode();
/*?*/
/*?*/           // Falls Modus GRAYBITMAP, wollen wir auch Mtf's als Graustufen darstellen
/*?*/           if( nOldDrawMode & DRAWMODE_GRAYBITMAP )
/*?*/           {
/*?*/               ULONG nNewDrawMode = nOldDrawMode;
/*?*/               nNewDrawMode &= ~( DRAWMODE_BLACKLINE | DRAWMODE_BLACKFILL | DRAWMODE_WHITEFILL | DRAWMODE_NOFILL );
/*?*/               pOutDev->SetDrawMode( nNewDrawMode |= DRAWMODE_GRAYLINE | DRAWMODE_GRAYFILL  );
/*?*/           }
/*?*/
/*?*/           if( bRotate && !bRota180 )
/*?*/               aAttr.SetRotation( nDrehWink / 10 );
/*?*/
/*?*/           pGraphic->Draw( pOutDev, aLogPos, aLogSize, &aAttr, nGraphicManagerDrawMode );
/*?*/           pOutDev->SetDrawMode( nOldDrawMode );
/*?*/
/*?*/             bDidPaint = true;
/*?*/       }
/*?*/
/*?*/         // #110290# Remove the SdrGraphObj from the list of objects to be removed on
/*?*/         // page switch. This is permissible, as the Draw above reenabled the swapout
/*?*/         // timer.
/*?*/         // #110573# Occasionally, the view is NULL (e.g. previews in impress and calc)
/*?*/         if( bDidPaint && pView )
/*?*/             ( (SdrView*) pView )->ImpAsyncPaintDone( this );
/*N*/   }

    // auch GRAPHIC_NONE oder SwappedOut( AsyncSwap )
/*N*/   if( ( bEmptyPresObj || bDraft ) && ( !bDraft || !( rInfoRec.nPaintMode & SDRPAINTMODE_HIDEDRAFTGRAF ) ) )
/*N*/   {
/*N*/       XubString   aText;
/*N*/       Bitmap*     pBmp = NULL;
/*N*/       FASTBOOL    bFill = FALSE;
/*N*/
/*N*/       if( bEmptyPresObj )
/*?*/           {DBG_ASSERT(0, "STRIP"); }//STRIP001 bFill = !ImpPaintEmptyPres( pOutDev );
/*N*/
/*N*/       // und nun noch einen grauen Rahmen drum herum, Text rein, ...
/*N*/       if( !bEmptyPresObj )
/*N*/       {
/*N*/           aText = aFileName;
/*N*/
/*N*/           if(!aText.Len())
/*N*/           {
/*N*/               aText = aName;
/*N*/
/*N*/               if( bLoading )
/*N*/               {
/*?*/                   aText.AppendAscii(" ...");
/*?*/                   //FASTBOOL bNoName=aText.Len()==0;
/*?*/                   //if (!bNoName) aText.Insert(' ',0);
/*?*/                   //else aText.Insert("...",0);
/*?*/                   //aText.Insert("Loading",0);
/*N*/               }
/*N*/           }
/*N*/
/*N*/ #ifndef SVX_LIGHT
/*N*/           pBmp = new Bitmap( ResId ( BMAP_GrafikEi, ImpGetResMgr() ) );
/*N*/ #endif
/*N*/       }
/*N*/
/*N*/       ImpPaintReplacement( pOutDev, aText, pBmp, bFill );
/*N*/       delete pBmp;
/*N*/   }
/*N*/
/*N*/   if( OUTDEV_PRINTER == pOutDev->GetOutDevType() )
/*?*/       ForceSwapOut();
/*N*/
/*N*/   return( HasText() ? SdrTextObj::Paint( rOut, rInfoRec ) : TRUE );
/*N*/ }

// -----------------------------------------------------------------------------

/*N*/ SdrObject* SdrGrafObj::CheckHit(const Point& rPnt, USHORT nTol, const SetOfByte* pVisiLayer) const
/*N*/ {
/*N*/   return ImpCheckHit( rPnt, nTol, pVisiLayer, TRUE );
/*N*/ }

// -----------------------------------------------------------------------------

//STRIP001 void SdrGrafObj::TakeObjNameSingul(XubString& rName) const
//STRIP001 {
//STRIP001  switch( pGraphic->GetType() )
//STRIP001  {
//STRIP001      case GRAPHIC_BITMAP:
//STRIP001         {
//STRIP001             const USHORT nId = ( ( IsTransparent() || ( (const SdrGrafTransparenceItem&) GetItem( SDRATTR_GRAFTRANSPARENCE ) ).GetValue() ) ?
//STRIP001                                  ( IsLinkedGraphic() ? STR_ObjNameSingulGRAFBMPTRANSLNK : STR_ObjNameSingulGRAFBMPTRANS ) :
//STRIP001                                  ( IsLinkedGraphic() ? STR_ObjNameSingulGRAFBMPLNK : STR_ObjNameSingulGRAFBMP ) );
//STRIP001
//STRIP001             rName=ImpGetResStr( nId );
//STRIP001         }
//STRIP001         break;
//STRIP001
//STRIP001      case GRAPHIC_GDIMETAFILE:
//STRIP001             rName=ImpGetResStr( IsLinkedGraphic() ? STR_ObjNameSingulGRAFMTFLNK : STR_ObjNameSingulGRAFMTF );
//STRIP001         break;
//STRIP001
//STRIP001         case GRAPHIC_NONE:
//STRIP001             rName=ImpGetResStr( IsLinkedGraphic() ? STR_ObjNameSingulGRAFNONELNK : STR_ObjNameSingulGRAFNONE );
//STRIP001         break;
//STRIP001
//STRIP001         default:
//STRIP001             rName=ImpGetResStr(  IsLinkedGraphic() ? STR_ObjNameSingulGRAFLNK : STR_ObjNameSingulGRAF );
//STRIP001         break;
//STRIP001  }
//STRIP001
//STRIP001  if( aName.Len() )
//STRIP001  {
//STRIP001      rName.AppendAscii( " '" );
//STRIP001      rName += aName;
//STRIP001      rName += sal_Unicode( '\'' );
//STRIP001  }
//STRIP001 }

// -----------------------------------------------------------------------------

//STRIP001 void SdrGrafObj::TakeObjNamePlural( XubString& rName ) const
//STRIP001 {
//STRIP001  switch( pGraphic->GetType() )
//STRIP001  {
//STRIP001      case GRAPHIC_BITMAP:
//STRIP001         {
//STRIP001             const USHORT nId = ( ( IsTransparent() || ( (const SdrGrafTransparenceItem&) GetItem( SDRATTR_GRAFTRANSPARENCE ) ).GetValue() ) ?
//STRIP001                                  ( IsLinkedGraphic() ? STR_ObjNamePluralGRAFBMPTRANSLNK : STR_ObjNamePluralGRAFBMPTRANS ) :
//STRIP001                                  ( IsLinkedGraphic() ? STR_ObjNamePluralGRAFBMPLNK : STR_ObjNamePluralGRAFBMP ) );
//STRIP001
//STRIP001             rName=ImpGetResStr( nId );
//STRIP001         }
//STRIP001         break;
//STRIP001
//STRIP001      case GRAPHIC_GDIMETAFILE:
//STRIP001             rName=ImpGetResStr( IsLinkedGraphic() ? STR_ObjNamePluralGRAFMTFLNK : STR_ObjNamePluralGRAFMTF );
//STRIP001         break;
//STRIP001
//STRIP001         case GRAPHIC_NONE:
//STRIP001             rName=ImpGetResStr( IsLinkedGraphic() ? STR_ObjNamePluralGRAFNONELNK : STR_ObjNamePluralGRAFNONE );
//STRIP001         break;
//STRIP001
//STRIP001         default:
//STRIP001             rName=ImpGetResStr(  IsLinkedGraphic() ? STR_ObjNamePluralGRAFLNK : STR_ObjNamePluralGRAF );
//STRIP001         break;
//STRIP001  }
//STRIP001
//STRIP001  if( aName.Len() )
//STRIP001  {
//STRIP001      rName.AppendAscii( " '" );
//STRIP001      rName += aName;
//STRIP001      rName += sal_Unicode( '\'' );
//STRIP001  }
//STRIP001 }

// -----------------------------------------------------------------------------

/*N*/ void SdrGrafObj::operator=( const SdrObject& rObj )
/*N*/ {
/*N*/   SdrRectObj::operator=( rObj );
/*N*/
/*N*/   const SdrGrafObj& rGraf = (SdrGrafObj&) rObj;
/*N*/
/*N*/   pGraphic->SetGraphic( rGraf.GetGraphic() );
/*N*/   aCropRect = rGraf.aCropRect;
/*N*/   aFileName = rGraf.aFileName;
/*N*/   aFilterName = rGraf.aFilterName;
/*N*/   aName = rGraf.aName;
/*N*/   bMirrored = rGraf.bMirrored;
/*N*/
/*N*/ #ifndef SVX_LIGHT
/*N*/   if( rGraf.pGraphicLink != NULL)
/*N*/ #else
/*N*/   if( rGraf.aFileName.Len() )
/*N*/ #endif
/*?*/       {DBG_ASSERT(0, "STRIP"); }//STRIP001 SetGraphicLink( aFileName, aFilterName );
/*N*/
/*N*/   ImpSetAttrToGrafInfo();
/*N*/ }

// -----------------------------------------------------------------------------

//STRIP001 FASTBOOL SdrGrafObj::HasSpecialDrag() const
//STRIP001 {
//STRIP001  return TRUE;
//STRIP001 }

// -----------------------------------------------------------------------------

//STRIP001 USHORT SdrGrafObj::GetHdlCount() const
//STRIP001 {
//STRIP001  return 8;
//STRIP001 }

// -----------------------------------------------------------------------------

//STRIP001 SdrHdl* SdrGrafObj::GetHdl(USHORT nHdlNum) const
//STRIP001 {
//STRIP001  return SdrRectObj::GetHdl( nHdlNum + 1 );
//STRIP001 }

// -----------------------------------------------------------------------------

/*N*/ void SdrGrafObj::NbcResize(const Point& rRef, const Fraction& xFact, const Fraction& yFact)
/*N*/ {
/*N*/   SdrRectObj::NbcResize( rRef, xFact, yFact );
/*N*/
/*N*/   FASTBOOL bMirrX = xFact.GetNumerator() < 0;
/*N*/   FASTBOOL bMirrY = yFact.GetNumerator() < 0;
/*N*/
/*N*/   if( bMirrX != bMirrY )
/*?*/       bMirrored = !bMirrored;
/*N*/ }

// -----------------------------------------------------------------------------

/*N*/ void SdrGrafObj::NbcRotate(const Point& rRef, long nWink, double sn, double cs)
/*N*/ {
/*N*/   SdrRectObj::NbcRotate(rRef,nWink,sn,cs);
/*N*/ }

// -----------------------------------------------------------------------------

//STRIP001 void SdrGrafObj::NbcMirror(const Point& rRef1, const Point& rRef2)
//STRIP001 {
//STRIP001  SdrRectObj::NbcMirror(rRef1,rRef2);
//STRIP001  bMirrored = !bMirrored;
//STRIP001 }

// -----------------------------------------------------------------------------

//STRIP001 void SdrGrafObj::NbcShear(const Point& rRef, long nWink, double tn, FASTBOOL bVShear)
//STRIP001 {
//STRIP001  SdrRectObj::NbcRotate( rRef, nWink, tn, bVShear );
//STRIP001 }

// -----------------------------------------------------------------------------

/*N*/ void SdrGrafObj::NbcSetSnapRect(const Rectangle& rRect)
/*N*/ {
/*N*/   SdrRectObj::NbcSetSnapRect(rRect);
/*N*/ }

// -----------------------------------------------------------------------------

/*N*/ void SdrGrafObj::NbcSetLogicRect( const Rectangle& rRect)
/*N*/ {
/*N*/   FASTBOOL bChg=rRect.GetSize()!=aRect.GetSize();
/*N*/   SdrRectObj::NbcSetLogicRect(rRect);
/*N*/ }

// -----------------------------------------------------------------------------

/*N*/ SdrObjGeoData* SdrGrafObj::NewGeoData() const
/*N*/ {
/*N*/   return new SdrGrafObjGeoData;
/*N*/ }

// -----------------------------------------------------------------------------

/*N*/ void SdrGrafObj::SaveGeoData(SdrObjGeoData& rGeo) const
/*N*/ {
/*N*/   SdrRectObj::SaveGeoData(rGeo);
/*N*/   SdrGrafObjGeoData& rGGeo=(SdrGrafObjGeoData&)rGeo;
/*N*/   rGGeo.bMirrored=bMirrored;
/*N*/ }

// -----------------------------------------------------------------------------

//STRIP001 void SdrGrafObj::RestGeoData(const SdrObjGeoData& rGeo)
//STRIP001 {
//STRIP001  long        nDrehMerk = aGeo.nDrehWink;
//STRIP001  long        nShearMerk = aGeo.nShearWink;
//STRIP001  FASTBOOL    bMirrMerk = bMirrored;
//STRIP001  Size        aSizMerk( aRect.GetSize() );
//STRIP001
//STRIP001  SdrRectObj::RestGeoData(rGeo);
//STRIP001  SdrGrafObjGeoData& rGGeo=(SdrGrafObjGeoData&)rGeo;
//STRIP001  bMirrored=rGGeo.bMirrored;
//STRIP001 }

// -----------------------------------------------------------------------------

/*N*/ void SdrGrafObj::SetPage( SdrPage* pNewPage )
/*N*/ {
/*N*/   FASTBOOL bRemove = pNewPage == NULL && pPage != NULL;
/*N*/   FASTBOOL bInsert = pNewPage != NULL && pPage == NULL;
/*N*/
/*N*/   if( bRemove )
/*N*/   {
/*N*/       // hier kein SwapIn noetig, weil wenn nicht geladen, dann auch nicht animiert.
/*N*/       if( pGraphic->IsAnimated())
/*?*/           pGraphic->StopAnimation();
/*N*/
/*N*/       if( pGraphicLink != NULL )
/*?*/           ImpLinkAbmeldung();
/*N*/   }
/*N*/
/*N*/   SdrRectObj::SetPage( pNewPage );
/*N*/
/*N*/   if(aFileName.Len() && bInsert)
/*?*/       {DBG_ASSERT(0, "STRIP"); }//STRIP001 ImpLinkAnmeldung();
/*N*/ }

// -----------------------------------------------------------------------------

/*N*/ void SdrGrafObj::SetModel( SdrModel* pNewModel )
/*N*/ {
/*N*/   FASTBOOL bChg = pNewModel != pModel;
/*N*/
/*N*/   if( bChg )
/*N*/   {
/*N*/       if( ( GRAFSTREAMPOS_INVALID != nGrafStreamPos ) || pGraphic->HasUserData() )
/*N*/       {
/*?*/           ForceSwapIn();
/*?*/           pGraphic->SetUserData();
/*?*/           nGrafStreamPos = GRAFSTREAMPOS_INVALID;
/*N*/       }
/*N*/
/*N*/       if( pGraphicLink != NULL )
/*?*/           ImpLinkAbmeldung();
/*N*/   }

    // Model umsetzen
/*N*/   SdrRectObj::SetModel(pNewModel);
/*N*/
/*N*/   if( bChg && aFileName.Len() )
/*?*/       {DBG_ASSERT(0, "STRIP"); }//STRIP001 ImpLinkAnmeldung();
/*N*/ }

// -----------------------------------------------------------------------------

//STRIP001 void SdrGrafObj::StartAnimation( OutputDevice* pOutDev, const Point& rPoint, const Size& rSize, long nExtraData )
//STRIP001 {
//STRIP001  GraphicAttr     aAttr( aGrafInfo );
//STRIP001  USHORT          nMirrorCase = ( aGeo.nDrehWink == 18000 ) ? ( bMirrored ? 3 : 4 ) : ( bMirrored ? 2 : 1 );
//STRIP001  FASTBOOL        bHMirr = nMirrorCase == 2 || nMirrorCase == 4;
//STRIP001  FASTBOOL        bVMirr = nMirrorCase == 3 || nMirrorCase == 4;
//STRIP001
//STRIP001  aAttr.SetMirrorFlags( ( bHMirr ? BMP_MIRROR_HORZ : 0 ) | ( bVMirr ? BMP_MIRROR_VERT : 0 ) );
//STRIP001  pGraphic->SetAnimationNotifyHdl( LINK( this, SdrGrafObj, ImpAnimationHdl ) );
//STRIP001  pGraphic->StartAnimation( pOutDev, rPoint, rSize, nExtraData, &aAttr );
//STRIP001 }

// -----------------------------------------------------------------------------

//STRIP001 void SdrGrafObj::StopAnimation(OutputDevice* pOutDev, long nExtraData)
//STRIP001 {
//STRIP001  pGraphic->StopAnimation( pOutDev, nExtraData );
//STRIP001 }

// -----------------------------------------------------------------------------

/*N*/ FASTBOOL SdrGrafObj::HasGDIMetaFile() const
/*N*/ {
/*N*/   return( pGraphic->GetType() == GRAPHIC_GDIMETAFILE );
/*N*/ }

// -----------------------------------------------------------------------------

/*N*/ const GDIMetaFile* SdrGrafObj::GetGDIMetaFile() const
/*N*/ {
/*N*/   DBG_ERROR( "Invalid return value! Don't use it! (KA)" );
/*N*/   return &GetGraphic().GetGDIMetaFile();
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////
// pre- and postprocessing for objects for saving

/*N*/ void SdrGrafObj::PreSave()
/*N*/ {
/*N*/   // call parent
/*N*/   SdrRectObj::PreSave();
/*N*/
/*N*/   // prepare SetItems for storage
/*N*/   const SfxItemSet& rSet = GetUnmergedItemSet();
/*N*/   const SfxItemSet* pParent = GetStyleSheet() ? &GetStyleSheet()->GetItemSet() : 0L;
/*N*/   SdrGrafSetItem aGrafAttr(rSet.GetPool());
/*N*/   aGrafAttr.GetItemSet().Put(rSet);
/*N*/   aGrafAttr.GetItemSet().SetParent(pParent);
/*N*/   mpObjectItemSet->Put(aGrafAttr);
/*N*/ }

/*N*/ void SdrGrafObj::PostSave()
/*N*/ {
/*N*/   // call parent
/*N*/   SdrRectObj::PostSave();
/*N*/
/*N*/   // remove SetItems from local itemset
/*N*/   mpObjectItemSet->ClearItem(SDRATTRSET_GRAF);
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ void SdrGrafObj::WriteData(SvStream& rOut) const
/*N*/ {
/*N*/   ForceSwapIn();
/*N*/   SdrRectObj::WriteData( rOut );
/*N*/
/*N*/   // Fuer Abwaertskompatibilitaet (Lesen neuer Daten mit altem Code)
/*N*/   SdrDownCompat aCompat( rOut, STREAM_WRITE );
/*N*/
/*N*/ #ifdef DBG_UTIL
/*N*/   aCompat.SetID( "SdrGrafObj" );
/*N*/ #endif
/*N*/
/*N*/   GraphicType eType( pGraphic->GetType() );
/*N*/   BOOL        bHasGraphic( !aFileName.Len() && eType != GRAPHIC_NONE );
/*N*/
/*N*/   // dieses Flag wird ab V11 rausgeschrieben
/*N*/   rOut << bHasGraphic;
/*N*/
/*N*/   if(bHasGraphic)
/*N*/   {
/*N*/       // Graphik ist nicht gelinkt: ggf. komprimiert speichern:
/*N*/       // seit V11 eingapackt
/*N*/       SdrDownCompat aGrafCompat(rOut, STREAM_WRITE);
/*N*/       BOOL bZCompr(pModel && pModel->IsSaveCompressed() && eType == GRAPHIC_BITMAP);
/*N*/       BOOL bNCompr(pModel && pModel->IsSaveNative());
/*N*/       const UINT16 nOldComprMode(rOut.GetCompressMode());
/*N*/       UINT16 nNewComprMode(nOldComprMode);
/*N*/
/*N*/ #ifdef DBG_UTIL
/*N*/       aGrafCompat.SetID( "SdrGrafObj(Graphic)" );
/*N*/ #endif
/*N*/
/*N*/       if(pModel->IsSwapGraphics() && (pModel->GetSwapGraphicsMode() & SDR_SWAPGRAPHICSMODE_DOC))
/*N*/       {
/*N*/           ((SdrGrafObj*)this)->pGraphic->SetUserData();
/*N*/           ((SdrGrafObj*)this)->nGrafStreamPos = rOut.Tell();
/*N*/       }
/*N*/
/*N*/       if(bZCompr)
/*N*/           nNewComprMode |= COMPRESSMODE_ZBITMAP;
/*N*/
/*N*/       if(bNCompr)
/*N*/           nNewComprMode |= COMPRESSMODE_NATIVE;
/*N*/
/*N*/       rOut.SetCompressMode( nNewComprMode );
/*N*/       rOut << pGraphic->GetGraphic();
/*N*/       rOut.SetCompressMode( nOldComprMode );
/*N*/   }
/*N*/
/*N*/   rOut << aCropRect;
/*N*/   rOut << BOOL(bMirrored);
/*N*/
/*N*/   rOut.WriteByteString(aName);
/*N*/
/*N*/   String aRelFileName;
/*N*/
/*N*/   if( aFileName.Len() )
/*N*/   {
/*?*/       aRelFileName = INetURLObject::AbsToRel( aFileName,
/*?*/                                               INetURLObject::WAS_ENCODED,
/*?*/                                               INetURLObject::DECODE_UNAMBIGUOUS );
/*N*/   }
/*N*/
/*N*/   rOut.WriteByteString( aRelFileName );
/*N*/
/*N*/   // UNICODE: rOut << aFilterName;
/*N*/   rOut.WriteByteString(aFilterName);
/*N*/
/*N*/   // ab V11
/*N*/   rOut << (BOOL)( aFileName.Len() != 0 );
/*N*/
/*N*/   SfxItemPool* pPool = GetItemPool();
/*N*/
/*N*/   if(pPool)
/*N*/   {
/*N*/       const SfxItemSet& rSet = GetUnmergedItemSet();
/*N*/
/*N*/       pPool->StoreSurrogate(rOut, &rSet.Get(SDRATTRSET_GRAF));
/*N*/   }
/*N*/   else
/*?*/       rOut << UINT16( SFX_ITEMS_NULL );
/*N*/
/*N*/   ForceSwapOut();
/*N*/ }

// -----------------------------------------------------------------------------

/*N*/ void SdrGrafObj::ReadDataTilV10( const SdrObjIOHeader& rHead, SvStream& rIn )
/*N*/ {
/*N*/   Graphic aGraphic;
/*N*/
/*N*/   // Import von allem mit Version <= 10
/*N*/   rIn >> aGraphic;
/*N*/
/*N*/   ULONG nError = rIn.GetError();
/*N*/
/*N*/   // Ist die Graphik defekt, oder wurde nur eine leere Graphik eingelesen? (was bei gelinkten Graphiken der Fall ist)
/*N*/   if( nError != 0)
/*?*/       rIn.ResetError();
/*N*/
/*N*/   if( rHead.GetVersion() >= 6)
/*N*/       rIn >> aCropRect;
/*N*/
/*N*/   if(rHead.GetVersion() >= 8)
/*N*/   {
/*N*/       // UNICODE: rIn>>aFileName;
/*N*/       rIn.ReadByteString(aFileName);
/*N*/   }
/*N*/
/*N*/   if(rHead.GetVersion() >= 9)
/*N*/   {
/*N*/       // UNICODE: rIn >> aFilterName;
/*N*/       rIn.ReadByteString(aFilterName);
/*N*/   }
/*N*/   else
/*?*/       aFilterName = String( RTL_CONSTASCII_USTRINGPARAM( "BMP - MS Windows" ) );
/*N*/
/*N*/   if( aFileName.Len() )
/*N*/   {
/*?*/ #ifndef SVX_LIGHT
/*?*/       String aFileURLStr;
/*?*/
/*?*/       if( ::utl::LocalFileHelper::ConvertPhysicalNameToURL( aFileName, aFileURLStr ) )
/*?*/       {
/*?*/           SvStream* pIStm = ::utl::UcbStreamHelper::CreateStream( aFileURLStr, STREAM_READ | STREAM_SHARE_DENYNONE );
/*?*/
/*?*/           if( pIStm )
/*?*/           {
/*?*/               GraphicFilter*  pFilter = GetGrfFilter();
/*?*/               USHORT          nError = pFilter->ImportGraphic( aGraphic, aFileURLStr, *pIStm );
/*?*/
/*?*/               SetGraphicLink( aFileURLStr, aFilterName );
/*?*/
/*?*/               delete pIStm;
/*?*/           }
/*?*/       }
/*?*/ #else
/*?*/       DBG_ERROR("SdrGrafObj::ReadDataTilV10(): SVX_LIGHT kann keine Graphic-Links");
/*?*/ #endif
/*N*/   }
/*N*/   else if( nError != 0 )
/*?*/       rIn.SetError(nError);
/*N*/
/*N*/
/*N*/   if( !rIn.GetError() )
/*N*/       pGraphic->SetGraphic( aGraphic );
/*N*/ }

// -----------------------------------------------------------------------------

/*N*/ #ifdef WNT
/*N*/ #pragma optimize ("",off)
/*N*/ #endif

/*N*/ void SdrGrafObj::ReadData( const SdrObjIOHeader& rHead, SvStream& rIn )
/*N*/ {
/*N*/   if( rIn.GetError() )
/*?*/       return;
/*N*/
/*N*/   SdrRectObj::ReadData( rHead, rIn );
/*N*/
/*N*/   SdrDownCompat   aCompat( rIn, STREAM_READ );
/*N*/   FASTBOOL        bDelayedLoad = ( pModel != NULL ) && pModel->IsSwapGraphics();
/*N*/
/*N*/ #ifdef DBG_UTIL
/*N*/   aCompat.SetID("SdrGrafObj");
/*N*/ #endif
/*N*/
/*N*/   pGraphic->SetUserData();
/*N*/   nGrafStreamPos = GRAFSTREAMPOS_INVALID;
/*N*/
/*N*/   if( rHead.GetVersion() < 11 )
/*N*/       ReadDataTilV10( rHead, rIn );
/*N*/   else
/*N*/   {
/*N*/       String  aFileNameRel;
/*N*/       BOOL    bHasGraphic;
/*N*/       BOOL    bTmp;
/*N*/       BOOL    bGraphicLink;
/*N*/
/*N*/       rIn >> bHasGraphic;
/*N*/
/*N*/       if( bHasGraphic )
/*N*/       {
/*N*/           SdrDownCompat aGrafCompat( rIn,STREAM_READ );
/*N*/
/*N*/ #ifdef DBG_UTIL
/*N*/           aGrafCompat.SetID("SdrGrafObj(Graphic)");
/*N*/ #endif
/*N*/
/*N*/           nGrafStreamPos = rIn.Tell();
/*N*/
/*N*/           if( !bDelayedLoad )
/*N*/           {
/*?*/               Graphic aGraphic;
/*?*/               rIn >> aGraphic;
/*?*/               pGraphic->SetGraphic( aGraphic );
/*N*/           }
/*N*/           else
/*N*/               pGraphic->SetSwapState();
/*N*/
/*N*/           // Ist die Grafik defekt, oder wurde nur eine leere Graphik eingelesen?
/*N*/           // Daran soll mein Read jedoch nicht scheitern.
/*N*/           if( rIn.GetError() != 0 )
/*?*/               rIn.ResetError();
/*N*/       }
/*N*/
/*N*/       rIn >> aCropRect;
/*N*/       rIn >> bTmp; bMirrored = bTmp;
/*N*/
/*N*/       rIn.ReadByteString(aName);
/*N*/       // #85414# since there seems to be some documents wich have an illegal
/*N*/       // character inside the name of a graphic object we have to fix this
/*N*/       // here on load time or it will crash our xml later.
/*N*/       const xub_StrLen nLen = aName.Len();
/*N*/       for( xub_StrLen nIndex = 0; nIndex < nLen; nIndex++ )
/*N*/       {
/*N*/           if( aName.GetChar( nIndex ) < ' ' )
/*?*/               aName.SetChar( nIndex, '?' );
/*N*/       }
/*N*/
/*N*/       rIn.ReadByteString(aFileNameRel);
/*N*/
/*N*/       if( aFileNameRel.Len() )
/*N*/       {
/*N*/           aFileName = ::URIHelper::SmartRelToAbs( aFileNameRel, FALSE,
/*N*/                                                   INetURLObject::WAS_ENCODED,
/*N*/                                                   INetURLObject::DECODE_UNAMBIGUOUS );
/*N*/       }
/*N*/       else
/*N*/           aFileName.Erase();
/*N*/
/*N*/       // UNICODE: rIn >> aFilterName;
/*N*/       rIn.ReadByteString(aFilterName);
/*N*/
/*N*/       rIn >> bGraphicLink;                    // auch dieses Flag ist neu in V11
/*N*/
/*N*/       if( aCompat.GetBytesLeft() > 0 )
/*N*/       {
/*N*/           SfxItemPool* pPool = GetItemPool();
/*N*/
/*N*/           if( pPool )
/*N*/           {
/*N*/               sal_uInt16 nSetID = SDRATTRSET_GRAF;
/*N*/               const SdrGrafSetItem* pGrafAttr = (const SdrGrafSetItem*)pPool->LoadSurrogate(rIn, nSetID, 0);
/*N*/               if(pGrafAttr)
/*N*/                   SetItemSet(pGrafAttr->GetItemSet());
/*N*/                   ImpSetAttrToGrafInfo();
/*N*/           }
/*N*/           else
/*N*/           {
/*?*/               UINT16 nSuroDummy;
/*?*/               rIn >> nSuroDummy;
/*N*/           }
/*N*/       }
/*N*/       else
/*N*/           bCopyToPoolOnAfterRead = TRUE;
/*N*/
/*N*/       if( bGraphicLink && aFileName.Len() )
/*N*/       {
/*?*/           SetGraphicLink( aFileName, aFilterName );
/*?*/
/*?*/           if( !bDelayedLoad )
/*?*/                 ImpUpdateGraphicLink();
/*N*/       }
/*N*/   }
/*N*/ }

// -----------------------------------------------------------------------------

/*N*/ #ifdef WNT
/*N*/ #pragma optimize ("",on)
/*N*/ #endif

// -----------------------------------------------------------------------------

//STRIP001 Rectangle SdrGrafObj::GetAnimationRect(const OutputDevice* pOutDev) const
//STRIP001 {
//STRIP001  return GetSnapRect();
//STRIP001 }

// -----------------------------------------------------------------------------

//STRIP001 void SdrGrafObj::SetAnimationSupervisor( OutputDevice* pDisplayDev, BOOL bObjSupervises )
//STRIP001 {
//STRIP001  ForceSwapIn();
//STRIP001  List* pAInfoList = pGraphic->GetAnimationInfoList();
//STRIP001
//STRIP001  if ( pAInfoList )
//STRIP001  {
//STRIP001      for( AInfo* pAInfo = (AInfo*) pAInfoList->First(); pAInfo; pAInfo = (AInfo*) pAInfoList->Next() )
//STRIP001      {
//STRIP001          if( pAInfo->pOutDev == pDisplayDev )
//STRIP001          {
//STRIP001              pAInfo->nExtraData = ( bObjSupervises ? 1L : (long) this );
//STRIP001
//STRIP001              if ( !bObjSupervises )
//STRIP001                  pAInfo->bPause = FALSE;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 }

// -----------------------------------------------------------------------------

//STRIP001 void SdrGrafObj::ResetAnimationLoopCount()
//STRIP001 {
//STRIP001  if( pGraphic->IsAnimated() )
//STRIP001  {
//STRIP001      ForceSwapIn();
//STRIP001      pGraphic->ResetAnimationLoopCount();
//STRIP001  }
//STRIP001 }

// -----------------------------------------------------------------------------

/*N*/ void SdrGrafObj::RestartAnimation(SdrPageView* pPageView) const
/*N*/ {
/*N*/   // ToDo: hier noch entsprechend implementieren wie im TextObj
/*N*/   SdrRectObj::RestartAnimation( pPageView );
/*N*/ }

// -----------------------------------------------------------------------------

//STRIP001 SdrObject* SdrGrafObj::DoConvertToPolyObj(BOOL bBezier) const
//STRIP001 {
//STRIP001  SdrObject* pRetval = NULL;
//STRIP001
//STRIP001  switch( GetGraphicType() )
//STRIP001  {
//STRIP001      case GRAPHIC_GDIMETAFILE:
//STRIP001      {
//STRIP001          // NUR die aus dem MetaFile erzeugbaren Objekte in eine Gruppe packen und zurueckliefern
//STRIP001          SdrObjGroup*            pGrp = new SdrObjGroup();
//STRIP001          ImpSdrGDIMetaFileImport aFilter(*GetModel());
//STRIP001          Point                   aOutPos( aRect.TopLeft() );
//STRIP001          const Size              aOutSiz( aRect.GetSize() );
//STRIP001
//STRIP001          aFilter.SetScaleRect(GetSnapRect());
//STRIP001          aFilter.SetLayer(GetLayer());
//STRIP001
//STRIP001          UINT32 nInsAnz = aFilter.DoImport(GetTransformedGraphic().GetGDIMetaFile(), *pGrp->GetSubList(), 0);
//STRIP001          if(nInsAnz)
//STRIP001          {
//STRIP001              pRetval = pGrp;
//STRIP001              pGrp->NbcSetLayer(GetLayer());
//STRIP001              pGrp->SetModel(GetModel());
//STRIP001              pRetval = ImpConvertAddText(pRetval, bBezier);
//STRIP001
//STRIP001                 // convert all children
//STRIP001                 if( pRetval )
//STRIP001                 {
//STRIP001                     SdrObject* pHalfDone = pRetval;
//STRIP001                     pRetval = pHalfDone->DoConvertToPolyObj(bBezier);
//STRIP001                     delete pHalfDone; // resulting object is newly created
//STRIP001
//STRIP001                     if( pRetval )
//STRIP001                     {
//STRIP001                         // flatten subgroups. As we call
//STRIP001                         // DoConvertToPolyObj() on the resulting group
//STRIP001                         // objects, subgroups can exist (e.g. text is
//STRIP001                         // a group object for every line).
//STRIP001                         SdrObjList* pList = pRetval->GetSubList();
//STRIP001                         if( pList )
//STRIP001                             pList->FlattenGroups();
//STRIP001                     }
//STRIP001                 }
//STRIP001          }
//STRIP001          else
//STRIP001              delete pGrp;
//STRIP001          break;
//STRIP001      }
//STRIP001      case GRAPHIC_BITMAP:
//STRIP001      {
//STRIP001          // Grundobjekt kreieren und Fuellung ergaenzen
//STRIP001          pRetval = SdrRectObj::DoConvertToPolyObj(bBezier);
//STRIP001
//STRIP001          // Bitmap als Attribut retten
//STRIP001          if(pRetval)
//STRIP001          {
//STRIP001              // Bitmap als Fuellung holen
//STRIP001              SfxItemSet aSet(GetItemSet());
//STRIP001
//STRIP001              aSet.Put(XFillStyleItem(XFILL_BITMAP));
//STRIP001              Bitmap aBitmap( GetTransformedGraphic().GetBitmap() );
//STRIP001              XOBitmap aXBmp(aBitmap, XBITMAP_STRETCH);
//STRIP001              aSet.Put(XFillBitmapItem(String(), aXBmp));
//STRIP001              aSet.Put(XFillBmpTileItem(FALSE));
//STRIP001
//STRIP001              pRetval->SetItemSet(aSet);
//STRIP001          }
//STRIP001          break;
//STRIP001      }
//STRIP001      case GRAPHIC_NONE:
//STRIP001      case GRAPHIC_DEFAULT:
//STRIP001      {
//STRIP001          pRetval = SdrRectObj::DoConvertToPolyObj(bBezier);
//STRIP001          break;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  return pRetval;
//STRIP001 }

// -----------------------------------------------------------------------------

/*N*/ void SdrGrafObj::AfterRead()
/*N*/ {
/*N*/   SdrRectObj::AfterRead();
/*N*/
/*N*/   if( bCopyToPoolOnAfterRead )
/*N*/   {
/*N*/       ImpSetGrafInfoToAttr();
/*N*/       bCopyToPoolOnAfterRead = FALSE;
/*N*/   }
/*N*/ }

// -----------------------------------------------------------------------------

/*N*/ void SdrGrafObj::SFX_NOTIFY( SfxBroadcaster& rBC, const TypeId& rBCType,
/*N*/                            const SfxHint& rHint, const TypeId& rHintType )
/*N*/ {
/*N*/   SetXPolyDirty();
/*N*/   SdrRectObj::SFX_NOTIFY( rBC, rBCType, rHint, rHintType );
/*N*/   ImpSetAttrToGrafInfo();
/*N*/ }

// -----------------------------------------------------------------------------

/*N*/ void SdrGrafObj::ForceDefaultAttr()
/*N*/ {
/*N*/   SdrRectObj::ForceDefaultAttr();
/*N*/
/*N*/   ImpForceItemSet();
/*N*/   mpObjectItemSet->Put( SdrGrafLuminanceItem( 0 ) );
/*N*/   mpObjectItemSet->Put( SdrGrafContrastItem( 0 ) );
/*N*/   mpObjectItemSet->Put( SdrGrafRedItem( 0 ) );
/*N*/   mpObjectItemSet->Put( SdrGrafGreenItem( 0 ) );
/*N*/   mpObjectItemSet->Put( SdrGrafBlueItem( 0 ) );
/*N*/   mpObjectItemSet->Put( SdrGrafGamma100Item( 100 ) );
/*N*/   mpObjectItemSet->Put( SdrGrafTransparenceItem( 0 ) );
/*N*/   mpObjectItemSet->Put( SdrGrafInvertItem( FALSE ) );
/*N*/   mpObjectItemSet->Put( SdrGrafModeItem( GRAPHICDRAWMODE_STANDARD ) );
/*N*/   mpObjectItemSet->Put( SdrGrafCropItem( 0, 0, 0, 0 ) );
/*N*/ }

// -----------------------------------------------------------------------------

/*N*/ void SdrGrafObj::NbcSetStyleSheet( SfxStyleSheet* pNewStyleSheet, FASTBOOL bDontRemoveHardAttr )
/*N*/ {
/*N*/   SetXPolyDirty();
/*N*/   SdrRectObj::NbcSetStyleSheet( pNewStyleSheet, bDontRemoveHardAttr );
/*N*/   ImpSetAttrToGrafInfo();
/*N*/ }

// -----------------------------------------------------------------------------
// ItemSet access

/*N*/ SfxItemSet* SdrGrafObj::CreateNewItemSet(SfxItemPool& rPool)
/*N*/ {
/*N*/   // include ALL items, 2D and 3D
/*N*/   return new SfxItemSet(rPool,
/*N*/       // ranges from SdrAttrObj
/*N*/       SDRATTR_START, SDRATTRSET_SHADOW,
/*N*/       SDRATTRSET_OUTLINER, SDRATTRSET_MISC,
/*N*/       SDRATTR_TEXTDIRECTION, SDRATTR_TEXTDIRECTION,
/*N*/
/*N*/       // graf attributes
/*N*/       SDRATTR_GRAF_FIRST, SDRATTRSET_GRAF,
/*N*/
/*N*/       // outliner and end
/*N*/       EE_ITEMS_START, EE_ITEMS_END,
/*N*/       0, 0);
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////
// private support routines for ItemSet access
/*N*/ void SdrGrafObj::ItemSetChanged(const SfxItemSet& rSet)
/*N*/ {
/*N*/   // local changes
/*N*/   SetXPolyDirty();
/*N*/
/*N*/   // call parent
/*N*/   SdrRectObj::ItemSetChanged(rSet);
/*N*/
/*N*/   // local changes
/*N*/   ImpSetAttrToGrafInfo();
/*N*/ }

// -----------------------------------------------------------------------------

/*N*/ void SdrGrafObj::ImpSetAttrToGrafInfo()
/*N*/ {
/*N*/   const SfxItemSet& rSet = GetItemSet();
/*N*/   const sal_uInt16 nTrans = ( (SdrGrafTransparenceItem&) rSet.Get( SDRATTR_GRAFTRANSPARENCE ) ).GetValue();
/*N*/   const SdrGrafCropItem&  rCrop = (const SdrGrafCropItem&) rSet.Get( SDRATTR_GRAFCROP );
/*N*/
/*N*/   aGrafInfo.SetLuminance( ( (SdrGrafLuminanceItem&) rSet.Get( SDRATTR_GRAFLUMINANCE ) ).GetValue() );
/*N*/   aGrafInfo.SetContrast( ( (SdrGrafContrastItem&) rSet.Get( SDRATTR_GRAFCONTRAST ) ).GetValue() );
/*N*/   aGrafInfo.SetChannelR( ( (SdrGrafRedItem&) rSet.Get( SDRATTR_GRAFRED ) ).GetValue() );
/*N*/   aGrafInfo.SetChannelG( ( (SdrGrafGreenItem&) rSet.Get( SDRATTR_GRAFGREEN ) ).GetValue() );
/*N*/   aGrafInfo.SetChannelB( ( (SdrGrafBlueItem&) rSet.Get( SDRATTR_GRAFBLUE ) ).GetValue() );
/*N*/   aGrafInfo.SetGamma( ( (SdrGrafGamma100Item&) rSet.Get( SDRATTR_GRAFGAMMA ) ).GetValue() * 0.01 );
/*N*/   aGrafInfo.SetTransparency( (BYTE) FRound( Min( nTrans, (USHORT) 100 )  * 2.55 ) );
/*N*/   aGrafInfo.SetInvert( ( (SdrGrafInvertItem&) rSet.Get( SDRATTR_GRAFINVERT ) ).GetValue() );
/*N*/   aGrafInfo.SetDrawMode( ( (SdrGrafModeItem&) rSet.Get( SDRATTR_GRAFMODE ) ).GetValue() );
/*N*/   aGrafInfo.SetCrop( rCrop.GetLeft(), rCrop.GetTop(), rCrop.GetRight(), rCrop.GetBottom() );
/*N*/
/*N*/   SetXPolyDirty();
/*N*/   SetRectsDirty();
/*N*/ }

// -----------------------------------------------------------------------------

/*N*/ void SdrGrafObj::ImpSetGrafInfoToAttr()
/*N*/ {
/*N*/   SetItem( SdrGrafLuminanceItem( aGrafInfo.GetLuminance() ) );
/*N*/   SetItem( SdrGrafContrastItem( aGrafInfo.GetContrast() ) );
/*N*/   SetItem( SdrGrafRedItem( aGrafInfo.GetChannelR() ) );
/*N*/   SetItem( SdrGrafGreenItem( aGrafInfo.GetChannelG() ) );
/*N*/   SetItem( SdrGrafBlueItem( aGrafInfo.GetChannelB() ) );
/*N*/   SetItem( SdrGrafGamma100Item( FRound( aGrafInfo.GetGamma() * 100.0 ) ) );
/*N*/   SetItem( SdrGrafTransparenceItem( (USHORT) FRound( aGrafInfo.GetTransparency() / 2.55 ) ) );
/*N*/   SetItem( SdrGrafInvertItem( aGrafInfo.IsInvert() ) );
/*N*/   SetItem( SdrGrafModeItem( aGrafInfo.GetDrawMode() ) );
/*N*/   SetItem( SdrGrafCropItem( aGrafInfo.GetLeftCrop(), aGrafInfo.GetTopCrop(), aGrafInfo.GetRightCrop(), aGrafInfo.GetBottomCrop() ) );
/*N*/ }

// -----------------------------------------------------------------------------

/*N*/ void SdrGrafObj::AdjustToMaxRect( const Rectangle& rMaxRect, BOOL bShrinkOnly )
/*N*/ {
/*N*/   Size aSize;
/*N*/   Size aMaxSize( rMaxRect.GetSize() );
/*N*/   if ( pGraphic->GetPrefMapMode().GetMapUnit() == MAP_PIXEL )
/*N*/       aSize = Application::GetDefaultDevice()->PixelToLogic( pGraphic->GetPrefSize(), MAP_100TH_MM );
/*N*/   else
/*N*/       aSize = OutputDevice::LogicToLogic( pGraphic->GetPrefSize(),
/*N*/                                           pGraphic->GetPrefMapMode(),
/*N*/                                           MapMode( MAP_100TH_MM ) );
/*N*/
/*N*/   if( aSize.Height() != 0 && aSize.Width() != 0 )
/*N*/   {
/*N*/       Point aPos( rMaxRect.TopLeft() );
/*N*/
/*N*/       // Falls Grafik zu gross, wird die Grafik
/*N*/       // in die Seite eingepasst
/*N*/       if ( (!bShrinkOnly                          ||
/*N*/            ( aSize.Height() > aMaxSize.Height() ) ||
/*N*/           ( aSize.Width()  > aMaxSize.Width()  ) )&&
/*N*/           aSize.Height() && aMaxSize.Height() )
/*N*/       {
/*N*/           float fGrfWH =  (float)aSize.Width() /
/*N*/                           (float)aSize.Height();
/*N*/           float fWinWH =  (float)aMaxSize.Width() /
/*N*/                           (float)aMaxSize.Height();
/*N*/
/*N*/           // Grafik an Pagesize anpassen (skaliert)
/*N*/           if ( fGrfWH < fWinWH )
/*N*/           {
/*N*/               aSize.Width() = (long)(aMaxSize.Height() * fGrfWH);
/*N*/               aSize.Height()= aMaxSize.Height();
/*N*/           }
/*N*/           else if ( fGrfWH > 0.F )
/*N*/           {
/*N*/               aSize.Width() = aMaxSize.Width();
/*N*/               aSize.Height()= (long)(aMaxSize.Width() / fGrfWH);
/*N*/           }
/*N*/
/*N*/           aPos = rMaxRect.Center();
/*N*/       }
/*N*/
/*N*/       if( bShrinkOnly )
/*N*/           aPos = aRect.TopLeft();
/*N*/
/*N*/       aPos.X() -= aSize.Width() / 2;
/*N*/       aPos.Y() -= aSize.Height() / 2;
/*N*/       SetLogicRect( Rectangle( aPos, aSize ) );
/*N*/   }
/*N*/ }

// -----------------------------------------------------------------------------

/*N*/ IMPL_LINK( SdrGrafObj, ImpSwapHdl, GraphicObject*, pO )
/*N*/ {
/*N*/   SvStream* pRet = GRFMGR_AUTOSWAPSTREAM_NONE;
/*N*/
/*N*/   if( pO->IsInSwapOut() )
/*N*/   {
/*N*/       if( pModel != NULL && pModel->IsSwapGraphics() && pGraphic->GetSizeBytes() > 20480 )
/*N*/       {
/*N*/           SdrViewIter aIter( this );
/*N*/           SdrView*    pView = aIter.FirstView();
/*N*/           BOOL        bVisible = FALSE;
/*N*/
/*N*/           while( !bVisible && pView )
/*N*/           {
/*N*/               bVisible = !pView->IsGrafDraft();
/*N*/
/*N*/               if( !bVisible )
/*?*/                   pView = aIter.NextView();
/*N*/           }
/*N*/
/*N*/           if( !bVisible )
/*N*/           {
/*N*/               const ULONG nSwapMode = pModel->GetSwapGraphicsMode();
/*N*/
/*N*/ #ifndef SVX_LIGHT
/*N*/               if( ( ( GRAFSTREAMPOS_INVALID != nGrafStreamPos ) || pGraphic->HasUserData() || pGraphicLink ) &&
/*N*/                   ( nSwapMode & SDR_SWAPGRAPHICSMODE_PURGE ) )
/*N*/ #else
/*N*/               if( ( ( GRAFSTREAMPOS_INVALID != nGrafStreamPos ) || pGraphic->HasUserData() || aFileName.Len() ) &&
/*N*/                   ( nSwapMode & SDR_SWAPGRAPHICSMODE_PURGE ) )
/*N*/ #endif
/*N*/               {
/*N*/                   pRet = NULL;
/*N*/               }
/*N*/               else if( nSwapMode & SDR_SWAPGRAPHICSMODE_TEMP )
/*N*/               {
/*N*/                   pRet = GRFMGR_AUTOSWAPSTREAM_TEMP;
/*N*/                   pGraphic->SetUserData();
/*N*/                   nGrafStreamPos = GRAFSTREAMPOS_INVALID;
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/   else if( pO->IsInSwapIn() )
/*N*/   {
/*N*/       // kann aus dem original Doc-Stream nachgeladen werden...
/*N*/       if( pModel != NULL )
/*N*/       {
/*N*/           if( ( GRAFSTREAMPOS_INVALID != nGrafStreamPos ) || pGraphic->HasUserData() )
/*N*/           {
/*N*/               SdrDocumentStreamInfo aStreamInfo;
/*N*/
/*N*/               aStreamInfo.mbDeleteAfterUse = FALSE;
/*N*/               aStreamInfo.maUserData = pGraphic->GetUserData();
/*N*/                 aStreamInfo.mpStorageRef = NULL;
/*N*/
/*N*/               SvStream* pStream = pModel->GetDocumentStream( aStreamInfo );
/*N*/
/*N*/               if( pStream != NULL )
/*N*/               {
/*N*/                   Graphic aGraphic;
/*N*/
/*N*/                   if( pGraphic->HasUserData() )
/*N*/                   {
/*?*/                       if( !GetGrfFilter()->ImportGraphic( aGraphic, String(), *pStream ) )
/*?*/                       {
/*?*/                           const String aUserData( pGraphic->GetUserData() );
/*?*/
/*?*/                           pGraphic->SetGraphic( aGraphic );
/*?*/                           pGraphic->SetUserData( aUserData );
/*?*/                           pRet = GRFMGR_AUTOSWAPSTREAM_LOADED;
/*N*/                       }
/*N*/                   }
/*N*/                   else
/*N*/                   {
/*N*/                       pStream->Seek( nGrafStreamPos );
/*N*/                       *pStream >> aGraphic;
/*N*/                       pGraphic->SetGraphic( aGraphic );
/*N*/
/*N*/                       if( !pStream->GetError() )
/*N*/                           pRet = GRFMGR_AUTOSWAPSTREAM_LOADED;
/*N*/                   }
/*N*/
/*N*/                   pStream->ResetError();
/*N*/
/*N*/                   if( aStreamInfo.mbDeleteAfterUse || aStreamInfo.mpStorageRef )
/*N*/                     {
/*N*/                       delete pStream;
/*N*/                         delete aStreamInfo.mpStorageRef;
/*N*/                     }
/*N*/               }
/*N*/           }
/*N*/           else if( !ImpUpdateGraphicLink() )
/*N*/             {
/*?*/               pRet = GRFMGR_AUTOSWAPSTREAM_TEMP;
/*N*/             }
/*N*/           else
/*N*/             {
/*?*/                 pRet = GRFMGR_AUTOSWAPSTREAM_LOADED;
/*N*/             }
/*N*/       }
/*N*/       else
/*?*/           pRet = GRFMGR_AUTOSWAPSTREAM_TEMP;
/*N*/   }
/*N*/
/*N*/   return (long)(void*) pRet;
/*N*/ }

// -----------------------------------------------------------------------------

//STRIP001 IMPL_LINK( SdrGrafObj, ImpAnimationHdl, Animation*, pAnimation )
//STRIP001 {
//STRIP001     // Wenn wir nicht mehr da sind, stoppen wir natuerlich alles und kehren gleich zurueck
//STRIP001     if( !bInserted )
//STRIP001  {
//STRIP001         pAnimation->Stop();
//STRIP001         return 0L;
//STRIP001     }
//STRIP001
//STRIP001     List*    pAInfoList = pAnimation->GetAInfoList();
//STRIP001     AInfo*   pAInfo = (AInfo*) pAInfoList->First();
//STRIP001  BOOL    bExtern = FALSE;
//STRIP001
//STRIP001     // Alle Extra-Data auf 0 setzen, wenn keine andere ExtraData
//STRIP001     // ausser der eigenen (1) gesetzt;
//STRIP001     // groesser als 1 bedeutet, daß die Animation von aussen gestartet
//STRIP001     // wurde, z.B. von der DiaShow.
//STRIP001     while( pAInfo != NULL )
//STRIP001  {
//STRIP001         if( pAInfo->nExtraData == 1L )
//STRIP001          pAInfo->nExtraData = 0;
//STRIP001      else if( pAInfo->nExtraData > 1L )
//STRIP001          bExtern = TRUE;
//STRIP001
//STRIP001      pAInfo = (AInfo*) pAInfoList->Next();
//STRIP001     }
//STRIP001
//STRIP001     if( pModel!=NULL && pPage!=NULL && bInserted && pAInfoList->Count() )
//STRIP001  {
//STRIP001         USHORT       nPageNum=pPage->GetPageNum();
//STRIP001         FASTBOOL    bMaster=pPage->IsMasterPage() && !bNotVisibleAsMaster;
//STRIP001         USHORT      nLsAnz=pModel->GetListenerCount();
//STRIP001
//STRIP001         for( USHORT nLsNum=0; nLsNum<nLsAnz; nLsNum++ )
//STRIP001      {
//STRIP001             SfxListener* pLs=pModel->GetListener(nLsNum);
//STRIP001             SdrMarkView* pView=PTR_CAST(SdrMarkView,pLs);
//STRIP001
//STRIP001             if( pView && ( pView->IsAnimationEnabled() || bExtern ) )
//STRIP001          {
//STRIP001                 FASTBOOL bMrk=pView->IsObjMarked(this);
//STRIP001                 FASTBOOL    bPause=pView->IsAnimationPause();
//STRIP001                 USHORT       nPvAnz=pView->GetPageViewCount();
//STRIP001
//STRIP001              for (USHORT nPvNum=0; nPvNum<nPvAnz; nPvNum++)
//STRIP001              {
//STRIP001                     SdrPageView* pPV=pView->GetPageViewPvNum(nPvNum);
//STRIP001                     SdrPage*     pPg=pPV->GetPage();
//STRIP001
//STRIP001                  if (pPV->GetVisibleLayers().IsSet(nLayerID))
//STRIP001                  {
//STRIP001                         FASTBOOL bJa=pPg==pPage;
//STRIP001
//STRIP001                      if (!bJa && bMaster && !pPg->IsMasterPage())
//STRIP001                      {
//STRIP001                             USHORT nMasterAnz=pPg->GetMasterPageCount();
//STRIP001
//STRIP001                          for (USHORT nMasterNum=0; nMasterNum<nMasterAnz && !bJa; nMasterNum++)
//STRIP001                          {
//STRIP001                                 const SdrMasterPageDescriptor& rMPD=pPg->GetMasterPageDescriptor(nMasterNum);
//STRIP001                                 bJa=nPageNum==rMPD.GetPageNum() && rMPD.GetVisibleLayers().IsSet(nLayerID);
//STRIP001                             }
//STRIP001                         }
//STRIP001                         if (bJa)
//STRIP001                      {
//STRIP001                             USHORT nOutAnz=pView->GetWinCount();
//STRIP001
//STRIP001                          for (USHORT nOutNum=0; nOutNum<nOutAnz; nOutNum++)
//STRIP001                          {
//STRIP001                                 OutputDevice* pOut=pView->GetWin(nOutNum);
//STRIP001
//STRIP001                              if( pOut->GetOutDevType()==OUTDEV_WINDOW )
//STRIP001                              {
//STRIP001                                  Rectangle   aDrawRect( GetAnimationRect( pOut ) );
//STRIP001                                  const Point aOffset( pPV->GetOffset() );
//STRIP001                                     FASTBOOL bFound = FALSE;
//STRIP001
//STRIP001                                  aDrawRect.Move( aOffset.X(), aOffset.Y() );
//STRIP001
//STRIP001                                     // Flag am gefundenen Objekt setzen
//STRIP001                                     pAInfo=(AInfo*)pAInfoList->First();
//STRIP001                                     while( pAInfo!=NULL && !bFound )
//STRIP001                                  {
//STRIP001                                         if (pAInfo->aStartOrg==aDrawRect.TopLeft() &&
//STRIP001                                             pAInfo->aStartSize==aDrawRect.GetSize() &&
//STRIP001                                             pAInfo->pOutDev==pOut )
//STRIP001                                         {
//STRIP001                                          if( pAInfo->nExtraData==0 )
//STRIP001                                              pAInfo->nExtraData=1L;
//STRIP001
//STRIP001                                             pAInfo->bPause = ( bMrk || bPause );
//STRIP001                                             bFound = TRUE;
//STRIP001                                         }
//STRIP001
//STRIP001                                      pAInfo=(AInfo*)pAInfoList->Next();
//STRIP001                                     }
//STRIP001
//STRIP001                                     // Falls kein Record gefunden, wird ein neuer erzeugt
//STRIP001                                     // Das passiert z.B., wenn das Obj auf einer MasterPage liegt
//STRIP001                                     // und diese mittels MasterPagePaintCache angezeigt wurde.
//STRIP001                                     if (!bFound)
//STRIP001                                     {
//STRIP001                                         pAInfo = new AInfo;
//STRIP001
//STRIP001                                         // erst einmal soviel wie moeglich bekanntes setzen
//STRIP001                                         *pAInfo = *(AInfo*) pAInfoList->GetObject( 0L );
//STRIP001
//STRIP001                                         pAInfo->aStartOrg = aDrawRect.TopLeft();
//STRIP001                                         pAInfo->aStartSize = aDrawRect.GetSize();
//STRIP001                                         pAInfo->pOutDev = pOut;
//STRIP001                                         pAInfo->nExtraData = 1;
//STRIP001                                         pAInfo->bPause = ( bMrk || bPause );
//STRIP001
//STRIP001                                         pAInfoList->Insert(pAInfo);
//STRIP001                                     }
//STRIP001                                 }
//STRIP001                             }
//STRIP001                         }
//STRIP001                     }
//STRIP001                 }
//STRIP001             }
//STRIP001         }
//STRIP001     }
//STRIP001
//STRIP001     // Alle Objekte mit nicht gesetztem Flag loeschen
//STRIP001     pAInfo = (AInfo*) pAInfoList->First();
//STRIP001
//STRIP001  while( pAInfo != NULL )
//STRIP001  {
//STRIP001         if( pAInfo->nExtraData == 0 )
//STRIP001      {
//STRIP001             delete (AInfo*)pAInfoList->Remove(pAInfo);
//STRIP001             pAInfo=(AInfo*)pAInfoList->GetCurObject();
//STRIP001         }
//STRIP001      else
//STRIP001             pAInfo=(AInfo*)pAInfoList->Next();
//STRIP001     }
//STRIP001
//STRIP001     return 0;
//STRIP001 }

}
