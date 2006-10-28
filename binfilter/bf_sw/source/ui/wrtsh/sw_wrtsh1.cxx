/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_wrtsh1.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 01:35:44 $
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
/*N*/           xCli = new SwOleClient( &GetView(), &GetView().GetEditWin() );
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



/*N*/ void SwWrtShell::ConnectObj( SvInPlaceObjectRef xIPObj, const SwRect &rPrt,
/*N*/                           const SwRect &rFrm )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/ }


/*------------------------------------------------------------------------
 Beschreibung:  Einfuegen harter Seitenumbruch;
                Selektionen werden ueberschrieben
------------------------------------------------------------------------*/



/*------------------------------------------------------------------------
 Beschreibung:  Einfuegen harter Zeilenumbruch;
                Selektionen werden ueberschrieben
------------------------------------------------------------------------*/


/*------------------------------------------------------------------------
 Beschreibung:  Einfuegen harter Spaltenumbruch;
                Selektionen werden ueberschrieben
------------------------------------------------------------------------*/



/*------------------------------------------------------------------------
 Beschreibung:  Einfuegen Fussnote
 Parameter:     rStr -- optionales Fussnotenzeichen
------------------------------------------------------------------------*/


/*------------------------------------------------------------------------
 Beschreibung:  SplitNode; hier auch, da
                    - selektierter Inhalt geloescht wird;
                    - der Cursorstack gfs. zurueckgesetzt wird.
------------------------------------------------------------------------*/



/*------------------------------------------------------------------------
 Beschreibung:  Numerierung anschalten
 Parameter:     Optionale Angabe eines Namens fuer die benannte Liste;
                dieser bezeichnet eine Position, wenn er in eine
                Zahl konvertierbar ist und kleiner ist als nMaxRules.
-------------------------------------------------------------------------*/


// zum Testen der CharFormate an der Numerierung
// extern void SetNumChrFmt( SwWrtShell*, SwNumRules& );


/*------------------------------------------------------------------------
 Beschreibung:  Default-Bulletliste erfragen
------------------------------------------------------------------------*/


/*--------------------------------------------------

--------------------------------------------------*/
/*N*/ int SwWrtShell::GetSelectionType() const
/*N*/ {
/*N*/   // ContentType kann nicht ermittelt werden innerhalb einer
/*N*/   // Start-/Endactionklammerung.
/*N*/   // Da es keinen ungueltigen Wert gibt, wird TEXT geliefert.
/*N*/   // Der Wert ist egal, da in EndAction ohnehin aktualisiert wird.
/*N*/
/*N*/   if ( BasicActionPend() )
/*N*/       return IsSelFrmMode() ? SEL_FRM : SEL_TXT;
/*N*/
/*N*/ //    if ( IsTableMode() )
/*N*/ //        return SEL_TBL | SEL_TBL_CELLS;
/*N*/
/*N*/   SwView &rView = ((SwView&)GetView());
/*N*/   USHORT nCnt;
/*N*/
/*N*/   // Rahmen einfuegen ist kein DrawMode
/*N*/   if ( !rView.GetEditWin().IsFrmAction() &&
/*N*/           (IsObjSelected() || (rView.IsDrawMode() && !IsFrmSelected()) ))
/*N*/   {
/*?*/       if (GetDrawView()->IsTextEdit())
/*?*/           nCnt = SEL_DRW_TXT;
/*?*/       else
/*?*/       {
/*?*/           DBG_BF_ASSERT(0, "STRIP"); //STRIP001 if (GetView().IsFormMode())   // Nur Forms selektiert
/*?*/       }
/*?*/
/*?*/       return nCnt;
/*N*/   }
/*N*/
/*N*/   nCnt = GetCntType();
/*N*/
/*N*/   if ( IsFrmSelected() )
/*N*/   {
/*?*/       if (rView.IsDrawMode())
/*?*/           rView.LeaveDrawCreate();    // Aufraeumen (Bug #45639)
/*?*/       if ( !(nCnt & (CNT_GRF | CNT_OLE)) )
/*?*/           return SEL_FRM;
/*N*/   }
/*N*/
/*N*/   if ( IsCrsrInTbl() )
/*N*/       nCnt |= SEL_TBL;
/*N*/
/*N*/   if ( IsTableMode() )
/*N*/       nCnt |= (SEL_TBL | SEL_TBL_CELLS);
/*N*/
/*N*/   if ( GetCurNumRule() )
/*N*/       nCnt |= SEL_NUM;
/*N*/
/*N*/   return nCnt;
/*N*/ }

