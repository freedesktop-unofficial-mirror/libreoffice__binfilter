/*************************************************************************
 *
 *  $RCSfile: editeng.hxx,v $
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

// MyEDITENG, wegen exportiertem EditEng
#ifndef _MyEDITENG_HXX
#define _MyEDITENG_HXX

class ImpEditEngine;
class EditView;
class OutputDevice;
class EditUndo;
class SvxFont;
class SfxUndoManager;
class SfxItemPool;
class SfxStyleSheet;
class String;
class SfxStyleSheetPool;
class SvxSearchItem;
class SvxFieldItem;
class SvxCharSetColorItem;
class SfxUndoAction;
class MapMode;
class Color;
class Font;
class KeyEvent;
class XPolyPolygon;
class PolyPolygon;
class Size;
class Point;
class Rectangle;
class SvStream;
class Link;
class OutputDevice;
class SvUShorts;
class SfxPoolItem;
class SvxNumBulletItem;
class SvxBulletItem;
class SvxLRSpaceItem;
class SvKeyValueIterator;
class SvxForbiddenCharactersTable;

#include <vos/ref.hxx>

#ifndef _COM_SUN_STAR_UNO_REFERENCE_H_
#include <com/sun/star/uno/Reference.h>
#endif

namespace com { namespace sun { namespace star {
  namespace linguistic2 {
    class XSpellChecker1;
    class XHyphenator;
}
  namespace datatransfer {
    class XTransferable;
}
}}}

#ifndef _RSCSFX_HXX //autogen
#include <rsc/rscsfx.hxx>
#endif
#ifndef _EDITDATA_HXX
#include <bf_svx/editdata.hxx>
#endif
#ifndef _LANG_HXX //autogen
#include <tools/lang.hxx>
#endif

#include <tools/rtti.hxx>   // wegen typedef TypeId

/** values for GetAttribs
*/
const sal_uInt8 EditEngineAttribs_All   = 0;        /// returns all attributes even when theire not set
const sal_uInt8 EditEngineAttribs_HardAndPara = 1;  /// returns all attributes set on paragraph and on portions
const sal_uInt8 EditEngineAttribs_OnlyHard = 2;     /// returns only attributes hard set on portions

#define GETATTRIBS_STYLESHEET   (sal_uInt8)0x01
#define GETATTRIBS_PARAATTRIBS  (sal_uInt8)0x02
#define GETATTRIBS_CHARATTRIBS  (sal_uInt8)0x04
#define GETATTRIBS_ALL          (sal_uInt8)0xFF

class EditEngine
{
    friend class EditView;
    friend class ImpEditView;
    friend class EditDbg;
    friend class Outliner;

private:
    ImpEditEngine*  pImpEditEngine;

                    EditEngine( const EditEngine& );
    EditEngine&     operator=( const EditEngine& );

#if _SOLAR__PRIVATE
    BOOL                PostKeyEvent( const KeyEvent& rKeyEvent, EditView* pView );
#endif

public:
                    EditEngine::EditEngine( SfxItemPool* pItemPool );
    virtual         ~EditEngine();

    const SfxItemSet&   GetEmptyItemSet();

    void            SetDefTab( USHORT nDefTab );
//STRIP001  USHORT          GetDefTab() const;

    void            SetRefDevice( OutputDevice* pRefDef );
    OutputDevice*   GetRefDevice() const;

    void            SetRefMapMode( const MapMode& rMapMode );
    MapMode         GetRefMapMode();

    void            SetUpdateMode( BOOL bUpdate );
    BOOL            GetUpdateMode() const;

    void            SetBackgroundColor( const Color& rColor );
//STRIP001  Color           GetBackgroundColor() const;
    Color           GetAutoColor() const;
    void            EnableAutoColor( BOOL b );
//STRIP001     BOOL            IsAutoColorEnabled() const;
//STRIP001     void            ForceAutoColor( BOOL b );
    BOOL            IsForceAutoColor() const;

