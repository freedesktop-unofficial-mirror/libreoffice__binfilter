/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_wrtsh3.cxx,v $
 *
 *  $Revision: 1.8 $
 *
 *  last change: $Author: hr $ $Date: 2007-01-02 18:12:16 $
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


#pragma hdrstop

#ifndef _SVX_SVXIDS_HRC //autogen
#include <bf_svx/svxids.hrc>
#endif
#ifndef _SFX_BINDINGS_HXX //autogen
#include <bf_sfx2/bindings.hxx>
#endif
#ifndef _SFXVIEWFRM_HXX
#include <bf_sfx2/viewfrm.hxx>
#endif


#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

#include "wrtsh.hxx"
#include "view.hxx"
#include "wrtsh.hrc"
namespace binfilter {

#define C2U(cChar) ::rtl::OUString::createFromAscii(cChar)

using namespace ::com::sun::star;
using namespace ::rtl;

extern sal_Bool bNoInterrupt;       // in mainwn.cxx



/*--------------------------------------------------------------------
    Beschreibung: FontWork-Slots invalidieren
 --------------------------------------------------------------------*/


/*N*/ void SwWrtShell::DrawSelChanged(SdrView* pView)
/*N*/ {
//STRIP001  static sal_uInt16 __READONLY_DATA aInval[] =
//STRIP001 /*N*/     {
//STRIP001 /*N*/         SID_ATTR_FILL_STYLE, SID_ATTR_FILL_COLOR, SID_ATTR_LINE_STYLE,
//STRIP001 /*N*/         SID_ATTR_LINE_WIDTH, SID_ATTR_LINE_COLOR, 0
//STRIP001 /*N*/     };
//STRIP001 /*N*/
//STRIP001 /*N*/     GetView().GetViewFrame()->GetBindings().Invalidate(aInval);
//STRIP001 /*N*/
//STRIP001 /*N*/     sal_Bool bOldVal = bNoInterrupt;
//STRIP001 /*N*/ /*N*/     bNoInterrupt = sal_True;    // Trick, um AttrChangedNotify ueber Timer auszufuehren
//STRIP001 /*N*/ /*N*/     GetView().AttrChangedNotify(this);
//STRIP001 /*N*/ /*N*/     bNoInterrupt = bOldVal;
/*N*/ }

}
