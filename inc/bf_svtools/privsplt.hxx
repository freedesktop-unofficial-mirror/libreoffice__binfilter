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

#ifndef _SV_PRIVSPLT_HXX
#define _SV_PRIVSPLT_HXX

#include <vcl/fixed.hxx>

namespace binfilter
{

enum PRIVSPLIT_DIRECTION {PRIVSPLIT_HORZ,PRIVSPLIT_VERT };

class SvPrivatSplit : public FixedLine
{
    private:

        Link                aCtrModifiedLink;
        BOOL                aMovingFlag;
        Pointer             aWinPointer;
        PRIVSPLIT_DIRECTION eAdrSplit;
        short               nOldX;
        short               nOldY;
        short               nNewX;
        short               nNewY;
        short               nMinPos;
        short               nMaxPos;
        Range               aXMovingRange;
        Range               aYMovingRange;
        short               nDeltaX;
        short               nDeltaY;
        void                ImplInitSettings( BOOL bFont, BOOL bForeground, BOOL bBackground );

    protected:
        virtual void        MouseButtonDown( const MouseEvent& rMEvt );
        virtual void        Tracking( const TrackingEvent& rTEvt );

    public:

        SvPrivatSplit( Window* pWindow, const ResId& rResId,PRIVSPLIT_DIRECTION eAdrSplit);

        SvPrivatSplit( Window* pParent,PRIVSPLIT_DIRECTION eAdrSplit, WinBits nStyle = 0);

        virtual short   GetDeltaX();
        virtual short   GetDeltaY();

        virtual void    CtrModified();

        void            SetXRange(Range cRgeX);
        void            SetYRange(Range cRgeY);

        void            MoveSplitTo(Point aPos);

        virtual void    StateChanged( StateChangedType nType );
        virtual void    DataChanged( const DataChangedEvent& rDCEvt );

        void            SetCtrModifiedHdl( const Link& rLink ) { aCtrModifiedLink = rLink; }
        const Link&     GetCtrModifiedHdl() const { return aCtrModifiedLink; }
};

}

#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
