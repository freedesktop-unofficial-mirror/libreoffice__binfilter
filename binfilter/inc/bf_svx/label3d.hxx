/*************************************************************************
 *
 *  $RCSfile: label3d.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 08:28:01 $
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

//STRIP001  virtual USHORT  GetHdlCount() const;
//STRIP001  virtual void    AddToHdlList(SdrHdlList& rHdlList) const;

    const SdrObject* Get2DLabelObj() const { return p2DLabelObj; }

    virtual void WriteData(SvStream& rOut) const;
    virtual void ReadData(const SdrObjIOHeader& rHead, SvStream& rIn);

//STRIP001  virtual void operator=(const SdrObject&);
    // TakeObjName...() ist fuer die Anzeige in der UI, z.B. "3 Rahmen selektiert".

//STRIP001  virtual void TakeObjNameSingul(String& rName) const;
//STRIP001  virtual void TakeObjNamePlural(String& rName) const;
};

}//end of namespace binfilter
#endif          // _E3D_LABEL3D_HXX
