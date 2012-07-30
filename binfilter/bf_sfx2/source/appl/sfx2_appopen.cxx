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

#include <com/sun/star/uno/Reference.h>
#include <com/sun/star/beans/PropertyValue.hpp>
#include <com/sun/star/frame/FrameSearchFlag.hpp>
#include <com/sun/star/frame/XComponentLoader.hpp>
#include <com/sun/star/frame/XNotifyingDispatch.hpp>
#include <com/sun/star/frame/XDispatchProvider.hpp>
#include <com/sun/star/frame/XFrame.hpp>
#include <com/sun/star/frame/DispatchResultState.hpp>
#include <com/sun/star/frame/XDispatchResultListener.hpp>
#include <com/sun/star/util/URL.hpp>
#include <com/sun/star/util/XURLTransformer.hpp>
#include <com/sun/star/document/XTypeDetection.hpp>
#include <com/sun/star/document/MacroExecMode.hpp>
#include <com/sun/star/document/UpdateDocMode.hpp>
#include <com/sun/star/task/XInteractionRequest.hpp>

#include <comphelper/processfactory.hxx>
#include <cppuhelper/implbase1.hxx>

#include <bf_svtools/intitem.hxx>
#include <bf_svtools/stritem.hxx>
#include <bf_svtools/eitem.hxx>
#include <bf_so3/svstor.hxx>
#include <doctempl.hxx>
#include <bf_svtools/sfxecode.hxx>

#include <bf_svtools/ehdl.hxx>
#include "bf_basic/sbxobj.hxx"
#include <bf_svtools/urihelper.hxx>
#include <unotools/localfilehelper.hxx>

#include <bf_svtools/itemset.hxx>

#include <bf_svtools/pathoptions.hxx>
#include <bf_svtools/moduleoptions.hxx>
#include <bf_svtools/templdlg.hxx>
#include <osl/file.hxx>
#include <bf_svtools/extendedsecurityoptions.hxx>
#include <bf_svtools/docpasswdrequest.hxx>

#ifdef _MSC_VER
#pragma hdrstop
#endif

#include "app.hxx"
#include "appdata.hxx"
#include "cfgmgr.hxx"
#include "docfile.hxx"
#include "fcontnr.hxx"
#include "objitem.hxx"
#include "objsh.hxx"
#include "objshimp.hxx"
#include "openflag.hxx"
#include "request.hxx"
#include "appimp.hxx"
#include "appuno.hxx"
#include "docfac.hxx"
#include "sfxsids.hrc"

#define _SVSTDARR_STRINGSDTOR
#include <bf_svtools/svstdarr.hxx>

#include <legacysmgr/legacy_binfilters_smgr.hxx>
namespace binfilter {

using namespace ::com::sun::star::beans;
using namespace ::com::sun::star::frame;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::util;
using namespace ::com::sun::star::task;
using namespace ::cppu;

//--------------------------------------------------------------------

/*N*/ sal_uInt32 CheckPasswd_Impl
/*N*/ (
/*N*/     SfxObjectShell* /*pDoc*/,
/*N*/   SfxItemPool & /*rPool*/,    // Pool, falls ein Set erzeugt werden mus
/*N*/   SfxMedium *pFile    // das Medium, dessen Passwort gfs. erfragt werden soll
/*N*/ )

/*  [Beschreibung]

    Zu einem Medium das Passwort erfragen; funktioniert nur, wenn es sich
    um einen Storage handelt.
    Wenn in der Documentinfo das Passwort-Flag gesetzt ist, wird
    das Passwort vom Benutzer per Dialog erfragt und an dem Set
    des Mediums gesetzt; das Set wird, wenn nicht vorhanden, erzeugt.

*/

/*N*/ {
/*N*/     ULONG nRet=0;
/*N*/     if( ( !pFile->GetFilter() || pFile->GetFilter()->UsesStorage() ) )
/*N*/     {
/*N*/         SvStorageRef aRef = pFile->GetStorage();
/*N*/         if(aRef.Is())
/*N*/         {
/*N*/             sal_Bool bIsEncrypted = sal_False;
/*N*/             ::com::sun::star::uno::Any aAny;
/*N*/             if ( aRef->GetProperty( ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "HasEncryptedEntries" )), aAny ) )
/*N*/                 aAny >>= bIsEncrypted;
/*N*/             else
/*N*/             {
/*N*/                 SfxDocumentInfo aInfo;
/*N*/                 bIsEncrypted = ( aInfo.Load(aRef) && aInfo.IsPasswd() );
/*N*/             }
/*N*/
/*N*/             if ( bIsEncrypted )
/*N*/             {
                nRet = ERRCODE_SFX_CANTGETPASSWD;
                SfxItemSet *pSet = pFile->GetItemSet();
                if( pSet )
                {
                    Reference< ::com::sun::star::task::XInteractionHandler > xInteractionHandler;

                    SFX_ITEMSET_ARG( pSet, pxInteractionItem, SfxUnoAnyItem, SID_INTERACTIONHANDLER, sal_False );
                    if( pxInteractionItem && ( pxInteractionItem->GetValue() >>= xInteractionHandler )
                     && xInteractionHandler.is() )
                    {
                        RequestDocumentPassword* pPasswordRequest = new RequestDocumentPassword(
                            ::com::sun::star::task::PasswordRequestMode_PASSWORD_ENTER,
                            INetURLObject( pFile->GetOrigURL() ).GetName( INetURLObject::DECODE_WITH_CHARSET ) );

                        Reference< XInteractionRequest > rRequest( pPasswordRequest );
                        xInteractionHandler->handle( rRequest );

                        if ( pPasswordRequest->isPassword() )
                        {
                            pSet->Put( SfxStringItem( SID_PASSWORD, pPasswordRequest->getPassword() ) );
                            nRet = ERRCODE_NONE;
                        }
                        else
                            nRet = ERRCODE_IO_ABORT;
                    }
                }
/*?*/             }
/*N*/         }
/*N*/     }
/*N*/     return nRet;
/*N*/ }


}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
