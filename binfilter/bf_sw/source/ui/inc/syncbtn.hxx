/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: syncbtn.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 05:54:56 $
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
#ifndef _SWSYNCBTN_HXX
#define _SWSYNCBTN_HXX

#ifndef _SFX_CHILDWIN_HXX //autogen
#include <bf_sfx2/childwin.hxx>
#endif

#ifdef _SYNCDLG

#ifndef _BASEDLGS_HXX //autogen
#include <bf_sfx2/basedlgs.hxx>
#endif

#ifndef _SV_BUTTON_HXX //autogen
#include <vcl/button.hxx>
#endif
namespace binfilter {

class SwWrtShell;

/*------------------------------------------------------------------------
    Beschreibung:
------------------------------------------------------------------------*/

//STRIP001 class SwSyncBtnDlg : public SfxFloatingWindow
//STRIP001 {
//STRIP001  PushButton              aSyncBtn;
//STRIP001
//STRIP001  DECL_LINK( BtnHdl,      PushButton* pBtn = 0 );
//STRIP001
//STRIP001 public:
//STRIP001  SwSyncBtnDlg(SfxBindings*, SfxChildWindow*, Window *pParent);
//STRIP001  ~SwSyncBtnDlg();
//STRIP001 };
} //namespace binfilter
#endif

/*------------------------------------------------------------------------
    Beschreibung:
------------------------------------------------------------------------*/
namespace binfilter {//STRIP009
class SwSyncChildWin : public SfxChildWindow
{
public:
    SwSyncChildWin( Window* ,
                    USHORT nId,
                    SfxBindings*,
                    SfxChildWinInfo*  );

    SFX_DECL_CHILDWINDOW( SwSyncChildWin );
};


} //namespace binfilter
#endif

