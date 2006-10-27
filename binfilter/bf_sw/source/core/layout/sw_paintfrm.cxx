/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_paintfrm.cxx,v $
 *
 *  $Revision: 1.7 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-27 22:55:18 $
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






//Ermittelt PrtArea plus Umrandung plus Schatten.





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


//------------------------------------------------------------------------

/** local help method for SwRootFrm::Paint(..) - Adjust given rectangle to pixel size

    By OD at 27.09.2002 for #103636#
    In order to avoid paint errors caused by multiple alignments - e.g. method
    ::SwAlignRect(..) - and other changes to the rectangle to be painted,
    this method is called for the rectangle to be painted in order to
    adjust it to the pixel it is overlapping.

    @author OD
*/

/*************************************************************************
|*
|*  SwRootFrm::Paint()
|*
|*  Beschreibung
|*      Fuer jede sichtbare Seite, die von Rect berÅhrt wird einmal Painten.
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


/*************************************************************************
|*
|*  SwRootFrm::HackPrepareLongTblPaint()
|*
|*  Ersterstellung      MA 27. Sep. 96
|*  Letzte Aenderung    MA 18. Nov. 97
|*
|*************************************************************************/



/*************************************************************************
|*
|*  SwLayoutFrm::Paint()
|*
|*  Ersterstellung      MA 19. May. 92
|*  Letzte Aenderung    MA 19. Apr. 95
|*
|*************************************************************************/






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

/** FlyFrm::IsShadowTransparent - for feature #99657#

    OD 13.08.2002
    determine, if shadow color of fly frame has to be drawn transparent
    declaration found in /core/inc/flyfrm.cxx

    @author OD

    @return true, if shadow color is transparent.
*/

/*************************************************************************
|*
|*  SwFlyFrm::IsPaint()
|*
|*  Ersterstellung      MA 16. Jan. 97
|*  Letzte Aenderung    MA 16. Jan. 97
|*
|*************************************************************************/


/*************************************************************************
|*
|*  SwFlyFrm::Paint()
|*
|*  Ersterstellung      MA ??
|*  Letzte Aenderung    MA 16. Jan. 97
|*
|*************************************************************************/

//Weiter unten definiert

/*************************************************************************
|*
|*    SwTabFrm::Paint()
|*
|*    Ersterstellung    MA 11. May. 93
|*    Letzte Aenderung  MA 23. Mar. 95
|*
|*************************************************************************/


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

/*************************************************************************
|*
|*  SwFrm::PaintBorderLine()
|*
|*  Ersterstellung      MA 22. Dec. 92
|*  Letzte Aenderung    MA 22. Jan. 95
|*
|*************************************************************************/


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

// method called for top and bottom border rectangles.

// OD 19.05.2003 #109667# - merge <lcl_PaintLeftLine> and <lcl_PaintRightLine>
// into new method <lcl_PaintLeftRightLine(..)>

// OD 19.05.2003 #109667# - merge <lcl_PaintTopLine> and <lcl_PaintBottomLine>
// into <lcl_PaintTopLine>


/*************************************************************************
|*
|*  const SwFrm* lcl_HasNextCell( const SwFrm& rFrm )
|*
|* No comment. #i15844#
|*
|*************************************************************************/



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

/*************************************************************************
|*
|*  SwFtnContFrm::PaintLine()
|*
|*  Beschreibung        Fussnotenline malen.
|*  Ersterstellung      MA 02. Mar. 93
|*  Letzte Aenderung    MA 28. Mar. 94
|*
|*************************************************************************/


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
