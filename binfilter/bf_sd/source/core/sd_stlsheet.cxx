/*************************************************************************
 *
 *  $RCSfile: sd_stlsheet.cxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: aw $ $Date: 2003-10-02 14:58:15 $
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

#pragma hdrstop

#include "eetext.hxx"       // definiert ITEMID_... fuer frmitems und textitem
#ifndef _EEITEMID_HXX //autogen
#include <bf_svx/eeitemid.hxx>
#endif
#ifndef _SVX_FHGTITEM_HXX //autogen
#include <bf_svx/fhgtitem.hxx>
#endif
#ifndef _SVDOATTR_HXX //autogen
#include <bf_svx/svdoattr.hxx>
#endif
#ifndef _SVX_ULSPITEM_HXX //autogen
#include <bf_svx/ulspitem.hxx>
#endif
#ifndef _SFXSMPLHINT_HXX //autogen
#include <svtools/smplhint.hxx>
#endif

#include <bf_svx/bulitem.hxx>
#include <bf_svx/lrspitem.hxx>

#include "stlsheet.hxx"
#include "sdresid.hxx"
#include "sdpage.hxx"
#include "drawdoc.hxx"
#include "stlpool.hxx"
#include "glob.hrc"
#include "app.hrc"
#include "glob.hxx"

#ifndef SVX_LIGHT
#ifndef MAC
#include "../ui/inc/viewshel.hxx"
#include "../ui/inc/sdview.hxx"
#include "../ui/inc/tabcontr.hxx"
#include "../ui/inc/layertab.hxx"
#include "../ui/inc/viewshel.hxx"
#include "../ui/inc/drawview.hxx"
#include "../ui/inc/drviewsh.hxx"
#include "../ui/inc/docshell.hxx"
#include "../ui/inc/outlview.hxx"
#include "../ui/inc/outlnvsh.hxx"
#else
#include "drviewsh.hxx"
#include "outlnvsh.hxx"
#endif
#endif // !SVX_LIGHT

/*N*/ TYPEINIT1(SdStyleSheet, SfxStyleSheet);

/*************************************************************************
|*
|* Ctor
|*
\************************************************************************/

/*N*/ SdStyleSheet::SdStyleSheet(const String& rName, SfxStyleSheetBasePool& rPool,
/*N*/                          SfxStyleFamily eFamily, USHORT nMask) :
/*N*/   SfxStyleSheet(rName, rPool, eFamily, nMask)
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
|* Store
|*
\************************************************************************/

