/*************************************************************************
 *
 *  $RCSfile: charrotateitem.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: hjs $ $Date: 2004-06-28 12:36:31 $
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

