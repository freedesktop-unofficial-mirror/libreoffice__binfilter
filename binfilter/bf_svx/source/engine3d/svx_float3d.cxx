/*************************************************************************
 *
 *  $RCSfile: svx_float3d.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2004-05-05 16:40:28 $
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
 *  WITHOUT WARRUNTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING,
 *  WITHOUT LIMITATION, WARRUNTIES THAT THE SOFTWARE IS FREE OF DEFECTS,
 *  MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE, OR NON-INFRINGING.
 *  See the License for the specific provisions governing your rights and
 *  obligations concerning the Software.
 *
 *  The Initial Developer of the Original Code is: Sun Microsystems, Inc..
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

#ifndef _SFXDISPATCH_HXX //autogen
#include <bf_sfx2/dispatch.hxx>
#endif
#ifndef _SFXMODULE_HXX //autogen
#include <bf_sfx2/module.hxx>
#endif
#ifndef _SFXVIEWFRM_HXX //autogen
#include <bf_sfx2/viewfrm.hxx>
#endif
#ifndef _SFXENUMITEM_HXX //autogen
#include <svtools/eitem.hxx>
#endif
#ifndef _SV_COLRDLG_HXX //autogen
#include <svtools/colrdlg.hxx>
#endif
#ifndef _SV_MSGBOX_HXX //autogen
#include <vcl/msgbox.hxx>
#endif

#ifndef _SFXVIEWSH_HXX //autogen
#include <bf_sfx2/viewsh.hxx>
#endif
#ifndef _SHL_HXX
#include <tools/shl.hxx>
#endif

#ifndef _SVX_XFLCLIT_HXX
#include <xflclit.hxx>
#endif
#ifndef _SVDMODEL_HXX
#include <svdmodel.hxx>
#endif
#ifndef _E3D_GLOBL3D_HXX
#include <globl3d.hxx>
#endif
#ifndef _E3D_VIEW3D_HXX
#include <view3d.hxx>
#endif
#ifndef _E3D_OBJ3D_HXX
#include <obj3d.hxx>
#endif
#ifndef _E3D_SPHERE3D_HXX
#include <sphere3d.hxx>
#endif
#ifndef _E3D_SCENE3D_HXX
#include <scene3d.hxx>
#endif
#ifndef _CAMERA3D_HXX
#include <camera3d.hxx>
#endif
#ifndef _SVX_FMMODEL_HXX
#include <fmmodel.hxx>
#endif
#ifndef _SVX_FMPAGE_HXX
#include <fmpage.hxx>
#endif
#ifndef _E3D_POLYSC3D_HXX
#include <polysc3d.hxx>
#endif
#ifndef _EEITEM_HXX //autogen
#include <eeitem.hxx>
#endif
#ifndef _SFXSTYLE_HXX
#include <svtools/style.hxx>
#endif


#include <dlgutil.hxx>
#include <dialmgr.hxx>
#include <viewpt3d.hxx> // ProjectionType

#include <svxids.hrc>
#include <dialogs.hrc>

#define ITEMID_COLOR            SID_ATTR_3D_LIGHTCOLOR
#include <colritem.hxx>
#include <e3ditem.hxx>

#include <gallery.hxx>
#define GALLERY_THEME "3D"

#ifndef _SFX_WHITER_HXX
#include <svtools/whiter.hxx>
#endif

#include "float3d.hxx"
#include "float3d.hrc"
namespace binfilter {

/*N*/ SFX_IMPL_DOCKINGWINDOW( Svx3DChildWindow, SID_3D_WIN )

//STRIP001 struct Svx3DWinImpl
//STRIP001 {
//STRIP001  SfxItemPool*        pPool;
//STRIP001  Image               maImgLightOnH;
//STRIP001  Image               maImgLightOffH;
//STRIP001 };

#define SETHCIMAGE(btn,res) \
{ \
    Bitmap aBmp( SVX_RES( res ) ); \
    Image aImage( aBmp, COL_LIGHTMAGENTA ); \
    btn.SetModeImage( aImage, BMP_COLOR_HIGHCONTRAST ); \
}

/*************************************************************************
|*  Svx3DWin - FloatingWindow
\************************************************************************/
//STRIP001 __EXPORT Svx3DWin::Svx3DWin( SfxBindings* pInBindings,
//STRIP001              SfxChildWindow *pCW, Window* pParent ) :
//STRIP001      SfxDockingWindow    ( pInBindings, pCW, pParent,
//STRIP001                                  SVX_RES( RID_SVXFLOAT_3D ) ),
//STRIP001      aBtnFavorites       ( this, SVX_RES( BTN_FAVORITES ) ),
//STRIP001      aBtnGeo             ( this, SVX_RES( BTN_GEO ) ),
//STRIP001      aBtnRepresentation  ( this, SVX_RES( BTN_REPRESENTATION ) ),
//STRIP001      aBtnLight           ( this, SVX_RES( BTN_LIGHT ) ),
//STRIP001      aBtnTexture         ( this, SVX_RES( BTN_TEXTURE ) ),
//STRIP001      aBtnMaterial        ( this, SVX_RES( BTN_MATERIAL ) ),
//STRIP001      aBtnUpdate          ( this, SVX_RES( BTN_UPDATE ) ),
//STRIP001      aBtnAssign          ( this, SVX_RES( BTN_ASSIGN ) ),
//STRIP001
//STRIP001      // Favoriten
//STRIP001      aCtlFavorites       ( this, SVX_RES( CTL_FAVORITES ) ),
//STRIP001         aFLFavorites        ( this, SVX_RES( FL_FAVORITES ) ),
//STRIP001      aBtnOnly3D          ( this, SVX_RES( BTN_ONLY_3D ) ),
//STRIP001      aBtnAllAttributes   ( this, SVX_RES( BTN_ALL_ATTRIBUTES ) ),
//STRIP001
//STRIP001      // Geometrie
//STRIP001      aFtHorizontal       ( this, SVX_RES( FT_HORIZONTAL ) ),
//STRIP001      aNumHorizontal      ( this, SVX_RES( NUM_HORIZONTAL ) ),
//STRIP001      aFtVertical         ( this, SVX_RES( FT_VERTICAL ) ),
//STRIP001      aNumVertical        ( this, SVX_RES( NUM_VERTICAL ) ),
//STRIP001         aFLSegments        ( this, SVX_RES( FL_SEGMENTS ) ),
//STRIP001      aFtPercentDiagonal  ( this, SVX_RES( FT_PERCENT_DIAGONAL ) ),
//STRIP001      aMtrPercentDiagonal ( this, SVX_RES( MTR_PERCENT_DIAGONAL ) ),
//STRIP001      aFtBackscale        ( this, SVX_RES( FT_BACKSCALE ) ),
//STRIP001      aMtrBackscale       ( this, SVX_RES( MTR_BACKSCALE ) ),
//STRIP001      aFtEndAngle         ( this, SVX_RES( FT_END_ANGLE ) ),
//STRIP001      aMtrEndAngle        ( this, SVX_RES( MTR_END_ANGLE ) ),
//STRIP001      aFtDepth            ( this, SVX_RES( FT_DEPTH ) ),
//STRIP001      aMtrDepth           ( this, SVX_RES( MTR_DEPTH ) ),
//STRIP001         aFLGeometrie       ( this, SVX_RES( FL_GEOMETRIE ) ),
//STRIP001
//STRIP001      aBtnNormalsObj      ( this, SVX_RES( BTN_NORMALS_OBJ ) ),
//STRIP001      aBtnNormalsFlat     ( this, SVX_RES( BTN_NORMALS_FLAT ) ),
//STRIP001      aBtnNormalsSphere   ( this, SVX_RES( BTN_NORMALS_SPHERE ) ),
//STRIP001      aBtnTwoSidedLighting( this, SVX_RES( BTN_TWO_SIDED_LIGHTING ) ),
//STRIP001      aBtnNormalsInvert   ( this, SVX_RES( BTN_NORMALS_INVERT ) ),
//STRIP001         aFLNormals         ( this, SVX_RES( FL_NORMALS ) ),
//STRIP001
//STRIP001      aBtnDoubleSided     ( this, SVX_RES( BTN_DOUBLE_SIDED ) ),
//STRIP001
//STRIP001      // Darstellung
//STRIP001      aFtShademode        ( this, SVX_RES( FT_SHADEMODE ) ),
//STRIP001      aLbShademode        ( this, SVX_RES( LB_SHADEMODE ) ),
//STRIP001      aBtnShadow3d        ( this, SVX_RES( BTN_SHADOW_3D ) ),
//STRIP001      aFtSlant            ( this, SVX_RES( FT_SLANT ) ),
//STRIP001      aMtrSlant           ( this, SVX_RES( MTR_SLANT ) ),
//STRIP001         aFLShadow          ( this, SVX_RES( FL_SHADOW ) ),
//STRIP001      aFtDistance         ( this, SVX_RES( FT_DISTANCE ) ),
//STRIP001      aMtrDistance        ( this, SVX_RES( MTR_DISTANCE ) ),
//STRIP001      aFtFocalLeng        ( this, SVX_RES( FT_FOCAL_LENGTH ) ),
//STRIP001      aMtrFocalLength     ( this, SVX_RES( MTR_FOCAL_LENGTH ) ),
//STRIP001         aFLCamera          ( this, SVX_RES( FL_CAMERA ) ),
//STRIP001         aFLRepresentation  ( this, SVX_RES( FL_REPRESENTATION ) ),
//STRIP001
//STRIP001      // Beleuchtung
//STRIP001      aBtnLight1          ( this, SVX_RES( BTN_LIGHT_1 ) ),
//STRIP001      aBtnLight2          ( this, SVX_RES( BTN_LIGHT_2 ) ),
//STRIP001      aBtnLight3          ( this, SVX_RES( BTN_LIGHT_3 ) ),
//STRIP001      aBtnLight4          ( this, SVX_RES( BTN_LIGHT_4 ) ),
//STRIP001      aBtnLight5          ( this, SVX_RES( BTN_LIGHT_5 ) ),
//STRIP001      aBtnLight6          ( this, SVX_RES( BTN_LIGHT_6 ) ),
//STRIP001      aBtnLight7          ( this, SVX_RES( BTN_LIGHT_7 ) ),
//STRIP001      aBtnLight8          ( this, SVX_RES( BTN_LIGHT_8 ) ),
//STRIP001      aLbLight1           ( this, SVX_RES( LB_LIGHT_1 ) ),
//STRIP001      aLbLight2           ( this, SVX_RES( LB_LIGHT_2 ) ),
//STRIP001      aLbLight3           ( this, SVX_RES( LB_LIGHT_3 ) ),
//STRIP001      aLbLight4           ( this, SVX_RES( LB_LIGHT_4 ) ),
//STRIP001      aLbLight5           ( this, SVX_RES( LB_LIGHT_5 ) ),
//STRIP001      aLbLight6           ( this, SVX_RES( LB_LIGHT_6 ) ),
//STRIP001      aLbLight7           ( this, SVX_RES( LB_LIGHT_7 ) ),
//STRIP001      aLbLight8           ( this, SVX_RES( LB_LIGHT_8 ) ),
//STRIP001
//STRIP001      aBtnLightColor      ( this, SVX_RES( BTN_LIGHT_COLOR ) ),
//STRIP001         aFTLightsource     ( this, SVX_RES( FT_LIGHTSOURCE ) ),
//STRIP001
//STRIP001      // #99694# Keyboard shortcuts activate the next control, so the
//STRIP001      // order needed to be changed here
//STRIP001         aFTAmbientlight    ( this, SVX_RES( FT_AMBIENTLIGHT ) ), // Text label
//STRIP001      aLbAmbientlight     ( this, SVX_RES( LB_AMBIENTLIGHT ) ),   // ListBox
//STRIP001      aBtnAmbientColor    ( this, SVX_RES( BTN_AMBIENT_COLOR ) ), // color button
//STRIP001
//STRIP001      aFLLight           ( this, SVX_RES( FL_LIGHT ) ),
//STRIP001
//STRIP001      // Texturen
//STRIP001      aFtTexKind          ( this, SVX_RES( FT_TEX_KIND ) ),
//STRIP001      aBtnTexLuminance    ( this, SVX_RES( BTN_TEX_LUMINANCE ) ),
//STRIP001      aBtnTexColor        ( this, SVX_RES( BTN_TEX_COLOR ) ),
//STRIP001      aFtTexMode          ( this, SVX_RES( FT_TEX_MODE ) ),
//STRIP001      aBtnTexReplace      ( this, SVX_RES( BTN_TEX_REPLACE ) ),
//STRIP001      aBtnTexModulate     ( this, SVX_RES( BTN_TEX_MODULATE ) ),
//STRIP001      aBtnTexBlend        ( this, SVX_RES( BTN_TEX_BLEND ) ),
//STRIP001      aFtTexProjectionX   ( this, SVX_RES( FT_TEX_PROJECTION_X ) ),
//STRIP001      aBtnTexParallelX    ( this, SVX_RES( BTN_TEX_PARALLEL_X ) ),
//STRIP001      aBtnTexCircleX      ( this, SVX_RES( BTN_TEX_CIRCLE_X ) ),
//STRIP001      aBtnTexObjectX      ( this, SVX_RES( BTN_TEX_OBJECT_X ) ),
//STRIP001      aFtTexProjectionY   ( this, SVX_RES( FT_TEX_PROJECTION_Y ) ),
//STRIP001      aBtnTexParallelY    ( this, SVX_RES( BTN_TEX_PARALLEL_Y ) ),
//STRIP001      aBtnTexCircleY      ( this, SVX_RES( BTN_TEX_CIRCLE_Y ) ),
//STRIP001      aBtnTexObjectY      ( this, SVX_RES( BTN_TEX_OBJECT_Y ) ),
//STRIP001      aFtTexFilter        ( this, SVX_RES( FT_TEX_FILTER ) ),
//STRIP001      aBtnTexFilter       ( this, SVX_RES( BTN_TEX_FILTER ) ),
//STRIP001         aFLTexture         ( this, SVX_RES( FL_TEXTURE ) ),
//STRIP001
//STRIP001      // Material
//STRIP001      aFtMatFavorites     ( this, SVX_RES( FT_MAT_FAVORITES ) ),
//STRIP001      aLbMatFavorites     ( this, SVX_RES( LB_MAT_FAVORITES ) ),
//STRIP001      aFtMatColor         ( this, SVX_RES( FT_MAT_COLOR ) ),
//STRIP001      aLbMatColor         ( this, SVX_RES( LB_MAT_COLOR ) ),
//STRIP001      aBtnMatColor        ( this, SVX_RES( BTN_MAT_COLOR ) ),
//STRIP001      aFtMatEmission      ( this, SVX_RES( FT_MAT_EMISSION ) ),
//STRIP001      aLbMatEmission      ( this, SVX_RES( LB_MAT_EMISSION ) ),
//STRIP001      aBtnEmissionColor   ( this, SVX_RES( BTN_EMISSION_COLOR ) ),
//STRIP001      aFtMatSpecular      ( this, SVX_RES( FT_MAT_SPECULAR ) ),
//STRIP001      aLbMatSpecular      ( this, SVX_RES( LB_MAT_SPECULAR ) ),
//STRIP001      aBtnSpecularColor   ( this, SVX_RES( BTN_SPECULAR_COLOR ) ),
//STRIP001      aFtMatSpecularIntensity( this, SVX_RES( FT_MAT_SPECULAR_INTENSITY ) ),
//STRIP001      aMtrMatSpecularIntensity( this, SVX_RES( MTR_MAT_SPECULAR_INTENSITY ) ),
//STRIP001         aFLMatSpecular     ( this, SVX_RES( FL_MAT_SPECULAR ) ),
//STRIP001         aFLMaterial        ( this, SVX_RES( FL_MATERIAL ) ),
//STRIP001
//STRIP001      // Unterer Bereich
//STRIP001      aBtnPerspective     ( this, SVX_RES( BTN_PERSPECTIVE ) ),
//STRIP001      aBtnConvertTo3D     ( this, SVX_RES( BTN_CHANGE_TO_3D ) ),
//STRIP001      aBtnLatheObject     ( this, SVX_RES( BTN_LATHE_OBJ ) ),
//STRIP001      aCtlPreview         ( this, SVX_RES( CTL_PREVIEW ) ),
//STRIP001      aCtlLightPreview    ( this, SVX_RES( CTL_LIGHT_PREVIEW ) ),
//STRIP001
//STRIP001      aImgLightOn         ( SVX_RES( RID_SVXIMAGE_LIGHT_ON ) ),
//STRIP001      aImgLightOff        ( SVX_RES( RID_SVXIMAGE_LIGHT_OFF ) ),
//STRIP001
//STRIP001      pLightGroup         ( NULL ),
//STRIP001      bUpdate             ( FALSE ),
//STRIP001      eViewType           ( VIEWTYPE_FAVORITES ),
//STRIP001
//STRIP001      pModel              ( NULL ),
//STRIP001      pFmPage             ( NULL ),
//STRIP001      pVDev               ( NULL ),
//STRIP001      p3DView             ( NULL ),
//STRIP001      pFavorSetList       ( NULL ),
//STRIP001      pMatFavSetList      ( NULL ),
//STRIP001
//STRIP001      pBindings           ( pInBindings ),
//STRIP001 //       pPool               ( NULL ),
//STRIP001      mpImpl              ( new Svx3DWinImpl() ),
//STRIP001      mpRemember2DAttributes(NULL),
//STRIP001      bOnly3DChanged      ( FALSE )
//STRIP001 {
//STRIP001  SETHCIMAGE( aBtnFavorites, BMP_FAVORITES_H );
//STRIP001  SETHCIMAGE( aBtnGeo, BMP_GEO_H );
//STRIP001  SETHCIMAGE( aBtnRepresentation, BMP_REPRESENTATION_H );
//STRIP001  SETHCIMAGE( aBtnLight, BMP_3DLIGHT_H );
//STRIP001  SETHCIMAGE( aBtnTexture, BMP_TEXTURE_H );
//STRIP001  SETHCIMAGE( aBtnMaterial, BMP_MATERIAL_H );
//STRIP001  SETHCIMAGE( aBtnUpdate, BMP_UPDATE_H );
//STRIP001  SETHCIMAGE( aBtnAssign, BMP_ASSIGN_H );
//STRIP001  SETHCIMAGE( aBtnOnly3D, BMP_ONLY_3D_H );
//STRIP001  SETHCIMAGE( aBtnAllAttributes, BMP_ALL_ATTRIBUTES_H );
//STRIP001  SETHCIMAGE( aBtnNormalsObj, BMP_NORMALS_OBJ_H );
//STRIP001  SETHCIMAGE( aBtnNormalsFlat, BMP_NORMALS_FLAT_H );
//STRIP001  SETHCIMAGE( aBtnNormalsSphere, BMP_NORMALS_SPHERE_H );
//STRIP001  SETHCIMAGE( aBtnTwoSidedLighting, BMP_TWO_SIDED_LIGHTING_H );
//STRIP001  SETHCIMAGE( aBtnNormalsInvert, BMP_NORMALS_INVERT_H );
//STRIP001  SETHCIMAGE( aBtnDoubleSided, BMP_DOUBLE_SIDED_H );
//STRIP001  SETHCIMAGE( aBtnShadow3d, BMP_SHADOW_3D_H );
//STRIP001  SETHCIMAGE( aBtnLight1, BMP_LIGHT_H );
//STRIP001  SETHCIMAGE( aBtnLight2, BMP_LIGHT_H );
//STRIP001  SETHCIMAGE( aBtnLight3, BMP_LIGHT_H );
//STRIP001  SETHCIMAGE( aBtnLight4, BMP_LIGHT_H );
//STRIP001  SETHCIMAGE( aBtnLight5, BMP_LIGHT_H );
//STRIP001  SETHCIMAGE( aBtnLight6, BMP_LIGHT_H );
//STRIP001  SETHCIMAGE( aBtnLight7, BMP_LIGHT_H );
//STRIP001  SETHCIMAGE( aBtnLight8, BMP_LIGHT_H );
//STRIP001  SETHCIMAGE( aBtnLightColor, BMP_LIGHT_COLOR_H );
//STRIP001  SETHCIMAGE( aBtnAmbientColor, BMP_AMBIENT_COLOR_H );
//STRIP001  SETHCIMAGE( aBtnTexLuminance, BMP_TEX_LUMINANCE_H );
//STRIP001  SETHCIMAGE( aBtnTexColor, BMP_TEX_COLOR_H );
//STRIP001  SETHCIMAGE( aBtnTexReplace, BMP_TEX_REPLACE_H );
//STRIP001  SETHCIMAGE( aBtnTexModulate, BMP_TEX_MODULATE_H );
//STRIP001  SETHCIMAGE( aBtnTexBlend, BMP_TEX_BLEND_H );
//STRIP001  SETHCIMAGE( aBtnTexParallelX, BMP_TEX_PARALLEL_H );
//STRIP001  SETHCIMAGE( aBtnTexCircleX, BMP_TEX_CIRCLE_H );
//STRIP001  SETHCIMAGE( aBtnTexObjectX, BMP_TEX_OBJECT_H );
//STRIP001  SETHCIMAGE( aBtnTexParallelY, BMP_TEX_PARALLEL_H );
//STRIP001  SETHCIMAGE( aBtnTexCircleY, BMP_TEX_CIRCLE_H );
//STRIP001  SETHCIMAGE( aBtnTexObjectY, BMP_TEX_OBJECT_H );
//STRIP001  SETHCIMAGE( aBtnTexFilter, BMP_TEX_FILTER_H );
//STRIP001  SETHCIMAGE( aBtnMatColor, BMP_COLORDLG_H );
//STRIP001  SETHCIMAGE( aBtnEmissionColor, BMP_COLORDLG_H );
//STRIP001  SETHCIMAGE( aBtnSpecularColor, BMP_COLORDLG_H );
//STRIP001  SETHCIMAGE( aBtnPerspective, BMP_PERSPECTIVE_H );
//STRIP001  SETHCIMAGE( aBtnConvertTo3D, BMP_CHANGE_TO_3D_H );
//STRIP001  SETHCIMAGE( aBtnLatheObject, BMP_LATHE_OBJ_H );
//STRIP001
//STRIP001  mpImpl->pPool = NULL;
//STRIP001  mpImpl->maImgLightOnH = Image( SVX_RES( RID_SVXIMAGE_LIGHT_ON_H ) );
//STRIP001  mpImpl->maImgLightOffH = Image( SVX_RES( RID_SVXIMAGE_LIGHT_OFF_H ) );
//STRIP001  FreeResource();
//STRIP001
//STRIP001  // Metrik einstellen
//STRIP001  eFUnit = GetModuleFieldUnit( NULL );
//STRIP001  aMtrDepth.SetUnit( eFUnit );
//STRIP001  aMtrDistance.SetUnit( eFUnit );
//STRIP001  aMtrFocalLength.SetUnit( eFUnit );
//STRIP001
//STRIP001  pControllerItem = new Svx3DCtrlItem(SID_3D_STATE, this, pBindings);
//STRIP001  pConvertTo3DItem = new SvxConvertTo3DItem(SID_CONVERT_TO_3D, pBindings);
//STRIP001  pConvertTo3DLatheItem = new SvxConvertTo3DItem(SID_CONVERT_TO_3D_LATHE_FAST, pBindings);
//STRIP001
//STRIP001  aBtnAssign.SetClickHdl( LINK( this, Svx3DWin, ClickAssignHdl ) );
//STRIP001  aBtnUpdate.SetClickHdl( LINK( this, Svx3DWin, ClickUpdateHdl ) );
//STRIP001
//STRIP001  Link aLink( LINK( this, Svx3DWin, ClickViewTypeHdl ) );
//STRIP001  aBtnFavorites.SetClickHdl( aLink );
//STRIP001  aBtnGeo.SetClickHdl( aLink );
//STRIP001  aBtnRepresentation.SetClickHdl( aLink );
//STRIP001  aBtnLight.SetClickHdl( aLink );
//STRIP001  aBtnTexture.SetClickHdl( aLink );
//STRIP001  aBtnMaterial.SetClickHdl( aLink );
//STRIP001
//STRIP001  aLink = LINK( this, Svx3DWin, ClickHdl );
//STRIP001  aBtnPerspective.SetClickHdl( aLink );
//STRIP001  aBtnConvertTo3D.SetClickHdl( aLink );
//STRIP001  aBtnLatheObject.SetClickHdl( aLink );
//STRIP001
//STRIP001  aBtnOnly3D.SetClickHdl( aLink );
//STRIP001  aBtnAllAttributes.SetClickHdl( aLink );
//STRIP001
//STRIP001  // Geometrie
//STRIP001  aBtnNormalsObj.SetClickHdl( aLink );
//STRIP001  aBtnNormalsFlat.SetClickHdl( aLink );
//STRIP001  aBtnNormalsSphere.SetClickHdl( aLink );
//STRIP001  aBtnTwoSidedLighting.SetClickHdl( aLink );
//STRIP001  aBtnNormalsInvert.SetClickHdl( aLink );
//STRIP001  aBtnDoubleSided.SetClickHdl( aLink );
//STRIP001
//STRIP001  // Darstellung
//STRIP001  aBtnShadow3d.SetClickHdl( aLink );
//STRIP001
//STRIP001  // Beleuchtung
//STRIP001  aBtnLight1.SetClickHdl( aLink );
//STRIP001  aBtnLight2.SetClickHdl( aLink );
//STRIP001  aBtnLight3.SetClickHdl( aLink );
//STRIP001  aBtnLight4.SetClickHdl( aLink );
//STRIP001  aBtnLight5.SetClickHdl( aLink );
//STRIP001  aBtnLight6.SetClickHdl( aLink );
//STRIP001  aBtnLight7.SetClickHdl( aLink );
//STRIP001  aBtnLight8.SetClickHdl( aLink );
//STRIP001
//STRIP001  // Texturen
//STRIP001  aBtnTexLuminance.SetClickHdl( aLink );
//STRIP001  aBtnTexColor.SetClickHdl( aLink );
//STRIP001  aBtnTexReplace.SetClickHdl( aLink );
//STRIP001  aBtnTexModulate.SetClickHdl( aLink );
//STRIP001  //aBtnTexBlend.SetClickHdl( aLink );
//STRIP001  aBtnTexParallelX.SetClickHdl( aLink );
//STRIP001  aBtnTexCircleX.SetClickHdl( aLink );
//STRIP001  aBtnTexObjectX.SetClickHdl( aLink );
//STRIP001  aBtnTexParallelY.SetClickHdl( aLink );
//STRIP001  aBtnTexCircleY.SetClickHdl( aLink );
//STRIP001  aBtnTexObjectY.SetClickHdl( aLink );
//STRIP001  aBtnTexFilter.SetClickHdl( aLink );
//STRIP001
//STRIP001  // Material
//STRIP001  aLink = LINK( this, Svx3DWin, ClickColorHdl );
//STRIP001  aBtnLightColor.SetClickHdl( aLink );
//STRIP001  aBtnAmbientColor.SetClickHdl( aLink );
//STRIP001  aBtnMatColor.SetClickHdl( aLink );
//STRIP001  aBtnEmissionColor.SetClickHdl( aLink );
//STRIP001  aBtnSpecularColor.SetClickHdl( aLink );
//STRIP001
//STRIP001
//STRIP001  aLink = LINK( this, Svx3DWin, SelectHdl );
//STRIP001  aLbMatFavorites.SetSelectHdl( aLink );
//STRIP001  aLbMatColor.SetSelectHdl( aLink );
//STRIP001  aLbMatEmission.SetSelectHdl( aLink );
//STRIP001  aLbMatSpecular.SetSelectHdl( aLink );
//STRIP001  aLbLight1.SetSelectHdl( aLink );
//STRIP001  aLbLight2.SetSelectHdl( aLink );
//STRIP001  aLbLight3.SetSelectHdl( aLink );
//STRIP001  aLbLight4.SetSelectHdl( aLink );
//STRIP001  aLbLight5.SetSelectHdl( aLink );
//STRIP001  aLbLight6.SetSelectHdl( aLink );
//STRIP001  aLbLight7.SetSelectHdl( aLink );
//STRIP001  aLbLight8.SetSelectHdl( aLink );
//STRIP001  aLbAmbientlight.SetSelectHdl( aLink );
//STRIP001  aLbShademode.SetSelectHdl( aLink );
//STRIP001
//STRIP001  aLink = LINK( this, Svx3DWin, ModifyHdl );
//STRIP001  aMtrMatSpecularIntensity.SetModifyHdl( aLink );
//STRIP001  aNumHorizontal.SetModifyHdl( aLink );
//STRIP001  aNumVertical.SetModifyHdl( aLink );
//STRIP001  aMtrSlant.SetModifyHdl( aLink );
//STRIP001
//STRIP001  aLink = LINK( this, Svx3DWin, DoubleClickHdl );
//STRIP001  aCtlFavorites.SetDoubleClickHdl( aLink );
//STRIP001     aCtlFavorites.SetStyle( aCtlFavorites.GetStyle() | WB_FLATVALUESET );
//STRIP001
//STRIP001  aLink = LINK( this, Svx3DWin, ClickFavoriteHdl );
//STRIP001  aCtlFavorites.SetSelectHdl( aLink );
//STRIP001
//STRIP001  // Preview-Callback
//STRIP001  aLink = LINK( this, Svx3DWin, ChangeLightCallbackHdl );
//STRIP001  aCtlLightPreview.SetUserInteractiveChangeCallback( aLink );
//STRIP001  aLink = LINK( this, Svx3DWin, ChangeSelectionCallbackHdl );
//STRIP001  aCtlLightPreview.SetUserSelectionChangeCallback( aLink );
//STRIP001
//STRIP001     aSize = GetOutputSizePixel();
//STRIP001  SetMinOutputSizePixel( aSize );
//STRIP001
//STRIP001  Construct();
//STRIP001
//STRIP001  // Initiierung der Initialisierung der ColorLBs
//STRIP001  SfxBoolItem aItem( SID_3D_INIT, TRUE );
//STRIP001  SfxViewFrame::Current()->GetBindings().GetDispatcher()->Execute(
//STRIP001      SID_3D_INIT, SFX_CALLMODE_ASYNCHRON | SFX_CALLMODE_RECORD, &aItem, 0L );
//STRIP001
//STRIP001  Reset();
//STRIP001 }

