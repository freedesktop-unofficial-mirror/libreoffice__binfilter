/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: inputwin.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-07 19:55:26 $
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

#ifndef SC_INPUTWIN_HXX
#define SC_INPUTWIN_HXX


#ifndef _TOOLBOX_HXX //autogen
#include <vcl/toolbox.hxx>
#endif
#ifndef _SFX_CHILDWIN_HXX //autogen
#include <bf_sfx2/childwin.hxx>
#endif
#ifndef _SFXLSTNER_HXX //autogen
#include <svtools/lstner.hxx>
#endif
#ifndef _COMBOBOX_HXX //autogen
#include <vcl/combobox.hxx>
#endif
#ifndef _WINDOW_HXX //autogen
#include <vcl/window.hxx>
#endif
#ifndef _TRANSFER_HXX
#include <svtools/transfer.hxx>
#endif
namespace binfilter {

class ScEditEngineDefaulter;
class EditView;
struct ESelection;
class ScInputHandler;
class ScAccessibleEditLineTextData;
struct EENotify;
class ScRangeList;

//========================================================================

class ScTextWnd : public Window, public DragSourceHelper        // edit window
{
public:
                    ScTextWnd( Window* pParent );
    virtual         ~ScTextWnd();

//STRIP001  void            SetTextString( const String& rString );
//STRIP001  const String&   GetTextString() const;

//STRIP001  BOOL            IsActive();
//STRIP001  EditView*       GetEditView();

                        // fuer FunktionsAutopiloten
//STRIP001  void            MakeDialogEditView();

//STRIP001  void            StartEditEngine();
//STRIP001  void            StopEditEngine( BOOL bAll );

//STRIP001  virtual void    DataChanged( const DataChangedEvent& rDCEvt );

//STRIP001  void            SetFormulaMode( BOOL bSet );

//STRIP001  virtual ::com::sun::star::uno::Reference< ::com::sun::star::accessibility::XAccessible > CreateAccessible();

//STRIP001     void            SetAccessibleTextData(ScAccessibleEditLineTextData* pTextData) {pAccTextData = pTextData;}

    DECL_LINK( NotifyHdl, EENotify* );

protected:
//STRIP001  virtual void    Paint( const Rectangle& rRec );
    virtual void    Resize();

//STRIP001  virtual void    MouseMove( const MouseEvent& rMEvt );
//STRIP001  virtual void    MouseButtonDown( const MouseEvent& rMEvt );
//STRIP001  virtual void    MouseButtonUp( const MouseEvent& rMEvt );
//STRIP001  virtual void    Command( const CommandEvent& rCEvt );
//STRIP001  virtual void    KeyInput(const KeyEvent& rKEvt);
//STRIP001  virtual void    GetFocus();
//STRIP001  virtual void    LoseFocus();

//STRIP001  virtual void    StartDrag( sal_Int8 nAction, const Point& rPosPixel );

//STRIP001  virtual String  GetText() const;

private:
    void            ImplInitSettings();
    void            UpdateAutoCorrFlag();

private:
    String      aString;
    Font        aTextFont;
    ScEditEngineDefaulter*  pEditEngine;            // erst bei Bedarf angelegt
    EditView*   pEditView;
    ScAccessibleEditLineTextData* pAccTextData;
    BOOL        bIsRTL;
    BOOL        bIsInsertMode;
    BOOL        bFormulaMode;

    // #102710#; this flag should be true if a key input or a command is handled
    // it prevents the call of InputChanged in the ModifyHandler of the EditEngine
    BOOL        bInputMode;
};

//========================================================================

class ScPosWnd : public ComboBox, public SfxListener        // Positionsanzeige
{
private:
    String          aPosStr;
    Accelerator*    pAccel;
    BOOL            bFormulaMode;
    BOOL            bTopHadFocus;

public:
                    ScPosWnd( Window* pParent );
    virtual         ~ScPosWnd();

//STRIP001  void            SetPos( const String& rPosStr );        // angezeigter Text
//STRIP001  void            SetFormulaMode( BOOL bSet );

protected:
//STRIP001  virtual void    Select();

//STRIP001  virtual long    Notify( NotifyEvent& rNEvt );

    virtual void    SFX_NOTIFY( SfxBroadcaster& rBC, const TypeId& rBCType,
                            const SfxHint& rHint, const TypeId& rHintType );

private:
    void            FillRangeNames();
//STRIP001  void            FillFunctions();
//STRIP001  void            DoEnter();

//STRIP001  void            ReleaseFocus_Impl();
};

//========================================================================

class ScInputWindow : public ToolBox                        // Parent-Toolbox
{
public:
                    ScInputWindow( Window* pParent, SfxBindings* pBind );
    virtual         ~ScInputWindow();

    virtual void    Resize();
//STRIP001  virtual void    Select();

//STRIP001  void            SetFuncString( const String& rString, BOOL bDoEdit = TRUE );
//STRIP001  void            SetPosString( const String& rStr );
//STRIP001  void            SetTextString( const String& rString );
//STRIP001  const String&   GetTextString();

//STRIP001  void            SetOkCancelMode();
//STRIP001  void            SetSumAssignMode();
//STRIP001  void            EnableButtons( BOOL bEnable = TRUE );

//STRIP001  void            SetFormulaMode( BOOL bSet );

//STRIP001  BOOL            IsActive();
//STRIP001  EditView*       GetEditView();
//STRIP001  EditView*       ActivateEdit( const String&     rText,
//STRIP001                                const ESelection& rSel );

//STRIP001  void            TextGrabFocus();
//STRIP001  void            TextInvalidate();
//STRIP001  void            SwitchToTextWin();
//STRIP001
//STRIP001  void            PosGrabFocus();

    // Fuer FunktionsAutopiloten
//STRIP001  void            MakeDialogEditView();

//STRIP001  void            StopEditEngine( BOOL bAll );

//STRIP001  void            SetInputHandler( ScInputHandler* pNew );

    ScInputHandler* GetInputHandler(){ return pInputHdl;}

    void            StateChanged( StateChangedType nType );
//STRIP001  virtual void    DataChanged( const DataChangedEvent& rDCEvt );


protected:
//STRIP001  virtual void    SetText( const String& rString );
//STRIP001  virtual String  GetText() const;

    sal_Bool        UseSubTotal( ScRangeList* pRangeList ) const;

private:
    ScPosWnd        aWndPos;
    ScTextWnd       aTextWindow;
    ScInputHandler* pInputHdl;
    SfxBindings*    pBindings;
    String          aTextOk;
    String          aTextCancel;
    String          aTextSum;
    String          aTextEqual;
    BOOL            bIsOkCancelMode;
};

//==================================================================

class ScInputWindowWrapper : public SfxChildWindow
{
public:
            ScInputWindowWrapper( Window*           pParent,
                                  USHORT            nId,
                                  SfxBindings*      pBindings,
                                  SfxChildWinInfo*  pInfo );

    SFX_DECL_CHILDWINDOW(ScInputWindowWrapper);
};


} //namespace binfilter
#endif

