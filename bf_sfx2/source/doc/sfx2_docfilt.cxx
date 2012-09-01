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


#ifdef SOLARIS
#include <ctime>
#endif

#include <string>


#ifdef _MSC_VER
#pragma hdrstop
#endif

#include "fltfnc.hxx"
#include "sfxuno.hxx"

namespace binfilter {

/*N*/ SfxFilter::SfxFilter(  const String &rName,
/*N*/                      const String &rWildCard,
/*N*/                      SfxFilterFlags nType,
/*N*/                      ULONG lFmt,
/*N*/                      const String &rMacTyp,
/*N*/                      const String &rTypNm,
/*N*/                      sal_uInt16 nIcon,
/*N*/                      const String &rMimeType,
/*N*/                      const SfxFilterContainer* pContainerP,
/*N*/                      const String &rUsrDat ):
/*N*/   aName( rName ),
/*N*/   aWildCard(rWildCard, ';'),
/*N*/   lFormat(lFmt),
/*N*/   aMacType(rMacTyp),
/*N*/   aTypeName(rTypNm),
/*N*/   aUserData(rUsrDat),
/*N*/   nFormatType(nType),
/*N*/   nDocIcon(nIcon),
/*N*/   pContainer( pContainerP ),
/*N*/   aMimeType( rMimeType ),
/*N*/   aFilterName( rName )
/*N*/ {
/*N*/   InitMembers_Impl();
/*N*/   pContainer = pContainerP;
/*N*/   aFilterName = rName;
/*N*/   aMimeType = rMimeType;
/*N*/ }

/*N*/ void SfxFilter::InitMembers_Impl()
/*N*/ {
/*N*/   String aExts = GetWildcard().getGlob();
/*N*/   String aShort, aLong;
/*N*/   String aRet;
/*N*/   sal_uInt16 nMaxLength =
/*N*/ #if defined( WIN ) || defined( OS2 )
/*N*/       3
/*N*/ #else
/*N*/       USHRT_MAX
/*N*/ #endif
/*N*/       ;
/*N*/   String aTest;
/*N*/   sal_uInt16 nPos = 0;
/*N*/   while( ( aRet = aExts.GetToken( nPos++, ';' ) ).Len() )
/*N*/   {
/*N*/       aTest = aRet;
/*N*/       aTest.SearchAndReplace( DEFINE_CONST_UNICODE( "*." ), String() );
/*N*/       if( aTest.Len() <= nMaxLength )
/*N*/       {
/*N*/           if( aShort.Len() ) aShort += ';';
/*N*/           aShort += aRet;
/*N*/       }
/*N*/       else
/*N*/       {
/*N*/           if( aLong.Len() ) aLong += ';';
/*N*/           aLong += aRet;
/*N*/       }
/*N*/   }
/*N*/   if( aShort.Len() && aLong.Len() )
/*N*/   {
/*N*/       aShort += ';';
/*N*/       aShort += aLong;
/*N*/   }
/*N*/   aWildCard.setGlob(aShort);
/*N*/
/*N*/   nVersion = SOFFICE_FILEFORMAT_50;
/*N*/   bPlugDataSearched = 0;
/*N*/   pPlugData = 0;
/*N*/   aUIName = aFilterName;
/*N*/ }

/*N*/ SfxFilter::~SfxFilter()
/*N*/ {
/*N*/   delete pPlugData;
/*N*/ }

/*N*/ const String& SfxFilter::GetTypeName() const
/*N*/ {
/*N*/   return
/*N*/ #ifdef MAC
/*N*/   aMacType;
/*N*/ #else
/*N*/   aTypeName;
/*N*/ #endif
/*N*/ }

/*N*/ String SfxFilter::GetFilterNameWithPrefix() const
/*N*/ {
/*N*/     String aLclName = pContainer->GetName();
/*N*/     aLclName += DEFINE_CONST_UNICODE( ": " );
/*N*/     aLclName += aFilterName;
/*N*/     return aLclName;
/*N*/ }
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
