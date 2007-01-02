/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_paintfrm.cxx,v $
 *
 *  $Revision: 1.8 $
 *
 *  last change: $Author: hr $ $Date: 2007-01-02 17:54:20 $
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

#define ITEMID_BOXINFO      SID_ATTR_BORDER_INNER
#include <hintids.hxx>

#define _SVSTDARR_LONGS

#ifndef _SVDPAGV_HXX //autogen
#include <bf_svx/svdpagv.hxx>
#endif



#ifndef _PAGEFRM_HXX
#include <pagefrm.hxx>
#endif
#ifndef _VIEWSH_HXX
#include <viewsh.hxx>
#endif

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

#ifndef _FRMTOOL_HXX
#include <frmtool.hxx>
#endif
#ifndef _VIRTOUTP_HXX
#include <virtoutp.hxx>
#endif
// OD 20.12.2002 #94627#
// OD 28.02.2003 #b4779636#, #107692#
// OD 02.07.2003 #108784#
namespace binfilter {

/*N*/ #define GETOBJSHELL()     ((SfxObjectShell*)rSh.GetDoc()->GetDocShell())


//Klassendeklarationen. Hier weil sie eben nur in diesem File benoetigt
//werden.

/*N*/ #define SUBCOL_PAGE     0x01    //Helplines of the page
/*N*/ #define SUBCOL_BREAK    0x02    //Helpline for a page or column break
/*N*/ #define SUBCOL_TAB      0x08    //Helplines inside tables
/*N*/ #define SUBCOL_FLY      0x10    //Helplines inside fly frames
/*N*/ #define SUBCOL_SECT     0x20    //Helplines inside sections

//----- Klassen zum Sammeln von Umrandungen und Hilfslinien ---




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
// OD 18.11.2002 #99672# - global variable for sub-lines of body, header, footer,
// section and footnote frames.


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

//Zum Sichern der statics, damit das Paint (quasi) reentrant wird.



//----------------- Implementierungen fuer Tabellenumrandung --------------


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

/** determine rectangle for right page shadow

    OD 12.02.2003 for #i9719# and #105645#

    @author OD
*/

/** determine rectangle for bottom page shadow

    OD 12.02.2003 for #i9719# and #105645#

    @author OD
*/

/** paint page border and shadow

    OD 12.02.2003 for #i9719# and #105645#
    implement paint of page border and shadow

    @author OD
*/

/** get bound rectangle of border and shadow for repaints

    OD 12.02.2003 for #i9719# and #105645#

    author OD
*/
/*N*/ void SwPageFrm::GetBorderAndShadowBoundRect(
/*N*/                                 const SwRect& _rPageRect,
/*N*/                                 ViewShell*    _pViewShell,
/*N*/                                 SwRect& _orBorderAndShadowBoundRect ) const
/*N*/ {DBG_BF_ASSERT(0, "STRIP");//STRIP001
/*N*/ }

/*************************************************************************
|*
|*  SwFrm::PaintBaBo()
|*
|*  Ersterstellung      MA 22. Oct. 93
|*  Letzte Aenderung    MA 19. Jun. 96
|*
|*************************************************************************/


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

/*************************************************************************
|*
|*  SwPageFrm::RefreshSubsidiary()
|*
|*  Beschreibung        Erneuert alle Hilfslinien der Seite.
|*  Ersterstellung      MA 04. Nov. 92
|*  Letzte Aenderung    MA 10. May. 95
|*
|*************************************************************************/


/*************************************************************************
|*
|*  SwLayoutFrm::RefreshLaySubsidiary()
|*
|*  Ersterstellung      MA 04. Nov. 92
|*  Letzte Aenderung    MA 22. Jan. 95
|*
|*************************************************************************/

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

// OD 18.11.2002 #99672# - new parameter <_pSubsLines>


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



/** SwPageFrm::GetDrawBackgrdColor - for #102450#

    determine the color, that is respectively will be drawn as background
    for the page frame.
    Using existing method SwFrm::GetBackgroundBrush to determine the color
    that is set at the page frame respectively is parent. If none is found
    return the global retouche color

    @author OD

    @return Color
*/


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

/*************************************************************************
|*
|*  SwFrmFmt::GetGraphic()
|*
|*  Ersterstellung      MA 23. Jul. 96
|*  Letzte Aenderung    MA 23. Jul. 96
|*
|*************************************************************************/




}
