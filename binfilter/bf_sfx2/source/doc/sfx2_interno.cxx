/*************************************************************************
 *
 *  $RCSfile: sfx2_interno.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 14:51:30 $
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

#ifdef SOLARIS
// HACK: prevent conflict between STLPORT and Workshop headers on Solaris 8
#include <ctime>
#endif

#include <string> // HACK: prevent conflict between STLPORT and Workshop headers

// auto strip #ifndef _SV_WRKWIN_HXX //autogen
// auto strip #include <vcl/wrkwin.hxx>
// auto strip #endif
// auto strip #ifndef _URLOBJ_HXX
// auto strip #include <tools/urlobj.hxx>
// auto strip #endif
// auto strip #ifndef _SVSTOR_HXX
// auto strip #include <so3/svstor.hxx>
// auto strip #endif

#include <svtools/eitem.hxx>

#pragma hdrstop

#define _SFX_INTERNO_CXX

// auto strip #include "sfxtypes.hxx"

#ifndef _SVTOOLS_IMGDEF_HXX
#include <svtools/imgdef.hxx>
#endif

// auto strip #include "tbxmgr.hxx"
// auto strip #include "app.hxx"
#include "dispatch.hxx"
#include "request.hxx"
#include "docfac.hxx"
// auto strip #include "docfilt.hxx"
// auto strip #include "viewfrm.hxx"
#include "viewsh.hxx"
// auto strip #include "virtmenu.hxx"
// auto strip #include "mnumgr.hxx"
#include "interno.hxx"
// auto strip #include "ipfrm.hxx"
#include "ipenv.hxx"
// auto strip #include "imgmgr.hxx"
// auto strip #include "childwin.hxx"
// auto strip #include "arrdecl.hxx"
// auto strip #include "cfgmgr.hxx"
// auto strip #include "tbxconf.hxx"
#include "fltfnc.hxx"
// auto strip #include "accmgr.hxx"
#include "sfxresid.hxx"
// auto strip #include "topfrm.hxx"
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
//STRIP001 /*?*/                        pIPF->GetViewShell()->GetWindow()->GetOutputSizePixel() );
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
 /*
         SfxApplication *pSfxApp = SFX_APP();
         pFrame = pObjShell->GetFrame();
         if ( !pFrame )
         {
 //(mba)/task: no correct outplace editing
             pFrame = SfxTopFrame::Create( pObjShell )->GetCurrentViewFrame();
         }
         else
         {
             pFrame->GetFrame()->Appear();
         }

         String aFN = GetFileName();
         if( aFN.Len() )
         {
             // Dokumentnamen setzen
             INetURLObject aDE( GetFileName(), INET_PROT_FILE );
             SetDocumentName( aDE.GetName() );
             pFrame->GetWindow().SetText( aDE.GetName() );
         }

         pFrame->GetWindow().ToTop();
         return ERRCODE_NONE;
  */
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
//STRIP001  if( bActivate )
//STRIP001  {
//STRIP001      DBG_ASSERT( pObjShell,
//STRIP001                  "SfxInPlaceObject::InPlaceActivate(): you must call SetShell() bevor" )
//STRIP001      DBG_ASSERT (!pFrame, "Objekt ist noch aktiv!");
//STRIP001
//STRIP001      // IPFenster erzeugen
//STRIP001      SfxInPlaceFrame *pIPFrame =
//STRIP001                      new SfxInPlaceFrame( *pObjShell );
//STRIP001      pFrame = pIPFrame;
//STRIP001      SetIPEnv( pIPFrame->GetEnv_Impl() );
//STRIP001
//STRIP001      if ( GetIPClient()->Owner() )
//STRIP001      {
//STRIP001             pFrame->SetParentViewFrame_Impl( SfxViewFrame::Current() );
//STRIP001      }
//STRIP001
//STRIP001      pIPFrame->GetDispatcher()->Flush();
//STRIP001      pIPFrame->DoActivate( FALSE );
//STRIP001  }
//STRIP001
//STRIP001  SvInPlaceObject::InPlaceActivate( bActivate );
//STRIP001
//STRIP001  if ( !bActivate )
//STRIP001  {
//STRIP001      // Im UIActivate wurde SetViewFrame(0) gemacht, aber neuerdings
//STRIP001      // gibt es dann kein Deactivate(TRUE), weil alter und neuer
//STRIP001      // ViewFrame der Applikation verschiedene Bindings haben.
//STRIP001      // Frame samt Fenstern jetzt im Deactivate wegwerfen
//STRIP001      // DoDeactivate erfolgt im UIDeactivate
//STRIP001      pFrame->GetFrame()->DoClose();
//STRIP001      pFrame = NULL;
//STRIP001  }
/*N*/ }

