/*************************************************************************
 *
 *  $RCSfile: sw_rdtox.cxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: aw $ $Date: 2003-10-02 15:33:06 $
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


#pragma hdrstop

#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _PAM_HXX
#include <pam.hxx>
#endif
#ifndef _RDSWG_HXX
#include <rdswg.hxx>
#endif
#ifndef _DOCTXM_HXX
#include <doctxm.hxx>
#endif
#ifndef _SWSWERROR_H
#include <swerror.h>
#endif
#ifndef _POOLFMT_HXX
#include <poolfmt.hxx>
#endif
#ifndef _SWSTYLENAMEMAPPER_HXX
#include <SwStyleNameMapper.hxx>
#endif


//////////////////////////////////////////////////////////////////////////////

// Achtung: Jede Routine nimmt an, dass der Record-Header bereits eingelesen
// ist. Sie arbeitet den Record so weit ab wie moeglich und schliesst den
// Vorgang mit end() ab.

//////////////////////////////////////////////////////////////////////////////

//STRIP001 SwTOXBase* SwSwgReader::InTOXBase()
//STRIP001 {
//STRIP001  // Den TOXtype einlesen
//STRIP001  BYTE eType;
//STRIP001  r >> eType;
//STRIP001  String aName( GetText() );
//STRIP001  if( !r ) return NULL;
//STRIP001  TOXTypes eTOXType = (TOXTypes) eType;
//STRIP001  // nach dem TOXType suchen
//STRIP001  USHORT nTOXType = pDoc->GetTOXTypeCount( eTOXType );
//STRIP001  const SwTOXType* pTOXType = NULL;
//STRIP001  for( USHORT n = 0; n < nTOXType; n++ )
//STRIP001  {
//STRIP001      const SwTOXType* p = pDoc->GetTOXType( eTOXType, n );
//STRIP001      if( p->GetTypeName() == aName )
//STRIP001      {
//STRIP001          pTOXType = p; break;
//STRIP001      }
//STRIP001  }
//STRIP001  // Falls nicht vorhanden, am Dokument einfuegen
//STRIP001  if( !pTOXType )
//STRIP001  {
//STRIP001      pDoc->InsertTOXType( SwTOXType ( eTOXType, aName ) );
//STRIP001      pTOXType = pDoc->GetTOXType( eTOXType, nTOXType );
//STRIP001  }
//STRIP001  // jetzt muss er da sein!
//STRIP001  if( !pTOXType )
//STRIP001  {
//STRIP001      Error(); return NULL;
//STRIP001  }
//STRIP001  // Die Variablen einlesen
//STRIP001  USHORT nCreaType;
//STRIP001  r >> nCreaType;
//STRIP001  String aTitle( GetText() );
//STRIP001  if( !r ) return NULL;
//STRIP001  // Die SwForm einlesen
//STRIP001  BYTE nPat, nTmpl;
//STRIP001  r >> nPat >> nTmpl;
//STRIP001  SwForm aForm(eType);
//STRIP001  if( nPat )
//STRIP001  {
//STRIP001      for( USHORT i = 0; i < nPat; i++ )
//STRIP001      {
//STRIP001          String aText( GetText() );
//STRIP001          if ( !r ) return NULL;
//STRIP001          if( aText.Len() )
//STRIP001              aText = SwForm::ConvertPatternFrom51( aText, eTOXType );
//STRIP001          if( i < aForm.GetFormMax() )
//STRIP001              aForm.SetPattern( i, aText );
//STRIP001      }
//STRIP001  }
//STRIP001  if( nTmpl )
//STRIP001  {
//STRIP001      for( USHORT i = 0; i < nTmpl; i++ )
//STRIP001      {
//STRIP001          String aText( GetText() );
//STRIP001          if ( !r ) return NULL;
//STRIP001          if( i < aForm.GetFormMax() )
//STRIP001          {
//STRIP001              if( !aText.Len() )
//STRIP001              {
//STRIP001                  // Bug 37672: falls keiner gefunden wird, nehme
//STRIP001                  //          die defaults
//STRIP001                  USHORT nPoolIdOffset = 0;
//STRIP001                  switch( eType )
//STRIP001                  {
//STRIP001                      case TOX_INDEX:
//STRIP001                          nPoolIdOffset = RES_POOLCOLL_TOX_IDXH -
//STRIP001                                          RES_POOLCOLL_REGISTER_BEGIN;
//STRIP001                          break;
//STRIP001                      case TOX_CONTENT:
//STRIP001                          if( 6 > i )
//STRIP001                              nPoolIdOffset = RES_POOLCOLL_TOX_CNTNTH -
//STRIP001                                              RES_POOLCOLL_REGISTER_BEGIN;
//STRIP001                          else
//STRIP001                              nPoolIdOffset = RES_POOLCOLL_TOX_CNTNT6 - 6 -
//STRIP001                                              RES_POOLCOLL_REGISTER_BEGIN;
//STRIP001                          break;
//STRIP001                      case TOX_USER:
//STRIP001                          nPoolIdOffset = RES_POOLCOLL_TOX_USERH -
//STRIP001                                          RES_POOLCOLL_REGISTER_BEGIN;
//STRIP001                          break;
//STRIP001                  }
//STRIP001
//STRIP001                  aText = *SwStyleNameMapper::GetRegisterUINameArray()[ nPoolIdOffset + i ];
//STRIP001              }
//STRIP001              aForm.SetTemplate( i, aText );
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  //fill tab stop positions into the patterns
//STRIP001  aForm.AdjustTabStops(*pDoc);
//STRIP001
//STRIP001  SwTOXBase* pBase = new SwTOXBase( pTOXType, aForm, nCreaType, aTitle );
//STRIP001  pBase->SetTOXName( pDoc->GetUniqueTOXBaseName( *pTOXType ) );
//STRIP001  // Zuletzt noch die Spezial-Variablen
//STRIP001  switch( eType )
//STRIP001  {
//STRIP001      case TOX_INDEX: {
//STRIP001          USHORT nOptions;
//STRIP001          r >> nOptions;
//STRIP001          pBase->SetOptions( nOptions );
//STRIP001          } break;
//STRIP001      case TOX_CONTENT: {
//STRIP001          USHORT nLevel;
//STRIP001          r >> nLevel;
//STRIP001          pBase->SetLevel( nLevel );
//STRIP001          } break;
//STRIP001      case TOX_USER:
//STRIP001          aName = GetText();
//STRIP001          pBase->SetTemplateName( aName );
//STRIP001          break;
//STRIP001  }
//STRIP001  if( !r )
//STRIP001  {
//STRIP001      delete pBase; return NULL;
//STRIP001  }
//STRIP001  return pBase;
//STRIP001 }

// Verzeichnis-Block

//STRIP001 void SwSwgReader::InTOX( SwNodeIndex& rPos, SwTxtNode* pNd )
//STRIP001 {
//STRIP001  if( r.next() != SWG_TOXDESC )
//STRIP001      Error();
//STRIP001  else
//STRIP001  {
//STRIP001      long nSkip = 0;
//STRIP001      if( aHdr.nVersion >= SWG_VER_TOXDATA ) {
//STRIP001          if( r.next() != SWG_DATA ) {
//STRIP001              Error(); return;
//STRIP001          }
//STRIP001          nSkip = r.getskip();
//STRIP001      }
//STRIP001      SwTOXBase* pBase = InTOXBase();
//STRIP001      if( !pBase ) return;
//STRIP001      BOOL bInLastNode = FALSE;
//STRIP001      USHORT nOff1 = 0, nOff2 = 0;
//STRIP001      if( nSkip ) {
//STRIP001          // Neu ab Version 2.06: Anfangs- und Endbereich
//STRIP001          // Des TOX-Bereichs einlesen
//STRIP001          r >> bInLastNode >> nOff1 >> nOff2;
//STRIP001          r.skip( nSkip );
//STRIP001      }
//STRIP001
//STRIP001      r.next();
//STRIP001      ULONG nStart = rPos.GetIndex();
//STRIP001      // Im Gegensatz zu einer Section wird dieser Text nicht als eigene
//STRIP001      // Section, sondern als ganz normaler Text verstanden.
//STRIP001      USHORT nNodes;
//STRIP001      r >> nNodes;
//STRIP001      r.next();
//STRIP001      for( USHORT i = 1; i <= nNodes && r.good(); i++)
//STRIP001      {
//STRIP001          switch( r.cur() )
//STRIP001          {
//STRIP001              case SWG_TEXTNODE:
//STRIP001                  FillTxtNode( pNd, rPos, 0 );
//STRIP001                  break;
//STRIP001              case SWG_GRFNODE:
//STRIP001                  InGrfNode( rPos );
//STRIP001                  break;
//STRIP001              case SWG_OLENODE:
//STRIP001                  InOleNode( rPos );
//STRIP001                  break;
//STRIP001              case SWG_TABLE:
//STRIP001                  InTable( rPos );
//STRIP001                  break;
//STRIP001              default:
//STRIP001                  // unbekannte Nodes
//STRIP001                  r.skipnext();
//STRIP001          }
//STRIP001          pNd = NULL;
//STRIP001      }
//STRIP001      // Den TOX aufspannen, falls da was ist
//STRIP001      // der PaM steht jetzt auf dem letzten eingelesenen Node
//STRIP001      BOOL bRes = TRUE;
//STRIP001      ULONG nEnd = rPos.GetIndex() - 1;
//STRIP001      if( bInLastNode ) nStart--;
//STRIP001      if( nStart <= nEnd )
//STRIP001          bRes = 0 != pDoc->InsertTableOf( nStart, nEnd, *pBase );
//STRIP001      delete pBase;
//STRIP001      if( !bRes && !bNew )
//STRIP001          Error( ERR_SWG_INTERNAL_ERROR );
//STRIP001  }
//STRIP001 }


