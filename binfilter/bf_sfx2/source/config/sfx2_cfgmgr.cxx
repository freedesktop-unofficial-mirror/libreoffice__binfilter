/*************************************************************************
 *
 *  $RCSfile: sfx2_cfgmgr.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: aw $ $Date: 2003-11-18 19:23:16 $
 *
 *  The Contents of this file are made available subject to the terms of
 *  either of the following licenses
 *
 *         - GNU Lesser General Public License Version 2.1
 *         - Sun Industry Standards Source License Version 1.1
 *
 *  Sun Microsystems Inc., October, 2000
 *
 *  GNU Lesser General Public License Version 2.1
 *  =============================================
 *  Copyright 2000 by Sun Microsystems, Inc.
 *  901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License version 2.1, as published by the Free Software Foundation.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *  MA  02111-1307  USA
 *
 *
 *  Sun Industry Standards Source License Version 1.1
 *  =================================================
 *  The contents of this file are subject to the Sun Industry Standards
 *  Source License Version 1.1 (the "License"); You may not use this file
 *  except in compliance with the License. You may obtain a copy of the
 *  License at http://www.openoffice.org/license.html.
 *
 *  Software provided under this License is provided on an "AS IS" basis,
 *  WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING,
 *  WITHOUT LIMITATION, WARRANTIES THAT THE SOFTWARE IS FREE OF DEFECTS,
 *  MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE, OR NON-INFRINGING.
 *  See the License for the specific provisions governing your rights and
 *  obligations concerning the Software.
 *
 *  The Initial Developer of the Original Code is: Sun Microsystems, Inc.
 *
 *  Copyright: 2000 by Sun Microsystems, Inc.
 *
 *  All Rights Reserved.
 *
 *  Contributor(s): _______________________________________
 *
 *
 ************************************************************************/

// include ---------------------------------------------------------------

#include <stdio.h>

#ifndef _COM_SUN_STAR_UCB_XCOMMANDENVIRONMENT_HPP_
#include <com/sun/star/ucb/XCommandEnvironment.hpp>
#endif
#ifndef _COM_SUN_STAR_LANG_WRAPPEDTARGETEXCEPTION_HPP_
#include <com/sun/star/lang/WrappedTargetException.hpp>
#endif
#ifndef _COM_SUN_STAR_UCB_INTERACTIVEAUGMENTEDIOEXCEPTION_HPP_
#include <com/sun/star/ucb/InteractiveAugmentedIOException.hpp>
#endif
#ifndef _COM_SUN_STAR_UCB_IOERRORCODE_HPP_
#include <com/sun/star/ucb/IOErrorCode.hpp>
#endif
#include <com/sun/star/uno/Reference.hxx>
#include <com/sun/star/uno/Any.hxx>

#include <ucbhelper/content.hxx>
#include <tools/urlobj.hxx>
#include <svtools/pathoptions.hxx>
#include <so3/svstor.hxx>
#include <sot/storinfo.hxx>

#ifndef _SVSTDARR_ULONGS_DECL
#define _SVSTDARR_ULONGS
#include <svtools/svstdarr.hxx>
#endif

#pragma hdrstop

#include "cfgmgr.hxx"
#include "cfgitem.hxx"
#include "objsh.hxx"
#include "cfgimpl.hxx"
#include "docfile.hxx"
namespace binfilter {

using namespace ::com::sun::star;

static const char pStorageName[] = "Configurations";

/*N*/ DBG_NAME(SfxConfigManager)

// ----------------------------------------------------------------------------

/*N*/ SotStorage* GetStorage( const String& rName, StreamMode nMode )
/*N*/ {
/*N*/     try
/*N*/   {
/*N*/       ::ucb::Content aContent( rName, uno::Reference < ::com::sun::star::ucb::XCommandEnvironment >() );
/*N*/       uno::Any aAny;
/*N*/       try
/*N*/       {
/*N*/           aAny = aContent.getPropertyValue( ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("IsDocument")) );
/*N*/       }
/*N*/       catch(::com::sun::star::ucb::InteractiveAugmentedIOException&)
/*N*/       {
/*N*/       }
/*N*/       sal_Bool bIsDocument;
/*N*/       if ( (aAny >>= bIsDocument) && bIsDocument )
/*N*/           return new SotStorage( TRUE, rName, nMode, STORAGE_TRANSACTED );
/*N*/       else
/*N*/           return new SotStorage( aContent, rName, nMode, STORAGE_TRANSACTED );
/*N*/   }
/*N*/     catch( ::com::sun::star::uno::Exception& e)
/*N*/     {
/*N*/       // Fatal error, possible corrupted configuration
/*N*/       ::com::sun::star::lang::WrappedTargetException wte;
/*N*/       ::rtl::OUString ouName = rName;
/*N*/       wte.Message = ::rtl::OUString::createFromAscii("GetStorage, name: '") + ouName +
/*N*/           ::rtl::OUString::createFromAscii("'");
/*N*/       wte.TargetException <<= e;
/*N*/       throw wte;
/*N*/   }
/*N*/ }

