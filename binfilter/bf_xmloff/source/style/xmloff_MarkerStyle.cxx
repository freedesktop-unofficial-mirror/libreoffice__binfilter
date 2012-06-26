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

#include "MarkerStyle.hxx"

#include "xexptran.hxx"


#include "nmspmap.hxx"


#include "xmlnmspe.hxx"


#include "xmlexp.hxx"

#include "xmlimp.hxx"


#include "rtl/ustring.hxx"

#include <com/sun/star/drawing/PolyPolygonBezierCoords.hpp>
namespace binfilter {

using namespace ::com::sun::star;
using namespace ::rtl;
using namespace ::binfilter::xmloff::token;


//-------------------------------------------------------------
// Import
//-------------------------------------------------------------

XMLMarkerStyleImport::XMLMarkerStyleImport( SvXMLImport& rImp )
    : rImport( rImp )
{
}

XMLMarkerStyleImport::~XMLMarkerStyleImport()
{
}

sal_Bool XMLMarkerStyleImport::importXML(
    const uno::Reference< xml::sax::XAttributeList >& xAttrList,
    uno::Any& rValue,
    OUString& rStrName )
{
    sal_Bool bRet           = sal_False;
    sal_Bool bHasViewBox    = sal_False;
    sal_Bool bHasPathData   = sal_False;

    SdXMLImExViewBox* pViewBox = NULL;

    SvXMLNamespaceMap& rNamespaceMap = rImport.GetNamespaceMap();
    SvXMLUnitConverter& rUnitConverter = rImport.GetMM100UnitConverter();

    sal_Int16 nAttrCount = xAttrList.is() ? xAttrList->getLength() : 0;
    for( sal_Int16 i = 0; i < nAttrCount; i++ )
    {
        OUString aStrFullAttrName = xAttrList->getNameByIndex( i );
        OUString aStrAttrName;
        rNamespaceMap.GetKeyByAttrName( aStrFullAttrName, &aStrAttrName );
        OUString aStrValue = xAttrList->getValueByIndex( i );

        if( IsXMLToken( aStrAttrName, XML_NAME ) )
        {
            rStrName = aStrValue;
        }
        else if( IsXMLToken( aStrAttrName, XML_VIEWBOX ) )
        {
            pViewBox = new SdXMLImExViewBox( aStrValue, rUnitConverter );
            bHasViewBox = sal_True;

        }
        else if( bHasViewBox && IsXMLToken( aStrAttrName, XML_D ) )
        {
            SdXMLImExSvgDElement aPoints(aStrValue, *pViewBox, awt::Point( 0, 0 ),
                awt::Size( pViewBox->GetWidth(), pViewBox->GetHeight() ),
                rUnitConverter );

            if(aPoints.IsCurve())
            {
                drawing::PolyPolygonBezierCoords aSourcePolyPolygon(
                    aPoints.GetPointSequenceSequence(),
                    aPoints.GetFlagSequenceSequence());
                rValue <<= aSourcePolyPolygon;
            }
            else
            {
                drawing::PolyPolygonBezierCoords aSourcePolyPolygon;
                aSourcePolyPolygon.Coordinates = aPoints.GetPointSequenceSequence();
                aSourcePolyPolygon.Flags.realloc(aSourcePolyPolygon.Coordinates.getLength());

                // Zeiger auf innere sequences holen
                const drawing::PointSequence* pInnerSequence = aSourcePolyPolygon.Coordinates.getConstArray();
                drawing::FlagSequence* pInnerSequenceFlags = aSourcePolyPolygon.Flags.getArray();

                for(sal_Int32 a(0); a < aSourcePolyPolygon.Coordinates.getLength(); a++)
                {
                    pInnerSequenceFlags->realloc(pInnerSequence->getLength());
                    drawing::PolygonFlags* pPolyFlags = pInnerSequenceFlags->getArray();

                    for(sal_Int32 b(0); b < pInnerSequence->getLength(); b++)
                        *pPolyFlags++ = drawing::PolygonFlags_NORMAL;

                    // next run
                    pInnerSequence++;
                    pInnerSequenceFlags++;
                }

                rValue <<= aSourcePolyPolygon;
            }

            bHasPathData = sal_True;
        }
    }

    if( pViewBox )
        delete pViewBox;

    bRet = bHasViewBox && bHasPathData;

    return bRet;
}


//-------------------------------------------------------------
// Export
//-------------------------------------------------------------

#ifndef SVX_LIGHT

XMLMarkerStyleExport::XMLMarkerStyleExport( SvXMLExport& rExp )
    : rExport( rExp )
{
}

XMLMarkerStyleExport::~XMLMarkerStyleExport()
{
}

sal_Bool XMLMarkerStyleExport::exportXML(
    const OUString& rStrName,
    const uno::Any& rValue )
{
    sal_Bool bRet(sal_False);

    if(rStrName.getLength())
    {
        drawing::PolyPolygonBezierCoords aBezier;

        if(rValue >>= aBezier)
        {
            OUString aStrValue;
            OUStringBuffer aOut;

            SvXMLUnitConverter& rUnitConverter =
                rExport.GetMM100UnitConverter();

            /////////////////
            // Name
            OUString aStrName( rStrName );
            rExport.AddAttribute( XML_NAMESPACE_DRAW, XML_NAME, aStrName );

            /////////////////
            // Viewbox (viewBox="0 0 1500 1000")
            sal_Int32 nMinX(0x7fffffff);
            sal_Int32 nMaxX(0x80000000);
            sal_Int32 nMinY(0x7fffffff);
            sal_Int32 nMaxY(0x80000000);
            sal_Int32 nOuterCnt(aBezier.Coordinates.getLength());
            drawing::PointSequence* pOuterSequence = aBezier.Coordinates.getArray();
            sal_Int32 a, b;
            sal_Bool bClosed(sal_False);

            for(a = 0L; a < nOuterCnt; a++)
            {
                drawing::PointSequence* pSequence = pOuterSequence++;
                const awt::Point *pPoints = pSequence->getConstArray();
                sal_Int32 nPointCount(pSequence->getLength());

                if(nPointCount)
                {
                    const awt::Point aStart = pPoints[0];
                    const awt::Point aEnd = pPoints[nPointCount - 1];

                    if(aStart.X == aEnd.X && aStart.Y == aEnd.Y)
                    {
                        bClosed = sal_True;
                    }
                }

                for(b = 0L; b < nPointCount; b++)
                {
                    const awt::Point aPoint = pPoints[b];

                    if( aPoint.X < nMinX )
                        nMinX = aPoint.X;

                    if( aPoint.X > nMaxX )
                        nMaxX = aPoint.X;

                    if( aPoint.Y < nMinY )
                        nMinY = aPoint.Y;

                    if( aPoint.Y > nMaxY )
                        nMaxY = aPoint.Y;
                }
            }

            sal_Int32 nDifX(nMaxX - nMinX);
            sal_Int32 nDifY(nMaxY - nMinY);

            SdXMLImExViewBox aViewBox( 0, 0, nDifX, nDifY );
            rExport.AddAttribute( XML_NAMESPACE_SVG, XML_VIEWBOX, aViewBox.GetExportString( rUnitConverter ) );

            /////////////////
            // Pathdata
            pOuterSequence = aBezier.Coordinates.getArray();
            drawing::FlagSequence*  pOuterFlags = aBezier.Flags.getArray();
            SdXMLImExSvgDElement aSvgDElement(aViewBox);

            for(a = 0L; a < nOuterCnt; a++)
            {
                drawing::PointSequence* pSequence = pOuterSequence++;
                drawing::FlagSequence* pFlags = pOuterFlags++;

                aSvgDElement.AddPolygon(pSequence, pFlags,
                    awt::Point( 0, 0 ),
                    awt::Size( aViewBox.GetWidth(), aViewBox.GetHeight() ),
                    rUnitConverter, bClosed);
            }

            // write point array
            rExport.AddAttribute(XML_NAMESPACE_SVG, XML_D, aSvgDElement.GetExportString());

            /////////////////
            // Do Write
            SvXMLElementExport rElem( rExport, XML_NAMESPACE_DRAW, XML_MARKER,
                                      sal_True, sal_False );
        }
    }

    return bRet;
}

#endif // #ifndef SVX_LIGHT
}//end of namespace binfilter

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
