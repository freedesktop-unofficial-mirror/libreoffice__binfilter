/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file incorporates work covered by the following license notice:
 *
 *   Licensed to the Apache Software Foundation (ASF) under one or more
 *   contributor license agreements. See the NOTICE file distributed
 *   with this work for additional information regarding copyright
 *   ownership. The ASF licenses this file to you under the Apache
 *   License, Version 2.0 (the "License"); you may not use this file
 *   except in compliance with the License. You may obtain a copy of
 *   the License at http://www.apache.org/licenses/LICENSE-2.0 .
 */

#include "graphicobject.hxx"

namespace binfilter {
    BfGraphicAttr::BfGraphicAttr() : GraphicAttr() {}
    BfGraphicAttr::~BfGraphicAttr() {}
    void            BfGraphicAttr::SetTransparency( BYTE cTransparency ) { GraphicAttr::SetTransparency(cTransparency); }
}//end of namespace binfilter

namespace binfilter {
    TYPEINIT1_AUTOFACTORY( BfGraphicObject, GraphicObject);
    void BfGraphicObject::GraphicManagerDestroyed() { GraphicObject::GraphicManagerDestroyed(); }
    SvStream* BfGraphicObject::GetSwapStream() const { return GraphicObject::GetSwapStream(); }
    void BfGraphicObject::Load( SvStream& rSt ) { GraphicObject::Load(rSt); }
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
    BOOL                    BfGraphicObject::SwapIn() { return GraphicObject::SwapIn(); }
    BOOL                    BfGraphicObject::SwapIn( SvStream* pIStm ) { return GraphicObject::SwapIn( pIStm ); }
}//end of namespace binfilter

// eof

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
