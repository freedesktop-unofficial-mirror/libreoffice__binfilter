/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sxmtritm.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 15:03:01 $
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
#ifndef _SXMTRITM_HXX
#define _SXMTRITM_HXX

#ifndef _SVDDEF_HXX //autogen
#include <bf_svx/svddef.hxx>
#endif

#ifndef _SDYNITM_HXX
#include <bf_svx/sdynitm.hxx>
#endif
namespace binfilter {

// Den Text quer zur Masslinie (90deg Drehung nach links)
class SdrMeasureTextRota90Item: public SdrYesNoItem {
public:
    SdrMeasureTextRota90Item(FASTBOOL bOn=FALSE): SdrYesNoItem(SDRATTR_MEASURETEXTROTA90,bOn) {}
    SdrMeasureTextRota90Item(SvStream& rIn): SdrYesNoItem(SDRATTR_MEASURETEXTROTA90,rIn) {}
};

// Das von mir berechnete TextRect um 180 deg drehen
// Der Text wird dann aber auch auf die andere Seite der
// Masslinie gebracht (wenn nicht Rota90)
class SdrMeasureTextUpsideDownItem: public SdrYesNoItem {
public:
    SdrMeasureTextUpsideDownItem(FASTBOOL bOn=FALSE): SdrYesNoItem(SDRATTR_MEASURETEXTUPSIDEDOWN,bOn) {}
    SdrMeasureTextUpsideDownItem(SvStream& rIn): SdrYesNoItem(SDRATTR_MEASURETEXTUPSIDEDOWN,rIn) {}
};

}//end of namespace binfilter
#endif
