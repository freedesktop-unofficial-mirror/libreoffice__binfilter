/*************************************************************************
 *
 *  $RCSfile: sw_paintfrm.cxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: aw $ $Date: 2003-10-02 15:27:18 $
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

#define ITEMID_BOXINFO      SID_ATTR_BORDER_INNER
#include <hintids.hxx>

#ifndef _SOUND_HXX //autogen
#include <vcl/sound.hxx>
#endif
#ifndef _POLY_HXX //autogen
#include <vcl/poly.hxx>
#endif
#define _SVSTDARR_LONGS
#include <svtools/svstdarr.hxx>

#ifndef _XOUTBMP_HXX //autogen
#include <bf_svx/xoutbmp.hxx>
#endif
#ifndef _SFX_PROGRESS_HXX //autogen
#include <bf_sfx2/progress.hxx>
#endif
#ifndef _SVX_BRSHITEM_HXX //autogen
#include <bf_svx/brshitem.hxx>
#endif
#ifndef _SVX_OPAQITEM_HXX //autogen
#include <bf_svx/opaqitem.hxx>
#endif
#ifndef _SVX_PRNTITEM_HXX //autogen
#include <bf_svx/prntitem.hxx>
#endif
#ifndef _SVX_BOXITEM_HXX //autogen
#include <bf_svx/boxitem.hxx>
#endif
#ifndef _SVX_SHADITEM_HXX //autogen
#include <bf_svx/shaditem.hxx>
#endif
#ifndef _GRAPH_HXX //autogen
#include <vcl/graph.hxx>
#endif
#ifndef _SVDPAGV_HXX //autogen
#include <bf_svx/svdpagv.hxx>
#endif
#ifndef SW_TGRDITEM_HXX
#include <tgrditem.hxx>
#endif


#ifndef _FMTSRND_HXX //autogen
#include <fmtsrnd.hxx>
#endif
#ifndef _FMTCLDS_HXX //autogen
#include <fmtclds.hxx>
#endif
#ifndef _SHL_HXX
#include <tools/shl.hxx>
#endif

#ifndef _SWMODULE_HXX
#include <swmodule.hxx>
#endif
#ifndef _ROOTFRM_HXX
#include <rootfrm.hxx>
#endif
#ifndef _PAGEFRM_HXX
#include <pagefrm.hxx>
#endif
#ifndef _CNTFRM_HXX
#include <cntfrm.hxx>
#endif
#ifndef _VIEWSH_HXX
#include <viewsh.hxx>
#endif
#ifndef _SECTION_HXX
#include <section.hxx>
#endif
#ifndef _SECTFRM_HXX
#include <sectfrm.hxx>
#endif
#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _VIEWIMP_HXX
#include <viewimp.hxx>
#endif
#ifndef _SWATRSET_HXX
#include <swatrset.hxx>
#endif
#ifndef _DFLYOBJ_HXX
#include <dflyobj.hxx>
#endif
#ifndef _FLYFRM_HXX
#include <flyfrm.hxx>
#endif
#ifndef _FRMTOOL_HXX
#include <frmtool.hxx>
#endif
#ifndef _VIEWOPT_HXX
#include <viewopt.hxx>
#endif
#ifndef _DVIEW_HXX
#include <dview.hxx>
#endif
#ifndef _DCONTACT_HXX
#include <dcontact.hxx>
#endif
#ifndef _TXTFRM_HXX
#include <txtfrm.hxx>
#endif
#ifndef _FTNFRM_HXX
#include <ftnfrm.hxx>
#endif
#ifndef _TABFRM_HXX
#include <tabfrm.hxx>
#endif
#ifndef _NOTXTFRM_HXX
#include <notxtfrm.hxx>
#endif
#ifndef _FRMSH_HXX
#include <frmsh.hxx>
#endif
#ifndef _SWREGION_HXX
#include <swregion.hxx>
#endif
#ifndef _LAYACT_HXX
#include <layact.hxx>
#endif
#ifndef _PAGEDESC_HXX
#include <pagedesc.hxx>
#endif
#ifndef _PTQUEUE_HXX
#include <ptqueue.hxx>
#endif
#ifndef _NOTEURL_HXX
#include <noteurl.hxx>
#endif
#ifndef _VIRTOUTP_HXX
#include <virtoutp.hxx>
#endif
#ifndef _LINEINFO_HXX
#include <lineinfo.hxx>
#endif
#ifndef _DBG_LAY_HXX
#include <dbg_lay.hxx>
#endif
#ifndef _ACCESSIBILITYOPTIONS_HXX
#include <accessibilityoptions.hxx>
#endif
// OD 20.12.2002 #94627#
#ifndef _DOCSH_HXX
#include <docsh.hxx>
#endif
// OD 28.02.2003 #b4779636#, #107692#
#ifndef _SWTABLE_HXX
#include <swtable.hxx>
#endif
// OD 02.07.2003 #108784#
#ifndef _SVDOGRP_HXX
#include <bf_svx/svdogrp.hxx>
#endif

/*N*/ #define GETOBJSHELL()     ((SfxObjectShell*)rSh.GetDoc()->GetDocShell())

//STRIP001 //Tabellenhilfslinien an?
//STRIP001 #define IS_SUBS_TABLE \
//STRIP001     (pGlobalShell->GetViewOptions()->IsTable() && \
//STRIP001     !pGlobalShell->GetViewOptions()->IsPagePreview()&&\
//STRIP001     !pGlobalShell->GetViewOptions()->IsReadonly()&&\
//STRIP001      SwViewOption::IsTableBoundaries())
//STRIP001 //sonstige Hilfslinien an?
//STRIP001 #define IS_SUBS (!pGlobalShell->GetViewOptions()->IsPagePreview() && \
//STRIP001         !pGlobalShell->GetViewOptions()->IsReadonly() && \
//STRIP001         SwViewOption::IsDocBoundaries())
//STRIP001 //Hilfslinien fuer Bereiche
//STRIP001 #define IS_SUBS_SECTION (!pGlobalShell->GetViewOptions()->IsPagePreview() && \
//STRIP001                             !pGlobalShell->GetViewOptions()->IsReadonly()&&\
//STRIP001                             SwViewOption::IsSectionBoundaries())
//STRIP001 #define IS_SUBS_FLYS (!pGlobalShell->GetViewOptions()->IsPagePreview() && \
//STRIP001                             !pGlobalShell->GetViewOptions()->IsReadonly()&&\
//STRIP001                                 SwViewOption::IsObjectBoundaries())
//STRIP001
//STRIP001 #define SW_MAXBORDERCACHE 20

//Klassendeklarationen. Hier weil sie eben nur in diesem File benoetigt
//werden.

/*N*/ #define SUBCOL_PAGE     0x01    //Helplines of the page
/*N*/ #define SUBCOL_BREAK    0x02    //Helpline for a page or column break
/*N*/ #define SUBCOL_TAB      0x08    //Helplines inside tables
/*N*/ #define SUBCOL_FLY      0x10    //Helplines inside fly frames
/*N*/ #define SUBCOL_SECT     0x20    //Helplines inside sections

//----- Klassen zum Sammeln von Umrandungen und Hilfslinien ---
//STRIP001 class SwLineRect : public SwRect
//STRIP001 {
//STRIP001  const Color    *pColor;
//STRIP001  const SwTabFrm *pTab;
//STRIP001        BYTE      nSubColor;  //Hilfslinien einfaerben
//STRIP001        BOOL      bPainted;   //schon gepaintet?
//STRIP001        BYTE      nLock;      //Um die Linien zum Hell-Layer abzugrenzen.
//STRIP001 public:
//STRIP001  SwLineRect( const SwRect &rRect, const Color *pCol,
//STRIP001                 const SwTabFrm *pT , const BYTE nSCol );
//STRIP001
//STRIP001  const Color         *GetColor() const { return pColor;}
//STRIP001  const SwTabFrm      *GetTab()   const { return pTab;  }
//STRIP001  void  SetPainted()                    { bPainted = TRUE; }
//STRIP001  void  Lock( BOOL bLock )              { if ( bLock )
//STRIP001                                              ++nLock;
//STRIP001                                          else if ( nLock )
//STRIP001                                              --nLock;
//STRIP001                                        }
//STRIP001  BOOL  IsPainted()               const { return bPainted; }
//STRIP001  BOOL  IsLocked()                const { return nLock != 0;  }
//STRIP001  BYTE  GetSubColor()             const { return nSubColor;}
//STRIP001
//STRIP001  BOOL MakeUnion( const SwRect &rRect );
//STRIP001 };

//STRIP001 SV_DECL_VARARR( SwLRects, SwLineRect, 100, 100 );

//STRIP001 class SwLineRects : public SwLRects
//STRIP001 {
//STRIP001  USHORT nLastCount;  //unuetze Durchlaeufe im PaintLines verhindern.
//STRIP001 public:
//STRIP001  SwLineRects() : nLastCount( 0 ) {}
//STRIP001  void AddLineRect( const SwRect& rRect,  const Color *pColor,
//STRIP001                       const SwTabFrm *pTab, const BYTE nSCol );
//STRIP001  void ConnectEdges( OutputDevice *pOut );
//STRIP001  void PaintLines  ( OutputDevice *pOut );
//STRIP001  void LockLines( BOOL bLock );
//STRIP001
//STRIP001      /// OD 13.08.2002 - correct type of function
//STRIP001     const USHORT Free() const { return nFree; }
//STRIP001 };

//STRIP001 class SwSubsRects : public SwLineRects
//STRIP001 {
//STRIP001  void RemoveSuperfluousSubsidiaryLines( const SwLineRects &rRects ); //;-)
//STRIP001 public:
//STRIP001  void PaintSubsidiary( OutputDevice *pOut, const SwLineRects *pRects );
//STRIP001
//STRIP001  inline void Ins( const SwRect &rRect, const BYTE nSCol );
//STRIP001 };

//----------------- End Klassen Umrandungen ----------------------

/*N*/ static ViewShell *pGlobalShell = 0;

//Wenn durchsichtige FlyInCnts im PaintBackground gepainted werden so soll der
//Hintergrund nicht mehr retouchiert werden.
//static FASTBOOL bLockFlyBackground = FALSE;

//Wenn vom Fly ein Metafile abgezogen wird, so soll nur der FlyInhalt und vor
//nur hintergrund vom FlyInhalt gepaintet werden.
/*N*/ static FASTBOOL bFlyMetafile = FALSE;
/*N*/ static OutputDevice *pFlyMetafileOut = 0;

//Die Retouche fuer Durchsichtige Flys wird vom Hintergrund der Flys
//erledigt. Dabei darf der Fly selbst natuerlich nicht ausgespart werden.
//siehe PaintBackground und lcl_SubtractFlys()
/*N*/ static SwFlyFrm *pRetoucheFly  = 0;
/*N*/ static SwFlyFrm *pRetoucheFly2 = 0;

//Groesse eines Pixel und die Haelfte davon. Wird jeweils bei Eintritt in
//SwRootFrm::Paint neu gesetzt.
/*N*/ static long nPixelSzW = 0, nPixelSzH = 0;
/*N*/ static long nHalfPixelSzW = 0, nHalfPixelSzH = 0;
/*N*/ static long nMinDistPixelW = 0, nMinDistPixelH = 0;

//Aktueller Zoomfaktor
/*N*/ static double aScaleX = 1.0;
/*N*/ static double aScaleY = 1.0;
/*N*/ static double aMinDistScale = 0.73;
/*N*/ static double aEdgeScale = 0.5;

//In pLines werden Umrandungen waehrend des Paint gesammelt und soweit
//moeglich zusammengefasst.
//In pSubsLines werden Hilfslinien gesammelt und zusammengefasst. Diese
//werden vor der Ausgabe mit pLines abgeglichen, so dass moeglichst keine
//Umrandungen von den Hilfslinen verdeckt werden.
//bTablines ist waerend des Paints einer Tabelle TRUE.
//STRIP001 static SwLineRects *pLines = 0;
//STRIP001 static SwSubsRects *pSubsLines = 0;
// OD 18.11.2002 #99672# - global variable for sub-lines of body, header, footer,
// section and footnote frames.
//STRIP001 static SwSubsRects *pSpecSubsLines = 0;

//STRIP001 static SfxProgress *pProgress = 0;

//Nicht mehr als ein Beep pro Paint, wird auch im Textbereich benutzt!
/*N*/ FASTBOOL bOneBeepOnly = TRUE;

/*N*/ static SwFlyFrm *pFlyOnlyDraw = 0;

//Damit die Flys auch fuer den Hack richtig gepaintet werden koennen.
/*N*/ static FASTBOOL bTableHack = FALSE;

//Um das teure Ermitteln der RetoucheColor zu optimieren
/*N*/ Color aGlobalRetoucheColor;

//Statics fuer Umrandungsalignment setzen.
// OD 05.05.2003 #107169# - adjustment for 'small' twip-to-pixel relations:
// For 'small' twip-to-pixel relations (less then 2:1)
// values of <nHalfPixelSzW> and <nHalfPixelSzH> are set to ZERO.
//STRIP001 void SwCalcPixStatics( OutputDevice *pOut )
//STRIP001 {
//STRIP001     // OD 30.04.2003 #107169# - determine 'small' twip-to-pixel relation
//STRIP001     sal_Bool bSmallTwipToPxRelW = sal_False;
//STRIP001     sal_Bool bSmallTwipToPxRelH = sal_False;
//STRIP001     {
//STRIP001         Size aCheckTwipToPxRelSz( pOut->PixelToLogic( Size( 100, 100 )) );
//STRIP001         if ( (aCheckTwipToPxRelSz.Width()/100.0) < 2.0 )
//STRIP001         {
//STRIP001             bSmallTwipToPxRelW = sal_True;
//STRIP001         }
//STRIP001         if ( (aCheckTwipToPxRelSz.Height()/100.0) < 2.0 )
//STRIP001         {
//STRIP001             bSmallTwipToPxRelH = sal_True;
//STRIP001         }
//STRIP001     }
//STRIP001
//STRIP001     Size aSz( pOut->PixelToLogic( Size( 1,1 )) );
//STRIP001
//STRIP001     nPixelSzW = aSz.Width();
//STRIP001     if( !nPixelSzW )
//STRIP001         nPixelSzW = 1;
//STRIP001     nPixelSzH = aSz.Height();
//STRIP001     if( !nPixelSzH )
//STRIP001         nPixelSzH = 1;
//STRIP001
//STRIP001     // OD 06.05.2003 #107169# - consider 'small' twip-to-pixel relations
//STRIP001     if ( !bSmallTwipToPxRelW )
//STRIP001     {
//STRIP001         nHalfPixelSzW = nPixelSzW / 2 + 1;
//STRIP001     }
//STRIP001     else
//STRIP001     {
//STRIP001         nHalfPixelSzW = 0;
//STRIP001     }
//STRIP001     // OD 06.05.2003 #107169# - consider 'small' twip-to-pixel relations
//STRIP001     if ( !bSmallTwipToPxRelH )
//STRIP001     {
//STRIP001         nHalfPixelSzH = nPixelSzH / 2 + 1;
//STRIP001     }
//STRIP001     else
//STRIP001     {
//STRIP001         nHalfPixelSzH = 0;
//STRIP001     }
//STRIP001
//STRIP001     nMinDistPixelW = nPixelSzW * 2 + 1;
//STRIP001  nMinDistPixelH = nPixelSzH * 2 + 1;
//STRIP001
//STRIP001  const MapMode &rMap = pOut->GetMapMode();
//STRIP001  aScaleX = rMap.GetScaleX();
//STRIP001  aScaleY = rMap.GetScaleY();
//STRIP001 }

//Zum Sichern der statics, damit das Paint (quasi) reentrant wird.
//STRIP001 class SwSavePaintStatics
//STRIP001 {
//STRIP001  FASTBOOL            bSFlyMetafile,
//STRIP001                      bSOneBeepOnly,
//STRIP001                      bSPageOnly;
//STRIP001  ViewShell          *pSGlobalShell;
//STRIP001  OutputDevice       *pSFlyMetafileOut;
//STRIP001  SwFlyFrm           *pSRetoucheFly,
//STRIP001                     *pSRetoucheFly2,
//STRIP001                     *pSFlyOnlyDraw;
//STRIP001  SwLineRects        *pSLines;
//STRIP001  SwSubsRects        *pSSubsLines;
//STRIP001  SfxProgress        *pSProgress;
//STRIP001  long                nSPixelSzW,
//STRIP001                      nSPixelSzH,
//STRIP001                      nSHalfPixelSzW,
//STRIP001                      nSHalfPixelSzH,
//STRIP001                      nSMinDistPixelW,
//STRIP001                      nSMinDistPixelH;
//STRIP001  Color               aSGlobalRetoucheColor;
//STRIP001  double              aSScaleX,
//STRIP001                      aSScaleY;
//STRIP001 public:
//STRIP001  SwSavePaintStatics();
//STRIP001  ~SwSavePaintStatics();
//STRIP001 };

//STRIP001 SwSavePaintStatics::SwSavePaintStatics() :
//STRIP001  bSFlyMetafile       ( bFlyMetafile      ),
//STRIP001     bSOneBeepOnly       ( bOneBeepOnly      ),
//STRIP001  pSGlobalShell       ( pGlobalShell      ),
//STRIP001  pSFlyMetafileOut    ( pFlyMetafileOut   ),
//STRIP001  pSRetoucheFly       ( pRetoucheFly      ),
//STRIP001  pSRetoucheFly2      ( pRetoucheFly2     ),
//STRIP001  pSFlyOnlyDraw       ( pFlyOnlyDraw      ),
//STRIP001  pSLines             ( pLines            ),
//STRIP001  pSSubsLines         ( pSubsLines        ),
//STRIP001  pSProgress          ( pProgress         ),
//STRIP001  nSPixelSzW          ( nPixelSzW         ),
//STRIP001  nSPixelSzH          ( nPixelSzH         ),
//STRIP001  nSHalfPixelSzW      ( nHalfPixelSzW     ),
//STRIP001  nSHalfPixelSzH      ( nHalfPixelSzH     ),
//STRIP001  nSMinDistPixelW     ( nMinDistPixelW    ),
//STRIP001  nSMinDistPixelH     ( nMinDistPixelH    ),
//STRIP001  aSGlobalRetoucheColor( aGlobalRetoucheColor ),
//STRIP001  aSScaleX            ( aScaleX           ),
//STRIP001     aSScaleY            ( aScaleY           )
//STRIP001 {
//STRIP001     bFlyMetafile = FALSE;
//STRIP001  pFlyMetafileOut = 0;
//STRIP001  pRetoucheFly  = 0;
//STRIP001  pRetoucheFly2 = 0;
//STRIP001  nPixelSzW = nPixelSzH =
//STRIP001  nHalfPixelSzW = nHalfPixelSzH =
//STRIP001  nMinDistPixelW = nMinDistPixelH = 0;
//STRIP001  aScaleX = aScaleY = 1.0;
//STRIP001  aMinDistScale = 0.73;
//STRIP001  aEdgeScale = 0.5;
//STRIP001  pLines = 0;
//STRIP001  pSubsLines = 0;
//STRIP001  pProgress = 0;
//STRIP001  bOneBeepOnly = TRUE;
//STRIP001 }

//STRIP001 SwSavePaintStatics::~SwSavePaintStatics()
//STRIP001 {
//STRIP001  pGlobalShell       = pSGlobalShell;
//STRIP001  bFlyMetafile       = bSFlyMetafile;
//STRIP001  bOneBeepOnly       = bSOneBeepOnly;
//STRIP001  pFlyMetafileOut    = pSFlyMetafileOut;
//STRIP001  pRetoucheFly       = pSRetoucheFly;
//STRIP001  pRetoucheFly2      = pSRetoucheFly2;
//STRIP001  pFlyOnlyDraw       = pSFlyOnlyDraw;
//STRIP001  pLines             = pSLines;
//STRIP001  pSubsLines         = pSSubsLines;
//STRIP001  pProgress          = pSProgress;
//STRIP001  nPixelSzW          = nSPixelSzW;
//STRIP001  nPixelSzH          = nSPixelSzH;
//STRIP001  nHalfPixelSzW      = nSHalfPixelSzW;
//STRIP001  nHalfPixelSzH      = nSHalfPixelSzH;
//STRIP001  nMinDistPixelW     = nSMinDistPixelW;
//STRIP001  nMinDistPixelH     = nSMinDistPixelH;
//STRIP001  aGlobalRetoucheColor = aSGlobalRetoucheColor;
//STRIP001  aScaleX            = aSScaleX;
//STRIP001  aScaleY            = aSScaleY;
//STRIP001 }

//----------------- Implementierungen fuer Tabellenumrandung --------------

//STRIP001 SV_IMPL_VARARR( SwLRects, SwLineRect );


//STRIP001 SwLineRect::SwLineRect( const SwRect &rRect, const Color *pCol,
//STRIP001                      const SwTabFrm *pT, const BYTE nSCol ) :
//STRIP001  SwRect( rRect ),
//STRIP001  pColor( pCol ),
//STRIP001  pTab( pT ),
//STRIP001  bPainted( FALSE ),
//STRIP001  nSubColor( nSCol ),
//STRIP001  nLock( 0 )
//STRIP001 {
//STRIP001 }

//STRIP001 BOOL SwLineRect::MakeUnion( const SwRect &rRect )
//STRIP001 {
//STRIP001  //Es wurde bereits ausserhalb geprueft, ob die Rechtecke die gleiche
//STRIP001  //Ausrichtung (horizontal bzw. vertikal), Farbe usw. besitzen.
//STRIP001  if ( Height() > Width() ) //Vertikale Linie
//STRIP001  {
//STRIP001      if ( Left()  == rRect.Left() && Width() == rRect.Width() )
//STRIP001      {
//STRIP001          //Zusammenfassen wenn kein Luecke zwischen den Linien ist.
//STRIP001          const long nAdd = nPixelSzW + nHalfPixelSzW;
//STRIP001          if ( Bottom() + nAdd >= rRect.Top() &&
//STRIP001               Top()    - nAdd <= rRect.Bottom()  )
//STRIP001          {
//STRIP001              Bottom( Max( Bottom(), rRect.Bottom() ) );
//STRIP001              Top   ( Min( Top(),    rRect.Top()    ) );
//STRIP001              return TRUE;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      if ( Top()  == rRect.Top() && Height() == rRect.Height() )
//STRIP001      {
//STRIP001          //Zusammenfassen wenn kein Luecke zwischen den Linien ist.
//STRIP001          const long nAdd = nPixelSzW + nHalfPixelSzW;
//STRIP001          if ( Right() + nAdd >= rRect.Left() &&
//STRIP001                  Left()  - nAdd <= rRect.Right() )
//STRIP001          {
//STRIP001              Right( Max( Right(), rRect.Right() ) );
//STRIP001              Left ( Min( Left(),  rRect.Left()  ) );
//STRIP001              return TRUE;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  return FALSE;
//STRIP001 }

//STRIP001 void SwLineRects::AddLineRect( const SwRect &rRect, const Color *pCol,
//STRIP001                             const SwTabFrm *pTab, const BYTE nSCol )
//STRIP001 {
//STRIP001  //Rueckwaerts durch, weil Linien die zusammengefasst werden koennen i.d.R.
//STRIP001  //im gleichen Kontext gepaintet werden.
//STRIP001  for ( USHORT i = Count(); i ; )
//STRIP001  {
//STRIP001      SwLineRect &rLRect = operator[](--i);
//STRIP001      //Pruefen von Ausrichtung, Farbe, Tabelle.
//STRIP001      if ( rLRect.GetTab() == pTab &&
//STRIP001           !rLRect.IsPainted() && rLRect.GetSubColor() == nSCol &&
//STRIP001           (rLRect.Height() > rLRect.Width()) == (rRect.Height() > rRect.Width()) &&
//STRIP001           ((!rLRect.GetColor() && !pCol) ||
//STRIP001            (rLRect.GetColor() && pCol && *rLRect.GetColor() == *pCol)) )
//STRIP001      {
//STRIP001          if ( rLRect.MakeUnion( rRect ) )
//STRIP001              return;
//STRIP001      }
//STRIP001  }
//STRIP001  Insert( SwLineRect( rRect, pCol, pTab, nSCol ), Count() );
//STRIP001 }

//STRIP001 void SwLineRects::ConnectEdges( OutputDevice *pOut )
//STRIP001 {
//STRIP001  if ( pOut->GetOutDevType() != OUTDEV_PRINTER )
//STRIP001  {
//STRIP001      //Fuer einen zu kleinen Zoom arbeite ich nicht.
//STRIP001      if ( aScaleX < aEdgeScale || aScaleY < aEdgeScale )
//STRIP001          return;
//STRIP001  }
//STRIP001
//STRIP001  static const long nAdd = 20;
//STRIP001
//STRIP001  SvPtrarr   aCheck( 64, 64 );
//STRIP001
//STRIP001  for ( int i = 0; i < (int)Count(); ++i )
//STRIP001  {
//STRIP001      SwLineRect &rL1 = operator[](USHORT(i));
//STRIP001      if ( !rL1.GetTab() || rL1.IsPainted() || rL1.IsLocked() )
//STRIP001          continue;
//STRIP001
//STRIP001      aCheck.Remove( 0, aCheck.Count() );
//STRIP001
//STRIP001      const FASTBOOL bVert = rL1.Height() > rL1.Width();
//STRIP001      long nL1a, nL1b, nL1c, nL1d;
//STRIP001
//STRIP001      if ( bVert )
//STRIP001         {
//STRIP001             nL1a = rL1.Top();   nL1b = rL1.Left();
//STRIP001          nL1c = rL1.Right(); nL1d = rL1.Bottom();
//STRIP001      }
//STRIP001      else
//STRIP001         {
//STRIP001             nL1a = rL1.Left();   nL1b = rL1.Top();
//STRIP001          nL1c = rL1.Bottom(); nL1d = rL1.Right();
//STRIP001      }
//STRIP001
//STRIP001      //Alle moeglicherweise mit i1 zu verbindenden Linien einsammeln.
//STRIP001      for ( USHORT i2 = 0; i2 < Count(); ++i2 )
//STRIP001      {
//STRIP001          SwLineRect &rL2 = operator[](i2);
//STRIP001          if ( rL2.GetTab() != rL1.GetTab() ||
//STRIP001               rL2.IsPainted()              ||
//STRIP001               rL2.IsLocked()               ||
//STRIP001               bVert == rL2.Height() > rL2.Width() )
//STRIP001              continue;
//STRIP001
//STRIP001          long nL2a, nL2b, nL2c, nL2d;
//STRIP001          if ( bVert )
//STRIP001             {
//STRIP001                 nL2a = rL2.Top();   nL2b = rL2.Left();
//STRIP001              nL2c = rL2.Right(); nL2d = rL2.Bottom();
//STRIP001          }
//STRIP001          else
//STRIP001             {
//STRIP001                 nL2a = rL2.Left();   nL2b = rL2.Top();
//STRIP001              nL2c = rL2.Bottom(); nL2d = rL2.Right();
//STRIP001          }
//STRIP001
//STRIP001          if ( (nL1a - nAdd < nL2d && nL1d + nAdd > nL2a) &&
//STRIP001                ((nL1b >  nL2b && nL1c        < nL2c) ||
//STRIP001                 (nL1c >= nL2c && nL1b - nAdd < nL2c) ||
//STRIP001                 (nL1b <= nL2b && nL1c + nAdd > nL2b)) )
//STRIP001          {
//STRIP001              SwLineRect *pMSC = &rL2;
//STRIP001              aCheck.Insert( (void*&)pMSC, aCheck.Count() );
//STRIP001          }
//STRIP001      }
//STRIP001      if ( aCheck.Count() < 2 )
//STRIP001          continue;
//STRIP001
//STRIP001      FASTBOOL bRemove = FALSE;
//STRIP001
//STRIP001      //Fuer jede Linie jede alle folgenden checken.
//STRIP001      for ( USHORT k = 0; !bRemove && k < aCheck.Count(); ++k )
//STRIP001      {
//STRIP001          SwLineRect &rR1 = (SwLineRect&)*(SwLineRect*)aCheck[k];
//STRIP001
//STRIP001          for ( USHORT k2 = k+1; !bRemove && k2 < aCheck.Count(); ++k2 )
//STRIP001          {
//STRIP001              SwLineRect &rR2 = (SwLineRect&)*(SwLineRect*)aCheck[k2];
//STRIP001              if ( bVert )
//STRIP001              {
//STRIP001                  SwLineRect *pLA = 0, *pLB;
//STRIP001                  if ( rR1.Top() < rR2.Top() )
//STRIP001                  {
//STRIP001                      pLA = &rR1; pLB = &rR2;
//STRIP001                  }
//STRIP001                  else if ( rR1.Top() > rR2.Top() )
//STRIP001                  {
//STRIP001                      pLA = &rR2; pLB = &rR1;
//STRIP001                  }
//STRIP001                  //beschreiben k1 und k2 eine Doppellinie?
//STRIP001                  if ( pLA && pLA->Bottom() + 60 > pLB->Top() )
//STRIP001                  {
//STRIP001                      if ( rL1.Top() < pLA->Top() )
//STRIP001                      {
//STRIP001                          if ( rL1.Bottom() == pLA->Bottom() )
//STRIP001                              continue;   //kleiner Irrtum (woher?)
//STRIP001
//STRIP001                          SwRect aIns( rL1 );
//STRIP001                          aIns.Bottom( pLA->Bottom() );
//STRIP001                          if ( !rL1.IsInside( aIns ) )
//STRIP001                              continue;
//STRIP001                          const USHORT nFree = Free();
//STRIP001                          Insert( SwLineRect( aIns, rL1.GetColor(),
//STRIP001                                         rL1.GetTab(), SUBCOL_TAB ), Count() );
//STRIP001                          if ( !nFree )
//STRIP001                          {
//STRIP001                              --i;
//STRIP001                              k = aCheck.Count();
//STRIP001                              break;
//STRIP001                          }
//STRIP001                      }
//STRIP001
//STRIP001                      if ( rL1.Bottom() > pLB->Bottom() )
//STRIP001                          rL1.Top( pLB->Top() );  //i1 nach oben verlaengern
//STRIP001                      else
//STRIP001                          bRemove = TRUE;         //abbrechen, i1 entfernen
//STRIP001                  }
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  SwLineRect *pLA = 0, *pLB;
//STRIP001                  if ( rR1.Left() < rR2.Left() )
//STRIP001                  {
//STRIP001                      pLA = &rR1; pLB = &rR2;
//STRIP001                  }
//STRIP001                  else if ( rR1.Left() > rR2.Left() )
//STRIP001                  {
//STRIP001                      pLA = &rR2; pLB = &rR1;
//STRIP001                  }
//STRIP001                  //Liegt eine 'doppellinie' vor?
//STRIP001                  if ( pLA && pLA->Right() + 60 > pLB->Left() )
//STRIP001                  {
//STRIP001                      if ( rL1.Left() < pLA->Left() )
//STRIP001                      {
//STRIP001                          if ( rL1.Right() == pLA->Right() )
//STRIP001                              continue;   //kleiner irrtum
//STRIP001
//STRIP001                          SwRect aIns( rL1 );
//STRIP001                          aIns.Right( pLA->Right() );
//STRIP001                          if ( !rL1.IsInside( aIns ) )
//STRIP001                              continue;
//STRIP001                          const USHORT nFree = Free();
//STRIP001                          Insert( SwLineRect( aIns, rL1.GetColor(),
//STRIP001                                         rL1.GetTab(), SUBCOL_TAB ), Count() );
//STRIP001                          if ( !nFree )
//STRIP001                          {
//STRIP001                              --i;
//STRIP001                              k = aCheck.Count();
//STRIP001                              break;
//STRIP001                          }
//STRIP001                      }
//STRIP001                      if ( rL1.Right() > pLB->Right() )
//STRIP001                          rL1.Left( pLB->Left() );
//STRIP001                      else
//STRIP001                          bRemove = TRUE;
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001      if ( bRemove )
//STRIP001      {
//STRIP001          Remove( i, 1 );
//STRIP001          --i;            //keinen auslassen!
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 inline void SwSubsRects::Ins( const SwRect &rRect, const BYTE nSCol )
//STRIP001 {
//STRIP001  //Linien die kuerzer als die breiteste Linienbreite sind werden
//STRIP001  //nicht aufgenommen.
//STRIP001  if ( rRect.Height() > DEF_LINE_WIDTH_4 || rRect.Width() > DEF_LINE_WIDTH_4 )
//STRIP001      Insert( SwLineRect( rRect, 0, 0, nSCol ), Count());
//STRIP001 }

//STRIP001 void SwSubsRects::RemoveSuperfluousSubsidiaryLines( const SwLineRects &rRects )
//STRIP001 {
//STRIP001  //Alle Hilfslinien, die sich mit irgendwelchen Umrandungen decken werden
//STRIP001  //entfernt bzw. zerstueckelt..
//STRIP001  for ( USHORT i = 0; i < Count(); ++i )
//STRIP001  {
//STRIP001         // OD 18.11.2002 #99672# - get a copy instead of a reference, because
//STRIP001         // an <insert> may destroy the object due to a necessary array resize.
//STRIP001         const SwLineRect aSubsLineRect = SwLineRect( operator[](i) );
//STRIP001
//STRIP001         // OD 19.12.2002 #106318# - add condition <aSubsLineRect.IsLocked()>
//STRIP001         // in order to consider only border lines, which are *not* locked.
//STRIP001         if ( aSubsLineRect.IsPainted() ||
//STRIP001              aSubsLineRect.IsLocked() )
//STRIP001          continue;
//STRIP001
//STRIP001         const bool bVerticalSubs = aSubsLineRect.Height() > aSubsLineRect.Width();
//STRIP001         SwRect aSubsRect( aSubsLineRect );
//STRIP001         if ( bVerticalSubs )
//STRIP001      {
//STRIP001             aSubsRect.Left  ( aSubsRect.Left()  - (nPixelSzW+nHalfPixelSzW) );
//STRIP001             aSubsRect.Right ( aSubsRect.Right() + (nPixelSzW+nHalfPixelSzW) );
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001             aSubsRect.Top   ( aSubsRect.Top()    - (nPixelSzH+nHalfPixelSzH) );
//STRIP001             aSubsRect.Bottom( aSubsRect.Bottom() + (nPixelSzH+nHalfPixelSzH) );
//STRIP001      }
//STRIP001      for ( USHORT k = 0; k < rRects.Count(); ++k )
//STRIP001      {
//STRIP001          SwLineRect &rLine = rRects[k];
//STRIP001
//STRIP001             // OD 20.12.2002 #106318# - do *not* consider painted or locked
//STRIP001             // border lines.
//STRIP001             // OD 20.01.2003 #i1837# - locked border lines have to be considered.
//STRIP001             if ( rLine.IsLocked () )
//STRIP001                 continue;
//STRIP001
//STRIP001             if ( !bVerticalSubs == rLine.Height() > rLine.Width() ) //gleiche Ausrichtung?
//STRIP001              continue;
//STRIP001
//STRIP001             if ( aSubsRect.IsOver( rLine ) )
//STRIP001          {
//STRIP001                 if ( bVerticalSubs ) //Vertikal?
//STRIP001              {
//STRIP001                     if ( aSubsRect.Left()  <= rLine.Right() &&
//STRIP001                          aSubsRect.Right() >= rLine.Left() )
//STRIP001                  {
//STRIP001                      long nTmp = rLine.Top()-(nPixelSzH+1);
//STRIP001                         if ( aSubsLineRect.Top() < nTmp )
//STRIP001                      {
//STRIP001                             SwRect aNewSubsRect( aSubsLineRect );
//STRIP001                             aNewSubsRect.Bottom( nTmp );
//STRIP001                             Insert( SwLineRect( aNewSubsRect, 0, 0,
//STRIP001                                                 aSubsLineRect.GetSubColor() ), Count());
//STRIP001                      }
//STRIP001                      nTmp = rLine.Bottom()+nPixelSzH+1;
//STRIP001                         if ( aSubsLineRect.Bottom() > nTmp )
//STRIP001                      {
//STRIP001                             SwRect aNewSubsRect( aSubsLineRect );
//STRIP001                             aNewSubsRect.Top( nTmp );
//STRIP001                             Insert( SwLineRect( aNewSubsRect, 0, 0,
//STRIP001                                                 aSubsLineRect.GetSubColor() ), Count());
//STRIP001                      }
//STRIP001                      Remove( i, 1 );
//STRIP001                      --i;
//STRIP001                      break;
//STRIP001                  }
//STRIP001              }
//STRIP001              else                                    //Horizontal
//STRIP001              {
//STRIP001                     if ( aSubsRect.Top() <= rLine.Bottom() &&
//STRIP001                          aSubsRect.Bottom() >= rLine.Top() )
//STRIP001                  {
//STRIP001                      long nTmp = rLine.Left()-(nPixelSzW+1);
//STRIP001                         if ( aSubsLineRect.Left() < nTmp )
//STRIP001                      {
//STRIP001                             SwRect aNewSubsRect( aSubsLineRect );
//STRIP001                             aNewSubsRect.Right( nTmp );
//STRIP001                             Insert( SwLineRect( aNewSubsRect, 0, 0,
//STRIP001                                                 aSubsLineRect.GetSubColor() ), Count());
//STRIP001                      }
//STRIP001                      nTmp = rLine.Right()+nPixelSzW+1;
//STRIP001                         if ( aSubsLineRect.Right() > nTmp )
//STRIP001                      {
//STRIP001                             SwRect aNewSubsRect( aSubsLineRect );
//STRIP001                             aNewSubsRect.Left( nTmp );
//STRIP001                             Insert( SwLineRect( aNewSubsRect, 0, 0,
//STRIP001                                                 aSubsLineRect.GetSubColor() ), Count());
//STRIP001                      }
//STRIP001                      Remove( i, 1 );
//STRIP001                      --i;
//STRIP001                      break;
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 void SwLineRects::LockLines( BOOL bLock )
//STRIP001 {
//STRIP001  for ( USHORT i = 0; i < Count(); ++i )
//STRIP001      operator[](i).Lock( bLock );
//STRIP001 }

