/*************************************************************************
 *
 *  $RCSfile: tabline.hxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:23:49 $
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
#ifndef _SVX_TAB_LINE_HXX
#define _SVX_TAB_LINE_HXX

// include ---------------------------------------------------------------

#ifndef _IMAGEBTN_HXX //autogen
#include <vcl/imagebtn.hxx>
#endif
#ifndef _GROUP_HXX //autogen
#include <vcl/group.hxx>
#endif
#ifndef _STDCTRL_HXX //autogen
#include <svtools/stdctrl.hxx>
#endif
#ifndef _SVDPAGE_HXX //autogen
#include <bf_svx/svdpage.hxx>
#endif
#ifndef _SVX_XLINEIT0_HXX //autogen
#include <bf_svx/xlineit0.hxx>
#endif
#ifndef _SVX_XLINIIT_HXX //autogen
#include <bf_svx/xlineit.hxx>
#endif
#ifndef _SVX_XSETITEM_HXX //autogen
#include <bf_svx/xsetit.hxx>
#endif

#ifndef _SVX_DLG_CTRL_HXX
#include <bf_svx/dlgctrl.hxx>
#endif
#ifndef _XOUTX_HXX //autogen
#include <bf_svx/xoutx.hxx>
#endif

#ifndef _SV_MENUBTN_HXX
#include <vcl/menubtn.hxx>
#endif
//STRIP001 class SvxBrushItem;
// define ----------------------------------------------------------------

//STRIP001 typedef USHORT ChangeType; // auch in tab_area.hxx (mitpflegen !!!)

//STRIP001 #define CT_NONE                 ( (ChangeType) 0x0000 )
//STRIP001 #define CT_MODIFIED             ( (ChangeType) 0x0001 )
//STRIP001 #define CT_CHANGED              ( (ChangeType) 0x0002 )
//STRIP001 #define CT_SAVED                ( (ChangeType) 0x0004 )

//STRIP001 class SdrModel;
//STRIP001 class SdrObject;

/*************************************************************************
|*
|* Transform-Tab-Dialog
|*
\************************************************************************/

//STRIP001 class SvxLineTabDialog : public SfxTabDialog
//STRIP001 {
//STRIP001 private:
//STRIP001  SdrModel*           pDrawModel;
//STRIP001  const SdrObject*    pObj;
//STRIP001
//STRIP001  const SfxItemSet&   rOutAttrs;
//STRIP001
//STRIP001  XColorTable*        pColorTab;
//STRIP001  XDashList*          pDashList;
//STRIP001  XDashList*          pNewDashList;
//STRIP001  XLineEndList*       pLineEndList;
//STRIP001  XLineEndList*       pNewLineEndList;
//STRIP001  BOOL                bObjSelected;
//STRIP001
//STRIP001  ChangeType          nLineEndListState;
//STRIP001  ChangeType          nDashListState;
//STRIP001  USHORT              nPageType;
//STRIP001  USHORT              nDlgType;
//STRIP001  USHORT              nPosDashLb;
//STRIP001  USHORT              nPosLineEndLb;
//STRIP001
//STRIP001  virtual void        PageCreated( USHORT nId, SfxTabPage &rPage );
//STRIP001
//STRIP001 protected:
//STRIP001  virtual short       Ok();
//STRIP001 #ifdef _SVX_TABLINE_CXX
//STRIP001  DECL_LINK( CancelHdl, void * );
//STRIP001  void                SavePalettes();
//STRIP001 #endif
//STRIP001
//STRIP001 public:
//STRIP001  SvxLineTabDialog( Window* pParent, const SfxItemSet* pAttr,
//STRIP001                    SdrModel* pModel, const SdrObject* pObj = NULL,
//STRIP001                    BOOL bHasObj = TRUE );
//STRIP001  ~SvxLineTabDialog();
//STRIP001
//STRIP001  void             SetNewDashList( XDashList* pInLst)
//STRIP001                      { pNewDashList = pInLst; }
//STRIP001  XDashList*       GetNewDashList() const { return pNewDashList; }
//STRIP001  const XDashList* GetDashList() const { return pDashList; }
//STRIP001
//STRIP001  void                SetNewLineEndList( XLineEndList* pInLst)
//STRIP001                          { pNewLineEndList = pInLst; }
//STRIP001  XLineEndList*       GetNewLineEndList() const { return pNewLineEndList; }
//STRIP001  const XLineEndList* GetLineEndList() const { return pLineEndList; }
//STRIP001 };

