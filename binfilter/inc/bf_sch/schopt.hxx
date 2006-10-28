/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: schopt.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 02:50:02 $
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

#ifndef _SCH_SCHOPT_HXX
#define _SCH_SCHOPT_HXX

// header for TYPEINFO
#ifndef _RTTI_HXX
#include <tools/rtti.hxx>
#endif
// header for ConfigItem
#ifndef _UTL_CONFIGITEM_HXX_
#include <unotools/configitem.hxx>
#endif
// header for SfxPoolItem
#ifndef _SFXPOOLITEM_HXX
#include <svtools/poolitem.hxx>
#endif
// header for Color
#ifndef _TOOLS_COLOR_HXX
#include <tools/color.hxx>
#endif
// header for Table
#ifndef _TOOLS_TABLE_HXX
#include <tools/table.hxx>
#endif
// header for XColorEntry
#ifndef _XTABLE_HXX
#include <bf_svx/xtable.hxx>   //STRIP002
#endif
namespace binfilter {

// --------------------
// default colors
// --------------------
class SchColorTable : private Table
{
public:
    SchColorTable();
    virtual ~SchColorTable() {}


    // make public
    Table::Count;

    // specialized methods from Table
    void            ClearAndDestroy();

    BOOL            Insert( ULONG nKey, XColorEntry* );
    XColorEntry*    Get( ULONG nKey ) const;

    Color           GetColor( ULONG nKey ) const;
    ColorData       GetColorData( ULONG nKey ) const;

    BOOL            operator ==( const SchColorTable& rCol ) const
                    { return Table::operator ==( rCol ); }
    BOOL            operator !=( const SchColorTable& rCol ) const
                    { return Table::operator !=( rCol ); }
};

// ====================
// all options
// ====================
class SchOptions : public ::utl::ConfigItem
{
private:
    SchColorTable       maDefColors;
    BOOL                mbIsInitialized;
    ::com::sun::star::uno::Sequence< ::rtl::OUString > maPropertyNames;

    ::com::sun::star::uno::Sequence< ::rtl::OUString > GetPropertyNames() const
        { return maPropertyNames; }
    BOOL RetrieveOptions();

public:
    SchOptions();
    virtual ~SchOptions();

    const SchColorTable& GetDefaultColors();

};

// ====================
// items
// ====================

} //namespace binfilter
#endif  // _SCH_SCHOPT_HXX

