/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: drwbassh.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 05:30:03 $
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
//STRIP001  SwDrawBase* pDrawActual;
//STRIP001
//STRIP001  UINT16      eDrawMode;
//STRIP001  BOOL        bRotate : 1;
//STRIP001  BOOL        bSelMove: 1;

//STRIP001     DECL_LINK( CheckGroupShapeNameHdl, SvxNameDialog* );
public:
    SwDrawBaseShell(SwView &rShell):SwBaseShell( rShell ){DBG_BF_ASSERT(0, "STRIP");} //STRIP001 SwDrawBaseShell(SwView &rShell);
//STRIP001  virtual     ~SwDrawBaseShell();

    SFX_DECL_INTERFACE(SW_DRAWBASESHELL);
//STRIP001  TYPEINFO();

//STRIP001  void        Execute(SfxRequest &);
//STRIP001  void        GetState(SfxItemSet &);
    void        DisableState(SfxItemSet &rSet){DBG_BF_ASSERT(0, "STRIP");}; //STRIP001 void     DisableState(SfxItemSet &rSet)               { Disable(rSet);}
//STRIP001  BOOL        Disable(SfxItemSet& rSet, USHORT nWhich = 0);

//STRIP001  void        StateStatusline(SfxItemSet &rSet);

};


} //namespace binfilter
#endif
