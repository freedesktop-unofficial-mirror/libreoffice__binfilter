/*************************************************************************
 *
 *  $RCSfile: writingmodeitem.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 08:29:28 $
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
#ifndef _SVX_WRITINGMODEITEM_HXX
#define _SVX_WRITINGMODEITEM_HXX

// include ---------------------------------------------------------------

#ifndef _COM_SUN_STAR_TEXT_WRITINGMODE_HPP_
#include <com/sun/star/text/WritingMode.hpp>
#endif

#ifndef _SFXINTITEM_HXX
#include <svtools/intitem.hxx>
#endif

#ifndef _SVDDEF_HXX
#include <bf_svx/svddef.hxx>
#endif
namespace binfilter {

// class SvxWritingModeItem ----------------------------------------------

class SvxWritingModeItem : public SfxUInt16Item
{
public:
    TYPEINFO();

    SvxWritingModeItem( ::com::sun::star::text::WritingMode eValue = ::com::sun::star::text::WritingMode_LR_TB, USHORT nWhich = SDRATTR_TEXTDIRECTION );
    virtual ~SvxWritingModeItem();

    SvxWritingModeItem& operator=( const SvxWritingModeItem& rItem );

    virtual SfxPoolItem*    Clone( SfxItemPool *pPool = 0 ) const;
//STRIP001  virtual SfxPoolItem*    Create(SvStream &, USHORT) const;
//STRIP001  virtual SvStream&       Store(SvStream & rStrm, USHORT nIVer) const;
    virtual USHORT          GetVersion( USHORT nFileVersion ) const;
    virtual int             operator==( const SfxPoolItem& ) const;

//STRIP001  virtual SfxItemPresentation GetPresentation( SfxItemPresentation ePres,
//STRIP001                                  SfxMapUnit eCoreMetric,
//STRIP001                                  SfxMapUnit ePresMetric,
//STRIP001                                  String &rText,
//STRIP001                                     const IntlWrapper * = 0 ) const;

//STRIP001  virtual sal_Bool PutValue( const ::com::sun::star::uno::Any& rVal,
//STRIP001                                  BYTE nMemberId );
    virtual sal_Bool QueryValue( ::com::sun::star::uno::Any& rVal,
                                BYTE nMemberId ) const;
};

}//end of namespace binfilter
#endif // #ifndef _SVX_WRITINGMODEITEM_HXX

