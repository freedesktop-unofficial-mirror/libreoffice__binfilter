/*************************************************************************
 *
 *  $RCSfile: rdswg.hxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: aw $ $Date: 2003-10-02 15:32:43 $
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
#ifndef _RDSWG_HXX
#define _RDSWG_HXX

#ifndef _SV_PRNTYPES_HXX //autogen
#include <vcl/prntypes.hxx>
#endif

#ifndef _SVARRAY_HXX
#include <svtools/svarray.hxx>
#endif
#ifndef _SWGSTR_HXX
#include <swgstr.hxx>
#endif
#ifndef _SWGIDS_HXX
#include <swgids.hxx>
#endif

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
class Pen;
class Brush;
class Color;
class SfxItemSet;
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

//STRIP001 class SwSwgReader
//STRIP001 {
//STRIP001  friend class Sw2TextBlocks;
//STRIP001
//STRIP001 private:
//STRIP001  ULONG         nErrno;       // Fehlernummer
//STRIP001  SwPaM*        pPaM;         // WriterG-Einfuegepos
//STRIP001  long          nDocStart;    // Beginn des Dokuments
//STRIP001  long          nRecStart;    // Beginn der Records im Dokument
//STRIP001  long          nNextDoc;     // Offset des naechsten Dokuments
//STRIP001  FrmInfo*      pFrms;        // Frame-ID-Infos
//STRIP001  FmtInfo*      pFmts;        // Format-Infos
//STRIP001  TxtCollInfo*  pCollIdx;     // Collection Index translation table
//STRIP001  PageDescInfo* pLayIdx;      // Layout Index translation table
//STRIP001  PageDescLink* pPageLinks;   // Format-Seiten-Links
//STRIP001  NumRuleInfo*  pRules;       // Num-Regelwerk
//STRIP001  SectionInfo*  pSects;       // Sections
//STRIP001  SectionInfo*  pLastSect;    // letzte Section
//STRIP001  LanguageInfo* pLanguages;   // Sprachen
//STRIP001  const ByteString* pNdOrigTxt;       // original text of the textnode
//STRIP001
//STRIP001  USHORT  nColl, nLay;        // Anzahl Collections, Seitenlayouts
//STRIP001  USHORT  nRules;             // Anzahl Regeln
//STRIP001  USHORT  nNamedFmt;          // Anzahl benannte Formate (fuer Textbausteine)
//STRIP001  USHORT  nFrm, nFrmSize;     // Anzahl Frame-IDs, Tabellengroesse
//STRIP001  USHORT  nSect, nSectSize;   // Anzahl Sections, Tabellengroesse
//STRIP001  USHORT  nTbl, nTblSize;     // Anzahl Tabellen, Tabellengroesse
//STRIP001  USHORT  nLang, nLangSize;   // Anzahl Sprachen, Tabellengroesse
//STRIP001  USHORT  nOptions;           // Lese-Optionen
//STRIP001  USHORT  nHelpFileId;        // Hilfe-ID fuer Vorlagen-Templates
//STRIP001  USHORT  nFlyLevel;          // != 0: FlyFmt wird eingelesen
//STRIP001  USHORT  nFlagBits;          // temp fuer PageDesc: Bits aus Format
//STRIP001  USHORT  nFmtLvl;            // Rekursionstiefe fuer InFormat()
//STRIP001  USHORT  nTblBoxLvl;         // Rekursionstiefe fuer InFormat in InTableBox()
//STRIP001
//STRIP001  SfxDocumentInfo* pInfo;
//STRIP001  String  aFileName;          // Name vom Eingabe-Stream
//STRIP001  SwgTables *pTables;
//STRIP001
//STRIP001  // gc25: swistream besitzt privaten Copy-CTOR
//STRIP001  SwSwgReader( const SwSwgReader & );
//STRIP001
//STRIP001  BOOL    LoadDocInfo( SfxDocumentInfo& );
//STRIP001
//STRIP001  short   LayoutIdx( short n );
//STRIP001  void    UpdateRuleRange( USHORT nIdx, SwTxtNode* pNd );
//STRIP001  void    ResolvePageDescLinks();
//STRIP001  String  ParseText();
//STRIP001 //   void    ConvertLineTerminators( String&, GUIType );
//STRIP001  void    LoadHeader();
//STRIP001
//STRIP001  void    InTxtFmtColls();
//STRIP001  void    InTxtFmtColl( short nIdx );

//STRIP001  void    InPageDescs();
//STRIP001  void    InPageDesc( short nIdx );
//STRIP001  void    InPageFtnInfo( SwPageFtnInfo& rFtn );
//STRIP001
//STRIP001  void    InTextHints( SwTxtNode& rNd, xub_StrLen nOffset );
//STRIP001  void    InNodeBookmark( SwNodeIndex& rPos );
//STRIP001  USHORT  GetNextSymbolFontHint( SwpHints*, USHORT, xub_StrLen&, xub_StrLen& );
//STRIP001  USHORT  GetNextCharsetColorHint( SwpHints*, USHORT, xub_StrLen&,
//STRIP001                                   xub_StrLen&, rtl_TextEncoding,
//STRIP001                                   rtl_TextEncoding&);
//STRIP001  void    ConvertText( SwTxtNode& rNd, rtl_TextEncoding eSrc );
//STRIP001  void    SetAttrSet( SwCntntNode& rNd, USHORT nId );
//STRIP001  void    InTxtNodeAttrs( SwTxtNode& rNd, USHORT nWhich1, USHORT nWhich2 );
//STRIP001  void    FillTxtNode( SwTxtNode* pNd, SwNodeIndex& rPos, xub_StrLen nOffset, USHORT=0);
//STRIP001  void    FillString( String& );
//STRIP001  void    InGrfNode( SwNodeIndex& rPos );
//STRIP001  void    InOleNode( SwNodeIndex& rPos );
//STRIP001
//STRIP001  SwTOXBase* InTOXBase();
//STRIP001  void    InTOXContents( SwNodeIndex& rPos, SwTxtNode* );
//STRIP001  void    InTOX( SwNodeIndex& rPos, SwTxtNode* );
//STRIP001
//STRIP001  void    InContents( BOOL bNode1 = TRUE, BOOL bBlock = FALSE, USHORT=0 );
//STRIP001  String  InContentsText( BOOL = TRUE );
//STRIP001  void    ScanContents( SwBlockNames* );
//STRIP001
//STRIP001  void    InFlyFrames( const SwNodeIndex* pNdIdx );
//STRIP001  void    InFlyFrame( const SwNodeIndex* pNdIdx );

//STRIP001  void    InDfltFmts();
//STRIP001  void    InNamedFmts( USHORT );
//STRIP001  void    ClearFmtIds();

//STRIP001  void    InTableBox( SwTableBoxes&, int, SwTableLine*, SwNodeIndex&,
//STRIP001                      const SwTable *pTable=0 );
//STRIP001  void    InTableLine( SwTableLines&, SwTableBox*, int, SwNodeIndex&,
//STRIP001                       const SwTable *pTable=0 );
//STRIP001  void    InTable( SwNodeIndex& rPos );

//STRIP001  void    InNumFmt( SwNumFmt& rFmt );
//STRIP001  SwNumRule* InNumRule();
//STRIP001  void    InOutlineRule();
//STRIP001  void    InTxtNumRule();
//STRIP001  void    InFtnInfo();
//STRIP001
//STRIP001  void    InGlobalMacroTbl();
//STRIP001  void    InJobSetup();
//STRIP001  void    InDocInfo();
//STRIP001  void    InStaticDocInfo( SfxDocumentInfo& );
//STRIP001  void    InDynamicDocInfo( SfxDocumentInfo& );
//STRIP001  void    InComment();
//STRIP001
//STRIP001  void    InLayoutFrames();
//STRIP001
//STRIP001  USHORT  InHint( SfxItemSet& );
//STRIP001  USHORT  InHint( SwTxtNode&, xub_StrLen, xub_StrLen );

//STRIP001  void    InFieldTypes();
//STRIP001  SwFieldType* InFieldType();

//STRIP001  BOOL    CopyRecord( SvStream* );

//STRIP001 public:
//STRIP001  SwDoc*    pDoc;             // WriterG-Dokumentzugriff
//STRIP001  BOOL      bNew;             // Darf es was neues sein?
//STRIP001  xub_StrLen  nCntntCol;      // Spalte fuer Rahmen im Node (RES_FLY_ANCHOR)
//STRIP001  USHORT    nPage1;           // Start-Seite bei Einfuegen (RES_FLY_ANCHOR)
//STRIP001  swistream r;                // Input-Stream
//STRIP001 //   SvStream r;             // Input-Stream
//STRIP001  DocHeader aHdr;             // Dokument-Header
//STRIP001  FileHeader aFile;           // Datei-Header
//STRIP001  USHORT  nStatus;            // Status-Flags:
//STRIP001
//STRIP001 #define  SWGSTAT_SHAREDFMT       0x0001      // Shared Fmt wird eingelesen
//STRIP001 #define  SWGSTAT_UPDATEEXPR      0x0002      // ExprFields-Update noetig
//STRIP001 #define  SWGSTAT_NO_BOOKMARKS    0x0004      // Bookmarks ueberlesen
//STRIP001 #define  SWGSTAT_LOCALFMTS       0x0008      // lokale Formate
//STRIP001 #define  SWGSTAT_CONVBLOCKS      0x0010      // Konversion von Textbausteinen
//STRIP001
//STRIP001                              // Ablage-Variable fuer Lesen von Layout-Frames
//STRIP001  USHORT    nFrmFlags;        // Layout-Frame-Flags
//STRIP001  SwFrm*    pUpper;           // Upper Layout-Frame
//STRIP001  SwFrm*    pMaster;          // Master Layout-Frame
//STRIP001  USHORT    eStartNodeType;   // fuers erzeugen von StartNodes
//STRIP001                              // Fly/Footer/Header!
//STRIP001
//STRIP001  SwSwgReader( SwDoc *pSwDoc, const SwPaM* pSwPaM, SvStream& rStream,
//STRIP001                  const String& rFileName, BOOL bNewDoc );
//STRIP001  ~SwSwgReader();
//STRIP001  ULONG   GetError() { return nErrno; }
//STRIP001
//STRIP001  const SfxDocumentInfo& GetDocInfo() { return *pInfo; }
//STRIP001
//STRIP001  void    LoadFileHeader();
//STRIP001  ULONG   Read( USHORT nOptions );
//STRIP001  ULONG   Scan( SwBlockNames* );
//STRIP001  BOOL    CheckPasswd( const String& );
//STRIP001
//STRIP001  void    RegisterFmt( SwFmt& rFmt, const SwTable *pTable=0 );
//STRIP001  void    RegisterAttrSet( SfxItemSet* pSet, USHORT nIdx );
//STRIP001  void    ReleaseAttrSets();
//STRIP001  void    ReRegisterFmt( const SwFmt& rFmtOld, const SwFmt& rFmtNew,
//STRIP001                         const SwTable *pTable=0 );
//STRIP001  SwFmt*  FindFmt( USHORT nIdx, BYTE cType );
//STRIP001  SfxItemSet* FindAttrSet( USHORT nIdx );
//STRIP001  SwFmt*  InFormat( SwFmt* pFmt = NULL, USHORT* pParentId = 0 );
//STRIP001  USHORT  InAttrSet( SwAttrSet& rSet );
//STRIP001  USHORT  InAttrSet( SwCntntNode& rNd );
//STRIP001  void    FillAttrSet( SwAttrSet& rSet, USHORT nId );
//STRIP001  BOOL    TestPoolFmt( SwFmt&, int );

//STRIP001  void    RegisterFrmId( SwFrm& rFrm, USHORT nId );
//STRIP001  SwFrm*  FindFrmId( USHORT nId );

//STRIP001  void    RegisterTable( USHORT nIdx, const SwTable *pTable );
//STRIP001  const SwTable *FindTable( USHORT nIdx );

//STRIP001  USHORT  RegisterSection( const SwNodeIndex& rStart, USHORT nId );

//STRIP001  SwNode* InNodeId();
//STRIP001  SwFrm*  InFrame();
//STRIP001  void    InFrmRect( SwRect&, SwRect* );

//STRIP001  SwPageDesc& FindPageDesc( USHORT nIdx );

            // Methoden fuer Hints:
//STRIP001  void    Error( ULONG = 0 );
//STRIP001  void    AddPageDescLink( const String&, USHORT nOff );
//STRIP001  String  GetText( BOOL bReq = TRUE );
//STRIP001  ByteString GetAsciiText( BOOL bReq = TRUE );
//STRIP001  SwField* InField();
//STRIP001  SwStartNode* InSection();
//STRIP001  void    FillSection( SwNodeIndex& rPos );
//STRIP001  void    InTextBlock( long );
//STRIP001  Color   InColor();
//STRIP001  void    InPen(USHORT& nWidth, Color& rCol);
//STRIP001  Color   InBrush();
//STRIP001
//STRIP001  void SetReadTxt( const ByteString* pTxt )   { pNdOrigTxt = pTxt; }
//STRIP001  const ByteString* GetReadTxt() const        { return pNdOrigTxt; }
//STRIP001
//STRIP001  BOOL    IsTableBoxFrmFmt() { return BOOL( nFmtLvl == (nTblBoxLvl+1) ); }
//STRIP001 };


#endif // _RDSWG_HXX
