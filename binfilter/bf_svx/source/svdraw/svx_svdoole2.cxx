/*************************************************************************
 *
 *  $RCSfile: svx_svdoole2.cxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:22:29 $
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

#ifndef _COM_SUN_STAR_UTIL_XMODIFYBROADCASTER_HPP_
#include <com/sun/star/util/XModifyBroadcaster.hpp>
#endif

#include <comphelper/processfactory.hxx>

#ifndef _IPOBJ_HXX //autogen
#include <so3/ipobj.hxx>
#endif
#ifndef _PERSIST_HXX
#include <so3/persist.hxx>
#endif
#ifndef _SFX_INTERNO_HXX
#include <bf_sfx2/interno.hxx>
#endif
#ifndef _SVDPAGV_HXX
#include <svdpagv.hxx>
#endif
#ifndef _GLOBNAME_HXX
#include <tools/globname.hxx>
#endif
#ifndef _IPCLIENT_HXX //autogen
#include <so3/ipclient.hxx>
#endif
#ifndef _SV_JOBSET_HXX
#include <vcl/jobset.hxx>
#endif
#ifndef _SO_CLSIDS_HXX
#include <so3/clsids.hxx>
#endif

#include <sot/formats.hxx>

#ifndef _IPENV_HXX //autogen
#include <so3/ipenv.hxx>
#endif
#ifndef _PSEUDO_HXX
#include <so3/pseudo.hxx>
#endif
#ifndef _SVXLINKMGR_HXX //autogen
#include <linkmgr.hxx>
#endif
#ifndef SVTOOLS_TRANSFER_HXX
#include <svtools/transfer.hxx>
#endif


#include "svdoole2.hxx"
#include <svtools/solar.hrc>
#include "svdxout.hxx"
#ifndef SVTOOLS_URIHELPER_HXX
#include <svtools/urihelper.hxx>
#endif

#include "svdpagv.hxx"
#include "svdmodel.hxx"
#include "svdio.hxx"
#include "svdglob.hxx"  // Stringcache
#include "svdstr.hrc"   // Objektname
#include "svdetc.hxx"
#include "svdview.hxx"
#include "unomlstr.hxx"

using namespace ::rtl;
using namespace ::com::sun::star;

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef SO2_DECL_SVINPLACEOBJECT_DEFINED
#define SO2_DECL_SVINPLACEOBJECT_DEFINED
SO2_DECL_REF(SvInPlaceObject)
#endif

/*N*/ class SdrOle2ObjImpl
/*N*/ {
/*N*/ public:
/*N*/   GDIMetaFile*    pMetaFile;          // Metafile fuer GetMtf kopieren und merken
/*N*/   GraphicObject*  pGraphicObject;
/*N*/   String          aPersistName;       // name of object in persist
/*N*/
/*N*/   // #107645#
/*N*/   // New local var to avoid repeated loading if load of OLE2 fails
/*N*/   sal_Bool        mbLoadingOLEObjectFailed;
/*N*/
/*N*/   bool    mbConnected;
/*N*/
/*N*/ };

////////////////////////////////////////////////////////////////////////////////////////////////////

// Predicate determining whether the given OLE is an internal math
// object
/*N*/ static bool ImplIsMathObj( const SvInPlaceObjectRef& rObjRef )
/*N*/ {
/*N*/     if( !rObjRef.Is() )
/*N*/         return false;
/*N*/
/*N*/     SvGlobalName aClassName( rObjRef->GetClassName() );
/*N*/
/*N*/     if( aClassName == SvGlobalName(BF_SO3_SM_CLASSID_30) ||
/*N*/         aClassName == SvGlobalName(BF_SO3_SM_CLASSID_40) ||
/*N*/         aClassName == SvGlobalName(BF_SO3_SM_CLASSID_50) ||
/*N*/         aClassName == SvGlobalName(BF_SO3_SM_CLASSID_60) ||
/*N*/         aClassName == SvGlobalName(BF_SO3_SM_CLASSID)         )
/*N*/     {
/*N*/         return true;
/*N*/     }
/*N*/     else
/*N*/     {
/*N*/         return false;
/*N*/     }
/*N*/ }

// -----------------------------------------------------------------------------

/*N*/ TYPEINIT1(SdrOle2Obj,SdrRectObj);
/*N*/
/*N*/ SdrOle2Obj::SdrOle2Obj(FASTBOOL bFrame_)
/*N*/ {
/*N*/   bInDestruction = FALSE;
/*N*/   Init();
/*N*/
/*N*/   ppObjRef=new SvInPlaceObjectRef;
/*N*/   bFrame=bFrame_;
/*N*/ }

// -----------------------------------------------------------------------------

//STRIP001 SdrOle2Obj::SdrOle2Obj(const SvInPlaceObjectRef& rNewObjRef, FASTBOOL bFrame_)
//STRIP001 {
//STRIP001  bInDestruction = FALSE;
//STRIP001  Init();
//STRIP001  ppObjRef=new SvInPlaceObjectRef(rNewObjRef);
//STRIP001
//STRIP001  bFrame=bFrame_;
//STRIP001
//STRIP001  SvInPlaceObjectRef& rIPRef = *ppObjRef;
//STRIP001
//STRIP001  if (rIPRef.Is() &&
//STRIP001      (rIPRef->GetMiscStatus() & SVOBJ_MISCSTATUS_NOTRESIZEABLE) )
//STRIP001  {
//STRIP001      SetResizeProtect(TRUE);
//STRIP001  }
//STRIP001
//STRIP001     // #108759# For math objects, set closed state to transparent
//STRIP001     if( ImplIsMathObj( *ppObjRef ) )
//STRIP001         SetClosedObj( false );
//STRIP001 }

// -----------------------------------------------------------------------------

/*N*/ SdrOle2Obj::SdrOle2Obj(const SvInPlaceObjectRef& rNewObjRef, const XubString& rNewObjName, FASTBOOL bFrame_)
/*N*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  bInDestruction = FALSE;
//STRIP001  Init();
//STRIP001
//STRIP001  ppObjRef=new SvInPlaceObjectRef(rNewObjRef);
//STRIP001
//STRIP001  mpImpl->aPersistName = rNewObjName;
//STRIP001  bFrame=bFrame_;
//STRIP001
//STRIP001  SvInPlaceObjectRef& rIPRef = *ppObjRef;
//STRIP001
//STRIP001  if (rIPRef.Is() &&
//STRIP001      (rIPRef->GetMiscStatus() & SVOBJ_MISCSTATUS_NOTRESIZEABLE) )
//STRIP001  {
//STRIP001      SetResizeProtect(TRUE);
//STRIP001  }
//STRIP001
//STRIP001     // #108759# For math objects, set closed state to transparent
//STRIP001     if( ImplIsMathObj( *ppObjRef ) )
//STRIP001         SetClosedObj( false );
/*N*/ }

// -----------------------------------------------------------------------------

