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

#include <tools/debug.hxx>

#include <com/sun/star/drawing/PolyPolygonBezierCoords.hpp>
#include <com/sun/star/drawing/LineDash.hpp>
#include <com/sun/star/awt/Gradient.hpp>
#include <com/sun/star/drawing/Hatch.hpp>
#include <com/sun/star/io/XActiveDataSource.hpp>

#include <bf_sfx2/docfile.hxx>
#include <bf_xmloff/xmluconv.hxx>

#include "bf_xmloff/xmlnmspe.hxx"
#include "bf_xmloff/nmspmap.hxx"
#include "bf_xmloff/xmlkywd.hxx"
#include "bf_xmloff/DashStyle.hxx"
#include "bf_xmloff/GradientStyle.hxx"
#include "bf_xmloff/HatchStyle.hxx"
#include "bf_xmloff/ImageStyle.hxx"
#include "bf_xmloff/MarkerStyle.hxx"

#include <com/sun/star/container/XNameContainer.hpp>
#include <unotools/streamwrap.hxx>

#include "xmlgrhlp.hxx"
#include "xmlxtexp.hxx"

#include <legacysmgr/legacy_binfilters_smgr.hxx>

namespace binfilter {
using namespace ::com::sun::star;
using namespace ::com::sun::star::container;
using namespace ::com::sun::star::document;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::awt;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::xml::sax;
using namespace ::rtl;
using namespace cppu;

/*N*/ class SvxXMLTableEntryExporter
/*N*/ {
/*N*/ public:
/*N*/   SvxXMLTableEntryExporter( SvXMLExport& rExport ) : mrExport( rExport ) {}
/*N*/   virtual ~SvxXMLTableEntryExporter();
/*N*/
/*N*/   virtual void exportEntry( const OUString& rStrName, const Any& rValue ) = 0;
/*N*/
/*N*/ protected:
/*N*/   SvXMLExport& mrExport;
/*N*/ };
/*N*/
/*N*/ ///////////////////////////////////////////////////////////////////////
/*N*/
/*N*/ SvxXMLTableEntryExporter::~SvxXMLTableEntryExporter()
/*N*/ {
/*N*/ }
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
