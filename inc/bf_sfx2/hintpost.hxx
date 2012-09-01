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
#ifndef _SFXHINTPOST_HXX
#define _SFXHINTPOST_HXX

#include <bf_sfx2/genlink.hxx>

#include <tools/ref.hxx>
namespace binfilter {

class SfxHint;

//===================================================================


//-------------------------------------------------------------------

class SfxHintPoster: public SvRefBase

/*  [Beschreibung]

    Mit Instanzen dieser Klasse k"onnen eindeutige Events per PostUserEvent
    "uber die StarView-Application verschickt werden. Wenn das User-Event
    ausgel"ost wird, wird der Handler <Event()> gerufen, dessen
    Basisimplementierung den mit <SetEventHdl()> angegbenen Link ruft.

    Die Instanz wird via Ref-Count mindestens solange gehalten, wie
    ein ggf. abgeschicktes Event noch nicht angekommen ist. Sollte das
    Ziel vorher sterben, ist die Verbindung zuvor mit 'SetEventHdl(GenLink())'
    zu kappen.
*/

{
    ULONG           nId;
    GenLink         aLink;

protected:
    virtual         ~SfxHintPoster();
    virtual void    Event( SfxHint* pPostedHint );
};

//-------------------------------------------------------------------

SV_DECL_IMPL_REF(SfxHintPoster);

}//end of namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
