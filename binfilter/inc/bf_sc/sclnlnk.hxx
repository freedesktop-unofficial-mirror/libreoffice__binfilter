/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sclnlnk.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 11:27:45 $
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

#ifndef SC_LINECON_HXX
#define SC_LINECON_HXX
namespace binfilter {

struct ScLineStruct
{
    short nLeft;    // Breite der linken Linie
    short nMiddle;  // Breite des Zwischenraums
    short nRight;   // Breite der rechten Linie
};

//STRIP001 void ScLinkLine(const ScLineStruct& dLine,
//STRIP001              const ScLineStruct& ltLine,
//STRIP001              const ScLineStruct& lLine,
//STRIP001              const ScLineStruct& lbLine,
//STRIP001              const ScLineStruct& rtLine,
//STRIP001              const ScLineStruct& rLine,
//STRIP001              const ScLineStruct& rbLine,
//STRIP001              short* dxArr);

} //namespace binfilter
#endif

