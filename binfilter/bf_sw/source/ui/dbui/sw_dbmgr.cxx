/*************************************************************************
 *
 *  $RCSfile: sw_dbmgr.cxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:20:15 $
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

#if STLPORT_VERSION>=321
#include <cstdarg>
#endif

#include <stdio.h>

#include <com/sun/star/text/NotePrintMode.hpp>

#ifndef _COM_SUN_STAR_SDB_COMMANDTYPE_HPP_
#include <com/sun/star/sdb/CommandType.hpp>
#endif
#ifndef _COM_SUN_STAR_FRAME_XCOMPONENTLOADER_HPP_
#include <com/sun/star/frame/XComponentLoader.hpp>
#endif
#ifndef _COM_SUN_STAR_UTIL_iXNUMBERFORMATTER_HPP_
#include <com/sun/star/util/XNumberFormatter.hpp>
#endif
#ifndef _COM_SUN_STAR_SDB_XCOMPLETEDCONNECTION_HPP_
#include <com/sun/star/sdb/XCompletedConnection.hpp>
#endif
#ifndef _COM_SUN_STAR_SDB_XCOMPLETEDEXECUTION_HPP_
#include <com/sun/star/sdb/XCompletedExecution.hpp>
#endif
#ifndef _COM_SUN_STAR_CONTAINER_XCHILD_HPP_
#include <com/sun/star/container/XChild.hpp>
#endif
#ifndef _COM_SUN_STAR_TEXT_MAILMERGEEVENT_
#include <com/sun/star/text/MailMergeEvent.hpp>
#endif
#ifndef _SFXVIEWFRM_HXX
#include <bf_sfx2/viewfrm.hxx>
#endif
#ifndef _DBCONFIG_HXX
#include <dbconfig.hxx>
#endif
#ifndef _SWDBTOOLSCLIENT_HXX
#include <swdbtoolsclient.hxx>
#endif
#ifndef _LSTBOX_HXX //autogen
#include <vcl/lstbox.hxx>
#endif
#ifndef _UNOTOOLS_TEMPFILE_HXX
#include <unotools/tempfile.hxx>
#endif
#ifndef SVTOOLS_URIHELPER_HXX
#include <svtools/urihelper.hxx>
#endif
#ifndef _SVSTDARR_HXX
#define _SVSTDARR_STRINGSDTOR
#include <svtools/svstdarr.hxx>
#endif
#ifndef _ZFORLIST_HXX //autogen
#include <svtools/zforlist.hxx>
#endif
#ifndef _ZFORMAT_HXX //autogen
#include <svtools/zformat.hxx>
#endif
#ifndef _SFXSTRITEM_HXX //autogen
#include <svtools/stritem.hxx>
#endif
#ifndef _SFXENUMITEM_HXX //autogen
#include <svtools/eitem.hxx>
#endif
#ifndef _SFX_PRINTER_HXX //autogen
#include <bf_sfx2/printer.hxx>
#endif
#ifndef _SFXDOCFILE_HXX //autogen
#include <bf_sfx2/docfile.hxx>
#endif
#ifndef _SFX_PROGRESS_HXX //autogen
#include <bf_sfx2/progress.hxx>
#endif
#ifndef _SFX_DOCFILT_HACK_HXX //autogen
#include <bf_sfx2/docfilt.hxx>
#endif
#ifndef _SFXDISPATCH_HXX //autogen
#include <bf_sfx2/dispatch.hxx>
#endif
#ifndef _OFF_APP_HXX //autogen
#include <bf_offmgr/app.hxx>
#endif
#ifndef _MAILENUM_HXX //autogen
#include <goodies/mailenum.hxx>
#endif
#include <cmdid.h>
#ifndef _SWTYPES_HXX
#include <swtypes.hxx>
#endif
#ifndef _SWMODULE_HXX
#include <swmodule.hxx>
#endif
#ifndef _VIEW_HXX
#include <view.hxx>
#endif
#ifndef _DOCSH_HXX
#include <docsh.hxx>
#endif
#ifndef _EDTWIN_HXX
#include <edtwin.hxx>
#endif
#ifndef _DBINSDLG_HXX
#include <dbinsdlg.hxx>
#endif
#ifndef _WRTSH_HXX
#include <wrtsh.hxx>
#endif
#ifndef _FLDBAS_HXX
#include <fldbas.hxx>
#endif
#ifndef _INITUI_HXX
#include <initui.hxx>
#endif
#ifndef _SWUNDO_HXX
#include <swundo.hxx>
#endif
#ifndef _FLDDAT_HXX
#include <flddat.hxx>
#endif
#ifndef _SWMODULE_HXX
#include <swmodule.hxx>
#endif
#ifndef _MODCFG_HXX
#include <modcfg.hxx>
#endif
#ifndef _SWPRTOPT_HXX
#include <swprtopt.hxx>
#endif
#ifndef _SHELLIO_HXX
#include <shellio.hxx>
#endif
#ifndef _DBUI_HXX
#include <dbui.hxx>
#endif
#ifndef _DBMGR_HXX
#include <dbmgr.hxx>
#endif
#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _SWWAIT_HXX
#include <swwait.hxx>
#endif
#ifndef _SWUNOHELPER_HXX
#include <swunohelper.hxx>
#endif

#ifndef _DBUI_HRC
#include <dbui.hrc>
#endif
#ifndef _GLOBALS_HRC
#include <globals.hrc>
#endif
#ifndef _STATSTR_HRC
#include <statstr.hrc>
#endif

#ifndef _SFXREQUEST_HXX
#include <bf_sfx2/request.hxx>
#endif
#ifndef _HINTIDS_HXX
#include <hintids.hxx>
#endif
#ifndef _COM_SUN_STAR_LANG_XMULTISERVICEFACTORY_HPP_
#include <com/sun/star/lang/XMultiServiceFactory.hpp>
#endif
#ifndef _COM_SUN_STAR_CONTAINER_XNAMEACCESS_HPP_
#include <com/sun/star/container/XNameAccess.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBC_XDATASOURCE_HPP_
#include <com/sun/star/sdbc/XDataSource.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBC_XROWSET_HPP_
#include <com/sun/star/sdbc/XRowSet.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBCX_XTABLESSUPPLIER_HPP_
#include <com/sun/star/sdbcx/XTablesSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBCX_XCOLUMNSSUPPLIER_HPP_
#include <com/sun/star/sdbcx/XColumnsSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_SDB_XQUERIESSUPPLIER_HPP_
#include <com/sun/star/sdb/XQueriesSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_SDB_XCOLUMN_HPP_
#include <com/sun/star/sdb/XColumn.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBC_DATATYPE_HPP_
#include <com/sun/star/sdbc/DataType.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBC_XSTATEMENT_HPP_
#include <com/sun/star/sdbc/XStatement.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBC_RESULTSETTYPE_HPP_
#include <com/sun/star/sdbc/ResultSetType.hpp>
#endif
#ifndef _COM_SUN_STAR_BEANS_XPROPERTYSET_HPP_
#include <com/sun/star/beans/XPropertySet.hpp>
#endif
#ifndef _COM_SUN_STAR_BEANS_PROPERTYVALUE_HPP_
#include <com/sun/star/beans/PropertyValue.hpp>
#endif
#ifndef _COMPHELPER_PROCESSFACTORY_HXX_
#include <comphelper/processfactory.hxx>
#endif
#ifndef _ISOLANG_HXX
#include <tools/isolang.hxx>
#endif
#ifndef _COM_SUN_STAR_UTIL_XNUMBERFORMATTYPES_HPP_
#include <com/sun/star/util/XNumberFormatTypes.hpp>
#endif
#ifndef _SVX_LANGITEM_HXX
#include <bf_svx/langitem.hxx>
#endif
#ifndef _SVX_UNOMID_HXX
#include <bf_svx/unomid.hxx>
#endif
#ifndef _NUMUNO_HXX
#include <svtools/numuno.hxx>
#endif

#include "mailmrge.hxx"
#include <unomailmerge.hxx>

#ifndef _SFXEVENT_HXX
#include <bf_sfx2/event.hxx>
#endif
#ifndef _SV_MSGBOX_HXX
#include <vcl/msgbox.hxx>
#endif
#ifndef _SVX_DATACCESSDESCRIPTOR_HXX_
#include <bf_svx/dataaccessdescriptor.hxx>
#endif
#ifndef _CPPUHELPER_IMPLBASE1_HXX_
#include <cppuhelper/implbase1.hxx>
#endif
#ifndef _VOS_MUTEX_HXX_
#include <vos/mutex.hxx>
#endif
#ifndef _LEGACYBINFILTERMGR_HXX
#include <legacysmgr/legacy_binfilters_smgr.hxx>    //STRIP002
#endif
using namespace svx;
using namespace ::com::sun::star;
using namespace com::sun::star::text;
using namespace com::sun::star::uno;
using namespace com::sun::star::container;
using namespace com::sun::star::frame;
using namespace com::sun::star::lang;
using namespace com::sun::star::sdb;
using namespace com::sun::star::sdbc;
using namespace com::sun::star::sdbcx;
using namespace com::sun::star::beans;
using namespace com::sun::star::util;
using namespace com::sun::star::task;

#define C2S(cChar) String::CreateFromAscii(cChar)
#define C2U(cChar) ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(cChar))

#define DB_SEP_SPACE    0
#define DB_SEP_TAB      1
#define DB_SEP_RETURN   2
#define DB_SEP_NEWLINE  3

/*N*/ SV_IMPL_PTRARR(SwDSParamArr, SwDSParamPtr);
const sal_Char cCursor[] = "Cursor";
const sal_Char cCommand[] = "Command";
const sal_Char cCommandType[] = "CommandType";
const sal_Char cDataSourceName[] = "DataSourceName";
const sal_Char cSelection[] = "Selection";
const sal_Char cActiveConnection[] = "ActiveConnection";

// -----------------------------------------------------------------------------
// Use nameless namespace to avoid to rubbish the global namespace
// -----------------------------------------------------------------------------
namespace
{

}
/* -----------------09.12.2002 12:35-----------------
 *
 * --------------------------------------------------*/

/*N*/ class SwConnectionDisposedListener_Impl : public cppu::WeakImplHelper1
/*N*/ < com::sun::star::lang::XEventListener >
/*N*/ {
/*N*/     SwNewDBMgr&     rDBMgr;
/*N*/
/*N*/     virtual void SAL_CALL disposing( const EventObject& Source ) throw (RuntimeException);
/*N*/ public:
/*N*/     SwConnectionDisposedListener_Impl(SwNewDBMgr& rMgr);
/*N*/     ~SwConnectionDisposedListener_Impl();
/*N*/
/*N*/ };
// -----------------------------------------------------------------------------
/*N*/ struct SwNewDBMgr_Impl
/*N*/ {
/*N*/     SwDSParam*          pMergeData;
/*N*/     SwMailMergeDlg*     pMergeDialog;
/*N*/     Reference<XEventListener> xDisposeListener;
/*N*/
/*N*/     SwNewDBMgr_Impl(SwNewDBMgr& rDBMgr)
/*N*/        :pMergeData(0)
/*N*/        ,pMergeDialog(0)
/*N*/        ,xDisposeListener(new SwConnectionDisposedListener_Impl(rDBMgr))
/*N*/         {}
/*N*/ };
/* -----------------------------17.07.00 17:04--------------------------------

 ---------------------------------------------------------------------------*/
//STRIP001 BOOL lcl_MoveAbsolute(SwDSParam* pParam, long nAbsPos)
//STRIP001 {
//STRIP001  BOOL bRet = FALSE;
//STRIP001  try
//STRIP001  {
//STRIP001      if(pParam->bScrollable)
//STRIP001      {
//STRIP001          bRet = pParam->xResultSet->absolute( nAbsPos );
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001             DBG_ERROR("no absolute positioning available")
//STRIP001         }
//STRIP001  }
//STRIP001  catch(Exception aExcept)
//STRIP001  {
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }
/* -----------------------------17.07.00 17:23--------------------------------

 ---------------------------------------------------------------------------*/
//STRIP001 BOOL lcl_GetColumnCnt(SwDSParam* pParam,
//STRIP001  const String& rColumnName, long nLanguage, String& rResult, double* pNumber)
//STRIP001 {
//STRIP001  Reference< XColumnsSupplier > xColsSupp( pParam->xResultSet, UNO_QUERY );
//STRIP001  Reference <XNameAccess> xCols = xColsSupp->getColumns();
//STRIP001  if(!xCols->hasByName(rColumnName))
//STRIP001      return FALSE;
//STRIP001  Any aCol = xCols->getByName(rColumnName);
//STRIP001  Reference< XPropertySet > xColumnProps;
//STRIP001     aCol >>= xColumnProps;
//STRIP001
//STRIP001  SwDBFormatData aFormatData;
//STRIP001  aFormatData.aNullDate = pParam->aNullDate;
//STRIP001  aFormatData.xFormatter = pParam->xFormatter;
//STRIP001
//STRIP001  String sLanguage, sCountry;
//STRIP001     ::ConvertLanguageToIsoNames( (USHORT)nLanguage, sLanguage, sCountry );
//STRIP001  aFormatData.aLocale.Language = sLanguage;
//STRIP001  aFormatData.aLocale.Country = sCountry;
//STRIP001
//STRIP001  rResult = SwNewDBMgr::GetDBField( xColumnProps, aFormatData, pNumber);
//STRIP001  return TRUE;
//STRIP001 };
/*--------------------------------------------------------------------
    Beschreibung: Daten importieren
 --------------------------------------------------------------------*/
