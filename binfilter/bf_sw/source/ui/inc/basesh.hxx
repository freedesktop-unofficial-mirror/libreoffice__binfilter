/*************************************************************************
 *
 *  $RCSfile: basesh.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:54:52 $
 *
 *  The Contents of this file are made available subject to the terms of
 *  either of the following licenses
 *
 *         - GNU Lesser General Public License Version 2.1
 *         - Sun Industry Standards Source License Version 1.1
 *
 *  Sun Microsystems Inc., October, 2000
 *
 *  GNU Lesser General Public License Version 2.1
 *  =============================================
 *  Copyright 2000 by Sun Microsystems, Inc.
 *  901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License version 2.1, as published by the Free Software Foundation.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *  MA  02111-1307  USA
 *
 *
 *  Sun Industry Standards Source License Version 1.1
 *  =================================================
 *  The contents of this file are subject to the Sun Industry Standards
 *  Source License Version 1.1 (the "License"); You may not use this file
 *  except in compliance with the License. You may obtain a copy of the
 *  License at http://www.openoffice.org/license.html.
 *
 *  Software provided under this License is provided on an "AS IS" basis,
 *  WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING,
 *  WITHOUT LIMITATION, WARRANTIES THAT THE SOFTWARE IS FREE OF DEFECTS,
 *  MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE, OR NON-INFRINGING.
 *  See the License for the specific provisions governing your rights and
 *  obligations concerning the Software.
 *
 *  The Initial Developer of the Original Code is: Sun Microsystems, Inc.
 *
 *  Copyright: 2000 by Sun Microsystems, Inc.
 *
 *  All Rights Reserved.
 *
 *  Contributor(s): _______________________________________
 *
 *
 ************************************************************************/
#ifndef _SWBASESH_HXX
#define _SWBASESH_HXX


#ifndef _SHELLID_HXX
#include <shellid.hxx>
#endif

#define _SVSTDARR_USHORTSSORT
#define _SVSTDARR_USHORTS

#ifndef _LINK_HXX //autogen
#include <tools/link.hxx>
#endif
#ifndef _SV_TIMER_HXX //autogen
#include <vcl/timer.hxx>
#endif
#ifndef _SFXMODULE_HXX //autogen
#include <bf_sfx2/module.hxx>
#endif
#ifndef _SFX_SHELL_HXX //autogen
#include <bf_sfx2/shell.hxx>
#endif
#include <svtools/svstdarr.hxx>
class GraphicFilter;
class SfxItemSet;
class Graphic;

namespace binfilter {

class SwWrtShell;
class SwCrsrShell;
class SwView;

class SwFlyFrmAttrMgr;

extern void DisableAllItems(SfxItemSet &);
struct DBTextStruct_Impl;
class SwBaseShell: public SfxShell
{
    SwView      &rView;

    // DragModus
    static USHORT nFrameMode;

    // Bug 75078 - if in GetState the asynch call of GetGraphic returns
    //              synch, the set the state directly into the itemset
    SfxItemSet*         pGetStateSet;

    //Update-Timer fuer Graphic
    SvUShortsSort aGrfUpdateSlots;

    DECL_LINK( GraphicArrivedHdl, SwCrsrShell* );
    DECL_LINK( UpdatePercentHdl, GraphicFilter* );

protected:

    SwWrtShell& GetShell   ();
//STRIP001  SwWrtShell* GetShellPtr();

    SwView&     GetView() { return rView; }

    SwFlyFrmAttrMgr *pFrmMgr;

    DECL_STATIC_LINK( SwBaseShell, InsertDBTextHdl, DBTextStruct_Impl* );

    void SetGetStateSet( SfxItemSet* p )            { pGetStateSet = p; }
    BOOL AddGrfUpdateSlot( USHORT nSlot )
                                { return aGrfUpdateSlots.Insert( nSlot ); }

//STRIP001     void InsertURLButton(const String& rURL, const String& rTarget, const String& rTxt);
public:
    SwBaseShell(SwView &rShell);
    virtual     ~SwBaseShell();
    SFX_DECL_INTERFACE(SW_BASESHELL);
    TYPEINFO();

    void        ExecDelete(SfxRequest &){DBG_ASSERT(0, "STRIP");} ;//STRIP001 void        ExecDelete(SfxRequest &);

    void        ExecClpbrd(SfxRequest &){DBG_ASSERT(0, "STRIP");}; //STRIP001 void        ExecClpbrd(SfxRequest &);
    void        StateClpbrd(SfxItemSet &);

    void        ExecUndo(SfxRequest &){DBG_ASSERT(0, "STRIP");}; //STRIP001 void        ExecUndo(SfxRequest &);
    void        StateUndo(SfxItemSet &);

    void        Execute(SfxRequest &){DBG_ASSERT(0, "STRIP");}; //STRIP001 void        Execute(SfxRequest &);
    void        GetState(SfxItemSet &);
    void        StateStyle(SfxItemSet &);

    void        ExecuteGallery(SfxRequest&){DBG_ASSERT(0, "STRIP");}; //STRIP001 void       ExecuteGallery(SfxRequest&);
    void        GetGalleryState(SfxItemSet&){DBG_ASSERT(0, "STRIP");}; //STRIP001 void      GetGalleryState(SfxItemSet&);

    void        ExecDlg(SfxRequest &){DBG_ASSERT(0, "STRIP");}; //STRIP001 void        ExecDlg(SfxRequest &);

    void        StateStatusLine(SfxItemSet &rSet);
    void        ExecTxtCtrl(SfxRequest& rReq){DBG_ASSERT(0, "STRIP");} ;//STRIP001  void        ExecTxtCtrl(SfxRequest& rReq);
    void        GetTxtFontCtrlState(SfxItemSet& rSet);
    void        GetTxtCtrlState(SfxItemSet& rSet);
    void        GetBorderState(SfxItemSet &rSet){DBG_ASSERT(0, "STRIP");}; //STRIP001 void      GetBorderState(SfxItemSet &rSet);
    void        GetBckColState(SfxItemSet &rSet);

     void        ExecBckCol(SfxRequest& rReq){DBG_ASSERT(0, "STRIP");}; //STRIP001 void        ExecBckCol(SfxRequest& rReq);
    void        SetWrapMode( USHORT nSlot );

    void        StateDisableItems(SfxItemSet &){DBG_ASSERT(0, "STRIP");};//STRIP001 void        StateDisableItems(SfxItemSet &);

    void        EditRegionDialog(SfxRequest& rReq){DBG_ASSERT(0, "STRIP"); };//STRIP001 void        EditRegionDialog(SfxRequest& rReq);
    void        InsertRegionDialog(SfxRequest& rReq){DBG_ASSERT(0, "STRIP"); };//STRIP001 void      InsertRegionDialog(SfxRequest& rReq);

    void        ExecField(SfxRequest& rReq){DBG_ASSERT(0, "STRIP");}; //STRIP001 void       ExecField(SfxRequest& rReq);

//STRIP001  static void    SetFrmMode( USHORT nMode, SwWrtShell *pShell );  //Mit Update!
    static void   _SetFrmMode( USHORT nMode )   { nFrameMode = nMode; }
    static USHORT  GetFrmMode()                 { return nFrameMode;  }

    //public fuer D&D
//STRIP001  int     InsertGraphic( const String &rPath, const String &rFilter,
//STRIP001                          BOOL bLink = TRUE, GraphicFilter *pFlt = 0,
//STRIP001                          Graphic* pPreviewGrf = 0,
//STRIP001                          BOOL bRule = FALSE );

};


} //namespace binfilter
#endif
