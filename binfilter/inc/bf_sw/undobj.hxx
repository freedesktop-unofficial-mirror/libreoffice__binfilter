/*************************************************************************
 *
 *  $RCSfile: undobj.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 08:34:24 $
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
#ifndef _UNDOBJ_HXX
#define _UNDOBJ_HXX

#ifndef _SVMEMPOOL_HXX //autogen
#include <tools/mempool.hxx>
#endif
#ifndef _SVSTDARR_HXX
#define _SVSTDARR_USHORTS
#define _SVSTDARR_ULONGS
#define _SVSTDARR_BOOLS
#define _SVSTDARR_BYTES
#define _SVSTDARR_USHORTSSORT
#include <svtools/svstdarr.hxx>
#endif
#ifndef _SFXITEMSET_HXX //autogen
#include <svtools/itemset.hxx>
#endif
#ifndef _COM_SUN_STAR_UNO_SEQUENCE_H_
#include <com/sun/star/uno/Sequence.h>
#endif
#ifndef _NUMRULE_HXX
#include <numrule.hxx>
#endif
#ifndef _REDLENUM_HXX
#include <redlenum.hxx>
#endif
class Graphic;
namespace binfilter {

class SwUndoIter;
class SwHistory;
class SwIndex;
class SwPaM;
struct SwPosition;
class SwDoc;
class SwNodes;
class SwFmt;
class SwFmtColl;
class SwTxtFmtColl;
class SwTxtNode;
class SwpHints;
class SwBookmark;
class SwTableNode;
class SwTable;
class SwTableBox;
struct SwSortOptions;
class SwFrmFmt;
class SwHstryBookmark;
class SwSection;
class SwSectionFmt;
class SvxTabStopItem;
class SwNumSection;
class SwDDEFieldType;

class SwGrfNode;
class SwUndos;
class SwUndoRange;
class SwFtnInfo;
class SwEndNoteInfo;
class SwNodeIndex;
class SwNodeRange;
class SwFmtAnchor;
struct SwUndoGroupObjImpl;
class SdrMark;
class SdrMarkList;
class SdrObject;
class SdrObjGroup;
class SdrUndoAction;
class SwDrawFrmFmt;
//STRIP001 class _SaveTable;
class SwTableAutoFmt;
class SwSelBoxes;
class SwTableSortBoxes;
class SwUndoSaveSections;
class SwUndoMoves;
class SwStartNode;
class _SaveFlyArr;
class SwTblToTxtSaves;
class SwRedlineData;
class SwRedlineSaveData;
class SwRedline;
class SwSectionNode;

namespace utl {
    class TransliterationWrapper;
}//STRIP008 ;

#ifndef PRODUCT
class Writer;
class SwUndo;
#define OUT_UNDOBJ( name )  \
    friend Writer& OutUndo_ ## name( Writer&, const SwUndo& );
#else
#define OUT_UNDOBJ( name )
#endif


typedef SwRedlineSaveData* SwRedlineSaveDataPtr;
SV_DECL_PTRARR_DEL( SwRedlineSaveDatas, SwRedlineSaveDataPtr, 8, 8 )

class SwUndo
{
    USHORT nId;
    USHORT nOrigRedlineMode;
protected:
//STRIP001  void RemoveIdxFromSection( SwDoc&, ULONG nSttIdx, ULONG* pEndIdx = 0 );
//STRIP001  void RemoveIdxFromRange( SwPaM& rPam, BOOL bMoveNext );
//STRIP001  void RemoveIdxRel( ULONG, const SwPosition& );

    void SetId( USHORT nNew ) { nId = nNew; }

//STRIP001  static BOOL CanRedlineGroup( SwRedlineSaveDatas& rCurr,
//STRIP001                              const SwRedlineSaveDatas& rCheck,
//STRIP001                              BOOL bCurrIsEnd );
public:
    SwUndo( USHORT nI ) { nId = nI; nOrigRedlineMode = REDLINE_NONE; }
    virtual ~SwUndo();

    USHORT GetId() const { return nId; }
//STRIP001  virtual void Undo( SwUndoIter& ) = 0;
//STRIP001  virtual void Redo( SwUndoIter& ) = 0;
//STRIP001  virtual void Repeat( SwUndoIter& );

        // das UndoObject merkt sich, welcher Mode eingeschaltet war.
        // In Undo/Redo/Repeat wird dann immer auf diesen zurueck geschaltet
    USHORT GetRedlineMode() const { return nOrigRedlineMode; }
    void SetRedlineMode( USHORT eMode ) { nOrigRedlineMode = eMode; }

        // sicher und setze die RedlineDaten
    static BOOL FillSaveData( const SwPaM& rRange, SwRedlineSaveDatas& rSData,
                            BOOL bDelRange = TRUE, BOOL bCopyNext = TRUE );
//STRIP001  static BOOL FillSaveDataForFmt( const SwPaM& , SwRedlineSaveDatas& );
//STRIP001  static void SetSaveData( SwDoc& rDoc, const SwRedlineSaveDatas& rSData );
//STRIP001  static BOOL HasHiddenRedlines( const SwRedlineSaveDatas& rSData );
};


// diese Klasse muss in ein Undo-Object vererbt werden, wenn dieses Inhalt
// fuers Redo/Undo ... speichert
class SwUndoSaveCntnt
{
protected:

    SwHistory* pHistory;

    // wird fuer das loeschen von Inhalt benoetigt. Fuer das ReDo werden
    // Inhalte in das UndoNodesArray verschoben. Diese Methoden fuegen
    // am Ende eines TextNodes ein Trenner fuer die Attribute. Damit werden
    // Attribute nicht expandiert.
    // MoveTo..     verschiebt aus dem NodesArray in das UndoNodesArray
    // MoveFrom..   verschiebt aus dem UndoNodesArray in das NodesArray
    void MoveToUndoNds( SwPaM& rPam,
                        SwNodeIndex* pNodeIdx = 0, SwIndex* pCntIdx = 0,
                        ULONG* pEndNdIdx = 0, xub_StrLen * pEndCntIdx = 0 );
//STRIP001  void MoveFromUndoNds( SwDoc& rDoc, ULONG nNodeIdx, xub_StrLen nCntntIdx,
//STRIP001                        SwPosition& rInsPos,
//STRIP001                        ULONG* pEndNdIdx = 0, xub_StrLen * pEndCntIdx = 0 );

    // diese beiden Methoden bewegen den SPoint vom Pam zurueck/vor. Damit
    // kann fuer ein Undo/Redo ein Bereich aufgespannt werden. (Der
    // SPoint liegt dann vor dem manipuliertem Bereich !!)
    // Das Flag gibt an, ob noch vorm SPoint Inhalt steht.
//STRIP001  BOOL MovePtBackward( SwPaM& rPam );
//STRIP001  void MovePtForward( SwPaM& rPam, BOOL bMvBkwrd );

    // vor dem Move ins UndoNodes-Array muss dafuer gesorgt werden, das
    // die Inhaltstragenden Attribute aus dem Nodes-Array entfernt werden.
    enum DelCntntType{  DELCNT_FTN = 0x01,
                        DELCNT_FLY = 0x02,
                        DELCNT_TOC = 0x04,
                        DELCNT_BKM = 0x08,
                        DELCNT_ALL = 0x0F,
                        DELCNT_CHKNOCNTNT = 0x80    // nur den NodeIndex beachten
                    };
    void DelCntntIndex( const SwPosition& pMark, const SwPosition& pPoint,
                        DelCntntType nDelCntntType = DELCNT_ALL );

public:
    SwUndoSaveCntnt();
    ~SwUndoSaveCntnt();
    OUT_UNDOBJ( SaveCntnt )
};


// sicher eine vollstaendige Section im Nodes-Array
class SwUndoSaveSection : private SwUndoSaveCntnt
{
    SwNodeIndex *pMvStt;
    SwRedlineSaveDatas* pRedlSaveData;
    ULONG nMvLen;           // Index ins UndoNodes-Array
    ULONG nStartPos;

protected:
    SwNodeIndex* GetMvSttIdx() const { return pMvStt; }
    ULONG GetMvNodeCnt() const { return nMvLen; }

public:
    SwUndoSaveSection();
    ~SwUndoSaveSection();

    void SaveSection( SwDoc* pDoc, const SwNodeIndex& rSttIdx );
    void SaveSection( SwDoc* pDoc, const SwNodeRange& rRange );
//STRIP001  void RestoreSection( SwDoc* pDoc, SwNodeIndex* pIdx, USHORT nSectType );
//STRIP001  void RestoreSection( SwDoc* pDoc, const SwNodeIndex& rInsPos );

    const SwHistory* GetHistory() const { return pHistory; }
          SwHistory* GetHistory()       { return pHistory; }
    OUT_UNDOBJ( SaveSection )
};


// Diese Klasse speichert den Pam als USHORT's und kann diese wieder zu
// einem PaM zusammensetzen
class SwUndRng
{
public:
    ULONG nSttNode, nEndNode;
    xub_StrLen nSttCntnt, nEndCntnt;

    SwUndRng();
    SwUndRng( const SwPaM& );

    void SetValues( const SwPaM& rPam );
//STRIP001  void SetPaM( SwPaM&, BOOL bCorrToCntnt = FALSE ) const;
//STRIP001  void SetPaM( SwUndoIter&, BOOL bCorrToCntnt = FALSE ) const;
};


class SwUndoStart: public SwUndo
{
    // Um innerhalb von Undo zuerkennen, wann ein Start vorliegt, gibt
    // GetId() immer die UNDO_START zurueck. Die UserId kann ueber
    // GetUserId() erfragt werden.
    USHORT nUserId;
    // fuer die "Verpointerung" von Start- und End-Undos
    USHORT nEndOffset;
public:
    SwUndoStart( USHORT nId );
//STRIP001  virtual void Undo( SwUndoIter& );
//STRIP001  virtual void Redo( SwUndoIter& );
//STRIP001  virtual void Repeat( SwUndoIter& );
    USHORT GetUserId() const { return nUserId; }
    // Setzen vom End-Undo-Offset geschieht im Doc::EndUndo
    USHORT GetEndOffset() const { return nEndOffset; }
    void SetEndOffset( USHORT n ) { nEndOffset = n; }
    OUT_UNDOBJ( Start )
};

class SwUndoEnd: public SwUndo
{
    // Um innerhalb von Undo zuerkennen, wann ein Ende vorliegt, gibt
    // GetId() immer die UNDO_END zurueck. Die UserId kann ueber
    // GetUserId() erfragt werden.
    USHORT nUserId;
    // fuer die "Verpointerung" von Start- und End-Undos
    USHORT nSttOffset;
public:
    SwUndoEnd( USHORT nId );
//STRIP001  virtual void Undo( SwUndoIter& );
//STRIP001  virtual void Redo( SwUndoIter& );
//STRIP001  virtual void Repeat( SwUndoIter& );
    USHORT GetUserId() const { return nUserId; }
    // Setzen vom Start-Undo-Offset geschieht im Doc::EndUndo
    USHORT GetSttOffset() const { return nSttOffset; }
    void SetSttOffset( USHORT n ) { nSttOffset = n; }
    OUT_UNDOBJ( End )
};

class SwUndoInsert: public SwUndo, private SwUndoSaveCntnt
{
    SwPosition *pPos;                   // Inhalt fuers Redo
    String* pTxt;
    SwRedlineData* pRedlData;
    ULONG nNode;
    xub_StrLen nCntnt, nLen;
    BOOL bIsWordDelim : 1;
    BOOL bIsAppend : 1;

    friend class SwDoc;     // eigentlich nur SwDoc::Insert( String )
    BOOL CanGrouping( sal_Unicode cIns );
    BOOL CanGrouping( const SwPosition& rPos );

public:
    SwUndoInsert( const SwNodeIndex& rNode, xub_StrLen nCntnt, xub_StrLen nLen,
                  BOOL bWDelim = TRUE );
    SwUndoInsert( const SwNodeIndex& rNode );
    virtual ~SwUndoInsert();
//STRIP001  virtual void Undo( SwUndoIter& );
//STRIP001  virtual void Redo( SwUndoIter& );
//STRIP001  virtual void Repeat( SwUndoIter& );

    BOOL CanGrouping( const SwPosition&, sal_Unicode cIns );
    OUT_UNDOBJ( Insert )

    DECL_FIXEDMEMPOOL_NEWDEL(SwUndoInsert)
};


class SwUndoDelete: public SwUndo, private SwUndRng, private SwUndoSaveCntnt
{
    SwNodeIndex* pMvStt;            // Position der Nodes im UndoNodes-Array
    String *pSttStr, *pEndStr;
    SwRedlineData* pRedlData;
    SwRedlineSaveDatas* pRedlSaveData;

    ULONG nNode;
    ULONG nNdDiff;              // Differenz von Nodes vor-nach Delete
    ULONG nSectDiff;            // Diff. von Nodes vor/nach Move mit SectionNodes
    USHORT nSetPos;

    BOOL bGroup : 1;    // TRUE: ist schon eine Gruppe; wird in CanGrouping() ausgwertet !!
    BOOL bBackSp : 1;   // TRUE: wenn Gruppierung und der Inhalt davor geloescht wird
    BOOL bJoinNext: 1;  // TRUE: wenn der Bereich von Oben nach unten geht
    BOOL bSectNdFnd : 1;    // TRUE: Sonderbehandlung fuer SectionNodes
    BOOL bMvAroundSectNd :1;// TRUE: Sonderbehandlung fuer SectionNodes
    BOOL bTblDelLastNd : 1; // TRUE: TextNode hinter der Tabelle einf./loeschen
    BOOL bDelFullPara : 1;  // TRUE: gesamte Nodes wurden geloescht
    BOOL bResetPgDesc : 1;  // TRUE: am nachfolgenden Node das PgDsc zuruecksetzen
    BOOL bResetPgBrk : 1;   // TRUE: am nachfolgenden Node das PgBreak zuruecksetzen

    BOOL SaveCntnt( const SwPosition* pStt, const SwPosition* pEnd,
                    SwTxtNode* pSttTxtNd, SwTxtNode* pEndTxtNd );
public:
    SwUndoDelete( SwPaM&, BOOL bFullPara = FALSE );
    virtual ~SwUndoDelete();
//STRIP001  virtual void Undo( SwUndoIter& );
//STRIP001  virtual void Redo( SwUndoIter& );
//STRIP001  virtual void Repeat( SwUndoIter& );
    BOOL CanGrouping( SwDoc*, const SwPaM& );

    void SetTblDelLastNd()      { bTblDelLastNd = TRUE; }

    // fuer die PageDesc/PageBreak Attribute einer Tabelle
    void SetPgBrkFlags( BOOL bPageBreak, BOOL bPageDesc )
        { bResetPgDesc = bPageDesc; bResetPgBrk = bPageBreak; }

    OUT_UNDOBJ( Delete )

    DECL_FIXEDMEMPOOL_NEWDEL(SwUndoDelete)
};


//STRIP001 class SwUndoOverwrite: public SwUndo, private SwUndoSaveCntnt
//STRIP001 {
//STRIP001  String aDelStr, aInsStr;
//STRIP001  SwRedlineSaveDatas* pRedlSaveData;
//STRIP001  ULONG nSttNode;
//STRIP001  xub_StrLen nSttCntnt;
//STRIP001  BOOL bInsChar : 1;      // kein Overwrite mehr; sondern Insert
//STRIP001  BOOL bGroup : 1;        // TRUE: ist schon eine Gruppe; wird in
//STRIP001                          //       CanGrouping() ausgwertet !!
//STRIP001 public:
//STRIP001  SwUndoOverwrite( SwDoc*, SwPosition&, sal_Unicode cIns );
//STRIP001  virtual ~SwUndoOverwrite();
//STRIP001  virtual void Undo( SwUndoIter& );
//STRIP001  virtual void Redo( SwUndoIter& );
//STRIP001  virtual void Repeat( SwUndoIter& );
//STRIP001  BOOL CanGrouping( SwDoc*, SwPosition&, sal_Unicode cIns );
//STRIP001  OUT_UNDOBJ( Overwrite )
//STRIP001 };


class SwUndoSplitNode: public SwUndo
{
    SwHistory* pHistory;
    SwRedlineData* pRedlData;
    ULONG nNode;
    xub_StrLen nCntnt;
    BOOL bTblFlag : 1;
    BOOL bChkTblStt : 1;
public:
    SwUndoSplitNode( SwDoc* pDoc, const SwPosition& rPos, BOOL bChkTbl );
    virtual ~SwUndoSplitNode();
//STRIP001  virtual void Undo( SwUndoIter& );
//STRIP001  virtual void Redo( SwUndoIter& );
//STRIP001  virtual void Repeat( SwUndoIter& );
    void SetTblFlag()       { bTblFlag = TRUE; }
    OUT_UNDOBJ( SplitNode )
};


//STRIP001 class SwUndoMove : public SwUndo, private SwUndRng, private SwUndoSaveCntnt
//STRIP001 {
//STRIP001  // nDest.. - Bereich, in den verschoben wurde (nach dem Move!)
//STRIP001  // nIns.. - Position, von der verschoben wurde und wieder die neue InsPos. ist
//STRIP001  // nMv.. Position auf die verschoben wird (vor dem Move!) ; fuers REDO
//STRIP001  ULONG nDestSttNode, nDestEndNode, nInsPosNode, nMvDestNode;
//STRIP001  xub_StrLen nDestSttCntnt, nDestEndCntnt, nInsPosCntnt, nMvDestCntnt;
//STRIP001
//STRIP001  USHORT nFtnStt;         // StartPos der Fussnoten in der History
//STRIP001
//STRIP001  BOOL bJoinNext : 1,
//STRIP001       bJoinPrev : 1,
//STRIP001       bMoveRange : 1;
//STRIP001
//STRIP001  void DelFtn( const SwPaM& );
//STRIP001 public:
//STRIP001  SwUndoMove( const SwPaM&, const SwPosition& );
//STRIP001  SwUndoMove( SwDoc* pDoc, const SwNodeRange&, const SwNodeIndex& );
//STRIP001  virtual void Undo( SwUndoIter& );
//STRIP001  virtual void Redo( SwUndoIter& );
//STRIP001  // setze den Destination-Bereich nach dem Verschieben.
//STRIP001  void SetDestRange( const SwPaM&, const SwPosition&, BOOL, BOOL );
//STRIP001  void SetDestRange( const SwNodeIndex& rStt, const SwNodeIndex& rEnd,
//STRIP001                      const SwNodeIndex& rInsPos );
//STRIP001
//STRIP001  BOOL IsMoveRange() const        { return bMoveRange; }
//STRIP001  ULONG GetEndNode() const        { return nEndNode; }
//STRIP001  ULONG GetDestSttNode() const    { return nDestSttNode; }
//STRIP001  xub_StrLen GetDestSttCntnt() const  { return nDestSttCntnt; }
//STRIP001  void AddTblMrgFlyHstry( SwHistory& rHstr );
//STRIP001
//STRIP001  OUT_UNDOBJ( Move )
//STRIP001 };


class SwUndoAttr : public SwUndo, private SwUndRng
{
    SfxItemSet aSet;                // Attribute fuers Redo
    SwHistory* pHistory;            // History fuers Undo
    SwRedlineData* pRedlData;       // Redlining
    SwRedlineSaveDatas* pRedlSaveData;
    ULONG nNdIdx;                   // fuers Redlining - Offset
    USHORT nInsFlags;               // Einfuege Flags

//STRIP001  void RemoveIdx( SwDoc& rDoc );
public:
    SwUndoAttr( const SwPaM&, const SfxItemSet&, USHORT nFlags = 0  );
    SwUndoAttr( const SwPaM&, const SfxPoolItem&, USHORT nFlags = 0 );
    virtual ~SwUndoAttr();
//STRIP001  virtual void Undo( SwUndoIter& );
//STRIP001  virtual void Redo( SwUndoIter& );
//STRIP001  virtual void Repeat( SwUndoIter& );
    SwHistory* GetHistory() { return pHistory; }
//STRIP001  void SaveRedlineData( const SwPaM& rPam, BOOL bInsCntnt );

    OUT_UNDOBJ( InsAttr )
};

//STRIP001 class SwUndoRstAttr : public SwUndo, private SwUndRng
//STRIP001 {
//STRIP001  SwHistory* pHistory;
//STRIP001  SvUShortsSort aIds;
//STRIP001  USHORT nFmtId;                  // Format-Id fuer das Redo
//STRIP001 public:
//STRIP001  SwUndoRstAttr( const SwPaM&, USHORT nFmtId );
//STRIP001  SwUndoRstAttr( const SwDoc&, const SwPosition&, USHORT nWhichId );
//STRIP001  virtual ~SwUndoRstAttr();
//STRIP001  virtual void Undo( SwUndoIter& );
//STRIP001  virtual void Redo( SwUndoIter& );
//STRIP001  virtual void Repeat( SwUndoIter& );
//STRIP001  void SetAttrs( const SvUShortsSort& rArr );
//STRIP001  SwHistory* GetHistory() { return pHistory; }
//STRIP001  OUT_UNDOBJ( ResetAttr )
//STRIP001 };


class SwUndoFmtAttr : public SwUndo
{
    friend class SwUndoDefaultAttr;
    SwFmt* pFmt;
    SfxItemSet* pOldSet;            // die alten Attribute
    ULONG nNode;
    USHORT nFmtWhich;
    BOOL bSaveDrawPt;

//STRIP001  int IsFmtInDoc( SwDoc* );       // ist das Attribut-Format noch im Doc ?
    void SaveFlyAnchor( BOOL bSaveDrawPt = FALSE );
//STRIP001  void RestoreFlyAnchor( SwUndoIter& rIter );
    void Init();

public:
    // meldet sich im Format an und sichert sich die alten Attribute
    SwUndoFmtAttr( const SfxItemSet& rOldSet, SwFmt& rFmt,
                    BOOL bSaveDrawPt = TRUE );
    SwUndoFmtAttr( const SfxPoolItem& rItem, SwFmt& rFmt,
                    BOOL bSaveDrawPt = TRUE );
    virtual ~SwUndoFmtAttr();
//STRIP001  virtual void Undo( SwUndoIter& );
//STRIP001  virtual void Redo( SwUndoIter& );
//STRIP001  virtual void Repeat( SwUndoIter& );
    OUT_UNDOBJ( InsFmtAttr )

//STRIP001  void PutAttr( const SfxPoolItem& rItem );
//STRIP001  SwFmt* GetFmt( SwDoc& rDoc );       // prueft, ob es noch im Doc ist!
};

//STRIP001 class SwUndoDontExpandFmt : public SwUndo
//STRIP001 {
//STRIP001  ULONG nNode;
//STRIP001  xub_StrLen nCntnt;
//STRIP001 public:
//STRIP001  SwUndoDontExpandFmt( const SwPosition& rPos );
//STRIP001  virtual void Undo( SwUndoIter& );
//STRIP001  virtual void Redo( SwUndoIter& );
//STRIP001  virtual void Repeat( SwUndoIter& );
//STRIP001 };

// Hilfs-Klasse, um die geaenderten Sets zu "empfangen"
struct _UndoFmtAttr : public SwClient
{
    SwUndoFmtAttr* pUndo;
    BOOL bSaveDrawPt;

    _UndoFmtAttr( SwFmt& rFmt, BOOL bSaveDrawPt = TRUE );
    virtual void Modify( SfxPoolItem*, SfxPoolItem* );
};


class SwUndoFmtColl : public SwUndo, private SwUndRng
{
    SwHistory* pHistory;
    SwFmtColl* pFmtColl;
public:
    SwUndoFmtColl( const SwPaM&, SwFmtColl* );
    virtual ~SwUndoFmtColl();
//STRIP001  virtual void Undo( SwUndoIter& );
//STRIP001  virtual void Redo( SwUndoIter& );
//STRIP001  virtual void Repeat( SwUndoIter& );
    SwHistory* GetHistory() { return pHistory; }
    OUT_UNDOBJ( SetFmtColl )
};


//STRIP001 class SwUndoMoveLeftMargin : public SwUndo, private SwUndRng
//STRIP001 {
//STRIP001  SwHistory* pHistory;
//STRIP001  BOOL bModulus;
//STRIP001 public:
//STRIP001  SwUndoMoveLeftMargin( const SwPaM&, BOOL bRight, BOOL bModulus );
//STRIP001  virtual ~SwUndoMoveLeftMargin();
//STRIP001  virtual void Undo( SwUndoIter& );
//STRIP001  virtual void Redo( SwUndoIter& );
//STRIP001  virtual void Repeat( SwUndoIter& );
//STRIP001  SwHistory* GetHistory() { return pHistory; }
//STRIP001  OUT_UNDOBJ( MoveLeftMargin )
//STRIP001 };

// Basis-Klasse fuer Insert von Dokument, Glossaries und Kopieren
//STRIP001 class SwUndoInserts : public SwUndo, public SwUndRng, private SwUndoSaveCntnt
//STRIP001 {
//STRIP001  SwTxtFmtColl *pTxtFmtColl, *pLastNdColl;
//STRIP001  SvPtrarr* pFrmFmts;
//STRIP001  SwUndos* pFlyUndos;
//STRIP001  SwRedlineData* pRedlData;
//STRIP001  BOOL bSttWasTxtNd;
//STRIP001 protected:
//STRIP001  ULONG nNdDiff;
//STRIP001  SwPosition *pPos;                   // Inhalt fuers Redo
//STRIP001  USHORT nSetPos;                     // Start in der History-Liste
//STRIP001
//STRIP001  SwUndoInserts( USHORT nUndoId, const SwPaM& );
//STRIP001 public:
//STRIP001  virtual ~SwUndoInserts();
//STRIP001
//STRIP001  virtual void Undo( SwUndoIter& );
//STRIP001  virtual void Redo( SwUndoIter& );
//STRIP001  virtual void Repeat( SwUndoIter& );
//STRIP001  // setze den Destination-Bereich nach dem Einlesen.
//STRIP001  void SetInsertRange( const SwPaM&, BOOL bScanFlys = TRUE,
//STRIP001                      BOOL bSttWasTxtNd = TRUE );
//STRIP001  OUT_UNDOBJ( Inserts )
//STRIP001 };

class SwUndoInsDoc //STRIP001 : public SwUndoInserts
{
public:
    SwUndoInsDoc( const SwPaM& ){DBG_ASSERT(0, "STRIP");} //STRIP001 SwUndoInsDoc( const SwPaM& );
//STRIP001  OUT_UNDOBJ( InsDoc )
};

//STRIP001 class SwUndoCpyDoc : public SwUndoInserts
//STRIP001 {
//STRIP001 public:
//STRIP001  SwUndoCpyDoc( const SwPaM& );
//STRIP001  OUT_UNDOBJ( Copy )
//STRIP001 };

class SwUndoInsTbl : public SwUndo
{
    String sTblNm;
    SwDDEFieldType* pDDEFldType;
    SvUShorts* pColWidth;
    SwRedlineData*  pRedlData;
    SwTableAutoFmt* pAutoFmt;
    ULONG nSttNode;
    USHORT nRows, nCols;
    USHORT nAdjust;
    USHORT nInsTblFlags;

public:
    SwUndoInsTbl( const SwPosition&, USHORT nCols, USHORT nRows,
                    USHORT eAdjust, USHORT nInsert,
                    const SwTableAutoFmt* pTAFmt, const SvUShorts* pColArr );
    virtual ~SwUndoInsTbl();
//STRIP001  virtual void Undo( SwUndoIter& );
//STRIP001  virtual void Redo( SwUndoIter& );
//STRIP001  virtual void Repeat( SwUndoIter& );
    OUT_UNDOBJ( InsTable )
};

class SwUndoTxtToTbl : public SwUndo, public SwUndRng
{
     String sTblNm;
     SvULongs* pDelBoxes;
     SwTableAutoFmt* pAutoFmt;
     SwHistory* pHistory;
     sal_Unicode cTrenner;
     USHORT nAdjust;
     USHORT nInsTblFlags;
     BOOL bSplitEnd : 1;

public:
    SwUndoTxtToTbl( const SwPaM&, sal_Unicode , USHORT, USHORT nInsert,
                    const SwTableAutoFmt* pAFmt );
    virtual ~SwUndoTxtToTbl();

//STRIP001  virtual void Undo( SwUndoIter& );
//STRIP001  virtual void Redo( SwUndoIter& );
//STRIP001  virtual void Repeat( SwUndoIter& );
//STRIP001
//STRIP001  SwHistory& GetHistory();        // wird ggfs. angelegt
//STRIP001  void AddFillBox( const SwTableBox& rBox );
//STRIP001  OUT_UNDOBJ( TextToTable )
};

//STRIP001 class SwUndoTblToTxt : public SwUndo
//STRIP001 {
//STRIP001  String sTblNm;
//STRIP001  SwDDEFieldType* pDDEFldType;
//STRIP001  _SaveTable* pTblSave;
//STRIP001  SwTblToTxtSaves* pBoxSaves;
//STRIP001  SwHistory* pHistory;
//STRIP001  ULONG nSttNd, nEndNd;
//STRIP001  USHORT nAdjust;
//STRIP001  sal_Unicode cTrenner;
//STRIP001  BOOL bCheckNumFmt : 1;
//STRIP001  BOOL bHdlnRpt : 1;
//STRIP001
//STRIP001 public:
//STRIP001  SwUndoTblToTxt( const SwTable& rTbl, sal_Unicode cCh );
//STRIP001  virtual ~SwUndoTblToTxt();
//STRIP001  virtual void Undo( SwUndoIter& );
//STRIP001  virtual void Redo( SwUndoIter& );
//STRIP001  virtual void Repeat( SwUndoIter& );
//STRIP001
//STRIP001  void SetRange( const SwNodeRange& );
//STRIP001  void AddBoxPos( SwDoc& rDoc, ULONG nNdIdx,
//STRIP001                  xub_StrLen nCntntIdx = STRING_MAXLEN);
//STRIP001  OUT_UNDOBJ( TableToText )
//STRIP001 };

//STRIP001 class SwUndoAttrTbl : public SwUndo
//STRIP001 {
//STRIP001  ULONG nSttNode;
//STRIP001  _SaveTable* pSaveTbl;
//STRIP001  BOOL bClearTabCol : 1;
//STRIP001 public:
//STRIP001  SwUndoAttrTbl( const SwTableNode& rTblNd, BOOL bClearTabCols = FALSE );
//STRIP001  virtual ~SwUndoAttrTbl();
//STRIP001  virtual void Undo( SwUndoIter& );
//STRIP001  virtual void Redo( SwUndoIter& );
//STRIP001  OUT_UNDOBJ( SetTableAttr )
//STRIP001 };

//STRIP001 class SwUndoTblAutoFmt : public SwUndo
//STRIP001 {
//STRIP001  ULONG nSttNode;
//STRIP001  _SaveTable* pSaveTbl;
//STRIP001  SwUndos* pUndos;
//STRIP001  BOOL bSaveCntntAttr;
//STRIP001
//STRIP001  void UndoRedo( BOOL bUndo, SwUndoIter& rUndoIter );
//STRIP001
//STRIP001 public:
//STRIP001  SwUndoTblAutoFmt( const SwTableNode& rTblNd, const SwTableAutoFmt& );
//STRIP001  virtual ~SwUndoTblAutoFmt();
//STRIP001  virtual void Undo( SwUndoIter& );
//STRIP001  virtual void Redo( SwUndoIter& );
//STRIP001  void SaveBoxCntnt( const SwTableBox& rBox );
//STRIP001  OUT_UNDOBJ( TableAutoFmt )
//STRIP001 };

//STRIP001 class SwUndoTblNdsChg : public SwUndo
//STRIP001 {
//STRIP001  _SaveTable* pSaveTbl;
//STRIP001  SvULongs aBoxes;
//STRIP001
//STRIP001  union {
//STRIP001      SvULongs* pNewSttNds;
//STRIP001      SwUndoSaveSections* pDelSects;
//STRIP001  } Ptrs;
//STRIP001  SvBools aMvBoxes;       // fuers SplitRow (aufgeteilte Nodes einer Box)
//STRIP001
//STRIP001  ULONG nSttNode, nCurrBox;
//STRIP001  USHORT nCount, nRelDiff, nAbsDiff, nSetColType;
//STRIP001  BOOL bFlag;
//STRIP001     BOOL bSameHeight;                   // only used for SplitRow
//STRIP001 public:
//STRIP001  SwUndoTblNdsChg( USHORT UndoId,
//STRIP001                  const SwSelBoxes& rBoxes,
//STRIP001                  const SwTableNode& rTblNd,
//STRIP001                     USHORT nCnt, BOOL bFlg, BOOL bSameHeight = FALSE );
//STRIP001
//STRIP001  // fuer SetColWidth
//STRIP001  SwUndoTblNdsChg( USHORT UndoId, const SwSelBoxes& rBoxes,
//STRIP001                  const SwTableNode& rTblNd );
//STRIP001
//STRIP001  virtual ~SwUndoTblNdsChg();
//STRIP001  virtual void Undo( SwUndoIter& );
//STRIP001  virtual void Redo( SwUndoIter& );
//STRIP001
//STRIP001  void SaveNewBoxes( const SwTableNode& rTblNd, const SwTableSortBoxes& rOld );
//STRIP001  void SaveNewBoxes( const SwTableNode& rTblNd, const SwTableSortBoxes& rOld,
//STRIP001                     const SwSelBoxes& rBoxes, const SvULongs& rNodeCnts );
//STRIP001  void SaveSection( SwStartNode* pSttNd );
//STRIP001
//STRIP001  void SetColWidthParam( ULONG nBoxIdx, USHORT nMode, USHORT nType,
//STRIP001                          SwTwips nAbsDif, SwTwips nRelDif )
//STRIP001  {
//STRIP001      nCurrBox = nBoxIdx;
//STRIP001      nCount = nMode;
//STRIP001      nSetColType = nType;
//STRIP001      nAbsDiff = (USHORT)nAbsDif;
//STRIP001      nRelDiff = (USHORT)nRelDif;
//STRIP001  }
//STRIP001  OUT_UNDOBJ( TblNodesChg )
//STRIP001 };

 class SwUndoTblMerge : public SwUndo, private SwUndRng
 {
//STRIP001  ULONG nTblNode;
//STRIP001  _SaveTable* pSaveTbl;
//STRIP001  SvULongs aBoxes, aNewSttNds;
//STRIP001  SwUndoMoves* pMoves;
    SwHistory* pHistory;

public:
    SwUndoTblMerge( const SwPaM& rTblSel );
    virtual ~SwUndoTblMerge();
//STRIP001  virtual void Undo( SwUndoIter& );
//STRIP001  virtual void Redo( SwUndoIter& );
//STRIP001
//STRIP001  void MoveBoxCntnt( SwPaM& rPam, SwPosition& rPos, const _SaveFlyArr& );
//STRIP001  void MoveBoxCntnt( SwDoc* pDoc, SwNodeRange& rRg, SwNodeIndex& rPos );
//STRIP001
//STRIP001  void SetSelBoxes( const SwSelBoxes& rBoxes );
//STRIP001
//STRIP001  void AddNewBox( ULONG nSttNdIdx )
//STRIP001      { aNewSttNds.Insert( nSttNdIdx, aNewSttNds.Count() ); }
//STRIP001
//STRIP001  void SaveCollection( const SwTableBox& rBox );
//STRIP001
//STRIP001  OUT_UNDOBJ( TblMerge )
};


//STRIP001 class SwUndoTblNumFmt : public SwUndo
//STRIP001 {
//STRIP001  SfxItemSet *pBoxSet;
//STRIP001  SwHistory* pHistory;
//STRIP001  String aStr, aNewFml;
//STRIP001
//STRIP001  ULONG nFmtIdx, nNewFmtIdx;
//STRIP001  double fNum, fNewNum;
//STRIP001  ULONG nNode;
//STRIP001
//STRIP001  BOOL bNewFmt : 1;
//STRIP001  BOOL bNewFml : 1;
//STRIP001  BOOL bNewValue : 1;
//STRIP001
//STRIP001 public:
//STRIP001  SwUndoTblNumFmt( const SwTableBox& rBox, const SfxItemSet* pNewSet = 0 );
//STRIP001  virtual ~SwUndoTblNumFmt();
//STRIP001  virtual void Undo( SwUndoIter& );
//STRIP001  virtual void Redo( SwUndoIter& );
//STRIP001
//STRIP001  void SetNumFmt( ULONG nNewFmtIdx, const double& rNewNumber )
//STRIP001          { nFmtIdx = nNewFmtIdx; fNum = rNewNumber; }
//STRIP001  void SetBox( const SwTableBox& rBox );
//STRIP001  OUT_UNDOBJ( TblNumFmt )
//STRIP001 };

class _UndoTblCpyTbl_Entries;

//STRIP001 class SwUndoTblCpyTbl : public SwUndo
//STRIP001 {
//STRIP001  _UndoTblCpyTbl_Entries* pArr;
//STRIP001  SwUndoTblNdsChg* pInsRowUndo;
//STRIP001 public:
//STRIP001  SwUndoTblCpyTbl();
//STRIP001  virtual ~SwUndoTblCpyTbl();
//STRIP001  virtual void Undo( SwUndoIter& );
//STRIP001  virtual void Redo( SwUndoIter& );
//STRIP001
//STRIP001  void AddBoxBefore( const SwTableBox& rBox, BOOL bDelCntnt );
//STRIP001  void AddBoxAfter( const SwTableBox& rBox, BOOL bDelCntnt );
//STRIP001
//STRIP001  BOOL IsEmpty() const;
//STRIP001  BOOL InsertRow( SwTable& rTbl, const SwSelBoxes& rBoxes, USHORT nCnt );
//STRIP001  OUT_UNDOBJ( TblCpyTbl )
//STRIP001 };

class SwUndoCpyTbl : public SwUndo
{
    SwUndoDelete* pDel;
    ULONG nTblNode;
public:
    SwUndoCpyTbl();
    virtual ~SwUndoCpyTbl();
    virtual void Undo( SwUndoIter& );
    virtual void Redo( SwUndoIter& );

    void SetTableSttIdx( ULONG nIdx )           { nTblNode = nIdx; }
    OUT_UNDOBJ( CpyTbl )
};

//STRIP001 class SwUndoSplitTbl : public SwUndo
//STRIP001 {
//STRIP001  ULONG nTblNode, nOffset;
//STRIP001  _SaveTable* pSavTbl;
//STRIP001  SwHistory* pHistory;
//STRIP001  USHORT nMode, nFmlEnd;
//STRIP001  BOOL bCalcNewSize;
//STRIP001 public:
//STRIP001  SwUndoSplitTbl( const SwTableNode& rTblNd, USHORT nMode, BOOL bCalcNewSize );
//STRIP001  virtual ~SwUndoSplitTbl();
//STRIP001  virtual void Undo( SwUndoIter& );
//STRIP001  virtual void Redo( SwUndoIter& );
//STRIP001  virtual void Repeat( SwUndoIter& );
//STRIP001
//STRIP001  void SetTblNodeOffset( ULONG nIdx )     { nOffset = nIdx - nTblNode; }
//STRIP001  SwHistory* GetHistory()                 { return pHistory; }
//STRIP001  void SaveFormula( SwHistory& rHistory );
//STRIP001 };

//STRIP001 class SwUndoMergeTbl : public SwUndo
//STRIP001 {
//STRIP001  String aName;
//STRIP001  ULONG nTblNode;
//STRIP001  _SaveTable* pSavTbl, *pSavHdl;
//STRIP001  SwHistory* pHistory;
//STRIP001  USHORT nMode;
//STRIP001  BOOL bWithPrev;
//STRIP001 public:
//STRIP001  SwUndoMergeTbl( const SwTableNode& rTblNd, const SwTableNode& rDelTblNd,
//STRIP001                  BOOL bWithPrev, USHORT nMode );
//STRIP001  virtual ~SwUndoMergeTbl();
//STRIP001  virtual void Undo( SwUndoIter& );
//STRIP001  virtual void Redo( SwUndoIter& );
//STRIP001  virtual void Repeat( SwUndoIter& );
//STRIP001
//STRIP001  SwHistory* GetHistory()                 { return pHistory; }
//STRIP001  void SaveFormula( SwHistory& rHistory );
//STRIP001 };


class SwUndoBookmark : public SwUndo
{
    SwHstryBookmark* pHBookmark;
protected:
    SwUndoBookmark( USHORT nUndoId, const SwBookmark& );

//STRIP001  void SetInDoc( SwDoc* );
//STRIP001  void ResetInDoc( SwDoc* );

public:
    virtual ~SwUndoBookmark();
};


//STRIP001 class SwUndoDelBookmark : public SwUndoBookmark
//STRIP001 {
//STRIP001 public:
//STRIP001  SwUndoDelBookmark( const SwBookmark& );
//STRIP001  virtual void Undo( SwUndoIter& );
//STRIP001  virtual void Redo( SwUndoIter& );
//STRIP001  OUT_UNDOBJ( DelBookmark )
//STRIP001 };

class SwUndoInsBookmark : public SwUndoBookmark
{
public:
    SwUndoInsBookmark( const SwBookmark& );
//STRIP001  virtual void Undo( SwUndoIter& );
//STRIP001  virtual void Redo( SwUndoIter& );
    OUT_UNDOBJ( InsBookmark )
};


/*--------------------------------------------------------------------
    Beschreibung: Undo auf Sorting
 --------------------------------------------------------------------*/

