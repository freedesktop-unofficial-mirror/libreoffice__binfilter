/*************************************************************************
 *
 *  $RCSfile: sch_docshell.cxx,v $
 *
 *  $Revision: 1.7 $
 *
 *  last change: $Author: kz $ $Date: 2005-01-21 13:17:27 $
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

#define ITEMID_FONTLIST         SID_ATTR_CHAR_FONTLIST
#define ITEMID_NUMBERINFO       SID_ATTR_NUMBERFORMAT_INFO
#define ITEMID_COLOR_TABLE      SID_COLOR_TABLE
#define ITEMID_GRADIENT_LIST    SID_GRADIENT_LIST
#define ITEMID_HATCH_LIST       SID_HATCH_LIST
#define ITEMID_BITMAP_LIST      SID_BITMAP_LIST
#define ITEMID_DASH_LIST        SID_DASH_LIST
#define ITEMID_LINEEND_LIST     SID_LINEEND_LIST

// auto strip #ifndef _SV_WRKWIN_HXX
// auto strip #include <vcl/wrkwin.hxx>
// auto strip #endif
#include <bf_svx/svxids.hrc>
// auto strip #ifndef _SFXITEMPOOL_HXX //autogen
// auto strip #include <svtools/itempool.hxx>
// auto strip #endif
#ifndef _SO_CLSIDS_HXX //autogen
#include <so3/clsids.hxx>
#endif
#ifndef _SFX_PRINTER_HXX //autogen
#include <bf_sfx2/printer.hxx>
#endif
// auto strip #ifndef _UNDO_HXX
// auto strip #include <svtools/undo.hxx>
// auto strip #endif
#ifndef _CTRLTOOL_HXX
#include <svtools/ctrltool.hxx>
#endif
// auto strip #ifndef _IPMENU_HXX
// auto strip #include <so3/ipmenu.hxx>
// auto strip #endif
// auto strip #ifndef _SFXMNUMGR_HXX
// auto strip #include <bf_sfx2/mnumgr.hxx>
// auto strip #endif
#ifndef _SFX_PROGRESS_HXX
#include <bf_sfx2/progress.hxx>
#endif
// auto strip #ifndef _SFX_WHITER_HXX //autogen
// auto strip #include <svtools/whiter.hxx>
// auto strip #endif
#ifndef _SFXSTBMGR_HXX //autogen
#include <bf_sfx2/stbmgr.hxx>
#endif
#ifndef _SFXECODE_HXX //autogen
#include <svtools/sfxecode.hxx>
#endif
#ifndef _SVX_DRAWITEM_HXX //autogen
#include <bf_svx/drawitem.hxx>
#endif
#ifndef _SFXSTYLE_HXX //autogen
#include <svtools/style.hxx>
#endif
// auto strip #ifndef _SCH_DLL_HXX //autogen
// auto strip #include <schdll.hxx>
// auto strip #endif
// auto strip #ifndef _SFXVIEWFRM_HXX //autogen
// auto strip #include <bf_sfx2/viewfrm.hxx>
// auto strip #endif
#ifndef INCLUDED_SVTOOLS_SAVEOPT_HXX
#include <svtools/saveopt.hxx>
#endif
#ifndef INCLUDED_SVTOOLS_PATHOPTIONS_HXX
#include <svtools/pathoptions.hxx>
#endif
// auto strip #ifndef _URLOBJ_HXX
// auto strip #include <tools/urlobj.hxx>
// auto strip #endif

// auto strip #include <sot/formats.hxx>
// auto strip #include <bf_svx/flstitem.hxx>
#include <bf_svx/svxids.hrc>

#include "app.hrc"
#include "strings.hrc"
#include "res_bmp.hrc"
#include "schresid.hxx"
#include "schview.hxx"
// auto strip #include "docshell.hxx"
#include "schmod.hxx"

#include "ChXChartDocument.hxx"
#include "ChXChartData.hxx"
// auto strip #include "SchTransferable.hxx"

// header for class SfxFilter
// auto strip #ifndef _SFX_DOCFILT_HACK_HXX
// auto strip #include <bf_sfx2/docfilt.hxx>
// auto strip #endif

#ifndef _RTL_LOGFILE_HXX_
#include <rtl/logfile.hxx>
#endif

// XML filter
#include "SchXMLWrapper.hxx"

#ifndef _SCH_MEMCHRT_HXX
#include "memchrt.hxx"
#endif
namespace binfilter {

#define POOL_BUFFER_SIZE        (USHORT)32768
#define BASIC_BUFFER_SIZE       (USHORT)8192
#define DOCUMENT_BUFFER_SIZE    (USHORT)32768

#define SCH_STYLE_SHEET_NAME    String( RTL_CONSTASCII_USTRINGPARAM( "SfxStyleSheets" ))

#define SCH_DEFAULT_CHART_SIZE_WIDTH  8000
#define SCH_DEFAULT_CHART_SIZE_HEIGHT 7000

using namespace ::com::sun::star::uno;


// STATIC DATA -----------------------------------------------------------

static const String __FAR_DATA aStarChartDoc = String( RTL_CONSTASCII_USTRINGPARAM( "StarChartDocument" ));

//----------------------------------------------------------------------

/*************************************************************************
|*
|* SFX-Slotmaps und -Definitionen
|*
\************************************************************************/

#define SchChartDocShell
#include "schslots.hxx"


namespace
{

/** This class sets EnableSetModified( TRUE ) in the CTOR, and
    EnableSetModified( FALSE ) in the DTOR.  Thus, this can be used to safeld do
    changes at the model without resulting in a modification.
 */
class lcl_NoModificationGuard
{
public:
    lcl_NoModificationGuard( SvPersist * pPersist ) :
            m_pPersist( pPersist ),
            m_bModifyingWasEnabled( pPersist ? pPersist->IsEnableSetModified() : FALSE )
    {
        if( m_bModifyingWasEnabled &&
            m_pPersist )
            m_pPersist->EnableSetModified( FALSE );
    }

    ~lcl_NoModificationGuard()
    {
        if( m_bModifyingWasEnabled &&
            m_pPersist )
            m_pPersist->EnableSetModified( TRUE );
    }

private:
    SvPersist * m_pPersist;
    BOOL        m_bModifyingWasEnabled;
};
}

/*N*/ SFX_IMPL_INTERFACE( SchChartDocShell, SfxObjectShell, SchResId( 0 ) )
/*N*/ // from macro: void SchChartDocShell::InitInterface_Impl()
/*N*/ {}

using namespace ::com::sun::star;

/*N*/ SFX_IMPL_OBJECTFACTORY_DLL(SchChartDocShell, schart,
/*N*/                          SvGlobalName(BF_SO3_SCH_CLASSID), Sch)

/*N*/ TYPEINIT1(SchChartDocShell, SfxObjectShell);

/*************************************************************************
|*
|* shared construction - used by internal CTOR and InitNew
|*
\************************************************************************/

