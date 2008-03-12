/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sd_grdocsh.cxx,v $
 *
 *  $Revision: 1.9 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 07:35:21 $
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

#ifndef _SVXIDS_HRC
#include <bf_svx/svxids.hrc>
#endif
#define ITEMID_SEARCH                   SID_SEARCH_ITEM
#ifndef _SFXAPP_HXX
#include <bf_sfx2/app.hxx>
#endif


#ifndef _SO_CLSIDS_HXX //autogen
#include <comphelper/classids.hxx>
#endif

#ifdef _MSC_VER
#pragma hdrstop
#endif

#include "strings.hrc"
#include "glob.hrc"

#include "bf_sd/grdocsh.hxx"
#include "sdresid.hxx"

namespace binfilter
{

TYPEINIT1(SdGraphicDocShell, SdDrawDocShell);

SFX_IMPL_OBJECTFACTORY_LOD(SdGraphicDocShell, sdraw, SvGlobalName(BF_SO3_SDRAW_CLASSID), Sd)

SdGraphicDocShell::SdGraphicDocShell(SfxObjectCreateMode eMode, BOOL bDataObject, DocumentType eDocType)
: SdDrawDocShell(eMode, bDataObject, eDocType)
{
    SetStyleFamily( 2 );
}

SdGraphicDocShell::SdGraphicDocShell(SdDrawDocument* pDoc, SfxObjectCreateMode eMode, BOOL bDataObject, DocumentType eDocType)
: SdDrawDocShell(pDoc, eMode, bDataObject, eDocType)
{
    SetStyleFamily( 2 );
}

SdGraphicDocShell::~SdGraphicDocShell()
{
}

}
