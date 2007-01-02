/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: editsh.hxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: hr $ $Date: 2007-01-02 18:43:17 $
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
class SvInPlaceObjectRef;
class SvInPlaceObject;
class Font;
namespace binfilter {
class BfGraphicObject; // fuer GetGraphicObj


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


    //check whether DB fields point to an available data source and returns it
    BOOL IsFieldDataSourceAvailable(String& rUsedDataSource) const;


    // Dokument - Statistics

    // Dokument - Info

    // Verzeichnismarke einfuegen loeschen


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

    /* Anwenden der ViewOptions mit Start-/EndAction */
    inline void ApplyViewOptions( const SwViewOption &rOpt );


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

    // special insert: Insert a new text node just before or after a section or
    // table, if the cursor is positioned at the start/end of said
    // section/table. The purpose of the method is to allow users to inert text
    // at certain 'impossible' position, e.g. before a table at the document
    // start or between to sections.
    bool DoSpecialInsert();
    bool CanSpecialInsert() const;

    // Optimierung UI

    inline const SvxLinkManager& GetLinkManager() const;

    // Numberformatter vom Doc erfragen
    const SvNumberFormatter* GetNumberFormatter() const
    {   return ((SwEditShell*)this)->GetNumberFormatter();  }


    // ctor/dtor
    SwEditShell( SwDoc&, Window*,
                 SwRootFrm* = 0, const SwViewOption *pOpt = 0 );
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
