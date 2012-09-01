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


#include <vcl/cvtgrf.hxx>

#ifndef SVX_LIGHT
#include <bf_sfx2/docfile.hxx>
#endif

#include "UnoNameItemTable.hxx"

#include "xdef.hxx"

#include "xbtmpit.hxx"
#include "unomid.hxx"
#include "unoprnms.hxx"
namespace binfilter {

using namespace ::com::sun::star;
using namespace ::rtl;
using namespace ::cppu;

class SvxUnoBitmapTable : public SvxUnoNameItemTable
{
public:
    SvxUnoBitmapTable( SdrModel* pModel ) throw();
    virtual ~SvxUnoBitmapTable() throw();

    virtual NameOrIndex* createItem() const throw();

    // XServiceInfo
    virtual OUString SAL_CALL getImplementationName(  ) throw( uno::RuntimeException );
    virtual uno::Sequence<  OUString > SAL_CALL getSupportedServiceNames(  ) throw( uno::RuntimeException);

    // XElementAccess
    virtual uno::Type SAL_CALL getElementType(  ) throw( uno::RuntimeException);
};

SvxUnoBitmapTable::SvxUnoBitmapTable( SdrModel* pModel ) throw()
: SvxUnoNameItemTable( pModel, XATTR_FILLBITMAP, MID_GRAFURL )
{
}

SvxUnoBitmapTable::~SvxUnoBitmapTable() throw()
{
}

OUString SAL_CALL SvxUnoBitmapTable::getImplementationName() throw( uno::RuntimeException )
{
    return OUString( RTL_CONSTASCII_USTRINGPARAM("SvxUnoBitmapTable") );
}

uno::Sequence< OUString > SAL_CALL SvxUnoBitmapTable::getSupportedServiceNames(  )
    throw( uno::RuntimeException )
{
    uno::Sequence< OUString > aSNS( 1 );
    aSNS.getArray()[0] = OUString( RTL_CONSTASCII_USTRINGPARAM("com.sun.star.drawing.BitmapTable" ));
    return aSNS;
}

NameOrIndex* SvxUnoBitmapTable::createItem() const throw()
{
    return new XFillBitmapItem();
}

// XElementAccess
uno::Type SAL_CALL SvxUnoBitmapTable::getElementType(  )
    throw( uno::RuntimeException )
{
    return ::getCppuType( (const ::rtl::OUString*)0 );
}

/**
 * Create a bitmaptable
 */
uno::Reference< uno::XInterface > SAL_CALL SvxUnoBitmapTable_createInstance( SdrModel* pModel )
{
    return *new SvxUnoBitmapTable(pModel);
}
}

namespace binfilter {
/** returns a GraphicObject for this URL */
BfGraphicObject CreateGraphicObjectFromURL( const ::rtl::OUString &rURL ) throw()
{
    const String aURL( rURL ), aPrefix( RTL_CONSTASCII_USTRINGPARAM(UNO_NAME_GRAPHOBJ_URLPREFIX) );

    if( aURL.Search( aPrefix ) == 0 )
    {
        // graphic manager url
        rtl::OString aUniqueID(rtl::OUStringToOString(rURL.copy(sizeof(UNO_NAME_GRAPHOBJ_URLPREFIX)-1), RTL_TEXTENCODING_UTF8));
        return BfGraphicObject(aUniqueID);
    }
    else
    {
        Graphic     aGraphic;

#ifndef SVX_LIGHT
        SfxMedium   aMedium( aURL, STREAM_READ, TRUE );
        SvStream*   pStream = aMedium.GetInStream();

        if( pStream )
            GraphicConverter::Import( *pStream, aGraphic );
#else
        String aSystemPath( rURL );
        ::utl::LocalFileHelper::ConvertURLToSystemPath( aSystemPath, aSystemPath );
        SvFileStream aFile( aSystemPath, STREAM_READ );
        GraphicConverter::Import( aFile, aGraphic );
#endif


        return BfGraphicObject( aGraphic );
    }
}
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
