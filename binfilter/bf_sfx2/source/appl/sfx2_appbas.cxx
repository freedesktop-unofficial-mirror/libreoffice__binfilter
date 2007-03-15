/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sfx2_appbas.cxx,v $
 *
 *  $Revision: 1.11 $
 *
 *  last change: $Author: obo $ $Date: 2007-03-15 15:21:17 $
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

#ifndef _COM_SUN_STAR_FRAME_XDESKTOP_HPP_
#include <com/sun/star/frame/XDesktop.hpp>
#endif
#ifndef _COM_SUN_STAR_UNO_REFERENCE_H_
#include <com/sun/star/uno/Reference.h>
#endif

#ifndef _URLOBJ_HXX
#include <tools/urlobj.hxx>
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

#include <svtools/pathoptions.hxx>

#pragma hdrstop

#include "appuno.hxx"
#include "objsh.hxx"
#include "app.hrc"
#include "dinfdlg.hxx"
#include "appdata.hxx"
#include "stbmgr.hxx"
#include "appimp.hxx"
#include "dlgcont.hxx"

#ifndef _BASMGR_HXX
#include "bf_basic/basmgr.hxx"
#endif

#include "scriptcont.hxx"

#define ITEMID_SEARCH SID_SEARCH_ITEM

#include "srchitem.hxx"

#define SFX_TYPEMAP
#define Selection

#ifndef _LEGACYBINFILTERMGR_HXX
#include <legacysmgr/legacy_binfilters_smgr.hxx>    //STRIP002
#endif
#include "so3/staticbaseurl.hxx"

