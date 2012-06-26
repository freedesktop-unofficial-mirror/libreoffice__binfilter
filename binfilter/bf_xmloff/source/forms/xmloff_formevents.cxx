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

#include "xmlevent.hxx"
namespace binfilter {

//.........................................................................
namespace xmloff
{
//.........................................................................

    //=====================================================================
    //= event translation table
    //=====================================================================
    static const XMLEventNameTranslation aEventTranslations[] =
    {
        { "XApproveActionListener::approveAction",      "on-approveaction" },
        { "XActionListener::actionPerformed",           "on-performaction" },
        { "XChangeListener::changed",                   "on-change" },
        { "XTextListener::textChanged",                 "on-textchange" },
        { "XItemListener::itemStateChanged",            "on-itemstatechange" },
        { "XFocusListener::focusGained",                "on-focus" },
        { "XFocusListener::focusLost",                  "on-blur" },
        { "XKeyListener::keyPressed",                   "on-keydown" },
        { "XKeyListener::keyReleased",                  "on-keyup" },
        { "XMouseListener::mouseEntered",               "on-mouseover" },
        { "XMouseMotionListener::mouseDragged",         "on-mousedrag" },
        { "XMouseMotionListener::mouseMoved",           "on-mousemove" },
        { "XMouseListener::mousePressed",               "on-mousedown" },
        { "XMouseListener::mouseReleased",              "on-mouseup" },
        { "XMouseListener::mouseExited",                "on-mouseout" },
        { "XResetListener::approveReset",               "on-approvereset" },
        { "XResetListener::resetted",                   "on-reset" },
        { "XSubmitListener::approveSubmit",             "on-submit" },
        { "XUpdateListener::approveUpdate",             "on-approveupdate" },
        { "XUpdateListener::updated",                   "on-update" },
        { "XLoadListener::loaded",                      "on-load" },
        { "XLoadListener::reloading",                   "on-startreload" },
        { "XLoadListener::reloaded",                    "on-reload" },
        { "XLoadListener::unloading",                   "on-startunload" },
        { "XLoadListener::unloaded",                    "on-unload" },
        { "XConfirmDeleteListener::confirmDelete",      "on-confirmdelete" },
        { "XRowSetApproveListener::approveRowChange",   "on-approverowchange" },
        { "XRowSetListener::rowChanged",                "on-rowchange" },
        { "XRowSetApproveListener::approveCursorMove",  "on-approvecursormove" },
        { "XRowSetListener::cursorMoved",               "on-cursormove" },
        { "XDatabaseParameterListener::approveParameter","on-supplyparameter" },
        { "XSQLErrorListener::errorOccured",            "on-error" },
        { 0, 0 }
    };

    const XMLEventNameTranslation* g_pFormsEventTranslation = aEventTranslations;

//.........................................................................
}   // namespace xmloff
//.........................................................................


}//end of namespace binfilter

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
