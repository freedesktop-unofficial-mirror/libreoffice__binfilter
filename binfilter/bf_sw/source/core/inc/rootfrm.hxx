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
#ifndef _ROOTFRM_HXX
#define _ROOTFRM_HXX

#include <bf_svtools/bf_solar.h>

#include "layfrm.hxx"
#include "frmfmt.hxx"
#include "doc.hxx"
class OutputDevice;
namespace binfilter {

class SwCntntFrm;
class ViewShell;
class SdrPage;
class SwPaM;
class SwCursor;
class SwShellCrsr;
class SwTableCursor;

class SwLayVout;
class SwDestroyList;
struct SwPosition;
struct SwCrsrMoveState;

#define HACK_TABLEMODE_INIT         0
#define HACK_TABLEMODE_LOCKLINES    1
#define HACK_TABLEMODE_PAINTLINES   2
#define HACK_TABLEMODE_UNLOCKLINES  3
#define HACK_TABLEMODE_EXIT         4

#define INV_SIZE    1
#define INV_PRTAREA 2
#define INV_POS     4
#define INV_TABLE   8
#define INV_SECTION 16
#define INV_LINENUM 32
#define INV_DIRECTION 64

class SwRootFrm : public SwLayoutFrm
{
    // Fuer das Anlegen und Zerstoeren des virtuellen Outputdevice-Managers
    friend void _FrmInit();     //erzeugt pVout
    friend void _FrmFinit();    //loescht pVout

    static SwLayVout     *pVout;
    static BOOL           bInPaint;     //Schutz gegen doppelte Paints.
    static BOOL           bNoVirDev;    //Bei SystemPaints kein virt. Device

public:
    SwRootFrm( SwFrmFmt *pFmt )
      : SwLayoutFrm( pFmt->GetDoc()->MakeFrmFmt(
          XubString( "Root", RTL_TEXTENCODING_MS_1252 ), pFmt ) ) {}
    static BOOL IsInPaint() { return bInPaint; }
    static void SetNoVirDev( const BOOL bNew ) { bNoVirDev = bNew; }
};

} //namespace binfilter
#endif  //_ROOTFRM_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
