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
#ifndef _SVX_FMEXCH_HXX
#define _SVX_FMEXCH_HXX

#include <comphelper/stl_types.hxx>

#include <bf_svtools/transfer.hxx>

class SvTreeListBox;
namespace binfilter {

class FmFormShell;
class FmFormPage;
class SvLBoxEntry;

//========================================================================
// Exchange types
#define SVX_FM_FIELD_EXCH           String("SvxFormFieldExch",              sizeof("SvxFormFieldExch"))
#define SVX_FM_CONTROL_EXCH         String("SvxFormExplCtrlExch",           sizeof("SvxFormExplCtrlExch"))
#define SVX_FM_CONTROLS_AS_PATH     String("SvxFormControlsAsPathExchange", sizeof("SvxFormControlsAsPathExchange"))
#define SVX_FM_HIDDEN_CONTROLS      String("SvxFormHiddenControlsExchange", sizeof("SvxFormHiddenControlsExchange"))
#define SVX_FM_FILTER_FIELDS        String("SvxFilterFieldExchange",        sizeof("SvxFilterFieldExchange"))

//========================================================================

//........................................................................
namespace svxform
{
//........................................................................

    //====================================================================

    DECLARE_STL_VECTOR( SvLBoxEntry*, ListBoxEntryArray );

    //====================================================================
    //= OLocalExchange
    //====================================================================

    //====================================================================
    //= OLocalExchangeHelper
    //====================================================================
    /// a helper for navigator windows (SvTreeListBox'es) which allow DnD within themself
    class OLocalExchangeHelper
    {
    protected:
        Window*             m_pDragSource;

    public:
        OLocalExchangeHelper( Window* _pDragSource );
        ~OLocalExchangeHelper();

        void        prepareDrag( );

        void        startDrag( sal_Int8 nDragSourceActions );
        void        copyToClipboard( ) const;



    protected:

    protected:
        void implReset();
    };

    //====================================================================
    //= OControlTransferData
    //====================================================================

    //====================================================================

    //====================================================================
    //= OControlExchange
    //====================================================================

    //====================================================================
    //= OControlExchangeHelper
    //====================================================================
/*N*/   class OControlExchangeHelper : public OLocalExchangeHelper
/*N*/   {
/*N*/   public:
/*N*/       OControlExchangeHelper(Window* _pDragSource) : OLocalExchangeHelper(_pDragSource) { }
/*N*/
/*N*/
/*N*/   protected:
/*N*/   };

    //====================================================================
    //====================================================================

//........................................................................
}   // namespace svxform
//........................................................................

}//end of namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
