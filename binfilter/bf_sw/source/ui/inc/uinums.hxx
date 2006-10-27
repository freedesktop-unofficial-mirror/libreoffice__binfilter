/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: uinums.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 00:58:30 $
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
#ifndef _UINUMS_HXX
#define _UINUMS_HXX

#ifndef _SVARRAY_HXX //autogen
#include <svtools/svarray.hxx>
#endif

#ifndef _NUMRULE_HXX
#include <numrule.hxx>
#endif
namespace binfilter {






//------------------------------------------------------------------------
/********************************************************************

********************************************************************/

/********************************************************************

********************************************************************/
class SwChapterNumRules //STRIP001 : public SwBaseNumRules
{

public:
    SwChapterNumRules(){DBG_BF_ASSERT(0, "STRIP");} //STRIP001 SwChapterNumRules();
    virtual ~SwChapterNumRules(){DBG_BF_ASSERT(0, "STRIP");} //STRIP001 virtual ~SwChapterNumRules();

};

// INLINE METHODE --------------------------------------------------------

} //namespace binfilter
#endif
