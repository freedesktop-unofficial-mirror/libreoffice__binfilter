/*************************************************************************
 *
 *  $RCSfile: sch_stlsheet.cxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: aw $ $Date: 2003-10-02 14:55:54 $
 *
 *  The Contents of this file are made available subject to the terms of
 *  either of the following licenses
 *
 *         - GNU Lesser General Public License Version 2.1
 *         - Sun Industry Standards Source License Version 1.1
 *
 *  Sun Microsystems Inc., October, 2000
 *
 *  GNU Lesser General Public License Version 2.1
 *  =============================================
 *  Copyright 2000 by Sun Microsystems, Inc.
 *  901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License version 2.1, as published by the Free Software Foundation.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *  MA  02111-1307  USA
 *
 *
 *  Sun Industry Standards Source License Version 1.1
 *  =================================================
 *  The contents of this file are subject to the Sun Industry Standards
 *  Source License Version 1.1 (the "License"); You may not use this file
 *  except in compliance with the License. You may obtain a copy of the
 *  License at http://www.openoffice.org/license.html.
 *
 *  Software provided under this License is provided on an "AS IS" basis,
 *  WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING,
 *  WITHOUT LIMITATION, WARRANTIES THAT THE SOFTWARE IS FREE OF DEFECTS,
 *  MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE, OR NON-INFRINGING.
 *  See the License for the specific provisions governing your rights and
 *  obligations concerning the Software.
 *
 *  The Initial Developer of the Original Code is: Sun Microsystems, Inc.
 *
 *  Copyright: 2000 by Sun Microsystems, Inc.
 *
 *  All Rights Reserved.
 *
 *  Contributor(s): _______________________________________
 *
 *
 ************************************************************************/

#pragma hdrstop

#ifndef _EEITEM_HXX //autogen
#include <bf_svx/eeitem.hxx>
#endif

#ifndef _XDEF_HXX //autogen
#include <bf_svx/xdef.hxx>
#endif

#ifndef _SFXSTYLE_HXX //autogen
#include <svtools/style.hxx>
#endif

#ifndef _SFXITEMSET_HXX //autogen
#include <svtools/itemset.hxx>
#endif

#ifndef _SFXSMPLHINT_HXX //autogen
#include <svtools/smplhint.hxx>
#endif

#include "stlsheet.hxx"

/*N*/ TYPEINIT1(SchStyleSheet, SfxStyleSheet);


/*************************************************************************
|*
|* Ctor
|*
\************************************************************************/

/*N*/ SchStyleSheet::SchStyleSheet(const String& rName, SfxStyleSheetBasePool& rPool,
/*N*/                            SfxStyleFamily eFamily, USHORT nMask) :
/*N*/   SfxStyleSheet(rName, rPool, eFamily, nMask)
/*N*/ {
/*N*/ }

/*************************************************************************
|*
|* Dtor
|*
\************************************************************************/

/*N*/ SchStyleSheet::~SchStyleSheet()
/*N*/ {
/*N*/ }

/*************************************************************************
|*
|* Load
|*
\************************************************************************/

/*N*/ void SchStyleSheet::Load (SvStream& rIn, USHORT nVersion)
/*N*/ {
/*N*/ }

/*************************************************************************
|*
|* Store
|*
\************************************************************************/

/*N*/ void SchStyleSheet::Store(SvStream& rOut)
/*N*/ {
/*N*/ }

/*************************************************************************
|*
|* Parent setzen
|*
\************************************************************************/

/*N*/ BOOL SchStyleSheet::SetParent(const String& rParentName)
/*N*/ {
/*N*/   if (SfxStyleSheet::SetParent(rParentName))
/*N*/   {
/*N*/       SfxStyleSheetBase* pStyle = rPool.Find(rParentName, nFamily);
/*N*/
/*N*/       if (pStyle)
/*N*/       {
/*?*/           SfxItemSet& rParentSet = pStyle->GetItemSet();
/*?*/           GetItemSet().SetParent(&rParentSet);
/*?*/           Broadcast(SfxSimpleHint(SFX_HINT_DATACHANGED));
/*?*/
/*?*/           return TRUE;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   return FALSE;
/*N*/ }

/*************************************************************************
|*
|* ItemSet ggfs. erzeugen und herausreichen
|*
\************************************************************************/

/*N*/ SfxItemSet& SchStyleSheet::GetItemSet()
/*N*/ {
/*N*/   if (!pSet)
/*N*/   {
/*N*/       USHORT nWhichPairTable[] = { XATTR_LINE_FIRST, XATTR_LINE_LAST,
/*N*/                                    XATTR_FILL_FIRST, XATTR_FILL_LAST,
/*N*/                                    EE_PARA_START, EE_CHAR_END,
/*N*/                                    (USHORT)0 };
/*N*/
/*N*/       pSet = new SfxItemSet(GetPool().GetPool(), nWhichPairTable);
/*N*/       bMySet = TRUE; //Eigentum erklaeren, damit der DTor der Basisklasse den
/*N*/                      //Set wieder abraeumt.
/*N*/   }
/*N*/
/*N*/   return *pSet;
/*N*/ }

/*************************************************************************
|*
|* IsUsed(), wird an Listeners erkannt
|*
\************************************************************************/

//STRIP001 BOOL SchStyleSheet::IsUsed() const
//STRIP001 {
//STRIP001  return HasListeners();
//STRIP001 }

/*************************************************************************
|*
|*
|*
\************************************************************************/

//STRIP001 BOOL SchStyleSheet::HasFollowSupport() const
//STRIP001 {
//STRIP001  return FALSE;
//STRIP001 }

/*************************************************************************
|*
|*
|*
\************************************************************************/

//STRIP001 BOOL SchStyleSheet::HasParentSupport() const
//STRIP001 {
//STRIP001  return TRUE;
//STRIP001 }



