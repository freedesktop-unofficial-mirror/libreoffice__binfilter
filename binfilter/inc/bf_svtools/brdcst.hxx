/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: brdcst.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 11:51:05 $
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
#ifndef _SFXBRDCST_HXX
#define _SFXBRDCST_HXX

#ifndef _RTTI_HXX //autogen
#include <tools/rtti.hxx>
#endif

#ifndef _SVARRAY_HXX
#include <bf_svtools/svarray.hxx>
#endif

namespace binfilter {

class SfxListener;
class SfxHint;

SV_DECL_PTRARR( SfxListenerArr_Impl, SfxListener*, 0, 2 )

#define SFX_FORWARD( rBC, rBCT, rHint, rHintT ) \
        Forward( rBC, rHint )

//-------------------------------------------------------------------------

class  SfxBroadcaster
{
friend class SfxListener;

    SfxListenerArr_Impl     aListeners;

private:
    BOOL         AddListener( SfxListener& rListener );
    void                    RemoveListener( SfxListener& rListener );
    const SfxBroadcaster&   operator=(const SfxBroadcaster &); // verboten

protected:
    void                    SFX_FORWARD(SfxBroadcaster& rBC, const TypeId& rBCType,
                                        const SfxHint& rHint, const TypeId& rHintType);
    virtual void            ListenersGone();

public:
                            TYPEINFO();

                            SfxBroadcaster();
                            SfxBroadcaster( const SfxBroadcaster &rBC );
    virtual                 ~SfxBroadcaster();

    void                    Broadcast( const SfxHint &rHint );
    void                    BroadcastDelayed( const SfxHint& rHint );
    void                    BroadcastInIdle( const SfxHint& rHint );

    BOOL                    HasListeners() const;
    USHORT                  GetListenerCount() const { return aListeners.Count(); }
    SfxListener*            GetListener( USHORT nNo ) const
                            { return (SfxListener*) aListeners[nNo]; }
};

}

#endif
