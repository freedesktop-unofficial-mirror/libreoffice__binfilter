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

#ifndef SC_DPSAVE_HXX
#define SC_DPSAVE_HXX

#include <bf_svtools/bf_solar.h>
#include <bf_tools/string.hxx>
#include <com/sun/star/sheet/XDimensionsSupplier.hpp>
#include <vector>

class SvStream;

// --------------------------------------------------------------------
//
//  classes to save Data Pilot settings
//

namespace binfilter {

class ScDPSaveMember
{
private:
    String      aName;
    USHORT      nVisibleMode;
    USHORT      nShowDetailsMode;

public:
                            ScDPSaveMember(const String& rName);
                            ScDPSaveMember(const ScDPSaveMember& r);
                            ScDPSaveMember(SvStream& rStream);
                            ~ScDPSaveMember();

    BOOL                    operator== ( const ScDPSaveMember& r ) const;

    const String&           GetName()   { return aName; }
    void                    SetIsVisible(BOOL bSet);
    BOOL                    GetIsVisible() { return BOOL(nVisibleMode); }
    void                    SetShowDetails(BOOL bSet);
    BOOL                    GetShowDetails() { return BOOL(nShowDetailsMode); }

    void                    WriteToSource( const ::com::sun::star::uno::Reference<
                                            ::com::sun::star::uno::XInterface>& xMember );

    void Store( SvStream& ) const {}
};


typedef std::vector< ScDPSaveMember* > type_MemberList;

class ScDPSaveDimension
{
private:
    String      aName;
    String*     pLayoutName;        // alternative name for layout, not used (yet)
    BOOL        bIsDataLayout;
    BOOL        bDupFlag;
    USHORT      nOrientation;
    USHORT      nFunction;          // enum GeneralFunction, for data dimensions
    long        nUsedHierarchy;
    USHORT      nShowEmptyMode;     //! at level
    BOOL        bSubTotalDefault;   //! at level
    long        nSubTotalCount;
    USHORT*     pSubTotalFuncs;     // enum GeneralFunction
    type_MemberList aMemberList;

public:
                            ScDPSaveDimension(const String& rName, BOOL bDataLayout);
                            ScDPSaveDimension(const ScDPSaveDimension& r);
                            ScDPSaveDimension(SvStream& rStream);
                            ~ScDPSaveDimension();

    BOOL                    operator== ( const ScDPSaveDimension& r ) const;

    const type_MemberList&  GetMembers() { return aMemberList; }
    void                    AddMember(ScDPSaveMember* pMember) { aMemberList.push_back( pMember ); };

    void                    SetDupFlag(BOOL bSet)   { bDupFlag = bSet; }
    BOOL                    GetDupFlag() const      { return bDupFlag; }

    const String&           GetName() const         { return aName; }
    BOOL                    IsDataLayout() const    { return bIsDataLayout; }

    void                    SetOrientation(USHORT nNew);
    void                    SetSubTotals(long nCount, const USHORT* pFuncs);
    long                    GetSubTotalsCount() { return nSubTotalCount; }
    USHORT                  GetSubTotalFunc(long nIndex) { return pSubTotalFuncs[nIndex]; }
    void                    SetShowEmpty(BOOL bSet);
    BOOL                    GetShowEmpty() { return BOOL(nShowEmptyMode); }
    void                    SetFunction(USHORT nNew);       // enum GeneralFunction
    USHORT                  GetFunction() { return nFunction; }
    void                    SetUsedHierarchy(long nNew);
    long                    GetUsedHierarchy() { return nUsedHierarchy; }
    void                    SetLayoutName(const String* pName);
    const String&           GetLayoutName() const;
    BOOL                    HasLayoutName() const;
    void                    ResetLayoutName();

    USHORT                  GetOrientation() const  { return nOrientation; }


    void                    WriteToSource( const ::com::sun::star::uno::Reference<
                                            ::com::sun::star::uno::XInterface>& xDim );

    void Store( SvStream& ) const {}
};

typedef std::vector< ScDPSaveDimension* > type_ScDPDimensionList;

class ScDPSaveData
{
private:
    type_ScDPDimensionList  aDimList;
    USHORT      nColumnGrandMode;
    USHORT      nRowGrandMode;
    USHORT      nIgnoreEmptyMode;
    USHORT      nRepeatEmptyMode;

public:
                            ScDPSaveData();
                            ScDPSaveData(const ScDPSaveData& r);
                            ~ScDPSaveData();

    ScDPSaveData&           operator= ( const ScDPSaveData& r );

    BOOL                    operator== ( const ScDPSaveData& r ) const;

    const type_ScDPDimensionList&   GetDimensions() const { return aDimList; }
    void                    AddDimension(ScDPSaveDimension* pDim) { aDimList.push_back(pDim); }

    ScDPSaveDimension*      GetDimensionByName(const String& rName);
    ScDPSaveDimension*      GetDataLayoutDimension();

    ScDPSaveDimension*      DuplicateDimension(const String& rName);

    ScDPSaveDimension*      GetExistingDimensionByName(const String& rName);

    void                    SetColumnGrand( BOOL bSet );
    BOOL                    GetColumnGrand() const { return BOOL(nColumnGrandMode); }
    void                    SetRowGrand( BOOL bSet );
    BOOL                    GetRowGrand() const { return BOOL(nRowGrandMode); }
    void                    SetIgnoreEmptyRows( BOOL bSet );
    BOOL                    GetIgnoreEmptyRows() const { return BOOL(nIgnoreEmptyMode); }
    void                    SetRepeatIfEmpty( BOOL bSet );
    BOOL                    GetRepeatIfEmpty() const { return BOOL(nRepeatEmptyMode); }

    void                    WriteToSource( const ::com::sun::star::uno::Reference<
                                            ::com::sun::star::sheet::XDimensionsSupplier>& xSource );

    void Store( SvStream& ) const {}
    void                    Load( SvStream& rStream );

};


} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
