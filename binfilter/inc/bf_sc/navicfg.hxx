/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: navicfg.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: hr $ $Date: 2007-01-02 18:27:21 $
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

#ifndef SC_NAVICFG_HXX
#define SC_NAVICFG_HXX

#ifndef _SOLAR_H
#include <tools/solar.h>
#endif
namespace binfilter {


//==================================================================
// CfgItem fuer Navigator-Zustand
//==================================================================

class ScNavipiCfg
{
private:
    USHORT  nListMode;
    USHORT  nDragMode;
    USHORT  nRootType;

public:
            ScNavipiCfg();

    USHORT  GetListMode() const         { return nListMode; }
    USHORT  GetDragMode() const         { return nDragMode; }
    USHORT  GetRootType() const         { return nRootType; }
};


} //namespace binfilter
#endif

