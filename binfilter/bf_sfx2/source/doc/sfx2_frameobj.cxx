/*************************************************************************
 *
 *  $RCSfile: sfx2_frameobj.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2004-05-05 16:40:14 $
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

#include <sot/formats.hxx>
#ifndef _SOT_CLSIDS_HXX
#include <sot/clsids.hxx>
#endif
#include <tools/list.hxx>
#ifndef _SOERR_HXX //autogen
#include <so3/soerr.hxx>
#endif
#ifndef _MSGBOX_HXX //autogen
#include <vcl/msgbox.hxx>
#endif
#ifndef _IPWIN_HXX //autogen
#include <so3/ipwin.hxx>
#endif
#ifndef _SVSTOR_HXX //autogen
#include <so3/svstor.hxx>
#endif

#include <svtools/urihelper.hxx>

#pragma hdrstop

#include "frameobj.hxx"

#include "frmenv.hxx"
#include "frmdescr.hxx"
#include "urlframe.hxx"
#include "viewfrm.hxx"
#include "viewsh.hxx"
#include "clientsh.hxx"
#include "docfile.hxx"
#include "basedlgs.hxx"
#include "framedlg.hxx"
#include "doc.hrc"
#include "sfxresid.hxx"
#include "request.hxx"
#include "interno.hxx"
#include "filedlghelper.hxx"

#include <appdata.hxx>
namespace binfilter {

//STRIP001 class SfxFrameObjectEditDialog_Impl : public SfxSingleTabDialog
//STRIP001 {
//STRIP001 public:
//STRIP001  SfxFrameObjectEditDialog_Impl( Window* pParent, const SfxItemSet& rOptionsSet, USHORT nUniqueId );
//STRIP001 };

//STRIP001 SfxFrameObjectEditDialog_Impl::SfxFrameObjectEditDialog_Impl( Window* pParent,
//STRIP001                      const SfxItemSet& rOptionsSet, USHORT nUniqueId )
//STRIP001  : SfxSingleTabDialog( pParent, rOptionsSet, nUniqueId )
//STRIP001 {
//STRIP001  SetTabPage( new SfxFramePropertiesPage_Impl( this, rOptionsSet ) );
//STRIP001 };

//STRIP001 SfxInsertFloatingFrameDialog::SfxInsertFloatingFrameDialog( Window *pParent )
//STRIP001  : pParentWindow( pParent )
//STRIP001 {
//STRIP001 }

//STRIP001 SvInPlaceObjectRef SfxInsertFloatingFrameDialog::Execute( SvStorage* pStor )
//STRIP001 {
//STRIP001  SfxFrameObjectRef aObj;
//STRIP001  SfxFrameDescriptor aDescr(0);
//STRIP001  SfxItemSet aSet( SFX_APP()->GetPool(), SID_FRAMEDESCRIPTOR, SID_FRAMEDESCRIPTOR );
//STRIP001  SfxFrameDescriptorItem aItem( &aDescr );
//STRIP001  aSet.Put( aItem );
//STRIP001  SfxFrameObjectEditDialog_Impl aDlg(
//STRIP001          pParentWindow,
//STRIP001          aSet,
//STRIP001          SID_FRAMEDESCRIPTOR );
//STRIP001
//STRIP001  if ( aDlg.Execute() == RET_OK )
//STRIP001  {
//STRIP001      // Item auswerten und in Descriptor "ubernehmen
//STRIP001      const SfxPoolItem *pItem;
//STRIP001      SfxItemState eState = aDlg.GetOutputItemSet()->GetItemState( SID_FRAMEDESCRIPTOR, FALSE, &pItem );
//STRIP001      if ( eState == SFX_ITEM_SET )
//STRIP001          aDescr.TakeProperties( ((SfxFrameDescriptorItem*)pItem)->GetProperties() );
//STRIP001
//STRIP001      // FrameObject anlegen
//STRIP001      aObj = new SfxFrameObject;
//STRIP001      aObj->DoInitNew( pStor );
//STRIP001
//STRIP001      // Daten "ubertragen
//STRIP001      aObj->EnableSetModified( FALSE );
//STRIP001      aObj->SetFrameDescriptor( &aDescr );
//STRIP001      aObj->EnableSetModified( TRUE );
//STRIP001  }
//STRIP001
//STRIP001  return (SvInPlaceObject*)&aObj;
//STRIP001 }



/*N*/ struct SfxFrameObject_Impl
/*  [Beschreibung]

    Impl-Struktur des SfxFrameObjects.
*/
/*N*/ {
/*N*/   SfxFrameObjectEnv_Impl*         pEnv;
/*N*/   SfxFrameDescriptor*     pFrmDescr;
/*N*/   SfxURLFrame*            pFrame;
/*N*/   Timer*                  pNewObjectTimer;
/*N*/   SfxObjectShellLock      xDoc;
/*N*/
/*N*/               SfxFrameObject_Impl()
/*N*/                   : pFrame( NULL )
/*N*/                   , pEnv( NULL )
/*N*/                   , pFrmDescr( new SfxFrameDescriptor( NULL ) )
/*N*/                   , pNewObjectTimer( NULL )
/*N*/               {
/*N*/               }
/*N*/
/*N*/               ~SfxFrameObject_Impl()
/*N*/               {
/*N*/                   // Der Descriptor geh"ort dem Object, andere erhalten
/*N*/                   // davon immer nur Clones
/*N*/                   delete pFrmDescr;
/*N*/               }
/*N*/ };


