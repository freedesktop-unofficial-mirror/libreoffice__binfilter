/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sfx2_appuno.cxx,v $
 *
 *  $Revision: 1.11 $
 *
 *  last change: $Author: obo $ $Date: 2007-03-15 15:22:01 $
 *
 *  The Contents of this file are made available subject to
 *  the terms of GNU Lesser General Public License Version 2.1.
 *
 *
 *    GNU Lesser General Public License Version 2.1
 *    =============================================
 *    Copyright 2005 by Sun Microsystems, Inc.
 *    901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *    This library is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License version 2.1, as published by the Free Software Foundation.
 *
 *    This library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with this library; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *    MA  02111-1307  USA
 *
 ************************************************************************/
#if defined(_MSC_VER) && (_MSC_VER >= 1300)
#pragma warning( disable : 4290 )
#endif

#include "appuno.hxx"

#include <svtools/itempool.hxx>

#ifndef _SFXRECTITEM_HXX //autogen
#include <svtools/rectitem.hxx>
#endif

#include <tools/urlobj.hxx>

#ifndef _SB_SBMETH_HXX
#include "bf_basic/sbmeth.hxx"
#endif
#ifndef _BASMGR_HXX
#include "bf_basic/basmgr.hxx"
#endif

#ifndef _SBXCORE_HXX
#include "bf_basic/sbxcore.hxx"
#endif
#ifndef _SBXCLASS_HXX
#include "bf_basic/sbx.hxx"
#endif

#include <svtools/stritem.hxx>
#include <svtools/intitem.hxx>
#include <svtools/eitem.hxx>

#ifndef _COM_SUN_STAR_FRAME_XCOMPONENTLOADER_HPP_
#include <com/sun/star/frame/XComponentLoader.hpp>
#endif
#ifndef _COM_SUN_STAR_FRAME_DISPATCHRESULTSTATE_HPP_
#include <com/sun/star/frame/DispatchResultState.hpp>
#endif
#ifndef _COM_SUN_STAR_DOCUMENT_MACROEXECMODE_HPP_
#include <com/sun/star/document/MacroExecMode.hpp>
#endif
#ifndef _COM_SUN_STAR_UCB_XCONTENT_HPP_
#include <com/sun/star/ucb/XContent.hpp>
#endif


using namespace ::com::sun::star::ucb;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::registry;
using namespace ::com::sun::star::frame;
using namespace ::com::sun::star::beans;
using namespace ::com::sun::star::io;

#pragma hdrstop

#include "sfxsids.hrc"
#include "msgpool.hxx"
#include "request.hxx"
#include "frmload.hxx"
#include "frame.hxx"
#include "sfxbasic.hxx"
#include "objuno.hxx"
#include "unoctitm.hxx"
#include "dispatch.hxx"
#include "doctemplates.hxx"
#include "shutdownicon.hxx"

#ifndef _SFX_NAMECONT_HXX
#include "namecont.hxx"
#endif

#include "scriptcont.hxx"
#include "dlgcont.hxx"
#include "objshimp.hxx"
#include "fltoptint.hxx"
#include "sfxbasecontroller.hxx"
#include "brokenpackageint.hxx"
#include "eventsupplier.hxx"

#ifndef _COM_SUN_STAR_DOCUMENT_FILTEROPTIONSREQUEST_HPP_
#include <com/sun/star/document/FilterOptionsRequest.hpp>
#endif

#ifndef _COM_SUN_STAR_DOCUMENT_BROKENPACKAGEREQUEST_HPP_
#include <com/sun/star/document/BrokenPackageRequest.hpp>
#endif