//STRIP001 void SwLineRects::PaintLines( OutputDevice *pOut )
//STRIP001 {
//STRIP001  //Painten der Umrandungen. Leider muessen wir zweimal durch.
//STRIP001  //Einmal fuer die innenliegenden und einmal fuer die Aussenkanten
//STRIP001  //der Tabellen.
//STRIP001  if ( Count() != nLastCount )
//STRIP001  {
//STRIP001      pOut->Push( PUSH_FILLCOLOR );
//STRIP001
//STRIP001      ConnectEdges( pOut );
//STRIP001      const Color *pLast = 0;
//STRIP001
//STRIP001      FASTBOOL bPaint2nd = FALSE;
//STRIP001      USHORT nMinCount = Count();
//STRIP001      for ( USHORT i = 0; i < Count(); ++i )
//STRIP001      {
//STRIP001          SwLineRect &rLRect = operator[](i);
//STRIP001
//STRIP001          if ( rLRect.IsPainted() )
//STRIP001              continue;
//STRIP001
//STRIP001          if ( rLRect.IsLocked() )
//STRIP001          {
//STRIP001              nMinCount = Min( nMinCount, i );
//STRIP001              continue;
//STRIP001          }
//STRIP001
//STRIP001          //Jetzt malen oder erst in der zweiten Runde?
//STRIP001          FASTBOOL bPaint = TRUE;
//STRIP001          if ( rLRect.GetTab() )
//STRIP001          {
//STRIP001              if ( rLRect.Height() > rLRect.Width() )
//STRIP001              {
//STRIP001                  //Senkrechte Kante, ueberlappt sie mit der TabellenKante?
//STRIP001                  SwTwips nLLeft  = rLRect.Left()  - 30,
//STRIP001                          nLRight = rLRect.Right() + 30,
//STRIP001                          nTLeft  = rLRect.GetTab()->Frm().Left() + rLRect.GetTab()->Prt().Left(),
//STRIP001                          nTRight = rLRect.GetTab()->Frm().Left() + rLRect.GetTab()->Prt().Right();
//STRIP001                  if ( (nTLeft >= nLLeft && nTLeft <= nLRight) ||
//STRIP001                       (nTRight>= nLLeft && nTRight<= nLRight) )
//STRIP001                      bPaint = FALSE;
//STRIP001              }
//STRIP001              else
//STRIP001              {   //Waagerechte Kante, ueberlappt sie mit der Tabellenkante?
//STRIP001                  SwTwips nLTop    = rLRect.Top()    - 30,
//STRIP001                          nLBottom = rLRect.Bottom() + 30,
//STRIP001                          nTTop    = rLRect.GetTab()->Frm().Top()  + rLRect.GetTab()->Prt().Top(),
//STRIP001                          nTBottom = rLRect.GetTab()->Frm().Top()  + rLRect.GetTab()->Prt().Bottom();
//STRIP001                  if ( (nTTop    >= nLTop && nTTop      <= nLBottom) ||
//STRIP001                       (nTBottom >= nLTop && nTBottom <= nLBottom) )
//STRIP001                      bPaint = FALSE;
//STRIP001              }
//STRIP001          }
//STRIP001          if ( bPaint )
//STRIP001          {
//STRIP001                 if ( !pLast || *pLast != *rLRect.GetColor() )
//STRIP001              {
//STRIP001                  pLast = rLRect.GetColor();
//STRIP001
//STRIP001                     ULONG nOldDrawMode = pOut->GetDrawMode();
//STRIP001                     if( pGlobalShell->GetWin() &&
//STRIP001                         Application::GetSettings().GetStyleSettings().GetHighContrastMode() )
//STRIP001                         pOut->SetDrawMode( 0 );
//STRIP001
//STRIP001                  pOut->SetFillColor( *pLast );
//STRIP001                     pOut->SetDrawMode( nOldDrawMode );
//STRIP001              }
//STRIP001                 if( !rLRect.IsEmpty() )
//STRIP001                     pOut->DrawRect( rLRect.SVRect() );
//STRIP001              rLRect.SetPainted();
//STRIP001          }
//STRIP001          else
//STRIP001              bPaint2nd = TRUE;
//STRIP001      }
//STRIP001      if ( bPaint2nd )
//STRIP001          for ( i = 0; i < Count(); ++i )
//STRIP001          {
//STRIP001              SwLineRect &rLRect = operator[](i);
//STRIP001              if ( rLRect.IsPainted() )
//STRIP001                  continue;
//STRIP001
//STRIP001              if ( rLRect.IsLocked() )
//STRIP001              {
//STRIP001                  nMinCount = Min( nMinCount, i );
//STRIP001                  continue;
//STRIP001              }
//STRIP001
//STRIP001              if ( !pLast || *pLast != *rLRect.GetColor() )
//STRIP001              {
//STRIP001                  pLast = rLRect.GetColor();
//STRIP001
//STRIP001                     ULONG nOldDrawMode = pOut->GetDrawMode();
//STRIP001                     if( pGlobalShell->GetWin() &&
//STRIP001                         Application::GetSettings().GetStyleSettings().GetHighContrastMode() )
//STRIP001                     {
//STRIP001                         pOut->SetDrawMode( 0 );
//STRIP001                     }
//STRIP001
//STRIP001                  pOut->SetFillColor( *pLast );
//STRIP001                     pOut->SetDrawMode( nOldDrawMode );
//STRIP001              }
//STRIP001                 if( !rLRect.IsEmpty() )
//STRIP001                     pOut->DrawRect( rLRect.SVRect() );
//STRIP001              rLRect.SetPainted();
//STRIP001          }
//STRIP001      nLastCount = nMinCount;
//STRIP001      pOut->Pop();
//STRIP001  }
//STRIP001 }

//STRIP001 void SwSubsRects::PaintSubsidiary( OutputDevice *pOut,
//STRIP001                                 const SwLineRects *pRects )
//STRIP001 {
//STRIP001  if ( Count() )
//STRIP001  {
//STRIP001      //Alle Hilfslinien, die sich fast decken entfernen (Tabellen)
//STRIP001      for ( USHORT i = 0; i < Count(); ++i )
//STRIP001      {
//STRIP001          SwLineRect &rLi = operator[](i);
//STRIP001             const bool bVerticalSubs = rLi.Height() > rLi.Width();
//STRIP001
//STRIP001          for ( USHORT k = i+1; k < Count(); ++k )
//STRIP001          {
//STRIP001              SwLineRect &rLk = operator[](k);
//STRIP001              if ( rLi.SSize() == rLk.SSize() )
//STRIP001              {
//STRIP001                     if ( bVerticalSubs == rLk.Height() > rLk.Width() )
//STRIP001                  {
//STRIP001                         if ( bVerticalSubs )
//STRIP001                      {
//STRIP001                          long nLi = rLi.Right();
//STRIP001                          long nLk = rLk.Right();
//STRIP001                          if ( rLi.Top() == rLk.Top() &&
//STRIP001                               ((nLi < rLk.Left() && nLi+21 > rLk.Left()) ||
//STRIP001                                (nLk < rLi.Left() && nLk+21 > rLi.Left())))
//STRIP001                          {
//STRIP001                              Remove( k, 1 );
//STRIP001                              //Nicht mit der inneren Schleife weiter, weil
//STRIP001                              //das Array schrumpfen koennte!
//STRIP001                              --i; k = Count();
//STRIP001                          }
//STRIP001                      }
//STRIP001                      else
//STRIP001                      {
//STRIP001                          long nLi = rLi.Bottom();
//STRIP001                          long nLk = rLk.Bottom();
//STRIP001                          if ( rLi.Left() == rLk.Left() &&
//STRIP001                               ((nLi < rLk.Top() && nLi+21 > rLk.Top()) ||
//STRIP001                                (nLk < rLi.Top() && nLk+21 > rLi.Top())))
//STRIP001                          {
//STRIP001                              Remove( k, 1 );
//STRIP001                              --i; k = Count();
//STRIP001                          }
//STRIP001                      }
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001
//STRIP001      if ( pRects && pRects->Count() )
//STRIP001          RemoveSuperfluousSubsidiaryLines( *pRects );
//STRIP001
//STRIP001      if ( Count() )
//STRIP001      {
//STRIP001          pOut->Push( PUSH_FILLCOLOR );
//STRIP001
//STRIP001             // OD 14.01.2003 #106660# - reset draw mode in high contrast
//STRIP001             // mode in order to get fill color set at output device.
//STRIP001             // Recover draw mode after draw of lines.
//STRIP001             // Necessary for the subsidiary lines painted by the fly frames.
//STRIP001             ULONG nOldDrawMode = pOut->GetDrawMode();
//STRIP001             if( pGlobalShell->GetWin() &&
//STRIP001                 Application::GetSettings().GetStyleSettings().GetHighContrastMode() )
//STRIP001             {
//STRIP001                 pOut->SetDrawMode( 0 );
//STRIP001             }
//STRIP001
//STRIP001             for ( USHORT i = 0; i < Count(); ++i )
//STRIP001          {
//STRIP001              SwLineRect &rLRect = operator[](i);
//STRIP001                 // OD 19.12.2002 #106318# - add condition <!rLRect.IsLocked()>
//STRIP001                 // to prevent paint of locked subsidiary lines.
//STRIP001                 if ( !rLRect.IsPainted() &&
//STRIP001                      !rLRect.IsLocked() )
//STRIP001              {
//STRIP001                  const Color *pCol;
//STRIP001                  switch ( rLRect.GetSubColor() )
//STRIP001                  {
//STRIP001                         case SUBCOL_PAGE: pCol = &SwViewOption::GetDocBoundariesColor(); break;
//STRIP001                         case SUBCOL_FLY: pCol = &SwViewOption::GetObjectBoundariesColor(); break;
//STRIP001                         case SUBCOL_TAB: pCol = &SwViewOption::GetTableBoundariesColor(); break;
//STRIP001                         case SUBCOL_SECT: pCol = &SwViewOption::GetSectionBoundColor(); break;
//STRIP001                         case SUBCOL_BREAK:    pCol = &SwViewOption::GetPageBreakColor(); break;
//STRIP001                  }
//STRIP001
//STRIP001                     if ( pOut->GetFillColor() != *pCol )
//STRIP001                         pOut->SetFillColor( *pCol );
//STRIP001                     pOut->DrawRect( rLRect.SVRect() );
//STRIP001
//STRIP001                     rLRect.SetPainted();
//STRIP001              }
//STRIP001          }
//STRIP001
//STRIP001             // OD 14.01.2003 #106660# - recovering draw mode
//STRIP001             pOut->SetDrawMode( nOldDrawMode );
//STRIP001
//STRIP001             pOut->Pop();
//STRIP001      }
//STRIP001  }
//STRIP001 }

//-------------------------------------------------------------------------
//Diverse Functions die in diesem File so verwendet werden.

// OD 20.02.2003 - Note: function <SwAlignRect(..)> also used outside this file.
// OD 29.04.2003 #107169# - correction: adjust rectangle on pixel level in order
//          to assure, that the border 'leaves its original pixel', if it has to.
//          No prior adjustments for odd relation between pixel and twip.
void MA_FASTCALL SwAlignRect( SwRect &rRect, ViewShell *pSh )
{
    if( !rRect.HasArea() )
        return;

    // OD 03.09.2002 #102450#
    // Assure that view shell (parameter <pSh>) exists, if the output device
    // is taken from this view shell --> no output device, no alignment.
    // Output device taken from view shell <pSh>, if <bFlyMetafile> not set.
    if ( !bFlyMetafile && !pSh )
    {
        return;
    }

    const OutputDevice *pOut = bFlyMetafile ?
                        pFlyMetafileOut : pSh->GetOut();

    // OD 28.04.2003 #107169# - hold original rectangle in pixel
    const Rectangle aOrgPxRect = pOut->LogicToPixel( rRect.SVRect() );
    // OD 29.04.2003 #107169# - determine pixel-center rectangle in twip
    const SwRect aPxCenterRect( pOut->PixelToLogic( aOrgPxRect ) );

    // OD 06.05.2003 #107169# - perform adjustments on pixel level.
    SwRect aAlignedPxRect( aOrgPxRect );
    if ( rRect.Top() > aPxCenterRect.Top() )
    {
        // 'leave pixel overlapping on top'
        aAlignedPxRect.Top( aAlignedPxRect.Top() + 1 );
    }

    if ( rRect.Bottom() < aPxCenterRect.Bottom() )
    {
        // 'leave pixel overlapping on bottom'
        aAlignedPxRect.Bottom( aAlignedPxRect.Bottom() - 1 );
    }

    if ( rRect.Left() > aPxCenterRect.Left() )
    {
        // 'leave pixel overlapping on left'
        aAlignedPxRect.Left( aAlignedPxRect.Left() + 1 );
    }

    if ( rRect.Right() < aPxCenterRect.Right() )
    {
        // 'leave pixel overlapping on right'
        aAlignedPxRect.Right( aAlignedPxRect.Right() - 1 );
    }

    // OD 11.10.2002 #103636# - consider negative width/height
    // check, if aligned SwRect has negative width/height.
    // If Yes, adjust it to width/height = 0 twip.
    // NOTE: A SwRect with negative width/height can occur, if the width/height
    //     of the given SwRect in twip was less than a pixel in twip and that
    //     the alignment calculates that the aligned SwRect should not contain
    //     the pixels the width/height is on.
    if ( aAlignedPxRect.Width() < 0 )
    {
        aAlignedPxRect.Width(0);
    }
    if ( aAlignedPxRect.Height() < 0 )
    {
        aAlignedPxRect.Height(0);
    }
    // OD 30.04.2003 #107169# - consider zero width/height
    // For converting a rectangle from pixel to logic it needs a width/height.
    // Thus, set width/height to one, if it's zero and correct this on the twip
    // level after the conversion.
    sal_Bool bZeroWidth = sal_False;
    if ( aAlignedPxRect.Width() == 0 )
    {
        aAlignedPxRect.Width(1);
        bZeroWidth = sal_True;
    }
    sal_Bool bZeroHeight = sal_False;
    if ( aAlignedPxRect.Height() == 0 )
    {
        aAlignedPxRect.Height(1);
        bZeroHeight = sal_True;
    }

    rRect = pOut->PixelToLogic( aAlignedPxRect.SVRect() );

    // OD 30.04.2003 #107169# - consider zero width/height and adjust calculated
    // aligned twip rectangle.
    // OD 19.05.2003 #109667# - reset width/height to zero; previous negative
    // width/height haven't to be considered.
    if ( bZeroWidth )
    {
        rRect.Width(0);
    }
    if ( bZeroHeight )
    {
        rRect.Height(0);
    }
}

/** OD 19.05.2003 #109667# - helper method for twip adjustments on pixel base

    method compares the x- or y-pixel position of two twip-point. If the x-/y-pixel
    positions are the same, the x-/y-pixel position of the second twip point is
    adjusted by a given amount of pixels.

    @author OD
*/
void lcl_CompPxPosAndAdjustPos( const OutputDevice&  _rOut,
                                const Point&         _rRefPt,
                                Point&               _rCompPt,
                                const sal_Bool       _bChkXPos,
                                const sal_Int8       _nPxAdjustment )
{
    const Point aRefPxPt = _rOut.LogicToPixel( _rRefPt );
    Point aCompPxPt = _rOut.LogicToPixel( _rCompPt );

    if ( _bChkXPos )
    {
        if ( aCompPxPt.X() == aRefPxPt.X() )
        {
            aCompPxPt.X() += _nPxAdjustment ;
            const Point aAdjustedCompPt = _rOut.PixelToLogic( aCompPxPt );
            _rCompPt.X() = aAdjustedCompPt.X();
        }
    }
    else
    {
        if ( aCompPxPt.Y() == aRefPxPt.Y() )
        {
            aCompPxPt.Y() += _nPxAdjustment ;
            const Point aAdjustedCompPt = _rOut.PixelToLogic( aCompPxPt );
            _rCompPt.Y() = aAdjustedCompPt.Y();
        }
    }
}

/** OD 25.09.2002 #99739# - method to pixel-align rectangle for drawing graphic object

    Because for drawing a graphic left-top-corner and size coordinations are
    used, these coordinations have to be determined on pixel level.
    Thus, convert rectangle to pixel and then convert left-top-corner and
    size of pixel rectangle back to logic.
    This calculation is necessary, because there exists a different between
    the convert from logic to pixel of a normal rectangle with its left-top-
    and right-bottom-corner and the same convert of the same rectangle
    with left-top-corner and size.
    Call this method before each <GraphicObject.Draw(...)>

    @author OD
*/
//STRIP001 void SwAlignGrfRect( SwRect *pGrfRect, const OutputDevice &rOut )
//STRIP001 {
//STRIP001     Rectangle aPxRect = rOut.LogicToPixel( pGrfRect->SVRect() );
//STRIP001     pGrfRect->Pos( rOut.PixelToLogic( aPxRect.TopLeft() ) );
//STRIP001     pGrfRect->SSize( rOut.PixelToLogic( aPxRect.GetSize() ) );
//STRIP001 }

//STRIP001 long MA_FASTCALL lcl_AlignWidth( const long nWidth )
//STRIP001 {
//STRIP001  if ( nWidth )
//STRIP001  {
//STRIP001      const long nW = nWidth % nPixelSzW;
//STRIP001
//STRIP001      if ( !nW || nW > nHalfPixelSzW )
//STRIP001          return Max(1L, nWidth - nHalfPixelSzW);
//STRIP001  }
//STRIP001  return nWidth;
//STRIP001 }

//STRIP001 long MA_FASTCALL lcl_AlignHeight( const long nHeight )
//STRIP001 {
//STRIP001  if ( nHeight )
//STRIP001  {
//STRIP001      const long nH = nHeight % nPixelSzH;
//STRIP001
//STRIP001      if ( !nH || nH > nHalfPixelSzH )
//STRIP001          return Max(1L, nHeight - nHalfPixelSzH);
//STRIP001  }
//STRIP001  return nHeight;
//STRIP001 }

//STRIP001 long MA_FASTCALL lcl_MinHeightDist( const long nDist )
//STRIP001 {
//STRIP001  if ( aScaleX < aMinDistScale || aScaleY < aMinDistScale )
//STRIP001      return nDist;
//STRIP001  return ::lcl_AlignHeight( Max( nDist, nMinDistPixelH ));
//STRIP001 }

//STRIP001 long MA_FASTCALL lcl_MinWidthDist( const long nDist )
//STRIP001 {
//STRIP001  if ( aScaleX < aMinDistScale || aScaleY < aMinDistScale )
//STRIP001      return nDist;
//STRIP001  return ::lcl_AlignWidth( Max( nDist, nMinDistPixelW ));
//STRIP001 }


//Ermittelt PrtArea plus Umrandung plus Schatten.
//STRIP001 void MA_FASTCALL lcl_CalcBorderRect( SwRect &rRect, const SwFrm *pFrm,
//STRIP001                                      const SwBorderAttrs &rAttrs,
//STRIP001                                         const BOOL bShadow )
//STRIP001 {
//STRIP001     // OD 23.01.2003 #106386# - special handling for cell frames.
//STRIP001     // The printing area of a cell frame is completely enclosed in the frame area
//STRIP001     // and a cell frame has no shadow. Thus, for cell frames the calculated
//STRIP001     // area equals the frame area.
//STRIP001     // Notes: Borders of cell frames in R2L text direction will switch its side
//STRIP001     //        - left border is painted on the right; right border on the left.
//STRIP001     //        See <lcl_PaintLeftLine> and <lcl_PaintRightLine>.
//STRIP001     if( pFrm->IsSctFrm() )
//STRIP001     {
//STRIP001      rRect = pFrm->Prt();
//STRIP001      rRect.Pos() += pFrm->Frm().Pos();
//STRIP001     }
//STRIP001     else if ( pFrm->IsCellFrm() )
//STRIP001      rRect = pFrm->Frm();
//STRIP001  else
//STRIP001  {
//STRIP001      rRect = pFrm->Prt();
//STRIP001      rRect.Pos() += pFrm->Frm().Pos();
//STRIP001
//STRIP001      if ( rAttrs.IsLine() || rAttrs.IsBorderDist() ||
//STRIP001          (bShadow && rAttrs.GetShadow().GetLocation() != SVX_SHADOW_NONE) )
//STRIP001      {
//STRIP001             SwRectFn fnRect = pFrm->IsVertical() ? fnRectVert : fnRectHori;
//STRIP001          const SvxBoxItem &rBox = rAttrs.GetBox();
//STRIP001             const FASTBOOL bTop = 0 != (pFrm->*fnRect->fnGetTopMargin)();
//STRIP001          if ( bTop )
//STRIP001          {
//STRIP001                 SwTwips nDiff = rBox.GetTop() ?
//STRIP001                     rBox.CalcLineSpace( BOX_LINE_TOP ) :
//STRIP001                     ( rAttrs.IsBorderDist() ?
//STRIP001                       // OD 23.01.2003 #106386# - increase of distance by
//STRIP001                       // one twip is incorrect.
//STRIP001                       rBox.GetDistance( BOX_LINE_TOP ) : 0 );
//STRIP001                 if( nDiff )
//STRIP001                     (rRect.*fnRect->fnSubTop)( nDiff );
//STRIP001          }
//STRIP001
//STRIP001             const FASTBOOL bBottom = 0 != (pFrm->*fnRect->fnGetBottomMargin)();
//STRIP001          if ( bBottom )
//STRIP001          {
//STRIP001                 SwTwips nDiff = rBox.GetBottom() ?
//STRIP001                     rBox.CalcLineSpace( BOX_LINE_BOTTOM ) :
//STRIP001                     ( rAttrs.IsBorderDist() ?
//STRIP001                       // OD 23.01.2003 #106386# - increase of distance by
//STRIP001                       // one twip is incorrect.
//STRIP001                       rBox.GetDistance( BOX_LINE_BOTTOM ) : 0 );
//STRIP001                 if( nDiff )
//STRIP001                     (rRect.*fnRect->fnAddBottom)( nDiff );
//STRIP001          }
//STRIP001
//STRIP001             if ( rBox.GetLeft() )
//STRIP001                 (rRect.*fnRect->fnSubLeft)( rBox.CalcLineSpace( BOX_LINE_LEFT ) );
//STRIP001          else if ( rAttrs.IsBorderDist() )
//STRIP001                  // OD 23.01.2003 #106386# - increase of distance by one twip is incorrect.
//STRIP001                 (rRect.*fnRect->fnSubLeft)( rBox.GetDistance( BOX_LINE_LEFT ) );
//STRIP001
//STRIP001          if ( rBox.GetRight() )
//STRIP001                 (rRect.*fnRect->fnAddRight)( rBox.CalcLineSpace( BOX_LINE_RIGHT ) );
//STRIP001          else if ( rAttrs.IsBorderDist() )
//STRIP001                  // OD 23.01.2003 #106386# - increase of distance by one twip is incorrect.
//STRIP001                 (rRect.*fnRect->fnAddRight)( rBox.GetDistance( BOX_LINE_RIGHT ) );
//STRIP001
//STRIP001          if ( bShadow && rAttrs.GetShadow().GetLocation() != SVX_SHADOW_NONE )
//STRIP001          {
//STRIP001              const SvxShadowItem &rShadow = rAttrs.GetShadow();
//STRIP001              if ( bTop )
//STRIP001                     (rRect.*fnRect->fnSubTop)(rShadow.CalcShadowSpace(SHADOW_TOP));
//STRIP001                 (rRect.*fnRect->fnSubLeft)(rShadow.CalcShadowSpace(SHADOW_LEFT));
//STRIP001              if ( bBottom )
//STRIP001                     (rRect.*fnRect->fnAddBottom)
//STRIP001                                     (rShadow.CalcShadowSpace( SHADOW_BOTTOM ));
//STRIP001                 (rRect.*fnRect->fnAddRight)(rShadow.CalcShadowSpace(SHADOW_RIGHT));
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  ::SwAlignRect( rRect, pGlobalShell );
//STRIP001 }

//STRIP001 void MA_FASTCALL lcl_ExtendLeftAndRight( SwRect&                _rRect,
//STRIP001                                          const SwFrm&           _rFrm,
//STRIP001                                          const SwBorderAttrs&   _rAttrs,
//STRIP001                                          const SwRectFn&        _rRectFn )
//STRIP001 {
//STRIP001     // OD 21.05.2003 #108789# - extend left/right border/shadow rectangle to
//STRIP001     // bottom of previous frame/to top of next frame, if border/shadow is joined
//STRIP001     // with previous/next frame.
//STRIP001     //if ( rAttrs.GetBox().GetTop() && !rAttrs.GetTopLine( pFrm ) )
//STRIP001     if ( _rAttrs.JoinedWithPrev( _rFrm ) )
//STRIP001  {
//STRIP001         const SwFrm* pPrevFrm = _rFrm.GetPrev();
//STRIP001         (_rRect.*_rRectFn->fnSetTop)( (pPrevFrm->*_rRectFn->fnGetPrtBottom)() );
//STRIP001  }
//STRIP001     //if ( rAttrs.GetBox().GetBottom() && !rAttrs.GetBottomLine( pFrm ) )
//STRIP001     if ( _rAttrs.JoinedWithNext( _rFrm ) )
//STRIP001  {
//STRIP001         const SwFrm* pNextFrm = _rFrm.GetNext();
//STRIP001         (_rRect.*_rRectFn->fnSetBottom)( (pNextFrm->*_rRectFn->fnGetPrtTop)() );
//STRIP001  }
//STRIP001 }


//STRIP001 void MA_FASTCALL lcl_SubtractFlys( const SwFrm *pFrm, const SwPageFrm *pPage,
//STRIP001                         const SwRect &rRect, SwRegionRects &rRegion )
//STRIP001 {
//STRIP001  const SwSortDrawObjs &rObjs = *pPage->GetSortedObjs();
//STRIP001  const SwFlyFrm *pSelfFly = pFrm->IsInFly() ? pFrm->FindFlyFrm() : pRetoucheFly2;
//STRIP001  if ( !pRetoucheFly )
//STRIP001      pRetoucheFly = pRetoucheFly2;
//STRIP001
//STRIP001  for ( USHORT j = 0; (j < rObjs.Count()) && rRegion.Count(); ++j )
//STRIP001  {
//STRIP001      SdrObject *pO = rObjs[j];
//STRIP001      if ( !pO->IsWriterFlyFrame() )
//STRIP001          continue;
//STRIP001
//STRIP001      const SwFlyFrm *pFly = ((SwVirtFlyDrawObj*)pO)->GetFlyFrm();
//STRIP001
//STRIP001      if ( pSelfFly == pFly || pRetoucheFly == pFly || !rRect.IsOver( pFly->Frm() ) )
//STRIP001          continue;
//STRIP001
//STRIP001      if ( !pFly->GetFmt()->GetPrint().GetValue() &&
//STRIP001              (OUTDEV_PRINTER == pGlobalShell->GetOut()->GetOutDevType() ||
//STRIP001              pGlobalShell->IsPreView()))
//STRIP001          continue;
//STRIP001
//STRIP001      const FASTBOOL bLowerOfSelf = pSelfFly && pFly->IsLowerOf( pSelfFly ) ?
//STRIP001                                          TRUE : FALSE;
//STRIP001
//STRIP001      //Bei zeichengebundenem Fly nur diejenigen betrachten, in denen er
//STRIP001      //nicht selbst verankert ist.
//STRIP001      //#33429# Warum nur bei zeichengebundenen? Es macht doch nie Sinn
//STRIP001      //Rahmen abzuziehen in denen er selbst verankert ist oder?
//STRIP001      if ( pSelfFly && pSelfFly->IsLowerOf( pFly ) )
//STRIP001          continue;
//STRIP001
//STRIP001      //#57194# Und warum gilt das nicht analog fuer den RetoucheFly?
//STRIP001      if ( pRetoucheFly && pRetoucheFly->IsLowerOf( pFly ) )
//STRIP001          continue;
//STRIP001
//STRIP001
//STRIP001 #ifndef PRODUCT
//STRIP001      //Flys, die innerhalb des eigenen verankert sind, muessen eine
//STRIP001      //groessere OrdNum haben oder Zeichengebunden sein.
//STRIP001      if ( pSelfFly && bLowerOfSelf )
//STRIP001      {
//STRIP001          ASSERT( pFly->IsFlyInCntFrm() ||
//STRIP001                  pO->GetOrdNumDirect() > pSelfFly->GetVirtDrawObj()->GetOrdNumDirect(),
//STRIP001                  "Fly with wrong z-Order" );
//STRIP001      }
//STRIP001 #endif
//STRIP001
//STRIP001      BOOL bStopOnHell = TRUE;
//STRIP001      if ( pSelfFly )
//STRIP001      {
//STRIP001          const SdrObject *pTmp = pSelfFly->GetVirtDrawObj();
//STRIP001          if ( pO->GetLayer() == pTmp->GetLayer() )
//STRIP001          {
//STRIP001              if ( pO->GetOrdNumDirect() < pTmp->GetOrdNumDirect() )
//STRIP001                  //Im gleichen Layer werden nur obenliegende beachtet.
//STRIP001                  continue;
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              if ( !bLowerOfSelf && !pFly->GetFmt()->GetOpaque().GetValue() )
//STRIP001                  //Aus anderem Layer interessieren uns nur nicht transparente
//STRIP001                  //oder innenliegende
//STRIP001                  continue;
//STRIP001              bStopOnHell = FALSE;
//STRIP001          }
//STRIP001      }
//STRIP001      if ( pRetoucheFly )
//STRIP001      {
//STRIP001          const SdrObject *pTmp = pRetoucheFly->GetVirtDrawObj();
//STRIP001          if ( pO->GetLayer() == pTmp->GetLayer() )
//STRIP001          {
//STRIP001              if ( pO->GetOrdNumDirect() < pTmp->GetOrdNumDirect() )
//STRIP001                  //Im gleichen Layer werden nur obenliegende beachtet.
//STRIP001                  continue;
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              if ( !pFly->IsLowerOf( pRetoucheFly ) && !pFly->GetFmt()->GetOpaque().GetValue() )
//STRIP001                  //Aus anderem Layer interessieren uns nur nicht transparente
//STRIP001                  //oder innenliegende
//STRIP001                  continue;
//STRIP001              bStopOnHell = FALSE;
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      //Wenn der Inhalt des Fly Transparent ist, wird er nicht abgezogen, es sei denn
//STRIP001      //er steht im Hell-Layer (#31941#)
//STRIP001      BOOL bHell = pO->GetLayer() == pFly->GetFmt()->GetDoc()->GetHellId();
//STRIP001      if ( (bStopOnHell && bHell) ||
//STRIP001              /// OD 05.08.2002 - change internal order of condition
//STRIP001              ///    first check "!bHell", then "..->Lower()" and "..->IsNoTxtFrm()"
//STRIP001              ///    have not to be performed, if frame is in "Hell"
//STRIP001              ( !bHell && pFly->Lower() && pFly->Lower()->IsNoTxtFrm() &&
//STRIP001                ( ((SwNoTxtFrm*)pFly->Lower())->IsTransparent() ||
//STRIP001                  ((SwNoTxtFrm*)pFly->Lower())->HasAnimation() ||
//STRIP001                  pFly->GetFmt()->GetSurround().IsContour()
//STRIP001                )
//STRIP001              )
//STRIP001            )
//STRIP001          continue;
//STRIP001
//STRIP001         /// OD 08.10.2002 #103898#
//STRIP001         /// Own if-statements for transparent background/shadow of fly frames
//STRIP001         /// (#99657#) in order to handle special conditions.
//STRIP001         if ( pFly->IsBackgroundTransparent() )
//STRIP001         {
//STRIP001             /// Background <pFly> is transparent drawn. Thus normally, its region
//STRIP001             /// have not to be substracted from given region.
//STRIP001             /// But, if method is called for a fly frame and
//STRIP001             /// <pFly> is a direct lower of this fly frame and
//STRIP001             /// <pFly> inherites its transparent background brush from its parent,
//STRIP001             /// then <pFly> frame area have to be subtracted from given region.
//STRIP001             /// NOTE: Because in Status Quo transparent backgrounds can only be
//STRIP001             ///     assigned to fly frames, the handle of this special case
//STRIP001             ///     avoids drawing of transparent areas more than once, if
//STRIP001             ///     a fly frame inherites a transparent background from its
//STRIP001             ///     parent fly frame.
//STRIP001             if ( pFrm->IsFlyFrm() &&
//STRIP001                  (pFly->GetAnchor()->FindFlyFrm() == pFrm) &&
//STRIP001                  static_cast<const SwFlyFrmFmt*>(pFly->GetFmt())->IsBackgroundBrushInherited()
//STRIP001                )
//STRIP001             {
//STRIP001                 SwRect aRect;
//STRIP001                 SwBorderAttrAccess aAccess( SwFrm::GetCache(), (SwFrm*)pFly );
//STRIP001                 const SwBorderAttrs &rAttrs = *aAccess.Get();
//STRIP001                 ::lcl_CalcBorderRect( aRect, pFly, rAttrs, TRUE );
//STRIP001                 rRegion -= aRect;
//STRIP001                 continue;
//STRIP001             }
//STRIP001             else
//STRIP001             {
//STRIP001                 continue;
//STRIP001             }
//STRIP001         }
//STRIP001         if ( pFly->IsShadowTransparent() )
//STRIP001         {
//STRIP001             continue;
//STRIP001         }
//STRIP001
//STRIP001      if ( bHell && pFly->GetAnchor()->IsInFly() )
//STRIP001      {
//STRIP001          //Damit die Umrandung nicht vom Hintergrund des anderen Flys
//STRIP001          //zerlegt wird.
//STRIP001          SwRect aRect;
//STRIP001          SwBorderAttrAccess aAccess( SwFrm::GetCache(), (SwFrm*)pFly );
//STRIP001          const SwBorderAttrs &rAttrs = *aAccess.Get();
//STRIP001          ::lcl_CalcBorderRect( aRect, pFly, rAttrs, TRUE );
//STRIP001          rRegion -= aRect;
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          SwRect aRect( pFly->Prt() );
//STRIP001          aRect += pFly->Frm().Pos();
//STRIP001          rRegion -= aRect;
//STRIP001      }
//STRIP001  }
//STRIP001  if ( pRetoucheFly == pRetoucheFly2 )
//STRIP001      pRetoucheFly = 0;
//STRIP001 }

//STRIP001 inline FASTBOOL IsShortCut( const SwRect &rRect, const SwRect &rFrmRect )
//STRIP001 {
//STRIP001  //Wenn der Frm vollstaendig rechts neben bzw. unter dem
//STRIP001  //Rect sitzt ist's genug mit Painten.
//STRIP001  return ( (rFrmRect.Top()  > rRect.Bottom()) ||
//STRIP001           (rFrmRect.Left() > rRect.Right()) );
//STRIP001 }

//---------------- Ausgabe fuer das BrushItem ----------------

