/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_edsect.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-27 22:34:47 $
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

#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _EDITSH_HXX
#include <editsh.hxx>
#endif
#ifndef _PAM_HXX
#include <pam.hxx>
#endif
#ifndef _DOCARY_HXX
#include <docary.hxx>
#endif
#ifndef _SECTION_HXX
#include <section.hxx>
#endif

namespace binfilter {


    // SS fuer Bereiche




/*N*/ const SwSection* SwEditShell::GetCurrSection() const
/*N*/ {
/*N*/   if( IsTableMode() )
/*?*/       return 0;
/*N*/
/*N*/   return GetDoc()->GetCurrSection( *GetCrsr()->GetPoint() );
/*N*/ }

/*-----------------17.03.99 11:53-------------------
 * SwEditShell::GetAnySection liefert den fuer Spalten
 * zustaendigen Bereich, bei Fussnoten kann es nicht der
 * Bereich innerhalb der Fussnote sein.
 * --------------------------------------------------*/




/*N*/ BOOL SwEditShell::IsAnySectionInDoc( BOOL bChkReadOnly, BOOL bChkHidden, BOOL bChkTOX ) const
/*N*/ {
/*N*/   const SwSectionFmts& rFmts = GetDoc()->GetSections();
/*N*/   USHORT nCnt = rFmts.Count();
        USHORT n=0;
/*N*/   for( n = 0; n < nCnt; ++n )
/*N*/   {
/*N*/       SectionType eTmpType;
/*N*/       const SwSectionFmt* pFmt = rFmts[ n ];
/*N*/       if( pFmt->IsInNodesArr() &&
/*N*/           (bChkTOX  ||
/*N*/               (eTmpType = pFmt->GetSection()->GetType()) != TOX_CONTENT_SECTION
/*N*/               && TOX_HEADER_SECTION != eTmpType ))
/*N*/       {
/*N*/           const SwSection& rSect = *rFmts[ n ]->GetSection();
/*N*/           if( (!bChkReadOnly && !bChkHidden ) ||
/*N*/               (bChkReadOnly && rSect.IsProtectFlag() ) ||
/*N*/               (bChkHidden && rSect.IsHiddenFlag() ) )
/*N*/               break;
/*N*/       }
/*N*/   }
/*N*/   return n != nCnt;
/*N*/ }












// search inside the cursor selection for full selected sections.
// if any part of section in the selection return 0.
// if more than one in the selection return the count


/**
 * Find the suitable node for a special insert (alt-enter).
 * This should enable inserting text before/after sections and tables.
 *
 * A node is found if:
 * 1) the innermost table/section is not in a write-protected area
 * 2) pCurrentPos is at or just before an end node
 *    (or at or just after a start node)
 * 3) there are only start/end nodes between pCurrentPos and the innermost
 *    table/section
 *
 * If a suitable node is found, an SwNode* is returned; else it is NULL.
 */


/** a node can be special-inserted (alt-Enter) whenever lcl_SpecialInsertNode
    finds a suitable position
*/


/** check whether a node cen be special-inserted (alt-Enter), and do so. Return
    whether insertion was possible.
 */

}
