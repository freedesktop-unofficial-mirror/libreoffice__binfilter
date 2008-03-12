/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: pseudo.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 08:11:18 $
 *
 *  The Contents of this file are made available subject to
 *  the terms of GNU Lesser General Public License Version 2.1.
 *
 *
 *    GNU Lesser General Public License Version 2.1
 *    =============================================
 *    Copyright 2005 by Sun Microsystems, Inc.
 *    901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *    This library is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License version 2.1, as published by the Free Software Foundation.
 *
 *    This library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with this library; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *    MA  02111-1307  USA
 *
 ************************************************************************/


#include <bf_so3/pseudo.hxx>
#include <tools/date.hxx>
#include <tools/debug.hxx>
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
    aMenuId = GetpApp()->CreateUniqueId();
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
#ifdef TEST_INVARIANT

void SvPseudoObject::TestMemberObjRef( BOOL /*bFree*/ )
/*  [Beschreibung]

    Siehe <So Debugging>.
*/
{
}

//=========================================================================

void SvPseudoObject::TestMemberInvariant( BOOL bPrint )
/*  [Beschreibung]

    Siehe <So Debugging>.
*/
{
    (void)bPrint;
}
#endif




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

    <SvPseudoObject::GetFullTypeName>, <SvPseudoObject::GetShortTypeName>,
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
String SvPseudoObject::GetAppName() const
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
    return aAppName;
}

//=========================================================================
String SvPseudoObject::GetFullTypeName() const
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
    return aFullTypeName;
}

//=========================================================================
String SvPseudoObject::GetShortTypeName() const
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
    return aShortTypeName;
}

//=========================================================================
ErrCode SvPseudoObject::DoVerb
(
    long nVerb,                         /* Der Index in die Verbtabelle */
    SvEmbeddedClient * pCallerClient,   /* Die Container-Seite mit dem der
                                           Objekt-Server ggf. kommuniziert.
                                        */
    Window * pWin,                      /* Das Fenster in dem das Objekt
                                           dargestellt wird. */
    const Rectangle * pWorkRectPixel    /* Die Position und Gr"osse des
                                           Objektes im Container */
)
/*  [Beschreibung]

    Diese Methode ist eine Wrapper-Funktion um <SvPseudoObject::Verb>.
    Sie teilt dem Container zusaetzlich mit, dass das Objekt in den
    sichtbaren Bereich geschoben werden soll.
*/
{
    // Default-Verben sind negativ
    return Verb( nVerb, pCallerClient, pWin, pWorkRectPixel );
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
const SvVerb * SvPseudoObject::GetVerb
(
    USHORT nMenuId  /* Wurden Verben mit der Methode
                       <SvEmbeddedObject::AppendVerbs> an ein Menu
                       angeh"angt, dann ist dies die MenuId, mit der
                       nach dem Verb gesucht wird */
) const
/*  [Beschreibung]

    In der Verbliste wird nach einem Verb mit der Id nMenuId gesucht.

    [Anmerkung]

    Nachdem ein Menu erzeugt wurde darf die Verbliste nicht vera"ndert
    werden, da die MenuIs's in den Verben vom Zeitpunkt des erzeugens und
    nicht vom Inhalt abh"angig sind.

    [R"uckgabewert]

    const SvVerb *  NULL, das Verb wurde nicht gefunden. Ansonsten wird
                    das Verb mit der entsprechenden MenuId geliefert.
*/
{
    const SvVerbList & rVerbs = GetVerbList();
    for( ULONG i = 0; i < rVerbs.Count(); i++ )
        if( rVerbs[ i ].GetMenuId() == nMenuId )
            return &rVerbs[ i ];
    return NULL;
}

//=========================================================================
void SvPseudoObject::AppendVerbs
(
    Menu & rMenu    /* An dieses Menu werden die Verben angeh"angt */
)
/*  [Beschreibung]

    Die Verben des Objektes werden an das Menu rMenu angeh"angt, wenn
    sie das Attribut <SvVerb::IsOnMenu> == TRUE haben.
*/
{
    const SvVerbList & rVerbs = GetVerbList();
    for( ULONG i = 0; i < rVerbs.Count(); i++ )
    {
        const SvVerb & rVerb = rVerbs[ i ];
        if( rVerb.IsOnMenu() )
            rMenu.InsertItem( rVerb.GetMenuId(), rVerb.GetName() );
    }
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