namespace binfilter {

#define FRAMELOADER_SERVICENAME         "com.sun.star.frame.FrameLoader"
#define PROTOCOLHANDLER_SERVICENAME     "com.sun.star.frame.ProtocolHandler"

static const String sTemplateRegionName   = String::CreateFromAscii( "TemplateRegionName"   );
static const String sTemplateName   = String::CreateFromAscii( "TemplateName"   );
static const String sAsTemplate     = String::CreateFromAscii( "AsTemplate"     );
static const String sOpenNewView    = String::CreateFromAscii( "OpenNewView"    );
static const String sViewId         = String::CreateFromAscii( "ViewId"         );
static const String sPluginMode     = String::CreateFromAscii( "PluginMode"     );
static const String sReadOnly       = String::CreateFromAscii( "ReadOnly"       );
static const String sStartPresentation = String::CreateFromAscii( "StartPresentation"       );
static const String sFrameName      = String::CreateFromAscii( "FrameName"      );
static const String sMediaType      = String::CreateFromAscii( "MediaType"    );
static const String sPostData       = String::CreateFromAscii( "PostData"       );
static const String sCharacterSet   = String::CreateFromAscii( "CharacterSet"   );
static const String sInputStream    = String::CreateFromAscii( "InputStream"    );
static const String sOutputStream   = String::CreateFromAscii( "OutputStream"    );
static const String sHidden         = String::CreateFromAscii( "Hidden"         );
static const String sPreview        = String::CreateFromAscii( "Preview"        );
static const String sViewOnly       = String::CreateFromAscii( "ViewOnly"       );
static const String sDontEdit       = String::CreateFromAscii( "DontEdit"       );
static const String sSilent         = String::CreateFromAscii( "Silent"         );
static const String sJumpMark       = String::CreateFromAscii( "JumpMark"       );
static const String sFileName       = String::CreateFromAscii( "FileName"       );
static const String sOrigURL        = String::CreateFromAscii( "OriginalURL"    );
static const String sSalvageURL     = String::CreateFromAscii( "SalvagedFile"   );
static const String sStatusInd      = String::CreateFromAscii( "StatusIndicator" );
static const String sModel          = String::CreateFromAscii( "Model" );
static const String sFrame          = String::CreateFromAscii( "Frame" );
static const String sViewData       = String::CreateFromAscii( "ViewData" );
static const String sFilterData     = String::CreateFromAscii( "FilterData" );
static const String sSelectionOnly  = String::CreateFromAscii( "SelectionOnly" );
static const String sFilterFlags    = String::CreateFromAscii( "FilterFlags" );
static const String sMacroExecMode  = String::CreateFromAscii( "MacroExecutionMode" );
static const String sUpdateDocMode  = String::CreateFromAscii( "UpdateDocMode" );
static const String sMinimized      = String::CreateFromAscii( "Minimized" );
static const String sInteractionHdl = String::CreateFromAscii( "InteractionHandler" );
static const String sWindowState    = String::CreateFromAscii( "WindowState" );
static const String sUCBContent     = String::CreateFromAscii( "UCBContent" );
static const String sRepairPackage  = String::CreateFromAscii( "RepairPackage" );
static const String sDocumentTitle  = String::CreateFromAscii( "DocumentTitle" );

/*N*/ void TransformParameters( sal_uInt16 nSlotId, const ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue>& rArgs, SfxAllItemSet& rSet, const SfxSlot* pSlot )
/*N*/ {
/*N*/     if ( !pSlot )
/*N*/         pSlot = SFX_SLOTPOOL().GetSlot( nSlotId );
/*N*/
/*N*/     if ( !pSlot )
/*N*/         return;
/*N*/
/*N*/     if ( nSlotId == SID_OPENURL )
/*N*/         nSlotId = SID_OPENDOC;
/*N*/     if ( nSlotId == SID_SAVEASURL )
/*N*/         nSlotId = SID_SAVEASDOC;
/*N*/
/*N*/     sal_Int32 nCount = rArgs.getLength();
/*N*/     if ( !nCount )
/*N*/         return;
/*N*/
/*N*/     const ::com::sun::star::beans::PropertyValue* pPropsVal = rArgs.getConstArray();
/*N*/     if ( !pSlot->IsMode(SFX_SLOT_METHOD) )
/*N*/     {
/*N*/         // slot is a property
/*N*/         const SfxType* pType = pSlot->GetType();
/*N*/         SfxPoolItem* pItem = pType->CreateItem();
/*N*/         if ( !pItem )
/*N*/         {
/*N*/ #ifdef DBG_UTIL
/*N*/             ByteString aStr( "No creator method for item: ");
/*N*/             aStr += ByteString::CreateFromInt32( nSlotId );
/*N*/             DBG_ERROR( aStr.GetBuffer() );
/*N*/ #endif
/*N*/             return;
/*N*/         }
/*N*/
/*N*/         USHORT nWhich = rSet.GetPool()->GetWhich(nSlotId);
/*N*/         BOOL bConvertTwips = ( rSet.GetPool()->GetMetric( nWhich ) == SFX_MAPUNIT_TWIP );
/*N*/         pItem->SetWhich( nWhich );
/*N*/         USHORT nSubCount = pType->nAttribs;
/*N*/         if ( nSubCount == 0 )
/*N*/         {
/*N*/             // simple property
/*N*/ #ifdef DBG_UTIL
/*N*/             // this indicates an error only for macro recording; if the dispatch API is used for
/*N*/             // UI purposes or from the testtool, it is possible to use the "toggle" ability of
/*N*/             // some property slots, so this should be notified as a warning only
/*N*/             if ( nCount != 1 )
/*N*/             {
/*N*/                 ByteString aStr( "MacroPlayer: wrong number of parameters for slot: ");
/*N*/                 aStr += ByteString::CreateFromInt32( nSlotId );
/*N*/                 DBG_WARNING( aStr.GetBuffer() );
/*N*/             }
/*N*/ #endif
/*N*/             if ( nCount )
/*N*/             {
/*N*/                 const ::com::sun::star::beans::PropertyValue& rProp = pPropsVal[0];
/*N*/                 String aName = rProp.Name;
/*N*/                 if ( aName.CompareToAscii( pSlot->pUnoName ) == COMPARE_EQUAL )
/*N*/                 {
/*N*/                     if( pItem->PutValue( rProp.Value ) )
/*N*/                         // only use successfully converted items
/*N*/                         rSet.Put( *pItem );
/*N*/ #ifdef DBG_UTIL
/*N*/                     else
/*N*/                     {
/*N*/                         ByteString aStr( "MacroPlayer: Property not convertable: ");
/*N*/                         aStr += pSlot->pUnoName;
/*N*/                         DBG_WARNING( aStr.GetBuffer() );
/*N*/                     }
/*N*/ #endif
/*N*/                 }
/*N*/ #ifdef DBG_UTIL
/*N*/                 else
/*N*/                 {
/*N*/                     // for a simple property the name of the only argument *must* match
/*N*/                     ByteString aStr( "MacroPlayer: Property name does not match: ");
/*N*/                     aStr += ByteString( aName, RTL_TEXTENCODING_UTF8 );
/*N*/                     DBG_WARNING( aStr.GetBuffer() );
/*N*/                 }
/*N*/ #endif
/*N*/             }
/*N*/         }
/*N*/         else
/*N*/         {
/*N*/ #ifdef DBG_UTIL
/*N*/             // this indicates an error only for macro recording; if the dispatch API is used for
/*N*/             // UI purposes or from the testtool, it is possible to skip some or all arguments,
/*N*/             // so this should be notified as a warning only
/*N*/             if ( nCount != nSubCount )
/*N*/             {
/*N*/                 ByteString aStr( "MacroPlayer: wrong number of parameters for slot: ");
/*N*/                 aStr += ByteString::CreateFromInt32( nSlotId );
/*N*/                 DBG_WARNING( aStr.GetBuffer() );
/*N*/             }
/*N*/ #endif
/*N*/             // complex property; collect sub items from the parameter set and reconstruct complex item
/*N*/             USHORT nFound=0;
/*N*/             for ( sal_uInt16 n=0; n<nCount; n++ )
/*N*/             {
/*N*/                 const ::com::sun::star::beans::PropertyValue& rProp = pPropsVal[n];
/*N*/                 USHORT nSub; for ( nSub=0; nSub<nSubCount; nSub++ )
/*N*/                 {
/*N*/                     // search sub item by name
/*N*/                     ByteString aStr( pSlot->pUnoName );
/*N*/                     aStr += '.';
/*N*/                     aStr += ByteString( pType->aAttrib[nSub].pName );
/*N*/                     const char* pName = aStr.GetBuffer();
/*N*/                     if ( rProp.Name.compareToAscii( pName ) == COMPARE_EQUAL )
/*N*/                   {
/*N*/                         BYTE nSubId = (BYTE) (sal_Int8) pType->aAttrib[nSub].nAID;
/*N*/                         if ( bConvertTwips )
/*N*/                             nSubId |= CONVERT_TWIPS;
/*N*/                         if ( pItem->PutValue( rProp.Value, nSubId ) )
/*N*/                             ++nFound;
/*N*/                       break;
/*N*/                   }
/*N*/                 }
/*N*/
/*N*/ #ifdef DBG_UTIL
/*N*/                 if ( nSub >= nSubCount )
/*N*/                 {
/*N*/                     // for complex property slots every passed argument *must* match to the name of a member of the item
/*N*/                     ByteString aStr( "MacroPlayer: Property name does not match: ");
/*N*/                     aStr += ByteString( String(rProp.Name), RTL_TEXTENCODING_UTF8 );
/*N*/                     DBG_WARNING( aStr.GetBuffer() );
/*N*/                 }
/*N*/ #endif
/*N*/             }
/*N*/
/*N*/             if ( nFound == nSubCount )
/*N*/                 // only use completely converted items
/*N*/                 rSet.Put( *pItem );
/*N*/ #ifdef DBG_UTIL
/*N*/             else
/*N*/             {
/*N*/                 ByteString aStr( "MacroPlayer: Complex property not convertable: ");
/*N*/                 aStr += pSlot->pUnoName;
/*N*/                 DBG_WARNING( aStr.GetBuffer() );
/*N*/             }
/*N*/ #endif
/*N*/         }
/*N*/
/*N*/         delete pItem;
/*N*/     }
/*N*/     else if ( nCount )
/*N*/     {
/*N*/ #ifdef DBG_UTIL
/*N*/         // for debugging purposes: detect parameters that don't match to any formal argument or one of its members
/*N*/         sal_Int32 nFoundArgs = 0;
/*N*/ #endif
/*N*/         // slot is a method
/*N*/         for ( sal_uInt16 nArgs=0; nArgs<pSlot->nArgDefCount; nArgs++ )
/*N*/         {
/*N*/             const SfxFormalArgument &rArg = pSlot->GetFormalArgument( nArgs );
/*N*/             SfxPoolItem* pItem = rArg.CreateItem();
/*N*/             if ( !pItem )
/*N*/             {
/*N*/ #ifdef DBG_UTIL
/*N*/                 ByteString aStr( "No creator method for argument: ");
/*N*/                 aStr += rArg.pName;
/*N*/                 DBG_ERROR( aStr.GetBuffer() );
/*N*/ #endif
/*N*/                 return;
/*N*/             }
/*N*/
/*N*/           USHORT nWhich = rSet.GetPool()->GetWhich(rArg.nSlotId);
/*N*/             BOOL bConvertTwips = ( rSet.GetPool()->GetMetric( nWhich ) == SFX_MAPUNIT_TWIP );
/*N*/             pItem->SetWhich( nWhich );
/*N*/             const SfxType* pType = rArg.pType;
/*N*/             USHORT nSubCount = pType->nAttribs;
/*N*/             if ( nSubCount == 0 )
/*N*/             {
/*N*/                 // "simple" (base type) argument
/*N*/                 for ( sal_uInt16 n=0; n<nCount; n++ )
/*N*/                 {
/*N*/                     const ::com::sun::star::beans::PropertyValue& rProp = pPropsVal[n];
/*N*/                     String aName = rProp.Name;
/*N*/                     if ( aName.CompareToAscii(rArg.pName) == COMPARE_EQUAL )
/*N*/                     {
/*N*/ #ifdef DBG_UTIL
/*N*/                         ++nFoundArgs;
/*N*/ #endif
/*N*/                         if( pItem->PutValue( rProp.Value ) )
/*N*/                             // only use successfully converted items
/*N*/                             rSet.Put( *pItem );
/*N*/ #ifdef DBG_UTIL
/*N*/                         else
/*N*/                         {
/*N*/                             ByteString aStr( "MacroPlayer: Property not convertable: ");
/*N*/                             aStr += rArg.pName;
/*N*/                             DBG_WARNING( aStr.GetBuffer() );
/*N*/                         }
/*N*/ #endif
/*N*/                         break;
/*N*/                     }
/*N*/                 }
/*N*/             }
/*N*/             else
/*N*/             {
/*N*/                 // complex argument; collect sub items from argument arry and reconstruct complex item
/*N*/               // only put item if at least one member was found and had the correct type
/*N*/               // (is this a good idea?! Should we ask for *all* members?)
/*N*/                 BOOL bRet = FALSE;
/*N*/                 for ( sal_uInt16 n=0; n<nCount; n++ )
/*N*/                 {
/*N*/                     const ::com::sun::star::beans::PropertyValue& rProp = pPropsVal[n];
/*N*/                     for ( USHORT nSub=0; nSub<nSubCount; nSub++ )
/*N*/                     {
/*N*/                         // search sub item by name
/*N*/                         ByteString aStr( rArg.pName );
/*N*/                         aStr += '.';
/*N*/                         aStr += pType->aAttrib[nSub].pName;
/*N*/                         const char* pName = aStr.GetBuffer();
/*N*/                         if ( rProp.Name.compareToAscii( pName ) == COMPARE_EQUAL )
/*N*/                         {
/*N*/                           // at least one member found ...
/*N*/                           bRet = TRUE;
/*N*/ #ifdef DBG_UTIL
/*N*/                             ++nFoundArgs;
/*N*/ #endif
/*N*/                             BYTE nSubId = (BYTE) (sal_Int8) pType->aAttrib[nSub].nAID;
/*N*/                             if ( bConvertTwips )
/*N*/                                 nSubId |= CONVERT_TWIPS;
/*N*/                             if (!pItem->PutValue( rProp.Value, nSubId ) )
/*N*/                               // ... but it was not convertable
/*N*/                                 bRet = FALSE;
/*N*/                           break;
/*N*/                         }
/*N*/                     }
/*N*/                 }
/*N*/
/*N*/                 if ( bRet )
/*N*/                     // only use completely converted items
/*N*/                     rSet.Put( *pItem );
/*N*/             }
/*N*/
/*N*/             delete pItem;
/*N*/         }
/*N*/
/*N*/         // special additional parameters for some slots not seen in the slot definitions
/*N*/         // Some of these slots are not considered to be used for macro recording, because they shouldn't be recorded as slots,
/*N*/         // but as dispatching or factory or arbitrary URLs to the frame
/*N*/         // Some also can use additional arguments that are not recordable (will be changed later,
/*N*/         // f.e. "SaveAs" shouldn't support parameters not in the slot definition!)
/*N*/         if ( nSlotId == SID_NEWWINDOW )
/*N*/         {
/*N*/             for ( sal_uInt16 n=0; n<nCount; n++ )
/*N*/             {
/*N*/                 const ::com::sun::star::beans::PropertyValue& rProp = pPropsVal[n];
/*N*/                 String aName = rProp.Name;
/*N*/                 if ( aName == sFrame )
/*N*/                     rSet.Put( SfxUnoAnyItem( SID_FILLFRAME, rProp.Value ) );
/*N*/                 else
/*N*/                 if ( aName == sHidden )
/*N*/                 {
/*N*/                     sal_Bool bVal = sal_False;
/*N*/                     if (rProp.Value >>= bVal)
/*N*/                         rSet.Put( SfxBoolItem( SID_HIDDEN, bVal ) );
/*N*/                 }
/*N*/             }
/*N*/         }
/*N*/         else if ( nSlotId == SID_OPENDOC || nSlotId == SID_EXPORTDOC || nSlotId == SID_SAVEASDOC ||
/*N*/                 nSlotId == SID_SAVETO || nSlotId == SID_EXPORTDOCASPDF || nSlotId == SID_DIRECTEXPORTDOCASPDF )
/*N*/         {
/*N*/             for ( sal_uInt16 n=0; n<nCount; n++ )
/*N*/             {
/*N*/                 const ::com::sun::star::beans::PropertyValue& rProp = pPropsVal[n];
/*N*/                 String aName = rProp.Name;
/*N*/                 if ( aName == sModel )
/*N*/                     rSet.Put( SfxUnoAnyItem( SID_DOCUMENT, rProp.Value ) );
/*N*/                 else if ( aName == sStatusInd )
/*N*/                      {
/*N*/                         Reference< ::com::sun::star::task::XStatusIndicator > xVal;
/*N*/                         sal_Bool bOK = ((rProp.Value >>= xVal) && xVal.is());
/*N*/                         DBG_ASSERT( bOK, "invalid type for StatusIndicator" )
/*N*/                         if (bOK)
/*N*/                             rSet.Put( SfxUnoAnyItem( SID_PROGRESS_STATUSBAR_CONTROL, rProp.Value ) );
/*N*/                      }
/*N*/                 else if ( aName == sInteractionHdl )
/*N*/                      {
/*N*/                         Reference< ::com::sun::star::task::XInteractionHandler > xVal;
/*N*/                         sal_Bool bOK = ((rProp.Value >>= xVal) && xVal.is());
/*N*/                         DBG_ASSERT( bOK, "invalid type for InteractionHandler" )
/*N*/                         if (bOK)
/*N*/                             rSet.Put( SfxUnoAnyItem( SID_INTERACTIONHANDLER, rProp.Value ) );
/*N*/                      }
/*N*/                 else if ( aName == sViewData )
/*N*/                     rSet.Put( SfxUnoAnyItem( SID_VIEW_DATA, rProp.Value ) );
/*N*/                 else if ( aName == sFilterData )
/*N*/                   rSet.Put( SfxUnoAnyItem( SID_FILTER_DATA, rProp.Value ) );
/*N*/                 else if ( aName == sInputStream )
/*N*/                      {
/*N*/                         Reference< XInputStream > xVal;
/*N*/                         sal_Bool bOK = ((rProp.Value >>= xVal) && xVal.is());
/*N*/                         DBG_ASSERT( bOK, "invalid type for InputStream" )
/*N*/                         if (bOK)
/*N*/                             rSet.Put( SfxUnoAnyItem( SID_INPUTSTREAM, rProp.Value ) );
/*N*/                      }
/*N*/                 else if ( aName == sUCBContent )
/*N*/                      {
/*N*/                         Reference< XContent > xVal;
/*N*/                         sal_Bool bOK = ((rProp.Value >>= xVal) && xVal.is());
/*N*/                         DBG_ASSERT( bOK, "invalid type for UCBContent" )
/*N*/                         if (bOK)
/*N*/                             rSet.Put( SfxUnoAnyItem( SID_CONTENT, rProp.Value ) );
/*N*/                      }
/*N*/                 else if ( aName == sOutputStream )
/*N*/                      {
/*N*/                         Reference< XOutputStream > xVal;
/*N*/                         sal_Bool bOK = ((rProp.Value >>= xVal) && xVal.is());
/*N*/                         DBG_ASSERT( bOK, "invalid type for OutputStream" )
/*N*/                         if (bOK)
/*N*/                             rSet.Put( SfxUnoAnyItem( SID_OUTPUTSTREAM, rProp.Value ) );
/*N*/                      }
/*N*/                 else if ( aName == sPostData )
/*N*/                      {
/*N*/                         Reference< XInputStream > xVal;
/*N*/                         sal_Bool bOK = (rProp.Value >>= xVal);
/*N*/                         DBG_ASSERT( bOK, "invalid type for PostData" )
/*N*/                         if (bOK)
/*N*/                             rSet.Put( SfxUnoAnyItem( SID_POSTDATA, rProp.Value ) );
/*N*/                      }
/*N*/                 else if ( aName == sAsTemplate )
/*N*/                      {
/*N*/                         sal_Bool bVal = sal_False;
/*N*/                         sal_Bool bOK = (rProp.Value >>= bVal);
/*N*/                         DBG_ASSERT( bOK, "invalid type for AsTemplate" )
/*N*/                         if (bOK)
/*N*/                             rSet.Put( SfxBoolItem( SID_TEMPLATE, bVal ) );
/*N*/                      }
/*N*/                 else if ( aName == sOpenNewView )
/*N*/                      {
/*N*/                         sal_Bool bVal = sal_False;
/*N*/                         sal_Bool bOK = (rProp.Value >>= bVal);
/*N*/                         DBG_ASSERT( bOK, "invalid type for OpenNewView" )
/*N*/                         if (bOK)
/*N*/                             rSet.Put( SfxBoolItem( SID_OPEN_NEW_VIEW, bVal ) );
/*N*/                      }
/*N*/                 else if ( aName == sViewId )
/*N*/                      {
/*N*/                         sal_Int16 nVal = -1;
/*N*/                         sal_Bool bOK = ((rProp.Value >>= nVal) && (nVal != -1));
/*N*/                         DBG_ASSERT( bOK, "invalid type for ViewId" )
/*N*/                         if (bOK)
/*N*/                             rSet.Put( SfxUInt16Item( SID_VIEW_ID, nVal ) );
/*N*/                      }
/*N*/                 else if ( aName == sPluginMode )
/*N*/                      {
/*N*/                         sal_Int16 nVal = -1;
/*N*/                         sal_Bool bOK = ((rProp.Value >>= nVal) && (nVal != -1));
/*N*/                         DBG_ASSERT( bOK, "invalid type for PluginMode" )
/*N*/                         if (bOK)
/*N*/                             rSet.Put( SfxUInt16Item( SID_PLUGIN_MODE, nVal ) );
/*N*/                      }
/*N*/                 else if ( aName == sReadOnly )
/*N*/                      {
/*N*/                         sal_Bool bVal = sal_False;
/*N*/                         sal_Bool bOK = (rProp.Value >>= bVal);
/*N*/                         DBG_ASSERT( bOK, "invalid type for ReadOnly" )
/*N*/                         if (bOK)
/*N*/                             rSet.Put( SfxBoolItem( SID_DOC_READONLY, bVal ) );
/*N*/                      }
/*N*/                 else if ( aName == sStartPresentation )
/*N*/                      {
/*N*/                         sal_Bool bVal = sal_False;
/*N*/                         sal_Bool bOK = (rProp.Value >>= bVal);
/*N*/                         DBG_ASSERT( bOK, "invalid type for StartPresentation" )
/*N*/                         if (bOK)
/*N*/                             rSet.Put( SfxBoolItem( SID_DOC_STARTPRESENTATION, bVal ) );
/*N*/                      }
/*N*/                 else if ( aName == sSelectionOnly )
/*N*/                      {
/*N*/                         sal_Bool bVal = sal_False;
/*N*/                         sal_Bool bOK = (rProp.Value >>= bVal);
/*N*/                         DBG_ASSERT( bOK, "invalid type for SelectionOnly" )
/*N*/                         if (bOK)
/*N*/                            rSet.Put( SfxBoolItem( SID_SELECTION, bVal ) );
/*N*/                      }
/*N*/                 else if ( aName == sHidden )
/*N*/                      {
/*N*/                         sal_Bool bVal = sal_False;
/*N*/                         sal_Bool bOK = (rProp.Value >>= bVal);
/*N*/                         DBG_ASSERT( bOK, "invalid type for Hidden" )
/*N*/                         if (bOK)
/*N*/                             rSet.Put( SfxBoolItem( SID_HIDDEN, bVal ) );
/*N*/                      }
/*N*/                 else if ( aName == sMinimized )
/*N*/                      {
/*N*/                         sal_Bool bVal = sal_False;
/*N*/                         sal_Bool bOK = (rProp.Value >>= bVal);
/*N*/                         DBG_ASSERT( bOK, "invalid type for Minimized" )
/*N*/                         if (bOK)
/*N*/                             rSet.Put( SfxBoolItem( SID_MINIMIZEWINS, bVal ) );
/*N*/                      }
/*N*/                 else if ( aName == sSilent )
/*N*/                      {
/*N*/                         sal_Bool bVal = sal_False;
/*N*/                         sal_Bool bOK = (rProp.Value >>= bVal);
/*N*/                         DBG_ASSERT( bOK, "invalid type for Silent" )
/*N*/                         if (bOK)
/*N*/                             rSet.Put( SfxBoolItem( SID_SILENT, bVal ) );
/*N*/                      }
/*N*/                 else if ( aName == sPreview )
/*N*/                      {
/*N*/                         sal_Bool bVal = sal_False;
/*N*/                         sal_Bool bOK = (rProp.Value >>= bVal);
/*N*/                         DBG_ASSERT( bOK, "invalid type for Preview" )
/*N*/                         if (bOK)
/*N*/                             rSet.Put( SfxBoolItem( SID_PREVIEW, bVal ) );
/*N*/                      }
/*N*/                 else if ( aName == sViewOnly )
/*N*/                      {
/*N*/                         sal_Bool bVal = sal_False;
/*N*/                         sal_Bool bOK = (rProp.Value >>= bVal);
/*N*/                         DBG_ASSERT( bOK, "invalid type for ViewOnly" )
/*N*/                         if (bOK)
/*N*/                             rSet.Put( SfxBoolItem( SID_VIEWONLY, bVal ) );
/*N*/                      }
/*N*/                 else if ( aName == sDontEdit )
/*N*/                      {
/*N*/                         sal_Bool bVal = sal_False;
/*N*/                         sal_Bool bOK = (rProp.Value >>= bVal);
/*N*/                         DBG_ASSERT( bOK, "invalid type for ViewOnly" )
/*N*/                         if (bOK)
/*N*/                             rSet.Put( SfxBoolItem( SID_EDITDOC, !bVal ) );
/*N*/                      }
/*N*/                 else if ( aName == sFileName )
/*N*/                      {
/*N*/                         ::rtl::OUString sVal;
/*N*/                         sal_Bool bOK = ((rProp.Value >>= sVal) && sVal.getLength());
/*N*/                         DBG_ASSERT( bOK, "invalid type or value for FileName" )
/*N*/                         if (bOK)
/*N*/                             rSet.Put( SfxStringItem( SID_FILE_NAME, sVal ) );
/*N*/                      }
/*N*/                 else if ( aName == sOrigURL )
/*N*/                      {
/*N*/                         ::rtl::OUString sVal;
/*N*/                         sal_Bool bOK = ((rProp.Value >>= sVal) && sVal.getLength());
/*N*/                         DBG_ASSERT( bOK, "invalid type or value for OrigURL" )
/*N*/                         if (bOK)
/*N*/                             rSet.Put( SfxStringItem( SID_ORIGURL, sVal ) );
/*N*/                      }
/*N*/                 else if ( aName == sSalvageURL )
/*N*/                      {
/*N*/                         ::rtl::OUString sVal;
/*N*/                         sal_Bool bOK = (rProp.Value >>= sVal);
/*N*/                         DBG_ASSERT( bOK, "invalid type or value for SalvageURL" )
/*N*/                         if (bOK)
/*N*/                             rSet.Put( SfxStringItem( SID_DOC_SALVAGE, sVal ) );
/*N*/                      }
/*N*/                 else if ( aName == sFrameName )
/*N*/                      {
/*N*/                         ::rtl::OUString sVal;
/*N*/                         sal_Bool bOK = (rProp.Value >>= sVal);
/*N*/                         DBG_ASSERT( bOK, "invalid type for FrameName" )
/*N*/                         if (bOK && sVal.getLength())
/*N*/                             rSet.Put( SfxStringItem( SID_TARGETNAME, sVal ) );
/*N*/                      }
/*N*/                 else if ( aName == sMediaType )
/*N*/                      {
/*N*/                         ::rtl::OUString sVal;
/*N*/                         sal_Bool bOK = ((rProp.Value >>= sVal) && sVal.getLength());
/*N*/                         DBG_ASSERT( bOK, "invalid type or value for MediaType" )
/*N*/                         if (bOK)
/*N*/                             rSet.Put( SfxStringItem( SID_CONTENTTYPE, sVal ) );
/*N*/                      }
/*N*/                 else if ( aName == sWindowState )
/*N*/                      {
/*N*/                         ::rtl::OUString sVal;
/*N*/                         sal_Bool bOK = ((rProp.Value >>= sVal) && sVal.getLength());
/*N*/                         DBG_ASSERT( bOK, "invalid type or value for WindowState" )
/*N*/                         if (bOK)
/*N*/                             rSet.Put( SfxStringItem( SID_WIN_POSSIZE, sVal ) );
/*N*/                      }
/*N*/                 else if ( aName == sTemplateName )
/*N*/                      {
/*N*/                         ::rtl::OUString sVal;
/*N*/                         sal_Bool bOK = ((rProp.Value >>= sVal) && sVal.getLength());
/*N*/                         DBG_ASSERT( bOK, "invalid type or value for TemplateName" )
/*N*/                         if (bOK)
/*N*/                             rSet.Put( SfxStringItem( SID_TEMPLATE_NAME, sVal ) );
/*N*/                      }
/*N*/                 else if ( aName == sTemplateRegionName )
/*N*/                      {
/*N*/                         ::rtl::OUString sVal;
/*N*/                         sal_Bool bOK = ((rProp.Value >>= sVal) && sVal.getLength());
/*N*/                         DBG_ASSERT( bOK, "invalid type or value for TemplateRegionName" )
/*N*/                         if (bOK)
/*N*/                             rSet.Put( SfxStringItem( SID_TEMPLATE_REGIONNAME, sVal ) );
/*N*/                      }
/*N*/                 else if ( aName == sJumpMark )
/*N*/                      {
/*N*/                         ::rtl::OUString sVal;
/*N*/                         sal_Bool bOK = ((rProp.Value >>= sVal) && sVal.getLength());
/*N*/                         DBG_ASSERT( bOK, "invalid type or value for JumpMark" )
/*N*/                         if (bOK)
/*N*/                             rSet.Put( SfxStringItem( SID_JUMPMARK, sVal ) );
/*N*/                      }
/*N*/                 else if ( aName == sCharacterSet )
/*N*/                      {
/*N*/                         ::rtl::OUString sVal;
/*N*/                         sal_Bool bOK = ((rProp.Value >>= sVal) && sVal.getLength());
/*N*/                         DBG_ASSERT( bOK, "invalid type or value for CharacterSet" )
/*N*/                         if (bOK)
/*N*/                             rSet.Put( SfxStringItem( SID_CHARSET, sVal ) );
/*N*/                      }
/*N*/                 else if ( aName == sFilterFlags )
/*N*/                      {
/*N*/                         ::rtl::OUString sVal;
/*N*/                         sal_Bool bOK = ((rProp.Value >>= sVal) && sVal.getLength());
/*N*/                         DBG_ASSERT( bOK, "invalid type or value for FilterFlags" )
/*N*/                         if (bOK)
/*N*/                             rSet.Put( SfxStringItem( SID_FILE_FILTEROPTIONS, sVal ) );
/*N*/                      }
/*N*/                 else if ( aName == sMacroExecMode )
/*N*/                 {
/*N*/                     sal_Int16 nVal =-1;
/*N*/                     sal_Bool bOK = ((rProp.Value >>= nVal) && (nVal != -1));
/*N*/                     DBG_ASSERT( bOK, "invalid type for MacroExecMode" )
/*N*/                     if (bOK)
/*N*/                         rSet.Put( SfxUInt16Item( SID_MACROEXECMODE, nVal ) );
/*N*/                 }
/*N*/                 else if ( aName == sUpdateDocMode )
/*N*/               {
/*N*/                     sal_Int16 nVal =-1;
/*N*/                     sal_Bool bOK = ((rProp.Value >>= nVal) && (nVal != -1));
/*N*/                     DBG_ASSERT( bOK, "invalid type for UpdateDocMode" )
/*N*/                     if (bOK)
/*N*/                         rSet.Put( SfxUInt16Item( SID_UPDATEDOCMODE, nVal ) );
/*N*/               }
/*N*/                 else if ( aName == sRepairPackage )
/*N*/                      {
/*N*/                         sal_Bool bVal = sal_False;
/*N*/                         sal_Bool bOK = (rProp.Value >>= bVal);
/*N*/                         DBG_ASSERT( bOK, "invalid type for RepairPackage" )
/*N*/                         if (bOK)
/*N*/                            rSet.Put( SfxBoolItem( SID_REPAIRPACKAGE, bVal ) );
/*N*/                      }
/*N*/                 else if ( aName == sDocumentTitle )
/*N*/                      {
/*N*/                         ::rtl::OUString sVal;
/*N*/                         sal_Bool bOK = ((rProp.Value >>= sVal) && sVal.getLength());
/*N*/                         DBG_ASSERT( bOK, "invalid type or value for DocumentTitle" )
/*N*/                         if (bOK)
/*N*/                             rSet.Put( SfxStringItem( SID_DOCINFO_TITLE, sVal ) );
/*N*/                      }
/*N*/
/*N*/             }
/*N*/         }
/*N*/ #ifdef DB_UTIL
/*N*/         else if ( nFoundArgs == nCount )
/*N*/         {
/*N*/             // except for the "special" slots: assure that every argument was convertable
/*N*/             ByteString aStr( "MacroPlayer: Some properties didn't match to any formal argument for slot: ");
/*N*/             aStr += pSlot->pUnoName;
/*N*/             DBG_WARNING( aStr.GetBuffer() );
/*N*/         }
/*N*/ #endif
/*N*/     }
/*N*/ }

/*N*/ void TransformItems( sal_uInt16 nSlotId, const SfxItemSet& rSet, ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue>& rArgs, const SfxSlot* pSlot )
/*N*/ {
/*N*/     if ( !pSlot )
/*N*/         pSlot = SFX_SLOTPOOL().GetSlot( nSlotId );
/*N*/
/*N*/     if ( !pSlot)
/*N*/         return;
/*N*/
/*N*/     if ( nSlotId == SID_OPENURL )
/*N*/         nSlotId = SID_OPENDOC;
/*N*/     if ( nSlotId == SID_SAVEASURL )
/*N*/         nSlotId = SID_SAVEASDOC;
/*N*/
/*N*/     // find number of properties to avoid permanent reallocations in the sequence
/*N*/     sal_Int32 nProps=0;
/*N*/
/*N*/ #ifdef DBG_UTIL
/*N*/     // trace number of items and compare with number of properties for debugging purposes
/*N*/     sal_Int32 nItems=0;
/*N*/ #endif
/*N*/
/*N*/     const SfxType *pType = pSlot->GetType();
/*N*/     if ( !pSlot->IsMode(SFX_SLOT_METHOD) )
/*N*/     {
/*N*/         // slot is a property
/*N*/         USHORT nWhich = rSet.GetPool()->GetWhich(nSlotId);
/*N*/         if ( rSet.GetItemState( nWhich ) == SFX_ITEM_SET ) //???
/*N*/         {
/*N*/             USHORT nSubCount = pType->nAttribs;
/*N*/             if ( nSubCount )
/*N*/                 // it's a complex property, we want it split into simple types
/*N*/                 // so we expect to get as many items as we have (sub) members
/*N*/                 nProps = nSubCount;
/*N*/             else
/*N*/                 // simple property: we expect to get exactly one item
/*N*/                 nProps++;
/*N*/         }
/*N*/ #ifdef DBG_UTIL
/*N*/         else
/*N*/         {
/*N*/             // we will not rely on the "toggle" ability of some property slots
/*N*/             ByteString aStr( "Processing property slot without argument: ");
/*N*/             aStr += ByteString::CreateFromInt32( nSlotId );
/*N*/             DBG_ERROR( aStr.GetBuffer() );
/*N*/         }
/*N*/ #endif
/*N*/
/*N*/ #ifdef DBG_UTIL
/*N*/         nItems++;
/*N*/ #endif
/*N*/     }
/*N*/     else
/*N*/     {
/*N*/         // slot is a method
/*N*/         USHORT nFormalArgs = pSlot->GetFormalArgumentCount();
/*N*/         for ( USHORT nArg=0; nArg<nFormalArgs; ++nArg )
/*N*/       {
/*N*/             // check every formal argument of the method
/*N*/             const SfxFormalArgument &rArg = pSlot->GetFormalArgument( nArg );
/*N*/             USHORT nWhich = rSet.GetPool()->GetWhich( rArg.nSlotId );
/*N*/             if ( rSet.GetItemState( nWhich ) == SFX_ITEM_SET ) //???
/*N*/             {
/*N*/                 USHORT nSubCount = rArg.pType->nAttribs;
/*N*/                 if ( nSubCount )
/*N*/                     // argument has a complex type, we want it split into simple types
/*N*/                     // so for this argument we expect to get as many items as we have (sub) members
/*N*/                     nProps += nSubCount;
/*N*/                 else
/*N*/                     // argument of simple type: we expect to get exactly one item for it
/*N*/                     nProps++;
/*N*/ #ifdef DBG_UTIL
/*N*/                 nItems++;
/*N*/ #endif
/*N*/             }
/*N*/         }
/*N*/
/*N*/         // special treatment for slots that are *not* meant to be recorded as slots (except SaveAs/To)
/*N*/         if ( nSlotId == SID_OPENDOC || nSlotId == SID_EXPORTDOC || nSlotId == SID_SAVEASDOC ||
/*N*/            nSlotId == SID_SAVETO || nSlotId == SID_EXPORTDOCASPDF || nSlotId == SID_DIRECTEXPORTDOCASPDF )
/*N*/         {
/*N*/             sal_Int32 nAdditional=0;
/*N*/             if ( rSet.GetItemState( SID_PROGRESS_STATUSBAR_CONTROL ) == SFX_ITEM_SET )
/*N*/                 nAdditional++;
/*N*/             if ( rSet.GetItemState( SID_INTERACTIONHANDLER ) == SFX_ITEM_SET )
/*N*/                 nAdditional++;
/*N*/             if ( rSet.GetItemState( SID_ORIGURL ) == SFX_ITEM_SET )
/*N*/                 nAdditional++;
/*N*/             if ( rSet.GetItemState( SID_DOC_SALVAGE ) == SFX_ITEM_SET )
/*N*/                 nAdditional++;
/*N*/             if ( rSet.GetItemState( SID_CONTENT ) == SFX_ITEM_SET )
/*N*/                 nAdditional++;
/*N*/             if ( rSet.GetItemState( SID_INPUTSTREAM ) == SFX_ITEM_SET )
/*N*/                 nAdditional++;
/*N*/             if ( rSet.GetItemState( SID_OUTPUTSTREAM ) == SFX_ITEM_SET )
/*N*/                 nAdditional++;
/*N*/             if ( rSet.GetItemState( SID_TEMPLATE ) == SFX_ITEM_SET )
/*N*/                 nAdditional++;
/*N*/             if ( rSet.GetItemState( SID_OPEN_NEW_VIEW ) == SFX_ITEM_SET )
/*N*/                 nAdditional++;
/*N*/             if ( rSet.GetItemState( SID_VIEW_ID ) == SFX_ITEM_SET )
/*N*/                 nAdditional++;
/*N*/             if ( rSet.GetItemState( SID_VIEW_DATA ) == SFX_ITEM_SET )
/*N*/                 nAdditional++;
/*N*/             if ( rSet.GetItemState( SID_FILTER_DATA ) == SFX_ITEM_SET )
/*N*/                 nAdditional++;
/*N*/             if ( rSet.GetItemState( SID_PLUGIN_MODE ) == SFX_ITEM_SET )
/*N*/                 nAdditional++;
/*N*/             if ( rSet.GetItemState( SID_DOC_READONLY ) == SFX_ITEM_SET )
/*N*/                 nAdditional++;
/*N*/             if ( rSet.GetItemState( SID_DOC_STARTPRESENTATION ) == SFX_ITEM_SET )
/*N*/                 nAdditional++;
/*N*/             if ( rSet.GetItemState( SID_SELECTION ) == SFX_ITEM_SET )
/*N*/                 nAdditional++;
/*N*/             if ( rSet.GetItemState( SID_CONTENTTYPE ) == SFX_ITEM_SET )
/*N*/                 nAdditional++;
/*N*/             if ( rSet.GetItemState( SID_WIN_POSSIZE ) == SFX_ITEM_SET )
/*N*/                 nAdditional++;
/*N*/     //        if ( rSet.GetItemState( SID_VIEW_POS_SIZE ) == SFX_ITEM_SET )
/*N*/     //            nAdditional++;
/*N*/             if ( rSet.GetItemState( SID_POSTDATA ) == SFX_ITEM_SET )
/*N*/                 nAdditional++;
/*N*/             if ( rSet.GetItemState( SID_CHARSET ) == SFX_ITEM_SET )
/*N*/                 nAdditional++;
/*N*/             if ( rSet.GetItemState( SID_TARGETNAME ) == SFX_ITEM_SET )
/*N*/                 nAdditional++;
/*N*/             if ( rSet.GetItemState( SID_TEMPLATE_NAME ) == SFX_ITEM_SET )
/*N*/                 nAdditional++;
/*N*/             if ( rSet.GetItemState( SID_TEMPLATE_REGIONNAME ) == SFX_ITEM_SET )
/*N*/                 nAdditional++;
/*N*/             if ( rSet.GetItemState( SID_HIDDEN ) == SFX_ITEM_SET )
/*N*/                 nAdditional++;
/*N*/             if ( rSet.GetItemState( SID_MINIMIZEWINS ) == SFX_ITEM_SET )
/*N*/                 nAdditional++;
/*N*/             if ( rSet.GetItemState( SID_PREVIEW ) == SFX_ITEM_SET )
/*N*/                 nAdditional++;
/*N*/             if ( rSet.GetItemState( SID_VIEWONLY ) == SFX_ITEM_SET )
/*N*/                 nAdditional++;
/*N*/             if ( rSet.GetItemState( SID_EDITDOC ) == SFX_ITEM_SET )
/*N*/                 nAdditional++;
/*N*/             if ( rSet.GetItemState( SID_SILENT ) == SFX_ITEM_SET )
/*N*/                 nAdditional++;
/*N*/             if ( rSet.GetItemState( SID_JUMPMARK ) == SFX_ITEM_SET )
/*N*/                 nAdditional++;
/*N*/             if ( rSet.GetItemState( SID_DOCUMENT ) == SFX_ITEM_SET )
/*N*/                 nAdditional++;
/*N*/             if ( rSet.GetItemState( SID_MACROEXECMODE ) == SFX_ITEM_SET )
/*N*/                 nAdditional++;
/*N*/             if ( rSet.GetItemState( SID_UPDATEDOCMODE ) == SFX_ITEM_SET )
/*N*/                 nAdditional++;
/*N*/             if ( rSet.GetItemState( SID_REPAIRPACKAGE ) == SFX_ITEM_SET )
/*N*/                 nAdditional++;
/*N*/             if ( rSet.GetItemState( SID_DOCINFO_TITLE ) == SFX_ITEM_SET )
/*N*/                 nAdditional++;
/*N*/
/*N*/             // consider additional arguments
/*N*/             nProps += nAdditional;
/*N*/ #ifdef DBG_UTIL
/*N*/             nItems += nAdditional;
/*N*/ #endif
/*N*/         }
/*N*/     }
/*N*/
/*N*/ #ifdef DBG_UTIL
/*N*/     // now check the itemset: is there any item that is not convertable using the list of formal arguments
/*N*/     // or the table of additional items?!
/*N*/     if ( rSet.Count() != nItems )
/*N*/     {
/*N*/         // detect unknown item and present error message
/*N*/         const USHORT *pRanges = rSet.GetRanges();
/*N*/         while ( *pRanges )
/*N*/         {
/*N*/             for(USHORT nId = *pRanges++; nId <= *pRanges; ++nId)
/*N*/             {
/*N*/                 if ( rSet.GetItemState(nId) < SFX_ITEM_SET ) //???
/*N*/                     // not really set
/*N*/                     continue;
/*N*/
/*N*/                 if ( !pSlot->IsMode(SFX_SLOT_METHOD) && nId == rSet.GetPool()->GetWhich( pSlot->GetSlotId() ) )
/*N*/                     continue;
/*N*/
/*N*/                 USHORT nFormalArgs = pSlot->GetFormalArgumentCount();
/*N*/                 USHORT nArg; for ( nArg=0; nArg<nFormalArgs; ++nArg )
/*N*/                 {
/*N*/                     const SfxFormalArgument &rArg = pSlot->GetFormalArgument( nArg );
/*N*/                     USHORT nWhich = rSet.GetPool()->GetWhich( rArg.nSlotId );
/*N*/                     if ( nId == nWhich )
/*N*/                         break;
/*N*/                 }
/*N*/
/*N*/                 if ( nArg<nFormalArgs )
/*N*/                     continue;
/*N*/
/*N*/                 if ( nSlotId == SID_OPENDOC || nSlotId == SID_EXPORTDOC || nSlotId == SID_SAVEASDOC ||
/*N*/                    nSlotId == SID_SAVETO || nSlotId == SID_EXPORTDOCASPDF || nSlotId == SID_DIRECTEXPORTDOCASPDF )
/*N*/                 {
/*N*/                     if ( nId == SID_DOCFRAME )
/*N*/                         continue;
/*N*/                     if ( nId == SID_PROGRESS_STATUSBAR_CONTROL )
/*N*/                         continue;
/*N*/                     if ( nId == SID_INTERACTIONHANDLER )
/*N*/                         continue;
/*N*/                     if ( nId == SID_VIEW_DATA )
/*N*/                         continue;
/*N*/                     if ( nId == SID_FILTER_DATA )
/*N*/                         continue;
/*N*/                     if ( nId == SID_DOCUMENT )
/*N*/                         continue;
/*N*/                     if ( nId == SID_CONTENT )
/*N*/                         continue;
/*N*/                     if ( nId == SID_INPUTSTREAM )
/*N*/                         continue;
/*N*/                     if ( nId == SID_OUTPUTSTREAM )
/*N*/                         continue;
/*N*/                     if ( nId == SID_POSTDATA )
/*N*/                         continue;
/*N*/                     if ( nId == SID_TEMPLATE )
/*N*/                         continue;
/*N*/                     if ( nId == SID_OPEN_NEW_VIEW )
/*N*/                         continue;
/*N*/                     if ( nId == SID_VIEW_ID )
/*N*/                         continue;
/*N*/                     if ( nId == SID_PLUGIN_MODE )
/*N*/                         continue;
/*N*/                     if ( nId == SID_DOC_READONLY )
/*N*/                         continue;
/*N*/                     if ( nId == SID_DOC_STARTPRESENTATION )
/*N*/                         continue;
/*N*/                     if ( nId == SID_SELECTION )
/*N*/                         continue;
/*N*/                     if ( nId == SID_HIDDEN )
/*N*/                         continue;
/*N*/                     if ( nId == SID_MINIMIZEWINS )
/*N*/                         continue;
/*N*/                     if ( nId == SID_SILENT )
/*N*/                         continue;
/*N*/                     if ( nId == SID_PREVIEW )
/*N*/                         continue;
/*N*/                     if ( nId == SID_VIEWONLY )
/*N*/                         continue;
/*N*/                     if ( nId == SID_EDITDOC )
/*N*/                         continue;
/*N*/                     if ( nId == SID_TARGETNAME )
/*N*/                         continue;
/*N*/                     if ( nId == SID_ORIGURL )
/*N*/                         continue;
/*N*/                     if ( nId == SID_DOC_SALVAGE )
/*N*/                         continue;
/*N*/                     if ( nId == SID_CONTENTTYPE )
/*N*/                         continue;
/*N*/                     if ( nId == SID_WIN_POSSIZE )
/*N*/                         continue;
/*N*/                     if ( nId == SID_TEMPLATE_NAME )
/*N*/                         continue;
/*N*/                     if ( nId == SID_TEMPLATE_REGIONNAME )
/*N*/                         continue;
/*N*/                     if ( nId == SID_JUMPMARK )
/*N*/                         continue;
/*N*/                     if ( nId == SID_CHARSET )
/*N*/                         continue;
/*N*/                     if ( nId == SID_MACROEXECMODE )
/*N*/                         continue;
/*N*/                     if ( nId == SID_UPDATEDOCMODE )
/*N*/                         continue;
/*N*/                     if ( nId == SID_REPAIRPACKAGE )
/*N*/                         continue;
/*N*/                     if ( nId == SID_DOCINFO_TITLE )
/*N*/                         continue;
/*N*/
/*N*/                     // used only internally
/*N*/                     if ( nId == SID_SAVETO )
/*N*/                         continue;
/*N*/                     if ( nId == SID_VIEW )
/*N*/                         continue;
/*N*/                 }
/*N*/
/*N*/                 ByteString aDbg( "Unknown item detected: ");
/*N*/                 aDbg += ByteString::CreateFromInt32( nId );
/*N*/                 DBG_ASSERT( nArg<nFormalArgs, aDbg.GetBuffer() );
/*N*/             }
/*N*/         }
/*N*/     }
/*N*/ #endif
/*N*/
/*N*/     if ( !nProps )
/*N*/         return;
/*N*/
/*N*/     // convert every item into a property
/*N*/     ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue> aSequ( nProps );
/*N*/     ::com::sun::star::beans::PropertyValue *pValue = aSequ.getArray();
/*N*/     nProps = 0;
/*N*/     if ( !pSlot->IsMode(SFX_SLOT_METHOD) )
/*N*/     {
/*N*/         // slot is a property
/*N*/         USHORT nWhich = rSet.GetPool()->GetWhich(nSlotId);
/*N*/         BOOL bConvertTwips = ( rSet.GetPool()->GetMetric( nWhich ) == SFX_MAPUNIT_TWIP );
/*N*/         SFX_ITEMSET_ARG( &rSet, pItem, SfxPoolItem, nWhich, sal_False );
/*N*/         if ( pItem ) //???
/*N*/         {
/*N*/             USHORT nSubCount = pType->nAttribs;
/*N*/             if ( !nSubCount )
/*N*/           {
/*N*/                 //rPool.FillVariable( *pItem, *pVar, eUserMetric );
/*N*/               pValue[nProps].Name = String( String::CreateFromAscii( pSlot->pUnoName ) ) ;
/*N*/                 if ( !pItem->QueryValue( pValue[nProps].Value ) )
/*N*/                 {
/*N*/                     ByteString aStr( "Item not convertable: ");
/*N*/                     aStr += ByteString::CreateFromInt32(nSlotId);
/*N*/                     DBG_ERROR( aStr.GetBuffer() );
/*N*/                 }
/*N*/           }
/*N*/           else
/*N*/           {
/*N*/                 // complex type, add a property value for every member of the struct
/*N*/                 for ( USHORT n=1; n<=nSubCount; ++n )
/*N*/               {
/*N*/                     //rPool.FillVariable( *pItem, *pVar, eUserMetric );
/*N*/                     BYTE nSubId = (BYTE) (sal_Int8) pType->aAttrib[n-1].nAID;
/*N*/                     if ( bConvertTwips )
/*N*/                         nSubId |= CONVERT_TWIPS;
/*N*/
/*N*/                     DBG_ASSERT( nSubId <= 255, "Member ID out of range" );
/*N*/                   String aName( String::CreateFromAscii( pSlot->pUnoName ) ) ;
/*N*/                   aName += '.';
/*N*/                     aName += String( String::CreateFromAscii( pType->aAttrib[n-1].pName ) ) ;
/*N*/                   pValue[nProps].Name = aName;
/*N*/                     if ( !pItem->QueryValue( pValue[nProps++].Value, nSubId ) )
/*N*/                     {
/*N*/                         ByteString aStr( "Sub item ");
/*N*/                         aStr += ByteString::CreateFromInt32( pType->aAttrib[n-1].nAID );
/*N*/                         aStr += " not convertable in slot: ";
/*N*/                         aStr += ByteString::CreateFromInt32(nSlotId);
/*N*/                         DBG_ERROR( aStr.GetBuffer() );
/*N*/                     }
/*N*/               }
/*N*/           }
/*N*/         }
/*N*/     }
/*N*/     else
/*N*/     {
/*N*/         // slot is a method
/*N*/         USHORT nFormalArgs = pSlot->GetFormalArgumentCount();
/*N*/         for ( USHORT nArg=0; nArg<nFormalArgs; ++nArg )
/*N*/       {
/*N*/             const SfxFormalArgument &rArg = pSlot->GetFormalArgument( nArg );
/*N*/             USHORT nWhich = rSet.GetPool()->GetWhich( rArg.nSlotId );
/*N*/             BOOL bConvertTwips = ( rSet.GetPool()->GetMetric( nWhich ) == SFX_MAPUNIT_TWIP );
/*N*/             SFX_ITEMSET_ARG( &rSet, pItem, SfxPoolItem, nWhich, sal_False );
/*N*/             if ( pItem ) //???
/*N*/             {
/*N*/                 USHORT nSubCount = rArg.pType->nAttribs;
/*N*/                 if ( !nSubCount )
/*N*/                 {
/*N*/                     //rPool.FillVariable( *pItem, *pVar, eUserMetric );
/*N*/                   pValue[nProps].Name = String( String::CreateFromAscii( rArg.pName ) ) ;
/*N*/                     if ( !pItem->QueryValue( pValue[nProps++].Value ) )
/*N*/                     {
/*N*/                         ByteString aStr( "Item not convertable: ");
/*N*/                         aStr += ByteString::CreateFromInt32(rArg.nSlotId);
/*N*/                         DBG_ERROR( aStr.GetBuffer() );
/*N*/                     }
/*N*/                 }
/*N*/                 else
/*N*/                 {
/*N*/                     // complex type, add a property value for every member of the struct
/*N*/                     for ( USHORT n = 1; n <= nSubCount; ++n )
/*N*/                     {
/*N*/                         //rPool.FillVariable( rItem, *pVar, eUserMetric );
/*N*/                         BYTE nSubId = (BYTE) (sal_Int8) rArg.pType->aAttrib[n-1].nAID;
/*N*/                         if ( bConvertTwips )
/*N*/                             nSubId |= CONVERT_TWIPS;
/*N*/
/*N*/                         DBG_ASSERT( nSubId <= 255, "Member ID out of range" );
/*N*/                       String aName( String::CreateFromAscii( rArg.pName ) ) ;
/*N*/                       aName += '.';
/*N*/                       aName += String( String::CreateFromAscii( rArg.pType->aAttrib[n-1].pName ) ) ;
/*N*/                       pValue[nProps].Name = aName;
/*N*/                         if ( !pItem->QueryValue( pValue[nProps++].Value, nSubId ) )
/*N*/                         {
/*N*/                             ByteString aStr( "Sub item ");
/*N*/                             aStr += ByteString::CreateFromInt32( rArg.pType->aAttrib[n-1].nAID );
/*N*/                             aStr += " not convertable in slot: ";
/*N*/                             aStr += ByteString::CreateFromInt32(rArg.nSlotId);
/*N*/                             DBG_ERROR( aStr.GetBuffer() );
/*N*/                         }
/*N*/                     }
/*N*/                 }
/*N*/             }
/*N*/       }
/*N*/
/*N*/         if ( nSlotId == SID_OPENDOC || nSlotId == SID_EXPORTDOC || nSlotId == SID_SAVEASDOC ||
/*N*/            nSlotId == SID_SAVETO || nSlotId == SID_EXPORTDOCASPDF || nSlotId == SID_DIRECTEXPORTDOCASPDF )
/*N*/         {
/*N*/             const SfxPoolItem *pItem=0;
/*N*/             if ( rSet.GetItemState( SID_PROGRESS_STATUSBAR_CONTROL, sal_False, &pItem ) == SFX_ITEM_SET )
/*N*/             {
/*N*/                 pValue[nProps].Name = sStatusInd;
/*N*/                 pValue[nProps++].Value = ( ((SfxUnoAnyItem*)pItem)->GetValue() );
/*N*/             }
/*N*/             if ( rSet.GetItemState( SID_INTERACTIONHANDLER, sal_False, &pItem ) == SFX_ITEM_SET )
/*N*/             {
/*N*/                 pValue[nProps].Name = sInteractionHdl;
/*N*/                 pValue[nProps++].Value = ( ((SfxUnoAnyItem*)pItem)->GetValue() );
/*N*/             }
/*N*/             if ( rSet.GetItemState( SID_VIEW_DATA, sal_False, &pItem ) == SFX_ITEM_SET )
/*N*/             {
/*N*/                 pValue[nProps].Name = sViewData;
/*N*/                 pValue[nProps++].Value = ( ((SfxUnoAnyItem*)pItem)->GetValue() );
/*N*/             }
/*N*/             if ( rSet.GetItemState( SID_FILTER_DATA, sal_False, &pItem ) == SFX_ITEM_SET )
/*N*/             {
/*N*/                 pValue[nProps].Name = sFilterData;
/*N*/                 pValue[nProps++].Value = ( ((SfxUnoAnyItem*)pItem)->GetValue() );
/*N*/             }
/*N*/             if ( rSet.GetItemState( SID_DOCUMENT, sal_False, &pItem ) == SFX_ITEM_SET )
/*N*/             {
/*N*/                 pValue[nProps].Name = sModel;
/*N*/                 pValue[nProps++].Value = ( ((SfxUnoAnyItem*)pItem)->GetValue() );
/*N*/             }
/*N*/             if ( rSet.GetItemState( SID_CONTENT, sal_False, &pItem ) == SFX_ITEM_SET )
/*N*/             {
/*N*/                 pValue[nProps].Name = sUCBContent;
/*N*/                 pValue[nProps++].Value = ( ((SfxUnoAnyItem*)pItem)->GetValue() );
/*N*/             }
/*N*/             if ( rSet.GetItemState( SID_INPUTSTREAM, sal_False, &pItem ) == SFX_ITEM_SET )
/*N*/             {
/*N*/                 pValue[nProps].Name = sInputStream;
/*N*/                 pValue[nProps++].Value = ( ((SfxUnoAnyItem*)pItem)->GetValue() );
/*N*/             }
/*N*/             if ( rSet.GetItemState( SID_OUTPUTSTREAM, sal_False, &pItem ) == SFX_ITEM_SET )
/*N*/             {
/*N*/                 pValue[nProps].Name = sOutputStream;
/*N*/                 pValue[nProps++].Value = ( ((SfxUnoAnyItem*)pItem)->GetValue() );
/*N*/             }
/*N*/             if ( rSet.GetItemState( SID_POSTDATA, sal_False, &pItem ) == SFX_ITEM_SET )
/*N*/             {
/*N*/                 pValue[nProps].Name = sPostData;
/*N*/                 pValue[nProps++].Value = ( ((SfxUnoAnyItem*)pItem)->GetValue() );
/*N*/             }
/*N*/             if ( rSet.GetItemState( SID_TEMPLATE, sal_False, &pItem ) == SFX_ITEM_SET )
/*N*/             {
/*N*/                 pValue[nProps].Name = sAsTemplate;
/*N*/                 pValue[nProps++].Value <<= ( ((SfxBoolItem*)pItem)->GetValue() );
/*N*/             }
/*N*/             if ( rSet.GetItemState( SID_OPEN_NEW_VIEW, sal_False, &pItem ) == SFX_ITEM_SET )
/*N*/             {
/*N*/                 pValue[nProps].Name = sOpenNewView;
/*N*/                 pValue[nProps++].Value <<= ( ((SfxBoolItem*)pItem)->GetValue() );
/*N*/             }
/*N*/             if ( rSet.GetItemState( SID_VIEW_ID, sal_False, &pItem ) == SFX_ITEM_SET )
/*N*/             {
/*N*/                 pValue[nProps].Name = sViewId;
/*N*/                 pValue[nProps++].Value <<= ( (sal_Int16) ((SfxUInt16Item*)pItem)->GetValue() );
/*N*/             }
/*N*/             if ( rSet.GetItemState( SID_PLUGIN_MODE, sal_False, &pItem ) == SFX_ITEM_SET )
/*N*/             {
/*N*/                 pValue[nProps].Name = sPluginMode;
/*N*/                 pValue[nProps++].Value <<= ( (sal_Int16) ((SfxUInt16Item*)pItem)->GetValue() );
/*N*/             }
/*N*/             if ( rSet.GetItemState( SID_DOC_READONLY, sal_False, &pItem ) == SFX_ITEM_SET )
/*N*/             {
/*N*/                 pValue[nProps].Name = sReadOnly;
/*N*/                 pValue[nProps++].Value <<= ( ((SfxBoolItem*)pItem)->GetValue() );
/*N*/             }
/*N*/             if ( rSet.GetItemState( SID_DOC_STARTPRESENTATION, sal_False, &pItem ) == SFX_ITEM_SET )
/*N*/             {
/*N*/                 pValue[nProps].Name = sStartPresentation;
/*N*/                 pValue[nProps++].Value <<= ( ((SfxBoolItem*)pItem)->GetValue() );
/*N*/             }
/*N*/             if ( rSet.GetItemState( SID_SELECTION, sal_False, &pItem ) == SFX_ITEM_SET )
/*N*/             {
/*N*/                 pValue[nProps].Name = sSelectionOnly;
/*N*/                 pValue[nProps++].Value <<= ( ((SfxBoolItem*)pItem)->GetValue() );
/*N*/             }
/*N*/             if ( rSet.GetItemState( SID_HIDDEN, sal_False, &pItem ) == SFX_ITEM_SET )
/*N*/             {
/*N*/                 pValue[nProps].Name = sHidden;
/*N*/                 pValue[nProps++].Value <<= ( ((SfxBoolItem*)pItem)->GetValue() );
/*N*/             }
/*N*/             if ( rSet.GetItemState( SID_MINIMIZEWINS, sal_False, &pItem ) == SFX_ITEM_SET )
/*N*/             {
/*N*/                 pValue[nProps].Name = sMinimized;
/*N*/                 pValue[nProps++].Value <<= ( ((SfxBoolItem*)pItem)->GetValue() );
/*N*/             }
/*N*/             if ( rSet.GetItemState( SID_SILENT, sal_False, &pItem ) == SFX_ITEM_SET )
/*N*/             {
/*N*/                 pValue[nProps].Name = sSilent;
/*N*/                 pValue[nProps++].Value <<= ( ((SfxBoolItem*)pItem)->GetValue() );
/*N*/             }
/*N*/             if ( rSet.GetItemState( SID_PREVIEW, sal_False, &pItem ) == SFX_ITEM_SET )
/*N*/             {
/*N*/                 pValue[nProps].Name = sPreview;
/*N*/                 pValue[nProps++].Value <<= ( ((SfxBoolItem*)pItem)->GetValue() );
/*N*/             }
/*N*/             if ( rSet.GetItemState( SID_VIEWONLY, sal_False, &pItem ) == SFX_ITEM_SET )
/*N*/             {
/*N*/                 pValue[nProps].Name = sViewOnly;
/*N*/                 pValue[nProps++].Value <<= (sal_Bool) (( ((SfxBoolItem*)pItem)->GetValue() ));
/*N*/             }
/*N*/             if ( rSet.GetItemState( SID_EDITDOC, sal_False, &pItem ) == SFX_ITEM_SET )
/*N*/             {
/*N*/                 pValue[nProps].Name = sDontEdit;
/*N*/                 pValue[nProps++].Value <<= (sal_Bool) (!( ((SfxBoolItem*)pItem)->GetValue() ));
/*N*/             }
/*N*/             if ( rSet.GetItemState( SID_TARGETNAME, sal_False, &pItem ) == SFX_ITEM_SET )
/*N*/             {
/*N*/                 pValue[nProps].Name = sFrameName;
/*N*/                 pValue[nProps++].Value <<= (  ::rtl::OUString(((SfxStringItem*)pItem)->GetValue()) );
/*N*/             }
/*N*/             if ( rSet.GetItemState( SID_ORIGURL, sal_False, &pItem ) == SFX_ITEM_SET )
/*N*/             {
/*N*/                 pValue[nProps].Name = sOrigURL;
/*N*/                 pValue[nProps++].Value <<= (  ::rtl::OUString(((SfxStringItem*)pItem)->GetValue()) );
/*N*/             }
/*N*/             if ( rSet.GetItemState( SID_DOC_SALVAGE, sal_False, &pItem ) == SFX_ITEM_SET )
/*N*/             {
/*N*/                 pValue[nProps].Name = sSalvageURL;
/*N*/                 pValue[nProps++].Value <<= (  ::rtl::OUString(((SfxStringItem*)pItem)->GetValue()) );
/*N*/             }
/*N*/             if ( rSet.GetItemState( SID_CONTENTTYPE, sal_False, &pItem ) == SFX_ITEM_SET )
/*N*/             {
/*N*/                 pValue[nProps].Name = sMediaType;
/*N*/                 pValue[nProps++].Value <<= (  ::rtl::OUString(((SfxStringItem*)pItem)->GetValue())  );
/*N*/             }
/*N*/             if ( rSet.GetItemState( SID_WIN_POSSIZE, sal_False, &pItem ) == SFX_ITEM_SET )
/*N*/             {
/*N*/                 pValue[nProps].Name = sWindowState;
/*N*/                 pValue[nProps++].Value <<= (  ::rtl::OUString(((SfxStringItem*)pItem)->GetValue())  );
/*N*/             }
/*N*/             if ( rSet.GetItemState( SID_TEMPLATE_NAME, sal_False, &pItem ) == SFX_ITEM_SET )
/*N*/             {
/*N*/                 pValue[nProps].Name = sTemplateName;
/*N*/                 pValue[nProps++].Value <<= (  ::rtl::OUString(((SfxStringItem*)pItem)->GetValue())  );
/*N*/             }
/*N*/             if ( rSet.GetItemState( SID_TEMPLATE_REGIONNAME, sal_False, &pItem ) == SFX_ITEM_SET )
/*N*/             {
/*N*/                 pValue[nProps].Name = sTemplateRegionName;
/*N*/                 pValue[nProps++].Value <<= (  ::rtl::OUString(((SfxStringItem*)pItem)->GetValue())  );
/*N*/             }
/*N*/             if ( rSet.GetItemState( SID_JUMPMARK, sal_False, &pItem ) == SFX_ITEM_SET )
/*N*/             {
/*N*/                 pValue[nProps].Name = sJumpMark;
/*N*/                 pValue[nProps++].Value <<= (  ::rtl::OUString(((SfxStringItem*)pItem)->GetValue())  );
/*N*/             }
/*N*/
/*N*/             SFX_ITEMSET_ARG( &rSet, pRectItem, SfxRectangleItem, SID_VIEW_POS_SIZE, sal_False );
/*N*/             if ( pRectItem )
/*N*/             {
/*N*/                 DBG_ERROR("PosSizeItem not supported yet!");
/*N*/             }
/*N*/
/*N*/             if ( rSet.GetItemState( SID_CHARSET, sal_False, &pItem ) == SFX_ITEM_SET )
/*N*/             {
/*N*/                 pValue[nProps].Name = sCharacterSet;
/*N*/                 pValue[nProps++].Value <<= (  ::rtl::OUString(((SfxStringItem*)pItem)->GetValue())  );
/*N*/             }
/*N*/             if ( rSet.GetItemState( SID_MACROEXECMODE, sal_False, &pItem ) == SFX_ITEM_SET )
/*N*/             {
/*N*/                 pValue[nProps].Name = sMacroExecMode;
/*N*/                 pValue[nProps++].Value <<= ( (sal_Int16) ((SfxUInt16Item*)pItem)->GetValue() );
/*N*/             }
/*N*/             if ( rSet.GetItemState( SID_UPDATEDOCMODE, sal_False, &pItem ) == SFX_ITEM_SET )
/*N*/             {
/*N*/                 pValue[nProps].Name = sUpdateDocMode;
/*N*/                 pValue[nProps++].Value <<= ( (sal_Int16) ((SfxUInt16Item*)pItem)->GetValue() );
/*N*/             }
/*N*/             if ( rSet.GetItemState( SID_REPAIRPACKAGE, sal_False, &pItem ) == SFX_ITEM_SET )
/*N*/             {
/*N*/                 pValue[nProps].Name = sRepairPackage;
/*N*/                 pValue[nProps++].Value <<= ( ((SfxBoolItem*)pItem)->GetValue() );
/*N*/             }
/*N*/             if ( rSet.GetItemState( SID_DOCINFO_TITLE, sal_False, &pItem ) == SFX_ITEM_SET )
/*N*/             {
/*N*/                 pValue[nProps].Name = sDocumentTitle;
/*N*/                 pValue[nProps++].Value <<= ( ::rtl::OUString(((SfxStringItem*)pItem)->GetValue()) );
/*N*/             }
/*N*/         }
/*N*/     }
/*N*/
/*N*/     rArgs = aSequ;
/*N*/ }

/*N*/ SFX_IMPL_XINTERFACE_5( SfxMacroLoader, OWeakObject, ::com::sun::star::frame::XDispatchProvider, ::com::sun::star::frame::XNotifyingDispatch, ::com::sun::star::frame::XDispatch, ::com::sun::star::frame::XSynchronousDispatch,::com::sun::star::lang::XInitialization )
/*N*/ SFX_IMPL_XTYPEPROVIDER_5( SfxMacroLoader, ::com::sun::star::frame::XDispatchProvider, ::com::sun::star::frame::XNotifyingDispatch, ::com::sun::star::frame::XDispatch, ::com::sun::star::frame::XSynchronousDispatch,::com::sun::star::lang::XInitialization  )
/*N*/ SFX_IMPL_XSERVICEINFO( SfxMacroLoader, PROTOCOLHANDLER_SERVICENAME, "com.sun.star.comp.sfx2.SfxMacroLoader" )
/*N*/ SFX_IMPL_SINGLEFACTORY( SfxMacroLoader )
/*N*/
/*N*/ void SAL_CALL SfxMacroLoader::initialize( const ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Any >& aArguments ) throw (::com::sun::star::uno::Exception, ::com::sun::star::uno::RuntimeException)
/*N*/ {
/*N*/   Reference < XFrame > xFrame;
/*N*/   if ( aArguments.getLength() )
/*N*/   {
/*N*/       aArguments[0] >>= xFrame;
/*N*/       m_xFrame = xFrame;
/*N*/   }
/*N*/ }

/*N*/ SfxObjectShell* SfxMacroLoader::GetObjectShell_Impl()
/*N*/ {
/*N*/   SfxObjectShell* pDocShell = NULL;
/*N*/   Reference < XFrame > xFrame( m_xFrame.get(), UNO_QUERY );
/*N*/   if ( xFrame.is() )
/*N*/   {
/*N*/       SfxFrame* pFrame=0;
/*N*/       for ( pFrame = SfxFrame::GetFirst(); pFrame; pFrame = SfxFrame::GetNext( *pFrame ) )
/*N*/       {
/*N*/           if ( pFrame->GetFrameInterface() == xFrame )
/*N*/               break;
/*N*/       }
/*N*/
/*N*/       if ( pFrame )
/*N*/           pDocShell = pFrame->GetCurrentDocument();
/*N*/   }
/*N*/
/*N*/   return pDocShell;
/*N*/ }

// -----------------------------------------------------------------------
/*N*/ ::com::sun::star::uno::Reference< ::com::sun::star::frame::XDispatch > SAL_CALL SfxMacroLoader::queryDispatch( const ::com::sun::star::util::URL&   aURL            ,
/*N*/                                                                                                                const ::rtl::OUString&               sTargetFrameName,
/*N*/                                                                                                                      sal_Int32                      nSearchFlags    ) throw( ::com::sun::star::uno::RuntimeException )
/*N*/ {
/*N*/     ::com::sun::star::uno::Reference< ::com::sun::star::frame::XDispatch > xDispatcher;
/*N*/     if(aURL.Complete.compareToAscii("macro:",6)==0)
/*N*/         xDispatcher = this;
/*N*/     return xDispatcher;
/*N*/ }

// -----------------------------------------------------------------------
/*N*/ ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Reference < ::com::sun::star::frame::XDispatch > > SAL_CALL
/*N*/                 SfxMacroLoader::queryDispatches( const ::com::sun::star::uno::Sequence < ::com::sun::star::frame::DispatchDescriptor >& seqDescriptor )
/*N*/                     throw( ::com::sun::star::uno::RuntimeException )
/*N*/ {
/*N*/     sal_Int32 nCount = seqDescriptor.getLength();
/*N*/     ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Reference < ::com::sun::star::frame::XDispatch > > lDispatcher(nCount);
/*N*/     for( sal_Int32 i=0; i<nCount; ++i )
/*N*/         lDispatcher[i] = this->queryDispatch( seqDescriptor[i].FeatureURL,
/*N*/                                               seqDescriptor[i].FrameName,
/*N*/                                               seqDescriptor[i].SearchFlags );
/*N*/     return lDispatcher;
/*N*/ }

// -----------------------------------------------------------------------
/*N*/ void SAL_CALL SfxMacroLoader::dispatchWithNotification( const ::com::sun::star::util::URL&                                                          aURL      ,
/*N*/                                                         const ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue >&            lArgs     ,
/*N*/                                                         const ::com::sun::star::uno::Reference< ::com::sun::star::frame::XDispatchResultListener >& xListener )
/*N*/               throw (::com::sun::star::uno::RuntimeException)
/*N*/ {
/*N*/     ::vos::OGuard aGuard( Application::GetSolarMutex() );
/*N*/
/*N*/     sal_uInt32 nPropertyCount = lArgs.getLength();
/*N*/     ::rtl::OUString aReferer;
/*N*/   for( sal_uInt32 nProperty=0; nProperty<nPropertyCount; ++nProperty )
/*N*/   {
/*N*/         if( lArgs[nProperty].Name == ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("Referer")) )
/*N*/       {
/*N*/             lArgs[nProperty].Value >>= aReferer;
/*N*/             break;
/*N*/         }
/*N*/     }
/*N*/
/*N*/   ::com::sun::star::uno::Any aAny;
/*N*/     ErrCode nErr = loadMacro( aURL.Complete, aAny, GetObjectShell_Impl() );
/*N*/     if( xListener.is() )
/*N*/     {
/*N*/         // always call dispatchFinished(), because we didn't load a document but
/*N*/       // executed a macro instead!
/*N*/         ::com::sun::star::frame::DispatchResultEvent aEvent;
/*N*/
/*N*/         aEvent.Source = static_cast< ::cppu::OWeakObject* >(this);
/*N*/         if( nErr == ERRCODE_NONE )
/*N*/             aEvent.State = ::com::sun::star::frame::DispatchResultState::SUCCESS;
/*N*/         else
/*N*/             aEvent.State = ::com::sun::star::frame::DispatchResultState::FAILURE;
/*N*/
/*N*/         xListener->dispatchFinished( aEvent ) ;
/*N*/     }
/*N*/ }

