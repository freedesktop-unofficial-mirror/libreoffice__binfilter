/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: chtscene.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 02:47:03 $
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

#ifndef _CHTSCENE_HXX
#define _CHTSCENE_HXX

#include <bf_svx/polysc3d.hxx>
#include <chtmodel.hxx>
namespace binfilter {

/*************************************************************************
|*
|* Basisklasse fuer 3D-Szenen
|* Die Ableitung von SchObjGroup erfolgt damit das Chart frei plaziert
|* werden kann. Die Komponenten von 2d-Charts sind auch SchObjGroups
|*
\************************************************************************/

//DECLARE_LIST(DescrList, E3dLabelObj*)//STRIP008 //DECLARE_LIST(DescrList, E3dLabelObj*);

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

    BOOL GetAskForLogicRect() {return bAskForLogicRect;}
    void SetAskForLogicRect(BOOL value) {bAskForLogicRect = value;}

    virtual void WriteData(SvStream& rOut) const;

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


} //namespace binfilter
#endif          // _E3D_SCENE3D_HXX