// -----------------------------------------------------------------------
//STRIP001 __EXPORT Svx3DWin::~Svx3DWin()
//STRIP001 {
//STRIP001  //delete pMatFavSetList;
//STRIP001  delete p3DView;
//STRIP001  delete pVDev;
//STRIP001  delete pModel;
//STRIP001
//STRIP001  delete pControllerItem;
//STRIP001  delete pConvertTo3DItem;
//STRIP001  delete pConvertTo3DLatheItem;
//STRIP001
//STRIP001  delete pLightGroup;
//STRIP001
//STRIP001  if(mpRemember2DAttributes)
//STRIP001      delete mpRemember2DAttributes;
//STRIP001
//STRIP001  delete mpImpl;
//STRIP001 }

// -----------------------------------------------------------------------
//STRIP001 void Svx3DWin::Construct()
//STRIP001 {
//STRIP001  // Ueber die Gallery werden die Favoriten eingelesen
//STRIP001  ULONG nFavCount = GalleryExplorer::GetSdrObjCount( GALLERY_THEME_3D );
//STRIP001
//STRIP001  // ValueSet Favoriten
//STRIP001  WinBits nWinBits = aCtlFavorites.GetStyle();
//STRIP001  nWinBits |= WB_ITEMBORDER | WB_DOUBLEBORDER; //| WB_NAMEFIELD
//STRIP001  if( nFavCount > 6 )
//STRIP001      nWinBits |= WB_VSCROLL;
//STRIP001
//STRIP001  aCtlFavorites.SetStyle( nWinBits );
//STRIP001  aCtlFavorites.SetColCount( 3 );
//STRIP001  aCtlFavorites.SetLineCount( 2 );
//STRIP001  aCtlFavorites.SetExtraSpacing( 1 );
//STRIP001
//STRIP001  // Listen erzeugen
//STRIP001 //   pFavorSetList = new List();
//STRIP001 //   SfxItemSet* pSet;
//STRIP001
//STRIP001  // Gallery thema locken
//STRIP001  GalleryExplorer::BeginLocking(GALLERY_THEME_3D);
//STRIP001
//STRIP001  for( ULONG nModelPos = 0; nModelPos < nFavCount; nModelPos++ )
//STRIP001  {
//STRIP001      Bitmap  aThumb;
//STRIP001      Size    aNewSize( 60, 60 );
//STRIP001
//STRIP001      if( GalleryExplorer::GetSdrObj( GALLERY_THEME_3D, nModelPos,
//STRIP001                                      pModel, &aThumb ) )
//STRIP001      {
//STRIP001          // ValueSet fuellen
//STRIP001          Size aOldSize = Size( aThumb.GetSizePixel() );
//STRIP001          aThumb.Scale( (double) aNewSize.Width() / aOldSize.Width(),
//STRIP001                          (double) aNewSize.Height() / aOldSize.Height() );
//STRIP001
//STRIP001          String aStr(SVX_RES(RID_SVXFLOAT3D_FAVORITE));
//STRIP001          aStr += sal_Unicode(' ');
//STRIP001          aStr += String::CreateFromInt32((INT32)nModelPos + 1L);
//STRIP001
//STRIP001          aCtlFavorites.InsertItem( (USHORT)nModelPos+1, aThumb, aStr );
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  // Gallery thema freigeben
//STRIP001  GalleryExplorer::EndLocking(GALLERY_THEME_3D);
//STRIP001
//STRIP001  if( nFavCount == 0 )
//STRIP001  {
//STRIP001      // Keine Favoriten vorhanden
//STRIP001      eViewType = VIEWTYPE_GEO;
//STRIP001  }
//STRIP001
//STRIP001  aCtlLightPreview.Hide();
//STRIP001  pLightGroup = new B3dLightGroup();
//STRIP001  *pLightGroup = *aCtlLightPreview.GetPreviewControl().GetLightGroup();
//STRIP001 }

// -----------------------------------------------------------------------
//STRIP001 void Svx3DWin::Reset()
//STRIP001 {
//STRIP001  // Diverse Initialisierungen, default ist AllAttributes
//STRIP001  aBtnAllAttributes.Check();
//STRIP001  aLbMatFavorites.SelectEntryPos( 0 ); // UserDefined
//STRIP001
//STRIP001  if( eViewType == VIEWTYPE_FAVORITES )
//STRIP001      ClickViewTypeHdl( &aBtnFavorites );
//STRIP001  else
//STRIP001  {
//STRIP001      ClickViewTypeHdl( &aBtnGeo );
//STRIP001      aBtnFavorites.Enable( FALSE );
//STRIP001  }
//STRIP001
//STRIP001  aLbShademode.SelectEntryPos( 0 );
//STRIP001  aMtrMatSpecularIntensity.SetValue( 50 );
//STRIP001
//STRIP001  aBtnLight1.Check();
//STRIP001 //   ClickHdl( &aBtnLight1 );
//STRIP001
//STRIP001  ClickUpdateHdl( NULL );
//STRIP001
//STRIP001  // Nichts selektieren, um Fehler beim erstselektieren zu vermeiden
//STRIP001  aCtlLightPreview.GetPreviewControl().SelectLight(Base3DLight0);
//STRIP001 }

//STRIP001 bool Svx3DWin::GetUILightState( ImageButton& aBtn ) const
//STRIP001 {
//STRIP001  return (aBtn.GetImage() == aImgLightOn) || (aBtn.GetImage() == mpImpl->maImgLightOnH);
//STRIP001 }

//STRIP001 void Svx3DWin::SetUILightState( ImageButton& aBtn, bool bState )
//STRIP001 {
//STRIP001  aBtn.SetImage( bState ? aImgLightOn : aImgLightOff );
//STRIP001  aBtn.SetModeImage( bState ? mpImpl->maImgLightOnH : mpImpl->maImgLightOffH, BMP_COLOR_HIGHCONTRAST );
//STRIP001 }

