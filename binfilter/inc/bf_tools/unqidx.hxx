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
#ifndef _BF_UNQIDX_HXX
#define _BF_UNQIDX_HXX

#include <bf_tools/contnr.hxx>

namespace binfilter {

// ---------------
// - UniqueIndex -
// ---------------

#define UNIQUEINDEX_ENTRY_NOTFOUND   CONTAINER_ENTRY_NOTFOUND

class UniqueIndex : private Container
{
private:
    sal_uIntPtr           nReSize;
    sal_uIntPtr           nStartIndex;
    sal_uIntPtr           nUniqIndex;
    sal_uIntPtr           nCount;

    sal_uIntPtr     Insert( sal_uIntPtr nIndex, void* p );
    void*           Get( sal_uIntPtr nIndex ) const;
    void*           Seek( void* p );

public:
                    UniqueIndex( sal_uIntPtr nStartIndex = 0,
                                 sal_uIntPtr nInitSize = 16,
                                 sal_uIntPtr nReSize = 16 );
                    UniqueIndex( const UniqueIndex& rIdx );

    sal_uIntPtr           Insert( void* p );
    void*           Remove( sal_uIntPtr nIndex );

    void            Clear();
    sal_uIntPtr           Count() const { return nCount; }

    sal_uIntPtr           GetCurIndex() const;
    sal_Bool            IsIndexValid( sal_uIntPtr nIndex ) const;

    void*           Seek( sal_uIntPtr nIndex );
    void*           First();
    void*           Last();
    void*           Next();
    void*           Prev();

    sal_uIntPtr           GetStartIndex() const { return nStartIndex; }
    sal_uIntPtr           GetCurMaxIndex() const
                        { return (nStartIndex + Container::GetSize()); }

    UniqueIndex&    operator =( const UniqueIndex& rIdx );

    sal_Bool            operator ==( const UniqueIndex& rIdx ) const;
    sal_Bool            operator !=( const UniqueIndex& rIdx ) const
                        { return !(UniqueIndex::operator==( rIdx )); }
};

inline void UniqueIndex::Clear()
{
    Container::Clear();
    nCount     = 0;
    nUniqIndex = 0;
}

}

#endif // _BF_UNQIDX_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
