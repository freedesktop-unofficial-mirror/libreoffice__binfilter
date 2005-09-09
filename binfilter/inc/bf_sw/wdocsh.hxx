/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: wdocsh.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 17:08:48 $
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
    SFX_DECL_INTERFACE(SW_WEBDOCSHELL);
    SFX_DECL_OBJECTFACTORY_DLL(SwWebDocShell, SW_DLL());
    TYPEINFO();

    SwWebDocShell(SfxObjectCreateMode eMode = SFX_CREATE_MODE_EMBEDDED);
    ~SwWebDocShell();

//STRIP001  virtual void        FillClass( SvGlobalName * pClassName,
//STRIP001                                 ULONG * pClipFormat,
//STRIP001                                 String * pAppName,
//STRIP001                                 String * pLongUserName,
//STRIP001                                 String * pUserName,
//STRIP001                                 long nVersion = SOFFICE_FILEFORMAT_CURRENT ) const;
//STRIP001  USHORT      GetSourcePara()const
//STRIP001                          {return nSourcePara;}
//STRIP001  void        SetSourcePara(USHORT nSet)
//STRIP001                          {nSourcePara = nSet;}
};

} //namespace binfilter
#endif


