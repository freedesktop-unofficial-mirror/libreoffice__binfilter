/*************************************************************************
 *
 *  $RCSfile: sw_dbfld.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 17:25:02 $
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

#include <float.h>

// auto strip #ifndef _SFXAPP_HXX //autogen
// auto strip #include <bf_sfx2/app.hxx>
// auto strip #endif
// auto strip #ifndef _ZFORLIST_HXX
// auto strip #include <svtools/zforlist.hxx>
// auto strip #endif
#ifndef _SVX_PAGEITEM_HXX
#include <bf_svx/pageitem.hxx>
#endif
// auto strip #ifndef _COM_SUN_STAR_SDBC_DATATYPE_HPP_
// auto strip #include <com/sun/star/sdbc/DataType.hpp>
// auto strip #endif
#ifndef _UNOTOOLS_TRANSLITERATIONWRAPPER_HXX
#include <unotools/transliterationwrapper.hxx>
#endif

#ifndef _FMTFLD_HXX
#include <fmtfld.hxx>
#endif
#ifndef _TXTFLD_HXX
#include <txtfld.hxx>
#endif

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

// auto strip #ifndef _DOC_HXX
// auto strip #include <doc.hxx>
// auto strip #endif
#ifndef _DOCARY_HXX
#include <docary.hxx>
#endif
// auto strip #ifndef _FRAME_HXX
// auto strip #include <frame.hxx>
// auto strip #endif
// auto strip #ifndef _FLDBAS_HXX
// auto strip #include <fldbas.hxx>
// auto strip #endif
// auto strip #ifndef _PAM_HXX
// auto strip #include <pam.hxx>
// auto strip #endif
#ifndef _NDTXT_HXX
#include <ndtxt.hxx>
#endif
#ifndef _DBFLD_HXX
#include <dbfld.hxx>
#endif
#ifndef _DBMGR_HXX
#include <dbmgr.hxx>
#endif
#ifndef _DOCFLD_HXX
#include <docfld.hxx>
#endif
// auto strip #ifndef _EXPFLD_HXX
// auto strip #include <expfld.hxx>
// auto strip #endif
// auto strip #ifndef _TXTATR_HXX
// auto strip #include <txtatr.hxx>
// auto strip #endif
#ifndef _UNOFLDMID_H
#include <unofldmid.h>
#endif
namespace binfilter {
extern String& GetString( const ::com::sun::star::uno::Any& rAny, String& rStr ); //STRIP008

using namespace ::com::sun::star::sdbc;
using namespace ::com::sun::star;
using namespace ::rtl;

/*--------------------------------------------------------------------
    Beschreibung: Datenbanktrenner durch Punkte fuer Anzeige ersetzen
 --------------------------------------------------------------------*/

