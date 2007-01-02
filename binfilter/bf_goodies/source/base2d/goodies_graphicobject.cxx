/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: goodies_graphicobject.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: hr $ $Date: 2007-01-02 16:46:38 $
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
#include "graphicobject.hxx"
#endif

namespace binfilter {
    BfGraphicAttr::BfGraphicAttr() : GraphicAttr() {}
    BfGraphicAttr::~BfGraphicAttr() {}
    void            BfGraphicAttr::SetTransparency( BYTE cTransparency ) { GraphicAttr::SetTransparency(cTransparency); }
}//end of namespace binfilter

namespace binfilter {
    TYPEINIT1_AUTOFACTORY( BfGraphicObject, GraphicObject);
    void BfGraphicObject::GraphicManagerDestroyed() { GraphicObject::GraphicManagerDestroyed(); }
    ULONG BfGraphicObject::GetReleaseFromCache() const { return GraphicObject::GetReleaseFromCache(); }
    SvStream* BfGraphicObject::GetSwapStream() const { return GraphicObject::GetSwapStream(); }
    void BfGraphicObject::Load( SvStream& rSt ) { GraphicObject::Load(rSt); }
    void BfGraphicObject::Save( SvStream& rSt ) { GraphicObject::Save(rSt); }
    void BfGraphicObject::Assign( const SvDataCopyStream& rSt ) { GraphicObject::Assign(rSt); }
    BfGraphicObject::BfGraphicObject( const GraphicManager* pMgr ) : GraphicObject(pMgr) {}
    BfGraphicObject::BfGraphicObject( const Graphic& rGraphic, const GraphicManager* pMgr ) : GraphicObject(rGraphic, pMgr) {}
    BfGraphicObject::BfGraphicObject( const BfGraphicObject& rCacheObj, const GraphicManager* pMgr ) : GraphicObject(rCacheObj, pMgr) {}
    BfGraphicObject::BfGraphicObject( const ByteString& rUniqueID, const GraphicManager* pMgr ) : GraphicObject(rUniqueID, pMgr) {}
    BfGraphicObject::~BfGraphicObject() {}

    BOOL                    BfGraphicObject::operator==( const BfGraphicObject& rCacheObj ) const { return GraphicObject::operator==(rCacheObj); }
    const Graphic&          BfGraphicObject::GetGraphic() const { return GraphicObject::GetGraphic(); }
    void                    BfGraphicObject::SetAttr( const BfGraphicAttr& rAttr ) { GraphicObject::SetAttr(rAttr); }
    const BfGraphicAttr&    BfGraphicObject::GetAttr() const { return (BfGraphicAttr&)GraphicObject::GetAttr(); }
    ByteString              BfGraphicObject::GetUniqueID() const { return GraphicObject::GetUniqueID(); }
    BfGraphicObject&        BfGraphicObject::operator=( const BfGraphicObject& rCacheObj ) { return (BfGraphicObject&)GraphicObject::operator=(rCacheObj); }
    void                    BfGraphicObject::SetUserData() { GraphicObject::SetUserData(); }
    void                    BfGraphicObject::SetUserData( const String& rUserData ) { GraphicObject::SetUserData(rUserData); }
    void                    BfGraphicObject::SetGraphic( const Graphic& rGraphic ) { GraphicObject::SetGraphic(rGraphic); }
    void                    BfGraphicObject::SetGraphic( const Graphic& rGraphic, const String& rLink ) { GraphicObject::SetGraphic(rGraphic, rLink); }
    void                    BfGraphicObject::SetSwapState() { GraphicObject::SetSwapState(); }
    void                    BfGraphicObject::FireSwapInRequest() { GraphicObject::FireSwapInRequest(); }
    void                    BfGraphicObject::FireSwapOutRequest() { GraphicObject::FireSwapOutRequest(); }
    void                    BfGraphicObject::StopAnimation( OutputDevice* pOut, long nExtraData) { GraphicObject::StopAnimation( pOut, nExtraData); }
    BOOL                    BfGraphicObject::Draw( OutputDevice* pOut, const Point& rPt, const Size& rSz, const BfGraphicAttr* pAttr, ULONG nFlags) { return GraphicObject::Draw( pOut, rPt, rSz, pAttr, nFlags); }
    String                  BfGraphicObject::GetUserData() const { return GraphicObject::GetUserData(); }
    void                    BfGraphicObject::SetSwapStreamHdl( const Link& rHdl, const ULONG nSwapOutTimeout) { GraphicObject::SetSwapStreamHdl( rHdl, nSwapOutTimeout); }
    void                    BfGraphicObject::ReleaseFromCache() { GraphicObject::ReleaseFromCache(); }
    String                  BfGraphicObject::GetLink() const { return GraphicObject::GetLink(); }
    void                    BfGraphicObject::SetLink( const String& rLink ) { GraphicObject::SetLink( rLink ); }
    BOOL                    BfGraphicObject::SwapOut() { return GraphicObject::SwapOut(); }
    BOOL                    BfGraphicObject::SwapOut( SvStream* pOStm ) { return GraphicObject::SwapOut( pOStm ); }
    BOOL                    BfGraphicObject::SwapIn() { return GraphicObject::SwapIn(); }
    BOOL                    BfGraphicObject::SwapIn( SvStream* pIStm ) { return GraphicObject::SwapIn( pIStm ); }
}//end of namespace binfilter

// eof
