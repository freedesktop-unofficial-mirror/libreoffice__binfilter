/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file incorporates work covered by the following license notice:
 *
 *   Licensed to the Apache Software Foundation (ASF) under one or more
 *   contributor license agreements. See the NOTICE file distributed
 *   with this work for additional information regarding copyright
 *   ownership. The ASF licenses this file to you under the Apache
 *   License, Version 2.0 (the "License"); you may not use this file
 *   except in compliance with the License. You may obtain a copy of
 *   the License at http://www.apache.org/licenses/LICENSE-2.0 .
 */

#include <vcl/metaact.hxx>



#include "svdobj.hxx"

#include "xdef.hxx"

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
/*N*/                                 bool                  /*bIsShadow*/ ) :
/*N*/     mrObj( rObj ),
/*N*/     mrXOut( rXOut ),
/*N*/     mbCommentWritten( false )
/*N*/ {
/*N*/     XFillStyle eFillStyle( ITEMVALUE( rFillItemSet, XATTR_FILLSTYLE, XFillStyleItem ) );
/*N*/     XGradient aGradient( ITEMVALUE( rFillItemSet, XATTR_FILLGRADIENT, XFillGradientItem ) );
/*N*/     XHatch aHatch( ITEMVALUE( rFillItemSet, XATTR_FILLHATCH, XFillHatchItem ) );
/*N*/
/*N*/     if( eFillStyle != XFILL_NONE && mrXOut.GetOutDev()->GetConnectMetaFile() )
/*?*/     {DBG_BF_ASSERT(0, "STRIP");
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

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
