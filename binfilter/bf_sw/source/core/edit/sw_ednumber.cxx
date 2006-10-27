/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_ednumber.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-27 22:34:26 $
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
#ifndef _EDIMP_HXX
#include <edimp.hxx>
#endif
#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _NDTXT_HXX
#include <ndtxt.hxx>
#endif
#ifndef _VISCRS_HXX
#include <viscrs.hxx>
#endif
#ifndef _PARATR_HXX
#include <paratr.hxx>
#endif
namespace binfilter {



/*N*/ SV_IMPL_VARARR_SORT( _SwPamRanges, SwPamRange )










// Numerierung Outline Regelwerk





// setzt, wenn noch keine Numerierung, sonst wird geaendert
// arbeitet mit alten und neuen Regeln, nur Differenzen aktualisieren

// Absaetze ohne Numerierung, aber mit Einzuegen

// Loeschen, Splitten der Aufzaehlungsliste



// Hoch-/Runterstufen








// Abfrage von Oultine Informationen:











// Outlines and SubOutline are ReadOnly?

/** Test whether outline may be moved (bCopy == false)
 *                           or copied (bCopy == true)
 * Verify these conditions:
 * 1) outline must be within main body (and not in redline)
 * 2) outline must not be within table
 * 3) if bCopy is set, outline must not be write protected
 */










/*N*/ BYTE SwEditShell::GetNumLevel( BOOL* pHasChilds ) const
/*N*/ {
/*N*/   // gebe die akt. Ebene zurueck, auf der sich der Point vom Cursor befindet
/*N*/   BYTE nLevel = NO_NUMBERING;
/*N*/
/*N*/   SwPaM* pCrsr = GetCrsr();
/*N*/   const SwTxtNode* pTxtNd = pCrsr->GetNode()->GetTxtNode();
/*N*/   const SwNumRule* pRule = pTxtNd->GetNumRule();
/*N*/   if( pRule && pTxtNd->GetNum() )
/*N*/   {
/*N*/       nLevel = pTxtNd->GetNum()->GetLevel();
/*N*/       if( pHasChilds )
/*N*/       {
/*?*/           *pHasChilds = FALSE;
/*?*/           // dann teste ob die NumSection noch weitere UnterEbenen hat:
/*?*/           // zuerst ueber alle TextNodes und falls da nichts gefunden
/*?*/           // wurde, ueber die Formate und deren GetInfo bis zu den Nodes
/*?*/
/*?*/           BYTE nLvl = nLevel & ~NO_NUMLEVEL;
/*?*/           if( nLvl + 1 < MAXLEVEL )
/*?*/           {
/*?*/               const String& rRule = pRule->GetName();
/*?*/               SwModify* pMod;
/*?*/               const SfxPoolItem* pItem;
/*?*/               USHORT i, nMaxItems = GetDoc()->GetAttrPool().GetItemCount( RES_PARATR_NUMRULE);
/*?*/               for( i = 0; i < nMaxItems; ++i )
/*?*/                   if( 0 != (pItem = GetDoc()->GetAttrPool().GetItem( RES_PARATR_NUMRULE, i ) ) &&
/*?*/                       0 != ( pMod = (SwModify*)((SwNumRuleItem*)pItem)->GetDefinedIn()) &&
/*?*/                       ((SwNumRuleItem*)pItem)->GetValue().Len() &&
/*?*/                       ((SwNumRuleItem*)pItem)->GetValue() == rRule &&
/*?*/                       pMod->IsA( TYPE( SwTxtNode )) &&
/*?*/                       ((SwTxtNode*)pMod)->GetNodes().IsDocNodes() &&
/*?*/                       ((SwTxtNode*)pMod)->GetNum() &&
/*?*/                       nLvl < ( ((SwTxtNode*)pMod)->GetNum()->GetLevel() & ~NO_NUMLEVEL) )
/*?*/                   {
/*?*/                       *pHasChilds = TRUE;
/*?*/                       break;
/*?*/                   }
/*?*/
/*?*/               if( !*pHasChilds )
/*?*/               {
/*?*/                   DBG_BF_ASSERT(0, "STRIP"); //STRIP001 SwNRuleLowerLevel aHnt( rRule, nLvl );
/*?*/               }
/*?*/
/*?*/           }
/*N*/       }
/*N*/   }
/*N*/
/*N*/   return nLevel;
/*N*/ }

/*N*/ const SwNumRule* SwEditShell::GetCurNumRule() const
/*N*/ {
/*N*/   return GetDoc()->GetCurrNumRule( *GetCrsr()->GetPoint() );
/*N*/ }














}
