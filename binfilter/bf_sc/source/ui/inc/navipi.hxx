/*************************************************************************
 *
 *  $RCSfile: navipi.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2004-05-05 16:39:44 $
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
#include <svtools/stdctrl.hxx>
#endif
#ifndef _SFXPOOLITEM_HXX //autogen
#include <svtools/poolitem.hxx>
#endif
#ifndef _SFXLSTNER_HXX //autogen
#include <svtools/lstner.hxx>
#endif
#ifndef _SFX_CHILDWIN_HXX //autogen
#include <bf_sfx2/childwin.hxx>
#endif

#ifndef SC_CONTENT_HXX
#include "content.hxx"
#endif

#ifndef _SVEDIT_HXX //autogen
#include <svtools/svmedit.hxx>
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
//STRIP001 class ScScenarioListBox : public ListBox
//STRIP001 {
//STRIP001 public:
//STRIP001          ScScenarioListBox( Window* pParent );
//STRIP001          ~ScScenarioListBox();
//STRIP001
//STRIP001  void UpdateEntries( List* pNewEntryList );
//STRIP001
//STRIP001 protected:
//STRIP001  virtual void    Select();
//STRIP001  virtual void    DoubleClick();
//STRIP001  virtual void    GetFocus();
//STRIP001  virtual void    LoseFocus();
//STRIP001  virtual long    Notify( NotifyEvent& rNEvt );
//STRIP001
//STRIP001 private:
//STRIP001  ScScenarioWindow&   rParent;
//STRIP001  List                aEntryList;
//STRIP001  String              aCurText;
//STRIP001  Accelerator*        pAccel;
//STRIP001  void                ClearEntryList();
//STRIP001  void                CopyEntryList( List& rNewList );
//STRIP001  DECL_LINK( AccelSelectHdl, Accelerator * );
//STRIP001 };

//========================================================================
// class ScScenarioWindow ------------------------------------------------
//========================================================================
//STRIP001 class ScScenarioWindow : public Window
//STRIP001 {
//STRIP001 public:
//STRIP001          ScScenarioWindow( Window* pParent,const String& aQH_List,const String& aQH_Comment);
//STRIP001          ~ScScenarioWindow();
//STRIP001
//STRIP001  void    NotifyState( const SfxPoolItem* pState );
//STRIP001  void    SetComment( const String& rComment )
//STRIP001              { aEdComment.SetText( rComment ); }
//STRIP001
//STRIP001  void    SetSizePixel( const Size& rNewSize );
//STRIP001
//STRIP001 protected:
//STRIP001
//STRIP001  virtual void    Paint( const Rectangle& rRec );
//STRIP001
//STRIP001 private:
//STRIP001  ScScenarioListBox   aLbScenario;
//STRIP001  MultiLineEdit       aEdComment;
//STRIP001 };

//==================================================================
//  class ColumnEdit
//==================================================================
//STRIP001 class ColumnEdit : public SpinField
//STRIP001 {
//STRIP001 public:
//STRIP001          ColumnEdit( ScNavigatorDlg* pParent, const ResId& rResId );
//STRIP001          ~ColumnEdit();
//STRIP001
//STRIP001  USHORT  GetCol() { return nCol; }
//STRIP001  void    SetCol( USHORT nColNo );
//STRIP001
//STRIP001 protected:
//STRIP001  virtual long    Notify( NotifyEvent& rNEvt );
//STRIP001  virtual void    LoseFocus();
//STRIP001  virtual void    Up();
//STRIP001  virtual void    Down();
//STRIP001  virtual void    First();
//STRIP001  virtual void    Last();
//STRIP001
//STRIP001 private:
//STRIP001  ScNavigatorDlg& rDlg;
//STRIP001  USHORT          nCol;
//STRIP001  USHORT          nKeyGroup;
//STRIP001
//STRIP001  void    EvalText        ();
//STRIP001  void    ExecuteCol      ();
//STRIP001  USHORT  AlphaToNum      ( String& rStr );
//STRIP001  USHORT  NumStrToAlpha   ( String& rStr );
//STRIP001  USHORT  NumToAlpha      ( USHORT nColNo, String& rStr );
//STRIP001 };


//==================================================================
//  class RowEdit
//==================================================================
//STRIP001 class RowEdit : public NumericField
//STRIP001 {
//STRIP001 public:
//STRIP001          RowEdit( ScNavigatorDlg* pParent, const ResId& rResId );
//STRIP001          ~RowEdit();
//STRIP001
//STRIP001  USHORT  GetRow()                { return (USHORT)GetValue(); }
//STRIP001  void    SetRow( USHORT nRow ){ SetValue( nRow ); }
//STRIP001
//STRIP001 protected:
//STRIP001  virtual long    Notify( NotifyEvent& rNEvt );
//STRIP001  virtual void    LoseFocus();
//STRIP001
//STRIP001 private:
//STRIP001  ScNavigatorDlg& rDlg;
//STRIP001
//STRIP001  void    ExecuteRow();
//STRIP001 };


//==================================================================
//  class ScDocListBox
//==================================================================
//STRIP001 class ScDocListBox : public ListBox
//STRIP001 {
//STRIP001 public:
//STRIP001          ScDocListBox( ScNavigatorDlg* pParent, const ResId& rResId );
//STRIP001          ~ScDocListBox();
//STRIP001
//STRIP001 protected:
//STRIP001  virtual void    Select();
//STRIP001
//STRIP001 private:
//STRIP001  ScNavigatorDlg& rDlg;
//STRIP001 };


//==================================================================
//  class CommandToolBox
//==================================================================
//STRIP001 class CommandToolBox : public ToolBox
//STRIP001 {
//STRIP001 public:
//STRIP001          CommandToolBox( ScNavigatorDlg* pParent, const ResId& rResId );
//STRIP001          ~CommandToolBox();
//STRIP001
//STRIP001  void Select( USHORT nId );
//STRIP001  void UpdateButtons();
//STRIP001     void InitImageList();
//STRIP001
//STRIP001  virtual void    DataChanged( const DataChangedEvent& rDCEvt );
//STRIP001
//STRIP001 protected:
//STRIP001  virtual void    Select();
//STRIP001  virtual void    Click();
//STRIP001
//STRIP001 private:
//STRIP001  ScNavigatorDlg& rDlg;
//STRIP001 };

//==================================================================
//  class ScNavigatorDlg
//==================================================================

//STRIP001 class ScNavigatorDlg : public Window, public SfxListener
//STRIP001 {
//STRIP001 friend class ScNavigatorControllerItem;
//STRIP001 friend class ScNavigatorDialogWrapper;
//STRIP001 friend class ColumnEdit;
//STRIP001 friend class RowEdit;
//STRIP001 friend class ScDocListBox;
//STRIP001 friend class CommandToolBox;
//STRIP001 friend class ScContentTree;
//STRIP001
//STRIP001 private:
//STRIP001  SfxBindings&        rBindings;      // must be first member
//STRIP001
//STRIP001  ImageList           aCmdImageList;  // must be before aTbxCmd
//STRIP001     ImageList           aCmdImageListH;
//STRIP001  FixedInfo           aFtCol;
//STRIP001  ColumnEdit          aEdCol;
//STRIP001  FixedInfo           aFtRow;
//STRIP001  RowEdit             aEdRow;
//STRIP001  CommandToolBox      aTbxCmd;
//STRIP001  ScContentTree       aLbEntries;
//STRIP001  ScDocListBox        aLbDocuments;
//STRIP001  ScScenarioWindow    aWndScenarios;
//STRIP001
//STRIP001  Timer           aContentTimer;
//STRIP001
//STRIP001  String          aTitleBase;
//STRIP001  String          aStrDragMode;
//STRIP001  String          aStrDisplay;
//STRIP001  String          aStrActive;
//STRIP001  String          aStrNotActive;
//STRIP001  String          aStrHidden;
//STRIP001  String          aStrActiveWin;
//STRIP001
//STRIP001     SfxChildWindowContext*  pContextWin;
//STRIP001     Size                    aInitSize;
//STRIP001     ScArea*                 pMarkArea;
//STRIP001     ScViewData*             pViewData;
//STRIP001
//STRIP001     long            nBorderOffset;
//STRIP001  long            nListModeHeight;
//STRIP001  long            nInitListHeight;
//STRIP001  NavListMode     eListMode;
//STRIP001  USHORT          nDropMode;
//STRIP001  USHORT          nCurCol;
//STRIP001  USHORT          nCurRow;
//STRIP001  USHORT          nCurTab;
//STRIP001  BOOL            bFirstBig;
//STRIP001
//STRIP001  ScNavigatorControllerItem** ppBoundItems;
//STRIP001
//STRIP001  DECL_LINK( TimeHdl, Timer* );
//STRIP001
//STRIP001  void    DoResize();
//STRIP001
//STRIP001     SfxBindings&    GetBindings()
//STRIP001                     { return rBindings; }
//STRIP001     BOOL    GetDBAtCursor( String& rStrName );
//STRIP001  BOOL    GetAreaAtCursor( String& rStrName );
//STRIP001
//STRIP001  void    SetCurrentCell( USHORT nCol, USHORT Row );
//STRIP001  void    SetCurrentCellStr( const String rName );
//STRIP001  void    SetCurrentTable( USHORT nTab );
//STRIP001  void    SetCurrentTableStr( const String rName );
//STRIP001  void    SetCurrentObject( const String rName );
//STRIP001  void    SetCurrentDoc( const String& rDocName );
//STRIP001
//STRIP001     ScTabViewShell*         GetTabViewShell() const;
//STRIP001     ScNavigatorSettings*    GetSettings();
//STRIP001     BOOL                    GetViewData();
//STRIP001
//STRIP001  void    UpdateColumn    ( const USHORT* pCol = NULL );
//STRIP001  void    UpdateRow       ( const USHORT* pRow = NULL );
//STRIP001  void    UpdateTable     ( const USHORT* pTab = NULL );
//STRIP001  void    UpdateAll       ();
//STRIP001
//STRIP001  void    GetDocNames(const String* pSelEntry = NULL);
//STRIP001
//STRIP001  void    SetListMode     ( NavListMode eMode, BOOL bSetSize = TRUE );
//STRIP001  void    ShowList        ( BOOL bShow, BOOL bSetSize );
//STRIP001  void    ShowScenarios   ( BOOL bShow, BOOL bSetSize );
//STRIP001
//STRIP001  void    SetDropMode(USHORT nNew);
//STRIP001  USHORT  GetDropMode() const         { return nDropMode; }
//STRIP001
//STRIP001  const String& GetStrDragMode() const    { return aStrDragMode; }
//STRIP001  const String& GetStrDisplay() const     { return aStrDisplay; }
//STRIP001
//STRIP001  void    CheckDataArea   ();
//STRIP001  void    MarkDataArea    ();
//STRIP001  void    UnmarkDataArea  ();
//STRIP001  void    StartOfDataArea ();
//STRIP001  void    EndOfDataArea   ();
//STRIP001
//STRIP001  static void ReleaseFocus();
//STRIP001
//STRIP001 protected:
//STRIP001  virtual void    Resize();
//STRIP001  virtual void    Paint( const Rectangle& rRec );
//STRIP001  virtual void    Resizing( Size& rSize );
//STRIP001
//STRIP001 public:
//STRIP001              ScNavigatorDlg( SfxBindings* pB, SfxChildWindowContext* pCW, Window* pParent );
//STRIP001              ~ScNavigatorDlg();
//STRIP001
//STRIP001  virtual void    SFX_NOTIFY( SfxBroadcaster& rBC, const TypeId& rBCType,
//STRIP001                          const SfxHint& rHint, const TypeId& rHintType );
//STRIP001
//STRIP001  void            CursorPosChanged();
//STRIP001
//STRIP001  virtual SfxChildAlignment
//STRIP001                  CheckAlignment(SfxChildAlignment,SfxChildAlignment);
//STRIP001  virtual void    DataChanged( const DataChangedEvent& rDCEvt );
//STRIP001 };

//==================================================================

class ScNavigatorDialogWrapper: public SfxChildWindowContext
{
public:
            ScNavigatorDialogWrapper( Window*           pParent,
                                      USHORT            nId,
                                      SfxBindings*      pBindings,
                                      SfxChildWinInfo*  pInfo ):SfxChildWindowContext( nId ){DBG_BF_ASSERT(0, "STRIP");} //STRIP001 SfxChildWinInfo*    pInfo );

    SFX_DECL_CHILDWINDOW_CONTEXT(ScNavigatorDialogWrapper)

//STRIP001  virtual void    Resizing( Size& rSize );

//STRIP001 private:
//STRIP001  ScNavigatorDlg* pNavigator;
};



} //namespace binfilter
#endif // SC_NAVIPI_HXX