/*N*/ SdrOle2Obj::SdrOle2Obj(const SvInPlaceObjectRef& rNewObjRef, const XubString& rNewObjName, const Rectangle& rNewRect, FASTBOOL bFrame_):
/*N*/   SdrRectObj(rNewRect)
/*N*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  bInDestruction = FALSE;
//STRIP001  Init();
//STRIP001
//STRIP001  ppObjRef=new SvInPlaceObjectRef(rNewObjRef);
//STRIP001
//STRIP001  mpImpl->aPersistName = rNewObjName;
//STRIP001  bFrame=bFrame_;
//STRIP001
//STRIP001  SvInPlaceObjectRef& rIPRef = *ppObjRef;
//STRIP001
//STRIP001  if (rIPRef.Is() &&
//STRIP001      (rIPRef->GetMiscStatus() & SVOBJ_MISCSTATUS_NOTRESIZEABLE) )
//STRIP001  {
//STRIP001      SetResizeProtect(TRUE);
//STRIP001  }
//STRIP001
//STRIP001     // #108759# For math objects, set closed state to transparent
//STRIP001     if( ImplIsMathObj( *ppObjRef ) )
//STRIP001         SetClosedObj( false );
/*N*/ }

// -----------------------------------------------------------------------------

/*N*/ void SdrOle2Obj::Init()
/*N*/ {
/*N*/   mpImpl = new SdrOle2ObjImpl;
/*N*/   pModifyListener = NULL;
/*N*/   pGraphic=NULL;
/*N*/   mpImpl->pMetaFile=NULL;
/*N*/   mpImpl->pGraphicObject=NULL;
/*N*/
/*N*/   // #107645#
/*N*/   // init to start situation, loading did not fail
/*N*/   mpImpl->mbLoadingOLEObjectFailed = sal_False;
/*N*/
/*N*/   mpImpl->mbConnected = false;
/*N*/ }

// -----------------------------------------------------------------------------

/*N*/ SdrOle2Obj::~SdrOle2Obj()
/*N*/ {
/*N*/   bInDestruction = TRUE;
/*N*/   // Aus Cache entfernen
/*N*/   GetSdrGlobalData().GetOLEObjCache().RemoveObj(this);
/*N*/
/*N*/   SvInPlaceObjectRef aRef( *ppObjRef );
/*N*/
/*N*/   Disconnect();
/*N*/
/*N*/   if(pModel && aRef.Is())
/*N*/   {
/*N*/       SvPersist* pPers=pModel->GetPersist();
/*N*/       if(pPers!=NULL)
/*N*/       {
/*?*/           pPers->Remove(aRef);
/*N*/       }
/*N*/   }
/*N*/   aRef.Clear();
/*N*/
/*N*/   delete ppObjRef;
/*N*/
/*N*/   if(pGraphic!=NULL)
/*?*/       delete pGraphic;
/*N*/
/*N*/   if(mpImpl->pMetaFile!=NULL)
/*?*/       delete mpImpl->pMetaFile;
/*N*/
/*N*/   if(mpImpl->pGraphicObject!=NULL)
/*?*/       delete mpImpl->pGraphicObject;
/*N*/
/*N*/   if(pModifyListener)
/*N*/   {
/*N*/       pModifyListener->invalidate();
/*N*/       pModifyListener->release();
/*N*/       pModifyListener = NULL;
/*N*/   }
/*N*/   delete mpImpl;
/*N*/ }

// -----------------------------------------------------------------------------

/*N*/ void SdrOle2Obj::SetGraphic(const Graphic* pGrf)
/*N*/ {
/*N*/   if ( pGraphic )
/*N*/   {
/*?*/       delete pGraphic;
/*?*/       pGraphic = NULL;
/*?*/       delete mpImpl->pGraphicObject;
/*?*/       mpImpl->pGraphicObject = NULL;
/*N*/   }
/*N*/
/*N*/   if (pGrf!=NULL)
/*N*/   {
/*?*/       pGraphic = new Graphic(*pGrf);
/*?*/       mpImpl->pGraphicObject = new GraphicObject( *pGraphic );
/*N*/   }
/*N*/
/*N*/   if ( ppObjRef->Is() && pGrf )
/*?*/       SendRepaintBroadcast();
/*N*/
/*N*/   SetChanged();
/*N*/ }

// -----------------------------------------------------------------------------

/*N*/ FASTBOOL SdrOle2Obj::IsEmpty() const
/*N*/ {
/*N*/   return !ppObjRef->Is();
/*N*/ }

// -----------------------------------------------------------------------------

/*N*/ void SdrOle2Obj::Connect()
/*N*/ {
/*N*/   if(pModel && mpImpl->aPersistName.Len())
/*N*/   {
/*N*/       SvPersist* pPers=pModel->GetPersist();
/*N*/       if (pPers!=NULL)
/*N*/       {
/*N*/           SvInfoObjectRef xIObj;
/*N*/           SvInfoObject* pInfo = pPers->Find(mpImpl->aPersistName);
/*N*/
/*N*/           if (!pInfo)
/*N*/           {
/*?*/               if ( !ppObjRef->Is() )
/*?*/                   GetObjRef();    // try to load inplace object
/*?*/
/*?*/               xIObj = pInfo = new SvEmbeddedInfoObject(*ppObjRef,mpImpl->aPersistName);
/*N*/           }
/*N*/
/*N*/           if ( !pPers->HasObject(mpImpl->aPersistName) )
/*N*/           {
/*?*/               pPers->Move(pInfo, mpImpl->aPersistName);
/*N*/           }
/*N*/           else
/*N*/           {
/*N*/               pInfo->SetDeleted(FALSE);
/*N*/           }
/*N*/       }
/*N*/
/*N*/       // In Cache einfuegen
/*N*/       GetSdrGlobalData().GetOLEObjCache().InsertObj(this);
/*N*/   }
/*N*/
/*N*/   if ( ppObjRef->Is() && (*ppObjRef)->GetMiscStatus() & SVOBJ_MISCSTATUS_RESIZEONPRINTERCHANGE )
/*N*/   {
/*N*/       if (pModel && pModel->GetRefDevice() &&
/*N*/           pModel->GetRefDevice()->GetOutDevType() == OUTDEV_PRINTER)
/*N*/       {
/*?*/           // Kein RefDevice oder RefDevice kein Printer
/*?*/           BOOL bModified = (*ppObjRef)->IsModified();
/*?*/           Printer* pPrinter = (Printer*) pModel->GetRefDevice();
/*?*/           (*ppObjRef)->OnDocumentPrinterChanged( pPrinter );
/*?*/           (*ppObjRef)->SetModified( bModified );
/*N*/       }
/*N*/   }
/*N*/
/*N*/   if( !IsEmpty() )
/*N*/   {
/*?*/       // register modify listener
/*?*/       if( pModifyListener == NULL )
/*?*/       {
/*?*/           ((SdrOle2Obj*)this)->pModifyListener = new SvxUnoShapeModifyListener( (SdrOle2Obj*)this );
/*?*/           pModifyListener->acquire();
/*?*/       }
/*?*/
/*?*/       uno::Reference< util::XModifyBroadcaster > xBC( getXModel(), uno::UNO_QUERY );
/*?*/       if( xBC.is() && pModifyListener )
/*?*/       {
/*?*/           uno::Reference< util::XModifyListener > xListener( pModifyListener );
/*?*/           xBC->addModifyListener( xListener );
/*?*/       }
/*?*/
/*?*/       mpImpl->mbConnected = true;
/*N*/   }
/*N*/ }

// -----------------------------------------------------------------------------

