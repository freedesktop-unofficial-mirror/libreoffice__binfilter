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

#ifndef _PARALIST_HXX
#define _PARALIST_HXX

#include <bf_svtools/bf_solar.h>
#include <tools/link.hxx>
#include <vector>
#include <limits.h>

namespace binfilter {
class Paragraph;

class ParagraphList
{
private:
    Link            aVisibleStateChangedHdl;
    std::vector< Paragraph* > aList;

public:
    void            Clear( BOOL bDestroyParagraphs );

    ULONG           GetParagraphCount() const           { return aList.size(); }
    Paragraph*      GetParagraph( ULONG nPos ) const    { return aList[ nPos ]; }

    ULONG           GetAbsPos( Paragraph* pParent ) const {
                        for( size_t i = 0, n = aList.size(); i < n; ++i ) {
                            if ( pParent == aList[ i ] ) {
                                return i;
                            }
                        }
                        return ULONG_MAX;
                    }

    void            Insert( Paragraph* pPara, ULONG nAbsPos = ULONG_MAX ) {
                        if ( nAbsPos < aList.size() ) {
                            std::vector< Paragraph* >::iterator it = aList.begin();
                            std::advance( it, nAbsPos );
                            aList.insert( it, pPara );
                        } else {
                            aList.push_back( pPara );
                        }
                    }

    void            Remove( ULONG nPara ) {
                        if ( nPara < aList.size() ) {
                            std::vector< Paragraph* >::iterator it = aList.begin();
                            std::advance( it, nPara );
                            aList.erase( it );
                        }
                    }


/*NBFF*/    Paragraph*      GetParent( Paragraph* pParagraph, USHORT& rRelPos ) const;


    void            SetVisibleStateChangedHdl( const Link& rLink ) { aVisibleStateChangedHdl = rLink; }
    Link            GetVisibleStateChangedHdl() const { return aVisibleStateChangedHdl; }
};

}//end of namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