/*************************************************************************
|*
|* Linien-Tab-Page
|*
\************************************************************************/

//defines fuer die Symbolauswahl auf der Page
//Positive Werte (0,...n) gibt den Indes in pSymbollist an, sonst :
#define SVX_SYMBOLTYPE_NONE       (-3)  //Symbol unsichtbar
#define SVX_SYMBOLTYPE_AUTO       (-2)  //Symbol automatisch erzeugen
#define SVX_SYMBOLTYPE_BRUSHITEM  (-1)  //Symbol ist als Graphic im Item enthalten:
#define SVX_SYMBOLTYPE_UNKNOWN  (-100) //unbekannt/nicht initialisiert

#if SUPD>642
#else
//assert compatibility to removed NumMenuButton
//STRIP001 class LineLocalExtMenuButton : public MenuButton
//STRIP001 {
//STRIP001  Link            maClickHdl_Impl;
//STRIP001  public:
//STRIP001         LineLocalExtMenuButton(Window* pParent, const ResId& rResId) :
//STRIP001          MenuButton(pParent, rResId){}
//STRIP001
//STRIP001 };
#endif

//STRIP001 class SvxLineTabPage : public SvxTabPage
//STRIP001 {
//STRIP001 private:
//STRIP001  FixedText           aFtLineStyle;
//STRIP001  LineLB              aLbLineStyle;
//STRIP001  FixedText           aFtColor;
//STRIP001  ColorLB             aLbColor;
//STRIP001  FixedText           aFtLineWidth;
//STRIP001  MetricField         aMtrLineWidth;
//STRIP001  FixedText           aFtTransparent;
//STRIP001  MetricField         aMtrTransparent;
//STRIP001  FixedLine           aFlLine;
//STRIP001  FixedText           aFtLineEndsStyle;
//STRIP001  LineEndLB           aLbStartStyle;
//STRIP001  FixedText           aFtLineEndsWidth;
//STRIP001  MetricField         aMtrStartWidth;
//STRIP001  TriStateBox         aTsbCenterStart;
//STRIP001  LineEndLB           aLbEndStyle;
//STRIP001  MetricField         aMtrEndWidth;
//STRIP001  TriStateBox         aTsbCenterEnd;
//STRIP001  CheckBox            aCbxSynchronize;
//STRIP001  FixedLine           aFlLineEnds;
//STRIP001  SvxXLinePreview     aCtlPreview;
//STRIP001  FixedLine           aFLSeparator;
//STRIP001
//STRIP001  //#58425# Symbole auf einer Linie (z.B. StarChart) ->
//STRIP001  BOOL                bNewSize;
//STRIP001  Graphic             aAutoSymbolGraphic;
//STRIP001  long                nNumMenuGalleryItems;
//STRIP001  long                nSymbolType;
//STRIP001  const SfxItemSet    *pSymbolAttr;
//STRIP001  FixedLine           aFlSymbol;
//STRIP001 #if SUPD>642
//STRIP001     MenuButton          aSymbolMB;
//STRIP001 #else
//STRIP001     LineLocalExtMenuButton  aSymbolMB;
//STRIP001 #endif
//STRIP001     FixedText           aSymbolWidthFT;
//STRIP001  MetricField         aSymbolWidthMF;
//STRIP001  FixedText           aSymbolHeightFT;
//STRIP001  MetricField         aSymbolHeightMF;
//STRIP001  CheckBox            aSymbolRatioCB;
//STRIP001  List                aGrfNames;
//STRIP001  List                aGrfBrushItems;
//STRIP001  String              sNumCharFmtName;
//STRIP001  BOOL                bLastWidthModified;
//STRIP001  Size                aSymbolLastSize;
//STRIP001  Graphic             aSymbolGraphic;
//STRIP001  Size                aSymbolSize;
//STRIP001  BOOL                bSymbols;
//STRIP001  //Handler für Gallery-Popup-Menue-Button + Size
//STRIP001  DECL_LINK( GraphicHdl_Impl, MenuButton * );
//STRIP001  DECL_LINK( MenuCreateHdl_Impl, MenuButton * );
//STRIP001  DECL_STATIC_LINK( SvxLineTabPage, GraphicArrivedHdl_Impl, SvxBrushItem* );
//STRIP001  DECL_LINK( SizeHdl_Impl, MetricField * );
//STRIP001  DECL_LINK( RatioHdl_Impl, CheckBox * );
//STRIP001  // <- Symbole
//STRIP001
//STRIP001
//STRIP001  const SfxItemSet&   rOutAttrs;
//STRIP001  RECT_POINT          eRP;
//STRIP001  BOOL                bObjSelected;
//STRIP001
//STRIP001  XOutdevItemPool*    pXPool;
//STRIP001  XOutputDevice       XOut;
//STRIP001  XLineStyleItem      aXLStyle;
//STRIP001  XLineWidthItem      aXWidth;
//STRIP001  XLineDashItem       aXDash;
//STRIP001  XLineColorItem      aXColor;
//STRIP001  XLineAttrSetItem    aXLineAttr;
//STRIP001  SfxItemSet&         rXLSet;
//STRIP001
//STRIP001  XColorTable*        pColorTab;
//STRIP001  XDashList*          pDashList;
//STRIP001  XLineEndList*       pLineEndList;
//STRIP001  SdrObjList          *pSymbolList;
//STRIP001
//STRIP001  ChangeType*         pnLineEndListState;
//STRIP001  ChangeType*         pnDashListState;
//STRIP001  USHORT*             pPageType;
//STRIP001  USHORT*             pDlgType;
//STRIP001  USHORT*             pPosDashLb;
//STRIP001  USHORT*             pPosLineEndLb;
//STRIP001
//STRIP001  SfxMapUnit          ePoolUnit;
//STRIP001
//STRIP001  // #63083#
//STRIP001  INT32               nActLineWidth;
//STRIP001
//STRIP001 #ifdef _SVX_TPLINE_CXX
//STRIP001  DECL_LINK( ClickInvisibleHdl_Impl, void * );
//STRIP001  DECL_LINK( ChangeStartHdl_Impl, void * );
//STRIP001  DECL_LINK( ChangeEndHdl_Impl, void * );
//STRIP001  DECL_LINK( ChangePreviewHdl_Impl, void * );
//STRIP001  DECL_LINK( ChangeTransparentHdl_Impl, void * );
//STRIP001
//STRIP001  BOOL FillXLSet_Impl();
//STRIP001 #endif
//STRIP001
//STRIP001  void FillListboxes();
//STRIP001 public:
//STRIP001
//STRIP001  //#58425# Symbole auf einer Linie (z.B. StarChart) Controls an/aus
//STRIP001
//STRIP001  // Symbolcontrols aktivieren:
//STRIP001  void ShowSymbolControls(BOOL bOn);
//STRIP001  //Liste von SdrObject(s), aus der Anhand eines positiven Wertes (Wert >= 0) im Attribut
//STRIP001  //SID_ATTR_SYMBOLTYPE  ein Symbol erzeugt wird. Die Liste ist cyclisch, d.h. gilt
//STRIP001  //SID_ATTR_SYMBOLTYPE.GetValue() >= pList->Count(), so wird das Listenelement
//STRIP001  //SID_ATTR_SYMBOLTYPE->GetValue() modulo pList->Count() benutzt
//STRIP001  void SetSymbolList(SdrObjList *pList){pSymbolList=pList;};
//STRIP001  //Attribute für Symbol, nur nötig, wenn ungleich den Linienattributen
//STRIP001  void SetSymbolAttr(const SfxItemSet* pSet){pSymbolAttr=pSet;};
//STRIP001  //Bei automatischen Symbolen ist hier eine Graphic mit dem Symbol zu setzten, das von
//STRIP001  //der Automatik des aufrufenden Moduls benutzt wird, dies dient nur der korrekten
//STRIP001  //Darstellung, Size-Controls sind bei Automatik disabled.
//STRIP001  void SetAutoSymbolGraphic(Graphic *p){aAutoSymbolGraphic=*p;}
//STRIP001
//STRIP001
//STRIP001
//STRIP001  SvxLineTabPage( Window* pParent, const SfxItemSet& rInAttrs );
//STRIP001  virtual ~SvxLineTabPage();
//STRIP001
//STRIP001  void    Construct();
//STRIP001
//STRIP001
//STRIP001  static  SfxTabPage* Create( Window*, const SfxItemSet& );
//STRIP001  static  USHORT*    GetRanges();
//STRIP001
//STRIP001  virtual BOOL FillItemSet( SfxItemSet& );
//STRIP001  virtual void Reset( const SfxItemSet& );
//STRIP001
//STRIP001  virtual void ActivatePage( const SfxItemSet& rSet );
//STRIP001  virtual int  DeactivatePage( SfxItemSet* pSet );
//STRIP001
//STRIP001  virtual void PointChanged( Window* pWindow, RECT_POINT eRP );
//STRIP001
//STRIP001  virtual void FillUserData();
//STRIP001
//STRIP001  void    SetColorTable( XColorTable* pColTab ) { pColorTab = pColTab; }
//STRIP001  void    SetDashList( XDashList* pDshLst ) { pDashList = pDshLst; }
//STRIP001  void    SetLineEndList( XLineEndList* pLneEndLst) { pLineEndList = pLneEndLst; }
//STRIP001  void    SetObjSelected( BOOL bHasObj ) { bObjSelected = bHasObj; }
//STRIP001
//STRIP001  void    SetPageType( USHORT* pInType ) { pPageType = pInType; }
//STRIP001  void    SetDlgType( USHORT* pInType ) { pDlgType = pInType; }
//STRIP001  void    SetPosDashLb( USHORT* pInPos ) { pPosDashLb = pInPos; }
//STRIP001  void    SetPosLineEndLb( USHORT* pInPos ) { pPosLineEndLb = pInPos; }
//STRIP001
//STRIP001  void    SetLineEndChgd( ChangeType* pIn ) { pnLineEndListState = pIn; }
//STRIP001  void    SetDashChgd( ChangeType* pIn ) { pnDashListState = pIn; }
//STRIP001
//STRIP001     virtual void    DataChanged( const DataChangedEvent& rDCEvt );
//STRIP001 };