/*?*/ ::com::sun::star::uno::Any SAL_CALL SfxMacroLoader::dispatchWithReturnValue( const ::com::sun::star::util::URL& aURL,
/*?*/                                                                            const ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue >& lArgs ) throw (::com::sun::star::uno::RuntimeException)
/*?*/ {{DBG_BF_ASSERT(0, "STRIP");} ::com::sun::star::uno::Any aRet; return aRet;//STRIP001
/*?*/ }

// -----------------------------------------------------------------------
/*N*/ void SAL_CALL SfxMacroLoader::dispatch( const ::com::sun::star::util::URL&                                               aURL  ,
/*N*/                                         const ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue >& lArgs )
/*N*/               throw (::com::sun::star::uno::RuntimeException)
/*N*/ {
/*N*/     ::vos::OGuard aGuard( Application::GetSolarMutex() );
/*N*/
/*N*/     sal_uInt32 nPropertyCount = lArgs.getLength();
/*N*/     ::rtl::OUString aReferer;
/*N*/   for( sal_uInt32 nProperty=0; nProperty<nPropertyCount; ++nProperty )
/*N*/   {
/*N*/         if( lArgs[nProperty].Name == ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("Referer")) )
/*N*/       {
/*N*/             lArgs[nProperty].Value >>= aReferer;
/*N*/             break;
/*N*/         }
/*N*/     }
/*N*/
/*N*/   ::com::sun::star::uno::Any aAny;
/*N*/     ErrCode nErr = loadMacro( aURL.Complete, aAny, GetObjectShell_Impl() );
/*N*/ }

