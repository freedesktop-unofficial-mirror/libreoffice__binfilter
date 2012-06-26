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
#ifndef _USRPREF_HXX
#define _USRPREF_HXX

#include <bf_svtools/bf_solar.h>



#include <unotools/configitem.hxx>
#include <fldupde.hxx>
#include "viewopt.hxx"

#include <tools/fldunit.hxx>
namespace binfilter {



class SwMasterUsrPref;
class SwContentViewConfig : public ::utl::ConfigItem
{
    SwMasterUsrPref&        rParent;
    BOOL                    bWeb;

    ::com::sun::star::uno::Sequence<rtl::OUString> GetPropertyNames();
    public:
        SwContentViewConfig(BOOL bWeb, SwMasterUsrPref& rParent);
        ~SwContentViewConfig();

    void                    Load();
    void                    SetModified(){ConfigItem::SetModified();}
    virtual void Commit();
    virtual void Notify( const ::com::sun::star::uno::Sequence< rtl::OUString >& aPropertyNames );
};


class SwLayoutViewConfig : public ::utl::ConfigItem
{
    SwMasterUsrPref&    rParent;
    BOOL                bWeb;

    ::com::sun::star::uno::Sequence<rtl::OUString> GetPropertyNames();
    public:
        SwLayoutViewConfig(BOOL bWeb, SwMasterUsrPref& rParent);
        ~SwLayoutViewConfig();

    void                    Load();
    void                    SetModified(){ConfigItem::SetModified();}
    virtual void Commit();
    virtual void Notify( const ::com::sun::star::uno::Sequence< rtl::OUString >& aPropertyNames );
};


class SwGridConfig : public ::utl::ConfigItem
{
    SwMasterUsrPref&    rParent;
    BOOL                bWeb;

    ::com::sun::star::uno::Sequence<rtl::OUString> GetPropertyNames();
    public:
        SwGridConfig(BOOL bWeb, SwMasterUsrPref& rParent);
        ~SwGridConfig();

    void                    Load();
    void                    SetModified(){ConfigItem::SetModified();}
    virtual void Commit();
    virtual void Notify( const ::com::sun::star::uno::Sequence< rtl::OUString >& aPropertyNames );
};


class SwCursorConfig : public ::utl::ConfigItem
{
    SwMasterUsrPref&    rParent;

    ::com::sun::star::uno::Sequence<rtl::OUString> GetPropertyNames();
    public:
        SwCursorConfig(SwMasterUsrPref& rParent);
        ~SwCursorConfig();

    void                    Load();
    void                    SetModified(){ConfigItem::SetModified();}
    virtual void Commit();
    virtual void Notify( const ::com::sun::star::uno::Sequence< rtl::OUString >& aPropertyNames );
};


class SwWebColorConfig : public ::utl::ConfigItem
{
    SwMasterUsrPref&        rParent;
    ::com::sun::star::uno::Sequence<rtl::OUString> aPropNames;

    public:
        SwWebColorConfig(SwMasterUsrPref& rParent);
        ~SwWebColorConfig();

    void                    Load();
    void                    SetModified(){ConfigItem::SetModified();}
    virtual void Commit();
    virtual void Notify( const ::com::sun::star::uno::Sequence< rtl::OUString >& aPropertyNames );
};


class SwMasterUsrPref : public SwViewOption
{
    friend class SwContentViewConfig;
    friend class SwLayoutViewConfig;
    friend class SwGridConfig;
    friend class SwCursorConfig;
    friend class SwWebColorConfig;

    SwContentViewConfig aContentConfig;
    SwLayoutViewConfig  aLayoutConfig;
    SwGridConfig        aGridConfig;
    SwCursorConfig      aCursorConfig;
    SwWebColorConfig*   pWebColorConfig;

    sal_Int32   nFldUpdateFlags;    //udpate of fields and charts
    sal_Int32   nLinkUpdateMode;
    FieldUnit   eUserMetric;
    FieldUnit   eHScrollMetric;
    sal_Bool    bIsHScrollMetricSet;
    FieldUnit   eVScrollMetric;
    sal_Bool    bIsVScrollMetricSet;


