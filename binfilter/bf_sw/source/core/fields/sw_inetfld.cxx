/*************************************************************************
 *
 *  $RCSfile: sw_inetfld.cxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: aw $ $Date: 2003-10-02 15:18:30 $
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

#include "hintids.hxx"

#ifndef _SFXMACITEM_HXX //autogen
#include <svtools/macitem.hxx>
#endif


#ifndef _CHARFMT_HXX //autogen
#include <charfmt.hxx>
#endif
#include "doc.hxx"
#include "inetfld.hxx"
#include "poolfmt.hxx"
#include "hints.hxx"


/*--------------------------------------------------------------------
    Beschreibung: SwINetFieldType by JP
 --------------------------------------------------------------------*/



SwINetFieldType::SwINetFieldType( SwDoc* pD )
    : SwFieldType( RES_INTERNETFLD ), pDoc( pD ),
    aNormalFmt( this, 0 ), aVisitFmt( this, 0 )
{
}



SwFieldType* SwINetFieldType::Copy() const
{
    return new SwINetFieldType( pDoc );
}



SwCharFmt* SwINetFieldType::GetCharFmt( const SwINetField& rFld )
{
    USHORT nId = RES_POOLCHR_INET_NORMAL;
    SwDepend* pDepend = &aNormalFmt;

    if( rFld.sURL.Len() && pDoc->IsVisitedURL( rFld.sURL ) )
    {
        nId = RES_POOLCHR_INET_VISIT;
        pDepend = &aVisitFmt;
    }

    SwCharFmt* pFmt = pDoc->GetCharFmtFromPool( nId );

    // noch nicht registriert ?
    if( !pDepend->GetRegisteredIn() )
        pFmt->Add( pDepend );       // anmelden

    return pFmt;
}

/*--------------------------------------------------------------------
    Beschreibung: SwINetFieldType by JP
 --------------------------------------------------------------------*/



SwINetField::SwINetField( SwINetFieldType* pTyp, USHORT nFmt,
                            const String& rURL, const String& rText )
    : SwField( pTyp, nFmt ), sURL( rURL ), sText( rText ),
    pMacroTbl( 0 )
{
}



SwINetField::~SwINetField()
{
    delete pMacroTbl;
}



String SwINetField::Expand() const
{
    return sText;
}



String SwINetField::GetCntnt(BOOL bName) const
{
    if( bName )
    {
        String aStr( sText );
        aStr += ' ';
        aStr += sURL;
        return aStr;
    }
    return Expand();
}



SwField* SwINetField::Copy() const
{
    SwINetField *pTmp = new SwINetField( (SwINetFieldType*)pType, nFormat,
                                            sURL, sText );
    pTmp->SetLanguage( GetLanguage() );
    pTmp->sTargetFrameName = sTargetFrameName;

    if( pMacroTbl )
        pTmp->pMacroTbl = new SvxMacroTableDtor( *pMacroTbl );

    return pTmp;
}

/*--------------------------------------------------------------------
    Beschreibung: Parameter setzen
 --------------------------------------------------------------------*/


const String& SwINetField::GetPar1() const
{
    return sURL;
}



String SwINetField::GetPar2() const
{
    return sText;
}



void SwINetField::SetPar1(const String& rStr)
{
    sURL = rStr;
}



void SwINetField::SetPar2(const String& rStr)
{
    sText = rStr;
}



SwCharFmt* SwINetField::GetCharFmt()
{
    return ((SwINetFieldType*)pType)->GetCharFmt( *this );
}



void SwINetField::SetMacroTbl( const SvxMacroTableDtor* pNewTbl )
{
    if( pNewTbl )
    {
        if( pMacroTbl )
            *pMacroTbl = *pNewTbl;
        else
            pMacroTbl = new SvxMacroTableDtor( *pNewTbl );
    }
    else if( pMacroTbl )
        delete pMacroTbl, pMacroTbl = 0;
}



void SwINetField::SetMacro( USHORT nEvent, const SvxMacro& rMacro )
{
    if( !pMacroTbl )
        pMacroTbl = new SvxMacroTableDtor;

    SvxMacro *pOldMacro;
    if( 0 != ( pOldMacro = pMacroTbl->Get( nEvent )) )
    {
        delete pOldMacro;
        pMacroTbl->Replace( nEvent, new SvxMacro( rMacro ) );
    }
    else
        pMacroTbl->Insert( nEvent, new SvxMacro( rMacro ) );
}



const SvxMacro* SwINetField::GetMacro( USHORT nEvent ) const
{
    const SvxMacro* pRet = 0;
    if( pMacroTbl && pMacroTbl->IsKeyValid( nEvent ) )
        pRet = pMacroTbl->Get( nEvent );
    return pRet;
}

#ifdef USED


String SwINetField::GetBookmark() const
{
    String sRet;
    USHORT nPos = sURL.Search( '#' );
    if( nPos < sURL.Len() )
        sRet = sURL.Copy( nPos+1 );
    return sRet;
}
#endif



