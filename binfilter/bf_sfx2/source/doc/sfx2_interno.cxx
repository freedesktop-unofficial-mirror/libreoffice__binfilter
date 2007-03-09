/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sfx2_interno.cxx,v $
 *
 *  $Revision: 1.9 $
 *
 *  last change: $Author: obo $ $Date: 2007-03-09 14:57:35 $
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

#include <so3/ipenv.hxx>
#include <svtools/eitem.hxx>

#define _SFX_INTERNO_CXX


#ifndef _SVTOOLS_IMGDEF_HXX
#include <svtools/imgdef.hxx>
#endif

#include "dispatch.hxx"
#include "request.hxx"
#include "docfac.hxx"
#include "viewsh.hxx"
#include "interno.hxx"
#include "fltfnc.hxx"
#include "sfxresid.hxx"
#include "doc.hrc"
namespace binfilter {

//-------------------------------------------------------------------------

#define SVIPWINDOW(p) ((SvInPlaceWindow&)p->GetWindow())

//-------------------------------------------------------------------------
/*N*/ SV_IMPL_FACTORY(SfxInPlaceObjectFactory){}};
/*N*/ TYPEINIT1(SfxInPlaceObjectFactory,SvFactory);
/*N*/ SO2_IMPL_CLASS1(SfxInPlaceObject,SfxInPlaceObjectFactory,SvInPlaceObject,
/*N*/         SvGlobalName(0x3C8A87D0L,0x9B53,0x11d3,0x9E,0xCE,0x00,0x50,0x04,0xD7,0x6C,0x4E))//STRIP002 SvGlobalName(0x3C8A87D0L,0x9B53,0x11d3,0x9E,0xCE,0x00,0x50,0x04,0xD7,0x6C,0x4D))
/*?*/ void SfxInPlaceObject::TestMemberObjRef(BOOL){}
/*?*/ void SfxInPlaceObject::TestMemberInvariant(BOOL){}
/*?*/ IUnknown* SfxInPlaceObject::GetMemberInterface( const SvGlobalName & ){ return 0L; }

/*N*/ SfxInPlaceObject::SfxInPlaceObject()
/*N*/ : pObjShell(0),
/*N*/   pFrame(0)
/*N*/ {
/*N*/   bTriggerLinkTimer = TRUE;
/*N*/   bDisableViewScaling = FALSE;
/*N*/   pNote = 0;
/*N*/
/*N*/   // Verben der Superklasse bekanntgeben, um GetVerbList nicht
/*N*/   // ueberlagern zu muessen
/*N*/     SvVerbList* pVerbs = new SvVerbList;
/*N*/     pVerbs->Append( SvVerb( 0, String( SfxResId( STR_EDITOBJECT ) ) ) );
/*N*/ //    pVerbs->Append( SvVerb( 1, String( SfxResId( STR_OPENOBJECT ) ) ) );
/*N*/ //    pVerbs->Append( SvVerb( 2, DEFINE_CONST_UNICODE(STARAPP_VERB), sal_True, sal_False ) );
/*N*/     pVerbs->Append( SvVerb( 3, String( SfxResId( STR_SAVECOPYDOC ) ) ) );
/*N*/     SetVerbList( pVerbs, TRUE );
/*N*/ }

/*N*/ void SfxInPlaceObject::SetShell( SfxObjectShell *pObjSh )
/*N*/ {
/*N*/     pObjShell = pObjSh;
/*N*/ }

//--------------------------------------------------------------------

/*N*/ SfxInPlaceObject::~SfxInPlaceObject()
/*N*/ {
/*N*/ }

//--------------------------------------------------------------------

/*N*/ void SfxInPlaceObject::FillClass( SvGlobalName * pClassName,
/*N*/                                 ULONG * pClipFormat,
/*N*/                                 String * pAppName,
/*N*/                                 String * pLongUserName,
/*N*/                                 String * pUserName,
/*N*/                                 long nVersion
/*N*/ ) const
/*N*/ {
/*N*/   SvPersist::FillClass( pClassName, pClipFormat, pAppName,
/*N*/                           pLongUserName, pUserName, nVersion );
/*N*/   DBG_ASSERT( pObjShell,
/*N*/               "SfxInPlaceObject::FillClass(): you must call SetShell() bevor" )
/*N*/   SfxObjectFactory &rFact = pObjShell->GetFactory();
/*N*/
/*N*/   for( USHORT n = 0; n < rFact.GetFilterCount(); n++ )
/*N*/   {
/*N*/       const SfxFilter * pFilter = rFact.GetFilter( n );
/*N*/
/*N*/       if ( pFilter->IsOwnFormat() &&
/*N*/            pFilter->GetVersion() == (ULONG)nVersion )
/*N*/       {
/*N*/           *pClassName     = *GetSvFactory();
/*N*/           *pClipFormat    = pFilter->GetFormat();
/*N*/             *pLongUserName  = pFilter->GetFilterName();
/*N*/             *pUserName      = pFilter->GetFilterName();
/*N*/           break;
/*N*/       }
/*N*/   }
/*N*/   *pAppName = String( SfxResId(STR_HUMAN_APPNAME ) );
/*N*/ }

