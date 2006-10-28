/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: fesh.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 04:41:09 $
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
#ifndef _FESH_HXX
#define _FESH_HXX

#ifndef _EDITSH_HXX
#include <editsh.hxx>
#endif
#ifndef _ORNTENUM_HXX
#include <orntenum.hxx>
#endif
#ifndef _FLYENUM_HXX
#include <flyenum.hxx>
#endif

// OD 25.06.2003 #108784#
#ifndef _SVDTYPES_HXX
#include <bf_svx/svdtypes.hxx>
#endif

#include <vector>
class SvEmbeddedObject;
class SvEmbeddedObjectRef;
class SvInPlaceObject;
class Color;
namespace binfilter {

class SwFlyFrm;

class SwTabCols;
class SvxBrushItem;
class SwTableAutoFmt;
class SwFrm;
class SwTabFrm;
class SwFmtFrmSize;
class SvxBorderLine;
class SvStorageStream;
class SdrObject;

class Outliner;
class SotDataObject;
class SdrViewUserMarker;
class SwFrmFmt;
struct SwSortOptions;
class SdrMarkList;

enum FrmType
{
    //Fuer GetFrmType() und GetSelFrmType(). Der Return-Wert ist eine
    //Veroderung.
    FRMTYPE_NONE    = 0,
    FRMTYPE_PAGE    = 1,
    FRMTYPE_HEADER  = 2,
    FRMTYPE_FOOTER  = 4,
    FRMTYPE_BODY    = 8,
    FRMTYPE_COLUMN  = 16,
    FRMTYPE_TABLE   = 32,
    FRMTYPE_FLY_FREE    = 64,
    FRMTYPE_FLY_ATCNT   = 128,
    FRMTYPE_FLY_INCNT   = 256,
    FRMTYPE_FOOTNOTE    = 512,
    FRMTYPE_FTNPAGE     = 1024,
    FRMTYPE_FLY_ANY     = 2048,
    FRMTYPE_DRAWOBJ     = 4096,
    FRMTYPE_COLSECT     = 8192,
    FRMTYPE_COLSECTOUTTAB = 16384
};

#define FRMTYPE_ANYCOLSECT ( FRMTYPE_COLSECT | FRMTYPE_COLSECTOUTTAB )

enum GotoObjType
{
    DRAW_CONTROL = 1,
    DRAW_SIMPLE = 2,
    DRAW_ANY = 3,
    FLY_FRM = 4,
    FLY_GRF = 8,
    FLY_OLE = 16,
    FLY_ANY = 28,
    GOTO_ANY = 31
};

enum FlyProtectType
{
     FLYPROTECT_CONTENT     = 1,        // kann verodert werden!
     FLYPROTECT_SIZE        = 2,
     FLYPROTECT_POS         = 4,
     FLYPROTECT_PARENT      = 8,        // nur Parents untersuchen
     FLYPROTECT_FIXED       = 16        // nur nicht aufhebbarer Schutz
                                        // z.B. durch OLE-Server, gilt auch
                                        // fuer Dialog
};

enum ObjCntType     //Fuer das Ermitteln des Cntnts per Positon (D&D)
{
    OBJCNT_NONE,
    OBJCNT_FLY,
    OBJCNT_GRF,
    OBJCNT_OLE,
    OBJCNT_SIMPLE,
    OBJCNT_CONTROL,
    OBJCNT_URLBUTTON,

