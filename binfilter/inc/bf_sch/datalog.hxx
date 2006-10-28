/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: datalog.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 02:47:26 $
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
#ifndef _SCH_DATALOG
#define _SCH_DATALOG

#include "memchrt.hxx"
#include <float.h>
#include <math.h>
#define SCH_DATALOG_ANY -1
namespace binfilter {

class SchDataLogBook
{
    long* mpRowCoordinates;
    long* mpColCoordinates;

    long dummy;

    long mnRows;
    long mnCols;
    long mnColsInitial;
    long mnRowsInitial;

    long mnRowsAdded;
    long mnColsAdded;
    long mnRowsLeft;
    long mnColsLeft;

    BOOL mbValid;
    BOOL mbRowChanged;
    BOOL mbColChanged;
    BOOL mbGetCol;

    void IncreaseRowCount();
    void IncreaseColCount();

public:

     void Reset();
     SchDataLogBook(const SchMemChart& aMemChart);
    ~SchDataLogBook();






    //Get*Id MUSS ..._ANY fuer nicht existierende Elemente zurueckgeben:
};

} //namespace binfilter
#endif
