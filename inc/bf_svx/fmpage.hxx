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

#ifndef _SVX_FMPAGE_HXX
#define _SVX_FMPAGE_HXX

#include <bf_svtools/bf_solar.h>

#include <bf_svx/svdpage.hxx>

namespace com { namespace sun { namespace star {
    namespace container {
        class XNameContainer;
    }
}}}

namespace binfilter {

class StarBASIC;
class FmFormModel;
class FmFormPageImpl;   // haelt die Liste aller Forms

class SfxJSArray;
class HelpEvent;

class FmFormPage : public SdrPage
{
    friend class FmFormObj;
    FmFormPageImpl* pImpl;

public:
    TYPEINFO();

    FmFormPage(FmFormModel& rModel,StarBASIC*, bool bMasterPage=sal_False);
    ~FmFormPage();

    using SdrPage::NbcInsertObject;
    using SdrPage::ReplaceObject;

    virtual void    ReadData(const SdrIOHeader& rHead, SvStream& rIn);
    virtual void    SetModel(SdrModel* pNewModel);

    virtual SdrPage* Clone() const;

    virtual void    InsertObject(SdrObject* pObj, ULONG nPos = CONTAINER_APPEND,
                                    const SdrInsertReason* pReason=NULL);

    virtual SdrObject* RemoveObject(ULONG nObjNum);

    // Zugriff auf alle Formulare
    const ::com::sun::star::uno::Reference< ::com::sun::star::container::XNameContainer>& GetForms() const;

    FmFormPageImpl*  GetImpl() const {return pImpl;}

public:
    String              aPageName;
    StarBASIC*          pBasic;

    const String&       GetName() const { return aPageName; }
    void                SetName( const String& rName ) { aPageName = rName; }
    StarBASIC*          GetBasic() const { return pBasic; }
};

}//end of namespace binfilter
#endif          // _SVX_FMPAGE_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
