/*************************************************************************
 *
 *  $RCSfile: svx_hlnkitem.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:45:08 $
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

// include ---------------------------------------------------------------
#pragma hdrstop

#define _SVX_HLNKITEM_CXX

#ifndef _SVX_SVXIDS_HRC
#include <svxids.hrc>
#endif
#ifndef _STREAM_HXX
#include <tools/stream.hxx>
#endif

#ifndef _MEMBERID_HRC
#include <memberid.hrc>
#endif

#ifndef __SBX_SBXVARIABLE_HXX
#include <svtools/sbxvar.hxx>
#endif

#include "hlnkitem.hxx"
namespace binfilter {

// -----------------------------------------------------------------------

/*N*/ TYPEINIT1_AUTOFACTORY(SvxHyperlinkItem, SfxPoolItem);

// class SvxHyperlinkItem ------------------------------------------------

/*--------------------------------------------------------------------
    Beschreibung:
 --------------------------------------------------------------------*/

#define HYPERLINKFF_MARKER  0x599401FE

//STRIP001 SvStream& SvxHyperlinkItem::Store( SvStream& rStrm, sal_uInt16 nItemVersion ) const
//STRIP001 {
//STRIP001  // store 'simple' data
//STRIP001  // UNICODE: rStrm << sName;
//STRIP001  rStrm.WriteByteString(sName);
//STRIP001
//STRIP001  // UNICODE: rStrm << sURL;
//STRIP001  rStrm.WriteByteString(sURL);
//STRIP001
//STRIP001  // UNICODE: rStrm << sTarget;
//STRIP001  rStrm.WriteByteString(sTarget);
//STRIP001
//STRIP001  rStrm << (sal_uInt32) eType;
//STRIP001
//STRIP001  // marker for versioninfo
//STRIP001  rStrm << (sal_uInt32) HYPERLINKFF_MARKER;
//STRIP001
//STRIP001  // new data
//STRIP001  // UNICODE: rStrm << sIntName;
//STRIP001  rStrm.WriteByteString(sIntName);
//STRIP001
//STRIP001  // macro-events
//STRIP001  rStrm << nMacroEvents;
//STRIP001
//STRIP001  // store macros
//STRIP001  sal_uInt16 nCnt = pMacroTable ? (sal_uInt16)pMacroTable->Count() : 0;
//STRIP001  sal_uInt16 nMax = nCnt;
//STRIP001  if( nCnt )
//STRIP001  {
//STRIP001      for( SvxMacro* pMac = pMacroTable->First(); pMac; pMac = pMacroTable->Next() )
//STRIP001          if( STARBASIC != pMac->GetScriptType() )
//STRIP001              --nCnt;
//STRIP001  }
//STRIP001
//STRIP001  rStrm << nCnt;
//STRIP001
//STRIP001  if( nCnt )
//STRIP001  {
//STRIP001      // 1. StarBasic-Macros
//STRIP001      for( SvxMacro* pMac = pMacroTable->First(); pMac; pMac = pMacroTable->Next() )
//STRIP001      {
//STRIP001          if( STARBASIC == pMac->GetScriptType() )
//STRIP001          {
//STRIP001              rStrm << (sal_uInt16)pMacroTable->GetCurKey();
//STRIP001
//STRIP001              // UNICODE: rStrm << pMac->GetLibName();
//STRIP001              rStrm.WriteByteString(pMac->GetLibName());
//STRIP001
//STRIP001              // UNICODE: rStrm << pMac->GetMacName();
//STRIP001              rStrm.WriteByteString(pMac->GetMacName());
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  nCnt = nMax - nCnt;
//STRIP001  rStrm << nCnt;
//STRIP001  if( nCnt )
//STRIP001  {
//STRIP001      // 2. ::com::sun::star::script::JavaScript-Macros
//STRIP001      for( SvxMacro* pMac = pMacroTable->First(); pMac; pMac = pMacroTable->Next() )
//STRIP001      {
//STRIP001          if( STARBASIC != pMac->GetScriptType() )
//STRIP001          {
//STRIP001              rStrm << (sal_uInt16)pMacroTable->GetCurKey();
//STRIP001
//STRIP001              // UNICODE: rStrm << pMac->GetLibName();
//STRIP001              rStrm.WriteByteString(pMac->GetLibName());
//STRIP001
//STRIP001              // UNICODE: rStrm << pMac->GetMacName();
//STRIP001              rStrm.WriteByteString(pMac->GetMacName());
//STRIP001
//STRIP001              rStrm << (sal_uInt16)pMac->GetScriptType();
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  return rStrm;
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung:
 --------------------------------------------------------------------*/

