/*************************************************************************
 *
 *  $RCSfile: txmsrt.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:50:02 $
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
#ifndef _TXMSRT_HXX
#define _TXMSRT_HXX

#ifndef _LANG_HXX
#include <tools/lang.hxx>
#endif
#ifndef _TOX_HXX
#include <tox.hxx>
#endif
class CharClass;
namespace binfilter {


class SwCntntNode;
class SwTxtNode;
class SwTxtTOXMark;
class SwIndex;
class SwFmtFld;
//STRIP001 class IndexEntrySupplierWrapper;

enum TOXSortType
{
    TOX_SORT_INDEX,
    TOX_SORT_CUSTOM,
    TOX_SORT_CONTENT,
    TOX_SORT_PARA,
    TOX_SORT_TABLE,
    TOX_SORT_AUTHORITY
};

//STRIP001 struct SwTOXSource
//STRIP001 {
//STRIP001  const SwCntntNode* pNd;
//STRIP001  xub_StrLen nPos;
//STRIP001  BOOL bMainEntry;
//STRIP001
//STRIP001  SwTOXSource() : pNd(0), nPos(0), bMainEntry(FALSE) {}
//STRIP001  SwTOXSource( const SwCntntNode* pNode, xub_StrLen n, BOOL bMain )
//STRIP001      : pNd(pNode), nPos(n), bMainEntry(bMain)
//STRIP001  {}
//STRIP001 };

//STRIP001 SV_DECL_VARARR( SwTOXSources, SwTOXSource, 0, 10 )

class SwTOXInternational
{
//STRIP001  IndexEntrySupplierWrapper* pIndexWrapper;
//STRIP001  CharClass* pCharClass;
//STRIP001  LanguageType eLang;
//STRIP001     String sSortAlgorithm;
//STRIP001     USHORT nOptions;
//STRIP001
//STRIP001  void Init();

public:
    SwTOXInternational( LanguageType nLang, USHORT nOptions,
                        const String& rSortAlgorithm ){DBG_ASSERT(0, "STRIP");} //STRIP001 const String& rSortAlgorithm );
//STRIP001  SwTOXInternational( const SwTOXInternational& );
//STRIP001  ~SwTOXInternational();
//STRIP001
//STRIP001     sal_Int32 Compare( const String& rTxt1, const String& rTxtReading1,
//STRIP001                        const ::com::sun::star::lang::Locale& rLocale1,
//STRIP001                        const String& rTxt2, const String& rTxtReading2,
//STRIP001                        const ::com::sun::star::lang::Locale& rLocale2 ) const;
//STRIP001
//STRIP001     inline BOOL IsEqual( const String& rTxt1, const String& rTxtReading1,
//STRIP001                          const ::com::sun::star::lang::Locale& rLocale1,
//STRIP001                          const String& rTxt2, const String& rTxtReading2,
//STRIP001                          const ::com::sun::star::lang::Locale& rLocale2 ) const
//STRIP001  {
//STRIP001         return 0 == Compare( rTxt1, rTxtReading1, rLocale1,
//STRIP001                              rTxt2, rTxtReading2, rLocale2 );
//STRIP001  }
//STRIP001
//STRIP001     inline BOOL IsLess( const String& rTxt1, const String& rTxtReading1,
//STRIP001                         const ::com::sun::star::lang::Locale& rLocale1,
//STRIP001                         const String& rTxt2, const String& rTxtReading2,
//STRIP001                         const ::com::sun::star::lang::Locale& rLocale2 ) const
//STRIP001  {
//STRIP001         return -1 == Compare( rTxt1, rTxtReading1, rLocale1,
//STRIP001                               rTxt2, rTxtReading2, rLocale2 );
//STRIP001  }
//STRIP001
//STRIP001     String GetIndexKey( const String& rTxt, const String& rTxtReading,
//STRIP001                         const ::com::sun::star::lang::Locale& rLcl ) const;
//STRIP001
//STRIP001  String GetFollowingText( BOOL bMorePages ) const;
//STRIP001
//STRIP001  String ToUpper( const String& rStr, xub_StrLen nPos ) const;
//STRIP001  inline BOOL IsNumeric( const String& rStr ) const;
};

/*--------------------------------------------------------------------
     Beschreibung: Klassen fuer die Sortierung der Verzeichnisse
 --------------------------------------------------------------------*/