//STRIP001 class SfxFrameObjectWindow_Impl : public Window
//STRIP001 {
//STRIP001  SfxFrameObject* pObj;
//STRIP001
//STRIP001 protected:
//STRIP001  virtual void    Resize();
//STRIP001
//STRIP001 public:
//STRIP001                     SfxFrameObjectWindow_Impl( SfxFrameObject *p,
//STRIP001                                  Window *pParent, USHORT nBits )
//STRIP001                      : Window( pParent, nBits )
//STRIP001                      , pObj( p )
//STRIP001                  {}
//STRIP001 };


//STRIP001 void SfxFrameObjectWindow_Impl::Resize()
//STRIP001 {
//STRIP001  // Die neue Fenstergr"o\se an den Frame weitergeben
//STRIP001  if ( pObj->GetFrame() )
//STRIP001         ((SfxURLFrame*)pObj->GetFrame())->GetFrameWindow_Impl()->SetOutputSizePixel( GetOutputSizePixel() );
//STRIP001 }

//=========================================================================
//STRIP001 SfxFrameObjectEnv_Impl::SfxFrameObjectEnv_Impl
//STRIP001 (
//STRIP001  SvContainerEnvironment * pFrm,  /* Das Callback Gegenst"uck zum
//STRIP001                                     InPlace-Environment */
//STRIP001  SfxFrameObject * pObj           /* Das zum Environment geh"orende
//STRIP001                                     Objekt */
//STRIP001 )
/*  [Beschreibung]

    Das Environment wird im <SfxFrameObject::InPlaceActivate()> angelegt.
    Durch die Verbindung mit dem Container Environment kann "uber die
    UI-Tools und Fenster verhandelt werden.

    [Querverweise]

    <SvInPlaceEnvironment>, <SvContainerEnvironment>
*/
//STRIP001  : SvInPlaceEnvironment( pFrm, pObj )
//STRIP001  , pFrameObject( pObj )
//STRIP001 {
//STRIP001  // Das Border- und Clip-Window werden erzeugt
//STRIP001  MakeWindows();
//STRIP001  SvInPlaceWindow *pBW = GetBorderWin();
//STRIP001  pBW->SetHatchBorderPixel( Size() );
//STRIP001
//STRIP001  // Eigentliches Fenster erzeugen
//STRIP001  Window *pWin = new SfxFrameObjectWindow_Impl( pObj, pBW, WB_CLIPCHILDREN );
//STRIP001  SetEditWin( pWin );
//STRIP001  pWin->Show();
//STRIP001
//STRIP001  // Fenster zuordnen (fuers Resize)
//STRIP001  pBW->SetObjWin( pWin );
//STRIP001 }

//=========================================================================
//STRIP001 SfxFrameObjectEnv_Impl::~SfxFrameObjectEnv_Impl()
/*  [Beschreibung]

    Die angelegten Fenster werden zerst"ort.
*/
//STRIP001 {
//STRIP001  Window *pWin = GetEditWin();
//STRIP001  pWin->Hide();
//STRIP001  SetEditWin( NULL );
//STRIP001  delete pWin;
//STRIP001  DeleteWindows();
//STRIP001 }

//STRIP001 void SfxFrameObjectEnv_Impl::ReleaseFrame()
//STRIP001 {
//STRIP001  pFrameObject->ReleaseFrame_Impl();
//STRIP001 }

//=========================================================================
//============== SfxFrameObject ===========================================
//=========================================================================
/*N*/ SO2_IMPL_BASIC_CLASS1_DLL( SfxFrameObject, SvFactory, SvInPlaceObject,
/*N*/             SvGlobalName( BF_SO3_IFRAME_CLASSID ) )

//=========================================================================
/*?*/ SfxFrameObject::SfxFrameObject()
/*?*/   : pImpl( new SfxFrameObject_Impl )
/*  [Beschreibung]

    Konstruktor der Klasse SfxFrameObject. Die Verbliste und das
    Format werden global initialisiert.
*/
/*?*/ {
/*?*/   // Verben der Superklasse bekanntgeben, um GetVerbs nicht
/*?*/   // ueberlagern zu muessen
/*?*/ //    SetTypeList( SvDataTypeList() );
/*?*/   SvVerbList *pVerbs = new SvVerbList;
/*?*/   pVerbs->Append( SvVerb( 1, String( SfxResId( STR_FRAMEOBJECT_PROPERTIES ) ) ) );
/*?*/   SetVerbList( pVerbs );
/*?*/ }

