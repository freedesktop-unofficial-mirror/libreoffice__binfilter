/*************************************************************************
 *
 *  $RCSfile: sd_anminfo.cxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: aw $ $Date: 2003-10-02 14:58:13 $
 *
 *  The Contents of this file are made available subject to the terms of
 *  either of the following licenses
 *
 *         - GNU Lesser General Public License Version 2.1
 *         - Sun Industry Standards Source License Version 1.1
 *
 *  Sun Microsystems Inc., October, 2000
 *
 *  GNU Lesser General Public License Version 2.1
 *  =============================================
 *  Copyright 2000 by Sun Microsystems, Inc.
 *  901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License version 2.1, as published by the Free Software Foundation.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *  MA  02111-1307  USA
 *
 *
 *  Sun Industry Standards Source License Version 1.1
 *  =================================================
 *  The contents of this file are subject to the Sun Industry Standards
 *  Source License Version 1.1 (the "License"); You may not use this file
 *  except in compliance with the License. You may obtain a copy of the
 *  License at http://www.openoffice.org/license.html.
 *
 *  Software provided under this License is provided on an "AS IS" basis,
 *  WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING,
 *  WITHOUT LIMITATION, WARRANTIES THAT THE SOFTWARE IS FREE OF DEFECTS,
 *  MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE, OR NON-INFRINGING.
 *  See the License for the specific provisions governing your rights and
 *  obligations concerning the Software.
 *
 *  The Initial Developer of the Original Code is: Sun Microsystems, Inc.
 *
 *  Copyright: 2000 by Sun Microsystems, Inc.
 *
 *  All Rights Reserved.
 *
 *  Contributor(s): _______________________________________
 *
 *
 ************************************************************************/

#ifndef _URLOBJ_HXX
#include <tools/urlobj.hxx>
#endif
#ifndef _SFXSMPLHINT_HXX //autogen
#include <svtools/smplhint.hxx>
#endif
#include "bf_svx/xtable.hxx"
#ifndef _SVDSURO_HXX //autogen
#include <bf_svx/svdsuro.hxx>
#endif
#ifndef _SVDOPATH_HXX //autogen
#include <bf_svx/svdopath.hxx>
#endif
#include <svtools/urihelper.hxx>

#pragma hdrstop

#include "anminfo.hxx"
#include "glob.hxx"
#include "sdiocmpt.hxx"
#include "drawdoc.hxx"

// #90477#
#ifndef _TOOLS_TENCCVT_HXX
#include <tools/tenccvt.hxx>
#endif

using namespace ::com::sun::star;

/*************************************************************************
|*
|* Konstruktor   (String aSecondSoundFile unbenutzt --> default ctor)
|*
\************************************************************************/

/*N*/ SdAnimationInfo::SdAnimationInfo(SdDrawDocument* pTheDoc)
/*N*/              : SdrObjUserData(SdUDInventor, SD_ANIMATIONINFO_ID, 0),
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
/*N*/                bInvisibleInPresentation   (FALSE),
/*N*/                nVerb                      (0),
/*N*/                pDoc                       (pTheDoc),
/*N*/                bShow                      (TRUE),
/*N*/                bIsShown                   (TRUE),
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
/*N*/                pPathObj                   (NULL),
/*N*/                pPathSuro                  (NULL),
/*N*/                eClickAction               (rAnmInfo.eClickAction),
/*N*/                eSecondEffect              (rAnmInfo.eSecondEffect),
/*N*/                eSecondSpeed               (rAnmInfo.eSecondSpeed),
/*N*/                bSecondSoundOn             (rAnmInfo.bSecondSoundOn),
/*N*/                bSecondPlayFull            (rAnmInfo.bSecondPlayFull),
/*N*/                bInvisibleInPresentation   (rAnmInfo.bInvisibleInPresentation),
/*N*/                nVerb                      (rAnmInfo.nVerb),
/*N*/                aBookmark                  (rAnmInfo.aBookmark),
/*N*/                aSecondSoundFile           (rAnmInfo.aSecondSoundFile),
/*N*/                pDoc                       (NULL),
/*N*/                bShow                      (rAnmInfo.bShow),
/*N*/                bIsShown                   (rAnmInfo.bIsShown),
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
|* Clone
|*
\************************************************************************/

//STRIP001 SdrObjUserData* SdAnimationInfo::Clone(SdrObject* pObj) const
//STRIP001 {
//STRIP001  return new SdAnimationInfo(*this);
//STRIP001 }


/*************************************************************************
|*
|* Daten in Stream schreiben
|*
\************************************************************************/

