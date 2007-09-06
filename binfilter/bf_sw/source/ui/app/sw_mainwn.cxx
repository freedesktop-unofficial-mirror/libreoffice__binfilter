/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_mainwn.cxx,v $
 *
 *  $Revision: 1.7 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 13:07:24 $
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


#ifdef _MSC_VER
#pragma hdrstop
#endif


#ifndef _SFX_PROGRESS_HXX //autogen
#include <bf_sfx2/progress.hxx>
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
