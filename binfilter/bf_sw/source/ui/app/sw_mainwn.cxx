/*************************************************************************
 *
 *  $RCSfile: sw_mainwn.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: aw $ $Date: 2004-02-13 14:30:56 $
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


#pragma hdrstop


#ifndef _SHL_HXX //autogen
#include <tools/shl.hxx>
#endif
#ifndef _STRING_HXX //autogen
#include <tools/string.hxx>
#endif
#ifndef _SVARRAY_HXX
#include <svtools/svstdarr.hxx>
#endif
#ifndef _SFX_PROGRESS_HXX //autogen
#include <bf_sfx2/progress.hxx>
#endif
#ifndef _RESID_HXX //autogen
#include <tools/resid.hxx>
#endif

#ifndef _SWDOCSH_HXX //autogen
#include <docsh.hxx>
#endif
#ifndef _SWMODULE_HXX //autogen
#include <swmodule.hxx>
#endif
#include "swtypes.hxx"
namespace binfilter {

class SwDocShell;

struct SwProgress
{
    long nStartValue,
         nStartCount;
    SwDocShell  *pDocShell;
    SfxProgress *pProgress;
};

static SvPtrarr *pProgressContainer = 0;

/*N*/ SwProgress *lcl_SwFindProgress( SwDocShell *pDocShell )
/*N*/ {
/*N*/   for ( USHORT i = 0; i < pProgressContainer->Count(); ++i )
/*N*/   {
/*N*/       SwProgress *pTmp = (SwProgress*)(*pProgressContainer)[i];
/*N*/       if ( pTmp->pDocShell == pDocShell )
/*N*/           return pTmp;
/*N*/   }
/*N*/   return 0;
/*N*/ }


/*N*/ void StartProgress( USHORT nMessResId, long nStartValue, long nEndValue,
/*N*/                   SwDocShell *pDocShell )
/*N*/ {
/*N*/   if( !SW_MOD()->IsEmbeddedLoadSave() )
/*N*/   {
/*N*/       SwProgress *pProgress = 0;
/*N*/
/*N*/       if ( !pProgressContainer )
/*N*/           pProgressContainer = new SvPtrarr( 2, 2 );
/*N*/       else
/*N*/       {
/*?*/           if ( 0 != (pProgress = lcl_SwFindProgress( pDocShell )) )
/*?*/               ++pProgress->nStartCount;
/*N*/       }
/*N*/       if ( !pProgress )
/*N*/       {
/*N*/           pProgress = new SwProgress;
/*N*/           pProgress->pProgress = new SfxProgress( pDocShell,
/*N*/                                                   SW_RESSTR(nMessResId),
/*N*/                                                   nEndValue - nStartValue,
/*N*/                                                   FALSE,
/*N*/                                                   TRUE );
/*N*/           pProgress->nStartCount = 1;
/*N*/           pProgress->pDocShell = pDocShell;
/*N*/           pProgressContainer->Insert( (void*)pProgress, 0 );
/*N*/       }
/*N*/       pProgress->nStartValue = nStartValue;
/*N*/   }
/*N*/ }


/*N*/ void SetProgressState( long nPosition, SwDocShell *pDocShell )
/*N*/ {
/*N*/   if( pProgressContainer && !SW_MOD()->IsEmbeddedLoadSave() )
/*N*/   {
/*N*/       SwProgress *pProgress = lcl_SwFindProgress( pDocShell );
/*N*/       if ( pProgress )
/*N*/           pProgress->pProgress->SetState(nPosition - pProgress->nStartValue);
/*N*/   }
/*N*/ }


/*N*/ void EndProgress( SwDocShell *pDocShell )
/*N*/ {
/*N*/   if( pProgressContainer && !SW_MOD()->IsEmbeddedLoadSave() )
/*N*/   {
/*N*/       SwProgress *pProgress = 0;
/*N*/       USHORT i;
/*N*/       for ( i = 0; i < pProgressContainer->Count(); ++i )
/*N*/       {
/*N*/           SwProgress *pTmp = (SwProgress*)(*pProgressContainer)[i];
/*N*/           if ( pTmp->pDocShell == pDocShell )
/*N*/           {
/*N*/               pProgress = pTmp;
/*N*/               break;
/*N*/           }
/*N*/       }
/*N*/
/*N*/       if ( pProgress && 0 == --pProgress->nStartCount )
/*N*/       {
/*N*/           pProgress->pProgress->Stop();
/*N*/           pProgressContainer->Remove( i );
/*N*/           delete pProgress->pProgress;
/*N*/           delete pProgress;
/*N*/           if ( !pProgressContainer->Count() )
/*N*/               delete pProgressContainer, pProgressContainer = 0;
/*N*/       }
/*N*/   }
/*N*/ }


//STRIP001 void SetProgressText( USHORT nId, SwDocShell *pDocShell )
//STRIP001 {
//STRIP001  if( pProgressContainer && !SW_MOD()->IsEmbeddedLoadSave() )
//STRIP001  {
//STRIP001      SwProgress *pProgress = lcl_SwFindProgress( pDocShell );
//STRIP001      if ( pProgress )
//STRIP001          pProgress->pProgress->SetStateText( 0, SW_RESSTR(nId) );
//STRIP001  }
//STRIP001 }


/*N*/ void RescheduleProgress( SwDocShell *pDocShell )
/*N*/ {
/*N*/   if( pProgressContainer && !SW_MOD()->IsEmbeddedLoadSave() )
/*N*/   {
/*N*/       SwProgress *pProgress = lcl_SwFindProgress( pDocShell );
/*N*/       if ( pProgress )
/*N*/           pProgress->pProgress->Reschedule();
/*N*/   }
/*N*/ }

}
