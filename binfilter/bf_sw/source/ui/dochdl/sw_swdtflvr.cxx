/*************************************************************************
 *
 *  $RCSfile: sw_swdtflvr.cxx,v $
 *
 *  $Revision: 1.7 $
 *
 *  last change: $Author: rt $ $Date: 2005-01-11 11:55:23 $
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

#ifdef PRECOMPILED
// auto strip #include "ui_pch.hxx"
#endif

#pragma hdrstop

// auto strip #ifndef _SOT_FORMATS_HXX
// auto strip #include <sot/formats.hxx>
// auto strip #endif
// auto strip #ifndef _LINKMGR_HXX
// auto strip #include <so3/linkmgr.hxx>
// auto strip #endif
// auto strip #ifndef _URLOBJ_HXX
// auto strip #include <tools/urlobj.hxx>
// auto strip #endif
#ifndef _PASTEDLG_HXX
#include <so3/pastedlg.hxx>
#endif
// auto strip #ifndef _WRKWIN_HXX
// auto strip #include <vcl/wrkwin.hxx>
// auto strip #endif
// auto strip #ifndef _MSGBOX_HXX
// auto strip #include <vcl/msgbox.hxx>
// auto strip #endif
// auto strip #ifndef _SFXDISPATCH_HXX
// auto strip #include <bf_sfx2/dispatch.hxx>
// auto strip #endif
// auto strip #ifndef _SFXSTRITEM_HXX
// auto strip #include <svtools/stritem.hxx>
// auto strip #endif
// auto strip #ifndef _IMAP_HXX
// auto strip #include <svtools/imap.hxx>
// auto strip #endif
// auto strip #ifndef _SVSTOR_HXX
// auto strip #include <so3/svstor.hxx>
// auto strip #endif
// auto strip #ifndef _GRAPH_HXX
// auto strip #include <vcl/graph.hxx>
// auto strip #endif
// auto strip #ifndef SVTOOLS_URIHELPER_HXX
// auto strip #include <svtools/urihelper.hxx>
// auto strip #endif
// auto strip #ifndef _SVDMODEL_HXX
// auto strip #include <bf_svx/svdmodel.hxx>
// auto strip #endif
// auto strip #ifndef _SVX_XEXCH_HXX
// auto strip #include <bf_svx/xexch.hxx>
// auto strip #endif
// auto strip #ifndef _SVX_DBAEXCHANGE_HXX_
// auto strip #include <bf_svx/dbaexchange.hxx>
// auto strip #endif
// auto strip #ifndef _SFXFRAME_HXX
// auto strip #include <bf_sfx2/frame.hxx>
// auto strip #endif
#ifndef _SVX_CLIPFMTITEM_HXX
#include <bf_svx/clipfmtitem.hxx>
#endif
// auto strip #ifndef _MIECLIP_HXX
// auto strip #include <bf_sfx2/mieclip.hxx>
// auto strip #endif
// auto strip #ifndef _OFF_APP_HXX
// auto strip #include <bf_offmgr/app.hxx>
// auto strip #endif
// auto strip #ifndef _SVDETC_HXX
// auto strip #include <bf_svx/svdetc.hxx>
// auto strip #endif
// auto strip #ifndef _XOUTBMP_HXX
// auto strip #include <bf_svx/xoutbmp.hxx>
// auto strip #endif
// auto strip #ifndef _URLBMK_HXX
// auto strip #include <svtools/urlbmk.hxx>
// auto strip #endif
// auto strip #ifndef _HTMLOUT_HXX
// auto strip #include <svtools/htmlout.hxx>
// auto strip #endif
// auto strip #ifndef _SVX_HLNKITEM_HXX
// auto strip #include <bf_svx/hlnkitem.hxx>
// auto strip #endif
// auto strip #ifndef _INETIMG_HXX
// auto strip #include <svtools/inetimg.hxx>
// auto strip #endif
#ifndef _SVX_PAPERINF_HXX
#include <bf_svx/paperinf.hxx>
#endif
#ifndef _SVX_FMVIEW_HXX
#include <bf_svx/fmview.hxx>
#endif
// auto strip #ifndef _SVX_IMPGRF_HXX
// auto strip #include <bf_svx/impgrf.hxx>
// auto strip #endif
// auto strip #ifndef _SVX_SCRIPTTYPEITEM_HXX
// auto strip #include <bf_svx/scripttypeitem.hxx>
// auto strip #endif
// auto strip #ifndef _SOT_FORMATS_HXX
// auto strip #include <sot/formats.hxx>
// auto strip #endif
// auto strip #ifndef _SFX_DOCFILT_HACK_HXX
// auto strip #include <bf_sfx2/docfilt.hxx>
// auto strip #endif
// auto strip #ifndef _FILELIST_HXX
// auto strip #include <so3/filelist.hxx>
// auto strip #endif
// auto strip #ifndef _LINKSRC_HXX
// auto strip #include <so3/linksrc.hxx>
// auto strip #endif
// auto strip #ifndef _GOODIES_IMAPOBJ_HXX
// auto strip #include <svtools/imapobj.hxx>
// auto strip #endif
// auto strip #ifndef _SFXDOCFILE_HXX
// auto strip #include <bf_sfx2/docfile.hxx>
// auto strip #endif
// auto strip #ifndef _UNOTOOLS_TRANSLITERATIONWRAPPER_HXX
// auto strip #include <unotools/transliterationwrapper.hxx>
// auto strip #endif
// auto strip #ifndef _UTL_STREAM_WRAPPER_HXX_
// auto strip #include <unotools/streamwrap.hxx>
// auto strip #endif

// auto strip #include <bf_svx/unomodel.hxx>

// auto strip #ifndef _FMTURL_HXX
// auto strip #include <fmturl.hxx>
// auto strip #endif
// auto strip #ifndef _FMTINFMT_HXX
// auto strip #include <fmtinfmt.hxx>
// auto strip #endif
// auto strip #ifndef _FMTFSIZE_HXX
// auto strip #include <fmtfsize.hxx>
// auto strip #endif
#ifndef _SWDTFLVR_HXX
#include <swdtflvr.hxx>
#endif
// auto strip #ifndef _SHELLIO_HXX
// auto strip #include <shellio.hxx>
// auto strip #endif
// auto strip #ifndef _DDEFLD_HXX
// auto strip #include <ddefld.hxx>
// auto strip #endif

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _PAGEDESC_HXX
#include <pagedesc.hxx>
#endif
// auto strip #ifndef _BOOKMRK_HXX
// auto strip #include <bookmrk.hxx>
// auto strip #endif
// auto strip #ifndef _DOCARY_HXX
// auto strip #include <docary.hxx>
// auto strip #endif
// auto strip #ifndef _SECTION_HXX
// auto strip #include <section.hxx>
// auto strip #endif
// auto strip #ifndef _NDTXT_HXX
// auto strip #include <ndtxt.hxx>
// auto strip #endif
// auto strip #ifndef _EDTWIN_HXX
// auto strip #include <edtwin.hxx>
// auto strip #endif
// auto strip #ifndef _NAVICONT_HXX
// auto strip #include <navicont.hxx>
// auto strip #endif
// auto strip #ifndef _SWCONT_HXX
// auto strip #include <swcont.hxx>
// auto strip #endif
#ifndef _WRTSH_HXX
#include <wrtsh.hxx>
#endif
#ifndef _SWMODULE_HXX
#include <swmodule.hxx>
#endif
#ifndef _VIEW_HXX
#include <view.hxx>
#endif
// auto strip #ifndef _HINTIDS_HXX
// auto strip #include <hintids.hxx>
// auto strip #endif
// auto strip #ifndef _DOCSH_HXX
// auto strip #include <docsh.hxx>
// auto strip #endif
#ifndef _WDOCSH_HXX
#include <wdocsh.hxx>
#endif
// auto strip #ifndef _FLDBAS_HXX
// auto strip #include <fldbas.hxx>     //DDE
// auto strip #endif
// auto strip #ifndef _SWUNDO_HXX
// auto strip #include <swundo.hxx>     // fuer Undo-Ids
// auto strip #endif
// auto strip #ifndef _PAM_HXX
// auto strip #include <pam.hxx>
// auto strip #endif
// auto strip #ifndef _NDOLE_HXX
// auto strip #include <ndole.hxx>
// auto strip #endif
// auto strip #ifndef _FRMFMT_HXX
// auto strip #include <frmfmt.hxx>
// auto strip #endif
// auto strip #ifndef _SWWAIT_HXX
// auto strip #include <swwait.hxx>
// auto strip #endif
// auto strip #ifndef _VIEWOPT_HXX
// auto strip #include <viewopt.hxx>
// auto strip #endif
// auto strip #ifndef _SWUNODEF_HXX
// auto strip #include <swunodef.hxx>
// auto strip #endif
// auto strip #ifndef _SV_SOUND_HXX
// auto strip #include <vcl/sound.hxx>
// auto strip #endif

#ifndef _SWSWERROR_H
#include <swerror.h>
#endif
#ifndef _CMDID_H
#include <cmdid.h>
#endif
#ifndef _DOCHDL_HRC
#include <dochdl.hrc>
#endif
#ifndef _GLOBALS_HRC
#include <globals.hrc>
#endif
// auto strip #include <sot/stg.hxx>

// #108584#
// auto strip #ifndef _SVDITER_HXX
// auto strip #include <bf_svx/svditer.hxx>
// auto strip #endif

// #108584#
// auto strip #ifndef _EEITEM_HXX
// auto strip #include <bf_svx/eeitem.hxx>
// auto strip #endif

// #108584#
// auto strip #ifndef _SVX_FHGTITEM_HXX
// auto strip #include <bf_svx/fhgtitem.hxx>
// auto strip #endif

// #108584#
// auto strip #ifndef _SVDPAGE_HXX
// auto strip #include <bf_svx/svdpage.hxx>
// auto strip #endif

// #109590#
// auto strip #ifndef _SWCRSR_HXX
// auto strip #include <swcrsr.hxx>
// auto strip #endif
#ifndef _OSL_ENDIAN_H_
#include <osl/endian.h>
#endif
#include "so3/staticbaseurl.hxx"
namespace binfilter {

extern BOOL bFrmDrag;
extern BOOL bDDINetAttr;
extern BOOL bExecuteDrag;


#define OLESIZE lA4Width - 2 * lMinBorder, 6 * MM50

#define SWTRANSFER_OBJECTTYPE_DRAWMODEL         0x00000001
#define SWTRANSFER_OBJECTTYPE_HTML              0x00000002
#define SWTRANSFER_OBJECTTYPE_RTF               0x00000004
#define SWTRANSFER_OBJECTTYPE_STRING            0x00000008
#define SWTRANSFER_OBJECTTYPE_SWOLE             0x00000010
#define SWTRANSFER_OBJECTTYPE_DDE               0x00000020

using namespace ::binfilter::svx;
using namespace ::rtl;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::datatransfer;

#ifdef DDE_AVAILABLE

#ifdef PM2
#define DDE_TXT_ENCODING    RTL_TEXTENCODING_IBM_850
#else
#define DDE_TXT_ENCODING    RTL_TEXTENCODING_MS_1252
#endif

//---------------------------------------------
// this struct conforms to the Microsoft
// OBJECTDESCRIPTOR -> see oleidl.h
// (MS platform sdk)
//---------------------------------------------

///*N*/ struct OleObjectDescriptor
///*N*/ {
///*N*/         sal_uInt32      cbSize;
///*N*/         ClsId           clsid;
///*N*/         sal_uInt32      dwDrawAspect;
///*N*/         Size            sizel;
///*N*/         Point           pointl;
///*N*/         sal_uInt32      dwStatus;
///*N*/         sal_uInt32      dwFullUserTypeName;
///*N*/         sal_uInt32      dwSrcOfCopy;
///*N*/ };

//STRIP001 class SwTrnsfrDdeLink : public ::so3::SvBaseLink
//STRIP001 {
//STRIP001  String sName;
//STRIP001  ::so3::SvLinkSourceRef refObj;
//STRIP001  SwTransferable& rTrnsfr;
//STRIP001  SwDocShell* pDocShell;
//STRIP001  ULONG nOldTimeOut;
//STRIP001  BOOL bDelBookmrk : 1;
//STRIP001  BOOL bInDisconnect : 1;
//STRIP001
//STRIP001  BOOL FindDocShell();
//STRIP001
//STRIP001 protected:
//STRIP001  virtual ~SwTrnsfrDdeLink();
//STRIP001
//STRIP001 public:
//STRIP001  SwTrnsfrDdeLink( SwTransferable& rTrans, SwWrtShell& rSh );
//STRIP001
//STRIP001  virtual void DataChanged( const String& rMimeType,
//STRIP001                            const ::com::sun::star::uno::Any & rValue );
//STRIP001  virtual void Closed();
//STRIP001
//STRIP001  BOOL WriteData( SvStream& rStrm );
//STRIP001  void Disconnect( BOOL bRemoveDataAdvise = TRUE );
//STRIP001 };

#endif

// helper class for Action and Undo enclosing
//STRIP001 class SwTrnsfrActionAndUndo
//STRIP001 {
//STRIP001  SwWrtShell *pSh;
//STRIP001  USHORT nUndoId;
//STRIP001 public:
//STRIP001  SwTrnsfrActionAndUndo( SwWrtShell *pS, USHORT nId, BOOL bDelSel = FALSE )
//STRIP001      : pSh( pS ), nUndoId( nId )
//STRIP001  {
//STRIP001      pSh->StartUndo( nUndoId );
//STRIP001      if( bDelSel )
//STRIP001          pSh->DelRight();
//STRIP001      pSh->StartAllAction();
//STRIP001  }
//STRIP001  ~SwTrnsfrActionAndUndo()
//STRIP001  {
//STRIP001      pSh->EndUndo( nUndoId );
//STRIP001      pSh->EndAllAction();
//STRIP001  }
//STRIP001 };


// -----------------------------------------------------------------------

//STRIP001 SwTransferable::SwTransferable( SwWrtShell& rSh )
//STRIP001  : pWrtShell( &rSh ),
//STRIP001    pCreatorView( 0 ),
//STRIP001  eBufferType( TRNSFR_NONE ),
//STRIP001  pClpDocFac( 0 ),
//STRIP001  pClpGraphic( 0 ),
//STRIP001  pClpBitmap( 0 ),
//STRIP001  pOrigGrf( 0 ),
//STRIP001  pBkmk( 0 ),
//STRIP001  pImageMap( 0 ),
//STRIP001  pTargetURL( 0 )
//STRIP001 {
//STRIP001     rSh.GetView().AddTransferable(*this);
//STRIP001     SwDocShell* pDShell = rSh.GetDoc()->GetDocShell();
//STRIP001  if( pDShell )
//STRIP001  {
//STRIP001      pDShell->FillTransferableObjectDescriptor( aObjDesc );
//STRIP001      if( pDShell->GetMedium() )
//STRIP001      {
//STRIP001          const INetURLObject& rURLObj = pDShell->GetMedium()->GetURLObject();
//STRIP001          aObjDesc.maDisplayName = URIHelper::removePassword(
//STRIP001                              rURLObj.GetMainURL( INetURLObject::NO_DECODE ),
//STRIP001                              INetURLObject::WAS_ENCODED,
//STRIP001                              INetURLObject::DECODE_UNAMBIGUOUS );
//STRIP001      }
//STRIP001  }
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 SwTransferable::~SwTransferable()
//STRIP001 {
//STRIP001     Application::GetSolarMutex().acquire();
//STRIP001
//STRIP001 #ifdef DDE_AVAILABLE
//STRIP001  // der DDELink braucht noch die WrtShell!
//STRIP001  if( refDdeLink.Is() )
//STRIP001  {
//STRIP001      ((SwTrnsfrDdeLink*)&refDdeLink)->Disconnect();
//STRIP001      refDdeLink.Clear();
//STRIP001  }
//STRIP001 #endif
//STRIP001
//STRIP001  pWrtShell = 0;
//STRIP001
//STRIP001     // dvo 2002-05-30, #99239#: release reference to the document so that
//STRIP001     // aDocShellRef will delete it (if aDocShellRef is set). Otherwise, the OLE
//STRIP001     // nodes keep references to their sub-storage when the storage is already
//STRIP001     // dead.
//STRIP001  delete pClpDocFac;
//STRIP001
//STRIP001  //JP 22.04.95: erst schliessen, dann kann die Ref. auch gecleared werden,
//STRIP001  //              so das die DocShell auch tatsaechlich geloescht wird!
//STRIP001  if( aDocShellRef.Is() )
//STRIP001  {
//STRIP001      SvEmbeddedObject * pObj = aDocShellRef;
//STRIP001      SwDocShell* pDocSh = (SwDocShell*)pObj;
//STRIP001      pDocSh->DoClose();
//STRIP001  }
//STRIP001  aDocShellRef.Clear();
//STRIP001
//STRIP001  SwModule* pMod = SW_MOD();
//STRIP001     if(pMod)
//STRIP001     {
//STRIP001         if ( pMod->pClipboard == this )
//STRIP001             pMod->pClipboard = 0;
//STRIP001         else if ( pMod->pDragDrop == this )
//STRIP001             pMod->pDragDrop = 0;
//STRIP001         else if ( pMod->pXSelection == this )
//STRIP001             pMod->pXSelection = 0;
//STRIP001     }
//STRIP001
//STRIP001  delete pClpGraphic;
//STRIP001  delete pClpBitmap;
//STRIP001  delete pImageMap;
//STRIP001  delete pTargetURL;
//STRIP001  delete pBkmk;
//STRIP001
//STRIP001
//STRIP001  eBufferType = TRNSFR_NONE;
//STRIP001
//STRIP001     Application::GetSolarMutex().release();
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 void SwTransferable::ObjectReleased()
//STRIP001 {
//STRIP001  SwModule *pMod = SW_MOD();
//STRIP001  if( this == pMod->pClipboard )
//STRIP001      pMod->pClipboard = 0;
//STRIP001  else if( this == pMod->pDragDrop )
//STRIP001      pMod->pDragDrop = 0;
//STRIP001  else if( this == pMod->pXSelection )
//STRIP001      pMod->pXSelection = 0;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 void SwTransferable::AddSupportedFormats()
//STRIP001 {
//STRIP001  // only need if we are the current XSelection Object
//STRIP001  SwModule *pMod = SW_MOD();
//STRIP001  if( this == pMod->pXSelection )
//STRIP001  {
//STRIP001      SetDataForDragAndDrop( Point( 0,0) );
//STRIP001  }
//STRIP001 }

// -----------------------------------------------------------------------

/*N*/  void SwTransferable::InitOle( SvEmbeddedObjectRef rRef, SwDoc& rDoc )
/*N*/  {
/*N*/   //OleVisArea einstellen. Linke obere Ecke der Seite und Groesse
/*N*/   //der RealSize in Twips.
/*N*/   const Size aSz( OLESIZE );
/*N*/   SwRect aVis( Point( DOCUMENTBORDER, DOCUMENTBORDER ), aSz );
/*N*/   rRef->SetVisArea( aVis.SVRect() );
/*N*/   rDoc.SetBrowseMode( TRUE );
/*N*/  }

// -----------------------------------------------------------------------

//STRIP001 SvEmbeddedObject* SwTransferable::FindOLEObj() const
//STRIP001 {
//STRIP001  SvEmbeddedObject* pRet = 0;
//STRIP001  if( pClpDocFac )
//STRIP001  {
//STRIP001      SwClientIter aIter( *(SwModify*)pClpDocFac->GetDoc()->
//STRIP001                          GetDfltGrfFmtColl() );
//STRIP001      for( SwCntntNode* pNd = (SwCntntNode*)aIter.First( TYPE( SwCntntNode ) );
//STRIP001              pNd; pNd = (SwCntntNode*)aIter.Next() )
//STRIP001          if( ND_OLENODE == pNd->GetNodeType() )
//STRIP001          {
//STRIP001              pRet = &((SwOLENode*)pNd)->GetOLEObj().GetOleRef();
//STRIP001              break;
//STRIP001          }
//STRIP001  }
//STRIP001  return pRet;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 void SwTransferable::RemoveDDELinkFormat( const Window& rWin )
//STRIP001 {
//STRIP001  RemoveFormat( SOT_FORMATSTR_ID_LINK );
//STRIP001  CopyToClipboard( (Window*)&rWin );
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 sal_Bool SwTransferable::GetData( const DATA_FLAVOR& rFlavor )
//STRIP001 {
//STRIP001  sal_uInt32  nFormat = SotExchange::GetFormat( rFlavor );
//STRIP001
    // we can only fullfil the request if
    // 1) we have data for this format
    // 2) we have either a clipboard document (pClpDocFac), or
    //    we have a SwWrtShell (so we can generate a new clipboard document)
