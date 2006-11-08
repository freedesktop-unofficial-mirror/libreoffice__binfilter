/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: excfntbf.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: kz $ $Date: 2006-11-08 15:42:00 $
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
#ifndef _EXCFNTBF_HXX
#define _EXCFNTBF_HXX

#ifndef _SOLAR_H
#include <tools/solar.h>
#endif
class String;
namespace binfilter {

class SvxColorItem;
class SvxFontItem;
class SvxFontHeightItem;


//------------------------------------------------------------------------

enum ExcScript {
    EXCSCR_None = 0x00,
    EXCSCR_Super = 0x01,
    EXCSCR_Sub = 0x02 };

enum ExcUnderline {
    EXCUNDER_None = 0x00,
    EXCUNDER_Single = 0x01,
    EXCUNDER_Double = 0x02,
    EXCUNDER_SingleAccount = 0x21,
    EXCUNDER_DoubleAccount = 0x22,
    EXCUNDER_Attr = 0xFF };

struct ExcFont{
    SvxFontItem             *pFont;
    SvxFontHeightItem       *pHeight;
    UINT16                  nColor;
    UINT16                  nWeight;
    ExcScript               eScript;
    ExcUnderline            eUnderline;
    INT16                   bItalic : 1;
    INT16                   bStrikeout : 1;
    INT16                   bOutline : 1;
    INT16                   bShadow : 1;
    };


//------------------------------------------------------------------------
class ColorBuffer
    {
    private:
        SvxColorItem        **pArray;
        SvxColorItem        *pDefault;
        UINT16              nMax;
        UINT16              nCount;
        BOOL                bAuto;
        // ----------------------------------------------------------
    public:
                            ColorBuffer();
                            ~ColorBuffer();

#ifdef USED
        void                Reset( void );
#endif
        BOOL                NewColor( UINT16 nR, UINT16 nG, UINT16 nB );
        const SvxColorItem  *GetColor( UINT16 nIndex );

        BOOL                Auto( void ) const { return bAuto; }
    };

//------------------------------------------------------------------------
class FontBuffer
    {
    private:
        ExcFont             **ppFonts;  // Array mit Fontbeschreibungen
        UINT16              nMax;       // Groesse des Arrays
        UINT16              nCount;     // akt. Speichermarke im Array
        ExcFont             aDefaultFont;
    public:
                            FontBuffer( UINT16 nNewMax = 128 );
                            ~FontBuffer();

        void                NewFont( UINT16 nHeight, BYTE nAttr0,
                                UINT16 nIndexCol, const String &rName );

        void                NewFont( UINT16 nHeight, BYTE nAttr0,
                                BYTE nUnderline, UINT16 nIndexCol,
                                UINT16 nBoldness, BYTE nFamily, BYTE nCharset,
                                const String &rName );

        const ExcFont       &GetFont( UINT16 nIndex );

#ifdef USED
        void                Reset( void );
#endif
    };




} //namespace binfilter
#endif

