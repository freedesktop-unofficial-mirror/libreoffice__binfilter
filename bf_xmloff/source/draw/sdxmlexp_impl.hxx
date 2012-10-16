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

#ifndef _SDXMLEXP_IMPL_HXX
#define _SDXMLEXP_IMPL_HXX

#include "xmlexp.hxx"

#include <com/sun/star/frame/XModel.hpp>

#include <com/sun/star/task/XStatusIndicator.hpp>

#include <com/sun/star/container/XNameAccess.hpp>

#include <com/sun/star/drawing/XDrawPage.hpp>

#include <vector>

class Rectangle;
namespace binfilter {
class SfxPoolItem;
class SfxItemSet;

//////////////////////////////////////////////////////////////////////////////

class SvXMLUnitConverter;
class SvXMLExportItemMapper;
class OUStrings_Impl;
class OUStringsSort_Impl;

class ImpPresPageDrawStylePropMapper;
class ImpXMLEXPPageMasterInfo;
class ImpXMLDrawPageInfoList;
class ImpXMLAutoLayoutInfo;
class SvXMLAutoStylePoolP;
class XMLSdPropHdlFactory;
class ImpXMLShapeStyleInfo;
class XMLShapeExportPropertyMapper;
class XMLPageExportPropertyMapper;

typedef ::std::vector< ImpXMLEXPPageMasterInfo* > ImpXMLEXPPageMasterList;
typedef ::std::vector< ImpXMLAutoLayoutInfo*    > ImpXMLAutoLayoutInfoList;

//////////////////////////////////////////////////////////////////////////////

enum XmlPlaceholder
{
    XmlPlaceholderTitle,
    XmlPlaceholderOutline,
    XmlPlaceholderSubtitle,
    XmlPlaceholderText,
    XmlPlaceholderGraphic,
    XmlPlaceholderObject,
    XmlPlaceholderChart,
    XmlPlaceholderOrgchart,
    XmlPlaceholderTable,
    XmlPlaceholderPage,
    XmlPlaceholderNotes,
    XmlPlaceholderHandout,
    XmlPlaceholderVerticalTitle,
    XmlPlaceholderVerticalOutline
};

//////////////////////////////////////////////////////////////////////////////

class SdXMLExport : public SvXMLExport
{
    ::com::sun::star::uno::Reference< ::com::sun::star::container::XNameAccess > mxDocStyleFamilies;
    ::com::sun::star::uno::Reference< ::com::sun::star::container::XIndexAccess > mxDocMasterPages;
    ::com::sun::star::uno::Reference< ::com::sun::star::container::XIndexAccess > mxDocDrawPages;
    sal_Int32                   mnDocMasterPageCount;
    sal_Int32                   mnDocDrawPageCount;
    sal_uInt32                  mnShapeStyleInfoIndex;
    sal_uInt32                  mnObjectCount;

    // temporary infos
    ImpXMLEXPPageMasterList*    mpPageMasterInfoList;
    ImpXMLEXPPageMasterList*    mpPageMasterUsageList;
    ImpXMLEXPPageMasterList*    mpNotesPageMasterUsageList;
    ImpXMLEXPPageMasterInfo*    mpHandoutPageMaster;
    ImpXMLAutoLayoutInfoList*   mpAutoLayoutInfoList;

    ::com::sun::star::uno::Sequence< ::rtl::OUString > maDrawPagesAutoLayoutNames;

    ::std::vector< ::rtl::OUString >        maDrawPagesStyleNames;
    ::std::vector< ::rtl::OUString >        maMasterPagesStyleNames;

    XMLSdPropHdlFactory*                mpSdPropHdlFactory;
    XMLShapeExportPropertyMapper*       mpPropertySetMapper;
    XMLPageExportPropertyMapper*        mpPresPagePropsMapper;

    sal_uInt32                  mnUsedDateStyles;           // this is a bitfield of the used formatings for date fields
    sal_uInt32                  mnUsedTimeStyles;           // this is a bitfield of the used formatings for time fields

    sal_Bool                    mbIsDraw;
    sal_Bool                    mbFamilyGraphicUsed;
    sal_Bool                    mbFamilyPresentationUsed;