/*N*/ SfxConfigManager::SfxConfigManager( SotStorage* pStorage )
/*N*/   : pObjShell( NULL )
/*N*/   , nErrno( ERR_NO )
/*N*/   , bModified( FALSE )
/*N*/ {
/*N*/   DBG_CTOR(SfxConfigManager, 0);
/*N*/
/*N*/     // configuration stored in any storage
/*N*/     pItemArr = new SfxConfigItemArr_Impl;
/*N*/
/*N*/   if ( !pStorage )
/*N*/   {
/*N*/       // default config manager
/*N*/         {
/*N*/             // first check the upper layers of configuration
/*N*/             String aPathes = SvtPathOptions().GetUIConfigPath();
/*N*/             sal_uInt16 i, nIdx=0, nCount=aPathes.GetTokenCount( ';' );
/*N*/             for ( i=0; i<nCount; ++i )
/*N*/           {
/*?*/                 String aPathToken = aPathes.GetToken( 0, ';', nIdx );
/*?*/                 INetURLObject aPath( aPathToken );
/*?*/                 String aCfgFileName;
/*?*/                 aPath.insertName( String::CreateFromAscii("soffice.cfg") );
/*?*/                 aCfgFileName = aPath.GetMainURL( INetURLObject::NO_DECODE );
/*?*/                 SotStorageRef xStorage( GetStorage( aCfgFileName, STREAM_STD_READ ) );
/*?*/
/*?*/                 // load all the items, user layer will overwrite them if necessary
/*?*/                 // every item from the upper layer will reference xStorage
/*?*/                 if ( !xStorage->GetError() )
/*?*/                     LoadConfiguration( *xStorage );
/*N*/             }
/*N*/         }
/*N*/
/*N*/         String aCfgFileName;
/*N*/         INetURLObject aPath( SvtPathOptions().GetUserConfigPath() );
/*N*/         aPath.insertName( String::CreateFromAscii("soffice.cfg") );
/*N*/         aCfgFileName = aPath.GetMainURL( INetURLObject::NO_DECODE );
/*N*/         pStorage = GetStorage( aCfgFileName, STREAM_STD_READWRITE );
/*N*/   }
/*N*/
/*N*/     if ( !pStorage->IsOLEStorage() )
/*N*/   {
/*N*/       // take the storage ( otherwise no configitems could be loaded )
/*N*/       m_xStorage = pStorage;
/*N*/
/*N*/         // any other configuration storage or document in 6.0 format
/*N*/         // read directory information
/*N*/         if ( !LoadConfiguration( *pStorage ) )
/*N*/             nErrno = ERR_READ;
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/         // any other configuration storage or document in 5.0 format
/*?*/         // create temporary storage for the converted data in 6.0 format
/*?*/         m_xStorage = new SotStorage( TRUE, String(), STREAM_STD_READWRITE, STORAGE_TRANSACTED );
/*?*/
/*?*/         // convert 5.0 configuration into own 6.0 storage
/*?*/       SfxConfigManagerImExport_Impl aImporter( pObjShell, pItemArr );
/*?*/         nErrno = aImporter.Import( pStorage, m_xStorage );
/*N*/   }
/*N*/ }

/*N*/ SfxConfigManager::SfxConfigManager( SfxObjectShell& rShell )
/*N*/     : pObjShell( &rShell )
/*N*/   , nErrno( ERR_NO )
/*N*/   , bModified( FALSE )
/*N*/ {
/*N*/   DBG_CTOR(SfxConfigManager, 0);
/*N*/
/*N*/     // configuration stored in a document or template
/*N*/     pItemArr = new SfxConfigItemArr_Impl;
/*N*/
/*N*/     // create temporary storage
/*N*/     m_xStorage = new SotStorage( TRUE, String(), STREAM_STD_READWRITE, STORAGE_TRANSACTED );
/*N*/
/*N*/     SotStorageRef xStorage = pObjShell->GetStorage();
/*N*/     if ( !xStorage->IsOLEStorage() )
/*N*/   {
/*?*/       // use the configuration substorage of the document
/*?*/       SotStorageRef xCfgStorage = xStorage->OpenSotStorage( String::CreateFromAscii(pStorageName), STREAM_STD_READWRITE );
/*?*/
/*?*/       // copy data, using the original storage is only possible for SvPersist objects
/*?*/       // the retransfer of the data is organized by the document
/*?*/       xCfgStorage->CopyTo( m_xStorage );
/*?*/
/*?*/         // read directory information
/*?*/         if ( !LoadConfiguration( *m_xStorage ) )
/*?*/             nErrno = ERR_READ;
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/         // convert 5.0 configuration into own 6.0 storage
/*N*/       SfxConfigManagerImExport_Impl aImporter( pObjShell, pItemArr );
/*N*/         nErrno = aImporter.Import( xStorage, m_xStorage );
/*N*/   }
/*N*/
/*N*/     rShell.SetConfigManager( this );
/*N*/ }