/*N*/ BOOL SwNewDBMgr::MergeNew(USHORT nOpt, SwWrtShell& rSh,
/*N*/                         const ODataAccessDescriptor& _rDescriptor)
/*N*/ {DBG_ASSERT(0, "STRIP"); return FALSE;//STRIP001
//STRIP001 /*?*/     SetMergeType( nOpt );
//STRIP001 /*?*/
//STRIP001 /*?*/     DBG_ASSERT(!bInMerge && !pImpl->pMergeData, "merge already activated!")
//STRIP001 /*?*/
//STRIP001 /*?*/     SwDBData aData;
//STRIP001 /*?*/     aData.nCommandType = CommandType::TABLE;
//STRIP001 /*?*/     Reference<XResultSet>  xResSet;
//STRIP001 /*?*/     Sequence<Any> aSelection;
//STRIP001 /*?*/     Reference< XConnection> xConnection;
//STRIP001 /*?*/
//STRIP001 /*?*/    _rDescriptor[daDataSource]  >>= aData.sDataSource;
//STRIP001 /*?*/    _rDescriptor[daCommand]     >>= aData.sCommand;
//STRIP001 /*?*/    _rDescriptor[daCommandType] >>= aData.nCommandType;
//STRIP001 /*?*/
//STRIP001 /*?*/    if ( _rDescriptor.has(daCursor) )
//STRIP001 /*?*/        _rDescriptor[daCursor] >>= xResSet;
//STRIP001 /*?*/    if ( _rDescriptor.has(daSelection) )
//STRIP001 /*?*/        _rDescriptor[daSelection] >>= aSelection;
//STRIP001 /*?*/    if ( _rDescriptor.has(daConnection) )
//STRIP001 /*?*/        _rDescriptor[daConnection] >>= xConnection;
//STRIP001 /*?*/
//STRIP001 /*?*/     if(!aData.sDataSource.getLength() || !aData.sCommand.getLength() || !xResSet.is())
//STRIP001 /*?*/    {
//STRIP001 /*?*/        return FALSE;
//STRIP001 /*?*/    }
//STRIP001 /*?*/
//STRIP001 /*?*/     pImpl->pMergeData = new SwDSParam(aData, xResSet, aSelection);
//STRIP001 /*?*/     SwDSParam*  pTemp = FindDSData(aData, FALSE);
//STRIP001 /*?*/    if(pTemp)
//STRIP001 /*?*/         *pTemp = *pImpl->pMergeData;
//STRIP001 /*?*/    else
//STRIP001 /*?*/    {
//STRIP001 /*?*/         //#94779# calls from the calculator may have added a connection with an invalid commandtype
//STRIP001 /*?*/         //"real" data base connections added here have to re-use the already available
//STRIP001 /*?*/         //DSData and set the correct CommandType
//STRIP001 /*?*/         SwDBData aTempData(aData);
//STRIP001 /*?*/        aData.nCommandType = -1;
//STRIP001 /*?*/        pTemp = FindDSData(aData, FALSE);
//STRIP001 /*?*/        if(pTemp)
//STRIP001 /*?*/            *pTemp = *pImpl->pMergeData;
//STRIP001 /*?*/        else
//STRIP001 /*?*/         {
//STRIP001 /*?*/            SwDSParam* pInsert = new SwDSParam(*pImpl->pMergeData);
//STRIP001 /*?*/            aDataSourceParams.Insert(pInsert, aDataSourceParams.Count());
//STRIP001 /*?*/            try
//STRIP001 /*?*/            {
//STRIP001 /*?*/                Reference<XComponent> xComponent(pInsert->xConnection, UNO_QUERY);
//STRIP001 /*?*/                if(xComponent.is())
//STRIP001 /*?*/                    xComponent->addEventListener(pImpl->xDisposeListener);
//STRIP001 /*?*/            }
//STRIP001 /*?*/            catch(Exception&)
//STRIP001 /*?*/            {
//STRIP001 /*?*/            }
//STRIP001 /*?*/         }
//STRIP001 /*?*/    }
//STRIP001 /*?*/     if(!pImpl->pMergeData->xConnection.is())
//STRIP001 /*?*/         pImpl->pMergeData->xConnection = xConnection;
//STRIP001 /*?*/     // add an XEventListener
//STRIP001 /*?*/
//STRIP001 /*?*/    try{
//STRIP001 /*?*/        //set to start position
//STRIP001 /*?*/         if(pImpl->pMergeData->aSelection.getLength())
//STRIP001 /*?*/        {
//STRIP001 /*?*/            sal_Int32 nPos = 0;
//STRIP001 /*?*/            pImpl->pMergeData->aSelection.getConstArray()[ pImpl->pMergeData->nSelectionIndex++ ] >>= nPos;
//STRIP001 /*?*/             pImpl->pMergeData->bEndOfDB = !pImpl->pMergeData->xResultSet->absolute( nPos );
//STRIP001 /*?*/             pImpl->pMergeData->CheckEndOfDB();
//STRIP001 /*?*/             if(pImpl->pMergeData->nSelectionIndex >= pImpl->pMergeData->aSelection.getLength())
//STRIP001 /*?*/                 pImpl->pMergeData->bEndOfDB = TRUE;
//STRIP001 /*?*/        }
//STRIP001 /*?*/        else
//STRIP001 /*?*/        {
//STRIP001 /*?*/             pImpl->pMergeData->bEndOfDB = !pImpl->pMergeData->xResultSet->first();
//STRIP001 /*?*/             pImpl->pMergeData->CheckEndOfDB();
//STRIP001 /*?*/        }
//STRIP001 /*?*/    }
//STRIP001 /*?*/     catch(Exception&)
//STRIP001 /*?*/    {
//STRIP001 /*?*/         pImpl->pMergeData->bEndOfDB = TRUE;
//STRIP001 /*?*/         pImpl->pMergeData->CheckEndOfDB();
//STRIP001 /*?*/        DBG_ERROR("exception in MergeNew()")
//STRIP001 /*?*/    }
//STRIP001 /*?*/
//STRIP001 /*?*/    Reference<XDataSource> xSource = SwNewDBMgr::getDataSourceAsParent(xConnection,aData.sDataSource);
//STRIP001 /*?*/
//STRIP001 /*?*/    Reference<XMultiServiceFactory> xMgr = ::legacy_binfilters::getLegacyProcessServiceFactory();
//STRIP001 /*?*/    if( xMgr.is() )
//STRIP001 /*?*/    {
//STRIP001 /*?*/        Reference<XInterface> xInstance = xMgr->createInstance( C2U( "com.sun.star.util.NumberFormatter" ));
//STRIP001 /*?*/         pImpl->pMergeData->xFormatter = Reference<util::XNumberFormatter>(xInstance, UNO_QUERY) ;
//STRIP001 /*?*/    }
//STRIP001 /*?*/
//STRIP001 /*?*/    Reference<XPropertySet> xSourceProps(xSource, UNO_QUERY);
//STRIP001 /*?*/    if(xSourceProps.is())
//STRIP001 /*?*/    {
//STRIP001 /*?*/        Any aFormats = xSourceProps->getPropertyValue(C2U("NumberFormatsSupplier"));
//STRIP001 /*?*/        if(aFormats.hasValue())
//STRIP001 /*?*/        {
//STRIP001 /*?*/            Reference<XNumberFormatsSupplier> xSuppl;
//STRIP001 /*?*/            aFormats >>= xSuppl;
//STRIP001 /*?*/            if(xSuppl.is())
//STRIP001 /*?*/            {
//STRIP001 /*?*/                Reference< XPropertySet > xSettings = xSuppl->getNumberFormatSettings();
//STRIP001 /*?*/                Any aNull = xSettings->getPropertyValue(C2U("NullDate"));
//STRIP001 /*?*/                 aNull >>= pImpl->pMergeData->aNullDate;
//STRIP001 /*?*/            }
//STRIP001 /*?*/        }
//STRIP001 /*?*/    }
//STRIP001 /*?*/
//STRIP001 /*?*/     rSh.ChgDBData(aData);
//STRIP001 /*?*/    bInMerge = TRUE;
//STRIP001 /*?*/
//STRIP001 /*?*/    if (IsInitDBFields())
//STRIP001 /*?*/    {
//STRIP001 /*?*/        // Bei Datenbankfeldern ohne DB-Name DB-Name von Dok einsetzen
//STRIP001 /*?*/        SvStringsDtor aDBNames(1, 1);
//STRIP001 /*?*/        aDBNames.Insert( new String(), 0);
//STRIP001 /*?*/        SwDBData aData = rSh.GetDBData();
//STRIP001 /*?*/        String sDBName = aData.sDataSource;
//STRIP001 /*?*/        sDBName += DB_DELIM;
//STRIP001 /*?*/        sDBName += (String)aData.sCommand;
//STRIP001 /*?*/        sDBName += DB_DELIM;
//STRIP001 /*?*/        sDBName += String::CreateFromInt32(aData.nCommandType);
//STRIP001 /*?*/        rSh.ChangeDBFields( aDBNames, sDBName);
//STRIP001 /*?*/        SetInitDBFields(FALSE);
//STRIP001 /*?*/    }
//STRIP001 /*?*/
//STRIP001 /*?*/    BOOL bRet = TRUE;
//STRIP001 /*?*/    switch(nOpt)
//STRIP001 /*?*/    {
//STRIP001 /*?*/        case DBMGR_MERGE:
//STRIP001 /*?*/            bRet = Merge(&rSh);   // Mischen
//STRIP001 /*?*/            break;
//STRIP001 /*?*/
//STRIP001 /*?*/        case DBMGR_MERGE_MAILMERGE: // Serienbrief
//STRIP001 /*?*/         {
//STRIP001 /*?*/            SfxDispatcher *pDis = rSh.GetView().GetViewFrame()->GetDispatcher();
//STRIP001 /*?*/             SfxBoolItem aMerge(FN_QRY_MERGE, TRUE);
//STRIP001 /*?*/
//STRIP001 /*?*/             // !! Currently (Jan-2003) silent is defined by supplying *any*
//STRIP001 /*?*/             // !! item!!  (Thus according to OS it would be silent even when
//STRIP001 /*?*/             // !! other items then SID_SILENT would be supplied!)
//STRIP001 /*?*/             // !! Therefore it has to be the 0 pointer when not silent.
//STRIP001 /*?*/             SfxBoolItem aMergeSilent(SID_SILENT, TRUE);
//STRIP001 /*?*/             SfxBoolItem *pMergeSilent = IsMergeSilent() ? &aMergeSilent : 0;
//STRIP001 /*?*/
//STRIP001 /*?*/             pDis->Execute(SID_PRINTDOC,
//STRIP001 /*?*/                     SFX_CALLMODE_SYNCHRON|SFX_CALLMODE_RECORD, &aMerge, pMergeSilent, 0L);
//STRIP001 /*?*/         }
//STRIP001 /*?*/         break;
//STRIP001 /*?*/
//STRIP001 /*?*/        case DBMGR_MERGE_MAILING:
//STRIP001 /*?*/            bRet = MergeMailing(&rSh);  // Mailing
//STRIP001 /*?*/            break;
//STRIP001 /*?*/
//STRIP001 /*?*/        case DBMGR_MERGE_MAILFILES:
//STRIP001 /*?*/            bRet = MergeMailFiles(&rSh);    // Serienbriefe als Dateien abspeichern
//STRIP001 /*?*/            break;
//STRIP001 /*?*/
//STRIP001 /*?*/        default:        // Einfuegen der selektierten Eintraege
//STRIP001 /*?*/                        // (war: InsertRecord)
//STRIP001 /*?*/            ImportFromConnection(&rSh);
//STRIP001 /*?*/            break;
//STRIP001 /*?*/    }
//STRIP001 /*?*/
//STRIP001 /*?*/    EndMerge();
//STRIP001 /*?*/    return bRet;
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung: Daten importieren
 --------------------------------------------------------------------*/


//STRIP001 BOOL SwNewDBMgr::Merge(SwWrtShell* pSh)
//STRIP001 {
//STRIP001  pSh->StartAllAction();
//STRIP001
//STRIP001  pSh->ViewShell::UpdateFlds(TRUE);
//STRIP001  pSh->SetModified();
//STRIP001
//STRIP001  pSh->EndAllAction();
//STRIP001
//STRIP001  return TRUE;
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung:
 --------------------------------------------------------------------*/
//STRIP001 void SwNewDBMgr::ImportFromConnection(   SwWrtShell* pSh )
//STRIP001 {
//STRIP001     if(pImpl->pMergeData && !pImpl->pMergeData->bEndOfDB)
//STRIP001  {
//STRIP001      {
//STRIP001          pSh->StartAllAction();
//STRIP001          pSh->StartUndo(0);
//STRIP001          BOOL bGroupUndo(pSh->DoesGroupUndo());
//STRIP001          pSh->DoGroupUndo(FALSE);
//STRIP001
//STRIP001          if( pSh->HasSelection() )
//STRIP001              pSh->DelRight();
//STRIP001
//STRIP001          SwWait *pWait = 0;
//STRIP001
//STRIP001          {
//STRIP001              ULONG i = 0;
//STRIP001              do {
//STRIP001
//STRIP001                  ImportDBEntry(pSh);
//STRIP001                  if( 10 == ++i )
//STRIP001                      pWait = new SwWait( *pSh->GetView().GetDocShell(), TRUE);
//STRIP001
//STRIP001              } while(ToNextMergeRecord());
//STRIP001          }
//STRIP001
//STRIP001          pSh->DoGroupUndo(bGroupUndo);
//STRIP001          pSh->EndUndo(0);
//STRIP001          pSh->EndAllAction();
//STRIP001          delete pWait;
//STRIP001      }
//STRIP001  }
//STRIP001 }
/*-----------------24.02.97 10.30-------------------

--------------------------------------------------*/

//STRIP001 String   lcl_FindColumn(const String& sFormatStr,USHORT  &nUsedPos, BYTE &nSeparator)
//STRIP001 {
//STRIP001  String sReturn;
//STRIP001  USHORT nLen = sFormatStr.Len();
//STRIP001  nSeparator = 0xff;
//STRIP001  while(nUsedPos < nLen && nSeparator == 0xff)
//STRIP001  {
//STRIP001      sal_Unicode cAkt = sFormatStr.GetChar(nUsedPos);
//STRIP001      switch(cAkt)
//STRIP001      {
//STRIP001          case ',':
//STRIP001              nSeparator = DB_SEP_SPACE;
//STRIP001          break;
//STRIP001          case ';':
//STRIP001              nSeparator = DB_SEP_RETURN;
//STRIP001          break;
//STRIP001          case ':':
//STRIP001              nSeparator = DB_SEP_TAB;
//STRIP001          break;
//STRIP001          case '#':
//STRIP001              nSeparator = DB_SEP_NEWLINE;
//STRIP001          break;
//STRIP001          default:
//STRIP001              sReturn += cAkt;
//STRIP001      }
//STRIP001      nUsedPos++;
//STRIP001
//STRIP001  }
//STRIP001  return sReturn;
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung:
 --------------------------------------------------------------------*/

//STRIP001 inline String lcl_GetDBInsertMode( const SwDBData& rData )
//STRIP001 {
//STRIP001  return aEmptyStr;
//STRIP001 #if 0
//STRIP001 //JP 13.11.00: must be change to the new configuration
//STRIP001  return  SFX_APP()->GetIniManager()->Get( String::CreateFromAscii(
//STRIP001              RTL_CONSTASCII_STRINGPARAM( "DataBaseFormatInfo" )),
//STRIP001              FALSE, FALSE, sDBName );
//STRIP001 #endif
//STRIP001 }


//STRIP001 void SwNewDBMgr::ImportDBEntry(SwWrtShell* pSh)
//STRIP001 {
//STRIP001     if(pImpl->pMergeData && !pImpl->pMergeData->bEndOfDB)
//STRIP001  {
//STRIP001         Reference< XColumnsSupplier > xColsSupp( pImpl->pMergeData->xResultSet, UNO_QUERY );
//STRIP001          Reference <XNameAccess> xCols = xColsSupp->getColumns();
//STRIP001         String sFormatStr( lcl_GetDBInsertMode( *pImpl->pMergeData ));
//STRIP001      USHORT nFmtLen = sFormatStr.Len();
//STRIP001      if( nFmtLen )
//STRIP001      {
//STRIP001          const char cSpace = ' ';
//STRIP001          const char cTab = '\t';
//STRIP001          USHORT nUsedPos = 0;
//STRIP001          BYTE    nSeparator;
//STRIP001          String sColumn = lcl_FindColumn(sFormatStr, nUsedPos, nSeparator);
//STRIP001          while( sColumn.Len() )
//STRIP001          {
//STRIP001              if(!xCols->hasByName(sColumn))
//STRIP001                  return;
//STRIP001              Any aCol = xCols->getByName(sColumn);
//STRIP001                 Reference< XPropertySet > xColumnProp;
//STRIP001                 aCol >>= xColumnProp;
//STRIP001              if(xColumnProp.is())
//STRIP001              {
//STRIP001                  SwDBFormatData aDBFormat;
//STRIP001                  String sInsert = GetDBField( xColumnProp,   aDBFormat);
//STRIP001                  if( DB_SEP_SPACE == nSeparator )
//STRIP001                          sInsert += cSpace;
//STRIP001                  else if( DB_SEP_TAB == nSeparator)
//STRIP001                          sInsert += cTab;
//STRIP001                  pSh->Insert(sInsert);
//STRIP001                  if( DB_SEP_RETURN == nSeparator)
//STRIP001                      pSh->SplitNode();
//STRIP001                  else if(DB_SEP_NEWLINE == nSeparator)
//STRIP001                          pSh->InsertLineBreak();
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  // Spalte nicht gefunden -> Fehler anzeigen
//STRIP001                  String sInsert = '?';
//STRIP001                  sInsert += sColumn;
//STRIP001                  sInsert += '?';
//STRIP001                  pSh->Insert(sInsert);
//STRIP001              }
//STRIP001              sColumn = lcl_FindColumn(sFormatStr, nUsedPos, nSeparator);
//STRIP001          }
//STRIP001          pSh->SplitNode();
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          String sStr;
//STRIP001             Sequence<rtl::OUString> aColNames = xCols->getElementNames();
//STRIP001             const rtl::OUString* pColNames = aColNames.getConstArray();
//STRIP001          long nLength = aColNames.getLength();
//STRIP001          for(long i = 0; i < nLength; i++)
//STRIP001          {
//STRIP001              Any aCol = xCols->getByName(pColNames[i]);
//STRIP001                 Reference< XPropertySet > xColumnProp;
//STRIP001                 aCol >>= xColumnProp;
//STRIP001              SwDBFormatData aDBFormat;
//STRIP001              sStr += GetDBField( xColumnProp, aDBFormat);
//STRIP001              if (i < nLength - 1)
//STRIP001                  sStr += '\t';
//STRIP001          }
//STRIP001          pSh->SwEditShell::Insert(sStr);
//STRIP001          pSh->SwFEShell::SplitNode();    // Zeilenvorschub
//STRIP001      }
//STRIP001  }
//STRIP001 }
/*--------------------------------------------------------------------
    Beschreibung: Listbox mit Tabellenliste fuellen
 --------------------------------------------------------------------*/
//STRIP001 BOOL SwNewDBMgr::GetTableNames(ListBox* pListBox, const String& rDBName)
//STRIP001 {
//STRIP001  BOOL bRet = FALSE;
//STRIP001     String sOldTableName(pListBox->GetSelectEntry());
//STRIP001  pListBox->Clear();
//STRIP001     SwDSParam* pParam = FindDSConnection(rDBName, FALSE);
//STRIP001     Reference< XConnection> xConnection;
//STRIP001     if(pParam && pParam->xConnection.is())
//STRIP001         xConnection = pParam->xConnection;
//STRIP001     else
//STRIP001     {
//STRIP001         rtl::OUString sDBName(rDBName);
//STRIP001         xConnection = RegisterConnection( sDBName );
//STRIP001     }
//STRIP001  if(xConnection.is())
//STRIP001  {
//STRIP001      Reference<XTablesSupplier> xTSupplier = Reference<XTablesSupplier>(xConnection, UNO_QUERY);
//STRIP001      if(xTSupplier.is())
//STRIP001      {
//STRIP001          Reference<XNameAccess> xTbls = xTSupplier->getTables();
//STRIP001             Sequence<rtl::OUString> aTbls = xTbls->getElementNames();
//STRIP001             const rtl::OUString* pTbls = aTbls.getConstArray();
//STRIP001          for(long i = 0; i < aTbls.getLength(); i++)
//STRIP001             {
//STRIP001                 USHORT nEntry = pListBox->InsertEntry(pTbls[i]);
//STRIP001                 pListBox->SetEntryData(nEntry, (void*)0);
//STRIP001             }
//STRIP001      }
//STRIP001      Reference<XQueriesSupplier> xQSupplier = Reference<XQueriesSupplier>(xConnection, UNO_QUERY);
//STRIP001      if(xQSupplier.is())
//STRIP001      {
//STRIP001          Reference<XNameAccess> xQueries = xQSupplier->getQueries();
//STRIP001             Sequence<rtl::OUString> aQueries = xQueries->getElementNames();
//STRIP001             const rtl::OUString* pQueries = aQueries.getConstArray();
//STRIP001          for(long i = 0; i < aQueries.getLength(); i++)
//STRIP001             {
//STRIP001                 USHORT nEntry = pListBox->InsertEntry(pQueries[i]);
//STRIP001                 pListBox->SetEntryData(nEntry, (void*)1);
//STRIP001             }
//STRIP001         }
//STRIP001      if (sOldTableName.Len())
//STRIP001          pListBox->SelectEntry(sOldTableName);
//STRIP001      bRet = TRUE;
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung: Listbox mit Spaltennamen einer Datenbank fuellen
 --------------------------------------------------------------------*/
//STRIP001 BOOL SwNewDBMgr::GetColumnNames(ListBox* pListBox,
//STRIP001          const String& rDBName, const String& rTableName, BOOL bAppend)
//STRIP001 {
//STRIP001  if (!bAppend)
//STRIP001      pListBox->Clear();
//STRIP001     SwDSParam* pParam = FindDSConnection(rDBName, FALSE);
//STRIP001     Reference< XConnection> xConnection;
//STRIP001     if(pParam && pParam->xConnection.is())
//STRIP001         xConnection = pParam->xConnection;
//STRIP001     else
//STRIP001     {
//STRIP001         rtl::OUString sDBName(rDBName);
//STRIP001         xConnection = RegisterConnection( sDBName );
//STRIP001     }
//STRIP001  Reference< XColumnsSupplier> xColsSupp = SwNewDBMgr::GetColumnSupplier(xConnection, rTableName);
//STRIP001  if(xColsSupp.is())
//STRIP001  {
//STRIP001      Reference <XNameAccess> xCols = xColsSupp->getColumns();
//STRIP001         const Sequence<rtl::OUString> aColNames = xCols->getElementNames();
//STRIP001         const rtl::OUString* pColNames = aColNames.getConstArray();
//STRIP001      for(int nCol = 0; nCol < aColNames.getLength(); nCol++)
//STRIP001      {
//STRIP001          pListBox->InsertEntry(pColNames[nCol]);
//STRIP001      }
//STRIP001  }
//STRIP001  return(TRUE);
//STRIP001 }
/* -----------------------------08.06.01 15:11--------------------------------

 ---------------------------------------------------------------------------*/
//STRIP001 BOOL SwNewDBMgr::GetColumnNames(ListBox* pListBox,
//STRIP001         Reference< XConnection> xConnection,
//STRIP001         const String& rTableName, BOOL bAppend)
//STRIP001 {
//STRIP001  if (!bAppend)
//STRIP001      pListBox->Clear();
//STRIP001  Reference< XColumnsSupplier> xColsSupp = SwNewDBMgr::GetColumnSupplier(xConnection, rTableName);
//STRIP001  if(xColsSupp.is())
//STRIP001  {
//STRIP001      Reference <XNameAccess> xCols = xColsSupp->getColumns();
//STRIP001         const Sequence<rtl::OUString> aColNames = xCols->getElementNames();
//STRIP001         const rtl::OUString* pColNames = aColNames.getConstArray();
//STRIP001      for(int nCol = 0; nCol < aColNames.getLength(); nCol++)
//STRIP001      {
//STRIP001          pListBox->InsertEntry(pColNames[nCol]);
//STRIP001      }
//STRIP001  }
//STRIP001  return(TRUE);
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung: CTOR
 --------------------------------------------------------------------*/

/*N*/ SwNewDBMgr::SwNewDBMgr() :
/*N*/             pImpl(new SwNewDBMgr_Impl(*this)),
/*N*/             pMergeEvtSrc(NULL),
/*N*/             bInMerge(FALSE),
/*N*/             bMergeLock(FALSE),
/*N*/             bMergeSilent(FALSE),
/*N*/           nMergeType(DBMGR_INSERT),
/*N*/           bInitDBFields(FALSE)
/*N*/ {
/*N*/ }
/* -----------------------------18.07.00 08:56--------------------------------

 ---------------------------------------------------------------------------*/
/*M*/ SwNewDBMgr::~SwNewDBMgr()
/*M*/ {
/*M*/     for(USHORT nPos = 0; nPos < aDataSourceParams.Count(); nPos++)
/*M*/     {
/*M*/         SwDSParam* pParam = aDataSourceParams[nPos];
/*M*/         if(pParam->xConnection.is())
/*M*/         {
/*M*/             try
/*M*/             {
/*M*/                 Reference<XComponent> xComp(pParam->xConnection, UNO_QUERY);
/*M*/                 if(xComp.is())
/*M*/                     xComp->dispose();
/*M*/             }
/*M*/             catch(const RuntimeException& )
/*M*/             {
/*M*/                 //may be disposed already since multiple entries may have used the same connection
/*M*/             }
/*M*/         }
/*M*/     }
/*M*/     delete pImpl;
/*M*/ }
/*--------------------------------------------------------------------
    Beschreibung:   Serienbrief drucken
 --------------------------------------------------------------------*/


//STRIP001 BOOL SwNewDBMgr::MergePrint( SwView& rView,
//STRIP001                           SwPrtOptions& rOpt, SfxProgress& rProgress )
//STRIP001 {
//STRIP001  SwWrtShell* pSh = &rView.GetWrtShell();
//STRIP001  //check if the doc is synchronized and contains at least one linked section
//STRIP001  BOOL bSynchronizedDoc = pSh->IsLabelDoc() && pSh->GetSectionFmtCount() > 1;
//STRIP001  //merge source is already open
//STRIP001     rOpt.nMergeCnt = 0;
//STRIP001     if(pImpl->pMergeData)
//STRIP001     {
//STRIP001         if(pImpl->pMergeData->aSelection.getLength())
//STRIP001             rOpt.nMergeCnt = pImpl->pMergeData->aSelection.getLength();
//STRIP001         else if(pImpl->pMergeData->xResultSet.is())
//STRIP001         {
//STRIP001             Reference<XPropertySet> xPrSet(pImpl->pMergeData->xResultSet, UNO_QUERY);
//STRIP001             if(xPrSet.is())
//STRIP001             {
//STRIP001                 try
//STRIP001                 {
//STRIP001                     sal_Bool bFinal;
//STRIP001                     Any aFinal = xPrSet->getPropertyValue(C2U("IsRowCountFinal"));
//STRIP001                     aFinal >>= bFinal;
//STRIP001                     if(!bFinal)
//STRIP001                     {
//STRIP001                         pImpl->pMergeData->xResultSet->last();
//STRIP001                         pImpl->pMergeData->xResultSet->first();
//STRIP001                     }
//STRIP001                     long nCount;
//STRIP001                     Any aCount = xPrSet->getPropertyValue(C2U("RowCount"));
//STRIP001                     aCount >>= nCount;
//STRIP001                     rOpt.nMergeCnt = (ULONG)nCount;
//STRIP001                 }
//STRIP001                 catch(Exception&)
//STRIP001                 {
//STRIP001                 }
//STRIP001             }
//STRIP001         }
//STRIP001     }
//STRIP001
//STRIP001     SwModuleOptions* pModOpt = SW_MOD()->GetModuleConfig();
//STRIP001     pModOpt->SetSinglePrintJob(rOpt.IsPrintSingleJobs());
//STRIP001
//STRIP001  SfxPrinter *pPrt = pSh->GetPrt();
//STRIP001  Link aSfxSaveLnk = pPrt->GetEndPrintHdl();
//STRIP001     if( rOpt.IsPrintSingleJobs()  )
//STRIP001      pPrt->SetEndPrintHdl( Link() );
//STRIP001
//STRIP001  BOOL bNewJob = FALSE,
//STRIP001       bUserBreak = FALSE,
//STRIP001       bRet = FALSE;
//STRIP001     long nStartRow, nEndRow;
//STRIP001     //calculate number of data sets to be printed
//STRIP001
//STRIP001     Sequence<PropertyValue> aViewProperties(15);
//STRIP001     PropertyValue* pViewProperties =  aViewProperties.getArray();
//STRIP001     pViewProperties[0].Name = C2U("MailMergeCount");
//STRIP001     pViewProperties[0].Value <<= (sal_Int32)rOpt.nMergeCnt;
//STRIP001     pViewProperties[1].Name = C2U("PrintGraphics");
//STRIP001     pViewProperties[1].Value <<= (sal_Bool)rOpt.IsPrintGraphic();
//STRIP001     pViewProperties[2].Name = C2U("PrintTables");
//STRIP001     pViewProperties[2].Value <<= (sal_Bool)rOpt.IsPrintTable();
//STRIP001     pViewProperties[3].Name = C2U("PrintDrawings");
//STRIP001     pViewProperties[3].Value <<= (sal_Bool)rOpt.IsPrintDraw();
//STRIP001     pViewProperties[4].Name = C2U("PrintLeftPages");
//STRIP001     pViewProperties[4].Value <<= (sal_Bool)rOpt.IsPrintLeftPage();
//STRIP001     pViewProperties[5].Name = C2U("PrintRightPages");
//STRIP001     pViewProperties[5].Value <<= (sal_Bool)rOpt.IsPrintRightPage();
//STRIP001     pViewProperties[6].Name = C2U("PrintControls");
//STRIP001     pViewProperties[6].Value <<= (sal_Bool)rOpt.IsPrintControl();
//STRIP001     pViewProperties[7].Name = C2U("PrintReversed");
//STRIP001     pViewProperties[7].Value <<= (sal_Bool)rOpt.IsPrintReverse();
//STRIP001     pViewProperties[8].Name = C2U("PrintPaperFromSetup");
//STRIP001     pViewProperties[8].Value <<= (sal_Bool)rOpt.IsPaperFromSetup();
//STRIP001     pViewProperties[9].Name = C2U("PrintFaxName");
//STRIP001     pViewProperties[9].Value <<= rOpt.GetFaxName();
//STRIP001     pViewProperties[10].Name = C2U("PrintAnnotationMode");
//STRIP001     pViewProperties[10].Value <<= (com::sun::star::text::NotePrintMode) rOpt.GetPrintPostIts();
//STRIP001     pViewProperties[11].Name = C2U("PrintProspect");
//STRIP001     pViewProperties[11].Value <<= (sal_Bool)rOpt.IsPrintProspect();
//STRIP001     pViewProperties[12].Name = C2U("PrintPageBackground");
//STRIP001     pViewProperties[12].Value <<= (sal_Bool)rOpt.IsPrintPageBackground();
//STRIP001     pViewProperties[13].Name = C2U("PrintBlackFonts");
//STRIP001     pViewProperties[13].Value <<= (sal_Bool)rOpt.IsPrintBlackFont();
//STRIP001     pViewProperties[14].Name = C2U("IsSinglePrintJob");
//STRIP001     pViewProperties[14].Value <<= (sal_Bool)rOpt.IsPrintSingleJobs();
//STRIP001
//STRIP001     rView.SetAdditionalPrintOptions(aViewProperties);
//STRIP001  do {
//STRIP001         nStartRow = pImpl->pMergeData ? pImpl->pMergeData->xResultSet->getRow() : 0;
//STRIP001         {
//STRIP001          pSh->ViewShell::UpdateFlds();
//STRIP001          ++rOpt.nMergeAct;
//STRIP001
//STRIP001             // launch MailMergeEvent if required
//STRIP001             const SwXMailMerge *pEvtSrc = GetMailMergeEvtSrc();
//STRIP001             if (pEvtSrc)
//STRIP001             {
//STRIP001                 Reference< XInterface > xRef( (XMailMergeBroadcaster *) pEvtSrc );
//STRIP001                 text::MailMergeEvent aEvt( xRef, rView.GetDocShell()->GetModel() );
//STRIP001                 pEvtSrc->LaunchMailMergeEvent( aEvt );
//STRIP001             }
//STRIP001
//STRIP001             rView.SfxViewShell::Print( rProgress ); // ggf Basic-Macro ausfuehren
//STRIP001             if( rOpt.IsPrintSingleJobs() && bRet )
//STRIP001          {
//STRIP001              //rOpt.bJobStartet = FALSE;
//STRIP001              bRet = FALSE;
//STRIP001          }
//STRIP001
//STRIP001             bMergeLock = TRUE;
//STRIP001             if(rOpt.IsPrintProspect())
//STRIP001          {
//STRIP001                 if( pPrt->IsJobActive() || pPrt->StartJob( rOpt.GetJobName() ))
//STRIP001                 {
//STRIP001                     pSh->PrintProspect( rOpt, rProgress );
//STRIP001                     bRet = TRUE;
//STRIP001                 }
//STRIP001          }
//STRIP001             else if( pSh->Prt( rOpt, rProgress ) )
//STRIP001              bRet = TRUE;
//STRIP001             bMergeLock = FALSE;
//STRIP001
//STRIP001          if( !pPrt->IsJobActive() )
//STRIP001          {
//STRIP001              bUserBreak = TRUE;
//STRIP001              bRet = FALSE;
//STRIP001              break;
//STRIP001          }
//STRIP001             if( !rOpt.IsPrintSingleJobs() )
//STRIP001          {
//STRIP001              String& rJNm = (String&)rOpt.GetJobName();
//STRIP001              rJNm.Erase();
//STRIP001          }
//STRIP001      }
//STRIP001         nEndRow = pImpl->pMergeData ? pImpl->pMergeData->xResultSet->getRow() : 0;
//STRIP001     } while( bSynchronizedDoc && (nStartRow != nEndRow)? ExistsNextRecord() : ToNextMergeRecord());
//STRIP001
//STRIP001     if( rOpt.IsPrintSingleJobs() )
//STRIP001  {
//STRIP001      pSh->GetPrt()->SetEndPrintHdl( aSfxSaveLnk );
//STRIP001      if ( !bUserBreak && !pSh->GetPrt()->IsJobActive() )     //Schon zu spaet?
//STRIP001          aSfxSaveLnk.Call( pSh->GetPrt() );
//STRIP001  }
//STRIP001
//STRIP001  rOpt.nMergeCnt = 0;
//STRIP001  rOpt.nMergeAct = 0;
//STRIP001
//STRIP001  nMergeType = DBMGR_INSERT;
//STRIP001
//STRIP001  SwDocShell* pDocSh = rView.GetDocShell();
//STRIP001  SfxViewFrame *pTmpFrm = SfxViewFrame::GetFirst(pDocSh);
//STRIP001
//STRIP001  while (pTmpFrm)     // Alle Views Invalidieren
//STRIP001  {
//STRIP001      SwView *pVw = PTR_CAST(SwView, pTmpFrm->GetViewShell());
//STRIP001      if (pVw)
//STRIP001          pVw->GetEditWin().Invalidate();
//STRIP001      pTmpFrm = pTmpFrm->GetNext(*pTmpFrm, pDocSh);
//STRIP001  }
//STRIP001
//STRIP001  return bRet;
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung:   Serienbrief als Mail versenden
 --------------------------------------------------------------------*/


//STRIP001 BOOL SwNewDBMgr::MergeMailing(SwWrtShell* pSh)
//STRIP001 {
//STRIP001  //check if the doc is synchronized and contains at least one linked section
//STRIP001  BOOL bSynchronizedDoc = pSh->IsLabelDoc() && pSh->GetSectionFmtCount() > 1;
//STRIP001  BOOL bLoop = TRUE;
//STRIP001
//STRIP001  {
//STRIP001         Reference< XColumnsSupplier > xColsSupp( pImpl->pMergeData->xResultSet, UNO_QUERY );
//STRIP001      Reference <XNameAccess> xCols = xColsSupp->getColumns();
//STRIP001      if(!xCols->hasByName(sEMailAddrFld))
//STRIP001          return FALSE;
//STRIP001      Any aCol = xCols->getByName(sEMailAddrFld);
//STRIP001         Reference< XPropertySet > xColumnProp;
//STRIP001         aCol >>= xColumnProp;
//STRIP001
//STRIP001      SfxDispatcher* pSfxDispatcher = pSh->GetView().GetViewFrame()->GetDispatcher();
//STRIP001      if (!sSubject.Len())    // Kein leeres Subject wegen Automail (PB)
//STRIP001          sSubject = ' ';
//STRIP001      SfxStringItem aSubject(SID_MAIL_SUBJECT, sSubject);
//STRIP001      SfxStringItem aText(SID_MAIL_TEXT, ' ');    // Leerer Text ist nicht moeglich
//STRIP001      SfxStringItem aAttached(SID_MAIL_ATTACH_FILE, sAttached);
//STRIP001      SfxBoolItem aAttach(SID_MAIL_ATTACH, TRUE);
//STRIP001
//STRIP001      SwModuleOptions* pModOpt = SW_MOD()->GetModuleConfig();
//STRIP001      BYTE nMailFmts = pModOpt->GetMailingFormats() | TXTFORMAT_ASCII;    // Immer Ascii
//STRIP001      SfxByteItem aTextFormats(SID_MAIL_TXTFORMAT, nMailFmts);
//STRIP001
//STRIP001      pSfxDispatcher->Execute( SID_SAVEDOC, SFX_CALLMODE_SYNCHRON|SFX_CALLMODE_RECORD);
//STRIP001      if( !pSh->IsModified() )
//STRIP001      {
//STRIP001          // Beim Speichern wurde kein Abbruch gedrueckt
//STRIP001          // neue DocShell erzeugen, alle gelinkten Bereiche embedden
//STRIP001          // und unter temporaerem Namen wieder speichern.
//STRIP001          String sTmpName;
//STRIP001          const SfxFilter* pSfxFlt;
//STRIP001
//STRIP001          {
//STRIP001              SfxMedium* pOrig = pSh->GetView().GetDocShell()->GetMedium();
//STRIP001              String sMainURL( pOrig->GetURLObject().GetMainURL(
//STRIP001                                          INetURLObject::NO_DECODE ));
//STRIP001                 pSfxFlt = SwIoSystem::GetFileFilter( sMainURL, ::aEmptyStr );
//STRIP001
//STRIP001              sTmpName = utl::TempFile::CreateTempName(0);
//STRIP001              sTmpName = URIHelper::SmartRelToAbs(sTmpName);
//STRIP001              SWUnoHelper::UCB_CopyFile( sMainURL, sTmpName );
//STRIP001          }
//STRIP001          String sAddress;
//STRIP001          ULONG nDocNo = 1;
//STRIP001          bCancel = FALSE;
//STRIP001
//STRIP001          PrintMonitor aPrtMonDlg(&pSh->GetView().GetEditWin(), TRUE);
//STRIP001          aPrtMonDlg.aDocName.SetText(pSh->GetView().GetDocShell()->GetTitle(22));
//STRIP001          aPrtMonDlg.aCancel.SetClickHdl(LINK(this, SwNewDBMgr, PrtCancelHdl));
//STRIP001             if (!IsMergeSilent())
//STRIP001                 aPrtMonDlg.Show();
//STRIP001
//STRIP001          OfficeApplication* pOffApp = OFF_APP();
//STRIP001          SfxRequest aReq( SID_OPENDOC, SFX_CALLMODE_SYNCHRON, pOffApp->GetPool() );
//STRIP001          aReq.AppendItem( SfxStringItem( SID_FILE_NAME, sTmpName ));
//STRIP001          if(pSfxFlt)
//STRIP001              aReq.AppendItem( SfxStringItem( SID_FILTER_NAME, pSfxFlt->GetName() ));
//STRIP001          aReq.AppendItem( SfxBoolItem( SID_HIDDEN, TRUE ) );
//STRIP001          aReq.AppendItem( SfxStringItem( SID_REFERER, String::CreateFromAscii(URL_PREFIX_PRIV_SOFFICE )));
//STRIP001
//STRIP001          pOffApp->ExecuteSlot( aReq, pOffApp->SfxApplication::GetInterface());
//STRIP001             const SfxPoolItem* pReturnValue = aReq.GetReturnValue();
//STRIP001          if(pReturnValue)
//STRIP001          {
//STRIP001              // DocShell besorgen
//STRIP001              SfxViewFrameItem* pVItem = (SfxViewFrameItem*)pReturnValue;
//STRIP001              SwView* pView = (SwView*) pVItem->GetFrame()->GetViewShell();
//STRIP001              SwWrtShell& rSh = pView->GetWrtShell();
//STRIP001              pView->AttrChangedNotify( &rSh );//Damit SelectShell gerufen wird.
//STRIP001
//STRIP001              SwDoc* pDoc = rSh.GetDoc();
//STRIP001              SwNewDBMgr* pOldDBMgr = pDoc->GetNewDBMgr();
//STRIP001              pDoc->SetNewDBMgr( this );
//STRIP001              pDoc->EmbedAllLinks();
//STRIP001              String sTempStat(SW_RES(STR_DB_EMAIL));
//STRIP001                 long nStartRow, nEndRow;
//STRIP001              do
//STRIP001              {
//STRIP001                     nStartRow = pImpl->pMergeData ? pImpl->pMergeData->xResultSet->getRow() : 0;
//STRIP001                     if(UIUNDO_DELETE_INVISIBLECNTNT == rSh.GetUndoIds())
//STRIP001                         rSh.Undo();
//STRIP001                     rSh.ViewShell::UpdateFlds();
//STRIP001
//STRIP001                     // alle versteckten Felder/Bereiche entfernen
//STRIP001                     rSh.RemoveInvisibleContent();
//STRIP001
//STRIP001                     SfxFrameItem aFrame( SID_DOCFRAME, pVItem->GetFrame() );
//STRIP001                     SwDBFormatData aDBFormat;
//STRIP001                     sAddress = GetDBField( xColumnProp, aDBFormat);
//STRIP001                     if (!sAddress.Len())
//STRIP001                         sAddress = '_';
//STRIP001
//STRIP001                     String sStat(sTempStat);
//STRIP001                     sStat += ' ';
//STRIP001                     sStat += String::CreateFromInt32( nDocNo++ );
//STRIP001                     aPrtMonDlg.aPrintInfo.SetText(sStat);
//STRIP001                     aPrtMonDlg.aPrinter.SetText( sAddress );
//STRIP001
//STRIP001                     // Rechenzeit fuer EMail-Monitor:
//STRIP001                     for (USHORT i = 0; i < 25; i++)
//STRIP001                         Application::Reschedule();
//STRIP001
//STRIP001                     sAddress.Insert(String::CreateFromAscii("mailto:"), 0);
//STRIP001                     SfxStringItem aRecipient( SID_MAIL_RECIPIENT, sAddress );
//STRIP001
//STRIP001                     const SfxPoolItem* pRet = pSfxDispatcher->Execute(
//STRIP001                                 SID_MAIL_SENDDOC,
//STRIP001                                 SFX_CALLMODE_SYNCHRON|SFX_CALLMODE_RECORD,
//STRIP001                                 &aRecipient, &aSubject, &aAttach, &aAttached,
//STRIP001                                 &aText, &aTextFormats, &aFrame,
//STRIP001                                 0L );
//STRIP001                     //this must be done here because pRet may be destroyed in Reschedule (DeleteOnIdle)
//STRIP001                     BOOL bBreak = pRet && !( (SfxBoolItem*)pRet )->GetValue();
//STRIP001
//STRIP001                     // Rechenzeit fuer EMail-Monitor:
//STRIP001                     for (i = 0; i < 25; i++)
//STRIP001                         Application::Reschedule();
//STRIP001
//STRIP001                     if ( bBreak )
//STRIP001                         break; // das Verschicken wurde unterbrochen
//STRIP001                     nEndRow = pImpl->pMergeData ? pImpl->pMergeData->xResultSet->getRow() : 0;
//STRIP001                 } while( !bCancel &&
//STRIP001                         (bSynchronizedDoc && (nStartRow != nEndRow) ? ExistsNextRecord() : ToNextMergeRecord()));
//STRIP001              pDoc->SetNewDBMgr( pOldDBMgr );
//STRIP001              pView->GetDocShell()->OwnerLock( FALSE );
//STRIP001
//STRIP001          }
//STRIP001             // remove the temporary file
//STRIP001          SWUnoHelper::UCB_DeleteFile( sTmpName );
//STRIP001          SW_MOD()->SetView(&pSh->GetView());
//STRIP001      }
//STRIP001
//STRIP001      nMergeType = DBMGR_INSERT;
//STRIP001  }
//STRIP001  return bLoop;
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung:   Serienbriefe als einzelne Dokumente speichern
 --------------------------------------------------------------------*/

//STRIP001 BOOL SwNewDBMgr::MergeMailFiles(SwWrtShell* pSh)
//STRIP001 {
//STRIP001  //check if the doc is synchronized and contains at least one linked section
//STRIP001  BOOL bSynchronizedDoc = pSh->IsLabelDoc() && pSh->GetSectionFmtCount() > 1;
//STRIP001  BOOL bLoop = TRUE;
//STRIP001
//STRIP001  Reference< XPropertySet > xColumnProp;
//STRIP001  {
//STRIP001      USHORT nColPos = 0;
//STRIP001      BOOL bColumnName = sEMailAddrFld.Len() > 0;
//STRIP001
//STRIP001      if (bColumnName)
//STRIP001      {
//STRIP001             Reference< XColumnsSupplier > xColsSupp( pImpl->pMergeData->xResultSet, UNO_QUERY );
//STRIP001          Reference <XNameAccess> xCols = xColsSupp->getColumns();
//STRIP001          if(!xCols->hasByName(sEMailAddrFld))
//STRIP001              return FALSE;
//STRIP001          Any aCol = xCols->getByName(sEMailAddrFld);
//STRIP001             aCol >>= xColumnProp;
//STRIP001      }
//STRIP001
//STRIP001      SfxDispatcher* pSfxDispatcher = pSh->GetView().GetViewFrame()->GetDispatcher();
//STRIP001         SwDocShell* pDocSh = pSh->GetView().GetDocShell();
//STRIP001         pSfxDispatcher->Execute( pDocSh->HasName() ? SID_SAVEDOC : SID_SAVEASDOC, SFX_CALLMODE_SYNCHRON|SFX_CALLMODE_RECORD);
//STRIP001         if( !pDocSh->IsModified() )
//STRIP001      {
//STRIP001          // Beim Speichern wurde kein Abbruch gedrueckt
//STRIP001          SfxMedium* pOrig = pSh->GetView().GetDocShell()->GetMedium();
//STRIP001          String sOldName(pOrig->GetURLObject().GetMainURL( INetURLObject::NO_DECODE ));
//STRIP001          const SfxFilter* pSfxFlt = SwIoSystem::GetFileFilter(
//STRIP001                                                  sOldName, ::aEmptyStr );
//STRIP001          String sAddress;
//STRIP001          bCancel = FALSE;
//STRIP001
//STRIP001          PrintMonitor aPrtMonDlg(&pSh->GetView().GetEditWin());
//STRIP001          aPrtMonDlg.aDocName.SetText(pSh->GetView().GetDocShell()->GetTitle(22));
//STRIP001
//STRIP001          aPrtMonDlg.aCancel.SetClickHdl(LINK(this, SwNewDBMgr, PrtCancelHdl));
//STRIP001             if (!IsMergeSilent())
//STRIP001                 aPrtMonDlg.Show();
//STRIP001
//STRIP001          SwDocShell *pDocSh = pSh->GetView().GetDocShell();
//STRIP001          // Progress, um KeyInputs zu unterbinden
//STRIP001          SfxProgress aProgress(pDocSh, ::aEmptyStr, 1);
//STRIP001
//STRIP001          // Alle Dispatcher sperren
//STRIP001          SfxViewFrame* pViewFrm = SfxViewFrame::GetFirst(pDocSh);
//STRIP001          while (pViewFrm)
//STRIP001          {
//STRIP001              pViewFrm->GetDispatcher()->Lock(TRUE);
//STRIP001              pViewFrm = SfxViewFrame::GetNext(*pViewFrm, pDocSh);
//STRIP001          }
//STRIP001          ULONG nDocNo = 1;
//STRIP001          ULONG nCounter = 0;
//STRIP001          String sExt( INetURLObject( sOldName ).GetExtension() );
//STRIP001             sExt.InsertAscii(".", 0);
//STRIP001
//STRIP001             long nStartRow, nEndRow;
//STRIP001             do
//STRIP001             {
//STRIP001                 nStartRow = pImpl->pMergeData ? pImpl->pMergeData->xResultSet->getRow() : 0;
//STRIP001                 {
//STRIP001                  String sPath(sSubject);
//STRIP001
//STRIP001                  if( bColumnName )
//STRIP001                  {
//STRIP001                      SwDBFormatData aDBFormat;
//STRIP001                      sAddress = GetDBField( xColumnProp, aDBFormat);
//STRIP001                      if (!sAddress.Len())
//STRIP001                          sAddress = '_';
//STRIP001                      sPath += sAddress;
//STRIP001                      nCounter = 0;
//STRIP001                  }
//STRIP001
//STRIP001                  INetURLObject aEntry(sPath);
//STRIP001                  String sLeading(aEntry.GetBase());
//STRIP001                  aEntry.removeSegment();
//STRIP001                  sPath = aEntry.GetMainURL( INetURLObject::NO_DECODE );
//STRIP001                  utl::TempFile aTemp(sLeading,&sExt,&sPath );
//STRIP001
//STRIP001                  if( !aTemp.IsValid() )
//STRIP001                  {
//STRIP001                      ErrorHandler::HandleError( ERRCODE_IO_NOTSUPPORTED );
//STRIP001                      bLoop = FALSE;
//STRIP001                      bCancel = TRUE;
//STRIP001                  }
//STRIP001                  else
//STRIP001                  {
//STRIP001                      INetURLObject aTempFile(aTemp.GetURL());
//STRIP001                      aPrtMonDlg.aPrinter.SetText( aTempFile.GetBase() );
//STRIP001                      String sStat(SW_RES(STR_STATSTR_LETTER));   // Brief
//STRIP001                      sStat += ' ';
//STRIP001                      sStat += String::CreateFromInt32( nDocNo++ );
//STRIP001                      aPrtMonDlg.aPrintInfo.SetText(sStat);
//STRIP001
//STRIP001                      // Rechenzeit fuer Save-Monitor:
//STRIP001                      for (USHORT i = 0; i < 10; i++)
//STRIP001                          Application::Reschedule();
//STRIP001
//STRIP001                      // Neues Dokument erzeugen und speichern
//STRIP001                      SfxObjectShellRef xDocSh( new SwDocShell( SFX_CREATE_MODE_INTERNAL ));
//STRIP001                      SfxMedium* pMed = new SfxMedium( sOldName, STREAM_STD_READ, TRUE );
//STRIP001                      pMed->SetFilter( pSfxFlt );
//STRIP001
//STRIP001                      if (xDocSh->DoLoad(pMed))
//STRIP001                      {
//STRIP001                             //create a view frame for the document
//STRIP001                             SfxViewFrame* pFrame = SFX_APP()->CreateViewFrame( *xDocSh, 0, TRUE );
//STRIP001                             //request the layout calculation
//STRIP001                             ((SwView*) pFrame->GetViewShell())->GetWrtShellPtr()->CalcLayout();
//STRIP001                             SwDoc* pDoc = ((SwDocShell*)(&xDocSh))->GetDoc();
//STRIP001                          SwNewDBMgr* pOldDBMgr = pDoc->GetNewDBMgr();
//STRIP001                          pDoc->SetNewDBMgr( this );
//STRIP001                          pDoc->UpdateFlds(0);
//STRIP001
//STRIP001                          // alle versteckten Felder/Bereiche entfernen
//STRIP001                          pDoc->RemoveInvisibleContent();
//STRIP001
//STRIP001                             // launch MailMergeEvent if required
//STRIP001                             const SwXMailMerge *pEvtSrc = GetMailMergeEvtSrc();
//STRIP001                             if (pEvtSrc)
//STRIP001                             {
//STRIP001                                 Reference< XInterface > xRef( (XMailMergeBroadcaster *) pEvtSrc );
//STRIP001                                 text::MailMergeEvent aEvt( xRef, xDocSh->GetModel() );
//STRIP001                                 pEvtSrc->LaunchMailMergeEvent( aEvt );
//STRIP001                             }
//STRIP001
//STRIP001                          SfxMedium* pDstMed = new SfxMedium(
//STRIP001                              aTempFile.GetMainURL( INetURLObject::NO_DECODE ),
//STRIP001                              STREAM_STD_READWRITE, TRUE );
//STRIP001                          pDstMed->SetFilter( pSfxFlt );
//STRIP001
//STRIP001                          xDocSh->DoSaveAs(*pDstMed);
//STRIP001                          xDocSh->DoSaveCompleted(pDstMed);
//STRIP001                          if( xDocSh->GetError() )
//STRIP001                          {
//STRIP001                              // error message ??
//STRIP001                              ErrorHandler::HandleError( xDocSh->GetError() );
//STRIP001                              bCancel = TRUE;
//STRIP001                              bLoop = FALSE;
//STRIP001                          }
//STRIP001                          pDoc->SetNewDBMgr( pOldDBMgr );
//STRIP001                      }
//STRIP001                      xDocSh->DoClose();
//STRIP001                  }
//STRIP001              }
//STRIP001                 nEndRow = pImpl->pMergeData ? pImpl->pMergeData->xResultSet->getRow() : 0;
//STRIP001             } while( !bCancel &&
//STRIP001                 (bSynchronizedDoc && (nStartRow != nEndRow)? ExistsNextRecord() : ToNextMergeRecord()));
//STRIP001          // Alle Dispatcher freigeben
//STRIP001          pViewFrm = SfxViewFrame::GetFirst(pDocSh);
//STRIP001          while (pViewFrm)
//STRIP001          {
//STRIP001              pViewFrm->GetDispatcher()->Lock(FALSE);
//STRIP001              pViewFrm = SfxViewFrame::GetNext(*pViewFrm, pDocSh);
//STRIP001          }
//STRIP001
//STRIP001          SW_MOD()->SetView(&pSh->GetView());
//STRIP001      }
//STRIP001
//STRIP001      nMergeType = DBMGR_INSERT;
//STRIP001  }
//STRIP001
//STRIP001  return bLoop;
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung:
  --------------------------------------------------------------------*/

//STRIP001 IMPL_LINK_INLINE_START( SwNewDBMgr, PrtCancelHdl, Button *, pButton )
//STRIP001 {
//STRIP001  pButton->GetParent()->Hide();
//STRIP001  bCancel = TRUE;
//STRIP001  return 0;
//STRIP001 }
//STRIP001 IMPL_LINK_INLINE_END( SwNewDBMgr, PrtCancelHdl, Button *, pButton )


/*--------------------------------------------------------------------
    Beschreibung: Numberformat der Spalte ermitteln und ggfs. in
                    den uebergebenen Formatter uebertragen
  --------------------------------------------------------------------*/

//STRIP001 ULONG SwNewDBMgr::GetColumnFmt( const String& rDBName,
//STRIP001                              const String& rTableName,
//STRIP001                              const String& rColNm,
//STRIP001                              SvNumberFormatter* pNFmtr,
//STRIP001                              long nLanguage )
//STRIP001 {
//STRIP001  ULONG nRet = 0;
//STRIP001  if(pNFmtr)
//STRIP001  {
//STRIP001         Reference< XDataSource> xSource;
//STRIP001         Reference< XConnection> xConnection;
//STRIP001         sal_Bool bUseMergeData = sal_False;
//STRIP001         if(pImpl->pMergeData &&
//STRIP001             pImpl->pMergeData->sDataSource.equals(rDBName) && pImpl->pMergeData->sCommand.equals(rTableName))
//STRIP001      {
//STRIP001             xConnection = pImpl->pMergeData->xConnection;
//STRIP001          Reference<XDataSource> xSource = SwNewDBMgr::getDataSourceAsParent(xConnection,rDBName);
//STRIP001             bUseMergeData = sal_True;
//STRIP001      }
//STRIP001         if(!xConnection.is() || !xSource.is())
//STRIP001         {
//STRIP001             SwDSParam* pParam = FindDSConnection(rDBName, FALSE);
//STRIP001             if(pParam && pParam->xConnection.is())
//STRIP001                 xConnection = pParam->xConnection;
//STRIP001             else
//STRIP001             {
//STRIP001                 rtl::OUString sDBName(rDBName);
//STRIP001                 xConnection = RegisterConnection( sDBName );
//STRIP001             }
//STRIP001             if(bUseMergeData)
//STRIP001                 pImpl->pMergeData->xConnection = xConnection;
//STRIP001         }
//STRIP001         Reference< XColumnsSupplier> xColsSupp = SwNewDBMgr::GetColumnSupplier(xConnection, rTableName);
//STRIP001      if(xColsSupp.is())
//STRIP001      {
//STRIP001          Reference <XNameAccess> xCols;
//STRIP001             try
//STRIP001             {
//STRIP001                 xCols = xColsSupp->getColumns();
//STRIP001             }
//STRIP001             catch(Exception&)
//STRIP001             {
//STRIP001                 DBG_ERROR("Exception in getColumns()")
//STRIP001             }
//STRIP001             if(!xCols.is() || !xCols->hasByName(rColNm))
//STRIP001              return nRet;
//STRIP001          Any aCol = xCols->getByName(rColNm);
//STRIP001             Reference< XPropertySet > xColumn;
//STRIP001             aCol >>= xColumn;
//STRIP001             nRet = GetColumnFmt(xSource, xConnection, xColumn, pNFmtr, nLanguage);
//STRIP001         }
//STRIP001         else
//STRIP001          nRet = pNFmtr->GetFormatIndex( NF_NUMBER_STANDARD, LANGUAGE_SYSTEM );
//STRIP001  }
//STRIP001  return nRet;
//STRIP001 }
/* -----------------------------07.06.01 15:43--------------------------------

 ---------------------------------------------------------------------------*/
//STRIP001 ULONG SwNewDBMgr::GetColumnFmt( Reference< XDataSource> xSource,
//STRIP001                         Reference< XConnection> xConnection,
//STRIP001                         Reference< XPropertySet> xColumn,
//STRIP001                      SvNumberFormatter* pNFmtr,
//STRIP001                         long nLanguage )
//STRIP001 {
//STRIP001  //JP 12.01.99: ggfs. das NumberFormat im Doc setzen
//STRIP001  ULONG nRet = 0;
//STRIP001
//STRIP001     if(!xSource.is())
//STRIP001     {
//STRIP001         Reference<XChild> xChild(xConnection, UNO_QUERY);
//STRIP001         xSource = Reference<XDataSource>(xChild->getParent(), UNO_QUERY);
//STRIP001     }
//STRIP001     if(xSource.is() && xConnection.is() && xColumn.is() && pNFmtr)
//STRIP001  {
//STRIP001      SvNumberFormatsSupplierObj* pNumFmt = new SvNumberFormatsSupplierObj( pNFmtr );
//STRIP001      Reference< util::XNumberFormatsSupplier >  xDocNumFmtsSupplier = pNumFmt;
//STRIP001      Reference< XNumberFormats > xDocNumberFormats = xDocNumFmtsSupplier->getNumberFormats();
//STRIP001      Reference< XNumberFormatTypes > xDocNumberFormatTypes(xDocNumberFormats, UNO_QUERY);
//STRIP001
//STRIP001      String sLanguage, sCountry;
//STRIP001         ::ConvertLanguageToIsoNames( (USHORT)nLanguage, sLanguage, sCountry );
//STRIP001      Locale aLocale;
//STRIP001      aLocale.Language = sLanguage;
//STRIP001      aLocale.Country = sCountry;
//STRIP001
//STRIP001      //get the number formatter of the data source
//STRIP001      Reference<XPropertySet> xSourceProps(xSource, UNO_QUERY);
//STRIP001      Reference< XNumberFormats > xNumberFormats;
//STRIP001      if(xSourceProps.is())
//STRIP001      {
//STRIP001          Any aFormats = xSourceProps->getPropertyValue(C2U("NumberFormatsSupplier"));
//STRIP001          if(aFormats.hasValue())
//STRIP001          {
//STRIP001                 Reference<XNumberFormatsSupplier> xSuppl;
//STRIP001                 aFormats >>= xSuppl;
//STRIP001              if(xSuppl.is())
//STRIP001              {
//STRIP001                  xNumberFormats = xSuppl->getNumberFormats();
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001         Any aFormat = xColumn->getPropertyValue(C2U("FormatKey"));
//STRIP001         if(aFormat.hasValue())
//STRIP001         {
//STRIP001             sal_Int32 nFmt;
//STRIP001             aFormat >>= nFmt;
//STRIP001             if(xNumberFormats.is())
//STRIP001             {
//STRIP001                 try
//STRIP001                 {
//STRIP001                     Reference<XPropertySet> xNumProps = xNumberFormats->getByKey( nFmt );
//STRIP001                     Any aFormat = xNumProps->getPropertyValue(C2U("FormatString"));
//STRIP001                     Any aLocale = xNumProps->getPropertyValue(C2U("Locale"));
//STRIP001                     rtl::OUString sFormat;
//STRIP001                     aFormat >>= sFormat;
//STRIP001                     com::sun::star::lang::Locale aLoc;
//STRIP001                     aLocale >>= aLoc;
//STRIP001                     nFmt = xDocNumberFormats->queryKey( sFormat, aLoc, sal_False );
//STRIP001                     if(NUMBERFORMAT_ENTRY_NOT_FOUND == nFmt)
//STRIP001                         nFmt = xDocNumberFormats->addNew( sFormat, aLoc );
//STRIP001                     nRet = nFmt;
//STRIP001                 }
//STRIP001                 catch(Exception&)
//STRIP001                 {
//STRIP001                     DBG_ERROR("illegal number format key")
//STRIP001                 }
//STRIP001             }
//STRIP001         }
//STRIP001         else
//STRIP001             nRet = SwNewDBMgr::GetDbtoolsClient().getDefaultNumberFormat(xColumn, xDocNumberFormatTypes,  aLocale);
//STRIP001  }
//STRIP001  return nRet;
//STRIP001 }

/* -----------------------------17.07.00 09:47--------------------------------

 ---------------------------------------------------------------------------*/
//STRIP001 sal_Int32 SwNewDBMgr::GetColumnType( const String& rDBName,
//STRIP001                        const String& rTableName,
//STRIP001                        const String& rColNm )
//STRIP001 {
//STRIP001  sal_Int32 nRet = DataType::SQLNULL;
//STRIP001     SwDSParam* pParam = FindDSConnection(rDBName, FALSE);
//STRIP001     Reference< XConnection> xConnection;
//STRIP001     if(pParam && pParam->xConnection.is())
//STRIP001         xConnection = pParam->xConnection;
//STRIP001     else
//STRIP001     {
//STRIP001         rtl::OUString sDBName(rDBName);
//STRIP001         xConnection = RegisterConnection( sDBName );
//STRIP001     }
//STRIP001  Reference< XColumnsSupplier> xColsSupp = SwNewDBMgr::GetColumnSupplier(xConnection, rTableName);
//STRIP001  if(xColsSupp.is())
//STRIP001  {
//STRIP001          Reference <XNameAccess> xCols = xColsSupp->getColumns();
//STRIP001      if(xCols->hasByName(rColNm))
//STRIP001      {
//STRIP001          Any aCol = xCols->getByName(rColNm);
//STRIP001             Reference <XPropertySet> xCol;
//STRIP001             aCol >>= xCol;
//STRIP001          Any aType = xCol->getPropertyValue(C2S("Type"));
//STRIP001          aType >>= nRet;
//STRIP001      }
//STRIP001  }
//STRIP001  return nRet;
//STRIP001 }

/* -----------------------------03.07.00 17:12--------------------------------

 ---------------------------------------------------------------------------*/
/*?*/ Reference< sdbc::XConnection> SwNewDBMgr::GetConnection(const String& rDataSource,
/*?*/                                                   Reference<XDataSource>& rxSource)
/*?*/ {
/*?*/   Reference< sdbc::XConnection> xConnection;
/*?*/   Reference<XNameAccess> xDBContext;
/*?*/   Reference< XMultiServiceFactory > xMgr( ::legacy_binfilters::getLegacyProcessServiceFactory() );
/*?*/   if( xMgr.is() )
/*?*/   {
/*?*/       Reference<XInterface> xInstance = xMgr->createInstance( C2U( "com.sun.star.sdb.DatabaseContext" ));
/*?*/       xDBContext = Reference<XNameAccess>(xInstance, UNO_QUERY) ;
/*?*/   }
/*?*/   DBG_ASSERT(xDBContext.is(), "com.sun.star.sdb.DataBaseContext: service not available")
/*?*/   if(xDBContext.is())
/*?*/   {
/*?*/       try
/*?*/       {
/*?*/           if(xDBContext->hasByName(rDataSource))
/*?*/           {
/*?*/               Reference<XCompletedConnection> xComplConnection;
/*?*/               xDBContext->getByName(rDataSource) >>= xComplConnection;
/*?*/               rxSource = Reference<XDataSource>(xComplConnection, UNO_QUERY);
/*?*/
/*?*/               Reference< XInteractionHandler > xHandler(
/*?*/                   xMgr->createInstance( C2U( "com.sun.star.sdb.InteractionHandler" )), UNO_QUERY);
/*?*/               xConnection = xComplConnection->connectWithCompletion( xHandler );
/*?*/           }
/*?*/       }
/*?*/       catch(Exception&) {}
/*?*/   }
/*?*/   return xConnection;
/*?*/ }
/* -----------------------------03.07.00 17:12--------------------------------

 ---------------------------------------------------------------------------*/
//STRIP001 Reference< sdbcx::XColumnsSupplier> SwNewDBMgr::GetColumnSupplier(Reference<sdbc::XConnection> xConnection,
//STRIP001                                  const String& rTableOrQuery,
//STRIP001                                  BYTE    eTableOrQuery)
//STRIP001 {
//STRIP001  Reference< sdbcx::XColumnsSupplier> xRet;
//STRIP001  if(SW_DB_SELECT_QUERY != eTableOrQuery)
//STRIP001  {
//STRIP001      Reference<XTablesSupplier> xTSupplier = Reference<XTablesSupplier>(xConnection, UNO_QUERY);
//STRIP001      if(xTSupplier.is())
//STRIP001      {
//STRIP001          Reference<XNameAccess> xTbls = xTSupplier->getTables();
//STRIP001          if(xTbls->hasByName(rTableOrQuery))
//STRIP001              try
//STRIP001              {
//STRIP001                  Any aTable = xTbls->getByName(rTableOrQuery);
//STRIP001                     Reference<XPropertySet> xPropSet;
//STRIP001                     aTable >>= xPropSet;
//STRIP001                  xRet = Reference<XColumnsSupplier>(xPropSet, UNO_QUERY);
//STRIP001              }
//STRIP001              catch(Exception&){}
//STRIP001      }
//STRIP001  }
//STRIP001  if(!xRet.is() && SW_DB_SELECT_QUERY != SW_DB_SELECT_TABLE)
//STRIP001  {
//STRIP001      Reference<XQueriesSupplier> xQSupplier = Reference<XQueriesSupplier>(xConnection, UNO_QUERY);
//STRIP001      if(xQSupplier.is())
//STRIP001      {
//STRIP001          Reference<XNameAccess> xQueries = xQSupplier->getQueries();
//STRIP001          if ( xQueries->hasByName(rTableOrQuery) )
//STRIP001              try
//STRIP001              {
//STRIP001                  xQueries->getByName(rTableOrQuery) >>= xRet;
//STRIP001              }
//STRIP001              catch(Exception&)
//STRIP001              {
//STRIP001              }
//STRIP001      }
//STRIP001  }
//STRIP001  return xRet;
//STRIP001 }
/* -----------------------------05.07.00 13:44--------------------------------

 ---------------------------------------------------------------------------*/
//STRIP001 String SwNewDBMgr::GetDBField(Reference<XPropertySet> xColumnProps,
//STRIP001                      const SwDBFormatData& rDBFormatData,
//STRIP001                      double* pNumber)
//STRIP001 {
//STRIP001  Reference< XColumn > xColumn(xColumnProps, UNO_QUERY);
//STRIP001  String sRet;
//STRIP001  DBG_ASSERT(xColumn.is(), "SwNewDBMgr::::ImportDBField: illegal arguments")
//STRIP001  if(!xColumn.is())
//STRIP001      return sRet;
//STRIP001
//STRIP001  Any aType = xColumnProps->getPropertyValue(C2U("Type"));
//STRIP001  sal_Int32 eDataType;
//STRIP001  aType >>= eDataType;
//STRIP001  switch(eDataType)
//STRIP001  {
//STRIP001      case DataType::CHAR:
//STRIP001      case DataType::VARCHAR:
//STRIP001      case DataType::LONGVARCHAR:
//STRIP001          sRet = xColumn->getString();
//STRIP001      break;
//STRIP001      case DataType::BIT:
//STRIP001      case DataType::TINYINT:
//STRIP001      case DataType::SMALLINT:
//STRIP001      case DataType::INTEGER:
//STRIP001      case DataType::BIGINT:
//STRIP001      case DataType::FLOAT:
//STRIP001      case DataType::REAL:
//STRIP001      case DataType::DOUBLE:
//STRIP001      case DataType::NUMERIC:
//STRIP001      case DataType::DECIMAL:
//STRIP001      case DataType::DATE:
//STRIP001      case DataType::TIME:
//STRIP001      case DataType::TIMESTAMP:
//STRIP001      {
//STRIP001 //           ::Date aTempDate(rDBFormatData.aNullDate.Day,
//STRIP001 //               rDBFormatData.aNullDate.Month, rDBFormatData.aNullDate.Year);
//STRIP001
//STRIP001          try
//STRIP001          {
//STRIP001                 SwDbtoolsClient& aClient = SwNewDBMgr::GetDbtoolsClient();
//STRIP001                 sRet = aClient.getValue(
//STRIP001                  xColumnProps,
//STRIP001                  rDBFormatData.xFormatter,
//STRIP001                  rDBFormatData.aLocale,
//STRIP001                  rDBFormatData.aNullDate);
//STRIP001              double fVal = xColumn->getDouble();
//STRIP001              if (pNumber)
//STRIP001                  *pNumber = fVal;
//STRIP001          }
//STRIP001             catch(Exception& )
//STRIP001          {
//STRIP001              DBG_ERROR("exception caught")
//STRIP001          }
//STRIP001
//STRIP001      }
//STRIP001      break;
//STRIP001
//STRIP001 //       case DataType::BINARY:
//STRIP001 //       case DataType::VARBINARY:
//STRIP001 //       case DataType::LONGVARBINARY:
//STRIP001 //       case DataType::SQLNULL:
//STRIP001 //       case DataType::OTHER:
//STRIP001 //       case DataType::OBJECT:
//STRIP001 //       case DataType::DISTINCT:
//STRIP001 //       case DataType::STRUCT:
//STRIP001 //       case DataType::ARRAY:
//STRIP001 //       case DataType::BLOB:
//STRIP001 //       case DataType::CLOB:
//STRIP001 //       case DataType::REF:
//STRIP001 //       default:
//STRIP001  }
//STRIP001 //   if (pFormat)
//STRIP001 //   {
//STRIP001 //       SFX_ITEMSET_GET(*pCol, pFormatItem, SfxUInt32Item, SBA_DEF_FMTVALUE, sal_True);
//STRIP001 //       *pFormat = pFormatItem->GetValue();
//STRIP001 //   }
//STRIP001
//STRIP001  return sRet;
//STRIP001 }
/* -----------------------------06.07.00 14:28--------------------------------
    releases the merge data source table or query after merge is completed
 ---------------------------------------------------------------------------*/
/*N*/ void  SwNewDBMgr::EndMerge()
/*N*/ {
/*N*/   DBG_ASSERT(bInMerge, "merge is not active")
/*N*/   bInMerge = FALSE;
/*N*/     delete pImpl->pMergeData;
/*N*/     pImpl->pMergeData = 0;
/*N*/ }
/* -----------------------------06.07.00 14:28--------------------------------
    checks if a desired data source table or query is open
 ---------------------------------------------------------------------------*/
/*N*/ BOOL    SwNewDBMgr::IsDataSourceOpen(const String& rDataSource,
/*N*/             const String& rTableOrQuery, sal_Bool bMergeOnly)
/*N*/ {
/*N*/     if(pImpl->pMergeData)
/*N*/   {
/*N*/         return !bMergeLock &&
/*N*/                 rDataSource == (String)pImpl->pMergeData->sDataSource &&
/*N*/                     rTableOrQuery == (String)pImpl->pMergeData->sCommand &&
/*N*/                     pImpl->pMergeData->xResultSet.is();
/*N*/   }
/*N*/     else if(!bMergeOnly)
/*N*/     {
/*N*/         SwDBData aData;
/*N*/         aData.sDataSource = rDataSource;
/*N*/         aData.sCommand = rTableOrQuery;
/*N*/         aData.nCommandType = -1;
/*N*/         SwDSParam* pFound = FindDSData(aData, FALSE);
/*N*/         return (pFound && pFound->xResultSet.is());
/*N*/     }
/*N*/     return sal_False;
/*N*/ }
/* -----------------------------17.07.00 16:44--------------------------------
    read column data a a specified position
 ---------------------------------------------------------------------------*/
//STRIP001 BOOL SwNewDBMgr::GetColumnCnt(const String& rSourceName, const String& rTableName,
//STRIP001                          const String& rColumnName, sal_uInt32 nAbsRecordId,
//STRIP001                          long nLanguage,
//STRIP001                          String& rResult, double* pNumber)
//STRIP001 {
//STRIP001  BOOL bRet = FALSE;
//STRIP001     SwDSParam* pFound = 0;
//STRIP001     //check if it's the merge data source
//STRIP001     if(pImpl->pMergeData &&
//STRIP001         rSourceName == (String)pImpl->pMergeData->sDataSource &&
//STRIP001         rTableName == (String)pImpl->pMergeData->sCommand)
//STRIP001  {
//STRIP001         pFound = pImpl->pMergeData;
//STRIP001     }
//STRIP001     else
//STRIP001  {
//STRIP001         SwDBData aData;
//STRIP001         aData.sDataSource = rSourceName;
//STRIP001         aData.sCommand = rTableName;
//STRIP001         aData.nCommandType = -1;
//STRIP001         pFound = FindDSData(aData, FALSE);
//STRIP001     }
//STRIP001     //check validity of supplied record Id
//STRIP001     if(pFound->aSelection.getLength())
//STRIP001     {
//STRIP001         //the destination has to be an element of the selection
//STRIP001         const Any* pSelection = pFound->aSelection.getConstArray();
//STRIP001         sal_Bool bFound = sal_False;
//STRIP001         for(sal_Int32 nPos = 0; !bFound && nPos < pFound->aSelection.getLength(); nPos++)
//STRIP001         {
//STRIP001             sal_Int32 nSelection;
//STRIP001             pSelection[nPos] >>= nSelection;
//STRIP001             if(nSelection == static_cast<sal_Int32>(nAbsRecordId))
//STRIP001                 bFound = sal_True;
//STRIP001         }
//STRIP001         if(!bFound)
//STRIP001             return FALSE;
//STRIP001     }
//STRIP001     if(pFound && pFound->xResultSet.is() && !pFound->bAfterSelection)
//STRIP001     {
//STRIP001         sal_Int32 nOldRow = 0;
//STRIP001         try
//STRIP001         {
//STRIP001             nOldRow = pFound->xResultSet->getRow();
//STRIP001         }
//STRIP001         catch(const Exception& )
//STRIP001         {
//STRIP001          return FALSE;
//STRIP001         }
//STRIP001         //position to the desired index
//STRIP001         BOOL bMove = TRUE;
//STRIP001         if ( nOldRow != static_cast<sal_Int32>(nAbsRecordId) )
//STRIP001             bMove = lcl_MoveAbsolute(pFound, nAbsRecordId);
//STRIP001         if(bMove)
//STRIP001         {
//STRIP001             bRet = lcl_GetColumnCnt(pFound, rColumnName, nLanguage, rResult, pNumber);
//STRIP001         }
//STRIP001         if ( nOldRow != static_cast<sal_Int32>(nAbsRecordId) )
//STRIP001             bMove = lcl_MoveAbsolute(pFound, nOldRow);
//STRIP001     }
//STRIP001  return bRet;
//STRIP001 }
/* -----------------------------06.07.00 16:47--------------------------------
    reads the column data at the current position
 ---------------------------------------------------------------------------*/
//STRIP001 BOOL SwNewDBMgr::GetMergeColumnCnt(const String& rColumnName, USHORT nLanguage,
//STRIP001                              String &rResult, double *pNumber, sal_uInt32 *pFormat)
//STRIP001 {
//STRIP001     if(!pImpl->pMergeData || !pImpl->pMergeData->xResultSet.is() || pImpl->pMergeData->bAfterSelection )
//STRIP001  {
//STRIP001      rResult.Erase();
//STRIP001      return FALSE;
//STRIP001  }
//STRIP001
//STRIP001     BOOL bRet = lcl_GetColumnCnt(pImpl->pMergeData, rColumnName, nLanguage, rResult, pNumber);
//STRIP001  return bRet;
//STRIP001 }
/* -----------------------------07.07.00 14:28--------------------------------

 ---------------------------------------------------------------------------*/
//STRIP001 BOOL SwNewDBMgr::ToNextMergeRecord()
//STRIP001 {
//STRIP001     DBG_ASSERT(pImpl->pMergeData && pImpl->pMergeData->xResultSet.is(), "no data source in merge")
//STRIP001     return ToNextRecord(pImpl->pMergeData);
//STRIP001 }
/* -----------------------------10.07.01 14:28--------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ BOOL SwNewDBMgr::ToNextRecord(
/*N*/     const String& rDataSource, const String& rCommand, sal_Int32 nCommandType)
/*N*/ {
/*N*/     SwDSParam* pFound = 0;
/*N*/     BOOL bRet = TRUE;
/*N*/     if(pImpl->pMergeData &&
/*N*/         rDataSource == (String)pImpl->pMergeData->sDataSource &&
/*N*/         rCommand == (String)pImpl->pMergeData->sCommand)
/*N*/         pFound = pImpl->pMergeData;
/*N*/     else
/*N*/     {
/*N*/         SwDBData aData;
/*N*/         aData.sDataSource = rDataSource;
/*N*/         aData.sCommand = rCommand;
/*N*/         aData.nCommandType = -1;
/*N*/         pFound = FindDSData(aData, FALSE);
/*N*/     }
/*N*/     return ToNextRecord(pFound);
/*N*/ }
/* -----------------------------10.07.01 14:38--------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ BOOL SwNewDBMgr::ToNextRecord(SwDSParam* pParam)
/*N*/ {
/*N*/     BOOL bRet = TRUE;
/*N*/     if(!pParam || !pParam->xResultSet.is() || pParam->bEndOfDB ||
/*N*/           (pParam->aSelection.getLength() && pParam->aSelection.getLength() <= pParam->nSelectionIndex))
/*N*/   {
/*N*/         if(pParam)
/*N*/             pParam->CheckEndOfDB();
/*N*/       return FALSE;
/*N*/   }
/*N*/   try
/*N*/   {
/*N*/         if(pParam->aSelection.getLength())
/*N*/       {
/*N*/           sal_Int32 nPos = 0;
/*N*/           pParam->aSelection.getConstArray()[ pParam->nSelectionIndex++ ] >>= nPos;
/*N*/             pParam->bEndOfDB = !pParam->xResultSet->absolute( nPos );
/*N*/             pParam->CheckEndOfDB();
/*N*/             bRet = !pParam->bEndOfDB;
/*N*/             if(pParam->nSelectionIndex >= pParam->aSelection.getLength())
/*N*/                 pParam->bEndOfDB = TRUE;
/*N*/       }
/*N*/       else
/*N*/       {
/*N*/             pParam->bEndOfDB = !pParam->xResultSet->next();
/*N*/             pParam->CheckEndOfDB();
/*N*/             bRet = !pParam->bEndOfDB;
/*N*/             ++pParam->nSelectionIndex;
/*N*/       }
/*N*/   }
/*N*/     catch(Exception&)
/*N*/   {
/*N*/   }
/*N*/     return bRet;
/*N*/ }

