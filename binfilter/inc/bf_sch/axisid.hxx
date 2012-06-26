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

#ifndef _SCH_AXISID_HXX
#define _SCH_AXISID_HXX

#define SCH_AXIS_ID_X 1
#define SCH_AXIS_ID_Y 2
#define SCH_AXIS_ID_Z 3

#include <bf_svx/svdobj.hxx>

#include <bf_svx/svditer.hxx>
namespace binfilter {

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

    virtual SdrObjUserData* Clone(SdrObject *) const { return NULL; } // DBG_BF_ASSERT

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


} //namespace binfilter
#endif  // _SCH_OBJID_HXX


/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