//STRIP001 struct SwSortUndoElement
//STRIP001 {
//STRIP001  union {
//STRIP001      struct {
//STRIP001          ULONG nKenn;
//STRIP001          ULONG nSource, nTarget;
//STRIP001      } TXT;
//STRIP001      struct {
//STRIP001          String *pSource, *pTarget;
//STRIP001      } TBL;
//STRIP001  } SORT_TXT_TBL;
//STRIP001
//STRIP001  SwSortUndoElement( const String& aS, const String& aT )
//STRIP001  {
//STRIP001      SORT_TXT_TBL.TBL.pSource = new String( aS );
//STRIP001      SORT_TXT_TBL.TBL.pTarget = new String( aT );
//STRIP001  }
//STRIP001  SwSortUndoElement( ULONG nS, ULONG nT )
//STRIP001  {
//STRIP001      SORT_TXT_TBL.TXT.nSource = nS;
//STRIP001      SORT_TXT_TBL.TXT.nTarget = nT;
//STRIP001      SORT_TXT_TBL.TXT.nKenn   = 0xffffffff;
//STRIP001  }
//STRIP001  ~SwSortUndoElement();
//STRIP001 };

//STRIP001 SV_DECL_PTRARR_DEL(SwSortList, SwSortUndoElement*, 10,30)
//STRIP001 SV_DECL_PTRARR(SwUndoSortList, SwNodeIndex*, 10,30)

