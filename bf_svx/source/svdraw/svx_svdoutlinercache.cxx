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


#include "svdoutlinercache.hxx"
#include "svdoutl.hxx"
#include "svdmodel.hxx"
namespace binfilter {

/*N*/ extern SdrOutliner* SdrMakeOutliner( USHORT nOutlinerMode, SdrModel* pModel );

/*N*/ SdrOutlinerCache::SdrOutlinerCache( SdrModel* pModel )
/*N*/ : mpModel( pModel ),
/*N*/   mpModeOutline( NULL ),
/*N*/   mpModeText( NULL )
/*N*/ {
/*N*/ }

/*N*/ SdrOutliner* SdrOutlinerCache::createOutliner( sal_uInt16 nOutlinerMode )
/*N*/ {
/*N*/   SdrOutliner* pOutliner = NULL;
/*N*/
/*N*/   if( (OUTLINERMODE_OUTLINEOBJECT == nOutlinerMode) && mpModeOutline )
/*N*/   {
/*N*/       pOutliner = mpModeOutline;
/*N*/       mpModeOutline = NULL;
/*N*/   }
/*N*/   else if( (OUTLINERMODE_TEXTOBJECT == nOutlinerMode) && mpModeText )
/*N*/   {
/*N*/       pOutliner = mpModeText;
/*N*/       mpModeText = NULL;
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       pOutliner = SdrMakeOutliner( nOutlinerMode, mpModel );
/*N*/       Outliner& aDrawOutliner = mpModel->GetDrawOutliner();
/*N*/       pOutliner->SetCalcFieldValueHdl( aDrawOutliner.GetCalcFieldValueHdl() );
/*N*/   }
/*N*/
/*N*/   return pOutliner;
/*N*/ }

/*N*/ SdrOutlinerCache::~SdrOutlinerCache()
/*N*/ {
/*N*/   if( mpModeOutline )
/*N*/   {
/*N*/       delete mpModeOutline;
/*N*/       mpModeOutline = NULL;
/*N*/   }
/*N*/
/*N*/   if( mpModeText )
/*N*/   {
/*N*/       delete mpModeText;
/*N*/       mpModeText = NULL;
/*N*/   }
/*N*/ }

/*N*/ void SdrOutlinerCache::disposeOutliner( SdrOutliner* pOutliner )
/*N*/ {
/*N*/   if( pOutliner )
/*N*/   {
/*N*/       USHORT nOutlMode = pOutliner->GetOutlinerMode();
/*N*/
/*N*/       if( (OUTLINERMODE_OUTLINEOBJECT == nOutlMode) && (NULL == mpModeOutline) )
/*N*/       {
/*N*/           mpModeOutline = pOutliner;
/*N*/           pOutliner->Clear();
/*N*/           pOutliner->SetVertical( false );
/*N*/       }
/*N*/       else if( (OUTLINERMODE_TEXTOBJECT == nOutlMode) && (NULL == mpModeText) )
/*N*/       {
/*N*/           mpModeText = pOutliner;
/*N*/           pOutliner->Clear();
/*N*/           pOutliner->SetVertical( false );
/*N*/       }
/*N*/       else
/*N*/       {
/*N*/           delete pOutliner;
/*N*/       }
/*N*/   }
/*N*/ }


}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
