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
#ifndef _SVX_BOXOBJ_HXX
#define _SVX_BOXOBJ_HXX

#include <bf_svtools/bf_solar.h>

#include <bf_sfx2/shobj.hxx>
namespace binfilter {
class SvxBoxItem;
class SvxBoxInfoItem;
class SvxBorderLine;

//-------------------------------------------------------------------------

class SvxBoxObject: public SfxShellSubObject

/*  [Beschreibung]

    Diese SbxObject-Subklasse kann das <SvxBoxItem> und <SvxBoxInfoItem>
    im SBX-System recorden und wieder abspielen. Hier werden keine
    G"ultigkeitspr"ufungen durchgef"uhrt, diese m"ussen in abgeleiteten
    Klassen spezifisch implementiert werden; dazu sind virtuelle Methoden
    vorhanden.
*/

{
friend class SvxBoxLineObject_Impl;

    SvxBoxItem*             pBox;
    SvxBoxInfoItem*         pBoxInfo;

#ifdef _SVX_BOXOBJ_CXX
private:
    const SvxBorderLine*    GetLine_Impl( USHORT nSID ) const;
    BOOL                    SetLine_Impl( USHORT nSID, const SvxBorderLine *pLine );
    void                    Update_Impl() const;
#endif

protected:
    // Schnittstelle zum SbxObject/SfxShell..Object
    void                    SFX_NOTIFY( SfxBroadcaster& rBC, const TypeId& rBCType,
                                    const SfxHint& rHint, const TypeId& rHintType );
    virtual ULONG           SetProperty( USHORT nSID, SbxVariable &rRet );
    virtual ULONG           GetProperty( USHORT nSID, SbxVariable &rRet );

    // bei den folgenden Methoden sind die Items bereits besorgt worden
    virtual SbxError        GetLineColor( USHORT nSID, Color &rColor ) const;
    virtual SbxError        GetLineStyle( USHORT nSID,
                                          USHORT &rOutWidth, USHORT &rDist, USHORT &rInWidth ) const;
    virtual SbxError        GetDistance( USHORT &rDist ) const;

    // nach den folgenden Methoden werden die Items wieder in die Shell gesetzt
    virtual SbxError        SetLineColor( USHORT nSID, const Color &rColor );
    virtual SbxError        SetLineStyle( USHORT nSID,
                                          USHORT nOutWidth, USHORT nDist, USHORT nInWidth );
    virtual SbxError        SetDistance( USHORT nDist );

public:
                            TYPEINFO();
                            SvxBoxObject( SfxShell *pShell = 0 );

                            ~SvxBoxObject();

    const SvxBoxItem&       GetBoxItem() const { return *pBox; }
    const SvxBoxInfoItem&   GetBoxInfoItem() const { return *pBoxInfo; }

    virtual String          GenerateSource( const String &rLinePrefix,
                                            const SbxObject *pRelativeTo );
};

}//end of namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
