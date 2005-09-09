/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sxreaitm.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 15:04:53 $
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
#ifndef _SXREAITM_HXX
#define _SXREAITM_HXX

#ifndef _SVDDEF_HXX //autogen
#include <bf_svx/svddef.hxx>
#endif

#ifndef _SXFIITM_HXX
#include <bf_svx/sxfiitm.hxx>
#endif
namespace binfilter {

//------------------------------
// class SdrResizeXAllItem
//------------------------------
class SdrResizeXAllItem: public SdrFractionItem {
public:
    SdrResizeXAllItem(): SdrFractionItem(SDRATTR_RESIZEXALL,Fraction(1,1)) {}
    SdrResizeXAllItem(const Fraction& rFact): SdrFractionItem(SDRATTR_RESIZEXALL,rFact) {}
    SdrResizeXAllItem(SvStream& rIn): SdrFractionItem(SDRATTR_RESIZEXALL,rIn)    {}
};

//------------------------------
// class SdrResizeYAllItem
//------------------------------
class SdrResizeYAllItem: public SdrFractionItem {
public:
    SdrResizeYAllItem(): SdrFractionItem(SDRATTR_RESIZEYALL,Fraction(1,1)) {}
    SdrResizeYAllItem(const Fraction& rFact): SdrFractionItem(SDRATTR_RESIZEYALL,rFact) {}
    SdrResizeYAllItem(SvStream& rIn): SdrFractionItem(SDRATTR_RESIZEYALL,rIn)    {}
};

}//end of namespace binfilter
#endif
