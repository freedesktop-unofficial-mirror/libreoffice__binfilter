/*************************************************************************
 *
 *  $RCSfile: sw_envimg.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2004-05-05 16:41:18 $
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

#ifndef _STREAM_HXX //autogen
#include <tools/stream.hxx>
#endif
#ifndef _TOOLS_RESID_HXX //autogen
#include <tools/resid.hxx>
#endif
#ifndef _SFXAPP_HXX //autogen
#include <bf_sfx2/app.hxx>
#endif
#ifndef _SVX_PAPERINF_HXX //autogen
#include <bf_svx/paperinf.hxx>
#endif
#ifndef _SVX_ADRITEM_HXX //autogen
#include <bf_svx/adritem.hxx>
#endif
#ifndef _COM_SUN_STAR_UNO_SEQUENCE_HXX_
#include <com/sun/star/uno/Sequence.hxx>
#endif

#ifndef _ERRHDL_HXX
#include <errhdl.hxx>
#endif
#ifndef _SWTYPES_HXX
#include <swtypes.hxx>
#endif
#ifndef _ENVIMG_HXX
#include <envimg.hxx>
#endif

#ifndef _CMDID_H
#include <cmdid.h>
#endif
#ifndef _ENVELP_HRC
#include <envelp.hrc>
#endif
namespace binfilter {

#ifdef WIN
#define NEXTLINE  UniString::CreateFromAscii("\r\n")
#else
#define NEXTLINE  '\n'
#endif

using namespace utl;
using namespace rtl;
using namespace ::com::sun::star::uno;

#define C2U(cChar) OUString::createFromAscii(cChar)

/*N*/ TYPEINIT1_AUTOFACTORY( SwEnvItem, SfxPoolItem );

// --------------------------------------------------------------------------
//STRIP001 String MakeSender()
//STRIP001 {
//STRIP001  SvxAddressItem aAdr;
//STRIP001
//STRIP001  String sRet;
//STRIP001  String sSenderToken(SW_RES(STR_SENDER_TOKENS));
//STRIP001  xub_StrLen nSttPos = 0, nTokenCount = sSenderToken.GetTokenCount(';');
//STRIP001  BOOL bLastLength = TRUE;
//STRIP001  for( xub_StrLen i = 0; i < nTokenCount; i++ )
//STRIP001  {
//STRIP001      String sToken = sSenderToken.GetToken( 0, ';', nSttPos );
//STRIP001      if(sToken.EqualsAscii("COMPANY"))
//STRIP001      {
//STRIP001          xub_StrLen nOldLen = sRet.Len();
//STRIP001          sRet += aAdr.GetToken( POS_COMPANY );
//STRIP001          bLastLength = sRet.Len() != nOldLen;
//STRIP001      }
//STRIP001      else if(sToken.EqualsAscii("CR"))
//STRIP001      {
//STRIP001          if(bLastLength)
//STRIP001              sRet +=NEXTLINE;
//STRIP001          bLastLength = TRUE;
//STRIP001      }
//STRIP001      else if(sToken.EqualsAscii("FIRSTNAME"))
//STRIP001          sRet += aAdr.GetFirstName();
//STRIP001      else if(sToken.EqualsAscii("LASTNAME"))
//STRIP001          sRet += aAdr.GetName();
//STRIP001      else if(sToken.EqualsAscii("ADDRESS"))
//STRIP001          sRet += aAdr.GetToken( POS_STREET );
//STRIP001      else if(sToken.EqualsAscii("COUNTRY"))
//STRIP001          sRet += aAdr.GetToken( POS_COUNTRY );
//STRIP001      else if(sToken.EqualsAscii("POSTALCODE"))
//STRIP001          sRet += aAdr.GetToken( POS_PLZ );
//STRIP001      else if(sToken.EqualsAscii("CITY"))
//STRIP001          sRet += aAdr.GetToken( POS_CITY );
//STRIP001      else if(sToken.EqualsAscii("STATEPROV"))
//STRIP001          sRet += aAdr.GetToken( POS_STATE );
//STRIP001      else if(sToken.Len()) //spaces
//STRIP001          sRet += sToken;
//STRIP001  }
//STRIP001  return sRet;
//STRIP001 }
// --------------------------------------------------------------------------
/*N*/ SwEnvItem::SwEnvItem() :
/*N*/   SfxPoolItem(FN_ENVELOP)
/*N*/ {
/*N*/ DBG_BF_ASSERT(0, "STRIP"); //STRIP001     aAddrText       = aEmptyStr;
//STRIP001  bSend           = TRUE;
//STRIP001  aSendText       = MakeSender();
//STRIP001  lSendFromLeft   = 566; // 1 cm
//STRIP001  lSendFromTop    = 566; // 1 cm
//STRIP001  lWidth          = lC65Width;
//STRIP001  lHeight         = lC65Height;
//STRIP001  eAlign          = ENV_HOR_LEFT;
//STRIP001  bPrintFromAbove = TRUE;
//STRIP001  lShiftRight     = 0;
//STRIP001  lShiftDown      = 0;
//STRIP001
//STRIP001  lAddrFromLeft   = Max(lWidth, lHeight) / 2;
//STRIP001  lAddrFromTop    = Min(lWidth, lHeight) / 2;
/*N*/ }
// --------------------------------------------------------------------------
/*N*/ SwEnvItem::SwEnvItem(const SwEnvItem& rItem) :
/*N*/   SfxPoolItem(FN_ENVELOP),
/*N*/   aAddrText      (rItem.aAddrText),
/*N*/   bSend          (rItem.bSend),
/*N*/   aSendText      (rItem.aSendText),
/*N*/   lSendFromLeft  (rItem.lSendFromLeft),
/*N*/   lSendFromTop   (rItem.lSendFromTop),
/*N*/   lAddrFromLeft  (rItem.lAddrFromLeft),
/*N*/   lAddrFromTop   (rItem.lAddrFromTop),
/*N*/   lWidth         (rItem.lWidth),
/*N*/   lHeight        (rItem.lHeight),
/*N*/   eAlign         (rItem.eAlign),
/*N*/   bPrintFromAbove(rItem.bPrintFromAbove),
/*N*/   lShiftRight    (rItem.lShiftRight),
/*N*/   lShiftDown     (rItem.lShiftDown)
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/ }