//STRIP001 SfxPoolItem* SvxHyperlinkItem::Create( SvStream &rStrm, sal_uInt16 nItemVersion ) const
//STRIP001 {
//STRIP001  SvxHyperlinkItem* pNew = new SvxHyperlinkItem( Which() );
//STRIP001  sal_uInt32 nType;
//STRIP001
//STRIP001  // simple data-types
//STRIP001  // UNICODE: rStrm >> pNew->sName;
//STRIP001  rStrm.ReadByteString(pNew->sName);
//STRIP001
//STRIP001  // UNICODE: rStrm >> pNew->sURL;
//STRIP001  rStrm.ReadByteString(pNew->sURL);
//STRIP001
//STRIP001  // UNICODE: rStrm >> pNew->sTarget;
//STRIP001  rStrm.ReadByteString(pNew->sTarget);
//STRIP001
//STRIP001  rStrm >> nType;
//STRIP001  pNew->eType = (SvxLinkInsertMode) nType;
//STRIP001
//STRIP001  sal_uInt32 nPos = rStrm.Tell();
//STRIP001  sal_uInt32 nMarker;
//STRIP001  rStrm >> nMarker;
//STRIP001  if ( nMarker == HYPERLINKFF_MARKER )
//STRIP001  {
//STRIP001      // new data
//STRIP001      // UNICODE: rStrm >> pNew->sIntName;
//STRIP001      rStrm.ReadByteString(pNew->sIntName);
//STRIP001
//STRIP001      // macro-events
//STRIP001      rStrm >> pNew->nMacroEvents;
//STRIP001
//STRIP001      // macros
//STRIP001      sal_uInt16 nCnt;
//STRIP001      rStrm >> nCnt;
//STRIP001      while( nCnt-- )
//STRIP001      {
//STRIP001          sal_uInt16 nCurKey;
//STRIP001          String aLibName, aMacName;
//STRIP001
//STRIP001          rStrm >> nCurKey;
//STRIP001          // UNICODE: rStrm >> aLibName;
//STRIP001          rStrm.ReadByteString(aLibName);
//STRIP001
//STRIP001          // UNICODE: rStrm >> aMacName;
//STRIP001          rStrm.ReadByteString(aMacName);
//STRIP001
//STRIP001          pNew->SetMacro( nCurKey, SvxMacro( aMacName, aLibName, STARBASIC ) );
//STRIP001      }
//STRIP001
//STRIP001      rStrm >> nCnt;
//STRIP001      while( nCnt-- )
//STRIP001      {
//STRIP001          sal_uInt16 nCurKey, nScriptType;
//STRIP001          String aLibName, aMacName;
//STRIP001
//STRIP001          rStrm >> nCurKey;
//STRIP001
//STRIP001          // UNICODE: rStrm >> aLibName;
//STRIP001          rStrm.ReadByteString(aLibName);
//STRIP001
//STRIP001          // UNICODE: rStrm >> aMacName;
//STRIP001          rStrm.ReadByteString(aMacName);
//STRIP001
//STRIP001          rStrm >> nScriptType;
//STRIP001
//STRIP001          pNew->SetMacro( nCurKey, SvxMacro( aMacName, aLibName,
//STRIP001                                      (ScriptType)nScriptType ) );
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001      rStrm.Seek( nPos );
//STRIP001
//STRIP001  return pNew;
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung:
 --------------------------------------------------------------------*/

//STRIP001 SvxHyperlinkItem::SvxHyperlinkItem( const SvxHyperlinkItem& rHyperlinkItem ):
//STRIP001          SfxPoolItem(rHyperlinkItem)
//STRIP001 {
//STRIP001  sName   = rHyperlinkItem.sName;
//STRIP001  sURL    = rHyperlinkItem.sURL;
//STRIP001  sTarget = rHyperlinkItem.sTarget;
//STRIP001  eType   = rHyperlinkItem.eType;
//STRIP001  sIntName = rHyperlinkItem.sIntName;
//STRIP001  nMacroEvents = rHyperlinkItem.nMacroEvents;
//STRIP001
//STRIP001  if( rHyperlinkItem.GetMacroTbl() )
//STRIP001      pMacroTable = new SvxMacroTableDtor( *rHyperlinkItem.GetMacroTbl() );
//STRIP001  else
//STRIP001      pMacroTable=NULL;
//STRIP001
//STRIP001 };

/*--------------------------------------------------------------------
    Beschreibung:
 --------------------------------------------------------------------*/

