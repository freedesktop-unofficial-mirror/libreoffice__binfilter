/*************************************************************************
 *
 *  $RCSfile: sfx2_appbas.cxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:23:14 $
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

#ifndef _COM_SUN_STAR_FRAME_XDESKTOP_HPP_
#include <com/sun/star/frame/XDesktop.hpp>
#endif
#ifndef _COM_SUN_STAR_SCRIPT_XLIBRARYCONTAINER_HPP_
#include <com/sun/star/script/XLibraryContainer.hpp>
#endif
#ifndef _UNOTOOLS_PROCESSFACTORY_HXX
#include <comphelper/processfactory.hxx>
#endif
#ifndef _COM_SUN_STAR_UNO_REFERENCE_H_
#include <com/sun/star/uno/Reference.h>
#endif

#ifndef _BASRDLL_HXX //autogen
#include <basic/basrdll.hxx>
#endif
#ifndef _URLOBJ_HXX
#include <tools/urlobj.hxx>
#endif
#ifndef _SFXMACITEM_HXX //autogen
#include <svtools/macitem.hxx>
#endif
#ifndef __SBX_SBX_FACTORY_HXX //autogen
#include <svtools/sbxfac.hxx>
#endif
#ifndef _SBXCLASS_HXX //autogen
#include <svtools/sbx.hxx>
#endif
#ifndef _SV_GRADIENT_HXX
#include <vcl/gradient.hxx>
#endif
#ifndef _SFXRECTITEM_HXX //autogen
#include <svtools/rectitem.hxx>
#endif
#ifndef _SFXINTITEM_HXX //autogen
#include <svtools/intitem.hxx>
#endif
#ifndef _SFXENUMITEM_HXX //autogen
#include <svtools/eitem.hxx>
#endif
#ifndef _SB_SBMOD_HXX //autogen
#include <basic/sbmod.hxx>
#endif
#ifndef _SFX_WHITER_HXX //autogen
#include <svtools/whiter.hxx>
#endif
#ifndef _SB_SBMETH_HXX //autogen
#include <basic/sbmeth.hxx>
#endif
#ifndef _SB_SBSTAR_HXX //autogen
#include <basic/sbstar.hxx>
#endif
#ifndef _SVSTOR_HXX //autogen
#include <so3/svstor.hxx>
#endif
#ifndef _SV_WRKWIN_HXX
#include <vcl/wrkwin.hxx>
#endif
#ifndef _MSGBOX_HXX //autogen
#include <vcl/msgbox.hxx>
#endif
#ifndef _REGCODE_HXX
#endif
#ifndef _SB_SBUNO_HXX
#include <basic/sbuno.hxx>
#endif
#ifndef _SFXECODE_HXX
#include <svtools/sfxecode.hxx>
#endif
#ifndef _EHDL_HXX
#include <svtools/ehdl.hxx>
#endif

#include <svtools/undoopt.hxx>
#include <svtools/pathoptions.hxx>
#include <svtools/useroptions.hxx>
#include <unotools/bootstrap.hxx>

#pragma hdrstop

#include "appuno.hxx"
#include "module.hxx"
#include "arrdecl.hxx"
#include "app.hxx"
#include "sfxtypes.hxx"
#include "sfxresid.hxx"
#include "msg.hxx"
#include "msgpool.hxx"
#include "progress.hxx"
#include "objsh.hxx"
#include "objitem.hxx"
#include "viewfrm.hxx"
#include "viewsh.hxx"
#include "dispatch.hxx"
#include "tplpitem.hxx"
#include "minfitem.hxx"
#include "app.hrc"
#include "evntconf.hxx"
#include "macrconf.hxx"
#include "request.hxx"
#include "docinf.hxx"
#include "dinfdlg.hxx"
#include "appdata.hxx"
#include "appbas.hxx"
#include "sfxhelp.hxx"
#include "stbmgr.hxx"
#include "appimp.hxx"
#include "basmgr.hxx"
#include "dlgcont.hxx"
#include "scriptcont.hxx"
#include "helper.hxx"

#define ITEMID_SEARCH SID_SEARCH_ITEM

#include "srchitem.hxx"
#ifndef _VOS_SOCKET_HXX_ //autogen
#include <vos/socket.hxx>
#endif

#define SFX_TYPEMAP
#define Selection
#include "sfxslots.hxx"

#ifndef _LEGACYBINFILTERMGR_HXX
#include <legacysmgr/legacy_binfilters_smgr.hxx>    //STRIP002
#endif

using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::frame;
using namespace ::com::sun::star::script;

// #ifndef STR_VERSION_ID
// #define STR_VERSION_ID 1
// #endif
// #ifndef STR_VERSION_TYPE
// #define STR_VERSION_TYPE 1
// #endif

//=========================================================================
/*ASDBG
const SfxConstant __FAR_DATA aConstants[] =
{
    SFX_USHORT_CONSTANT( "AlignBottom",         ALIGN_BOTTOM ),
    SFX_USHORT_CONSTANT( "AlignTop",            ALIGN_TOP ),
    SFX_USHORT_CONSTANT( "CharSetANSI",         CHARSET_ANSI ),
    SFX_USHORT_CONSTANT( "CharSetDontKnow",     CHARSET_DONTKNOW ),
    SFX_USHORT_CONSTANT( "CharSetIBMPC437",     CHARSET_IBMPC_437 ),
    SFX_USHORT_CONSTANT( "CharSetIBMPC850",     CHARSET_IBMPC_850 ),
    SFX_USHORT_CONSTANT( "CharSetIBMPC860",     CHARSET_IBMPC_860 ),
    SFX_USHORT_CONSTANT( "CharSetIBMPC861",     CHARSET_IBMPC_861 ),
    SFX_USHORT_CONSTANT( "CharSetIBMPC863",     CHARSET_IBMPC_863 ),
    SFX_USHORT_CONSTANT( "CharSetIBMPC865",     CHARSET_IBMPC_865 ),
    SFX_USHORT_CONSTANT( "CharSetIBMPC",        CHARSET_IBMPC ),
    SFX_USHORT_CONSTANT( "CharSetMac",          CHARSET_MAC ),
    SFX_USHORT_CONSTANT( "CharSetSymbol",       CHARSET_SYMBOL ),
    SFX_USHORT_CONSTANT( "CharSetSystem",       RTL_TEXTENCODING_UTF8 ),
    SFX_USHORT_CONSTANT( "FamilyDecorative",    FAMILY_DECORATIVE ),
    SFX_USHORT_CONSTANT( "FamilyDontknow",      FAMILY_DONTKNOW ),
    SFX_USHORT_CONSTANT( "FamilyModern",        FAMILY_MODERN ),
    SFX_USHORT_CONSTANT( "FamilyRoman",         FAMILY_ROMAN ),
    SFX_USHORT_CONSTANT( "FamilyScript",        FAMILY_SCRIPT ),
    SFX_USHORT_CONSTANT( "FamilySwiss",         FAMILY_SWISS ),
    SFX_USHORT_CONSTANT( "FamilySystem",        FAMILY_SYSTEM ),
    SFX_USHORT_CONSTANT( "GradientAxial",       GRADIENT_AXIAL ),
    SFX_USHORT_CONSTANT( "GradientElliptical",  GRADIENT_ELLIPTICAL ),
    SFX_USHORT_CONSTANT( "GradientLinear",      GRADIENT_LINEAR ),
    SFX_USHORT_CONSTANT( "GradientRadial",      GRADIENT_RADIAL ),
    SFX_USHORT_CONSTANT( "GradientRect",        GRADIENT_RECT ),
    SFX_USHORT_CONSTANT( "GradientSquare",      GRADIENT_SQUARE ),
    SFX_USHORT_CONSTANT( "ItalicNone",          ITALIC_NONE ),
    SFX_USHORT_CONSTANT( "ItalicOblique",       ITALIC_OBLIQUE ),
    SFX_USHORT_CONSTANT( "StrikeThroughDouble", STRIKEOUT_DOUBLE ),
    SFX_USHORT_CONSTANT( "StrikeThroughNone",   STRIKEOUT_NONE ),
    SFX_USHORT_CONSTANT( "StrikeThroughSingle", STRIKEOUT_SINGLE ),
    SFX_USHORT_CONSTANT( "UnderlineDotted",     UNDERLINE_DOTTED ),
    SFX_USHORT_CONSTANT( "UnderlineDouble",     UNDERLINE_DOUBLE ),
    SFX_USHORT_CONSTANT( "UnderlineNone",       UNDERLINE_NONE ),
    SFX_USHORT_CONSTANT( "UnderlineSingle",     UNDERLINE_SINGLE ),
    SFX_USHORT_CONSTANT( "UnitFoot",            FUNIT_FOOT ),
    SFX_USHORT_CONSTANT( "UnitInch",            FUNIT_INCH ),
    SFX_USHORT_CONSTANT( "UnitMile",            FUNIT_MILE ),
    SFX_USHORT_CONSTANT( "UnitPercent",         FUNIT_PERCENT ),
    SFX_USHORT_CONSTANT( "UnitPoint",           FUNIT_POINT ),
    SFX_USHORT_CONSTANT( "UnitTwip",            FUNIT_TWIP ),
    SFX_USHORT_CONSTANT( "Unit_cm",             FUNIT_CM ),
    SFX_USHORT_CONSTANT( "Unit_m",              FUNIT_M ),
    SFX_USHORT_CONSTANT( "Unit_mm",             FUNIT_MM ),
    SFX_USHORT_CONSTANT( "WeightBlack",         WEIGHT_BLACK ),
    SFX_USHORT_CONSTANT( "WeightBold",          WEIGHT_BOLD ),
    SFX_USHORT_CONSTANT( "WeightDontKnow",      WEIGHT_DONTKNOW ),
    SFX_USHORT_CONSTANT( "WeightLight",         WEIGHT_LIGHT ),
    SFX_USHORT_CONSTANT( "WeightMedium",        WEIGHT_MEDIUM ),
    SFX_USHORT_CONSTANT( "WeightNormal",        WEIGHT_NORMAL ),
    SFX_USHORT_CONSTANT( "WeightSemibold",      WEIGHT_SEMIBOLD ),
    SFX_USHORT_CONSTANT( "WeightSemilight",     WEIGHT_SEMILIGHT ),
    SFX_USHORT_CONSTANT( "WeightThin",          WEIGHT_THIN ),
    SFX_USHORT_CONSTANT( "WeightUltrabold",     WEIGHT_ULTRABOLD ),
    SFX_USHORT_CONSTANT( "WeightUltralight",    WEIGHT_ULTRALIGHT )
};
*/
//========================================================================

