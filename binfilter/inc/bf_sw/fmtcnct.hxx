/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: fmtcnct.hxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 04:42:24 $
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
#ifndef _FMTCNCT_HXX
#define _FMTCNCT_HXX


#ifndef _FORMAT_HXX //autogen
#include <format.hxx>
#endif
class IntlWrapper;
namespace binfilter {


class SwFlyFrmFmt;


//Verbindung (Textfluss) zwischen zwei FlyFrms

class SwFmtChain: public SfxPoolItem
{
    SwClient aPrev, //Vorgaenger (SwFlyFrmFmt), wenn es diesen gibt.
             aNext; //Nachfolger (SwFlyFrmFmt), wenn es diesen gibt.


public:
    SwFmtChain() : SfxPoolItem( RES_CHAIN ) {}
    SwFmtChain( const SwFmtChain &rCpy );

    inline SwFmtChain &operator=( const SwFmtChain& );

    // "pure virtual Methoden" vom SfxPoolItem
    virtual int             operator==( const SfxPoolItem& ) const;
    virtual SfxPoolItem*    Clone( SfxItemPool* pPool = 0 ) const;
    virtual SfxPoolItem*    Create(SvStream &, USHORT nVer) const;
    virtual SvStream&       Store(SvStream &, USHORT nIVer) const;
    virtual USHORT          GetVersion( USHORT nFFVer ) const;

    virtual BOOL             QueryValue( ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 ) const;

    SwFlyFrmFmt* GetPrev() const { return (SwFlyFrmFmt*)aPrev.GetRegisteredIn(); }
    SwFlyFrmFmt* GetNext() const { return (SwFlyFrmFmt*)aNext.GetRegisteredIn(); }


    void SetPrev( SwFlyFrmFmt *pFmt );
    void SetNext( SwFlyFrmFmt *pFmt );
};

SwFmtChain &SwFmtChain::operator=( const SwFmtChain &rCpy )
{
    SetPrev( rCpy.GetPrev() );
    SetNext( rCpy.GetNext() );
    return *this;
}


#if !(defined(MACOSX) && ( __GNUC__ < 3 ))
// GrP moved to gcc_outl.cxx; revisit with gcc3
inline const SwFmtChain &SwAttrSet::GetChain(BOOL bInP) const
    { return (const SwFmtChain&)Get( RES_CHAIN,bInP); }

inline const SwFmtChain &SwFmt::GetChain(BOOL bInP) const
    { return aSet.GetChain(bInP); }
#endif

} //namespace binfilter
#endif

