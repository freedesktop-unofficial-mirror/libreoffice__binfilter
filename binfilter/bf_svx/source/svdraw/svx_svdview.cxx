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

#include <eeitem.hxx>

#include "svdio.hxx"
#include "svdstr.hrc"   // Namen aus der Resource
#include "svdglob.hxx"  // StringCache
#include "svdpagv.hxx"
#include "svdopath.hxx" // fuer GetContext
#include "svdograf.hxx" // fuer GetContext
#include "svdview.hxx"
#include "editview.hxx" // fuer GetField
#define ITEMID_FIELD EE_FEATURE_FIELD  /* wird fuer #include <flditem.hxx> benoetigt */


#include "itemdata.hxx"

#include "flditem.hxx"  // fuer URLField
#include "svdoutl.hxx"

// #90477#
#include <tools/tenccvt.hxx>
namespace binfilter {

/*N*/ TYPEINIT1(SdrView,SdrCreateView);

/*N*/ SdrView::SdrView(SdrModel* pModel1, OutputDevice* pOut):
/*N*/   SdrCreateView(pModel1,pOut),
/*N*/   bNoExtendedMouseDispatcher(FALSE),
/*N*/   bNoExtendedKeyDispatcher(FALSE),
/*N*/   bNoExtendedCommandDispatcher(FALSE)
/*N*/ {
/*N*/   bTextEditOnObjectsWithoutTextIfTextTool=FALSE;
/*N*/
/*N*/
/*N*/   onAccessibilityOptionsChanged();
/*N*/ }

/*N*/ SdrView::SdrView(SdrModel* pModel1):
/*N*/   SdrCreateView(pModel1,(OutputDevice*)NULL),
/*N*/   bNoExtendedMouseDispatcher(FALSE),
/*N*/   bNoExtendedKeyDispatcher(FALSE),
/*N*/   bNoExtendedCommandDispatcher(FALSE)
/*N*/ {
/*N*/   bTextEditOnObjectsWithoutTextIfTextTool=FALSE;
/*N*/
/*N*/
/*N*/   onAccessibilityOptionsChanged();
/*N*/ }

/*N*/ SdrView::~SdrView()
/*N*/ {
/*N*/ }






/* new interface src537 */



// Mit der Maus draggen (Move)
// Beispiel beim erzeugen eines Rechtecks. MouseDown muss ohne
// ModKey erfolgen, weil sonst i.d.R. Markieren forciert wird (s.u.)
// Drueckt man dann beim MouseMove gleichzeitig Shift, Ctrl, und Alt,
// so erzeugt man ein zentrisches Quadrat ohne Fang.
// Die Doppelbelegung von Ortho und Shift stellt i.d.R. kein Problem dar,
// da sich beides meisst gegenseitig ausschliesst. Einzig Shear (das beim
// Verzerren, nicht dass beim Drehen) beruecksichtigt beides gleichzeitig.
// Dass muss der Anwender erstmal noch umschiffen (z.B. mit einer Hilfslinie).
#define MODKEY_NoSnap    bCtrl  /* Fang temporaer aus */
#define MODKEY_Ortho     bShift /* na eben ortho */
#define MODKEY_Center    bAlt   /* Zentrisch erzeugen/resizen */
//#define MODKEY_BigOrtho  bAlt
#define MODKEY_AngleSnap bShift
#define MODKEY_CopyDrag  bCtrl  /* Draggen mit kopieren */

// irgendwo hinklicken (MouseDown)
#define MODKEY_PolyPoly  bAlt   /* Neues Poly bei InsPt und bei Create */
#define MODKEY_MultiMark bShift /* MarkObj ohne vorher UnmarkAll */
#define MODKEY_Unmark    bAlt   /* Unmark durch Rahmenaufziehen */
#define MODKEY_ForceMark bCtrl  /* Rahmenaufziehen erzwingen, auch wenn Obj an MausPos */
#define MODKEY_DeepMark  bAlt   /* MarkNextObj */
#define MODKEY_DeepBackw bShift /* MarkNextObj rueckwaerts */

} //namespace binfilter
#include "outlobj.hxx"
namespace binfilter {

/*N*/ void SdrView::UnmarkAll()
/*N*/ {
/*N*/   if (IsTextEdit()) {
/*?*/       ESelection eSel=GetTextEditOutlinerView()->GetSelection();
/*?*/       eSel.nStartPara=eSel.nEndPara;
/*?*/       eSel.nStartPos=eSel.nEndPos;
/*?*/       GetTextEditOutlinerView()->SetSelection(eSel);
/*N*/   }
        else if ( !HasMarkedGluePoints() )
        {
/*N*/       if ( !HasMarkedPoints() )
/*N*/           UnmarkAllObj();
        }
/*N*/ }


/*N*/ void SdrView::DeleteMarked()
/*N*/ {DBG_BF_ASSERT(0, "STRIP");
/*N*/ }


/*N*/ void SdrView::WriteRecords(SvStream& rOut) const
/*N*/ {
/*N*/   {
/*N*/       // Der CharSet muss! als erstes rausgestreamt werden
/*N*/       SdrNamedSubRecord aSubRecord(rOut,STREAM_WRITE,SdrInventor,SDRIORECNAME_VIEWCHARSET);
/*N*/
/*N*/       // UNICODE:
/*N*/       // rtl_TextEncoding eOutCharSet=rOut.GetStreamCharSet();
/*N*/       rtl_TextEncoding eOutCharSet = osl_getThreadTextEncoding();
/*N*/
/*N*/       // #90477# rOut << UINT16( GetStoreCharSet( eOutCharSet ) );
/*N*/       rOut << (UINT16)GetSOStoreTextEncoding(eOutCharSet);
/*N*/   }
/*N*/   SdrCreateView::WriteRecords(rOut);
/*N*/ }

/*N*/ BOOL SdrView::ReadRecord(const SdrIOHeader& rViewHead,
/*N*/   const SdrNamedSubRecord& rSubHead,
/*N*/   SvStream& rIn)
/*N*/ {
/*N*/   BOOL bRet=FALSE;
/*N*/   if (rSubHead.GetInventor()==SdrInventor) {
/*N*/       bRet=TRUE;
/*N*/       switch (rSubHead.GetIdentifier()) {
/*N*/           case SDRIORECNAME_VIEWCHARSET: {
/*N*/               UINT16 nCharSet;
/*N*/               // #90477# rIn>>nCharSet;
/*N*/               // rIn.SetStreamCharSet(rtl_TextEncoding(nCharSet));
/*N*/               rIn >> nCharSet;
/*N*/               rIn.SetStreamCharSet(GetSOLoadTextEncoding((rtl_TextEncoding)nCharSet));
/*N*/           } break;
/*N*/           default: bRet=FALSE;
/*N*/       }
/*N*/   }
/*N*/   if (!bRet) bRet=SdrCreateView::ReadRecord(rViewHead,rSubHead,rIn);
/*N*/   return bRet;
/*N*/ }

/*N*/ SvStream& operator<<(SvStream& rOut, const SdrView& rView)
/*N*/ {
/*N*/   SdrIOHeader aHead(rOut,STREAM_WRITE,SdrIOViewID);
/*N*/   rView.WriteRecords(rOut);
/*N*/   return rOut;
/*N*/ }

/*N*/ SvStream& operator>>(SvStream& rIn, SdrView& rView)
/*N*/ {
/*N*/   if (rIn.GetError()!=0) return rIn;
/*N*/   rView.BrkAction();
/*N*/   rView.Clear();
/*N*/   SdrIOHeader aHead(rIn,STREAM_READ);
/*N*/   if (!aHead.IsMagic()) {
/*N*/       rIn.SetError(SVSTREAM_FILEFORMAT_ERROR); // Format-Fehler
/*N*/       return rIn;
/*N*/   }
/*N*/   rtl_TextEncoding eStreamCharSetMerker=rIn.GetStreamCharSet(); // Der StreamCharSet wird von SdrView::ReadRecord() gesetzt
/*N*/   while (aHead.GetBytesLeft()>0 && rIn.GetError()==0 && !rIn.IsEof()) {
/*N*/       SdrNamedSubRecord aSubRecord(rIn,STREAM_READ);
/*N*/       rView.ReadRecord(aHead,aSubRecord,rIn);
/*N*/   }
/*N*/
/*N*/   rIn.SetStreamCharSet(eStreamCharSetMerker); // StreamCharSet wieder restaurieren
/*N*/
/*N*/   rView.InvalidateAllWin();
/*N*/   return rIn;
/*N*/ }


/*N*/ void SdrView::SFX_NOTIFY(SfxBroadcaster& rBC, const TypeId& rBCType, const SfxHint& rHint, const TypeId& rHintType)
/*N*/ {
/*N*/   if( rHint.ISA( SfxSimpleHint ) && ( (SfxSimpleHint&) rHint ).GetId() == SFX_HINT_ACCESSIBILITY_CHANGED )
/*N*/   {
/*?*/       onAccessibilityOptionsChanged();
/*N*/   }
/*N*/
/*N*/   SdrCreateView::SFX_NOTIFY(rBC, rBCType, rHint, rHintType );
/*N*/ }


/** method is called whenever the global SvtAccessibilityOptions is changed */
/*N*/ void SdrView::onAccessibilityOptionsChanged()
/*N*/ {
/*N*/ }

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