/*N*/ void SdrOle2Obj::Disconnect()
/*N*/ {
/*N*/   if( !mpImpl->mbConnected )
/*N*/       return;
/*N*/
/*N*/   if( !IsEmpty() && mpImpl->aPersistName.Len() )
/*N*/   {
/*N*/       uno::Reference< util::XModifyBroadcaster > xBC( getXModel(), uno::UNO_QUERY );
/*N*/       if( xBC.is() && pModifyListener )
/*N*/       {
/*N*/           uno::Reference< util::XModifyListener > xListener( pModifyListener );
/*N*/           xBC->removeModifyListener( xListener );
/*N*/       }
/*N*/   }
/*N*/
/*N*/   if (pModel && mpImpl->aPersistName.Len() )
/*N*/   {
/*N*/       if( pModel->IsInDestruction() )
/*N*/       {
/*N*/           *ppObjRef = NULL;
/*N*/       }
/*N*/       else
/*N*/       {
/*N*/           SvPersist* pPers = pModel->GetPersist();
/*N*/
/*N*/           if (pPers)
/*N*/           {
/*N*/               SvInfoObject* pInfo = pPers->Find(mpImpl->aPersistName);
/*N*/
/*N*/               if (pInfo)
/*N*/               {
/*N*/                   pInfo->SetDeleted(TRUE);
/*N*/                   pInfo->SetObj(0);
/*N*/               }
/*N*/           }
/*N*/
/*N*/           if ( ppObjRef->Is() )
/*N*/               (*ppObjRef)->DoClose();
/*N*/       }
/*N*/
/*N*/       // Aus Cache entfernen
/*N*/       GetSdrGlobalData().GetOLEObjCache().RemoveObj(this);
/*N*/
/*N*/       if ( ppObjRef->Is() )
/*N*/           ppObjRef->Clear();
/*N*/   }
/*N*/
/*N*/   mpImpl->mbConnected = false;
/*N*/ }

// -----------------------------------------------------------------------------

/*N*/ void SdrOle2Obj::SetModel(SdrModel* pNewModel)
/*N*/ {
/*N*/   FASTBOOL bChg = pNewModel!=pModel;
/*N*/
/*N*/   if( bChg )
/*N*/         Disconnect(); // mit dem alten Namen
/*N*/
/*N*/   if( pModel && pNewModel )
/*N*/   {
/*?*/       SvPersist* pDestPers = pNewModel->GetPersist();
/*?*/       SvPersist* pSrcPers  = pModel->GetPersist();
/*?*/
/*?*/       if( pDestPers && pSrcPers && ( pDestPers != pSrcPers ) )
/*?*/       {
/*?*/               {DBG_ASSERT(0, "STRIP");} //STRIP001 ImpCopyObject( *pSrcPers, *pDestPers, mpImpl->aPersistName );
/*?*/       }
/*N*/   }
/*N*/
/*N*/   SdrRectObj::SetModel( pNewModel );
/*N*/
/*N*/   if( bChg )
/*N*/         Connect();
/*N*/ }

// -----------------------------------------------------------------------------

/*N*/ void SdrOle2Obj::SetPage(SdrPage* pNewPage)
/*N*/ {
/*N*/   FASTBOOL bRemove=pNewPage==NULL && pPage!=NULL;
/*N*/   FASTBOOL bInsert=pNewPage!=NULL && pPage==NULL;
/*N*/
/*N*/   if (bRemove) Disconnect();
/*N*/
/*N*/   SdrRectObj::SetPage(pNewPage);
/*N*/
/*N*/   if (bInsert) Connect();
/*N*/ }

// -----------------------------------------------------------------------------

/*N*/ void SdrOle2Obj::SetObjRef(const SvInPlaceObjectRef& rNewObjRef)
/*N*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  if( rNewObjRef == *ppObjRef )
//STRIP001      return;
//STRIP001
//STRIP001  Disconnect();
//STRIP001
//STRIP001  *ppObjRef=rNewObjRef;
//STRIP001
//STRIP001  SvInPlaceObjectRef& rIPRef = *ppObjRef;
//STRIP001
//STRIP001  if (rIPRef.Is() &&
//STRIP001      (rIPRef->GetMiscStatus() & SVOBJ_MISCSTATUS_NOTRESIZEABLE) )
//STRIP001  {
//STRIP001      SetResizeProtect(TRUE);
//STRIP001  }
//STRIP001
//STRIP001     // #108759# For math objects, set closed state to transparent
//STRIP001     if( ImplIsMathObj( *ppObjRef ) )
//STRIP001         SetClosedObj( false );
//STRIP001
//STRIP001  Connect();
//STRIP001  SetChanged();
//STRIP001  SendRepaintBroadcast();
/*N*/ }

// -----------------------------------------------------------------------------

/*N*/ void SdrOle2Obj::SetClosedObj( bool bIsClosed )
/*N*/ {
/*N*/     // #108759# Allow changes to the closed state of OLE objects
/*N*/     bClosedObj = bIsClosed;
/*N*/ }

// -----------------------------------------------------------------------------

//STRIP001 FASTBOOL SdrOle2Obj::HasSetName() const
//STRIP001 {
//STRIP001  return TRUE;
//STRIP001 }

// -----------------------------------------------------------------------------

//STRIP001 void SdrOle2Obj::SetName(const XubString& rStr)
//STRIP001 {
//STRIP001  aName = rStr;
//STRIP001  SetChanged();
//STRIP001 }

// -----------------------------------------------------------------------------

/*N*/ XubString SdrOle2Obj::GetName() const
/*N*/ {
/*N*/   return aName;
/*N*/ }

// -----------------------------------------------------------------------------

/*N*/ void SdrOle2Obj::SetPersistName( const String& rPersistName )
/*N*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001     mpImpl->aPersistName = rPersistName;
//STRIP001  SetChanged();
/*N*/ }

// -----------------------------------------------------------------------------

/*N*/ String SdrOle2Obj::GetPersistName() const
/*N*/ {
/*N*/     return mpImpl->aPersistName;
/*N*/ }

// -----------------------------------------------------------------------------

//STRIP001 void SdrOle2Obj::TakeObjInfo(SdrObjTransformInfoRec& rInfo) const
//STRIP001 {
//STRIP001  rInfo.bRotateFreeAllowed=FALSE;
//STRIP001  rInfo.bRotate90Allowed  =FALSE;
//STRIP001  rInfo.bMirrorFreeAllowed=FALSE;
//STRIP001  rInfo.bMirror45Allowed  =FALSE;
//STRIP001  rInfo.bMirror90Allowed  =FALSE;
//STRIP001  rInfo.bTransparenceAllowed = FALSE;
//STRIP001  rInfo.bGradientAllowed = FALSE;
//STRIP001  rInfo.bShearAllowed     =FALSE;
//STRIP001  rInfo.bEdgeRadiusAllowed=FALSE;
//STRIP001  rInfo.bNoOrthoDesired   =FALSE;
//STRIP001  rInfo.bCanConvToPath    =FALSE;
//STRIP001  rInfo.bCanConvToPoly    =FALSE;
//STRIP001  rInfo.bCanConvToPathLineToArea=FALSE;
//STRIP001  rInfo.bCanConvToPolyLineToArea=FALSE;
//STRIP001  rInfo.bCanConvToContour = FALSE;
//STRIP001 }

