/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sch_schlib.cxx,v $
 *
 *  $Revision: 1.8 $
 *
 *  last change: $Author: vg $ $Date: 2007-10-15 11:49:06 $
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
#pragma optimize("",off)
#endif


#ifndef _SFX_DOCFILT_HACK_HXX //autogen
#include <bf_sfx2/docfilt.hxx>
#endif

#ifndef _SFXAPP_HXX
#include <bf_sfx2/app.hxx>
#endif

#ifndef _SO_CLSIDS_HXX
#include <so3/clsids.hxx>
#endif

#include <sot/formats.hxx>
#include "schmod.hxx"
#include "docshell.hxx"
#include "schlib.hxx"

class ValueSet;

#include "res_bmp.hrc"
namespace binfilter {

#define SCH_FORMAT_STR_50_FORMAT String( RTL_CONSTASCII_USTRINGPARAM( "StarChart 5.0" ))

/*?*/ TYPEINIT1( SchModuleDummy, SfxModule );

extern "C" { static void SAL_CALL thisModule() {} }

/*?*/ SFX_IMPL_OBJECTFACTORY_LIB( SchChartDocShell, SFXOBJECTSHELL_STD_NORMAL, schart,
                            SvGlobalName(BF_SO3_SCH_CLASSID), Sch, String( RTL_CONSTASCII_USTRINGPARAM( DLL_NAME )) )
// from macro: void __EXPORT SchChartDocShell::InitFactory()
/*?*/ {
/*?*/   ULONG nFormat50 = SOT_FORMATSTR_ID_STARCHART_50;
/*?*/   SfxObjectFactory& rFactory = (SfxObjectFactory&)Factory();
/*?*/   rFactory.SetDocumentServiceName(String::CreateFromAscii("com.sun.star.chart.ChartDocument"));
/*?*/ }

/*************************************************************************
|*
|* Konstruktor
|*
\************************************************************************/

/*?*/ SchDLL::SchDLL()
/*?*/ {
/*?*/ }

/*************************************************************************
|*
|* Destruktor
|*
\************************************************************************/

/*?*/ SchDLL::~SchDLL()
/*?*/ {
/*?*/ }

/*************************************************************************
|*
|*
|*
\************************************************************************/


/*?*/ void SchDLL::LibInit()
/*?*/ {
/*?*/   // Das Anlegen des ResMgr ist nur fuer die obige Filter-Registierung
/*?*/   // notwendig. Sobald dort kein SdResId mehr notwendig ist, kann das
/*?*/   // Anlegen entfallen
/*?*/   SchChartDocShell::RegisterFactory(SDT_SCH_DOCFACTPRIO);
/*?*/
/*?*/   SCH_MOD() = (SchModule *) new SchModuleDummy(NULL, TRUE, &SchChartDocShell::Factory() );
/*?*/ }

/*************************************************************************
|*
|*
|*
\************************************************************************/


/*?*/ void SchDLL::LibExit()
/*?*/ {
/*?*/   FreeLibSch();
/*?*/
/*?*/   // destroy the dummy-module with Object-Factory-Pointer
/*?*/   DELETEZ( SCH_MOD() );
/*?*/ }

/*************************************************************************
|*
|*
|*
\************************************************************************/


/*N*/ void __EXPORT SchDLL::Update( SvInPlaceObjectRef aIPObj, SchMemChart* pData, OutputDevice* pOut )
/*N*/ {
/*N*/   void (__LOADONCALLAPI*fp)(SvInPlaceObjectRef, SchMemChart*, OutputDevice*);
/*N*/
/*N*/   fp = (void (__LOADONCALLAPI*)(SvInPlaceObjectRef, SchMemChart*, OutputDevice*))GetFuncSch("SchUpdate");
/*N*/
/*N*/   if (fp)
/*N*/   {
/*N*/   fp(aIPObj, pData, pOut);
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|*
|*
\************************************************************************/


/*N*/ void __EXPORT SchDLL::Update( SvInPlaceObjectRef aIPObj, SchMemChart* pData, const SfxItemSet& rAttr, OutputDevice* pOut )
/*N*/ {
/*N*/   void (__LOADONCALLAPI*fp)(SvInPlaceObjectRef, SchMemChart*, const SfxItemSet&, OutputDevice*);
/*N*/
/*N*/   fp = (void (__LOADONCALLAPI*)(SvInPlaceObjectRef, SchMemChart*, const SfxItemSet&, OutputDevice*))GetFuncSch("SchUpdateAttr");
/*N*/
/*N*/   if (fp)
/*N*/   {
/*N*/   fp(aIPObj, pData, rAttr, pOut);
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|*
|*
\************************************************************************/


/*N*/ SchMemChart* __EXPORT SchDLL::GetChartData (SvInPlaceObjectRef aIPObj)
/*N*/ {
/*N*/   SchMemChart* (__LOADONCALLAPI*fp)(SvInPlaceObjectRef);
/*N*/
/*N*/   fp = (SchMemChart* (__LOADONCALLAPI*)(SvInPlaceObjectRef aIPObj))GetFuncSch("SchGetChartData");
/*N*/
/*N*/   return fp
/*N*/              ? fp (aIPObj)
/*N*/              : 0;
/*N*/ }

/*************************************************************************
|*
|*
|*
\************************************************************************/

/*N*/ SchMemChart* __EXPORT SchDLL::NewMemChart ()
/*N*/ {
/*?*/   SchMemChart* (__LOADONCALLAPI*fp)();
/*?*/
/*?*/   fp = (SchMemChart* (__LOADONCALLAPI*)())GetFuncSch("SchNewMemChartNone");
/*?*/
/*?*/   return fp
/*?*/              ? fp ()
/*?*/              : 0;
/*N*/ }

/*************************************************************************
|*
|*
|*
\************************************************************************/

/*N*/ SchMemChart* __EXPORT SchDLL::NewMemChart (short nCols, short nRows)
/*N*/ {
/*N*/   SchMemChart* (__LOADONCALLAPI*fp)(short, short);
/*N*/
/*N*/   fp = (SchMemChart* (__LOADONCALLAPI*)(short, short))GetFuncSch("SchNewMemChartXY");
/*N*/
/*N*/   if (fp)
/*N*/   {
/*N*/       return fp(nCols, nRows);
/*N*/   }
/*N*/   else return 0;
/*N*/ }

/*************************************************************************
|*
|*
|*
\************************************************************************/

/*?*/ SchMemChart* __EXPORT SchDLL::NewMemChart (const SchMemChart &rMemChart)
/*?*/ {
/*?*/   SchMemChart* (__LOADONCALLAPI*fp)(const SchMemChart &);
/*?*/
/*?*/   fp = (SchMemChart* (__LOADONCALLAPI*)(const SchMemChart &))GetFuncSch("SchNewMemChartCopy");
/*?*/
/*?*/   if (fp)
/*?*/   {
/*?*/       return fp(rMemChart);
/*?*/   }
/*?*/   else return 0;
/*?*/ }

/*************************************************************************
|*
|*
|*
\************************************************************************/

/*?*/ ChartModel __EXPORT *SchDLL::GetModel (SvInPlaceObjectRef aIPObj)
/*?*/ {
/*?*/   ChartModel *(__LOADONCALLAPI*fp)(SvInPlaceObjectRef);
/*?*/
/*?*/   fp = (ChartModel* (__LOADONCALLAPI*)(SvInPlaceObjectRef))GetFuncSch("SchGetModel");
/*?*/
/*?*/   if (fp)
/*?*/   {
/*?*/       return fp(aIPObj);
/*?*/   }
/*?*/   else return 0;
/*?*/ }

/*************************************************************************
|*
|*
|*
\************************************************************************/


/*?*/ void __EXPORT SchDLL::SetTransparentBackground( SvInPlaceObjectRef aIPObj, BOOL bTransp )
/*?*/ {
/*?*/   void (__LOADONCALLAPI*fp)(SvInPlaceObjectRef, BOOL );
/*?*/
/*?*/   fp = (void (__LOADONCALLAPI*)(SvInPlaceObjectRef, BOOL))GetFuncSch("SchSetTransparent");
/*?*/
/*?*/   if (fp)
/*?*/   {
/*?*/   fp(aIPObj, bTransp);
/*?*/   }
/*?*/ }

/*N*/ void __EXPORT SchDLL::GetDefaultForColumnText( const SchMemChart& rMemChart, sal_Int32 nCol, String& aResult )
/*N*/ {
/*N*/   void (__LOADONCALLAPI*fp)( const SchMemChart&, sal_Int32, String& );
/*N*/
/*N*/   fp = (void (__LOADONCALLAPI*)( const SchMemChart&, sal_Int32, String& ))GetFuncSch("SchGetDefaultForColumnText");
/*N*/
/*N*/   if( fp )
/*N*/   {
/*N*/       fp( rMemChart, nCol, aResult );
/*N*/   }
/*N*/ }

/*N*/ void __EXPORT SchDLL::GetDefaultForRowText( const SchMemChart& rMemChart, sal_Int32 nRow, String& aResult )
/*N*/ {
/*N*/   void (__LOADONCALLAPI*fp)( const SchMemChart&, sal_Int32, String& );
/*N*/
/*N*/   fp = (void (__LOADONCALLAPI*)( const SchMemChart&, sal_Int32, String& ))GetFuncSch("SchGetDefaultForRowText");
/*N*/
/*N*/   if( fp )
/*N*/   {
/*N*/       fp( rMemChart, nRow, aResult );
/*N*/   }
/*N*/ }

/*N*/ void __EXPORT SchDLL::ConvertChartRangeForWriter( SchMemChart& rMemChart,
/*N*/                                                   BOOL bOldToNew )
/*N*/ {
/*N*/   void (__LOADONCALLAPI* fp )( SchMemChart&, BOOL )
/*N*/       = (void (__LOADONCALLAPI*)( SchMemChart&, BOOL ))
/*N*/                               GetFuncSch("SchConvertChartRangeForWriter");
/*N*/   if( fp )
/*N*/       fp( rMemChart, bOldToNew );
/*N*/ }

/*?*/ void __EXPORT SchDLL::ConvertChartRangeForCalc( SchMemChart& rMemChart,
/*?*/                                               BOOL bOldToNew )
/*?*/ {
/*?*/   void (__LOADONCALLAPI* fp )( SchMemChart&, BOOL )
/*?*/       = (void (__LOADONCALLAPI*)( SchMemChart&, BOOL ))
/*?*/                               GetFuncSch("SchConvertChartRangeForCalc");
/*?*/   if( fp )
/*?*/       fp( rMemChart, bOldToNew );
/*?*/ }

/*?*/ void __EXPORT SchDLL::MemChartResetTranslation( SchMemChart& rMemChart,
/*?*/                                               long *pTable,long nCnt )
/*?*/ {
/*?*/   void (__LOADONCALLAPI* fp )( SchMemChart&, long*, long )
/*?*/       = (void (__LOADONCALLAPI*)( SchMemChart&, long*, long ))
/*?*/                               GetFuncSch("SchMemChartResetTranslation");
/*?*/   if( fp )
/*?*/       fp( rMemChart, pTable, nCnt );
/*?*/ }

/*?*/ void __EXPORT SchDLL::MemChartUpdateTranslation( SchMemChart& rMemChart,
/*?*/                                                   long *pTable,long nCnt )
/*?*/ {
/*?*/   void (__LOADONCALLAPI* fp )( SchMemChart&, long*, long )
/*?*/       = (void (__LOADONCALLAPI*)( SchMemChart&, long*, long ))
/*?*/                               GetFuncSch("SchMemChartUpdateTranslation");
/*?*/   if( fp )
/*?*/       fp( rMemChart, pTable, nCnt );
/*?*/ }


/*N*/ void __EXPORT SchDLL::MemChartInsertCols( SchMemChart& rMemChart,
/*N*/                                           short nAtCol, short nCount)
/*N*/ {
/*N*/   void (__LOADONCALLAPI* fp )( SchMemChart&, short, short )
/*N*/       = (void (__LOADONCALLAPI*)( SchMemChart&, short, short ))
/*N*/                               GetFuncSch("SchMemChartInsertCols");
/*N*/   if( fp )
/*N*/       fp( rMemChart, nAtCol, nCount );
/*N*/ }
/*?*/ void __EXPORT SchDLL::MemChartRemoveCols( SchMemChart& rMemChart,
/*?*/                                           short nAtCol, short nCount)
/*?*/ {
/*?*/   void (__LOADONCALLAPI* fp )( SchMemChart&, short, short )
/*?*/       = (void (__LOADONCALLAPI*)( SchMemChart&, short, short ))
/*?*/                               GetFuncSch("SchMemChartRemoveCols");
/*?*/   if( fp )
/*?*/       fp( rMemChart, nAtCol, nCount );
/*?*/ }

/*N*/ void __EXPORT SchDLL::MemChartInsertRows( SchMemChart& rMemChart,
/*N*/                                           short nAtRow, short nCount )
/*N*/ {
/*N*/   void (__LOADONCALLAPI* fp )( SchMemChart&, short, short )
/*N*/       = (void (__LOADONCALLAPI*)( SchMemChart&, short, short ))
/*N*/                               GetFuncSch("SchMemChartInsertRows");
/*N*/   if( fp )
/*N*/       fp( rMemChart, nAtRow, nCount );
/*N*/ }
/*?*/ void __EXPORT SchDLL::MemChartRemoveRows( SchMemChart& rMemChart,
/*?*/                                           short nAtRow, short nCount )
/*?*/ {
/*?*/   void (__LOADONCALLAPI* fp )( SchMemChart&, short, short )
/*?*/       = (void (__LOADONCALLAPI*)( SchMemChart&, short, short ))
/*?*/                               GetFuncSch("SchMemChartRemoveRows");
/*?*/   if( fp )
/*?*/       fp( rMemChart, nAtRow, nCount );
/*?*/ }

/*?*/ void __EXPORT SchDLL::MemChartSwapCols( SchMemChart& rMemChart,
/*?*/                                       int nAtCol1, int nAtCol2 )
/*?*/ {
/*?*/   void (__LOADONCALLAPI* fp )( SchMemChart&, int, int )
/*?*/       = (void (__LOADONCALLAPI*)( SchMemChart&, int, int ))
/*?*/                               GetFuncSch("SchMemChartSwapCols");
/*?*/   if( fp )
/*?*/       fp( rMemChart, nAtCol1, nAtCol2 );
/*?*/ }
/*?*/ void __EXPORT SchDLL::MemChartSwapRows( SchMemChart& rMemChart,
/*?*/                                       int nAtRow1,int nAtRow2 )
/*?*/ {
/*?*/   void (__LOADONCALLAPI* fp )( SchMemChart&, int, int )
/*?*/       = (void (__LOADONCALLAPI*)( SchMemChart&, int, int ))
/*?*/                               GetFuncSch("SchMemChartSwapRows");
/*?*/   if( fp )
/*?*/       fp( rMemChart, nAtRow1, nAtRow2);
/*?*/ }




/*************************************************************************
|*
|*
|*
\************************************************************************/

/*?*/ ULONG __EXPORT SchDLL::DetectFilter(
/*?*/   SfxMedium& rMedium,
/*?*/   const SfxFilter** pFilter,
/*?*/   SfxFilterFlags nMust,
/*?*/   SfxFilterFlags nDont )
/*?*/ {
/*?*/   ULONG nReturn = ERRCODE_ABORT;
/*?*/
/*?*/   if (rMedium.GetError() != SVSTREAM_OK)
/*?*/   {
/*?*/       return (rMedium.GetError());
/*?*/   }
/*?*/
/*?*/   SvStorage* pStorage = rMedium.GetStorage();
/*?*/   if( pStorage )
/*?*/   {
/*?*/       // Detect using contained streams (StarChart 3.0)
/*?*/
/*?*/       String aStreamName( RTL_CONSTASCII_USTRINGPARAM( "StarChartDocument" ));
/*?*/
/*?*/       if (pStorage->IsContained( aStreamName ) &&
/*?*/           pStorage->IsStream( aStreamName ))
/*?*/       {
/*?*/           const SfxFilter* pFilt = NULL;
/*?*/
/*?*/           if (*pFilter)
/*?*/           {
/*?*/               pFilt = SFX_APP()->GetFilter( SchChartDocShell::Factory(), (*pFilter)->GetFilterName());
/*?*/           }
/*?*/           else
/*?*/           {
/*?*/               pFilt = SFX_APP()->GetFilter( SchChartDocShell::Factory(), SCH_FORMAT_STR_50_FORMAT );
/*?*/           }
/*?*/
/*?*/           if (pFilt &&
/*?*/               (pFilt->GetFilterFlags() & nMust) == nMust &&
/*?*/               (pFilt->GetFilterFlags() & nDont) == 0)
/*?*/           {
/*?*/               *pFilter = pFilt;
/*?*/               nReturn = ERRCODE_NONE;
/*?*/           }
/*?*/       }
/*?*/   }
/*?*/   else
/*?*/       nReturn = ULONG_MAX;
/*?*/
/*?*/   return (nReturn);
/*?*/ //    return (rMedium.GetError());
/*?*/ }

/*************************************************************************
|*
|* Lade Module von aussen
|*
\************************************************************************/

/*?*/ SfxModule *SchModuleDummy::Load()
/*?*/ {
/*?*/   return (LoadLibSch() ? SCH_MOD() : NULL);
/*?*/ }

/*************************************************************************
|*
|* Bestimme die GUID abh. von der Version
|*
\************************************************************************/

/*?*/ const SvGlobalName SchModuleDummy::GetID (USHORT nFileFormat)
/*?*/ {
/*?*/   SvGlobalName aName;
/*?*/
/*?*/   switch (nFileFormat)
/*?*/   {
/*?*/       case SOFFICE_FILEFORMAT_60:
/*?*/       {
/*?*/           aName = SvGlobalName(BF_SO3_SCH_CLASSID_60);
/*?*/       }
/*?*/       break;
/*?*/
/*?*/       case SOFFICE_FILEFORMAT_50:
/*?*/       {
/*?*/           aName = SvGlobalName(BF_SO3_SCH_CLASSID_50);
/*?*/       }
/*?*/       break;
/*?*/
/*?*/       case SOFFICE_FILEFORMAT_40:
/*?*/       {
/*?*/           aName = SvGlobalName(BF_SO3_SCH_CLASSID_40);
/*?*/       }
/*?*/       break;
/*?*/
/*?*/       case SOFFICE_FILEFORMAT_31:
/*?*/       {
/*?*/           aName = SvGlobalName(BF_SO3_SCH_CLASSID_30);
/*?*/       }
/*?*/       break;
/*?*/
/*?*/       default:
/*?*/       {
/*?*/           DBG_ERROR( "Unknown file format" );
/*?*/       }
/*?*/       break;
/*?*/   }
/*?*/
/*?*/   return aName;
/*?*/ }

/*************************************************************************
|*
|* Bestimme die Version aus der GUID
|*
\************************************************************************/

/*?*/ USHORT SchModuleDummy::HasID (const SvGlobalName &rName)
/*?*/ {
/*?*/   USHORT nRet = 0;
/*?*/
/*?*/   if (GetID(SOFFICE_FILEFORMAT_31) == rName)
/*?*/   {
/*?*/       nRet = SOFFICE_FILEFORMAT_31;
/*?*/   }
/*?*/   else if (GetID(SOFFICE_FILEFORMAT_40) == rName)
/*?*/   {
/*?*/       nRet = SOFFICE_FILEFORMAT_40;
/*?*/   }
/*?*/   else if (GetID(SOFFICE_FILEFORMAT_50) == rName)
/*?*/   {
/*?*/       nRet = SOFFICE_FILEFORMAT_50;
/*?*/   }
/*?*/   else if (GetID(SOFFICE_FILEFORMAT_60) == rName)
/*?*/   {
/*?*/       nRet = SOFFICE_FILEFORMAT_60;
/*?*/   }
/*?*/
/*?*/   return(nRet);
/*?*/ }

}
