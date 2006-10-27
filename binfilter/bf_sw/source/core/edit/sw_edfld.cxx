/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_edfld.cxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-27 22:33:09 $
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


#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

#ifndef _EDITSH_HXX
#include <editsh.hxx>
#endif
#ifndef _NDTXT_HXX
#include <ndtxt.hxx>        // GetCurFld
#endif
#ifndef _FMTFLD_HXX //autogen
#include <fmtfld.hxx>
#endif
#ifndef _TXTFLD_HXX //autogen
#include <txtfld.hxx>
#endif
#ifndef _EXPFLD_HXX
#include <expfld.hxx>
#endif
#ifndef _COM_SUN_STAR_CONTAINER_XNAMEACCESS_HPP_
#include <com/sun/star/container/XNameAccess.hpp>
#endif

#ifndef _PAM_HXX
#include "pam.hxx"
#endif

#ifndef _DOC_HXX
#include "doc.hxx"
#endif

namespace binfilter {
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::container;
using namespace ::com::sun::star::lang;
using namespace ::rtl;


// wenn Selektion groesser Max Nodes oder mehr als Max Selektionen
// => keine Attribute
static const USHORT nMaxLookup = 40;

/*--------------------------------------------------------------------
    Beschreibung: Feldtypen zu einer ResId zaehlen
                  wenn 0 alle zaehlen
 --------------------------------------------------------------------*/


/*--------------------------------------------------------------------
    Beschreibung: Feldtypen zu einer ResId finden
                  wenn 0 alle finden
 --------------------------------------------------------------------*/

/*--------------------------------------------------------------------
    Beschreibung: Den ersten Typen mit ResId und Namen finden
 --------------------------------------------------------------------*/

/*--------------------------------------------------------------------
    Beschreibung: Feldtypen loeschen
 --------------------------------------------------------------------*/

/*--------------------------------------------------------------------
    Beschreibung: FieldType ueber Name loeschen
 --------------------------------------------------------------------*/



/*************************************************************************
|*
|*                  SwEditShell::Insert( SwField )
|*
|*    Beschreibung  an der Cursorposition ein Feld einfuegen
|*    Quelle:       vgl. SwEditShell::Insert( String )
|*
*************************************************************************/

/*************************************************************************
|*
|*                  SwEditShell::GetCurFld()
|*
|*    Beschreibung  Stehen die PaMs auf Feldern ?
|*    Quelle:       edtfrm.cxx:
|*
*************************************************************************/

/*N*/ inline SwTxtFld *GetDocTxtFld( const SwPosition* pPos )
/*N*/ {
/*N*/   SwTxtNode *pNode = pPos->nNode.GetNode().GetTxtNode();
/*N*/   if( pNode )
/*N*/       return pNode->GetTxtFld( pPos->nContent );
/*N*/   else
/*N*/       return 0;
/*N*/ }

/*N*/ SwField* SwEditShell::GetCurFld() const
/*N*/ {
/*N*/   // Wenn es keine Selektionen gibt, gilt der Wert der aktuellen
/*N*/   // Cursor-Position.
/*N*/
/*N*/   SwPaM* pCrsr = GetCrsr();
/*N*/   SwTxtFld *pTxtFld = GetDocTxtFld( pCrsr->Start() );
/*N*/   SwField *pCurFld = NULL;
/*N*/
    /* #108536# Field was only recognized if no selection was
        present. Now it is recognized if either the cursor is in the
        field or the selection spans exactly over the field. */
/*N*/   if( pTxtFld &&
/*N*/         pCrsr->GetNext() == pCrsr &&
/*N*/         pCrsr->Start()->nNode == pCrsr->End()->nNode &&
/*N*/         (pCrsr->End()->nContent.GetIndex() -
/*N*/          pCrsr->Start()->nContent.GetIndex()) <= 1)
/*N*/   {
/*?*/       pCurFld = (SwField*)pTxtFld->GetFld().GetFld();
/*?*/       // TabellenFormel ? wandel internen in externen Namen um
/*?*/       if( RES_TABLEFLD == pCurFld->GetTyp()->Which() )
/*?*/       {
/*?*/           const SwTableNode* pTblNd = IsCrsrInTbl();
/*?*/           ((SwTblField*)pCurFld)->PtrToBoxNm( pTblNd ? &pTblNd->GetTable() : 0 );
/*?*/       }
/*?*/
/*N*/   }

    /* #108536# removed handling of multi-selections */

/*N*/   return pCurFld;
/*N*/ }


/*************************************************************************
|*
|*                  SwEditShell::UpdateFlds()
|*
|*    Beschreibung  Stehen die PaMs auf Feldern ?
|*                  BP 12.05.92
|*
*************************************************************************/


/*-----------------13.05.92 10:54-------------------
 Liefert den logischen fuer die Datenbank zurueck
 --------------------------------------------------*/


/*N*/ const SwDBData& SwEditShell::GetDBDesc() const
/*N*/ {
/*N*/   return GetDoc()->GetDBDesc();
/*N*/ }






/*--------------------------------------------------------------------
    Beschreibung:  Alle Expression-Felder erneuern
 --------------------------------------------------------------------*/

/*N*/ SwNewDBMgr* SwEditShell::GetNewDBMgr() const
/*N*/ {
/*N*/   return GetDoc()->GetNewDBMgr();
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung: Feldtypen einfuegen
 --------------------------------------------------------------------*/








/*N*/ BOOL SwEditShell::IsLabelDoc() const
/*N*/ {
/*N*/   return GetDoc()->IsLabelDoc();
/*N*/ }
/* -----------------------------21.12.99 12:53--------------------------------

 ---------------------------------------------------------------------------*/
/* -----------------------------03.08.2001 12:04------------------------------

 ---------------------------------------------------------------------------*/
/* -----------------28.11.2002 17:53-----------------
 *
 * --------------------------------------------------*/

}
