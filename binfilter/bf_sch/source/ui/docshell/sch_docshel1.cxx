/*************************************************************************
 *
 *  $RCSfile: sch_docshel1.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 12:55:08 $
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

#ifndef _SVX_SVXIDS_HRC
#define ITEMID_FONTLIST         SID_ATTR_CHAR_FONTLIST
#define ITEMID_NUMBERINFO       SID_ATTR_NUMBERFORMAT_INFO
#define ITEMID_COLOR_TABLE      SID_COLOR_TABLE
#define ITEMID_GRADIENT_LIST    SID_GRADIENT_LIST
#define ITEMID_HATCH_LIST       SID_HATCH_LIST
#define ITEMID_BITMAP_LIST      SID_BITMAP_LIST
#define ITEMID_DASH_LIST        SID_DASH_LIST
#define ITEMID_LINEEND_LIST     SID_LINEEND_LIST
#include <bf_svx/svxids.hrc>
#endif

// auto strip #ifndef _REF_HXX
// auto strip #include <tools/ref.hxx>
// auto strip #endif

// auto strip #ifndef _CTRLTOOL_HXX
// auto strip #include <svtools/ctrltool.hxx>
// auto strip #endif
// auto strip #include <bf_svx/flstitem.hxx>
#ifndef _SFXDISPATCH_HXX
#include <bf_sfx2/dispatch.hxx>
#endif
// auto strip #ifndef _SFXVIEWFRM_HXX
// auto strip #include <bf_sfx2/viewfrm.hxx>
// auto strip #endif

#include "app.hrc"
#include "strings.hrc"
#include "res_bmp.hrc"
// auto strip #include "memchrt.hxx"
// auto strip #include "schview.hxx"
#include "docshell.hxx"
// auto strip #include "stlpool.hxx"
// auto strip #ifndef _CHTMODEL_HXX
// auto strip #include "chtmodel.hxx"
// auto strip #endif
// auto strip #include "schresid.hxx"

#include "viewshel.hxx"
namespace binfilter {

/*************************************************************************
|*
|*  Zeichnen der DocShell (mittels der Hilfsklasse SchViewSpecial)
|*
\************************************************************************/

//STRIP001 class SchViewSpecial : public SchView
//STRIP001 {
//STRIP001  BOOL bDontRecurse;
//STRIP001
//STRIP001  public:
//STRIP001  SchViewSpecial(SchChartDocShell* pDocSh, OutputDevice* pOutDev,
//STRIP001                 SchViewShell* pShell) :
//STRIP001      SchView(pDocSh, pOutDev, pShell),
//STRIP001      bDontRecurse (FALSE)
//STRIP001  {
//STRIP001  }
//STRIP001
//STRIP001  virtual ~SchViewSpecial() {};
//STRIP001
//STRIP001  // Wenn die View kein Invalidate() an den Fenstern durchfuehren soll, muss
//STRIP001  // man diese beiden folgenden Methoden ueberladen und entsprechend anders
//STRIP001  // reagieren.
//STRIP001  virtual void InvalidateOneWin(Window& rWin);
//STRIP001
//STRIP001  virtual void InvalidateOneWin(Window& rWin, const Rectangle& rRect);
//STRIP001
//STRIP001  BOOL &DontRecurse ()
//STRIP001  {
//STRIP001      return bDontRecurse;
//STRIP001  }
//STRIP001 };

//STRIP001 void SchViewSpecial::InvalidateOneWin(Window& rWin)
//STRIP001 {
//STRIP001  Region aRegion;
//STRIP001  InitRedraw(&rWin, aRegion);
//STRIP001 }

//STRIP001 void SchViewSpecial::InvalidateOneWin(Window& rWin, const Rectangle& rRect)
//STRIP001 {
//STRIP001  if (!bDontRecurse)
//STRIP001  {
//STRIP001      bDontRecurse = TRUE;
//STRIP001      InitRedraw(&rWin, rRect);
//STRIP001  }
//STRIP001 }

/*************************************************************************
|*
|*
|*
\************************************************************************/

