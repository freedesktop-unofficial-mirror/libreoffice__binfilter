/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file incorporates work covered by the following license notice:
 *
 *   Licensed to the Apache Software Foundation (ASF) under one or more
 *   contributor license agreements. See the NOTICE file distributed
 *   with this work for additional information regarding copyright
 *   ownership. The ASF licenses this file to you under the Apache
 *   License, Version 2.0 (the "License"); you may not use this file
 *   except in compliance with the License. You may obtain a copy of
 *   the License at http://www.apache.org/licenses/LICENSE-2.0 .
 */

#ifndef SC_USERLIST_HXX
#define SC_USERLIST_HXX

#include <bf_svtools/bf_solar.h>


#include "collect.hxx"
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
/*N*/  BOOL Store( SvStream& ) const {return FALSE;}
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
/*N*/ BOOL Store( SvStream& ) const {return FALSE;}
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

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
