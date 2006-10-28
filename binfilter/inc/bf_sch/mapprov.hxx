/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: mapprov.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 02:48:44 $
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

#ifndef SCH_MAPPROV_HXX
#define SCH_MAPPROV_HXX

// header for SfxItemPropertyMap
#ifndef _SFX_ITEMPROP_HXX
#include <svtools/itemprop.hxx>
#endif

namespace binfilter {

// ----------------------------------------------
//                   Map-Id's
// ----------------------------------------------

#define CHMAP_NONE                   0
#define CHMAP_CHART                  1
#define CHMAP_AREA                   2
#define CHMAP_LINE                   3
#define CHMAP_DOC                    4
#define CHMAP_AXIS                   5
#define CHMAP_LEGEND                 6
#define CHMAP_TITLE                  7
#define CHMAP_DATAROW                8
#define CHMAP_DATAPOINT              9
#define CHMAP_END                   10      // last one used + 1

class ChartModel;

// ----------------------------------------------
//      Map-Provider ( to sort the maps )
// ----------------------------------------------

class SchUnoPropertyMapProvider
{
private:
    SfxItemPropertyMap* pMapArr[ CHMAP_END ];
    void Sort( short nId );

public:
    SchUnoPropertyMapProvider();
    ~SchUnoPropertyMapProvider();

    SfxItemPropertyMap* GetMap( short PropertyId, ChartModel* );
    SfxItemPropertyMap* CopyMap( const SfxItemPropertyMap* pMap1 );
};

} //namespace binfilter
#endif  // SCH_MAPPROV_HXX

