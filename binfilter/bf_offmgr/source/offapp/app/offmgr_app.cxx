/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: offmgr_app.cxx,v $
 *
 *  $Revision: 1.12 $
 *
 *  last change: $Author: obo $ $Date: 2007-03-15 15:17:27 $
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

#ifndef _TOOLS_SIMPLERESMGR_HXX_
#include <tools/simplerm.hxx>
#endif

#ifndef _COM_SUN_STAR_DRAWING_MEASURETEXTVERTPOS_HPP_
#include <com/sun/star/drawing/MeasureTextVertPos.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_TEXTANIMATIONDIRECTION_HPP_
#include <com/sun/star/drawing/TextAnimationDirection.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_CONNECTIONTYPE_HPP_
#include <com/sun/star/drawing/ConnectionType.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_LINESTYLE_HPP_
#include <com/sun/star/drawing/LineStyle.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_TEXTUREMODE_HPP_
#include <com/sun/star/drawing/TextureMode.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_ARRANGEMENT_HPP_
#include <com/sun/star/drawing/Arrangement.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_TEXTANIMATIONKIND_HPP_
#include <com/sun/star/drawing/TextAnimationKind.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_DASHSTYLE_HPP_
#include <com/sun/star/drawing/DashStyle.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_TEXTADJUST_HPP_
#include <com/sun/star/drawing/TextAdjust.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_PROJECTIONMODE_HPP_
#include <com/sun/star/drawing/ProjectionMode.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_LINEENDTYPE_HPP_
#include <com/sun/star/drawing/LineEndType.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_RECTANGLEPOINT_HPP_
#include <com/sun/star/drawing/RectanglePoint.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_MEASURETEXTHORZPOS_HPP_
#include <com/sun/star/drawing/MeasureTextHorzPos.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_CONNECTORTYPE_HPP_
#include <com/sun/star/drawing/ConnectorType.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_MIRRORAXIS_HPP_
#include <com/sun/star/drawing/MirrorAxis.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_TEXTUREKIND_HPP_
#include <com/sun/star/drawing/TextureKind.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_NORMALSKIND_HPP_
#include <com/sun/star/drawing/NormalsKind.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_ALIGNMENT_HPP_
#include <com/sun/star/drawing/Alignment.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_SHADEMODE_HPP_
#include <com/sun/star/drawing/ShadeMode.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_MEASUREKIND_HPP_
#include <com/sun/star/drawing/MeasureKind.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_LAYERTYPE_HPP_
#include <com/sun/star/drawing/LayerType.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_SNAPOBJECTTYPE_HPP_
#include <com/sun/star/drawing/SnapObjectType.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_FILLSTYLE_HPP_
#include <com/sun/star/drawing/FillStyle.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_CIRCLEKIND_HPP_
#include <com/sun/star/drawing/CircleKind.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_HORIZONTALDIMENSIONING_HPP_
#include <com/sun/star/drawing/HorizontalDimensioning.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_HATCHSTYLE_HPP_
#include <com/sun/star/drawing/HatchStyle.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_VERTICALDIMENSIONING_HPP_
#include <com/sun/star/drawing/VerticalDimensioning.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_TEXTFITTOSIZETYPE_HPP_
#include <com/sun/star/drawing/TextFitToSizeType.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_POLYGONKIND_HPP_
#include <com/sun/star/drawing/PolygonKind.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_TEXTUREPROJECTIONMODE_HPP_
#include <com/sun/star/drawing/TextureProjectionMode.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_POLYGONFLAGS_HPP_
#include <com/sun/star/drawing/PolygonFlags.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_DRAWVIEWMODE_HPP_
#include <com/sun/star/drawing/DrawViewMode.hpp>
#endif
#ifndef _COM_SUN_STAR_LOADER_XIMPLEMENTATIONLOADER_HPP_
#include <com/sun/star/loader/XImplementationLoader.hpp>
#endif
#ifndef _COM_SUN_STAR_LOADER_CANNOTACTIVATEFACTORYEXCEPTION_HPP_
#include <com/sun/star/loader/CannotActivateFactoryException.hpp>
#endif
#ifndef _COM_SUN_STAR_CONTAINER_XSET_HPP_
#include <com/sun/star/container/XSet.hpp>
#endif
#include <comphelper/processfactory.hxx>
#include <rtl/logfile.hxx>

#ifndef _SVX_UNOSHCOL_HXX

#ifndef _CONFIG_HXX
#include <tools/config.hxx>
#endif