//=========================================================================
/*?*/ SfxFrameObject::~SfxFrameObject()
/*  [Beschreibung]

    Destruktor der Klasse SfxFrameObject.
*/
/*?*/ {
/*?*/   delete pImpl;
/*?*/ }

//=========================================================================
/*?*/ IMPL_LINK( SfxFrameObject, NewObjectHdl_Impl, Timer *, pTimer )
/*  [Beschreibung]

    Wurde kein URL im Objekt gesetzt, dann fragt es im InPlaceActivate
    nach einem. Dies muss asynchron geschehen, da in den H„ndlern
    des IP-Protocol eine modale Dialogbox verboten ist.
*/
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/     sfx2::FileDialogHelper aDlg( WB_OPEN );
//STRIP001 /*?*/
//STRIP001 /*?*/     if( ERRCODE_NONE == aDlg.Execute() )
//STRIP001 /*?*/    {
//STRIP001 /*?*/         String aName( URIHelper::SmartRelToAbs( aDlg.GetPath() ) );
//STRIP001 /*?*/
//STRIP001 /*?*/        // Namen "ubertragen
//STRIP001 /*?*/        pImpl->pFrmDescr->SetURL( aName );
//STRIP001 /*?*/        pImpl->pFrame->GetDescriptor()->SetURL( aName );
//STRIP001 /*?*/        pImpl->pFrame->Update();
//STRIP001 /*?*/    }
/*?*/
/*?*/     return 0;
/*?*/ }

//=========================================================================
/*N*/ BOOL SfxFrameObject::ConstructFrame()
/*  [Beschreibung]

    Die Methode erzeugt den Frame. Es ist notwendig, da\s das Objekt
    InPlace-Active ist.
*/
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  // Nur in SfxApps kann ein Frame aufgebaut werden
//STRIP001  SfxInPlaceClientRef aClient = GetIPClient();
//STRIP001  if ( !aClient.Is() )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  DBG_ASSERT( !pImpl->pFrame, "Doppelter Aufruf ConstructFrame!" );
//STRIP001  if ( !pImpl->pFrame)
//STRIP001  {
//STRIP001      pImpl->xDoc.Clear();
//STRIP001
//STRIP001      // Der Frame erh"alt als Parent den ViewFrame seines Clients
//STRIP001      SfxViewFrame *pView = aClient->GetViewShell()->GetViewFrame();
//STRIP001      SfxFrame *pParent = pView->GetFrame();
//STRIP001
//STRIP001      // Den URLFrame erzeugen, der l"adt dann asynchron das Dokument
//STRIP001      pImpl->pFrame = new SfxURLFrame( pImpl->pFrmDescr->Clone(),
//STRIP001          pImpl->pEnv, pImpl->pEnv, pParent );
//STRIP001
//STRIP001      // Dieser Frame wird nicht "uber eine Id, sondern "uber seinen
//STRIP001      // Objektnamen identifiziert; daher auf keinen Fall die Id setzen,
//STRIP001      // wohl aber den IdName.
//STRIP001      pImpl->pFrame->SetFrameIdName_Impl( GetParent()->Find(this)->GetObjName() );
//STRIP001  }
//STRIP001
//STRIP001  // Focus setzen, Frame zieht ihn dann auf seine ViewShell weiter
/*N*/   return TRUE;
/*N*/ }

//=========================================================================
//STRIP001 void SfxFrameObject::DataChanged_Impl
//STRIP001 (
//STRIP001  BOOL bOnlyEmbedSource   /* TRUE, es "andert sich nur die persistenten
//STRIP001                             Daten. FALSE, auch das MetaFile "andert
//STRIP001                             sich */
//STRIP001 )
/*  [Beschreibung]

    Wenn die Daten sich "andern, muss das Modify-Flag gesetzt werden.
    Ausserdem m"ussen alle angemeldeten Advises benachrichtigt werden.
    In Abh"angigkeit des Parameters wird angezeigt, dass sich auch
    die View und das Mtf ge"andert hat.
*/
//STRIP001 {
//STRIP001  if( IsEnableSetModified() )
//STRIP001  { // nicht im init oder deinit
//STRIP001      SetModified( TRUE );
//STRIP001      if( bOnlyEmbedSource )
//STRIP001      {
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          ViewChanged( ASPECT_CONTENT );
//STRIP001      }
//STRIP001  }
//STRIP001 }

