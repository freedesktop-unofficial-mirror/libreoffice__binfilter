/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svx_impgrfll.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-27 21:36:01 $
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





#ifndef _SV_METAACT_HXX
#include <vcl/metaact.hxx>
#endif



#include "svdobj.hxx"

#ifndef _XDEF_HXX
#include "xdef.hxx"
#endif

#include "xattr.hxx"
#include "xoutx.hxx"

#include "svdoimp.hxx"
#include "svdattr.hxx"
namespace binfilter {


///////////////////////////////////////////////////////////////////////////////

#define ITEMVALUE(ItemSet,Id,Cast)  ((const Cast&)(ItemSet).Get(Id)).GetValue()

////////////////////////////////////////////////////////////////////////////////////////////////////

// #100127# Bracket filled output with a comment, if recording a Mtf
/*N*/ ImpGraphicFill::ImpGraphicFill( const SdrObject&      rObj,
/*N*/                                 const ExtOutputDevice&    rXOut,
/*N*/                                 const SfxItemSet&         rFillItemSet,
/*N*/                                 bool                  bIsShadow       ) :
/*N*/     mrObj( rObj ),
/*N*/     mrXOut( rXOut ),
/*N*/     mbCommentWritten( false )
/*N*/ {
/*N*/   const SfxItemSet& rSet = rObj.GetItemSet();
/*N*/     XFillStyle eFillStyle( ITEMVALUE( rFillItemSet, XATTR_FILLSTYLE, XFillStyleItem ) );
/*N*/     XGradient aGradient( ITEMVALUE( rFillItemSet, XATTR_FILLGRADIENT, XFillGradientItem ) );
/*N*/     XHatch aHatch( ITEMVALUE( rFillItemSet, XATTR_FILLHATCH, XFillHatchItem ) );
/*N*/
/*N*/   sal_Int32 nDX( ((SdrShadowXDistItem&)(rSet.Get(SDRATTR_SHADOWXDIST))).GetValue() );
/*N*/   sal_Int32 nDY( ((SdrShadowYDistItem&)(rSet.Get(SDRATTR_SHADOWYDIST))).GetValue() );
/*N*/
/*N*/     GDIMetaFile* pMtf=NULL;
/*N*/     if( eFillStyle != XFILL_NONE &&
/*N*/         (pMtf=mrXOut.GetOutDev()->GetConnectMetaFile()) )
/*?*/     {DBG_BF_ASSERT(0, "STRIP");//STRIP001
/*?*/     }
/*N*/ }

// #100127# Bracket filled output with a comment, if recording a Mtf
/*N*/ ImpGraphicFill::~ImpGraphicFill()
/*N*/ {
/*N*/     GDIMetaFile* pMtf=NULL;
/*N*/     if( mbCommentWritten &&
/*N*/         (pMtf=mrXOut.GetOutDev()->GetConnectMetaFile()) )
/*N*/     {
/*?*/         pMtf->AddAction( new MetaCommentAction( "XPATHFILL_SEQ_END" ) );
/*N*/     }
/*N*/ }

///////////////////////////////////////////////////////////////////////////////

// #104609# Extracted from XOutputDevice::ImpCalcBmpFillStartValues
}