// -----------------------------------------------------------------------
/*N*/ void SAL_CALL SfxMacroLoader::addStatusListener( const ::com::sun::star::uno::Reference< ::com::sun::star::frame::XStatusListener >& xControl ,
/*N*/                                                  const ::com::sun::star::util::URL&                                                  aURL     )
/*N*/               throw (::com::sun::star::uno::RuntimeException)
/*N*/ {
    /* TODO
            How we can handle different listener for further coming or currently running dispatch() jobs
            without any inconsistency!
     */
/*N*/ }

// -----------------------------------------------------------------------
/*N*/ void SAL_CALL SfxMacroLoader::removeStatusListener( const ::com::sun::star::uno::Reference< ::com::sun::star::frame::XStatusListener >& xControl ,
/*N*/                                                     const ::com::sun::star::util::URL&                                                  aURL     )
/*N*/         throw (::com::sun::star::uno::RuntimeException)
/*N*/ {
/*N*/ }
} //namespace binfilter
extern ::com::sun::star::uno::Any sbxToUnoValue( SbxVariable* pVar );
namespace binfilter {//STRIP009
// -----------------------------------------------------------------------
/*N*/ ErrCode SfxMacroLoader::loadMacro( const ::rtl::OUString& rURL, ::com::sun::star::uno::Any& rRetval, SfxObjectShell* pSh )
/*N*/   throw ( ::com::sun::star::uno::RuntimeException )
/*N*/ {
        DBG_ERROR( "SfxMacroLoader::loadMacro: dead code!" );
        return ERRCODE_BASIC_PROC_UNDEFINED;
/*N*/ }

/*N*/ SFX_IMPL_XSERVICEINFO( SfxAppDispatchProvider, "com.sun.star.frame.DispatchProvider", "com.sun.star.comp.sfx2.AppDispatchProvider" )                                                                \
/*N*/ SFX_IMPL_SINGLEFACTORY( SfxAppDispatchProvider );
/*N*/
/*N*/ void SAL_CALL SfxAppDispatchProvider::initialize( const ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Any >& aArguments ) throw (::com::sun::star::uno::Exception, ::com::sun::star::uno::RuntimeException)
/*N*/ {
/*N*/   Reference < XFrame > xFrame;
/*N*/   if ( aArguments.getLength() )
/*N*/   {
/*N*/       aArguments[0] >>= xFrame;
/*N*/       m_xFrame = xFrame;
/*N*/   }
/*N*/ }

/*N*/ Reference < XDispatch > SAL_CALL SfxAppDispatchProvider::queryDispatch( const ::com::sun::star::util::URL& aURL, const ::rtl::OUString& sTargetFrameName,
/*N*/                     FrameSearchFlags eSearchFlags ) throw( RuntimeException )
/*N*/ {
/*N*/     USHORT nId = 0;
/*N*/     Reference < XDispatch > xDisp;
/*N*/     if ( aURL.Protocol.compareToAscii( "slot:" ) == COMPARE_EQUAL ||
/*N*/          aURL.Protocol.compareToAscii( "commandId:" ) == COMPARE_EQUAL )
/*N*/     {
/*N*/         nId = (USHORT) aURL.Path.toInt32();
/*N*/     }
/*N*/
/*N*/   if ( aURL.Protocol.compareToAscii( ".uno:" ) == COMPARE_EQUAL )
/*N*/   {
/*N*/       // Support ".uno" commands. Map commands to slotid
/*N*/       nId = SFX_APP()->GetAppDispatcher_Impl()->GetSlotId( aURL.Main );
/*N*/   }
/*N*/
/*N*/   if ( nId && SFX_APP()->GetAppDispatcher_Impl()->HasSlot_Impl( nId ) )
/*N*/         xDisp = new SfxOfficeDispatch( SFX_APP()->GetAppDispatcher_Impl(), nId, aURL ) ;
/*N*/
/*N*/     return xDisp;
/*N*/ }

/*N*/ Sequence< Reference < XDispatch > > SAL_CALL SfxAppDispatchProvider::queryDispatches( const Sequence < DispatchDescriptor >& seqDescriptor )
/*N*/                         throw( RuntimeException )
/*N*/ {
/*N*/     return Sequence< Reference < XDispatch > >();
/*N*/ }
#ifdef TEST_HANDLERS

#include <com/sun/star/awt/XKeyHandler.hdl>
#include <com/sun/star/awt/XMouseClickHandler.hdl>

class TestKeyHandler: public ::cppu::WeakImplHelper2
<
    ::com::sun::star::awt::XKeyHandler,
    ::com::sun::star::lang::XServiceInfo
>
{
public:
    TestKeyHandler( const ::com::sun::star::uno::Reference < ::com::sun::star::lang::XMultiServiceFactory >& ){}

    SFX_DECL_XSERVICEINFO
    virtual sal_Bool SAL_CALL keyPressed( const ::com::sun::star::awt::KeyEvent& aEvent ) throw (::com::sun::star::uno::RuntimeException);
    virtual sal_Bool SAL_CALL keyReleased( const ::com::sun::star::awt::KeyEvent& aEvent ) throw (::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL disposing( const ::com::sun::star::lang::EventObject& Source)
        throw (::com::sun::star::uno::RuntimeException);
};

class TestMouseClickHandler: public ::cppu::WeakImplHelper2
<
    ::com::sun::star::awt::XMouseClickHandler,
    ::com::sun::star::lang::XServiceInfo
>
{
public:
    TestMouseClickHandler( const ::com::sun::star::uno::Reference < ::com::sun::star::lang::XMultiServiceFactory >& ){}

    SFX_DECL_XSERVICEINFO
    virtual sal_Bool SAL_CALL mousePressed( const ::com::sun::star::awt::MouseEvent& e ) throw (::com::sun::star::uno::RuntimeException);
    virtual sal_Bool SAL_CALL mouseReleased( const ::com::sun::star::awt::MouseEvent& e ) throw (::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL disposing( const ::com::sun::star::lang::EventObject& Source)
        throw (::com::sun::star::uno::RuntimeException);
};

/*N*/ sal_Bool SAL_CALL TestKeyHandler::keyPressed( const ::com::sun::star::awt::KeyEvent& aEvent ) throw (::com::sun::star::uno::RuntimeException)
/*N*/ {
/*N*/   return sal_False;
/*N*/ }
/*N*/
/*N*/ sal_Bool SAL_CALL TestKeyHandler::keyReleased( const ::com::sun::star::awt::KeyEvent& aEvent ) throw (::com::sun::star::uno::RuntimeException)
/*N*/ {
/*N*/   return sal_False;
/*N*/ }
/*N*/
/*N*/ void SAL_CALL TestKeyHandler::disposing( const ::com::sun::star::lang::EventObject& Source) throw (::com::sun::star::uno::RuntimeException)
/*N*/ {
/*N*/ }
/*N*/
/*N*/ sal_Bool SAL_CALL TestMouseClickHandler::mousePressed( const ::com::sun::star::awt::MouseEvent& e ) throw (::com::sun::star::uno::RuntimeException)
/*N*/ {
/*N*/   return sal_False;
/*N*/ }
/*N*/
/*N*/ sal_Bool SAL_CALL TestMouseClickHandler::mouseReleased( const ::com::sun::star::awt::MouseEvent& e ) throw (::com::sun::star::uno::RuntimeException)
/*N*/ {
/*N*/   return sal_False;
/*N*/ }
/*N*/
/*N*/ void SAL_CALL TestMouseClickHandler::disposing( const ::com::sun::star::lang::EventObject& Source) throw (::com::sun::star::uno::RuntimeException)
/*N*/ {
/*N*/ }
/*N*/
/*N*/ SFX_IMPL_XSERVICEINFO( TestKeyHandler, "com.sun.star.task.Job", "com.sun.star.comp.Office.KeyHandler");
/*N*/ SFX_IMPL_XSERVICEINFO( TestMouseClickHandler, "com.sun.star.task.Job", "com.sun.star.comp.Office.MouseClickHandler");
/*N*/ SFX_IMPL_SINGLEFACTORY( TestKeyHandler );
/*N*/ SFX_IMPL_SINGLEFACTORY( TestMouseClickHandler );
#endif
// -----------------------------------------------------------------------

extern "C" {

/*N*/
/*N*/ sal_Bool SAL_CALL sfx2_component_writeInfo(   void*   pServiceManager ,
/*N*/                                       void*   pRegistryKey    )
/*N*/ {
/*N*/   ::com::sun::star::uno::Reference< ::com::sun::star::registry::XRegistryKey >        xKey( reinterpret_cast< ::com::sun::star::registry::XRegistryKey* >( pRegistryKey ) )   ;
/*N*/
/*N*/     // Eigentliche Implementierung und ihre Services registrieren
/*N*/     ::rtl::OUString aImpl;
/*N*/     ::rtl::OUString aTempStr;
/*N*/     ::rtl::OUString aKeyStr;
/*N*/     Reference< XRegistryKey > xNewKey;
/*N*/     Reference< XRegistryKey > xLoaderKey;
/*N*/
/*N*/     // global app event broadcaster
/*N*/     aImpl = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("/"));
/*N*/     aImpl += SfxGlobalEvents_Impl::impl_getStaticImplementationName();
/*N*/
/*N*/     aTempStr = aImpl;
/*N*/     aTempStr += ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("/UNO/SERVICES"));
/*N*/     xNewKey = xKey->createKey( aTempStr );
/*N*/     xNewKey->createKey( ::rtl::OUString::createFromAscii("com.sun.star.frame.GlobalEventBroadcaster") );
/*N*/
/*N*/     // global app dispatcher
/*N*/     aImpl = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("/"));
/*N*/     aImpl += SfxAppDispatchProvider::impl_getStaticImplementationName();
/*N*/
/*N*/     aTempStr = aImpl;
/*N*/     aTempStr += ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("/UNO/SERVICES"));
/*N*/     xNewKey = xKey->createKey( aTempStr );
/*N*/     xNewKey->createKey( ::rtl::OUString::createFromAscii("com.sun.star.frame.ProtocolHandler") );
/*N*/
/*N*/     // standalone document info
/*N*/     aImpl = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("/"));
/*N*/     aImpl += SfxStandaloneDocumentInfoObject::impl_getStaticImplementationName();
/*N*/
/*N*/     aTempStr = aImpl;
/*N*/     aTempStr += ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("/UNO/SERVICES"));
/*N*/     xNewKey = xKey->createKey( aTempStr );
/*N*/     xNewKey->createKey( ::rtl::OUString::createFromAscii("com.sun.star.document.StandaloneDocumentInfo") );
/*N*/
/*N*/     // frame loader
/*N*/     aImpl = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("/"));
/*N*/     aImpl += SfxFrameLoader_Impl::impl_getStaticImplementationName();
/*N*/
/*N*/     aTempStr = aImpl;
/*N*/     aTempStr += ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("/UNO/SERVICES"));
/*N*/     xNewKey = xKey->createKey( aTempStr );
/*N*/     Sequence < ::rtl::OUString > aServices = SfxFrameLoader_Impl::impl_getStaticSupportedServiceNames();
/*N*/     sal_Int32 nCount = aServices.getLength();
/*N*/     for ( sal_Int16 i=0; i<nCount; i++ )
/*N*/         xNewKey->createKey( aServices.getConstArray()[i] );
/*N*/
/*N*/     // macro loader
/*N*/     aImpl = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("/"));
/*N*/     aImpl += SfxMacroLoader::impl_getStaticImplementationName();
/*N*/
/*N*/     aTempStr = aImpl;
/*N*/     aTempStr += ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("/UNO/SERVICES"));
/*N*/     xNewKey = xKey->createKey( aTempStr );
/*N*/     xNewKey->createKey( ::rtl::OUString::createFromAscii("com.sun.star.frame.ProtocolHandler") );
/*N*/
/*N*/   // - sfx document templates
/*N*/   aImpl = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("/"));
/*N*/     aImpl += SfxDocTplService::impl_getStaticImplementationName();
/*N*/
/*N*/     aTempStr = aImpl;
/*N*/     aTempStr += ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("/UNO/SERVICES"));
/*N*/     xNewKey = xKey->createKey( aTempStr );
/*N*/     xNewKey->createKey( ::rtl::OUString::createFromAscii("com.sun.star.frame.DocumentTemplates") );
/*N*/
/*N*/   // quickstart wrapper service
/*N*/     aImpl = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("/"));
/*N*/     aImpl += ShutdownIcon::impl_getStaticImplementationName();
/*N*/
/*N*/     aTempStr = aImpl;
/*N*/     aTempStr += ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("/UNO/SERVICES"));
/*N*/     xNewKey = xKey->createKey( aTempStr );
/*N*/     xNewKey->createKey( ::rtl::OUString::createFromAscii("com.sun.star.office.Quickstart") );
/*N*/
/*N*/   // script library container service
/*N*/     aImpl = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("/"));
/*N*/     aImpl += SfxScriptLibraryContainer::impl_getStaticImplementationName();
/*N*/
/*N*/     aTempStr = aImpl;
/*N*/     aTempStr += ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("/UNO/SERVICES"));
/*N*/     xNewKey = xKey->createKey( aTempStr );
/*N*/     xNewKey->createKey( ::rtl::OUString::createFromAscii("com.sun.star.script.ScriptLibraryContainer") );
/*N*/
/*N*/   // application script library container service
/*N*/     aImpl = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("/"));
/*N*/     aImpl += SfxApplicationScriptLibraryContainer::impl_getStaticImplementationName();
/*N*/
/*N*/     aTempStr = aImpl;
/*N*/     aTempStr += ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("/UNO/SERVICES"));
/*N*/     xNewKey = xKey->createKey( aTempStr );
/*N*/     xNewKey->createKey( ::rtl::OUString::createFromAscii("com.sun.star.script.ApplicationScriptLibraryContainer") );
/*N*/
/*N*/   // dialog library container service
/*N*/     aImpl = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("/"));
/*N*/     aImpl += SfxDialogLibraryContainer::impl_getStaticImplementationName();
/*N*/
/*N*/     aTempStr = aImpl;
/*N*/     aTempStr += ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("/UNO/SERVICES"));
/*N*/     xNewKey = xKey->createKey( aTempStr );
/*N*/     xNewKey->createKey( ::rtl::OUString::createFromAscii("com.sun.star.script.DialogLibraryContainer") );
/*N*/
/*N*/   // application dialog library container service
/*N*/     aImpl = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("/"));
/*N*/     aImpl += SfxApplicationDialogLibraryContainer::impl_getStaticImplementationName();
/*N*/
/*N*/     aTempStr = aImpl;
/*N*/     aTempStr += ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("/UNO/SERVICES"));
/*N*/     xNewKey = xKey->createKey( aTempStr );
/*N*/     xNewKey->createKey( ::rtl::OUString::createFromAscii("com.sun.star.script.ApplicationDialogLibraryContainer") );
/*N*/
/*N*/   return sal_True;
/*N*/ }
/*N*/
/*N*/ void* SAL_CALL sfx2_component_getFactory( const   sal_Char*   pImplementationName ,
/*N*/                                               void*       pServiceManager     ,
/*N*/                                               void*       pRegistryKey        )
/*N*/ {
/*N*/   // Set default return value for this operation - if it failed.
/*N*/   void* pReturn = NULL ;
/*N*/
/*N*/   if  (
/*N*/           ( pImplementationName   !=  NULL ) &&
/*N*/           ( pServiceManager       !=  NULL )
/*N*/       )
/*N*/   {
/*N*/       // Define variables which are used in following macros.
/*N*/       ::com::sun::star::uno::Reference< ::com::sun::star::lang::XSingleServiceFactory >   xFactory                                                                                                ;
/*N*/       ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >    xServiceManager( reinterpret_cast< ::com::sun::star::lang::XMultiServiceFactory* >( pServiceManager ) ) ;

        //=============================================================================
        //  Add new macro line to handle new service.
        //
        //  !!! ATTENTION !!!
        //      Write no ";" at end of line and dont forget "else" ! (see macro)
        //=============================================================================
/*N*/         IF_NAME_CREATECOMPONENTFACTORY( SfxGlobalEvents_Impl )
/*N*/         IF_NAME_CREATECOMPONENTFACTORY( SfxFrameLoader_Impl )
/*N*/         IF_NAME_CREATECOMPONENTFACTORY( SfxMacroLoader )
/*N*/         IF_NAME_CREATECOMPONENTFACTORY( SfxStandaloneDocumentInfoObject )
/*N*/         IF_NAME_CREATECOMPONENTFACTORY( SfxAppDispatchProvider )
/*N*/         IF_NAME_CREATECOMPONENTFACTORY( SfxDocTplService )
/*N*/       IF_NAME_CREATECOMPONENTFACTORY( ShutdownIcon )
/*N*/       IF_NAME_CREATECOMPONENTFACTORY( SfxScriptLibraryContainer )
/*N*/       IF_NAME_CREATECOMPONENTFACTORY( SfxDialogLibraryContainer )
/*N*/       IF_NAME_CREATECOMPONENTFACTORY( SfxApplicationScriptLibraryContainer )
/*N*/       IF_NAME_CREATECOMPONENTFACTORY( SfxApplicationDialogLibraryContainer )
/*N*/ #ifdef TEST_HANDLERS
/*N*/       IF_NAME_CREATECOMPONENTFACTORY( TestKeyHandler )
/*N*/       IF_NAME_CREATECOMPONENTFACTORY( TestMouseClickHandler )
/*N*/ #endif
/*N*/         // Factory is valid - service was found.
/*N*/       if ( xFactory.is() )
/*N*/       {
/*N*/           xFactory->acquire();
/*N*/           pReturn = xFactory.get();
/*N*/       }
/*N*/   }
/*N*/   // Return with result of this operation.
/*N*/   return pReturn ;
/*N*/ }
} // extern "C"