    OBJCNT_GROUPOBJ,
    OBJCNT_DONTCARE     // nicht bestimmbar - unterschiedliche Objecte selektiert
};

//fuer GetAnyCurRect
enum CurRectType
{
    RECT_PAGE,                  //Rect der aktuellen Seite.
    RECT_PAGE_CALC,             //... Seite wird ggf. Formatiert
    RECT_PAGE_PRT,              //Rect der aktuellen PrtArea der Seite
    RECT_FRM,                   //Rect des aktuellen Rahmen
    RECT_FLY_EMBEDDED,          //Rect des aktuellen FlyFrm
    RECT_FLY_PRT_EMBEDDED,      //Rect der PrtArea des FlyFrm
    RECT_SECTION,               //Rect des aktuellen Bereichs
    RECT_OUTTABSECTION,         //Rect des aktuellen Bereichs,
                                // aber ausserhalb der Tabelle
    RECT_SECTION_PRT,           //Rect der aktuellen PrtArea des Bereichs
    RECT_OUTTABSECTION_PRT,     //Rect der aktuellen PrtArea des Bereichs,
                                // aber ausserhalb der Tabelle
    RECT_HEADERFOOTER,          //Rect des aktuellen Headers/Footer
    RECT_HEADERFOOTER_PRT       //Rect der PrtArea des aktuellen Headers/Footers
};

struct SwGetCurColNumPara
{
    const SwFrmFmt* pFrmFmt;
    const SwRect* pPrtRect, *pFrmRect;
    SwGetCurColNumPara() : pFrmFmt( 0 ), pPrtRect( 0 ), pFrmRect( 0 ) {}
};

#define SW_PASTESDR_INSERT      1
#define SW_PASTESDR_REPLACE     2
#define SW_PASTESDR_SETATTR     3

#define SW_ADD_SELECT   1
#define SW_ENTER_GROUP  2
#define SW_LEAVE_FRAME  4

#define SW_MOVE_UP      0
#define SW_MOVE_DOWN    1
#define SW_MOVE_LEFT    2
#define SW_MOVE_RIGHT   3

#define SW_TABCOL_NONE  0
#define SW_TABCOL_HORI  1
#define SW_TABCOL_VERT  2

class SwFEShell : public SwEditShell
{
    SdrViewUserMarker *pChainFrom,
                      *pChainTo;
    BOOL bCheckForOLEInCaption;

    SwFlyFrm *FindFlyFrm() const;
    SwFlyFrm *FindFlyFrm( const SvEmbeddedObject *pObj ) const;

    //Actions fuer alle Shells beenden und ChangeLink rufen.





    //0 == in keiner Spalte
    USHORT _GetCurColNum( const SwFrm *pFrm,
                          SwGetCurColNumPara* pPara ) const;




    // Methoden fuers kopieren von DrawObjecten

        // get list of marked SdrObjects;
    // helper method for GetSelFrmType, IsSelContainsControl
    const SdrMarkList* _GetMarkList() const;


public:
    TYPEINFO();
    SwFEShell( SwDoc& rDoc, Window *pWin,
               SwRootFrm *pMaster = 0, const SwViewOption *pOpt = 0 );
    SwFEShell( SwEditShell& rShell, Window *pWin );
    virtual ~SwFEShell();

    // Copy und Paste Methoden fuer das interne Clipboard
    // Copy-Methode fuer Drag&Drop


    // befindet sich der selektierte Rahmen innerhalb eines anderen?
    // Innerhalb eines des sichtbaren Ankers?

//SS fuer DrawObjekte und Rahmen-----------------------------

    //Wenn ein Objekt angegeben wurde, so wird genau diese Markiert (anstatt
    //ueber die Position zu suchen.
    BOOL SelectObj( const Point& rSelPt, BYTE nFlag = 0, SdrObject *pObj = 0 );

    //Selektion nach oben unten bewegen (Z-Order).
    //TRUE  == ganz nach oben/unten
    //FALSE == einen ueberholen


    // folgende zwei Methoden returnen den enum SdrHdlKind, um sich ein
    // includen von SVDRAW.HXX zu ersparen als int deklariert.

    // #107513#
    // Test if there is a draw object at that position and if it should be selected.
    // The 'should' is aimed at Writer text fly frames which may be in front of
    // the draw object.
    sal_Bool ShouldObjectBeSelected(const Point& rPt);

    // Returns if Upper of frame at current position is section frame
    // Currently only used by the rules. To be replaced by something more
    // sophisticated one day.
    bool IsDirectlyInSection() const;

