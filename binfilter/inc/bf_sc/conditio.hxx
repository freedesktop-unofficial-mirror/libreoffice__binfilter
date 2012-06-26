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

#ifndef SC_CONDITIO_HXX
#define SC_CONDITIO_HXX

#include <bf_svtools/bf_solar.h>

#include "global.hxx"

#include <bf_svtools/svarray.hxx>
namespace binfilter {

class ScBaseCell;
class ScFormulaCell;
class ScTokenArray;
class ScMultipleReadHeader;
class ScRangeList;


#define SC_COND_GROW 16

//  nOptions Flags
#define SC_COND_NOBLANKS    1


            // Reihenfolge von ScConditionMode wie ScQueryOp,
            // damit einmal zusammengefasst werden kann:

enum ScConditionMode
{
    SC_COND_EQUAL,
    SC_COND_LESS,
    SC_COND_GREATER,
    SC_COND_EQLESS,
    SC_COND_EQGREATER,
    SC_COND_NOTEQUAL,
    SC_COND_BETWEEN,
    SC_COND_NOTBETWEEN,
    SC_COND_DIRECT,
    SC_COND_NONE
};

enum ScConditionValType
{
    SC_VAL_VALUE,
    SC_VAL_STRING,
    SC_VAL_FORMULA
};

class ScConditionEntry
{
                                        // gespeicherte Daten:
    ScConditionMode     eOp;
    USHORT              nOptions;
    double              nVal1;          // eingegeben oder berechnet
    double              nVal2;
    String              aStrVal1;       // eingegeben oder berechnet
    String              aStrVal2;
    BOOL                bIsStr1;        // um auch leere Strings zu erkennen
    BOOL                bIsStr2;
    ScTokenArray*       pFormula1;      // eingegebene Formel
    ScTokenArray*       pFormula2;
    ScAddress           aSrcPos;        // Quell-Adresse fuer Formeln
                                        // temporaere Daten:
    ScFormulaCell*      pFCell1;
    ScFormulaCell*      pFCell2;
    ScDocument*         pDoc;
    BOOL                bRelRef1;
    BOOL                bRelRef2;
    BOOL                bFirstRun;

    void    MakeCells( const ScAddress& rPos );
    void    Compile( const String& rExpr1, const String& rExpr2, BOOL bEnglish,
                        BOOL bCompileXML, BOOL bTextToReal );
    void    Interpret( const ScAddress& rPos );

    BOOL    IsValid( double nArg ) const;

protected:
            ScConditionEntry( SvStream& rStream, ScMultipleReadHeader& rHdr,
                                ScDocument* pDocument );
public:
            ScConditionEntry( ScConditionMode eOper,
                                const String& rExpr1, const String& rExpr2,
                                ScDocument* pDocument, const ScAddress& rPos,
                                BOOL bCompileEnglish, BOOL bCompileXML );
            ScConditionEntry( const ScConditionEntry& r );  // flache Kopie der Formeln
            // echte Kopie der Formeln (fuer Ref-Undo):
            ScConditionEntry( ScDocument* pDocument, const ScConditionEntry& r );
            virtual ~ScConditionEntry();

    int             operator== ( const ScConditionEntry& r ) const;

    BOOL            IsCellValid( ScBaseCell* pCell, const ScAddress& rPos ) const;

    ScConditionMode GetOperation() const        { return eOp; }
    BOOL            IsIgnoreBlank() const       { return ( nOptions & SC_COND_NOBLANKS ) == 0; }
    void            SetIgnoreBlank(BOOL bSet);
    ScAddress       GetSrcPos() const           { return aSrcPos; }

    String          GetExpression( const ScAddress& rCursor, USHORT nPos, ULONG nNumFmt = 0,
                                    BOOL bEnglish = FALSE, BOOL bCompileXML = FALSE,
                                    BOOL bTextToReal = FALSE ) const;


    void            CompileXML();
    void            UpdateReference( UpdateRefMode eUpdateRefMode,
                                const ScRange& rRange, short nDx, short nDy, short nDz );

