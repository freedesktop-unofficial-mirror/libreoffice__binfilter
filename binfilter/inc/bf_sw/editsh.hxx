/*************************************************************************
 *
 *  $RCSfile: editsh.hxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:23:52 $
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

class PolyPolygon;
class SwDoc;
class DateTime;
class CommandExtTextInputData;

class SvNumberFormatter;
class SfxPoolItem;
class SfxItemSet;
class SvxLinkManager;
class SvxAutoCorrect;

class SwField;          // fuer Felder
class SwFieldType;
class SwDDEFieldType;
class SwNewDBMgr;

struct SwDocStat;
class SfxDocumentInfo;
class SvStringsDtor;
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
class Graphic;          // fuer GetGraphic
class GraphicObject;    // fuer GetGraphicObj
class SwFmtINetFmt;     // InsertURL
class SvInPlaceObjectRef;
class SvInPlaceObject;
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
class Font;
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

namespace com { namespace sun { namespace star { namespace uno {
    template < class > class Sequence;
}}}};


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
//STRIP001  friend class SwAutoFormat;
    friend void _InitCore();
    friend void _FinitCore();
    // fuer die PamCorrAbs/-Rel Methoden
    friend class SwUndo;

    SfxPoolItem& _GetChrFmt( SfxPoolItem& ) const;

    /*
     * liefert einen Pointer auf einen SwGrfNode; dieser wird von
     * GetGraphic() und GetGraphicSize() verwendet.
     */
//STRIP001  SwGrfNode *_GetGrfNode() const ;

//STRIP001  void DeleteSel( SwPaM& rPam, BOOL* pUndo = 0 );

//STRIP001  void _SetSectionAttr( SwSectionFmt& rSectFmt, const SfxItemSet& rSet );

public:
    // Editieren (immer auf allen selektierten Bereichen)
//STRIP001  void Insert( sal_Unicode, BOOL bOnlyCurrCrsr = FALSE );
//STRIP001  void Insert( const String &);
//STRIP001  void Overwrite( const String & );

    // Ersetz einen selektierten Bereich in einem TextNode mit dem
    // String. Ist fuers Suchen&Ersetzen gedacht.
    // bRegExpRplc - ersetze Tabs (\\t) und setze den gefundenen String
    //               ein ( nicht \& )
    //              z.B.: Fnd: "zzz", Repl: "xx\t\\t..&..\&"
    //                      --> "xx\t<Tab>..zzz..&"
//STRIP001  BOOL Replace( const String& rNewStr, BOOL bRegExpRplc = FALSE );

    // loescht den Inhalt aller Bereiche;
    // werden ganze Nodes selektiert, werden die Nodes geloescht
//STRIP001  long Delete();

    // remove a complete paragraph
//STRIP001  BOOL DelFullPara();

    // change text to Upper/Lower/Hiragana/Katagana/...
//STRIP001  void TransliterateText( sal_uInt32 nType );

    // loesche den nicht sichtbaren Content aus dem Document, wie z.B.:
    // versteckte Bereiche, versteckte Absaetze
//STRIP001  BOOL RemoveInvisibleContent();

    // embedded alle lokalen Links (Bereiche/Grafiken)
//STRIP001  BOOL EmbedAllLinks();
//STRIP001  USHORT GetLinkUpdMode(BOOL bDocSettings = FALSE) const;
//STRIP001  void SetLinkUpdMode( USHORT nMode );

    // verschiebe den Inhalt aller Bereiche an die akt. Cursor-Position
//STRIP001  long Move();

    // kopiere den Inhalt aller Bereiche an die akt. Cursor-Position
    // in die angegebene Shell
//STRIP001  long Copy( SwEditShell* pDestShell = 0 );

    // fuers Kopieren uebers ClipBoard:
    //  wird Tabelle in Tabelle kopiert, verschiebe aus dieser dann
    //  alle Cursor. Copy und Paste muss aufgrund der FlyFrames in
    //  der FEShell stehen!
    // kopiere alle Selectionen und das Doc
    //JP 21.10.96: und fuer die SVX-Autokorrektur
//STRIP001  BOOL _CopySelToDoc( SwDoc* pInsDoc, SwNodeIndex* pNdInsPos = 0 );

//STRIP001  long SplitNode( BOOL bAutoFormat = FALSE, BOOL bCheckTableStart = TRUE );
//STRIP001  void AutoFmtBySplitNode();

    // ist der Cursor in einem INetAttribut, dann wird das komplett
    // geloescht; inclusive des Hinweistextes (wird beim Drag&Drop gebraucht)
//STRIP001  BOOL DelINetAttrWithText();

    // ist der Cursor am Ende einer Zeichenvorlage, an der das DontExpand-Flag
    // noch nicht gesetzt ist, wird dies gesetzt ( => return TRUE; )
//STRIP001  BOOL DontExpandFmt();

    // Anwenden / Entfernen von Attributen
    // liefert Attribute im angeforderten AttributSet. Wenn nicht eindeutig
    // steht im Set ein DONT_CARE !!
    BOOL GetAttr( SfxItemSet& ) const;
//STRIP001  void SetAttr( const SfxPoolItem&, USHORT nFlags = 0 );
//STRIP001  void SetAttr( const SfxItemSet&, USHORT nFlags = 0 );

    // Setze das Attribut als neues default Attribut im Dokument.
