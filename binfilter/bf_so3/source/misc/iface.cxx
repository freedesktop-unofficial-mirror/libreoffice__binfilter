/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: iface.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: vg $ $Date: 2007-10-23 13:49:08 $
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

#include <string.h>
#include <stdio.h>


#include <bf_so3/iface.hxx>
#include <sot/agg.hxx>
#include <svtools/ownlist.hxx>

#include "bf_so3/soerr.hxx"

#ifndef _DEBUG_HXX //autogen
#include <tools/debug.hxx>
#endif

/************** class SvObject ******************************************/
SV_IMPL_FACTORY(SvObjectFactory)
    {
    }
};
TYPEINIT1(SvObjectFactory,SvFactory);


SO2_IMPL_CLASS1_DLL(SvObject,SvObjectFactory,SotObject,
                   SvGlobalName( 0x7F7E0E60L, 0xC32D, 0x101B,
                            0x80, 0x4C, 0x04, 0x02, 0x1C, 0x00, 0x70, 0x02 ) )

/*************************************************************************
|*  SvObject::GetMemberInterface()
|*
|*  Beschreibung:
*************************************************************************/
IUnknown * SvObject::GetMemberInterface( const SvGlobalName & )
{
    return NULL;
}

/*************************************************************************
|*  SvObject::TestMemberObjRef()
|*
|*  Beschreibung:
*************************************************************************/
void SvObject::TestMemberObjRef( BOOL /*bFree*/ )
{
}

/*************************************************************************
|*  SvObject::TestMemberObjRef()
|*
|*  Beschreibung:
*************************************************************************/

#ifdef TEST_INVARIANT
void SvObject::TestMemberInvariant( BOOL /*bPrint*/ )
{
#ifdef DBG_UTIL
    if( !Owner() && pClient )
    {
        ByteString aTest( "\t\tpClient == " );
        aTest += ByteString::CreateFromInt32( (ULONG)pClient );
        DBG_TRACE( aTest.GetBuffer() );
    }
    if( Owner() && pService )
    {
        ByteString aTest( "\t\tpService == " );
        aTest += ByteString::CreateFromInt32( (ULONG)pService );
        DBG_TRACE( aTest.GetBuffer() );
    }
#endif
}
#endif

/*************************************************************************
|*    SvObject::SvObject()
|*
|*    Beschreibung
*************************************************************************/
SvObject::SvObject()
    : pObj        ( NULL ) // union mit pClient, pService
    , nExtCount   ( 0 )
{
}

/*************************************************************************
|*
|*    SvObject::~SvObject()
|*
|*    Beschreibung
|*    Ersterstellung    MM 05.06.94
|*    Letzte Aenderung  MM 05.06.94
|*
*************************************************************************/
SvObject::~SvObject()
{
}

/*************************************************************************
|*
|*    SvObject::ReleaseRef()
|*    SvObject::ReleaseExt()
|*
|*    Beschreibung
|*    Ersterstellung    MM 05.06.94
|*    Letzte Aenderung  MM 05.06.94
|*
*************************************************************************/
UINT32 SvObject::ReleaseRef()
{
#ifdef DBG_UTIL
    if( GetRefCount() == nExtCount )
    {
        ByteString aStr( "Internal RefCount underflow: Count == " );
        aStr += ByteString::CreateFromInt32( GetRefCount() );
        aStr += ", ExtCount == ";
        aStr += ByteString::CreateFromInt32( nExtCount );
        DBG_ERROR( aStr.GetBuffer() );
    }
#endif
    return SotObject::ReleaseRef();
}


UINT32 SvObject::ReleaseExt()
{
#ifdef DBG_UTIL
    if( nExtCount == 0 )
    { // wegen Fehler bei Fehlermeldung
        DBG_TRACE( "External RefCount underflow" );
    }
//    DBG_ASSERT( nExtCount != 0,
//                "External RefCount underflow" );
#endif
    if( nExtCount != 0 )
    {   // Niemals ausbauen! Schutz gegen !feindliche!
        // Applikationen.
        nExtCount--;
        return ReleaseRef();
    }
    return GetRefCount();
}



