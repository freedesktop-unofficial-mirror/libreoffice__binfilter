/*************************************************************************
 *
 *  $RCSfile: sw_prtopt.cxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:20:16 $
 *
 *  The Contents of this file are made available subject to the terms of
 *  either of the following licenses
 *
 *         - GNU Lesser General Public License Version 2.1
 *         - Sun Industry Standards Source License Version 1.1
 *
 *  Sun Microsystems Inc., October, 2000
 *
 *  GNU Lesser General Public License Version 2.1
 *  =============================================
 *  Copyright 2000 by Sun Microsystems, Inc.
 *  901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License version 2.1, as published by the Free Software Foundation.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *  MA  02111-1307  USA
 *
 *
 *  Sun Industry Standards Source License Version 1.1
 *  =================================================
 *  The contents of this file are subject to the Sun Industry Standards
 *  Source License Version 1.1 (the "License"); You may not use this file
 *  except in compliance with the License. You may obtain a copy of the
 *  License at http://www.openoffice.org/license.html.
 *
 *  Software provided under this License is provided on an "AS IS" basis,
 *  WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING,
 *  WITHOUT LIMITATION, WARRANTIES THAT THE SOFTWARE IS FREE OF DEFECTS,
 *  MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE, OR NON-INFRINGING.
 *  See the License for the specific provisions governing your rights and
 *  obligations concerning the Software.
 *
 *  The Initial Developer of the Original Code is: Sun Microsystems, Inc.
 *
 *  Copyright: 2000 by Sun Microsystems, Inc.
 *
 *  All Rights Reserved.
 *
 *  Contributor(s): _______________________________________
 *
 *
 ************************************************************************/


#pragma hdrstop

#ifndef _UTL_CONFIGMGR_HXX_
#include <unotools/configmgr.hxx>
#endif
#ifndef _PRTOPT_HXX
#include <prtopt.hxx>
#endif
#ifndef _SWPRTOPT_HXX
#include <swprtopt.hxx>
#endif

#ifndef _TOOLS_DEBUG_HXX
#include <tools/debug.hxx>
#endif
#ifndef _COM_SUN_STAR_UNO_ANY_HXX_
#include <com/sun/star/uno/Any.hxx>
#endif
#ifndef _COM_SUN_STAR_UNO_SEQUENCE_HXX_
#include <com/sun/star/uno/Sequence.hxx>
#endif

using namespace utl;
using namespace rtl;
using namespace com::sun::star::uno;

/*N*/ #define C2U(cChar) OUString::createFromAscii(cChar)
/*--------------------------------------------------------------------
     Beschreibung: Ctor
 --------------------------------------------------------------------*/

