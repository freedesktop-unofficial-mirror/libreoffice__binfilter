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
#ifndef _BF_REF_HXX
#define _BF_REF_HXX

#include <bf_tools/list.hxx>
#include <vector>

 /************************** S v R e f L i s t ****************************/
#define PRV_SV_DECL_REF_LIST(CN,EN,vis) \
class CN##List : private List                                           \
{                                                                       \
public:                                                                 \
            using List::Clear;                                          \
            using List::Count;                                          \
            using List::GetCurPos;                                      \
                                                                        \
            CN##List( sal_uInt16 _nInitSize = 16, sal_uInt16 _nReSize = 16 )  \
                : List( _nInitSize, _nReSize ) {}                       \
            CN##List( sal_uInt16 _nBlockSize, sal_uInt16 _nInitSize,    \
                           sal_uInt16 _nReSize )                        \
                : List( _nBlockSize, _nInitSize, _nReSize ) {}          \
            CN##List( const CN##List& rClassName )                      \
                : List( rClassName ) {}                                 \
                                                                        \
    void    Insert( EN p, sal_uIntPtr nIndex )                          \
                { List::Insert( (void*)p, nIndex ); }                   \
    void    Insert( EN p )                                              \
                { List::Insert( (void*)p ); }                           \
    EN      Remove()                                                    \
                { return (EN)List::Remove(); }                          \
    EN      Remove( sal_uIntPtr nIndex )                                \
                { return (EN)List::Remove( nIndex ); }                  \
    EN      Remove( EN p )                                              \
                { return (EN)List::Remove( (void*)p ); }                \
    EN      Replace( EN p, sal_uIntPtr nIndex )                         \
                { return (EN)List::Replace( (void*)p, nIndex ); }       \
    EN      Replace( EN pNew, EN pOld )                                 \
                { return (EN)List::Replace( (void*)pNew, (void*)pOld ); }   \
                                                                        \
    EN      GetCurObject() const                                        \
                { return (EN)List::GetCurObject(); }                    \
    EN      GetObject( sal_uIntPtr nIndex ) const                       \
                { return (EN)List::GetObject( nIndex ); }               \
    sal_uIntPtr GetPos( const EN p ) const                              \
                { return List::GetPos( (const void*)p ); }              \
                                                                        \
    EN      Seek( sal_uIntPtr nIndex )                                  \
                { return (EN)List::Seek( nIndex ); }                    \
    EN      Seek( void* p ) { return (EN)List::Seek( p ); }             \
    EN      First()         { return (EN)List::First(); }               \
    EN      Last()          { return (EN)List::Last(); }                \
    EN      Next()          { return (EN)List::Next(); }                \
    EN      Prev()          { return (EN)List::Prev(); }                \
                                                                        \
    CN##List&  operator =( const CN##List& rClassName )                 \
                    { List::operator =( rClassName ); return *this; }   \
                                                                        \
    sal_Bool        operator ==( const CN##List& rList ) const          \
                    { return List::operator ==( rList ); }              \
    sal_Bool        operator !=( const CN##List& rList ) const          \
                    { return List::operator !=( rList ); }              \
};                                                                      \
class vis CN##MemberList : public CN##List\
{\
public:\
    inline CN##MemberList();\
    inline CN##MemberList(sal_uInt16 nInitSz, sal_uInt16 nResize );\
    inline CN##MemberList( const CN##MemberList & rRef );\
    inline ~CN##MemberList();\
    inline CN##MemberList & operator =( const CN##MemberList & rRef );\
    inline void Clear();\
    inline void Insert( EN p )\
        {\
            CN##List::Insert( p );\
            p->AddRef();\
        }\
    inline void Insert( EN p, sal_uIntPtr nIndex )\
        {\
            CN##List::Insert( p, nIndex );\
            p->AddRef();\
        }\
    inline void Append( EN p ) { Insert( p, LIST_APPEND ); }\
    inline EN   Remove();\
    inline EN   Remove( sal_uIntPtr nIndex );\
    inline EN   Remove( EN p );\
    inline EN   Replace( EN p, sal_uIntPtr nIndex );\
    inline EN   Replace( EN pNew, EN pOld );\
    inline void Append( const CN##MemberList & );\
};

#define SV_DECL_REF_LIST(CN,EN) \
PRV_SV_DECL_REF_LIST(CN,EN,/* empty */)

/************************** S v R e f L i s t ****************************/
#define SV_IMPL_REF_LIST( CN, EN ) \
inline CN##MemberList::CN##MemberList(){}\
inline CN##MemberList::CN##MemberList(sal_uInt16 nInitSz, sal_uInt16 nResize )\
    : CN##List( nInitSz, nResize ){}\
inline CN##MemberList::CN##MemberList( const CN##MemberList & rRef ) \
      : CN##List( rRef ) \
{\
    sal_uIntPtr nOldCount = Count(); \
    EN pEntry = First(); \
    while( pEntry ) \
    { pEntry->AddRef(); pEntry = Next(); } \
    Seek( nOldCount ); /* auch Curser gleich */ \
}\
inline CN##MemberList::~CN##MemberList() { Clear(); } \
inline CN##MemberList & CN##MemberList::operator = \
                    ( const CN##MemberList & rRef ) \
{\
    CN##MemberList & rList = (CN##MemberList &)rRef; \
    sal_uIntPtr nOldCount = rList.Count(); \
    /* Count der Objekte erhoehen */ \
    EN pEntry = rList.First(); \
    while( pEntry ) \
    { pEntry->AddRef(); pEntry = rList.Next(); } \
    rList.Seek( nOldCount ); /* Curser zurueck */ \
    /* Liste kopieren */ \
    Clear(); \
    CN##List::operator = ( rRef ); \
    return *this; \
}\
inline void        CN##MemberList::Clear() \
{\
    EN pEntry = Last();\
    while( NULL != pEntry )\
        pEntry = Remove();\
}\
inline EN CN##MemberList::Remove() \
{\
    EN p = CN##List::Remove(); \
    if( p ) p->ReleaseReference(); return p; \
}\
inline EN CN##MemberList::Remove( sal_uIntPtr nIndex ) \
{\
    EN p = CN##List::Remove( nIndex ); \
    if( p ) p->ReleaseReference(); return p; \
}\
inline EN CN##MemberList::Remove( EN p ) \
{\
    p = CN##List::Remove( p ); \
    if( p ) p->ReleaseReference(); return p; \
}\
inline EN CN##MemberList::Replace( EN p, sal_uIntPtr nIndex ) \
{\
    p->AddRef(); p = CN##List::Replace( p, nIndex ); \
    if( p ) p->ReleaseReference(); return p; \
}\
inline EN CN##MemberList::Replace( EN pNew, EN pOld ) \
{\
    pNew->AddRef(); CN##List::Replace( pNew, pOld ); \
    if( pOld ) pOld->ReleaseReference(); return pOld; \
}\
inline void CN##MemberList::Append( const CN##MemberList & rList )\
{\
    for( sal_uIntPtr i = 0; i < rList.Count(); i++ )\
        Append( rList.GetObject( i ) );\
}

/************************** S v M e m b e r L i s t **********************/
#define PRV_SV_DECL_MEMBER_LIST(Class,EntryName)        \
       Class##MemberList() {}                           \
inline void Insert( EntryName p );                      \
inline void Insert( EntryName p, sal_uIntPtr nIndex );        \
inline void Append( EntryName p );                      \
inline EntryName   Remove();                            \
inline EntryName   Remove( sal_uIntPtr nIndex );              \
inline EntryName   Remove( EntryName p );               \
inline EntryName   Replace( EntryName p, sal_uIntPtr nIndex );\
inline EntryName   Replace( EntryName pNew, EntryName pOld );\
inline EntryName   GetCurObject() const;\
inline EntryName   GetObject( sal_uIntPtr nIndex ) const;\
inline sal_uIntPtr       GetPos( const EntryName ) const;\
inline EntryName Seek( sal_uIntPtr nIndex );\
inline EntryName Seek( EntryName p );\
inline EntryName First();\
inline EntryName Last();\
inline EntryName Next();\
inline EntryName Prev();\
inline void      Append( const Class##MemberList & rList );

#define PRV_SV_IMPL_MEMBER_LIST(ClassName,EntryName,BaseList)\
inline void ClassName##MemberList::Insert( EntryName p )\
            {BaseList::Insert(p);}\
inline void ClassName##MemberList::Insert( EntryName p, sal_uIntPtr nIdx )\
            {BaseList::Insert(p,nIdx);}\
inline void ClassName##MemberList::Append( EntryName p )\
            {BaseList::Append(p);}\
inline EntryName ClassName##MemberList::Remove()\
            {return (EntryName)BaseList::Remove();}\
inline EntryName ClassName##MemberList::Remove( sal_uIntPtr nIdx )\
            {return (EntryName)BaseList::Remove(nIdx);}\
inline EntryName ClassName##MemberList::Remove( EntryName p )\
            {return (EntryName)BaseList::Remove(p);}\
inline EntryName ClassName##MemberList::Replace( EntryName p, sal_uIntPtr nIdx )\
            {return (EntryName)BaseList::Replace(p,nIdx);}\
inline EntryName ClassName##MemberList::Replace( EntryName p, EntryName pOld )\
            {return (EntryName)BaseList::Replace(p,pOld);}\
inline EntryName   ClassName##MemberList::GetCurObject() const\
            {return (EntryName)BaseList::GetCurObject();}\
inline EntryName   ClassName##MemberList::GetObject( sal_uIntPtr nIdx ) const\
            {return (EntryName)BaseList::GetObject( nIdx );}\
inline EntryName ClassName##MemberList::Seek( sal_uIntPtr nIdx )\
            {return (EntryName)BaseList::Seek( nIdx );}\
inline EntryName ClassName##MemberList::Seek( EntryName p )\
            {return (EntryName)BaseList::Seek( p );}\
inline EntryName ClassName##MemberList::First()\
            {return (EntryName)BaseList::First();}\
inline EntryName ClassName##MemberList::Last()\
            {return (EntryName)BaseList::Last();}\
inline EntryName ClassName##MemberList::Next()\
            {return (EntryName)BaseList::Next();}\
inline EntryName ClassName##MemberList::Prev()\
            {return (EntryName)BaseList::Prev();}\
inline void      ClassName##MemberList::Append( const ClassName##MemberList & rList )\
            {BaseList::Append(rList);}\
inline sal_uIntPtr   ClassName##MemberList::GetPos( const EntryName p) const\
            {return BaseList::GetPos( p );}

#define SV_DECL_REF_LIST(CN,EN) \
PRV_SV_DECL_REF_LIST(CN,EN,/* empty */)

#define SV_DECL_REF_LIST_VISIBILITY(CN,EN,vis) \
PRV_SV_DECL_REF_LIST(CN,EN,vis)

#endif // _Weak_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
