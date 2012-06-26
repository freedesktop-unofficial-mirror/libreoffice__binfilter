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

#ifndef _EDITOBJ_HXX
#define _EDITOBJ_HXX

#include <bf_svtools/bf_solar.h>

#include <tools/stream.hxx>
#include <tools/debug.hxx>
#include <rsc/rscsfx.hxx>
#include <bf_svtools/itemset.hxx>
#include <bf_svx/eeitem.hxx>
namespace binfilter {

class SfxItemPool;
class SfxStyleSheetPool;

DBG_NAMEEX( EE_EditTextObject )

class SvxFieldItem;

#define EDTOBJ_SETTINGS_ULITEMSUMMATION     0x00000001
#define EDTOBJ_SETTINGS_ULITEMFIRSTPARA     0x00000002

class EditTextObject
{
private:
    USHORT              nWhich;

protected:
                        EditTextObject( USHORT nWhich );
                        EditTextObject( const EditTextObject& r );

    virtual void        StoreData( SvStream& ) const
                        {}

    virtual void        CreateData( SvStream& /* rIStream */ )
                        {}

public:
    virtual             ~EditTextObject();

    USHORT              Which() const { return nWhich; }

    virtual USHORT      GetUserType() const
                        { return 0; }

    virtual void        SetUserType( USHORT /* n */ )
                        {}

    virtual BOOL        IsVertical() const
                        { return FALSE; }

    virtual void        SetVertical( BOOL )
                        {}

    virtual USHORT      GetVersion() const
                        { return 0; }

    virtual EditTextObject* Clone() const = 0;

    BOOL Store( SvStream& ) const {return FALSE;}
    static EditTextObject*  Create( SvStream& rIStream,
                                SfxItemPool* pGlobalTextObjectPool = 0 );

    virtual void        AdjustImportedLRSpaceItems( BOOL /* bTurnOfBullets */ )
                        {}

    virtual void        FinishLoad( SfxStyleSheetPool* /* pStyleSheetPool */ )
                        {}

    virtual USHORT      GetParagraphCount() const
                        { return 0; }

    virtual XubString   GetText( USHORT ) const
                        { return XubString(); }

    virtual void        Insert( const EditTextObject& /* rObj */, USHORT /* nPara */ )
                        {}

    virtual void        ClearPortionInfo()
                        {}

    virtual void        MergeParaAttribs(
                            const SfxItemSet&,
                            USHORT = EE_CHAR_START,
                            USHORT = EE_CHAR_END
                        ) {}

    virtual BOOL        HasField( TypeId = NULL ) const
                        { return FALSE; }

    virtual SfxItemSet  GetParaAttribs( USHORT nPara ) const;

    virtual void        GetStyleSheet(
                            USHORT          /* nPara   */,
                            XubString&      /* rName   */,
                            SfxStyleFamily& /* eFamily */
                        ) const {}

    virtual void        SetStyleSheet(
                            USHORT                  /* nPara   */,
                            const XubString&        /* rName   */,
                            const SfxStyleFamily&   /* eFamily */
                        ) {}

    virtual BOOL        ChangeStyleSheets(
                            const XubString&    /* rOldName   */,
                            SfxStyleFamily      /* eOldFamily */,
                            const XubString&    /* rNewName   */,
                            SfxStyleFamily      /* eNewFamily */
                        )
                        { return FALSE; }

    virtual void        ChangeStyleSheetName(
                            SfxStyleFamily      /* eFamily  */,
                            const XubString&    /* rOldName */,
                            const XubString&    /* rNewName */
                        ) {}
};

}//end of namespace binfilter
#endif  // _EDITOBJ_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
