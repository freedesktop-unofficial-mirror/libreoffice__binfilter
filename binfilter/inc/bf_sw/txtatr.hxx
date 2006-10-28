/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: txtatr.hxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 04:59:31 $
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
#ifndef _TXTATR_HXX
#define _TXTATR_HXX

#ifndef _TXATBASE_HXX
#include <txatbase.hxx>     // SwTxtAttr/SwTxtAttrEnd
#endif
#ifndef _CALBCK_HXX
#include <calbck.hxx>
#endif
namespace binfilter {

class SwTxtNode;    // fuer SwTxtFld
class SvxFont;
class SwCharSetCol;
class SwCharFmt;
class SvxTwoLinesItem;

// ATT_CHARFMT *********************************************

class SwTxtCharFmt : public SwTxtAttrEnd
{
    SwTxtNode* pMyTxtNd;
    BOOL bPrevNoHyph    : 1;
    BOOL bPrevBlink     : 1;
    BOOL bPrevURL       : 1;
    BOOL bColor         : 1;

public:
    SwTxtCharFmt( const SwFmtCharFmt& rAttr, xub_StrLen nStart, xub_StrLen nEnd );
    ~SwTxtCharFmt( );

    // werden vom SwFmtCharFmt hierher weitergeleitet
    virtual void Modify( SfxPoolItem*, SfxPoolItem* );    // SwClient
    virtual BOOL GetInfo( SfxPoolItem& rInfo ) const;

    // erfrage und setze den TxtNode Pointer
    inline const SwTxtNode& GetTxtNode() const;
    void ChgTxtNode( const SwTxtNode* pNew ) { pMyTxtNd = (SwTxtNode*)pNew; }

};

// ATT_HARDBLANK ******************************


// ATT_XNLCONTAINERITEM ******************************


// ******************************

class SwTxtRuby : public SwTxtAttrEnd, public SwClient
{

public:
    SwTxtRuby( const SwFmtRuby& rAttr, xub_StrLen nStart, xub_StrLen nEnd ): SwTxtAttrEnd( (SfxPoolItem &)rAttr, nStart, nEnd ){DBG_BF_ASSERT(0, "STRIP");} ;//STRIP001     SwTxtRuby( const SwFmtRuby& rAttr, xub_StrLen nStart, xub_StrLen nEnd );

};

// ******************************


// --------------- Inline Implementierungen ------------------------

inline const SwTxtNode& SwTxtCharFmt::GetTxtNode() const
{
    ASSERT( pMyTxtNd, "SwTxtCharFmt:: wo ist mein TextNode?" );
    return *pMyTxtNd;
}


} //namespace binfilter
#endif
