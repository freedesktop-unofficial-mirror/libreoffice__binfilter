/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sch_docshel1.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: obo $ $Date: 2007-07-17 09:49:20 $
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

#ifndef _SVX_SVXIDS_HRC
#define ITEMID_FONTLIST         SID_ATTR_CHAR_FONTLIST
#define ITEMID_NUMBERINFO       SID_ATTR_NUMBERFORMAT_INFO
#define ITEMID_COLOR_TABLE      SID_COLOR_TABLE
#define ITEMID_GRADIENT_LIST    SID_GRADIENT_LIST
#define ITEMID_HATCH_LIST       SID_HATCH_LIST
#define ITEMID_BITMAP_LIST      SID_BITMAP_LIST
#define ITEMID_DASH_LIST        SID_DASH_LIST
#define ITEMID_LINEEND_LIST     SID_LINEEND_LIST
#include <bf_svx/svxids.hrc>
#endif

#include <bf_sfx2/app.hxx>

#include "app.hrc"
#include "strings.hrc"
#include "res_bmp.hrc"
#include "docshell.hxx"

namespace binfilter {

/*************************************************************************
|*
|*  Zeichnen der DocShell (mittels der Hilfsklasse SchViewSpecial)
|*
\************************************************************************/




/*************************************************************************
|*
|*
|*
\************************************************************************/


/*************************************************************************
|*
|*  Bitmap der StyleFamily zurueckgeben (zunaechst Dummy)
|*
\************************************************************************/

/*N*/ SfxStyleSheetBasePool* SchChartDocShell::GetStyleSheetPool() throw()
/*N*/ {
/*N*/   return (SfxStyleSheetBasePool*)pChDoc->GetStyleSheetPool();
/*N*/ }

/*************************************************************************
|*
|*  Vorlage einfuegen (zunaechst nur Dummy)
|*
\************************************************************************/


/*************************************************************************
|*
|*  Vorlage entfernen (zunaechst nur Dummy)
|*
\************************************************************************/


/*************************************************************************
|*
|*  Chart updaten
|*
\************************************************************************/


/*************************************************************************
|*
|*
|*
\************************************************************************/

/*N*/ Rectangle SchChartDocShell::GetVisArea(USHORT nAspect) const throw()
/*N*/ {
/*N*/   return SfxInPlaceObject::GetVisArea((nAspect == ASPECT_THUMBNAIL) ?
/*N*/                                        ASPECT_CONTENT : nAspect);
/*N*/ }

/*************************************************************************
|*
|* VisArea fuer InPlace setzen
|*
\************************************************************************/

/*N*/ void SchChartDocShell::SetVisArea(const Rectangle& rRect) throw()
/*N*/ {
/*N*/   Rectangle aRect(rRect);
/*N*/   aRect.SetPos(Point(0, 0));
/*N*/
/*N*/   if( GetCreateMode() == SFX_CREATE_MODE_EMBEDDED )
/*N*/   {
/*N*/       // sets the modified flag
/*N*/       SfxInPlaceObject::SetVisArea( rRect );
/*N*/
/*N*/         // #107434# propagate modified status to changed status at model
/*N*/         if( pChDoc && IsModified() )
/*N*/             pChDoc->SetChanged( TRUE );
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/         // does not set the modified flag
/*?*/       SvEmbeddedObject::SetVisArea( rRect );
/*N*/   }
/*N*/
/*N*/     if( GetCreateMode() != SFX_CREATE_MODE_INTERNAL )
/*N*/   {
/*N*/       Size aSize;
/*N*/
/*N*/       if (rRect.IsEmpty ())
/*N*/           aSize = Size ();
/*N*/       else
/*N*/           aSize = GetVisArea(ASPECT_CONTENT).GetSize();
/*N*/
/*N*/       SdrPage* pPage = pChDoc->GetPage(0);
/*N*/
/*N*/       if(aSize.Width() > 0 && aSize.Height() > 0)
/*N*/       {
/*N*/           if( !pPage || aSize != pPage->GetSize() )
/*N*/           {
/*N*/               pChDoc->ResizePage(aSize);
/*N*/
/*N*/                 // notify the controller
/*N*/                 // note: the controller is only available in in-place
/*N*/                 // Broadcast( SchVisAreaChangedHint( rRect ) );
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|* OLE-Status
|*
\************************************************************************/

/*N*/ ULONG SchChartDocShell::GetMiscStatus() const throw()
/*N*/ {
/*N*/   // Chart soll stets selber resizen
/*N*/   ULONG nStatus = SfxInPlaceObject::GetMiscStatus() |
/*N*/                   SVOBJ_MISCSTATUS_SERVERRESIZE     |
/*N*/                   SVOBJ_MISCSTATUS_RESIZEONPRINTERCHANGE;
/*N*/
/*N*/   return nStatus;
/*N*/ }

/*N*/ void SchChartDocShell::SetModified( BOOL bModified ) throw()
/*N*/ {
/*N*/   if( IsEnableSetModified() )
/*N*/   {
/*N*/       SfxInPlaceObject::SetModified( bModified );
/*N*/       DBG_ASSERT( pChDoc, "Invalid ChartModel" );
/*N*/       if( ! pChDoc->IsLockedBuild())
/*N*/           Broadcast( SfxSimpleHint( SFX_HINT_DOCCHANGED ) );
/*N*/   }
/*N*/ }



}
