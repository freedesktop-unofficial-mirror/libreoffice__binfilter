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
#ifndef _BF_UNQID_HXX
#define _BF_UNQID_HXX

#include <bf_tools/unqidx.hxx>

namespace binfilter {

// ---------------
// - ImpUniqueId -
// ---------------

struct ImpUniqueId
{
    sal_uIntPtr    nId;
    sal_uInt16   nRefCount;
    void     Release()
             {
                nRefCount--;
                if( 0 == nRefCount )
                    delete this;
             }
};

// ------------
// - UniqueId -
// ------------

class UniqueIdContainer;
class UniqueItemId
{
    friend class UniqueIdContainer;
    ImpUniqueId*    pId;

                    UniqueItemId( ImpUniqueId * pIdP )
                        { pId = pIdP; pId->nRefCount++; }
public:
                    UniqueItemId() { pId = NULL; }
                    UniqueItemId( const UniqueItemId & rId )
                        { pId = rId.pId; if( pId ) pId->nRefCount++; }
                    ~UniqueItemId()
                        { if( pId ) pId->Release(); }
    UniqueItemId&   operator = ( const UniqueItemId & rId )
                        {
                            if( rId.pId ) rId.pId->nRefCount++;
                            if( pId ) pId->Release();
                            pId = rId.pId;
                            return *this;
                        }
    sal_uIntPtr           GetId() const { return pId ? pId->nId : 0; }
};

// ---------------------
// - UniqueIdContainer -
// ---------------------

class UniqueIdContainer : private UniqueIndex
{
    sal_uInt16              nCollectCount;

public: // Irgend etwas mit protected falsch
    void                Clear( sal_Bool bAll );

public:
                        UniqueIdContainer( sal_uIntPtr _nStartIndex,
                                           sal_uIntPtr _nInitSize = 16,
                                           sal_uIntPtr _nReSize = 16 )
                            : UniqueIndex( _nStartIndex, _nInitSize, _nReSize )
                            , nCollectCount( 0 )
                            {}
                        UniqueIdContainer( const UniqueIdContainer& );

                        ~UniqueIdContainer()
                            { Clear( sal_True ); }
    UniqueIdContainer&  operator = ( const UniqueIdContainer & );

    sal_Bool                IsIndexValid( sal_uIntPtr nIndex ) const
                            { return UniqueIndex::IsIndexValid( nIndex ); }

    UniqueItemId        CreateId();
};

}

#endif // _BF_UNQID_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
