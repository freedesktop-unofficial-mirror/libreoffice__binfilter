/*************************************************************************
 *
 *  $RCSfile: svx_flditem.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: aw $ $Date: 2004-02-13 14:30:42 $
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

#ifndef _SV_METAACT_HXX
#include <vcl/metaact.hxx>
#endif
#ifndef _ZFORLIST_HXX
#include <svtools/zforlist.hxx>
#endif
#ifndef _INTN_HXX
#include <tools/intn.hxx>
#endif
#ifndef _URLOBJ_HXX
#include <tools/urlobj.hxx>
#endif
//#ifndef _SV_SYSTEM_HXX
//#include <vcl/system.hxx>
//#endif
#pragma hdrstop

#define _SVX_FLDITEM_CXX

#ifndef _UNOTOOLS_LOCALFILEHELPER_HXX
#include <unotools/localfilehelper.hxx>
#endif

#define ITEMID_FIELD    0
#include "flditem.hxx"
#include "adritem.hxx"

// #90477#
#ifndef _TOOLS_TENCCVT_HXX
#include <tools/tenccvt.hxx>
#endif
namespace binfilter {

#define FRAME_MARKER    (ULONG)0x21981357
#define CHARSET_MARKER  (FRAME_MARKER+1)

// -----------------------------------------------------------------------

/*N*/ TYPEINIT1( SvxFieldItem, SfxPoolItem );

/*N*/ SV_IMPL_PERSIST1( SvxFieldData, SvPersistBase );

// -----------------------------------------------------------------------

