/*************************************************************************
 *
 *  $RCSfile: postattr.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 08:28:30 $
 *
 *  The Contents of this file are made available subject to the terms of
 *  either of the following licenses
 *
 *         - GNU Lesser General Public License Version 2.1
 *         - Sun Industry Standards Source License Version 1.1
 *
 *  Sun Microsystems Inc., October, 2000
 *
 *  GNU Lesser General Public License Version 2.1
 *  =============================================
 *  Copyright 2000 by Sun Microsystems, Inc.
 *  901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License version 2.1, as published by the Free Software Foundation.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *  MA  02111-1307  USA
 *
 *
 *  Sun Industry Standards Source License Version 1.1
 *  =================================================
 *  The contents of this file are subject to the Sun Industry Standards
 *  Source License Version 1.1 (the "License"); You may not use this file
 *  except in compliance with the License. You may obtain a copy of the
 *  License at http://www.openoffice.org/license.html.
 *
 *  Software provided under this License is provided on an "AS IS" basis,
 *  WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING,
 *  WITHOUT LIMITATION, WARRANTIES THAT THE SOFTWARE IS FREE OF DEFECTS,
 *  MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE, OR NON-INFRINGING.
 *  See the License for the specific provisions governing your rights and
 *  obligations concerning the Software.
 *
 *  The Initial Developer of the Original Code is: Sun Microsystems, Inc.
 *
 *  Copyright: 2000 by Sun Microsystems, Inc.
 *
 *  All Rights Reserved.
 *
 *  Contributor(s): _______________________________________
 *
 *
 ************************************************************************/
#ifndef _SVX_POSTATTR_HXX
#define _SVX_POSTATTR_HXX

// include ---------------------------------------------------------------

#ifndef _SFXSTRITEM_HXX //autogen
#include <svtools/stritem.hxx>
#endif
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

//STRIP001  SvxPostItAuthorItem( USHORT nWhich = ITEMID_AUTHOR );
//STRIP001
//STRIP001  SvxPostItAuthorItem( const String& rAuthor, USHORT nWhich = ITEMID_AUTHOR );
//STRIP001  virtual SfxItemPresentation GetPresentation( SfxItemPresentation ePres,
//STRIP001                                  SfxMapUnit eCoreMetric,
//STRIP001                                  SfxMapUnit ePresMetric,
//STRIP001                                     String &rText, const IntlWrapper * = 0 ) const;
//STRIP001
//STRIP001  virtual SfxPoolItem*    Clone( SfxItemPool *pPool = 0 ) const;
//STRIP001
//STRIP001  inline SvxPostItAuthorItem& operator=( const SvxPostItAuthorItem& rAuthor )
//STRIP001  {
//STRIP001      SetValue( rAuthor.GetValue() );
//STRIP001      return *this;
//STRIP001  }
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

//STRIP001  SvxPostItDateItem( USHORT nWhich = ITEMID_DATE );
//STRIP001
//STRIP001  SvxPostItDateItem( const String& rDate, USHORT nWhich = ITEMID_DATE );
//STRIP001  virtual SfxItemPresentation GetPresentation( SfxItemPresentation ePres,
//STRIP001                                  SfxMapUnit eCoreMetric,
//STRIP001                                  SfxMapUnit ePresMetric,
//STRIP001                                     String &rText, const IntlWrapper * = 0 ) const;
//STRIP001  virtual SfxPoolItem*    Clone( SfxItemPool *pPool = 0 ) const;
//STRIP001
//STRIP001  inline SvxPostItDateItem& operator=( const SvxPostItDateItem& rDate )
//STRIP001  {
//STRIP001      SetValue( rDate.GetValue() );
//STRIP001      return *this;
//STRIP001  }
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

//STRIP001  SvxPostItTextItem( USHORT nWhich = ITEMID_TEXT );
//STRIP001
//STRIP001  SvxPostItTextItem( const String& rText, USHORT nWhich = ITEMID_TEXT );
//STRIP001  // "pure virtual Methoden" vom SfxPoolItem
//STRIP001  virtual SfxItemPresentation GetPresentation( SfxItemPresentation ePres,
//STRIP001                                  SfxMapUnit eCoreMetric,
//STRIP001                                  SfxMapUnit ePresMetric,
//STRIP001                                     String &rText, const IntlWrapper * = 0 ) const;
//STRIP001
//STRIP001  virtual SfxPoolItem*    Clone( SfxItemPool *pPool = 0 ) const;
//STRIP001
//STRIP001  inline SvxPostItTextItem& operator=( const SvxPostItTextItem& rText )
//STRIP001  {
//STRIP001      SetValue( rText.GetValue() );
//STRIP001      return *this;
//STRIP001  }
};
#endif

}//end of namespace binfilter
#endif

