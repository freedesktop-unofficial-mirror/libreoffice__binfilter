/*************************************************************************
 *
 *  $RCSfile: axisid.hxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:23:25 $
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

#ifndef _SCH_AXISID_HXX
#define _SCH_AXISID_HXX

#define SCH_AXIS_ID_X 1
#define SCH_AXIS_ID_Y 2
#define SCH_AXIS_ID_Z 3

#ifndef _SVDOBJ_HXX //autogen
#include <bf_svx/svdobj.hxx>
#endif

#ifndef _SVDITER_HXX //autogen
#include <bf_svx/svditer.hxx>
#endif

/*************************************************************************
|*
|* Id-Objekt fuer Chart-Grafik-Objekte
|*
\************************************************************************/

class SchAxisId : public SdrObjUserData
{
    long nAxisId;

public:
    SchAxisId ();
    SchAxisId (long nId);
//STRIP001  SchAxisId (const SchAxisId &rAxisId);

    virtual SdrObjUserData* Clone(SdrObject *pObj) const;

    virtual void WriteData(SvStream& rOut);
    virtual void ReadData(SvStream& rIn);

    long &AxisId ()
    {
        return nAxisId;
    }

    long AxisId () const
    {
        return nAxisId;
    }
};

/*************************************************************************
|*
|* Tool-Funktionen fuer Objekt-Ids
|*
\************************************************************************/

//STRIP001 SchAxisId *GetAxisId (const SdrObject& rObj);
//STRIP001 SdrObject *GetObjWithAxisId (long             nObjId,
//STRIP001                           const SdrObjList &rObjList,
//STRIP001                           long             *pIndex,
//STRIP001                           SdrIterMode      eMode);

#endif  // _SCH_OBJID_HXX


