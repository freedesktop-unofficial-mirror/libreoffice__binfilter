/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sc_imoptdlg.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-07 18:59:59 $
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

#ifdef PCH
// auto strip #include "ui_pch.hxx"
#endif

#pragma hdrstop

#include "imoptdlg.hxx"
// auto strip #include "scresid.hxx"
#include "imoptdlg.hrc"

#ifndef _RTL_TENCINFO_H
#include <rtl/tencinfo.h>
#endif

static const sal_Char pStrFix[] = "FIX";

// auto strip #ifndef _TOOLS_DEBUG_HXX //STRIP001 added by binary filter//========================================================================
// auto strip #include <tools/debug.hxx> //STRIP001 added by binary filter // ScDelimiterTable
// auto strip #endif //STRIP001 added by binary filter//========================================================================
namespace binfilter {

class ScDelimiterTable
{
public:
        ScDelimiterTable( const String& rDelTab )
            :   theDelTab ( rDelTab ),
                cSep      ( '\t' ),
                nCount    ( rDelTab.GetTokenCount('\t') ),
                nIter     ( 0 )
            {}

    USHORT  GetCode( const String& rDelimiter ) const;
     String GetDelimiter( sal_Unicode nCode ) const;

    String  FirstDel()  { nIter = 0; return theDelTab.GetToken( nIter, cSep ); }
    String  NextDel()   { nIter +=2; return theDelTab.GetToken( nIter, cSep ); }

private:
    const String        theDelTab;
    const sal_Unicode   cSep;
    const xub_StrLen    nCount;
    xub_StrLen          nIter;
};

//------------------------------------------------------------------------

/*N*/ USHORT ScDelimiterTable::GetCode( const String& rDel ) const
/*N*/ {
/*N*/   sal_Unicode nCode = 0;
/*N*/   xub_StrLen i = 0;
/*N*/
/*N*/   if ( nCount >= 2 )
/*N*/   {
/*N*/       while ( i<nCount )
/*N*/       {
/*N*/           if ( rDel == theDelTab.GetToken( i, cSep ) )
/*N*/           {
/*N*/               nCode = (sal_Unicode) theDelTab.GetToken( i+1, cSep ).ToInt32();
/*N*/               i     = nCount;
/*N*/           }
/*N*/           else
/*N*/               i += 2;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   return nCode;
/*N*/ }

//------------------------------------------------------------------------

/*N*/ String ScDelimiterTable::GetDelimiter( sal_Unicode nCode ) const
/*N*/ {
/*N*/   String aStrDel;
/*N*/   xub_StrLen i = 0;
/*N*/
/*N*/   if ( nCount >= 2 )
/*N*/   {
/*N*/       while ( i<nCount )
/*N*/       {
/*N*/           if ( nCode == (sal_Unicode) theDelTab.GetToken( i+1, cSep ).ToInt32() )
/*N*/           {
/*N*/               aStrDel = theDelTab.GetToken( i, cSep );
/*N*/               i       = nCount;
/*N*/           }
/*N*/           else
/*N*/               i += 2;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   return aStrDel;
/*N*/ }

//========================================================================
// ScImportOptionsDlg
//========================================================================

//STRIP001 ScImportOptionsDlg::ScImportOptionsDlg(
//STRIP001         Window*                 pParent,
//STRIP001         BOOL                    bAscii,
//STRIP001         const ScImportOptions*  pOptions,
//STRIP001         const String*           pStrTitle,
//STRIP001         BOOL                    bMultiByte,
//STRIP001         BOOL                    bOnlyDbtoolsEncodings,
//STRIP001         BOOL                    bImport )
//STRIP001
//STRIP001  :   ModalDialog ( pParent, ScResId( RID_SCDLG_IMPORTOPT ) ),
//STRIP001      aBtnOk      ( this, ScResId( BTN_OK ) ),
//STRIP001      aBtnCancel  ( this, ScResId( BTN_CANCEL ) ),
//STRIP001      aBtnHelp    ( this, ScResId( BTN_HELP ) ),
//STRIP001      aFtFieldSep ( this, ScResId( FT_FIELDSEP ) ),
//STRIP001      aEdFieldSep ( this, ScResId( ED_FIELDSEP ) ),
//STRIP001      aFtTextSep  ( this, ScResId( FT_TEXTSEP ) ),
//STRIP001      aEdTextSep  ( this, ScResId( ED_TEXTSEP ) ),
//STRIP001      aFtFont     ( this, ScResId( FT_FONT ) ),
//STRIP001         aLbFont     ( this, ScResId( bAscii ? DDLB_FONT : LB_FONT ) ),
//STRIP001         aFlFieldOpt ( this, ScResId( FL_FIELDOPT ) ),
//STRIP001         aCbFixed    ( this, ScResId( CB_FIXEDWIDTH ) )
//STRIP001 {
//STRIP001 /*N*/    // im Ctor-Initializer nicht moeglich (MSC kann das nicht):
//STRIP001 /*N*/    pFieldSepTab = new ScDelimiterTable( String(ScResId(SCSTR_FIELDSEP)) );
//STRIP001 /*N*/    pTextSepTab  = new ScDelimiterTable( String(ScResId(SCSTR_TEXTSEP)) );
//STRIP001 /*N*/
//STRIP001 /*N*/    String aStr = pFieldSepTab->FirstDel();
//STRIP001 /*N*/    sal_Unicode nCode;
//STRIP001 /*N*/
//STRIP001 /*N*/    while ( aStr.Len() > 0 )
//STRIP001 /*N*/    {
//STRIP001 /*N*/        aEdFieldSep.InsertEntry( aStr );
//STRIP001 /*N*/        aStr = pFieldSepTab->NextDel();
//STRIP001 /*N*/    }
//STRIP001 /*N*/
//STRIP001 /*N*/    aStr = pTextSepTab->FirstDel();
//STRIP001 /*N*/
//STRIP001 /*N*/    while ( aStr.Len() > 0 )
//STRIP001 /*N*/    {
//STRIP001 /*N*/        aEdTextSep.InsertEntry( aStr );
//STRIP001 /*N*/        aStr = pTextSepTab->NextDel();
//STRIP001 /*N*/    }
//STRIP001 /*N*/
//STRIP001 /*N*/    aEdFieldSep.SetText( aEdFieldSep.GetEntry(0) );
//STRIP001 /*N*/    aEdTextSep.SetText( aEdTextSep.GetEntry(0) );
//STRIP001 /*N*/
//STRIP001 /*N*/     if ( bOnlyDbtoolsEncodings )
//STRIP001 /*N*/     {   //!TODO: Unicode and MultiByte would need work in each filter
//STRIP001 /*N*/         // Think of field lengths in dBase export
//STRIP001 /*N*/        if ( bMultiByte )
//STRIP001 /*N*/             aLbFont.FillFromDbTextEncodingMap( bImport, RTL_TEXTENCODING_INFO_UNICODE );
//STRIP001 /*N*/        else
//STRIP001 /*N*/             aLbFont.FillFromDbTextEncodingMap( bImport, RTL_TEXTENCODING_INFO_UNICODE |
//STRIP001 /*N*/                 RTL_TEXTENCODING_INFO_MULTIBYTE );
//STRIP001 /*N*/     }
//STRIP001 /*N*/     else if ( !bAscii )
//STRIP001 /*N*/     {   //!TODO: Unicode would need work in each filter
//STRIP001 /*N*/        if ( bMultiByte )
//STRIP001 /*N*/             aLbFont.FillFromTextEncodingTable( bImport, RTL_TEXTENCODING_INFO_UNICODE );
//STRIP001 /*N*/        else
//STRIP001 /*N*/            aLbFont.FillFromTextEncodingTable( bImport, RTL_TEXTENCODING_INFO_UNICODE |
//STRIP001 /*N*/                 RTL_TEXTENCODING_INFO_MULTIBYTE );
//STRIP001 /*N*/    }
//STRIP001 /*N*/    else
//STRIP001 /*N*/    {
//STRIP001 /*N*/        if ( pOptions )
//STRIP001 /*N*/        {
//STRIP001 /*N*/            nCode = pOptions->nFieldSepCode;
//STRIP001 /*N*/            aStr  = pFieldSepTab->GetDelimiter( nCode );
//STRIP001 /*N*/
//STRIP001 /*N*/            if ( !aStr.Len() )
//STRIP001 /*N*/                aEdFieldSep.SetText( String((sal_Unicode)nCode) );
//STRIP001 /*N*/            else
//STRIP001 /*N*/                aEdFieldSep.SetText( aStr );
//STRIP001 /*N*/
//STRIP001 /*N*/            nCode = pOptions->nTextSepCode;
//STRIP001 /*N*/            aStr  = pTextSepTab->GetDelimiter( nCode );
//STRIP001 /*N*/
//STRIP001 /*N*/            if ( !aStr.Len() )
//STRIP001 /*N*/                aEdTextSep.SetText( String((sal_Unicode)nCode) );
//STRIP001 /*N*/            else
//STRIP001 /*N*/                aEdTextSep.SetText( aStr );
//STRIP001 /*N*/        }
//STRIP001 /*N*/        // all encodings allowed, even Unicode
//STRIP001 /*N*/        aLbFont.FillFromTextEncodingTable( bImport );
//STRIP001 /*N*/    }
//STRIP001 /*N*/
//STRIP001 /*N*/     if( bAscii )
//STRIP001 /*N*/     {
//STRIP001 /*N*/         Size aWinSize( GetSizePixel() );
//STRIP001 /*N*/         aWinSize.Height() = aCbFixed.GetPosPixel().Y() + aCbFixed.GetSizePixel().Height();
//STRIP001 /*N*/         Size aDiffSize( LogicToPixel( Size( 0, 6 ), MapMode( MAP_APPFONT ) ) );
//STRIP001 /*N*/         aWinSize.Height() += aDiffSize.Height();
//STRIP001 /*N*/         SetSizePixel( aWinSize );
//STRIP001 /*N*/         aCbFixed.Show();
//STRIP001 /*N*/         aCbFixed.SetClickHdl( LINK( this, ScImportOptionsDlg, FixedWidthHdl ) );
//STRIP001 /*N*/         aCbFixed.Check( FALSE );
//STRIP001 /*N*/     }
//STRIP001 /*N*/     else
//STRIP001 /*N*/     {
//STRIP001 /*N*/         aFlFieldOpt.SetText( aFtFont.GetText() );
//STRIP001 /*N*/        aFtFieldSep.Hide();
//STRIP001 /*N*/         aFtTextSep.Hide();
//STRIP001 /*N*/         aFtFont.Hide();
//STRIP001 /*N*/        aEdFieldSep.Hide();
//STRIP001 /*N*/         aEdTextSep.Hide();
//STRIP001 /*N*/         aCbFixed.Hide();
//STRIP001 /*N*/        aLbFont.GrabFocus();
//STRIP001 /*N*/     }
//STRIP001 /*N*/
//STRIP001 /*N*/    aLbFont.SelectTextEncoding( pOptions ? pOptions->eCharSet :
//STRIP001 /*N*/        gsl_getSystemTextEncoding() );
//STRIP001 /*N*/
//STRIP001 /*N*/    // optionaler Titel:
//STRIP001 /*N*/    if ( pStrTitle )
//STRIP001 /*N*/        SetText( *pStrTitle );
//STRIP001 /*N*/
//STRIP001 /*N*/    FreeResource();
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 __EXPORT ScImportOptionsDlg::~ScImportOptionsDlg()
//STRIP001 {
//STRIP001  delete pFieldSepTab;
//STRIP001  delete pTextSepTab;
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 void ScImportOptionsDlg::GetImportOptions( ScImportOptions& rOptions ) const
//STRIP001 {
//STRIP001 /*N*/    rOptions.SetTextEncoding( aLbFont.GetSelectTextEncoding() );
//STRIP001 /*N*/
//STRIP001 /*N*/     if ( aCbFixed.IsVisible() )
//STRIP001 /*N*/    {
//STRIP001 /*N*/        rOptions.nFieldSepCode = GetCodeFromCombo( aEdFieldSep );
//STRIP001 /*N*/        rOptions.nTextSepCode  = GetCodeFromCombo( aEdTextSep );
//STRIP001 /*N*/         rOptions.bFixedWidth = aCbFixed.IsChecked();
//STRIP001 /*N*/    }
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 USHORT ScImportOptionsDlg::GetCodeFromCombo( const ComboBox& rEd ) const
//STRIP001 {
//STRIP001  ScDelimiterTable* pTab;
//STRIP001  String  aStr( rEd.GetText() );
//STRIP001  USHORT  nCode;
//STRIP001
//STRIP001  if ( &rEd == &aEdTextSep )
//STRIP001      pTab = pTextSepTab;
//STRIP001  else
//STRIP001      pTab = pFieldSepTab;
//STRIP001
//STRIP001  if ( !aStr.Len() )
//STRIP001  {
//STRIP001      nCode = 0;          // kein Trennzeichen
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      nCode = pTab->GetCode( aStr );
//STRIP001
//STRIP001      if ( nCode == 0 )
//STRIP001          nCode = (USHORT)aStr.GetChar(0);
//STRIP001  }
//STRIP001
//STRIP001  return nCode;
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 IMPL_LINK( ScImportOptionsDlg, FixedWidthHdl, CheckBox*, pCheckBox )
//STRIP001 {
//STRIP001     if( pCheckBox == &aCbFixed )
//STRIP001     {
//STRIP001         BOOL bEnable = !aCbFixed.IsChecked();
//STRIP001         aFtFieldSep.Enable( bEnable );
//STRIP001         aEdFieldSep.Enable( bEnable );
//STRIP001         aFtTextSep.Enable( bEnable );
//STRIP001         aEdTextSep.Enable( bEnable );
//STRIP001     }
//STRIP001     return 0;
//STRIP001 }


//------------------------------------------------------------------------
//  Der Options-String darf kein Semikolon mehr enthalten (wegen Pickliste)
//  darum ab Version 336 Komma stattdessen


/*N*/ ScImportOptions::ScImportOptions( const String& rStr )
/*N*/ {
/*N*/     bFixedWidth = FALSE;
/*N*/     nFieldSepCode = 0;
/*N*/   if ( rStr.GetTokenCount(',') >= 3 )
/*N*/   {
/*N*/         String aToken( rStr.GetToken( 0, ',' ) );
/*N*/         if( aToken.EqualsIgnoreCaseAscii( pStrFix ) )
/*N*/             bFixedWidth = TRUE;
/*N*/         else
/*N*/             nFieldSepCode = (sal_Unicode) aToken.ToInt32();
/*N*/       nTextSepCode  = (sal_Unicode) rStr.GetToken(1,',').ToInt32();
/*N*/       aStrFont      = rStr.GetToken(2,',');
/*N*/       eCharSet      = ScGlobal::GetCharsetValue(aStrFont);
/*N*/   }
/*N*/ }
/*N*/
//------------------------------------------------------------------------

/*N*/ String ScImportOptions::BuildString() const
/*N*/ {
/*N*/   String  aResult;
/*N*/
/*N*/     if( bFixedWidth )
/*N*/         aResult.AppendAscii( pStrFix );
/*N*/     else
/*N*/         aResult += String::CreateFromInt32(nFieldSepCode);
/*N*/   aResult += ',';
/*N*/   aResult += String::CreateFromInt32(nTextSepCode);
/*N*/   aResult += ',';
/*N*/   aResult += aStrFont;
/*N*/
/*N*/   return aResult;
/*N*/ }

//------------------------------------------------------------------------

/*N*/ void ScImportOptions::SetTextEncoding( rtl_TextEncoding nEnc )
/*N*/ {
/*N*/   eCharSet = (nEnc == RTL_TEXTENCODING_DONTKNOW ?
/*N*/       gsl_getSystemTextEncoding() : nEnc);
/*N*/   aStrFont = ScGlobal::GetCharsetString( nEnc );
/*N*/ }
}
