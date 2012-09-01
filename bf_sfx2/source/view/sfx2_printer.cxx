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

#include <bf_svtools/itemset.hxx>
#include <bf_svtools/svarray.hxx>

#include "bf_sfx2/printer.hxx"
namespace binfilter {

//--------------------------------------------------------------------

// struct SfxPrinter_Impl ------------------------------------------------

/*N*/ struct SfxPrinter_Impl
/*N*/ {
/*N*/   BOOL                mbAll;
/*N*/   BOOL                mbSelection;
/*N*/   BOOL                mbFromTo;
/*N*/   BOOL                mbRange;
/*N*/
/*N*/   SfxPrinter_Impl() :
/*N*/       mbAll       ( TRUE ),
/*N*/       mbSelection ( TRUE ),
/*N*/       mbFromTo    ( TRUE ),
/*N*/       mbRange     ( TRUE ) {}
/*N*/ };

//--------------------------------------------------------------------

/*N*/ SfxFont::SfxFont( const FontFamily eFontFamily, const rtl::OUString& aFontName,
/*N*/                 const FontPitch eFontPitch, const CharSet eFontCharSet ):
/*N*/   aName( aFontName ),
/*N*/   eFamily( eFontFamily ),
/*N*/   ePitch( eFontPitch ),
/*N*/   eCharSet( eFontCharSet )
/*N*/ {
/*N*/ }

// class SfxPrinter ------------------------------------------------------

/*N*/ SfxPrinter* SfxPrinter::Create( SvStream& rStream, SfxItemSet* pOptions )

/*  [Beschreibung]

    Erzeugt einen <SfxPrinter> aus dem Stream. Geladen wird genaugenommen
    nur ein JobSetup. Falls ein solcher Drucker auf dem System nicht
    verf"augbar ist, wird das Original als Orig-JobSetup gemerkt und
    ein "anhlicher exisitierender Drucker genommen.

    Die 'pOptions' werden in den erzeugten SfxPrinter "ubernommen,
    der Returnwert geh"ort dem Caller.
*/

/*N*/ {
/*N*/   // JobSetup laden
/*N*/   JobSetup aFileJobSetup;
/*N*/   rStream >> aFileJobSetup;
/*N*/
/*N*/   // Drucker erzeugen
/*N*/   SfxPrinter *pPrinter = new SfxPrinter( pOptions, aFileJobSetup );
/*N*/   return pPrinter;
/*N*/ }

//--------------------------------------------------------------------

/*N*/ SfxPrinter::SfxPrinter( SfxItemSet* pTheOptions ) :

/*  [Beschreibung]

    Dieser Ctor erzeugt einen Standard-Drucker.
*/

/*N*/   pOptions( pTheOptions ),
/*N*/   bKnown(sal_True)

/*N*/ {
/*N*/   pImpl = new SfxPrinter_Impl;
/*N*/ }

//--------------------------------------------------------------------

/*N*/ SfxPrinter::SfxPrinter( SfxItemSet* pTheOptions,
/*N*/                       const JobSetup& rTheOrigJobSetup ) :

/*N*/   Printer         ( rTheOrigJobSetup.GetPrinterName() ),
/*N*/   pOptions        ( pTheOptions )

/*N*/ {
/*N*/   pImpl = new SfxPrinter_Impl;
/*N*/   bKnown = GetName() == rTheOrigJobSetup.GetPrinterName();
/*N*/
/*N*/   if ( bKnown )
        {
/*N*/       SetJobSetup( rTheOrigJobSetup );
        }

        // --> Use old XPrinter emulation. rTheOrigJobSetup
        // already has this setting (see SfxPrinter::Create()).
        JobSetup aJobSetup( GetJobSetup() );
        aJobSetup.SetValue( rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "StrictSO52Compatibility" ) ),
                            rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "true" ) ) );
        SetJobSetup( aJobSetup );
/*N*/ }

//--------------------------------------------------------------------

/*N*/ SfxPrinter::SfxPrinter( SfxItemSet* pTheOptions,
/*N*/                       const rtl::OUString& rPrinterName ) :
/*N*/
/*N*/   Printer         ( rPrinterName ),
/*N*/   pOptions        ( pTheOptions ),
/*N*/   bKnown          ( GetName() == rPrinterName )
/*N*/
/*N*/ {
/*N*/   pImpl = new SfxPrinter_Impl;
/*N*/ }

//--------------------------------------------------------------------

/*N*/ SfxPrinter::~SfxPrinter()
/*N*/ {
/*N*/   delete pOptions;
/*N*/   delete pImpl;
/*N*/ }

//--------------------------------------------------------------------

/*N*/ void SfxPrinter::SetOptions( const SfxItemSet &rNewOptions )
/*N*/ {
/*N*/   pOptions->Set(rNewOptions);
/*N*/ }

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
