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
#ifndef _LAYCACHE_HXX
#define _LAYCACHE_HXX
namespace binfilter {


class SwDoc;
class SwLayCacheImpl;

/*************************************************************************
 *                      class SwLayoutCache
 *
 * This class allows to save layout information in the file and it contains
 * this information after loading of a file.
 * Call Read(..) with a stream and the member pLayCacheImpl will
 * read the information from the stream and store it in an internal structur.
 * There's a simple locking mechanism at these classes,
 * if somebody reads the information, he increments the lock count by 1,
 * during the Read(..) function the lock count will set to $8000.
 *
 **************************************************************************/

class SwLayoutCache
{
    SwLayCacheImpl *pImpl;
    USHORT nLockCount;
public:
    SwLayoutCache() : pImpl( NULL ), nLockCount( 0 ) {}
    ~SwLayoutCache();

    void ClearImpl();
    sal_Bool IsLocked() const { return nLockCount > 0; }
    USHORT& GetLockCount() { return nLockCount; }
    SwLayCacheImpl *LockImpl()
        { if( nLockCount & 0x8000 ) return NULL;
          if ( pImpl )
            ++nLockCount;
          return pImpl; }
    void UnlockImpl() { --nLockCount; }
};

} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
