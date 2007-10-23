/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: dinfobj.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: vg $ $Date: 2007-10-23 13:42:13 $
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
#ifndef _SFX_DINFOBJ_HXX
#define _SFX_DINFOBJ_HXX


#ifndef _AUTO_HXX //autogen
#include <bf_so3/auto.hxx>
#endif
#include "docinf.hxx"
#include "dinfdlg.hxx"
namespace binfilter {

class SfxMedium;

//=========================================================================

class SfxDocumentInfoObject_Impl: public SvDispatch
{
    SfxDocumentInfoItem     aDocInfo;
    SfxMedium*              pMedium;

protected:
    SvGlobalName            GetTypeName() const;
    BOOL                    FillTypeLibInfo( String * pName,
                                     USHORT * pMajor, USHORT * pMinor ) const;

public:
                            SfxDocumentInfoObject_Impl();
                            ~SfxDocumentInfoObject_Impl();

    virtual void            SFX_NOTIFY( SfxBroadcaster& rBC, const TypeId& rBCType,
                                    const SfxHint& rHint, const TypeId& rHintType );
};


}//end of namespace binfilter
#endif