//========================================================================
void SvObject::MakeUnknown()
/* [Beschreibung]

    Klassen, die immer extern sind, aber nicht sofort <SvObject::Init>
    rufen, m"ussen diese Methode "uberladen.
    Darin muss das externe Objekt erzeugt und mit Init eingesetzt werden.
    Im Konstruktor muss das Objekt als extern gekennzeichnet werden.

    [Beispiel]

    void MyClass::MyClass()
    {
        SetExtern();
    }

    void MyClass::MakeUnknown()
    {
        CreateBindCtx( 0, &pObjI );
        Init( pObjI );
    }
*/
{
}



UINT32 SvObject::AddExtRef()
{
    ++nExtCount;
    return AddRef();
}


//=========================================================================
// Nicht die Superklasse rufen, wegen Umstellung So2 -> So3 & Sot
USHORT SvObject::FuzzyLock
(
    BOOL bLock,     /* TRUE, lock. FALSE, unlock. */
    BOOL bIntern,   /* TRUE, es handelt sich um einen internen Lock.
                       FALSE, der Lock kam von aussen (Ole2, Ipc2) */
    BOOL bClose     /* TRUE, Close aufrufen wenn letzte Lock */
)
/*  [Beschreibung]

    Erlaubte Parameterkombinationen:
    ( TRUE,  TRUE,  *     ) ->  interner Lock.
    ( FALSE, TRUE,  TRUE  ) ->  interner Unlock mit Close,
                                wenn LockCount() == 0
    ( TRUE,  FALSE, *     ) ->  externer Lock.
    ( FALSE, FALSE, TRUE  ) ->  externer Unlock mit Close,
                                wenn LockCount() == 0
    ( FALSE, FALSE, FALSE ) ->  externer Unlock

    F"ur !Owner() wird der Aufruf an das externe Objekt weitergeleitet.
    F"ur diese muss das <IOleItemContainer>-Interface zur Vef"ugung stehen.
    bIntern und bClose werden dann ignoriert.
    Wenn der LockCount auf 0 wechselt, wird <SvObject::DoClose>
    gerufen, wenn kein OwnerLock besteht.

    [Anmerkung]

*/
{
    SvObjectRef xHoldAlive( this );
    USHORT nRet;
    if( bLock )
    {
        if( bIntern )
            AddRef();
        else
            AddExtRef();
        nRet = ++nStrongLockCount;
    }
    else
    {
        nRet = --nStrongLockCount;
        if( bIntern )
            ReleaseRef();
        else
            ReleaseExt();
    }

    (void)bClose;
/*
    // i9662: leads to crashes if embedded object inside embedded object is connected
    // there seems to be no case where a Close() is necessary here -> workaround!
    if( !nRet && bClose && !nOwnerLockCount )
        DoClose();
*/
    return nRet;
}


/*************************************************************************
|*    void TestInSendMessage()
|*
|*    Beschreibung
*************************************************************************/
#if defined (_INC_WINDOWS) || defined (_WINDOWS_)
RECT GetSysRect( const Rectangle & rRect )
{
    RECT aRect;
    aRect.top    = (int)rRect.Top();
    aRect.left   = (int)rRect.Left();
    if( rRect.Right() == RECT_EMPTY )
        aRect.right  = aRect.left;
    else
        aRect.right  = (int)(rRect.Right() +1);
    if( rRect.Bottom() == RECT_EMPTY )
        aRect.bottom = aRect.top;
    else
        aRect.bottom = (int)(rRect.Bottom() +1);
    return aRect;
}
Rectangle GetSvRect( const RECT & rRect )
{
    Rectangle aRect;
    aRect.Top()     = rRect.top;
    aRect.Left()    = rRect.left;
    if( rRect.right != rRect.left )
        aRect.Right()   = rRect.right -1;
    if( rRect.bottom != rRect.top )
        aRect.Bottom()  = rRect.bottom -1;
    return aRect;
}
#endif

/*************************************************************************
|*    void TestInSendMessage()
|*
|*    Beschreibung
*************************************************************************/
void TestInSendMessage()
{
}


IMPL_PTRHINT(SvObjectDyingHint, SvObject);