    void            InsertView( EditView* pEditView, USHORT nIndex = EE_APPEND );
    EditView*       RemoveView( EditView* pEditView );
//STRIP001  EditView*       RemoveView( USHORT nIndex = EE_APPEND );
//STRIP001  EditView*       GetView( USHORT nIndex = 0 ) const;
//STRIP001  USHORT          GetViewCount() const;
    BOOL            HasView( EditView* pView ) const;
//STRIP001  EditView*       GetActiveView() const;
//STRIP001  void            SetActiveView( EditView* pView );

    void            SetPaperSize( const Size& rSize );
    const Size&     GetPaperSize() const;

    void            SetVertical( BOOL bVertical );
    BOOL            IsVertical() const;

//STRIP001     void                        SetDefaultHorizontalTextDirection( EEHorizontalTextDirection eHTextDir );
//STRIP001     EEHorizontalTextDirection   GetDefaultHorizontalTextDirection() const;

    USHORT          GetScriptType( const ESelection& rSelection ) const;
    LanguageType    GetLanguage( USHORT nPara, USHORT nPos ) const;

//STRIP001  void            TransliterateText( const ESelection& rSelection, sal_Int32 nTransliterationMode );

    void            SetAsianCompressionMode( USHORT nCompression );
//STRIP001  USHORT          GetAsianCompressionMode() const;

    void            SetKernAsianPunctuation( BOOL bEnabled );
//STRIP001     BOOL            IsKernAsianPunctuation() const;

//STRIP001  void                SetPolygon( const XPolyPolygon& rPoly );
//STRIP001  void                SetPolygon( const XPolyPolygon& rPoly, const XPolyPolygon* pXorPoly );
    void                ClearPolygon();
//STRIP001  const PolyPolygon*  GetPolygon();

//STRIP001  const Size&     GetMinAutoPaperSize() const;
    void            SetMinAutoPaperSize( const Size& rSz );

//STRIP001  const Size&     GetMaxAutoPaperSize() const;
    void            SetMaxAutoPaperSize( const Size& rSz );

    String          GetText( LineEnd eEnd = LINEEND_LF ) const;
    String          GetText( const ESelection& rSelection, const LineEnd eEnd = LINEEND_LF ) const;
    ULONG           GetTextLen() const;
    ULONG           GetTextHeight() const;
    ULONG           CalcTextWidth();

    String          GetText( USHORT nParagraph ) const;
    xub_StrLen          GetTextLen( USHORT nParagraph ) const;
    ULONG           GetTextHeight( USHORT nParagraph ) const;

    USHORT          GetParagraphCount() const;

    USHORT          GetLineCount( USHORT nParagraph ) const;
    xub_StrLen      GetLineLen( USHORT nParagraph, USHORT nLine ) const;
    ULONG           GetLineHeight( USHORT nParagraph, USHORT nLine = 0 );
    USHORT          GetFirstLineOffset( USHORT nParagraph );
    ParagraphInfos  GetParagraphInfos( USHORT nPara );
    USHORT          FindParagraph( long nDocPosY );
    EPosition       FindDocPosition( const Point& rDocPos ) const;
    Rectangle       GetCharacterBounds( const EPosition& rPos ) const;

//STRIP001  String          GetWord( USHORT nPara, xub_StrLen nIndex );

    ESelection      GetWord( const ESelection& rSelection, USHORT nWordType ) const;
//STRIP001     ESelection      WordLeft( const ESelection& rSelection, USHORT nWordType  ) const;
//STRIP001     ESelection      WordRight( const ESelection& rSelection, USHORT nWordType  ) const;
//STRIP001     ESelection      CursorLeft( const ESelection& rSelection, USHORT nCharacterIteratorMode ) const;
//STRIP001     ESelection      CursorRight( const ESelection& rSelection, USHORT nCharacterIteratorMode ) const;

    void            Clear();
    void            SetText( const String& rStr );

