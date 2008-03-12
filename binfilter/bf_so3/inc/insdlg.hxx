/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: insdlg.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 08:10:23 $
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
#ifndef _INSDLG_HXX
#define _INSDLG_HXX

#ifndef _GLOBNAME_HXX //autogen
#include <tools/globname.hxx>
#endif
#ifndef _OWNCONT_HXX
#include <bf_svtools/ownlist.hxx>
#endif
#ifndef _SO2REF_HXX
#include <bf_so3/so2ref.hxx>
#endif

#ifndef INCLUDED_SO3DLLAPI_H
#include "bf_so3/so3dllapi.h"
#endif

class SvAppletObject;

#ifndef SV_DECL_SVBASELINK2_DEFINED
#define SV_DECL_SVBASELINK2_DEFINED
SV_DECL_REF(SvBaseLink2)
#endif

namespace binfilter
{
#ifndef SO2_DECL_SVINPLACEOBJECT_DEFINED
#define SO2_DECL_SVINPLACEOBJECT_DEFINED
SO2_DECL_REF(SvInPlaceObject)
#endif

/********************** SvObjectServer ***********************************
*************************************************************************/
class SO3_DLLPUBLIC SvObjectServer
{
private:
    SvGlobalName    aClassName;
    String          aHumanName;

public:
    SvObjectServer( const SvGlobalName & rClassP, const String & rHumanP ) :
        aClassName( rClassP ),
        aHumanName( rHumanP ) {}

    const SvGlobalName &    GetClassName() const { return aClassName; }
    const String &          GetHumanName() const { return aHumanName; }
};

class SO3_DLLPRIVATE SvObjectServerList
{
    PRV_SV_DECL_OWNER_LIST(SvObjectServerList,SvObjectServer)
    SO3_DLLPRIVATE const SvObjectServer *  Get( const String & rHumanName ) const;
    SO3_DLLPRIVATE const SvObjectServer *  Get( const SvGlobalName & ) const;
    SO3_DLLPRIVATE void                    Remove( const SvGlobalName & );

    SO3_DLLPRIVATE void                 FillInsertObjects();
};

}   // namespace so3

#endif // _INSDLG_HXX