// --------------------------------------------------------------------------
//STRIP001 SwEnvItem& SwEnvItem::operator =(const SwEnvItem& rItem)
//STRIP001 {
//STRIP001  aAddrText       = rItem.aAddrText;
//STRIP001  bSend           = rItem.bSend;
//STRIP001  aSendText       = rItem.aSendText;
//STRIP001  lSendFromLeft   = rItem.lSendFromLeft;
//STRIP001  lSendFromTop    = rItem.lSendFromTop;
//STRIP001  lAddrFromLeft   = rItem.lAddrFromLeft;
//STRIP001  lAddrFromTop    = rItem.lAddrFromTop;
//STRIP001  lWidth          = rItem.lWidth;
//STRIP001  lHeight         = rItem.lHeight;
//STRIP001  eAlign          = rItem.eAlign;
//STRIP001  bPrintFromAbove = rItem.bPrintFromAbove;
//STRIP001  lShiftRight     = rItem.lShiftRight;
//STRIP001  lShiftDown      = rItem.lShiftDown;
//STRIP001  return *this;
//STRIP001 }
// --------------------------------------------------------------------------
/*N*/ int SwEnvItem::operator ==(const SfxPoolItem& rItem) const
/*N*/ {
DBG_BF_ASSERT(0, "STRIP"); return 0;//STRIP001  const SwEnvItem& rEnv = (const SwEnvItem&) rItem;
//STRIP001
//STRIP001  return aAddrText       == rEnv.aAddrText       &&
//STRIP001         bSend           == rEnv.bSend           &&
//STRIP001         aSendText       == rEnv.aSendText       &&
//STRIP001         lSendFromLeft   == rEnv.lSendFromLeft   &&
//STRIP001         lSendFromTop    == rEnv.lSendFromTop    &&
//STRIP001         lAddrFromLeft   == rEnv.lAddrFromLeft   &&
//STRIP001         lAddrFromTop    == rEnv.lAddrFromTop    &&
//STRIP001         lWidth          == rEnv.lWidth          &&
//STRIP001         lHeight         == rEnv.lHeight         &&
//STRIP001         eAlign          == rEnv.eAlign          &&
//STRIP001         bPrintFromAbove == rEnv.bPrintFromAbove &&
//STRIP001         lShiftRight     == rEnv.lShiftRight     &&
//STRIP001         lShiftDown      == rEnv.lShiftDown;
/*N*/ }

