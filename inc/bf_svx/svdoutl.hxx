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

#ifndef _SVDOUTL_HXX
#define _SVDOUTL_HXX

#include <bf_svx/outliner.hxx>
namespace binfilter {

class SdrTextObj;

class SdrOutliner : public Outliner
{
protected:
    const SdrTextObj* pTextObj;

public:
//    TYPEINFO();

    SdrOutliner( SfxItemPool* pItemPool, USHORT nMode );
    virtual ~SdrOutliner() ;

    void  SetTextObj( const SdrTextObj* pObj );
    void SetTextObjNoInit( const SdrTextObj* pObj );

    const SdrTextObj* GetTextObj() const { return pTextObj; }

    virtual String  CalcFieldValue(const SvxFieldItem& rField, USHORT nPara, USHORT nPos, Color*& rpTxtColor, Color*& rpFldColor);
};

}//end of namespace binfilter
#endif //_SVDOUTL_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