//=========================================================================
//STRIP001 void SfxFrameObject::FillClass
//STRIP001 (
//STRIP001  SvGlobalName * pClassName,  /* Der Typ der Klasse */
//STRIP001  ULONG * pFormat,            /* Das Dateiformat in dem geschrieben wird */
//STRIP001  String * pAppName,          /* Der Applikationsname */
//STRIP001  String * pFullTypeName,     /* Der genaue Name des Typs */
//STRIP001     String * pShortTypeName     /* Der kurze Name des Typs  */
//STRIP001     , long /* nFileFormat */
//STRIP001 ) const
/*  [Beschreibung]

    Mit dieser Methode werden Informationen "uber das Objekt angefordert.
    Wird das Objekt gesichert, dann werden diese Informationen in den
    Storage geschrieben.

    [Anmerkung]
*/
//STRIP001 {
//STRIP001  *pClassName     = *GetSvFactory();
//STRIP001  *pFormat        = 0;
//STRIP001  *pAppName       = DEFINE_CONST_UNICODE( "StarDivision FloatingFrame 1.0" );
//STRIP001  *pFullTypeName  = DEFINE_CONST_UNICODE( "StarDivision FloatingFrame 1.0" );
//STRIP001  *pShortTypeName = DEFINE_CONST_UNICODE( "FloatingFrame" );
//STRIP001 }

//=========================================================================
//STRIP001 void SfxFrameObject::Open
//STRIP001 (
//STRIP001  BOOL bOpen  /* TRUE, es handelt sich um eine Open.
//STRIP001                 FALSE, es handelt sich um Close. */
//STRIP001 )
/*  [Beschreibung]

    Die Verbindung zum Client wird ge"offnet oder geschlossen.

    [Querverweise]

    <SvEmbeddedObject::Open()>
*/
//STRIP001 {
//STRIP001  // l"asst Environment los
//STRIP001  SvInPlaceObject::Open( bOpen );
//STRIP001 }

//=========================================================================
//STRIP001 void SfxFrameObject::InPlaceActivate
//STRIP001 (
//STRIP001  BOOL bActivate  /* TRUE, InPlace Aktivierung beginnt.
//STRIP001                     FALSE, InPlace Aktivierung endet. */
//STRIP001 )
/*  [Beschreibung]

    Das Objekt wird InPlace aktiviert oder deaktiviert.

    [Querverweise]

    <SvInPlaceObject::InPlaceActivate()>
*/
//STRIP001 {
//STRIP001  if( bActivate )
//STRIP001  {
//STRIP001      SvContainerEnvironment* pEnv = GetIPClient()->GetEnv();
//STRIP001      pImpl->pEnv = new SfxFrameObjectEnv_Impl( pEnv, this );
//STRIP001
//STRIP001      // wird in die Verwaltung eingesetzt
//STRIP001      SetIPEnv( pImpl->pEnv );
//STRIP001      pImpl->pEnv->GetClipWin()->Show();
//STRIP001
//STRIP001      if( !ConstructFrame() )
//STRIP001      {
//STRIP001          // Es konnte kein Frame erzeugt werden, da der Client keine
//STRIP001          // SfxApp ist
//STRIP001          DoClose();
//STRIP001          return;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  SvInPlaceObject::InPlaceActivate( bActivate );
//STRIP001
//STRIP001  if( !bActivate )
//STRIP001  {
//STRIP001      DELETEZ( pImpl->pNewObjectTimer );
//STRIP001      if ( pImpl->pFrame )
//STRIP001      {
//STRIP001          // Dokument bis zum Abr"aumen des Frames festhalten
//STRIP001          pImpl->xDoc = pImpl->pFrame->GetCurrentDocument();
//STRIP001
//STRIP001          // Frame hat sich noch nicht abgemeldet
//STRIP001          if ( pImpl->xDoc.Is() )
//STRIP001              pImpl->xDoc->SetModified(FALSE);
//STRIP001          pImpl->pFrame->DoClose();
//STRIP001          pImpl->pFrame = NULL;
//STRIP001      }
//STRIP001
//STRIP001      DELETEZ( pImpl->pEnv );
//STRIP001  }
//STRIP001 }

