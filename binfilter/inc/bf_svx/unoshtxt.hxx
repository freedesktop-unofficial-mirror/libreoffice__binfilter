/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: unoshtxt.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 15:19:19 $
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

#ifndef SVX_UNOSHTXT_HXX
#define SVX_UNOSHTXT_HXX

#include <memory>

#ifndef _SVX_UNOEDSRC_HXX
#include <bf_svx/unoedsrc.hxx>
#endif
class Window;
namespace binfilter {

class SvxTextForwarder;
class SdrObject;
class SdrView;
class SvxTextEditSourceImpl;

class SvxTextEditSource : public SvxEditSource, public SvxViewForwarder
{
public:
    SvxTextEditSource( SdrObject* pObj );

    /** Since the views don't broadcast their dying, make sure that
        this object gets destroyed if the view becomes invalid

        The window is necessary, since our views can display on multiple windows
     */
    SvxTextEditSource( SdrObject& rObj, SdrView& rView, const Window& rViewWindow );

    virtual ~SvxTextEditSource();

    virtual SvxEditSource*          Clone() const;
    virtual SvxTextForwarder*       GetTextForwarder();
     virtual SvxViewForwarder*      GetViewForwarder();
     virtual SvxEditViewForwarder*  GetEditViewForwarder( sal_Bool bCreate = sal_False );
    virtual void                    UpdateData();

    virtual SfxBroadcaster&         GetBroadcaster() const;

    SdrObject* GetSdrObject() const;

    void lock();
    void unlock();

    static sal_Bool hasLevels( const SdrObject* pObject );

    // the viewforwarder interface
    virtual BOOL        IsValid() const;
    virtual Rectangle   GetVisArea() const;
    virtual Point       LogicToPixel( const Point&, const MapMode& ) const;
    virtual Point       PixelToLogic( const Point&, const MapMode& ) const;

private:
    SvxTextEditSource( SvxTextEditSourceImpl* pImpl );

    SvxTextEditSourceImpl*  mpImpl;
};

}//end of namespace binfilter
#endif
