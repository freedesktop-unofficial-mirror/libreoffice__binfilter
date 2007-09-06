/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_docstat.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 12:00:44 $
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

#ifndef _DOCSTAT_HXX
#include <docstat.hxx>
#endif
namespace binfilter {


/************************************************************************
 *                         SwDocStat::SwDocStat()
 ************************************************************************/

/*N*/ SwDocStat::SwDocStat() :
/*N*/   nTbl(0),
/*N*/   nGrf(0),
/*N*/   nOLE(0),
/*N*/   nPage(1),
/*N*/   nPara(1),
/*N*/   nWord(0),
/*N*/   nChar(0),
/*N*/   bModified(TRUE),
/*N*/   pInternStat(0)
/*N*/ {}

/************************************************************************
 *                         void SwDocStat::Reset()
 ************************************************************************/

/*N*/ void SwDocStat::Reset()
/*N*/ {
/*N*/   nTbl    = 0;
/*N*/   nGrf    = 0;
/*N*/   nOLE    = 0;
/*N*/   nPage   = 1;
/*N*/   nPara   = 1;
/*N*/   nWord   = 0;
/*N*/   nChar   = 0;
/*N*/   bModified = TRUE;
/*N*/   pInternStat = 0;
/*N*/ }

}
