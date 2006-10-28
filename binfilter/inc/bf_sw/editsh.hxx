/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: editsh.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 04:40:20 $
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
#ifndef _EDITSH_HXX
#define _EDITSH_HXX

#ifndef _STRING_HXX //autogen
#include <tools/string.hxx>
#endif
#ifndef _SVARRAY_HXX //autogen
#include <svtools/svarray.hxx>
#endif
#ifndef _SV_FONT_HXX //autogen
#include <vcl/font.hxx>
#endif
#ifndef _SVXSWAFOPT_HXX
#include <bf_svx/swafopt.hxx>
#endif
#ifndef _CRSRSH_HXX
#include <crsrsh.hxx>   // fuer Basisklasse
#endif
#ifndef _ITABENUM_HXX
#include <itabenum.hxx>
#endif
#ifndef _SWDBDATA_HXX
#include <swdbdata.hxx>
#endif
#ifndef _COM_SUN_STAR_LINGUISTIC2_XSPELLALTERNATIVES_HPP_
#include <com/sun/star/linguistic2/XSpellAlternatives.hpp>
#endif
namespace com { namespace sun { namespace star { namespace uno {
    template < class > class Sequence;
}}}};
class PolyPolygon;
class DateTime;
class CommandExtTextInputData;

class SvNumberFormatter;
class SfxPoolItem;
class SfxItemSet;
class SvStringsDtor;
class Graphic;          // fuer GetGraphic
class GraphicObject; // fuer GetGraphicObj
class SvInPlaceObjectRef;
class SvInPlaceObject;
class Font;
namespace binfilter {


class SwDoc;
class SvxLinkManager;
class SvxAutoCorrect;

class SwField;          // fuer Felder
class SwFieldType;
class SwDDEFieldType;
class SwNewDBMgr;

struct SwDocStat;
class SfxDocumentInfo;

class SvStringsSort;
class SwAutoCompleteWord;

class SwFmtRefMark;
class SwFmtCol;
class SwNumRule;        // Numerierung
class SwNodeNum;        // Numerierung
class SwUndoIds;        // fuer Undo
class SwTxtFmtColl;
#ifdef USED
class SwGrfFmt;
class SwGrfFmtColl;
#endif
class SwGrfNode;
class SwFlyFrmFmt;

class SwFrmFmt;         // fuer GetTxtNodeFmts()
class SwCharFmt;
class SwExtTextInput;
class SwTxtNode;        // fuer IsNotMakeTxtNode
class SwRootFrm;        // fuer CTOR
class SwFmtINetFmt;     // InsertURL

class SwTable;
class SwTextBlocks;     // fuer GlossaryRW
class SwBlockExceptList;
class SwFmtFtn;
class SpellCheck;
class SwSection;
class SwSectionFmt;
class SwTOXMarks;
class SwTOXBase;
class SwTOXType;
class SwTableAutoFmt;
class SwPageDesc;
class SchMemChart;

class SwTxtINetFmt;
class SwSeqFldList;
class SwGlblDocContent;
class SwGlblDocContents;
class SwRedline;
class SwRedlineData;
class SwFtnInfo;
class SwEndNoteInfo;
class SwLineNumberInfo;
class SwAttrSet;
class SwAuthEntry;

//STRIP008 namespace com { namespace sun { namespace star { namespace uno {
//STRIP008  template < class > class Sequence;
//STRIP008 }}}};


// Flags for GetScriptType - to define how handle weak - scripts (b.e.
// symbol characters):
// GETSCRIPT_WEAKTOAPPLANGSCRIPT:
//      app language define the script type if only weak characters
//      are selected and before the weak script no weak script if found
//      (mostly the default for Get any attributes, etc)
// GETSCRIPT_WEAKTOAPPLANGSCRIPT:
//      app language defines the script type if only weak characters
//      are selected and before the weak script no weak script is found
//      (mostly the default for Get any attributes, etc)
// GETSCRIPT_WEAKTOALL:
//      all script flags are set.
//      are selected and before the weak script no weak script if found
//      (mostly the default for Get any attributes, etc)
#define GETSCRIPT_WEAKTOAPPLANGSCRIPT   0
#define GETSCRIPT_WEAKTOALL             1


#define GETSELTXT_PARABRK_TO_BLANK      0
#define GETSELTXT_PARABRK_KEEP          1
#define GETSELTXT_PARABRK_TO_ONLYCR     2

/****************************************************************
 *  zum Abfragen der INet-Attribute fuer den Navigator
 ****************************************************************/
struct SwGetINetAttr
{
    String sText;
    const SwTxtINetFmt& rINetAttr;