struct SwTOXSortTabBase
{
//STRIP001  SwTOXSources aTOXSources;
//STRIP001     ::com::sun::star::lang::Locale aLocale;
//STRIP001  const SwTxtNode* pTOXNd;
//STRIP001  const SwTxtTOXMark* pTxtMark;
//STRIP001  const SwTOXInternational* pTOXIntl;
//STRIP001  ULONG nPos;
//STRIP001  xub_StrLen nCntPos;
//STRIP001     USHORT nType;
//STRIP001  static USHORT nOpt;

    SwTOXSortTabBase( TOXSortType nType,
                      const SwCntntNode* pTOXSrc,
                      const SwTxtTOXMark* pTxtMark,
                      const SwTOXInternational* pIntl,
                      const ::com::sun::star::lang::Locale* pLocale = NULL ){DBG_ASSERT(0, "STRIP");} //STRIP001 const ::com::sun::star::lang::Locale* pLocale = NULL );

//STRIP001  USHORT  GetType() const         { return nType; }
//STRIP001  USHORT  GetOptions() const      { return nOpt; }

//STRIP001  virtual void    FillText( SwTxtNode& rNd, const SwIndex& rInsPos, USHORT nAuthField = 0) const;
//STRIP001  virtual USHORT  GetLevel()  const = 0;
//STRIP001  virtual BOOL    operator==( const SwTOXSortTabBase& );
//STRIP001  virtual BOOL    operator<( const SwTOXSortTabBase& );
//STRIP001
//STRIP001  virtual String  GetURL() const;
//STRIP001
//STRIP001     inline void GetTxt( String&, String& ) const;
//STRIP001     inline const ::com::sun::star::lang::Locale& GetLocale() const;
//STRIP001
private:
//STRIP001  BOOL bValidTxt;
//STRIP001     String sSortTxt;
//STRIP001     String sSortTxtReading;

//STRIP001     virtual void _GetText( String&, String& ) = 0;
};

//STRIP001 inline void SwTOXSortTabBase::GetTxt( String& rSortTxt,
//STRIP001                                       String& rSortTxtReading ) const
//STRIP001 {
//STRIP001  if( !bValidTxt )
//STRIP001  {
//STRIP001      SwTOXSortTabBase* pThis = (SwTOXSortTabBase*)this;
//STRIP001         pThis->_GetText( pThis->sSortTxt, pThis->sSortTxtReading );
//STRIP001      pThis->bValidTxt = TRUE;
//STRIP001  }

//STRIP001     rSortTxt = sSortTxt;
//STRIP001     rSortTxtReading = sSortTxtReading;
//STRIP001 }

//STRIP001 inline const ::com::sun::star::lang::Locale& SwTOXSortTabBase::GetLocale() const
//STRIP001 {
//STRIP001     return aLocale;
//STRIP001 }

/*--------------------------------------------------------------------
     Beschreibung: fuer Sortierung nach Text
 --------------------------------------------------------------------*/

//STRIP001 struct SwTOXIndex : public SwTOXSortTabBase
//STRIP001 {
//STRIP001  SwTOXIndex( const SwTxtNode&, const SwTxtTOXMark*, USHORT nOptions, BYTE nKeyLevel,
//STRIP001                 const SwTOXInternational& rIntl,
//STRIP001                 const ::com::sun::star::lang::Locale& rLocale );
//STRIP001
//STRIP001
//STRIP001  virtual void    FillText( SwTxtNode& rNd, const SwIndex& rInsPos, USHORT nAuthField = 0 ) const;
//STRIP001  virtual USHORT  GetLevel() const;
//STRIP001  virtual BOOL    operator==( const SwTOXSortTabBase& );
//STRIP001  virtual BOOL    operator<( const SwTOXSortTabBase& );
//STRIP001
//STRIP001 private:
//STRIP001     virtual void _GetText( String&, String& );
//STRIP001
//STRIP001  BYTE    nKeyLevel;
//STRIP001 };

