/*************************************************************************
 *
 *  $RCSfile: boxitem.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 08:27:29 $
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
#ifndef _SVX_BOXITEM_HXX
#define _SVX_BOXITEM_HXX

// include ---------------------------------------------------------------

#ifndef _SFXPOOLITEM_HXX //autogen
#include <svtools/poolitem.hxx>
#endif
#ifndef _COLOR_HXX //autogen
#include <vcl/color.hxx>
#endif
#ifndef _SVX_SVXIDS_HRC
#include <bf_svx/svxids.hrc>
#endif

#ifdef _USE_NAMESPACE
namespace rtl
{
#endif
    class OUString;
#ifdef _USE_NAMESPACE
}
#endif
namespace binfilter {

// class SvxBoxItem ------------------------------------------------------

// Linien-Defaults in Twips (fruehere Writer-Defaults):

#define DEF_LINE_WIDTH_0        1
#define DEF_LINE_WIDTH_1        20
#define DEF_LINE_WIDTH_2        50
#define DEF_LINE_WIDTH_3        80
#define DEF_LINE_WIDTH_4        100

#define DEF_MAX_LINE_WIDHT      DEF_LINE_WIDTH_4
#define DEF_MAX_LINE_DIST       DEF_LINE_WIDTH_2

#define DEF_DOUBLE_LINE0_OUT    DEF_LINE_WIDTH_0
#define DEF_DOUBLE_LINE0_IN     DEF_LINE_WIDTH_0
#define DEF_DOUBLE_LINE0_DIST   DEF_LINE_WIDTH_1

#define DEF_DOUBLE_LINE1_OUT    DEF_LINE_WIDTH_1
#define DEF_DOUBLE_LINE1_IN     DEF_LINE_WIDTH_1
#define DEF_DOUBLE_LINE1_DIST   DEF_LINE_WIDTH_1

#define DEF_DOUBLE_LINE2_OUT    DEF_LINE_WIDTH_2
#define DEF_DOUBLE_LINE2_IN     DEF_LINE_WIDTH_2
#define DEF_DOUBLE_LINE2_DIST   DEF_LINE_WIDTH_2

#define DEF_DOUBLE_LINE3_OUT    DEF_LINE_WIDTH_2
#define DEF_DOUBLE_LINE3_IN     DEF_LINE_WIDTH_1
#define DEF_DOUBLE_LINE3_DIST   DEF_LINE_WIDTH_2

#define DEF_DOUBLE_LINE4_OUT    DEF_LINE_WIDTH_1
#define DEF_DOUBLE_LINE4_IN     DEF_LINE_WIDTH_2
#define DEF_DOUBLE_LINE4_DIST   DEF_LINE_WIDTH_1

#define DEF_DOUBLE_LINE5_OUT    DEF_LINE_WIDTH_3
#define DEF_DOUBLE_LINE5_IN     DEF_LINE_WIDTH_2
#define DEF_DOUBLE_LINE5_DIST   DEF_LINE_WIDTH_2

#define DEF_DOUBLE_LINE6_OUT    DEF_LINE_WIDTH_2
#define DEF_DOUBLE_LINE6_IN     DEF_LINE_WIDTH_3
#define DEF_DOUBLE_LINE6_DIST   DEF_LINE_WIDTH_2

#define DEF_DOUBLE_LINE7_OUT    DEF_LINE_WIDTH_0
#define DEF_DOUBLE_LINE7_IN     DEF_LINE_WIDTH_0
#define DEF_DOUBLE_LINE7_DIST   DEF_LINE_WIDTH_2

#define DEF_DOUBLE_LINE8_OUT    DEF_LINE_WIDTH_1
#define DEF_DOUBLE_LINE8_IN     DEF_LINE_WIDTH_0
#define DEF_DOUBLE_LINE8_DIST   DEF_LINE_WIDTH_2

#define DEF_DOUBLE_LINE9_OUT    DEF_LINE_WIDTH_2
#define DEF_DOUBLE_LINE9_IN     DEF_LINE_WIDTH_0
#define DEF_DOUBLE_LINE9_DIST   DEF_LINE_WIDTH_2

#define DEF_DOUBLE_LINE10_OUT   DEF_LINE_WIDTH_3
#define DEF_DOUBLE_LINE10_IN    DEF_LINE_WIDTH_0
#define DEF_DOUBLE_LINE10_DIST  DEF_LINE_WIDTH_2

//SvxBorderLine, Beschreibung einer Seite der Umrandung ------

class SvxBorderLine
{
protected:
    Color  aColor;
    USHORT nOutWidth;
    USHORT nInWidth;
    USHORT nDistance;

public:
    SvxBorderLine( const Color *pCol = 0, USHORT nOut = 0,
                   USHORT nIn = 0, USHORT nDist = 0 );

    const Color&    GetColor() const { return aColor; }
    USHORT          GetOutWidth() const { return nOutWidth; }
    USHORT          GetInWidth() const { return nInWidth; }
    USHORT          GetDistance() const { return nDistance; }

    void            SetColor( const Color &rColor ) { aColor = rColor; }
    void            SetOutWidth( USHORT nNew ) { nOutWidth = nNew; }
    void            SetInWidth( USHORT nNew ) { nInWidth = nNew;  }
    void            SetDistance( USHORT nNew ) { nDistance = nNew; }
    void            ScaleMetrics( long nMult, long nDiv );

    BOOL            operator==( const SvxBorderLine &rCmp ) const;

//STRIP001     String          GetValueString( SfxMapUnit eSrcUnit, SfxMapUnit eDestUnit,
//STRIP001                                     const IntlWrapper* pIntl,
//STRIP001                                  BOOL bMetricStr = FALSE ) const;
};

/*
[Beschreibung]
Dieses Item beschreibt ein Umrandungsattribut (alle vier Kanten und
Abstand nach innen.
*/