/*************************************************************************
|*
|* Linien-Definitions-Tab-Page
|*
\************************************************************************/

//STRIP001 class SvxLineDefTabPage : public SfxTabPage
//STRIP001 {
//STRIP001 private:
//STRIP001  FixedLine           aFlDefinition;
//STRIP001  FixedText           aFTLinestyle;
//STRIP001  LineLB              aLbLineStyles;
//STRIP001  FixedText           aFtType;
//STRIP001  ListBox             aLbType1;
//STRIP001  ListBox             aLbType2;
//STRIP001  FixedText           aFtNumber;
//STRIP001  NumericField        aNumFldNumber1;
//STRIP001  NumericField        aNumFldNumber2;
//STRIP001  FixedText           aFtLength;
//STRIP001  MetricField         aMtrLength1;
//STRIP001  MetricField         aMtrLength2;
//STRIP001  FixedText           aFtDistance;
//STRIP001  MetricField         aMtrDistance;
//STRIP001  CheckBox            aCbxSynchronize;
//STRIP001  PushButton          aBtnAdd;
//STRIP001  PushButton          aBtnModify;
//STRIP001  PushButton          aBtnDelete;
//STRIP001  ImageButton         aBtnLoad;
//STRIP001  ImageButton         aBtnSave;
//STRIP001  SvxXLinePreview     aCtlPreview;
//STRIP001
//STRIP001  const SfxItemSet&   rOutAttrs;
//STRIP001  XDash               aDash;
//STRIP001  BOOL                bObjSelected;
//STRIP001
//STRIP001  XOutdevItemPool*    pXPool;
//STRIP001  XOutputDevice       XOut;
//STRIP001  XLineStyleItem      aXLStyle;
//STRIP001  XLineWidthItem      aXWidth;
//STRIP001  XLineDashItem       aXDash;
//STRIP001  XLineColorItem      aXColor;
//STRIP001  XLineAttrSetItem    aXLineAttr;
//STRIP001  SfxItemSet&         rXLSet;
//STRIP001
//STRIP001  XDashList*          pDashList;
//STRIP001
//STRIP001  ChangeType*         pnDashListState;
//STRIP001  USHORT*             pPageType;
//STRIP001  USHORT*             pDlgType;
//STRIP001  USHORT*             pPosDashLb;
//STRIP001
//STRIP001  SfxMapUnit          ePoolUnit;
//STRIP001  FieldUnit           eFUnit;
//STRIP001
//STRIP001 #ifdef _SVX_TPLNEDEF_CXX
//STRIP001  void FillDash_Impl();
//STRIP001  void FillDialog_Impl();
//STRIP001
//STRIP001  DECL_LINK( ClickAddHdl_Impl, void * );
//STRIP001  DECL_LINK( ClickModifyHdl_Impl, void * );
//STRIP001  DECL_LINK( ClickDeleteHdl_Impl, void * );
//STRIP001  DECL_LINK( SelectLinestyleHdl_Impl, void * );
//STRIP001  DECL_LINK( ChangePreviewHdl_Impl, void * );
//STRIP001  DECL_LINK( ChangeNumber1Hdl_Impl, void * );
//STRIP001  DECL_LINK( ChangeNumber2Hdl_Impl, void * );
//STRIP001  DECL_LINK( ClickLoadHdl_Impl, void * );
//STRIP001  DECL_LINK( ClickSaveHdl_Impl, void * );
//STRIP001  DECL_LINK( ChangeMetricHdl_Impl, void * );
//STRIP001  DECL_LINK( SelectTypeHdl_Impl, void * );
//STRIP001
//STRIP001  void CheckChanges_Impl();
//STRIP001 #endif
//STRIP001
//STRIP001 public:
//STRIP001  SvxLineDefTabPage( Window* pParent, const SfxItemSet& rInAttrs  );
//STRIP001
//STRIP001  void    Construct();
//STRIP001
//STRIP001  static  SfxTabPage* Create( Window*, const SfxItemSet& );
//STRIP001  virtual BOOL FillItemSet( SfxItemSet& );
//STRIP001  virtual void Reset( const SfxItemSet & );
//STRIP001
//STRIP001  virtual void ActivatePage( const SfxItemSet& rSet );
//STRIP001  virtual int  DeactivatePage( SfxItemSet* pSet );
//STRIP001
//STRIP001  void    SetDashList( XDashList* pDshLst ) { pDashList = pDshLst; }
//STRIP001  void    SetObjSelected( BOOL bHasObj ) { bObjSelected = bHasObj; }
//STRIP001
//STRIP001  void    SetPageType( USHORT* pInType ) { pPageType = pInType; }
//STRIP001  void    SetDlgType( USHORT* pInType ) { pDlgType = pInType; }
//STRIP001  void    SetPosDashLb( USHORT* pInPos ) { pPosDashLb = pInPos; }
//STRIP001
//STRIP001  void    SetDashChgd( ChangeType* pIn ) { pnDashListState = pIn; }
//STRIP001
//STRIP001     virtual void    DataChanged( const DataChangedEvent& rDCEvt );
//STRIP001 };