//STRIP001 class SwUndoSort : public SwUndo, private SwUndRng
//STRIP001 {
//STRIP001  SwSortOptions*  pSortOpt;       // die Optionen mit den Sortier-Kriterien
//STRIP001  SwSortList      aSortList;
//STRIP001  SwUndoAttrTbl*  pUndoTblAttr;
//STRIP001  SwRedlineData*  pRedlData;
//STRIP001  ULONG           nTblNd;
//STRIP001
//STRIP001  void RemoveIdx( SwPaM& rPam );
//STRIP001 public:
//STRIP001  SwUndoSort( const SwPaM&, const SwSortOptions& );
//STRIP001  SwUndoSort( ULONG nStt, ULONG nEnd, const SwTableNode&,
//STRIP001              const SwSortOptions&, BOOL bSaveTable );
//STRIP001  virtual ~SwUndoSort();
//STRIP001
//STRIP001  virtual void Undo( SwUndoIter& );
//STRIP001  virtual void Redo( SwUndoIter& );
//STRIP001  virtual void Repeat( SwUndoIter& );
//STRIP001
//STRIP001  void Insert( const String& rOrgPos, const String& rNewPos );
//STRIP001  void Insert( ULONG nOrgPos, ULONG nNewPos );
//STRIP001
//STRIP001  OUT_UNDOBJ( Sort )
//STRIP001 };



