/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_swdtflvr.cxx,v $
 *
 *  $Revision: 1.9 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 00:09:11 $
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

#ifdef PRECOMPILED
#endif

#pragma hdrstop

#ifndef _PASTEDLG_HXX
#include <so3/pastedlg.hxx>
#endif
#ifndef _SVX_CLIPFMTITEM_HXX
#include <bf_svx/clipfmtitem.hxx>
#endif
#ifndef _SVX_PAPERINF_HXX
#include <bf_svx/paperinf.hxx>
#endif
#ifndef _SVX_FMVIEW_HXX
#include <bf_svx/fmview.hxx>
#endif


#ifndef _SWDTFLVR_HXX
#include <swdtflvr.hxx>
#endif

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _PAGEDESC_HXX
#include <pagedesc.hxx>
#endif
#ifndef _WRTSH_HXX
#include <wrtsh.hxx>
#endif
#ifndef _SWMODULE_HXX
#include <swmodule.hxx>
#endif
#ifndef _VIEW_HXX
#include <view.hxx>
#endif
#ifndef _WDOCSH_HXX
#include <wdocsh.hxx>
#endif

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

// #108584#

// #108584#

// #108584#

// #108584#

// #109590#
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


#endif

// helper class for Action and Undo enclosing


// -----------------------------------------------------------------------


// -----------------------------------------------------------------------


// -----------------------------------------------------------------------


// -----------------------------------------------------------------------


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


// -----------------------------------------------------------------------


// -----------------------------------------------------------------------

    // we can only fullfil the request if
    // 1) we have data for this format
    // 2) we have either a clipboard document (pClpDocFac), or
    //    we have a SwWrtShell (so we can generate a new clipboard document)

// -----------------------------------------------------------------------


// -----------------------------------------------------------------------


// -----------------------------------------------------------------------


// -----------------------------------------------------------------------


// -----------------------------------------------------------------------


// -----------------------------------------------------------------------


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


// -----------------------------------------------------------------------


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
/*N*/   }
/*N*/   else
/*N*/       eOType = rSh.GetObjCntTypeOfSelection();
/*N*/
/*N*/   switch( eOType )
/*N*/   {
/*N*/   case OBJCNT_GRF:
/*N*/       {
/*?*/           DBG_BF_ASSERT(0, "STRIP"); //STRIP001 BOOL bIMap, bLink;
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


// -----------------------------------------------------------------------


// -----------------------------------------------------------------------


// -----------------------------------------------------------------------



// -----------------------------------------------------------------------


// -----------------------------------------------------------------------


// -----------------------------------------------------------------------


// -----------------------------------------------------------------------


// -----------------------------------------------------------------------


// -----------------------------------------------------------------------


// -----------------------------------------------------------------------


// -----------------------------------------------------------------------


// -----------------------------------------------------------------------


// -----------------------------------------------------------------------


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





/*  */



// Interfaces for Selection

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

/*  */


// -----------------------------------------------------------------------


// -----------------------------------------------------------------------


// -----------------------------------------------------------------------


// -----------------------------------------------------------------------


// -----------------------------------------------------------------------


// -----------------------------------------------------------------------


// -----------------------------------------------------------------------





}
