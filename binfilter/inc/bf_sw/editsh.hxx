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
#ifndef _EDITSH_HXX
#define _EDITSH_HXX

#include <bf_svtools/bf_solar.h>

#include <bf_tools/string.hxx>
#include <bf_svtools/svarray.hxx>
#include <vcl/font.hxx>
#include <bf_svx/swafopt.hxx>
#include <crsrsh.hxx>   // fuer Basisklasse
#include <itabenum.hxx>
#include <swdbdata.hxx>
#include <com/sun/star/linguistic2/XSpellAlternatives.hpp>

namespace com { namespace sun { namespace star { namespace uno {
    template < class > class Sequence;
}}}}
class PolyPolygon;
class DateTime;
class CommandExtTextInputData;

class Graphic;          // fuer GetGraphic
class Font;
namespace binfilter {
class SvStringsDtor;
class SvInPlaceObjectRef;
class SvInPlaceObject;
class SvNumberFormatter;
class SfxPoolItem;
class SfxItemSet;
class BfGraphicObject; // fuer GetGraphicObj


class SwDoc;
class SvxLinkManager;
class SvxAutoCorrect;

class SwField;          // fuer Felder
class SwFieldType;
class SwDDEFieldType;
class SwNewDBMgr;

struct SwDocStat;
class SfxDocumentInfo;

class SvStringsSort;
class SwAutoCompleteWord;

class SwFmtRefMark;
class SwFmtCol;
class SwNumRule;        // Numerierung
class SwNodeNum;        // Numerierung
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
class SwFmtINetFmt;     // InsertURL

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
    // fuer die privaten Methoden DelRange und die vom AutoCorrect
    friend void _InitCore();
    friend void _FinitCore();
    // fuer die PamCorrAbs/-Rel Methoden

    SfxPoolItem& _GetChrFmt( SfxPoolItem& ) const;

    /*
     * liefert einen Pointer auf einen SwGrfNode; dieser wird von
     * GetGraphic() und GetGraphicSize() verwendet.
     */



public:

#ifdef USED
    // GRF
    USHORT GetGrfFmtCollCount() const;
    SwGrfFmtColl& GetGrfFmtColl( USHORT nGrfFmtColl) const;
    void DelGrfFmtColl(USHORT nFmt);
    SwGrfFmtColl* GetCurGrfFmtColl() const;
    void SetGrfFmtColl(SwGrfFmtColl*);
    SwGrfFmtColl *MakeGrfFmtColl(const String &rFmtCollName,
        SwGrfFmtColl *pDerivedFrom = 0);
#endif

        // Gebe die "Auto-Collection" mit der Id zurueck. Existiert
        // sie noch nicht, dann erzuege sie
        // return das geforderte automatische  Format - Basis-Klasse !
        // returne die geforderte automatische Seiten-Vorlage
        // returne die geforderte automatische NumRule

    // erfrage ob die Absatz-/Zeichen-/Rahmen-/Seiten - Vorlage benutzt wird

        // returne das geforderte automatische Format

    // Felder
    void Insert(SwField&);


    //check whether DB fields point to an available data source and returns it
    BOOL IsFieldDataSourceAvailable(String& rUsedDataSource) const;

    // Is spelling active somewhere else?
    // Is text conversion active somewhere else?
    BOOL HasConvIter() const;

    // special insert: Insert a new text node just before or after a section or
    // table, if the cursor is positioned at the start/end of said
    // section/table. The purpose of the method is to allow users to inert text
    // at certain 'impossible' position, e.g. before a table at the document
    // start or between to sections.
    bool DoSpecialInsert();
    bool CanSpecialInsert() const;

    // Optimierung UI

    inline const SvxLinkManager& GetLinkManager() const;

    // Numberformatter vom Doc erfragen
    const SvNumberFormatter* GetNumberFormatter() const
    {   return ((SwEditShell*)this)->GetNumberFormatter();  }

    virtual ~SwEditShell() {}

private:
    // fuer METWARE:
    // es wird nicht kopiert und nicht zugewiesen
    SwEditShell(const SwEditShell &);
    const SwEditShell &operator=(const SwEditShell &);
};

inline const SvxLinkManager& SwEditShell::GetLinkManager() const
{   return ((SwEditShell*)this)->GetLinkManager();  }

} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
