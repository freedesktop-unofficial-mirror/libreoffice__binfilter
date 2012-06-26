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
#ifndef SW_LINEINFO_HXX
#define SW_LINEINFO_HXX

#include <bf_svtools/bf_solar.h>


#include "calbck.hxx"
#include "numrule.hxx"
namespace binfilter {

class SwCharFmt;
class SwDoc;

enum LineNumberPosition
{
    LINENUMBER_POS_LEFT,
    LINENUMBER_POS_RIGHT,
    LINENUMBER_POS_INSIDE,
    LINENUMBER_POS_OUTSIDE
};

class SwLineNumberInfo : public SwClient //purpose of derivation from SwClient:
                                         //character style for displaying the numbers.
{
    SvxNumberType       aType;              //e.g. roman linenumbers
    String              aDivider;           //String for aditional interval (vert. lines user defined)
    USHORT              nPosFromLeft;       //Position for paint
    USHORT              nCountBy;           //Paint only for every n line
    USHORT              nDividerCountBy;    //Interval for display of an user defined
                                            //string every n lines
    LineNumberPosition  ePos;               //Where should the display occur (number and divicer)
    BOOL                bPaintLineNumbers;  //Should anything be displayed?
    BOOL                bCountBlankLines;   //Count empty lines?
    BOOL                bCountInFlys;       //Count also within FlyFrames?
    BOOL                bRestartEachPage;   //Restart counting at the first paragraph of each page
                                            //(even on follows when paragraphs are splitted)

public:
    SwLineNumberInfo();
    SwLineNumberInfo(const SwLineNumberInfo&);

    SwLineNumberInfo& operator=(const SwLineNumberInfo&);
    BOOL operator==( const SwLineNumberInfo& rInf ) const;

    SwCharFmt *GetCharFmt(SwDoc &rDoc) const;
    void SetCharFmt( SwCharFmt* );

    const SvxNumberType &GetNumType() const             { return aType; }
    void                SetNumType( SvxNumberType aNew ){ aType = aNew; }

    const String &GetDivider() const    { return aDivider; }
    void SetDivider( const String &r )  { aDivider = r; }
    USHORT GetDividerCountBy() const    { return nDividerCountBy; }
    void SetDividerCountBy( USHORT n )  { nDividerCountBy = n; }

    USHORT GetPosFromLeft() const       { return nPosFromLeft; }
    void   SetPosFromLeft( USHORT n)    { nPosFromLeft = n;    }

    USHORT GetCountBy() const           { return nCountBy; }
    void   SetCountBy( USHORT n)        { nCountBy = n;    }

    LineNumberPosition GetPos() const   { return ePos; }
    void SetPos( LineNumberPosition eP ){ ePos = eP;   }

    BOOL   IsPaintLineNumbers() const   { return bPaintLineNumbers; }
    void   SetPaintLineNumbers( BOOL b ){ bPaintLineNumbers = b;    }

    BOOL   IsCountBlankLines() const    { return bCountBlankLines;  }
    void   SetCountBlankLines( BOOL b ) { bCountBlankLines = b;     }

    BOOL   IsCountInFlys() const        { return bCountInFlys;      }
    void   SetCountInFlys( BOOL b )     { bCountInFlys = b;         }

    BOOL   IsRestartEachPage() const    { return bRestartEachPage;  }
    void   SetRestartEachPage( BOOL b ) { bRestartEachPage = b;     }

    virtual void Modify( SfxPoolItem*, SfxPoolItem* );
};



} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
