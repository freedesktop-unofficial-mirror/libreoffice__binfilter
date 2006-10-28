/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: fmtanchr.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 04:41:46 $
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
#ifndef _FMTANCHR_HXX
#define _FMTANCHR_HXX

#ifndef _SWTYPES_HXX //autogen
#include <swtypes.hxx>
#endif
#ifndef _FORMAT_HXX //autogen
#include <format.hxx>
#endif
class IntlWrapper;
namespace binfilter {

struct SwPosition;

#define IVER_FMTANCHOR_LONGIDX ((USHORT)1)

//FlyAnchor, Anker des Freifliegenden Rahmen ----

class SwFmtAnchor: public SfxPoolItem
{
    SwPosition *pCntntAnchor;   //0 Fuer Seitengebundene Rahmen.
                                //Index fuer Absatzgebundene Rahmen.
                                //Position fuer Zeichengebundene Rahmen
    RndStdIds  nAnchorId;
    USHORT     nPageNum;        //Seitennummer bei Seitengeb. Rahmen.

public:
    SwFmtAnchor( RndStdIds eRnd = FLY_PAGE, USHORT nPageNum = 0 );
    SwFmtAnchor( const SwFmtAnchor &rCpy );
    ~SwFmtAnchor();

    //  Zuweisungsoperator
    SwFmtAnchor &operator=( const SwFmtAnchor& );

    // "pure virtual Methoden" vom SfxPoolItem
    virtual int             operator==( const SfxPoolItem& ) const;
    virtual SfxPoolItem*    Clone( SfxItemPool* pPool = 0 ) const;
    virtual SfxPoolItem*    Create(SvStream &, USHORT nVer) const;
    virtual SvStream&       Store(SvStream &, USHORT nIVer) const;
    virtual USHORT          GetVersion( USHORT nFFVer ) const;

    virtual BOOL             QueryValue( ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 ) const;
    virtual BOOL             PutValue( const ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 );

    RndStdIds GetAnchorId() const { return nAnchorId; }
    USHORT GetPageNum() const { return nPageNum; }
    const SwPosition *GetCntntAnchor() const { return pCntntAnchor; }

    void SetPageNum( USHORT nNew ) { nPageNum = nNew; }

    void SetType( RndStdIds nRndId ) { nAnchorId = nRndId; }
    void SetAnchor( const SwPosition *pPos );
};

#if !(defined(MACOSX) && ( __GNUC__ < 3 ))
// GrP moved to gcc_outl.cxx; revisit with gcc3
inline const SwFmtAnchor &SwAttrSet::GetAnchor(BOOL bInP) const
     { return (const SwFmtAnchor&)Get( RES_ANCHOR,bInP); }

 inline const SwFmtAnchor &SwFmt::GetAnchor(BOOL bInP) const
     { return aSet.GetAnchor(bInP); }
#endif

} //namespace binfilter
#endif

