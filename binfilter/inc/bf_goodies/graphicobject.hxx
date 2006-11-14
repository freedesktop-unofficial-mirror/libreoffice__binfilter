/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: graphicobject.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: ihi $ $Date: 2006-11-14 12:18:43 $
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

#ifndef _BF_GOODIES_GRAPHICOBJECT_HXX
#define _BF_GOODIES_GRAPHICOBJECT_HXX

#ifndef _GRFMGR_HXX
#include <goodies/grfmgr.hxx>
#endif

// wrapper for GraphicAttr for binfilter
namespace binfilter {
    class BfGraphicAttr : public GraphicAttr
    {
    public:
        BfGraphicAttr();
        ~BfGraphicAttr();
        void            SetTransparency( BYTE cTransparency );
    };
}//end of namespace binfilter

// wrapper for GraphicObject for binfilter
namespace binfilter {
    class BfGraphicObject : public GraphicObject
    {
    protected:
        virtual void GraphicManagerDestroyed();
        virtual ULONG GetReleaseFromCache() const;
        virtual SvStream* GetSwapStream() const;
        virtual void Load( SvStream& );
        virtual void Save( SvStream& );
        virtual void Assign( const SvDataCopyStream& );

    public:
        TYPEINFO();
        BfGraphicObject( const GraphicManager* pMgr = NULL );
        BfGraphicObject( const Graphic& rGraphic, const GraphicManager* pMgr = NULL );
        BfGraphicObject( const Graphic& rGraphic, const String& rLink, const GraphicManager* pMgr = NULL );
        BfGraphicObject( const BfGraphicObject& rCacheObj, const GraphicManager* pMgr = NULL );
        BfGraphicObject( const ByteString& rUniqueID, const GraphicManager* pMgr = NULL );
        ~BfGraphicObject();

        BOOL                    operator==( const BfGraphicObject& rCacheObj ) const;
        const Graphic&          GetGraphic() const;
        void                    SetAttr( const BfGraphicAttr& rAttr );
        const BfGraphicAttr&    GetAttr() const;
        ByteString              GetUniqueID() const;
        BfGraphicObject&        operator=( const BfGraphicObject& rCacheObj );
        void                    SetUserData();
        void                    SetUserData( const String& rUserData );
        void                    SetGraphic( const Graphic& rGraphic );
        void                    SetGraphic( const Graphic& rGraphic, const String& rLink );
        void                    SetSwapState();
        void                    FireSwapInRequest();
        void                    FireSwapOutRequest();
        void                    StopAnimation( OutputDevice* pOut = NULL, long nExtraData = 0L );
        BOOL                    Draw( OutputDevice* pOut, const Point& rPt, const Size& rSz,
                                    const BfGraphicAttr* pAttr = NULL, ULONG nFlags = GRFMGR_DRAW_STANDARD );
        String                  GetUserData() const;
        void                    SetSwapStreamHdl();
        void                    SetSwapStreamHdl( const Link& rHdl, const ULONG nSwapOutTimeout = 0UL );
        void                    ReleaseFromCache();
        String                  GetLink() const;
        void                    SetLink();
        void                    SetLink( const String& rLink );
        BOOL                    SwapOut();
        BOOL                    SwapOut( SvStream* pOStm );
        BOOL                    SwapIn();
        BOOL                    SwapIn( SvStream* pIStm );
    };
}//end of namespace binfilter
#endif // _BF_GOODIES_GRAPHICOBJECT_HXX
