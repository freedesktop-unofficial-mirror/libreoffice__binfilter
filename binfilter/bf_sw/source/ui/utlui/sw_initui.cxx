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


#ifdef _MSC_VER
#pragma hdrstop
#endif

#include <viewsh.hxx>
#include <edtwin.hxx>
#include <shellres.hxx>

#include <utlui.hrc>
#include <initui.hrc>
#include <comcore.hrc>
#include <authfld.hxx>
#include <dbmgr.hxx>
#include "swtypes.hxx"
namespace binfilter {

/*--------------------------------------------------------------------
    Beschreibung:   globale Pointer
 --------------------------------------------------------------------*/

String* pOldGrfCat = 0;
String* pOldTabCat = 0;
String* pOldFrmCat = 0;
String* pOldDrwCat = 0;

SvStringsDtor* pDBNameList = 0;

SvStringsDtor*  pAuthFieldNameList = 0;
SvStringsDtor*  pAuthFieldTypeList = 0;

/*--------------------------------------------------------------------
    Beschreibung:   UI beenden
 --------------------------------------------------------------------*/

/*N*/ ShellResource::ShellResource()
/*N*/   : Resource( SW_RES(RID_SW_SHELLRES) ),
/*N*/   aPostItAuthor( SW_RESSTR( STR_POSTIT_AUTHOR ) ),
/*N*/   aPostItPage( SW_RESSTR( STR_POSTIT_PAGE ) ),
/*N*/   aPostItLine( SW_RESSTR( STR_POSTIT_LINE ) ),
/*N*/   aCalc_Syntax( SW_RESSTR( STR_CALC_SYNTAX ) ),
/*N*/   aCalc_ZeroDiv( SW_RESSTR( STR_CALC_ZERODIV ) ),
/*N*/   aCalc_Brack( SW_RESSTR( STR_CALC_BRACK ) ),
/*N*/   aCalc_Pow( SW_RESSTR( STR_CALC_POW ) ),
/*N*/   aCalc_VarNFnd( SW_RESSTR( STR_CALC_VARNFND ) ),
/*N*/   aCalc_Overflow( SW_RESSTR( STR_CALC_OVERFLOW ) ),
/*N*/   aCalc_WrongTime( SW_RESSTR( STR_CALC_WRONGTIME ) ),
/*N*/   aCalc_Default( SW_RESSTR( STR_CALC_DEFAULT ) ),
/*N*/   aCalc_Error( SW_RESSTR( STR_CALC_ERROR ) ),
/*N*/   aGetRefFld_Up( SW_RESSTR( STR_GETREFFLD_UP ) ),
/*N*/   aGetRefFld_Down( SW_RESSTR( STR_GETREFFLD_DOWN ) ),
/*N*/   aStrAllPageHeadFoot( SW_RESSTR( STR_ALLPAGE_HEADFOOT ) ),
/*N*/   aStrNone( SW_RESSTR( STR_TEMPLATE_NONE )),
/*N*/   aFixedStr( SW_RESSTR( STR_FIELD_FIXED )),
/*N*/   aTOXIndexName(          SW_RESSTR(STR_TOI)),
/*N*/   aTOXUserName(           SW_RESSTR(STR_TOU)),
/*N*/   aTOXContentName(        SW_RESSTR(STR_TOC)),
/*N*/   aTOXIllustrationsName(  SW_RESSTR(STR_TOX_ILL)),
/*N*/   aTOXObjectsName(        SW_RESSTR(STR_TOX_OBJ)),
/*N*/   aTOXTablesName(         SW_RESSTR(STR_TOX_TBL)),
/*N*/   aTOXAuthoritiesName(    SW_RESSTR(STR_TOX_AUTH)),
/*N*/   pAutoFmtNameLst( 0 ),
/*N*/   sPageDescFirstName(     SW_RESSTR(STR_PAGEDESC_FIRSTNAME)),
/*N*/   sPageDescFollowName(    SW_RESSTR(STR_PAGEDESC_FOLLOWNAME)),
/*N*/   sPageDescName(          SW_RESSTR(STR_PAGEDESC_NAME))
/*N*/ {
/*N*/   const USHORT nCount = FLD_DOCINFO_END - FLD_DOCINFO_BEGIN;
/*N*/
/*N*/   for(USHORT i = 0; i < nCount; ++i)
/*N*/   {
/*N*/       String* pNew = new String(SW_RESSTR(FLD_DOCINFO_BEGIN + i));
/*N*/       aDocInfoLst.Insert(pNew, aDocInfoLst.Count());
/*N*/   }
/*N*/
/*N*/   FreeResource();
/*N*/ }

/*N*/ ShellResource::~ShellResource()
/*N*/ {
/*N*/   if( pAutoFmtNameLst )
/*?*/       delete pAutoFmtNameLst, pAutoFmtNameLst = 0;
/*N*/ }

 const String&  SwAuthorityFieldType::GetAuthTypeName(ToxAuthorityType eType)
 {
    if(!pAuthFieldTypeList)
    {
        pAuthFieldTypeList = new SvStringsDtor(AUTH_TYPE_END, 1);
        for(USHORT i = 0; i < AUTH_TYPE_END; i++)
            pAuthFieldTypeList->Insert(
                new String(SW_RESSTR(STR_AUTH_TYPE_START + i)),
                                    pAuthFieldTypeList->Count());
    }
    return *pAuthFieldTypeList->GetObject(eType);
 }



}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
