/*************************************************************************
 *
 *  $RCSfile: starmath_utility.cxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:19:18 $
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

#ifndef _SFXAPP_HXX //autogen
#include <bf_sfx2/app.hxx>
#endif
#ifndef _SV_VIRDEV_HXX //autogen
#include <vcl/virdev.hxx>
#endif
#ifndef NOOLDSV //autogen
#include <vcl/system.hxx>
#endif
#ifndef _STRING_HXX
#include <tools/string.hxx>
#endif
#ifndef _TOOLS_TENCCVT_HXX
#include <tools/tenccvt.hxx>
#endif
#ifndef _OSL_THREAD_H_
#include <osl/thread.h>
#endif

#include "starmath.hrc"

#include "utility.hxx"
#include "dialog.hxx"
#include "view.hxx"
#include "smdll.hxx"


/*N*/ SmViewShell * SmGetActiveView()
/*N*/   // return pointer to active SmViewShell, if this is not possible
/*N*/   // return 0 instead.
/*N*/ {
/*N*/   SfxViewShell *pView = SfxViewShell::Current();
/*N*/   return PTR_CAST(SmViewShell, pView);
/*N*/ }


////////////////////////////////////////


/*N*/ SvStream& operator << (SvStream& rStream, const SmFace& rFont)
/*N*/ {
/*N*/   rStream.WriteByteString(ExportString(rFont.GetName()));
/*N*/   rStream << (ULONG)rFont.GetFamily();
/*N*/     rStream << (ULONG)GetSOStoreTextEncoding( rFont.GetCharSet() );
/*N*/   rStream << (ULONG)rFont.GetWeight();
/*N*/   rStream << (ULONG)rFont.GetItalic();
/*N*/
/*N*/   return rStream;
/*N*/ }

/*N*/ SvStream& operator >> (SvStream& rStream, SmFace& rFont)
/*N*/ {
/*N*/   ULONG   nData;
/*N*/     ByteString  aByteStr;
/*N*/
/*N*/     rStream.ReadByteString( aByteStr );
/*N*/     rFont.SetName( ImportString( aByteStr ) );
/*N*/   rStream >> nData;
/*N*/   rFont.SetFamily((FontFamily)nData);
/*N*/   rStream >> nData;
/*N*/     rFont.SetCharSet( GetSOLoadTextEncoding( (rtl_TextEncoding) nData ) );
/*N*/   rStream >> nData;
/*N*/   rFont.SetWeight((FontWeight)nData);
/*N*/   rStream >> nData;
/*N*/   rFont.SetItalic((FontItalic)nData);
/*N*/
/*N*/   return rStream;
/*N*/ }

/*?*/ void ReadSM20Font(SvStream& rStream, Font& rFont)
/*?*/ {
/*?*/   BOOL    bData;
/*?*/   ULONG   nData;
/*?*/     ByteString  aByteStr;
/*?*/
/*?*/     rStream.ReadByteString( aByteStr );
/*?*/     rFont.SetName( ImportString( aByteStr ) );
/*?*/   rStream >> nData;
/*?*/   rFont.SetFamily((FontFamily)nData);
/*?*/   rStream >> nData;
/*?*/     rFont.SetCharSet( GetSOLoadTextEncoding( (rtl_TextEncoding) nData ) );
/*?*/   rStream >> nData;
/*?*/   rFont.SetWeight((FontWeight)nData);
/*?*/   rStream >> bData;
/*?*/   if (bData)
/*?*/       rFont.SetItalic(ITALIC_NORMAL);
/*?*/   else
/*?*/       rFont.SetItalic(ITALIC_NONE);
/*?*/ }


////////////////////////////////////////////////////////////
//
// SmRectCache
//


/*N*/ SmRectCache::Key::Key(const XubString &rText, const Font &rFont)
/*N*/ {
/*N*/ }


