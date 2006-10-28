/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: fmtline.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 04:44:28 $
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
#ifndef SW_FMTLINE_HXX
#define SW_FMTLINE_HXX


#ifndef _FORMAT_HXX //autogen
#include <format.hxx>
#endif
class IntlWrapper;
namespace binfilter {


class SwFmtLineNumber: public SfxPoolItem
{
    ULONG nStartValue   :24; //Startwert fuer den Absatz, 0 == kein Startwert
    ULONG bCountLines   :1;  //Zeilen des Absatzes sollen mitgezaehlt werden.

public:
    SwFmtLineNumber();
    ~SwFmtLineNumber();

    TYPEINFO();

    // "pure virtual Methoden" vom SfxPoolItem
    virtual int             operator==( const SfxPoolItem& ) const;
    virtual SfxPoolItem*    Clone( SfxItemPool* pPool = 0 ) const;
    virtual SfxPoolItem*    Create(SvStream &, USHORT nVer) const;
    virtual SvStream&       Store(SvStream &, USHORT nIVer) const;
    virtual USHORT           GetVersion( USHORT nFFVer ) const;
    virtual BOOL             QueryValue( ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 ) const;
    virtual BOOL             PutValue( const ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 );

    ULONG GetStartValue() const { return nStartValue; }
    BOOL  IsCount()       const { return bCountLines != 0; }

    void SetStartValue( ULONG nNew ) { nStartValue = nNew; }
    void SetCountLines( BOOL b )     { bCountLines = b;    }
};

#if !(defined(MACOSX) && ( __GNUC__ < 3 ))
// GrP moved to gcc_outl.cxx; revisit with gcc3
inline const SwFmtLineNumber &SwAttrSet::GetLineNumber(BOOL bInP) const
    { return (const SwFmtLineNumber&)Get( RES_LINENUMBER,bInP); }

inline const SwFmtLineNumber &SwFmt::GetLineNumber(BOOL bInP) const
    { return aSet.GetLineNumber(bInP); }
#endif

} //namespace binfilter
#endif

