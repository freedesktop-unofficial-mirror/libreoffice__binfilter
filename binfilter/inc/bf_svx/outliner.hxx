/*************************************************************************
 *
 *  $RCSfile: outliner.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 08:28:22 $
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

#ifndef _OUTLINER_HXX
#define _OUTLINER_HXX

#ifndef _GEN_HXX //autogen
#include <tools/gen.hxx>
#endif
#ifndef _STRING_HXX //autogen
#include <tools/string.hxx>
#endif
#ifndef _TOOLS_DEBUG_HXX //autogen
#include <tools/debug.hxx>
#endif
#ifndef _EDITDATA_HXX //autogen
#include <bf_svx/editdata.hxx>
#endif
#ifndef _LANG_HXX //autogen
#include <tools/lang.hxx>
#endif
#ifndef _SV_COLOR_HXX //autogen
#include <vcl/color.hxx>
#endif
#ifndef _SV_GRAPH_HXX
#include <vcl/graph.hxx>
#endif
#ifndef _LIST_HXX //autogen
#include <tools/list.hxx>
#endif
#ifndef _LINK_HXX //autogen
#include <tools/link.hxx>
#endif
#ifndef _RSCSFX_HXX //autogen
#include <rsc/rscsfx.hxx>
#endif

#include <tools/rtti.hxx>   // wegen typedef TypeId
#ifndef _COM_SUN_STAR_UNO_REFERENCE_H_
#include <com/sun/star/uno/Reference.h>
#endif

#include <vos/ref.hxx>
#include <bf_svx/svxfont.hxx>

namespace com { namespace sun { namespace star { namespace linguistic2 {
    class XSpellChecker1;
    class XHyphenator;
}}}}
class SvStream;
class Window;
class KeyEvent;
class MouseEvent;
class Pointer;
class MapMode;
class OutputDevice;
class PolyPolygon;
class SfxStyleSheetPool;
class SfxStyleSheet;
class SfxItemPool;
class SfxItemSet;
class SfxUndoManager;
class SvKeyValueIterator;
namespace binfilter {

class OutlinerEditEng;
class Outliner;
class EditView;
class EditUndo;
class ParagraphList;
class OutlinerParaObject;
class SvxBulletItem;
class SvxFont;
class SvxSearchItem;
class SvxFieldItem;
class OLUndoRemove;
class XPolyPolygon;
class CommandEvent;
class SvxNumBulletItem;
class SvxNumberFormat;
class SvxLRSpaceItem;
class EditEngine;
class SvxForbiddenCharactersTable;

//STRIP008 #ifndef _COM_SUN_STAR_UNO_REFERENCE_H_
//STRIP008 #include <com/sun/star/uno/Reference.h>
//STRIP008 #endif
//STRIP008
//STRIP008 #include <vos/ref.hxx>
//STRIP008 #include <bf_svx/svxfont.hxx>
//STRIP008
//STRIP008 namespace com { namespace sun { namespace star { namespace linguistic2 {
//STRIP008  class XSpellChecker1;
//STRIP008  class XHyphenator;
//STRIP008 }}}}

// nur interner Gebrauch!
#define PARAFLAG_DROPTARGET         0x1000
#define PARAFLAG_DROPTARGET_EMPTY   0x2000
#define PARAFLAG_HOLDDEPTH          0x4000
#define PARAFLAG_SETBULLETTEXT      0x8000

// Undo-Action-Ids
#define OLUNDO_DEPTH            EDITUNDO_USER
// #define OLUNDO_HEIGHT           EDITUNDO_USER+1
#define OLUNDO_EXPAND           EDITUNDO_USER+2
#define OLUNDO_COLLAPSE         EDITUNDO_USER+3
// #define OLUNDO_REMOVE           EDITUNDO_USER+4
#define OLUNDO_ATTR             EDITUNDO_USER+5
#define OLUNDO_INSERT           EDITUNDO_USER+6
// #define OLUNDO_MOVEPARAGRAPHS    EDITUNDO_USER+7
#define OLUNDO_CHECKPARA        EDITUNDO_USER+8

// MT 07/00: Only for internal use, oder some kind like hPara for the few
// functions where you need it outside ( eg. moving paragraphs... )

class Paragraph
{
private:
    friend class Outliner;
    friend class ParagraphList;
    friend class OutlinerView;
    friend class OutlinerParaObject;
    friend class OutlinerEditEng;
    friend class OLUndoDepth;
    friend class OutlinerUndoCheckPara;

    Paragraph& operator=(const Paragraph& rPara );

    USHORT              nFlags;
    USHORT              nDepth;
    XubString           aBulText;
    Size                aBulSize;
    BOOL                bVisible;

    BOOL                IsVisible() const { return bVisible; }
    void                SetText( const XubString& rText ) { aBulText = rText; aBulSize.Width() = -1; }
    void                Invalidate() { aBulSize.Width() = -1; }
    void                SetDepth( USHORT nNewDepth ) { nDepth = nNewDepth; aBulSize.Width() = -1; }
    const XubString&    GetText() const { return aBulText; }

                        Paragraph( USHORT nDepth );
//STRIP001                      Paragraph( const Paragraph& );
                        ~Paragraph();

    USHORT              GetDepth() const { return nDepth; }
};

struct ParaRange
{
    USHORT  nStartPara;
    USHORT  nEndPara;

            ParaRange( USHORT nS, USHORT nE ) { nStartPara = nS, nEndPara = nE; }

    void    Adjust();
    USHORT  Len() const { return 1 + ( ( nEndPara > nStartPara ) ? (nEndPara-nStartPara) : (nStartPara-nEndPara) ); }
};

inline void ParaRange::Adjust()
{
    if ( nStartPara > nEndPara )
    {
        USHORT nTmp = nStartPara;
        nStartPara = nEndPara;
        nEndPara = nTmp;
    }
}

#define OL_ROOTPARENT (Paragraph*)NULL

class OutlinerView
{
    friend class Outliner;

private:

    Outliner*   pOwner;
    EditView*   pEditView;

    // Drag & Drop
    BOOL        bBeginDragAtMove_OLDMEMBER;
    BOOL        bInDragMode;
    Point       aDDStartPosRef;
    Point       aDDStartPosPix;
    ULONG       nDDStartPara;
    ULONG       nDDStartParaVisChildCount;
    ULONG       nDDCurPara;
    USHORT      nDDStartDepth;
    USHORT      nDDCurDepth;
    USHORT      nDDMaxDepth;
    BOOL        bDDChangingDepth;
    BOOL        bDDCursorVisible;
    long*       pHorTabArrDoc;
    long        nDDScrollLRBorderWidthWin;  // Left Right
    long        nDDScrollTBBorderWidthWin;  // Top Bottom
    long        nDDScrollLROffs;
    long        nDDScrollTDOffs;

    void*       pDummy;
    ULONG       nDummy;

    enum MouseTarget {
        MouseText = 0,
        MouseBullet = 1,
        MouseHypertext = 2,    //            ausserhalb OutputArea
        MouseOutside = 3,    //            ausserhalb OutputArea
        MouseDontKnow = 4
    };
    MouseTarget OLD_ePrevMouseTarget;

#ifdef _OUTLINER_CXX

//STRIP001  void        ImplExpandOrCollaps( USHORT nStartPara, USHORT nEndPara, BOOL bExpand );

//STRIP001  ULONG       ImpCheckMousePos( const Point& rPosPixel, MouseTarget& reTarget);
//STRIP001  void        ImpToggleExpand( Paragraph* pParentPara );
//STRIP001  ParaRange   ImpGetSelectedParagraphs( BOOL bIncludeHiddenChilds );
//STRIP001  void        ImpHideDDCursor();
//STRIP001  void        ImpShowDDCursor();
//STRIP001  void        ImpPaintDDCursor();

//STRIP001  void        ImpDragScroll( const Point& rPosPix );
//STRIP001  void        ImpScrollLeft();
//STRIP001  void        ImpScrollRight();
//STRIP001  void        ImpScrollUp();
//STRIP001  void        ImpScrollDown();

//STRIP001  ULONG       ImpGetInsertionPara( const Point& rPosPixel );
//STRIP001  Point       ImpGetDocPos( const Point& rPosPixel );
//STRIP001  Pointer     ImpGetMousePointer( MouseTarget eTarget );
//STRIP001  USHORT      ImpInitPaste( ULONG& rStart );
//STRIP001  void        ImpPasted( ULONG nStart, ULONG nPrevParaCount, USHORT nSize);
//STRIP001  USHORT      ImpCalcSelectedPages( BOOL bIncludeFirstSelected );
//STRIP001  BOOL        ImpIsIndentingPages();

#endif

public:
                OutlinerView( Outliner* pOut, Window* pWindow );
    virtual     ~OutlinerView();

    EditView&   GetEditView() const { return *pEditView; }

//STRIP001  void        Scroll( long nHorzScroll, long nVertScroll );

//STRIP001  void        Paint( const Rectangle& rRect );
//STRIP001  BOOL        PostKeyEvent( const KeyEvent& rKEvt );
//STRIP001  BOOL        MouseButtonDown( const MouseEvent& );
//STRIP001  BOOL        MouseButtonUp( const MouseEvent& );
//STRIP001  BOOL        MouseMove( const MouseEvent& );

//STRIP001  void        ShowCursor( BOOL bGotoCursor = TRUE );
//STRIP001  void        HideCursor();

//STRIP001  void        SetOutliner( Outliner* pOutliner );
    Outliner*   GetOutliner() const { return pOwner; }

//STRIP001  void        SetWindow( Window* pWindow );
    Window*     GetWindow() const;

//STRIP001  void        SetReadOnly( BOOL bReadOnly );
//STRIP001  BOOL        IsReadOnly() const;

//STRIP001  void        SetOutputArea( const Rectangle& rRect );
    Rectangle   GetOutputArea() const;

    Rectangle   GetVisArea() const;

//STRIP001  List*       CreateSelectionList();

    // gibt Anzahl selektierter Absaetze zurueck
    // MT 07/00: Who needs this?
//STRIP001  ULONG       Select( Paragraph* pParagraph,
//STRIP001                  BOOL bSelect=TRUE,
//STRIP001                  BOOL bWChilds=TRUE);

    String      GetSelected() const;
//STRIP001  void        SelectRange( ULONG nFirst, USHORT nCount );
//STRIP001  void        SetAttribs( const SfxItemSet& );
//STRIP001  void        Indent( short nDiff );
//STRIP001  void        AdjustDepth( short nDX );   // Spaeter gegeb Indent ersetzen!

//STRIP001  BOOL        AdjustHeight( long nDY );
//STRIP001  void        AdjustDepth( Paragraph* pPara, short nDX,
//STRIP001                  BOOL bWithChilds = FALSE );
//STRIP001  void        AdjustHeight( Paragraph* pPara, long nDY,
//STRIP001                  BOOL bWithChilds=FALSE );

//STRIP001  ULONG       Read( SvStream& rInput, EETextFormat eFormat, BOOL bSelect = FALSE, SvKeyValueIterator* pHTTPHeaderAttrs = NULL );
//STRIP001  ULONG       Write( SvStream& rOutput, EETextFormat eFormat );

//STRIP001  void        InsertText( const String& rNew, BOOL bSelect = FALSE );
//STRIP001  void        InsertText( const OutlinerParaObject& rParaObj );
//STRIP001  void        Expand();
//STRIP001  void        Collapse();
//STRIP001  void        Expand( Paragraph* );
//STRIP001  void        Collapse( Paragraph* );
//STRIP001  void        ExpandAll();
//STRIP001  void        CollapseAll();

//STRIP001  void        SetBackgroundColor( const Color& rColor );
//STRIP001  Color       GetBackgroundColor();

//STRIP001  SfxItemSet  GetAttribs();

    void        Cut();
    void        Copy();
    void        Paste();
//STRIP001  void        PasteSpecial();
//STRIP001  void        EnablePaste( BOOL bEnable );

//STRIP001  void        Undo();
//STRIP001  void        Redo();

    void            SetStyleSheet( SfxStyleSheet* );
//STRIP001  SfxStyleSheet*  GetStyleSheet() const;

//STRIP001  void        SetControlWord( ULONG nWord );
//STRIP001  ULONG       GetControlWord() const;

//STRIP001  void            SetAnchorMode( EVAnchorMode eMode );
//STRIP001  EVAnchorMode    GetAnchorMode() const;

//STRIP001  Pointer     GetPointer( const Point& rPosPixel );
//STRIP001  void        Command( const CommandEvent& rCEvt );
//STRIP001  void        RemoveCharAttribs( ULONG nPara, USHORT nWhich = 0 );

//STRIP001  void        CompleteAutoCorrect();

    // Depricated
//STRIP001  EESpellState    StartSpeller( LanguageType eLang,BOOL bMultipleDoc = FALSE );
//STRIP001  EESpellState    StartThesaurus( LanguageType eLang );

//STRIP001  EESpellState    StartSpeller( BOOL bMultipleDoc = FALSE );
//STRIP001  EESpellState    StartThesaurus();
//STRIP001  USHORT          StartSearchAndReplace( const SvxSearchItem& rSearchItem );

//STRIP001  void            TransliterateText( sal_Int32 nTransliterationMode );

    ESelection  GetSelection();

//STRIP001  USHORT      GetSelectedScriptType() const;

//STRIP001  void        SetVisArea( const Rectangle& rRec );
    void        SetSelection( const ESelection& );

//STRIP001  void        RemoveAttribs( BOOL bRemoveParaAttribs = FALSE, USHORT nWhich = 0 );
//STRIP001  BOOL        HasSelection() const;

//STRIP001  void                InsertField( const SvxFieldItem& rFld );
//STRIP001  const SvxFieldItem* GetFieldUnderMousePointer() const;
//STRIP001  const SvxFieldItem* GetFieldUnderMousePointer( USHORT& nPara, xub_StrLen& nPos ) const;
//STRIP001  const SvxFieldItem* GetFieldAtSelection() const;

//STRIP001  void        ShowBullets( BOOL bShow, BOOL bAffectLevel0 );

//STRIP001  BOOL        IsCursorAtWrongSpelledWord( BOOL bMarkIfWrong = FALSE );
//STRIP001  BOOL        IsWrongSpelledWordAtPos( const Point& rPosPixel, BOOL bMarkIfWrong = FALSE );
//STRIP001  void        SpellIgnoreWord();
//STRIP001  void        ExecuteSpellPopup( const Point& rPosPixel, Link* pCallBack = 0 );

//STRIP001  void        SetInvalidateMore( USHORT nPixel );
//STRIP001  USHORT      GetInvalidateMore() const;
};

#if _SOLAR__PRIVATE
DECLARE_LIST(ViewList,OutlinerView*)
#else
typedef List ViewList;
#endif

class DrawPortionInfo
{
public:
    const Point&    rStartPos;

    const String&   rText;
    USHORT          nTextStart;
    USHORT          nTextLen;

    USHORT          nPara;
    xub_StrLen      nIndex;

    const SvxFont&  rFont;

    const long*     pDXArray;

    // #101498# BiDi level needs to be transported, too.
    BYTE            mnBiDiLevel;

    BYTE GetBiDiLevel() const { return mnBiDiLevel; }
    sal_Bool IsRTL() const;

    DrawPortionInfo( const Point& rPos, const String& rTxt, USHORT nTxtStart, USHORT nTxtLen,
        const SvxFont& rFnt, USHORT nPar, xub_StrLen nIdx, const long* pDXArr, BYTE nBiDiLevel)
        :   rStartPos(rPos), rText(rTxt), rFont(rFnt), nPara(nPar), nIndex(nIdx),
            pDXArray(pDXArr), mnBiDiLevel(nBiDiLevel)
        {
            nTextStart = nTxtStart;
            nTextLen = nTxtLen;
        }
};

class EditFieldInfo
{
private:
    Outliner*           pOutliner;
    const SvxFieldItem& rFldItem;

    Color*              pTxtColor;
    Color*              pFldColor;

    String              aRepresentation;

    USHORT              nPara;
    xub_StrLen          nPos;
    BOOL                bSimpleClick;

                        EditFieldInfo();
                        EditFieldInfo( const EditFieldInfo& );

public:
                    EditFieldInfo( Outliner* pOutl, const SvxFieldItem& rFItem, USHORT nPa, xub_StrLen nPo )
                        : rFldItem( rFItem )
                    {
                        pOutliner = pOutl;
                        nPara = nPa; nPos = nPo;
                        pTxtColor = 0; pFldColor = 0; bSimpleClick = FALSE;
                    }
                    ~EditFieldInfo()
                    {
                        delete pTxtColor;
                        delete pFldColor;
                    }

    Outliner*       GetOutliner() const { return pOutliner; }

    const SvxFieldItem& GetField() const { return rFldItem; }

    Color*          GetTxtColor() const { return pTxtColor; }
    void            SetTxtColor( const Color& rColor )
                        { delete pTxtColor; pTxtColor = new Color( rColor ); }

    Color*          GetFldColor() const { return pFldColor; }
    void            SetFldColor( const Color& rColor )
                        { delete pFldColor; pFldColor = new Color( rColor ); }
    void            ClearFldColor()
                        { delete pFldColor; pFldColor = 0; }

    USHORT          GetPara() const { return nPara; }
    xub_StrLen          GetPos() const { return nPos; }

    BOOL            IsSimpleClick() const { return bSimpleClick; }
    void            SetSimpleClick( BOOL bSimple ) { bSimpleClick = bSimple; }

    const String&       GetRepresentation() const                { return aRepresentation; }
    String&             GetRepresentation()                      { return aRepresentation; }
    void                SetRepresentation( const String& rStr )  { aRepresentation = rStr; }
};

struct EBulletInfo
{
    BOOL        bVisible;
    USHORT      nType;          // see SvxNumberType
    String      aText;
    SvxFont     aFont;
    Graphic     aGraphic;
    USHORT      nParagraph;
    Rectangle   aBounds;

    EBulletInfo() : bVisible( FALSE ), nType( 0 ), nParagraph( EE_PARA_NOT_FOUND ) {}
};

#define OUTLINERMODE_DONTKNOW       0x0000
#define OUTLINERMODE_TEXTOBJECT     0x0001
#define OUTLINERMODE_TITLEOBJECT    0x0002
#define OUTLINERMODE_OUTLINEOBJECT  0x0003
#define OUTLINERMODE_OUTLINEVIEW    0x0004

#define OUTLINERMODE_USERMASK       0x00FF

#define OUTLINERMODE_SUBTITLE       (0x0100|OUTLINERMODE_TEXTOBJECT)
#define OUTLINERMODE_NOTE           (0x0200|OUTLINERMODE_TEXTOBJECT)

class Outliner
{
    friend class OutlinerView;
    friend class OutlinerEditEng;
    friend class OutlinerParaObject;
    friend class OLUndoExpand;
    friend class OutlinerUndoChangeDepth;
    friend class OutlinerUndoCheckPara;

    OutlinerEditEng*    pEditEngine;

    ParagraphList*      pParaList;
    ViewList            aViewList;

    Paragraph*          pHdlParagraph;
    Link                aDrawPortionHdl;
    Link                aExpandHdl;
    Link                aParaInsertedHdl;
    Link                aParaRemovingHdl;
    Link                aDepthChangedHdl;
    Link                aWidthArrReqHdl;
    Link                aBeginMovingHdl;
    Link                aEndMovingHdl;
    Link                aIndentingPagesHdl;
    Link                aRemovingPagesHdl;
    Link                aFieldClickedHdl;
    Link                aCalcFieldValueHdl;

    USHORT              nDepthChangedHdlPrevDepth;
    USHORT              nMaxDepth;
    USHORT              nMinDepth;
    USHORT              nFirstPage;

    USHORT              nOutlinerMode;

    BOOL                bIsExpanding; // Nur in Expand/Collaps-Hdl gueltig, mal umstellen
    BOOL                bFirstParaIsEmpty;
    BOOL                bBlockInsCallback;
    BOOL                bStrippingPortions;
    BOOL                bPasting;

    SvxNumberFormat*    pOverwriteLevel0Bullet;

    ULONG               nDummy;

#ifdef _OUTLINER_CXX

    DECL_LINK(              ParaVisibleStateChangedHdl, Paragraph* );
    DECL_LINK(              BeginMovingParagraphsHdl, MoveParagraphsInfo* );
    DECL_LINK(              EndMovingParagraphsHdl, MoveParagraphsInfo* );
    DECL_LINK(              BeginPasteOrDropHdl, PasteOrDropInfos* );
    DECL_LINK(              EndPasteOrDropHdl, PasteOrDropInfos* );
    DECL_LINK(              EditEngineNotifyHdl, EENotify* );
    void                    ImplCheckParagraphs( USHORT nStart, USHORT nEnd );
    BOOL                    ImplHasBullet( USHORT nPara ) const;
    const SvxNumberFormat*  ImplGetBullet( USHORT nPara ) const;
    Size                    ImplGetBulletSize( USHORT nPara );
    void                    ImplCalcBulletText( USHORT nPara, BOOL bRecalcLevel, BOOL bRecalcChilds );
    String                  ImplGetBulletText( USHORT nPara );
    void                    ImplCheckNumBulletItem( USHORT nPara );
    void                    ImplInitDepth( USHORT nPara, USHORT nDepth, BOOL bCreateUndo, BOOL bUndoAction = FALSE );
    void                    ImplSetLevelDependendStyleSheet( USHORT nPara, SfxStyleSheet* pLevelStyle = NULL );

    void                    ImplBlockInsertionCallbacks( BOOL b );

    void                ImplCheckStyleSheet( USHORT nPara, BOOL bReplaceExistingStyle );
    void                ImpRecalcBulletIndent( ULONG nPara );

    const SvxBulletItem& ImpGetBullet( ULONG nPara, USHORT& );
//STRIP001  void        ImpFilterIndents( ULONG nFirstPara, ULONG nLastPara );
    void        ImpConvertOutToEdt( Paragraph* pPara, ULONG nPara );
//STRIP001  BOOL        ImpConvertEdtToOut( Paragraph* pPara, ULONG nPara, EditView* pView = 0 );

//STRIP001  void        ImpTextPasted( ULONG nStartPara, USHORT nCount );
//STRIP001  void        ImpDropped( OutlinerView* pView );
    long        ImpCalcMaxBulletWidth( USHORT nPara, const SvxBulletItem& rBullet );
    Font        ImpCalcBulletFont( USHORT nPara ) const;
    Rectangle   ImpCalcBulletArea( USHORT nPara, BOOL bAdjust, BOOL bReturnPaperPos );
    long        ImpGetTextIndent( ULONG nPara );
//STRIP001  BOOL        ImpCanIndentSelectedPages( OutlinerView* pCurView );
//STRIP001  BOOL        ImpCanDeleteSelectedPages( OutlinerView* pCurView );
//STRIP001  BOOL        ImpCanDeleteSelectedPages( OutlinerView* pCurView, USHORT nFirstPage, USHORT nPages );

    USHORT      ImplGetOutlinerMode() const { return nOutlinerMode & OUTLINERMODE_USERMASK; }
    void        ImplCheckDepth( USHORT& rnDepth ) const;
#endif

protected:
    void            ParagraphInserted( USHORT nParagraph );
    void            ParagraphDeleted( USHORT nParagraph );
    void            ParaAttribsChanged( USHORT nParagraph );
    void            ParagraphHeightChanged( USHORT nParagraph );

//STRIP001  virtual void    StyleSheetChanged( SfxStyleSheet* pStyle );

//STRIP001  void        InvalidateBullet( Paragraph* pPara, ULONG nPara );
    void        PaintBullet( USHORT nPara, const Point& rStartPos,
                    const Point& rOrigin, short nOrientation,
                    OutputDevice* pOutDev );

public:

                    Outliner( SfxItemPool* pPool, USHORT nOutlinerMode );
    virtual         ~Outliner();

    void            Init( USHORT nOutlinerMode );
    USHORT          GetMode() const { return nOutlinerMode; }

    void            SetVertical( BOOL bVertical );
    BOOL            IsVertical() const;

//STRIP001     void                        SetDefaultHorizontalTextDirection( EEHorizontalTextDirection eHTextDir );
//STRIP001     EEHorizontalTextDirection   GetDefaultHorizontalTextDirection() const;

    USHORT          GetScriptType( const ESelection& rSelection ) const;
    LanguageType    GetLanguage( USHORT nPara, USHORT nPos ) const;

    void            SetAsianCompressionMode( USHORT nCompressionMode );
//STRIP001  USHORT          GetAsianCompressionMode() const;

    void            SetKernAsianPunctuation( BOOL bEnabled );
//STRIP001     BOOL            IsKernAsianPunctuation() const;

//STRIP001  ULONG           InsertView( OutlinerView* pView, ULONG nIndex=LIST_APPEND);
//STRIP001  OutlinerView*   RemoveView( OutlinerView* pView );
//STRIP001  OutlinerView*   RemoveView( ULONG nIndex );
//STRIP001  OutlinerView*   GetView( ULONG nIndex ) const;
//STRIP001  ULONG           GetViewCount() const;

    Paragraph*      Insert( const String& rText, ULONG nAbsPos = LIST_APPEND,
                                USHORT nDepth = 0 );
    void            SetText( const OutlinerParaObject& );
//STRIP001  void            AddText( const OutlinerParaObject& );
    void            SetText( const String& rText, Paragraph* pParagraph );
    String          GetText( Paragraph* pPara, ULONG nParaCount=1 ) const;

    OutlinerParaObject* CreateParaObject( USHORT nStartPara = 0, USHORT nParaCount = 0xFFFF ) const;

    const SfxItemSet& GetEmptyItemSet() const;

    void            SetRefMapMode( const MapMode& );
    MapMode         GetRefMapMode() const;

    void            SetBackgroundColor( const Color& rColor );
//STRIP001  Color           GetBackgroundColor() const;

    void            SetMinDepth( USHORT nDepth, BOOL bCheckParas = FALSE );
    USHORT          GetMinDepth() const { return nMinDepth; }

    void            SetMaxDepth( USHORT nDepth, BOOL bCheckParas = FALSE );
    USHORT          GetMaxDepth() const { return nMaxDepth; }

    void            SetUpdateMode( BOOL bUpdate );
    BOOL            GetUpdateMode() const;

    void            Clear();

//STRIP001     void            RemoveAttribs( const ESelection& rSelection, sal_Bool bRemoveParaAttribs, sal_uInt16 nWhich );

    ULONG           GetParagraphCount() const;
    Paragraph*      GetParagraph( ULONG nAbsPos ) const;

    BOOL            HasParent( Paragraph* pParagraph ) const;
//STRIP001  BOOL            HasChilds( Paragraph* pParagraph ) const;
//STRIP001  ULONG           GetChildCount( Paragraph* pParent ) const;
//STRIP001  BOOL            IsExpanded( Paragraph* pPara ) const;
//  Paragraph*      GetParagraph( Paragraph* pParent, ULONG nRelPos ) const;
//STRIP001  Paragraph*      GetParent( Paragraph* pParagraph ) const;
//  ULONG           GetRelPos( Paragraph* pParent, Paragraph* pPara ) const;
    ULONG           GetAbsPos( Paragraph* pPara );

    USHORT          GetDepth( USHORT nPara ) const;
    void            SetDepth( Paragraph* pParagraph, USHORT nNewDepth );

//STRIP001  void            SetVisible( Paragraph* pPara, BOOL bVisible );
    BOOL            IsVisible( Paragraph* pPara ) const { return pPara->IsVisible(); }

    void            EnableUndo( BOOL bEnable );
    BOOL            IsUndoEnabled() const;
    void            UndoActionStart( USHORT nId );
    void            UndoActionEnd( USHORT nId );
//STRIP001  void            InsertUndo( EditUndo* pUndo );
    BOOL            IsInUndo();

//STRIP001  void            ClearModifyFlag();
//STRIP001  BOOL            IsModified() const;

    Paragraph*      GetHdlParagraph() const { return pHdlParagraph; }
    BOOL            IsExpanding() const { return bIsExpanding; }

//STRIP001  virtual void    ExpandHdl();
    void            SetExpandHdl( const Link& rLink ) { aExpandHdl = rLink; }
    Link            GetExpandHdl() const { return aExpandHdl; }

    virtual void    ParagraphInsertedHdl();
    void            SetParaInsertedHdl(const Link& rLink){aParaInsertedHdl=rLink;}
    Link            GetParaInsertedHdl() const { return aParaInsertedHdl; }

    virtual void    ParagraphRemovingHdl();
    void            SetParaRemovingHdl(const Link& rLink){aParaRemovingHdl=rLink;}
    Link            GetParaRemovingHdl() const { return aParaRemovingHdl; }

    virtual void    DepthChangedHdl();
    void            SetDepthChangedHdl(const Link& rLink){aDepthChangedHdl=rLink;}
    Link            GetDepthChangedHdl() const { return aDepthChangedHdl; }
    USHORT          GetPrevDepth() const { return nDepthChangedHdlPrevDepth; }

//STRIP001  virtual long    RemovingPagesHdl( OutlinerView* );
    void            SetRemovingPagesHdl(const Link& rLink){aRemovingPagesHdl=rLink;}
    Link            GetRemovingPagesHdl() const { return aRemovingPagesHdl; }
//STRIP001  virtual long    IndentingPagesHdl( OutlinerView* );
    void            SetIndentingPagesHdl(const Link& rLink){aIndentingPagesHdl=rLink;}
    Link            GetIndentingPagesHdl() const { return aIndentingPagesHdl; }
    // nur gueltig in den beiden oberen Handlern
    USHORT          GetSelPageCount() const { return nDepthChangedHdlPrevDepth; }
    // nur gueltig in den beiden oberen Handlern
    ULONG           GetFirstSelPage() const { return (ULONG)pHdlParagraph; }

    void            SetCalcFieldValueHdl(const Link& rLink ) { aCalcFieldValueHdl= rLink; }
    Link            GetCalcFieldValueHdl() const { return aCalcFieldValueHdl; }

    void            SetFieldClickedHdl(const Link& rLink ) { aFieldClickedHdl= rLink; }
    Link            GetFieldClickedHdl() const { return aFieldClickedHdl; }

    void            SetDrawPortionHdl(const Link& rLink){aDrawPortionHdl=rLink;}
    Link            GetDrawPortionHdl() const { return aDrawPortionHdl; }

    void            SetModifyHdl( const Link& rLink );
    Link            GetModifyHdl() const;

    void            SetNotifyHdl( const Link& rLink );
//STRIP001  Link            GetNotifyHdl() const;

//STRIP001  void            SetStatusEventHdl( const Link& rLink );
    Link            GetStatusEventHdl() const;

//STRIP001  void            Draw( OutputDevice* pOutDev, const Rectangle& rOutRect );
//STRIP001  void            Draw( OutputDevice* pOutDev, const Rectangle& rOutRect, const Point& rStartDocPos );
//STRIP001  void            Draw( OutputDevice* pOutDev, const Point& rStartPos, short nOrientation = 0 );

    const Size&     GetPaperSize() const;
    void            SetPaperSize( const Size& rSize );

    void            SetFirstPageNumber( USHORT n )  { nFirstPage = n; }
    USHORT          GetFirstPageNumber() const      { return nFirstPage; }

//STRIP001  void                SetPolygon( const XPolyPolygon& rPoly );
//STRIP001  void                SetPolygon( const XPolyPolygon& rPoly, const XPolyPolygon* pXorPoly );
    void                ClearPolygon();
//STRIP001  const PolyPolygon*  GetPolygon();

//STRIP001  const Size&     GetMinAutoPaperSize() const;
    void            SetMinAutoPaperSize( const Size& rSz );

//STRIP001  const Size&     GetMaxAutoPaperSize() const;
    void            SetMaxAutoPaperSize( const Size& rSz );

    void            SetDefTab( USHORT nTab );
//STRIP001  USHORT          GetDefTab() const;

//STRIP001  BOOL            IsFlatMode() const;
//STRIP001  void            SetFlatMode( BOOL bFlat );

//STRIP001     void            EnableAutoColor( BOOL b );
//STRIP001     BOOL            IsAutoColorEnabled() const;

//STRIP001     void            ForceAutoColor( BOOL b );
    BOOL            IsForceAutoColor() const;

//STRIP001     void            OverwriteLevel0Bullet( const SvxNumberFormat& rNumberFormat );
    EBulletInfo     GetBulletInfo( USHORT nPara );

//STRIP001  void        SetWordDelimiters( const String& rDelimiters );
//STRIP001  String      GetWordDelimiters() const;
//STRIP001  String      GetWord( USHORT nPara, xub_StrLen nIndex );

    void            StripPortions();

    // #101498#
    virtual void    DrawingText( const Point& rStartPos, const String& rText, USHORT nTextStart, USHORT nTextLen,
                        const long* pDXArray, const SvxFont& rFont,
                        USHORT nPara, xub_StrLen nIndex, BYTE nRightToLeft);

    Size            CalcTextSize();

//STRIP001  Point           GetDocPos( Paragraph* pPara );

    void                SetStyleSheetPool( SfxStyleSheetPool* pSPool );
    SfxStyleSheetPool*  GetStyleSheetPool();

    BOOL            IsInSelectionMode() const;

    void            SetStyleSheet( ULONG nPara, SfxStyleSheet* pStyle );
    SfxStyleSheet*  GetStyleSheet( ULONG nPara );

    void            SetParaAttribs( ULONG nPara, const SfxItemSet&, bool bApiCall = false );
    SfxItemSet      GetParaAttribs( ULONG nPara );

//STRIP001  void            Remove( Paragraph* pPara, ULONG nParaCount );
//STRIP001  BOOL            Expand( Paragraph* );
//STRIP001  BOOL            Collapse( Paragraph* );

    // gibt ein Array mit den Bulletbreiten der n Einrueckebenen
    // zurueck. Letzter Wert muss -1 sein. Wird vom Outliner geloescht.
    Link            GetWidthArrReqHdl() const{ return aWidthArrReqHdl; }
    void            SetWidthArrReqHdl(const Link& rLink){aWidthArrReqHdl=rLink; }

    void            SetControlWord( ULONG nWord );
    ULONG           GetControlWord() const;

    Link            GetBeginMovingHdl() const { return aBeginMovingHdl; }
    void            SetBeginMovingHdl(const Link& rLink) {aBeginMovingHdl=rLink;}
    Link            GetEndMovingHdl() const {return aEndMovingHdl;}
    void            SetEndMovingHdl( const Link& rLink){aEndMovingHdl=rLink;}

    ULONG           GetLineCount( ULONG nParagraph ) const;
    USHORT          GetLineLen( ULONG nParagraph, USHORT nLine ) const;
    ULONG           GetLineHeight( ULONG nParagraph, ULONG nLine = 0 );

    // nFormat muss ein Wert aus dem enum EETextFormat sein (wg.CLOOKS)
    ULONG           Read( SvStream& rInput, USHORT, SvKeyValueIterator* pHTTPHeaderAttrs = NULL );

    SfxUndoManager& GetUndoManager();

    void            QuickSetAttribs( const SfxItemSet& rSet, const ESelection& rSel );
    void            QuickInsertField( const SvxFieldItem& rFld, const ESelection& rSel );
    void            QuickInsertLineBreak( const ESelection& rSel );

    // nur fuer EditEngine-Modus
    void            QuickInsertText( const String& rText, const ESelection& rSel );
    void            QuickDelete( const ESelection& rSel );
    void            QuickRemoveCharAttribs( USHORT nPara, USHORT nWhich = 0 );
    void            QuickFormatDoc( BOOL bFull = FALSE );

    BOOL            UpdateFields();
//STRIP001  void            RemoveFields( BOOL bKeepFieldText, TypeId aType = NULL );

//STRIP001  virtual void    FieldClicked( const SvxFieldItem& rField, USHORT nPara, xub_StrLen nPos );
//STRIP001  virtual void    FieldSelected( const SvxFieldItem& rField, USHORT nPara, xub_StrLen nPos );
    virtual String  CalcFieldValue( const SvxFieldItem& rField, USHORT nPara, xub_StrLen nPos, Color*& rTxtColor, Color*& rFldColor );

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

    // Depricated
    void            SetDefaultLanguage( LanguageType eLang );
//STRIP001  LanguageType    GetDefaultLanguage() const;

//STRIP001  BOOL            HasOnlineSpellErrors() const;
//STRIP001  void            CompleteOnlineSpelling();

    // Depricated
//STRIP001  EESpellState    HasSpellErrors( LanguageType eLang );

//STRIP001  EESpellState    HasSpellErrors();
//STRIP001  BOOL            HasText( const SvxSearchItem& rSearchItem );
//STRIP001  virtual BOOL    SpellNextDocument();

    void            SetEditTextObjectPool( SfxItemPool* pPool );
    SfxItemPool*    GetEditTextObjectPool() const;

    void            SetRefDevice( OutputDevice* pRefDev );
    OutputDevice*   GetRefDevice() const;

//STRIP001  USHORT          GetFirstLineOffset( ULONG nParagraph );

    ULONG           GetTextHeight() const;
    ULONG           GetTextHeight( ULONG nParagraph ) const;
    Point           GetDocPosTopLeft( ULONG nParagraph );
    Point           GetDocPos( const Point& rPaperPos ) const;
    BOOL            IsTextPos( const Point& rPaperPos, USHORT nBorder = 0 );
    BOOL            IsTextPos( const Point& rPaperPos, USHORT nBorder, BOOL* pbBuuletPos );

    void            SetGlobalCharStretching( USHORT nX = 100, USHORT nY = 100 );
//STRIP001  void            GetGlobalCharStretching( USHORT& rX, USHORT& rY );
    void            DoStretchChars( USHORT nX, USHORT nY );
    void            EraseVirtualDevice();

    void            SetBigTextObjectStart( USHORT nStartAtPortionCount );
//STRIP001  USHORT          GetBigTextObjectStart() const;
    BOOL            ShouldCreateBigTextObject() const;

    const EditEngine& GetEditEngine() const { return *((EditEngine*)pEditEngine); }

    // this is needed for StarOffice Api
    void SetLevelDependendStyleSheet( USHORT nPara );

    USHORT  GetOutlinerMode() const { return nOutlinerMode & OUTLINERMODE_USERMASK; }
};

}//end of namespace binfilter
#endif

