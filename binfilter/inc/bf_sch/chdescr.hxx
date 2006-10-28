/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: chdescr.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 02:46:30 $
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

#ifndef _SCH_CHTDESCR_HXX_
#define _SCH_CHTDESCR_HXX_

//STRIP008 class SdrObjList;
//STRIP008 class SchObjGroup;
//STRIP008 class ChartAxis;
class SfxItemSet;

#ifndef _SVDOBJ_HXX //autogen wg. SdrObject
#include <bf_svx/svdobj.hxx>
#endif

#include "adjust.hxx"
#include "tools/solar.h"
#ifndef _SV_GEN_HXX //autogen
#include <tools/gen.hxx>
#endif
#include "schattr.hxx"
#ifndef _SVX_CHRTITEM_HXX //autogen
#define ITEMID_DOUBLE           0
#define ITEMID_CHARTTEXTORDER   SCHATTR_TEXT_ORDER
#define ITEMID_CHARTTEXTORIENT  SCHATTR_TEXT_ORIENT
#define ITEMID_CHARTLEGENDPOS   SCHATTR_LEGEND_POS
#define ITEMID_CHARTDATADESCR   SCHATTR_DATADESCR_DESCR
#include <bf_svx/chrtitem.hxx>
#endif
#ifndef _SVX_VECTOR3D_HXX //autogen
#include <goodies/vector3d.hxx>
#endif

#include <float.h>      // for DBL_MIN
class Matrix4D;
namespace binfilter {
class SdrObjList;
class SchObjGroup;
class ChartAxis;
class ChartModel;
class ChartScene;

struct DataDescription
{
public:
    Vector3D          aTextPos3D;
    Point             aTextPos2D;
    double            fValue;
    SvxChartDataDescr eDescr;
    ChartAdjust       eAdjust;
    BOOL              bSymbol;
    BOOL              bShow;
    SdrObject         *pLabelObj;

    DataDescription() :                     // (BM) default constructor
        aTextPos3D( 0, 0, 0 ),
        aTextPos2D( 0, 0 ),
        fValue( DBL_MIN ),
        eDescr( CHDESCR_NONE ),
        eAdjust( CHADJUST_CENTER_CENTER ),
        bSymbol( FALSE ),
        bShow( FALSE ),
        pLabelObj( NULL )
    {}
};

class ChartDataDescription
{

    long mnRows;
    long mnCols;
    ChartModel* mpModel;
    SdrObjList** mpDescrLists;
    SdrObjList*  mpList;
    DataDescription* mpDescrArray;
    BOOL mbEnable;
    SchObjGroup** mpDescrGroups;
    void Dirty2D(BOOL bRowDescr);

public:

    BOOL Enabled() { return mbEnable; }
    void Build( BOOL bRowDescr=TRUE );  // insert data description in list (i.e. page)

    void Build3D( ChartScene* pScene, Matrix4D* pMatrix=NULL );
    DataDescription* Insert( long nCol, long nRow, const SfxItemSet& rAttr, Point aPos,
                             BOOL bPercent, ChartAdjust eAdjust, ChartAxis* pAxis);

    ChartDataDescription( long nCols, long nRows, SdrObjList *pList, ChartModel* mpModel, BOOL bEnable=TRUE );
    ~ChartDataDescription();
};

} //namespace binfilter
#endif