#ifndef _SVX_IMPGRF_HXX //autogen
#include <bf_svx/impgrf.hxx>
#endif
#ifndef _STRING_HXX //autogen
//#include <tools/string.hxx>
#endif
#ifndef _URLOBJ_HXX //autogen
#include <tools/urlobj.hxx>
#endif
#ifndef _SFXPTITEM_HXX
#include <svtools/ptitem.hxx>
#endif
#ifndef _SFX_FCONTNR_HXX //autogen
#include <bf_sfx2/fcontnr.hxx>
#endif
#ifndef _SFXREQUEST_HXX
#include <bf_sfx2/request.hxx>
#endif
#ifndef _FM_FMOBJFAC_HXX
#include <bf_svx/fmobjfac.hxx>
#endif
#ifndef _SVX_SIIMPORT_HXX
#include <bf_svx/siimport.hxx>
#endif
#ifndef _SVX_TBCONTRL_HXX //autogen
#include <bf_svx/tbcontrl.hxx>
#endif
#ifndef _SVX_SRCHDLG_HXX //autogen
#include <bf_svx/srchdlg.hxx>
#endif
#ifndef _SVX_ADRITEM_HXX //autogen
#include <bf_svx/adritem.hxx>
#endif
#ifndef _OUTLINER_HXX //autogen
#include <bf_svx/outliner.hxx>
#endif
#ifndef _SV_WRKWIN_HXX //autogen
#include <vcl/wrkwin.hxx>
#endif
#ifndef _IMAPDLG_HXX_ //autogen
#include <bf_svx/imapdlg.hxx>
#endif
#ifndef _CPPUHELPER_FACTORY_HXX_
#include <cppuhelper/factory.hxx>
#endif

#ifndef _SFXREQUEST_HXX
#include <bf_sfx2/request.hxx>
#endif

#ifndef _SFXITEMSET_HXX
#include <svtools/itemset.hxx>
#endif
#ifndef _OFA_FONTSUBSTCONFIG_HXX
#include <fontsubstconfig.hxx>
#endif

// include ---------------------------------------------------------------

#ifndef _OFF_APP_HXX
#include "app.hxx"
#endif
#ifndef _OFF_APPIMP_HXX
#include "appimp.hxx"
#endif
#ifndef _OFF_RESID_HXX
#include "resid.hxx"
#endif
#ifndef _OFF_APP_HRC
#include "app.hrc"
#endif

#ifndef _SFX_DBCOLL_HXX
#include "dbcoll.hxx"
#endif
#ifndef _SVX_DLG_HYPERLINK_HXX
#include "hyprlink.hxx"
#endif
#ifndef _SFX_INETOPT_HXX
#include "optuno.hxx"
#endif

#ifndef _SV_MSGBOX_HXX
#include <vcl/msgbox.hxx>
#endif
#ifndef _SFXDISPATCH_HXX
#include <bf_sfx2/dispatch.hxx>
#endif
#ifndef _SFXMSG_HXX
#include <bf_sfx2/msg.hxx>
#endif
#ifndef _SFXOBJFACE_HXX
#include <bf_sfx2/objface.hxx>
#endif

#ifndef _PSTM_HXX
#include <tools/pstm.hxx>
#endif

#ifndef _SVX_ITEMDATA_HXX
#include <bf_svx/itemdata.hxx>
#endif

#define ITEMID_FIELD 0
#ifndef _SVX_FLDITEM_HXX
#include <bf_svx/flditem.hxx>
#endif
#ifndef _SVDFIELD_HXX
#include <bf_svx/svdfield.hxx>
#endif
#ifndef _OBJFAC3D_HXX
#include <bf_svx/objfac3d.hxx>
#endif
#ifndef _SVX_SIZEITEM_HXX
#define ITEMID_SIZE 0
#include <bf_svx/sizeitem.hxx>
#endif
#ifndef _SVX_ZOOMITEM_HXX
#include <bf_svx/zoomitem.hxx>
#endif
#ifndef _SVX_LANGITEM_HXX
#define ITEMID_LANGUAGE 0
#include <bf_svx/langitem.hxx>
#endif
#ifndef _SVX_UNOSHGRP_HXX
#include <bf_svx/unoshcol.hxx>
#endif
#endif

#ifndef _SVX_TAB_HYPERLINK_HXX
#include <bf_svx/hyperdlg.hxx>
#endif
#ifndef _SVX_HLNKITEM_HXX
#include <bf_svx/hlnkitem.hxx>
#endif
#ifndef _NUMUNO_HXX
#include <svtools/numuno.hxx>
#endif
#ifndef _SB_SBSTAR_HXX
#include "bf_basic/sbstar.hxx"
#endif

#include <svtools/moduleoptions.hxx>
#include <bf_sfx2/viewsh.hxx>
#include <bf_sfx2/viewfrm.hxx>

