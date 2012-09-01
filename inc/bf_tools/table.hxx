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
#ifndef _TOOLS_TABLE_HXX
#define _TOOLS_TABLE_HXX

#include <tools/solar.h>
#include <bf_tools/contnr.hxx>

namespace binfilter
{

// ---------
// - Table -
// ---------

#define TABLE_ENTRY_NOTFOUND   CONTAINER_ENTRY_NOTFOUND

class Table : private Container
{
private:
    sal_uIntPtr nCount;
    SAL_DLLPRIVATE sal_uIntPtr    ImplGetIndex( sal_uIntPtr nKey, sal_uIntPtr* pIndex = NULL ) const;
public:
            Table( sal_uInt16 nInitSize = 16, sal_uInt16 nReSize = 16 );
            Table( const Table& rTable ) : Container( rTable )
                { nCount = rTable.nCount; }

    sal_Bool    Insert( sal_uIntPtr nKey, void* p );
    void*   Remove( sal_uIntPtr nKey );
    void*   Replace( sal_uIntPtr nKey, void* p );
    void*   Get( sal_uIntPtr nKey ) const;

    void    Clear() { Container::Clear(); nCount = 0; }
    sal_uIntPtr Count() const { return( nCount ); }

    void*   GetCurObject() const;
    sal_uIntPtr GetCurKey() const { return (sal_uIntPtr)Container::GetCurObject(); }
    sal_uIntPtr GetKey( const void* p ) const;
    sal_Bool    IsKeyValid( sal_uIntPtr nKey ) const;

    void*   GetObject( sal_uIntPtr nPos ) const
                { return Container::GetObject( (nPos*2)+1 ); }
    sal_uIntPtr GetObjectKey( sal_uIntPtr nPos ) const
                { return (sal_uIntPtr)Container::GetObject( nPos*2 ); }
    sal_uIntPtr SearchKey( sal_uIntPtr nKey, sal_uIntPtr* pPos = NULL ) const;

    void*   Seek( sal_uIntPtr nKey );
    void*   First();
    void*   Last();
    void*   Next();
    void*   Prev();

    Table&  operator =( const Table& rTable );

    sal_Bool    operator ==( const Table& rTable ) const
                { return Container::operator ==( rTable ); }
    sal_Bool    operator !=( const Table& rTable ) const
                { return Container::operator !=( rTable ); }
};

inline Table& Table::operator =( const Table& r )
{
    Container::operator =( r );
    nCount = r.nCount;
    return *this;
}

// -----------------
// - DECLARE_TABLE -
// -----------------

#define DECLARE_TABLE( ClassName, Type )                                \
class ClassName : private Table                                         \
{                                                                       \
public:                                                                 \
                using Table::Clear;                                     \
                using Table::Count;                                     \
                using Table::GetCurKey;                                 \
                using Table::GetObjectKey;                              \
                using Table::SearchKey;                                 \
                using Table::IsKeyValid;                                \
                                                                        \
                ClassName( sal_uInt16 _nInitSize = 16,                      \
                           sal_uInt16 _nReSize = 16 ) :                     \
                    Table( _nInitSize, _nReSize ) {}                    \
                ClassName( const ClassName& rClassName ) :              \
                    Table( rClassName ) {}                              \
                                                                        \
    sal_Bool        Insert( sal_uIntPtr nKey, Type p )                          \
                    { return Table::Insert( nKey, (void*)p ); }         \
    Type        Remove( sal_uIntPtr nKey )                                  \
                    { return (Type)Table::Remove( nKey ); }             \
    Type        Replace( sal_uIntPtr nKey, Type p )                         \
                    { return (Type)Table::Replace( nKey, (void*)p ); }  \
    Type        Get( sal_uIntPtr nKey ) const                               \
                    { return (Type)Table::Get( nKey ); }                \
                                                                        \
    Type        GetCurObject() const                                    \
                    { return (Type)Table::GetCurObject(); }             \
    sal_uIntPtr     GetKey( const Type p ) const                            \
                    { return Table::GetKey( (const void*)p ); }         \
                                                                        \
    Type        GetObject( sal_uIntPtr nPos ) const                         \
                    { return (Type)Table::GetObject( nPos ); }          \
                                                                        \
    Type        Seek( sal_uIntPtr nKey )                                        \
                    { return (Type)Table::Seek( nKey ); }               \
    Type        First() { return (Type)Table::First(); }                \
    Type        Last()  { return (Type)Table::Last(); }                 \
    Type        Next()  { return (Type)Table::Next(); }                 \
    Type        Prev()  { return (Type)Table::Prev(); }                 \
                                                                        \
    ClassName&  operator =( const ClassName& rClassName )               \
                    { Table::operator =( rClassName );                  \
                      return *this; }                                   \
                                                                        \
    sal_Bool        operator ==( const ClassName& rTable ) const            \
                    { return Table::operator ==( rTable ); }            \
    sal_Bool        operator !=( const ClassName& rTable ) const            \
                    { return Table::operator !=( rTable ); }            \
};

} // namespace binfilter

#endif // _TOOLS_TABLE_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