/** lcl_DrawGraphicBackgrd - local help method to draw a background for a graphic

    OD 17.10.2002 #103876#
    Under certain circumstances we have to draw a background for a graphic.
    This method takes care of the conditions and draws the background with the
    corresponding color.
    Method introduced for bug fix #103876# in order to optimize drawing tiled
    background graphics. Previously, this code was integrated in method
    <lcl_DrawGraphic>.
    Method implemented as a inline, checking the conditions and calling method
    method <lcl_implDrawGraphicBackgrd(..)> for the intrinsic drawing.

    @author OD

    @param _rBackgrdBrush
    background brush contain the color the background has to be drawn.

    @param _pOut
    output device the background has to be drawn in.

    @param _rPaintRect
    paint retangle in the output device, which has to be drawn with the background.
    rectangle have to be aligned by method ::SwAlignRect

    @param _rGraphicObj
    graphic object, for which the background has to be drawn. Used for checking
    the transparency of its bitmap, its type and if the graphic is drawn transparent

    @param _bNumberingGraphic
    boolean indicating that graphic is used as a numbering.

    @param _bBackgrdAlreadyDrawn
    boolean (optional; default: false) indicating, if the background is already drawn.
*/
//STRIP001 void lcl_implDrawGraphicBackgrd( const SvxBrushItem& _rBackgrdBrush,
//STRIP001                                  OutputDevice* _pOut,
//STRIP001                                  const SwRect& _rAlignedPaintRect,
//STRIP001                                  const GraphicObject& _rGraphicObj )
//STRIP001 {
//STRIP001     /// determine color of background
//STRIP001     ///     If color of background brush is not "no fill"/"auto fill" or
//STRIP001     ///     <bFlyMetafile> is set, use color of background brush, otherwise
//STRIP001     ///     use global retouche color.
//STRIP001     const Color aColor( ( (_rBackgrdBrush.GetColor() != COL_TRANSPARENT) || bFlyMetafile )
//STRIP001                         ? _rBackgrdBrush.GetColor()
//STRIP001                         : aGlobalRetoucheColor );
//STRIP001
//STRIP001     /// determine, if background color have to be drawn transparent
//STRIP001     /// and calculate transparency percent value
//STRIP001     sal_Int8 nTransparencyPercent = 0;
//STRIP001     bool bDrawTransparent = false;
//STRIP001     if ( aColor.GetTransparency() != 0 )
//STRIP001     ///     background color is transparent --> draw transparent.
//STRIP001     {
//STRIP001         bDrawTransparent = true;
//STRIP001         nTransparencyPercent = (aColor.GetTransparency()*100 + 0x7F)/0xFF;
//STRIP001     }
//STRIP001     else if ( (_rGraphicObj.GetAttr().GetTransparency() != 0) &&
//STRIP001                 (_rBackgrdBrush.GetColor() == COL_TRANSPARENT) )
//STRIP001     ///     graphic is drawn transparent and background color is
//STRIP001     ///     "no fill"/"auto fill" --> draw transparent
//STRIP001     {
//STRIP001         bDrawTransparent = true;
//STRIP001         nTransparencyPercent = (_rGraphicObj.GetAttr().GetTransparency()*100 + 0x7F)/0xFF;
//STRIP001     }
//STRIP001
//STRIP001     if ( bDrawTransparent )
//STRIP001     {
//STRIP001         /// draw background transparent
//STRIP001         if( _pOut->GetFillColor() != aColor.GetRGBColor() )
//STRIP001             _pOut->SetFillColor( aColor.GetRGBColor() );
//STRIP001         PolyPolygon aPoly( _rAlignedPaintRect.SVRect() );
//STRIP001         _pOut->DrawTransparent( aPoly, nTransparencyPercent );
//STRIP001     }
//STRIP001     else
//STRIP001     {
//STRIP001         /// draw background opaque
//STRIP001         if ( _pOut->GetFillColor() != aColor )
//STRIP001             _pOut->SetFillColor( aColor );
//STRIP001         _pOut->DrawRect( _rAlignedPaintRect.SVRect() );
//STRIP001     }
//STRIP001 }

//STRIP001 inline void lcl_DrawGraphicBackgrd( const SvxBrushItem& _rBackgrdBrush,
//STRIP001                                     OutputDevice* _pOut,
//STRIP001                                     const SwRect& _rAlignedPaintRect,
//STRIP001                                     const GraphicObject& _rGraphicObj,
//STRIP001                                     bool _bNumberingGraphic,
//STRIP001                                     bool _bBackgrdAlreadyDrawn = false )
//STRIP001 {
//STRIP001     /// draw background with background color, if
//STRIP001     ///     (1) graphic is not used as a numbering AND
//STRIP001     ///     (2) background is not already drawn AND
//STRIP001     ///     (3) intrinsic graphic is transparent OR intrinsic graphic doesn't exists
//STRIP001     if ( !_bNumberingGraphic &&
//STRIP001          !_bBackgrdAlreadyDrawn &&
//STRIP001          ( _rGraphicObj.IsTransparent() || _rGraphicObj.GetType() == GRAPHIC_NONE  )
//STRIP001        )
//STRIP001     {
//STRIP001         lcl_implDrawGraphicBackgrd( _rBackgrdBrush, _pOut, _rAlignedPaintRect, _rGraphicObj );
//STRIP001     }
//STRIP001 }

/// OD 06.08.2002 #99657# - Note: the transparency of the background graphic
///     is saved in SvxBrushItem.GetGraphicObject(<shell>).GetAttr().Set/GetTransparency()
///     and is considered in the drawing of the graphic.
///     Thus, to provide transparent background graphic for text frames nothing
///     has to be coded.
/// OD 25.09.2002 #99739# - use align rectangle for drawing graphic
/// OD 25.09.2002 #99739# - pixel-align coordinations for drawing graphic.
/// OD 17.10.2002 #103876# - outsource code for drawing background of the graphic
///     with a background color in method <lcl_DrawGraphicBackgrd>
///     Also, change type of <bGrfNum> and <bClip> from <BOOL> to <bool>.
//STRIP001 void lcl_DrawGraphic( const SvxBrushItem& rBrush, OutputDevice *pOut,
//STRIP001                    ViewShell &rSh, const SwRect &rGrf, const SwRect &rOut,
//STRIP001                       bool bClip, bool bGrfNum,
//STRIP001                       bool bBackgrdAlreadyDrawn = false )
//STRIP001                       /// OD 02.09.2002 #99657#
//STRIP001                       /// add parameter <bBackgrdAlreadyDrawn> to indicate
//STRIP001                       /// that the background is already drawn.
//STRIP001 {
//STRIP001     /// OD 25.09.2002 #99739# - calculate align rectangle from parameter <rGrf>
//STRIP001     ///     and use aligned rectangle <aAlignedGrfRect> in the following code
//STRIP001     SwRect aAlignedGrfRect = rGrf;
//STRIP001     ::SwAlignRect( aAlignedGrfRect, &rSh );
//STRIP001
//STRIP001     /// OD 17.10.2002 #103876# - change type from <FASTBOOL> to <bool>.
//STRIP001     const bool bNotInside = bClip && !rOut.IsInside( aAlignedGrfRect );
//STRIP001  if ( bNotInside )
//STRIP001  {
//STRIP001      pOut->Push( PUSH_CLIPREGION );
//STRIP001      pOut->IntersectClipRegion( rOut.SVRect() );
//STRIP001  }
//STRIP001
//STRIP001  //Hier kein Link, wir wollen die Grafik synchron laden!
//STRIP001     ((SvxBrushItem&)rBrush).SetDoneLink( Link() );
//STRIP001  GraphicObject *pGrf = (GraphicObject*)rBrush.GetGraphicObject(
//STRIP001                                                  GETOBJSHELL() );
//STRIP001
//STRIP001     /// OD 17.10.2002 #103876# - outsourcing drawing of background with a background color.
//STRIP001     ::lcl_DrawGraphicBackgrd( rBrush, pOut, aAlignedGrfRect, *pGrf, bGrfNum, bBackgrdAlreadyDrawn );
//STRIP001
//STRIP001     /// OD 25.09.2002 #99739# -
//STRIP001     /// Because for drawing a graphic left-top-corner and size coordinations are
//STRIP001     /// used, these coordinations have to be determined on pixel level.
//STRIP001     ::SwAlignGrfRect( &aAlignedGrfRect, *pOut );
//STRIP001     pGrf->Draw( pOut, aAlignedGrfRect.Pos(), aAlignedGrfRect.SSize() );
//STRIP001
//STRIP001  if ( bNotInside )
//STRIP001      pOut->Pop();
//STRIP001 } // end of method <lcl_DrawGraphic>

//STRIP001 void MA_FASTCALL DrawGraphic( const SvxBrushItem *pBrush,
//STRIP001                               OutputDevice *pOutDev,
//STRIP001                               const SwRect &rOrg,
//STRIP001                               const SwRect &rOut,
//STRIP001                               const BYTE nGrfNum,
//STRIP001                               const sal_Bool bConsiderBackgroundTransparency )
//STRIP001     /// OD 05.08.2002 #99657# - add 6th parameter to indicate that method should
//STRIP001     ///   consider background transparency, saved in the color of the brush item
//STRIP001 {
//STRIP001     ViewShell &rSh = *pGlobalShell;
//STRIP001     /// OD 17.10.2002 #103876# - change type from <BOOL> to <bool>
//STRIP001     bool bReplaceGrfNum = GRFNUM_REPLACE == nGrfNum;
//STRIP001     bool bGrfNum = GRFNUM_NO != nGrfNum;
//STRIP001  Size aGrfSize;
//STRIP001  SvxGraphicPosition ePos = GPOS_NONE;
//STRIP001  if( pBrush && !bReplaceGrfNum )
//STRIP001  {
//STRIP001      if( rSh.GetViewOptions()->IsGraphic() )
//STRIP001      {
//STRIP001          ((SvxBrushItem*)pBrush)->SetDoneLink( STATIC_LINK(
//STRIP001                                  rSh.GetDoc(), SwDoc, BackgroundDone ) );
//STRIP001          SfxObjectShell &rObjSh = *GETOBJSHELL();
//STRIP001          const Graphic* pGrf = pBrush->GetGraphic( &rObjSh );
//STRIP001          if( pGrf && GRAPHIC_NONE != pGrf->GetType() )
//STRIP001          {
//STRIP001              ePos = pBrush->GetGraphicPos();
//STRIP001              if( pGrf->IsSupportedGraphic() )
//STRIP001                  // don't the use the specific output device! Bug 94802
//STRIP001                     aGrfSize = ::GetGraphicSizeTwip( *pGrf, 0 );
//STRIP001          }
//STRIP001      }
//STRIP001      else
//STRIP001          bReplaceGrfNum = bGrfNum;
//STRIP001  }
//STRIP001
//STRIP001  SwRect aGrf;
//STRIP001  aGrf.SSize( aGrfSize );
//STRIP001  FASTBOOL bDraw = TRUE;
//STRIP001  FASTBOOL bRetouche = TRUE;
//STRIP001  switch ( ePos )
//STRIP001  {
//STRIP001  case GPOS_LT:
//STRIP001      aGrf.Pos() = rOrg.Pos();
//STRIP001      break;
//STRIP001
//STRIP001  case GPOS_MT:
//STRIP001      aGrf.Pos().Y() = rOrg.Top();
//STRIP001      aGrf.Pos().X() = rOrg.Left() + rOrg.Width()/2 - aGrfSize.Width()/2;
//STRIP001      break;
//STRIP001
//STRIP001  case GPOS_RT:
//STRIP001      aGrf.Pos().Y() = rOrg.Top();
//STRIP001      aGrf.Pos().X() = rOrg.Right() - aGrfSize.Width();
//STRIP001      break;
//STRIP001
//STRIP001  case GPOS_LM:
//STRIP001      aGrf.Pos().Y() = rOrg.Top() + rOrg.Height()/2 - aGrfSize.Height()/2;
//STRIP001      aGrf.Pos().X() = rOrg.Left();
//STRIP001      break;
//STRIP001
//STRIP001  case GPOS_MM:
//STRIP001      aGrf.Pos().Y() = rOrg.Top() + rOrg.Height()/2 - aGrfSize.Height()/2;
//STRIP001      aGrf.Pos().X() = rOrg.Left() + rOrg.Width()/2 - aGrfSize.Width()/2;
//STRIP001      break;
//STRIP001
//STRIP001  case GPOS_RM:
//STRIP001      aGrf.Pos().Y() = rOrg.Top() + rOrg.Height()/2 - aGrfSize.Height()/2;
//STRIP001      aGrf.Pos().X() = rOrg.Right() - aGrfSize.Width();
//STRIP001      break;
//STRIP001
//STRIP001  case GPOS_LB:
//STRIP001      aGrf.Pos().Y() = rOrg.Bottom() - aGrfSize.Height();
//STRIP001      aGrf.Pos().X() = rOrg.Left();
//STRIP001      break;
//STRIP001
//STRIP001  case GPOS_MB:
//STRIP001      aGrf.Pos().Y() = rOrg.Bottom() - aGrfSize.Height();
//STRIP001      aGrf.Pos().X() = rOrg.Left() + rOrg.Width()/2 - aGrfSize.Width()/2;
//STRIP001      break;
//STRIP001
//STRIP001  case GPOS_RB:
//STRIP001      aGrf.Pos().Y() = rOrg.Bottom() - aGrfSize.Height();
//STRIP001      aGrf.Pos().X() = rOrg.Right() - aGrfSize.Width();
//STRIP001      break;
//STRIP001
//STRIP001  case GPOS_AREA:
//STRIP001      aGrf = rOrg;
//STRIP001         /// OD 05.09.2002 #102912#
//STRIP001         /// In spite the fact that the background graphic have to fill the complete
//STRIP001         /// area, it has been checked, if the graphic will completely fill out
//STRIP001         /// the region to be painted <rOut> and thus, nothing has to be retouched.
//STRIP001         /// For example, this is the case for a fly frame without a background
//STRIP001         /// brush positioned on the border of the page and inherited the
//STRIP001         /// background brush from the page.
//STRIP001         bRetouche = !rOut.IsInside( aGrf );
//STRIP001      break;
//STRIP001
//STRIP001  case GPOS_TILED:
//STRIP001      {
//STRIP001             // OD 17.10.2002 #103876# - draw background of tiled graphic
//STRIP001             // before drawing tiled graphic in loop
//STRIP001             // determine graphic object
//STRIP001             GraphicObject* pGraphicObj = const_cast< GraphicObject* >(pBrush->GetGraphicObject( GETOBJSHELL() ));
//STRIP001             // calculate aligned paint rectangle
//STRIP001             SwRect aAlignedPaintRect = rOut;
//STRIP001             ::SwAlignRect( aAlignedPaintRect, &rSh );
//STRIP001             // OD 25.10.2002 #103876# - draw background color for aligned paint rectangle
//STRIP001             lcl_DrawGraphicBackgrd( *pBrush, pOutDev, aAlignedPaintRect, *pGraphicObj, bGrfNum );
//STRIP001
//STRIP001             // set left-top-corner of background graphic to left-top-corner of the
//STRIP001             // area, from which the background brush is determined.
//STRIP001             aGrf.Pos() = rOrg.Pos();
//STRIP001             // setup clipping at output device
//STRIP001             pOutDev->Push( PUSH_CLIPREGION );
//STRIP001             pOutDev->IntersectClipRegion( rOut.SVRect() );
//STRIP001             // OD 28.10.2002 #103876# - use new method <GraphicObject::DrawTiled(::)>
//STRIP001             {
//STRIP001                 // calculate paint offset
//STRIP001                 Point aPaintOffset( aAlignedPaintRect.Pos() - aGrf.Pos() );
//STRIP001                 // draw background graphic tiled for aligned paint rectangle
//STRIP001                 pGraphicObj->DrawTiled( pOutDev,
//STRIP001                                         aAlignedPaintRect.SVRect(),
//STRIP001                                         aGrf.SSize(),
//STRIP001                                         Size( aPaintOffset.X(), aPaintOffset.Y() ) );
//STRIP001             }
//STRIP001             // reset clipping at output device
//STRIP001             pOutDev->Pop();
//STRIP001             // set <bDraw> and <bRetouche> to false, indicating that background
//STRIP001             // graphic and background are already drawn.
//STRIP001             bDraw = bRetouche = FALSE;
//STRIP001      }
//STRIP001      break;
//STRIP001
//STRIP001  case GPOS_NONE:
//STRIP001      bDraw = FALSE;
//STRIP001      break;
//STRIP001
//STRIP001     default: ASSERT( !pOutDev, "new Graphic position?" );
//STRIP001  }
//STRIP001
//STRIP001     /// OD 02.09.2002 #99657#
//STRIP001     /// init variable <bGrfBackgrdAlreadDrawn> to indicate, if background of
//STRIP001     /// graphic is already drawn or not.
//STRIP001     bool bGrfBackgrdAlreadyDrawn = false;
//STRIP001  if ( bRetouche )
//STRIP001  {
//STRIP001         pOutDev->Push( PUSH_FILLCOLOR );
//STRIP001
//STRIP001         /// OD 07.08.2002 #99657# #GetTransChg#
//STRIP001         ///     check, if a existing background graphic (not filling the complete
//STRIP001         ///     background) is transparent drawn and the background color is
//STRIP001         ///     "no fill" respectively "auto fill", if background transparency
//STRIP001         ///     has to be considered.
//STRIP001         ///     If YES, memorise transparency of background graphic.
//STRIP001         ///     check also, if background graphic bitmap is transparent.
//STRIP001         bool bTransparentGrfWithNoFillBackgrd = false;
//STRIP001         sal_Int32 nGrfTransparency = 0;
//STRIP001         bool bGrfIsTransparent = false;
//STRIP001         if ( (ePos != GPOS_NONE) &&
//STRIP001              (ePos != GPOS_TILED) && (ePos != GPOS_AREA)
//STRIP001            )
//STRIP001         {
//STRIP001             GraphicObject *pGrf = (GraphicObject*)pBrush->GetGraphicObject(
//STRIP001                                                     GETOBJSHELL() );
//STRIP001             if ( bConsiderBackgroundTransparency )
//STRIP001             {
//STRIP001                 GraphicAttr pGrfAttr = pGrf->GetAttr();
//STRIP001                 if ( (pGrfAttr.GetTransparency() != 0) &&
//STRIP001                      ( pBrush && (pBrush->GetColor() == COL_TRANSPARENT) )
//STRIP001                    )
//STRIP001                 {
//STRIP001                     bTransparentGrfWithNoFillBackgrd = true;
//STRIP001                     nGrfTransparency = pGrfAttr.GetTransparency();
//STRIP001                 }
//STRIP001             }
//STRIP001             if ( pGrf->IsTransparent() )
//STRIP001             {
//STRIP001                 bGrfIsTransparent = true;
//STRIP001             }
//STRIP001         }
//STRIP001
//STRIP001         /// OD 06.08.2002 #99657# #GetTransChg# - to get color of brush,
//STRIP001         ///     check background color against COL_TRANSPARENT ("no fill"/"auto fill")
//STRIP001         ///     instead of checking, if transparency is not set.
//STRIP001         const Color aColor( pBrush &&
//STRIP001                             ( !(pBrush->GetColor() == COL_TRANSPARENT) ||
//STRIP001                               bFlyMetafile )
//STRIP001                     ? pBrush->GetColor()
//STRIP001                     : aGlobalRetoucheColor );
//STRIP001
//STRIP001         /// OD 08.08.2002 #99657# - determine, if background region have to be
//STRIP001         ///     drawn transparent.
//STRIP001         ///     background region has to be drawn transparent, if
//STRIP001         ///         background transparency have to be considered
//STRIP001         ///     AND
//STRIP001         ///       ( background color is transparent OR
//STRIP001         ///         background graphic is transparent and background color is "no fill"
//STRIP001         ///       )
//STRIP001         sal_Bool bDrawTransparent = bConsiderBackgroundTransparency &&
//STRIP001                                 ( ( aColor.GetTransparency() != 0) ||
//STRIP001                                     bTransparentGrfWithNoFillBackgrd );
//STRIP001
//STRIP001         /// OD 06.08.2002 #99657# - if background region have to be drawn
//STRIP001         ///     transparent, set only the RGB values of the background color as
//STRIP001         ///     the fill color for the output device.
//STRIP001         if ( bDrawTransparent )
//STRIP001         {
//STRIP001             if( pOutDev->GetFillColor() != aColor.GetRGBColor() )
//STRIP001                 pOutDev->SetFillColor( aColor.GetRGBColor() );
//STRIP001         }
//STRIP001         else
//STRIP001         {
//STRIP001             if( pOutDev->GetFillColor() != aColor )
//STRIP001                 pOutDev->SetFillColor( aColor );
//STRIP001         }
//STRIP001
//STRIP001         /// OD 02.09.2002 #99657#
//STRIP001         if ( bDrawTransparent )
//STRIP001         {
//STRIP001             /// background region have to be drawn transparent.
//STRIP001             /// Thus, create a poly-polygon from the region and draw it with
//STRIP001             /// the corresponding transparency precent.
//STRIP001             PolyPolygon aDrawPoly( rOut.SVRect() );
//STRIP001             if ( aGrf.HasArea() )
//STRIP001             {
//STRIP001                 if ( !bGrfIsTransparent )
//STRIP001                 {
//STRIP001                     /// substract area of background graphic from draw area
//STRIP001                     /// OD 08.10.2002 #103898# - consider only that part of the
//STRIP001                     ///     graphic area that is overlapping with draw area.
//STRIP001                     SwRect aTmpGrf = aGrf;
//STRIP001                     aTmpGrf.Intersection( rOut );
//STRIP001                     if ( aTmpGrf.HasArea() )
//STRIP001                     {
//STRIP001                         Polygon aGrfPoly( aTmpGrf.SVRect() );
//STRIP001                         aDrawPoly.Insert( aGrfPoly );
//STRIP001                     }
//STRIP001                 }
//STRIP001                 else
//STRIP001                     bGrfBackgrdAlreadyDrawn = true;
//STRIP001             }
//STRIP001             /// calculate transparency percent:
//STRIP001             /// ( <transparency value[0x01..0xFF]>*100 + 0x7F ) / 0xFF
//STRIP001             /// If there is a background graphic with a background color "no fill"/"auto fill",
//STRIP001             /// the transparency value is taken from the background graphic,
//STRIP001             /// otherwise take the transparency value from the color.
//STRIP001             sal_Int8 nTransparencyPercent =
//STRIP001               (( bTransparentGrfWithNoFillBackgrd ? nGrfTransparency : aColor.GetTransparency()
//STRIP001                )*100 + 0x7F)/0xFF;
//STRIP001             /// draw poly-polygon transparent
//STRIP001             pOutDev->DrawTransparent( aDrawPoly, nTransparencyPercent );
//STRIP001         }
//STRIP001         else
//STRIP001         {
//STRIP001             SwRegionRects aRegion( rOut, 4 );
//STRIP001             if ( !bGrfIsTransparent )
//STRIP001                 aRegion -= aGrf;
//STRIP001             else
//STRIP001                 bGrfBackgrdAlreadyDrawn = true;
//STRIP001             /// loop rectangles of background region, which has to be drawn
//STRIP001             for( USHORT i = 0; i < aRegion.Count(); ++i )
//STRIP001             {
//STRIP001                 pOutDev->DrawRect( aRegion[i].SVRect() );
//STRIP001             }
//STRIP001         }
//STRIP001        pOutDev ->Pop();
//STRIP001  }
//STRIP001
//STRIP001     if( bDraw && aGrf.IsOver( rOut ) )
//STRIP001         /// OD 02.09.2002 #99657#
//STRIP001         /// add parameter <bGrfBackgrdAlreadyDrawn>
//STRIP001         lcl_DrawGraphic( *pBrush, pOutDev, rSh, aGrf, rOut, true, bGrfNum,
//STRIP001                          bGrfBackgrdAlreadyDrawn );
//STRIP001
//STRIP001  if( bReplaceGrfNum )
//STRIP001  {
//STRIP001      const Bitmap& rBmp = SwNoTxtFrm::GetBitmap( FALSE );
//STRIP001         Font aTmp( pOutDev->GetFont() );
//STRIP001         ((Graphic*)0)->Draw( pOutDev, aEmptyStr, aTmp, rBmp,
//STRIP001                           rOrg.Pos(), rOrg.SSize() );
//STRIP001  }
//STRIP001 }

//------------------------------------------------------------------------

/** local help method for SwRootFrm::Paint(..) - Adjust given rectangle to pixel size

    By OD at 27.09.2002 for #103636#
    In order to avoid paint errors caused by multiple alignments - e.g. method
    ::SwAlignRect(..) - and other changes to the rectangle to be painted,
    this method is called for the rectangle to be painted in order to
    adjust it to the pixel it is overlapping.

    @author OD
*/
//STRIP001 void lcl_AdjustRectToPixelSize( SwRect& io_aSwRect, const OutputDevice &aOut )
//STRIP001 {
//STRIP001     /// local constant object of class <Size> to determine number of Twips
//STRIP001     /// representing a pixel.
//STRIP001     const Size aTwipToPxSize( aOut.PixelToLogic( Size( 1,1 )) );
//STRIP001
//STRIP001     /// local object of class <Rectangle> in Twip coordinates
//STRIP001     /// calculated from given rectangle aligned to pixel centers.
//STRIP001     const Rectangle aPxCenterRect = aOut.PixelToLogic(
//STRIP001             aOut.LogicToPixel( io_aSwRect.SVRect() ) );
//STRIP001
//STRIP001     /// local constant object of class <Rectangle> representing given rectangle
//STRIP001     /// in pixel.
//STRIP001     const Rectangle aOrgPxRect = aOut.LogicToPixel( io_aSwRect.SVRect() );
//STRIP001
//STRIP001     /// calculate adjusted rectangle from pixel centered rectangle.
//STRIP001     /// Due to rounding differences <aPxCenterRect> doesn't exactly represents
//STRIP001     /// the Twip-centers. Thus, adjust borders by half of pixel width/height plus 1.
//STRIP001     /// Afterwards, adjust calculated Twip-positions of the all borders.
//STRIP001     Rectangle aSizedRect = aPxCenterRect;
//STRIP001     aSizedRect.Left() -= (aTwipToPxSize.Width()/2 + 1);
//STRIP001     aSizedRect.Right() += (aTwipToPxSize.Width()/2 + 1);
//STRIP001     aSizedRect.Top() -= (aTwipToPxSize.Height()/2 + 1);
//STRIP001     aSizedRect.Bottom() += (aTwipToPxSize.Height()/2 + 1);
//STRIP001
//STRIP001     /// adjust left()
//STRIP001     while ( (aOut.LogicToPixel(aSizedRect)).Left() < aOrgPxRect.Left() )
//STRIP001     {
//STRIP001         ++aSizedRect.Left();
//STRIP001     }
//STRIP001     /// adjust right()
//STRIP001     while ( (aOut.LogicToPixel(aSizedRect)).Right() > aOrgPxRect.Right() )
//STRIP001     {
//STRIP001         --aSizedRect.Right();
//STRIP001     }
//STRIP001     /// adjust top()
//STRIP001     while ( (aOut.LogicToPixel(aSizedRect)).Top() < aOrgPxRect.Top() )
//STRIP001     {
//STRIP001         ++aSizedRect.Top();
//STRIP001     }
//STRIP001     /// adjust bottom()
//STRIP001     while ( (aOut.LogicToPixel(aSizedRect)).Bottom() > aOrgPxRect.Bottom() )
//STRIP001     {
//STRIP001         --aSizedRect.Bottom();
//STRIP001     }
//STRIP001
//STRIP001     io_aSwRect = SwRect( aSizedRect );
//STRIP001
//STRIP001 #ifndef PRODUCT
//STRIP001     Rectangle aTestOrgPxRect = aOut.LogicToPixel( io_aSwRect.SVRect() );
//STRIP001     Rectangle aTestNewPxRect = aOut.LogicToPixel( aSizedRect );
//STRIP001     ASSERT( aTestOrgPxRect == aTestNewPxRect,
//STRIP001             "Error in lcl_AlignRectToPixelSize(..): Adjusted rectangle has incorrect position or size");
//STRIP001 #if OSL_DEBUG_LEVEL > 1
//STRIP001     Rectangle aTestNewRect( aSizedRect );
//STRIP001     /// check Left()
//STRIP001     --aSizedRect.Left();
//STRIP001     aTestNewPxRect = aOut.LogicToPixel( aSizedRect );
//STRIP001     ASSERT( aTestOrgPxRect.Left() >= (aTestNewPxRect.Left()+1),
//STRIP001             "Error in lcl_AlignRectToPixelSize(..): Left() not correct adjusted");
//STRIP001     ++aSizedRect.Left();
//STRIP001     /// check Right()
//STRIP001     ++aSizedRect.Right();
//STRIP001     aTestNewPxRect = aOut.LogicToPixel( aSizedRect );
//STRIP001     ASSERT( aTestOrgPxRect.Right() <= (aTestNewPxRect.Right()-1),
//STRIP001             "Error in lcl_AlignRectToPixelSize(..): Right() not correct adjusted");
//STRIP001     --aSizedRect.Right();
//STRIP001     /// check Top()
//STRIP001     --aSizedRect.Top();
//STRIP001     aTestNewPxRect = aOut.LogicToPixel( aSizedRect );
//STRIP001     ASSERT( aTestOrgPxRect.Top() >= (aTestNewPxRect.Top()+1),
//STRIP001             "Error in lcl_AlignRectToPixelSize(..): Top() not correct adjusted");
//STRIP001     ++aSizedRect.Top();
//STRIP001     /// check Bottom()
//STRIP001     ++aSizedRect.Bottom();
//STRIP001     aTestNewPxRect = aOut.LogicToPixel( aSizedRect );
//STRIP001     ASSERT( aTestOrgPxRect.Bottom() <= (aTestNewPxRect.Bottom()-1),
//STRIP001             "Error in lcl_AlignRectToPixelSize(..): Bottom() not correct adjusted");
//STRIP001     --aSizedRect.Bottom();
//STRIP001 #endif
//STRIP001 #endif
//STRIP001 }

/*************************************************************************
|*
|*  SwRootFrm::Paint()
|*
|*  Beschreibung
|*      Fuer jede sichtbare Seite, die von Rect berhrt wird einmal Painten.
|*      1. Umrandungen und Hintergruende Painten.
|*      2. Den DrawLayer (Ramen und Zeichenobjekte) der unter dem Dokument
|*         liegt painten (Hoelle).
|*      3. Den Dokumentinhalt (Text) Painten.
|*      4. Den Drawlayer der ueber dem Dokuemnt liegt painten.
|*
|*  Ersterstellung      MA 01. Jun. 92
|*  Letzte Aenderung    MA 10. Oct. 97
|*
|*************************************************************************/

//STRIP001 void SwRootFrm::Paint( const SwRect& rRect ) const
//STRIP001 {
//STRIP001  ASSERT( Lower() && Lower()->IsPageFrm(), "Lower der Root keine Seite." );
//STRIP001
//STRIP001  PROTOCOL( this, PROT_FILE_INIT, 0, 0)
//STRIP001
//STRIP001  FASTBOOL bResetRootPaint = FALSE;
//STRIP001  ViewShell *pSh = pCurrShell;
//STRIP001
//STRIP001  if ( pSh->GetWin() )
//STRIP001  {
//STRIP001      if ( pSh->GetOut() == pSh->GetWin() && !pSh->GetWin()->IsVisible() )
//STRIP001      {
//STRIP001          return;
//STRIP001      }
//STRIP001      if ( SwRootFrm::bInPaint )
//STRIP001      {
//STRIP001          SwPaintQueue::Add( pSh, rRect );
//STRIP001          return;
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001      SwRootFrm::bInPaint = bResetRootPaint = TRUE;
//STRIP001
//STRIP001  SwSavePaintStatics *pStatics = 0;
//STRIP001  if ( pGlobalShell )
//STRIP001      pStatics = new SwSavePaintStatics();
//STRIP001  pGlobalShell = pSh;
//STRIP001
//STRIP001  bOneBeepOnly = pSh->GetWin() != 0 && pSh->GetDoc()->IsFrmBeepEnabled();
//STRIP001  if( !pSh->GetWin() )
//STRIP001      pProgress = SfxProgress::GetActiveProgress( (SfxObjectShell*) pSh->GetDoc()->GetDocShell() );
//STRIP001
//STRIP001  ::SwCalcPixStatics( pSh->GetOut() );
//STRIP001  aGlobalRetoucheColor = pSh->Imp()->GetRetoucheColor();
//STRIP001
//STRIP001  //Ggf. eine Action ausloesen um klare Verhaeltnisse zu schaffen.
//STRIP001  //Durch diesen Kunstgriff kann in allen Paints davon ausgegangen werden,
//STRIP001  //das alle Werte gueltigt sind - keine Probleme, keine Sonderbehandlung(en).
//STRIP001  if ( !pSh->IsInEndAction() && !pSh->IsPaintInProgress() &&
//STRIP001       (!pSh->Imp()->IsAction() || !pSh->Imp()->GetLayAction().IsActionInProgress() ) )
//STRIP001  {
//STRIP001      ((SwRootFrm*)this)->ResetTurbo();
//STRIP001      SwLayAction aAction( (SwRootFrm*)this, pSh->Imp() );
//STRIP001      aAction.SetPaint( FALSE );
//STRIP001      aAction.SetComplete( FALSE );
//STRIP001      aAction.SetReschedule( pProgress ? TRUE : FALSE );
//STRIP001      aAction.Action();
//STRIP001      ((SwRootFrm*)this)->ResetTurboFlag();
//STRIP001      if ( !pSh->ActionPend() )
//STRIP001          pSh->Imp()->DelRegions();
//STRIP001  }
//STRIP001
//STRIP001  SwRect aRect( rRect );
//STRIP001     aRect.Intersection( pSh->VisArea() );
//STRIP001
//STRIP001  FASTBOOL bExtraData = ::IsExtraData( GetFmt()->GetDoc() );
//STRIP001
//STRIP001  pLines = new SwLineRects;   //Sammler fuer Umrandungen.
//STRIP001
//STRIP001     // #104289#. During painting, something (OLE) can
//STRIP001     // load the linguistic, which in turn can cause a reformat
//STRIP001     // of the document. Dangerous! We better set this flag to
//STRIP001     // avoid the reformat.
//STRIP001     const sal_Bool bOldAction = IsCallbackActionEnabled();
//STRIP001     ((SwRootFrm*)this)->SetCallbackActionEnabled( FALSE );
//STRIP001
//STRIP001  const SwPageFrm *pPage = pSh->Imp()->GetFirstVisPage();
//STRIP001
//STRIP001  while ( pPage && !::IsShortCut( aRect, pPage->Frm() ) )
//STRIP001  {
//STRIP001      if ( !pPage->IsEmptyPage() && aRect.IsOver( pPage->Frm() ) )
//STRIP001      {
//STRIP001          if ( pSh->GetWin() )
//STRIP001             {
//STRIP001              pSubsLines = new SwSubsRects;
//STRIP001                 // OD 18.11.2002 #99672# - create array for special sub-lines
//STRIP001                 pSpecSubsLines = new SwSubsRects;
//STRIP001             }
//STRIP001
//STRIP001          SwRect aPaintRect( pPage->Frm() );
//STRIP001          aPaintRect._Intersection( aRect );
//STRIP001
//STRIP001          if ( bExtraData )
//STRIP001          {
//STRIP001              //Ja, das ist grob, aber wie macht man es besser?
//STRIP001                 SWRECTFN( pPage )
//STRIP001                 (aPaintRect.*fnRect->fnSetLeftAndWidth)(
//STRIP001                     (pPage->Frm().*fnRect->fnGetLeft)(),
//STRIP001                     (pPage->Frm().*fnRect->fnGetWidth)() );
//STRIP001              aPaintRect._Intersection( pSh->VisArea() );
//STRIP001          }
//STRIP001
//STRIP001             /// OD 27.09.2002 #103636# - changed method SwLayVout::Enter(..)
//STRIP001             /// 2nd parameter is no longer <const> and will be set to the
//STRIP001             /// rectangle the virtual output device is calculated from <aPaintRect>,
//STRIP001             /// if the virtual output is used.
//STRIP001             pVout->Enter( pSh, aPaintRect, !bNoVirDev );
//STRIP001
//STRIP001             /// OD 27.09.2002 #103636# - adjust paint rectangle to pixel size
//STRIP001             /// Thus, all objects overlapping on pixel level with the unadjusted
//STRIP001             /// paint rectangle will be considered in the paint.
//STRIP001             lcl_AdjustRectToPixelSize( aPaintRect, *(pSh->GetOut()) );
//STRIP001
//STRIP001          pVout->SetOrgRect( aPaintRect );
//STRIP001
//STRIP001          pPage->PaintBaBo( aPaintRect, pPage, TRUE );
//STRIP001
//STRIP001             /// OD 29.08.2002 #102450#
//STRIP001             /// determine background color of page for <PaintLayer> method
//STRIP001             /// calls, paint <hell> or <heaven>
//STRIP001             const Color aPageBackgrdColor = pPage->GetDrawBackgrdColor();
//STRIP001
//STRIP001          if ( pSh->Imp()->HasDrawView() )
//STRIP001          {
//STRIP001                 pLines->LockLines( TRUE );
//STRIP001                 // OD 29.08.2002 #102450# - add 3rd parameter
//STRIP001                 // OD 09.12.2002 #103045# - add 4th parameter for horizontal text direction.
//STRIP001                 pSh->Imp()->PaintLayer( pSh->GetDoc()->GetHellId(), aPaintRect,
//STRIP001                                         &aPageBackgrdColor, (pPage->IsRightToLeft() ? true : false) );
//STRIP001              pLines->PaintLines( pSh->GetOut() );
//STRIP001              pLines->LockLines( FALSE );
//STRIP001          }
//STRIP001
//STRIP001             if( pSh->GetWin() )
//STRIP001             {
//STRIP001                 // OD 18.11.2002 #99672# - collect sub-lines
//STRIP001                 pPage->RefreshSubsidiary( aPaintRect );
//STRIP001                 // OD 18.11.2002 #99672# - paint special sub-lines
//STRIP001                 pSpecSubsLines->PaintSubsidiary( pSh->GetOut(), NULL );
//STRIP001             }
//STRIP001
//STRIP001             pPage->Paint( aPaintRect );
//STRIP001
//STRIP001             // OD 20.12.2002 #94627# - no paint of page border and shadow, if
//STRIP001             // writer is in place mode.
//STRIP001             if( pSh->GetWin() &&
//STRIP001                 !pSh->GetDoc()->GetDocShell()->GetProtocol().IsInPlaceActive() )
//STRIP001             {
//STRIP001                 // OD 12.02.2003 #i9719#, #105645# - use new method
//STRIP001                 // <SwPageFrm::PaintBorderAndShadow(..)>.
//STRIP001                 pPage->PaintBorderAndShadow( pPage->Frm(), pSh );
//STRIP001             }
//STRIP001
//STRIP001          pLines->PaintLines( pSh->GetOut() );
//STRIP001
//STRIP001          BOOL bControlExtra = FALSE;
//STRIP001          if ( pSh->Imp()->HasDrawView() )
//STRIP001          {
//STRIP001                 /// OD 29.08.2002 #102450# - add 3rd parameter
//STRIP001                 // OD 09.12.2002 #103045# - add 4th parameter for horizontal text direction.
//STRIP001                 pSh->Imp()->PaintLayer( pSh->GetDoc()->GetHeavenId(), aPaintRect,
//STRIP001                                         &aPageBackgrdColor,
//STRIP001                                         (pPage->IsRightToLeft() ? true : false) );
//STRIP001              if( pVout->IsFlushable() )
//STRIP001                  bControlExtra = TRUE;
//STRIP001              else
//STRIP001                     pSh->Imp()->PaintLayer( pSh->GetDoc()->GetControlsId(), aPaintRect );
//STRIP001              pLines->PaintLines( pSh->GetOut() );
//STRIP001          }
//STRIP001
//STRIP001          if ( bExtraData )
//STRIP001                 pPage->RefreshExtraData( aPaintRect );
//STRIP001
//STRIP001             if ( pSh->GetWin() )
//STRIP001          {
//STRIP001                 pSubsLines->PaintSubsidiary( pSh->GetOut(), pLines );
//STRIP001              DELETEZ( pSubsLines );
//STRIP001                 DELETEZ( pSpecSubsLines );
//STRIP001             }
//STRIP001          pVout->Leave();
//STRIP001          if( bControlExtra )
//STRIP001                 pSh->Imp()->PaintLayer( pSh->GetDoc()->GetControlsId(), aPaintRect );
//STRIP001      }
//STRIP001      ASSERT( !pPage->GetNext() || pPage->GetNext()->IsPageFrm(),
//STRIP001              "Nachbar von Seite keine Seite." );
//STRIP001      pPage = (SwPageFrm*)pPage->GetNext();
//STRIP001  }
//STRIP001
//STRIP001  DELETEZ( pLines );
//STRIP001
//STRIP001  if ( pSh->GetWin() && pSh->Imp()->HasDrawView() &&
//STRIP001       pSh->Imp()->GetDrawView()->IsGridVisible() )
//STRIP001     {
//STRIP001         pSh->Imp()->GetDrawView()->GetPageViewPgNum(0)->DrawGrid(
//STRIP001             *pSh->GetOut(), rRect.SVRect(), SwViewOption::GetTextGridColor() );
//STRIP001     }
//STRIP001
//STRIP001  if ( bResetRootPaint )
//STRIP001      SwRootFrm::bInPaint = FALSE;
//STRIP001  if ( pStatics )
//STRIP001      delete pStatics;
//STRIP001  else
//STRIP001  {
//STRIP001      pProgress = 0;
//STRIP001      pGlobalShell = 0;
//STRIP001  }
//STRIP001
//STRIP001  if ( ViewShell::IsLstEndAction() && pSh->GetWin() && pSh->Imp()->HasDrawView() )
//STRIP001      pSh->Imp()->GetDrawView()->PostPaint();
//STRIP001
//STRIP001     ((SwRootFrm*)this)->SetCallbackActionEnabled( bOldAction );
//STRIP001 }

