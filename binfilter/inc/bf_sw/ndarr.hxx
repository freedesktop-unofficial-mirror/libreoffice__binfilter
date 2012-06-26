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

#ifndef _NDARR_HXX
#define _NDARR_HXX

#include <bf_svtools/bf_solar.h>

#include <bf_svtools/svarray.hxx>

#include <bparr.hxx>
#include <ndtyp.hxx>

class Graphic;
class UniString;

namespace binfilter {
class SvInPlaceObject;
class BfGraphicObject;

class SwAttrSet;
class SwCntntFrm;
class SwCntntNode;
class SwDoc;
class SwGrfFmtColl;
class SwGrfNode;
class SwHistory;
class SwNode;
class SwNodeIndex;
class SwNodeRange;
class SwOLENode;
class SwOutlineNodes;
class SwPaM;
class SwSection;
class SwSectionFmt;
class SwSectionNode;
class SwStartNode;
class SwTableBoxFmt;
class SwTableFmt;
class SwTableLine;
class SwTableLineFmt;
class SwTableNode;
class SwTblToTxtSaves;
class SwTxtFmtColl;
class SwTxtNode;
struct SwPosition;


// --------------------
// class SwNodes
// --------------------

typedef SwNode * SwNodePtr;
typedef BOOL (*FnForEach_SwNodes)( const SwNodePtr&, void* pArgs );

SV_DECL_PTRARR_SORT( SwOutlineNodes, SwNodePtr, 0, 10 )

class SwNodes: private BigPtrArray
{
    friend class SwDoc;
    friend class SwNode;
    friend class SwNodeIndex;

    SwNodePtr operator[]( USHORT n ) const;
    SwNodePtr operator[]( int n ) const;

    SwNodeIndex* pRoot;                 // Liste aller Indizies auf Nodes

    void Insert( const SwNodePtr pNode, const SwNodeIndex& rPos );
    void Insert( const SwNodePtr pNode, ULONG nPos);

    SwDoc* pMyDoc;                      // in diesem Doc ist das Nodes-Array

    SwNode *pEndOfPostIts, *pEndOfInserts,  // das sind die festen Bereiche
           *pEndOfAutotext, *pEndOfRedlines,
           *pEndOfContent;

    SwOutlineNodes* pOutlineNds;        // Array aller GliederiungsNodes

    BOOL bInNodesDel : 1;               // falls rekursiv aufgerufen wird
                                        // Num/Outline nicht aktualisierem
    BOOL bInDelUpdOutl : 1;             // Flags fuers aktualisieren von Outl.
    BOOL bInDelUpdNum : 1;              // Flags fuers aktualisieren von Outl.

    // fuer dier Verwaltung der Indizies
    void RegisterIndex( SwNodeIndex& rIdx );
    void DeRegisterIndex( SwNodeIndex& rIdx );
    void RemoveNode( ULONG nDelPos, ULONG nLen, bool bDel );

    // Aktionen auf die Nodes
    void SectionUpDown( const SwNodeIndex & aStart, const SwNodeIndex & aEnd );
    void DelNodes( const SwNodeIndex& rStart, ULONG nCnt = 1 );

    void UpdtOutlineIdx( const SwNode& );   // Update ab Node alle OutlineNodes

    void _CopyNodes( const SwNodeRange&, const SwNodeIndex&,
                    BOOL bNewFrms = TRUE, BOOL bTblInsDummyNode = FALSE ) const;
    void _DelDummyNodes( const SwNodeRange& rRg );

protected:
    SwNodes( SwDoc* pDoc );

public:
    ~SwNodes();

    SwNodePtr operator[]( ULONG n ) const
        { return (SwNodePtr)BigPtrArray::operator[] ( n ); }

//JP 29.09.97: impl. steht im ndindex.hxx - sollte moeglichst bald auf die
//              neue Schnittstelle angepasst werden
    inline SwNodePtr operator[]( const SwNodeIndex& rIdx ) const;