//STRIP001  void SetDefault( const SfxPoolItem& );

    // Erfrage das Default Attribut vom Dokument.
    const SfxPoolItem& GetDefault( USHORT nFmtHint ) const;

//STRIP001  void ResetAttr();
//STRIP001  void GCAttr();

    // returns the scripttpye of the selection
    USHORT GetScriptType( USHORT nFlags = GETSCRIPT_WEAKTOAPPLANGSCRIPT ) const;

    // returns the language at current cursor position
    USHORT GetCurLang() const;

    // FrameFormate
//STRIP001  SwFrmFmt* FindFrmFmtByName( const String& rName ) const;

    // TABLE
//STRIP001  USHORT GetTblFrmFmtCount( BOOL bUsed = FALSE ) const;
//STRIP001  SwFrmFmt& GetTblFrmFmt(USHORT nFmt, BOOL bUsed = FALSE ) const;
//STRIP001  String GetUniqueTblName() const;

    // CHAR
//STRIP001  USHORT GetCharFmtCount() const;
//STRIP001  SwCharFmt& GetCharFmt(USHORT nFmt) const;
    SwCharFmt* GetCurCharFmt() const;
//STRIP001  void FillByEx(SwCharFmt*, BOOL bReset = FALSE);
//STRIP001  SwCharFmt* MakeCharFmt( const String& rName, SwCharFmt* pDerivedFrom = 0 );
//STRIP001  SwCharFmt* FindCharFmtByName( const String& rName ) const;


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
//STRIP001  SwTxtFmtColl& GetDfltTxtFmtColl() const;
//STRIP001  USHORT GetTxtFmtCollCount() const;
//STRIP001  SwTxtFmtColl& GetTxtFmtColl( USHORT nTxtFmtColl) const;
    SwTxtFmtColl* GetCurTxtFmtColl() const;
//STRIP001  void SetTxtFmtColl(SwTxtFmtColl*);
//STRIP001  SwTxtFmtColl *MakeTxtFmtColl(const String &rFmtCollName,
//STRIP001      SwTxtFmtColl *pDerivedFrom = 0);
//STRIP001  void FillByEx(SwTxtFmtColl*, BOOL bReset = FALSE);
//STRIP001  SwTxtFmtColl* FindTxtFmtCollByName( const String& rName ) const;
#ifdef USED
    // GRF
    USHORT GetGrfFmtCollCount() const;
    SwGrfFmtColl& GetGrfFmtColl( USHORT nGrfFmtColl) const;
    void DelGrfFmtColl(USHORT nFmt);
    SwGrfFmtColl* GetCurGrfFmtColl() const;
    void SetGrfFmtColl(SwGrfFmtColl*);
    SwGrfFmtColl *MakeGrfFmtColl(const String &rFmtCollName,
        SwGrfFmtColl *pDerivedFrom = 0);
//STRIP001  SwGrfFmtColl* FindGrfFmtCollByName( const String& rName ) const;
#endif

        // Gebe die "Auto-Collection" mit der Id zurueck. Existiert
        // sie noch nicht, dann erzuege sie
//STRIP001  SwTxtFmtColl* GetTxtCollFromPool( USHORT nId );
        // return das geforderte automatische  Format - Basis-Klasse !
//STRIP001  SwFmt* GetFmtFromPool( USHORT nId );
        // returne die geforderte automatische Seiten-Vorlage
//STRIP001  SwPageDesc* GetPageDescFromPool( USHORT nId );
        // returne die geforderte automatische NumRule
//STRIP001  SwNumRule* GetNumRuleFromPool( USHORT nId );

    // erfrage ob die Absatz-/Zeichen-/Rahmen-/Seiten - Vorlage benutzt wird
//STRIP001  BOOL IsUsed( const SwModify& ) const;
//STRIP001  BOOL IsUsed( const SwNumRule& ) const;

        // returne das geforderte automatische Format
//STRIP001  SwFrmFmt* GetFrmFmtFromPool( USHORT nId )
//STRIP001      { return (SwFrmFmt*)SwEditShell::GetFmtFromPool( nId ); }
//STRIP001  SwCharFmt* GetCharFmtFromPool( USHORT nId )
//STRIP001      { return (SwCharFmt*)SwEditShell::GetFmtFromPool( nId ); }

    // Felder
    void Insert(SwField&);
    SwField* GetCurFld() const;

//STRIP001  void UpdateFlds( SwField & );       // ein einzelnes Feld

//STRIP001  USHORT GetFldTypeCount(USHORT nResId = USHRT_MAX, BOOL bUsed = FALSE) const;
//STRIP001  SwFieldType* GetFldType(USHORT nId, USHORT nResId = USHRT_MAX, BOOL bUsed = FALSE) const;
//STRIP001  SwFieldType* GetFldType(USHORT nResId, const String& rName) const;

//STRIP001  void RemoveFldType(USHORT nId, USHORT nResId = USHRT_MAX);
//STRIP001  void RemoveFldType(USHORT nResId, const String& rName);
//STRIP001  BOOL RenameUserFields(const String& rOldName, const String& rNewName);

//STRIP001  void FieldToText( SwFieldType* pType );

