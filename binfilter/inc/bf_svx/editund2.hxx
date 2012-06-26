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

#ifndef _EDITUND2_HXX
#define _EDITUND2_HXX

#include <bf_svtools/undo.hxx>
namespace binfilter {

class ImpEditEngine;

class EditUndoManager : public SfxUndoManager
{
private:
    ImpEditEngine*  pImpEE;
public:
                    EditUndoManager( ImpEditEngine* pImpEE );

};

// -----------------------------------------------------------------------
// EditUndo
// ------------------------------------------------------------------------
class EditUndo : public SfxUndoAction
{
private:
    USHORT          nId;
    ImpEditEngine*  pImpEE;

public:
                    EditUndo( USHORT nI, ImpEditEngine* pImpEE );
    virtual         ~EditUndo();

    ImpEditEngine*  GetImpEditEngine() const    { return pImpEE; }

    using SfxUndoAction::Repeat;

    virtual String  GetComment() const;
    virtual USHORT  GetId() const;
};

}//end of namespace binfilter
#endif  // _EDITUND2_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
