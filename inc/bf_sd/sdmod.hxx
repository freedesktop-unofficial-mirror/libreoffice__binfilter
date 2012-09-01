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

#ifndef _SDMOD_HXX
#define _SDMOD_HXX

#include <bf_svtools/bf_solar.h>


#ifndef _SDDLL_HXX
#define _SD_DLL             // fuer SD_MOD()
#include "sddll.hxx"        // fuer SdModuleDummy
#endif
#include "glob.hxx"
#include "pres.hxx"
#include <bf_so3/svstor.hxx>
#include <bf_svtools/lstner.hxx>
#include <com/sun/star/text/WritingMode.hpp>
class SvFactory;
class OutputDevice;

namespace binfilter {

class SfxErrorHandler;
class SvNumberFormatter;
class SdOptions;
class BasicIDE;
class SdAppLinkHdl;
class SvxErrorHandler;
class EditFieldInfo;
class SdDrawDocShell;
class SdView;
class SdPage;
class SdDrawDocument;
// ----------------------
// - SdOptionStreamMode -
// ----------------------

enum SdOptionStreamMode
{
    SD_OPTION_LOAD = 0,
    SD_OPTION_STORE = 1
};

/*************************************************************************
|*
|* This subclass of <SfxModule> (which is a subclass of <SfxShell>) is
|* linked to the DLL. One instance of this class exists while the DLL is
|* loaded.
|*
|* SdModule is like to be compared with the <SfxApplication>-subclass.
|*
|* Remember: Don`t export this class! It uses DLL-internal symbols.
|*
\************************************************************************/

class SdModule : public SdModuleDummy, public SfxListener
{
protected:

    SdOptions*              pImpressOptions;
    SdOptions*              pDrawOptions;
    SvStorageRef            xOptionStorage;
    BOOL                    bAutoSave;
    SfxErrorHandler*        mpErrorHdl;
    OutputDevice*           mpVirtualRefDevice;

    virtual void            Notify( SfxBroadcaster& rBC, const SfxHint& rHint );

public:

                            TYPEINFO();
                            DECL_LINK( CalcFieldValueHdl, EditFieldInfo* );

                            SdModule(SvFactory* pDrawObjFact, SvFactory* pGraphicObjFact);
    virtual                 ~SdModule();

    virtual SfxModule*      Load();
    virtual void            Free();


    SdOptions*              GetSdOptions(DocumentType eDocType);

    OutputDevice* GetVirtualRefDevice (void);

    OutputDevice* GetRefDevice (SdDrawDocShell& rDocShell);
    ::com::sun::star::text::WritingMode GetDefaultWritingMode() const;
};




#ifndef SD_MOD
#define SD_MOD() ( *(SdModule**) GetAppData(BF_SHL_DRAW) )
#endif

} //namespace binfilter
#endif                                 // _SDMOD_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