/* -----------------------------13.07.00 17:23--------------------------------
    synchronized labels contain a next record field at their end
    to assure that the next page can be created in mail merge
    the cursor position must be validated
 ---------------------------------------------------------------------------*/
//STRIP001 BOOL SwNewDBMgr::ExistsNextRecord() const
//STRIP001 {
//STRIP001     return pImpl->pMergeData && !pImpl->pMergeData->bEndOfDB;
//STRIP001 }
/* -----------------------------13.07.00 10:41--------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ sal_uInt32    SwNewDBMgr::GetSelectedRecordId()
/*N*/ {
/*N*/   sal_uInt32  nRet = 0;
/*N*/     DBG_ASSERT(pImpl->pMergeData && pImpl->pMergeData->xResultSet.is(), "no data source in merge")
/*N*/     if(!pImpl->pMergeData || !pImpl->pMergeData->xResultSet.is())
/*N*/       return FALSE;
/*N*/   try
/*N*/   {
/*N*/         nRet = pImpl->pMergeData->xResultSet->getRow();
/*N*/   }
/*N*/     catch(Exception& )
/*N*/   {
/*N*/   }
/*N*/   return nRet;
/*N*/ }
/* -----------------------------13.07.00 10:58--------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ sal_Bool SwNewDBMgr::ToRecordId(sal_Int32 nSet)
/*N*/ {DBG_ASSERT(0, "STRIP"); return FALSE;//STRIP001
//STRIP001 /*?*/     DBG_ASSERT(pImpl->pMergeData && pImpl->pMergeData->xResultSet.is(), "no data source in merge")
//STRIP001 /*?*/     if(!pImpl->pMergeData || !pImpl->pMergeData->xResultSet.is()|| nSet < 0)
//STRIP001 /*?*/        return FALSE;
//STRIP001 /*?*/    sal_Bool bRet = FALSE;
//STRIP001 /*?*/     sal_Int32 nAbsPos = nSet;
//STRIP001 /*?*/
//STRIP001 /*?*/    if(nAbsPos >= 0)
//STRIP001 /*?*/    {
//STRIP001 /*?*/         bRet = lcl_MoveAbsolute(pImpl->pMergeData, nAbsPos);
//STRIP001 /*?*/         pImpl->pMergeData->bEndOfDB = !bRet;
//STRIP001 /*?*/         pImpl->pMergeData->CheckEndOfDB();
//STRIP001 /*?*/    }
//STRIP001 /*?*/    return bRet;
/*N*/ }
/* -----------------------------17.07.00 14:50--------------------------------

 ---------------------------------------------------------------------------*/
