/*************************************************************************
 *
 *  $RCSfile: chtscene.hxx,v $
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

#ifndef _CHTSCENE_HXX
#define _CHTSCENE_HXX

#include <bf_svx/polysc3d.hxx>
#include <chtmodel.hxx>

/*************************************************************************
|*
|* Basisklasse fuer 3D-Szenen
|* Die Ableitung von SchObjGroup erfolgt damit das Chart frei plaziert
|* werden kann. Die Komponenten von 2d-Charts sind auch SchObjGroups
|*
\************************************************************************/

//DECLARE_LIST(DescrList, E3dLabelObj*);

class ChartScene : public E3dPolyScene
{
  protected:
    ChartModel* pDoc;
    BOOL        bAskForLogicRect;
    Rectangle   Get3DDescrRect(E3dLabelObj *p3DObj,B3dCamera& rCamSet);

  public:

    TYPEINFO();
    ChartScene(ChartModel* pModel);
    virtual ~ChartScene();
    void Initialize();

    virtual Volume3D FitInSnapRect();
//STRIP001  virtual void operator=(const SdrObject& rObj);

    BOOL GetAskForLogicRect() {return bAskForLogicRect;}
    void SetAskForLogicRect(BOOL value) {bAskForLogicRect = value;}

    virtual void WriteData(SvStream& rOut) const;
//STRIP001  virtual void ReadData(const SdrObjIOHeader& rHead, SvStream& rIn);

    void InsertAllTitleText (DescrList         &rList,
                             E3dObject         *pGroup,
                             long              nAxisId);

    // just call parent? overloading deprecated?
    //  The following three methods call their respective equivalents of
    //  E3dObject.  This is necessary because they are overloaded in E3dScene
    //  with methods that do not what we want :-)
//      virtual USHORT  GetHdlCount (void)  const
//          {   return E3dObject::GetHdlCount();    }
//      virtual void    AddToHdlList    (SdrHdlList& rHdlList)  const
//          {   E3dObject::AddToHdlList (rHdlList); }
//      virtual FASTBOOL    HasSpecialDrag  (void)  const
//          {   return E3dObject::HasSpecialDrag ();    }

    void ReduceDescrList(DescrList& aList);
};


#endif          // _E3D_SCENE3D_HXX