//--------------------------------------------------------------------

class SwUndoFlyBase : public SwUndo, private SwUndoSaveSection
{
protected:
    SwFrmFmt* pFrmFmt;                  // das gespeicherte FlyFormat
    ULONG nNdPgPos;
    xub_StrLen nCntPos;                 // Seite/am Absatz/im Absatz
    USHORT nRndId;
    BOOL bDelFmt;                       // loesche das gespeicherte Format

//STRIP001  void InsFly( SwUndoIter&, BOOL bShowSel = TRUE );
//STRIP001  void DelFly( SwDoc* );

    SwUndoFlyBase( SwFrmFmt* pFormat, USHORT nUndoId );

    SwNodeIndex* GetMvSttIdx() const { return SwUndoSaveSection::GetMvSttIdx(); }
    ULONG GetMvNodeCnt() const { return SwUndoSaveSection::GetMvNodeCnt(); }

public:
    virtual ~SwUndoFlyBase();

//STRIP001  virtual void Undo( SwUndoIter& ) = 0;
//STRIP001  virtual void Redo( SwUndoIter& ) = 0;
    OUT_UNDOBJ( FlyBase )
};

class SwUndoInsLayFmt : public SwUndoFlyBase
{
public:
    SwUndoInsLayFmt( SwFrmFmt* pFormat );

//STRIP001  virtual void Undo( SwUndoIter& );
//STRIP001  virtual void Redo( SwUndoIter& );
//STRIP001  virtual void Repeat( SwUndoIter& );
    OUT_UNDOBJ( InsLayFmt )
};