    SwGetINetAttr( const String& rTxt, const SwTxtINetFmt& rAttr )
        : sText( rTxt ), rINetAttr( rAttr )
    {}
};
SV_DECL_PTRARR_DEL( SwGetINetAttrs, SwGetINetAttr*, 0, 5 )

/****************************************************************
 *  Typen der Inhaltsformen
 ****************************************************************/
#define CNT_TXT 0x0001
#define CNT_GRF 0x0002
#define CNT_OLE 0x0010
/* Teste einen USHORT auf eine bestimmte Inhaltsform */
#define CNT_HasTxt(USH) ((USH)&CNT_TXT)
#define CNT_HasGrf(USH) ((USH)&CNT_GRF)
#define CNT_HasOLE(USH) ((USH)&CNT_OLE)

class SwEditShell: public SwCrsrShell
{
    static SvxSwAutoFmtFlags* pAutoFmtFlags;

    // fuer die privaten Methoden DelRange und die vom AutoCorrect
    friend void _InitCore();
    friend void _FinitCore();
    // fuer die PamCorrAbs/-Rel Methoden
    friend class SwUndo;

    SfxPoolItem& _GetChrFmt( SfxPoolItem& ) const;

    /*
     * liefert einen Pointer auf einen SwGrfNode; dieser wird von
     * GetGraphic() und GetGraphicSize() verwendet.
     */



public:
    // Editieren (immer auf allen selektierten Bereichen)

    // Ersetz einen selektierten Bereich in einem TextNode mit dem
    // String. Ist fuers Suchen&Ersetzen gedacht.
    // bRegExpRplc - ersetze Tabs (\\t) und setze den gefundenen String
    //               ein ( nicht \& )
    //              z.B.: Fnd: "zzz", Repl: "xx\t\\t..&..\&"
    //                      --> "xx\t<Tab>..zzz..&"

    // loescht den Inhalt aller Bereiche;
    // werden ganze Nodes selektiert, werden die Nodes geloescht

    // remove a complete paragraph

    // change text to Upper/Lower/Hiragana/Katagana/...

    // loesche den nicht sichtbaren Content aus dem Document, wie z.B.:
    // versteckte Bereiche, versteckte Absaetze

    // embedded alle lokalen Links (Bereiche/Grafiken)

    // verschiebe den Inhalt aller Bereiche an die akt. Cursor-Position

    // kopiere den Inhalt aller Bereiche an die akt. Cursor-Position
    // in die angegebene Shell

    // fuers Kopieren uebers ClipBoard:
    //  wird Tabelle in Tabelle kopiert, verschiebe aus dieser dann
    //  alle Cursor. Copy und Paste muss aufgrund der FlyFrames in
    //  der FEShell stehen!
    // kopiere alle Selectionen und das Doc
    //JP 21.10.96: und fuer die SVX-Autokorrektur


    // ist der Cursor in einem INetAttribut, dann wird das komplett
    // geloescht; inclusive des Hinweistextes (wird beim Drag&Drop gebraucht)

    // ist der Cursor am Ende einer Zeichenvorlage, an der das DontExpand-Flag
    // noch nicht gesetzt ist, wird dies gesetzt ( => return TRUE; )

    // Anwenden / Entfernen von Attributen
    // liefert Attribute im angeforderten AttributSet. Wenn nicht eindeutig
    // steht im Set ein DONT_CARE !!
    BOOL GetAttr( SfxItemSet& ) const;

