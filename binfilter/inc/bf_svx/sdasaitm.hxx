/*************************************************************************
 *
 *  $RCSfile: sdasaitm.hxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:23:38 $
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

#ifndef _SDASAITM_HXX
#define _SDASAITM_HXX

#ifndef _SFXPOOLITEM_HXX //autogen
#include <svtools/poolitem.hxx>
#endif
#ifndef _LIST_HXX
#include <tools/list.hxx>
#endif

class SdrAutoShapeAdjustmentValue
{
    sal_uInt32  nValue;

    friend class SdrAutoShapeAdjustmentItem;

    public :

        void        SetValue( sal_Int32 nVal ) { nValue = nVal; };
        sal_Int32   GetValue() const { return nValue; };

};

class SdrAutoShapeAdjustmentItem : public SfxPoolItem
{
            List    aAdjustmentValueList;

    public :

            TYPEINFO();
            SdrAutoShapeAdjustmentItem();
            SdrAutoShapeAdjustmentItem( SvStream& rIn, sal_uInt16 nVersion );
            ~SdrAutoShapeAdjustmentItem();

            virtual int                 operator==( const SfxPoolItem& ) const;
//STRIP001          virtual SfxItemPresentation GetPresentation(SfxItemPresentation ePresentation,
//STRIP001                                          SfxMapUnit eCoreMetric, SfxMapUnit ePresentationMetric,
//STRIP001                                                 String &rText, const IntlWrapper * = 0) const;
            virtual SfxPoolItem*        Create( SvStream&, sal_uInt16 nItem ) const;
            virtual SvStream&           Store( SvStream&, sal_uInt16 nVersion ) const;
            virtual SfxPoolItem*        Clone( SfxItemPool* pPool = NULL ) const;
            virtual sal_uInt16          GetVersion( sal_uInt16 nFileFormatVersion ) const;

//STRIP001          virtual sal_Bool            QueryValue( com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 ) const;
//STRIP001          virtual sal_Bool            PutValue( const com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 );

#ifdef SDR_ISPOOLABLE
            virtual int IsPoolable() const;
#endif

            sal_uInt32                          GetCount() const { return aAdjustmentValueList.Count(); };
//STRIP001          const SdrAutoShapeAdjustmentValue&  GetValue( sal_uInt32 nIndex ) const;
//STRIP001          void                                SetValue( sal_uInt32 nIndex,
//STRIP001                                                      const SdrAutoShapeAdjustmentValue& rVal );
};

#endif