    EditTextObject* CreateTextObject();
    EditTextObject* CreateTextObject( USHORT nPara, USHORT nParas = 1 );
//STRIP001  EditTextObject* CreateTextObject( const ESelection& rESelection );
    void            SetText( const EditTextObject& rTextObject );

//STRIP001  void            RemoveParagraph( USHORT nPara );
//STRIP001  void            InsertParagraph( USHORT nPara, const EditTextObject& rTxtObj );
    void            InsertParagraph( USHORT nPara, const String& rText);

//STRIP001  void            SetText( USHORT nPara, const EditTextObject& rTxtObj );
    void            SetText( USHORT nPara, const String& rText);

    void                SetParaAttribs( USHORT nPara, const SfxItemSet& rSet );
    const SfxItemSet&   GetParaAttribs( USHORT nPara ) const;

    void                GetCharAttribs( USHORT nPara, EECharAttribArray& rLst ) const;

    SfxItemSet          GetAttribs( USHORT nPara, USHORT nStart, USHORT nEnd, sal_uInt8 nFlags = 0xFF ) const;
    SfxItemSet          GetAttribs( const ESelection& rSel, BOOL bOnlyHardAttrib = EditEngineAttribs_All );

    BOOL                HasParaAttrib( USHORT nPara, USHORT nWhich ) const;
    const SfxPoolItem&  GetParaAttrib( USHORT nPara, USHORT nWhich );

//STRIP001  Font            GetStandardFont( USHORT nPara );
//STRIP001  SvxFont         GetStandardSvxFont( USHORT nPara );

//STRIP001     void            RemoveAttribs( const ESelection& rSelection, sal_Bool bRemoveParaAttribs, sal_uInt16 nWhich );

//STRIP001  void            ShowParagraph( USHORT nParagraph, BOOL bShow = TRUE );
//STRIP001  BOOL            IsParagraphVisible( USHORT nParagraph );

    SfxUndoManager& GetUndoManager();
    void            UndoActionStart( USHORT nId );
    void            UndoActionEnd( USHORT nId );
    BOOL            IsInUndo();

    void            EnableUndo( BOOL bEnable );
    BOOL            IsUndoEnabled();

    void            ClearModifyFlag();
    void            SetModified();
    BOOL            IsModified() const;

    void            SetModifyHdl( const Link& rLink );
    Link            GetModifyHdl() const;

//STRIP001  BOOL            IsInSelectionMode() const;
//STRIP001  void            StopSelectionMode();

    void            StripPortions();
    void            GetPortions( USHORT nPara, SvUShorts& rList );

//STRIP001  long            GetFirstLineStartX( USHORT nParagraph );
    Point           GetDocPosTopLeft( USHORT nParagraph );
    Point           GetDocPos( const Point& rPaperPos ) const;
    BOOL            IsTextPos( const Point& rPaperPos, USHORT nBorder = 0 );

    // StartDocPos entspr. VisArea.TopLeft().
//STRIP001  void            Draw( OutputDevice* pOutDev, const Rectangle& rOutRect );
//STRIP001  void            Draw( OutputDevice* pOutDev, const Rectangle& rOutRect, const Point& rStartDocPos );
//STRIP001  void            Draw( OutputDevice* pOutDev, const Rectangle& rOutRect, const Point& rStartDocPos, BOOL bClip );
//STRIP001  void            Draw( OutputDevice* pOutDev, const Point& rStartPos, short nOrientation = 0 );

//  ULONG: Fehlercode des Streams.
    ULONG           Read( SvStream& rInput, EETextFormat, SvKeyValueIterator* pHTTPHeaderAttrs = NULL );
    ULONG           Write( SvStream& rOutput, EETextFormat );

    void            SetStatusEventHdl( const Link& rLink );
//STRIP001  Link            GetStatusEventHdl() const;

    void            SetNotifyHdl( const Link& rLink );
    Link            GetNotifyHdl() const;

//STRIP001  void            SetImportHdl( const Link& rLink );
//STRIP001  Link            GetImportHdl() const;

