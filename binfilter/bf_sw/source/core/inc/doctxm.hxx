/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: doctxm.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-08 09:26:43 $
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
#ifndef _DOCTXM_HXX
#define _DOCTXM_HXX


#ifndef _SVARRAY_HXX //autogen
#include <svtools/svarray.hxx>
#endif
#ifndef _SV_GEN_HXX
#include <tools/gen.hxx>
#endif

#ifndef _TOX_HXX
#include <tox.hxx>
#endif
#ifndef _SECTION_HXX
#include <section.hxx>
#endif
class  SvUShorts;
class  SvStringsDtor;
class  SvPtrarr;
namespace binfilter {

class  SwTOXInternational;

class  SwTxtNode;
class  SwTxtFmtColl;
struct SwPosition;
struct SwTOXSortTabBase;

typedef SwTOXSortTabBase* SwTOXSortTabBasePtr;

SV_DECL_PTRARR(SwTOXSortTabBases, SwTOXSortTabBasePtr, 0, 5 )//STRIP008 ;

/*--------------------------------------------------------------------
     Beschreibung: Ring der speziellen Verzeichnisse
 --------------------------------------------------------------------*/

class SwTOXBaseSection : public SwTOXBase, public SwSection
{
    SwTOXSortTabBases aSortArr;

//STRIP001  void    UpdateMarks( const SwTOXInternational& rIntl,
//STRIP001                          const SwTxtNode* pOwnChapterNode );
//STRIP001  void    UpdateOutline( const SwTxtNode* pOwnChapterNode );
//STRIP001  void    UpdateTemplate( const SwTxtNode* pOwnChapterNode );
//STRIP001  void    UpdateCntnt( SwTOXElement eType,
//STRIP001                          const SwTxtNode* pOwnChapterNode );
//STRIP001  void    UpdateTable( const SwTxtNode* pOwnChapterNode );
//STRIP001  void    UpdateSequence( const SwTxtNode* pOwnChapterNode );
//STRIP001  void    UpdateAuthorities( const SwTxtNode* pOwnChapterNode,
//STRIP001                                      const SwTOXInternational& rIntl );
    void    UpdateAll();

    // Sortiert einfuegen ins Array fuer die Generierung
//STRIP001  void    InsertSorted(SwTOXSortTabBase* pBase);

    // Alpha-Trennzeichen bei der Generierung einfuegen
//STRIP001  void    InsertAlphaDelimitter( const SwTOXInternational& rIntl );

    // Textrumpf generieren
    // OD 18.03.2003 #106329# - add parameter <_TOXSectNdIdx> and <_pDefaultPageDesc>
//STRIP001     void GenerateText( USHORT nArrayIdx,
//STRIP001                        USHORT nCount,
//STRIP001                        SvStringsDtor&,
//STRIP001                        const sal_uInt32   _nTOXSectNdIdx,
//STRIP001                        const SwPageDesc*  _pDefaultPageDesc );

    // Seitennummerplatzhalter gegen aktuelle Nummern austauschen
//STRIP001  void    _UpdatePageNum( SwTxtNode* pNd,
//STRIP001                          const SvUShorts& rNums,
//STRIP001                          const SvPtrarr &rDescs,
//STRIP001                          const SvUShorts* pMainEntryNums,
//STRIP001                          const SwTOXInternational& rIntl );

    // Bereich fuer Stichwort einfuegen suchen
//STRIP001     Range GetKeyRange( const String& rStr, const String& rStrReading,
//STRIP001                        const SwTOXSortTabBase& rNew, USHORT nLevel,
//STRIP001                        const Range& rRange );

    // returne die TextCollection ueber den Namen / aus Format-Pool
//STRIP001  SwTxtFmtColl* GetTxtFmtColl( USHORT nLevel );

public:
    SwTOXBaseSection( const SwTOXBase& rBase );
    virtual ~SwTOXBaseSection();

    // OD 19.03.2003 #106329# - add parameter <_bNewTOX> in order to distinguish
    // between the creation of a new table-of-content or an update of
    // a table-of-content. Default value: false
    void Update( const SfxItemSet* pAttr = 0,
                 const bool        _bNewTOX = false ); // Formatieren
    void UpdatePageNum();               // Seitennummern einfuegen
    TYPEINFO();                         // fuers rtti

//STRIP001  BOOL SetPosAtStartEnd( SwPosition& rPos, BOOL bAtStart = TRUE ) const;
};
/* -----------------02.09.99 07:52-------------------

 --------------------------------------------------*/
struct SwDefTOXBase_Impl
{
    SwTOXBase* pContBase;
    SwTOXBase* pIdxBase;
    SwTOXBase* pUserBase;
    SwTOXBase* pTblBase;
    SwTOXBase* pObjBase;
    SwTOXBase* pIllBase;
    SwTOXBase* pAuthBase;

    SwDefTOXBase_Impl() :
    pContBase(0),
    pIdxBase(0),
    pUserBase(0),
    pTblBase(0),
    pObjBase(0),
    pIllBase(0),
    pAuthBase(0)
    {}
    ~SwDefTOXBase_Impl()
    {
        delete pContBase;
        delete pIdxBase;
        delete pUserBase;
        delete pTblBase;
        delete pObjBase;
        delete pIllBase;
        delete pAuthBase;
    }

};

} //namespace binfilter
#endif  // _DOCTXM_HXX
