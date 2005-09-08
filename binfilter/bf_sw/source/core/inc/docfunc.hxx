/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: docfunc.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-08 09:26:10 $
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
#ifndef _DOCFUNC_HXX
#define _DOCFUNC_HXX


// Diese Klasse wird von der Editshell benutz um fuer belibige
// Doc-Aktionen ueber eine definierte Schnittstelle alle Cursor/
// Bookmarks/usw. aus dem Loeschbereich zu verschieben, mit einem
// anschliessenden Join-Node.
// Das wird zur Zeit vom
//      - Delete
//      - Replace
// benotigt.


#ifndef _STRING_HXX //autogen
#include <tools/string.hxx>
#endif
namespace binfilter {
class SwPaM;

enum DocFNType { DOC_DELETE, DOC_REPLACE };

class SwCallDocFunction
{
    // Parameter fuers Replace  (leider kein union moeglich; Str-Klasse !!)
    const String aRplStr;
    DocFNType eDocFnType;
    BOOL bRplRegExp;

public:
    // fuer parameterlose Methoden
    SwCallDocFunction( DocFNType eDocFn ) : eDocFnType( eDocFn ), aRplStr() {}
    // fuer das Replace
    SwCallDocFunction( const String& rStr, BOOL bFlag );

    BOOL Call( SwPaM& );

    // ALLE Methoden stehen im eddel.cxx !!
};


} //namespace binfilter
#endif
    //_DOCFUNC_HXX