//STRIP001  void ChangeAuthorityData(const SwAuthEntry* pNewData);

    // Datenbankinfo
//STRIP001  SwDBData GetDBData() const;
    const SwDBData& GetDBDesc() const;
//STRIP001  void ChgDBData(const SwDBData& SwDBData);
//STRIP001  void ChangeDBFields( const SvStringsDtor& rOldNames,
//STRIP001                       const String& rNewName );
//STRIP001  void GetAllUsedDB( SvStringsDtor& rDBNameList,
//STRIP001                      SvStringsDtor* pAllDBNames = 0 );

//STRIP001     BOOL IsAnyDatabaseFieldInDoc()const;
    //check whether DB fields point to an available data source and returns it
    BOOL IsFieldDataSourceAvailable(String& rUsedDataSource) const;
//STRIP001  void UpdateExpFlds(BOOL bCloseDB = FALSE);// nur alle ExpressionFelder updaten
//STRIP001  void SetFixFields( BOOL bOnlyTimeDate = FALSE,
//STRIP001                      const DateTime* pNewDateTime = 0 );
//STRIP001  void LockExpFlds();
//STRIP001  void UnlockExpFlds();
//STRIP001  BOOL IsExpFldsLocked() const;

//STRIP001  USHORT GetFldUpdateFlags(BOOL bDocSettings = FALSE) const;
//STRIP001  void SetFldUpdateFlags( USHORT eFlags );

    // fuer die Evaluierung der DBFelder (neuer DB-Manager)
    SwNewDBMgr* GetNewDBMgr() const;

//STRIP001  SwFieldType* InsertFldType(const SwFieldType &);

    // Aenderungen am Dokument?
//STRIP001  BOOL IsModified() const;
//STRIP001  void SetModified();
    void ResetModified();
//STRIP001  void SetUndoNoResetModified();

    // Dokument - Statistics
//STRIP001  void UpdateDocStat( SwDocStat& rStat );

    // Dokument - Info
//STRIP001  const SfxDocumentInfo* GetInfo() const;

    // Verzeichnismarke einfuegen loeschen
//STRIP001  void    Insert(const SwTOXMark& rMark);
//STRIP001  void    DeleteTOXMark(SwTOXMark* pMark);

    // Alle Markierungen am aktuellen SPoint ermitteln
    USHORT  GetCurTOXMarks(SwTOXMarks& rMarks) const ;

    // Verzeichnis einfuegen, und bei Bedarf erneuern
//STRIP001  void                InsertTableOf(const SwTOXBase& rTOX,
//STRIP001                                      const SfxItemSet* pSet = 0);
//STRIP001  BOOL                UpdateTableOf(const SwTOXBase& rTOX,
//STRIP001                                      const SfxItemSet* pSet = 0);
    const SwTOXBase*    GetCurTOX() const;
//STRIP001  const SwAttrSet&    GetTOXBaseAttrSet(const SwTOXBase& rTOX) const;
//STRIP001  const SwTOXBase*    GetDefaultTOXBase( TOXTypes eTyp, BOOL bCreate = FALSE );
//STRIP001  void                SetDefaultTOXBase(const SwTOXBase& rBase);

//STRIP001  BOOL                IsTOXBaseReadonly(const SwTOXBase& rTOXBase) const;
//STRIP001  void                SetTOXBaseReadonly(const SwTOXBase& rTOXBase, BOOL bReadonly);

//STRIP001  USHORT              GetTOXCount() const;
//STRIP001  const SwTOXBase*    GetTOX( USHORT nPos ) const;
//STRIP001  BOOL                DeleteTOX( const SwTOXBase& rTOXBase, BOOL bDelNodes = FALSE );
//STRIP001  BOOL                DeleteCurTOX();

//STRIP001  String GetUniqueTOXBaseName( const SwTOXType& rType,
//STRIP001                              const String* pChkStr = 0 ) const;

//STRIP001  BOOL SetTOXBaseName(const SwTOXBase& rTOXBase, const String& rName);
//STRIP001  void SetTOXBaseProtection(const SwTOXBase& rTOXBase, BOOL bProtect);

    // nach einlesen einer Datei alle Verzeichnisse updaten
//STRIP001  void SetUpdateTOX( BOOL bFlag = TRUE );
//STRIP001  BOOL IsUpdateTOX() const;

    // Verzeichnis-Typen verwalten
//STRIP001  USHORT              GetTOXTypeCount(TOXTypes eTyp) const;
//STRIP001  const SwTOXType*    GetTOXType(TOXTypes eTyp, USHORT nId) const;
//STRIP001  void                InsertTOXType(const SwTOXType& rTyp);

    //AutoMark file
//STRIP001  const String&   GetTOIAutoMarkURL() const;
//STRIP001  void            SetTOIAutoMarkURL(const String& rSet);
//STRIP001  void            ApplyAutoMark();

    // Schluessel fuer die Indexverwaltung
//STRIP001  USHORT GetTOIKeys( SwTOIKeyType eTyp, SvStringsSort& rArr ) const;

//STRIP001  void SetOutlineNumRule(const SwNumRule&);
//STRIP001  const SwNumRule* GetOutlineNumRule() const;
    // Gliederung - hoch-/runterstufen
