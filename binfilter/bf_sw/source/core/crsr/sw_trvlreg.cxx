/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_trvlreg.cxx,v $
 *
 *  $Revision: 1.8 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 11:55:49 $
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

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

#ifndef _CRSRSH_HXX
#include <crsrsh.hxx>
#endif
#ifndef _VISCRS_HXX
#include <viscrs.hxx>
#endif
namespace binfilter {



/*N*/ FASTBOOL GotoPrevRegion( SwPaM& rCurCrsr, SwPosRegion fnPosRegion,
/*N*/                       FASTBOOL bInReadOnly )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/   return FALSE;
/*N*/ }


/*N*/ FASTBOOL GotoNextRegion( SwPaM& rCurCrsr, SwPosRegion fnPosRegion,
/*N*/                       FASTBOOL bInReadOnly )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/   return FALSE;
/*N*/ }


/*N*/ FASTBOOL GotoCurrRegion( SwPaM& rCurCrsr, SwPosRegion fnPosRegion,
/*N*/                       FASTBOOL bInReadOnly )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); return FALSE; //STRIP001
/*N*/ }


/*N*/ FASTBOOL GotoCurrRegionAndSkip( SwPaM& rCurCrsr, SwPosRegion fnPosRegion,
/*N*/                               FASTBOOL bInReadOnly )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/   return FALSE;
/*N*/ }
}
