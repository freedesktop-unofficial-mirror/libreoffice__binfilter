/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: fmexpl.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-27 21:08:13 $
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
#ifndef _SVX_FMEXPL_HXX
#define _SVX_FMEXPL_HXX







#ifndef _SFXDOCKWIN_HXX //autogen
#include <bf_sfx2/dockwin.hxx>
#endif












#ifndef _SVX_FMVIEW_HXX
#include "fmview.hxx"
#endif


class SdrObjListIter;
namespace binfilter {

class FmFormShell;
class SdrObject;
class FmFormModel;

//========================================================================

//========================================================================

//========================================================================

//========================================================================

//========================================================================

//========================================================================
class FmNavViewMarksChanged : public SfxHint
{
    FmFormView* pView;
public:
    FmNavViewMarksChanged(FmFormView* pWhichView) { pView = pWhichView; }
    virtual ~FmNavViewMarksChanged() {}

};

//========================================================================

//========================================================================


//========================================================================
// FmNavRequestSelectHint - jemand teilt dem NavigatorTree mit, dass er bestimmte Eintraege selektieren soll



//========================================================================


//========================================================================


//========================================================================
//............................................................................
namespace svxform
{
//............................................................................

    //========================================================================
    // class OFormComponentObserver
    //========================================================================

    //========================================================================
    //= NavigatorTreeModel
    //========================================================================

    //========================================================================


    //========================================================================

    //========================================================================
    class NavigatorFrameManager : public SfxChildWindow
    {
    public:
        NavigatorFrameManager( Window *pParent, sal_uInt16 nId, SfxBindings *pBindings,
                          SfxChildWinInfo *pInfo );
        SFX_DECL_CHILDWINDOW( NavigatorFrameManager );
    };

//............................................................................
}   // namespace svxform
//............................................................................

}//end of namespace binfilter
#endif // _SVX_FMEXPL_HXX

