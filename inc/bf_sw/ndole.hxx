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
#ifndef _NDOLE_HXX
#define _NDOLE_HXX

#include <bf_svtools/bf_solar.h>

#include <ndnotxt.hxx>

namespace binfilter {

class SvInPlaceObjectRef;
class SvInPlaceObject;

class SwGrfFmtColl;
class SwDoc;
class SwOLENode;
class SwOLELink;
class SwOLELRUCache;


class SwOLEObj
{
    friend class SwOLENode;

    static SwOLELRUCache* pOLELRU_Cache;

    const SwOLENode* pOLENd;

    //Entweder Ref oder Name sind bekannt, wenn nur der Name bekannt ist, wird
    //dir Ref bei Anforderung durch GetOleRef() vom Sfx besorgt.
    SvInPlaceObjectRef *pOLERef;    //new/delete, damit so2.hxx wegfaellt.
    String aName;

    SwOLEObj( const SwOLEObj& rObj );   //nicht erlaubt.
    SwOLEObj();

    void SetNode( SwOLENode* pNode );

public:
    SwOLEObj( SvInPlaceObject *pObj );
    SwOLEObj( const String &rName );
    ~SwOLEObj();

     BOOL RemovedFromLRU();

#ifndef _FESHVIEW_ONLY_INLINE_NEEDED
    SvInPlaceObjectRef GetOleRef();
    const String &GetName() const { return aName; }

    BOOL IsOleRef() const;  //Damit das Objekt nicht unnoetig geladen werden muss.
#endif
};


// --------------------
// SwOLENode
// --------------------

struct SwPersistentOleData;

class SwOLENode: public SwNoTxtNode
{
    friend class SwNodes;
    SwOLEObj aOLEObj;
    SwPersistentOleData* pSavedData;
    String sChartTblName;       // bei Chart Objecten: Name der ref. Tabelle
    BOOL   bOLESizeInvalid;     //Soll beim SwDoc::PrtOLENotify beruecksichtig
                                //werden (zum Beispiel kopiert). Ist nicht
                                //Persistent.

    SwOLENode(  const SwNodeIndex &rWhere,
                SvInPlaceObject *,
                SwGrfFmtColl *pGrfColl,
                SwAttrSet* pAutoAttr = 0 );

    SwOLENode(  const SwNodeIndex &rWhere,
                const String &rName,
                SwGrfFmtColl *pGrfColl,
                SwAttrSet* pAutoAttr = 0 );

    // aOLEObj besitzt einen privaten Copy-CTOR, wir brauchen auch einen:
    SwOLENode( const SwOLENode & );

public:
    const SwOLEObj& GetOLEObj() const { return aOLEObj; }
          SwOLEObj& GetOLEObj()       { return aOLEObj; }

    virtual SwCntntNode *SplitNode( const SwPosition & );
        // steht in ndcopy.cxx
    virtual SwCntntNode* MakeCopy( SwDoc*, const SwNodeIndex& ) const;

    virtual Size GetTwipSize() const;

    BOOL IsOLESizeInvalid() const   { return bOLESizeInvalid; }
    void SetOLESizeInvalid( BOOL b ){ bOLESizeInvalid = b; }

#ifndef _FESHVIEW_ONLY_INLINE_NEEDED
    const String& GetChartTblName() const       { return sChartTblName; }
    void SetChartTblName( const String& rNm )   { sChartTblName = rNm; }
#endif
};


// Inline Metoden aus Node.hxx - erst hier ist der TxtNode bekannt !!
inline SwOLENode *SwNode::GetOLENode()
{
     return ND_OLENODE == nNodeType ? (SwOLENode*)this : 0;
}

inline const SwOLENode *SwNode::GetOLENode() const
{
     return ND_OLENODE == nNodeType ? (const SwOLENode*)this : 0;
}

} //namespace binfilter
#endif  // _NDOLE_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