//STRIP001 BOOL SmRectCache::Key::operator <  (const Key &rKey) const
//STRIP001 {
//STRIP001 #ifdef never
//STRIP001  BOOL  bRes = FALSE;
//STRIP001
//STRIP001  if (aText < rKey.aText)
//STRIP001      bRes = TRUE;
//STRIP001  else if ()
//STRIP001
//STRIP001  return      aText       <  rKey.aText
//STRIP001          ||  aText       == rKey.aText        &&  aFontName   < rKey.aFontName
//STRIP001          ||  aFontName   == rKey.aFontname    &&  aFontSize   < rKey.aFontSize
//STRIP001          ||  aFontSize   == rKey.aFontSize    &&  eFontWeight < rKey.eFontWeight
//STRIP001          ||  eFontWeight == rKey.eFontWeight  &&  eFontItalic < rKey.eFontItalic;
//STRIP001 #endif
//STRIP001  return FALSE;
//STRIP001 }


//STRIP001 BOOL SmRectCache::Key::operator == (const Key &rKey) const
//STRIP001 {
//STRIP001  return      aText       == rKey.aText
//STRIP001          &&  aFontName   == rKey.aFontName
//STRIP001          &&  aFontSize   == rKey.aFontSize
//STRIP001          &&  eFontWeight == rKey.eFontWeight
//STRIP001          &&  eFontItalic == rKey.eFontItalic;
//STRIP001 }


/*N*/ SmRectCache::SmRectCache()
/*N*/ {
/*N*/   pVirDev = 0;
/*N*/ }


/*N*/ SmRectCache::~SmRectCache()
/*N*/ {
/*N*/   delete pVirDev;
/*N*/ }


/*N*/ const SmRect * SmRectCache::Search(const Key &rKey) const
/*N*/ {
/*N*/   return 0;
/*N*/ }


/*N*/ const SmRect * SmRectCache::Add(const Key &rKey, const SmRect &rRect)
/*N*/ {
/*N*/   return (const SmRect *)-1;
/*N*/ }


/*N*/ VirtualDevice * SmRectCache::GetVirDev()
/*N*/ {
/*N*/   if (!pVirDev)
/*N*/   {
/*N*/       SmViewShell *pView = SmGetActiveView();
/*N*/       if (pView)
/*?*/           pVirDev = new VirtualDevice( pView->GetGraphicWindow() );
/*N*/       else
/*N*/           pVirDev = new VirtualDevice;
/*N*/       pVirDev->SetMapMode( MapMode(MAP_100TH_MM) );
/*N*/   }
/*N*/   DBG_ASSERT(pVirDev->GetMapMode().GetMapUnit() == MAP_100TH_MM,
/*N*/              "Sm : falscher MapMode");
/*N*/
/*N*/   return pVirDev;
/*N*/ }


/*N*/ void SmRectCache::Reset()
/*N*/ {
/*N*/ }


////////////////////////////////////////////////////////////

#define TE_UCS2     "UCS2"
#define PRE_TE      "<?"
#define POST_TE     ")>"


//STRIP001 ByteString ConvertUnknownCharacter(sal_Unicode ch)
//STRIP001 {
//STRIP001     ByteString aString( RTL_CONSTASCII_STRINGPARAM( PRE_TE TE_UCS2 ) );
//STRIP001     aString.Append( "(" );
//STRIP001  aString += ByteString::CreateFromInt32(ch);
//STRIP001     aString += POST_TE;
//STRIP001  return aString;
//STRIP001 }


/*N*/ const ByteString ExportString( const String& rString )
/*N*/ {
/*N*/   ByteString  aString;
/*N*/
/*N*/     rtl_TextEncoding nEnc = RTL_TEXTENCODING_MS_1252;
/*N*/   for (xub_StrLen i = 0; i < rString.Len(); i++)
/*N*/   {
/*N*/         sal_Unicode ch = rString.GetChar(i);
/*N*/       if ((ch != '\r') && (ch != '\n') && (ch != '\t'))
/*N*/       {
/*N*/             sal_Char cChar = ByteString::ConvertFromUnicode( ch, nEnc, FALSE );
/*N*/           if (cChar == 0)
/*?*/                   {DBG_ASSERT(0, "STRIP");} //STRIP001 /*?*/              aString += ConvertUnknownCharacter(ch);
/*N*/           else
/*N*/               aString += cChar;
/*N*/       }
/*N*/       else
/*N*/             aString += (sal_Char) ch;
/*N*/   }
/*N*/
/*N*/   aString.ConvertLineEnd(LINEEND_CRLF);
/*N*/     return aString;
/*N*/ }

#define TEXTENCODINGTAB_LEN     12

