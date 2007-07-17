/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sd_docshell.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: obo $ $Date: 2007-07-17 10:05:15 $
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

#define ITEMID_FONTLIST                 SID_ATTR_CHAR_FONTLIST
#define ITEMID_COLOR_TABLE              SID_COLOR_TABLE
#define ITEMID_GRADIENT_LIST            SID_GRADIENT_LIST
#define ITEMID_HATCH_LIST               SID_HATCH_LIST
#define ITEMID_BITMAP_LIST              SID_BITMAP_LIST
#define ITEMID_DASH_LIST                SID_DASH_LIST
#define ITEMID_LINEEND_LIST             SID_LINEEND_LIST
#define ITEMID_SEARCH                   SID_SEARCH_ITEM

#include <bf_sfx2/app.hxx>


#ifndef _SVXIDS_HRC
#include <bf_svx/svxids.hrc>
#endif
#ifndef _SFXINTITEM_HXX
#include <svtools/intitem.hxx>
#endif
#ifndef _SFX_PRINTER_HXX //autogen
#include <bf_sfx2/printer.hxx>
#endif
#ifndef _SVX_FLSTITEM_HXX //autogen
#include <bf_svx/flstitem.hxx>
#endif
#ifndef _SVX_DRAWITEM_HXX //autogen
#include <bf_svx/drawitem.hxx>
#endif
#ifndef _CTRLTOOL_HXX //autogen
#include <svtools/ctrltool.hxx>
#endif
#ifndef _FILTER_HXX //autogen
#include <svtools/filter.hxx>
#endif
#ifndef _SO_CLSIDS_HXX
#include <so3/clsids.hxx>
#endif

#include "app.hrc"
#include "strmname.h"
#include "strings.hrc"
#include "docshell.hxx"
#include "drawdoc.hxx"
#include "glob.hrc"
#include "res_bmp.hrc"
#include "sdresid.hxx"
#include "frmview.hxx"
#include "unomodel.hxx"

#define POOL_BUFFER_SIZE                (USHORT)32768
#define BASIC_BUFFER_SIZE               (USHORT)8192
#define DOCUMENT_BUFFER_SIZE            (USHORT)32768

namespace binfilter {
GraphicFilter* GetGrfFilter();

SfxProgress* SdDrawDocShell::mpSpecialProgress = NULL;
Link*        SdDrawDocShell::mpSpecialProgressHdl = NULL;

/*************************************************************************
|*
|* SFX-Slotmaps und -Definitionen
|*
\************************************************************************/
/*N*/ TYPEINIT1( SdDrawDocShell, SfxObjectShell );
}//namespace binfilter


