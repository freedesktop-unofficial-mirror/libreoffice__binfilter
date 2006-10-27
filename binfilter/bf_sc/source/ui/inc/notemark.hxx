/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: notemark.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-27 16:18:43 $
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

#ifndef SC_NOTEMARK_HXX
#define SC_NOTEMARK_HXX

#ifndef _MAPMOD_HXX //autogen
#include <vcl/mapmod.hxx>
#endif
#ifndef _TIMER_HXX //autogen
#include <vcl/timer.hxx>
#endif

#ifndef SC_SCGLOB_HXX
#include "global.hxx"
#endif
namespace binfilter {

class ScNoteMarker
{
public:
    ScNoteMarker( Window* pWin,                         //STRIP001              ScNoteMarker( Window* pWin,
        Window* pRight, Window* pBottom, Window* pDiagonal,//STRIP001                               Window* pRight, Window* pBottom, Window* pDiagonal,
        ScDocument* pD, ScAddress aPos,                     //STRIP001                              ScDocument* pD, ScAddress aPos,
        const String& rUser, const MapMode& rMap,           //STRIP001                              const String& rUser, const MapMode& rMap,
        BOOL bLeftEdge, BOOL bForce, BOOL bKeyboard ){DBG_BF_ASSERT(0, "STRIP");} //STRIP001                                BOOL bLeftEdge, BOOL bForce, BOOL bKeyboard );
};



} //namespace binfilter
#endif

