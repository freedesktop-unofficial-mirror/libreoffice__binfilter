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
#ifndef _SVX_FMSHIMP_HXX
#define _SVX_FMSHIMP_HXX


#include <com/sun/star/container/XContainerListener.hpp>
#include <com/sun/star/util/XModifyListener.hpp>
#include <com/sun/star/form/XForm.hpp>
#include <com/sun/star/form/XFormController.hpp>
#include <com/sun/star/form/NavigationBarMode.hpp>
#include <com/sun/star/view/XSelectionChangeListener.hpp>



#include "svdmark.hxx"

#include "svxids.hrc"


#define _SVSTDARR_BOOLS
#define _SVSTDARR_BYTES
#define _SVSTDARR_LONGS
#define _SVSTDARR_ULONGS
#define _SVSTDARR_USHORTS

#include "fmsearch.hxx"
#include <cppuhelper/compbase6.hxx>
#include <unotools/configitem.hxx>

#include <queue>
namespace binfilter {

SV_DECL_PTRARR(SdrObjArray, SdrObject*, 32, 16)
DECLARE_STL_VECTOR( ::com::sun::star::uno::Reference< ::com::sun::star::form::XForm > ,FmFormArray);

// catch databse exceptions if occur
#define DO_SAFE(statement) try { statement; } catch( const Exception& ) { OSL_FAIL("unhandled exception (I tried to move a cursor (or something like that).)"); }

#define GA_DISABLE_SYNC     1
#define GA_FORCE_SYNC       2
#define GA_ENABLE_SYNC      3
#define GA_SYNC_MASK        3
#define GA_DISABLE_ROCTRLR  4
#define GA_ENABLE_ROCTRLR   8


// flags for controlling the behaviour when calling loadForms
#define FORMS_LOAD          0x0000      // default: simply load
#define FORMS_SYNC          0x0000      // default: do in synchronous

#define FORMS_UNLOAD        0x0001      // unload
#define FORMS_RESET         0x0002      // reset after the load/unload
#define FORMS_ASYNC         0x0004      // do this async

// forward declarations
class FmFormShell;


//==============================================================================
// a class iterating through all fields of a form which are bound to a field
// sub forms are ignored, grid columns (where the grid is a direct child of the form) are included

//========================================================================
// I would prefer this to be a struct local to FmXFormShell but unfortunately local structs/classes
// are somewhat difficult with some of our compilers
class FmCursorActionThread;
struct CursorActionDescription
{
    FmCursorActionThread*   pThread;
    sal_uInt32                  nFinishedEvent;
        // we want to do the cleanup of the thread in the main thread so we post an event to ourself
    sal_Bool                    bCanceling;
        // this thread is being canceled

    CursorActionDescription() : pThread(NULL), nFinishedEvent(0), bCanceling(sal_False) { }
};

class FmFormPage;
//========================================================================
struct FmLoadAction
{
    FmFormPage* pPage;
    sal_uInt32  nEventId;
    sal_uInt16  nFlags;

    FmLoadAction( ) : pPage( NULL ), nEventId( 0 ), nFlags( 0 ) { }
    FmLoadAction( FmFormPage* _pPage, sal_uInt16 _nFlags, sal_uInt32 _nEventId )
        :pPage( _pPage ), nEventId( _nEventId ), nFlags( _nFlags )
    {
    }
};

//========================================================================
class SfxViewFrame;
typedef ::cppu::WeakComponentImplHelper6<   ::com::sun::star::sdbc::XRowSetListener,
                                            ::com::sun::star::beans::XPropertyChangeListener,
                                            ::com::sun::star::util::XModifyListener,
                                            ::com::sun::star::container::XContainerListener,
                                            ::com::sun::star::view::XSelectionChangeListener,
                                            ::com::sun::star::form::XFormControllerListener> FmXFormShell_BD_BASE;

//========================================================================
class FmXFormShell_Base_Disambiguation : public FmXFormShell_BD_BASE
{
    using ::com::sun::star::beans::XPropertyChangeListener::disposing;
protected:
    FmXFormShell_Base_Disambiguation( ::osl::Mutex& _rMutex );
    virtual void SAL_CALL disposing();
};

//========================================================================
typedef FmXFormShell_Base_Disambiguation    FmXFormShell_BASE;
typedef ::utl::ConfigItem                   FmXFormShell_CFGBASE;


}//end of namespace binfilter
#endif          // _SVX_FMSHIMP_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
