/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: rangeseq.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 11:23:57 $
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

#ifndef SC_RANGESEQ_HXX
#define SC_RANGESEQ_HXX

#ifndef _SOLAR_H
#include <tools/solar.h>
#endif

#ifndef _COM_SUN_STAR_UNO_ANY_H_
#include <com/sun/star/uno/Any.h>
#endif
class SvNumberFormatter;
namespace binfilter {

class ScDocument;
class ScRange;
class ScMatrix;

class ScRangeToSequence
{
public:
    static BOOL FillLongArray( ::com::sun::star::uno::Any& rAny,
                                ScDocument* pDoc, const ScRange& rRange );
    static BOOL FillLongArray( ::com::sun::star::uno::Any& rAny,
                                const ScMatrix* pMatrix );
    static BOOL FillDoubleArray( ::com::sun::star::uno::Any& rAny,
                                ScDocument* pDoc, const ScRange& rRange );
    static BOOL FillDoubleArray( ::com::sun::star::uno::Any& rAny,
                                const ScMatrix* pMatrix );
    static BOOL FillStringArray( ::com::sun::star::uno::Any& rAny,
                                ScDocument* pDoc, const ScRange& rRange );
    static BOOL FillStringArray( ::com::sun::star::uno::Any& rAny,
                                const ScMatrix* pMatrix, SvNumberFormatter* pFormatter );
    static BOOL FillMixedArray( ::com::sun::star::uno::Any& rAny,
                                ScDocument* pDoc, const ScRange& rRange,
                                BOOL bAllowNV = FALSE );
    static BOOL FillMixedArray( ::com::sun::star::uno::Any& rAny,
                                const ScMatrix* pMatrix );
};


//STRIP001 class ScByteSequenceToString
//STRIP001 {
//STRIP001 public:
//STRIP001  //  rAny must contain Sequence<sal_Int8>,
//STRIP001  //  may or may not contain 0-bytes at the end
//STRIP001  static BOOL GetString( String& rString, const ::com::sun::star::uno::Any& rAny,
//STRIP001                          sal_uInt16 nEncoding );
//STRIP001 };

} //namespace binfilter
#endif