// --------------------------------------------------------------------------
/*N*/ SfxPoolItem* SwEnvItem::Clone(SfxItemPool*) const
/*N*/ {
/*N*/   return new SwEnvItem(*this);
/*N*/ }
// --------------------------------------------------------------------------
// --------------------------------------------------------------------------
//STRIP001 SwEnvCfgItem::SwEnvCfgItem() :
//STRIP001  ConfigItem(C2U("Office.Writer/Envelope"))
//STRIP001 {
//STRIP001  Sequence<OUString> aNames = GetPropertyNames();
//STRIP001  Sequence<Any> aValues = GetProperties(aNames);
//STRIP001  EnableNotification(aNames);
//STRIP001  const Any* pValues = aValues.getConstArray();
//STRIP001  DBG_ASSERT(aValues.getLength() == aNames.getLength(), "GetProperties failed")
//STRIP001  if(aValues.getLength() == aNames.getLength())
//STRIP001  {
//STRIP001      for(int nProp = 0; nProp < aNames.getLength(); nProp++)
//STRIP001      {
//STRIP001          if(pValues[nProp].hasValue())
//STRIP001          {
//STRIP001              switch(nProp)
//STRIP001              {
//STRIP001                  case  0: pValues[nProp] >>= aEnvItem.aAddrText; break;// "Inscription/Addressee",
//STRIP001                  case  1: pValues[nProp] >>= aEnvItem.aSendText; break;// "Inscription/Sender",
//STRIP001                  case  2: aEnvItem.bSend = *(sal_Bool*)pValues[nProp].getValue(); break;// "Inscription/UseSender",
//STRIP001                  case  3:
//STRIP001                      pValues[nProp] >>= aEnvItem.lAddrFromLeft;// "Format/AddresseeFromLeft",
//STRIP001                      aEnvItem.lAddrFromLeft = MM100_TO_TWIP(aEnvItem.lAddrFromLeft);
//STRIP001                  break;
//STRIP001                  case  4:
//STRIP001                      pValues[nProp] >>= aEnvItem.lAddrFromTop;  // "Format/AddresseeFromTop",
//STRIP001                      aEnvItem.lAddrFromTop = MM100_TO_TWIP(aEnvItem.lAddrFromTop);
//STRIP001                  break;
//STRIP001                  case  5:
//STRIP001                      pValues[nProp] >>= aEnvItem.lSendFromLeft; // "Format/SenderFromLeft",
//STRIP001                      aEnvItem.lSendFromLeft = MM100_TO_TWIP(aEnvItem.lSendFromLeft);
//STRIP001                  break;
//STRIP001                  case  6:
//STRIP001                      pValues[nProp] >>= aEnvItem.lSendFromTop;// "Format/SenderFromTop",
//STRIP001                      aEnvItem.lSendFromTop = MM100_TO_TWIP(aEnvItem.lSendFromTop);
//STRIP001                  break;
//STRIP001                  case  7:
//STRIP001                      pValues[nProp] >>= aEnvItem.lWidth; // "Format/Width",
//STRIP001                      aEnvItem.lWidth = MM100_TO_TWIP(aEnvItem.lWidth);
//STRIP001                  break;
//STRIP001                  case  8:
//STRIP001                      pValues[nProp] >>= aEnvItem.lHeight; // "Format/Height",
//STRIP001                      aEnvItem.lHeight = MM100_TO_TWIP(aEnvItem.lHeight);
//STRIP001                  break;
//STRIP001                  case  9:
//STRIP001                  {
//STRIP001                      sal_Int32 nTemp;
//STRIP001                      pValues[nProp] >>= nTemp; aEnvItem.eAlign = (SwEnvAlign)nTemp; break;// "Print/Alignment",
//STRIP001                  }
//STRIP001                  case 10: aEnvItem.bPrintFromAbove = *(sal_Bool*)pValues[nProp].getValue(); break;// "Print/FromAbove",
//STRIP001                  case 11:
//STRIP001                      pValues[nProp] >>= aEnvItem.lShiftRight;
//STRIP001                      aEnvItem.lShiftRight = MM100_TO_TWIP(aEnvItem.lShiftRight);// "Print/Right",
//STRIP001                  break;
//STRIP001                  case 12:
//STRIP001                      pValues[nProp] >>= aEnvItem.lShiftDown;
//STRIP001                      aEnvItem.lShiftDown = MM100_TO_TWIP(aEnvItem.lShiftDown);
//STRIP001                  break;// "Print/Down"
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 }
/* -----------------------------26.09.00 14:04--------------------------------

 ---------------------------------------------------------------------------*/
