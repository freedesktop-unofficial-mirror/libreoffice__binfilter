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

#ifndef SC_DPOBJECT_HXX
#define SC_DPOBJECT_HXX

#include <bf_svtools/bf_solar.h>

#include "global.hxx"

#include "collect.hxx"

#include <com/sun/star/sheet/XDimensionsSupplier.hpp>
class Rectangle;
class SvStream;
namespace binfilter {


//------------------------------------------------------------------


class ScDPSaveData;
class ScDPOutput;
struct ScDPPositionData;
class ScMultipleReadHeader;
class ScPivot;
class ScPivotCollection;
struct ScPivotParam;
struct ScImportSourceDesc;
struct ScSheetSourceDesc;


struct ScDPServiceDesc
{
    String  aServiceName;
    String  aParSource;
    String  aParName;
    String  aParUser;
    String  aParPass;

    ScDPServiceDesc( const String& rServ, const String& rSrc, const String& rNam,
                        const String& rUser, const String& rPass ) :
        aServiceName( rServ ), aParSource( rSrc ), aParName( rNam ),
        aParUser( rUser ), aParPass( rPass ) {  }

    BOOL operator== ( const ScDPServiceDesc& rOther ) const
        { return aServiceName == rOther.aServiceName &&
                 aParSource   == rOther.aParSource &&
                 aParName     == rOther.aParName &&
                 aParUser     == rOther.aParUser &&
                 aParPass     == rOther.aParPass; }
};


class ScDPObject : public DataObject
{
private:
    ScDocument*             pDoc;
                                            // settings
    ScDPSaveData*           pSaveData;
    String                  aTableName;
    String                  aTableTag;
    ScRange                 aOutRange;
    ScSheetSourceDesc*      pSheetDesc;     //  for sheet data
    ScImportSourceDesc*     pImpDesc;       //  for database data
    ScDPServiceDesc*        pServDesc;      //  for external service
                                            // cached data
    ::com::sun::star::uno::Reference< ::com::sun::star::sheet::XDimensionsSupplier> xSource;
    ScDPOutput*             pOutput;
    BOOL                    bSettingsChanged;
    BOOL                    bAlive;         // FALSE if only used to hold settings


    void                CreateObjects();

public:
                ScDPObject( ScDocument* pD );
                ScDPObject(const ScDPObject& r);
    virtual     ~ScDPObject();

    virtual DataObject* Clone() const { return NULL; } // DBG_BF_ASSERT

    void                SetAlive(BOOL bSet);

    void                InvalidateData();
    void                InvalidateSource();


    void                SetSaveData(const ScDPSaveData& rData);
    ScDPSaveData*       GetSaveData() const     { return pSaveData; }

    void                SetOutRange(const ScRange& rRange);
    const ScRange&      GetOutRange() const     { return aOutRange; }

    void                SetSheetDesc(const ScSheetSourceDesc& rDesc);

    const ScSheetSourceDesc* GetSheetDesc() const   { return pSheetDesc; }
    const ScImportSourceDesc* GetImportSourceDesc() const   { return pImpDesc; }
    const ScDPServiceDesc* GetDPServiceDesc() const { return pServDesc; }


    BOOL                IsSheetData() const;
    BOOL                IsImportData() const { return(pImpDesc != NULL); }
    BOOL                IsServiceData() const { return(pServDesc != NULL); }

    void                SetName(const String& rNew);
    const String&       GetName() const                 { return aTableName; }
    void                SetTag(const String& rNew);
    const String&       GetTag() const                  { return aTableTag; }

    BOOL                LoadNew(SvStream& rStream, ScMultipleReadHeader& rHdr );
    BOOL                FillOldParam(ScPivotParam& rParam, BOOL bForFile) const;
    void                InitFromOldPivot(const ScPivot& rOld, ScDocument* pDoc, BOOL bSetSource);

    static void         ConvertOrientation( ScDPSaveData& rSaveData,
                            PivotField* pFields, USHORT nCount, USHORT nOrient,
                            ScDocument* pDoc, USHORT nRow, USHORT nTab,
                            const ::com::sun::star::uno::Reference<
                                ::com::sun::star::sheet::XDimensionsSupplier>& xSource,
                            BOOL bOldDefaults,
                            PivotField* pRefColFields = NULL, USHORT nRefColCount = 0,
                            PivotField* pRefRowFields = NULL, USHORT nRefRowCount = 0 );
};


class ScDPCollection : public Collection
{
private:
    ScDocument* pDoc;

public:
                ScDPCollection(ScDocument* pDocument);
                ScDPCollection(const ScDPCollection& r);
    virtual     ~ScDPCollection();

    virtual DataObject* Clone() const { return NULL; }  // DBG_BF_ASSERT

    ScDPObject* operator[](USHORT nIndex) const {return (ScDPObject*)At(nIndex);}

    BOOL        LoadNew( SvStream& rStream );

    void        ConvertOldTables( ScPivotCollection& rOldColl );

    String      CreateNewName( USHORT nMin = 1 ) const;
    void        EnsureNames();
};


} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
