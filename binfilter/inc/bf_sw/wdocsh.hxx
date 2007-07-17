/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: wdocsh.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: obo $ $Date: 2007-07-17 12:58:03 $
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
#ifndef _SWWDOCSH_HXX
#define _SWWDOCSH_HXX

#include "docsh.hxx"
#ifndef SW_SWDLL_HXX
#include <swdll.hxx>
#endif
namespace binfilter {

class SwWebDocShell: public SwDocShell
{
    USHORT      nSourcePara;    // aktive Zeile in der SourceView
public:

    // aber selbst implementieren
    SFX_DECL_OBJECTFACTORY_DLL(SwWebDocShell, SW_DLL());
    TYPEINFO();

    SwWebDocShell(SfxObjectCreateMode eMode = SFX_CREATE_MODE_EMBEDDED);
    ~SwWebDocShell();

};

} //namespace binfilter
#endif


