/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: SwAppletImpl.hxx,v $
 *
 *  $Revision: 1.7 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 10:32:41 $
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

#ifndef _SW_APPLET_IMPL_HXX
#define _SW_APPLET_IMPL_HXX

#define SWHTML_OPTTYPE_IGNORE 0
#define SWHTML_OPTTYPE_TAG 1
#define SWHTML_OPTTYPE_PARAM 2
#define SWHTML_OPTTYPE_SIZE 3

#ifndef _STRING_HXX //autogen
#include <tools/string.hxx>
#endif

#ifndef _HTMLKYWD_HXX
#include <bf_svtools/htmlkywd.hxx>
#endif
#ifndef _FRAMEOBJ_HXX //autogen
#include <bf_sfx2/frameobj.hxx>
#endif
#ifndef _WRKWIN_HXX //autogen
#include <vcl/wrkwin.hxx>
#endif
#ifndef _SVSTOR_HXX //autogen
#include <bf_so3/svstor.hxx>
#endif
#ifndef _APPLET_HXX //autogen
#include <bf_so3/applet.hxx>
#endif
#ifndef _PLUGIN_HXX //autogen
#include <bf_so3/plugin.hxx>
#endif
#ifndef _SFXITEMSET_HXX
#include <bf_svtools/itemset.hxx>
#endif
namespace binfilter {

class SfxItemSet;
extern sal_Char const SVTOOLS_CONSTASCII_DECL( sHTML_O_hidden, "HIDDEN" );
extern sal_Char const SVTOOLS_CONSTASCII_DECL( sHTML_HIDDEN_false, "FALSE" );
extern sal_Char const SVTOOLS_CONSTASCII_DECL( sHTML_O_archive, "ARCHIVE" );
extern sal_Char const SVTOOLS_CONSTASCII_DECL( sHTML_O_archives, "ARCHIVES" );
extern sal_Char const SVTOOLS_CONSTASCII_DECL( sHTML_O_object, "OBJECT" );

class SwApplet_Impl
{
    SvAppletObjectRef xApplet;      // das aktuelle Applet
    SfxItemSet        aItemSet;

public:
    static USHORT GetOptionType( const String& rName, BOOL bApplet ){DBG_BF_ASSERT(0, "STRIP"); return 0;} //STRIP001 static USHORT GetOptionType( const String& rName, BOOL bApplet );
    SwApplet_Impl( SfxItemSet& rSet ): aItemSet ( rSet) {}
    ~SwApplet_Impl(){DBG_BF_ASSERT(0, "STRIP");}; //STRIP001 ~SwApplet_Impl();

    void CreateApplet( const String& rCode, const String& rName,//STRIP001  void CreateApplet( const String& rCode, const String& rName,
        BOOL bMayScript, const String& rCodeBase ){DBG_BF_ASSERT(0, "STRIP");}; //STRIP001 //STRIP001                      BOOL bMayScript, const String& rCodeBase );
        sal_Bool CreateApplet();
    SvAppletObject* GetApplet() { return &xApplet; }
    SfxItemSet& GetItemSet() { return aItemSet; }
};
} //namespace binfilter
#endif