//STRIP001 void SchChartDocShell::Draw( OutputDevice* pOut, const JobSetup& rSetup,
//STRIP001                           USHORT nAspect) throw()
//STRIP001 {
//STRIP001  CHART_TRACE( "SchChartDocShell::Draw" );
//STRIP001
//STRIP001  OutDevType eOutDevType = pOut->GetOutDevType();
//STRIP001
//STRIP001     OutDevViewType eViewType =  pOut->GetOutDevViewType();
//STRIP001     BOOL bForceAutoColor = SvtAccessibilityOptions().GetIsAutomaticFontColor();
//STRIP001     BOOL bEnableAutoColor = TRUE;
//STRIP001     //#106611# don't use automatic colors in WYSIWYG Print Previews
//STRIP001     if(eViewType==OUTDEV_VIEWTYPE_PRINTPREVIEW
//STRIP001         && !SvtAccessibilityOptions().GetIsForPagePreviews())
//STRIP001     {
//STRIP001         bForceAutoColor = FALSE;
//STRIP001         bEnableAutoColor = FALSE;
//STRIP001     }
//STRIP001
//STRIP001     pChDoc->GetOutliner()->EnableAutoColor(bEnableAutoColor);
//STRIP001     pChDoc->GetDrawOutliner().EnableAutoColor(bEnableAutoColor);
//STRIP001
//STRIP001     pChDoc->GetOutliner()->ForceAutoColor(bForceAutoColor);
//STRIP001     pChDoc->GetDrawOutliner().ForceAutoColor(bForceAutoColor);
//STRIP001
//STRIP001  Rectangle aVisArea = GetVisArea(ASPECT_CONTENT);
//STRIP001
//STRIP001  if (!pChDoc->IsInitialized())
//STRIP001  {
//STRIP001      CHART_TRACE( "SchChartDocShell::Draw - Initializing" );
//STRIP001      SetVisArea(aVisArea);   // Groesse der Seite auf VisArea setzen
//STRIP001      pChDoc->Initialize();
//STRIP001  }
//STRIP001
//STRIP001  pOut->IntersectClipRegion(aVisArea);
//STRIP001
//STRIP001  SchViewSpecial* pChView = new SchViewSpecial(this, pOut, NULL);
//STRIP001
//STRIP001  pChView->SetPageVisible (FALSE);
//STRIP001 //    pChView->DontRecurse () = TRUE;
//STRIP001  pChView->ShowPagePgNum(0, aVisArea.TopLeft());
//STRIP001  pChView->DontRecurse () = FALSE;
//STRIP001
//STRIP001  if (eOutDevType != OUTDEV_WINDOW)
//STRIP001  {
//STRIP001      MapMode aOldMapMode = pOut->GetMapMode();
//STRIP001
//STRIP001      if (eOutDevType == OUTDEV_PRINTER)
//STRIP001      {
//STRIP001          MapMode aMapMode = aOldMapMode;
//STRIP001          Point aOrigin = aMapMode.GetOrigin();
//STRIP001          aOrigin.X() += 1;
//STRIP001          aOrigin.Y() += 1;
//STRIP001          aMapMode.SetOrigin(aOrigin);
//STRIP001          pOut->SetMapMode(aMapMode);
//STRIP001      }
//STRIP001
//STRIP001      Region aRegion (aVisArea);
//STRIP001      pChView->InitRedraw(pOut, aRegion);
//STRIP001
//STRIP001      if (eOutDevType == OUTDEV_PRINTER)
//STRIP001          pOut->SetMapMode(aOldMapMode);
//STRIP001  }
//STRIP001
//STRIP001  delete pChView;
//STRIP001 }

/*************************************************************************
|*
|*  Bitmap der StyleFamily zurueckgeben (zunaechst Dummy)
|*
\************************************************************************/

/*N*/ SfxStyleSheetBasePool* SchChartDocShell::GetStyleSheetPool() throw()
/*N*/ {
/*N*/   return (SfxStyleSheetBasePool*)pChDoc->GetStyleSheetPool();
/*N*/ }