    // Flat-Mode: Keine Zeichenformatierung auswerten => Fuer Outliner
    BOOL            IsFlatMode() const;
//STRIP001  void            SetFlatMode( BOOL bFlat );

    void            SetControlWord( ULONG nWord );
    ULONG           GetControlWord() const;

    void            QuickSetAttribs( const SfxItemSet& rSet, const ESelection& rSel );
    void            QuickRemoveCharAttribs( USHORT nPara, USHORT nWhich = 0 );
//STRIP001  void            QuickMarkInvalid( const ESelection& rSel );
    void            QuickFormatDoc( BOOL bFull = FALSE );
    void            QuickInsertField( const SvxFieldItem& rFld, const ESelection& rSel );
    void            QuickInsertLineBreak( const ESelection& rSel );
    void            QuickInsertText( const String& rText, const ESelection& rSel );
    void            QuickDelete( const ESelection& rSel );
//STRIP001  void            QuickMarkToBeRepainted( USHORT nPara );

    void            SetGlobalCharStretching( USHORT nX = 100, USHORT nY = 100 );
//STRIP001  void            GetGlobalCharStretching( USHORT& rX, USHORT& rY );
    void            DoStretchChars( USHORT nX, USHORT nY );

    void            SetEditTextObjectPool( SfxItemPool* pPool );
    SfxItemPool*    GetEditTextObjectPool() const;

    void                SetStyleSheetPool( SfxStyleSheetPool* pSPool );
    SfxStyleSheetPool*  GetStyleSheetPool();

    void                SetStyleSheet( USHORT nPara, SfxStyleSheet* pStyle );
    SfxStyleSheet*      GetStyleSheet( USHORT nPara ) const;

    void            SetWordDelimiters( const String& rDelimiters );
    String          GetWordDelimiters() const;

//STRIP001  void            SetGroupChars( const String& rChars );
//STRIP001  String          GetGroupChars() const;

//STRIP001  void            EnablePasteSpecial( BOOL bEnable );
//STRIP001  BOOL            IsPasteSpecialEnabled() const;

//STRIP001  void            EnableIdleFormatter( BOOL bEnable );
//STRIP001  BOOL            IsIdleFormatterEnabled() const;

    void            EraseVirtualDevice();

    void            SetSpeller( ::com::sun::star::uno::Reference<
                            ::com::sun::star::linguistic2::XSpellChecker1 > &xSpeller );
//STRIP001  ::com::sun::star::uno::Reference<
//STRIP001      ::com::sun::star::linguistic2::XSpellChecker1 >
//STRIP001                  GetSpeller();
//STRIP001  ::com::sun::star::uno::Reference<
//STRIP001      ::com::sun::star::linguistic2::XHyphenator >
//STRIP001                  GetHyphenator() const;
    void            SetHyphenator( ::com::sun::star::uno::Reference<
                            ::com::sun::star::linguistic2::XHyphenator >& xHyph );

    void            SetForbiddenCharsTable( vos::ORef<SvxForbiddenCharactersTable> xForbiddenChars );
//STRIP001  vos::ORef<SvxForbiddenCharactersTable>  GetForbiddenCharsTable() const;

    void            SetDefaultLanguage( LanguageType eLang );
//STRIP001  LanguageType    GetDefaultLanguage() const;

    BOOL            HasOnlineSpellErrors() const;
    void            CompleteOnlineSpelling();

//STRIP001  void            SetBigTextObjectStart( USHORT nStartAtPortionCount );
//STRIP001  USHORT          GetBigTextObjectStart() const;
    BOOL            ShouldCreateBigTextObject() const;

    // Zum schnellen Vorab-Pruefen ohne View:
//STRIP001  EESpellState    HasSpellErrors( LanguageType eLang );
//STRIP001  EESpellState    HasSpellErrors();
//STRIP001  BOOL            HasText( const SvxSearchItem& rSearchItem );

    BOOL            UpdateFields();
//STRIP001  void            RemoveFields( BOOL bKeepFieldText, TypeId aType = NULL );

