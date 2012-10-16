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

#ifdef _MSC_VER
#pragma hdrstop
#endif

#include <bf_svx/eeitemid.hxx>

#include <bf_svx/eeitem.hxx>

#include <bf_svtools/itemset.hxx>
#include <bf_svtools/smplhint.hxx>
#include <bf_svx/xdef.hxx>
#include <bf_svx/svddef.hxx>
#include <bf_svx/svdoattr.hxx>
#include "stlsheet.hxx"
#include "sdresid.hxx"
#include "sdpage.hxx"
#include "drawdoc.hxx"
#include "stlpool.hxx"
#include "glob.hrc"
#include "glob.hxx"

namespace binfilter {

/*N*/ TYPEINIT1(SdStyleSheet, SfxStyleSheet);

/*************************************************************************
|*
|* Ctor
|*
\************************************************************************/

/*N*/ SdStyleSheet::SdStyleSheet(const String& rName, SfxStyleSheetBasePool& rInPool,
/*N*/                          SfxStyleFamily eFamily, USHORT nInMask) :
/*N*/   SfxStyleSheet(rName, rInPool, eFamily, nInMask)
/*N*/ {
/*N*/ }

/*************************************************************************
|*
|* Dtor
|*
\************************************************************************/

/*N*/ SdStyleSheet::~SdStyleSheet()
/*N*/ {
/*N*/   delete pSet;
/*N*/   pSet = NULL;    // damit nachfolgende Destruktoren eine Chance haben
/*N*/ }

/*************************************************************************
|*
|* Load
|*
\************************************************************************/

/*N*/ void SdStyleSheet::Load (SvStream& rIn, USHORT nVersion)
/*N*/ {
/*N*/   SfxStyleSheetBase::Load(rIn, nVersion);
/*N*/
/*N*/   // Die Default-Maske war frueher 0xAFFE.
/*N*/   // Aus dieser Default-Maske wurden die benoetigten Flags ausmaskiert.
/*N*/   // Nun wurde das Flag SFXSTYLEBIT_READONLY eingefuehrt, was dazu
/*N*/   // das alle StyleSheets read-only waren.
/*N*/   // Da im Draw kein StyleSheet read-only sein soll, wird an dieser Stelle
/*N*/   // das Flag zurueckgesetzt.
/*N*/   nMask &= ~SFXSTYLEBIT_READONLY;
/*N*/ }

/*************************************************************************
|*
|* Parent setzen
|*
\************************************************************************/

/*N*/ BOOL SdStyleSheet::SetParent(const String& rParentName)
/*N*/ {
/*N*/   BOOL bResult = FALSE;
/*N*/
/*N*/   if (SfxStyleSheet::SetParent(rParentName))
/*N*/   {
/*N*/       // PseudoStyleSheets haben keine eigenen ItemSets
/*N*/       if (nFamily != SFX_STYLE_FAMILY_PSEUDO)
/*N*/       {
/*N*/           if( rParentName.Len() )
/*N*/           {
/*N*/               SfxStyleSheetBase* pStyle = rPool.Find(rParentName, nFamily);
/*N*/               if (pStyle)
/*N*/               {
/*N*/                   bResult = TRUE;
/*N*/                   SfxItemSet& rParentSet = pStyle->GetItemSet();
/*N*/                   GetItemSet().SetParent(&rParentSet);
/*N*/                   Broadcast( SfxSimpleHint( SFX_HINT_DATACHANGED ) );
/*N*/               }
/*N*/           }
/*N*/           else
/*N*/           {
/*N*/               bResult = TRUE;
/*N*/               GetItemSet().SetParent(NULL);
/*N*/               Broadcast( SfxSimpleHint( SFX_HINT_DATACHANGED ) );
/*N*/           }
/*N*/       }
/*N*/       else
/*N*/       {
/*N*/           bResult = TRUE;
/*N*/       }
/*N*/   }
/*N*/   return bResult;
/*N*/ }

/*************************************************************************
|*
|* ItemSet ggfs. erzeugen und herausreichen
|*
\************************************************************************/

/*N*/ SfxItemSet& SdStyleSheet::GetItemSet()
/*N*/ {
/*N*/   if (nFamily == SFX_STYLE_FAMILY_PARA || nFamily == SD_LT_FAMILY)
/*N*/   {
/*N*/       // ggfs. das ItemSet 'on demand' anlegen
/*N*/       if (!pSet)
/*N*/       {
/*N*/           USHORT nWhichPairTable[] = { XATTR_LINE_FIRST,              XATTR_LINE_LAST,
/*N*/                                        XATTR_FILL_FIRST,              XATTR_FILL_LAST,
/*N*/
/*N*/                                        SDRATTR_SHADOW_FIRST,          SDRATTR_SHADOW_LAST,
/*N*/                                        SDRATTR_TEXT_MINFRAMEHEIGHT,   SDRATTR_TEXT_HORZADJUST,
/*N*/                                        SDRATTR_TEXT_ANIKIND,          SDRATTR_TEXT_CONTOURFRAME,
/*N*/                                        SDRATTR_EDGE_FIRST,            SDRATTR_EDGE_LAST,
/*N*/                                        SDRATTR_MEASURE_FIRST,         SDRATTR_MEASURE_LAST,
/*N*/
/*N*/                                        EE_PARA_START,                 EE_CHAR_END,
/*N*/
/*N*/                                        SDRATTR_XMLATTRIBUTES,         SDRATTR_XMLATTRIBUTES,
/*N*/
/*N*/                                        SDRATTR_3D_FIRST, SDRATTR_3D_LAST,
/*N*/                                        0, 0 };
/*N*/
/*N*/           pSet = new SfxItemSet(GetPool().GetPool(), nWhichPairTable);
/*N*/       }
/*N*/
/*N*/       return *pSet;
/*N*/   }
/*N*/
/*N*/   // dies ist eine Stellvertretervorlage fuer die interne Vorlage des
/*N*/   // aktuellen Praesentationslayouts: dessen ItemSet returnieren
/*N*/   else
/*N*/   {
/*N*/ //        return (GetRealStyleSheet()->GetItemSet());
/*N*/
/*N*/       SdStyleSheet* pSdSheet = GetRealStyleSheet();
/*N*/
/*N*/       if (pSdSheet)
/*N*/       {
/*N*/           return(pSdSheet->GetItemSet());
/*N*/       }
/*N*/       else
/*N*/       {
/*N*/           if (!pSet)
/*N*/           {
/*N*/               USHORT nWhichPairTable[] = { XATTR_LINE_FIRST,              XATTR_LINE_LAST,
/*N*/                                            XATTR_FILL_FIRST,              XATTR_FILL_LAST,
/*N*/
/*N*/                                            SDRATTR_SHADOW_FIRST,          SDRATTR_SHADOW_LAST,
/*N*/                                            SDRATTR_TEXT_MINFRAMEHEIGHT,   SDRATTR_TEXT_HORZADJUST,
/*N*/                                            SDRATTR_TEXT_ANIKIND,          SDRATTR_TEXT_CONTOURFRAME,
/*N*/                                            SDRATTR_EDGE_FIRST,            SDRATTR_EDGE_LAST,
/*N*/                                            SDRATTR_MEASURE_FIRST,         SDRATTR_MEASURE_LAST,
/*N*/
/*N*/                                            EE_PARA_START,                 EE_CHAR_END,
/*N*/
/*N*/                                           SDRATTR_XMLATTRIBUTES,          SDRATTR_XMLATTRIBUTES,
/*N*/
/*N*/                                           SDRATTR_3D_FIRST, SDRATTR_3D_LAST,
/*N*/                                            0, 0 };
/*N*/
/*N*/               pSet = new SfxItemSet(GetPool().GetPool(), nWhichPairTable);
/*N*/           }
/*N*/
/*N*/           return(*pSet);
/*N*/       }
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|* IsUsed(), eine Vorlage gilt als benutzt, wenn sie von eingefuegten Objekten
|*           oder von benutzten Vorlagen referenziert wird
|*
\************************************************************************/

/*N*/ BOOL SdStyleSheet::IsUsed() const
/*N*/ {
/*N*/   BOOL bResult = FALSE;
/*N*/
/*N*/   USHORT nListenerCount = GetListenerCount();
/*N*/   if (nListenerCount > 0)
/*?*/   {
/*?*/       for (USHORT n = 0; n < nListenerCount; n++)
/*?*/       {
/*?*/           SfxListener* pListener = GetListener(n);
            // NULL-Pointer ist im Listener-Array erlaubt
/*?*/           if (pListener && pListener->ISA(SdrAttrObj))
/*?*/           {
/*?*/               bResult = ((SdrAttrObj*)pListener)->IsInserted();
/*?*/           }
/*?*/           else if (pListener && pListener->ISA(SfxStyleSheet))
/*?*/           {
/*?*/               bResult = ((SfxStyleSheet*)pListener)->IsUsed();
/*?*/           }
/*?*/           if (bResult)
/*?*/               break;
/*?*/       }
/*?*/   }
/*N*/   return bResult;
/*N*/ }

/*************************************************************************
|*
|* CreateChildList, erstellt eine Liste der unmittelbaren Kinder dieser
|* Vorlage; die Liste gehoert dem Caller!
|*
\************************************************************************/


/*************************************************************************
|*
|* das StyleSheet ermitteln, fuer das dieses StyleSheet steht
|*
\************************************************************************/

/*N*/ SdStyleSheet* SdStyleSheet::GetRealStyleSheet() const
/*N*/ {
/*N*/   String aRealStyle;
/*N*/   String aSep( RTL_CONSTASCII_USTRINGPARAM( SD_LT_SEPARATOR ));
/*N*/   SdStyleSheet* pRealStyle = NULL;
/*N*/   SdDrawDocument* pDoc = ((SdStyleSheetPool&) rPool).GetDoc();
/*N*/
/*N*/   if (aRealStyle.Len() == 0)
/*N*/   {
/*N*/       SdPage* pPage = pDoc->GetSdPage(0, PK_STANDARD);
/*N*/
/*N*/       if (pPage)
/*N*/       {
/*N*/           aRealStyle = pDoc->GetSdPage(0, PK_STANDARD)->GetLayoutName();
/*N*/       }
/*N*/       else
/*N*/       {
/*N*/           // Noch keine Seite vorhanden
/*N*/           // Dieses kann beim Aktualisieren vonDokumentvorlagen vorkommen
/*?*/           SfxStyleSheetIterator aIter(&rPool, SD_LT_FAMILY);
            SfxStyleSheetBase* pSheet = aIter.First();
            if( pSheet )
                aRealStyle = pSheet->GetName();
        }

/*N*/       aRealStyle.Erase(aRealStyle.Search(aSep) + aSep.Len());
/*N*/   }
/*N*/
/*N*/   // jetzt vom Namen (landessprachlich angepasst) auf den internen
/*N*/   // Namen (unabhaengig von der Landessprache) mappen
/*N*/   String aInternalName;
/*N*/
/*N*/   if (aName.Equals(String(SdResId(STR_PSEUDOSHEET_TITLE).toString())))
/*N*/   {
/*N*/       aInternalName = SdResId(STR_LAYOUT_TITLE).toString();
/*N*/   }
/*N*/   else if (aName.Equals(String(SdResId(STR_PSEUDOSHEET_SUBTITLE).toString())))
/*N*/   {
/*N*/       aInternalName = SdResId(STR_LAYOUT_SUBTITLE).toString();
/*N*/   }
/*N*/   else if (aName.Equals(String(SdResId(STR_PSEUDOSHEET_BACKGROUND).toString())))
/*N*/   {
/*N*/       aInternalName = SdResId(STR_LAYOUT_BACKGROUND).toString();
/*N*/   }
/*N*/   else if (aName.Equals(String(SdResId(STR_PSEUDOSHEET_BACKGROUNDOBJECTS).toString())))
/*N*/   {
/*N*/       aInternalName = SdResId(STR_LAYOUT_BACKGROUNDOBJECTS).toString();
/*N*/   }
/*N*/   else if (aName.Equals(String(SdResId(STR_PSEUDOSHEET_NOTES).toString())))
/*N*/   {
/*N*/       aInternalName = SdResId(STR_LAYOUT_NOTES).toString();
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       String aOutlineStr(SdResId(STR_PSEUDOSHEET_OUTLINE).toString());
/*N*/       USHORT nPos = aName.Search(aOutlineStr);
/*N*/       if (nPos != STRING_NOTFOUND)
/*N*/       {
/*N*/           String aNumStr(aName.Copy(aOutlineStr.Len()));
/*N*/           aInternalName = SdResId(STR_LAYOUT_OUTLINE).toString();
/*N*/           aInternalName += aNumStr;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   aRealStyle += aInternalName;
/*N*/   pRealStyle = (SdStyleSheet*)rPool.Find(aRealStyle, SD_LT_FAMILY);
/*N*/   if( !pRealStyle )
/*N*/   {
/*N*/       SfxStyleSheetIterator aIter(&rPool, SD_LT_FAMILY);
/*N*/       if( aIter.Count() > 0 )
/*N*/           // StyleSheet not found, but pool already loaded
/*N*/           DBG_ASSERT(pRealStyle, "Internal StyleSheet not found");
/*N*/   }
/*N*/
/*N*/   return pRealStyle;
/*N*/ }

/*************************************************************************
|*
|* das PseudoStyleSheet ermitteln, durch das dieses StyleSheet vertreten wird
|*
\************************************************************************/



/*************************************************************************
|*
|* Notify
|*
\************************************************************************/

/*N*/ void SdStyleSheet::SFX_NOTIFY(SfxBroadcaster& rBC, const TypeId& rBCType,
/*N*/                             const SfxHint& rHint, const TypeId& rHintType)
/*N*/ {
/*N*/   // erstmal die Basisklassenfunktionalitaet
/*N*/   SfxStyleSheet::Notify(rBC, rHint);
/*N*/
/*N*/   // wenn der Stellvertreter ein Notify bezueglich geaenderter Attribute
/*N*/   // bekommt, sorgt er dafuer, dass das eigentlich gemeinte StyleSheet
/*N*/   // broadcastet
/*N*/   SfxSimpleHint* pSimple = PTR_CAST(SfxSimpleHint, &rHint);
/*N*/   ULONG nId = pSimple == NULL ? 0 : pSimple->GetId();
/*N*/   if (nId == SFX_HINT_DATACHANGED && nFamily == SFX_STYLE_FAMILY_PSEUDO)
/*N*/   {
/*?*/       SdStyleSheet* pRealStyle = GetRealStyleSheet();
/*?*/       if (pRealStyle)
/*?*/           pRealStyle->Broadcast(rHint);
/*N*/   }
/*N*/ }

/*************************************************************************
|* AdjustToFontHeight passt die Bulletbreite und den linken Texteinzug
|* des uebergebenen ItemSets dessen Fonthoehe an. Die neuen Werte werden so
|* berechnet, dass das Verhaeltnis zur Fonthoehe so ist wie im StyleSheet.
|*
|* bOnlyMissingItems legt fest, ob lediglich nicht gesetzte Items ergaenzt
|* (TRUE) oder explizit gesetzte Items ueberschreiben werden sollen (FALSE)
|*
\************************************************************************/






}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