/*N*/ SfxConfigManager::~SfxConfigManager()
/*N*/ {
/*N*/     for( USHORT i = 0; i < pItemArr->Count(); ++i )
/*N*/     {
/*N*/         SfxConfigItem_Impl* pItem = (*pItemArr)[i];
/*N*/         if ( pItem->pCItem )
/*N*/         {
/*?*/             DBG_ERROR("SfxConfigItem not removed!");
/*?*/             pItem->pCItem->ReleaseConfigManager();
/*N*/         }
/*N*/       delete pItem;
/*N*/     }
/*N*/
/*N*/     delete pItemArr;
/*N*/ }

// ------------------------------------------------------------------------

/*?*/ SotStorage* SfxConfigManager::GetConfigurationStorage( SotStorage* pDocStor )
/*?*/ {
/*?*/   return pDocStor->OpenSotStorage( String::CreateFromAscii(pStorageName), STREAM_STD_READWRITE );
/*?*/ }

/*?*/ String SfxConfigManager::GetURL()
/*?*/ {
/*?*/     if ( pObjShell )
/*?*/         return pObjShell->GetMedium()->GetName();
/*?*/     else if ( m_xStorage.Is() )
/*?*/         return m_xStorage->GetName();
/*?*/
/*?*/     DBG_ERROR("No storage!")
/*?*/     return String();
/*?*/ }

/*?*/ void SfxConfigManager::SetModified(BOOL bMod)
/*?*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  bModified = bMod;
//STRIP001  if ( bMod && pObjShell)
//STRIP001      pObjShell->SetModified( TRUE );
/*?*/ }

/*N*/ BOOL SfxConfigManager::HasConfiguration( SotStorage& rStorage )
/*N*/ {
/*N*/     if ( rStorage.IsOLEStorage() )
/*N*/   {
/*N*/         return SfxConfigManagerImExport_Impl::HasConfiguration( rStorage );
/*N*/     }
/*N*/     else
/*N*/     {
/*?*/         return rStorage.IsStorage( String::CreateFromAscii(pStorageName) );
/*N*/     }
/*N*/ }

// ----------------------------------------------------------------------------

/*N*/ BOOL SfxConfigManager::LoadConfiguration( SotStorage& rStorage )
/*N*/ {
/*N*/     // for the case that there are several layers of configuration
/*N*/     USHORT nOldCount = pItemArr->Count();
/*N*/
/*N*/     SvStorageInfoList aList;
/*N*/     rStorage.FillInfoList( &aList );
/*N*/     for( USHORT i = 0; i < aList.Count(); i++ )
/*N*/     {
/*?*/         SvStorageInfo& rInfo = aList.GetObject( i );
/*?*/         if ( rInfo.IsStream() )
/*?*/         {
/*?*/             // get StreamName and ItemType
/*?*/             SfxConfigItem_Impl* pItem = NULL;
/*?*/             String aStreamName = rInfo.GetName();
/*?*/             USHORT nType = SfxConfigManagerImExport_Impl::GetType( aStreamName );
/*?*/
/*?*/             // check items from upper layers if one of them is of the same type
/*?*/             for ( USHORT nPos=0; nPos<nOldCount; nPos++ )
/*?*/             {
/*?*/                 if ( (*pItemArr)[nPos]->nType == nType )
/*?*/                 {
/*?*/                     pItem = (*pItemArr)[nPos];
/*?*/                     break;
/*?*/                 }
/*?*/             }
/*?*/
/*?*/             if ( !pItem )
/*?*/             {
/*?*/                 // new item
/*?*/                 pItem = new SfxConfigItem_Impl;
/*?*/                 pItemArr->Insert( pItem, pItemArr->Count() );
/*?*/                 pItem->aStreamName = aStreamName;
/*?*/                 pItem->nType = nType;
/*?*/
/*?*/                 // compatibility for 5.0 format
/*?*/                 pItem->bDefault = FALSE;
/*?*/             }
/*?*/
/*?*/             // every item will hold a reference to its storage
/*?*/             pItem->xStorage = &rStorage;
/*?*/         }
/*N*/     }
/*N*/
/*N*/     return TRUE;
/*N*/ }

