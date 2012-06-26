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
#ifndef _SWTABLE_HXX
#define _SWTABLE_HXX

#include <bf_svtools/bf_solar.h>

#include <tools/mempool.hxx>
#include <tools/ref.hxx>
#include <bf_svtools/svarray.hxx>
#include <tblenum.hxx>
#include <calbck.hxx>

#ifndef DBG_UTIL
#include <node.hxx>         // fuer StartNode->GetMyIndex
#else
namespace binfilter {
class SwStartNode;
} //namespace binfilter
#endif
class Color;
namespace binfilter {

class SfxPoolItem;
class SwFrmFmt;
class SwTableFmt;
class SwTableLineFmt;
class SwTableBoxFmt;
class SwTableLine;
class SwTableBox;
class SwTableNode;
class SwTabCols;
class SwDoc;
class SwSelBoxes;
class SwTblCalcPara;
class SwChartLines;
struct SwPosition;
class SwNodeIndex;

class SchMemChart;
class SwTableBox_Impl;

#ifndef SW_DECL_SWSERVEROBJECT_DEFINED
#define SW_DECL_SWSERVEROBJECT_DEFINED
SV_DECL_REF( SwServerObject )
#endif

SV_DECL_PTRARR_DEL(SwTableLines, SwTableLine*, 10, 20)
SV_DECL_PTRARR_DEL(SwTableBoxes, SwTableBox*, 25, 50)

// speicher die Inhaltstragenden Box-Pointer zusaetzlich in einem
// sortierten Array (fuers rechnen in der Tabelle)
typedef SwTableBox* SwTableBoxPtr;
SV_DECL_PTRARR_SORT( SwTableSortBoxes, SwTableBoxPtr, 25, 50 )

class SwTable: public SwClient           //Client vom FrmFmt
{
protected:
    SwTableLines aLines;
    SwTableSortBoxes aSortCntBoxes;
     SwServerObjectRef refObj;  // falls DataServer -> Pointer gesetzt

//SOLL das fuer jede Tabelle einstellbar sein?
    TblChgMode   eTblChgMode;

    USHORT       nGrfsThatResize;   // Anzahl der Grfs, die beim HTML-Import
                                    // noch ein Resize der Tbl. anstossen

    BOOL         bModifyLocked  :1;
    BOOL         bHeadlineRepeat:1;

    BOOL IsModifyLocked(){ return bModifyLocked;}

public:
    TYPEINFO();

    SwTable( SwTableFmt* );
    SwTable( const SwTable& rTable );       // kein Copy der Lines !!
    ~SwTable();

    USHORT IncGrfsThatResize() { return ++nGrfsThatResize; }
    USHORT DecGrfsThatResize() { return nGrfsThatResize ? --nGrfsThatResize : 0; }

    void LockModify()   { bModifyLocked = TRUE; }   //Muessen _immer_ paarig
    void UnlockModify() { bModifyLocked = FALSE;}   //benutzt werden!

    BOOL IsHeadlineRepeat() const { return bHeadlineRepeat; }
    void SetHeadlineRepeat( BOOL bSet ) { bHeadlineRepeat = bSet; }

          SwTableLines &GetTabLines() { return aLines; }
    const SwTableLines &GetTabLines() const { return aLines; }

    SwFrmFmt* GetFrmFmt()       { return (SwFrmFmt*)pRegisteredIn; }
    SwFrmFmt* GetFrmFmt() const { return (SwFrmFmt*)pRegisteredIn; }

    virtual void Modify( SfxPoolItem* pOld, SfxPoolItem* pNew );

          SwTableSortBoxes& GetTabSortBoxes()       { return aSortCntBoxes; }
    const SwTableSortBoxes& GetTabSortBoxes() const { return aSortCntBoxes; }

        // gebe den Zellnamen zu der angebenen Row/Col zurueck. Das ist
        // nur fuer ausgeglichene Tabellen interessant, weil diese keine
        // "Sub"Boxen kennen. Es wird z.B. aus (0,0) ein "A1".
        // lese die 1. Nummer und loesche sie aus dem String
        // (wird von GetTblBox und SwTblFld benutzt)
    static USHORT _GetBoxNum( String& rStr, BOOL bFirst = FALSE );
        // suche die Inhaltstragende Box mit dem Namen
    const SwTableBox* GetTblBox( const String& rName ) const;
        // kopiere die selektierten Boxen in ein anderes Dokument.
        // kopiere die Tabelle in diese. (die Logik steht im TBLRWCL.CXX)
        // kopiere die Headline (mit Inhalt!) der Tabelle in eine andere

        // erfrage die Box, dessen Start-Index auf nBoxStt steht
          SwTableBox* GetTblBox( ULONG nSttIdx );
    const SwTableBox* GetTblBox( ULONG nSttIdx ) const
                        {   return ((SwTable*)this)->GetTblBox( nSttIdx );  }

    // returnt TRUE wenn sich in der Tabelle Verschachtelungen befinden
    BOOL IsTblComplex() const;

    // suche alle Inhaltstragenden-Boxen der Grundline in der diese Box
    // steht. rBoxes auch als Return-Wert, um es gleich weiter zu benutzen
    //JP 31.01.97: bToTop = TRUE -> hoch bis zur Grundline,
    //                      FALSE-> sonst nur die Line der Box
        // erfrage vom Client Informationen
    virtual BOOL GetInfo( SfxPoolItem& ) const;

        // suche im Format nach der angemeldeten Tabelle
    static SwTable* FindTable( SwFrmFmt* pFmt );

        // Struktur ein wenig aufraeumen
    void GCLines();
        // BorderLine ein wenig aufraeumen
    void GCBorderLines();