//--------------------------------------------------------------------

/*N*/ void SfxInPlaceObject::SetModified( BOOL bSet )
/*N*/ {
/*N*/   if ( !bSet || !pObjShell->IsReadOnlyMedium() )
/*N*/   {
/*N*/       SvInPlaceObject::SetModified( bSet );
/*N*/         if( bSet && bTriggerLinkTimer && IsEnableSetModified() )
/*N*/       {
/*N*/           ViewChanged( ASPECT_CONTENT );
/*N*/       }
/*N*/   }
/*N*/ }

//--------------------------------------------------------------------

/*N*/ void SfxInPlaceObject::UpdateLinks()
/*N*/ {
/*N*/   SendViewChanged();
/*N*/ }

//--------------------------------------------------------------------

/*N*/ BOOL SfxInPlaceObject::InitNew( SvStorage * pStor)
/*N*/ {
/*N*/   if( SvInPlaceObject::InitNew( pStor ) )
/*N*/   {
/*N*/       return TRUE;
/*N*/   }
/*N*/   return FALSE;
/*N*/ }

//--------------------------------------------------------------------

/*N*/ BOOL SfxInPlaceObject::Load( SvStorage * pStor )
/*N*/ {
/*N*/   if( SvInPlaceObject::Load( pStor ) )
/*N*/   {
/*N*/       // Spaeter mal Childs on demand
/*N*/ //        if( LoadChilds() )
/*N*/           return TRUE;
/*N*/   }
/*N*/   return FALSE;
/*N*/ }

//--------------------------------------------------------------------

/*N*/ BOOL SfxInPlaceObject::Save()
/*N*/ {
/*N*/   if( !SaveChilds() )
/*N*/       return FALSE;
/*N*/   if( SvInPlaceObject::Save() )
/*N*/         return pObjShell->SfxObjectShell::Save();
/*N*/   return FALSE;
/*N*/ }

//--------------------------------------------------------------------

/*N*/ BOOL SfxInPlaceObject::SaveAs( SvStorage * pNewStor )
/*N*/ {
/*N*/   if( !SaveAsChilds( pNewStor ) )
/*N*/       return FALSE;
/*N*/     if( SvInPlaceObject::SaveAs( pNewStor ) )
/*N*/         return pObjShell->SfxObjectShell::SaveAs(pNewStor);
/*N*/   return FALSE;
/*N*/ }

//--------------------------------------------------------------------

/*N*/ void SfxInPlaceObject::HandsOff()
/*N*/ {
/*N*/   SvInPlaceObject::HandsOff();
/*N*/ }

//--------------------------------------------------------------------

/*N*/ BOOL SfxInPlaceObject::SaveCompleted( SvStorage * pStor )
/*N*/ {
/*N*/   if( !SaveCompletedChilds( pStor ) )
/*N*/       return FALSE;
/*N*/   if( SvInPlaceObject::SaveCompleted( pStor ) )
/*N*/   {
/*N*/       return TRUE;
/*N*/   }
/*N*/   return FALSE;
/*N*/ }

//--------------------------------------------------------------------