static const struct
{
    const char         *pText;
    rtl_TextEncoding    nEnc;
} aTextEncodingTab[ TEXTENCODINGTAB_LEN ] =
{
    { TE_UCS2,        RTL_TEXTENCODING_UCS2 },  // is RTL_TEXTENCODING_UNICODE in 6.0
    { "DONTKNOW",     RTL_TEXTENCODING_DONTKNOW },
    { "ANSI",         RTL_TEXTENCODING_MS_1252 },
    { "MAC",          RTL_TEXTENCODING_APPLE_ROMAN },
    { "PC437",        RTL_TEXTENCODING_IBM_437 },
    { "PC850",        RTL_TEXTENCODING_ASCII_US },
    { "PC860",        RTL_TEXTENCODING_IBM_860 },
    { "PC861",        RTL_TEXTENCODING_IBM_861 },
    { "PC863",        RTL_TEXTENCODING_IBM_863 },
    { "PC865",        RTL_TEXTENCODING_IBM_865 },
    { "SYSTEM",       RTL_TEXTENCODING_DONTKNOW },
    { "SYMBOL",       RTL_TEXTENCODING_SYMBOL }
};

//STRIP001 int GetTextEncodingTabIndex( const String &rTxt, xub_StrLen nPos )
//STRIP001 {
//STRIP001     int nRes = -1;
//STRIP001     for (int i = 0;  i < TEXTENCODINGTAB_LEN  &&  nRes == -1;  ++i)
//STRIP001     {
//STRIP001         if (nPos == rTxt.SearchAscii( aTextEncodingTab[i].pText , nPos ))
//STRIP001             nRes = i;
//STRIP001     }
//STRIP001     return nRes;
//STRIP001 }

/*N*/ const String ImportString( const ByteString& rByteString )
/*N*/ {
/*N*/     String  aString( rByteString, RTL_TEXTENCODING_MS_1252 );
/*N*/
/*N*/     const xub_StrLen nPreLen  = sizeof( PRE_TE ) - 1;
/*N*/     const xub_StrLen nPostLen = sizeof( POST_TE ) - 1;
/*N*/
/*N*/     xub_StrLen nPreStart = 0;
/*N*/     while( STRING_NOTFOUND != ( nPreStart =
/*N*/                                     aString.SearchAscii( PRE_TE, nPreStart )) )
/*N*/     {
/*?*/           DBG_ASSERT(0, "STRIP"); //STRIP001 /*N*/         //
//STRIP001 /*N*/         // convert 'unknown character' to unicode character
//STRIP001 /*N*/         //
//STRIP001 /*?*/         xub_StrLen nTeStart = nPreStart + nPreLen;
//STRIP001 /*?*/         xub_StrLen nTeLen   = 0;
//STRIP001 /*?*/         int nIdx = GetTextEncodingTabIndex( aString, nTeStart );
//STRIP001 /*?*/         DBG_ASSERT( nIdx >= 0, "text-encoding is missing" );
//STRIP001 /*?*/         rtl_TextEncoding nEnc = RTL_TEXTENCODING_DONTKNOW;
//STRIP001 /*?*/         if (nIdx >= 0)
//STRIP001 /*?*/         {
//STRIP001 /*?*/             nEnc = aTextEncodingTab[ nIdx ].nEnc;
//STRIP001 /*?*/             nTeLen = strlen( aTextEncodingTab[ nIdx ].pText );
//STRIP001 /*?*/         }
//STRIP001 /*?*/         if (RTL_TEXTENCODING_DONTKNOW == nEnc)
//STRIP001 /*?*/             nEnc = osl_getThreadTextEncoding();
//STRIP001 /*?*/         //
//STRIP001 /*?*/         xub_StrLen nNumStart = nTeStart + nTeLen + 1, // +1 because of "("
//STRIP001 /*?*/                    nReplLen;
//STRIP001 /*?*/         xub_StrLen nPostStart = aString.SearchAscii( POST_TE, nNumStart );
//STRIP001 /*?*/         String sRepl;
//STRIP001 /*?*/         if( STRING_NOTFOUND != nPostStart )
//STRIP001 /*?*/         {
//STRIP001 /*?*/             INT32 nCharVal = aString.Copy( nNumStart, nPostStart - nNumStart ).ToInt32();
//STRIP001 /*?*/             DBG_ASSERT( nCharVal != 0, "String -> Int32 failed ?" );
//STRIP001 /*?*/             if (RTL_TEXTENCODING_UNICODE == nEnc)
//STRIP001 /*?*/             {
//STRIP001 /*?*/                 if (nCharVal)
//STRIP001 /*?*/                     sRepl = (sal_Unicode) nCharVal;
//STRIP001 /*?*/             }
//STRIP001 /*?*/             else
//STRIP001 /*?*/             {
//STRIP001 /*?*/                 DBG_ASSERT( 0 <= nCharVal  &&  nCharVal <= 256,
//STRIP001 /*?*/                         "character value out of range" );
//STRIP001 /*?*/                 sRepl = ByteString::ConvertToUnicode( nCharVal, nEnc );
//STRIP001 /*?*/             }
//STRIP001 /*?*/             DBG_ASSERT( sRepl.Len() || !nCharVal, "conversion failed" );
//STRIP001 /*?*/             nReplLen = nPostStart + nPostLen - nPreStart;
//STRIP001 /*?*/         }
//STRIP001 /*?*/         else
//STRIP001 /*?*/         {
//STRIP001 /*?*/             DBG_ERROR( "import error: 'unknown character' delimiter missing" );
//STRIP001 /*?*/             sRepl.AssignAscii( RTL_CONSTASCII_STRINGPARAM( "<?>" ) );
//STRIP001 /*?*/             nReplLen = nPreLen;
//STRIP001 /*?*/         }
//STRIP001 /*?*/
//STRIP001 /*?*/         aString.Replace( nPreStart, nReplLen, sRepl );
//STRIP001 /*?*/         nPreStart += sRepl.Len();
/*N*/     }
/*N*/
/*N*/     // in old 2.0 or 3.0 formulas the strings to be imported do have an
/*N*/     // additional '\0' character at the end that gets removed here.
/*N*/     if (aString.Len())
/*N*/         aString.EraseTrailingChars( '\0' );
/*N*/
/*N*/   aString.ConvertLineEnd();
/*N*/     return aString;
/*N*/ }

