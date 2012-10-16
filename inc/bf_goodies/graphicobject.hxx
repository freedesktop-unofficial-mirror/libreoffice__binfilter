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

#ifndef _BF_GOODIES_GRAPHICOBJECT_HXX
#define _BF_GOODIES_GRAPHICOBJECT_HXX

#include <bf_svtools/bf_solar.h>
#include <bf_tools/string.hxx>

#include <svtools/grfmgr.hxx>

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
        virtual SvStream* GetSwapStream() const;
        virtual void Load( SvStream& );
        virtual void Save( SvStream& ) {};
        virtual void Assign( const SvDataCopyStream& );

    public:
        TYPEINFO();
        BfGraphicObject( const GraphicManager* pMgr = NULL );
        BfGraphicObject( const Graphic& rGraphic, const GraphicManager* pMgr = NULL );
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
        void                    SetSwapStreamHdl( const Link& rHdl, const ULONG nSwapOutTimeout = 0UL );
        void                    ReleaseFromCache();
        String                  GetLink() const;
        void                    SetLink( const String& rLink );
        BOOL                    SwapIn();
        BOOL                    SwapIn( SvStream* pIStm );
    };
}//end of namespace binfilter
#endif // _BF_GOODIES_GRAPHICOBJECT_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