// -----------------------------------------------------------------------------

/*N*/ UINT16 SdrOle2Obj::GetObjIdentifier() const
/*N*/ {
/*N*/   return bFrame ? UINT16(OBJ_FRAME) : UINT16(OBJ_OLE2);
/*N*/ }

// -----------------------------------------------------------------------------

//STRIP001 FASTBOOL SdrOle2Obj::Paint(ExtOutputDevice& rOut, const SdrPaintInfoRec& rInfoRec) const
//STRIP001 {
//STRIP001  FASTBOOL bOk=TRUE;
//STRIP001
//STRIP001  if( !pGraphic )
//STRIP001      GetObjRef();    // try to load inplace object
//STRIP001
//STRIP001  if (ppObjRef->Is())
//STRIP001  {
//STRIP001      if( !bSizProt && (*ppObjRef)->GetMiscStatus() & SVOBJ_MISCSTATUS_NOTRESIZEABLE )
//STRIP001          ( (SdrOle2Obj*) this)->bSizProt = TRUE;
//STRIP001
//STRIP001      const SvEditObjectProtocol& rProt=(*ppObjRef)->GetProtocol();
//STRIP001
//STRIP001      OutputDevice* pOut=rOut.GetOutDev();
//STRIP001
//STRIP001      if (!rProt.IsInPlaceActive() || (*ppObjRef)->GetIPClient()->GetEnv()->GetEditWin()!=pOut)
//STRIP001      {
//STRIP001          if ((rInfoRec.nPaintMode & SDRPAINTMODE_DRAFTGRAF) ==0)
//STRIP001          {
//STRIP001              if (((*ppObjRef)->GetMiscStatus() & SVOBJ_MISCSTATUS_ACTIVATEWHENVISIBLE))
//STRIP001              {
//STRIP001                  // PlugIn-Objekt connecten
//STRIP001                  if (rInfoRec.pPV!=NULL)
//STRIP001                  {
//STRIP001                      SdrOle2Obj* pOle2Obj = (SdrOle2Obj*) this;
//STRIP001                      SdrView* pSdrView = (SdrView*) &rInfoRec.pPV->GetView();
//STRIP001                      pSdrView->DoConnect(pOle2Obj);
//STRIP001                  }
//STRIP001              }
//STRIP001
//STRIP001
//STRIP001              // don't call DoDraw if this ís a special object and SDRPAINTMODE_HIDEDRAFTGRAF is set
//STRIP001                 if( ( ( (*ppObjRef)->GetMiscStatus() & SVOBJ_MISCSTATUS_SPECIALOBJECT ) == 0 ) ||
//STRIP001                     ( ( rInfoRec.nPaintMode & SDRPAINTMODE_HIDEDRAFTGRAF ) == 0 ) )
//STRIP001                 {
//STRIP001                     // #108759# Temporarily set the current background
//STRIP001                     // color, since OLEs rely on that during
//STRIP001                     // auto-colored text rendering
//STRIP001                     Wallpaper aOldBg( pOut->GetBackground() );
//STRIP001
//STRIP001                     if( rInfoRec.pPV && GetPage() )
//STRIP001                         pOut->SetBackground( rInfoRec.pPV->GetView().CalcBackgroundColor( GetSnapRect(),
//STRIP001                                                                                           rInfoRec.pPV->GetVisibleLayers(),
//STRIP001                                                                                           *GetPage() ) );
//STRIP001
//STRIP001                     pOut->Push( PUSH_CLIPREGION );
//STRIP001                  pOut->IntersectClipRegion( aRect );
//STRIP001                  (*ppObjRef)->DoDraw(pOut,aRect.TopLeft(),aRect.GetSize(),JobSetup());
//STRIP001                     pOut->Pop();
//STRIP001
//STRIP001                     // #108759# Restore old background
//STRIP001                     pOut->SetBackground( aOldBg );
//STRIP001                 }
//STRIP001          }
//STRIP001          else if( ( rInfoRec.nPaintMode & SDRPAINTMODE_HIDEDRAFTGRAF ) == 0 )
//STRIP001          { // sonst SDRPAINTMODE_DRAFTGRAF
//STRIP001              Polygon aPoly(Rect2Poly(aRect,aGeo));
//STRIP001              pOut->SetLineColor(Color(COL_BLACK));
//STRIP001              pOut->DrawPolyLine(aPoly);
//STRIP001              pOut->DrawLine(aPoly[0],aPoly[2]);
//STRIP001              pOut->DrawLine(aPoly[1],aPoly[3]);
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  else if ( pGraphic )
//STRIP001  {
//STRIP001      OutputDevice* pOutDev=rOut.GetOutDev();
//STRIP001      if( IsEmptyPresObj() )
//STRIP001      {
//STRIP001          const MapMode   aDstMapMode( pOutDev->GetMapMode().GetMapUnit() );
//STRIP001          Point           aPos(aRect.Center());
//STRIP001          Size            aDstSize;
//STRIP001
//STRIP001          if( pGraphic->GetPrefMapMode().GetMapUnit() == MAP_PIXEL )
//STRIP001              aDstSize = pOutDev->PixelToLogic( pGraphic->GetPrefSize(), aDstMapMode );
//STRIP001          else
//STRIP001              aDstSize = pOutDev->LogicToLogic( pGraphic->GetPrefSize(), pGraphic->GetPrefMapMode(), aDstMapMode );
//STRIP001
//STRIP001          aPos.X()-=aDstSize.Width() /2;
//STRIP001          aPos.Y()-=aDstSize.Height()/2;
//STRIP001          if (aPos.X() >= aRect.Left() && aPos.Y() >= aRect.Top())
//STRIP001              pGraphic->Draw(pOutDev,aPos, aDstSize);
//STRIP001
//STRIP001             svtools::ColorConfig aColorConfig;
//STRIP001             svtools::ColorConfigValue aColor( aColorConfig.GetColorValue( svtools::OBJECTBOUNDARIES ) );
//STRIP001
//STRIP001          if( aColor.bIsVisible )
//STRIP001          {
//STRIP001              pOutDev->SetFillColor();
//STRIP001              pOutDev->SetLineColor( aColor.nColor );
//STRIP001              pOutDev->DrawRect(aRect);
//STRIP001          }
//STRIP001      }
//STRIP001      else
//STRIP001          pGraphic->Draw( pOutDev, aRect.TopLeft(), aRect.GetSize() );
//STRIP001  }
//STRIP001  // #100499# OLE without context and without bitmap, do the same as
//STRIP001  // for empty groups, additionally draw empty OLE bitmap
//STRIP001  else
//STRIP001  {
//STRIP001      if(!rInfoRec.bPrinter && rInfoRec.aPaintLayer.IsSet(nLayerId))
//STRIP001      {
//STRIP001          OutputDevice* pOutDev = rOut.GetOutDev();
//STRIP001
//STRIP001          pOutDev->SetFillInBrush(Brush(BRUSH_NULL));
//STRIP001          pOutDev->SetPen(Color(COL_LIGHTGRAY));
//STRIP001          pOutDev->DrawRect(aOutRect);
//STRIP001
//STRIP001          Bitmap aBitmap(ResId(BMP_OLEOBJ, ImpGetResMgr()));
//STRIP001          Rectangle aSnapRect(GetSnapRect());
//STRIP001          Size aBitmapSize(pOutDev->PixelToLogic(aBitmap.GetSizePixel()));
//STRIP001
//STRIP001          pOutDev->DrawBitmap(
//STRIP001              aSnapRect.Center() - Point(aBitmapSize.Width() / 2, aBitmapSize.Height() / 2),
//STRIP001              aBitmapSize,
//STRIP001              aBitmap);
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if (HasText())
//STRIP001  {
//STRIP001      bOk=SdrTextObj::Paint(rOut,rInfoRec);
//STRIP001  }
//STRIP001  return bOk;
//STRIP001 }