class SwUndoDelLayFmt : public SwUndoFlyBase
{
    BOOL bShowSelFrm;
public:
    SwUndoDelLayFmt( SwFrmFmt* pFormat );

//STRIP001  virtual void Undo( SwUndoIter& );
//STRIP001  virtual void Redo( SwUndoIter& );
//STRIP001  void Redo();        // Schnittstelle fuers Rollback

//STRIP001  void ChgShowSel( BOOL bNew ) { bShowSelFrm = bNew; }
//STRIP001  BOOL GetShowSel() const { return bShowSelFrm; }
//STRIP001  OUT_UNDOBJ( DelLayFmt )
};


class SwUndoSetFlyFmt : public SwUndo, public SwClient
{
    SwFrmFmt* pFrmFmt;                  // das gespeicherte FlyFormat
    SwFrmFmt* pOldFmt;                  // die alte Fly Vorlage
    SwFrmFmt* pNewFmt;                  // die neue Fly Vorlage
    SfxItemSet* pItemSet;               // die zurueck-/ gesetzten Attribute
    ULONG nOldNode, nNewNode;
    xub_StrLen nOldCntnt, nNewCntnt;
    USHORT nOldAnchorTyp, nNewAnchorTyp;
    BOOL bAnchorChgd;

//STRIP001  void PutAttr( USHORT nWhich, const SfxPoolItem* pItem );
//STRIP001  void Modify( SfxPoolItem*, SfxPoolItem* );
//STRIP001  void GetAnchor( SwFmtAnchor& rAnhor, ULONG nNode, xub_StrLen nCntnt );

public:
    SwUndoSetFlyFmt( SwFrmFmt& rFlyFmt, SwFrmFmt& rNewFrmFmt );
    virtual ~SwUndoSetFlyFmt();

//STRIP001  virtual void Undo( SwUndoIter& );
//STRIP001  virtual void Redo( SwUndoIter& );
};

