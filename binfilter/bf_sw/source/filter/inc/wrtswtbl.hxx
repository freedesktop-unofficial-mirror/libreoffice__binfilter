/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: wrtswtbl.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 10:34:04 $
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

#ifndef  _WRTSWTBL_HXX
#define  _WRTSWTBL_HXX

#ifndef _SOLAR_H
#include <tools/solar.h>
#endif
#ifndef _TOOLS_COLOR_HXX
#include <tools/color.hxx>
#endif
#ifndef _SVARRAY_HXX
#include <bf_svtools/svarray.hxx>
#endif

#ifndef _ORNTENUM_HXX
#include <orntenum.hxx>
#endif
#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif
class Color;
namespace binfilter {


class SwTableBox;
class SwTableBoxes;
class SwTableLine;
class SwTableLines;
class SwTable;
class SwFrmFmt;
class SwHTMLTableLayout;
class SvxBrushItem;
class SvxBoxItem;
class SvxBorderLine;


//---------------------------------------------------------------------------
//       Code aus dem HTML-Filter fuers schreiben von Tabellen
//---------------------------------------------------------------------------

#define COLFUZZY 20
#define ROWFUZZY 20
#define COL_DFLT_WIDTH ((2*COLFUZZY)+1)
#define ROW_DFLT_HEIGHT (2*ROWFUZZY)+1


//-----------------------------------------------------------------------




//-----------------------------------------------------------------------






//-----------------------------------------------------------------------

class SwWriteTableCol
{
    USHORT nPos;                        // End Position der Spalte

    USHORT nWidthOpt;

    BOOL bRelWidthOpt : 1;
    BOOL bOutWidth : 1;                 // Spaltenbreite ausgeben?

public:
    BOOL bLeftBorder : 1;               // Welche Umrandungen sind da?
    BOOL bRightBorder : 1;

    SwWriteTableCol( USHORT nPosition );

    USHORT GetPos() const                       { return nPos; }

    void SetLeftBorder( BOOL bBorder )          { bLeftBorder = bBorder; }
    BOOL HasLeftBorder() const                  { return bLeftBorder; }

    void SetRightBorder( BOOL bBorder )         { bRightBorder = bBorder; }
    BOOL HasRightBorder() const                 { return bRightBorder; }

    void SetOutWidth( BOOL bSet )               { bOutWidth = bSet; }
    BOOL GetOutWidth() const                    { return bOutWidth; }

    inline int operator==( const SwWriteTableCol& rCol ) const;
    inline int operator<( const SwWriteTableCol& rCol ) const;

    void SetWidthOpt( USHORT nWidth, BOOL bRel )
    {
        nWidthOpt = nWidth; bRelWidthOpt = bRel;
    }
    USHORT GetWidthOpt() const                  { return nWidthOpt; }
    BOOL HasRelWidthOpt() const                 { return bRelWidthOpt; }
};

inline int SwWriteTableCol::operator==( const SwWriteTableCol& rCol ) const
{
    // etwas Unschaerfe zulassen
    return (nPos >= rCol.nPos ? nPos - rCol.nPos
                                     : rCol.nPos - nPos ) <= COLFUZZY;
}

inline int SwWriteTableCol::operator<( const SwWriteTableCol& rCol ) const
{
    // Da wir hier nur die Wahrheits-Grade 0 und 1 kennen, lassen wir lieber
    // auch nicht zu, dass x==y und x<y gleichzeitig gilt ;-)
    return nPos < rCol.nPos - COLFUZZY;
}


typedef SwWriteTableCol *SwWriteTableColPtr;
SV_DECL_PTRARR_SORT_DEL( SwWriteTableCols, SwWriteTableColPtr, 5, 5 )

//-----------------------------------------------------------------------

class SwWriteTable
{








public:
    static long GetBoxWidth( const SwTableBox *pBox );






};




} //namespace binfilter
#endif

