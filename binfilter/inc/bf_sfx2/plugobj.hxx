/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: plugobj.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: obo $ $Date: 2007-07-17 12:41:50 $
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

#ifndef _PLUGOBJ_HXX
#define _PLUGOBJ_HXX

#ifndef _PLUGIN_HXX //autogen
#include <so3/plugin.hxx>
#endif
#include "bf_sfx2/app.hxx"

namespace binfilter {

//=========================================================================
struct SfxPluginObject_Impl;
class SfxFrameDescriptor;


struct SfxPluginObjectFactoryPtr
{
    // Ist n"otig, da im SO2_DECL_BASIC_CLASS_DLL-Macro ein Pointer auf
    // eine exportierbare struct/class "ubergeben werden mu\s
    SotFactory *pSfxPluginObjectFactory;
    SfxPluginObjectFactoryPtr();
};

class SfxPluginObject : public SvPlugInObject
/*  [Beschreibung]

*/
{
    SfxPluginObject_Impl*   pImpl;

#if _SOLAR__PRIVATE
    DECL_STATIC_LINK( SfxPluginObject, MIMEAvailable_Impl, String* );
#endif

protected:
    virtual void            FillClass( SvGlobalName * pClassName,
                               ULONG * pFormat,
                               String * pAppName,
                               String * pFullTypeName,
                               String * pShortTypeName ) const;

                            // Protokoll
    virtual void            InPlaceActivate( BOOL );

                            ~SfxPluginObject();
public:

    static SfxPluginObjectFactoryPtr*
                            GetFactoryPtr();
                            SfxPluginObject();

                            SO2_DECL_BASIC_CLASS_DLL(SfxPluginObject, GetFactoryPtr())
};

inline SfxPluginObjectFactoryPtr::SfxPluginObjectFactoryPtr()
    : pSfxPluginObjectFactory(0)    // sonst funzt ClassFactory() nicht!
{
}

SO2_DECL_IMPL_REF(SfxPluginObject)


}//end of namespace binfilter
#endif
