/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: objadj.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 02:49:05 $
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

#ifndef _SCH_OBJADJ_HXX
#define _SCH_OBJADJ_HXX

#ifndef _SCH_ADJUST_HXX
#include "adjust.hxx"
#endif

#ifndef _SVX_CHRTITEM_HXX //autogen
#include <bf_svx/chrtitem.hxx>
#endif
#ifndef _SVDOBJ_HXX //autogen
#include <bf_svx/svdobj.hxx>
#endif
#ifndef _STREAM_HXX //autogen
#include <tools/stream.hxx>
#endif
namespace binfilter {


/*************************************************************************
|*
|* Ausrichtung von Chart-Objekten
|*
\************************************************************************/

class SchObjectAdjust : public SdrObjUserData
{
    ChartAdjust         eAdjust;    // Ausrichtung
    SvxChartTextOrient  eOrient;    // Orientierung

public:
    SchObjectAdjust();
    SchObjectAdjust(ChartAdjust eAdj, SvxChartTextOrient eOr);

    virtual SdrObjUserData* Clone(SdrObject *pObj) const;

    virtual void WriteData(SvStream& rOut);
    virtual void ReadData(SvStream& rIn);

    void SetAdjust(ChartAdjust eAdj) { eAdjust = eAdj; }
    ChartAdjust GetAdjust() { return eAdjust; }

    void SetOrient(SvxChartTextOrient eOr) { eOrient = eOr; }
    SvxChartTextOrient GetOrient() { return eOrient; }
};

/*************************************************************************
|*
|* Tool-Funktion fuer Objekt-Ausrichtung
|*
\************************************************************************/

extern SchObjectAdjust* GetObjectAdjust(const SdrObject& rObj);

} //namespace binfilter
#endif  // _SCH_OBJADJ_HXX


