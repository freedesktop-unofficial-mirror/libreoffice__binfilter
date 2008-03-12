/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: outstrm.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 12:22:09 $
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

#ifndef SVTOOLS_OUTSTRM_HXX
#define SVTOOLS_OUTSTRM_HXX

#ifndef INCLUDED_SVLDLLAPI_H

#endif

#ifndef _COM_SUN_STAR_UNO_REFERENCE_H_
#include <com/sun/star/uno/Reference.h>
#endif
#ifndef _STREAM_HXX
#include <tools/stream.hxx>
#endif

namespace com { namespace sun { namespace star { namespace io {
    class XOutputStream;
} } } }

namespace binfilter
{

//============================================================================
class  SvOutputStream: public SvStream
{
    com::sun::star::uno::Reference< com::sun::star::io::XOutputStream >
        m_xStream;

     virtual ULONG GetData(void *, ULONG);

     virtual ULONG PutData(void const * pData, ULONG nSize);

     virtual ULONG SeekPos(ULONG);

     virtual void FlushData();

     virtual void SetSize(ULONG);

public:
    SvOutputStream(com::sun::star::uno::Reference<
                           com::sun::star::io::XOutputStream > const &
                       rTheStream);

    virtual ~SvOutputStream();

    virtual USHORT IsA() const;
};

}

#endif // SVTOOLS_OUTSTRM_HXX

