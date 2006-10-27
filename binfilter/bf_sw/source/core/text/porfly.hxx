/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: porfly.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-27 23:06:10 $
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
#ifndef _PORFLY_HXX
#define _PORFLY_HXX

#include "porglue.hxx"
namespace binfilter {

class SwDrawContact;
class SwFrmFmt;
class SwFlyInCntFrm;
class SwTxtFrm;
struct SwCrsrMoveState;

/*************************************************************************
 *                class SwFlyPortion
 *************************************************************************/

class SwFlyPortion : public SwFixPortion
{
    KSHORT nBlankWidth;
public:
    inline  SwFlyPortion( const SwRect &rFlyRect )
        : SwFixPortion(rFlyRect), nBlankWidth( 0 ) { SetWhichPor( POR_FLY ); }
    inline const KSHORT GetBlankWidth( ) const { return nBlankWidth; }
    inline void SetBlankWidth( const KSHORT nNew ) { nBlankWidth = nNew; }
    virtual void Paint( const SwTxtPaintInfo &rInf ) const{DBG_BF_ASSERT(0, "STRIP");} //STRIP001   virtual void Paint( const SwTxtPaintInfo &rInf ) const;
    virtual sal_Bool Format( SwTxtFormatInfo &rInf );
    OUTPUT_OPERATOR
};

/*************************************************************************
 *                class SwFlyCntPortion
 *************************************************************************/

#define SETBASE_NOFLAG  0
#define SETBASE_QUICK   1
#define SETBASE_ULSPACE 2
#define SETBASE_INIT    4
#define SETBASE_ROTATE  8
#define SETBASE_REVERSE 16
#ifdef BIDI
#define SETBASE_BIDI    32
#endif

class SwFlyCntPortion : public SwLinePortion
{
    void *pContact; // bDraw ? DrawContact : FlyInCntFrm
    Point aRef;     // Relativ zu diesem Point wird die AbsPos berechnet.
    sal_Bool bDraw : 1;  // DrawContact?
    sal_Bool bMax : 1;   // Zeilenausrichtung und Hoehe == Zeilenhoehe
    sal_uInt8 nAlign : 3; // Zeilenausrichtung? Nein, oben, mitte, unten

public:
    SwFlyCntPortion( const SwTxtFrm& rFrm, SwFlyInCntFrm *pFly,
                     const Point &rBase, long nAscent, long nDescent,
                     long nFlyAsc, long nFlyDesc, sal_uInt8 nFlags );
    SwFlyCntPortion( const SwTxtFrm& rFrm, SwDrawContact *pDrawContact,
                     const Point &rBase, long nAscent, long nDescent,
                     long nFlyAsc, long nFlyDesc, sal_uInt8 nFlags );
    inline const Point& GetRefPoint() const { return aRef; }
    inline SwFlyInCntFrm *GetFlyFrm() { return (SwFlyInCntFrm*)pContact; }
    inline const SwFlyInCntFrm *GetFlyFrm() const
        { return (SwFlyInCntFrm*)pContact; }
    inline SwDrawContact *GetDrawContact() { return (SwDrawContact*)pContact; }
    inline const SwDrawContact* GetDrawContact() const
        { return (SwDrawContact*)pContact; }
    inline const sal_Bool IsDraw() const { return bDraw; }
    inline const sal_Bool IsMax() const { return bMax; }
    inline const sal_uInt8 GetAlign() const { return nAlign; }
    inline void SetAlign( sal_uInt8 nNew ) { nAlign = nNew; }
    inline void SetMax( sal_Bool bNew ) { bMax = bNew; }
    void SetBase( const SwTxtFrm& rFrm, const Point &rBase,
                  long nLnAscent, long nLnDescent, long nFlyAscent,
                  long nFlyDescent, sal_uInt8 nFlags );
    const SwFrmFmt *GetFrmFmt() const;
    virtual sal_Bool Format( SwTxtFormatInfo &rInf );
    virtual void Paint( const SwTxtPaintInfo &rInf ) const{DBG_BF_ASSERT(0, "STRIP");} ;//STRIP001  virtual void Paint( const SwTxtPaintInfo &rInf ) const;
    OUTPUT_OPERATOR
};

CLASSIO( SwFlyPortion )
CLASSIO( SwFlyCntPortion )


} //namespace binfilter
#endif
