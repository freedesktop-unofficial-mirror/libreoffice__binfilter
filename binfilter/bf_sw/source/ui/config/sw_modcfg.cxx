/*************************************************************************
 *
 *  $RCSfile: sw_modcfg.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:54:11 $
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

#ifndef _HINTIDS_HXX
#include <hintids.hxx>
#endif
#ifndef _SO_CLSIDS_HXX
#include <so3/clsids.hxx>
#endif
#ifndef _STREAM_HXX //autogen
#include <tools/stream.hxx>
#endif
#ifndef _SV_SVAPP_HXX //autogen
#include <vcl/svapp.hxx>
#endif
#ifndef _MAILENUM_HXX //autogen
#include <goodies/mailenum.hxx>
#endif
#ifndef _SVX_SVXIDS_HRC //autogen
#include <bf_svx/svxids.hrc>
#endif
#ifndef _SVX_SVXENUM_HXX //autogen
#include <bf_svx/svxenum.hxx>
#endif
#ifndef _TOOLS_DEBUG_HXX //autogen
#include <tools/debug.hxx>
#endif
#ifndef _FACTORY_HXX //autogen
#include <so3/factory.hxx>
#endif

#ifndef _SWTYPES_HXX
#include <swtypes.hxx>
#endif
#ifndef _ITABENUM_HXX
#include <itabenum.hxx>
#endif
#ifndef _MODCFG_HXX
#include <modcfg.hxx>
#endif
#ifndef _FLDUPDE_HXX
#include <fldupde.hxx>
#endif

#ifndef _COM_SUN_STAR_UNO_ANY_HXX_
#include <com/sun/star/uno/Any.hxx>
#endif
#ifndef _COM_SUN_STAR_UNO_SEQUENCE_HXX_
#include <com/sun/star/uno/Sequence.hxx>
#endif
namespace binfilter {

using namespace utl;
using namespace rtl;
using namespace ::com::sun::star::uno;

#define C2U(cChar) OUString::createFromAscii(cChar)
#define GLOB_NAME_CALC      0
#define GLOB_NAME_IMPRESS   1
#define GLOB_NAME_DRAW      2
#define GLOB_NAME_MATH      3
#define GLOB_NAME_CHART     4

/*N*/ SV_IMPL_PTRARR_SORT(InsCapOptArr, InsCaptionOptPtr)
/* -----------------03.11.98 13:46-------------------
 *
 * --------------------------------------------------*/
/*N*/ InsCaptionOpt* InsCaptionOptArr::Find(const SwCapObjType eType, const SvGlobalName *pOleId) const
/*N*/ {
/*N*/   for (USHORT i = 0; i < Count(); i++ )
/*N*/   {
/*?*/       InsCaptionOpt* pObj = GetObject(i);
/*?*/       if (pObj->GetObjType() == eType &&
/*?*/           (eType != OLE_CAP ||
/*?*/            (pOleId &&
/*?*/             (pObj->GetOleId() == *pOleId ||
/*?*/              SvFactory::GetAutoConvertTo(pObj->GetOleId()) == *pOleId))))
/*?*/           return pObj;
/*N*/   }
/*N*/
/*N*/   return 0;
/*N*/ }

/* -----------------03.11.98 15:05-------------------
 *
 * --------------------------------------------------*/

//STRIP001 const InsCaptionOpt* SwModuleOptions::GetCapOption(
//STRIP001  BOOL bHTML, const SwCapObjType eType, const SvGlobalName *pOleId)
//STRIP001 {
//STRIP001  if(bHTML)
//STRIP001  {
//STRIP001      DBG_ERROR("no caption option in sw/web!")
//STRIP001      return 0;
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      sal_Bool bFound = FALSE;
//STRIP001      if(eType == OLE_CAP && pOleId)
//STRIP001      {
//STRIP001          for( USHORT nId = 0; nId <= GLOB_NAME_CHART && !bFound; nId++)
//STRIP001              bFound = *pOleId == aInsertConfig.aGlobalNames[nId  ];
//STRIP001          if(!bFound)
//STRIP001              return aInsertConfig.pOLEMiscOpt;
//STRIP001      }
//STRIP001      return aInsertConfig.pCapOptions->Find(eType, pOleId);
//STRIP001  }
//STRIP001 }

/* -----------------03.11.98 15:05-------------------
 *
 * --------------------------------------------------*/

