/*************************************************************************
 *
 *  $RCSfile: algitem.hxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:23:35 $
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
#ifndef _SVX_ALGITEM_HXX
#define _SVX_ALGITEM_HXX

// include ---------------------------------------------------------------

#include <bf_svx/svxids.hrc>

#ifndef _SFXPOOLITEM_HXX //autogen
#include <svtools/poolitem.hxx>
#endif
#ifndef _SFXENUMITEM_HXX //autogen
#include <svtools/eitem.hxx>
#endif
#ifndef _SVX_SVXENUM_HXX
#include <bf_svx/svxenum.hxx>
#endif

class SvStream;

//------------------------------------------------------------------------

#ifdef ITEMID_HORJUSTIFY

class SvxHorJustifyItem: public SfxEnumItem
{
public:
    TYPEINFO();

    SvxHorJustifyItem(
        const SvxCellHorJustify eJustify = SVX_HOR_JUSTIFY_STANDARD,
        const USHORT nId = ITEMID_HORJUSTIFY );

//STRIP001  virtual SfxItemPresentation GetPresentation( SfxItemPresentation ePres,
//STRIP001                                  SfxMapUnit eCoreMetric,
//STRIP001                                  SfxMapUnit ePresMetric,
//STRIP001                                     String &rText, const IntlWrapper * = 0 ) const;

    virtual sal_Bool             QueryValue( com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 ) const;
    virtual sal_Bool             PutValue( const com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 );

    virtual USHORT          GetValueCount() const;
//STRIP001  virtual String          GetValueText( USHORT nVal ) const;
    virtual SfxPoolItem*    Clone( SfxItemPool *pPool = 0 ) const;
    virtual SfxPoolItem*    Create( SvStream& rStream, USHORT nVer ) const;

    inline  SvxHorJustifyItem& operator=(const SvxHorJustifyItem& rHorJustify)
            {
                SetValue( rHorJustify.GetValue() );
                return *this;
            }
};

#endif

//------------------------------------------------------------------------

#ifdef ITEMID_VERJUSTIFY

class SvxVerJustifyItem: public SfxEnumItem
{
public:
    TYPEINFO();

    SvxVerJustifyItem(
        const SvxCellVerJustify eJustify = SVX_VER_JUSTIFY_STANDARD,
        const USHORT nId = ITEMID_VERJUSTIFY );

//STRIP001  virtual SfxItemPresentation GetPresentation( SfxItemPresentation ePres,
//STRIP001                                  SfxMapUnit eCoreMetric,
//STRIP001                                  SfxMapUnit ePresMetric,
//STRIP001                                     String &rText, const IntlWrapper * = 0 ) const;

    virtual sal_Bool             QueryValue( com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 ) const;
    virtual sal_Bool             PutValue( const com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 );

    virtual USHORT          GetValueCount() const;
//STRIP001  virtual String          GetValueText( USHORT nVal ) const;
    virtual SfxPoolItem*    Clone( SfxItemPool *pPool = 0 ) const;
    virtual SfxPoolItem*    Create( SvStream& rStream, USHORT nVer ) const;

    inline  SvxVerJustifyItem& operator=(const SvxVerJustifyItem& rVerJustify)
            {
                SetValue( rVerJustify.GetValue() );
                return *this;
            }
};

#endif

//------------------------------------------------------------------------

#ifdef ITEMID_ORIENTATION

class SvxOrientationItem: public SfxEnumItem
{
public:
    TYPEINFO();

    SvxOrientationItem(
        const SvxCellOrientation eOrientation = SVX_ORIENTATION_STANDARD,
        const USHORT nId = ITEMID_ORIENTATION );

//STRIP001  virtual SfxItemPresentation GetPresentation( SfxItemPresentation ePres,
//STRIP001                                  SfxMapUnit eCoreMetric,
//STRIP001                                  SfxMapUnit ePresMetric,
//STRIP001                                     String &rText, const IntlWrapper * = 0 ) const;

    virtual sal_Bool             QueryValue( com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 ) const;
    virtual sal_Bool             PutValue( const com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 );

    virtual USHORT          GetValueCount() const;
//STRIP001  virtual String          GetValueText( USHORT nVal ) const;
    virtual SfxPoolItem*    Clone( SfxItemPool *pPool = 0 ) const;
    virtual SfxPoolItem*    Create( SvStream& rStream, USHORT nVer ) const;

    inline  SvxOrientationItem& operator=(const SvxOrientationItem& rOrientation)
            {
                SetValue( rOrientation.GetValue() );
                return *this;
            }
};

#endif

//------------------------------------------------------------------------

#ifdef ITEMID_MARGIN

class SvxMarginItem: public SfxPoolItem
{
    INT16       nLeftMargin;
    INT16       nTopMargin;
    INT16       nRightMargin;
    INT16       nBottomMargin;
public:
    TYPEINFO();
    SvxMarginItem( const USHORT nId = ITEMID_MARGIN );
    SvxMarginItem( INT16 nLeft, INT16 nTop = 0,
                   INT16 nRight = 0, INT16 nBottom = 0,
                   const USHORT nId = ITEMID_MARGIN );
    SvxMarginItem( const SvxMarginItem& );

//STRIP001  virtual SfxItemPresentation GetPresentation( SfxItemPresentation ePres,
//STRIP001                                  SfxMapUnit eCoreMetric,
//STRIP001                                  SfxMapUnit ePresMetric,
//STRIP001                                     String &rText, const IntlWrapper * = 0 ) const;

    virtual int              operator==( const SfxPoolItem& ) const;
    virtual SfxPoolItem*     Clone( SfxItemPool *pPool = 0 ) const;
    virtual SfxPoolItem*     Create( SvStream& rStream, USHORT nVer ) const;
    virtual SvStream&        Store( SvStream&, USHORT nItemVersion ) const;

    virtual sal_Bool             QueryValue( com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 ) const;
    virtual sal_Bool             PutValue( const com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 );

            INT16           GetLeftMargin() const {return nLeftMargin; }
//STRIP001          BOOL            SetLeftMargin(INT16 nLeft);
            INT16           GetTopMargin() const {return nTopMargin; }
//STRIP001          BOOL            SetTopMargin(INT16 nTop);
            INT16           GetRightMargin() const {return nRightMargin; }
//STRIP001          BOOL            SetRightMargin(INT16 nRight);
            INT16           GetBottomMargin() const {return nBottomMargin; }
//STRIP001          BOOL            SetBottomMargin(INT16 nBottom);

    inline  SvxMarginItem& operator=(const SvxMarginItem& rMargin)
            {
                nLeftMargin = rMargin.nLeftMargin;
                nTopMargin = rMargin.nTopMargin;
                nRightMargin = rMargin.nRightMargin;
                nBottomMargin = rMargin.nBottomMargin;
                return *this;
            }
};

#endif

#endif

