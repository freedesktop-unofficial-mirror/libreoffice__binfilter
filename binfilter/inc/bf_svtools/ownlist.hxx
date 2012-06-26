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

#ifndef _OWNLIST_HXX
#define _OWNLIST_HXX

#include "bf_svtools/svtdllapi.h"

#include <tools/stream.hxx>
#include <bf_tools/ownlist.hxx>

#include <com/sun/star/uno/Sequence.hxx>

namespace com { namespace sun { namespace star {
    namespace beans {
        struct PropertyValue;
    }
}}}

namespace binfilter
{


//=========================================================================
class SvCommand
/*  [Beschreibung]

    Enth"alt einen String, welcher das Kommando angibt und eine weiteren
    String, der das Argument des Kommandos bildet. W"urde solch ein
    Kommando "uber die Kommandozeile angegeben werden, s"ahe es wie folgt
    aus: Kommando = Argument.
*/
{
    String  aCommand;
    String  aArgument;
public:
                    SvCommand() {}
                    SvCommand( const String & rCommand, const String & rArg )
                    {
                        aCommand = rCommand;
                        aArgument = rArg;
                    }
    const String & GetCommand() const { return aCommand; }
    const String & GetArgument() const { return aArgument; }

    friend SvStream& operator >> ( SvStream& rStm, SvCommand & rThis )
                    {
                        rThis.aCommand = rStm.ReadUniOrByteString( osl_getThreadTextEncoding() );
                        rThis.aArgument = rStm.ReadUniOrByteString( osl_getThreadTextEncoding() );
                        return rStm;
                    }
    friend SvStream& operator << ( SvStream& rStm, const SvCommand & rThis )
                    {
                        rStm.WriteUniOrByteString( rThis.aCommand, osl_getThreadTextEncoding() );
                        rStm.WriteUniOrByteString( rThis.aArgument, osl_getThreadTextEncoding() );
                        return rStm;
                    }
};

//=========================================================================
class SvCommandList
/*  [Beschreibung]

    Die Liste enth"alt Objekte vom Typ SvCommand. Wird ein Objekt
    eingef"ugt, dann wird es kopiert und das neue Objekt wird
    in die Liste gestellt.
*/
{
                    PRV_SV_DECL_OWNER_LIST(SvCommandList,SvCommand);
    SvCommand &     Append( const String & rCommand, const String & rArg );

     friend SvStream& operator >> ( SvStream& rStm, SvCommandList & );
     friend SvStream& operator << ( SvStream&, const SvCommandList & );
};

}

#endif // _OWNLIST_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
