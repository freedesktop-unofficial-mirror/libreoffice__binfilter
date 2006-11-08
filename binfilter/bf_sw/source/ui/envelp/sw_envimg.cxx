/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_envimg.cxx,v $
 *
 *  $Revision: 1.7 $
 *
 *  last change: $Author: kz $ $Date: 2006-11-08 12:45:40 $
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

#ifndef _SWTYPES_HXX
#include <swtypes.hxx>
#endif
#ifndef _ENVIMG_HXX
#include <envimg.hxx>
#endif

#ifndef _CMDID_H
#include <cmdid.h>
#endif
namespace binfilter {

#ifdef WIN
#define NEXTLINE  UniString::CreateFromAscii("\r\n")
#else
#define NEXTLINE  '\n'
#endif

using namespace utl;
using namespace rtl;
using namespace ::com::sun::star::uno;

#define C2U(cChar) OUString::createFromAscii(cChar)

/*N*/ TYPEINIT1_AUTOFACTORY( SwEnvItem, SfxPoolItem );

/*N*/ SwEnvItem::SwEnvItem() :
/*N*/   SfxPoolItem(FN_ENVELOP)
/*N*/ {
/*N*/ DBG_BF_ASSERT(0, "STRIP"); //STRIP001     aAddrText       = aEmptyStr;
/*N*/ }
// --------------------------------------------------------------------------
/*N*/ SwEnvItem::SwEnvItem(const SwEnvItem& rItem) :
/*N*/   SfxPoolItem(FN_ENVELOP),
/*N*/   aAddrText      (rItem.aAddrText),
/*N*/   bSend          (rItem.bSend),
/*N*/   aSendText      (rItem.aSendText),
/*N*/   lSendFromLeft  (rItem.lSendFromLeft),
/*N*/   lSendFromTop   (rItem.lSendFromTop),
/*N*/   lAddrFromLeft  (rItem.lAddrFromLeft),
/*N*/   lAddrFromTop   (rItem.lAddrFromTop),
/*N*/   lWidth         (rItem.lWidth),
/*N*/   lHeight        (rItem.lHeight),
/*N*/   eAlign         (rItem.eAlign),
/*N*/   bPrintFromAbove(rItem.bPrintFromAbove),
/*N*/   lShiftRight    (rItem.lShiftRight),
/*N*/   lShiftDown     (rItem.lShiftDown)
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/ }

// --------------------------------------------------------------------------
/*N*/ int SwEnvItem::operator ==(const SfxPoolItem& rItem) const
/*N*/ {
DBG_BF_ASSERT(0, "STRIP"); return 0;//STRIP001  const SwEnvItem& rEnv = (const SwEnvItem&) rItem;
/*N*/ }

// --------------------------------------------------------------------------
/*N*/ SfxPoolItem* SwEnvItem::Clone(SfxItemPool*) const
/*N*/ {
/*N*/   return new SwEnvItem(*this);
/*N*/ }
// --------------------------------------------------------------------------
}
