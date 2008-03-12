/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: binddata.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 08:10:10 $
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

#ifndef _BINDDATA_HXX
#define _BINDDATA_HXX "$Revision: 1.3 $"

#ifndef _SOLAR_H
#include <tools/solar.h>
#endif
#ifndef _LIST_HXX
#include <tools/list.hxx>
#endif

namespace binfilter
{

class SvBindingTransportFactory;
DECLARE_LIST (SvBindingTransportFactoryList, SvBindingTransportFactory*)

class SvLockBytesFactory;
DECLARE_LIST (SvLockBytesFactoryList, SvLockBytesFactory*)

class SvBindingData_Impl;

/*========================================================================
 *
 * SvBindingData interface.
 *
 *======================================================================*/
struct SvBindingData
{
    /** Representation.
    */
    SvBindingTransportFactoryList  m_aTransportFactories;
    SvLockBytesFactoryList         m_aLockBytesFactories;

    SvBindingData_Impl            *m_pImpl;

    /** Construction/Destruction.
    */
    SvBindingData (void);
    ~SvBindingData (void);

    /** Get/Delete.
    */
    static SvBindingData* Get    (void);
    static void           Delete (void);

    /** HasHttpCache.
    */
    BOOL HasHttpCache (void);

    /** ShouldUseFtpProxy.
    */
    BOOL ShouldUseFtpProxy (const String &rUrl);
};

#define BAPP() (SvBindingData::Get())

}

#endif /* _BINDDATA_HXX */