/*************************************************************************
|*
|* Linienenden-Definitions-Tab-Page
|*
\************************************************************************/

//STRIP001 class SvxLineEndDefTabPage : public SfxTabPage
//STRIP001 {
//STRIP001 private:
//STRIP001  FixedLine           aFlTip;
//STRIP001  FixedText           aFTTitle;
//STRIP001  Edit                aEdtName;
//STRIP001  FixedText           aFTLineEndStyle;
//STRIP001  LineEndLB           aLbLineEnds;
//STRIP001  PushButton          aBtnAdd;
//STRIP001  PushButton          aBtnModify;
//STRIP001  PushButton          aBtnDelete;
//STRIP001  ImageButton         aBtnLoad;
//STRIP001  ImageButton         aBtnSave;
//STRIP001  FixedInfo           aFiTip;
//STRIP001  SvxXLinePreview     aCtlPreview;
//STRIP001
//STRIP001  const SfxItemSet&   rOutAttrs;
//STRIP001  const SdrObject*    pPolyObj;
//STRIP001  BOOL                bObjSelected;
//STRIP001
//STRIP001  XOutdevItemPool*    pXPool;
//STRIP001  XOutputDevice       XOut;
//STRIP001  XLineStyleItem      aXLStyle;
//STRIP001  XLineWidthItem      aXWidth;
//STRIP001  XLineColorItem      aXColor;
//STRIP001  XLineAttrSetItem    aXLineAttr;
//STRIP001  SfxItemSet&         rXLSet;
//STRIP001
//STRIP001  XLineEndList*       pLineEndList;
//STRIP001
//STRIP001  ChangeType*         pnLineEndListState;
//STRIP001  USHORT*             pPageType;
//STRIP001  USHORT*             pDlgType;
//STRIP001  USHORT*             pPosLineEndLb;
//STRIP001
//STRIP001 #ifdef _SVX_TPLNEEND_CXX
//STRIP001  DECL_LINK( ClickAddHdl_Impl, void * );
//STRIP001  DECL_LINK( ClickModifyHdl_Impl, void * );
//STRIP001  DECL_LINK( ClickDeleteHdl_Impl, void * );
//STRIP001  DECL_LINK( ClickLoadHdl_Impl, void * );
//STRIP001  DECL_LINK( ClickSaveHdl_Impl, void * );
//STRIP001  DECL_LINK( SelectLineEndHdl_Impl, void * );
//STRIP001  long ChangePreviewHdl_Impl( void* p );
//STRIP001
//STRIP001  void CheckChanges_Impl();
//STRIP001 #endif
//STRIP001
//STRIP001 public:
//STRIP001  SvxLineEndDefTabPage( Window* pParent, const SfxItemSet& rInAttrs );
//STRIP001  ~SvxLineEndDefTabPage();
//STRIP001
//STRIP001  void    Construct();
//STRIP001
//STRIP001  static  SfxTabPage* Create( Window*, const SfxItemSet& );
//STRIP001  virtual BOOL FillItemSet( SfxItemSet& );
//STRIP001  virtual void Reset( const SfxItemSet & );
//STRIP001
//STRIP001  virtual void ActivatePage( const SfxItemSet& rSet );
//STRIP001  virtual int  DeactivatePage( SfxItemSet* pSet );
//STRIP001
//STRIP001  void    SetLineEndList( XLineEndList* pInList ) { pLineEndList = pInList; }
//STRIP001  void    SetPolyObj( const SdrObject* pObj ) { pPolyObj = pObj; }
//STRIP001  void    SetObjSelected( BOOL bHasObj ) { bObjSelected = bHasObj; }
//STRIP001
//STRIP001  void    SetPageType( USHORT* pInType ) { pPageType = pInType; }
//STRIP001  void    SetDlgType( USHORT* pInType ) { pDlgType = pInType; }
//STRIP001  void    SetPosLineEndLb( USHORT* pInPos ) { pPosLineEndLb = pInPos; }
//STRIP001
//STRIP001  void    SetLineEndChgd( ChangeType* pIn ) { pnLineEndListState = pIn; }
//STRIP001
//STRIP001     virtual void    DataChanged( const DataChangedEvent& rDCEvt );
//STRIP001 };

#endif // _SVX_TAB_LINE_HXX

