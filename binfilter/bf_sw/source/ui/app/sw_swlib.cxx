/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_swlib.cxx,v $
 *
 *  $Revision: 1.8 $
 *
 *  last change: $Author: vg $ $Date: 2007-10-15 11:49:46 $
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


#define _SWLIB_CXX

#ifndef _SFX_FCONTNR_HXX //autogen
#include <bf_sfx2/fcontnr.hxx>
#endif
#ifndef _SFXDOCFILE_HXX //autogen
#include <bf_sfx2/docfile.hxx>
#endif
#ifndef _PARHTML_HXX //autogen
#include <svtools/parhtml.hxx>
#endif

#include <swdll0.hxx> // wird vom makefile generiert
#ifndef _SWMODULE_HXX //autogen
#include <swmodule.hxx>
#endif
#ifndef _SWWDOCSH_HXX //autogen
#include <wdocsh.hxx>
#endif
#ifndef _SWGLOBDOCSH_HXX //autogen
#include <globdoc.hxx>
#endif
#ifndef _SHELLIO_HXX //autogen
#include <shellio.hxx>
#endif
#ifndef _SO_CLSIDS_HXX
#include <so3/clsids.hxx>
#endif

#include <svtools/moduleoptions.hxx>

#include <app.hrc>
#include <web.hrc>
#include <globdoc.hrc>

#include <iodetect.hxx>

namespace binfilter {

#define C2S(cChar) String::CreateFromAscii(RTL_CONSTASCII_STRINGPARAM(cChar))
//os: the Icon Id is unused since start of VCL
#define ICON_ID_INVALID 0

inline BOOL IsDocShellRegistered()
{
    return SvtModuleOptions().IsWriter();
}

USHORT AutoDetec( const String& FileName, USHORT & rVersion );

IO_DETECT_IMPL1
IO_DETECT_IMPL2
IO_DETECT_IMPL3
IO_DETECT_IMPL4

//-------------------------------------------------------------------------
extern "C" { static void SAL_CALL thisModule() {} }

SFX_IMPL_MODULE_LIB(Sw, C2S(DLL_NAME))

TYPEINIT1( SwModuleDummy, SfxModule );


//-------------------------------------------------------------------------
SFX_IMPL_OBJECTFACTORY_MOD(SwDocShell,                      \
        SFXOBJECTSHELL_STD_NORMAL|SFXOBJECTSHELL_HASMENU,   \
        swriter,                                            \
        SvGlobalName(BF_SO3_SW_CLASSID),                        \
        Sw,                                                 \
        DLL_NAME)
{
    SfxObjectFactory& rFactory = (SfxObjectFactory&)Factory();
    rFactory.SetDocumentServiceName(C2S("com.sun.star.text.TextDocument"));
    rFactory.GetFilterContainer()->SetDetectFilter( &SwDLL::DetectFilter );
}

//-------------------------------------------------------------------------
SFX_IMPL_OBJECTFACTORY_MOD(SwWebDocShell,                               \
        SFXOBJECTSHELL_STD_NORMAL|SFXOBJECTSHELL_HASMENU, swriter/web,  \
        SvGlobalName(BF_SO3_SWWEB_CLASSID),                             \
        Sw,                                                             \
        DLL_NAME)
{
    SfxObjectFactory& rFactory = (SfxObjectFactory&)Factory();
    rFactory.SetDocumentServiceName(C2S("com.sun.star.text.WebDocument"));
    rFactory.GetFilterContainer()->SetDetectFilter( &SwDLL::DetectFilter );
}

//-------------------------------------------------------------------------
SFX_IMPL_OBJECTFACTORY_MOD(SwGlobalDocShell,                                          \
         SFXOBJECTSHELL_STD_NORMAL|SFXOBJECTSHELL_HASMENU, swriter/GlobalDocument, \
        SvGlobalName(BF_SO3_SWGLOB_CLASSID),                                \
        Sw,                                                                           \
        DLL_NAME)
{
    SfxObjectFactory& rFactory = (SfxObjectFactory&)Factory();
    rFactory.SetDocumentServiceName(C2S("com.sun.star.text.GlobalDocument"));
    rFactory.GetFilterContainer()->SetDetectFilter( &SwDLL::GlobDetectFilter );
}

//-------------------------------------------------------------------------

void    SwDLL::LibInit()
{
    // in most cases you must initialize your document-factory here
    SvtModuleOptions aOpt;
    SfxObjectFactory* pWriterFactory = NULL;
    SfxObjectFactory* pGlobalFactory = NULL;
    if ( aOpt.IsWriter() )
    {
        SwDocShell::RegisterFactory(    SDT_SW_DOCFACTPRIO      );
        SwGlobalDocShell::RegisterFactory(SDT_SW_DOCFACTPRIO + 2);
        pWriterFactory = &SwDocShell::Factory();
        pGlobalFactory = &SwGlobalDocShell::Factory();
    }

    // WebWriter alway needed because it is used for the help viewer
    SwWebDocShell::RegisterFactory( SDT_SW_DOCFACTPRIO + 1  );

    // create a dummy-module for Object-Factory-Pointer
    SW_MOD() = (SwModule*)new SwModuleDummy( 0, TRUE, &SwWebDocShell::Factory(), pWriterFactory, pGlobalFactory );
    SwModule* pMod = SW_MOD();
}

//-------------------------------------------------------------------------
void    SwDLL::LibExit()
{
        // Innerhalb von FreeLibSw wird Exit() gerufen
    FreeLibSw();

    // destroy the dummy-module with Object-Factory-Pointer
    DELETEZ( *(SwModuleDummy**) GetAppData(BF_SHL_WRITER) );
}

//-------------------------------------------------------------------------

SfxModule* SwModuleDummy::Load()
{
    return (LoadLibSw() ? SW_MOD() : NULL);
}
}
