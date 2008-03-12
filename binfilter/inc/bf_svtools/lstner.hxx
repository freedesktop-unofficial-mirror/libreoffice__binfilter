/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: lstner.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 12:17:47 $
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
#ifndef _SFXLSTNER_HXX
#define _SFXLSTNER_HXX

#ifndef _RTTI_HXX
#include <tools/rtti.hxx>
#endif

#ifndef _SVARRAY_HXX
#include <bf_svtools/svarray.hxx>
#endif

namespace binfilter
{

class SfxBroadcaster;
class SfxHint;

SV_DECL_PTRARR( SfxBroadcasterArr_Impl, SfxBroadcaster*, 0, 2 )

#define SFX_NOTIFY( rBC, rBCT, rHint, rHintT ) \
        Notify( rBC, rHint )

//-------------------------------------------------------------------------

class  SfxListener
{
    ::binfilter::SfxBroadcasterArr_Impl aBCs;

private:
    const SfxListener&  operator=(const SfxListener &); // n.i., ist verboten

public:
    TYPEINFO();

                        SfxListener();
                        SfxListener( const SfxListener &rCopy );
    virtual             ~SfxListener();

    BOOL                StartListening( SfxBroadcaster& rBroadcaster, BOOL bPreventDups = FALSE );
    BOOL                EndListening( SfxBroadcaster& rBroadcaster, BOOL bAllDups = FALSE );
    void                EndListening( USHORT nNo );
    void                EndListeningAll();
    BOOL                IsListening( SfxBroadcaster& rBroadcaster ) const;

    USHORT              GetBroadcasterCount() const
                        { return aBCs.Count(); }
    SfxBroadcaster*     GetBroadcasterJOE( USHORT nNo ) const
                        { return (SfxBroadcaster*) aBCs.GetObject(nNo); }

    virtual void        Notify( SfxBroadcaster& rBC, const SfxHint& rHint );

#ifndef _NOTIFY_HXX
    void RemoveBroadcaster_Impl( SfxBroadcaster& rBC );
#endif
};

}

#endif
