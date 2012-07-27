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

#include <memory>

#include <com/sun/star/xml/AttributeData.hpp>
#include <com/sun/star/lang/XUnoTunnel.hpp>

#include <bf_xmloff/xmlcnimp.hxx>
#include <bf_xmloff/unoatrcn.hxx>
#include "xmlcnitm.hxx"
namespace binfilter {

using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::container;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::xml;

using rtl::OUString;

// ------------------------------------------------------------------------

/*N*/ TYPEINIT1(SvXMLAttrContainerItem, SfxPoolItem);

/*N*/ SvXMLAttrContainerItem::SvXMLAttrContainerItem( USHORT nWhich ) :
/*N*/   SfxPoolItem( nWhich )
/*N*/ {
/*N*/   pImpl = new SvXMLAttrContainerData;
/*N*/ }

/*N*/ SvXMLAttrContainerItem::SvXMLAttrContainerItem(
/*N*/                                       const SvXMLAttrContainerItem& rItem ) :
/*N*/   SfxPoolItem( rItem )
/*N*/ {
/*N*/   pImpl = new SvXMLAttrContainerData( *rItem.pImpl );
/*N*/ }

/*N*/ SvXMLAttrContainerItem::~SvXMLAttrContainerItem()
/*N*/ {
/*N*/   delete pImpl;
/*N*/ }

/*N*/ int SvXMLAttrContainerItem::operator==( const SfxPoolItem& rItem ) const
/*N*/ {
/*N*/   DBG_ASSERT( rItem.ISA(SvXMLAttrContainerItem),
/*N*/              "SvXMLAttrContainerItem::operator ==(): Bad type");
/*N*/   return *pImpl == *((const SvXMLAttrContainerItem&)rItem).pImpl;
/*N*/ }



/*N*/ USHORT SvXMLAttrContainerItem::GetVersion( USHORT /*nFileFormatVersion*/ ) const
/*N*/ {
/*N*/   // This item should never be stored
/*N*/   return USHRT_MAX;
/*N*/ }

/*N*/ bool  SvXMLAttrContainerItem::QueryValue( ::com::sun::star::uno::Any& rVal, BYTE /*nMemberId*/ ) const
/*N*/ {
/*N*/   Reference<XNameContainer> xContainer =
/*N*/       new SvUnoAttributeContainer( new SvXMLAttrContainerData( *pImpl ) );
/*N*/
/*N*/   rVal.setValue( &xContainer, ::getCppuType((Reference<XNameContainer>*)0) );
/*N*/   return true;
/*N*/ }
/*N*/ bool SvXMLAttrContainerItem::PutValue( const ::com::sun::star::uno::Any& rVal, BYTE /*nMemberId*/ )
/*NBFF*/{
/*NBFF*/    Reference<XInterface> xRef;
/*NBFF*/    SvUnoAttributeContainer* pContainer = NULL;
/*NBFF*/
/*NBFF*/    if( rVal.getValue() != NULL && rVal.getValueType().getTypeClass() == TypeClass_INTERFACE )
/*NBFF*/    {
/*NBFF*/        xRef = *(Reference<XInterface>*)rVal.getValue();
/*NBFF*/        Reference<XUnoTunnel> xTunnel(xRef, UNO_QUERY);
/*NBFF*/        if( xTunnel.is() )
/*NBFF*/            pContainer = (SvUnoAttributeContainer*)xTunnel->getSomething(SvUnoAttributeContainer::getUnoTunnelId());
/*NBFF*/    }
/*NBFF*/
/*NBFF*/    if( pContainer )
/*NBFF*/    {
/*NBFF*/        delete pImpl;
/*NBFF*/        pImpl = new SvXMLAttrContainerData( * pContainer->GetContainerImpl() );
/*NBFF*/    }
/*NBFF*/    else
/*NBFF*/    {
/*NBFF*/ 		::std::auto_ptr<SvXMLAttrContainerData> pNewImpl(new SvXMLAttrContainerData);
/*NBFF*/
/*NBFF*/        try
/*NBFF*/        {
/*NBFF*/            Reference<XNameContainer> xContainer( xRef, UNO_QUERY );
/*NBFF*/            if( !xContainer.is() )
/*NBFF*/                return false;
/*NBFF*/
/*NBFF*/            const Sequence< OUString > aNameSequence( xContainer->getElementNames() );
/*NBFF*/            const OUString* pNames = aNameSequence.getConstArray();
/*NBFF*/            const INT32 nCount = aNameSequence.getLength();
/*NBFF*/            Any aAny;
/*NBFF*/            AttributeData* pData;
/*NBFF*/
/*NBFF*/            INT32 nAttr; for( nAttr = 0; nAttr < nCount; nAttr++ )
/*NBFF*/            {
/*NBFF*/                const OUString aName( *pNames++ );
/*NBFF*/
/*NBFF*/                aAny = xContainer->getByName( aName );
/*NBFF*/                if( aAny.getValue() == NULL || aAny.getValueType() != ::getCppuType((AttributeData*)0) )
/*NBFF*/                    return false;
/*NBFF*/
/*NBFF*/                pData = (AttributeData*)aAny.getValue();
/*NBFF*/                sal_Int32 pos = aName.indexOf( sal_Unicode(':') );
/*NBFF*/                if( pos != -1 )
/*NBFF*/                {
/*NBFF*/                    const OUString aPrefix( aName.copy( 0, pos ));
/*NBFF*/                    const OUString aLName( aName.copy( pos+1 ));
/*NBFF*/
/*NBFF*/                    if( pData->Namespace.getLength() == 0 )
/*NBFF*/                    {
/*NBFF*/                        if( !pNewImpl->AddAttr( aPrefix, aLName, pData->Value ) )
/*NBFF*/                            break;
/*NBFF*/                    }
/*NBFF*/                    else
/*NBFF*/                    {
/*NBFF*/                        if( !pNewImpl->AddAttr( aPrefix, pData->Namespace, aLName, pData->Value ) )
/*NBFF*/                            break;
/*NBFF*/                    }
/*NBFF*/                }
/*NBFF*/                else
/*NBFF*/                {
/*NBFF*/                    if( !pNewImpl->AddAttr( aName, pData->Value ) )
/*NBFF*/                        break;
/*NBFF*/                }
/*NBFF*/            }
/*NBFF*/
/*NBFF*/            if( nAttr == nCount )
/*NBFF*/            {
/*NBFF*/                delete pImpl;
/*NBFF*/ 				pImpl = pNewImpl.release();
/*NBFF*/            }
/*NBFF*/            else
/*NBFF*/            {
/*NBFF*/ 				return false;
/*NBFF*/            }
/*NBFF*/        }
/*NBFF*/        catch(...)
/*NBFF*/        {
/*NBFF*/            return false;
/*NBFF*/        }
/*NBFF*/    }
/*NBFF*/    return true;
/*N*/ }


/*N*/ BOOL SvXMLAttrContainerItem::AddAttr( const OUString& rLName,
/*N*/                                     const OUString& rValue )
/*N*/ {
/*N*/   return pImpl->AddAttr( rLName, rValue );
/*N*/ }

/*N*/ BOOL SvXMLAttrContainerItem::AddAttr( const OUString& rPrefix,
/*N*/         const OUString& rNamespace, const OUString& rLName,
/*N*/         const OUString& rValue )
/*N*/ {
/*N*/   return pImpl->AddAttr( rPrefix, rNamespace, rLName, rValue );
/*N*/ }

/*N*/ USHORT SvXMLAttrContainerItem::GetAttrCount() const
/*N*/ {
/*N*/   return (USHORT)pImpl->GetAttrCount();
/*N*/ }

/*N*/ OUString SvXMLAttrContainerItem::GetAttrNamespace( USHORT i ) const
/*N*/ {
/*N*/   return pImpl->GetAttrNamespace( i );
/*N*/ }

/*N*/ OUString SvXMLAttrContainerItem::GetAttrPrefix( USHORT i ) const
/*N*/ {
/*N*/   return pImpl->GetAttrPrefix( i );
/*N*/ }

/*N*/ const OUString& SvXMLAttrContainerItem::GetAttrLName( USHORT i ) const
/*N*/ {
/*N*/   return pImpl->GetAttrLName( i );
/*N*/ }

/*N*/ const OUString& SvXMLAttrContainerItem::GetAttrValue( USHORT i ) const
/*N*/ {
/*N*/   return pImpl->GetAttrValue( i );
/*N*/ }

/*N*/ USHORT SvXMLAttrContainerItem::GetFirstNamespaceIndex() const
/*N*/ { return 0;   // DBG_BF_ASSERT VIRTUAL
/*N*/ }

/*N*/ USHORT SvXMLAttrContainerItem::GetNextNamespaceIndex( USHORT /*nIdx*/ ) const
/*N*/ { return 0;   // DBG_BF_ASSERT VIRTUAL
/*N*/ }

/*N*/ const OUString& SvXMLAttrContainerItem::GetNamespace( USHORT /*i*/ ) const
/*N*/ {
/*N*/   static OUString aStripped;  // DBG_BF_ASSERT VIRTUAL
/*N*/   return aStripped;
/*N*/ }

/*N*/ const OUString& SvXMLAttrContainerItem::GetPrefix( USHORT /*i*/ ) const
/*N*/ {
/*N*/   static OUString aStripped;  // DBG_BF_ASSERT VIRTUAL
/*N*/   return aStripped;
/*N*/ }


}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