//=========================================================================
//STRIP001 ErrCode SfxFrameObject::Verb
//STRIP001 (
//STRIP001  long                nVerb,      /* welche Art des Aktivierens ist
//STRIP001                                     gew"unscht */
//STRIP001  SvEmbeddedClient *  pCl,        /* Callback-Svhnittstelle des Aufruffers */
//STRIP001  Window *            pWin,       /* Parent auf dem aktiviert werden soll */
//STRIP001  const Rectangle * pWorkRectPixel/* Position und Gr"osse, an der das Objekt
//STRIP001                                     aktiviert werden soll */
//STRIP001 )
/*  [Beschreibung]

    Es wird Versucht ein Applet zu starten. Es gibt nur die M"oglichkeit
    InPlace zu aktivieren. Deshalb sind auch nur die Verben gestattet,
    die dies ausl"osen.

    [R"uckgabewert]

    BOOL            TRUE, es wurde InPlace aktiviert.
                    FALSE, es wurde nicht InPLace aktiviert.

    [Querverweise]

    <SvPseudoObject::Verb>
*/
//STRIP001 {
//STRIP001  ErrCode nRet = ERRCODE_SO_NOT_INPLACEACTIVE;
//STRIP001  switch( nVerb )
//STRIP001  {
//STRIP001      case SVVERB_SHOW:
//STRIP001      case SVVERB_IPACTIVATE:
//STRIP001      case 0L:
//STRIP001          nRet = GetProtocol().IPProtocol();
//STRIP001          break;
//STRIP001      case SVVERB_HIDE:
//STRIP001          nRet = DoInPlaceActivate( FALSE );
//STRIP001          break;
//STRIP001      case 2:
//STRIP001          {
//STRIP001 /*
//STRIP001              SfxObjectShell* pObj = pImpl->pFrame->GetCurrentDocument();
//STRIP001              if ( pObj )
//STRIP001              {
//STRIP001                  String aFileName( pObj->GetMedium()->GetName() );
//STRIP001                  if ( aFileName.Len() )
//STRIP001                  {
//STRIP001                      SfxStringItem aName( SID_FILE_NAME, aFileName );
//STRIP001                      SfxBoolItem aCreateView( SID_OPEN_NEW_VIEW, TRUE );
//STRIP001                      SFX_APP()->GetAppDispatcher().Execute( SID_OPENDOC,
//STRIP001                              SFX_CALLMODE_ASYNCHRON, &aName,
//STRIP001                              &aCreateView, 0L);
//STRIP001                      bRet = TRUE;
//STRIP001                  }
//STRIP001              }
//STRIP001 */
//STRIP001              break;
//STRIP001          }
//STRIP001      case 1:
//STRIP001          {
//STRIP001              SfxInPlaceClientRef aClient = GetIPClient();
//STRIP001              if ( !aClient.Is() )
//STRIP001                  return ERRCODE_SO_NOT_INPLACEACTIVE;
//STRIP001
//STRIP001              // Dialogaufruf gew"unscht; FrameDescriptor zur ItemId suchen
//STRIP001              SfxFrameDescriptor *pD = pImpl->pFrmDescr;
//STRIP001              String aName = GetParent()->Find(this)->GetObjName();
//STRIP001
//STRIP001              // Der Objectname als FrameName soll nur intern sein
//STRIP001              if ( pD->GetName() == aName)
//STRIP001                  pD->SetName( String() );
//STRIP001
//STRIP001              SfxItemSet aSet( SFX_APP()->GetPool(), SID_FRAMEDESCRIPTOR, SID_FRAMEDESCRIPTOR );
//STRIP001              SfxFrameDescriptorItem aItem( pD );
//STRIP001              aSet.Put( aItem );
//STRIP001
//STRIP001              SfxFrameObjectEditDialog_Impl *pDlg = new SfxFrameObjectEditDialog_Impl(
//STRIP001                      &aClient->GetViewShell()->GetViewFrame()->GetWindow(),
//STRIP001                      aSet,
//STRIP001                      SID_FRAMEDESCRIPTOR );
//STRIP001
//STRIP001              int nChanged = pDlg->Execute();
//STRIP001              if ( nChanged == RET_OK )
//STRIP001              {
//STRIP001                  // Item auswerten und in Descriptor "ubernehmen
//STRIP001                  const SfxPoolItem *pItem;
//STRIP001                  SfxItemState eState = pDlg->GetOutputItemSet()->GetItemState( SID_FRAMEDESCRIPTOR, FALSE, &pItem );
//STRIP001                  if ( eState == SFX_ITEM_SET )
//STRIP001                      pD->TakeProperties( ((SfxFrameDescriptorItem*)pItem)->GetProperties() );
//STRIP001                  DataChanged_Impl( FALSE );
//STRIP001              }
//STRIP001
//STRIP001              // Falls der Benutzer keinen Namen vergeben hat, den internen wieder einsetzen
//STRIP001              if ( ! pD->GetName().Len() )
//STRIP001                  pD->SetName( aName );
//STRIP001
//STRIP001              // ggf. Frame updaten
//STRIP001              if ( nChanged == RET_OK && pImpl->pFrame )
//STRIP001              {
//STRIP001                  SfxFrameDescriptor *pFD = pImpl->pFrame->GetDescriptor();
//STRIP001                  SfxFrameSetDescriptor *pSD = pFD->GetParent();
//STRIP001                  pImpl->pFrame->Update( pImpl->pFrmDescr->Clone( pSD ) );
//STRIP001                  delete pFD;
//STRIP001              }
//STRIP001
//STRIP001              nRet = ERRCODE_NONE;
//STRIP001              delete pDlg;
//STRIP001              break;
//STRIP001          }
//STRIP001  }
//STRIP001  return nRet;
//STRIP001 }

