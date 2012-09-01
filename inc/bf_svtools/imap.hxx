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

#ifndef _IMAP_HXX
#define _IMAP_HXX

#include <bf_svtools/bf_solar.h>


#include <bf_tools/string.hxx>
#include <bf_tools/list.hxx>
#include <tools/stream.hxx>

class Point;
class Rectangle;
class Size;
class Fraction;

namespace binfilter
{

class IMapObject;

class  ImageMap
{
    List                maList;
    String              aName;

protected:

    // Binaer laden
    void                ImpReadImageMap( SvStream& rIStm, USHORT nCount, const String& );

public:

    TYPEINFO();

                        ImageMap() {};
                        ImageMap( const ImageMap& rImageMap );

                        // Der Dtor gibt den intern belegten
                        // Speicher wieder frei;
                        //  alle IMapObjekte werden im Dtor zerstoert;
    virtual             ~ImageMap();

    // Zuweisungsoperator
    ImageMap&           operator=( const ImageMap& rImageMap );

    // Vergleichsoperator (es wird alles auf Gleichheit geprueft)
    BOOL                operator==( const ImageMap& rImageMap );
    BOOL                operator!=( const ImageMap& rImageMap );

    // In die Map wird ein neues IMap-Obkekt ans Ende eingefuegt
    void                InsertIMapObject( const IMapObject& rIMapObject );

    // Zugriff auf einzelne IMapObjekte; die Objekte
    // duerfen von aussen _nicht_ zerstoert werden
    IMapObject*         GetFirstIMapObject() { return (IMapObject*) maList.First(); }
    IMapObject*         GetNextIMapObject() { return (IMapObject*) maList.Next(); }
    IMapObject*         GetLastIMapObject() { return (IMapObject*) maList.Last(); }
    IMapObject*         GetPrevIMapObject() { return (IMapObject*) maList.Prev(); }
    IMapObject*         GetIMapObject( USHORT nPos ) const { return (IMapObject*) maList.GetObject( nPos ); }

    // Gibt die Gesamtanzahl der IMap-Objekte zurueck
    UINT16              GetIMapObjectCount() const { return (UINT16) maList.Count(); }

    // Loescht alle internen Objekte
    void                ClearImageMap();

    // liefert / setzt den Namen der ImageMap
    const String&       GetName() const { return aName; }
    void                SetName( const String& rName ) { aName = rName; }

    // skaliert alle Objekte der ImageMap entpr. dem uebergebenen Faktor
    void                Scale( const Fraction& rFractX, const Fraction& rFracY );

    // Im-/Export
    void                Read( SvStream& rIStm, const String& rBaseURL );
};

class IMapCompat
{
    SvStream*       pRWStm;
    ULONG           nCompatPos;
    ULONG           nTotalSize;
    USHORT          nStmMode;

                    IMapCompat() {}
                    IMapCompat( const IMapCompat& ) {}
    IMapCompat&     operator=( const IMapCompat& ) { return *this; }
    BOOL            operator==( const IMapCompat& ) { return FALSE; }

public:

                    IMapCompat( SvStream& rStm, const USHORT nStreamMode );
                    ~IMapCompat();
};

}

#endif // _IMAP_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
