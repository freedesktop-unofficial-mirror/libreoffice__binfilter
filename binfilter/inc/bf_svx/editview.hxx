/*************************************************************************
 *
 *  $RCSfile: editview.hxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:23:51 $
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

// MyEDITVIEW, wegen exportiertem EditView
#ifndef _MyEDITVIEW_HXX
#define _MyEDITVIEW_HXX

#ifndef _RSCSFX_HXX //autogen
#include <rsc/rscsfx.hxx>
#endif
#ifndef _LANG_HXX //autogen
#include <tools/lang.hxx>
#endif

#ifndef _TOOLS_COLOR_HXX
#include <tools/color.hxx>
#endif

class EditEngine;
class ImpEditEngine;
class ImpEditView;
class SvxSearchItem;
class SvxFieldItem;
class Window;
class Pointer;
class Cursor;
class KeyEvent;
class MouseEvent;
class DropEvent;
class CommandEvent;
class Rectangle;
class Link;
class Pair;
class Point;
class Range;
class SvStream;
class SvKeyValueIterator;
class SfxStyleSheet;

#ifndef _EDITDATA_HXX
#include <bf_svx/editdata.hxx>
#endif

#ifndef _COM_SUN_STAR_UNO_REFERENCE_H_
#include <com/sun/star/uno/Reference.h>
#endif

namespace com {
namespace sun {
namespace star {
namespace datatransfer {
    class XTransferable;
}}}}

class EditView
{
    friend class EditEngine;
    friend class ImpEditEngine;
    friend class EditSelFunctionSet;

public: // brauche ich fuer Undo
    ImpEditView*    GetImpEditView() const      { return pImpEditView; }
//STRIP001  ImpEditEngine*  GetImpEditEngine() const;

private:
    ImpEditView*    pImpEditView;

                    EditView( const EditView& );
//STRIP001  EditView&       operator=( const EditView& );

public:
                    EditView( EditEngine* pEng, Window* pWindow );
    virtual         ~EditView();

//STRIP001  void            SetEditEngine( EditEngine* pEditEngine );
    EditEngine*     GetEditEngine() const;

//STRIP001  void            SetWindow( Window* pWin );
    Window*         GetWindow() const;

//STRIP001  void            Paint( const Rectangle& rRect );
//STRIP001  void            Invalidate();
//STRIP001  Pair            Scroll( long nHorzScroll, long nVertScroll, BYTE nRangeCheck = RGCHK_NEG );

    void            ShowCursor( BOOL bGotoCursor = TRUE, BOOL bForceVisCursor = TRUE );
    void            HideCursor();

//STRIP001  EESelectionMode GetSelectionMode() const;
    void            SetSelectionMode( EESelectionMode eMode );

//STRIP001  void            SetReadOnly( BOOL bReadOnly );
    BOOL            IsReadOnly() const;

    BOOL            HasSelection() const;
    ESelection      GetSelection() const;
    void            SetSelection( const ESelection& rNewSel );
//STRIP001  BOOL            SelectCurrentWord();

//STRIP001  void            IndentBlock();
//STRIP001  void            UnindentBlock();

    BOOL            IsInsertMode() const;
//STRIP001  void            SetInsertMode( BOOL bInsert );

//STRIP001  void            ReplaceSelected( const String& rStr );
//STRIP001  String          GetSelected();
//STRIP001  void            DeleteSelected();

//STRIP001  USHORT          GetSelectedScriptType() const;

                        // Position der VisArea im Ausgabefenster.
                        // Eine Groessenaenderung betrifft auch die VisArea
    void                SetOutputArea( const Rectangle& rRec );
    const Rectangle&    GetOutputArea() const;

                        // Dokumentposition.
                        // Eine Groessenaenderung betrifft auch die VisArea
    void                SetVisArea( const Rectangle& rRec );
    const Rectangle&    GetVisArea() const;

//STRIP001  void            SetPointer( const Pointer& rPointer );
    const Pointer&  GetPointer() const;

//STRIP001  void            SetCursor( const Cursor& rCursor );
//STRIP001  Cursor*         GetCursor() const;

//STRIP001  void            InsertText( const String& rNew, BOOL bSelect = FALSE );

    BOOL            PostKeyEvent( const KeyEvent& rKeyEvent );

//STRIP001  BOOL            MouseButtonUp( const MouseEvent& rMouseEvent );
//STRIP001  BOOL            MouseButtonDown( const MouseEvent& rMouseEvent );
//STRIP001  BOOL            MouseMove( const MouseEvent& rMouseEvent );
//STRIP001  void            Command( const CommandEvent& rCEvt );

//STRIP001  BOOL            Drop( const DropEvent& rEvt );
//STRIP001  BOOL            QueryDrop( DropEvent& rEvt );
//STRIP001  ESelection      GetDropPos();

    void            Cut();
    void            Copy();
    void            Paste();
//STRIP001  void            PasteSpecial();

//STRIP001  void            EnablePaste( BOOL bEnable );
//STRIP001  BOOL            IsPasteEnabled() const;

//STRIP001  void            Undo();
//STRIP001  void            Redo();

    // speziell fuer Olli
//STRIP001  USHORT          GetParagraph( const Point& rMousePosPixel );
//STRIP001  Point           GetWindowPosTopLeft( USHORT nParagraph );
//STRIP001  void            MoveParagraphs( Range aParagraphs, USHORT nNewPos );
//STRIP001     void            MoveParagraphs( long nDiff );

//STRIP001  const SfxItemSet&   GetEmptyItemSet();
//STRIP001  SfxItemSet          GetAttribs();
//STRIP001  void                SetAttribs( const SfxItemSet& rSet );
//STRIP001  void                SetParaAttribs( const SfxItemSet& rSet, USHORT nPara );
//STRIP001  void                RemoveAttribs( BOOL bRemoveParaAttribs = FALSE, USHORT nWhich = 0 );
//STRIP001  void                RemoveCharAttribs( USHORT nPara, USHORT nWhich = 0 );

//STRIP001  ULONG           Read( SvStream& rInput, EETextFormat eFormat, BOOL bSelect = FALSE, SvKeyValueIterator* pHTTPHeaderAttrs = NULL );
//STRIP001  ULONG           Write( SvStream& rOutput, EETextFormat eFormat );

//STRIP001  void            SetBackgroundColor( const Color& rColor );
//STRIP001  Color           GetBackgroundColor() const;

//STRIP001  void            SetControlWord( ULONG nWord );
//STRIP001  ULONG           GetControlWord() const;

//STRIP001  EditTextObject* CreateTextObject();
//STRIP001  void            InsertText( const EditTextObject& rTextObject );
//STRIP001  void            InsertText( ::com::sun::star::uno::Reference< ::com::sun::star::datatransfer::XTransferable > xDataObj, BOOL bUseSpecial );

    // An EditView, damit bei TRUE flackerfreies Update:
//STRIP001  void            SetEditEngineUpdateMode( BOOL bUpdate );
//STRIP001  void            ForceUpdate();

//STRIP001  SfxStyleSheet*  GetStyleSheet() const;
    void            SetStyleSheet( SfxStyleSheet* pStyle );

//STRIP001  void            SetAnchorMode( EVAnchorMode eMode );
//STRIP001  EVAnchorMode    GetAnchorMode() const;

//STRIP001  BOOL            MatchGroup();

//STRIP001  void            CompleteAutoCorrect();

//STRIP001  EESpellState    StartSpeller( BOOL bMultipleDoc = FALSE );
//STRIP001  EESpellState    StartSpeller( LanguageType eLang, BOOL bMultipleDoc = FALSE );
//STRIP001  EESpellState    StartThesaurus();
//STRIP001  EESpellState    StartThesaurus( LanguageType eLang );
//STRIP001  USHORT          StartSearchAndReplace( const SvxSearchItem& rSearchItem );

//STRIP001  void            TransliterateText( sal_Int32 nTransliterationMode );

//STRIP001  BOOL            IsCursorAtWrongSpelledWord( BOOL bMarkIfWrong = FALSE );
//STRIP001  BOOL            IsWrongSpelledWordAtPos( const Point& rPosPixel, BOOL bMarkIfWrong = FALSE );
//STRIP001  void            SpellIgnoreWord();
//STRIP001  void            ExecuteSpellPopup( const Point& rPosPixel, Link* pCallBack = 0 );

//STRIP001  void                InsertField( const SvxFieldItem& rFld );
//STRIP001  const SvxFieldItem* GetFieldUnderMousePointer() const;
//STRIP001  const SvxFieldItem* GetFieldUnderMousePointer( USHORT& nPara, xub_StrLen& nPos ) const;
    const SvxFieldItem* GetField( const Point& rPos, USHORT* pnPara = NULL, xub_StrLen* pnPos = NULL ) const;

//STRIP001  const SvxFieldItem* GetFieldAtSelection() const;

//STRIP001  String          GetWordUnderMousePointer() const;
//STRIP001  String          GetWordUnderMousePointer( Rectangle& rWordRect ) const;

//STRIP001  void            SetInvalidateMore( USHORT nPixel );
//STRIP001  USHORT          GetInvalidateMore() const;
};

#endif // _MyEDITVIEW_HXX
