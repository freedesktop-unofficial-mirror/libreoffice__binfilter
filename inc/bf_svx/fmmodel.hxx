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

#ifndef _SVX_FMMODEL_HXX
#define _SVX_FMMODEL_HXX

#include <bf_svtools/bf_solar.h>

#include <bf_svx/svdmodel.hxx>
class SbxObject;
class SbxArray;
class SbxValue;
namespace binfilter {

class SvPersist;

class SfxItemPool;
class VCItemPool;
class FmXUndoEnvironment;
class SfxObjectShell;


struct FmFormModelImplData;
class FmFormModel :
    public SdrModel
{
private:
    FmFormModelImplData*    m_pImpl;
    SfxObjectShell*         pObjShell;
    sal_Bool            bStreamingOldVersion;

    sal_Bool            m_bOpenInDesignMode : 1;
    sal_Bool            m_bAutoControlFocus : 1;


public:
    TYPEINFO();

    FmFormModel(const XubString& rPath, SfxItemPool* pPool=NULL,
                SvPersist* pPers=NULL );
    FmFormModel(const XubString& rPath, SfxItemPool* pPool, SvPersist* pPers,
                bool bUseExtColorTable);

    virtual ~FmFormModel();

    virtual void     InsertPage(SdrPage* pPage, sal_uInt16 nPos=0xFFFF);
    virtual SdrPage* RemovePage(sal_uInt16 nPgNum);
    virtual void     MovePage(USHORT nPgNum, USHORT nNewPos);
    virtual void     InsertMasterPage(SdrPage* pPage, sal_uInt16 nPos=0xFFFF);
    virtual SdrPage* RemoveMasterPage(sal_uInt16 nPgNum);

    virtual void ReadData(const SdrIOHeader& rHead, SvStream& rIn);

    virtual SdrLayerID      GetControlExportLayerId( const SdrObject& rObj ) const;
    SfxObjectShell*         GetObjectShell() const { return pObjShell; }
    void                    SetObjectShell( SfxObjectShell* pShell );

    sal_Bool GetOpenInDesignMode() const { return m_bOpenInDesignMode; }
    void SetOpenInDesignMode( sal_Bool _bOpenDesignMode );

    sal_Bool    GetAutoControlFocus() const { return m_bAutoControlFocus; }
    void        SetAutoControlFocus( sal_Bool _bAutoControlFocus );

    /** check whether the OpenInDesignMode has been set explicitly or been loaded (<FALSE/>)
        or if it still has the default value from construction (<TRUE/>)
    */
    sal_Bool    OpenInDesignModeIsDefaulted( );

#if _SOLAR__PRIVATE
    void        implSetOpenInDesignMode( sal_Bool _bOpenDesignMode, sal_Bool _bForce );

    sal_Bool IsStreamingOldVersion() const { return bStreamingOldVersion; }
    FmXUndoEnvironment& GetUndoEnv();

    XubString GetUniquePageId();
#endif

};

}//end of namespace binfilter
#endif          // _FM_FMMODEL_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
