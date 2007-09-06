/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sch_objadj.cxx,v $
 *
 *  $Revision: 1.7 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 11:17:32 $
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

#ifdef _MSC_VER
#pragma hdrstop
#endif

#include "objadj.hxx"
#include "glob.hxx"

#ifndef _TOOLS_DEBUG_HXX
#include <tools/debug.hxx>
#endif

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


/*************************************************************************
|*
|* Kopie erzeugen
|*
\************************************************************************/

/*N*/ SdrObjUserData* SchObjectAdjust::Clone(SdrObject *pObj) const
/*N*/ {
/*?*/   DBG_BF_ASSERT(0, "STRIP"); return NULL;//STRIP001 return new SchObjectAdjust(*this);
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