    ULONG Count() const { return BigPtrArray::Count(); }
    void ForEach( FnForEach_SwNodes fnForEach, void* pArgs = 0 )
    {
        BigPtrArray::ForEach( 0, BigPtrArray::Count(),
                                (FnForEach) fnForEach, pArgs );
    }
    void ForEach( ULONG nStt, ULONG nEnd, FnForEach_SwNodes fnForEach, void* pArgs = 0 )
    {
        BigPtrArray::ForEach( nStt, nEnd, (FnForEach) fnForEach, pArgs );
    }
    void ForEach( const SwNodeIndex& rStart, const SwNodeIndex& rEnd,
                    FnForEach_SwNodes fnForEach, void* pArgs = 0 );

    // eine noch leere Section
    SwNode& GetEndOfPostIts() const     { return *pEndOfPostIts; }
    // Section fuer alle Fussnoten
    SwNode& GetEndOfInserts() const     { return *pEndOfInserts; }
    // Section fuer alle Flys/Header/Footers
    SwNode& GetEndOfAutotext() const    { return *pEndOfAutotext; }
    // Section fuer alle Redlines
    SwNode& GetEndOfRedlines() const    { return *pEndOfRedlines; }
    // das ist der letzte EndNode einer SonderSection. Hier nach kommt nur
    // noch die normale ContentSection (also der BodyText)
    SwNode& GetEndOfExtras() const      { return *pEndOfRedlines; }
    // die normale ContentSection (also der BodyText)
    SwNode& GetEndOfContent() const     { return *pEndOfContent; }

    // ist das NodesArray das normale vom Doc? (nicht das UndoNds, .. )
    // Implementierung steht im doc.hxx (weil man dazu Doc kennen muss) !
    inline BOOL IsDocNodes() const;

    void Delete(const SwNodeIndex &rPos, ULONG nNodes = 1);

    void _Copy( const SwNodeRange& rRg, const SwNodeIndex& rInsPos,
                BOOL bNewFrms = TRUE ) const
        {   _CopyNodes( rRg, rInsPos, bNewFrms ); }

    void SectionDown( SwNodeRange *pRange, SwStartNodeType = SwNormalStartNode );

    BOOL CheckNodesRange( const SwNodeIndex& rStt, const SwNodeIndex& rEnd ) const;

    void GoStartOfSection(SwNodeIndex *) const {}   // DBG_BF_ASSERT
    void GoEndOfSection(SwNodeIndex *) const;

    SwCntntNode* GoNext(SwNodeIndex *) const;
    SwCntntNode* GoPrevious(SwNodeIndex *) const;

    //Gehe zum naechsten/vorherigen Cntnt/Tabellennode, fuer den
    //es LayoutFrames gibt, dabei Kopf-/Fusszeilen/Rahmen etc. nicht verlassen
    SwNode* GoNextWithFrm(SwNodeIndex *) const;

    // zum naechsten Content-Node, der nicht geschuetzt oder versteckt ist
    // (beides auf FALSE ==> GoNext/GoPrevious!!!)
    SwCntntNode* GoNextSection( SwNodeIndex *, int bSkipHidden  = TRUE,
                                           int bSkipProtect = TRUE ) const;
    SwCntntNode* GoPrevSection( SwNodeIndex *, int bSkipHidden  = TRUE,
                                           int bSkipProtect = TRUE ) const;

    // erzeuge ein leere Section von Start und EndNode. Darf nur gerufen
    // werden, wenn eine neue Section mit Inhalt erzeugt werden soll.
    // Zum Beispiel bei den Filtern/Undo/...
    SwStartNode* MakeEmptySection( const SwNodeIndex& rIdx,
                                    SwStartNodeType = SwNormalStartNode );