// -----------------------------------------------------------------------------

/*N*/ SdrObject* SdrOle2Obj::CheckHit(const Point& rPnt, USHORT nTol, const SetOfByte* pVisiLayer) const
/*N*/ {
/*N*/   return ImpCheckHit(rPnt,nTol,pVisiLayer,TRUE,TRUE);
/*N*/ }

// -----------------------------------------------------------------------------

//STRIP001 void SdrOle2Obj::TakeObjNameSingul(XubString& rName) const
//STRIP001 {
//STRIP001  rName = ImpGetResStr(bFrame ? STR_ObjNameSingulFrame : STR_ObjNameSingulOLE2);
//STRIP001
//STRIP001  if( aName.Len() )
//STRIP001  {
//STRIP001      rName.AppendAscii(" '");
//STRIP001      rName += aName;
//STRIP001      rName += sal_Unicode('\'');
//STRIP001  }
//STRIP001 }

// -----------------------------------------------------------------------------

//STRIP001 void SdrOle2Obj::TakeObjNamePlural(XubString& rName) const
//STRIP001 {
//STRIP001  rName=ImpGetResStr(bFrame ? STR_ObjNamePluralFrame : STR_ObjNamePluralOLE2);
//STRIP001 }

// -----------------------------------------------------------------------------

//STRIP001 void SdrOle2Obj::ImpAssign( const SdrObject& rObj, SdrPage* pNewPage, SdrModel* pNewModel )
//STRIP001 {
//STRIP001     const SdrOle2Obj& rOle2Obj = static_cast< const SdrOle2Obj& >( rObj );
//STRIP001
//STRIP001  if( pModel )
//STRIP001         Disconnect();
//STRIP001
//STRIP001     SdrRectObj::operator=( rObj );
//STRIP001
//STRIP001     // #108867# Manually copying bClosedObj attribute
//STRIP001     SetClosedObj( rObj.IsClosedObj() );
//STRIP001
//STRIP001     if( pNewPage )
//STRIP001         pPage = pNewPage;
//STRIP001
//STRIP001     if( pNewModel )
//STRIP001         pModel = pNewModel;
//STRIP001
//STRIP001     aName = rOle2Obj.aName;
//STRIP001  mpImpl->aPersistName = rOle2Obj.mpImpl->aPersistName;
//STRIP001  aProgName = rOle2Obj.aProgName;
//STRIP001  bFrame = rOle2Obj.bFrame;
//STRIP001
//STRIP001  if( rOle2Obj.pGraphic )
//STRIP001  {
//STRIP001      if( pGraphic )
//STRIP001      {
//STRIP001          delete pGraphic;
//STRIP001          delete mpImpl->pGraphicObject;
//STRIP001      }
//STRIP001
//STRIP001         pGraphic = new Graphic( *rOle2Obj.pGraphic );
//STRIP001      mpImpl->pGraphicObject = new GraphicObject( *pGraphic );
//STRIP001  }
//STRIP001
//STRIP001  if( pModel && rObj.GetModel() )
//STRIP001     {
//STRIP001      SvPersist* pDestPers = pModel->GetPersist();
//STRIP001      SvPersist* pSrcPers = rObj.GetModel()->GetPersist();
//STRIP001
//STRIP001         if( pDestPers && pSrcPers )
//STRIP001         {
//STRIP001             ImpCopyObject( *pSrcPers, *pDestPers, mpImpl->aPersistName );
//STRIP001
//STRIP001             if( rOle2Obj.ppObjRef->Is() && ppObjRef->Is() &&
//STRIP001                 ( (*rOle2Obj.ppObjRef)->GetMapUnit() == (*ppObjRef)->GetMapUnit() ) )
//STRIP001             {
//STRIP001                     (*ppObjRef)->SetVisArea( (*rOle2Obj.ppObjRef)->GetVisArea() );
//STRIP001             }
//STRIP001         }
//STRIP001
//STRIP001         Connect();
//STRIP001  }
//STRIP001 }

// -----------------------------------------------------------------------------

//STRIP001 void SdrOle2Obj::ImpCopyObject( SvPersist& rSrcPersist, SvPersist& rDstPersist, String& rPersistName )
//STRIP001 {
//STRIP001     SvInfoObject* pInfo = rSrcPersist.Find( rPersistName );
//STRIP001
//STRIP001     if( pInfo != NULL )
//STRIP001     {
//STRIP001         SvPersistRef    xNewRef;
//STRIP001         const String    aOldPersistName( rPersistName );
//STRIP001
//STRIP001      // loop because of storage bug 46033
//STRIP001      for( USHORT i = 1, n = 0; n < 100; i++, n++ )
//STRIP001      {
//STRIP001          String aStr( rPersistName = OUString::createFromAscii( "Object " ) );
//STRIP001
//STRIP001             aStr += String::CreateFromInt32( i );
//STRIP001
//STRIP001             while( rDstPersist.Find( aStr ) )
//STRIP001             {
//STRIP001              aStr = rPersistName;
//STRIP001              aStr += String::CreateFromInt32( ++i );
//STRIP001          }
//STRIP001
//STRIP001             xNewRef = rDstPersist.CopyObject( aOldPersistName, rPersistName = aStr, &rSrcPersist );
//STRIP001
//STRIP001             if( xNewRef.Is() )
//STRIP001              break;
//STRIP001      }
//STRIP001
//STRIP001      *ppObjRef = &rDstPersist.GetObject( rPersistName );
//STRIP001  }
//STRIP001 }

// -----------------------------------------------------------------------------

//STRIP001 void SdrOle2Obj::operator=(const SdrObject& rObj)
//STRIP001 {
//STRIP001     if( &rObj != this )
//STRIP001         ImpAssign( rObj );
//STRIP001 }

// -----------------------------------------------------------------------------

//STRIP001 SdrObject* SdrOle2Obj::Clone( SdrPage* pNewPage, SdrModel* pNewModel ) const
//STRIP001 {
//STRIP001  SdrOle2Obj* pObj = static_cast< SdrOle2Obj* >( SdrObjFactory::MakeNewObject( GetObjInventor(), GetObjIdentifier(),NULL ) );
//STRIP001
//STRIP001     if( pObj )
//STRIP001     {
//STRIP001         pObj->ImpAssign( *this, pNewPage, pNewModel );
//STRIP001
//STRIP001         if( pNewModel )
//STRIP001          pObj->SetModel( pNewModel );
//STRIP001     }
//STRIP001
//STRIP001  return pObj;
//STRIP001 }

// -----------------------------------------------------------------------------

//STRIP001 FASTBOOL SdrOle2Obj::HasSpecialDrag() const
//STRIP001 {
//STRIP001  return FALSE;
//STRIP001 }