    const ::rtl::OUString           msZIndex;
    const ::rtl::OUString           msEmptyPres;
    const ::rtl::OUString           msModel;
    const ::rtl::OUString           msStartShape;
    const ::rtl::OUString           msEndShape;
    const ::rtl::OUString           msPageLayoutNames;

    virtual void _ExportStyles(BOOL bUsed);
    virtual void _ExportAutoStyles();
    virtual void _ExportMasterStyles();
    virtual void _ExportContent();
    // #82003#
    virtual void _ExportMeta();

    ImpXMLEXPPageMasterInfo* ImpGetOrCreatePageMasterInfo( ::com::sun::star::uno::Reference< ::com::sun::star::drawing::XDrawPage > xMasterPage );
    void ImpPrepPageMasterInfos();
    void ImpPrepDrawMasterInfos();
    void ImpWritePageMasterInfos();
    void ImpPrepAutoLayoutInfos();

    ImpXMLEXPPageMasterInfo* ImpGetPageMasterInfoByName(const ::rtl::OUString& rName);

    void ImpPrepDrawPageInfos();
    void ImpPrepMasterPageInfos();
    void ImpWritePresentationStyles();

    BOOL ImpPrepAutoLayoutInfo(const ::com::sun::star::uno::Reference< ::com::sun::star::drawing::XDrawPage >& xPage, ::rtl::OUString& rName);
    void ImpWriteAutoLayoutInfos();
    void ImpWriteAutoLayoutPlaceholder(XmlPlaceholder ePl, const Rectangle& rRect);

    void exportFormsElement( ::com::sun::star::uno::Reference< ::com::sun::star::drawing::XDrawPage > xDrawPage );
    void exportPresentationSettings();

    // #82003# helper function for recursive object count
    sal_uInt32 ImpRecursiveObjectCount( ::com::sun::star::uno::Reference< ::com::sun::star::drawing::XShapes > xShapes);

protected:
    virtual void GetViewSettings( ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue>& aProps);
    virtual void GetConfigurationSettings( ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue>& aProps);

public:
    // #110680#
    SdXMLExport(
        const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >& xServiceFactory,
        sal_Bool bIsDraw, sal_uInt16 nExportFlags = EXPORT_ALL );
    virtual ~SdXMLExport();

    void SetProgress(sal_Int32 nProg);

    // XExporter
    virtual void SAL_CALL setSourceDocument( const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XComponent >& xDoc ) throw(::com::sun::star::lang::IllegalArgumentException, ::com::sun::star::uno::RuntimeException);

    // get factories and mappers
    XMLSdPropHdlFactory* GetSdPropHdlFactory() const { return mpSdPropHdlFactory; }
    XMLShapeExportPropertyMapper* GetPropertySetMapper() const { return mpPropertySetMapper; }
    XMLPageExportPropertyMapper* GetPresPagePropsMapper() const { return mpPresPagePropsMapper; }

    BOOL IsDraw() const { return mbIsDraw; }
    BOOL IsImpress() const { return !mbIsDraw; }

    BOOL IsFamilyGraphicUsed() const { return mbFamilyGraphicUsed; }
    void SetFamilyGraphicUsed() { mbFamilyGraphicUsed = TRUE; }
    BOOL IsFamilyPresentationUsed() const { return mbFamilyPresentationUsed; }
    void SetFamilyPresentationUsed() { mbFamilyPresentationUsed = TRUE; }

    virtual void addDataStyle(const sal_Int32 nNumberFormat, sal_Bool bTimeFormat = sal_False );
    virtual void exportDataStyles();
    virtual void exportAutoDataStyles();
    virtual ::rtl::OUString getDataStyleName(const sal_Int32 nNumberFormat, sal_Bool bTimeFormat = sal_False ) const;

    // XServiceInfo ( : SvXMLExport )
    virtual ::rtl::OUString SAL_CALL getImplementationName() throw( ::com::sun::star::uno::RuntimeException );
};

}//end of namespace binfilter
#endif  //  _SDXMLEXP_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
