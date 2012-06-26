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

#include "bf_svx/xtable.hxx"
#include <bf_svx/svdsuro.hxx>
#include <bf_svx/svdopath.hxx>
#include <bf_svtools/urihelper.hxx>

#ifdef _MSC_VER
#pragma hdrstop
#endif

#include "anminfo.hxx"
#include "glob.hxx"
#include "sdiocmpt.hxx"
#include "drawdoc.hxx"

// #90477#
#include <tools/tenccvt.hxx>
#include "bf_so3/staticbaseurl.hxx"
namespace binfilter {

using namespace ::com::sun::star;

/*************************************************************************
|*
|* Konstruktor   (String aSecondSoundFile unbenutzt --> default ctor)
|*
\************************************************************************/

/*N*/ SdAnimationInfo::SdAnimationInfo(SdDrawDocument* pTheDoc)
/*N*/              : SdrObjUserData(SdUDInventor, SD_ANIMATIONINFO_ID, 0),
/*N*/                pDoc                       (pTheDoc),
/*N*/                pPolygon                   (NULL),
/*N*/                eEffect                    (presentation::AnimationEffect_NONE),
/*N*/                eTextEffect                (presentation::AnimationEffect_NONE),
/*N*/                eSpeed                     (presentation::AnimationSpeed_SLOW),
/*N*/                bActive                    (TRUE),
/*N*/                bDimPrevious               (FALSE),
/*N*/                bIsMovie                   (FALSE),
/*N*/                bDimHide                   (FALSE),
/*N*/                bSoundOn                   (FALSE),
/*N*/                bPlayFull                  (FALSE),
/*N*/                pPathSuro                  (NULL),
/*N*/                pPathObj                   (NULL),
/*N*/                eClickAction               (presentation::ClickAction_NONE),
/*N*/                eSecondEffect              (presentation::AnimationEffect_NONE),
/*N*/                eSecondSpeed               (presentation::AnimationSpeed_SLOW),
/*N*/                bSecondSoundOn             (FALSE),
/*N*/                bSecondPlayFull            (FALSE),
/*N*/                nVerb                      (0),
/*N*/                bInvisibleInPresentation   (FALSE),
/*N*/                bIsShown                   (TRUE),
/*N*/                bShow                      (TRUE),
/*N*/                bDimmed                    (FALSE),
/*N*/                nPresOrder                 (LIST_APPEND)
/*N*/ {
/*N*/   aBlueScreen = RGB_Color(COL_LIGHTMAGENTA);
/*N*/   aDimColor = RGB_Color(COL_LIGHTGRAY);
/*N*/ }

/*************************************************************************
|*
|* Copy Konstruktor
|* einige Anteile koennen nicht kopiert werden, da sie Referenzen in ein
|* bestimmtes Model bilden
|*
\************************************************************************/

/*N*/ SdAnimationInfo::SdAnimationInfo(const SdAnimationInfo& rAnmInfo)
/*N*/              : SdrObjUserData             (rAnmInfo),
/*N*/                SfxListener(),
/*N*/                pDoc                       (NULL),
/*N*/                pPolygon                   (NULL),
/*N*/                aStart                     (rAnmInfo.aStart),
/*N*/                aEnd                       (rAnmInfo.aEnd),
/*N*/                eEffect                    (rAnmInfo.eEffect),
/*N*/                eTextEffect                (rAnmInfo.eTextEffect),
/*N*/                eSpeed                     (rAnmInfo.eSpeed),
/*N*/                bActive                    (rAnmInfo.bActive),
/*N*/                bDimPrevious               (rAnmInfo.bDimPrevious),
/*N*/                bIsMovie                   (rAnmInfo.bIsMovie),
/*N*/                bDimHide                   (rAnmInfo.bDimHide),
/*N*/                aBlueScreen                (rAnmInfo.aBlueScreen),
/*N*/                aDimColor                  (rAnmInfo.aDimColor),
/*N*/                aSoundFile                 (rAnmInfo.aSoundFile),
/*N*/                bSoundOn                   (rAnmInfo.bSoundOn),
/*N*/                bPlayFull                  (rAnmInfo.bPlayFull),
/*N*/                pPathSuro                  (NULL),
/*N*/                pPathObj                   (NULL),
/*N*/                eClickAction               (rAnmInfo.eClickAction),
/*N*/                eSecondEffect              (rAnmInfo.eSecondEffect),
/*N*/                eSecondSpeed               (rAnmInfo.eSecondSpeed),
/*N*/                aSecondSoundFile           (rAnmInfo.aSecondSoundFile),
/*N*/                bSecondSoundOn             (rAnmInfo.bSecondSoundOn),
/*N*/                bSecondPlayFull            (rAnmInfo.bSecondPlayFull),
/*N*/                aBookmark                  (rAnmInfo.aBookmark),
/*N*/                nVerb                      (rAnmInfo.nVerb),
/*N*/                bInvisibleInPresentation   (rAnmInfo.bInvisibleInPresentation),
/*N*/                bIsShown                   (rAnmInfo.bIsShown),
/*N*/                bShow                      (rAnmInfo.bShow),
/*N*/                bDimmed                    (rAnmInfo.bDimmed),
/*N*/                nPresOrder                 (LIST_APPEND)
/*N*/ {
/*N*/   if (pPolygon)
/*N*/       pPolygon = new Polygon(*(rAnmInfo.pPolygon));
/*N*/
/*N*/   // kann nicht uebertragen werden
/*N*/   if (eEffect == presentation::AnimationEffect_PATH)
/*N*/       eEffect =  presentation::AnimationEffect_NONE;
/*N*/ }

/*************************************************************************
|*
|* Destruktor
|*
\************************************************************************/

/*N*/ SdAnimationInfo::~SdAnimationInfo()
/*N*/ {
/*N*/   delete pPathSuro;
/*N*/   delete pPolygon;
/*N*/ }

/*************************************************************************
|*
|* Daten aus Stream lesen
|*
\************************************************************************/

/*N*/ void SdAnimationInfo::ReadData(SvStream& rIn)
/*N*/ {
/*N*/   SdrObjUserData::ReadData(rIn);
/*N*/
/*N*/   SdIOCompat  aIO(rIn, STREAM_READ);
/*N*/   UINT32      nTemp32;
/*N*/   UINT16      nTemp;
/*N*/
/*N*/   rIn >> nTemp;
/*N*/   if (nTemp)
/*N*/   {
/*N*/       pPolygon = new Polygon;
/*N*/       rIn >> *pPolygon;
/*N*/   }
/*N*/
/*N*/   rIn >> aStart;
/*N*/   rIn >> aEnd;
/*N*/
/*N*/   rIn >> nTemp; eEffect = (presentation::AnimationEffect)nTemp;
/*N*/   rIn >> nTemp; eSpeed = (presentation::AnimationSpeed)nTemp;
/*N*/
/*N*/   rIn >> nTemp; bActive = (BOOL)nTemp;
/*N*/   rIn >> nTemp; bDimPrevious = (BOOL)nTemp;
/*N*/   rIn >> nTemp; bIsMovie = (BOOL)nTemp;
/*N*/
/*N*/   rIn >> aBlueScreen;
/*N*/   rIn >> aDimColor;
/*N*/
/*N*/   rtl_TextEncoding eTextEnc = RTL_TEXTENCODING_DONTKNOW;
/*N*/
/*N*/   // ab hier werden Daten der Versionen > 0 eingelesen
/*N*/   if (aIO.GetVersion() > 0)
/*N*/   {
/*N*/       INT16 nCharSet;
/*N*/       rIn >> nCharSet;
/*N*/
/*N*/       // #unicode# eTextEnc = (rtl_TextEncoding)nCharSet;
/*N*/       eTextEnc = (rtl_TextEncoding)GetSOLoadTextEncoding((rtl_TextEncoding)nCharSet);
/*N*/
/*N*/       String aSoundFileRel = rIn.ReadUniOrByteString( eTextEnc );
/*N*/       if( aSoundFileRel.Len() )
/*N*/       {
/*N*/           INetURLObject aURLObj(SmartRel2Abs( INetURLObject(::binfilter::StaticBaseUrl::GetBaseURL()), aSoundFileRel, ::binfilter::GetMaybeFileHdl(), false, false, INetURLObject::WAS_ENCODED, INetURLObject::DECODE_UNAMBIGUOUS, RTL_TEXTENCODING_UTF8, false, INetURLObject::FSYS_DETECT ));
/*N*/           aSoundFile = aURLObj.GetMainURL( INetURLObject::NO_DECODE );
/*N*/       }
/*N*/   }
/*N*/
/*N*/   // ab hier werden Daten der Versionen > 1 eingelesen
/*N*/   if (aIO.GetVersion() > 1)
/*N*/       rIn >> bSoundOn;
/*N*/
/*N*/   // ab hier werden Daten der Versionen > 2 eingelesen
/*N*/   if (aIO.GetVersion() > 2)
/*N*/       rIn >> bPlayFull;
/*N*/
/*N*/   // ab hier werden Daten der Versionen > 3 eingelesen
/*N*/   if (aIO.GetVersion() > 3)
/*N*/   {
/*N*/       USHORT nFlag;
/*N*/       rIn >> nFlag;
/*N*/       if (nFlag == 1)
/*N*/       {
/*N*/           DBG_ASSERT(pDoc, "kein Doc");
/*N*/           pPathSuro = new SdrObjSurrogate(*pDoc, rIn);
/*N*/       }
/*N*/   }
/*N*/
/*N*/   // ab hier werden Daten der Versionen > 4 eingelesen
/*N*/   if (aIO.GetVersion() > 4)
/*N*/   {
/*N*/       rIn >> nTemp; eClickAction  = (presentation::ClickAction)nTemp;
/*N*/       rIn >> nTemp; eSecondEffect = (presentation::AnimationEffect)nTemp;
/*N*/       rIn >> nTemp; eSecondSpeed  = (presentation::AnimationSpeed)nTemp;
/*N*/
/*N*/       if (eClickAction == presentation::ClickAction_DOCUMENT ||
/*N*/           eClickAction == presentation::ClickAction_PROGRAM  ||
/*N*/           eClickAction == presentation::ClickAction_VANISH   ||
/*N*/           eClickAction == presentation::ClickAction_SOUND)
/*N*/       {
/*N*/           String aBookmarkRel = rIn.ReadUniOrByteString( eTextEnc );
/*N*/           INetURLObject aURLObj(::binfilter::StaticBaseUrl::SmartRelToAbs(aBookmarkRel, FALSE,
/*N*/                                                            INetURLObject::WAS_ENCODED,
/*N*/                                                            INetURLObject::DECODE_UNAMBIGUOUS));
/*N*/           aBookmark = aURLObj.GetMainURL( INetURLObject::NO_DECODE );
/*N*/       }
/*N*/       else
/*N*/           aBookmark = rIn.ReadUniOrByteString( eTextEnc );
/*N*/
/*N*/       String aSecondSoundFileRel = rIn.ReadUniOrByteString( eTextEnc );
/*N*/       if( aSecondSoundFileRel.Len() )
/*N*/       {
/*N*/           INetURLObject aURLObj(SmartRel2Abs( INetURLObject(::binfilter::StaticBaseUrl::GetBaseURL()), aSecondSoundFileRel, ::binfilter::GetMaybeFileHdl(), false, false, INetURLObject::WAS_ENCODED, INetURLObject::DECODE_UNAMBIGUOUS, RTL_TEXTENCODING_UTF8, false, INetURLObject::FSYS_DETECT ));
/*N*/           aSecondSoundFile = aURLObj.GetMainURL( INetURLObject::NO_DECODE );
/*N*/       }
/*N*/
/*N*/       rIn >> nTemp; bInvisibleInPresentation = (BOOL)nTemp;
/*N*/       rIn >> nTemp; nVerb = (USHORT)nTemp;
/*N*/   }
/*N*/
/*N*/   // ab hier werden Daten der Versionen > 5 eingelesen
/*N*/   if (aIO.GetVersion() > 5)
/*N*/   {
/*N*/       rIn >> bSecondSoundOn;
/*N*/       rIn >> bSecondPlayFull;
/*N*/   }
/*N*/
/*N*/   // ab hier werden Daten der Versionen > 6 eingelesen
/*N*/   if (aIO.GetVersion() > 6)
/*N*/       rIn >> bDimHide;
/*N*/
/*N*/   // ab hier werden Daten der Versionen > 7 eingelesen
/*N*/   if (aIO.GetVersion() > 7)
/*N*/   {
/*N*/       rIn >> nTemp;
/*N*/       eTextEffect = (presentation::AnimationEffect)nTemp;
/*N*/   }
/*N*/
/*N*/   if (aIO.GetVersion() > 8)
/*N*/   {
/*N*/       rIn >> nTemp32;
/*N*/       nPresOrder = nTemp32;
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|* SetPath, Verbindung zum Pfadobjekt herstellen bzw. loesen
|*
\************************************************************************/


/*************************************************************************
|*
|* Notify, Aenderungen am Pfadobjekt
|*
\************************************************************************/


/*************************************************************************
|*
|* AfterRead, ggfs. Surrogat aufloesen
|*
\************************************************************************/

/*N*/ void SdAnimationInfo::AfterRead()
/*N*/ {
/*N*/   if (pPathSuro)
/*N*/   {
/*N*/       pPathObj = (SdrPathObj*)pPathSuro->GetObject();
/*N*/       DBG_ASSERT(pPathObj, "Surrogat kann nicht aufgeloest werden");
/*N*/   }
/*N*/ }



}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