/*************************************************************************
|*
|*  SwRootFrm::HackPrepareLongTblPaint()
|*
|*  Ersterstellung      MA 27. Sep. 96
|*  Letzte Aenderung    MA 18. Nov. 97
|*
|*************************************************************************/

//STRIP001 void SwRootFrm::HackPrepareLongTblPaint( int nMode )
//STRIP001 {
//STRIP001  switch ( nMode )
//STRIP001  {
//STRIP001      case HACK_TABLEMODE_INIT       : ASSERT( !pLines, "HackPrepare: already prepared" );
//STRIP001                                       pLines = new SwLineRects;
//STRIP001                                       ASSERT( !pGlobalShell, "old GlobalShell lost" );
//STRIP001                                       pGlobalShell = GetShell();
//STRIP001                                       bTableHack = TRUE;
//STRIP001                                       break;
//STRIP001      case HACK_TABLEMODE_LOCKLINES  : pLines->LockLines( TRUE ); break;
//STRIP001      case HACK_TABLEMODE_PAINTLINES : pLines->PaintLines( GetShell()->GetOut() );
//STRIP001                                       break;
//STRIP001      case HACK_TABLEMODE_UNLOCKLINES: pLines->LockLines( FALSE ); break;
//STRIP001      case HACK_TABLEMODE_EXIT       : pLines->PaintLines( GetShell()->GetOut() );
//STRIP001                                       DELETEZ( pLines );
//STRIP001                                       pGlobalShell = 0;
//STRIP001                                       bTableHack = FALSE;
//STRIP001                                       break;
//STRIP001  }
//STRIP001 }


/*************************************************************************
|*
|*  SwLayoutFrm::Paint()
|*
|*  Ersterstellung      MA 19. May. 92
|*  Letzte Aenderung    MA 19. Apr. 95
|*
|*************************************************************************/

//STRIP001 void MA_FASTCALL lcl_EmergencyFormatFtnCont( SwFtnContFrm *pCont )
//STRIP001 {
//STRIP001  //Es kann sein, dass der Cont vernichtet wird.
//STRIP001  SwCntntFrm *pCnt = pCont->ContainsCntnt();
//STRIP001  while ( pCnt && pCnt->IsInFtn() )
//STRIP001  {
//STRIP001      pCnt->Calc();
//STRIP001      pCnt = pCnt->GetNextCntntFrm();
//STRIP001  }
//STRIP001 }

//STRIP001 class SwShortCut
//STRIP001 {
//STRIP001     SwRectDist fnCheck;
//STRIP001     long nLimit;
//STRIP001 public:
//STRIP001     SwShortCut( const SwFrm& rFrm, const SwRect& rRect );
//STRIP001     BOOL Stop( const SwRect& rRect ) const
//STRIP001         { return (rRect.*fnCheck)( nLimit ) > 0; }
//STRIP001 };

//STRIP001 SwShortCut::SwShortCut( const SwFrm& rFrm, const SwRect& rRect )
//STRIP001 {
//STRIP001     BOOL bVert = rFrm.IsVertical();
//STRIP001     BOOL bR2L = rFrm.IsRightToLeft();
//STRIP001     if( rFrm.IsNeighbourFrm() && bVert == bR2L )
//STRIP001     {
//STRIP001         if( bVert )
//STRIP001         {
//STRIP001             fnCheck = &SwRect::GetBottomDistance;
//STRIP001             nLimit = rRect.Top();
//STRIP001         }
//STRIP001         else
//STRIP001         {
//STRIP001             fnCheck = &SwRect::GetLeftDistance;
//STRIP001             nLimit = rRect.Left() + rRect.Width();
//STRIP001         }
//STRIP001     }
//STRIP001     else if( bVert == rFrm.IsNeighbourFrm() )
//STRIP001     {
//STRIP001         fnCheck = &SwRect::GetTopDistance;
//STRIP001         nLimit = rRect.Top() + rRect.Height();
//STRIP001     }
//STRIP001     else
//STRIP001     {
//STRIP001         fnCheck = &SwRect::GetRightDistance;
//STRIP001         nLimit = rRect.Left();
//STRIP001     }
//STRIP001 }

//STRIP001 void SwLayoutFrm::Paint( const SwRect& rRect ) const
//STRIP001 {
//STRIP001  const SwFrm *pFrm = Lower();
//STRIP001  if ( !pFrm )
//STRIP001      return;
//STRIP001
//STRIP001     SwShortCut aShortCut( *pFrm, rRect );
//STRIP001  BOOL bCnt;
//STRIP001  if ( TRUE == (bCnt = pFrm->IsCntntFrm()) )
//STRIP001      pFrm->Calc();
//STRIP001
//STRIP001  if ( pFrm->IsFtnContFrm() )
//STRIP001     {
//STRIP001         ::lcl_EmergencyFormatFtnCont( (SwFtnContFrm*)pFrm );
//STRIP001      pFrm = Lower();
//STRIP001  }
//STRIP001
//STRIP001  const SwPageFrm *pPage = 0;
//STRIP001  const FASTBOOL bWin   = pGlobalShell->GetWin() ? TRUE : FALSE;
//STRIP001
//STRIP001  while ( IsAnLower( pFrm ) )
//STRIP001  {
//STRIP001      SwRect aPaintRect( pFrm->PaintArea() );
//STRIP001         if( aShortCut.Stop( aPaintRect ) )
//STRIP001          break;
//STRIP001      if ( bCnt && pProgress )
//STRIP001          pProgress->Reschedule();
//STRIP001
//STRIP001      //Wenn ein Frm es explizit will muss retouchiert werden.
//STRIP001      //Erst die Retouche, denn selbige koennte die aligned'en Raender
//STRIP001      //plaetten.
//STRIP001      if ( pFrm->IsRetouche() )
//STRIP001      {
//STRIP001          if ( pFrm->IsRetoucheFrm() && bWin && !pFrm->GetNext() )
//STRIP001          {   if ( !pPage )
//STRIP001                  pPage = FindPageFrm();
//STRIP001                pFrm->Retouche( pPage, rRect );
//STRIP001          }
//STRIP001          pFrm->ResetRetouche();
//STRIP001      }
//STRIP001      if ( rRect.IsOver( aPaintRect ) )
//STRIP001      {
//STRIP001          if ( bCnt && pFrm->IsCompletePaint() &&
//STRIP001               !rRect.IsInside( aPaintRect ) && GetpApp()->AnyInput( INPUT_KEYBOARD ) )
//STRIP001          {
//STRIP001              //fix(8104): Es kann vorkommen, dass die Verarbeitung nicht
//STRIP001              //vollstaendig war, aber trotzdem Teile des Absatzes gepaintet
//STRIP001              //werden. In der Folge werden dann evtl. wiederum andere Teile
//STRIP001              //des Absatzes garnicht mehr gepaintet. Einziger Ausweg scheint
//STRIP001              //hier ein Invalidieren der Windows zu sein.
//STRIP001              //Um es nicht alzu Heftig werden zu lassen versuche ich hier
//STRIP001              //das Rechteck zu begrenzen indem der gewuenschte Teil gepaintet
//STRIP001              //und nur die uebrigen Absatzanteile invalidiert werden.
//STRIP001              if ( aPaintRect.Left()  == rRect.Left() &&
//STRIP001                   aPaintRect.Right() == rRect.Right() )
//STRIP001              {
//STRIP001                  aPaintRect.Bottom( rRect.Top() - 1 );
//STRIP001                  if ( aPaintRect.Height() > 0 )
//STRIP001                      pGlobalShell->InvalidateWindows(aPaintRect);
//STRIP001                  aPaintRect.Top( rRect.Bottom() + 1 );
//STRIP001                  aPaintRect.Bottom( pFrm->Frm().Bottom() );
//STRIP001                  if ( aPaintRect.Height() > 0 )
//STRIP001                      pGlobalShell->InvalidateWindows(aPaintRect);
//STRIP001                  aPaintRect.Top( pFrm->Frm().Top() );
//STRIP001                  aPaintRect.Bottom( pFrm->Frm().Bottom() );
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  pGlobalShell->InvalidateWindows( aPaintRect );
//STRIP001                  pFrm = pFrm->GetNext();
//STRIP001                  if ( pFrm && (TRUE == (bCnt = pFrm->IsCntntFrm())) )
//STRIP001                      pFrm->Calc();
//STRIP001                  continue;
//STRIP001              }
//STRIP001          }
//STRIP001          pFrm->ResetCompletePaint();
//STRIP001          aPaintRect._Intersection( rRect );
//STRIP001          pFrm->Paint( aPaintRect );
//STRIP001
//STRIP001          if ( Lower() && Lower()->IsColumnFrm() )
//STRIP001          {
//STRIP001              //Ggf. die Spaltentrennlinien malen. Fuer den Seitenbody ist
//STRIP001              //nicht der Upper sondern die Seite Zustaendig.
//STRIP001              const SwFrmFmt *pFmt = GetUpper() && GetUpper()->IsPageFrm()
//STRIP001                                          ? GetUpper()->GetFmt()
//STRIP001                                          : GetFmt();
//STRIP001              const SwFmtCol &rCol = pFmt->GetCol();
//STRIP001              if ( rCol.GetLineAdj() != COLADJ_NONE )
//STRIP001              {
//STRIP001                  if ( !pPage )
//STRIP001                      pPage = pFrm->FindPageFrm();
//STRIP001                  PaintColLines( aPaintRect, rCol, pPage );
//STRIP001              }
//STRIP001          }
//STRIP001
//STRIP001          //Nur: Body, Column, Tab, Header, Footer, FtnCont, Ftn
//STRIP001          if ( bOneBeepOnly && (pFrm->GetType() & 0x08FC))
//STRIP001          {
//STRIP001              //Wenn der Frm ueber seinen Upper hinausragt gibts die gelbe Karte.
//STRIP001              const long nDeadline = Frm().Top() + Prt().Top() +
//STRIP001                                     Prt().Height() - 1;
//STRIP001              if ( pFrm->Frm().Bottom() > nDeadline )
//STRIP001              {
//STRIP001                  if ( pGlobalShell->VisArea().Bottom() > nDeadline &&
//STRIP001                       pGlobalShell->VisArea().Top() < nDeadline )
//STRIP001                  {
//STRIP001                      bOneBeepOnly = FALSE;
//STRIP001                      Sound::Beep();
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001      if ( !bCnt && pFrm->GetNext() && pFrm->GetNext()->IsFtnContFrm() )
//STRIP001          ::lcl_EmergencyFormatFtnCont( (SwFtnContFrm*)pFrm->GetNext() );
//STRIP001
//STRIP001      pFrm = pFrm->GetNext();
//STRIP001      if ( pFrm && (TRUE == (bCnt = pFrm->IsCntntFrm())) )
//STRIP001          pFrm->Calc();
//STRIP001  }
//STRIP001 }


/** FlyFrm::IsBackgroundTransparent - for feature #99657#

    OD 12.08.2002
    determines, if background of fly frame has to be drawn transparent
    declaration found in /core/inc/flyfrm.cxx
    OD 08.10.2002 #103898# - If the background of the fly frame itself is not
    transparent and the background is inherited from its parent/grandparent,
    the background brush, used for drawing, has to be investigated for transparency.

    @author OD

    @return true, if background is transparent drawn.
*/
//STRIP001 const sal_Bool SwFlyFrm::IsBackgroundTransparent() const
//STRIP001 {
//STRIP001     sal_Bool bBackgroundTransparent = GetFmt()->IsBackgroundTransparent();
//STRIP001     if ( !bBackgroundTransparent &&
//STRIP001          static_cast<const SwFlyFrmFmt*>(GetFmt())->IsBackgroundBrushInherited() )
//STRIP001     {
//STRIP001         const SvxBrushItem* pBackgrdBrush = 0;
//STRIP001         const Color* pSectionTOXColor = 0;
//STRIP001         SwRect aDummyRect;
//STRIP001         if ( GetBackgroundBrush( pBackgrdBrush, pSectionTOXColor, aDummyRect, false) )
//STRIP001         {
//STRIP001             if ( pSectionTOXColor &&
//STRIP001                  (pSectionTOXColor->GetTransparency() != 0) &&
//STRIP001                  (pSectionTOXColor->GetColor() != COL_TRANSPARENT) )
//STRIP001             {
//STRIP001                 bBackgroundTransparent = sal_True;
//STRIP001             }
//STRIP001             else if ( pBackgrdBrush )
//STRIP001             {
//STRIP001                 if ( (pBackgrdBrush->GetColor().GetTransparency() != 0) &&
//STRIP001                      (pBackgrdBrush->GetColor() != COL_TRANSPARENT) )
//STRIP001                 {
//STRIP001                     bBackgroundTransparent = sal_True;
//STRIP001                 }
//STRIP001                 else
//STRIP001                 {
//STRIP001                     const GraphicObject *pTmpGrf =
//STRIP001                             static_cast<const GraphicObject*>(pBackgrdBrush->GetGraphicObject());
//STRIP001                     if ( (pTmpGrf) &&
//STRIP001                          (pTmpGrf->GetAttr().GetTransparency() != 0)
//STRIP001                        )
//STRIP001                     {
//STRIP001                         bBackgroundTransparent = sal_True;
//STRIP001                     }
//STRIP001                 }
//STRIP001             }
//STRIP001         }
//STRIP001     }
//STRIP001
//STRIP001     return bBackgroundTransparent;
//STRIP001 };

/** FlyFrm::IsShadowTransparent - for feature #99657#

    OD 13.08.2002
    determine, if shadow color of fly frame has to be drawn transparent
    declaration found in /core/inc/flyfrm.cxx

    @author OD

    @return true, if shadow color is transparent.
*/
//STRIP001 const sal_Bool SwFlyFrm::IsShadowTransparent() const
//STRIP001 {
//STRIP001     return GetFmt()->IsShadowTransparent();
//STRIP001 };

/*************************************************************************
|*
|*  SwFlyFrm::IsPaint()
|*
|*  Ersterstellung      MA 16. Jan. 97
|*  Letzte Aenderung    MA 16. Jan. 97
|*
|*************************************************************************/

//STRIP001 BOOL SwFlyFrm::IsPaint( SdrObject *pObj, const ViewShell *pSh )
//STRIP001 {
//STRIP001  SdrObjUserCall *pUserCall;
//STRIP001
//STRIP001  if ( 0 == ( pUserCall = GetUserCall(pObj) ) )
//STRIP001      return TRUE;
//STRIP001
//STRIP001  //Attributabhaengig nicht fuer Drucker oder PreView painten
//STRIP001  FASTBOOL bPaint =  pFlyOnlyDraw ||
//STRIP001                     ((SwContact*)pUserCall)->GetFmt()->GetPrint().GetValue();
//STRIP001  if ( !bPaint )
//STRIP001      bPaint = pSh->GetWin() && !pSh->IsPreView();
//STRIP001
//STRIP001  if ( bPaint )
//STRIP001  {
//STRIP001      //Das Paint kann evtl. von von uebergeordneten Flys verhindert werden.
//STRIP001      SwFrm *pAnch = 0;
//STRIP001      if ( pObj->IsWriterFlyFrame() )
//STRIP001      {
//STRIP001          SwFlyFrm *pFly = ((SwVirtFlyDrawObj*)pObj)->GetFlyFrm();
//STRIP001          if ( pFlyOnlyDraw && pFlyOnlyDraw == pFly )
//STRIP001              return TRUE;
//STRIP001
//STRIP001          //Die Anzeige eines Zwischenstadiums vermeiden, Flys die nicht mit
//STRIP001          //der Seite auf der sie verankert sind ueberlappen werden auch
//STRIP001          //nicht gepaintet.
//STRIP001          //HACK: Ausnahme: Drucken von Rahmen in Tabellen, diese koennen
//STRIP001          //bei uebergrossen Tabellen (HTML) schon mal auserhalb der Seite
//STRIP001          //stehen.
//STRIP001          SwPageFrm *pPage = pFly->FindPageFrm();
//STRIP001          if ( pPage )
//STRIP001          {
//STRIP001              if ( pPage->Frm().IsOver( pFly->Frm() ) )
//STRIP001                  pAnch = pFly->GetAnchor();
//STRIP001              else if ( bTableHack &&
//STRIP001                        pFly->Frm().Top() >= pFly->GetAnchor()->Frm().Top() &&
//STRIP001                        pFly->Frm().Top() < pFly->GetAnchor()->Frm().Bottom() &&
//STRIP001                        long(pSh->GetOut()) == long(pSh->GetPrt()) )
//STRIP001              {
//STRIP001                  pAnch = pFly->GetAnchor();
//STRIP001              }
//STRIP001          }
//STRIP001
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          pAnch = ((SwDrawContact*)pUserCall)->GetAnchor();
//STRIP001          if ( pAnch )
//STRIP001          {
//STRIP001              if ( !pAnch->GetValidPosFlag() )
//STRIP001                  pAnch = 0;
//STRIP001              else if ( long(pSh->GetOut()) == long(pSh->GetPrt()) )
//STRIP001              {
//STRIP001                  //HACK: fuer das Drucken muessen wir ein paar Objekte
//STRIP001                  //weglassen, da diese sonst doppelt gedruckt werden.
//STRIP001                  //Die Objekte sollen gedruckt werden, wenn der TableHack
//STRIP001                  //gerade greift. In der Folge duerfen sie nicht gedruckt werden
//STRIP001                  //wenn sie mit der Seite dran sind, ueber der sie von der
//STRIP001                  //Position her gerade schweben.
//STRIP001                  SwPageFrm *pPage = pAnch->FindPageFrm();
//STRIP001                  if ( !bTableHack &&
//STRIP001                       !pPage->Frm().IsOver( pObj->GetBoundRect() ) )
//STRIP001                      pAnch = 0;
//STRIP001              }
//STRIP001          }
//STRIP001             else
//STRIP001             {
//STRIP001                 // OD 02.07.2003 #108784# - debug assert
//STRIP001                 if ( !pObj->ISA(SdrObjGroup) )
//STRIP001                 {
//STRIP001                     ASSERT( false, "<SwFlyFrm::IsPaint(..)> - paint of drawing object without anchor frame!?" );
//STRIP001                 }
//STRIP001             }
//STRIP001      }
//STRIP001      if ( pAnch )
//STRIP001      {
//STRIP001          if ( pAnch->IsInFly() )
//STRIP001              bPaint = SwFlyFrm::IsPaint( pAnch->FindFlyFrm()->GetVirtDrawObj(),
//STRIP001                                          pSh );
//STRIP001          else if ( pFlyOnlyDraw )
//STRIP001              bPaint = FALSE;
//STRIP001      }
//STRIP001      else
//STRIP001          bPaint = FALSE;
//STRIP001  }
//STRIP001  return bPaint;
//STRIP001 }

/*************************************************************************
|*
|*  SwFlyFrm::Paint()
|*
|*  Ersterstellung      MA ??
|*  Letzte Aenderung    MA 16. Jan. 97
|*
|*************************************************************************/

//Weiter unten definiert
//STRIP001 void MA_FASTCALL lcl_PaintLowerBorders( const SwLayoutFrm *pLay,
//STRIP001                             const SwRect &rRect, const SwPageFrm *pPage );

//STRIP001 void SwFlyFrm::Paint( const SwRect& rRect ) const
//STRIP001 {
//STRIP001     //wegen der Ueberlappung von Rahmen und Zeichenobjekten muessen die
//STRIP001  //Flys ihre Umrandung (und die der Innenliegenden) direkt ausgeben.
//STRIP001  //z.B. #33066#
//STRIP001  pLines->LockLines(TRUE);
//STRIP001
//STRIP001     SwRect aRect( rRect );
//STRIP001  aRect._Intersection( Frm() );
//STRIP001
//STRIP001     OutputDevice* pOut = pGlobalShell->GetOut();
//STRIP001  pOut->Push( PUSH_CLIPREGION );
//STRIP001  pOut->SetClipRegion();
//STRIP001     const SwPageFrm* pPage = FindPageFrm();
//STRIP001
//STRIP001  const SwNoTxtFrm *pNoTxt = Lower() && Lower()->IsNoTxtFrm()
//STRIP001                                              ? (SwNoTxtFrm*)Lower() : 0;
//STRIP001     /// OD 19.08.2002 #99657# - rename local variable
//STRIP001     ///     <bTransparent> --> <bIsGraphicTransparent>
//STRIP001     FASTBOOL bIsGraphicTransparent = pNoTxt ? pNoTxt->IsTransparent() : FALSE,
//STRIP001           bContour     = GetFmt()->GetSurround().IsContour(),
//STRIP001           bHell, bPaintBack;
//STRIP001
//STRIP001     if ( bIsGraphicTransparent &&
//STRIP001       GetVirtDrawObj()->GetLayer() == GetFmt()->GetDoc()->GetHellId() &&
//STRIP001       GetAnchor()->FindFlyFrm() )
//STRIP001  {
//STRIP001      SwFlyFrm *pOldRet = pRetoucheFly2; pRetoucheFly2 = (SwFlyFrm*)this;
//STRIP001      const SwFrm *pFrm = GetAnchor()->FindFlyFrm();
//STRIP001      SwBorderAttrAccess aAccess( SwFrm::GetCache(), pFrm );
//STRIP001      const SwBorderAttrs &rAttrs = *aAccess.Get();
//STRIP001      pFrm->PaintBackground( aRect, pPage, rAttrs, FALSE, FALSE );
//STRIP001      pRetoucheFly2 = pOldRet;
//STRIP001     }
//STRIP001 //#33429#            else
//STRIP001  {
//STRIP001      PolyPolygon aPoly;
//STRIP001      if ( bContour )
//STRIP001         {
//STRIP001             // OD 16.04.2003 #i13147# - add 2nd parameter with value <sal_True>
//STRIP001             // to indicate that method is called for paint in order to avoid
//STRIP001             // load of the intrinsic graphic.
//STRIP001             bContour = GetContour( aPoly, sal_True );
//STRIP001         }
//STRIP001
//STRIP001      //Hintergrund painten fuer:
//STRIP001      bPaintBack = !pNoTxt || Prt().SSize() != Frm().SSize();
//STRIP001      //sowie fuer Transparente und Contour in der Hoelle
//STRIP001      bPaintBack = bPaintBack ||
//STRIP001                 ((bIsGraphicTransparent || bContour ) &&
//STRIP001              TRUE == (bHell = GetVirtDrawObj()->GetLayer() == GetFmt()->GetDoc()->GetHellId()));
//STRIP001      //sowie fuer Transparente und Contour mit eigener Brush
//STRIP001         if ( !bPaintBack && (bIsGraphicTransparent||bContour) )
//STRIP001      {
//STRIP001          const SvxBrushItem &rBack = GetFmt()->GetBackground();
//STRIP001             /// OD 07.08.2002 #99657# #GetTransChg#
//STRIP001             ///     to determine, if background has to be painted, by checking, if
//STRIP001             ///     background color is not COL_TRANSPARENT ("no fill"/"auto fill")
//STRIP001             ///     or a background graphic exists.
//STRIP001             bPaintBack = !(rBack.GetColor() == COL_TRANSPARENT) ||
//STRIP001             ///bPaintBack = !rBack.GetColor().GetTransparency() ||
//STRIP001                          rBack.GetGraphicPos() != GPOS_NONE;
//STRIP001      }
//STRIP001
//STRIP001      if ( bPaintBack )
//STRIP001      {
//STRIP001          //#24926# JP 01.02.96, PaintBaBo in teilen hier, damit PaintBorder
//STRIP001          //das orig. Rect bekommt, aber PaintBackground das begrenzte.
//STRIP001
//STRIP001          pOut->Push( PUSH_FILLCOLOR );
//STRIP001
//STRIP001          pPage = FindPageFrm();
//STRIP001
//STRIP001          SwBorderAttrAccess aAccess( SwFrm::GetCache(), (SwFrm*)this );
//STRIP001          const SwBorderAttrs &rAttrs = *aAccess.Get();
//STRIP001
//STRIP001             // OD 06.08.2002 #99657# - paint border before painting background
//STRIP001             // paint border
//STRIP001             {
//STRIP001                 SwRect aTmp( rRect );
//STRIP001                 PaintBorder( aTmp, pPage, rAttrs );
//STRIP001             }
//STRIP001
//STRIP001             // paint background
//STRIP001             {
//STRIP001                 SwRegionRects aRegion( aRect );
//STRIP001                 if ( pNoTxt && !bIsGraphicTransparent )
//STRIP001                 {
//STRIP001                     //Was wir eigentlich Painten wollen ist der schmale Streifen
//STRIP001                     //zwischen PrtArea und aeusserer Umrandung.
//STRIP001                     SwRect aTmp( Prt() ); aTmp += Frm().Pos();
//STRIP001                     aRegion -= aTmp;
//STRIP001                 }
//STRIP001                 if ( bContour )
//STRIP001                 {
//STRIP001                     pOut->Push();
//STRIP001                     if ( !pOut->GetConnectMetaFile() || pOut->GetOutDevType() == OUTDEV_PRINTER )
//STRIP001                     {
//STRIP001                         pOut->SetClipRegion( aPoly );
//STRIP001                     }
//STRIP001                     for ( USHORT i = 0; i < aRegion.Count(); ++i )
//STRIP001                         PaintBackground( aRegion[i], pPage, rAttrs, FALSE, TRUE );
//STRIP001                     pOut->Pop();
//STRIP001                 }
//STRIP001                 else
//STRIP001                     for ( USHORT i = 0; i < aRegion.Count(); ++i )
//STRIP001                         PaintBackground( aRegion[i], pPage, rAttrs, FALSE, TRUE );
//STRIP001             }
//STRIP001
//STRIP001          pOut->Pop();
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001     // OD 19.12.2002 #106318# - fly frame will paint it's subsidiary lines and
//STRIP001     // the subsidiary lines of its lowers on its own, due to overlapping with
//STRIP001     // other fly frames or other objects.
//STRIP001     if( pGlobalShell->GetWin() )
//STRIP001     {
//STRIP001         bool bSubsLineRectsCreated;
//STRIP001         if ( pSubsLines )
//STRIP001         {
//STRIP001             // Lock already existing subsidiary lines
//STRIP001             pSubsLines->LockLines( TRUE );
//STRIP001             bSubsLineRectsCreated = false;
//STRIP001         }
//STRIP001         else
//STRIP001         {
//STRIP001             // create new subsidiardy lines
//STRIP001             pSubsLines = new SwSubsRects;
//STRIP001             bSubsLineRectsCreated = true;
//STRIP001         }
//STRIP001
//STRIP001         bool bSpecSubsLineRectsCreated;
//STRIP001         if ( pSpecSubsLines )
//STRIP001         {
//STRIP001             // Lock already existing special subsidiary lines
//STRIP001             pSpecSubsLines->LockLines( TRUE );
//STRIP001             bSpecSubsLineRectsCreated = false;
//STRIP001         }
//STRIP001         else
//STRIP001         {
//STRIP001             // create new special subsidiardy lines
//STRIP001             pSpecSubsLines = new SwSubsRects;
//STRIP001             bSpecSubsLineRectsCreated = true;
//STRIP001         }
//STRIP001         // Add subsidiary lines of fly frame and its lowers
//STRIP001         RefreshLaySubsidiary( pPage, aRect );
//STRIP001         // paint subsidiary lines of fly frame and its lowers
//STRIP001         pSpecSubsLines->PaintSubsidiary( pOut, NULL );
//STRIP001         pSubsLines->PaintSubsidiary( pOut, pLines );
//STRIP001         if ( !bSubsLineRectsCreated )
//STRIP001             // unlock subsidiary lines
//STRIP001             pSubsLines->LockLines( FALSE );
//STRIP001         else
//STRIP001             // delete created subsidiary lines container
//STRIP001             DELETEZ( pSubsLines );
//STRIP001
//STRIP001         if ( !bSpecSubsLineRectsCreated )
//STRIP001             // unlock special subsidiary lines
//STRIP001             pSpecSubsLines->LockLines( FALSE );
//STRIP001         else
//STRIP001             // delete created special subsidiary lines container
//STRIP001             DELETEZ( pSpecSubsLines );
//STRIP001     }
//STRIP001
//STRIP001     SwLayoutFrm::Paint( aRect );
//STRIP001  Validate();
//STRIP001
//STRIP001     // OD 19.12.2002 #106318# - first paint lines added by fly frame paint
//STRIP001     // and then unlock other lines.
//STRIP001     pLines->PaintLines( pOut );
//STRIP001     pLines->LockLines( FALSE );
//STRIP001
//STRIP001  pOut->Pop();
//STRIP001
//STRIP001  if ( pProgress && pNoTxt )
//STRIP001      pProgress->Reschedule();
//STRIP001 }
/*************************************************************************
|*
|*    SwTabFrm::Paint()
|*
|*    Ersterstellung    MA 11. May. 93
|*    Letzte Aenderung  MA 23. Mar. 95
|*
|*************************************************************************/

//STRIP001 void SwTabFrm::Paint( const SwRect& rRect ) const
//STRIP001 {
//STRIP001     if ( pGlobalShell->GetViewOptions()->IsTable() )
//STRIP001     {
//STRIP001      SwLayoutFrm::Paint( rRect );
//STRIP001     }
//STRIP001     // OD 10.01.2003 #i6467# - no light grey rectangle for page preview
//STRIP001     else if ( pGlobalShell->GetWin() && !pGlobalShell->IsPreView() )
//STRIP001  {
//STRIP001         // OD 10.01.2003 #i6467# - intersect output rectangle with table frame
//STRIP001         SwRect aTabRect( Prt() );
//STRIP001         aTabRect.Pos() += Frm().Pos();
//STRIP001         SwRect aTabOutRect( rRect );
//STRIP001         aTabOutRect.Intersection( aTabRect );
//STRIP001         pGlobalShell->GetViewOptions()->
//STRIP001                 DrawRect( pGlobalShell->GetOut(), aTabOutRect, COL_LIGHTGRAY );
//STRIP001  }
//STRIP001  ((SwTabFrm*)this)->ResetComplete();
//STRIP001 }

