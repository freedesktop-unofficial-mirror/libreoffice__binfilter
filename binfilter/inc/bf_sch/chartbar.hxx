/*************************************************************************
 *
 *  $RCSfile: chartbar.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 08:25:24 $
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
#ifndef SCH_CHARTBAR_HXX
#define SCH_CHARTBAR_HXX
class Rectangle;
namespace binfilter {

class ChartModel;
class ChartAxis;
//Achtung! evtl. wird der default-Zuweisungsoperator benutzt!
//bei Erweiterungen bedenken! ganz wichtig!
class ChartBarDescriptor
{
    ChartAxis* mpAxis;
    ChartModel* mpModel;
    long nOverlapPercent;
    long nGapPercent;

    long nOver;      //Position des nächsten Balkens, kann gleich nBarWidth sein
    long nGap;       //Größe der Lücke
    long nPartWidth; //gesamte Breite je Spalte mit Gap
    long nColWidth;  //    "     "     "   "    ohne Gap
    long nBarWidth;  //Breite eines einzelnen Balkens
    long nCnt;       //Anzahl der Elemente, die der Berechnung zugrunde liegen

    long nCurrent;
    long nLeft;

public:

    inline void Assign(ChartModel* pModel,ChartAxis* pAxis)
    {
        mpModel=pModel;
        mpAxis=pAxis;
        SetGap(nGapPercent);//StarOne: Diese Eigenschaften hängen als Attribute an der Achse
        SetOverlap(nOverlapPercent);
    };
    void SetOverlap(long nPercent);
    long GetOverlap() const;
    long GetGap() const;
    void SetGap(long nPercent);
//STRIP001     void ChangeModel( ChartModel* pNewModel );

    ChartBarDescriptor(long nOverlap=0,long nGap=100):
        mpAxis(NULL),
        nOverlapPercent(nOverlap),
        nGapPercent(nGap)
    {
    }
    ChartBarDescriptor(const Rectangle& aRect,long nColCnt,long nRowCnt,long nOverlap=0,long nGap=100):
        mpAxis(NULL),
        nOverlapPercent(nOverlap),
        nGapPercent(nGap)
    {
        Create(aRect,nColCnt,nRowCnt);
    }

    ~ChartBarDescriptor(){};

    /// copy CTOR using the new model given
    ChartBarDescriptor( const ChartBarDescriptor& rSrc, ChartModel* pNewModel );

    inline long Middle()                      //aktuelle Spaltenmitte
    {
        return (nLeft + (nPartWidth - nGap)/2 );
    };
    inline long NextCol()                     //eine Spalte weiterschalten
    {
        nCurrent = nLeft + nPartWidth;
        nLeft = nCurrent;
        return nCurrent;
    };
    inline long BarLeft()
    {
        return nCurrent;
    };          //linke  BarPosition
    inline long BarRight()
    {
        return nCurrent+nBarWidth;
    };//rechte BarPsoition
    inline long BarWidth()
    {
        return nBarWidth;
    };
    inline long BarTop()
    {
        return nCurrent+nBarWidth;
    };//obere  BarPsoition
    inline long BarBottom()
    {
        return nCurrent;
    };          //untere BarPosition

    inline long NextBar() //innerhalb der Spalte einen Balken weiterschalten
    {
        nCurrent+=nOver;//if(nOver)nCurrent+=nOver;else nCurrent+=nBarWidth;
        return nCurrent;
    };

    void Create(const Rectangle& aRect,long nColCnt,long nRowCnt);
};
} //namespace binfilter
#endif


