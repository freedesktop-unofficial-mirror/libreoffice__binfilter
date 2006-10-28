/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svxerr.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 04:14:09 $
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
#ifndef _SVXERR_HXX
#define _SVXERR_HXX

// include ---------------------------------------------------------------


// define ----------------------------------------------------------------




#define ERRCODE_SVX_GRAPHIC_WRONG_FILEFORMAT   (8UL | ERRCODE_AREA_SVX | \
                                                ERRCODE_CLASS_READ )
#define ERRCODE_SVX_FORMS_NOIOSERVICES         (10UL | ERRCODE_AREA_SVX )
#define ERRCODE_SVX_FORMS_READWRITEFAILED      (11UL | ERRCODE_AREA_SVX )

#define ERRCODE_SVX_BULLETITEM_NOBULLET        (12UL | ERRCODE_AREA_SVX )


#define ERRCODE_SVX_VBASIC_STORAGE_EXIST       (14UL | ERRCODE_AREA_SVX     \
                                                     | ERRCODE_WARNING_MASK \
                                                     | ERRCODE_CLASS_WRITE )

// both codes will be used twice : with ERRCODE_CLASS_READ- and ERRCODE_CLASS_WRITE-bits

// class SvxErrorHandler -------------------------------------------------

#ifndef __RSC

#ifndef _EHDL_HXX //autogen
#include <svtools/ehdl.hxx>
#endif
namespace binfilter {
class SvxErrorHandler : private SfxErrorHandler
{
  public:
    SvxErrorHandler();
};

}//end of namespace binfilter
#endif

#endif