////////////////////////////////////////////////////////////


/**************************************************************************/

/*N*/ SmPickList::SmPickList(USHORT nInitSize, USHORT nMaxSize) :
/*N*/   SfxPtrArr((BYTE) nInitSize, 1)
/*N*/ {
/*N*/   nSize = nMaxSize;
/*N*/ }


/*N*/ SmPickList::~SmPickList()
/*N*/ {
/*N*/   Clear();
/*N*/ }


//STRIP001 SmPickList& SmPickList::operator=(const SmPickList& rList)
//STRIP001 {
//STRIP001  USHORT  nPos;
//STRIP001
//STRIP001  Clear();
//STRIP001  nSize = rList.nSize;
//STRIP001  for (nPos = 0; nPos < rList.Count(); nPos++)
//STRIP001      InsertPtr(nPos, CreateItem(rList.Get(nPos)));
//STRIP001
//STRIP001  return *this;
//STRIP001 }


//STRIP001 void SmPickList::Insert(const void *pItem)
//STRIP001 {
//STRIP001  Remove(pItem);
//STRIP001  InsertPtr(0, CreateItem(pItem));
//STRIP001
//STRIP001  if (Count() > nSize)
//STRIP001  {
//STRIP001      DestroyItem(GetPtr(nSize));
//STRIP001      RemovePtr(nSize, 1);
//STRIP001  }
//STRIP001 }


//STRIP001 void SmPickList::Update(const void *pItem, const void *pNewItem)
//STRIP001 {
//STRIP001  USHORT  nPos;
//STRIP001
//STRIP001  for (nPos = 0; nPos < Count(); nPos++)
//STRIP001      if (CompareItem(GetPtr(nPos), pItem))
//STRIP001      {
//STRIP001          DestroyItem(GetPtr(nPos));
//STRIP001          GetPtr(nPos) = CreateItem(pNewItem);
//STRIP001          break;
//STRIP001      }
//STRIP001 }

//STRIP001 void SmPickList::Remove(const void *pItem)
//STRIP001 {
//STRIP001  USHORT  nPos;
//STRIP001
//STRIP001  for (nPos = 0; nPos < Count(); nPos++)
//STRIP001      if (CompareItem(GetPtr(nPos), pItem))
//STRIP001      {
//STRIP001          DestroyItem(GetPtr(nPos));
//STRIP001          RemovePtr(nPos, 1);
//STRIP001          break;
//STRIP001      }
//STRIP001 }

