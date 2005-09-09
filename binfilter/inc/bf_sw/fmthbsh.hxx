/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: fmthbsh.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 16:04:59 $
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
#ifndef _FMTHBSH_HXX
#define _FMTHBSH_HXX


#ifndef _SFXPOOLITEM_HXX //autogen
#include <svtools/poolitem.hxx>
#endif
namespace binfilter {

// ATT_SOFTHYPH ******************************
// Attribut fuer benutzerdefinierte Trennstellen.

class SwFmtSoftHyph : public SfxPoolItem
{
public:
    SwFmtSoftHyph();

    // "pure virtual Methoden" vom SfxPoolItem
    virtual int operator==( const SfxPoolItem& ) const{DBG_BF_ASSERT(0, "STRIP"); return 0;}; //STRIP001    virtual int             operator==( const SfxPoolItem& ) const;
    virtual SfxPoolItem*    Clone( SfxItemPool* pPool = 0 ) const{DBG_BF_ASSERT(0, "STRIP");return NULL; }; //STRIP001  virtual SfxPoolItem*    Clone( SfxItemPool* pPool = 0 ) const;
    virtual SfxPoolItem*    Create(SvStream &, USHORT nVer) const;
    virtual SvStream&       Store(SvStream &, USHORT nIVer) const;

    inline SwFmtSoftHyph& operator=(const SwFmtSoftHyph& rSH) {
            return *this;
        }
};

// ATT_HARDBLANK ******************************
// Attribut fuer geschuetzte Leerzeichen.

class SwFmtHardBlank : public SfxPoolItem
{
    sal_Unicode cChar;
public:
    SwFmtHardBlank( sal_Unicode cCh, BOOL bCheck = TRUE );

    // "pure virtual Methoden" vom SfxPoolItem
    virtual int             operator==( const SfxPoolItem& ) const{DBG_BF_ASSERT(0, "STRIP"); return 0;}; //STRIP001    virtual int             operator==( const SfxPoolItem& ) const;
    virtual SfxPoolItem*    Clone( SfxItemPool* pPool = 0 ) const{DBG_BF_ASSERT(0, "STRIP"); return NULL;}; //STRIP001  virtual SfxPoolItem*    Clone( SfxItemPool* pPool = 0 ) const;
    virtual SfxPoolItem*    Create(SvStream &, USHORT nVer) const;
    virtual SvStream&       Store(SvStream &, USHORT nIVer) const;

    virtual USHORT           GetVersion( USHORT nFFVer ) const;

    inline sal_Unicode GetChar() const { return cChar; }
    inline SwFmtHardBlank& operator=(const SwFmtHardBlank& rHB)
    { cChar = rHB.GetChar(); return *this; }
};


} //namespace binfilter
#endif

