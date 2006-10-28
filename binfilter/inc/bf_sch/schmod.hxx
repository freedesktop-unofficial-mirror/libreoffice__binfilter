/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: schmod.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 02:49:50 $
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

#ifndef _SCHMOD_HXX
#define _SCHMOD_HXX

#ifndef _SFXLSTNER_HXX
#include <svtools/lstner.hxx>
#endif

#include "schdll0.hxx"        // fuer SchModuleDummy
#include "schdll.hxx"
#include "objfac.hxx"

#include "glob.hxx"
#include "schopt.hxx"
class SvFactory;
namespace binfilter {

class SvxErrorHandler;
class E3dObjFactory;
class SchTransferable;

/*************************************************************************
|*
|* This subclass of <SfxModule> (which is a subclass of <SfxShell>) is
|* linked to the DLL. One instance of this class exists while the DLL is
|* loaded.
|*
|* SdModule is like to be compared with the <SfxApplication>-subclass.
|*
|* Remember: Don`t export this class! It uses DLL-internal symbols.
|*
\************************************************************************/

class SchModule : public SchModuleDummy, public SfxListener
{
protected:
    XOutdevItemPool*    pXOutDevPool;

    SchDragServer*      pDragData;
    SchDragServer*      pClipboardData;
    // new clipborad format
    SchTransferable*    mpTransferDragDrop;
    SchTransferable*    mpTransferClipboard;
    SchTransferable*    mpTransferSelectionClipbd;

    SchObjFactory*      pSchObjFactory;
    E3dObjFactory*      pE3dFactory;
    SchOptions*         pChartOptions;

    virtual void FillStatusBar(StatusBar &rBar);

public:
    TYPEINFO();
    SFX_DECL_INTERFACE( SCH_IF_SCHAPP );

    SchModule(SvFactory* pObjFact);
    virtual ~SchModule();

    void Execute(SfxRequest& rReq);
    void GetState(SfxItemSet&);

    SchDragServer *GetDragData()                            { return pDragData; }
    void SetDragData(SchDragServer* pData)                  { pDragData = pData; }

    SchDragServer *GetClipboardData()                       { return pClipboardData; }
    void SetClipboardData(SchDragServer* pData)             { pClipboardData = pData; }

    // new clipboard format
    SchTransferable* GetDragTransferable()                  { return mpTransferDragDrop; }
    void SetDragTransferable( SchTransferable* pTrans )     { mpTransferDragDrop = pTrans; }

    SchTransferable* GetClipboardTransferable()             { return mpTransferClipboard; }
    void SetClipboardTransferable( SchTransferable* pTrans) { mpTransferClipboard = pTrans; }

    SchTransferable* GetSelectionClipboardTransferable()    { return mpTransferSelectionClipbd; }
    void SetSelectionClipboardTransferable( SchTransferable* pTrans) { mpTransferSelectionClipbd = pTrans; }



    SchOptions*          GetSchOptions();

    // virtual methods for options dialog (impl. see appopt.cxx)

    virtual void        Notify( SfxBroadcaster& rBC, const SfxHint& rHint );
};




#ifndef SCH_MOD1
#define SCH_MOD1() ( *(SchModule**) GetAppData(BF_SHL_SCH) )
#endif

} //namespace binfilter
#endif                                 // _SCHMOD_HXX
