/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: fmtfld.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 16:03:31 $
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
#ifndef _FMTFLD_HXX
#define _FMTFLD_HXX


#ifndef _SFXPOOLITEM_HXX //autogen
#include <svtools/poolitem.hxx>
#endif
#ifndef _CALBCK_HXX //autogen
#include <calbck.hxx>
#endif
namespace binfilter {

class SwField;
class SwTxtFld;
// ATT_FLD ***********************************

class SwFmtFld : public SfxPoolItem, public SwClient
{
    friend class SwTxtFld;
    friend void _InitCore();

    SwField *pField;
    SwTxtFld* pTxtAttr;     // mein TextAttribut
    SwFmtFld();             // das default-Attibut

    // geschuetzter CopyCtor
    SwFmtFld& operator=(const SwFmtFld& rFld);
public:
    TYPEINFO();

    SwFmtFld( const SwField &rFld );
    SwFmtFld( const SwFmtFld& rAttr );
    ~SwFmtFld();

    // "pure virtual Methoden" vom SfxPoolItem
    virtual int             operator==( const SfxPoolItem& ) const;
    virtual SfxPoolItem*    Clone( SfxItemPool* pPool = 0 ) const;
    virtual SfxPoolItem*    Create(SvStream &, USHORT nVer) const;
    virtual SvStream&       Store(SvStream &, USHORT nIVer) const;

    virtual void Modify( SfxPoolItem* pOld, SfxPoolItem* pNew );
    virtual BOOL GetInfo( SfxPoolItem& rInfo ) const;

    const SwField *GetFld() const   { return pField; }
    SwField *GetFld()               { return pField; }

    const SwTxtFld *GetTxtFld() const   { return pTxtAttr; }
    SwTxtFld *GetTxtFld()               { return pTxtAttr; }

    BOOL IsFldInDoc() const;
    BOOL IsProtect() const;
};


} //namespace binfilter
#endif

