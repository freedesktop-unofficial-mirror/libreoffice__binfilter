/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_findtxt.cxx,v $
 *
 *  $Revision: 1.7 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 11:54:45 $
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



#ifdef _MSC_VER
#pragma hdrstop
#endif

#define _SVSTDARR_ULONGS


#ifndef _TXTFLD_HXX //autogen
#include <txtfld.hxx>
#endif
#ifndef _SWCRSR_HXX
#include <swcrsr.hxx>
#endif

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

namespace binfilter {

using namespace ::com::sun::star;
using namespace ::com::sun::star::util;







// Parameter fuers Suchen und Ersetzen von Text






/*M*/ ULONG SwCursor::Find( const SearchOptions& rSearchOpt,
/*M*/                       SwDocPositions nStart, SwDocPositions nEnde,
/*M*/                         BOOL& bCancel,
/*M*/                       FindRanges eFndRngs, int bReplace )
/*M*/ {DBG_BF_ASSERT(0, "STRIP"); return 0;//STRIP001
/*M*/ }



}
