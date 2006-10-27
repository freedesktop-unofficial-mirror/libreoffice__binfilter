/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: hdftctrl.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 00:43:06 $
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

#ifndef _HDFTCTRL_HXX
#define _HDFTCTRL_HXX

#ifndef _SFXMNUITEM_HXX //autogen
#include <bf_sfx2/mnuitem.hxx>
#endif
#ifndef _SFXAPP_HXX //autogen
#include <bf_sfx2/app.hxx>
#endif
#define _SVSTDARR_STRINGSSORTDTOR
#define _SVSTDARR_BOOLS
#include <svtools/svstdarr.hxx>
namespace binfilter {

class SwDocShell;

class SwHeadFootMenuControl : public SfxMenuControl
{

public:
    SFX_DECL_MENU_CONTROL();

    SwHeadFootMenuControl( USHORT nPos, Menu& rMenu,    //STRIP001  SwHeadFootMenuControl( USHORT nPos, Menu& rMenu,
        SfxBindings& rBindings ){DBG_BF_ASSERT(0, "STRIP");};   //STRIP001                              SfxBindings& rBindings );
};

} //namespace binfilter
#endif