//STRIP001 void lcl_ExtractMembers(const String& rDBName, String& sSource, String& sTable, String& sStatement)
//STRIP001 {
//STRIP001  sSource = rDBName.GetToken(0, DB_DELIM);
//STRIP001  sTable = rDBName.GetToken(0).GetToken(1, DB_DELIM);
//STRIP001  sal_uInt16 nPos;
//STRIP001  if ((nPos = rDBName.Search(';')) != STRING_NOTFOUND)
//STRIP001      sStatement = rDBName.Copy(nPos + 1);
//STRIP001 }
/* -----------------------------17.07.00 14:17--------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ BOOL SwNewDBMgr::OpenDataSource(const String& rDataSource, const String& rTableOrQuery, sal_Int32 nCommandType)
/*N*/ {
/*?*/     SwDBData aData;
/*?*/     aData.sDataSource = rDataSource;
/*?*/     aData.sCommand = rTableOrQuery;
/*?*/     aData.nCommandType = nCommandType;
/*?*/
/*?*/     SwDSParam* pFound = FindDSData(aData, TRUE);
/*?*/   Reference< XDataSource> xSource;
/*?*/   if(pFound->xResultSet.is())
/*?*/       return TRUE;
/*?*/     SwDSParam* pParam = FindDSConnection(rDataSource, FALSE);
/*?*/     Reference< XConnection> xConnection;
/*?*/     if(pParam && pParam->xConnection.is())
/*?*/         pFound->xConnection = pParam->xConnection;
/*?*/     else
/*?*/     {
/*?*/         rtl::OUString sDataSource(rDataSource);
/*?*/         pFound->xConnection = RegisterConnection( sDataSource );
/*?*/     }
/*?*/   if(pFound->xConnection.is())
/*?*/   {
/*?*/       try
/*?*/       {
/*?*/           Reference< sdbc::XDatabaseMetaData >  xMetaData = pFound->xConnection->getMetaData();
/*?*/             try
/*?*/             {
/*?*/                 pFound->bScrollable = xMetaData
/*?*/                       ->supportsResultSetType((sal_Int32)ResultSetType::SCROLL_INSENSITIVE);
/*?*/             }
/*?*/             catch(Exception&)
/*?*/             {
/*?*/                 //#98373# DB driver may not be ODBC 3.0 compliant
/*?*/                 pFound->bScrollable = TRUE;
/*?*/             }
/*?*/           pFound->xStatement = pFound->xConnection->createStatement();
/*?*/             rtl::OUString aQuoteChar = xMetaData->getIdentifierQuoteString();
/*?*/             rtl::OUString sStatement(C2U("SELECT * FROM "));
/*?*/             sStatement = C2U("SELECT * FROM ");
/*?*/             sStatement += aQuoteChar;
/*?*/             sStatement += rTableOrQuery;
/*?*/             sStatement += aQuoteChar;
/*?*/             pFound->xResultSet = pFound->xStatement->executeQuery( sStatement );
/*?*/
/*?*/           //after executeQuery the cursor must be positioned
/*?*/             pFound->bEndOfDB = !pFound->xResultSet->next();
/*?*/             pFound->bAfterSelection = sal_False;
/*?*/             pFound->CheckEndOfDB();
/*?*/             ++pFound->nSelectionIndex;
/*?*/       }
/*?*/       catch (Exception&)
/*?*/       {
/*?*/           pFound->xResultSet = 0;
/*?*/           pFound->xStatement = 0;
/*?*/           pFound->xConnection = 0;
/*?*/       }
/*?*/   }
/*?*/   return pFound->xResultSet.is();
/*N*/ }
/* -----------------------------14.08.2001 10:26------------------------------

 ---------------------------------------------------------------------------*/