namespace binfilter {
#include "sfxslots.hxx"

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
//--------------------------------------------------------------------

namespace
{
    static BasicManager*& lcl_getAppBasicManager()
    {
        static BasicManager* s_pAppBasicManager = NULL;
        return s_pAppBasicManager;
    }
}

//========================================================================

StarBASIC* SfxApplication::GetBasic_Impl() const
{
    BasicManager* pBasMgr = lcl_getAppBasicManager();
    return pBasMgr ? pBasMgr->GetLib(0) : NULL;
}

//------------------------------------------------------------------------

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
        String aBaseURL = so3::StaticBaseUrl::GetBaseURL();
        so3::StaticBaseUrl::SetBaseURL( aAppBasicObj.GetMainURL( INetURLObject::NO_DECODE ) );
        pImp->pBasicMgr->Store( *aStor );
        so3::StaticBaseUrl::SetBaseURL( aBaseURL );
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


//--------------------------------------------------------------------

BasicManager* SfxApplication::GetBasicManager()
{
    if ( pAppData_Impl->nBasicCallLevel == 0 )
        // sicherheitshalber
        EnterBasicCall();

    BasicManager*& pBasMgr = lcl_getAppBasicManager();
    if ( !pBasMgr )
    {
        // Directory bestimmen
        SvtPathOptions aPathCFG;
        String aAppBasicDir( aPathCFG.GetBasicPath() );
        if ( !aAppBasicDir.Len() )
            aPathCFG.SetBasicPath( String::CreateFromAscii("$(prog)") );

        // #58293# soffice.new nur im ::com::sun::star::sdbcx::User-Dir suchen => erstes Verzeichnis
        String aAppFirstBasicDir = aAppBasicDir.GetToken(1);

        // Basic erzeugen und laden
        // MT: #47347# AppBasicDir ist jetzt ein PATH!
        INetURLObject aAppBasic( SvtPathOptions().SubstituteVariable( String::CreateFromAscii("$(progurl)") ) );
        aAppBasic.insertName( Application::GetAppName() );

        pBasMgr = new BasicManager( new StarBASIC, &aAppBasicDir );

        // Als Destination das erste Dir im Pfad:
        String aFileName( aAppBasic.getName() );
        aAppBasic = INetURLObject( aAppBasicDir.GetToken(1) );
        DBG_ASSERT( aAppBasic.GetProtocol() != INET_PROT_NOT_VALID, "Invalid URL!" );
        aAppBasic.insertName( aFileName );
        pBasMgr->SetStorageName( aAppBasic.PathToFileName() );

        // globale Variablen
        StarBASIC *pBas = pBasMgr->GetLib(0);
        sal_Bool bBasicWasModified = pBas->IsModified();

/*
        Reference< ::com::sun::star::lang::XMultiServiceFactory > xSMgr = ::comphelper::getProcessServiceFactory();
        Any aDesktop;
        Reference< XDesktop > xDesktop( xSMgr->createInstance(::rtl::OUString::createFromAscii("com.sun.star.frame.Desktop")), UNO_QUERY );
        aDesktop <<= xDesktop ;
        SbxObjectRef xUnoObj = GetSbUnoObject( DEFINE_CONST_UNICODE("StarDesktop"), aDesktop );
        xUnoObj->SetFlag( SBX_DONTSTORE );
        pBas->Insert( xUnoObj );
        //pBas->setRoot( xDesktop );
*/

        // Basic container
        SfxScriptLibraryContainer* pBasicCont = new SfxScriptLibraryContainer
            ( DEFINE_CONST_UNICODE( "StarBasic" ), pBasMgr );
        pBasicCont->acquire();  // Hold via UNO
        Reference< XLibraryContainer > xBasicCont = static_cast< XLibraryContainer* >( pBasicCont );
//        pAppData_Impl->pBasicLibContainer = pBasicCont;
        pBasicCont->setBasicManager( pBasMgr );

        // Dialog container
        SfxDialogLibraryContainer* pDialogCont = new SfxDialogLibraryContainer( NULL );
        pDialogCont->acquire(); // Hold via UNO
        Reference< XLibraryContainer > xDialogCont = static_cast< XLibraryContainer* >( pDialogCont );
//        pAppData_Impl->pDialogLibContainer = pDialogCont;

        LibraryContainerInfo* pInfo = new LibraryContainerInfo
            ( xBasicCont, xDialogCont, static_cast< OldBasicPassword* >( pBasicCont ) );
        pBasMgr->SetLibraryContainerInfo( pInfo );

/*      Any aBasicCont;
        aBasicCont <<= xBasicCont;
        xUnoObj = GetSbUnoObject( DEFINE_CONST_UNICODE("BasicLibraries"), aBasicCont );
        pBas->Insert( xUnoObj );

        Any aDialogCont;
        aDialogCont <<= xDialogCont;
        xUnoObj = GetSbUnoObject( DEFINE_CONST_UNICODE("DialogLibraries"), aDialogCont );
        pBas->Insert( xUnoObj );

        Any aAny;
        SfxObjectShell* pDoc = SfxObjectShell::Current();
        if ( pDoc )
        {
            Reference< XInterface > xInterface ( pDoc->GetModel(), UNO_QUERY );
            aAny <<= xInterface;
        }

        SFX_APP()->Get_Impl()->pThisDocument = pDoc;
        xUnoObj = GetSbUnoObject( DEFINE_CONST_UNICODE("ThisComponent"), aAny );
        xUnoObj->SetFlag( SBX_DONTSTORE );
        pBas->Insert( xUnoObj );
*/

        // Konstanten
//ASDBG     RegisterBasicConstants( "so", aConstants, sizeof(aConstants)/sizeof(SfxConstant) );

        // Durch MakeVariable wird das Basic modifiziert.
        if ( !bBasicWasModified )
            pBas->SetModified( sal_False );
    }

    return pBasMgr;
}

//--------------------------------------------------------------------


//--------------------------------------------------------------------

/*?*/ Reference< XLibraryContainer > SfxApplication::GetBasicContainer()
/*?*/ {DBG_BF_ASSERT(0, "STRIP");   Reference< XLibraryContainer > xRet; return xRet;//STRIP001
/*?*/ }

//--------------------------------------------------------------------

/*N*/ StarBASIC* SfxApplication::GetBasic()
/*N*/ {
/*N*/   return GetBasicManager()->GetLib(0);
/*N*/ }

//--------------------------------------------------------------------


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


//-------------------------------------------------------------------------


//-------------------------------------------------------------------------
/*?*/ void SfxApplication::PropExec_Impl( SfxRequest &rReq )
/*?*/ {
/*?*/ }

//-------------------------------------------------------------------------
/*?*/ void SfxApplication::PropState_Impl( SfxItemSet &rSet )
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*?*/ }

//--------------------------------------------------------------------
/*N*/ void SfxApplication::MacroExec_Impl( SfxRequest& rReq )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/ }

//--------------------------------------------------------------------
/*N*/ void SfxApplication::MacroState_Impl( SfxItemSet& rSet )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/ }

//-------------------------------------------------------------------------



}
