/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file incorporates work covered by the following license notice:
 *
 *   Licensed to the Apache Software Foundation (ASF) under one or more
 *   contributor license agreements. See the NOTICE file distributed
 *   with this work for additional information regarding copyright
 *   ownership. The ASF licenses this file to you under the Apache
 *   License, Version 2.0 (the "License"); you may not use this file
 *   except in compliance with the License. You may obtain a copy of
 *   the License at http://www.apache.org/licenses/LICENSE-2.0 .
 */

#ifndef _SCH_DATAPOIN_HXX
#define _SCH_DATAPOIN_HXX

#include <bf_svx/svdobj.hxx>
#include <tools/stream.hxx>
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

    virtual SdrObjUserData* Clone(SdrObject *) const { return NULL; } // DBG_BF_ASSERT

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


/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
