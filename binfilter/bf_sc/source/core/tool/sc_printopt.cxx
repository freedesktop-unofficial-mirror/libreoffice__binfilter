/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sc_printopt.cxx,v $
 *
 *  $Revision: 1.7 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 10:48:48 $
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

#ifdef PCH
#endif

#ifdef _MSC_VER
#pragma hdrstop
#endif


#include "printopt.hxx"
namespace binfilter {

using namespace utl;
using namespace rtl;
using namespace ::com::sun::star::uno;

// -----------------------------------------------------------------------


// -----------------------------------------------------------------------

/*N*/ ScPrintOptions::ScPrintOptions()
/*N*/ {
/*N*/   SetDefaults();
/*N*/ }

/*N*/ ScPrintOptions::ScPrintOptions( const ScPrintOptions& rCpy ) :
/*N*/   bSkipEmpty( rCpy.bSkipEmpty ),
/*N*/   bAllSheets( rCpy.bAllSheets )
/*N*/ {
/*N*/ }

/*N*/ ScPrintOptions::~ScPrintOptions()
/*N*/ {
/*N*/ }

/*N*/ void ScPrintOptions::SetDefaults()
/*N*/ {
/*N*/   bSkipEmpty = FALSE;
/*N*/   bAllSheets = TRUE;
/*N*/ }




// -----------------------------------------------------------------------








// -----------------------------------------------------------------------

#define CFGPATH_PRINT           "Office.Calc/Print"

#define SCPRINTOPT_EMPTYPAGES       0
#define SCPRINTOPT_ALLSHEETS        1
#define SCPRINTOPT_COUNT            2


/*N*/ ScPrintCfg::ScPrintCfg() :
/*N*/   ConfigItem( OUString::createFromAscii( CFGPATH_PRINT ) )
/*N*/ {
    DBG_BF_ASSERT(0, "STRIP"); //STRIP001 Sequence<OUString> aNames = GetPropertyNames();
/*N*/ }






}
