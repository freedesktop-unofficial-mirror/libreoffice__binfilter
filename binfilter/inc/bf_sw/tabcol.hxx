/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: tabcol.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 04:58:06 $
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
#ifndef _TABCOL_HXX
#define _TABCOL_HXX

#ifndef _SVSTDARR_HXX
#define _SVSTDARR_LONGS
#define _SVSTDARR_BOOLS
#include <svtools/svstdarr.hxx>
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
        SwTabCols( USHORT nSize = 0 ){DBG_BF_ASSERT(0, "STRIP");} ;//STRIP001   SwTabCols( USHORT nSize = 0 );
        SwTabCols( const SwTabCols& ){DBG_BF_ASSERT(0, "STRIP");} ;//STRIP001   SwTabCols( const SwTabCols& );

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