//STRIP001 SvxHyperlinkItem::SvxHyperlinkItem( sal_uInt16 nWhich, String& rName, String& rURL,
//STRIP001                                  String& rTarget, String& rIntName, SvxLinkInsertMode eTyp,
//STRIP001                                  sal_uInt16 nEvents, SvxMacroTableDtor *pMacroTbl ):
//STRIP001  SfxPoolItem (nWhich),
//STRIP001  sName       (rName),
//STRIP001  sURL        (rURL),
//STRIP001  sTarget     (rTarget),
//STRIP001  eType       (eTyp),
//STRIP001  sIntName (rIntName),
//STRIP001  nMacroEvents (nEvents)
//STRIP001 {
//STRIP001  if (pMacroTbl)
//STRIP001      pMacroTable = new SvxMacroTableDtor ( *pMacroTbl );
//STRIP001  else
//STRIP001      pMacroTable=NULL;
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung:
 --------------------------------------------------------------------*/

/*?*/ SfxPoolItem* SvxHyperlinkItem::Clone( SfxItemPool* ) const
/*?*/ {
/*?*/ DBG_ASSERT(0, "STRIP"); return NULL;//STRIP001    return new SvxHyperlinkItem( *this );
/*?*/ }

/*--------------------------------------------------------------------
    Beschreibung:
 --------------------------------------------------------------------*/

/*?*/ int SvxHyperlinkItem::operator==( const SfxPoolItem& rAttr ) const
/*?*/ {
/*?*/ DBG_ASSERT(0, "STRIP"); return 0;//STRIP001 //STRIP001    DBG_ASSERT( SfxPoolItem::operator==(rAttr), "unterschiedliche Typen" );
//STRIP001
//STRIP001  const SvxHyperlinkItem& rItem = (const SvxHyperlinkItem&) rAttr;
//STRIP001
//STRIP001  sal_Bool bRet = ( sName   == rItem.sName   &&
//STRIP001                sURL    == rItem.sURL    &&
//STRIP001                sTarget == rItem.sTarget &&
//STRIP001                eType   == rItem.eType   &&
//STRIP001                sIntName == rItem.sIntName &&
//STRIP001                nMacroEvents == rItem.nMacroEvents);
//STRIP001  if (!bRet)
//STRIP001      return sal_False;
//STRIP001
//STRIP001  const SvxMacroTableDtor* pOther = ((SvxHyperlinkItem&)rAttr).pMacroTable;
//STRIP001  if( !pMacroTable )
//STRIP001      return ( !pOther || !pOther->Count() );
//STRIP001  if( !pOther )
//STRIP001      return 0 == pMacroTable->Count();
//STRIP001
//STRIP001  const SvxMacroTableDtor& rOwn = *pMacroTable;
//STRIP001  const SvxMacroTableDtor& rOther = *pOther;
//STRIP001
//STRIP001  // Anzahl unterschiedlich => auf jeden Fall ungleich
//STRIP001  if( rOwn.Count() != rOther.Count() )
//STRIP001      return sal_False;
//STRIP001
//STRIP001  // einzeln vergleichen; wegen Performance ist die Reihenfolge wichtig
//STRIP001  for( sal_uInt16 nNo = 0; nNo < rOwn.Count(); ++nNo )
//STRIP001  {
//STRIP001      const SvxMacro *pOwnMac = rOwn.GetObject(nNo);
//STRIP001      const SvxMacro *pOtherMac = rOther.GetObject(nNo);
//STRIP001      if (    rOwn.GetKey(pOwnMac) != rOther.GetKey(pOtherMac)  ||
//STRIP001              pOwnMac->GetLibName() != pOtherMac->GetLibName() ||
//STRIP001              pOwnMac->GetMacName() != pOtherMac->GetMacName() )
//STRIP001          return sal_False;
//STRIP001  }
//STRIP001
//STRIP001  return sal_True;
/*?*/ }


/*--------------------------------------------------------------------
    Beschreibung:
 --------------------------------------------------------------------*/