    void            SourceChanged( const ScAddress& rChanged );

protected:
    virtual void    DataChanged( const ScRange* pModified ) const;
    ScDocument*     GetDocument() const     { return pDoc; }
};

//
//  einzelner Eintrag fuer bedingte Formatierung
//

class ScConditionalFormat;

class ScCondFormatEntry : public ScConditionEntry
{
    String                  aStyleName;
    ScConditionalFormat*    pParent;

public:
            ScCondFormatEntry( ScConditionMode eOper,
                                const String& rExpr1, const String& rExpr2,
                                ScDocument* pDocument, const ScAddress& rPos,
                                const String& rStyle,
                                BOOL bCompileEnglish = FALSE, BOOL bCompileXML = FALSE );
            ScCondFormatEntry( const ScCondFormatEntry& r );
            ScCondFormatEntry( ScDocument* pDocument, const ScCondFormatEntry& r );
            ScCondFormatEntry( SvStream& rStream, ScMultipleReadHeader& rHdr,
                                ScDocument* pDocument );
            ~ScCondFormatEntry();

    void            SetParent( ScConditionalFormat* pNew )  { pParent = pNew; }

    int             operator== ( const ScCondFormatEntry& r ) const;

    const String&   GetStyle() const        { return aStyleName; }

protected:
    virtual void    DataChanged( const ScRange* pModified ) const;
};

//
//  komplette bedingte Formatierung
//

class ScConditionalFormat
{
    ScDocument*         pDoc;
    ScRangeList*        pAreas;             // Bereiche fuer Paint
    sal_uInt32          nKey;               // Index in Attributen
    ScCondFormatEntry** ppEntries;
    USHORT              nEntryCount;
    BOOL                bIsUsed;            // temporaer beim Speichern

public:
            ScConditionalFormat(sal_uInt32 nNewKey, ScDocument* pDocument);
            ScConditionalFormat(const ScConditionalFormat& r);
            ScConditionalFormat(SvStream& rStream, ScMultipleReadHeader& rHdr,
                                ScDocument* pDocument);
            ~ScConditionalFormat();

    // echte Kopie der Formeln (fuer Ref-Undo / zwischen Dokumenten)
    ScConditionalFormat* Clone(ScDocument* pNewDoc = NULL) const;

    void            AddEntry( const ScCondFormatEntry& rNew );

    BOOL            IsEmpty() const         { return (nEntryCount == 0); }
    USHORT          Count() const           { return nEntryCount; }

    void            CompileXML();
    void            UpdateReference( UpdateRefMode eUpdateRefMode,
                                const ScRange& rRange, short nDx, short nDy, short nDz );

    void            SourceChanged( const ScAddress& rAddr );

    const ScCondFormatEntry* GetEntry( USHORT nPos ) const;

    const String&   GetCellStyle( ScBaseCell* pCell, const ScAddress& rPos ) const;

    BOOL            EqualEntries( const ScConditionalFormat& r ) const;

    void            DoRepaint( const ScRange* pModified );
    void            InvalidateArea();

    sal_uInt32      GetKey() const          { return nKey; }
    void            SetKey(sal_uInt32 nNew) { nKey = nNew; }    // nur wenn nicht eingefuegt!

    void            SetUsed(BOOL bSet)      { bIsUsed = bSet; }
    BOOL            IsUsed() const          { return bIsUsed; }

    //  sortiert (per PTRARR) nach Index
    //  operator== nur fuer die Sortierung
    BOOL operator ==( const ScConditionalFormat& r ) const  { return nKey == r.nKey; }
    BOOL operator < ( const ScConditionalFormat& r ) const  { return nKey <  r.nKey; }
};

//
//  Liste der Bereiche und Formate:
//

typedef ScConditionalFormat* ScConditionalFormatPtr;

SV_DECL_PTRARR_SORT(ScConditionalFormats_Impl, ScConditionalFormatPtr,
                        SC_COND_GROW, SC_COND_GROW)

class ScConditionalFormatList : public ScConditionalFormats_Impl
{
public:
        ScConditionalFormatList() {}
        ScConditionalFormatList(const ScConditionalFormatList& rList);
        ~ScConditionalFormatList() {}

    void    InsertNew( ScConditionalFormat* pNew )
                { if (!Insert(pNew)) delete pNew; }

    ScConditionalFormat* GetFormat( sal_uInt32 nKey );

    void    Load( SvStream& rStream, ScDocument* pDocument );
    void    Store( SvStream& ) const {}

    void    CompileXML();
    void    UpdateReference( UpdateRefMode eUpdateRefMode,
                                const ScRange& rRange, short nDx, short nDy, short nDz );

    void    SourceChanged( const ScAddress& rAddr );

};

} //namespace binfilter
#endif


/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
