/*************************************************************************
 *
 *  $RCSfile: svdoole2.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: hjs $ $Date: 2004-06-28 12:36:46 $
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

#ifndef _SVDOOLE2_HXX
#define _SVDOOLE2_HXX

#ifndef _COM_SUN_STAR_FRAME_XMODEL_HPP_
#include <com/sun/star/frame/XModel.hpp>
#endif

#ifndef _SVDORECT_HXX
#include <bf_svx/svdorect.hxx>
#endif
#ifndef _GRAPH_HXX //autogen
#include <vcl/graph.hxx>
#endif
#ifndef _GDIMTF_HXX //autogen
#include <vcl/gdimtf.hxx>
#endif
#ifndef _SOT_STORAGE_HXX
#include <sot/storage.hxx>
#endif
class SvPersist;
class SvInPlaceObjectRef;
class SvEmbeddedInfoObject;
namespace binfilter {

//************************************************************
//   Vorausdeklarationen
//************************************************************


// ***********************************************************
//  SvInPlaceObject dummy implementation for displaying
//  plugins with the StarOffice Player without so3
// ***********************************************************

//************************************************************
//   SdrOle2Obj
//************************************************************

class SvxUnoShapeModifyListener;

class SdrOle2ObjImpl;

class SdrOle2Obj :  public SdrRectObj
{
protected:
    SvInPlaceObjectRef*         ppObjRef;    // Referenz auf Objekt

    String                      aName;       // Name des Objektes

    Graphic*                    pGraphic;
    String                      aProgName;

    // wg. Kompatibilitaet erstmal am SdrTextObj
    BOOL                        bFrame : 1;
    BOOL                        bInDestruction : 1;

    SdrOle2ObjImpl*             mpImpl;

    SvxUnoShapeModifyListener*  pModifyListener;

protected:

/*NBFF*/    void ImpSetVisAreaSize();
//STRIP001     void ImpAssign( const SdrObject& rObj, SdrPage* pNewPage = NULL, SdrModel* pNewModel = NULL );
//STRIP001     void ImpCopyObject( SvPersist& rSrcPersist, SvPersist& rDstPersist, String& rPersistName );

//STRIP001  void CreatePersistName( SvPersist* pPers );
    void Init();

public:
    TYPEINFO();

    SdrOle2Obj(FASTBOOL bFrame_=FALSE);
//STRIP001  SdrOle2Obj(const SvInPlaceObjectRef& rNewObjRef, FASTBOOL bFrame_=FALSE);
    SdrOle2Obj(const SvInPlaceObjectRef& rNewObjRef, const String& rNewObjName, FASTBOOL bFrame_=FALSE);
    SdrOle2Obj(const SvInPlaceObjectRef& rNewObjRef, const String& rNewObjName, const Rectangle& rNewRect, FASTBOOL bFrame_=FALSE);
    virtual ~SdrOle2Obj();

    // Ein OLE-Zeichenobjekt kann eine StarView-Grafik beinhalten.
    // Diese wird angezeigt, wenn das OLE-Objekt leer ist.
    void        SetGraphic(const Graphic* pGrf);
    Graphic*    GetGraphic() const { return pGraphic; }

    // OLE object has got a separate PersistName member now;
    // !!! use ::SetPersistName( ... ) only, if you know what you do !!!
    String      GetPersistName() const;
    void        SetPersistName( const String& rPersistName );

//STRIP001  virtual FASTBOOL HasSetName() const;

//STRIP001  virtual void    SetName(const String& rStr);
    virtual String  GetName() const;

    // Einem SdrOle2Obj kann man ein Applikationsnamen verpassen, den man
    // spaeter wieder abfragen kann (SD braucht das fuer Praesentationsobjekte).
    void SetProgName(const String& rNam) { aProgName=rNam; }
    const String& GetProgName() const { return aProgName; }
    FASTBOOL IsEmpty() const;
    void SetObjRef(const SvInPlaceObjectRef& rNewObjRef);
    const SvInPlaceObjectRef& GetObjRef() const;

    virtual void SetPage(SdrPage* pNewPage);
    virtual void SetModel(SdrModel* pModel);

    /** Change the IsClosedObj attribute

        @param bIsClosed
        Whether the OLE object is closed, i.e. has opaque background
     */
    void SetClosedObj( bool bIsClosed );

//STRIP001  virtual void TakeObjInfo(SdrObjTransformInfoRec& rInfo) const;
    virtual UINT16 GetObjIdentifier() const;
//STRIP001  virtual FASTBOOL Paint(ExtOutputDevice& rOut, const SdrPaintInfoRec& rInfoRec) const;
    virtual SdrObject* CheckHit(const Point& rPnt, USHORT nTol, const SetOfByte* pVisiLayer) const;

//STRIP001     virtual SdrObject* Clone(SdrPage* pPage, SdrModel* pModel) const;

//STRIP001     virtual void TakeObjNameSingul(String& rName) const;
//STRIP001  virtual void TakeObjNamePlural(String& rName) const;

//STRIP001  virtual void operator=(const SdrObject& rObj);
//STRIP001  virtual FASTBOOL HasSpecialDrag() const;

    virtual void NbcMove(const Size& rSize);
    virtual void NbcResize(const Point& rRef, const Fraction& xFact, const Fraction& yFact);
    virtual void NbcSetSnapRect(const Rectangle& rRect);
    virtual void NbcSetLogicRect(const Rectangle& rRect);
//STRIP001  virtual void SetGeoData(const SdrObjGeoData& rGeo);

    // fuer Import:
    FASTBOOL HasGDIMetaFile() const;
    const GDIMetaFile* GetGDIMetaFile() const;

    virtual void WriteData(SvStream& rOut) const;
    virtual void ReadData(const SdrObjIOHeader& rHead, SvStream& rIn);

    BOOL Unload();

    void Connect();
    void Disconnect();

    ::com::sun::star::uno::Reference< ::com::sun::star::frame::XModel > getXModel() const;

    /// #110015# sets the visible area at the SvInPlaceObject and SvEmbeddedInfoObject
    void SetVisibleArea( const Rectangle& rArea );
};

}//end of namespace binfilter
#endif //_SVDOOLE2_HXX