/*************************************************************************
|*
|*  Vorlage einfuegen (zunaechst nur Dummy)
|*
\************************************************************************/

//STRIP001 BOOL SchChartDocShell::Insert( SfxObjectShell &rSource, USHORT nSourceIdx1,
//STRIP001                             USHORT nSourceIdx2, USHORT nSourceIdx3,
//STRIP001                             USHORT &nIdx1, USHORT &nIdx2, USHORT &nIdx3,
//STRIP001                             USHORT &nDeleted )  throw()
//STRIP001 {
//STRIP001  CHART_TRACE( "SchChartDocShell::Insert" );
//STRIP001
//STRIP001  BOOL bRet = FALSE;
//STRIP001
//STRIP001  if (INDEX_IGNORE == nIdx1 && CONTENT_STYLE == nSourceIdx1)
//STRIP001      nIdx1 = CONTENT_STYLE;
//STRIP001
//STRIP001  if (CONTENT_STYLE == nSourceIdx1 && CONTENT_STYLE == nIdx1)
//STRIP001  {
//STRIP001      SfxStyleSheetBasePool* pHisPool  = rSource.GetStyleSheetPool();
//STRIP001      SfxStyleSheetBasePool* pMyPool   = GetStyleSheetPool();
//STRIP001      SfxStyleSheetBase*     pHisSheet = (*pHisPool)[nSourceIdx2];
//STRIP001
//STRIP001      if (nIdx2 == INDEX_IGNORE)
//STRIP001          nIdx2 = pMyPool->Count();
//STRIP001
//STRIP001      // wenn so eine Vorlage schon existiert: loeschen!
//STRIP001      String          aOldName(pHisSheet->GetName());
//STRIP001      SfxStyleFamily  eOldFamily = pHisSheet->GetFamily();
//STRIP001
//STRIP001      SfxStyleSheetBase* pExist = pMyPool->Find(aOldName, eOldFamily);
//STRIP001      // USHORT nOldHelpId = pExist->GetHelpId(??? VB ueberlegt sich was);
//STRIP001      if (pExist)
//STRIP001      {
//STRIP001          // gleich wird's geloescht; vorher noch den Index feststellen
//STRIP001          SfxStyleSheetBase* pScan = pMyPool->First();
//STRIP001          USHORT nCount = 0;
//STRIP001          while(pScan)
//STRIP001          {
//STRIP001              if (pScan == pExist)
//STRIP001              {
//STRIP001                  nDeleted = nCount;
//STRIP001                  break;
//STRIP001              }
//STRIP001              nCount++;
//STRIP001              pScan = pMyPool->Next();
//STRIP001          }
//STRIP001
//STRIP001          pMyPool->Erase(pExist);
//STRIP001          pExist = NULL;
//STRIP001      }
//STRIP001
//STRIP001      SfxStyleSheetBase& rNewSheet = pMyPool->Make(aOldName, eOldFamily,
//STRIP001                                              pHisSheet->GetMask(), nIdx2);
//STRIP001
//STRIP001      // ItemSet der neuen Vorlage fuellen
//STRIP001      rNewSheet.GetItemSet().Put(pHisSheet->GetItemSet());
//STRIP001
//STRIP001      // wer bekommt den Neuen als Parent? wer benutzt den Neuen als Follow?
//STRIP001      SfxStyleSheetBase* pTestSheet = pMyPool->First();
//STRIP001      while (pTestSheet)
//STRIP001      {
//STRIP001          if (pTestSheet->GetFamily() == eOldFamily &&
//STRIP001              pTestSheet->HasParentSupport()        &&
//STRIP001              pTestSheet->GetParent() == aOldName)
//STRIP001              pTestSheet->SetParent(aOldName); // Verknuepfung neu aufbauen
//STRIP001
//STRIP001          if (pTestSheet->GetFamily() == eOldFamily &&
//STRIP001              pTestSheet->HasFollowSupport()        &&
//STRIP001              pTestSheet->GetFollow() == aOldName)
//STRIP001              pTestSheet->SetFollow(aOldName); // Verknuepfung neu aufbauen
//STRIP001
//STRIP001          pTestSheet = pMyPool->Next();
//STRIP001      }
//STRIP001
//STRIP001      // hat der Neue einen Parent? wenn ja, mit gleichem Namen bei uns suchen
//STRIP001      if (pHisSheet->HasParentSupport())
//STRIP001      {
//STRIP001          const String& rParentName = pHisSheet->GetParent();
//STRIP001          if (0 != rParentName.Len())
//STRIP001          {
//STRIP001              SfxStyleSheetBase* pParentOfNew = pMyPool->Find(rParentName,
//STRIP001                                                              eOldFamily);
//STRIP001              if (pParentOfNew)
//STRIP001                  rNewSheet.SetParent(rParentName);
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      // hat der Neue einen Follow? wenn ja, mit gleichem Namen bei uns suchen
//STRIP001      if (pHisSheet->HasFollowSupport())
//STRIP001      {
//STRIP001          const String& rFollowName = pHisSheet->GetFollow();
//STRIP001          if (0 != rFollowName.Len())
//STRIP001          {
//STRIP001              SfxStyleSheetBase* pFollowOfNew = pMyPool->Find(rFollowName,
//STRIP001                                                              eOldFamily);
//STRIP001              if (pFollowOfNew)
//STRIP001                  rNewSheet.SetFollow(rFollowName);
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      // Model geaendert
//STRIP001      pChDoc->SetChanged(TRUE);
//STRIP001      SetModified(TRUE);
//STRIP001
//STRIP001      bRet = TRUE;
//STRIP001  }
//STRIP001
//STRIP001  return bRet;
//STRIP001 }