//STRIP001 struct SwTOXCustom : public SwTOXSortTabBase
//STRIP001 {
//STRIP001     SwTOXCustom( const String& rKey, USHORT nLevel,
//STRIP001                  const SwTOXInternational& rIntl,
//STRIP001                  const ::com::sun::star::lang::Locale& rLocale );
//STRIP001
//STRIP001  virtual USHORT GetLevel() const;
//STRIP001  virtual BOOL   operator==( const SwTOXSortTabBase& );
//STRIP001  virtual BOOL   operator<( const SwTOXSortTabBase& );
//STRIP001
//STRIP001 private:
//STRIP001     virtual void _GetText( String&, String& );
//STRIP001
//STRIP001  String  aKey;
//STRIP001  USHORT  nLev;
//STRIP001 };

/*--------------------------------------------------------------------
     Beschreibung: fuer Sortierung nach Position
 --------------------------------------------------------------------*/

//STRIP001 struct SwTOXContent : public SwTOXSortTabBase
//STRIP001 {
//STRIP001  SwTOXContent( const SwTxtNode&, const SwTxtTOXMark*,
//STRIP001              const SwTOXInternational& rIntl );
//STRIP001
//STRIP001  virtual void    FillText( SwTxtNode& rNd, const SwIndex& rInsPos, USHORT nAuthField = 0 ) const;
//STRIP001  virtual USHORT  GetLevel() const;
//STRIP001 private:
//STRIP001     virtual void _GetText( String&, String& );
//STRIP001
//STRIP001 };

//STRIP001 struct SwTOXPara : public SwTOXSortTabBase
//STRIP001 {
//STRIP001  SwTOXPara( const SwCntntNode&, SwTOXElement, USHORT nLevel = FORM_ALPHA_DELIMITTER );
//STRIP001
//STRIP001  void    SetStartIndex( xub_StrLen nSet)     { nStartIndex = nSet;}
//STRIP001  void    SetEndIndex( xub_StrLen nSet )      { nEndIndex = nSet;}
//STRIP001
//STRIP001  virtual void    FillText( SwTxtNode& rNd, const SwIndex& rInsPos, USHORT nAuthField = 0 ) const;
//STRIP001  virtual USHORT  GetLevel() const;
//STRIP001
//STRIP001  virtual String  GetURL() const;
//STRIP001 private:
//STRIP001     virtual void _GetText( String&, String& );
//STRIP001
//STRIP001  SwTOXElement eType;
//STRIP001  USHORT m_nLevel;
//STRIP001  xub_StrLen nStartIndex;
//STRIP001  xub_StrLen nEndIndex;
//STRIP001 };

//STRIP001 struct SwTOXTable : public SwTOXSortTabBase
//STRIP001 {
//STRIP001  SwTOXTable( const SwCntntNode& rNd );
//STRIP001  void    SetLevel(USHORT nSet){nLevel = nSet;}
//STRIP001
//STRIP001  virtual USHORT  GetLevel() const;
//STRIP001
//STRIP001  virtual String  GetURL() const;
//STRIP001 private:
//STRIP001     virtual void _GetText( String&, String& );
//STRIP001
//STRIP001  USHORT nLevel;
//STRIP001 };

//STRIP001 struct SwTOXAuthority : public SwTOXSortTabBase
//STRIP001 {
//STRIP001 private:
//STRIP001  SwFmtFld& m_rField;
//STRIP001  virtual void    FillText( SwTxtNode& rNd, const SwIndex& rInsPos, USHORT nAuthField = 0 ) const;
//STRIP001     virtual void _GetText( String&, String& );
//STRIP001
//STRIP001 public:
//STRIP001  SwTOXAuthority( const SwCntntNode& rNd, SwFmtFld& rField, const SwTOXInternational& rIntl );
//STRIP001  SwFmtFld& GetFldFmt() {return m_rField;}
//STRIP001
//STRIP001  virtual BOOL    operator==( const SwTOXSortTabBase& );
//STRIP001  virtual BOOL    operator<( const SwTOXSortTabBase& );
//STRIP001  virtual USHORT  GetLevel() const;
//STRIP001 };


} //namespace binfilter
#endif // _TXMSRT_HXX
