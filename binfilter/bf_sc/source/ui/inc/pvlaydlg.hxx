/*************************************************************************
 *
 *  $RCSfile: pvlaydlg.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:30:04 $
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

#ifndef SC_PVLAYDLG_HXX
#define SC_PVLAYDLG_HXX

#ifndef _LSTBOX_HXX //autogen
#include <vcl/lstbox.hxx>
#endif
#ifndef _SCRBAR_HXX //autogen
#include <vcl/scrbar.hxx>
#endif
#ifndef _STDCTRL_HXX //autogen
#include <svtools/stdctrl.hxx>
#endif
#ifndef _MOREBTN_HXX //autogen
#include <vcl/morebtn.hxx>
#endif

#ifndef SC_SCGLOB_HXX
#include "global.hxx"
#endif

#ifndef SC_ANYREFDG_HXX
#include "anyrefdg.hxx"
#endif

#ifndef SC_FIELDWND_HXX
#include "fieldwnd.hxx"
#endif
namespace binfilter {


/*==========================================================================*\

    Eine Instanz der Klasse ScPivotLayoutDlg ist ein (semi-)modaler
    Dialog, in dem mit der Maus Felder mit Spaltenueberschriften den
    drei Pivot-Kategorien "Spalte", "Zeile" und "Daten" zugeordnet
    werden koennen.

    Der Dialog erhaelt in der Struktur LabelData Informationen ueber
    diese Ueberschriften (Name, Art (Zahl/String) und Funktionsmaske).
    Weiterhin werden drei PivotFeld-Arrays uebergeben, mit denen die
    drei Kategorie-Fenster initialisiert werden. Ein Kategorie-Fenster
    wird durch eine Instanz der Klasse FieldWindow dargestellt. Ein
    solches Fenster ist fuer die Darstellung der Datenstrukturen am
    Schirm zustaendig. Es meldet Mausaktionen an den Dialog weiter und
    bietet entsprechende Methoden zur Veraenderung der Darstellung.
    Der Dialog sorgt fuer den Abgleich der interenen Datenstrukturen mit
    der Bildschirmdarstellung. Ein weiteres FieldWindow (Select) bietet
    alle Tabellenueberschriften zur Auswahl an, ist also "read-only".

\*==========================================================================*/

//============================================================================

class ScViewData;
class ScDocument;
class ScRangeData;
struct FuncData;
class ScDPObject;

//============================================================================

#define FUNC_COUNT 11

