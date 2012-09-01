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

#ifndef _FMSEARCH_HXX
#define _FMSEARCH_HXX

#include <com/sun/star/sdbc/XResultSet.hpp>

#define _SVSTDARR_STRINGSDTOR
#include <bf_svtools/svstdarr.hxx>

#include <vcl/dialog.hxx>

#include <vcl/button.hxx>

#include <vcl/fixed.hxx>

#include <vcl/edit.hxx>

#include <vcl/combobox.hxx>

#include <vcl/lstbox.hxx>

#include <tools/link.hxx>

#include <comphelper/stl_types.hxx>

namespace com { namespace sun { namespace star {
    namespace util {
        class XNumberFormatsSupplier;
    }
}}}

namespace binfilter {

// ===================================================================================================
// moegliche Rueckgabewerte fuer den Found-Handler
#define FM_SEARCH_GETFOCUS_ASYNC    0x0001
    // setzt den Fokus auf den Dialog nicht sofort nach dem Aufruf des Found-Handlers, sondern postet sich selber dafuer
    // ein Ereignis

#define MAX_HISTORY_ENTRIES     50

// ===================================================================================================
// Hilfsmethoden

    // check if the control has one of the interfaces we can use for searching
    // *pCurrentText will be filled with the current text of the control (as used when searching this control)

// ===================================================================================================
// Hilfsstrukturen

struct FmFoundRecordInformation
{
    ::com::sun::star::uno::Any      aPosition;  // Bookmark des Datensatzes, in dem der Text gefunden wurde
    sal_Int16       nFieldPos;  // dito : die relative Position der Spalte (im Stringnamen in Feldliste im Constructor)
    sal_Int16       nContext;   // Kontext, in dem gesucht und gefunden wurde (falls die aktuelle Suche verschiedene solche kennt)
};

DECLARE_STL_VECTOR( ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface>, InterfaceArray);
    // TODO : use stl

// ===================================================================================================
// = struct FmSearchContext - Informationen fuer Suche in verschiedenen Kontexten
// ===================================================================================================

struct FmSearchContext
{
    // [in]
    sal_Int16                   nContext;       // die Nummer des Kontextes
    // [out]
    ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XResultSet>           xCursor;        // der Iterator fuer diesen Kontext
    String                  strUsedFields;  // eine Liste von durch ';' getrennten Feldnamen
    InterfaceArray          arrFields;      // die korrespondierenden Text-Interfaces fuer die Felder in strUsedFields
    String                  sFieldDisplayNames;     // if not empty : names to be displayed for the searchable fields (must have the same token count as strUsedFields !)
};

// ===================================================================================================
// = class FmSearchDialog - Dialog fuer Suchen in Formularen/Tabellen
// ===================================================================================================

namespace svxform {
    class FmSearchConfigItem;
}

class FmSearchEngine;
struct FmSearchProgress;


}//end of namespace binfilter
#endif // _FMSEARCH_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
