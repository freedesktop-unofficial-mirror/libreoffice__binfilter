/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: imapinfo.hxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 11:31:01 $
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

#ifndef _SD_IMAPINFO_HXX
#define _SD_IMAPINFO_HXX

#ifndef _SD_SDIOCMPT_HXX
#include "sdiocmpt.hxx"
#endif
#ifndef _SD_GLOB_HXX
#include "glob.hxx"
#endif
#ifndef _SVDOBJ_HXX //autogen
#include <bf_svx/svdobj.hxx>
#endif
#ifndef _IMAP_HXX //autogen
#include <bf_svtools/imap.hxx>
#endif
#include "bf_so3/staticbaseurl.hxx"
namespace binfilter {


/*************************************************************************
|*
|*
|*
\************************************************************************/

class SdIMapInfo : public SdrObjUserData, public SfxListener
{

    ImageMap        aImageMap;

public:
                    SdIMapInfo() :
                        SdrObjUserData( SdUDInventor, SD_IMAPINFO_ID, 0 ) {};

                    SdIMapInfo( const ImageMap& rImageMap ) :
                        SdrObjUserData( SdUDInventor, SD_IMAPINFO_ID, 0 ),
                        aImageMap( rImageMap ) {};

                    SdIMapInfo( const SdIMapInfo& rIMapInfo ) :
                        SdrObjUserData( SdUDInventor, SD_IMAPINFO_ID, 0 ),
                        aImageMap( rIMapInfo.aImageMap ) {};

    virtual         ~SdIMapInfo() {};

    virtual SdrObjUserData* Clone( SdrObject* pObj ) const { return new SdIMapInfo( *this ); }

    virtual void WriteData( SvStream& rOStm );
    virtual void ReadData( SvStream& rIStm );

    void            SetImageMap( const ImageMap& rIMap ) { aImageMap = rIMap; }
    const ImageMap& GetImageMap() const { return aImageMap; }
};


/*************************************************************************
|*
|*
|*
\************************************************************************/

inline void SdIMapInfo::WriteData( SvStream& rOStm )
{
    SdrObjUserData::WriteData( rOStm );

    SdIOCompat aIO( rOStm, STREAM_WRITE, 1 );

    aImageMap.Write(
        rOStm, ::binfilter::StaticBaseUrl::GetBaseURL(INetURLObject::NO_DECODE));
}


/*************************************************************************
|*
|*
|*
\************************************************************************/

inline void SdIMapInfo::ReadData( SvStream& rIStm )
{
    SdrObjUserData::ReadData( rIStm );

    SdIOCompat aIO( rIStm, STREAM_READ );

    aImageMap.Read(
        rIStm, ::binfilter::StaticBaseUrl::GetBaseURL(INetURLObject::NO_DECODE));
}


} //namespace binfilter
#endif      // _SD_IMAPINFO_HXX


