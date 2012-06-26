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
#ifndef _NDNOTXT_HXX
#define _NDNOTXT_HXX

#include <bf_svtools/bf_solar.h>

#include "node.hxx"
class PolyPolygon;
namespace binfilter {



// --------------------
// SwNoTxtNode
// --------------------

class SwNoTxtNode : public SwCntntNode
{
    friend class SwNodes;
    friend class SwNoTxtFrm;

    String aAlternateText;      // alternativer Text  (HTML)

    PolyPolygon *pContour;      // Polygon fuer Konturumlauf
    BOOL bAutomaticContour : 1; // automatic contour polygon, not manipulated
    BOOL bContourMapModeValid : 1; // contour map mode is not the graphics's
                                   // prefered map mode, but either
                                      // MM100 or or pixel
    BOOL bPixelContour : 1;     // contour map mode is invalid and pixel.

    // erzeugt fuer alle Ableitungen einen AttrSet mit Bereichen
    // fuer Frame- und Grafik-Attributen (wird nur vom SwCntntNode gerufen)
    virtual void NewAttrSet( SwAttrPool& );

    SwNoTxtNode( const SwNoTxtNode& );              //nicht erlaubt
    SwNoTxtNode &operator=( const SwNoTxtNode& );   //nicht erlaubt

protected:
    SwNoTxtNode( const SwNodeIndex &rWhere, const BYTE nNdType,
                SwGrfFmtColl *pGrColl, SwAttrSet* pAutoAttr = 0 );

public:
    ~SwNoTxtNode();

    virtual SwCntntFrm *MakeFrm();

    inline SwGrfFmtColl *GetGrfColl() const;

    virtual Size GetTwipSize() const = 0;


    // alternativen Text abfragen/setzen
    const String& GetAlternateText() const      { return aAlternateText; }
    void SetAlternateText( const String& rTxt, sal_Bool bBroadcast=sal_False );

    void               SetContour( const PolyPolygon *pPoly,
                                   BOOL bAutomatic = FALSE );
    const PolyPolygon *HasContour() const;
    BOOL           _HasContour() const { return pContour!=0; };

    void               SetAutomaticContour( BOOL bSet ) { bAutomaticContour = bSet; }
    BOOL         HasAutomaticContour() const { return bAutomaticContour; }

    // get either a MM100 or pixel contour, return FALSE if no contour is set.
    BOOL               GetContourAPI( PolyPolygon &rPoly ) const;

    void               SetPixelContour( BOOL bSet ) { bPixelContour = bSet; }
    BOOL         IsPixelContour() const;

    BOOL         IsContourMapModeValid() const { return bContourMapModeValid; }

    //Besorgt die Graphic, mit SwapIn fuer GrfNode, per GetData fuer OLE.
    Graphic GetGraphic() const;
};

inline SwGrfFmtColl* SwNoTxtNode::GetGrfColl() const
{
    return (SwGrfFmtColl*)GetRegisteredIn();
}

// Inline Metoden aus Node.hxx - erst hier ist der TxtNode bekannt !!
inline SwNoTxtNode *SwNode::GetNoTxtNode()
{
    return ND_NOTXTNODE & nNodeType ? (SwNoTxtNode*)this : 0;
}

inline const SwNoTxtNode *SwNode::GetNoTxtNode() const
{
    return ND_NOTXTNODE & nNodeType ? (const SwNoTxtNode*)this : 0;
}

} //namespace binfilter
#endif  // _NDNOTXT_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
