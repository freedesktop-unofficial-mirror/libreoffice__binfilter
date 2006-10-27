/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: drawview.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-27 16:07:22 $
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

#ifndef SC_DRAWVIEW_HXX
#define SC_DRAWVIEW_HXX

#ifndef _SVX_FMVIEW_HXX //autogen
#include <bf_svx/fmview.hxx>
#endif

#include "global.hxx"
namespace binfilter {

class ScDocument;
class ScViewData;
class SdrViewUserMarker;

class ScDrawView: public FmFormView
{
    ScViewData*             pViewData;
    OutputDevice*           pDev;                   //! noetig ?
    ScDocument*             pDoc;
    USHORT                  nTab;
    Fraction                aScaleX;                // Faktor fuer Drawing-MapMode
    Fraction                aScaleY;
    SdrViewUserMarker*      pDropMarker;
    SdrObject*              pDropMarkObj;
    BOOL                    bInConstruct;
    BOOL                    bDisableHdl;

    void            Construct();
    void            UpdateBrowser();

protected:
    virtual void    ModelHasChanged();

    // add custom handles (used by other apps, e.g. AnchorPos)
    virtual void AddCustomHdl();

public:
                    ScDrawView( OutputDevice* pOut, ScViewData* pData );
    virtual         ~ScDrawView();

    virtual void    MarkListHasChanged();
    virtual void    SFX_NOTIFY( SfxBroadcaster& rBC, const TypeId& rBCType,
                         const SfxHint& rHint, const TypeId& rHintType );

    void            DrawMarks( OutputDevice* pOut ) const;


    BOOL            IsDisableHdl() const    { return bDisableHdl; }


    void            InvalidateAttribs();
    void            InvalidateDrawTextAttrs();


    void            GetScale( Fraction& rFractX, Fraction& rFractY ) const;
    void            RecalcScale();
    void            UpdateWorkArea();
    USHORT          GetTab() const      { return nTab; }




    void            VCAddWin( Window* pWin );
    void            VCRemoveWin( Window* pWin );


    USHORT          GetPopupMenuId();
    void            UpdateUserViewOptions();


    String          GetSelectedChartName() const;


    SdrEndTextEditKind  ScEndTextEdit();    // ruft SetDrawTextUndo(0)
};




} //namespace binfilter
#endif