/*N*/ Sequence<OUString> SwPrintOptions::GetPropertyNames()
/*N*/ {
/*N*/   static const char* aPropNames[] =
/*N*/   {
/*N*/       "Content/Graphic",              //  0
/*N*/       "Content/Table",                //  1
/*N*/       "Content/Control",              //  2
/*N*/       "Content/Background",           //  3
/*N*/       "Content/PrintBlack",           //  4
/*N*/       "Content/Note",                 //  5
/*N*/       "Page/Reversed",                //  6
/*N*/       "Page/Brochure",                //  7
/*N*/       "Output/SinglePrintJob",        //  8
/*N*/       "Output/Fax",                   //  9
/*N*/       "Papertray/FromPrinterSetup",   // 10
/*N*/       "Content/Drawing",              // 11 not in SW/Web
/*N*/       "Page/LeftPage",                // 12 not in SW/Web
/*N*/       "Page/RightPage"                // 13 not in SW/Web
/*N*/   };
/*N*/   const int nCount = bIsWeb ? 11 : 14;
/*N*/   Sequence<OUString> aNames(nCount);
/*N*/   OUString* pNames = aNames.getArray();
/*N*/   for(int i = 0; i < nCount; i++)
/*N*/   {
/*N*/       pNames[i] = OUString::createFromAscii(aPropNames[i]);
/*N*/   }
/*N*/   return aNames;
/*N*/ }
/* -----------------------------06.09.00 16:44--------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ SwPrintOptions::SwPrintOptions(sal_Bool bWeb) :
/*N*/     ConfigItem(bWeb ? C2U("Office.WriterWeb/Print") :  C2U("Office.Writer/Print"),
/*N*/         CONFIG_MODE_DELAYED_UPDATE|CONFIG_MODE_RELEASE_TREE),
/*N*/   bIsWeb(bWeb)
/*N*/ {
/*N*/     bPrintPageBackground = !bWeb;
/*N*/     bPrintBlackFont = bWeb;
/*N*/     Sequence<OUString> aNames = GetPropertyNames();
/*N*/   Sequence<Any> aValues = GetProperties(aNames);
/*N*/   const Any* pValues = aValues.getConstArray();
/*N*/   DBG_ASSERT(aValues.getLength() == aNames.getLength(), "GetProperties failed")
/*N*/   if(aValues.getLength() == aNames.getLength())
/*N*/   {
/*N*/       for(int nProp = 0; nProp < aNames.getLength(); nProp++)
/*N*/       {
/*N*/           if(pValues[nProp].hasValue())
/*N*/           {
/*N*/               switch(nProp)
/*N*/               {
/*N*/                   case  0: bPrintGraphic      = *(sal_Bool*)pValues[nProp].getValue(); break;
/*N*/                   case  1: bPrintTable            = *(sal_Bool*)pValues[nProp].getValue();  break;
/*N*/                   case  2: bPrintControl      = *(sal_Bool*)pValues[nProp].getValue() ;  break;
/*N*/                   case  3: bPrintPageBackground= *(sal_Bool*)pValues[nProp].getValue();  break;
/*N*/                   case  4: bPrintBlackFont        = *(sal_Bool*)pValues[nProp].getValue();  break;
/*N*/                     case  5:
/*N*/                     {
/*N*/                         sal_Int32 nTmp;
/*N*/                         pValues[nProp] >>=  nTmp;
/*N*/                         nPrintPostIts = (sal_Int16)nTmp;
/*N*/                     }
/*N*/                     break;
/*N*/                     case  6: bPrintReverse      = *(sal_Bool*)pValues[nProp].getValue();  break;
/*N*/                   case  7: bPrintProspect      = *(sal_Bool*)pValues[nProp].getValue();  break;
/*N*/                   case  8: bPrintSingleJobs   = *(sal_Bool*)pValues[nProp].getValue();  break;
/*N*/                   case  9: pValues[nProp] >>= sFaxName;  break;
/*N*/                   case 10: bPaperFromSetup    = *(sal_Bool*)pValues[nProp].getValue();  break;
/*N*/                   case 11: bPrintDraw         = *(sal_Bool*)pValues[nProp].getValue() ;  break;
/*N*/                   case 12: bPrintLeftPage     = *(sal_Bool*)pValues[nProp].getValue();  break;
/*N*/                   case 13: bPrintRightPage        = *(sal_Bool*)pValues[nProp].getValue();  break;
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/ }
/* -----------------------------06.09.00 16:50--------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ SwPrintOptions::~SwPrintOptions()
/*N*/ {
/*N*/ }
/* -----------------------------06.09.00 16:43--------------------------------

 ---------------------------------------------------------------------------*/
//STRIP001 void SwPrintOptions::Commit()
//STRIP001 {
//STRIP001  Sequence<OUString> aNames = GetPropertyNames();
//STRIP001
//STRIP001  OUString* pNames = aNames.getArray();
//STRIP001  Sequence<Any> aValues(aNames.getLength());
//STRIP001  Any* pValues = aValues.getArray();
//STRIP001
//STRIP001  const Type& rType = ::getBooleanCppuType();
//STRIP001  BOOL bVal;
//STRIP001  for(int nProp = 0; nProp < aNames.getLength(); nProp++)
//STRIP001  {
//STRIP001      switch(nProp)
//STRIP001      {
//STRIP001          case  0: bVal = bPrintGraphic; pValues[nProp].setValue(&bVal, rType);break;
//STRIP001          case  1: bVal = bPrintTable         ;pValues[nProp].setValue(&bVal, rType);  break;
//STRIP001          case  2: bVal = bPrintControl        ; pValues[nProp].setValue(&bVal, rType);  break;
//STRIP001          case  3: bVal = bPrintPageBackground; pValues[nProp].setValue(&bVal, rType);  break;
//STRIP001          case  4: bVal = bPrintBlackFont     ; pValues[nProp].setValue(&bVal, rType);  break;
//STRIP001             case  5: pValues[nProp] <<=  (sal_Int32)nPrintPostIts       ; break;
//STRIP001             case  6: bVal = bPrintReverse       ; pValues[nProp].setValue(&bVal, rType);  break;
//STRIP001          case  7: bVal = bPrintProspect      ; pValues[nProp].setValue(&bVal, rType);  break;
//STRIP001          case  8: bVal = bPrintSingleJobs     ; pValues[nProp].setValue(&bVal, rType);  break;
//STRIP001          case  9: pValues[nProp] <<= sFaxName;  break;
//STRIP001          case 10: bVal = bPaperFromSetup     ; pValues[nProp].setValue(&bVal, rType);  break;
//STRIP001          case 11: bVal = bPrintDraw           ; pValues[nProp].setValue(&bVal, rType);  break;
//STRIP001          case 12: bVal = bPrintLeftPage       ; pValues[nProp].setValue(&bVal, rType);  break;
//STRIP001          case 13: bVal = bPrintRightPage     ; pValues[nProp].setValue(&bVal, rType);  break;
//STRIP001      }
//STRIP001  }
//STRIP001  PutProperties(aNames, aValues);
//STRIP001 }




