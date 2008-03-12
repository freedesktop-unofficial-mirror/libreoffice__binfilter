/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svx_unoedsrc.cxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 09:46:23 $
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

#ifdef _MSC_VER
#pragma hdrstop
#endif

#ifndef _SFXBRDCST_HXX
#include <bf_svtools/brdcst.hxx>
#endif

#include "unoedsrc.hxx"
namespace binfilter {

//------------------------------------------------------------------------

SvxTextForwarder::~SvxTextForwarder()
{
}

//------------------------------------------------------------------------

SvxViewForwarder::~SvxViewForwarder()
{
}

//------------------------------------------------------------------------

SvxEditSource::~SvxEditSource()
{
}

SvxViewForwarder* SvxEditSource::GetViewForwarder()
{
    return NULL;
}

SvxEditViewForwarder* SvxEditSource::GetEditViewForwarder( sal_Bool bCreate )
{
    return NULL;
}

SfxBroadcaster& SvxEditSource::GetBroadcaster() const
{
    DBG_ERROR("SvxEditSource::GetBroadcaster called for implementation missing this feature!");

    static SfxBroadcaster aBroadcaster;

    return aBroadcaster;
}
}
