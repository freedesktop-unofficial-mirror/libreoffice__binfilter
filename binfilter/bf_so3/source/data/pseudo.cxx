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


#include <bf_so3/pseudo.hxx>
#include <tools/date.hxx>
#include <tools/debug.hxx>
#include <bf_tools/unqid.hxx>
#include <vcl/svapp.hxx>
#include <vcl/wrkwin.hxx>
#include <vcl/menu.hxx>
#include <bf_so3/embobj.hxx>
#include <bf_so3/client.hxx>
#include <bf_so3/svstor.hxx>
#include "bf_so3/soerr.hxx"

namespace binfilter {

//=========================================================================
//==================class SvVerb===========================================
//=========================================================================
PRV_SV_IMPL_OWNER_LIST(SvVerbList,SvVerb)

namespace
{
    UniqueItemId lclCreateUniqueId()
    {
        static UniqueIdContainer aUniqueIdContainer(UNIQUEID_SV_BEGIN);
        return aUniqueIdContainer.CreateId();
    }
}

//=========================================================================
SvVerb::SvVerb
(
    long nIdP,              /* Identifer des Verbs  */
    const String & rNameP,  /* Name des Verbs, sprachabh"angig  */
    BOOL bConstP,           /* TRUE, dieses Verb ver"andert das Objekt nicht */
    BOOL bOnMenuP           /* TRUE, dieses Verb soll im Menu erscheinen */
)
{
    nId     = nIdP;
    aName   = rNameP;
    aMenuId = lclCreateUniqueId();
    bConst  = bConstP;
    bOnMenu = bOnMenuP;
}

//=========================================================================
SvVerb::SvVerb
(
    const SvVerb & rObj
)
{
    nId     = rObj.nId;
    aName   = rObj.aName;
    aMenuId = rObj.aMenuId;
    bConst  = rObj.bConst;
    bOnMenu = rObj.bOnMenu;
}

//=========================================================================
SvVerb & SvVerb::operator =
(
    const SvVerb & rObj
)
{
    if( this != &rObj )
    {
        nId     = rObj.nId;
        aName   = rObj.aName;
        aMenuId = rObj.aMenuId;
        bConst  = rObj.bConst;
        bOnMenu = rObj.bOnMenu;
    }
    return *this;
}

//=========================================================================
SvVerb::~SvVerb()
{
    // UniqueId wird freigegeben
}

//=========================================================================
//==================class SvPseudoObject===================================
//=========================================================================
SV_IMPL_FACTORY(SvPseudoObjectFactory)
    {
    }
};
TYPEINIT1(SvPseudoObjectFactory,SvFactory);

SO2_IMPL_STANDARD_CLASS1_DLL(SvPseudoObject,SvPseudoObjectFactory,SvObject,
                             0x2A499E61L, 0x733F, 0x101C,
                             0x8D,0x86,0x4A,0x04,0x12,0x94,0x26,0x0D)
//=========================================================================
SvPseudoObject::SvPseudoObject()
/*  [Beschreibung]

    Konstruktor der Klasse SvPseudoObject.
*/
    : pVerbs        ( NULL )
    , bDeleteVerbs  ( FALSE )
{
}

//=========================================================================
SvPseudoObject::~SvPseudoObject()
/*  [Beschreibung]

    Destruktor der Klasse SvPeudoObjekt. Das Objekt tr"agt sich selber
    aus der <Running Object Table> aus.
*/
{
    if( bDeleteVerbs ) // Selbst erzeugt ?
        delete pVerbs;
}

//=========================================================================
::IUnknown * SvPseudoObject::GetMemberInterface( const SvGlobalName & )
/*  [Beschreibung]

    Jede Klasse muss eine Abfrage auf die Ole-Interfaces unterst"utzen.
    Es d"urfen nur die eigenen Ole-Interfaces und nicht die der
    Super-Klassen abgefragt werden. Siehe <So Ole-Unterst"utzung>.
*/
{
    return NULL;
}

//=========================================================================
void SvPseudoObject::FillClass
(
    SvGlobalName * pClassName,  /* Der Typ der Klasse */
    ULONG * pFormat,            /* Das Dateiformat in dem geschrieben wird */
    String * pAppName,          /* Der Applikationsname */
    String * pFullTypeName,     /* Der genaue Name des Typs */
    String * pShortTypeName,    /* Der kurze Name des Typs  */
    long /*nFileFormat */       /* F"ur dieses Office-Format sollen die
                                   Parameter gef"ullt werden */
) const
/*  [Beschreibung]

    Diese Methode liefert Informationen "uber den Typ und das Dateiformat
    des Objektes. Alle Parameter werden von der Methode gefuellt.

    [R"uckgabewert]

    *pClassName     Liefert den Typ-Identifier des Objektes.
    *pFormat        Immer 0, siehe aber <SvEmbeddedObject::FillClass>
    *pAppName       Den sprachabh"angigen Applikationsnamen.
    *pFullTypeName  Den sprachabh"angigen Namen des Typs.
    *pShortTypeName Den kurzen sprachabh"angigen Namen des Typs. Er darf
                    nicht l"anger als 15 Zeichen sein.

    [Beispiel]

    MyClass::FillClass( ... )
    {
        *pClassName     = *SvFactory::GetSvFactory(); // keine emulation
        *pFormat        = 0;
        *pAppName       = "StarDivison Calc 3.0";
        *pFullTypeName  = "StarDivison Calc 3.0 Tabelle";
        *pShortTypeName = "Tabelle";
    }

    [Querverweise]

    <SvPersist::FillClass()>
*/
{
    *pFormat        = 0;
    *pFullTypeName  = *pShortTypeName = *pAppName = String();
    *pClassName     = SvGlobalName();

    if( Owner() )
    {
        *pClassName = *GetSvFactory();
        *pAppName = Application::GetDisplayName();
    }
}

