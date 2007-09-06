/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_tblafmt.cxx,v $
 *
 *  $Revision: 1.10 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 12:04:00 $
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

#define ITEMID_BOXINFO      SID_ATTR_BORDER_INNER



#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

#ifndef _ZFORMAT_HXX //autogen
#include <svtools/zformat.hxx>
#endif
#ifndef _SVX_DIALOGS_HRC
#include <bf_svx/dialogs.hrc>
#endif

#define READ_OLDVERS        // erstmal noch alte Versionen lesen

#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _TBLAFMT_HXX
#include <tblafmt.hxx>
#endif
#ifndef _CELLATR_HXX
#include <cellatr.hxx>
#endif
#ifndef _ERRHDL_HXX //autogen
#include <errhdl.hxx>
#endif
#include "so3/staticbaseurl.hxx"
namespace binfilter {

// bis SO5PF
const USHORT AUTOFORMAT_ID_X        = 9501;
const USHORT AUTOFORMAT_ID_358      = 9601;
const USHORT AUTOFORMAT_DATA_ID_X   = 9502;

// ab SO5
//! in nachfolgenden Versionen muss der Betrag dieser IDs groesser sein
const USHORT AUTOFORMAT_ID_504      = 9801;
const USHORT AUTOFORMAT_DATA_ID_504 = 9802;

const USHORT AUTOFORMAT_ID_552      = 9901;
const USHORT AUTOFORMAT_DATA_ID_552 = 9902;

// --- from 641 on: CJK and CTL font settings
const USHORT AUTOFORMAT_ID_641      = 10001;
const USHORT AUTOFORMAT_DATA_ID_641 = 10002;

// current version
const USHORT AUTOFORMAT_ID          = AUTOFORMAT_ID_641;
const USHORT AUTOFORMAT_DATA_ID     = AUTOFORMAT_DATA_ID_641;


#ifdef READ_OLDVERS
const USHORT AUTOFORMAT_OLD_ID      = 8201;
const USHORT AUTOFORMAT_OLD_ID1     = 8301;
const USHORT AUTOFORMAT_OLD_DATA_ID = 8202;
#endif

}
