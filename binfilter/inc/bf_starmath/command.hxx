/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: command.hxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 03:12:30 $
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
#ifndef MATH_COMMAND_HXX
#define MATH_COMMAND_HXX



#ifndef _BITMAP_HXX //autogen
#include <vcl/bitmap.hxx>
#endif
class String;
namespace binfilter {



class SmCommandDesc: public Resource
{
protected:
    String      *pSample;
    String      *pCommand;
    String      *pText;
    String      *pHelp;
    Bitmap      *pGraphic;

public:
    SmCommandDesc(const ResId& rResId);
    ~SmCommandDesc();

    const String  &GetSample()  const { return (*pSample);  }
    const String  &GetCommand() const { return (*pCommand); }
    const String  &GetText()    const { return (*pText); }
    const String  &GetHelp()    const { return (*pHelp); }
    const Bitmap  &GetGraphic() const { return (*pGraphic); }
};


} //namespace binfilter
#endif

