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
#ifndef _SVSTDARR_STRINGSSORTDTOR_DECL
#define _SVSTDARR_STRINGSSORTDTOR
#include <bf_svtools/svstdarr.hxx>
#endif

#include "xmlnmspe.hxx"

#include <com/sun/star/style/XStyleFamiliesSupplier.hpp>
#include <com/sun/star/style/XStyle.hpp>
#include <com/sun/star/beans/XPropertyState.hpp>
#include <com/sun/star/document/XEventsSupplier.hpp>

#include "xmlaustp.hxx"
#include "xmlexp.hxx"
#include "XMLEventExport.hxx"
namespace binfilter {

using namespace ::com::sun::star;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::style;
using namespace ::com::sun::star::container;
using namespace ::com::sun::star::beans;

using rtl::OUString;
using namespace ::binfilter::xmloff::token;

using ::com::sun::star::document::XEventsSupplier;

XMLStyleExport::XMLStyleExport(
        SvXMLExport& rExp,
        const ::rtl::OUString& rPoolStyleName,
        SvXMLAutoStylePoolP *pAutoStyleP ) :
    rExport( rExp ),
    sIsPhysical( RTL_CONSTASCII_USTRINGPARAM( "IsPhysical" ) ),
    sIsAutoUpdate( RTL_CONSTASCII_USTRINGPARAM( "IsAutoUpdate" ) ),
    sFollowStyle( RTL_CONSTASCII_USTRINGPARAM( "FollowStyle" ) ),
    sNumberingStyleName( RTL_CONSTASCII_USTRINGPARAM( "NumberingStyleName" ) ),
    sPoolStyleName( rPoolStyleName ),
    pAutoStylePool( pAutoStyleP  )
{
}

XMLStyleExport::~XMLStyleExport()
{
}

void XMLStyleExport::exportStyleAttributes( const Reference< XStyle >& /*rStyle*/ )
{
}

void XMLStyleExport::exportStyleContent( const Reference< XStyle >& /*rStyle*/ )
{
}

sal_Bool XMLStyleExport::exportStyle(
        const Reference< XStyle >& rStyle,
          const OUString& rXMLFamily,
        const UniReference < SvXMLExportPropertyMapper >& rPropMapper,
        const OUString* pPrefix )
{
    Reference< XPropertySet > xPropSet( rStyle, UNO_QUERY );
    Reference< XPropertySetInfo > xPropSetInfo =
            xPropSet->getPropertySetInfo();

    Any aAny;

    // Don't export styles that aren't existing really. This may be the
    // case for StarOffice Writer's pool styles.
    if( xPropSetInfo->hasPropertyByName( sIsPhysical ) )
    {
        aAny = xPropSet->getPropertyValue( sIsPhysical );
        if( !*(sal_Bool *)aAny.getValue() )
            return sal_False;
    }

    // <style:style ...>
    GetExport().CheckAttrList();

    // style:name="..."
    OUString sName;

    if(pPrefix)
        sName = *pPrefix;
    sName += rStyle->getName();

    GetExport().AddAttribute( XML_NAMESPACE_STYLE, XML_NAME, sName );

    // style:family="..."
    if( rXMLFamily.getLength() > 0 )
        GetExport().AddAttribute( XML_NAMESPACE_STYLE, XML_FAMILY, rXMLFamily);

    // style:parent-style-name="..."
    OUString sParentString(rStyle->getParentStyle());
    OUString sParent;

    if(sParentString.getLength())
    {
        if(pPrefix)
            sParent = *pPrefix;
        sParent += sParentString;
    }
    else
        sParent = sPoolStyleName;

    if( sParent.getLength() )
        GetExport().AddAttribute( XML_NAMESPACE_STYLE, XML_PARENT_STYLE_NAME,
                                    sParent );

    // style:next-style-name="..." (paragraph styles only)
    if( xPropSetInfo->hasPropertyByName( sFollowStyle ) )
    {
        aAny = xPropSet->getPropertyValue( sFollowStyle );
        OUString sNextName;
        aAny >>= sNextName;
        if( sName != sNextName )
        {
            GetExport().AddAttribute( XML_NAMESPACE_STYLE, XML_NEXT_STYLE_NAME,
                          sNextName );
        }
    }

    // style:auto-update="..." (SW only)
    if( xPropSetInfo->hasPropertyByName( sIsAutoUpdate ) )
    {
        aAny = xPropSet->getPropertyValue( sIsAutoUpdate );
        if( *(sal_Bool *)aAny.getValue() )
            GetExport().AddAttribute( XML_NAMESPACE_STYLE, XML_AUTO_UPDATE,
                                      XML_TRUE );
    }

    // style:list-style-name="..." (SW paragarph styles only)
    if( xPropSetInfo->hasPropertyByName( sNumberingStyleName ) )
    {
        Reference< XPropertyState > xPropState( xPropSet, uno::UNO_QUERY );
        if( PropertyState_DIRECT_VALUE ==
                xPropState->getPropertyState( sNumberingStyleName  ) )
        {
            aAny = xPropSet->getPropertyValue( sNumberingStyleName );
            if( aAny.hasValue() )
            {
                OUString sListName;
                aAny >>= sListName;
                if( sListName.getLength() )
                    GetExport().AddAttribute( XML_NAMESPACE_STYLE, XML_LIST_STYLE_NAME,
                                  sListName );
            }
        }
    }

    // style:pool-id="..." is not required any longer since we use
    // english style names only
    exportStyleAttributes( rStyle );

    // TODO: style:help-file-name="..." and style:help-id="..." can neither
    // be modified by UI nor by API and that for, have not to be exported
    // currently.

    {
        // <style:style>
        SvXMLElementExport aElem( GetExport(), XML_NAMESPACE_STYLE, XML_STYLE,
                                  sal_True, sal_True );
        // <style:properties>
        ::std::vector< XMLPropertyState > xPropStates =
            rPropMapper->Filter( xPropSet );
        rPropMapper->exportXML( GetExport(), xPropStates,
                                XML_EXPORT_FLAG_IGN_WS );
        exportStyleContent( rStyle );

        // <script:events>, if they are supported by this style
        Reference<XEventsSupplier> xEventsSupp(rStyle, UNO_QUERY);
        GetExport().GetEventExport().Export(xEventsSupp);
    }
    return sal_True;
}

sal_Bool XMLStyleExport::exportDefaultStyle(
        const Reference< XPropertySet >& xPropSet,
          const OUString& rXMLFamily,
        const UniReference < SvXMLExportPropertyMapper >& rPropMapper )
{
    Reference< XPropertySetInfo > xPropSetInfo =
            xPropSet->getPropertySetInfo();

    Any aAny;

    // <style:default-style ...>
    GetExport().CheckAttrList();

    {
        // style:family="..."
        if( rXMLFamily.getLength() > 0 )
            GetExport().AddAttribute( XML_NAMESPACE_STYLE, XML_FAMILY,
                                      rXMLFamily );
        // <style:style>
        SvXMLElementExport aElem( GetExport(), XML_NAMESPACE_STYLE,
                                  XML_DEFAULT_STYLE,
                                  sal_True, sal_True );
        // <style:properties>
        //::std::vector< XMLPropertyState > xPropStates =
        //  rPropMapper->FilterDefaults( xPropSet );
        ::std::vector< XMLPropertyState > xPropStates =
            rPropMapper->FilterDefaults( xPropSet );
        rPropMapper->exportXML( GetExport(), xPropStates,
                                     XML_EXPORT_FLAG_IGN_WS );
//      exportStyleContent( rStyle );
    }
    return sal_True;
}

void XMLStyleExport::exportStyleFamily(
    const sal_Char *pFamily,
    const OUString& rXMLFamily,
    const UniReference < SvXMLExportPropertyMapper >& rPropMapper,
    sal_Bool bUsed, sal_uInt16 nFamily, const OUString* pPrefix)
{
    const OUString sFamily(OUString::createFromAscii(pFamily ));
    exportStyleFamily( sFamily, rXMLFamily, rPropMapper, bUsed, nFamily,
                       pPrefix);
}

void XMLStyleExport::exportStyleFamily(
    const OUString& rFamily, const OUString& rXMLFamily,
    const UniReference < SvXMLExportPropertyMapper >& rPropMapper,
    sal_Bool bUsed, sal_uInt16 nFamily, const OUString* pPrefix)
{
    DBG_ASSERT( GetExport().GetModel().is(), "There is the model?" );
    Reference< XStyleFamiliesSupplier > xFamiliesSupp( GetExport().GetModel(),
                                                       UNO_QUERY );
    Reference< XNameAccess > xStyleCont;

    Reference< XNameAccess > xFamilies( xFamiliesSupp->getStyleFamilies() );
    if( xFamilies->hasByName( rFamily ) )
        xFamilies->getByName( rFamily ) >>= xStyleCont;

    if( !xStyleCont.is() )
        return;

    Reference< XIndexAccess > xStyles( xStyleCont, UNO_QUERY );
    const sal_Int32 nStyles = xStyles->getCount();

    // If next styles are supported and used styles should be exported only,
    // the next style may be unused but has to be exported, too. In this case
    // the names of all exported styles are remembered.
    SvStringsSortDtor *pExportedStyles = 0;
    sal_Bool bFirstStyle = sal_True;
    sal_Int32 i;

    for( i=0; i < nStyles; i++ )
    {
        Reference< XStyle > xStyle;
        try
        {
            xStyles->getByIndex( i ) >>= xStyle;
        }
        catch( lang::IndexOutOfBoundsException )
        {
            // due to bugs in prior versions it is possible that
            // a binary file is missing some critical styles.
            // The only possible way to deal with this is to
            // not export them here and remain silent.
            continue;
        }

        DBG_ASSERT( xStyle.is(), "Style not found for export!" );
        if( xStyle.is() )
        {
            if( !bUsed || xStyle->isInUse() )
            {
                BOOL bExported = exportStyle( xStyle, rXMLFamily, rPropMapper,
                                              pPrefix );
                if( bUsed && bFirstStyle && bExported  )
                {
                    // If this is the first style, find out wether next styles
                    // are supported.
                    Reference< XPropertySet > xPropSet( xStyle, UNO_QUERY );
                    Reference< XPropertySetInfo > xPropSetInfo =
                        xPropSet->getPropertySetInfo();

                    if( xPropSetInfo->hasPropertyByName( sFollowStyle ) )
                        pExportedStyles = new SvStringsSortDtor;
                    bFirstStyle = sal_False;
                }

                if( pExportedStyles && bExported )
                {
                    // If next styles are supported, remember this style's name.
                    String *pTmp = new String( xStyle->getName() );
                    if( !pExportedStyles->Insert( pTmp ) )
                        delete pTmp;
                }
            }

            // if an auto style pool is given, remember this style's name as a
            // style name that must not be used by automatic styles.
            if( pAutoStylePool )
                pAutoStylePool->RegisterName( nFamily, xStyle->getName() );
        }
    }

    if( pExportedStyles )
    {
        // if next styles are supported, export all next styles that are
        // unused and that for, haven't been exported in the first loop.
        for( i=0; i < nStyles; i++ )
        {
            Reference< XStyle > xStyle;
            xStyles->getByIndex( i ) >>= xStyle;

            DBG_ASSERT( xStyle.is(), "Style not found for export!" );
            if( xStyle.is() )
            {
                Reference< XPropertySet > xPropSet( xStyle, UNO_QUERY );
                Reference< XPropertySetInfo > xPropSetInfo( xPropSet->getPropertySetInfo() );

                // styles that aren't existing realy are ignored.
                if( xPropSetInfo->hasPropertyByName( sIsPhysical ) )
                {
                    Any aAny( xPropSet->getPropertyValue( sIsPhysical ) );
                    if( !*(sal_Bool *)aAny.getValue() )
                        continue;
                }

                if( !xStyle->isInUse() )
                    continue;

                if( !xPropSetInfo->hasPropertyByName( sFollowStyle ) )
                {
                    DBG_ASSERT( 0==sFollowStyle.getLength(),
                                "no follow style???" );
                    continue;
                }

                OUString sNextName;
                xPropSet->getPropertyValue( sFollowStyle ) >>= sNextName;
                String sTmp( sNextName );
                // if the next style hasn't been exported by now, export it now
                // and remember its name.
                if( xStyle->getName() != sNextName &&
                    !pExportedStyles->Seek_Entry( &sTmp ) )
                {
                    xStyleCont->getByName( sNextName ) >>= xStyle;
                    DBG_ASSERT( xStyle.is(), "Style not found for export!" );

                    if( xStyle.is() && exportStyle( xStyle, rXMLFamily, rPropMapper, pPrefix ) )
                        pExportedStyles->Insert( new String( sTmp ) );
                }
            }
        }
    }

    delete pExportedStyles;
}


}//end of namespace binfilter

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