//STRIP001  BOOL OutlineUpDown( short nOffset = 1 );
    // Gliederung - hoch-/runtermoven
//STRIP001  BOOL MoveOutlinePara( short nOffset = 1);
    // Outlines and SubOutline are protected ?
//STRIP001  BOOL IsProtectedOutlinePara() const;

    // Numerierung Aufzaehlunglisten
    // liefert Regelwerk der aktuellen Aufzaehlung (FALSE sonst)
    const SwNumRule* GetCurNumRule() const;
    // setzt, wenn noch keine Numerierung, sonst wird geaendert
    // arbeitet mit alten und neuen Regeln, nur Differenzen aktualisieren
//STRIP001  void SetCurNumRule(const SwNumRule&);
    // Absaetze ohne Numerierung, aber mit Einzuegen
//STRIP001  BOOL NoNum();
    // Loeschen, Splitten der Aufzaehlungsliste
//STRIP001  BOOL DelNumRules();
    // Hoch-/Runterstufen
//STRIP001  BOOL NumUpDown( BOOL bDown = TRUE );
    // Hoch-/Runtermoven sowohl innerhalb als auch ausserhalb von Numerierungen
//STRIP001  BOOL MoveParagraph( long nOffset = 1);
//STRIP001  BOOL MoveNumParas( BOOL bUpperLower, BOOL bUpperLeft );
    // No-/Numerierung ueber Delete/Backspace ein/abschalten
//STRIP001  BOOL NumOrNoNum( BOOL bDelete = FALSE, BOOL bChkStart = TRUE,
//STRIP001                      BOOL bOutline = FALSE );
//STRIP001  BOOL IsNoNum( BOOL bChkStart = TRUE, BOOL bOutline = FALSE ) const;
    // returne den Num-Level des Nodes, in dem sich der Point vom
    // Cursor befindet. Return kann sein :
    // - NO_NUMBERING, 0..MAXLEVEL-1, NO_NUMLEVEL .. NO_NUMLEVEL|MAXLEVEL-1
    BYTE GetNumLevel( BOOL* pHasChilds = 0 ) const;
    // detect highest and lowest level to check moving of outline levels
//STRIP001     void GetCurrentOutlineLevels( sal_uInt8& rUpper, sal_uInt8& rLower );

//STRIP001  String GetUniqueNumRuleName( const String* pChkStr = 0, BOOL bAutoNum = TRUE ) const;
//STRIP001  void ChgNumRuleFmts( const SwNumRule& rRule );
    // setze und erfrage, ob an aktueller PointPos eine Numerierung mit
    // dem StartFlag startet
//STRIP001  void SetNumRuleStart( BOOL bFlag = TRUE );
//STRIP001  BOOL IsNumRuleStart() const;
//STRIP001  void SetNodeNumStart( USHORT nStt = USHRT_MAX );
//STRIP001  USHORT IsNodeNumStart() const;
//STRIP001  BOOL ReplaceNumRule( const String& rOldRule, const String& rNewRule );

    // Undo
    // UndoHistory am Dokument pflegen
    // bei Save, SaveAs, Create wird UndoHistory zurueckgesetzt ???
    void DoUndo( BOOL bOn = TRUE );
//STRIP001  BOOL DoesUndo() const;
//STRIP001  void DoGroupUndo( BOOL bUn = TRUE );
//STRIP001  BOOL DoesGroupUndo() const;
//STRIP001  void DelAllUndoObj();

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
//STRIP001  USHORT GetRepeatIds( String* pRepeatStr = 0, SwUndoIds *pRedoIds = 0) const;

    // 0 letzte Aktion, sonst Aktionen bis zum Start der Klammerung nUndoId
    // mit KillPaMs, ClearMark
//STRIP001  BOOL Undo(USHORT nUndoId = 0, USHORT nCnt = 1 );
    // wiederholt
//STRIP001  USHORT Repeat( USHORT nCount );
    // wiederholt
//STRIP001  USHORT Redo( USHORT nCnt = 1 );
#ifdef USED
    // Aktionen klammern
//STRIP001  void StartAction();
//STRIP001  void EndAction();
#endif
    // fuer alle Sichten auf dieses Dokument
    void StartAllAction();
    void EndAllAction();

    //Damit Start-/EndActions aufgesetzt werden koennen.
    void CalcLayout();

    // Inhaltsform bestimmen, holen, liefert Type am CurCrsr->SPoint
    USHORT GetCntType() const;
//STRIP001  BOOL HasOtherCnt() const; // gibt es Rahmen, Fussnoten, ...

    /* Anwenden der ViewOptions mit Start-/EndAction */
    inline void ApplyViewOptions( const SwViewOption &rOpt );

    // Text innerhalb der Selektion erfragen
    // Returnwert liefert FALSE, wenn der selektierte Bereich
    // zu gross ist, um in den Stringpuffer kopiert zu werden
    // oder andere Fehler auftreten
//STRIP001  BOOL GetSelectedText( String &rBuf,
//STRIP001                      int nHndlParaBreak = GETSELTXT_PARABRK_TO_BLANK );

    /*
     * liefert eine Graphic, wenn CurCrsr->Point() auf einen
     * SwGrfNode zeigt (und Mark nicht gesetzt ist oder auf die
     * gleiche Graphic zeigt), sonst gibt's was auf die Finger
     */