//--------------------------------------------------------------------

class _UnReplaceData;
SV_DECL_PTRARR_DEL( _UnReplaceDatas, _UnReplaceData*, 10, 25 )//STRIP008 ;

//STRIP001 class SwUndoReplace : public SwUndo
//STRIP001 {
//STRIP001  friend class SwDoc;
//STRIP001
//STRIP001  BOOL bOldIterFlag;      // Status vom Undo-Iter vorm 1. Aufruf
//STRIP001  USHORT nAktPos;         // fuer GetUndoRange und Undo/Redo
//STRIP001  _UnReplaceDatas aArr;
//STRIP001  SwRedlineData* pRedlData;
//STRIP001
//STRIP001 public:
//STRIP001  SwUndoReplace();
//STRIP001  virtual ~SwUndoReplace();
//STRIP001  virtual void Undo( SwUndoIter& );
//STRIP001  virtual void Redo( SwUndoIter& );
//STRIP001
//STRIP001  void AddEntry( const SwPaM& rPam, const String& rInsert, BOOL bRegExp );
//STRIP001  void SetEntryEnd( const SwPaM& rPam );
//STRIP001
//STRIP001  BOOL IsFull() const
//STRIP001      { return ((USHRT_MAX / sizeof( void* )) - 50 ) < aArr.Count(); }
//STRIP001
//STRIP001  OUT_UNDOBJ( Replace )
//STRIP001 };


//--------------------------------------------------------------------


//STRIP001 class SwUndoTblHeadline : public SwUndo
//STRIP001 {
//STRIP001  ULONG nTblNd;
//STRIP001  BOOL bOldHeadline;
//STRIP001 public:
//STRIP001  SwUndoTblHeadline( const SwTable&, BOOL bOldHdl );
//STRIP001  virtual void Undo( SwUndoIter& );
//STRIP001  virtual void Redo( SwUndoIter& );
//STRIP001  virtual void Repeat( SwUndoIter& );
//STRIP001  OUT_UNDOBJ( SwUndoTblHeadline )
//STRIP001 };


//------------ Undo von Insert-/Delete-Sections ----------------------

class SwUndoInsSection : public SwUndo, private SwUndRng
{
    SwHistory* pHistory;
    SwSection* pSection;
    SwRedlineData* pRedlData;
    SfxItemSet* pAttr;
    ULONG nSectNodePos;
    BOOL bSplitAtStt : 1;
    BOOL bSplitAtEnd : 1;
    BOOL bUpdateFtn : 1;

//STRIP001  void Join( SwDoc& rDoc, ULONG nNode );

public:
    SwUndoInsSection( const SwPaM&, const SwSection&,
                        const SfxItemSet* pSet );
    virtual ~SwUndoInsSection();
//STRIP001  virtual void Undo( SwUndoIter& );
//STRIP001  virtual void Redo( SwUndoIter& );
//STRIP001  virtual void Repeat( SwUndoIter& );
    OUT_UNDOBJ( SwUndoInsSection )

    void SetSectNdPos( ULONG nPos )         { nSectNodePos = nPos; }
    void SaveSplitNode( SwTxtNode* pTxtNd, BOOL bAtStt );
    void SetUpdtFtnFlag( BOOL bFlag )       { bUpdateFtn = bFlag; }
};

//STRIP001 class SwUndoDelSection : public SwUndo
//STRIP001 {
//STRIP001  ULONG nSttNd, nEndNd;
//STRIP001  SwSection* pSection;
//STRIP001  SfxItemSet* pAttr;
//STRIP001 public:
//STRIP001  SwUndoDelSection( const SwSectionFmt& );
//STRIP001  virtual ~SwUndoDelSection();
//STRIP001  virtual void Undo( SwUndoIter& );
//STRIP001  virtual void Redo( SwUndoIter& );
//STRIP001  OUT_UNDOBJ( SwUndoDelSection )
//STRIP001 };

class SwUndoChgSection : public SwUndo
{
    ULONG nSttNd;
    SwSection* pSection;
    SfxItemSet* pAttr;
    BOOL bOnlyAttrChgd;
public:
    SwUndoChgSection( const SwSectionFmt&, BOOL bOnlyAttrChgd );
    virtual ~SwUndoChgSection();
//STRIP001  virtual void Undo( SwUndoIter& );
//STRIP001  virtual void Redo( SwUndoIter& );
//STRIP001  OUT_UNDOBJ( SwUndoChgSection )
};

class SwUndoChgSectPsswd : public SwUndo
{
    ::com::sun::star::uno::Sequence <sal_Int8> aPasswd;
    ULONG nSectNd;
public:
    SwUndoChgSectPsswd(
                const ::com::sun::star::uno::Sequence <sal_Int8> & rOld,
                const SwSectionNode* pSectNd = 0 );
    virtual void Undo( SwUndoIter& );
    virtual void Redo( SwUndoIter& );
    OUT_UNDOBJ( SwUndoChgSectPsswd )
};

//------------ Undo von verschieben/stufen von Gliederung ----------------

//STRIP001 class SwUndoOutlineLeftRight : public SwUndo, private SwUndRng
//STRIP001 {
//STRIP001  short nOffset;
//STRIP001 public:
//STRIP001  SwUndoOutlineLeftRight( const SwPaM& rPam, short nOffset );
//STRIP001  virtual void Undo( SwUndoIter& );
//STRIP001  virtual void Redo( SwUndoIter& );
//STRIP001  virtual void Repeat( SwUndoIter& );
//STRIP001  OUT_UNDOBJ( SwUndoOutlineLeftRight )
//STRIP001 };

//--------------------------------------------------------------------

class SwUndoDefaultAttr : public SwUndo
{
    SfxItemSet* pOldSet;            // die alten Attribute
    SvxTabStopItem* pTabStop;
public:
    // meldet sich im Format an und sichert sich die alten Attribute
    SwUndoDefaultAttr( const SfxItemSet& rOldSet );
    virtual ~SwUndoDefaultAttr();
//STRIP001  virtual void Undo( SwUndoIter& );
//STRIP001  virtual void Redo( SwUndoIter& );
    OUT_UNDOBJ( DefaultAttr )
};

//--------------------------------------------------------------------
// ---------- Undo fuer Numerierung ----------------------------------

class SwUndoInsNum : public SwUndo, private SwUndRng
{
    SwNumRule aNumRule;
    SwHistory* pHistory;
    ULONG nSttSet;
    SwNumRule* pOldNumRule;
    String sReplaceRule;
    USHORT nLRSavePos;
public:
    SwUndoInsNum( const SwPaM& rPam, const SwNumRule& rRule );
    SwUndoInsNum( const SwNumRule& rOldRule, const SwNumRule& rNewRule );
    SwUndoInsNum( const SwPosition& rPos, const SwNumRule& rRule,
                            const String& rReplaceRule );
    virtual ~SwUndoInsNum();
//STRIP001  virtual void Undo( SwUndoIter& );
//STRIP001  virtual void Redo( SwUndoIter& );
//STRIP001  virtual void Repeat( SwUndoIter& );

//STRIP001  SwHistory* GetHistory();        // wird ggfs. neu angelegt!
    void SetSttNum( ULONG nNdIdx ) { nSttSet = nNdIdx; }
//STRIP001  void SaveOldNumRule( const SwNumRule& rOld );

//STRIP001  void SetLRSpaceEndPos();

    OUT_UNDOBJ( InsNum )
};

