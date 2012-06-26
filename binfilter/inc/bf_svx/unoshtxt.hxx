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

#ifndef SVX_UNOSHTXT_HXX
#define SVX_UNOSHTXT_HXX

#include <bf_svtools/bf_solar.h>

#include <memory>

#include <bf_svx/unoedsrc.hxx>
class Window;
namespace binfilter {

class SvxTextForwarder;
class SdrObject;
class SdrView;
class SvxTextEditSourceImpl;

class SvxTextEditSource : public SvxEditSource, public SvxViewForwarder
{
public:
    SvxTextEditSource( SdrObject* pObj );

    virtual ~SvxTextEditSource();

    virtual SvxEditSource*          Clone() const;
    virtual SvxTextForwarder*       GetTextForwarder();
     virtual SvxViewForwarder*      GetViewForwarder();
     virtual SvxEditViewForwarder*  GetEditViewForwarder( sal_Bool bCreate = sal_False );
    virtual void                    UpdateData();

    virtual SfxBroadcaster&         GetBroadcaster() const;

    void lock();
    void unlock();

    static sal_Bool hasLevels( const SdrObject* pObject );

    // the viewforwarder interface
    virtual BOOL        IsValid() const;
    virtual Rectangle   GetVisArea() const;
    virtual Point       LogicToPixel( const Point&, const MapMode& ) const;
    virtual Point       PixelToLogic( const Point&, const MapMode& ) const;

private:
    SvxTextEditSource( SvxTextEditSourceImpl* pImpl );

    SvxTextEditSourceImpl*  mpImpl;
};

}//end of namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