namespace binfilter {

/*N*/ SFX_IMPL_OBJECTFACTORY_LOD(SdDrawDocShell, simpress,
/*N*/                          SvGlobalName(BF_SO3_SIMPRESS_CLASSID), Sd)

/*************************************************************************
|*
|* Construct
|*
\************************************************************************/

/*N*/ void SdDrawDocShell::Construct()
/*N*/ {
/*N*/   bInDestruction = FALSE;
/*N*/   SetSlotFilter();     // setzt Filter zurueck
/*N*/   SetShell(this);
/*N*/
/*N*/   pDoc = new SdDrawDocument(eDocType, this);
/*N*/   SetModel( new SdXImpressDocument( this ) );
/*N*/   SetPool( &pDoc->GetItemPool() );
/*N*/   UpdateTablePointers();
/*N*/   SetStyleFamily(5);       //CL: eigentlich SFX_STYLE_FAMILY_PSEUDO
/*N*/ }

/*************************************************************************
|*
|* Konstruktor 1
|*
\************************************************************************/

/*N*/ SdDrawDocShell::SdDrawDocShell(SfxObjectCreateMode eMode,
/*N*/                              BOOL bDataObject,
/*N*/                              DocumentType eDocumentType) :
/*N*/   SfxObjectShell(eMode),
/*N*/   pPrinter(NULL),
/*N*/   pDoc(NULL),
/*N*/   pFontList(NULL),
/*N*/   bUIActive(FALSE),
/*N*/   pProgress(NULL),
/*N*/   bSdDataObj(bDataObject),
/*N*/   bOwnPrinter(FALSE),
/*N*/   eDocType(eDocumentType),
/*N*/     mbNewDocument( sal_True )
/*N*/ {
/*N*/ //    pDoc = new SdDrawDocument(eDocType, this);
/*N*/   Construct();
/*N*/ }

/*************************************************************************
|*
|* Konstruktor 2
|*
\************************************************************************/

SdDrawDocShell::SdDrawDocShell(SdDrawDocument* pDoc, SfxObjectCreateMode eMode,
                               BOOL bDataObject,
                               DocumentType eDocumentType) :
    SfxObjectShell(eMode),
    pPrinter(NULL),
    pDoc(pDoc),
    pFontList(NULL),
    bUIActive(FALSE),
    pProgress(NULL),
    bSdDataObj(bDataObject),
    bOwnPrinter(FALSE),
    eDocType(eDocumentType),
    mbNewDocument( sal_True )
{
    Construct();
}

/*************************************************************************
|*
|* Destruktor
|*
\************************************************************************/

/*N*/ SdDrawDocShell::~SdDrawDocShell()
/*N*/ {
/*N*/   bInDestruction = TRUE;
/*N*/
/*N*/   delete pFontList;
/*N*/
/*N*/   if (bOwnPrinter)
/*N*/       delete pPrinter;
/*N*/
/*N*/   delete pDoc;
/*N*/
/*N*/ }

/*************************************************************************
|*
|* Slot-Stati setzen
|*
\************************************************************************/



/*************************************************************************
|*
|* SFX-Aktivierung
|*
\************************************************************************/


/*************************************************************************
|*
|* SFX-Deaktivierung
|*
\************************************************************************/

/*N*/ void SdDrawDocShell::Deactivate( BOOL )
/*N*/ {
/*N*/ }

/*************************************************************************
|*
|* Tabellenzeiger auffrischen
|*
\************************************************************************/

/*N*/ void SdDrawDocShell::UpdateTablePointers()
/*N*/ {
/*N*/   PutItem( SvxColorTableItem( pDoc->GetColorTable() ) );
/*N*/   PutItem( SvxGradientListItem( pDoc->GetGradientList() ) );
/*N*/   PutItem( SvxHatchListItem( pDoc->GetHatchList() ) );
/*N*/   PutItem( SvxBitmapListItem( pDoc->GetBitmapList() ) );
/*N*/   PutItem( SvxDashListItem( pDoc->GetDashList() ) );
/*N*/   PutItem( SvxLineEndListItem( pDoc->GetLineEndList() ) );
/*N*/
/*N*/   delete pFontList;
/*N*/   pFontList = new FontList( GetPrinter(TRUE), Application::GetDefaultDevice(), FALSE );
/*N*/   SvxFontListItem aFontListItem( pFontList );
/*N*/   PutItem( aFontListItem );
/*N*/ }

/*************************************************************************
|*
|*
|*
\************************************************************************/


/*************************************************************************
|*
|*  den eingestellten SlotFilter anwenden
|*
\************************************************************************/



/*N*/ void SdDrawDocShell::SetModified( BOOL bSet /* = TRUE */ )
/*N*/ {
/*N*/   SfxInPlaceObject::SetModified( bSet );
/*N*/
/*N*/     // #100237# change model state, too
/*N*/     // #103182# only set the changed state if modification is enabled
/*N*/     if( IsEnableSetModified() && pDoc )
/*N*/         pDoc->NbcSetChanged( bSet );
/*N*/
/*N*/   Broadcast( SfxSimpleHint( SFX_HINT_DOCCHANGED ) );
/*N*/ }


/*************************************************************************
|*
|* Callback fuer ExecuteSpellPopup()
|*
\************************************************************************/

// #91457# ExecuteSpellPopup now handled by SdDrawDocShell. This is necessary
// to get hands on the outliner and the text object.

}