    USHORT          GetFieldCount( USHORT nPara ) const;
    EFieldInfo      GetFieldInfo( USHORT nPara, USHORT nField ) const;

//STRIP001     BOOL            IsRightToLeft( USHORT nPara ) const;

    ::com::sun::star::uno::Reference< ::com::sun::star::datatransfer::XTransferable >
                    CreateTransferable( const ESelection& rSelection ) const;

    // MT: Can't create new virtual functions like for ParagraphInserted/Deleted, musst be compatible in SRC638, change later...
    void            SetBeginMovingParagraphsHdl( const Link& rLink );
    void            SetEndMovingParagraphsHdl( const Link& rLink );
    void            SetBeginPasteOrDropHdl( const Link& rLink );
    void            SetEndPasteOrDropHdl( const Link& rLink );

    virtual void    PaintingFirstLine( USHORT nPara, const Point& rStartPos, long nBaseLineY, const Point& rOrigin, short nOrientation, OutputDevice* pOutDev );
    virtual void    ParagraphInserted( USHORT nNewParagraph );
    virtual void    ParagraphDeleted( USHORT nDeletedParagraph );
    virtual void    ParaAttribsChanged( USHORT nParagraph );
//STRIP001  virtual void    StyleSheetChanged( SfxStyleSheet* pStyle );
    virtual void    ParagraphHeightChanged( USHORT nPara );

    // #101498#
    virtual void    DrawingText( const Point& rStartPos, const String& rText, USHORT nTextStart, USHORT nTextLen, const long* pDXArray, const SvxFont& rFont, USHORT nPara, xub_StrLen nIndex, BYTE nRightToLeft);

    virtual String  GetUndoComment( USHORT nUndoId ) const;
    virtual BOOL    FormattingParagraph( USHORT nPara );
//STRIP001  virtual BOOL    SpellNextDocument();
//STRIP001  virtual void    FieldClicked( const SvxFieldItem& rField, USHORT nPara, xub_StrLen nPos );
//STRIP001  virtual void    FieldSelected( const SvxFieldItem& rField, USHORT nPara, xub_StrLen nPos );
    virtual String  CalcFieldValue( const SvxFieldItem& rField, USHORT nPara, xub_StrLen nPos, Color*& rTxtColor, Color*& rFldColor );
    virtual Rectangle GetBulletArea( USHORT nPara );

    static void     SetGetAutoCorrectHdl( const Link& rHdl );
    static SfxItemPool* CreatePool( BOOL bLoadRefCounts = TRUE );
//STRIP001  static ULONG    RegisterClipboardFormatName();
//STRIP001  static BOOL     DoesKeyChangeText( const KeyEvent& rKeyEvent );
//STRIP001  static BOOL     DoesKeyMoveCursor( const KeyEvent& rKeyEvent );
    static BOOL     IsSimpleCharInput( const KeyEvent& rKeyEvent );
//STRIP001  static USHORT   GetAvailableSearchOptions();
//STRIP001  static void     SetFontInfoInItemSet( SfxItemSet& rItemSet, const Font& rFont );
//STRIP001  static void     SetFontInfoInItemSet( SfxItemSet& rItemSet, const SvxFont& rFont );
//STRIP001  static Font     CreateFontFromItemSet( const SfxItemSet& rItemSet );
    static Font     CreateFontFromItemSet( const SfxItemSet& rItemSet, USHORT nScriptType );
    static SvxFont  CreateSvxFontFromItemSet( const SfxItemSet& rItemSet );
    static void     ImportBulletItem( SvxNumBulletItem& rNumBullet, USHORT nLevel, const SvxBulletItem* pOldBullet, const SvxLRSpaceItem* pOldLRSpace );
    static BOOL     IsPrintable( sal_Unicode c ) { return ( ( c >= 32 ) && ( c != 127 ) ); }
//STRIP001     static BOOL     HasValidData( ::com::sun::star::uno::Reference< ::com::sun::star::datatransfer::XTransferable >& rTransferable );
};

#endif // _MyEDITENG_HXX