//STRIP001 SwEnvCfgItem::~SwEnvCfgItem()
//STRIP001 {
//STRIP001 }
/* -----------------------------26.09.00 14:05--------------------------------

 ---------------------------------------------------------------------------*/
//STRIP001 void SwEnvCfgItem::Commit()
//STRIP001 {
//STRIP001  Sequence<OUString> aNames = GetPropertyNames();
//STRIP001  OUString* pNames = aNames.getArray();
//STRIP001  Sequence<Any> aValues(aNames.getLength());
//STRIP001  Any* pValues = aValues.getArray();
//STRIP001
//STRIP001  const Type& rType = ::getBooleanCppuType();
//STRIP001  for(int nProp = 0; nProp < aNames.getLength(); nProp++)
//STRIP001  {
//STRIP001      switch(nProp)
//STRIP001      {
//STRIP001          case  0: pValues[nProp] <<= aEnvItem.aAddrText; break;// "Inscription/Addressee",
//STRIP001          case  1: pValues[nProp] <<= aEnvItem.aSendText; break;// "Inscription/Sender",
//STRIP001          case  2: pValues[nProp].setValue(&aEnvItem.bSend, rType);break;// "Inscription/UseSender",
//STRIP001          case  3: pValues[nProp] <<= TWIP_TO_MM100(aEnvItem.lAddrFromLeft) ; break;// "Format/AddresseeFromLeft",
//STRIP001          case  4: pValues[nProp] <<= TWIP_TO_MM100(aEnvItem.lAddrFromTop)  ; break;// "Format/AddresseeFromTop",
//STRIP001          case  5: pValues[nProp] <<= TWIP_TO_MM100(aEnvItem.lSendFromLeft) ; break;// "Format/SenderFromLeft",
//STRIP001          case  6: pValues[nProp] <<= TWIP_TO_MM100(aEnvItem.lSendFromTop)  ; break;// "Format/SenderFromTop",
//STRIP001          case  7: pValues[nProp] <<= TWIP_TO_MM100(aEnvItem.lWidth)  ; break;// "Format/Width",
//STRIP001          case  8: pValues[nProp] <<= TWIP_TO_MM100(aEnvItem.lHeight) ; break;// "Format/Height",
//STRIP001          case  9: pValues[nProp] <<= sal_Int32(aEnvItem.eAlign); break;// "Print/Alignment",
//STRIP001          case 10: pValues[nProp].setValue(&aEnvItem.bPrintFromAbove, rType); break;// "Print/FromAbove",
//STRIP001          case 11: pValues[nProp] <<= TWIP_TO_MM100(aEnvItem.lShiftRight);break; // "Print/Right",
//STRIP001          case 12: pValues[nProp] <<= TWIP_TO_MM100(aEnvItem.lShiftDown); break;// "Print/Down"
//STRIP001      }
//STRIP001  }
//STRIP001  PutProperties(aNames, aValues);
//STRIP001 }
/* -----------------------------26.09.00 14:04--------------------------------

 ---------------------------------------------------------------------------*/
//STRIP001 Sequence<rtl::OUString> SwEnvCfgItem::GetPropertyNames()
//STRIP001 {
//STRIP001  static const char* aPropNames[] =
//STRIP001  {
//STRIP001      "Inscription/Addressee",    //  0
//STRIP001      "Inscription/Sender",       //  1
//STRIP001      "Inscription/UseSender",    //  2
//STRIP001      "Format/AddresseeFromLeft", //  3
//STRIP001      "Format/AddresseeFromTop",  //  4
//STRIP001      "Format/SenderFromLeft",    //  5
//STRIP001      "Format/SenderFromTop",     //  6
//STRIP001      "Format/Width",             //  7
//STRIP001      "Format/Height",            //  8
//STRIP001      "Print/Alignment",          //  9
//STRIP001      "Print/FromAbove",          // 10
//STRIP001      "Print/Right",              // 11
//STRIP001      "Print/Down"                // 12
//STRIP001  };
//STRIP001  const int nCount = 13;
//STRIP001  Sequence<OUString> aNames(nCount);
//STRIP001  OUString* pNames = aNames.getArray();
//STRIP001  for(int i = 0; i < nCount; i++)
//STRIP001      pNames[i] = OUString::createFromAscii(aPropNames[i]);
//STRIP001  return aNames;
//STRIP001 }