/*N*/ StarBASIC* SfxApplication::GetBasic_Impl() const
/*N*/ {
/*N*/     return pImp->pBasicMgr ? pImp->pBasicMgr->GetLib(0) : NULL;
/*N*/ }

//------------------------------------------------------------------------
//STRIP001 String lcl_GetVersionString(ResMgr* pImpResMgr)
//STRIP001 {
//STRIP001  ::rtl::OUString aDefault;
//STRIP001  String aVersion( utl::Bootstrap::getBuildIdData( aDefault ));
//STRIP001
//STRIP001  if ( aVersion.Len() == 0 )
//STRIP001      DBG_ERROR( "No BUILDID in bootstrap file found" );
//STRIP001
//STRIP001  aVersion.Erase( 0, aVersion.Search( ':' ) + 1 );
//STRIP001  aVersion.Erase( aVersion.Search( ')' ) );
//STRIP001  return aVersion;
//STRIP001 }

//------------------------------------------------------------------------
/*(mba)
SbxObject* SfxSbxObjectFactory_Impl::CreateObject( const String &rType )
{
    if ( COMPARE_EQUAL == rType.CompareIgnoreCaseToAscii( "DocumentInfo" ) )
        return new SfxDocumentInfoObject_Impl;
    if ( COMPARE_EQUAL == rType.CompareIgnoreCaseToAscii( "Progress" ) )
        return SfxProgress::CreateObject_Impl();
    return 0;
}*/

