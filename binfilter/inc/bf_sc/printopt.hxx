/*************************************************************************
 *
 *  $RCSfile: printopt.hxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:23:20 $
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

#ifndef SC_PRINTOPT_HXX
#define SC_PRINTOPT_HXX

#ifndef _SFXPOOLITEM_HXX
#include <svtools/poolitem.hxx>
#endif

#ifndef _UTL_CONFIGITEM_HXX_
#include <unotools/configitem.hxx>
#endif


class ScPrintOptions
{
private:
    BOOL    bSkipEmpty;
    BOOL    bAllSheets;

public:
                ScPrintOptions();
                ScPrintOptions( const ScPrintOptions& rCpy );
                ~ScPrintOptions();

    BOOL    GetSkipEmpty() const            { return bSkipEmpty; }
    void    SetSkipEmpty( BOOL bVal )       { bSkipEmpty = bVal; }
    BOOL    GetAllSheets() const            { return bAllSheets; }
    void    SetAllSheets( BOOL bVal )       { bAllSheets = bVal; }

    void    SetDefaults();

//STRIP001  const ScPrintOptions&   operator=  ( const ScPrintOptions& rCpy );
//STRIP001  int                     operator== ( const ScPrintOptions& rOpt ) const;
//STRIP001  int                     operator!= ( const ScPrintOptions& rOpt ) const;
};

//==================================================================
// item for the dialog / options page
//==================================================================

//STRIP001 class ScTpPrintItem : public SfxPoolItem
//STRIP001 {
//STRIP001 public:
//STRIP001              TYPEINFO();
//STRIP001              ScTpPrintItem( USHORT nWhich );
//STRIP001              ScTpPrintItem( USHORT nWhich,
//STRIP001                             const ScPrintOptions& rOpt );
//STRIP001              ScTpPrintItem( const ScTpPrintItem& rItem );
//STRIP001              ~ScTpPrintItem();
//STRIP001
//STRIP001  virtual String          GetValueText() const;
//STRIP001  virtual int             operator==( const SfxPoolItem& ) const;
//STRIP001  virtual SfxPoolItem*    Clone( SfxItemPool *pPool = 0 ) const;
//STRIP001
//STRIP001  const ScPrintOptions&   GetPrintOptions() const { return theOptions; }
//STRIP001
//STRIP001 private:
//STRIP001  ScPrintOptions theOptions;
//STRIP001 };

//==================================================================
// config item
//==================================================================

class ScPrintCfg : public ScPrintOptions, public utl::ConfigItem
{
//STRIP001  com::sun::star::uno::Sequence<rtl::OUString> GetPropertyNames();

public:
    ScPrintCfg();

    void            SetOptions( const ScPrintOptions& rNew ){DBG_ASSERT(0, "STRIP");} //STRIP001    void            SetOptions( const ScPrintOptions& rNew );
//STRIP001  void            OptionsChanged();   // after direct access to ScPrintOptions base class
//STRIP001
//STRIP001  virtual void    Commit();
};

#endif

