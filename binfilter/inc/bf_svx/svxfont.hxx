/*************************************************************************
 *
 *  $RCSfile: svxfont.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 08:29:04 $
 *
 *  The Contents of this file are made available subject to the terms of
 *  either of the following licenses
 *
 *         - GNU Lesser General Public License Version 2.1
 *         - Sun Industry Standards Source License Version 1.1
 *
 *  Sun Microsystems Inc., October, 2000
 *
 *  GNU Lesser General Public License Version 2.1
 *  =============================================
 *  Copyright 2000 by Sun Microsystems, Inc.
 *  901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License version 2.1, as published by the Free Software Foundation.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *  MA  02111-1307  USA
 *
 *
 *  Sun Industry Standards Source License Version 1.1
 *  =================================================
 *  The contents of this file are subject to the Sun Industry Standards
 *  Source License Version 1.1 (the "License"); You may not use this file
 *  except in compliance with the License. You may obtain a copy of the
 *  License at http://www.openoffice.org/license.html.
 *
 *  Software provided under this License is provided on an "AS IS" basis,
 *  WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING,
 *  WITHOUT LIMITATION, WARRANTIES THAT THE SOFTWARE IS FREE OF DEFECTS,
 *  MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE, OR NON-INFRINGING.
 *  See the License for the specific provisions governing your rights and
 *  obligations concerning the Software.
 *
 *  The Initial Developer of the Original Code is: Sun Microsystems, Inc.
 *
 *  Copyright: 2000 by Sun Microsystems, Inc.
 *
 *  All Rights Reserved.
 *
 *  Contributor(s): _______________________________________
 *
 *
 ************************************************************************/
#ifndef _SVX_SVXFONT_HXX
#define _SVX_SVXFONT_HXX

#include <limits.h>     // USHRT_MAX
#ifndef _SVX_SVXENUM_HXX
#include <bf_svx/svxenum.hxx>
#endif

#ifndef _LANG_HXX //autogen
#include <tools/lang.hxx>
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
//STRIP001  void DoOnCapitals( SvxDoCapitals &rDo,
//STRIP001                     const USHORT nPartLen = USHRT_MAX ) const;

    void SetPhysFont( OutputDevice *pOut ) const;
//STRIP001  Font ChgPhysFont( OutputDevice *pOut ) const;

//STRIP001  Size GetCapitalSize( const OutputDevice *pOut, const String &rTxt,
//STRIP001                        const USHORT nIdx, const USHORT nLen) const;
//STRIP001  void DrawCapital( OutputDevice *pOut, const Point &rPos, const String &rTxt,
//STRIP001                    const USHORT nIdx, const USHORT nLen ) const;

//STRIP001  Size GetPhysTxtSize( const OutputDevice *pOut, const String &rTxt,
//STRIP001                       const USHORT nIdx, const USHORT nLen ) const;

    Size GetPhysTxtSize( const OutputDevice *pOut, const String &rTxt );

//STRIP001  Size GetTxtSize( const OutputDevice *pOut, const String &rTxt,
//STRIP001                    const USHORT nIdx = 0, const USHORT nLen = STRING_LEN );

//STRIP001  void DrawText( OutputDevice *pOut, const Point &rPos, const String &rTxt,
//STRIP001             const USHORT nIdx = 0, const USHORT nLen = STRING_LEN ) const;

    void QuickDrawText( OutputDevice *pOut, const Point &rPos, const String &rTxt,
               const USHORT nIdx = 0, const USHORT nLen = STRING_LEN, const long* pDXArray = NULL ) const;

    Size QuickGetTextSize( const OutputDevice *pOut, const String &rTxt,
                         const USHORT nIdx, const USHORT nLen, long* pDXArray = NULL ) const;

//STRIP001  void DrawPrev( OutputDevice* pOut, Printer* pPrinter,
//STRIP001                 const Point &rPos, const String &rTxt,
//STRIP001                 const USHORT nIdx = 0, const USHORT nLen = STRING_LEN ) const;

#endif // !REDUCEDSVXFONT
//STRIP001  static void DrawArrow( OutputDevice &rOut, const Rectangle& rRect,
//STRIP001      const Size& rSize, const Color& rCol, BOOL bLeft );
    SvxFont&    operator=( const SvxFont& rFont );
    SvxFont&    operator=( const Font& rFont );
};

}//end of namespace binfilter
#endif // #ifndef   _SVX_SVXFONT_HXX

