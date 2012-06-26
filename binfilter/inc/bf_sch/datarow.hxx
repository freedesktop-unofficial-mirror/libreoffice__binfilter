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

#ifndef _SCH_DATAROW_HXX
#define _SCH_DATAROW_HXX

#include <bf_svx/svdobj.hxx>
#include <tools/stream.hxx>
namespace binfilter {

/*************************************************************************
|*
|* Datenreihen-Index
|*
\************************************************************************/

class SchDataRow : public SdrObjUserData
{
    short nRow;

public:
    SchDataRow();
    SchDataRow(short nR);

    virtual SdrObjUserData* Clone(SdrObject *) const { return NULL; } // DBG_BF_ASSERT

    virtual void ReadData(SvStream& rIn);

    void SetRow(short nR) { nRow = nR; }
    short GetRow() { return nRow; }
};

/*************************************************************************
|*
|* Tool-Funktion fuer Datenreihen-Index
|*
\************************************************************************/

extern SchDataRow* GetDataRow(const SdrObject& rObj);
extern SdrObject* GetObjWithRow(short nRow, const SdrObjList& rObjList,
                                ULONG* pIndex = NULL);

} //namespace binfilter
#endif  // _SCH_DATAROW_HXX


/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
