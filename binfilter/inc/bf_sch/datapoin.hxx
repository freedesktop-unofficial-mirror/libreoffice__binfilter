/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: datapoin.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 02:47:36 $
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

#ifndef _SCH_DATAPOIN_HXX
#define _SCH_DATAPOIN_HXX

#ifndef _SVDOBJ_HXX //autogen
#include <bf_svx/svdobj.hxx>
#endif
#ifndef _STREAM_HXX //autogen
#include <tools/stream.hxx>
#endif
namespace binfilter {

/*************************************************************************
|*
|* Datenpunkt
|*
\************************************************************************/

class SchDataPoint : public SdrObjUserData
{
    short nCol;
    short nRow;

public:
    SchDataPoint();
    SchDataPoint(short nC, short nR);

        virtual SdrObjUserData* Clone(SdrObject *pObj) const;

    virtual void WriteData(SvStream& rOut);
    virtual void ReadData(SvStream& rIn);

    void SetCol(short nC) { nCol = nC; }
    void SetRow(short nR) { nRow = nR; }
    short GetCol() { return nCol; }
    short GetRow() { return nRow; }
};

/*************************************************************************
|*
|* Tool-Funktion fuer Datenpunkt
|*
\************************************************************************/

extern SchDataPoint* GetDataPoint(const SdrObject& rObj);
extern SdrObject* GetObjWithColRow(short nCol, short nRow,
                                   const SdrObjList& rObjList,
                                   ULONG* pIndex = NULL);

} //namespace binfilter
#endif  // _SCH_DATAPOIN_HXX


