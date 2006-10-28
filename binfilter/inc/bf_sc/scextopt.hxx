/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: scextopt.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 02:41:43 $
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

#ifndef _SCEXTOPT_HXX
#define _SCEXTOPT_HXX


#ifndef SC_SCGLOB_HXX
#include "global.hxx"
#endif
namespace binfilter {




// ACHTUNG1: einzelne Einstellungen sollten stimmen
//              -> Absicherung nur ueber Assertions
// ACHTUNG2: Plausibilitaet der Einstellungen untereinander ist nicht
//              gewaehrleistet

struct ScExtTabOptions
{
    // Split -Info
    UINT16                      nTabNum;
    UINT16                      nSplitX;            // horiz. pos. in twips, 0 = no split
    UINT16                      nSplitY;            // vert. pos. ~
    UINT16                      nLeftCol;           // leftmost column visible
    UINT16                      nTopRow;            // topmost row visible
    UINT16                      nLeftSplitCol;      // leftmost column after horizontal split
    UINT16                      nTopSplitRow;       // topmost row after vertical split
    UINT16                      nActPane;           // 0: br, 1: tr, 2: bl, 3: tl

    ScRange                     aLastSel;           // last selection
    BOOL                        bValidSel;
    ScRange                     aDim;               // original Excel size
    BOOL                        bValidDim;

    BOOL                        bSelected;
    BOOL                        bFrozen;            // = TRUE -> nSplitX / nSplitY contain
                                                    // count of visible columns/rows

    inline                      ScExtTabOptions( void );
    inline                      ScExtTabOptions( const ScExtTabOptions& rCpy );
    inline void                 operator =( const ScExtTabOptions& rCpy );

    void                        SetSelection( const ScRange& rSelection );
    void                        SetDimension( const ScRange& rDim );
};




class CodenameList : protected List
{
    // Code: colrowst.cxx
private:
protected:
public:
    inline                      CodenameList( void );
                                CodenameList( const CodenameList& );
    virtual                     ~CodenameList();

    inline void                 Append( const String& );
};




class ScExtDocOptions
{
// Code: colrowst.cxx
private:
    // Window -Info
    ScExtTabOptions**       ppExtTabOpts;

    String*                 pCodenameWB;
    CodenameList*           pCodenames;

    BOOL                    bChanged;       // for import: copy data only first time to doc
    bool                    bWinProtection;  // Excel Workbook Windows protection flag

public:
    UINT32                  nLinkCnt;       // Zaehlt die Rekursionstufe beim Laden
                                            //  von externen Dokumenten
    UINT16                  nActTab;        // aktuelle Tabelle
    ScRange*                pOleSize;       // visible range if embedded
    UINT16                  nSelTabs;       // count of selected sheets
    Color*                  pGridCol;       // Farbe Grid und Row-/Col-Heading
    UINT16                  nZoom;          // in %
    // Cursor
    UINT16                  nCurCol;        // aktuelle Cursor-Position
    UINT16                  nCurRow;
    // -------------------------------------------------------------------
                            ScExtDocOptions( void );
                            ~ScExtDocOptions();

    inline const ScExtTabOptions*   GetExtTabOptions( const UINT16 nTabNum ) const;
    inline ScExtTabOptions* GetExtTabOptions( const UINT16 nTabNum );
    inline const String*    GetCodename( void ) const;      // for Workbook globals
    inline CodenameList*    GetCodenames( void );           // for tables

    inline void             SetWinProtection(bool bImportWinProtection) {bWinProtection = bImportWinProtection; }
    inline bool             IsWinProtected()         { return bWinProtection; }
};




inline CodenameList::CodenameList( void )
{
}


inline void CodenameList::Append( const String& r )
{
    List::Insert( new String( r ), LIST_APPEND );
}










inline ScExtTabOptions::ScExtTabOptions( void )
{
    nTabNum = nSplitX = nSplitY = nLeftCol = nTopRow = nLeftSplitCol = nTopSplitRow = 0;
    nActPane = 3;
    bSelected = bFrozen = bValidSel = bValidDim = FALSE;
}


inline ScExtTabOptions::ScExtTabOptions( const ScExtTabOptions& rCpy )
{
    nTabNum = rCpy.nTabNum;
    nSplitX = rCpy.nSplitX;
    nSplitY = rCpy.nSplitY;
    nLeftCol = rCpy.nLeftCol;
    nTopRow = rCpy.nTopRow;
    nLeftSplitCol = rCpy.nLeftSplitCol;
    nTopSplitRow = rCpy.nTopSplitRow;
    nActPane = rCpy.nActPane;
    aLastSel = rCpy.aLastSel;
    aDim = rCpy.aDim;
    bSelected = rCpy.bSelected;
    bFrozen = rCpy.bFrozen;
    bValidSel = rCpy.bValidSel;
    bValidDim = rCpy.bValidDim;
}


inline void ScExtTabOptions::operator =( const ScExtTabOptions& rCpy )
{
    nTabNum = rCpy.nTabNum;
    nSplitX = rCpy.nSplitX;
    nSplitY = rCpy.nSplitY;
    nLeftCol = rCpy.nLeftCol;
    nTopRow = rCpy.nTopRow;
    nLeftSplitCol = rCpy.nLeftSplitCol;
    nTopSplitRow = rCpy.nTopSplitRow;
    nActPane = rCpy.nActPane;
    aLastSel = rCpy.aLastSel;
    aDim = rCpy.aDim;
    bSelected = rCpy.bSelected;
    bFrozen = rCpy.bFrozen;
    bValidSel = rCpy.bValidSel;
    bValidDim = rCpy.bValidDim;
}




inline const ScExtTabOptions* ScExtDocOptions::GetExtTabOptions( const UINT16 nTab ) const
{
    return (nTab <= MAXTAB) ? ppExtTabOpts[ nTab ] : NULL;
}


inline ScExtTabOptions* ScExtDocOptions::GetExtTabOptions( const UINT16 nTab )
{
    return (nTab <= MAXTAB) ? ppExtTabOpts[ nTab ] : NULL;
}


inline const String* ScExtDocOptions::GetCodename( void ) const
{
    return pCodenameWB;
}


inline CodenameList* ScExtDocOptions::GetCodenames( void )
{
    return pCodenames;
}


} //namespace binfilter
#endif