    // Setze das Attribut als neues default Attribut im Dokument.

    // Erfrage das Default Attribut vom Dokument.
    const SfxPoolItem& GetDefault( USHORT nFmtHint ) const;


    // returns the scripttpye of the selection
    USHORT GetScriptType( USHORT nFlags = GETSCRIPT_WEAKTOAPPLANGSCRIPT ) const;

    // returns the language at current cursor position
    USHORT GetCurLang() const;

    // FrameFormate

    // TABLE

    // CHAR
    SwCharFmt* GetCurCharFmt() const;


    /* Formatcollections, neu */
    /* GetXXXCount() liefert die Anzahl der im Dokument vorhandenen XXX
     * GetXXX(i)     liefert das i-te XXX (ERR_RAISE bei Ueberindizierung!)
     * DelXXX(i)     loescht das i-te XXX (ERR_RAISE bei Ueberindizierung!)
     * GetCurXXX()   liefert das am Cursor oder in den Bereichen
     *               geltende XXX (0, wenn nicht eindeutig!)
     * SetXXX()      setzt am Cursor oder in den Bereichen das XXX
     * MakeXXX()     macht ein XXX, abgeleitet vom pDerivedFrom
     */

    // TXT
    SwTxtFmtColl* GetCurTxtFmtColl() const;
#ifdef USED
    // GRF
    USHORT GetGrfFmtCollCount() const;
    SwGrfFmtColl& GetGrfFmtColl( USHORT nGrfFmtColl) const;
    void DelGrfFmtColl(USHORT nFmt);
    SwGrfFmtColl* GetCurGrfFmtColl() const;
    void SetGrfFmtColl(SwGrfFmtColl*);
    SwGrfFmtColl *MakeGrfFmtColl(const String &rFmtCollName,
        SwGrfFmtColl *pDerivedFrom = 0);
#endif

        // Gebe die "Auto-Collection" mit der Id zurueck. Existiert
        // sie noch nicht, dann erzuege sie
        // return das geforderte automatische  Format - Basis-Klasse !
        // returne die geforderte automatische Seiten-Vorlage
        // returne die geforderte automatische NumRule

    // erfrage ob die Absatz-/Zeichen-/Rahmen-/Seiten - Vorlage benutzt wird

        // returne das geforderte automatische Format

    // Felder
    void Insert(SwField&);
    SwField* GetCurFld() const;






    // Datenbankinfo
    const SwDBData& GetDBDesc() const;

    //check whether DB fields point to an available data source and returns it
    BOOL IsFieldDataSourceAvailable(String& rUsedDataSource) const;


    // fuer die Evaluierung der DBFelder (neuer DB-Manager)
    SwNewDBMgr* GetNewDBMgr() const;


    // Aenderungen am Dokument?
    void ResetModified();

    // Dokument - Statistics

    // Dokument - Info

    // Verzeichnismarke einfuegen loeschen

    // Alle Markierungen am aktuellen SPoint ermitteln
    USHORT  GetCurTOXMarks(SwTOXMarks& rMarks) const ;

    // Verzeichnis einfuegen, und bei Bedarf erneuern
    const SwTOXBase*    GetCurTOX() const;





    // nach einlesen einer Datei alle Verzeichnisse updaten

    // Verzeichnis-Typen verwalten

    //AutoMark file

    // Schluessel fuer die Indexverwaltung

    // Gliederung - hoch-/runterstufen
    // Gliederung - hoch-/runtermoven
    // Outlines and SubOutline are protected ?

