/*************************************************************************
 *
 *  $RCSfile: plugobj.hxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:23:28 $
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

#ifndef _PLUGOBJ_HXX
#define _PLUGOBJ_HXX

#ifndef _PLUGIN_HXX //autogen
#include <so3/plugin.hxx>
#endif
#include "bf_sfx2/app.hxx"

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
    SfxFrame*               GetFrame() const;


                            // Macro mu\s exportiert werden, sonst geht das
                            // SO2-RTTI schief, da GetFactoryAdress() die
                            // Factory-Adresse der Basisklasse liefert.
                            // Da das zweite Argument in einer Inline-Funktion
                            // verwendet wird, mu\s dieses exportierbare
                            // Funktionsaufrufe verwenden, also nicht z.B.
                            // SFX_APP()->Get_Impl()
                            SO2_DECL_BASIC_CLASS_DLL(SfxPluginObject, GetFactoryPtr())

#if _SOLAR__PRIVATE
    void                    ReleaseFrame_Impl();
    BOOL                    ConstructFrame();
#endif
};

inline SfxPluginObjectFactoryPtr::SfxPluginObjectFactoryPtr()
    : pSfxPluginObjectFactory(0)    // sonst funzt ClassFactory() nicht!
{
    // hier Factory nicht erzeugen, da GetFactoryPtr() erst nach Beenden dieses
    // ctors einen vern"unftigen Wert liefern kann!
}

SO2_DECL_IMPL_REF(SfxPluginObject)


#endif
