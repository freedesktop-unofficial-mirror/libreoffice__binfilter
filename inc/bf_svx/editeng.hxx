/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file incorporates work covered by the following license notice:
 *
 *   Licensed to the Apache Software Foundation (ASF) under one or more
 *   contributor license agreements. See the NOTICE file distributed
 *   with this work for additional information regarding copyright
 *   ownership. The ASF licenses this file to you under the Apache
 *   License, Version 2.0 (the "License"); you may not use this file
 *   except in compliance with the License. You may obtain a copy of
 *   the License at http://www.apache.org/licenses/LICENSE-2.0 .
 */


// MyEDITENG, wegen exportiertem EditEng
#ifndef _MyEDITENG_HXX
#define _MyEDITENG_HXX

#include <bf_svtools/bf_solar.h>

class OutputDevice;
class String;
class MapMode;
class Color;
class Font;
class KeyEvent;
class PolyPolygon;
class Size;
class Point;
class Rectangle;
class SvStream;
class Link;
class OutputDevice;
namespace binfilter {
class SvKeyValueIterator;
class SvUShorts;
class SfxStyleSheetPool;
class SfxUndoManager;
class SfxItemPool;
class SfxStyleSheet;
class SfxUndoAction;
class SfxPoolItem;
class ImpEditEngine;
class EditView;
class EditUndo;
class SvxFont;
class SvxFieldItem;
class SvxCharSetColorItem;
class XPolyPolygon;
class SvxNumBulletItem;
class SvxBulletItem;
class SvxLRSpaceItem;
class SvxForbiddenCharactersTable;
}//end of namespace binfilter
#include <rtl/ref.hxx>

#include <com/sun/star/uno/Reference.h>

namespace com { namespace sun { namespace star {
  namespace linguistic2 {
    class XSpellChecker1;
    class XHyphenator;
}
  namespace datatransfer {
    class XTransferable;
}
}}}

#include <rsc/rscsfx.hxx>
#include <bf_svx/editdata.hxx>
#include <i18npool/lang.h>

#include <tools/rtti.hxx>   // wegen typedef TypeId
namespace binfilter {
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
                    EditEngine( SfxItemPool* pItemPool );
    virtual         ~EditEngine();

    const SfxItemSet&   GetEmptyItemSet();

    void            SetDefTab( USHORT nDefTab );

    void            SetRefDevice( OutputDevice* pRefDef );
    OutputDevice*   GetRefDevice() const;

    void            SetRefMapMode( const MapMode& rMapMode );
    MapMode         GetRefMapMode();

    void            SetUpdateMode( BOOL bUpdate );
    BOOL            GetUpdateMode() const;

    void            SetBackgroundColor( const Color& rColor );
    Color           GetAutoColor() const;
    void            EnableAutoColor( BOOL b );
    BOOL            IsForceAutoColor() const;

    EditView*       RemoveView( EditView* pEditView );

    void            SetPaperSize( const Size& rSize );
    const Size&     GetPaperSize() const;

    void            SetVertical( BOOL bVertical );
    BOOL            IsVertical() const;


    USHORT          GetScriptType( const ESelection& rSelection ) const;
    LanguageType    GetLanguage( USHORT nPara, USHORT nPos ) const;


    void            SetAsianCompressionMode( USHORT nCompression );

    void            SetKernAsianPunctuation( BOOL bEnabled );

    void                ClearPolygon();

    void            SetMinAutoPaperSize( const Size& rSz );

    void            SetMaxAutoPaperSize( const Size& rSz );

    String          GetText( LineEnd eEnd = LINEEND_LF ) const;
    String          GetText( const ESelection& rSelection, const LineEnd eEnd = LINEEND_LF ) const;
    sal_uInt32      GetTextHeight() const;
    sal_uInt32      CalcTextWidth();

    String          GetText( USHORT nParagraph ) const;
    xub_StrLen          GetTextLen( USHORT nParagraph ) const;

    USHORT          GetParagraphCount() const;

    USHORT          GetLineCount( USHORT nParagraph ) const;
    USHORT          GetFirstLineOffset( USHORT nParagraph );
    ParagraphInfos  GetParagraphInfos( USHORT nPara );
    USHORT          FindParagraph( long nDocPosY );
    EPosition       FindDocPosition( const Point& rDocPos ) const;
    Rectangle       GetCharacterBounds( const EPosition& rPos ) const;


    ESelection      GetWord( const ESelection& rSelection, USHORT nWordType ) const;

    void            Clear();
    void            SetText( const String& rStr );

    EditTextObject* CreateTextObject();
    EditTextObject* CreateTextObject( USHORT nPara, USHORT nParas = 1 );
    void            SetText( const EditTextObject& rTextObject );

    void            InsertParagraph( USHORT nPara, const String& rText);

    void            SetText( USHORT nPara, const String& rText);

    void                SetParaAttribs( USHORT nPara, const SfxItemSet& rSet );
    const SfxItemSet&   GetParaAttribs( USHORT nPara ) const;

    SfxItemSet          GetAttribs( USHORT nPara, USHORT nStart, USHORT nEnd, sal_uInt8 nFlags = 0xFF ) const;
    SfxItemSet          GetAttribs( const ESelection& rSel, BOOL bOnlyHardAttrib = EditEngineAttribs_All );

