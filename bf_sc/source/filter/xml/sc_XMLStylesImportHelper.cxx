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

#ifdef _MSC_VER
#pragma hdrstop
#endif


#include "XMLStylesImportHelper.hxx"
#include "xmlimprt.hxx"

#include <tools/debug.hxx>

#include <com/sun/star/util/NumberFormat.hpp>
namespace binfilter {

using namespace ::com::sun::star;

void ScMyStyleNumberFormats::AddStyleNumberFormat(const ::rtl::OUString& rStyleName, const sal_Int32 nNumberFormat)
{
    ScMyStyleNumberFormat aFormat(rStyleName, nNumberFormat);
    aSet.insert(aFormat);
}

sal_Int32 ScMyStyleNumberFormats::GetStyleNumberFormat(const ::rtl::OUString& rStyleName)
{
    ScMyStyleNumberFormat aStyleNumberFormat(rStyleName);
    ScMyStyleNumberFormatSet::iterator aItr = aSet.find(aStyleNumberFormat);
    if (aItr == aSet.end())
        return -1;
    else
        return aItr->nNumberFormat;
}

ScMyStyleRanges::ScMyStyleRanges()
    :
    pTextList(NULL),
    pNumberList(NULL),
    pTimeList(NULL),
    pDateTimeList(NULL),
    pPercentList(NULL),
    pLogicalList(NULL),
    pUndefinedList(NULL),
    pCurrencyList(NULL)
{
}

ScMyStyleRanges::~ScMyStyleRanges()
{
    if (pTextList)
        delete pTextList;
    if (pNumberList)
        delete pNumberList;
    if (pTimeList)
        delete pTimeList;
    if (pDateTimeList)
        delete pDateTimeList;
    if (pPercentList)
        delete pPercentList;
    if (pLogicalList)
        delete pLogicalList;
    if (pUndefinedList)
        delete pUndefinedList;
    if (pCurrencyList)
        delete pCurrencyList;
}

void ScMyStyleRanges::AddRange(const ScRange& rRange, ScRangeList* pList,
    const ::rtl::OUString* pStyleName, const sal_Int16 nType,
    ScXMLImport& rImport, const sal_uInt32 nMaxRanges)
{
    pList->Join(rRange);
    DBG_ASSERT(nMaxRanges > 0, "MaxRanges to less");
    if (pList->Count() > nMaxRanges)
    {
        sal_Int32 nCount(pList->Count());
        ScRange* pRange = NULL;
        for (sal_Int32 i = 0; i < nCount; i++)
        {
            pRange = pList->GetObject(i);
            if (pRange && (pRange->aEnd.Row() + 1 < rRange.aStart.Row()))
            {
                rImport.SetStyleToRange(*pRange, pStyleName, nType, NULL);
                delete pRange;
                pRange = NULL;
                pList->Remove(i);
            }
        }
    }
}

void ScMyStyleRanges::AddCurrencyRange(const ScRange& rRange, ScRangeListRef xList,
    const ::rtl::OUString* pStyleName, const ::rtl::OUString* pCurrency,
    ScXMLImport& rImport, const sal_uInt32 nMaxRanges)
{
    xList->Join(rRange);
    DBG_ASSERT(nMaxRanges > 0, "MaxRanges to less");
    if (xList->Count() > nMaxRanges)
    {
        sal_Int32 nCount(xList->Count());
        ScRange* pRange = NULL;
        for (sal_Int32 i = 0; i < nCount; i++)
        {
            pRange = xList->GetObject(i);
            if (pRange && (pRange->aEnd.Row() + 1 < rRange.aStart.Row()))
            {
                rImport.SetStyleToRange(*pRange, pStyleName, util::NumberFormat::CURRENCY, pCurrency);
                delete pRange;
                pRange = NULL;
                xList->Remove(i);
            }
        }
    }
}

void ScMyStyleRanges::AddRange(const ScRange& rRange,
    const ::rtl::OUString* pStyleName, const sal_Int16 nType,
    ScXMLImport& rImport, const sal_uInt32 nMaxRanges)
{
    switch (nType)
    {
        case util::NumberFormat::NUMBER:
        {
            if (!pNumberList)
                pNumberList = new ScRangeList();
            AddRange(rRange, pNumberList, pStyleName, nType, rImport, nMaxRanges);
        }
        break;
        case util::NumberFormat::TEXT:
        {
            if (!pTextList)
                pTextList = new ScRangeList();
            AddRange(rRange, pTextList, pStyleName, nType, rImport, nMaxRanges);
        }
        break;
        case util::NumberFormat::TIME:
        {
            if (!pTimeList)
                pTimeList = new ScRangeList();
            AddRange(rRange, pTimeList, pStyleName, nType, rImport, nMaxRanges);
        }
        break;
        case util::NumberFormat::DATETIME:
        {
            if (!pDateTimeList)
                pDateTimeList = new ScRangeList();
            AddRange(rRange, pDateTimeList, pStyleName, nType, rImport, nMaxRanges);
        }
        break;
        case util::NumberFormat::PERCENT:
        {
            if (!pPercentList)
                pPercentList = new ScRangeList();
            AddRange(rRange, pPercentList, pStyleName, nType, rImport, nMaxRanges);
        }
        break;
        case util::NumberFormat::LOGICAL:
        {
            if (!pLogicalList)
                pLogicalList = new ScRangeList();
            AddRange(rRange, pLogicalList, pStyleName, nType, rImport, nMaxRanges);
        }
        break;
        case util::NumberFormat::UNDEFINED:
        {
            if (!pUndefinedList)
                pUndefinedList = new ScRangeList();
            AddRange(rRange, pUndefinedList, pStyleName, nType, rImport, nMaxRanges);
        }
        break;
        default:
        {
            OSL_FAIL("wrong type");
        }
        break;
    }
}

void ScMyStyleRanges::AddCurrencyRange(const ScRange& rRange,
    const ::rtl::OUString* pStyleName, const ::rtl::OUString* pCurrency,
    ScXMLImport& rImport, const sal_uInt32 nMaxRanges)
{
    if (!pCurrencyList)
        pCurrencyList = new ScMyCurrencyStylesSet();
    ScMyCurrencyStyle aStyle;
    if (pCurrency)
        aStyle.sCurrency = *pCurrency;
    ScMyCurrencyStylesSet::iterator aItr = pCurrencyList->find(aStyle);
    if (aItr == pCurrencyList->end())
    {
        std::pair<ScMyCurrencyStylesSet::iterator, bool> aPair = pCurrencyList->insert(aStyle);
        if (aPair.second)
        {
            aItr = aPair.first;
            AddCurrencyRange(rRange, aItr->xRanges, pStyleName, pCurrency, rImport, nMaxRanges);
        }
    }
    else
        aItr->xRanges->Join(rRange);
}

void ScMyStyleRanges::InsertColRow(const ScRange& rRange, const sal_Int16 nDx, const sal_Int16 nDy,
        const sal_Int16 nDz, ScDocument* pDoc)
{
    UpdateRefMode aRefMode = URM_INSDEL;
    if (pNumberList)
        pNumberList->UpdateReference(aRefMode, pDoc, rRange, nDx, nDy, nDz);
    if (pTextList)
        pTextList->UpdateReference(aRefMode, pDoc, rRange, nDx, nDy, nDz);
    if (pTimeList)
        pTimeList->UpdateReference(aRefMode, pDoc, rRange, nDx, nDy, nDz);
    if (pDateTimeList)
        pDateTimeList->UpdateReference(aRefMode, pDoc, rRange, nDx, nDy, nDz);
    if (pPercentList)
        pPercentList->UpdateReference(aRefMode, pDoc, rRange, nDx, nDy, nDz);
    if (pLogicalList)
        pLogicalList->UpdateReference(aRefMode, pDoc, rRange, nDx, nDy, nDz);
    if (pUndefinedList)
        pUndefinedList->UpdateReference(aRefMode, pDoc, rRange, nDx, nDy, nDz);
    if (pCurrencyList)
    {
        ScMyCurrencyStylesSet::iterator aItr = pCurrencyList->begin();
        while (aItr != pCurrencyList->end())
        {
            aItr->xRanges->UpdateReference(aRefMode, pDoc, rRange, nDx, nDy, nDz);
            ++aItr;
        }
    }
}

void ScMyStyleRanges::InsertRow(const sal_Int32 nRow, const sal_Int32 nTab, ScDocument* pDoc)
{
    InsertColRow(ScRange(0, static_cast<sal_uInt16>(nRow), static_cast<sal_uInt16>(nTab),
        MAXCOL, MAXROW, static_cast<sal_uInt16>(nTab)), 0, 1, 0, pDoc);
}

void ScMyStyleRanges::InsertCol(const sal_Int32 nCol, const sal_Int32 nTab, ScDocument* pDoc)
{
    InsertColRow(ScRange(static_cast<sal_uInt16>(nCol), 0, static_cast<sal_uInt16>(nTab),
        MAXCOL, MAXROW, static_cast<sal_uInt16>(nTab)), 1, 0, 0, pDoc);
}

void ScMyStyleRanges::SetStylesToRanges(ScRangeList* pList,
    const ::rtl::OUString* pStyleName, const sal_Int16 nCellType,
    const ::rtl::OUString* pCurrency, ScXMLImport& rImport)
{
    sal_Int32 nCount(pList->Count());
    for (sal_Int32 i = 0; i < nCount; i++)
        rImport.SetStyleToRange(*pList->GetObject(i), pStyleName, nCellType, pCurrency);
}

void ScMyStyleRanges::SetStylesToRanges(ScRangeListRef xList,
    const ::rtl::OUString* pStyleName, const sal_Int16 nCellType,
    const ::rtl::OUString* pCurrency, ScXMLImport& rImport)
{
    sal_Int32 nCount(xList->Count());
    for (sal_Int32 i = 0; i < nCount; i++)
        rImport.SetStyleToRange(*xList->GetObject(i), pStyleName, nCellType, pCurrency);
}

void ScMyStyleRanges::SetStylesToRanges(const ::rtl::OUString* pStyleName, ScXMLImport& rImport)
{
    if (pNumberList)
        SetStylesToRanges(pNumberList, pStyleName, util::NumberFormat::NUMBER, NULL, rImport);
    if (pTextList)
        SetStylesToRanges(pTextList, pStyleName, util::NumberFormat::TEXT, NULL, rImport);
    if (pTimeList)
        SetStylesToRanges(pTimeList, pStyleName, util::NumberFormat::TIME, NULL, rImport);
    if (pDateTimeList)
        SetStylesToRanges(pDateTimeList, pStyleName, util::NumberFormat::DATETIME, NULL, rImport);
    if (pPercentList)
        SetStylesToRanges(pPercentList, pStyleName, util::NumberFormat::PERCENT, NULL, rImport);
    if (pLogicalList)
        SetStylesToRanges(pLogicalList, pStyleName, util::NumberFormat::LOGICAL, NULL, rImport);
    if (pUndefinedList)
        SetStylesToRanges(pUndefinedList, pStyleName, util::NumberFormat::UNDEFINED, NULL, rImport);
    if (pCurrencyList)
    {
        ScMyCurrencyStylesSet::iterator aItr = pCurrencyList->begin();
        while (aItr != pCurrencyList->end())
        {
            SetStylesToRanges(aItr->xRanges, pStyleName, util::NumberFormat::CURRENCY, &aItr->sCurrency, rImport);
            ++aItr;
        }
    }
}

//----------------------------------------------------------------------------

ScMyStylesImportHelper::ScMyStylesImportHelper(ScXMLImport& rTempImport)
    :
    aCellStyles(),
    aColDefaultStyles(),
    rImport(rTempImport),
    pStyleName(NULL),
    pPrevStyleName(NULL),
    pCurrency(NULL),
    pPrevCurrency(NULL),
    nMaxRanges(0),
    bPrevRangeAdded(sal_True)
{
    aRowDefaultStyle = aCellStyles.end();
}

ScMyStylesImportHelper::~ScMyStylesImportHelper()
{
    if (pPrevStyleName)
        delete pPrevStyleName;
    if (pPrevCurrency)
        delete pPrevCurrency;
    if (pStyleName)
        delete pStyleName;
    if (pCurrency)
        delete pCurrency;
}

void ScMyStylesImportHelper::ResetAttributes()
{
    if (pPrevStyleName)
        delete pPrevStyleName;
    if (pPrevCurrency)
        delete pPrevCurrency;
    pPrevStyleName = pStyleName;
    pPrevCurrency = pCurrency;
    nPrevCellType = nCellType;
    pStyleName = NULL;
    pCurrency = NULL;
    nCellType = 0;
}

ScMyStylesSet::iterator ScMyStylesImportHelper::GetIterator(const ::rtl::OUString* pInStyleName)
{
    ScMyStyle aStyle;
    if (pInStyleName)
        aStyle.sStyleName = *pInStyleName;
    else
        OSL_FAIL("here is no stylename given");
    ScMyStylesSet::iterator aItr = aCellStyles.find(aStyle);
    if (aItr == aCellStyles.end())
    {
        std::pair<ScMyStylesSet::iterator, bool> aPair = aCellStyles.insert(aStyle);
        if (aPair.second)
            aItr = aPair.first;
        else
        {
            OSL_FAIL("not possible to insert style");
            return aCellStyles.end();
        }
    }
    return aItr;
}

void ScMyStylesImportHelper::AddDefaultRange(const ScRange& rRange)
{
    DBG_ASSERT(aRowDefaultStyle != aCellStyles.end(), "no row default style");
    if (!aRowDefaultStyle->sStyleName.getLength())
    {
        sal_uInt32 nStartCol(rRange.aStart.Col());
        sal_uInt32 nEndCol(rRange.aEnd.Col());
        if (aColDefaultStyles.size() > nStartCol)
        {
            ScMyStylesSet::iterator aPrevItr = aColDefaultStyles[nStartCol];
            DBG_ASSERT(aColDefaultStyles.size() > nEndCol, "to much columns");
            for (sal_uInt32 i = nStartCol + 1; (i <= nEndCol) && (i < aColDefaultStyles.size()); i++)
            {
                if (aPrevItr != aColDefaultStyles[i])
                {
                    DBG_ASSERT(aPrevItr != aCellStyles.end(), "no column default style");
                    ScRange aRange(rRange);
                    aRange.aStart.SetCol(static_cast<sal_uInt16>(nStartCol));
                    aRange.aEnd.SetCol(static_cast<sal_uInt16>(i - 1));
                    if (pPrevStyleName)
                        delete pPrevStyleName;
                    pPrevStyleName = new ::rtl::OUString(aPrevItr->sStyleName);
                    AddSingleRange(aRange);
                    nStartCol = i;
                    aPrevItr = aColDefaultStyles[i];
                }
            }
            if (aPrevItr != aCellStyles.end())
            {
                ScRange aRange(rRange);
                aRange.aStart.SetCol(static_cast<sal_uInt16>(nStartCol));
                if (pPrevStyleName)
                    delete pPrevStyleName;
                pPrevStyleName = new ::rtl::OUString(aPrevItr->sStyleName);
                AddSingleRange(aRange);
            }
            else
                DBG_ERRORFILE("no column default style");
        }
        else
            DBG_ERRORFILE("to much columns");
    }
    else
    {
        if (pPrevStyleName)
            delete pPrevStyleName;
        pPrevStyleName = new ::rtl::OUString(aRowDefaultStyle->sStyleName);
        AddSingleRange(rRange);
    }
}

void ScMyStylesImportHelper::AddSingleRange(const ScRange& rRange)
{
    if (nMaxRanges == 0)
        nMaxRanges = aColDefaultStyles.size();
    ScMyStylesSet::iterator aItr = GetIterator(pPrevStyleName);
    if (aItr != aCellStyles.end())
    {
        if (nPrevCellType != util::NumberFormat::CURRENCY)
            aItr->xRanges->AddRange(rRange, pPrevStyleName, nPrevCellType,
                rImport, nMaxRanges);
        else
            aItr->xRanges->AddCurrencyRange(rRange, pPrevStyleName, pPrevCurrency,
                rImport, nMaxRanges);
    }
}

void ScMyStylesImportHelper::AddRange()
{
    if (pPrevStyleName && pPrevStyleName->getLength())
        AddSingleRange(aPrevRange);
    else
        AddDefaultRange(aPrevRange);
    ResetAttributes();
}

void ScMyStylesImportHelper::AddColumnStyle(const ::rtl::OUString& sStyleName, const sal_Int32 nColumn, const sal_Int32 nRepeat)
{
    DBG_ASSERT(static_cast<sal_uInt32>(nColumn) == aColDefaultStyles.size(), "some columns are absent");
    (void)nColumn;
    ScMyStylesSet::iterator aItr = GetIterator(&sStyleName);
    DBG_ASSERT(aItr != aCellStyles.end(), "no column default style");
    for (sal_Int32 i = 0; i < nRepeat; i++)
        aColDefaultStyles.push_back(aItr);
}

void ScMyStylesImportHelper::SetRowStyle(const ::rtl::OUString& sStyleName)
{
    aRowDefaultStyle = GetIterator(&sStyleName);
}

void ScMyStylesImportHelper::SetAttributes(::rtl::OUString* pInStyleName,
    ::rtl::OUString* pInCurrency, const sal_Int16 nInCellType)
{
    if (pStyleName)
        delete pStyleName;
    if (pCurrency)
        delete pCurrency;
    pStyleName = pInStyleName;
    pCurrency = pInCurrency;
    nCellType = nInCellType;
}

void ScMyStylesImportHelper::AddRange(const ScRange& rRange)
{
    if (!bPrevRangeAdded)
    {
        sal_Bool bAddRange(sal_False);
        if (nCellType == nPrevCellType &&
            IsEqual(pStyleName, pPrevStyleName) &&
            IsEqual(pCurrency, pPrevCurrency))
        {
            if (rRange.aStart.Row() == aPrevRange.aStart.Row())
            {
                if (rRange.aEnd.Row() == aPrevRange.aEnd.Row())
                {
                    DBG_ASSERT(aPrevRange.aEnd.Col() + 1 == rRange.aStart.Col(), "something wents wrong");
                    aPrevRange.aEnd.SetCol(rRange.aEnd.Col());
                }
                else
                    bAddRange = sal_True;
            }
            else
            {
                if (rRange.aStart.Col() == aPrevRange.aStart.Col() &&
                    rRange.aEnd.Col() == aPrevRange.aEnd.Col())
                {
                    DBG_ASSERT(aPrevRange.aEnd.Row() + 1 == rRange.aStart.Row(), "something wents wrong");
                    aPrevRange.aEnd.SetRow(rRange.aEnd.Row());
                }
                else
                    bAddRange = sal_True;
            }
        }
        else
            bAddRange = sal_True;
        if (bAddRange)
        {
            AddRange();
            aPrevRange = rRange;
        }
    }
    else
    {
        aPrevRange = rRange;
        ResetAttributes();
        bPrevRangeAdded = sal_False;
    }
}

void ScMyStylesImportHelper::AddCell(const ::com::sun::star::table::CellAddress& rAddress)
{
    ScAddress aScAddress( static_cast<USHORT>(rAddress.Column), static_cast<USHORT>(rAddress.Row), rAddress.Sheet );
    ScRange aScRange( aScAddress, aScAddress );
    AddRange(aScRange);
}

void ScMyStylesImportHelper::InsertRow(const sal_Int32 nRow, const sal_Int32 nTab, ScDocument* pDoc)
{
    rImport.LockSolarMutex();
    ScMyStylesSet::iterator aItr = aCellStyles.begin();
    while (aItr != aCellStyles.end())
    {
        aItr->xRanges->InsertRow(nRow, nTab, pDoc);
        ++aItr;
    }
    rImport.UnlockSolarMutex();
}

void ScMyStylesImportHelper::InsertCol(const sal_Int32 nCol, const sal_Int32 nTab, ScDocument* pDoc)
{
    rImport.LockSolarMutex();
    ScMyStylesSet::iterator aItr = aCellStyles.begin();
    while (aItr != aCellStyles.end())
    {
        aItr->xRanges->InsertCol(nCol, nTab, pDoc);
        ++aItr;
    }
    rImport.UnlockSolarMutex();
}

void ScMyStylesImportHelper::EndTable()
{
    if (!bPrevRangeAdded)
    {
        AddRange();
        bPrevRangeAdded = sal_True;
    }
    nMaxRanges = 0;
}

void ScMyStylesImportHelper::SetStylesToRanges()
{
    ScMyStylesSet::iterator aItr = aCellStyles.begin();
    while (aItr != aCellStyles.end())
    {
        aItr->xRanges->SetStylesToRanges(&aItr->sStyleName, rImport);
        ++aItr;
    }
    aCellStyles.clear();
    aColDefaultStyles.clear();
    nMaxRanges = 0;
}

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
