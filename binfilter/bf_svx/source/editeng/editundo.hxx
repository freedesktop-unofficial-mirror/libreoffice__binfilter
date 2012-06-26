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

#ifndef _EDITUNDO_HXX
#define _EDITUNDO_HXX

#include <editdoc.hxx>
#include <editund2.hxx>
#include <editdata.hxx>

namespace binfilter {

class ImpEditEngine;
class EditView;

// -----------------------------------------------------------------------
// EditUndoInsertChars
// ------------------------------------------------------------------------
class EditUndoInsertChars : public EditUndo
{
private:
    EPaM            aEPaM;
    String          aText;

public:
                    TYPEINFO();
                    EditUndoInsertChars( ImpEditEngine* pImpEE, const EPaM& rEPaM, const String& rStr );

    using SfxUndoAction::Repeat;

    virtual BOOL    Merge( SfxUndoAction *pNextAction );
};

// -----------------------------------------------------------------------
// EditUndoInsertFeature
// ------------------------------------------------------------------------
class EditUndoInsertFeature : public EditUndo
{
private:
    EPaM            aEPaM;
    SfxPoolItem*    pFeature;

public:
                    EditUndoInsertFeature( ImpEditEngine* pImpEE, const EPaM& rEPaM,
                                            const SfxPoolItem& rFeature);
                    ~EditUndoInsertFeature();

    using SfxUndoAction::Repeat;
};

// -----------------------------------------------------------------------
// EditUndoSetStyleSheet
// ------------------------------------------------------------------------
class EditUndoSetStyleSheet: public EditUndo
{
private:
    USHORT          nPara;
    XubString       aPrevName;
    XubString       aNewName;
    SfxStyleFamily  ePrevFamily;
    SfxStyleFamily  eNewFamily;
    SfxItemSet      aPrevParaAttribs;

public:

                    EditUndoSetStyleSheet( ImpEditEngine* pImpEE, USHORT nPara,
                        const XubString& rPrevName, SfxStyleFamily ePrevFamily,
                        const XubString& rNewName, SfxStyleFamily eNewFamily,
                        const SfxItemSet& rPrevParaAttribs );

    using SfxUndoAction::Repeat;
};

// -----------------------------------------------------------------------
// EditUndoSetParaAttribs
// ------------------------------------------------------------------------
class EditUndoSetParaAttribs: public EditUndo
{
private:
    USHORT          nPara;
    SfxItemSet      aPrevItems;
    SfxItemSet      aNewItems;

public:
                    EditUndoSetParaAttribs( ImpEditEngine* pImpEE, USHORT nPara, const SfxItemSet& rPrevItems, const SfxItemSet& rNewItems );

    using SfxUndoAction::Repeat;
};

}//end of namespace binfilter
#endif // _EDITUNDO_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
