/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: txtfld.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 16:40:21 $
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
#ifndef _TXTFLD_HXX
#define _TXTFLD_HXX

#ifndef _TXATBASE_HXX //autogen
#include <txatbase.hxx>
#endif
// auto strip #ifndef _STRING_HXX //autogen
// auto strip #include <tools/string.hxx>
// auto strip #endif
namespace binfilter {

class SwTxtNode;

// ATT_FLD ***********************************

class SwTxtFld : public SwTxtAttr
{
    String     aExpand;
    SwTxtNode  *pMyTxtNd;
public:
    SwTxtFld( const SwFmtFld& rAttr, xub_StrLen nStart );
    ~SwTxtFld();

//STRIP001  void CopyFld( SwTxtFld *pDest ) const;
    void Expand();
    inline void ExpandAlways();

    // erfrage und setze den TxtNode Pointer
    const SwTxtNode* GetpTxtNode() const { return pMyTxtNd; }
    inline const SwTxtNode& GetTxtNode() const;
    void ChgTxtNode( const SwTxtNode* pNew ) { pMyTxtNd = (SwTxtNode*)pNew; }
    // enable notification that field content has changed and needs reformatting
    void NotifyContentChange(SwFmtFld& rFmtFld);
};

inline const SwTxtNode& SwTxtFld::GetTxtNode() const
{
    ASSERT( pMyTxtNd, "SwTxtFld:: wo ist mein TextNode?" );
    return *pMyTxtNd;
}

inline void SwTxtFld::ExpandAlways()
{
    aExpand += ' ';
    Expand();
}

} //namespace binfilter
#endif