//STRIP001  const Graphic &GetGraphic( BOOL bWait = TRUE ) const;
//STRIP001  const GraphicObject &GetGraphicObj() const;
//STRIP001  BOOL IsGrfSwapOut( BOOL bOnlyLinked = FALSE ) const;
//STRIP001  USHORT GetGraphicType() const;

//STRIP001  const PolyPolygon *GetGraphicPolygon() const;
//STRIP001  void SetGraphicPolygon( const PolyPolygon *pPoly );

    // If there's an automatic, not manipulated polygon at the selected
    // notxtnode, it has to be deleted, e.g. cause the object has changed.
//STRIP001     void ClearAutomaticContour();

    /*
     * liefert die Groesse einer Graphic in Twips, wenn der Cursor
     * auf einer Graphic steht; BOOL liefert FALSE, wenn s.o.
     */
//STRIP001  BOOL GetGrfSize(Size&) const;
    /*
     * liefert den Namen und den Filter einer Graphic, wenn der Cursor
     * auf einer Graphic steht, sonst gibt's was auf die Finger!
     * Ist ein String-Ptr != 0 dann returne den entsp. Namen
     */
//STRIP001  void GetGrfNms( String* pGrfName, String* pFltName,
//STRIP001                  const SwFlyFrmFmt* = 0 ) const;
    /*
     * erneutes Einlesen, falls Graphic nicht Ok ist. Die
     * aktuelle wird durch die neue ersetzt.
     */
//STRIP001  void ReRead( const String& rGrfName, const String& rFltName,
//STRIP001                const Graphic* pGraphic = 0,
//STRIP001                const GraphicObject* pGrafObj = 0 );

    // alternativen Text einer Grafik/OLe-Objectes abfragen/setzen
//STRIP001  const String& GetAlternateText() const;
//STRIP001  void SetAlternateText( const String& rTxt );

    //eindeutige Identifikation des Objektes (fuer ImageMapDlg)
//STRIP001  void    *GetIMapInventor() const;
//STRIP001  Graphic GetIMapGraphic( BOOL bWait = TRUE ) const; //liefert eine Graphic fuer alle Flys!
//STRIP001  const SwFlyFrmFmt* FindFlyByName( const String& rName, BYTE nNdTyp = 0 ) const;

    //liefert ein ClientObject, wenn CurCrsr->Point() auf einen
    //SwOLENode zeigt (und Mark nicht gesetzt ist oder auf das
    //gleiche ClientObject zeigt), sonst gibt's was auf die
    //Finger.
//STRIP001  SvInPlaceObjectRef GetOLEObj() const;
    //Gibt es ein OleObject mit diesem Namen (SwFmt)?
//STRIP001  BOOL HasOLEObj( const String &rName ) const;

    //Liefert den Pointer auf die Daten des Chart, indem sich der Crsr
    //befindet.
//STRIP001  void SetChartName( const String &rName );
    // returne den ChartNamen - vom Crsr oder vom uebergebenen OLE-Object
    // reurnt aEmptyStr wenn nicht gefunden wurde
//STRIP001  const String& GetChartName( SvInPlaceObject* pObj = 0 );
    //Sucht die Tabelle und liefert ein mit den Daten der Tabelle gefuelltes
    //pData. Wenn pData 0 ist wird eines angelegt.
//STRIP001  void UpdateChartData( const String &rName, SchMemChart *&pData );
    //Updaten der Inhalte aller Charts zu der Tabelle mit dem angegeben Namen
//STRIP001  void UpdateCharts( const String &rName );

    //  aktuelles Wort erfragen
//STRIP001  String GetCurWord();

    // Textbaustein aus dem Textbausteindokument in
    // das aktuelle Dokument, Vorlagen nur wenn es nicht schon gibt
//STRIP001  void InsertGlossary( SwTextBlocks& rGlossary, const String& );
    // aktuelle Selektion zum Textbaustein machen und ins
    // Textbausteindokument einfuegen, einschliesslich Vorlagen
//STRIP001  USHORT MakeGlossary( SwTextBlocks& rToFill, const String& rName,
//STRIP001                       const String& rShortName, BOOL bSaveRelFile = FALSE,
//STRIP001                       BOOL bSaveRelNet = FALSE, const String* pOnlyTxt=0 );
    // speicher den gesamten Inhalt des Docs als Textbaustein
//STRIP001  USHORT SaveGlossaryDoc( SwTextBlocks& rGlossary, const String& rName,
//STRIP001                          const String& rShortName,
//STRIP001                          BOOL bSaveRelFile = FALSE,
//STRIP001                          BOOL bSaveRelNet = FALSE,
//STRIP001                          BOOL bOnlyTxt = FALSE );

    // Linguistik
    // Selektionen sichern
//STRIP001  void HyphStart( SwDocPositions eStart, SwDocPositions eEnde );
    // Selektionen wiederherstellen
//STRIP001  void HyphEnd();
//STRIP001  ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface>
//STRIP001              HyphContinue( USHORT* pPageCnt, USHORT* pPageSt );
    // zu trennendes Wort ignorieren
//STRIP001  void HyphIgnore();

    // zum Einfuegen des SoftHyphens, Position ist der Offset
    // innerhalb des getrennten Wortes.
