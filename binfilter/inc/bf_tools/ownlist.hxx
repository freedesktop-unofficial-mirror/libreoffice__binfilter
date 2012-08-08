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

#ifndef _TOOLS_OWNLIST_HXX
#define _TOOLS_OWNLIST_HXX

#include <bf_tools/list.hxx>

namespace binfilter {
/*************************************************************************
*************************************************************************/

#define PRV_SV_DECL_OWNER_LIST(ClassName,Type)                            \
    List  aTypes;                                                         \
public:                                                                   \
                        ClassName( sal_uInt16 nInitSize = 16,                 \
                                   sal_uInt16 nReSize = 16 )                  \
                            : aTypes( nInitSize, nReSize ) {}             \
                        ClassName( const ClassName & rObj )               \
                        { *this = rObj; }                                 \
    ClassName &         operator = ( const ClassName & );                 \
                        ~ClassName()                                      \
                        { Clear(); }                                      \
    void                Clear();                                          \
    void                Remove()                                          \
                        { delete (Type *)aTypes.Remove(); }               \
    void                Remove( Type * pObj )                             \
                        { delete (Type *)aTypes.Remove( pObj ); }         \
    void                Remove( sal_uIntPtr nPos )                              \
                        { delete (Type *)aTypes.Remove( nPos ); }         \
    Type &              Insert( const Type &, sal_uIntPtr nPos );               \
    Type &              Insert( const Type & rType )                      \
                        { return Insert( rType, aTypes.GetCurPos() ); }   \
    Type &              Append( const Type & rType )                      \
                        { return Insert( rType, LIST_APPEND ); }          \
    Type &              GetObject( sal_uIntPtr nPos ) const                     \
                        { return *(Type *)aTypes.GetObject( nPos ); }     \
    Type &              operator []( sal_uIntPtr nPos ) const                   \
                        { return *(Type *)aTypes.GetObject( nPos ); }     \
    sal_uIntPtr               Count() const { return aTypes.Count(); }

#define PRV_SV_IMPL_OWNER_LIST(ClassName,Type)                          \
ClassName & ClassName::operator = ( const ClassName & rObj )            \
{                                                                       \
    if( this != &rObj )                                                 \
    {                                                                   \
        Clear();                                                        \
        for( sal_uIntPtr i = 0; i < rObj.Count(); i++ )                       \
            Append( rObj.GetObject( i ) );                              \
    }                                                                   \
    return *this;                                                       \
}                                                                       \
void ClassName::Clear()                                                 \
{                                                                       \
    Type * p = (Type *)aTypes.First();                                  \
    while( p )                                                          \
    {                                                                   \
        delete p;                                                       \
        p = (Type *)aTypes.Next();                                      \
    }                                                                   \
    aTypes.Clear();                                                     \
}                                                                       \
Type & ClassName::Insert( const Type & rType, sal_uIntPtr nPos )              \
{                                                                       \
    Type * pType = new Type( rType );                                   \
    aTypes.Insert( pType, nPos );                                       \
    return *pType;                                                      \
}

}
#endif // _TOOLS_OWNLIST_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