// -----------------------------------------------------------------------
//STRIP001 void Svx3DWin::Update( SfxItemSet& rAttrs )
//STRIP001 {
//STRIP001  // remember 2d attributes
//STRIP001  if(mpRemember2DAttributes)
//STRIP001      mpRemember2DAttributes->ClearItem();
//STRIP001  else
//STRIP001      mpRemember2DAttributes = new SfxItemSet(*rAttrs.GetPool(),
//STRIP001          SDRATTR_START, SDRATTR_SHADOW_LAST,
//STRIP001          SDRATTR_3D_FIRST, SDRATTR_3D_LAST,
//STRIP001 //           SDRATTR_START, SDRATTR_CIRC_LAST,
//STRIP001 //           SDRATTR_GRAF_FIRST, SDRATTR_3DSCENE_LAST,
//STRIP001          0, 0);
//STRIP001
//STRIP001  SfxWhichIter aIter(*mpRemember2DAttributes);
//STRIP001  sal_uInt16 nWhich(aIter.FirstWhich());
//STRIP001
//STRIP001  while(nWhich)
//STRIP001  {
//STRIP001      SfxItemState eState = rAttrs.GetItemState(nWhich, FALSE);
//STRIP001      if(SFX_ITEM_DONTCARE == eState)
//STRIP001          mpRemember2DAttributes->InvalidateItem(nWhich);
//STRIP001      else if(SFX_ITEM_SET == eState)
//STRIP001          mpRemember2DAttributes->Put(rAttrs.Get(nWhich, FALSE));
//STRIP001
//STRIP001      nWhich = aIter.NextWhich();
//STRIP001  }
//STRIP001
//STRIP001  // construct field values
//STRIP001  const SfxPoolItem* pItem;
//STRIP001  BOOL bUpdate = FALSE;
//STRIP001
//STRIP001  // evtl. PoolUnit ermitteln
//STRIP001  if( !mpImpl->pPool )
//STRIP001  {
//STRIP001      mpImpl->pPool = rAttrs.GetPool();
//STRIP001      DBG_ASSERT( mpImpl->pPool, "Wo ist der Pool?" );
//STRIP001      ePoolUnit = mpImpl->pPool->GetMetric( SID_ATTR_LINE_WIDTH );
//STRIP001  }
//STRIP001  eFUnit = GetModuleFieldUnit( &rAttrs );
//STRIP001
//STRIP001
//STRIP001 // Segmentanzahl aenderbar ? und andere Stati
//STRIP001  SfxItemState eState = rAttrs.GetItemState( SID_ATTR_3D_INTERN, FALSE, &pItem );
//STRIP001  if( SFX_ITEM_SET == eState )
//STRIP001  {
//STRIP001      UINT32 nState = ( ( const SfxUInt32Item* )pItem )->GetValue();
//STRIP001      BOOL bLathe   = (BOOL) ( nState & 1 );
//STRIP001      BOOL bExtrude = (BOOL) ( nState & 2 );
//STRIP001      BOOL bSphere  = (BOOL) ( nState & 4 );
//STRIP001      BOOL bCube    = (BOOL) ( nState & 8 );
//STRIP001
//STRIP001      BOOL bChart = (BOOL) ( nState & 32 ); // Chart
//STRIP001
//STRIP001      if( !bChart )
//STRIP001      {
//STRIP001          // Bei Cube-Objekten werden keine Segmente eingestellt
//STRIP001          aFtHorizontal.Enable( !bCube );
//STRIP001          aNumHorizontal.Enable( !bCube );
//STRIP001          aFtVertical.Enable( !bCube );
//STRIP001          aNumVertical.Enable( !bCube );
//STRIP001             aFLSegments.Enable( !bCube );
//STRIP001
//STRIP001          aFtPercentDiagonal.Enable( !bCube && !bSphere );
//STRIP001          aMtrPercentDiagonal.Enable( !bCube && !bSphere );
//STRIP001          aFtBackscale.Enable( !bCube && !bSphere );
//STRIP001          aMtrBackscale.Enable( !bCube && !bSphere );
//STRIP001          aFtDepth.Enable( !bCube && !bSphere );
//STRIP001          aMtrDepth.Enable( !bCube && !bSphere );
//STRIP001          if( bCube )
//STRIP001          {
//STRIP001              aNumHorizontal.SetEmptyFieldValue();
//STRIP001              aNumVertical.SetEmptyFieldValue();
//STRIP001          }
//STRIP001          if( bCube || bSphere )
//STRIP001          {
//STRIP001              aMtrPercentDiagonal.SetEmptyFieldValue();
//STRIP001              aMtrBackscale.SetEmptyFieldValue();
//STRIP001              aMtrDepth.SetEmptyFieldValue();
//STRIP001          }
//STRIP001
//STRIP001          // Nur bei Lathe-Objekten gibt es einen Endwinkel
//STRIP001          aFtEndAngle.Enable( !bExtrude && !bCube && !bSphere );
//STRIP001          aMtrEndAngle.Enable( !bExtrude && !bCube && !bSphere );
//STRIP001          if( bExtrude || bCube || bSphere )
//STRIP001              aMtrEndAngle.SetEmptyFieldValue();
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          // Geometrie
//STRIP001          aFtHorizontal.Enable( FALSE );
//STRIP001          aNumHorizontal.Enable( FALSE );
//STRIP001          aNumHorizontal.SetEmptyFieldValue();
//STRIP001          aFtVertical.Enable( FALSE );
//STRIP001          aNumVertical.Enable( FALSE );
//STRIP001          aNumVertical.SetEmptyFieldValue();
//STRIP001             aFLSegments.Enable( FALSE );
//STRIP001          aFtEndAngle.Enable( FALSE );
//STRIP001          aMtrEndAngle.Enable( FALSE );
//STRIP001          aMtrEndAngle.SetEmptyFieldValue();
//STRIP001          aFtDepth.Enable( FALSE );
//STRIP001          aMtrDepth.Enable( FALSE );
//STRIP001          aMtrDepth.SetEmptyFieldValue();
//STRIP001
//STRIP001          // Darstellung
//STRIP001          aBtnShadow3d.Enable( FALSE );
//STRIP001          aFtSlant.Enable( FALSE );
//STRIP001          aMtrSlant.Enable( FALSE );
//STRIP001             aFLShadow.Enable( FALSE );
//STRIP001
//STRIP001          aFtDistance.Enable( FALSE );
//STRIP001          aMtrDistance.Enable( FALSE );
//STRIP001          aMtrDistance.SetEmptyFieldValue();
//STRIP001          aFtFocalLeng.Enable( FALSE );
//STRIP001          aMtrFocalLength.Enable( FALSE );
//STRIP001          aMtrFocalLength.SetEmptyFieldValue();
//STRIP001             aFLCamera.Enable( FALSE );
//STRIP001
//STRIP001          // Unterer Bereich
//STRIP001          aBtnConvertTo3D.Enable( FALSE );
//STRIP001          aBtnLatheObject.Enable( FALSE );
//STRIP001      }
//STRIP001  }
//STRIP001 // Bitmapfuellung ? -> Status
//STRIP001  BOOL bBitmap(FALSE);
//STRIP001  eState = rAttrs.GetItemState(XATTR_FILLSTYLE);
//STRIP001  if(eState != SFX_ITEM_DONTCARE)
//STRIP001  {
//STRIP001      XFillStyle eXFS = (XFillStyle)((const XFillStyleItem&)rAttrs.Get(XATTR_FILLSTYLE)).GetValue();
//STRIP001      bBitmap = (eXFS == XFILL_BITMAP || eXFS == XFILL_GRADIENT || eXFS == XFILL_HATCH);
//STRIP001  }
//STRIP001
//STRIP001  aFtTexKind.Enable( bBitmap );
//STRIP001  aBtnTexLuminance.Enable( bBitmap );
//STRIP001  aBtnTexColor.Enable( bBitmap );
//STRIP001  aFtTexMode.Enable( bBitmap );
//STRIP001  aBtnTexReplace.Enable( bBitmap );
//STRIP001  aBtnTexModulate.Enable( bBitmap );
//STRIP001  aBtnTexBlend.Enable( bBitmap );
//STRIP001  aFtTexProjectionX.Enable( bBitmap );
//STRIP001  aBtnTexParallelX.Enable( bBitmap );
//STRIP001  aBtnTexCircleX.Enable( bBitmap );
//STRIP001  aBtnTexObjectX.Enable( bBitmap );
//STRIP001  aFtTexProjectionY.Enable( bBitmap );
//STRIP001  aBtnTexParallelY.Enable( bBitmap );
//STRIP001  aBtnTexCircleY.Enable( bBitmap );
//STRIP001  aBtnTexObjectY.Enable( bBitmap );
//STRIP001  aFtTexFilter.Enable( bBitmap );
//STRIP001  aBtnTexFilter.Enable( bBitmap );
//STRIP001     aFLTexture.Enable( bBitmap );
//STRIP001
//STRIP001
//STRIP001 // Geometrie
//STRIP001  // Anzahl Segmente (horizontal)
//STRIP001  if( aNumHorizontal.IsEnabled() )
//STRIP001  {
//STRIP001      eState = rAttrs.GetItemState(SDRATTR_3DOBJ_HORZ_SEGS);
//STRIP001      if(eState != SFX_ITEM_DONTCARE)
//STRIP001      {
//STRIP001          UINT32 nValue = ((const Svx3DHorizontalSegmentsItem&)rAttrs.Get(SDRATTR_3DOBJ_HORZ_SEGS)).GetValue();
//STRIP001          if(nValue != (UINT32)aNumHorizontal.GetValue())
//STRIP001          {
//STRIP001              aNumHorizontal.SetValue( nValue );
//STRIP001              // evtl. am Ende...
//STRIP001              aCtlLightPreview.GetPreviewControl().SetHorizontalSegments( (UINT16)nValue );
//STRIP001              bUpdate = TRUE;
//STRIP001          }
//STRIP001          else if( aNumHorizontal.IsEmptyFieldValue() )
//STRIP001              aNumHorizontal.SetValue( nValue );
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          if( !aNumHorizontal.IsEmptyFieldValue() )
//STRIP001          {
//STRIP001              aNumHorizontal.SetEmptyFieldValue();
//STRIP001              bUpdate = TRUE;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  // Anzahl Segmente (vertikal)
//STRIP001  if( aNumVertical.IsEnabled() )
//STRIP001  {
//STRIP001      eState = rAttrs.GetItemState(SDRATTR_3DOBJ_VERT_SEGS);
//STRIP001      if( eState != SFX_ITEM_DONTCARE )
//STRIP001      {
//STRIP001          UINT32 nValue = ((const Svx3DVerticalSegmentsItem&)rAttrs.Get(SDRATTR_3DOBJ_VERT_SEGS)).GetValue();
//STRIP001          if( nValue != (UINT32) aNumVertical.GetValue() )
//STRIP001          {
//STRIP001              aNumVertical.SetValue( nValue );
//STRIP001              // evtl. am Ende...
//STRIP001              aCtlLightPreview.GetPreviewControl().SetVerticalSegments( (UINT16)nValue );
//STRIP001              //aCtlPreview.SetVerticalSegments( (UINT16)nValue );
//STRIP001              bUpdate = TRUE;
//STRIP001          }
//STRIP001          else if( aNumVertical.IsEmptyFieldValue() )
//STRIP001              aNumVertical.SetValue( nValue );
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          if( !aNumVertical.IsEmptyFieldValue() )
//STRIP001          {
//STRIP001              aNumVertical.SetEmptyFieldValue();
//STRIP001              bUpdate = TRUE;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  // Tiefe
//STRIP001  if( aMtrDepth.IsEnabled() )
//STRIP001  {
//STRIP001      eState = rAttrs.GetItemState(SDRATTR_3DOBJ_DEPTH);
//STRIP001      if( eState != SFX_ITEM_DONTCARE )
//STRIP001      {
//STRIP001          UINT32 nValue = ((const Svx3DDepthItem&)rAttrs.Get(SDRATTR_3DOBJ_DEPTH)).GetValue();
//STRIP001          UINT32 nValue2 = GetCoreValue( aMtrDepth, ePoolUnit );
//STRIP001          if( nValue != nValue2 )
//STRIP001          {
//STRIP001              if( eFUnit != aMtrDepth.GetUnit() )
//STRIP001                  SetFieldUnit( aMtrDepth, eFUnit );
//STRIP001
//STRIP001              SetMetricValue( aMtrDepth, nValue, ePoolUnit );
//STRIP001              bUpdate = TRUE;
//STRIP001          }
//STRIP001          else if( aMtrDepth.IsEmptyFieldValue() )
//STRIP001              aMtrDepth.SetValue( aMtrDepth.GetValue() );
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          if( !aMtrDepth.IsEmptyFieldValue() )
//STRIP001          {
//STRIP001              aMtrDepth.SetEmptyFieldValue();
//STRIP001              bUpdate = TRUE;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  // Doppelwandig/-seitig
//STRIP001  eState = rAttrs.GetItemState(SDRATTR_3DOBJ_DOUBLE_SIDED);
//STRIP001  if( eState != SFX_ITEM_DONTCARE )
//STRIP001  {
//STRIP001      BOOL bValue = ((const Svx3DDoubleSidedItem&)rAttrs.Get(SDRATTR_3DOBJ_DOUBLE_SIDED)).GetValue();
//STRIP001      if( bValue != aBtnDoubleSided.IsChecked() )
//STRIP001      {
//STRIP001          aBtnDoubleSided.Check( bValue );
//STRIP001          bUpdate = TRUE;
//STRIP001      }
//STRIP001      else if( aBtnDoubleSided.GetState() == STATE_DONTKNOW )
//STRIP001          aBtnDoubleSided.Check( bValue );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      if( aBtnDoubleSided.GetState() != STATE_DONTKNOW )
//STRIP001      {
//STRIP001          aBtnDoubleSided.SetState( STATE_DONTKNOW );
//STRIP001          bUpdate = TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  // Kantenrundung
//STRIP001  if( aMtrPercentDiagonal.IsEnabled() )
//STRIP001  {
//STRIP001      eState = rAttrs.GetItemState(SDRATTR_3DOBJ_PERCENT_DIAGONAL);
//STRIP001      if( eState != SFX_ITEM_DONTCARE )
//STRIP001      {
//STRIP001          UINT16 nValue = ((const Svx3DPercentDiagonalItem&)rAttrs.Get(SDRATTR_3DOBJ_PERCENT_DIAGONAL)).GetValue();
//STRIP001          if( nValue != aMtrPercentDiagonal.GetValue() )
//STRIP001          {
//STRIP001              aMtrPercentDiagonal.SetValue( nValue );
//STRIP001              bUpdate = TRUE;
//STRIP001          }
//STRIP001          else if( aMtrPercentDiagonal.IsEmptyFieldValue() )
//STRIP001              aMtrPercentDiagonal.SetValue( nValue );
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          if( !aMtrPercentDiagonal.IsEmptyFieldValue() )
//STRIP001          {
//STRIP001              aMtrPercentDiagonal.SetEmptyFieldValue();
//STRIP001              bUpdate = TRUE;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  // Tiefenskalierung
//STRIP001  if( aMtrBackscale.IsEnabled() )
//STRIP001  {
//STRIP001      eState = rAttrs.GetItemState(SDRATTR_3DOBJ_BACKSCALE);
//STRIP001      if( eState != SFX_ITEM_DONTCARE )
//STRIP001      {
//STRIP001          UINT16 nValue = ((const Svx3DBackscaleItem&)rAttrs.Get(SDRATTR_3DOBJ_BACKSCALE)).GetValue();
//STRIP001          if( nValue != aMtrBackscale.GetValue() )
//STRIP001          {
//STRIP001              aMtrBackscale.SetValue( nValue );
//STRIP001              bUpdate = TRUE;
//STRIP001          }
//STRIP001          else if( aMtrBackscale.IsEmptyFieldValue() )
//STRIP001              aMtrBackscale.SetValue( nValue );
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          if( !aMtrBackscale.IsEmptyFieldValue() )
//STRIP001          {
//STRIP001              aMtrBackscale.SetEmptyFieldValue();
//STRIP001              bUpdate = TRUE;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  // Endwinkel
//STRIP001  if( aMtrEndAngle.IsEnabled() )
//STRIP001  {
//STRIP001      eState = rAttrs.GetItemState(SDRATTR_3DOBJ_END_ANGLE);
//STRIP001      if( eState != SFX_ITEM_DONTCARE )
//STRIP001      {
//STRIP001          INT32 nValue = ((const Svx3DEndAngleItem&)rAttrs.Get(SDRATTR_3DOBJ_END_ANGLE)).GetValue();
//STRIP001          if( nValue != aMtrEndAngle.GetValue() )
//STRIP001          {
//STRIP001              aMtrEndAngle.SetValue( nValue );
//STRIP001              bUpdate = TRUE;
//STRIP001          }
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          if( !aMtrEndAngle.IsEmptyFieldValue() )
//STRIP001          {
//STRIP001              aMtrEndAngle.SetEmptyFieldValue();
//STRIP001              bUpdate = TRUE;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  // Normalentyp
//STRIP001  eState = rAttrs.GetItemState(SDRATTR_3DOBJ_NORMALS_KIND);
//STRIP001  if( eState != SFX_ITEM_DONTCARE )
//STRIP001  {
//STRIP001      UINT16 nValue = ((const Svx3DNormalsKindItem&)rAttrs.Get(SDRATTR_3DOBJ_NORMALS_KIND)).GetValue();
//STRIP001
//STRIP001      if( ( !aBtnNormalsObj.IsChecked() && nValue == 0 ) ||
//STRIP001          ( !aBtnNormalsFlat.IsChecked() && nValue == 1 ) ||
//STRIP001          ( !aBtnNormalsSphere.IsChecked() && nValue == 2 ) )
//STRIP001      {
//STRIP001          aBtnNormalsObj.Check( nValue == 0 );
//STRIP001          aBtnNormalsFlat.Check( nValue == 1 );
//STRIP001          aBtnNormalsSphere.Check( nValue == 2 );
//STRIP001          bUpdate = TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      if( aBtnNormalsObj.IsChecked() ||
//STRIP001          aBtnNormalsFlat.IsChecked() ||
//STRIP001          aBtnNormalsSphere.IsChecked() )
//STRIP001      {
//STRIP001          aBtnNormalsObj.Check( FALSE );
//STRIP001          aBtnNormalsFlat.Check( FALSE );
//STRIP001          aBtnNormalsSphere.Check( FALSE );
//STRIP001          bUpdate = TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  // Normalen invertieren
//STRIP001  eState = rAttrs.GetItemState(SDRATTR_3DOBJ_NORMALS_INVERT);
//STRIP001  if( eState != SFX_ITEM_DONTCARE )
//STRIP001  {
//STRIP001      BOOL bValue = ((const Svx3DNormalsInvertItem&)rAttrs.Get(SDRATTR_3DOBJ_NORMALS_INVERT)).GetValue();
//STRIP001      if( bValue != aBtnNormalsInvert.IsChecked() )
//STRIP001      {
//STRIP001          aBtnNormalsInvert.Check( bValue );
//STRIP001          bUpdate = TRUE;
//STRIP001      }
//STRIP001      else if( aBtnNormalsInvert.GetState() == STATE_DONTKNOW )
//STRIP001          aBtnNormalsInvert.Check( bValue );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      if( aBtnNormalsInvert.GetState() != STATE_DONTKNOW )
//STRIP001      {
//STRIP001          aBtnNormalsInvert.SetState( STATE_DONTKNOW );
//STRIP001          bUpdate = TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  // 2-seitige Beleuchtung
//STRIP001  eState = rAttrs.GetItemState(SDRATTR_3DSCENE_TWO_SIDED_LIGHTING);
//STRIP001  if( eState != SFX_ITEM_DONTCARE )
//STRIP001  {
//STRIP001      BOOL bValue = ((const Svx3DTwoSidedLightingItem&)rAttrs.Get(SDRATTR_3DSCENE_TWO_SIDED_LIGHTING)).GetValue();
//STRIP001      if( bValue != aBtnTwoSidedLighting.IsChecked() )
//STRIP001      {
//STRIP001          aBtnTwoSidedLighting.Check( bValue );
//STRIP001          bUpdate = TRUE;
//STRIP001      }
//STRIP001      else if( aBtnTwoSidedLighting.GetState() == STATE_DONTKNOW )
//STRIP001          aBtnTwoSidedLighting.Check( bValue );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      if( aBtnTwoSidedLighting.GetState() != STATE_DONTKNOW )
//STRIP001      {
//STRIP001          aBtnTwoSidedLighting.SetState( STATE_DONTKNOW );
//STRIP001          bUpdate = TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001 // Darstellung
//STRIP001  // Shademode
//STRIP001  eState = rAttrs.GetItemState(SDRATTR_3DSCENE_SHADE_MODE);
//STRIP001  if( eState != SFX_ITEM_DONTCARE )
//STRIP001  {
//STRIP001      UINT16 nValue = ((const Svx3DShadeModeItem&)rAttrs.Get(SDRATTR_3DSCENE_SHADE_MODE)).GetValue();
//STRIP001      if( nValue != aLbShademode.GetSelectEntryPos() )
//STRIP001      {
//STRIP001          aLbShademode.SelectEntryPos( nValue );
//STRIP001          bUpdate = TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      if( aLbShademode.GetSelectEntryCount() != 0 )
//STRIP001      {
//STRIP001          aLbShademode.SetNoSelection();
//STRIP001          bUpdate = TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  // 3D-Shatten
//STRIP001  eState = rAttrs.GetItemState(SDRATTR_3DOBJ_SHADOW_3D);
//STRIP001  if( eState != SFX_ITEM_DONTCARE )
//STRIP001  {
//STRIP001      BOOL bValue = ((const Svx3DShadow3DItem&)rAttrs.Get(SDRATTR_3DOBJ_SHADOW_3D)).GetValue();
//STRIP001      if( bValue != aBtnShadow3d.IsChecked() )
//STRIP001      {
//STRIP001          aBtnShadow3d.Check( bValue );
//STRIP001          aFtSlant.Enable( bValue );
//STRIP001          aMtrSlant.Enable( bValue );
//STRIP001          bUpdate = TRUE;
//STRIP001      }
//STRIP001      else if( aBtnShadow3d.GetState() == STATE_DONTKNOW )
//STRIP001          aBtnShadow3d.Check( bValue );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      if( aBtnShadow3d.GetState() != STATE_DONTKNOW )
//STRIP001      {
//STRIP001          aBtnShadow3d.SetState( STATE_DONTKNOW );
//STRIP001          bUpdate = TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  // Neigung (Schatten)
//STRIP001  eState = rAttrs.GetItemState(SDRATTR_3DSCENE_SHADOW_SLANT);
//STRIP001  if( eState != SFX_ITEM_DONTCARE )
//STRIP001  {
//STRIP001      UINT16 nValue = ((const Svx3DShadowSlantItem&)rAttrs.Get(SDRATTR_3DSCENE_SHADOW_SLANT)).GetValue();
//STRIP001      if( nValue != aMtrSlant.GetValue() )
//STRIP001      {
//STRIP001          aMtrSlant.SetValue( nValue );
//STRIP001          bUpdate = TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      if( !aMtrSlant.IsEmptyFieldValue() )
//STRIP001      {
//STRIP001          aMtrSlant.SetEmptyFieldValue();
//STRIP001          bUpdate = TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  // Distanz
//STRIP001  eState = rAttrs.GetItemState(SDRATTR_3DSCENE_DISTANCE);
//STRIP001  if( eState != SFX_ITEM_DONTCARE )
//STRIP001  {
//STRIP001      UINT32 nValue = ((const Svx3DDistanceItem&)rAttrs.Get(SDRATTR_3DSCENE_DISTANCE)).GetValue();
//STRIP001      UINT32 nValue2 = GetCoreValue( aMtrDistance, ePoolUnit );
//STRIP001      if( nValue != nValue2 )
//STRIP001      {
//STRIP001          if( eFUnit != aMtrDistance.GetUnit() )
//STRIP001              SetFieldUnit( aMtrDistance, eFUnit );
//STRIP001
//STRIP001          SetMetricValue( aMtrDistance, nValue, ePoolUnit );
//STRIP001          bUpdate = TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      if( !aMtrDepth.IsEmptyFieldValue() )
//STRIP001      {
//STRIP001          aMtrDepth.SetEmptyFieldValue();
//STRIP001          bUpdate = TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  // Brennweite
//STRIP001  eState = rAttrs.GetItemState(SDRATTR_3DSCENE_FOCAL_LENGTH);
//STRIP001  if( eState != SFX_ITEM_DONTCARE )
//STRIP001  {
//STRIP001      UINT32 nValue = ((const Svx3DFocalLengthItem&)rAttrs.Get(SDRATTR_3DSCENE_FOCAL_LENGTH)).GetValue();
//STRIP001      UINT32 nValue2 = GetCoreValue( aMtrFocalLength, ePoolUnit );
//STRIP001      if( nValue != nValue2 )
//STRIP001      {
//STRIP001          if( eFUnit != aMtrFocalLength.GetUnit() )
//STRIP001              SetFieldUnit( aMtrFocalLength, eFUnit );
//STRIP001
//STRIP001          SetMetricValue( aMtrFocalLength, nValue, ePoolUnit );
//STRIP001          bUpdate = TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      if( !aMtrFocalLength.IsEmptyFieldValue() )
//STRIP001      {
//STRIP001          aMtrFocalLength.SetEmptyFieldValue();
//STRIP001          bUpdate = TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001 // Beleuchtung
//STRIP001  Color aColor;
//STRIP001  Vector3D aVector;
//STRIP001  // Licht 1 (Farbe)
//STRIP001  eState = rAttrs.GetItemState(SDRATTR_3DSCENE_LIGHTCOLOR_1);
//STRIP001  if( eState != SFX_ITEM_DONTCARE )
//STRIP001  {
//STRIP001      aColor = ((const Svx3DLightcolor1Item&)rAttrs.Get(SDRATTR_3DSCENE_LIGHTCOLOR_1)).GetValue();
//STRIP001      ColorLB* pLb = &aLbLight1;
//STRIP001      if( aColor != pLb->GetSelectEntryColor() )
//STRIP001      {
//STRIP001          LBSelectColor( pLb, aColor );
//STRIP001
//STRIP001          pLightGroup->SetIntensity( aColor, Base3DMaterialDiffuse, Base3DLight0 );
//STRIP001          bUpdate = TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      if( aLbLight1.GetSelectEntryCount() != 0 )
//STRIP001      {
//STRIP001          aLbLight1.SetNoSelection();
//STRIP001          bUpdate = TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001  // Licht 1 (an/aus)
//STRIP001  eState = rAttrs.GetItemState(SDRATTR_3DSCENE_LIGHTON_1);
//STRIP001  if( eState != SFX_ITEM_DONTCARE )
//STRIP001  {
//STRIP001      bool bOn = ((const Svx3DLightOnOff1Item&)rAttrs.Get(SDRATTR_3DSCENE_LIGHTON_1)).GetValue() != 0;
//STRIP001      if( ( bOn && !GetUILightState( aBtnLight1 )) ||
//STRIP001          ( !bOn && GetUILightState( aBtnLight1 )) )
//STRIP001      {
//STRIP001          SetUILightState( aBtnLight1, bOn );
//STRIP001          pLightGroup->Enable( bOn, Base3DLight0 );
//STRIP001          bUpdate = TRUE;
//STRIP001      }
//STRIP001      if( aBtnLight1.GetState() == STATE_DONTKNOW )
//STRIP001          aBtnLight1.Check( aBtnLight1.IsChecked() );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      if( aBtnLight1.GetState() != STATE_DONTKNOW )
//STRIP001      {
//STRIP001          aBtnLight1.SetState( STATE_DONTKNOW );
//STRIP001          bUpdate = TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001  // Licht 1 (Richtung)
//STRIP001  eState = rAttrs.GetItemState(SDRATTR_3DSCENE_LIGHTDIRECTION_1);
//STRIP001  if( eState != SFX_ITEM_DONTCARE )
//STRIP001  {
//STRIP001      aVector = ((const Svx3DLightDirection1Item&)rAttrs.Get(SDRATTR_3DSCENE_LIGHTDIRECTION_1)).GetValue();
//STRIP001      Vector3D aVector2 = pLightGroup->GetDirection( Base3DLight0 );
//STRIP001      if( aVector != aVector2 )
//STRIP001      {
//STRIP001          pLightGroup->SetDirection( aVector, Base3DLight0 );
//STRIP001          bUpdate = TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  // Licht 2 (Farbe)
//STRIP001  eState = rAttrs.GetItemState(SDRATTR_3DSCENE_LIGHTCOLOR_2);
//STRIP001  if( eState != SFX_ITEM_DONTCARE )
//STRIP001  {
//STRIP001      aColor = ((const Svx3DLightcolor2Item&)rAttrs.Get(SDRATTR_3DSCENE_LIGHTCOLOR_2)).GetValue();
//STRIP001      ColorLB* pLb = &aLbLight2;
//STRIP001      if( aColor != pLb->GetSelectEntryColor() )
//STRIP001      {
//STRIP001          LBSelectColor( pLb, aColor );
//STRIP001
//STRIP001          pLightGroup->SetIntensity( aColor, Base3DMaterialDiffuse, Base3DLight1 );
//STRIP001          bUpdate = TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      if( aLbLight2.GetSelectEntryCount() != 0 )
//STRIP001      {
//STRIP001          aLbLight2.SetNoSelection();
//STRIP001          bUpdate = TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001  // Licht 2 (an/aus)
//STRIP001  eState = rAttrs.GetItemState(SDRATTR_3DSCENE_LIGHTON_2);
//STRIP001  if( eState != SFX_ITEM_DONTCARE )
//STRIP001  {
//STRIP001      bool bOn = ((const Svx3DLightOnOff2Item&)rAttrs.Get(SDRATTR_3DSCENE_LIGHTON_2)).GetValue() != 0;
//STRIP001      if( ( bOn && !GetUILightState( aBtnLight2 )) ||
//STRIP001          ( !bOn && GetUILightState( aBtnLight2 )) )
//STRIP001      {
//STRIP001          SetUILightState( aBtnLight2, bOn );
//STRIP001          pLightGroup->Enable( bOn, Base3DLight1 );
//STRIP001          bUpdate = TRUE;
//STRIP001      }
//STRIP001      if( aBtnLight2.GetState() == STATE_DONTKNOW )
//STRIP001          aBtnLight2.Check( aBtnLight2.IsChecked() );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      if( aBtnLight2.GetState() != STATE_DONTKNOW )
//STRIP001      {
//STRIP001          aBtnLight2.SetState( STATE_DONTKNOW );
//STRIP001          bUpdate = TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001  // Licht 2 (Richtung)
//STRIP001  eState = rAttrs.GetItemState(SDRATTR_3DSCENE_LIGHTDIRECTION_2);
//STRIP001  if( eState != SFX_ITEM_DONTCARE )
//STRIP001  {
//STRIP001      aVector = ((const Svx3DLightDirection2Item&)rAttrs.Get(SDRATTR_3DSCENE_LIGHTDIRECTION_2)).GetValue();
//STRIP001      Vector3D aVector2 = pLightGroup->GetDirection( Base3DLight1 );
//STRIP001      if( aVector != aVector2 )
//STRIP001      {
//STRIP001          pLightGroup->SetDirection( aVector, Base3DLight1 );
//STRIP001          bUpdate = TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  // Licht 3 (Farbe)
//STRIP001  eState = rAttrs.GetItemState(SDRATTR_3DSCENE_LIGHTCOLOR_3);
//STRIP001  if( eState != SFX_ITEM_DONTCARE )
//STRIP001  {
//STRIP001      aColor = ((const Svx3DLightcolor3Item&)rAttrs.Get(SDRATTR_3DSCENE_LIGHTCOLOR_3)).GetValue();
//STRIP001      ColorLB* pLb = &aLbLight3;
//STRIP001      if( aColor != pLb->GetSelectEntryColor() )
//STRIP001      {
//STRIP001          LBSelectColor( pLb, aColor );
//STRIP001          pLightGroup->SetIntensity( aColor, Base3DMaterialDiffuse, Base3DLight2 );
//STRIP001
//STRIP001          bUpdate = TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      if( aLbLight3.GetSelectEntryCount() != 0 )
//STRIP001      {
//STRIP001          aLbLight3.SetNoSelection();
//STRIP001          bUpdate = TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001  // Licht 3 (an/aus)
//STRIP001  eState = rAttrs.GetItemState(SDRATTR_3DSCENE_LIGHTON_3);
//STRIP001  if( eState != SFX_ITEM_DONTCARE )
//STRIP001  {
//STRIP001      bool bOn = ((const Svx3DLightOnOff3Item&)rAttrs.Get(SDRATTR_3DSCENE_LIGHTON_3)).GetValue() != 0;
//STRIP001      if( ( bOn && !GetUILightState( aBtnLight3)) ||
//STRIP001          ( !bOn && GetUILightState( aBtnLight3)) )
//STRIP001      {
//STRIP001          SetUILightState( aBtnLight3, bOn );
//STRIP001          pLightGroup->Enable( bOn, Base3DLight2 );
//STRIP001          bUpdate = TRUE;
//STRIP001      }
//STRIP001      if( aBtnLight3.GetState() == STATE_DONTKNOW )
//STRIP001          aBtnLight3.Check( aBtnLight3.IsChecked() );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      if( aBtnLight3.GetState() != STATE_DONTKNOW )
//STRIP001      {
//STRIP001          aBtnLight3.SetState( STATE_DONTKNOW );
//STRIP001          bUpdate = TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001  // Licht 3 (Richtung)
//STRIP001  eState = rAttrs.GetItemState(SDRATTR_3DSCENE_LIGHTDIRECTION_3);
//STRIP001  if( eState != SFX_ITEM_DONTCARE )
//STRIP001  {
//STRIP001      aVector = ((const Svx3DLightDirection3Item&)rAttrs.Get(SDRATTR_3DSCENE_LIGHTDIRECTION_3)).GetValue();
//STRIP001      Vector3D aVector2 = pLightGroup->GetDirection( Base3DLight2 );
//STRIP001      if( aVector != aVector2 )
//STRIP001      {
//STRIP001          pLightGroup->SetDirection( aVector, Base3DLight2 );
//STRIP001          bUpdate = TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  // Licht 4 (Farbe)
//STRIP001  eState = rAttrs.GetItemState(SDRATTR_3DSCENE_LIGHTCOLOR_4);
//STRIP001  if( eState != SFX_ITEM_DONTCARE )
//STRIP001  {
//STRIP001      aColor = ((const Svx3DLightcolor4Item&)rAttrs.Get(SDRATTR_3DSCENE_LIGHTCOLOR_4)).GetValue();
//STRIP001      ColorLB* pLb = &aLbLight4;
//STRIP001      if( aColor != pLb->GetSelectEntryColor() )
//STRIP001      {
//STRIP001          LBSelectColor( pLb, aColor );
//STRIP001          pLightGroup->SetIntensity( aColor, Base3DMaterialDiffuse, Base3DLight3 );
//STRIP001
//STRIP001          bUpdate = TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      if( aLbLight4.GetSelectEntryCount() != 0 )
//STRIP001      {
//STRIP001          aLbLight4.SetNoSelection();
//STRIP001          bUpdate = TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001  // Licht 4 (an/aus)
//STRIP001  eState = rAttrs.GetItemState(SDRATTR_3DSCENE_LIGHTON_4);
//STRIP001  if( eState != SFX_ITEM_DONTCARE )
//STRIP001  {
//STRIP001      bool bOn = ((const Svx3DLightOnOff4Item&)rAttrs.Get(SDRATTR_3DSCENE_LIGHTON_4)).GetValue() != 0;
//STRIP001      if( ( bOn && !GetUILightState( aBtnLight4 )) ||
//STRIP001          ( !bOn && GetUILightState( aBtnLight4 )) )
//STRIP001      {
//STRIP001          SetUILightState( aBtnLight4, bOn );
//STRIP001          pLightGroup->Enable( bOn, Base3DLight3 );
//STRIP001          bUpdate = TRUE;
//STRIP001      }
//STRIP001      if( aBtnLight4.GetState() == STATE_DONTKNOW )
//STRIP001          aBtnLight4.Check( aBtnLight4.IsChecked() );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      if( aBtnLight4.GetState() != STATE_DONTKNOW )
//STRIP001      {
//STRIP001          aBtnLight4.SetState( STATE_DONTKNOW );
//STRIP001          bUpdate = TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001  // Licht 4 (Richtung)
//STRIP001  eState = rAttrs.GetItemState(SDRATTR_3DSCENE_LIGHTDIRECTION_4);
//STRIP001  if( eState != SFX_ITEM_DONTCARE )
//STRIP001  {
//STRIP001      aVector = ((const Svx3DLightDirection4Item&)rAttrs.Get(SDRATTR_3DSCENE_LIGHTDIRECTION_4)).GetValue();
//STRIP001      Vector3D aVector2 = pLightGroup->GetDirection( Base3DLight3 );
//STRIP001      if( aVector != aVector2 )
//STRIP001      {
//STRIP001          pLightGroup->SetDirection( aVector, Base3DLight3 );
//STRIP001          bUpdate = TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  // Licht 5 (Farbe)
//STRIP001  eState = rAttrs.GetItemState(SDRATTR_3DSCENE_LIGHTCOLOR_5);
//STRIP001  if( eState != SFX_ITEM_DONTCARE )
//STRIP001  {
//STRIP001      aColor = ((const Svx3DLightcolor5Item&)rAttrs.Get(SDRATTR_3DSCENE_LIGHTCOLOR_5)).GetValue();
//STRIP001      ColorLB* pLb = &aLbLight5;
//STRIP001      if( aColor != pLb->GetSelectEntryColor() )
//STRIP001      {
//STRIP001          LBSelectColor( pLb, aColor );
//STRIP001          pLightGroup->SetIntensity( aColor, Base3DMaterialDiffuse, Base3DLight4 );
//STRIP001
//STRIP001          bUpdate = TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      if( aLbLight5.GetSelectEntryCount() != 0 )
//STRIP001      {
//STRIP001          aLbLight5.SetNoSelection();
//STRIP001          bUpdate = TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001  // Licht 5 (an/aus)
//STRIP001  eState = rAttrs.GetItemState(SDRATTR_3DSCENE_LIGHTON_5);
//STRIP001  if( eState != SFX_ITEM_DONTCARE )
//STRIP001  {
//STRIP001      bool bOn = ((const Svx3DLightOnOff5Item&)rAttrs.Get(SDRATTR_3DSCENE_LIGHTON_5)).GetValue() != 0;
//STRIP001      if( ( bOn && !GetUILightState( aBtnLight5 )) ||
//STRIP001          ( !bOn && GetUILightState( aBtnLight5 )) )
//STRIP001      {
//STRIP001          SetUILightState( aBtnLight5, bOn );
//STRIP001          pLightGroup->Enable( bOn, Base3DLight4 );
//STRIP001          bUpdate = TRUE;
//STRIP001      }
//STRIP001      if( aBtnLight5.GetState() == STATE_DONTKNOW )
//STRIP001          aBtnLight5.Check( aBtnLight5.IsChecked() );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      if( aBtnLight5.GetState() != STATE_DONTKNOW )
//STRIP001      {
//STRIP001          aBtnLight5.SetState( STATE_DONTKNOW );
//STRIP001          bUpdate = TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001  // Licht 5 (Richtung)
//STRIP001  eState = rAttrs.GetItemState(SDRATTR_3DSCENE_LIGHTDIRECTION_5);
//STRIP001  if( eState != SFX_ITEM_DONTCARE )
//STRIP001  {
//STRIP001      aVector = ((const Svx3DLightDirection5Item&)rAttrs.Get(SDRATTR_3DSCENE_LIGHTDIRECTION_5)).GetValue();
//STRIP001      Vector3D aVector2 = pLightGroup->GetDirection( Base3DLight4 );
//STRIP001      if( aVector != aVector2 )
//STRIP001      {
//STRIP001          pLightGroup->SetDirection( aVector, Base3DLight4 );
//STRIP001          bUpdate = TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  // Licht 6 (Farbe)
//STRIP001  eState = rAttrs.GetItemState(SDRATTR_3DSCENE_LIGHTCOLOR_6);
//STRIP001  if( eState != SFX_ITEM_DONTCARE )
//STRIP001  {
//STRIP001      aColor = ((const Svx3DLightcolor6Item&)rAttrs.Get(SDRATTR_3DSCENE_LIGHTCOLOR_6)).GetValue();
//STRIP001      ColorLB* pLb = &aLbLight6;
//STRIP001      if( aColor != pLb->GetSelectEntryColor() )
//STRIP001      {
//STRIP001          LBSelectColor( pLb, aColor );
//STRIP001          pLightGroup->SetIntensity( aColor, Base3DMaterialDiffuse, Base3DLight5 );
//STRIP001
//STRIP001          bUpdate = TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      if( aLbLight6.GetSelectEntryCount() != 0 )
//STRIP001      {
//STRIP001          aLbLight6.SetNoSelection();
//STRIP001          bUpdate = TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001  // Licht 6 (an/aus)
//STRIP001  eState = rAttrs.GetItemState(SDRATTR_3DSCENE_LIGHTON_6);
//STRIP001  if( eState != SFX_ITEM_DONTCARE )
//STRIP001  {
//STRIP001      bool bOn = ((const Svx3DLightOnOff6Item&)rAttrs.Get(SDRATTR_3DSCENE_LIGHTON_6)).GetValue() != 0;
//STRIP001      if( ( bOn && !GetUILightState( aBtnLight6 )) ||
//STRIP001          ( !bOn && GetUILightState( aBtnLight6 )) )
//STRIP001      {
//STRIP001          SetUILightState( aBtnLight6, bOn );
//STRIP001          pLightGroup->Enable( bOn, Base3DLight5 );
//STRIP001          bUpdate = TRUE;
//STRIP001      }
//STRIP001      if( aBtnLight6.GetState() == STATE_DONTKNOW )
//STRIP001          aBtnLight6.Check( aBtnLight6.IsChecked() );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      if( aBtnLight6.GetState() != STATE_DONTKNOW )
//STRIP001      {
//STRIP001          aBtnLight6.SetState( STATE_DONTKNOW );
//STRIP001          bUpdate = TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001  // Licht 6 (Richtung)
//STRIP001  eState = rAttrs.GetItemState(SDRATTR_3DSCENE_LIGHTDIRECTION_6);
//STRIP001  if( eState != SFX_ITEM_DONTCARE )
//STRIP001  {
//STRIP001      aVector = ((const Svx3DLightDirection6Item&)rAttrs.Get(SDRATTR_3DSCENE_LIGHTDIRECTION_6)).GetValue();
//STRIP001      Vector3D aVector2 = pLightGroup->GetDirection( Base3DLight5 );
//STRIP001      if( aVector != aVector2 )
//STRIP001      {
//STRIP001          pLightGroup->SetDirection( aVector, Base3DLight5 );
//STRIP001          bUpdate = TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  // Licht 7 (Farbe)
//STRIP001  eState = rAttrs.GetItemState(SDRATTR_3DSCENE_LIGHTCOLOR_7);
//STRIP001  if( eState != SFX_ITEM_DONTCARE )
//STRIP001  {
//STRIP001      aColor = ((const Svx3DLightcolor7Item&)rAttrs.Get(SDRATTR_3DSCENE_LIGHTCOLOR_7)).GetValue();
//STRIP001      ColorLB* pLb = &aLbLight7;
//STRIP001      if( aColor != pLb->GetSelectEntryColor() )
//STRIP001      {
//STRIP001          LBSelectColor( pLb, aColor );
//STRIP001          pLightGroup->SetIntensity( aColor, Base3DMaterialDiffuse, Base3DLight6 );
//STRIP001
//STRIP001          bUpdate = TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      if( aLbLight7.GetSelectEntryCount() != 0 )
//STRIP001      {
//STRIP001          aLbLight7.SetNoSelection();
//STRIP001          bUpdate = TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001  // Licht 7 (an/aus)
//STRIP001  eState = rAttrs.GetItemState(SDRATTR_3DSCENE_LIGHTON_7);
//STRIP001  if( eState != SFX_ITEM_DONTCARE )
//STRIP001  {
//STRIP001      bool bOn = ((const Svx3DLightOnOff7Item&)rAttrs.Get(SDRATTR_3DSCENE_LIGHTON_7)).GetValue() != 0;
//STRIP001      if( ( bOn && !GetUILightState( aBtnLight7 )) ||
//STRIP001          ( !bOn && GetUILightState( aBtnLight7 )) )
//STRIP001      {
//STRIP001          SetUILightState( aBtnLight7 , bOn );
//STRIP001          pLightGroup->Enable( bOn, Base3DLight6 );
//STRIP001          bUpdate = TRUE;
//STRIP001      }
//STRIP001      if( aBtnLight7.GetState() == STATE_DONTKNOW )
//STRIP001          aBtnLight7.Check( aBtnLight7.IsChecked() );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      if( aBtnLight7.GetState() != STATE_DONTKNOW )
//STRIP001      {
//STRIP001          aBtnLight7.SetState( STATE_DONTKNOW );
//STRIP001          bUpdate = TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001  // Licht 7 (Richtung)
//STRIP001  eState = rAttrs.GetItemState(SDRATTR_3DSCENE_LIGHTDIRECTION_7);
//STRIP001  if( eState != SFX_ITEM_DONTCARE )
//STRIP001  {
//STRIP001      aVector = ((const Svx3DLightDirection7Item&)rAttrs.Get(SDRATTR_3DSCENE_LIGHTDIRECTION_7)).GetValue();
//STRIP001      Vector3D aVector2 = pLightGroup->GetDirection( Base3DLight6 );
//STRIP001      if( aVector != aVector2 )
//STRIP001      {
//STRIP001          pLightGroup->SetDirection( aVector, Base3DLight6 );
//STRIP001          bUpdate = TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  // Licht 8 (Farbe)
//STRIP001  eState = rAttrs.GetItemState(SDRATTR_3DSCENE_LIGHTCOLOR_8);
//STRIP001  if( eState != SFX_ITEM_DONTCARE )
//STRIP001  {
//STRIP001      aColor = ((const Svx3DLightcolor8Item&)rAttrs.Get(SDRATTR_3DSCENE_LIGHTCOLOR_8)).GetValue();
//STRIP001      ColorLB* pLb = &aLbLight8;
//STRIP001      if( aColor != pLb->GetSelectEntryColor() )
//STRIP001      {
//STRIP001          LBSelectColor( pLb, aColor );
//STRIP001          pLightGroup->SetIntensity( aColor, Base3DMaterialDiffuse, Base3DLight7 );
//STRIP001
//STRIP001          bUpdate = TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      if( aLbLight8.GetSelectEntryCount() != 0 )
//STRIP001      {
//STRIP001          aLbLight8.SetNoSelection();
//STRIP001          bUpdate = TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001  // Licht 8 (an/aus)
//STRIP001  eState = rAttrs.GetItemState(SDRATTR_3DSCENE_LIGHTON_8);
//STRIP001  if( eState != SFX_ITEM_DONTCARE )
//STRIP001  {
//STRIP001      bool bOn = ((const Svx3DLightOnOff8Item&)rAttrs.Get(SDRATTR_3DSCENE_LIGHTON_8)).GetValue() != 0;
//STRIP001      if( ( bOn && !GetUILightState( aBtnLight8 )) ||
//STRIP001          ( !bOn && GetUILightState( aBtnLight8 )) )
//STRIP001      {
//STRIP001          SetUILightState( aBtnLight8, bOn );
//STRIP001          pLightGroup->Enable( bOn, Base3DLight7 );
//STRIP001          bUpdate = TRUE;
//STRIP001      }
//STRIP001      if( aBtnLight8.GetState() == STATE_DONTKNOW )
//STRIP001          aBtnLight8.Check( aBtnLight8.IsChecked() );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      if( aBtnLight8.GetState() != STATE_DONTKNOW )
//STRIP001      {
//STRIP001          aBtnLight8.SetState( STATE_DONTKNOW );
//STRIP001          bUpdate = TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001  // Licht 8 (Richtung)
//STRIP001  eState = rAttrs.GetItemState(SDRATTR_3DSCENE_LIGHTDIRECTION_8);
//STRIP001  if( eState != SFX_ITEM_DONTCARE )
//STRIP001  {
//STRIP001      aVector = ((const Svx3DLightDirection8Item&)rAttrs.Get(SDRATTR_3DSCENE_LIGHTDIRECTION_8)).GetValue();
//STRIP001      Vector3D aVector2 = pLightGroup->GetDirection( Base3DLight7 );
//STRIP001      if( aVector != aVector2 )
//STRIP001      {
//STRIP001          pLightGroup->SetDirection( aVector, Base3DLight7 );
//STRIP001          bUpdate = TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  // Umgebungslicht
//STRIP001  eState = rAttrs.GetItemState(SDRATTR_3DSCENE_AMBIENTCOLOR);
//STRIP001  if( eState != SFX_ITEM_DONTCARE )
//STRIP001  {
//STRIP001      aColor = ((const Svx3DAmbientcolorItem&)rAttrs.Get(SDRATTR_3DSCENE_AMBIENTCOLOR)).GetValue();
//STRIP001      ColorLB* pLb = &aLbAmbientlight;
//STRIP001      if( aColor != pLb->GetSelectEntryColor() )
//STRIP001      {
//STRIP001          LBSelectColor( pLb, aColor );
//STRIP001          pLightGroup->SetGlobalAmbientLight( aColor );
//STRIP001
//STRIP001          bUpdate = TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      if( aLbAmbientlight.GetSelectEntryCount() != 0 )
//STRIP001      {
//STRIP001          aLbAmbientlight.SetNoSelection();
//STRIP001          bUpdate = TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001
//STRIP001 // Texturen
//STRIP001  // Art
//STRIP001  if( bBitmap )
//STRIP001  {
//STRIP001      eState = rAttrs.GetItemState(SDRATTR_3DOBJ_TEXTURE_KIND);
//STRIP001      if( eState != SFX_ITEM_DONTCARE )
//STRIP001      {
//STRIP001          UINT16 nValue = ((const Svx3DTextureKindItem&)rAttrs.Get(SDRATTR_3DOBJ_TEXTURE_KIND)).GetValue();
//STRIP001
//STRIP001          if( ( !aBtnTexLuminance.IsChecked() && nValue == 1 ) ||
//STRIP001              ( !aBtnTexColor.IsChecked() && nValue == 3 ) )
//STRIP001          {
//STRIP001              aBtnTexLuminance.Check( nValue == 1 );
//STRIP001              aBtnTexColor.Check( nValue == 3 );
//STRIP001              bUpdate = TRUE;
//STRIP001          }
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          if( aBtnTexLuminance.IsChecked() ||
//STRIP001              aBtnTexColor.IsChecked() )
//STRIP001          {
//STRIP001              aBtnTexLuminance.Check( FALSE );
//STRIP001              aBtnTexColor.Check( FALSE );
//STRIP001              bUpdate = TRUE;
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      // Modus
//STRIP001      eState = rAttrs.GetItemState(SDRATTR_3DOBJ_TEXTURE_MODE);
//STRIP001      if( eState != SFX_ITEM_DONTCARE )
//STRIP001      {
//STRIP001          UINT16 nValue = ((const Svx3DTextureModeItem&)rAttrs.Get(SDRATTR_3DOBJ_TEXTURE_MODE)).GetValue();
//STRIP001
//STRIP001          if( ( !aBtnTexReplace.IsChecked() && nValue == 1 ) ||
//STRIP001              ( !aBtnTexModulate.IsChecked() && nValue == 2 ) )
//STRIP001          {
//STRIP001              aBtnTexReplace.Check( nValue == 1 );
//STRIP001              aBtnTexModulate.Check( nValue == 2 );
//STRIP001              //aBtnTexBlend.Check( nValue == 2 );
//STRIP001              bUpdate = TRUE;
//STRIP001          }
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          if( aBtnTexReplace.IsChecked() ||
//STRIP001              aBtnTexModulate.IsChecked() )
//STRIP001          {
//STRIP001              aBtnTexReplace.Check( FALSE );
//STRIP001              aBtnTexModulate.Check( FALSE );
//STRIP001              //aBtnTexBlend.Check( FALSE );
//STRIP001              bUpdate = TRUE;
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      // Projektion X
//STRIP001      eState = rAttrs.GetItemState(SDRATTR_3DOBJ_TEXTURE_PROJ_X);
//STRIP001      if( eState != SFX_ITEM_DONTCARE )
//STRIP001      {
//STRIP001          UINT16 nValue = ((const Svx3DTextureProjectionXItem&)rAttrs.Get(SDRATTR_3DOBJ_TEXTURE_PROJ_X)).GetValue();
//STRIP001
//STRIP001          if( ( !aBtnTexObjectX.IsChecked() && nValue == 0 ) ||
//STRIP001              ( !aBtnTexParallelX.IsChecked() && nValue == 1 ) ||
//STRIP001              ( !aBtnTexCircleX.IsChecked() && nValue == 2 ) )
//STRIP001          {
//STRIP001              aBtnTexObjectX.Check( nValue == 0 );
//STRIP001              aBtnTexParallelX.Check( nValue == 1 );
//STRIP001              aBtnTexCircleX.Check( nValue == 2 );
//STRIP001              bUpdate = TRUE;
//STRIP001          }
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          if( aBtnTexObjectX.IsChecked() ||
//STRIP001              aBtnTexParallelX.IsChecked() ||
//STRIP001              aBtnTexCircleX.IsChecked() )
//STRIP001          {
//STRIP001              aBtnTexObjectX.Check( FALSE );
//STRIP001              aBtnTexParallelX.Check( FALSE );
//STRIP001              aBtnTexCircleX.Check( FALSE );
//STRIP001              bUpdate = TRUE;
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      // Projektion Y
//STRIP001      eState = rAttrs.GetItemState(SDRATTR_3DOBJ_TEXTURE_PROJ_Y);
//STRIP001      if( eState != SFX_ITEM_DONTCARE )
//STRIP001      {
//STRIP001          UINT16 nValue = ((const Svx3DTextureProjectionYItem&)rAttrs.Get(SDRATTR_3DOBJ_TEXTURE_PROJ_Y)).GetValue();
//STRIP001
//STRIP001          if( ( !aBtnTexObjectY.IsChecked() && nValue == 0 ) ||
//STRIP001              ( !aBtnTexParallelY.IsChecked() && nValue == 1 ) ||
//STRIP001              ( !aBtnTexCircleY.IsChecked() && nValue == 2 ) )
//STRIP001          {
//STRIP001              aBtnTexObjectY.Check( nValue == 0 );
//STRIP001              aBtnTexParallelY.Check( nValue == 1 );
//STRIP001              aBtnTexCircleY.Check( nValue == 2 );
//STRIP001              bUpdate = TRUE;
//STRIP001          }
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          if( aBtnTexObjectY.IsChecked() ||
//STRIP001              aBtnTexParallelY.IsChecked() ||
//STRIP001              aBtnTexCircleY.IsChecked() )
//STRIP001          {
//STRIP001              aBtnTexObjectY.Check( FALSE );
//STRIP001              aBtnTexParallelY.Check( FALSE );
//STRIP001              aBtnTexCircleY.Check( FALSE );
//STRIP001              bUpdate = TRUE;
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      // Filter
//STRIP001      eState = rAttrs.GetItemState(SDRATTR_3DOBJ_TEXTURE_FILTER);
//STRIP001      if( eState != SFX_ITEM_DONTCARE )
//STRIP001      {
//STRIP001          BOOL bValue = ((const Svx3DTextureFilterItem&)rAttrs.Get(SDRATTR_3DOBJ_TEXTURE_FILTER)).GetValue();
//STRIP001          if( bValue != aBtnTexFilter.IsChecked() )
//STRIP001          {
//STRIP001              aBtnTexFilter.Check( bValue );
//STRIP001              bUpdate = TRUE;
//STRIP001          }
//STRIP001          if( aBtnTexFilter.GetState() == STATE_DONTKNOW )
//STRIP001              aBtnTexFilter.Check( bValue );
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          if( aBtnTexFilter.GetState() != STATE_DONTKNOW )
//STRIP001          {
//STRIP001              aBtnTexFilter.SetState( STATE_DONTKNOW );
//STRIP001              bUpdate = TRUE;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001
//STRIP001 // Material
//STRIP001  // Favoriten
//STRIP001  //aLbMatFavorites.SelectEntryPos( 0 );
//STRIP001
//STRIP001  // Objektfarbe
//STRIP001  eState = rAttrs.GetItemState(XATTR_FILLCOLOR);
//STRIP001  if( eState != SFX_ITEM_DONTCARE )
//STRIP001  {
//STRIP001      aColor = ((const XFillColorItem&)rAttrs.Get(XATTR_FILLCOLOR)).GetValue();
//STRIP001      aCtlLightPreview.GetPreviewControl().SetMaterial( aColor, Base3DMaterialDiffuse );
//STRIP001      ColorLB* pLb = &aLbMatColor;
//STRIP001      if( aColor != pLb->GetSelectEntryColor() )
//STRIP001      {
//STRIP001          LBSelectColor( pLb, aColor );
//STRIP001          bUpdate = TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      if( aLbMatColor.GetSelectEntryCount() != 0 )
//STRIP001      {
//STRIP001          aLbMatColor.SetNoSelection();
//STRIP001          bUpdate = TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  // Slebstleuchtfarbe
//STRIP001  eState = rAttrs.GetItemState(SDRATTR_3DOBJ_MAT_EMISSION);
//STRIP001  if( eState != SFX_ITEM_DONTCARE )
//STRIP001  {
//STRIP001      aColor = ((const Svx3DMaterialEmissionItem&)rAttrs.Get(SDRATTR_3DOBJ_MAT_EMISSION)).GetValue();
//STRIP001      aCtlLightPreview.GetPreviewControl().SetMaterial( aColor, Base3DMaterialEmission );
//STRIP001      ColorLB* pLb = &aLbMatEmission;
//STRIP001      if( aColor != pLb->GetSelectEntryColor() )
//STRIP001      {
//STRIP001          LBSelectColor( pLb, aColor );
//STRIP001          bUpdate = TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      if( aLbMatEmission.GetSelectEntryCount() != 0 )
//STRIP001      {
//STRIP001          aLbMatEmission.SetNoSelection();
//STRIP001          bUpdate = TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  // Glanzpunkt
//STRIP001  eState = rAttrs.GetItemState(SDRATTR_3DOBJ_MAT_SPECULAR);
//STRIP001  if( eState != SFX_ITEM_DONTCARE )
//STRIP001  {
//STRIP001      aColor = ((const Svx3DMaterialSpecularItem&)rAttrs.Get(SDRATTR_3DOBJ_MAT_SPECULAR)).GetValue();
//STRIP001      aCtlLightPreview.GetPreviewControl().SetMaterial( aColor, Base3DMaterialSpecular );
//STRIP001      ColorLB* pLb = &aLbMatSpecular;
//STRIP001      if( aColor != pLb->GetSelectEntryColor() )
//STRIP001      {
//STRIP001          LBSelectColor( pLb, aColor );
//STRIP001          bUpdate = TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      if( aLbMatSpecular.GetSelectEntryCount() != 0 )
//STRIP001      {
//STRIP001          aLbMatSpecular.SetNoSelection();
//STRIP001          bUpdate = TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  // Glanzpunkt Intensitaet
//STRIP001  eState = rAttrs.GetItemState(SDRATTR_3DOBJ_MAT_SPECULAR_INTENSITY);
//STRIP001  if( eState != SFX_ITEM_DONTCARE )
//STRIP001  {
//STRIP001      UINT16 nValue = ((const Svx3DMaterialSpecularIntensityItem&)rAttrs.Get(SDRATTR_3DOBJ_MAT_SPECULAR_INTENSITY)).GetValue();
//STRIP001      aCtlLightPreview.GetPreviewControl().SetShininess( nValue );
//STRIP001      if( nValue != aMtrMatSpecularIntensity.GetValue() )
//STRIP001      {
//STRIP001          aMtrMatSpecularIntensity.SetValue( nValue );
//STRIP001          bUpdate = TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      if( !aMtrMatSpecularIntensity.IsEmptyFieldValue() )
//STRIP001      {
//STRIP001          aMtrMatSpecularIntensity.SetEmptyFieldValue();
//STRIP001          bUpdate = TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001
//STRIP001 // Sonstige
//STRIP001  // Perspektive
//STRIP001  eState = rAttrs.GetItemState(SDRATTR_3DSCENE_PERSPECTIVE);
//STRIP001  if( eState != SFX_ITEM_DONTCARE )
//STRIP001  {
//STRIP001      ProjectionType ePT = (ProjectionType)((const Svx3DPerspectiveItem&)rAttrs.Get(SDRATTR_3DSCENE_PERSPECTIVE)).GetValue();
//STRIP001      if( ( !aBtnPerspective.IsChecked() && ePT == PR_PERSPECTIVE ) ||
//STRIP001          ( aBtnPerspective.IsChecked() && ePT == PR_PARALLEL ) )
//STRIP001      {
//STRIP001          aBtnPerspective.Check( ePT == PR_PERSPECTIVE );
//STRIP001          bUpdate = TRUE;
//STRIP001      }
//STRIP001      if( aBtnPerspective.GetState() == STATE_DONTKNOW )
//STRIP001          aBtnPerspective.Check( ePT == PR_PERSPECTIVE );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      if( aBtnPerspective.GetState() != STATE_DONTKNOW )
//STRIP001      {
//STRIP001          aBtnPerspective.SetState( STATE_DONTKNOW );
//STRIP001          bUpdate = TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if( !bUpdate && !bOnly3DChanged )
//STRIP001  {
//STRIP001      // Eventuell sind aber die 2D-Attribute unterschiedlich. Vergleiche
//STRIP001      // diese und entscheide
//STRIP001
//STRIP001
//STRIP001      bUpdate = TRUE;
//STRIP001  }
//STRIP001
//STRIP001  if( bUpdate || bOnly3DChanged )
//STRIP001  {
//STRIP001      // Preview updaten
//STRIP001      aCtlLightPreview.GetPreviewControl().SetLightGroup( pLightGroup );
//STRIP001
//STRIP001      SfxItemSet aSet(rAttrs);
//STRIP001
//STRIP001      // set LineStyle hard to XLINE_NONE when it's not set so that
//STRIP001      // the default (XLINE_SOLID) is not used for 3d preview
//STRIP001      if(SFX_ITEM_SET != aSet.GetItemState(XATTR_LINESTYLE, FALSE))
//STRIP001          aSet.Put(XLineStyleItem(XLINE_NONE));
//STRIP001
//STRIP001      // set FillColor hard to WHITE when it's SFX_ITEM_DONTCARE so that
//STRIP001      // the default (Blue7) is not used for 3d preview
//STRIP001      if(SFX_ITEM_DONTCARE == aSet.GetItemState(XATTR_FILLCOLOR, FALSE))
//STRIP001          aSet.Put(XFillColorItem(String(), Color(COL_WHITE)));
//STRIP001
//STRIP001      aCtlPreview.Set3DAttributes(aSet);
//STRIP001  }
//STRIP001
//STRIP001  // handle state of converts possible
//STRIP001  aBtnConvertTo3D.Enable(pConvertTo3DItem->GetState());
//STRIP001  aBtnLatheObject.Enable(pConvertTo3DLatheItem->GetState());
//STRIP001 }

// -----------------------------------------------------------------------
//STRIP001 void Svx3DWin::GetAttr( SfxItemSet& rAttrs )
//STRIP001 {
//STRIP001  // 2D-Attribute und alle anderen holen
//STRIP001 //   rAttrs.Put( aCtlPreview.Get3DAttributes() );
//STRIP001
//STRIP001  // get remembered 2d attributes from the dialog
//STRIP001  if(mpRemember2DAttributes)
//STRIP001  {
//STRIP001      SfxWhichIter aIter(*mpRemember2DAttributes);
//STRIP001      sal_uInt16 nWhich(aIter.FirstWhich());
//STRIP001
//STRIP001      while(nWhich)
//STRIP001      {
//STRIP001          SfxItemState eState = mpRemember2DAttributes->GetItemState(nWhich, FALSE);
//STRIP001          if(SFX_ITEM_DONTCARE == eState)
//STRIP001              rAttrs.InvalidateItem(nWhich);
//STRIP001          else if(SFX_ITEM_SET == eState)
//STRIP001              rAttrs.Put(mpRemember2DAttributes->Get(nWhich, FALSE));
//STRIP001
//STRIP001          nWhich = aIter.NextWhich();
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001 // Sonstige, muss vorne stehen da auf allen Seiten
//STRIP001  // Perspektive
//STRIP001  if( aBtnPerspective.GetState() != STATE_DONTKNOW )
//STRIP001  {
//STRIP001      UINT16 nValue;
//STRIP001      if( aBtnPerspective.IsChecked() )
//STRIP001          nValue = PR_PERSPECTIVE;
//STRIP001      else
//STRIP001          nValue = PR_PARALLEL;
//STRIP001      rAttrs.Put(Svx3DPerspectiveItem(nValue));
//STRIP001  }
//STRIP001  else
//STRIP001      rAttrs.InvalidateItem(SDRATTR_3DSCENE_PERSPECTIVE);
//STRIP001
//STRIP001 // Geometrie
//STRIP001  // evtl. PoolUnit ermitteln (Falls dies in Update() nicht passiert ist)
//STRIP001  if( !mpImpl->pPool )
//STRIP001  {
//STRIP001      DBG_ERROR( "Kein Pool in GetAttr()! Evtl. inkompatibel zu drviewsi.cxx ?" );
//STRIP001      mpImpl->pPool = rAttrs.GetPool();
//STRIP001      DBG_ASSERT( mpImpl->pPool, "Wo ist der Pool?" );
//STRIP001      ePoolUnit = mpImpl->pPool->GetMetric( SID_ATTR_LINE_WIDTH );
//STRIP001
//STRIP001      eFUnit = GetModuleFieldUnit( &rAttrs );
//STRIP001  }
//STRIP001
//STRIP001  // Anzahl Segmente (horizontal)
//STRIP001  if( !aNumHorizontal.IsEmptyFieldValue() )
//STRIP001  {
//STRIP001      UINT32 nValue = aNumHorizontal.GetValue();
//STRIP001      rAttrs.Put(Svx3DHorizontalSegmentsItem(nValue));
//STRIP001  }
//STRIP001  else
//STRIP001      rAttrs.InvalidateItem(SDRATTR_3DOBJ_HORZ_SEGS);
//STRIP001
//STRIP001  // Anzahl Segmente (vertikal)
//STRIP001  if( !aNumVertical.IsEmptyFieldValue() )
//STRIP001  {
//STRIP001      UINT32 nValue = aNumVertical.GetValue();
//STRIP001      rAttrs.Put(Svx3DVerticalSegmentsItem(nValue));
//STRIP001  }
//STRIP001  else
//STRIP001      rAttrs.InvalidateItem(SDRATTR_3DOBJ_VERT_SEGS);
//STRIP001
//STRIP001  // Tiefe
//STRIP001  if( !aMtrDepth.IsEmptyFieldValue() )
//STRIP001  {
//STRIP001      UINT32 nValue = GetCoreValue( aMtrDepth, ePoolUnit );
//STRIP001      rAttrs.Put(Svx3DDepthItem(nValue));
//STRIP001  }
//STRIP001  else
//STRIP001      rAttrs.InvalidateItem(SDRATTR_3DOBJ_DEPTH);
//STRIP001
//STRIP001  // Doppelseitig
//STRIP001  TriState eState = aBtnDoubleSided.GetState();
//STRIP001  if( eState != STATE_DONTKNOW )
//STRIP001  {
//STRIP001      BOOL bValue = STATE_CHECK == eState;
//STRIP001      rAttrs.Put(Svx3DDoubleSidedItem(bValue));
//STRIP001  }
//STRIP001  else
//STRIP001      rAttrs.InvalidateItem(SDRATTR_3DOBJ_DOUBLE_SIDED);
//STRIP001
//STRIP001  // Kantenrundung
//STRIP001  if( !aMtrPercentDiagonal.IsEmptyFieldValue() )
//STRIP001  {
//STRIP001      UINT16 nValue = (UINT16) aMtrPercentDiagonal.GetValue();
//STRIP001      rAttrs.Put(Svx3DPercentDiagonalItem(nValue));
//STRIP001  }
//STRIP001  else
//STRIP001      rAttrs.InvalidateItem(SDRATTR_3DOBJ_PERCENT_DIAGONAL);
//STRIP001
//STRIP001  // Tiefenskalierung
//STRIP001  if( !aMtrBackscale.IsEmptyFieldValue() )
//STRIP001  {
//STRIP001      UINT16 nValue = (UINT16)aMtrBackscale.GetValue();
//STRIP001      rAttrs.Put(Svx3DBackscaleItem(nValue));
//STRIP001  }
//STRIP001  else
//STRIP001      rAttrs.InvalidateItem(SDRATTR_3DOBJ_BACKSCALE);
//STRIP001
//STRIP001  // Endwinkel
//STRIP001  if( !aMtrEndAngle.IsEmptyFieldValue() )
//STRIP001  {
//STRIP001      UINT16 nValue = (UINT16)aMtrEndAngle.GetValue();
//STRIP001      rAttrs.Put(Svx3DEndAngleItem(nValue));
//STRIP001  }
//STRIP001  else
//STRIP001      rAttrs.InvalidateItem(SDRATTR_3DOBJ_END_ANGLE);
//STRIP001
//STRIP001  // Normalentyp
//STRIP001  UINT16 nValue = 99;
//STRIP001  if( aBtnNormalsObj.IsChecked() )
//STRIP001      nValue = 0;
//STRIP001  else if( aBtnNormalsFlat.IsChecked() )
//STRIP001      nValue = 1;
//STRIP001  else if( aBtnNormalsSphere.IsChecked() )
//STRIP001      nValue = 2;
//STRIP001
//STRIP001  if( nValue <= 2 )
//STRIP001      rAttrs.Put(Svx3DNormalsKindItem(nValue));
//STRIP001  else
//STRIP001      rAttrs.InvalidateItem(SDRATTR_3DOBJ_NORMALS_KIND);
//STRIP001
//STRIP001  // Normalen invertieren
//STRIP001  eState = aBtnNormalsInvert.GetState();
//STRIP001  if( eState != STATE_DONTKNOW )
//STRIP001  {
//STRIP001      BOOL bValue = STATE_CHECK == eState;
//STRIP001      rAttrs.Put(Svx3DNormalsInvertItem(bValue));
//STRIP001  }
//STRIP001  else
//STRIP001      rAttrs.InvalidateItem(SDRATTR_3DOBJ_NORMALS_INVERT);
//STRIP001
//STRIP001  // 2-seitige Beleuchtung
//STRIP001  eState = aBtnTwoSidedLighting.GetState();
//STRIP001  if( eState != STATE_DONTKNOW )
//STRIP001  {
//STRIP001      BOOL bValue = STATE_CHECK == eState;
//STRIP001      rAttrs.Put(Svx3DTwoSidedLightingItem(bValue));
//STRIP001  }
//STRIP001  else
//STRIP001      rAttrs.InvalidateItem(SDRATTR_3DSCENE_TWO_SIDED_LIGHTING);
//STRIP001
//STRIP001 // Darstellung
//STRIP001  // Shademode
//STRIP001  if( aLbShademode.GetSelectEntryCount() )
//STRIP001  {
//STRIP001      nValue = aLbShademode.GetSelectEntryPos();
//STRIP001      rAttrs.Put(Svx3DShadeModeItem(nValue));
//STRIP001  }
//STRIP001  else
//STRIP001      rAttrs.InvalidateItem(SDRATTR_3DSCENE_SHADE_MODE);
//STRIP001
//STRIP001  // 3D-Shatten
//STRIP001  eState = aBtnShadow3d.GetState();
//STRIP001  if( eState != STATE_DONTKNOW )
//STRIP001  {
//STRIP001      BOOL bValue = STATE_CHECK == eState;
//STRIP001      rAttrs.Put(Svx3DShadow3DItem(bValue));
//STRIP001      rAttrs.Put(SdrShadowItem(bValue));
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      rAttrs.InvalidateItem(SDRATTR_3DOBJ_SHADOW_3D);
//STRIP001      rAttrs.InvalidateItem(SDRATTR_SHADOW);
//STRIP001  }
//STRIP001
//STRIP001  // Neigung (Schatten)
//STRIP001  if( !aMtrSlant.IsEmptyFieldValue() )
//STRIP001  {
//STRIP001      UINT16 nValue = (UINT16) aMtrSlant.GetValue();
//STRIP001      rAttrs.Put(Svx3DShadowSlantItem(nValue));
//STRIP001  }
//STRIP001  else
//STRIP001      rAttrs.InvalidateItem(SDRATTR_3DSCENE_SHADOW_SLANT);
//STRIP001
//STRIP001  // Distanz
//STRIP001  if( !aMtrDistance.IsEmptyFieldValue() )
//STRIP001  {
//STRIP001      UINT32 nValue = GetCoreValue( aMtrDistance, ePoolUnit );
//STRIP001      rAttrs.Put(Svx3DDistanceItem(nValue));
//STRIP001  }
//STRIP001  else
//STRIP001      rAttrs.InvalidateItem(SDRATTR_3DSCENE_DISTANCE);
//STRIP001
//STRIP001  // Brennweite
//STRIP001  if( !aMtrFocalLength.IsEmptyFieldValue() )
//STRIP001  {
//STRIP001      UINT32 nValue = GetCoreValue( aMtrFocalLength, ePoolUnit );
//STRIP001      rAttrs.Put(Svx3DFocalLengthItem(nValue));
//STRIP001  }
//STRIP001  else
//STRIP001      rAttrs.InvalidateItem(SDRATTR_3DSCENE_FOCAL_LENGTH);
//STRIP001
//STRIP001 // Beleuchtung
//STRIP001  Image aImg;
//STRIP001  Vector3D aVector;
//STRIP001  Color aColor;
//STRIP001  // Licht 1 Farbe
//STRIP001  if( aLbLight1.GetSelectEntryCount() )
//STRIP001  {
//STRIP001      aColor = aLbLight1.GetSelectEntryColor();
//STRIP001      rAttrs.Put(Svx3DLightcolor1Item(aColor));
//STRIP001  }
//STRIP001  else
//STRIP001      rAttrs.InvalidateItem(SDRATTR_3DSCENE_LIGHTCOLOR_1);
//STRIP001  // Licht 1 (an/aus)
//STRIP001  eState = aBtnLight1.GetState();
//STRIP001  if( eState != STATE_DONTKNOW )
//STRIP001  {
//STRIP001      BOOL bValue = GetUILightState( aBtnLight1 );
//STRIP001      rAttrs.Put(Svx3DLightOnOff1Item(bValue));
//STRIP001
//STRIP001      // Licht 1 (Richtung)
//STRIP001      if( bValue )
//STRIP001      {
//STRIP001          aVector = pLightGroup->GetDirection( Base3DLight0 );
//STRIP001          rAttrs.Put(Svx3DLightDirection1Item(aVector));
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001      rAttrs.InvalidateItem(SDRATTR_3DSCENE_LIGHTON_1);
//STRIP001
//STRIP001
//STRIP001  // Licht 2 Farbe
//STRIP001  if( aLbLight2.GetSelectEntryCount() )
//STRIP001  {
//STRIP001      aColor = aLbLight2.GetSelectEntryColor();
//STRIP001      rAttrs.Put(Svx3DLightcolor2Item(aColor));
//STRIP001  }
//STRIP001  else
//STRIP001      rAttrs.InvalidateItem(SDRATTR_3DSCENE_LIGHTCOLOR_2);
//STRIP001  // Licht 2 (an/aus)
//STRIP001  eState = aBtnLight2.GetState();
//STRIP001  if( eState != STATE_DONTKNOW )
//STRIP001  {
//STRIP001      BOOL bValue = GetUILightState( aBtnLight2 );
//STRIP001      rAttrs.Put(Svx3DLightOnOff2Item(bValue));
//STRIP001
//STRIP001      // Licht 2 (Richtung)
//STRIP001      if( bValue )
//STRIP001      {
//STRIP001          aVector = pLightGroup->GetDirection( Base3DLight1 );
//STRIP001          rAttrs.Put(Svx3DLightDirection2Item(aVector));
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001      rAttrs.InvalidateItem(SDRATTR_3DSCENE_LIGHTON_2);
//STRIP001
//STRIP001  // Licht 3 Farbe
//STRIP001  if( aLbLight3.GetSelectEntryCount() )
//STRIP001  {
//STRIP001      aColor = aLbLight3.GetSelectEntryColor();
//STRIP001      rAttrs.Put(Svx3DLightcolor3Item(aColor));
//STRIP001  }
//STRIP001  else
//STRIP001      rAttrs.InvalidateItem(SDRATTR_3DSCENE_LIGHTCOLOR_3);
//STRIP001  // Licht 3 (an/aus)
//STRIP001  eState = aBtnLight3.GetState();
//STRIP001  if( eState != STATE_DONTKNOW )
//STRIP001  {
//STRIP001      BOOL bValue = GetUILightState( aBtnLight3 );
//STRIP001      rAttrs.Put(Svx3DLightOnOff3Item(bValue));
//STRIP001
//STRIP001      // Licht 3 (Richtung)
//STRIP001      if( bValue )
//STRIP001      {
//STRIP001          aVector = pLightGroup->GetDirection( Base3DLight2 );
//STRIP001          rAttrs.Put(Svx3DLightDirection3Item(aVector));
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001      rAttrs.InvalidateItem(SDRATTR_3DSCENE_LIGHTON_3);
//STRIP001
//STRIP001  // Licht 4 Farbe
//STRIP001  if( aLbLight4.GetSelectEntryCount() )
//STRIP001  {
//STRIP001      aColor = aLbLight4.GetSelectEntryColor();
//STRIP001      rAttrs.Put(Svx3DLightcolor4Item(aColor));
//STRIP001  }
//STRIP001  else
//STRIP001      rAttrs.InvalidateItem(SDRATTR_3DSCENE_LIGHTCOLOR_4);
//STRIP001  // Licht 4 (an/aus)
//STRIP001  eState = aBtnLight4.GetState();
//STRIP001  if( eState != STATE_DONTKNOW )
//STRIP001  {
//STRIP001      BOOL bValue = GetUILightState( aBtnLight4 );
//STRIP001      rAttrs.Put(Svx3DLightOnOff4Item(bValue));
//STRIP001
//STRIP001      // Licht 4 (Richtung)
//STRIP001      if( bValue )
//STRIP001      {
//STRIP001          aVector = pLightGroup->GetDirection( Base3DLight3 );
//STRIP001          rAttrs.Put(Svx3DLightDirection4Item(aVector));
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001      rAttrs.InvalidateItem(SDRATTR_3DSCENE_LIGHTON_4);
//STRIP001
//STRIP001  // Licht 5 Farbe
//STRIP001  if( aLbLight5.GetSelectEntryCount() )
//STRIP001  {
//STRIP001      aColor = aLbLight5.GetSelectEntryColor();
//STRIP001      rAttrs.Put(Svx3DLightcolor5Item(aColor));
//STRIP001  }
//STRIP001  else
//STRIP001      rAttrs.InvalidateItem(SDRATTR_3DSCENE_LIGHTCOLOR_5);
//STRIP001  // Licht 5 (an/aus)
//STRIP001  eState = aBtnLight5.GetState();
//STRIP001  if( eState != STATE_DONTKNOW )
//STRIP001  {
//STRIP001      BOOL bValue = GetUILightState( aBtnLight5 );
//STRIP001      rAttrs.Put(Svx3DLightOnOff5Item(bValue));
//STRIP001
//STRIP001      // Licht 5 (Richtung)
//STRIP001      if( bValue )
//STRIP001      {
//STRIP001          aVector = pLightGroup->GetDirection( Base3DLight4 );
//STRIP001          rAttrs.Put(Svx3DLightDirection5Item(aVector));
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001      rAttrs.InvalidateItem(SDRATTR_3DSCENE_LIGHTON_5);
//STRIP001
//STRIP001  // Licht 6 Farbe
//STRIP001  if( aLbLight6.GetSelectEntryCount() )
//STRIP001  {
//STRIP001      aColor = aLbLight6.GetSelectEntryColor();
//STRIP001      rAttrs.Put(Svx3DLightcolor6Item(aColor));
//STRIP001  }
//STRIP001  else
//STRIP001      rAttrs.InvalidateItem(SDRATTR_3DSCENE_LIGHTCOLOR_6);
//STRIP001  // Licht 6 (an/aus)
//STRIP001  eState = aBtnLight6.GetState();
//STRIP001  if( eState != STATE_DONTKNOW )
//STRIP001  {
//STRIP001      BOOL bValue = GetUILightState( aBtnLight6 );
//STRIP001      rAttrs.Put(Svx3DLightOnOff6Item(bValue));
//STRIP001
//STRIP001      // Licht 6 (Richtung)
//STRIP001      if( bValue )
//STRIP001      {
//STRIP001          aVector = pLightGroup->GetDirection( Base3DLight5 );
//STRIP001          rAttrs.Put(Svx3DLightDirection6Item(aVector));
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001      rAttrs.InvalidateItem(SDRATTR_3DSCENE_LIGHTON_6);
//STRIP001
//STRIP001  // Licht 7 Farbe
//STRIP001  if( aLbLight7.GetSelectEntryCount() )
//STRIP001  {
//STRIP001      aColor = aLbLight7.GetSelectEntryColor();
//STRIP001      rAttrs.Put(Svx3DLightcolor7Item(aColor));
//STRIP001  }
//STRIP001  else
//STRIP001      rAttrs.InvalidateItem(SDRATTR_3DSCENE_LIGHTCOLOR_7);
//STRIP001  // Licht 7 (an/aus)
//STRIP001  eState = aBtnLight7.GetState();
//STRIP001  if( eState != STATE_DONTKNOW )
//STRIP001  {
//STRIP001      BOOL bValue = GetUILightState( aBtnLight7 );
//STRIP001      rAttrs.Put(Svx3DLightOnOff7Item(bValue));
//STRIP001
//STRIP001      // Licht 7 (Richtung)
//STRIP001      if( bValue )
//STRIP001      {
//STRIP001          aVector = pLightGroup->GetDirection( Base3DLight6 );
//STRIP001          rAttrs.Put(Svx3DLightDirection7Item(aVector));
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001      rAttrs.InvalidateItem(SDRATTR_3DSCENE_LIGHTON_7);
//STRIP001
//STRIP001  // Licht 8 Farbe
//STRIP001  if( aLbLight8.GetSelectEntryCount() )
//STRIP001  {
//STRIP001      aColor = aLbLight8.GetSelectEntryColor();
//STRIP001      rAttrs.Put(Svx3DLightcolor8Item(aColor));
//STRIP001  }
//STRIP001  else
//STRIP001      rAttrs.InvalidateItem(SDRATTR_3DSCENE_LIGHTCOLOR_8);
//STRIP001  // Licht 8 (an/aus)
//STRIP001  eState = aBtnLight8.GetState();
//STRIP001  if( eState != STATE_DONTKNOW )
//STRIP001  {
//STRIP001      BOOL bValue = GetUILightState( aBtnLight8 );
//STRIP001      rAttrs.Put(Svx3DLightOnOff8Item(bValue));
//STRIP001
//STRIP001      // Licht 8 (Richtung)
//STRIP001      if( bValue )
//STRIP001      {
//STRIP001          aVector = pLightGroup->GetDirection( Base3DLight7 );
//STRIP001          rAttrs.Put(Svx3DLightDirection8Item(aVector));
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001      rAttrs.InvalidateItem(SDRATTR_3DSCENE_LIGHTON_8);
//STRIP001
//STRIP001  // Umgebungslicht
//STRIP001  if( aLbAmbientlight.GetSelectEntryCount() )
//STRIP001  {
//STRIP001      aColor = aLbAmbientlight.GetSelectEntryColor();
//STRIP001      rAttrs.Put(Svx3DAmbientcolorItem(aColor));
//STRIP001  }
//STRIP001  else
//STRIP001      rAttrs.InvalidateItem(SDRATTR_3DSCENE_AMBIENTCOLOR);
//STRIP001
//STRIP001 // Texturen
//STRIP001  // Art
//STRIP001  nValue = 3;
//STRIP001  if( aBtnTexLuminance.IsChecked() )
//STRIP001      nValue = 1;
//STRIP001  else if( aBtnTexColor.IsChecked() )
//STRIP001      nValue = 3;
//STRIP001
//STRIP001  if( nValue == 1 || nValue == 3 )
//STRIP001      rAttrs.Put(Svx3DTextureKindItem(nValue));
//STRIP001  else
//STRIP001      rAttrs.InvalidateItem(SDRATTR_3DOBJ_TEXTURE_KIND);
//STRIP001
//STRIP001
//STRIP001  // Modus
//STRIP001  nValue = 99;
//STRIP001  if( aBtnTexReplace.IsChecked() )
//STRIP001      nValue = 1;
//STRIP001  else if( aBtnTexModulate.IsChecked() )
//STRIP001      nValue = 2;
//STRIP001  //else if( aBtnTexBlend.IsChecked() )
//STRIP001  //  nValue = 2;
//STRIP001
//STRIP001  if( nValue == 1 || nValue == 2 )
//STRIP001      rAttrs.Put(Svx3DTextureModeItem(nValue));
//STRIP001  else
//STRIP001      rAttrs.InvalidateItem(SDRATTR_3DOBJ_TEXTURE_MODE);
//STRIP001
//STRIP001  // Projektion X
//STRIP001  nValue = 99;
//STRIP001  if( aBtnTexObjectX.IsChecked() )
//STRIP001      nValue = 0;
//STRIP001  else if( aBtnTexParallelX.IsChecked() )
//STRIP001      nValue = 1;
//STRIP001  else if( aBtnTexCircleX.IsChecked() )
//STRIP001      nValue = 2;
//STRIP001
//STRIP001  if( nValue <= 2 )
//STRIP001      rAttrs.Put(Svx3DTextureProjectionXItem(nValue));
//STRIP001  else
//STRIP001      rAttrs.InvalidateItem(SDRATTR_3DOBJ_TEXTURE_PROJ_X);
//STRIP001
//STRIP001  // Projektion Y
//STRIP001  nValue = 99;
//STRIP001  if( aBtnTexObjectY.IsChecked() )
//STRIP001      nValue = 0;
//STRIP001  else if( aBtnTexParallelY.IsChecked() )
//STRIP001      nValue = 1;
//STRIP001  else if( aBtnTexCircleY.IsChecked() )
//STRIP001      nValue = 2;
//STRIP001
//STRIP001  if( nValue <= 2 )
//STRIP001      rAttrs.Put(Svx3DTextureProjectionYItem(nValue));
//STRIP001  else
//STRIP001      rAttrs.InvalidateItem(SDRATTR_3DOBJ_TEXTURE_PROJ_Y);
//STRIP001
//STRIP001
//STRIP001  // Filter
//STRIP001  eState = aBtnTexFilter.GetState();
//STRIP001  if( eState != STATE_DONTKNOW )
//STRIP001  {
//STRIP001      BOOL bValue = STATE_CHECK == eState;
//STRIP001      rAttrs.Put(Svx3DTextureFilterItem(bValue));
//STRIP001  }
//STRIP001  else
//STRIP001      rAttrs.InvalidateItem(SDRATTR_3DOBJ_TEXTURE_FILTER);
//STRIP001
//STRIP001
//STRIP001 // Material
//STRIP001  // Objektfarbe
//STRIP001  if( aLbMatColor.GetSelectEntryCount() )
//STRIP001  {
//STRIP001      aColor = aLbMatColor.GetSelectEntryColor();
//STRIP001      rAttrs.Put( XFillColorItem( String(), aColor) );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      rAttrs.InvalidateItem( XATTR_FILLCOLOR );
//STRIP001  }
//STRIP001
//STRIP001  // Slebstleuchtfarbe
//STRIP001  if( aLbMatEmission.GetSelectEntryCount() )
//STRIP001  {
//STRIP001      aColor = aLbMatEmission.GetSelectEntryColor();
//STRIP001      rAttrs.Put(Svx3DMaterialEmissionItem(aColor));
//STRIP001  }
//STRIP001  else
//STRIP001      rAttrs.InvalidateItem(SDRATTR_3DOBJ_MAT_EMISSION);
//STRIP001
//STRIP001  // Glanzpunkt
//STRIP001  if( aLbMatSpecular.GetSelectEntryCount() )
//STRIP001  {
//STRIP001      aColor = aLbMatSpecular.GetSelectEntryColor();
//STRIP001      rAttrs.Put(Svx3DMaterialSpecularItem(aColor));
//STRIP001  }
//STRIP001  else
//STRIP001      rAttrs.InvalidateItem(SDRATTR_3DOBJ_MAT_SPECULAR);
//STRIP001
//STRIP001  // Glanzpunkt Intensitaet
//STRIP001  if( !aMtrMatSpecularIntensity.IsEmptyFieldValue() )
//STRIP001  {
//STRIP001      UINT16 nValue = (UINT16) aMtrMatSpecularIntensity.GetValue();
//STRIP001      rAttrs.Put(Svx3DMaterialSpecularIntensityItem(nValue));
//STRIP001  }
//STRIP001  else
//STRIP001      rAttrs.InvalidateItem(SDRATTR_3DOBJ_MAT_SPECULAR_INTENSITY);
//STRIP001 }

// -----------------------------------------------------------------------
//STRIP001 void __EXPORT Svx3DWin::Resize()
//STRIP001 {
//STRIP001  if ( !IsFloatingMode() ||
//STRIP001       !GetFloatingWindow()->IsRollUp() )
//STRIP001  {
//STRIP001      Size aWinSize( GetOutputSizePixel() ); // vorher rSize im Resizing()
//STRIP001
//STRIP001      if( aWinSize.Height() >= GetMinOutputSizePixel().Height() &&
//STRIP001          aWinSize.Width() >= GetMinOutputSizePixel().Width() )
//STRIP001      {
//STRIP001          Size aDiffSize;
//STRIP001          aDiffSize.Width() = aWinSize.Width() - aSize.Width();
//STRIP001          aDiffSize.Height() = aWinSize.Height() - aSize.Height();
//STRIP001
//STRIP001          Point aXPt;
//STRIP001          Point aYPt;
//STRIP001          aXPt.X() = aDiffSize.Width();
//STRIP001          aYPt.Y() = aDiffSize.Height();
//STRIP001
//STRIP001          Size aObjSize;
//STRIP001
//STRIP001          // Hide
//STRIP001          aBtnUpdate.Hide();
//STRIP001          aBtnAssign.Hide();
//STRIP001
//STRIP001          aBtnConvertTo3D.Hide();
//STRIP001          aBtnLatheObject.Hide();
//STRIP001          aBtnPerspective.Hide();
//STRIP001
//STRIP001          aCtlPreview.Hide();
//STRIP001          aCtlLightPreview.Hide();
//STRIP001
//STRIP001             aFLFavorites.Hide();
//STRIP001             aFLGeometrie.Hide();
//STRIP001             aFLRepresentation.Hide();
//STRIP001             aFLLight.Hide();
//STRIP001             aFLTexture.Hide();
//STRIP001             aFLMaterial.Hide();
//STRIP001
//STRIP001          // Verschieben / Resizen
//STRIP001          aBtnUpdate.SetPosPixel( aBtnUpdate.GetPosPixel() + aXPt );
//STRIP001          aBtnAssign.SetPosPixel( aBtnAssign.GetPosPixel() + aXPt );
//STRIP001
//STRIP001              // Preview-Controls
//STRIP001          aObjSize = aCtlPreview.GetOutputSizePixel();
//STRIP001          aObjSize.Width() += aDiffSize.Width();
//STRIP001          aObjSize.Height() += aDiffSize.Height();
//STRIP001          aCtlPreview.SetOutputSizePixel( aObjSize );
//STRIP001          aCtlLightPreview.SetOutputSizePixel( aObjSize );
//STRIP001
//STRIP001             // Groups
//STRIP001             aObjSize = aFLFavorites.GetOutputSizePixel();
//STRIP001          aObjSize.Width() += aDiffSize.Width();
//STRIP001             aFLFavorites.SetOutputSizePixel( aObjSize );
//STRIP001             aFLGeometrie.SetOutputSizePixel( aObjSize );
//STRIP001             aFLSegments.SetOutputSizePixel( aObjSize );
//STRIP001             aFLShadow.SetOutputSizePixel( aObjSize );
//STRIP001             aFLCamera.SetOutputSizePixel( aObjSize );
//STRIP001             aFLRepresentation.SetOutputSizePixel( aObjSize );
//STRIP001             aFLLight.SetOutputSizePixel( aObjSize );
//STRIP001             aFLTexture.SetOutputSizePixel( aObjSize );
//STRIP001             aFLMaterial.SetOutputSizePixel( aObjSize );
//STRIP001
//STRIP001              // Y-Position der unteren Buttons
//STRIP001          aBtnConvertTo3D.SetPosPixel( aBtnConvertTo3D.GetPosPixel() + aYPt );
//STRIP001          aBtnLatheObject.SetPosPixel( aBtnLatheObject.GetPosPixel() + aYPt );
//STRIP001          aBtnPerspective.SetPosPixel( aBtnPerspective.GetPosPixel() + aYPt );
//STRIP001
//STRIP001          // Show
//STRIP001          aBtnUpdate.Show();
//STRIP001          aBtnAssign.Show();
//STRIP001
//STRIP001          aBtnConvertTo3D.Show();
//STRIP001          aBtnLatheObject.Show();
//STRIP001          aBtnPerspective.Show();
//STRIP001
//STRIP001          if( aBtnFavorites.IsChecked() )
//STRIP001              ClickViewTypeHdl( &aBtnFavorites );
//STRIP001          if( aBtnGeo.IsChecked() )
//STRIP001              ClickViewTypeHdl( &aBtnGeo );
//STRIP001          if( aBtnRepresentation.IsChecked() )
//STRIP001              ClickViewTypeHdl( &aBtnRepresentation );
//STRIP001          if( aBtnLight.IsChecked() )
//STRIP001              ClickViewTypeHdl( &aBtnLight );
//STRIP001          if( aBtnTexture.IsChecked() )
//STRIP001              ClickViewTypeHdl( &aBtnTexture );
//STRIP001          if( aBtnMaterial.IsChecked() )
//STRIP001              ClickViewTypeHdl( &aBtnMaterial );
//STRIP001
//STRIP001          aSize = aWinSize;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  SfxDockingWindow::Resize();
//STRIP001 }

// -----------------------------------------------------------------------
//STRIP001 IMPL_LINK( Svx3DWin, ClickUpdateHdl, void *, EMPTYARG )
//STRIP001 {
//STRIP001  bUpdate = !aBtnUpdate.IsChecked();
//STRIP001  aBtnUpdate.Check( bUpdate );
//STRIP001
//STRIP001  if( bUpdate )
//STRIP001  {
//STRIP001      SfxBoolItem aItem( SID_3D_STATE, TRUE );
//STRIP001      SfxViewFrame::Current()->GetBindings().GetDispatcher()->Execute(
//STRIP001          SID_3D_STATE, SFX_CALLMODE_ASYNCHRON | SFX_CALLMODE_RECORD, &aItem, 0L );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      // Controls koennen u.U. disabled sein
//STRIP001      /*
//STRIP001      aFtSegments.Enable();
//STRIP001      aNumHorizontal.Enable();
//STRIP001      aNumVertical.Enable();
//STRIP001      */
//STRIP001  }
//STRIP001
//STRIP001  return( 0L );
//STRIP001 }

// -----------------------------------------------------------------------
//STRIP001 IMPL_LINK( Svx3DWin, ClickAssignHdl, void *, EMPTYARG )
//STRIP001 {
//STRIP001  SfxBoolItem aItem( SID_3D_ASSIGN, TRUE );
//STRIP001  SfxViewFrame::Current()->GetBindings().GetDispatcher()->Execute(
//STRIP001      SID_3D_ASSIGN, SFX_CALLMODE_ASYNCHRON | SFX_CALLMODE_RECORD, &aItem, 0L );
//STRIP001
//STRIP001  return( 0L );
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 IMPL_LINK( Svx3DWin, ClickViewTypeHdl, void *, pBtn )
//STRIP001 {
//STRIP001
//STRIP001  if( pBtn )
//STRIP001  {
//STRIP001      // Da das permanente Updaten der Preview zu teuer waere
//STRIP001      BOOL bUpdatePreview = aBtnLight.IsChecked();
//STRIP001
//STRIP001      aBtnFavorites.Check( &aBtnFavorites == pBtn );
//STRIP001      aBtnGeo.Check( &aBtnGeo == pBtn );
//STRIP001      aBtnRepresentation.Check( &aBtnRepresentation == pBtn );
//STRIP001      aBtnLight.Check( &aBtnLight == pBtn );
//STRIP001      aBtnTexture.Check( &aBtnTexture == pBtn );
//STRIP001      aBtnMaterial.Check( &aBtnMaterial == pBtn );
//STRIP001
//STRIP001      if( aBtnFavorites.IsChecked() )
//STRIP001          eViewType = VIEWTYPE_FAVORITES;
//STRIP001      if( aBtnGeo.IsChecked() )
//STRIP001          eViewType = VIEWTYPE_GEO;
//STRIP001      if( aBtnRepresentation.IsChecked() )
//STRIP001          eViewType = VIEWTYPE_REPRESENTATION;
//STRIP001      if( aBtnLight.IsChecked() )
//STRIP001          eViewType = VIEWTYPE_LIGHT;
//STRIP001      if( aBtnTexture.IsChecked() )
//STRIP001          eViewType = VIEWTYPE_TEXTURE;
//STRIP001      if( aBtnMaterial.IsChecked() )
//STRIP001          eViewType = VIEWTYPE_MATERIAL;
//STRIP001
//STRIP001      // Favoriten
//STRIP001      if( eViewType == VIEWTYPE_FAVORITES )
//STRIP001      {
//STRIP001          aCtlFavorites.Show();
//STRIP001             aFLFavorites.Show();
//STRIP001          aBtnOnly3D.Show();
//STRIP001          aBtnAllAttributes.Show();
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          aCtlFavorites.Hide();
//STRIP001             aFLFavorites.Hide();
//STRIP001          aBtnOnly3D.Hide();
//STRIP001          aBtnAllAttributes.Hide();
//STRIP001      }
//STRIP001
//STRIP001      // Geometrie
//STRIP001      if( eViewType == VIEWTYPE_GEO )
//STRIP001      {
//STRIP001          aFtHorizontal.Show();
//STRIP001          aNumHorizontal.Show();
//STRIP001          aFtVertical.Show();
//STRIP001          aNumVertical.Show();
//STRIP001             aFLSegments.Show();
//STRIP001          aFtPercentDiagonal.Show();
//STRIP001          aMtrPercentDiagonal.Show();
//STRIP001          aFtBackscale.Show();
//STRIP001          aMtrBackscale.Show();
//STRIP001          aFtEndAngle.Show();
//STRIP001          aMtrEndAngle.Show();
//STRIP001          aFtDepth.Show();
//STRIP001          aMtrDepth.Show();
//STRIP001             aFLGeometrie.Show();
//STRIP001
//STRIP001          aBtnNormalsObj.Show();
//STRIP001          aBtnNormalsFlat.Show();
//STRIP001          aBtnNormalsSphere.Show();
//STRIP001          aBtnTwoSidedLighting.Show();
//STRIP001          aBtnNormalsInvert.Show();
//STRIP001             aFLNormals.Show();
//STRIP001          aBtnDoubleSided.Show();
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          aFtHorizontal.Hide();
//STRIP001          aNumHorizontal.Hide();
//STRIP001          aFtVertical.Hide();
//STRIP001          aNumVertical.Hide();
//STRIP001             aFLSegments.Hide();
//STRIP001          aFtPercentDiagonal.Hide();
//STRIP001          aMtrPercentDiagonal.Hide();
//STRIP001          aFtBackscale.Hide();
//STRIP001          aMtrBackscale.Hide();
//STRIP001          aFtEndAngle.Hide();
//STRIP001          aMtrEndAngle.Hide();
//STRIP001          aFtDepth.Hide();
//STRIP001          aMtrDepth.Hide();
//STRIP001             aFLGeometrie.Hide();
//STRIP001
//STRIP001          aBtnNormalsObj.Hide();
//STRIP001          aBtnNormalsFlat.Hide();
//STRIP001          aBtnNormalsSphere.Hide();
//STRIP001          aBtnTwoSidedLighting.Hide();
//STRIP001          aBtnNormalsInvert.Hide();
//STRIP001             aFLNormals.Hide();
//STRIP001          aBtnDoubleSided.Hide();
//STRIP001      }
//STRIP001
//STRIP001      // Darstellung
//STRIP001      if( eViewType == VIEWTYPE_REPRESENTATION )
//STRIP001      {
//STRIP001          aFtShademode.Show();
//STRIP001          aLbShademode.Show();
//STRIP001          aBtnShadow3d.Show();
//STRIP001          aFtSlant.Show();
//STRIP001          aMtrSlant.Show();
//STRIP001             aFLShadow.Show();
//STRIP001          aFtDistance.Show();
//STRIP001          aMtrDistance.Show();
//STRIP001          aFtFocalLeng.Show();
//STRIP001          aMtrFocalLength.Show();
//STRIP001             aFLCamera.Show();
//STRIP001             aFLRepresentation.Show();
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          aFtShademode.Hide();
//STRIP001          aLbShademode.Hide();
//STRIP001          aBtnShadow3d.Hide();
//STRIP001          aFtSlant.Hide();
//STRIP001          aMtrSlant.Hide();
//STRIP001             aFLShadow.Hide();
//STRIP001          aFtDistance.Hide();
//STRIP001          aMtrDistance.Hide();
//STRIP001          aFtFocalLeng.Hide();
//STRIP001          aMtrFocalLength.Hide();
//STRIP001             aFLCamera.Hide();
//STRIP001             aFLRepresentation.Hide();
//STRIP001      }
//STRIP001
//STRIP001      // Beleuchtung
//STRIP001      if( eViewType == VIEWTYPE_LIGHT )
//STRIP001      {
//STRIP001          aBtnLight1.Show();
//STRIP001          aBtnLight2.Show();
//STRIP001          aBtnLight3.Show();
//STRIP001          aBtnLight4.Show();
//STRIP001          aBtnLight5.Show();
//STRIP001          aBtnLight6.Show();
//STRIP001          aBtnLight7.Show();
//STRIP001          aBtnLight8.Show();
//STRIP001          //aLbLight1.Show();
//STRIP001          aBtnLightColor.Show();
//STRIP001             aFTLightsource.Show();
//STRIP001          aLbAmbientlight.Show();
//STRIP001          aBtnAmbientColor.Show();
//STRIP001             aFTAmbientlight.Show();
//STRIP001             aFLLight.Show();
//STRIP001          //aFtLightX.Show();
//STRIP001          //aFtLightY.Show();
//STRIP001          //aFtLightZ.Show();
//STRIP001          //aGrpLightInfo.Show();
//STRIP001
//STRIP001          ColorLB* pLb = GetLbByButton();
//STRIP001          if( pLb )
//STRIP001              pLb->Show();
//STRIP001
//STRIP001          aCtlLightPreview.Show();
//STRIP001          aCtlPreview.Hide();
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          aBtnLight1.Hide();
//STRIP001          aBtnLight2.Hide();
//STRIP001          aBtnLight3.Hide();
//STRIP001          aBtnLight4.Hide();
//STRIP001          aBtnLight5.Hide();
//STRIP001          aBtnLight6.Hide();
//STRIP001          aBtnLight7.Hide();
//STRIP001          aBtnLight8.Hide();
//STRIP001          aLbLight1.Hide();
//STRIP001          aLbLight2.Hide();
//STRIP001          aLbLight3.Hide();
//STRIP001          aLbLight4.Hide();
//STRIP001          aLbLight5.Hide();
//STRIP001          aLbLight6.Hide();
//STRIP001          aLbLight7.Hide();
//STRIP001          aLbLight8.Hide();
//STRIP001          aBtnLightColor.Hide();
//STRIP001             aFTLightsource.Hide();
//STRIP001          aLbAmbientlight.Hide();
//STRIP001          aBtnAmbientColor.Hide();
//STRIP001             aFTAmbientlight.Hide();
//STRIP001             aFLLight.Hide();
//STRIP001
//STRIP001          if( !aCtlPreview.IsVisible() )
//STRIP001          {
//STRIP001              aCtlPreview.Show();
//STRIP001              aCtlLightPreview.Hide();
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      // Texturen
//STRIP001      if( eViewType == VIEWTYPE_TEXTURE )
//STRIP001      {
//STRIP001          aFtTexKind.Show();
//STRIP001          aBtnTexLuminance.Show();
//STRIP001          aBtnTexColor.Show();
//STRIP001          aFtTexMode.Show();
//STRIP001          aBtnTexReplace.Show();
//STRIP001          aBtnTexModulate.Show();
//STRIP001          //aBtnTexBlend.Show();
//STRIP001          aFtTexProjectionX.Show();
//STRIP001          aBtnTexParallelX.Show();
//STRIP001          aBtnTexCircleX.Show();
//STRIP001          aBtnTexObjectX.Show();
//STRIP001          aFtTexProjectionY.Show();
//STRIP001          aBtnTexParallelY.Show();
//STRIP001          aBtnTexCircleY.Show();
//STRIP001          aBtnTexObjectY.Show();
//STRIP001          aFtTexFilter.Show();
//STRIP001          aBtnTexFilter.Show();
//STRIP001             aFLTexture.Show();
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          aFtTexKind.Hide();
//STRIP001          aBtnTexLuminance.Hide();
//STRIP001          aBtnTexColor.Hide();
//STRIP001          aFtTexMode.Hide();
//STRIP001          aBtnTexReplace.Hide();
//STRIP001          aBtnTexModulate.Hide();
//STRIP001          aBtnTexBlend.Hide();
//STRIP001          aFtTexProjectionX.Hide();
//STRIP001          aBtnTexParallelX.Hide();
//STRIP001          aBtnTexCircleX.Hide();
//STRIP001          aBtnTexObjectX.Hide();
//STRIP001          aFtTexProjectionY.Hide();
//STRIP001          aBtnTexParallelY.Hide();
//STRIP001          aBtnTexCircleY.Hide();
//STRIP001          aBtnTexObjectY.Hide();
//STRIP001          aFtTexFilter.Hide();
//STRIP001          aBtnTexFilter.Hide();
//STRIP001             aFLTexture.Hide();
//STRIP001      }
//STRIP001
//STRIP001      // Material
//STRIP001      if( eViewType == VIEWTYPE_MATERIAL )
//STRIP001      {
//STRIP001          aFtMatFavorites.Show();
//STRIP001          aLbMatFavorites.Show();
//STRIP001          aFtMatColor.Show();
//STRIP001          aLbMatColor.Show();
//STRIP001          aBtnMatColor.Show();
//STRIP001          aFtMatEmission.Show();
//STRIP001          aLbMatEmission.Show();
//STRIP001          aBtnEmissionColor.Show();
//STRIP001          aFtMatSpecular.Show();
//STRIP001          aLbMatSpecular.Show();
//STRIP001          aBtnSpecularColor.Show();
//STRIP001          aFtMatSpecularIntensity.Show();
//STRIP001          aMtrMatSpecularIntensity.Show();
//STRIP001             aFLMatSpecular.Show();
//STRIP001             aFLMaterial.Show();
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          aFtMatFavorites.Hide();
//STRIP001          aLbMatFavorites.Hide();
//STRIP001          aFtMatColor.Hide();
//STRIP001          aLbMatColor.Hide();
//STRIP001          aBtnMatColor.Hide();
//STRIP001          aFtMatEmission.Hide();
//STRIP001          aLbMatEmission.Hide();
//STRIP001          aBtnEmissionColor.Hide();
//STRIP001          aFtMatSpecular.Hide();
//STRIP001          aLbMatSpecular.Hide();
//STRIP001          aBtnSpecularColor.Hide();
//STRIP001          aFtMatSpecularIntensity.Hide();
//STRIP001          aMtrMatSpecularIntensity.Hide();
//STRIP001             aFLMatSpecular.Hide();
//STRIP001             aFLMaterial.Hide();
//STRIP001      }
//STRIP001      if( bUpdatePreview && !aBtnLight.IsChecked() )
//STRIP001          UpdatePreview();
//STRIP001
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      aBtnFavorites.Check( eViewType == VIEWTYPE_FAVORITES );
//STRIP001      aBtnGeo.Check( eViewType == VIEWTYPE_GEO );
//STRIP001      aBtnRepresentation.Check( eViewType == VIEWTYPE_REPRESENTATION );
//STRIP001      aBtnLight.Check( eViewType == VIEWTYPE_LIGHT );
//STRIP001      aBtnTexture.Check( eViewType == VIEWTYPE_TEXTURE );
//STRIP001      aBtnMaterial.Check( eViewType == VIEWTYPE_MATERIAL );
//STRIP001  }
//STRIP001  return( 0L );
//STRIP001 }

// -----------------------------------------------------------------------
//STRIP001 IMPL_LINK( Svx3DWin, ClickHdl, PushButton *, pBtn )
//STRIP001 {
//STRIP001  BOOL bUpdatePreview = FALSE;
//STRIP001
//STRIP001  if( pBtn )
//STRIP001  {
//STRIP001      USHORT nSId = 0;
//STRIP001
//STRIP001      if( pBtn == &aBtnConvertTo3D )
//STRIP001      {
//STRIP001          nSId = SID_CONVERT_TO_3D;
//STRIP001      }
//STRIP001      else if( pBtn == &aBtnLatheObject )
//STRIP001      {
//STRIP001          nSId = SID_CONVERT_TO_3D_LATHE_FAST;
//STRIP001      }
//STRIP001      // Favoriten
//STRIP001      else if( pBtn == &aBtnOnly3D ||
//STRIP001               pBtn == &aBtnAllAttributes )
//STRIP001      {
//STRIP001          bOnly3DChanged = TRUE;
//STRIP001          aBtnOnly3D.Check( pBtn == &aBtnOnly3D );
//STRIP001          aBtnAllAttributes.Check( pBtn == &aBtnAllAttributes );
//STRIP001          bUpdatePreview = TRUE;
//STRIP001      }
//STRIP001      // Geometrie
//STRIP001      else if( pBtn == &aBtnNormalsObj ||
//STRIP001               pBtn == &aBtnNormalsFlat ||
//STRIP001               pBtn == &aBtnNormalsSphere )
//STRIP001      {
//STRIP001          aBtnNormalsObj.Check( pBtn == &aBtnNormalsObj );
//STRIP001          aBtnNormalsFlat.Check( pBtn == &aBtnNormalsFlat );
//STRIP001          aBtnNormalsSphere.Check( pBtn == &aBtnNormalsSphere );
//STRIP001          bUpdatePreview = TRUE;
//STRIP001      }
//STRIP001      else if( pBtn == &aBtnLight1 ||
//STRIP001               pBtn == &aBtnLight2 ||
//STRIP001               pBtn == &aBtnLight3 ||
//STRIP001               pBtn == &aBtnLight4 ||
//STRIP001               pBtn == &aBtnLight5 ||
//STRIP001               pBtn == &aBtnLight6 ||
//STRIP001               pBtn == &aBtnLight7 ||
//STRIP001               pBtn == &aBtnLight8 )
//STRIP001      {
//STRIP001          // Beleuchtung
//STRIP001          ColorLB* pLb = GetLbByButton( pBtn );
//STRIP001          pLb->Show();
//STRIP001
//STRIP001          if( pBtn->IsChecked() )
//STRIP001          {
//STRIP001              SetUILightState( *(ImageButton*)pBtn, !GetUILightState( *(ImageButton*)pBtn ) );
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              pBtn->Check();
//STRIP001
//STRIP001              if( pBtn != &aBtnLight1 && aBtnLight1.IsChecked() )
//STRIP001              {
//STRIP001                  aBtnLight1.Check( FALSE );
//STRIP001                  aLbLight1.Hide();
//STRIP001              }
//STRIP001              if( pBtn != &aBtnLight2 && aBtnLight2.IsChecked() )
//STRIP001              {
//STRIP001                  aBtnLight2.Check( FALSE );
//STRIP001                  aLbLight2.Hide();
//STRIP001              }
//STRIP001              if( pBtn != &aBtnLight3 && aBtnLight3.IsChecked() )
//STRIP001              {
//STRIP001                  aBtnLight3.Check( FALSE );
//STRIP001                  aLbLight3.Hide();
//STRIP001              }
//STRIP001              if( pBtn != &aBtnLight4 && aBtnLight4.IsChecked() )
//STRIP001              {
//STRIP001                  aBtnLight4.Check( FALSE );
//STRIP001                  aLbLight4.Hide();
//STRIP001              }
//STRIP001              if( pBtn != &aBtnLight5 && aBtnLight5.IsChecked() )
//STRIP001              {
//STRIP001                  aBtnLight5.Check( FALSE );
//STRIP001                  aLbLight5.Hide();
//STRIP001              }
//STRIP001              if( pBtn != &aBtnLight6 && aBtnLight6.IsChecked() )
//STRIP001              {
//STRIP001                  aBtnLight6.Check( FALSE );
//STRIP001                  aLbLight6.Hide();
//STRIP001              }
//STRIP001              if( pBtn != &aBtnLight7 && aBtnLight7.IsChecked() )
//STRIP001              {
//STRIP001                  aBtnLight7.Check( FALSE );
//STRIP001                  aLbLight7.Hide();
//STRIP001              }
//STRIP001              if( pBtn != &aBtnLight8 && aBtnLight8.IsChecked() )
//STRIP001              {
//STRIP001                  aBtnLight8.Check( FALSE );
//STRIP001                  aLbLight8.Hide();
//STRIP001              }
//STRIP001          }
//STRIP001          BOOL bEnable = GetUILightState( *(ImageButton*)pBtn );
//STRIP001          aBtnLightColor.Enable( bEnable );
//STRIP001          pLb->Enable( bEnable );
//STRIP001
//STRIP001          ClickLightHdl( pBtn );
//STRIP001          bUpdatePreview = TRUE;
//STRIP001      }
//STRIP001      // Texturen
//STRIP001      else if( pBtn == &aBtnTexLuminance ||
//STRIP001               pBtn == &aBtnTexColor )
//STRIP001      {
//STRIP001          aBtnTexLuminance.Check( pBtn == &aBtnTexLuminance );
//STRIP001          aBtnTexColor.Check( pBtn == &aBtnTexColor );
//STRIP001          bUpdatePreview = TRUE;
//STRIP001      }
//STRIP001      else if( pBtn == &aBtnTexReplace ||
//STRIP001               pBtn == &aBtnTexModulate )// ||
//STRIP001               //pBtn == &aBtnTexBlend )
//STRIP001      {
//STRIP001          aBtnTexReplace.Check( pBtn == &aBtnTexReplace );
//STRIP001          aBtnTexModulate.Check( pBtn == &aBtnTexModulate );
//STRIP001          //aBtnTexBlend.Check( pBtn == &aBtnTexBlend );
//STRIP001          bUpdatePreview = TRUE;
//STRIP001      }
//STRIP001      else if( pBtn == &aBtnTexParallelX ||
//STRIP001               pBtn == &aBtnTexCircleX ||
//STRIP001               pBtn == &aBtnTexObjectX )
//STRIP001      {
//STRIP001          aBtnTexParallelX.Check( pBtn == &aBtnTexParallelX );
//STRIP001          aBtnTexCircleX.Check( pBtn == &aBtnTexCircleX );
//STRIP001          aBtnTexObjectX.Check( pBtn == &aBtnTexObjectX );
//STRIP001          bUpdatePreview = TRUE;
//STRIP001      }
//STRIP001      else if( pBtn == &aBtnTexParallelY ||
//STRIP001               pBtn == &aBtnTexCircleY ||
//STRIP001               pBtn == &aBtnTexObjectY )
//STRIP001      {
//STRIP001          aBtnTexParallelY.Check( pBtn == &aBtnTexParallelY );
//STRIP001          aBtnTexCircleY.Check( pBtn == &aBtnTexCircleY );
//STRIP001          aBtnTexObjectY.Check( pBtn == &aBtnTexObjectY );
//STRIP001          bUpdatePreview = TRUE;
//STRIP001      }
//STRIP001      else if( pBtn == &aBtnShadow3d  )
//STRIP001      {
//STRIP001          pBtn->Check( !pBtn->IsChecked() );
//STRIP001          aFtSlant.Enable( pBtn->IsChecked() );
//STRIP001          aMtrSlant.Enable( pBtn->IsChecked() );
//STRIP001          bUpdatePreview = TRUE;
//STRIP001      }
//STRIP001      // Sonstige (keine Gruppen)
//STRIP001      else if( pBtn != NULL )
//STRIP001      {
//STRIP001          pBtn->Check( !pBtn->IsChecked() );
//STRIP001          bUpdatePreview = TRUE;
//STRIP001      }
//STRIP001
//STRIP001      if( nSId > 0 )
//STRIP001      {
//STRIP001          SfxBoolItem aItem( nSId, TRUE );
//STRIP001          SfxViewFrame::Current()->GetBindings().GetDispatcher()->Execute(
//STRIP001              nSId, SFX_CALLMODE_ASYNCHRON | SFX_CALLMODE_RECORD, &aItem, 0L );
//STRIP001      }
//STRIP001      else if( bUpdatePreview == TRUE )
//STRIP001          UpdatePreview();
//STRIP001  }
//STRIP001  return( 0L );
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 IMPL_LINK( Svx3DWin, ClickColorHdl, PushButton *, pBtn )
//STRIP001 {
//STRIP001  SvColorDialog aColorDlg( this );
//STRIP001  ColorLB* pLb;
//STRIP001
//STRIP001  if( pBtn == &aBtnLightColor )
//STRIP001      pLb = GetLbByButton();
//STRIP001  else if( pBtn == &aBtnAmbientColor )
//STRIP001      pLb = &aLbAmbientlight;
//STRIP001  else if( pBtn == &aBtnMatColor )
//STRIP001      pLb = &aLbMatColor;
//STRIP001  else if( pBtn == &aBtnEmissionColor )
//STRIP001      pLb = &aLbMatEmission;
//STRIP001  else if( pBtn == &aBtnSpecularColor )
//STRIP001      pLb = &aLbMatSpecular;
//STRIP001
//STRIP001  Color aColor = pLb->GetSelectEntryColor();
//STRIP001
//STRIP001  aColorDlg.SetColor( aColor );
//STRIP001  if( aColorDlg.Execute() == RET_OK )
//STRIP001  {
//STRIP001      aColor = aColorDlg.GetColor();
//STRIP001      if( LBSelectColor( pLb, aColor ) )
//STRIP001          SelectHdl( pLb );
//STRIP001  }
//STRIP001  return( 0L );
//STRIP001 }

// -----------------------------------------------------------------------
//STRIP001 IMPL_LINK( Svx3DWin, SelectHdl, void *, p )
//STRIP001 {
//STRIP001  if( p )
//STRIP001  {
//STRIP001      Color aColor;
//STRIP001      BOOL bUpdatePreview = FALSE;
//STRIP001
//STRIP001      // Material
//STRIP001      if( p == &aLbMatFavorites )
//STRIP001      {
//STRIP001          Color aColObj( COL_WHITE );
//STRIP001          Color aColEmis( COL_BLACK );
//STRIP001          Color aColSpec( COL_WHITE );
//STRIP001          USHORT nSpecIntens = 20;
//STRIP001
//STRIP001          USHORT nPos = aLbMatFavorites.GetSelectEntryPos();
//STRIP001          switch( nPos )
//STRIP001          {
//STRIP001              case 1: // Metall
//STRIP001              {
//STRIP001                  aColObj = Color(230,230,255);
//STRIP001                  aColEmis = Color(10,10,30);
//STRIP001                  aColSpec = Color(200,200,200);
//STRIP001                  nSpecIntens = 20;
//STRIP001              }
//STRIP001              break;
//STRIP001
//STRIP001              case 2: // Gold
//STRIP001              {
//STRIP001                  aColObj = Color(230,255,0);
//STRIP001                  aColEmis = Color(51,0,0);
//STRIP001                  aColSpec = Color(255,255,240);
//STRIP001                  nSpecIntens = 20;
//STRIP001              }
//STRIP001              break;
//STRIP001
//STRIP001              case 3: // Chrom
//STRIP001              {
//STRIP001                  aColObj = Color(36,117,153);
//STRIP001                  aColEmis = Color(18,30,51);
//STRIP001                  aColSpec = Color(230,230,255);
//STRIP001                  nSpecIntens = 2;
//STRIP001              }
//STRIP001              break;
//STRIP001
//STRIP001              case 4: // Plastik
//STRIP001              {
//STRIP001                  aColObj = Color(255,48,57);
//STRIP001                  aColEmis = Color(35,0,0);
//STRIP001                  aColSpec = Color(179,202,204);
//STRIP001                  nSpecIntens = 60;
//STRIP001              }
//STRIP001              break;
//STRIP001
//STRIP001              case 5: // Holz
//STRIP001              {
//STRIP001                  aColObj = Color(153,71,1);
//STRIP001                  aColEmis = Color(21,22,0);
//STRIP001                  aColSpec = Color(255,255,153);
//STRIP001                  nSpecIntens = 75;
//STRIP001              }
//STRIP001              break;
//STRIP001          }
//STRIP001          LBSelectColor( &aLbMatColor, aColObj );
//STRIP001          LBSelectColor( &aLbMatEmission, aColEmis );
//STRIP001          LBSelectColor( &aLbMatSpecular, aColSpec );
//STRIP001          aMtrMatSpecularIntensity.SetValue( nSpecIntens );
//STRIP001
//STRIP001          bUpdatePreview = TRUE;
//STRIP001      }
//STRIP001      else if( p == &aLbMatColor ||
//STRIP001               p == &aLbMatEmission ||
//STRIP001               p == &aLbMatSpecular )
//STRIP001      {
//STRIP001          aColor = ( ( (ColorLB*)p )->GetSelectEntryColor() );
//STRIP001
//STRIP001          Base3DMaterialValue eType = Base3DMaterialDiffuse;
//STRIP001          //if( p == &aLbMatColor )
//STRIP001          if( p == &aLbMatEmission )
//STRIP001              eType = Base3DMaterialEmission;
//STRIP001          else if( p == &aLbMatSpecular )
//STRIP001              eType = Base3DMaterialSpecular;
//STRIP001
//STRIP001          //aCtlPreview.SetMaterial( aColor, eType );
//STRIP001          aCtlLightPreview.GetPreviewControl().SetMaterial( aColor, eType );
//STRIP001
//STRIP001          aLbMatFavorites.SelectEntryPos( 0 );
//STRIP001
//STRIP001          bUpdatePreview = TRUE;
//STRIP001      }
//STRIP001      // Beleuchtung
//STRIP001      else if( p == &aLbAmbientlight )
//STRIP001      {
//STRIP001          Color aColor = aLbAmbientlight.GetSelectEntryColor();
//STRIP001          pLightGroup->SetGlobalAmbientLight( aColor );
//STRIP001
//STRIP001          aCtlLightPreview.GetPreviewControl().SetLightGroup( pLightGroup );
//STRIP001          //aCtlPreview.SetLightGroup( pLightGroup );
//STRIP001          bUpdatePreview = TRUE;
//STRIP001      }
//STRIP001      else if( p == &aLbLight1 ||
//STRIP001               p == &aLbLight2 ||
//STRIP001               p == &aLbLight3 ||
//STRIP001               p == &aLbLight4 ||
//STRIP001               p == &aLbLight5 ||
//STRIP001               p == &aLbLight6 ||
//STRIP001               p == &aLbLight7 ||
//STRIP001               p == &aLbLight8 )
//STRIP001      {
//STRIP001          Color aColor = ( (ColorLB*)p )->GetSelectEntryColor();
//STRIP001          USHORT nLightSource = GetLightSource();
//STRIP001
//STRIP001          *pLightGroup = *aCtlLightPreview.GetPreviewControl().GetLightGroup();
//STRIP001
//STRIP001          pLightGroup->SetIntensity( aColor,
//STRIP001                          Base3DMaterialDiffuse,
//STRIP001                          (Base3DLightNumber) nLightSource );
//STRIP001
//STRIP001          aCtlLightPreview.GetPreviewControl().SetLightGroup( pLightGroup );
//STRIP001          //aCtlPreview.SetLightGroup( pLightGroup );
//STRIP001          bUpdatePreview = TRUE;
//STRIP001      }
//STRIP001      else if( p == &aLbShademode )
//STRIP001          bUpdatePreview = TRUE;
//STRIP001
//STRIP001      if( bUpdatePreview == TRUE )
//STRIP001          UpdatePreview();
//STRIP001  }
//STRIP001  return( 0L );
//STRIP001 }

// -----------------------------------------------------------------------
//STRIP001 IMPL_LINK( Svx3DWin, ModifyHdl, void*, pField )
//STRIP001 {
//STRIP001  if( pField )
//STRIP001  {
//STRIP001      BOOL bUpdatePreview = FALSE;
//STRIP001
//STRIP001      // Material
//STRIP001      if( pField == &aMtrMatSpecularIntensity )
//STRIP001      {
//STRIP001          UINT16 nValue = (UINT16) ( (MetricField*)pField )->GetValue();
//STRIP001          //aCtlPreview.SetShininess( nValue );
//STRIP001          aCtlLightPreview.GetPreviewControl().SetShininess( nValue );
//STRIP001          bUpdatePreview = TRUE;
//STRIP001      }
//STRIP001      else if( pField == &aNumHorizontal )
//STRIP001      {
//STRIP001          UINT16 nValue = (UINT16) ( (NumericField*)pField )->GetValue();
//STRIP001          aCtlLightPreview.GetPreviewControl().SetHorizontalSegments( nValue );
//STRIP001          //aCtlPreview.SetHorizontalSegments( nValue );
//STRIP001          bUpdatePreview = TRUE;
//STRIP001      }
//STRIP001      else if( pField == &aNumVertical )
//STRIP001      {
//STRIP001          UINT16 nValue = (UINT16) ( (NumericField*)pField )->GetValue();
//STRIP001          aCtlLightPreview.GetPreviewControl().SetVerticalSegments( nValue );
//STRIP001          //aCtlPreview.SetVerticalSegments( nValue );
//STRIP001          bUpdatePreview = TRUE;
//STRIP001      }
//STRIP001      else if( pField == &aMtrSlant )
//STRIP001          bUpdatePreview = TRUE;
//STRIP001
//STRIP001      if( bUpdatePreview == TRUE )
//STRIP001          UpdatePreview();
//STRIP001  }
//STRIP001  return( 0L );
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 IMPL_LINK( Svx3DWin, ClickLightHdl, PushButton*, pBtn )
//STRIP001 {
//STRIP001
//STRIP001  if( pBtn )
//STRIP001  {
//STRIP001      USHORT nLightSource = GetLightSource( pBtn );
//STRIP001      ColorLB* pLb = GetLbByButton( pBtn );
//STRIP001      Color aColor( pLb->GetSelectEntryColor() );
//STRIP001      *pLightGroup = *aCtlLightPreview.GetPreviewControl().GetLightGroup();
//STRIP001
//STRIP001      pLightGroup->SetIntensity( aColor,
//STRIP001                      Base3DMaterialDiffuse,
//STRIP001                      (Base3DLightNumber) nLightSource );
//STRIP001
//STRIP001      pLightGroup->Enable( GetUILightState( *(ImageButton*)pBtn ),    (Base3DLightNumber) nLightSource );
//STRIP001
//STRIP001      aCtlLightPreview.GetPreviewControl().SetLightGroup( pLightGroup );
//STRIP001      aCtlLightPreview.GetPreviewControl().SelectLight( (Base3DLightNumber) nLightSource );
//STRIP001      aCtlLightPreview.CheckSelection();
//STRIP001
//STRIP001      //aCtlPreview.SetLightGroup( pLightGroup );
//STRIP001  }
//STRIP001  return( 0L );
//STRIP001 }


// -----------------------------------------------------------------------
//STRIP001 IMPL_LINK( Svx3DWin, DoubleClickHdl, void*, p )
//STRIP001 {
//STRIP001  //USHORT nItemId = aCtlFavorites.GetSelectItemId();
//STRIP001
//STRIP001  //SfxItemSet* pSet = (SfxItemSet*) pFavorSetList->GetObject( nItemId - 1 );
//STRIP001  //Update( *pSet );
//STRIP001
//STRIP001  // und zuweisen
//STRIP001  ClickAssignHdl( NULL );
//STRIP001
//STRIP001  return( 0L );
//STRIP001 }

// -----------------------------------------------------------------------
//STRIP001 IMPL_LINK( Svx3DWin, ClickFavoriteHdl, void*, p )
//STRIP001 {
//STRIP001  USHORT nItemId = aCtlFavorites.GetSelectItemId();
//STRIP001
//STRIP001  if( nItemId > 0 )
//STRIP001  {
//STRIP001      // neues, leeres Model generieren
//STRIP001      if(pModel)
//STRIP001          delete pModel;
//STRIP001      pModel = new FmFormModel();
//STRIP001      pModel->GetItemPool().FreezeIdRanges();
//STRIP001
//STRIP001      if( GalleryExplorer::GetSdrObj( GALLERY_THEME_3D, nItemId-1, pModel ) )
//STRIP001      {
//STRIP001          // VDev
//STRIP001          if(!pVDev)
//STRIP001          {
//STRIP001              pVDev = new VirtualDevice();
//STRIP001              MapMode aMapMode( MAP_100TH_MM );
//STRIP001              pVDev->SetMapMode( aMapMode );
//STRIP001          }
//STRIP001
//STRIP001          // 3D View
//STRIP001          E3dView a3DView( pModel, pVDev );
//STRIP001          a3DView.SetMarkHdlHidden(TRUE);
//STRIP001
//STRIP001          // PageView
//STRIP001          SdrPageView* pPageView = a3DView.ShowPagePgNum( 0, Point() );
//STRIP001          a3DView.MarkAll();
//STRIP001
//STRIP001          // Status der Selektion am Preview setzen, SYNCHRON
//STRIP001          SfxBoolItem aItem( SID_3D_STATE, TRUE );
//STRIP001          SfxViewFrame::Current()->GetBindings().GetDispatcher()->Execute(
//STRIP001              SID_3D_STATE, SFX_CALLMODE_SYNCHRON | SFX_CALLMODE_RECORD, &aItem, 0L );
//STRIP001
//STRIP001          // Attribute des Favoriten holen und setzen
//STRIP001          SfxItemSet aFavoriteItemSet = a3DView.Get3DAttributes();
//STRIP001
//STRIP001          if( aBtnOnly3D.IsChecked())
//STRIP001          {
//STRIP001              // throw out 2d attributes
//STRIP001              for(sal_uInt16 a(SDRATTR_START); a < SDRATTR_3D_FIRST; a++)
//STRIP001              {
//STRIP001                  if(a != SDRATTR_SHADOW
//STRIP001                      // #100997# let the linestyle attribute set as in the favourite
//STRIP001                      // since the default for 3d objects is different from 2d objects
//STRIP001                      && a != XATTR_LINESTYLE)
//STRIP001                  {
//STRIP001                      aFavoriteItemSet.ClearItem(a);
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001
//STRIP001          // #61783# Remove distance and focus from prototypes
//STRIP001          aFavoriteItemSet.ClearItem(SDRATTR_3DSCENE_DISTANCE);
//STRIP001          aFavoriteItemSet.ClearItem(SDRATTR_3DSCENE_FOCAL_LENGTH);
//STRIP001
//STRIP001          // set ItemSet
//STRIP001          BOOL bOldUpdate(bUpdate);
//STRIP001          bUpdate = FALSE;
//STRIP001
//STRIP001          if(mpRemember2DAttributes)
//STRIP001          {
//STRIP001              SfxItemSet aNewItemSet(*mpRemember2DAttributes);
//STRIP001              SfxWhichIter aIter(aFavoriteItemSet);
//STRIP001              sal_uInt16 nWhich(aIter.FirstWhich());
//STRIP001
//STRIP001              // #83024# remember original distance and focus
//STRIP001              sal_uInt32 nDVal = ((const Svx3DDistanceItem&)aNewItemSet.Get(SDRATTR_3DSCENE_DISTANCE)).GetValue();
//STRIP001              sal_uInt32 nFVal = ((const Svx3DFocalLengthItem&)aNewItemSet.Get(SDRATTR_3DSCENE_FOCAL_LENGTH)).GetValue();
//STRIP001
//STRIP001              while(nWhich)
//STRIP001              {
//STRIP001                  SfxItemState eState = aFavoriteItemSet.GetItemState(nWhich, FALSE);
//STRIP001                  if(SFX_ITEM_DONTCARE == eState)
//STRIP001                      aNewItemSet.InvalidateItem(nWhich);
//STRIP001                  else if(SFX_ITEM_SET == eState)
//STRIP001                      aNewItemSet.Put(aFavoriteItemSet.Get(nWhich, FALSE));
//STRIP001                  else
//STRIP001                      aNewItemSet.ClearItem(nWhich);
//STRIP001
//STRIP001                  nWhich = aIter.NextWhich();
//STRIP001              }
//STRIP001
//STRIP001              // #83024# restore original distance and focus
//STRIP001              aNewItemSet.Put(Svx3DDistanceItem(nDVal));
//STRIP001              aNewItemSet.Put(Svx3DFocalLengthItem(nFVal));
//STRIP001
//STRIP001              Update(aNewItemSet);
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              Update(aFavoriteItemSet);
//STRIP001          }
//STRIP001
//STRIP001          bUpdate = bOldUpdate;
//STRIP001      }
//STRIP001  }
//STRIP001  return( 0L );
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 IMPL_LINK( Svx3DWin, ChangeLightCallbackHdl, void*, p )
//STRIP001 {
//STRIP001  *pLightGroup = *aCtlLightPreview.GetPreviewControl().GetLightGroup();
//STRIP001  //aCtlPreview.SetLightGroup( pLightGroup );
//STRIP001
//STRIP001  return( 0L );
//STRIP001 }


// -----------------------------------------------------------------------

//STRIP001 IMPL_LINK( Svx3DWin, ChangeSelectionCallbackHdl, void*, p )
//STRIP001 {
//STRIP001  Base3DLightNumber eLight = aCtlLightPreview.GetPreviewControl().GetSelectedLight();
//STRIP001
//STRIP001  PushButton* pBtn = NULL;
//STRIP001
//STRIP001  switch( eLight )
//STRIP001  {
//STRIP001      case 0: pBtn = &aBtnLight1; break;
//STRIP001      case 1: pBtn = &aBtnLight2; break;
//STRIP001      case 2: pBtn = &aBtnLight3; break;
//STRIP001      case 3: pBtn = &aBtnLight4; break;
//STRIP001      case 4: pBtn = &aBtnLight5; break;
//STRIP001      case 5: pBtn = &aBtnLight6; break;
//STRIP001      case 6: pBtn = &aBtnLight7; break;
//STRIP001      case 7: pBtn = &aBtnLight8; break;
//STRIP001  }
//STRIP001
//STRIP001  if( pBtn )
//STRIP001      ClickHdl( pBtn );
//STRIP001  else
//STRIP001  {
//STRIP001      // Zustand: Keine Lampe selektiert
//STRIP001      if( aBtnLight1.IsChecked() )
//STRIP001      {
//STRIP001          aBtnLight1.Check( FALSE );
//STRIP001          aLbLight1.Enable( FALSE );
//STRIP001      }
//STRIP001      else if( aBtnLight2.IsChecked() )
//STRIP001      {
//STRIP001          aBtnLight2.Check( FALSE );
//STRIP001          aLbLight2.Enable( FALSE );
//STRIP001      }
//STRIP001      else if( aBtnLight3.IsChecked() )
//STRIP001      {
//STRIP001          aBtnLight3.Check( FALSE );
//STRIP001          aLbLight3.Enable( FALSE );
//STRIP001      }
//STRIP001      else if( aBtnLight4.IsChecked() )
//STRIP001      {
//STRIP001          aBtnLight4.Check( FALSE );
//STRIP001          aLbLight4.Enable( FALSE );
//STRIP001      }
//STRIP001      else if( aBtnLight5.IsChecked() )
//STRIP001      {
//STRIP001          aBtnLight5.Check( FALSE );
//STRIP001          aLbLight5.Enable( FALSE );
//STRIP001      }
//STRIP001      else if( aBtnLight6.IsChecked() )
//STRIP001      {
//STRIP001          aBtnLight6.Check( FALSE );
//STRIP001          aLbLight6.Enable( FALSE );
//STRIP001      }
//STRIP001      else if( aBtnLight7.IsChecked() )
//STRIP001      {
//STRIP001          aBtnLight7.Check( FALSE );
//STRIP001          aLbLight7.Enable( FALSE );
//STRIP001      }
//STRIP001      else if( aBtnLight8.IsChecked() )
//STRIP001      {
//STRIP001          aBtnLight8.Check( FALSE );
//STRIP001          aLbLight8.Enable( FALSE );
//STRIP001      }
//STRIP001      aBtnLightColor.Enable( FALSE );
//STRIP001  }
//STRIP001
//STRIP001  return( 0L );
//STRIP001 }

// -----------------------------------------------------------------------
// Methode um sicherzustellen, dass die LB auch mit einer Farbe gesetzt ist
// Liefert TRUE zurueck, falls Farbe hinzugefuegt wurde
// -----------------------------------------------------------------------
//STRIP001 BOOL Svx3DWin::LBSelectColor( ColorLB* pLb, const Color& rColor )
//STRIP001 {
//STRIP001  BOOL bRet = FALSE;
//STRIP001
//STRIP001  pLb->SetNoSelection();
//STRIP001  pLb->SelectEntry( rColor );
//STRIP001  if( pLb->GetSelectEntryCount() == 0 )
//STRIP001  {
//STRIP001      String aStr(SVX_RES(RID_SVXFLOAT3D_FIX_R));
//STRIP001
//STRIP001      aStr += String::CreateFromInt32((INT32)rColor.GetRed());
//STRIP001      aStr += sal_Unicode(' ');
//STRIP001      aStr += String(SVX_RES(RID_SVXFLOAT3D_FIX_G));
//STRIP001      aStr += String::CreateFromInt32((INT32)rColor.GetGreen());
//STRIP001      aStr += sal_Unicode(' ');
//STRIP001      aStr += String(SVX_RES(RID_SVXFLOAT3D_FIX_B));
//STRIP001      aStr += String::CreateFromInt32((INT32)rColor.GetBlue());
//STRIP001
//STRIP001      USHORT nPos = pLb->InsertEntry( rColor, aStr );
//STRIP001      pLb->SelectEntryPos( nPos );
//STRIP001      bRet = TRUE;
//STRIP001  }
//STRIP001  return( bRet );
//STRIP001 }

// -----------------------------------------------------------------------
//STRIP001 void Svx3DWin::UpdatePreview()
//STRIP001 {
//STRIP001  if( pModel == NULL )
//STRIP001      pModel = new FmFormModel();
//STRIP001
//STRIP001  if(bOnly3DChanged)
//STRIP001  {
//STRIP001      // slot executen
//STRIP001      SfxBoolItem aItem( SID_3D_STATE, TRUE );
//STRIP001      SfxViewFrame::Current()->GetBindings().GetDispatcher()->Execute(
//STRIP001          SID_3D_STATE, SFX_CALLMODE_SYNCHRON | SFX_CALLMODE_RECORD, &aItem, 0L );
//STRIP001      // Flag zuruecksetzen
//STRIP001      bOnly3DChanged = FALSE;
//STRIP001
//STRIP001      // Favorit nochmals anwenden
//STRIP001      ClickFavoriteHdl(0);
//STRIP001  }
//STRIP001
//STRIP001  // ItemSet besorgen
//STRIP001  SfxItemSet aSet( pModel->GetItemPool(), SDRATTR_START, SDRATTR_END);
//STRIP001
//STRIP001  // Attribute holen und im Preview setzen
//STRIP001  GetAttr( aSet );
//STRIP001  aCtlPreview.Set3DAttributes( aSet );
//STRIP001  aCtlFavorites.SetNoSelection();
//STRIP001 }

//////////////////////////////////////////////////////////////////////////////
// document is to be reloaded, destroy remembered ItemSet (#83951#)
//STRIP001 void Svx3DWin::DocumentReload()
//STRIP001 {
//STRIP001  if(mpRemember2DAttributes)
//STRIP001      delete mpRemember2DAttributes;
//STRIP001  mpRemember2DAttributes = 0L;
//STRIP001 }

// -----------------------------------------------------------------------
//STRIP001 void Svx3DWin::InitColorLB( const SdrModel* pDoc )
//STRIP001 {
//STRIP001  aLbLight1.Fill( pDoc->GetColorTable() );
//STRIP001  aLbLight2.CopyEntries( aLbLight1 );
//STRIP001  aLbLight3.CopyEntries( aLbLight1 );
//STRIP001  aLbLight4.CopyEntries( aLbLight1 );
//STRIP001  aLbLight5.CopyEntries( aLbLight1 );
//STRIP001  aLbLight6.CopyEntries( aLbLight1 );
//STRIP001  aLbLight7.CopyEntries( aLbLight1 );
//STRIP001  aLbLight8.CopyEntries( aLbLight1 );
//STRIP001  aLbAmbientlight.CopyEntries( aLbLight1 );
//STRIP001  aLbMatColor.CopyEntries( aLbLight1 );
//STRIP001  aLbMatEmission.CopyEntries( aLbLight1 );
//STRIP001  aLbMatSpecular.CopyEntries( aLbLight1 );
//STRIP001
//STRIP001  // Erstmal...
//STRIP001  Color aColWhite( COL_WHITE );
//STRIP001  Color aColBlack( COL_BLACK );
//STRIP001  aLbLight1.SelectEntry( aColWhite );
//STRIP001  aLbLight2.SelectEntry( aColWhite );
//STRIP001  aLbLight3.SelectEntry( aColWhite );
//STRIP001  aLbLight4.SelectEntry( aColWhite );
//STRIP001  aLbLight5.SelectEntry( aColWhite );
//STRIP001  aLbLight6.SelectEntry( aColWhite );
//STRIP001  aLbLight7.SelectEntry( aColWhite );
//STRIP001  aLbLight8.SelectEntry( aColWhite );
//STRIP001  aLbAmbientlight.SelectEntry( aColBlack );
//STRIP001  aLbMatColor.SelectEntry( aColWhite );
//STRIP001  aLbMatEmission.SelectEntry( aColBlack );
//STRIP001  aLbMatSpecular.SelectEntry( aColWhite );
//STRIP001 }

// -----------------------------------------------------------------------
//STRIP001 USHORT Svx3DWin::GetLightSource( const PushButton* pBtn )
//STRIP001 {
//STRIP001  USHORT nLight = 8;
//STRIP001
//STRIP001  if( pBtn == NULL )
//STRIP001  {
//STRIP001      if( aBtnLight1.IsChecked() )
//STRIP001          nLight = 0;
//STRIP001      else if( aBtnLight2.IsChecked() )
//STRIP001          nLight = 1;
//STRIP001      else if( aBtnLight3.IsChecked() )
//STRIP001          nLight = 2;
//STRIP001      else if( aBtnLight4.IsChecked() )
//STRIP001          nLight = 3;
//STRIP001      else if( aBtnLight5.IsChecked() )
//STRIP001          nLight = 4;
//STRIP001      else if( aBtnLight6.IsChecked() )
//STRIP001          nLight = 5;
//STRIP001      else if( aBtnLight7.IsChecked() )
//STRIP001          nLight = 6;
//STRIP001      else if( aBtnLight8.IsChecked() )
//STRIP001          nLight = 7;
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      if( pBtn == &aBtnLight1 )
//STRIP001          nLight = 0;
//STRIP001      else if( pBtn == &aBtnLight2 )
//STRIP001          nLight = 1;
//STRIP001      else if( pBtn == &aBtnLight3 )
//STRIP001          nLight = 2;
//STRIP001      else if( pBtn == &aBtnLight4 )
//STRIP001          nLight = 3;
//STRIP001      else if( pBtn == &aBtnLight5 )
//STRIP001          nLight = 4;
//STRIP001      else if( pBtn == &aBtnLight6 )
//STRIP001          nLight = 5;
//STRIP001      else if( pBtn == &aBtnLight7 )
//STRIP001          nLight = 6;
//STRIP001      else if( pBtn == &aBtnLight8 )
//STRIP001          nLight = 7;
//STRIP001  }
//STRIP001  return( nLight );
//STRIP001 };

// -----------------------------------------------------------------------
//STRIP001 ColorLB* Svx3DWin::GetLbByButton( const PushButton* pBtn )
//STRIP001 {
//STRIP001  ColorLB* pLb = NULL;
//STRIP001
//STRIP001  if( pBtn == NULL )
//STRIP001  {
//STRIP001      if( aBtnLight1.IsChecked() )
//STRIP001          pLb = &aLbLight1;
//STRIP001      else if( aBtnLight2.IsChecked() )
//STRIP001          pLb = &aLbLight2;
//STRIP001      else if( aBtnLight3.IsChecked() )
//STRIP001          pLb = &aLbLight3;
//STRIP001      else if( aBtnLight4.IsChecked() )
//STRIP001          pLb = &aLbLight4;
//STRIP001      else if( aBtnLight5.IsChecked() )
//STRIP001          pLb = &aLbLight5;
//STRIP001      else if( aBtnLight6.IsChecked() )
//STRIP001          pLb = &aLbLight6;
//STRIP001      else if( aBtnLight7.IsChecked() )
//STRIP001          pLb = &aLbLight7;
//STRIP001      else if( aBtnLight8.IsChecked() )
//STRIP001          pLb = &aLbLight8;
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      if( pBtn == &aBtnLight1 )
//STRIP001          pLb = &aLbLight1;
//STRIP001      else if( pBtn == &aBtnLight2 )
//STRIP001          pLb = &aLbLight2;
//STRIP001      else if( pBtn == &aBtnLight3 )
//STRIP001          pLb = &aLbLight3;
//STRIP001      else if( pBtn == &aBtnLight4 )
//STRIP001          pLb = &aLbLight4;
//STRIP001      else if( pBtn == &aBtnLight5 )
//STRIP001          pLb = &aLbLight5;
//STRIP001      else if( pBtn == &aBtnLight6 )
//STRIP001          pLb = &aLbLight6;
//STRIP001      else if( pBtn == &aBtnLight7 )
//STRIP001          pLb = &aLbLight7;
//STRIP001      else if( pBtn == &aBtnLight8 )
//STRIP001          pLb = &aLbLight8;
//STRIP001  }
//STRIP001  return( pLb );
//STRIP001 };

/*************************************************************************
|*
|* Ableitung vom SfxChildWindow als "Behaelter" fuer Effekte
|*
\************************************************************************/
/*N*/ __EXPORT Svx3DChildWindow::Svx3DChildWindow( Window* pParent,
/*N*/                                                        USHORT nId,
/*N*/                                                        SfxBindings* pBindings,
/*N*/                                                        SfxChildWinInfo* pInfo ) :
/*N*/   SfxChildWindow( pParent, nId )
/*N*/ {
DBG_BF_ASSERT(0, "STRIP"); //STRIP001   Svx3DWin* pWin = new Svx3DWin( pBindings, this, pParent );
//STRIP001 /*?*/    pWindow = pWin;
//STRIP001 /*?*/
//STRIP001 /*?*/    eChildAlignment = SFX_ALIGN_NOALIGNMENT;
//STRIP001 /*?*/
//STRIP001 /*?*/    pWin->Initialize( pInfo );
/*N*/ }

/*************************************************************************
|*
|* ControllerItem fuer 3DStatus
|*
\************************************************************************/
//STRIP001 Svx3DCtrlItem::Svx3DCtrlItem( USHORT nId,
//STRIP001                              Svx3DWin* pWin,
//STRIP001                              SfxBindings* pBindings) :
//STRIP001  SfxControllerItem( nId, *pBindings ),
//STRIP001  p3DWin( pWin )
//STRIP001 {
//STRIP001 }

// -----------------------------------------------------------------------
//STRIP001 void __EXPORT Svx3DCtrlItem::StateChanged( USHORT nSId,
//STRIP001                      SfxItemState eState, const SfxPoolItem* pItem )
//STRIP001 {
//STRIP001  /*
//STRIP001  if( eState >= SFX_ITEM_AVAILABLE && nSId == SID_3D_STATE )
//STRIP001  {
//STRIP001      const SfxUInt32Item* pStateItem = PTR_CAST( SfxUInt32Item, pItem );
//STRIP001      DBG_ASSERT( pStateItem, "SfxUInt32Item erwartet");
//STRIP001      UINT32 nState = pStateItem->GetValue();
//STRIP001      p3DWin->bCount = (BOOL) (nState & 3D_COUNT);
//STRIP001  }
//STRIP001  */
//STRIP001 }

/*************************************************************************
|*
|* ControllerItem fuer Status Slot SID_CONVERT_TO_3D
|*
\************************************************************************/

//STRIP001 SvxConvertTo3DItem::SvxConvertTo3DItem(UINT16 nId, SfxBindings* pBindings)
//STRIP001 :    SfxControllerItem(nId, *pBindings),
//STRIP001  bState(FALSE)
//STRIP001 {
//STRIP001 }

//STRIP001 void SvxConvertTo3DItem::StateChanged(UINT16 nId, SfxItemState eState, const SfxPoolItem* pState)
//STRIP001 {
//STRIP001  BOOL bNewState = (eState != SFX_ITEM_DISABLED);
//STRIP001  if(bNewState != bState)
//STRIP001  {
//STRIP001      bState = bNewState;
//STRIP001      SfxBoolItem aItem( SID_3D_STATE, TRUE );
//STRIP001      SfxViewFrame::Current()->GetBindings().GetDispatcher()->Execute(
//STRIP001          SID_3D_STATE, SFX_CALLMODE_ASYNCHRON|SFX_CALLMODE_RECORD, &aItem, 0L);
//STRIP001  }
//STRIP001 }


}