//=========================================================================
/*
SfxSelectionObject::SfxSelectionObject
(
    SfxViewFrame *pFrame               // ein Frame als Parent
)

//  [Beschreibung]

//  interner Ctor f"ur Default-Behandlung


:   SfxShellSubObject( pFrame, SFX_TYPELIB_INFO(Selection), "Selection" ),
   _pFrame( pFrame )
{
    SetFlag( SBX_EXTSEARCH | SBX_DONTSTORE ); // unsichtbar
}

//-------------------------------------------------------------------------

SfxSelectionObject::SfxSelectionObject
(
    SfxViewFrame *pFrame,               // ein Frame als Parent
    const String& rClassName,
    const SfxTypeLibImpl &rTypeLibInfo
)

:   SfxShellSubObject( pFrame, rClassName, rTypeLibInfo, "Selection" ),
   _pFrame( pFrame )
{
    SetFlag( SBX_EXTSEARCH | SBX_DONTSTORE ); // unsichtbar
}

//-------------------------------------------------------------------------

SvDispatch* SfxSelectionObject::GetAggObject( sal_uInt16 nIdx )

{
    // selbst?
    if ( 0 == nIdx )
        return SfxShellSubObject::GetAggObject( 0 );

    // die oberhalb der ::com::sun::star::sdbcx::View auf dem Dispatcher befindlichen Shells indizieren
    SfxDispatcher *pDispat = _pFrame->GetDispatcher();
    SfxShell *pSh = pDispat->GetShell( nIdx-1 );
    if ( !pSh || pSh->ISA(SfxObjectShell) )
        return 0;
    return (SvDispatch*) pSh->GetSbxObject();
}

//-------------------------------------------------------------------------

SbxVariable* SfxSelectionObject::Find
(
    const String&   rName,
    SbxClassType    t
)
{
    // einige Member selbst bedienen
    String aName( rName.ToLowerAscii() );
    if ( aName == "name" || aName == "classname" )
        return SfxShellSubObject::Find( rName, t );

    // nur die oberhalb der ::com::sun::star::sdbcx::View auf dem Dispatcher liegenden Shells durchsuchen
    SfxDispatcher *pDispat = _pFrame->GetDispatcher();
    pDispat->Flush();
    SfxShell *pSh;
    for ( sal_uInt16 n = 0;
          ( pSh = pDispat->GetShell( n ) ) && !pSh->ISA(SfxViewFrame);
          ++n )
    {
        SbxObject *pObj = pSh->GetSbxObject();
        if ( pObj )
        {
            if ( ( t == SbxCLASS_DONTCARE || t == SbxCLASS_OBJECT ) &&
                 pObj->GetName() == rName )
                return pObj;
            else
            {
                SbxVariable *pRes = pObj->Find( rName, t );
                if ( pRes )
                    return pRes;
            }
        }
    }

    return 0;
}

//-------------------------------------------------------------------------

SbxVariable* SfxSelectionObject::FindUserData
(
    sal_uInt32 nId
)
{
    // nur die oberhalb der ::com::sun::star::sdbcx::View auf dem Dispatcher liegenden Shells durchsuchen
    SfxDispatcher *pDispat = _pFrame->GetDispatcher();
    SfxShell *pSh;
    for ( sal_uInt16 n = 0;
          ( pSh = pDispat->GetShell( n ) ) && !pSh->ISA(SfxViewFrame);
          ++n )
    {
        SbxObject *pObj = pSh->GetSbxObject();
        if ( pObj )
        {
            SbxVariable *pRes = pObj->FindUserData( nId );
            if ( pRes )
                return pRes;
        }
    }

    return 0;
}

//=========================================================================

class SfxConstants_Impl: public SbxObject
{
    const char*         _pPrefix;
    const SfxConstant*  _pConsts;
    sal_uInt16              _nCount;

public:
                        SfxConstants_Impl( const char *pPrefix,
                                           const SfxConstant *pConsts,
                                           sal_uInt16 n );
    SbxVariable*        Find( const String& rName, SbxClassType t );
};

//-------------------------------------------------------------------------

SfxConstants_Impl::SfxConstants_Impl
(
    const char*         pPrefix,
    const SfxConstant*  pConsts,
    sal_uInt16              nCount
)
:   SbxObject( "Constants" ),
    _pPrefix( pPrefix ),
    _pConsts( pConsts ),
    _nCount( nCount )
{
    SetFlag( SBX_EXTSEARCH | SBX_DONTSTORE ); // unsichtbar
    SetName( String( (long) this ) ); // random
}

//-------------------------------------------------------------------------

SbxVariable* SfxConstants_Impl::Find
(
    const String&   rName,
    SbxClassType    t
)
{
    // stimmt Typ und Prefix?
    String aPrefix;
    if ( _pPrefix )
        aPrefix += _pPrefix;
    if ( ( SbxCLASS_DONTCARE != t && SbxCLASS_PROPERTY != t ) ||
         ( aPrefix.Len() && aPrefix.Len() != rName.Match( _pPrefix ) ) )
        return 0;

    // schon drin?
    SbxVariable* pRes = SbxObject::Find( rName, t );
    if( pRes )
        return pRes;

    // sonst suchen
    String aSearched( rName );
    aSearched.ToLowerAscii();
    for ( sal_uInt16 n = 0; n < _nCount; ++n )
    {
        // gefunden?
        const SfxConstant &rConst = _pConsts[n];
        String aName( aPrefix );
        aName += rConst.pName;
        if ( aSearched == aName.ToLowerAscii() )
        {
            // on-demand erzeugen
            SbxVariable *pVar = Make( aName, SbxCLASS_PROPERTY, rConst.eType );
            switch ( rConst.eType )
            {
                case SbxUSHORT:
                    pVar->PutUShort( (sal_uInt16)(int) rConst.pData );
                    break;

                case SbxCHAR:
                    pVar->PutChar( (char)(int) rConst.pData );
                    break;

                case SbxBYTE:
                    pVar->PutByte( (sal_Int8)(int) rConst.pData );
                    break;

                case SbxBOOL:
                    pVar->PutBool( (sal_Bool)(int) rConst.pData );
                    break;

                case SbxINTEGER:
                    pVar->PutInteger( (short)(int) rConst.pData );
                    break;

                case SbxLONG:
                    pVar->PutLong( (long) rConst.pData );
                    break;

                case SbxUINT:
                    pVar->PutUShort( (sal_uInt16)(int) rConst.pData );
                    break;

                case SbxULONG:
                    pVar->PutULong( (sal_uInt32) rConst.pData );
                    break;

                case SbxLPSTR:
                    pVar->PutString( (char*) rConst.pData );
                    break;

                default:
                    DBG_ERROR( "type of constant not supported" );
            }

            pVar->ResetFlag( SBX_WRITE );
            pVar->SetFlag( SBX_CONST );
            pVar->SetFlag( SBX_FIXED );
            return pVar;
        }
    }

    return 0;
}
*/
//=========================================================================
/*N*/ sal_uInt16 SfxApplication::SaveBasicManager() const
/*N*/ {
    /* AB, 19.4.2001: No sbl files stored any more -> new library containers
    // MT: #47347# AppBasicDir ist jetzt ein PATH!
    // Ncht den vom BasicManager, falls inzwischen der Pfad geaendert wurde !?
    // So wird natuerlich auch das erste Dir genommen, wenn der BasicManager
    // vorher im zweiten gefunden wurde...
    String aBasicPath( SvtPathOptions().GetBasicPath() );
    INetURLObject aAppBasicObj( aBasicPath.GetToken(1) );
    aAppBasicObj.insertName( Application::GetAppName() );
    aAppBasicObj.setExtension( DEFINE_CONST_UNICODE( "sbl" ) );
    String aAppBasicPath( aAppBasicObj.GetMainURL( INetURLObject::NO_DECODE ) );
    SvStorageRef aStor = new SvStorage( aAppBasicPath );
    if ( aStor->GetError() == 0 )
    {
        String aBaseURL = INetURLObject::GetBaseURL();
        INetURLObject::SetBaseURL( aAppBasicObj.GetMainURL( INetURLObject::NO_DECODE ) );
        pImp->pBasicMgr->Store( *aStor );
        INetURLObject::SetBaseURL( aBaseURL );
    }
    if ( aStor->GetError() != 0 )
    {
        ErrorBox aBox(GetTopWindow(), SfxResId(MSG_ERR_WRITE_SBL));
        String aMsg( SearchAndReplace( aBox.GetMessText(), 0x0040, aAppBasicPath ) ); // 40h = '@'
        aBox.SetMessText( aMsg );
        aBox.Execute();
    }

    return (sal_uInt16)aStor->GetError();
    */
/*N*/
/*N*/   return 0;
/*N*/ }

