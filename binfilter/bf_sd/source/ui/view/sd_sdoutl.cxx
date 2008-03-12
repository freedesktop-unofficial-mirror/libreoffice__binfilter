/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sd_sdoutl.cxx,v $
 *
 *  $Revision: 1.7 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 07:59:05 $
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

#include <bf_sfx2/app.hxx>
#include <bf_svx/editstat.hxx>
#include <bf_svx/unolingu.hxx>
#include <bf_svx/eeitem.hxx>
#include <bf_svx/forbiddencharacterstable.hxx>

#include "sdoutl.hxx"
#include "drawdoc.hxx"
#include "sdmod.hxx"

class SfxStyleSheetPool;

namespace binfilter {

SdOutliner::SdOutliner( SdDrawDocument* pDoc, USHORT nMode )
: SdrOutliner( &pDoc->GetItemPool(), nMode )
{
    SetStyleSheetPool((SfxStyleSheetPool*) pDoc->GetStyleSheetPool());
    SetEditTextObjectPool( &pDoc->GetItemPool() );
    SetCalcFieldValueHdl(LINK(SD_MOD(), SdModule, CalcFieldValueHdl));
    SetForbiddenCharsTable( pDoc->GetForbiddenCharsTable() );

    ULONG nCntrl = GetControlWord();
    nCntrl |= EE_CNTRL_ALLOWBIGOBJS;
    nCntrl |= EE_CNTRL_URLSFXEXECUTE;
    nCntrl |= EE_CNTRL_MARKFIELDS;
    nCntrl |= EE_CNTRL_AUTOCORRECT;
    nCntrl |= EE_CNTRL_NOREDLINES;
    nCntrl &= ~EE_CNTRL_ONLINESPELLING;

    SetControlWord(nCntrl);

    SetDefaultLanguage( Application::GetSettings().GetLanguage() );
}

SdOutliner::~SdOutliner()
{
}

}