// -----------------------------------------------------------------------------

//STRIP001 void SdrOle2Obj::ImpSetVisAreaSize()
//STRIP001 {
//STRIP001  GetObjRef();    // try to load inplace object
//STRIP001  SvInPlaceObjectRef& rIPRef=*ppObjRef;
//STRIP001
//STRIP001  if (rIPRef.Is())
//STRIP001  {
//STRIP001      if (rIPRef->GetMiscStatus() & SVOBJ_MISCSTATUS_SERVERRESIZE)
//STRIP001      {
//STRIP001          // Server resized selbst (StarChart)
//STRIP001          // Neue VisArea setzen
//STRIP001          Rectangle aVisArea = OutputDevice::LogicToLogic( aRect,
//STRIP001                                  pModel->GetScaleUnit(), rIPRef->GetMapUnit() );
//STRIP001          rIPRef->SetVisArea(aVisArea);
//STRIP001
//STRIP001          // Wurde die VisArea akzeptiert?
//STRIP001          Rectangle aAcceptedVisArea(rIPRef->GetVisArea());
//STRIP001
//STRIP001          if (aVisArea.GetSize() != aAcceptedVisArea.GetSize())
//STRIP001          {
//STRIP001              // VisArea wurde nicht akzeptiert -> korrigieren
//STRIP001              aRect.SetSize(OutputDevice::LogicToLogic( aAcceptedVisArea.GetSize(),
//STRIP001                      rIPRef->GetMapUnit(), pModel->GetScaleUnit()));
//STRIP001          }
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          /**********************************************************************
//STRIP001          * Nun wird nicht mehr die VisArea gesetzt, sondern es erfolgt eine
//STRIP001          * Skalierung
//STRIP001          **********************************************************************/
//STRIP001          SvEmbeddedClient* pClient = (*ppObjRef)->GetClient();
//STRIP001
//STRIP001          if (pClient)
//STRIP001          {
//STRIP001              SvClientData* pData = pClient->GetClientData();
//STRIP001              Size aObjAreaSize = rIPRef->GetVisArea().GetSize();
//STRIP001              aObjAreaSize = OutputDevice::LogicToLogic( aObjAreaSize,
//STRIP001                                                         rIPRef->GetMapUnit(),
//STRIP001                                                         pModel->GetScaleUnit() );
//STRIP001
//STRIP001              Size aSize = aRect.GetSize();
//STRIP001              Fraction aScaleWidth (aSize.Width(),  aObjAreaSize.Width() );
//STRIP001              Fraction aScaleHeight(aSize.Height(), aObjAreaSize.Height() );
//STRIP001              // Nun auf 10 Binaerstellen kuerzen
//STRIP001              Kuerzen(aScaleHeight, 10);
//STRIP001              Kuerzen(aScaleWidth,  10);
//STRIP001
//STRIP001              pData->SetSizeScale(aScaleWidth, aScaleHeight);
//STRIP001
//STRIP001              Rectangle aScaleRect(aRect.TopLeft(), aObjAreaSize);
//STRIP001              pData->SetObjArea(aScaleRect);
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 }

// -----------------------------------------------------------------------------

/*N*/ void SdrOle2Obj::NbcResize(const Point& rRef, const Fraction& xFact, const Fraction& yFact)
/*N*/ {
/*N*/   SdrRectObj::NbcResize(rRef,xFact,yFact);
/*N*/   if (aGeo.nShearWink!=0 || aGeo.nDrehWink!=0) { // kleine Korrekturen
/*?*/       if (aGeo.nDrehWink>=9000 && aGeo.nDrehWink<27000) {
/*?*/           aRect.Move(aRect.Left()-aRect.Right(),aRect.Top()-aRect.Bottom());
/*?*/       }
/*?*/       aGeo.nDrehWink=0;
/*?*/       aGeo.nShearWink=0;
/*?*/       aGeo.nSin=0.0;
/*?*/       aGeo.nCos=1.0;
/*?*/       aGeo.nTan=0.0;
/*?*/       SetRectsDirty();
/*N*/   }
/*N*/   if( (NULL == pModel) || !pModel->isLocked() )
/*?*/       {DBG_ASSERT(0, "STRIP"); }//STRIP001 ImpSetVisAreaSize();
/*N*/ }

// -----------------------------------------------------------------------------

//STRIP001 void SdrOle2Obj::SetGeoData(const SdrObjGeoData& rGeo)
//STRIP001 {
//STRIP001  SdrRectObj::SetGeoData(rGeo);
//STRIP001  if( (NULL == pModel) || !pModel->isLocked() )
//STRIP001      ImpSetVisAreaSize();
//STRIP001 }

// -----------------------------------------------------------------------------

/*N*/ void SdrOle2Obj::NbcSetSnapRect(const Rectangle& rRect)
/*N*/ {
/*N*/   SdrRectObj::NbcSetSnapRect(rRect);
/*N*/   if( (NULL == pModel) || !pModel->isLocked() )
/*?*/   {DBG_ASSERT(0, "STRIP"); }//STRIP001    ImpSetVisAreaSize();
/*N*/ }

// -----------------------------------------------------------------------------

/*N*/ void SdrOle2Obj::NbcSetLogicRect(const Rectangle& rRect)
/*N*/ {
/*N*/   SdrRectObj::NbcSetLogicRect(rRect);
/*N*/   if( (NULL == pModel) || !pModel->isLocked() )
/*?*/       {DBG_ASSERT(0, "STRIP"); }//STRIP001 ImpSetVisAreaSize();
/*N*/ }

// -----------------------------------------------------------------------------

/*N*/ FASTBOOL SdrOle2Obj::HasGDIMetaFile() const
/*N*/ {DBG_ASSERT(0, "STRIP"); return FALSE;//STRIP001
//STRIP001  GetObjRef();    // try to load inplace object
//STRIP001  SvInPlaceObjectRef& rIPRef=*ppObjRef;
//STRIP001  BOOL bOK = FALSE;
//STRIP001  if ( rIPRef.Is() )
//STRIP001      bOK = TRUE;
//STRIP001
//STRIP001  return bOK;
/*N*/ }

// -----------------------------------------------------------------------------

/*N*/ const GDIMetaFile* SdrOle2Obj::GetGDIMetaFile() const
/*N*/ {DBG_ASSERT(0, "STRIP");return NULL; //STRIP001
//STRIP001  if( mpImpl->pMetaFile )
//STRIP001  {
//STRIP001      delete ((SdrOle2Obj*)this)->mpImpl->pMetaFile;
//STRIP001      ((SdrOle2Obj*)this)->mpImpl->pMetaFile = NULL;
//STRIP001  }
//STRIP001
//STRIP001  GetObjRef();    // try to load inplace object
//STRIP001  SvInPlaceObjectRef& rIPRef=*ppObjRef;
//STRIP001
//STRIP001  if (rIPRef.Is())
//STRIP001  {
//STRIP001      GDIMetaFile*            pMtf=NULL;
//STRIP001         TransferableDataHelper  aData(rIPRef->CreateTransferableSnapshot() );
//STRIP001
//STRIP001         if( aData.HasFormat( FORMAT_GDIMETAFILE ) )
//STRIP001         {
//STRIP001             GDIMetaFile* pNewMtf = new GDIMetaFile;
//STRIP001
//STRIP001             if( aData.GetGDIMetaFile( FORMAT_GDIMETAFILE, *pNewMtf ) )
//STRIP001                 ((SdrOle2Obj*)this)->mpImpl->pMetaFile = pNewMtf;
//STRIP001             else
//STRIP001                 delete pNewMtf;
//STRIP001         }
//STRIP001  }
//STRIP001  return mpImpl->pMetaFile;
/*N*/ }

