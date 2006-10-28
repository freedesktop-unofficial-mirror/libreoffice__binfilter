/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: adritem.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 03:19:39 $
 *
 *  The Contents of this file are made available subject to
 *  the terms of GNU Lesser General Public License Version 2.1.
 *
 *
 *    GNU Lesser General Public License Version 2.1
 *    =============================================
 *    Copyright 2005 by Sun Microsystems, Inc.
 *    901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *    This library is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License version 2.1, as published by the Free Software Foundation.
 *
 *    This library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with this library; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *    MA  02111-1307  USA
 *
 ************************************************************************/
#ifndef _SVX_ADRITEM_HXX
#define _SVX_ADRITEM_HXX

// include ---------------------------------------------------------------

#ifndef _SFXSTRITEM_HXX //autogen
#include <svtools/stritem.hxx>
#endif
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

