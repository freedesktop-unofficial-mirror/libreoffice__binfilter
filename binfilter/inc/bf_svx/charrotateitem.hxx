/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: charrotateitem.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 13:08:34 $
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
#ifndef _SVX_CHARROTATEITEM_HXX
#define _SVX_CHARROTATEITEM_HXX

// include ---------------------------------------------------------------

#ifndef _SFXINTITEM_HXX
#include <svtools/intitem.hxx>
#endif
#ifndef _SVX_SVXIDS_HRC
#include <bf_svx/svxids.hrc>
#endif
namespace binfilter {

// class SvxCharRotateItem ----------------------------------------------

/* [Description]

    This item defines a character rotation value (0,1 degree). Currently
    character can only be rotated 90,0 and 270,0 degrees.
    The flag FitToLine defines only a UI-Information -
    if true it must also create a SvxCharScaleItem.

*/

class SvxCharRotateItem : public SfxUInt16Item
{
    sal_Bool bFitToLine;
public:
    TYPEINFO();

    SvxCharRotateItem( sal_uInt16 nValue = 0,
                       sal_Bool bFitIntoLine = sal_False,
                       const sal_uInt16 nId = ITEMID_CHARROTATE );

/*NBFF*/    virtual SfxPoolItem*    Clone( SfxItemPool *pPool = 0 ) const;
/*NBFF*/    virtual SfxPoolItem*    Create(SvStream &, USHORT) const;
/*NBFF*/    virtual SvStream&       Store(SvStream & rStrm, USHORT nIVer) const;
    virtual USHORT          GetVersion( USHORT nFileVersion ) const;

/*NBFF*/    virtual SfxItemPresentation GetPresentation( SfxItemPresentation ePres,
/*NBFF*/                                    SfxMapUnit eCoreMetric,
/*NBFF*/                                    SfxMapUnit ePresMetric,
/*NBFF*/                                    String &rText,
/*NBFF*/                                     const IntlWrapper * = 0 ) const;

/*NBFF*/    virtual sal_Bool PutValue( const ::com::sun::star::uno::Any& rVal,
/*NBFF*/                                    BYTE nMemberId );
/*NBFF*/    virtual sal_Bool QueryValue( ::com::sun::star::uno::Any& rVal,
/*NBFF*/                                BYTE nMemberId ) const;

/*NBFF*/    inline SvxCharRotateItem& operator=( const SvxCharRotateItem& rItem )
/*NBFF*/    {
/*NBFF*/        SetValue( rItem.GetValue() );
/*NBFF*/        SetFitToLine( rItem.IsFitToLine() );
/*NBFF*/        return *this;
/*NBFF*/    }

/*NBFF*/    virtual int              operator==( const SfxPoolItem& ) const;

    // our currently only degree values
/*NBFF*/    void SetTopToBotton()                   { SetValue( 2700 ); }
/*NBFF*/    void SetBottomToTop()                   { SetValue(  900 ); }
/*NBFF*/    sal_Bool IsTopToBotton() const          { return 2700 == GetValue(); }
/*NBFF*/    sal_Bool IsBottomToTop() const          { return  900 == GetValue(); }
/*NBFF*/
/*NBFF*/    sal_Bool IsFitToLine() const            { return bFitToLine; }
/*NBFF*/    void SetFitToLine( sal_Bool b )         { bFitToLine = b; }
};

}//end of namespace binfilter
#endif

