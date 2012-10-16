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
#ifndef _TABCOL_HXX
#define _TABCOL_HXX

#include <bf_svtools/bf_solar.h>

#ifndef _SVSTDARR_HXX
#define _SVSTDARR_LONGS
#define _SVSTDARR_BOOLS
#include <bf_svtools/svstdarr.hxx>
#endif
namespace binfilter {

class SwTabCols : public SvLongs
{
    long nLeftMin,      //Linker aeusserer Rand (Bezugspunkt) in
                        //Dokumentkordinaten.
                        //Alle anderen Werte relativ zu diesem Punkt!
            nLeft,      //Linker Rand der Tabelle.
           nRight,      //Rechter Rand der Tabelle.
           nRightMax;   //Maximaler rechter Rand der Tabelle.



    SvBools aHidden;    //Fuer jeden Eintrag ein Flag, Hidden oder nicht.
                        //Wenn das Flag Hidden TRUE ist liegt der Spalten-
                        //trenner nicht in der aktuellen Zeile; er muss
                        //mit gepflegt werden, darf aber nicht angezeigt
                        //werden.
public:
    SwTabCols( USHORT /*nSize*/ = 0 ){DBG_BF_ASSERT(0, "STRIP");} ;
    SwTabCols( const SwTabCols& ) : SvLongs() {DBG_BF_ASSERT(0, "STRIP");} ;
    BOOL IsHidden( USHORT nPos ) const         { return aHidden[nPos]; }
    void SetHidden( USHORT nPos, BOOL bValue ) { aHidden[nPos] = bValue; }
    inline void InsertHidden( USHORT nPos, BOOL bValue );
    inline void DeleteHidden( USHORT nPos, USHORT nAnz = 1 );

    //fuer den CopyCTor
    const SvBools& GetHidden() const { return aHidden; }

    long GetLeftMin() const { return nLeftMin; }
    long GetLeft()  const { return nLeft;    }
    long GetRight() const { return nRight;   }
    long GetRightMax()const { return nRightMax;}

    void SetLeftMin ( long nNew )   { nLeftMin = nNew; }
    void SetLeft    ( long nNew )   { nLeft = nNew;    }
    void SetRight   ( long nNew )   { nRight = nNew;   }
    void SetRightMax( long nNew )   { nRightMax = nNew;}
};

inline void SwTabCols::InsertHidden( USHORT nPos, BOOL bValue )
{
    aHidden.Insert( bValue, nPos );
}
inline void SwTabCols::DeleteHidden( USHORT nPos, USHORT nAnz )
{
    aHidden.Remove( nPos, nAnz );
}

} //namespace binfilter
#endif  //_TABCOL_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