    //Returnwerte siehe oben FrmType.
    //pPt: Crsr bzw. DocPos; bStopAtFly: Bei Flys anhalten oder ueber den Anchor weitergehen
    // Obgleich (0,TRUE) eine Art Standard ist, sind die Parameter nicht defaultet, damit
    // bei jeder Benutzung insbesondere das bStopAtFly bewusst genutzt wird.
    USHORT GetFrmType( const Point *pPt, BOOL bStopAtFly ) const;
    USHORT GetSelFrmType() const;               //Selektion (Drawing)

    /** #108784# check whether selected frame contains a control;
     * companion method to GetSelFrmType, used for preventing
     * drag&drop of controls into header */
    bool IsSelContainsControl() const;

    ObjCntType GetObjCntTypeOfSelection( SdrObject** ppObj = 0 ) const;

    //Zum Anpassen der PosAttr bei Ankerwechseln.
    //Zum Verschieben von Flys mit der Tastatur

    // Groesse von Drawobjekten setzen


    //Methoden fuer die Statuszeile.

    //SS fuer die BriefUmschlaege: hole alle Seitengebundenen Objekte
    //und setze diese auf eine neue Seite.

    // zeige die aktuelle Selektion an ( ggfs. den Rahmen/DrawObject)
    virtual void MakeSelVisible();

    // returne das FrmFmt von dem evt. unter dem Point stehenden Object.
    // Das Object wird nicht selektiert!
    // returns a format too, if the point is over the text of any fly

    //Welcher Schutz ist am selektierten Objekt gesetzt?
    BYTE IsSelObjProtected( FlyProtectType eType ) const;

    //Liefert neben der Grafik in rName bei gelinkten Grafiken den Namen mit
    //Pfad und sonst den Grafiknamen. rbLink ist TRU bei gelinkten Grafiken.

//SS fuer Rahmen --------------------------------------------

    BOOL IsFrmSelected() const;
    // determines whether a frame or its environment is vertically formatted and right-to-left
    BOOL IsFrmVertical(BOOL bEnvironment, BOOL& bRightToLeft) const;

    SwFrmFmt* GetCurFrmFmt() const; //Wenn Rahmen, dann Rahmenvorlage, sonst 0
#ifdef ACCESSIBLE_LAYOUT
    const SwFlyFrm *GetCurrFlyFrm() const { return FindFlyFrm(); }
#endif

    // finde/loeschen den Fly, in dem der Cursor steht

    //Selebstaendiges selektieren von Flys

    //iterieren ueber Flys - fuer Basic-Collections

    //Wenn ein fly selectiert ist, zieht er den Crsr in den ersten CntntFrm

    //Get FlyFrameFormat; fuer UI Macro Anbindung an Flys
    const SwFrmFmt* GetFlyFrmFmt() const;
          SwFrmFmt* GetFlyFrmFmt();

    //OLE, Server fordert neue Groesse an, die gewuenschten Werte werden
    //als Rahmenattribute eingestellt. Wenn die Werte nicht erlaubt sind,
    //so wird von der Formatierung geclippt und eine Scalierung eingestellt.
    //siehe CalcAndSetScale().
    void RequestObjectResize( const SwRect &rRect, SvEmbeddedObject *pIPObj );

    //Der Client fuer das OleObject muss bezueglich der Scalierung auf dem
    //neuesten Stand gehalten werden. Impl in der WrtShell.
    //Wird ein Pointer auf eine Size uebergeben, so ist diese die aktuelle
    //Core-Groesse des Objectes. Anderfalls wird die Groesse per GetCurFlyRect()
    //besorgt.
    virtual void CalcAndSetScale( SvEmbeddedObjectRef xIPObj,
                                  const SwRect *pFlyPrtRect = 0,
                                  const SwRect *pFlyFrmRect = 0 ) = 0;

    //Objekte mit ActivateWhenVisible werden beim Paint Connected.
    //gerufen von notxtfrm::Paint, impl in wrtsh
    virtual void ConnectObj( SvInPlaceObjectRef xIPObj, const SwRect &rPrt,
                             const SwRect &rFrm ) = 0;

    //Sichbaren Bereich auf das Object setzen, wenn es noch nicht sichtbar ist.