/*?*/ Reference< XConnection> SwNewDBMgr::RegisterConnection(rtl::OUString& rDataSource)
/*?*/ {
/*?*/     SwDSParam* pFound = SwNewDBMgr::FindDSConnection(rDataSource, TRUE);
/*?*/     Reference< XDataSource> xSource;
/*?*/     if(!pFound->xConnection.is())
/*?*/   {
/*?*/         pFound->xConnection = SwNewDBMgr::GetConnection(rDataSource, xSource );
/*?*/         try
/*?*/         {
/*?*/             Reference<XComponent> xComponent(pFound->xConnection, UNO_QUERY);
/*?*/             if(xComponent.is())
/*?*/                 xComponent->addEventListener(pImpl->xDisposeListener);
/*?*/         }
/*?*/         catch(Exception&)
/*?*/         {
/*?*/         }
/*?*/   }
/*?*/     return pFound->xConnection;
/*?*/ }
/* -----------------------------17.07.00 15:55--------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ sal_uInt32      SwNewDBMgr::GetSelectedRecordId(
/*N*/     const String& rDataSource, const String& rTableOrQuery, sal_Int32 nCommandType)
/*N*/ {
/*N*/   sal_uInt32 nRet = -1;
/*N*/   //check for merge data source first
/*N*/     if(pImpl->pMergeData && rDataSource == (String)pImpl->pMergeData->sDataSource &&
/*N*/                     rTableOrQuery == (String)pImpl->pMergeData->sCommand &&
/*N*/                     (nCommandType == -1 || nCommandType == pImpl->pMergeData->nCommandType) &&
/*N*/                     pImpl->pMergeData->xResultSet.is())
/*N*/       nRet = GetSelectedRecordId();
/*N*/   else
/*N*/   {
/*N*/         SwDBData aData;
/*N*/         aData.sDataSource = rDataSource;
/*N*/         aData.sCommand = rTableOrQuery;
/*N*/         aData.nCommandType = nCommandType;
/*N*/         SwDSParam* pFound = FindDSData(aData, FALSE);
/*N*/       if(pFound && pFound->xResultSet.is())
/*N*/       {
/*N*/           try
/*N*/           {   //if a selection array is set the current row at the result set may not be set yet
/*N*/               if(pFound->aSelection.getLength())
/*N*/               {
/*N*/                   sal_Int32 nSelIndex = pFound->nSelectionIndex;
/*N*/                     if(nSelIndex >= pFound->aSelection.getLength())
/*N*/                       nSelIndex = pFound->aSelection.getLength() -1;
/*N*/                   pFound->aSelection.getConstArray()[nSelIndex] >>= nRet;
/*N*/
/*N*/               }
/*N*/               else
/*N*/                   nRet = pFound->xResultSet->getRow();
/*N*/           }
/*N*/           catch(Exception&){}
/*N*/       }
/*N*/   }
/*N*/   return nRet;
/*N*/ }

