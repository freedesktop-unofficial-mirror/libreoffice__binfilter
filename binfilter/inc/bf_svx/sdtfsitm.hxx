/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sdtfsitm.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 03:59:51 $
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
#ifndef _SDTFSITM_HXX
#define _SDTFSITM_HXX

#ifndef _SFXENUMITEM_HXX //autogen
#include <svtools/eitem.hxx>
#endif

#ifndef _SVDDEF_HXX //autogen
#include <bf_svx/svddef.hxx>
#endif
namespace binfilter {

enum SdrFitToSizeType {SDRTEXTFIT_NONE,         // - kein FitToSize
                       SDRTEXTFIT_PROPORTIONAL, // - Alle Buchstaben proportional umgroessern
                       SDRTEXTFIT_ALLLINES,     // - Zus. jede Zeile separat in der Breite stretchen
                       SDRTEXTFIT_RESIZEATTR};  // - Bei Rahmenumgroesserung (ausser Autogrow) wird
                                                //   die Schriftgroesse umattributiert (hart)

// Bei SDRTEXTFIT_PROPORTIONAL und SDRTEXTFIT_ALLLINES gibt es kein AutoGrow und
// keine automatischen Umbrueche.
// Ist SDRTEXTFIT_RESIZEATTR gesetzt, so wird beim umgroessern des Textrahmens
// (ausser bei AutoGrow) die Schrift durch harte Attributierung ebenfalls
// umgegroessert.
// Bei AutoGrowingWidth gibt es ebenfalls keine automatischen Umbrueche (erst bei
// TextMaxFrameWidth).

//--------------------------------
// class SdrTextFitToSizeTypeItem
//--------------------------------
class SdrTextFitToSizeTypeItem: public SfxEnumItem {
public:
    TYPEINFO();
    SdrTextFitToSizeTypeItem(SdrFitToSizeType eFit=SDRTEXTFIT_NONE): SfxEnumItem(SDRATTR_TEXT_FITTOSIZE,eFit) {}
    SdrTextFitToSizeTypeItem(SvStream& rIn)                        : SfxEnumItem(SDRATTR_TEXT_FITTOSIZE,rIn)  {}
    virtual SfxPoolItem*     Clone(SfxItemPool* pPool=NULL) const;
    virtual SfxPoolItem*     Create(SvStream& rIn, USHORT nVer) const;
    virtual USHORT           GetValueCount() const; // { return 4; }
            SdrFitToSizeType GetValue() const      { return (SdrFitToSizeType)SfxEnumItem::GetValue(); }

    virtual sal_Bool             QueryValue( ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 ) const;
    virtual sal_Bool             PutValue( const ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 );

};

}//end of namespace binfilter
#endif
