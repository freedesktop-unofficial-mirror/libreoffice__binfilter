/*************************************************************************
 *
 *  $RCSfile: inputhdl.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2004-05-05 16:39:43 $
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

#ifndef SC_INPUTHDL_HXX
#define SC_INPUTHDL_HXX

#ifndef SC_SCGLOB_HXX
#include "global.hxx"
#endif

#ifndef _FRACT_HXX //autogen
#include <tools/fract.hxx>
#endif

#ifndef _GEN_HXX //autogen
#include <tools/gen.hxx>
#endif
class Timer;
class KeyEvent;
namespace binfilter {

class ScDocument;
class ScTabView;
class ScTabViewShell;
class ScInputWindow;
class ScPatternAttr;
class EditEngine;
class ScEditEngineDefaulter;
class EditView;
class EditTextObject;
class ScInputHdlState;
class TypedStrCollection;
class ScRangeFindList;
class CommandEvent;

struct ESelection;

//========================================================================
//  ScInputHandler
//========================================================================

class ScInputHandler
{
private:
    ScInputWindow*          pInputWin;

    ScEditEngineDefaulter*  pEngine;                // editierte Daten in der Tabelle
    EditView*               pTableView;                 // aktive EditView dazu
    EditView*               pTopView;                   // EditView in der Eingabezeile

    TypedStrCollection*     pColumnData;
    TypedStrCollection*     pFormulaData;
    ULONG                   nTipVisible;
    String                  aManualTip;
    String                  aAutoSearch;
    USHORT                  nAutoPos;
    BOOL                    bUseTab;                    // Blaettern moeglich

    BOOL                    bTextValid;                 // Text noch nicht in Edit-Engine
    String                  aCurrentText;

    String                  aFormText;                  // fuer Funktions-Autopilot
    xub_StrLen              nFormSelStart;              // Selektion fuer Funktions-Autopilot
    xub_StrLen              nFormSelEnd;

    USHORT                  nAutoPar;                   // autom.parentheses than can be overwritten

    ScAddress               aCursorPos;
    ScInputMode             eMode;
    BOOL                    bModified;
    BOOL                    bSelIsRef;
    BOOL                    bFormulaMode;
    BOOL                    bInRangeUpdate;
    BOOL                    bParenthesisShown;
    BOOL                    bCreatingFuncView;
    BOOL                    bInEnterHandler;
    BOOL                    bCommandErrorShown;
    BOOL                    bInOwnChange;

    BOOL                    bProtected;
    BOOL                    bCellHasPercentFormat;
    ULONG                   nValidation;
    USHORT                  nAttrAdjust;                // enum SvxCellHorJustify

    Fraction                aScaleX;                    // fuer Ref-MapMode
    Fraction                aScaleY;

    ScTabViewShell*         pRefViewSh;
    ScTabViewShell*         pActiveViewSh;

    const ScPatternAttr*    pLastPattern;
    SfxItemSet*             pEditDefaults;
    BOOL                    bLastIsSymbol;

    ScInputHdlState*        pLastState;
    Timer*                  pDelayTimer;

    ScRangeFindList*        pRangeFindList;

    static BOOL             bAutoComplete;              // aus App-Optionen
    static BOOL             bOptLoaded;

#ifdef _INPUTHDL_CXX
private:
//STRIP001  void            UpdateActiveView();
//STRIP001  void            SetAllUpdateMode( BOOL bUpdate );
//STRIP001  void            SyncViews( EditView* pSourceView = NULL );
//STRIP001  BOOL            StartTable( sal_Unicode cTyped, BOOL bFromCommand );
//STRIP001  void            RemoveSelection();
//STRIP001  void            UpdateFormulaMode();
//STRIP001  void            InvalidateAttribs();
    void            ImplCreateEditEngine();
//STRIP001  DECL_LINK(      DelayTimer, Timer* );
//STRIP001  void            GetColData();
//STRIP001  void            UseColData();
//STRIP001  void            NextAutoEntry( BOOL bBack );
//STRIP001  void            UpdateAdjust( sal_Unicode cTyped );
//STRIP001  void            GetFormulaData();
//STRIP001  void            UseFormulaData();
//STRIP001  void            NextFormulaEntry( BOOL bBack );
//STRIP001  void            PasteFunctionData();
//STRIP001  void            PasteManualTip();
//STRIP001  EditView*       GetFuncEditView();
//STRIP001  void            RemoveAdjust();
//STRIP001  void            RemoveRangeFinder();
    void            DeleteRangeFinder();
//STRIP001  void            UpdateParenthesis();
//STRIP001  void            UpdateAutoCorrFlag();
    void            ResetAutoPar();
//STRIP001  void            AutoParAdded();
//STRIP001  BOOL            CursorAtClosingPar();
//STRIP001  void            SkipClosingPar();
    void            StopInputWinEngine( BOOL bAll );
    DECL_LINK( ModifyHdl, void* );
#endif

public:
                    ScInputHandler();
    virtual         ~ScInputHandler();

//STRIP001  void            SetMode( ScInputMode eNewMode );
    BOOL            IsInputMode() const { return (eMode != SC_INPUT_NONE); }
    BOOL            IsEditMode() const  { return (eMode != SC_INPUT_NONE &&
                                                  eMode != SC_INPUT_TYPE); }
    BOOL            IsTopMode() const   { return (eMode == SC_INPUT_TOP);  }

//STRIP001  const String&   GetEditString();
    const String&   GetFormString() const   { return aFormText; }

//STRIP001  BOOL            GetTextAndFields( ScEditEngineDefaulter& rDestEngine );

//STRIP001  BOOL            KeyInput( const KeyEvent& rKEvt, BOOL bStartEdit = FALSE );
    void            EnterHandler( BYTE nBlockMode = 0 );
//STRIP001  void            CancelHandler();
//STRIP001  void            SetReference( const ScRange& rRef, ScDocument* pDoc );
//STRIP001  void            AddRefEntry();

//STRIP001  BOOL            InputCommand( const CommandEvent& rCEvt, BOOL bForce );

//STRIP001  void            InsertFunction( const String& rFuncName, BOOL bAddPar = TRUE );
//STRIP001  void            ClearText();

//STRIP001  void            InputSelection( EditView* pView );
//STRIP001  void            InputChanged( EditView* pView );

    void            ViewShellGone(ScTabViewShell* pViewSh){DBG_BF_ASSERT(0, "STRIP");}; //STRIP001 void         ViewShellGone(ScTabViewShell* pViewSh);
    void            SetRefViewShell(ScTabViewShell* pRefVsh) {pRefViewSh=pRefVsh;}


    void            NotifyChange( const ScInputHdlState* pState, BOOL bForce = FALSE,
                                    ScTabViewShell* pSourceSh = NULL,
                                    BOOL bStopEditing = TRUE);

//STRIP001  void            ResetDelayTimer(); //BugId 54702

    void            HideTip();
//STRIP001  void            ShowTip( const String& rText );     // am Cursor

    void            SetRefScale( const Fraction& rX, const Fraction& rY );
    void            UpdateRefDevice();

//STRIP001  EditView*       GetActiveView();
    EditView*       GetTableView()      { return pTableView; }
    EditView*       GetTopView()        { return pTopView; }

//STRIP001  BOOL            DataChanging( sal_Unicode cTyped = 0, BOOL bFromCommand = FALSE );
//STRIP001  void            DataChanged();

    BOOL            TakesReturn() const     { return ( nTipVisible != 0 ); }

    void            SetModified()       { bModified = TRUE; }

    BOOL            GetSelIsRef() const     { return bSelIsRef; }
    void            SetSelIsRef(BOOL bSet)  { bSelIsRef = bSet; }

//STRIP001  void            ShowRefFrame();

    ScRangeFindList* GetRangeFindList()     { return pRangeFindList; }

//STRIP001  void            UpdateRange( USHORT nIndex, const ScRange& rNew );

    // Kommunikation mit Funktionsautopilot
//STRIP001  void            InputGetSelection       ( xub_StrLen& rStart, xub_StrLen& rEnd );
//STRIP001  void            InputSetSelection       ( xub_StrLen nStart, xub_StrLen nEnd );
//STRIP001  void            InputReplaceSelection   ( const String& rStr );
//STRIP001  String          InputGetFormulaStr      ();

    BOOL            IsFormulaMode() const                   { return bFormulaMode; }
    ScInputWindow*  GetInputWindow()                        { return pInputWin; }
    void            SetInputWindow( ScInputWindow* pNew )   { pInputWin = pNew; }

    BOOL            IsInEnterHandler() const                { return bInEnterHandler; }
    BOOL            IsInOwnChange() const                   { return bInOwnChange; }

//STRIP001  BOOL            IsModalMode( SfxObjectShell* pDocSh );

//STRIP001  void            ActivateInputWindow( const String&     rText,
//STRIP001                                       const ESelection& rSel );

//STRIP001  void            ForgetLastPattern();

//STRIP001  void            UpdateSpellSettings( BOOL bFromStartTab = FALSE );

//STRIP001  void            FormulaPreview();

//STRIP001  Size            GetTextSize();      // in 1/100mm

                    // eigentlich private, fuer SID_INPUT_SUM public
//STRIP001  void            InitRangeFinder( const String& rFormula );

    static void     SetAutoComplete(BOOL bSet)  { bAutoComplete = bSet; }
};

//========================================================================
//  ScInputHdlState
//========================================================================
class ScInputHdlState
{
    friend class ScInputHandler;

public:
        ScInputHdlState( const ScAddress& rCurPos,
                         const ScAddress& rStartPos,
                         const ScAddress& rEndPos,
                         const String& rString,
                         const EditTextObject* pData );
        ScInputHdlState( const ScInputHdlState& rCpy );
        ~ScInputHdlState();

    ScInputHdlState&    operator= ( const ScInputHdlState& r );
//STRIP001  int                 operator==( const ScInputHdlState& r ) const;
//STRIP001  int                 operator!=( const ScInputHdlState& r ) const
//STRIP001                          { return !operator==( r ); }

    const ScAddress&        GetPos() const          { return aCursorPos; }
    const ScAddress&        GetStartPos() const     { return aStartPos; }
    const ScAddress&        GetEndPos() const       { return aEndPos; }
    const String&           GetString() const       { return aString; }
    const EditTextObject*   GetEditData() const     { return pEditData; }

private:
    ScAddress       aCursorPos;
     ScAddress      aStartPos;
     ScAddress      aEndPos;
     String         aString;
     EditTextObject* pEditData;
};



} //namespace binfilter
#endif


