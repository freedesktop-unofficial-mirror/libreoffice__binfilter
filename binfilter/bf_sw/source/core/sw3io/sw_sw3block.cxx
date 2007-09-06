/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_sw3block.cxx,v $
 *
 *  $Revision: 1.8 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 12:24:22 $
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


#ifdef _MSC_VER
#pragma hdrstop
#endif


#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

#ifndef _DOC_HXX
#include <doc.hxx>
#endif

#ifndef _ERRHDL_HXX
#include <errhdl.hxx>
#endif

#ifndef _SW3IMP_HXX
#include <sw3imp.hxx>
#endif

#ifndef _SWSWERROR_H
#include <swerror.h>
#endif
namespace binfilter {

#define STREAM_STGREAD  ( STREAM_READ | STREAM_SHARE_DENYWRITE | STREAM_NOCREATE )
#define STREAM_STGWRITE ( STREAM_READ | STREAM_WRITE | STREAM_SHARE_DENYWRITE )

sal_Char __FAR_DATA N_BLOCKINFO[] = "AutotextInfo";


/*************************************************************************
*
*   Enumeration aller Textbausteine
*
*************************************************************************/

// Das Directory enthaelt die Kurz- und Langnamen der Bausteine. Die
// Bausteine selbst sind unter ihrem Kurznamen in eigenen Streams
// abgelegt. Die Namen selbst sind nach folgender Konvention aufgebaut:
// 1. Zeichen: #
// ! == 0x01
// / == 0x0F
// \ == 0x0C
// : == 0x0A
// . == 0x0E


// Der Fehlercode wird zurueckgeliefert. Das Ende der Liste
// wird durch einen leeren Short-Namen angezeigt.


/*************************************************************************
*
*   I/O einzelner Textbausteine
*
*************************************************************************/


////////////////////////////////////////////////////////////////////////////


// Textbaustein-Konversionsmode ein/ausschalten
// Das Flag verhindert das Commit auf die Root nach dem Schreiben
// eines Textbausteins; daher wird hier committed, wenn das
// Flag geloescht wird.



// ggf. eine SvPersist-Instanz einrichten

/*N*/ BOOL Sw3IoImp::CheckPersist()
/*N*/ {
/*N*/   // Haben wir schon einen Persist?
/*N*/   if( pDoc->GetPersist() )
/*N*/       return TRUE;
        DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001 /*?*/    pPersist = new Sw3Persist;
/*N*/ }

// ggf. eine SvPersist-Instanz freigeben


//////////////////////////////////////////////////////////////////////////



}
