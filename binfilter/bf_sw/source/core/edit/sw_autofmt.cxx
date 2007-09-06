/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_autofmt.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 12:09:02 $
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
#define _SVSTDARR_LONGS
#define _SVSTDARR_USHORTS

#include <ctype.h>
#ifndef _HINTIDS_HXX
#include <hintids.hxx>
#endif



#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

#ifndef _EDITSH_HXX
#include <editsh.hxx>
#endif

#ifndef _STATSTR_HRC
#include <statstr.hrc>
#endif
#ifndef _COMCORE_HRC
#include <comcore.hrc>
#endif

namespace binfilter {

//-------------------------------------------------------------------

//JP 16.12.99: definition:
//      from pos cPosEnDash to cPosEmDash all chars changed to endashes,
//      from pos cPosEmDash to cPosEnd    all chars changed to emdashes
//      all other chars are changed to the user configuration




/*N*/ SvxSwAutoFmtFlags* SwEditShell::pAutoFmtFlags = 0;

// Anzahl von Num-/Bullet-Absatzvorlagen. MAXLEVEL wird demnaechst auf
// x erhoeht, die Anzahl Vorlagen aber nicht (Ueberbleibsel aus <= 4.0)

    static BOOL  m_bAskForCancelUndoWhileBufferOverflow;
    static short m_nActionWhileAutoformatUndoBufferOverflow;


















































// ist ein Punkt am Ende ??


// loesche im Node Anfang oder/und Ende








        // loesche den vorherigen Absatz














        // dann lasse doch mal das AutoCorrect auf den akt. TextNode los






/*N*/ SvxSwAutoFmtFlags* SwEditShell::GetAutoFmtFlags()
/*N*/ {
/*N*/   if (!pAutoFmtFlags)
/*N*/       pAutoFmtFlags = new SvxSwAutoFmtFlags;
/*N*/
/*N*/   return pAutoFmtFlags;
/*N*/ }

/*N*/ void SwEditShell::SetAutoFmtFlags(SvxSwAutoFmtFlags * pFlags)
/*N*/ {
/*N*/   SvxSwAutoFmtFlags* pEditFlags = GetAutoFmtFlags();
/*N*/
/*N*/   pEditFlags->bSetNumRule     = pFlags->bSetNumRule;
/*N*/   pEditFlags->bChgEnumNum     = pFlags->bChgEnumNum;
/*N*/   pEditFlags->bSetBorder      = pFlags->bSetBorder;
/*N*/   pEditFlags->bCreateTable    = pFlags->bCreateTable;
/*N*/   pEditFlags->bReplaceStyles  = pFlags->bReplaceStyles;
/*N*/   pEditFlags->bAFmtByInpDelSpacesAtSttEnd =
/*N*/                                   pFlags->bAFmtByInpDelSpacesAtSttEnd;
/*N*/   pEditFlags->bAFmtByInpDelSpacesBetweenLines =
/*N*/                                   pFlags->bAFmtByInpDelSpacesBetweenLines;
/*N*/
/*N*/   //JP 15.12.98: BulletZeichen und Font in die "normalen" kopieren,
/*N*/   //          weil beim Autoformat nur mit diesen gearbeitet wird!
/*N*/   pEditFlags->cBullet             = pFlags->cByInputBullet;
/*N*/   pEditFlags->aBulletFont         = pFlags->aByInputBulletFont;
/*N*/   pEditFlags->cByInputBullet      = pFlags->cByInputBullet;
/*N*/   pEditFlags->aByInputBulletFont  = pFlags->aByInputBulletFont;
/*N*/ }

}
