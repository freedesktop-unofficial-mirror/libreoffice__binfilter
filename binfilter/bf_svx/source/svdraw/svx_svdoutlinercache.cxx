/*************************************************************************
 *
 *  $RCSfile: svx_svdoutlinercache.cxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:22:16 $
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


#include "svdoutlinercache.hxx"
#include "svdoutl.hxx"
#include "svdmodel.hxx"

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


