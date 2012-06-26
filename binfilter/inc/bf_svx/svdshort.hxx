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

#error svdshort wird nicht mehr verwendet!

#ifndef _SVDSHORT_HXX
#define _SVDSHORT_HXX
namespace binfilter {

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef Weg_Mit_Den_Doofen_Abkuerzungen
                                           // Statistik - Stand 02-03-1995
                                           //   Haeufigkeit  Ersparnis
#define SdrObjSurrogate              SdrSU
#define SdrHelpLineKind              SdrFLK /* HL ist schon besetzt */
#define SdrHelpLineList              SdrFLL /* HL ist schon besetzt */
#define SdrHelpLine                  SdrFL  /* HL ist schon besetzt */
#define SdrMasterPageDescriptorList  SdrMPL
#define SdrMasterPageDescriptor      SdrMP
#define SdrObjTransformInfoRec       SdrTI
#define SdrDragCrook                 SdrDC
#define SdrDragMirror                SdrDI
#define SdrDragMovHdl                SdrDH
#define SdrDragResize                SdrDZ
#define SdrDragRotate                SdrDR
#define SdrDragShear                 SdrDE
#define SdrDragMove                  SdrDM
#define SdrCreateCmd                 SdrCC
#define SdrUndoAttrObj               SdrAU
#define SdrObjKind                   SdrOK
#define SdrUndoGroup                 SdrUG
#define SdrUndoAction                SdrUA
#define SdrAttrObj                   SdrAO
#define SdrGrafObj                   SdrGO
#define SdrMarkList                  SdrML
#define SdrHdlList                   SdrHL
#define SdrLayerAdmin                SdrLA
//#define SdrObjEditRec                SdrER
#define SdrObjIOHeader               SdrOH
#define SdrObjUserCall               SdrUC
#define SdrObjUnknown                SdrUO
#define SdrExchangeView              SdrXV
#define SdrCreateView                SdrCV
#define SdrOle2Obj                   SdrOO
#define SdrObjGeoData                SdrGD
#define SdrDragView                  SdrDV
#define SdrSnapView                  SdrSV
#define SdrObjList                   SdrOL
#define SdrEdgeObj                   SdrEO
#define SdrCircObj                   SdrCO
#define SdrObjGroup                  SdrOG
#define SdrPage                      SdrPg
#define SdrObjEditView               SdrOV
#define SdrModel                     SdrMD
#define ExtOutputDevice              SdrXO
#define SdrEditView                  SdrEV
#define SdrPaintView                 SdrNV
#define SdrPolyObj                   SdrPO
#define SdrRectObj                   SdrRO
#define SdrTextObj                   SdrTO
#define SdrMarkView                  SdrMV
#define SdrPathObj                   SdrBO
#define SdrPageView                  SdrPV
#define SdrVirtObj                   SdrVO
#define SdrObject                    SdrO

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////

}//end of namespace binfilter
#endif //_SVDSHORT_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