//STRIP001     if( !HasFormat( nFormat ) || ( pClpDocFac == NULL && pWrtShell == NULL ) )
//STRIP001      return sal_False;
//STRIP001
//STRIP001  if( !pClpDocFac )
//STRIP001  {
//STRIP001      USHORT nSelectionType = pWrtShell->GetSelectionType();
//STRIP001
//STRIP001 // SEL_GRF kommt vom ContentType der editsh
//STRIP001      if( (SwWrtShell::SEL_GRF | SwWrtShell::SEL_DRW_FORM) & nSelectionType )
//STRIP001      {
//STRIP001          pClpGraphic = new Graphic;
//STRIP001          if( !pWrtShell->GetDrawObjGraphic( FORMAT_GDIMETAFILE, *pClpGraphic ))
//STRIP001              pOrigGrf = pClpGraphic;
//STRIP001          pClpBitmap = new Graphic;
//STRIP001          if( !pWrtShell->GetDrawObjGraphic( FORMAT_BITMAP, *pClpBitmap ))
//STRIP001              pOrigGrf = pClpBitmap;
//STRIP001
//STRIP001          // ist es ein URL-Button ?
//STRIP001          String sURL, sDesc;
//STRIP001          if( pWrtShell->GetURLFromButton( sURL, sDesc ) )
//STRIP001          {
//STRIP001              pBkmk = new INetBookmark( sURL, sDesc );
//STRIP001              eBufferType = TRNSFR_INETFLD;
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      pClpDocFac = new SwDocFac;
//STRIP001      SwDoc* pTmpDoc = pClpDocFac->GetDoc();
//STRIP001
//STRIP001         const SfxDocumentInfo * pInfo = pWrtShell->GetInfo();
//STRIP001         if (pInfo)
//STRIP001             pTmpDoc->SetInfo(*pInfo);
//STRIP001
//STRIP001      pTmpDoc->SetRefForDocShell( (SvEmbeddedObjectRef*)&(long&)aDocShellRef );
//STRIP001      pTmpDoc->LockExpFlds();     // nie die Felder updaten - Text so belassen
//STRIP001      pWrtShell->Copy( pTmpDoc );
//STRIP001
//STRIP001      // es wurde in der CORE eine neu angelegt (OLE-Objekte kopiert!)
//STRIP001      if( aDocShellRef.Is() )
//STRIP001          SwTransferable::InitOle( aDocShellRef, *pTmpDoc );
//STRIP001      pTmpDoc->SetRefForDocShell( 0 );
//STRIP001
//STRIP001      if( nSelectionType & SwWrtShell::SEL_TXT && !pWrtShell->HasMark() )
//STRIP001      {
//STRIP001          SwContentAtPos aCntntAtPos( SwContentAtPos::SW_INETATTR );
//STRIP001
//STRIP001          Point aPos( SwEditWin::GetDDStartPosX(), SwEditWin::GetDDStartPosY());
//STRIP001
//STRIP001          BOOL bSelect = bExecuteDrag &&
//STRIP001                          pWrtShell->GetView().GetDocShell() &&
//STRIP001                          !pWrtShell->GetView().GetDocShell()->IsReadOnly();
//STRIP001          if( pWrtShell->GetContentAtPos( aPos, aCntntAtPos, bSelect ) )
//STRIP001          {
//STRIP001              pBkmk = new INetBookmark(
//STRIP001                      ((SwFmtINetFmt*)aCntntAtPos.aFnd.pAttr)->GetValue(),
//STRIP001                      aCntntAtPos.sStr );
//STRIP001              eBufferType = TRNSFR_INETFLD;
//STRIP001              if( bSelect )
//STRIP001                  pWrtShell->SelectTxtAttr( RES_TXTATR_INETFMT );
//STRIP001          }
//STRIP001      }
//STRIP001      if( pWrtShell->IsFrmSelected() )
//STRIP001      {
//STRIP001          SfxItemSet aSet( pWrtShell->GetAttrPool(), RES_URL, RES_URL );
//STRIP001          pWrtShell->GetFlyFrmAttr( aSet );
//STRIP001          const SwFmtURL& rURL = (SwFmtURL&)aSet.Get( RES_URL );
//STRIP001          if( rURL.GetMap() )
//STRIP001              pImageMap = new ImageMap( *rURL.GetMap() );
//STRIP001          else if( rURL.GetURL().Len() )
//STRIP001              pTargetURL = new INetImage( aEmptyStr, rURL.GetURL(),
//STRIP001                                          rURL.GetTargetFrameName(),
//STRIP001                                          aEmptyStr, Size() );
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  sal_Bool    bOK = sal_False;
//STRIP001  if( TRNSFR_OLE == eBufferType )
//STRIP001  {
//STRIP001      // aus dem ClipDoc das OLE-Object besorgen und von dem die Daten
//STRIP001      // besorgen.
//STRIP001      SvEmbeddedObject* pObj = FindOLEObj();
//STRIP001      if( pObj )
//STRIP001      {
//STRIP001          TransferableDataHelper aD( pObj->CreateTransferableSnapshot() );
//STRIP001          ::com::sun::star::uno::Any aAny( aD.GetAny( rFlavor ));
//STRIP001          if( aAny.hasValue() )
//STRIP001              bOK = SetAny( aAny, rFlavor );
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      switch( nFormat )
//STRIP001      {
//STRIP001 #ifdef DDE_AVAILABLE
//STRIP001      case SOT_FORMATSTR_ID_LINK:
//STRIP001          if( refDdeLink.Is() )
//STRIP001              bOK = SetObject( &refDdeLink,
//STRIP001                                  SWTRANSFER_OBJECTTYPE_DDE, rFlavor );
//STRIP001          break;
//STRIP001 #endif
//STRIP001      case SOT_FORMATSTR_ID_OBJECTDESCRIPTOR:
//STRIP001      case SOT_FORMATSTR_ID_LINKSRCDESCRIPTOR:
//STRIP001          bOK = SetTransferableObjectDescriptor( aObjDesc, rFlavor );
//STRIP001          break;
//STRIP001
//STRIP001      case SOT_FORMATSTR_ID_DRAWING:
//STRIP001          {
//STRIP001              SwDoc *pDoc = pClpDocFac->GetDoc();
//STRIP001              ASSERT( pDoc, "Document not found" );
//STRIP001              bOK = SetObject( pDoc->GetDrawModel(),
//STRIP001                              SWTRANSFER_OBJECTTYPE_DRAWMODEL, rFlavor );
//STRIP001          }
//STRIP001          break;
//STRIP001
//STRIP001      case SOT_FORMAT_STRING:
//STRIP001          bOK = SetObject( pClpDocFac->GetDoc(),
//STRIP001                              SWTRANSFER_OBJECTTYPE_STRING, rFlavor );
//STRIP001          break;
//STRIP001
//STRIP001      case SOT_FORMAT_RTF:
//STRIP001          bOK = SetObject( pClpDocFac->GetDoc(),
//STRIP001                              SWTRANSFER_OBJECTTYPE_RTF, rFlavor );
//STRIP001          break;
//STRIP001
//STRIP001      case SOT_FORMATSTR_ID_HTML:
//STRIP001          bOK = SetObject( pClpDocFac->GetDoc(),
//STRIP001                              SWTRANSFER_OBJECTTYPE_HTML, rFlavor );
//STRIP001          break;
//STRIP001
//STRIP001      case SOT_FORMATSTR_ID_SVXB:
//STRIP001          if( eBufferType & TRNSFR_GRAPHIC && pOrigGrf )
//STRIP001              bOK = SetGraphic( *pOrigGrf, rFlavor );
//STRIP001          break;
//STRIP001
//STRIP001      case SOT_FORMAT_GDIMETAFILE:
//STRIP001          if( eBufferType & TRNSFR_GRAPHIC )
//STRIP001              bOK = SetGDIMetaFile( pClpGraphic->GetGDIMetaFile(), rFlavor );
//STRIP001          break;
//STRIP001      case SOT_FORMAT_BITMAP:
//STRIP001          if( eBufferType & TRNSFR_GRAPHIC )
//STRIP001              bOK = SetBitmap( (pClpBitmap ? pClpBitmap
//STRIP001                                           : pClpGraphic)->GetBitmap(),
//STRIP001                               rFlavor );
//STRIP001          break;
//STRIP001
//STRIP001      case SOT_FORMATSTR_ID_SVIM:
//STRIP001          if( pImageMap )
//STRIP001              bOK = SetImageMap( *pImageMap, rFlavor );
//STRIP001          break;
//STRIP001
//STRIP001      case SOT_FORMATSTR_ID_INET_IMAGE:
//STRIP001          if( pTargetURL )
//STRIP001              bOK = SetINetImage( *pTargetURL, rFlavor );
//STRIP001          break;
//STRIP001
//STRIP001      case SOT_FORMATSTR_ID_SOLK:
//STRIP001      case SOT_FORMATSTR_ID_NETSCAPE_BOOKMARK:
//STRIP001      case SOT_FORMATSTR_ID_FILEGRPDESCRIPTOR:
//STRIP001      case SOT_FORMATSTR_ID_FILECONTENT:
//STRIP001      case SOT_FORMATSTR_ID_UNIFORMRESOURCELOCATOR:
//STRIP001      case SOT_FORMAT_FILE:
//STRIP001          if( (TRNSFR_INETFLD & eBufferType) && pBkmk )
//STRIP001              bOK = SetINetBookmark( *pBkmk, rFlavor );
//STRIP001          break;
//STRIP001
//STRIP001      case SOT_FORMATSTR_ID_EMBED_SOURCE:
//STRIP001 //       default:
//STRIP001          if( !aDocShellRef.Is() )
//STRIP001          {
//STRIP001              SwDoc *pDoc = pClpDocFac->GetDoc();
//STRIP001              SwDocShell* pNewDocSh = new SwDocShell( pDoc,
//STRIP001                                       SFX_CREATE_MODE_EMBEDDED );
//STRIP001              aDocShellRef = pNewDocSh;
//STRIP001              aDocShellRef->DoInitNew( NULL );
//STRIP001              SwTransferable::InitOle( aDocShellRef, *pDoc );
//STRIP001          }
//STRIP001          bOK = SetObject( &aDocShellRef, SWTRANSFER_OBJECTTYPE_SWOLE,
//STRIP001                          rFlavor );
//STRIP001          break;
//STRIP001      }
//STRIP001  }
//STRIP001  return bOK;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 sal_Bool SwTransferable::WriteObject( SotStorageStreamRef& xStream,
//STRIP001                                  void* pObject, sal_uInt32 nObjectType,
//STRIP001                                  const DATA_FLAVOR& rFlavor )
//STRIP001 {
//STRIP001  sal_Bool bRet = sal_False;
//STRIP001  WriterRef xWrt;
//STRIP001
//STRIP001  switch( nObjectType )
//STRIP001  {
//STRIP001  case SWTRANSFER_OBJECTTYPE_DRAWMODEL:
//STRIP001      {
//STRIP001          //JP 28.02.2001: dont change the sequence of commands - Bug 8
//STRIP001          SdrModel *pModel = (SdrModel*)pObject;
//STRIP001          pModel->SetStreamingSdrModel( TRUE );
//STRIP001          xStream->SetBufferSize( 16348 );
//STRIP001
//STRIP001          // #108584#
//STRIP001          // for the changed pool defaults from drawing layer pool set those
//STRIP001          // attributes as hard attributes to preserve them for saving
//STRIP001          const SfxItemPool& rItemPool = pModel->GetItemPool();
//STRIP001          const SvxFontHeightItem& rDefaultFontHeight = (const SvxFontHeightItem&)rItemPool.GetDefaultItem(EE_CHAR_FONTHEIGHT);
//STRIP001
//STRIP001          // SW should have no MasterPages
//STRIP001          DBG_ASSERT(0L == pModel->GetMasterPageCount(), "SW with MasterPages (!)");
//STRIP001
//STRIP001          for(sal_uInt16 a(0); a < pModel->GetPageCount(); a++)
//STRIP001          {
//STRIP001              const SdrPage* pPage = pModel->GetPage(a);
//STRIP001              SdrObjListIter aIter(*pPage, IM_DEEPNOGROUPS);
//STRIP001
//STRIP001              while(aIter.IsMore())
//STRIP001              {
//STRIP001                  SdrObject* pObj = aIter.Next();
//STRIP001                  const SvxFontHeightItem& rItem = (const SvxFontHeightItem&)pObj->GetItem(EE_CHAR_FONTHEIGHT);
//STRIP001
//STRIP001                  if(rItem.GetHeight() == rDefaultFontHeight.GetHeight())
//STRIP001                  {
//STRIP001                      pObj->SetItem(rDefaultFontHeight);
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001
//STRIP001          {
//STRIP001              ::com::sun::star::uno::Reference< ::com::sun::star::io::XOutputStream> xDocOut( new utl::OOutputStreamWrapper( *xStream ) );
//STRIP001              if( SvxDrawingLayerExport( pModel, xDocOut ) )
//STRIP001                  xStream->Commit();
//STRIP001          }
//STRIP001
//STRIP001          pModel->SetStreamingSdrModel( FALSE );
//STRIP001
//STRIP001          bRet = ERRCODE_NONE == xStream->GetError();
//STRIP001      }
//STRIP001      break;
//STRIP001
//STRIP001  case SWTRANSFER_OBJECTTYPE_SWOLE:
//STRIP001      {
//STRIP001          SvEmbeddedObject* pEmbObj = (SvEmbeddedObject*) pObject;
//STRIP001             SvStorageRef xWorkStore( new SvStorage( TRUE, *xStream ) );
//STRIP001
//STRIP001          xStream->SetBufferSize( 0xff00 );
//STRIP001
//STRIP001          // write document storage
//STRIP001          pEmbObj->SetupStorage( xWorkStore );
//STRIP001          bRet = pEmbObj->DoSaveAs( xWorkStore );
//STRIP001          pEmbObj->DoSaveCompleted();
//STRIP001          xWorkStore->Commit();
//STRIP001          xStream->Commit();
//STRIP001
//STRIP001          bRet = ERRCODE_NONE == xStream->GetError();
//STRIP001      }
//STRIP001      break;
//STRIP001
//STRIP001
//STRIP001  case SWTRANSFER_OBJECTTYPE_DDE:
//STRIP001 #ifdef DDE_AVAILABLE
//STRIP001      {
//STRIP001          xStream->SetBufferSize( 1024 );
//STRIP001          SwTrnsfrDdeLink* pDdeLnk = (SwTrnsfrDdeLink*)pObject;
//STRIP001          if( pDdeLnk->WriteData( *xStream ) )
//STRIP001          {
//STRIP001              xStream->Commit();
//STRIP001              bRet = ERRCODE_NONE == xStream->GetError();
//STRIP001          }
//STRIP001      }
//STRIP001 #endif
//STRIP001      break;
//STRIP001
//STRIP001  case SWTRANSFER_OBJECTTYPE_HTML:
//STRIP001      GetHTMLWriter( aEmptyStr, xWrt );
//STRIP001      break;
//STRIP001
//STRIP001  case SWTRANSFER_OBJECTTYPE_RTF:
//STRIP001      GetRTFWriter( aEmptyStr, xWrt );
//STRIP001      break;
//STRIP001
//STRIP001  case SWTRANSFER_OBJECTTYPE_STRING:
//STRIP001      GetASCWriter( aEmptyStr, xWrt );
//STRIP001      if( xWrt.Is() )
//STRIP001      {
//STRIP001          SwAsciiOptions aAOpt;
//STRIP001          aAOpt.SetCharSet( RTL_TEXTENCODING_UTF8 );
//STRIP001          xWrt->SetAsciiOptions( aAOpt );
//STRIP001
//STRIP001             // #102841# no start char for clipboard
//STRIP001             xWrt->bUCS2_WithStartChar = FALSE;
//STRIP001      }
//STRIP001      break;
//STRIP001  }
//STRIP001
//STRIP001  if( xWrt.Is() )
//STRIP001  {
//STRIP001      //JP 12.04.96: fuer die absoluten/relative Namen -> absolut lassen!
//STRIP001      SwDoc* pDoc = (SwDoc*)pObject;
//STRIP001      String sSave( so3::StaticBaseUrl::GetBaseURL() );
//STRIP001      so3::StaticBaseUrl::SetBaseURL( aEmptyStr );
//STRIP001
//STRIP001      xWrt->bWriteClipboardDoc = TRUE;
//STRIP001      xWrt->bWriteOnlyFirstTable = 0 != (TRNSFR_TABELLE & eBufferType);
//STRIP001      xWrt->SetShowProgress( FALSE );
//STRIP001      SwWriter aWrt( *xStream, *pDoc );
//STRIP001      if( !IsError( aWrt.Write( xWrt )) )
//STRIP001      {
//STRIP001          *xStream << '\0';               // terminate with a zero
//STRIP001          xStream->Commit();
//STRIP001          bRet = sal_True;
//STRIP001      }
//STRIP001      so3::StaticBaseUrl::SetBaseURL( sSave );
//STRIP001  }
//STRIP001
//STRIP001  return bRet;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 int SwTransferable::Cut()
//STRIP001 {
//STRIP001  int nRet = Copy( TRUE );
//STRIP001  if( nRet )
//STRIP001      DeleteSelection();
//STRIP001  return nRet;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 void SwTransferable::DeleteSelection()
//STRIP001 {
//STRIP001     if(!pWrtShell)
//STRIP001         return;
//STRIP001     // Selektionsart vor Action-Klammerung erfragen
//STRIP001  const int nSelection = pWrtShell->GetSelectionType();
//STRIP001  pWrtShell->StartUndo( UNDO_DELETE );
//STRIP001  if( ( SwWrtShell::SEL_TXT | SwWrtShell::SEL_TBL ) & nSelection )
//STRIP001      pWrtShell->IntelligentCut( nSelection );
//STRIP001  pWrtShell->DelRight();
//STRIP001  pWrtShell->EndUndo( UNDO_DELETE );
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 int SwTransferable::Copy( BOOL bIsCut )
//STRIP001 {
//STRIP001  int nRet = 1;
//STRIP001     if(!pWrtShell)
//STRIP001         return 0;;
//STRIP001
//STRIP001  String sGrfNm;
//STRIP001  const int nSelection = pWrtShell->GetSelectionType();
//STRIP001  if( nSelection == SwWrtShell::SEL_GRF )
//STRIP001  {
//STRIP001      pClpGraphic = new Graphic;
//STRIP001      if( !pWrtShell->GetDrawObjGraphic( FORMAT_GDIMETAFILE, *pClpGraphic ))
//STRIP001          pOrigGrf = pClpGraphic;
//STRIP001      pClpBitmap = new Graphic;
//STRIP001      if( !pWrtShell->GetDrawObjGraphic( FORMAT_BITMAP, *pClpBitmap ))
//STRIP001          pOrigGrf = pClpBitmap;
//STRIP001
//STRIP001      pClpDocFac = new SwDocFac;
//STRIP001      pWrtShell->Copy( pClpDocFac->GetDoc() );
//STRIP001
//STRIP001      if (! pOrigGrf->GetBitmap().IsEmpty())
//STRIP001        AddFormat( SOT_FORMATSTR_ID_SVXB );
//STRIP001
//STRIP001      AddFormat( SOT_FORMATSTR_ID_OBJECTDESCRIPTOR );
//STRIP001      const Graphic &rGrf = pWrtShell->GetGraphic();
//STRIP001      if( rGrf.IsSupportedGraphic() )
//STRIP001      {
//STRIP001          AddFormat( FORMAT_GDIMETAFILE );
//STRIP001          AddFormat( FORMAT_BITMAP );
//STRIP001      }
//STRIP001      eBufferType = TRNSFR_GRAPHIC;
//STRIP001      pWrtShell->GetGrfNms( &sGrfNm, 0 );
//STRIP001  }
//STRIP001  else if ( nSelection == SwWrtShell::SEL_OLE )
//STRIP001  {
//STRIP001      pClpDocFac = new SwDocFac;
//STRIP001      SwDoc *pDoc = pClpDocFac->GetDoc();
//STRIP001      aDocShellRef = new SwDocShell( pDoc, SFX_CREATE_MODE_EMBEDDED);
//STRIP001      aDocShellRef->DoInitNew( NULL );
//STRIP001      pWrtShell->Copy( pDoc );
//STRIP001
//STRIP001      AddFormat( SOT_FORMATSTR_ID_EMBED_SOURCE );
//STRIP001      AddFormat( SOT_FORMATSTR_ID_OBJECTDESCRIPTOR );
//STRIP001      AddFormat( FORMAT_GDIMETAFILE );
//STRIP001      eBufferType = TRNSFR_OLE;
//STRIP001  }
//STRIP001  //Gibt es ueberhaupt etwas zum bereitstellen?
//STRIP001  else if ( pWrtShell->IsSelection() || pWrtShell->IsFrmSelected() ||
//STRIP001            pWrtShell->IsObjSelected() )
//STRIP001  {
//STRIP001      SwWait *pWait = 0;
//STRIP001      if( pWrtShell->ShouldWait() )
//STRIP001          pWait = new SwWait( *pWrtShell->GetView().GetDocShell(), TRUE );
//STRIP001
//STRIP001      pClpDocFac = new SwDocFac;
//STRIP001
//STRIP001      // zusaetzlichen Cursor erzeugen, damit eine Gleichbehandlung
//STRIP001      // von Tastatur- und Mausselektion moeglich ist.
//STRIP001      // Im AddMode wird bei Tastaturselektion der neue Cursor erst
//STRIP001      // beim Bewegen des Cursors nach Selektionsende erzeugt.
//STRIP001      if( pWrtShell->IsAddMode() && pWrtShell->SwCrsrShell::HasSelection() )
//STRIP001          pWrtShell->CreateCrsr();
//STRIP001
//STRIP001      SwDoc* pTmpDoc = pClpDocFac->GetDoc();
//STRIP001
//STRIP001         const SfxDocumentInfo * pInfo = pWrtShell->GetInfo();
//STRIP001         if (pInfo)
//STRIP001             pTmpDoc->SetInfo(*pInfo);
//STRIP001
//STRIP001      pTmpDoc->SetRefForDocShell( (SvEmbeddedObjectRef*)&(long&)aDocShellRef );
//STRIP001      pTmpDoc->LockExpFlds();     // nie die Felder updaten - Text so belassen
//STRIP001      pWrtShell->Copy( pTmpDoc );
//STRIP001
//STRIP001 #ifdef DDE_AVAILABLE
//STRIP001      {
//STRIP001          // remove all DDE-Bookmarks, they are invalid inside the clipdoc!
//STRIP001          const SwBookmarks& rBkmk = pTmpDoc->GetBookmarks();
//STRIP001          for( USHORT n = rBkmk.Count(); n; )
//STRIP001              if( DDE_BOOKMARK == rBkmk[ --n ]->GetType() )
//STRIP001                  pTmpDoc->DelBookmark( n );
//STRIP001      }
//STRIP001 #endif
//STRIP001
//STRIP001      // es wurde in der CORE eine neu angelegt (OLE-Objekte kopiert!)
//STRIP001      if( aDocShellRef.Is() )
//STRIP001          SwTransferable::InitOle( aDocShellRef, *pTmpDoc );
//STRIP001      pTmpDoc->SetRefForDocShell( 0 );
//STRIP001
//STRIP001      if( pWrtShell->IsObjSelected() )
//STRIP001          eBufferType = TRNSFR_DRAWING;
//STRIP001      else
//STRIP001      {
//STRIP001          eBufferType = TRNSFR_DOCUMENT;
//STRIP001          if (pWrtShell->IntelligentCut(nSelection, FALSE) != SwWrtShell::NO_WORD)
//STRIP001              eBufferType = (TransferBufferType)(TRNSFR_DOCUMENT_WORD | eBufferType);
//STRIP001      }
//STRIP001
//STRIP001      int bDDELink = pWrtShell->IsSelection();
//STRIP001      if( nSelection & SwWrtShell::SEL_TBL_CELLS )
//STRIP001      {
//STRIP001          eBufferType = (TransferBufferType)(TRNSFR_TABELLE | eBufferType);
//STRIP001          bDDELink = pWrtShell->HasWholeTabSelection();
//STRIP001      }
//STRIP001
//STRIP001      //Wenn's einer braucht OLE'n wir ihm was.
//STRIP001      AddFormat( SOT_FORMATSTR_ID_EMBED_SOURCE );
//STRIP001      AddFormat( SOT_FORMATSTR_ID_OBJECTDESCRIPTOR );
//STRIP001
//STRIP001      //RTF vor das Metafile von OLE stellen, weil mit weniger verlusten
//STRIP001      //behaftet.
//STRIP001      if( !pWrtShell->IsObjSelected() )
//STRIP001      {
//STRIP001          AddFormat( FORMAT_RTF );
//STRIP001          AddFormat( SOT_FORMATSTR_ID_HTML );
//STRIP001      }
//STRIP001      if( pWrtShell->IsSelection() )
//STRIP001          AddFormat( FORMAT_STRING );
//STRIP001
//STRIP001      if( nSelection & ( SwWrtShell::SEL_DRW | SwWrtShell::SEL_DRW_FORM ))
//STRIP001      {
//STRIP001          AddFormat( SOT_FORMATSTR_ID_DRAWING );
//STRIP001          if ( nSelection & SwWrtShell::SEL_DRW )
//STRIP001          {
//STRIP001              AddFormat( FORMAT_GDIMETAFILE );
//STRIP001              AddFormat( FORMAT_BITMAP );
//STRIP001          }
//STRIP001          eBufferType = (TransferBufferType)( TRNSFR_GRAPHIC | eBufferType );
//STRIP001
//STRIP001          pClpGraphic = new Graphic;
//STRIP001          if( !pWrtShell->GetDrawObjGraphic( FORMAT_GDIMETAFILE, *pClpGraphic ))
//STRIP001              pOrigGrf = pClpGraphic;
//STRIP001          pClpBitmap = new Graphic;
//STRIP001          if( !pWrtShell->GetDrawObjGraphic( FORMAT_BITMAP, *pClpBitmap ))
//STRIP001              pOrigGrf = pClpBitmap;
//STRIP001
//STRIP001          // ist es ein URL-Button ?
//STRIP001          String sURL, sDesc;
//STRIP001          if( pWrtShell->GetURLFromButton( sURL, sDesc ) )
//STRIP001          {
//STRIP001              AddFormat( FORMAT_STRING );
//STRIP001                  AddFormat( SOT_FORMATSTR_ID_SOLK );
//STRIP001                  AddFormat( SOT_FORMATSTR_ID_NETSCAPE_BOOKMARK );
//STRIP001                  AddFormat( SOT_FORMATSTR_ID_FILECONTENT );
//STRIP001                  AddFormat( SOT_FORMATSTR_ID_FILEGRPDESCRIPTOR );
//STRIP001                  AddFormat( SOT_FORMATSTR_ID_UNIFORMRESOURCELOCATOR );
//STRIP001              eBufferType = (TransferBufferType)( TRNSFR_INETFLD | eBufferType );
//STRIP001              nRet = sal_True;
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001 #ifdef DDE_AVAILABLE
//STRIP001      // beim Cut hat DDE-Link keinen Sinn!!
//STRIP001      SwDocShell* pDShell;
//STRIP001      if( !bIsCut && bDDELink &&
//STRIP001          0 != ( pDShell = pWrtShell->GetDoc()->GetDocShell()) &&
//STRIP001          SFX_CREATE_MODE_STANDARD == pDShell->GetCreateMode() )
//STRIP001      {
//STRIP001          AddFormat( SOT_FORMATSTR_ID_LINK );
//STRIP001          refDdeLink = new SwTrnsfrDdeLink( *this, *pWrtShell );
//STRIP001      }
//STRIP001 #endif
//STRIP001      //ObjectDescriptor wurde bereits aus der alten DocShell gefuellt.
//STRIP001      //Jetzt noch anpassen. Dadurch kann im GetData die erste Anfrage
//STRIP001      //auch noch mit delayed rendering beantwortet werden.
//STRIP001      aObjDesc.mbCanLink = FALSE;
//STRIP001      Size aSz( OLESIZE );
//STRIP001      aObjDesc.maSize = OutputDevice::LogicToLogic( aSz, MAP_TWIP, MAP_100TH_MM );
//STRIP001
//STRIP001      delete pWait;
//STRIP001  }
//STRIP001  else
//STRIP001      nRet = 0;
//STRIP001
//STRIP001  if( pWrtShell->IsFrmSelected() )
//STRIP001  {
//STRIP001      SfxItemSet aSet( pWrtShell->GetAttrPool(), RES_URL, RES_URL );
//STRIP001      pWrtShell->GetFlyFrmAttr( aSet );
//STRIP001      const SwFmtURL& rURL = (SwFmtURL&)aSet.Get( RES_URL );
//STRIP001      if( rURL.GetMap() )
//STRIP001      {
//STRIP001          pImageMap = new ImageMap( *rURL.GetMap() );
//STRIP001          AddFormat( SOT_FORMATSTR_ID_SVIM );
//STRIP001      }
//STRIP001      else if( rURL.GetURL().Len() )
//STRIP001      {
//STRIP001          pTargetURL = new INetImage( sGrfNm, rURL.GetURL(),
//STRIP001                                      rURL.GetTargetFrameName(),
//STRIP001                                      aEmptyStr, Size() );
//STRIP001          AddFormat( SOT_FORMATSTR_ID_INET_IMAGE );
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  SW_MOD()->pClipboard = this;
//STRIP001  CopyToClipboard( &pWrtShell->GetView().GetEditWin() );
//STRIP001
//STRIP001  return nRet;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 int SwTransferable::CalculateAndCopy()
//STRIP001 {
//STRIP001     if(!pWrtShell)
//STRIP001         return 0;
//STRIP001     SwWait aWait( *pWrtShell->GetView().GetDocShell(), TRUE );
//STRIP001
//STRIP001  String aStr( pWrtShell->Calculate() );
//STRIP001
//STRIP001  pClpDocFac = new SwDocFac;
//STRIP001  pWrtShell->Copy( pClpDocFac->GetDoc(), &aStr);
//STRIP001  eBufferType = TRNSFR_DOCUMENT;
//STRIP001  AddFormat( FORMAT_STRING );
//STRIP001
//STRIP001  SW_MOD()->pClipboard = this;
//STRIP001  CopyToClipboard( &pWrtShell->GetView().GetEditWin() );
//STRIP001
//STRIP001  return 1;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 int SwTransferable::CopyGlossary( SwTextBlocks& rGlossary,
//STRIP001                                  const String& rStr )
//STRIP001 {
//STRIP001     if(!pWrtShell)
//STRIP001         return 0;
//STRIP001     SwWait aWait( *pWrtShell->GetView().GetDocShell(), TRUE );
//STRIP001
//STRIP001  pClpDocFac = new SwDocFac;
//STRIP001  SwDoc* pCDoc = pClpDocFac->GetDoc();
//STRIP001
//STRIP001  SwNodes& rNds = pCDoc->GetNodes();
//STRIP001  SwNodeIndex aNodeIdx( *rNds.GetEndOfContent().StartOfSectionNode() );
//STRIP001  SwCntntNode* pCNd = rNds.GoNext( &aNodeIdx ); // gehe zum 1. ContentNode
//STRIP001  SwPaM aPam( *pCNd );
//STRIP001
//STRIP001  pCDoc->SetRefForDocShell( (SvEmbeddedObjectRef*)&(long&)aDocShellRef );
//STRIP001  pCDoc->LockExpFlds();   // nie die Felder updaten - Text so belassen
//STRIP001
//STRIP001  pCDoc->InsertGlossary( rGlossary, rStr, aPam, 0 );
//STRIP001
//STRIP001  // es wurde in der CORE eine neu angelegt (OLE-Objekte kopiert!)
//STRIP001  if( aDocShellRef.Is() )
//STRIP001      SwTransferable::InitOle( aDocShellRef, *pCDoc );
//STRIP001  pCDoc->SetRefForDocShell( 0 );
//STRIP001
//STRIP001  eBufferType = TRNSFR_DOCUMENT;
//STRIP001
//STRIP001  //Wenn's einer braucht OLE'n wir ihm was.
//STRIP001  AddFormat( SOT_FORMATSTR_ID_EMBED_SOURCE );
//STRIP001  AddFormat( SOT_FORMATSTR_ID_OBJECTDESCRIPTOR );
//STRIP001  AddFormat( FORMAT_RTF );
//STRIP001  AddFormat( SOT_FORMATSTR_ID_HTML );
//STRIP001  AddFormat( FORMAT_STRING );
//STRIP001
//STRIP001  //ObjectDescriptor wurde bereits aus der alten DocShell gefuellt.
//STRIP001  //Jetzt noch anpassen. Dadurch kann im GetData die erste Anfrage
//STRIP001  //auch noch mit delayed rendering beantwortet werden.
//STRIP001  aObjDesc.mbCanLink = FALSE;
//STRIP001  Size aSz( OLESIZE );
//STRIP001  aObjDesc.maSize = OutputDevice::LogicToLogic( aSz, MAP_TWIP, MAP_100TH_MM );
//STRIP001
//STRIP001  SW_MOD()->pClipboard = this;
//STRIP001  CopyToClipboard( &pWrtShell->GetView().GetEditWin() );
//STRIP001
//STRIP001  return 1;
//STRIP001 }

