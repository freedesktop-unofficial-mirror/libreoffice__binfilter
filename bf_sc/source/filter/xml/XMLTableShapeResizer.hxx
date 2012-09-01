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

#ifndef _SC_XMLTABLESHAPERESIZER_HXX
#define _SC_XMLTABLESHAPERESIZER_HXX

#include <com/sun/star/drawing/XShape.hpp>
#include <com/sun/star/table/CellAddress.hpp>
#ifndef __SGI_STL_LIST
#include <list>
#endif
class Rectangle;
namespace binfilter {

class ScXMLImport;
class ScChartListenerCollection;
class ScDocument;

struct ScMyToResizeShape
{
    ::com::sun::star::uno::Reference < ::com::sun::star::drawing::XShape> xShape;
    ::rtl::OUString* pRangeList;
    ::com::sun::star::table::CellAddress    aEndCell;
    ::com::sun::star::table::CellAddress    aStartCell;
    sal_Int32 nEndX;
    sal_Int32 nEndY;

    ScMyToResizeShape() : pRangeList(NULL) {}
};

typedef std::list<ScMyToResizeShape> ScMyToResizeShapes;

class ScMyShapeResizer
{
    ScXMLImport&                rImport;
    ScMyToResizeShapes          aShapes;
    ScChartListenerCollection*  pCollection;

    sal_Bool IsOLE(::com::sun::star::uno::Reference< ::com::sun::star::drawing::XShape >& rShape) const;
    void CreateChartListener(ScDocument* pDoc,
        const ::rtl::OUString& rName,
        const ::rtl::OUString* pRangeList);
    void GetNewShapeSizePos(ScDocument* pDoc, const Rectangle& rStartRect,
                            const ::com::sun::star::table::CellAddress& rEndCell,
                            ::com::sun::star::awt::Point& rPoint, ::com::sun::star::awt::Size& rSize,
                            sal_Int32& rEndX, sal_Int32& rEndY) const;
public:
    ScMyShapeResizer(ScXMLImport& rImport);
    ~ScMyShapeResizer();

    void    AddShape(::com::sun::star::uno::Reference < ::com::sun::star::drawing::XShape>& rShape,
                    ::rtl::OUString* pRangeList,
                    ::com::sun::star::table::CellAddress& rStartAddress,
                    ::com::sun::star::table::CellAddress& rEndAddress,
                    sal_Int32 nEndX, sal_Int32 nEndY);
    void    ResizeShapes();
};

} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
