/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_wrtsh1.cxx,v $
 *
 *  $Revision: 1.8 $
 *
 *  last change: $Author: hr $ $Date: 2007-01-02 18:12:05 $
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


#if STLPORT_VERSION>=321
#include <math.h>   // prevent conflict between exception and std::exception
#endif

#ifndef _HINTIDS_HXX
#include <hintids.hxx>
#endif

#ifndef _SVDVIEW_HXX //autogen
#include <bf_svx/svdview.hxx>
#endif
#ifndef _IPENV_HXX //autogen
#include <so3/ipenv.hxx>
#endif

#ifndef _WDOCSH_HXX
#include <wdocsh.hxx>
#endif

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

#ifndef _WRTSH_HXX
#include <wrtsh.hxx>
#endif
#ifndef _CMDID_H
#include <cmdid.h>
#endif
#ifndef _PAGEDESC_HXX
#include <pagedesc.hxx>
#endif
#ifndef _SWCLI_HXX
#include <swcli.hxx>
#endif
#ifndef _WVIEW_HXX
#include <wview.hxx>
#endif
#ifndef _EDTWIN_HXX
#include <edtwin.hxx>
#endif
#ifndef _VISCRS_HXX //autogen wg. SwSelPaintRects
#include <viscrs.hxx>
#endif
#ifndef _SWDTFLVR_HXX
#include <swdtflvr.hxx>
#endif
#ifndef _SWERROR_H
#include <swerror.h>
#endif
#ifndef _WRTSH_HRC
#include <wrtsh.hrc>
#endif
namespace binfilter {

#define COMMON_INI_LIST \
        rView(rShell),\
        ePageMove(MV_NO),\
        pCrsrStack(0),  \
        fnLeaveSelect(&SwWrtShell::SttLeaveSelect),\
        fnDrag(&SwWrtShell::BeginDrag),\
        fnEndDrag(&SwWrtShell::EndDrag),\
        fnSetCrsr(&SwWrtShell::SetCrsr),\
        fnKillSel(&SwWrtShell::Ignore),\
        bDestOnStack(FALSE),\
        pModeStack(0)

#define BITFLD_INI_LIST \
        bClearMark = \
        bIns = TRUE;\
        bAddMode = \
        bExtMode = \
        bInSelect = \
        bCopy = \
        bLayoutMode = \
        bNoEdit = \
        bSelWrd = \
        bSelLn = \
        bIsInClickToEdit = FALSE;



/*------------------------------------------------------------------------
 Beschreibung:   Object in die Core einfuegen.
                 Vom ClipBoard oder Insert
------------------------------------------------------------------------*/


/*------------------------------------------------------------------------
    Beschreibung: Das aktuelle selektierte OLE-Objekt wird mit dem
                  Verb in den Server geladen.
------------------------------------------------------------------------*/





/*N*/ void SwWrtShell::CalcAndSetScale( SvEmbeddedObjectRef xObj,
/*N*/                            const SwRect *pFlyPrtRect,
/*N*/                            const SwRect *pFlyFrmRect )
/*N*/ {
/*N*/   //Einstellen der Skalierung am Client. Diese ergibt sich aus der Differenz
/*N*/   //zwischen der VisArea des Objektes und der ObjArea.
/*N*/   ASSERT( xObj.Is(), "ObjectRef not  valid" );
/*N*/
/*N*/   SfxInPlaceClientRef xCli = GetView().FindIPClient( xObj, &GetView().GetEditWin() );
/*N*/   if ( !xCli.Is() || !xCli->GetEnv() )
/*N*/   {
/*N*/       //Das kann ja wohl nur ein nicht aktives Objekt sein. Diese bekommen
/*N*/       //auf Wunsch die neue Groesse als VisArea gesetzt (StarChart)
/*N*/       if( SVOBJ_MISCSTATUS_SERVERRESIZE & xObj->GetMiscStatus() )
/*N*/       {
/*N*/           SwRect aRect( pFlyPrtRect ? *pFlyPrtRect
/*N*/                       : GetAnyCurRect( RECT_FLY_PRT_EMBEDDED, 0, &xObj ));
/*N*/           if( !aRect.IsEmpty() )
/*N*/               xObj->SetVisArea( OutputDevice::LogicToLogic(
/*N*/                           aRect.SVRect(), MAP_TWIP, xObj->GetMapUnit() ));
/*N*/           return;
/*N*/       }
/*N*/       if ( SVOBJ_MISCSTATUS_ALWAYSACTIVATE & xObj->GetMiscStatus() ||
/*N*/            SVOBJ_MISCSTATUS_RESIZEONPRINTERCHANGE & xObj->GetMiscStatus() )
/*N*/       {
/*N*/           DBG_BF_ASSERT(0, "STRIP"); //STRIP001 xCli = new SwOleClient( &GetView(), &GetView().GetEditWin() );
/*N*/       }
/*N*/       else
/*N*/           return;
/*N*/   }
/*N*/
/*N*/   Size aVisArea( xObj->GetVisArea().GetSize() );
/*N*/   BOOL bSetScale100 = TRUE;
/*N*/   SvContainerEnvironment *pEnv = xCli->GetEnv();
/*N*/
/*N*/   // solange keine vernuenftige Size vom Object kommt, kann nichts
/*N*/   // skaliert werden
/*N*/   if( aVisArea.Width() && aVisArea.Height() )
/*N*/   {
/*N*/       const MapMode aTmp( MAP_TWIP );
/*N*/       aVisArea = OutputDevice::LogicToLogic( aVisArea, xObj->GetMapUnit(), aTmp);
/*N*/       Size aObjArea;
/*N*/       if ( pFlyPrtRect )
/*?*/           aObjArea = pFlyPrtRect->SSize();
/*N*/       else
/*N*/           aObjArea = GetAnyCurRect( RECT_FLY_PRT_EMBEDDED, 0, &xObj ).SSize();
/*N*/
/*N*/       // differ the aObjArea and aVisArea by 1 Pixel then set new VisArea
/*N*/       long nX, nY;
/*N*/       SwSelPaintRects::Get1PixelInLogic( *this, &nX, &nY );
/*N*/       if( !( aVisArea.Width() - nX <= aObjArea.Width() &&
/*N*/              aVisArea.Width() + nX >= aObjArea.Width() &&
/*N*/              aVisArea.Height()- nY <= aObjArea.Height()&&
/*N*/              aVisArea.Height()+ nY >= aObjArea.Height() ))
/*N*/       {
/*N*/           if( SVOBJ_MISCSTATUS_RESIZEONPRINTERCHANGE & xObj->GetMiscStatus() )
/*N*/           {
/*N*/               //This type of objects should never be resized.
/*N*/               //If this request comes from the Writer core (inaktive Object
/*N*/               //ist resized), the Object should be resized too.
/*N*/               //If this request comes from the Object itself, the Frame
/*N*/               //in the Writer core should be resized.
/*N*/               if ( pFlyPrtRect )      //Request from core?
/*N*/               {
/*?*/                   xObj->SetVisArea( OutputDevice::LogicToLogic(
/*?*/                       pFlyPrtRect->SVRect(), MAP_TWIP, xObj->GetMapUnit() ));
/*N*/               }
/*N*/               else
/*N*/               {
/*N*/                   SwRect aTmp( Point( LONG_MIN, LONG_MIN ), aVisArea );
/*N*/                   RequestObjectResize( aTmp, xObj );
/*N*/               }
/*N*/               //Der Rest erledigt sich, weil wir eh wiederkommen sollten, evtl.
/*N*/               //sogar rekursiv.
/*N*/               return;
/*N*/           }
/*N*/           else
/*?*/           {
/*?*/               const Fraction aScaleWidth ( aObjArea.Width(),  aVisArea.Width() );
/*?*/               const Fraction aScaleHeight( aObjArea.Height(), aVisArea.Height());
/*?*/               pEnv->SetSizeScale( aScaleWidth, aScaleHeight );
/*?*/               bSetScale100 = FALSE;
/*N*/           }
/*N*/       }
/*N*/   }
/*?*/
/*?*/   if( bSetScale100 )
/*?*/   {
/*?*/       const Fraction aScale( 1, 1 );
/*?*/       pEnv->SetSizeScale( aScale, aScale );
/*?*/   }
/*?*/
/*?*/   //Jetzt ist auch der guenstige Zeitpunkt die ObjArea einzustellen.
/*?*/   //Die Scalierung muss beruecksichtigt werden.
/*?*/   SwRect aArea;
/*?*/   if ( pFlyPrtRect )
/*?*/   {
/*?*/       aArea = *pFlyPrtRect;
/*?*/       aArea += pFlyFrmRect->Pos();
/*?*/   }
/*?*/   else
/*?*/   {
/*?*/       aArea = GetAnyCurRect( RECT_FLY_PRT_EMBEDDED, 0, &xObj );
/*?*/       aArea.Pos() += GetAnyCurRect( RECT_FLY_EMBEDDED, 0, &xObj ).Pos();
/*?*/   }
/*?*/   aArea.Width ( Fraction( aArea.Width()  ) / pEnv->GetScaleWidth() );
/*?*/   aArea.Height( Fraction( aArea.Height() ) / pEnv->GetScaleHeight());
/*?*/   pEnv->SetObjArea( aArea.SVRect() );
/*?*/
/*?*/   if ( SVOBJ_MISCSTATUS_ALWAYSACTIVATE & xObj->GetMiscStatus() )
/*?*/   {
/*?*/       xObj->DoConnect( xCli );
/*?*/       xObj->DoVerb();
/*?*/   }
/*N*/ }

/*N*/ SwWrtShell::SwWrtShell( SwDoc& rDoc, Window *pWin, SwView &rShell,
/*N*/                                          SwRootFrm *pRoot, const SwViewOption *pViewOpt )
/*N*/  : SwFEShell( rDoc, pWin, pRoot, pViewOpt),
/*N*/    COMMON_INI_LIST
/*N*/ {
/*N*/  BITFLD_INI_LIST
/*N*/  SET_CURR_SHELL( this );
/*N*/  SetSfxViewShell( (SfxViewShell *)&rShell );
/*N*/  SetFlyMacroLnk( LINK(this, SwWrtShell, ExecFlyMac) );
/*N*/ }

/*N*/ void SwWrtShell::ConnectObj( SvInPlaceObjectRef xIPObj, const SwRect &rPrt,
/*N*/                           const SwRect &rFrm )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/ }


/*N*/ SwWrtShell::~SwWrtShell()
/*N*/ {
/*N*/   SET_CURR_SHELL( this );
/*N*/   while(IsModePushed())
/*?*/   {DBG_BF_ASSERT(0, "STRIP");} //STRIP001     PopMode();
/*N*/   while(PopCrsr(FALSE))
/*N*/       ;
/*N*/   SwTransferable::ClearSelection( *this );
/*N*/ }
}
