/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: drwbassh.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 00:38:42 $
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
#ifndef _SWDRWBASSH_HXX
#define _SWDRWBASSH_HXX

#include "basesh.hxx"
class SfxItemSet;
namespace binfilter {

class SwWrtShell;
class SwView;

class SwDrawBase;
class SvxNameDialog;

class SwDrawBaseShell: public SwBaseShell
{

public:
    SwDrawBaseShell(SwView &rShell):SwBaseShell( rShell ){DBG_BF_ASSERT(0, "STRIP");} //STRIP001 SwDrawBaseShell(SwView &rShell);

    SFX_DECL_INTERFACE(SW_DRAWBASESHELL);

    void        DisableState(SfxItemSet &rSet){DBG_BF_ASSERT(0, "STRIP");}; //STRIP001 void     DisableState(SfxItemSet &rSet)               { Disable(rSet);}


};


} //namespace binfilter
#endif
