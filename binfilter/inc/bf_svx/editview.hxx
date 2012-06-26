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

// MyEDITVIEW, wegen exportiertem EditView
#ifndef _MyEDITVIEW_HXX
#define _MyEDITVIEW_HXX

#include <bf_svtools/bf_solar.h>

#include <rsc/rscsfx.hxx>

#include <tools/color.hxx>
class Window;
class Pointer;
class Cursor;
class KeyEvent;
class MouseEvent;
class Rectangle;
class Link;
class Pair;
class Point;
class Range;
class SvStream;
namespace binfilter {
class SvKeyValueIterator;

class SfxStyleSheet;
class EditEngine;
class ImpEditEngine;
class ImpEditView;
class SvxFieldItem;
class DropEvent;
class CommandEvent;
}//end of namespace binfilter //namespace binfilter
#include <bf_svx/editdata.hxx>

#include <com/sun/star/uno/Reference.h>

namespace com {
namespace sun {
namespace star {
namespace datatransfer {
    class XTransferable;
}}}}

namespace binfilter {
class EditView
{
    friend class EditEngine;
    friend class ImpEditEngine;
    friend class EditSelFunctionSet;

public: // brauche ich fuer Undo
    ImpEditView*    GetImpEditView() const      { return pImpEditView; }

private:
    ImpEditView*    pImpEditView;

                    EditView( const EditView& );

public:
    virtual         ~EditView();

    EditEngine*     GetEditEngine() const;

    Window*         GetWindow() const;


    void            ShowCursor( BOOL bGotoCursor = TRUE, BOOL bForceVisCursor = TRUE );
    void            HideCursor();

    BOOL            HasSelection() const;
    ESelection      GetSelection() const;
    void            SetSelection( const ESelection& rNewSel );


    const Rectangle&    GetOutputArea() const;

    const Rectangle&    GetVisArea() const;

};

}//end of namespace binfilter
#endif // _MyEDITVIEW_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