/* -----------------------------17.07.00 14:18--------------------------------
    close all data sources - after fields were updated
 ---------------------------------------------------------------------------*/
/*N*/ void  SwNewDBMgr::CloseAll(BOOL bIncludingMerge)
/*N*/ {
/*N*/     //the only thing done here is to reset the selection index
/*N*/   //all connections stay open
/*N*/     for(USHORT nPos = 0; nPos < aDataSourceParams.Count(); nPos++)
/*N*/     {
/*N*/         SwDSParam* pParam = aDataSourceParams[nPos];
/*N*/         if(bIncludingMerge || pParam != pImpl->pMergeData)
/*N*/         {
/*N*/           pParam->nSelectionIndex = 0;
/*N*/           pParam->bAfterSelection = sal_False;
/*N*/             try
/*N*/             {
/*N*/                 if(!bInMerge && pParam->xResultSet.is())
/*N*/                     pParam->xResultSet->first();
/*N*/             }
/*N*/             catch(Exception& )
/*N*/             {}
/*N*/         }
/*N*/     }
/*N*/ }
/* -----------------------------17.07.00 14:54--------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ SwDSParam* SwNewDBMgr::FindDSData(const SwDBData& rData, BOOL bCreate)
/*N*/ {
/*N*/   SwDSParam* pFound = 0;
/*N*/   for(USHORT nPos = aDataSourceParams.Count(); nPos; nPos--)
/*N*/   {
/*N*/       SwDSParam* pParam = aDataSourceParams[nPos - 1];
/*N*/         if(rData.sDataSource == pParam->sDataSource &&
/*N*/             rData.sCommand == pParam->sCommand &&
/*N*/             (rData.nCommandType == -1 || rData.nCommandType == pParam->nCommandType ||
/*N*/             (bCreate && pParam->nCommandType == -1)))
/*N*/           {
/*N*/                 //#94779# calls from the calculator may add a connection with an invalid commandtype
/*N*/                 //later added "real" data base connections have to re-use the already available
/*N*/                 //DSData and set the correct CommandType
/*N*/                 if(bCreate && pParam->nCommandType == -1)
/*N*/                     pParam->nCommandType = rData.nCommandType;
/*N*/               pFound = pParam;
/*N*/               break;
/*N*/           }
/*N*/   }
/*N*/   if(bCreate)
/*N*/   {
/*N*/       if(!pFound)
/*N*/       {
/*N*/             pFound = new SwDSParam(rData);
/*N*/           aDataSourceParams.Insert(pFound, aDataSourceParams.Count());
/*N*/             try
/*N*/             {
/*N*/                 Reference<XComponent> xComponent(pFound->xConnection, UNO_QUERY);
/*N*/                 if(xComponent.is())
/*N*/                     xComponent->addEventListener(pImpl->xDisposeListener);
/*N*/             }
/*N*/             catch(Exception&)
/*N*/             {
/*N*/             }
/*N*/         }
/*N*/   }
/*N*/   return pFound;
/*N*/ }
/* -----------------------------14.08.2001 10:27------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ SwDSParam*  SwNewDBMgr::FindDSConnection(const rtl::OUString& rDataSource, BOOL bCreate)
/*N*/ {
/*N*/   SwDSParam* pFound = 0;
/*N*/   for(USHORT nPos = 0; nPos < aDataSourceParams.Count(); nPos++)
/*N*/   {
/*N*/       SwDSParam* pParam = aDataSourceParams[nPos];
/*N*/         if(rDataSource == pParam->sDataSource)
/*N*/         {
/*N*/             pFound = pParam;
/*N*/             break;
/*N*/         }
/*N*/   }
/*N*/   if(bCreate && !pFound)
/*N*/   {
/*?*/         SwDBData aData;
/*?*/         aData.sDataSource = rDataSource;
/*?*/         pFound = new SwDSParam(aData);
/*?*/       aDataSourceParams.Insert(pFound, aDataSourceParams.Count());
/*?*/         try
/*?*/         {
/*?*/             Reference<XComponent> xComponent(pFound->xConnection, UNO_QUERY);
/*?*/             if(xComponent.is())
/*?*/                 xComponent->addEventListener(pImpl->xDisposeListener);
/*?*/         }
/*?*/         catch(Exception&)
/*?*/         {
/*?*/         }
/*N*/     }
/*N*/   return pFound;
/*N*/ }