/*N*/ BOOL SfxConfigManager::StoreConfiguration( SotStorage* pStorage )
/*N*/ {
/*N*/     // What about the Modified flag ?! ( see also appmisc, config dialog, objcont! )
/*N*/     BOOL bOwnSaveDone = FALSE;
/*N*/     BOOL bRet = TRUE;
/*N*/     if ( m_xStorage.Is() )
/*N*/     {
/*N*/         // first update own storage
/*N*/         bRet = !bModified || StoreConfiguration_Impl( m_xStorage ) && m_xStorage->Commit();
/*N*/         bOwnSaveDone = TRUE;
/*N*/         if ( !pStorage && pObjShell )
/*N*/         {
/*?*/             // pStorage == NULL means : storage of document should be updated also
/*?*/             SotStorage* pDocumentStorage = pObjShell->GetStorage();
/*?*/             if ( !pDocumentStorage->IsOLEStorage() )
/*?*/             {
/*?*/                 // use the configuration substorage of the document
/*?*/                 SotStorageRef xCfgStorage = pDocumentStorage->OpenSotStorage(
/*?*/                         String::CreateFromAscii(pStorageName), STREAM_STD_READWRITE, STORAGE_TRANSACTED );
/*?*/                 bRet = m_xStorage->CopyTo( xCfgStorage ) && xCfgStorage->Commit();
/*?*/             }
/*?*/             else
/*?*/             {
/*?*/                 // 5.0 format : store compact configuration stream
/*?*/                 SfxConfigManagerImExport_Impl aExporter( pObjShell, pItemArr );
/*?*/                 nErrno = aExporter.Export( m_xStorage, pDocumentStorage );
/*?*/                 bRet = ( nErrno == ERR_NO );
/*?*/             }
/*?*/
/*?*/             if ( bRet )
/*?*/             {
/*?*/                 // can't commit changes if the documents' storage is under control of the document
/*?*/                 if( pObjShell->GetCreateMode() == SFX_CREATE_MODE_ORGANIZER )
/*?*/                     bRet = pDocumentStorage->Commit();
/*?*/                 else
/*?*/                 {
/*?*/                   // The configuration will be stored together the document, so the modified flag
/*?*/                   // must remain set!
/*?*/                     return TRUE;
/*?*/                 }
/*?*/             }
/*N*/         }
/*N*/
/*N*/         if ( bRet && !pStorage || pStorage == (SotStorage*) m_xStorage )
/*N*/         {
/*N*/             // only storing into own storage was requested
/*N*/             bModified = FALSE;
/*N*/             return TRUE;
/*N*/         }
/*N*/     }
/*N*/   else
/*?*/       DBG_ASSERT( pStorage, "Can't save configuration!" );
/*?*/
/*?*/     if ( !bRet || !pStorage )
/*?*/       return FALSE;
/*?*/
/*?*/     // store also into storage passed as parameter, but don't commit the changes,  because this will be done by the caller
/*?*/     if ( !pStorage->IsOLEStorage() )
/*?*/   {
/*?*/         // 6.0 format
/*?*/         if ( bOwnSaveDone )
/*?*/         {
/*?*/             // if own storage is updated, just copy it to the destination storage
/*?*/             bRet = m_xStorage->CopyTo( pStorage );
/*?*/         }
/*?*/         else
/*?*/         {
/*?*/             bRet = StoreConfiguration_Impl( pStorage );
/*?*/         }
/*?*/   }
/*?*/   else
/*?*/   {
/*?*/         // 5.0 format : store compact configuration stream
/*?*/       SfxConfigManagerImExport_Impl aExporter( pObjShell, pItemArr );
/*?*/         nErrno = aExporter.Export( m_xStorage, pStorage );
/*?*/         bRet = ( nErrno == ERR_NO );
/*?*/   }
/*?*/
/*?*/   bModified = !bRet;
/*?*/     return bRet;
/*N*/ }