//STRIP001 class SwUndoDelNum : public SwUndo, private SwUndRng
//STRIP001 {
//STRIP001  SvULongs aNodeIdx;
//STRIP001  SvBytes aLevels;
//STRIP001  SvBools aRstLRSpaces;
//STRIP001  SwHistory* pHistory;
//STRIP001 public:
//STRIP001  SwUndoDelNum( const SwPaM& rPam );
//STRIP001  virtual ~SwUndoDelNum();
//STRIP001  virtual void Undo( SwUndoIter& );
//STRIP001  virtual void Redo( SwUndoIter& );
//STRIP001  virtual void Repeat( SwUndoIter& );
//STRIP001
//STRIP001  void AddNode( const SwTxtNode& rNd, BOOL bResetLRSpace );
//STRIP001  SwHistory* GetHistory() { return pHistory; }
//STRIP001
//STRIP001  OUT_UNDOBJ( DelNum )
//STRIP001 };

//STRIP001 class SwUndoMoveNum : public SwUndo, private SwUndRng
//STRIP001 {
//STRIP001  ULONG nNewStt;
//STRIP001  long nOffset;
//STRIP001 public:
//STRIP001  SwUndoMoveNum( const SwPaM& rPam, long nOffset, BOOL bIsOutlMv = FALSE );
//STRIP001  virtual void Undo( SwUndoIter& );
//STRIP001  virtual void Redo( SwUndoIter& );
//STRIP001  virtual void Repeat( SwUndoIter& );
//STRIP001  void SetStartNode( ULONG nValue ) { nNewStt = nValue; }
//STRIP001  OUT_UNDOBJ( MoveNum )
//STRIP001 };

class SwUndoNumUpDown : public SwUndo, private SwUndRng
{
    short nOffset;
public:
    SwUndoNumUpDown( const SwPaM& rPam, short nOffset );
//STRIP001  virtual void Undo( SwUndoIter& );
//STRIP001  virtual void Redo( SwUndoIter& );
//STRIP001  virtual void Repeat( SwUndoIter& );
    OUT_UNDOBJ( NumUpDown )
};

//STRIP001 class SwUndoNumOrNoNum : public SwUndo
//STRIP001 {
//STRIP001  ULONG nIdx;
//STRIP001  BOOL bDel : 1;
//STRIP001  BOOL bOutline : 1;
//STRIP001 public:
//STRIP001  SwUndoNumOrNoNum( const SwNodeIndex& rIdx, BOOL bDelete, BOOL bOutline );
//STRIP001  virtual void Undo( SwUndoIter& );
//STRIP001  virtual void Redo( SwUndoIter& );
//STRIP001  virtual void Repeat( SwUndoIter& );
//STRIP001  OUT_UNDOBJ( NumOrNoNum )
//STRIP001 };

class SwUndoNumRuleStart : public SwUndo
{
    ULONG nIdx;
    USHORT nOldStt, nNewStt;
    BOOL bSetSttValue : 1;
    BOOL bFlag : 1;
public:
    SwUndoNumRuleStart( const SwPosition& rPos, BOOL bDelete );
    SwUndoNumRuleStart( const SwPosition& rPos, USHORT nStt );
//STRIP001  virtual void Undo( SwUndoIter& );
//STRIP001  virtual void Redo( SwUndoIter& );
//STRIP001  virtual void Repeat( SwUndoIter& );
    OUT_UNDOBJ( NumRuleStart )
};

//--------------------------------------------------------------------
// ---------- Undo fuer DrawObjecte ----------------------------------

//STRIP001 class SwSdrUndo : public SwUndo
//STRIP001 {
//STRIP001  SdrUndoAction* pSdrUndo;
//STRIP001  SdrMarkList* pMarkList; // MarkList for all selected SdrObjects
//STRIP001 public:
//STRIP001  SwSdrUndo( SdrUndoAction* , const SdrMarkList* pMarkList );
//STRIP001  virtual ~SwSdrUndo();
//STRIP001  virtual void Undo( SwUndoIter& );
//STRIP001  virtual void Redo( SwUndoIter& );
//STRIP001
//STRIP001  String GetComment() const;
//STRIP001 };

//STRIP001 class SwUndoDrawGroup : public SwUndo
//STRIP001 {
//STRIP001  SwUndoGroupObjImpl* pObjArr;
//STRIP001  USHORT nSize;
//STRIP001  BOOL bDelFmt;
//STRIP001
//STRIP001 public:
//STRIP001  SwUndoDrawGroup( USHORT nCnt );
//STRIP001  virtual ~SwUndoDrawGroup();
//STRIP001  virtual void Undo( SwUndoIter& );
//STRIP001  virtual void Redo( SwUndoIter& );
//STRIP001
//STRIP001  void AddObj( USHORT nPos, SwDrawFrmFmt*, SdrObject* );
//STRIP001  void SetGroupFmt( SwDrawFrmFmt* );
//STRIP001 };

//STRIP001 class SwUndoDrawUnGroup : public SwUndo
//STRIP001 {
//STRIP001  SwUndoGroupObjImpl* pObjArr;
//STRIP001  USHORT nSize;
//STRIP001  BOOL bDelFmt;
//STRIP001
//STRIP001 public:
//STRIP001  SwUndoDrawUnGroup( SdrObjGroup* );
//STRIP001  virtual ~SwUndoDrawUnGroup();
//STRIP001  virtual void Undo( SwUndoIter& );
//STRIP001  virtual void Redo( SwUndoIter& );
//STRIP001
//STRIP001  void AddObj( USHORT nPos, SwDrawFrmFmt* );
//STRIP001 };

//STRIP001 class SwUndoDrawDelete : public SwUndo
//STRIP001 {
//STRIP001  SwUndoGroupObjImpl* pObjArr;
//STRIP001  SdrMarkList* pMarkLst;  // MarkList for all selected SdrObjects
//STRIP001  USHORT nSize;
//STRIP001  BOOL bDelFmt;
//STRIP001
//STRIP001 public:
//STRIP001  SwUndoDrawDelete( USHORT nCnt );
//STRIP001  virtual ~SwUndoDrawDelete();
//STRIP001  virtual void Undo( SwUndoIter& );
//STRIP001  virtual void Redo( SwUndoIter& );
//STRIP001
//STRIP001  void AddObj( USHORT nPos, SwDrawFrmFmt*, const SdrMark& );
//STRIP001 };

//--------------------------------------------------------------------

//STRIP001 class SwUndoReRead : public SwUndo
//STRIP001 {
//STRIP001  Graphic *pGrf;
//STRIP001  String *pNm, *pFltr;
//STRIP001  ULONG nPos;
//STRIP001  USHORT nMirr;
//STRIP001
//STRIP001  void SaveGraphicData( const SwGrfNode& );
//STRIP001  void SetAndSave( SwUndoIter& );
//STRIP001
//STRIP001 public:
//STRIP001  SwUndoReRead( const SwPaM& rPam, const SwGrfNode& pGrfNd );
//STRIP001  virtual ~SwUndoReRead();
//STRIP001
//STRIP001  virtual void Undo( SwUndoIter& );
//STRIP001  virtual void Redo( SwUndoIter& );
//STRIP001 };

//--------------------------------------------------------------------

//STRIP001 class SwUndoInsertLabel : public SwUndo
//STRIP001 {
//STRIP001  union {
//STRIP001      struct {
//STRIP001          // fuer NoTxtFrms
//STRIP001          SwUndoInsLayFmt* pUndoFly;
//STRIP001          SwUndoFmtAttr* pUndoAttr;
//STRIP001      } OBJECT;
//STRIP001      struct {
//STRIP001          // fuer Tabelle/TextRahmen
//STRIP001          SwUndoDelete* pUndoInsNd;
//STRIP001          ULONG nNode;
//STRIP001      } NODE;
//STRIP001  };
//STRIP001
//STRIP001  String sText;
//STRIP001  Point aPos;                 // fuer Zeichen-Objekte
//STRIP001  USHORT nFldId;
//STRIP001  SwLabelType eType;
//STRIP001  BYTE nLayerId;              // fuer Zeichen-Objekte
//STRIP001  BOOL bBefore        :1;
//STRIP001  BOOL bUndoKeep      :1;
//STRIP001  BOOL bCpyBrd        :1;
//STRIP001
//STRIP001 public:
//STRIP001  SwUndoInsertLabel( const SwLabelType eTyp, const String &rText,
//STRIP001                      const BOOL bBefore, const USHORT nId,
//STRIP001                      const BOOL bCpyBrd );
//STRIP001  virtual ~SwUndoInsertLabel();
//STRIP001
//STRIP001  virtual void Undo( SwUndoIter& );
//STRIP001  virtual void Redo( SwUndoIter& );
//STRIP001  virtual void Repeat( SwUndoIter& );
//STRIP001
//STRIP001  void SetNodePos( ULONG nNd )
//STRIP001      { if( LTYPE_OBJECT != eType ) NODE.nNode = nNd; }
//STRIP001
//STRIP001  void SetUndoKeep()  { bUndoKeep = TRUE; }
//STRIP001  void SetFlys( SwFrmFmt& rOldFly, SfxItemSet& rChgSet, SwFrmFmt& rNewFly );
//STRIP001  void SetDrawObj( const Point& rPos, BYTE nLayerId );
//STRIP001 };

//--------------------------------------------------------------------