/* -----------------------------17.07.00 14:31--------------------------------
    rDBName: <Source> + DB_DELIM + <Table>; + <Statement>
 ---------------------------------------------------------------------------*/
/*M*/ void    SwNewDBMgr::AddDSData(const SwDBData& rData, long nSelStart, long nSelEnd)
/*M*/ {
/*M*/     SwDSParam* pFound = FindDSData(rData, TRUE);
/*M*/     if(nSelStart > 0)
/*M*/   {
/*M*/         if(nSelEnd < nSelStart)
/*M*/       {
/*M*/           sal_uInt32 nZw = nSelEnd;
/*M*/           nSelEnd = nSelStart;
/*M*/           nSelStart = nZw;
/*M*/       }
/*M*/
/*M*/         pFound->aSelection.realloc(nSelEnd - nSelStart + 1);
/*M*/         Any* pSelection = pFound->aSelection.getArray();
/*M*/         for (long i = nSelStart; i <= nSelEnd; i++, ++pSelection)
/*M*/             *pSelection <<= i;
/*M*/   }
/*M*/     else
/*M*/         pFound->aSelection.realloc(0);
/*M*/ }
/* -----------------------------17.07.00 14:31--------------------------------

 ---------------------------------------------------------------------------*/
/*M*/ void    SwNewDBMgr::GetDSSelection(const SwDBData& rData, long& rSelStart, long& rSelEnd)
/*M*/ {
/*M*/     SwDSParam* pFound = FindDSData(rData, FALSE);
/*M*/     if(!pFound || !pFound->aSelection.getLength())
/*M*/       rSelStart = -1L;
/*M*/   else
/*M*/   {
/*M*/         pFound->aSelection.getConstArray()[0] >>= rSelStart;
/*M*/         pFound->aSelection.getConstArray()[pFound->aSelection.getLength() - 1] >>= rSelEnd;
/*M*/     }
/*M*/ }
/* -----------------------------17.07.00 14:34--------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ const SwDBData&   SwNewDBMgr::GetAddressDBName()
/*N*/ {
/*N*/   return SW_MOD()->GetDBConfig()->GetAddressSource();
/*N*/ }
/* -----------------------------18.07.00 13:13--------------------------------

 ---------------------------------------------------------------------------*/
