/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw3marks.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 10:11:15 $
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
#ifndef _SW3MARKS_HXX
#define _SW3MARKS_HXX

#ifndef _SOLAR_H
#include <tools/solar.h>
#endif
#ifndef _CNTNRSRT_HXX
#include <bf_svtools/cntnrsrt.hxx>
#endif
namespace binfilter {

enum Sw3MarkType {
    SW3_TOX_POINT, SW3_TOX_MARK,
    SW3_BOOK_POINT, SW3_BOOK_MARK,
    SW3_REDLINE_START, SW3_REDLINE_END,
    SW3_MARKTYPE_END
};

class Sw3Mark
{
    friend int sw3mark_compare( const Sw3Mark& r1, const Sw3Mark& r2 );

    Sw3MarkType eType;                  // Art des Eintrags
    ULONG       nNodePos;               // Node-Index
    xub_StrLen  nNodeOff;               // Position-Index
    USHORT      nId;                    // ID des Eintrags

public:

    Sw3Mark() : eType(SW3_TOX_POINT), nNodePos(0),nNodeOff(0), nId(0) {}
    Sw3Mark( Sw3Mark& r ) : eType(r.eType), nNodePos(r.nNodePos),
                            nNodeOff(r.nNodeOff), nId(r.nId) {}

    Sw3MarkType GetType() const     { return  eType; }
    ULONG       GetNodePos() const  { return  nNodePos; }
    xub_StrLen  GetNodeOff() const  { return  nNodeOff; }
    USHORT      GetId() const       { return  nId; }

    void SetType( Sw3MarkType nSet ){ eType = nSet; }
    void SetNodePos( ULONG nSet )   { nNodePos = nSet; }
    void SetNodeOff( xub_StrLen nSet )  { nNodeOff = nSet; }
    void SetId( USHORT nSet )       { nId = nSet; }
};

DECLARE_CONTAINER_SORT_DEL( Sw3Marks, Sw3Mark )

} //namespace binfilter
#endif