//--------------------------------------------------------------------
/*N*/ sal_uInt16 SfxApplication::SaveDialogContainer() const
/*N*/ {
/*N*/   // Save Dialog Container
/*N*/   sal_Bool bComplete = sal_False;
/*N*/   if( pImp->pDialogLibContainer )
/*N*/       pImp->pDialogLibContainer->storeLibraries( bComplete );
/*N*/   return 0;
/*N*/ }

//--------------------------------------------------------------------
/*N*/ sal_uInt16 SfxApplication::SaveBasicContainer() const
/*N*/ {
/*N*/   // Save Dialog Container
/*N*/   sal_Bool bComplete = sal_False;
/*N*/   if( pImp->pBasicLibContainer )
/*N*/       pImp->pBasicLibContainer->storeLibraries( bComplete );
/*N*/   return 0;
/*N*/ }

//--------------------------------------------------------------------

//STRIP001 void SfxApplication::RegisterBasicConstants
//STRIP001 (
//STRIP001  const char*        pPrefix, // Prefix vor Konstanten-Namen
//STRIP001  const SfxConstant* pConsts, // Array von <SfxConstant> Instanzen
//STRIP001  sal_uInt16 nCount               // Anahl der Kontanten in pConsts
//STRIP001 )
//STRIP001
//STRIP001 /*   [Beschreibung]
//STRIP001
//STRIP001  Diese Methode meldet Konstanten beim BASIC an. Sie sollte on-demand
//STRIP001  (in GetSbxObject() der Applikation) gerufen werden. Das Array mu\s
//STRIP001  alphabetisch nach den Namen sortiert sein!
//STRIP001
//STRIP001  Durch den Prefix kann Speicher gespart und das Suchen beschleunigt
//STRIP001  werden. Im StarOffice soll der Prefix "so" verwendet werden.
//STRIP001
//STRIP001
//STRIP001  [Beispiel]
//STRIP001
//STRIP001  const SfxConstant __FAR_DATA aConstants[] =
//STRIP001  {
//STRIP001      SFX_BOOL_CONSTANT( "False", sal_False ),
//STRIP001      SFX_BOOL_CONSTANT( "True",  sal_True ),
//STRIP001  };
//STRIP001
//STRIP001  ...
//STRIP001  SFX_APP()->RegisterBasicConstants( 0, aConstants, 2 );
//STRIP001  ...
//STRIP001
//STRIP001 */
//STRIP001
//STRIP001 {
//STRIP001 //   DBG_ASSERT( pImp->pBasicMgr, "no basic available" );
//STRIP001
//STRIP001 //   pImp->pBasicMgr->GetLib(0)->Insert(
//STRIP001 //               new SfxConstants_Impl( pPrefix, pConsts, nCount ) );
//STRIP001 }

//--------------------------------------------------------------------

//STRIP001 SbxVariable* MakeVariable( StarBASIC *pBas, SbxObject *pObject,
//STRIP001         const char *pName, sal_uInt32 nSID, SbxDataType eType, SbxClassType eClassType )
//STRIP001 {
//STRIP001  SbxVariable *pVar = pBas->Make( String::CreateFromAscii(pName), eClassType, eType ); //SbxCLASS_PROPERTY
//STRIP001  pVar->SetUserData( nSID );
//STRIP001  pVar->SetFlag( SBX_DONTSTORE );
//STRIP001  pObject->StartListening( pVar->GetBroadcaster() );
//STRIP001  return pVar;
//STRIP001 }

//--------------------------------------------------------------------

/*N*/ BasicManager* SfxApplication::GetBasicManager()
/*N*/ {
/*N*/ //    DBG_ASSERT( pAppData_Impl->nBasicCallLevel != 0,
/*N*/ //                "unnecessary call to GetBasicManager() - inefficient!" );
/*N*/   if ( pAppData_Impl->nBasicCallLevel == 0 )
/*N*/       // sicherheitshalber
/*N*/       EnterBasicCall();
/*N*/
/*N*/   if ( !pImp->pBasicMgr )
/*N*/   {
/*N*/       // Directory bestimmen
/*N*/       SvtPathOptions aPathCFG;
/*N*/       String aAppBasicDir( aPathCFG.GetBasicPath() );
/*N*/       if ( !aAppBasicDir.Len() )
/*?*/             aPathCFG.SetBasicPath( String::CreateFromAscii("$(prog)") );
/*N*/
/*N*/       // #58293# soffice.new nur im ::com::sun::star::sdbcx::User-Dir suchen => erstes Verzeichnis
/*N*/       String aAppFirstBasicDir = aAppBasicDir.GetToken(1);
/*N*/
/*N*/       // Basic erzeugen und laden
/*N*/       // MT: #47347# AppBasicDir ist jetzt ein PATH!
/*N*/         INetURLObject aAppBasic( SvtPathOptions().SubstituteVariable( String::CreateFromAscii("$(progurl)") ) );
/*N*/         aAppBasic.insertName( Application::GetAppName() );
/*N*/
/*N*/       BasicManager* pBasicManager = new BasicManager( new StarBASIC, &aAppBasicDir );
/*N*/         pImp->pBasicMgr = pBasicManager;
/*N*/
/*N*/       // Als Destination das erste Dir im Pfad:
/*N*/       String aFileName( aAppBasic.getName() );
/*N*/         aAppBasic = INetURLObject( aAppBasicDir.GetToken(1) );
/*N*/         DBG_ASSERT( aAppBasic.GetProtocol() != INET_PROT_NOT_VALID, "Invalid URL!" );
/*N*/       aAppBasic.insertName( aFileName );
/*N*/       pImp->pBasicMgr->SetStorageName( aAppBasic.PathToFileName() );
/*N*/
/*N*/       // globale Variablen
/*N*/       StarBASIC *pBas = pImp->pBasicMgr->GetLib(0);
/*N*/       sal_Bool bBasicWasModified = pBas->IsModified();
/*N*/
/*N*/         Reference< ::com::sun::star::lang::XMultiServiceFactory > xSMgr = ::legacy_binfilters::getLegacyProcessServiceFactory();
/*N*/         Any aDesktop;
/*N*/         Reference< XDesktop > xDesktop( xSMgr->createInstance(::rtl::OUString::createFromAscii("com.sun.star.frame.Desktop")), UNO_QUERY );
/*N*/       aDesktop <<= xDesktop ;
/*N*/       SbxObjectRef xUnoObj = GetSbUnoObject( DEFINE_CONST_UNICODE("StarDesktop"), aDesktop );
/*N*/       xUnoObj->SetFlag( SBX_DONTSTORE );
/*N*/       pBas->Insert( xUnoObj );
/*N*/       //pBas->setRoot( xDesktop );
/*N*/
/*N*/       // Basic container
/*N*/       SfxScriptLibraryContainer* pBasicCont = new SfxScriptLibraryContainer
/*N*/           ( DEFINE_CONST_UNICODE( "StarBasic" ), pBasicManager );
/*N*/       pBasicCont->acquire();  // Hold via UNO
/*N*/         Reference< XLibraryContainer > xBasicCont = static_cast< XLibraryContainer* >( pBasicCont );
/*N*/       pImp->pBasicLibContainer = pBasicCont;
/*N*/         pBasicCont->setBasicManager( pBasicManager );
/*N*/
/*N*/       // Dialog container
/*N*/         SotStorage* pStor = NULL;
/*N*/       SfxDialogLibraryContainer* pDialogCont = new SfxDialogLibraryContainer( pStor );
/*N*/       pDialogCont->acquire(); // Hold via UNO
/*N*/         Reference< XLibraryContainer > xDialogCont = static_cast< XLibraryContainer* >( pDialogCont );
/*N*/       pImp->pDialogLibContainer = pDialogCont;
/*N*/
/*N*/       LibraryContainerInfo* pInfo = new LibraryContainerInfo
/*N*/             ( xBasicCont, xDialogCont, static_cast< OldBasicPassword* >( pBasicCont ) );
/*N*/       pBasicManager->SetLibraryContainerInfo( pInfo );
/*N*/
/*N*/       Any aBasicCont;
/*N*/       aBasicCont <<= xBasicCont;
/*N*/       xUnoObj = GetSbUnoObject( DEFINE_CONST_UNICODE("BasicLibraries"), aBasicCont );
/*N*/       pBas->Insert( xUnoObj );
/*N*/
/*N*/       Any aDialogCont;
/*N*/       aDialogCont <<= xDialogCont;
/*N*/       xUnoObj = GetSbUnoObject( DEFINE_CONST_UNICODE("DialogLibraries"), aDialogCont );
/*N*/       pBas->Insert( xUnoObj );
/*N*/
/*N*/         Any aAny;
/*N*/         SfxObjectShell* pDoc = SfxObjectShell::Current();
/*N*/         if ( pDoc )
/*N*/         {
/*N*/             Reference< XInterface > xInterface ( pDoc->GetModel(), UNO_QUERY );
/*N*/             aAny <<= xInterface;
/*N*/         }
/*N*/
/*N*/         SFX_APP()->Get_Impl()->pThisDocument = pDoc;
/*N*/         xUnoObj = GetSbUnoObject( DEFINE_CONST_UNICODE("ThisComponent"), aAny );
/*N*/         xUnoObj->SetFlag( SBX_DONTSTORE );
/*N*/         pBas->Insert( xUnoObj );
/*N*/
/*N*/       // Konstanten
/*N*/ //ASDBG       RegisterBasicConstants( "so", aConstants, sizeof(aConstants)/sizeof(SfxConstant) );
/*N*/
/*N*/       // Durch MakeVariable wird das Basic modifiziert.
/*N*/       if ( !bBasicWasModified )
/*N*/           pBas->SetModified( sal_False );
/*N*/   }
/*N*/
/*N*/   return pImp->pBasicMgr;
/*N*/ }

