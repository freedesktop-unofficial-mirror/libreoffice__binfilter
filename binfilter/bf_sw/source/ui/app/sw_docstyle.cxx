/*************************************************************************
 *
 *  $RCSfile: sw_docstyle.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2004-05-05 16:41:16 $
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

#define _SVSTDARR_USHORTS

#ifndef _UIPARAM_HXX
#include <uiparam.hxx>
#endif
#ifndef _HINTIDS_HXX
#include <hintids.hxx>
#endif

#ifndef _SFXITEMITER_HXX
#include <svtools/itemiter.hxx>
#endif
#ifndef _SFXENUMITEM_HXX //autogen
#include <svtools/eitem.hxx>
#endif
#ifndef _SVX_BOXITEM_HXX
#include <bf_svx/boxitem.hxx>
#endif
#ifndef _SVX_NUMITEM_HXX //autogen
#include <bf_svx/numitem.hxx>
#endif

#ifndef _FMTCOL_HXX //autogen
#include <fmtcol.hxx>
#endif
#ifndef _UITOOL_HXX
#include <uitool.hxx>
#endif
#ifndef _SWMODULE_HXX
#include <swmodule.hxx>
#endif
#ifndef _WRTSH_HXX
#include <wrtsh.hxx>
#endif
#ifndef _DOCSH_HXX
#include <docsh.hxx>
#endif
#ifndef _ERRHDL_HXX
#include <errhdl.hxx>
#endif
#ifndef _FRMFMT_HXX
#include <frmfmt.hxx>
#endif
#ifndef _CHARFMT_HXX
#include <charfmt.hxx>
#endif
#ifndef _POOLFMT_HXX
#include <poolfmt.hxx>
#endif
#ifndef _PAGEDESC_HXX
#include <pagedesc.hxx>
#endif
#ifndef _DOCSTYLE_HXX
#include <docstyle.hxx>
#endif
#ifndef _DOCARY_HXX
#include <docary.hxx>
#endif
#ifndef _CCOLL_HXX
#include <ccoll.hxx>
#endif
#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _HINTS_HXX
#include <hints.hxx>
#endif
#ifndef _NUMRULE_HXX
#include <numrule.hxx>
#endif
#ifndef _UIITEMS_HXX
#include <uiitems.hxx>
#endif

#ifndef _CMDID_H
#include <cmdid.h>
#endif
#ifndef _SWSTYLE_H
#include <swstyle.h>
#endif
#ifndef _APP_HRC
#include <app.hrc>
#endif
#ifndef _SWSTYLENAMEMAPPER_HXX
#include <SwStyleNameMapper.hxx>
#endif
#ifndef _SVTOOLS_CJKOPTIONS_HXX
#include <svtools/cjkoptions.hxx>
#endif
#ifndef _COMPHELPER_PROCESSFACTORY_HXX_
#include <comphelper/processfactory.hxx>
#endif
#ifndef _UNOTOOLS_LOCALEDATAWRAPPER_HXX
#include <unotools/localedatawrapper.hxx>
#endif
#ifndef _UNOTOOLS_INTLWRAPPER_HXX
#include <unotools/intlwrapper.hxx>
#endif
#ifndef _LEGACYBINFILTERMGR_HXX
#include <legacysmgr/legacy_binfilters_smgr.hxx>    //STRIP002
#endif
namespace binfilter {

// MD 06.02.95: Die Formatnamen in der Liste aller Namen haben als
// erstes Zeichen die Familie:

#define cCHAR       (sal_Unicode)'c'
#define cPARA       (sal_Unicode)'p'
#define cFRAME      (sal_Unicode)'f'
#define cPAGE       (sal_Unicode)'g'
#define cNUMRULE    (sal_Unicode)'n'

// Dieses Zeichen wird bei der Herausgabe der Namen wieder entfernt und
// die Familie wird neu generiert.

// Ausserdem gibt es jetzt zusaetzlich das Bit bPhysical. Ist dieses Bit
// TRUE, werden die Pool-Formatnamen NICHT mit eingetragen.


/*N*/ class SwImplShellAction
/*N*/ {
/*N*/   SwWrtShell* pSh;
/*N*/   CurrShell* pCurrSh;
/*N*/ public:
/*N*/   SwImplShellAction( SwDoc& rDoc );
/*N*/   ~SwImplShellAction();
/*N*/
/*N*/   SwWrtShell* GetSh() { return pSh; }
/*N*/ };

/*N*/ SwImplShellAction::SwImplShellAction( SwDoc& rDoc )
/*N*/   : pCurrSh( 0 )
/*N*/ {
/*N*/   if( rDoc.GetDocShell() )
/*N*/       pSh = rDoc.GetDocShell()->GetWrtShell();
/*N*/   else
/*N*/       pSh = 0;
/*N*/
/*N*/   if( pSh )
/*N*/   {
/*N*/       pCurrSh = new CurrShell( pSh );
/*N*/       pSh->StartAllAction();
/*N*/   }
/*N*/ }

