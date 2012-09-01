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

#ifndef SC_DBDOCFUN_HXX
#define SC_DBDOCFUN_HXX

#include <bf_svtools/bf_solar.h>

#include <com/sun/star/uno/Sequence.hxx>

class String;
namespace binfilter {

struct ScImportParam;
struct ScQueryParam;
struct ScSortParam;
struct ScSubTotalParam;

class SfxViewFrame;
class SbaSelectionList;
class ScDBData;
class ScDocShell;
class ScAddress;
class ScRange;
class ScDPObject;
} //namespace binfilter
namespace com { namespace sun { namespace star {
    namespace beans {
        struct PropertyValue;
    }
    namespace sdbc {
        class XResultSet;
    }
} } }
namespace binfilter {
// ---------------------------------------------------------------------------

class ScDBDocFunc
{
friend class ScDBFunc;

private:
    ScDocShell&     rDocShell;

public:
                    ScDBDocFunc( ScDocShell& rDocSh ): rDocShell(rDocSh) {}
                    ~ScDBDocFunc() {}

    BOOL            DoImport( USHORT nTab, const ScImportParam& rParam,
                        const ::com::sun::star::uno::Reference<
                        ::com::sun::star::sdbc::XResultSet >& xResultSet,
                        const SbaSelectionList* pSelection, BOOL bRecord,
                        BOOL bAddrInsert = FALSE );

    BOOL            AddDBRange( const String& rName, const ScRange& rRange );
    BOOL            DeleteDBRange( const String& rName );
    BOOL            RenameDBRange( const String& rOld, const String& rNew );
    BOOL            ModifyDBData( const ScDBData& rNewData );    // Name unveraendert

    BOOL            RepeatDB( const String& rDBName, BOOL bRecord );

    BOOL            DataPilotUpdate( ScDPObject* pOldObj, const ScDPObject* pNewObj,
                                        BOOL bRecord, BOOL bApi );
};



} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
