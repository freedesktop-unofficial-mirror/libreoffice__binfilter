/*************************************************************************
 *
 *  $RCSfile: sw_swlib.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 18:32:27 $
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


#define _SWLIB_CXX

// auto strip #ifndef _SFX_OBJFAC_HXX //autogen
// auto strip #include <bf_sfx2/docfac.hxx>
// auto strip #endif
// auto strip #ifndef _SFX_DOCFILT_HACK_HXX //autogen
// auto strip #include <bf_sfx2/docfilt.hxx>
// auto strip #endif
#ifndef _SFX_FCONTNR_HXX //autogen
#include <bf_sfx2/fcontnr.hxx>
#endif
#ifndef _SFXDOCFILE_HXX //autogen
#include <bf_sfx2/docfile.hxx>
#endif
// auto strip #ifndef _SFXAPP_HXX //autogen
// auto strip #include <bf_sfx2/app.hxx>
// auto strip #endif
// auto strip #ifndef _INETTYPE_HXX //autogen
// auto strip #include <svtools/inettype.hxx>
// auto strip #endif
// auto strip #ifndef _MSGBOX_HXX //autogen
// auto strip #include <vcl/msgbox.hxx>
// auto strip #endif
#ifndef _PARHTML_HXX //autogen
#include <svtools/parhtml.hxx>
#endif

// auto strip #include <swdll.hxx>
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

#ifndef _IODETECT_HXX
#include <iodetect.hxx>
#endif
namespace binfilter {

#define C2S(cChar) String::CreateFromAscii(RTL_CONSTASCII_STRINGPARAM(cChar))
//os: the Icon Id is unused since start of VCL
#define ICON_ID_INVALID 0

inline BOOL IsDocShellRegistered()
{
// zu dem Zeitpunkt ist das Interface der DocShell leider noch nicht
// registriert!!

//  return 0 != (SFX_APP()->GetInterfaceByIdImpl( SfxInterfaceId(SW_DOCSHELL) ));
    return SvtModuleOptions().IsWriter();
}

USHORT AutoDetec( const String& FileName, USHORT & rVersion );

IO_DETECT_IMPL1
IO_DETECT_IMPL2
IO_DETECT_IMPL3
IO_DETECT_IMPL4

//-------------------------------------------------------------------------


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