    // check resize of OLE-Object
    BOOL IsCheckForOLEInCaption() const         { return bCheckForOLEInCaption; }
    void SetCheckForOLEInCaption( BOOL bFlag )  { bCheckForOLEInCaption = bFlag; }

    // setze am selektierten FlyFrame einen Namen

    // erezeuge eindeutige Namen fuer Rahmen

    // springe zum benannten Rahmen (Grafik/OLE)
    BOOL GotoFly( const String& rName, FlyCntType eType = FLYCNTTYPE_ALL,
                    BOOL bSelFrame = TRUE );
    // steht an der Position eine Grafik mit einer URL ?

    //Fuer das Chain wird immer der durch das Format spezifizierte Fly
    //mit dem durch den Point getroffenen verbunden.
    //In rRect wird das Rect des Flys geliefert (fuer Highlight desselben)
        int Chain( SwFrmFmt &rSource, const SwFrmFmt &rDest );
    void HideChainMarker();
    void SetChainMarker();


//SS fuer DrawObjekte ---------------------

    //Temporaer um Bug zu umgehen.

    //Achtung: Uneindeutikeiten bei Mehrfachselektionen.



    //Setzen vom DragMode (z.B. Rotate), tut nix bei Rahmenselektion.

    USHORT IsObjSelected() const;   //Liefert gleich die Anzahl der Objekte,
                                    //zaehlt aber nicht die Objekte in Gruppen.
#ifdef ACCESSIBLE_LAYOUT
#endif


    //Ankertyp des selektierten Objektes, -1 bei Uneindeutigkeit oder
    //Rahmenselektion; FLY_PAGE bzw. FLY_AT_CNTNT aus frmatr.hxx sonst.

    //Erzeugen von DrawObjekten, beim Begin wird der Objekttyp mitgegeben.
    //Beim End kann ein Cmd mitgegeben werden, hier ist ggf.
    //SDRCREATE_RESTRAINTEND fuer Ende oder SDRCREATE_NEXTPOINT fuer ein
    //Polygon relevant. Nach dem RESTRAINTEND ist das Objekt erzeugt und
    //selektiert.
    //Mit BreakCreate wird der Vorgang abgebrochen, dann ist kein Objekt
    //mehr selektiert.

    // Funktionen fÅr Rubberbox, um Draw-Objekte zu selektieren

    //Gruppe erzeugen, aufloesen, nix bei Rahmenselektion.
                                //Es koennen noch immer Gruppen dabei sein.

// OD 27.06.2003 #108784# - change return type.


    //Umankern. erlaubt sind: FLY_PAGE und FLY_AT_CNTNT des enum RndStdIds aus
    //frmatr.hxx. Hier kein enum wg. Abhaengigkeiten
    //Der BOOL ist nur fuer internen Gebrauch! Anker wird nur - anhand der
    //aktuellen Dokumentposition - neu gesetzt aber nicht umgesetzt.

    // hole die selectierten DrawObj als Grafik (MetaFile/Bitmap)
    // Return-Wert besagt ob konvertiert wurde!!



        //Einfuegen eines DrawObjectes. Das Object muss bereits im DrawModel
        // angemeldet sein.


//------------------------------------------

    //Auskunft ueber naechstliegenden Inhalt zum uebergebenen Point

    //convert document position into position relative to the current page
    Point GetRelativePagePosition(const Point& rDocPos);

    //Layout-Selektion Hiden/Zeigen und aufruf an die CrsrSh weiterreichen.
    void ShGetFcs( BOOL bUpdate = TRUE );

    //PageDescriptor-Schnittstelle
    USHORT GetCurPageDesc( const BOOL bCalcFrm = TRUE ) const;
    USHORT GetMousePageDesc( const Point &rPt ) const;
    USHORT GetPageDescCnt() const;

    const SwPageDesc& GetPageDesc( USHORT i ) const;
    // if inside all selection only one PageDesc, return this.
    // Otherwise return 0 pointer