/*?*/ BOOL SfxConfigManager::StoreConfiguration_Impl( SotStorage* pStorage )
/*?*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
/*?*/     BOOL bRet = TRUE;
//STRIP001
//STRIP001     // store directly into the destination storage
//STRIP001     USHORT nCount = pItemArr->Count();
//STRIP001     for ( USHORT nPos=0; bRet && nPos<nCount; nPos++ )
//STRIP001     {
//STRIP001         SfxConfigItem_Impl* pItem = (*pItemArr)[nPos];
//STRIP001         SfxConfigItem* pCItem = pItem->pCItem;
//STRIP001         if ( pCItem && pCItem->IsModified() )
//STRIP001          pItem->bDefault = pCItem->IsDefault();
//STRIP001
//STRIP001         if ( pItem->bDefault )
//STRIP001         {
//STRIP001             // elements with default configuration will not be stored
//STRIP001             if ( pStorage->IsContained( pItem->aStreamName ) )
//STRIP001                 pStorage->Remove( pItem->aStreamName );
//STRIP001         }
//STRIP001         else if ( pCItem )
//STRIP001         {
//STRIP001             if( pCItem->IsModified() || !pStorage->IsContained( pItem->aStreamName ) )
//STRIP001          {
//STRIP001                 // store all items that have not been stored before
//STRIP001                 bRet = pCItem->Store( *pStorage );
//STRIP001              if ( pStorage == m_xStorage )
//STRIP001                  pItem->xStorage = m_xStorage;
//STRIP001          }
//STRIP001         }
//STRIP001
//STRIP001      if ( pCItem )
//STRIP001          pCItem->SetModified( FALSE );
//STRIP001     }
//STRIP001
/*?*/     return bRet;
/*?*/ }

// ----------------------------------------------------------------------------

/*N*/ void SfxConfigManager::AddConfigItem( SfxConfigItem& rCItem )
/*N*/ {
/*N*/     for( USHORT i = 0; i < pItemArr->Count(); ++i )
/*N*/     {
/*N*/         SfxConfigItem_Impl* pItem = (*pItemArr)[i];
/*N*/         if ( pItem->nType == rCItem.GetType() )
/*N*/         {
/*N*/             if ( pItem->pCItem )
/*N*/             {
/*N*/                 SfxConfigItems_Impl& rItems = pItem->aItems;
/*N*/                 USHORT nCount = rItems.Count();
/*N*/ #ifdef DBG_UTIL
/*N*/                 for ( USHORT nItem=0; nItem<nCount; nItem++ )
/*N*/                     if ( rItems[nItem] == &rCItem )
/*N*/                         DBG_ERROR("Item already inserted!");
/*N*/ #endif
/*N*/                 rItems.Insert( &rCItem, nCount );
/*N*/             }
/*N*/             else
/*N*/                 pItem->pCItem = &rCItem;
/*N*/             return;
/*N*/         }
/*N*/     }
/*N*/
/*N*/     SfxConfigItem_Impl* pItem = new SfxConfigItem_Impl( &rCItem );
/*N*/     pItemArr->Insert( pItem, pItemArr->Count() );
/*N*/     pItem->bDefault = rCItem.IsDefault();
/*N*/     pItem->aStreamName = SfxConfigManagerImExport_Impl::GetStreamName( pItem->nType );
/*N*/ }

/*N*/ void SfxConfigManager::RemoveConfigItem( SfxConfigItem& rCItem )
/*N*/ {
/*N*/     for( USHORT i = 0; i < pItemArr->Count(); ++i )
/*N*/     {
/*N*/         SfxConfigItem_Impl* pItem = (*pItemArr)[i];
/*N*/         if ( pItem->nType == rCItem.GetType() )
/*N*/         {
/*N*/           if ( pItem->pCItem == &rCItem )
/*N*/           {
/*N*/               if ( pItem->aItems.Count() )
/*N*/               {
/*?*/                   pItem->pCItem = pItem->aItems[0];
/*?*/                   pItem->aItems.Remove( 0 );
/*N*/               }
/*N*/               else
/*N*/                   pItem->pCItem = NULL;
/*N*/           }
/*N*/           else
/*N*/           {
/*N*/                 USHORT nCount = pItem->aItems.Count();
/*N*/                 for ( USHORT nItem=0; nItem<nCount; nItem++ )
/*N*/                   if ( pItem->aItems[nItem] == &rCItem )
/*N*/                   {
/*N*/                       pItem->aItems.Remove(nItem);
/*N*/                       break;
/*N*/                   }
/*N*/           }
/*N*/
/*N*/             return;
/*N*/         }
/*N*/     }
/*N*/
/*N*/     DBG_ERROR( "Item not registered!" );
/*N*/ }

/*N*/ BOOL SfxConfigManager::HasConfigItem( USHORT nType )
/*N*/ {
/*N*/     for( USHORT i = 0; i < pItemArr->Count(); ++i )
/*N*/     {
/*N*/         SfxConfigItem_Impl* pItem = (*pItemArr)[i];
/*N*/         if ( pItem->nType == nType )
/*N*/             return TRUE;
/*N*/     }
/*N*/
/*N*/     return FALSE;
/*N*/ }