//STRIP001 void SmPickList::SetSize(USHORT nNewSize)
//STRIP001 {
//STRIP001  nSize = nNewSize;
//STRIP001
//STRIP001  while (Count() > nSize)
//STRIP001  {
//STRIP001      DestroyItem(GetPtr(Count() - 1));
//STRIP001      RemovePtr(Count() - 1, 1);
//STRIP001  }
//STRIP001 }


//STRIP001 BOOL SmPickList::Contains(const void *pItem) const
//STRIP001 {
//STRIP001  USHORT  nPos;
//STRIP001
//STRIP001  for (nPos = 0; nPos < Count(); nPos++)
//STRIP001      if (CompareItem(GetPtr(nPos), pItem))
//STRIP001          return TRUE;
//STRIP001
//STRIP001  return FALSE;
//STRIP001 }


/*N*/ void SmPickList::Clear()
/*N*/ {
/*N*/   USHORT  nPos;
/*N*/
/*N*/   for (nPos = 0; nPos < Count(); nPos++)
/*?*/       DestroyItem(GetPtr(nPos));
/*N*/
/*N*/   RemovePtr(0, Count());
/*N*/ }


//STRIP001 SvStream& operator << (SvStream& rStream, const SmPickList& rPickList)
//STRIP001 {
//STRIP001  USHORT      nPos;
//STRIP001
//STRIP001  rStream << 'p';
//STRIP001  rStream << rPickList.nSize;
//STRIP001  rStream << rPickList.Count();
//STRIP001
//STRIP001  for (nPos = 0; nPos < rPickList.Count(); nPos++)
//STRIP001      rPickList.SaveItem(rStream, rPickList.GetObject(nPos));
//STRIP001
//STRIP001  return rStream;
//STRIP001 }

//STRIP001 SvStream& operator >> (SvStream& rStream, SmPickList& rPickList)
//STRIP001 {
//STRIP001  char    cTag;
//STRIP001  USHORT  nCount, nPos;
//STRIP001  void   *pItem;
//STRIP001
//STRIP001  rPickList.Clear();
//STRIP001
//STRIP001  rStream >> cTag;
//STRIP001  if (cTag == 'p')
//STRIP001  {
//STRIP001      rStream >> rPickList.nSize;
//STRIP001      rStream >> nCount;
//STRIP001
//STRIP001      for (nPos = 0; nPos < nCount; nPos++)
//STRIP001      {
//STRIP001          pItem = rPickList.CreateItem(String());
//STRIP001          rPickList.LoadItem(rStream, pItem);
//STRIP001          rPickList.InsertPtr(nPos, pItem);
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  return rStream;
//STRIP001 }


/**************************************************************************/
/**************************************************************************/

/*?*/ void * SmFontPickList::CreateItem(const String& rString)
/*?*/ {
/*?*/ DBG_ASSERT(0, "STRIP"); return NULL;//STRIP001    return new Font();
/*?*/ }

/*?*/ void * SmFontPickList::CreateItem(const void *pItem)
/*?*/ {
/*?*/ DBG_ASSERT(0, "STRIP"); return NULL;//STRIP001    return new Font(*((Font *) pItem));
/*?*/ }

/*?*/ void SmFontPickList::DestroyItem(void *pItem)
/*?*/ {
/*?*/ DBG_ASSERT(0, "STRIP"); //STRIP001    delete (Font *)pItem;
/*?*/ }

/*?*/ BOOL SmFontPickList::CompareItem(const void *pFirstItem, const void *pSecondItem) const
/*?*/ {
/*?*/ DBG_ASSERT(0, "STRIP"); return FALSE;//STRIP001   Font    *pFirstFont, *pSecondFont;
//STRIP001
//STRIP001  pFirstFont  = (Font *)pFirstItem;
//STRIP001  pSecondFont = (Font *)pSecondItem;
//STRIP001
//STRIP001  if (pFirstFont->GetName() == pSecondFont->GetName())
//STRIP001      if ((pFirstFont->GetFamily()  == pSecondFont->GetFamily())  &&
//STRIP001          (pFirstFont->GetCharSet() == pSecondFont->GetCharSet()) &&
//STRIP001          (pFirstFont->GetWeight()  == pSecondFont->GetWeight())  &&
//STRIP001          (pFirstFont->GetItalic()  == pSecondFont->GetItalic()))
//STRIP001          return (TRUE);
//STRIP001
//STRIP001  return FALSE;
/*?*/ }

