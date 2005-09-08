/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: appdata.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-08 03:21:34 $
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
#ifndef _SFX_APPDATA_HXX
#define _SFX_APPDATA_HXX

#include <tools/link.hxx>
#include <tools/list.hxx>
#include <svtools/lstner.hxx>
#include <vcl/timer.hxx>
#include <tools/string.hxx>
#include "rtl/ref.hxx"

#include "bitset.hxx"
class SvStrings;
class Config;
class SvVerbList;
class DdeService;
class SfxItemPool;
class SvUShorts;
class SfxCancelManager;
class SvtSaveOptions;
class SvtUndoOptions;
class SvtHelpOptions;
class ResMgr;
class Window;
namespace binfilter {

class SfxApplication;

class SfxBmkMenu;
class SfxProgress;
class SfxChildWinFactArr_Impl;
class SfxToolBoxConfig;
class SfxDdeDocTopics_Impl;
class SfxEventConfiguration;
class SfxMacroConfig;
class SfxInitLinkList;
class SfxFilterMatcher;
struct SfxFrameObjectFactoryPtr;
struct SfxPluginObjectFactoryPtr;
class ISfxTemplateCommon;
class SfxFilterMatcher;
class SfxStatusDispatcher;
class SfxDdeTriggerTopic_Impl;
class SfxMiscCfg;
class SfxDocumentTemplates;
class SfxFrameArr_Impl;
class SfxObjectFactory;
class SfxObjectShell;
namespace sfx2 { namespace appl { class ImeStatusWindow; } }

//=========================================================================
// SfxAppData_Impl
//=========================================================================

class SfxAppData_Impl : public SfxListener
{
public:
    IndexBitSet                         aIndexBitSet;           // for counting noname documents
    List                                aPendingInitFactories;  // late filter init
    Timer                               aLateInitTimer;
    String                              aLastDir;               // for IO dialog
    String                              aLastFilter;            // for IO dialog
    String                              aLastNewURL;            // for AppControl
    String                              aOpenList;              // command line arguments
    String                              aPrintList;             // command line arguments
    String                              aPortalConnect;         // command line arguments
    bool                                bServer;                // command line arguments

    // DDE stuff
    DdeService*                         pDdeService;
    SfxDdeDocTopics_Impl*               pDocTopics;
    SfxDdeTriggerTopic_Impl*            pTriggerTopic;
    DdeService*                         pDdeService2;

    // single instance classes
    SfxChildWinFactArr_Impl*            pFactArr;
    SfxPluginObjectFactoryPtr*          pSfxPluginObjectFactoryPtr;
    SfxObjectFactory*                   pSfxPlugInObjectShellFactory;
    SfxFrameObjectFactoryPtr*           pSfxFrameObjectFactoryPtr;
    SfxFrameArr_Impl*                   pTopFrames;

    // special members
    SfxInitLinkList*                    pInitLinkList;

    // application members
    SfxFilterMatcher*                   pMatcher;
    SfxCancelManager*                   pCancelMgr;
    ResMgr*                             pLabelResMgr;
    SfxStatusDispatcher*                pAppDispatch;
    SfxDocumentTemplates*               pTemplates;

    // global pointers
    SvVerbList*                         pVerbs;
    Config*                             pFilterIni;
    SfxItemPool*                        pPool;
    SfxEventConfiguration*              pEventConfig;
    SvUShorts*                          pDisabledSlotList;
    SvStrings*                          pSecureURLs;
    SfxMiscCfg*                         pMiscConfig;
    SvtSaveOptions*                     pSaveOptions;
    SvtUndoOptions*                     pUndoOptions;
    SvtHelpOptions*                     pHelpOptions;

    // "current" functionality
    SfxObjectShell*                     pThisDocument;
    SfxProgress*                        pProgress;
    Window*                             pDefFocusWin;
    ISfxTemplateCommon*                 pTemplateCommon;

    USHORT                              nDocModalMode;              // counts documents in modal mode
    USHORT                              nAutoTabPageId;
    USHORT                              nExecutingSID;
    USHORT                              nBasicCallLevel;
    USHORT                              nRescheduleLocks;
    USHORT                              nInReschedule;
    USHORT                              nAsynchronCalls;
    USHORT                              nAppEvent;                  // command line interpretation

    ::rtl::Reference< sfx2::appl::ImeStatusWindow > m_xImeStatusWindow;

    BOOL                                bDirectAliveCount : 1;
    BOOL                                bInQuit : 1;
    BOOL                                bInvalidateOnUnlock : 1;
    BOOL                                bBean : 1;
    BOOL                                bMinimized : 1;
    BOOL                                bInvisible : 1;
    BOOL                                bInException : 1;
    BOOL                                bPlugged : 1;
    BOOL                                bOLEResize : 1;

                                        SfxAppData_Impl( SfxApplication* );
                                        ~SfxAppData_Impl();

    virtual void                        Notify( SfxBroadcaster &rBC, const SfxHint &rHint );
    void                                UpdateApplicationSettings( BOOL bDontHide );
    SfxDocumentTemplates*               GetDocumentTemplates();
    DECL_STATIC_LINK(                   SfxAppData_Impl, CreateDocumentTemplates, void* );
    void                                DeInitDDE();
};

}//end of namespace binfilter
#endif // #ifndef _SFX_APPDATA_HXX