/*N*/ void SdAnimationInfo::WriteData(SvStream& rOut)
/*N*/ {
/*N*/   SdrObjUserData::WriteData(rOut);
/*N*/
/*N*/           // letzter Parameter ist die aktuelle Versionsnummer des Codes
/*N*/   SdIOCompat aIO(rOut, STREAM_WRITE, 9);
/*N*/
/*N*/   if(pPolygon)
/*N*/   {
/*N*/       rOut << (UINT16)1;  // es folgt ein Polygon
/*N*/       rOut << *pPolygon;
/*N*/   }
/*N*/   else
/*N*/       rOut << (UINT16)0;  // kein Polygon
/*N*/
/*N*/   rOut << aStart;
/*N*/   rOut << aEnd;
/*N*/   rOut << (UINT16)eEffect;
/*N*/   rOut << (UINT16)eSpeed;
/*N*/
/*N*/   rOut << (UINT16)bActive;
/*N*/   rOut << (UINT16)bDimPrevious;
/*N*/   rOut << (UINT16)bIsMovie;
/*N*/
/*N*/   rOut << aBlueScreen;
/*N*/   rOut << aDimColor;
/*N*/
/*N*/   // #90477# rtl_TextEncoding eSysEnc = ::GetStoreCharSet( gsl_getSystemTextEncoding() );
/*N*/   rtl_TextEncoding eSysEnc = GetSOStoreTextEncoding(gsl_getSystemTextEncoding(), (sal_uInt16)rOut.GetVersion());
/*N*/
/*N*/   rOut << (INT16) eSysEnc;
/*N*/
/*N*/   rOut.WriteByteString( INetURLObject::AbsToRel( aSoundFile,
/*N*/                                                  INetURLObject::WAS_ENCODED,
/*N*/                                                  INetURLObject::DECODE_UNAMBIGUOUS), eSysEnc );
/*N*/
/*N*/   rOut << bSoundOn;
/*N*/   rOut << bPlayFull;
/*N*/
/*N*/
/*N*/   if (pPathObj && pPathObj->IsInserted())
/*N*/   {
/*N*/        rOut << (USHORT)1;
/*N*/        SdrObjSurrogate aSuro(pPathObj);
/*N*/        rOut << aSuro;
/*N*/   }
/*N*/   else
/*N*/       rOut << (USHORT)0;
/*N*/
/*N*/   rOut << (UINT16)eClickAction;
/*N*/   rOut << (UINT16)eSecondEffect;
/*N*/   rOut << (UINT16)eSecondSpeed;
/*N*/
/*N*/   if (eClickAction == presentation::ClickAction_DOCUMENT || eClickAction == presentation::ClickAction_PROGRAM  ||
/*N*/       eClickAction == presentation::ClickAction_VANISH   || eClickAction == presentation::ClickAction_SOUND)
/*N*/   {
/*N*/       rOut.WriteByteString( INetURLObject::AbsToRel( aBookmark,
/*N*/                                                      INetURLObject::WAS_ENCODED,
/*N*/                                                      INetURLObject::DECODE_UNAMBIGUOUS), eSysEnc );
/*N*/   }
/*N*/   else
/*N*/       rOut.WriteByteString( aBookmark, eSysEnc );
/*N*/
/*N*/   rOut.WriteByteString( INetURLObject::AbsToRel(aSecondSoundFile,
/*N*/                                                 INetURLObject::WAS_ENCODED,
/*N*/                                                 INetURLObject::DECODE_UNAMBIGUOUS), eSysEnc );
/*N*/   rOut << (UINT16)bInvisibleInPresentation;
/*N*/   rOut << (UINT16)nVerb;
/*N*/
/*N*/   rOut << bSecondSoundOn;
/*N*/   rOut << bSecondPlayFull;
/*N*/
/*N*/   rOut << bDimHide;
/*N*/   rOut << (UINT16)eTextEffect;
/*N*/   rOut << (UINT32)nPresOrder;
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
/*N*/   rtl_TextEncoding eTextEnc;
/*N*/
/*N*/   // ab hier werden Daten der Versionen > 0 eingelesen
/*N*/   if (aIO.GetVersion() > 0)
/*N*/   {
/*N*/       INT16 nCharSet;
/*N*/       rIn >> nCharSet;
/*N*/
/*N*/       // #unicode# eTextEnc = (rtl_TextEncoding)nCharSet;
/*N*/       eTextEnc = (rtl_TextEncoding)GetSOLoadTextEncoding((rtl_TextEncoding)nCharSet, (sal_uInt16)rIn.GetVersion());
/*N*/
/*N*/       String aSoundFileRel;
/*N*/       rIn.ReadByteString( aSoundFileRel, eTextEnc );
/*N*/       if( aSoundFileRel.Len() )
/*N*/       {
/*N*/           INetURLObject aURLObj(::URIHelper::SmartRel2Abs( INetURLObject(INetURLObject::GetBaseURL()), aSoundFileRel, ::URIHelper::GetMaybeFileHdl(), false, false, INetURLObject::WAS_ENCODED, INetURLObject::DECODE_UNAMBIGUOUS, RTL_TEXTENCODING_UTF8, false, INetURLObject::FSYS_DETECT ));
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
/*N*/           String aBookmarkRel;
/*N*/           rIn.ReadByteString( aBookmarkRel, eTextEnc );
/*N*/           INetURLObject aURLObj(::URIHelper::SmartRelToAbs(aBookmarkRel, FALSE,
/*N*/                                                            INetURLObject::WAS_ENCODED,
/*N*/                                                            INetURLObject::DECODE_UNAMBIGUOUS));
/*N*/           aBookmark = aURLObj.GetMainURL( INetURLObject::NO_DECODE );
/*N*/       }
/*N*/       else
/*N*/           rIn.ReadByteString( aBookmark, eTextEnc );
/*N*/
/*N*/       String aSecondSoundFileRel;
/*N*/       rIn.ReadByteString( aSecondSoundFileRel, eTextEnc );
/*N*/       if( aSecondSoundFileRel.Len() )
/*N*/       {
/*N*/           INetURLObject aURLObj(::URIHelper::SmartRel2Abs( INetURLObject(INetURLObject::GetBaseURL()), aSecondSoundFileRel, ::URIHelper::GetMaybeFileHdl(), false, false, INetURLObject::WAS_ENCODED, INetURLObject::DECODE_UNAMBIGUOUS, RTL_TEXTENCODING_UTF8, false, INetURLObject::FSYS_DETECT ));
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

//STRIP001 void SdAnimationInfo::SetPath(SdrPathObj* pPath)
//STRIP001 {
//STRIP001  // alte Verbindung loesen, wenn eine besteht und die neue eine andere ist
//STRIP001  if (pPathObj != NULL && pPathObj != pPath)
//STRIP001  {
//STRIP001      // alte Verbindung loesen
//STRIP001      if (pDoc)
//STRIP001          EndListening(*pDoc);
//STRIP001      pPathObj->RemoveListener(*this);
//STRIP001      pPathObj = NULL;
//STRIP001  }
//STRIP001
//STRIP001  // ggfs. neue Verbindung herstellen, wenn es nicht die alte ist
//STRIP001  if (pPathObj != pPath && pPath != NULL)
//STRIP001  {
//STRIP001      if (pDoc == NULL)               // durch copy ctor entstanden
//STRIP001          pDoc = (SdDrawDocument*)pPath->GetModel();
//STRIP001      pPathObj = pPath;
//STRIP001      pPathObj->AddListener(*this);   // DYING
//STRIP001      StartListening(*pDoc);          // OBJ_INSERTED, OBJ_REMOVED
//STRIP001  }
//STRIP001 }

/*************************************************************************
|*
|* Notify, Aenderungen am Pfadobjekt
|*
\************************************************************************/

//STRIP001 void SdAnimationInfo::SFX_NOTIFY(SfxBroadcaster& rBC, const TypeId& rBCType, const SfxHint& rHint, const TypeId& rHintType)
//STRIP001 {
//STRIP001  SdrHint* pSdrHint = PTR_CAST(SdrHint,&rHint);
//STRIP001  if (pSdrHint)
//STRIP001  {
//STRIP001      SdrHintKind eKind = pSdrHint->GetKind();
//STRIP001      if (eKind == HINT_OBJREMOVED && pSdrHint->GetObject() == pPathObj)
//STRIP001          eEffect = presentation::AnimationEffect_NONE;
//STRIP001      else if (eKind == HINT_OBJINSERTED && pSdrHint->GetObject() == pPathObj)
//STRIP001          eEffect = presentation::AnimationEffect_PATH;
//STRIP001  }
//STRIP001
//STRIP001  SfxSimpleHint* pSimpleHint = PTR_CAST(SfxSimpleHint, &rHint);
//STRIP001  if (pSimpleHint)
//STRIP001  {
//STRIP001      ULONG nId = pSimpleHint->GetId();
//STRIP001      if (nId == SFX_HINT_DYING)
//STRIP001      {
//STRIP001          eEffect = presentation::AnimationEffect_NONE;
//STRIP001      }
//STRIP001  }
//STRIP001 }

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



