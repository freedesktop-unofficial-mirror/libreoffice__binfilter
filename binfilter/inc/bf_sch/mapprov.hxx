/*************************************************************************
 *
 *  $RCSfile: mapprov.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 20:52:46 $
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

#ifndef SCH_MAPPROV_HXX
#define SCH_MAPPROV_HXX

// header for SfxItemPropertyMap
#ifndef _SFX_ITEMPROP_HXX
#include <svtools/itemprop.hxx>
#endif

// auto strip #ifndef _SCH_UNONAMES_HXX
// auto strip #include "unonames.hxx"
// auto strip #endif
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