/*N*/ SvxFieldData::SvxFieldData()
/*N*/ {
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SvxFieldData::~SvxFieldData()
/*N*/ {
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SvxFieldData* SvxFieldData::Clone() const
/*N*/ {
/*N*/   return new SvxFieldData;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ int SvxFieldData::operator==( const SvxFieldData& rFld ) const
/*N*/ {
/*N*/   DBG_ASSERT( Type() == rFld.Type(), "==: Verschiedene Typen" );
/*N*/   return TRUE;    // Basicklasse immer gleich.
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ void SvxFieldData::Load( SvPersistStream & rStm )
/*N*/ {
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ void SvxFieldData::Save( SvPersistStream & rStm )
/*N*/ {
/*N*/ }


/*?*/ MetaAction* SvxFieldData::createBeginComment() const
/*?*/ {
/*?*/   DBG_ASSERT(0, "STRIP"); return NULL;//STRIP001  return new MetaCommentAction( "FIELD_SEQ_BEGIN" );
/*?*/ }

/*?*/ MetaAction* SvxFieldData::createEndComment() const
/*?*/ {
/*?*/   DBG_ASSERT(0, "STRIP");return NULL;//STRIP001   return new MetaCommentAction( "FIELD_SEQ_END" );
/*?*/ }

// -----------------------------------------------------------------------

/*N*/ SvxFieldItem::SvxFieldItem( SvxFieldData* pFld, const USHORT nId ) :
/*N*/   SfxPoolItem( nId )
/*N*/ {
/*N*/   pField = pFld;  // gehoert direkt dem Item
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SvxFieldItem::SvxFieldItem( const SvxFieldData& rField, const USHORT nId ) :
/*N*/   SfxPoolItem( nId )
/*N*/ {
/*N*/   pField = rField.Clone();
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SvxFieldItem::SvxFieldItem( const SvxFieldItem& rItem ) :
/*N*/   SfxPoolItem ( rItem )
/*N*/ {
/*N*/   pField = rItem.GetField() ? rItem.GetField()->Clone() : 0;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SvxFieldItem::~SvxFieldItem()
/*N*/ {
/*N*/   delete pField;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxFieldItem::Clone( SfxItemPool* ) const
/*N*/ {
/*N*/   return new SvxFieldItem(*this);
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxFieldItem::Create( SvStream& rStrm, USHORT ) const
/*N*/ {
/*N*/   SvxFieldData* pData = 0;
/*N*/   SvPersistStream aPStrm( GetClassManager(), &rStrm );
/*N*/   aPStrm >> pData;
/*N*/
/*N*/   if( aPStrm.IsEof() )
/*?*/       aPStrm.SetError( SVSTREAM_GENERALERROR );
/*N*/
/*N*/   if ( aPStrm.GetError() == ERRCODE_IO_NOFACTORY )
/*?*/       aPStrm.ResetError();    // Eigentlich einen Code, dass nicht alle Attr gelesen wurden...
/*N*/
/*N*/   return new SvxFieldItem( pData, Which() );
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SvStream& SvxFieldItem::Store( SvStream& rStrm, USHORT nItemVersion ) const
/*N*/ {
/*N*/   DBG_ASSERT( pField, "SvxFieldItem::Store: Feld?!" );
/*N*/   SvPersistStream aPStrm( GetClassManager(), &rStrm );
/*N*/   // Das ResetError in der obigen Create-Methode gab es in 3.1 noch nicht,
/*N*/   // deshalb duerfen beim 3.x-Export neuere Items nicht gespeichert werden!
/*N*/   if ( ( rStrm.GetVersion() <= SOFFICE_FILEFORMAT_31 ) && pField &&
/*N*/           pField->GetClassId() == 50 /* SdrMeasureField */ )
/*N*/   {
/*N*/       // SvxFieldData reicht nicht, weil auch nicht am ClassMgr angemeldet
/*?*/       SvxURLField aDummyData;
/*?*/       aPStrm << &aDummyData;
/*N*/   }
/*N*/   else
/*N*/       aPStrm << pField;
/*N*/
/*N*/   return rStrm;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ int SvxFieldItem::operator==( const SfxPoolItem& rItem ) const
/*N*/ {
/*N*/   DBG_ASSERT( SfxPoolItem::operator==( rItem ), "unequal which or type" );
/*N*/
/*N*/   const SvxFieldData* pOtherFld = ((const SvxFieldItem&)rItem).GetField();
/*N*/   if ( !pField && !pOtherFld )
/*N*/       return TRUE;
/*N*/
/*N*/   if ( ( !pField && pOtherFld ) || ( pField && !pOtherFld ) )
/*N*/       return FALSE;
/*N*/
/*N*/   return ( ( pField->Type() == pOtherFld->Type() )
/*N*/               && ( *pField == *pOtherFld ) );
/*N*/ }

// =================================================================
// Es folgen die Ableitungen von SvxFieldData...
// =================================================================

/*N*/ SV_IMPL_PERSIST1( SvxDateField, SvxFieldData );

// -----------------------------------------------------------------------

/*N*/ SvxDateField::SvxDateField()
/*N*/ {
/*N*/   nFixDate = Date().GetDate();
/*N*/   eType = SVXDATETYPE_VAR;
/*N*/   eFormat = SVXDATEFORMAT_STDSMALL;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SvxDateField::SvxDateField( const Date& rDate, SvxDateType eT, SvxDateFormat eF )
/*N*/ {
/*N*/   nFixDate = rDate.GetDate();
/*N*/   eType = eT;
/*N*/   eFormat = eF;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SvxFieldData* SvxDateField::Clone() const
/*N*/ {
/*N*/   return new SvxDateField( *this );
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ int SvxDateField::operator==( const SvxFieldData& rOther ) const
/*N*/ {
/*N*/   if ( rOther.Type() != Type() )
/*N*/       return FALSE;
/*N*/
/*N*/   const SvxDateField& rOtherFld = (const SvxDateField&) rOther;
/*N*/   return ( ( nFixDate == rOtherFld.nFixDate ) &&
/*N*/               ( eType == rOtherFld.eType ) &&
/*N*/               ( eFormat == rOtherFld.eFormat ) );
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ void SvxDateField::Load( SvPersistStream & rStm )
/*N*/ {
/*N*/   USHORT nType, nFormat;
/*N*/
/*N*/   rStm >> nFixDate;
/*N*/   rStm >> nType;
/*N*/   rStm >> nFormat;
/*N*/
/*N*/   eType = (SvxDateType)nType;
/*N*/   eFormat= (SvxDateFormat)nFormat;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ void SvxDateField::Save( SvPersistStream & rStm )
/*N*/ {
/*N*/   rStm << nFixDate;
/*N*/   rStm << (USHORT)eType;
/*N*/   rStm << (USHORT)eFormat;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ String SvxDateField::GetFormatted( SvNumberFormatter& rFormatter, LanguageType eLang ) const
/*N*/ {DBG_ASSERT(0, "STRIP"); return String(); //STRIP001
//STRIP001     Date aDate; // current date
//STRIP001  if ( eType == SVXDATETYPE_FIX )
//STRIP001      aDate.SetDate( nFixDate );
//STRIP001
//STRIP001  SvxDateFormat eTmpFormat = eFormat;
//STRIP001
//STRIP001  if ( eTmpFormat == SVXDATEFORMAT_SYSTEM )
//STRIP001  {
//STRIP001      DBG_ERROR( "SVXDATEFORMAT_SYSTEM nicht implementiert!" );
//STRIP001      eTmpFormat = SVXDATEFORMAT_STDSMALL;
//STRIP001  }
//STRIP001  else if ( eTmpFormat == SVXDATEFORMAT_APPDEFAULT )
//STRIP001  {
//STRIP001      DBG_ERROR( "SVXDATEFORMAT_APPDEFAULT: Woher nehmen?" );
//STRIP001      eTmpFormat = SVXDATEFORMAT_STDSMALL;
//STRIP001  }
//STRIP001
//STRIP001     ULONG nFormatKey;
//STRIP001
//STRIP001  switch( eTmpFormat )
//STRIP001  {
//STRIP001      case SVXDATEFORMAT_STDSMALL:
//STRIP001             // short
//STRIP001             nFormatKey = rFormatter.GetFormatIndex( NF_DATE_SYSTEM_SHORT, eLang );
//STRIP001      break;
//STRIP001      case SVXDATEFORMAT_STDBIG:
//STRIP001             // long
//STRIP001             nFormatKey = rFormatter.GetFormatIndex( NF_DATE_SYSTEM_LONG, eLang );
//STRIP001      break;
//STRIP001      case SVXDATEFORMAT_A:
//STRIP001          // 13.02.96
//STRIP001             nFormatKey = rFormatter.GetFormatIndex( NF_DATE_SYS_DDMMYY, eLang );
//STRIP001      break;
//STRIP001      case SVXDATEFORMAT_B:
//STRIP001          // 13.02.1996
//STRIP001             nFormatKey = rFormatter.GetFormatIndex( NF_DATE_SYS_DDMMYYYY, eLang );
//STRIP001      break;
//STRIP001      case SVXDATEFORMAT_C:
//STRIP001             // 13. Feb 1996
//STRIP001             nFormatKey = rFormatter.GetFormatIndex( NF_DATE_SYS_DMMMYYYY, eLang );
//STRIP001      break;
//STRIP001      case SVXDATEFORMAT_D:
//STRIP001             // 13. Februar 1996
//STRIP001             nFormatKey = rFormatter.GetFormatIndex( NF_DATE_SYS_DMMMMYYYY, eLang );
//STRIP001      break;
//STRIP001      case SVXDATEFORMAT_E:
//STRIP001             // Die, 13. Februar 1996
//STRIP001             nFormatKey = rFormatter.GetFormatIndex( NF_DATE_SYS_NNDMMMMYYYY, eLang );
//STRIP001      break;
//STRIP001      case SVXDATEFORMAT_F:
//STRIP001             // Dienstag, 13. Februar 1996
//STRIP001             nFormatKey = rFormatter.GetFormatIndex( NF_DATE_SYS_NNNNDMMMMYYYY, eLang );
//STRIP001      break;
//STRIP001         default:
//STRIP001             nFormatKey = rFormatter.GetStandardFormat( NUMBERFORMAT_DATE, eLang );
//STRIP001  }
//STRIP001
//STRIP001     double fDiffDate = aDate - *(rFormatter.GetNullDate());
//STRIP001     String aStr;
//STRIP001      Color* pColor = NULL;
//STRIP001     rFormatter.GetOutputString( fDiffDate, nFormatKey, aStr, &pColor );
//STRIP001     return aStr;
/*N*/ }

// deprecated, to be removed
/*N*/ XubString SvxDateField::GetFormatted( LanguageType eLanguage, LanguageType eFmt ) const
/*N*/ {DBG_ASSERT(0, "STRIP"); return XubString(); //STRIP001
//STRIP001  International aInter( eLanguage, eFmt );
//STRIP001  int bLongDate = FALSE;
//STRIP001
//STRIP001  Date aDate; // aktuelles
//STRIP001  if ( eType == SVXDATETYPE_FIX )
//STRIP001      aDate.SetDate( nFixDate );
//STRIP001
//STRIP001  SvxDateFormat eTmpFormat = eFormat;
//STRIP001
//STRIP001  if ( eTmpFormat == SVXDATEFORMAT_SYSTEM )
//STRIP001  {
//STRIP001      DBG_ERROR( "SVXDATEFORMAT_SYSTEM nicht implementiert!" );
//STRIP001      eTmpFormat = SVXDATEFORMAT_STDSMALL;
//STRIP001  }
//STRIP001  else if ( eTmpFormat == SVXDATEFORMAT_APPDEFAULT )
//STRIP001  {
//STRIP001      DBG_ERROR( "SVXDATEFORMAT_APPDEFAULT: Woher nehmen?" );
//STRIP001      eTmpFormat = SVXDATEFORMAT_STDSMALL;
//STRIP001  }
//STRIP001
//STRIP001  switch( eTmpFormat )
//STRIP001  {
//STRIP001      // kurze Formate standard
//STRIP001      case SVXDATEFORMAT_STDSMALL:
//STRIP001      break;
//STRIP001      case SVXDATEFORMAT_STDBIG:
//STRIP001      {
//STRIP001          bLongDate = TRUE;
//STRIP001      }
//STRIP001      break;
//STRIP001      case SVXDATEFORMAT_A:
//STRIP001      {
//STRIP001          // 13.02.96
//STRIP001          aInter.SetDateCentury( FALSE );
//STRIP001      }
//STRIP001      break;
//STRIP001      case SVXDATEFORMAT_B:
//STRIP001      {
//STRIP001          // 13.02.1996
//STRIP001          aInter.SetDateCentury( TRUE );
//STRIP001      }
//STRIP001      break;
//STRIP001      case SVXDATEFORMAT_C:
//STRIP001      {
//STRIP001          // 13.Feb 1996
//STRIP001          aInter.SetLongDateDayOfWeekFormat( DAYOFWEEK_NONE );
//STRIP001          aInter.SetLongDateMonthFormat( MONTH_SHORT );
//STRIP001          aInter.SetDateCentury( TRUE );
//STRIP001          bLongDate = TRUE;
//STRIP001      }
//STRIP001      break;
//STRIP001      case SVXDATEFORMAT_D:
//STRIP001      {
//STRIP001          // 13.Februar 1996
//STRIP001          aInter.SetLongDateDayOfWeekFormat(DAYOFWEEK_NONE);
//STRIP001          aInter.SetLongDateMonthFormat(MONTH_LONG);
//STRIP001          aInter.SetDateCentury(TRUE);
//STRIP001          bLongDate = TRUE;
//STRIP001      }
//STRIP001      break;
//STRIP001      case SVXDATEFORMAT_E:
//STRIP001      {
//STRIP001          // Die, 13.Februar 1996
//STRIP001          aInter.SetLongDateDayOfWeekFormat(DAYOFWEEK_SHORT);
//STRIP001          aInter.SetLongDateMonthFormat(MONTH_LONG);
//STRIP001          aInter.SetDateCentury(TRUE);
//STRIP001          bLongDate = TRUE;
//STRIP001      }
//STRIP001      break;
//STRIP001      case SVXDATEFORMAT_F:
//STRIP001      {
//STRIP001          // Dienstag, 13.Februar 1996
//STRIP001          aInter.SetLongDateDayOfWeekFormat(DAYOFWEEK_LONG);
//STRIP001          aInter.SetLongDateMonthFormat(MONTH_LONG);
//STRIP001          aInter.SetDateCentury(TRUE);
//STRIP001          bLongDate = TRUE;
//STRIP001      }
//STRIP001      break;
//STRIP001  }
//STRIP001
//STRIP001  if( bLongDate )
//STRIP001      return aInter.GetLongDate( aDate );
//STRIP001  return aInter.GetDate( aDate );
/*N*/ }

//STRIP001 MetaAction* SvxDateField::createBeginComment() const
//STRIP001 {
//STRIP001  return new MetaCommentAction( "FIELD_SEQ_BEGIN" );
//STRIP001 }

/*N*/ SV_IMPL_PERSIST1( SvxURLField, SvxFieldData );

// -----------------------------------------------------------------------

/*N*/ SvxURLField::SvxURLField()
/*N*/ {
/*N*/   eFormat = SVXURLFORMAT_URL;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SvxURLField::SvxURLField( const XubString& rURL, const XubString& rRepres, SvxURLFormat eFmt )
/*N*/   : aURL( rURL ), aRepresentation( rRepres )
/*N*/ {
/*N*/   eFormat = eFmt;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SvxFieldData* SvxURLField::Clone() const
/*N*/ {
/*N*/   return new SvxURLField( *this );
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ int SvxURLField::operator==( const SvxFieldData& rOther ) const
/*N*/ {
/*N*/   if ( rOther.Type() != Type() )
/*N*/       return FALSE;
/*N*/
/*N*/   const SvxURLField& rOtherFld = (const SvxURLField&) rOther;
/*N*/   return ( ( eFormat == rOtherFld.eFormat ) &&
/*N*/               ( aURL == rOtherFld.aURL ) &&
/*N*/               ( aRepresentation == rOtherFld.aRepresentation ) &&
/*N*/               ( aTargetFrame == rOtherFld.aTargetFrame ) );
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ void SvxURLField::Load( SvPersistStream & rStm )
/*N*/ {
/*N*/   USHORT nFormat;
/*N*/   ULONG nFrameMarker, nCharSetMarker;
/*N*/   long nUlongSize = (long)sizeof(ULONG);
/*N*/   String aTmpURL;
/*N*/
/*N*/   rStm >> nFormat;
/*N*/
/*N*/   // UNICODE: rStm >> aTmpURL;
/*N*/   rStm.ReadByteString(aTmpURL);
/*N*/
/*N*/   // UNICODE: rStm >> aRepresentation;
/*N*/   // read to a temp string first, read text encoding and
/*N*/   // convert later to stay compatible to fileformat
/*N*/   ByteString aTempString;
/*N*/   rtl_TextEncoding aTempEncoding = RTL_TEXTENCODING_MS_1252;  // #101493# Init for old documents
/*N*/   rStm.ReadByteString(aTempString);
/*N*/
/*N*/   rStm >> nFrameMarker;
/*N*/   if ( nFrameMarker == FRAME_MARKER )
/*N*/   {
/*N*/       // UNICODE: rStm >> aTargetFrame;
/*N*/       rStm.ReadByteString(aTargetFrame);
/*N*/
/*N*/       rStm >> nCharSetMarker;
/*N*/       if ( nCharSetMarker == CHARSET_MARKER )
/*N*/       {
/*N*/           USHORT nCharSet;
/*N*/           rStm >> nCharSet;
/*N*/
/*N*/           // remember encoding
/*N*/           aTempEncoding = (rtl_TextEncoding)nCharSet;
/*N*/       }
/*N*/       else
/*?*/           rStm.SeekRel( -nUlongSize );
/*N*/   }
/*N*/   else
/*?*/       rStm.SeekRel( -nUlongSize );
/*N*/
/*N*/   // now build representation string due to known encoding
/*N*/   aRepresentation = String(aTempString, aTempEncoding);
/*N*/
/*N*/   eFormat= (SvxURLFormat)nFormat;
/*N*/
/*N*/   // Relatives Speichern => Beim laden absolut machen.
/*N*/   aURL = INetURLObject::RelToAbs( aTmpURL );
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ void SvxURLField::Save( SvPersistStream & rStm )
/*N*/ {
/*N*/   // Relatives Speichern der URL
/*N*/   String aTmpURL = INetURLObject::AbsToRel( aURL );
/*N*/
/*N*/   rStm << (USHORT)eFormat;
/*N*/
/*N*/   // UNICODE: rStm << aTmpURL;
/*N*/   rStm.WriteByteString(aTmpURL);
/*N*/
/*N*/   // UNICODE: rStm << aRepresentation;
/*N*/   rStm.WriteByteString(aRepresentation);
/*N*/
/*N*/   rStm << FRAME_MARKER;
/*N*/
/*N*/   // UNICODE: rStm << aTargetFrame;
/*N*/   rStm.WriteByteString(aTargetFrame);
/*N*/
/*N*/   rStm << CHARSET_MARKER;
/*N*/
/*N*/   // #90477# rStm << (USHORT)GetStoreCharSet(gsl_getSystemTextEncoding(), rStm.GetVersion());
/*N*/   rStm << (USHORT)GetSOStoreTextEncoding(gsl_getSystemTextEncoding(), (sal_uInt16)rStm.GetVersion());
/*N*/ }

//STRIP001 MetaAction* SvxURLField::createBeginComment() const
//STRIP001 {
//STRIP001  return new MetaCommentAction( "FIELD_SEQ_BEGIN" );
//STRIP001 }

// =================================================================
// Die Felder, die aus Calc ausgebaut wurden:
// =================================================================

/*N*/ SV_IMPL_PERSIST1( SvxPageField, SvxFieldData );

/*N*/ SvxFieldData* __EXPORT SvxPageField::Clone() const
/*N*/ {
/*N*/   return new SvxPageField;        // leer
/*N*/ }

/*N*/ int __EXPORT SvxPageField::operator==( const SvxFieldData& rCmp ) const
/*N*/ {
/*N*/   return ( rCmp.Type() == TYPE(SvxPageField) );
/*N*/ }

/*N*/ void __EXPORT SvxPageField::Load( SvPersistStream & rStm )
/*N*/ {
/*N*/ }

/*N*/ void __EXPORT SvxPageField::Save( SvPersistStream & rStm )
/*N*/ {
/*N*/ }

//STRIP001 MetaAction* SvxPageField::createBeginComment() const
//STRIP001 {
//STRIP001     return new MetaCommentAction( "FIELD_SEQ_BEGIN;PageField" );
//STRIP001 }


/*N*/ SV_IMPL_PERSIST1( SvxPagesField, SvxFieldData );

/*N*/ SvxFieldData* __EXPORT SvxPagesField::Clone() const
/*N*/ {
/*N*/   return new SvxPagesField;   // leer
/*N*/ }

/*N*/ int __EXPORT SvxPagesField::operator==( const SvxFieldData& rCmp ) const
/*N*/ {
/*N*/   return ( rCmp.Type() == TYPE(SvxPagesField) );
/*N*/ }

/*N*/ void __EXPORT SvxPagesField::Load( SvPersistStream & rStm )
/*N*/ {
/*N*/ }

/*N*/ void __EXPORT SvxPagesField::Save( SvPersistStream & rStm )
/*N*/ {
/*N*/ }

/*N*/ SV_IMPL_PERSIST1( SvxTimeField, SvxFieldData );

/*N*/ SvxFieldData* __EXPORT SvxTimeField::Clone() const
/*N*/ {
/*N*/   return new SvxTimeField;    // leer
/*N*/ }

/*N*/ int __EXPORT SvxTimeField::operator==( const SvxFieldData& rCmp ) const
/*N*/ {
/*N*/   return ( rCmp.Type() == TYPE(SvxTimeField) );
/*N*/ }

/*N*/ void __EXPORT SvxTimeField::Load( SvPersistStream & rStm )
/*N*/ {
/*N*/ }

/*N*/ void __EXPORT SvxTimeField::Save( SvPersistStream & rStm )
/*N*/ {
/*N*/ }

//STRIP001 MetaAction* SvxTimeField::createBeginComment() const
//STRIP001 {
//STRIP001  return new MetaCommentAction( "FIELD_SEQ_BEGIN" );
//STRIP001 }

/*N*/ SV_IMPL_PERSIST1( SvxFileField, SvxFieldData );

/*N*/ SvxFieldData* __EXPORT SvxFileField::Clone() const
/*N*/ {
/*N*/   return new SvxFileField;    // leer
/*N*/ }

/*N*/ int __EXPORT SvxFileField::operator==( const SvxFieldData& rCmp ) const
/*N*/ {
/*N*/   return ( rCmp.Type() == TYPE(SvxFileField) );
/*N*/ }

/*N*/ void __EXPORT SvxFileField::Load( SvPersistStream & rStm )
/*N*/ {
/*N*/ }

/*N*/ void __EXPORT SvxFileField::Save( SvPersistStream & rStm )
/*N*/ {
/*N*/ }

/*N*/ SV_IMPL_PERSIST1( SvxTableField, SvxFieldData );

/*N*/ SvxFieldData* __EXPORT SvxTableField::Clone() const
/*N*/ {
/*N*/   return new SvxTableField;   // leer
/*N*/ }

/*N*/ int __EXPORT SvxTableField::operator==( const SvxFieldData& rCmp ) const
/*N*/ {
/*N*/   return ( rCmp.Type() == TYPE(SvxTableField) );
/*N*/ }

/*N*/ void __EXPORT SvxTableField::Load( SvPersistStream & rStm )
/*N*/ {
/*N*/ }

/*N*/ void __EXPORT SvxTableField::Save( SvPersistStream & rStm )
/*N*/ {
/*N*/ }

//----------------------------------------------------------------------------
//      SvxExtTimeField
//----------------------------------------------------------------------------

/*N*/ SV_IMPL_PERSIST1( SvxExtTimeField, SvxFieldData );

//----------------------------------------------------------------------------

/*N*/ SvxExtTimeField::SvxExtTimeField()
/*N*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  nFixTime = Time().GetTime();
//STRIP001  eType = SVXTIMETYPE_VAR;
//STRIP001  eFormat = SVXTIMEFORMAT_STANDARD;
/*N*/ }

//----------------------------------------------------------------------------

/*N*/ SvxExtTimeField::SvxExtTimeField( const Time& rTime, SvxTimeType eT, SvxTimeFormat eF )
/*N*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  nFixTime = rTime.GetTime();
//STRIP001  eType = eT;
//STRIP001  eFormat = eF;
/*N*/ }

//----------------------------------------------------------------------------

/*N*/ SvxFieldData* SvxExtTimeField::Clone() const
/*N*/ {DBG_ASSERT(0, "STRIP"); return 0; //STRIP001
//STRIP001  return new SvxExtTimeField( *this );
/*N*/ }

//----------------------------------------------------------------------------

/*N*/ int SvxExtTimeField::operator==( const SvxFieldData& rOther ) const
/*N*/ {DBG_ASSERT(0, "STRIP"); return 0; //STRIP001
//STRIP001  if ( rOther.Type() != Type() )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  const SvxExtTimeField& rOtherFld = (const SvxExtTimeField&) rOther;
//STRIP001  return ( ( nFixTime == rOtherFld.nFixTime ) &&
//STRIP001              ( eType == rOtherFld.eType ) &&
//STRIP001              ( eFormat == rOtherFld.eFormat ) );
/*N*/ }

//----------------------------------------------------------------------------

/*N*/ void SvxExtTimeField::Load( SvPersistStream & rStm )
/*N*/ {
/*N*/   USHORT nType, nFormat;
/*N*/
/*N*/   rStm >> nFixTime;
/*N*/   rStm >> nType;
/*N*/   rStm >> nFormat;
/*N*/
/*N*/   eType = (SvxTimeType) nType;
/*N*/   eFormat= (SvxTimeFormat) nFormat;
/*N*/ }

//----------------------------------------------------------------------------

/*N*/ void SvxExtTimeField::Save( SvPersistStream & rStm )
/*N*/ {
/*N*/   rStm << nFixTime;
/*N*/   rStm << (USHORT) eType;
/*N*/   rStm << (USHORT) eFormat;
/*N*/ }

//----------------------------------------------------------------------------

//STRIP001 String SvxExtTimeField::GetFormatted( SvNumberFormatter& rFormatter, LanguageType eLang ) const
//STRIP001 {
//STRIP001     Time aTime; // current time
//STRIP001  if ( eType == SVXTIMETYPE_FIX )
//STRIP001      aTime.SetTime( nFixTime );
//STRIP001
//STRIP001  SvxTimeFormat eTmpFormat = eFormat;
//STRIP001
//STRIP001  switch( eTmpFormat )
//STRIP001  {
//STRIP001         case SVXTIMEFORMAT_SYSTEM :
//STRIP001             DBG_ERROR( "SVXTIMEFORMAT_SYSTEM: not implemented" );
//STRIP001             eTmpFormat = SVXTIMEFORMAT_STANDARD;
//STRIP001         break;
//STRIP001         case SVXTIMEFORMAT_APPDEFAULT :
//STRIP001             DBG_ERROR( "SVXTIMEFORMAT_APPDEFAULT: not implemented" );
//STRIP001             eTmpFormat = SVXTIMEFORMAT_STANDARD;
//STRIP001         break;
//STRIP001  }
//STRIP001
//STRIP001     ULONG nFormatKey;
//STRIP001
//STRIP001  switch( eTmpFormat )
//STRIP001  {
//STRIP001      case SVXTIMEFORMAT_12_HM:
//STRIP001             nFormatKey = rFormatter.GetFormatIndex( NF_TIME_HHMMAMPM, eLang );
//STRIP001      break;
//STRIP001         case SVXTIMEFORMAT_12_HMSH:
//STRIP001         {   // no builtin format available, try to insert or reuse
//STRIP001             String aFormatCode( RTL_CONSTASCII_USTRINGPARAM( "HH:MM:SS.00 AM/PM" ) );
//STRIP001             xub_StrLen nCheckPos;
//STRIP001             short nType;
//STRIP001             BOOL bInserted = rFormatter.PutandConvertEntry( aFormatCode,
//STRIP001                 nCheckPos, nType, nFormatKey, LANGUAGE_ENGLISH_US, eLang );
//STRIP001             DBG_ASSERT( nCheckPos == 0, "SVXTIMEFORMAT_12_HMSH: could not insert format code" );
//STRIP001             if ( nCheckPos )
//STRIP001                 nFormatKey = rFormatter.GetFormatIndex( NF_TIME_HH_MMSS00, eLang );
//STRIP001         }
//STRIP001         break;
//STRIP001      case SVXTIMEFORMAT_24_HM:
//STRIP001             nFormatKey = rFormatter.GetFormatIndex( NF_TIME_HHMM, eLang );
//STRIP001      break;
//STRIP001      case SVXTIMEFORMAT_24_HMSH:
//STRIP001             nFormatKey = rFormatter.GetFormatIndex( NF_TIME_HH_MMSS00, eLang );
//STRIP001      break;
//STRIP001      case SVXTIMEFORMAT_12_HMS:
//STRIP001             nFormatKey = rFormatter.GetFormatIndex( NF_TIME_HHMMSSAMPM, eLang );
//STRIP001      break;
//STRIP001      case SVXTIMEFORMAT_24_HMS:
//STRIP001             nFormatKey = rFormatter.GetFormatIndex( NF_TIME_HHMMSS, eLang );
//STRIP001      break;
//STRIP001      case SVXTIMEFORMAT_STANDARD:
//STRIP001         default:
//STRIP001             nFormatKey = rFormatter.GetStandardFormat( NUMBERFORMAT_TIME, eLang );
//STRIP001  }
//STRIP001
//STRIP001     double fFracTime = aTime.GetTimeInDays();
//STRIP001     String aStr;
//STRIP001      Color* pColor = NULL;
//STRIP001     rFormatter.GetOutputString( fFracTime, nFormatKey, aStr, &pColor );
//STRIP001     return aStr;
//STRIP001 }

// deprecated, to be removed
//STRIP001 XubString SvxExtTimeField::GetFormatted( LanguageType eLanguage, LanguageType eFmt ) const
//STRIP001 {
//STRIP001  International aInter( eLanguage, eFmt );
//STRIP001  XubString aStrTime;
//STRIP001
//STRIP001  Time aTime; // aktuelle Zeit
//STRIP001  if ( eType == SVXTIMETYPE_FIX )
//STRIP001      aTime.SetTime( nFixTime );
//STRIP001
//STRIP001  SvxTimeFormat eTmpFormat = eFormat;
//STRIP001
//STRIP001  if ( eTmpFormat == SVXTIMEFORMAT_SYSTEM )
//STRIP001  {
//STRIP001      DBG_ERROR( "SVXTIMEFORMAT_SYSTEM nicht implementiert!" );
//STRIP001      eTmpFormat = SVXTIMEFORMAT_STANDARD;
//STRIP001  }
//STRIP001  else if ( eTmpFormat == SVXTIMEFORMAT_APPDEFAULT )
//STRIP001  {
//STRIP001      DBG_ERROR( "SVXTIMEFORMAT_APPDEFAULT: Woher nehmen?" );
//STRIP001      eTmpFormat = SVXTIMEFORMAT_STANDARD;
//STRIP001  }
//STRIP001
//STRIP001  // 12 oder 24 Stunden
//STRIP001  switch( eTmpFormat )
//STRIP001  {
//STRIP001      case SVXTIMEFORMAT_24_HM:
//STRIP001      case SVXTIMEFORMAT_24_HMS:
//STRIP001      case SVXTIMEFORMAT_24_HMSH:
//STRIP001          aInter.SetTimeFormat( HOUR_24 );
//STRIP001      break;
//STRIP001
//STRIP001      default:
//STRIP001          aInter.SetTimeFormat( HOUR_12 );
//STRIP001      break;
//STRIP001  }
//STRIP001  switch( eTmpFormat )
//STRIP001  {
//STRIP001      case SVXTIMEFORMAT_12_HM:
//STRIP001      case SVXTIMEFORMAT_24_HM:
//STRIP001           aStrTime = aInter.GetTime( aTime, FALSE );
//STRIP001      break;
//STRIP001
//STRIP001      case SVXTIMEFORMAT_12_HMSH:
//STRIP001      case SVXTIMEFORMAT_24_HMSH:
//STRIP001           aStrTime = aInter.GetTime( aTime, TRUE, TRUE );
//STRIP001      break;
//STRIP001
//STRIP001      case SVXTIMEFORMAT_STANDARD:
//STRIP001      case SVXTIMEFORMAT_12_HMS:
//STRIP001      case SVXTIMEFORMAT_24_HMS:
//STRIP001      default:
//STRIP001           aStrTime = aInter.GetTime( aTime, TRUE );
//STRIP001      break;
//STRIP001
//STRIP001  }
//STRIP001
//STRIP001  return( aStrTime );
//STRIP001 }

//STRIP001 MetaAction* SvxExtTimeField::createBeginComment() const
//STRIP001 {
//STRIP001  return new MetaCommentAction( "FIELD_SEQ_BEGIN" );
//STRIP001 }

//----------------------------------------------------------------------------
//      SvxExtFileField
//----------------------------------------------------------------------------

/*N*/ SV_IMPL_PERSIST1( SvxExtFileField, SvxFieldData );

//----------------------------------------------------------------------------

/*N*/ SvxExtFileField::SvxExtFileField()
/*N*/ {
/*N*/   eType = SVXFILETYPE_VAR;
/*N*/   eFormat = SVXFILEFORMAT_FULLPATH;
/*N*/ }

//----------------------------------------------------------------------------

/*N*/ SvxExtFileField::SvxExtFileField( const XubString& rStr, SvxFileType eT, SvxFileFormat eF )
/*N*/ {
/*N*/   aFile = rStr;
/*N*/   eType = eT;
/*N*/   eFormat = eF;
/*N*/ }

//----------------------------------------------------------------------------

/*N*/ SvxFieldData* SvxExtFileField::Clone() const
/*N*/ {DBG_ASSERT(0, "STRIP"); return NULL; //STRIP001
//STRIP001  return new SvxExtFileField( *this );
/*N*/ }

//----------------------------------------------------------------------------

/*N*/ int SvxExtFileField::operator==( const SvxFieldData& rOther ) const
/*N*/ {DBG_ASSERT(0, "STRIP"); return 0; //STRIP001
//STRIP001  if ( rOther.Type() != Type() )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  const SvxExtFileField& rOtherFld = (const SvxExtFileField&) rOther;
//STRIP001  return ( ( aFile == rOtherFld.aFile ) &&
//STRIP001              ( eType == rOtherFld.eType ) &&
//STRIP001              ( eFormat == rOtherFld.eFormat ) );
/*N*/ }

//----------------------------------------------------------------------------

/*N*/ void SvxExtFileField::Load( SvPersistStream & rStm )
/*N*/ {
/*N*/   USHORT nType, nFormat;
/*N*/
/*N*/   // UNICODE: rStm >> aFile;
/*N*/   rStm.ReadByteString(aFile);
/*N*/
/*N*/   rStm >> nType;
/*N*/   rStm >> nFormat;
/*N*/
/*N*/   eType = (SvxFileType) nType;
/*N*/   eFormat= (SvxFileFormat) nFormat;
/*N*/ }

//----------------------------------------------------------------------------

/*N*/ void SvxExtFileField::Save( SvPersistStream & rStm )
/*N*/ {
/*N*/   // UNICODE: rStm << aFile;
/*N*/   rStm.WriteByteString(aFile);
/*N*/
/*N*/   rStm << (USHORT) eType;
/*N*/   rStm << (USHORT) eFormat;
/*N*/ }

//----------------------------------------------------------------------------

//STRIP001 XubString SvxExtFileField::GetFormatted() const
//STRIP001 {
//STRIP001  XubString aString;
//STRIP001
//STRIP001  INetURLObject aURLObj( aFile );
//STRIP001
//STRIP001     if( INET_PROT_NOT_VALID == aURLObj.GetProtocol() )
//STRIP001     {
//STRIP001         // invalid? try to interpret string as system file name
//STRIP001         String aURLStr;
//STRIP001
//STRIP001         ::utl::LocalFileHelper::ConvertPhysicalNameToURL( aFile, aURLStr );
//STRIP001
//STRIP001         aURLObj.SetURL( aURLStr );
//STRIP001     }
//STRIP001
//STRIP001     // #92009# Be somewhat liberate when trying to
//STRIP001     // get formatted content out of the FileField
//STRIP001     if( INET_PROT_NOT_VALID == aURLObj.GetProtocol() )
//STRIP001     {
//STRIP001         // still not valid? Then output as is
//STRIP001         aString = aFile;
//STRIP001     }
//STRIP001  else if( INET_PROT_FILE == aURLObj.GetProtocol() )
//STRIP001  {
//STRIP001      switch( eFormat )
//STRIP001      {
//STRIP001          case SVXFILEFORMAT_FULLPATH:
//STRIP001              aString = aURLObj.getFSysPath(INetURLObject::FSYS_DETECT);
//STRIP001          break;
//STRIP001
//STRIP001          case SVXFILEFORMAT_PATH:
//STRIP001                 aURLObj.removeSegment(INetURLObject::LAST_SEGMENT, false);
//STRIP001                 // #101742# Leave trailing slash at the pathname
//STRIP001                 aURLObj.setFinalSlash();
//STRIP001              aString = aURLObj.getFSysPath(INetURLObject::FSYS_DETECT);
//STRIP001          break;
//STRIP001
//STRIP001          case SVXFILEFORMAT_NAME:
//STRIP001              aString = aURLObj.getBase();
//STRIP001          break;
//STRIP001
//STRIP001          case SVXFILEFORMAT_NAME_EXT:
//STRIP001              aString = aURLObj.getName();
//STRIP001          break;
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      switch( eFormat )
//STRIP001      {
//STRIP001          case SVXFILEFORMAT_FULLPATH:
//STRIP001              aString = aURLObj.GetMainURL( INetURLObject::DECODE_TO_IURI );
//STRIP001          break;
//STRIP001
//STRIP001          case SVXFILEFORMAT_PATH:
//STRIP001                 aURLObj.removeSegment(INetURLObject::LAST_SEGMENT, false);
//STRIP001                 // #101742# Leave trailing slash at the pathname
//STRIP001                 aURLObj.setFinalSlash();
//STRIP001              aString = aURLObj.GetMainURL( INetURLObject::DECODE_TO_IURI );
//STRIP001          break;
//STRIP001
//STRIP001          case SVXFILEFORMAT_NAME:
//STRIP001              aString = aURLObj.getBase();
//STRIP001          break;
//STRIP001
//STRIP001          case SVXFILEFORMAT_NAME_EXT:
//STRIP001              aString = aURLObj.getName();
//STRIP001          break;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  return( aString );
//STRIP001 }

//----------------------------------------------------------------------------
//      SvxAuthorField
//----------------------------------------------------------------------------

/*N*/ SV_IMPL_PERSIST1( SvxAuthorField, SvxFieldData );

//----------------------------------------------------------------------------

/*N*/ SvxAuthorField::SvxAuthorField()
/*N*/ {
/*N*/   eType = SVXAUTHORTYPE_VAR;
/*N*/   eFormat = SVXAUTHORFORMAT_FULLNAME;
/*N*/ }

//----------------------------------------------------------------------------

/*N*/ SvxAuthorField::SvxAuthorField( const SvxAddressItem& rAdrItem,
/*N*/                                   SvxAuthorType eT, SvxAuthorFormat eF )
/*N*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  aName      = rAdrItem.GetName();
//STRIP001  aFirstName = rAdrItem.GetFirstName();
//STRIP001  aShortName = rAdrItem.GetShortName();
//STRIP001  eType   = eT;
//STRIP001  eFormat = eF;
/*N*/ }

//----------------------------------------------------------------------------

/*N*/ SvxFieldData* SvxAuthorField::Clone() const
/*N*/ {DBG_ASSERT(0, "STRIP"); return NULL; //STRIP001
//STRIP001  return new SvxAuthorField( *this );
/*N*/ }

//----------------------------------------------------------------------------

/*N*/ int SvxAuthorField::operator==( const SvxFieldData& rOther ) const
/*N*/ {DBG_ASSERT(0, "STRIP"); return 0; //STRIP001
//STRIP001  if ( rOther.Type() != Type() )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  const SvxAuthorField& rOtherFld = (const SvxAuthorField&) rOther;
//STRIP001  return ( ( aName == rOtherFld.aName ) &&
//STRIP001              ( aFirstName == rOtherFld.aFirstName ) &&
//STRIP001              ( aShortName == rOtherFld.aShortName ) &&
//STRIP001              ( eType == rOtherFld.eType ) &&
//STRIP001              ( eFormat == rOtherFld.eFormat ) );
/*N*/ }

//----------------------------------------------------------------------------

/*N*/ void SvxAuthorField::Load( SvPersistStream & rStm )
/*N*/ {
/*N*/   USHORT nType, nFormat;
/*N*/
/*N*/   // UNICODE: rStm >> aName;
/*N*/   rStm.ReadByteString(aName);
/*N*/
/*N*/   // UNICODE: rStm >> aFirstName;
/*N*/   rStm.ReadByteString(aFirstName);
/*N*/
/*N*/   // UNICODE: rStm >> aShortName;
/*N*/   rStm.ReadByteString(aShortName);
/*N*/
/*N*/   rStm >> nType;
/*N*/   rStm >> nFormat;
/*N*/
/*N*/   eType = (SvxAuthorType) nType;
/*N*/   eFormat= (SvxAuthorFormat) nFormat;
/*N*/ }

//----------------------------------------------------------------------------

/*N*/ void SvxAuthorField::Save( SvPersistStream & rStm )
/*N*/ {
/*N*/   // UNICODE: rStm << aName;
/*N*/   rStm.WriteByteString(aName);
/*N*/
/*N*/   // UNICODE: rStm << aFirstName;
/*N*/   rStm.WriteByteString(aFirstName);
/*N*/
/*N*/   // UNICODE: rStm << aShortName;
/*N*/   rStm.WriteByteString(aShortName);
/*N*/
/*N*/   rStm << (USHORT) eType;
/*N*/   rStm << (USHORT) eFormat;
/*N*/ }

//----------------------------------------------------------------------------

/*N*/ XubString SvxAuthorField::GetFormatted() const
/*N*/ {
/*N*/   XubString aString;
/*N*/
/*N*/   switch( eFormat )
/*N*/   {
/*N*/       case SVXAUTHORFORMAT_FULLNAME:
/*N*/           aString  = aFirstName;
/*N*/           aString += sal_Unicode(' ');
/*N*/           aString += aName;
/*N*/       break;
/*N*/
/*N*/       case SVXAUTHORFORMAT_NAME:
/*N*/           aString = aName;
/*N*/       break;
/*N*/
/*N*/       case SVXAUTHORFORMAT_FIRSTNAME:
/*N*/           aString = aFirstName;
/*N*/       break;
/*N*/
/*N*/       case SVXAUTHORFORMAT_SHORTNAME:
/*N*/           aString = aShortName;
/*N*/       break;
/*N*/   }
/*N*/
/*N*/   return( aString );
/*N*/ }


}
