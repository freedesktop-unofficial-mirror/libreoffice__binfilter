/*************************************************************************
 *
 *  $RCSfile: sch_axisid.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2004-05-05 16:39:51 $
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

#include "axisid.hxx"
#include "glob.hxx"
#ifndef _TOOLS_DEBUG_HXX
#include <tools/debug.hxx>
#endif
namespace binfilter {
/*************************************************************************
|*
|* Objekt-Id ermitteln;
|* Liefert -1, wenn das Objekt keine Id hat
|*
\************************************************************************/

//STRIP001 SchAxisId* GetAxisId (const SdrObject& rObj)
//STRIP001 {
//STRIP001  for (long i = 0;
//STRIP001            i < rObj.GetUserDataCount();
//STRIP001            i ++)
//STRIP001  {
//STRIP001      SdrObjUserData *pData = rObj.GetUserData(i);
//STRIP001
//STRIP001      if (pData && (pData->GetId() == SCH_AXIS_ID)) return (SchAxisId*) pData;
//STRIP001  }
//STRIP001
//STRIP001  return NULL;
//STRIP001 }

/*************************************************************************
|*
|* Objekt mit Id suchen;
|* liefert NULL, wenn kein Objekt gefunden wurde.
|*
\************************************************************************/

//STRIP001 SdrObject *GetObjWithAxisId (long             nAxisId,
//STRIP001                           const SdrObjList &rObjList,
//STRIP001                           long             *pIndex,
//STRIP001                           SdrIterMode      eMode)
//STRIP001 {
//STRIP001  long           nIndex = 0;
//STRIP001  SdrObjListIter aIterator (rObjList, eMode);
//STRIP001
//STRIP001  while (aIterator.IsMore ())
//STRIP001  {
//STRIP001      SdrObject *pObj    = aIterator.Next ();
//STRIP001      SchAxisId *pAxisId = GetAxisId (*pObj);
//STRIP001
//STRIP001      if (pAxisId && (pAxisId->AxisId () == nAxisId))
//STRIP001      {
//STRIP001          if (pIndex) *pIndex = nIndex;
//STRIP001          return pObj;
//STRIP001      }
//STRIP001
//STRIP001      nIndex++;
//STRIP001  }
//STRIP001
//STRIP001  return NULL;
//STRIP001 }

/*************************************************************************
|*
|* Konstruktor
|*
\************************************************************************/

/*N*/ SchAxisId::SchAxisId () :
/*N*/   SdrObjUserData (SchInventor, SCH_AXIS_ID, 0),
/*N*/   nAxisId (0)
/*N*/ {
/*N*/ }

/*************************************************************************
|*
|* Konstruktor
|*
\************************************************************************/

/*N*/ SchAxisId::SchAxisId (long nId) :
/*N*/   SdrObjUserData (SchInventor, SCH_AXIS_ID, 0),
/*N*/   nAxisId (nId)
/*N*/ {
/*N*/ }

/*************************************************************************
|*
|* Kopier-Konstruktor
|*
\************************************************************************/

//STRIP001 SchAxisId::SchAxisId (const SchAxisId &rAxisId) :
//STRIP001  SdrObjUserData (rAxisId),
//STRIP001  nAxisId (rAxisId.nAxisId)
//STRIP001 {
//STRIP001 }

/*************************************************************************
|*
|* Kopie erzeugen
|*
\************************************************************************/

/*N*/ SdrObjUserData* SchAxisId::Clone(SdrObject *pObj) const
/*N*/ {
/*?*/   DBG_BF_ASSERT(0, "STRIP"); return NULL;//STRIP001 return new SchAxisId (*this);
/*N*/ }

/*************************************************************************
|*
|* Daten in Stream schreiben
|*
\************************************************************************/

/*N*/ void SchAxisId::WriteData(SvStream& rOut)
/*N*/ {
/*N*/   SdrObjUserData::WriteData(rOut);
/*N*/
/*N*/   rOut << nAxisId;
/*N*/ }


/*************************************************************************
|*
|* Daten aus Stream lesen
|*
\************************************************************************/

/*N*/ void SchAxisId::ReadData(SvStream& rIn)
/*N*/ {
/*N*/   SdrObjUserData::ReadData(rIn);
/*N*/
/*N*/   rIn >> nAxisId;
/*N*/ }



}