//STRIP001 class ScDPLayoutDlg : public ScAnyRefDlg
//STRIP001 {
//STRIP001 public:
//STRIP001                             ScDPLayoutDlg(
//STRIP001                                 SfxBindings* pB,
//STRIP001                                 SfxChildWindow* pCW,
//STRIP001                                 Window* pParent,
//STRIP001                                 const ScDPObject* pDPObject );
//STRIP001     virtual                 ~ScDPLayoutDlg();
//STRIP001
//STRIP001     virtual void            SetReference( const ScRange& rRef, ScDocument* pDoc );
//STRIP001     virtual BOOL            IsRefInputMode() const { return bRefInputMode; }
//STRIP001     virtual void            SetActive();
//STRIP001     virtual BOOL            Close();
//STRIP001
//STRIP001     void                    NotifyDoubleClick    ( ScDPFieldType eType, long nFieldIndex );
//STRIP001     PointerStyle            NotifyMouseButtonDown( ScDPFieldType eType, long nFieldIndex );
//STRIP001     void                    NotifyMouseButtonUp  ( const Point& rAt );
//STRIP001     PointerStyle            NotifyMouseMove      ( const Point& rAt );
//STRIP001     void                    NotifyFieldFocus     ( ScDPFieldType eType, BOOL bGotFocus );
//STRIP001     void                    NotifyMoveField      ( ScDPFieldType eToType );
//STRIP001     void                    NotifyRemoveField    ( ScDPFieldType eType, long nFieldIndex );
//STRIP001     BOOL                    NotifyMoveSlider     ( USHORT nKeyCode );   // return TRUE, if position changed
//STRIP001
//STRIP001 protected:
//STRIP001     virtual void            Deactivate();
//STRIP001
//STRIP001 private:
//STRIP001     FixedLine               aFlLayout;
//STRIP001     FixedText               aFtCol;
//STRIP001     ScDPFieldWindow         aWndCol;
//STRIP001     FixedText               aFtRow;
//STRIP001     ScDPFieldWindow         aWndRow;
//STRIP001     FixedText               aFtData;
//STRIP001     ScDPFieldWindow         aWndData;
//STRIP001     ScDPFieldWindow         aWndSelect;
//STRIP001     ScrollBar               aSlider;
//STRIP001     FixedInfo               aFtInfo;
//STRIP001
//STRIP001     FixedLine               aFlAreas;
//STRIP001     ListBox                 aLbOutPos;
//STRIP001     FixedText               aFtOutArea;
//STRIP001     ScRefEdit               aEdOutPos;
//STRIP001     ScRefButton             aRbOutPos;
//STRIP001     CheckBox                aBtnIgnEmptyRows;
//STRIP001     CheckBox                aBtnDetectCat;
//STRIP001     CheckBox                aBtnTotalCol;
//STRIP001     CheckBox                aBtnTotalRow;
//STRIP001
//STRIP001     OKButton                aBtnOk;
//STRIP001     CancelButton            aBtnCancel;
//STRIP001     HelpButton              aBtnHelp;
//STRIP001     PushButton              aBtnRemove;
//STRIP001     PushButton              aBtnOptions;
//STRIP001     MoreButton              aBtnMore;
//STRIP001
//STRIP001     const String            aStrUndefined;
//STRIP001     const String            aStrNewTable;
//STRIP001     String*                 aFuncNameArr[FUNC_COUNT];
//STRIP001
//STRIP001     ScDPFieldType           eDnDFromType;
//STRIP001     long                    nDnDFromIndex;
//STRIP001     BOOL                    bIsDrag;
//STRIP001
//STRIP001     Rectangle               aRectRow;
//STRIP001     Rectangle               aRectCol;
//STRIP001     Rectangle               aRectData;
//STRIP001     Rectangle               aRectSelect;
//STRIP001
//STRIP001     LabelData**             aLabelDataArr; // (nCol, Feldname, Zahl/Text)
//STRIP001     long                    nLabelCount;
//STRIP001
//STRIP001     ScDPFieldType           eLastActiveType;        /// Type of last active area.
//STRIP001     long                    nOffset;                /// Offset of first field in TYPE_SELECT area.
//STRIP001
//STRIP001     FuncData*               aSelectArr[MAX_LABELS]; // (nCol, nFuncMask)
//STRIP001     FuncData*               aColArr   [MAX_FIELDS]; // (nCol, nFuncMask)
//STRIP001     FuncData*               aRowArr   [MAX_FIELDS]; // (nCol, nFuncMask)
//STRIP001     FuncData*               aDataArr  [MAX_FIELDS]; // (nCol, nFuncMask)
//STRIP001
//STRIP001     BOOL                    bShowAll[MAX_LABELS];
//STRIP001
//STRIP001     ScDPObject*             pDlgDPObject;
//STRIP001     ScPivotParam            thePivotData;
//STRIP001     ScViewData*             pViewData;
//STRIP001     ScDocument*             pDoc;
//STRIP001     BOOL                    bRefInputMode;
//STRIP001
//STRIP001 #ifdef _PVLAYDLG_CXX
//STRIP001 private:
//STRIP001     ScDPFieldWindow&        GetFieldWindow  ( ScDPFieldType eType );
//STRIP001     void                    Init            ();
//STRIP001     void                    InitWndSelect   ( LabelData** ppLabelArr, long nLabels );
//STRIP001     void                    InitWnd         ( PivotField* pArr, long nCount, ScDPFieldType eType );
//STRIP001     void                    InitFocus       ();
//STRIP001     void                    CalcWndSizes    ();
//STRIP001     Point                   DlgPos2WndPos   ( const Point& rPt, Window& rWnd );
//STRIP001     LabelData*              GetLabelData    ( short nCol, long* pPos = NULL );
//STRIP001     String                  GetLabelString  ( short nCol );
//STRIP001     String                  GetFuncString   ( USHORT& rFuncMask, BOOL bIsValue = TRUE );
//STRIP001     BOOL                    Contains        ( FuncData** pArr, short nCol, long& nAt );
//STRIP001     void                    Remove          ( FuncData** pArr, long nAt );
//STRIP001     void                    Insert          ( FuncData** pArr, const FuncData& rFData, long nAt );
//STRIP001
//STRIP001     void                    AddField        ( long nFromIndex,
//STRIP001                                               ScDPFieldType eToType, const Point& rAtPos );
//STRIP001     void                    MoveField       ( ScDPFieldType eFromType, long nFromIndex,
//STRIP001                                               ScDPFieldType eToType, const Point&  rAtPos );
//STRIP001     void                    RemoveField     ( ScDPFieldType eRemType, long nRemIndex );
//STRIP001
//STRIP001     BOOL                    GetPivotArrays  ( PivotField*   pColArr,
//STRIP001                                               PivotField*   pRowArr,
//STRIP001                                               PivotField*   pDataArr,
//STRIP001                                               USHORT&       rColCount,
//STRIP001                                               USHORT&       rRowCount,
//STRIP001                                               USHORT&       rDataCount );
//STRIP001  // Handler
//STRIP001     DECL_LINK( ClickHdl, PushButton * );
//STRIP001  DECL_LINK( ScrollHdl, ScrollBar * );
//STRIP001  DECL_LINK( SelAreaHdl, ListBox * );
//STRIP001  DECL_LINK( MoreClickHdl, MoreButton * );
//STRIP001  DECL_LINK( EdModifyHdl, Edit * );
//STRIP001  DECL_LINK( OkHdl, OKButton * );
//STRIP001  DECL_LINK( CancelHdl, CancelButton * );
//STRIP001 #endif
//STRIP001 };



} //namespace binfilter
#endif // SC_PVLAYDLG_HXX