class SwUndoChgFtn : public SwUndo, private SwUndRng
{
    SwHistory* pHistory;
    String sTxt;
    USHORT nNo;
    BOOL bEndNote;
public:
    SwUndoChgFtn( const SwPaM& rRange, const String& rTxt,
                    USHORT nNum, BOOL bIsEndNote );
    virtual ~SwUndoChgFtn();

//STRIP001  virtual void Undo( SwUndoIter& );
//STRIP001  virtual void Redo( SwUndoIter& );
//STRIP001  virtual void Repeat( SwUndoIter& );

    SwHistory* GetHistory() { return pHistory; }
};

//STRIP001 class SwUndoFtnInfo : public SwUndo
//STRIP001 {
//STRIP001  SwFtnInfo *pFtnInfo;
//STRIP001
//STRIP001 public:
//STRIP001  SwUndoFtnInfo( const SwFtnInfo &rInfo );
//STRIP001  virtual ~SwUndoFtnInfo();
//STRIP001
//STRIP001  virtual void Undo( SwUndoIter& );
//STRIP001  virtual void Redo( SwUndoIter& );
//STRIP001 };

//STRIP001 class SwUndoEndNoteInfo : public SwUndo
//STRIP001 {
//STRIP001  SwEndNoteInfo *pEndNoteInfo;
//STRIP001
//STRIP001 public:
//STRIP001  SwUndoEndNoteInfo( const SwEndNoteInfo &rInfo );
//STRIP001  virtual ~SwUndoEndNoteInfo();
//STRIP001
//STRIP001  virtual void Undo( SwUndoIter& );
//STRIP001  virtual void Redo( SwUndoIter& );
//STRIP001 };


//--------------------------------------------------------------------

//STRIP001 struct _UndoTransliterate_Data;
//STRIP001 class SwUndoTransliterate : public SwUndo, public SwUndRng
//STRIP001 {
//STRIP001  _UndoTransliterate_Data *pData, *pLastData;
//STRIP001  sal_uInt32 nType;
//STRIP001
//STRIP001 public:
//STRIP001  SwUndoTransliterate( const SwPaM& rPam,
//STRIP001                          const utl::TransliterationWrapper& rTrans );
//STRIP001  virtual ~SwUndoTransliterate();
//STRIP001
//STRIP001  virtual void Undo( SwUndoIter& rUndoIter );
//STRIP001  virtual void Redo( SwUndoIter& rUndoIter );
//STRIP001  virtual void Repeat( SwUndoIter& rUndoIter );
//STRIP001
//STRIP001  void AddChanges( const SwTxtNode& rTNd, xub_StrLen nStart, xub_StrLen nLen,
//STRIP001                  ::com::sun::star::uno::Sequence <long>& rOffsets );
//STRIP001  BOOL HasData() const {return 0 != pData; }
//STRIP001 };

//--------------------------------------------------------------------

//STRIP001 class SwUndoRedline : public SwUndo, public SwUndRng
//STRIP001 {
//STRIP001 protected:
//STRIP001  SwRedlineData* pRedlData;
//STRIP001  SwRedlineSaveDatas* pRedlSaveData;
//STRIP001  USHORT nUserId;
//STRIP001  BOOL bHiddenRedlines;
//STRIP001
//STRIP001  virtual void _Undo( SwUndoIter& );
//STRIP001  virtual void _Redo( SwUndoIter& );
//STRIP001
//STRIP001 public:
//STRIP001  SwUndoRedline( USHORT nUserId, const SwPaM& rRange );
//STRIP001  virtual ~SwUndoRedline();
//STRIP001  virtual void Undo( SwUndoIter& );
//STRIP001  virtual void Redo( SwUndoIter& );
//STRIP001
//STRIP001  USHORT GetUserId() const { return nUserId; }
//STRIP001  USHORT GetRedlSaveCount() const
//STRIP001      { return pRedlSaveData ? pRedlSaveData->Count() : 0; }
//STRIP001 };

//STRIP001 class SwUndoRedlineDelete : public SwUndoRedline
//STRIP001 {
//STRIP001  BOOL bCanGroup : 1;
//STRIP001  BOOL bIsDelim : 1;
//STRIP001  BOOL bIsBackspace : 1;
//STRIP001
//STRIP001  virtual void _Undo( SwUndoIter& );
//STRIP001  virtual void _Redo( SwUndoIter& );
//STRIP001
//STRIP001 public:
//STRIP001  SwUndoRedlineDelete( const SwPaM& rRange, USHORT nUserId = 0 );
//STRIP001
//STRIP001  BOOL CanGrouping( const SwUndoRedlineDelete& rPrev );
//STRIP001 };

//STRIP001 class SwUndoRedlineSort : public SwUndoRedline
//STRIP001 {
//STRIP001  SwSortOptions* pOpt;
//STRIP001  ULONG nSaveEndNode, nOffset;
//STRIP001  xub_StrLen nSaveEndCntnt;
//STRIP001
//STRIP001  virtual void _Undo( SwUndoIter& );
//STRIP001  virtual void _Redo( SwUndoIter& );
//STRIP001
//STRIP001 public:
//STRIP001  SwUndoRedlineSort( const SwPaM& rRange, const SwSortOptions& rOpt );
//STRIP001  virtual ~SwUndoRedlineSort();
//STRIP001  virtual void Repeat( SwUndoIter& );
//STRIP001
//STRIP001  void SetSaveRange( const SwPaM& rRange );
//STRIP001  void SetOffset( const SwNodeIndex& rIdx );
//STRIP001 };

//STRIP001 class SwUndoAcceptRedline : public SwUndoRedline
//STRIP001 {
//STRIP001  virtual void _Redo( SwUndoIter& );
//STRIP001 public:
//STRIP001  SwUndoAcceptRedline( const SwPaM& rRange );
//STRIP001  virtual void Repeat( SwUndoIter& );
//STRIP001 };

//STRIP001 class SwUndoRejectRedline : public SwUndoRedline
//STRIP001 {
//STRIP001  virtual void _Redo( SwUndoIter& );
//STRIP001 public:
//STRIP001  SwUndoRejectRedline( const SwPaM& rRange );
//STRIP001  virtual void Repeat( SwUndoIter& );
//STRIP001 };

//--------------------------------------------------------------------

//STRIP001 class SwUndoCompDoc : public SwUndo, public SwUndRng
//STRIP001 {
//STRIP001  SwRedlineData* pRedlData;
//STRIP001  SwUndoDelete* pUnDel, *pUnDel2;
//STRIP001  SwRedlineSaveDatas* pRedlSaveData;
//STRIP001  BOOL bInsert;
//STRIP001 public:
//STRIP001  SwUndoCompDoc( const SwPaM& rRg, BOOL bIns );
//STRIP001  SwUndoCompDoc( const SwRedline& rRedl );
//STRIP001
//STRIP001  virtual ~SwUndoCompDoc();
//STRIP001  virtual void Undo( SwUndoIter& );
//STRIP001  virtual void Redo( SwUndoIter& );
//STRIP001 };


//--------------------------------------------------------------------

// Object der als Iterator durch die Undo-Liste laeuft, bis die
// letze oder die angegebene Klammerung/Id erreicht ist.

//STRIP001 class SwUndoIter
//STRIP001 {
//STRIP001  friend class SwDoc;     // um im SwDoc::Undo  bWeiter zu stezen
//STRIP001  friend void SwUndoEnd::Undo( SwUndoIter& );
//STRIP001  friend void SwUndoStart::Undo( SwUndoIter& );
//STRIP001  friend void SwUndoEnd::Redo( SwUndoIter& );
//STRIP001  friend void SwUndoStart::Redo( SwUndoIter& );
//STRIP001  friend void SwUndoEnd::Repeat( SwUndoIter& );
//STRIP001  friend void SwUndoStart::Repeat( SwUndoIter& );
//STRIP001  friend void SwUndoReplace::Undo( SwUndoIter& );
//STRIP001  friend void SwUndoReplace::Redo( SwUndoIter& );
//STRIP001
//STRIP001  USHORT nUndoId;
//STRIP001  USHORT nEndCnt;
//STRIP001  BOOL bWeiter : 1;
//STRIP001  BOOL bUpdateAttr : 1;   // Setze das GCAttr an der CursorShell
//STRIP001
//STRIP001 public:
//STRIP001  SwPaM * pAktPam;        // Member fuer das Undo
//STRIP001  SwUndo* pLastUndoObj;   // fuers Redo, das vorherige UndoObj.
//STRIP001  SwFrmFmt* pSelFmt;      // ggfs. das Format Rahmen/Object-Selektionen
//STRIP001  SdrMarkList* pMarkList; // MarkList for all selected SdrObjects
//STRIP001
//STRIP001  SwUndoIter( SwPaM * pPam, USHORT nId = 0 );
//STRIP001
//STRIP001  BOOL IsNextUndo() const             { return bWeiter; }
//STRIP001  BOOL IsUpdateAttr() const           { return bUpdateAttr; }
//STRIP001  void SetUpdateAttr( BOOL bNew )     { bUpdateAttr = bNew; }
//STRIP001
//STRIP001  inline SwDoc& GetDoc() const;
//STRIP001  USHORT GetId() const    { return nUndoId; }
//STRIP001  USHORT GetLastUndoId() const
//STRIP001      { return  pLastUndoObj ? pLastUndoObj->GetId() : 0 ; }
//STRIP001  void ClearSelections()  { pSelFmt = 0; pMarkList = 0; }
//STRIP001 };




}
#endif