//=========================================================================
//STRIP001 void SfxFrameObject::SetVisArea
//STRIP001 (
//STRIP001  const Rectangle & rVisArea  /* neue Position und Groesse des
//STRIP001                                 sichtbaren Ausschnitts */
//STRIP001 )
/*  [Beschreibung]

    Der sichtbare Ausschnitt beginnt immer an der Position (0, 0).
*/
//STRIP001 {
//STRIP001  Rectangle aR( rVisArea );
//STRIP001  aR.SetPos( Point() );
//STRIP001  SvInPlaceObject::SetVisArea( aR );
//STRIP001
//STRIP001  DataChanged_Impl( TRUE );
//STRIP001 /*
//STRIP001  if ( pImpl->pFrame )
//STRIP001  {
//STRIP001      SfxObjectShell *pDoc = pImpl->pFrame->GetCurrentDocument();
//STRIP001      if ( pDoc && pDoc->GetInPlaceObject() )
//STRIP001          pDoc->GetInPlaceObject()->SetVisArea( rVisArea );
//STRIP001  }
//STRIP001 */
//STRIP001 }

//STRIP001 Rectangle SfxFrameObject::GetVisArea( USHORT nAspect ) const
//STRIP001 {
//STRIP001 /*
//STRIP001  if ( pImpl->pFrame || pImpl->xDoc.Is() )
//STRIP001  {
//STRIP001      SfxObjectShell* pDoc;
//STRIP001      if(pImpl->pFrame)
//STRIP001          pDoc = pImpl->pFrame->GetCurrentDocument();
//STRIP001      else
//STRIP001          pDoc = pImpl->xDoc;
//STRIP001      if ( pDoc && pDoc->GetInPlaceObject() )
//STRIP001          return pDoc->GetInPlaceObject()->GetVisArea( nAspect );
//STRIP001  }
//STRIP001 */
//STRIP001  return SvInPlaceObject::GetVisArea( nAspect );
//STRIP001 }

//=========================================================================
// aus PlugIn
//STRIP001 void SoPaintReplacement( const Rectangle &rRect, String &rText,
//STRIP001                       OutputDevice *pOut );

//=========================================================================
//STRIP001 void SfxFrameObject::Draw
//STRIP001 (
//STRIP001  OutputDevice *  pDev,   /* in dieses Device findet die Ausgabe statt */
//STRIP001  const JobSetup &rSetup, /* fuer dieses Device soll formatiert werden */
//STRIP001  USHORT          nAspect /* Darstellungsvariante des Objektes */
//STRIP001 )
/*  [Beschreibung]

    Ein Ausgabe ist nicht m"oglich und auch nicht n"otig.
    und als Unterschrift der URL ausgegeben,

    [Querverweise]

    <SvEmbeddedObject::Draw>
*/
//STRIP001 {
//STRIP001  if ( !pImpl->pFrame )
//STRIP001  {
//STRIP001 /*
//STRIP001      if ( pImpl->xDoc.Is() && pImpl->xDoc->GetInPlaceObject() )
//STRIP001      {
//STRIP001          SfxInPlaceObject *pObj = pImpl->xDoc->GetInPlaceObject();
//STRIP001          pObj->DoDraw( pDev, Point(), pObj->GetVisArea().GetSize(),
//STRIP001              rSetup, nAspect );
//STRIP001      }
//STRIP001      else
//STRIP001 */
//STRIP001      {
//STRIP001          Rectangle aVisArea = GetVisArea( nAspect );
//STRIP001          String aString( DEFINE_CONST_UNICODE( "FloatingFrame" ) );
//STRIP001          SoPaintReplacement( aVisArea, aString, pDev );
//STRIP001      }
//STRIP001  }
//STRIP001 }

//=========================================================================
//STRIP001 BOOL SfxFrameObject::InitNew
//STRIP001 (
//STRIP001  SvStorage * pStor   /* Storage auf dem das Objekt arbeitet. Der kann
//STRIP001                         auch NULL sein, das Bedeutet, es wird auf einem
//STRIP001                         tempor"aren Storage gearbeitet */
//STRIP001 )
/*  [Beschreibung]

    Nach dem Konstruktor muss diese Methode oder Load gerufen werden,
    um das Objekt zu initialisieren.
    <SvPersist::InitNew>

    [R"uckgabewert]

    BOOL            TRUE, Initialisierung hat geklappt.
                    FALSE, Initialisierung hat nicht geklappt, das Objekt
                    muss sofort freigegeben werden.

    [Querverweise]

*/
//STRIP001 {
//STRIP001  if( SvInPlaceObject::InitNew( pStor ) )
//STRIP001  {
//STRIP001      // Standardgr"osse
//STRIP001      SetVisArea( Rectangle( Point(), Size( 10000, 5000 ) ) );
//STRIP001      return TRUE;
//STRIP001  }
//STRIP001  return FALSE;
//STRIP001 }

