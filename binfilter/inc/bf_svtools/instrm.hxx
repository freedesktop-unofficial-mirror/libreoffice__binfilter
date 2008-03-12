/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: instrm.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 12:12:30 $
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

#ifndef SVTOOLS_INSTRM_HXX
#define SVTOOLS_INSTRM_HXX


#ifndef _COM_SUN_STAR_UNO_REFERENCE_H_
#include <com/sun/star/uno/Reference.h>
#endif
#ifndef _STREAM_HXX
#include <tools/stream.hxx>
#endif

namespace com { namespace sun { namespace star { namespace io {
    class XInputStream;
    class XSeekable;
} } } }

namespace binfilter
{

class SvDataPipe_Impl;

//============================================================================
class  SvInputStream: public SvStream
{
    com::sun::star::uno::Reference< com::sun::star::io::XInputStream >
        m_xStream;
    com::sun::star::uno::Reference< com::sun::star::io::XSeekable >
        m_xSeekable;
    SvDataPipe_Impl * m_pPipe;
    ULONG m_nSeekedFrom;

     bool open();

     virtual ULONG GetData(void * pData, ULONG nSize);

     virtual ULONG PutData(void const *, ULONG);

     virtual ULONG SeekPos(ULONG nPos);

     virtual void FlushData();

     virtual void SetSize(ULONG);

public:
    SvInputStream(
        com::sun::star::uno::Reference< com::sun::star::io::XInputStream >
                const &
            rTheStream);

    virtual ~SvInputStream();

    virtual USHORT IsA() const;

    virtual void AddMark(ULONG nPos);

    virtual void RemoveMark(ULONG nPos);
};

}

#endif // SVTOOLS_INSTRM_HXX