    const SwRect& GetAnyCurRect( CurRectType eType,
                                 const Point* pPt = 0,
                                 const SvEmbeddedObject *pObj = 0 ) const;

    //Seitennummer der Seite in der der Point liegt, 0 wenn keine
    //getroffen ist.
    BOOL GetPageNumber( long nYPos, BOOL bAtCrsrPos, USHORT& rPhyNum, USHORT& rVirtNum, String &rDisplay ) const;



    BOOL    FinishOLEObj();                             // Server wird beendet

    //Attribute der Tabelle besorgen/setzen.

    //Tabelle vollstaendig selektiert?
    //Ist der Inhalt einer Tabellenzelle oder mindestens eine Tabellenzelle
    //vollstaendig selektiert ist



                                //Fehler ueber enum zurueck
    // Zelle Vertikal oder Horizontal splitten.

    //Der Pointer muss vom Aufrufer zerstoert werden wenn != 0

    USHORT GetBoxAlign() const;         //USHRT_MAX fuer uneindeutig!

    //Ausgleichen der Zeilenhoehen. Mit bTstOnly festellen ob mehr als eine
    //Zeile markiert ist.
    BOOL BalanceRowHeight( BOOL bTstOnly );

    void GetTabBorders(       SfxItemSet& rSet) const;





                            // nichtet, wenn der Cursor nicht in Readonly darf

    BOOL IsInRepeatedHeadline() const;

    //Stellt die Breiten der Zellen so ein, dass der Inhalt moeglichst
    //nicht umgebrochen werden muss.
    //bBalance sorgt fuer einen Ausgleich der markierten Spalten.
    //Nicht erlaubt, wenn nur  leere Zellen selektiert sind.
    BOOL IsAdjustCellWidthAllowed( BOOL bBalance = FALSE ) const;

    //Ausgleich der Zellenbreiten, mit bTstOnly feststellen, ob mehr als
    //eine Zelle markiert ist.
    BOOL BalanceCellWidth( BOOL bTstOnly );

        // AutoFormat fuer die Tabelle/TabellenSelection
        // Erfrage wie attributiert ist
        // aender eine  Zellenbreite/-Hoehe/Spaltenbreite/Zeilenhoehe
        // Autosumme

    //Phy:  Tatsaechliche Seitenanzahl.
    //Virt: Vom User evtl. gesetzten Offset mit einbeziehen.

    // Setzt an der aktuellen Postion einen neuen Page Offset

    //SS fuer Beschriftungen

    //Das Lineal will auch noch etwas von uns wissen.
    USHORT GetCurColNum( SwGetCurColNumPara* pPara = 0 ) const; //0 == in keiner Spalte
    BOOL IsTableRightToLeft()const;
    BOOL IsLastCellInRow() const;
    BOOL IsMouseTableRightToLeft(const Point &rPt) const;
    // Die Breite des aktuellen Bereichs fuer Spaltendialog

    void GetConnectableFrmFmts
    (SwFrmFmt & rFmt, const String & rReference, BOOL bSuccessors,
     ::std::vector< String > & aPrevPageVec,
     ::std::vector< String > & aThisPageVec,
     ::std::vector< String > & aNextPageVec,
     ::std::vector< String > & aRestVec);

    /** SwFEShell::GetShapeBackgrd

        OD 02.09.2002 for #102450#:
        method determines background color of the page the selected drawing
        object is on and returns this color.
        If no color is found, because no drawing object is selected or ...,
        color COL_BLACK (default color on constructing object of class Color)
        is returned.

        @author OD

        @returns an object of class Color
    */
    const Color GetShapeBackgrd() const;

    /** Is default horizontal text direction for selected drawing object right-to-left

        OD 09.12.2002 #103045#
        Because drawing objects only painted for each page only, the default
        horizontal text direction of a drawing object is given by the corresponding
        page property.

        @author OD

        @returns boolean, indicating, if the horizontal text direction of the
        page, the selected drawing object is on, is right-to-left.
    */
    const bool IsShapeDefaultHoriTextDirR2L() const;

    void ParkCursorInTab();
};

} //namespace binfilter
#endif