/*N*/ static inline Reference < XTransferable > * lcl_getTransferPointer ( Reference < XTransferable > &xRef )
/*N*/ {
/*N*/   return &xRef;
/*N*/ }
// -----------------------------------------------------------------------

/*N*/ BOOL SwTransferable::IsPaste( const SwWrtShell& rSh,
/*N*/                             const TransferableDataHelper& rData )
/*N*/ {
/*N*/     // Check the common case first: We can always paste our own data!
/*N*/     // #106503#: If _only_ the internal format can be pasted, this check will
/*N*/     // yield 'true', while the one below would give a (wrong) result 'false'.
/*N*/     bool bIsPaste = ( SW_MOD()->pClipboard != NULL );
/*N*/
/*N*/     // if it's not our own data, we need to have a closer look:
/*N*/     if( ! bIsPaste )
/*N*/     {
/*N*/         // determine the proper paste action, and return true if we find one
/*N*/         Reference<XTransferable> xTransferable( rData.GetXTransferable() );
/*N*/         USHORT nDestination = SwTransferable::GetSotDestination( rSh );
/*N*/         USHORT nSourceOptions =
/*N*/                   (( EXCHG_DEST_DOC_TEXTFRAME == nDestination ||
/*N*/                      EXCHG_DEST_SWDOC_FREE_AREA == nDestination ||
/*N*/                      EXCHG_DEST_DOC_TEXTFRAME_WEB == nDestination ||
/*N*/                      EXCHG_DEST_SWDOC_FREE_AREA_WEB == nDestination )
/*N*/                                   ? EXCHG_IN_ACTION_COPY
/*N*/                      : EXCHG_IN_ACTION_MOVE);
/*N*/
/*N*/         ULONG nFormat;          // output param for GetExchangeAction
/*N*/         USHORT nEventAction;    // output param for GetExchangeAction
/*N*/         USHORT nAction = SotExchange::GetExchangeAction(
/*N*/                               rData.GetDataFlavorExVector(),
/*N*/                               nDestination,
/*N*/                               nSourceOptions,             /* ?? */
/*N*/                               EXCHG_IN_ACTION_DEFAULT,    /* ?? */
/*N*/                               nFormat, nEventAction, 0,
/*N*/                               lcl_getTransferPointer ( xTransferable ) );
/*N*/
/*N*/         // if we find a suitable action, we can paste!
/*N*/         bIsPaste = (EXCHG_INOUT_ACTION_NONE != nAction);
/*N*/     }
/*N*/
/*N*/   return bIsPaste;
/*N*/ }

// -----------------------------------------------------------------------

