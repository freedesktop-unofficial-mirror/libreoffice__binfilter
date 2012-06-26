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

#include <ctype.h>
#include "token.hxx"

namespace binfilter {

struct TokenTable { SbiToken t; const char *s; };

static short nToken;                    // Anzahl der Tokens

static TokenTable* pTokTable;

static TokenTable aTokTable_Basic [] = {        // Token-Tabelle:

    { CAT,      "&" },
    { MUL,      "*" },
    { PLUS,     "+" },
    { MINUS,    "-" },
    { DIV,      "/" },
    { EOS,      ":" },
    { ASSIGN,   ":=" },
    { LT,       "<" },
    { LE,       "<=" },
    { NE,       "<>" },
    { EQ,       "=" },
    { GT,       ">" },
    { GE,       ">=" },
    { ACCESS,   "Access" },
    { ALIAS,    "Alias" },
    { AND,      "And" },
    { ANY,      "Any" },
    { APPEND,   "Append" },
    { AS,       "As" },
    { BASE,     "Base" },
    { BINARY,   "Binary" },
    { TBOOLEAN, "Boolean" },
    { BYREF,    "ByRef", },
    { TBYTE,    "Byte", },
    { BYVAL,    "ByVal", },
    { CALL,     "Call" },
    { CASE,     "Case" },
    { _CDECL_,  "Cdecl" },
    { CLASSMODULE, "ClassModule" },
    { CLOSE,    "Close" },
    { COMPARE,  "Compare" },
    { COMPATIBLE,"Compatible" },
    { _CONST_,  "Const" },
    { TCURRENCY,"Currency" },
    { TDATE,    "Date" },
    { DECLARE,  "Declare" },
    { DEFBOOL,  "DefBool" },
    { DEFCUR,   "DefCur" },
    { DEFDATE,  "DefDate" },
    { DEFDBL,   "DefDbl" },
    { DEFERR,   "DefErr" },
    { DEFINT,   "DefInt" },
    { DEFLNG,   "DefLng" },
    { DEFOBJ,   "DefObj" },
    { DEFSNG,   "DefSng" },
    { DEFSTR,   "DefStr" },
    { DEFVAR,   "DefVar" },
    { DIM,      "Dim" },
    { DO,       "Do" },
    { TDOUBLE,  "Double" },
    { EACH,     "Each" },
    { ELSE,     "Else" },
    { ELSEIF,   "ElseIf" },
    { END,      "End" },
    { ENDENUM,  "End Enum" },
    { ENDFUNC,  "End Function" },
    { ENDIF,    "End If" },
    { ENDPROPERTY, "End Property" },
    { ENDSELECT,"End Select" },
    { ENDSUB,   "End Sub" },
    { ENDTYPE,  "End Type" },
    { ENDIF,    "EndIf" },
    { ENUM,     "Enum" },
    { EQV,      "Eqv" },
    { ERASE,    "Erase" },
    { _ERROR_,  "Error" },
    { EXIT,     "Exit" },
    { EXPLICIT, "Explicit" },
    { FOR,      "For" },
    { FUNCTION, "Function" },
    { GET,      "Get" },
    { GLOBAL,   "Global" },
    { GOSUB,    "GoSub" },
    { GOTO,     "GoTo" },
    { IF,       "If" },
    { IMP,      "Imp" },
    { IMPLEMENTS, "Implements" },
    { _IN_,     "In" },
    { INPUT,    "Input" },              // auch INPUT #
    { TINTEGER, "Integer" },
    { IS,       "Is" },
    { LET,      "Let" },
    { LIB,      "Lib" },
    { LINE,     "Line" },
    { LINEINPUT,"Line Input" },
    { LOCAL,    "Local" },
    { LOCK,     "Lock" },
    { TLONG,    "Long" },
    { LOOP,     "Loop" },
    { LPRINT,   "LPrint" },
    { LSET,     "LSet" }, // JSM
    { MOD,      "Mod" },
    { NAME,     "Name" },
    { NEW,      "New" },
    { NEXT,     "Next" },
    { NOT,      "Not" },
    { TOBJECT,  "Object" },
    { ON,       "On" },
    { OPEN,     "Open" },
    { OPTION,   "Option" },
    { _OPTIONAL_,   "Optional" },
    { OR,       "Or" },
    { OUTPUT,   "Output" },
    { PARAMARRAY,   "ParamArray" },
    { PRESERVE, "Preserve" },
    { PRINT,    "Print" },
    { PRIVATE,  "Private" },
    { PROPERTY, "Property" },
    { PUBLIC,   "Public" },
    { RANDOM,   "Random" },
    { READ,     "Read" },
    { REDIM,    "ReDim" },
    { REM,      "Rem" },
    { RESUME,   "Resume" },
    { RETURN,   "Return" },
    { RSET,     "RSet" }, // JSM
    { SELECT,   "Select" },
    { SET,      "Set" },
#ifdef SHARED
#undef SHARED
#define tmpSHARED
#endif
    { SHARED,   "Shared" },
#ifdef tmpSHARED
#define SHARED
#undef tmpSHARED
#endif
    { TSINGLE,  "Single" },
    { STATIC,   "Static" },
    { STEP,     "Step" },
    { STOP,     "Stop" },
    { TSTRING,  "String" },
    { SUB,      "Sub" },
    { STOP,     "System" },
    { TEXT,     "Text" },
    { THEN,     "Then" },
    { TO,       "To", },
    { TYPE,     "Type" },
    { TYPEOF,   "TypeOf" },
    { UNTIL,    "Until" },
    { TVARIANT, "Variant" },
    { VBASUPPORT,   "VbaSupport" },
    { WEND,     "Wend" },
    { WHILE,    "While" },
    { WITH,     "With" },
    { WRITE,    "Write" },              // auch WRITE #
    { XOR,      "Xor" },
    { NIL,      "" }
};

// Der Konstruktor ermittelt die Laenge der Token-Tabelle.

SbiTokenizer::SbiTokenizer( const ::rtl::OUString& rSrc, StarBASIC* pb )
           : SbiScanner( rSrc, pb )
{
    pTokTable = aTokTable_Basic;
    TokenTable *tp;
    bEof = bAs = FALSE;
    eCurTok = NIL;
    ePush = NIL;
    bEos = bKeywords = bErrorIsSymbol = TRUE;
    if( !nToken )
        for( nToken = 0, tp = pTokTable; tp->t; nToken++, tp++ ) {}
}

SbiTokenizer::~SbiTokenizer()
{}

// Einlesen des naechsten Tokens, ohne dass das Token geschluckt wird

SbiToken SbiTokenizer::Peek()
{
    if( ePush == NIL )
    {
        USHORT nOldLine = nLine;
        USHORT nOldCol1 = nCol1;
        USHORT nOldCol2 = nCol2;
        ePush = Next();
        nPLine = nLine; nLine = nOldLine;
        nPCol1 = nCol1; nCol1 = nOldCol1;
        nPCol2 = nCol2; nCol2 = nOldCol2;
    }
    return eCurTok = ePush;
}

// Einlesen des naechsten Tokens und Ablage desselben
// Tokens, die nicht in der Token-Tabelle vorkommen, werden
// direkt als Zeichen zurueckgeliefert.
// Einige Worte werden gesondert behandelt.

SbiToken SbiTokenizer::Next()
{
    if (bEof) return EOLN;
    // Schon eines eingelesen?
    if( ePush != NIL )
    {
        eCurTok = ePush;
        ePush = NIL;
        nLine = nPLine;
        nCol1 = nPCol1;
        nCol2 = nPCol2;
        bEos = IsEoln( eCurTok );
        return eCurTok;
    }
    TokenTable *tp;

    // Sonst einlesen:
    if( !NextSym() )
    {
        bEof = bEos = TRUE;
        return eCurTok = EOLN;
    }
    // Zeilenende?
    if( aSym.GetBuffer()[0] == '\n' )
    {
        bEos = TRUE; return eCurTok = EOLN;
    }
    bEos = FALSE;

    // Zahl?
    if( bNumber )
        return eCurTok = NUMBER;

    // String?
    else if( ( eScanType == SbxDATE || eScanType == SbxSTRING ) && !bSymbol )
        return eCurTok = FIXSTRING;
    // Sonderfaelle von Zeichen, die zwischen "Z" und "a" liegen. ICompare()
    // wertet die Position dieser Zeichen unterschiedlich aus.
    else if( aSym.GetBuffer()[0] == '^' )
        return eCurTok = EXPON;
    else if( aSym.GetBuffer()[0] == '\\' )
        return eCurTok = IDIV;
    else
    {
        // Mit Typkennung oder ein Symbol und keine Keyword-Erkennung?
        // Dann kein Token-Test
        if( eScanType != SbxVARIANT
         || ( !bKeywords && bSymbol ) )
            return eCurTok = SYMBOL;
        // Gueltiges Token?
        short lb = 0;
        short ub = nToken-1;
        short delta;
        do
        {
            delta = (ub - lb) >> 1;
            tp = &pTokTable[ lb + delta ];
            StringCompare res = aSym.CompareIgnoreCaseToAscii( tp->s );
            // Gefunden?
            if( res == COMPARE_EQUAL ) goto special;
            // Groesser? Dann untere Haelfte
            if( res == COMPARE_LESS )
            {
                if ((ub - lb) == 2) ub = lb;
                else ub = ub - delta;
            }
            // Kleiner? Dann obere Haelfte
            else
            {
                if ((ub -lb) == 2) lb = ub;
                else lb = lb + delta;
            }
        } while( delta );
        // Symbol? Wenn nicht >= Token
        sal_Unicode ch = aSym.GetBuffer()[0];
        if( !BasicSimpleCharClass::isAlpha( ch, bCompatible ) && !bSymbol )
            return eCurTok = (SbiToken) (ch & 0x00FF);
        return eCurTok = SYMBOL;
    }
special:
    // LINE INPUT
    if( tp->t == LINE )
    {
        short nC1 = nCol1;
        String aOldSym = aSym;
        eCurTok = Peek();
        if( eCurTok == INPUT )
        {
            Next();
            nCol1 = nC1;
            return eCurTok = LINEINPUT;
        }
        else
        {
            aSym = aOldSym;
            return eCurTok = LINE;
        }
    }
    // END IF, CASE, SUB, DEF, FUNCTION, TYPE, CLASS, WITH
    if( tp->t == END )
    {
        // AB, 15.3.96, Spezialbehandlung fuer END, beim Peek() geht die
        // aktuelle Zeile verloren, daher alles merken und danach restaurieren
        USHORT nOldLine = nLine;
        USHORT nOldCol  = nCol;
        USHORT nOldCol1 = nCol1;
        USHORT nOldCol2 = nCol2;
        String aOldSym = aSym;
        SaveLine();             // pLine im Scanner sichern

        eCurTok = Peek();
        switch( eCurTok )
        {
            case IF:       Next(); eCurTok = ENDIF; break;
            case SELECT:   Next(); eCurTok = ENDSELECT; break;
            case SUB:      Next(); eCurTok = ENDSUB; break;
            case FUNCTION: Next(); eCurTok = ENDFUNC; break;
            case PROPERTY: Next(); eCurTok = ENDPROPERTY; break;
            case TYPE:     Next(); eCurTok = ENDTYPE; break;
            case ENUM:     Next(); eCurTok = ENDENUM; break;
            case WITH:     Next(); eCurTok = ENDWITH; break;
            default :      eCurTok = END;
        }
        nCol1 = nOldCol1;
        if( eCurTok == END )
        {
            // Alles zuruecksetzen, damit Token nach END ganz neu gelesen wird
            ePush = NIL;
            nLine = nOldLine;
            nCol  = nOldCol;
            nCol2 = nOldCol2;
            aSym = aOldSym;
            RestoreLine();      // pLine im Scanner restaurieren
        }
        return eCurTok;
    }
    // Sind Datentypen Keywords?
    // Nur nach AS, sonst sind es Symbole!
    // Es gibt ja ERROR(), DATA(), STRING() etc.
    eCurTok = tp->t;
    // AS: Datentypen sind Keywords
    if( tp->t == AS )
        bAs = TRUE;
    else
    {
        if( bAs )
            bAs = FALSE;
        else if( eCurTok >= DATATYPE1 && eCurTok <= DATATYPE2 && (bErrorIsSymbol || eCurTok != _ERROR_) )
            eCurTok = SYMBOL;
    }

    // CLASSMODULE, PROPERTY, GET, ENUM token only visible in compatible mode
    SbiToken eTok = tp->t;
    if( bCompatible )
    {
        // #129904 Suppress system
        if( eTok == STOP && aSym.CompareIgnoreCaseToAscii( "system" ) == COMPARE_EQUAL )
            eCurTok = SYMBOL;
    }
    else
    {
        if( eTok == CLASSMODULE ||
            eTok == IMPLEMENTS ||
            eTok == PARAMARRAY ||
            eTok == ENUM ||
            eTok == PROPERTY ||
            eTok == GET ||
            eTok == TYPEOF )
        {
            eCurTok = SYMBOL;
        }
    }

    bEos = IsEoln( eCurTok );
    return eCurTok;
}
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
