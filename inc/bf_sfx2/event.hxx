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
#ifndef _SFXEVENT_HXX
#define _SFXEVENT_HXX

#include <bf_svtools/bf_solar.h>

#include <bf_tools/string.hxx>
#include <bf_svtools/hint.hxx>

#include <com/sun/star/uno/Sequence.hxx>
#include <com/sun/star/beans/PropertyValue.hpp>
class PrintDialog;
class Printer;
namespace binfilter {

class SfxObjectShell;

//-------------------------------------------------------------------

class SfxEventHint : public SfxHint
{
    USHORT              nEventId;
    SfxObjectShell*     pObjShell;
    String              _aArgs;
    BOOL                _bDummy;
    BOOL                _bAddToHistory;

public:
    TYPEINFO();
                        SfxEventHint( USHORT nId,
                                      const String& rArgs,
                                      SfxObjectShell *pObj = 0  )
                        :   nEventId(nId),
                            pObjShell(pObj),
                            _aArgs( rArgs ),
                            _bAddToHistory(FALSE)
                        {}
                        SfxEventHint( USHORT nId, SfxObjectShell *pObj = 0 )
                        :   nEventId(nId),
                            pObjShell(pObj),
                            _bAddToHistory(FALSE)
                        {}

    const String& GetArgs() const { return _aArgs;}

    USHORT              GetEventId() const
                        { return nEventId; }

    SfxObjectShell*     GetObjShell() const
                        { return pObjShell; }
};

//-------------------------------------------------------------------

class SfxNamedHint : public SfxHint
{
    String              _aEventName;
    SfxObjectShell*     _pObjShell;
    String              _aArgs;
    BOOL                _bDummy;
    BOOL                _bAddToHistory;

public:
                        TYPEINFO();

                        SfxNamedHint( const String& rName,
                                      const String& rArgs,
                                      SfxObjectShell *pObj = 0  )
                        :   _aEventName( rName ),
                            _pObjShell( pObj),
                            _aArgs( rArgs ),
                            _bAddToHistory( FALSE )
                        {}

                        SfxNamedHint( const String& rName,
                                      SfxObjectShell *pObj = 0 )
                        :   _aEventName( rName ),
                            _pObjShell( pObj ),
                            _bAddToHistory( FALSE )
                        {}

    const String&       GetArgs() const { return _aArgs;}
    const String&       GetName() const { return _aEventName; }
    SfxObjectShell*     GetObjShell() const { return _pObjShell; }
};

class SfxPrintingHint : public SfxHint
{
    PrintDialog*        pDialog;
    Printer*            pPrinter;
    sal_Int32           nWhich;
    ::com::sun::star::uno::Sequence < ::com::sun::star::beans::PropertyValue > aOpts;
public:
                        TYPEINFO();
                        SfxPrintingHint( sal_Int32 nEvent, PrintDialog* pDlg, Printer* pPrt, const ::com::sun::star::uno::Sequence < ::com::sun::star::beans::PropertyValue >& rOpts )
                            : pDialog( pDlg )
                            , pPrinter( pPrt )
                            , nWhich( nEvent )
                            , aOpts( rOpts )
                        {}

                        SfxPrintingHint( sal_Int32 nEvent, PrintDialog* pDlg, Printer* pPrt )
                            : pDialog( pDlg )
                            , pPrinter( pPrt )
                            , nWhich( nEvent )
                        {}

    Printer*            GetPrinter() const { return pPrinter; }
    PrintDialog*        GetPrintDialog() const { return pDialog; }
    sal_Int32           GetWhich() const { return nWhich; }
    const ::com::sun::star::uno::Sequence < ::com::sun::star::beans::PropertyValue >& GetAdditionalOptions() { return aOpts; }
};

}//end of namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
