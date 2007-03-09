/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_vprint.cxx,v $
 *
 *  $Revision: 1.8 $
 *
 *  last change: $Author: obo $ $Date: 2007-03-09 16:40:47 $
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


#ifndef _HINTIDS_HXX
#include <hintids.hxx>
#endif

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

#ifndef _FESH_HXX
#include <fesh.hxx>
#endif
#ifndef _VIEWIMP_HXX
#include <viewimp.hxx>      // Imp->SetFirstVisPageInvalid()
#endif
#ifndef _STATSTR_HRC
#include <statstr.hrc>      //      -- " --
#endif
#ifndef _PTQUEUE_HXX
#include <ptqueue.hxx>
#endif

#include <bf_sfx2/printer.hxx>

namespace binfilter {

#define JOBSET_ERR_DEFAULT          0
#define JOBSET_ERR_ERROR            1
#define JOBSET_ERR_ISSTARTET        2

//--------------------------------------------------------------------
//Klasse zum Puffern von Paints
class SwQueuedPaint
{
public:
    SwQueuedPaint *pNext;
    ViewShell      *pSh;
    SwRect          aRect;

    SwQueuedPaint( ViewShell *pNew, const SwRect &rRect ) :
        pNext( 0 ),
        pSh( pNew ),
        aRect( rRect )
    {}
};

SwQueuedPaint *SwPaintQueue::pQueue = 0;

/*N*/ void SwPaintQueue::Remove( ViewShell *pSh )
/*N*/ {
/*N*/   SwQueuedPaint *pPt;
/*N*/   if ( 0 != (pPt = pQueue) )
/*N*/   {
/*?*/       SwQueuedPaint *pPrev = 0;
/*?*/       while ( pPt && pPt->pSh != pSh )
/*?*/       {
/*?*/           pPrev = pPt;
/*?*/           pPt = pPt->pNext;
/*?*/       }
/*?*/       if ( pPt )
/*?*/       {
/*?*/           if ( pPrev )
/*?*/               pPrev->pNext = pPt->pNext;
/*?*/           else if ( pPt == pQueue )
/*?*/               pQueue = 0;
/*?*/           delete pPt;
/*?*/       }
/*N*/   }
/*N*/ }

/*M*/ void ViewShell::InitPrt( SfxPrinter *pPrt, OutputDevice *pPDFOut )
/*M*/ {
/*M*/   //Fuer den Printer merken wir uns einen negativen Offset, der
/*M*/   //genau dem Offset de OutputSize entspricht. Das ist notwendig,
/*M*/   //weil unser Ursprung der linken ober Ecke der physikalischen
/*M*/   //Seite ist, die Ausgaben (SV) aber den Outputoffset als Urstprung
/*M*/   //betrachten.
/*M*/     OutputDevice *pTmpDev = pPDFOut ? pPDFOut : (OutputDevice *) pPrt;
/*M*/     if ( pTmpDev )
/*M*/   {
/*M*/         aPrtOffst = pPrt ? pPrt->GetPageOffset() : Point();
/*M*/
/*M*/         aPrtOffst += pTmpDev->GetMapMode().GetOrigin();
/*M*/         MapMode aMapMode( pTmpDev->GetMapMode() );
/*M*/       aMapMode.SetMapUnit( MAP_TWIP );
/*M*/         pTmpDev->SetMapMode( aMapMode );
/*M*/         pTmpDev->SetLineColor();
/*M*/         pTmpDev->SetFillColor();
/*M*/   }
/*M*/   else
/*M*/       aPrtOffst.X() = aPrtOffst.Y() = 0;
/*M*/
/*M*/   if ( !pWin )
/*M*/         pOut = pTmpDev;    //Oder was sonst?
/*M*/ }
}
