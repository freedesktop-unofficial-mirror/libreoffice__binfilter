/*************************************************************************
 *
 *  $RCSfile: sd_grdocsh.cxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:19:33 $
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

#ifndef _SVXIDS_HRC
#include <bf_svx/svxids.hrc>
#endif
#define ITEMID_SEARCH                   SID_SEARCH_ITEM
#ifndef _SFXAPP_HXX
#include <bf_sfx2/app.hxx>
#endif
#ifndef _SVX_SRCHITEM_HXX
#include <bf_svx/srchitem.hxx>
#endif

#ifndef _GLOBNAME_HXX //autogen
#include <tools/globname.hxx>
#endif

#ifndef _SO_CLSIDS_HXX //autogen
#include <so3/clsids.hxx>
#endif

#pragma hdrstop

#include "app.hrc"
#include "strings.hrc"
#include "glob.hrc"

#include "grdocsh.hxx"
#include "docshell.hxx"
#include "drawdoc.hxx"
#include "sdresid.hxx"



/*************************************************************************
|*
|* SFX-Slotmaps und -Definitionen
|*
\************************************************************************/
/*N*/ TYPEINIT1(SdGraphicDocShell, SdDrawDocShell);

#define SdGraphicDocShell
#include "sdgslots.hxx"


/*N*/ SFX_IMPL_INTERFACE(SdGraphicDocShell, SfxObjectShell, SdResId(0))
/*N*/ {
/*N*/   SFX_CHILDWINDOW_REGISTRATION(SID_SEARCH_DLG);
/*N*/ }

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



