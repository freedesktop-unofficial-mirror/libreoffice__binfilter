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
#ifndef _SVX_POSTATTR_HXX
#define _SVX_POSTATTR_HXX

namespace binfilter {

// class SvxPostItAuthorItem ---------------------------------------------

#ifdef ITEMID_AUTHOR

/*
[Beschreibung]
Dieses Item beschreibt das Autoren-Kuerzel eines Notizzettels.
*/

class SvxPostItAuthorItem: public SfxStringItem
{
public:
    TYPEINFO();

};
#endif

// class SvxPostItDateItem -----------------------------------------------

#ifdef ITEMID_DATE

/*
[Beschreibung]
Dieses Item beschreibt das Datum eines Notizzettels.
*/

class SvxPostItDateItem: public SfxStringItem
{
public:
    TYPEINFO();

};
#endif

// class SvxPostItTextItem -----------------------------------------------

#ifdef ITEMID_TEXT

/*
[Beschreibung]
Dieses Item beschreibt den Text eines Notizzettels.
*/

class SvxPostItTextItem: public SfxStringItem
{
public:
    TYPEINFO();

};
#endif

}//end of namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