//STRIP001 BOOL SwModuleOptions::SetCapOption(BOOL bHTML, const InsCaptionOpt* pOpt)
//STRIP001 {
//STRIP001  BOOL bRet = FALSE;
//STRIP001
//STRIP001  if(bHTML)
//STRIP001  {
//STRIP001      DBG_ERROR("no caption option in sw/web!")
//STRIP001  }
//STRIP001  else if (pOpt)
//STRIP001  {
//STRIP001      sal_Bool bFound = FALSE;
//STRIP001      if(pOpt->GetObjType() == OLE_CAP && &pOpt->GetOleId())
//STRIP001      {
//STRIP001          for( USHORT nId = 0; nId <= GLOB_NAME_CHART; nId++)
//STRIP001              bFound = pOpt->GetOleId() == aInsertConfig.aGlobalNames[nId  ];
//STRIP001          if(!bFound)
//STRIP001          {
//STRIP001              if(aInsertConfig.pOLEMiscOpt)
//STRIP001                  *aInsertConfig.pOLEMiscOpt = *pOpt;
//STRIP001              else
//STRIP001                  aInsertConfig.pOLEMiscOpt = new InsCaptionOpt(*pOpt);
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      InsCaptionOptArr& rArr = *aInsertConfig.pCapOptions;
//STRIP001      InsCaptionOpt *pObj = rArr.Find(pOpt->GetObjType(), &pOpt->GetOleId());
//STRIP001
//STRIP001      if (pObj)
//STRIP001      {
//STRIP001          *pObj = *pOpt;
//STRIP001      }
//STRIP001      else
//STRIP001          rArr.Insert(new InsCaptionOpt(*pOpt));
//STRIP001
//STRIP001      aInsertConfig.SetModified();
//STRIP001      bRet = TRUE;
//STRIP001  }
//STRIP001
//STRIP001  return bRet;
//STRIP001 }
/*-----------------13.01.97 12.44-------------------

--------------------------------------------------*/
/*N*/ SwModuleOptions::SwModuleOptions() :
/*N*/   aInsertConfig(FALSE),
/*N*/   aWebInsertConfig(TRUE),
/*N*/   aTableConfig(FALSE),
/*N*/   aWebTableConfig(TRUE),
/*N*/   bHideFieldTips(FALSE)
/*N*/ {
/*N*/ }
/* -----------------------------19.01.01 12:26--------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ String SwModuleOptions::ConvertWordDelimiter(const String& rDelim, BOOL bFromUI)
/*N*/ {
/*N*/   String sReturn;
/*N*/   if(bFromUI)
/*N*/   {
/*N*/       String sChar;
/*N*/
/*N*/       xub_StrLen i = 0;
/*N*/       sal_Unicode c;
/*N*/
/*N*/       while (i < rDelim.Len())
/*N*/       {
/*N*/           c = rDelim.GetChar(i++);
/*N*/
/*N*/           if (c == '\\')
/*N*/           {
/*N*/               c = rDelim.GetChar(i++);
/*N*/
/*N*/               switch (c)
/*N*/               {
/*N*/                   case 'n':   sReturn += '\n';    break;
/*N*/                   case 't':   sReturn += '\t';    break;
/*?*/                   case '\\':  sReturn += '\\';    break;
/*N*/
/*N*/                   case 'x':
/*N*/                   {
/*N*/                       sal_Unicode nVal, nChar;
/*N*/                       BOOL bValidData = TRUE;
/*N*/                       xub_StrLen n;
/*N*/                       for( n = 0, nChar = 0; n < 2 && i < rDelim.Len(); ++n, ++i )
/*N*/                       {
/*N*/                           if( ((nVal = rDelim.GetChar( i )) >= '0') && ( nVal <= '9') )
/*?*/                               nVal -= '0';
/*N*/                           else if( (nVal >= 'A') && (nVal <= 'F') )
/*?*/                               nVal -= 'A' - 10;
/*N*/                           else if( (nVal >= 'a') && (nVal <= 'f') )
/*N*/                               nVal -= 'a' - 10;
/*N*/                           else
/*N*/                           {
/*?*/                               DBG_ERROR( "ungueltiger Hex-Wert" );
/*?*/                               bValidData = FALSE;
/*?*/                               break;
/*N*/                           }
/*N*/
/*N*/                           (nChar <<= 4 ) += nVal;
/*N*/                       }
/*N*/                       if( bValidData )
/*N*/                           sReturn += nChar;
/*N*/                       break;
/*N*/                   }
/*N*/
/*?*/                   default:    // Unbekannt, daher nur Backslash einfuegen
/*?*/                       sReturn += '\\';
/*?*/                       i--;
/*?*/                       break;
/*N*/               }
/*N*/           }
/*N*/           else
/*N*/               sReturn += c;
/*N*/       }
/*N*/   }
/*N*/   else
/*N*/   {
/*?*/       for (xub_StrLen i = 0; i < rDelim.Len(); i++)
/*?*/       {
/*?*/           sal_Unicode c = rDelim.GetChar(i);
/*?*/
/*?*/           switch (c)
/*?*/           {
/*?*/               case '\n':  sReturn.AppendAscii(RTL_CONSTASCII_STRINGPARAM("\\n")); break;
/*?*/               case '\t':  sReturn.AppendAscii(RTL_CONSTASCII_STRINGPARAM("\\t")); break;
/*?*/               case '\\':  sReturn.AppendAscii(RTL_CONSTASCII_STRINGPARAM("\\\\"));    break;
/*?*/
/*?*/               default:
/*?*/                   if( c <= 0x1f || c >= 0x7f )
/*?*/                   {
/*?*/                       sReturn.AppendAscii( RTL_CONSTASCII_STRINGPARAM( "\\x" ))
/*?*/                           += String::CreateFromInt32( c, 16 );
/*?*/                   }
/*?*/                   else
/*?*/                       sReturn += c;
/*?*/           }
/*?*/       }
/*N*/   }
/*N*/   return sReturn;
/*N*/ }
/* -----------------------------10.10.00 16:22--------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ const Sequence<OUString>& SwRevisionConfig::GetPropertyNames()
/*N*/ {
/*N*/   static Sequence<OUString> aNames;
/*N*/   if(!aNames.getLength())
/*N*/   {
/*N*/       const int nCount = 8;
/*N*/       aNames.realloc(nCount);
/*N*/       static const char* aPropNames[] =
/*N*/       {
/*N*/           "TextDisplay/Insert/Attribute",             // 0
/*N*/           "TextDisplay/Insert/Color",                 // 1
/*N*/           "TextDisplay/Delete/Attribute",             // 2
/*N*/           "TextDisplay/Delete/Color",                 // 3
/*N*/           "TextDisplay/ChangedAttribute/Attribute",   // 4
/*N*/           "TextDisplay/ChangedAttribute/Color",       // 5
/*N*/           "LinesChanged/Mark",                        // 6
/*N*/           "LinesChanged/Color"                        // 7
/*N*/       };
/*N*/       OUString* pNames = aNames.getArray();
/*N*/       for(int i = 0; i < nCount; i++)
/*N*/           pNames[i] = OUString::createFromAscii(aPropNames[i]);
/*N*/   }
/*N*/   return aNames;
/*N*/ }
/*-- 10.10.00 16:22:22---------------------------------------------------

  -----------------------------------------------------------------------*/
/*N*/ SwRevisionConfig::SwRevisionConfig() :
/*N*/     ConfigItem(C2U("Office.Writer/Revision"),
/*N*/         CONFIG_MODE_DELAYED_UPDATE|CONFIG_MODE_RELEASE_TREE)
/*N*/ {
/*N*/   aInsertAttr.nItemId = SID_ATTR_CHAR_UNDERLINE;
/*N*/   aInsertAttr.nAttr = UNDERLINE_SINGLE;
/*N*/   aInsertAttr.nColor = COL_TRANSPARENT;
/*N*/   aDeletedAttr.nItemId = SID_ATTR_CHAR_STRIKEOUT;
/*N*/   aDeletedAttr.nAttr = STRIKEOUT_SINGLE;
/*N*/   aDeletedAttr.nColor = COL_TRANSPARENT;
/*N*/   aFormatAttr.nItemId = SID_ATTR_CHAR_WEIGHT;
/*N*/   aFormatAttr.nAttr = WEIGHT_BOLD;
/*N*/   aFormatAttr.nColor = COL_BLACK;
/*N*/
/*N*/     Load();
/*N*/ }
/*-- 10.10.00 16:22:23---------------------------------------------------

  -----------------------------------------------------------------------*/
/*N*/ SwRevisionConfig::~SwRevisionConfig()
/*N*/ {
/*N*/ }
/*-- 10.10.00 16:22:56---------------------------------------------------

  -----------------------------------------------------------------------*/
//STRIP001 sal_Int32 lcl_ConvertAttrToCfg(const AuthorCharAttr& rAttr)
//STRIP001 {
//STRIP001  sal_Int32 nRet = 0;
//STRIP001  switch(rAttr.nItemId)
//STRIP001  {
//STRIP001      case  SID_ATTR_CHAR_WEIGHT: nRet = 1; break;
//STRIP001      case  SID_ATTR_CHAR_POSTURE: nRet = 2; break;
//STRIP001      case  SID_ATTR_CHAR_UNDERLINE: nRet = UNDERLINE_SINGLE == rAttr.nAttr ? 3 : 4; break;
//STRIP001         case  SID_ATTR_CHAR_STRIKEOUT: nRet = 3; break;
//STRIP001      case  SID_ATTR_CHAR_CASEMAP:
//STRIP001      {
//STRIP001          switch(rAttr.nAttr)
//STRIP001          {
//STRIP001              case  SVX_CASEMAP_VERSALIEN   : nRet = 5;break;
//STRIP001              case  SVX_CASEMAP_GEMEINE     : nRet = 6;break;
//STRIP001              case  SVX_CASEMAP_KAPITAELCHEN: nRet = 7;break;
//STRIP001              case  SVX_CASEMAP_TITEL       : nRet = 8;break;
//STRIP001          }
//STRIP001      }
//STRIP001         break;
//STRIP001      case SID_ATTR_BRUSH : nRet = 9; break;
//STRIP001  }
//STRIP001  return nRet;
//STRIP001 }
//-----------------------------------------------------------------------------
//STRIP001 void SwRevisionConfig::Commit()
//STRIP001 {
//STRIP001  const Sequence<OUString>& aNames = GetPropertyNames();
//STRIP001  const OUString* pNames = aNames.getConstArray();
//STRIP001  Sequence<Any> aValues(aNames.getLength());
//STRIP001  Any* pValues = aValues.getArray();
//STRIP001
//STRIP001  const Type& rType = ::getBooleanCppuType();
//STRIP001  for(int nProp = 0; nProp < aNames.getLength(); nProp++)
//STRIP001  {
//STRIP001      sal_Int32 nVal = -1;
//STRIP001      switch(nProp)
//STRIP001      {
//STRIP001             case 0 : nVal = lcl_ConvertAttrToCfg(aInsertAttr); break;
//STRIP001          case 1 : nVal = aInsertAttr.nColor  ; break;
//STRIP001             case 2 : nVal = lcl_ConvertAttrToCfg(aDeletedAttr); break;
//STRIP001          case 3 : nVal = aDeletedAttr.nColor ; break;
//STRIP001             case 4 : nVal = lcl_ConvertAttrToCfg(aFormatAttr); break;
//STRIP001          case 5 : nVal = aFormatAttr.nColor  ; break;
//STRIP001          case 6 : nVal = nMarkAlign          ; break;
//STRIP001          case 7 : nVal = aMarkColor.GetColor(); break;
//STRIP001      }
//STRIP001      pValues[nProp] <<= nVal;
//STRIP001  }
//STRIP001  PutProperties(aNames, aValues);
//STRIP001 }
/*-- 10.10.00 16:22:56---------------------------------------------------

  -----------------------------------------------------------------------*/