//=========================================================================
SvGlobalName SvPseudoObject::GetClassName() const
/*  [Beschreibung]

    Ruft <SvPseudoObject::FillClass> auf, um den Typ des Objektes zu bekommen.

    [R"uckgabewert]

    SvGlobalName    Der Typ des Objektes.
*/
{
    SvGlobalName    aName;
    String          aAppName, aFullTypeName, aShortTypeName;
    ULONG           nFormat;

    FillClass( &aName, &nFormat, &aAppName, &aFullTypeName,
                &aShortTypeName );
    return aName;
}

//=========================================================================
ErrCode SvPseudoObject::Verb
(
    long nVerb,                         /* Der Index in die Verbtabelle */
    SvEmbeddedClient * pCl,             /* Die Container-Seite mit dem der
                                           Objekt-Server ggf. kommuniziert.
                                        */
    Window * pWin,                      /* Das Fenster in dem das Objekt
                                           dargestellt wird. */
    const Rectangle * pWorkRectPixel    /* Die Position und Gr"osse des
                                           Objektes im Container */
)
/*  [Beschreibung]

    Der Objekt-Server wird mit nVerb beauftragt eine bestimmte Aktion
    auszufuehren. Dies kann z.B. das Abspielen eines Sound's oder Video's
    sein. Ebenso kann es das oeffnen und Anzeigen eines Dokumentes
    bedeuten. Es gibt einige Default-Verben:
    SVVERB_SHOW,        Anzeigen des Objektes
    SVVERB_OPEN,        Anzeigen des Objektes im eigenen Dokumentfenster
    SVVERB_HIDE,        Das Objekt nicht mehr anzeigen.
    SVVERB_UIACTIVATE,  Das Objekt UI-Aktivieren.
    SVVERB_IPACTIVATE,  Das Objekt IP-Aktivieren.

    [Anmerkung]
    Einige Verben machen nur IP-Aktivierung sinn. Mehr ueber IP-Aktivierung
    in der Klasse <SvInPLaceObjekt>.

*/
{
    (void)nVerb;
    (void)pCl;
    (void)pWin;
    (void)pWorkRectPixel;

    ErrCode nRet = ERRCODE_SO_GENERALERROR;
    return nRet;
}

//=========================================================================
BOOL SvPseudoObject::Close()
/*  [Beschreibung]

    Versucht alle zum Objekt bestehenden Verbindungen abzubrechen.

    [Anmerkung]

    Handelt es sich um einen Link, dann muss die Verbindung zur Quelle
    abgebrochen werden.
*/
{
    return TRUE;
}

//=========================================================================
void SvPseudoObject::SetVerbList
(
    SvVerbList * pVerbsP    /* die Verbliste wird "ubernommen,
                               sie darf nicht zerst"ort werden, bevor
                               sie nicht mit SetVerbList( NULL ) oder
                               automatisch im Destruktor ausgetragen wurde */
    , BOOL bDelete
)
/*  [Beschreibung]

    Setzen der Verbliste, diese wird dann in
    <SvPseudoObject::GetVerbList> zur"uckgegeben.
*/
{
    if( bDeleteVerbs )
        delete pVerbs;

    bDeleteVerbs = bDelete;
    pVerbs = pVerbsP;
}


//=========================================================================
const SvVerbList & SvPseudoObject::GetVerbList() const
/*  [Beschreibung]

    Die Verbliste des Objektes wird zur"uckgegeben.
*/
{
    if( pVerbs ) // darf, wegen Unique Id's nicht geaendert werden
        return *pVerbs;

    ((SvPseudoObject *)this)->pVerbs = new SvVerbList();
    ((SvPseudoObject *)this)->bDeleteVerbs    = TRUE;

    return *pVerbs;
}

//=========================================================================
ULONG SvPseudoObject::GetMiscStatus() const
/*  [Beschreibung]

    Diese Methode liefert weitere Informationen "uber das Objekt.
*/
{
    ULONG nMisc = 0;
    return nMisc;
}


}


/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
