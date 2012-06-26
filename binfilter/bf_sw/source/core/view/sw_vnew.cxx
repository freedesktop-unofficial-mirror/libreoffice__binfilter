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


#ifdef _MSC_VER
#pragma hdrstop
#endif

#include <rtl/logfile.hxx>

#include <horiornt.hxx>

#include <doc.hxx>
#include <docsh.hxx>
#include <viewsh.hxx>
#include <rootfrm.hxx>
#include <viewimp.hxx>
#include <viewopt.hxx>
#include <txtfrm.hxx>       // Zugriff auf TxtCache
#include <notxtfrm.hxx>
#include <fntcache.hxx>
#include <docufld.hxx>
#include <ptqueue.hxx>
#include <dview.hxx>        // SdrView
#include <ndgrf.hxx>
#include <ndindex.hxx>
#include <accessibilityoptions.hxx>
namespace binfilter {

/******************************************************************************
|*
|*  ViewShell::~ViewShell()
|*
******************************************************************************/

/*N*/ ViewShell::~ViewShell()
/*N*/ {
/*N*/   {
/*N*/       SET_CURR_SHELL( this );
/*N*/       bPaintWorks = FALSE;
/*N*/
/*N*/       //Die Animierten Grafiken abschalten!
/*N*/       if( pDoc )
/*N*/       {
/*N*/           SwNodes& rNds = pDoc->GetNodes();
/*N*/           SwGrfNode *pGNd;
/*N*/
/*N*/           SwStartNode *pStNd;
/*N*/           SwNodeIndex aIdx( *rNds.GetEndOfAutotext().StartOfSectionNode(), 1 );
/*N*/           while ( 0 != (pStNd = aIdx.GetNode().GetStartNode()) )
/*N*/           {
/*N*/               aIdx++;
/*N*/               if ( 0 != ( pGNd = aIdx.GetNode().GetGrfNode() ) )
/*N*/               {
/*N*/                   if( pGNd->IsAnimated() )
/*N*/                   {
/*N*/                       SwClientIter aIter( *pGNd );
/*N*/                       for( SwFrm* pFrm = (SwFrm*)aIter.First( TYPE(SwFrm) );
/*N*/                           pFrm; pFrm = (SwFrm*)aIter.Next() )
/*N*/                       {
/*N*/                           OSL_ENSURE( pFrm->IsNoTxtFrm(), "GraphicNode with Text?" );
/*N*/                           ((SwNoTxtFrm*)pFrm)->StopAnimation( pOut );
/*N*/                       }
/*N*/                   }
/*N*/               }
/*N*/               aIdx.Assign( *pStNd->EndOfSectionNode(), +1 );
/*N*/           }
/*N*/
/*N*/           GetDoc()->StopNumRuleAnimations( pOut );
/*N*/       }
/*N*/
/*N*/       delete pImp; //Erst loeschen, damit die LayoutViews vernichtet werden.
/*N*/       pImp = 0;   // Set to zero, because ~SwFrm relies on it.
/*N*/
/*N*/       if ( pDoc )
/*N*/       {
/*N*/           if( !pDoc->RemoveLink() )
/*?*/               delete pDoc, pDoc = 0;
/*N*/       }
/*N*/
/*N*/       delete pOpt;
/*N*/
/*N*/       //Format-Cache zurueckschrauben.
/*N*/       if ( SwTxtFrm::GetTxtCache()->GetCurMax() > 250 )
/*N*/           SwTxtFrm::GetTxtCache()->DecreaseMax( 100 );
/*N*/
/*N*/       //Ggf. aus der PaintQueue entfernen lassen
/*N*/       SwPaintQueue::Remove( this );
/*N*/
/*N*/       OSL_ENSURE( !nStartAction, "EndAction() pending." );
/*N*/   }
/*N*/
/*N*/     delete mpTmpRef;
/*N*/     delete pAccOptions;
/*N*/ }

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
