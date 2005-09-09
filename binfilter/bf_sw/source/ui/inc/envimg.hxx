/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: envimg.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 05:30:57 $
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
#ifndef _ENVIMG_HXX
#define _ENVIMG_HXX

#ifndef _SFXPOOLITEM_HXX //autogen
#include <svtools/poolitem.hxx>
#endif
// auto strip #ifndef _UTL_CONFIGITEM_HXX_
// auto strip #include <unotools/configitem.hxx>
// auto strip #endif
namespace binfilter {

// enum -----------------------------------------------------------------------

enum SwEnvAlign
{
    ENV_HOR_LEFT = 0,
    ENV_HOR_CNTR,
    ENV_HOR_RGHT,
    ENV_VER_LEFT,
    ENV_VER_CNTR,
    ENV_VER_RGHT
};

// class SwEnvItem ------------------------------------------------------------

class SwEnvItem : public SfxPoolItem
{
public:

    ::rtl::OUString   aAddrText;       // Text fuer Empfaenger
    sal_Bool        bSend;           // Absender?
    ::rtl::OUString     aSendText;       // Text fuer Absender
    sal_Int32       lAddrFromLeft;   // Linker Abstand fuer Empfaenger (twips)
    sal_Int32       lAddrFromTop;    // Oberer Abstand fuer Empfaenger (twips)
    sal_Int32       lSendFromLeft;   // Linker Abstand fuer Absender   (twips)
    sal_Int32       lSendFromTop;    // Oberer Abstand fuer Absender   (twips)
    sal_Int32       lWidth;          // Breite des Umschlags           (twips)
    sal_Int32       lHeight;         // Hoehe  des Umschlags           (twips)
    SwEnvAlign      eAlign;          // Ausrichtung beim Einzug
    sal_Bool        bPrintFromAbove; // Von oben drucken?
    sal_Int32       lShiftRight;     // Verschiebung nach rechts       (twips)
    sal_Int32       lShiftDown;      // Verschiebung nach unten        (twips)

    SwEnvItem();
    SwEnvItem(const SwEnvItem& rItem);

    TYPEINFO();

//STRIP001  SwEnvItem& operator =(const SwEnvItem& rItem);

    virtual int operator ==(const SfxPoolItem& rItem) const;

    virtual SfxPoolItem*     Clone(SfxItemPool* = 0) const;
//STRIP001     virtual BOOL             QueryValue( ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 ) const;
//STRIP001  virtual BOOL             PutValue( const ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 );
};

// class SwEnvCfgItem -------------------------------------------------------
//STRIP001 class SwEnvCfgItem : public ::utl::ConfigItem
//STRIP001 {
//STRIP001  SwEnvItem aEnvItem;

//STRIP001  ::com::sun::star::uno::Sequence<rtl::OUString> GetPropertyNames();
//STRIP001 public:
//STRIP001  SwEnvCfgItem();
//STRIP001  ~SwEnvCfgItem();

//STRIP001  SwEnvItem& GetItem() {return aEnvItem;}

//STRIP001  virtual void            Commit();
//STRIP001 };
} //namespace binfilter
#endif