/*N*/ BOOL SfxConfigManager::LoadConfigItem( SfxConfigItem& rCItem )
/*N*/ {
/*N*/     DBG_ASSERT( m_xStorage.Is(), "No storage for configurations!" );
/*N*/
/*N*/     // search for item
/*N*/     for( USHORT i = 0; i < pItemArr->Count(); ++i )
/*N*/     {
/*N*/         SfxConfigItem_Impl* pItem = (*pItemArr)[i];
/*N*/         if ( pItem->nType == rCItem.GetType() )
/*N*/         {
/*N*/             // update configuration befor using it
/*N*/             // find last modified item
/*N*/             SfxConfigItem* pCfgItem = NULL;
/*N*/             if ( pItem->pCItem && pItem->pCItem->IsModified() )
/*N*/                 pCfgItem = pItem->pCItem;
/*N*/
/*N*/             USHORT nCount = pItem->aItems.Count();
/*N*/             for ( USHORT nItem=0; nItem<nCount; nItem++ )
/*N*/                 if ( pItem->aItems[nItem]->IsModified() )
/*N*/                     pCfgItem = pItem->aItems[nItem];
/*N*/
/*N*/             if ( pCfgItem )
/*?*/                 pCfgItem->StoreConfig();
/*N*/
/*N*/             if ( pItem->bDefault )
/*N*/             {
/*N*/                 // no configuration in storage
/*N*/                 rCItem.UseDefault();
/*N*/             }
/*N*/             else if ( pItem->xStorage.Is() )
/*N*/             {
/*N*/                 // item configuration is in upper layer of configuration
/*N*/                 if ( rCItem.Load( *pItem->xStorage ) != SfxConfigItem::ERR_OK )
/*N*/                   rCItem.UseDefault();
/*N*/             }
/*N*/             else
/*N*/             {
/*N*/                 DBG_ERROR("Item without Storage!");
/*N*/                 rCItem.UseDefault();
/*N*/                 return FALSE;
/*N*/             }
/*N*/
/*N*/             return TRUE;
/*N*/         }
/*N*/     }
/*N*/
/*N*/     DBG_ERROR("ItemType not registered!");
/*N*/     return FALSE;
/*N*/ }

/*?*/ BOOL SfxConfigManager::StoreConfigItem( SfxConfigItem& rCItem )
/*?*/ {DBG_ASSERT(0, "STRIP");return FALSE;//STRIP001
//STRIP001     DBG_ASSERT( m_xStorage.Is(), "No storage for configurations!" );
//STRIP001     if ( !m_xStorage.Is() )
//STRIP001         return FALSE;
//STRIP001
//STRIP001  BOOL bRet = TRUE;
//STRIP001
//STRIP001     // search for item
//STRIP001     for( USHORT i = 0; i < pItemArr->Count(); ++i )
//STRIP001     {
//STRIP001         SfxConfigItem_Impl* pItem = (*pItemArr)[i];
//STRIP001         if ( pItem->nType == rCItem.GetType() )
//STRIP001         {
//STRIP001             pItem->bDefault = rCItem.IsDefault();
//STRIP001             if ( rCItem.IsDefault() )
//STRIP001             {
//STRIP001                 // elements with default configuration will not be stored
//STRIP001                 if ( m_xStorage->IsContained( pItem->aStreamName ) )
//STRIP001                     bRet = m_xStorage->Remove( pItem->aStreamName );
//STRIP001             }
//STRIP001             else
//STRIP001             {
//STRIP001                 pItem->xStorage = m_xStorage;
//STRIP001                 if( rCItem.IsModified() || !m_xStorage->IsContained( pItem->aStreamName ) )
//STRIP001              {
//STRIP001                     // store all items that have not been stored before
//STRIP001                     bRet = rCItem.Store( *m_xStorage );
//STRIP001              }
//STRIP001             }
//STRIP001
//STRIP001             if ( rCItem.GetConfigManager() == this  )
//STRIP001              rCItem.SetModified( FALSE );
//STRIP001
//STRIP001          break;
//STRIP001         }
//STRIP001     }
//STRIP001
//STRIP001     DBG_ASSERT( i<pItemArr->Count(), "Item not registered!" );
//STRIP001     return bRet;
/*?*/ }

//STRIP001 BOOL SfxConfigManager::StoreAlwaysConfigItem( SfxConfigItem& rCItem )
//STRIP001 {
//STRIP001     DBG_ASSERT( m_xStorage.Is(), "No storage for configurations!" );
//STRIP001     if ( !m_xStorage.Is() )
//STRIP001         return FALSE;
//STRIP001
//STRIP001  BOOL bRet = TRUE;
//STRIP001
//STRIP001     // search for item
//STRIP001     for( USHORT i = 0; i < pItemArr->Count(); ++i )
//STRIP001     {
//STRIP001         SfxConfigItem_Impl* pItem = (*pItemArr)[i];
//STRIP001         if ( pItem->nType == rCItem.GetType() )
//STRIP001         {
//STRIP001             pItem->bDefault = FALSE;
//STRIP001             pItem->xStorage = m_xStorage;
//STRIP001
//STRIP001             // store all items that have not been stored before
//STRIP001             bRet = rCItem.Store( *m_xStorage );
//STRIP001
//STRIP001             if ( rCItem.GetConfigManager() == this  )
//STRIP001              rCItem.SetModified( FALSE );
//STRIP001
//STRIP001          break;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  return bRet;
//STRIP001 }