/*?*/ String SmFontPickList::GetStringItem(void *pItem)
/*?*/ {
/*?*/   DBG_ASSERT(0, "STRIP"); String  aString; return aString;//STRIP001  Font   *pFont;
//STRIP001  String  aString;
//STRIP001     const sal_Char *pDelim = ", ";
//STRIP001
//STRIP001  pFont = (Font *)pItem;
//STRIP001
//STRIP001  aString = pFont->GetName();
//STRIP001
//STRIP001  if (pFont->GetItalic() != ITALIC_NONE)
//STRIP001     {
//STRIP001         aString.AppendAscii( pDelim );
//STRIP001      aString += String(SmResId(RID_FONTITALIC));
//STRIP001     }
//STRIP001  if (pFont->GetWeight() == WEIGHT_BOLD)
//STRIP001     {
//STRIP001         aString.AppendAscii( pDelim );
//STRIP001      aString += String(SmResId(RID_FONTBOLD));
//STRIP001     }
//STRIP001
//STRIP001  return (aString);
/*?*/ }

/*?*/ void SmFontPickList::LoadItem(SvStream& rStream, void *pItem)
/*?*/ {
/*?*/   DBG_ASSERT(0, "STRIP"); //STRIP001  rStream >> *((Font *)pItem);
/*?*/ }

/*?*/ void SmFontPickList::SaveItem(SvStream& rStream, const void *pItem) const
/*?*/ {
/*?*/   DBG_ASSERT(0, "STRIP"); //STRIP001  rStream << *(const Font *) pItem;
/*?*/ }

//STRIP001 void SmFontPickList::Insert(const Font &rFont)
//STRIP001 {
//STRIP001  SmPickList::Insert((void *)&rFont);
//STRIP001 }

//STRIP001 void SmFontPickList::Update(const Font &rFont, const Font &rNewFont)
//STRIP001 {
//STRIP001  SmPickList::Update((void *)&rFont, (void *)&rNewFont);
//STRIP001 }

//STRIP001 void SmFontPickList::Remove(const Font &rFont)
//STRIP001 {
//STRIP001  SmPickList::Remove((void *)&rFont);
//STRIP001 }


//STRIP001 void SmFontPickList::ReadFrom(const SmFontDialog& rDialog)
//STRIP001 {
//STRIP001  Insert(rDialog.GetFont());
//STRIP001 }

//STRIP001 void SmFontPickList::WriteTo(SmFontDialog& rDialog) const
//STRIP001 {
//STRIP001  rDialog.SetFont(Get());
//STRIP001 }


/**************************************************************************/


/**************************************************************************/

//STRIP001 IMPL_LINK( SmFontPickListBox, SelectHdl, ListBox *, pListBox )
//STRIP001 {
//STRIP001  USHORT  nPos;
//STRIP001  String  aString;
//STRIP001
//STRIP001  nPos = GetSelectEntryPos();
//STRIP001
//STRIP001  if (nPos != 0)
//STRIP001  {
//STRIP001      SmFontPickList::Insert(Get(nPos));
//STRIP001      aString = GetEntry(nPos);
//STRIP001      RemoveEntry(nPos);
//STRIP001      InsertEntry(aString, 0);
//STRIP001  }
//STRIP001
//STRIP001  SelectEntryPos(0);
//STRIP001
//STRIP001  return 0;
//STRIP001 }


//STRIP001 SmFontPickListBox::SmFontPickListBox(Window* pParent, WinBits nWinStyle, USHORT nMax) :
//STRIP001  SmFontPickList(nMax, nMax),
//STRIP001  ListBox(pParent, nWinStyle)
//STRIP001 {
//STRIP001  SetSelectHdl(LINK(this, SmFontPickListBox, SelectHdl));
//STRIP001 }


//STRIP001 SmFontPickListBox::SmFontPickListBox(Window* pParent, const ResId& rResId, USHORT nMax) :
//STRIP001  SmFontPickList(nMax, nMax),
//STRIP001  ListBox(pParent, rResId)
//STRIP001 {
//STRIP001  SetSelectHdl(LINK(this, SmFontPickListBox, SelectHdl));
//STRIP001 }


