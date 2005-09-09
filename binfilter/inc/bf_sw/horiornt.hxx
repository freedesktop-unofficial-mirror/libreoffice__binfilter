/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: horiornt.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 16:11:05 $
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

#ifndef _HORIORNT_HXX
#define _HORIORNT_HXX
namespace binfilter {


//SwFmtHoriOrient, wie und woran orientiert --
//  sich der FlyFrm in der Hoizontalen ----------

enum SwHoriOrient
{
    HORI_NONE,      //Der Wert in nYPos gibt die RelPos direkt an.
    HORI_RIGHT,     //Der Rest ist fuer automatische Ausrichtung.
    HORI_CENTER,
    HORI_LEFT,
    HORI_INSIDE,
    HORI_OUTSIDE,
    HORI_FULL,          //Spezialwert fuer Tabellen
    HORI_LEFT_AND_WIDTH  //Auch fuer Tabellen

    //Die Verwendung fuer FlyFrms ist klar. Fuer Tabellen ist die
    //Auswertung folgendermassen definiert:
    //NONE                == Die Randattribute zaehlen.
    //LEFT, CENTER, RIGHT == Wunschbreite wird falls moegliche eingehalten
    //                       und wenn noch Platz zur Verfuegung steht wird
    //                       ausgerichtet.
    //FULL                == Die Tabelle nutzt die ganze verfuegbare Breite.
    //LEFT_AND_WIDTH      == Linker Rand und Wunschbreite werden beruecksichtigt.
};



} //namespace binfilter
#endif