// -----------------------------------------------------------------------------

/*N*/ void SdrOle2Obj::WriteData(SvStream& rOut) const
/*N*/ {
/*N*/   SdrRectObj::WriteData(rOut);
/*N*/   SdrDownCompat aCompat(rOut,STREAM_WRITE); // Fuer Abwaertskompatibilitaet (Lesen neuer Daten mit altem Code)
/*N*/ #ifdef DBG_UTIL
/*N*/   aCompat.SetID("SdrOle2Obj");
/*N*/ #endif
/*N*/
/*N*/   // UNICODE: rOut<<mpImpl->aPersistName;
/*N*/   rOut.WriteByteString(mpImpl->aPersistName);
/*N*/
/*N*/   // UNICODE: rOut<<aProgName;
/*N*/   rOut.WriteByteString(aProgName);
/*N*/
/*N*/   GetObjRef();
/*N*/   BOOL bObjRefValid=ppObjRef->Is();
/*N*/   rOut<<bObjRefValid;
/*N*/   BOOL bPreview = FALSE;
/*N*/   if( !IsEmptyPresObj() && pModel && pModel->IsSaveOLEPreview() )
/*N*/       bPreview = TRUE;
/*N*/
/*N*/   if( bPreview )
/*N*/   {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/        // set preview graphic (not for empty presentation objects)
//STRIP001 /*?*/        GetGDIMetaFile();
//STRIP001 /*?*/        if( mpImpl->pMetaFile )
//STRIP001 /*?*/        {
//STRIP001 /*?*/            Graphic aNewGraphic( *mpImpl->pMetaFile );
//STRIP001 /*?*/            ( (SdrOle2Obj*) this )->SetGraphic( &aNewGraphic );
//STRIP001 /*?*/        }
/*N*/   }

/*N*/   BOOL bHasGraphic=pGraphic!=NULL;
/*N*/   rOut<<bHasGraphic;
/*N*/   if (bHasGraphic)
/*N*/   {
/*?*/       SdrDownCompat aGrafCompat(rOut,STREAM_WRITE); // ab V11 eingepackt
/*?*/ #ifdef DBG_UTIL
/*?*/       aGrafCompat.SetID("SdrOle2Obj(Graphic)");
/*?*/ #endif
/*?*/       rOut<<*pGraphic;
/*N*/   }
/*N*/
/*N*/   if( bPreview )
/*?*/       ( (SdrOle2Obj*) this )->SetGraphic( NULL );     // remove preview graphic
/*N*/ }

// -----------------------------------------------------------------------------

/*N*/ void SdrOle2Obj::ReadData(const SdrObjIOHeader& rHead, SvStream& rIn)
/*N*/ {
/*N*/   rIn.SetError( 0 );
/*N*/
/*N*/   if (rIn.GetError()!=0) return;
/*N*/   SdrRectObj::ReadData(rHead,rIn);
/*N*/   SdrDownCompat aCompat(rIn,STREAM_READ); // Fuer Abwaertskompatibilitaet (Lesen neuer Daten mit altem Code)
/*N*/ #ifdef DBG_UTIL
/*N*/   aCompat.SetID("SdrOle2Obj");
/*N*/ #endif
/*N*/
/*N*/   // UNICODE: rIn >> mpImpl->aPersistName;
/*N*/   rIn.ReadByteString(mpImpl->aPersistName);
/*N*/
/*N*/   // UNICODE: rIn >> aProgName;
/*N*/   rIn.ReadByteString(aProgName);
/*N*/
/*N*/   BOOL bObjRefValid;
/*N*/   rIn>>bObjRefValid;
/*N*/
/*N*/   BOOL bHasGraphic;
/*N*/   rIn>>bHasGraphic;
/*N*/   if (bHasGraphic)
/*N*/   {
/*?*/       if(pGraphic==NULL)
/*?*/           pGraphic=new Graphic;
/*?*/
/*?*/       if(rHead.GetVersion()>=11)
/*?*/       { // ab V11 eingepackt
/*?*/           SdrDownCompat aGrafCompat(rIn,STREAM_READ);
/*?*/ #ifdef DBG_UTIL
/*?*/           aGrafCompat.SetID("SdrOle2Obj(Graphic)");
/*?*/ #endif
/*?*/           rIn>>*pGraphic;
/*?*/       }
/*?*/       else
/*?*/           rIn>>*pGraphic;
/*?*/
/*?*/       if( mpImpl->pGraphicObject )
/*?*/           delete mpImpl->pGraphicObject;
/*?*/
/*?*/       mpImpl->pGraphicObject = new GraphicObject( *pGraphic );
/*N*/   }
/*N*/ }

// -----------------------------------------------------------------------------

/*N*/ void SdrOle2Obj::NbcMove(const Size& rSize)
/*N*/ {
/*N*/   SdrRectObj::NbcMove(rSize);
/*N*/   if( (NULL == pModel) || !pModel->isLocked() )
/*?*/   {DBG_ASSERT(0, "STRIP"); }//STRIP001    ImpSetVisAreaSize();
/*N*/ }

// -----------------------------------------------------------------------------

