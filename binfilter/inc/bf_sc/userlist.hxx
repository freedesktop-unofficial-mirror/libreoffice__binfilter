/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: userlist.hxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 02:44:14 $
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

#ifndef SC_USERLIST_HXX
#define SC_USERLIST_HXX


#ifndef SC_COLLECT_HXX
#include "collect.hxx"
#endif
namespace binfilter {

//------------------------------------------------------------------------
class ScUserListData : public DataObject
{
friend class ScUserList;
    String  aStr;
    USHORT  nTokenCount;
    String* pSubStrings;
    String* pUpperSub;

    void    InitTokens();

public:
                    ScUserListData(const String& rStr);
                    ScUserListData(const ScUserListData& rData);
/*N*/                   ScUserListData( SvStream& rStream );
    virtual         ~ScUserListData();

    virtual DataObject*     Clone() const { return new ScUserListData(*this); }
/*N*/           BOOL            Store( SvStream& rStream ) const;
    const   String&         GetString() const { return aStr; }
            BOOL            GetSubIndex(const String& rSubStr, USHORT& rIndex) const;
};

//------------------------------------------------------------------------
class ScUserList : public Collection
{
public:
                    ScUserList( USHORT nLim = 4, USHORT nDel = 4);
                    ScUserList( const ScUserList& rUserList ) : Collection ( rUserList ) {}

    virtual DataObject*     Clone() const;

            ScUserListData* GetData( const String& rSubStr ) const;
/*N*/           BOOL            Load( SvStream& rStream );
/*N*/           BOOL            Store( SvStream& rStream ) const;
            /// If the list in rStr is already inserted
            BOOL            HasEntry( const String& rStr ) const;

    inline  ScUserListData* operator[]( const USHORT nIndex) const;
    inline  ScUserList&     operator= ( const ScUserList& r );
};

inline  ScUserList& ScUserList::operator=( const ScUserList& r )
    { return (ScUserList&)Collection::operator=( r ); }

inline ScUserListData* ScUserList::operator[]( const USHORT nIndex) const
    { return (ScUserListData*)At(nIndex); }


} //namespace binfilter
#endif

