/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: glshell.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 05:35:56 $
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
#ifndef _AUTODOC_HXX
#define _AUTODOC_HXX

#include "wdocsh.hxx"
namespace binfilter {

class SwTextBlocks;


class SwGlosDocShell : public SwDocShell
{
//STRIP001  String          aLongName;
//STRIP001  String          aShortName;
//STRIP001  String          aGroupName;
//STRIP001  sal_Bool        bShow;
//STRIP001 protected:
//STRIP001  virtual BOOL Save();

public:
//STRIP001  TYPEINFO();
    SFX_DECL_INTERFACE(SW_GLOSDOCSHELL);
//STRIP001              SwGlosDocShell( sal_Bool bNewShow = sal_True);
//STRIP001      virtual ~SwGlosDocShell();
//STRIP001
//STRIP001  void            Execute( SfxRequest& );
//STRIP001  void            GetState( SfxItemSet& );
//STRIP001  void            SetLongName( const String& rLongName )
//STRIP001                      { aLongName = rLongName; }
//STRIP001  void            SetShortName( const String& rShortName )
//STRIP001                      { aShortName = rShortName; }
//STRIP001  void            SetGroupName( const String& rGroupName )
//STRIP001                      { aGroupName = rGroupName; }
//STRIP001  const String&   GetShortName(){return aShortName;}
};


class SwWebGlosDocShell : public SwWebDocShell
{
//STRIP001  String          aLongName;
//STRIP001  String          aShortName;
//STRIP001  String          aGroupName;
//STRIP001 protected:
//STRIP001  virtual BOOL Save();

public:
//STRIP001  TYPEINFO();
    SFX_DECL_INTERFACE(SW_WEBGLOSDOCSHELL);
                SwWebGlosDocShell();
        virtual ~SwWebGlosDocShell();
//STRIP001
//STRIP001  void            Execute( SfxRequest& );
//STRIP001  void            GetState( SfxItemSet& );
//STRIP001  void            SetLongName( const String& rLongName )
//STRIP001                      { aLongName = rLongName; }
//STRIP001  void            SetShortName( const String& rShortName )
//STRIP001                      { aShortName = rShortName; }
//STRIP001  void            SetGroupName( const String& rGroupName )
//STRIP001                      { aGroupName = rGroupName; }
//STRIP001  const String&   GetShortName(){return aShortName;}
};

} //namespace binfilter
#endif





