/*N*/ BOOL SdrOle2Obj::Unload()
/*N*/ {
/*N*/   BOOL bUnloaded = FALSE;
/*N*/
/*N*/   if( ppObjRef && ppObjRef->Is() )
/*N*/   {
/*N*/       //Nicht notwendig im Doc DTor (MM)
/*N*/       ULONG nRefCount = (*ppObjRef)->GetRefCount();
/*N*/       // prevent Unload if there are external references
/*N*/       if( nRefCount > 2 )
/*N*/           return FALSE;
/*N*/       DBG_ASSERT( nRefCount == 2, "Wrong RefCount for unload" );
/*N*/   }
/*N*/   else
/*N*/       bUnloaded = TRUE;
/*N*/
/*N*/   if (pModel && ppObjRef && ppObjRef->Is() &&
/*N*/       SVOBJ_MISCSTATUS_ALWAYSACTIVATE != (*ppObjRef)->GetMiscStatus() &&
/*N*/       1 < (*ppObjRef)->GetRefCount()                                  &&
/*N*/       !(*ppObjRef)->IsModified()                                      &&
/*N*/       !(*ppObjRef)->GetProtocol().IsInPlaceActive() )
/*N*/   {
/*N*/       SvPersist* pPersist = pModel->GetPersist();
/*N*/
/*N*/       if (pPersist)
/*N*/       {
/*N*/           SvPersist* pO = *ppObjRef;
/*N*/           if( pO->IsModified() )
/*N*/           {
/*?*/               pO->DoSave();
/*?*/               pO->DoSaveCompleted();
/*N*/           }
/*N*/           ppObjRef->Clear();
/*N*/           if (pPersist->Unload(pO))
/*N*/               bUnloaded = TRUE;
/*N*/           else
/*?*/               *ppObjRef = pO;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   return bUnloaded;
/*N*/ }

// -----------------------------------------------------------------------------

//STRIP001 void SdrOle2Obj::CreatePersistName( SvPersist* pPers )
//STRIP001 {
//STRIP001  mpImpl->aPersistName = OUString::createFromAscii( "Object " );
//STRIP001  String aStr( mpImpl->aPersistName );
//STRIP001  USHORT i = 1;
//STRIP001  aStr+=String::CreateFromInt32( i );
//STRIP001  while( pPers->Find( aStr ) )
//STRIP001  {
//STRIP001      aStr = mpImpl->aPersistName;
//STRIP001      aStr += String::CreateFromInt32(++i);
//STRIP001  }
//STRIP001  mpImpl->aPersistName = aStr;
//STRIP001 }

// -----------------------------------------------------------------------------

/*N*/ const SvInPlaceObjectRef& SdrOle2Obj::GetObjRef() const
/*N*/ {
/*N*/   if ( !ppObjRef->Is() && pModel && pModel->GetPersist() && !pModel->GetPersist()->IsHandsOff() )
/*N*/   {
/*N*/       // #107645#
/*N*/       // Only try loading if it did not wrent wrong up to now
/*N*/       if(!mpImpl->mbLoadingOLEObjectFailed)
/*N*/       {
/*N*/           // Objekt laden
/*N*/           (*ppObjRef) = &( pModel->GetPersist()->GetObject( mpImpl->aPersistName ) );
/*N*/
/*N*/           // #107645#
/*N*/           // If loading of OLE object failed, remember that to not invoke a endless
/*N*/           // loop trying to load it again and again.
/*N*/           if(!ppObjRef->Is())
/*N*/           {
/*N*/               mpImpl->mbLoadingOLEObjectFailed = sal_True;
/*N*/           }
/*N*/
/*N*/             // #108759# For math objects, set closed state to transparent
/*N*/             if( ImplIsMathObj( *ppObjRef ) )
/*N*/                 const_cast<SdrOle2Obj*>(this)->SetClosedObj( false );
/*N*/       }
/*N*/
/*N*/       if ( ppObjRef->Is() )
/*N*/       {
/*N*/           if( !IsEmptyPresObj() )
/*N*/           {
/*N*/               // #75637# remember modified status of model
/*N*/               BOOL bWasChanged(pModel ? pModel->IsChanged() : FALSE);
/*N*/
/*N*/               // perhaps preview not valid anymore
/*N*/               // #75637# This line changes the modified state of the model
/*N*/               ( (SdrOle2Obj*) this )->SetGraphic( NULL );
/*N*/
/*N*/               // #75637# if status was not set before, force it back
/*N*/               // to not set, so that SetGraphic(0L) above does not
/*N*/               // set the modified state of the model.
/*N*/               if(!bWasChanged && pModel && pModel->IsChanged())
/*N*/                   pModel->SetChanged(FALSE);
/*N*/           }
/*N*/
/*N*/           if ( (*ppObjRef)->GetMiscStatus() & SVOBJ_MISCSTATUS_RESIZEONPRINTERCHANGE )
/*N*/           {
/*N*/               if (pModel && pModel->GetRefDevice() &&
/*N*/                   pModel->GetRefDevice()->GetOutDevType() == OUTDEV_PRINTER)
/*N*/               {
/*N*/                   if(!bInDestruction)
/*N*/                   {
/*N*/                       // prevent SetModified (don't want no update here)
/*N*/                       sal_Bool bWasEnabled = (*ppObjRef)->IsEnableSetModified();
/*N*/                       if ( bWasEnabled )
/*N*/                           (*ppObjRef)->EnableSetModified( sal_False );
/*N*/
/*N*/                       // Kein RefDevice oder RefDevice kein Printer
/*N*/                       Printer* pPrinter = (Printer*) pModel->GetRefDevice();
/*N*/                       (*ppObjRef)->OnDocumentPrinterChanged( pPrinter );
/*N*/
/*N*/                       // reset state
/*N*/                       (*ppObjRef)->EnableSetModified( bWasEnabled );
/*N*/                   }
/*N*/               }
/*N*/           }
/*N*/
/*N*/           // register modify listener on initial load
/*N*/           if( pModifyListener == NULL )
/*N*/           {
/*N*/               ((SdrOle2Obj*)this)->pModifyListener = new SvxUnoShapeModifyListener( (SdrOle2Obj*)this );
/*N*/               pModifyListener->acquire();
/*N*/
/*N*/               uno::Reference< util::XModifyBroadcaster > xBC( getXModel(), uno::UNO_QUERY );
/*N*/               if( xBC.is() && pModifyListener )
/*N*/               {
/*N*/                   uno::Reference< util::XModifyListener > xListener( pModifyListener );
/*N*/                   xBC->addModifyListener( xListener );
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/
/*N*/   if (ppObjRef->Is())
/*N*/   {
/*N*/       // In Cache einfuegen
/*N*/       GetSdrGlobalData().GetOLEObjCache().InsertObj((SdrOle2Obj*) this);
/*N*/   }
/*N*/
/*N*/   return *ppObjRef;
/*N*/ }

// -----------------------------------------------------------------------------

/*N*/ uno::Reference< frame::XModel > SdrOle2Obj::getXModel() const
/*N*/ {
/*N*/   uno::Reference< frame::XModel > xModel;
/*N*/
/*N*/   if( pModel )
/*N*/   {
/*N*/       SvInPlaceObjectRef xSvIPO( GetObjRef() );
/*N*/       SfxInPlaceObjectRef xIPO( xSvIPO );
/*N*/       if( xIPO.Is() )
/*N*/       {
/*N*/           SfxObjectShell* pShell = xIPO->GetObjectShell();
/*N*/
/*N*/           if( pShell )
/*N*/               xModel = pShell->GetModel();
/*N*/       }
/*N*/   }
/*N*/
/*N*/   return xModel;
/*N*/ }

// -----------------------------------------------------------------------------

/// #110015# sets the visible area at the SvInPlaceObject and SvEmbeddedInfoObject
/*N*/ void SdrOle2Obj::SetVisibleArea( const Rectangle& rVisArea )
/*N*/ {
/*N*/   const SvInPlaceObjectRef& xInplace = GetObjRef();
/*N*/   if( xInplace.Is() )
/*N*/   {
/*N*/       xInplace->SetVisArea( rVisArea );
/*N*/
/*N*/       if( pModel && (!pModel->GetPersist()->IsEnableSetModified()) )
/*N*/           xInplace->SetModified(FALSE);
/*N*/   }
/*N*/
/*N*/   if(pModel && mpImpl->aPersistName.Len() )
/*N*/   {
/*N*/       SvPersist* pPers = pModel->GetPersist();
/*N*/
/*N*/       if (pPers)
/*N*/       {
/*N*/           SvInfoObject* pInfo = pPers->Find(mpImpl->aPersistName);
/*N*/           SvEmbeddedInfoObject * pEmbed = PTR_CAST(SvEmbeddedInfoObject, pInfo );
/*N*/
/*N*/           if( pEmbed )
/*N*/               pEmbed->SetInfoVisArea( rVisArea );
/*N*/       }
/*N*/   }
/*N*/ }

// -----------------------------------------------------------------------------