/*N*/ void SchChartDocShell::Construct() throw()
/*N*/ {
/*N*/   DBG_ASSERT( pChDoc, "SchChartDocShell::Construct() called with no valid model!" );
/*N*/   //Wird fuer die ModelCollection benoetigt
/*N*/   SetPool(&pChDoc->GetItemPool());
/*N*/     if( pUndoManager )
/*?*/         delete pUndoManager;
/*N*/     pUndoManager = new SfxUndoManager;
/*N*/
/*N*/   // Listen, bzw. Tables im ItemSet der DocShell anlegen
/*N*/   UpdateTablePointers();
/*N*/
/*N*/   if (pChDoc->GetPageCount() == 0L)
/*N*/   {
/*N*/       // Seite einfuegen
/*N*/       SdrPage* pPage = pChDoc->AllocPage(FALSE);
/*N*/       pPage->SetSize(GetVisArea(ASPECT_CONTENT).GetSize());
/*N*/       pChDoc->InsertPage(pPage);
/*N*/   }
/*N*/
/*N*/     // #i2914# remove menu item for 'Save Copy as...'
/*N*/     SvVerbList * pVerbList = new SvVerbList( GetVerbList() );
/*N*/
/*N*/     ULONG nCount = pVerbList->Count();
/*N*/     ULONG i = 0;
/*N*/     for( ; i < nCount; ++i )
/*N*/     {
/*N*/         // The Id 3 is the verb for 'Save Copy as...'
/*N*/         if( pVerbList->GetObject( i ).GetId() == 3 )
/*N*/         {
/*N*/             pVerbList->Remove( i );
/*N*/             break;
/*N*/         }
/*N*/     }
/*N*/     SetVerbList( pVerbList, TRUE );
/*N*/
/*N*/ }