//STRIP001 int SwTransferable::Paste( SwWrtShell& rSh, TransferableDataHelper& rData )
//STRIP001 {
//STRIP001  USHORT nEventAction, nAction,
//STRIP001         nDestination = SwTransferable::GetSotDestination( rSh );
//STRIP001  ULONG nFormat;
//STRIP001
//STRIP001  if( SW_MOD()->pClipboard )
//STRIP001      nAction = EXCHG_OUT_ACTION_INSERT_PRIVATE;
//STRIP001  else
//STRIP001  {
//STRIP001      USHORT nSourceOptions =
//STRIP001                  (( EXCHG_DEST_DOC_TEXTFRAME == nDestination ||
//STRIP001                     EXCHG_DEST_SWDOC_FREE_AREA == nDestination ||
//STRIP001                     EXCHG_DEST_DOC_TEXTFRAME_WEB == nDestination ||
//STRIP001                     EXCHG_DEST_SWDOC_FREE_AREA_WEB == nDestination )
//STRIP001                                  ? EXCHG_IN_ACTION_COPY
//STRIP001                                  : EXCHG_IN_ACTION_MOVE);
//STRIP001         Reference<XTransferable> xTransferable( rData.GetXTransferable() );
//STRIP001      nAction = SotExchange::GetExchangeAction(
//STRIP001                                  rData.GetDataFlavorExVector(),
//STRIP001                                  nDestination,
//STRIP001                                  nSourceOptions,             /* ?? */
//STRIP001                                  EXCHG_IN_ACTION_DEFAULT,    /* ?? */
//STRIP001                                  nFormat, nEventAction, 0,
//STRIP001                                  lcl_getTransferPointer ( xTransferable ) );
//STRIP001  }
//STRIP001
//STRIP001  return EXCHG_INOUT_ACTION_NONE != nAction &&
//STRIP001          SwTransferable::PasteData( rData, rSh, nAction, nFormat,
//STRIP001                                         nDestination, FALSE, FALSE );
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 int SwTransferable::PasteData( TransferableDataHelper& rData,
//STRIP001                          SwWrtShell& rSh, USHORT nAction, ULONG nFormat,
//STRIP001                          USHORT nDestination, BOOL bIsPasteFmt,
//STRIP001                          sal_Bool bIsDefault,
//STRIP001                          const Point* pPt, sal_Int8 nDropAction,
//STRIP001                          BOOL bPasteSelection )
//STRIP001 {
//STRIP001  SwWait aWait( *rSh.GetView().GetDocShell(), FALSE );
//STRIP001  SwTrnsfrActionAndUndo* pAction = 0;
//STRIP001  SwModule* pMod = SW_MOD();
//STRIP001
//STRIP001  int nRet = 0;
//STRIP001
//STRIP001  if( pPt )
//STRIP001  {
//STRIP001      // external Drop
//STRIP001      if( bPasteSelection ? !pMod->pXSelection : !pMod->pDragDrop )
//STRIP001      {
//STRIP001          switch( nDestination )
//STRIP001          {
//STRIP001          case EXCHG_DEST_DOC_LNKD_GRAPH_W_IMAP:
//STRIP001          case EXCHG_DEST_DOC_LNKD_GRAPHOBJ:
//STRIP001          case EXCHG_DEST_DOC_GRAPH_W_IMAP:
//STRIP001          case EXCHG_DEST_DOC_GRAPHOBJ:
//STRIP001          case EXCHG_DEST_DOC_OLEOBJ:
//STRIP001          case EXCHG_DEST_DOC_DRAWOBJ:
//STRIP001          case EXCHG_DEST_DOC_URLBUTTON:
//STRIP001          case EXCHG_DEST_DOC_GROUPOBJ:
//STRIP001              // Rahmen/Objecte selektieren
//STRIP001              SwTransferable::SetSelInShell( rSh, TRUE, pPt );
//STRIP001              break;
//STRIP001
//STRIP001          // case EXCHG_DEST_DOC_TEXTFRAME:
//STRIP001          // case EXCHG_DEST_SWDOC_FREE_AREA:
//STRIP001          // case EXCHG_DEST_DOC_URLFIELD:
//STRIP001          default:
//STRIP001              SwTransferable::SetSelInShell( rSh, FALSE, pPt );
//STRIP001              break;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  else if( ( !pMod->pClipboard || bIsPasteFmt ) &&
//STRIP001          !rSh.IsTableMode() && rSh.HasSelection() )
//STRIP001  {
//STRIP001      // dann die Selektionen loeschen
//STRIP001
//STRIP001      //Selektierten Inhalt loeschen,
//STRIP001      // - nicht bei Tabellen-Selektion
//STRIP001      // - nicht bei ReRead einer Grafik/DDEDaten
//STRIP001      // - nicht bei D&D, fuer die richtige Selektion wurde im
//STRIP001      //      Drop-Handler gesorgt
//STRIP001      BOOL bDelSel = FALSE;
//STRIP001      switch( nDestination )
//STRIP001      {
//STRIP001      case EXCHG_DEST_DOC_TEXTFRAME:
//STRIP001      case EXCHG_DEST_SWDOC_FREE_AREA:
//STRIP001      case EXCHG_DEST_DOC_TEXTFRAME_WEB:
//STRIP001      case EXCHG_DEST_SWDOC_FREE_AREA_WEB:
//STRIP001          bDelSel = TRUE;
//STRIP001          break;
//STRIP001      }
//STRIP001
//STRIP001      if( bDelSel )
//STRIP001          pAction = new SwTrnsfrActionAndUndo( &rSh, UNDO_INSERT, TRUE );
//STRIP001  }
//STRIP001
//STRIP001  SwTransferable* pTrans;
//STRIP001  if( pPt && ( bPasteSelection ? 0 != ( pTrans = pMod->pXSelection )
//STRIP001                               : 0 != ( pTrans = pMod->pDragDrop) ))
//STRIP001  {
//STRIP001      // then internal Drag & Drop or XSelection
//STRIP001      nRet = pTrans->PrivateDrop( rSh, *pPt, DND_ACTION_MOVE == nDropAction,
//STRIP001                                  bPasteSelection );
//STRIP001  }
//STRIP001  else if( !pPt && 0 != ( pTrans = pMod->pClipboard ) &&
//STRIP001          EXCHG_OUT_ACTION_INSERT_PRIVATE == nAction )
//STRIP001  {
//STRIP001      // then internal paste
//STRIP001      nRet = pTrans->PrivatePaste( rSh );
//STRIP001  }
//STRIP001  else if( EXCHG_INOUT_ACTION_NONE != nAction )
//STRIP001  {
//STRIP001      if( !pAction )
//STRIP001          pAction = new SwTrnsfrActionAndUndo( &rSh, UNDO_INSERT );
//STRIP001
//STRIP001      // im Drag&Drop duerfen keine MessageBoxen angezeigt werden
//STRIP001      BOOL bMsg = 0 == pPt;
//STRIP001      BYTE nActionFlags = ( nAction >> 8 ) & 0xFF;
//STRIP001
//STRIP001      USHORT nClearedAction = ( nAction & EXCHG_ACTION_MASK );
//STRIP001      // Selektionen loeschen
//STRIP001
//STRIP001      switch( nClearedAction )
//STRIP001      {
//STRIP001      case EXCHG_OUT_ACTION_INSERT_PRIVATE:
//STRIP001 ASSERT( pPt, "EXCHG_OUT_ACTION_INSERT_PRIVATE: was soll hier passieren?" );
//STRIP001          break;
//STRIP001
//STRIP001      case EXCHG_OUT_ACTION_MOVE_PRIVATE:
//STRIP001 ASSERT( pPt, "EXCHG_OUT_ACTION_MOVE_PRIVATE: was soll hier passieren?" );
//STRIP001          break;
//STRIP001
//STRIP001
//STRIP001      case EXCHG_IN_ACTION_MOVE:
//STRIP001      case EXCHG_IN_ACTION_COPY:
//STRIP001      case EXCHG_IN_ACTION_LINK:
//STRIP001      case EXCHG_OUT_ACTION_INSERT_HTML:
//STRIP001      case EXCHG_OUT_ACTION_INSERT_STRING:
//STRIP001      case EXCHG_OUT_ACTION_INSERT_IMAGEMAP:
//STRIP001      case EXCHG_OUT_ACTION_REPLACE_IMAGEMAP:
//STRIP001
//STRIP001          // dann muss ueber das Format gegangen werden
//STRIP001          switch( nFormat )
//STRIP001          {
//STRIP001          case SOT_FORMATSTR_ID_DRAWING:
//STRIP001              nRet = SwTransferable::_PasteSdrFormat( rData, rSh,
//STRIP001                                              SW_PASTESDR_INSERT, pPt,
//STRIP001                                              nActionFlags );
//STRIP001              break;
//STRIP001
//STRIP001          case SOT_FORMATSTR_ID_HTML:
//STRIP001          case SOT_FORMATSTR_ID_HTML_SIMPLE:
//STRIP001          case SOT_FORMATSTR_ID_HTML_NO_COMMENT:
//STRIP001          case SOT_FORMAT_RTF:
//STRIP001          case SOT_FORMAT_STRING:
//STRIP001              nRet = SwTransferable::_PasteFileContent( rData, rSh,
//STRIP001                                                          nFormat, bMsg );
//STRIP001              break;
//STRIP001
//STRIP001          case SOT_FORMATSTR_ID_NETSCAPE_BOOKMARK:
//STRIP001              {
//STRIP001                  INetBookmark aBkmk;
//STRIP001                  if( rData.GetINetBookmark( nFormat, aBkmk ) )
//STRIP001                  {
//STRIP001                      SwFmtINetFmt aFmt( aBkmk.GetURL(), aEmptyStr );
//STRIP001                      rSh.InsertURL( aFmt, aBkmk.GetDescription() );
//STRIP001                      nRet = 1;
//STRIP001                  }
//STRIP001              }
//STRIP001              break;
//STRIP001
//STRIP001          case SOT_FORMATSTR_ID_SD_OLE:
//STRIP001              nRet = SwTransferable::_PasteOLE( rData, rSh, nFormat,
//STRIP001                                                  nActionFlags, bMsg );
//STRIP001              break;
//STRIP001
//STRIP001          case SOT_FORMATSTR_ID_SVIM:
//STRIP001              nRet = SwTransferable::_PasteImageMap( rData, rSh );
//STRIP001              break;
//STRIP001
//STRIP001          case SOT_FORMATSTR_ID_SVXB:
//STRIP001          case SOT_FORMAT_BITMAP:
//STRIP001          case SOT_FORMAT_GDIMETAFILE:
//STRIP001              nRet = SwTransferable::_PasteGrf( rData, rSh, nFormat,
//STRIP001                                              SW_PASTESDR_INSERT,pPt,
//STRIP001                                              nActionFlags, bMsg );
//STRIP001              break;
//STRIP001
//STRIP001          case SOT_FORMATSTR_ID_SBA_FIELDDATAEXCHANGE:
//STRIP001          case SOT_FORMATSTR_ID_SBA_DATAEXCHANGE:
//STRIP001          case SOT_FORMATSTR_ID_SBA_CTRLDATAEXCHANGE:
//STRIP001              nRet = SwTransferable::_PasteDBData( rData, rSh, nFormat,
//STRIP001                                          EXCHG_IN_ACTION_LINK == nClearedAction,
//STRIP001                                          pPt, bMsg );
//STRIP001              break;
//STRIP001
//STRIP001          case SOT_FORMAT_FILE:
//STRIP001              nRet = SwTransferable::_PasteFileName( rData, rSh, nFormat,
//STRIP001                              ( EXCHG_IN_ACTION_MOVE == nClearedAction
//STRIP001                                  ? SW_PASTESDR_REPLACE
//STRIP001                                  : EXCHG_IN_ACTION_LINK == nClearedAction
//STRIP001                                      ? SW_PASTESDR_SETATTR
//STRIP001                                      : SW_PASTESDR_INSERT),
//STRIP001                              pPt, nActionFlags, bMsg );
//STRIP001              break;
//STRIP001
//STRIP001          case SOT_FORMAT_FILE_LIST:
//STRIP001              // dann nur als Grafiken einfuegen
//STRIP001              nRet = SwTransferable::_PasteFileList( rData, rSh,
//STRIP001                                  EXCHG_IN_ACTION_LINK == nClearedAction,
//STRIP001                                  pPt, bMsg );
//STRIP001              break;
//STRIP001
//STRIP001          case SOT_FORMATSTR_ID_SONLK:
//STRIP001              if( pPt )
//STRIP001              {
//STRIP001                  NaviContentBookmark aBkmk;
//STRIP001                  if( aBkmk.Paste( rData ) )
//STRIP001                  {
//STRIP001                         if(bIsDefault)
//STRIP001                         {
//STRIP001                             switch(aBkmk.GetDefaultDragType())
//STRIP001                             {
//STRIP001                                 case REGION_MODE_NONE: nClearedAction = EXCHG_IN_ACTION_COPY; break;
//STRIP001                                 case REGION_MODE_EMBEDDED: nClearedAction = EXCHG_IN_ACTION_MOVE; break;
//STRIP001                                 case REGION_MODE_LINK: nClearedAction = EXCHG_IN_ACTION_LINK; break;
//STRIP001                             }
//STRIP001                         }
//STRIP001                         rSh.NavigatorPaste( aBkmk, nClearedAction );
//STRIP001                      nRet = 1;
//STRIP001                  }
//STRIP001              }
//STRIP001              break;
//STRIP001
//STRIP001          case SOT_FORMATSTR_ID_INET_IMAGE:
//STRIP001          case SOT_FORMATSTR_ID_NETSCAPE_IMAGE:
//STRIP001              nRet = SwTransferable::_PasteTargetURL( rData, rSh,
//STRIP001                                                      SW_PASTESDR_INSERT,
//STRIP001                                                      pPt, TRUE );
//STRIP001              break;
//STRIP001
//STRIP001          default:
//STRIP001              ASSERT( pPt, "unbekanntes Format" );
//STRIP001          }
//STRIP001          break;
//STRIP001
//STRIP001      case EXCHG_OUT_ACTION_INSERT_FILE:
//STRIP001          nRet = SwTransferable::_PasteFileName( rData, rSh, nFormat,
//STRIP001                                      SW_PASTESDR_INSERT, pPt,
//STRIP001                                      nActionFlags, bMsg );
//STRIP001          break;
//STRIP001
//STRIP001      case EXCHG_OUT_ACTION_INSERT_OLE:
//STRIP001          nRet = SwTransferable::_PasteOLE( rData, rSh, nFormat,
//STRIP001                                              nActionFlags,bMsg );
//STRIP001          break;
//STRIP001
//STRIP001      case EXCHG_OUT_ACTION_INSERT_DDE:
//STRIP001 #ifdef DDE_AVAILABLE
//STRIP001          {
//STRIP001              FASTBOOL bReRead = 0 != CNT_HasGrf( rSh.GetCntType() );
//STRIP001              nRet = SwTransferable::_PasteDDE( rData, rSh, bReRead, bMsg );
//STRIP001          }
//STRIP001 #endif
//STRIP001          break;
//STRIP001
//STRIP001      case EXCHG_OUT_ACTION_INSERT_HYPERLINK:
//STRIP001          {
//STRIP001              String sURL, sDesc;
//STRIP001              if( SOT_FORMAT_FILE == nFormat )
//STRIP001              {
//STRIP001                  if( rData.GetString( nFormat, sURL ) && sURL.Len() )
//STRIP001                  {
//STRIP001                      SwTransferable::_CheckForURLOrLNKFile( rData, sURL, &sDesc );
//STRIP001                      if( !sDesc.Len() )
//STRIP001                          sDesc = sURL;
//STRIP001                      nRet = 1;
//STRIP001                  }
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  INetBookmark aBkmk;
//STRIP001                  if( rData.GetINetBookmark( nFormat, aBkmk ) )
//STRIP001                  {
//STRIP001                      sURL = aBkmk.GetURL();
//STRIP001                      sDesc = aBkmk.GetDescription();
//STRIP001                      nRet = 1;
//STRIP001                  }
//STRIP001              }
//STRIP001
//STRIP001              if( nRet )
//STRIP001              {
//STRIP001                  SwFmtINetFmt aFmt( sURL, aEmptyStr );
//STRIP001                  rSh.InsertURL( aFmt, sDesc );
//STRIP001              }
//STRIP001          }
//STRIP001          break;
//STRIP001
//STRIP001      case EXCHG_OUT_ACTION_GET_ATTRIBUTES:
//STRIP001          switch( nFormat )
//STRIP001          {
//STRIP001          case SOT_FORMATSTR_ID_DRAWING:
//STRIP001              nRet = SwTransferable::_PasteSdrFormat( rData, rSh,
//STRIP001                                              SW_PASTESDR_SETATTR, pPt,
//STRIP001                                              nActionFlags );
//STRIP001              break;
//STRIP001          case SOT_FORMATSTR_ID_SVXB:
//STRIP001          case SOT_FORMAT_GDIMETAFILE:
//STRIP001          case SOT_FORMAT_BITMAP:
//STRIP001          case SOT_FORMATSTR_ID_NETSCAPE_BOOKMARK:
//STRIP001          case SOT_FORMAT_FILE:
//STRIP001          case SOT_FORMATSTR_ID_FILEGRPDESCRIPTOR:
//STRIP001          case SOT_FORMATSTR_ID_UNIFORMRESOURCELOCATOR:
//STRIP001              nRet = SwTransferable::_PasteGrf( rData, rSh, nFormat,
//STRIP001                                              SW_PASTESDR_SETATTR, pPt,
//STRIP001                                              nActionFlags, bMsg );
//STRIP001              break;
//STRIP001          default:
//STRIP001              ASSERT( FALSE, "unbekanntes Format" );
//STRIP001          }
//STRIP001
//STRIP001          break;
//STRIP001
//STRIP001      case EXCHG_OUT_ACTION_INSERT_DRAWOBJ:
//STRIP001          nRet = SwTransferable::_PasteSdrFormat( rData, rSh,
//STRIP001                                              SW_PASTESDR_INSERT, pPt,
//STRIP001                                              nActionFlags );
//STRIP001          break;
//STRIP001      case EXCHG_OUT_ACTION_INSERT_SVXB:
//STRIP001      case EXCHG_OUT_ACTION_INSERT_GDIMETAFILE:
//STRIP001      case EXCHG_OUT_ACTION_INSERT_BITMAP:
//STRIP001      case EXCHG_OUT_ACTION_INSERT_GRAPH:
//STRIP001          nRet = SwTransferable::_PasteGrf( rData, rSh, nFormat,
//STRIP001                                              SW_PASTESDR_INSERT, pPt,
//STRIP001                                              nActionFlags, bMsg );
//STRIP001          break;
//STRIP001
//STRIP001      case EXCHG_OUT_ACTION_REPLACE_DRAWOBJ:
//STRIP001          nRet = SwTransferable::_PasteSdrFormat( rData, rSh,
//STRIP001                                              SW_PASTESDR_REPLACE, pPt,
//STRIP001                                              nActionFlags );
//STRIP001          break;
//STRIP001
//STRIP001      case EXCHG_OUT_ACTION_REPLACE_SVXB:
//STRIP001      case EXCHG_OUT_ACTION_REPLACE_GDIMETAFILE:
//STRIP001      case EXCHG_OUT_ACTION_REPLACE_BITMAP:
//STRIP001      case EXCHG_OUT_ACTION_REPLACE_GRAPH:
//STRIP001          nRet = SwTransferable::_PasteGrf( rData, rSh, nFormat,
//STRIP001                                              SW_PASTESDR_REPLACE,pPt,
//STRIP001                                              nActionFlags, bMsg );
//STRIP001          break;
//STRIP001
//STRIP001      case EXCHG_OUT_ACTION_INSERT_INTERACTIVE:
//STRIP001          nRet = SwTransferable::_PasteAsHyperlink( rData, rSh, nFormat );
//STRIP001          break;
//STRIP001
//STRIP001      default:
//STRIP001          ASSERT( FALSE, "unbekannte Action" );
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if( !bPasteSelection && rSh.IsFrmSelected() )
//STRIP001  {
//STRIP001      rSh.EnterSelFrmMode();
//STRIP001      //force ::SelectShell
//STRIP001      rSh.GetView().StopShellTimer();
//STRIP001  }
//STRIP001
//STRIP001  if( pAction )
//STRIP001      delete pAction;
//STRIP001
//STRIP001  return nRet;
//STRIP001 }

// -----------------------------------------------------------------------

/*N*/  USHORT SwTransferable::GetSotDestination( const SwWrtShell& rSh,
/*N*/                                           const Point* pPt )
/*N*/  {
/*N*/   USHORT nRet = EXCHG_INOUT_ACTION_NONE;
/*N*/
/*N*/   ObjCntType eOType;
/*N*/   if( pPt )
/*N*/   {
/*?*/       DBG_BF_ASSERT(0, "STRIP"); //STRIP001 SdrObject *pObj = 0;
//STRIP001 /*?*/        eOType = rSh.GetObjCntType( *pPt, pObj );
/*N*/   }
/*N*/   else
/*N*/       eOType = rSh.GetObjCntTypeOfSelection();
/*N*/
/*N*/   switch( eOType )
/*N*/   {
/*N*/   case OBJCNT_GRF:
/*N*/       {
/*?*/           DBG_BF_ASSERT(0, "STRIP"); //STRIP001 BOOL bIMap, bLink;
//STRIP001 /*?*/            if( pPt )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                bIMap = 0 != rSh.GetFmtFromObj( *pPt )->GetURL().GetMap();
//STRIP001 /*?*/                String aDummy;
//STRIP001 /*?*/                rSh.GetGrfAtPos( *pPt, aDummy, bLink );
//STRIP001 /*?*/            }
//STRIP001 /*?*/            else
//STRIP001 /*?*/            {
//STRIP001 /*?*/                bIMap = 0 != rSh.GetFlyFrmFmt()->GetURL().GetMap();
//STRIP001 /*?*/                String aDummy;
//STRIP001 /*?*/                rSh.GetGrfNms( &aDummy, 0 );
//STRIP001 /*?*/                bLink = 0 != aDummy.Len();
//STRIP001 /*?*/            }
//STRIP001 /*?*/
//STRIP001 /*?*/            if( bLink && bIMap )
//STRIP001 /*?*/                nRet = EXCHG_DEST_DOC_LNKD_GRAPH_W_IMAP;
//STRIP001 /*?*/            else if( bLink )
//STRIP001 /*?*/                nRet = EXCHG_DEST_DOC_LNKD_GRAPHOBJ;
//STRIP001 /*?*/            else if( bIMap )
//STRIP001 /*?*/                nRet = EXCHG_DEST_DOC_GRAPH_W_IMAP;
//STRIP001 /*?*/            else
//STRIP001 /*?*/                nRet = EXCHG_DEST_DOC_GRAPHOBJ;
/*N*/       }
/*N*/       break;
/*N*/
/*N*/   case OBJCNT_FLY:
/*N*/       if( rSh.GetView().GetDocShell()->ISA(SwWebDocShell) )
/*N*/           nRet = EXCHG_DEST_DOC_TEXTFRAME_WEB;
/*N*/       else
/*N*/           nRet = EXCHG_DEST_DOC_TEXTFRAME;
/*N*/       break;
/*N*/   case OBJCNT_OLE:        nRet = EXCHG_DEST_DOC_OLEOBJ;       break;
/*N*/
/*N*/   case OBJCNT_CONTROL:    /* no Action avail */
/*N*/   case OBJCNT_SIMPLE:     nRet = EXCHG_DEST_DOC_DRAWOBJ;      break;
/*N*/   case OBJCNT_URLBUTTON:  nRet = EXCHG_DEST_DOC_URLBUTTON;    break;
/*N*/   case OBJCNT_GROUPOBJ:   nRet = EXCHG_DEST_DOC_GROUPOBJ;     break;
/*N*/
/*N*/  // was mmchen wir bei Mehrfachselektion???
/*N*/  //   case OBJCNT_DONTCARE:
/*N*/   default:
/*N*/       {
/*
 JP 13.07.98: Bug 52637: es wird ein URL-Feld erkannt also werden nur die
                         Inhalte zugelassen. Das ist aber bestimmt nicht das
                         gewollte.
             SwContentAtPos aCntntAtPos( SwContentAtPos::SW_INETATTR );
             SfxItemSet aSet( (SfxItemPool&)rSh.GetAttrPool(),
                             RES_TXTATR_INETFMT, RES_TXTATR_INETFMT );
             if( pPt ? ((SwWrtShell&)rSh).GetContentAtPos( *pPt, aCntntAtPos, FALSE )
                      : (rSh.GetAttr( aSet ) && aSet.Count()) )
                 nRet = EXCHG_DEST_DOC_URLFIELD;
             else
*/
/*N*/           if( rSh.GetView().GetDocShell()->ISA(SwWebDocShell) )
/*N*/               nRet = EXCHG_DEST_SWDOC_FREE_AREA_WEB;
/*N*/           else
/*N*/               nRet = EXCHG_DEST_SWDOC_FREE_AREA;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   return nRet;
/*N*/  }

// -----------------------------------------------------------------------

//STRIP001 int SwTransferable::_PasteFileContent( TransferableDataHelper& rData,
//STRIP001                                  SwWrtShell& rSh, ULONG nFmt, BOOL bMsg )
//STRIP001 {
//STRIP001  USHORT nResId = MSG_CLPBRD_FORMAT_ERROR;
//STRIP001  int nRet = 0;
//STRIP001
//STRIP001  MSE40HTMLClipFormatObj aMSE40ClpObj;
//STRIP001  String sTmpBaseURL( so3::StaticBaseUrl::GetBaseURL() );
//STRIP001
//STRIP001  SotStorageStreamRef xStrm;
//STRIP001  SvStream* pStream = 0;
//STRIP001  SwRead pRead = 0;
//STRIP001  ::rtl::OUString sData;
//STRIP001  switch( nFmt )
//STRIP001  {
//STRIP001  case SOT_FORMAT_STRING:
//STRIP001      {
//STRIP001          pRead = ReadAscii;
//STRIP001          if( rData.GetString( nFmt, sData ) )
//STRIP001          {
//STRIP001              pStream = new SvMemoryStream( (void*)sData.getStr(),
//STRIP001                          sData.getLength() * sizeof( sal_Unicode ),
//STRIP001                          STREAM_READ );
//STRIP001 #ifdef OSL_BIGENDIAN
//STRIP001              pStream->SetNumberFormatInt( NUMBERFORMAT_INT_BIGENDIAN );
//STRIP001 #else
//STRIP001              pStream->SetNumberFormatInt( NUMBERFORMAT_INT_LITTLEENDIAN );
//STRIP001 #endif
//STRIP001
//STRIP001              SwAsciiOptions aAOpt;
//STRIP001              aAOpt.SetCharSet( RTL_TEXTENCODING_UCS2 );
//STRIP001              pRead->GetReaderOpt().SetASCIIOpts( aAOpt );
//STRIP001              break;
//STRIP001          }
//STRIP001      }
//STRIP001      // no break - because then test if we get a stream
//STRIP001
//STRIP001  default:
//STRIP001      if( rData.GetSotStorageStream( nFmt, xStrm ) )
//STRIP001      {
//STRIP001          if( ( SOT_FORMATSTR_ID_HTML_SIMPLE == nFmt ) ||
//STRIP001                 ( SOT_FORMATSTR_ID_HTML_NO_COMMENT == nFmt ) )
//STRIP001          {
//STRIP001              pStream = aMSE40ClpObj.IsValid( *xStrm );
//STRIP001              pRead = ReadHTML;
//STRIP001              pRead->SetReadUTF8( TRUE );
//STRIP001              so3::StaticBaseUrl::SetBaseURL( aMSE40ClpObj.GetBaseURL() );
//STRIP001
//STRIP001                 BOOL bNoComments =
//STRIP001                     ( nFmt == SOT_FORMATSTR_ID_HTML_NO_COMMENT );
//STRIP001                 pRead->SetIgnoreHTMLComments( bNoComments );
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              pStream = &xStrm;
//STRIP001              if( SOT_FORMAT_RTF == nFmt )
//STRIP001                  pRead = ReadRtf;
//STRIP001              else if( !pRead )
//STRIP001                  pRead = ReadHTML;
//STRIP001          }
//STRIP001      }
//STRIP001      break;
//STRIP001  }
//STRIP001
//STRIP001  if( pStream && pRead )
//STRIP001  {
//STRIP001      Link aOldLink( rSh.GetChgLnk() );
//STRIP001      rSh.SetChgLnk( Link() );
//STRIP001
//STRIP001      SwReader aReader( *pStream, aEmptyStr, *rSh.GetCrsr() );
//STRIP001      if( IsError( aReader.Read( *pRead )) )
//STRIP001          nResId = ERR_CLPBRD_READ;
//STRIP001      else
//STRIP001          nResId = 0, nRet = 1;
//STRIP001
//STRIP001      so3::StaticBaseUrl::SetBaseURL( sTmpBaseURL );
//STRIP001
//STRIP001      rSh.SetChgLnk( aOldLink );
//STRIP001      if( nRet )
//STRIP001          rSh.CallChgLnk();
//STRIP001  }
//STRIP001  else
//STRIP001      nResId = MSG_CLPBRD_FORMAT_ERROR;
//STRIP001
//STRIP001  // Exist a SvMemoryStream? (data in the OUString and xStrm is empty)
//STRIP001  if( pStream && !xStrm.Is() )
//STRIP001      delete pStream;
//STRIP001
//STRIP001  if( bMsg && nResId )
//STRIP001  {
//STRIP001      InfoBox( 0, SW_RES( nResId )).Execute();
//STRIP001  }
//STRIP001  return nRet;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 int SwTransferable::_PasteOLE( TransferableDataHelper& rData, SwWrtShell& rSh,
//STRIP001                              ULONG nFmt, BYTE nActionFlags, BOOL bMsg )
//STRIP001 {
//STRIP001  int nRet = 0;
//STRIP001  TransferableObjectDescriptor aObjDesc;
//STRIP001  SotStorageStreamRef xStrm;
//STRIP001  SvStorageRef xStore;
//STRIP001  Reader* pRead = 0;
//STRIP001  SotFormatStringId nId;
//STRIP001  if( rData.HasFormat( SOT_FORMATSTR_ID_EMBEDDED_OBJ ) )
//STRIP001      nId = SOT_FORMATSTR_ID_EMBEDDED_OBJ;
//STRIP001  else if( rData.HasFormat( SOT_FORMATSTR_ID_EMBED_SOURCE ) &&
//STRIP001           rData.HasFormat( SOT_FORMATSTR_ID_OBJECTDESCRIPTOR ))
//STRIP001      nId = SOT_FORMATSTR_ID_EMBED_SOURCE;
//STRIP001  else
//STRIP001      nId = 0;
//STRIP001
//STRIP001  if( nId && rData.GetSotStorageStream( nId, xStrm ) && xStrm.Is() )
//STRIP001  {
//STRIP001      USHORT nFileVersion;
//STRIP001      xStore = new SvStorage( *xStrm );
//STRIP001      switch( xStore->GetFormat() )
//STRIP001      {
//STRIP001      case SOT_FORMATSTR_ID_STARWRITER_50:
//STRIP001      case SOT_FORMATSTR_ID_STARWRITERWEB_50:
//STRIP001      case SOT_FORMATSTR_ID_STARWRITERGLOB_50:
//STRIP001          nFileVersion = SOFFICE_FILEFORMAT_50;
//STRIP001          goto PASTEOLE_SETREADSW3;
//STRIP001
//STRIP001      case SOT_FORMATSTR_ID_STARWRITER_40:
//STRIP001      case SOT_FORMATSTR_ID_STARWRITERWEB_40:
//STRIP001      case SOT_FORMATSTR_ID_STARWRITERGLOB_40:
//STRIP001          nFileVersion = SOFFICE_FILEFORMAT_40;
//STRIP001          goto PASTEOLE_SETREADSW3;
//STRIP001
//STRIP001      case SOT_FORMATSTR_ID_STARWRITER_30:
//STRIP001          nFileVersion = SOFFICE_FILEFORMAT_31;
//STRIP001          goto PASTEOLE_SETREADSW3;
//STRIP001
//STRIP001 PASTEOLE_SETREADSW3:
//STRIP001          pRead = ReadSw3;
//STRIP001          xStore->SetVersion( nFileVersion );
//STRIP001          break;
//STRIP001
//STRIP001      case SOT_FORMATSTR_ID_STARWRITER_60:
//STRIP001      case SOT_FORMATSTR_ID_STARWRITERWEB_60:
//STRIP001      case SOT_FORMATSTR_ID_STARWRITERGLOB_60:
//STRIP001          pRead = ReadXML;
//STRIP001          break;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if( pRead )
//STRIP001  {
//STRIP001      SwReader aReader( *xStore, aEmptyStr, *rSh.GetCrsr() );
//STRIP001      if( !IsError( aReader.Read( *pRead )) )
//STRIP001          nRet = 1;
//STRIP001      else if( bMsg )
//STRIP001          InfoBox( 0, SW_RES(ERR_CLPBRD_READ) ).Execute();
//STRIP001  }
//STRIP001  else if( (  rData.HasFormat( SOT_FORMATSTR_ID_OBJECTDESCRIPTOR ) &&
//STRIP001              rData.GetTransferableObjectDescriptor(
//STRIP001                      SOT_FORMATSTR_ID_OBJECTDESCRIPTOR, aObjDesc ) &&
//STRIP001            ( nFmt == nId ? xStore.Is()
//STRIP001                          : ( xStore.Clear(),
//STRIP001                              rData.GetSotStorageStream( nFmt, xStrm )) ))
//STRIP001          || ( rData.HasFormat(
//STRIP001                  ( nFmt = SOT_FORMATSTR_ID_OBJECTDESCRIPTOR_OLE )) &&
//STRIP001               rData.GetTransferableObjectDescriptor( nFmt, aObjDesc ))
//STRIP001          )
//STRIP001  {
//STRIP001      SvInPlaceObjectRef xIPObj;
//STRIP001      if( SOT_FORMATSTR_ID_OBJECTDESCRIPTOR_OLE == nFmt )
//STRIP001      {
//STRIP001          xStore = new SvStorage( aEmptyStr, STREAM_STD_READWRITE );
//STRIP001          xIPObj = &((SvFactory*)SvInPlaceObject::ClassFactory())
//STRIP001                      ->CreateAndInit(  rData.GetXTransferable(), xStore);
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          if( !xStore.Is() )
//STRIP001              xStore = new SvStorage( *xStrm );
//STRIP001          xIPObj = &( (SvFactory*)SvInPlaceObject::
//STRIP001                              ClassFactory() )->CreateAndLoad( xStore );
//STRIP001      }
//STRIP001
//STRIP001      if( xIPObj.Is() )
//STRIP001      {
//STRIP001          //Size einstellen. Ist ein Hack wg. Auslieferung, die Size sollte
//STRIP001          //an das InsertOle uebergeben werden!!!!!!!!!!
//STRIP001          const Size aSize( aObjDesc.maSize );    //immer 100TH_MM
//STRIP001          if( aSize.Width() && aSize.Height() )
//STRIP001          {
//STRIP001              xIPObj->SetVisAreaSize( OutputDevice::LogicToLogic( aSize,
//STRIP001                                  MAP_100TH_MM, xIPObj->GetMapUnit() ) );
//STRIP001          }
//STRIP001          //Ende mit Hack!
//STRIP001
//STRIP001          rSh.InsertOle( xIPObj );
//STRIP001          nRet = 1;
//STRIP001
//STRIP001          if( nRet && ( nActionFlags &
//STRIP001              ( EXCHG_OUT_ACTION_FLAG_INSERT_TARGETURL >> 8) ))
//STRIP001              SwTransferable::_PasteTargetURL( rData, rSh, 0, 0, FALSE );
//STRIP001
//STRIP001      }
//STRIP001  }
//STRIP001  return nRet;
//STRIP001 }

// -----------------------------------------------------------------------


// -----------------------------------------------------------------------

//STRIP001 int SwTransferable::_PasteTargetURL( TransferableDataHelper& rData,
//STRIP001                                  SwWrtShell& rSh, USHORT nAction,
//STRIP001                                  const Point* pPt, BOOL bInsertGRF )
//STRIP001 {
//STRIP001  int nRet = 0;
//STRIP001  INetImage aINetImg;
//STRIP001  if( ( rData.HasFormat( SOT_FORMATSTR_ID_INET_IMAGE ) &&
//STRIP001        rData.GetINetImage( SOT_FORMATSTR_ID_INET_IMAGE, aINetImg )) ||
//STRIP001      ( rData.HasFormat( SOT_FORMATSTR_ID_NETSCAPE_IMAGE ) &&
//STRIP001        rData.GetINetImage( SOT_FORMATSTR_ID_NETSCAPE_IMAGE, aINetImg )) )
//STRIP001  {
//STRIP001      if( aINetImg.GetImageURL().Len() && bInsertGRF )
//STRIP001      {
//STRIP001          String sURL( aINetImg.GetImageURL() );
//STRIP001          SwTransferable::_CheckForURLOrLNKFile( rData, sURL );
//STRIP001
//STRIP001          //!!! auf FileSystem abpruefen - nur dann ist es sinnvoll die
//STRIP001          // Grafiken zu testen !!!!
//STRIP001          Graphic aGrf;
//STRIP001          GraphicFilter *pFlt = ::GetGrfFilter();
//STRIP001          nRet = GRFILTER_OK == ::LoadGraphic( sURL, aEmptyStr, aGrf, pFlt );
//STRIP001          if( nRet )
//STRIP001          {
//STRIP001              switch( nAction )
//STRIP001              {
//STRIP001              case SW_PASTESDR_INSERT:
//STRIP001                  SwTransferable::SetSelInShell( rSh, FALSE, pPt );
//STRIP001                  rSh.Insert( sURL, aEmptyStr, aGrf );
//STRIP001                  break;
//STRIP001
//STRIP001              case SW_PASTESDR_REPLACE:
//STRIP001                  if( rSh.IsObjSelected() )
//STRIP001                  {
//STRIP001                      rSh.ReplaceSdrObj( sURL, aEmptyStr, &aGrf );
//STRIP001                      Point aPt( pPt ? *pPt : rSh.GetCrsrDocPos() );
//STRIP001                      SwTransferable::SetSelInShell( rSh, TRUE, &aPt );
//STRIP001                  }
//STRIP001                  else
//STRIP001                      rSh.ReRead( sURL, aEmptyStr, &aGrf );
//STRIP001                  break;
//STRIP001
//STRIP001              case SW_PASTESDR_SETATTR:
//STRIP001                  if( rSh.IsObjSelected() )
//STRIP001                      rSh.Paste( aGrf );
//STRIP001                  else if( OBJCNT_GRF == rSh.GetObjCntTypeOfSelection() )
//STRIP001                      rSh.ReRead( sURL, aEmptyStr, &aGrf );
//STRIP001                  else
//STRIP001                  {
//STRIP001                      SwTransferable::SetSelInShell( rSh, FALSE, pPt );
//STRIP001                      rSh.Insert( sURL, aEmptyStr, aGrf );
//STRIP001                  }
//STRIP001                  break;
//STRIP001              default:
//STRIP001                  nRet = 0;
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001      else
//STRIP001          nRet = 1;
//STRIP001  }
//STRIP001
//STRIP001  if( nRet )
//STRIP001  {
//STRIP001      SfxItemSet aSet( rSh.GetAttrPool(), RES_URL, RES_URL );
//STRIP001      rSh.GetFlyFrmAttr( aSet );
//STRIP001      SwFmtURL aURL( (SwFmtURL&)aSet.Get( RES_URL ) );
//STRIP001
//STRIP001      if( aURL.GetURL() != aINetImg.GetTargetURL() ||
//STRIP001          aURL.GetTargetFrameName() != aINetImg.GetTargetFrame() )
//STRIP001      {
//STRIP001          aURL.SetURL( aINetImg.GetTargetURL(), FALSE );
//STRIP001          aURL.SetTargetFrameName( aINetImg.GetTargetFrame() );
//STRIP001          aSet.Put( aURL );
//STRIP001          rSh.SetFlyFrmAttr( aSet );
//STRIP001      }
//STRIP001  }
//STRIP001  return nRet;
//STRIP001 }


// -----------------------------------------------------------------------

//STRIP001 void SwTransferable::SetSelInShell( SwWrtShell& rSh, BOOL bSelectFrm,
//STRIP001                                      const Point* pPt )
//STRIP001 {
//STRIP001  if( bSelectFrm )
//STRIP001  {
//STRIP001      // Rahmen/Objecte selektieren
//STRIP001      if( pPt && !SFX_APP()->IsDispatcherLocked() )
//STRIP001      {
//STRIP001          rSh.GetView().NoRotate();
//STRIP001          if( rSh.SelectObj( *pPt ))
//STRIP001          {
//STRIP001              rSh.HideCrsr();
//STRIP001              rSh.EnterSelFrmMode( pPt );
//STRIP001              bFrmDrag = TRUE;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      if( rSh.IsFrmSelected() || rSh.IsObjSelected() )
//STRIP001      {
//STRIP001          rSh.UnSelectFrm();
//STRIP001          rSh.LeaveSelFrmMode();
//STRIP001          rSh.GetView().GetEditWin().StopInsFrm();
//STRIP001          bFrmDrag = FALSE;
//STRIP001      }
//STRIP001      else if( rSh.GetView().GetDrawFuncPtr() )
//STRIP001          rSh.GetView().GetEditWin().StopInsFrm();
//STRIP001
//STRIP001      rSh.EnterStdMode();
//STRIP001      if( pPt )
//STRIP001          rSh.SwCrsrShell::SetCrsr( *pPt, TRUE );
//STRIP001  }
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 int SwTransferable::_PasteDDE( TransferableDataHelper& rData,
//STRIP001                              SwWrtShell& rWrtShell, FASTBOOL bReReadGrf,
//STRIP001                              BOOL bMsg )
//STRIP001 {
//STRIP001 #ifdef DDE_AVAILABLE
//STRIP001  // Daten aus dem Clipboardformat
//STRIP001  String aApp, aTopic, aItem;
//STRIP001
//STRIP001  {
//STRIP001      SotStorageStreamRef xStrm;
//STRIP001      if( !rData.GetSotStorageStream( SOT_FORMATSTR_ID_LINK, xStrm ))
//STRIP001      {
//STRIP001          ASSERT( !&rWrtShell, "DDE Data not found." );
//STRIP001          return 0;
//STRIP001      }   //sinnvollen Fehler melden!!
//STRIP001
//STRIP001      xStrm->ReadCString( aApp, DDE_TXT_ENCODING );
//STRIP001      xStrm->ReadCString( aTopic, DDE_TXT_ENCODING );
//STRIP001      xStrm->ReadCString( aItem, DDE_TXT_ENCODING );
//STRIP001  }
//STRIP001
//STRIP001  String aCmd;
//STRIP001  ::so3::MakeLnkName( aCmd, &aApp, aTopic, aItem );
//STRIP001
//STRIP001  // wollen wir jetzt eine Grafik einlesen ?
//STRIP001  ULONG nFormat;
//STRIP001  if( !rData.HasFormat( FORMAT_RTF ) &&
//STRIP001      !rData.HasFormat( SOT_FORMATSTR_ID_HTML ) &&
//STRIP001      !rData.HasFormat( FORMAT_STRING ) &&
//STRIP001      (rData.HasFormat( nFormat = FORMAT_GDIMETAFILE ) ||
//STRIP001       rData.HasFormat( nFormat = FORMAT_BITMAP )) )
//STRIP001  {
//STRIP001      Graphic aGrf;
//STRIP001      int nRet = rData.GetGraphic( nFormat, aGrf );
//STRIP001      if( nRet )
//STRIP001      {
//STRIP001          String sLnkTyp( String::CreateFromAscii(
//STRIP001                      RTL_CONSTASCII_STRINGPARAM( "DDE" )));
//STRIP001          if ( bReReadGrf )
//STRIP001              rWrtShell.ReRead( aCmd, sLnkTyp, &aGrf );
//STRIP001          else
//STRIP001              rWrtShell.Insert( aCmd, sLnkTyp, aGrf );
//STRIP001      }
//STRIP001      return nRet;
//STRIP001  }
//STRIP001
//STRIP001  SwFieldType* pTyp;
//STRIP001  USHORT i = 1,j;
//STRIP001  String aName;
//STRIP001  BOOL bAlreadyThere = FALSE, bDoublePaste = FALSE;
//STRIP001  USHORT nSize = rWrtShell.GetFldTypeCount();
//STRIP001  const ::utl::TransliterationWrapper& rColl = ::GetAppCmpStrIgnore();
//STRIP001
//STRIP001  do {
//STRIP001      aName = aApp;
//STRIP001      aName += String::CreateFromInt32( i );
//STRIP001      for( j = INIT_FLDTYPES; j < nSize; j++ )
//STRIP001      {
//STRIP001          pTyp = rWrtShell.GetFldType( j );
//STRIP001          if( RES_DDEFLD == pTyp->Which() )
//STRIP001          {
//STRIP001              String sTmp( ((SwDDEFieldType*)pTyp)->GetCmd() );
//STRIP001              if( rColl.isEqual( sTmp, aCmd ) &&
//STRIP001                  ::so3::LINKUPDATE_ALWAYS == ((SwDDEFieldType*)pTyp)->GetType() )
//STRIP001              {
//STRIP001                  aName = pTyp->GetName();
//STRIP001                  bDoublePaste = TRUE;
//STRIP001                  break;
//STRIP001              }
//STRIP001              else if( rColl.isEqual( aName, pTyp->GetName() ) )
//STRIP001                  break;
//STRIP001          }
//STRIP001      }
//STRIP001      if( j == nSize )
//STRIP001          bAlreadyThere = FALSE;
//STRIP001      else
//STRIP001      {
//STRIP001          bAlreadyThere = TRUE;
//STRIP001          i++;
//STRIP001      }
//STRIP001  }
//STRIP001  while( bAlreadyThere && !bDoublePaste );
//STRIP001
//STRIP001  if( !bDoublePaste )
//STRIP001  {
//STRIP001      SwDDEFieldType aType( aName, aCmd, ::so3::LINKUPDATE_ALWAYS );
//STRIP001      pTyp = rWrtShell.InsertFldType( aType );
//STRIP001  }
//STRIP001
//STRIP001
//STRIP001  SwDDEFieldType* pDDETyp = (SwDDEFieldType*)pTyp;
//STRIP001
//STRIP001  String aExpand;
//STRIP001  if( rData.GetString( FORMAT_STRING, aExpand ))
//STRIP001  {
//STRIP001      do {            // middle checked loop
//STRIP001
//STRIP001          // Wenn die Daten von einer Tabellenkalkulation kommen
//STRIP001          // fuegen wir eine DDE-Tabelle ein
//STRIP001          if( ( rData.HasFormat( SOT_FORMATSTR_ID_SYLK ) ||
//STRIP001                rData.HasFormat( SOT_FORMATSTR_ID_SYLK_BIGCAPS ) ) &&
//STRIP001              aExpand.Len() &&
//STRIP001               ( 1 < aExpand.GetTokenCount( '\n' ) ||
//STRIP001                     aExpand.GetTokenCount( '\t' )) )
//STRIP001          {
//STRIP001              // wo stehen wir ueberhaupt ??
//STRIP001              // Wir duerfen keine Tabelle in eine Tabelle einfuegen !!
//STRIP001              if( rWrtShell.IsCrsrInTbl() )
//STRIP001              {
//STRIP001                  if(bMsg)
//STRIP001                      InfoBox(0, String(SW_RES(STR_NO_TABLE))).Execute();
//STRIP001                  pDDETyp = 0;
//STRIP001                  break;
//STRIP001              }
//STRIP001
//STRIP001              String sTmp( aExpand );
//STRIP001              xub_StrLen nRows = sTmp.GetTokenCount( '\n' );
//STRIP001              if( nRows )
//STRIP001                  --nRows;
//STRIP001              sTmp = sTmp.GetToken( 0, '\n' );
//STRIP001              xub_StrLen nCols = sTmp.GetTokenCount( '\t' );
//STRIP001
//STRIP001              // mindestens eine Spalte & Zeile muss vorhanden sein
//STRIP001              if( !nRows || !nCols )
//STRIP001              {
//STRIP001                  if( bMsg )
//STRIP001                      InfoBox(0, SW_RESSTR(STR_NO_TABLE)).Execute();
//STRIP001                  pDDETyp = 0;
//STRIP001                  break;
//STRIP001              }
//STRIP001
//STRIP001              rWrtShell.InsertDDETable( pDDETyp, nRows, nCols );
//STRIP001          }
//STRIP001          else if( 1 < aExpand.GetTokenCount( '\n' ) )
//STRIP001          {
//STRIP001              // mehrere Absaetze -> eine geschuetzte Section einfuegen
//STRIP001              if( rWrtShell.HasSelection() )
//STRIP001                  rWrtShell.DelRight();
//STRIP001
//STRIP001              SwSection aSect( DDE_LINK_SECTION, aName );
//STRIP001              aSect.SetLinkFileName( aCmd );
//STRIP001              aSect.SetProtect();
//STRIP001              rWrtShell.InsertSection( aSect );
//STRIP001
//STRIP001              pDDETyp = 0;                // FeldTypen wieder entfernen
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              // Einfuegen
//STRIP001              SwDDEField aSwDDEField( pDDETyp );
//STRIP001              rWrtShell.Insert( aSwDDEField );
//STRIP001          }
//STRIP001
//STRIP001      } while( FALSE );
//STRIP001  }
//STRIP001  else
//STRIP001      pDDETyp = 0;                        // FeldTypen wieder entfernen
//STRIP001
//STRIP001  if( !pDDETyp && !bDoublePaste )
//STRIP001  {
//STRIP001      // FeldTyp wieder entfernen - Fehler aufgetreten!
//STRIP001      for( j = nSize; j >= INIT_FLDTYPES; --j )
//STRIP001          if( pTyp == rWrtShell.GetFldType( j ) )
//STRIP001          {
//STRIP001              rWrtShell.RemoveFldType( j );
//STRIP001              break;
//STRIP001          }
//STRIP001  }
//STRIP001
//STRIP001  return 1;
//STRIP001 #else
//STRIP001  return 0;
//STRIP001 #endif
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 int SwTransferable::_PasteSdrFormat(  TransferableDataHelper& rData,
//STRIP001                                  SwWrtShell& rSh, USHORT nAction,
//STRIP001                                  const Point* pPt, BYTE nActionFlags )
//STRIP001 {
//STRIP001  int nRet = 0;
//STRIP001  SotStorageStreamRef xStrm;
//STRIP001  if( rData.GetSotStorageStream( SOT_FORMATSTR_ID_DRAWING, xStrm ))
//STRIP001  {
//STRIP001      xStrm->SetVersion( SOFFICE_FILEFORMAT_50 );
//STRIP001      rSh.Paste( *xStrm, nAction, pPt );
//STRIP001      nRet = 1;
//STRIP001
//STRIP001      if( nRet && ( nActionFlags &
//STRIP001          ( EXCHG_OUT_ACTION_FLAG_INSERT_TARGETURL >> 8) ))
//STRIP001          SwTransferable::_PasteTargetURL( rData, rSh, 0, 0, FALSE );
//STRIP001  }
//STRIP001  return nRet;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 int SwTransferable::_PasteGrf( TransferableDataHelper& rData, SwWrtShell& rSh,
//STRIP001                              ULONG nFmt, USHORT nAction, const Point* pPt,
//STRIP001                              BYTE nActionFlags, BOOL bMsg )
//STRIP001 {
//STRIP001  int nRet = 0;
//STRIP001
//STRIP001  Graphic aGrf;
//STRIP001  INetBookmark aBkmk;
//STRIP001  BOOL bCheckForGrf = FALSE, bCheckForImageMap = FALSE;
//STRIP001
//STRIP001  switch( nFmt )
//STRIP001  {
//STRIP001  case SOT_FORMAT_BITMAP:
//STRIP001  case SOT_FORMAT_GDIMETAFILE:
//STRIP001      nRet = rData.GetGraphic( nFmt, aGrf );
//STRIP001      break;
//STRIP001
//STRIP001  case SOT_FORMATSTR_ID_NETSCAPE_BOOKMARK:
//STRIP001  case SOT_FORMATSTR_ID_FILEGRPDESCRIPTOR:
//STRIP001  case SOT_FORMATSTR_ID_UNIFORMRESOURCELOCATOR:
//STRIP001      if( 0 != ( nRet = rData.GetINetBookmark( nFmt, aBkmk ) ))
//STRIP001      {
//STRIP001 /*               if( SW_PASTESDR_SETATTR != nAction )
//STRIP001          {
//STRIP001              INetURLObject aURL( aBkmk.GetURL() );
//STRIP001              bCheckForGrf = INET_PROT_FILE == aURL.GetProtocol();
//STRIP001              nRet = 0 != bCheckForGrf;
//STRIP001          }
//STRIP001 */
//STRIP001          if( SW_PASTESDR_SETATTR == nAction )
//STRIP001              nFmt = SOT_FORMATSTR_ID_NETSCAPE_BOOKMARK;
//STRIP001          else
//STRIP001              bCheckForGrf = TRUE;
//STRIP001      }
//STRIP001      break;
//STRIP001
//STRIP001  case SOT_FORMAT_FILE:
//STRIP001      {
//STRIP001          String sTxt;
//STRIP001          if( 0 != ( nRet = rData.GetString( nFmt, sTxt ) ) )
//STRIP001          {
//STRIP001              String sDesc;
//STRIP001              SwTransferable::_CheckForURLOrLNKFile( rData, sTxt, &sDesc );
//STRIP001
//STRIP001              aBkmk = INetBookmark(
//STRIP001                  so3::StaticBaseUrl::SmartRelToAbs( sTxt ), sDesc );
//STRIP001              bCheckForGrf = TRUE;
//STRIP001              bCheckForImageMap = SW_PASTESDR_REPLACE == nAction;
//STRIP001          }
//STRIP001      }
//STRIP001      break;
//STRIP001
//STRIP001  default:
//STRIP001      nRet = rData.GetGraphic( nFmt, aGrf );
//STRIP001      break;
//STRIP001  }
//STRIP001
//STRIP001  if( bCheckForGrf )
//STRIP001  {
//STRIP001      //!!! auf FileSystem abpruefen - nur dann ist es sinnvoll die
//STRIP001      // Grafiken zu testen !!!!
//STRIP001      GraphicFilter *pFlt = ::GetGrfFilter();
//STRIP001      nRet = GRFILTER_OK == ::LoadGraphic( aBkmk.GetURL(), aEmptyStr,
//STRIP001                                          aGrf, pFlt );
//STRIP001      if( !nRet && SW_PASTESDR_SETATTR == nAction &&
//STRIP001          SOT_FORMAT_FILE == nFmt &&
//STRIP001          // Bug 63031 - nur bei Rahmenselektion
//STRIP001          rSh.IsFrmSelected() )
//STRIP001      {
//STRIP001          // dann als Hyperlink hinter die Grafik setzen
//STRIP001          nFmt = SOT_FORMATSTR_ID_NETSCAPE_BOOKMARK;
//STRIP001          nRet = TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if( nRet )
//STRIP001  {
//STRIP001      String sURL;
//STRIP001      if( rSh.GetView().GetDocShell()->ISA(SwWebDocShell) )
//STRIP001          sURL = aBkmk.GetURL();
//STRIP001
//STRIP001      switch( nAction )
//STRIP001      {
//STRIP001      case SW_PASTESDR_INSERT:
//STRIP001          SwTransferable::SetSelInShell( rSh, FALSE, pPt );
//STRIP001          rSh.Insert( sURL, aEmptyStr, aGrf );
//STRIP001          break;
//STRIP001
//STRIP001      case SW_PASTESDR_REPLACE:
//STRIP001          if( rSh.IsObjSelected() )
//STRIP001          {
//STRIP001              rSh.ReplaceSdrObj( sURL, aEmptyStr, &aGrf );
//STRIP001              Point aPt( pPt ? *pPt : rSh.GetCrsrDocPos() );
//STRIP001              SwTransferable::SetSelInShell( rSh, TRUE, &aPt );
//STRIP001          }
//STRIP001          else
//STRIP001              rSh.ReRead( sURL, aEmptyStr, &aGrf );
//STRIP001          break;
//STRIP001
//STRIP001      case SW_PASTESDR_SETATTR:
//STRIP001          if( SOT_FORMATSTR_ID_NETSCAPE_BOOKMARK == nFmt )
//STRIP001          {
//STRIP001              if( rSh.IsFrmSelected() )
//STRIP001              {
//STRIP001                  SfxItemSet aSet( rSh.GetAttrPool(), RES_URL, RES_URL );
//STRIP001                  rSh.GetFlyFrmAttr( aSet );
//STRIP001                  SwFmtURL aURL( (SwFmtURL&)aSet.Get( RES_URL ) );
//STRIP001                  aURL.SetURL( aBkmk.GetURL(), FALSE );
//STRIP001                  aSet.Put( aURL );
//STRIP001                  rSh.SetFlyFrmAttr( aSet );
//STRIP001              }
//STRIP001          }
//STRIP001          else if( rSh.IsObjSelected() )
//STRIP001              rSh.Paste( aGrf );
//STRIP001          else if( OBJCNT_GRF == rSh.GetObjCntTypeOfSelection() )
//STRIP001              rSh.ReRead( sURL, aEmptyStr, &aGrf );
//STRIP001          else
//STRIP001          {
//STRIP001              SwTransferable::SetSelInShell( rSh, FALSE, pPt );
//STRIP001              rSh.Insert( aBkmk.GetURL(), aEmptyStr, aGrf );
//STRIP001          }
//STRIP001          break;
//STRIP001      default:
//STRIP001          nRet = 0;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if( nRet )
//STRIP001  {
//STRIP001
//STRIP001      if( nActionFlags &
//STRIP001          (( EXCHG_OUT_ACTION_FLAG_INSERT_IMAGEMAP |
//STRIP001              EXCHG_OUT_ACTION_FLAG_REPLACE_IMAGEMAP ) >> 8) )
//STRIP001          SwTransferable::_PasteImageMap( rData, rSh );
//STRIP001
//STRIP001      if( nActionFlags &
//STRIP001          ( EXCHG_OUT_ACTION_FLAG_INSERT_TARGETURL >> 8) )
//STRIP001          SwTransferable::_PasteTargetURL( rData, rSh, 0, 0, FALSE );
//STRIP001  }
//STRIP001  else if( bCheckForImageMap )
//STRIP001  {
//STRIP001      // oder sollte das File ein ImageMap-File sein?
//STRIP001      ImageMap aMap;
//STRIP001      SfxMedium aMed( INetURLObject(aBkmk.GetURL()).GetFull(),
//STRIP001                          STREAM_STD_READ, FALSE );
//STRIP001      if( !aMed.GetInStream()->GetError() && IMAP_ERR_OK ==
//STRIP001          aMap.Read( *aMed.GetInStream(), IMAP_FORMAT_DETECT ) &&
//STRIP001          aMap.GetIMapObjectCount() )
//STRIP001      {
//STRIP001          SfxItemSet aSet( rSh.GetAttrPool(), RES_URL, RES_URL );
//STRIP001          rSh.GetFlyFrmAttr( aSet );
//STRIP001          SwFmtURL aURL( (SwFmtURL&)aSet.Get( RES_URL ) );
//STRIP001          aURL.SetMap( &aMap );
//STRIP001          aSet.Put( aURL );
//STRIP001          rSh.SetFlyFrmAttr( aSet );
//STRIP001          nRet = 1;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  return nRet;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 int SwTransferable::_PasteImageMap( TransferableDataHelper& rData,
//STRIP001                                  SwWrtShell& rSh )
//STRIP001 {
//STRIP001  int nRet = 0;
//STRIP001  if( rData.HasFormat( SOT_FORMATSTR_ID_SVIM ))
//STRIP001  {
//STRIP001      SfxItemSet aSet( rSh.GetAttrPool(), RES_URL, RES_URL );
//STRIP001      rSh.GetFlyFrmAttr( aSet );
//STRIP001      SwFmtURL aURL( (SwFmtURL&)aSet.Get( RES_URL ) );
//STRIP001      const ImageMap* pOld = aURL.GetMap();
//STRIP001
//STRIP001      // setzen oder ersetzen ist hier die Frage
//STRIP001      ImageMap aImageMap;
//STRIP001      if( rData.GetImageMap( SOT_FORMATSTR_ID_SVIM, aImageMap ) &&
//STRIP001          ( !pOld || aImageMap != *pOld ))
//STRIP001      {
//STRIP001          aURL.SetMap( &aImageMap );
//STRIP001          aSet.Put( aURL );
//STRIP001          rSh.SetFlyFrmAttr( aSet );
//STRIP001      }
//STRIP001      nRet = 1;
//STRIP001  }
//STRIP001  return nRet;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 int SwTransferable::_PasteAsHyperlink( TransferableDataHelper& rData,
//STRIP001                                      SwWrtShell& rSh, ULONG nFmt )
//STRIP001 {
//STRIP001  int nRet = 0;
//STRIP001  String sFile;
//STRIP001  if( rData.GetString( nFmt, sFile ) && sFile.Len() )
//STRIP001  {
//STRIP001      String sDesc;
//STRIP001      SwTransferable::_CheckForURLOrLNKFile( rData, sFile, &sDesc );
//STRIP001
//STRIP001      //#41801# ersteinmal die URL absolut machen
//STRIP001      INetURLObject aURL;
//STRIP001      aURL.SetSmartProtocol( INET_PROT_FILE );
//STRIP001      aURL.SetSmartURL( sFile );
//STRIP001      sFile = aURL.GetMainURL( INetURLObject::NO_DECODE );
//STRIP001
//STRIP001      switch( rSh.GetObjCntTypeOfSelection() )
//STRIP001      {
//STRIP001      case OBJCNT_FLY:
//STRIP001      case OBJCNT_GRF:
//STRIP001      case OBJCNT_OLE:
//STRIP001          {
//STRIP001              SfxItemSet aSet( rSh.GetAttrPool(), RES_URL, RES_URL );
//STRIP001              rSh.GetFlyFrmAttr( aSet );
//STRIP001              SwFmtURL aURL( (SwFmtURL&)aSet.Get( RES_URL ) );
//STRIP001              aURL.SetURL( sFile, FALSE );
//STRIP001              if( !aURL.GetName().Len() )
//STRIP001                  aURL.SetName( sFile );
//STRIP001              aSet.Put( aURL );
//STRIP001              rSh.SetFlyFrmAttr( aSet );
//STRIP001          }
//STRIP001          break;
//STRIP001
//STRIP001      default:
//STRIP001          {
//STRIP001              rSh.InsertURL( SwFmtINetFmt( sFile, aEmptyStr ),
//STRIP001                              sDesc.Len() ? sDesc : sFile );
//STRIP001          }
//STRIP001      }
//STRIP001      nRet = TRUE;
//STRIP001  }
//STRIP001  return nRet;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 int SwTransferable::_PasteFileName( TransferableDataHelper& rData,
//STRIP001                                  SwWrtShell& rSh, ULONG nFmt,
//STRIP001                                  USHORT nAction, const Point* pPt,
//STRIP001                                  BYTE nActionFlags, BOOL bMsg )
//STRIP001 {
//STRIP001  int nRet = SwTransferable::_PasteGrf( rData, rSh, nFmt, nAction,
//STRIP001                                          pPt, nActionFlags, bMsg );
//STRIP001
//STRIP001     if( !nRet )
//STRIP001     {
//STRIP001         String sFile, sDesc;
//STRIP001         if( rData.GetString( nFmt, sFile ) && sFile.Len() )
//STRIP001         {
//STRIP001             if(Sound::IsSoundFile( sFile ))
//STRIP001             {
//STRIP001                 SvxHyperlinkItem aHyperLink( SID_HYPERLINK_SETLINK, sFile, sFile,
//STRIP001                                 aEmptyStr, aEmptyStr,
//STRIP001                                 SW_PASTESDR_INSERT == nAction ? HLINK_BUTTON : HLINK_FIELD);
//STRIP001                 SwView& rView = rSh.GetView();
//STRIP001                 rView.GetViewFrame()->GetDispatcher()->Execute(
//STRIP001                                 SID_HYPERLINK_SETLINK, SFX_CALLMODE_ASYNCHRON,
//STRIP001                                 &aHyperLink,0L);
//STRIP001             }
//STRIP001             else
//STRIP001             {
//STRIP001                 BOOL bIsURLFile = SwTransferable::_CheckForURLOrLNKFile( rData, sFile, &sDesc );
//STRIP001
//STRIP001                 //Eigenes FileFormat? -->Einfuegen, nicht fuer StarWriter/Web
//STRIP001                 const SfxFilter* pFlt = SW_PASTESDR_SETATTR == nAction
//STRIP001                         ? 0 : SwIoSystem::GetFileFilter( sFile, aEmptyStr );
//STRIP001                 if( pFlt && !rSh.GetView().GetDocShell()->ISA(SwWebDocShell)
//STRIP001     /*
//STRIP001     JP 02.07.98: warum nur fuer die Formate ??
//STRIP001                     && ( pFlt->GetUserData() == FILTER_SW5 ||
//STRIP001                     pFlt->GetUserData() == FILTER_SW4 ||
//STRIP001                     pFlt->GetUserData() == FILTER_SW3 ||
//STRIP001                     pFlt->GetUserData() == FILTER_SWG )
//STRIP001     */
//STRIP001                     )
//STRIP001                 {
//STRIP001     // und dann per PostUser Event den Bereich-Einfuegen-Dialog hochreissen
//STRIP001                     SwSection* pSect = new SwSection( FILE_LINK_SECTION,
//STRIP001                                     rSh.GetDoc()->GetUniqueSectionName() );
//STRIP001                     pSect->SetLinkFileName( so3::StaticBaseUrl::SmartRelToAbs( sFile ) );
//STRIP001                     pSect->SetProtect( TRUE );
//STRIP001
//STRIP001                     Application::PostUserEvent( STATIC_LINK( &rSh, SwWrtShell,
//STRIP001                                                 InsertRegionDialog ), pSect );
//STRIP001                     nRet = 1;
//STRIP001     #if 0
//STRIP001                     if( rSh.InsertSection( aSect ) )
//STRIP001                     {
//STRIP001                         if( SW_PASTESDR_SETATTR != nAction )
//STRIP001                         {
//STRIP001                             aSect.SetType( CONTENT_SECTION );
//STRIP001                             aSect.SetProtect( FALSE );
//STRIP001                             for( USHORT i = rSh.GetSectionFmtCount(); i; )
//STRIP001                                 if( aNm == rSh.GetSectionFmt( --i ).
//STRIP001                                                     GetSection()->GetName())
//STRIP001                                 {
//STRIP001                                     rSh.ChgSection( i, aSect );
//STRIP001                                     break;
//STRIP001                                 }
//STRIP001                         }
//STRIP001                         nRet = TRUE;
//STRIP001                     }
//STRIP001     #endif
//STRIP001                 }
//STRIP001                 else if( SW_PASTESDR_SETATTR == nAction ||
//STRIP001                         ( bIsURLFile && SW_PASTESDR_INSERT == nAction ))
//STRIP001                 {
//STRIP001                     //Fremde Files koennen wir immerhin noch als Links
//STRIP001                     //Einfuegen.
//STRIP001
//STRIP001                     //#41801# ersteinmal die URL absolut machen
//STRIP001                     INetURLObject aURL;
//STRIP001                     aURL.SetSmartProtocol( INET_PROT_FILE );
//STRIP001                     aURL.SetSmartURL( sFile );
//STRIP001                     sFile = aURL.GetMainURL( INetURLObject::NO_DECODE );
//STRIP001
//STRIP001                     switch( rSh.GetObjCntTypeOfSelection() )
//STRIP001                     {
//STRIP001                     case OBJCNT_FLY:
//STRIP001                     case OBJCNT_GRF:
//STRIP001                     case OBJCNT_OLE:
//STRIP001                         {
//STRIP001                             SfxItemSet aSet( rSh.GetAttrPool(), RES_URL, RES_URL );
//STRIP001                             rSh.GetFlyFrmAttr( aSet );
//STRIP001                             SwFmtURL aURL( (SwFmtURL&)aSet.Get( RES_URL ) );
//STRIP001                             aURL.SetURL( sFile, FALSE );
//STRIP001                             if( !aURL.GetName().Len() )
//STRIP001                                 aURL.SetName( sFile );
//STRIP001                             aSet.Put( aURL );
//STRIP001                             rSh.SetFlyFrmAttr( aSet );
//STRIP001                         }
//STRIP001                         break;
//STRIP001
//STRIP001                     default:
//STRIP001                         {
//STRIP001                             rSh.InsertURL( SwFmtINetFmt( sFile, aEmptyStr ),
//STRIP001                                             sDesc.Len() ? sDesc : sFile );
//STRIP001                         }
//STRIP001                     }
//STRIP001                     nRet = TRUE;
//STRIP001                 }
//STRIP001             }
//STRIP001      }
//STRIP001  }
//STRIP001  return nRet;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 int SwTransferable::_PasteDBData( TransferableDataHelper& rData,
//STRIP001                                  SwWrtShell& rSh, ULONG nFmt, BOOL bLink,
//STRIP001                                  const Point* pDragPt, BOOL bMsg )
//STRIP001 {
//STRIP001  int nRet = 0;
//STRIP001  String sTxt;
//STRIP001  if( rData.GetString( nFmt, sTxt ) && sTxt.Len() )
//STRIP001  {
//STRIP001      USHORT nWh = SOT_FORMATSTR_ID_SBA_CTRLDATAEXCHANGE == nFmt
//STRIP001                  ? 0
//STRIP001                  : SOT_FORMATSTR_ID_SBA_DATAEXCHANGE == nFmt
//STRIP001                              ? (bLink
//STRIP001                                  ? FN_QRY_MERGE_FIELD
//STRIP001                                  : FN_QRY_INSERT)
//STRIP001                              : (bLink
//STRIP001                                  ? 0
//STRIP001                                  : FN_QRY_INSERT_FIELD );
//STRIP001         DataFlavorExVector& rVector = rData.GetDataFlavorExVector();
//STRIP001      sal_Bool bHaveColumnDescriptor = OColumnTransferable::canExtractColumnDescriptor(rVector, CTF_COLUMN_DESCRIPTOR | CTF_CONTROL_EXCHANGE);
//STRIP001      if( nWh )
//STRIP001      {
//STRIP001             SfxUsrAnyItem* pConnectionItem   = 0;
//STRIP001          SfxUsrAnyItem* pCursorItem      = 0;
//STRIP001             SfxUsrAnyItem* pColumnItem       = 0;
//STRIP001             SfxUsrAnyItem* pSourceItem       = 0;
//STRIP001             SfxUsrAnyItem* pCommandItem      = 0;
//STRIP001             SfxUsrAnyItem* pCommandTypeItem = 0;
//STRIP001             SfxUsrAnyItem* pColumnNameItem   = 0;
//STRIP001             SfxUsrAnyItem* pSelectionItem    = 0;
//STRIP001
//STRIP001             BOOL bDataAvailable = TRUE;
//STRIP001          ODataAccessDescriptor aDesc;
//STRIP001             if(bHaveColumnDescriptor)
//STRIP001                 aDesc = OColumnTransferable::extractColumnDescriptor(rData);
//STRIP001             else if(ODataAccessObjectTransferable::canExtractObjectDescriptor(rVector) )
//STRIP001                 aDesc = ODataAccessObjectTransferable::extractObjectDescriptor(rData);
//STRIP001             else
//STRIP001                 bDataAvailable = FALSE;
//STRIP001
//STRIP001             if ( bDataAvailable )
//STRIP001             {
//STRIP001                 pConnectionItem = new SfxUsrAnyItem(FN_DB_CONNECTION_ANY, aDesc[daConnection]);
//STRIP001                 pColumnItem = new SfxUsrAnyItem(FN_DB_COLUMN_ANY, aDesc[daColumnObject]);
//STRIP001                 pSourceItem = new SfxUsrAnyItem(FN_DB_DATA_SOURCE_ANY, aDesc[daDataSource]);
//STRIP001                 pCommandItem = new SfxUsrAnyItem(FN_DB_DATA_COMMAND_ANY, aDesc[daCommand]);
//STRIP001                 pCommandTypeItem = new SfxUsrAnyItem(FN_DB_DATA_COMMAND_TYPE_ANY, aDesc[daCommandType]);
//STRIP001                 pColumnNameItem = new SfxUsrAnyItem(FN_DB_DATA_COLUMN_NAME_ANY, aDesc[daColumnName]);
//STRIP001                 pSelectionItem = new SfxUsrAnyItem(FN_DB_DATA_SELECTION_ANY, aDesc[daSelection]);
//STRIP001              pCursorItem = new SfxUsrAnyItem(FN_DB_DATA_CURSOR_ANY, aDesc[daCursor]);
//STRIP001             }
//STRIP001
//STRIP001             SwView& rView = rSh.GetView();
//STRIP001          //force ::SelectShell
//STRIP001          rView.StopShellTimer();
//STRIP001
//STRIP001          SfxStringItem aDataDesc( nWh, sTxt );
//STRIP001          rView.GetViewFrame()->GetDispatcher()->Execute(
//STRIP001                                 nWh, SFX_CALLMODE_ASYNCHRON, &aDataDesc,
//STRIP001                                 pConnectionItem, pColumnItem,
//STRIP001                                 pSourceItem, pCommandItem, pCommandTypeItem,
//STRIP001                                 pColumnNameItem, pSelectionItem, pCursorItem,0L);
//STRIP001             delete pConnectionItem;
//STRIP001             delete pColumnItem;
//STRIP001             delete pSourceItem;
//STRIP001             delete pCommandItem;
//STRIP001             delete pCommandTypeItem;
//STRIP001             delete pColumnNameItem;
//STRIP001          delete pCursorItem;
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          SdrObject* pObj;
//STRIP001          rSh.MakeDrawView();
//STRIP001          FmFormView* pFmView = PTR_CAST( FmFormView, rSh.GetDrawView() );
//STRIP001          if (pFmView && bHaveColumnDescriptor)
//STRIP001          {
//STRIP001              if ( 0 != (pObj = pFmView->CreateFieldControl( OColumnTransferable::extractColumnDescriptor(rData) ) ) )
//STRIP001                  rSh.SwFEShell::Insert( *pObj, 0, 0, pDragPt );
//STRIP001          }
//STRIP001      }
//STRIP001      nRet = 1;
//STRIP001  }
//STRIP001  else if( bMsg )
//STRIP001  {
//STRIP001      InfoBox( 0, SW_RES(MSG_CLPBRD_FORMAT_ERROR)).Execute();
//STRIP001  }
//STRIP001  return nRet;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 int SwTransferable::_PasteFileList( TransferableDataHelper& rData,
//STRIP001                                  SwWrtShell& rSh, BOOL bLink,
//STRIP001                                  const Point* pPt, BOOL bMsg )
//STRIP001 {
//STRIP001  int nRet = 0;
//STRIP001  FileList aFileList;
//STRIP001  if( rData.GetFileList( SOT_FORMAT_FILE_LIST, aFileList ) &&
//STRIP001      aFileList.Count() )
//STRIP001  {
//STRIP001      USHORT nAct = bLink ? SW_PASTESDR_SETATTR : SW_PASTESDR_INSERT;
//STRIP001      String sFlyNm;
//STRIP001      // iterate over the filelist
//STRIP001      for( ULONG n = 0, nEnd = aFileList.Count(); n < nEnd; ++n )
//STRIP001      {
//STRIP001          TransferDataContainer* pHlp = new TransferDataContainer;
//STRIP001          pHlp->CopyString( FORMAT_FILE, aFileList.GetFile( n ));
//STRIP001          TransferableDataHelper aData( pHlp );
//STRIP001
//STRIP001          if( SwTransferable::_PasteGrf( aData, rSh, SOT_FORMAT_FILE, nAct,
//STRIP001                                          pPt, FALSE, bMsg ))
//STRIP001          {
//STRIP001              if( bLink )
//STRIP001              {
//STRIP001                  sFlyNm = rSh.GetFlyName();
//STRIP001                  SwTransferable::SetSelInShell( rSh, FALSE, pPt );
//STRIP001              }
//STRIP001              nRet = 1;
//STRIP001          }
//STRIP001      }
//STRIP001      if( sFlyNm.Len() )
//STRIP001          rSh.GotoFly( sFlyNm );
//STRIP001  }
//STRIP001  else if( bMsg )
//STRIP001  {
//STRIP001      InfoBox( 0, SW_RES(MSG_CLPBRD_FORMAT_ERROR)).Execute();
//STRIP001  }
//STRIP001  return nRet;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 BOOL SwTransferable::_CheckForURLOrLNKFile( TransferableDataHelper& rData,
//STRIP001                                      String& rFileName, String* pTitle )
//STRIP001 {
//STRIP001  BOOL bIsURLFile = FALSE;
//STRIP001  INetBookmark aBkmk;
//STRIP001  if( rData.GetINetBookmark( SOT_FORMATSTR_ID_SOLK, aBkmk ) )
//STRIP001  {
//STRIP001      rFileName = aBkmk.GetURL();
//STRIP001      if( pTitle )
//STRIP001          *pTitle = aBkmk.GetDescription();
//STRIP001      bIsURLFile = TRUE;
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      xub_StrLen nLen = rFileName.Len();
//STRIP001      if( 4 < nLen && '.' == rFileName.GetChar( nLen - 4 ))
//STRIP001      {
//STRIP001          String sExt( rFileName.Copy( nLen - 3 ));
//STRIP001          if( sExt.EqualsIgnoreCaseAscii( "url" ))
//STRIP001          {
//STRIP001 ASSERT( !&rFileName, "how do we read today .URL - Files?" );
//STRIP001 // JP 12.05.00 UNICODE - CHANGES
//STRIP001 #if 0
//STRIP001
//STRIP001              bIsURLFile = TRUE;
//STRIP001              Config aCfg( rFileName );
//STRIP001              aCfg.SetGroup( INTERNETSHORTCUT_ID_TAG );
//STRIP001
//STRIP001              // Einlesung und Konvertierung des URL aus der Datei
//STRIP001              rFileName = aCfg.ReadKey( INTERNETSHORTCUT_URL_TAG,
//STRIP001                                          URLFILE_CHARSET );
//STRIP001
//STRIP001              // dann teste doch mal auf ein lokales File
//STRIP001              INetURLObject aURL( rFileName );
//STRIP001              if( INET_PROT_FILE == aURL.GetProtocol() )
//STRIP001                  rFileName = aURL.PathToFileName();
//STRIP001
//STRIP001              // Einlesung und Konvertierung des Titels aus der Datei
//STRIP001              if( pTitle )
//STRIP001                  *pTitle = aCfg.ReadKey( INTERNETSHORTCUT_TITLE_TAG,
//STRIP001                                          URLFILE_CHARSET  );
//STRIP001 #endif
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  return bIsURLFile;
//STRIP001 }

// -----------------------------------------------------------------------

/*N*/ BOOL SwTransferable::IsPasteSpecial( const SwWrtShell& rWrtShell,
/*N*/                                    const TransferableDataHelper& rData )
/*N*/ {
/*N*/     // we can paste-special if there's an entry in the paste-special-format list
/*N*/     SvxClipboardFmtItem aClipboardFmtItem(0);
/*N*/     FillClipFmtItem( rWrtShell, rData, aClipboardFmtItem);
/*N*/     return aClipboardFmtItem.Count() > 0;
/*N*/ }

// -----------------------------------------------------------------------

//STRIP001 int SwTransferable::PasteFormat( SwWrtShell& rSh,
//STRIP001                                  TransferableDataHelper& rData,
//STRIP001                                  ULONG nFormat )
//STRIP001 {
//STRIP001  SwWait aWait( *rSh.GetView().GetDocShell(), FALSE );
//STRIP001  int nRet = 0;
//STRIP001
//STRIP001  ULONG nPrivateFmt = FORMAT_PRIVATE;
//STRIP001  SwTransferable *pClipboard = SW_MOD()->pClipboard;
//STRIP001  if( pClipboard &&
//STRIP001      ((TRNSFR_DOCUMENT|TRNSFR_GRAPHIC|TRNSFR_OLE) & pClipboard->eBufferType ))
//STRIP001      nPrivateFmt = SOT_FORMATSTR_ID_EMBED_SOURCE;
//STRIP001
//STRIP001  if( pClipboard && nPrivateFmt == nFormat )
//STRIP001      nRet = pClipboard->PrivatePaste( rSh );
//STRIP001  else if( rData.HasFormat( nFormat ) )
//STRIP001  {
//STRIP001         Reference<XTransferable> xTransferable( rData.GetXTransferable() );
//STRIP001      USHORT nEventAction,
//STRIP001             nDestination = SwTransferable::GetSotDestination( rSh ),
//STRIP001             nSourceOptions =
//STRIP001                  (( EXCHG_DEST_DOC_TEXTFRAME == nDestination ||
//STRIP001                     EXCHG_DEST_SWDOC_FREE_AREA == nDestination ||
//STRIP001                     EXCHG_DEST_DOC_TEXTFRAME_WEB == nDestination ||
//STRIP001                     EXCHG_DEST_SWDOC_FREE_AREA_WEB == nDestination )
//STRIP001                                      ? EXCHG_IN_ACTION_COPY
//STRIP001                                      : EXCHG_IN_ACTION_MOVE),
//STRIP001             nAction = SotExchange::GetExchangeAction(
//STRIP001                                  rData.GetDataFlavorExVector(),
//STRIP001                                  nDestination,
//STRIP001                                  nSourceOptions,             /* ?? */
//STRIP001                                  EXCHG_IN_ACTION_DEFAULT,    /* ?? */
//STRIP001                                  nFormat, nEventAction, nFormat,
//STRIP001                                  lcl_getTransferPointer ( xTransferable ) );
//STRIP001
//STRIP001      if( EXCHG_INOUT_ACTION_NONE != nAction )
//STRIP001          nRet = SwTransferable::PasteData( rData, rSh, nAction, nFormat,
//STRIP001                                                 nDestination, TRUE, FALSE );
//STRIP001  }
//STRIP001  return nRet;
//STRIP001 }

// -----------------------------------------------------------------------

/*N*/ int SwTransferable::_TestAllowedFormat( const TransferableDataHelper& rData,
/*N*/                                       ULONG nFormat, USHORT nDestination )
/*N*/ {
/*N*/   USHORT nAction = EXCHG_INOUT_ACTION_NONE, nEventAction;
/*N*/   if( rData.HasFormat( nFormat )) {
/*N*/         Reference<XTransferable> xTransferable( rData.GetXTransferable() );
/*N*/       nAction = SotExchange::GetExchangeAction(
/*N*/                       rData.GetDataFlavorExVector(),
/*N*/                       nDestination, EXCHG_IN_ACTION_COPY,
/*N*/                       EXCHG_IN_ACTION_COPY, nFormat,
/*N*/                       nEventAction, nFormat,
/*N*/                       lcl_getTransferPointer ( xTransferable ) );
/*N*/     }
/*N*/   return EXCHG_INOUT_ACTION_NONE != nAction;
/*N*/ }

// -----------------------------------------------------------------------

/**
 * the list of formats which will be offered to the user in the 'Paste
 * Special...' dialog and the paste button menu
 */
/*N*/ static USHORT aPasteSpecialIds[] =
/*N*/ {
/*N*/     SOT_FORMATSTR_ID_HTML,
/*N*/     SOT_FORMATSTR_ID_HTML_SIMPLE,
/*N*/     SOT_FORMATSTR_ID_HTML_NO_COMMENT,
/*N*/     FORMAT_RTF,
/*N*/     FORMAT_STRING,
/*N*/     SOT_FORMATSTR_ID_SONLK,
/*N*/     SOT_FORMATSTR_ID_NETSCAPE_BOOKMARK,
/*N*/     SOT_FORMATSTR_ID_DRAWING,
/*N*/     SOT_FORMATSTR_ID_SVXB,
/*N*/     FORMAT_GDIMETAFILE,
/*N*/     FORMAT_BITMAP,
/*N*/     SOT_FORMATSTR_ID_SVIM,
/*N*/     SOT_FORMATSTR_ID_FILEGRPDESCRIPTOR,
/*N*/     0
/*N*/ };

//STRIP001 int SwTransferable::PasteSpecial( SwWrtShell& rSh, TransferableDataHelper& rData, ULONG& rFormatUsed )
//STRIP001 {
//STRIP001  int nRet = 0;
//STRIP001  SvPasteObjectDialog* pDlg = new SvPasteObjectDialog;
//STRIP001
//STRIP001  DataFlavorExVector aFormats( rData.GetDataFlavorExVector() );
//STRIP001  TransferableObjectDescriptor aDesc;
//STRIP001
//STRIP001  USHORT nDest = SwTransferable::GetSotDestination( rSh );
//STRIP001
//STRIP001  SwTransferable *pClipboard = SW_MOD()->pClipboard;
//STRIP001  if( pClipboard )
//STRIP001  {
//STRIP001      aDesc = pClipboard->aObjDesc;
//STRIP001      USHORT nResId;
//STRIP001      if( pClipboard->eBufferType & TRNSFR_DOCUMENT )
//STRIP001          nResId = STR_PRIVATETEXT;
//STRIP001      else if( pClipboard->eBufferType & TRNSFR_GRAPHIC )
//STRIP001          nResId = STR_PRIVATEGRAPHIC;
//STRIP001      else if( pClipboard->eBufferType == TRNSFR_OLE )
//STRIP001          nResId = STR_PRIVATEOLE;
//STRIP001      else
//STRIP001          nResId = 0;
//STRIP001
//STRIP001      if( nResId )
//STRIP001      {
//STRIP001          if( STR_PRIVATEOLE == nResId || STR_PRIVATEGRAPHIC == nResId )
//STRIP001          {
//STRIP001              // add SOT_FORMATSTR_ID_EMBED_SOURCE to the formats. This
//STRIP001              // format display then the private format name.
//STRIP001              DataFlavorEx aFlavorEx;
//STRIP001              aFlavorEx.mnSotId = SOT_FORMATSTR_ID_EMBED_SOURCE;
//STRIP001              aFormats.insert( aFormats.begin(), aFlavorEx );
//STRIP001          }
//STRIP001          pDlg->SetObjName( pClipboard->aObjDesc.maClassName,
//STRIP001                              SW_RES( nResId ) );
//STRIP001          pDlg->Insert( SOT_FORMATSTR_ID_EMBED_SOURCE, aEmptyStr );
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      if( rData.HasFormat( SOT_FORMATSTR_ID_OBJECTDESCRIPTOR ) )
//STRIP001          rData.GetTransferableObjectDescriptor(
//STRIP001                              SOT_FORMATSTR_ID_OBJECTDESCRIPTOR, aDesc );
//STRIP001
//STRIP001      if( SwTransferable::_TestAllowedFormat( rData, SOT_FORMATSTR_ID_EMBED_SOURCE, nDest ))
//STRIP001          pDlg->Insert( SOT_FORMATSTR_ID_EMBED_SOURCE, aEmptyStr );
//STRIP001      if( SwTransferable::_TestAllowedFormat( rData, SOT_FORMATSTR_ID_LINK_SOURCE, nDest ))
//STRIP001          pDlg->Insert( SOT_FORMATSTR_ID_LINK_SOURCE, aEmptyStr );
//STRIP001  }
//STRIP001
//STRIP001 #ifdef DDE_AVAILABLE
//STRIP001
//STRIP001  if( SwTransferable::_TestAllowedFormat( rData, SOT_FORMATSTR_ID_LINK, nDest ))
//STRIP001      pDlg->Insert( SOT_FORMATSTR_ID_LINK, SW_RES(STR_DDEFORMAT) );
//STRIP001
//STRIP001 #endif
//STRIP001
//STRIP001  for( USHORT* pIds = aPasteSpecialIds; *pIds; ++pIds )
//STRIP001      if( SwTransferable::_TestAllowedFormat( rData, *pIds, nDest ))
//STRIP001          pDlg->Insert( *pIds, aEmptyStr );
//STRIP001
//STRIP001  ULONG nFormat = pDlg->Execute( &rSh.GetView().GetEditWin(), aFormats,
//STRIP001                                  aDesc, rData );
//STRIP001
//STRIP001  if( nFormat )
//STRIP001      nRet = SwTransferable::PasteFormat( rSh, rData, nFormat );
//STRIP001
//STRIP001     if ( nRet )
//STRIP001         rFormatUsed = nFormat;
//STRIP001
//STRIP001     delete pDlg;
//STRIP001  return nRet;
//STRIP001 }


/*N*/ void SwTransferable::FillClipFmtItem( const SwWrtShell& rSh,
/*N*/                               const TransferableDataHelper& rData,
/*N*/                               SvxClipboardFmtItem & rToFill )
/*N*/ {
/*N*/   USHORT nDest = SwTransferable::GetSotDestination( rSh );
/*N*/   SwTransferable *pClipboard = SW_MOD()->pClipboard;
/*N*/   if( pClipboard )
/*N*/   {
/*?*/       USHORT nResId;
/*?*/       if( pClipboard->eBufferType & TRNSFR_DOCUMENT )
/*?*/           nResId = STR_PRIVATETEXT;
/*?*/       else if( pClipboard->eBufferType & TRNSFR_GRAPHIC )
/*?*/           nResId = STR_PRIVATEGRAPHIC;
/*?*/       else if( pClipboard->eBufferType == TRNSFR_OLE )
/*?*/           nResId = STR_PRIVATEOLE;
/*?*/       else
/*?*/           nResId = 0;
/*?*/
/*?*/       if( nResId )
/*?*/           rToFill.AddClipbrdFormat( SOT_FORMATSTR_ID_EMBED_SOURCE,
/*?*/                                       SW_RES( nResId ) );
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       TransferableObjectDescriptor aDesc;
/*N*/       if( rData.HasFormat( SOT_FORMATSTR_ID_OBJECTDESCRIPTOR ) )
/*N*/           ((TransferableDataHelper&)rData).GetTransferableObjectDescriptor(
/*N*/                               SOT_FORMATSTR_ID_OBJECTDESCRIPTOR, aDesc );
/*N*/
/*N*/       if( SwTransferable::_TestAllowedFormat( rData, SOT_FORMATSTR_ID_EMBED_SOURCE, nDest ))
/*N*/           rToFill.AddClipbrdFormat( SOT_FORMATSTR_ID_EMBED_SOURCE,
/*N*/                                           aDesc.maTypeName );
/*N*/       if( SwTransferable::_TestAllowedFormat( rData, SOT_FORMATSTR_ID_LINK_SOURCE, nDest ))
/*N*/           rToFill.AddClipbrdFormat( SOT_FORMATSTR_ID_LINK_SOURCE );
/*N*/
/*N*/       SotFormatStringId nFormat;
/*N*/       if ( rData.HasFormat(nFormat = SOT_FORMATSTR_ID_EMBED_SOURCE_OLE) || rData.HasFormat(nFormat = SOT_FORMATSTR_ID_EMBEDDED_OBJ_OLE) )
/*N*/       {
/*N*/           String sName,sSource;
/*N*/           if ( SvPasteObjectDialog::GetEmbeddedName(rData,sName,sSource,nFormat) )
/*N*/               rToFill.AddClipbrdFormat( nFormat, sName );
/*N*/       }
/*N*/   }
/*N*/
/*N*/ #ifdef DDE_AVAILABLE
/*N*/
/*N*/   if( SwTransferable::_TestAllowedFormat( rData, SOT_FORMATSTR_ID_LINK, nDest ))
/*N*/       rToFill.AddClipbrdFormat( SOT_FORMATSTR_ID_LINK, SW_RES(STR_DDEFORMAT) );
/*N*/
/*N*/ #endif
/*N*/
/*N*/   for( USHORT* pIds = aPasteSpecialIds; *pIds; ++pIds )
/*N*/       if( SwTransferable::_TestAllowedFormat( rData, *pIds, nDest ))
/*N*/           rToFill.AddClipbrdFormat( *pIds, aEmptyStr );
/*N*/ }

//STRIP001 void SwTransferable::SetDataForDragAndDrop( const Point& rSttPos )
//STRIP001 {
//STRIP001     if(!pWrtShell)
//STRIP001         return;
//STRIP001     String sGrfNm;
//STRIP001  const int nSelection = pWrtShell->GetSelectionType();
//STRIP001  if( SwWrtShell::SEL_GRF == nSelection)
//STRIP001  {
//STRIP001      AddFormat( SOT_FORMATSTR_ID_SVXB );
//STRIP001      const Graphic &rGrf = pWrtShell->GetGraphic();
//STRIP001      if ( rGrf.IsSupportedGraphic() )
//STRIP001      {
//STRIP001          AddFormat( FORMAT_GDIMETAFILE );
//STRIP001          AddFormat( FORMAT_BITMAP );
//STRIP001      }
//STRIP001      eBufferType = TRNSFR_GRAPHIC;
//STRIP001      pWrtShell->GetGrfNms( &sGrfNm, 0 );
//STRIP001  }
//STRIP001  else if( SwWrtShell::SEL_OLE == nSelection )
//STRIP001  {
//STRIP001      AddFormat( SOT_FORMATSTR_ID_EMBED_SOURCE );
//STRIP001      AddFormat( SOT_FORMATSTR_ID_OBJECTDESCRIPTOR );
//STRIP001      AddFormat( FORMAT_GDIMETAFILE );
//STRIP001      eBufferType = TRNSFR_OLE;
//STRIP001  }
//STRIP001  //Gibt es ueberhaupt etwas zum bereitstellen?
//STRIP001  else if ( pWrtShell->IsSelection() || pWrtShell->IsFrmSelected() ||
//STRIP001            pWrtShell->IsObjSelected() )
//STRIP001  {
//STRIP001      if( pWrtShell->IsObjSelected() )
//STRIP001          eBufferType = TRNSFR_DRAWING;
//STRIP001      else
//STRIP001      {
//STRIP001          eBufferType = TRNSFR_DOCUMENT;
//STRIP001          if( SwWrtShell::NO_WORD !=
//STRIP001              pWrtShell->IntelligentCut( nSelection, FALSE ))
//STRIP001              eBufferType = TransferBufferType( TRNSFR_DOCUMENT_WORD
//STRIP001                                                  | eBufferType);
//STRIP001      }
//STRIP001
//STRIP001      if( nSelection & SwWrtShell::SEL_TBL_CELLS )
//STRIP001          eBufferType = (TransferBufferType)(TRNSFR_TABELLE | eBufferType);
//STRIP001
//STRIP001      AddFormat( SOT_FORMATSTR_ID_EMBED_SOURCE );
//STRIP001      AddFormat( SOT_FORMATSTR_ID_OBJECTDESCRIPTOR );
//STRIP001
//STRIP001      //RTF vor das Metafile von OLE stellen, weil mit weniger verlusten
//STRIP001      //behaftet.
//STRIP001      if( !pWrtShell->IsObjSelected() )
//STRIP001      {
//STRIP001          AddFormat( FORMAT_RTF );
//STRIP001          AddFormat( SOT_FORMATSTR_ID_HTML );
//STRIP001      }
//STRIP001      if( pWrtShell->IsSelection() )
//STRIP001          AddFormat( FORMAT_STRING );
//STRIP001
//STRIP001      if( nSelection & ( SwWrtShell::SEL_DRW | SwWrtShell::SEL_DRW_FORM ))
//STRIP001      {
//STRIP001          AddFormat( SOT_FORMATSTR_ID_DRAWING );
//STRIP001          if ( nSelection & SwWrtShell::SEL_DRW )
//STRIP001          {
//STRIP001              AddFormat( FORMAT_GDIMETAFILE );
//STRIP001              AddFormat( FORMAT_BITMAP );
//STRIP001          }
//STRIP001          eBufferType = (TransferBufferType)( TRNSFR_GRAPHIC | eBufferType );
//STRIP001
//STRIP001          pClpGraphic = new Graphic;
//STRIP001          if( !pWrtShell->GetDrawObjGraphic( FORMAT_GDIMETAFILE, *pClpGraphic ))
//STRIP001              pOrigGrf = pClpGraphic;
//STRIP001          pClpBitmap = new Graphic;
//STRIP001          if( !pWrtShell->GetDrawObjGraphic( FORMAT_BITMAP, *pClpBitmap ))
//STRIP001              pOrigGrf = pClpBitmap;
//STRIP001
//STRIP001          // ist es ein URL-Button ?
//STRIP001          String sURL, sDesc;
//STRIP001          if( pWrtShell->GetURLFromButton( sURL, sDesc ) )
//STRIP001          {
//STRIP001              AddFormat( FORMAT_STRING );
//STRIP001                  AddFormat( SOT_FORMATSTR_ID_SOLK );
//STRIP001                  AddFormat( SOT_FORMATSTR_ID_NETSCAPE_BOOKMARK );
//STRIP001                  AddFormat( SOT_FORMATSTR_ID_FILECONTENT );
//STRIP001                  AddFormat( SOT_FORMATSTR_ID_FILEGRPDESCRIPTOR );
//STRIP001                  AddFormat( SOT_FORMATSTR_ID_UNIFORMRESOURCELOCATOR );
//STRIP001              eBufferType = (TransferBufferType)( TRNSFR_INETFLD | eBufferType );
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      //ObjectDescriptor wurde bereits aus der alten DocShell gefuellt.
//STRIP001      //Jetzt noch anpassen. Dadurch kann im GetData die erste Anfrage
//STRIP001      //auch noch mit delayed rendering beantwortet werden.
//STRIP001      aObjDesc.mbCanLink = FALSE;
//STRIP001      aObjDesc.maDragStartPos = rSttPos;
//STRIP001      aObjDesc.maSize = OutputDevice::LogicToLogic( Size( OLESIZE ),
//STRIP001                                              MAP_TWIP, MAP_100TH_MM );
//STRIP001  }
//STRIP001  else if( nSelection & SwWrtShell::SEL_TXT && !pWrtShell->HasMark() )
//STRIP001  {
//STRIP001      // ist nur ein Feld - Selektiert?
//STRIP001      SwContentAtPos aCntntAtPos( SwContentAtPos::SW_INETATTR );
//STRIP001      Point aPos( SwEditWin::GetDDStartPosX(), SwEditWin::GetDDStartPosY());
//STRIP001
//STRIP001      if( pWrtShell->GetContentAtPos( aPos, aCntntAtPos ) )
//STRIP001      {
//STRIP001          AddFormat( FORMAT_STRING );
//STRIP001              AddFormat( SOT_FORMATSTR_ID_SOLK );
//STRIP001              AddFormat( SOT_FORMATSTR_ID_NETSCAPE_BOOKMARK );
//STRIP001              AddFormat( SOT_FORMATSTR_ID_FILECONTENT );
//STRIP001              AddFormat( SOT_FORMATSTR_ID_FILEGRPDESCRIPTOR );
//STRIP001              AddFormat( SOT_FORMATSTR_ID_UNIFORMRESOURCELOCATOR );
//STRIP001          eBufferType = TRNSFR_INETFLD;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if( pWrtShell->IsFrmSelected() )
//STRIP001  {
//STRIP001      SfxItemSet aSet( pWrtShell->GetAttrPool(), RES_URL, RES_URL );
//STRIP001      pWrtShell->GetFlyFrmAttr( aSet );
//STRIP001      const SwFmtURL& rURL = (SwFmtURL&)aSet.Get( RES_URL );
//STRIP001      if( rURL.GetMap() )
//STRIP001      {
//STRIP001          pImageMap = new ImageMap( *rURL.GetMap() );
//STRIP001          AddFormat( SOT_FORMATSTR_ID_SVIM );
//STRIP001      }
//STRIP001      else if( rURL.GetURL().Len() )
//STRIP001      {
//STRIP001          pTargetURL = new INetImage( sGrfNm, rURL.GetURL(),
//STRIP001                                      rURL.GetTargetFrameName(),
//STRIP001                                      aEmptyStr, Size() );
//STRIP001          AddFormat( SOT_FORMATSTR_ID_INET_IMAGE );
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 void SwTransferable::StartDrag( Window* pWin, const Point& rPos )
//STRIP001 {
//STRIP001     if(!pWrtShell)
//STRIP001         return;
//STRIP001     bOldIdle = pWrtShell->GetViewOptions()->IsIdle();
//STRIP001  bCleanUp = TRUE;
//STRIP001
//STRIP001  ((SwViewOption *)pWrtShell->GetViewOptions())->SetIdle( FALSE );
//STRIP001
//STRIP001  if( pWrtShell->IsSelFrmMode() )
//STRIP001      pWrtShell->ShowCrsr();
//STRIP001
//STRIP001 #ifdef MAC
//STRIP001 //!! Mac is able to show a outline of the drag source. The new interface not!
//STRIP001 //!! const Region aRegion( pWrtShell->GetCrsrRegion() );
//STRIP001 //!!                     , &aRegion
//STRIP001 #endif
//STRIP001
//STRIP001  SW_MOD()->pDragDrop = this;
//STRIP001
//STRIP001  SetDataForDragAndDrop( rPos );
//STRIP001
//STRIP001  sal_Int8 nDragOptions = DND_ACTION_COPYMOVE | DND_ACTION_LINK;
//STRIP001  SwDocShell* pDShell = pWrtShell->GetView().GetDocShell();
//STRIP001  if( ( pDShell && pDShell->IsReadOnly() ) || pWrtShell->HasReadonlySel() )
//STRIP001      nDragOptions &= ~DND_ACTION_MOVE;
//STRIP001
//STRIP001  TransferableHelper::StartDrag( pWin, nDragOptions );
//STRIP001 }

//STRIP001 void SwTransferable::DragFinished( sal_Int8 nAction )
//STRIP001 {
//STRIP001  //Und noch die letzten Nacharbeiten damit alle Stati stimmen.
//STRIP001  if( DND_ACTION_MOVE == nAction  )
//STRIP001  {
//STRIP001      if( bCleanUp )
//STRIP001      {
//STRIP001          //Es wurde auserhalb des Writers gedroped. Wir muessen noch
//STRIP001          //loeschen.
//STRIP001
//STRIP001          pWrtShell->StartAllAction();
//STRIP001          pWrtShell->StartUndo( UIUNDO_DRAG_AND_MOVE );
//STRIP001          if ( pWrtShell->IsTableMode() )
//STRIP001              pWrtShell->DeleteTblSel();
//STRIP001          else
//STRIP001          {
//STRIP001              if ( !(pWrtShell->IsSelFrmMode() || pWrtShell->IsObjSelected()) )
//STRIP001                  //SmartCut, eines der Blanks mitnehmen.
//STRIP001                  pWrtShell->IntelligentCut( pWrtShell->GetSelectionType(), TRUE );
//STRIP001              pWrtShell->DelRight();
//STRIP001          }
//STRIP001          pWrtShell->EndUndo( UIUNDO_DRAG_AND_MOVE );
//STRIP001          pWrtShell->EndAllAction();
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          const int nSelection = pWrtShell->GetSelectionType();
//STRIP001          if( ( SwWrtShell::SEL_FRM | SwWrtShell::SEL_GRF |
//STRIP001               SwWrtShell::SEL_OLE | SwWrtShell::SEL_DRW ) & nSelection )
//STRIP001          {
//STRIP001              pWrtShell->EnterSelFrmMode();
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  pWrtShell->GetView().GetEditWin().DragFinished();
//STRIP001
//STRIP001  if( pWrtShell->IsSelFrmMode() )
//STRIP001      pWrtShell->HideCrsr();
//STRIP001  else
//STRIP001      pWrtShell->ShowCrsr();
//STRIP001 //!! else if( DND_ACTION_NONE != nAction )
//STRIP001 //!!     pWrtShell->ShowCrsr();
//STRIP001 //!! else
//STRIP001 //!! {
//STRIP001 //!!     //Muss wohl sein weil gescrollt wurde und ?...?
//STRIP001 //!!     pWrtShell->StartAction();
//STRIP001 //!!     pWrtShell->EndAction();
//STRIP001 //!! }
//STRIP001
//STRIP001  ((SwViewOption *)pWrtShell->GetViewOptions())->SetIdle( bOldIdle );
//STRIP001 }


/*  */

//STRIP001 int SwTransferable::PrivatePaste( SwWrtShell& rShell )
//STRIP001 {
//STRIP001  // erst den SelectionType erfragen, dann Action-Klammerung !!!!
//STRIP001  // (sonst wird nicht in eine TabellenSelektion gepastet!!!)
//STRIP001  ASSERT( !rShell.ActionPend(), "Paste darf nie eine Actionklammerung haben" );
//STRIP001  const int nSelection = rShell.GetSelectionType();
//STRIP001
//STRIP001  SwTrnsfrActionAndUndo aAction( &rShell, (USHORT)UNDO_INSERT );
//STRIP001
//STRIP001  //Selektierten Inhalt loeschen, nicht bei Tabellen-Selektion und
//STRIP001  //Tabelle im Clipboard
//STRIP001  if( rShell.HasSelection() && !( nSelection & SwWrtShell::SEL_TBL_CELLS))
//STRIP001  {
//STRIP001      rShell.DelRight();
//STRIP001      // war ein Fly selektiert, so muss jetzt fuer eine gueltige
//STRIP001      // Cursor-Position gesorgt werden! (geparkter Cursor!)
//STRIP001      if( ( SwWrtShell::SEL_FRM | SwWrtShell::SEL_GRF |
//STRIP001          SwWrtShell::SEL_OLE | SwWrtShell::SEL_DRW |
//STRIP001          SwWrtShell::SEL_DRW_FORM ) & nSelection )
//STRIP001      {
//STRIP001          // den Cursor wieder positionieren
//STRIP001          Point aPt( rShell.GetCharRect().Pos() );
//STRIP001          rShell.SwCrsrShell::SetCrsr( aPt, TRUE );
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  BOOL bInWrd, bEndWrd, bSttWrd,
//STRIP001       bSmart = TRNSFR_DOCUMENT_WORD & eBufferType;
//STRIP001  if( bSmart )
//STRIP001  {
//STRIP001 // #108491# Why not for other Scripts? If TRNSFR_DOCUMENT_WORD is set, we have
//STRIP001 // a word in the buffer, word in this context means 'something with spaces at
//STRIP001 // beginning and end'. In this case we definitely want these spaces to be inserted
//STRIP001 // here.
//STRIP001 //      if( SCRIPTTYPE_LATIN != rShell.GetScriptType() )
//STRIP001 //          bSmart = FALSE;
//STRIP001 //      else
//STRIP001 //      {
//STRIP001          bInWrd = rShell.IsInWrd();
//STRIP001          bEndWrd = rShell.IsEndWrd();
//STRIP001          bSmart = bInWrd || bEndWrd;
//STRIP001          if( bSmart )
//STRIP001          {
//STRIP001              bSttWrd = rShell.IsSttWrd();
//STRIP001              if( bSmart && !bSttWrd && (bInWrd || bEndWrd) )
//STRIP001                  rShell.SwEditShell::Insert(' ');
//STRIP001          }
//STRIP001 //      }
//STRIP001  }
//STRIP001
//STRIP001  int nRet = rShell.Paste( pClpDocFac->GetDoc() );
//STRIP001
//STRIP001  // Wenn Smart Paste dann Leerzeichen einfuegen
//STRIP001  if( nRet && bSmart && (bInWrd || bSttWrd) )
//STRIP001      rShell.SwEditShell::Insert(' ');
//STRIP001
//STRIP001  return nRet;
//STRIP001 }

//STRIP001 int SwTransferable::PrivateDrop( SwWrtShell& rSh, const Point& rDragPt,
//STRIP001                              BOOL bMove, BOOL bIsXSelection )
//STRIP001 {
//STRIP001  int cWord    = 0;
//STRIP001  BOOL bInWrd  = FALSE;
//STRIP001  BOOL bEndWrd = FALSE;
//STRIP001  BOOL bSttWrd = FALSE;
//STRIP001  BOOL bSttPara= FALSE;
//STRIP001  BOOL bTblSel = FALSE;
//STRIP001  BOOL bFrmSel = FALSE;
//STRIP001
//STRIP001  SwWrtShell& rSrcSh = *GetShell();
//STRIP001
//STRIP001  rSh.UnSetVisCrsr();
//STRIP001
//STRIP001  if( TRNSFR_INETFLD == eBufferType )
//STRIP001  {
//STRIP001      if( rSh.GetFmtFromObj( rDragPt ) )
//STRIP001      {
//STRIP001          INetBookmark aTmp;
//STRIP001          if( (TRNSFR_INETFLD & eBufferType) && pBkmk )
//STRIP001              aTmp = *pBkmk;
//STRIP001
//STRIP001          // Zielgrafik selektieren
//STRIP001          if( rSh.SelectObj( rDragPt ) )
//STRIP001          {
//STRIP001              rSh.HideCrsr();
//STRIP001              rSh.EnterSelFrmMode( &rDragPt );
//STRIP001              bFrmDrag = TRUE;
//STRIP001          }
//STRIP001
//STRIP001          const int nSelection = rSh.GetSelectionType();
//STRIP001
//STRIP001          // Draw-Objekte erstmal noch nicht beruecksichtigen
//STRIP001          if( SwWrtShell::SEL_GRF & nSelection )
//STRIP001          {
//STRIP001              SfxItemSet aSet( rSh.GetAttrPool(), RES_URL, RES_URL );
//STRIP001              rSh.GetFlyFrmAttr( aSet );
//STRIP001              SwFmtURL aURL( (SwFmtURL&)aSet.Get( RES_URL ) );
//STRIP001              aURL.SetURL( aTmp.GetURL(), FALSE );
//STRIP001              aSet.Put( aURL );
//STRIP001              rSh.SetFlyFrmAttr( aSet );
//STRIP001              return 1;
//STRIP001          }
//STRIP001
//STRIP001          if( SwWrtShell::SEL_DRW & nSelection )
//STRIP001          {
//STRIP001              rSh.LeaveSelFrmMode();
//STRIP001              rSh.UnSelectFrm();
//STRIP001              rSh.ShowCrsr();
//STRIP001              bFrmDrag = FALSE;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if( &rSh != &rSrcSh && (SwWrtShell::SEL_GRF & rSh.GetSelectionType()) &&
//STRIP001      TRNSFR_GRAPHIC == eBufferType )
//STRIP001  {
//STRIP001      // ReRead auf die Grafik
//STRIP001      String sGrfNm, sFltNm;
//STRIP001      rSrcSh.GetGrfNms( &sGrfNm, &sFltNm );
//STRIP001      rSh.ReRead( sGrfNm, sFltNm, &rSrcSh.GetGraphic() );
//STRIP001      return 1;
//STRIP001  }
//STRIP001
//STRIP001  //Nicht in Selektionen oder selektierten Rahmen
//STRIP001  if( rSh.ChgCurrPam( rDragPt ) ||
//STRIP001      ( rSh.IsSelFrmMode() && rSh.IsInsideSelectedObj( rDragPt )) )
//STRIP001      return 0;
//STRIP001
//STRIP001  if( rSrcSh.IsTableMode() )
//STRIP001      bTblSel = TRUE;
//STRIP001  else if( rSrcSh.IsSelFrmMode() || rSrcSh.IsObjSelected() )
//STRIP001  {
//STRIP001      // keine positionsgeschuetzten Objecte verschieben!
//STRIP001      if( bMove && rSrcSh.IsSelObjProtected( FLYPROTECT_POS ) )
//STRIP001          return 0;
//STRIP001
//STRIP001      bFrmSel = TRUE;
//STRIP001  }
//STRIP001
//STRIP001  const int nSel = rSrcSh.GetSelectionType();
//STRIP001
//STRIP001  USHORT nUndoId = bMove ? UIUNDO_DRAG_AND_MOVE : UIUNDO_DRAG_AND_COPY;
//STRIP001  if( rSrcSh.GetDoc() != rSh.GetDoc() )
//STRIP001      rSrcSh.StartUndo( nUndoId );
//STRIP001  rSh.StartUndo( nUndoId );
//STRIP001
//STRIP001  rSh.StartAction();
//STRIP001  rSrcSh.StartAction();
//STRIP001
//STRIP001  if( &rSrcSh != &rSh )
//STRIP001  {
//STRIP001      rSh.EnterStdMode();
//STRIP001      rSh.SwCrsrShell::SetCrsr( rDragPt, TRUE );
//STRIP001      cWord = rSrcSh.IntelligentCut( nSel, FALSE );
//STRIP001  }
//STRIP001  else if( !bTblSel && !bFrmSel )
//STRIP001  {
//STRIP001      if( !rSh.IsAddMode() )
//STRIP001          rSh.SwCrsrShell::CreateCrsr();
//STRIP001      rSh.SwCrsrShell::SetCrsr( rDragPt, TRUE );
//STRIP001      rSh.GoPrevCrsr();
//STRIP001      cWord = rSh.IntelligentCut( rSh.GetSelectionType(), FALSE );
//STRIP001      rSh.GoNextCrsr();
//STRIP001  }
//STRIP001
//STRIP001  bInWrd  = rSh.IsInWrd();
//STRIP001  bEndWrd = rSh.IsEndWrd();
//STRIP001  bSttWrd = !bEndWrd && rSh.IsSttWrd();
//STRIP001  bSttPara= rSh.IsSttPara();
//STRIP001
//STRIP001  Point aSttPt( SwEditWin::GetDDStartPosX(), SwEditWin::GetDDStartPosY() );
//STRIP001
//STRIP001  //JP 05.03.96: INetFelder erstmal selektieren !
//STRIP001  if( TRNSFR_INETFLD == eBufferType )
//STRIP001  {
//STRIP001      if( &rSrcSh == &rSh )
//STRIP001      {
//STRIP001          rSh.GoPrevCrsr();
//STRIP001          rSh.SwCrsrShell::SetCrsr( aSttPt, TRUE );
//STRIP001          rSh.SelectTxtAttr( RES_TXTATR_INETFMT );
//STRIP001          if( rSh.ChgCurrPam( rDragPt ) )
//STRIP001          {
//STRIP001              // nicht in sich selbst kopieren/verschieben
//STRIP001              rSh.DestroyCrsr();
//STRIP001              rSh.EndUndo( nUndoId );
//STRIP001              rSh.EndAction();
//STRIP001              rSh.EndAction();
//STRIP001              return 0;
//STRIP001          }
//STRIP001          rSh.GoNextCrsr();
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          rSrcSh.SwCrsrShell::SetCrsr( aSttPt, TRUE );
//STRIP001          rSrcSh.SelectTxtAttr( RES_TXTATR_INETFMT );
//STRIP001      }
//STRIP001
//STRIP001      // ist am Einfuege Punkt ein URL-Attribut? Dann das ersetzen,
//STRIP001      // also einfach eine Selektion aufspannen?
//STRIP001      rSh.DelINetAttrWithText();
//STRIP001      bDDINetAttr = TRUE;
//STRIP001  }
//STRIP001
//STRIP001  if ( rSrcSh.IsSelFrmMode() )
//STRIP001  {
//STRIP001      //Hack: Spezialbehandlung austricksen
//STRIP001      aSttPt -= aSttPt - rSrcSh.GetObjRect().Pos();
//STRIP001  }
//STRIP001
//STRIP001  BOOL bRet = rSrcSh.SwFEShell::Copy( &rSh, aSttPt, rDragPt, bMove,
//STRIP001                                          !bIsXSelection );
//STRIP001
//STRIP001  if( !bIsXSelection )
//STRIP001  {
//STRIP001      rSrcSh.Push();
//STRIP001      if ( bRet && bMove && !bFrmSel )
//STRIP001      {
//STRIP001          if ( bTblSel )
//STRIP001             {
//STRIP001                 /* #109590# delete table contents not cells */
//STRIP001              rSrcSh.Delete();
//STRIP001             }
//STRIP001          else
//STRIP001          {
//STRIP001              //SmartCut, eines der Blank mitnehmen.
//STRIP001              rSh.SwCrsrShell::DestroyCrsr();
//STRIP001              if ( cWord == SwWrtShell::WORD_SPACE_BEFORE )
//STRIP001                  rSh.ExtendSelection( FALSE );
//STRIP001              else if ( cWord == SwWrtShell::WORD_SPACE_AFTER )
//STRIP001                  rSh.ExtendSelection();
//STRIP001              rSrcSh.DelRight();
//STRIP001          }
//STRIP001      }
//STRIP001      rSrcSh.KillPams();
//STRIP001      rSrcSh.Pop( FALSE );
//STRIP001
//STRIP001         /* #109590# after dragging a table selection inside one shell
//STRIP001             set cursor to the drop position. */
//STRIP001         if (bTblSel && &rSh == &rSrcSh)
//STRIP001         {
//STRIP001             rSrcSh.SwCrsrShell::SetCrsr(rDragPt);
//STRIP001             rSrcSh.GetSwCrsr()->SetMark();
//STRIP001         }
//STRIP001  }
//STRIP001
//STRIP001  if( bRet && !bTblSel && !bFrmSel )
//STRIP001  {
//STRIP001      if( (bInWrd || bEndWrd) &&
//STRIP001          (cWord == SwWrtShell::WORD_SPACE_AFTER ||
//STRIP001              cWord == SwWrtShell::WORD_SPACE_BEFORE) )
//STRIP001      {
//STRIP001          if ( bSttWrd || bInWrd )
//STRIP001              rSh.SwEditShell::Insert(' ', bIsXSelection);
//STRIP001          if ( !bSttWrd || (bInWrd && !bSttPara) )
//STRIP001          {
//STRIP001              rSh.SwapPam();
//STRIP001              if ( !bSttWrd )
//STRIP001                  rSh.SwEditShell::Insert(' ', bIsXSelection);
//STRIP001              rSh.SwapPam();
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      if( bIsXSelection )
//STRIP001      {
//STRIP001          if( &rSrcSh == &rSh && !rSh.IsAddMode() )
//STRIP001          {
//STRIP001              rSh.SwCrsrShell::DestroyCrsr();
//STRIP001              rSh.GoPrevCrsr();
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              rSh.SwapPam();
//STRIP001              rSh.SwCrsrShell::ClearMark();
//STRIP001          }
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          if( rSh.IsAddMode() )
//STRIP001              rSh.SwCrsrShell::CreateCrsr();
//STRIP001          else
//STRIP001          {
//STRIP001              // Selektionsmodus einschalten
//STRIP001              rSh.SttSelect();
//STRIP001              rSh.EndSelect();
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if( bRet && bMove && bFrmSel )
//STRIP001      rSrcSh.LeaveSelFrmMode();
//STRIP001
//STRIP001  if( rSrcSh.GetDoc() != rSh.GetDoc() )
//STRIP001      rSrcSh.EndUndo( nUndoId );
//STRIP001  rSh.EndUndo( nUndoId );
//STRIP001
//STRIP001      // Shell in den richtigen Status versetzen
//STRIP001  if( &rSrcSh != &rSh && ( rSh.IsFrmSelected() || rSh.IsObjSelected() ))
//STRIP001      rSh.EnterSelFrmMode();
//STRIP001
//STRIP001  rSrcSh.EndAction();
//STRIP001  rSh.EndAction();
//STRIP001  return 1;
//STRIP001 }

// Interfaces for Selection
//STRIP001 void SwTransferable::CreateSelection( SwWrtShell& rSh,
//STRIP001                                    const ViewShell * _pCreatorView )
//STRIP001 {
//STRIP001  SwModule *pMod = SW_MOD();
//STRIP001  SwTransferable* pNew = new SwTransferable( rSh );
//STRIP001
//STRIP001  /* #96392#*/
//STRIP001      pNew->pCreatorView = _pCreatorView;
//STRIP001
//STRIP001  ::com::sun::star::uno::Reference<
//STRIP001          ::com::sun::star::datatransfer::XTransferable > xRef( pNew );
//STRIP001  pMod->pXSelection = pNew;
//STRIP001  pNew->CopyToSelection( rSh.GetWin() );
//STRIP001 }

/*N*/ void SwTransferable::ClearSelection( SwWrtShell& rSh,
/*N*/                                    const ViewShell * _pCreatorView)
/*N*/ {
/*N*/   SwModule *pMod = SW_MOD();
/*N*/     if( pMod->pXSelection &&
/*N*/         ((!pMod->pXSelection->pWrtShell) || (pMod->pXSelection->pWrtShell == &rSh)) &&
/*N*/       /* #96392# */
/*N*/         (!_pCreatorView || (pMod->pXSelection->pCreatorView == _pCreatorView)) )
/*N*/   {
/*N*/       TransferableHelper::ClearSelection( rSh.GetWin() );
/*N*/   }
/*N*/ }
/* -----------------3/31/2003 11:46AM----------------

 --------------------------------------------------*/
/*N*/ const Sequence< sal_Int8 >& SwTransferable::getUnoTunnelId()
/*N*/ {
/*N*/     static Sequence< sal_Int8 > aSeq;
/*N*/     if( !aSeq.getLength() )
/*N*/     {
/*N*/         static osl::Mutex           aCreateMutex;
/*N*/         osl::Guard< osl::Mutex >    aGuard( aCreateMutex );
/*N*/         aSeq.realloc( 16 );
/*N*/         rtl_createUuid( reinterpret_cast< sal_uInt8* >( aSeq.getArray() ), 0, sal_True );
/*N*/     }
/*N*/     return aSeq;
/*N*/ }
/* -----------------3/31/2003 11:46AM----------------

 --------------------------------------------------*/
//STRIP001 sal_Int64 SwTransferable::getSomething( const Sequence< sal_Int8 >& rId ) throw( RuntimeException )
//STRIP001 {
//STRIP001     sal_Int64 nRet;
//STRIP001     if( ( rId.getLength() == 16 ) &&
//STRIP001         ( 0 == rtl_compareMemory( getUnoTunnelId().getConstArray(), rId.getConstArray(), 16 ) ) )
//STRIP001     {
//STRIP001         nRet = (sal_Int64) this;
//STRIP001     }
//STRIP001     else
//STRIP001         nRet = TransferableHelper::getSomething(rId);
//STRIP001     return nRet;
//STRIP001 }

/*  */

//STRIP001 #ifdef DDE_AVAILABLE

// -----------------------------------------------------------------------

//STRIP001 SwTrnsfrDdeLink::SwTrnsfrDdeLink( SwTransferable& rTrans, SwWrtShell& rSh )
//STRIP001  : rTrnsfr( rTrans ), pDocShell( 0 ),
//STRIP001  bDelBookmrk( FALSE ), bInDisconnect( FALSE )
//STRIP001 {
//STRIP001  // hier kommen wir nur bei Tabellen- oder Text-Selection an
//STRIP001  const int nSelection = rSh.GetSelectionType();
//STRIP001  if( SwWrtShell::SEL_TBL_CELLS & nSelection )
//STRIP001  {
//STRIP001      SwFrmFmt* pFmt = rSh.GetTableFmt();
//STRIP001      if( pFmt )
//STRIP001          sName = pFmt->GetName();
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      // wir erzeugen uns eine temp. Bookmark (ohne UNDO!)
//STRIP001      BOOL bUndo = rSh.DoesUndo();
//STRIP001      rSh.DoUndo( FALSE );
//STRIP001      BOOL bIsModified = rSh.IsModified();
//STRIP001
//STRIP001      sName.AssignAscii( RTL_CONSTASCII_STRINGPARAM( "DDE_LINK" ));
//STRIP001      rSh.MakeUniqueBookmarkName( sName );
//STRIP001
//STRIP001      //Ok, den eindeutigen Namen haben wir
//STRIP001      if( !rSh.SetBookmark( KeyCode(), sName, aEmptyStr ) )
//STRIP001          sName.Erase();
//STRIP001      else
//STRIP001      {
//STRIP001          USHORT nBookPos = rSh.FindBookmark( sName );
//STRIP001          if( USHRT_MAX != nBookPos )
//STRIP001          {
//STRIP001              SwBookmark& rBookMk = rSh.GetBookmark( nBookPos );
//STRIP001              rBookMk.SetType( DDE_BOOKMARK );
//STRIP001          }
//STRIP001          bDelBookmrk = TRUE;
//STRIP001          if( !bIsModified )
//STRIP001              rSh.ResetModified();
//STRIP001      }
//STRIP001
//STRIP001      rSh.DoUndo( bUndo );
//STRIP001  }
//STRIP001
//STRIP001  if( sName.Len() &&
//STRIP001      0 != ( pDocShell = rSh.GetDoc()->GetDocShell() ) )
//STRIP001  {
//STRIP001      // dann erzeugen wir uns mal unseren "Server" und connecten uns
//STRIP001      // zu diesem
//STRIP001      refObj = pDocShell->DdeCreateLinkSource( sName );
//STRIP001      if( refObj.Is() )
//STRIP001      {
//STRIP001          refObj->AddConnectAdvise( this );
//STRIP001          refObj->AddDataAdvise( this,
//STRIP001 //                           SotExchange::GetFormatMimeType( FORMAT_RTF ),
//STRIP001                          aEmptyStr,
//STRIP001                          ADVISEMODE_NODATA | ADVISEMODE_ONLYONCE );
//STRIP001          nOldTimeOut = refObj->GetUpdateTimeout();
//STRIP001          refObj->SetUpdateTimeout( 0 );
//STRIP001      }
//STRIP001  }
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 SwTrnsfrDdeLink::~SwTrnsfrDdeLink()
//STRIP001 {
//STRIP001  if( refObj.Is() )
//STRIP001      Disconnect();
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 void SwTrnsfrDdeLink::DataChanged( const String& ,
//STRIP001                                  const ::com::sun::star::uno::Any& )
//STRIP001 {
//STRIP001  // tja das wars dann mit dem Link
//STRIP001  if( !bInDisconnect )
//STRIP001  {
//STRIP001      if( FindDocShell() && pDocShell->GetView() )
//STRIP001          rTrnsfr.RemoveDDELinkFormat( pDocShell->GetView()->GetEditWin() );
//STRIP001      Disconnect( FALSE );
//STRIP001  }
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 BOOL SwTrnsfrDdeLink::WriteData( SvStream& rStrm )
//STRIP001 {
//STRIP001  if( !refObj.Is() || !FindDocShell() )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  const ByteString aAppNm( GetpApp()->GetAppName(),  DDE_TXT_ENCODING );
//STRIP001  const ByteString aTopic( pDocShell->GetTitle( SFX_TITLE_FULLNAME ),
//STRIP001                          DDE_TXT_ENCODING );
//STRIP001  const ByteString aName( sName, DDE_TXT_ENCODING );
//STRIP001
//STRIP001  sal_Char* pMem = new char[ aAppNm.Len() + aTopic.Len() + aName.Len() + 4 ];
//STRIP001
//STRIP001  xub_StrLen nLen = aAppNm.Len();
//STRIP001  memcpy( pMem, aAppNm.GetBuffer(), nLen );
//STRIP001  pMem[ nLen++ ] = 0;
//STRIP001  memcpy( pMem + nLen, aTopic.GetBuffer(), aTopic.Len() );
//STRIP001  nLen += aTopic.Len();
//STRIP001  pMem[ nLen++ ] = 0;
//STRIP001  memcpy( pMem + nLen, aName.GetBuffer(), aName.Len() );
//STRIP001  nLen += aName.Len();
//STRIP001  pMem[ nLen++ ] = 0;
//STRIP001  pMem[ nLen++ ] = 0;
//STRIP001
//STRIP001  rStrm.Write( pMem, nLen );
//STRIP001     delete[] pMem;
//STRIP001
//STRIP001  if( bDelBookmrk )
//STRIP001  {
//STRIP001      // er wird das erstemal abgeholt, also ins Undo mitaufnehmen
//STRIP001      // aber wie??
//STRIP001  }
//STRIP001
//STRIP001  SwDoc* pDoc = pDocShell->GetDoc();
//STRIP001  USHORT nBookPos = pDoc->FindBookmark( sName );
//STRIP001  if( USHRT_MAX != nBookPos )
//STRIP001  {
//STRIP001      SwBookmark* pBookMk = pDoc->GetBookmarks()[ nBookPos ];
//STRIP001      pBookMk->SetType( BOOKMARK );
//STRIP001      pDoc->SetModified();
//STRIP001  }
//STRIP001
//STRIP001  bDelBookmrk = FALSE;
//STRIP001  return TRUE;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 void SwTrnsfrDdeLink::Disconnect( BOOL bRemoveDataAdvise )
//STRIP001 {
//STRIP001  //JP 29.01.96 Bug 24432:
//STRIP001  //      kein DataChanged mehr entgegen nehmen, wenn man
//STRIP001  //      sich schon im Disconnet befindet!
//STRIP001  //      (DTOR vom Bookmark verschickt einen DataChanged!)
//STRIP001  BOOL bOldDisconnect = bInDisconnect;
//STRIP001  bInDisconnect = TRUE;
//STRIP001
//STRIP001  // den nicht verwendeten Bookmark wieder zerstoeren (ohne Undo!)?
//STRIP001  if( bDelBookmrk && refObj.Is() && FindDocShell() )
//STRIP001  {
//STRIP001      SwDoc* pDoc = pDocShell->GetDoc();
//STRIP001      BOOL bUndo = pDoc->DoesUndo();
//STRIP001      pDoc->DoUndo( FALSE );
//STRIP001
//STRIP001      BOOL bIsModified = pDoc->IsModified();
//STRIP001
//STRIP001      pDoc->DelBookmark( sName );
//STRIP001
//STRIP001      if( !bIsModified )
//STRIP001          pDoc->ResetModified();
//STRIP001
//STRIP001      pDoc->DoUndo( bUndo );
//STRIP001      bDelBookmrk = FALSE;
//STRIP001  }
//STRIP001
//STRIP001  if( refObj.Is() )
//STRIP001  {
//STRIP001      refObj->SetUpdateTimeout( nOldTimeOut );
//STRIP001      refObj->RemoveConnectAdvise( this );
//STRIP001      if( bRemoveDataAdvise )
//STRIP001          // in einem DataChanged darf das SelectionObject NIE geloescht
//STRIP001          // werden; wird schon von der Basisklasse erledigt
//STRIP001          // (ADVISEMODE_ONLYONCE!!!!)
//STRIP001          // Im normalen Disconnet aber schon!
//STRIP001          refObj->RemoveAllDataAdvise( this );
//STRIP001      refObj.Clear();
//STRIP001  }
//STRIP001  bInDisconnect = bOldDisconnect;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 BOOL SwTrnsfrDdeLink::FindDocShell()
//STRIP001 {
//STRIP001  TypeId aType( TYPE( SwDocShell ) );
//STRIP001  SfxObjectShell* pTmpSh = SfxObjectShell::GetFirst( &aType );
//STRIP001  while( pTmpSh )
//STRIP001  {
//STRIP001      if( pTmpSh == pDocShell )       // die wollen wir haben
//STRIP001      {
//STRIP001          if( pDocShell->GetDoc() )
//STRIP001              return TRUE;
//STRIP001          break;      // das Doc ist nicht mehr vorhanden, also raus!
//STRIP001      }
//STRIP001      pTmpSh = SfxObjectShell::GetNext( *pTmpSh, &aType );
//STRIP001  }
//STRIP001
//STRIP001  pDocShell = 0;
//STRIP001  return FALSE;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 void SwTrnsfrDdeLink::Closed()
//STRIP001 {
//STRIP001  if( !bInDisconnect && refObj.Is() )
//STRIP001  {
//STRIP001      refObj->RemoveAllDataAdvise( this );
//STRIP001      refObj->RemoveConnectAdvise( this );
//STRIP001      refObj.Clear();
//STRIP001  }
//STRIP001 }

//STRIP001 #endif



}