    SwTableNode* GetTableNode() const;

        // Daten Server-Methoden
    const SwServerObject* GetObject() const     {  return &refObj; }
      SwServerObject* GetObject()           {  return &refObj; }

    TblChgMode GetTblChgMode() const        { return eTblChgMode; }
    void SetTblChgMode( TblChgMode eMode )  { eTblChgMode = eMode; }

};

class SwTableLine: public SwClient      // Client vom FrmFmt
{
    SwTableBoxes aBoxes;
    SwTableBox *pUpper;

public:
    TYPEINFO();

    SwTableLine( SwTableLineFmt*, USHORT nBoxes, SwTableBox *pUp );
    ~SwTableLine();

          SwTableBoxes &GetTabBoxes() { return aBoxes; }
    const SwTableBoxes &GetTabBoxes() const { return aBoxes; }

          SwTableBox *GetUpper() { return pUpper; }
    const SwTableBox *GetUpper() const { return pUpper; }
    void SetUpper( SwTableBox *pNew ) { pUpper = pNew; }


    SwFrmFmt* GetFrmFmt()       { return (SwFrmFmt*)pRegisteredIn; }
    SwFrmFmt* GetFrmFmt() const { return (SwFrmFmt*)pRegisteredIn; }

    //Macht ein eingenes FrmFmt wenn noch mehr Lines von ihm abhaengen.
    SwFrmFmt* ClaimFrmFmt();
    void ChgFrmFmt( SwTableLineFmt* pNewFmt );

    // suche nach der naechsten/vorherigen Box mit Inhalt
    SwTableBox* FindNextBox( const SwTable&, const SwTableBox* =0,
                            BOOL bOvrTblLns=TRUE ) const;
    SwTableBox* FindPreviousBox( const SwTable&, const SwTableBox* =0,
                            BOOL bOvrTblLns=TRUE ) const;

};

class SwTableBox: public SwClient       //Client vom FrmFmt
{
    friend class SwNodes;           // um den Index umzusetzen !
    friend void DelBoxNode(SwTableSortBoxes&);  // um den StartNode* zu loeschen !
    friend class SwXMLTableContext;

    //nicht (mehr) implementiert.
    SwTableBox( const SwTableBox & );

    SwTableLines aLines;
    const SwStartNode * pSttNd;
    SwTableLine *pUpper;
    SwTableBox_Impl* pImpl;

    SwTableBox &operator=( const SwTableBox &); //gibts nicht.
    // falls das Format schon Formeln/Values enthaelt, muss ein neues
    // fuer die neue Box erzeugt werden.
    SwTableBoxFmt* CheckBoxFmt( SwTableBoxFmt* );

public:
    TYPEINFO();

    SwTableBox( SwTableBoxFmt*, USHORT nLines, SwTableLine *pUp = 0 );
    SwTableBox( SwTableBoxFmt*, const SwStartNode&, SwTableLine *pUp = 0 );
    SwTableBox( SwTableBoxFmt*, const SwNodeIndex&, SwTableLine *pUp = 0 );
    ~SwTableBox();

          SwTableLines &GetTabLines() { return aLines; }
    const SwTableLines &GetTabLines() const { return aLines; }

          SwTableLine *GetUpper() { return pUpper; }
    const SwTableLine *GetUpper() const { return pUpper; }
    void SetUpper( SwTableLine *pNew ) { pUpper = pNew; }

    SwFrmFmt* GetFrmFmt()       { return (SwFrmFmt*)pRegisteredIn; }
    SwFrmFmt* GetFrmFmt() const { return (SwFrmFmt*)pRegisteredIn; }

    //Macht ein eingenes FrmFmt wenn noch mehr Boxen von ihm abhaengen.
    SwFrmFmt* ClaimFrmFmt();
    void ChgFrmFmt( SwTableBoxFmt *pNewFmt );

    const SwStartNode *GetSttNd() const { return pSttNd; }
    ULONG GetSttIdx() const
#ifndef DBG_UTIL
        { return pSttNd ? pSttNd->GetIndex() : 0; }
#else
        ;
#endif

    // suche nach der naechsten/vorherigen Box mit Inhalt
    // gebe den Namen dieser Box zurueck. Dieser wird dynamisch bestimmt
    // und ergibt sich aus der Position in den Lines/Boxen/Tabelle
    String GetName() const;
    // gebe den "Wert" der Box zurueck (fuers rechnen in der Tabelle)
    double GetValue( SwTblCalcPara& rPara ) const;

    BOOL IsInHeadline( const SwTable* pTbl = 0 ) const;

    // enthaelt die Box Inhalt, der als Nummer formatiert werden kann?
    ULONG IsValidNumTxtNd( BOOL bCheckAttr = TRUE ) const;
    // teste ob der BoxInhalt mit der Nummer uebereinstimmt, wenn eine
    // Tabellenformel gesetzt ist. (fuers Redo des Change vom NumFormat!)

    // ist das eine FormelBox oder eine Box mit numerischen Inhalt (AutoSum)
    // Was es ist, besagt der ReturnWert - die WhichId des Attributes
    // Leere Boxen haben den ReturnWert USHRT_MAX !!

    // fuers Laden - tauscht bei Value Zellen den Inhalt aus, falls sie
    // fuer die Sprache System formatiert sind.
    void ChgByLanguageSystem();

    DECL_FIXEDMEMPOOL_NEWDEL(SwTableBox)

    // zugriff auf interne Daten - z.Z. benutzt fuer den NumFormatter
};

} //namespace binfilter
#endif  //_SWTABLE_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