#define BOX_LINE_TOP    ((USHORT)0)
#define BOX_LINE_BOTTOM ((USHORT)1)
#define BOX_LINE_LEFT   ((USHORT)2)
#define BOX_LINE_RIGHT  ((USHORT)3)

#define BOX_4DISTS_VERSION ((USHORT)1)

class SvxBoxItem : public SfxPoolItem
{
    SvxBorderLine  *pTop,
                   *pBottom,
                   *pLeft,
                   *pRight;
    USHORT          nTopDist,
                    nBottomDist,
                    nLeftDist,
                    nRightDist;

public:
    TYPEINFO();

    SvxBoxItem( const USHORT nId = ITEMID_BOX );
    SvxBoxItem( const SvxBoxItem &rCpy );
    ~SvxBoxItem();
    SvxBoxItem &operator=( const SvxBoxItem& rBox );

    // "pure virtual Methoden" vom SfxPoolItem
    virtual int              operator==( const SfxPoolItem& ) const;
    virtual sal_Bool             QueryValue( ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 ) const;
    virtual sal_Bool             PutValue( const ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 );

//STRIP001  virtual SfxItemPresentation GetPresentation( SfxItemPresentation ePres,
//STRIP001                                  SfxMapUnit eCoreMetric,
//STRIP001                                  SfxMapUnit ePresMetric,
//STRIP001                                     String &rText, const IntlWrapper * = 0 ) const;

    virtual SfxPoolItem*     Clone( SfxItemPool *pPool = 0 ) const;
    virtual SfxPoolItem*     Create(SvStream &, USHORT) const;
    virtual SvStream&        Store(SvStream &, USHORT nItemVersion ) const;
    virtual USHORT           GetVersion( USHORT nFileVersion ) const;

//STRIP001  virtual int              ScaleMetrics( long nMult, long nDiv );
//STRIP001  virtual int              HasMetrics() const;

    const   SvxBorderLine* GetTop()    const { return pTop; }
    const   SvxBorderLine* GetBottom() const { return pBottom; }
    const   SvxBorderLine* GetLeft()   const { return pLeft; }
    const   SvxBorderLine* GetRight()  const { return pRight; }

//STRIP001  const   SvxBorderLine* GetLine( USHORT nLine ) const;

        //Die Pointer werden kopiert!
    void    SetLine( const SvxBorderLine* pNew, USHORT nLine );

    USHORT  GetDistance( USHORT nLine ) const;
    USHORT  GetDistance() const;

    void    SetDistance( USHORT nNew, USHORT nLine );
    inline void SetDistance( USHORT nNew );

        //Breite der Linien plus Zwischenraum plus Abstand nach innen.
        //JP 09.06.99: bIgnoreLine = TRUE -> Distance auch returnen, wenn
        //                          keine Line gesetzt ist
    USHORT  CalcLineSpace( USHORT nLine, BOOL bIgnoreLine = FALSE ) const;
};

inline void SvxBoxItem::SetDistance( USHORT nNew )
{
    nTopDist = nBottomDist = nLeftDist = nRightDist = nNew;
}

// class SvxBoxInfoItem --------------------------------------------------

/*
[Beschreibung]
Noch ein Item fuer die Umrandung. Dieses Item hat lediglich SS-Funktionalitaet.
Einerseits wird dem allgemeinen Dialog mit diesem Item mitgeteilt, welche
Moeglichkeiten er anbieten soll.
Andererseits werden ueber dieses Attribut ggf. die BorderLines fuer die
horizontalen und vertikalen innerern Linien transportiert.
*/

#define BOXINFO_LINE_HORI   ((USHORT)0)
#define BOXINFO_LINE_VERT   ((USHORT)1)