//STRIP001  void InsertSoftHyph( const xub_StrLen nHyphPos );

    //Tabelle
//STRIP001  const SwTable& InsertTable(USHORT nRows, USHORT nCols,
//STRIP001                              SwHoriOrient = HORI_FULL,
//STRIP001                              USHORT nInsert = ALL_TBL_INS_ATTR,
//STRIP001                              const SwTableAutoFmt* pTAFmt = 0 );
//STRIP001  void InsertDDETable( SwDDEFieldType* pDDEType,
//STRIP001                          USHORT nRows, USHORT nCols,
//STRIP001                          SwHoriOrient eAdj = HORI_FULL,
//STRIP001                          USHORT nInsert = HEADLINE_NO_BORDER );
    void UpdateTable();
//STRIP001  void SetTableName( SwFrmFmt& rTblFmt, const String &rNewName );

    SwFrmFmt *GetTableFmt();
//STRIP001  BOOL TextToTable( sal_Unicode cCh, SwHoriOrient eAdj = HORI_FULL,
//STRIP001                      USHORT nInsert = ALL_TBL_INS_ATTR,
//STRIP001                      const SwTableAutoFmt* pTAFmt = 0 );
//STRIP001  BOOL TableToText( sal_Unicode cCh );
//STRIP001  FASTBOOL IsTextToTableAvailable() const;

//STRIP001  BOOL GetTblBoxFormulaAttrs( SfxItemSet& rSet ) const;
//STRIP001  void SetTblBoxFormulaAttrs( const SfxItemSet& rSet );

//STRIP001  BOOL IsTableBoxTextFormat() const;
//STRIP001  String GetTableBoxText() const;

    // Change Modus erfragen/setzen
    USHORT GetTblChgMode() const;
//STRIP001  void SetTblChgMode( USHORT eMode );

    // Zellenbreiten ueber Min/Max Berechnung an Tabellenbreite anpassen
//STRIP001  void OptimizeTblBoxWidthMinMax();
    // Tabelle an der Cursor Position aufsplitten
//STRIP001  BOOL SplitTable( USHORT eMode );
    // Tabellen verbinden
    // CanMerge kann feststellen, ob Prev oder Next moeglich ist. Wird
    // der Pointer pChkNxtPrv uebergeben, wird festgestellt in welche
    // Richtung es moeglich ist.
//STRIP001  BOOL CanMergeTable( BOOL bWithPrev = TRUE, BOOL* pChkNxtPrv = 0 ) const;
//STRIP001  BOOL MergeTable( BOOL bWithPrev = TRUE, USHORT nMode = 0 );
        // setze das InsertDB als Tabelle Undo auf:
//STRIP001  void AppendUndoForInsertFromDB( BOOL bIsTable );

    /*
        functions used for spell checking and text conversion
    */

    // Selektionen sichern
//STRIP001  void SpellStart( SwDocPositions eStart, SwDocPositions eEnde,
//STRIP001                      SwDocPositions eCurr, sal_Bool bIsConversion = sal_False );
    // Selektionen wiederherstellen
//STRIP001     void SpellEnd( sal_Bool bIsConversion = sal_False );
//STRIP001     ::com::sun::star::uno::Any SpellContinue(
//STRIP001                     USHORT* pPageCnt, USHORT* pPageSt,
//STRIP001                     sal_Bool bIsConversion = sal_False );

    // Is spelling active somewhere else?
//STRIP001  BOOL HasSpellIter() const;
    // Is text conversion active somewhere else?
    BOOL HasConvIter() const;
    // Is hyphenation active somewhere else?
//STRIP001  BOOL HasHyphIter() const;

//STRIP001  ::com::sun::star::uno::Reference<
//STRIP001      ::com::sun::star::linguistic2::XSpellAlternatives >
//STRIP001          GetCorrection( const Point* pPt );

//STRIP001  void SetLinguRange( SwDocPositions eStart, SwDocPositions eEnde );

    // returne zum Namen die im Doc gesetzte Referenz
//STRIP001  const SwFmtRefMark* GetRefMark( const String& rName ) const;
    // returne die Namen aller im Doc gesetzten Referenzen
    //  Ist der ArrayPointer 0 dann returne nur, ob im Doc. eine RefMark
    //  gesetzt ist
//STRIP001  USHORT GetRefMarks( SvStringsDtor* = 0 ) const;

    // rufe die Autokorrektur auf
//STRIP001  void AutoCorrect( SvxAutoCorrect& rACorr, BOOL bInsertMode = TRUE,
//STRIP001                      sal_Unicode cChar = ' ' );
//STRIP001  BOOL GetPrevAutoCorrWord( SvxAutoCorrect& rACorr, String& rWord );

    // dann setze nach entsprechenden Regeln unsere Vorlagen
//STRIP001  void AutoFormat( const SvxSwAutoFmtFlags* pAFlags = 0 );

    static SvxSwAutoFmtFlags* GetAutoFmtFlags();
    static void SetAutoFmtFlags(SvxSwAutoFmtFlags *);

    // errechnet die Selektion
//STRIP001  String Calculate();