    sal_Int32   nDefTab;            //default tab stop distance

public:
    SwMasterUsrPref(BOOL bWeb);
    ~SwMasterUsrPref();


    void SetModified()
        {
            aContentConfig.SetModified();
            aLayoutConfig.SetModified();
            aGridConfig.SetModified();
            aCursorConfig.SetModified();
            if(pWebColorConfig)
                pWebColorConfig->SetModified();
        }

    void SetUpdateLinkMode(sal_Int32 nSet, sal_Bool bNoModify = sal_False)
        {
            nLinkUpdateMode = nSet;
            if(!bNoModify)
                aContentConfig.SetModified();
        }
    sal_Int32 GetUpdateLinkMode() const {return nLinkUpdateMode; }

    void SetUpdateFields(BOOL bSet, sal_Bool bNoModify = sal_False)
        {
            if(bSet && nFldUpdateFlags == AUTOUPD_OFF)
            {
                nFldUpdateFlags = AUTOUPD_FIELD_ONLY;
                if(!bNoModify)
                    aContentConfig.SetModified();
             }
            else if(!bSet)
            {
                nFldUpdateFlags = AUTOUPD_OFF;
                if(!bNoModify)
                    aContentConfig.SetModified();
            }
        };
    sal_Bool IsUpdateFields()const {return nFldUpdateFlags != AUTOUPD_OFF; }

    sal_Int32   GetFldUpdateFlags()const {return nFldUpdateFlags;}
    void        SetFldUpdateFlags(sal_Int32 nSet, sal_Bool bNoModify = sal_False)
        {
            nFldUpdateFlags = nSet;
            if(!bNoModify)
                aContentConfig.SetModified();
        }

    void SetUpdateCharts(BOOL bSet, sal_Bool bNoModify = sal_False)
        {
            if(bSet)
            {
                nFldUpdateFlags = AUTOUPD_FIELD_AND_CHARTS;
                if(!bNoModify)
                    aContentConfig.SetModified();
             }
             else if(nFldUpdateFlags == AUTOUPD_FIELD_AND_CHARTS)
             {
                nFldUpdateFlags = AUTOUPD_FIELD_ONLY;
                if(!bNoModify)
                    aContentConfig.SetModified();
             }
        };
    sal_Bool IsUpdateCharts()const {return nFldUpdateFlags == AUTOUPD_FIELD_AND_CHARTS; }

    FieldUnit   GetMetric() const { return eUserMetric;}
    void        SetMetric(FieldUnit eSet, sal_Bool bNoModify = sal_False)
                {
                    eUserMetric = eSet;
                    if(!bNoModify)
                        aLayoutConfig.SetModified();
                }

    sal_Bool    IsHScrollMetric()const {return bIsHScrollMetricSet;}
    FieldUnit   GetHScrollMetric() const { return bIsHScrollMetricSet ? eHScrollMetric : eUserMetric;}
    void        SetHScrollMetric(FieldUnit eSet, sal_Bool bNoModify = sal_False)
                {
                    eHScrollMetric = eSet; bIsHScrollMetricSet = sal_True;
                    if(!bNoModify)
                        aLayoutConfig.SetModified();
                }

    sal_Bool    IsVScrollMetric()const {return bIsVScrollMetricSet;}
    FieldUnit   GetVScrollMetric() const { return bIsVScrollMetricSet ? eVScrollMetric : eUserMetric;}
    void        SetVScrollMetric(FieldUnit eSet, sal_Bool bNoModify = sal_False)
                {
                    eVScrollMetric = eSet; bIsVScrollMetricSet = sal_True;
                    if(!bNoModify)
                        aLayoutConfig.SetModified();
                }

    sal_Int32   GetDefTab() const { return nDefTab;}
    void        SetDefTab( sal_Int32  nSet, sal_Bool bNoModify = sal_False )
                {
                    nDefTab = nSet;
                    if(!bNoModify)
                        aLayoutConfig.SetModified();
                }

};

} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