/*N*/ void SdStyleSheet::Store(SvStream& rOut)
/*N*/ {
/*N*/   SfxStyleSheetBase::Store(rOut);
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

//STRIP001 List* SdStyleSheet::CreateChildList() const
//STRIP001 {
//STRIP001  List* pResult = new List;
//STRIP001
//STRIP001  USHORT nListenerCount = GetListenerCount();
//STRIP001  if (nListenerCount > 0)
//STRIP001  {
//STRIP001      for (USHORT n = 0; n < nListenerCount; n++)
//STRIP001      {
//STRIP001          SfxListener* pListener = GetListener(n);
//STRIP001          // NULL-Pointer ist im Listener-Array erlaubt
//STRIP001          if (pListener && pListener->ISA(SdStyleSheet) &&
//STRIP001              ((SdStyleSheet*)pListener)->GetParent() == aName)
//STRIP001          {
//STRIP001              pResult->Insert((SdStyleSheet*)pListener, LIST_APPEND);
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  return pResult;
//STRIP001 }

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
/*N*/ #ifndef SVX_LIGHT
/*N*/   SfxViewShell* pViewShell = SfxViewShell::Current();
/*N*/
/*N*/   if (pViewShell && pViewShell->ISA(SdViewShell) &&
/*N*/       ((SdViewShell*) pViewShell)->GetDoc() == pDoc)
/*N*/   {
/*?*/       SdPage* pPage = ((SdDrawViewShell*) pViewShell)->GetActualPage();
        DBG_ASSERT(pPage, "aktuelle Seite nicht gefunden");
        aRealStyle = pPage->GetLayoutName();
        // hinter dem Separator abschneiden
        aRealStyle.Erase(aRealStyle.Search(aSep) + aSep.Len());
    }
/*N*/ #else
/*N*/   SdrPage* pPage = pDoc->GetSdPage(0, PK_STANDARD);
/*N*/   if( pPage )
/*N*/   {
/*N*/       aRealStyle = pPage->GetLayoutName();
/*N*/       aRealStyle.Erase(aRealStyle.Search(aSep) + aSep.Len());
/*N*/   }
/*N*/ #endif // !SVX_LIGHT
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
/*N*/   if (aName == String(SdResId(STR_PSEUDOSHEET_TITLE)))
/*N*/   {
/*N*/       aInternalName = String(SdResId(STR_LAYOUT_TITLE));
/*N*/   }
/*N*/   else if (aName == String(SdResId(STR_PSEUDOSHEET_SUBTITLE)))
/*N*/   {
/*N*/       aInternalName = String(SdResId(STR_LAYOUT_SUBTITLE));
/*N*/   }
/*N*/   else if (aName == String(SdResId(STR_PSEUDOSHEET_BACKGROUND)))
/*N*/   {
/*N*/       aInternalName = String(SdResId(STR_LAYOUT_BACKGROUND));
/*N*/   }
/*N*/   else if (aName == String(SdResId(STR_PSEUDOSHEET_BACKGROUNDOBJECTS)))
/*N*/   {
/*N*/       aInternalName = String(SdResId(STR_LAYOUT_BACKGROUNDOBJECTS));
/*N*/   }
/*N*/   else if (aName == String(SdResId(STR_PSEUDOSHEET_NOTES)))
/*N*/   {
/*N*/       aInternalName = String(SdResId(STR_LAYOUT_NOTES));
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       String aOutlineStr(SdResId(STR_PSEUDOSHEET_OUTLINE));
/*N*/       USHORT nPos = aName.Search(aOutlineStr);
/*N*/       if (nPos != STRING_NOTFOUND)
/*N*/       {
/*N*/           String aNumStr(aName.Copy(aOutlineStr.Len()));
/*N*/           aInternalName = String(SdResId(STR_LAYOUT_OUTLINE));
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

//STRIP001 SdStyleSheet* SdStyleSheet::GetPseudoStyleSheet() const
//STRIP001 {
//STRIP001  SdStyleSheet* pPseudoStyle = NULL;
//STRIP001  String aSep( RTL_CONSTASCII_USTRINGPARAM( SD_LT_SEPARATOR ));
//STRIP001  String aStyleName(aName);
//STRIP001      // ohne Layoutnamen und Separator
//STRIP001  aStyleName.Erase(0, aStyleName.Search(aSep) + aSep.Len());
//STRIP001
//STRIP001  if (aStyleName == String(SdResId(STR_LAYOUT_TITLE)))
//STRIP001  {
//STRIP001      aStyleName = String(SdResId(STR_PSEUDOSHEET_TITLE));
//STRIP001  }
//STRIP001  else if (aStyleName == String(SdResId(STR_LAYOUT_SUBTITLE)))
//STRIP001  {
//STRIP001      aStyleName = String(SdResId(STR_PSEUDOSHEET_SUBTITLE));
//STRIP001  }
//STRIP001  else if (aStyleName == String(SdResId(STR_LAYOUT_BACKGROUND)))
//STRIP001  {
//STRIP001      aStyleName = String(SdResId(STR_PSEUDOSHEET_BACKGROUND));
//STRIP001  }
//STRIP001  else if (aStyleName == String(SdResId(STR_LAYOUT_BACKGROUNDOBJECTS)))
//STRIP001  {
//STRIP001      aStyleName = String(SdResId(STR_PSEUDOSHEET_BACKGROUNDOBJECTS));
//STRIP001  }
//STRIP001  else if (aStyleName == String(SdResId(STR_LAYOUT_NOTES)))
//STRIP001  {
//STRIP001      aStyleName = String(SdResId(STR_PSEUDOSHEET_NOTES));
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      String aOutlineStr((SdResId(STR_LAYOUT_OUTLINE)));
//STRIP001      USHORT nPos = aStyleName.Search(aOutlineStr);
//STRIP001      if (nPos != STRING_NOTFOUND)
//STRIP001      {
//STRIP001          String aNumStr(aStyleName.Copy(aOutlineStr.Len()));
//STRIP001          aStyleName = String(SdResId(STR_PSEUDOSHEET_OUTLINE));
//STRIP001          aStyleName += aNumStr;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  pPseudoStyle = (SdStyleSheet*)rPool.Find(aStyleName, (SfxStyleFamily)SFX_STYLE_FAMILY_PSEUDO);
//STRIP001  DBG_ASSERT(pPseudoStyle, "PseudoStyleSheet nicht gefunden");
//STRIP001
//STRIP001  return pPseudoStyle;
//STRIP001 }


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

//STRIP001 void SdStyleSheet::AdjustToFontHeight(SfxItemSet& rSet, BOOL bOnlyMissingItems)
//STRIP001 {
//STRIP001  // Bulletbreite und Texteinzug an neue Fonthoehe
//STRIP001  // anpassen, wenn sie nicht explizit gesetzt wurden
//STRIP001  SfxStyleFamily eFamily = nFamily;
//STRIP001  String aStyleName(aName);
//STRIP001  if (eFamily == SFX_STYLE_FAMILY_PSEUDO)
//STRIP001  {
//STRIP001      SfxStyleSheet* pRealStyle = GetRealStyleSheet();
//STRIP001      eFamily = pRealStyle->GetFamily();
//STRIP001      aStyleName = pRealStyle->GetName();
//STRIP001  }
//STRIP001
//STRIP001  if (eFamily == SD_LT_FAMILY &&
//STRIP001      aStyleName.Search(String(SdResId(STR_LAYOUT_OUTLINE))) != STRING_NOTFOUND &&
//STRIP001      rSet.GetItemState(EE_CHAR_FONTHEIGHT) == SFX_ITEM_SET)
//STRIP001  {
//STRIP001      const SfxItemSet* pCurSet = &GetItemSet();
//STRIP001      UINT32 nNewHeight = ((SvxFontHeightItem&)rSet.Get(EE_CHAR_FONTHEIGHT)).GetHeight();
//STRIP001      UINT32 nOldHeight = ((SvxFontHeightItem&)pCurSet->Get(EE_CHAR_FONTHEIGHT)).GetHeight();
//STRIP001
//STRIP001      if (rSet.GetItemState(EE_PARA_BULLET) != SFX_ITEM_SET || !bOnlyMissingItems)
//STRIP001      {
//STRIP001          const SvxBulletItem& rBItem = (const SvxBulletItem&)pCurSet->Get(EE_PARA_BULLET);
//STRIP001          double fBulletFraction = double(rBItem.GetWidth()) / nOldHeight;
//STRIP001          SvxBulletItem aNewBItem(rBItem);
//STRIP001          aNewBItem.SetWidth((UINT32)(fBulletFraction * nNewHeight));
//STRIP001          rSet.Put(aNewBItem);
//STRIP001      }
//STRIP001
//STRIP001      if (rSet.GetItemState(EE_PARA_LRSPACE) != SFX_ITEM_SET || !bOnlyMissingItems)
//STRIP001      {
//STRIP001          const SvxLRSpaceItem& rLRItem = (const SvxLRSpaceItem&)pCurSet->Get(EE_PARA_LRSPACE);
//STRIP001          double fIndentFraction = double(rLRItem.GetTxtLeft()) / nOldHeight;
//STRIP001          SvxLRSpaceItem aNewLRItem(rLRItem);
//STRIP001          aNewLRItem.SetTxtLeft((USHORT)(fIndentFraction * nNewHeight));
//STRIP001          double fFirstIndentFraction = double(rLRItem.GetTxtFirstLineOfst()) / nOldHeight;
//STRIP001          aNewLRItem.SetTxtFirstLineOfst((short)(fFirstIndentFraction * nNewHeight));
//STRIP001          rSet.Put(aNewLRItem);
//STRIP001      }
//STRIP001
//STRIP001      if (rSet.GetItemState(EE_PARA_ULSPACE) != SFX_ITEM_SET || !bOnlyMissingItems)
//STRIP001      {
//STRIP001          const SvxULSpaceItem& rULItem = (const SvxULSpaceItem&)pCurSet->Get(EE_PARA_ULSPACE);
//STRIP001          SvxULSpaceItem aNewULItem(rULItem);
//STRIP001          double fLowerFraction = double(rULItem.GetLower()) / nOldHeight;
//STRIP001          aNewULItem.SetLower((USHORT)(fLowerFraction * nNewHeight));
//STRIP001          double fUpperFraction = double(rULItem.GetUpper()) / nOldHeight;
//STRIP001          aNewULItem.SetUpper((USHORT)(fUpperFraction * nNewHeight));
//STRIP001          rSet.Put(aNewULItem);
//STRIP001      }
//STRIP001  }
//STRIP001 }



//STRIP001 BOOL SdStyleSheet::HasFollowSupport() const
//STRIP001 {
//STRIP001  return FALSE;
//STRIP001 }

//STRIP001 BOOL SdStyleSheet::HasParentSupport() const
//STRIP001 {
//STRIP001  return TRUE;
//STRIP001 }

//STRIP001 BOOL SdStyleSheet::HasClearParentSupport() const
//STRIP001 {
//STRIP001  return TRUE;
//STRIP001 }