//=========================================================================

/*N*/ void SAL_CALL FilterOptionsContinuation::setFilterOptions(
/*N*/               const ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue >& rProps )
/*N*/       throw (::com::sun::star::uno::RuntimeException)
/*N*/ {
/*N*/   rProperties = rProps;
/*N*/ }
/*N*/
/*N*/ ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue > SAL_CALL
/*N*/   FilterOptionsContinuation::getFilterOptions()
/*N*/       throw (::com::sun::star::uno::RuntimeException)
/*N*/ {
/*N*/   return rProperties;
/*N*/ }
/*N*/
/*N*/ //=========================================================================
/*N*/
/*N*/ RequestFilterOptions::RequestFilterOptions( ::com::sun::star::uno::Reference< ::com::sun::star::frame::XModel > rModel,
/*N*/                             ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue > rProperties )
/*N*/ {
/*N*/   ::rtl::OUString temp;
/*N*/   ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface > temp2;
/*N*/   ::com::sun::star::document::FilterOptionsRequest aOptionsRequest( temp,
/*N*/                                                                         temp2,
/*N*/                                                                     rModel,
/*N*/                                                                     rProperties );
/*N*/
/*N*/       m_aRequest <<= aOptionsRequest;
/*N*/
/*N*/       m_pAbort  = new ContinuationAbort;
/*N*/       m_pOptions = new FilterOptionsContinuation;
/*N*/
/*N*/       m_lContinuations.realloc( 2 );
/*N*/       m_lContinuations[0] = ::com::sun::star::uno::Reference< ::com::sun::star::task::XInteractionContinuation >( m_pAbort  );
/*N*/       m_lContinuations[1] = ::com::sun::star::uno::Reference< ::com::sun::star::task::XInteractionContinuation >( m_pOptions );
/*N*/ }
/*N*/
/*N*/ ::com::sun::star::uno::Any SAL_CALL RequestFilterOptions::getRequest()
/*N*/       throw( ::com::sun::star::uno::RuntimeException )
/*N*/ {
/*N*/   return m_aRequest;
/*N*/ }
/*N*/
/*N*/ ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Reference< ::com::sun::star::task::XInteractionContinuation > >
/*N*/   SAL_CALL RequestFilterOptions::getContinuations()
/*N*/       throw( ::com::sun::star::uno::RuntimeException )
/*N*/ {
/*N*/   return m_lContinuations;
/*N*/ }
/*N*/
/*N*/ //=========================================================================
/*N*/
/*N*/ RequestPackageReparation::RequestPackageReparation( ::rtl::OUString aName )
/*N*/ {
/*N*/   ::rtl::OUString temp;
/*N*/   ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface > temp2;
/*N*/   ::com::sun::star::document::BrokenPackageRequest aBrokenPackageRequest( temp,
/*N*/                                                                               temp2,
/*N*/                                                                           aName );
/*N*/
/*N*/       m_aRequest <<= aBrokenPackageRequest;
/*N*/
/*N*/       m_pApprove = new ContinuationApprove;
/*N*/       m_pDisapprove = new ContinuationDisapprove;
/*N*/
/*N*/       m_lContinuations.realloc( 2 );
/*N*/       m_lContinuations[0] = ::com::sun::star::uno::Reference< ::com::sun::star::task::XInteractionContinuation >( m_pApprove );
/*N*/       m_lContinuations[1] = ::com::sun::star::uno::Reference< ::com::sun::star::task::XInteractionContinuation >( m_pDisapprove );
/*N*/ }
/*N*/
/*N*/ ::com::sun::star::uno::Any SAL_CALL RequestPackageReparation::getRequest()
/*N*/       throw( ::com::sun::star::uno::RuntimeException )
/*N*/ {
/*N*/   return m_aRequest;
/*N*/ }
/*N*/
/*N*/ ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Reference< ::com::sun::star::task::XInteractionContinuation > >
/*N*/   SAL_CALL RequestPackageReparation::getContinuations()
/*N*/       throw( ::com::sun::star::uno::RuntimeException )
/*N*/ {
/*N*/   return m_lContinuations;
/*N*/ }
/*N*/
/*N*/ //=========================================================================
/*N*/
/*N*/ NotifyBrokenPackage::NotifyBrokenPackage( ::rtl::OUString aName )
/*N*/ {
/*N*/   ::rtl::OUString temp;
/*N*/   ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface > temp2;
/*N*/   ::com::sun::star::document::BrokenPackageRequest aBrokenPackageRequest( temp,
/*N*/                                                                               temp2,
/*N*/                                                                           aName );
/*N*/
/*N*/       m_aRequest <<= aBrokenPackageRequest;
/*N*/
/*N*/       m_pAbort  = new ContinuationAbort;
/*N*/
/*N*/       m_lContinuations.realloc( 1 );
/*N*/       m_lContinuations[0] = ::com::sun::star::uno::Reference< ::com::sun::star::task::XInteractionContinuation >( m_pAbort  );
/*N*/ }
/*N*/
/*N*/ ::com::sun::star::uno::Any SAL_CALL NotifyBrokenPackage::getRequest()
/*N*/       throw( ::com::sun::star::uno::RuntimeException )
/*N*/ {
/*N*/   return m_aRequest;
/*N*/ }
/*N*/
/*N*/ ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Reference< ::com::sun::star::task::XInteractionContinuation > >
/*N*/   SAL_CALL NotifyBrokenPackage::getContinuations()
/*N*/       throw( ::com::sun::star::uno::RuntimeException )
/*N*/ {
/*N*/   return m_lContinuations;
/*N*/ }


}
