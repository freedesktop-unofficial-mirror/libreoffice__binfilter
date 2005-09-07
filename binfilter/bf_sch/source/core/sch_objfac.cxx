/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sch_objfac.cxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-07 21:59:09 $
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

#pragma hdrstop

#include "axisid.hxx"
#include "schgroup.hxx"
#include "objfac.hxx"
#include "objid.hxx"
#include "objadj.hxx"
#include "datarow.hxx"
#include "datapoin.hxx"
// auto strip #include "lightfac.hxx"
#include "glob.hxx"
namespace binfilter {


/*************************************************************************
|*
|* Konstruktor
|*
\************************************************************************/

/*N*/ SchObjFactory::SchObjFactory() :
/*N*/   bInserted(FALSE)
/*N*/ {
/*N*/ }

/*************************************************************************
|*
|* Chart-interne Objekte erzeugen
|*
\************************************************************************/

/*N*/ IMPL_LINK( SchObjFactory, MakeObject, SdrObjFactory*, pObjFactory)
/*N*/ {
/*N*/   if (pObjFactory->nInventor == SchInventor &&
/*N*/       pObjFactory->nIdentifier == SCH_OBJGROUP_ID)
/*N*/       pObjFactory->pNewObj = new SchObjGroup;
/*N*/
/*N*/   return 0;
/*N*/ }

/*************************************************************************
|*
|* Chart-Userdata erzeugen
|*
\************************************************************************/

/*N*/ IMPL_LINK( SchObjFactory, MakeUserData, SdrObjFactory* ,pObjFactory)
/*N*/ {
/*N*/   if (pObjFactory->nInventor == SchInventor)
/*N*/       switch (pObjFactory->nIdentifier)
/*N*/       {
/*N*/           case SCH_OBJECTID_ID:
/*N*/               pObjFactory->pNewData = new SchObjectId;
/*N*/               break;
/*N*/
/*N*/           case SCH_OBJECTADJUST_ID:
/*N*/               pObjFactory->pNewData = new SchObjectAdjust;
/*N*/               break;
/*N*/
/*N*/           case SCH_DATAROW_ID:
/*N*/               pObjFactory->pNewData = new SchDataRow;
/*N*/               break;
/*N*/
/*N*/           case SCH_DATAPOINT_ID:
/*N*/               pObjFactory->pNewData = new SchDataPoint;
/*N*/               break;
/*N*/
/*N*/           case SCH_LIGHTFACTOR_ID:
/*?*/               {DBG_BF_ASSERT(0, "STRIP");} //STRIP001 pObjFactory->pNewData = new SchLightFactor;
/*?*/               DBG_ERROR("SCH_LIGHTFACTOR_ID no longer available");
/*?*/               break;
/*N*/
/*N*/           case SCH_AXIS_ID :
/*N*/               pObjFactory->pNewData = new SchAxisId;
/*N*/               break;
/*N*/       }
/*N*/
/*N*/       return 0;
/*N*/ }



}
