/*************************************************************************
 *
 *  $RCSfile: lspcitem.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 08:28:07 $
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
#ifndef _SVX_LSPCITEM_HXX
#define _SVX_LSPCITEM_HXX

// include ---------------------------------------------------------------

#ifndef _SFXENUMITEM_HXX //autogen
#include <svtools/eitem.hxx>
#endif
#ifndef _SVX_SVXENUM_HXX
#include <bf_svx/svxenum.hxx>
#endif

#ifndef _SVX_SVXIDS_HRC
#include <bf_svx/svxids.hrc>
#endif

class SvXMLUnitConverter;
#ifdef _USE_NAMESPACE
namespace rtl
{
#endif
    class OUString;
#ifdef _USE_NAMESPACE
}
#endif
namespace binfilter {

// class SvxLineSpacingItem ----------------------------------------------

/*
[Beschreibung]
Dieses Item beschreibt den Abstand zwischen den Zeilen.
*/

class SvxLineSpacingItem : public SfxEnumItemInterface
{
    friend SvStream& operator<<( SvStream&, SvxLineSpacingItem& ); //$ ostream

    short nInterLineSpace;
    USHORT nLineHeight;
    BYTE nPropLineSpace;
    SvxLineSpace eLineSpace;
    SvxInterLineSpace eInterLineSpace;

public:
    TYPEINFO();

    // Der Writer verlaesst sich auf eine Default-Hoehe von 200!
    // Eigentlich wuerde ich alle Werte mit 0 initialisieren, aber wer kann
    // die Folgen beim Writer absehen ?
    // => lieber einen krummen Wert als Default, aber der Programmierer
    // sieht, dass dort etwas besonderes passiert.
    SvxLineSpacingItem( USHORT nHeight = 200, const USHORT nId = ITEMID_LINESPACING );

    // "pure virtual Methoden" vom SfxPoolItem
    virtual int              operator==( const SfxPoolItem& ) const;
    virtual sal_Bool             QueryValue( ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 ) const;
    virtual sal_Bool             PutValue( const ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 );

//STRIP001  virtual SfxItemPresentation GetPresentation( SfxItemPresentation ePres,
//STRIP001                                  SfxMapUnit eCoreMetric,
//STRIP001                                  SfxMapUnit ePresMetric,
//STRIP001                                     String &rText, const IntlWrapper * = 0 ) const;

    virtual SfxPoolItem*     Clone( SfxItemPool *pPool = 0 ) const;
    virtual SfxPoolItem*     Create(SvStream &, USHORT) const;
    virtual SvStream&        Store(SvStream &, USHORT nItemVersion ) const;

    // Methoden zum Abfragen und Aendern
    // Interlinespace wird zur Hoehe addiert.
    inline short GetInterLineSpace() const { return nInterLineSpace; }
    inline void SetInterLineSpace( const short nSpace )
    {
        nInterLineSpace = nSpace;
        eInterLineSpace = SVX_INTER_LINE_SPACE_FIX;
    }

    // Bestimmt absolute oder minimale Zeilenhoehe.
    inline USHORT GetLineHeight() const { return nLineHeight; }
    inline void SetLineHeight( const USHORT nHeight )
    {
        nLineHeight = nHeight;
        eLineSpace = SVX_LINE_SPACE_MIN;
    }

    // Vergroessert oder verkleinert die Zeilenhoehe.
    const BYTE GetPropLineSpace() const { return nPropLineSpace; }
    inline void SetPropLineSpace( const BYTE nProp )
    {
        nPropLineSpace = nProp;
        eInterLineSpace = SVX_INTER_LINE_SPACE_PROP;
    }

    inline SvxLineSpace &GetLineSpaceRule() { return eLineSpace; }
    inline SvxLineSpace GetLineSpaceRule() const { return eLineSpace; }

    inline SvxInterLineSpace &GetInterLineSpaceRule() { return eInterLineSpace; }
    inline SvxInterLineSpace GetInterLineSpaceRule() const { return eInterLineSpace; }

    virtual USHORT          GetValueCount() const;
    virtual String          GetValueTextByPos( USHORT nPos ) const;
    virtual USHORT          GetEnumValue() const;
    virtual void            SetEnumValue( USHORT nNewVal );
};

}//end of namespace binfilter
#endif

