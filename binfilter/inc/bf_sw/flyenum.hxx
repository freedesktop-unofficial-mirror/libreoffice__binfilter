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

#ifndef _FLYENUM_HXX
#define _FLYENUM_HXX
namespace binfilter {

enum FlyCntType
{
     FLYCNTTYPE_ALL = 0,
     FLYCNTTYPE_FRM,
     FLYCNTTYPE_GRF,
     FLYCNTTYPE_OLE

};

//Returnwerte fuer Chainable und Chain
#define SW_CHAIN_OK             0
#define SW_CHAIN_NOT_EMPTY      1       //Nur leere Frames duerfen connected werden
#define SW_CHAIN_IS_IN_CHAIN    2       //Destination ist bereits in einer chain
#define SW_CHAIN_WRONG_AREA     3       //Destination steht in einer nicht erlaubten
                                        //Section (Kopf-/Fusszeile)
#define SW_CHAIN_NOT_FOUND      4       //Destination und/oder Source nicht gefunden
#define SW_CHAIN_SOURCE_CHAINED 5       //Source hat bereits einen Follow
#define SW_CHAIN_SELF           6       //Sich selbst zu verketten  ist
                                        //natuerlich nicht erleubt.



} //namespace binfilter
#endif


/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