    // Numerierung Aufzaehlunglisten
    // liefert Regelwerk der aktuellen Aufzaehlung (FALSE sonst)
    const SwNumRule* GetCurNumRule() const;
    // setzt, wenn noch keine Numerierung, sonst wird geaendert
    // arbeitet mit alten und neuen Regeln, nur Differenzen aktualisieren
    // Absaetze ohne Numerierung, aber mit Einzuegen
    // Loeschen, Splitten der Aufzaehlungsliste
    // Hoch-/Runterstufen
    // Hoch-/Runtermoven sowohl innerhalb als auch ausserhalb von Numerierungen
    // No-/Numerierung ueber Delete/Backspace ein/abschalten
    // returne den Num-Level des Nodes, in dem sich der Point vom
    // Cursor befindet. Return kann sein :
    // - NO_NUMBERING, 0..MAXLEVEL-1, NO_NUMLEVEL .. NO_NUMLEVEL|MAXLEVEL-1
    BYTE GetNumLevel( BOOL* pHasChilds = 0 ) const;
    // detect highest and lowest level to check moving of outline levels

    // setze und erfrage, ob an aktueller PointPos eine Numerierung mit
    // dem StartFlag startet

    // Undo
    // UndoHistory am Dokument pflegen
    // bei Save, SaveAs, Create wird UndoHistory zurueckgesetzt ???
    void DoUndo( BOOL bOn = TRUE );

    // macht rueckgaengig:
    // setzt Undoklammerung auf, liefert nUndoId der Klammerung
    USHORT StartUndo( USHORT nUndoId = 0 );
    // schliesst Klammerung der nUndoId, nicht vom UI benutzt
    USHORT EndUndo( USHORT nUndoId = 0 );
    // liefert die Id der letzten undofaehigen Aktion zurueck
    // fuellt ggf. VARARR mit User-UndoIds
    USHORT GetUndoIds( String* pUndoStr = 0, SwUndoIds *pUndoIds = 0) const;

        // abfragen/setzen der Anzahl von wiederherstellbaren Undo-Actions
    static USHORT GetUndoActionCount();
    static void SetUndoActionCount( USHORT nNew );

    // Redo
    // liefert die Id der letzten Redofaehigen Aktion zurueck
    // fuellt ggf. VARARR mit RedoIds
    USHORT GetRedoIds( String* pRedoStr = 0, SwUndoIds *pRedoIds = 0) const;

    // Repeat
    // liefert die Id der letzten Repeatfaehigen Aktion zurueck
    // fuellt ggf. VARARR mit RedoIds

    // 0 letzte Aktion, sonst Aktionen bis zum Start der Klammerung nUndoId
    // mit KillPaMs, ClearMark
    // wiederholt
    // wiederholt
#ifdef USED
    // Aktionen klammern
#endif
    // fuer alle Sichten auf dieses Dokument
    void StartAllAction();
    void EndAllAction();

    //Damit Start-/EndActions aufgesetzt werden koennen.
    void CalcLayout();

    // Inhaltsform bestimmen, holen, liefert Type am CurCrsr->SPoint
    USHORT GetCntType() const;

    /* Anwenden der ViewOptions mit Start-/EndAction */
    inline void ApplyViewOptions( const SwViewOption &rOpt );

    // Text innerhalb der Selektion erfragen
    // Returnwert liefert FALSE, wenn der selektierte Bereich
    // zu gross ist, um in den Stringpuffer kopiert zu werden
    // oder andere Fehler auftreten

    /*
     * liefert eine Graphic, wenn CurCrsr->Point() auf einen
     * SwGrfNode zeigt (und Mark nicht gesetzt ist oder auf die
     * gleiche Graphic zeigt), sonst gibt's was auf die Finger
     */


    // If there's an automatic, not manipulated polygon at the selected
    // notxtnode, it has to be deleted, e.g. cause the object has changed.

    /*
     * liefert die Groesse einer Graphic in Twips, wenn der Cursor
     * auf einer Graphic steht; BOOL liefert FALSE, wenn s.o.
     */
    /*
     * liefert den Namen und den Filter einer Graphic, wenn der Cursor
     * auf einer Graphic steht, sonst gibt's was auf die Finger!
     * Ist ein String-Ptr != 0 dann returne den entsp. Namen
     */
    /*
     * erneutes Einlesen, falls Graphic nicht Ok ist. Die
     * aktuelle wird durch die neue ersetzt.
     */