#define VALID_TOP           0x01
#define VALID_BOTTOM        0x02
#define VALID_LEFT          0x04
#define VALID_RIGHT         0x08
#define VALID_HORI          0x10
#define VALID_VERT          0x20
#define VALID_DISTANCE      0x40
#define VALID_DISABLE       0x80

#ifdef ITEMID_BOXINFO
class SvxBoxInfoItem : public SfxPoolItem
{
    SvxBorderLine* pHori;   //innere horizontale Linie
    SvxBorderLine* pVert;   //innere vertikale Linie

    BOOL bTable     :1;     //Es koennen Werte fuer eine Tabelle bearbeitet
                            //werden (horizontale und vertikale Linie).

    /*
     z.Z. nur fuer StarWriter: Abstand nach innen von SvxBoxItem.
     Wenn der Abstand gewuenscht ist, so muss das Feld fuer den Abstand vom
     Dialog freigeschaltet werden. nDefDist ist als Defaultwert anzusehen.
     Wenn irgendeine    Linie eingeschalt ist oder wird, so muss dieser
     Abstand defaultet werden. bMinDist gibt an, ob der Wert durch den
     Anwender unterschritten werden darf. Mit nDist wird der aktuelle
     Abstand von der App zum Dialog und zurueck transportiert.
    */

    BOOL    bDist      :1;  // TRUE, Abstand freischalten.
    BOOL    bMinDist   :1;  // TRUE, Abstand darf nicht unterschritten werden.

    BYTE    nValidFlags;    // 0000 0000
                            // ³³³³ ³³³À?VALID_TOP
                            // ³³³³ ³³ÀÄ?VALID_BOTTOM
                            // ³³³³ ³ÀÄÄ?VALID_LEFT
                            // ³³³³ ÀÄÄÄ?VALID_RIGHT
                            // ³³³ÀÄÄÄÄÄÄ VALID_HORI
                            // ³³ÀÄÄÄÄÄÄÄ VALID_VERT
                            // ³ÀÄÄÄÄÄÄÄÄ VALID_DIST
                            // ÀÄÄÄÄÄÄÄÄÄ VALID_DISABLE

    USHORT  nDefDist;       // Der Default- bzw. Minimalabstand.

public:
    TYPEINFO();

    SvxBoxInfoItem( const USHORT nId = ITEMID_BOXINFO );
    SvxBoxInfoItem( const SvxBoxInfoItem &rCpy );
    ~SvxBoxInfoItem();
//STRIP001  SvxBoxInfoItem &operator=( const SvxBoxInfoItem &rCpy );

    // "pure virtual Methoden" vom SfxPoolItem
    virtual int              operator==( const SfxPoolItem& ) const;
//STRIP001  virtual SfxItemPresentation GetPresentation( SfxItemPresentation ePres,
//STRIP001                                  SfxMapUnit eCoreMetric,
//STRIP001                                  SfxMapUnit ePresMetric,
//STRIP001                                     String &rText, const IntlWrapper * = 0 ) const;
//STRIP001  virtual sal_Bool             QueryValue( ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 ) const;
//STRIP001  virtual sal_Bool             PutValue( const ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 );

    virtual SfxPoolItem*    Clone( SfxItemPool *pPool = 0 ) const;
    virtual SfxPoolItem*    Create(SvStream &, USHORT) const;
    virtual SvStream&       Store(SvStream &, USHORT nItemVersion ) const;
//STRIP001  virtual int              ScaleMetrics( long nMult, long nDiv );
//STRIP001  virtual int              HasMetrics() const;

    const SvxBorderLine*    GetHori() const { return pHori; }
    const SvxBorderLine*    GetVert() const { return pVert; }

    //Die Pointer werden kopiert!
    void                    SetLine( const SvxBorderLine* pNew, USHORT nLine );

    BOOL    IsTable() const             { return bTable; }
    void    SetTable( BOOL bNew )       { bTable = bNew; }
    BOOL    IsDist() const              { return bDist; }
    void    SetDist( BOOL bNew )        { bDist = bNew; }
    BOOL    IsMinDist() const           { return bMinDist; }
    void    SetMinDist( BOOL bNew )     { bMinDist = bNew; }
    USHORT  GetDefDist() const          { return nDefDist; }
    void    SetDefDist( USHORT nNew )   { nDefDist = nNew; }

    BOOL                    IsValid( BYTE nValid ) const
                                { return ( nValidFlags & nValid ) == nValid; }
    void                    SetValid( BYTE nValid, BOOL bValid = TRUE )
                                { bValid ? ( nValidFlags |= nValid )
                                         : ( nValidFlags &= ~nValid ); }
    void                    ResetFlags();
};
#endif

}//end of namespace binfilter
#endif