//STRIP001  BOOL InsertURL( const SwFmtINetFmt& rFmt, const String& rStr,
//STRIP001                  BOOL bKeepSelection = FALSE );
//STRIP001  USHORT GetINetAttrs( SwGetINetAttrs& rArr );

    //SS Fuer holen/ersetzen DropCap-Inhalt
//STRIP001  String GetDropTxt( const USHORT nChars ) const;
//STRIP001  void   ReplaceDropTxt( const String &rStr );

    // Abfrage von Oultine Informationen:
//STRIP001  USHORT GetOutlineCnt() const;

//STRIP001  BYTE GetOutlineLevel( USHORT nIdx ) const;
    // mit exp. Felder und KapitelNummern
//STRIP001  String GetOutlineText( USHORT nIdx, BOOL bWithNum = TRUE ) const;
    // die Nummer
//STRIP001  const SwNodeNum* GetOutlineNum( USHORT nIdx ) const;

    // may an outline be moved or copied?
    // Check whether it's in text body, not in table, and not read-only (move)
//STRIP001  BOOL IsOutlineMovable( USHORT nIdx ) const;
//STRIP001  BOOL IsOutlineCopyable( USHORT nIdx ) const;

//STRIP001  USHORT GetLineCount( BOOL bActPos = TRUE );

    // erfrage und setze den Fussnoten-Text/Nummer. Set.. auf akt. SSelection!
//STRIP001  BOOL GetCurFtn( SwFmtFtn* pToFillFtn = 0 );
//STRIP001  BOOL SetCurFtn( const SwFmtFtn& rFillFtn );
//STRIP001  BOOL HasFtns( BOOL bEndNotes = FALSE ) const;
//z.Zt nicht benoetigt  USHORT GetFtnCnt( BOOL bEndNotes = FALSE ) const;
        // gebe Liste aller Fussnoten und deren Anfangstexte
//STRIP001  USHORT GetSeqFtnList( SwSeqFldList& rList, BOOL bEndNotes = FALSE );

    // SS fuer Bereiche
//STRIP001  const SwSection* InsertSection( const SwSection& rNew,
//STRIP001                                  const SfxItemSet* = 0 );
//STRIP001  BOOL IsInsRegionAvailable() const;
    const SwSection* GetCurrSection() const;
    // liefert wie GetCurrSection() den aktuellen Bereich, allerdings geht diese Funktion
    // ueber die Frames und erwischt dabei auch den Bereich, wenn der Cursor in einer
    // Fussnote steht, deren Referenz in einem spaltigen Bereich steckt.
    // Wenn man bOutOfTab setzt, wird der Bereich gesucht,
    // der die Tabelle umfasst, nicht etwa ein innerer.
//STRIP001     const SwSection* GetAnySection( BOOL bOutOfTab = FALSE, const Point* pPt = 0 ) const;

//STRIP001  USHORT GetSectionFmtCount() const;
//STRIP001  USHORT GetSectionFmtPos( const SwSectionFmt& ) const;
//STRIP001  const SwSectionFmt& GetSectionFmt(USHORT nFmt) const;
//STRIP001  void DelSectionFmt( USHORT nFmt );
//STRIP001  void ChgSection( USHORT nSect, const SwSection&, const SfxItemSet* = 0 );
    BOOL IsAnySectionInDoc( BOOL bChkReadOnly = FALSE,
                            BOOL bChkHidden = FALSE,
                            BOOL BChkTOX = FALSE ) const;
        // Passwort fuer geschuetzte Bereiche erfragen/setzen
//STRIP001  void ChgSectionPasswd(
//STRIP001              const ::com::sun::star::uno::Sequence <sal_Int8>& rNew,
//STRIP001                 const SwSection& rSect );

//STRIP001  String GetUniqueSectionName( const String* pChkStr = 0 ) const;

    //Attribute setzen
//STRIP001  void SetSectionAttr(const SfxItemSet& rSet, SwSectionFmt* pSectFmt = 0);

    // search inside the cursor selection for full selected sections.
    // if any part of section in the selection return 0.
    // if more than one in the selection return the count
//STRIP001  USHORT GetFullSelectedSectionCount() const;

    // special insert: Insert a new text node just before or after a section or
    // table, if the cursor is positioned at the start/end of said
    // section/table. The purpose of the method is to allow users to inert text
    // at certain 'impossible' position, e.g. before a table at the document
    // start or between to sections.
    bool DoSpecialInsert();
    bool CanSpecialInsert() const;

    // Optimierung UI
//STRIP001  void SetNewDoc(BOOL bNew = TRUE);

//STRIP001        SvxLinkManager& GetLinkManager();
    inline const SvxLinkManager& GetLinkManager() const;

    // linken Rand ueber Objectleiste einstellen (aenhlich dem Stufen von
    // Numerierungen), optional kann man "um" den Offset stufen oder "auf"
    // die Position gestuft werden (bModulus = TRUE)
    BOOL IsMoveLeftMargin( BOOL bRight = TRUE, BOOL bModulus = TRUE ) const;
//STRIP001  void MoveLeftMargin( BOOL bRight = TRUE, BOOL bModulus = TRUE );

    // Numberformatter vom Doc erfragen
//STRIP001        SvNumberFormatter* GetNumberFormatter();
    const SvNumberFormatter* GetNumberFormatter() const
    {   return ((SwEditShell*)this)->GetNumberFormatter();  }

    // Extrakt fuellen