//STRIP001 void SvxHyperlinkItem::SetMacro( sal_uInt16 nEvent, const SvxMacro& rMacro )
//STRIP001 {
//STRIP001  if( nEvent < EVENT_SFX_START )
//STRIP001  {
//STRIP001      switch( nEvent )
//STRIP001      {
//STRIP001          case HYPERDLG_EVENT_MOUSEOVER_OBJECT:
//STRIP001              nEvent = SFX_EVENT_MOUSEOVER_OBJECT;
//STRIP001              break;
//STRIP001          case HYPERDLG_EVENT_MOUSECLICK_OBJECT:
//STRIP001              nEvent = SFX_EVENT_MOUSECLICK_OBJECT;
//STRIP001              break;
//STRIP001          case HYPERDLG_EVENT_MOUSEOUT_OBJECT:
//STRIP001              nEvent = SFX_EVENT_MOUSEOUT_OBJECT;
//STRIP001              break;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if( !pMacroTable )
//STRIP001      pMacroTable = new SvxMacroTableDtor;
//STRIP001
//STRIP001  SvxMacro *pOldMacro;
//STRIP001  if( 0 != ( pOldMacro = pMacroTable->Get( nEvent )) )
//STRIP001  {
//STRIP001      delete pOldMacro;
//STRIP001      pMacroTable->Replace( nEvent, new SvxMacro( rMacro ) );
//STRIP001  }
//STRIP001  else
//STRIP001      pMacroTable->Insert( nEvent, new SvxMacro( rMacro ) );
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung:
 --------------------------------------------------------------------*/

//STRIP001 void SvxHyperlinkItem::SetMacroTable( const SvxMacroTableDtor& rTbl )
//STRIP001 {
//STRIP001  if ( pMacroTable )
//STRIP001      delete pMacroTable;
//STRIP001
//STRIP001  pMacroTable = new SvxMacroTableDtor ( rTbl );
//STRIP001 }

//STRIP001 BOOL SvxHyperlinkItem::QueryValue( ::com::sun::star::uno::Any& rVal, BYTE nMemberId ) const
//STRIP001 {
//STRIP001     sal_Bool bConvert = 0!=(nMemberId&CONVERT_TWIPS);
//STRIP001     nMemberId &= ~CONVERT_TWIPS;
//STRIP001  switch(nMemberId)
//STRIP001  {
//STRIP001         case MID_HLINK_NAME   :
//STRIP001             rVal <<= ::rtl::OUString(sIntName.GetBuffer());
//STRIP001      break;
//STRIP001         case MID_HLINK_TEXT   :
//STRIP001             rVal <<= ::rtl::OUString(sName.GetBuffer());
//STRIP001      break;
//STRIP001         case MID_HLINK_URL:
//STRIP001             rVal <<= ::rtl::OUString(sURL.GetBuffer());
//STRIP001      break;
//STRIP001         case MID_HLINK_TARGET:
//STRIP001             rVal <<= ::rtl::OUString(sTarget.GetBuffer());
//STRIP001      break;
//STRIP001         case MID_HLINK_TYPE:
//STRIP001             rVal <<= (sal_Int32) eType;
//STRIP001      break;
//STRIP001         default:
//STRIP001             return FALSE;
//STRIP001  }
//STRIP001
//STRIP001     return TRUE;
//STRIP001 }

//STRIP001 BOOL SvxHyperlinkItem::PutValue( const ::com::sun::star::uno::Any& rVal, BYTE nMemberId )
//STRIP001 {
//STRIP001     sal_Bool bConvert = 0!=(nMemberId&CONVERT_TWIPS);
//STRIP001     nMemberId &= ~CONVERT_TWIPS;
//STRIP001     ::rtl::OUString aStr;
//STRIP001     sal_Int32 nVal;
//STRIP001  switch(nMemberId)
//STRIP001  {
//STRIP001         case MID_HLINK_NAME   :
//STRIP001          if(!(rVal >>= aStr))
//STRIP001              return sal_False;
//STRIP001             sIntName = aStr.getStr();
//STRIP001      break;
//STRIP001         case MID_HLINK_TEXT   :
//STRIP001          if(!(rVal >>= aStr))
//STRIP001              return sal_False;
//STRIP001             sName = aStr.getStr();
//STRIP001      break;
//STRIP001         case MID_HLINK_URL:
//STRIP001          if(!(rVal >>= aStr))
//STRIP001              return sal_False;
//STRIP001             sURL = aStr.getStr();
//STRIP001      break;
//STRIP001         case MID_HLINK_TARGET:
//STRIP001          if(!(rVal >>= aStr))
//STRIP001              return sal_False;
//STRIP001             sTarget = aStr.getStr();
//STRIP001      break;
//STRIP001         case MID_HLINK_TYPE:
//STRIP001             if(!(rVal >>= nVal))
//STRIP001              return sal_False;
//STRIP001             eType = (SvxLinkInsertMode) (sal_uInt16) nVal;
//STRIP001      break;
//STRIP001         default:
//STRIP001             return FALSE;
//STRIP001  }
//STRIP001
//STRIP001     return TRUE;
//STRIP001 }

}
