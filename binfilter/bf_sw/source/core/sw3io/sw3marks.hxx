/*************************************************************************
 *
 *  $RCSfile: sw3marks.hxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: aw $ $Date: 2003-10-02 15:30:42 $
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
#ifndef _SW3MARKS_HXX
#define _SW3MARKS_HXX

#ifndef _SOLAR_H
#include <tools/solar.h>
#endif
#ifndef _CNTNRSRT_HXX
#include <svtools/cntnrsrt.hxx>
#endif

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

#endif
