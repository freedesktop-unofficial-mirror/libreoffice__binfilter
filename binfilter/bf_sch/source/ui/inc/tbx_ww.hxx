/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: tbx_ww.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-07 22:58:05 $
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



#ifndef _SCH_TBX_WW_HXX
#define _SCH_TBX_WW_HXX

#ifndef _SV_TOOLBOX_HXX //autogen
#include <vcl/toolbox.hxx>
#endif
#ifndef _SFXTBXCTRL_HXX //autogen
#include <bf_sfx2/tbxctrl.hxx>
#endif


#include "schresid.hxx"
namespace binfilter {

//------------------------------------------------------------------------

class SchPopupWindowTbx : public SfxPopupWindow
{
private:
    ToolBox             aTbx;

public:
    SchPopupWindowTbx( USHORT nId, SfxToolBoxControl* pTbxCtl,
                      SchResId aRIdWin, SchResId aRIdTbx,
                      SfxBindings& rBindings );
    ~SchPopupWindowTbx() {}

    void StartSelection() { aTbx.StartSelection(); }
    void SelectHdl( void* p );
};

} //namespace binfilter
#endif      // _SCH_TBX_WW_HXX

