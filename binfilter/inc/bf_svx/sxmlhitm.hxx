/*************************************************************************
 *
 *  $RCSfile: sxmlhitm.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 08:29:10 $
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
#ifndef _SXMLHITM_HXX
#define _SXMLHITM_HXX

#ifndef _SVDDEF_HXX //autogen
#include <bf_svx/svddef.hxx>
#endif

#ifndef _SDMETITM_HXX
#include <bf_svx/sdmetitm.hxx>
#endif
namespace binfilter {

/*************************************************************************/
/* Measure                                                               */
/*************************************************************************/
//                             ___
//    ?       100,00km       ?2mm = SdrMeasureHelplineOverhangItem
//    ?--------------------->?--
//    ?                      ?8mm = SdrMeasureLineDistItem
//    ?                      ?
//    浜様様様様様様?        ?--
//    ?            ?        ?SdrMeasureHelpline1/2LenItem
//    ?            藩様様様様?--
//    ?Zu bemassendes Objekt ?
//    藩様様様様様様様様様様様?

// Abstand der Masslinie zur Bezugskante (Norm=8mm)
// laesst sich auch draggen an den beiden Handles
// die auf den Pfeilspitzen liegen
class SdrMeasureLineDistItem: public SdrMetricItem {
public:
    SdrMeasureLineDistItem(long nVal=0): SdrMetricItem(SDRATTR_MEASURELINEDIST,nVal)  {}
    SdrMeasureLineDistItem(SvStream& rIn): SdrMetricItem(SDRATTR_MEASURELINEDIST,rIn) {}
};

// Ueberhang der Masshilfslinien an der Masslinie (Norm=2mm)
class SdrMeasureHelplineOverhangItem: public SdrMetricItem {
public:
    SdrMeasureHelplineOverhangItem(long nVal=0): SdrMetricItem(SDRATTR_MEASUREHELPLINEOVERHANG,nVal)  {}
    SdrMeasureHelplineOverhangItem(SvStream& rIn): SdrMetricItem(SDRATTR_MEASUREHELPLINEOVERHANG,rIn) {}
};

// Abstand der der Masshilfslinienenden zur Bezugskante
// Damit die Masshilfslinien nicht das Objekt beruehren
class SdrMeasureHelplineDistItem: public SdrMetricItem {
public:
    SdrMeasureHelplineDistItem(long nVal=0): SdrMetricItem(SDRATTR_MEASUREHELPLINEDIST,nVal)  {}
    SdrMeasureHelplineDistItem(SvStream& rIn): SdrMetricItem(SDRATTR_MEASUREHELPLINEDIST,rIn) {}
};

// Ueberlaenge der Hilfslinien ueber die Bezugskante
// laesst sich auch draggen an den beiden runden Handles,
// die sich default unter den beiden Referenzpunkten befinden
class SdrMeasureHelpline1LenItem: public SdrMetricItem {
public:
    SdrMeasureHelpline1LenItem(long nVal=0): SdrMetricItem(SDRATTR_MEASUREHELPLINE1LEN,nVal)  {}
    SdrMeasureHelpline1LenItem(SvStream& rIn): SdrMetricItem(SDRATTR_MEASUREHELPLINE1LEN,rIn) {}
};
class SdrMeasureHelpline2LenItem: public SdrMetricItem {
public:
    SdrMeasureHelpline2LenItem(long nVal=0): SdrMetricItem(SDRATTR_MEASUREHELPLINE2LEN,nVal)  {}
    SdrMeasureHelpline2LenItem(SvStream& rIn): SdrMetricItem(SDRATTR_MEASUREHELPLINE2LEN,rIn) {}
};

}//end of namespace binfilter
#endif
