/*************************************************************************
 *
 *  $RCSfile: chdescr.hxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:23:26 $
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

#ifndef _SCH_CHTDESCR_HXX_
#define _SCH_CHTDESCR_HXX_

class SdrObjList;
class SchObjGroup;
class ChartAxis;
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
//STRIP001  void Create(long nRow);
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

#endif


