/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_vprint.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-27 23:24:46 $
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


#pragma hdrstop

#ifndef _HINTIDS_HXX
#include <hintids.hxx>
#endif

#ifndef _SFX_PRNMON_HXX
#include <bf_sfx2/prnmon.hxx>
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

//Klasse zum Speichern einiger Druckereinstellungen

// saves some settings from the draw view








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



/******************************************************************************
 *  Methode     :   void SetSwVisArea( ViewShell *pSh, Point aPrtOffset, ...
 *  Beschreibung:
 *  Erstellt    :   OK 04.11.94 16:27
 *  Aenderung   :
 ******************************************************************************/


/******************************************************************************
 *  Methode     :   struct _PostItFld : public _SetGetExpFld
 *  Beschreibung:   Update an das PostItFeld
 *  Erstellt    :   OK 07.11.94 10:18
 *  Aenderung   :
 ******************************************************************************/




/******************************************************************************
 *  Methode     :   void lcl_GetPostIts( SwDoc* pDoc, _SetGetExpFlds& ...
 *  Beschreibung:
 *  Erstellt    :   OK 07.11.94 10:20
 *  Aenderung   :
 ******************************************************************************/



/******************************************************************************
 *  Methode     :   void lcl_FormatPostIt( SwDoc* pDoc, SwPaM& aPam, ...
 *  Beschreibung:
 *  Erstellt    :   OK 07.11.94 10:20
 *  Aenderung   :
 ******************************************************************************/



/******************************************************************************
 *  Methode     :   void lcl_PrintPostIts( ViewShell* pPrtShell )
 *  Beschreibung:
 *  Erstellt    :   OK 07.11.94 10:21
 *  Aenderung   :   MA 10. May. 95
 ******************************************************************************/



/******************************************************************************
 *  Methode     :   void lcl_PrintPostItsEndDoc( ViewShell* pPrtShell, ...
 *  Beschreibung:
 *  Erstellt    :   OK 07.11.94 10:21
 *  Aenderung   :   MA 10. May. 95
 ******************************************************************************/



/******************************************************************************
 *  Methode     :   void lcl_PrintPostItsEndPage( ViewShell* pPrtShell, ...
 *  Beschreibung:
 *  Erstellt    :   OK 07.11.94 10:22
 *  Aenderung   :
 ******************************************************************************/



/******************************************************************************
 *  Methode     :   void ViewShell::SetPrt( SfxPrinter *pNew, OutputDevice *pPDFOut )
 *  Beschreibung:
 *  Erstellt    :   OK 07.11.94 10:22
 *  Aenderung   :
 ******************************************************************************/

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


/******************************************************************************
 *  Methode     :   void ViewShell::ChgAllPageOrientation
 *  Erstellt    :   MA 08. Aug. 95
 *  Aenderung   :
 ******************************************************************************/



/******************************************************************************
 *  Methode     :   void ViewShell::ChgAllPageOrientation
 *  Erstellt    :   MA 08. Aug. 95
 *  Aenderung   :
 ******************************************************************************/



/******************************************************************************
 *  Methode     :   void ViewShell::CalcPagesForPrint( short nMax, BOOL ...
 *  Beschreibung:
 *  Erstellt    :   OK 04.11.94 15:33
 *  Aenderung   :   MA 07. Jun. 95
 ******************************************************************************/







/******************************************************************************/

/*N*/ SwDoc * ViewShell::FillPrtDoc( SwDoc *pPrtDoc, const SfxPrinter* pPrt)
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); return NULL;//STRIP001
/*N*/ }

/******************************************************************************
 *  Methode     :   void ViewShell::Prt( const SwPrtOptions& rOptions, SfxProgress& rProgress,
 *                                       OutputDevice *pPDFOut )
 *  Beschreibung:
 *  Erstellt    :   OK 04.11.94 15:33
 *  Aenderung   :   MA 10. May. 95
 ******************************************************************************/


/*N*/ BOOL ViewShell::Prt( SwPrtOptions& rOptions, SfxProgress& rProgress,
/*N*/                      OutputDevice *pPDFOut )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001
/*N*/ }

/******************************************************************************
 *  Methode     :   PrtOle2()
 *  Beschreibung:
 *  Erstellt    :   PK 07.12.94
 *  Aenderung   :   MA 16. Feb. 95
 ******************************************************************************/




/******************************************************************************
 *  Methode     :   IsAnyFieldInDoc()
 *  Beschreibung:   Stellt fest, ob im DocNodesArray Felder verankert sind
 *  Erstellt    :   JP 27.07.95
 *  Aenderung   :   JP 10.12.97
 ******************************************************************************/






/******************************************************************************
 *  Klasse      :   SwPrtOptSave
 *  Erstellt    :   AMA 12.07.95
 *  Aenderung   :   AMA 12.07.95
 *  Holt sich im Ctor folgende Einstellungen des Druckers, die im Dtor dann
 *  wieder im Drucker gesetzt werden (falls sie sich ueberhaupt geaendert haben)
 *  - PaperBin - Orientation - PaperSize -
 ******************************************************************************/








/******************************************************************************
 *  SwDrawViewSave
 *
 *  Saves some settings at the draw view
 ******************************************************************************/




// OD 09.01.2003 #i6467# - method also called for page preview
}
