/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svdouno.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 04:09:58 $
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
namespace binfilter {

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
    ::com::sun::star::uno::Reference< ::com::sun::star::awt::XControlModel > xUnoControlModel; // kann auch von aussen gesetzt werden

private:

public:
    TYPEINFO();

//  UNICODE: SdrUnoObj(BOOL bOwnsModel = TRUE, const String& rModelName = "");
    SdrUnoObj(const String& rModelName, BOOL bOwnsModel = TRUE);
    SdrUnoObj(const String& rModelName,
        const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >& rxSFac,
        BOOL bOwnsModel = TRUE);
    virtual ~SdrUnoObj();

    virtual void SetPage(SdrPage* pNewPage);
    virtual void SetModel(SdrModel* pModel);



    virtual void NbcMove(const Size& rSize);
    virtual void NbcResize(const Point& rRef, const Fraction& xFact, const Fraction& yFact);
    virtual void NbcSetSnapRect(const Rectangle& rRect);
    virtual void NbcSetLogicRect(const Rectangle& rRect);
    virtual void NbcSetLayer(SdrLayerID nLayer);

    virtual void WriteData(SvStream& rOut) const;
    virtual void ReadData(const SdrObjIOHeader& rHead, SvStream& rIn);


    ::com::sun::star::uno::Reference< ::com::sun::star::awt::XControlModel > GetUnoControlModel() const {return xUnoControlModel;}
    ::com::sun::star::uno::Reference< ::com::sun::star::awt::XControl > GetUnoControl(const OutputDevice* pOut) const;

    const String& GetUnoControlModelTypeName() const { return aUnoControlTypeName; }
    const String& GetUnoControlTypeName() const { return aUnoControlTypeName; }

    void SetUnoControlModel(::com::sun::star::uno::Reference< ::com::sun::star::awt::XControlModel > xModel);
    void VisAreaChanged(const OutputDevice* pOut=NULL);
};

}//end of namespace binfilter
#endif          // _SVDOUNO_HXX