    // die Impl. von "Make...Node" stehen in den angegebenen .ccx-Files
    SwTxtNode *MakeTxtNode( const SwNodeIndex & rWhere,
                            SwTxtFmtColl *pColl,
                            SwAttrSet* pAutoAttr = 0 ); // in ndtxt.cxx
    SwStartNode* MakeTextSection( const SwNodeIndex & rWhere,
                            SwStartNodeType eSttNdTyp,
                            SwTxtFmtColl *pColl,
                            SwAttrSet* pAutoAttr = 0 );

    SwGrfNode *MakeGrfNode( const SwNodeIndex & rWhere,
                            const UniString& rGrfName,
                            const UniString& rFltName,
                            const Graphic* pGraphic,
                            SwGrfFmtColl *pColl,
                            SwAttrSet* pAutoAttr = 0,
                            BOOL bDelayed = FALSE );    // in ndgrf.cxx

    SwGrfNode *MakeGrfNode( const SwNodeIndex & rWhere,
                            const BfGraphicObject& rGrfObj,
                            SwGrfFmtColl *pColl,
                            SwAttrSet* pAutoAttr = 0 ); // in ndgrf.cxx

    SwOLENode *MakeOLENode( const SwNodeIndex & rWhere,
                            SvInPlaceObject *pObj,
                            SwGrfFmtColl *pColl,
                            SwAttrSet* pAutoAttr = 0 ); // in ndole.cxx
    SwOLENode *MakeOLENode( const SwNodeIndex & rWhere,
                            UniString &rName,
                            SwGrfFmtColl *pColl,
                            SwAttrSet* pAutoAttr = 0 ); // in ndole.cxx

        // Array aller GliederiungsNodes;
    const SwOutlineNodes& GetOutLineNds() const { return *pOutlineNds; }
        // ab einem bestimmten TextNode alle Updaten
    void UpdateOutlineNode( const SwNode&, BYTE nOldLevel, BYTE nNewLevel );
        // alle Nodes Updaten - Rule/Format-Aenderung
    void UpdateOutlineNodes();

        // fuege die Nodes fuer die Tabelle ein
        // wenn Lines angegeben, erzeuge die Matrix aus Lines & Boxen
        // ansonsten nur die Anzahl von Boxen.
        /* #109161#

       New parameter pAttrSet: If pAttrSet is non-null and contains an
       adjust item it is propagated to the table cells. If there is an
       adjust in pCntntTxtColl or pHeadlineTxtColl this adjust item
       overrides the item in pAttrSet.

     */
    SwTableNode* InsertTable( const SwNodeIndex& rNdIdx,
                        USHORT nBoxes, SwTxtFmtColl* pCntntTxtColl,
                        USHORT nLines=0, SwTxtFmtColl* pHeadlineTxtColl=0,
                              const SwAttrSet * pAttrSet = 0);

        // Splittet eine Tabelle in der Grund-Zeile, in der der Index steht.
        // Alle GrundZeilen dahinter wandern in eine neue Tabelle/-Node.
        // Ist das Flag bCalcNewSize auf TRUE, wird fuer beide neuen Tabellen
        // die neue SSize aus dem Max der Boxen errechnet; vorrausgesetzt,
        // die SSize ist "absolut" gesetzt (LONG_MAX)
        // (Wird zur Zeit nur fuer den RTF-Parser benoetigt)
        // fuegt 2 Tabellen, die hintereinander stehen, wieder zusammen

        // fuege eine neue SwSection ein
    SwSectionNode* InsertSection( const SwNodeIndex& rNdIdx,
                                SwSectionFmt& rSectionFmt,
                                const SwSection&,
                                const SwNodeIndex* pEnde,
                                BOOL bInsAtStart = TRUE );

        // in welchem Doc steht das Nodes-Array ?
            SwDoc* GetDoc()         { return pMyDoc; }
    const   SwDoc* GetDoc() const   { return pMyDoc; }
private:
    // privater Constructor, weil nie kopiert werden darf !!
    SwNodes( const SwNodes & rNodes );
};



} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
