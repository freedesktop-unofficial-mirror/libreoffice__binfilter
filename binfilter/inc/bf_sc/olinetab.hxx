/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: olinetab.hxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: hr $ $Date: 2007-01-02 18:27:33 $
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

#ifndef SC_OUTLINETAB_HXX
#define SC_OUTLINETAB_HXX


#ifndef SC_COLLECT_HXX
#include "collect.hxx"
#endif
class SvStream;
namespace binfilter {


#define SC_OL_MAXDEPTH      7

class ScMultipleReadHeader;
class ScMultipleWriteHeader;


class ScOutlineEntry : public DataObject
{
    USHORT      nStart;
    USHORT      nSize;
    BOOL        bHidden;
    BOOL        bVisible;

public:
                            ScOutlineEntry( USHORT nNewStart, USHORT nNewSize,
                                                 BOOL bNewHidden = FALSE );
                            ScOutlineEntry( const ScOutlineEntry& rEntry );
                            ScOutlineEntry( SvStream& rStream, ScMultipleReadHeader& rHdr );

    void                    Store( SvStream& rStream, ScMultipleWriteHeader& rHdr );
    virtual DataObject*     Clone() const;
    USHORT                  GetStart() const    { return nStart; }
/*N*/   USHORT                  GetSize() const     { return nSize; }
    USHORT                  GetEnd() const      { return nStart+nSize-1; }
    BOOL                    IsHidden() const    { return bHidden; }             // Gruppe versteckt
/*N*/   void                    Move( short nDelta );
/*N*/   void                    SetSize( USHORT nNewSize );
/*N*/   void                    SetPosSize( USHORT nNewPos, USHORT nNewSize );
    void                    SetVisible( BOOL bNewVisible );
};


class ScOutlineCollection : public SortedCollection
{
public:
                            ScOutlineCollection();

    virtual short           Compare(DataObject* pKey1, DataObject* pKey2) const;

};


class ScOutlineArray
{
friend class ScSubOutlineIterator;

private:
    USHORT                  nDepth;
    ScOutlineCollection     aCollections[SC_OL_MAXDEPTH];

/*N*/   BOOL                    DecDepth();
    void                    FindEntry( USHORT nSearchPos, USHORT& rFindLevel, USHORT& rFindIndex,
                                        USHORT nMaxLevel = SC_OL_MAXDEPTH );
public:
                            ScOutlineArray();
                             ScOutlineArray( const ScOutlineArray& rArray );

    USHORT                  GetDepth() const         { return nDepth; }


    BOOL                    Insert( USHORT nStartCol, USHORT nEndCol, BOOL& rSizeChanged,
                                    BOOL bHidden = FALSE, BOOL bVisible = TRUE );

    ScOutlineEntry*         GetEntry( USHORT nLevel, USHORT nIndex ) const;
    USHORT                  GetCount( USHORT nLevel ) const;

    void                    SetVisibleBelow( USHORT nLevel, USHORT nEntry, BOOL bValue,
                                                BOOL bSkipHidden = FALSE );


/*N*/    BOOL                    TestInsertSpace( USHORT nSize, USHORT nMaxVal ) const;
/*N*/   void                    InsertSpace( USHORT nStartPos, USHORT nSize );
/*N*/   BOOL                    DeleteSpace( USHORT nStartPos, USHORT nSize );

    BOOL                    ManualAction( USHORT nStartPos, USHORT nEndPos,
                                            BOOL bShow, BYTE* pHiddenFlags );
     void                   Load( SvStream& rStream );
    void                    Store( SvStream& rStream );
};


class ScOutlineTable
{
private:
    ScOutlineArray          aColOutline;
    ScOutlineArray          aRowOutline;

public:
                            ScOutlineTable();
                            ScOutlineTable( const ScOutlineTable& rOutline );

    const ScOutlineArray*   GetColArray() const     { return &aColOutline; }
    ScOutlineArray*         GetColArray()           { return &aColOutline; }
    const ScOutlineArray*   GetRowArray() const     { return &aRowOutline; }
     ScOutlineArray*            GetRowArray()           { return &aRowOutline; }

/*N*/   BOOL                    TestInsertCol( USHORT nSize );
/*N*/   void                    InsertCol( USHORT nStartCol, USHORT nSize );
/*N*/   BOOL                    DeleteCol( USHORT nStartCol, USHORT nSize );    // TRUE: Undo nur ueber Original
/*N*/   BOOL                    TestInsertRow( USHORT nSize );
/*N*/   void                    InsertRow( USHORT nStartRow, USHORT nSize );
/*N*/   BOOL                    DeleteRow( USHORT nStartRow, USHORT nSize );
    void                    Load( SvStream& rStream );
     void                   Store( SvStream& rStream );
};


class ScSubOutlineIterator
{
private:
    ScOutlineArray*         pArray;
    USHORT                  nStart;
    USHORT                  nEnd;
    USHORT                  nSubLevel;
    USHORT                  nSubEntry;
    USHORT                  nCount;
    USHORT                  nDepth;

public:
                            ScSubOutlineIterator( ScOutlineArray* pOutlineArray );
    ScOutlineEntry*         GetNext();
/*N*/   void                    DeleteLast();
};

} //namespace binfilter
#endif


