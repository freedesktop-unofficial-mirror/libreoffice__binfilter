/*************************************************************************
 *
 *  $RCSfile: smmod.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 08:27:17 $
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

#ifndef _SMMOD_HXX
#define _SMMOD_HXX

#ifndef _SV_RESARY_HXX
#include <tools/resary.hxx>
#endif
#ifndef _SFXLSTNER_HXX
#include <svtools/lstner.hxx>
#endif
#ifndef INCLUDED_SVTOOLS_COLORCFG_HXX
#include <svtools/colorcfg.hxx>
#endif

#ifndef _SMDLL_HXX
#define _SM_DLL             // fuer SD_MOD()
#include <bf_starmath/smdll.hxx>        // fuer SdModuleDummy
#endif
#ifndef _STARMATH_HRC
#include "starmath.hrc"
#endif
class SvFactory;
class SvtSysLocale;
class VirtualDevice;

namespace binfilter {

class SvxErrorHandler;


class SmConfig;
class SmModule;

/*************************************************************************
|*
|* This subclass of <SfxModule> (which is a subclass of <SfxShell>) is
|* linked to the DLL. One instance of this class exists while the DLL is
|* loaded.
|*
|* SdModule is like to be compared with the <SfxApplication>-subclass.
|*
|* Remember: Don`t export this class! It uses DLL-internal symbols.
|*
\************************************************************************/

class SmRectCache;

/////////////////////////////////////////////////////////////////

/*N*/ class SmNamesArray : public Resource
/*N*/ {
/*N*/     ResStringArray      aNamesAry;
/*N*/     LanguageType        nLanguage;
/*N*/
/*N*/ public:
/*N*/     SmNamesArray( LanguageType nLang, int nRID ) :
/*N*/         Resource( SmResId(RID_LOCALIZED_NAMES) ),
/*N*/         nLanguage   (nLang),
/*N*/         aNamesAry   (ResId(nRID))
/*N*/     {
/*N*/         FreeResource();
/*N*/     }
/*N*/
/*N*/     LanguageType            GetLanguage() const     { return nLanguage; }
/*N*/     const ResStringArray&   GetNamesArray() const   { return aNamesAry; }
/*N*/ };

/////////////////////////////////////////////////////////////////

class SmLocalizedSymbolData : public Resource
{
    ResStringArray      aUiSymbolNamesAry;
    ResStringArray      aExportSymbolNamesAry;
    ResStringArray      aUiSymbolSetNamesAry;
    ResStringArray      aExportSymbolSetNamesAry;
    SmNamesArray       *p50NamesAry;
    SmNamesArray       *p60NamesAry;
    LanguageType        n50NamesLang;
    LanguageType        n60NamesLang;

public:
    SmLocalizedSymbolData();
    ~SmLocalizedSymbolData();

    const ResStringArray& GetUiSymbolNamesArray() const     { return aUiSymbolNamesAry; }
    const ResStringArray& GetExportSymbolNamesArray() const { return aExportSymbolNamesAry; }
    const String          GetUiSymbolName( const String &rExportName ) const;
    const String          GetExportSymbolName( const String &rUiName ) const;

    const ResStringArray& GetUiSymbolSetNamesArray() const     { return aUiSymbolSetNamesAry; }
    const ResStringArray& GetExportSymbolSetNamesArray() const { return aExportSymbolSetNamesAry; }
    const String          GetUiSymbolSetName( const String &rExportName ) const;
//STRIP001     const String          GetExportSymbolSetName( const String &rUiName ) const;

    const ResStringArray* Get50NamesArray( LanguageType nLang );
    const ResStringArray* Get60NamesArray( LanguageType nLang );
};

/////////////////////////////////////////////////////////////////

class SmModule : public SmModuleDummy, public SfxListener
{
    ::svtools::ColorConfig        *pColorConfig;
    SmConfig                *pConfig;
    SmLocalizedSymbolData   *pLocSymbolData;
    SmRectCache             *pRectCache;
    SvtSysLocale            *pSysLocale;
    VirtualDevice           *pVirtualDev;

    virtual void FillStatusBar(StatusBar &rBar);
    void _CreateSysLocale() const;
    void _CreateVirtualDev() const;

    void ApplyColorConfigValues( const svtools::ColorConfig &rColorCfg );

public:
    TYPEINFO();
    SFX_DECL_INTERFACE(SFX_INTERFACE_SMA_START + 0);

    SmModule(SvFactory* pObjFact);
    virtual ~SmModule();

//STRIP001  virtual SfxModule * Load();
//STRIP001  virtual void        Free();

    // SfxListener
    virtual void        Notify( SfxBroadcaster& rBC, const SfxHint& rHint );

    ::svtools::ColorConfig &  GetColorConfig();

    SmConfig *          GetConfig();
    SmRectCache *       GetRectCache()     { return pRectCache; }

    SmLocalizedSymbolData &   GetLocSymbolData() const;

    void GetState(SfxItemSet&);

    const SvtSysLocale& GetSysLocale() const
    {
        if( !pSysLocale )
            _CreateSysLocale();
        return *pSysLocale;
    }

    VirtualDevice &     GetDefaultVirtualDev()
    {
        if (!pVirtualDev)
            _CreateVirtualDev();
        return *pVirtualDev;
    }

    //virtuelle Methoden fuer den Optionendialog
//STRIP001  virtual SfxItemSet*  CreateItemSet( USHORT nId );
//STRIP001  virtual void         ApplyItemSet( USHORT nId, const SfxItemSet& rSet );
//STRIP001  virtual SfxTabPage*  CreateTabPage( USHORT nId, Window* pParent, const SfxItemSet& rSet );
};

#define SM_MOD1() ( *(SmModule**) GetAppData(BF_SHL_SM) )

} //namespace binfilter
#endif                                 // _SDMOD_HXX