//--------------------------------------------------------------------

//STRIP001 Reference< XLibraryContainer > SfxApplication::GetDialogContainer()
//STRIP001 {
//STRIP001  Reference< XLibraryContainer > xRet
//STRIP001      = static_cast< XLibraryContainer* >( pImp->pDialogLibContainer );
//STRIP001  return xRet;
//STRIP001 }

//--------------------------------------------------------------------

/*?*/ Reference< XLibraryContainer > SfxApplication::GetBasicContainer()
/*?*/ {DBG_ASSERT(0, "STRIP");  Reference< XLibraryContainer > xRet; return xRet;//STRIP001
//STRIP001  Reference< XLibraryContainer > xRet
//STRIP001      = static_cast< XLibraryContainer* >( pImp->pBasicLibContainer );
//STRIP001  return xRet;
/*?*/ }

//--------------------------------------------------------------------

/*N*/ StarBASIC* SfxApplication::GetBasic()
/*N*/ {
/*N*/   return GetBasicManager()->GetLib(0);
/*N*/ }

//--------------------------------------------------------------------

//STRIP001 FASTBOOL SfxApplication::IsInBasicCall() const
//STRIP001 {
//STRIP001  return 0 != pAppData_Impl->nBasicCallLevel;
//STRIP001 }

//--------------------------------------------------------------------

/*N*/ void SfxApplication::EnterBasicCall()
/*N*/ {
/*N*/   if ( 1 == ++pAppData_Impl->nBasicCallLevel )
/*N*/   {
/*N*/       DBG_TRACE( "SfxShellObject: BASIC-on-demand" );
/*N*/
/*N*/       // das kann l"anger dauern, da Progress nicht geht, wenigstens Sanduhr
/*N*/ //(mba)/task        SfxWaitCursor aWait;
/*N*/
/*N*/       // zuerst das BASIC laden
/*N*/       GetBasic();
/*
        // als erstes SfxShellObject das SbxObject der SfxApplication erzeugen
        SbxObject *pSbx = GetSbxObject();
        DBG_ASSERT( pSbx, "SfxShellObject: can't create SbxObject for SfxApplication" );

        // die SbxObjects aller Module erzeugen
        SfxModuleArr_Impl& rArr = GetModules_Impl();
        for ( sal_uInt16 n = 0; n < rArr.Count(); ++n )
        {
            SfxModule *pMod = rArr.GetObject(n);
            if ( pMod->IsLoaded() )
            {
                pSbx = pMod->GetSbxObject();
                DBG_ASSERT( pSbx, "SfxModule: can't create SbxObject" );
            }
        }

        // die SbxObjects aller Tasks erzeugen
        for ( SfxTask *pTask = SfxTask::GetFirst(); pTask; pTask = SfxTask::GetNext( *pTask ) )
            pTask->GetSbxObject();

        // die SbxObjects aller SfxObjectShells erzeugen (ggf. Frame-los!)
        for ( SfxObjectShell *pObjSh = SfxObjectShell::GetFirst( NULL, sal_False );
              pObjSh;
              pObjSh = SfxObjectShell::GetNext(*pObjSh, NULL, sal_False) )
        {
            // kein IP-Object oder wenn doch dann initialisiert?
            SvStorageRef aStorage;
            if ( !pObjSh->IsHandsOff() )
                aStorage = pObjSh->GetStorage();
            if ( !pObjSh->GetInPlaceObject() || aStorage.Is() )
            {
                DBG( DbgOutf( "SfxShellObject: BASIC-on-demand for %s",
                              pObjSh->SfxShell::GetName().GetBuffer() ) );
                pSbx = pObjSh->GetSbxObject();
                DBG_ASSERT( pSbx, "SfxShellObject: can't create SbxObject" );
            }
        }

        // die SbxObjects der SfxShells auf den Stacks der Frames erzeugen
        for ( SfxViewFrame *pFrame = SfxViewFrame::GetFirst(0,0,sal_False);
              pFrame;
              pFrame = SfxViewFrame::GetNext(*pFrame,0,0,sal_False) )
        {
            // den Dispatcher des Frames rausholen
            SfxDispatcher *pDispat = pFrame->GetDispatcher();
            pDispat->Flush();

            // "uber alle SfxShells auf dem Stack des Dispatchers iterieren
            // Frame selbst wird ausgespart, da er indirekt angezogen wird,
            // sofern er ein Dokument enth"alt.
            for ( sal_uInt16 nStackIdx = pDispat->GetShellLevel(*pFrame);
                  0 != nStackIdx;
                  --nStackIdx )
            {
                DBG( DbgOutf( "SfxShellObject: BASIC-on-demand for level %u", nStackIdx-1 ); )
                pSbx = pDispat->GetShell(nStackIdx - 1)->GetSbxObject();
                DBG_ASSERT( pSbx, "SfxShellObject: can't create SbxObject" );
            }

            if ( !pFrame->GetObjectShell() )
            {
                DBG( DbgOutf( "SfxShellObject: BASIC-on-demand for empty frame" ); )
                pSbx = pFrame->GetSbxObject();
                DBG_ASSERT( pSbx, "SfxShellObject: can't create SbxObject" );
            }
        }
*/
        // Factories anmelden
//        SbxBase::AddFactory( new SfxSbxObjectFactory_Impl );
/*N*/   }
/*N*/ }

