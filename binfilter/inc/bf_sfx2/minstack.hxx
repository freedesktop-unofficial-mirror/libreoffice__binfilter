/*************************************************************************
 *
 *  $RCSfile: minstack.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 20:59:26 $
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
#ifndef _SFXMINSTACK_HXX
#define _SFXMINSTACK_HXX

//ASDBG #ifndef _SFXMINARRAY_HXX
// auto strip #ifndef _SFXVARARR_HXX
// auto strip #include <bf_sfx2/minarray.hxx>
// auto strip #endif
namespace binfilter {

#define DECL_OBJSTACK( ARR, T, nI, nG ) \
DECL_OBJARRAY( ARR##arr_, T, nI, nG ); \
class ARR: private ARR##arr_ \
{ \
public: \
    ARR( BYTE nInitSize = nI, BYTE nGrowSize = nG ): \
        ARR##arr_( nInitSize, nGrowSize ) \
    {} \
\
    ARR( const ARR& rOrig ): \
        ARR##arr_( rOrig ) \
    {} \
\
    USHORT      Count() const { return ARR##arr_::Count(); } \
    void        Push( const T& rElem ) { Append( rElem ); } \
    const T& Top( USHORT nLevel = 0 ) const \
                { return (*this)[Count()-nLevel-1]; } \
    const T& Bottom() const { return (*this)[0]; } \
    T        Pop(); \
    void        Clear() { ARR##arr_::Clear(); } \
    BOOL        Contains( const T& rItem ) const \
                { return ARR##arr_::Contains( rItem ); } \
}

#define IMPL_OBJSTACK( ARR, T ) \
IMPL_OBJARRAY( ARR##arr_, T ); \
\
T ARR::Pop() \
{   T aRet = (*this)[Count()-1]; \
    Remove( Count()-1, 1 ); \
    return aRet; \
}
//STRIP008 the following "DECL_PTRARRAY( ARR##arr_, T, nI, nG );\" should be "DECL_PTRARRAY( ARR##arr_, T, nI, nG )\"
#define DECL_PTRSTACK( ARR, T, nI, nG ) \
DECL_PTRARRAY( ARR##arr_, T, nI, nG ) \
class ARR: private ARR##arr_ \
{ \
public: \
    ARR( BYTE nInitSize = nI, BYTE nGrowSize = nG ): \
        ARR##arr_( nInitSize, nGrowSize ) \
    {} \
\
    ARR( const ARR& rOrig ): \
        ARR##arr_( rOrig ) \
    {} \
\
    USHORT      Count() const { return ARR##arr_::Count(); } \
    void        Push( T rElem ) { Append( rElem ); } \
    BOOL        Replace( T rOldElem, T rNewElem ) \
                { return ARR##arr_::Replace( rOldElem, rNewElem ); } \
    T           Top( USHORT nLevel = 0 ) const \
                { return (*this)[Count()-nLevel-1]; } \
    T           Bottom() const { return (*this)[0]; } \
    T           Pop() \
                {   T aRet = (*this)[Count()-1]; \
                    Remove( Count()-1, 1 ); \
                    return aRet; \
                } \
    T*       operator*() \
                { return &(*this)[Count()-1]; } \
    void        Clear() { ARR##arr_::Clear(); } \
    BOOL        Contains( const T pItem ) const \
                { return ARR##arr_::Contains( pItem ); } \
}

}//end of namespace binfilter
#endif

