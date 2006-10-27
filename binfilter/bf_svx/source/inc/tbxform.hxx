/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: tbxform.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-27 21:13:08 $
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
#ifndef _SVX_TBXFORM_HXX
#define _SVX_TBXFORM_HXX

#ifndef _SFXTBXCTRL_HXX //autogen
#include <bf_sfx2/tbxctrl.hxx>
#endif




class FixedText;
namespace binfilter {

//========================================================================


//========================================================================


//========================================================================


//========================================================================
class SvxFmTbxCtlConfig : public SfxToolBoxControl
{
private:
    UINT16 nLastSlot;

public:
    SFX_DECL_TOOLBOX_CONTROL();

    SvxFmTbxCtlConfig( USHORT nId, ToolBox& rTbx, SfxBindings& );
    ~SvxFmTbxCtlConfig() {}

    virtual void                StateChanged( USHORT nSID, SfxItemState eState,
                                              const SfxPoolItem* pState );
};

//========================================================================
class SvxFmTbxCtlAbsRec : public SfxToolBoxControl
{
public:
    SFX_DECL_TOOLBOX_CONTROL();

    SvxFmTbxCtlAbsRec( USHORT nId, ToolBox& rTbx, SfxBindings& rBindings );


};

//========================================================================
class SvxFmTbxCtlRecText : public SfxToolBoxControl
{
public:
    SFX_DECL_TOOLBOX_CONTROL();

    SvxFmTbxCtlRecText( USHORT nId, ToolBox& rTbx, SfxBindings& rBindings );
};

//========================================================================
class SvxFmTbxCtlRecFromText : public SfxToolBoxControl
{
public:
    SFX_DECL_TOOLBOX_CONTROL();

    SvxFmTbxCtlRecFromText( USHORT nId, ToolBox& rTbx, SfxBindings& rBindings );
};

//========================================================================
class SvxFmTbxCtlRecTotal : public SfxToolBoxControl
{
    FixedText* pFixedText;

public:
    SFX_DECL_TOOLBOX_CONTROL();

    SvxFmTbxCtlRecTotal( USHORT nId, ToolBox& rTbx, SfxBindings& rBindings );
};

/*
//========================================================================
class SvxFmTbxCtlFilterText : public SfxToolBoxControl
{
    FixedText* pFixedText;
    XubString aText;
public:
    SFX_DECL_TOOLBOX_CONTROL();

    SvxFmTbxCtlFilterText( USHORT nId, ToolBox& rTbx, SfxBindings& rBindings );
    ~SvxFmTbxCtlFilterText();

    virtual Window* CreateItemWindow( Window* pParent );
    virtual void    StateChanged( USHORT nSID, SfxItemState eState,
                                  const SfxPoolItem* pState );
};
*/

//========================================================================
class SvxFmTbxNextRec : public SfxToolBoxControl
{
public:
    SFX_DECL_TOOLBOX_CONTROL();
    SvxFmTbxNextRec( USHORT nId, ToolBox& rTbx, SfxBindings& rBindings );
};

//========================================================================
class SvxFmTbxPrevRec : public SfxToolBoxControl
{
public:
    SFX_DECL_TOOLBOX_CONTROL();
    SvxFmTbxPrevRec( USHORT nId, ToolBox& rTbx, SfxBindings& rBindings );
};


}//end of namespace binfilter
#endif