//STRIP001 Sequence<rtl::OUString> SwNewDBMgr::GetExistingDatabaseNames()
//STRIP001 {
//STRIP001  Reference<XNameAccess> xDBContext;
//STRIP001  Reference< XMultiServiceFactory > xMgr( ::legacy_binfilters::getLegacyProcessServiceFactory() );
//STRIP001  if( xMgr.is() )
//STRIP001  {
//STRIP001      Reference<XInterface> xInstance = xMgr->createInstance( C2U( "com.sun.star.sdb.DatabaseContext" ));
//STRIP001      xDBContext = Reference<XNameAccess>(xInstance, UNO_QUERY) ;
//STRIP001  }
//STRIP001  if(xDBContext.is())
//STRIP001  {
//STRIP001      return xDBContext->getElementNames();
//STRIP001  }
//STRIP001     return Sequence<rtl::OUString>();
//STRIP001 }
/* -----------------------------10.11.00 17:10--------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ void SwNewDBMgr::ExecuteFormLetter(   SwWrtShell& rSh,
/*N*/                         const Sequence<PropertyValue>& rProperties,
/*N*/                         BOOL bWithDataSourceBrowser)
/*N*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  //prevent second call
//STRIP001     if(pImpl->pMergeDialog)
//STRIP001      return ;
//STRIP001     rtl::OUString sDataSource, sDataTableOrQuery;
//STRIP001     Sequence<Any> aSelection;
//STRIP001
//STRIP001  sal_Int32 nSelectionPos = 0;
//STRIP001     sal_Int32 nResultSetIdx = -1;
//STRIP001  sal_Int16 nCmdType = CommandType::TABLE;
//STRIP001     Reference< XConnection> xConnection;
//STRIP001
//STRIP001  ODataAccessDescriptor aDescriptor(rProperties);
//STRIP001  aDescriptor[daDataSource]   >>= sDataSource;
//STRIP001  aDescriptor[daCommand]      >>= sDataTableOrQuery;
//STRIP001  aDescriptor[daCommandType]  >>= nCmdType;
//STRIP001
//STRIP001  if ( aDescriptor.has(daSelection) )
//STRIP001      aDescriptor[daSelection] >>= aSelection;
//STRIP001  if ( aDescriptor.has(daConnection) )
//STRIP001      aDescriptor[daConnection] >>= xConnection;
//STRIP001
//STRIP001     if(!sDataSource.getLength() || !sDataTableOrQuery.getLength())
//STRIP001  {
//STRIP001      DBG_ERROR("PropertyValues missing or unset")
//STRIP001      return;
//STRIP001  }
//STRIP001
//STRIP001     pImpl->pMergeDialog = new SwMailMergeDlg(
//STRIP001                  &rSh.GetView().GetViewFrame()->GetWindow(), rSh,
//STRIP001                  sDataSource,
//STRIP001                  sDataTableOrQuery,
//STRIP001                     nCmdType,
//STRIP001                     xConnection,
//STRIP001                     bWithDataSourceBrowser ? 0 : &aSelection );
//STRIP001
//STRIP001     if(pImpl->pMergeDialog->Execute() == RET_OK)
//STRIP001  {
//STRIP001      aDescriptor[daSelection] <<= pImpl->pMergeDialog->GetSelection();
//STRIP001
//STRIP001         Reference<XResultSet> xResSet = pImpl->pMergeDialog->GetResultSet();
//STRIP001         if(xResSet.is())
//STRIP001          aDescriptor[daCursor] <<= xResSet;
//STRIP001
//STRIP001         OFF_APP()->NotifyEvent(SfxEventHint(SW_EVENT_MAIL_MERGE, rSh.GetView().GetViewFrame()->GetObjectShell()));
//STRIP001         MergeNew(pImpl->pMergeDialog->GetMergeType(), rSh, aDescriptor);
//STRIP001         OFF_APP()->NotifyEvent(SfxEventHint(SW_EVENT_MAIL_MERGE_END, rSh.GetView().GetViewFrame()->GetObjectShell()));
//STRIP001
//STRIP001      // reset the cursor inside
//STRIP001      xResSet = NULL;
//STRIP001      aDescriptor[daCursor] <<= xResSet;
//STRIP001  }
//STRIP001     DELETEZ(pImpl->pMergeDialog);
/*N*/ }
/* -----------------------------13.11.00 08:20--------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ void SwNewDBMgr::InsertText(SwWrtShell& rSh,
/*N*/                       const Sequence< PropertyValue>& rProperties)
/*N*/ {
/*?*/     DBG_ASSERT(0, "STRIP"); //STRIP001 rtl::OUString sDataSource, sDataTableOrQuery;
//STRIP001 /*?*/    Reference<XResultSet>  xResSet;
//STRIP001 /*?*/     Sequence<Any> aSelection;
//STRIP001 /*?*/    BOOL bHasSelectionProperty = FALSE;
//STRIP001 /*?*/    sal_Int32 nSelectionPos = 0;
//STRIP001 /*?*/    sal_Int16 nCmdType = CommandType::TABLE;
//STRIP001 /*?*/    const PropertyValue* pValues = rProperties.getConstArray();
//STRIP001 /*?*/     Reference< XConnection> xConnection;
//STRIP001 /*?*/     for(sal_Int32 nPos = 0; nPos < rProperties.getLength(); nPos++)
//STRIP001 /*?*/    {
//STRIP001 /*?*/         if(pValues[nPos].Name.equalsAsciiL(RTL_CONSTASCII_STRINGPARAM(cDataSourceName)))
//STRIP001 /*?*/            pValues[nPos].Value >>= sDataSource;
//STRIP001 /*?*/         else if(pValues[nPos].Name.equalsAsciiL(RTL_CONSTASCII_STRINGPARAM(cCommand)))
//STRIP001 /*?*/            pValues[nPos].Value >>= sDataTableOrQuery;
//STRIP001 /*?*/         else if(pValues[nPos].Name.equalsAsciiL(RTL_CONSTASCII_STRINGPARAM(cCursor)))
//STRIP001 /*?*/            pValues[nPos].Value >>= xResSet;
//STRIP001 /*?*/         else if(pValues[nPos].Name.equalsAsciiL(RTL_CONSTASCII_STRINGPARAM(cSelection)))
//STRIP001 /*?*/        {
//STRIP001 /*?*/            bHasSelectionProperty = TRUE;
//STRIP001 /*?*/            nSelectionPos = nPos;
//STRIP001 /*?*/            pValues[nPos].Value >>= aSelection;
//STRIP001 /*?*/        }
//STRIP001 /*?*/         else if(pValues[nPos].Name.equalsAsciiL(RTL_CONSTASCII_STRINGPARAM(cCommandType)))
//STRIP001 /*?*/            pValues[nPos].Value >>= nCmdType;
//STRIP001 /*?*/         else if(pValues[nPos].Name.equalsAsciiL(RTL_CONSTASCII_STRINGPARAM(cActiveConnection)))
//STRIP001 /*?*/             pValues[nPos].Value >>= xConnection;
//STRIP001 /*?*/     }
//STRIP001 /*?*/    if(!sDataSource.getLength() || !sDataTableOrQuery.getLength() || !xResSet.is())
//STRIP001 /*?*/    {
//STRIP001 /*?*/        DBG_ERROR("PropertyValues missing or unset")
//STRIP001 /*?*/        return;
//STRIP001 /*?*/    }
//STRIP001 /*?*/    Reference< XMultiServiceFactory > xMgr( ::legacy_binfilters::getLegacyProcessServiceFactory() );
//STRIP001 /*?*/     Reference<XDataSource> xSource;
//STRIP001 /*?*/     Reference<XChild> xChild(xConnection, UNO_QUERY);
//STRIP001 /*?*/     if(xChild.is())
//STRIP001 /*?*/         xSource = Reference<XDataSource>(xChild->getParent(), UNO_QUERY);
//STRIP001 /*?*/     if(!xSource.is())
//STRIP001 /*?*/         xSource = SwNewDBMgr::GetDbtoolsClient().getDataSource(sDataSource, xMgr);
//STRIP001 /*?*/    Reference< XColumnsSupplier > xColSupp( xResSet, UNO_QUERY );
//STRIP001 /*?*/    SwDBData aDBData;
//STRIP001 /*?*/    aDBData.sDataSource = sDataSource;
//STRIP001 /*?*/    aDBData.sCommand = sDataTableOrQuery;
//STRIP001 /*?*/    aDBData.nCommandType = nCmdType;
//STRIP001 /*?*/
//STRIP001 /*?*/    SwInsertDBColAutoPilot *pDlg = new SwInsertDBColAutoPilot(
//STRIP001 /*?*/            rSh.GetView(),
//STRIP001 /*?*/            xSource,
//STRIP001 /*?*/            xColSupp,
//STRIP001 /*?*/            aDBData );
//STRIP001 /*?*/    if( RET_OK == pDlg->Execute() )
//STRIP001 /*?*/    {
//STRIP001 /*?*/         rtl::OUString sDummy;
//STRIP001 /*?*/         if(!xConnection.is())
//STRIP001 /*?*/             xConnection = xSource->getConnection(sDummy, sDummy);
//STRIP001 /*?*/         try
//STRIP001 /*?*/         {
//STRIP001 /*?*/             pDlg->DataToDoc( aSelection , xSource, xConnection, xResSet);
//STRIP001 /*?*/         }
//STRIP001 /*?*/         catch(Exception& )
//STRIP001 /*?*/         {
//STRIP001 /*?*/             DBG_ERROR("exception caught")
//STRIP001 /*?*/         }
//STRIP001 /*?*/     }
//STRIP001 /*?*/    delete pDlg;
//STRIP001 /*?*/
/*N*/ }
/* -----------------------------30.08.2001 12:00------------------------------

 ---------------------------------------------------------------------------*/
SwDbtoolsClient* SwNewDBMgr::pDbtoolsClient = NULL;

SwDbtoolsClient& SwNewDBMgr::GetDbtoolsClient()
{
    if ( !pDbtoolsClient )
        pDbtoolsClient = new SwDbtoolsClient;
    return *pDbtoolsClient;
}
/* -----------------13.05.2003 15:34-----------------

 --------------------------------------------------*/
void SwNewDBMgr::RemoveDbtoolsClient()
{
    delete pDbtoolsClient;
    pDbtoolsClient = 0;
}
/* -----------------------------20.08.2002 12:00------------------------------

 ---------------------------------------------------------------------------*/
/*M*/ Reference<XDataSource> SwNewDBMgr::getDataSourceAsParent(const Reference< XConnection>& _xConnection,const ::rtl::OUString& _sDataSourceName)
/*M*/ {
/*M*/   Reference<XDataSource> xSource;
/*M*/   Reference<XChild> xChild(_xConnection, UNO_QUERY);
/*M*/   if ( xChild.is() )
/*M*/       xSource = Reference<XDataSource>(xChild->getParent(), UNO_QUERY);
/*M*/   if ( !xSource.is() )
/*M*/       xSource = SwNewDBMgr::GetDbtoolsClient().getDataSource(_sDataSourceName, ::legacy_binfilters::getLegacyProcessServiceFactory());
/*M*/
/*M*/   return xSource;
/*M*/ }
/* -----------------------------20.08.2002 12:00------------------------------

 ---------------------------------------------------------------------------*/
/*M*/ Reference<XResultSet> SwNewDBMgr::createCursor(const ::rtl::OUString& _sDataSourceName,
/*M*/                                      const ::rtl::OUString& _sCommand,
/*M*/                                      sal_Int32 _nCommandType,
/*M*/                                      const Reference<XConnection>& _xConnection
/*M*/                                     )
/*M*/ {
/*M*/   Reference<XResultSet> xResultSet;
/*M*/   try
/*M*/   {
/*M*/       Reference< XMultiServiceFactory > xMgr( ::legacy_binfilters::getLegacyProcessServiceFactory() );
/*M*/       if( xMgr.is() )
/*M*/       {
/*M*/           Reference<XInterface> xInstance = xMgr->createInstance(
/*M*/               C2U( "com.sun.star.sdb.RowSet" ));
/*M*/           Reference <XPropertySet> xRowSetPropSet(xInstance, UNO_QUERY);
/*M*/           if(xRowSetPropSet.is())
/*M*/           {
/*M*/               xRowSetPropSet->setPropertyValue(C2U("DataSourceName"), makeAny(_sDataSourceName));
/*M*/               xRowSetPropSet->setPropertyValue(C2U("ActiveConnection"), makeAny(_xConnection));
/*M*/               xRowSetPropSet->setPropertyValue(C2U("Command"), makeAny(_sCommand));
/*M*/               xRowSetPropSet->setPropertyValue(C2U("CommandType"), makeAny(_nCommandType));
/*M*/
/*M*/               Reference< XCompletedExecution > xRowSet(xInstance, UNO_QUERY);
/*M*/
/*M*/               if ( xRowSet.is() )
/*M*/               {
/*M*/                   Reference< XInteractionHandler > xHandler(xMgr->createInstance(C2U("com.sun.star.sdb.InteractionHandler")), UNO_QUERY);
/*M*/                   xRowSet->executeWithCompletion(xHandler);
/*M*/               }
/*M*/               xResultSet = Reference<XResultSet>(xRowSet, UNO_QUERY);
/*M*/           }
/*M*/       }
/*M*/   }
/*M*/   catch(const Exception&)
/*M*/   {
/*M*/       DBG_ASSERT(0,"Catched exception while creating a new RowSet!");
/*M*/   }
/*M*/   return xResultSet;
/*M*/ }
/* -----------------09.12.2002 12:38-----------------
 *
 * --------------------------------------------------*/
/*N*/ SwConnectionDisposedListener_Impl::SwConnectionDisposedListener_Impl(SwNewDBMgr& rMgr) :
/*N*/     rDBMgr(rMgr)
/*N*/ {};
/* -----------------09.12.2002 12:39-----------------
 *
 * --------------------------------------------------*/
/*N*/ SwConnectionDisposedListener_Impl::~SwConnectionDisposedListener_Impl()
/*N*/ {};
/* -----------------09.12.2002 12:39-----------------
 *
 * --------------------------------------------------*/
/*N*/ void SwConnectionDisposedListener_Impl::disposing( const EventObject& rSource )
/*N*/         throw (RuntimeException)
/*N*/ {
/*N*/     ::vos::OGuard aGuard(Application::GetSolarMutex());
/*N*/     Reference<XConnection> xSource(rSource.Source, UNO_QUERY);
/*N*/     for(USHORT nPos = rDBMgr.aDataSourceParams.Count(); nPos; nPos--)
/*N*/     {
/*N*/         SwDSParam* pParam = rDBMgr.aDataSourceParams[nPos - 1];
/*N*/         if(pParam->xConnection.is() &&
/*N*/                 (xSource == pParam->xConnection))
/*N*/         {
/*N*/             rDBMgr.aDataSourceParams.DeleteAndDestroy(nPos - 1);
/*N*/         }
/*N*/     }
/*N*/ }


