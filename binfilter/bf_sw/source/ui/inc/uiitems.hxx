/*************************************************************************
 *
 *  $RCSfile: uiitems.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:55:46 $
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
#ifndef _UIITEMS_HXX
#define _UIITEMS_HXX

#include "pagedesc.hxx"
#include "cmdid.h"
#ifndef _SFXINTITEM_HXX
#include <svtools/intitem.hxx>
#endif
class IntlWrapper;
namespace binfilter {
class SwNumRule;


/*--------------------------------------------------------------------
    Beschreibung: Container fuer FootNote
 --------------------------------------------------------------------*/
class SwPageFtnInfoItem : public SfxPoolItem
{
    SwPageFtnInfo aFtnInfo;

public:

    SwPageFtnInfoItem(const USHORT nId, SwPageFtnInfo& rInfo);
    SwPageFtnInfoItem(const SwPageFtnInfoItem& rItem );
    ~SwPageFtnInfoItem();

    virtual SfxPoolItem*    Clone( SfxItemPool *pPool = 0 ) const;
    virtual int             operator==( const SfxPoolItem& ) const;
//STRIP001  virtual SfxItemPresentation GetPresentation( SfxItemPresentation ePres,
//STRIP001                                  SfxMapUnit eCoreMetric,
//STRIP001                                  SfxMapUnit ePresMetric,
//STRIP001                                  String &rText,
//STRIP001                                     const IntlWrapper*    pIntl = 0 ) const;

    virtual BOOL             QueryValue( ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 ) const;
    virtual BOOL             PutValue( const ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 );

    SwPageFtnInfo& GetPageFtnInfo()             { return aFtnInfo; }
    const SwPageFtnInfo& GetPageFtnInfo() const { return aFtnInfo; }
    void SetPageFtnInfo(SwPageFtnInfo& rInf)    { aFtnInfo = rInf; }
};

/*******************************************************************/

//STRIP001 class SwPtrItem : public SfxPoolItem
//STRIP001 {
//STRIP001  void* pMisc;

//STRIP001 public:
//STRIP001  SwPtrItem( const USHORT nId = FN_PARAM_GRF_DIALOG, void* pPtr = 0);
//STRIP001  SwPtrItem( const SwPtrItem& rItem );

//STRIP001  virtual SfxPoolItem*    Clone( SfxItemPool *pPool = 0 ) const;
//STRIP001  virtual int             operator==( const SfxPoolItem& ) const;

//STRIP001  void    SetValue(void * pPtr)   { pMisc= pPtr; }
//STRIP001  void*   GetValue() const        { return pMisc; }
//STRIP001 };

/*******************************************************************/

//STRIP001 class SwUINumRuleItem : public SfxPoolItem
//STRIP001 {
//STRIP001  SwNumRule* pRule;

//STRIP001 public:
//STRIP001  SwUINumRuleItem( const String& rName, const USHORT = FN_PARAM_ACT_NUMBER);
//STRIP001  SwUINumRuleItem( const SwNumRule& rRule, const USHORT = FN_PARAM_ACT_NUMBER);
//STRIP001  SwUINumRuleItem( const SwUINumRuleItem& rItem );
//STRIP001  virtual ~SwUINumRuleItem();

//STRIP001  virtual SfxPoolItem*    Clone( SfxItemPool *pPool = 0 ) const;
//STRIP001  virtual int             operator==( const SfxPoolItem& ) const;

//STRIP001  virtual BOOL             QueryValue( ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 ) const;
//STRIP001  virtual BOOL             PutValue( const ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 );

//STRIP001  const SwNumRule* GetNumRule() const         { return pRule; }
//STRIP001        SwNumRule* GetNumRule()               { return pRule; }
//STRIP001 };

/* -----------------17.06.98 17:40-------------------
 *
 * --------------------------------------------------*/
//STRIP001 class SwBackgroundDestinationItem : public SfxUInt16Item
//STRIP001 {
//STRIP001 public:
//STRIP001  SwBackgroundDestinationItem(USHORT  nWhich, USHORT nValue);

//STRIP001  virtual SfxPoolItem*     Clone( SfxItemPool *pPool = 0 ) const;
//STRIP001 };

} //namespace binfilter
#endif // _UIITEMS_HXX
