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

#ifndef _EDITSEL_HXX
#define _EDITSEL_HXX

#include <vcl/seleng.hxx>
namespace binfilter {

class EditView;

//  ----------------------------------------------------------------------
//  class EditSelFunctionSet
//  ----------------------------------------------------------------------
class EditSelFunctionSet: public FunctionSet
{
private:
    EditView*       pCurView;

public:
                    EditSelFunctionSet();

    virtual void    BeginDrag()         {}
    virtual void    CreateAnchor()      {}
    virtual void    DestroyAnchor()     {}

    virtual BOOL    SetCursorAtPoint(
                        const Point& /* rPointPixel */,
                        BOOL = FALSE
                    )
                    { return FALSE; }

    virtual BOOL    IsSelectionAtPoint( const Point& /* rPointPixel */ )
                    { return FALSE; }

    virtual void    DeselectAtPoint( const Point& /* rPointPixel */ )
                    {}

    virtual void    DeselectAll()       {}

    void            SetCurView( EditView* pView )       { pCurView = pView; }
    EditView*       GetCurView()                        { return pCurView; }
};

// ----------------------------------------------------------------------
//  class EditSelectionEngine
//  ----------------------------------------------------------------------
class EditSelectionEngine : public SelectionEngine
{
public:
                    EditSelectionEngine();

    void            SetCurView( EditView* pNewView );
};

}//end of namespace binfilter
#endif // _EDITSEL_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
