/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: viscrs.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 05:02:36 $
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
#ifndef _VISCRS_HXX
#define _VISCRS_HXX

#ifndef _CURSOR_HXX //autogen
#include <vcl/cursor.hxx>
#endif
#include "swcrsr.hxx"
#include "swrect.hxx"
#include "swregion.hxx"
class Window;
namespace binfilter {

class SwCrsrShell;
class SwShellCrsr;



// --------  Ab hier Klassen / Methoden fuer den nicht Text-Cursor ------

class SwVisCrsr
#ifdef SW_CRSR_TIMER
                : private Timer
#endif
{
    friend void _InitCore();
    friend void _FinitCore();

    BOOL bIsVisible : 1;
    BOOL bIsDragCrsr : 1;

#ifdef SW_CRSR_TIMER
    BOOL bTimerOn : 1;
#endif

    Cursor aTxtCrsr;
    const SwCrsrShell* pCrsrShell;

#ifdef SW_CRSR_TIMER
#endif
    void _SetPosAndShow();

public:
    SwVisCrsr( const SwCrsrShell * pCShell );
    ~SwVisCrsr();

    void Show();
    void Hide();

    FASTBOOL IsVisible() const { return bIsVisible; }
    FASTBOOL IsDragCrsr() const { return bIsDragCrsr; }
    void SetDragCrsr( BOOL bFlag = TRUE ) { bIsDragCrsr = bFlag; }

#ifdef SW_CRSR_TIMER
#endif
};


// ------ Ab hier Klassen / Methoden fuer die Selectionen -------

class SwSelPaintRects : public SwRects
{
    friend void _InitCore();
    friend void _FinitCore();

    static long nPixPtX, nPixPtY;
    static MapMode *pMapMode;

    // die Shell
    const SwCrsrShell* pCShell;


    virtual void FillRects() = 0;

public:
    SwSelPaintRects( const SwCrsrShell& rCSh );
    ~SwSelPaintRects();

    void Show();
    void Hide();

    const SwCrsrShell* GetShell() const { return pCShell; }
    // check current MapMode of the shell and set possibly the static members.
    // Optional set the parameters pX, pY
    static void Get1PixelInLogic( const ViewShell& rSh,
                                    long* pX = 0, long* pY = 0 );
};


class SwShellCrsr : public virtual SwCursor, public SwSelPaintRects
{
    // Dokument-Positionen der Start/End-Charakter einer SSelection
    Point aMkPt, aPtPt;
    const SwPosition* pPt;      // fuer Zuordung vom GetPoint() zum aPtPt

    virtual void FillRects();   // fuer Table- und normalen Crsr

public:
    SwShellCrsr( const SwCrsrShell& rCrsrSh, const SwPosition &rPos );
    virtual ~SwShellCrsr();

    virtual operator SwShellCrsr* ();

    void Show();            // Update und zeige alle Selektionen an

    const Point& GetPtPos() const   { return( SwPaM::GetPoint() == pPt ? aPtPt : aMkPt ); }
          Point& GetPtPos()         { return( SwPaM::GetPoint() == pPt ? aPtPt : aMkPt ); }
    const Point& GetMkPos() const   { return( SwPaM::GetMark() == pPt ? aPtPt : aMkPt ); }
          Point& GetMkPos()         { return( SwPaM::GetMark() == pPt ? aPtPt : aMkPt ); }
    const Point& GetSttPos() const  { return( SwPaM::Start() == pPt ? aPtPt : aMkPt ); }
          Point& GetSttPos()        { return( SwPaM::Start() == pPt ? aPtPt : aMkPt ); }
    const Point& GetEndPos() const  { return( SwPaM::End() == pPt ? aPtPt : aMkPt ); }
          Point& GetEndPos()        { return( SwPaM::End() == pPt ? aPtPt : aMkPt ); }




    FASTBOOL UpDown( BOOL bUp, USHORT nCnt = 1 );

    // TRUE: an die Position kann der Cursor gesetzt werden

#ifndef PRODUCT
// JP 05.03.98: zum Testen des UNO-Crsr Verhaltens hier die Implementierung
//              am sichtbaren Cursor
#endif

    DECL_FIXEDMEMPOOL_NEWDEL( SwShellCrsr )
};



class SwShellTableCrsr : public virtual SwShellCrsr, public virtual SwTableCursor
{
    // die Selection hat die gleiche Reihenfolge wie die
    // TabellenBoxen. D.h., wird aus dem einen Array an einer Position
    // etwas geloescht, dann muss es auch im anderen erfolgen!!


public:
    SwShellTableCrsr( const SwCrsrShell& rCrsrSh, const SwPosition& rPos );
    SwShellTableCrsr( const SwCrsrShell& rCrsrSh,
                    const SwPosition &rMkPos, const Point& rMkPt,
                    const SwPosition &rPtPos, const Point& rPtPt );
    virtual ~SwShellTableCrsr();

     virtual operator SwShellTableCrsr* ();


    // Pruefe, ob sich der SPoint innerhalb der Tabellen-SSelection befindet

    virtual void SetMark();
    virtual operator SwShellCrsr* ();
    virtual operator SwTableCursor* ();

    // TRUE: an die Position kann der Cursor gesetzt werden

// JP 05.03.98: zum Testen des UNO-Crsr Verhaltens hier die Implementierung
//              am sichtbaren Cursor
};



} //namespace binfilter
#endif  // _VISCRS_HXX
