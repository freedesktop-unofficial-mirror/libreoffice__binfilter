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

// MyEDITDATA, wegen exportiertem EditData
#ifndef _MyEDITDATA_HXX
#define _MyEDITDATA_HXX

#include <bf_svtools/bf_solar.h>

#include <bf_tools/string.hxx>

#include <bf_svtools/svarray.hxx>
namespace binfilter {

class SfxItemSet;
class SfxPoolItem;
class SfxStyleSheet;

class SvParser;
class SvxFieldItem;

enum EETextFormat       { EE_FORMAT_TEXT = 0x20, EE_FORMAT_RTF, EE_FORMAT_BIN = 0x31, EE_FORMAT_HTML, EE_FORMAT_XML };
enum EEHorizontalTextDirection { EE_HTEXTDIR_DEFAULT, EE_HTEXTDIR_L2R, EE_HTEXTDIR_R2L };

#define EE_PARA_NOT_FOUND       0xFFFF
#define EE_PARA_APPEND          0xFFFF
#define EE_PARA_ALL             0xFFFF
#define EE_APPEND               0xFFFF
#define EE_INDEX_NOT_FOUND      0xFFFF

// Fehlermeldungen fuer Read/Write-Methode
#define EE_READWRITE_OK              (SVSTREAM_OK)
#define EE_READWRITE_WRONGFORMAT     (SVSTREAM_ERRBASE_USER+1)
#define EE_READWRITE_GENERALERROR    (SVSTREAM_ERRBASE_USER+2)

#define EDITUNDO_START              100
#define EDITUNDO_REMOVECHARS        100
#define EDITUNDO_CONNECTPARAS       101
#define EDITUNDO_REMOVEFEATURE      102
#define EDITUNDO_MOVEPARAGRAPHS     103
#define EDITUNDO_INSERTFEATURE      104
#define EDITUNDO_SPLITPARA          105
#define EDITUNDO_INSERTCHARS        106
#define EDITUNDO_DELCONTENT         107
#define EDITUNDO_DELETE             108
#define EDITUNDO_CUT                109
#define EDITUNDO_PASTE              110
#define EDITUNDO_INSERT             111
#define EDITUNDO_SRCHANDREPL        112
#define EDITUNDO_MOVEPARAS          113
#define EDITUNDO_PARAATTRIBS        114
#define EDITUNDO_ATTRIBS            115
#define EDITUNDO_DRAGANDDROP        116
#define EDITUNDO_READ               117
#define EDITUNDO_STYLESHEET         118
#define EDITUNDO_REPLACEALL         119
#define EDITUNDO_STRETCH            120
#define EDITUNDO_RESETATTRIBS       121
#define EDITUNDO_INDENTBLOCK        122
#define EDITUNDO_UNINDENTBLOCK      123
#define EDITUNDO_MARKSELECTION      124
#define EDITUNDO_TRANSLITERATE      125
#define EDITUNDO_END                125

#define EDITUNDO_USER               200

#define EE_COMPATIBLEMODE_PARAGRAPHSPACING_SUMMATION            0x0001
#define EE_COMPATIBLEMODE_PARAGRAPHSPACING_BEFOREFIRSTPARAGRAPH 0x0002

class EditView;
class EditEngine;
class ImpEditView;
class ImpEditEngine;
class EditTextObject;

#define RGCHK_NONE          0   // Keine Korrektur der ViusArea beim Scrollen
#define RGCHK_NEG           1   // Keine neg. ViusArea beim Scrollen
#define RGCHK_PAPERSZ1      2   // VisArea muss in Papierbreite,Texthoehe liegen

struct EPosition
{
    USHORT      nPara;
    xub_StrLen  nIndex;

    EPosition()
    {
        nPara = EE_PARA_NOT_FOUND;
        nIndex = EE_INDEX_NOT_FOUND;
    }

    EPosition( USHORT nPara_, xub_StrLen nPos_ )
    {
        nPara = nPara_;
        nIndex = nPos_;
    }

    EPosition( const EPosition& rPosition )
    {
        nPara = rPosition.nPara;
        nIndex = rPosition.nIndex;
    }
};

struct ESelection
{
    USHORT      nStartPara;
    xub_StrLen  nStartPos;
    USHORT      nEndPara;
    xub_StrLen  nEndPos;

    ESelection() { nStartPara = 0; nStartPos = 0; nEndPara = 0; nEndPos = 0; }