//--------------------------------------------------------------------

/*N*/ void SfxApplication::LeaveBasicCall()
/*N*/ {
/*N*/   --pAppData_Impl->nBasicCallLevel;
/*N*/ }

//--------------------------------------------------------------------

//STRIP001 void SfxApplication::EventExec_Impl( SfxRequest &rReq, SfxObjectShell *pObjSh )
//STRIP001 {
//STRIP001 }

//-------------------------------------------------------------------------

//STRIP001 void SfxApplication::EventState_Impl
//STRIP001 (
//STRIP001  sal_uInt16          nSID,
//STRIP001  SfxItemSet&     rSet,
//STRIP001  SfxObjectShell* pObjSh
//STRIP001 )
//STRIP001 {
//STRIP001 }

//-------------------------------------------------------------------------
/*?*/ void SfxApplication::PropExec_Impl( SfxRequest &rReq )
/*?*/ {
//STRIP001 #if SUPD<613//MUSTINI
//STRIP001  SfxIniManager *pIniMgr = GetIniManager();
//STRIP001 #endif
//STRIP001  const SfxItemSet *pArgs = rReq.GetArgs();
//STRIP001  sal_uInt16 nSID = rReq.GetSlot();
//STRIP001  switch ( nSID )
//STRIP001  {
//STRIP001      case SID_CREATE_BASICOBJECT:
//STRIP001      {
//STRIP001          SFX_REQUEST_ARG(rReq, pItem, SfxStringItem, nSID, sal_False);
//STRIP001          if ( pItem )
//STRIP001          {
//STRIP001              SbxObject* pObject = SbxBase::CreateObject( pItem->GetValue() );
//STRIP001              pObject->AddRef();
//STRIP001 //(mba)                rReq.SetReturnValue( SfxObjectItem( 0, pObject ) );
//STRIP001              rReq.Done();
//STRIP001          }
//STRIP001          break;
//STRIP001      }
//STRIP001
//STRIP001      case SID_DELETE_BASICOBJECT:
//STRIP001      {
//STRIP001          SFX_REQUEST_ARG(rReq, pItem, SfxObjectItem, nSID, sal_False);
//STRIP001          if ( pItem )
//STRIP001          {
//STRIP001 //(mba)                SbxObject* pObject = pItem->GetObject();
//STRIP001 //(mba)                pObject->ReleaseRef();
//STRIP001          }
//STRIP001          break;
//STRIP001      }
//STRIP001
//STRIP001      case SID_WIN_POSSIZE:
//STRIP001      {
//STRIP001          break;
//STRIP001      }
//STRIP001
//STRIP001      case SID_INTERACTIVEMODE:
//STRIP001      {
//STRIP001          break;
//STRIP001      }
//STRIP001
//STRIP001      case SID_ATTR_UNDO_COUNT:
//STRIP001      {
//STRIP001          SFX_REQUEST_ARG(rReq, pCountItem, SfxUInt16Item, nSID, sal_False);
//STRIP001             SvtUndoOptions().SetUndoCount( pCountItem->GetValue() );
//STRIP001          break;
//STRIP001      }
//STRIP001
//STRIP001      case SID_WIN_VISIBLE:
//STRIP001      {
//STRIP001          break;
//STRIP001      }
//STRIP001
//STRIP001      case SID_ON_STARTAPP:
//STRIP001      case SID_ON_CLOSEAPP:
//STRIP001      case SID_ON_CREATEDOC:
//STRIP001      case SID_ON_OPENDOC:
//STRIP001      case SID_ON_PREPARECLOSEDOC:
//STRIP001      case SID_ON_CLOSEDOC:
//STRIP001      case SID_ON_SAVEDOC:
//STRIP001      case SID_ON_SAVEASDOC:
//STRIP001      case SID_ON_ACTIVATEDOC:
//STRIP001      case SID_ON_DEACTIVATEDOC:
//STRIP001      case SID_ON_PRINTDOC:
//STRIP001      case SID_ON_SAVEDOCDONE:
//STRIP001      case SID_ON_SAVEASDOCDONE:
//STRIP001          EventExec_Impl( rReq, 0 );
//STRIP001          break;
//STRIP001
//STRIP001      case SID_STATUSBARTEXT:
//STRIP001      {
//STRIP001          SFX_REQUEST_ARG(rReq, pStringItem, SfxStringItem, nSID, sal_False);
//STRIP001          String aText = pStringItem->GetValue();
//STRIP001          if ( aText.Len() )
//STRIP001              GetpApp()->ShowStatusText( aText );
//STRIP001          else
//STRIP001              GetpApp()->HideStatusText();
//STRIP001          break;
//STRIP001      }
//STRIP001
//STRIP001      case SID_HELP:
//STRIP001      {
//STRIP001          break;
//STRIP001      }
//STRIP001
//STRIP001      case SID_PLAYMACRO:
//STRIP001          PlayMacro_Impl( rReq, GetBasic() );
//STRIP001          break;
//STRIP001
//STRIP001      case SID_OFFICE_PRIVATE_USE:
//STRIP001      case SID_OFFICE_COMMERCIAL_USE:
//STRIP001      {
//STRIP001          DBG_ASSERT( sal_False, "SfxApplication::PropExec_Impl()\nSID_OFFICE_PRIVATE_USE & SID_OFFICE_COMMERCIAL_USE are obsolete!\n" );
//STRIP001          break;
//STRIP001      }
//STRIP001
//STRIP001      case SID_OFFICE_CUSTOMERNUMBER:
//STRIP001      {
//STRIP001          SFX_REQUEST_ARG(rReq, pStringItem, SfxStringItem, nSID, sal_False);
//STRIP001
//STRIP001          if ( pStringItem )
//STRIP001              SvtUserOptions().SetCustomerNumber( pStringItem->GetValue() );
//STRIP001          break;
//STRIP001      }
//STRIP001  }
/*?*/ }