//--------------------------------------------------------------------

/*N*/ void SfxInPlaceObject::Embed( BOOL bEmbed )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*
//STRIP001  SvInPlaceObject::Embed( bEmbed );
//STRIP001
//STRIP001  if( bEmbed )
//STRIP001  {
//STRIP001         DBG_ASSERT( pObjShell, "SfxInPlaceObject::Embed(): you must call SetShell() bevor" )
//STRIP001      if (pFrame)
//STRIP001      {
//STRIP001          SetIPEnv( 0 );
//STRIP001          pFrame->GetFrame()->DoClose();
//STRIP001          pFrame = NULL;
//STRIP001      }
//STRIP001
//STRIP001         pFrame = SfxTopFrame::Create( pObjShell,0 )->GetCurrentViewFrame();
//STRIP001         pFrame->GetFrame()->Appear();
//STRIP001
//STRIP001      // Beim Writer stehen sonst die Scrollbars mittendrin
//STRIP001      pFrame->InvalidateBorderImpl( pFrame->GetViewShell() );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      // Unter WIN 3.1 mu\s das MDI-Window schon hier deleted werden,
//STRIP001      // da sonst zun"achst die Verbindung zum Client geclosed wird, dieser
//STRIP001      // dabei den Focus von Windows erh"alt, der ihm aber anschlie\send
//STRIP001      // gleich wieder durch den Window-ctor des MDI-Windows entzogen wird.
//STRIP001      pFrame->GetFrame()->DoClose();
//STRIP001      pFrame = NULL;
//STRIP001  }
//STRIP001 */
/*N*/ }

//--------------------------------------------------------------------

//STRIP001 void SfxInPlaceObject::UIActivate( BOOL bActivate )
//STRIP001 {
//STRIP001  SfxApplication *pApp = SFX_APP();
//STRIP001  SfxViewFrame *pParent = pFrame->GetParentViewFrame_Impl();
//STRIP001  if ( bActivate )
//STRIP001  {
//STRIP001      if ( pParent )
//STRIP001          pParent->SetIPFrame_Impl( GetIPFrame_Impl() );
//STRIP001
//STRIP001      // DoActivate erfolgte schon im InPlaceActivate
//STRIP001      pApp->SetViewFrame( pFrame );
//STRIP001      pFrame->DoActivate( TRUE );
//STRIP001         pFrame->GetDispatcher()->Update_Impl( TRUE );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      if ( pParent )
//STRIP001          // Bei internem InPlace das Container-Dokument aktivieren
//STRIP001          pParent->SetIPFrame_Impl( NULL );
//STRIP001
//STRIP001      if ( pApp->GetViewFrame() == pFrame )
//STRIP001          // Das muss nicht sein, es k"onnte auch die Task gewechselt worden sein
//STRIP001          pApp->SetViewFrame( pParent );
//STRIP001
//STRIP001      pFrame->DoDeactivate( TRUE );
//STRIP001  }
//STRIP001
//STRIP001  SvInPlaceObject::UIActivate( bActivate );
//STRIP001  GetIPFrame_Impl()->GetEnv_Impl()->UIActivate(bActivate);
//STRIP001
//STRIP001  if ( !bActivate && pApp->GetViewFrame() == pFrame )
//STRIP001  {
//STRIP001      // Wenn jetzt noch der InPlaceFrame aktiv ist ( externes InPlace ),
//STRIP001      // deaktivieren
//STRIP001      pApp->SetViewFrame(0);
//STRIP001  }
//STRIP001 }

//--------------------------------------------------------------------