/*?*/ void SfxConfigManager::CopyConfigItem( SfxConfigManager& rMgr, USHORT nType )
/*?*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  BOOL bIsDefault = TRUE;
//STRIP001  for( USHORT i = 0; i < rMgr.pItemArr->Count(); ++i )
//STRIP001     {
//STRIP001         SfxConfigItem_Impl* pItem = (*rMgr.pItemArr)[i];
//STRIP001         if ( pItem->nType == nType )
//STRIP001         {
//STRIP001             if ( rMgr.m_xStorage->IsContained( pItem->aStreamName ) )
//STRIP001          {
//STRIP001              rMgr.m_xStorage->CopyTo( pItem->aStreamName, m_xStorage, pItem->aStreamName );
//STRIP001              bIsDefault = FALSE;
//STRIP001
//STRIP001              // Important: Set modified flag, because SfxConfigManager is modified due to CopyTo!
//STRIP001              // Otherwise StoreConfiguration doesn't call Commit() which is needed to write back to the storage.
//STRIP001              SetModified( TRUE );
//STRIP001          }
//STRIP001
//STRIP001          break;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001     for( USHORT n = 0; n < pItemArr->Count(); ++n )
//STRIP001     {
//STRIP001         SfxConfigItem_Impl* pItem = (*pItemArr)[n];
//STRIP001      if ( pItem->nType == nType )
//STRIP001      {
//STRIP001          // needs update of internal data!
//STRIP001          pItem->bDefault = bIsDefault;
//STRIP001          pItem->xStorage = m_xStorage;
//STRIP001          if ( bIsDefault && m_xStorage->IsContained( pItem->aStreamName ))
//STRIP001               m_xStorage->Remove( pItem->aStreamName );
//STRIP001          return;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if ( !bIsDefault )
//STRIP001  {
//STRIP001      SfxConfigItem_Impl* pItem = new SfxConfigItem_Impl;
//STRIP001      pItemArr->Insert( pItem, pItemArr->Count() );
//STRIP001      pItem->aStreamName = SfxConfigManagerImExport_Impl::GetStreamName( nType );
//STRIP001      pItem->nType = nType;
//STRIP001      pItem->xStorage = m_xStorage;
//STRIP001
//STRIP001      // compatibility for 5.0 format
//STRIP001      pItem->bDefault = FALSE;
//STRIP001  }
/*?*/ }

/*?*/ void SfxConfigManager::RemovePersistentConfigItem( USHORT nType )
/*?*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001     for( USHORT i = 0; i < pItemArr->Count(); ++i )
//STRIP001     {
//STRIP001         SfxConfigItem_Impl* pItem = (*pItemArr)[i];
//STRIP001         if ( pItem->nType == nType )
//STRIP001      {
//STRIP001             if ( m_xStorage->IsContained( pItem->aStreamName ) )
//STRIP001                 m_xStorage->Remove( pItem->aStreamName );
//STRIP001          break;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001     for( USHORT n = 0; n < pItemArr->Count(); ++n )
//STRIP001     {
//STRIP001         SfxConfigItem_Impl* pItem = (*pItemArr)[n];
//STRIP001      if ( pItem->nType == nType )
//STRIP001      {
//STRIP001             if ( pItem->pCItem )
//STRIP001             {
//STRIP001                 pItem->pCItem->ReConnect( NULL );
//STRIP001                 SfxConfigItems_Impl& rItems = pItem->aItems;
//STRIP001                 USHORT nCount = rItems.Count();
//STRIP001                 for ( USHORT nItem=0; nItem<nCount; nItem++ )
//STRIP001                  rItems[nItem]->ReConnect( NULL );
//STRIP001             }
//STRIP001
//STRIP001             delete pItemArr->GetObject( n );
//STRIP001             pItemArr->Remove( n );
//STRIP001          break;
//STRIP001      }
//STRIP001  }
/*?*/ }

/*?*/ void SfxConfigManager::ReInitialize( USHORT nType )
/*?*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001     for( USHORT i = 0; i < pItemArr->Count(); ++i )
//STRIP001     {
//STRIP001         SfxConfigItem_Impl* pItem = (*pItemArr)[i];
//STRIP001         if ( pItem->nType == nType )
//STRIP001         {
//STRIP001             if ( pItem->pCItem )
//STRIP001             {
//STRIP001                 pItem->pCItem->ReInitialize();
//STRIP001                 SfxConfigItems_Impl& rItems = pItem->aItems;
//STRIP001                 USHORT nCount = rItems.Count();
//STRIP001                 for ( USHORT nItem=0; nItem<nCount; nItem++ )
//STRIP001                         rItems[nItem]->ReInitialize();
//STRIP001             }
//STRIP001
//STRIP001             break;
//STRIP001         }
//STRIP001     }
/*?*/ }