/*************************************************************************
|*
|*  Vorlage entfernen (zunaechst nur Dummy)
|*
\************************************************************************/

//STRIP001 BOOL SchChartDocShell::Remove( USHORT nIdx1, USHORT nIdx2, USHORT nIdx3 ) throw()
//STRIP001 {
//STRIP001
//STRIP001  CHART_TRACE( "SchChartDocShell::Remove" );
//STRIP001
//STRIP001  BOOL bRet = FALSE;
//STRIP001
//STRIP001  if (CONTENT_STYLE == nIdx1)
//STRIP001  {
//STRIP001      SfxStyleSheetBasePool* pMyPool  = GetStyleSheetPool();
//STRIP001      SfxStyleSheetBase*     pMySheet =  (*pMyPool)[nIdx2];
//STRIP001      String          aName(pMySheet->GetName());
//STRIP001      String          aEmpty;
//STRIP001      SfxStyleFamily  eFamily = pMySheet->GetFamily();
//STRIP001      if (pMySheet)
//STRIP001      {
//STRIP001          pMyPool->Erase(pMySheet);
//STRIP001          bRet = TRUE;
//STRIP001      }
//STRIP001
//STRIP001      SfxStyleSheetBase* pTestSheet = pMyPool->First();
//STRIP001      while (pTestSheet)
//STRIP001      {
//STRIP001          if (pTestSheet->GetFamily() == eFamily &&
//STRIP001              pTestSheet->HasParentSupport()     &&
//STRIP001              pTestSheet->GetParent() == aName)
//STRIP001              pTestSheet->SetParent(aEmpty); // Verknuepfung aufloesen
//STRIP001
//STRIP001          if (pTestSheet->GetFamily() == eFamily &&
//STRIP001              pTestSheet->HasFollowSupport()        &&
//STRIP001              pTestSheet->GetFollow() == aName)
//STRIP001              pTestSheet->SetFollow(aEmpty); // Verknuepfung aufloesen
//STRIP001
//STRIP001          pTestSheet = pMyPool->Next();
//STRIP001      }
//STRIP001
//STRIP001  }
//STRIP001
//STRIP001  // Model geaendert
//STRIP001  pChDoc->SetChanged(TRUE);
//STRIP001  SetModified(TRUE);
//STRIP001
//STRIP001  return bRet;
//STRIP001 }