/*------------------------------------------------------------------------
 Beschreibung:  Finden der TextCollection mit dem Name rCollname
 Return:                Pointer auf die Collection oder 0, wenn keine
                                TextCollection mit diesem Namen existiert oder
                                diese eine Defaultvorlage ist.
------------------------------------------------------------------------*/


/*------------------------------------------------------------------------
 Beschreibung:  Finden der Zeichenvorlage mit dem Name rCollname
 Return:                Pointer auf die Collection oder 0, wenn keine
                                Zeichenvorlage mit diesem Namen existiert oder
                                diese eine Defaultvorlage oder automatische Vorlage ist.
------------------------------------------------------------------------*/




/*------------------------------------------------------------------------
 Beschreibung:  Finden des Tabellenformates mit dem Name rFmtname
 Return:                Pointer auf das Format oder 0, wenn kein
                                Rahmenformat mit diesem Namen existiert oder
                                dieses eine Defaultformat oder automatisches Format ist.
------------------------------------------------------------------------*/





/*------------------------------------------------------------------------
 Beschreibung:  Anwenden der Vorlagen
------------------------------------------------------------------------*/




/*------------------------------------------------------------------------
 Beschreibung:  Zugriff Vorlagen
------------------------------------------------------------------------*/



/*N*/ String SwWrtShell::GetCurPageStyle( const BOOL bCalcFrm ) const
/*N*/ {
/*N*/   return GetPageDesc(GetCurPageDesc( bCalcFrm )).GetName();
/*N*/ }

/*------------------------------------------------------------------------
 Beschreibung:  Aktuelle Vorlage anhand der geltenden Attribute aendern
------------------------------------------------------------------------*/





/*-----------------12.03.97 12.24-------------------

--------------------------------------------------*/





/*
 * eine Art kontrollierter copy ctor
 */

/*?*/ SwWrtShell::SwWrtShell( SwWrtShell& rSh, Window *pWin, SwView &rShell )
/*?*/   : SwFEShell( rSh, pWin ),
/*?*/    COMMON_INI_LIST
/*?*/ {
/*?*/   BITFLD_INI_LIST
/*?*/   SET_CURR_SHELL( this );
/*?*/   SetSfxViewShell( (SfxViewShell *)&rShell );
/*?*/   SetFlyMacroLnk( LINK(this, SwWrtShell, ExecFlyMac) );
/*?*/ }


/*N*/ SwWrtShell::SwWrtShell( SwDoc& rDoc, Window *pWin, SwView &rShell,
/*N*/                       SwRootFrm *pRoot, const SwViewOption *pViewOpt )
/*N*/   : SwFEShell( rDoc, pWin, pRoot, pViewOpt),
/*N*/     COMMON_INI_LIST
/*N*/ {
/*N*/   BITFLD_INI_LIST
/*N*/   SET_CURR_SHELL( this );
/*N*/   SetSfxViewShell( (SfxViewShell *)&rShell );
/*N*/   SetFlyMacroLnk( LINK(this, SwWrtShell, ExecFlyMac) );
/*N*/ }

/*
 * ctor
 */



/*N*/ SwWrtShell::~SwWrtShell()
/*N*/ {
/*N*/   SET_CURR_SHELL( this );
/*N*/   while(IsModePushed())
/*?*/   {DBG_BF_ASSERT(0, "STRIP");} //STRIP001     PopMode();
/*N*/   while(PopCrsr(FALSE))
/*N*/       ;
/*N*/   SwTransferable::ClearSelection( *this );
/*N*/ }

















/*--------------------------------------------------------------------
    Beschreibung:
 --------------------------------------------------------------------*/






    // die Core erzeugt eine Selektion, das SttSelect muss gerufen werden

// --------------
/*N*/ void SwWrtShell::ChgDBData(const SwDBData& aDBData)
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/ }




}
