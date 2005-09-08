/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_dobjfac.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-08 08:53:27 $
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


#ifndef _ERRHDL_HXX
#include <errhdl.hxx>
#endif
// auto strip #ifndef _DPAGE_HXX
// auto strip #include <dpage.hxx>
// auto strip #endif
#ifndef _DOBJFAC_HXX
#include <dobjfac.hxx>
#endif
#ifndef _DFLYOBJ_HXX
#include <dflyobj.hxx>
#endif
namespace binfilter {

SwObjectFactory aSwObjectFactory;

/*************************************************************************
|*
|* void SwObjectFactory::MakeObject()
|*
\************************************************************************/

/*N*/ IMPL_LINK( SwObjectFactory, MakeObject, SdrObjFactory*, pObjFactory )
/*N*/ {
/*N*/   if ( pObjFactory->nInventor == SWGInventor )
/*N*/   {
/*N*/       //Kein switch, derzeit gibt es nur einen.
/*?*/       ASSERT( pObjFactory->nIdentifier == SwFlyDrawObjIdentifier,
/*?*/                                       "Falscher Inventor oder identifier." );
/*?*/       pObjFactory->pNewObj = new SwFlyDrawObj();
/*N*/   }
/*N*/   return 0;
/*N*/ }


}
