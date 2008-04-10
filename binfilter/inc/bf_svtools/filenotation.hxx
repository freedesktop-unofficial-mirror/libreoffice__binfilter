/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: filenotation.hxx,v $
 * $Revision: 1.3 $
 *
 * This file is part of OpenOffice.org.
 *
 * OpenOffice.org is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * only, as published by the Free Software Foundation.
 *
 * OpenOffice.org is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License version 3 for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 *
 * You should have received a copy of the GNU Lesser General Public License
 * version 3 along with OpenOffice.org.  If not, see
 * <http://www.openoffice.org/license.html>
 * for a copy of the LGPLv3 License.
 *
 ************************************************************************/

#ifndef SVTOOLS_FILENOTATION_HXX
#define SVTOOLS_FILENOTATION_HXX

#ifndef _RTL_USTRING_HXX_
#include <rtl/ustring.hxx>
#endif

//.........................................................................
namespace binfilter
{
//.........................................................................

    //=====================================================================
    //= OFileNotation
    //=====================================================================
    class  OFileNotation
    {
    protected:
        ::rtl::OUString     m_sSystem;
        ::rtl::OUString     m_sFileURL;

    public:
        enum NOTATION
        {
            N_SYSTEM,
            N_URL
        };

        OFileNotation( const ::rtl::OUString& _rUrlOrPath );
        OFileNotation( const ::rtl::OUString& _rUrlOrPath, NOTATION _eInputNotation );

        ::rtl::OUString get(NOTATION _eOutputNotation);

    private:
         void   construct( const ::rtl::OUString& _rUrlOrPath );
         bool    implInitWithSystemNotation( const ::rtl::OUString& _rSystemPath );
         bool    implInitWithURLNotation( const ::rtl::OUString& _rURL );
    };

//.........................................................................
}
//.........................................................................

#endif // SVTOOLS_FILENOTATION_HXX

