/*************************************************************************
 *
 *  $RCSfile: undodat.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:30:17 $
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

#ifndef SC_UNDODAT_HXX
#define SC_UNDODAT_HXX

#ifndef SC_UNDOBASE_HXX
#include "undobase.hxx"
#endif

#ifndef SC_RANGEUTL_HXX
#include "rangeutl.hxx"     // ScArea
#endif

#ifndef SC_RANGELST_HXX
#include "rangelst.hxx"     // ScRangeListRef
#endif

#ifndef SC_MARKDATA_HXX
#include "markdata.hxx"
#endif

#ifndef SC_SORTPARAM_HXX
#include "sortparam.hxx"
#endif
namespace binfilter {


class ScDocShell;
class ScDocument;
class ScOutlineTable;
class ScRangeName;
class ScDBData;
class ScDBCollection;
class ScPivot;
class ScDPObject;

//----------------------------------------------------------------------------

//STRIP001 class ScUndoDoOutline: public ScSimpleUndo
//STRIP001 {
//STRIP001 public:
//STRIP001                  TYPEINFO();
//STRIP001                  ScUndoDoOutline( ScDocShell* pNewDocShell,
//STRIP001                          USHORT nNewStart, USHORT nNewEnd, USHORT nNewTab,
//STRIP001                          ScDocument* pNewUndoDoc, BOOL bNewColumns,
//STRIP001                          USHORT nNewLevel, USHORT nNewEntry, BOOL bNewShow );
//STRIP001  virtual         ~ScUndoDoOutline();
//STRIP001
//STRIP001  virtual void    Undo();
//STRIP001  virtual void    Redo();
//STRIP001  virtual void    Repeat(SfxRepeatTarget& rTarget);
//STRIP001  virtual BOOL    CanRepeat(SfxRepeatTarget& rTarget) const;
//STRIP001
//STRIP001  virtual String  GetComment() const;
//STRIP001
//STRIP001 private:
//STRIP001  USHORT          nStart;
//STRIP001  USHORT          nEnd;
//STRIP001  USHORT          nTab;
//STRIP001  ScDocument*     pUndoDoc;
//STRIP001  BOOL            bColumns;
//STRIP001  USHORT          nLevel;
//STRIP001  USHORT          nEntry;
//STRIP001  BOOL            bShow;
//STRIP001 };


//STRIP001 class ScUndoMakeOutline: public ScSimpleUndo
//STRIP001 {
//STRIP001 public:
//STRIP001                  TYPEINFO();
//STRIP001                  ScUndoMakeOutline( ScDocShell* pNewDocShell,
//STRIP001                          USHORT nStartX, USHORT nStartY, USHORT nStartZ,
//STRIP001                          USHORT nEndX, USHORT nEndY, USHORT nEndZ,
//STRIP001                          ScOutlineTable* pNewUndoTab,
//STRIP001                          BOOL bNewColumns, BOOL bNewMake );
//STRIP001  virtual         ~ScUndoMakeOutline();
//STRIP001
//STRIP001  virtual void    Undo();
//STRIP001  virtual void    Redo();
//STRIP001  virtual void    Repeat(SfxRepeatTarget& rTarget);
//STRIP001  virtual BOOL    CanRepeat(SfxRepeatTarget& rTarget) const;
//STRIP001
//STRIP001  virtual String  GetComment() const;
//STRIP001
//STRIP001 private:
//STRIP001  ScTripel        aBlockStart;
//STRIP001  ScTripel        aBlockEnd;
//STRIP001  ScOutlineTable* pUndoTable;
//STRIP001  BOOL            bColumns;
//STRIP001  BOOL            bMake;
//STRIP001 };


//STRIP001 class ScUndoOutlineLevel: public ScSimpleUndo
//STRIP001 {
//STRIP001 public:
//STRIP001                  TYPEINFO();
//STRIP001                  ScUndoOutlineLevel( ScDocShell* pNewDocShell,
//STRIP001                          USHORT nNewStart, USHORT nNewEnd, USHORT nNewTab,
//STRIP001                          ScDocument* pNewUndoDoc, ScOutlineTable* pNewUndoTab,
//STRIP001                          BOOL bNewColumns, USHORT nNewLevel );
//STRIP001  virtual         ~ScUndoOutlineLevel();
//STRIP001
//STRIP001  virtual void    Undo();
//STRIP001  virtual void    Redo();
//STRIP001  virtual void    Repeat(SfxRepeatTarget& rTarget);
//STRIP001  virtual BOOL    CanRepeat(SfxRepeatTarget& rTarget) const;
//STRIP001
//STRIP001  virtual String  GetComment() const;
//STRIP001
//STRIP001 private:
//STRIP001  USHORT          nStart;
//STRIP001  USHORT          nEnd;
//STRIP001  USHORT          nTab;
//STRIP001  ScDocument*     pUndoDoc;
//STRIP001  ScOutlineTable* pUndoTable;
//STRIP001  BOOL            bColumns;
//STRIP001  USHORT          nLevel;
//STRIP001 };


//STRIP001 class ScUndoOutlineBlock: public ScSimpleUndo
//STRIP001 {
//STRIP001 public:
//STRIP001                  TYPEINFO();
//STRIP001                  ScUndoOutlineBlock( ScDocShell* pNewDocShell,
//STRIP001                          USHORT nStartX, USHORT nStartY, USHORT nStartZ,
//STRIP001                          USHORT nEndX, USHORT nEndY, USHORT nEndZ,
//STRIP001                          ScDocument* pNewUndoDoc, ScOutlineTable* pNewUndoTab,
//STRIP001                          BOOL bNewShow );
//STRIP001  virtual         ~ScUndoOutlineBlock();
//STRIP001
//STRIP001  virtual void    Undo();
//STRIP001  virtual void    Redo();
//STRIP001  virtual void    Repeat(SfxRepeatTarget& rTarget);
//STRIP001  virtual BOOL    CanRepeat(SfxRepeatTarget& rTarget) const;
//STRIP001
//STRIP001  virtual String  GetComment() const;
//STRIP001
//STRIP001 private:
//STRIP001  ScTripel        aBlockStart;
//STRIP001  ScTripel        aBlockEnd;
//STRIP001  ScDocument*     pUndoDoc;
//STRIP001  ScOutlineTable* pUndoTable;
//STRIP001  BOOL            bShow;
//STRIP001 };


//STRIP001 class ScUndoRemoveAllOutlines: public ScSimpleUndo
//STRIP001 {
//STRIP001 public:
//STRIP001                  TYPEINFO();
//STRIP001                  ScUndoRemoveAllOutlines( ScDocShell* pNewDocShell,
//STRIP001                          USHORT nStartX, USHORT nStartY, USHORT nStartZ,
//STRIP001                          USHORT nEndX, USHORT nEndY, USHORT nEndZ,
//STRIP001                          ScDocument* pNewUndoDoc, ScOutlineTable* pNewUndoTab );
//STRIP001  virtual         ~ScUndoRemoveAllOutlines();
//STRIP001
//STRIP001  virtual void    Undo();
//STRIP001  virtual void    Redo();
//STRIP001  virtual void    Repeat(SfxRepeatTarget& rTarget);
//STRIP001  virtual BOOL    CanRepeat(SfxRepeatTarget& rTarget) const;
//STRIP001
//STRIP001  virtual String  GetComment() const;
//STRIP001
//STRIP001 private:
//STRIP001  ScTripel        aBlockStart;
//STRIP001  ScTripel        aBlockEnd;
//STRIP001  ScDocument*     pUndoDoc;
//STRIP001  ScOutlineTable* pUndoTable;
//STRIP001 };


//STRIP001 class ScUndoAutoOutline: public ScSimpleUndo
//STRIP001 {
//STRIP001 public:
//STRIP001                  TYPEINFO();
//STRIP001                  ScUndoAutoOutline( ScDocShell* pNewDocShell,
//STRIP001                          USHORT nStartX, USHORT nStartY, USHORT nStartZ,
//STRIP001                          USHORT nEndX, USHORT nEndY, USHORT nEndZ,
//STRIP001                          ScDocument* pNewUndoDoc, ScOutlineTable* pNewUndoTab );
//STRIP001  virtual         ~ScUndoAutoOutline();
//STRIP001
//STRIP001  virtual void    Undo();
//STRIP001  virtual void    Redo();
//STRIP001  virtual void    Repeat(SfxRepeatTarget& rTarget);
//STRIP001  virtual BOOL    CanRepeat(SfxRepeatTarget& rTarget) const;
//STRIP001
//STRIP001  virtual String  GetComment() const;
//STRIP001
//STRIP001 private:
//STRIP001  ScTripel        aBlockStart;
//STRIP001  ScTripel        aBlockEnd;
//STRIP001  ScDocument*     pUndoDoc;
//STRIP001  ScOutlineTable* pUndoTable;
//STRIP001 };


//STRIP001 class ScUndoSubTotals: public ScSimpleUndo
//STRIP001 {
//STRIP001 public:
//STRIP001                  TYPEINFO();
//STRIP001                  ScUndoSubTotals( ScDocShell* pNewDocShell, USHORT nNewTab,
//STRIP001                          const ScSubTotalParam& rNewParam, USHORT nNewEndY,
//STRIP001                          ScDocument* pNewUndoDoc, ScOutlineTable* pNewUndoTab,
//STRIP001 //                           ScDBData* pNewData,
//STRIP001                          ScRangeName* pNewUndoRange, ScDBCollection* pNewUndoDB );
//STRIP001  virtual         ~ScUndoSubTotals();
//STRIP001
//STRIP001  virtual void    Undo();
//STRIP001  virtual void    Redo();
//STRIP001  virtual void    Repeat(SfxRepeatTarget& rTarget);
//STRIP001  virtual BOOL    CanRepeat(SfxRepeatTarget& rTarget) const;
//STRIP001
//STRIP001  virtual String  GetComment() const;
//STRIP001
//STRIP001 private:
//STRIP001  USHORT          nTab;
//STRIP001  ScSubTotalParam aParam;                         // Original uebergebener Parameter
//STRIP001  USHORT          nNewEndRow;                     // Ergebnis-Groesse
//STRIP001  ScDocument*     pUndoDoc;
//STRIP001  ScOutlineTable* pUndoTable;
//STRIP001 //   ScDBData*       pUndoDBData;
//STRIP001  ScRangeName*    pUndoRange;
//STRIP001  ScDBCollection* pUndoDB;
//STRIP001 };


//STRIP001 class ScUndoSort: public ScSimpleUndo
//STRIP001 {
//STRIP001 public:
//STRIP001                  TYPEINFO();
//STRIP001                  ScUndoSort( ScDocShell* pNewDocShell, USHORT nNewTab,
//STRIP001                          const ScSortParam& rParam,
//STRIP001                          BOOL bQuery, ScDocument* pNewUndoDoc,
//STRIP001                          ScDBCollection* pNewUndoDB, const ScRange* pDest = NULL );
//STRIP001  virtual         ~ScUndoSort();
//STRIP001
//STRIP001  virtual void    Undo();
//STRIP001  virtual void    Redo();
//STRIP001  virtual void    Repeat(SfxRepeatTarget& rTarget);
//STRIP001  virtual BOOL    CanRepeat(SfxRepeatTarget& rTarget) const;
//STRIP001
//STRIP001  virtual String  GetComment() const;
//STRIP001
//STRIP001 private:
//STRIP001  USHORT          nTab;
//STRIP001  ScSortParam     aSortParam;
//STRIP001  BOOL            bRepeatQuery;
//STRIP001  ScDocument*     pUndoDoc;
//STRIP001  ScDBCollection* pUndoDB;                // wegen Quell- und Zielbereich
//STRIP001  BOOL            bDestArea;
//STRIP001  ScRange         aDestRange;
//STRIP001 };


//STRIP001 class ScUndoQuery: public ScSimpleUndo
//STRIP001 {
//STRIP001 public:
//STRIP001                  TYPEINFO();
//STRIP001                  ScUndoQuery( ScDocShell* pNewDocShell, USHORT nNewTab,
//STRIP001                          const ScQueryParam& rParam, ScDocument* pNewUndoDoc,
//STRIP001                          ScDBCollection* pNewUndoDB, const ScRange* pOld,
//STRIP001                          BOOL bSize, const ScRange* pAdvSrc );
//STRIP001  virtual         ~ScUndoQuery();
//STRIP001
//STRIP001  virtual void    Undo();
//STRIP001  virtual void    Redo();
//STRIP001  virtual void    Repeat(SfxRepeatTarget& rTarget);
//STRIP001  virtual BOOL    CanRepeat(SfxRepeatTarget& rTarget) const;
//STRIP001
//STRIP001  virtual String  GetComment() const;
//STRIP001
//STRIP001 private:
//STRIP001  USHORT          nTab;
//STRIP001  ScQueryParam    aQueryParam;
//STRIP001  ScDocument*     pUndoDoc;
//STRIP001  ScDBCollection* pUndoDB;                // wegen Quell- und Zielbereich
//STRIP001  ScRange         aOldDest;
//STRIP001  ScRange         aAdvSource;
//STRIP001  BOOL            bIsAdvanced;
//STRIP001  BOOL            bDestArea;
//STRIP001  BOOL            bDoSize;
//STRIP001 };


class ScUndoDBData: public ScSimpleUndo
{
public:
//STRIP001                  TYPEINFO();
                    ScUndoDBData( ScDocShell* pNewDocShell,
                            ScDBCollection* pNewUndoColl, ScDBCollection* pNewRedoColl );
    virtual         ~ScUndoDBData();

//STRIP001  virtual void    Undo();
//STRIP001  virtual void    Redo();
//STRIP001  virtual void    Repeat(SfxRepeatTarget& rTarget);
    virtual BOOL    CanRepeat(SfxRepeatTarget& rTarget) const;

    virtual String  GetComment() const;

private:
    ScDBCollection* pUndoColl;
    ScDBCollection* pRedoColl;
};


//STRIP001 class ScUndoImportData: public ScSimpleUndo
//STRIP001 {
//STRIP001 public:
//STRIP001                  TYPEINFO();
//STRIP001                  ScUndoImportData( ScDocShell* pNewDocShell, USHORT nNewTab,
//STRIP001                          const ScImportParam& rParam, USHORT nNewEndX, USHORT nNewEndY,
//STRIP001                          USHORT nNewFormula,
//STRIP001                          ScDocument* pNewUndoDoc, ScDocument* pNewRedoDoc,
//STRIP001                          ScDBData* pNewUndoData, ScDBData* pNewRedoData );
//STRIP001  virtual         ~ScUndoImportData();
//STRIP001
//STRIP001  virtual void    Undo();
//STRIP001  virtual void    Redo();
//STRIP001  virtual void    Repeat(SfxRepeatTarget& rTarget);
//STRIP001  virtual BOOL    CanRepeat(SfxRepeatTarget& rTarget) const;
//STRIP001
//STRIP001  virtual String  GetComment() const;
//STRIP001
//STRIP001 private:
//STRIP001  USHORT          nTab;
//STRIP001  ScImportParam   aImportParam;
//STRIP001  USHORT          nEndCol;
//STRIP001  USHORT          nEndRow;
//STRIP001  ScDocument*     pUndoDoc;
//STRIP001  ScDocument*     pRedoDoc;
//STRIP001  ScDBData*       pUndoDBData;
//STRIP001  ScDBData*       pRedoDBData;
//STRIP001  USHORT          nFormulaCols;
//STRIP001  BOOL            bRedoFilled;
//STRIP001 };


//STRIP001 class ScUndoRepeatDB: public ScSimpleUndo
//STRIP001 {
//STRIP001 public:
//STRIP001                  TYPEINFO();
//STRIP001                  ScUndoRepeatDB( ScDocShell* pNewDocShell, USHORT nNewTab,
//STRIP001                          USHORT nStartX, USHORT nStartY, USHORT nEndX, USHORT nEndY,
//STRIP001                          USHORT nResultEndRow, USHORT nCurX, USHORT nCurY,
//STRIP001                          ScDocument* pNewUndoDoc, ScOutlineTable* pNewUndoTab,
//STRIP001                          ScRangeName* pNewUndoRange, ScDBCollection* pNewUndoDB,
//STRIP001                          const ScRange* pOldQ, const ScRange* pNewQ );
//STRIP001  virtual         ~ScUndoRepeatDB();
//STRIP001
//STRIP001  virtual void    Undo();
//STRIP001  virtual void    Redo();
//STRIP001  virtual void    Repeat(SfxRepeatTarget& rTarget);
//STRIP001  virtual BOOL    CanRepeat(SfxRepeatTarget& rTarget) const;
//STRIP001
//STRIP001  virtual String  GetComment() const;
//STRIP001
//STRIP001 private:
//STRIP001  ScTripel        aBlockStart;
//STRIP001  ScTripel        aBlockEnd;
//STRIP001  USHORT          nNewEndRow;
//STRIP001  ScTripel        aCursorPos;
//STRIP001  ScDocument*     pUndoDoc;
//STRIP001  ScOutlineTable* pUndoTable;
//STRIP001  ScRangeName*    pUndoRange;
//STRIP001  ScDBCollection* pUndoDB;
//STRIP001  ScRange         aOldQuery;
//STRIP001  ScRange         aNewQuery;
//STRIP001  BOOL            bQuerySize;
//STRIP001 };


//STRIP001 class ScUndoPivot: public ScSimpleUndo
//STRIP001 {
//STRIP001 public:
//STRIP001                  TYPEINFO();
//STRIP001                  ScUndoPivot( ScDocShell* pNewDocShell,
//STRIP001                          const ScArea& rOld, const ScArea& rNew,
//STRIP001                          ScDocument* pOldDoc, ScDocument* pNewDoc,
//STRIP001                          const ScPivot* pOldPivot, const ScPivot* pNewPivot );
//STRIP001  virtual         ~ScUndoPivot();
//STRIP001
//STRIP001  virtual void    Undo();
//STRIP001  virtual void    Redo();
//STRIP001  virtual void    Repeat(SfxRepeatTarget& rTarget);
//STRIP001  virtual BOOL    CanRepeat(SfxRepeatTarget& rTarget) const;
//STRIP001
//STRIP001  virtual String  GetComment() const;
//STRIP001
//STRIP001 private:
//STRIP001  ScArea          aOldArea;
//STRIP001  ScArea          aNewArea;
//STRIP001  ScDocument*     pOldUndoDoc;
//STRIP001  ScDocument*     pNewUndoDoc;
//STRIP001  ScPivotParam    aOldParam;              // fuer Redo
//STRIP001  ScQueryParam    aOldQuery;
//STRIP001  ScArea          aOldSrc;
//STRIP001  ScPivotParam    aNewParam;              // fuer Undo in Collection
//STRIP001  ScQueryParam    aNewQuery;
//STRIP001  ScArea          aNewSrc;
//STRIP001  String          aOldName;
//STRIP001  String          aOldTag;
//STRIP001  String          aNewName;
//STRIP001  String          aNewTag;
//STRIP001 };


//STRIP001 class ScUndoDataPilot: public ScSimpleUndo
//STRIP001 {
//STRIP001 public:
//STRIP001                  TYPEINFO();
//STRIP001                  ScUndoDataPilot( ScDocShell* pNewDocShell,
//STRIP001                          ScDocument* pOldDoc, ScDocument* pNewDoc,
//STRIP001                          const ScDPObject* pOldObj, const ScDPObject* pNewObj );
//STRIP001  virtual         ~ScUndoDataPilot();
//STRIP001
//STRIP001  virtual void    Undo();
//STRIP001  virtual void    Redo();
//STRIP001  virtual void    Repeat(SfxRepeatTarget& rTarget);
//STRIP001  virtual BOOL    CanRepeat(SfxRepeatTarget& rTarget) const;
//STRIP001
//STRIP001  virtual String  GetComment() const;
//STRIP001
//STRIP001 private:
//STRIP001  ScDocument*     pOldUndoDoc;
//STRIP001  ScDocument*     pNewUndoDoc;
//STRIP001  ScDPObject*     pOldDPObject;
//STRIP001  ScDPObject*     pNewDPObject;
//STRIP001 };


//STRIP001 class ScUndoConsolidate: public ScSimpleUndo
//STRIP001 {
//STRIP001 public:
//STRIP001                      TYPEINFO();
//STRIP001                      ScUndoConsolidate( ScDocShell* pNewDocShell,
//STRIP001                              const ScArea& rArea, const ScConsolidateParam& rPar,
//STRIP001                              ScDocument* pNewUndoDoc, BOOL bReference,
//STRIP001                              USHORT nInsCount, ScOutlineTable* pTab,
//STRIP001                              ScDBData* pData );
//STRIP001  virtual             ~ScUndoConsolidate();
//STRIP001
//STRIP001  virtual void        Undo();
//STRIP001  virtual void        Redo();
//STRIP001  virtual void        Repeat(SfxRepeatTarget& rTarget);
//STRIP001  virtual BOOL        CanRepeat(SfxRepeatTarget& rTarget) const;
//STRIP001
//STRIP001  virtual String      GetComment() const;
//STRIP001
//STRIP001 private:
//STRIP001  ScArea              aDestArea;
//STRIP001  ScDocument*         pUndoDoc;
//STRIP001  ScConsolidateParam  aParam;
//STRIP001  BOOL                bInsRef;
//STRIP001  USHORT              nInsertCount;
//STRIP001  ScOutlineTable*     pUndoTab;
//STRIP001  ScDBData*           pUndoData;
//STRIP001 };


class ScUndoChartData: public ScSimpleUndo
{
public:
//STRIP001                      TYPEINFO();
                        ScUndoChartData( ScDocShell* pNewDocShell,
                                const String& rName, const ScRange& rNew,
                                BOOL bColHdr, BOOL bRowHdr, BOOL bAdd );
                        ScUndoChartData( ScDocShell* pNewDocShell,
                                const String& rName, const ScRangeListRef& rNew,
                                BOOL bColHdr, BOOL bRowHdr, BOOL bAdd );
    virtual             ~ScUndoChartData();

//STRIP001  virtual void        Undo();
//STRIP001  virtual void        Redo();
//STRIP001  virtual void        Repeat(SfxRepeatTarget& rTarget);
//STRIP001  virtual BOOL        CanRepeat(SfxRepeatTarget& rTarget) const;

//STRIP001  virtual String      GetComment() const;

private:
    String              aChartName;
    ScRangeListRef      aOldRangeListRef;
    BOOL                bOldColHeaders;
    BOOL                bOldRowHeaders;
//  ScRange             aNewRange;
    ScRangeListRef      aNewRangeListRef;
    BOOL                bNewColHeaders;
    BOOL                bNewRowHeaders;
    BOOL                bAddRange;

//STRIP001  void                Init();
};




} //namespace binfilter
#endif