/*************************************************************************
|*
|*  SwFrm::PaintShadow()
|*
|*  Beschreibung        Malt einen Shatten wenns das FrmFormat fordert.
|*      Der Schatten wird immer an den auesseren Rand des OutRect gemalt.
|*      Das OutRect wird ggf. so verkleinert, dass auf diesem das
|*      malen der Umrandung stattfinden kann.
|*  Ersterstellung      MA 21. Dec. 92
|*  Letzte Aenderung    MA 29. May. 97
|*
|*************************************************************************/
/// OD 23.08.2002 #99657#
///     draw full shadow rectangle for frames with transparent drawn backgrounds.
//STRIP001 void SwFrm::PaintShadow( const SwRect& rRect, SwRect& rOutRect,
//STRIP001                       const SwPageFrm *pPage,
//STRIP001                       const SwBorderAttrs &rAttrs ) const
//STRIP001 {
//STRIP001  const SvxShadowItem &rShadow = rAttrs.GetShadow();
//STRIP001  const long nWidth  = ::lcl_AlignWidth ( rShadow.GetWidth() );
//STRIP001  const long nHeight = ::lcl_AlignHeight( rShadow.GetWidth() );
//STRIP001
//STRIP001  SwRects aRegion( 2, 2 );
//STRIP001  SwRect aOut( rOutRect );
//STRIP001
//STRIP001  const FASTBOOL bCnt    = IsCntntFrm();
//STRIP001  const FASTBOOL bTop    = !bCnt || rAttrs.GetTopLine  ( this ) ? TRUE : FALSE;
//STRIP001  const FASTBOOL bBottom = !bCnt || rAttrs.GetBottomLine( this ) ? TRUE : FALSE;
//STRIP001
//STRIP001     SvxShadowLocation eLoc = rShadow.GetLocation();
//STRIP001
//STRIP001     SWRECTFN( this )
//STRIP001     if( IsVertical() )
//STRIP001     {
//STRIP001         switch( eLoc )
//STRIP001         {
//STRIP001             case SVX_SHADOW_BOTTOMRIGHT: eLoc = SVX_SHADOW_BOTTOMLEFT;  break;
//STRIP001             case SVX_SHADOW_TOPLEFT:     eLoc = SVX_SHADOW_TOPRIGHT;    break;
//STRIP001             case SVX_SHADOW_TOPRIGHT:    eLoc = SVX_SHADOW_BOTTOMRIGHT; break;
//STRIP001             case SVX_SHADOW_BOTTOMLEFT:  eLoc = SVX_SHADOW_TOPLEFT;     break;
//STRIP001         }
//STRIP001     }
//STRIP001
//STRIP001     /// OD 23.08.2002 #99657# - determine, if full shadow rectangle have to
//STRIP001     ///     be drawn or only two shadow rectangles beside the frame.
//STRIP001     ///     draw full shadow rectangle, if frame background is drawn transparent.
//STRIP001     ///     Status Quo:
//STRIP001     ///         SwLayoutFrm can have transparent drawn backgrounds. Thus,
//STRIP001     ///         "asked" their frame format.
//STRIP001     sal_Bool bDrawFullShadowRectangle =
//STRIP001             ( IsLayoutFrm() &&
//STRIP001               (static_cast<const SwLayoutFrm*>(this))->GetFmt()->IsBackgroundTransparent()
//STRIP001             );
//STRIP001     switch ( eLoc )
//STRIP001  {
//STRIP001      case SVX_SHADOW_BOTTOMRIGHT:
//STRIP001          {
//STRIP001                 if ( bDrawFullShadowRectangle )
//STRIP001                 {
//STRIP001                     /// OD 06.08.2002 #99657# - draw full shadow rectangle
//STRIP001                     aOut.Top( aOut.Top() + nHeight );
//STRIP001                     aOut.Left( aOut.Left() + nWidth );
//STRIP001                     aRegion.Insert( aOut, aRegion.Count() );
//STRIP001                 }
//STRIP001                 else
//STRIP001                 {
//STRIP001                     aOut.Top ( aOut.Bottom() - nHeight );
//STRIP001                     aOut.Left( aOut.Left()   + nWidth );
//STRIP001                     if ( bBottom )
//STRIP001                         aRegion.Insert( aOut, aRegion.Count() );
//STRIP001                     aOut.Left( aOut.Right()   - nWidth );
//STRIP001                     aOut.Top ( rOutRect.Top() + nHeight );
//STRIP001                     if ( bBottom )
//STRIP001                         aOut.Bottom( aOut.Bottom() - nHeight );
//STRIP001                     if ( bCnt && (!bTop || !bBottom) )
//STRIP001                         ::lcl_ExtendLeftAndRight( aOut, *(this), rAttrs, fnRect );
//STRIP001                     aRegion.Insert( aOut, aRegion.Count() );
//STRIP001                 }
//STRIP001
//STRIP001              rOutRect.Right ( rOutRect.Right() - nWidth );
//STRIP001              rOutRect.Bottom( rOutRect.Bottom()- nHeight );
//STRIP001          }
//STRIP001          break;
//STRIP001      case SVX_SHADOW_TOPLEFT:
//STRIP001          {
//STRIP001                 if ( bDrawFullShadowRectangle )
//STRIP001                 {
//STRIP001                     /// OD 06.08.2002 #99657# - draw full shadow rectangle
//STRIP001                     aOut.Bottom( aOut.Bottom() - nHeight );
//STRIP001                     aOut.Right( aOut.Right() - nWidth );
//STRIP001                     aRegion.Insert( aOut, aRegion.Count() );
//STRIP001                 }
//STRIP001                 else
//STRIP001                 {
//STRIP001                     aOut.Bottom( aOut.Top()   + nHeight );
//STRIP001                     aOut.Right ( aOut.Right() - nWidth );
//STRIP001                     if ( bTop )
//STRIP001                         aRegion.Insert( aOut, aRegion.Count() );
//STRIP001                     aOut.Right ( aOut.Left() + nWidth );
//STRIP001                     aOut.Bottom( rOutRect.Bottom() - nHeight );
//STRIP001                     if ( bTop )
//STRIP001                         aOut.Top( aOut.Top() + nHeight );
//STRIP001                     if ( bCnt && (!bBottom || !bTop) )
//STRIP001                         ::lcl_ExtendLeftAndRight( aOut, *(this), rAttrs, fnRect );
//STRIP001                     aRegion.Insert( aOut, aRegion.Count() );
//STRIP001                 }
//STRIP001
//STRIP001              rOutRect.Left( rOutRect.Left() + nWidth );
//STRIP001              rOutRect.Top(  rOutRect.Top() + nHeight );
//STRIP001          }
//STRIP001          break;
//STRIP001      case SVX_SHADOW_TOPRIGHT:
//STRIP001          {
//STRIP001                 if ( bDrawFullShadowRectangle )
//STRIP001                 {
//STRIP001                     /// OD 06.08.2002 #99657# - draw full shadow rectangle
//STRIP001                     aOut.Bottom( aOut.Bottom() - nHeight);
//STRIP001                     aOut.Left( aOut.Left() + nWidth );
//STRIP001                     aRegion.Insert( aOut, aRegion.Count() );
//STRIP001                 }
//STRIP001                 else
//STRIP001                 {
//STRIP001                     aOut.Bottom( aOut.Top() + nHeight );
//STRIP001                     aOut.Left (  aOut.Left()+ nWidth );
//STRIP001                     if ( bTop )
//STRIP001                         aRegion.Insert( aOut, aRegion.Count() );
//STRIP001                     aOut.Left  ( aOut.Right() - nWidth );
//STRIP001                     aOut.Bottom( rOutRect.Bottom() - nHeight );
//STRIP001                     if ( bTop )
//STRIP001                         aOut.Top( aOut.Top() + nHeight );
//STRIP001                     if ( bCnt && (!bBottom || bTop) )
//STRIP001                         ::lcl_ExtendLeftAndRight( aOut, *(this), rAttrs, fnRect );
//STRIP001                     aRegion.Insert( aOut, aRegion.Count() );
//STRIP001                 }
//STRIP001
//STRIP001                 rOutRect.Right( rOutRect.Right() - nWidth );
//STRIP001              rOutRect.Top( rOutRect.Top() + nHeight );
//STRIP001          }
//STRIP001          break;
//STRIP001      case SVX_SHADOW_BOTTOMLEFT:
//STRIP001          {
//STRIP001                 if ( bDrawFullShadowRectangle )
//STRIP001                 {
//STRIP001                     /// OD 06.08.2002 #99657# - draw full shadow rectangle
//STRIP001                     aOut.Top( aOut.Top() + nHeight );
//STRIP001                     aOut.Right( aOut.Right() - nWidth );
//STRIP001                     aRegion.Insert( aOut, aRegion.Count() );
//STRIP001                 }
//STRIP001                 else
//STRIP001                 {
//STRIP001                     aOut.Top  ( aOut.Bottom()- nHeight );
//STRIP001                     aOut.Right( aOut.Right() - nWidth );
//STRIP001                     if ( bBottom )
//STRIP001                         aRegion.Insert( aOut, aRegion.Count() );
//STRIP001                     aOut.Right( aOut.Left() + nWidth );
//STRIP001                     aOut.Top( rOutRect.Top() + nHeight );
//STRIP001                     if ( bBottom )
//STRIP001                         aOut.Bottom( aOut.Bottom() - nHeight );
//STRIP001                     if ( bCnt && (!bTop || !bBottom) )
//STRIP001                         ::lcl_ExtendLeftAndRight( aOut, *(this), rAttrs, fnRect );
//STRIP001                     aRegion.Insert( aOut, aRegion.Count() );
//STRIP001                 }
//STRIP001
//STRIP001              rOutRect.Left( rOutRect.Left() + nWidth );
//STRIP001              rOutRect.Bottom( rOutRect.Bottom() - nHeight );
//STRIP001          }
//STRIP001          break;
//STRIP001 #ifndef PRODUCT
//STRIP001      default:    ASSERT( !this, "new ShadowLocation() ?" );
//STRIP001 #endif
//STRIP001  }
//STRIP001
//STRIP001  OutputDevice *pOut = pGlobalShell->GetOut();
//STRIP001
//STRIP001     ULONG nOldDrawMode = pOut->GetDrawMode();
//STRIP001     Color aShadowColor( rShadow.GetColor() );
//STRIP001     if( aRegion.Count() && pGlobalShell->GetWin() &&
//STRIP001         Application::GetSettings().GetStyleSettings().GetHighContrastMode() )
//STRIP001     {
//STRIP001         // Is heigh contrast mode, the output device has already set the
//STRIP001         // DRAWMODE_SETTINGSFILL flag. This causes the SetFillColor function
//STRIP001         // to ignore the setting of a new color. Therefore we have to reset
//STRIP001         // the drawing mode
//STRIP001         pOut->SetDrawMode( 0 );
//STRIP001         aShadowColor = SwViewOption::GetFontColor();
//STRIP001     }
//STRIP001
//STRIP001     if ( pOut->GetFillColor() != aShadowColor )
//STRIP001         pOut->SetFillColor( aShadowColor );
//STRIP001
//STRIP001     pOut->SetDrawMode( nOldDrawMode );
//STRIP001
//STRIP001  for ( USHORT i = 0; i < aRegion.Count(); ++i )
//STRIP001  {
//STRIP001      SwRect &rOut = aRegion[i];
//STRIP001      aOut = rOut;
//STRIP001         // OD 30.09.2002 #103636# - no SwAlign of shadow rectangle
//STRIP001         // no alignment necessary, because (1) <rRect> is already aligned
//STRIP001         // and because (2) paint of border and background will occur later.
//STRIP001         // Thus, (1) assures that no conflicts with neighbour object will occure
//STRIP001         // and (2) assures that border and background is not affected by the
//STRIP001         // shadow paint.
//STRIP001         /*
//STRIP001         ::SwAlignRect( aOut, pGlobalShell );
//STRIP001         */
//STRIP001      if ( rRect.IsOver( aOut ) && aOut.Height() > 0 && aOut.Width() > 0 )
//STRIP001      {
//STRIP001          aOut._Intersection( rRect );
//STRIP001          pOut->DrawRect( aOut.SVRect() );
//STRIP001      }
//STRIP001  }
//STRIP001 }

/*************************************************************************
|*
|*  SwFrm::PaintBorderLine()
|*
|*  Ersterstellung      MA 22. Dec. 92
|*  Letzte Aenderung    MA 22. Jan. 95
|*
|*************************************************************************/

//STRIP001 void SwFrm::PaintBorderLine( const SwRect& rRect,
//STRIP001                           const SwRect& rOutRect,
//STRIP001                           const SwPageFrm *pPage,
//STRIP001                           const Color *pColor ) const
//STRIP001 {
//STRIP001  if ( !rOutRect.IsOver( rRect ) )
//STRIP001      return;
//STRIP001
//STRIP001  SwRect aOut( rOutRect );
//STRIP001  aOut._Intersection( rRect );
//STRIP001
//STRIP001  const SwTabFrm *pTab = IsCellFrm() ? FindTabFrm() : 0;
//STRIP001     BYTE nSubCol = ( IsCellFrm() || IsRowFrm() ) ? SUBCOL_TAB :
//STRIP001                    ( IsInSct() ? SUBCOL_SECT :
//STRIP001                    ( IsInFly() ? SUBCOL_FLY : SUBCOL_PAGE ) );
//STRIP001     if( pColor && pGlobalShell->GetWin() &&
//STRIP001         Application::GetSettings().GetStyleSettings().GetHighContrastMode() )
//STRIP001     {
//STRIP001         pColor = &SwViewOption::GetFontColor();
//STRIP001     }
//STRIP001
//STRIP001  if ( pPage->GetSortedObjs() )
//STRIP001  {
//STRIP001      SwRegionRects aRegion( aOut, 4, 1 );
//STRIP001      ::lcl_SubtractFlys( this, pPage, aOut, aRegion );
//STRIP001      for ( USHORT i = 0; i < aRegion.Count(); ++i )
//STRIP001             pLines->AddLineRect( aRegion[i], pColor, pTab, nSubCol );
//STRIP001  }
//STRIP001  else
//STRIP001         pLines->AddLineRect( aOut, pColor, pTab, nSubCol );
//STRIP001 }

/*************************************************************************
|*
|*  SwFrm::PaintBorderLines()
|*
|*  Beschreibung        Nur alle Linien einfach oder alle Linien doppelt!!!!
|*  Ersterstellung      MA 22. Dec. 92
|*  Letzte Aenderung    MA 22. Mar. 95
|*
|*************************************************************************/

// OD 29.04.2003 #107169# - method called for left and right border rectangles.
// For a printer output device perform adjustment for non-overlapping top and
// bottom border rectangles. Thus, add parameter <_bPrtOutputDev> to indicate
// printer output device.
// NOTE: For printer output device left/right border rectangle <_iorRect>
//       has to be already non-overlapping the outer top/bottom border rectangle.
//STRIP001 void MA_FASTCALL lcl_SubTopBottom( SwRect&              _iorRect,
//STRIP001                                    const SvxBoxItem&    _rBox,
//STRIP001                                    const SwBorderAttrs& _rAttrs,
//STRIP001                                    const SwFrm*         _pFrm,
//STRIP001                                    const SwRectFn&      _rRectFn,
//STRIP001                                    const sal_Bool       _bPrtOutputDev )
//STRIP001 {
//STRIP001     const BOOL bCnt = _pFrm->IsCntntFrm();
//STRIP001     if ( _rBox.GetTop() && _rBox.GetTop()->GetInWidth() &&
//STRIP001          ( !bCnt || _rAttrs.GetTopLine( _pFrm ) )
//STRIP001        )
//STRIP001  {
//STRIP001         // substract distance between outer and inner line.
//STRIP001         SwTwips nDist = ::lcl_MinHeightDist( _rBox.GetTop()->GetDistance() );
//STRIP001         // OD 19.05.2003 #109667# - non-overlapping border rectangles:
//STRIP001         // adjust x-/y-position, if inner top line is a hair line (width = 1)
//STRIP001         sal_Bool bIsInnerTopLineHairline = sal_False;
//STRIP001         if ( !_bPrtOutputDev )
//STRIP001         {
//STRIP001             // additionally substract width of top outer line
//STRIP001             // --> left/right inner/outer line doesn't overlap top outer line.
//STRIP001             nDist += ::lcl_AlignHeight( _rBox.GetTop()->GetOutWidth() );
//STRIP001         }
//STRIP001         else
//STRIP001         {
//STRIP001             // OD 29.04.2003 #107169# - additionally substract width of top inner line
//STRIP001             // --> left/right inner/outer line doesn't overlap top inner line.
//STRIP001             nDist += ::lcl_AlignHeight( _rBox.GetTop()->GetInWidth() );
//STRIP001             bIsInnerTopLineHairline = _rBox.GetTop()->GetInWidth() == 1;
//STRIP001         }
//STRIP001         (_iorRect.*_rRectFn->fnSubTop)( -nDist );
//STRIP001         // OD 19.05.2003 #109667# - adjust calculated border top, if inner top line
//STRIP001         // is a hair line
//STRIP001         if ( bIsInnerTopLineHairline )
//STRIP001         {
//STRIP001             if ( _pFrm->IsVertical() )
//STRIP001             {
//STRIP001                 // right of border rectangle has to be checked and adjusted
//STRIP001                 Point aCompPt( _iorRect.Right(), 0 );
//STRIP001                 Point aRefPt( aCompPt.X() + 1, aCompPt.Y() );
//STRIP001                 lcl_CompPxPosAndAdjustPos( *(pGlobalShell->GetOut()),
//STRIP001                                           aRefPt, aCompPt,
//STRIP001                                           sal_True, -1 );
//STRIP001                 _iorRect.Right( aCompPt.X() );
//STRIP001             }
//STRIP001             else
//STRIP001             {
//STRIP001                 // top of border rectangle has to be checked and adjusted
//STRIP001                 Point aCompPt( 0, _iorRect.Top() );
//STRIP001                 Point aRefPt( aCompPt.X(), aCompPt.Y() - 1 );
//STRIP001                 lcl_CompPxPosAndAdjustPos( *(pGlobalShell->GetOut()),
//STRIP001                                           aRefPt, aCompPt,
//STRIP001                                           sal_False, +1 );
//STRIP001                 _iorRect.Top( aCompPt.Y() );
//STRIP001             }
//STRIP001         }
//STRIP001  }
//STRIP001
//STRIP001     if ( _rBox.GetBottom() && _rBox.GetBottom()->GetInWidth() &&
//STRIP001          ( !bCnt || _rAttrs.GetBottomLine( _pFrm ) )
//STRIP001        )
//STRIP001  {
//STRIP001         // substract distance between outer and inner line.
//STRIP001         SwTwips nDist = ::lcl_MinHeightDist( _rBox.GetBottom()->GetDistance() );
//STRIP001         // OD 19.05.2003 #109667# - non-overlapping border rectangles:
//STRIP001         // adjust x-/y-position, if inner bottom line is a hair line (width = 1)
//STRIP001         sal_Bool bIsInnerBottomLineHairline = sal_False;
//STRIP001         if ( !_bPrtOutputDev )
//STRIP001         {
//STRIP001             // additionally substract width of bottom outer line
//STRIP001             // --> left/right inner/outer line doesn't overlap bottom outer line.
//STRIP001             nDist += ::lcl_AlignHeight( _rBox.GetBottom()->GetOutWidth() );
//STRIP001         }
//STRIP001         else
//STRIP001         {
//STRIP001             // OD 29.04.2003 #107169# - additionally substract width of bottom inner line
//STRIP001             // --> left/right inner/outer line doesn't overlap bottom inner line.
//STRIP001             nDist += ::lcl_AlignHeight( _rBox.GetBottom()->GetInWidth() );
//STRIP001             bIsInnerBottomLineHairline = _rBox.GetBottom()->GetInWidth() == 1;
//STRIP001         }
//STRIP001         (_iorRect.*_rRectFn->fnAddBottom)( -nDist );
//STRIP001         // OD 19.05.2003 #109667# - adjust calculated border bottom, if inner
//STRIP001         // bottom line is a hair line.
//STRIP001         if ( bIsInnerBottomLineHairline )
//STRIP001         {
//STRIP001             if ( _pFrm->IsVertical() )
//STRIP001             {
//STRIP001                 // left of border rectangle has to be checked and adjusted
//STRIP001                 Point aCompPt( _iorRect.Left(), 0 );
//STRIP001                 Point aRefPt( aCompPt.X() - 1, aCompPt.Y() );
//STRIP001                 lcl_CompPxPosAndAdjustPos( *(pGlobalShell->GetOut()),
//STRIP001                                           aRefPt, aCompPt,
//STRIP001                                           sal_True, +1 );
//STRIP001                 _iorRect.Left( aCompPt.X() );
//STRIP001             }
//STRIP001             else
//STRIP001             {
//STRIP001                 // bottom of border rectangle has to be checked and adjusted
//STRIP001                 Point aCompPt( 0, _iorRect.Bottom() );
//STRIP001                 Point aRefPt( aCompPt.X(), aCompPt.Y() + 1 );
//STRIP001                 lcl_CompPxPosAndAdjustPos( *(pGlobalShell->GetOut()),
//STRIP001                                           aRefPt, aCompPt,
//STRIP001                                           sal_False, -1 );
//STRIP001                 _iorRect.Bottom( aCompPt.Y() );
//STRIP001             }
//STRIP001         }
//STRIP001  }
//STRIP001 }

// method called for top and bottom border rectangles.
//STRIP001 void MA_FASTCALL lcl_SubLeftRight( SwRect&           rRect,
//STRIP001                                    const SvxBoxItem& rBox,
//STRIP001                                    const SwRectFn&   rRectFn )
//STRIP001 {
//STRIP001  if ( rBox.GetLeft() && rBox.GetLeft()->GetInWidth() )
//STRIP001  {
//STRIP001         const long nDist = ::lcl_MinWidthDist( rBox.GetLeft()->GetDistance() )
//STRIP001                            + ::lcl_AlignWidth( rBox.GetLeft()->GetOutWidth() );
//STRIP001         (rRect.*rRectFn->fnSubLeft)( -nDist );
//STRIP001  }
//STRIP001
//STRIP001  if ( rBox.GetRight() && rBox.GetRight()->GetInWidth() )
//STRIP001  {
//STRIP001         const long nDist = ::lcl_MinWidthDist( rBox.GetRight()->GetDistance() )
//STRIP001                            + ::lcl_AlignWidth( rBox.GetRight()->GetOutWidth() );
//STRIP001         (rRect.*rRectFn->fnAddRight)( -nDist );
//STRIP001  }
//STRIP001 }

// OD 19.05.2003 #109667# - merge <lcl_PaintLeftLine> and <lcl_PaintRightLine>
// into new method <lcl_PaintLeftRightLine(..)>
//STRIP001 void lcl_PaintLeftRightLine( const sal_Bool         _bLeft,
//STRIP001                              const SwFrm&           _rFrm,
//STRIP001                              const SwPageFrm&       _rPage,
//STRIP001                              const SwRect&          _rOutRect,
//STRIP001                              const SwRect&          _rRect,
//STRIP001                              const SwBorderAttrs&   _rAttrs,
//STRIP001                              const SwRectFn&        _rRectFn )
//STRIP001 {
//STRIP001     const SvxBoxItem& rBox = _rAttrs.GetBox();
//STRIP001     const sal_Bool bR2L = _rFrm.IsCellFrm() && _rFrm.IsRightToLeft();
//STRIP001     const SvxBorderLine* pLeftRightBorder = 0;
//STRIP001     if ( _bLeft )
//STRIP001     {
//STRIP001         pLeftRightBorder = bR2L ? rBox.GetRight() : rBox.GetLeft();
//STRIP001     }
//STRIP001     else
//STRIP001     {
//STRIP001         pLeftRightBorder = bR2L ? rBox.GetLeft() : rBox.GetRight();
//STRIP001     }
//STRIP001     // OD 06.05.2003 #107169# - init boolean indicating printer output device.
//STRIP001     const sal_Bool bPrtOutputDev =
//STRIP001             ( OUTDEV_PRINTER == pGlobalShell->GetOut()->GetOutDevType() );
//STRIP001
//STRIP001     if ( !pLeftRightBorder )
//STRIP001     {
//STRIP001         return;
//STRIP001     }
//STRIP001
//STRIP001     SwRect aRect( _rOutRect );
//STRIP001     if ( _bLeft )
//STRIP001     {
//STRIP001         (aRect.*_rRectFn->fnAddRight)( ::lcl_AlignWidth( pLeftRightBorder->GetOutWidth() ) -
//STRIP001                                        (aRect.*_rRectFn->fnGetWidth)() );
//STRIP001     }
//STRIP001     else
//STRIP001     {
//STRIP001         (aRect.*_rRectFn->fnSubLeft)( ::lcl_AlignWidth( pLeftRightBorder->GetOutWidth() ) -
//STRIP001                                       (aRect.*_rRectFn->fnGetWidth)() );
//STRIP001     }
//STRIP001
//STRIP001     const BOOL bCnt = _rFrm.IsCntntFrm();
//STRIP001
//STRIP001     if ( bCnt )
//STRIP001     {
//STRIP001         ::lcl_ExtendLeftAndRight( aRect, _rFrm, _rAttrs, _rRectFn );
//STRIP001     }
//STRIP001
//STRIP001     // OD 06.05.2003 #107169# - adjustments for printer output device
//STRIP001     if ( bPrtOutputDev )
//STRIP001     {
//STRIP001         // substract width of outer top line.
//STRIP001         if ( rBox.GetTop() && (!bCnt || _rAttrs.GetTopLine( &_rFrm )) )
//STRIP001         {
//STRIP001             long nDist = ::lcl_AlignHeight( rBox.GetTop()->GetOutWidth() );
//STRIP001             (aRect.*_rRectFn->fnSubTop)( -nDist );
//STRIP001             // OD 19.05.2003 #109667# - If outer top line is hair line, calculated
//STRIP001             // top has to be adjusted.
//STRIP001             if ( nDist == 1 )
//STRIP001             {
//STRIP001                 if ( _rFrm.IsVertical() )
//STRIP001                 {
//STRIP001                     // right of border rectangle has to be checked and adjusted
//STRIP001                     Point aCompPt( aRect.Right(), 0 );
//STRIP001                     Point aRefPt( aCompPt.X() + 1, aCompPt.Y() );
//STRIP001                     lcl_CompPxPosAndAdjustPos( *(pGlobalShell->GetOut()),
//STRIP001                                               aRefPt, aCompPt,
//STRIP001                                               sal_True, -1 );
//STRIP001                     aRect.Right( aCompPt.X() );
//STRIP001                 }
//STRIP001                 else
//STRIP001                 {
//STRIP001                     // top of border rectangle has to be checked and adjusted
//STRIP001                     Point aCompPt( 0, aRect.Top() );
//STRIP001                     Point aRefPt( aCompPt.X(), aCompPt.Y() - 1 );
//STRIP001                     lcl_CompPxPosAndAdjustPos( *(pGlobalShell->GetOut()),
//STRIP001                                               aRefPt, aCompPt,
//STRIP001                                               sal_False, +1 );
//STRIP001                     aRect.Top( aCompPt.Y() );
//STRIP001                 }
//STRIP001             }
//STRIP001         }
//STRIP001         // substract width of outer bottom line.
//STRIP001         if ( rBox.GetBottom() && (!bCnt || _rAttrs.GetBottomLine( &_rFrm )) )
//STRIP001         {
//STRIP001             long nDist = ::lcl_AlignHeight( rBox.GetBottom()->GetOutWidth());
//STRIP001             (aRect.*_rRectFn->fnAddBottom)( -nDist );
//STRIP001             // OD 19.05.2003 #109667# - If outer bottom line is hair line, calculated
//STRIP001             // top has to be adjusted.
//STRIP001             if ( nDist == 1 )
//STRIP001             {
//STRIP001                 if ( _rFrm.IsVertical() )
//STRIP001                 {
//STRIP001                     // left of border rectangle has to be checked and adjusted
//STRIP001                     Point aCompPt( aRect.Left(), 0 );
//STRIP001                     Point aRefPt( aCompPt.X() - 1, aCompPt.Y() );
//STRIP001                     lcl_CompPxPosAndAdjustPos( *(pGlobalShell->GetOut()),
//STRIP001                                               aRefPt, aCompPt,
//STRIP001                                               sal_True, +1 );
//STRIP001                     aRect.Left( aCompPt.X() );
//STRIP001                 }
//STRIP001                 else
//STRIP001                 {
//STRIP001                     // bottom of border rectangle has to be checked and adjusted
//STRIP001                     Point aCompPt( 0, aRect.Bottom() );
//STRIP001                     Point aRefPt( aCompPt.X(), aCompPt.Y() + 1 );
//STRIP001                     lcl_CompPxPosAndAdjustPos( *(pGlobalShell->GetOut()),
//STRIP001                                               aRefPt, aCompPt,
//STRIP001                                               sal_False, -1 );
//STRIP001                     aRect.Bottom( aCompPt.Y() );
//STRIP001                 }
//STRIP001             }
//STRIP001         }
//STRIP001     }
//STRIP001
//STRIP001     if ( !pLeftRightBorder->GetInWidth() )
//STRIP001     {
//STRIP001         // OD 06.05.2003 #107169# - add 6th parameter
//STRIP001         ::lcl_SubTopBottom( aRect, rBox, _rAttrs, &_rFrm, _rRectFn, bPrtOutputDev );
//STRIP001     }
//STRIP001
//STRIP001     // OD 29.04.2003 #107169# - paint SwAligned-rectangle
//STRIP001     {
//STRIP001         SwRect aPaintRect( aRect );
//STRIP001         ::SwAlignRect( aPaintRect, _rFrm.GetShell() );
//STRIP001         // if <SwAlignRect> reveals rectangle with no width, adjust rectangle
//STRIP001         // to the prior left postion with width of one twip.
//STRIP001         if ( (aPaintRect.*_rRectFn->fnGetWidth)() == 0 )
//STRIP001         {
//STRIP001             if ( _bLeft )
//STRIP001             {
//STRIP001                 (aPaintRect.*_rRectFn->fnSetLeft)( (aRect.*_rRectFn->fnGetLeft)() );
//STRIP001                 (aPaintRect.*_rRectFn->fnSetRight)( (aRect.*_rRectFn->fnGetLeft)() );
//STRIP001                 (aPaintRect.*_rRectFn->fnAddRight)( 1 );
//STRIP001             }
//STRIP001             else
//STRIP001             {
//STRIP001                 (aPaintRect.*_rRectFn->fnSetLeft)( (aRect.*_rRectFn->fnGetRight)() - 1 );
//STRIP001                 (aPaintRect.*_rRectFn->fnSetRight)( (aRect.*_rRectFn->fnGetRight)() - 1 );
//STRIP001                 (aPaintRect.*_rRectFn->fnAddRight)( 1 );
//STRIP001             }
//STRIP001         }
//STRIP001         _rFrm.PaintBorderLine( _rRect, aPaintRect, &_rPage, &pLeftRightBorder->GetColor() );
//STRIP001     }
//STRIP001
//STRIP001     if ( pLeftRightBorder->GetInWidth() )
//STRIP001     {
//STRIP001         const long nDist = ::lcl_MinWidthDist( pLeftRightBorder->GetDistance() );
//STRIP001         long nWidth = ::lcl_AlignWidth( pLeftRightBorder->GetInWidth() );
//STRIP001         if ( _bLeft )
//STRIP001         {
//STRIP001             (aRect.*_rRectFn->fnAddRight)( nDist + nWidth );
//STRIP001             (aRect.*_rRectFn->fnSubLeft)( nWidth - (aRect.*_rRectFn->fnGetWidth)() );
//STRIP001         }
//STRIP001         else
//STRIP001         {
//STRIP001             (aRect.*_rRectFn->fnSubLeft)( nDist + nWidth );
//STRIP001             (aRect.*_rRectFn->fnAddRight)( nWidth - (aRect.*_rRectFn->fnGetWidth)() );
//STRIP001         }
//STRIP001         // OD 06.05.2003 #107169# - add 6th parameter
//STRIP001         ::lcl_SubTopBottom( aRect, rBox, _rAttrs, &_rFrm, _rRectFn, bPrtOutputDev );
//STRIP001         // OD 29.04.2003 #107169# - paint SwAligned-rectangle
//STRIP001         {
//STRIP001             SwRect aPaintRect( aRect );
//STRIP001             ::SwAlignRect( aPaintRect, _rFrm.GetShell() );
//STRIP001             // if <SwAlignRect> reveals rectangle with no width, adjust
//STRIP001             // rectangle to the prior left postion with width of one twip.
//STRIP001             if ( (aPaintRect.*_rRectFn->fnGetWidth)() == 0 )
//STRIP001             {
//STRIP001                 if ( _bLeft )
//STRIP001                 {
//STRIP001                     (aPaintRect.*_rRectFn->fnSetLeft)( (aRect.*_rRectFn->fnGetLeft)() );
//STRIP001                     (aPaintRect.*_rRectFn->fnSetRight)( (aRect.*_rRectFn->fnGetLeft)() );
//STRIP001                     (aPaintRect.*_rRectFn->fnAddRight)( 1 );
//STRIP001                 }
//STRIP001                 else
//STRIP001                 {
//STRIP001                     (aPaintRect.*_rRectFn->fnSetLeft)( (aRect.*_rRectFn->fnGetRight)() - 1 );
//STRIP001                     (aPaintRect.*_rRectFn->fnSetRight)( (aRect.*_rRectFn->fnGetRight)() - 1 );
//STRIP001                     (aPaintRect.*_rRectFn->fnAddRight)( 1 );
//STRIP001                 }
//STRIP001             }
//STRIP001             _rFrm.PaintBorderLine( _rRect, aPaintRect, &_rPage, &pLeftRightBorder->GetColor() );
//STRIP001         }
//STRIP001     }
//STRIP001 }

// OD 19.05.2003 #109667# - merge <lcl_PaintTopLine> and <lcl_PaintBottomLine>
// into <lcl_PaintTopLine>
//STRIP001 void lcl_PaintTopBottomLine( const sal_Bool         _bTop,
//STRIP001                              const SwFrm&           _rFrm,
//STRIP001                              const SwPageFrm&       _rPage,
//STRIP001                              const SwRect&          _rOutRect,
//STRIP001                              const SwRect&          _rRect,
//STRIP001                              const SwBorderAttrs&   _rAttrs,
//STRIP001                              const SwRectFn&        _rRectFn )
//STRIP001 {
//STRIP001     const SvxBoxItem& rBox = _rAttrs.GetBox();
//STRIP001     const SvxBorderLine* pTopBottomBorder = 0;
//STRIP001     if ( _bTop )
//STRIP001     {
//STRIP001         pTopBottomBorder = rBox.GetTop();
//STRIP001     }
//STRIP001     else
//STRIP001     {
//STRIP001         pTopBottomBorder = rBox.GetBottom();
//STRIP001     }
//STRIP001
//STRIP001     if ( !pTopBottomBorder )
//STRIP001     {
//STRIP001      return;
//STRIP001     }
//STRIP001
//STRIP001     SwRect aRect( _rOutRect );
//STRIP001     if ( _bTop )
//STRIP001     {
//STRIP001         (aRect.*_rRectFn->fnAddBottom)( ::lcl_AlignHeight( pTopBottomBorder->GetOutWidth() ) -
//STRIP001                                         (aRect.*_rRectFn->fnGetHeight)() );
//STRIP001     }
//STRIP001     else
//STRIP001     {
//STRIP001         (aRect.*_rRectFn->fnSubTop)( ::lcl_AlignHeight( pTopBottomBorder->GetOutWidth() ) -
//STRIP001                                      (aRect.*_rRectFn->fnGetHeight)() );
//STRIP001     }
//STRIP001
//STRIP001     // OD 29.04.2003 #107169# - paint SwAligned-rectangle
//STRIP001     {
//STRIP001         SwRect aPaintRect( aRect );
//STRIP001         ::SwAlignRect( aPaintRect, _rFrm.GetShell() );
//STRIP001         // if <SwAlignRect> reveals rectangle with no width, adjust rectangle
//STRIP001         // to the prior top postion with width of one twip.
//STRIP001         if ( (aPaintRect.*_rRectFn->fnGetHeight)() == 0 )
//STRIP001         {
//STRIP001             if ( _bTop )
//STRIP001             {
//STRIP001                 (aPaintRect.*_rRectFn->fnSetTop)( (aRect.*_rRectFn->fnGetTop)() );
//STRIP001                 (aPaintRect.*_rRectFn->fnSetBottom)( (aRect.*_rRectFn->fnGetTop)() );
//STRIP001                 (aPaintRect.*_rRectFn->fnAddBottom)( 1 );
//STRIP001             }
//STRIP001             else
//STRIP001             {
//STRIP001                 (aPaintRect.*_rRectFn->fnSetTop)( (aRect.*_rRectFn->fnGetBottom)() - 1 );
//STRIP001                 (aPaintRect.*_rRectFn->fnSetBottom)( (aRect.*_rRectFn->fnGetBottom)() - 1 );
//STRIP001                 (aPaintRect.*_rRectFn->fnAddBottom)( 1 );
//STRIP001             }
//STRIP001         }
//STRIP001         _rFrm.PaintBorderLine( _rRect, aPaintRect, &_rPage, &pTopBottomBorder->GetColor() );
//STRIP001     }
//STRIP001
//STRIP001     if ( pTopBottomBorder->GetInWidth() )
//STRIP001  {
//STRIP001         const long nDist = ::lcl_MinHeightDist( pTopBottomBorder->GetDistance() );
//STRIP001         const long nHeight = ::lcl_AlignHeight( pTopBottomBorder->GetInWidth() );
//STRIP001         if ( _bTop )
//STRIP001         {
//STRIP001             (aRect.*_rRectFn->fnAddBottom)( nDist + nHeight );
//STRIP001             (aRect.*_rRectFn->fnSubTop)( nHeight - (aRect.*_rRectFn->fnGetHeight)() );
//STRIP001         }
//STRIP001         else
//STRIP001         {
//STRIP001             (aRect.*_rRectFn->fnSubTop)( nDist + nHeight );
//STRIP001             (aRect.*_rRectFn->fnAddBottom)( nHeight -(aRect.*_rRectFn->fnGetHeight)() );
//STRIP001         }
//STRIP001         ::lcl_SubLeftRight( aRect, rBox, _rRectFn );
//STRIP001         // OD 29.04.2003 #107169# - paint SwAligned-rectangle
//STRIP001         {
//STRIP001             SwRect aPaintRect( aRect );
//STRIP001             ::SwAlignRect( aPaintRect, _rFrm.GetShell() );
//STRIP001             // if <SwAlignRect> reveals rectangle with no width, adjust
//STRIP001             // rectangle to the prior top postion with width of one twip.
//STRIP001             if ( (aPaintRect.*_rRectFn->fnGetHeight)() == 0 )
//STRIP001             {
//STRIP001                 if ( _bTop )
//STRIP001                 {
//STRIP001                     (aPaintRect.*_rRectFn->fnSetTop)( (aRect.*_rRectFn->fnGetTop)() );
//STRIP001                     (aPaintRect.*_rRectFn->fnSetBottom)( (aRect.*_rRectFn->fnGetTop)() );
//STRIP001                     (aPaintRect.*_rRectFn->fnAddBottom)( 1 );
//STRIP001                 }
//STRIP001                 else
//STRIP001                 {
//STRIP001                     (aPaintRect.*_rRectFn->fnSetTop)( (aRect.*_rRectFn->fnGetBottom)() - 1 );
//STRIP001                     (aPaintRect.*_rRectFn->fnSetBottom)( (aRect.*_rRectFn->fnGetBottom)() - 1 );
//STRIP001                     (aPaintRect.*_rRectFn->fnAddBottom)( 1 );
//STRIP001                 }
//STRIP001             }
//STRIP001             _rFrm.PaintBorderLine( _rRect, aPaintRect, &_rPage, &pTopBottomBorder->GetColor() );
//STRIP001         }
//STRIP001  }
//STRIP001 }