    ESelection( USHORT nStPara, xub_StrLen nStPos, USHORT nEPara, xub_StrLen nEPos )
    {
        nStartPara  = nStPara;
        nStartPos   = nStPos;
        nEndPara    = nEPara;
        nEndPos     = nEPos;
    }

    ESelection( USHORT nPara, xub_StrLen nPos )
    {
        nStartPara  = nPara;
        nStartPos   = nPos;
        nEndPara    = nPara;
        nEndPos     = nPos;
    }

    ESelection( const ESelection& r )
    {
        nStartPara  = r.nStartPara;
        nStartPos   = r.nStartPos;
        nEndPara    = r.nEndPara;
        nEndPos     = r.nEndPos;
    }

    ESelection& operator = ( const ESelection& r )
    {
        nStartPara  = r.nStartPara;
        nStartPos   = r.nStartPos;
        nEndPara    = r.nEndPara;
        nEndPos     = r.nEndPos;
        return *this;
    }

    void    Adjust();
    BOOL    IsEqual( const ESelection& rS );
    BOOL    IsLess( const ESelection& rS );
    BOOL    IsGreater( const ESelection& rS );
    BOOL    IsZero();
    BOOL    HasRange() const;
};

inline BOOL ESelection::HasRange() const
{
    return ( nStartPara != nEndPara ) || ( nStartPos != nEndPos );
}

inline sal_Bool ESelection::IsZero()
{
    return ( ( nStartPara == 0 ) && ( nStartPos == 0 ) &&
             ( nEndPara == 0 ) && ( nEndPos == 0 ) );
}

inline sal_Bool ESelection::IsEqual( const ESelection& rS )
{
    return ( ( nStartPara == rS.nStartPara ) && ( nStartPos == rS.nStartPos ) &&
             ( nEndPara == rS.nEndPara ) && ( nEndPos == rS.nEndPos ) );
}

inline sal_Bool ESelection::IsLess( const ESelection& rS )
{
    // Selektion muss justiert sein.
    // => Nur pueffen, ob Ende von 'this' < Start von rS

    if ( ( nEndPara < rS.nStartPara ) ||
         ( ( nEndPara == rS.nStartPara ) && ( nEndPos < rS.nStartPos ) && !IsEqual( rS ) ) )
    {
        return sal_True;
    }
    return sal_False;
}

inline sal_Bool ESelection::IsGreater( const ESelection& rS )
{
    // Selektion muss justiert sein.
    // => Nur pueffen, ob Ende von 'this' > Start von rS

    if ( ( nStartPara > rS.nEndPara ) ||
         ( ( nStartPara == rS.nEndPara ) && ( nStartPos > rS.nEndPos ) && !IsEqual( rS ) ) )
    {
        return sal_True;
    }
    return sal_False;
}

inline void ESelection::Adjust()
{
    sal_Bool bSwap = sal_False;
    if ( nStartPara > nEndPara )
        bSwap = sal_True;
    else if ( ( nStartPara == nEndPara ) && ( nStartPos > nEndPos ) )
        bSwap = sal_True;

    if ( bSwap )
    {
        sal_uInt16 nSPar = nStartPara; sal_uInt16 nSPos = nStartPos;
        nStartPara = nEndPara; nStartPos = nEndPos;
        nEndPara = nSPar; nEndPos = nSPos;
    }
}

struct EFieldInfo
{
    SvxFieldItem*   pFieldItem;
    String          aCurrentText;
    EPosition       aPosition;

    EFieldInfo();
    EFieldInfo( const SvxFieldItem& rFieldItem, USHORT nPara, USHORT nPos );
    ~EFieldInfo();

    EFieldInfo( const EFieldInfo& );
};

// -----------------------------------------------------------------------

enum ImportState {
                    RTFIMP_START, RTFIMP_END,               // nur pParser, nPara, nIndex
                    RTFIMP_NEXTTOKEN, RTFIMP_UNKNOWNATTR,   // nToken+nTokenValue
                    RTFIMP_SETATTR,                         // pAttrs
                    RTFIMP_INSERTTEXT,                      // aText
                    RTFIMP_INSERTPARA,                      // -
                    HTMLIMP_START, HTMLIMP_END,             // nur pParser, nPara, nIndex
                    HTMLIMP_NEXTTOKEN, HTMLIMP_UNKNOWNATTR, // nToken
                    HTMLIMP_SETATTR,                        // pAttrs
                    HTMLIMP_INSERTTEXT,                     // aText
                    HTMLIMP_INSERTPARA, HTMLIMP_INSERTFIELD // -
                    };

struct ImportInfo
{
    SvParser*               pParser;
    ESelection              aSelection;
    ImportState             eState;

