/*************************************************************************
 *
 *  $RCSfile: sch_objadj.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:32:28 $
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

#pragma hdrstop

#include "objadj.hxx"
#include "glob.hxx"
namespace binfilter {




/*************************************************************************
|*
|* Objekt-Ausrichting ermitteln
|*
\************************************************************************/

/*N*/ SchObjectAdjust* GetObjectAdjust(const SdrObject& rObj)
/*N*/ {
/*N*/   for (USHORT i = 0; i < rObj.GetUserDataCount(); i++)
/*N*/   {
/*N*/       SdrObjUserData *pData = rObj.GetUserData(i);
/*N*/       if (pData && pData->GetId() == SCH_OBJECTADJUST_ID)
/*N*/           return (SchObjectAdjust*)pData;
/*N*/   }
/*N*/
/*?*/   return NULL;
/*N*/ }

/*************************************************************************
|*
|* Konstruktor
|*
\************************************************************************/

/*N*/ SchObjectAdjust::SchObjectAdjust() :
/*N*/   SdrObjUserData(SchInventor, SCH_OBJECTADJUST_ID, 1),
/*N*/   eAdjust(CHADJUST_TOP_LEFT),
/*N*/   eOrient(CHTXTORIENT_STANDARD)
/*N*/ {
/*N*/ }

/*************************************************************************
|*
|* Konstruktor
|*
\************************************************************************/

/*N*/ SchObjectAdjust::SchObjectAdjust(ChartAdjust eAdj,
/*N*/                                SvxChartTextOrient eOr) :
/*N*/   SdrObjUserData(SchInventor, SCH_OBJECTADJUST_ID, 1),
/*N*/   eAdjust(eAdj),
/*N*/   eOrient(eOr)
/*N*/ {
/*N*/ }

/*************************************************************************
|*
|* Kopier-Konstruktor
|*
\************************************************************************/

//STRIP001 SchObjectAdjust::SchObjectAdjust(const SchObjectAdjust& rObjectAdjust) :
//STRIP001  SdrObjUserData(rObjectAdjust),
//STRIP001  eAdjust(rObjectAdjust.eAdjust),
//STRIP001  eOrient(rObjectAdjust.eOrient)
//STRIP001 {
//STRIP001 }

/*************************************************************************
|*
|* Kopie erzeugen
|*
\************************************************************************/

/*N*/ SdrObjUserData* SchObjectAdjust::Clone(SdrObject *pObj) const
/*N*/ {
/*?*/   DBG_ASSERT(0, "STRIP"); return NULL;//STRIP001 return new SchObjectAdjust(*this);
/*N*/ }

/*************************************************************************
|*
|* Daten in Stream schreiben
|*
\************************************************************************/

/*N*/ void SchObjectAdjust::WriteData(SvStream& rOut)
/*N*/ {
/*N*/   SdrObjUserData::WriteData(rOut);
/*N*/
/*N*/   rOut << (INT16)eAdjust;
/*N*/   rOut << (INT16)eOrient;
/*N*/ }

/*************************************************************************
|*
|* Daten aus Stream lesen
|*
\************************************************************************/

/*N*/ void SchObjectAdjust::ReadData(SvStream& rIn)
/*N*/ {
/*N*/   SdrObjUserData::ReadData(rIn);
/*N*/
/*N*/   INT16 nInt16;
/*N*/
/*N*/   rIn >> nInt16; eAdjust = (ChartAdjust)nInt16;
/*N*/
/*N*/   if (nVersion < 1)
/*?*/       eOrient = CHTXTORIENT_STANDARD;
/*N*/   else
/*N*/   {
/*N*/       rIn >> nInt16; eOrient = (SvxChartTextOrient)nInt16;
/*N*/   }
/*N*/
/*N*/ }



}
