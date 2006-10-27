/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svx_float3d.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-27 20:48:51 $
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

#ifndef _SFXDISPATCH_HXX //autogen
#include <bf_sfx2/dispatch.hxx>
#endif

#ifndef _SFXDOCKWIN_HXX
#include <bf_sfx2/dockwin.hxx>
#endif

#include <bf_svx/f3dchild.hxx>

#include "float3d.hrc"
namespace binfilter {

/*N*/ SFX_IMPL_DOCKINGWINDOW( Svx3DChildWindow, SID_3D_WIN )


/*************************************************************************
|*
|* Ableitung vom SfxChildWindow als "Behaelter" fuer Effekte
|*
\************************************************************************/
/*N*/ __EXPORT Svx3DChildWindow::Svx3DChildWindow( Window* pParent,
/*N*/                                                        USHORT nId,
/*N*/                                                        SfxBindings* pBindings,
/*N*/                                                        SfxChildWinInfo* pInfo ) :
/*N*/   SfxChildWindow( pParent, nId )
/*N*/ {
DBG_BF_ASSERT(0, "STRIP"); //STRIP001   Svx3DWin* pWin = new Svx3DWin( pBindings, this, pParent );
/*N*/ }


}