/*N*/ void SchChartDocShell::DataModified( chart::ChartDataChangeEvent& aEvent ) throw()
/*N*/ {
/*N*/   uno::Reference< chart::XChartDocument > xChartDoc( GetModel(), uno::UNO_QUERY );
/*N*/   if( xChartDoc.is() )
/*N*/   {
/*N*/       uno::Reference< chart::XChartData > xData = xChartDoc->getData();
/*N*/       if( xData.is() )
/*N*/       {
/*N*/           ChXChartData* pChXData = ChXChartData::getImplementation( xData );
/*N*/           if( pChXData )
/*N*/           {
/*N*/               pChXData->DataModified( aEvent );
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/ }


/*************************************************************************
|*
|* Default CTOR - this one is called by the factory from SFX
|*
\************************************************************************/

/*N*/ SchChartDocShell::SchChartDocShell(SfxObjectCreateMode eMode) throw() :
/*N*/   SfxObjectShell(eMode),
/*N*/   pUndoManager(NULL),
/*N*/   pPrinter(NULL),
/*N*/   pFontList(NULL),
/*N*/   pChDoc(NULL),
/*N*/   bInitNewNoNewDoc(FALSE),
/*N*/   bOwnPrinter(FALSE),
/*N*/   mbClipboardExport( FALSE )
/*N*/ {
/*N*/   CHART_TRACE( "SchChartDocShell::SchChartDocShell(SfxObjectCreateMode)" );
/*N*/   SetShell(this);
/*N*/   SetModel( new ChXChartDocument( this ));
/*N*/ }

/*************************************************************************
|*
|* CTOR used by dragserver
|*
\************************************************************************/

//STRIP001 SchChartDocShell::SchChartDocShell(ChartModel* pDoc,
//STRIP001                                 SfxObjectCreateMode eMode) throw() :
//STRIP001  SfxObjectShell(eMode),
//STRIP001  pUndoManager(NULL),
//STRIP001  pPrinter(NULL),
//STRIP001  pFontList(NULL),
//STRIP001  pChDoc(pDoc),
//STRIP001  bInitNewNoNewDoc(TRUE),
//STRIP001  bOwnPrinter(FALSE),
//STRIP001  mbClipboardExport( FALSE )
//STRIP001 {
//STRIP001  CHART_TRACE1( "SchChartDocShell::SchChartDocShell(pDoc,eMode) pDoc=%lx", (long)pDoc );
//STRIP001  SetShell(this);
//STRIP001  SetModel( new ChXChartDocument( this ));
//STRIP001  Construct();
//STRIP001 }

/*************************************************************************
|*
|* Destruktor
|*
\************************************************************************/

/*N*/ SchChartDocShell::~SchChartDocShell() throw()
/*N*/ {
/*N*/   CHART_TRACE( "SchChartDocShell::~SchChartDocShell" );
/*N*/
/*N*/   delete pFontList;
/*N*/
/*N*/   delete pUndoManager;
/*N*/
/*N*/   if( pChDoc )
/*N*/   {
/*N*/       pChDoc->ClearUndoBuffer();              // clear draw undo actions
/*N*/       pChDoc->SetMaxUndoActionCount( 1 );     // don't add further undo actions
/*N*/   }
/*N*/
/*N*/   if(bOwnPrinter)
/*N*/       delete pPrinter;
/*N*/
/*N*/   delete pChDoc;
/*N*/ }

/*************************************************************************
|*
|* SFX-Requests bearbeiten
|*
\************************************************************************/

/*?*/ void SchChartDocShell::Execute(SfxRequest& rReq) throw()
/*?*/ {
/*?*/   DBG_BF_ASSERT(0, "STRIP"); //STRIP001   switch (rReq.GetSlot())
//STRIP001  {
//STRIP001      case SID_CLOSEDOC:
//STRIP001          SfxObjectShell::DoClose();
//STRIP001          break;
//STRIP001
//STRIP001      case SID_UPDATE:
//STRIP001          pChDoc->InitDataAttrs();
//STRIP001          pChDoc->BuildChart(FALSE);
//STRIP001          break;
//STRIP001  }
/*?*/ }

/*************************************************************************
|*
|* Slot-Stati setzen
|*
\************************************************************************/

/*?*/ void SchChartDocShell::GetState(SfxItemSet &rSet) throw()
/*?*/ {
/*?*/   DBG_BF_ASSERT(0, "STRIP"); //STRIP001   SfxWhichIter aIter(rSet);
//STRIP001  USHORT nWhich = aIter.FirstWhich();
//STRIP001
//STRIP001  while (nWhich)
//STRIP001  {
//STRIP001      USHORT nSlotId = SfxItemPool::IsWhich(nWhich) ?
//STRIP001                       GetPool().GetSlotId(nWhich) : nWhich;
//STRIP001
//STRIP001      switch (nSlotId)
//STRIP001      {
/*            case SID_DOC_MODIFIED:
                rSet.Put( SfxStringItem( SID_DOC_MODIFIED,
                                         IsModified() ? '*' : ' ' ) );
                //rSet.Put(SfxBoolItem(SID_DOC_MODIFIED, IsModified()));
                break;
*/
//STRIP001          case SID_DOCTEMPLATE :
//STRIP001              rSet.DisableItem (SID_DOCTEMPLATE);
//STRIP001              break;
//STRIP001      }
//STRIP001
//STRIP001      nWhich = aIter.NextWhich();
//STRIP001  }
/*?*/ }

/*************************************************************************
|*
|* SFX-Aktivierung
|*
\************************************************************************/

//STRIP001 void SchChartDocShell::Activate() throw()
//STRIP001 {
//STRIP001 }

/*************************************************************************
|*
|* SFX-Deaktivierung
|*
\************************************************************************/

//STRIP001 void SchChartDocShell::Deactivate() throw()
//STRIP001 {
//STRIP001 }

/*************************************************************************
|*
|* SFX-Undomanager zurueckgeben
|*
\************************************************************************/

/*N*/ SfxUndoManager* SchChartDocShell::GetUndoManager() throw()
/*N*/ {
/*N*/   return pUndoManager;
/*N*/ }

/*************************************************************************
|*
|* SfxPrinter ggf. erzeugen und zurueckgeben
|*
\************************************************************************/
/*N*/ SfxPrinter* SchChartDocShell::GetPrinter() throw()
/*N*/ {
/*N*/   if (!pPrinter)
/*N*/   {
/*N*/       SfxBoolItem aItem(SID_PRINTER_NOTFOUND_WARN, TRUE);
/*N*/       // ItemSet mit speziellem Poolbereich anlegen
/*N*/       SfxItemSet* pSet = new SfxItemSet(GetPool(),
/*N*/                                         SID_PRINTER_NOTFOUND_WARN,
/*N*/                                         SID_PRINTER_NOTFOUND_WARN, 0);
/*N*/       pSet->Put(aItem);
/*N*/       pPrinter = new SfxPrinter(pSet);
/*N*/       bOwnPrinter = TRUE;
/*N*/
/*N*/       MapMode aMapMode = pPrinter->GetMapMode();
/*N*/       aMapMode.SetMapUnit(MAP_100TH_MM);
/*N*/       pPrinter->SetMapMode(aMapMode);
/*N*/
/*N*/       if (pChDoc)
/*N*/       {
/*N*/           if (pPrinter != pChDoc->GetRefDevice())
/*N*/               pChDoc->SetRefDevice(pPrinter);
/*N*/
/*N*/           if (pPrinter != pChDoc->GetOutliner()->GetRefDevice())
/*N*/               pChDoc->GetOutliner()->SetRefDevice(pPrinter);
/*N*/       }
/*N*/   }
/*N*/
/*N*/   return pPrinter;
/*N*/ }


/*************************************************************************
|*
|* neuen SfxPrinter setzen
|*
\************************************************************************/
/*N*/ void SchChartDocShell::SetPrinter( SfxPrinter* pNewPrinter, BOOL bIsDeletedHere ) throw()
/*N*/ {
/*N*/     bool bFirstTimeSettingPrinter = ( pPrinter == NULL );
/*N*/
/*N*/     // Printer may only be used, if the MapUnit is correct
/*N*/   if( pNewPrinter &&
/*N*/         pNewPrinter->GetMapMode().GetMapUnit() == MAP_100TH_MM )
/*N*/   {
/*N*/       if (pPrinter && bOwnPrinter && (pPrinter != pNewPrinter))
/*N*/       {
/*?*/           delete pPrinter;
/*?*/           bOwnPrinter = FALSE;
/*N*/       }
/*N*/
/*N*/       bOwnPrinter = bIsDeletedHere;
/*N*/
/*N*/       pPrinter = pNewPrinter;
/*N*/       if(pFontList)delete pFontList;
/*N*/       OutputDevice* pOut = Application::GetDefaultDevice();   // #67730#
/*N*/       pFontList = new FontList( pPrinter, pOut, FALSE );
/*N*/       PutItem(SvxFontListItem(pFontList));
/*N*/     }
/*N*/   else
/*?*/       if( bIsDeletedHere )
/*?*/           delete pNewPrinter;
/*N*/
/*N*/     OutputDevice * pRefDev = GetRefDevice();
/*N*/     if( pChDoc &&
/*N*/         pRefDev &&
/*N*/         pRefDev->GetMapMode().GetMapUnit() == MAP_100TH_MM )
/*N*/     {
/*N*/         // set ref device at document at its outliner as well
/*N*/         OutputDevice * pRefDev = GetRefDevice();
/*N*/         if( pRefDev && pRefDev->GetMapMode().GetMapUnit() == MAP_100TH_MM )
/*N*/         {
/*N*/             pChDoc->SetRefDevice( pRefDev );
/*N*/             pChDoc->GetOutliner()->SetRefDevice( pRefDev );
/*N*/
/*N*/             // re-render chart with new ref-device
/*N*/
/*N*/             // call EnableSetModified( FALSE ) temporarily and safely
/*N*/             lcl_NoModificationGuard aNoModGuard( this );
/*N*/
/*N*/             if( ! bFirstTimeSettingPrinter &&
/*N*/                 pChDoc->IsInitialized() )
/*N*/             {
/*?*/                 pChDoc->BuildChart( FALSE );
/*N*/             }
/*N*/         }
/*N*/     }
/*N*/ }

/*************************************************************************
|*
|*
|*
\************************************************************************/
//STRIP001 Printer* SchChartDocShell::GetDocumentPrinter() throw()
//STRIP001 {
//STRIP001  return GetPrinter();
//STRIP001 }

/*************************************************************************
|*
|*
|*
\************************************************************************/
/*N*/ void SchChartDocShell::OnDocumentPrinterChanged(Printer* pNewPrinter) throw()
/*N*/ {
/*N*/     // we have no rtti, thus assert that we have an SfxPrinter
/*N*/     SetPrinter( reinterpret_cast< SfxPrinter * >( pNewPrinter ) );
/*N*/ }

/*N*/ OutputDevice * SchChartDocShell::GetRefDevice()
/*N*/ {
/*N*/     if ( GetProtocol().IsInPlaceActive() ||
/*N*/          SFX_CREATE_MODE_EMBEDDED == GetCreateMode() )
/*N*/     {
/*N*/         OutputDevice* pOutDev = GetDocumentRefDev();
/*N*/         if ( pOutDev )
/*N*/             return pOutDev;
/*N*/     }
/*N*/
/*N*/     return GetPrinter();
/*N*/ }

/*************************************************************************
|*
|* InitNew, (Dokument wird neu erzeugt): Streams oeffnen
|*
\************************************************************************/

/*N*/ BOOL SchChartDocShell::InitNew( SvStorage * pStor ) throw()
/*N*/ {
/*N*/   CHART_TRACE1( "SchChartDocShell::InitNew pModel=%lx", (long)pChDoc );
/*N*/
/*N*/   if( SfxInPlaceObject::InitNew( pStor ))
/*N*/   {
/*N*/       if(!pChDoc)
/*N*/       {
/*N*/           pChDoc = new ChartModel( SvtPathOptions().GetPalettePath(), this );
/*N*/           // set new model at ChXChartDocument
/*N*/           ChXChartDocument* pImpl = ChXChartDocument::getImplementation( GetModel() );
/*N*/           if( pImpl )
/*N*/               pImpl->SetChartModel( pChDoc );
/*N*/           Construct();
/*N*/       }
/*N*/       if( pChDoc )
/*N*/       {
/*N*/           if(bInitNewNoNewDoc)
/*?*/               pChDoc->NewOrLoadCompleted(DOC_LOADED);
/*N*/           else
/*N*/               pChDoc->NewOrLoadCompleted(NEW_DOC);
/*N*/       }
/*N*/
/*N*/       SetVisArea(Rectangle(Point(0, 0), Size( SCH_DEFAULT_CHART_SIZE_WIDTH, SCH_DEFAULT_CHART_SIZE_HEIGHT )));
/*N*/
/*N*/       return TRUE;
/*N*/   }
/*N*/
/*N*/   return FALSE;
/*N*/ }

/*************************************************************************
|*
|* Load: Pools und Dokument laden
|*
\************************************************************************/

/*N*/ BOOL SchChartDocShell::Load(SvStorage * pStor) throw()
/*N*/ {
/*N*/   RTL_LOGFILE_CONTEXT_AUTHOR (context, "sch", "af119097", "::SchChartDocShell::Load");
/*N*/
/*N*/   CHART_TRACE( "SchChartDocShell::Load" );
/*N*/
/*N*/   BOOL bRet = FALSE;
/*N*/
/*N*/   pChDoc = new ChartModel( SvtPathOptions().GetPalettePath(), this );
/*N*/   SetPool( &pChDoc->GetItemPool());
/*N*/   ChXChartDocument* pImpl = ChXChartDocument::getImplementation( GetModel() );
/*N*/   if( pImpl )
/*?*/       pImpl->SetChartModel( pChDoc );
/*N*/
/*N*/     sal_Bool bIsXML = pStor->GetVersion() >= SOFFICE_FILEFORMAT_60;
/*N*/
/*N*/   if( bIsXML )
/*N*/   {
//STRIP001      RTL_LOGFILE_CONTEXT_TRACE (context, "XML format");
//STRIP001      bRet = SfxInPlaceObject::Load( pStor );
//STRIP001
//STRIP001      // create a new draw page etc.
//STRIP001      Construct();
//STRIP001      // The XML Filter expects a completely
//STRIP001      // initialized document. This is achieved by the
//STRIP001      // following statement
//STRIP001      pChDoc->NewOrLoadCompleted( NEW_DOC );
//STRIP001
//STRIP001      if( bRet )
//STRIP001      {
//STRIP001          SetWaitCursor( TRUE );
//STRIP001
//STRIP001          if( pStor )
//STRIP001          {
//STRIP001                 Reference< ::com::sun::star::frame::XModel> xModel(GetModel());
//STRIP001              SchXMLWrapper aFilter( xModel, *pStor, TRUE );
//STRIP001                 sal_Int32 nWarning = aFilter.Import();
//STRIP001                 if( nWarning )
//STRIP001                     SetError( nWarning );
//STRIP001
//STRIP001                 // ok if there was no waring
//STRIP001              bRet = (nWarning == 0);
//STRIP001
//STRIP001                 // reset number format ids last set by calc
//STRIP001                 pChDoc->ResetLastAxisNumFmt( -2 );
//STRIP001
//STRIP001              if( bRet )
//STRIP001              {
//STRIP001                  // during import the page size is set
//STRIP001                  // the vis area has to be set to the whole page size
//STRIP001                     Size aPageSize = pChDoc->GetPage( 0 )->GetSize();
//STRIP001                     if( aPageSize.Width() <= 0 ||
//STRIP001                         aPageSize.Height() <= 0 )
//STRIP001                     {
//STRIP001                         // invalid page size
//STRIP001                         // assume that page size is uninitialized
//STRIP001                         DBG_ASSERT( aPageSize.Height() == 0 &&
//STRIP001                                     aPageSize.Width() == 0,
//STRIP001                                     "Invalid Page Size" );
//STRIP001                         aPageSize.setWidth( SCH_DEFAULT_CHART_SIZE_WIDTH );
//STRIP001                         aPageSize.setHeight( SCH_DEFAULT_CHART_SIZE_HEIGHT );
//STRIP001                     }
//STRIP001
//STRIP001                  Rectangle aVisRect( Point( 0, 0 ), aPageSize );
//STRIP001                  SetVisArea( aVisRect );
//STRIP001
//STRIP001                  pChDoc->SetChanged( FALSE );
//STRIP001                  pChDoc->NewOrLoadCompleted( DOC_LOADED );
//STRIP001                  SetModified( FALSE );
//STRIP001
//STRIP001                  FinishedLoading(SFX_LOADED_ALL);
//STRIP001              }
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              DBG_ERROR( "Load (XML): got no Storage in Medium!" );
//STRIP001          }
//STRIP001          SetWaitCursor( FALSE );
//STRIP001      }
//STRIP001      else
//STRIP001          DBG_ERROR( "Load (XML): SfxInPlaceObject::Load failed!" );
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       ULONG nStorFmt = pStor->GetFormat();
/*N*/       RTL_LOGFILE_CONTEXT_TRACE1 (context, "binary format %lu", nStorFmt);
/*N*/
/*N*/         // do some initializations
/*N*/       Construct();
/*N*/
/*N*/         pProgress = NULL;
/*N*/
/*N*/       if ( nStorFmt == SOT_FORMATSTR_ID_STARCHART_50 ||
/*N*/            nStorFmt == SOT_FORMATSTR_ID_STARCHART_40 ||
/*N*/            nStorFmt == SOT_FORMATSTR_ID_STARCHART    ||
/*N*/            nStorFmt == SOT_FORMATSTR_ID_STARCHARTDOCUMENT_50
/*N*/           )
/*N*/       {
/*N*/           if( GetCreateMode() != SFX_CREATE_MODE_EMBEDDED )
/*N*/               pProgress = new SfxProgress( this, String( SchResId( STR_OPEN_DOCUMENT )), 100 );
/*N*/
/*N*/           if( pProgress )
/*N*/               pProgress->SetState( 0, 100 );
/*N*/
/*N*/           bRet = SfxInPlaceObject::Load( pStor );
/*N*/
/*N*/           if( pProgress )
/*N*/               pProgress->SetState( 30 );
/*N*/
/*N*/           if( bRet )
/*N*/           {
/*N*/               SetWaitCursor( TRUE );
/*N*/
/*N*/               // Pool und StyleSheet Pool laden
/*N*/               String aStyleSheetsStr( SCH_STYLE_SHEET_NAME );
/*N*/
/*N*/               if (pStor->IsStream(aStyleSheetsStr))
/*N*/               {
/*N*/                   ULONG nError;
/*N*/                   SvStorageStreamRef rPoolStream = pStor->OpenStream( aStyleSheetsStr );
/*N*/                   rPoolStream->SetVersion( pStor->GetVersion());
/*N*/                   if( ! rPoolStream->GetError())
/*N*/                   {
/*N*/                       rPoolStream->SetBufferSize( POOL_BUFFER_SIZE );
/*N*/                       nError = rPoolStream->GetError();
/*N*/                       GetPool().SetFileFormatVersion( (USHORT)pStor->GetVersion ());
/*N*/                       GetPool().Load( *rPoolStream );
/*N*/                       nError = rPoolStream->GetError();
/*N*/                       if( nError )
/*N*/                       {
/*?*/                           DBG_ERROR1( "Errorcode 0x%x loading Pool", nError );
/*?*/                           rPoolStream->ResetError();
/*?*/                           SetError( ERRCODE_WARNING_MASK | nError );
/*N*/                       }
/*N*/                       GetStyleSheetPool()->Load( *rPoolStream );
/*N*/                       nError = rPoolStream->GetError();
/*N*/                       if( nError )
/*N*/                       {
/*?*/                           DBG_ERROR1( "Errorcode 0x%x loading StyleSheet-Pool", nError );
/*?*/                           rPoolStream->ResetError();
/*?*/                           SetError( ERRCODE_WARNING_MASK | nError );
/*N*/                       }
/*N*/                       rPoolStream->SetBufferSize( 0 );
/*N*/                   }
/*N*/                   else bRet = FALSE;
/*N*/               }
/*N*/               else bRet = FALSE;
/*N*/
/*N*/               if( pProgress )
/*N*/                   pProgress->SetState( 70 );
/*N*/
/*N*/               // wenn gewuenscht, das Dokument laden
/*N*/               if (bRet && (GetCreateMode() != SFX_CREATE_MODE_ORGANIZER))
/*N*/               {
/*N*/                   // Model der Drawing Engine laden
/*N*/                   if (pStor->IsStream( aStarChartDoc ))
/*N*/                   {
/*N*/                       SvStorageStreamRef rDocumentStream = pStor->OpenStream( aStarChartDoc );
/*N*/                       rDocumentStream->SetVersion( pStor->GetVersion());
/*N*/                       GetPool().SetFileFormatVersion ( (USHORT)pStor->GetVersion());
/*N*/                       if( ! rDocumentStream->GetError())
/*N*/                       {
/*N*/                           rDocumentStream->SetBufferSize( DOCUMENT_BUFFER_SIZE );
/*N*/                           rDocumentStream->SetKey( pStor->GetKey()); // set password
/*N*/
/*N*/                             // read ChartModel
/*N*/                           *rDocumentStream >> *pChDoc;
/*N*/
/*N*/                             bRet = ( rDocumentStream->GetError() == 0 );
/*N*/
/*N*/                           // garbled with password?
/*N*/                           if( ! bRet )
/*N*/                           {
/*?*/                               if( pStor->GetKey().Len() == 0 )
/*?*/                               {
/*?*/                                   // no password set => cannot load
/*?*/                                   SetError( ERRCODE_SFX_DOLOADFAILED );
/*?*/                               }
/*?*/                               else
/*?*/                               {
/*?*/                                   // password was set, but obviously wrong
/*?*/                                   SetError( ERRCODE_SFX_WRONGPASSWORD );
/*?*/                               }
/*N*/                           }
/*N*/
/*N*/                           rDocumentStream->SetBufferSize( 0 );
/*N*/                       }
/*N*/                       else bRet = FALSE;
/*N*/                   }
/*N*/                   else bRet = FALSE;
/*N*/               }
/*N*/
/*N*/               if( pProgress )
/*N*/                   pProgress->SetState( 100 );
/*N*/
/*N*/               // (noch) keine ungesicherten Aenderungen im Model
/*N*/               if (bRet)
/*N*/               {

                        // #i39672# convert range strings to new XML compatible format

                        // Note: Formerly, the parent storage was queried to
                        // find out whether it is a Writer or a Calc.  This
                        // worked, because it was done in SaveAs().  It is
                        // better to do the conversion right after loading,
                        // however here we have no parent.  So both conversions
                        // are called.  This works, because the things written
                        // to the SomeData strings is so different, that both
                        // routines won't convert the data for the wrong
                        // format. (Note: only the conversion from old to new,
                        // i.e. the call with parameter TRUE, work like this, as
                        // the new format is the same for both)

                        // try Writer
                        bool bConverted =
                            pChDoc->GetChartData()->ConvertChartRangeForWriter( TRUE );

                        // try Calc
                        if( ! bConverted )
                        {
                            SchMemChart* pData = pChDoc->GetChartData();
                            if( pData &&
                                pData->SomeData3().Len() > 0 &&
                                (pData->GetChartRange().maRanges.size() == 0) )
                                bConverted = pData->ConvertChartRangeForCalc( TRUE );
                        }

/*N*/                   pChDoc->SetChanged( FALSE );
/*N*/                   pChDoc->NewOrLoadCompleted( DOC_LOADED );
/*N*/               }
/*N*/
/*N*/               SetWaitCursor( FALSE );
/*N*/           }
/*N*/
/*N*/           if( pProgress )
/*N*/               pProgress->SetState( 100 );
/*N*/
/*N*/           if (bRet)
/*N*/           {
/*N*/               UpdateTablePointers();
/*N*/               FinishedLoading( SFX_LOADED_ALL );
/*N*/           }
/*N*/       }
/*N*/       else
/*N*/       {
/*?*/           pStor->SetError( SVSTREAM_WRONGVERSION );
/*N*/       }
/*N*/
/*N*/       if( pProgress )
/*N*/       {
/*N*/           delete pProgress;
/*N*/           pProgress = NULL;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   return bRet;
/*N*/ }

/*************************************************************************
|*
|*
|*
\************************************************************************/

//STRIP001 sal_Bool SchChartDocShell::ConvertTo( SfxMedium &rMedium )
//STRIP001 {
//STRIP001  BOOL            bRet = FALSE;
//STRIP001
//STRIP001  String aFilterName( rMedium.GetFilter()->GetFilterName() );
//STRIP001  if( aFilterName.EqualsAscii( "StarOffice XML (Chart)" ))
//STRIP001  {
        /**********************************************************************
         * StarOffice XML-Filter Export
         **********************************************************************/
//STRIP001      SvStorage* pStorage = rMedium.GetOutputStorage( sal_True );
//STRIP001      if( pStorage )
//STRIP001      {
//STRIP001             Reference< ::com::sun::star::frame::XModel> xModel(GetModel());
//STRIP001          SchXMLWrapper aFilter( xModel, *pStorage, TRUE );
//STRIP001
//STRIP001          // update user info before writing
//STRIP001          UpdateDocInfoForSave();
//STRIP001
//STRIP001          bRet = aFilter.Export();
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          DBG_ERROR( "ConvertTo: got no Storage in Medium!" );
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  FinishedLoading( SFX_LOADED_ALL );
//STRIP001
//STRIP001  return  bRet;
//STRIP001 }

//STRIP001 sal_Bool SchChartDocShell::ConvertFrom( SfxMedium &rMedium )
//STRIP001 {
//STRIP001  BOOL bRet = FALSE;
//STRIP001
//STRIP001  const String aFilterName(rMedium.GetFilter()->GetFilterName());
//STRIP001
//STRIP001  if( aFilterName.EqualsAscii( "StarOffice XML (Chart)" ))
//STRIP001  {
        /**********************************************************************
        * StarOffice XML-Filter Import
        **********************************************************************/
//STRIP001      SvStorage* pStorage = rMedium.GetStorage();
//STRIP001      if( pStorage )
//STRIP001      {
//STRIP001             Reference< ::com::sun::star::frame::XModel> xModel(GetModel());
//STRIP001          SchXMLWrapper aFilter( xModel, *pStorage, TRUE );
//STRIP001             sal_Int32 nWarning = aFilter.Import();
//STRIP001             if( nWarning )
//STRIP001                 SetError( nWarning );
//STRIP001
//STRIP001             // ok if there was no waring
//STRIP001             bRet = (nWarning == 0);
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          DBG_ERROR( "ConvertFrom: got no Storage in Medium!" );
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  FinishedLoading( SFX_LOADED_ALL );
//STRIP001
//STRIP001  return bRet;
//STRIP001 }

// ------------------------------------------------------------

//STRIP001 void SchChartDocShell::HandsOff() throw()
//STRIP001 {
//STRIP001  SfxInPlaceObject::HandsOff();
//STRIP001
//STRIP001     if( pChDoc )
//STRIP001         pChDoc->HandsOff();
//STRIP001 }

// ------------------------------------------------------------

/*N*/ BOOL SchChartDocShell::Save() throw()
/*N*/ {
/*N*/   RTL_LOGFILE_CONTEXT_AUTHOR (context, "sch", "af119097", "::SchChartDocShell::Save");
/*N*/
/*N*/   SvStorage* pStor = GetStorage();
/*N*/   DBG_ASSERT( pStor, "Save() without Storage called!" );
/*N*/
/*N*/     long nFileFormat = pStor->GetVersion();
/*N*/     sal_Bool bIsXML = nFileFormat >= SOFFICE_FILEFORMAT_60;
/*N*/   BOOL bRet = FALSE;
/*N*/
/*N*/   if( bIsXML )
/*N*/   {
/*N*/       RTL_LOGFILE_CONTEXT_TRACE (context, "XML format");
/*N*/       bRet = SfxInPlaceObject::Save();
/*N*/
        /**********************************************************************
         * StarOffice XML-Filter Export
         **********************************************************************/
/*N*/       if( pStor )
/*N*/       {
/*N*/             Reference< ::com::sun::star::frame::XModel> xModel(GetModel());
/*N*/           SchXMLWrapper aFilter( xModel, *pStor,
/*N*/                                  GetCreateMode() != SFX_CREATE_MODE_EMBEDDED );
/*N*/
/*N*/           // update user info before writing
/*N*/           UpdateDocInfoForSave();
/*N*/
/*N*/           bRet = aFilter.Export();
/*N*/       }
/*N*/       else
/*N*/       {
/*N*/           DBG_ERROR( "SaveAs (XML): got no Storage in Medium!" );
/*N*/       }
/*N*/
/*N*/           FinishedLoading( SFX_LOADED_ALL );
/*N*/   }
/*N*/   else        // binary format <= 5.0
/*N*/   {
/*N*/       pChDoc->PrepareAxisStorage();
/*N*/       SvStorageStreamRef rDocumentStream = pStor->OpenStream( aStarChartDoc );
/*N*/
/*N*/         if( rDocumentStream.Is() && ! rDocumentStream->GetError() )
/*N*/       {
/*N*/           rDocumentStream->SetVersion( pStor->GetVersion() );
/*N*/
/*N*/             if( nFileFormat <= SOFFICE_FILEFORMAT_40 && pChDoc->IsReal3D())
/*N*/             {
/*?*/                 CHART_TRACE( "Fileformat 4.0" );
/*?*/                 pChDoc->PrepareOld3DStorage();
/*N*/             }
/*N*/
/*N*/             bRet = SfxInPlaceObject::Save();
/*N*/             SfxStatusBarManager* pStbMgr =
/*N*/                 (GetCreateMode() == SFX_CREATE_MODE_EMBEDDED) ?
/*N*/                 NULL : SFX_APP()->GetStatusBarManager();
/*N*/
/*N*/             if (pStbMgr)
/*?*/                 pStbMgr->StartProgressMode(SchResId(STR_SAVE_DOCUMENT), 100);
/*N*/
/*N*/             // komprimiert/native speichern?
/*N*/             SvtSaveOptions                            aOptions;
/*N*/             const SvtSaveOptions::SaveGraphicsMode    eSaveMode( aOptions.GetSaveGraphicsMode() );
/*N*/             const BOOL                                bSaveNative = ( SvtSaveOptions::SaveGraphicsOriginal == eSaveMode );
/*N*/             const BOOL                                bSaveCompressed = ( bSaveNative || ( SvtSaveOptions::SaveGraphicsCompressed == eSaveMode ) );
/*N*/
/*N*/             pChDoc->SetSaveCompressed( bSaveCompressed );
/*N*/             pChDoc->SetSaveNative( bSaveNative );
/*N*/
/*N*/             if( bRet )
/*N*/             {
/*N*/                 pChDoc->PreSave();
/*N*/
/*N*/                 SetWaitCursor( TRUE );
/*N*/
/*N*/                 SvStorageStreamRef rPoolStream = pStor->OpenStream( SCH_STYLE_SHEET_NAME );
/*N*/                 if( ! rPoolStream->GetError())
/*N*/                 {
/*N*/                     rPoolStream->SetSize( 0 );
/*N*/                     rPoolStream->SetBufferSize( POOL_BUFFER_SIZE );
/*N*/                     GetPool().Store( *rPoolStream );
/*N*/
/*N*/                     if( pStbMgr )
/*?*/                         pStbMgr->SetProgressState( 20 );
/*N*/
/*N*/                     // the style sheet pool uses next() and first() methods without resetting
/*N*/                     // the search mask (?) so it has to be done here
/*N*/                     GetStyleSheetPool()->SetSearchMask( SFX_STYLE_FAMILY_ALL );
/*N*/                     // FALSE = also save unused style sheets
/*N*/                     GetStyleSheetPool()->Store( *rPoolStream, FALSE );
/*N*/                     rPoolStream->SetBufferSize( 0 );
/*N*/
/*N*/                     if( pStbMgr )
/*?*/                         pStbMgr->SetProgressState( 50 );
/*N*/                 }
/*N*/                 else bRet = FALSE;
/*N*/                 if (bRet)
/*N*/                     bRet = rPoolStream->GetError() == 0;
/*N*/                 DBG_ASSERT(bRet, "Fehler beim Schreiben der Pools");
/*N*/
/*N*/                 if( ! rDocumentStream->GetError())
/*N*/                 {
/*N*/                     rDocumentStream->SetSize( 0 );
/*N*/                     rDocumentStream->SetBufferSize( DOCUMENT_BUFFER_SIZE );
/*N*/                     *rDocumentStream << *pChDoc;
/*N*/                     rDocumentStream->SetBufferSize( 0 );
/*N*/                 }
/*N*/                 else
/*N*/                     bRet = FALSE;
/*N*/
/*N*/                 if (bRet)
/*N*/                     bRet = rDocumentStream->GetError() == 0;
/*N*/                 DBG_ASSERT(bRet, "Fehler beim Schreiben des Models");
/*N*/
/*N*/                 // finished
/*N*/                 if( pStbMgr )
/*?*/                     pStbMgr->SetProgressState( 100 );
/*N*/
/*N*/                 SetWaitCursor( FALSE );
/*N*/
/*N*/                 pChDoc->PostSave();
/*N*/             }
/*N*/
/*N*/             if (pStbMgr)
/*?*/                 pStbMgr->EndProgressMode();
/*N*/
/*N*/             if(nFileFormat <= SOFFICE_FILEFORMAT_40 && pChDoc->IsReal3D())
/*N*/             {
/*?*/                 pChDoc->CleanupOld3DStorage();
/*N*/             }
/*N*/         }
/*N*/   }
/*N*/
/*N*/   return bRet;
/*N*/ }

/*************************************************************************
|*
|*
|*
\************************************************************************/

/*N*/ BOOL SchChartDocShell::SaveAs(SvStorage * pStor) throw()
/*N*/ {
/*N*/   RTL_LOGFILE_CONTEXT_AUTHOR (context, "sch", "af119097", "::SchChartDocShell::SaveAs");
/*N*/
/*N*/   CHART_TRACE( "SchChartDocShell::SaveAs" );
/*N*/
/*N*/   BOOL bRet = FALSE;
/*N*/
/*N*/     long nOldFormat = GetStorage()->GetVersion();
/*N*/     long nNewFormat = pStor->GetVersion();
/*N*/
/*N*/   BOOL bIsXML = nNewFormat >= SOFFICE_FILEFORMAT_60;
/*N*/     BOOL bFormatChanges = (nOldFormat != nNewFormat);
/*N*/
/*N*/   //  If chart was loaded from binary format it has never been built.
/*N*/   if( ! pChDoc->IsInitialized())
/*N*/       pChDoc->Initialize();
/*N*/
/*N*/   if( bIsXML )
/*N*/   {
/*N*/       RTL_LOGFILE_CONTEXT_TRACE (context, "XML format");
/*N*/       bRet = SfxInPlaceObject::SaveAs( pStor );
/*N*/
         /**********************************************************************
          * StarOffice XML-Filter Export
          **********************************************************************/
/*N*/       if( pStor )
/*N*/       {
/*N*/             Reference< ::com::sun::star::frame::XModel> xModel(GetModel());
/*N*/           SchXMLWrapper aFilter( xModel, *pStor,
/*N*/                                  GetCreateMode() != SFX_CREATE_MODE_EMBEDDED );
/*N*/
/*N*/           // update user info before writing
/*N*/           UpdateDocInfoForSave();
/*N*/
/*N*/             // old storage was binary format
/*N*/             if( bFormatChanges )
/*N*/             {
/*N*/                 // convert SomeData-strings from Calc/Writer to data structure
/*N*/                 SvPersist* pParent = GetParent();
/*N*/                 if( pParent )
/*N*/                 {
/*?*/                     // determine which is parent application
/*?*/                      DBG_BF_ASSERT(0, "STRIP");

DBG_ERROR( "Conversion routine called" );
fprintf( stderr,  "BM: Conversion routine called\n" );
SvGlobalName aGlobalName;
 /*?*/                     ULONG nFileFormat;
 /*?*/                     String aAppName, aFullName, aShortName;
 /*?*/                     pParent->FillClass( &aGlobalName, &nFileFormat,
 /*?*/                                         &aAppName, &aFullName, &aShortName,
 /*?*/                                         SOFFICE_FILEFORMAT_60 );
 /*?*/
 /*?*/                     // calc does this conversion itself except when object was
 /*?*/                     // copied to clipboard. In this case SomeData3 was filled before.
 /*?*/                     if( nFileFormat == SOT_FORMATSTR_ID_STARCALC_60 )
 /*?*/                     {
 /*?*/                         SchMemChart* pData = pChDoc->GetChartData();
 /*?*/                         if( pData &&
 /*?*/                             pData->SomeData3().Len() > 0 &&
 /*?*/                             (pData->GetChartRange().maRanges.size() == 0) )
 /*?*/                         {
 /*?*/                             pData->ConvertChartRangeForCalc( TRUE );
 /*?*/                         }
 /*?*/                     }
 /*?*/                     else if( nFileFormat == SOT_FORMATSTR_ID_STARWRITER_60 )
 /*?*/                         pChDoc->GetChartData()->ConvertChartRangeForWriter( TRUE );

 /*N*/                 }
/*N*/             }
/*N*/
/*N*/           bRet = aFilter.Export();
/*N*/       }
/*N*/       else
/*N*/       {
/*?*/           DBG_ERROR( "SaveAs (XML): got no Storage in Medium!" );
/*N*/       }
/*N*/   }
/*N*/   else        // binary format <= 5.0
/*N*/   {
/*N*/       pChDoc->PrepareAxisStorage();
/*N*/       long nFileFormat = pStor->GetVersion();
/*N*/       RTL_LOGFILE_CONTEXT_TRACE1 (context, "binary format %ld", nFileFormat);
/*N*/       if(nFileFormat <= SOFFICE_FILEFORMAT_40 && pChDoc->IsReal3D())
/*N*/       {
/*N*/           pChDoc->PrepareOld3DStorage();
/*N*/           CHART_TRACE( "Fileformat 4.0" );
/*N*/       }
/*N*/
/*N*/       bRet = SfxInPlaceObject::SaveAs( pStor );
/*N*/       SfxStatusBarManager* pStbMgr =
/*N*/           (GetCreateMode() == SFX_CREATE_MODE_EMBEDDED) ?
/*N*/           NULL : SFX_APP()->GetStatusBarManager();
/*N*/       if (pStbMgr)
/*N*/           pStbMgr->StartProgressMode(SchResId(STR_SAVE_DOCUMENT), 100);
/*N*/
/*N*/       // compressed or native format
/*N*/       SvtSaveOptions                          aOptions;
/*N*/       const SvtSaveOptions::SaveGraphicsMode  eSaveMode( aOptions.GetSaveGraphicsMode() );
/*N*/       const BOOL                              bSaveNative = ( SvtSaveOptions::SaveGraphicsOriginal == eSaveMode );
/*N*/       const BOOL                              bSaveCompressed = ( bSaveNative || ( SvtSaveOptions::SaveGraphicsCompressed == eSaveMode ) );
/*N*/
/*N*/       pChDoc->SetSaveCompressed( bSaveCompressed );
/*N*/       pChDoc->SetSaveNative( bSaveNative );
/*N*/
/*N*/       if (bRet)
/*N*/       {
/*N*/           pChDoc->PreSave();
/*N*/           SvStorageStreamRef rPoolStream = pStor->OpenStream( SCH_STYLE_SHEET_NAME );
/*N*/           rPoolStream->SetVersion( pStor->GetVersion ());
/*N*/
/*N*/           SetWaitCursor( TRUE );
/*N*/
/*N*/           if( ! rPoolStream->GetError())
/*N*/           {
/*N*/               rPoolStream->SetBufferSize(POOL_BUFFER_SIZE);
/*N*/               GetPool().SetFileFormatVersion( (USHORT)pStor->GetVersion ());
/*N*/               GetPool().Store( *rPoolStream );
/*N*/
/*N*/               if( pStbMgr )
/*N*/                   pStbMgr->SetProgressState( 20 );
/*N*/
/*N*/               // the style sheet pool uses next() and first() methods without resetting
/*N*/               // the search mask (?) so it has to be done here
/*N*/               GetStyleSheetPool()->SetSearchMask( SFX_STYLE_FAMILY_ALL );
/*N*/               // FALSE = also save unused style sheets
/*N*/               GetStyleSheetPool()->Store( *rPoolStream, FALSE );
/*N*/               rPoolStream->SetBufferSize( 0 );
/*N*/
/*N*/               if( pStbMgr )
/*N*/                   pStbMgr->SetProgressState( 50 );
/*N*/           }
/*N*/           else
/*N*/               bRet = FALSE;
/*N*/
/*N*/           if( bRet )
/*N*/               bRet = rPoolStream->GetError() == 0;
/*N*/           DBG_ASSERT( bRet, "Fehler beim Schreiben der Pools" );
/*N*/
/*N*/           SvStorageStreamRef rDocumentStream = pStor->OpenStream( aStarChartDoc );
/*N*/           rDocumentStream->SetVersion( pStor->GetVersion());
/*N*/           GetPool().SetFileFormatVersion ( (USHORT)pStor->GetVersion ());
/*N*/
/*N*/           if( ! rDocumentStream->GetError())
/*N*/           {
/*N*/                 // old storage was XML format
/*N*/                 // always convert as internal storage is only the chart range
/*N*/ //                 if( bFormatChanges )
/*N*/ //                 {
/*N*/                     // convert data structure from Calc/Writer to SomeData strings
/*N*/                     SvPersist* pParent = GetParent();
/*N*/                     if( pParent )
/*N*/                     {
/*N*/                         // determine which is parent application
/*N*/                         SvGlobalName aGlobalName;
/*N*/                         ULONG nFileFormat;
/*N*/                         String aAppName, aFullName, aShortName;
/*N*/                         pParent->FillClass( &aGlobalName, &nFileFormat,
/*N*/                                             &aAppName, &aFullName, &aShortName,
/*N*/                                             SOFFICE_FILEFORMAT_60 );
/*N*/
/*N*/                         if( nFileFormat == SOT_FORMATSTR_ID_STARCALC_60 )
/*?*/                          pChDoc->GetChartData()->ConvertChartRangeForCalc( FALSE );
/*N*/                         else if( nFileFormat == SOT_FORMATSTR_ID_STARWRITER_60 )
/*N*/                             pChDoc->GetChartData()->ConvertChartRangeForWriter( FALSE );
/*N*/                     }
/*N*/ //                 }
/*N*/
/*N*/                 rDocumentStream->SetBufferSize( DOCUMENT_BUFFER_SIZE );
/*N*/               rDocumentStream->SetKey( pStor->GetKey());  // set password
/*N*/               *rDocumentStream << *pChDoc;
/*N*/               rDocumentStream->SetBufferSize( 0 );
/*N*/           }
/*N*/           else bRet = FALSE;
/*N*/           if( bRet )
/*N*/               bRet = rDocumentStream->GetError() == 0;
/*N*/           DBG_ASSERT( bRet, "Fehler beim Schreiben des Models" );
/*N*/
/*N*/           // finished
/*N*/           if( pStbMgr )
/*N*/               pStbMgr->SetProgressState( 100 );
/*N*/
/*N*/           SetWaitCursor( FALSE );
/*N*/
/*N*/           pChDoc->PostSave();
/*N*/       }
/*N*/
/*N*/       if( pStbMgr )
/*N*/           pStbMgr->EndProgressMode();
/*N*/
/*N*/       if( nFileFormat <= SOFFICE_FILEFORMAT_40 && pChDoc->IsReal3D())
/*N*/       {
/*N*/           pChDoc->CleanupOld3DStorage();
/*N*/       }
/*N*/   }
/*N*/
/*N*/   return bRet;
/*N*/ }

/*************************************************************************
|*
|*
|*
\************************************************************************/

/*N*/ BOOL SchChartDocShell::SaveCompleted( SvStorage * pStor ) throw()
/*N*/ {
/*N*/   CHART_TRACE( "SchChartDocShell::SaveCompleted" );
/*N*/
/*N*/   BOOL bRet = SfxInPlaceObject::SaveCompleted( pStor );
/*N*/
/*N*/   if( bRet )
/*N*/   {
/*N*/       if( pStor && pChDoc )
/*N*/         {
/*N*/             // #99758# SetChanged was called here which called SetModified().  I
/*N*/             // removed this, since it is not clear why this was introduced in
/*N*/             // rev. 1.48 (loading of files with additional graphics does not set
/*N*/             // the modified flag to true)
/*N*/
/*N*/             // throw away old graphics streams
/*N*/           pChDoc->HandsOff();
/*N*/         }
/*N*/   }
/*N*/   return bRet;
/*N*/ }

/*************************************************************************
|*
|* Tabellenzeiger auffrischen
|*
\************************************************************************/
/*N*/ void SchChartDocShell::UpdateTablePointers() throw()
/*N*/ {
/*N*/   PutItem(SvxColorTableItem(pChDoc->GetColorTable()));
/*N*/   PutItem(SvxGradientListItem(pChDoc->GetGradientList()));
/*N*/   PutItem(SvxHatchListItem(pChDoc->GetHatchList()));
/*N*/   PutItem(SvxBitmapListItem(pChDoc->GetBitmapList()));
/*N*/   PutItem(SvxDashListItem(pChDoc->GetDashList()));
/*N*/   PutItem(SvxLineEndListItem(pChDoc->GetLineEndList()));
/*N*/
/*N*/   if(pFontList)delete pFontList;
/*N*/
/*N*/   if ( GetCreateMode() == SFX_CREATE_MODE_EMBEDDED && !pPrinter )
/*N*/   {
/*N*/       // OLE-Objekt: kein Printer anlegen
/*?*/       pFontList = new FontList( Application::GetDefaultDevice(), NULL, FALSE );   // #67730#
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       pFontList = new FontList(GetPrinter(), NULL, FALSE);
/*N*/   }
/*N*/
/*N*/   SvxFontListItem aFontListItem(pFontList);
/*N*/   PutItem(aFontListItem);
/*N*/
/*N*/ //    PutItem(SvxNumberInfoItem(pChDoc->GetNumFormatter()));
/*N*/ }

/*************************************************************************
|*
|* FillClass
|*
\************************************************************************/

/*N*/ void SchChartDocShell::FillClass(SvGlobalName* pClassName,
/*N*/                                ULONG*  pFormat,
/*N*/                                String* pAppName,
/*N*/                                String* pFullTypeName,
/*N*/                                String* pShortTypeName,
/*N*/                                long    nFileFormat) const throw()
/*N*/ {
/*N*/   SfxInPlaceObject::FillClass(pClassName, pFormat, pAppName, pFullTypeName,
/*N*/                               pShortTypeName, nFileFormat);
/*N*/
/*N*/   if (nFileFormat == SOFFICE_FILEFORMAT_31)
/*N*/   {
/*N*/       *pClassName     = SvGlobalName(BF_SO3_SCH_CLASSID_30);
/*N*/       *pFormat        = SOT_FORMATSTR_ID_STARCHART;
/*N*/       (*pAppName).AssignAscii( RTL_CONSTASCII_STRINGPARAM( "Schart 3.1" ));
/*N*/       *pFullTypeName  = String(SchResId(STR_CHART_DOCUMENT_FULLTYPE_31));
/*N*/       *pShortTypeName = String(SchResId(STR_CHART_DOCUMENT));
/*N*/   }
/*N*/   else if (nFileFormat == SOFFICE_FILEFORMAT_40)
/*N*/   {
/*N*/       *pClassName     = SvGlobalName(BF_SO3_SCH_CLASSID_40);
/*N*/       *pFormat        = SOT_FORMATSTR_ID_STARCHART_40;
/*N*/       *pFullTypeName  = String(SchResId(STR_CHART_DOCUMENT_FULLTYPE_40));
/*N*/       *pShortTypeName = String(SchResId(STR_CHART_DOCUMENT));
/*N*/   }
/*N*/   else if (nFileFormat == SOFFICE_FILEFORMAT_50)
/*N*/   {
/*N*/       *pClassName     = SvGlobalName(BF_SO3_SCH_CLASSID_50);

            // for binfilter, we need the FormatIDs to be set. Not setting them
            // has always been an error (!)
            *pFormat        = SOT_FORMATSTR_ID_STARCHART_50;

/*N*/       *pFullTypeName  = String(SchResId(STR_CHART_DOCUMENT_FULLTYPE_50));
/*N*/       *pShortTypeName = String(SchResId(STR_CHART_DOCUMENT));
/*N*/   }
/*N*/   else if (nFileFormat == SOFFICE_FILEFORMAT_60)
/*N*/   {
/*N*/       *pClassName     = SvGlobalName(BF_SO3_SCH_CLASSID_60);

            // for binfilter, we need the FormatIDs to be set. Not setting them
            // has always been an error (!)
            *pFormat        = SOT_FORMATSTR_ID_STARCHART_60;

/*N*/       *pFullTypeName  = String(SchResId(STR_CHART_DOCUMENT_FULLTYPE_60));
/*N*/       *pShortTypeName = String(SchResId(STR_CHART_DOCUMENT));
/*N*/   }
/*N*/ }

//STRIP001 void SchChartDocShell::InPlaceActivate( BOOL b ) throw()
//STRIP001 {
//STRIP001  if( pChDoc )
//STRIP001  {
//STRIP001      pChDoc->CatchUpBufferedData();
//STRIP001  }
//STRIP001  SfxInPlaceObject::InPlaceActivate( b );
//STRIP001 }
}