    // alternativen Text einer Grafik/OLe-Objectes abfragen/setzen

    //eindeutige Identifikation des Objektes (fuer ImageMapDlg)

    //liefert ein ClientObject, wenn CurCrsr->Point() auf einen
    //SwOLENode zeigt (und Mark nicht gesetzt ist oder auf das
    //gleiche ClientObject zeigt), sonst gibt's was auf die
    //Finger.
    //Gibt es ein OleObject mit diesem Namen (SwFmt)?

    //Liefert den Pointer auf die Daten des Chart, indem sich der Crsr
    //befindet.
    // returne den ChartNamen - vom Crsr oder vom uebergebenen OLE-Object
    // reurnt aEmptyStr wenn nicht gefunden wurde
    //Sucht die Tabelle und liefert ein mit den Daten der Tabelle gefuelltes
    //pData. Wenn pData 0 ist wird eines angelegt.
    //Updaten der Inhalte aller Charts zu der Tabelle mit dem angegeben Namen

    //  aktuelles Wort erfragen

    // Textbaustein aus dem Textbausteindokument in
    // das aktuelle Dokument, Vorlagen nur wenn es nicht schon gibt
    // aktuelle Selektion zum Textbaustein machen und ins
    // Textbausteindokument einfuegen, einschliesslich Vorlagen
    // speicher den gesamten Inhalt des Docs als Textbaustein

    // Linguistik
    // Selektionen sichern
    // Selektionen wiederherstellen
    // zu trennendes Wort ignorieren

    // zum Einfuegen des SoftHyphens, Position ist der Offset
    // innerhalb des getrennten Wortes.

    //Tabelle
    void UpdateTable();

    SwFrmFmt *GetTableFmt();



    // Change Modus erfragen/setzen
    USHORT GetTblChgMode() const;

    // Zellenbreiten ueber Min/Max Berechnung an Tabellenbreite anpassen
    // Tabelle an der Cursor Position aufsplitten
    // Tabellen verbinden
    // CanMerge kann feststellen, ob Prev oder Next moeglich ist. Wird
    // der Pointer pChkNxtPrv uebergeben, wird festgestellt in welche
    // Richtung es moeglich ist.
        // setze das InsertDB als Tabelle Undo auf:

    /*
        functions used for spell checking and text conversion
    */

    // Selektionen sichern
    // Selektionen wiederherstellen

    // Is spelling active somewhere else?
    // Is text conversion active somewhere else?
    BOOL HasConvIter() const;
    // Is hyphenation active somewhere else?



    // returne zum Namen die im Doc gesetzte Referenz
    // returne die Namen aller im Doc gesetzten Referenzen
    //  Ist der ArrayPointer 0 dann returne nur, ob im Doc. eine RefMark
    //  gesetzt ist

    // rufe die Autokorrektur auf

    // dann setze nach entsprechenden Regeln unsere Vorlagen

    static SvxSwAutoFmtFlags* GetAutoFmtFlags();
    static void SetAutoFmtFlags(SvxSwAutoFmtFlags *);

    // errechnet die Selektion


    //SS Fuer holen/ersetzen DropCap-Inhalt

    // Abfrage von Oultine Informationen:

    // mit exp. Felder und KapitelNummern
    // die Nummer

    // may an outline be moved or copied?
    // Check whether it's in text body, not in table, and not read-only (move)


    // erfrage und setze den Fussnoten-Text/Nummer. Set.. auf akt. SSelection!
//z.Zt nicht benoetigt  USHORT GetFtnCnt( BOOL bEndNotes = FALSE ) const;
        // gebe Liste aller Fussnoten und deren Anfangstexte

    // SS fuer Bereiche
    const SwSection* GetCurrSection() const;
    // liefert wie GetCurrSection() den aktuellen Bereich, allerdings geht diese Funktion
    // ueber die Frames und erwischt dabei auch den Bereich, wenn der Cursor in einer
    // Fussnote steht, deren Referenz in einem spaltigen Bereich steckt.
    // Wenn man bOutOfTab setzt, wird der Bereich gesucht,
    // der die Tabelle umfasst, nicht etwa ein innerer.

