/*************************************************************************
 *
 *  $RCSfile: svdouno.hxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:23:50 $
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

#ifndef _SVDOUNO_HXX
#define _SVDOUNO_HXX

#ifndef _COM_SUN_STAR_AWT_XCONTROLMODEL_HPP_
#include <com/sun/star/awt/XControlModel.hpp>
#endif
#ifndef _COM_SUN_STAR_AWT_XCONTROL_HPP_
#include <com/sun/star/awt/XControl.hpp>
#endif
#ifndef _COM_SUN_STAR_AWT_XMULTISERVICEFACTORY_HPP_
#include <com/sun/star/lang/XMultiServiceFactory.hpp>
#endif

#ifndef _SVDORECT_HXX
#include <bf_svx/svdorect.hxx>
#endif

//************************************************************
//   Vorausdeklarationen
//************************************************************

class SdrView;
class SdrControlEventListenerImpl;

//************************************************************
//   SdrUnoObj
//************************************************************

class SdrUnoObj : public SdrRectObj
{
    friend class                SdrPageView;
    friend class                SdrControlEventListenerImpl;

    SdrControlEventListenerImpl*    pEventListener;

    String                      aUnoControlModelTypeName;
    String                      aUnoControlTypeName;
    BOOL                        bOwnUnoControlModel;

protected:
    ::com::sun::star::uno::Reference< com::sun::star::awt::XControlModel > xUnoControlModel; // kann auch von aussen gesetzt werden

private:
//STRIP001  void CreateUnoControlModel(const String& rModelName);
//STRIP001  void CreateUnoControlModel(const String& rModelName,
//STRIP001      const ::com::sun::star::uno::Reference< com::sun::star::lang::XMultiServiceFactory >& rxSFac );

public:
    TYPEINFO();

//  UNICODE: SdrUnoObj(BOOL bOwnsModel = TRUE, const String& rModelName = "");
    SdrUnoObj(const String& rModelName, BOOL bOwnsModel = TRUE);
    SdrUnoObj(const String& rModelName,
        const ::com::sun::star::uno::Reference< com::sun::star::lang::XMultiServiceFactory >& rxSFac,
        BOOL bOwnsModel = TRUE);
    virtual ~SdrUnoObj();

    virtual void SetPage(SdrPage* pNewPage);
    virtual void SetModel(SdrModel* pModel);

//STRIP001  virtual void TakeObjInfo(SdrObjTransformInfoRec& rInfo) const;
//STRIP001  virtual UINT16 GetObjIdentifier() const;
//STRIP001  virtual FASTBOOL Paint(ExtOutputDevice& rOut, const SdrPaintInfoRec& rInfoRec) const;
//STRIP001  virtual SdrObject* CheckHit(const Point& rPnt, USHORT nTol, const SetOfByte* pVisiLayer) const;

//STRIP001  virtual void operator = (const SdrObject& rObj);
//STRIP001  virtual FASTBOOL HasSpecialDrag() const;

    virtual void NbcMove(const Size& rSize);
    virtual void NbcResize(const Point& rRef, const Fraction& xFact, const Fraction& yFact);
    virtual void NbcSetSnapRect(const Rectangle& rRect);
    virtual void NbcSetLogicRect(const Rectangle& rRect);
    virtual void NbcSetLayer(SdrLayerID nLayer);

    virtual void WriteData(SvStream& rOut) const;
    virtual void ReadData(const SdrObjIOHeader& rHead, SvStream& rIn);

//STRIP001  virtual void TakeObjNameSingul(XubString& rName) const;
//STRIP001  virtual void TakeObjNamePlural(XubString& rName) const;

    ::com::sun::star::uno::Reference< com::sun::star::awt::XControlModel > GetUnoControlModel() const {return xUnoControlModel;}
    ::com::sun::star::uno::Reference< com::sun::star::awt::XControl > GetUnoControl(const OutputDevice* pOut) const;
//STRIP001  OutputDevice* GetOutputDevice(::com::sun::star::uno::Reference< com::sun::star::awt::XControl > _xControl) const;

    const String& GetUnoControlModelTypeName() const { return aUnoControlTypeName; }
    const String& GetUnoControlTypeName() const { return aUnoControlTypeName; }

    void SetUnoControlModel(::com::sun::star::uno::Reference< com::sun::star::awt::XControlModel > xModel);
    void VisAreaChanged(const OutputDevice* pOut=NULL);
};

#endif          // _SVDOUNO_HXX

