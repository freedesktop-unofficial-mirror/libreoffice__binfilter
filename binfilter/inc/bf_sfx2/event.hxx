/*************************************************************************
 *
 *  $RCSfile: event.hxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:23:30 $
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
#ifndef _SFXEVENT_HXX
#define _SFXEVENT_HXX

#ifndef _STRING_HXX //autogen
#include <tools/string.hxx>
#endif
#ifndef _SFXHINT_HXX //autogen
#include <svtools/hint.hxx>
#endif

#include <com/sun/star/uno/Sequence.hxx>
#include <com/sun/star/beans/PropertyValue.hpp>

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
                            _bAddToHistory(FALSE),
                            _aArgs( rArgs )
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
                            _bAddToHistory( FALSE ),
                            _aArgs( rArgs )
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

class PrintDialog;
class Printer;
class SfxPrintingHint : public SfxHint
{
    PrintDialog*        pDialog;
    Printer*            pPrinter;
    sal_Int32           nWhich;
    com::sun::star::uno::Sequence < com::sun::star::beans::PropertyValue > aOpts;
public:
                        TYPEINFO();
                        SfxPrintingHint( sal_Int32 nEvent, PrintDialog* pDlg, Printer* pPrt, const com::sun::star::uno::Sequence < com::sun::star::beans::PropertyValue >& rOpts )
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
    const com::sun::star::uno::Sequence < com::sun::star::beans::PropertyValue >& GetAdditionalOptions() { return aOpts; }
};

#endif