//STRIP001 SmFontPickListBox& SmFontPickListBox::operator=(const SmFontPickList& rList)
//STRIP001 {
//STRIP001  USHORT nPos;
//STRIP001
//STRIP001  *(SmFontPickList *)this = rList;
//STRIP001
//STRIP001  for (nPos = 0; nPos < Count(); nPos++)
//STRIP001      InsertEntry(GetStringItem(GetPtr(nPos)), nPos);
//STRIP001
//STRIP001  if (Count() > 0)
//STRIP001      SelectEntry(GetStringItem(GetPtr(0)));
//STRIP001
//STRIP001  return *this;
//STRIP001 }

//STRIP001 void SmFontPickListBox::Insert(const Font &rFont)
//STRIP001 {
//STRIP001  SmFontPickList::Insert(rFont);
//STRIP001
//STRIP001  RemoveEntry(GetStringItem(GetPtr(0)));
//STRIP001  InsertEntry(GetStringItem(GetPtr(0)), 0);
//STRIP001  SelectEntry(GetStringItem(GetPtr(0)));
//STRIP001
//STRIP001  while (GetEntryCount() > nSize)
//STRIP001      RemoveEntry(GetEntryCount() - 1);
//STRIP001
//STRIP001  return;
//STRIP001 }


//STRIP001 void SmFontPickListBox::Update(const Font &rFont, const Font &rNewFont)
//STRIP001 {
//STRIP001  SmFontPickList::Update(rFont, rNewFont);
//STRIP001
//STRIP001  // ********************** hier fehlt noch was
//STRIP001
//STRIP001  return;
//STRIP001 }


//STRIP001 void SmFontPickListBox::Remove(const Font &rFont)
//STRIP001 {
//STRIP001  SmFontPickList::Remove(rFont);
//STRIP001
//STRIP001  // ********************** hier fehlt noch was
//STRIP001
//STRIP001  return;
//STRIP001 }

////////////////////////////////////////

/*N*/ void SmFace::Impl_Init()
/*N*/ {
/*N*/     SetSize( GetSize() );
/*N*/     SetTransparent( TRUE );
/*N*/     SetAlign( ALIGN_BASELINE );
/*N*/     SetColor( COL_AUTO );
/*N*/ }

/*N*/ void SmFace::SetSize(const Size& rSize)
/*N*/ {
/*N*/   Size  aSize (rSize);
/*N*/
/*N*/   // check the requested size against minimum value
/*N*/   static int __READONLY_DATA  nMinVal = SmPtsTo100th_mm(2);
/*N*/
/*N*/   if (aSize.Height() < nMinVal)
/*N*/       aSize.Height() = nMinVal;
/*N*/
/*N*/   //! we don't force a maximum value here because this may prevent eg the
/*N*/   //! parentheses in "left ( ... right )" from matching up with large
/*N*/   //! bodies (eg stack{...} with many entries).
/*N*/   //! Of course this is holds only if characters are used and not polygons.
/*N*/
/*N*/   Font::SetSize(aSize);
/*N*/ }


/*N*/ long SmFace::GetBorderWidth() const
/*N*/ {
/*N*/   if (nBorderWidth < 0)
/*N*/       return GetDefaultBorderWidth();
/*N*/   else
/*N*/       return nBorderWidth;
/*N*/ }

/*N*/ SmFace & SmFace::operator = (const SmFace &rFace)
/*N*/ {
/*N*/   Font::operator = (rFace);
/*N*/   nBorderWidth = -1;
/*N*/   return *this;
/*N*/ }


/*N*/ SmFace & operator *= (SmFace &rFace, const Fraction &rFrac)
/*N*/   // scales the width and height of 'rFace' by 'rFrac' and returns a
/*N*/   // reference to 'rFace'.
/*N*/   // It's main use is to make scaling fonts look easier.
/*N*/ { const Size &rFaceSize = rFace.GetSize();
/*N*/
/*N*/   rFace.SetSize(Size(Fraction(rFaceSize.Width())  *= rFrac,
/*N*/                      Fraction(rFaceSize.Height()) *= rFrac));
/*N*/   return rFace;
/*N*/ }



