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

#ifndef _SC_XMLCHANGETRACKINGEXPORTHELPER_HXX
#define _SC_XMLCHANGETRACKINGEXPORTHELPER_HXX

#include <bf_xmloff/xmltoken.hxx>
#ifndef __SGI_STL_LIST
#include <list>
#endif
#include <com/sun/star/text/XText.hpp>
#include <rtl/ustrbuf.hxx>

class DateTime;

namespace binfilter {

class String;
class ScChangeAction;
class ScChangeTrack;
class ScXMLExport;
class ScBaseCell;
class ScChangeActionDel;
class ScBigRange;
class ScEditEngineTextObj;
class ScChangeActionTable;

typedef std::list<ScChangeActionDel*> ScMyDeletionsList;

class ScChangeTrackingExportHelper
{
    ScXMLExport&    rExport;

    ScChangeTrack*  pChangeTrack;
    ScEditEngineTextObj* pEditTextObj;
    ScChangeActionTable* pDependings;
    ::rtl::OUString sChangeIDPrefix;
    ::com::sun::star::uno::Reference< ::com::sun::star::text::XText>    xText;

    ::rtl::OUString GetChangeID(const sal_uInt32 nActionNumber);
    void GetAcceptanceState(const ScChangeAction* pAction);

    void WriteBigRange(const ScBigRange& rBigRange, xmloff::token::XMLTokenEnum aName);
    void WriteChangeInfo(const ScChangeAction* pAction);
    void WriteGenerated(const ScChangeAction* pDependAction);
    void WriteDeleted(const ScChangeAction* pDependAction);
    void WriteDepending(const ScChangeAction* pDependAction);
    void WriteDependings(ScChangeAction* pAction);

    void WriteEmptyCell();
    void SetValueAttributes(const double& fValue, const String& sValue);
    void WriteValueCell(const ScBaseCell* pCell, const String& sValue);
    void WriteStringCell(const ScBaseCell* pCell);
    void WriteEditCell(const ScBaseCell* pCell);
    void WriteFormulaCell(const ScBaseCell* pCell, const String& sValue);
    void WriteCell(const ScBaseCell* pCell, const String& sValue);

    void WriteContentChange(ScChangeAction* pAction);
    void AddInsertionAttributes(const ScChangeAction* pAction);
    void WriteInsertion(ScChangeAction* pAction);
    void AddDeletionAttributes(const ScChangeActionDel* pAction, const ScChangeActionDel* pLastAction);
    void WriteDeletionCells(ScChangeActionDel* pAction);
    void WriteCutOffs(const ScChangeActionDel* pAction);
    void WriteDeletion(ScChangeAction* pAction);
    void WriteMovement(ScChangeAction* pAction);
    void WriteRejection(ScChangeAction* pAction);

    void CollectCellAutoStyles(const ScBaseCell* pBaseCell);
    void CollectActionAutoStyles(ScChangeAction* pAction);
    void WorkWithChangeAction(ScChangeAction* pAction);
public:
    ScChangeTrackingExportHelper(ScXMLExport& rExport);
    ~ScChangeTrackingExportHelper();

    void CollectAutoStyles();
    void CollectAndWriteChanges();
};

} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