/*************************************************************************
|*
|*  const SwFrm* lcl_HasNextCell( const SwFrm& rFrm )
|*
|* No comment. #i15844#
|*
|*************************************************************************/

//STRIP001 const SwFrm* lcl_HasNextCell( const SwFrm& rFrm )
//STRIP001 {
//STRIP001     ASSERT( rFrm.IsCellFrm(),
//STRIP001             "lcl_HasNextCell( const SwFrm& rFrm ) should be called with SwCellFrm" )
//STRIP001
//STRIP001     const SwFrm* pTmpFrm = &rFrm;
//STRIP001     do
//STRIP001     {
//STRIP001         if ( pTmpFrm->GetNext() )
//STRIP001             return pTmpFrm->GetNext();
//STRIP001
//STRIP001         pTmpFrm = pTmpFrm->GetUpper()->GetUpper();
//STRIP001     }
//STRIP001     while ( pTmpFrm->IsCellFrm() );
//STRIP001
//STRIP001     return 0;
//STRIP001 }


/*************************************************************************
|*
|*  SwFrm::PaintBorder()
|*
|*  Beschreibung        Malt Schatten und Umrandung
|*  Ersterstellung      MA 23.01.92
|*  Letzte Aenderung    MA 29. Jul. 96
|*
|*************************************************************************/

/** local method to determine cell frame, from which the border attributes
    for paint of top/bottom border has to be used.

    OD 21.02.2003 #b4779636#, #107692#

    @author OD


    @param _pCellFrm
    input parameter - constant pointer to cell frame for which the cell frame
    for the border attributes has to be determined.

    @param _rCellBorderAttrs
    input parameter - constant reference to the border attributes of cell frame
    <_pCellFrm>.

    @param _bTop
    input parameter - boolean, that controls, if cell frame for top border or
    for bottom border has to be determined.

    @return constant pointer to cell frame, for which the border attributes has
    to be used
*/
//STRIP001 const SwFrm* lcl_GetCellFrmForBorderAttrs( const SwFrm*         _pCellFrm,
//STRIP001                                            const SwBorderAttrs& _rCellBorderAttrs,
//STRIP001                                            const bool           _bTop )
//STRIP001 {
//STRIP001     ASSERT( _pCellFrm, "No cell frame available, dying soon" )
//STRIP001
//STRIP001     // determine, if cell frame is at bottom/top border of a table frame and
//STRIP001     // the table frame has/is a follow.
//STRIP001     const SwFrm* pTmpFrm = _pCellFrm;
//STRIP001     bool bCellAtBorder = true;
//STRIP001     bool bCellAtLeftBorder = !_pCellFrm->GetPrev();
//STRIP001     bool bCellAtRightBorder = !_pCellFrm->GetNext();
//STRIP001     while( !pTmpFrm->IsRowFrm() || !pTmpFrm->GetUpper()->IsTabFrm() )
//STRIP001     {
//STRIP001         pTmpFrm = pTmpFrm->GetUpper();
//STRIP001         if ( pTmpFrm->IsRowFrm() &&
//STRIP001              (_bTop ? pTmpFrm->GetPrev() : pTmpFrm->GetNext())
//STRIP001            )
//STRIP001         {
//STRIP001             bCellAtBorder = false;
//STRIP001         }
//STRIP001         if ( pTmpFrm->IsCellFrm() )
//STRIP001         {
//STRIP001             if ( pTmpFrm->GetPrev() )
//STRIP001             {
//STRIP001                 bCellAtLeftBorder = false;
//STRIP001             }
//STRIP001             if ( pTmpFrm->GetNext() )
//STRIP001             {
//STRIP001                 bCellAtRightBorder = false;
//STRIP001             }
//STRIP001         }
//STRIP001     }
//STRIP001     ASSERT( pTmpFrm && pTmpFrm->IsRowFrm(), "No RowFrm available" );
//STRIP001
//STRIP001     const SwLayoutFrm* pParentRowFrm = static_cast<const SwLayoutFrm*>(pTmpFrm);
//STRIP001     const SwTabFrm* pParentTabFrm =
//STRIP001             static_cast<const SwTabFrm*>(pParentRowFrm->GetUpper());
//STRIP001
//STRIP001     const bool bCellNeedsAttribute = bCellAtBorder &&
//STRIP001                                      ( _bTop ?
//STRIP001                                       // bCellInFirstRowWithMaster
//STRIP001                                        ( !pParentRowFrm->GetPrev() &&
//STRIP001                                          pParentTabFrm->IsFollow() &&
//STRIP001                                          !pParentTabFrm->GetTable()->IsHeadlineRepeat() ) :
//STRIP001                                       // bCellInLastRowWithFollow
//STRIP001                                        ( !pParentRowFrm->GetNext() &&
//STRIP001                                          pParentTabFrm->GetFollow() )
//STRIP001                                      );
//STRIP001
//STRIP001     const SwFrm* pRet = _pCellFrm;
//STRIP001     if ( bCellNeedsAttribute )
//STRIP001     {
//STRIP001         // determine, if cell frame has no borders inside the table.
//STRIP001         const SwFrm* pNextCell = 0;
//STRIP001         bool bNoBordersInside = false;
//STRIP001
//STRIP001         if ( bCellAtLeftBorder && ( 0 != ( pNextCell = lcl_HasNextCell( *_pCellFrm ) ) ) )
//STRIP001         {
//STRIP001             SwBorderAttrAccess aAccess( SwFrm::GetCache(), pNextCell );
//STRIP001             const SwBorderAttrs &rBorderAttrs = *aAccess.Get();
//STRIP001             const SvxBoxItem& rBorderBox = rBorderAttrs.GetBox();
//STRIP001             bCellAtRightBorder = !lcl_HasNextCell( *pNextCell );
//STRIP001             bNoBordersInside =
//STRIP001                 ( !rBorderBox.GetTop()    || !pParentRowFrm->GetPrev() ) &&
//STRIP001                   !rBorderBox.GetLeft() &&
//STRIP001                 ( !rBorderBox.GetRight()  || bCellAtRightBorder ) &&
//STRIP001                 ( !rBorderBox.GetBottom() || !pParentRowFrm->GetNext() );
//STRIP001         }
//STRIP001         else
//STRIP001         {
//STRIP001             const SvxBoxItem& rBorderBox = _rCellBorderAttrs.GetBox();
//STRIP001             bNoBordersInside =
//STRIP001                 ( !rBorderBox.GetTop()    || !pParentRowFrm->GetPrev() ) &&
//STRIP001                 ( !rBorderBox.GetLeft()   || bCellAtLeftBorder ) &&
//STRIP001                 ( !rBorderBox.GetRight()  || bCellAtRightBorder ) &&
//STRIP001                 ( !rBorderBox.GetBottom() || !pParentRowFrm->GetNext() );
//STRIP001         }
//STRIP001
//STRIP001         if ( bNoBordersInside )
//STRIP001         {
//STRIP001             if ( _bTop && !_rCellBorderAttrs.GetBox().GetTop() )
//STRIP001             {
//STRIP001                 // #b4779636#-hack:
//STRIP001                 // Cell frame has no top border and no border inside the table, but
//STRIP001                 // it is at the top border of a table frame, which is a follow.
//STRIP001                 // Thus, use border attributes of cell frame in first row of complete table.
//STRIP001                 // First, determine first table frame of complete table.
//STRIP001                 SwTabFrm* pMasterTabFrm = const_cast<SwTabFrm*>(pParentTabFrm->FindMaster());
//STRIP001                 while ( pMasterTabFrm->IsFollow() )
//STRIP001                 {
//STRIP001                     pMasterTabFrm = pMasterTabFrm->FindMaster();
//STRIP001                 }
//STRIP001                 // determine first row of complete table.
//STRIP001                 const SwFrm* pFirstRow = pMasterTabFrm->GetLower();
//STRIP001                 // return first cell in first row
//STRIP001                 SwFrm* pTmpFrm = const_cast<SwFrm*>(pFirstRow->GetLower());
//STRIP001                 while ( !pTmpFrm->IsCellFrm() ||
//STRIP001                         ( pTmpFrm->GetLower() && pTmpFrm->GetLower()->IsRowFrm() )
//STRIP001                       )
//STRIP001                 {
//STRIP001                     pTmpFrm = pTmpFrm->GetLower();
//STRIP001                 }
//STRIP001                 ASSERT( pTmpFrm && pTmpFrm->IsCellFrm(), "No CellFrm available" );
//STRIP001                 pRet = pTmpFrm;
//STRIP001             }
//STRIP001             else if ( !_bTop && !_rCellBorderAttrs.GetBox().GetBottom() )
//STRIP001             {
//STRIP001                 // #b4779636#-hack:
//STRIP001                 // Cell frame has no bottom border and no border inside the table,
//STRIP001                 // but it is at the bottom border of a table frame, which has a follow.
//STRIP001                 // Thus, use border attributes of cell frame in last row of complete table.
//STRIP001                 // First, determine last table frame of complete table.
//STRIP001                 SwTabFrm* pLastTabFrm = const_cast<SwTabFrm*>(pParentTabFrm->GetFollow());
//STRIP001                 while ( pLastTabFrm->GetFollow() )
//STRIP001                 {
//STRIP001                     pLastTabFrm = pLastTabFrm->GetFollow();
//STRIP001                 }
//STRIP001                 // determine last row of complete table.
//STRIP001                 SwFrm* pLastRow = pLastTabFrm->GetLower();
//STRIP001                 while ( pLastRow->GetNext() )
//STRIP001                 {
//STRIP001                     pLastRow = pLastRow->GetNext();
//STRIP001                 }
//STRIP001                 // return first bottom border cell in last row
//STRIP001                 SwFrm* pTmpFrm = const_cast<SwFrm*>(pLastRow->GetLower());
//STRIP001                 while ( !pTmpFrm->IsCellFrm() ||
//STRIP001                         ( pTmpFrm->GetLower() && pTmpFrm->GetLower()->IsRowFrm() )
//STRIP001                       )
//STRIP001                 {
//STRIP001                     if ( pTmpFrm->IsRowFrm() )
//STRIP001                     {
//STRIP001                         while ( pTmpFrm->GetNext() )
//STRIP001                         {
//STRIP001                             pTmpFrm = pTmpFrm->GetNext();
//STRIP001                         }
//STRIP001                     }
//STRIP001                     pTmpFrm = pTmpFrm->GetLower();
//STRIP001                 }
//STRIP001                 ASSERT( pTmpFrm && pTmpFrm->IsCellFrm(), "No CellFrm available" );
//STRIP001                 pRet = pTmpFrm;
//STRIP001             }
//STRIP001         }
//STRIP001     }
//STRIP001
//STRIP001     return pRet;
//STRIP001 }

//STRIP001 void SwFrm::PaintBorder( const SwRect& rRect, const SwPageFrm *pPage,
//STRIP001                       const SwBorderAttrs &rAttrs ) const
//STRIP001 {
//STRIP001
//STRIP001  //fuer (Row,Body,Ftn,Root,Column,NoTxt) gibt's hier nix zu tun
//STRIP001  if ( (GetType() & 0x90C5) || (Prt().SSize() == Frm().SSize()) )
//STRIP001      return;
//STRIP001
//STRIP001  if ( (GetType() & 0x2000) &&    //Cell
//STRIP001       !pGlobalShell->GetViewOptions()->IsTable() )
//STRIP001      return;
//STRIP001
//STRIP001     const bool bLine = rAttrs.IsLine() ? true : false;
//STRIP001     const bool bShadow = rAttrs.GetShadow().GetLocation() != SVX_SHADOW_NONE;
//STRIP001
//STRIP001     // OD 24.02.2003 #b4779636#, #107692# - flag to control,
//STRIP001     // if #b4779636#-hack has to be used.
//STRIP001     const bool bb4779636HackActive = true;
//STRIP001     // OD 21.02.2003 #b4779636#, #107692#
//STRIP001     const SwFrm* pCellFrmForBottomBorderAttrs = 0;
//STRIP001     const SwFrm* pCellFrmForTopBorderAttrs = 0;
//STRIP001     bool         bFoundCellForTopOrBorderAttrs = false;
//STRIP001     if ( bb4779636HackActive && IsCellFrm() )
//STRIP001     {
//STRIP001         pCellFrmForBottomBorderAttrs = lcl_GetCellFrmForBorderAttrs( this, rAttrs, false );
//STRIP001         if ( pCellFrmForBottomBorderAttrs != this )
//STRIP001             bFoundCellForTopOrBorderAttrs = true;
//STRIP001         pCellFrmForTopBorderAttrs = lcl_GetCellFrmForBorderAttrs( this, rAttrs, true );
//STRIP001         if ( pCellFrmForTopBorderAttrs != this )
//STRIP001             bFoundCellForTopOrBorderAttrs = true;
//STRIP001     }
//STRIP001
//STRIP001     // OD 24.02.2003 #b4779636#, #107692# - add condition <bFoundCellForTopOrBorderAttrs>
//STRIP001     // for #b4779636#-hack
//STRIP001     if ( bLine || bShadow || bFoundCellForTopOrBorderAttrs )
//STRIP001  {
//STRIP001      //Wenn das Rechteck vollstandig innerhalb der PrtArea liegt,
//STRIP001      //so braucht kein Rand gepainted werden.
//STRIP001      //Fuer die PrtArea muss der Aligned'e Wert zugrunde gelegt werden,
//STRIP001      //anderfalls wuerden u.U. Teile nicht verarbeitet.
//STRIP001      SwRect aRect( Prt() );
//STRIP001      aRect += Frm().Pos();
//STRIP001      ::SwAlignRect( aRect, pGlobalShell );
//STRIP001         // OD 27.09.2002 #103636# - new local boolean variable in order to
//STRIP001         // suspend border paint under special cases - see below.
//STRIP001         // NOTE: This is a fix for the implementation of feature #99657#.
//STRIP001         bool bDrawOnlyShadowForTransparentFrame = false;
//STRIP001         if ( aRect.IsInside( rRect ) )
//STRIP001         {
//STRIP001             // OD 27.09.2002 #103636# - paint shadow, if background is transparent.
//STRIP001             // Because of introduced transparent background for fly frame #99657#,
//STRIP001             // the shadow have to be drawn if the background is transparent,
//STRIP001             // in spite the fact that the paint rectangle <rRect> lies fully
//STRIP001             // in the printing area.
//STRIP001             // NOTE to chosen solution:
//STRIP001             //     On transparent background, continue processing, but suspend
//STRIP001             //     drawing of border by setting <bDrawOnlyShadowForTransparentFrame>
//STRIP001             //     to true.
//STRIP001             if ( IsLayoutFrm() &&
//STRIP001                  static_cast<const SwLayoutFrm*>(this)->GetFmt()->IsBackgroundTransparent() )
//STRIP001             {
//STRIP001                  bDrawOnlyShadowForTransparentFrame = true;
//STRIP001             }
//STRIP001             else
//STRIP001             {
//STRIP001                 return;
//STRIP001             }
//STRIP001         }
//STRIP001
//STRIP001      if ( !pPage )
//STRIP001          pPage = FindPageFrm();
//STRIP001
//STRIP001      ::lcl_CalcBorderRect( aRect, this, rAttrs, TRUE );
//STRIP001      rAttrs.SetGetCacheLine( TRUE );
//STRIP001      if ( bShadow )
//STRIP001          PaintShadow( rRect, aRect, pPage, rAttrs );
//STRIP001         // OD 27.09.2002 #103636# - suspend drawing of border
//STRIP001         // add condition < NOT bDrawOnlyShadowForTransparentFrame > - see above
//STRIP001         // OD 24.02.2003 #b4779636#, #107692# - add condition <bFoundCellForTopOrBorderAttrs>
//STRIP001         // for #b4779636#-hack.
//STRIP001         if ( ( bLine || bFoundCellForTopOrBorderAttrs ) &&
//STRIP001              !bDrawOnlyShadowForTransparentFrame )
//STRIP001      {
//STRIP001             SWRECTFN( this )
//STRIP001             // OD 19.05.2003 #109667# - use new method <lcl_PaintLeftRightLine(..)>
//STRIP001             //::lcl_PaintLeftLine  ( this, pPage, aRect, rRect, rAttrs, fnRect );
//STRIP001             //::lcl_PaintRightLine ( this, pPage, aRect, rRect, rAttrs, fnRect );
//STRIP001             ::lcl_PaintLeftRightLine ( sal_True, *(this), *(pPage), aRect, rRect, rAttrs, fnRect );
//STRIP001             ::lcl_PaintLeftRightLine ( sal_False, *(this), *(pPage), aRect, rRect, rAttrs, fnRect );
//STRIP001          if ( !IsCntntFrm() || rAttrs.GetTopLine( this ) )
//STRIP001             {
//STRIP001                 // OD 21.02.2003 #b4779636#, #107692# -
//STRIP001                 // #b4779636#-hack: If another cell frame for top border
//STRIP001                 // paint is found, paint its top border.
//STRIP001                 if ( IsCellFrm() && pCellFrmForTopBorderAttrs != this )
//STRIP001                 {
//STRIP001                     SwBorderAttrAccess aAccess( SwFrm::GetCache(),
//STRIP001                                                 pCellFrmForTopBorderAttrs );
//STRIP001                     const SwBorderAttrs &rTopAttrs = *aAccess.Get();
//STRIP001                     // OD 19.05.2003 #109667# - use new method <lcl_PaintTopBottomLine(..)>
//STRIP001                     //::lcl_PaintTopLine( this, pPage, aRect, rRect, rTopAttrs, fnRect );
//STRIP001                     ::lcl_PaintTopBottomLine( sal_True, *(this), *(pPage), aRect, rRect, rTopAttrs, fnRect );
//STRIP001                 }
//STRIP001                 else
//STRIP001                 {
//STRIP001                     // OD 19.05.2003 #109667# - use new method <lcl_PaintTopBottomLine(..)>
//STRIP001                     //::lcl_PaintTopLine( this, pPage, aRect, rRect, rAttrs, fnRect );
//STRIP001                     ::lcl_PaintTopBottomLine( sal_True, *(this), *(pPage), aRect, rRect, rAttrs, fnRect );
//STRIP001                 }
//STRIP001             }
//STRIP001             if ( !IsCntntFrm() || rAttrs.GetBottomLine( this ) )
//STRIP001             {
//STRIP001                 // OD 21.02.2003 #b4779636#, #107692# -
//STRIP001                 // #b4779636#-hack: If another cell frame for bottom border
//STRIP001                 // paint is found, paint its bottom border.
//STRIP001                 if ( IsCellFrm() && pCellFrmForBottomBorderAttrs != this )
//STRIP001                 {
//STRIP001                     SwBorderAttrAccess aAccess( SwFrm::GetCache(),
//STRIP001                                                 pCellFrmForBottomBorderAttrs );
//STRIP001                     const SwBorderAttrs &rBottomAttrs = *aAccess.Get();
//STRIP001                     // OD 19.05.2003 #109667# - use new method <lcl_PaintTopBottomLine(..)>
//STRIP001                     //::lcl_PaintBottomLine(this, pPage, aRect, rRect, rBottomAttrs, fnRect);
//STRIP001                     ::lcl_PaintTopBottomLine(sal_False, *(this), *(pPage), aRect, rRect, rBottomAttrs, fnRect);
//STRIP001                 }
//STRIP001                 else
//STRIP001                 {
//STRIP001                     // OD 19.05.2003 #109667# - use new method <lcl_PaintTopBottomLine(..)>
//STRIP001                     //::lcl_PaintBottomLine(this, pPage, aRect, rRect, rAttrs, fnRect);
//STRIP001                     ::lcl_PaintTopBottomLine(sal_False, *(this), *(pPage), aRect, rRect, rAttrs, fnRect);
//STRIP001                 }
//STRIP001             }
//STRIP001      }
//STRIP001      rAttrs.SetGetCacheLine( FALSE );
//STRIP001  }
//STRIP001 }
/*************************************************************************
|*
|*  SwFtnContFrm::PaintBorder()
|*
|*  Beschreibung        Spezialimplementierung wg. der Fussnotenlinie.
|*      Derzeit braucht nur der obere Rand beruecksichtigt werden.
|*      Auf andere Linien und Schatten wird verzichtet.
|*  Ersterstellung      MA 27. Feb. 93
|*  Letzte Aenderung    MA 08. Sep. 93
|*
|*************************************************************************/

//STRIP001 void SwFtnContFrm::PaintBorder( const SwRect& rRect, const SwPageFrm *pPage,
//STRIP001                              const SwBorderAttrs & ) const
//STRIP001 {
//STRIP001  //Wenn das Rechteck vollstandig innerhalb der PrtArea liegt, so gibt es
//STRIP001  //keinen Rand zu painten.
//STRIP001  SwRect aRect( Prt() );
//STRIP001  aRect.Pos() += Frm().Pos();
//STRIP001  if ( !aRect.IsInside( rRect ) )
//STRIP001      PaintLine( rRect, pPage );
//STRIP001 }
/*************************************************************************
|*
|*  SwFtnContFrm::PaintLine()
|*
|*  Beschreibung        Fussnotenline malen.
|*  Ersterstellung      MA 02. Mar. 93
|*  Letzte Aenderung    MA 28. Mar. 94
|*
|*************************************************************************/

//STRIP001 void SwFtnContFrm::PaintLine( const SwRect& rRect,
//STRIP001                            const SwPageFrm *pPage ) const
//STRIP001 {
//STRIP001  //Laenge der Linie ergibt sich aus der prozentualen Angabe am PageDesc.
//STRIP001  //Die Position ist ebenfalls am PageDesc angegeben.
//STRIP001  //Der Pen steht direkt im PageDesc.
//STRIP001
//STRIP001  if ( !pPage )
//STRIP001      pPage = FindPageFrm();
//STRIP001  const SwPageFtnInfo &rInf = pPage->GetPageDesc()->GetFtnInfo();
//STRIP001
//STRIP001     SWRECTFN( this )
//STRIP001     SwTwips nPrtWidth = (Prt().*fnRect->fnGetWidth)();
//STRIP001     Fraction aFract( nPrtWidth, 1 );
//STRIP001  const SwTwips nWidth = (long)(aFract *= rInf.GetWidth());
//STRIP001
//STRIP001     SwTwips nX = (this->*fnRect->fnGetPrtLeft)();
//STRIP001  switch ( rInf.GetAdj() )
//STRIP001  {
//STRIP001      case FTNADJ_CENTER:
//STRIP001             nX += nPrtWidth/2 - nWidth/2; break;
//STRIP001      case FTNADJ_RIGHT:
//STRIP001             nX += nPrtWidth - nWidth; break;
//STRIP001      case FTNADJ_LEFT:
//STRIP001          /* do nothing */; break;
//STRIP001      default:
//STRIP001          ASSERT( !this, "Neues Adjustment fuer Fussnotenlinie?" );
//STRIP001  }
//STRIP001     SwTwips nLineWidth = rInf.GetLineWidth();
//STRIP001     const SwRect aLineRect = bVert ?
//STRIP001         SwRect( Point(Frm().Left()+Frm().Width()-rInf.GetTopDist()-nLineWidth,
//STRIP001                       nX), Size( nLineWidth, nWidth ) )
//STRIP001             : SwRect( Point( nX, Frm().Pos().Y() + rInf.GetTopDist() ),
//STRIP001                             Size( nWidth, rInf.GetLineWidth()));
//STRIP001  if ( aLineRect.HasArea() )
//STRIP001      PaintBorderLine( rRect, aLineRect , pPage, &rInf.GetLineColor() );
//STRIP001 }

/*************************************************************************
|*
|*  SwLayoutFrm::PaintColLines()
|*
|*  Beschreibung        Painted die Trennlinien fuer die innenliegenden
|*                      Spalten.
|*  Ersterstellung      MA 21. Jun. 93
|*  Letzte Aenderung    MA 28. Mar. 94
|*
|*************************************************************************/

//STRIP001 void SwLayoutFrm::PaintColLines( const SwRect &rRect, const SwFmtCol &rFmtCol,
//STRIP001                               const SwPageFrm *pPage ) const
//STRIP001 {
//STRIP001  const SwFrm *pCol = Lower();
//STRIP001  if ( !pCol || !pCol->IsColumnFrm() )
//STRIP001      return;
//STRIP001
//STRIP001     SwRectFn fnRect = pCol->IsVertical() ? fnRectVert : fnRectHori;
//STRIP001     SwRect aLineRect = Prt();
//STRIP001     aLineRect += Frm().Pos();
//STRIP001
//STRIP001     SwTwips nTop = ((aLineRect.*fnRect->fnGetHeight)()*rFmtCol.GetLineHeight())
//STRIP001                    / 100 - (aLineRect.*fnRect->fnGetHeight)();
//STRIP001     SwTwips nBottom = 0;
//STRIP001
//STRIP001  switch ( rFmtCol.GetLineAdj() )
//STRIP001  {
//STRIP001      case COLADJ_CENTER:
//STRIP001             nBottom = nTop / 2; nTop -= nBottom; break;
//STRIP001      case COLADJ_TOP:
//STRIP001             nBottom = nTop; nTop = 0; break;
//STRIP001      case COLADJ_BOTTOM:
//STRIP001             break;
//STRIP001      default:
//STRIP001          ASSERT( !this, "Neues Adjustment fuer Spaltenlinie?" );
//STRIP001  }
//STRIP001
//STRIP001     if( nTop )
//STRIP001         (aLineRect.*fnRect->fnSubTop)( nTop );
//STRIP001     if( nBottom )
//STRIP001         (aLineRect.*fnRect->fnAddBottom)( nBottom );
//STRIP001
//STRIP001     SwTwips nPenHalf = rFmtCol.GetLineWidth();
//STRIP001     (aLineRect.*fnRect->fnSetWidth)( nPenHalf );
//STRIP001     nPenHalf /= 2;
//STRIP001
//STRIP001     //Damit uns nichts verlorengeht muessen wir hier etwas grosszuegiger sein.
//STRIP001  SwRect aRect( rRect );
//STRIP001     (aRect.*fnRect->fnSubLeft)( nPenHalf + nPixelSzW );
//STRIP001     (aRect.*fnRect->fnAddRight)( nPenHalf + nPixelSzW );
//STRIP001     SwRectGet fnGetX = IsRightToLeft() ? fnRect->fnGetLeft : fnRect->fnGetRight;
//STRIP001  while ( pCol->GetNext() )
//STRIP001  {
//STRIP001         (aLineRect.*fnRect->fnSetPosX)
//STRIP001             ( (pCol->Frm().*fnGetX)() - nPenHalf );
//STRIP001      if ( aRect.IsOver( aLineRect ) )
//STRIP001             PaintBorderLine( aRect, aLineRect , pPage, &rFmtCol.GetLineColor());
//STRIP001      pCol = pCol->GetNext();
//STRIP001  }
//STRIP001 }

