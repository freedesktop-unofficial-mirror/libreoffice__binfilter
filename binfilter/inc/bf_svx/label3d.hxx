/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: label3d.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 03:40:47 $
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

#ifndef _E3D_LABEL3D_HXX
#define _E3D_LABEL3D_HXX

#ifndef _E3D_PNTOBJ3D_HXX
#include <bf_svx/pntobj3d.hxx>
#endif
namespace binfilter {

class Viewport3D;
class E3dScene;
class E3dLabelObj;

/************************************************************************/

class E3dLabelObj;
DECLARE_LIST(E3dLabelList, E3dLabelObj*)//STRIP008 DECLARE_LIST(E3dLabelList, E3dLabelObj*);

/*************************************************************************
|*
|* Objekt zur Verknuepfung eines 2D-Labels mit einer 3D-Position.
|* Bei einer Transformation wird die neue Position des 2D-Objekts
|* mit SetAnchorPos gesetzt. Wenn das Objekt zu dieser Position
|* ausgerichtet werden soll (z.B. rechtsbuendig), kann das mittels
|* SetRelativePos erreicht werden.
|*
\************************************************************************/

class E3dLabelObj : public E3dPointObj
{
 // damit nicht jeder daran rumpfuschen kann...
 friend class E3dScene;
    SdrObject* GetMy2DLabelObj() { return p2DLabelObj; }

 protected:
    SdrObject* p2DLabelObj;

 public:
    TYPEINFO();
    // Eigentumsuebergang bei pLabelObj!
    E3dLabelObj(const Vector3D& aPos,
                SdrObject*      pLabelObj) :
        E3dPointObj(aPos),
        p2DLabelObj(pLabelObj)
    {
    }

    E3dLabelObj() :
        E3dPointObj(),
        p2DLabelObj(NULL)
    {
    }

    virtual ~E3dLabelObj();

    virtual void SetPage(SdrPage* pNewPage);
    virtual void SetModel(SdrModel* pNewModel);

    virtual UINT16 GetObjIdentifier() const;


    const SdrObject* Get2DLabelObj() const { return p2DLabelObj; }

    virtual void WriteData(SvStream& rOut) const;
    virtual void ReadData(const SdrObjIOHeader& rHead, SvStream& rIn);

    // TakeObjName...() ist fuer die Anzeige in der UI, z.B. "3 Rahmen selektiert".

};

}//end of namespace binfilter
#endif          // _E3D_LABEL3D_HXX
