/*************************************************************************
 *
 *  $RCSfile: svx_svditer.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 16:23:16 $
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

#ifndef _SVDITER_HXX
#include "svditer.hxx"
#endif

// auto strip #ifndef _SVDPAGE_HXX
// auto strip #include "svdpage.hxx"
// auto strip #endif

// auto strip #ifndef _SVDOBJ_HXX
// auto strip #include "svdobj.hxx"
// auto strip #endif

// #99190#
#ifndef _E3D_SCENE3D_HXX
#include "scene3d.hxx"
#endif
namespace binfilter {

/*N*/ SdrObjListIter::SdrObjListIter(const SdrObjList& rObjList, SdrIterMode eMode, BOOL bReverse)
/*N*/ : maObjList(1024, 64, 64),
/*N*/   mnIndex(0L),
/*N*/   mbReverse(bReverse)
/*N*/ {
/*N*/   ImpProcessObjectList(rObjList, eMode);
/*N*/   Reset();
/*N*/ }

/*N*/ SdrObjListIter::SdrObjListIter(const SdrObject& rGroup, SdrIterMode eMode, BOOL bReverse)
/*N*/ : maObjList(1024, 64, 64),
/*N*/   mnIndex(0L),
/*N*/   mbReverse(bReverse)
/*N*/ {
/*N*/   ImpProcessObjectList(*rGroup.GetSubList(), eMode);
/*N*/   Reset();
/*N*/ }

/*N*/ void SdrObjListIter::ImpProcessObjectList(const SdrObjList& rObjList, SdrIterMode eMode)
/*N*/ {
/*N*/   for(sal_uInt32 a(0L); a < rObjList.GetObjCount(); a++)
/*N*/   {
/*N*/       SdrObject* pObj = rObjList.GetObj(a);
/*N*/       sal_Bool bIsGroup(pObj->IsGroupObject());
/*N*/
/*N*/       // #99190# 3D objects are no group objects, IsGroupObject()
/*N*/       // only tests if pSub is not null ptr :-(
/*N*/       if(bIsGroup && pObj->ISA(E3dObject) && !pObj->ISA(E3dScene))
/*N*/           bIsGroup = sal_False;
/*N*/
/*N*/       if(eMode != IM_DEEPNOGROUPS || !bIsGroup)
/*N*/           maObjList.Insert(pObj, LIST_APPEND);
/*N*/
/*N*/       if(bIsGroup && eMode != IM_FLAT)
/*N*/           ImpProcessObjectList(*pObj->GetSubList(), eMode);
/*N*/   }
/*N*/ }

}
