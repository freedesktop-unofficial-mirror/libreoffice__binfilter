/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: hintwin.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-07 19:54:04 $
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

#ifndef SC_HINTWIN_HXX
#define SC_HINTWIN_HXX

#ifndef _WINDOW_HXX //autogen
#include <vcl/window.hxx>
#endif
namespace binfilter {

class ScHintWindow : public Window
{
//STRIP001 private:
//STRIP001  String  aTitle;
//STRIP001  String  aMessage;
//STRIP001  Point   aTextStart;
//STRIP001  long    nTextHeight;
//STRIP001  Font    aTextFont;
//STRIP001  Font    aHeadFont;
//STRIP001
//STRIP001 protected:
//STRIP001  virtual void    Paint( const Rectangle& rRect );
//STRIP001
public:
    ScHintWindow( Window* pParent, const String& rTit, const String& rMsg ):Window( pParent ){DBG_BF_ASSERT(0, "STRIP");} //STRIP001 ;//STRIP001            ScHintWindow( Window* pParent, const String& rTit, const String& rMsg );
//STRIP001          ~ScHintWindow();
};



} //namespace binfilter
#endif

