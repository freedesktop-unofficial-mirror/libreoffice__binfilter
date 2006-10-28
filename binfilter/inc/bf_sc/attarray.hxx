/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: attarray.hxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 02:27:22 $
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

#ifndef SC_ATRARR_HXX
#define SC_ATRARR_HXX


#ifndef SC_SCATTR_HXX
#include "attrib.hxx"
#endif
class Rectangle;
class SfxItemPoolCache;
class SfxStyleSheetBase;
namespace binfilter {

class ScDocument;
class ScMarkArray;
class ScPatternAttr;
class ScStyleSheet;

class SvxBorderLine;
class SvxBoxItem;
class SvxBoxInfoItem;

#define SC_LINE_EMPTY           0
#define SC_LINE_SET             1
#define SC_LINE_DONTCARE        2

#define SC_ATTRARRAY_DELTA      4

struct ScLineFlags
{
    BYTE    nLeft;
    BYTE    nRight;
    BYTE    nTop;
    BYTE    nBottom;
    BYTE    nHori;
    BYTE    nVert;

    ScLineFlags() : nLeft(SC_LINE_EMPTY),nRight(SC_LINE_EMPTY),nTop(SC_LINE_EMPTY),
                    nBottom(SC_LINE_EMPTY),nHori(SC_LINE_EMPTY),nVert(SC_LINE_EMPTY) {}
};

struct ScAttrEntry
{
    USHORT                  nRow;
    const ScPatternAttr*    pPattern;
};


class ScAttrArray
{
private:
    USHORT          nCol;
    USHORT          nTab;
    ScDocument*     pDocument;

    USHORT          nCount;
    USHORT          nLimit;
    ScAttrEntry*    pData;

friend class ScDocument;                // fuer FillInfo
friend class ScDocumentIterator;
friend class ScAttrIterator;
friend void lcl_IterGetNumberFormat( ULONG& nFormat,
        const ScAttrArray*& rpArr, USHORT& nAttrEndRow,
        const ScAttrArray* pNewArr, USHORT nRow, ScDocument* pDoc );


public:
            ScAttrArray( USHORT nNewCol, USHORT nNewTab, ScDocument* pDoc );
            ~ScAttrArray();

    void    SetTab(USHORT nNewTab)  { nTab = nNewTab; }
    void    SetCol(USHORT nNewCol)  { nCol = nNewCol; }

    void    TestData() const;
    void    Reset( const ScPatternAttr* pPattern, BOOL bAlloc = TRUE );
    BOOL    Concat(USHORT nPos);

    const ScPatternAttr* GetPattern( USHORT nRow ) const;
    void    MergePatternArea( USHORT nStartRow, USHORT nEndRow, SfxItemSet** ppSet, BOOL bDeep ) const;


    void    SetPattern( USHORT nRow, const ScPatternAttr* pPattern, BOOL bPutToPool = FALSE );
    void    SetPatternArea( USHORT nStartRow, USHORT nEndRow, const ScPatternAttr* pPattern, BOOL bPutToPool = FALSE);
    void    ApplyStyleArea( USHORT nStartRow, USHORT nEndRow, ScStyleSheet* pStyle );
    void    ApplyCacheArea( USHORT nStartRow, USHORT nEndRow, SfxItemPoolCache* pCache );

/*N*/   void    ClearItems( USHORT nStartRow, USHORT nEndRow, const USHORT* pWhich );



    BOOL    ApplyFlags( USHORT nStartRow, USHORT nEndRow, INT16 nFlags );
/*N*/   BOOL    RemoveFlags( USHORT nStartRow, USHORT nEndRow, INT16 nFlags );

    BOOL    Search( USHORT nRow, short& nIndex ) const;

    BOOL    HasAttrib( USHORT nRow1, USHORT nRow2, USHORT nMask ) const;
    BOOL    ExtendMerge( USHORT nThisCol, USHORT nStartRow, USHORT nEndRow,
                                USHORT& rPaintCol, USHORT& rPaintRow,
                                BOOL bRefresh, BOOL bAttrs );
    BOOL    RemoveAreaMerge( USHORT nStartRow, USHORT nEndRow );