//-------------------------------------------------------------------------
/*?*/ void SfxApplication::PropState_Impl( SfxItemSet &rSet )
/*?*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  SfxViewFrame *pFrame = SfxViewFrame::Current();
//STRIP001  SfxWhichIter aIter(rSet);
//STRIP001  for ( sal_uInt16 nSID = aIter.FirstWhich(); nSID; nSID = aIter.NextWhich() )
//STRIP001  {
//STRIP001      switch ( nSID )
//STRIP001      {
//STRIP001          case SID_PROGNAME:
//STRIP001              rSet.Put( SfxStringItem( SID_PROGNAME, GetName() ) );
//STRIP001              break;
//STRIP001
//STRIP001          case SID_ACTIVEDOCUMENT:
//STRIP001              rSet.Put( SfxObjectItem( SID_ACTIVEDOCUMENT, SfxObjectShell::Current() ) );
//STRIP001              break;
//STRIP001
//STRIP001          case SID_APPLICATION:
//STRIP001                 rSet.Put( SfxObjectItem( SID_APPLICATION, this ) );
//STRIP001              break;
//STRIP001
//STRIP001          case SID_STARWRITER:
//STRIP001          {
//STRIP001              SfxModule *pMod = (*(SfxModule**) GetAppData(BF_SHL_WRITER))->Load();
//STRIP001              if ( pMod ) HACK(muss vom Modul selbst gemacht werden)
//STRIP001                  pMod->SetName( DEFINE_CONST_UNICODE("StarWriter") );
//STRIP001                 rSet.Put( SfxObjectItem( nSID, pMod ) );
//STRIP001              break;
//STRIP001          }
//STRIP001
//STRIP001          case SID_STARDRAW:
//STRIP001          {
//STRIP001              SfxModule *pMod = (*(SfxModule**) GetAppData(BF_SHL_DRAW))->Load();
//STRIP001              if ( pMod ) HACK(muss vom Modul selbst gemacht werden)
//STRIP001                  pMod->SetName( DEFINE_CONST_UNICODE("StarDraw") );
//STRIP001                 rSet.Put( SfxObjectItem( nSID, pMod  ) );
//STRIP001              break;
//STRIP001          }
//STRIP001
//STRIP001          case SID_STARCALC:
//STRIP001          {
//STRIP001              SfxModule *pMod = (*(SfxModule**) GetAppData(BF_SHL_CALC))->Load();
//STRIP001              if ( pMod ) HACK(muss vom Modul selbst gemacht werden)
//STRIP001                  pMod->SetName( DEFINE_CONST_UNICODE("StarCalc") );
//STRIP001                 rSet.Put( SfxObjectItem( nSID, pMod  ) );
//STRIP001              break;
//STRIP001          }
//STRIP001
//STRIP001          case SID_PROGFILENAME:
//STRIP001              rSet.Put( SfxStringItem( SID_PROGFILENAME, Application::GetAppFileName() ) );
//STRIP001              break;
//STRIP001
//STRIP001          case SID_INTERACTIVEMODE:
//STRIP001              rSet.Put( SfxBoolItem( SID_INTERACTIVEMODE, !IsDispatcherLocked() ) );
//STRIP001              break;
//STRIP001
//STRIP001          case SID_ATTR_UNDO_COUNT:
//STRIP001                 rSet.Put( SfxUInt16Item( SID_ATTR_UNDO_COUNT, SvtUndoOptions().GetUndoCount() ) );
//STRIP001              break;
//STRIP001
//STRIP001          case SID_ON_STARTAPP:
//STRIP001          case SID_ON_CLOSEAPP:
//STRIP001          case SID_ON_CREATEDOC:
//STRIP001          case SID_ON_OPENDOC:
//STRIP001          case SID_ON_PREPARECLOSEDOC:
//STRIP001          case SID_ON_CLOSEDOC:
//STRIP001          case SID_ON_SAVEDOC:
//STRIP001          case SID_ON_SAVEASDOC:
//STRIP001          case SID_ON_ACTIVATEDOC:
//STRIP001          case SID_ON_DEACTIVATEDOC:
//STRIP001          case SID_ON_PRINTDOC:
//STRIP001          case SID_ON_SAVEDOCDONE:
//STRIP001          case SID_ON_SAVEASDOCDONE:
//STRIP001              EventState_Impl( nSID, rSet, 0 );
//STRIP001
//STRIP001          case SID_UPDATE_VERSION:
//STRIP001              rSet.Put( SfxUInt32Item( SID_UPDATE_VERSION, SUPD ) );
//STRIP001              break;
//STRIP001
//STRIP001          case SID_BUILD_VERSION:
//STRIP001          {
//STRIP001              String aVersion = lcl_GetVersionString(pAppData_Impl->pLabelResMgr);
//STRIP001              rSet.Put( SfxUInt32Item( SID_BUILD_VERSION, (sal_uInt32) aVersion.ToInt32() ) );
//STRIP001              break;
//STRIP001          }
//STRIP001
//STRIP001          case SID_STATUSBARTEXT:
//STRIP001          {
//STRIP001              rSet.Put( SfxStringItem( SID_STATUSBARTEXT, GetStatusBarManager()->GetStatusBar()->GetText() ) );
//STRIP001              break;
//STRIP001          }
//STRIP001          case SID_OFFICE_VERSION_ID:
//STRIP001          {
//STRIP001              String sVersionString;
//STRIP001              ResId aVerId( STR_VERSION_ID, pAppData_Impl->pLabelResMgr );
//STRIP001              if(pAppData_Impl->pLabelResMgr->IsAvailable(    aVerId.SetRT( RSC_STRING ) ))
//STRIP001                  sVersionString += String(aVerId);
//STRIP001              else
//STRIP001                  sVersionString += DEFINE_CONST_UNICODE("50"); // wenn man keine Iso-Dll haben sollte und vorher nicht abgeraucht ist
//STRIP001              String sOS(S2U(getenv("OS")));
//STRIP001              String sProc(S2U(getenv("CPU")));
//STRIP001
//STRIP001              sal_uInt16 nSystem = SYSTEM_ID;
//STRIP001              if(nSystem < 10)
//STRIP001                  sVersionString += 0x0030 ; // '0' = 30h
//STRIP001              sVersionString += String::CreateFromInt32( nSystem );
//STRIP001              String sBuildVersion = lcl_GetVersionString(pAppData_Impl->pLabelResMgr);
//STRIP001              sal_uInt16 nLen = sBuildVersion.Len();
//STRIP001              if(nLen > 4)
//STRIP001              {
//STRIP001                  DBG_ERROR("Buildversion laenger als 4 Zeichen ?")
//STRIP001                  sBuildVersion.Erase(4, nLen - 4);
//STRIP001              }
//STRIP001              else if(nLen < 4)
//STRIP001              {
//STRIP001                  DBG_ERROR("Buildversion kuerzer als 4 Zeichen ?")
//STRIP001
//STRIP001                  while(5 > nLen++)
//STRIP001                      sBuildVersion.Insert(DEFINE_CONST_UNICODE("0"), 0);
//STRIP001              }
//STRIP001              sVersionString += sBuildVersion;
//STRIP001              String sResStr(S2U(ResMgr::GetLang()));
//STRIP001              if( sResStr.Len() < 2)
//STRIP001                  sResStr.Insert(DEFINE_CONST_UNICODE("0"), 0);
//STRIP001              sVersionString += sResStr;
//STRIP001
//STRIP001              aVerId = ResId( STR_VERSION_TYPE, pAppData_Impl->pLabelResMgr );
//STRIP001              if(pAppData_Impl->pLabelResMgr->IsAvailable(    aVerId.SetRT( RSC_STRING ) ))
//STRIP001                  sVersionString += String(aVerId);
//STRIP001              else
//STRIP001                  sVersionString += DEFINE_CONST_UNICODE("99"); // wenn man keine Iso-Dll haben sollte
//STRIP001
//STRIP001              sal_uInt16 nDemoKind = GetDemoKind();
//STRIP001              switch(nDemoKind)
//STRIP001              {
//STRIP001                  case  SFX_DEMOKIND_FULL  : sVersionString += '1'; break;
//STRIP001                  case  SFX_DEMOKIND_TRYBUY: sVersionString += '2'; break;
//STRIP001                  case  SFX_DEMOKIND_DEMO  : sVersionString += '3'; break;
//STRIP001                  default: sVersionString += '0';
//STRIP001              }
//STRIP001
//STRIP001              sVersionString += Application::IsRemoteServer() ? '1' : '0';
//STRIP001              rSet.Put(SfxStringItem(nSID, sVersionString));
//STRIP001
//STRIP001          }
//STRIP001          break;
//STRIP001
//STRIP001          case SID_OFFICE_PRIVATE_USE:
//STRIP001          case SID_OFFICE_COMMERCIAL_USE:
//STRIP001          {
//STRIP001              DBG_ASSERT( sal_False, "SfxApplication::PropState_Impl()\nSID_OFFICE_PRIVATE_USE & SID_OFFICE_COMMERCIAL_USE are obsolete!\n" );
//STRIP001              break;
//STRIP001          }
//STRIP001
//STRIP001          case SID_OFFICE_CUSTOMERNUMBER:
//STRIP001          {
//STRIP001              rSet.Put( SfxStringItem( nSID, SvtUserOptions().GetCustomerNumber() ) );
//STRIP001              break;
//STRIP001          }
//STRIP001      }
//STRIP001  }
/*?*/ }

