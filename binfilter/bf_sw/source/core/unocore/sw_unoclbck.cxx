/*************************************************************************
 *
 *  $RCSfile: sw_unoclbck.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 18:08:44 $
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

#pragma hdrstop

// auto strip #ifndef _HINTIDS_HXX
// auto strip #include <hintids.hxx>
// auto strip #endif

// auto strip #ifndef _TOOLS_DEBUG_HXX
// auto strip #include <tools/debug.hxx>
// auto strip #endif

// auto strip #ifndef _SWTYPES_HXX
// auto strip #include <swtypes.hxx>
// auto strip #endif

#ifndef _ERRHDL_HXX
#include <errhdl.hxx>
#endif

// auto strip #ifndef _UNOOBJ_HXX
// auto strip #include <unoobj.hxx>
// auto strip #endif
#ifndef _UNOIDX_HXX
#include <unoidx.hxx>
#endif
// auto strip #ifndef _TOX_HXX
// auto strip #include <tox.hxx>
// auto strip #endif
#ifndef _UNOCLBCK_HXX
#include <unoclbck.hxx>
#endif
// auto strip #ifndef _TXTFTN_HXX
// auto strip #include <txtftn.hxx>
// auto strip #endif
// auto strip #ifndef _FMTFTN_HXX
// auto strip #include <fmtftn.hxx>
// auto strip #endif

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

#ifndef _DOC_HXX
#include <doc.hxx>
#endif
// auto strip #ifndef _FMTRFMRK_HXX
// auto strip #include <fmtrfmrk.hxx>
// auto strip #endif
// auto strip #ifndef _TXTRFMRK_HXX
// auto strip #include <txtrfmrk.hxx>
// auto strip #endif
namespace binfilter {

/* -----------------------------06.01.00 13:51--------------------------------

 ---------------------------------------------------------------------------*/
SwUnoCallBack::SwUnoCallBack(SwModify *pToRegisterIn)   :
    SwModify(pToRegisterIn)
{
}
/* -----------------------------06.01.00 13:51--------------------------------

 ---------------------------------------------------------------------------*/
SwUnoCallBack::~SwUnoCallBack()
{
}
/* -----------------------------01.09.00 12:03--------------------------------

 ---------------------------------------------------------------------------*/
SwXReferenceMark* SwUnoCallBack::GetRefMark(const SwFmtRefMark& rMark)
{
    SwClientIter aIter( *this );
    SwXReferenceMark* pxRefMark = (SwXReferenceMark*)aIter.First( TYPE( SwXReferenceMark ));
    while(pxRefMark)
    {
        SwDoc* pDoc = pxRefMark->GetDoc();
        if(pDoc)
        {
            const SwFmtRefMark* pFmt = pDoc->GetRefMark(pxRefMark->GetMarkName());
            if(pFmt == &rMark)
                return pxRefMark;
        }
        pxRefMark = (SwXReferenceMark*)aIter.Next( );
    }
    return 0;
}
/* -----------------------------05.09.00 12:38--------------------------------

 ---------------------------------------------------------------------------*/
SwXFootnote* SwUnoCallBack::GetFootnote(const SwFmtFtn& rMark)
{
    SwClientIter aIter( *this );
    SwXFootnote* pxFootnote = (SwXFootnote*)aIter.First( TYPE( SwXFootnote ));
    while(pxFootnote)
    {
        SwDoc* pDoc = pxFootnote->GetDoc();
        if(pDoc)
        {
            const SwFmtFtn* pFtn = pxFootnote->FindFmt();
            if(pFtn == &rMark)
                return pxFootnote;
        }
        pxFootnote = (SwXFootnote*)aIter.Next( );
    }
    return 0;
}

/* -----------------------------27.11.00 17:15--------------------------------

 ---------------------------------------------------------------------------*/
SwXDocumentIndexMark* SwUnoCallBack::GetTOXMark(const SwTOXMark& rMark)
{
    SwClientIter aIter( *this );
    SwXDocumentIndexMark* pxIndexMark = (SwXDocumentIndexMark*)aIter.First( TYPE( SwXDocumentIndexMark ));
    while(pxIndexMark)
    {
        const SwTOXMark* pMark = pxIndexMark->GetTOXMark();
        if(pMark == &rMark)
            return pxIndexMark;

        pxIndexMark = (SwXDocumentIndexMark*)aIter.Next( );
    }
    return 0;
}

}