//STRIP001 void SwPageFrm::PaintGrid( OutputDevice* pOut, SwRect &rRect ) const
//STRIP001 {
//STRIP001     if( !bHasGrid || pRetoucheFly || pRetoucheFly2 )
//STRIP001         return;
//STRIP001     GETGRID( this )
//STRIP001     if( pGrid && ( OUTDEV_PRINTER != pOut->GetOutDevType() ?
//STRIP001         pGrid->GetDisplayGrid() : pGrid->GetPrintGrid() ) )
//STRIP001     {
//STRIP001         const SwLayoutFrm* pBody = FindBodyCont();
//STRIP001         if( pBody )
//STRIP001         {
//STRIP001             SwRect aGrid( pBody->Prt() );
//STRIP001             aGrid += pBody->Frm().Pos();
//STRIP001
//STRIP001             SwRect aInter( aGrid );
//STRIP001             aInter.Intersection( rRect );
//STRIP001             if( aInter.HasArea() )
//STRIP001             {
//STRIP001                 BOOL bGrid = pGrid->GetRubyTextBelow();
//STRIP001                 BOOL bCell = GRID_LINES_CHARS == pGrid->GetGridType();
//STRIP001                 long nGrid = pGrid->GetBaseHeight();
//STRIP001                 long nRuby = pGrid->GetRubyHeight();
//STRIP001                 long nSum = nGrid + nRuby;
//STRIP001                 const Color *pCol = &pGrid->GetColor();
//STRIP001
//STRIP001                 SwTwips nRight = aInter.Left() + aInter.Width();
//STRIP001                 SwTwips nBottom = aInter.Top() + aInter.Height();
//STRIP001                 if( IsVertical() )
//STRIP001                 {
//STRIP001                     SwTwips nOrig = aGrid.Left() + aGrid.Width();
//STRIP001                     SwTwips nY = nOrig + nSum *
//STRIP001                                  ( ( nOrig - aInter.Left() ) / nSum );
//STRIP001                     SwRect aTmp( Point( nY, aInter.Top() ),
//STRIP001                                 Size( 1, aInter.Height() ) );
//STRIP001                     SwTwips nX = aGrid.Top() + nGrid *
//STRIP001                                 ( ( aInter.Top() - aGrid.Top() )/ nGrid );
//STRIP001                     if( nX < aInter.Top() )
//STRIP001                         nX += nGrid;
//STRIP001                     SwTwips nGridBottom = aGrid.Top() + aGrid.Height();
//STRIP001                     BOOL bLeft = aGrid.Top() >= aInter.Top();
//STRIP001                     BOOL bRight = nGridBottom <= nBottom;
//STRIP001                     BOOL bBorder = bLeft || bRight;
//STRIP001                     while( nY > nRight )
//STRIP001                     {
//STRIP001                         aTmp.Pos().X() = nY;
//STRIP001                         if( bGrid )
//STRIP001                         {
//STRIP001                             nY -= nGrid;
//STRIP001                             SwTwips nPosY = Max( aInter.Left(), nY );
//STRIP001                             SwTwips nHeight = Min(nRight, aTmp.Pos().X())-nPosY;
//STRIP001                             if( nHeight > 0 )
//STRIP001                             {
//STRIP001                                 if( bCell )
//STRIP001                                 {
//STRIP001                                     SwRect aVert( Point( nPosY, nX ),
//STRIP001                                                 Size( nHeight, 1 ) );
//STRIP001                                     while( aVert.Top() <= nBottom )
//STRIP001                                     {
//STRIP001                                         PaintBorderLine(rRect,aVert,this,pCol);
//STRIP001                                         aVert.Pos().Y() += nGrid;
//STRIP001                                     }
//STRIP001                                 }
//STRIP001                                 else if( bBorder )
//STRIP001                                 {
//STRIP001                                     SwRect aVert( Point( nPosY, aGrid.Top() ),
//STRIP001                                                   Size( nHeight, 1 ) );
//STRIP001                                     if( bLeft )
//STRIP001                                         PaintBorderLine(rRect,aVert,this,pCol);
//STRIP001                                     if( bRight )
//STRIP001                                     {
//STRIP001                                         aVert.Pos().Y() = nGridBottom;
//STRIP001                                         PaintBorderLine(rRect,aVert,this,pCol);
//STRIP001                                     }
//STRIP001                                 }
//STRIP001                             }
//STRIP001                         }
//STRIP001                         else
//STRIP001                         {
//STRIP001                             nY -= nRuby;
//STRIP001                             if( bBorder )
//STRIP001                             {
//STRIP001                                 SwTwips nPos = Max( aInter.Left(), nY );
//STRIP001                                 SwTwips nW = Min(nRight, aTmp.Pos().X()) - nPos;
//STRIP001                                 SwRect aVert( Point( nPos, aGrid.Top() ),
//STRIP001                                               Size( nW, 1 ) );
//STRIP001                                 if( nW > 0 )
//STRIP001                                 {
//STRIP001                                     if( bLeft )
//STRIP001                                         PaintBorderLine(rRect,aVert,this,pCol);
//STRIP001                                     if( bRight )
//STRIP001                                     {
//STRIP001                                         aVert.Pos().Y() = nGridBottom;
//STRIP001                                         PaintBorderLine(rRect,aVert,this,pCol);
//STRIP001                                     }
//STRIP001                                 }
//STRIP001                             }
//STRIP001                         }
//STRIP001                         bGrid = !bGrid;
//STRIP001                     }
//STRIP001                     while( nY >= aInter.Left() )
//STRIP001                     {
//STRIP001                         aTmp.Pos().X() = nY;
//STRIP001                         PaintBorderLine( rRect, aTmp, this, pCol);
//STRIP001                         if( bGrid )
//STRIP001                         {
//STRIP001                             nY -= nGrid;
//STRIP001                             SwTwips nHeight = aTmp.Pos().X()
//STRIP001                                               - Max(aInter.Left(), nY );
//STRIP001                             if( nHeight > 0 )
//STRIP001                             {
//STRIP001                                 if( bCell )
//STRIP001                                 {
//STRIP001                                     SwRect aVert( Point(aTmp.Pos().X()-nHeight,
//STRIP001                                                   nX ), Size( nHeight, 1 ) );
//STRIP001                                     while( aVert.Top() <= nBottom )
//STRIP001                                     {
//STRIP001                                         PaintBorderLine(rRect,aVert,this,pCol);
//STRIP001                                         aVert.Pos().Y() += nGrid;
//STRIP001                                     }
//STRIP001                                 }
//STRIP001                                 else if( bBorder )
//STRIP001                                 {
//STRIP001                                     SwRect aVert( Point(aTmp.Pos().X()-nHeight,
//STRIP001                                             aGrid.Top() ), Size( nHeight, 1 ) );
//STRIP001                                     if( bLeft )
//STRIP001                                         PaintBorderLine(rRect,aVert,this,pCol);
//STRIP001                                     if( bRight )
//STRIP001                                     {
//STRIP001                                         aVert.Pos().Y() = nGridBottom;
//STRIP001                                         PaintBorderLine(rRect,aVert,this,pCol);
//STRIP001                                     }
//STRIP001                                 }
//STRIP001                             }
//STRIP001                         }
//STRIP001                         else
//STRIP001                         {
//STRIP001                             nY -= nRuby;
//STRIP001                             if( bBorder )
//STRIP001                             {
//STRIP001                                 SwTwips nPos = Max( aInter.Left(), nY );
//STRIP001                                 SwTwips nW = Min(nRight, aTmp.Pos().X()) - nPos;
//STRIP001                                 SwRect aVert( Point( nPos, aGrid.Top() ),
//STRIP001                                               Size( nW, 1 ) );
//STRIP001                                 if( nW > 0 )
//STRIP001                                 {
//STRIP001                                     if( bLeft )
//STRIP001                                         PaintBorderLine(rRect,aVert,this,pCol);
//STRIP001                                     if( bRight )
//STRIP001                                     {
//STRIP001                                         aVert.Pos().Y() = nGridBottom;
//STRIP001                                         PaintBorderLine(rRect,aVert,this,pCol);
//STRIP001                                     }
//STRIP001                                 }
//STRIP001                             }
//STRIP001                         }
//STRIP001                         bGrid = !bGrid;
//STRIP001                     }
//STRIP001                 }
//STRIP001                 else
//STRIP001                 {
//STRIP001                     SwTwips nOrig = aGrid.Top();
//STRIP001                     SwTwips nY = nOrig + nSum *( (aInter.Top()-nOrig)/nSum );
//STRIP001                     SwRect aTmp( Point( aInter.Left(), nY ),
//STRIP001                                 Size( aInter.Width(), 1 ) );
//STRIP001                     SwTwips nX = aGrid.Left() + nGrid *
//STRIP001                                 ( ( aInter.Left() - aGrid.Left() )/ nGrid );
//STRIP001                     if( nX < aInter.Left() )
//STRIP001                         nX += nGrid;
//STRIP001                     SwTwips nGridRight = aGrid.Left() + aGrid.Width();
//STRIP001                     BOOL bLeft = aGrid.Left() >= aInter.Left();
//STRIP001                     BOOL bRight = nGridRight <= nRight;
//STRIP001                     BOOL bBorder = bLeft || bRight;
//STRIP001                     while( nY < aInter.Top() )
//STRIP001                     {
//STRIP001                         aTmp.Pos().Y() = nY;
//STRIP001                         if( bGrid )
//STRIP001                         {
//STRIP001                             nY += nGrid;
//STRIP001                             SwTwips nPosY = Max( aInter.Top(), aTmp.Pos().Y() );
//STRIP001                             SwTwips nHeight = Min(nBottom, nY ) - nPosY;
//STRIP001                             if( nHeight )
//STRIP001                             {
//STRIP001                                 if( bCell )
//STRIP001                                 {
//STRIP001                                     SwRect aVert( Point( nX, nPosY ),
//STRIP001                                                 Size( 1, nHeight ) );
//STRIP001                                     while( aVert.Left() <= nRight )
//STRIP001                                     {
//STRIP001                                         PaintBorderLine(rRect,aVert,this,pCol);
//STRIP001                                         aVert.Pos().X() += nGrid;
//STRIP001                                     }
//STRIP001                                 }
//STRIP001                                 else if ( bBorder )
//STRIP001                                 {
//STRIP001                                     SwRect aVert( Point( aGrid.Left(), nPosY ),
//STRIP001                                                 Size( 1, nHeight ) );
//STRIP001                                     if( bLeft )
//STRIP001                                         PaintBorderLine(rRect,aVert,this,pCol);
//STRIP001                                     if( bRight )
//STRIP001                                     {
//STRIP001                                         aVert.Pos().X() = nGridRight;
//STRIP001                                         PaintBorderLine(rRect,aVert,this,pCol);
//STRIP001                                     }
//STRIP001                                 }
//STRIP001                             }
//STRIP001                         }
//STRIP001                         else
//STRIP001                         {
//STRIP001                             nY += nRuby;
//STRIP001                             if( bBorder )
//STRIP001                             {
//STRIP001                                 SwTwips nPos = Max(aInter.Top(),aTmp.Pos().Y());
//STRIP001                                 SwTwips nH = Min( nBottom, nY ) - nPos;
//STRIP001                                 SwRect aVert( Point( aGrid.Left(), nPos ),
//STRIP001                                             Size( 1, nH ) );
//STRIP001                                 if( nH > 0 )
//STRIP001                                 {
//STRIP001                                     if( bLeft )
//STRIP001                                         PaintBorderLine(rRect,aVert,this,pCol);
//STRIP001                                     if( bRight )
//STRIP001                                     {
//STRIP001                                         aVert.Pos().X() = nGridRight;
//STRIP001                                         PaintBorderLine(rRect,aVert,this,pCol);
//STRIP001                                     }
//STRIP001                                 }
//STRIP001                             }
//STRIP001                         }
//STRIP001                         bGrid = !bGrid;
//STRIP001                     }
//STRIP001                     while( nY <= nBottom )
//STRIP001                     {
//STRIP001                         aTmp.Pos().Y() = nY;
//STRIP001                         PaintBorderLine( rRect, aTmp, this, pCol);
//STRIP001                         if( bGrid )
//STRIP001                         {
//STRIP001                             nY += nGrid;
//STRIP001                             SwTwips nHeight = Min(nBottom, nY) - aTmp.Pos().Y();
//STRIP001                             if( nHeight )
//STRIP001                             {
//STRIP001                                 if( bCell )
//STRIP001                                 {
//STRIP001                                     SwRect aVert( Point( nX, aTmp.Pos().Y() ),
//STRIP001                                                 Size( 1, nHeight ) );
//STRIP001                                     while( aVert.Left() <= nRight )
//STRIP001                                     {
//STRIP001                                         PaintBorderLine( rRect, aVert, this, pCol);
//STRIP001                                         aVert.Pos().X() += nGrid;
//STRIP001                                     }
//STRIP001                                 }
//STRIP001                                 else if( bBorder )
//STRIP001                                 {
//STRIP001                                     SwRect aVert( Point( aGrid.Left(),
//STRIP001                                         aTmp.Pos().Y() ), Size( 1, nHeight ) );
//STRIP001                                     if( bLeft )
//STRIP001                                         PaintBorderLine(rRect,aVert,this,pCol);
//STRIP001                                     if( bRight )
//STRIP001                                     {
//STRIP001                                         aVert.Pos().X() = nGridRight;
//STRIP001                                         PaintBorderLine(rRect,aVert,this,pCol);
//STRIP001                                     }
//STRIP001                                 }
//STRIP001                             }
//STRIP001                         }
//STRIP001                         else
//STRIP001                         {
//STRIP001                             nY += nRuby;
//STRIP001                             if( bBorder )
//STRIP001                             {
//STRIP001                                 SwTwips nPos = Max(aInter.Top(),aTmp.Pos().Y());
//STRIP001                                 SwTwips nH = Min( nBottom, nY ) - nPos;
//STRIP001                                 SwRect aVert( Point( aGrid.Left(), nPos ),
//STRIP001                                             Size( 1, nH ) );
//STRIP001                                 if( nH > 0 )
//STRIP001                                 {
//STRIP001                                     if( bLeft )
//STRIP001                                         PaintBorderLine(rRect,aVert,this,pCol);
//STRIP001                                     if( bRight )
//STRIP001                                     {
//STRIP001                                         aVert.Pos().X() = nGridRight;
//STRIP001                                         PaintBorderLine(rRect,aVert,this,pCol);
//STRIP001                                     }
//STRIP001                                 }
//STRIP001                             }
//STRIP001                         }
//STRIP001                         bGrid = !bGrid;
//STRIP001                     }
//STRIP001                 }
//STRIP001             }
//STRIP001         }
//STRIP001     }
//STRIP001 }

/** paint margin area of a page

    OD 20.11.2002 for #104598#:
    implement paint of margin area; margin area will be painted for a
    view shell with a window and if the document is not in online layout.

    @author OD

    @param _rOutputRect
    input parameter - constant instance reference of the rectangle, for
    which an output has to be generated.

    @param _pViewShell
    input parameter - instance of the view shell, on which the output
    has to be generated.
*/
//STRIP001 void SwPageFrm::PaintMarginArea( const SwRect& _rOutputRect,
//STRIP001                                  ViewShell* _pViewShell ) const
//STRIP001 {
//STRIP001     if ( _pViewShell->GetWin() &&
//STRIP001          !_pViewShell->GetDoc()->IsBrowseMode()
//STRIP001        )
//STRIP001     {
//STRIP001         SwRect aPgPrtRect( Prt() );
//STRIP001         aPgPrtRect.Pos() += Frm().Pos();
//STRIP001         if ( !aPgPrtRect.IsInside( _rOutputRect ) )
//STRIP001         {
//STRIP001             SwRect aPgRect = Frm();
//STRIP001             aPgRect._Intersection( _rOutputRect );
//STRIP001             SwRegionRects aPgRegion( aPgRect );
//STRIP001             aPgRegion -= aPgPrtRect;
//STRIP001             const SwPageFrm* pPage = static_cast<const SwPageFrm*>(this);
//STRIP001             if ( pPage->GetSortedObjs() )
//STRIP001                 ::lcl_SubtractFlys( this, pPage, aPgRect, aPgRegion );
//STRIP001             if ( aPgRegion.Count() )
//STRIP001             {
//STRIP001                 OutputDevice *pOut = _pViewShell->GetOut();
//STRIP001                 if ( pOut->GetFillColor() != aGlobalRetoucheColor )
//STRIP001                     pOut->SetFillColor( aGlobalRetoucheColor );
//STRIP001                 for ( USHORT i = 0; i < aPgRegion.Count(); ++i )
//STRIP001                 {
//STRIP001                     if ( 1 < aPgRegion.Count() )
//STRIP001                     {
//STRIP001                         ::SwAlignRect( aPgRegion[i], pGlobalShell );
//STRIP001                         if( !aPgRegion[i].HasArea() )
//STRIP001                             continue;
//STRIP001                     }
//STRIP001                     pOut->DrawRect( aPgRegion[i].SVRect() );
//STRIP001                 }
//STRIP001             }
//STRIP001         }
//STRIP001     }
//STRIP001 }

// ----------------------------------------------------------------------
//
// const SwPageFrm::mnBorderPxWidth, const SwPageFrm::mnShadowPxWidth
// SwPageFrm::GetBorderRect (..), SwPageFrm::GetRightShadowRect(..),
// SwPageFrm::GetBottomShadowRect(..),
// SwPageFrm::PaintBorderAndShadow(..),
// SwPageFrm::GetBorderAndShadowBoundRect(..)
//
// OD 12.02.2003 for #i9719# and #105645#
// ----------------------------------------------------------------------

/*N*/ const sal_Int8 SwPageFrm::mnBorderPxWidth = 1;
/*N*/ const sal_Int8 SwPageFrm::mnShadowPxWidth = 2;

/** determine rectangle for page border

    OD 12.02.2003 for #i9719# and #105645#

    @author OD
*/
//STRIP001 void SwPageFrm::GetBorderRect( const SwRect& _rPageRect,
//STRIP001                                ViewShell*    _pViewShell,
//STRIP001                                SwRect& _orBorderRect ) const
//STRIP001 {
//STRIP001     SwRect aAlignedPageRect( _rPageRect );
//STRIP001     SwAlignRect( aAlignedPageRect, _pViewShell );
//STRIP001     Rectangle aBorderPxRect =
//STRIP001             _pViewShell->GetOut()->LogicToPixel( aAlignedPageRect.SVRect() );
//STRIP001
//STRIP001     aBorderPxRect.Left() = aBorderPxRect.Left() - mnBorderPxWidth;
//STRIP001     aBorderPxRect.Top() = aBorderPxRect.Top() - mnBorderPxWidth;
//STRIP001     aBorderPxRect.Right() = aBorderPxRect.Right() + mnBorderPxWidth;
//STRIP001     aBorderPxRect.Bottom() = aBorderPxRect.Bottom() + mnBorderPxWidth;
//STRIP001
//STRIP001     _orBorderRect =
//STRIP001             SwRect( _pViewShell->GetOut()->PixelToLogic( aBorderPxRect ) );
//STRIP001 }

/** determine rectangle for right page shadow

    OD 12.02.2003 for #i9719# and #105645#

    @author OD
*/
//STRIP001 void SwPageFrm::GetRightShadowRect( const SwRect& _rPageRect,
//STRIP001                                     ViewShell*    _pViewShell,
//STRIP001                                     SwRect&       _orRightShadowRect ) const
//STRIP001 {
//STRIP001     SwRect aAlignedPageRect( _rPageRect );
//STRIP001     SwAlignRect( aAlignedPageRect, _pViewShell );
//STRIP001     Rectangle aPagePxRect =
//STRIP001             _pViewShell->GetOut()->LogicToPixel( aAlignedPageRect.SVRect() );
//STRIP001
//STRIP001     Rectangle aRightShadowPxRect(
//STRIP001                     aPagePxRect.Right() + mnShadowPxWidth,
//STRIP001                     aPagePxRect.Top() + 1,
//STRIP001                     aPagePxRect.Right() + mnBorderPxWidth + mnShadowPxWidth,
//STRIP001                     aPagePxRect.Bottom() + mnBorderPxWidth + mnShadowPxWidth );
//STRIP001
//STRIP001     _orRightShadowRect =
//STRIP001             SwRect( _pViewShell->GetOut()->PixelToLogic( aRightShadowPxRect ) );
//STRIP001 }

/** determine rectangle for bottom page shadow

    OD 12.02.2003 for #i9719# and #105645#

    @author OD
*/
//STRIP001 void SwPageFrm::GetBottomShadowRect( const SwRect& _rPageRect,
//STRIP001                                      ViewShell*    _pViewShell,
//STRIP001                                      SwRect&       _orBottomShadowRect ) const
//STRIP001 {
//STRIP001     SwRect aAlignedPageRect( _rPageRect );
//STRIP001     SwAlignRect( aAlignedPageRect, _pViewShell );
//STRIP001     Rectangle aPagePxRect =
//STRIP001             _pViewShell->GetOut()->LogicToPixel( aAlignedPageRect.SVRect() );
//STRIP001
//STRIP001     Rectangle aBottomShadowPxRect(
//STRIP001                     aPagePxRect.Left() + 1,
//STRIP001                     aPagePxRect.Bottom() + mnShadowPxWidth,
//STRIP001                     aPagePxRect.Right() + mnBorderPxWidth + mnShadowPxWidth,
//STRIP001                     aPagePxRect.Bottom() + mnBorderPxWidth + mnShadowPxWidth );
//STRIP001
//STRIP001     _orBottomShadowRect =
//STRIP001             SwRect( _pViewShell->GetOut()->PixelToLogic( aBottomShadowPxRect ) );
//STRIP001 }

/** paint page border and shadow

    OD 12.02.2003 for #i9719# and #105645#
    implement paint of page border and shadow

    @author OD
*/
//STRIP001 void SwPageFrm::PaintBorderAndShadow( const SwRect& _rPageRect,
//STRIP001                                       ViewShell*    _pViewShell ) const
//STRIP001 {
//STRIP001     // get color for page border and shadow paint
//STRIP001     const Color& rColor = SwViewOption::GetFontColor();
//STRIP001
//STRIP001     // save current fill and line color of output device
//STRIP001     Color aFill( _pViewShell->GetOut()->GetFillColor() );
//STRIP001     Color aLine( _pViewShell->GetOut()->GetLineColor() );
//STRIP001
//STRIP001     // paint page border
//STRIP001     _pViewShell->GetOut()->SetFillColor(); // OD 20.02.2003 #107369# - no fill color
//STRIP001     _pViewShell->GetOut()->SetLineColor( rColor );
//STRIP001     SwRect aPaintRect;
//STRIP001     GetBorderRect( _rPageRect, _pViewShell, aPaintRect );
//STRIP001     _pViewShell->GetOut()->DrawRect( aPaintRect.SVRect() );
//STRIP001
//STRIP001     // paint shadow
//STRIP001     _pViewShell->GetOut()->SetFillColor( rColor );
//STRIP001     GetRightShadowRect( _rPageRect, _pViewShell, aPaintRect );
//STRIP001     _pViewShell->GetOut()->DrawRect( aPaintRect.SVRect() );
//STRIP001     GetBottomShadowRect( _rPageRect, _pViewShell, aPaintRect );
//STRIP001     _pViewShell->GetOut()->DrawRect( aPaintRect.SVRect() );
//STRIP001
//STRIP001     _pViewShell->GetOut()->SetFillColor( aFill );
//STRIP001     _pViewShell->GetOut()->SetLineColor( aLine );
//STRIP001
//STRIP001 }

/** get bound rectangle of border and shadow for repaints

    OD 12.02.2003 for #i9719# and #105645#

    author OD
*/
/*N*/ void SwPageFrm::GetBorderAndShadowBoundRect(
/*N*/                                 const SwRect& _rPageRect,
/*N*/                                 ViewShell*    _pViewShell,
/*N*/                                 SwRect& _orBorderAndShadowBoundRect ) const
/*N*/ {DBG_ASSERT(0, "STRIP");//STRIP001
//STRIP001     SwRect aTmpRect;
//STRIP001     GetBorderRect( _rPageRect, _pViewShell, _orBorderAndShadowBoundRect );
//STRIP001     GetRightShadowRect( _rPageRect, _pViewShell, aTmpRect );
//STRIP001     _orBorderAndShadowBoundRect.Union( aTmpRect );
//STRIP001     GetBottomShadowRect( _rPageRect, _pViewShell, aTmpRect );
//STRIP001     _orBorderAndShadowBoundRect.Union( aTmpRect );
/*N*/ }

/*************************************************************************
|*
|*  SwFrm::PaintBaBo()
|*
|*  Ersterstellung      MA 22. Oct. 93
|*  Letzte Aenderung    MA 19. Jun. 96
|*
|*************************************************************************/

//STRIP001 void SwFrm::PaintBaBo( const SwRect& rRect, const SwPageFrm *pPage,
//STRIP001                     const BOOL bLowerBorder ) const
//STRIP001 {
//STRIP001  if ( !pPage )
//STRIP001      pPage = FindPageFrm();
//STRIP001
//STRIP001  OutputDevice *pOut = pGlobalShell->GetOut();
//STRIP001  pOut->Push( PUSH_FILLCOLOR );
//STRIP001
//STRIP001  SwBorderAttrAccess aAccess( SwFrm::GetCache(), (SwFrm*)this );
//STRIP001  const SwBorderAttrs &rAttrs = *aAccess.Get();
//STRIP001
//STRIP001     // OD 20.11.2002 #104598# - take care of page margin area
//STRIP001     // Note: code move from <SwFrm::PaintBackground(..)> to new method
//STRIP001     // <SwPageFrm::Paintmargin(..)>.
//STRIP001     if ( IsPageFrm() )
//STRIP001     {
//STRIP001         static_cast<const SwPageFrm*>(this)->PaintMarginArea( rRect, pGlobalShell );
//STRIP001     }
//STRIP001
//STRIP001     // OD 06.08.2002 #99657# - paint border before painting background
//STRIP001     // paint grid for page frame and paint border
//STRIP001     {
//STRIP001         SwRect aRect( rRect );
//STRIP001         if( IsPageFrm() )
//STRIP001             ((SwPageFrm*)this)->PaintGrid( pOut, aRect );
//STRIP001         PaintBorder( aRect, pPage, rAttrs );
//STRIP001     }
//STRIP001
//STRIP001     // paint background
//STRIP001     {
//STRIP001         PaintBackground( rRect, pPage, rAttrs, FALSE, bLowerBorder );
//STRIP001     }
//STRIP001
//STRIP001  pOut->Pop();
//STRIP001 }

/*************************************************************************
|*
|*  SwFrm::PaintBackground()
|*
|*  Ersterstellung      MA 04. Jan. 93
|*  Letzte Aenderung    MA 06. Feb. 97
|*
|*************************************************************************/
/// OD 05.09.2002 #102912#
/// Do not paint background for fly frames without a background brush by
/// calling <PaintBaBo> at the page or at the fly frame its anchored
//STRIP001 void SwFrm::PaintBackground( const SwRect &rRect, const SwPageFrm *pPage,
//STRIP001                           const SwBorderAttrs & rAttrs,
//STRIP001                           const BOOL bLowerMode,
//STRIP001                           const BOOL bLowerBorder ) const
//STRIP001 {
//STRIP001     // OD 20.01.2003 #i1837# - no paint of table background, if corresponding
//STRIP001     // option is *not* set.
//STRIP001     if( IsTabFrm() &&
//STRIP001         !pGlobalShell->GetViewOptions()->IsTable() )
//STRIP001     {
//STRIP001         return;
//STRIP001     }
//STRIP001
//STRIP001     ViewShell *pSh = pGlobalShell;
//STRIP001  const FASTBOOL bWin = pSh->GetWin() ? TRUE : FALSE;
//STRIP001  const SvxBrushItem* pItem;
//STRIP001     /// OD 05.09.2002 #102912#
//STRIP001     /// temporary background brush for a fly frame without a background brush
//STRIP001     SvxBrushItem* pTmpBackBrush = 0;
//STRIP001     const Color* pCol;
//STRIP001  SwRect aOrigBackRect;
//STRIP001  const FASTBOOL bPageFrm = IsPageFrm();
//STRIP001  FASTBOOL bLowMode = TRUE;
//STRIP001
//STRIP001     FASTBOOL bBack = GetBackgroundBrush( pItem, pCol, aOrigBackRect, bLowerMode );
//STRIP001     //- Ausgabe wenn ein eigener Hintergrund mitgebracht wird.
//STRIP001     bool bNoFlyBackground = !bFlyMetafile && !bBack && IsFlyFrm();
//STRIP001     if ( bNoFlyBackground )
//STRIP001     {
//STRIP001         // OD 05.09.2002 #102912# - Fly frame has no background.
//STRIP001         // Try to find background brush at parents, if previous call of
//STRIP001         // <GetBackgroundBrush> disabled this option with the parameter <bLowerMode>
//STRIP001         if ( bLowerMode )
//STRIP001         {
//STRIP001             bBack = GetBackgroundBrush( pItem, pCol, aOrigBackRect, false );
//STRIP001         }
//STRIP001         // If still no background found for the fly frame, initialize the
//STRIP001         // background brush <pItem> with global retouche color and set <bBack>
//STRIP001         // to TRUE, that fly frame will paint its background using this color.
//STRIP001         if ( !bBack )
//STRIP001         {
//STRIP001             // OD 10.01.2003 #i6467# - on print output, pdf output and
//STRIP001             // in embedded mode not editing color COL_WHITE is used instead of
//STRIP001             // the global retouche color.
//STRIP001             if ( pSh->GetOut()->GetOutDevType() == OUTDEV_PRINTER ||
//STRIP001                  pSh->GetViewOptions()->IsPDFExport() ||
//STRIP001                  ( pSh->GetDoc()->GetDocShell()->GetCreateMode() == SFX_CREATE_MODE_EMBEDDED &&
//STRIP001                    !pSh->GetDoc()->GetDocShell()->GetProtocol().IsInPlaceActive()
//STRIP001                  )
//STRIP001                )
//STRIP001             {
//STRIP001                 pTmpBackBrush = new SvxBrushItem( Color( COL_WHITE ) );
//STRIP001             }
//STRIP001             else
//STRIP001             {
//STRIP001                 pTmpBackBrush = new SvxBrushItem( aGlobalRetoucheColor );
//STRIP001             }
//STRIP001             pItem = pTmpBackBrush;
//STRIP001             bBack = true;
//STRIP001         }
//STRIP001     }
//STRIP001
//STRIP001  SwRect aPaintRect( Frm() );
//STRIP001  if( IsTxtFrm() || IsSctFrm() )
//STRIP001      aPaintRect = UnionFrm( TRUE );
//STRIP001
//STRIP001  if ( aPaintRect.IsOver( rRect ) )
//STRIP001  {
//STRIP001         if ( bBack || bPageFrm || !bLowerMode )
//STRIP001         {
//STRIP001             const FASTBOOL bBrowse = pSh->GetDoc()->IsBrowseMode();
//STRIP001
//STRIP001             SwRect aRect;
//STRIP001             if ( (bPageFrm && bBrowse) ||
//STRIP001                  (IsTxtFrm() && Prt().SSize() == Frm().SSize()) )
//STRIP001             {
//STRIP001                 aRect = Frm();
//STRIP001                 ::SwAlignRect( aRect, pGlobalShell );
//STRIP001             }
//STRIP001             else
//STRIP001             {
//STRIP001                 ::lcl_CalcBorderRect( aRect, this, rAttrs, FALSE );
//STRIP001                 if ( (IsTxtFrm() || IsTabFrm()) && GetPrev() )
//STRIP001                 {
//STRIP001                     if ( GetPrev()->GetAttrSet()->GetBackground() ==
//STRIP001                          GetAttrSet()->GetBackground() )
//STRIP001                     {
//STRIP001                         aRect.Top( Frm().Top() );
//STRIP001                     }
//STRIP001                 }
//STRIP001             }
//STRIP001             aRect.Intersection( rRect );
//STRIP001
//STRIP001             OutputDevice *pOut = pSh->GetOut();
//STRIP001
//STRIP001             if ( aRect.HasArea() )
//STRIP001             {
//STRIP001                 SvxBrushItem* pNewItem;
//STRIP001                 SwRegionRects aRegion( aRect );
//STRIP001                 if( pCol )
//STRIP001                 {
//STRIP001                     pNewItem = new SvxBrushItem( *pCol );
//STRIP001                     pItem = pNewItem;
//STRIP001                 }
//STRIP001                 if ( pPage->GetSortedObjs() )
//STRIP001                     ::lcl_SubtractFlys( this, pPage, aRect, aRegion );
//STRIP001
//STRIP001                 {
//STRIP001                     /// OD 06.08.2002 #99657# - determine, if background transparency
//STRIP001                     ///     have to be considered for drawing.
//STRIP001                     ///     --> Status Quo: background transparency have to be
//STRIP001                     ///        considered for fly frames
//STRIP001                     const sal_Bool bConsiderBackgroundTransparency = IsFlyFrm();
//STRIP001                     for ( USHORT i = 0; i < aRegion.Count(); ++i )
//STRIP001                     {
//STRIP001                         if ( 1 < aRegion.Count() )
//STRIP001                         {
//STRIP001                             ::SwAlignRect( aRegion[i], pGlobalShell );
//STRIP001                             if( !aRegion[i].HasArea() )
//STRIP001                                 continue;
//STRIP001                         }
//STRIP001                         /// OD 06.08.2002 #99657# - add 6th parameter to indicate, if
//STRIP001                         ///     background transparency have to be considered
//STRIP001                         ///     Set missing 5th parameter to the default value GRFNUM_NO
//STRIP001                         ///         - see declaration in /core/inc/frmtool.hxx.
//STRIP001                         ::DrawGraphic( pItem, pOut, aOrigBackRect, aRegion[i], GRFNUM_NO,
//STRIP001                                 bConsiderBackgroundTransparency );
//STRIP001                     }
//STRIP001                 }
//STRIP001                 if( pCol )
//STRIP001                     delete pNewItem;
//STRIP001             }
//STRIP001         }
//STRIP001         else
//STRIP001             bLowMode = bLowerMode ? TRUE : FALSE;
//STRIP001  }
//STRIP001
//STRIP001     /// OD 05.09.2002 #102912#
//STRIP001     /// delete temporary background brush.
//STRIP001     delete pTmpBackBrush;
//STRIP001
//STRIP001     //Jetzt noch Lower und dessen Nachbarn.
//STRIP001  //Wenn ein Frn dabei die Kette verlaesst also nicht mehr Lower von mir ist
//STRIP001  //so hoert der Spass auf.
//STRIP001  const SwFrm *pFrm = GetLower();
//STRIP001     if ( pFrm )
//STRIP001  {
//STRIP001      SwRect aFrmRect;
//STRIP001      SwRect aRect( PaintArea() );
//STRIP001      aRect._Intersection( rRect );
//STRIP001      SwRect aBorderRect( aRect );
//STRIP001         SwShortCut aShortCut( *pFrm, aBorderRect );
//STRIP001      do
//STRIP001      {   if ( pProgress )
//STRIP001              pProgress->Reschedule();
//STRIP001
//STRIP001          aFrmRect = pFrm->PaintArea();
//STRIP001          if ( aFrmRect.IsOver( aBorderRect ) )
//STRIP001          {
//STRIP001              SwBorderAttrAccess aAccess( SwFrm::GetCache(), (SwFrm*)pFrm );
//STRIP001              const SwBorderAttrs &rAttrs = *aAccess.Get();
//STRIP001                 /// OD 06.08.2002 #99657# - paint border before painting background
//STRIP001                 if ( bLowerBorder )
//STRIP001                     pFrm->PaintBorder( aBorderRect, pPage, rAttrs );
//STRIP001              if ( ( pFrm->IsLayoutFrm() && bLowerBorder ) ||
//STRIP001                   aFrmRect.IsOver( aRect ) )
//STRIP001                  pFrm->PaintBackground( aRect, pPage, rAttrs, bLowMode,
//STRIP001                                         bLowerBorder );
//STRIP001          }
//STRIP001          pFrm = pFrm->GetNext();
//STRIP001      } while ( pFrm && pFrm->GetUpper() == this &&
//STRIP001                   !aShortCut.Stop( aFrmRect ) );
//STRIP001  }
//STRIP001 }

/*************************************************************************
|*
|*  SwPageFrm::RefreshSubsidiary()
|*
|*  Beschreibung        Erneuert alle Hilfslinien der Seite.
|*  Ersterstellung      MA 04. Nov. 92
|*  Letzte Aenderung    MA 10. May. 95
|*
|*************************************************************************/

//STRIP001 void SwPageFrm::RefreshSubsidiary( const SwRect &rRect ) const
//STRIP001 {
//STRIP001     if ( IS_SUBS || IS_SUBS_TABLE || IS_SUBS_SECTION || IS_SUBS_FLYS )
//STRIP001  {
//STRIP001      SwRect aRect( rRect );
//STRIP001         // OD 18.02.2003 #104989# - Not necessary and incorrect alignment of
//STRIP001         // the output rectangle.
//STRIP001         //::SwAlignRect( aRect, pGlobalShell );
//STRIP001      if ( aRect.HasArea() )
//STRIP001      {
//STRIP001          //Beim Paint ueber die Root wird das Array von dort gesteuert.
//STRIP001          //Anderfalls kuemmern wir uns selbst darum.
//STRIP001          FASTBOOL bDelSubs = FALSE;
//STRIP001          if ( !pSubsLines )
//STRIP001          {
//STRIP001              pSubsLines = new SwSubsRects;
//STRIP001                 // OD 20.12.2002 #106318# - create container for special subsidiary lines
//STRIP001                 pSpecSubsLines = new SwSubsRects;
//STRIP001                 bDelSubs = TRUE;
//STRIP001          }
//STRIP001
//STRIP001          RefreshLaySubsidiary( this, aRect );
//STRIP001
//STRIP001             if ( bDelSubs )
//STRIP001          {
//STRIP001                 // OD 20.12.2002 #106318# - paint special subsidiary lines
//STRIP001                 // and delete its container
//STRIP001                 pSpecSubsLines->PaintSubsidiary( pGlobalShell->GetOut(), NULL );
//STRIP001                 DELETEZ( pSpecSubsLines );
//STRIP001
//STRIP001                 pSubsLines->PaintSubsidiary( pGlobalShell->GetOut(), pLines );
//STRIP001              DELETEZ( pSubsLines );
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 }

/*************************************************************************
|*
|*  SwLayoutFrm::RefreshLaySubsidiary()
|*
|*  Ersterstellung      MA 04. Nov. 92
|*  Letzte Aenderung    MA 22. Jan. 95
|*
|*************************************************************************/
//STRIP001 void SwLayoutFrm::RefreshLaySubsidiary( const SwPageFrm *pPage,
//STRIP001                                         const SwRect &rRect ) const
//STRIP001 {
//STRIP001  const FASTBOOL bNoLowerColumn = !Lower() || !Lower()->IsColumnFrm();
//STRIP001  const FASTBOOL bSubsOpt   = IS_SUBS;
//STRIP001  const FASTBOOL bSubsTable = ((GetType() & (FRM_ROW | FRM_CELL)) && IS_SUBS_TABLE);
//STRIP001  const FASTBOOL bSubsOther = (GetType() & (FRM_HEADER | FRM_FOOTER | FRM_FTN )) && bSubsOpt;
//STRIP001  const FASTBOOL bSubsSect  = IsSctFrm() &&
//STRIP001                              bNoLowerColumn &&
//STRIP001                              IS_SUBS_SECTION;
//STRIP001     const FASTBOOL bSubsFly   = IS_SUBS_FLYS &&
//STRIP001                                 (GetType() & FRM_FLY) &&
//STRIP001                                 bNoLowerColumn &&
//STRIP001                              (!Lower() || !Lower()->IsNoTxtFrm() ||
//STRIP001                               !((SwNoTxtFrm*)Lower())->HasAnimation());
//STRIP001  FASTBOOL bSubsBody = FALSE;
//STRIP001  if ( GetType() & FRM_BODY )
//STRIP001  {
//STRIP001      if ( IsPageBodyFrm() )
//STRIP001          bSubsBody = bSubsOpt && bNoLowerColumn;                                 //nur ohne Spalten
//STRIP001         else    //Spaltenbody
//STRIP001      {
//STRIP001          if ( GetUpper()->GetUpper()->IsSctFrm() )
//STRIP001              bSubsBody = IS_SUBS_SECTION;
//STRIP001          else
//STRIP001              bSubsBody = bSubsOpt;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if ( bSubsOther || bSubsSect  || bSubsBody || bSubsTable || bSubsFly )
//STRIP001      PaintSubsidiaryLines( pPage, rRect );
//STRIP001
//STRIP001     const SwFrm *pLow = Lower();
//STRIP001     if( !pLow )
//STRIP001         return;
//STRIP001     SwShortCut aShortCut( *pLow, rRect );
//STRIP001     while( pLow && !aShortCut.Stop( pLow->Frm() ) )
//STRIP001     {
//STRIP001         if ( pLow->Frm().IsOver( rRect ) && pLow->Frm().HasArea() )
//STRIP001         {
//STRIP001             if ( pLow->IsLayoutFrm() )
//STRIP001                 ((const SwLayoutFrm*)pLow)->RefreshLaySubsidiary( pPage, rRect);
//STRIP001             else if ( pLow->GetDrawObjs() )
//STRIP001             {
//STRIP001                 const SwDrawObjs &rObjs = *pLow->GetDrawObjs();
//STRIP001                 for ( USHORT i = 0; i < rObjs.Count(); ++i )
//STRIP001                 {
//STRIP001                     SdrObject *pO = rObjs[i];
//STRIP001                     if ( pO->IsWriterFlyFrame() )
//STRIP001                     {
//STRIP001                         const SwFlyFrm *pFly = ((SwVirtFlyDrawObj*)pO)->GetFlyFrm();
//STRIP001                         if ( pFly->IsFlyInCntFrm() && pFly->Frm().IsOver( rRect ) )
//STRIP001                         {
//STRIP001                             if ( !pFly->Lower() || !pFly->Lower()->IsNoTxtFrm() ||
//STRIP001                                  !((SwNoTxtFrm*)pFly->Lower())->HasAnimation())
//STRIP001                                 pFly->RefreshLaySubsidiary( pPage, rRect );
//STRIP001                         }
//STRIP001                     }
//STRIP001                 }
//STRIP001             }
//STRIP001         }
//STRIP001         pLow = pLow->GetNext();
//STRIP001     }
//STRIP001 }

/*************************************************************************
|*
|*  SwLayoutFrm::PaintSubsidiaryLines()
|*
|*  Beschreibung        Hilfslinien um die PrtAreas malen
|*      Nur die LayoutFrm's die direkt Cntnt enthalten.
|*  Ersterstellung      MA 21. May. 92
|*  Letzte Aenderung    MA 22. Jan. 95
|*
|*************************************************************************/

//Malt die angegebene Linie, achtet darauf, dass keine Flys uebermalt werden.
//STRIP001 PointPtr pX = &Point::nA;
//STRIP001 PointPtr pY = &Point::nB;
//STRIP001 SizePtr pWidth = &Size::nA;
//STRIP001 SizePtr pHeight = &Size::nB;