//STRIP001 void SfxConfigManager::ReInitialize( const String& rStreamName )
//STRIP001 {
//STRIP001  if ( !pObjShell && m_xStorage.Is() )
//STRIP001  {
//STRIP001      //StoreConfiguration(m_xStorage);
//STRIP001 /*
//STRIP001      String aName = m_xStorage->GetName();
//STRIP001      SotStorageRef xStorage = new SotStorage( aName, STREAM_STD_READWRITE );
//STRIP001      for( USHORT i = 0; i < pItemArr->Count(); ++i )
//STRIP001      {
//STRIP001          SfxConfigItem_Impl* pItem = (*pItemArr)[i];
//STRIP001          if ( pItem->xStorage == m_xStorage )
//STRIP001              pItem->xStorage = xStorage;
//STRIP001      }
//STRIP001
//STRIP001      m_xStorage = xStorage;
//STRIP001 */
//STRIP001      m_xStorage->Revert();
//STRIP001
//STRIP001      USHORT nType = SfxConfigManagerImExport_Impl::GetType( rStreamName );
//STRIP001      if ( nType )
//STRIP001          ReInitialize( nType );
//STRIP001  }
//STRIP001 }

/*?*/ void SfxConfigManager::ReInitialize( SfxConfigItem* pCItem )
/*?*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001     for( USHORT i = 0; i < pItemArr->Count(); ++i )
//STRIP001     {
//STRIP001         SfxConfigItem_Impl* pItem = (*pItemArr)[i];
//STRIP001         if ( pItem->nType == pCItem->GetType() )
//STRIP001         {
//STRIP001             if ( pItem->pCItem )
//STRIP001             {
//STRIP001                 if ( pItem->pCItem != pCItem )
//STRIP001                     pItem->pCItem->ReInitialize();
//STRIP001                 SfxConfigItems_Impl& rItems = pItem->aItems;
//STRIP001                 USHORT nCount = rItems.Count();
//STRIP001                 for ( USHORT nItem=0; nItem<nCount; nItem++ )
//STRIP001                     if ( rItems[nItem] != pCItem )
//STRIP001                         rItems[nItem]->ReInitialize();
//STRIP001             }
//STRIP001
//STRIP001             break;
//STRIP001         }
//STRIP001     }
/*?*/ }

/*?*/ void SfxConfigManager::ResetConfigItem( USHORT nType )
/*?*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001     for( USHORT i = 0; i < pItemArr->Count(); ++i )
//STRIP001     {
//STRIP001         SfxConfigItem_Impl* pItem = (*pItemArr)[i];
//STRIP001         if ( pItem->nType == nType )
//STRIP001         {
//STRIP001             // elements with default configuration will not be stored
//STRIP001             if ( m_xStorage->IsContained( pItem->aStreamName ) )
//STRIP001             {
//STRIP001                 m_xStorage->Remove( pItem->aStreamName );
//STRIP001
//STRIP001              // Important: Set modified flag, because SfxConfigManager is modified due to m_xStorage->Remove!
//STRIP001              // Otherwise StoreConfiguration doesn't call Commit() which is needed to write back to the storage.
//STRIP001              SetModified( TRUE );
//STRIP001          }
//STRIP001             pItem->bDefault = TRUE;
//STRIP001             break;
//STRIP001         }
//STRIP001     }
/*?*/ }

/*?*/ void SfxConfigManager::ReConnect( USHORT nType, SfxConfigManager* pOther )
/*?*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001     for( USHORT i = 0; i < pItemArr->Count(); ++i )
//STRIP001     {
//STRIP001         SfxConfigItem_Impl* pItem = (*pItemArr)[i];
//STRIP001         if ( pItem->nType == nType )
//STRIP001         {
//STRIP001             if ( pItem->pCItem )
//STRIP001             {
//STRIP001                 pItem->pCItem->ReConnect( pOther );
//STRIP001                 SfxConfigItems_Impl& rItems = pItem->aItems;
//STRIP001                 USHORT nCount = rItems.Count();
//STRIP001                 for ( USHORT nItem=0; nItem<nCount; nItem++ )
//STRIP001                         rItems[nItem]->ReConnect( pOther );
//STRIP001             }
//STRIP001
//STRIP001             break;
//STRIP001         }
//STRIP001     }
/*?*/ }

}
