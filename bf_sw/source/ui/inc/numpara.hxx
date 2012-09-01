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
#ifndef _NUMPARA_HXX
#define _NUMPARA_HXX

#include <bf_svtools/bf_solar.h>


#include <vcl/lstbox.hxx>
#include <vcl/fixed.hxx>
#include <vcl/field.hxx>
#include <vcl/button.hxx>
namespace binfilter {


/* --- class SwParagraphNumTabPage ----------------------------------------
    Mit dieser TabPage werden Numerierungseinstellungen am Absatz bzw. der
    Absatzvorlage vorgenommen.

 ---------------------------------------------------------------------------*/
class SwParagraphNumTabPage : public SfxTabPage
{
    FixedText               aNumberStyleFT;
    ListBox                 aNumberStyleLB;

    FixedLine               aNewStartFL;
    TriStateBox             aNewStartCB;
    TriStateBox             aNewStartNumberCB;
    NumericField            aNewStartNF;

    FixedLine               aCountParaFL;
    TriStateBox             aCountParaCB;
    TriStateBox             aRestartParaCountCB;
    FixedText               aRestartFT;
    NumericField            aRestartNF;

    BOOL                    bModified : 1;
    BOOL                    bCurNumrule : 1;

    DECL_LINK( NewStartHdl_Impl, CheckBox* );
    DECL_LINK( StyleHdl_Impl, ListBox* );
    DECL_LINK( LineCountHdl_Impl, CheckBox* );

protected:
        SwParagraphNumTabPage(Window* pParent, const SfxItemSet& rSet );

public:
        ~SwParagraphNumTabPage();

    static SfxTabPage*  Create( Window* pParent,
                                const SfxItemSet& rSet );
    static USHORT*      GetRanges();

    virtual BOOL        FillItemSet( SfxItemSet& rSet );
    virtual void        Reset( const SfxItemSet& rSet );

    void                EnableNewStart();

    ListBox&            GetStyleBox() {return aNumberStyleLB;};

};


} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