/*N*/ void lcl_ConvertCfgToAttr(sal_Int32 nVal, AuthorCharAttr& rAttr, sal_Bool bDelete = sal_False)
/*N*/ {
/*N*/   rAttr.nItemId = rAttr.nAttr = 0;
/*N*/   switch(nVal)
/*N*/   {
/*N*/       case 1: rAttr.nItemId = SID_ATTR_CHAR_WEIGHT;   rAttr.nAttr = WEIGHT_BOLD              ; break;
/*?*/       case 2: rAttr.nItemId = SID_ATTR_CHAR_POSTURE;  rAttr.nAttr = ITALIC_NORMAL            ; break;
/*N*/         case 3: if(bDelete)
/*N*/                 {
/*N*/                     rAttr.nItemId = SID_ATTR_CHAR_STRIKEOUT;
/*N*/                     rAttr.nAttr = STRIKEOUT_SINGLE;
/*N*/                 }
/*N*/                 else
/*N*/                 {
/*N*/                     rAttr.nItemId = SID_ATTR_CHAR_UNDERLINE;
/*N*/                     rAttr.nAttr = UNDERLINE_SINGLE;
/*N*/                 }
/*N*/         break;
/*?*/       case 4: rAttr.nItemId = SID_ATTR_CHAR_UNDERLINE;rAttr.nAttr = UNDERLINE_DOUBLE         ; break;
/*?*/       case 5: rAttr.nItemId = SID_ATTR_CHAR_CASEMAP;  rAttr.nAttr = SVX_CASEMAP_VERSALIEN    ; break;
/*?*/       case 6: rAttr.nItemId = SID_ATTR_CHAR_CASEMAP;  rAttr.nAttr = SVX_CASEMAP_GEMEINE      ; break;
/*?*/       case 7: rAttr.nItemId = SID_ATTR_CHAR_CASEMAP;  rAttr.nAttr = SVX_CASEMAP_KAPITAELCHEN ; break;
/*?*/       case 8: rAttr.nItemId = SID_ATTR_CHAR_CASEMAP;  rAttr.nAttr = SVX_CASEMAP_TITEL        ; break;
/*?*/       case 9: rAttr.nItemId = SID_ATTR_BRUSH; break;
/*N*/   }
/*N*/ }
/*N*/ void SwRevisionConfig::Load()
/*N*/ {
/*N*/   const Sequence<OUString>& aNames = GetPropertyNames();
/*N*/   Sequence<Any> aValues = GetProperties(aNames);
/*N*/   const Any* pValues = aValues.getConstArray();
/*N*/   DBG_ASSERT(aValues.getLength() == aNames.getLength(), "GetProperties failed")
/*N*/   if(aValues.getLength() == aNames.getLength())
/*N*/   {
/*N*/       for(int nProp = 0; nProp < aNames.getLength(); nProp++)
/*N*/       {
/*N*/           if(pValues[nProp].hasValue())
/*N*/           {
/*N*/               sal_Int32 nVal;
/*N*/               pValues[nProp] >>= nVal;
/*N*/               switch(nProp)
/*N*/               {
/*N*/                   case 0 : lcl_ConvertCfgToAttr(nVal, aInsertAttr); break;
/*N*/                   case 1 : aInsertAttr.nColor     = nVal; break;
/*N*/                     case 2 : lcl_ConvertCfgToAttr(nVal, aDeletedAttr, sal_True); break;
/*N*/                   case 3 : aDeletedAttr.nColor    = nVal; break;
/*N*/                   case 4 : lcl_ConvertCfgToAttr(nVal, aFormatAttr); break;
/*N*/                   case 5 : aFormatAttr.nColor     = nVal; break;
/*N*/                   case 6 : nMarkAlign             = nVal; break;
/*N*/                   case 7 : aMarkColor.SetColor(nVal); break;
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/ }
/* -----------------------------10.10.00 16:22--------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ const Sequence<OUString>& SwInsertConfig::GetPropertyNames()
/*N*/ {
/*N*/   static Sequence<OUString> aNames;
/*N*/   static Sequence<OUString> aWebNames;
/*N*/   if(!aNames.getLength())
/*N*/   {
/*N*/       static const char* aPropNames[] =
/*N*/       {
/*N*/           "Table/Header",                                 // 0
/*N*/           "Table/RepeatHeader",                           // 1
/*N*/           "Table/Border",                                 // 2
/*N*/           "Table/Split",                                  // 3 from here not in writer/web
/*N*/           "Caption/Automatic",                            // 4
/*N*/           "Caption/WriterObject/Table/Enable",        // 5
/*N*/           "Caption/WriterObject/Table/Settings/Category",     // 6
/*N*/           "Caption/WriterObject/Table/Settings/Numbering",    // 7
/*N*/           "Caption/WriterObject/Table/Settings/CaptionText",  // 8
/*N*/           "Caption/WriterObject/Table/Settings/Delimiter",    // 9
/*N*/           "Caption/WriterObject/Table/Settings/Level",        //10
/*N*/           "Caption/WriterObject/Table/Settings/Position",     //11
/*N*/           "Caption/WriterObject/Frame/Enable",                //12
/*N*/           "Caption/WriterObject/Frame/Settings/Category",     //13
/*N*/           "Caption/WriterObject/Frame/Settings/Numbering",    //14
/*N*/           "Caption/WriterObject/Frame/Settings/CaptionText",  //15
/*N*/           "Caption/WriterObject/Frame/Settings/Delimiter",    //16
/*N*/           "Caption/WriterObject/Frame/Settings/Level",        //17
/*N*/           "Caption/WriterObject/Frame/Settings/Position",     //18
/*N*/           "Caption/WriterObject/Graphic/Enable",              //19
/*N*/           "Caption/WriterObject/Graphic/Settings/Category",   //20
/*N*/           "Caption/WriterObject/Graphic/Settings/Numbering",  //21
/*N*/           "Caption/WriterObject/Graphic/Settings/CaptionText",//22
/*N*/           "Caption/WriterObject/Graphic/Settings/Delimiter",  //23
/*N*/           "Caption/WriterObject/Graphic/Settings/Level",      //24
/*N*/           "Caption/OfficeObject/Calc/Enable",                 //25
/*N*/           "Caption/OfficeObject/Calc/Settings/Category",      //26
/*N*/           "Caption/OfficeObject/Calc/Settings/Numbering",     //27
/*N*/           "Caption/OfficeObject/Calc/Settings/CaptionText",   //28
/*N*/           "Caption/OfficeObject/Calc/Settings/Delimiter",     //29
/*N*/           "Caption/OfficeObject/Calc/Settings/Level",         //30
/*N*/           "Caption/OfficeObject/Calc/Settings/Position",      //31
/*N*/           "Caption/OfficeObject/Impress/Enable",              //32
/*N*/           "Caption/OfficeObject/Impress/Settings/Category",   //33
/*N*/           "Caption/OfficeObject/Impress/Settings/Numbering",  //34
/*N*/           "Caption/OfficeObject/Impress/Settings/CaptionText",//35
/*N*/           "Caption/OfficeObject/Impress/Settings/Delimiter",  //36
/*N*/           "Caption/OfficeObject/Impress/Settings/Level",      //37
/*N*/           "Caption/OfficeObject/Impress/Settings/Position",   //38
/*N*/           "Caption/OfficeObject/Chart/Enable",                //39
/*N*/           "Caption/OfficeObject/Chart/Settings/Category",     //40
/*N*/           "Caption/OfficeObject/Chart/Settings/Numbering",    //41
/*N*/           "Caption/OfficeObject/Chart/Settings/CaptionText",  //42
/*N*/           "Caption/OfficeObject/Chart/Settings/Delimiter",    //43
/*N*/           "Caption/OfficeObject/Chart/Settings/Level",        //44
/*N*/           "Caption/OfficeObject/Chart/Settings/Position",     //45
/*N*/           "Caption/OfficeObject/Formula/Enable",              //46
/*N*/           "Caption/OfficeObject/Formula/Settings/Category",   //47
/*N*/           "Caption/OfficeObject/Formula/Settings/Numbering",  //48
/*N*/           "Caption/OfficeObject/Formula/Settings/CaptionText",//49
/*N*/           "Caption/OfficeObject/Formula/Settings/Delimiter",  //50
/*N*/           "Caption/OfficeObject/Formula/Settings/Level",      //51
/*N*/           "Caption/OfficeObject/Formula/Settings/Position",   //52
/*N*/           "Caption/OfficeObject/Draw/Enable",                 //53
/*N*/           "Caption/OfficeObject/Draw/Settings/Category",      //54
/*N*/           "Caption/OfficeObject/Draw/Settings/Numbering",     //55
/*N*/           "Caption/OfficeObject/Draw/Settings/CaptionText",   //56
/*N*/           "Caption/OfficeObject/Draw/Settings/Delimiter",     //57
/*N*/           "Caption/OfficeObject/Draw/Settings/Level",         //58
/*N*/           "Caption/OfficeObject/Draw/Settings/Position",      //59
/*N*/           "Caption/OfficeObject/OLEMisc/Enable",              //60
/*N*/           "Caption/OfficeObject/OLEMisc/Settings/Category",   //61
/*N*/           "Caption/OfficeObject/OLEMisc/Settings/Numbering",  //62
/*N*/           "Caption/OfficeObject/OLEMisc/Settings/CaptionText",//63
/*N*/           "Caption/OfficeObject/OLEMisc/Settings/Delimiter",  //64
/*N*/           "Caption/OfficeObject/OLEMisc/Settings/Level",      //65
/*N*/           "Caption/OfficeObject/OLEMisc/Settings/Position"    //66
/*N*/       };
/*N*/       const int nCount = 67;
/*N*/       const int nWebCount = 3;
/*N*/       aNames.realloc(nCount);
/*N*/       aWebNames.realloc(nWebCount);
/*N*/       OUString* pNames = aNames.getArray();
/*N*/       OUString* pWebNames = aWebNames.getArray();
/*N*/       int i;
/*N*/       for(i = 0; i < nCount; i++)
/*N*/           pNames[i] = C2U(aPropNames[i]);
/*N*/       for(i = 0; i < nWebCount; i++)
/*N*/           pWebNames[i] = C2U(aPropNames[i]);
/*N*/   }
/*N*/   return bIsWeb ? aWebNames : aNames;
/*N*/ }
/*-- 10.10.00 16:22:22---------------------------------------------------

  -----------------------------------------------------------------------*/
/*N*/ SwInsertConfig::SwInsertConfig(sal_Bool bWeb) :
/*N*/     ConfigItem(bWeb ? C2U("Office.WriterWeb/Insert") : C2U("Office.Writer/Insert"),
/*N*/         CONFIG_MODE_DELAYED_UPDATE|CONFIG_MODE_RELEASE_TREE),
/*N*/   bIsWeb(bWeb),
/*N*/   pCapOptions(0),
/*N*/   pOLEMiscOpt(0)
/*N*/ {
/*N*/   aGlobalNames[GLOB_NAME_CALC   ] = SvGlobalName(BF_SO3_SC_CLASSID);
/*N*/   aGlobalNames[GLOB_NAME_IMPRESS] = SvGlobalName(BF_SO3_SIMPRESS_CLASSID);
/*N*/   aGlobalNames[GLOB_NAME_DRAW   ] = SvGlobalName(BF_SO3_SDRAW_CLASSID);
/*N*/   aGlobalNames[GLOB_NAME_MATH   ] = SvGlobalName(BF_SO3_SM_CLASSID);
/*N*/   aGlobalNames[GLOB_NAME_CHART  ] = SvGlobalName(BF_SO3_SCH_CLASSID);
/*N*/   if(!bIsWeb)
/*N*/       pCapOptions = new InsCaptionOptArr;
/*N*/
/*N*/     Load();
/*N*/ }
/*-- 10.10.00 16:22:23---------------------------------------------------

  -----------------------------------------------------------------------*/
/*N*/ SwInsertConfig::~SwInsertConfig()
/*N*/ {
/*N*/   delete pCapOptions;
/*N*/   delete pOLEMiscOpt;
/*N*/ }
/*-- 10.10.00 16:22:56---------------------------------------------------

  -----------------------------------------------------------------------*/
//STRIP001 void lcl_WriteOpt(const InsCaptionOpt& rOpt, Any* pValues, sal_Int32 nProp, sal_Int32 nOffset)
//STRIP001 {
//STRIP001  switch(nOffset)
//STRIP001  {
//STRIP001      case 0:
//STRIP001      {
//STRIP001          sal_Bool bTemp = rOpt.UseCaption();
//STRIP001          pValues[nProp].setValue(&bTemp, ::getBooleanCppuType());
//STRIP001      }
//STRIP001      break;//Enable
//STRIP001      case 1: pValues[nProp] <<= OUString(rOpt.GetCategory()); break;//Category
//STRIP001      case 2: pValues[nProp] <<= (sal_Int32)rOpt.GetNumType(); break;//Numbering",
//STRIP001      case 3: pValues[nProp] <<= OUString(rOpt.GetCaption());  break;//CaptionText",
//STRIP001      case 4: pValues[nProp] <<= OUString(rOpt.GetSeparator());break;//Delimiter",
//STRIP001      case 5: pValues[nProp] <<= (sal_Int32)rOpt.GetLevel();   break;//Level",
//STRIP001      case 6: pValues[nProp] <<= (sal_Int32)rOpt.GetPos();     break;//Position",
//STRIP001  }
//STRIP001 }
//-----------------------------------------------------------------------------
//STRIP001 void SwInsertConfig::Commit()
//STRIP001 {
//STRIP001  const Sequence<OUString>& aNames = GetPropertyNames();
//STRIP001  const OUString* pNames = aNames.getConstArray();
//STRIP001  Sequence<Any> aValues(aNames.getLength());
//STRIP001  Any* pValues = aValues.getArray();
//STRIP001
//STRIP001  const Type& rType = ::getBooleanCppuType();
//STRIP001  for(int nProp = 0; nProp < aNames.getLength(); nProp++)
//STRIP001  {
//STRIP001      sal_Int32 nVal = -1;
//STRIP001      const InsCaptionOpt* pWriterTableOpt = 0;
//STRIP001      const InsCaptionOpt* pWriterFrameOpt = 0;
//STRIP001      const InsCaptionOpt* pWriterGraphicOpt = 0;
//STRIP001      const InsCaptionOpt* pOLECalcOpt = 0;
//STRIP001      const InsCaptionOpt* pOLEImpressOpt = 0;
//STRIP001      const InsCaptionOpt* pOLEChartOpt = 0;
//STRIP001      const InsCaptionOpt* pOLEFormulaOpt = 0;
//STRIP001      const InsCaptionOpt* pOLEDrawOpt = 0;
//STRIP001      if(pCapOptions)
//STRIP001      {
//STRIP001          pWriterTableOpt = pCapOptions->Find(TABLE_CAP, 0);
//STRIP001          pWriterFrameOpt = pCapOptions->Find(FRAME_CAP, 0);
//STRIP001          pWriterGraphicOpt = pCapOptions->Find(GRAPHIC_CAP, 0);
//STRIP001          pOLECalcOpt = pCapOptions->Find(OLE_CAP, &aGlobalNames[GLOB_NAME_CALC]);
//STRIP001          pOLEImpressOpt = pCapOptions->Find(OLE_CAP, &aGlobalNames[GLOB_NAME_IMPRESS]);
//STRIP001          pOLEDrawOpt = pCapOptions->Find(OLE_CAP, &aGlobalNames[GLOB_NAME_DRAW   ]);
//STRIP001          pOLEFormulaOpt = pCapOptions->Find(OLE_CAP, &aGlobalNames[GLOB_NAME_MATH   ]);
//STRIP001          pOLEChartOpt = pCapOptions->Find(OLE_CAP, &aGlobalNames[GLOB_NAME_CHART  ]);
//STRIP001      }
//STRIP001      switch(nProp)
//STRIP001      {
//STRIP001          case  0:
//STRIP001          {
//STRIP001              sal_Bool bVal = 0 !=(nInsTblFlags&HEADLINE); pValues[nProp].setValue(&bVal, rType);
//STRIP001          }
//STRIP001          break;//"Table/Header",
//STRIP001          case  1:
//STRIP001          {
//STRIP001              sal_Bool bVal = 0 !=(nInsTblFlags&REPEAT); pValues[nProp].setValue(&bVal, rType);
//STRIP001          }
//STRIP001          break;//"Table/RepeatHeader",
//STRIP001          case  2:
//STRIP001          {
//STRIP001              sal_Bool bVal = 0 !=(nInsTblFlags&DEFAULT_BORDER ); pValues[nProp].setValue(&bVal, rType);
//STRIP001          }
//STRIP001          break;//"Table/Border",
//STRIP001          case  3:
//STRIP001          {
//STRIP001              sal_Bool bVal = 0 !=(nInsTblFlags&SPLIT_LAYOUT); pValues[nProp].setValue(&bVal, rType);
//STRIP001          }
//STRIP001          break;//"Table/Split",
//STRIP001          case  4: pValues[nProp].setValue(&bInsWithCaption, rType);break;//"Caption/Automatic",
//STRIP001
//STRIP001          case  5: case  6: case  7: case  8: case  9: case 10: case 11: //"Caption/WriterObject/Table/Position",
//STRIP001                  if(pWriterTableOpt)
//STRIP001                      lcl_WriteOpt(*pWriterTableOpt, pValues, nProp, nProp - 5);
//STRIP001          break;
//STRIP001          case 12: case 13: case 14: case 15: case 16: case 17: case 18:
//STRIP001                  if(pWriterFrameOpt)
//STRIP001                      lcl_WriteOpt(*pWriterFrameOpt, pValues, nProp, nProp - 12);
//STRIP001          case 19: case 20: case 21: case 22: case 23: case 24:
//STRIP001                  if(pWriterGraphicOpt)
//STRIP001                      lcl_WriteOpt(*pWriterGraphicOpt, pValues, nProp, nProp - 19);
//STRIP001                  break;
//STRIP001          case 25: case 26: case 27: case 28: case 29: case 30: case 31:
//STRIP001                  if(pOLECalcOpt)
//STRIP001                      lcl_WriteOpt(*pOLECalcOpt, pValues, nProp, nProp - 25);
//STRIP001          break;
//STRIP001          case 32: case 33: case 34: case 35: case 36: case 37: case 38:
//STRIP001                  if(pOLEImpressOpt)
//STRIP001                      lcl_WriteOpt(*pOLEImpressOpt, pValues, nProp, nProp - 32);
//STRIP001          break;
//STRIP001          case 39: case 40: case 41: case 42: case 43: case 44: case 45:
//STRIP001                  if(pOLEChartOpt)
//STRIP001                      lcl_WriteOpt(*pOLEChartOpt, pValues, nProp, nProp - 39);
//STRIP001          break;
//STRIP001          case 46: case 47: case 48: case 49: case 50: case 51: case 52:
//STRIP001                  if(pOLEFormulaOpt)
//STRIP001                      lcl_WriteOpt(*pOLEFormulaOpt, pValues, nProp, nProp - 46);
//STRIP001          break;
//STRIP001          case 53: case 54:   case 55: case 56: case 57: case 58: case 59:
//STRIP001                  if(pOLEDrawOpt)
//STRIP001                      lcl_WriteOpt(*pOLEDrawOpt, pValues, nProp, nProp - 53);
//STRIP001          break;
//STRIP001          case 60: case 61: case 62: case 63: case 64: case 65: case 66:
//STRIP001                  if(pOLEMiscOpt)
//STRIP001                      lcl_WriteOpt(*pOLEMiscOpt, pValues, nProp, nProp - 60);
//STRIP001          break;
//STRIP001
//STRIP001      }
//STRIP001  }
//STRIP001  PutProperties(aNames, aValues);
//STRIP001 }
/*-- 10.10.00 16:22:56---------------------------------------------------

  -----------------------------------------------------------------------*/
/*N*/ void lcl_ReadOpt(InsCaptionOpt& rOpt, const Any* pValues, sal_Int32 nProp, sal_Int32 nOffset)
/*N*/ {
/*N*/   switch(nOffset)
/*N*/   {
/*N*/       case 0:
/*N*/           rOpt.UseCaption() = *(sal_Bool*)pValues[nProp].getValue();
/*N*/       break;//Enable
/*N*/       case 1:
/*N*/       {
/*N*/           OUString sTemp; pValues[nProp] >>= sTemp;
/*N*/           rOpt.SetCategory(sTemp);
/*N*/       }
/*N*/       break;//Category
/*N*/       case 2:
/*N*/       {
/*N*/           sal_Int32 nTemp;  pValues[nProp] >>= nTemp;
/*N*/           rOpt.SetNumType(nTemp);
/*N*/       }
/*N*/       break;//Numbering",
/*N*/       case 3:
/*N*/       {
/*N*/           OUString sTemp; pValues[nProp] >>= sTemp;
/*N*/           rOpt.SetCaption(sTemp);
/*N*/       }
/*N*/       break;//CaptionText",
/*N*/       case 4:
/*N*/       {
/*N*/           OUString sTemp; pValues[nProp] >>= sTemp;
/*N*/           if(sTemp.getLength())
/*N*/               rOpt.SetSeparator(sTemp[0]);
/*N*/       }
/*N*/       break;//Delimiter",
/*N*/       case 5:
/*N*/       {
/*N*/           sal_Int32 nTemp;  pValues[nProp] >>= nTemp;
/*N*/           rOpt.SetLevel(nTemp);
/*N*/       }
/*N*/       break;//Level",
/*N*/       case 6:
/*N*/       {
/*N*/           sal_Int32 nTemp;  pValues[nProp] >>= nTemp;
/*N*/           rOpt.SetPos(nTemp);
/*N*/       }
/*N*/       break;//Position",
/*N*/   }
/*N*/ }
//-----------------------------------------------------------------------------
/*N*/ void SwInsertConfig::Load()
/*N*/ {
/*N*/   const Sequence<OUString>& aNames = GetPropertyNames();
/*N*/   Sequence<Any> aValues = GetProperties(aNames);
/*N*/   const Any* pValues = aValues.getConstArray();
/*N*/   DBG_ASSERT(aValues.getLength() == aNames.getLength(), "GetProperties failed")
/*N*/   if(aValues.getLength() == aNames.getLength())
/*N*/   {
/*N*/       InsCaptionOpt* pWriterTableOpt = 0;
/*N*/       InsCaptionOpt* pWriterFrameOpt = 0;
/*N*/       InsCaptionOpt* pWriterGraphicOpt = 0;
/*N*/       InsCaptionOpt* pOLECalcOpt = 0;
/*N*/       InsCaptionOpt* pOLEImpressOpt = 0;
/*N*/       InsCaptionOpt* pOLEChartOpt = 0;
/*N*/       InsCaptionOpt* pOLEFormulaOpt = 0;
/*N*/       InsCaptionOpt* pOLEDrawOpt = 0;
/*N*/       if(pCapOptions)
/*N*/       {
/*N*/           pWriterTableOpt = pCapOptions->Find(TABLE_CAP, 0);
/*N*/           pWriterFrameOpt = pCapOptions->Find(FRAME_CAP, 0);
/*N*/           pWriterGraphicOpt = pCapOptions->Find(GRAPHIC_CAP, 0);
/*N*/           pOLECalcOpt = pCapOptions->Find(OLE_CAP, &aGlobalNames[GLOB_NAME_CALC]);
/*N*/           pOLEImpressOpt = pCapOptions->Find(OLE_CAP, &aGlobalNames[GLOB_NAME_IMPRESS]);
/*N*/           pOLEDrawOpt = pCapOptions->Find(OLE_CAP, &aGlobalNames[GLOB_NAME_DRAW   ]);
/*N*/           pOLEFormulaOpt = pCapOptions->Find(OLE_CAP, &aGlobalNames[GLOB_NAME_MATH   ]);
/*N*/           pOLEChartOpt = pCapOptions->Find(OLE_CAP, &aGlobalNames[GLOB_NAME_CHART  ]);
/*N*/       }
/*N*/       else if(!bIsWeb)
/*?*/           return;
/*N*/
/*N*/       nInsTblFlags = 0;
/*N*/       for(int nProp = 0; nProp < aNames.getLength(); nProp++)
/*N*/       {
/*N*/           if(pValues[nProp].hasValue())
/*N*/           {
/*N*/                 sal_Bool bBool = nProp < 5 ? *(sal_Bool*)pValues[nProp].getValue() : sal_False;
/*N*/                 switch(nProp)
/*N*/               {
/*N*/                   case  0:
/*N*/                   {
/*N*/                         if(bBool)
/*N*/                           nInsTblFlags|= HEADLINE;
/*N*/                   }
/*N*/                   break;//"Table/Header",
/*N*/                   case  1:
/*N*/                   {
/*N*/                         if(bBool)
/*N*/                           nInsTblFlags|= REPEAT;
/*N*/                   }
/*N*/                   break;//"Table/RepeatHeader",
/*N*/                   case  2:
/*N*/                   {
/*N*/                         if(bBool)
/*N*/                           nInsTblFlags|= DEFAULT_BORDER;
/*N*/                   }
/*N*/                   break;//"Table/Border",
/*N*/                   case  3:
/*N*/                   {
/*N*/                         if(bBool)
/*N*/                           nInsTblFlags|= SPLIT_LAYOUT;
/*N*/                   }
/*N*/                   break;//"Table/Split",
/*N*/                   case 4:
/*N*/                         bInsWithCaption = bBool;
/*N*/                   break;
/*N*/                   case  5: case  6: case  7: case  8: case  9: case 10: case 11:
/*N*/                       if(!pWriterTableOpt)
/*N*/                       {
/*N*/                           pWriterTableOpt = new InsCaptionOpt(TABLE_CAP);
/*N*/                           pCapOptions->Insert(pWriterTableOpt);
/*N*/                       }
/*N*/                       lcl_ReadOpt(*pWriterTableOpt, pValues, nProp, nProp - 5);
/*N*/                   break;
/*N*/                   case 12: case 13: case 14: case 15: case 16: case 17: case 18:
/*N*/                       if(!pWriterFrameOpt)
/*N*/                       {
/*N*/                           pWriterFrameOpt = new InsCaptionOpt(FRAME_CAP);
/*N*/                           pCapOptions->Insert(pWriterFrameOpt);
/*N*/                       }
/*N*/                       lcl_ReadOpt(*pWriterFrameOpt, pValues, nProp, nProp - 12);
/*N*/                   case 19: case 20: case 21:case 22: case 23: case 24:
/*N*/                       if(!pWriterGraphicOpt)
/*N*/                       {
/*N*/                           pWriterGraphicOpt = new InsCaptionOpt(GRAPHIC_CAP);
/*N*/                           pCapOptions->Insert(pWriterGraphicOpt);
/*N*/                       }
/*N*/                       lcl_ReadOpt(*pWriterGraphicOpt, pValues, nProp, nProp - 19);
/*N*/                       break;
/*N*/                   case 25: case 26: case 27: case 28: case 29: case 30: case 31:
/*N*/                       if(!pOLECalcOpt)
/*N*/                       {
/*N*/                           pOLECalcOpt = new InsCaptionOpt(OLE_CAP, &aGlobalNames[GLOB_NAME_CALC]);
/*N*/                           pCapOptions->Insert(pOLECalcOpt);
/*N*/                       }
/*N*/                       lcl_ReadOpt(*pOLECalcOpt, pValues, nProp, nProp - 25);
/*N*/                   break;
/*N*/                   case 32: case 33: case 34: case 35: case 36: case 37: case 38:
/*N*/                       if(!pOLEImpressOpt)
/*N*/                       {
/*N*/                           pOLEImpressOpt = new InsCaptionOpt(OLE_CAP, &aGlobalNames[GLOB_NAME_IMPRESS]);
/*N*/                           pCapOptions->Insert(pOLEImpressOpt);
/*N*/                       }
/*N*/                       lcl_ReadOpt(*pOLEImpressOpt, pValues, nProp, nProp - 32);
/*N*/                   break;
/*N*/                   case 39: case 40: case 41: case 42: case 43: case 44: case 45:
/*N*/                       if(!pOLEChartOpt)
/*N*/                       {
/*N*/                           pOLEChartOpt = new InsCaptionOpt(OLE_CAP, &aGlobalNames[GLOB_NAME_CHART]);
/*N*/                           pCapOptions->Insert(pOLEChartOpt);
/*N*/                       }
/*N*/                       lcl_ReadOpt(*pOLEChartOpt, pValues, nProp, nProp - 39);
/*N*/                   break;
/*N*/                   case 46: case 47: case 48: case 49: case 50: case 51: case 52:
/*N*/                       if(!pOLEFormulaOpt)
/*N*/                       {
/*N*/                           pOLEFormulaOpt = new InsCaptionOpt(OLE_CAP, &aGlobalNames[GLOB_NAME_MATH]);
/*N*/                           pCapOptions->Insert(pOLEFormulaOpt);
/*N*/                       }
/*N*/                       lcl_ReadOpt(*pOLEFormulaOpt, pValues, nProp, nProp - 46);
/*N*/                   break;
/*N*/                   case 53: case 54:   case 55: case 56: case 57: case 58: case 59:
/*N*/                       if(!pOLEDrawOpt)
/*N*/                       {
/*N*/                           pOLEDrawOpt = new InsCaptionOpt(OLE_CAP, &aGlobalNames[GLOB_NAME_DRAW]);
/*N*/                           pCapOptions->Insert(pOLEDrawOpt);
/*N*/                       }
/*N*/                         lcl_ReadOpt(*pOLEDrawOpt, pValues, nProp, nProp - 53);
/*N*/                   break;
/*N*/                   case 60: case 61: case 62: case 63: case 64: case 65: case 66:
/*N*/                       if(!pOLEMiscOpt)
/*N*/                       {
/*N*/                           pOLEMiscOpt = new InsCaptionOpt(OLE_CAP);
/*N*/                       }
/*N*/                       lcl_ReadOpt(*pOLEMiscOpt, pValues, nProp, nProp - 60);
/*N*/                   break;
/*N*/
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/ }
/* -----------------------------10.10.00 16:22--------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ const Sequence<OUString>& SwTableConfig::GetPropertyNames()
/*N*/ {
/*N*/   const int nCount = 8;
/*N*/   static Sequence<OUString> aNames(nCount);
/*N*/   static const char* aPropNames[] =
/*N*/   {
/*N*/       "Shift/Row",                    //  0
/*N*/       "Shift/Column",                 //  1
/*N*/       "Insert/Row",                   //  2
/*N*/       "Insert/Column",                //  3
/*N*/       "Change/Effect",                //  4
/*N*/       "Input/NumberRecognition",      //  5
/*N*/       "Input/NumberFormatRecognition",//  6
/*N*/       "Input/Alignment"               //  7
/*N*/   };
/*N*/   OUString* pNames = aNames.getArray();
/*N*/   for(int i = 0; i < nCount; i++)
/*N*/       pNames[i] = OUString::createFromAscii(aPropNames[i]);
/*N*/   return aNames;
/*N*/ }
/*-- 10.10.00 16:22:22---------------------------------------------------

  -----------------------------------------------------------------------*/
/*N*/ SwTableConfig::SwTableConfig(sal_Bool bWeb) :
/*N*/     ConfigItem(bWeb ? C2U("Office.WriterWeb/Table") : C2U("Office.Writer/Table"),
/*N*/         CONFIG_MODE_DELAYED_UPDATE|CONFIG_MODE_RELEASE_TREE)
/*N*/ {
/*N*/     Load();
/*N*/ }
/*-- 10.10.00 16:22:23---------------------------------------------------

  -----------------------------------------------------------------------*/
/*N*/ SwTableConfig::~SwTableConfig()
/*N*/ {
/*N*/ }
/*-- 10.10.00 16:22:56---------------------------------------------------

  -----------------------------------------------------------------------*/
//STRIP001 void SwTableConfig::Commit()
//STRIP001 {
//STRIP001  const Sequence<OUString>& aNames = GetPropertyNames();
//STRIP001  const OUString* pNames = aNames.getConstArray();
//STRIP001  Sequence<Any> aValues(aNames.getLength());
//STRIP001  Any* pValues = aValues.getArray();
//STRIP001
//STRIP001  const Type& rType = ::getBooleanCppuType();
//STRIP001  for(int nProp = 0; nProp < aNames.getLength(); nProp++)
//STRIP001  {
//STRIP001      switch(nProp)
//STRIP001      {
//STRIP001          case 0 : pValues[nProp] <<= (sal_Int32)TWIP_TO_MM100(nTblHMove); break;  //"Shift/Row",
//STRIP001          case 1 : pValues[nProp] <<= (sal_Int32)TWIP_TO_MM100(nTblVMove); break;     //"Shift/Column",
//STRIP001          case 2 : pValues[nProp] <<= (sal_Int32)TWIP_TO_MM100(nTblHInsert); break;   //"Insert/Row",
//STRIP001          case 3 : pValues[nProp] <<= (sal_Int32)TWIP_TO_MM100(nTblVInsert); break;   //"Insert/Column",
//STRIP001          case 4 : pValues[nProp] <<= (sal_Int32)eTblChgMode; break;   //"Change/Effect",
//STRIP001          case 5 : pValues[nProp].setValue(&bInsTblFormatNum, rType); break;  //"Input/NumberRecognition",
//STRIP001          case 6 : pValues[nProp].setValue(&bInsTblChangeNumFormat, rType); break;  //"Input/NumberFormatRecognition",
//STRIP001          case 7 : pValues[nProp].setValue(&bInsTblAlignNum, rType); break;  //"Input/Alignment"
//STRIP001      }
//STRIP001  }
//STRIP001  PutProperties(aNames, aValues);
//STRIP001 }
/*-- 10.10.00 16:22:56---------------------------------------------------

  -----------------------------------------------------------------------*/
/*N*/ void SwTableConfig::Load()
/*N*/ {
/*N*/   const Sequence<OUString>& aNames = GetPropertyNames();
/*N*/   Sequence<Any> aValues = GetProperties(aNames);
/*N*/   const Any* pValues = aValues.getConstArray();
/*N*/   DBG_ASSERT(aValues.getLength() == aNames.getLength(), "GetProperties failed")
/*N*/   if(aValues.getLength() == aNames.getLength())
/*N*/   {
/*N*/       for(int nProp = 0; nProp < aNames.getLength(); nProp++)
/*N*/       {
/*N*/           if(pValues[nProp].hasValue())
/*N*/           {
/*N*/               sal_Int32 nTemp;
/*N*/               switch(nProp)
/*N*/               {
/*N*/                   case 0 : pValues[nProp] >>= nTemp; nTblHMove = (USHORT)MM100_TO_TWIP(nTemp); break;  //"Shift/Row",
/*N*/                   case 1 : pValues[nProp] >>= nTemp; nTblVMove = (USHORT)MM100_TO_TWIP(nTemp); break;     //"Shift/Column",
/*N*/                   case 2 : pValues[nProp] >>= nTemp; nTblHInsert = (USHORT)MM100_TO_TWIP(nTemp); break;   //"Insert/Row",
/*N*/                   case 3 : pValues[nProp] >>= nTemp; nTblVInsert = (USHORT)MM100_TO_TWIP(nTemp); break;   //"Insert/Column",
/*N*/                   case 4 : pValues[nProp] >>= nTemp; eTblChgMode = (TblChgMode)nTemp; break;   //"Change/Effect",
/*N*/                   case 5 : bInsTblFormatNum = *(sal_Bool*)pValues[nProp].getValue();  break;  //"Input/NumberRecognition",
/*N*/                   case 6 : bInsTblChangeNumFormat = *(sal_Bool*)pValues[nProp].getValue(); break;  //"Input/NumberFormatRecognition",
/*N*/                   case 7 : bInsTblAlignNum = *(sal_Bool*)pValues[nProp].getValue(); break;  //"Input/Alignment"
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/ }
/*-- 18.01.01 17:02:47---------------------------------------------------

  -----------------------------------------------------------------------*/
/*N*/ SwMiscConfig::SwMiscConfig() :
/*N*/     ConfigItem(C2U("Office.Writer"),
/*N*/         CONFIG_MODE_DELAYED_UPDATE|CONFIG_MODE_RELEASE_TREE),
/*N*/   bDefaultFontsInCurrDocOnly(sal_False),
/*N*/   bShowIndexPreview(sal_False),
/*N*/   bGrfToGalleryAsLnk(sal_True),
/*N*/   bNumAlignSize(sal_True),
/*N*/   bSinglePrintJob(sal_False),
/*N*/   bIsNameFromColumn(sal_True),
/*N*/   nMailingFormats(0)
/*N*/ {
/*N*/     Load();
/*N*/ }
/*-- 18.01.01 17:02:47---------------------------------------------------

  -----------------------------------------------------------------------*/
/*N*/ SwMiscConfig::~SwMiscConfig()
/*N*/ {
/*N*/ }
/*-- 18.01.01 17:02:47---------------------------------------------------

  -----------------------------------------------------------------------*/
/*N*/ const Sequence<OUString>& SwMiscConfig::GetPropertyNames()
/*N*/ {
/*N*/   static Sequence<OUString> aNames;
/*N*/   if(!aNames.getLength())
/*N*/   {
/*N*/       const int nCount = 11;
/*N*/       aNames.realloc(nCount);
/*N*/       static const char* aPropNames[] =
/*N*/       {
/*N*/           "Statistics/WordNumber/Delimiter",          // 0
/*N*/           "DefaultFont/Document",                     // 1
/*N*/           "Index/ShowPreview",                        // 2
/*N*/           "Misc/GraphicToGalleryAsLink",              // 3
/*N*/           "Numbering/Graphic/KeepRatio",              // 4
/*N*/           "FormLetter/PrintOutput/SinglePrintJobs",   // 5
/*N*/           "FormLetter/MailingOutput/Format",          // 6
/*N*/           "FormLetter/FileOutput/FileName/FromDatabaseField",  // 7
/*N*/           "FormLetter/FileOutput/Path",               // 8
/*N*/           "FormLetter/FileOutput/FileName/FromManualSetting",   // 9
/*N*/           "FormLetter/FileOutput/FileName/Generation"//10
/*N*/       };
/*N*/       OUString* pNames = aNames.getArray();
/*N*/       for(int i = 0; i < nCount; i++)
/*N*/           pNames[i] = C2U(aPropNames[i]);
/*N*/   }
/*N*/   return aNames;
/*N*/ }
/*-- 18.01.01 17:02:47---------------------------------------------------

  -----------------------------------------------------------------------*/
//STRIP001 void SwMiscConfig::Commit()
//STRIP001 {
//STRIP001  const Sequence<OUString>& aNames = GetPropertyNames();
//STRIP001  const OUString* pNames = aNames.getConstArray();
//STRIP001  Sequence<Any> aValues(aNames.getLength());
//STRIP001  Any* pValues = aValues.getArray();
//STRIP001
//STRIP001  const Type& rType = ::getBooleanCppuType();
//STRIP001  for(int nProp = 0; nProp < aNames.getLength(); nProp++)
//STRIP001  {
//STRIP001      switch(nProp)
//STRIP001      {
//STRIP001          case 0 :
//STRIP001              pValues[nProp] <<= OUString(
//STRIP001                  SwModuleOptions::ConvertWordDelimiter(sWordDelimiter, sal_False));
//STRIP001          break;
//STRIP001          case 1 : pValues[nProp].setValue(&bDefaultFontsInCurrDocOnly, rType); break;
//STRIP001          case 2 : pValues[nProp].setValue(&bShowIndexPreview, rType) ;        break;
//STRIP001          case 3 : pValues[nProp].setValue(&bGrfToGalleryAsLnk, rType);        break;
//STRIP001          case 4 : pValues[nProp].setValue(&bNumAlignSize, rType);            break;
//STRIP001          case 5 : pValues[nProp].setValue(&bSinglePrintJob, rType);          break;
//STRIP001          case 6 : pValues[nProp] <<= nMailingFormats;             break;
//STRIP001          case 7 : pValues[nProp] <<= OUString(sNameFromColumn);  break;
//STRIP001          case 8 : pValues[nProp] <<= OUString(sMailingPath);     break;
//STRIP001          case 9 : pValues[nProp] <<= OUString(sMailName);        break;
//STRIP001          case 10: pValues[nProp].setValue(&bIsNameFromColumn, rType);break;
//STRIP001      }
//STRIP001  }
//STRIP001  PutProperties(aNames, aValues);
//STRIP001 }
/*-- 18.01.01 17:02:48---------------------------------------------------

  -----------------------------------------------------------------------*/
/*N*/ void SwMiscConfig::Load()
/*N*/ {
/*N*/   const Sequence<OUString>& aNames = GetPropertyNames();
/*N*/   Sequence<Any> aValues = GetProperties(aNames);
/*N*/   const Any* pValues = aValues.getConstArray();
/*N*/   DBG_ASSERT(aValues.getLength() == aNames.getLength(), "GetProperties failed")
/*N*/   if(aValues.getLength() == aNames.getLength())
/*N*/   {
/*N*/       OUString sTmp;
/*N*/       for(int nProp = 0; nProp < aNames.getLength(); nProp++)
/*N*/       {
/*N*/           if(pValues[nProp].hasValue())
/*N*/           {
/*N*/               switch(nProp)
/*N*/               {
/*N*/                   case 0 : pValues[nProp] >>= sTmp;
/*N*/                       sWordDelimiter = SwModuleOptions::ConvertWordDelimiter(sTmp, sal_True);
/*N*/                   break;
/*N*/                   case 1 : bDefaultFontsInCurrDocOnly = *(sal_Bool*)pValues[nProp].getValue(); break;
/*N*/                   case 2 : bShowIndexPreview = *(sal_Bool*)pValues[nProp].getValue(); break;
/*N*/                   case 3 : bGrfToGalleryAsLnk = *(sal_Bool*)pValues[nProp].getValue(); break;
/*N*/                   case 4 : bNumAlignSize = *(sal_Bool*)pValues[nProp].getValue(); break;
/*N*/                   case 5 : bSinglePrintJob = *(sal_Bool*)pValues[nProp].getValue(); break;
/*?*/                   case 6 : pValues[nProp] >>= nMailingFormats;              ; break;
/*?*/                   case 7 : pValues[nProp] >>= sTmp; sNameFromColumn = sTmp; break;
/*N*/                   case 8 : pValues[nProp] >>= sTmp; sMailingPath = sTmp;  break;
/*?*/                   case 9 : pValues[nProp] >>= sTmp; sMailName = sTmp;     break;
/*?*/                   case 10: bIsNameFromColumn = *(sal_Bool*)pValues[nProp].getValue(); break;
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/ }
}
