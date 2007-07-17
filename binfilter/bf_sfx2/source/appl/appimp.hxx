/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: appimp.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: obo $ $Date: 2007-07-17 10:32:36 $
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
#ifndef _SFXAPPIMP_HXX
#define _SFXAPPIMP_HXX

#include <tools/time.hxx>
#include <tools/string.hxx>
class MenuBar;
class UniqueIndex;
class BasicManager;
class Timer;
namespace binfilter {

class SfxTbxCtrlFactArr_Impl;
class SfxStbCtrlFactArr_Impl;
class SfxMenuCtrlFactArr_Impl;
class SfxViewFrameArr_Impl;
class SfxViewShellArr_Impl;
class SfxObjectShellArr_Impl;
class IntroWindow_Impl;
class SfxTemplateDialog;
class SfxDialogLibraryContainer;
class SfxScriptLibraryContainer;
class SfxBasicTestWin;

struct SfxApplication_Impl
{
    Time                        aAutoSaveTime;
    String                      aMemExceptionString;
    String                      aResWarningString;
    String                      aResExceptionString;
    String                      aSysResExceptionString;
    String                      aDoubleExceptionString;
    String                      aBasicSourceName;
    SfxTbxCtrlFactArr_Impl*     pTbxCtrlFac;
    SfxStbCtrlFactArr_Impl*     pStbCtrlFac;
    SfxMenuCtrlFactArr_Impl*    pMenuCtrlFac;
    SfxViewFrameArr_Impl*       pViewFrames;
    SfxViewShellArr_Impl*       pViewShells;
    SfxObjectShellArr_Impl*     pObjShells;
    MenuBar*                    pEmptyMenu;         // dummy for no-menu
    IntroWindow_Impl*           pIntro;
    UniqueIndex*                pEventHdl;          // Hook-Liste fuer UserEvents
    SfxTemplateDialog*          pTemplateDlg;
    SfxScriptLibraryContainer*  pBasicLibContainer;
    SfxDialogLibraryContainer*  pDialogLibContainer;
    SfxBasicTestWin*            pBasicTestWin;
    Timer*                      pAutoSaveTimer;
    USHORT                      nDocNo;             // Laufende Doc-Nummer (AutoName)
    USHORT                      nWarnLevel;
    BOOL                        bConfigLoaded:1;
    BOOL                        bAutoSaveNow:1;     // ist TRUE, wenn der Timer abgelaufen ist, wenn die App nicht aktiv war
};

}//end of namespace binfilter
#endif

