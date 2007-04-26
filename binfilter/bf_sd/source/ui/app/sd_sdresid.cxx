/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sd_sdresid.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2007-04-26 07:12:06 $
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

#pragma hdrstop

#ifndef _SHL_HXX //autogen
#include <tools/shl.hxx>
#endif

#include "sddll.hxx"
#include "sdresid.hxx"
namespace binfilter {


/*************************************************************************
|*
|* Ctor
|*
\************************************************************************/

/*N*/ SdResId::SdResId(USHORT nId) :
/*N*/   ResId(nId, *SD_MOD()->GetResMgr())
/*N*/ //    ResId(nId, *(ResMgr**) GetAppData(BF_SHL_DRAW))
/*N*/ {
/*N*/ }


/*************************************************************************
|*
|* 2.Ctor (kann entfallen)
|*
\************************************************************************/

/*N*/ SdResId::SdResId(USHORT nId, ResMgr* pMgr) :
/*N*/   ResId(nId, *pMgr)
/*N*/ {
/*N*/ }




}
