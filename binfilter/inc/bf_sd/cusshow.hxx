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

#ifndef _SD_CUSSHOW_HXX
#define _SD_CUSSHOW_HXX


#include <tools/list.hxx>
#include <tools/stream.hxx>

#include <cppuhelper/weakref.hxx>
namespace binfilter {

class SdDrawDocument;

/*************************************************************************
|*
|* CustomShow
|*
\************************************************************************/
class SdCustomShow : public List
{
private:
    String          aName;
    SdDrawDocument* pDoc;

    // this is a weak reference to a possible living api wrapper for this custom show
    ::com::sun::star::uno::WeakReference< ::com::sun::star::uno::XInterface > mxUnoCustomShow;

public:
    SdCustomShow(SdDrawDocument* pDrawDoc);
    SdCustomShow(SdDrawDocument* pDrawDoc, ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface > xShow );

    SdCustomShow( const SdCustomShow& rShow );
    virtual ~SdCustomShow();

    void   SetName(const String& rName) { aName = rName; }
    String GetName() const              { return aName; }

    SdDrawDocument* GetDoc() const { return pDoc; }

    friend SvStream& operator << (SvStream& rOut, const SdCustomShow& rCustomShow);
    friend SvStream& operator >> (SvStream& rIn, SdCustomShow& rCustomShow);

    ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface > getUnoCustomShow();
};

} //namespace binfilter
#endif      // _SD_CUSSHOW_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
