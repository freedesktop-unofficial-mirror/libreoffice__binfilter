/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: postattr.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 03:54:03 $
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
#ifndef _SVX_POSTATTR_HXX
#define _SVX_POSTATTR_HXX

// include ---------------------------------------------------------------

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

