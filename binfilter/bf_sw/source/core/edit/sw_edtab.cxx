/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_edtab.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: kz $ $Date: 2006-11-08 12:30:19 $
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


#pragma hdrstop

#define ITEMID_BOXINFO      SID_ATTR_BORDER_INNER
#ifndef _HINTIDS_HXX
#include <hintids.hxx>
#endif

#define _SVSTDARR_ULONGS



#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

#ifndef _EDITSH_HXX
#include <editsh.hxx>
#endif
#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _HINTS_HXX
#include <hints.hxx>
#endif
#ifndef _NODE_HXX
#include <node.hxx>
#endif
#ifndef _MDIEXP_HXX
#include <mdiexp.hxx>
#endif
namespace binfilter {








/*--------------------------------------------------------------------
    Beschreibung: Tabellenfelder einer Tabelle updaten
 --------------------------------------------------------------------*/
/*N*/ void SwEditShell::UpdateTable()
/*N*/ {
/*N*/   const SwTableNode* pTblNd = IsCrsrInTbl();
/*N*/
/*N*/   // Keine Arme keine Kekse
/*N*/   if( pTblNd )
/*N*/   {
/*N*/       StartAllAction();
/*N*/       StartUndo();
/*N*/       EndAllTblBoxEdit();
/*N*/       SwTableFmlUpdate aTblUpdate( (SwTable*)&pTblNd->GetTable() );
/*N*/       GetDoc()->UpdateTblFlds( &aTblUpdate );
/*N*/       EndUndo();
/*N*/       EndAllAction();
/*N*/   }
/*N*/ }

    // Change Modus erfragen/setzen
/*N*/ USHORT SwEditShell::GetTblChgMode() const
/*N*/ {
/*N*/   USHORT nMode;
/*N*/   const SwTableNode* pTblNd = IsCrsrInTbl();
/*N*/   if( pTblNd )
/*N*/       nMode = pTblNd->GetTable().GetTblChgMode();
/*N*/   else
/*?*/       nMode = 0;//STRIP001GetTblChgDefaultMode();
/*N*/   return nMode;
/*N*/ }




    // Zellenbreiten ueber Min/Max Berechnung an Tabellenbreite anpassen






        // setze das InsertDB als Tabelle Undo auf:

}