//=========================================================================
/*N*/ static const char * pDocName = "FloatingFrame";
#define nVersion 3

/*N*/ BOOL SfxFrameObject::Load
/*N*/ (
/*N*/   SvStorage * pStor   /* Storage aus dem das Objekt geladen wird. */
/*N*/ )
/*  [Beschreibung]

    Nach dem Konstruktor muss diese Methode oder InitNew gerufen werden,
    um das Objekt zu initialisieren.

    [R"uckgabewert]

    BOOL            TRUE, das Objekt wurde geladen.
                    FALSE, das Objekt wurde nicht geladen, es
                    muss sofort freigegeben werden.

    [Querverweise]

    <SvPersist::Load>
*/
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  if( SvInPlaceObject::Load( pStor ) )
//STRIP001  {
//STRIP001      SvStorageStreamRef xStm;
//STRIP001      xStm = pStor->OpenStream( String::CreateFromAscii( pDocName ), STREAM_STD_READ );
//STRIP001      xStm->SetBufferSize( 8192 );
//STRIP001
//STRIP001      // nicht vorhandener Stream ist kein Fehler
//STRIP001      if( xStm->GetError() == SVSTREAM_FILE_NOT_FOUND )
//STRIP001          return TRUE;
//STRIP001
//STRIP001      BYTE nFileVersion;
//STRIP001      *xStm >> nFileVersion;
//STRIP001      if( nFileVersion < nVersion )
//STRIP001          pImpl->pFrmDescr->Load( *xStm, 2 );
//STRIP001      else
//STRIP001          pImpl->pFrmDescr->Load( *xStm, nFileVersion );
//STRIP001
//STRIP001      return xStm->GetError() == ERRCODE_NONE;
//STRIP001  }
/*N*/   return FALSE;
/*N*/ }

//=========================================================================
/*N*/ BOOL SfxFrameObject::Save()
/*  [Beschreibung]

    Der Inhalt des Objektes wird in den, in <SfxFrameObject::InitNew>
    oder <SfxFrameObject::Load> "ubergebenen Storage, geschrieben.

    [R"uckgabewert]

    BOOL            TRUE, das Objekt wurde geschreiben.
                    FALSE, das Objekt wurde nicht geschrieben. Es muss
                    die in der Klasse <SvPersist> beschrieben
                    Fehlerbehandlung erfolgen.

    [Querverweise]

    <SvPersist::Save>
*/
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  if( SvInPlaceObject::Save() )
//STRIP001  {
//STRIP001      SvStorageStreamRef xStm;
//STRIP001      xStm = GetStorage()->OpenStream( String::CreateFromAscii( pDocName ),
//STRIP001                                       STREAM_STD_WRITE | STREAM_TRUNC );
//STRIP001      xStm->SetBufferSize( 8192 );
//STRIP001
//STRIP001      *xStm << (BYTE) nVersion;
//STRIP001      pImpl->pFrmDescr->Store( *xStm );
//STRIP001      return xStm->GetError() == ERRCODE_NONE;
//STRIP001  }
/*N*/   return FALSE;
/*N*/ }

//=========================================================================
/*N*/ BOOL SfxFrameObject::SaveAs
/*N*/ (
/*N*/   SvStorage *pStor    /* Storage, in den der Inhalt des Objekte
                           geschrieben wird */
/*N*/ )
/*  [Beschreibung]

    Der Inhalt des Objektes wird in pStor geschrieben.

    [Anmerkung]

    Der Storage wird nicht behalten.

    [R"uckgabewert]

    BOOL            TRUE, das Objekt wurde geschreiben.
                    FALSE, das Objekt wurde nicht geschrieben. Es muss
                    die in der Klasse <SvPersist> beschrieben
                    Fehlerbehandlung erfolgen.

    [Querverweise]

    <SvPersist::SaveAs>
*/
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  if( SvInPlaceObject::SaveAs( pStor ) )
//STRIP001  {
//STRIP001      SvStorageStreamRef xStm;
//STRIP001      xStm = pStor->OpenStream( String::CreateFromAscii( pDocName ),
//STRIP001                                STREAM_STD_WRITE | STREAM_TRUNC );
//STRIP001      xStm->SetBufferSize( 8192 );
//STRIP001
//STRIP001      *xStm << (BYTE) nVersion;
//STRIP001      pImpl->pFrmDescr->Store( *xStm );
//STRIP001
//STRIP001      return xStm->GetError() == ERRCODE_NONE;
//STRIP001  }
/*N*/   return FALSE;
/*N*/ }

