/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_swdtflvr.cxx,v $
 *
 *  $Revision: 1.13 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 13:09:58 $
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

#ifdef _MSC_VER
#pragma hdrstop
#endif

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

/*N*/ static inline Reference < XTransferable > * lcl_getTransferPointer ( Reference < XTransferable > &xRef )
/*N*/ {
/*N*/   return &xRef;
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

/*  */


// -----------------------------------------------------------------------


// -----------------------------------------------------------------------


// -----------------------------------------------------------------------


// -----------------------------------------------------------------------


// -----------------------------------------------------------------------


// -----------------------------------------------------------------------


// -----------------------------------------------------------------------





}
