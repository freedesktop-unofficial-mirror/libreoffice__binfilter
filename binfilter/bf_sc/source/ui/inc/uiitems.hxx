/*************************************************************************
 *
 *  $RCSfile: uiitems.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:30:16 $
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

#ifndef SC_UIITEMS_HXX
#define SC_UIITEMS_HXX

#ifndef SC_CONDITIO_HXX
#include "conditio.hxx"
#endif
#ifndef SC_SORTPARAM_HXX
#include "sortparam.hxx"
#endif

#ifndef _SFXPOOLITEM_HXX //autogen
#include <svtools/poolitem.hxx>
#endif
namespace binfilter {

class ScEditEngineDefaulter;
class EditTextObject;
class ScViewData;
class ScDPSaveData;

// ---------------------------------------------------------------------------

//  Items

//STRIP001 class ScInputStatusItem : public SfxPoolItem
//STRIP001 {
//STRIP001  ScAddress           aCursorPos;
//STRIP001  ScAddress           aStartPos;
//STRIP001  ScAddress           aEndPos;
//STRIP001  String              aString;
//STRIP001  EditTextObject*     pEditData;
//STRIP001
//STRIP001 public:
//STRIP001                          TYPEINFO();
//STRIP001                          ScInputStatusItem( USHORT nWhich,
//STRIP001                                             USHORT nTab,
//STRIP001                                             USHORT nCol, USHORT nRow,
//STRIP001                                             USHORT nStartCol, USHORT nStartRow,
//STRIP001                                             USHORT nEndCol,   USHORT nSEndRow,
//STRIP001                                             const String& rString,
//STRIP001                                             const EditTextObject* pData );
//STRIP001                          ScInputStatusItem( USHORT nWhich,
//STRIP001                                             const ScAddress& rCurPos,
//STRIP001                                             const ScAddress& rStartPos,
//STRIP001                                             const ScAddress& rEndPos,
//STRIP001                                             const String& rString,
//STRIP001                                             const EditTextObject* pData );
//STRIP001                          ScInputStatusItem( const ScInputStatusItem& rItem );
//STRIP001                          ~ScInputStatusItem();
//STRIP001
//STRIP001  virtual String          GetValueText() const;
//STRIP001
//STRIP001  virtual int             operator==( const SfxPoolItem& ) const;
//STRIP001  virtual SfxPoolItem*    Clone( SfxItemPool *pPool = 0 ) const;
//STRIP001
//STRIP001  const ScAddress&        GetPos() const      { return aCursorPos; }
//STRIP001  const ScAddress&        GetStartPos() const { return aStartPos; }
//STRIP001  const ScAddress&        GetEndPos() const   { return aEndPos; }
//STRIP001  USHORT                  GetTab() const      { return aCursorPos.Tab(); }
//STRIP001  USHORT                  GetCol() const      { return aCursorPos.Col(); }
//STRIP001  USHORT                  GetRow() const      { return aCursorPos.Row(); }
//STRIP001  USHORT                  GetStartCol() const { return aStartPos.Col(); }
//STRIP001  USHORT                  GetStartRow() const { return aStartPos.Row(); }
//STRIP001  USHORT                  GetEndCol() const   { return aEndPos.Col(); }
//STRIP001  USHORT                  GetEndRow() const   { return aEndPos.Row(); }
//STRIP001
//STRIP001  const String&           GetString() const   { return aString; }
//STRIP001  const EditTextObject*   GetEditData() const { return pEditData; }
//STRIP001 };


#define SC_TAB_INSERTED     1
#define SC_TAB_DELETED      2
#define SC_TAB_MOVED        3
#define SC_TAB_COPIED       4
#define SC_TAB_HIDDEN       5

class ScTablesHint : public SfxHint
{
    USHORT nId;
    USHORT nTab1;
    USHORT nTab2;

public:
                    TYPEINFO();
                    ScTablesHint(USHORT nNewId, USHORT nTable1, USHORT nTable2=0);
                    ~ScTablesHint();

    USHORT          GetId() const           { return nId; }
    USHORT          GetTab1() const         { return nTab1; }
    USHORT          GetTab2() const         { return nTab2; }
};

class ScEditViewHint : public SfxHint
{
    ScEditEngineDefaulter*  pEditEngine;
    ScAddress                   aCursorPos;

public:
                    TYPEINFO();
                    ScEditViewHint();
                    ScEditViewHint( ScEditEngineDefaulter* pEngine, const ScAddress& rCurPos );
                    ~ScEditViewHint();

    USHORT          GetCol() const      { return aCursorPos.Col(); }
    USHORT          GetRow() const      { return aCursorPos.Row(); }
    USHORT          GetTab() const      { return aCursorPos.Tab(); }
    ScEditEngineDefaulter*  GetEngine() const   { return pEditEngine; }
};

class ScIndexHint : public SfxHint
{
    USHORT nId;
    USHORT nIndex;

public:
                    TYPEINFO();
                    ScIndexHint(USHORT nNewId, USHORT nIdx);
                    ~ScIndexHint();

    USHORT          GetId() const           { return nId; }
    USHORT          GetIndex() const        { return nIndex; }
};

//----------------------------------------------------------------------------
// Parameter-Item fuer den Sortierdialog:

class ScSortItem : public SfxPoolItem
{
public:
                            TYPEINFO();
                            ScSortItem( USHORT              nWhich,
                                        ScViewData*         ptrViewData,
                                        const ScSortParam*  pSortData );
                            ScSortItem( USHORT              nWhich,
                                        const ScSortParam*  pSortData );
                            ScSortItem( const ScSortItem& rItem );
                            ~ScSortItem();

//STRIP001  virtual String          GetValueText() const;
    virtual int             operator==( const SfxPoolItem& ) const{DBG_ASSERT(0, "STRIP");return 0;}; //STRIP001 virtual int             operator==( const SfxPoolItem& ) const;
    virtual SfxPoolItem*    Clone( SfxItemPool *pPool = 0 ) const{DBG_ASSERT(0, "STRIP");return NULL;}; //STRIP001 virtual SfxPoolItem*    Clone( SfxItemPool *pPool = 0 ) const;

    ScViewData*         GetViewData () const { return pViewData; }
//STRIP001  const ScSortParam&  GetSortData () const { return theSortData; }

private:
    ScViewData*     pViewData;
    ScSortParam     theSortData;
};

//----------------------------------------------------------------------------
// Parameter-Item fuer den Filterdialog:

class ScQueryItem : public SfxPoolItem
{
public:
                            TYPEINFO();
                            ScQueryItem( USHORT                 nWhich,
                                         ScViewData*            ptrViewData,
                                         const ScQueryParam*    pQueryData );
                            ScQueryItem( USHORT                 nWhich,
                                         const ScQueryParam*    pQueryData );
                            ScQueryItem( const ScQueryItem& rItem );
                            ~ScQueryItem();

//STRIP001  virtual String          GetValueText() const;
    virtual int             operator==( const SfxPoolItem& ) const{DBG_ASSERT(0, "STRIP");return 0;}; //STRIP001 virtual int             operator==( const SfxPoolItem& ) const;
    virtual SfxPoolItem*    Clone( SfxItemPool *pPool = 0 ) const{DBG_ASSERT(0, "STRIP"); return NULL;}; //STRIP001 virtual SfxPoolItem*    Clone( SfxItemPool *pPool = 0 ) const;

     ScViewData*            GetViewData () const { return pViewData; }
//STRIP001  const ScQueryParam& GetQueryData() const { return theQueryData; }

//STRIP001  BOOL        GetAdvancedQuerySource(ScRange& rSource) const;
//STRIP001  void        SetAdvancedQuerySource(const ScRange* pSource);

private:
    ScViewData*     pViewData;
    ScQueryParam    theQueryData;
    BOOL            bIsAdvanced;
    ScRange         aAdvSource;
};

//----------------------------------------------------------------------------
// Parameter-Item fuer den Zwischenergebnisdialog:

class ScSubTotalItem : public SfxPoolItem
{
public:
                TYPEINFO();
                ScSubTotalItem( USHORT                  nWhich,
                                ScViewData*             ptrViewData,
                                const ScSubTotalParam*  pSubTotalData );
                ScSubTotalItem( USHORT                  nWhich,
                                const ScSubTotalParam*  pSubTotalData );
                ScSubTotalItem( const ScSubTotalItem&   rItem );
                ~ScSubTotalItem();

//STRIP001  virtual String          GetValueText() const;
    virtual int             operator==( const SfxPoolItem& ) const{DBG_ASSERT(0, "STRIP"); return 0;}; //STRIP001 virtual int             operator==( const SfxPoolItem& ) const;
    virtual SfxPoolItem*    Clone( SfxItemPool *pPool = 0 ) const{DBG_ASSERT(0, "STRIP"); return NULL;}; //STRIP001 virtual SfxPoolItem*    Clone( SfxItemPool *pPool = 0 ) const;

    ScViewData*             GetViewData () const { return pViewData; }
    const ScSubTotalParam&  GetSubTotalData() const { return theSubTotalData; }

private:
    ScViewData*     pViewData;
    ScSubTotalParam theSubTotalData;
};

//----------------------------------------------------------------------------
// Parameter-Item fuer die Benutzerlisten-TabPage:

class ScUserListItem : public SfxPoolItem
{
public:
                TYPEINFO();
                ScUserListItem( USHORT nWhich );
                ScUserListItem( const ScUserListItem& rItem );
                ~ScUserListItem();

//STRIP001  virtual String          GetValueText() const;
    virtual int             operator==( const SfxPoolItem& ) const{DBG_ASSERT(0, "STRIP");return 0;}; //STRIP001 virtual int             operator==( const SfxPoolItem& ) const;
    virtual SfxPoolItem*    Clone( SfxItemPool *pPool = 0 ) const{DBG_ASSERT(0, "STRIP"); return NULL;}; //STRIP001 virtual SfxPoolItem*    Clone( SfxItemPool *pPool = 0 ) const;

//STRIP001  void        SetUserList ( const ScUserList& rUserList );
//STRIP001  ScUserList* GetUserList () const { return pUserList; }

private:
    ScUserList* pUserList;
};

//----------------------------------------------------------------------------
// Parameter-Item fuer die Konsolidieren-Dialog

class ScConsolidateItem : public SfxPoolItem
{
public:
                TYPEINFO();
                ScConsolidateItem( USHORT                    nWhich,
                                   const ScConsolidateParam* pParam );
                ScConsolidateItem( const ScConsolidateItem& rItem );
                ~ScConsolidateItem();

//STRIP001  virtual String          GetValueText() const;
    virtual int             operator==( const SfxPoolItem& ) const{DBG_ASSERT(0, "STRIP"); return 0;}; //STRIP001 virtual int             operator==( const SfxPoolItem& ) const;
    virtual SfxPoolItem*    Clone( SfxItemPool *pPool = 0 ) const{DBG_ASSERT(0, "STRIP"); return NULL;}; //STRIP001 virtual SfxPoolItem*    Clone( SfxItemPool *pPool = 0 ) const;

//STRIP001  const ScConsolidateParam& GetData() const { return theConsData; }

private:
    ScConsolidateParam  theConsData;
};

//----------------------------------------------------------------------------
// Parameter-Item fuer den Pivot-Dialog

class ScPivotItem : public SfxPoolItem
{
public:
                TYPEINFO();
                ScPivotItem( USHORT nWhich, const ScDPSaveData* pData,
                             const ScRange* pRange, BOOL bNew );
                ScPivotItem( const ScPivotItem& rItem );
                ~ScPivotItem();

//STRIP001  virtual String          GetValueText() const;
    virtual int             operator==( const SfxPoolItem& ) const{DBG_ASSERT(0, "STRIP");return 0;}; //STRIP001 virtual int             operator==( const SfxPoolItem& ) const;
    virtual SfxPoolItem*    Clone( SfxItemPool *pPool = 0 ) const{DBG_ASSERT(0, "STRIP");return NULL;}; //STRIP001 virtual SfxPoolItem*    Clone( SfxItemPool *pPool = 0 ) const;

//STRIP001  const ScDPSaveData& GetData() const         { return *pSaveData; }
//STRIP001  const ScRange&      GetDestRange() const    { return aDestRange; }
//STRIP001  BOOL                IsNewSheet() const      { return bNewSheet; }

private:
    ScDPSaveData*   pSaveData;
    ScRange         aDestRange;
    BOOL            bNewSheet;
};

//----------------------------------------------------------------------------
// Parameter-Item fuer den Solver-Dialog

class ScSolveItem : public SfxPoolItem
{
public:
                TYPEINFO();
                ScSolveItem( USHORT              nWhich,
                             const ScSolveParam* pParam );
                ScSolveItem( const ScSolveItem& rItem );
                ~ScSolveItem();

//STRIP001  virtual String          GetValueText() const;
    virtual int             operator==( const SfxPoolItem& ) const{DBG_ASSERT(0, "STRIP");return 0;}; //STRIP001 virtual int             operator==( const SfxPoolItem& ) const;
    virtual SfxPoolItem*    Clone( SfxItemPool *pPool = 0 ) const{DBG_ASSERT(0, "STRIP"); return NULL;}; //STRIP001 virtual SfxPoolItem*    Clone( SfxItemPool *pPool = 0 ) const;

//STRIP001  const ScSolveParam& GetData() const { return theSolveData; }

private:
    ScSolveParam    theSolveData;
};

//----------------------------------------------------------------------------
// Parameter-Item fuer den Mehrfachoperationen-Dialog

//STRIP001 class ScTabOpItem : public SfxPoolItem
//STRIP001 {
//STRIP001 public:
//STRIP001              TYPEINFO();
//STRIP001              ScTabOpItem( USHORT              nWhich,
//STRIP001                           const ScTabOpParam* pParam );
//STRIP001              ScTabOpItem( const ScTabOpItem& rItem );
//STRIP001              ~ScTabOpItem();
//STRIP001
//STRIP001  virtual String          GetValueText() const;
//STRIP001  virtual int             operator==( const SfxPoolItem& ) const;
//STRIP001  virtual SfxPoolItem*    Clone( SfxItemPool *pPool = 0 ) const;
//STRIP001
//STRIP001  const ScTabOpParam& GetData() const { return theTabOpData; }
//STRIP001
//STRIP001 private:
//STRIP001  ScTabOpParam    theTabOpData;
//STRIP001 };

//----------------------------------------------------------------------------
// Parameter-Item fuer den Dialog bedingte Formatierung

class ScCondFrmtItem : public SfxPoolItem
{
public:
                TYPEINFO();
                ScCondFrmtItem( USHORT nWhich,
//!                             const ScConditionalFormat* pCondFrmt );
                                const ScConditionalFormat& rCondFrmt );
                ScCondFrmtItem( const ScCondFrmtItem& rItem );
                ~ScCondFrmtItem();

    virtual String          GetValueText() const;
    virtual int             operator==( const SfxPoolItem& ) const;
    virtual SfxPoolItem*    Clone( SfxItemPool *pPool = 0 ) const;

    const ScConditionalFormat&  GetData() const { return theCondFrmtData; }

private:
    ScConditionalFormat theCondFrmtData;
};



} //namespace binfilter
#endif

