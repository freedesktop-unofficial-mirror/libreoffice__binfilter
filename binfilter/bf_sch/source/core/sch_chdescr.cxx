/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file incorporates work covered by the following license notice:
 *
 *   Licensed to the Apache Software Foundation (ASF) under one or more
 *   contributor license agreements. See the NOTICE file distributed
 *   with this work for additional information regarding copyright
 *   ownership. The ASF licenses this file to you under the Apache
 *   License, Version 2.0 (the "License"); you may not use this file
 *   except in compliance with the License. You may obtain a copy of
 *   the License at http://www.apache.org/licenses/LICENSE-2.0 .
 */
#include <bf_svtools/eitem.hxx>

#include "chdescr.hxx"

#include "float.h"
#include "schgroup.hxx"
#include "chtscene.hxx"
namespace binfilter {

/*N*/ ChartDataDescription::ChartDataDescription(long nCols, long nRows, SdrObjList *pList,
/*N*/                                          ChartModel* pModel, BOOL bEnable) :
/*N*/       mnRows(nRows),
/*N*/       mnCols(nCols),
/*N*/       mpModel(pModel),
/*N*/       mpDescrLists(NULL),
/*N*/       mpList(pList),
/*N*/       mpDescrArray(NULL),
/*N*/       mbEnable(bEnable),
/*N*/       mpDescrGroups(NULL)
/*N*/ {
/*N*/ }

/*N*/ void ChartDataDescription::Build( BOOL bRowDescr )
/*N*/ {
/*N*/   Dirty2D( bRowDescr );
/*N*/   if(mpList && mpDescrGroups)
/*N*/   {
/*?*/       for( long nRow=0; nRow<mnRows; nRow++ )
/*?*/       {
/*?*/           if(mpDescrGroups[nRow])
/*?*/               mpList->NbcInsertObject( mpDescrGroups[nRow] );
/*?*/       }
/*?*/   }
/*N*/ }

/*N*/ void ChartDataDescription::Build3D( ChartScene *pScene, Matrix4D* pMatrix )
/*N*/ {
/*N*/   if(pScene && mpDescrGroups)
/*N*/   {
/*?*/       for( long nRow=0; nRow<mnRows; nRow++ )
/*?*/       {
/*?*/           for( long nCol=0; nCol<mnCols; nCol++ )
/*?*/           {
/*?*/               long nIndex = nCol + nRow * mnCols;
/*?*/               if( mpDescrArray[nIndex].fValue != DBL_MIN )
/*?*/               {
/*?*/                   mpDescrArray[nIndex].pLabelObj->SetMarkProtect(TRUE);
/*?*/                   E3dLabelObj* pLabel=new E3dLabelObj(mpDescrArray[nIndex].aTextPos3D,
/*?*/                                                       mpDescrArray[nIndex].pLabelObj);
/*?*/
/*?*/                   CHART_TRACE3( "Descr::Build3D TextPos = (%ld, %ld, %ld)",
/*?*/                                 mpDescrArray[ nIndex ].aTextPos3D.X(),
/*?*/                                 mpDescrArray[ nIndex ].aTextPos3D.Y(),
/*?*/                                 mpDescrArray[ nIndex ].aTextPos3D.Z() );
/*?*/
/*?*/                   pLabel->SetMarkProtect(TRUE);
/*?*/                   pScene->Insert3DObj(pLabel);
/*?*/                   if(pMatrix)
/*?*/                       pLabel->NbcSetTransform(*pMatrix);
/*?*/               }
/*?*/           }
/*?*/       }
/*?*/   }
/*N*/ }

/*N*/ ChartDataDescription::~ChartDataDescription()
/*N*/ {
/*N*/   if(mpDescrLists)
/*?*/       delete[] mpDescrLists;
/*N*/   if(mpDescrGroups)
/*?*/       delete[] mpDescrGroups;
/*N*/   if(mpDescrArray)
/*?*/       delete[] mpDescrArray;
/*N*/ }


/*N*/ void ChartDataDescription::Dirty2D( BOOL /*bRowDescr*/ )
/*N*/ {
/*N*/
/*N*/   if(mpDescrLists)
/*N*/   {
/*?*/       for( long nRow = 0; nRow < mnRows; nRow ++ )
/*?*/       {
/*?*/           if( mpDescrLists[nRow] )
/*?*/           {
/*?*/               for( long nCol = 0; nCol < mnCols; nCol++ )
/*?*/               {
/*?*/                       long nIndex = nCol + nRow * mnCols;
/*?*/                       if (mpDescrArray[nIndex].fValue != DBL_MIN)
/*?*/                           if (mpDescrArray[nIndex].pLabelObj)
/*?*/                               mpDescrLists[nRow]->NbcInsertObject(mpDescrArray[nIndex].pLabelObj);
/*?*/               }
/*?*/           }
/*?*/       }
/*N*/   }
/*N*/ }

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
