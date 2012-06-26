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

#ifndef _SCANNER_HXX
#define _SCANNER_HXX

#include <bf_tools/string.hxx>
#include "sberrors.hxx"

namespace binfilter {

// Der Scanner ist stand-alone, d.h. er kann von ueberallher verwendet
// werden. Eine BASIC-Instanz ist fuer Fehlermeldungen notwendig. Ohne
// BASIC werden die Fehler nur gezaehlt. Auch ist Basic notwendig, wenn
// eine erweiterte SBX-Variable zur Erkennung von Datentypen etc. verwendet
// werden soll.

class StarBASIC;

class SbiScanner
{
    ::rtl::OUString   aBuf;             // Input-Puffer
    ::rtl::OUString   aLine;            // aktuelle Zeile
    const sal_Unicode* pLine;           // Pointer
    const sal_Unicode* pSaveLine;       // Merker fuer Line
protected:
    String aSym;                        // Symbolpuffer
    String aError;                      // Fehler-String
    SbxDataType eScanType;              // evtl. Datentyp
    StarBASIC* pBasic;                  // Instanz fuer Fehler-Callbacks
    double nVal;                        // numerischer Wert
    short  nCurCol1;                    // aktuelle Spalte 1
    short  nSavedCol1;                  // gerettete Spalte 1
    short  nCol;                        // aktuelle Spaltennummer
    short  nErrors;                     // Anzahl Fehler
    short  nColLock;                    // Lock-Zaehler fuer Col1
    INT32  nBufPos;                     // aktuelle Buffer-Pos
    USHORT nLine;                       // aktuelle Zeile
    USHORT nCol1, nCol2;                // aktuelle 1. und 2. Spalte
    BOOL   bSymbol;                     // TRUE: Symbol gescannt
    BOOL   bNumber;                     // TRUE: Zahl gescannt
    BOOL   bSpaces;                     // TRUE: Whitespace vor Token
    BOOL   bErrors;                     // TRUE: Fehler generieren
    BOOL   bAbort;                      // TRUE: abbrechen
    BOOL   bHash;                       // TRUE: # eingelesen
    BOOL   bError;                      // TRUE: Fehler generieren
    BOOL   bUsedForHilite;              // TRUE: Nutzung fuer Highlighting
    BOOL   bCompatible;                 // TRUE: OPTION Compatible
    BOOL   bPrevLineExtentsComment;     // TRUE: Previous line is comment and ends on "... _"

    void   GenError( SbError );
public:
    SbiScanner( const ::rtl::OUString&, StarBASIC* = NULL );
   ~SbiScanner();

    void  EnableErrors()            { bError = FALSE; }
    BOOL  IsHash()                  { return bHash;   }
    BOOL  IsCompatible()            { return bCompatible; }
    void  SetCompatible( bool b )   { bCompatible = b; }        // #118206
    BOOL  WhiteSpace()              { return bSpaces; }
    short GetErrors()               { return nErrors; }
    short GetLine()                 { return nLine;   }
    short GetCol1()                 { return nCol1;   }
    short GetCol2()                 { return nCol2;   }
    void  SetCol1( short n )        { nCol1 = n;      }
    StarBASIC* GetBasic()           { return pBasic;  }
    void  SaveLine(void)            { pSaveLine = pLine; }
    void  RestoreLine(void)         { pLine = pSaveLine; }
    void  LockColumn();
    void  UnlockColumn();

    BOOL NextSym();                 // naechstes Symbol lesen
    const String& GetSym()          { return aSym;  }
    SbxDataType GetType()           { return eScanType; }
    double    GetDbl()              { return nVal;  }
};

class LetterTable
{
    bool        IsLetterTab[256];

public:
    LetterTable( void );

    inline bool isLetter( sal_Unicode c )
    {
        bool bRet = (c < 256) ? IsLetterTab[c] : isLetterUnicode( c );
        return bRet;
    }
    bool isLetterUnicode( sal_Unicode c );
};

class BasicSimpleCharClass
{
    static LetterTable aLetterTable;

public:
    static BOOL isAlpha( sal_Unicode c, bool bCompatible )
    {
        BOOL bRet = (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
                    || (bCompatible && aLetterTable.isLetter( c ));
        return bRet;
    }

    static BOOL isDigit( sal_Unicode c )
    {
        BOOL bRet = (c >= '0' && c <= '9');
        return bRet;
    }

    static BOOL isAlphaNumeric( sal_Unicode c, bool bCompatible )
    {
        BOOL bRet = isDigit( c ) || isAlpha( c, bCompatible );
        return bRet;
    }
};

}

#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