#include "calwin.hxx"
#ifndef _OFA_APEARCFG_HXX
#include "apearcfg.hxx"
#endif

#ifndef _SBASLTID_HRC
#include "sbasltid.hrc"
#endif

#ifndef _VOS_MUTEX_HXX_
#include <vos/mutex.hxx>
#endif

#include <osl/module.hxx>
#ifndef _LEGACYBINFILTERMGR_HXX
#include <legacysmgr/legacy_binfilters_smgr.hxx>    //STRIP002
#endif

using namespace ::com::sun::star::uno;

//=========================================================================

#define SFX_TYPEMAP
#define Address
#define _ExecAddress  ExecuteApp_Impl
#define _StateAddress GetStateApp_Impl
#define OfficeApplication
//STRIP008 #include "ofaslots.hxx"
namespace binfilter {
#include "ofaslots.hxx"
/*N*/ TYPEINIT1(OfficeApplication,SfxApplication);

#define IS_AVAILABLE(WhichId,ppItem) \
    (pArgs->GetItemState((WhichId), sal_True, ppItem ) == SFX_ITEM_SET)

#define DOSTRING( x )                       #x
#define STRING( x )                         DOSTRING( x )

//=========================================================================

//=========================================================================

/*N*/ SFX_IMPL_INTERFACE(OfficeApplication,SfxApplication,OffResId(RID_DESKTOP))
/*N*/ {
/*N*/   SFX_CHILDWINDOW_REGISTRATION( SID_HYPERLINK_INSERT );
/*N*/ //  SFX_CHILDWINDOW_REGISTRATION( SID_HYPERLINK_DIALOG );
/*N*/ //    SFX_CHILDWINDOW_REGISTRATION( SID_SHOW_BROWSER );
/*N*/ }

// ------------------------------------------------------------------------
// hack: this must be implemented somewhere else, hack for 554 update

/*N*/  Reference< XInterface > SAL_CALL SvxShapeCollection_CreateInstance( const Reference< ::com::sun::star::lang::XMultiServiceFactory >& rSMgr ) throw( Exception )
/*N*/  {
/*?*/   return *( new SvxShapeCollection() );
/*N*/  }

/*N*/ void OfficeApplication::Init()
/*N*/ {
/*N*/   RTL_LOGFILE_CONTEXT( aLog, "offmgr (cd100003) ::OfficeApplication::Init" );
/*N*/
/*N*/     SfxApplication::Init();
/*N*/
/*N*/   SvxIMapDlgChildWindow::RegisterChildWindow();
/*N*/
/*N*/     // set basic error handler
/*N*/   StarBASIC::SetGlobalErrorHdl( LINK( this, OfficeApplication, GlobalBasicErrorHdl ) );
/*N*/
/*N*/   CreateDataImpl();
/*N*/   UseFontSubst();
/*N*/
/*N*/   OfficeApplication::RegisterInterface();
/*N*/
/*N*/   SvxSearchDialogWrapper::RegisterChildWindow();
/*N*/   SvxHlinkDlgWrapper::RegisterChildWindow ();
/*N*/
/*N*/   //OfficeApplication::RegisterInterface();
/*N*/     SvxReloadControllerItem::RegisterControl( SID_RELOAD );
/*N*/
/*N*/     // SvxURLField registrieren
/*N*/   SvClassManager& rClassManager = SvxFieldItem::GetClassManager();
/*N*/   rClassManager.SV_CLASS_REGISTER( SvxFieldData );
/*N*/   rClassManager.SV_CLASS_REGISTER( SvxURLField );
/*N*/   rClassManager.SV_CLASS_REGISTER( SvxDateField );
/*N*/   rClassManager.SV_CLASS_REGISTER( SvxPageField );
/*N*/   rClassManager.SV_CLASS_REGISTER( SvxTimeField );
/*N*/   rClassManager.SV_CLASS_REGISTER( SvxExtTimeField );
/*N*/   rClassManager.SV_CLASS_REGISTER( SvxExtFileField );
/*N*/   rClassManager.SV_CLASS_REGISTER( SvxAuthorField );
/*N*/
/*N*/     // SvDraw-Felder registrieren
/*N*/     SdrRegisterFieldClasses();
/*N*/
/*N*/     // 3D-Objekt-Factory eintragen
/*N*/     E3dObjFactory();
/*N*/
/*N*/     // ::com::sun::star::form::component::Form-Objekt-Factory eintragen
/*N*/     FmFormObjFactory();
/*N*/
/*N*/     // factory for dummy import of old si-controls in 3.1 documents
/*N*/     SiImportFactory();
/*N*/
/*N*/   // Servies etc. registrieren
/*N*/   RTL_LOGFILE_CONTEXT_TRACE( aLog, "{ register services: com.sun.star.drawing.ShapeCollection/com.sun.star.util.NumberFormatter" );
/*N*/   Reference< ::com::sun::star::lang::XMultiServiceFactory >  xSMgr = ::legacy_binfilters::getLegacyProcessServiceFactory();
/*N*/   Reference< ::com::sun::star::container::XSet >  xSet( xSMgr, UNO_QUERY );
/*N*/   Sequence< ::rtl::OUString >         aName( 1 );
/*N*/   Reference< ::com::sun::star::lang::XSingleServiceFactory >  xFact;
/*N*/
/*N*/   aName.getArray()[0] = ::rtl::OUString::createFromAscii("com.sun.star.drawing.ShapeCollection");
/*N*/   xFact = ::cppu::createSingleFactory( xSMgr, ::rtl::OUString::createFromAscii("ShapeCollection"), SvxShapeCollection_CreateInstance, aName );
/*N*/   xSet->insert( makeAny(xFact) );
/*N*/
//STRIP007  Not needed, Number formatter is now registered and accessed normally // aName.getArray()[0] = ::rtl::OUString::createFromAscii("com.sun.star.util.NumberFormatter");
//STRIP007  xFact = ::cppu::createSingleFactory( xSMgr, ::rtl::OUString::createFromAscii("NumberFormatter"), SvNumberFormatterServiceObj_NewInstance, aName );
//STRIP007  xSet->insert( makeAny( xFact ) );
/*N*/
/*N*/   xSet->insert( makeAny( SfxSettingsContainer::impl_createFactory(xSMgr) ) );
/*N*/   RTL_LOGFILE_CONTEXT_TRACE( aLog, "} register services: com.sun.star.drawing.ShapeCollection/com.sun.star.util.NumberFormatter" );
/*N*/
/*N*/   // options - general - appearance
//delete by jmeng  in Unix for i31251 begin
#ifdef WNT
/*N*/   OfaTabAppearanceCfg* pAppearanceCfg = GetTabAppearanceConfig();
/*N*/   pAppearanceCfg->SetInitialized();
/*N*/   pAppearanceCfg->SetApplicationDefaults( GetpApp() );
#endif
//delete by jmeng  in Unix for i31251 end
/*N*/
/*N*/     pDataImpl->SetVCLSettings();
/*N*/ }

// ------------------------------------------------------------------------
/*N*/ void OfficeApplication::Exit()
/*N*/ {
/*N*/   if ( pDataImpl->pWordDeInitFct )
/*?*/       pDataImpl->pWordDeInitFct();
/*N*/ }

//------------------------------------------------------------------------------


/*N*/ void OfficeApplication::UseFontSubst()
/*N*/ {
/*N*/   OutputDevice::BeginFontSubstitution();
/*N*/   // Alte Substitution entfernen
/*N*/   sal_uInt16 nOldCount = OutputDevice::GetFontSubstituteCount();
/*N*/
/*N*/   while (nOldCount)
/*?*/       OutputDevice::RemoveFontSubstitute(--nOldCount);

    // Neue Substitution einlesen
/*N*/   OfaFontSubstConfig aFontConfig;
/*N*/     sal_Int32 nCount = aFontConfig.IsEnabled() ? aFontConfig.SubstitutionCount() : 0;
/*N*/
/*N*/   for (sal_Int32  i = 0; i < nCount; i++)
/*N*/   {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/     }
/*N*/   OutputDevice::EndFontSubstitution();
/*N*/ }

// ------------------------------------------------------------------------

/*N*/ ResMgr* OfficeApplication::GetOffResManager()
/*N*/ {
/*N*/   if ( !pImpl->pResMgr )
/*N*/       pImpl->pResMgr = CreateResManager( "bf_ofa"); //STRIP005
/*N*/   return pImpl->pResMgr;
/*N*/ }

// ------------------------------------------------------------------------

/*N*/void OfficeApplication::DrawExec_Impl( SfxRequest &rReq )
/*N*/{DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/ }

// ------------------------------------------------------------------------

/*N*/void OfficeApplication::ModuleState_Impl( SfxItemSet &rSet )
/*N*/{DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/ }


// ------------------------------------------------------------------------

/*N*/void OfficeApplication::WriterExec_Impl( SfxRequest &rReq )
/*N*/{DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/ }

// ------------------------------------------------------------------------

/*N*/ IMPL_LINK( OfficeApplication, GlobalBasicErrorHdl, StarBASIC*, pBasic )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); return 0;//STRIP001
/*N*/ }

// ------------------------------------------------------------------------
} //namespace binfilter