//STRIP001  void Summary( SwDoc* pExtDoc, BYTE nLevel, BYTE nPara, BOOL bImpress );

    // Schnitstellen fuers GlobalDokument
//STRIP001  void SetGlobalDoc( BOOL bFlag = TRUE );
//STRIP001  BOOL IsGlobalDoc() const;
//STRIP001  void SetGlblDocSaveLinks( BOOL bFlag = TRUE );
//STRIP001  BOOL IsGlblDocSaveLinks() const;
//STRIP001  USHORT GetGlobalDocContent( SwGlblDocContents& rArr ) const;
//STRIP001  BOOL InsertGlobalDocContent( const SwGlblDocContent& rPos,
//STRIP001                               const SwSection& rNew );
//STRIP001  BOOL InsertGlobalDocContent( const SwGlblDocContent& rPos,
//STRIP001                               const SwTOXBase& rTOX );
//STRIP001  BOOL InsertGlobalDocContent( const SwGlblDocContent& rPos );
//STRIP001  BOOL DeleteGlobalDocContent( const SwGlblDocContents& rArr,
//STRIP001                              USHORT nPos );
//STRIP001  BOOL MoveGlobalDocContent( const SwGlblDocContents& rArr ,
//STRIP001                              USHORT nFromPos, USHORT nToPos,
//STRIP001                              USHORT nNewPos );
//STRIP001  BOOL GotoGlobalDocContent( const SwGlblDocContent& rPos );
    // erzeuge Anhand der vorgebenen Collection Teildokumente
    // falls keine angegeben ist, nehme die Kapitelvorlage der 1. Ebene
//STRIP001  BOOL GenerateGlobalDoc( const String& rPath,
//STRIP001                              const SwTxtFmtColl* pSplitColl = 0 );
//STRIP001  BOOL GenerateHTMLDoc( const String& rPath,
//STRIP001                              const SwTxtFmtColl* pSplitColl = 0 );

    // alles fuers Redlining
//STRIP001  USHORT GetRedlineMode() const;
//STRIP001  void SetRedlineMode( USHORT eMode );
    BOOL IsRedlineOn() const;
//STRIP001  USHORT GetRedlineCount() const;
//STRIP001  const SwRedline& GetRedline( USHORT nPos ) const;
//STRIP001  BOOL AcceptRedline( USHORT nPos );
//STRIP001  BOOL AcceptRedline();
//STRIP001  BOOL RejectRedline( USHORT nPos );
//STRIP001  BOOL RejectRedline();
    // suche das Redline zu diesem Data und returne die Pos im Array
    // USHRT_MAX wird returnt, falls nicht vorhanden
//STRIP001  USHORT FindRedlineOfData( const SwRedlineData& ) const;

    // Kommentar am Redline an der Position setzen
//STRIP001  BOOL SetRedlineComment( const String& rS );
//STRIP001  const SwRedline* GetCurrRedline() const;

    // Redline Anzeigeattribute wurden geaendert, Views updaten
//STRIP001  void UpdateRedlineAttr();

    //  vergleiche zwei Dokument mit einander
//STRIP001  long CompareDoc( const SwDoc& rDoc );
    // merge zweier Dokumente
//STRIP001  long MergeDoc( const SwDoc& rDoc );

    // Dokumentglobale Fussnoteneigenschaften
//STRIP001  const SwFtnInfo& GetFtnInfo() const;
//STRIP001  void  SetFtnInfo(const SwFtnInfo& rInfo);
//STRIP001  const SwEndNoteInfo& GetEndNoteInfo() const;
//STRIP001  void  SetEndNoteInfo(const SwEndNoteInfo& rInfo);

    //Einstellungen fuer Zeilennummierung
//STRIP001  const SwLineNumberInfo &GetLineNumberInfo() const;
//STRIP001  void  SetLineNumberInfo( const SwLineNumberInfo& rInfo);

    // Etiketten: Bereiche synchronisieren
//STRIP001  void SetLabelDoc( BOOL bFlag = TRUE );
    BOOL IsLabelDoc() const;

    // Schnittstelle fuer die TextInputDaten - ( fuer die Texteingabe
    // von japanischen/chinesischen Zeichen)
//STRIP001  SwExtTextInput* CreateExtTextInput();
//STRIP001     String DeleteExtTextInput( SwExtTextInput* pDel = 0, BOOL bInsText = TRUE );
//  SwExtTextInput* GetExtTextInput() const;
//STRIP001  void SetExtTextInputData( const CommandExtTextInputData& );

    // Schnistelle fuer den Zugriff auf die AutoComplete-Liste
//STRIP001  static SwAutoCompleteWord& GetAutoCompleteWords();

    // returns a scaling factor of selected text. Used for the rotated
    // character attribut dialog.
//STRIP001  USHORT GetScalingOfSelectedText() const;

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
//STRIP001 class SwActKontext {
//STRIP001  SwEditShell *pSh;
//STRIP001 public:
//STRIP001  SwActKontext(SwEditShell *pShell);
//STRIP001  ~SwActKontext();
//STRIP001 };

//STRIP001 #define ACT_KONTEXT(x)   SwActKontext _aActKontext_(x)

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



#endif
