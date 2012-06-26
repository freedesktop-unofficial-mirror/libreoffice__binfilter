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

#ifndef SC_DDELINK_HXX
#define SC_DDELINK_HXX

#include <bf_so3/lnkbase.hxx>
#include <bf_svtools/brdcst.hxx>
namespace binfilter {

class ScDocument;
class ScMatrix;
class ScMultipleReadHeader;

class ScDdeLink : public ::binfilter::SvBaseLink, public SfxBroadcaster
{
private:
static BOOL bIsInUpdate;

    ScDocument*     pDoc;

    String          aAppl;          // Verbindungsdaten
    String          aTopic;
    String          aItem;
    BYTE            nMode;          // Zahlformat-Modus

    BOOL            bNeedUpdate;    // wird gesetzt, wenn Update nicht moeglich war

    ScMatrix*       pResult;        // Ergebnis

public:
    TYPEINFO();

            ScDdeLink( ScDocument* pD,
                         const String& rA, const String& rT, const String& rI,
                        BYTE nM );
            ScDdeLink( ScDocument* pD, SvStream& rStream, ScMultipleReadHeader& rHdr );
    virtual ~ScDdeLink();

                                            // von SvBaseLink ueberladen:
    virtual void    DataChanged( const String& rMimeType,
                                const ::com::sun::star::uno::Any & rValue );

                                            // von SfxBroadcaster ueberladen:

                                            // fuer Interpreter:

    const ScMatrix* GetResult() const   { return pResult; }
    ScMatrix* GetResult()   {return pResult; }

    const String&   GetAppl() const     { return aAppl; }
    const String&   GetTopic() const    { return aTopic; }
    const String&   GetItem() const     { return aItem; }
    BYTE            GetMode() const     { return nMode; }

    void            TryUpdate();
};


} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
