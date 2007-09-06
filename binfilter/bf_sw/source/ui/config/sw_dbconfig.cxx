/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_dbconfig.cxx,v $
 *
 *  $Revision: 1.7 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 13:08:33 $
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


#ifdef _MSC_VER
#pragma hdrstop
#endif

#ifndef _DBCONFIG_HXX
#include <dbconfig.hxx>
#endif

#ifndef _TOOLS_DEBUG_HXX
#include <tools/debug.hxx>
#endif
#ifndef _COM_SUN_STAR_UNO_SEQUENCE_HXX_
#include <com/sun/star/uno/Sequence.hxx>
#endif
#ifndef _SWDBDATA_HXX
#include <swdbdata.hxx>
#endif
namespace binfilter {
using namespace utl;
using namespace rtl;
using namespace ::com::sun::star::uno;

/*N*/ #define C2U(cChar) OUString::createFromAscii(cChar)
/*--------------------------------------------------------------------
     Beschreibung: Ctor
 --------------------------------------------------------------------*/

/*N*/ const Sequence<OUString>& SwDBConfig::GetPropertyNames()
/*N*/ {
/*N*/   static Sequence<OUString> aNames;
/*N*/   if(!aNames.getLength())
/*N*/   {
/*N*/       static const char* aPropNames[] =
/*N*/       {
/*N*/             "AddressBook/DataSourceName",        //  0
/*N*/             "AddressBook/Command",              //  1
/*N*/             "AddressBook/CommandType",          //  2
/*N*/             "Bibliography/CurrentDataSource/DataSourceName",        //  4
/*N*/             "Bibliography/CurrentDataSource/Command",              //  5
/*N*/             "Bibliography/CurrentDataSource/CommandType"          //  6
/*N*/         };
/*N*/         const int nCount = sizeof(aPropNames)/sizeof(const char*);
/*N*/       aNames.realloc(nCount);
/*N*/       OUString* pNames = aNames.getArray();
/*N*/       for(int i = 0; i < nCount; i++)
/*N*/           pNames[i] = OUString::createFromAscii(aPropNames[i]);
/*N*/   }
/*N*/   return aNames;
/*N*/ }
/* -----------------------------06.09.00 16:44--------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ SwDBConfig::SwDBConfig() :
/*N*/     ConfigItem(C2U("Office.DataAccess"),
/*N*/         CONFIG_MODE_DELAYED_UPDATE|CONFIG_MODE_RELEASE_TREE),
/*N*/     pAdrImpl(0),
/*N*/     pBibImpl(0)
/*N*/ {
/*N*/ };
/* -----------------------------06.09.00 16:50--------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ SwDBConfig::~SwDBConfig()
/*N*/ {
/*N*/     delete pAdrImpl;
/*N*/     delete pBibImpl;
/*N*/ }
/* -----------------------------20.02.01 12:32--------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ void SwDBConfig::Load()
/*N*/ {
/*N*/   const Sequence<OUString>& rNames = GetPropertyNames();
/*N*/     if(!pAdrImpl)
/*N*/   {
/*N*/
/*N*/         pAdrImpl = new SwDBData;
/*N*/         pAdrImpl->nCommandType = 0;
/*N*/         pBibImpl = new SwDBData;
/*N*/         pBibImpl->nCommandType = 0;
/*N*/     }
/*N*/   Sequence<Any> aValues = GetProperties(rNames);
/*N*/   const Any* pValues = aValues.getConstArray();
/*N*/   DBG_ASSERT(aValues.getLength() == rNames.getLength(), "GetProperties failed")
/*N*/   if(aValues.getLength() == rNames.getLength())
/*N*/   {
/*N*/       for(int nProp = 0; nProp < rNames.getLength(); nProp++)
/*N*/       {
/*N*/           switch(nProp)
/*N*/           {
/*N*/                 case  0: pValues[nProp] >>= pAdrImpl->sDataSource;  break;
/*N*/                 case  1: pValues[nProp] >>= pAdrImpl->sCommand;     break;
/*N*/                 case  2: pValues[nProp] >>= pAdrImpl->nCommandType; break;
/*N*/                 case  3: pValues[nProp] >>= pBibImpl->sDataSource;  break;
/*N*/                 case  4: pValues[nProp] >>= pBibImpl->sCommand;     break;
/*N*/                 case  5: pValues[nProp] >>= pBibImpl->nCommandType; break;
/*N*/             }
/*N*/       }
/*N*/   }
/*N*/ }
/* -----------------------------20.02.01 12:36--------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ const SwDBData& SwDBConfig::GetAddressSource()
/*N*/ {
/*N*/     if(!pAdrImpl)
/*N*/       Load();
/*N*/     return *pAdrImpl;
/*N*/ }
}
