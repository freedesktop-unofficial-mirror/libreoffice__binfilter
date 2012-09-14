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


#include "callform.hxx"
#include "global.hxx"

#include <comphelper/processfactory.hxx>
#include <tools/urlobj.hxx>
#include <ucbhelper/content.hxx>
#include <unotools/localfilehelper.hxx>

#include <tools/debug.hxx>
#include <bf_svtools/pathoptions.hxx>

#include <com/sun/star/sdbc/XResultSet.hpp>
#include <com/sun/star/sdbc/XRow.hpp>
#include <com/sun/star/ucb/XCommandEnvironment.hpp>
#include <com/sun/star/ucb/XContentAccess.hpp>

#ifdef _MSC_VER
#pragma hdrstop
#endif

using namespace ::com::sun::star;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::ucb;
namespace binfilter {


// static
/*N*/ void ScGlobal::InitAddIns()
/*N*/ {
/*N*/   // multi paths separated by semicolons
/*N*/   SvtPathOptions aPathOpt;
/*N*/   String aMultiPath = aPathOpt.GetAddinPath();
/*N*/   if ( aMultiPath.Len() > 0 )
/*N*/   {
/*N*/       xub_StrLen nTokens = aMultiPath.GetTokenCount( ';' );
/*N*/       xub_StrLen nIndex = 0;
/*N*/       for ( xub_StrLen j=0; j<nTokens; j++ )
/*N*/       {
/*N*/           String aPath( aMultiPath.GetToken( 0, ';', nIndex ) );
/*N*/           if ( aPath.Len() > 0 )
/*N*/           {
/*N*/               //  use LocalFileHelper to convert the path to a URL that always points
/*N*/               //  to the file on the server
/*N*/               rtl::OUString aUrl;
/*N*/               if ( ::utl::LocalFileHelper::ConvertPhysicalNameToURL( aPath, aUrl ) )
/*N*/                   aPath = aUrl;
/*N*/
/*N*/               INetURLObject aObj;
/*N*/               aObj.SetSmartURL( aPath );
/*N*/               aObj.setFinalSlash();
/*N*/               try
/*N*/               {
/*N*/                   ::ucbhelper::Content aCnt( aObj.GetMainURL(INetURLObject::NO_DECODE),
/*N*/                       Reference< XCommandEnvironment > (), comphelper::getProcessComponentContext() );
/*N*/                   Reference< sdbc::XResultSet > xResultSet;
/*N*/                   Sequence< ::rtl::OUString > aProps;
/*N*/                   try
/*N*/                   {
/*N*/                       xResultSet = aCnt.createCursor(
/*N*/                           aProps, ::ucbhelper::INCLUDE_DOCUMENTS_ONLY );
/*N*/                   }
/*N*/                   catch ( Exception& )
/*N*/                   {
/*N*/                       // ucb may throw different exceptions on failure now
/*N*/                       // no assertion if AddIn directory doesn't exist
/*N*/                   }
/*N*/
/*N*/                   if ( xResultSet.is() )
/*N*/                   {
/*N*/                       Reference< sdbc::XRow > xRow( xResultSet, UNO_QUERY );
/*N*/                       Reference< XContentAccess >
/*N*/                           xContentAccess( xResultSet, UNO_QUERY );
/*N*/                       try
/*N*/                       {
/*N*/                           if ( xResultSet->first() )
/*N*/                           {
/*N*/                               do
/*?*/                               {
/*?*/                                   ::rtl::OUString aId( xContentAccess->queryContentIdentifierString() );
/*?*/                               }
/*?*/                               while ( xResultSet->next() );
/*?*/                           }
/*N*/                       }
/*N*/                       catch ( Exception& )
/*N*/                       {
/*N*/                           DBG_ERRORFILE( "ResultSetException catched!" );
/*N*/                       }
/*N*/                   }
/*N*/               }
/*N*/               catch ( Exception& )
/*N*/               {
/*N*/                   DBG_ERRORFILE( "Exception catched!" );
/*N*/               }
/*N*/               catch ( ... )
/*N*/               {
/*N*/
/*N*/                   DBG_ERRORFILE( "unexpected exception caught!" );
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/ }



}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
