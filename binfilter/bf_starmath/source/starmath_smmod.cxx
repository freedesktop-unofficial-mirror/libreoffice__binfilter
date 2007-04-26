/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: starmath_smmod.cxx,v $
 *
 *  $Revision: 1.7 $
 *
 *  last change: $Author: rt $ $Date: 2007-04-26 07:15:51 $
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

#ifndef _SV_STATUS_HXX //autogen
#include <vcl/status.hxx>
#endif
#ifndef _SFXAPP_HXX //autogen
#include <bf_sfx2/app.hxx>
#endif
#ifndef _SFXOBJFACE_HXX //autogen
#include <bf_sfx2/objface.hxx>
#endif
#ifndef _SFX_WHITER_HXX //autogen
#include <svtools/whiter.hxx>
#endif
#ifndef _SFX_HRC //autogen
#include <bf_sfx2/sfx.hrc>
#endif
#ifndef _SVX_SVXIDS_HRC //autogen
#include <bf_svx/svxids.hrc>
#endif
#ifndef INCLUDED_SVTOOLS_SYSLOCALE_HXX
#include <svtools/syslocale.hxx>
#endif

#include <vcl/virdev.hxx>

#ifndef _SFXITEMSET_HXX
#include <svtools/itemset.hxx>
#endif