    BOOL IsAnySectionInDoc( BOOL bChkReadOnly = FALSE,
                            BOOL bChkHidden = FALSE,
                            BOOL BChkTOX = FALSE ) const;
        // Passwort fuer geschuetzte Bereiche erfragen/setzen


    //Attribute setzen

    // search inside the cursor selection for full selected sections.
    // if any part of section in the selection return 0.
    // if more than one in the selection return the count

    // special insert: Insert a new text node just before or after a section or
    // table, if the cursor is positioned at the start/end of said
    // section/table. The purpose of the method is to allow users to inert text
    // at certain 'impossible' position, e.g. before a table at the document
    // start or between to sections.
    bool DoSpecialInsert();
    bool CanSpecialInsert() const;

    // Optimierung UI

    inline const SvxLinkManager& GetLinkManager() const;

    // linken Rand ueber Objectleiste einstellen (aenhlich dem Stufen von
    // Numerierungen), optional kann man "um" den Offset stufen oder "auf"
    // die Position gestuft werden (bModulus = TRUE)
    BOOL IsMoveLeftMargin( BOOL bRight = TRUE, BOOL bModulus = TRUE ) const;

    // Numberformatter vom Doc erfragen
    const SvNumberFormatter* GetNumberFormatter() const
    {   return ((SwEditShell*)this)->GetNumberFormatter();  }

    // Extrakt fuellen

    // Schnitstellen fuers GlobalDokument
    // erzeuge Anhand der vorgebenen Collection Teildokumente
    // falls keine angegeben ist, nehme die Kapitelvorlage der 1. Ebene

    // alles fuers Redlining
    BOOL IsRedlineOn() const;
    // suche das Redline zu diesem Data und returne die Pos im Array
    // USHRT_MAX wird returnt, falls nicht vorhanden

    // Kommentar am Redline an der Position setzen

    // Redline Anzeigeattribute wurden geaendert, Views updaten

    //  vergleiche zwei Dokument mit einander
    // merge zweier Dokumente

    // Dokumentglobale Fussnoteneigenschaften

    //Einstellungen fuer Zeilennummierung

    // Etiketten: Bereiche synchronisieren
    BOOL IsLabelDoc() const;

    // Schnittstelle fuer die TextInputDaten - ( fuer die Texteingabe
    // von japanischen/chinesischen Zeichen)
//  SwExtTextInput* GetExtTextInput() const;

    // Schnistelle fuer den Zugriff auf die AutoComplete-Liste

    // returns a scaling factor of selected text. Used for the rotated
    // character attribut dialog.

    // ctor/dtor
    SwEditShell( SwDoc&, Window*,
                 SwRootFrm* = 0, const SwViewOption *pOpt = 0 );
    // verkleideter Copy-Constructor
     SwEditShell( SwEditShell&, Window* );
    virtual ~SwEditShell();

private:
    // fuer METWARE:
    // es wird nicht kopiert und nicht zugewiesen
    SwEditShell(const SwEditShell &);
    const SwEditShell &operator=(const SwEditShell &);
};

inline void SwEditShell::ApplyViewOptions( const SwViewOption &rOpt )
{
    SwCrsrShell::StartAction();
    ViewShell::ApplyViewOptions( rOpt );
    SwEditShell::EndAction();
}

inline const SvxLinkManager& SwEditShell::GetLinkManager() const
{   return ((SwEditShell*)this)->GetLinkManager();  }

/*
 * Klasse fuer den automatisierten Aufruf von Start- und
 * EndAction();
 */


/*
 * Klasse fuer den automatisierten Aufruf von Start- und
 * EndCrsrMove();
 */
class SwMvKontext {
    SwEditShell *pSh;
public:
    SwMvKontext(SwEditShell *pShell );
    ~SwMvKontext();
};

#define MV_KONTEXT(x)   SwMvKontext _aMvKontext_(x)



} //namespace binfilter
#endif
