/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: rdswg.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-27 23:01:09 $
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
#ifndef _RDSWG_HXX
#define _RDSWG_HXX

#ifndef _SV_PRNTYPES_HXX //autogen
#include <vcl/prntypes.hxx>
#endif

#ifndef _SVARRAY_HXX
#include <svtools/svarray.hxx>
#endif
class Brush;
class Color;
class SfxItemSet;
class Pen;
namespace binfilter {

class SwRect;
class SwPaM;
class SwDoc;
class SwFrm;
class SwFmt;
class SwAttrSet;
class SwNumFmt;
class SwNumRule;
class SwPageDesc;
class SwPageFtnInfo;
class SwNode;
class SwCntntNode;
class SwTxtNode;
class SwTOXBase;
class SwNodeIndex;
class SwTable;
class SwTableBox;
class SwTableBoxes;
class SwTableLine;
class SwTableLines;
class SwField;
class SwFieldType;
class SwpHints;


class SwBlockNames;
class SwStartNode;

class SfxDocumentInfo;

struct FmtInfo {                // Format-Deskriptor:
    union {
        SfxItemSet* pSet;       // AttrSet oder
        SwFmt*      pFmt;       // Format
    };
    BYTE cFmt;                  // Bitflags
};

#define FINFO_FORMAT    0x01    // Eintrag ist Format
#define FINFO_LOCAL     0x02    // Eintrag ist lokal

struct TxtCollInfo {            // Textcollection-Info:
    USHORT nDerived;            // Abhaengigkeit
    USHORT nFollow;             // Folgeindex
};

struct PageDescInfo {           // Seitenbeschreibungs-Info:
    USHORT nPoolId;             // Pool-ID
    USHORT nActualIdx;          // der tatsaechliche Index
    USHORT nFollow;             // Folgeindex
};

struct NumRuleInfo {            // Numerierungs-Regeln:
    SwNumRule* pNumRule;        // dazugehoerige Regel
    SwTxtNode* pBgn, *pEnd;     // Anfang + Ende im Nodes-Array
};

struct FrmInfo {                // Frame-ID-Info:
    SwFrm* pFrm;                // der Frame
    USHORT nId;                 // und sein ID
};

struct LanguageInfo {           // Sprach-Info:
    USHORT nLanguage;           // Sprache
    BOOL   bSupported;          // TRUE, wenn unterstuetzt
};

class PageDescLink : public String{ // Verknuepfung Format mit Seite
public:
    PageDescLink* pLink;        // Link zum naechsten
    USHORT  nOffset;            // Offset
    union {
        SwAttrSet* pSet;        // AttrSet oder
        SwFmt*     pFmt;        // Format
    };
    BYTE cFmt;                  // TRUE: Ptr ist Format
    PageDescLink( const String& s, USHORT n ) : String( s )
    { pLink = NULL; pSet = NULL; cFmt = FALSE; nOffset = n; }
};

struct SectionInfo {            // Section-Info:
    USHORT  nId;                // Section ID
    SwNode* pNode1;             // StartNode
};

typedef const SwTable *SwgSwTablePtr;
SV_DECL_PTRARR(SwgTables,SwgSwTablePtr,4,4)














            // Methoden fuer Hints:


} //namespace binfilter
#endif // _RDSWG_HXX
