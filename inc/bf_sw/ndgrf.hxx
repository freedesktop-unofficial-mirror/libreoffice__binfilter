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
#ifndef _NDGRF_HXX
#define _NDGRF_HXX

#include <bf_svtools/bf_solar.h>


#include <bf_so3/lnkbase.hxx>
#include <bf_goodies/graphicobject.hxx>
#include <ndnotxt.hxx>
namespace binfilter {

class SvStorage;
class SwGrfFmtColl;
class SwDoc;
class BfGraphicAttr;


// --------------------
// SwGrfNode
// --------------------
class SwGrfNode: public SwNoTxtNode
{
    friend class SwNodes;
    friend class SwGrfFrm;

    BfGraphicObject aGrfObj;
    ::binfilter::SvBaseLinkRef refLink;     // falls Grafik nur als Link, dann Pointer gesetzt
    Size nGrfSize;
    String aNewStrmName;        // SW3/XML: new stream name (either SW3 stream
                                // name or package url)
    String aLowResGrf;          // HTML: LowRes Grafik (Ersatzdarstellung bis
                                //      die normale (HighRes) geladen ist.

    BOOL bTransparentFlagValid  :1;
    BOOL bInSwapIn              :1;
    BOOL bGrafikArrived         :1;
    BOOL bChgTwipSize           :1;
    BOOL bChgTwipSizeFromPixel  :1;
    BOOL bLoadLowResGrf         :1;
    BOOL bFrameInPaint          :1; //Um Start-/EndActions im Paint (ueber
                                    //SwapIn zu verhindern.
    BOOL bScaleImageMap         :1; //Image-Map in SetTwipSize skalieren

    SwGrfNode( const SwNodeIndex& rWhere,
               const String& rGrfName, const String& rFltName,
               const Graphic* pGraphic,
               SwGrfFmtColl* pGrfColl,
               SwAttrSet* pAutoAttr = 0 );
    // Ctor fuer Einlesen (SW/G) ohne Grafik
    SwGrfNode( const SwNodeIndex& rWhere,
               const String& rGrfName, const String& rFltName,
               SwGrfFmtColl* pGrfColl,
               SwAttrSet* pAutoAttr = 0 );
    SwGrfNode( const SwNodeIndex& rWhere,
               const BfGraphicObject& rGrfObj,
               SwGrfFmtColl* pGrfColl,
               SwAttrSet* pAutoAttr = 0 );

    void InsertLink( const String& rGrfName, const String& rFltName );
    BOOL ImportGraphic( SvStream& ){DBG_BF_ASSERT(0, "STRIP"); return FALSE;}
    BOOL HasStreamName() const { return aGrfObj.HasUserData(); }
    BOOL GetStreamStorageNames( String& rStrmName, String& rStgName ) const;

    DECL_LINK( SwapGraphic, BfGraphicObject* );

public:
    virtual ~SwGrfNode();

    const Graphic&          GetGrf() const      { return aGrfObj.GetGraphic(); }
    const BfGraphicObject&  GetGrfObj() const   { return aGrfObj; }
          BfGraphicObject&  GetGrfObj()         { return aGrfObj; }

    virtual SwCntntNode *SplitNode( const SwPosition & );

    virtual Size GetTwipSize() const;
#ifndef _FESHVIEW_ONLY_INLINE_NEEDED
    void SetTwipSize( const Size& rSz );

    inline BOOL IsAnimated() const              { return aGrfObj.IsAnimated(); }

    inline BOOL IsChgTwipSize() const           { return bChgTwipSize; }
    inline BOOL IsChgTwipSizeFromPixel() const  { return bChgTwipSizeFromPixel; }
    inline void SetChgTwipSize( BOOL b, BOOL bFromPx=FALSE )        { bChgTwipSize = b; bChgTwipSizeFromPixel = bFromPx; }

    inline BOOL IsGrafikArrived() const         { return bGrafikArrived; }
    inline void SetGrafikArrived( BOOL b )      { bGrafikArrived = b; }

    inline BOOL IsFrameInPaint() const          { return bFrameInPaint; }
    inline void SetFrameInPaint( BOOL b )       { bFrameInPaint = b; }

    inline BOOL IsScaleImageMap() const         { return bScaleImageMap; }
    inline void SetScaleImageMap( BOOL b )      { bScaleImageMap = b; }

    // alles fuers Laden der LowRes-Grafiken
    inline BOOL IsLoadLowResGrf() const         { return bLoadLowResGrf; }
    inline void SetLoadLowResGrf( BOOL b )      { bLoadLowResGrf = b; }
    const String& GetLowResGrfName() const      { return aLowResGrf; }
    void SetLowResGrfName( const String& r )    { aLowResGrf = r; }
#endif
        // steht in ndcopy.cxx
    virtual SwCntntNode* MakeCopy( SwDoc*, const SwNodeIndex& ) const;
#ifndef _FESHVIEW_ONLY_INLINE_NEEDED
        // erneutes Einlesen, falls Graphic nicht Ok ist. Die
        // aktuelle wird durch die neue ersetzt.
    BOOL ReRead( const String& rGrfName, const String& rFltName,
                  const Graphic* pGraphic = 0,
                  const BfGraphicObject* pGrfObj = 0,
                  BOOL bModify = TRUE );
        // Laden der Grafik unmittelbar vor der Anzeige
    short SwapIn( BOOL bWaitForData = FALSE );
    void SetStreamName( const String& r ) { aGrfObj.SetUserData( r ); }
    void SetNewStreamName( const String& r ) { aNewStrmName = r; }
    // is this node selected by any shell?
    BOOL IsSelected() const{DBG_BF_ASSERT(0, "STRIP");return FALSE;} ;
#endif

        // Der Grafik sagen, dass sich der Node im Undobereich befindet

#ifndef _FESHVIEW_ONLY_INLINE_NEEDED
        // Abfrage der Link-Daten
    BOOL IsGrfLink() const                  { return refLink.Is(); }
    inline BOOL IsLinkedFile() const;
    inline BOOL IsLinkedDDE() const;
    ::binfilter::SvBaseLinkRef GetLink() const  { return refLink; }
    BOOL GetFileFilterNms( String* pFileNm, String* pFilterNm ) const;

        // Prioritaet beim Laden der Grafik setzen. Geht nur, wenn der Link
        // ein FileObject gesetzt hat

    // Skalieren einer Image-Map: Die Image-Map wird um den Faktor
    // zwischen Grafik-Groesse und Rahmen-Groesse vergroessert/verkleinert

    // returns the with our graphic attributes filled Graphic-Attr-Structure

#endif
};


// ----------------------------------------------------------------------
// Inline Metoden aus Node.hxx - erst hier ist der TxtNode bekannt !!
inline       SwGrfNode   *SwNode::GetGrfNode()
{
     return ND_GRFNODE == nNodeType ? (SwGrfNode*)this : 0;
}
inline const SwGrfNode   *SwNode::GetGrfNode() const
{
     return ND_GRFNODE == nNodeType ? (const SwGrfNode*)this : 0;
}

#ifndef _FESHVIEW_ONLY_INLINE_NEEDED
inline BOOL SwGrfNode::IsLinkedFile() const
{
    return refLink.Is() && OBJECT_CLIENT_GRF == refLink->GetObjType();
}
inline BOOL SwGrfNode::IsLinkedDDE() const
{
    return refLink.Is() && OBJECT_CLIENT_DDE == refLink->GetObjType();
}
#endif


} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
