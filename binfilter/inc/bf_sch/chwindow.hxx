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

#ifndef _SCH_SDWINDOW_HXX
#define _SCH_SDWINDOW_HXX


#include <tools/gen.hxx>
#include <vcl/window.hxx>
#include <vcl/event.hxx>
#include <bf_svtools/transfer.hxx>
namespace com { namespace sun { namespace star {
    namespace accessibility {
        class XAccessible;
    }
}}}
namespace binfilter {

class SchViewShell;
class ChartModel;


namespace accessibility
{
    class AccessibleDocumentView;
}

/*************************************************************************
|*
|* SchWindow beinhaltet den eigentlichen Arbeitsbereich von
|* SchViewShell
|*
\************************************************************************/
class SchWindow : public Window, public DropTargetHelper
{
protected:
    Point   aWinPos;
    Point   aViewOrigin;
    Size    aViewSize;

    SchViewShell* pViewShell;


    // for quick help

    /** Create an accessibility object that makes this window accessible.

        @return
            The returned reference is empty if no accessible object could be
            created.
    */

private:
    // for quick help

    /// attention: this pointer is only valid, if the weak reference below is valid
    ::binfilter::accessibility::AccessibleDocumentView * m_pAccDocumentView;
    ::com::sun::star::uno::WeakReference< ::com::sun::star::accessibility::XAccessible >
        m_xAccDocumentView;

public:
    SchWindow(Window* pParent);
    virtual ~SchWindow();

    void SetViewShell(SchViewShell* pViewSh) { pViewShell=pViewSh; };


    void SetZoom(long nZoom);
    long SetZoomFactor(long nZoom);

    long GetZoom() const
        { return GetMapMode().GetScaleX().GetNumerator() * 100L /
                 GetMapMode().GetScaleX().GetDenominator(); }

    void SetWinPos(const Point& rPos) { aWinPos = rPos; }
    const Point& GetWinPos() { return aWinPos; }
    void SetViewOrigin(const Point& rPos) { aViewOrigin = rPos; }
    const Point& GetViewOrigin() { return aViewOrigin; }
    void SetViewSize(const Size& rSize) { aViewSize = rSize; }
    const Size& GetViewSize() { return aViewSize; }


    // DropTargetHelper



};

} //namespace binfilter
#endif      // _SCH_SDWINDOW_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
