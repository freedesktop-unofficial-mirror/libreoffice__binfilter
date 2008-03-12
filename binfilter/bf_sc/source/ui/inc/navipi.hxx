/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: navipi.hxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 07:09:13 $
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

#ifndef SC_NAVIPI_HXX
#define SC_NAVIPI_HXX

#ifndef _TOOLBOX_HXX //autogen
#include <vcl/toolbox.hxx>
#endif
#ifndef _FIELD_HXX //autogen
#include <vcl/field.hxx>
#endif
#ifndef _LSTBOX_HXX //autogen
#include <vcl/lstbox.hxx>
#endif
#ifndef _STDCTRL_HXX //autogen
#include <bf_svtools/stdctrl.hxx>
#endif
#ifndef _SFXPOOLITEM_HXX //autogen
#include <bf_svtools/poolitem.hxx>
#endif
#ifndef _SFXLSTNER_HXX //autogen
#include <bf_svtools/lstner.hxx>
#endif
#ifndef _SFX_CHILDWIN_HXX //autogen
#include <bf_sfx2/childwin.hxx>
#endif

#ifndef SC_CONTENT_HXX
#include "content.hxx"
#endif

#ifndef _SVEDIT_HXX //autogen
#include <bf_svtools/svmedit.hxx>
#endif
namespace binfilter {


class ScTabViewShell;
class ScViewData;
class ScArea;
class ScScenarioWindow;
class ScNavigatorControllerItem;
class ScNavigatorDialogWrapper;
class ScNavigatorDlg;
class ScNavigatorSettings;
class ScRange;

//========================================================================

#define SC_DROPMODE_URL         0
#define SC_DROPMODE_LINK        1
#define SC_DROPMODE_COPY        2

enum NavListMode { NAV_LMODE_NONE       = 0x4000,
                   NAV_LMODE_AREAS      = 0x2000,
                   NAV_LMODE_DBAREAS    = 0x1000,
                   NAV_LMODE_DOCS       = 0x800,
                   NAV_LMODE_SCENARIOS  = 0x400 };

//========================================================================
// class ScScenarioListBox -----------------------------------------------
//========================================================================

//========================================================================
// class ScScenarioWindow ------------------------------------------------
//========================================================================

//==================================================================
//  class ColumnEdit
//==================================================================


//==================================================================
//  class RowEdit
//==================================================================


//==================================================================
//  class ScDocListBox
//==================================================================


//==================================================================
//  class CommandToolBox
//==================================================================

//==================================================================
//  class ScNavigatorDlg
//==================================================================


//==================================================================

class ScNavigatorDialogWrapper: public SfxChildWindowContext
{
public:
            ScNavigatorDialogWrapper( Window*           pParent,
                                      USHORT            nId,
                                      SfxBindings*      pBindings,
                                      SfxChildWinInfo*  pInfo ):SfxChildWindowContext( nId ){DBG_BF_ASSERT(0, "STRIP");} //STRIP001 SfxChildWinInfo*    pInfo );

    SFX_DECL_CHILDWINDOW_CONTEXT(ScNavigatorDialogWrapper)


};



} //namespace binfilter
#endif // SC_NAVIPI_HXX

