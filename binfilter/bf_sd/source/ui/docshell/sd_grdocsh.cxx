/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sd_grdocsh.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: obo $ $Date: 2007-07-17 10:05:27 $
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
#include <so3/clsids.hxx>
#endif

#pragma hdrstop

#include "app.hrc"
#include "strings.hrc"
#include "glob.hrc"

#include "grdocsh.hxx"
#include "sdresid.hxx"



/*************************************************************************
|*
|* SFX-Slotmaps und -Definitionen
|*
\************************************************************************/
namespace binfilter {

/*N*/ TYPEINIT1(SdGraphicDocShell, SdDrawDocShell);

/*N*/ SFX_IMPL_OBJECTFACTORY_LOD(SdGraphicDocShell, sdraw,
/*N*/                          SvGlobalName(BF_SO3_SDRAW_CLASSID), Sd)

/*************************************************************************
|*
|* Konstruktor 1
|*
\************************************************************************/

/*N*/ SdGraphicDocShell::SdGraphicDocShell(SfxObjectCreateMode eMode,
/*N*/                                    BOOL bDataObject,
/*N*/                                    DocumentType eDocType) :
/*N*/   SdDrawDocShell(eMode, bDataObject, eDocType)
/*N*/ {
/*N*/   SetStyleFamily( 2 ); //CL: eigentlich SFX_STYLE_FAMILY_PARA, aber der stylist ist sch....
/*N*/ }

/*************************************************************************
|*
|* Konstruktor 2
|*
\************************************************************************/

/*N*/ SdGraphicDocShell::SdGraphicDocShell(SdDrawDocument* pDoc, SfxObjectCreateMode eMode,
/*N*/                                    BOOL bDataObject,
/*N*/                                    DocumentType eDocType) :
/*N*/   SdDrawDocShell(pDoc, eMode, bDataObject, eDocType)
/*N*/ {
/*N*/   SetStyleFamily( 2 ); //CL: eigentlich SFX_STYLE_FAMILY_PARA, aber der stylist ist sch....
/*N*/ }

/*************************************************************************
|*
|* Destruktor
|*
\************************************************************************/

/*N*/ SdGraphicDocShell::~SdGraphicDocShell()
/*N*/ {
/*N*/ }



}
