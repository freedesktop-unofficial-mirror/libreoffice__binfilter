/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: app.hxx,v $
 *
 *  $Revision: 1.8 $
 *
 *  last change: $Author: obo $ $Date: 2007-07-17 12:19:27 $
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
#ifndef _OFF_APP_HXX
#define _OFF_APP_HXX

// include ---------------------------------------------------------------

#ifndef _SFXAPP_HXX //autogen
#include <bf_sfx2/app.hxx>
#endif

class ResMgr;

namespace binfilter {


#define OFA_REFERER         "private:user"

// forward ---------------------------------------------------------------

class XColorTable;
class  OfficeData_Impl;

// class OfficeApplication -----------------------------------------------

class OfficeApplication : public SfxApplication
{
private:
    OfficeData_Impl*            pDataImpl;

    virtual void                Init( );

public:
                                TYPEINFO();

                                OfficeApplication();
                                ~OfficeApplication();

    ResMgr*                     GetOffResManager();
    XColorTable*                GetStdColorTable();
};

#define OFF_APP()   ( (OfficeApplication*)SfxGetpApp() )

} //namespace binfilter
#endif // #ifndef _OFF_APP_HXX