#ifndef _CONFIG_HXX
#include "config.hxx"
#endif
#ifndef VIEW_HXX
#include "view.hxx"
#endif
#include "starmath.hrc"
namespace binfilter {//STRIP009
/*N*/ TYPEINIT1( SmModuleDummy, SfxModule );
/*N*/ TYPEINIT1( SmModule, SmModuleDummy );

#define SmModule
#include "smslots.hxx"
} //namespace binfilter
namespace binfilter {

/////////////////////////////////////////////////////////////////

/*N*/ SmLocalizedSymbolData::SmLocalizedSymbolData() :
/*N*/     Resource( SmResId(RID_LOCALIZED_NAMES) ),
/*N*/   aUiSymbolNamesAry       ( SmResId(RID_UI_SYMBOL_NAMES) ),
/*N*/     aExportSymbolNamesAry   ( SmResId(RID_EXPORT_SYMBOL_NAMES) ),
/*N*/     aUiSymbolSetNamesAry    ( SmResId(RID_UI_SYMBOLSET_NAMES) ),
/*N*/     aExportSymbolSetNamesAry( SmResId(RID_EXPORT_SYMBOLSET_NAMES) ),
/*N*/     p50NamesAry             ( 0 ),
/*N*/     p60NamesAry             ( 0 ),
/*N*/     n50NamesLang            ( LANGUAGE_NONE ),
/*N*/     n60NamesLang            ( LANGUAGE_NONE )
/*N*/ {
/*N*/   FreeResource();
/*N*/ }


/*N*/ SmLocalizedSymbolData::~SmLocalizedSymbolData()
/*N*/ {
/*N*/     delete p50NamesAry;
/*N*/     delete p60NamesAry;
/*N*/ }


/*N*/ const String SmLocalizedSymbolData::GetUiSymbolName( const String &rExportName ) const
/*N*/ {
/*N*/   String aRes;
/*N*/
/*N*/     const SmLocalizedSymbolData &rData = SM_MOD1()->GetLocSymbolData();
/*N*/     const ResStringArray &rUiNames = rData.GetUiSymbolNamesArray();
/*N*/     const ResStringArray &rExportNames = rData.GetExportSymbolNamesArray();
/*N*/     USHORT nCount = rExportNames.Count();
/*N*/     for (USHORT i = 0;  i < nCount  &&  !aRes.Len();  ++i)
/*N*/   {
/*N*/         if (rExportName == rExportNames.GetString(i))
/*N*/       {
/*N*/             aRes = rUiNames.GetString(i);
/*N*/           break;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   return aRes;
/*N*/ }


/*N*/ const String SmLocalizedSymbolData::GetExportSymbolName( const String &rUiName ) const
/*N*/ {
/*N*/   String aRes;
/*N*/
/*N*/     const SmLocalizedSymbolData &rData = SM_MOD1()->GetLocSymbolData();
/*N*/     const ResStringArray &rUiNames = rData.GetUiSymbolNamesArray();
/*N*/     const ResStringArray &rExportNames = rData.GetExportSymbolNamesArray();
/*N*/   USHORT nCount = rUiNames.Count();
/*N*/     for (USHORT i = 0;  i < nCount  &&  !aRes.Len();  ++i)
/*N*/   {
/*N*/         if (rUiName == rUiNames.GetString(i))
/*N*/       {
/*N*/           aRes = rExportNames.GetString(i);
/*N*/           break;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   return aRes;
/*N*/ }


/*N*/ const String SmLocalizedSymbolData::GetUiSymbolSetName( const String &rExportName ) const
/*N*/ {
/*N*/   String aRes;
/*N*/
/*N*/     const SmLocalizedSymbolData &rData = SM_MOD1()->GetLocSymbolData();
/*N*/     const ResStringArray &rUiNames = rData.GetUiSymbolSetNamesArray();
/*N*/     const ResStringArray &rExportNames = rData.GetExportSymbolSetNamesArray();
/*N*/     USHORT nCount = rExportNames.Count();
/*N*/     for (USHORT i = 0;  i < nCount  &&  !aRes.Len();  ++i)
/*N*/   {
/*N*/         if (rExportName == rExportNames.GetString(i))
/*N*/       {
/*N*/             aRes = rUiNames.GetString(i);
/*N*/           break;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   return aRes;
/*N*/ }




/*N*/ const ResStringArray* SmLocalizedSymbolData::Get50NamesArray( LanguageType nLang )
/*N*/ {
/*N*/     if (nLang != n50NamesLang)
/*N*/     {
/*N*/         int nRID;
/*N*/         switch (nLang)
/*N*/         {
/*?*/             case LANGUAGE_FRENCH    : nRID = RID_FRENCH_50_NAMES;  break;
/*?*/             case LANGUAGE_ITALIAN   : nRID = RID_ITALIAN_50_NAMES;  break;
/*?*/             case LANGUAGE_SWEDISH   : nRID = RID_SWEDISH_50_NAMES;  break;
/*?*/             case LANGUAGE_SPANISH   : nRID = RID_SPANISH_50_NAMES;  break;
/*N*/             default                 : nRID = -1;  break;
/*N*/         }
/*N*/         delete p50NamesAry;
/*N*/         p50NamesAry = 0;
/*N*/         n50NamesLang = nLang;
/*N*/         if (-1 != nRID)
/*?*/             p50NamesAry = new SmNamesArray( n50NamesLang, nRID );
/*N*/     }
/*N*/
/*N*/     return p50NamesAry ? &p50NamesAry->GetNamesArray() : 0;
/*N*/ }


/*N*/ const ResStringArray* SmLocalizedSymbolData::Get60NamesArray( LanguageType nLang )
/*N*/ {
/*N*/     if (nLang != n60NamesLang)
/*N*/     {
/*N*/         int nRID;
/*N*/         switch (nLang)
/*N*/         {
/*?*/             case LANGUAGE_FRENCH    : nRID = RID_FRENCH_60_NAMES;  break;
/*?*/             case LANGUAGE_ITALIAN   : nRID = RID_ITALIAN_60_NAMES;  break;
/*?*/             case LANGUAGE_SWEDISH   : nRID = RID_SWEDISH_60_NAMES;  break;
/*?*/             case LANGUAGE_SPANISH   : nRID = RID_SPANISH_60_NAMES;  break;
/*N*/             default                 : nRID = -1;  break;
/*N*/         }
/*N*/         delete p60NamesAry;
/*N*/         p60NamesAry = 0;
/*N*/         n60NamesLang = nLang;
/*N*/         if (-1 != nRID)
/*?*/             p60NamesAry = new SmNamesArray( n60NamesLang, nRID );
/*N*/     }
/*N*/
/*N*/     return p60NamesAry ? &p60NamesAry->GetNamesArray() : 0;
/*N*/ }

/////////////////////////////////////////////////////////////////

/*N*/ SFX_IMPL_INTERFACE(SmModule, SfxModule, SmResId(RID_APPLICATION))
/*N*/ {
/*N*/   SFX_STATUSBAR_REGISTRATION(SmResId(RID_STATUSBAR));
/*N*/ }


/*N*/ SmModule::SmModule(SvFactory* pObjFact) :
/*N*/   SmModuleDummy(SFX_APP()->CreateResManager("bf_sm"), FALSE, pObjFact),   //STRIP005
/*N*/     pConfig( 0 ),
/*N*/     pColorConfig( 0 ),
/*N*/     pLocSymbolData( 0 ),
/*N*/     pRectCache( new SmRectCache ),
/*N*/     pSysLocale( 0 ),
/*N*/     pVirtualDev( 0 )
/*N*/ {
/*N*/   SetName( C2S("StarMath" ));
/*N*/ }


/*N*/ SmModule::~SmModule()
/*N*/ {
/*N*/   delete pConfig;
/*N*/     delete pColorConfig;
/*N*/     delete pLocSymbolData;
/*N*/   delete pRectCache;
/*N*/   delete pSysLocale;
/*N*/     delete pVirtualDev;
/*N*/ }

/*N*/ void SmModule::_CreateSysLocale() const
/*N*/ {
/*N*/   SmModule* pThis = (SmModule*)this;
/*N*/   pThis->pSysLocale = new SvtSysLocale;
/*N*/ }

/*N*/ void SmModule::_CreateVirtualDev() const
/*N*/ {
/*N*/   SmModule* pThis = (SmModule*)this;
/*N*/     pThis->pVirtualDev = new VirtualDevice;
/*N*/ }

/*N*/ void SmModule::ApplyColorConfigValues( const svtools::ColorConfig &rColorCfg )
/*N*/ {
/*N*/     //invalidate all graphic and edit windows
/*N*/     const TypeId aSmViewTypeId = TYPE(SmViewShell);
/*N*/     SfxViewShell* pViewShell = SfxViewShell::GetFirst();
/*N*/     while (pViewShell)
/*N*/     {
/*N*/         if ((pViewShell->IsA(aSmViewTypeId)))
/*N*/         {
/*N*/             SmViewShell *pSmView = (SmViewShell *) pViewShell;
/*N*/             pSmView->GetGraphicWindow().ApplyColorConfigValues( rColorCfg );
/*N*/             SmEditWindow *pEditWin = pSmView->GetEditWindow();
/*N*/             if (pEditWin)
/*?*/                 {DBG_BF_ASSERT(0, "STRIP"); }//STRIP001 pEditWin->ApplyColorConfigValues( rColorCfg );
/*N*/         }
/*N*/         pViewShell = SfxViewShell::GetNext( *pViewShell );
/*N*/     }
/*N*/ }

/*N*/ svtools::ColorConfig & SmModule::GetColorConfig()
/*N*/ {
/*N*/     if(!pColorConfig)
/*N*/     {
/*N*/         pColorConfig = new svtools::ColorConfig;
/*N*/         ApplyColorConfigValues( *pColorConfig );
/*N*/         StartListening( *pColorConfig );
/*N*/     }
/*N*/     return *pColorConfig;
/*N*/ }

/*N*/ void SmModule::Notify( SfxBroadcaster &rBC, const SfxHint &rHint )
/*N*/ {
/*N*/     if (rHint.ISA(SfxSimpleHint))
/*N*/     {
/*N*/         ULONG nHintId = ((SfxSimpleHint&)rHint).GetId();
/*N*/         if (SFX_HINT_COLORS_CHANGED == nHintId)
/*N*/             ApplyColorConfigValues(*pColorConfig);
/*N*/     }
/*N*/ }

/*N*/ SmConfig * SmModule::GetConfig()
/*N*/ {
/*N*/     if(!pConfig)
/*N*/         pConfig = new SmConfig;
/*N*/     return pConfig;
/*N*/ }

/*N*/ SmLocalizedSymbolData & SmModule::GetLocSymbolData() const
/*N*/ {
/*N*/     if (!pLocSymbolData)
/*N*/         ((SmModule *) this)->pLocSymbolData = new SmLocalizedSymbolData;
/*N*/     return *pLocSymbolData;
/*N*/ }

/*N*/ void SmModule::GetState(SfxItemSet &rSet)
/*N*/ {
/*N*/   SfxWhichIter aIter(rSet);
/*N*/
/*N*/   for (USHORT nWh = aIter.FirstWhich(); 0 != nWh; nWh = aIter.NextWhich())
/*N*/       switch (nWh)
/*N*/       {
/*N*/           case SID_CONFIGEVENT :
/*N*/               rSet.DisableItem(SID_CONFIGEVENT);
/*N*/               break;
/*N*/       }
/*N*/ }

/*N*/ void SmModule::FillStatusBar(StatusBar &rBar)
/*N*/ {
/*N*/   rBar.InsertItem(SID_TEXTSTATUS, 300, SIB_LEFT | SIB_IN);
/*N*/   rBar.InsertItem(SID_ATTR_ZOOM, rBar.GetTextWidth(C2S(" 100% ")));
/*N*/   rBar.InsertItem(SID_MODIFYSTATUS, rBar.GetTextWidth(C2S(" * ")));
/*N*/ }

/*N*/ SfxModule *SmModuleDummy::Load()
/*N*/ {
/*N*/   return 0;
/*N*/ }

}
