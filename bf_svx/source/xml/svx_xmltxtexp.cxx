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

/** this file implements an export of a selected EditEngine content into
    a xml stream. See bf_svx/source/inc/xmledit.hxx for interface */

#include <com/sun/star/ucb/XAnyCompareFactory.hpp>
#include <com/sun/star/style/XStyleFamiliesSupplier.hpp>
#include <com/sun/star/io/XActiveDataSource.hpp>











#include <unotools/streamwrap.hxx>


#include "bf_xmloff/xmlexp.hxx"


#include "unofored.hxx"

#include "unotext.hxx"

#include "editsource.hxx"

#include <cppuhelper/implbase4.hxx>

#include "unofield.hxx"

#include "unomod.hxx"
#include "unonrule.hxx"
#include <legacysmgr/legacy_binfilters_smgr.hxx>
namespace binfilter {
using namespace ::com::sun::star;
using namespace ::com::sun::star::container;
using namespace ::com::sun::star::document;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::awt;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::xml::sax;
using namespace cppu;

using rtl::OUString;

///////////////////////////////////////////////////////////////////////

class SvxEditEngineSourceImpl;

///////////////////////////////////////////////////////////////////////

/*N*/ class SvxEditEngineSourceImpl
/*N*/ {
/*N*/ private:
/*N*/   oslInterlockedCount maRefCount;
/*N*/
/*N*/   EditEngine*             mpEditEngine;
/*N*/   SvxTextForwarder*       mpTextForwarder;
/*N*/
/*N*/   ~SvxEditEngineSourceImpl();
/*N*/
/*N*/ public:
/*N*/   void SAL_CALL acquire();
/*N*/   void SAL_CALL release();
/*N*/
/*N*/   SvxTextForwarder*       GetTextForwarder();
/*N*/ };
/*N*/
/*N*/ ///////////////////////////////////////////////////////////////////////
/*N*/
/*N*/ SvxEditEngineSourceImpl::~SvxEditEngineSourceImpl()
/*N*/ {
/*N*/   delete mpTextForwarder;
/*N*/ }
/*N*/
/*N*/ //------------------------------------------------------------------------
/*N*/
/*N*/ void SAL_CALL SvxEditEngineSourceImpl::acquire()
/*N*/ {
/*N*/   osl_incrementInterlockedCount( &maRefCount );
/*N*/ }
/*N*/
/*N*/ //------------------------------------------------------------------------
/*N*/
/*N*/ void SAL_CALL SvxEditEngineSourceImpl::release()
/*N*/ {
/*N*/   if( ! osl_decrementInterlockedCount( &maRefCount ) )
/*N*/       delete this;
/*N*/ }
/*N*/
/*N*/ //------------------------------------------------------------------------
/*N*/
/*N*/ SvxTextForwarder* SvxEditEngineSourceImpl::GetTextForwarder()
/*N*/ {
/*N*/   if (!mpTextForwarder)
/*N*/       mpTextForwarder = new SvxEditEngineForwarder( *mpEditEngine );
/*N*/
/*N*/   return mpTextForwarder;
/*N*/ }
/*N*/
/*N*/ // --------------------------------------------------------------------
/*N*/ // SvxTextEditSource
/*N*/ // --------------------------------------------------------------------
/*N*/
/*N*/ SvxEditEngineSource::SvxEditEngineSource( SvxEditEngineSourceImpl* pImpl )
/*N*/ {
/*N*/   mpImpl = pImpl;
/*N*/   mpImpl->acquire();
/*N*/ }
/*N*/
/*N*/ //------------------------------------------------------------------------
/*N*/
/*N*/ SvxEditEngineSource::~SvxEditEngineSource()
/*N*/ {
/*N*/   mpImpl->release();
/*N*/ }
/*N*/
/*N*/ //------------------------------------------------------------------------
/*N*/
/*N*/ SvxEditSource* SvxEditEngineSource::Clone() const
/*N*/ {
/*N*/   return new SvxEditEngineSource( mpImpl );
/*N*/ }
/*N*/
/*N*/ //------------------------------------------------------------------------
/*N*/
/*N*/ SvxTextForwarder* SvxEditEngineSource::GetTextForwarder()
/*N*/ {
/*N*/     return mpImpl->GetTextForwarder();
/*N*/ }
/*N*/
/*N*/ //------------------------------------------------------------------------
/*N*/
/*N*/ void SvxEditEngineSource::UpdateData()
/*N*/ {
/*N*/ }
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