// OD 18.11.2002 #99672# - new parameter <_pSubsLines>
//STRIP001 void MA_FASTCALL lcl_RefreshLine( const SwLayoutFrm *pLay,
//STRIP001                                   const SwPageFrm *pPage,
//STRIP001                                   const Point &rP1,
//STRIP001                                   const Point &rP2,
//STRIP001                                   const BYTE nSubColor,
//STRIP001                                   SwLineRects* _pSubsLines )
//STRIP001 {
//STRIP001  //In welche Richtung gehts? Kann nur Horizontal oder Vertikal sein.
//STRIP001  ASSERT( ((rP1.X() == rP2.X()) || (rP1.Y() == rP2.Y())),
//STRIP001          "Schraege Hilfslinien sind nicht erlaubt." );
//STRIP001     const PTPTR pDirPt = rP1.X() == rP2.X() ? pY : pX;
//STRIP001     const PTPTR pOthPt = pDirPt == pX ? pY : pX;
//STRIP001     const SIZEPTR pDirSz = pDirPt == pX ? pWidth : pHeight;
//STRIP001     const SIZEPTR pOthSz = pDirSz == pWidth ? pHeight : pWidth;
//STRIP001  Point aP1( rP1 ),
//STRIP001        aP2( rP2 );
//STRIP001
//STRIP001  while ( aP1.*pDirPt < aP2.*pDirPt )
//STRIP001  {   //Der Startpunkt wird jetzt, falls er in einem Fly sitzt, direkt
//STRIP001      //hinter den Fly gesetzt.
//STRIP001      //Wenn der Endpunkt in einem Fly sitzt oder zwischen Start und Endpunkt
//STRIP001      //ein Fly sitzt, so wird der Endpunkt eben an den Start herangezogen.
//STRIP001      //Auf diese art und weise wird eine Portion nach der anderen
//STRIP001      //ausgegeben.
//STRIP001
//STRIP001      //Wenn ich selbst ein Fly bin, weiche ich nur denjenigen Flys aus,
//STRIP001      //die 'ueber' mir sitzen; d.h. die in dem Array hinter mir stehen.
//STRIP001      //Auch wenn ich in einem Fly sitze oder in einem Fly im Fly usw. weiche
//STRIP001      //ich keinem dieser Flys aus.
//STRIP001      SwOrderIter aIter( pPage );
//STRIP001      const SwFlyFrm *pMyFly = pLay->FindFlyFrm();
//STRIP001      if ( pMyFly )
//STRIP001      {
//STRIP001          aIter.Current( pMyFly->GetVirtDrawObj() );
//STRIP001          while ( 0 != (pMyFly = pMyFly->GetAnchor()->FindFlyFrm()) )
//STRIP001          {
//STRIP001              if ( aIter()->GetOrdNum() > pMyFly->GetVirtDrawObj()->GetOrdNum() )
//STRIP001                  aIter.Current( pMyFly->GetVirtDrawObj() );
//STRIP001          }
//STRIP001      }
//STRIP001      else
//STRIP001          aIter.Bottom();
//STRIP001
//STRIP001      while ( aIter() )
//STRIP001      {
//STRIP001          const SwVirtFlyDrawObj *pObj = (SwVirtFlyDrawObj*)aIter();
//STRIP001          const SwFlyFrm *pFly = pObj ? pObj->GetFlyFrm() : 0;
//STRIP001
//STRIP001          //Mir selbst weiche ich natuerlich nicht aus. Auch wenn ich
//STRIP001          //_in_ dem Fly sitze weiche ich nicht aus.
//STRIP001          if ( !pFly || (pFly == pLay || pFly->IsAnLower( pLay )) )
//STRIP001             {
//STRIP001                 aIter.Next();
//STRIP001              continue;
//STRIP001          }
//STRIP001
//STRIP001             // OD 19.12.2002 #106318# - do *not* consider fly frames with
//STRIP001             // a transparent background.
//STRIP001             if ( pFly->IsBackgroundTransparent() )
//STRIP001             {
//STRIP001                 aIter.Next();
//STRIP001                 continue;
//STRIP001             }
//STRIP001
//STRIP001          //Sitzt das Obj auf der Linie
//STRIP001          const Rectangle &rBound = pObj->GetBoundRect();
//STRIP001          const Point aDrPt( rBound.TopLeft() );
//STRIP001          const Size  aDrSz( rBound.GetSize() );
//STRIP001          if ( rP1.*pOthPt >= aDrPt.*pOthPt &&
//STRIP001               rP1.*pOthPt <= (aDrPt.*pOthPt + aDrSz.*pOthSz) )
//STRIP001          {
//STRIP001              if ( aP1.*pDirPt >= aDrPt.*pDirPt &&
//STRIP001                   aP1.*pDirPt <= (aDrPt.*pDirPt + aDrSz.*pDirSz) )
//STRIP001                  aP1.*pDirPt = aDrPt.*pDirPt + aDrSz.*pDirSz;
//STRIP001
//STRIP001              if ( aP2.*pDirPt >= aDrPt.*pDirPt &&
//STRIP001                   aP1.*pDirPt < (aDrPt.*pDirPt - 1) )
//STRIP001                  aP2.*pDirPt = aDrPt.*pDirPt - 1;
//STRIP001          }
//STRIP001          aIter.Next();
//STRIP001      }
//STRIP001
//STRIP001      if ( aP1.*pDirPt < aP2.*pDirPt )
//STRIP001      {
//STRIP001          SwRect aRect( aP1, aP2 );
//STRIP001             // OD 18.11.2002 #99672# - use parameter <_pSubsLines> instead of
//STRIP001             // global variable <pSubsLines>.
//STRIP001             _pSubsLines->AddLineRect( aRect, 0, 0, nSubColor );
//STRIP001      }
//STRIP001      aP1 = aP2;
//STRIP001      aP1.*pDirPt += 1;
//STRIP001      aP2 = rP2;
//STRIP001  }
//STRIP001 }

//STRIP001 void SwLayoutFrm::PaintSubsidiaryLines( const SwPageFrm *pPage,
//STRIP001                                      const SwRect &rRect ) const
//STRIP001 {
//STRIP001     const bool bFlys = pPage->GetSortedObjs() ? true : false;
//STRIP001
//STRIP001     const bool bCell = IsCellFrm() ? true : false;
//STRIP001     // use frame area for cells
//STRIP001     // OD 13.02.2003 #i3662# - for section use also frame area
//STRIP001     const bool bUseFrmArea = bCell || IsSctFrm();
//STRIP001     SwRect aOriginal( bUseFrmArea ? Frm() : Prt() );
//STRIP001     if ( !bUseFrmArea )
//STRIP001         aOriginal.Pos() += Frm().Pos();
//STRIP001     // OD 13.02.2003 #i3662# - enlarge top of column body frame's printing area
//STRIP001     // in sections to top of section frame.
//STRIP001     const bool bColBodyInSection = IsBodyFrm() &&
//STRIP001                                    !IsPageBodyFrm() &&
//STRIP001                                    GetUpper()->GetUpper()->IsSctFrm();
//STRIP001     if ( bColBodyInSection )
//STRIP001     {
//STRIP001         aOriginal.Top( GetUpper()->GetUpper()->Frm().Top() );
//STRIP001     }
//STRIP001
//STRIP001     ::SwAlignRect( aOriginal, pGlobalShell );
//STRIP001
//STRIP001     if ( !aOriginal.IsOver( rRect ) )
//STRIP001      return;
//STRIP001
//STRIP001  SwRect aOut( aOriginal );
//STRIP001  aOut._Intersection( rRect );
//STRIP001     // OD 13.02.2003 #i3662# - do not intersect *enlarged* column body frame's
//STRIP001     // printing area with the paint area of the body frame. Otherwise enlargement
//STRIP001     // will get lost.
//STRIP001     if ( !bColBodyInSection )
//STRIP001     {
//STRIP001         aOut.Intersection( PaintArea() );
//STRIP001     }
//STRIP001
//STRIP001  const SwTwips nRight = aOut.Right();
//STRIP001  const SwTwips nBottom= aOut.Bottom();
//STRIP001
//STRIP001  const Point aRT( nRight, aOut.Top() );
//STRIP001  const Point aRB( nRight, nBottom );
//STRIP001  const Point aLB( aOut.Left(), nBottom );
//STRIP001
//STRIP001     BYTE nSubColor = ( bCell || IsRowFrm() ) ? SUBCOL_TAB :
//STRIP001                      ( IsInSct() ? SUBCOL_SECT :
//STRIP001                      ( IsInFly() ? SUBCOL_FLY : SUBCOL_PAGE ) );
//STRIP001
//STRIP001     // OD 05.11.2002 #102406# - body frames are responsible for page/column breaks.
//STRIP001     BOOL bBreak = FALSE;
//STRIP001     if ( IsBodyFrm() )
//STRIP001     {
//STRIP001         const SwCntntFrm *pCnt = ContainsCntnt();
//STRIP001         if ( pCnt )
//STRIP001         {
//STRIP001             // OD 05.11.2002 #102406# - adjust setting of <bBreak>.
//STRIP001             bBreak = pCnt->IsPageBreak( TRUE ) ||
//STRIP001                      ( IsColBodyFrm() && pCnt->IsColBreak( TRUE ) );
//STRIP001         }
//STRIP001     }
//STRIP001
//STRIP001     // OD 18.11.2002 #99672# - collect body, header, footer, footnote and section
//STRIP001     // sub-lines in <pSpecSubsLine> array.
//STRIP001     const bool bSpecialSublines = IsBodyFrm() || IsHeaderFrm() || IsFooterFrm() ||
//STRIP001                                   IsFtnFrm() || IsSctFrm();
//STRIP001     SwLineRects* pUsedSubsLines = bSpecialSublines ? pSpecSubsLines : pSubsLines;
//STRIP001
//STRIP001     // NOTE: for cell frames only left and right (horizontal layout) respectively
//STRIP001     //      top and bottom (vertical layout) lines painted.
//STRIP001     const bool bVert = IsVertical() ? true : false;
//STRIP001     if ( bFlys )
//STRIP001  {
//STRIP001         // OD 14.11.2002 #104822# - add control for drawing left and right lines
//STRIP001         if ( !bCell || !bVert )
//STRIP001         {
//STRIP001             if ( aOriginal.Left() == aOut.Left() )
//STRIP001                 ::lcl_RefreshLine( this, pPage, aOut.Pos(), aLB, nSubColor,
//STRIP001                                    pUsedSubsLines );
//STRIP001             // OD 14.11.2002 #104821# - in vertical layout set page/column break at right
//STRIP001             if ( aOriginal.Right() == nRight )
//STRIP001                 ::lcl_RefreshLine( this, pPage, aRT, aRB,
//STRIP001                                    (bBreak && bVert) ? SUBCOL_BREAK : nSubColor,
//STRIP001                                    pUsedSubsLines );
//STRIP001         }
//STRIP001         // OD 14.11.2002 #104822# - adjust control for drawing top and bottom lines
//STRIP001         if ( !bCell || bVert )
//STRIP001      {
//STRIP001          if ( aOriginal.Top() == aOut.Top() )
//STRIP001                 // OD 14.11.2002 #104821# - in horizontal layout set page/column break at top
//STRIP001              ::lcl_RefreshLine( this, pPage, aOut.Pos(), aRT,
//STRIP001                                    (bBreak && !bVert) ? SUBCOL_BREAK : nSubColor,
//STRIP001                                    pUsedSubsLines );
//STRIP001          if ( aOriginal.Bottom() == nBottom )
//STRIP001                 ::lcl_RefreshLine( this, pPage, aLB, aRB, nSubColor,
//STRIP001                                    pUsedSubsLines );
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001         // OD 14.11.2002 #104822# - add control for drawing left and right lines
//STRIP001         if ( !bCell || !IsVertical() )
//STRIP001         {
//STRIP001             if ( aOriginal.Left() == aOut.Left() )
//STRIP001             {
//STRIP001                 SwRect aRect( aOut.Pos(), aLB );
//STRIP001                 pUsedSubsLines->AddLineRect( aRect, 0, 0, nSubColor );
//STRIP001             }
//STRIP001             // OD 14.11.2002 #104821# - in vertical layout set page/column break at right
//STRIP001             if ( aOriginal.Right() == nRight )
//STRIP001             {
//STRIP001                 SwRect aRect( aRT, aRB );
//STRIP001                 pUsedSubsLines->AddLineRect( aRect, 0, 0,
//STRIP001                         (bBreak && bVert) ? SUBCOL_BREAK : nSubColor );
//STRIP001             }
//STRIP001         }
//STRIP001         // OD 14.11.2002 #104822# - adjust control for drawing top and bottom lines
//STRIP001         if ( !bCell || IsVertical() )
//STRIP001         {
//STRIP001          if ( aOriginal.Top() == aOut.Top() )
//STRIP001          {
//STRIP001                 // OD 14.11.2002 #104821# - in horizontal layout set page/column break at top
//STRIP001              SwRect aRect( aOut.Pos(), aRT );
//STRIP001                 pUsedSubsLines->AddLineRect( aRect, 0, 0,
//STRIP001                         (bBreak && !bVert) ? SUBCOL_BREAK : nSubColor );
//STRIP001          }
//STRIP001          if ( aOriginal.Bottom() == nBottom )
//STRIP001          {
//STRIP001              SwRect aRect( aLB, aRB );
//STRIP001                 pUsedSubsLines->AddLineRect( aRect, 0, 0, nSubColor );
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 }

/*************************************************************************
|*
|*  SwPageFrm::RefreshExtraData(), SwLayoutFrm::RefreshExtraData()
|*
|*  Beschreibung        Erneuert alle Extradaten (Zeilennummern usw) der Seite.
|*                      Grundsaetzlich sind nur diejenigen Objekte beruecksichtig,
|*                      die in die seitliche Ausdehnung des Rects ragen.
|*  Ersterstellung      MA 20. Jan. 98
|*  Letzte Aenderung    MA 18. Feb. 98
|*
|*************************************************************************/

//STRIP001 void SwPageFrm::RefreshExtraData( const SwRect &rRect ) const
//STRIP001 {
//STRIP001  const SwLineNumberInfo &rInfo = GetFmt()->GetDoc()->GetLineNumberInfo();
//STRIP001  FASTBOOL bLineInFly = rInfo.IsPaintLineNumbers() && rInfo.IsCountInFlys()
//STRIP001      || (SwHoriOrient)SW_MOD()->GetRedlineMarkPos() != HORI_NONE;
//STRIP001
//STRIP001  SwRect aRect( rRect );
//STRIP001  ::SwAlignRect( aRect, pGlobalShell );
//STRIP001  if ( aRect.HasArea() )
//STRIP001  {
//STRIP001      SwLayoutFrm::RefreshExtraData( aRect );
//STRIP001
//STRIP001      if ( bLineInFly && GetSortedObjs() )
//STRIP001          for ( USHORT i = 0; i < GetSortedObjs()->Count(); ++i )
//STRIP001          {
//STRIP001              SdrObject *pO = (*GetSortedObjs())[i];
//STRIP001              if ( pO->IsWriterFlyFrame() )
//STRIP001              {
//STRIP001                  const SwFlyFrm *pFly = ((SwVirtFlyDrawObj*)pO)->GetFlyFrm();
//STRIP001                  if ( pFly->Frm().Top() <= aRect.Bottom() &&
//STRIP001                       pFly->Frm().Bottom() >= aRect.Top() )
//STRIP001                      pFly->RefreshExtraData( aRect );
//STRIP001              }
//STRIP001          }
//STRIP001  }
//STRIP001 }

//STRIP001 void SwLayoutFrm::RefreshExtraData( const SwRect &rRect ) const
//STRIP001 {
//STRIP001
//STRIP001  const SwLineNumberInfo &rInfo = GetFmt()->GetDoc()->GetLineNumberInfo();
//STRIP001  FASTBOOL bLineInBody = rInfo.IsPaintLineNumbers(),
//STRIP001           bLineInFly  = bLineInBody && rInfo.IsCountInFlys(),
//STRIP001           bRedLine = (SwHoriOrient)SW_MOD()->GetRedlineMarkPos()!=HORI_NONE;
//STRIP001
//STRIP001  const SwCntntFrm *pCnt = ContainsCntnt();
//STRIP001  while ( pCnt && IsAnLower( pCnt ) )
//STRIP001  {
//STRIP001      if ( pCnt->IsTxtFrm() && ( bRedLine ||
//STRIP001           ( !pCnt->IsInTab() &&
//STRIP001             ((bLineInBody && pCnt->IsInDocBody()) ||
//STRIP001             (bLineInFly  && pCnt->IsInFly())) ) ) &&
//STRIP001           pCnt->Frm().Top() <= rRect.Bottom() &&
//STRIP001           pCnt->Frm().Bottom() >= rRect.Top() )
//STRIP001      {
//STRIP001          ((SwTxtFrm*)pCnt)->PaintExtraData( rRect );
//STRIP001      }
//STRIP001      if ( bLineInFly && pCnt->GetDrawObjs() )
//STRIP001          for ( USHORT i = 0; i < pCnt->GetDrawObjs()->Count(); ++i )
//STRIP001          {
//STRIP001              SdrObject *pO = (*pCnt->GetDrawObjs())[i];
//STRIP001              if ( pO->IsWriterFlyFrame() )
//STRIP001              {
//STRIP001                  const SwFlyFrm *pFly = ((SwVirtFlyDrawObj*)pO)->GetFlyFrm();
//STRIP001                  if ( pFly->IsFlyInCntFrm() &&
//STRIP001                       pFly->Frm().Top() <= rRect.Bottom() &&
//STRIP001                       pFly->Frm().Bottom() >= rRect.Top() )
//STRIP001                      pFly->RefreshExtraData( rRect );
//STRIP001              }
//STRIP001      }
//STRIP001      pCnt = pCnt->GetNextCntntFrm();
//STRIP001  }
//STRIP001 }

/** SwPageFrm::GetDrawBackgrdColor - for #102450#

    determine the color, that is respectively will be drawn as background
    for the page frame.
    Using existing method SwFrm::GetBackgroundBrush to determine the color
    that is set at the page frame respectively is parent. If none is found
    return the global retouche color

    @author OD

    @return Color
*/
//STRIP001 const Color& SwPageFrm::GetDrawBackgrdColor() const
//STRIP001 {
//STRIP001     const SvxBrushItem* pBrushItem;
//STRIP001     const Color* pDummyColor;
//STRIP001     SwRect aDummyRect;
//STRIP001     if ( GetBackgroundBrush( pBrushItem, pDummyColor, aDummyRect, true) )
//STRIP001         return pBrushItem->GetColor();
//STRIP001     else
//STRIP001         return aGlobalRetoucheColor;
//STRIP001 }


/*************************************************************************
|*
|*    SwFrm::Retouche
|*
|*    Beschreibung      Retouche fuer einen Bereich.
|*      Retouche wird nur dann durchgefuehrt, wenn der Frm der letzte seiner
|*      Kette ist. Der Gesamte Bereich des Upper unterhalb des Frm wird
|*      per PaintBackground gecleared.
|*    Ersterstellung    MA 13. Apr. 93
|*    Letzte Aenderung  MA 25. Jul. 96
|*
|*************************************************************************/

//STRIP001 void SwFrm::Retouche( const SwPageFrm * pPage, const SwRect &rRect ) const
//STRIP001 {
//STRIP001  if ( bFlyMetafile )
//STRIP001      return;
//STRIP001
//STRIP001  ASSERT( GetUpper(), "Retoucheversuch ohne Upper." );
//STRIP001  ASSERT( GetShell() && pGlobalShell->GetWin(), "Retouche auf dem Drucker?" );
//STRIP001
//STRIP001  SwRect aRetouche( GetUpper()->PaintArea() );
//STRIP001  aRetouche.Top( Frm().Top() + Frm().Height() );
//STRIP001  aRetouche.Intersection( pGlobalShell->VisArea() );
//STRIP001
//STRIP001  if ( aRetouche.HasArea() )
//STRIP001  {
//STRIP001      //Uebergebenes Rect ausparen. Dafuer brauchen wir leider eine Region
//STRIP001      //zum ausstanzen.
//STRIP001      SwRegionRects aRegion( aRetouche );
//STRIP001      aRegion -= rRect;
//STRIP001      ViewShell *pSh = GetShell();
//STRIP001      for ( USHORT i = 0; i < aRegion.Count(); ++i )
//STRIP001      {
//STRIP001          SwRect &rRetouche = aRegion[i];
//STRIP001
//STRIP001          GetUpper()->PaintBaBo( rRetouche, pPage, TRUE );
//STRIP001
//STRIP001          //Hoelle und Himmel muessen auch refreshed werden.
//STRIP001          //Um Rekursionen zu vermeiden muss mein Retouche Flag zuerst
//STRIP001          //zurueckgesetzt werden!
//STRIP001          ResetRetouche();
//STRIP001             SwRect aRetouchePart( rRetouche );
//STRIP001             if ( aRetouchePart.HasArea() )
//STRIP001             {
//STRIP001                 // OD 30.08.2002 #102450#
//STRIP001                 // determine background color of page for <PaintLayer> method
//STRIP001                 // calls, painting <hell> or <heaven>
//STRIP001                 const Color aPageBackgrdColor = pPage->GetDrawBackgrdColor();
//STRIP001                 // OD 29.08.2002 #102450#
//STRIP001                 // add 3rd parameter to <PaintLayer> method calls
//STRIP001                 // OD 09.12.2002 #103045# - add 4th parameter for horizontal text direction.
//STRIP001                 pSh->Imp()->PaintLayer( pSh->GetDoc()->GetHellId(),
//STRIP001                                         aRetouchePart, &aPageBackgrdColor,
//STRIP001                                         (pPage->IsRightToLeft() ? true : false) );
//STRIP001                 pSh->Imp()->PaintLayer( pSh->GetDoc()->GetHeavenId(),
//STRIP001                                         aRetouchePart, &aPageBackgrdColor,
//STRIP001                                         (pPage->IsRightToLeft() ? true : false) );
//STRIP001                 pSh->Imp()->PaintLayer( pSh->GetDoc()->GetControlsId(),
//STRIP001                                         aRetouchePart );
//STRIP001             }
//STRIP001
//STRIP001          SetRetouche();
//STRIP001
//STRIP001          //Da wir uns ausserhalb aller Paint-Bereiche begeben muessen hier
//STRIP001          //leider die Hilfslinien erneuert werden.
//STRIP001             pPage->RefreshSubsidiary( aRetouchePart );
//STRIP001      }
//STRIP001  }
//STRIP001  if ( ViewShell::IsLstEndAction() )
//STRIP001      ResetRetouche();
//STRIP001 }

/** SwFrm::GetBackgroundBrush

    @descr
    determine the background brush for the frame:
    the background brush is taken from it-self or from its parent (anchor/upper).
    Normally, the background brush is taken, which has no transparent color or
    which has a background graphic. But there are some special cases:
    (1) No background brush is taken from a page frame, if view option "IsPageBack"
        isn't set.
    (2) Background brush from a index section is taken under special conditions.
        In this case parameter <rpCol> is set to the index shading color.
    (3) New (OD 20.08.2002) - Background brush is taken, if on background drawing
        of the frame transparency is considered and its color is not "no fill"/"auto fill"
    ---- old description in german:
    Beschreibung        Liefert die Backgroundbrush fuer den Bereich des
        des Frm. Die Brush wird entweder von ihm selbst oder von einem
        Upper vorgegeben, die erste Brush wird benutzt.
        Ist fuer keinen Frm eine Brush angegeben, so wird FALSE zurueck-
        geliefert.
    Ersterstellung      MA 23. Dec. 92
    Letzte Aenderung    MA 04. Feb. 97

    @param rpBrush
    output parameter - constant reference pointer the found background brush

    @param rpCol
    output parameter - constant reference pointer to the color of the index shading
    set under special conditions, if background brush is taken from an index section.

    @param rOrigRect
    in-/output parameter - reference to the retangle the background brush is
    considered for - adjusted to the frame, from which the background brush is
    taken.

    @parem bLowerMode
    input parameter - boolean indicating, if background brush should *not* be
    taken from parent.

    @author MA
    @change 20.08.2002 by OD
    @docdate 20.08.2002

    @return true, if a background brush for the frame is found
*/
//STRIP001 BOOL SwFrm::GetBackgroundBrush( const SvxBrushItem* & rpBrush,
//STRIP001                              const Color*& rpCol,
//STRIP001                              SwRect &rOrigRect,
//STRIP001                              BOOL bLowerMode ) const
//STRIP001 {
//STRIP001  const SwFrm *pFrm = this;
//STRIP001  ViewShell *pSh = GetShell();
//STRIP001  const SwViewOption *pOpt = pSh->GetViewOptions();
//STRIP001  rpBrush = 0;
//STRIP001  rpCol = NULL;
//STRIP001  do
//STRIP001  {   if ( pFrm->IsPageFrm() && !pOpt->IsPageBack() )
//STRIP001          return FALSE;
//STRIP001
//STRIP001      const SvxBrushItem &rBack = pFrm->GetAttrSet()->GetBackground();
//STRIP001      if( pFrm->IsSctFrm() )
//STRIP001      {
//STRIP001          const SwSection* pSection = ((SwSectionFrm*)pFrm)->GetSection();
//STRIP001             /// OD 20.08.2002 #99657# #GetTransChg#
//STRIP001             ///     Note: If frame <pFrm> is a section of the index and
//STRIP001             ///         it its background color is "no fill"/"auto fill" and
//STRIP001             ///         it has no background graphic and
//STRIP001             ///         we are not in the page preview and
//STRIP001             ///         we are not in read-only mode and
//STRIP001             ///         option "index shadings" is set and
//STRIP001             ///         the output is not the printer
//STRIP001             ///         then set <rpCol> to the color of the index shading
//STRIP001             if( pSection && (   TOX_HEADER_SECTION == pSection->GetType() ||
//STRIP001                                 TOX_CONTENT_SECTION == pSection->GetType() ) &&
//STRIP001                 (rBack.GetColor() == COL_TRANSPARENT) &&
//STRIP001                 ///rBack.GetColor().GetTransparency() &&
//STRIP001                 rBack.GetGraphicPos() == GPOS_NONE &&
//STRIP001                 !pOpt->IsPagePreview() && !pOpt->IsReadonly() &&
//STRIP001                 SwViewOption::IsIndexShadings() &&
//STRIP001                 !pOpt->IsPDFExport() &&
//STRIP001                 pSh->GetOut()->GetOutDevType() != OUTDEV_PRINTER )
//STRIP001             {
//STRIP001                 rpCol = &SwViewOption::GetIndexShadingsColor();
//STRIP001             }
//STRIP001         }
//STRIP001
//STRIP001         /// OD 20.08.2002 #99657#
//STRIP001         ///     determine, if background draw of frame <pFrm> considers transparency
//STRIP001         ///     --> Status Quo: background transparency have to be
//STRIP001         ///                     considered for fly frames
//STRIP001         const sal_Bool bConsiderBackgroundTransparency = pFrm->IsFlyFrm();
//STRIP001         /// OD 20.08.2002 #99657#
//STRIP001         ///     add condition:
//STRIP001         ///     If <bConsiderBackgroundTransparency> is set - see above -,
//STRIP001         ///     return brush of frame <pFrm>, if its color is *not* "no fill"/"auto fill"
//STRIP001         if ( !rBack.GetColor().GetTransparency() ||
//STRIP001              rBack.GetGraphicPos() != GPOS_NONE ||
//STRIP001              rpCol ||
//STRIP001              (bConsiderBackgroundTransparency && (rBack.GetColor() != COL_TRANSPARENT))
//STRIP001            )
//STRIP001      {
//STRIP001          rpBrush = &rBack;
//STRIP001          if ( pFrm->IsPageFrm() && pSh->GetDoc()->IsBrowseMode() )
//STRIP001              rOrigRect = pFrm->Frm();
//STRIP001          else
//STRIP001          {
//STRIP001              if ( pFrm->Frm().SSize() != pFrm->Prt().SSize() )
//STRIP001              {
//STRIP001                  SwBorderAttrAccess aAccess( SwFrm::GetCache(), pFrm );
//STRIP001                  const SwBorderAttrs &rAttrs = *aAccess.Get();
//STRIP001                  ::lcl_CalcBorderRect( rOrigRect, pFrm, rAttrs, FALSE );
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  rOrigRect = pFrm->Prt();
//STRIP001                  rOrigRect += pFrm->Frm().Pos();
//STRIP001              }
//STRIP001          }
//STRIP001          return TRUE;
//STRIP001      }
//STRIP001
//STRIP001         if ( bLowerMode )
//STRIP001             /// Do not try to get background brush from parent (anchor/upper)
//STRIP001          return FALSE;
//STRIP001
//STRIP001         /// get parent frame - anchor or upper - for next loop
//STRIP001      if ( pFrm->IsFlyFrm() )
//STRIP001             /// OD 20.08.2002 - use "static_cast" instead of "old C-cast"
//STRIP001             pFrm = (static_cast<const SwFlyFrm*>(pFrm))->GetAnchor();
//STRIP001             ///pFrm = ((SwFlyFrm*)pFrm)->GetAnchor();
//STRIP001      else
//STRIP001          pFrm = pFrm->GetUpper();
//STRIP001
//STRIP001  } while ( pFrm );
//STRIP001
//STRIP001     return FALSE;
//STRIP001 }

/*************************************************************************
|*
|*  SwFrmFmt::GetGraphic()
|*
|*  Ersterstellung      MA 23. Jul. 96
|*  Letzte Aenderung    MA 23. Jul. 96
|*
|*************************************************************************/

//STRIP001 void SetOutDevAndWin( ViewShell *pSh, OutputDevice *pO,
//STRIP001                    Window *pW, USHORT nZoom )
//STRIP001 {
//STRIP001  pSh->pOut = pO;
//STRIP001  pSh->pWin = pW;
//STRIP001  pSh->pOpt->SetZoom( nZoom );
//STRIP001 }

//STRIP001 Graphic SwFrmFmt::MakeGraphic( ImageMap* pMap )
//STRIP001 {
//STRIP001  return Graphic();
//STRIP001 }

//STRIP001 Graphic SwFlyFrmFmt::MakeGraphic( ImageMap* pMap )
//STRIP001 {
//STRIP001  Graphic aRet;
//STRIP001  //irgendeinen Fly suchen!
//STRIP001  SwClientIter aIter( *this );
//STRIP001     SwClient *pFirst = aIter.First( TYPE(SwFrm) );
//STRIP001  ViewShell *pSh;
//STRIP001     if ( pFirst && 0 != ( pSh = ((SwFrm*)pFirst)->GetShell()) )
//STRIP001  {
//STRIP001      ViewShell *pOldGlobal = pGlobalShell;
//STRIP001      pGlobalShell = pSh;
//STRIP001
//STRIP001      FASTBOOL bNoteURL = pMap &&
//STRIP001          SFX_ITEM_SET != GetAttrSet().GetItemState( RES_URL, TRUE );
//STRIP001      if( bNoteURL )
//STRIP001      {
//STRIP001          ASSERT( !pNoteURL, "MakeGraphic: pNoteURL already used? " );
//STRIP001          pNoteURL = new SwNoteURL;
//STRIP001      }
//STRIP001      SwFlyFrm *pFly = (SwFlyFrm*)pFirst;
//STRIP001
//STRIP001      OutputDevice *pOld = pSh->GetOut();
//STRIP001      VirtualDevice aDev( *pOld );
//STRIP001      aDev.EnableOutput( FALSE );
//STRIP001
//STRIP001      GDIMetaFile aMet;
//STRIP001      MapMode aMap( pOld->GetMapMode().GetMapUnit() );
//STRIP001      aDev.SetMapMode( aMap );
//STRIP001      aMet.SetPrefMapMode( aMap );
//STRIP001
//STRIP001      ::SwCalcPixStatics( pSh->GetOut() );
//STRIP001      aMet.SetPrefSize( pFly->Frm().SSize() );
//STRIP001
//STRIP001      aMet.Record( &aDev );
//STRIP001      aDev.SetLineColor();
//STRIP001      aDev.SetFillColor();
//STRIP001      aDev.SetFont( pOld->GetFont() );
//STRIP001
//STRIP001      Window *pWin = pSh->GetWin();
//STRIP001      USHORT nZoom = pSh->GetViewOptions()->GetZoom();
//STRIP001      ::SetOutDevAndWin( pSh, &aDev, 0, 100 );
//STRIP001      bFlyMetafile = TRUE;
//STRIP001      pFlyMetafileOut = pWin;
//STRIP001
//STRIP001      SwViewImp *pImp = pSh->Imp();
//STRIP001      pFlyOnlyDraw = pFly;
//STRIP001      pLines = new SwLineRects;
//STRIP001
//STRIP001      //Rechteck ggf. ausdehnen, damit die Umrandunge mit aufgezeichnet werden.
//STRIP001      SwRect aOut( pFly->Frm() );
//STRIP001      SwBorderAttrAccess aAccess( SwFrm::GetCache(), pFly );
//STRIP001      const SwBorderAttrs &rAttrs = *aAccess.Get();
//STRIP001      if ( rAttrs.CalcRightLine() )
//STRIP001          aOut.SSize().Width() += 2*nPixelSzW;
//STRIP001      if ( rAttrs.CalcBottomLine() )
//STRIP001          aOut.SSize().Height()+= 2*nPixelSzH;
//STRIP001
//STRIP001         // OD 09.12.2002 #103045# - determine page, fly frame is on
//STRIP001         const SwPageFrm* pFlyPage = pFly->FindPageFrm();
//STRIP001         // OD 30.08.2002 #102450#
//STRIP001         // determine color of page, the fly frame is on, for <PaintLayer> method
//STRIP001         // calls, painting <hell> or <heaven>
//STRIP001         const Color aPageBackgrdColor = pFlyPage->GetDrawBackgrdColor();
//STRIP001         // OD 30.08.2002 #102450# - add 3rd parameter
//STRIP001         // OD 09.12.2002 #103045# - add 4th parameter for horizontal text direction.
//STRIP001         pImp->PaintLayer( pSh->GetDoc()->GetHellId(), aOut, &aPageBackgrdColor,
//STRIP001                           (pFlyPage->IsRightToLeft() ? true : false) );
//STRIP001      pLines->PaintLines( &aDev );
//STRIP001      if ( pFly->IsFlyInCntFrm() )
//STRIP001          pFly->Paint( aOut );
//STRIP001      pLines->PaintLines( &aDev );
//STRIP001         /// OD 30.08.2002 #102450# - add 3rd parameter
//STRIP001         pImp->PaintLayer( pSh->GetDoc()->GetHeavenId(), aOut, &aPageBackgrdColor,
//STRIP001                           (pFlyPage->IsRightToLeft() ? true : false) );
//STRIP001      pLines->PaintLines( &aDev );
//STRIP001      if( pSh->GetViewOptions()->IsControl() )
//STRIP001      {
//STRIP001             pImp->PaintLayer( pSh->GetDoc()->GetControlsId(), aOut );
//STRIP001          pLines->PaintLines( &aDev );
//STRIP001      }
//STRIP001      DELETEZ( pLines );
//STRIP001      pFlyOnlyDraw = 0;
//STRIP001
//STRIP001      pFlyMetafileOut = 0;
//STRIP001      bFlyMetafile = FALSE;
//STRIP001      ::SetOutDevAndWin( pSh, pOld, pWin, nZoom );
//STRIP001
//STRIP001      aMet.Stop();
//STRIP001      aMet.Move( -pFly->Frm().Left(), -pFly->Frm().Top() );
//STRIP001      aRet = Graphic( aMet );
//STRIP001
//STRIP001      if( bNoteURL )
//STRIP001      {
//STRIP001          ASSERT( pNoteURL, "MakeGraphic: Good Bye, NoteURL." );
//STRIP001          pNoteURL->FillImageMap( pMap, pFly->Frm().Pos(), aMap );
//STRIP001          delete pNoteURL;
//STRIP001          pNoteURL = NULL;
//STRIP001      }
//STRIP001      pGlobalShell = pOldGlobal;
//STRIP001  }
//STRIP001  return aRet;
//STRIP001 }

//STRIP001 Graphic SwDrawFrmFmt::MakeGraphic( ImageMap* pMap )
//STRIP001 {
//STRIP001  Graphic aRet;
//STRIP001  SdrModel *pMod = GetDoc()->GetDrawModel();
//STRIP001  if ( pMod )
//STRIP001  {
//STRIP001      SdrObject *pObj = FindSdrObject();
//STRIP001      SdrView *pView = new SdrView( pMod );
//STRIP001      SdrPageView *pPgView = pView->ShowPagePgNum( 0, Point() );
//STRIP001      pView->MarkObj( pObj, pPgView );
//STRIP001      aRet = pView->GetMarkedObjBitmap();
//STRIP001      pView->HidePage( pPgView );
//STRIP001      delete pView;
//STRIP001  }
//STRIP001  return aRet;
//STRIP001 }