/*************************************************************************
|*
|*  Chart updaten
|*
\************************************************************************/

//STRIP001 void SchChartDocShell::UpdateChart( OutputDevice* pOut ) throw()
//STRIP001 {
//STRIP001  pChDoc->BuildChart(TRUE);
//STRIP001 }

/*************************************************************************
|*
|*
|*
\************************************************************************/

/*N*/ Rectangle SchChartDocShell::GetVisArea(USHORT nAspect) const throw()
/*N*/ {
/*N*/   return SfxInPlaceObject::GetVisArea((nAspect == ASPECT_THUMBNAIL) ?
/*N*/                                        ASPECT_CONTENT : nAspect);
/*N*/ }

/*************************************************************************
|*
|* VisArea fuer InPlace setzen
|*
\************************************************************************/

/*N*/ void SchChartDocShell::SetVisArea(const Rectangle& rRect) throw()
/*N*/ {
/*N*/   Rectangle aRect(rRect);
/*N*/   aRect.SetPos(Point(0, 0));
/*N*/
/*N*/   if( GetCreateMode() == SFX_CREATE_MODE_EMBEDDED )
/*N*/   {
/*N*/       // sets the modified flag
/*N*/       SfxInPlaceObject::SetVisArea( rRect );
/*N*/
/*N*/         // #107434# propagate modified status to changed status at model
/*N*/         if( pChDoc && IsModified() )
/*N*/             pChDoc->SetChanged( TRUE );
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/         // does not set the modified flag
/*?*/       SvEmbeddedObject::SetVisArea( rRect );
/*N*/   }
/*N*/
/*N*/     if( GetCreateMode() != SFX_CREATE_MODE_INTERNAL )
/*N*/   {
/*N*/       Size aSize;
/*N*/
/*N*/       if (rRect.IsEmpty ())
/*N*/           aSize = Size ();
/*N*/       else
/*N*/           aSize = GetVisArea(ASPECT_CONTENT).GetSize();
/*N*/
/*N*/       SdrPage* pPage = pChDoc->GetPage(0);
/*N*/
/*N*/       if(aSize.Width() > 0 && aSize.Height() > 0)
/*N*/       {
/*N*/           if( !pPage || aSize != pPage->GetSize() )
/*N*/           {
/*N*/               SfxViewFrame* pViewFrame = GetFrame();
/*N*/               if( pViewFrame )
/*N*/                   pViewFrame->GetDispatcher()->Execute( SID_TOOL_SELECT,
/*N*/                                                         SFX_CALLMODE_SYNCHRON );
/*N*/               pChDoc->ResizePage(aSize);
/*N*/
/*N*/                 // notify the controller
/*N*/                 // note: the controller is only available in in-place
/*N*/                 Broadcast( SchVisAreaChangedHint( rRect ) );
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|* OLE-Status
|*
\************************************************************************/

/*N*/ ULONG SchChartDocShell::GetMiscStatus() const throw()
/*N*/ {
/*N*/   // Chart soll stets selber resizen
/*N*/   ULONG nStatus = SfxInPlaceObject::GetMiscStatus() |
/*N*/                   SVOBJ_MISCSTATUS_SERVERRESIZE     |
/*N*/                   SVOBJ_MISCSTATUS_RESIZEONPRINTERCHANGE;
/*N*/
/*N*/   return nStatus;
/*N*/ }

/*N*/ void SchChartDocShell::SetModified( BOOL bModified ) throw()
/*N*/ {
/*N*/   if( IsEnableSetModified() )
/*N*/   {
/*N*/       SfxInPlaceObject::SetModified( bModified );
/*N*/       DBG_ASSERT( pChDoc, "Invalid ChartModel" );
/*N*/       if( ! pChDoc->IsLockedBuild())
/*N*/           Broadcast( SfxSimpleHint( SFX_HINT_DOCCHANGED ) );
/*N*/   }
/*N*/ }



}