//=========================================================================
//STRIP001 void SfxFrameObject::HandsOff()
/*  [Beschreibung]

    Ab diesen Zeitpunkt, bis zum <SfxFrameObject::SaveCompleted>,
    darf auf den Storage im Objekt nicht zugegriffen werden.

    [Querverweise]

    <SvPersist::HandsOff>
*/
//STRIP001 {
//STRIP001  SvInPlaceObject::HandsOff();
//STRIP001 }

//=========================================================================
/*N*/ BOOL SfxFrameObject::SaveCompleted
/*N*/ (
/*N*/   SvStorage * pStor   /* Storage auf dem das Objekt arbeitet. Der kann
                           auch NULL sein. Dies Bedeutet, es wird auf
                           dem alten Storage weiter gearbeitet */
/*N*/ )
/*  [Beschreibung]

    Nach dem Aufruf dieser Methode ist das Verhalten des Objektes
    wieder definiert.

    [R"uckgabewert]

    BOOL            TRUE, es kann auf dem neuen Storage gearbeitet werden.
                    FALSE, es kann nicht auf dem neuen Storage gearbeitet
                    werden

    [Querverweise]

    <SvPersist::SaveCompleted>
*/
/*N*/ {
/*N*/   return SvInPlaceObject::SaveCompleted( pStor );
/*N*/ }

//=========================================================================
//STRIP001 ULONG SfxFrameObject::GetMiscStatus() const
/*  [Beschreibung]

    Da ein Applet immer aktiviert wird, es ein Link ist und er
    keine UI-Tools braucht, muss dieser Status zur"uckgegeben werden.

    [R"uckgabewert]

    ULONG           Es wird immer  SVOBJ_MISCSTATUS_LINK,
                    SVOBJ_MISCSTATUS_INSIDEOUT und
                    SVOBJ_MISCSTATUS_ACTIVATEWHENVISIBLE zur"uckgegeben

    [Querverweise]

    <SvPseudoObject::GetMiscStatus()>
*/
//STRIP001 {
//STRIP001  ULONG nMisc = 0;
//STRIP001
//STRIP001  //nMisc = SVOBJ_MISCSTATUS_LINK;
//STRIP001  nMisc |= SVOBJ_MISCSTATUS_INSIDEOUT;
//STRIP001  nMisc |= SVOBJ_MISCSTATUS_ACTIVATEWHENVISIBLE;
//STRIP001     nMisc |= SVOBJ_MISCSTATUS_SPECIALOBJECT;
//STRIP001  return nMisc;
//STRIP001 }

//=========================================================================
//STRIP001 BOOL SfxFrameObject::IsLink() const
/*  [Beschreibung]

    Dieser Typ von Objekt ist immer ein Link.

    [R"uckgabewert]

    BOOL            Immer TRUE.

    [Querverweise]

    <SvPseudoObject::IsLink()>
*/
//STRIP001 {
//STRIP001  //return TRUE;
//STRIP001  return FALSE;
//STRIP001 }

/*?*/ void SfxFrameObject::SetFrameDescriptor( const SfxFrameDescriptor *pD )
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  DBG_ASSERT( pD, "Kein Descriptor!" );
//STRIP001  if ( pD )
//STRIP001  {
//STRIP001      if ( pImpl->pFrmDescr )
//STRIP001          delete pImpl->pFrmDescr;
//STRIP001      pImpl->pFrmDescr = pD->Clone( NULL );
//STRIP001      if ( pImpl->pFrame )
//STRIP001      {
//STRIP001          SfxFrameDescriptor *pFD = pImpl->pFrame->GetDescriptor();
//STRIP001          SfxFrameSetDescriptor *pSD = pFD->GetParent();
//STRIP001          pImpl->pFrame->Update( pImpl->pFrmDescr->Clone( pSD ) );
//STRIP001          delete pFD;
//STRIP001      }
//STRIP001
//STRIP001      DataChanged_Impl( FALSE );
//STRIP001  }
/*?*/ }

/*?*/ const SfxFrameDescriptor* SfxFrameObject::GetFrameDescriptor() const
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); return NULL;//STRIP001
//STRIP001 /*?*/    return pImpl->pFrmDescr;
/*?*/ }

//STRIP001 SfxFrame* SfxFrameObject::GetFrame() const
//STRIP001 {
//STRIP001  return pImpl->pFrame;
//STRIP001 }

//STRIP001 void SfxFrameObject::ReleaseFrame_Impl()
//STRIP001 {
//STRIP001  pImpl->pFrame = NULL;
//STRIP001 }

/*N*/ SfxFrameObjectFactoryPtr* SfxFrameObject::GetFactoryPtr()
/*N*/ {
/*N*/   return SFX_APP()->Get_Impl()->pSfxFrameObjectFactoryPtr;
/*N*/ }

}
