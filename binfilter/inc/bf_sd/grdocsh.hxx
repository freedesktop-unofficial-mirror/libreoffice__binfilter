/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: grdocsh.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 11:30:26 $
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

#ifndef _SD_GRDOCSH_HXX
#define _SD_GRDOCSH_HXX

#ifndef _SFX_OBJFAC_HXX //autogen
#include <bf_sfx2/docfac.hxx>
#endif
#ifndef _SFX_INTERNO_HXX //autogen
#include <bf_sfx2/interno.hxx>
#endif
#ifndef _SFX_OBJSH_HXX //autogen
#include <bf_sfx2/objsh.hxx>
#endif

#ifndef _SD_DOCSHELL_HXX
#include "docshell.hxx"
#endif
#ifndef _SD_GLOB_HXX
#include "glob.hxx"
#endif
#ifndef _SDMOD_HXX
#include "sdmod.hxx"
#endif
#ifndef _PRESENTATION_HXX
#include "pres.hxx"
#endif
namespace binfilter {


/*************************************************************************
|*
|* Document-Shell fuer Draw-Dokumente
|*
\************************************************************************/

class SdGraphicDocShell : public SdDrawDocShell
{
 public:
    TYPEINFO();

    SFX_DECL_OBJECTFACTORY_DLL(SdGraphicDocShell, SD_MOD());

    SdGraphicDocShell(SfxObjectCreateMode eMode = SFX_CREATE_MODE_EMBEDDED,
                   BOOL bSdDataObj=FALSE, DocumentType=DOCUMENT_TYPE_DRAW);
    SdGraphicDocShell(SdDrawDocument* pDoc, SfxObjectCreateMode eMode = SFX_CREATE_MODE_EMBEDDED,
                   BOOL bSdDataObj=FALSE, DocumentType=DOCUMENT_TYPE_DRAW);
    ~SdGraphicDocShell();
};

#ifndef SV_DECL_SDGRAPHICDOCSHELL_DEFINED
#define SV_DECL_SDGRAPHICDOCSHELL_DEFINED
SV_DECL_REF(SdGraphicDocShell)
#endif

SV_IMPL_REF (SdGraphicDocShell)


} //namespace binfilter
#endif          // _SD_GRDOCSH_HXX