/*N*/ String lcl_DBTrennConv(const String& aContent)
/*N*/ {
/*N*/   String sTmp(aContent);
/*N*/   sal_Unicode* pStr = sTmp.GetBufferAccess();
/*N*/   for( USHORT i = sTmp.Len(); i; --i, ++pStr )
/*N*/       if( DB_DELIM == *pStr )
/*N*/           *pStr = '.';
/*N*/   return sTmp;
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung: DatenbankFeldTyp
 --------------------------------------------------------------------*/

/*N*/ SwDBFieldType::SwDBFieldType(SwDoc* pDocPtr, const String& rNam, const SwDBData& rDBData ) :
/*N*/   SwValueFieldType( pDocPtr, RES_DBFLD ),
/*N*/   aDBData(rDBData),
/*N*/   nRefCnt(0),
/*N*/   sColumn(rNam)
/*N*/ {
/*N*/     if(aDBData.sDataSource.getLength() || aDBData.sCommand.getLength())
/*N*/     {
/*N*/         sName =  aDBData.sDataSource;
/*N*/         sName += DB_DELIM;
/*N*/         sName += (String)aDBData.sCommand;
/*N*/         sName += DB_DELIM;
/*N*/     }
/*N*/   sName += GetColumnName();
/*N*/ }
//------------------------------------------------------------------------------

/*N*/ SwFieldType* SwDBFieldType::Copy() const
/*N*/ {
/*N*/   SwDBFieldType* pTmp = new SwDBFieldType(GetDoc(), sColumn, aDBData);
/*N*/   return pTmp;
/*N*/ }

//------------------------------------------------------------------------------
/*N*/ const String& SwDBFieldType::GetName() const
/*N*/ {
/*N*/   return sName;
/*N*/ }

//------------------------------------------------------------------------------

/*N*/ void SwDBFieldType::ReleaseRef()
/*N*/ {
/*N*/   ASSERT(nRefCnt > 0, "RefCount kleiner 0!");
/*N*/
/*N*/   if (--nRefCnt <= 0)
/*N*/   {
/*N*/       USHORT nPos = GetDoc()->GetFldTypes()->GetPos(this);
/*N*/
/*N*/       if (nPos != USHRT_MAX)
/*N*/       {
/*N*/           GetDoc()->RemoveFldType(nPos);
/*N*/           delete this;
/*N*/       }
/*N*/   }
/*N*/ }

/* -----------------24.02.99 14:51-------------------
 *
 * --------------------------------------------------*/
/*N*/ BOOL SwDBFieldType::QueryValue( ::com::sun::star::uno::Any& rAny, BYTE nMId ) const
/*N*/ {
/*N*/     nMId &= ~CONVERT_TWIPS;
/*N*/   switch( nMId )
/*N*/   {
/*N*/   case FIELD_PROP_PAR2:
/*N*/       rAny <<= aDBData.sDataSource;
/*N*/       break;
/*N*/   case FIELD_PROP_PAR4:
/*N*/       rAny <<= aDBData.sCommand;
/*N*/       break;
/*N*/   case FIELD_PROP_PAR1:
/*N*/       rAny <<= OUString(sColumn);
/*N*/       break;
/*N*/   case FIELD_PROP_SHORT1:
/*N*/       rAny <<= aDBData.nCommandType;
/*N*/       break;
/*N*/   default:
/*?*/       DBG_ERROR("illegal property");
/*N*/   }
/*N*/   return TRUE;
/*N*/ }
/* -----------------24.02.99 14:51-------------------
 *
 * --------------------------------------------------*/
/*N*/ BOOL SwDBFieldType::PutValue( const ::com::sun::star::uno::Any& rAny, BYTE nMId )
/*N*/ {
/*N*/     nMId &= ~CONVERT_TWIPS;
/*N*/   switch( nMId )
/*N*/   {
/*N*/   case FIELD_PROP_PAR2:
/*?*/       rAny >>= aDBData.sDataSource;
/*?*/       break;
/*?*/   case FIELD_PROP_PAR4:
/*?*/       rAny >>= aDBData.sCommand;
/*?*/       break;
/*?*/   case FIELD_PROP_PAR1:
/*?*/       {
/*?*/           String sTmp;
/*?*/           ::binfilter::GetString( rAny, sTmp );
/*?*/           if( sTmp != sColumn )
/*?*/           {
/*?*/               sColumn = sTmp;
/*?*/               SwClientIter aIter( *this );
/*?*/               SwFmtFld* pFld = (SwFmtFld*)aIter.First( TYPE( SwFmtFld ));
/*?*/               while(pFld)
/*?*/               {
/*?*/                   // Feld im Undo?
/*?*/                   SwTxtFld *pTxtFld = pFld->GetTxtFld();
/*?*/                   if(pTxtFld && pTxtFld->GetTxtNode().GetNodes().IsDocNodes() )
/*?*/                   {
/*?*/                       SwDBField* pDBField = (SwDBField*)pFld->GetFld();
/*?*/                       pDBField->ClearInitialized();
/*?*/                       pDBField->InitContent();
/*?*/                   }
/*?*/                   pFld = (SwFmtFld*)aIter.Next();
/*?*/               }
/*?*/           }
/*?*/       }
/*?*/       break;
/*N*/   case FIELD_PROP_SHORT1:
/*N*/       rAny >>= aDBData.nCommandType;
/*N*/       break;
/*N*/   default:
/*?*/       DBG_ERROR("illegal property");
/*N*/   }
/*N*/   return TRUE;
/*N*/ }
/*--------------------------------------------------------------------
    Beschreibung: SwDBField
 --------------------------------------------------------------------*/

/*N*/ SwDBField::SwDBField(SwDBFieldType* pTyp, ULONG nFmt)
/*N*/   :   SwValueField(pTyp, nFmt),
/*N*/       bValidValue(FALSE),
/*N*/       bIsInBodyTxt(TRUE),
/*N*/       bInitialized(FALSE),
/*N*/       nSubType(0)
/*N*/ {
/*N*/   if (GetTyp())
/*N*/       ((SwDBFieldType*)GetTyp())->AddRef();
/*N*/   InitContent();
/*N*/ }

//------------------------------------------------------------------------------

/*N*/ SwDBField::~SwDBField()
/*N*/ {
/*N*/   if (GetTyp())
/*N*/       ((SwDBFieldType*)GetTyp())->ReleaseRef();
/*N*/ }

//------------------------------------------------------------------------------

/*N*/ void SwDBField::InitContent()
/*N*/ {
/*N*/   if (!IsInitialized())
/*N*/   {
/*N*/       aContent = '<';
/*N*/       aContent += ((SwDBFieldType*)GetTyp())->GetColumnName();
/*N*/       aContent += '>';
/*N*/   }
/*N*/ }

//------------------------------------------------------------------------------

/*N*/ void SwDBField::InitContent(const String& rExpansion)
/*N*/ {
/*N*/   if (rExpansion.Len() > 2)
/*N*/   {
/*N*/       if (rExpansion.GetChar(0) == '<' &&
/*N*/           rExpansion.GetChar(rExpansion.Len() - 1) == '>')
/*N*/       {
/*N*/           String sColumn( rExpansion.Copy( 1, rExpansion.Len() - 2 ) );
/*N*/           if( ::binfilter::GetAppCmpStrIgnore().isEqual( sColumn,
/*N*/                           ((SwDBFieldType *)GetTyp())->GetColumnName() ))
/*N*/           {
/*N*/               InitContent();
/*N*/               return;
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/   SetExpansion( rExpansion );
/*N*/ }

//------------------------------------------------------------------------------

/*N*/ String SwDBField::GetOldContent()
/*N*/ {
/*N*/   String sOldExpand = Expand();
/*N*/   String sNewExpand = sOldExpand;
/*N*/   BOOL bOldInit = bInitialized;
/*N*/
/*N*/   bInitialized = FALSE;
/*N*/   InitContent();
/*N*/   bInitialized = bOldInit;
/*N*/
/*N*/   if( ::binfilter::GetAppCmpStrIgnore().isEqual( sNewExpand, Expand() ) )
/*N*/   {
/*N*/       sNewExpand = '<';
/*N*/       sNewExpand += ((SwDBFieldType *)GetTyp())->GetColumnName();
/*N*/       sNewExpand += '>';
/*N*/   }
/*N*/   SetExpansion( sOldExpand );
/*N*/
/*N*/   return sNewExpand;
/*N*/ }

//------------------------------------------------------------------------------

/*N*/ String SwDBField::Expand() const
/*N*/ {
/*N*/     String sRet;
/*N*/     if(0 ==(GetSubType() & SUB_INVISIBLE))
/*N*/         sRet = lcl_DBTrennConv(aContent);
/*N*/     return sRet;
/*N*/ }

//------------------------------------------------------------------------------

/*N*/ SwField* SwDBField::Copy() const
/*N*/ {
/*N*/   SwDBField *pTmp = new SwDBField((SwDBFieldType*)GetTyp(), GetFormat());
/*N*/   pTmp->aContent      = aContent;
/*N*/   pTmp->bIsInBodyTxt  = bIsInBodyTxt;
/*N*/   pTmp->bValidValue   = bValidValue;
/*N*/   pTmp->bInitialized  = bInitialized;
/*N*/   pTmp->nSubType      = nSubType;
/*N*/   pTmp->SetValue(GetValue());
/*N*/
/*N*/   return pTmp;
/*N*/ }

//STRIP001 /*N*/ String SwDBField::GetCntnt(BOOL bName) const
//STRIP001 /*N*/ {
//STRIP001 /*N*/    if(bName)
//STRIP001 /*N*/   {
//STRIP001 /*?*/       const String& rDBName = ((SwDBFieldType*)GetTyp())->GetName();
//STRIP001 /*?*/       String sContent( SFX_APP()->LocalizeDBName(INI2NATIONAL,
//STRIP001 /*?*/                                           rDBName.GetToken(0, DB_DELIM)));
//STRIP001 /*?*/
//STRIP001 /*?*/       if (sContent.Len() > 1)
//STRIP001 /*?*/       {
//STRIP001 /*?*/           sContent += DB_DELIM;
//STRIP001 /*?*/           sContent += rDBName.GetToken(1, DB_DELIM);
//STRIP001 /*?*/           sContent += DB_DELIM;
//STRIP001 /*?*/           sContent += rDBName.GetToken(2, DB_DELIM);
//STRIP001 /*?*/       }
//STRIP001 /*?*/       return lcl_DBTrennConv(sContent);
//STRIP001 /*N*/    }
//STRIP001 /*N*/    return Expand();
//STRIP001 /*N*/ }

//------------------------------------------------------------------------------

void SwDBField::ChgValue( double d, BOOL bVal )
{
    bValidValue = bVal;
    SetValue(d);

    if( bValidValue )
        aContent = ((SwValueFieldType*)GetTyp())->ExpandValue(d, GetFormat(), GetLanguage());
}

/*--------------------------------------------------------------------
    Beschreibung:
 --------------------------------------------------------------------*/

SwFieldType* SwDBField::ChgTyp( SwFieldType* pNewType )
{
    SwFieldType* pOld = SwValueField::ChgTyp( pNewType );

    ((SwDBFieldType*)pNewType)->AddRef();
    ((SwDBFieldType*)pOld)->ReleaseRef();

    return pOld;
}

/*--------------------------------------------------------------------
    Beschreibung: Aktuellen Field-Value holen und chachen
 --------------------------------------------------------------------*/

/*N*/ void SwDBField::Evaluate()
 /*N*/ {    DBG_ERROR("STRIP")
//STRIP001 /*N*/    SwNewDBMgr* pMgr = GetDoc()->GetNewDBMgr();
//STRIP001 /*N*/
//STRIP001 /*N*/    // erstmal loeschen
//STRIP001 /*N*/    bValidValue = FALSE;
//STRIP001 /*N*/    double nValue = DBL_MAX;
//STRIP001 /*N*/    const SwDBData& aTmpData = GetDBData();
//STRIP001 /*N*/
//STRIP001 /*N*/     if(!pMgr || !pMgr->IsDataSourceOpen(aTmpData.sDataSource, aTmpData.sCommand, sal_True))
//STRIP001 /*N*/        return ;
//STRIP001 /*N*/
//STRIP001 /*N*/    ULONG nFmt;
//STRIP001 /*?*/
//STRIP001 /*?*/    // Passenden Spaltennamen suchen
//STRIP001 /*?*/   String aColNm( ((SwDBFieldType*)GetTyp())->GetColumnName() );
//STRIP001 /*?*/
//STRIP001 /*?*/   SvNumberFormatter* pDocFormatter = GetDoc()->GetNumberFormatter();
//STRIP001 /*?*/   pMgr->GetMergeColumnCnt(aColNm, GetLanguage(), aContent, &nValue, &nFmt);
//STRIP001 /*?*/   if( !( nSubType & SUB_OWN_FMT ) )
//STRIP001 /*?*/       SetFormat( nFmt = pMgr->GetColumnFmt( aTmpData.sDataSource, aTmpData.sCommand,
//STRIP001 /*?*/                                       aColNm, pDocFormatter, GetLanguage() ));
//STRIP001 /*?*/
//STRIP001 /*?*/   if( DBL_MAX != nValue )
//STRIP001 /*?*/   {
//STRIP001 /*?*/       sal_Int32 nColumnType = pMgr->GetColumnType(aTmpData.sDataSource, aTmpData.sCommand, aColNm);
//STRIP001 /*?*/       if( DataType::DATE == nColumnType  || DataType::TIME == nColumnType  ||
//STRIP001 /*?*/                  DataType::TIMESTAMP  == nColumnType)
//STRIP001 /*?*/
//STRIP001 /*?*/       {
//STRIP001 /*?*/           Date aStandard(1,1,1900);
//STRIP001 /*?*/           if (*pDocFormatter->GetNullDate() != aStandard)
//STRIP001 /*?*/               nValue += (aStandard - *pDocFormatter->GetNullDate());
//STRIP001 /*?*/       }
//STRIP001 /*?*/       bValidValue = TRUE;
//STRIP001 /*?*/       SetValue(nValue);
//STRIP001 /*?*/       aContent = ((SwValueFieldType*)GetTyp())->ExpandValue(nValue, GetFormat(), GetLanguage());
//STRIP001 /*?*/   }
//STRIP001 /*?*/   else
//STRIP001 /*?*/   {
//STRIP001 /*?*/       SwSbxValue aVal;
//STRIP001 /*?*/       aVal.PutString( aContent );
//STRIP001 /*?*/
//STRIP001 /*?*/       if (aVal.IsNumeric())
//STRIP001 /*?*/       {
//STRIP001 /*?*/           SetValue(aVal.GetDouble());
//STRIP001 /*?*/
//STRIP001 /*?*/           SvNumberFormatter* pFormatter = GetDoc()->GetNumberFormatter();
//STRIP001 /*?*/           if (nFmt && nFmt != ULONG_MAX && !pFormatter->IsTextFormat(nFmt))
//STRIP001 /*?*/               bValidValue = TRUE; // Wegen Bug #60339 nicht mehr bei allen Strings
//STRIP001 /*?*/       }
//STRIP001 /*?*/       else
//STRIP001 /*?*/       {
//STRIP001 /*?*/           // Bei Strings TRUE wenn Laenge > 0 sonst FALSE
//STRIP001 /*?*/           SetValue(aContent.Len() ? 1 : 0);
//STRIP001 /*?*/       }
//STRIP001 /*?*/   }
//STRIP001 /*?*/   bInitialized = TRUE;
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung: Namen erfragen
 --------------------------------------------------------------------*/

const String& SwDBField::GetPar1() const
{
    return ((SwDBFieldType*)GetTyp())->GetName();
}

/*--------------------------------------------------------------------
    Beschreibung:
 --------------------------------------------------------------------*/

/*N*/ USHORT SwDBField::GetSubType() const
/*N*/ {
/*N*/   return nSubType;
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung:
 --------------------------------------------------------------------*/

/*N*/ void SwDBField::SetSubType(USHORT nType)
/*N*/ {
/*N*/   nSubType = nType;
/*N*/ }

/*-----------------06.03.98 16:15-------------------

--------------------------------------------------*/
/*N*/ BOOL SwDBField::QueryValue( ::com::sun::star::uno::Any& rAny, BYTE nMId ) const
/*N*/ {
/*N*/     nMId &= ~CONVERT_TWIPS;
/*N*/   switch( nMId )
/*N*/   {
/*N*/   case FIELD_PROP_BOOL1:
/*N*/       {
/*N*/           BOOL bTemp = 0 == (GetSubType()&SUB_OWN_FMT);
/*N*/           rAny.setValue(&bTemp, ::getBooleanCppuType());
/*N*/       }
/*N*/       break;
/*N*/     case FIELD_PROP_BOOL2:
/*N*/     {
/*N*/         sal_Bool bVal = 0 == (GetSubType() & SUB_INVISIBLE);
/*N*/         rAny.setValue(&bVal, ::getBooleanCppuType());
/*N*/     }
/*N*/     break;
/*N*/   case FIELD_PROP_FORMAT:
/*N*/       rAny <<= (sal_Int32)GetFormat();
/*N*/       break;
/*N*/   case FIELD_PROP_PAR1:
/*?*/       rAny <<= OUString(aContent);
/*?*/       break;
/*?*/   default:
/*?*/       DBG_ERROR("illegal property");
/*N*/   }
/*N*/   return TRUE;
/*N*/
/*N*/ }
/*-----------------06.03.98 16:15-------------------

--------------------------------------------------*/
/*N*/ BOOL SwDBField::PutValue( const ::com::sun::star::uno::Any& rAny, BYTE nMId )
/*N*/ {
/*N*/     nMId &= ~CONVERT_TWIPS;
/*N*/   switch( nMId )
/*N*/   {
/*N*/   case FIELD_PROP_BOOL1:
/*N*/       if( *(sal_Bool*)rAny.getValue() )
/*N*/           SetSubType(GetSubType()&~SUB_OWN_FMT);
/*N*/       else
/*N*/           SetSubType(GetSubType()|SUB_OWN_FMT);
/*N*/       break;
/*N*/     case FIELD_PROP_BOOL2:
/*N*/     {
/*N*/         USHORT nSubType = GetSubType();
/*N*/         sal_Bool bVisible;
/*N*/         if(!(rAny >>= bVisible))
/*N*/             return FALSE;
/*N*/         if(bVisible)
/*N*/             nSubType &= ~SUB_INVISIBLE;
/*N*/         else
/*N*/             nSubType |= SUB_INVISIBLE;
/*N*/         SetSubType(nSubType);
/*N*/         //invalidate text node
/*N*/         if(GetTyp())
/*N*/         {
/*N*/             SwClientIter aIter( *GetTyp() );
/*N*/             SwFmtFld* pFld = (SwFmtFld*)aIter.First( TYPE( SwFmtFld ));
/*N*/             while(pFld)
/*N*/             {
/*N*/                 SwTxtFld *pTxtFld = pFld->GetTxtFld();
/*N*/                 if(pTxtFld && (SwDBField*)pFld->GetFld() == this )
/*N*/                 {
/*N*/                     //notify the change
/*N*/                     pTxtFld->NotifyContentChange(*pFld);
/*N*/                     break;
/*N*/                 }
/*N*/                 pFld = (SwFmtFld*)aIter.Next();
/*N*/             }
/*N*/         }
/*N*/     }
/*N*/     break;
/*N*/   case FIELD_PROP_FORMAT:
/*N*/       {
/*N*/           sal_Int32 nTemp;
/*N*/           rAny >>= nTemp;
/*N*/           SetFormat(nTemp);
/*N*/       }
/*N*/       break;
/*N*/   case FIELD_PROP_PAR1:
/*N*/       ::binfilter::GetString( rAny, aContent );
/*N*/       break;
/*N*/   default:
/*?*/       DBG_ERROR("illegal property");
/*N*/   }
/*N*/   return TRUE;
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung: Basisklasse fuer alle weiteren Datenbankfelder
 --------------------------------------------------------------------*/

/*N*/ SwDBNameInfField::SwDBNameInfField(SwFieldType* pTyp, const SwDBData& rDBData, ULONG nFmt) :
/*N*/   SwField(pTyp, nFmt),
/*N*/     aDBData(rDBData),
/*N*/     nSubType(0)
/*N*/ {
/*N*/ }

//------------------------------------------------------------------------------

/*N*/ SwDBData SwDBNameInfField::GetDBData(SwDoc* pDoc)
/*N*/ {
/*N*/   SwDBData aRet;
/*N*/   if(aDBData.sDataSource.getLength())
/*N*/       aRet = aDBData;
/*N*/   else
/*N*/       aRet = pDoc->GetDBData();
/*N*/   return aRet;
/*N*/ }

//------------------------------------------------------------------------------

//STRIP001 /*N*/ String SwDBNameInfField::GetCntnt(BOOL bName) const
//STRIP001 /*N*/ {
//STRIP001 /*N*/    String sStr(SwField::GetCntnt(bName));
//STRIP001 /*N*/
//STRIP001 /*N*/    if(bName)
//STRIP001 /*N*/    {
//STRIP001 /*?*/        if (aDBData.sDataSource.getLength())
//STRIP001 /*?*/        {
//STRIP001 /*?*/            sStr += ':';
//STRIP001 /*?*/            sStr += String(aDBData.sDataSource);
//STRIP001 /*?*/            sStr += DB_DELIM;
//STRIP001 /*?*/            sStr += String(aDBData.sCommand);
//STRIP001 /*?*/        }
//STRIP001 /*N*/    }
//STRIP001 /*N*/    return lcl_DBTrennConv(sStr);
//STRIP001 /*N*/ }
//STRIP001
/*-----------------06.03.98 16:55-------------------

--------------------------------------------------*/
/*N*/ BOOL SwDBNameInfField::QueryValue( ::com::sun::star::uno::Any& rAny, BYTE nMId ) const
/*N*/ {
/*N*/     nMId &= ~CONVERT_TWIPS;
/*N*/   switch( nMId )
/*N*/   {
/*N*/   case FIELD_PROP_PAR1:
/*N*/       rAny <<= aDBData.sDataSource;
/*N*/       break;
/*N*/   case FIELD_PROP_PAR2:
/*N*/       rAny <<= aDBData.sCommand;
/*N*/       break;
/*N*/   case FIELD_PROP_SHORT1:
/*N*/       rAny <<= aDBData.nCommandType;
/*N*/       break;
/*N*/     case FIELD_PROP_BOOL2:
/*N*/     {
/*N*/         sal_Bool bVal = 0 == (GetSubType() & SUB_INVISIBLE);
/*N*/         rAny.setValue(&bVal, ::getBooleanCppuType());
/*N*/     }
/*N*/     break;
/*N*/   default:
/*?*/       DBG_ERROR("illegal property");
/*N*/   }
/*N*/   return TRUE;
/*N*/ }
/*-----------------06.03.98 16:55-------------------

--------------------------------------------------*/
BOOL SwDBNameInfField::PutValue( const ::com::sun::star::uno::Any& rAny, BYTE nMId )
{
    nMId &= ~CONVERT_TWIPS;
    switch( nMId )
    {
    case FIELD_PROP_PAR1:
        rAny >>= aDBData.sDataSource;
        break;
    case FIELD_PROP_PAR2:
        rAny >>= aDBData.sCommand;
        break;
    case FIELD_PROP_SHORT1:
        rAny >>= aDBData.nCommandType;
        break;
    case FIELD_PROP_BOOL2:
    {
        USHORT nSubType = GetSubType();
        sal_Bool bVisible;
        if(!(rAny >>= bVisible))
            return FALSE;
        if(bVisible)
            nSubType &= ~SUB_INVISIBLE;
        else
            nSubType |= SUB_INVISIBLE;
        SetSubType(nSubType);
    }
    break;
    default:
        DBG_ERROR("illegal property");
    }
    return TRUE;
}
/* -----------------4/10/2003 15:03------------------

 --------------------------------------------------*/
/*N*/ USHORT SwDBNameInfField::GetSubType() const
/*N*/ {
/*N*/     return nSubType;
/*N*/ }
/* -----------------4/10/2003 15:03------------------

 --------------------------------------------------*/
/*N*/ void SwDBNameInfField::SetSubType(USHORT nType)
/*N*/ {
/*N*/     nSubType = nType;
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung: NaechsterDatensatz
 --------------------------------------------------------------------*/

/*N*/ SwDBNextSetFieldType::SwDBNextSetFieldType()
/*N*/   : SwFieldType( RES_DBNEXTSETFLD )
/*N*/ {
/*N*/ }

//------------------------------------------------------------------------------

/*N*/ SwFieldType* SwDBNextSetFieldType::Copy() const
/*N*/ {
            SwDBNextSetFieldType* pTmp = new SwDBNextSetFieldType();
            return pTmp;
/*N*/ }
/*--------------------------------------------------------------------
    Beschreibung: SwDBSetField
 --------------------------------------------------------------------*/

/*N*/ SwDBNextSetField::SwDBNextSetField(SwDBNextSetFieldType* pTyp,
/*N*/                                  const String& rCond,
/*N*/                                  const String& rDummy,
/*N*/                                  const SwDBData& rDBData) :
/*N*/   SwDBNameInfField(pTyp, rDBData), aCond(rCond), bCondValid(TRUE)
/*N*/ {}

//------------------------------------------------------------------------------

/*N*/ String SwDBNextSetField::Expand() const
/*N*/ {
/*N*/   return aEmptyStr;
/*N*/ }

//------------------------------------------------------------------------------

/*N*/ SwField* SwDBNextSetField::Copy() const
/*N*/ {
/*N*/   SwDBNextSetField *pTmp = new SwDBNextSetField((SwDBNextSetFieldType*)GetTyp(),
/*N*/                                        aCond, aEmptyStr, GetDBData());
/*N*/     pTmp->SetSubType(GetSubType());
/*N*/   pTmp->bCondValid = bCondValid;
/*N*/   return pTmp;
/*N*/ }
//------------------------------------------------------------------------------

/*N*/ void SwDBNextSetField::Evaluate(SwDoc* pDoc)
/*N*/ {
/*N*/   SwNewDBMgr* pMgr = pDoc->GetNewDBMgr();
/*N*/   const SwDBData& rData = GetDBData();
/*N*/   if( !bCondValid ||
/*N*/             !pMgr || !pMgr->IsDataSourceOpen(rData.sDataSource, rData.sCommand, sal_False))
/*N*/       return ;
/*N*/     pMgr->ToNextRecord(rData.sDataSource, rData.sCommand);
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung: Bedingung
 --------------------------------------------------------------------*/

/*N*/ const String& SwDBNextSetField::GetPar1() const
/*N*/ {
/*N*/   return aCond;
/*N*/ }

void SwDBNextSetField::SetPar1(const String& rStr)
{
    aCond = rStr;
}
/*-----------------06.03.98 16:16-------------------

--------------------------------------------------*/
/*N*/ BOOL SwDBNextSetField::QueryValue( uno::Any& rAny, BYTE nMId ) const
/*N*/ {
/*N*/     nMId &= ~CONVERT_TWIPS;
/*N*/   BOOL bRet = TRUE;
/*N*/   switch( nMId )
/*N*/   {
/*N*/   case FIELD_PROP_PAR3:
/*N*/       rAny <<= OUString(aCond);
/*N*/       break;
/*N*/   default:
/*N*/       bRet = SwDBNameInfField::QueryValue( rAny, nMId );
/*N*/   }
/*N*/   return bRet;
/*N*/ }
/*-----------------06.03.98 16:16-------------------

--------------------------------------------------*/
BOOL SwDBNextSetField::PutValue( const ::com::sun::star::uno::Any& rAny, BYTE nMId )
{
    nMId &= ~CONVERT_TWIPS;
    BOOL bRet = TRUE;
    switch( nMId )
    {
    case FIELD_PROP_PAR3:
        ::binfilter::GetString( rAny, aCond );
        break;
    default:
        bRet = SwDBNameInfField::PutValue( rAny, nMId );
    }
    return bRet;
}

/*--------------------------------------------------------------------
    Beschreibung:
 --------------------------------------------------------------------*/
/*
String SwDBNextSetField::GetPar2() const
{
    return GetDBName();
}

void SwDBNextSetField::SetPar2(const String& rStr)
{
    GetDBName() = rStr;
}
*/

/*--------------------------------------------------------------------
    Beschreibung: Datensatz mit bestimmter ID
 --------------------------------------------------------------------*/

/*N*/ SwDBNumSetFieldType::SwDBNumSetFieldType() :
/*N*/   SwFieldType( RES_DBNUMSETFLD )
/*N*/ {
/*N*/ }

//------------------------------------------------------------------------------

/*N*/ SwFieldType* SwDBNumSetFieldType::Copy() const
/*N*/ {
        SwDBNumSetFieldType* pTmp = new SwDBNumSetFieldType();
        return pTmp;
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung: SwDBSetField
 --------------------------------------------------------------------*/

/*N*/ SwDBNumSetField::SwDBNumSetField(SwDBNumSetFieldType* pTyp,
/*N*/                                const String& rCond,
/*N*/                                const String& rDBNum,
/*N*/                                const SwDBData& rDBData) :
/*N*/   SwDBNameInfField(pTyp, rDBData),
/*N*/   aCond(rCond),
/*N*/   aPar2(rDBNum),
/*N*/   bCondValid(TRUE)
/*N*/ {}

//------------------------------------------------------------------------------

/*N*/ String SwDBNumSetField::Expand() const
/*N*/ {
/*N*/   return aEmptyStr;
/*N*/ }

//------------------------------------------------------------------------------

/*N*/ SwField* SwDBNumSetField::Copy() const
/*N*/ {
/*N*/   SwDBNumSetField *pTmp = new SwDBNumSetField((SwDBNumSetFieldType*)GetTyp(),
/*N*/                                        aCond, aPar2, GetDBData());
/*N*/   pTmp->bCondValid = bCondValid;
/*N*/     pTmp->SetSubType(GetSubType());
/*N*/   return pTmp;
/*N*/ }

/*N*/ void SwDBNumSetField::Evaluate(SwDoc* pDoc)
/*N*/ {
/*N*/   SwNewDBMgr* pMgr = pDoc->GetNewDBMgr();
/*N*/   const SwDBData& aTmpData = GetDBData();
/*N*/
/*N*/   if( bCondValid && pMgr && pMgr->IsInMerge() &&
/*N*/                         pMgr->IsDataSourceOpen(aTmpData.sDataSource, aTmpData.sCommand, sal_True))
/*N*/   {   // Bedingug OK -> aktuellen Set einstellen
/*N*/       pMgr->ToRecordId(Max((USHORT)aPar2.ToInt32(), USHORT(1))-1);
/*N*/   }
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung: LogDBName
 --------------------------------------------------------------------*/

/*N*/ const String& SwDBNumSetField::GetPar1() const
/*N*/ {
/*N*/   return aCond;
/*N*/ }

void SwDBNumSetField::SetPar1(const String& rStr)
{
    aCond = rStr;
}

/*--------------------------------------------------------------------
    Beschreibung: Bedingung
 --------------------------------------------------------------------*/

/*N*/ String SwDBNumSetField::GetPar2() const
/*N*/ {
/*N*/   return aPar2;
/*N*/ }

void SwDBNumSetField::SetPar2(const String& rStr)
{
    aPar2 = rStr;
}
/*-----------------06.03.98 16:16-------------------

--------------------------------------------------*/
/*N*/ BOOL SwDBNumSetField::QueryValue( ::com::sun::star::uno::Any& rAny, BYTE nMId ) const
/*N*/ {
/*N*/     nMId &= ~CONVERT_TWIPS;
/*N*/   BOOL bRet = TRUE;
/*N*/   switch( nMId )
/*N*/   {
/*N*/   case FIELD_PROP_PAR3:
/*N*/       rAny <<= OUString(aCond);
/*N*/       break;
/*N*/   case FIELD_PROP_FORMAT:
/*N*/       rAny <<= (sal_Int32)aPar2.ToInt32();
/*N*/       break;
/*N*/   default:
/*N*/       bRet = SwDBNameInfField::QueryValue(rAny, nMId );
/*N*/   }
/*N*/   return bRet;
/*N*/ }
/*-----------------06.03.98 16:16-------------------

--------------------------------------------------*/
BOOL    SwDBNumSetField::PutValue( const ::com::sun::star::uno::Any& rAny, BYTE nMId )
{
    nMId &= ~CONVERT_TWIPS;
    BOOL bRet = TRUE;
    switch( nMId )
    {
    case FIELD_PROP_PAR3:
        ::binfilter::GetString( rAny, aCond );
        break;
    case FIELD_PROP_FORMAT:
        {
            sal_Int32 nVal;
            rAny >>= nVal;
            aPar2 = String::CreateFromInt32(nVal);
        }
        break;
    default:
        bRet = SwDBNameInfField::PutValue(rAny, nMId );
    }
    return bRet;
}

/*--------------------------------------------------------------------
    Beschreibung: SwDBNameFieldType
 --------------------------------------------------------------------*/

/*N*/ SwDBNameFieldType::SwDBNameFieldType(SwDoc* pDocument)
/*N*/   : SwFieldType( RES_DBNAMEFLD )
/*N*/ {
/*N*/   pDoc = pDocument;
/*N*/ }
//------------------------------------------------------------------------------

/*N*/ String SwDBNameFieldType::Expand(ULONG nFmt) const
/*N*/ {
/*N*/   ASSERT( nFmt >= FF_BEGIN && nFmt < FF_END, "Expand: kein guelt. Fmt!" );
/*N*/   const SwDBData aData = pDoc->GetDBData();
/*N*/   String sRet(aData.sDataSource);
/*N*/   sRet += '.';
/*N*/   sRet += (String)aData.sCommand;
/*N*/   return sRet;
/*N*/ }
//------------------------------------------------------------------------------

/*N*/ SwFieldType* SwDBNameFieldType::Copy() const
/*N*/ {
        SwDBNameFieldType *pTmp = new SwDBNameFieldType(pDoc);
        return pTmp;
/*N*/ }

//------------------------------------------------------------------------------

/*--------------------------------------------------------------------
    Beschreibung: Name der angedockten DB
 --------------------------------------------------------------------*/

/*N*/ SwDBNameField::SwDBNameField(SwDBNameFieldType* pTyp, const SwDBData& rDBData, ULONG nFmt)
/*N*/   : SwDBNameInfField(pTyp, rDBData, nFmt)
/*N*/ {}

//------------------------------------------------------------------------------

/*N*/ String SwDBNameField::Expand() const
/*N*/ {
/*N*/     String sRet;
/*N*/     if(0 ==(GetSubType() & SUB_INVISIBLE))
/*N*/         sRet = ((SwDBNameFieldType*)GetTyp())->Expand(GetFormat());
/*N*/     return sRet;
/*N*/ }

//------------------------------------------------------------------------------

/*N*/ SwField* SwDBNameField::Copy() const
/*N*/ {
/*N*/   SwDBNameField *pTmp = new SwDBNameField((SwDBNameFieldType*)GetTyp(), GetDBData());
/*N*/   pTmp->ChangeFormat(GetFormat());
/*N*/   pTmp->SetLanguage(GetLanguage());
/*N*/     pTmp->SetSubType(GetSubType());
/*N*/   return pTmp;
/*N*/ }

/*-----------------06.03.98 16:16-------------------

--------------------------------------------------*/
/*N*/ BOOL SwDBNameField::QueryValue( ::com::sun::star::uno::Any& rAny, BYTE nMId ) const
/*N*/ {
/*N*/   return SwDBNameInfField::QueryValue(rAny, nMId );
/*N*/ }
/*-----------------06.03.98 16:16-------------------

--------------------------------------------------*/
BOOL SwDBNameField::PutValue( const ::com::sun::star::uno::Any& rAny, BYTE nMId )
{
    return SwDBNameInfField::PutValue(rAny, nMId );
}
/*--------------------------------------------------------------------
    Beschreibung: SwDBNameFieldType
 --------------------------------------------------------------------*/

/*N*/ SwDBSetNumberFieldType::SwDBSetNumberFieldType()
/*N*/   : SwFieldType( RES_DBSETNUMBERFLD )
/*N*/ {
/*N*/ }

//------------------------------------------------------------------------------

/*N*/ SwFieldType* SwDBSetNumberFieldType::Copy() const
/*N*/ {
        SwDBSetNumberFieldType *pTmp = new SwDBSetNumberFieldType;
        return pTmp;
/*N*/ }

//------------------------------------------------------------------------------

/*--------------------------------------------------------------------
    Beschreibung: SetNumber der angedockten DB
 --------------------------------------------------------------------*/

/*N*/ SwDBSetNumberField::SwDBSetNumberField(SwDBSetNumberFieldType* pTyp,
/*N*/                                      const SwDBData& rDBData,
/*N*/                                      ULONG nFmt)
/*N*/   : SwDBNameInfField(pTyp, rDBData, nFmt), nNumber(0)
/*N*/ {}

//------------------------------------------------------------------------------

/*N*/ String SwDBSetNumberField::Expand() const
/*N*/ {
/*N*/     if(0 !=(GetSubType() & SUB_INVISIBLE) || nNumber == 0)
/*?*/       return aEmptyStr;
/*N*/   else
/*N*/       return FormatNumber((USHORT)nNumber, GetFormat());
/*N*/   //return(nNumber == 0 ? aEmptyStr : FormatNumber(nNumber, GetFormat()));
/*N*/ }

//------------------------------------------------------------------------------

/*N*/ void SwDBSetNumberField::Evaluate(SwDoc* pDoc)
/*N*/ {
/*N*/   SwNewDBMgr* pMgr = pDoc->GetNewDBMgr();
/*N*/
/*N*/     const SwDBData& aTmpData = GetDBData();
/*N*/     if (!pMgr || !pMgr->IsInMerge() ||
/*N*/         !pMgr->IsDataSourceOpen(aTmpData.sDataSource, aTmpData.sCommand, sal_False))
/*N*/         return;
/*N*/     nNumber = pMgr->GetSelectedRecordId();
/*N*/ }


//------------------------------------------------------------------------------

/*N*/ SwField* SwDBSetNumberField::Copy() const
/*N*/ {
/*N*/   SwDBSetNumberField *pTmp =
/*N*/       new SwDBSetNumberField((SwDBSetNumberFieldType*)GetTyp(), GetDBData(), GetFormat());
/*N*/   pTmp->SetLanguage(GetLanguage());
/*N*/   pTmp->SetSetNumber(nNumber);
/*N*/     pTmp->SetSubType(GetSubType());
/*N*/   return pTmp;
/*N*/ }
/*-----------------06.03.98 16:15-------------------

--------------------------------------------------*/
/*N*/ BOOL SwDBSetNumberField::QueryValue( ::com::sun::star::uno::Any& rAny, BYTE nMId ) const
/*N*/ {
/*N*/   BOOL bRet = TRUE;
/*N*/     nMId &= ~CONVERT_TWIPS;
/*N*/   switch( nMId )
/*N*/   {
/*N*/   case FIELD_PROP_USHORT1:
/*N*/       rAny <<= (sal_Int16)GetFormat();
/*N*/       break;
/*N*/   case FIELD_PROP_FORMAT:
/*N*/       rAny <<= nNumber;
/*N*/       break;
/*N*/   default:
/*N*/       bRet = SwDBNameInfField::QueryValue( rAny, nMId );
/*N*/   }
/*N*/   return bRet;
/*N*/ }
/*-----------------06.03.98 16:15-------------------

--------------------------------------------------*/
BOOL SwDBSetNumberField::PutValue( const ::com::sun::star::uno::Any& rAny, BYTE nMId )
{
    BOOL bRet = TRUE;
    nMId &= ~CONVERT_TWIPS;
    switch( nMId )
    {
    case FIELD_PROP_USHORT1:
        {
            sal_Int16 nSet;
            rAny >>= nSet;
            if(nSet < (INT16) SVX_NUMBER_NONE )
                SetFormat(nSet);
            else
                //exception(wrong_value)
                ;
        }
        break;
    case FIELD_PROP_FORMAT:
        rAny >>= nNumber;
        break;
    default:
        bRet = SwDBNameInfField::PutValue( rAny, nMId );
    }
    return bRet;
}


}