//--------------------------------------------------------------------
/*N*/ void SfxApplication::MacroExec_Impl( SfxRequest& rReq )
/*N*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  DBG_MEMTEST();
//STRIP001  if ( SfxMacroConfig::IsMacroSlot( rReq.GetSlot() ) )
//STRIP001  {
//STRIP001      // SlotId referenzieren, damit nicht im Execute der Slot abgeschossen
//STRIP001      // werden kann
//STRIP001      GetMacroConfig()->RegisterSlotId(rReq.GetSlot());
//STRIP001      SFX_REQUEST_ARG(rReq, pArgs, SfxStringItem,
//STRIP001                      rReq.GetSlot(), sal_False);
//STRIP001      String aArgs;
//STRIP001      if( pArgs ) aArgs = pArgs->GetValue();
//STRIP001      if ( GetMacroConfig()->ExecuteMacro(rReq.GetSlot(), aArgs ) )
//STRIP001          rReq.Done();
//STRIP001      GetMacroConfig()->ReleaseSlotId(rReq.GetSlot());
//STRIP001  }
/*N*/ }

//--------------------------------------------------------------------
/*N*/ void SfxApplication::MacroState_Impl( SfxItemSet& rSet )
/*N*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  DBG_MEMTEST();
//STRIP001
//STRIP001    // Gestrichen, da zu teuer! Ausserdem waere ein EnterBasicCall noetig
//STRIP001 /*
//STRIP001  const sal_uInt16 *pRanges = rSet.GetRanges();
//STRIP001  DBG_ASSERT(pRanges && *pRanges, "Set ohne Bereich");
//STRIP001  while ( *pRanges )
//STRIP001  {
//STRIP001      for(sal_uInt16 nWhich = *pRanges++; nWhich <= *pRanges; ++nWhich)
//STRIP001      {
//STRIP001          sal_Bool bOK = sal_False;
//STRIP001          if ( SfxMacroConfig::IsMacroSlot( nWhich ) )
//STRIP001              bOK = GetMacroConfig()->CheckMacro(nWhich);
//STRIP001
//STRIP001          if ( !bOK )
//STRIP001              rSet.DisableItem(nWhich);
//STRIP001      }
//STRIP001
//STRIP001      ++pRanges;
//STRIP001  }
//STRIP001  */
/*N*/ }

//-------------------------------------------------------------------------

//STRIP001 void SfxApplication::PlayMacro_Impl( SfxRequest &rReq, StarBASIC *pBasic )
//STRIP001 {
//STRIP001  EnterBasicCall();
//STRIP001  sal_Bool bOK = sal_False;
//STRIP001
//STRIP001  // Makro und asynch-Flag
//STRIP001  SFX_REQUEST_ARG(rReq,pMacro,SfxStringItem,SID_STATEMENT,sal_False);
//STRIP001  SFX_REQUEST_ARG(rReq,pAsynch,SfxBoolItem,SID_ASYNCHRON,sal_False);
//STRIP001
//STRIP001  if ( pAsynch && pAsynch->GetValue() )
//STRIP001  {
//STRIP001      // asynchron ausf"uhren
//STRIP001      GetDispatcher_Impl()->Execute( SID_PLAYMACRO, SFX_CALLMODE_ASYNCHRON, pMacro, 0L );
//STRIP001      rReq.Done();
//STRIP001  }
//STRIP001  else if ( pMacro )
//STRIP001  {
//STRIP001      // Statement aufbereiten
//STRIP001      DBG_ASSERT( pBasic, "no BASIC found" ) ;
//STRIP001      String aStatement( '[' );
//STRIP001      aStatement += pMacro->GetValue();
//STRIP001      aStatement += ']';
//STRIP001
//STRIP001      // P"aventiv den Request abschlie\sen, da er ggf. zerst"ort wird
//STRIP001      rReq.Done();
//STRIP001      rReq.ReleaseArgs();
//STRIP001
//STRIP001      // Statement ausf"uhren
//STRIP001      SbxVariable* pRet = pBasic->Execute( aStatement );
//STRIP001      bOK = 0 == SbxBase::GetError();
//STRIP001      SbxBase::ResetError();
//STRIP001  }
//STRIP001
//STRIP001  LeaveBasicCall();
//STRIP001  rReq.SetReturnValue(SfxBoolItem(0,bOK));
//STRIP001 }


