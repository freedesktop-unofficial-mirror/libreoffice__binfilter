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

#ifndef _CELLFML_HXX
#define _CELLFML_HXX

#include <bf_svtools/bf_solar.h>

#include <bf_tools/string.hxx>
namespace binfilter {

class SwTable;
class SwNode;
class SwTableSortBoxes;
class SwSelBoxes;
class SwCalc;
class SwTableBox;
class SwTableFmlUpdate;

class SwTblCalcPara
{
    const SwTableBox* pLastTblBox;
    USHORT nStackCnt, nMaxSize;

public:
    SwTableSortBoxes *pBoxStk;  // Stack fuers erkennen von Rekursionen !
    SwCalc& rCalc;              // akt. Calculator
    const SwTable* pTbl;        // akt. Tabelle

    SwTblCalcPara( SwCalc& rCalculator, const SwTable& rTable );
    ~SwTblCalcPara();

    BOOL IsStackOverFlow() const        { return nMaxSize == nStackCnt; }
    BOOL IncStackCnt()                  { return nMaxSize == ++nStackCnt; }
    void DecStackCnt()                  { if( nStackCnt ) --nStackCnt; }
    void SetLastTblBox( const SwTableBox* pBox )    { pLastTblBox = pBox; }
};



class SwTableFormula
{
typedef void (SwTableFormula:: *FnScanFormel)( const SwTable&, String&,
                                            String&, String*, void* ) const;

    void BoxNmsToPtr( const SwTable&, String&, String&, String* = 0,
                        void* pPara = 0 ) const;
    void PtrToBoxNms( const SwTable&, String&, String&, String* = 0,
                        void* pPara = 0 ) const;
    void _MakeFormel( const SwTable&, String&, String&, String* = 0,
                        void* pPara = 0 ) const;
    void _SplitMergeBoxNm( const SwTable&, String&, String&, String* = 0,
                        void* = 0 ) const{DBG_BF_ASSERT(0, "STRIP");}

    void GetBoxes( const SwTableBox& rStt, const SwTableBox& rEnd,
                    SwSelBoxes& rBoxes ) const;
    String ScanString( FnScanFormel fnFormel, const SwTable& rTbl,
                        void* = 0 ) const;


protected:
    enum NameType { EXTRNL_NAME, INTRNL_NAME, REL_NAME };

    String      sFormel;            // akt. Formel
    NameType    eNmType;            // akt. Darstellungs Art
    BOOL        bValidValue;        // TRUE: Formel neu berechnen

    // suche den Node, in dem die Formel steht:
    //  TextFeld    -> TextNode,
    //  BoxAttribut -> BoxStartNode
    // !!! MUSS VON JEDER ABLEITUNG UEBERLADEN WERDEN !!!
    virtual const SwNode* GetNodeOfFormula() const = 0;

    SwTableFormula( const String& rFormel );

    ~SwTableFormula() {}

    String MakeFormel( SwTblCalcPara& rCalcPara ) const
    {
        return ScanString( &SwTableFormula::_MakeFormel,
                            *rCalcPara.pTbl, &rCalcPara );
    }

public:

    SwTableFormula( const SwTableFormula& rCpy )    { *this = rCpy; }
    SwTableFormula& operator=( const SwTableFormula& rCpy )
        {
                                    sFormel = rCpy.sFormel;
                                    eNmType = rCpy.eNmType;
                                    bValidValue = rCpy.bValidValue;
                                    return *this;
        }

    // erzeuge aus der internen (fuer CORE) die externe (fuer UI) Formel
    void PtrToBoxNm( const SwTable* pTbl );
    // erzeuge aus der externen (fuer UI) die interne (fuer CORE) Formel
    void BoxNmToPtr( const SwTable* pTbl );

    // ist gerade eine intern Darstellung aktiv
    BOOL IsIntrnlName() const           { return eNmType == INTRNL_NAME; }
    // erfrage die akt. Darstellung der Formel
    NameType GetNameType() const        { return eNmType; }

    // erfrage/setze das Flag, ob der akt. Wert gueltig ist
    BOOL        IsValid() const             { return bValidValue; }
    inline void ChgValid( BOOL bNew )       { bValidValue = bNew; }

    const String& GetFormula() const        { return sFormel; }
    void SetFormula( const String& rNew )
        {
            sFormel = rNew;
            bValidValue = FALSE;
            eNmType = EXTRNL_NAME;
        }

    // sind alle Boxen gueltig, auf die sich die Formel bezieht?
};



} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
