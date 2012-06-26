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

#ifndef _SV_SECTION_HXX
#define _SV_SECTION_HXX

#include <bf_svtools/bf_solar.h>

#include <vcl/sv.h>
#include <vcl/ctrl.hxx>
#include <vcl/dockwin.hxx>

#include <vcl/tabpage.hxx>

#include <bf_svtools/expander.hxx>

#include <bf_svtools/privsplt.hxx>

namespace binfilter
{

class SvSectionControl;

class SvSection : public DockingWindow
{
private:
        SvSectionControl*       pSectionControl;
        USHORT                  nSectionID;
        Window*                 pChildWin;
        XubString               aName;
        long                    nHeight;
        long                    nMinHeight;
        long                    nMinWidth;
        long                    nOldHeight;

        DECL_LINK( ToggleHdl,   SvExpander* );
        DECL_LINK( SplitHdl,    SvPrivatSplit* );

        void                    ImplExpandSection();
        void                    ImplShrinkSection();

protected:
        SvExpander              aExpander;
        Window                  aChildWinContainer;
        SvPrivatSplit           aPrivatSplit;

        virtual void            Resize();
        virtual void            Paint( const Rectangle& rRect );
        virtual long            Notify( NotifyEvent& rNEvt );

public:
        SvSection(const XubString& rName,SvSectionControl* pParent,
                    WinBits nStyle = 0);
        SvSection(const XubString& rName,SvSectionControl* pParent,
                    Window* pChildWin, WinBits nStyle = 0);

        virtual void            SetScrollPos(long nPos);
        void                    SetChildPos(long nPos);

        void                    SetSectionControl(SvSectionControl* pParent);
        const SvSectionControl* GetSectionControl()const ;
        void                    SetSectionText( const XubString& );
        const XubString&            GetSectionText() const {return aName;}

        void                    SetChildWin(Window* pChildWin);
        Window*                 GetChildWin() const {return pChildWin;}

        void                    SetSectionID(USHORT nId) {nSectionID=nId;}
        USHORT                  GetSectionID() const {return nSectionID;}

        void                    SetMaxHeight(long nHeight);
        long                    GetMaxHeight();

        void                    SetMinHeight(long nHeight);
        long                    GetMinHeight();

        void                    SetMinWidth(long nWidth);
        long                    GetMinWidth();

        void                    ExpandSection();
        void                    ShrinkSection();
        BOOL                    IsExpanded();
};

}

#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
