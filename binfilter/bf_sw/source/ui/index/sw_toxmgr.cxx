/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_toxmgr.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: kz $ $Date: 2006-11-08 12:47:26 $
 *
 *  The Contents of this file are made available subject to
 *  the terms of GNU Lesser General Public License Version 2.1.
 *
 *
 *    GNU Lesser General Public License Version 2.1
 *    =============================================
 *    Copyright 2005 by Sun Microsystems, Inc.
 *    901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *    This library is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License version 2.1, as published by the Free Software Foundation.
 *
 *    This library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with this library; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *    MA  02111-1307  USA
 *
 ************************************************************************/


#pragma hdrstop

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

#ifndef _WRTSH_HXX
#include <wrtsh.hxx>
#endif
#ifndef _SHELLRES_HXX
#include <shellres.hxx>
#endif
#ifndef _TOXMGR_HXX
#include <toxmgr.hxx>
#endif

#ifndef _GLOBALS_HRC
#include <globals.hrc>
#endif
namespace binfilter {

/*-----------------23.01.98 07:41-------------------
    Standard - Verzeichnisnamen herausreichen
--------------------------------------------------*/
/*N*/ const String& SwTOXBase::GetTOXName(TOXTypes eType)
/*N*/ {
/*N*/   const String* pRet;
/*N*/   ShellResource* pShellRes = ViewShell::GetShellRes();
/*N*/   switch(eType)
/*N*/   {
/*N*/       case  TOX_CONTENT      :    pRet = &pShellRes->aTOXContentName;       break;
/*N*/       case  TOX_INDEX        :    pRet = &pShellRes->aTOXIndexName;         break;
/*?*/       case  TOX_USER         :    pRet = &pShellRes->aTOXUserName;          break;
/*?*/       case  TOX_ILLUSTRATIONS:    pRet = &pShellRes->aTOXIllustrationsName; break;
/*?*/       case  TOX_OBJECTS      :    pRet = &pShellRes->aTOXObjectsName;       break;
/*?*/       case  TOX_TABLES       :    pRet = &pShellRes->aTOXTablesName;        break;
/*?*/       case  TOX_AUTHORITIES :     pRet = &pShellRes->aTOXAuthoritiesName;   break;
/*N*/   }
/*N*/   return *pRet;
/*N*/ }

}
