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
#ifndef _SVX_ADRITEM_HXX
#define _SVX_ADRITEM_HXX

#include <bf_svtools/bf_solar.h>

// include ---------------------------------------------------------------

#include <bf_svtools/stritem.hxx>
namespace binfilter {

// define ----------------------------------------------------------------

#define POS_COMPANY     ((USHORT) 0)
#define POS_STREET      ((USHORT) 1)
#define POS_COUNTRY     ((USHORT) 2)
#define POS_PLZ         ((USHORT) 3)
#define POS_CITY        ((USHORT) 4)
#define POS_TITLE       ((USHORT) 5)
#define POS_POSITION    ((USHORT) 6)
#define POS_TEL_PRIVATE ((USHORT) 7)
#define POS_TEL_COMPANY ((USHORT) 8)
#define POS_FAX         ((USHORT) 9)
#define POS_EMAIL       ((USHORT)10)
#define POS_STATE       ((USHORT)11)
#define POS_FATHERSNAME ((USHORT)12)
#define POS_APARTMENT   ((USHORT)13)
#define POS_FIRSTNAME   ((USHORT)14)
#define POS_LASTNAME    ((USHORT)15)
#define POS_SHORTNAME   ((USHORT)16)

#define SfxAddressItem  SvxAddressItem

const char cAdrToken = '#';

// forward ---------------------------------------------------------------

class SfxIniManager;

// class SvxAddressItem --------------------------------------------------

class SvxAddressItem : public SfxStringItem
{
private:
    String  aName;
    String  aFirstName;
    String  aShortName;

public:
    TYPEINFO();

    SvxAddressItem( USHORT nWhich = 0 );
    SvxAddressItem( const String& rAddress, const String& rShortName,
                    const String& rFirstName, const String& rName,
                    USHORT nWhich = 0 );
    SvxAddressItem( SvStream& rStrm, USHORT nWhich = 0 );
    SvxAddressItem( const SvxAddressItem& );
    ~SvxAddressItem() {}



    BOOL                    SetToken( USHORT nPos, const String &rVal );
    String                  GetToken( USHORT nPos ) const;
    String                  GetFirstName() const    { return aFirstName; }
    String                  GetName() const         { return aName; }
    String                  GetShortName() const    { return aShortName; }
    String                  GetEmail() const        { return GetToken( POS_EMAIL ); }

    sal_Bool                IsTokenReadonly( USHORT nToken ) const;

#if _SOLAR__PRIVATE
    String                  GetCompany() const      { return GetToken( POS_COMPANY ); }
    String                  GetStreet() const       { return GetToken( POS_STREET ); }
    String                  GetCountry() const      { return GetToken( POS_COUNTRY ); }
    String                  GetPLZ() const          { return GetToken( POS_PLZ ); }
    String                  GetCity() const         { return GetToken( POS_CITY ); }
    String                  GetTitle() const        { return GetToken( POS_TITLE ); }
    String                  GetPosition() const     { return GetToken( POS_POSITION ); }
    String                  GetTelPriv() const      { return GetToken( POS_TEL_PRIVATE ); }
    String                  GetTelCompany() const   { return GetToken( POS_TEL_COMPANY ); }
    String                  GetFax() const          { return GetToken( POS_FAX ); }
    String                  GetState() const        { return GetToken( POS_STATE ); }
    String                  GetFatherName() const   { return GetToken( POS_FATHERSNAME ); }
    String                  GetApartmentNr() const  { return GetToken( POS_APARTMENT ); }
#endif
};

}//end of namespace binfilter
#endif // #ifndef _SVX_ADRITEM_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