//STRIP001 void SfxInPlaceObject::TopWinActivate( BOOL bActivate )
//STRIP001 {
//STRIP001 #ifdef DBG_UTIL
//STRIP001  ByteString aTest( "TopWinActivate( " );
//STRIP001  aTest += bActivate ? "TRUE" : "FALSE";
//STRIP001  aTest += " )";
//STRIP001  DBG_TRACE( aTest.GetBuffer() );
//STRIP001 #endif
//STRIP001
//STRIP001  if ( bActivate )
//STRIP001  {
//STRIP001      if ( GetProtocol().IsDocWinActive() && GetProtocol().IsUIActive() )
//STRIP001      {
//STRIP001          GetIPFrame_Impl()->GetEnv_Impl()->TopWinActivate(bActivate);
//STRIP001
//STRIP001          // Hier muss der ViewFrame gesetzt werden, da beim Umschalten von
//STRIP001          // StarApplikation-MDI auf Applikation mit StarApplikation-IP diese
//STRIP001          // nur ein TopWinActivate, aber kein DocWinActivate bekommt !
//STRIP001
//STRIP001          if ( SFX_APP()->GetViewFrame() != pFrame )
//STRIP001              SFX_APP()->SetViewFrame( pFrame );
//STRIP001          else
//STRIP001              pFrame->DoActivate( FALSE );
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  SvInPlaceObject::TopWinActivate( bActivate );
//STRIP001
//STRIP001  if ( !bActivate )
//STRIP001  {
//STRIP001      if ( GetProtocol().IsDocWinActive() && GetProtocol().IsUIActive() )
//STRIP001      {
//STRIP001          GetIPFrame_Impl()->GetEnv_Impl()->TopWinActivate( bActivate );
//STRIP001          pFrame->DoDeactivate( FALSE );
//STRIP001      }
//STRIP001  }
//STRIP001 }

//--------------------------------------------------------------------

//STRIP001 void SfxInPlaceObject::DocWinActivate( BOOL bActivate )
//STRIP001 {
//STRIP001 #ifdef DBG_UTIL
//STRIP001  ByteString aTest( "DocWinActivate( " );
//STRIP001  aTest += bActivate ? "TRUE" : "FALSE";
//STRIP001  aTest += " )";
//STRIP001  DBG_TRACE( aTest.GetBuffer() );
//STRIP001 #endif
//STRIP001
//STRIP001  if ( bActivate )
//STRIP001  {
//STRIP001      if ( GetProtocol().IsUIActive() )
//STRIP001      {
//STRIP001          GetIPFrame_Impl()->GetEnv_Impl()->DocWinActivate( bActivate );
//STRIP001          if ( SFX_APP()->GetViewFrame() != pFrame )
//STRIP001              SFX_APP()->SetViewFrame(pFrame);
//STRIP001          else
//STRIP001              pFrame->DoActivate(FALSE);
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  SvInPlaceObject::DocWinActivate( bActivate );
//STRIP001
//STRIP001  if ( !bActivate )
//STRIP001  {
//STRIP001      if ( GetProtocol().IsUIActive() )
//STRIP001      {
//STRIP001          GetIPFrame_Impl()->GetEnv_Impl()->DocWinActivate( bActivate );
//STRIP001          pFrame->DoDeactivate( FALSE );
//STRIP001      }
//STRIP001  }
//STRIP001 }

//--------------------------------------------------------------------

/*N*/ void SfxInPlaceObject::DocumentNameChanged( const String & rDocName )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  if ( !pFrame->IsA( TYPE(SfxInPlaceFrame) ) )
//STRIP001  {
//STRIP001      // Name f"ur Window zusammenbauen
//STRIP001      String aName = GetShortTypeName();
//STRIP001      aName += DEFINE_CONST_UNICODE( " in " );         //! muss noch internationalisiert werden
//STRIP001      aName += rDocName;
//STRIP001
//STRIP001      // DocName in Titelzeile von MDI-Window und als SbxObject-Name setzen
//STRIP001      pFrame->GetTopFrame()->GetWindow().SetText( aName );
//STRIP001      pFrame->SetName( aName );
//STRIP001
//STRIP001      // Slots invalidieren, damit Menue-Eintr"age aktualisiert werden
//STRIP001      pFrame->GetBindings().Invalidate(SID_CLOSEDOC);
//STRIP001      pFrame->GetBindings().Invalidate(SID_SAVEDOC);
//STRIP001      pFrame->GetBindings().Invalidate(SID_SAVEASDOC);
//STRIP001      pFrame->GetBindings().Invalidate(SID_QUITAPP);
//STRIP001  }
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