/*N*/ SwImplShellAction::~SwImplShellAction()
/*N*/ {
/*N*/   if( pCurrSh )
/*N*/   {
/*N*/       pSh->EndAllAction();
/*N*/       delete pCurrSh;
/*N*/   }
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung:   SwCharFormate finden/anlegen
                    evtl. Style fuellen
 --------------------------------------------------------------------*/

/*N*/ SwCharFmt* lcl_FindCharFmt(   SwDoc& rDoc,
/*N*/                           const String& rName,
/*N*/                           SwDocStyleSheet* pStyle = 0,
/*N*/                           FASTBOOL bCreate = TRUE )
/*N*/ {
/*N*/   SwCharFmt*  pFmt = 0;
/*N*/   if( rName.Len() )
/*N*/   {
/*N*/       pFmt = rDoc.FindCharFmtByName( rName );
/*N*/       if( !pFmt && rName == *SwStyleNameMapper::GetTextUINameArray()[ RES_POOLCOLL_STANDARD -
/*N*/                                               RES_POOLCOLL_TEXT_BEGIN ] )
/*N*/       {
/*N*/           // Standard-Zeichenvorlage
/*?*/           pFmt = (SwCharFmt*)rDoc.GetDfltCharFmt();
/*N*/       }
/*N*/
/*N*/       if( !pFmt && bCreate )
/*N*/       {   // Pool abklappern
/*N*/           const USHORT nId = SwStyleNameMapper::GetPoolIdFromUIName(rName, GET_POOLID_CHRFMT);
/*N*/           if(nId != USHRT_MAX)
/*N*/               pFmt = rDoc.GetCharFmtFromPool(nId);
/*N*/       }
/*N*/   }
/*N*/   if(pStyle)
/*N*/   {
/*N*/       if(pFmt)
/*N*/       {
/*N*/           pStyle->SetPhysical(TRUE);
/*N*/           SwFmt* p = pFmt->DerivedFrom();
/*N*/           if( p && !p->IsDefault() )
/*N*/               pStyle->PresetParent( p->GetName() );
/*N*/           else
/*N*/               pStyle->PresetParent( aEmptyStr );
/*N*/       }
/*N*/       else
/*N*/           pStyle->SetPhysical(FALSE);
/*N*/   }
/*N*/   return pFmt;
/*N*/ }


/*--------------------------------------------------------------------
    Beschreibung:   ParaFormate finden/erzeugen
                    Style fuellen
 --------------------------------------------------------------------*/

/*N*/ SwTxtFmtColl* lcl_FindParaFmt(    SwDoc& rDoc,
/*N*/                               const String& rName,
/*N*/                               SwDocStyleSheet* pStyle = 0,
/*N*/                               FASTBOOL bCreate = TRUE )
/*N*/ {
/*N*/   SwTxtFmtColl*   pColl = 0;
/*N*/
/*N*/   if( rName.Len() )
/*N*/   {
/*N*/       pColl = rDoc.FindTxtFmtCollByName( rName );
/*N*/       if( !pColl && bCreate )
/*N*/       {   // Pool abklappern
/*N*/           const USHORT nId = SwStyleNameMapper::GetPoolIdFromUIName(rName, GET_POOLID_TXTCOLL);
/*N*/           if(nId != USHRT_MAX)
/*N*/               pColl = rDoc.GetTxtCollFromPool(nId);
/*N*/       }
/*N*/   }
/*N*/
/*N*/   if(pStyle)
/*N*/   {
/*N*/       if(pColl)
/*N*/       {
/*N*/           pStyle->SetPhysical(TRUE);
/*N*/           if( pColl->DerivedFrom() && !pColl->DerivedFrom()->IsDefault() )
/*N*/               pStyle->PresetParent( pColl->DerivedFrom()->GetName() );
/*N*/           else
/*N*/               pStyle->PresetParent( aEmptyStr );
/*N*/
/*N*/           SwTxtFmtColl& rNext = pColl->GetNextTxtFmtColl();
/*N*/           pStyle->PresetFollow(rNext.GetName());
/*N*/       }
/*N*/       else
/*N*/           pStyle->SetPhysical(FALSE);
/*N*/   }
/*N*/   return pColl;
/*N*/ }


/*--------------------------------------------------------------------
    Beschreibung:   Rahmenformate
 --------------------------------------------------------------------*/


/*N*/ SwFrmFmt* lcl_FindFrmFmt( SwDoc& rDoc,
/*N*/                           const String& rName,
/*N*/                           SwDocStyleSheet* pStyle = 0,
/*N*/                           FASTBOOL bCreate = TRUE )
/*N*/ {
/*N*/   SwFrmFmt* pFmt = 0;
/*N*/   if( rName.Len() )
/*N*/   {
/*N*/       pFmt = rDoc.FindFrmFmtByName( rName );
/*N*/       if( !pFmt && bCreate )
/*N*/       {   // Pool abklappern
/*N*/           const USHORT nId = SwStyleNameMapper::GetPoolIdFromUIName(rName, GET_POOLID_FRMFMT);
/*N*/           if(nId != USHRT_MAX)
/*N*/               pFmt = rDoc.GetFrmFmtFromPool(nId);
/*N*/       }
/*N*/   }
/*N*/
/*N*/   if(pStyle)
/*N*/   {
/*N*/       if(pFmt)
/*N*/       {
/*N*/           pStyle->SetPhysical(TRUE);
/*N*/           if( pFmt->DerivedFrom() && !pFmt->DerivedFrom()->IsDefault() )
/*?*/               pStyle->PresetParent( pFmt->DerivedFrom()->GetName() );
/*N*/           else
/*N*/               pStyle->PresetParent( aEmptyStr );
/*N*/       }
/*N*/       else
/*N*/           pStyle->SetPhysical(FALSE);
/*N*/   }
/*N*/   return pFmt;
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung:   Seitendescriptoren
 --------------------------------------------------------------------*/


/*N*/ const SwPageDesc* lcl_FindPageDesc(   SwDoc&  rDoc,
/*N*/                                   const String&    rName,
/*N*/                                   SwDocStyleSheet* pStyle = 0,
/*N*/                                   FASTBOOL bCreate = TRUE )
/*N*/ {
/*N*/   const SwPageDesc* pDesc = 0;
/*N*/
/*N*/   if( rName.Len() )
/*N*/   {
/*N*/       pDesc = rDoc.FindPageDescByName( rName );
/*N*/       if( !pDesc && bCreate )
/*N*/       {
/*N*/           USHORT nId = SwStyleNameMapper::GetPoolIdFromUIName(rName, GET_POOLID_PAGEDESC);
/*N*/           if(nId != USHRT_MAX)
/*N*/               pDesc = rDoc.GetPageDescFromPool(nId);
/*N*/       }
/*N*/   }
/*N*/
/*N*/   if(pStyle)
/*N*/   {
/*N*/       if(pDesc)
/*N*/       {
/*N*/           pStyle->SetPhysical(TRUE);
/*N*/           if(pDesc->GetFollow())
/*N*/               pStyle->PresetFollow(pDesc->GetFollow()->GetName());
/*N*/           else
/*?*/               pStyle->PresetParent( aEmptyStr );
/*N*/       }
/*N*/       else
/*N*/           pStyle->SetPhysical(FALSE);
/*N*/   }
/*N*/   return pDesc;
/*N*/ }

/*N*/ const SwNumRule* lcl_FindNumRule( SwDoc&  rDoc,
/*N*/                                   const String&    rName,
/*N*/                                   SwDocStyleSheet* pStyle = 0,
/*N*/                                   FASTBOOL bCreate = TRUE )
/*N*/ {
/*N*/   const SwNumRule* pRule = 0;
/*N*/
/*N*/   if( rName.Len() )
/*N*/   {
/*N*/       pRule = rDoc.FindNumRulePtr( rName );
/*N*/       if( !pRule && bCreate )
/*N*/       {
/*N*/           USHORT nId = SwStyleNameMapper::GetPoolIdFromUIName(rName, GET_POOLID_NUMRULE);
/*N*/           if(nId != USHRT_MAX)
/*N*/               pRule = rDoc.GetNumRuleFromPool(nId);
/*N*/       }
/*N*/   }
/*N*/
/*N*/   if(pStyle)
/*N*/   {
/*N*/       if(pRule)
/*N*/       {
/*N*/           pStyle->SetPhysical(TRUE);
/*N*/           pStyle->PresetParent( aEmptyStr );
/*N*/       }
/*N*/       else
/*N*/           pStyle->SetPhysical(FALSE);
/*N*/   }
/*N*/   return pRule;
/*N*/ }


//STRIP001 USHORT lcl_FindName( const SwPoolFmtList& rLst, SfxStyleFamily eFam,
//STRIP001                      const String& rName )
//STRIP001 {
//STRIP001  if( rLst.Count() )
//STRIP001  {
//STRIP001      // suchen
//STRIP001      String sSrch( ' ' );
//STRIP001      switch( eFam )
//STRIP001      {
//STRIP001      case SFX_STYLE_FAMILY_CHAR:  sSrch = cCHAR;     break;
//STRIP001      case SFX_STYLE_FAMILY_PARA:  sSrch = cPARA;     break;
//STRIP001      case SFX_STYLE_FAMILY_FRAME: sSrch = cFRAME;    break;
//STRIP001      case SFX_STYLE_FAMILY_PAGE:  sSrch = cPAGE;     break;
//STRIP001      case SFX_STYLE_FAMILY_PSEUDO: sSrch = cNUMRULE; break;
//STRIP001      }
//STRIP001      sSrch += rName;
//STRIP001      for( USHORT i=0; i < rLst.Count(); ++i )
//STRIP001          if( *rLst[i] == sSrch )
//STRIP001              return i;
//STRIP001  }
//STRIP001  return USHRT_MAX;
//STRIP001 }

//STRIP001 FASTBOOL FindPhyStyle( SwDoc& rDoc, const String& rName, SfxStyleFamily eFam )
//STRIP001 {
//STRIP001  switch( eFam )
//STRIP001  {
//STRIP001  case SFX_STYLE_FAMILY_CHAR :
//STRIP001      return 0 != lcl_FindCharFmt( rDoc, rName, 0, FALSE );
//STRIP001  case SFX_STYLE_FAMILY_PARA :
//STRIP001      return 0 != lcl_FindParaFmt( rDoc, rName, 0, FALSE );
//STRIP001  case SFX_STYLE_FAMILY_FRAME:
//STRIP001      return 0 != lcl_FindFrmFmt( rDoc, rName, 0, FALSE );
//STRIP001  case SFX_STYLE_FAMILY_PAGE :
//STRIP001      return 0 != lcl_FindPageDesc( rDoc, rName, 0, FALSE );
//STRIP001  case SFX_STYLE_FAMILY_PSEUDO:
//STRIP001      return 0 != lcl_FindNumRule( rDoc, rName, 0, FALSE );
//STRIP001  }
//STRIP001  return FALSE;
//STRIP001 }


/*--------------------------------------------------------------------
    Beschreibung:   Einfuegen von Strings in die Liste der Vorlagen
 --------------------------------------------------------------------*/


/*N*/ void SwPoolFmtList::Append( char cChar, const String& rStr )
/*N*/ {
/*N*/   String* pStr = new String( cChar );
/*N*/   *pStr += rStr;
/*N*/   for ( USHORT i=0; i < Count(); ++i )
/*N*/   {
/*N*/       if( *operator[](i) == *pStr )
/*N*/       {
/*N*/           delete pStr;
/*N*/           return;
/*N*/       }
/*N*/   }
/*N*/   Insert( pStr, Count() );
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung:   Liste kompletti loeschen
 --------------------------------------------------------------------*/


/*N*/ void SwPoolFmtList::Erase()
/*N*/ {
/*N*/   DeleteAndDestroy( 0, Count() );
/*N*/ }

/*  */

/*--------------------------------------------------------------------
    Beschreibung:  UI-seitige implementierung von StyleSheets
                   greift auf die Core-Engine zu
 --------------------------------------------------------------------*/

/*N*/ SwDocStyleSheet::SwDocStyleSheet( SwDoc&          rDocument,
/*N*/                                   const String&           rName,
/*N*/                                   SwDocStyleSheetPool&    rPool,
/*N*/                                   SfxStyleFamily          eFam,
/*N*/                                   USHORT                  nMask) :
/*N*/
/*N*/   SfxStyleSheetBase( rName, rPool, eFam, nMask ),
/*N*/   rDoc(rDocument),
/*N*/   pCharFmt(0),
/*N*/   pFrmFmt(0),
/*N*/   pColl(0),
/*N*/   pDesc(0),
/*N*/   pNumRule(0),
/*N*/   bPhysical(FALSE),
/*N*/   aCoreSet(GetPool().GetPool(),
/*N*/           RES_CHRATR_BEGIN,       RES_CHRATR_END - 1,
/*N*/           RES_PARATR_BEGIN,       RES_PARATR_END - 1,
/*N*/           RES_FRMATR_BEGIN,       RES_FRMATR_END - 1,
/*N*/           RES_UNKNOWNATR_BEGIN,   RES_UNKNOWNATR_END-1,
/*N*/           SID_ATTR_PAGE,          SID_ATTR_PAGE_EXT1,
/*N*/           SID_ATTR_PAGE_HEADERSET,SID_ATTR_PAGE_FOOTERSET,
/*N*/           SID_ATTR_BORDER_INNER,  SID_ATTR_BORDER_INNER,
/*N*/           FN_PARAM_FTN_INFO,      FN_PARAM_FTN_INFO,
/*N*/           SID_ATTR_PARA_MODEL,    SID_ATTR_PARA_MODEL,
/*N*/           SID_ATTR_PARA_PAGENUM, SID_ATTR_PARA_PAGENUM,
/*N*/           SID_SWREGISTER_MODE,    SID_SWREGISTER_COLLECTION,
/*N*/           FN_COND_COLL,           FN_COND_COLL,
/*N*/           SID_ATTR_AUTO_STYLE_UPDATE, SID_ATTR_AUTO_STYLE_UPDATE,
/*N*/           SID_ATTR_NUMBERING_RULE,    SID_ATTR_NUMBERING_RULE,
/*N*/           SID_PARA_BACKGRND_DESTINATION,  SID_ATTR_BRUSH_CHAR,
/*N*/           SID_ATTR_NUMBERING_RULE,    SID_ATTR_NUMBERING_RULE,
/*N*/           0)
/*N*/ {
/*N*/   nHelpId = UCHAR_MAX;
/*N*/ }


/*N*/ SwDocStyleSheet::SwDocStyleSheet( const SwDocStyleSheet& rOrg) :
/*N*/   SfxStyleSheetBase(rOrg),
/*N*/   pCharFmt(rOrg.pCharFmt),
/*N*/   pFrmFmt(rOrg.pFrmFmt),
/*N*/   pColl(rOrg.pColl),
/*N*/   pDesc(rOrg.pDesc),
/*N*/   pNumRule(rOrg.pNumRule),
/*N*/   rDoc(rOrg.rDoc),
/*N*/   bPhysical(rOrg.bPhysical),
/*N*/   aCoreSet(rOrg.aCoreSet)
/*N*/ {
/*N*/ }


/*N*/  SwDocStyleSheet::~SwDocStyleSheet()
/*N*/ {
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung:   Zuruecksetzen
 --------------------------------------------------------------------*/


/*N*/ void  SwDocStyleSheet::Reset()
/*N*/ {
/*N*/   aName.Erase();
/*N*/   aFollow.Erase();
/*N*/   aParent.Erase();
/*N*/   SetPhysical(FALSE);
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung:   virtuelle Methoden
 --------------------------------------------------------------------*/


/*N*/ const String&  SwDocStyleSheet::GetParent() const
/*N*/ {
/*N*/   if( !bPhysical )
/*N*/   {
/*?*/       // dann pruefe, ob schon im Doc vorhanden
/*?*/       SwFmt* pFmt = 0;
/*?*/       SwGetPoolIdFromName eGetType;
/*?*/       switch(nFamily)
/*?*/       {
/*?*/       case SFX_STYLE_FAMILY_CHAR:
/*?*/           pFmt = rDoc.FindCharFmtByName( aName );
/*?*/           eGetType = GET_POOLID_CHRFMT;
/*?*/           break;
/*?*/
/*?*/       case SFX_STYLE_FAMILY_PARA:
/*?*/           pFmt = rDoc.FindTxtFmtCollByName( aName );
/*?*/           eGetType = GET_POOLID_TXTCOLL;
/*?*/           break;
/*?*/
/*?*/       case SFX_STYLE_FAMILY_FRAME:
/*?*/           pFmt = rDoc.FindFrmFmtByName( aName );
/*?*/           eGetType = GET_POOLID_FRMFMT;
/*?*/           break;
/*?*/
/*?*/       case SFX_STYLE_FAMILY_PAGE:
/*?*/       case SFX_STYLE_FAMILY_PSEUDO:
/*?*/       default:
/*?*/           return aEmptyStr;       // es gibt keinen Parent
/*?*/       }
/*?*/
/*?*/       String sTmp;
/*?*/       if( !pFmt )         // noch nicht vorhanden, also dflt. Parent
/*?*/       {
/*?*/           USHORT i = SwStyleNameMapper::GetPoolIdFromUIName( aName, eGetType );
/*?*/           i = ::binfilter::GetPoolParent( i );
/*?*/           if( i && USHRT_MAX != i )
/*?*/               SwStyleNameMapper::FillUIName( i, sTmp );
/*?*/       }
/*?*/       else
/*?*/       {
/*?*/           SwFmt* p = pFmt->DerivedFrom();
/*?*/           if( p && !p->IsDefault() )
/*?*/               sTmp = p->GetName();
/*?*/       }
/*?*/       SwDocStyleSheet* pThis = (SwDocStyleSheet*)this;
/*?*/       pThis->aParent = sTmp;
/*N*/   }
/*N*/   return aParent;
/*N*/ }

/*--------------------------------------------------------------------
   Beschreibung:    Nachfolger
 --------------------------------------------------------------------*/


/*N*/ const String&  SwDocStyleSheet::GetFollow() const
/*N*/ {
/*N*/   if( !bPhysical )
/*N*/   {
/*?*/       SwDocStyleSheet* pThis = (SwDocStyleSheet*)this;
/*?*/       pThis->FillStyleSheet( FillAllInfo );
/*N*/   }
/*N*/   return aFollow;
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung:   Welche Verkettung ist moeglich
 --------------------------------------------------------------------*/


//STRIP001 BOOL  SwDocStyleSheet::HasFollowSupport() const
//STRIP001 {
//STRIP001  switch(nFamily)
//STRIP001  {
//STRIP001      case SFX_STYLE_FAMILY_PARA :
//STRIP001      case SFX_STYLE_FAMILY_PAGE : return TRUE;
//STRIP001      case SFX_STYLE_FAMILY_FRAME:
//STRIP001      case SFX_STYLE_FAMILY_CHAR :
//STRIP001      case SFX_STYLE_FAMILY_PSEUDO: return FALSE;
//STRIP001      default:
//STRIP001          ASSERT(!this, "unbekannte Style-Familie");
//STRIP001  }
//STRIP001  return FALSE;
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung:   Parent ?
 --------------------------------------------------------------------*/


//STRIP001 BOOL  SwDocStyleSheet::HasParentSupport() const
//STRIP001 {
//STRIP001  BOOL bRet = FALSE;
//STRIP001  switch(nFamily)
//STRIP001  {
//STRIP001      case SFX_STYLE_FAMILY_CHAR :
//STRIP001      case SFX_STYLE_FAMILY_PARA :
//STRIP001      case SFX_STYLE_FAMILY_FRAME: bRet = TRUE;
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }


//STRIP001 BOOL  SwDocStyleSheet::HasClearParentSupport() const
//STRIP001 {
//STRIP001  BOOL bRet = FALSE;
//STRIP001  switch(nFamily)
//STRIP001  {
//STRIP001      case SFX_STYLE_FAMILY_PARA :
//STRIP001      case SFX_STYLE_FAMILY_CHAR :
//STRIP001      case SFX_STYLE_FAMILY_FRAME: bRet = TRUE;
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung:   textuelle Beschreibung ermitteln
 --------------------------------------------------------------------*/
//STRIP001 String  SwDocStyleSheet::GetDescription(SfxMapUnit eUnit)
//STRIP001 {
//STRIP001     IntlWrapper aIntlWrapper(
//STRIP001         ::legacy_binfilters::getLegacyProcessServiceFactory(),
//STRIP001         GetAppLocaleData().getLocale());
//STRIP001
//STRIP001     String sPlus(String::CreateFromAscii(" + "));
//STRIP001  if ( SFX_STYLE_FAMILY_PAGE == nFamily )
//STRIP001  {
//STRIP001      if( !pSet )
//STRIP001          GetItemSet();
//STRIP001
//STRIP001      SfxItemIter aIter( *pSet );
//STRIP001      String aDesc;
//STRIP001      const SfxPoolItem* pItem = aIter.FirstItem();
//STRIP001
//STRIP001      while ( pItem )
//STRIP001      {
//STRIP001          if(!IsInvalidItem(pItem))
//STRIP001              switch ( pItem->Which() )
//STRIP001              {
//STRIP001                  case RES_LR_SPACE:
//STRIP001                  case SID_ATTR_PAGE_SIZE:
//STRIP001                  case SID_ATTR_PAGE_MAXSIZE:
//STRIP001                  case SID_ATTR_PAGE_PAPERBIN:
//STRIP001                  case SID_ATTR_PAGE_APP:
//STRIP001                  case SID_ATTR_BORDER_INNER:
//STRIP001                      break;
//STRIP001                  default:
//STRIP001                  {
//STRIP001                      String aItemPresentation;
//STRIP001                      if ( !IsInvalidItem( pItem ) &&
//STRIP001                           rPool.GetPool().GetPresentation(
//STRIP001                              *pItem, SFX_ITEM_PRESENTATION_COMPLETE,
//STRIP001                                 eUnit, aItemPresentation, &aIntlWrapper ) )
//STRIP001                      {
//STRIP001                          if ( aDesc.Len() && aItemPresentation.Len() )
//STRIP001                              aDesc += sPlus;
//STRIP001                          aDesc += aItemPresentation;
//STRIP001                      }
//STRIP001                  }
//STRIP001              }
//STRIP001          pItem = aIter.NextItem();
//STRIP001      }
//STRIP001      return aDesc;
//STRIP001  }
//STRIP001  else if ( SFX_STYLE_FAMILY_FRAME == nFamily ||
//STRIP001                  SFX_STYLE_FAMILY_PARA == nFamily)
//STRIP001  {
//STRIP001      if( !pSet )
//STRIP001          GetItemSet();
//STRIP001
//STRIP001      SfxItemIter aIter( *pSet );
//STRIP001      String aDesc;
//STRIP001      const SfxPoolItem* pItem = aIter.FirstItem();
//STRIP001
//STRIP001      String sPageNum, sModel, sBreak;
//STRIP001         BOOL bHasWesternFontPrefix = FALSE;
//STRIP001         BOOL bHasCJKFontPrefix = FALSE;
//STRIP001         SvtCJKOptions aCJKOptions;
//STRIP001
//STRIP001      while ( pItem )
//STRIP001      {
//STRIP001          if(!IsInvalidItem(pItem))
//STRIP001              switch ( pItem->Which() )
//STRIP001              {
//STRIP001                  case SID_ATTR_AUTO_STYLE_UPDATE:
//STRIP001                  case SID_PARA_BACKGRND_DESTINATION:
//STRIP001                  case RES_PAGEDESC:
//STRIP001                     //CTL no yet supported
//STRIP001                     case RES_CHRATR_CTL_FONT:
//STRIP001                     case RES_CHRATR_CTL_FONTSIZE:
//STRIP001                     case RES_CHRATR_CTL_LANGUAGE:
//STRIP001                     case RES_CHRATR_CTL_POSTURE:
//STRIP001                     case RES_CHRATR_CTL_WEIGHT:
//STRIP001                         break;
//STRIP001                     default:
//STRIP001                  {
//STRIP001                      String aItemPresentation;
//STRIP001                      if ( !IsInvalidItem( pItem ) &&
//STRIP001                           rPool.GetPool().GetPresentation(
//STRIP001                              *pItem, SFX_ITEM_PRESENTATION_COMPLETE,
//STRIP001                                 eUnit, aItemPresentation, &aIntlWrapper ) )
//STRIP001                      {
//STRIP001                             BOOL bIsDefault = FALSE;
//STRIP001                          switch ( pItem->Which() )
//STRIP001                          {
//STRIP001                                 case SID_ATTR_PARA_PAGENUM:
//STRIP001                                  sPageNum = aItemPresentation;
//STRIP001                                  break;
//STRIP001                              case SID_ATTR_PARA_MODEL:
//STRIP001                                  sModel = aItemPresentation;
//STRIP001                                  break;
//STRIP001                              case RES_BREAK:
//STRIP001                                  sBreak = aItemPresentation;
//STRIP001                                  break;
//STRIP001                                 case RES_CHRATR_CJK_FONT:
//STRIP001                                 case RES_CHRATR_CJK_FONTSIZE:
//STRIP001                                 case RES_CHRATR_CJK_LANGUAGE:
//STRIP001                                 case RES_CHRATR_CJK_POSTURE:
//STRIP001                                 case RES_CHRATR_CJK_WEIGHT:
//STRIP001                                 if(aCJKOptions.IsCJKFontEnabled())
//STRIP001                                     bIsDefault = TRUE;
//STRIP001                                 if(!bHasCJKFontPrefix)
//STRIP001                                 {
//STRIP001                                     aItemPresentation.Insert(SW_RESSTR(STR_CJK_FONT), 0);
//STRIP001                                     bHasCJKFontPrefix = TRUE;
//STRIP001                                 }
//STRIP001                                 break;
//STRIP001                                 case RES_CHRATR_FONT:
//STRIP001                                 case RES_CHRATR_FONTSIZE:
//STRIP001                                 case RES_CHRATR_LANGUAGE:
//STRIP001                                 case RES_CHRATR_POSTURE:
//STRIP001                                 case RES_CHRATR_WEIGHT:
//STRIP001                                 if(!bHasWesternFontPrefix)
//STRIP001                                 {
//STRIP001                                     aItemPresentation.Insert(SW_RESSTR(STR_WESTERN_FONT), 0);
//STRIP001                                     bHasWesternFontPrefix = TRUE;
//STRIP001                                     bIsDefault = TRUE;
//STRIP001                                 }
//STRIP001                                 // no break;
//STRIP001                                 default:
//STRIP001                                     bIsDefault = TRUE;
//STRIP001                             }
//STRIP001                             if(bIsDefault)
//STRIP001                             {
//STRIP001                                 if ( aDesc.Len() && aItemPresentation.Len() )
//STRIP001                                  aDesc += sPlus;
//STRIP001                              aDesc += aItemPresentation;
//STRIP001                             }
//STRIP001                         }
//STRIP001                  }
//STRIP001              }
//STRIP001          pItem = aIter.NextItem();
//STRIP001      }
//STRIP001      //Sonderbehandlung fuer Umburch, Seitenvorlage und Seitenoffset
//STRIP001      if(sBreak.Len() && !sModel.Len())  // wemm Model. dann ist Break ungueltig
//STRIP001      {
//STRIP001          if(aDesc.Len())
//STRIP001              aDesc += sPlus;
//STRIP001          aDesc += sBreak;
//STRIP001      }
//STRIP001      if(sModel.Len())
//STRIP001      {
//STRIP001          if(aDesc.Len())
//STRIP001              aDesc += sPlus;
//STRIP001          aDesc += SW_RESSTR(STR_PAGEBREAK);
//STRIP001          aDesc += sPlus;
//STRIP001          aDesc += sModel;
//STRIP001          if(sPageNum != String(UniString::CreateFromInt32(0)))
//STRIP001          {
//STRIP001              aDesc += sPlus;
//STRIP001              aDesc += SW_RESSTR(STR_PAGEOFFSET);
//STRIP001              aDesc += sPageNum;
//STRIP001          }
//STRIP001      }
//STRIP001      return aDesc;
//STRIP001  }
//STRIP001  else if( SFX_STYLE_FAMILY_PSEUDO == nFamily )
//STRIP001  {
//STRIP001 //       if( pNumRule )
//STRIP001 //           return pNumRule->GetName();
//STRIP001      //os: was sollte man bei Numerierungen schon anzeigen?
//STRIP001      return aEmptyStr;
//STRIP001  }
//STRIP001
//STRIP001  return SfxStyleSheetBase::GetDescription(eUnit);
//STRIP001 }


//STRIP001 String  SwDocStyleSheet::GetDescription()
//STRIP001 {
//STRIP001  return GetDescription(SFX_MAPUNIT_CM);
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung:   Namen setzen
 --------------------------------------------------------------------*/


//STRIP001 BOOL  SwDocStyleSheet::SetName( const String& rStr)
//STRIP001 {
//STRIP001  if( !rStr.Len() )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  if( aName != rStr )
//STRIP001  {
//STRIP001      if( !SfxStyleSheetBase::SetName( rStr ))
//STRIP001          return FALSE;
//STRIP001  }
//STRIP001  else if(!bPhysical)
//STRIP001      FillStyleSheet( FillPhysical );
//STRIP001
//STRIP001  int bChg = FALSE;
//STRIP001  switch(nFamily)
//STRIP001  {
//STRIP001      case SFX_STYLE_FAMILY_CHAR :
//STRIP001      {
//STRIP001          ASSERT(pCharFmt, "SwCharFormat fehlt!");
//STRIP001          if( pCharFmt && pCharFmt->GetName() != rStr )
//STRIP001          {
//STRIP001              pCharFmt->SetName( rStr );
//STRIP001              bChg = TRUE;
//STRIP001          }
//STRIP001          break;
//STRIP001      }
//STRIP001      case SFX_STYLE_FAMILY_PARA :
//STRIP001      {
//STRIP001          ASSERT(pColl, "Collektion fehlt!");
//STRIP001          if( pColl && pColl->GetName() != rStr )
//STRIP001          {
//STRIP001              pColl->SetName( rStr );
//STRIP001              bChg = TRUE;
//STRIP001          }
//STRIP001          break;
//STRIP001      }
//STRIP001      case SFX_STYLE_FAMILY_FRAME:
//STRIP001      {
//STRIP001          ASSERT(pFrmFmt, "FrmFmt fehlt!");
//STRIP001          if( pFrmFmt && pFrmFmt->GetName() != rStr )
//STRIP001          {
//STRIP001              pFrmFmt->SetName( rStr );
//STRIP001              bChg = TRUE;
//STRIP001          }
//STRIP001          break;
//STRIP001      }
//STRIP001      case SFX_STYLE_FAMILY_PAGE :
//STRIP001          ASSERT(pDesc, "PageDesc fehlt!");
//STRIP001          if( pDesc && pDesc->GetName() != rStr )
//STRIP001          {
//STRIP001              //PageDesc setzen - mit vorherigem kopieren - ist fuer das
//STRIP001              //setzen des Namens wohl nicht notwendig. Deshalb erlauben
//STRIP001              //wir hier mal einen cast.
//STRIP001              ((SwPageDesc*)pDesc)->SetName( rStr );
//STRIP001              rDoc.SetModified();
//STRIP001              bChg = TRUE;
//STRIP001          }
//STRIP001          break;
//STRIP001      case SFX_STYLE_FAMILY_PSEUDO:
//STRIP001          ASSERT(pNumRule, "NumRule fehlt!");
//STRIP001          if( pNumRule && pNumRule->GetName() != rStr )
//STRIP001          {
//STRIP001              ((SwNumRule*)pNumRule)->SetName( rStr );
//STRIP001              rDoc.SetModified();
//STRIP001              bChg = TRUE;
//STRIP001          }
//STRIP001          break;
//STRIP001
//STRIP001
//STRIP001 #ifdef DBG_UTIL
//STRIP001      default:
//STRIP001          ASSERT(!this, "unbekannte Style-Familie");
//STRIP001 #endif
//STRIP001  }
//STRIP001
//STRIP001  if( bChg )
//STRIP001  {
//STRIP001      rPool.First();      // interne Liste muss geupdatet werden
//STRIP001      rPool.Broadcast( SfxStyleSheetHint( SFX_STYLESHEET_MODIFIED, *this ) );
//STRIP001      SwEditShell* pSh = rDoc.GetEditShell();
//STRIP001      if( pSh )
//STRIP001          pSh->CallChgLnk();
//STRIP001  }
//STRIP001  return TRUE;
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung:   Ableitungshirachie
 --------------------------------------------------------------------*/


/*N*/ BOOL   SwDocStyleSheet::SetParent( const String& rStr)
/*N*/ {
/*N*/   SwFmt* pFmt = 0, *pParent = 0;
/*N*/   switch(nFamily)
/*N*/   {
/*N*/       case SFX_STYLE_FAMILY_CHAR :
/*N*/           ASSERT( pCharFmt, "SwCharFormat fehlt!" )
/*N*/           if( 0 != ( pFmt = pCharFmt ) && rStr.Len() )
/*N*/               pParent = lcl_FindCharFmt(rDoc, rStr);
/*N*/           break;
/*N*/
/*N*/       case SFX_STYLE_FAMILY_PARA :
/*N*/           ASSERT( pColl, "Collektion fehlt!")
/*N*/           if( 0 != ( pFmt = pColl ) && rStr.Len() )
/*N*/               pParent = lcl_FindParaFmt( rDoc, rStr );
/*N*/           break;
/*N*/
/*N*/       case SFX_STYLE_FAMILY_FRAME:
/*?*/           ASSERT(pFrmFmt, "FrameFormat fehlt!");
/*?*/           if( 0 != ( pFmt = pFrmFmt ) && rStr.Len() )
/*?*/               pParent = lcl_FindFrmFmt( rDoc, rStr );
/*?*/           break;
/*N*/
/*N*/       case SFX_STYLE_FAMILY_PAGE:
/*N*/       case SFX_STYLE_FAMILY_PSEUDO:
/*N*/           break;
/*N*/       default:
/*N*/           ASSERT(!this, "unbekannte Style-Familie");
/*N*/   }
/*N*/
/*N*/   BOOL bRet = FALSE;
/*N*/   if( pFmt && pFmt->DerivedFrom() &&
/*N*/       pFmt->DerivedFrom()->GetName() != rStr )
/*N*/   {
/*N*/       {
/*N*/           SwImplShellAction aTmp( rDoc );
/*N*/           bRet = pFmt->SetDerivedFrom( pParent );
/*N*/       }
/*N*/
/*N*/       if( bRet )
/*N*/       {
/*N*/           aParent = rStr;
/*N*/           rPool.Broadcast( SfxStyleSheetHint( SFX_STYLESHEET_MODIFIED,
/*N*/                           *this ) );
/*N*/       }
/*N*/   }
/*N*/
/*N*/   return bRet;
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung:   Nachfolger detzen
 --------------------------------------------------------------------*/


/*N*/ BOOL   SwDocStyleSheet::SetFollow( const String& rStr)
/*N*/ {
/*N*/   if( rStr.Len() && !SfxStyleSheetBase::SetFollow( rStr ))
/*?*/       return FALSE;
/*N*/
/*N*/   SwImplShellAction aTmpSh( rDoc );
/*N*/   switch(nFamily)
/*N*/   {
/*N*/   case SFX_STYLE_FAMILY_PARA :
/*N*/   {
/*N*/       ASSERT(pColl, "Collection fehlt!");
/*N*/       if( pColl )
/*N*/       {
/*N*/           SwTxtFmtColl* pFollow = pColl;
/*N*/           if( rStr.Len() && 0 == (pFollow = lcl_FindParaFmt(rDoc, rStr) ))
/*?*/               pFollow = pColl;
/*N*/
/*N*/           pColl->SetNextTxtFmtColl(*pFollow);
/*N*/       }
/*N*/       break;
/*N*/   }
/*N*/   case SFX_STYLE_FAMILY_PAGE :
/*N*/   {
/*N*/       ASSERT(pDesc, "PageDesc fehlt!");
/*N*/       if( pDesc )
/*N*/       {
/*N*/           const SwPageDesc* pFollowDesc = rStr.Len()
/*N*/                                           ? lcl_FindPageDesc(rDoc, rStr)
/*N*/                                           : 0;
/*N*/           USHORT nId;
/*N*/           if( rDoc.FindPageDescByName( pDesc->GetName(), &nId ))
/*N*/           {
/*N*/               SwPageDesc aDesc( *pDesc );
/*N*/               aDesc.SetFollow( pFollowDesc );
/*N*/               rDoc.ChgPageDesc( nId, aDesc );
/*N*/               pDesc = &rDoc.GetPageDesc( nId );
/*N*/           }
/*N*/       }
/*N*/       break;
/*N*/   }
/*N*/   case SFX_STYLE_FAMILY_CHAR:
/*N*/   case SFX_STYLE_FAMILY_FRAME:
/*N*/   case SFX_STYLE_FAMILY_PSEUDO:
/*N*/       break;
/*N*/   default:
/*?*/       ASSERT(!this, "unbekannte Style-Familie");
/*N*/   }
/*N*/
/*N*/   return TRUE;
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung:   ueber Name und Family, Mask den ItemSet rausholen
 --------------------------------------------------------------------*/

/*N*/ SfxItemSet&   SwDocStyleSheet::GetItemSet()
/*N*/ {
/*N*/   if(!bPhysical)
/*?*/       FillStyleSheet( FillPhysical );
/*N*/
/*N*/   switch(nFamily)
/*N*/   {
/*N*/       case SFX_STYLE_FAMILY_CHAR:
/*N*/           {
/*N*/               ASSERT(pCharFmt, "Wo ist das SwCharFmt");
/*N*/               aCoreSet.Put(pCharFmt->GetAttrSet());
/*N*/               if(pCharFmt->DerivedFrom())
/*N*/                   aCoreSet.SetParent(&pCharFmt->DerivedFrom()->GetAttrSet());
/*N*/           }
/*N*/           break;
/*N*/       case SFX_STYLE_FAMILY_PARA :
/*N*/       case SFX_STYLE_FAMILY_FRAME:
/*N*/           {
/*N*/               SvxBoxInfoItem aBoxInfo;
/*N*/               aBoxInfo.SetTable( FALSE );
/*N*/               aBoxInfo.SetDist( TRUE);    // Abstandsfeld immer anzeigen
/*N*/               aBoxInfo.SetMinDist( TRUE );// Minimalgroesse in Tabellen und Absaetzen setzen
/*N*/               aBoxInfo.SetDefDist( MIN_BORDER_DIST );// Default-Abstand immer setzen
/*N*/                   // Einzelne Linien koennen nur in Tabellen DontCare-Status haben
/*N*/               aBoxInfo.SetValid( VALID_DISABLE, TRUE );
/*N*/               if ( nFamily == SFX_STYLE_FAMILY_PARA )
/*N*/               {
/*N*/                   ASSERT(pColl, "Wo ist die Collektion");
/*N*/                   aCoreSet.Put(pColl->GetAttrSet());
/*N*/                   aCoreSet.Put( aBoxInfo );
/*N*/                   aCoreSet.Put(SfxBoolItem(SID_ATTR_AUTO_STYLE_UPDATE, pColl->IsAutoUpdateFmt()));
/*N*/                   if(pColl->DerivedFrom())
/*N*/                       aCoreSet.SetParent(&pColl->DerivedFrom()->GetAttrSet());
/*N*/               }
/*N*/               else
/*N*/               {
/*N*/                   ASSERT(pFrmFmt, "Wo ist das FrmFmt");
/*N*/                   aCoreSet.Put(pFrmFmt->GetAttrSet());
/*N*/                   aCoreSet.Put( aBoxInfo );
/*N*/                   aCoreSet.Put(SfxBoolItem(SID_ATTR_AUTO_STYLE_UPDATE, pFrmFmt->IsAutoUpdateFmt()));
/*N*/                   if(pFrmFmt->DerivedFrom())
/*N*/                       aCoreSet.SetParent(&pFrmFmt->DerivedFrom()->GetAttrSet());
/*N*/               }
/*N*/           }
/*N*/           break;
/*N*/
/*N*/       case SFX_STYLE_FAMILY_PAGE :
/*N*/           {
/*N*/               ASSERT(pDesc, "Kein PageDescriptor");
/*N*/               ::binfilter::PageDescToItemSet(*((SwPageDesc*)pDesc), aCoreSet);
/*N*/           }
/*N*/           break;
/*N*/
/*N*/       case SFX_STYLE_FAMILY_PSEUDO:
/*N*/           {
/*N*/               ASSERT(pNumRule, "Keine NumRule");
/*N*/               SvxNumRule aRule = pNumRule->MakeSvxNumRule();
/*N*/               aCoreSet.Put(SvxNumBulletItem(aRule));
/*N*/           }
/*N*/           break;
/*N*/
/*N*/
/*N*/ #ifdef DBG_UTIL
/*N*/       default:
/*N*/           ASSERT(!this, "unbekannte Style-Familie");
/*N*/ #endif
/*N*/   }
/*N*/   // Member der Basisklasse
/*N*/   pSet = &aCoreSet;
/*N*/
/*N*/   return aCoreSet;
/*N*/ }
/*N*/
/*--------------------------------------------------------------------
    Beschreibung:   ItemSet setzen
 --------------------------------------------------------------------*/


/*N*/ void   SwDocStyleSheet::SetItemSet(const SfxItemSet& rSet)
/*N*/ {
/*N*/   // gegebenenfalls Format erst ermitteln
/*N*/   if(!bPhysical)
/*?*/       FillStyleSheet( FillPhysical );
/*N*/
/*N*/   SwImplShellAction aTmpSh( rDoc );
/*N*/
/*N*/   ASSERT( &rSet != &aCoreSet, "SetItemSet mit eigenem Set ist nicht erlaubt" );
/*N*/
/*N*/   SwFmt* pFmt = 0;
/*N*/   SwPageDesc* pNewDsc = 0;
/*N*/   USHORT nPgDscPos;
/*N*/
/*N*/   switch(nFamily)
/*N*/   {
/*N*/       case SFX_STYLE_FAMILY_CHAR :
/*N*/           {
/*N*/               ASSERT(pCharFmt, "Wo ist das CharFormat");
/*N*/               pFmt = pCharFmt;
/*N*/           }
/*N*/           break;
/*N*/
/*N*/       case SFX_STYLE_FAMILY_PARA :
/*N*/       {
/*N*/           ASSERT(pColl, "Wo ist die Collection");
/*N*/           const SfxPoolItem* pAutoUpdate;
/*N*/           if(SFX_ITEM_SET == rSet.GetItemState(SID_ATTR_AUTO_STYLE_UPDATE,FALSE, &pAutoUpdate ))
/*N*/           {
/*N*/               pColl->SetAutoUpdateFmt(((const SfxBoolItem*)pAutoUpdate)->GetValue());
/*N*/           }
/*N*/
/*N*/           const SwCondCollItem* pCondItem;
/*N*/           if( SFX_ITEM_SET != rSet.GetItemState( FN_COND_COLL, FALSE,
/*N*/               (const SfxPoolItem**)&pCondItem ))
/*N*/               pCondItem = 0;
/*N*/
/*N*/           if( RES_CONDTXTFMTCOLL == pColl->Which() && pCondItem )
/*N*/           {
/*?*/               DBG_BF_ASSERT(0, "STRIP"); //STRIP001 SwFmt* pFindFmt;
//STRIP001 /*?*/                const CommandStruct* pCmds = SwCondCollItem::GetCmds();
//STRIP001 /*?*/                for(USHORT i = 0; i < COND_COMMAND_COUNT; i++)
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    SwCollCondition aCond( 0, pCmds[ i ].nCnd, pCmds[ i ].nSubCond );
//STRIP001 /*?*/                    ((SwConditionTxtFmtColl*)pColl)->RemoveCondition( aCond );
//STRIP001 /*?*/                    const String& rStyle = pCondItem->GetStyle( i );
//STRIP001 /*?*/                    if( rStyle.Len() &&
//STRIP001 /*?*/                        0 != ( pFindFmt = lcl_FindParaFmt( rDoc, rStyle, 0, TRUE )))
//STRIP001 /*?*/                    {
//STRIP001 /*?*/                        pFindFmt->Add( &aCond );
//STRIP001 /*?*/                        ((SwConditionTxtFmtColl*)pColl)->InsertCondition( aCond );
//STRIP001 /*?*/                    }
//STRIP001 /*?*/                }
//STRIP001 /*?*/
//STRIP001 /*?*/                // Document auf die neue Bedingungen updaten
//STRIP001 /*?*/                SwCondCollCondChg aMsg( pColl );
//STRIP001 /*?*/                pColl->Modify( &aMsg, &aMsg );
/*N*/           }
/*N*/           else if( pCondItem && !pColl->GetDepends() )
/*N*/           {
/*?*/               // keine bedingte Vorlage, dann erstmal erzeugen und
/*?*/               // alle wichtigen Werte uebernehmen
/*?*/               DBG_BF_ASSERT(0, "STRIP"); //STRIP001 SwConditionTxtFmtColl* pCColl = rDoc.MakeCondTxtFmtColl(
//STRIP001 /*?*/                        pColl->GetName(), (SwTxtFmtColl*)pColl->DerivedFrom() );
//STRIP001 /*?*/                if( pColl != &pColl->GetNextTxtFmtColl() )
//STRIP001 /*?*/                    pCColl->SetNextTxtFmtColl( pColl->GetNextTxtFmtColl() );
//STRIP001 /*?*/
//STRIP001 /*?*/                pCColl->SetOutlineLevel( pColl->GetOutlineLevel() );
//STRIP001 /*?*/
//STRIP001 /*?*/                SwTxtFmtColl* pFindFmt;
//STRIP001 /*?*/                const CommandStruct* pCmds = SwCondCollItem::GetCmds();
//STRIP001 /*?*/                for( USHORT i = 0; i < COND_COMMAND_COUNT; ++i )
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    const String& rStyle = pCondItem->GetStyle( i );
//STRIP001 /*?*/                    if( rStyle.Len() &&
//STRIP001 /*?*/                        0 != ( pFindFmt = lcl_FindParaFmt( rDoc, rStyle, 0, TRUE )))
//STRIP001 /*?*/                    {
//STRIP001 /*?*/                        pCColl->InsertCondition( SwCollCondition( pFindFmt,
//STRIP001 /*?*/                                    pCmds[ i ].nCnd, pCmds[ i ].nSubCond ) );
//STRIP001 /*?*/                    }
//STRIP001 /*?*/                }
//STRIP001 /*?*/
//STRIP001 /*?*/                rDoc.DelTxtFmtColl( pColl );
//STRIP001 /*?*/                pColl = pCColl;
/*N*/           }
/*N*/           pFmt = pColl;

/*N*/           USHORT nId = pColl->GetPoolFmtId() &
/*N*/                           ~ ( COLL_GET_RANGE_BITS | POOLGRP_NOCOLLID );
/*N*/           switch( GetMask() & ( 0x0fff & ~SWSTYLEBIT_CONDCOLL ) )
/*N*/           {
/*N*/               case SWSTYLEBIT_TEXT:
/*N*/                   nId |= COLL_TEXT_BITS;
/*N*/                   break;
/*N*/               case SWSTYLEBIT_CHAPTER:
/*N*/                   nId |= COLL_DOC_BITS;
/*N*/                   break;
/*N*/               case SWSTYLEBIT_LIST:
/*N*/                   nId |= COLL_LISTS_BITS;
/*N*/                   break;
/*N*/               case SWSTYLEBIT_IDX:
/*N*/                   nId |= COLL_REGISTER_BITS;
/*N*/                   break;
/*N*/               case SWSTYLEBIT_EXTRA:
/*N*/                   nId |= COLL_EXTRA_BITS;
/*N*/                   break;
/*N*/               case SWSTYLEBIT_HTML:
/*N*/                   nId |= COLL_HTML_BITS;
/*N*/                   break;
/*N*/           }
/*N*/           pColl->SetPoolFmtId( nId );
/*N*/           break;
/*N*/       }
/*N*/       case SFX_STYLE_FAMILY_FRAME:
/*N*/       {
/*N*/           ASSERT(pFrmFmt, "Wo ist das FrmFmt");
/*N*/           const SfxPoolItem* pAutoUpdate;
/*N*/           if(SFX_ITEM_SET == rSet.GetItemState(SID_ATTR_AUTO_STYLE_UPDATE,FALSE, &pAutoUpdate ))
/*N*/           {
/*N*/               pFrmFmt->SetAutoUpdateFmt(((const SfxBoolItem*)pAutoUpdate)->GetValue());
/*N*/           }
/*N*/           pFmt = pFrmFmt;
/*N*/       }
/*N*/       break;
/*N*/
/*N*/       case SFX_STYLE_FAMILY_PAGE :
/*N*/           {
/*N*/               ASSERT(pDesc, "Wo ist der PageDescriptor");
/*N*/
/*N*/               if( rDoc.FindPageDescByName( pDesc->GetName(), &nPgDscPos ))
/*N*/               {
/*N*/                   pNewDsc = new SwPageDesc( *pDesc );
/*N*/                   pFmt = &pNewDsc->GetMaster();
/*N*/               }
/*N*/           }
/*N*/           break;
/*N*/
/*N*/       case SFX_STYLE_FAMILY_PSEUDO:
/*N*/           {
/*N*/               ASSERT(pNumRule, "Wo ist die NumRule");
/*N*/               const SfxPoolItem* pItem;
/*N*/               switch( rSet.GetItemState( SID_ATTR_NUMBERING_RULE, FALSE, &pItem ))
/*N*/               {
/*N*/               case SFX_ITEM_SET:
/*N*/               {
/*N*/                   SvxNumRule* pSetRule = ((SvxNumBulletItem*)pItem)->GetNumRule();
/*N*/                   pSetRule->UnLinkGraphics();
/*N*/                   //SwNumRule aSetRule(rDoc.GetUniqueNumRuleName());
/*N*/                   SwNumRule aSetRule(pNumRule->GetName());
/*N*/                   aSetRule.SetSvxRule(*pSetRule, &rDoc);
/*N*/                   rDoc.ChgNumRuleFmts( aSetRule );
/*N*/               }
/*N*/               break;
/*N*/               case SFX_ITEM_DONTCARE:
/*N*/                   // NumRule auf default Werte
/*N*/                   // was sind die default Werte?
/*N*/                   {
/*?*/                       SwNumRule aRule( pNumRule->GetName() );
/*?*/                       rDoc.ChgNumRuleFmts( aRule );
/*?*/                   }
/*N*/                   break;
/*N*/               }
/*N*/           }
/*N*/           break;
/*N*/
/*N*/ #ifdef DBG_UTIL
/*N*/       default:
/*N*/           ASSERT(!this, "unbekannte Style-Familie");
/*N*/ #endif
/*N*/   }
/*N*/
/*N*/   if( pFmt && rSet.Count())
/*N*/   {
/*N*/       SfxItemIter aIter( rSet );
/*N*/       const SfxPoolItem* pItem = aIter.GetCurItem();
/*N*/       while( TRUE )
/*N*/       {
/*N*/           if( IsInvalidItem( pItem ) )            // Clearen
/*?*/               pFmt->ResetAttr( rSet.GetWhichByPos(aIter.GetCurPos()));
/*N*/
/*N*/           if( aIter.IsAtEnd() )
/*N*/               break;
/*N*/           pItem = aIter.NextItem();
/*N*/       }
/*N*/       SfxItemSet aSet(rSet);
/*N*/       aSet.ClearInvalidItems();
/*N*/
/*N*/       aCoreSet.ClearItem();
/*N*/
/*N*/       if( pNewDsc )
/*N*/       {
/*N*/           ::binfilter::ItemSetToPageDesc( aSet, *pNewDsc );
/*N*/           rDoc.ChgPageDesc( nPgDscPos, *pNewDsc );
/*N*/           pDesc = &rDoc.GetPageDesc( nPgDscPos );
/*N*/           delete pNewDsc;
/*N*/       }
/*N*/       else
/*N*/           pFmt->SetAttr( aSet );      // alles gesetzten Putten
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       aCoreSet.ClearItem();
/*N*/       if( pNewDsc )           // den muessen wir noch vernichten!!
/*?*/           delete pNewDsc;
/*N*/   }
/*N*/ }

//STRIP001 void lcl_SaveStyles( USHORT nFamily, SvPtrarr& rArr, SwDoc& rDoc )
//STRIP001 {
//STRIP001  switch( nFamily )
//STRIP001  {
//STRIP001  case SFX_STYLE_FAMILY_CHAR:
//STRIP001      {
//STRIP001          const SwCharFmts& rTbl = *rDoc.GetCharFmts();
//STRIP001          for( sal_uInt16 n = 0, nCnt = rTbl.Count(); n < nCnt; ++n )
//STRIP001          {
//STRIP001              void* p = (void*)rTbl[ n ];
//STRIP001              rArr.Insert( p, n );
//STRIP001          }
//STRIP001      }
//STRIP001      break;
//STRIP001  case SFX_STYLE_FAMILY_PARA:
//STRIP001      {
//STRIP001          const SwTxtFmtColls& rTbl = *rDoc.GetTxtFmtColls();
//STRIP001          for( sal_uInt16 n = 0, nCnt = rTbl.Count(); n < nCnt; ++n )
//STRIP001          {
//STRIP001              void* p = (void*)rTbl[ n ];
//STRIP001              rArr.Insert( p, n );
//STRIP001          }
//STRIP001      }
//STRIP001      break;
//STRIP001  case SFX_STYLE_FAMILY_FRAME:
//STRIP001      {
//STRIP001          const SwFrmFmts& rTbl = *rDoc.GetFrmFmts();
//STRIP001          for( sal_uInt16 n = 0, nCnt = rTbl.Count(); n < nCnt; ++n )
//STRIP001          {
//STRIP001              void* p = (void*)rTbl[ n ];
//STRIP001              rArr.Insert( p, n );
//STRIP001          }
//STRIP001      }
//STRIP001      break;
//STRIP001
//STRIP001  case SFX_STYLE_FAMILY_PAGE:
//STRIP001      {
//STRIP001          for( sal_uInt16 n = 0, nCnt = rDoc.GetPageDescCnt(); n < nCnt; ++n )
//STRIP001          {
//STRIP001              void* p = (void*)&rDoc.GetPageDesc( n );
//STRIP001              rArr.Insert( p, n );
//STRIP001          }
//STRIP001      }
//STRIP001      break;
//STRIP001
//STRIP001  case SFX_STYLE_FAMILY_PSEUDO:
//STRIP001      {
//STRIP001          const SwNumRuleTbl& rTbl = rDoc.GetNumRuleTbl();
//STRIP001          for( sal_uInt16 n = 0, nCnt = rTbl.Count(); n < nCnt; ++n )
//STRIP001          {
//STRIP001              void* p = (void*)rTbl[ n ];
//STRIP001              rArr.Insert( p, n );
//STRIP001          }
//STRIP001      }
//STRIP001      break;
//STRIP001  }
//STRIP001 }

//STRIP001 void lcl_DeleteInfoStyles( USHORT nFamily, SvPtrarr& rArr, SwDoc& rDoc )
//STRIP001 {
//STRIP001  sal_uInt16 n, nCnt;
//STRIP001  switch( nFamily )
//STRIP001  {
//STRIP001  case SFX_STYLE_FAMILY_CHAR:
//STRIP001      {
//STRIP001          SvUShorts aDelArr;
//STRIP001          const SwCharFmts& rTbl = *rDoc.GetCharFmts();
//STRIP001          for( sal_uInt16 n = 0, nCnt = rTbl.Count(); n < nCnt; ++n )
//STRIP001          {
//STRIP001              void* p = (void*)rTbl[ n ];
//STRIP001              if( USHRT_MAX == rArr.GetPos( p ))
//STRIP001                  aDelArr.Insert( n, 0 );
//STRIP001          }
//STRIP001          for( n = 0, nCnt = aDelArr.Count(); n < nCnt; ++n )
//STRIP001              rDoc.DelCharFmt( aDelArr[ n ] );
//STRIP001      }
//STRIP001      break;
//STRIP001
//STRIP001  case SFX_STYLE_FAMILY_PARA :
//STRIP001      {
//STRIP001          SvUShorts aDelArr;
//STRIP001          const SwTxtFmtColls& rTbl = *rDoc.GetTxtFmtColls();
//STRIP001          for( sal_uInt16 n = 0, nCnt = rTbl.Count(); n < nCnt; ++n )
//STRIP001          {
//STRIP001              void* p = (void*)rTbl[ n ];
//STRIP001              if( USHRT_MAX == rArr.GetPos( p ))
//STRIP001                  aDelArr.Insert( n, 0 );
//STRIP001          }
//STRIP001          for( n = 0, nCnt = aDelArr.Count(); n < nCnt; ++n )
//STRIP001              rDoc.DelTxtFmtColl( aDelArr[ n ] );
//STRIP001      }
//STRIP001      break;
//STRIP001
//STRIP001  case SFX_STYLE_FAMILY_FRAME:
//STRIP001      {
//STRIP001          SvPtrarr aDelArr;
//STRIP001          const SwFrmFmts& rTbl = *rDoc.GetFrmFmts();
//STRIP001          for( sal_uInt16 n = 0, nCnt = rTbl.Count(); n < nCnt; ++n )
//STRIP001          {
//STRIP001              void* p = (void*)rTbl[ n ];
//STRIP001              if( USHRT_MAX == rArr.GetPos( p ))
//STRIP001                  aDelArr.Insert( p, 0 );
//STRIP001          }
//STRIP001          for( n = 0, nCnt = aDelArr.Count(); n < nCnt; ++n )
//STRIP001              rDoc.DelFrmFmt( (SwFrmFmt*)aDelArr[ n ] );
//STRIP001      }
//STRIP001      break;
//STRIP001
//STRIP001  case SFX_STYLE_FAMILY_PAGE:
//STRIP001      {
//STRIP001          SvUShorts aDelArr;
//STRIP001          for( n = 0, nCnt = rDoc.GetPageDescCnt(); n < nCnt; ++n )
//STRIP001          {
//STRIP001              void* p = (void*)&rDoc.GetPageDesc( n );
//STRIP001              if( USHRT_MAX == rArr.GetPos( p ))
//STRIP001                  aDelArr.Insert( n, 0 );
//STRIP001          }
//STRIP001          for( n = 0, nCnt = aDelArr.Count(); n < nCnt; ++n )
//STRIP001              rDoc.DelPageDesc( aDelArr[ n ] );
//STRIP001      }
//STRIP001      break;
//STRIP001
//STRIP001
//STRIP001  case SFX_STYLE_FAMILY_PSEUDO:
//STRIP001      {
//STRIP001          SvPtrarr aDelArr;
//STRIP001          const SwNumRuleTbl& rTbl = rDoc.GetNumRuleTbl();
//STRIP001          for( n = 0, nCnt = rTbl.Count(); n < nCnt; ++n )
//STRIP001          {
//STRIP001              void* p = (void*)rTbl[ n ];
//STRIP001              if( USHRT_MAX == rArr.GetPos( p ))
//STRIP001                  aDelArr.Insert( p, 0 );
//STRIP001          }
//STRIP001          for( n = 0, nCnt = aDelArr.Count(); n < nCnt; ++n )
//STRIP001              rDoc.DelNumRule( ((SwNumRule*)aDelArr[ n ])->GetName() );
//STRIP001      }
//STRIP001      break;
//STRIP001  }
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung:   Das Format ermitteln
 --------------------------------------------------------------------*/

/*N*/ BOOL SwDocStyleSheet::FillStyleSheet( FillStyleType eFType )
/*N*/ {
/*N*/   BOOL bRet = FALSE;
/*N*/   USHORT nPoolId = USHRT_MAX;
/*N*/   SwFmt* pFmt = 0;
/*N*/
/*N*/   BOOL bCreate = FillPhysical == eFType;
/*N*/   BOOL bDeleteInfo = FALSE;
/*N*/   BOOL bFillOnlyInfo = FillAllInfo == eFType;
/*N*/   SvPtrarr aDelArr;
/*N*/
/*N*/   switch(nFamily)
/*N*/   {
/*N*/   case SFX_STYLE_FAMILY_CHAR:
/*N*/       pCharFmt = lcl_FindCharFmt(rDoc, aName, this, bCreate );
/*N*/       bPhysical = 0 != pCharFmt;
/*N*/       if( bFillOnlyInfo && !bPhysical )
/*N*/       {
/*?*/       DBG_BF_ASSERT(0, "STRIP"); //STRIP001   bDeleteInfo = TRUE;
//STRIP001 /*?*/            ::lcl_SaveStyles( nFamily, aDelArr, rDoc );
//STRIP001 /*?*/            pCharFmt = lcl_FindCharFmt(rDoc, aName, this, TRUE );
/*N*/       }
/*N*/
/*N*/       pFmt = pCharFmt;
/*N*/       if( !bCreate && !pFmt )
/*N*/       {
/*N*/           if( aName == *SwStyleNameMapper::GetTextUINameArray()[ RES_POOLCOLL_STANDARD -
/*N*/                                           RES_POOLCOLL_TEXT_BEGIN ] )
/*N*/               nPoolId = 0;
/*N*/           else
/*N*/               nPoolId = SwStyleNameMapper::GetPoolIdFromUIName( aName, GET_POOLID_CHRFMT );
/*N*/       }
/*N*/
/*N*/       bRet = 0 != pCharFmt || USHRT_MAX != nPoolId;
/*N*/
/*N*/       if( bDeleteInfo )
/*?*/           pCharFmt = 0;
/*N*/       break;
/*N*/
/*N*/   case SFX_STYLE_FAMILY_PARA:
/*N*/       {
/*N*/           pColl = lcl_FindParaFmt(rDoc, aName, this, bCreate);
/*N*/           bPhysical = 0 != pColl;
/*N*/           if( bFillOnlyInfo && !bPhysical )
/*N*/           {
/*?*/           DBG_BF_ASSERT(0, "STRIP"); //STRIP001   bDeleteInfo = TRUE;
//STRIP001 /*?*/                ::lcl_SaveStyles( nFamily, aDelArr, rDoc );
//STRIP001 /*?*/                pColl = lcl_FindParaFmt(rDoc, aName, this, TRUE );
/*N*/           }
/*N*/
/*N*/           pFmt = pColl;
/*N*/           if( pColl )
/*N*/               PresetFollow( pColl->GetNextTxtFmtColl().GetName() );
/*N*/           else if( !bCreate )
/*N*/               nPoolId = SwStyleNameMapper::GetPoolIdFromUIName( aName, GET_POOLID_TXTCOLL );
/*N*/
/*N*/           bRet = 0 != pColl || USHRT_MAX != nPoolId;
/*N*/
/*N*/           if( bDeleteInfo )
/*N*/               pColl = 0;
/*N*/       }
/*N*/       break;
/*N*/
/*N*/   case SFX_STYLE_FAMILY_FRAME:
/*N*/       pFrmFmt = lcl_FindFrmFmt(rDoc,  aName, this, bCreate);
/*N*/       bPhysical = 0 != pFrmFmt;
/*N*/       if( bFillOnlyInfo && bPhysical )
/*N*/       {
/*?*/           DBG_BF_ASSERT(0, "STRIP"); //STRIP001 bDeleteInfo = TRUE;
//STRIP001 /*?*/            ::lcl_SaveStyles( nFamily, aDelArr, rDoc );
//STRIP001 /*?*/            pFrmFmt = lcl_FindFrmFmt(rDoc, aName, this, TRUE );
/*N*/       }
/*N*/       pFmt = pFrmFmt;
/*N*/       if( !bCreate && !pFmt )
/*N*/           nPoolId = SwStyleNameMapper::GetPoolIdFromUIName( aName, GET_POOLID_FRMFMT );
/*N*/
/*N*/       bRet = 0 != pFrmFmt || USHRT_MAX != nPoolId;
/*N*/
/*N*/       if( bDeleteInfo )
/*N*/           pFrmFmt = 0;
/*N*/       break;
/*N*/
/*N*/   case SFX_STYLE_FAMILY_PAGE:
/*N*/       pDesc = lcl_FindPageDesc(rDoc, aName, this, bCreate);
/*N*/       bPhysical = 0 != pDesc;
/*N*/       if( bFillOnlyInfo && !pDesc )
/*N*/       {
/*?*/           DBG_BF_ASSERT(0, "STRIP"); //STRIP001 bDeleteInfo = TRUE;
//STRIP001 /*?*/            ::lcl_SaveStyles( nFamily, aDelArr, rDoc );
//STRIP001 /*?*/            pDesc = lcl_FindPageDesc( rDoc, aName, this, TRUE );
/*N*/       }
/*N*/
/*N*/       if( pDesc )
/*N*/       {
/*N*/           nPoolId = pDesc->GetPoolFmtId();
/*N*/           nHelpId = pDesc->GetPoolHelpId();
/*N*/           if( pDesc->GetPoolHlpFileId() != UCHAR_MAX )
/*?*/               aHelpFile = *rDoc.GetDocPattern( pDesc->GetPoolHlpFileId() );
/*N*/           else
/*N*/               aHelpFile.Erase();
/*N*/       }
/*N*/       else if( !bCreate )
/*N*/           nPoolId = SwStyleNameMapper::GetPoolIdFromUIName( aName, GET_POOLID_PAGEDESC );
/*N*/       SetMask( USER_FMT & nPoolId ? SFXSTYLEBIT_USERDEF : 0 );
/*N*/
/*N*/       bRet = 0 != pDesc || USHRT_MAX != nPoolId;
/*N*/       if( bDeleteInfo )
/*N*/           pDesc = 0;
/*N*/       break;
/*N*/
/*N*/   case SFX_STYLE_FAMILY_PSEUDO:
/*N*/       pNumRule = lcl_FindNumRule(rDoc, aName, this, bCreate);
/*N*/       bPhysical = 0 != pNumRule;
/*N*/       if( bFillOnlyInfo && !pNumRule )
/*N*/       {
/*?*/           DBG_BF_ASSERT(0, "STRIP"); //STRIP001 bDeleteInfo = TRUE;
//STRIP001 /*?*/            ::lcl_SaveStyles( nFamily, aDelArr, rDoc );
//STRIP001 /*?*/            pNumRule = lcl_FindNumRule( rDoc, aName, this, TRUE );
/*N*/       }
/*N*/
/*N*/       if( pNumRule )
/*N*/       {
/*N*/           nPoolId = pNumRule->GetPoolFmtId();
/*N*/           nHelpId = pNumRule->GetPoolHelpId();
/*N*/           if( pNumRule->GetPoolHlpFileId() != UCHAR_MAX )
/*N*/               aHelpFile = *rDoc.GetDocPattern( pNumRule->GetPoolHlpFileId() );
/*N*/           else
/*N*/               aHelpFile.Erase();
/*N*/       }
/*N*/       else if( !bCreate )
/*N*/           nPoolId = SwStyleNameMapper::GetPoolIdFromUIName( aName, GET_POOLID_NUMRULE );
/*N*/       SetMask( USER_FMT & nPoolId ? SFXSTYLEBIT_USERDEF : 0 );
/*N*/
/*N*/       bRet = 0 != pNumRule || USHRT_MAX != nPoolId;
/*N*/
/*N*/       if( bDeleteInfo )
/*N*/           pNumRule = 0;
/*N*/       break;
/*N*/   }
/*N*/
/*N*/   if( SFX_STYLE_FAMILY_CHAR == nFamily ||
/*N*/       SFX_STYLE_FAMILY_PARA == nFamily ||
/*N*/       SFX_STYLE_FAMILY_FRAME == nFamily )
/*N*/   {
/*N*/       if( pFmt )
/*N*/           nPoolId = pFmt->GetPoolFmtId();
/*N*/
/*N*/       USHORT nMask = 0;
/*N*/       if( pFmt == rDoc.GetDfltCharFmt() )
/*N*/           nMask |= SFXSTYLEBIT_READONLY;
/*N*/       else if( USER_FMT & nPoolId )
/*N*/           nMask |= SFXSTYLEBIT_USERDEF;
/*N*/
/*N*/       switch ( COLL_GET_RANGE_BITS & nPoolId )
/*N*/       {
/*N*/       case COLL_TEXT_BITS:     nMask |= SWSTYLEBIT_TEXT;    break;
/*N*/       case COLL_DOC_BITS :     nMask |= SWSTYLEBIT_CHAPTER; break;
/*N*/       case COLL_LISTS_BITS:    nMask |= SWSTYLEBIT_LIST;    break;
/*N*/       case COLL_REGISTER_BITS: nMask |= SWSTYLEBIT_IDX;     break;
/*N*/       case COLL_EXTRA_BITS:    nMask |= SWSTYLEBIT_EXTRA;   break;
/*N*/       case COLL_HTML_BITS:     nMask |= SWSTYLEBIT_HTML;    break;
/*N*/       }
/*N*/
/*N*/       if( pFmt )
/*N*/       {
/*N*/           ASSERT( bPhysical, "Format nicht gefunden" );
/*N*/
/*N*/           nHelpId = pFmt->GetPoolHelpId();
/*N*/           if( pFmt->GetPoolHlpFileId() != UCHAR_MAX )
/*?*/               aHelpFile = *rDoc.GetDocPattern( pFmt->GetPoolHlpFileId() );
/*N*/           else
/*N*/               aHelpFile.Erase();
/*N*/
/*N*/           if( RES_CONDTXTFMTCOLL == pFmt->Which() )
/*N*/               nMask |= SWSTYLEBIT_CONDCOLL;
/*N*/       }
/*N*/
/*N*/       SetMask( nMask );
/*N*/   }
/*N*/   if( bDeleteInfo && bFillOnlyInfo )
/*?*/ { DBG_BF_ASSERT(0, "STRIP"); }//STRIP001  ::lcl_DeleteInfoStyles( nFamily, aDelArr, rDoc );
/*N*/   return bRet;
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung:   Neues Format in der Core anlegen
 --------------------------------------------------------------------*/


/*N*/ void   SwDocStyleSheet::Create()
/*N*/ {
/*N*/   switch(nFamily)
/*N*/   {
/*N*/       case SFX_STYLE_FAMILY_CHAR :
/*N*/           pCharFmt = lcl_FindCharFmt( rDoc, aName );
/*N*/           if( !pCharFmt )
/*N*/               pCharFmt = rDoc.MakeCharFmt(aName,
/*N*/                                           rDoc.GetDfltCharFmt());
/*N*/           pCharFmt->SetAuto( FALSE );
/*N*/           break;
/*N*/
/*N*/       case SFX_STYLE_FAMILY_PARA :
/*N*/           pColl = lcl_FindParaFmt( rDoc, aName );
/*N*/           if( !pColl )
/*N*/           {
/*N*/               SwTxtFmtColl *pPar = (*rDoc.GetTxtFmtColls())[0];
/*N*/               if( nMask & SWSTYLEBIT_CONDCOLL )
/*?*/               {DBG_BF_ASSERT(0, "STRIP");} //STRIP001     pColl = rDoc.MakeCondTxtFmtColl( aName, pPar );
/*N*/               else
/*N*/                   pColl = rDoc.MakeTxtFmtColl( aName, pPar );
/*N*/           }
/*N*/           break;
/*N*/
/*N*/       case SFX_STYLE_FAMILY_FRAME:
/*N*/           pFrmFmt = lcl_FindFrmFmt( rDoc, aName );
/*N*/           if( !pFrmFmt )
/*N*/               pFrmFmt = rDoc.MakeFrmFmt(aName, rDoc.GetDfltFrmFmt());
/*N*/           pFrmFmt->SetAuto( FALSE );
/*N*/           break;
/*N*/
/*N*/       case SFX_STYLE_FAMILY_PAGE :
/*N*/           pDesc = lcl_FindPageDesc( rDoc, aName );
/*N*/           if( !pDesc )
/*N*/           {
/*N*/               USHORT nId = rDoc.MakePageDesc(aName);
/*N*/               pDesc = &rDoc.GetPageDesc(nId);
/*N*/           }
/*N*/           break;
/*N*/
/*N*/       case SFX_STYLE_FAMILY_PSEUDO:
/*?*/           pNumRule = lcl_FindNumRule( rDoc, aName );
/*?*/           if( !pNumRule )
/*?*/           {
/*?*/               //JP 05.02.99: temp Namen erzeugen, damit kein ASSERT kommt
/*?*/               String sTmpNm( aName );
/*?*/               if( !aName.Len() )
/*?*/                   sTmpNm = rDoc.GetUniqueNumRuleName();
/*?*/
/*?*/               SwNumRule* pRule = rDoc.GetNumRuleTbl()[
/*?*/                                       rDoc.MakeNumRule( sTmpNm ) ];
/*?*/               pRule->SetAutoRule( FALSE );
/*?*/               if( !aName.Len() )
/*?*/                   pRule->SetName( aName );
/*?*/               pNumRule = pRule;
/*?*/           }
/*N*/           break;
/*N*/   }
/*N*/   bPhysical = TRUE;
/*N*/   aCoreSet.ClearItem();
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung:   Konkrete Formate rausholen
 --------------------------------------------------------------------*/



/*N*/ SwCharFmt* SwDocStyleSheet::GetCharFmt()
/*N*/ {
/*N*/   if(!bPhysical)
/*N*/       FillStyleSheet( FillPhysical );
/*N*/   return pCharFmt;
/*N*/ }


/*N*/ SwTxtFmtColl* SwDocStyleSheet::GetCollection()
/*N*/ {
/*N*/   if(!bPhysical)
/*N*/       FillStyleSheet( FillPhysical );
/*N*/   return pColl;
/*N*/ }


/*N*/ const SwPageDesc* SwDocStyleSheet::GetPageDesc()
/*N*/ {
/*N*/   if(!bPhysical)
/*N*/       FillStyleSheet( FillPhysical );
/*N*/   return pDesc;
/*N*/ }

/*N*/ const SwNumRule * SwDocStyleSheet::GetNumRule()
/*N*/ {
/*N*/   if(!bPhysical)
/*N*/       FillStyleSheet( FillPhysical );
/*N*/   return pNumRule;
/*N*/ }

/*N*/ void SwDocStyleSheet::SetNumRule(const SwNumRule& rRule)
/*N*/ {
/*N*/   DBG_ASSERT(pNumRule, "Wo ist die NumRule")
/*N*/   rDoc.ChgNumRuleFmts( rRule );
/*N*/ }

// Namen UND Familie aus String re-generieren
// First() und Next() (s.u.) fuegen einen Kennbuchstaben an Pos.1 ein

/*N*/ void SwDocStyleSheet::PresetNameAndFamily(const String& rName)
/*N*/ {
/*N*/   switch( rName.GetChar(0) )
/*N*/   {
/*N*/       case cPARA:     nFamily = SFX_STYLE_FAMILY_PARA; break;
/*N*/       case cFRAME:    nFamily = SFX_STYLE_FAMILY_FRAME; break;
/*N*/       case cPAGE:     nFamily = SFX_STYLE_FAMILY_PAGE; break;
/*N*/       case cNUMRULE:  nFamily = SFX_STYLE_FAMILY_PSEUDO; break;
/*N*/       default:        nFamily = SFX_STYLE_FAMILY_CHAR; break;
/*N*/   }
/*N*/   aName = rName;
/*N*/   aName.Erase( 0, 1 );
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung:   Ist das Format physikalisch schon vorhanden
 --------------------------------------------------------------------*/


/*N*/ void SwDocStyleSheet::SetPhysical(BOOL bPhys)
/*N*/ {
/*N*/   bPhysical = bPhys;
/*N*/
/*N*/   if(!bPhys)
/*N*/   {
/*N*/       pCharFmt = 0;
/*N*/       pColl    = 0;
/*N*/       pFrmFmt  = 0;
/*N*/       pDesc    = 0;
/*N*/   }
/*N*/ }

/*N*/ SwFrmFmt* SwDocStyleSheet::GetFrmFmt()
/*N*/ {
/*N*/   if(!bPhysical)
/*N*/       FillStyleSheet( FillPhysical );
/*N*/   return pFrmFmt;
/*N*/ }


//STRIP001 BOOL  SwDocStyleSheet::IsUsed() const
//STRIP001 {
//STRIP001  if( !bPhysical )
//STRIP001  {
//STRIP001      SwDocStyleSheet* pThis = (SwDocStyleSheet*)this;
//STRIP001      pThis->FillStyleSheet( FillOnlyName );
//STRIP001  }
//STRIP001
//STRIP001  // immer noch nicht ?
//STRIP001  if( !bPhysical )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  const SwModify* pMod;
//STRIP001  switch( nFamily )
//STRIP001  {
//STRIP001  case SFX_STYLE_FAMILY_CHAR : pMod = pCharFmt;   break;
//STRIP001  case SFX_STYLE_FAMILY_PARA : pMod = pColl;      break;
//STRIP001  case SFX_STYLE_FAMILY_FRAME: pMod = pFrmFmt;    break;
//STRIP001  case SFX_STYLE_FAMILY_PAGE : pMod = pDesc;      break;
//STRIP001
//STRIP001  case SFX_STYLE_FAMILY_PSEUDO:
//STRIP001          return pNumRule ? rDoc.IsUsed( *pNumRule ) : FALSE;
//STRIP001
//STRIP001  default:
//STRIP001      ASSERT(!this, "unbekannte Style-Familie");
//STRIP001      return FALSE;
//STRIP001  }
//STRIP001  return rDoc.IsUsed( *pMod );
//STRIP001 }


//STRIP001 ULONG  SwDocStyleSheet::GetHelpId( String& rFile )
//STRIP001 {
//STRIP001 static String sTemplateHelpFile = String::CreateFromAscii("swrhlppi.hlp");
//STRIP001
//STRIP001  USHORT nId, nPoolId;
//STRIP001  unsigned char nFileId = UCHAR_MAX;
//STRIP001
//STRIP001  rFile = sTemplateHelpFile;
//STRIP001
//STRIP001  const SwFmt* pTmpFmt = 0;
//STRIP001  switch( nFamily )
//STRIP001  {
//STRIP001  case SFX_STYLE_FAMILY_CHAR :
//STRIP001      if( !pCharFmt &&
//STRIP001          0 == (pCharFmt = lcl_FindCharFmt( rDoc, aName, 0, FALSE )) )
//STRIP001      {
//STRIP001          nId = SwStyleNameMapper::GetPoolIdFromUIName( aName, GET_POOLID_CHRFMT );
//STRIP001          return USHRT_MAX == nId ? 0 : nId;
//STRIP001      }
//STRIP001      pTmpFmt = pCharFmt;
//STRIP001      break;
//STRIP001
//STRIP001  case SFX_STYLE_FAMILY_PARA:
//STRIP001      if( !pColl &&
//STRIP001          0 == ( pColl = lcl_FindParaFmt( rDoc, aName, 0, FALSE )) )
//STRIP001      {
//STRIP001          nId = SwStyleNameMapper::GetPoolIdFromUIName( aName, GET_POOLID_TXTCOLL );
//STRIP001          return USHRT_MAX == nId ? 0 : nId;
//STRIP001      }
//STRIP001      pTmpFmt = pColl;
//STRIP001      break;
//STRIP001
//STRIP001  case SFX_STYLE_FAMILY_FRAME:
//STRIP001      if( !pFrmFmt &&
//STRIP001          0 == ( pFrmFmt = lcl_FindFrmFmt( rDoc, aName, 0, FALSE ) ) )
//STRIP001      {
//STRIP001          nId = SwStyleNameMapper::GetPoolIdFromUIName( aName, GET_POOLID_FRMFMT );
//STRIP001          return USHRT_MAX == nId ? 0 : nId;
//STRIP001      }
//STRIP001      pTmpFmt = pFrmFmt;
//STRIP001      break;
//STRIP001
//STRIP001  case SFX_STYLE_FAMILY_PAGE:
//STRIP001      if( !pDesc &&
//STRIP001          0 == ( pDesc = lcl_FindPageDesc( rDoc, aName, 0, FALSE ) ) )
//STRIP001      {
//STRIP001          nId = SwStyleNameMapper::GetPoolIdFromUIName( aName, GET_POOLID_PAGEDESC );
//STRIP001          return USHRT_MAX == nId ? 0 : nId;
//STRIP001      }
//STRIP001
//STRIP001      nId = pDesc->GetPoolHelpId();
//STRIP001      nFileId = pDesc->GetPoolHlpFileId();
//STRIP001      nPoolId = pDesc->GetPoolFmtId();
//STRIP001      break;
//STRIP001
//STRIP001  case SFX_STYLE_FAMILY_PSEUDO:
//STRIP001      if( !pNumRule &&
//STRIP001          0 == ( pNumRule = lcl_FindNumRule( rDoc, aName, 0, FALSE ) ) )
//STRIP001      {
//STRIP001          nId = SwStyleNameMapper::GetPoolIdFromUIName( aName, GET_POOLID_NUMRULE );
//STRIP001          return USHRT_MAX == nId ? 0 : nId;
//STRIP001      }
//STRIP001
//STRIP001      nId = pNumRule->GetPoolHelpId();
//STRIP001      nFileId = pNumRule->GetPoolHlpFileId();
//STRIP001      nPoolId = pNumRule->GetPoolFmtId();
//STRIP001      break;
//STRIP001
//STRIP001  default:
//STRIP001      ASSERT(!this, "unbekannte Style-Familie");
//STRIP001      return 0;
//STRIP001  }
//STRIP001
//STRIP001  if( pTmpFmt )
//STRIP001  {
//STRIP001      nId = pTmpFmt->GetPoolHelpId();
//STRIP001      nFileId = pTmpFmt->GetPoolHlpFileId();
//STRIP001      nPoolId = pTmpFmt->GetPoolFmtId();
//STRIP001  }
//STRIP001
//STRIP001  if( UCHAR_MAX != nFileId )
//STRIP001  {
//STRIP001      const String *pTemplate = rDoc.GetDocPattern( nFileId );
//STRIP001      if( pTemplate )
//STRIP001      {
//STRIP001 //           const String aHelpPath(MakeHelpPath(*pTemplate));
//STRIP001          rFile = *pTemplate;
//STRIP001      }
//STRIP001  }
//STRIP001  else if( !IsPoolUserFmt( nPoolId ) )
//STRIP001  {
//STRIP001      nId = nPoolId;
//STRIP001  }
//STRIP001
//STRIP001  // weil sich der SFX so anstellt mit der HilfeId:
//STRIP001  if( USHRT_MAX == nId )
//STRIP001      nId = 0;        // entsp. keine Hilfe anzeigen
//STRIP001
//STRIP001  return nId;
//STRIP001 }


//STRIP001 void  SwDocStyleSheet::SetHelpId( const String& r, ULONG nId )
//STRIP001 {
//STRIP001  BYTE nFileId = rDoc.SetDocPattern( r );
//STRIP001  USHORT nHId = nId;      //!! SFX hat eigenmaechtig auf ULONG umgestellt!
//STRIP001
//STRIP001  SwFmt* pTmpFmt = 0;
//STRIP001  switch( nFamily )
//STRIP001  {
//STRIP001  case SFX_STYLE_FAMILY_CHAR : pTmpFmt = pCharFmt;    break;
//STRIP001  case SFX_STYLE_FAMILY_PARA : pTmpFmt = pColl;       break;
//STRIP001  case SFX_STYLE_FAMILY_FRAME: pTmpFmt = pFrmFmt;     break;
//STRIP001  case SFX_STYLE_FAMILY_PAGE :
//STRIP001      ((SwPageDesc*)pDesc)->SetPoolHelpId( nHId );
//STRIP001      ((SwPageDesc*)pDesc)->SetPoolHlpFileId( nFileId );
//STRIP001      break;
//STRIP001
//STRIP001  case SFX_STYLE_FAMILY_PSEUDO:
//STRIP001      ((SwNumRule*)pNumRule)->SetPoolHelpId( nHId );
//STRIP001      ((SwNumRule*)pNumRule)->SetPoolHlpFileId( nFileId );
//STRIP001      break;
//STRIP001
//STRIP001  default:
//STRIP001      ASSERT(!this, "unbekannte Style-Familie");
//STRIP001      return ;
//STRIP001  }
//STRIP001  if( pTmpFmt )
//STRIP001  {
//STRIP001      pTmpFmt->SetPoolHelpId( nHId );
//STRIP001      pTmpFmt->SetPoolHlpFileId( nFileId );
//STRIP001  }
//STRIP001 }


/*  */

/*--------------------------------------------------------------------
    Beschreibung:   Methoden fuer den DocStyleSheetPool
 --------------------------------------------------------------------*/

/*N*/ SwDocStyleSheetPool::SwDocStyleSheetPool( SwDoc& rDocument, BOOL bOrg )
/*N*/   : SfxStyleSheetBasePool( rDocument.GetAttrPool() ),
/*N*/   aStyleSheet( rDocument, aEmptyStr, *this, SFX_STYLE_FAMILY_CHAR, 0 ),
/*N*/   rDoc( rDocument )
/*N*/ {
/*N*/   bOrganizer = bOrg;
/*N*/ }

/*N*/  SwDocStyleSheetPool::~SwDocStyleSheetPool()
/*N*/ {
/*N*/ }

/*N*/ SfxStyleSheetBase&     SwDocStyleSheetPool::Make(
/*N*/       const String&   rName,
/*N*/       SfxStyleFamily  eFam,
/*N*/       USHORT          nMask,
/*N*/       USHORT          nPos )
/*N*/ {
/*N*/   aStyleSheet.PresetName(rName);
/*N*/   aStyleSheet.PresetParent(aEmptyStr);
/*N*/   aStyleSheet.PresetFollow(aEmptyStr);
/*N*/   aStyleSheet.SetMask(nMask) ;
/*N*/   aStyleSheet.SetFamily(eFam);
/*N*/   aStyleSheet.SetPhysical(TRUE);
/*N*/   aStyleSheet.Create();
/*N*/
/*N*/   return aStyleSheet;
/*N*/ }


//STRIP001 SfxStyleSheetBase*    SwDocStyleSheetPool::Create( const SfxStyleSheetBase& rOrg)
//STRIP001 {
//STRIP001  ASSERT(!this , "Create im SW-Stylesheet-Pool geht nicht" );
//STRIP001  return NULL;
//STRIP001 }


//STRIP001 SfxStyleSheetBase*    SwDocStyleSheetPool::Create( const String &,
//STRIP001                                              SfxStyleFamily, USHORT )
//STRIP001 {
//STRIP001  ASSERT( !this, "Create im SW-Stylesheet-Pool geht nicht" );
//STRIP001  return NULL;
//STRIP001 }

//STRIP001 void  SwDocStyleSheetPool::Replace( SfxStyleSheetBase& rSource,
//STRIP001                                          SfxStyleSheetBase& rTarget )
//STRIP001 {
//STRIP001  SfxStyleFamily eFamily( rSource.GetFamily() );
//STRIP001  if( rSource.HasParentSupport())
//STRIP001  {
//STRIP001      const String& rParentName = rSource.GetParent();
//STRIP001      if( 0 != rParentName.Len() )
//STRIP001      {
//STRIP001          SfxStyleSheetBase* pParentOfNew = Find( rParentName, eFamily );
//STRIP001          if( pParentOfNew )
//STRIP001              rTarget.SetParent( rParentName );
//STRIP001      }
//STRIP001  }
//STRIP001  if( rSource.HasFollowSupport())
//STRIP001  {
//STRIP001      const String& rFollowName = rSource.GetFollow();
//STRIP001      if( 0 != rFollowName.Len() )
//STRIP001      {
//STRIP001          SfxStyleSheetBase* pFollowOfNew = Find( rFollowName, eFamily );
//STRIP001          if( pFollowOfNew )
//STRIP001              rTarget.SetFollow( rFollowName );
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  SwImplShellAction aTmpSh( rDoc );
//STRIP001
//STRIP001  BOOL bSwSrcPool = GetAppName() == rSource.GetPool().GetAppName();
//STRIP001  if( SFX_STYLE_FAMILY_PAGE == eFamily && bSwSrcPool )
//STRIP001  {
//STRIP001      // gesondert behandeln!!
//STRIP001      SwPageDesc* pDestDsc =
//STRIP001          (SwPageDesc*)((SwDocStyleSheet&)rTarget).GetPageDesc();
//STRIP001      SwPageDesc* pCpyDsc =
//STRIP001          (SwPageDesc*)((SwDocStyleSheet&)rSource).GetPageDesc();
//STRIP001      rDoc.CopyPageDesc( *pCpyDsc, *pDestDsc );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      const SwFmt *pSourceFmt = 0;
//STRIP001      SwFmt *pTargetFmt = 0;
//STRIP001      SwPageDesc *pTargetDesc = 0;
//STRIP001      USHORT nPgDscPos = USHRT_MAX;
//STRIP001      switch( eFamily )
//STRIP001      {
//STRIP001      case SFX_STYLE_FAMILY_CHAR :
//STRIP001          if( bSwSrcPool )
//STRIP001              pSourceFmt = ((SwDocStyleSheet&)rSource).GetCharFmt();
//STRIP001          pTargetFmt = ((SwDocStyleSheet&)rTarget).GetCharFmt();
//STRIP001          break;
//STRIP001      case SFX_STYLE_FAMILY_PARA :
//STRIP001          if( bSwSrcPool )
//STRIP001              pSourceFmt = ((SwDocStyleSheet&)rSource).GetCollection();
//STRIP001          pTargetFmt = ((SwDocStyleSheet&)rTarget).GetCollection();
//STRIP001          break;
//STRIP001      case SFX_STYLE_FAMILY_FRAME:
//STRIP001          if( bSwSrcPool )
//STRIP001              pSourceFmt = ((SwDocStyleSheet&)rSource).GetFrmFmt();
//STRIP001          pTargetFmt = ((SwDocStyleSheet&)rTarget).GetFrmFmt();
//STRIP001          break;
//STRIP001      case SFX_STYLE_FAMILY_PAGE:
//STRIP001          if( bSwSrcPool )
//STRIP001              pSourceFmt = &((SwDocStyleSheet&)rSource).GetPageDesc()
//STRIP001                              ->GetMaster();
//STRIP001          {
//STRIP001              SwPageDesc *pDesc = rDoc.FindPageDescByName(
//STRIP001                  ((SwDocStyleSheet&)rTarget).GetPageDesc()->GetName(),
//STRIP001                  &nPgDscPos );
//STRIP001
//STRIP001              if( pDesc )
//STRIP001                  pTargetFmt = &pDesc->GetMaster();
//STRIP001          }
//STRIP001          break;
//STRIP001      case SFX_STYLE_FAMILY_PSEUDO:
//STRIP001          // Eine NumRule besteht nur aus einem Item, also muss man
//STRIP001          // hier nichts loeschen.
//STRIP001          break;
//STRIP001      }
//STRIP001      if( pTargetFmt )
//STRIP001      {
//STRIP001          if( pSourceFmt )
//STRIP001              pTargetFmt->DelDiffs( *pSourceFmt );
//STRIP001          else if( USHRT_MAX != nPgDscPos )
//STRIP001              pTargetFmt->ResetAttr( RES_PAGEDESC, RES_FRMATR_END-1 );
//STRIP001          else
//STRIP001              pTargetFmt->ResetAllAttr();
//STRIP001
//STRIP001          if( USHRT_MAX != nPgDscPos )
//STRIP001              rDoc.ChgPageDesc( nPgDscPos, rDoc.GetPageDesc(nPgDscPos) );
//STRIP001      }
//STRIP001      ((SwDocStyleSheet&)rTarget).SetItemSet( rSource.GetItemSet() );
//STRIP001  }
//STRIP001 }

/*N*/ SfxStyleSheetIterator*  SwDocStyleSheetPool::CreateIterator(
/*N*/                       SfxStyleFamily eFam, USHORT nMask )
/*N*/ {
/*N*/   return new SwStyleSheetIterator( this, eFam, nMask );
/*N*/ }

//STRIP001 void   SwDocStyleSheetPool::Erase( SfxStyleSheetBase* pStyle)
//STRIP001 {
//STRIP001  if( !pStyle )
//STRIP001      return;
//STRIP001
//STRIP001  BOOL bBroadcast = TRUE;
//STRIP001  SwImplShellAction aTmpSh( rDoc );
//STRIP001  const String& rName = pStyle->GetName();
//STRIP001  switch( pStyle->GetFamily() )
//STRIP001  {
//STRIP001  case SFX_STYLE_FAMILY_CHAR:
//STRIP001      {
//STRIP001          SwCharFmt* pFmt = lcl_FindCharFmt(rDoc, rName, 0, FALSE );
//STRIP001          if(pFmt)
//STRIP001              rDoc.DelCharFmt(pFmt);
//STRIP001      }
//STRIP001      break;
//STRIP001  case SFX_STYLE_FAMILY_PARA:
//STRIP001      {
//STRIP001          SwTxtFmtColl* pColl = lcl_FindParaFmt(rDoc, rName, 0, FALSE );
//STRIP001          if(pColl)
//STRIP001              rDoc.DelTxtFmtColl(pColl);
//STRIP001      }
//STRIP001      break;
//STRIP001  case SFX_STYLE_FAMILY_FRAME:
//STRIP001      {
//STRIP001          SwFrmFmt* pFmt = lcl_FindFrmFmt(rDoc, rName, 0, FALSE );
//STRIP001          if(pFmt)
//STRIP001              rDoc.DelFrmFmt(pFmt);
//STRIP001      }
//STRIP001      break;
//STRIP001  case SFX_STYLE_FAMILY_PAGE :
//STRIP001      {
//STRIP001          USHORT nPos;
//STRIP001          if( rDoc.FindPageDescByName( rName, &nPos ))
//STRIP001              rDoc.DelPageDesc( nPos );
//STRIP001      }
//STRIP001      break;
//STRIP001
//STRIP001  case SFX_STYLE_FAMILY_PSEUDO:
//STRIP001      {
//STRIP001          if( !rDoc.DelNumRule( rName ) )
//STRIP001              // Broadcast nur versenden, wenn etwas geloescht wurde
//STRIP001              bBroadcast = FALSE;
//STRIP001      }
//STRIP001      break;
//STRIP001
//STRIP001  default:
//STRIP001      ASSERT(!this, "unbekannte Style-Familie");
//STRIP001      bBroadcast = FALSE;
//STRIP001  }
//STRIP001
//STRIP001  if( bBroadcast )
//STRIP001      Broadcast( SfxStyleSheetHint( SFX_STYLESHEET_ERASED, *pStyle ) );
//STRIP001 }



/*N*/ BOOL  SwDocStyleSheetPool::SetParent( SfxStyleFamily eFam,
/*N*/                               const String &rStyle, const String &rParent )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001
//STRIP001  SwFmt* pFmt = 0, *pParent = 0;
//STRIP001  switch( eFam )
//STRIP001  {
//STRIP001  case SFX_STYLE_FAMILY_CHAR :
//STRIP001      if( 0 != ( pFmt = lcl_FindCharFmt( rDoc, rStyle ) ) && rParent.Len() )
//STRIP001          pParent = lcl_FindCharFmt(rDoc, rParent );
//STRIP001      break;
//STRIP001
//STRIP001  case SFX_STYLE_FAMILY_PARA :
//STRIP001      if( 0 != ( pFmt = lcl_FindParaFmt( rDoc, rStyle ) ) && rParent.Len() )
//STRIP001          pParent = lcl_FindParaFmt( rDoc, rParent );
//STRIP001      break;
//STRIP001
//STRIP001  case SFX_STYLE_FAMILY_FRAME:
//STRIP001      if( 0 != ( pFmt = lcl_FindFrmFmt( rDoc, rStyle ) ) && rParent.Len() )
//STRIP001          pParent = lcl_FindFrmFmt( rDoc, rParent );
//STRIP001      break;
//STRIP001
//STRIP001  case SFX_STYLE_FAMILY_PAGE:
//STRIP001  case SFX_STYLE_FAMILY_PSEUDO:
//STRIP001      break;
//STRIP001
//STRIP001  default:
//STRIP001      ASSERT(!this, "unbekannte Style-Familie");
//STRIP001  }
//STRIP001
//STRIP001  BOOL bRet = FALSE;
//STRIP001  if( pFmt && pFmt->DerivedFrom() &&
//STRIP001      pFmt->DerivedFrom()->GetName() != rParent )
//STRIP001  {
//STRIP001      {
//STRIP001          SwImplShellAction aTmpSh( rDoc );
//STRIP001          bRet = pFmt->SetDerivedFrom( pParent );
//STRIP001      }
//STRIP001
//STRIP001      if( bRet )
//STRIP001      {
//STRIP001          // nur fuer das Broadcasting
//STRIP001          aStyleSheet.PresetName( rStyle );
//STRIP001          aStyleSheet.PresetParent( rParent );
//STRIP001          if( SFX_STYLE_FAMILY_PARA == eFam )
//STRIP001              aStyleSheet.PresetFollow( ((SwTxtFmtColl*)pFmt)->
//STRIP001                      GetNextTxtFmtColl().GetName() );
//STRIP001          else
//STRIP001              aStyleSheet.PresetFollow( aEmptyStr );
//STRIP001
//STRIP001          Broadcast( SfxStyleSheetHint( SFX_STYLESHEET_MODIFIED,
//STRIP001                                          aStyleSheet ) );
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  return bRet;
/*N*/ }

/*N*/ SfxStyleSheetBase* SwDocStyleSheetPool::Find( const String& rName,
/*N*/                                           SfxStyleFamily eFam, USHORT n )
/*N*/ {
/*N*/   USHORT nSMask = n;
/*N*/   if( SFX_STYLE_FAMILY_PARA == eFam && rDoc.IsHTMLMode() )
/*N*/   {
/*?*/       // dann sind nur HTML-Vorlagen von Interesse
/*?*/       if( USHRT_MAX == nSMask )
/*?*/           nSMask = SWSTYLEBIT_HTML | SFXSTYLEBIT_USERDEF | SFXSTYLEBIT_USED;
/*?*/       else
/*?*/           nSMask &= SFXSTYLEBIT_USED | SFXSTYLEBIT_USERDEF |
/*?*/                               SWSTYLEBIT_CONDCOLL | SWSTYLEBIT_HTML;
/*?*/       if( !nSMask )
/*?*/           nSMask = SWSTYLEBIT_HTML;
/*N*/   }

/*N*/   const BOOL bSearchUsed = ( n != SFXSTYLEBIT_ALL &&
/*N*/                            n & SFXSTYLEBIT_USED ) ? TRUE : FALSE;
/*N*/   const SwModify* pMod = 0;
/*N*/
/*N*/   aStyleSheet.SetPhysical( FALSE );
/*N*/   aStyleSheet.PresetName( rName );
/*N*/   aStyleSheet.SetFamily( eFam );
/*N*/   BOOL bFnd = aStyleSheet.FillStyleSheet( SwDocStyleSheet::FillOnlyName );
/*N*/
/*N*/   if( aStyleSheet.IsPhysical() )
/*N*/   {
/*N*/       switch( eFam )
/*N*/       {
/*N*/       case SFX_STYLE_FAMILY_CHAR:
/*N*/           pMod = aStyleSheet.GetCharFmt();
/*N*/           break;
/*N*/
/*N*/       case SFX_STYLE_FAMILY_PARA:
/*N*/           pMod = aStyleSheet.GetCollection();
/*N*/           break;
/*N*/
/*N*/       case SFX_STYLE_FAMILY_FRAME:
/*N*/           pMod = aStyleSheet.GetFrmFmt();
/*N*/           break;
/*N*/
/*N*/       case SFX_STYLE_FAMILY_PAGE:
/*N*/           pMod = aStyleSheet.GetPageDesc();
/*N*/           break;
/*N*/
/*N*/       case SFX_STYLE_FAMILY_PSEUDO:
/*N*/           {
/*N*/               const SwNumRule* pRule = aStyleSheet.GetNumRule();
/*N*/               if( pRule &&
/*N*/                   !(bSearchUsed && (bOrganizer || rDoc.IsUsed(*pRule)) ) &&
/*N*/                   (( nSMask & ~SFXSTYLEBIT_USED) == SFXSTYLEBIT_USERDEF
/*N*/                           ? !(pRule->GetPoolFmtId() & USER_FMT)
/*N*/                               // benutzte gesucht und keine gefunden
/*N*/                           : bSearchUsed ))
/*N*/                   bFnd = FALSE;
/*N*/           }
/*N*/           break;
/*N*/
/*N*/       default:
/*N*/           ASSERT(!this, "unbekannte Style-Familie");
/*N*/       }
/*N*/   }
/*N*/
/*N*/   // dann noch die Maske auswerten:
/*N*/   if( pMod && !(bSearchUsed && (bOrganizer || rDoc.IsUsed(*pMod)) ) )
/*N*/   {
/*N*/       const USHORT nId = SFX_STYLE_FAMILY_PAGE == eFam
/*N*/                       ? ((SwPageDesc*)pMod)->GetPoolFmtId()
/*N*/                       : ((SwFmt*)pMod)->GetPoolFmtId();
/*N*/
/*N*/       if( ( nSMask & ~SFXSTYLEBIT_USED) == SFXSTYLEBIT_USERDEF
/*N*/           ? !(nId & USER_FMT)
/*N*/               // benutzte gesucht und keine gefunden
/*N*/           : bSearchUsed )
/*N*/           bFnd = FALSE;
/*N*/   }
/*N*/   return bFnd ? &aStyleSheet : 0;
/*N*/ }

/*  */

/*N*/ SwStyleSheetIterator::SwStyleSheetIterator( SwDocStyleSheetPool* pBase,
/*N*/                               SfxStyleFamily eFam, USHORT n )
/*N*/   : SfxStyleSheetIterator( pBase, eFam, n ),
/*N*/   aIterSheet( pBase->GetDoc(), aEmptyStr, *pBase, SFX_STYLE_FAMILY_CHAR, 0 ),
/*N*/   aStyleSheet( pBase->GetDoc(), aEmptyStr, *pBase, SFX_STYLE_FAMILY_CHAR, 0 )
/*N*/ {
/*N*/   bFirstCalled = FALSE;
/*N*/   nLastPos = 0;
/*N*/   StartListening( *pBase );
/*N*/ }

/*N*/  SwStyleSheetIterator::~SwStyleSheetIterator()
/*N*/ {
/*N*/   EndListening( aIterSheet.GetPool() );
/*N*/ }

//STRIP001 USHORT  SwStyleSheetIterator::Count()
//STRIP001 {
//STRIP001  // Liste richtig fuellen lassen !!
//STRIP001  if( !bFirstCalled )
//STRIP001      First();
//STRIP001  return aLst.Count();
//STRIP001 }

//STRIP001 SfxStyleSheetBase*  SwStyleSheetIterator::operator[]( USHORT nIdx )
//STRIP001 {
//STRIP001  // gefunden
//STRIP001  if( !bFirstCalled )
//STRIP001      First();
//STRIP001  aStyleSheet.PresetNameAndFamily( *aLst[ nIdx ] );
//STRIP001  aStyleSheet.SetPhysical( FALSE );
//STRIP001  aStyleSheet.FillStyleSheet( SwDocStyleSheet::FillOnlyName );
//STRIP001
//STRIP001  return &aStyleSheet;
//STRIP001 }

/*N*/ SfxStyleSheetBase*  SwStyleSheetIterator::First()
/*N*/ {
/*N*/   // Alte Liste loeschen
/*N*/   bFirstCalled = TRUE;
/*N*/   nLastPos = 0;
/*N*/   aLst.Erase();
/*N*/
/*N*/   // aktuellen loeschen
/*N*/   aIterSheet.Reset();
/*N*/
/*N*/   SwDoc& rDoc = ((SwDocStyleSheetPool*)pBasePool)->GetDoc();
/*N*/   const USHORT nSrchMask = nMask;
/*N*/   const BOOL bSearchUsed = SearchUsed();
/*N*/
/*N*/   const BOOL bOrganizer = ((SwDocStyleSheetPool*)pBasePool)->IsOrganizerMode();
/*N*/
/*N*/   if( nSearchFamily == SFX_STYLE_FAMILY_CHAR
/*N*/    || nSearchFamily == SFX_STYLE_FAMILY_ALL )
/*N*/   {
/*?*/       const USHORT nArrLen = rDoc.GetCharFmts()->Count();
/*?*/       for( USHORT i = 0; i < nArrLen; i++ )
/*?*/       {
/*?*/           SwCharFmt* pFmt = (*rDoc.GetCharFmts())[ i ];
/*?*/           if( pFmt->IsDefault() && pFmt != rDoc.GetDfltCharFmt() )
/*?*/               continue;
/*?*/
/*?*/           const BOOL  bUsed = bSearchUsed && (bOrganizer || rDoc.IsUsed(*pFmt));
/*?*/           if( !bUsed )
/*?*/           {
/*?*/               // Standard ist keine Benutzervorlage #46181#
/*?*/               const USHORT nId = rDoc.GetDfltCharFmt() == pFmt ?
/*?*/                       RES_POOLCHR_INET_NORMAL :
/*?*/                               pFmt->GetPoolFmtId();
/*?*/               if( (nSrchMask & ~SFXSTYLEBIT_USED) == SFXSTYLEBIT_USERDEF
/*?*/                   ? !(nId & USER_FMT)
/*?*/                       // benutzte gesucht und keine gefunden
/*?*/                   : bSearchUsed )
/*?*/               continue;
/*?*/
/*?*/               if( rDoc.IsHTMLMode() && !(nId & USER_FMT) &&
/*?*/                   !( RES_POOLCHR_HTML_BEGIN <= nId &&
/*?*/                         nId < RES_POOLCHR_HTML_END ) &&
/*?*/                   RES_POOLCHR_INET_NORMAL != nId &&
/*?*/                   RES_POOLCHR_INET_VISIT != nId &&
/*?*/                   RES_POOLCHR_FOOTNOTE  != nId &&
/*?*/                   RES_POOLCHR_ENDNOTE != nId )
/*?*/                   continue;
/*?*/           }
/*?*/
/*?*/           aLst.Append( cCHAR, pFmt == rDoc.GetDfltCharFmt()
/*?*/                       ? (const String&) *SwStyleNameMapper::GetTextUINameArray()[ RES_POOLCOLL_STANDARD -
/*?*/                                               RES_POOLCOLL_TEXT_BEGIN ]
/*?*/                       : pFmt->GetName() );
/*?*/       }
/*?*/
/*?*/       // PoolFormate
/*?*/       //
/*?*/       if( nSrchMask == SFXSTYLEBIT_ALL )
/*?*/       {
/*?*/           if( !rDoc.IsHTMLMode() )
/*?*/               AppendStyleList(SwStyleNameMapper::GetChrFmtUINameArray(),
/*?*/                               bSearchUsed, GET_POOLID_CHRFMT, cCHAR);
/*?*/           else
/*?*/           {
/*?*/               aLst.Append( cCHAR, *SwStyleNameMapper::GetChrFmtUINameArray()[
/*?*/                       RES_POOLCHR_INET_NORMAL - RES_POOLCHR_BEGIN ] );
/*?*/               aLst.Append( cCHAR, *SwStyleNameMapper::GetChrFmtUINameArray()[
/*?*/                       RES_POOLCHR_INET_VISIT - RES_POOLCHR_BEGIN ] );
/*?*/               aLst.Append( cCHAR, *SwStyleNameMapper::GetChrFmtUINameArray()[
/*?*/                       RES_POOLCHR_ENDNOTE - RES_POOLCHR_BEGIN ] );
/*?*/               aLst.Append( cCHAR, *SwStyleNameMapper::GetChrFmtUINameArray()[
/*?*/                       RES_POOLCHR_FOOTNOTE - RES_POOLCHR_BEGIN ] );
/*?*/           }
/*?*/           AppendStyleList(SwStyleNameMapper::GetHTMLChrFmtUINameArray(),
/*?*/                               bSearchUsed, GET_POOLID_CHRFMT, cCHAR);
/*N*/       }
/*N*/   }

/*N*/   if( nSearchFamily == SFX_STYLE_FAMILY_PARA ||
/*N*/       nSearchFamily == SFX_STYLE_FAMILY_ALL )
/*N*/   {
/*N*/       USHORT nSMask = nSrchMask;
/*N*/       if( rDoc.IsHTMLMode() )
/*N*/       {
/*?*/           // dann sind nur HTML-Vorlagen von Interesse
/*?*/           if( USHRT_MAX == nSMask )
/*?*/               nSMask = SWSTYLEBIT_HTML | SFXSTYLEBIT_USERDEF |
/*?*/                           SFXSTYLEBIT_USED;
/*?*/           else
/*?*/               nSMask &= SFXSTYLEBIT_USED | SFXSTYLEBIT_USERDEF |
/*?*/                               SWSTYLEBIT_CONDCOLL | SWSTYLEBIT_HTML;
/*?*/           if( !nSMask )
/*?*/               nSMask = SWSTYLEBIT_HTML;
/*N*/       }
/*N*/
/*N*/       const USHORT nArrLen = rDoc.GetTxtFmtColls()->Count();
/*N*/       for( USHORT i = 0; i < nArrLen; i++ )
/*N*/       {
/*N*/           SwTxtFmtColl* pColl = (*rDoc.GetTxtFmtColls())[ i ];
/*N*/
/*N*/           if(pColl->IsDefault())
/*N*/               continue;
/*N*/
/*N*/           const BOOL bUsed = bOrganizer || rDoc.IsUsed(*pColl);
/*N*/           if( !(bSearchUsed && bUsed ))
/*N*/           {
/*N*/               const USHORT nId = pColl->GetPoolFmtId();
/*N*/               switch ( (nSMask & ~SFXSTYLEBIT_USED) )
/*N*/               {
/*N*/               case SFXSTYLEBIT_USERDEF:
/*N*/                   if(!IsPoolUserFmt(nId)) continue;
/*N*/                   break;
/*N*/               case SWSTYLEBIT_TEXT:
/*?*/                   if((nId & COLL_GET_RANGE_BITS) != COLL_TEXT_BITS) continue;
/*?*/                   break;
/*N*/               case SWSTYLEBIT_CHAPTER:
/*?*/                   if((nId  & COLL_GET_RANGE_BITS) != COLL_DOC_BITS) continue;
/*?*/                   break;
/*N*/               case SWSTYLEBIT_LIST:
/*?*/                   if((nId  & COLL_GET_RANGE_BITS) != COLL_LISTS_BITS) continue;
/*?*/                   break;
/*N*/               case SWSTYLEBIT_IDX:
/*N*/                   if((nId  & COLL_GET_RANGE_BITS) != COLL_REGISTER_BITS) continue;
/*N*/                   break;
/*N*/               case SWSTYLEBIT_EXTRA:
/*N*/                   if((nId  & COLL_GET_RANGE_BITS) != COLL_EXTRA_BITS) continue;
/*N*/                   break;
/*N*/
/*N*/               case SWSTYLEBIT_HTML | SFXSTYLEBIT_USERDEF:
/*?*/                   if(IsPoolUserFmt(nId))
/*?*/                       break;
/*N*/                   // ansonten weiter
/*N*/               case SWSTYLEBIT_HTML:
/*?*/                   if( (nId  & COLL_GET_RANGE_BITS) != COLL_HTML_BITS)
/*?*/                   {
/*?*/                       // einige wollen wir aber auch in dieser Section sehen
/*?*/                       BOOL bWeiter = TRUE;
/*?*/                       switch( nId )
/*?*/                       {
/*?*/                       case RES_POOLCOLL_SENDADRESS:   //  --> ADDRESS
/*?*/                       case RES_POOLCOLL_TABLE_HDLN:   //  --> TH
/*?*/                       case RES_POOLCOLL_TABLE:        //  --> TD
/*?*/                       case RES_POOLCOLL_TEXT:         //  --> P
/*?*/                       case RES_POOLCOLL_HEADLINE_BASE://  --> H
/*?*/                       case RES_POOLCOLL_HEADLINE1:    //  --> H1
/*?*/                       case RES_POOLCOLL_HEADLINE2:    //  --> H2
/*?*/                       case RES_POOLCOLL_HEADLINE3:    //  --> H3
/*?*/                       case RES_POOLCOLL_HEADLINE4:    //  --> H4
/*?*/                       case RES_POOLCOLL_HEADLINE5:    //  --> H5
/*?*/                       case RES_POOLCOLL_HEADLINE6:    //  --> H6
/*?*/                       case RES_POOLCOLL_STANDARD:     //  --> P
/*?*/                       case RES_POOLCOLL_FOOTNOTE:
/*?*/                       case RES_POOLCOLL_ENDNOTE:
/*?*/                           bWeiter = FALSE;
/*?*/                           break;
/*?*/                       }
/*?*/                       if( bWeiter )
/*?*/                           continue;
/*?*/                   }
/*?*/                   break;
/*?*/               case SWSTYLEBIT_CONDCOLL:
/*?*/                   if( RES_CONDTXTFMTCOLL != pColl->Which() ) continue;
/*?*/                   break;
/*N*/               default:
/*N*/                   // benutzte gesucht und keine gefunden
/*N*/                   if( bSearchUsed )
/*N*/                       continue;
/*N*/               }
/*N*/           }
/*N*/           aLst.Append( cPARA, pColl->GetName() );
/*N*/       }
/*N*/
/*N*/       const BOOL bAll = nSMask == SFXSTYLEBIT_ALL;
/*N*/       if ( bAll || (nSMask & ~SFXSTYLEBIT_USED) == SWSTYLEBIT_TEXT )
/*N*/           AppendStyleList(SwStyleNameMapper::GetTextUINameArray(),
/*N*/                           bSearchUsed, GET_POOLID_TXTCOLL, cPARA );
/*N*/       if ( bAll || (nSMask & ~SFXSTYLEBIT_USED) == SWSTYLEBIT_CHAPTER )
/*N*/           AppendStyleList(SwStyleNameMapper::GetDocUINameArray(),
/*N*/                           bSearchUsed, GET_POOLID_TXTCOLL, cPARA ) ;
/*N*/       if ( bAll || (nSMask & ~SFXSTYLEBIT_USED) == SWSTYLEBIT_LIST )
/*N*/           AppendStyleList(SwStyleNameMapper::GetListsUINameArray(),
/*N*/                           bSearchUsed, GET_POOLID_TXTCOLL, cPARA ) ;
/*N*/       if ( bAll || (nSMask & ~SFXSTYLEBIT_USED) == SWSTYLEBIT_IDX )
/*N*/           AppendStyleList(SwStyleNameMapper::GetRegisterUINameArray(),
/*N*/                           bSearchUsed, GET_POOLID_TXTCOLL, cPARA ) ;
/*N*/       if ( bAll || (nSMask & ~SFXSTYLEBIT_USED) == SWSTYLEBIT_EXTRA )
/*N*/           AppendStyleList(SwStyleNameMapper::GetExtraUINameArray(),
/*N*/                           bSearchUsed, GET_POOLID_TXTCOLL, cPARA ) ;
/*N*/       if ( bAll || (nSMask & ~SFXSTYLEBIT_USED) == SWSTYLEBIT_CONDCOLL )
/*N*/       {
/*?*/           DBG_BF_ASSERT(0, "STRIP"); //STRIP001 if( !bSearchUsed ||
//STRIP001 /*?*/                rDoc.IsPoolTxtCollUsed( RES_POOLCOLL_TEXT ))
//STRIP001 /*?*/                aLst.Append( cPARA, *SwStyleNameMapper::GetTextUINameArray()[
//STRIP001 /*?*/                        RES_POOLCOLL_TEXT - RES_POOLCOLL_TEXT_BEGIN ] );
/*N*/       }
/*N*/       if ( bAll ||
/*N*/           (nSMask & ~SFXSTYLEBIT_USED) == SWSTYLEBIT_HTML ||
/*N*/           (nSMask & ~SFXSTYLEBIT_USED) ==
/*N*/                       (SWSTYLEBIT_HTML | SFXSTYLEBIT_USERDEF) )
/*N*/       {
/*?*/           DBG_BF_ASSERT(0, "STRIP"); //STRIP001 AppendStyleList(SwStyleNameMapper::GetHTMLUINameArray(),
//STRIP001 /*?*/                            bSearchUsed, GET_POOLID_TXTCOLL, cPARA ) ;
//STRIP001 /*?*/            if( !bAll )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                // dann auch die, die wir mappen:
//STRIP001 /*?*/                static USHORT aPoolIds[] = {
//STRIP001 /*?*/                    RES_POOLCOLL_SENDADRESS,    //  --> ADDRESS
//STRIP001 /*?*/                    RES_POOLCOLL_TABLE_HDLN,    //  --> TH
//STRIP001 /*?*/                    RES_POOLCOLL_TABLE,     //  --> TD
//STRIP001 /*?*/                    RES_POOLCOLL_STANDARD,      //  --> P
//STRIP001 /*?*/                    RES_POOLCOLL_TEXT,          //  --> P
//STRIP001 /*?*/                    RES_POOLCOLL_HEADLINE_BASE, //  --> H
//STRIP001 /*?*/                    RES_POOLCOLL_HEADLINE1, //  --> H1
//STRIP001 /*?*/                    RES_POOLCOLL_HEADLINE2, //  --> H2
//STRIP001 /*?*/                    RES_POOLCOLL_HEADLINE3, //  --> H3
//STRIP001 /*?*/                    RES_POOLCOLL_HEADLINE4, //  --> H4
//STRIP001 /*?*/                    RES_POOLCOLL_HEADLINE5, //  --> H5
//STRIP001 /*?*/                    RES_POOLCOLL_HEADLINE6, //  --> H6
//STRIP001 /*?*/                    RES_POOLCOLL_FOOTNOTE,
//STRIP001 /*?*/                    RES_POOLCOLL_ENDNOTE,
//STRIP001 /*?*/                    0
//STRIP001 /*?*/                    };
//STRIP001 /*?*/
//STRIP001 /*?*/                USHORT* pPoolIds = aPoolIds;
//STRIP001 /*?*/                String s;
//STRIP001 /*?*/                while( *pPoolIds )
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    if( !bSearchUsed || rDoc.IsPoolTxtCollUsed( *pPoolIds ) )
//STRIP001 /*?*/                        aLst.Append( cPARA,
//STRIP001 /*?*/                            s = SwStyleNameMapper::GetUIName( *pPoolIds, s ));
//STRIP001 /*?*/                    ++pPoolIds;
//STRIP001 /*?*/                }
//STRIP001 /*?*/            }
/*N*/       }
/*N*/   }
/*N*/
/*N*/   if( nSearchFamily == SFX_STYLE_FAMILY_FRAME ||
/*N*/       nSearchFamily == SFX_STYLE_FAMILY_ALL )
/*?*/   {
/*?*/       const USHORT nArrLen = rDoc.GetFrmFmts()->Count();
/*?*/       for( USHORT i = 0; i < nArrLen; i++ )
/*?*/       {
/*?*/           SwFrmFmt* pFmt = (*rDoc.GetFrmFmts())[ i ];
/*?*/           if(pFmt->IsDefault() || pFmt->IsAuto())
/*?*/               continue;
/*?*/
/*?*/           const USHORT nId = pFmt->GetPoolFmtId();
/*?*/           BOOL bUsed = bSearchUsed && ( bOrganizer || rDoc.IsUsed(*pFmt));
/*?*/           if( !bUsed )
/*?*/           {
/*?*/               if( (nSrchMask & ~SFXSTYLEBIT_USED) == SFXSTYLEBIT_USERDEF
/*?*/                   ? !(nId & USER_FMT)
/*?*/                   // benutzte gesucht und keine gefunden
/*?*/                   : bSearchUsed )
/*?*/                   continue;
/*?*/           }
/*?*/
/*?*/           aLst.Append( cFRAME, pFmt->GetName() );
/*?*/       }
/*?*/
/*?*/       // PoolFormate
/*?*/       //
/*?*/       if ( nSrchMask == SFXSTYLEBIT_ALL )
/*?*/           AppendStyleList(SwStyleNameMapper::GetFrmFmtUINameArray(),
/*?*/                                   bSearchUsed, GET_POOLID_FRMFMT, cFRAME);
/*N*/   }
/*N*/
/*N*/   if( nSearchFamily == SFX_STYLE_FAMILY_PAGE ||
/*N*/       nSearchFamily == SFX_STYLE_FAMILY_ALL )
/*N*/   {
/*N*/       const USHORT nCount = rDoc.GetPageDescCnt();
/*N*/       for(USHORT i = 0; i < nCount; ++i)
/*N*/       {
/*N*/           const SwPageDesc& rDesc = rDoc.GetPageDesc(i);
/*N*/           const USHORT nId = rDesc.GetPoolFmtId();
/*N*/           BOOL bUsed = bSearchUsed && ( bOrganizer || rDoc.IsUsed(rDesc));
/*N*/           if( !bUsed )
/*N*/           {
/*N*/               if( (nSrchMask & ~SFXSTYLEBIT_USED) == SFXSTYLEBIT_USERDEF
/*N*/                   ? !(nId & USER_FMT)
/*N*/                   // benutzte gesucht und keine gefunden
/*N*/                   : bSearchUsed )
/*?*/                   continue;
/*N*/           }
/*N*/
/*N*/           aLst.Append( cPAGE, rDesc.GetName() );
/*N*/       }
/*N*/       if ( nSrchMask == SFXSTYLEBIT_ALL )
/*N*/           AppendStyleList(SwStyleNameMapper::GetPageDescUINameArray(),
/*N*/                           bSearchUsed, GET_POOLID_PAGEDESC, cPAGE);
/*N*/   }
/*N*/
/*N*/   if( nSearchFamily == SFX_STYLE_FAMILY_PSEUDO ||
/*N*/       nSearchFamily == SFX_STYLE_FAMILY_ALL )
/*N*/   {
/*?*/       const SwNumRuleTbl& rNumTbl = rDoc.GetNumRuleTbl();
/*?*/       for(USHORT i = 0; i < rNumTbl.Count(); ++i)
/*?*/       {
/*?*/           const SwNumRule& rRule = *rNumTbl[ i ];
/*?*/           if( !rRule.IsAutoRule() )
/*?*/           {
/*?*/               BOOL bUsed = bSearchUsed && ( bOrganizer || rDoc.IsUsed(rRule) );
/*?*/               if( !bUsed )
/*?*/               {
/*?*/                   if( (nSrchMask & ~SFXSTYLEBIT_USED) == SFXSTYLEBIT_USERDEF
/*?*/                       ? !(rRule.GetPoolFmtId() & USER_FMT)
/*?*/                       // benutzte gesucht und keine gefunden
/*?*/                       : bSearchUsed )
/*?*/                       continue;
/*?*/               }
/*?*/
/*?*/               aLst.Append( cNUMRULE, rRule.GetName() );
/*?*/           }
/*?*/       }
/*?*/       if ( nSrchMask == SFXSTYLEBIT_ALL )
/*?*/           AppendStyleList(SwStyleNameMapper::GetNumRuleUINameArray(),
/*?*/                           bSearchUsed, GET_POOLID_NUMRULE, cNUMRULE);
/*N*/   }
/*N*/
/*N*/   if(aLst.Count() > 0)
/*N*/   {
/*N*/       nLastPos = USHRT_MAX;
/*N*/       return Next();
/*N*/   }
/*N*/   return 0;
/*N*/ }

/*N*/ SfxStyleSheetBase*  SwStyleSheetIterator::Next()
/*N*/ {
/*N*/   nLastPos++;
/*N*/   if(aLst.Count() > 0 && nLastPos < aLst.Count())
/*N*/   {
/*N*/       aIterSheet.PresetNameAndFamily(*aLst[nLastPos]);
/*N*/       aIterSheet.SetPhysical( FALSE );
/*N*/       aIterSheet.SetMask( nMask );
/*N*/       if(aIterSheet.pSet)
/*N*/       {
/*?*/           aIterSheet.pSet->ClearItem(0);
/*?*/           aIterSheet.pSet= 0;
/*N*/       }
/*N*/       return &aIterSheet;
/*N*/   }
/*N*/   return 0;
/*N*/ }

//STRIP001 SfxStyleSheetBase*  SwStyleSheetIterator::Find( const UniString& rName )
//STRIP001 {
//STRIP001  // suchen
//STRIP001  if( !bFirstCalled )
//STRIP001      First();
//STRIP001
//STRIP001  nLastPos = lcl_FindName( aLst, nSearchFamily, rName );
//STRIP001  if( USHRT_MAX != nLastPos )
//STRIP001  {
//STRIP001      // gefunden
//STRIP001      aStyleSheet.PresetNameAndFamily(*aLst[nLastPos]);
//STRIP001      // neuer Name gesetzt, also bestimme seine Daten
//STRIP001      aStyleSheet.FillStyleSheet( SwDocStyleSheet::FillOnlyName );
//STRIP001      if( !aStyleSheet.IsPhysical() )
//STRIP001          aStyleSheet.SetPhysical( FALSE );
//STRIP001
//STRIP001      return &aStyleSheet;
//STRIP001  }
//STRIP001  return 0;
//STRIP001 }

/*N*/ void SwStyleSheetIterator::AppendStyleList(const SvStringsDtor& rList,
/*N*/                                           BOOL    bTestUsed,
/*N*/                                           USHORT nSection, char cType )
/*N*/ {
/*N*/   if( bTestUsed )
/*N*/   {
/*?*/       DBG_BF_ASSERT(0, "STRIP"); //STRIP001 SwDoc& rDoc = ((SwDocStyleSheetPool*)pBasePool)->GetDoc();
//STRIP001 /*?*/        for ( USHORT i=0; i < rList.Count(); ++i )
//STRIP001 /*?*/        {
//STRIP001 /*?*/            BOOL bUsed = FALSE;
//STRIP001 /*?*/            USHORT nId = SwStyleNameMapper::GetPoolIdFromUIName(*rList[i], (SwGetPoolIdFromName)nSection);
//STRIP001 /*?*/            switch ( nSection )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                case GET_POOLID_TXTCOLL:
//STRIP001 /*?*/                        bUsed = rDoc.IsPoolTxtCollUsed( nId );
//STRIP001 /*?*/                        break;
//STRIP001 /*?*/                case GET_POOLID_CHRFMT:
//STRIP001 /*?*/                        bUsed = rDoc.IsPoolFmtUsed( nId );
//STRIP001 /*?*/                        break;
//STRIP001 /*?*/                case GET_POOLID_FRMFMT:
//STRIP001 /*?*/                        bUsed = rDoc.IsPoolFmtUsed( nId );
//STRIP001 /*?*/                case GET_POOLID_PAGEDESC:
//STRIP001 /*?*/                        bUsed = rDoc.IsPoolPageDescUsed( nId );
//STRIP001 /*?*/                        break;
//STRIP001 /*?*/                default:
//STRIP001 /*?*/                    ASSERT( !this, "unknown PoolFmt-Id" );
//STRIP001 /*?*/            }
//STRIP001 /*?*/            if ( bUsed )
//STRIP001 /*?*/                aLst.Append( cType, *rList[i] );
//STRIP001 /*?*/        }
/*N*/   }
/*N*/   else
/*N*/       for ( USHORT i=0; i < rList.Count(); ++i )
/*N*/           aLst.Append( cType, *rList[i] );
/*N*/ }

/*N*/ void  SwStyleSheetIterator::Notify( SfxBroadcaster&, const SfxHint& rHint )
/*N*/ {
/*N*/   // suchen und aus der Anzeige-Liste entfernen !!
/*N*/   if( rHint.ISA( SfxStyleSheetHint ) &&
/*N*/       SFX_STYLESHEET_ERASED == ((SfxStyleSheetHint&) rHint).GetHint() )
/*N*/   {
/*?*/       DBG_BF_ASSERT(0, "STRIP"); //STRIP001 SfxStyleSheetBase* pStyle = ((SfxStyleSheetHint&)rHint).GetStyleSheet();
//STRIP001 /*?*/
//STRIP001 /*?*/        USHORT nTmpPos = lcl_FindName( aLst, pStyle->GetFamily(),
//STRIP001 /*?*/                                        pStyle->GetName() );
//STRIP001 /*?*/        if( nTmpPos < aLst.Count() )
//STRIP001 /*?*/            aLst.DeleteAndDestroy( nTmpPos );
/*N*/   }
/*N*/ }


}
