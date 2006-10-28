/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svxfont.hxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 04:14:21 $
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
#ifndef _SVX_SVXFONT_HXX
#define _SVX_SVXFONT_HXX

#include <limits.h>     // USHRT_MAX
#ifndef _SVX_SVXENUM_HXX
#include <bf_svx/svxenum.hxx>
#endif

#ifndef INCLUDED_I18NPOOL_LANG_H
#include <i18npool/lang.h>
#endif
#ifndef _SV_FONT_HXX //autogen
#include <vcl/font.hxx>
#endif
class OutputDevice;
class Printer;
namespace binfilter {

class SvxDoCapitals;

class SvxFont : public Font
{
    LanguageType eLang;         // Language
    SvxCaseMap   eCaseMap;      // Textauszeichnung
    short nEsc;                 // Grad der Hoch-/Tiefstellung
    BYTE  nPropr;               // Grad der Verkleinerung der Fonthoehe
    short nKern;                // Kerning in Pt

public:
    SvxFont();
    SvxFont( const Font &rFont );
    SvxFont( const SvxFont &rFont );

    // Methoden fuer die Hoch-/Tiefstellung
    inline short GetEscapement() const { return nEsc; }
    inline void SetEscapement( const short nNewEsc ) { nEsc = nNewEsc; }

    inline BYTE GetPropr() const { return nPropr; }
    inline void SetPropr( const BYTE nNewPropr ) { nPropr = nNewPropr; }
    inline void SetProprRel( const BYTE nNewPropr )
        { SetPropr( (BYTE)( (long)nNewPropr * (long)nPropr / 100L ) ); }

    // Kerning
    inline short GetFixKerning() const { return nKern; }
    inline void  SetFixKerning( const short nNewKern ) { nKern = nNewKern; }

    inline SvxCaseMap GetCaseMap() const { return eCaseMap; }
    inline void    SetCaseMap( const SvxCaseMap eNew ) { eCaseMap = eNew; }

    inline LanguageType GetLanguage() const { return eLang; }
    inline void SetLanguage( const LanguageType eNewLan ) { eLang = eNewLan; }

    // Is-Methoden:
    inline BOOL IsCaseMap() const { return SVX_CASEMAP_NOT_MAPPED != eCaseMap; }
    inline BOOL IsCapital() const { return SVX_CASEMAP_KAPITAELCHEN == eCaseMap; }
    inline BOOL IsKern() const { return 0 != nKern; }
    inline BOOL IsEsc() const { return 0 != nEsc; }

    // Versalien, Gemeine etc. beruecksichtigen
    String CalcCaseMap( const String &rTxt ) const;

// Der folgende Bereich wird nicht von jedem benoetigt, er kann deshalb
// ausgeklammert werden.
#ifndef REDUCEDSVXFONT
    // Kapitaelchenbearbeitung

    void SetPhysFont( OutputDevice *pOut ) const;



    Size GetPhysTxtSize( const OutputDevice *pOut, const String &rTxt );



    void QuickDrawText( OutputDevice *pOut, const Point &rPos, const String &rTxt,
               const USHORT nIdx = 0, const USHORT nLen = STRING_LEN, const sal_Int32* pDXArray = NULL ) const;

    Size QuickGetTextSize( const OutputDevice *pOut, const String &rTxt,
                         const USHORT nIdx, const USHORT nLen, sal_Int32* pDXArray = NULL ) const;


#endif // !REDUCEDSVXFONT
    SvxFont&    operator=( const SvxFont& rFont );
    SvxFont&    operator=( const Font& rFont );
};

}//end of namespace binfilter
#endif // #ifndef   _SVX_SVXFONT_HXX