    BOOL                HasParaAttrib( USHORT nPara, USHORT nWhich ) const;
    const SfxPoolItem&  GetParaAttrib( USHORT nPara, USHORT nWhich );


    SfxUndoManager& GetUndoManager();
    void            UndoActionStart( USHORT nId );
    void            UndoActionEnd( USHORT nId );
    BOOL            IsInUndo();

    void            EnableUndo( BOOL bEnable );
    BOOL            IsUndoEnabled();

    void            SetModified();

    Link            GetModifyHdl() const;


    void            StripPortions();
    void            GetPortions( USHORT nPara, SvUShorts& rList );

    Point           GetDocPosTopLeft( USHORT nParagraph );
    Point           GetDocPos( const Point& rPaperPos ) const;
    BOOL            IsTextPos( const Point& rPaperPos, USHORT nBorder = 0 );

    // StartDocPos entspr. VisArea.TopLeft().

    void            SetStatusEventHdl( const Link& rLink );

    void            SetNotifyHdl( const Link& rLink );


    // Flat-Mode: Keine Zeichenformatierung auswerten => Fuer Outliner
    BOOL            IsFlatMode() const;

    void            SetControlWord( sal_uInt32 nWord );
    sal_uInt32      GetControlWord() const;

    void            QuickSetAttribs( const SfxItemSet& rSet, const ESelection& rSel );
    void            QuickRemoveCharAttribs( USHORT nPara, USHORT nWhich = 0 );
    void            QuickFormatDoc( BOOL bFull = FALSE );
    void            QuickInsertField( const SvxFieldItem& rFld, const ESelection& rSel );
    void            QuickInsertLineBreak( const ESelection& rSel );
    void            QuickInsertText( const String& rText, const ESelection& rSel );
    void            QuickDelete( const ESelection& rSel );

    void            SetGlobalCharStretching( USHORT nX = 100, USHORT nY = 100 );

    void            SetEditTextObjectPool( SfxItemPool* pPool );
    SfxItemPool*    GetEditTextObjectPool() const;

    void                SetStyleSheetPool( SfxStyleSheetPool* pSPool );
    SfxStyleSheetPool*  GetStyleSheetPool();

    void                SetStyleSheet( USHORT nPara, SfxStyleSheet* pStyle );
    SfxStyleSheet*      GetStyleSheet( USHORT nPara ) const;

    void            SetWordDelimiters( const String& rDelimiters );
    String          GetWordDelimiters() const;




    void            EraseVirtualDevice();

    void            SetSpeller( ::com::sun::star::uno::Reference<
                            ::com::sun::star::linguistic2::XSpellChecker1 > &xSpeller );
    void            SetHyphenator( ::com::sun::star::uno::Reference<
                            ::com::sun::star::linguistic2::XHyphenator >& xHyph );

    void            SetForbiddenCharsTable( rtl::Reference<SvxForbiddenCharactersTable> xForbiddenChars );

    void            SetDefaultLanguage( LanguageType eLang );

    BOOL            HasOnlineSpellErrors() const;
    void            CompleteOnlineSpelling();

    BOOL            ShouldCreateBigTextObject() const;

    // Zum schnellen Vorab-Pruefen ohne View:

    BOOL            UpdateFields();

    USHORT          GetFieldCount( USHORT nPara ) const;
    EFieldInfo      GetFieldInfo( USHORT nPara, USHORT nField ) const;


    ::com::sun::star::uno::Reference< ::com::sun::star::datatransfer::XTransferable >
                    CreateTransferable( const ESelection& rSelection ) const;

    // MT: Can't create new virtual functions like for ParagraphInserted/Deleted, musst be compatible in SRC638, change later...
    void            SetBeginMovingParagraphsHdl( const Link& rLink );
    void            SetEndMovingParagraphsHdl( const Link& rLink );
    void            SetBeginPasteOrDropHdl( const Link& rLink );
    void            SetEndPasteOrDropHdl( const Link& rLink );

    virtual void    ParaAttribsChanged( USHORT ) {} // DBG_BF_ASSERT
    virtual void    ParagraphHeightChanged( USHORT ) {} // DBG_BF_ASSERT

    virtual void    DrawingText( const Point&, const String&, USHORT, USHORT, const sal_Int32*, const SvxFont&, USHORT, xub_StrLen, BYTE) {} // DBG_BF_ASSERT

    virtual String  GetUndoComment( USHORT nUndoId ) const;
    virtual String  CalcFieldValue( const SvxFieldItem& rField, USHORT nPara, xub_StrLen nPos, Color*& rTxtColor, Color*& rFldColor );
    virtual Rectangle GetBulletArea( USHORT nPara );

    static SfxItemPool* CreatePool( BOOL bLoadRefCounts = TRUE );
    static Font     CreateFontFromItemSet( const SfxItemSet& rItemSet, USHORT nScriptType );
    static SvxFont  CreateSvxFontFromItemSet( const SfxItemSet& rItemSet );
    static void     ImportBulletItem( SvxNumBulletItem& rNumBullet, USHORT nLevel, const SvxBulletItem* pOldBullet, const SvxLRSpaceItem* pOldLRSpace );
    static BOOL     IsPrintable( sal_Unicode c ) { return ( ( c >= 32 ) && ( c != 127 ) ); }
};

}//end of namespace binfilter
#endif // _MyEDITENG_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
