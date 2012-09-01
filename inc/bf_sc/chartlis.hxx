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

#ifndef SC_CHARTLIS_HXX
#define SC_CHARTLIS_HXX

#include <bf_svtools/bf_solar.h>


#include <vcl/timer.hxx>

#include <bf_svtools/lstner.hxx>
#include "collect.hxx"
#include "rangelst.hxx"


#include <com/sun/star/chart/XChartData.hpp>
namespace binfilter {
class ScDocument;
class ScChartUnoData;

class ScChartListener : public StrData, public SfxListener
{
private:
    ScRangeListRef  aRangeListRef;
    ScChartUnoData* pUnoData;
    ScDocument*     pDoc;
    BOOL            bUsed;  // fuer ScChartListenerCollection::FreeUnused
    BOOL            bDirty;
    BOOL            bSeriesRangesScheduled;

                    // not implemented
    ScChartListener& operator=( const ScChartListener& );

public:
                    ScChartListener( const String& rName, ScDocument* pDoc,
                                    const ScRange& rRange );
                    ScChartListener( const String& rName, ScDocument* pDoc,
                                    const ScRangeListRef& rRangeListRef );
                    ScChartListener( const ScChartListener& );
    virtual         ~ScChartListener();
    virtual DataObject* Clone() const { return NULL; } // DBG_BF_ASSERT

    void            SetUno( const ::com::sun::star::uno::Reference< ::com::sun::star::chart::XChartDataChangeEventListener >& rListener,
                            const ::com::sun::star::uno::Reference< ::com::sun::star::chart::XChartData >& rSource );
    ::com::sun::star::uno::Reference< ::com::sun::star::chart::XChartDataChangeEventListener >  GetUnoListener() const;
    ::com::sun::star::uno::Reference< ::com::sun::star::chart::XChartData >                     GetUnoSource() const;

    BOOL            IsUno() const   { return (pUnoData != NULL); }

    virtual void    Notify( SfxBroadcaster& rBC, const SfxHint& rHint );
    void            StartListeningTo();
    void            EndListeningTo();
    void            Update();
    const ScRangeListRef&   GetRangeList() const { return aRangeListRef; }
    void            SetRangeList( const ScRangeListRef& rNew ) { aRangeListRef = rNew; }
    void            SetRangeList( const ScRange& rNew );
    BOOL            IsUsed() const { return bUsed; }
    void            SetUsed( BOOL bFlg ) { bUsed = bFlg; }
    BOOL            IsDirty() const { return bDirty; }
    void            SetDirty( BOOL bFlg ) { bDirty = bFlg; }

    // if chart series ranges are to be updated later on (e.g. DeleteTab, InsertTab)
    void            ScheduleSeriesRanges()      { bSeriesRangesScheduled = TRUE; }

};

class ScChartListenerCollection : public StrCollection
{
private:
    Timer           aTimer;
    ScDocument*     pDoc;

                    DECL_LINK( TimerHdl, Timer* );

                    // not implemented
    ScChartListenerCollection& operator=( const ScChartListenerCollection& );

public:
                    ScChartListenerCollection( ScDocument* pDoc );
                    ScChartListenerCollection( const ScChartListenerCollection& );
    virtual DataObject* Clone() const { return NULL; } // DBG_BF_ASSERT

    virtual         ~ScChartListenerCollection();

    // FreeUnused nur wie in ScDocument::UpdateChartListenerCollection verwenden!
    void            FreeUnused();
    void            FreeUno( const ::com::sun::star::uno::Reference< ::com::sun::star::chart::XChartDataChangeEventListener >& rListener,
                             const ::com::sun::star::uno::Reference< ::com::sun::star::chart::XChartData >& rSource );
    void            StartTimer();
    void            UpdateDirtyCharts();
    void            SetDirty();
};


} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
