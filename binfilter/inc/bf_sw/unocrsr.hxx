/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: unocrsr.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 16:43:11 $
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
#ifndef _UNOCRSR_HXX
#define _UNOCRSR_HXX

#ifndef _SWCRSR_HXX
#include <swcrsr.hxx>
#endif
#ifndef _CALBCK_HXX
#include <calbck.hxx>
#endif
namespace binfilter {


class SwUnoCrsr : public virtual SwCursor, public SwModify
{
    BOOL bRemainInSection : 1;
    BOOL bSkipOverHiddenSections : 1;
    BOOL bSkipOverProtectSections : 1;

public:
    SwUnoCrsr( const SwPosition &rPos, SwPaM* pRing = 0 );
    SwUnoCrsr( SwUnoCrsr& );
    virtual ~SwUnoCrsr();

    virtual operator SwUnoCrsr* ();

//  virtual SwCursor* Create( SwPaM* pRing = 0 ) const;

    // gibt es eine Selection vom Content in die Tabelle
    // Return Wert gibt an, ob der Crsr auf der alten Position verbleibt
    virtual FASTBOOL IsSelOvr( int eFlags =
                                ( SELOVER_CHECKNODESSECTION |
                                  SELOVER_TOGGLE | SELOVER_CHANGEPOS ));

    BOOL IsRemainInSection() const          { return bRemainInSection; }
    void SetRemainInSection( BOOL bFlag )   { bRemainInSection = bFlag; }

    BOOL IsSkipOverProtectSections() const
                                    { return bSkipOverProtectSections; }
    void SetSkipOverProtectSections( BOOL bFlag )
                                    { bSkipOverProtectSections = bFlag; }

    BOOL IsSkipOverHiddenSections() const
                                    { return bSkipOverHiddenSections; }
    void SetSkipOverHiddenSections( BOOL bFlag )
                                    { bSkipOverHiddenSections = bFlag; }

    DECL_FIXEDMEMPOOL_NEWDEL( SwUnoCrsr )
};



class SwUnoTableCrsr : public virtual SwUnoCrsr, public virtual SwTableCursor
{
    // die Selection hat die gleiche Reihenfolge wie die
    // TabellenBoxen. D.h., wird aus dem einen Array an einer Position
    // etwas geloescht, dann muss es auch im anderen erfolgen!!
    SwCursor aTblSel;

public:
    SwUnoTableCrsr( const SwPosition& rPos );
    virtual ~SwUnoTableCrsr();

//  virtual SwCursor* Create( SwPaM* pRing = 0 ) const;

    virtual operator SwUnoCrsr* ();
    virtual operator SwUnoTableCrsr* ();
    virtual operator SwTableCursor* ();

    // gibt es eine Selection vom Content in die Tabelle
    // Return Wert gibt an, ob der Crsr auf der alten Position verbleibt
    virtual FASTBOOL IsSelOvr( int eFlags =
                                ( SELOVER_CHECKNODESSECTION |
                                  SELOVER_TOGGLE | SELOVER_CHANGEPOS ));

    void MakeBoxSels();
           SwCursor& GetSelRing()           { return aTblSel; }
    const SwCursor& GetSelRing() const      { return aTblSel; }
};



} //namespace binfilter
#endif
