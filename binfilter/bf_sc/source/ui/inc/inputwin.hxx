/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: inputwin.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 07:08:46 $
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
#include <bf_svtools/lstner.hxx>
#endif
#ifndef _COMBOBOX_HXX //autogen
#include <vcl/combobox.hxx>
#endif
#ifndef _WINDOW_HXX //autogen
#include <vcl/window.hxx>
#endif
#ifndef _TRANSFER_HXX
#include <bf_svtools/transfer.hxx>
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



                        // fuer FunktionsAutopiloten






    DECL_LINK( NotifyHdl, EENotify* );

protected:
    virtual void    Resize();




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


protected:


    virtual void    SFX_NOTIFY( SfxBroadcaster& rBC, const TypeId& rBCType,
                            const SfxHint& rHint, const TypeId& rHintType );

private:
    void            FillRangeNames();

};

//========================================================================

class ScInputWindow : public ToolBox                        // Parent-Toolbox
{
public:
                    ScInputWindow( Window* pParent, SfxBindings* pBind );
    virtual         ~ScInputWindow();

    virtual void    Resize();






    // Fuer FunktionsAutopiloten



    ScInputHandler* GetInputHandler(){ return pInputHdl;}

    void            StateChanged( StateChangedType nType );


protected:

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

