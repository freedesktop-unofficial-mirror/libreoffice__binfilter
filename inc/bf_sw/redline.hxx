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
#ifndef _REDLINE_HXX
#define _REDLINE_HXX

#include <bf_svtools/bf_solar.h>

#include <tools/datetime.hxx>
#include <bf_tools/string.hxx>

#define _SVSTDARR_USHORTS
#include <bf_svtools/svstdarr.hxx>

#include <pam.hxx>
#include <redlenum.hxx>
namespace binfilter {
class SfxItemSet;



class SwRedlineData
{
    friend class SwRedline;
    SwRedlineData* pNext;       // Verweis auf weitere Daten

    String sComment;
    DateTime aStamp;
    SwRedlineType eType;
    USHORT nAuthor, nSeqNo;

public:
    SwRedlineData( const SwRedlineData& rCpy, BOOL bCpyNext = TRUE );

    // fuer sw3io: pNext/pExtraData gehen in eigenen Besitz ueber!
    SwRedlineData( SwRedlineType eT, USHORT nAut, const DateTime& rDT,
                   const String& rCmnt, SwRedlineData* pNxt );

    ~SwRedlineData();

    int operator==( const SwRedlineData& rCmp ) const
        {
            return nAuthor == rCmp.nAuthor
                && eType == rCmp.eType
                && sComment == rCmp.sComment
                && (  (  !pNext && !rCmp.pNext )
                   || (  pNext
                      && rCmp.pNext
                      && *pNext == *rCmp.pNext
                      )
                   );
        }
    int operator!=( const SwRedlineData& rCmp ) const
        {   return !operator==( rCmp ); }

    SwRedlineType GetType() const
        { return SwRedlineType( eType & REDLINE_NO_FLAG_MASK); }
    SwRedlineType GetRealType() const       { return eType; }
    USHORT GetAuthor() const                { return nAuthor; }
    const String& GetComment() const        { return sComment; }
    const DateTime& GetTimeStamp() const    { return aStamp; }
    inline const SwRedlineData* Next() const{ return pNext; }

    void SetTimeStamp( const DateTime& rDT)
        { aStamp = rDT; aStamp.SetSec( 0 ); aStamp.Set100Sec( 0 ); }
    void SetComment( const String& rS )     { sComment = rS; }
    void SetAutoFmtFlag()
        { eType = SwRedlineType( eType | REDLINE_FORM_AUTOFMT ); }
    int CanCombine( const SwRedlineData& rCmp ) const
        {
            return nAuthor == rCmp.nAuthor
                && eType == rCmp.eType
                && sComment == rCmp.sComment
                && GetTimeStamp() == rCmp.GetTimeStamp()
                && (  (  !pNext
                      && !rCmp.pNext
                      )
                   || (  pNext
                      && rCmp.pNext
                      && pNext->CanCombine( *rCmp.pNext )
                      )
                   );
        }

    // fuers UI-seitige zusammenfassen von Redline-Actionen. Wird z.Z. nur
    // fuers Autoformat mit Redline benoetigt. Der Wert != 0 bedeutet dabei,
    // das es noch weitere geben kann!
    USHORT GetSeqNo() const                     { return nSeqNo; }
    void SetSeqNo( USHORT nNo )                 { nSeqNo = nNo; }
};


class SwRedline : public SwPaM
{
    SwRedlineData* pRedlineData;
    SwNodeIndex* pCntntSect;
    BOOL bDelLastPara : 1;
    BOOL bIsLastParaDelete : 1;
    BOOL bIsVisible : 1;


public:
    SwRedline( const SwRedlineData& rData, const SwPosition& rPos );
    // fuer sw3io: pData geht in eigenen Besitz ueber!
    SwRedline(SwRedlineData* pData, const SwPosition& rPos, BOOL bVsbl,
               BOOL bDelLP, BOOL bIsPD) :
        SwPaM( rPos ), pRedlineData( pData ), pCntntSect( 0 ),
        bDelLastPara( bDelLP ), bIsLastParaDelete( bIsPD ), bIsVisible( bVsbl )
    {}
    SwRedline( const SwRedline& );
    virtual ~SwRedline();

    SwNodeIndex* GetContentIdx() const { return pCntntSect; }

    BOOL IsVisible() const { return bIsVisible; }
    BOOL IsDelLastPara() const { return bDelLastPara; }
    BOOL IsLastParaDelete() const { return bIsLastParaDelete; }

    // das BOOL besagt, ob nach dem setzen der Pos kein Bereich mehr
    // aufgespannt ist. -> TRUE, ansonten Bereich und FALSE
    void SetStart( const SwPosition& rPos, SwPosition* pSttPtr = 0 )
    {
        if( !pSttPtr ) pSttPtr = Start();
        *pSttPtr = rPos;
    }
    void SetEnd( const SwPosition& rPos, SwPosition* pEndPtr = 0 )
    {
        if( !pEndPtr ) pEndPtr = End();
        *pEndPtr = rPos;
    }
    // liegt eine gueltige Selektion vor?
/*N*/   BOOL HasValidRange() const; //SW50.SDW

    USHORT GetAuthor() const { return pRedlineData->GetAuthor(); }
    const DateTime& GetTimeStamp() const { return pRedlineData->GetTimeStamp(); }
    SwRedlineType GetType() const { return pRedlineData->GetType(); }
    SwRedlineType GetRealType() const { return pRedlineData->GetRealType(); }
    const SwRedlineData& GetRedlineData() const { return *pRedlineData; }
    int operator==( const SwRedlineData& rCmp ) const
        { return *pRedlineData == rCmp; }
    int operator!=( const SwRedlineData& rCmp ) const
        { return *pRedlineData != rCmp; }
    void SetAutoFmtFlag()               { pRedlineData->SetAutoFmtFlag(); }

    const String& GetAuthorString( USHORT nPos = 0 ) const;

    const String& GetComment() const    { return pRedlineData->GetComment(); }
    void SetComment( const String& rS ) { pRedlineData->SetComment( rS ); }

    // fuers UI-seitige zusammenfassen von Redline-Actionen. Wird z.Z. nur
    // fuers Autoformat mit Redline benoetigt. Der Wert != 0 bedeutet dabei,
    // das es noch weitere geben kann!
    USHORT GetSeqNo() const             { return pRedlineData->GetSeqNo(); }
    void SetSeqNo( USHORT nNo )         { pRedlineData->SetSeqNo( nNo ); }

    // calculates the intersection with text node number nNdIdx

    BOOL IsOwnRedline( const SwRedline& rRedl ) const
        { return GetAuthor() == rRedl.GetAuthor(); }
    BOOL CanCombine( const SwRedline& rRedl ) const;


     int operator==( const SwRedline& ) const;
    int operator<( const SwRedline& ) const;
};

} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
