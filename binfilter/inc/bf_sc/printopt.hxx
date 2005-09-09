/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: printopt.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 11:22:32 $
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

#ifndef SC_PRINTOPT_HXX
#define SC_PRINTOPT_HXX

#ifndef _SFXPOOLITEM_HXX
#include <svtools/poolitem.hxx>
#endif

#ifndef _UTL_CONFIGITEM_HXX_
#include <unotools/configitem.hxx>
#endif
namespace binfilter {


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

class ScPrintCfg : public ScPrintOptions, public ::utl::ConfigItem
{
//STRIP001  ::com::sun::star::uno::Sequence<rtl::OUString> GetPropertyNames();

public:
    ScPrintCfg();

    void            SetOptions( const ScPrintOptions& rNew ){DBG_BF_ASSERT(0, "STRIP");} //STRIP001     void            SetOptions( const ScPrintOptions& rNew );
//STRIP001  void            OptionsChanged();   // after direct access to ScPrintOptions base class
//STRIP001
//STRIP001  virtual void    Commit();
};

} //namespace binfilter
#endif

