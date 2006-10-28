/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: objid.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 02:49:17 $
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

#ifndef _SCH_OBJID_HXX
#define _SCH_OBJID_HXX

#ifndef _SVDOBJ_HXX //autogen
#include <bf_svx/svdobj.hxx>
#endif
#ifndef _STREAM_HXX //autogen
#include <tools/stream.hxx>
#endif
#ifndef _SVDITER_HXX //autogen
#include <bf_svx/svditer.hxx>
#endif
namespace binfilter {


/*************************************************************************
|*
|* Id-Objekt fuer Chart-Grafik-Objekte
|*
\************************************************************************/

class SchObjectId : public SdrObjUserData
{
    UINT16 nObjId;  // Id-Wert

public:
    SchObjectId();
    SchObjectId(UINT16 nId);

        virtual SdrObjUserData* Clone(SdrObject *pObj) const;

    virtual void WriteData(SvStream& rOut);
    virtual void ReadData(SvStream& rIn);

        void SetObjId(UINT16 nId) {  nObjId = nId; }
    UINT16 GetObjId() { return nObjId; }
};

/*************************************************************************
|*
|* Tool-Funktionen fuer Objekt-Ids
|*
\************************************************************************/

extern SchObjectId* GetObjectId(const SdrObject& rObj);

extern SdrObject* GetObjWithId(UINT16 nObjId, const SdrObjList& rObjList,
                                                           ULONG* pIndex = NULL,
                                                           SdrIterMode eMode = IM_FLAT);

//Die hier folgenden Funktionen dienen AUSSCHLIESSLICH zu DEBUG-Zwecken
#ifdef DBG_UTIL
extern char *GetCHOBJIDName(const long id);
#endif

} //namespace binfilter
#endif  // _SCH_OBJID_HXX