//STRIP001 BOOL SwEnvItem::QueryValue( Any& rVal, BYTE nMemberId ) const
//STRIP001 {
//STRIP001     sal_Bool bRet = sal_True;
//STRIP001     switch(nMemberId & ~CONVERT_TWIPS)
//STRIP001     {
//STRIP001         case MID_ENV_ADDR_TEXT : rVal <<= aAddrText; break;
//STRIP001         case MID_ENV_SEND : rVal <<= bSend; break;
//STRIP001         case MID_SEND_TEXT : rVal <<= aSendText; break;
//STRIP001         case MID_ENV_ADDR_FROM_LEFT : rVal <<= lAddrFromLeft; break;
//STRIP001         case MID_ENV_ADDR_FROM_TOP : rVal <<= lAddrFromTop; break;
//STRIP001         case MID_ENV_SEND_FROM_LEFT : rVal <<= lSendFromLeft; break;
//STRIP001         case MID_ENV_SEND_FROM_TOP : rVal <<= lSendFromTop; break;
//STRIP001         case MID_ENV_WIDTH : rVal <<= lWidth; break;
//STRIP001         case MID_ENV_HEIGHT : rVal <<= lHeight; break;
//STRIP001         case MID_ENV_ALIGN            : rVal <<= (sal_Int16) eAlign; break;
//STRIP001         case MID_ENV_PRINT_FROM_ABOVE  : rVal <<= bPrintFromAbove; break;
//STRIP001         case MID_ENV_SHIFT_RIGHT      : rVal <<= lShiftRight; break;
//STRIP001         case MID_ENV_SHIFT_DOWN       : rVal <<= lShiftDown; break;
//STRIP001         default:
//STRIP001             DBG_ERROR("Wrong memberId");
//STRIP001             bRet = sal_False;
//STRIP001     }
//STRIP001     return bRet;
//STRIP001 }
/* -----------------------------26.04.01 12:26--------------------------------

 ---------------------------------------------------------------------------*/
//STRIP001 BOOL SwEnvItem::PutValue(const Any& rVal, BYTE nMemberId)
//STRIP001 {
//STRIP001     BOOL bRet = FALSE;
//STRIP001     switch(nMemberId  & ~CONVERT_TWIPS)
//STRIP001     {
//STRIP001         case MID_ENV_ADDR_TEXT : bRet = (rVal >>= aAddrText); break;
//STRIP001         case MID_ENV_SEND : bRet = (rVal >>= bSend); break;
//STRIP001         case MID_SEND_TEXT : bRet = (rVal >>= aSendText); break;
//STRIP001         case MID_ENV_ADDR_FROM_LEFT : bRet = (rVal >>= lAddrFromLeft); break;
//STRIP001         case MID_ENV_ADDR_FROM_TOP : bRet = (rVal >>= lAddrFromTop); break;
//STRIP001         case MID_ENV_SEND_FROM_LEFT : bRet = (rVal >>= lSendFromLeft); break;
//STRIP001         case MID_ENV_SEND_FROM_TOP : bRet = (rVal >>= lSendFromTop); break;
//STRIP001         case MID_ENV_WIDTH : bRet = (rVal >>= lWidth); break;
//STRIP001         case MID_ENV_HEIGHT : bRet = (rVal >>= lHeight); break;
//STRIP001         case MID_ENV_ALIGN :
//STRIP001         {
//STRIP001             sal_Int16 nTemp;
//STRIP001             bRet = (rVal >>= nTemp);
//STRIP001             if (bRet)
//STRIP001                 eAlign = SwEnvAlign(nTemp);
//STRIP001             break;
//STRIP001         }
//STRIP001         case MID_ENV_PRINT_FROM_ABOVE  : bRet = (rVal >>= bPrintFromAbove); break;
//STRIP001         case MID_ENV_SHIFT_RIGHT      : bRet = (rVal >>= lShiftRight); break;
//STRIP001         case MID_ENV_SHIFT_DOWN       : bRet = (rVal >>= lShiftDown); break;
//STRIP001         default:
//STRIP001             DBG_ERROR("Wrong memberId");
//STRIP001     }
//STRIP001     return bRet;
//STRIP001 }
}
