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
#ifndef _INSDLG_HXX
#define _INSDLG_HXX

#include <tools/globname.hxx>
#include <bf_svtools/ownlist.hxx>
#include <bf_so3/so2ref.hxx>

#include "bf_so3/so3dllapi.h"

class SvAppletObject;

#ifndef SV_DECL_SVBASELINK2_DEFINED
#define SV_DECL_SVBASELINK2_DEFINED
SV_DECL_REF(SvBaseLink2)
#endif

namespace binfilter
{
#ifndef SO2_DECL_SVINPLACEOBJECT_DEFINED
#define SO2_DECL_SVINPLACEOBJECT_DEFINED
SO2_DECL_REF(SvInPlaceObject)
#endif

/********************** SvObjectServer ***********************************
*************************************************************************/
class SO3_DLLPUBLIC SvObjectServer
{
private:
    SvGlobalName    aClassName;
    String          aHumanName;

public:
    SvObjectServer( const SvGlobalName & rClassP, const String & rHumanP ) :
        aClassName( rClassP ),
        aHumanName( rHumanP ) {}

    const SvGlobalName &    GetClassName() const { return aClassName; }
    const String &          GetHumanName() const { return aHumanName; }
};

class SO3_DLLPRIVATE SvObjectServerList
{
    PRV_SV_DECL_OWNER_LIST(SvObjectServerList,SvObjectServer)
    SO3_DLLPRIVATE const SvObjectServer *  Get( const SvGlobalName & ) const;
    SO3_DLLPRIVATE void                    Remove( const SvGlobalName & );

    SO3_DLLPRIVATE void                 FillInsertObjects();
};

}   // namespace so3

#endif // _INSDLG_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