    int                     nToken;
    short                   nTokenValue;

    String                  aText;

    void*                   pAttrs; // RTF: SvxRTFItemStackType*, HTML: SfxItemSet*

    ImportInfo( ImportState eState, SvParser* pPrsrs, const ESelection& rSel );
    ~ImportInfo();
};

#define EE_SEARCH_WORDONLY      0x0001
#define EE_SEARCH_EXACT         0x0002
#define EE_SEARCH_BACKWARD      0x0004
#define EE_SEARCH_INSELECTION   0x0008
#define EE_SEARCH_REGEXPR       0x0010
#define EE_SEARCH_PATTERN       0x0020

struct ParagraphInfos
{
    USHORT  nParaHeight;
    USHORT  nLines;

    USHORT  nFirstLineStartX;

    USHORT  nFirstLineOffset;
    USHORT  nFirstLineHeight;
    USHORT  nFirstLineTextHeight;
    USHORT  nFirstLineMaxAscent;

    BOOL    bValid; // Bei einer Abfrage waehrend der Formatierung ungueltig!
};

struct MoveParagraphsInfo
{
    USHORT  nStartPara;
    USHORT  nEndPara;
    USHORT  nDestPara;

    MoveParagraphsInfo( USHORT nS, USHORT nE, USHORT nD )
        { nStartPara = nS; nEndPara = nE; nDestPara = nD; }
};

#define EE_ACTION_PASTE 1
#define EE_ACTION_DROP  2

struct PasteOrDropInfos
{
    USHORT  nAction;
    USHORT  nStartPara;
    USHORT  nEndPara;
    SfxStyleSheet* pLevel0Style;
    SfxStyleSheet* pLevelNStyle;

    PasteOrDropInfos()
        {   nStartPara = 0xFFFF; nEndPara = 0xFFFF;
            pLevel0Style = NULL; pLevelNStyle = NULL; nAction = 0; }
};

enum EENotifyType
{
    /// EditEngine text was modified
    EE_NOTIFY_TEXTMODIFIED,

    /// A paragraph was inserted into the EditEngine
    EE_NOTIFY_PARAGRAPHINSERTED,

    /// A paragraph was removed from the EditEngine
    EE_NOTIFY_PARAGRAPHREMOVED,

    /// Multiple paragraphs have been removed from the EditEngine
    EE_NOTIFY_PARAGRAPHSMOVED,

    /// The height of at least one paragraph has changed
    EE_NOTIFY_TEXTHEIGHTCHANGED,

    /// The view area of the EditEngine scrolled
    EE_NOTIFY_TEXTVIEWSCROLLED,

    /// The selection and/or the cursor position has changed
    EE_NOTIFY_TEXTVIEWSELECTIONCHANGED,

    /** Denotes the beginning of a collected amount of EditEngine
        notification events. This event itself is not queued, but sent
        immediately
     */
    EE_NOTIFY_BLOCKNOTIFICATION_START,

    /** Denotes the end of a collected amount of EditEngine
        notification events. After this event, the queue is empty, and
        a high-level operation such as "insert paragraph" is finished
     */
    EE_NOTIFY_BLOCKNOTIFICATION_END,

    /// Denotes the beginning of a high-level action triggered by a key press
    EE_NOTIFY_INPUT_START,

    /// Denotes the end of a high-level action triggered by a key press
    EE_NOTIFY_INPUT_END
};

struct EENotify
{
    EENotifyType    eNotificationType;
    EditEngine*     pEditEngine;
    EditView*       pEditView;

    USHORT          nParagraph; // only valid in PARAGRAPHINSERTED/EE_NOTIFY_PARAGRAPHREMOVED

    USHORT          nParam1;
    USHORT          nParam2;

    EENotify( EENotifyType eType )
        { eNotificationType = eType; pEditEngine = NULL; pEditView = NULL; nParagraph = EE_PARA_NOT_FOUND; nParam1 = 0; nParam2 = 0; }
};

}//end of namespace binfilter
#endif // _MyEDITDATA_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
