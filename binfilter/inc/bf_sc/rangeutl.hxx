/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: rangeutl.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 02:40:31 $
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

#ifndef SC_RANGEUTL_HXX
#define SC_RANGEUTL_HXX

#ifndef _STRING_HXX //autogen
#include <tools/string.hxx>
#endif
class SvStream;
namespace binfilter {

//------------------------------------------------------------------------


class ScArea;
class ScDocument;
class ScRefTripel;
class ScTripel;
class ScRange;
class ScRangeName;
class ScDBCollection;

enum RutlNameScope { RUTL_NONE=0, RUTL_NAMES, RUTL_DBASE };

//------------------------------------------------------------------------

class ScRangeUtil
{
public:
                ScRangeUtil()  {}
                ~ScRangeUtil() {}



    void    CutPosString        ( const String&     theAreaStr,
                                  String&           thePosStr ) const;


    BOOL    IsAbsArea           ( const String& rAreaStr,
                                  ScDocument*   pDoc,
                                  USHORT        nTab,
                                  String*       pCompleteStr = 0,
                                  ScRefTripel*  pStartPos    = 0,
                                  ScRefTripel*  pEndPos      = 0 ) const;


    BOOL    MakeRangeFromName   ( const String& rName,
                                    ScDocument*     pDoc,
                                    USHORT          nCurTab,
                                    ScRange&        rRange,
                                    RutlNameScope eScope=RUTL_NAMES
                                  ) const;
};

//------------------------------------------------------------------------

class ScArea
{
public:
            ScArea( USHORT tab      = 0,
                    USHORT colStart = 0,
                    USHORT rowStart = 0,
                    USHORT colEnd   = 0,
                    USHORT rowEnd   = 0 );

            ScArea( const ScArea& r );

    ScArea& operator=   ( const ScArea& r );

public:
    USHORT nTab;
    USHORT nColStart;
    USHORT nRowStart;
    USHORT nColEnd;
    USHORT nRowEnd;
};

/*N#116571#*/ SvStream& operator<< ( SvStream& rStream, const ScArea& rArea );
/*N#116571#*/ SvStream& operator>> ( SvStream& rStream, ScArea& rArea );

//------------------------------------------------------------------------

//
//  gibt Bereiche mit Referenz und alle DB-Bereiche zurueck
//



} //namespace binfilter
#endif // SC_RANGEUTL_HXX

