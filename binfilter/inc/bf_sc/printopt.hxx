/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: printopt.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 02:39:14 $
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

};

//==================================================================
// item for the dialog / options page
//==================================================================


//==================================================================
// config item
//==================================================================

class ScPrintCfg : public ScPrintOptions, public ::utl::ConfigItem
{

public:
    ScPrintCfg();

    void            SetOptions( const ScPrintOptions& rNew ){DBG_BF_ASSERT(0, "STRIP");} //STRIP001     void            SetOptions( const ScPrintOptions& rNew );
};

} //namespace binfilter
#endif