/*N*/ void SfxInPlaceObject::SetVisArea( const Rectangle & rRect )
/*N*/ {
/*N*/   if( GetVisArea() != rRect )
/*N*/   {
/*N*/       Size aSize (GetVisArea().GetSize());
/*N*/       // Groesse des Objects setzen
/*N*/       SvInPlaceObject::SetVisArea( rRect );
/*N*/
/*N*/       SetModified( TRUE );
/*N*/
/*N*/         if ( GetIPEnv() && GetIPEnv()->GetEditWin() )
/*?*/             ViewChanged( ASPECT_CONTENT );
/*N*/
/*N*/       SfxInPlaceFrame *pIPF = PTR_CAST(SfxInPlaceFrame,pFrame);
/*N*/
/*N*/       // OutPlace die Gr"o\se des MDI-Fensters anpassen
/*N*/       // Unbedingt den Gr"o\senvergleich machen, spart nicht nur Zeit, sondern
/*N*/       // vermeidet auch Rundungsfehler !
/*N*/       if ( GetObjectShell()->GetCreateMode() == SFX_CREATE_MODE_EMBEDDED )
/*N*/       {
/*N*/           // in case of ole outplace editing the frame should be found
/*N*/           SfxViewFrame* pFrameToResize = pFrame ? pFrame : SfxViewFrame::GetFirst( GetObjectShell() );
/*N*/
/*N*/           if ( pFrameToResize && !pIPF && rRect.GetSize() != aSize &&
/*N*/               !pFrameToResize->IsAdjustPosSizePixelLocked_Impl() )
/*N*/
/*N*/           {
/*N*/               // Zuerst die logischen Koordinaten von IP-Objekt und EditWindow
/*N*/               // ber"ucksichtigen
/*?*/               SfxViewShell *pShell = pFrameToResize->GetViewShell();
/*?*/               Window *pWindow = pShell->GetWindow();
/*?*/
/*?*/               // Da in den Applikationen bei der R"ucktransformation immer die
/*?*/               // Eckpunkte tranformiert werden und nicht die Size (um die Ecken
/*?*/               // alignen zu k"onnen), transformieren wir hier auch die Punkte, um
/*?*/               // m"oglichst wenig Rundungsfehler zu erhalten.
/*?*/               Rectangle aRect = pWindow->LogicToPixel( rRect );
/*?*/               Size aSize = aRect.GetSize();
/*?*/               pShell->GetWindow()->SetSizePixel( aSize );
/*?*/               pFrameToResize->DoAdjustPosSizePixel( pShell, Point(), aSize );
/*N*/           }
/*N*/       }
/*N*/
/*N*/       // bei InPlace die View skalieren
/*N*/         if ( GetIPEnv() && GetIPEnv()->GetEditWin() && !bDisableViewScaling && pIPF )
/*?*/           {DBG_BF_ASSERT(0, "STRIP");}//STRIP001 pIPF->GetEnv_Impl()->MakeScale( rRect.GetSize(), GetMapUnit(),
/*N*/   }
/*N*/ }

//--------------------------------------------------------------------

/*N*/ ErrCode SfxInPlaceObject::Verb( long nVerb, SvEmbeddedClient *pCaller,
/*N*/                               Window *pWindow, const Rectangle* pRect)
/*N*/ {
     if ( pCaller && pCaller == GetClient() )
     {
         if ( nVerb == 1 )
             return DoEmbed(TRUE);
         else if ( nVerb == 3 )
         {
             SfxObjectShell* pDoc = GetObjectShell();
             SfxRequest aReq( SID_SAVEASDOC, SFX_CALLMODE_SYNCHRON, pDoc->GetPool() );
             aReq.AppendItem( SfxBoolItem( SID_SAVETO, TRUE ) );
             pDoc->ExecuteSlot( aReq );
             return ERRCODE_NONE;
         }
         return SvInPlaceObject::Verb(nVerb, pCaller, pWindow, pRect);
     }
     else
     {
         DBG_ERROR("This behaviour is undefined!");
         return FALSE;
     }
/*N*/ }

//--------------------------------------------------------------------

/*?*/ BOOL SfxInPlaceObject::Verb( long nVerb, const Rectangle* pRect )
/*?*/ {
/*?*/   return (BOOL)DoEmbed( TRUE );
/*?*/ }

//--------------------------------------------------------------------

/*?*/ void SfxInPlaceObject::Open( BOOL bOpen )
/*?*/ {
/*?*/   SvInPlaceObject::Open( bOpen );
/*?*/ }

//-------------------------------------------------------------------------

/*N*/ void SfxInPlaceObject::InPlaceActivate( BOOL bActivate )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/ }

//--------------------------------------------------------------------

/*N*/ void SfxInPlaceObject::Embed( BOOL bEmbed )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/ }

//--------------------------------------------------------------------

/*N*/ void SfxInPlaceObject::DocumentNameChanged( const String & rDocName )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/ }

//--------------------------------------------------------------------

/*N*/ SfxForceLinkTimer_Impl::SfxForceLinkTimer_Impl( SfxObjectShell *pObj )
/*N*/ {
/*N*/   pInObj = pObj->GetInPlaceObject();
/*N*/   if( pInObj )
/*N*/   {
/*N*/       pInObj->SetTriggerLinkTimer( FALSE );
/*N*/       pInObj->UpdateLinks();
/*N*/   }
/*N*/ }
}
