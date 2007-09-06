/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sfx2_misccfg.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 11:27:20 $
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

#ifndef _ZFORLIST_HXX //autogen
#include <svtools/zforlist.hxx>
#endif

#ifndef _TOOLS_DEBUG_HXX
#include <tools/debug.hxx>
#endif
#include "misccfg.hxx"
namespace binfilter {

#define DEFAULT_TAB 2000

#define DEF_INCH    2540L
#define DEF_RELTWIP 1440L

using namespace rtl;
using namespace ::com::sun::star::uno;

#define C2U(cChar) OUString::createFromAscii(cChar)
/*--------------------------------------------------------------------
     Beschreibung:
 --------------------------------------------------------------------*/
/*N*/ SfxMiscCfg::SfxMiscCfg() :
/*N*/   ConfigItem(C2U("Office.Common") ),
/*N*/   nYear2000( SvNumberFormatter::GetYear2000Default() ),
/*N*/   bNotFound (FALSE),
/*N*/   bPaperSize(FALSE),
/*N*/   bPaperOrientation (FALSE)
/*N*/ {
/*N*/   Load();
/*N*/ }
/* -----------------------------02.03.01 15:31--------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ SfxMiscCfg::~SfxMiscCfg()
/*N*/ {
/*N*/ }
/*--------------------------------------------------------------------
     Beschreibung:
 --------------------------------------------------------------------*/

/*?*/ void SfxMiscCfg::SetNotFoundWarning( BOOL bSet)
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*?*/ }

/*--------------------------------------------------------------------
     Beschreibung:
 --------------------------------------------------------------------*/

/*?*/ void SfxMiscCfg::SetPaperSizeWarning( BOOL bSet)
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*?*/ }

/*--------------------------------------------------------------------
     Beschreibung:
 --------------------------------------------------------------------*/
/*?*/ void SfxMiscCfg::SetPaperOrientationWarning( BOOL bSet)
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*?*/ }
/*--------------------------------------------------------------------
     Beschreibung:
 --------------------------------------------------------------------*/

/*?*/ void SfxMiscCfg::SetYear2000( sal_Int32 nSet )
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*?*/ }
/* -----------------------------02.03.01 15:31--------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ const Sequence<OUString>& SfxMiscCfg::GetPropertyNames()
/*N*/ {
/*N*/   static Sequence<OUString> aNames;
/*N*/   if(!aNames.getLength())
/*N*/   {
/*N*/       static const char* aPropNames[] =
/*N*/       {
/*N*/               "Print/Warning/PaperSize",              //  0
/*N*/               "Print/Warning/PaperOrientation",       //  1
/*N*/               "Print/Warning/NotFound",               //  2
/*N*/           "DateFormat/TwoDigitYear",              //  3
/*N*/       };
/*N*/         const int nCount = 4;
/*N*/       aNames.realloc(nCount);
/*N*/       OUString* pNames = aNames.getArray();
/*N*/       for(int i = 0; i < nCount; i++)
/*N*/           pNames[i] = OUString::createFromAscii(aPropNames[i]);
/*N*/   }
/*N*/   return aNames;
/*N*/ }
/* -----------------------------02.03.01 15:31--------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ void SfxMiscCfg::Load()
/*N*/ {
/*N*/   const Sequence<OUString>& aNames = GetPropertyNames();
/*N*/   Sequence<Any> aValues = GetProperties(aNames);
/*N*/   EnableNotification(aNames);
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
/*N*/                   case  0: bPaperSize        = *(sal_Bool*)pValues[nProp].getValue(); break;      //"Print/Warning/PaperSize",
/*N*/                     case  1: bPaperOrientation = *(sal_Bool*)pValues[nProp].getValue();  break;     //"Print/Warning/PaperOrientation",
/*N*/                     case  2: bNotFound         = *(sal_Bool*)pValues[nProp].getValue()  ;  break;   //"Print/Warning/NotFound",
/*N*/                   case  3: pValues[nProp] >>= nYear2000;break;                                    //"DateFormat/TwoDigitYear",
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/ }
/* -----------------------------02.03.01 15:31--------------------------------

 ---------------------------------------------------------------------------*/
/*?*/ void SfxMiscCfg::Notify( const ::com::sun::star::uno::Sequence<rtl::OUString>& aPropertyNames)
/*?*/ {
/*?*/   Load();
/*?*/ }
/* -----------------------------02.03.01 15:31--------------------------------

 ---------------------------------------------------------------------------*/
/*?*/ void SfxMiscCfg::Commit()
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*?*/ }

}