    void    FindStyleSheet( const SfxStyleSheetBase* pStyleSheet, BOOL* pUsed, BOOL bReset );
    BOOL    IsStyleSheetUsed( const ScStyleSheet& rStyle, BOOL bGatherAllStyles ) const;

    void    DeleteAreaSafe(USHORT nStartRow, USHORT nEndRow);

    BOOL    IsEmpty() const;


    BOOL    HasVisibleAttr( USHORT& rFirstRow, USHORT& rLastRow, BOOL bSkipFirst ) const;
    BOOL    IsVisibleEqual( const ScAttrArray& rOther,
                            USHORT nStartRow, USHORT nEndRow ) const;
    BOOL    IsAllEqual( const ScAttrArray& rOther, USHORT nStartRow, USHORT nEndRow ) const;

/*N*/   BOOL    TestInsertCol( USHORT nStartRow, USHORT nEndRow) const;
/*N*/   BOOL    TestInsertRow( USHORT nSize ) const;
/*N*/   void    InsertRow( USHORT nStartRow, USHORT nSize );
/*N*/   void    DeleteRow( USHORT nStartRow, USHORT nSize );
/*N*/   void    DeleteRange( USHORT nStartIndex, USHORT nEndIndex );
    void    DeleteArea( USHORT nStartRow, USHORT nEndRow );
/*N*/   void    MoveTo( USHORT nStartRow, USHORT nEndRow, ScAttrArray& rAttrArray );
    void    CopyArea( USHORT nStartRow, USHORT nEndRow, short nDy, ScAttrArray& rAttrArray,
                        INT16 nStripFlags = 0 );

    void    DeleteHardAttr( USHORT nStartRow, USHORT nEndRow );

    void    Save( SvStream& rStream ) const;
    void    Load( SvStream& rStream );
    void    ConvertFontsAfterLoad();     // old binary file format
};


//  ------------------------------------------------------------------------------
//                              Iterator fuer Attribute
//  ------------------------------------------------------------------------------

/*N*/ class ScAttrIterator
/*N*/ {
/*N*/   const ScAttrArray*  pArray;
/*N*/   short               nPos;
/*N*/   USHORT              nRow;
/*N*/   USHORT              nEndRow;
/*N*/ public:
/*N*/   inline              ScAttrIterator( const ScAttrArray* pNewArray, USHORT nStart, USHORT nEnd );
/*N*/   inline const ScPatternAttr* Next( USHORT& rTop, USHORT& rBottom );
/*N*/   USHORT              GetNextRow() const { return nRow; }
/*N*/ };
/*N*/
/*N*/
/*N*/ inline ScAttrIterator::ScAttrIterator( const ScAttrArray* pNewArray, USHORT nStart, USHORT nEnd ) :
/*N*/   pArray( pNewArray ),
/*N*/   nRow( nStart ),
/*N*/   nEndRow( nEnd )
/*N*/ {
/*N*/   if ( nStart )
/*N*/       pArray->Search( nStart, nPos );
/*N*/   else
/*N*/       nPos = 0;
/*N*/ }
/*N*/
/*N*/ inline const ScPatternAttr*   ScAttrIterator::Next( USHORT& rTop, USHORT& rBottom )
/*N*/ {
/*N*/   const ScPatternAttr* pRet;
/*N*/   if ( nPos < (short) pArray->nCount && nRow <= nEndRow )
/*N*/   {
/*N*/       rTop = nRow;
/*N*/       rBottom = Min( pArray->pData[nPos].nRow, nEndRow );
/*N*/       pRet = pArray->pData[nPos].pPattern;
/*N*/       nRow = rBottom + 1;
/*N*/       ++nPos;
/*N*/   }
/*N*/   else
/*N*/       pRet = NULL;
/*N*/   return pRet;
/*N*/ }



} //namespace binfilter
#endif


