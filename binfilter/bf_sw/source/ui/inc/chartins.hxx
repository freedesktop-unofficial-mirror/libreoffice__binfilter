/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: chartins.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 05:22:57 $
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
#ifndef _CHARTINS_HXX
#define _CHARTINS_HXX

#ifndef _SFX_CHILDWIN_HXX //autogen
#include <bf_sfx2/childwin.hxx>
#endif

#ifdef _CHARTINS_CXX

#ifndef _BASEDLGS_HXX //autogen
#include <bf_sfx2/basedlgs.hxx>
#endif

#ifndef _STDCTRL_HXX
#include <svtools/stdctrl.hxx>
#endif

#ifndef _BUTTON_HXX //autogen
#include <vcl/button.hxx>
#endif

#ifndef _BUTTON_HXX //autogen
#include <vcl/button.hxx>
#endif

#include "autoedit.hxx"
//STRIP001 class SfxItemSet;
namespace binfilter {


//STRIP001 class SwWrtShell;
//STRIP001 class SchMemChart;

//========================================================================

//STRIP001 class SwInsertChartDlg : public SfxModelessDialog
//STRIP001 {
//STRIP001     FixedLine       aFL1;
//STRIP001     CheckBox        aFirstRow;
//STRIP001  CheckBox        aFirstCol;
//STRIP001     FixedText       aRangeFt;
//STRIP001  AutoEdit        aRangeEd;
//STRIP001
//STRIP001     FixedInfo       aTextFt;
//STRIP001
//STRIP001     HelpButton      aHelp;
//STRIP001  CancelButton    aCancel;
//STRIP001
//STRIP001     FixedLine       aHLine;
//STRIP001  PushButton      aPrev;
//STRIP001  PushButton      aNext;
//STRIP001  PushButton      aFinish;
//STRIP001
//STRIP001     SchMemChart *   pChartData;
//STRIP001  ModalDialog*    pChartDlg;
//STRIP001  SfxItemSet*     pInItemSet;
//STRIP001  SfxItemSet*     pOutItemSet;
//STRIP001  SwWrtShell*     pWrtShell;
//STRIP001  String          aAktTableName;
//STRIP001  BOOL            bUpdateChartData;
//STRIP001  BOOL            bChartInserted;
//STRIP001  BOOL            bChildOpen;
//STRIP001
//STRIP001  void UpdateData();
//STRIP001  virtual BOOL        Close();
//STRIP001
//STRIP001 public:
//STRIP001  SwInsertChartDlg( SfxBindings*, SfxChildWindow*,
//STRIP001                    Window *pParent, SwWrtShell * );
//STRIP001  ~SwInsertChartDlg();
//STRIP001
//STRIP001  DECL_LINK( SelTblCellsNotify, SwWrtShell * );
//STRIP001  DECL_LINK( ModifyHdl, Edit* );
//STRIP001  DECL_LINK( NextHdl, Button* );
//STRIP001  DECL_LINK( FinishHdl, Button* );
//STRIP001  DECL_LINK( CloseHdl, Button* );
//STRIP001  DECL_LINK( ClickHdl, CheckBox* );
//STRIP001
//STRIP001     virtual void    Activate();
//STRIP001 };
}//namespace binfilter
#endif
namespace binfilter {//STRIP009
class SwInsertChartChild : public SfxChildWindow
{
public:
    SwInsertChartChild( Window* ,
                        USHORT nId,
                        SfxBindings*,
                        SfxChildWinInfo*  );
    SFX_DECL_CHILDWINDOW( SwInsertChartChild );
};


} //namespace binfilter
#endif

