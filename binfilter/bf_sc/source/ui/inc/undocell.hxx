/*************************************************************************
 *
 *  $RCSfile: undocell.hxx,v $
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

#ifndef SC_UNDOCELL_HXX
#define SC_UNDOCELL_HXX

#ifndef SC_UNDOBASE_HXX
#include "undobase.hxx"
#endif
namespace binfilter {

class ScDocShell;
class ScBaseCell;
class ScPatternAttr;
class EditTextObject;
class SdrUndoAction;
class ScDetOpList;
class ScDetOpData;
class ScRangeName;

//----------------------------------------------------------------------------

//STRIP001 class ScUndoCursorAttr: public ScSimpleUndo
//STRIP001 {
//STRIP001 public:
//STRIP001                  TYPEINFO();
//STRIP001                  ScUndoCursorAttr( ScDocShell* pNewDocShell,
//STRIP001                          USHORT nNewCol, USHORT nNewRow, USHORT nNewTab,
//STRIP001                          const ScPatternAttr* pOldPat, const ScPatternAttr* pNewPat,
//STRIP001                          const ScPatternAttr* pApplyPat, BOOL bAutomatic );
//STRIP001  virtual         ~ScUndoCursorAttr();
//STRIP001
//STRIP001  virtual void    Undo();
//STRIP001  virtual void    Redo();
//STRIP001  virtual void    Repeat(SfxRepeatTarget& rTarget);
//STRIP001  virtual BOOL    CanRepeat(SfxRepeatTarget& rTarget) const;
//STRIP001
//STRIP001  virtual String  GetComment() const;
//STRIP001
//STRIP001 private:
//STRIP001  USHORT          nCol;
//STRIP001  USHORT          nRow;
//STRIP001  USHORT          nTab;
//STRIP001  ScPatternAttr*  pOldPattern;
//STRIP001  ScPatternAttr*  pNewPattern;
//STRIP001  ScPatternAttr*  pApplyPattern;
//STRIP001  BOOL            bIsAutomatic;
//STRIP001
//STRIP001  void            DoChange( const ScPatternAttr* pWhichPattern ) const;
//STRIP001 };


//STRIP001 class ScUndoEnterData: public ScSimpleUndo
//STRIP001 {
//STRIP001 public:
//STRIP001                  TYPEINFO();
//STRIP001                  ScUndoEnterData( ScDocShell* pNewDocShell,
//STRIP001                          USHORT nNewCol, USHORT nNewRow, USHORT nNewTab,
//STRIP001                          USHORT nNewCount, USHORT* pNewTabs,
//STRIP001                          ScBaseCell** ppOldData, BOOL* pHasForm, ULONG* pOldForm,
//STRIP001                          const String& rNewStr, EditTextObject* pObj = NULL );
//STRIP001  virtual         ~ScUndoEnterData();
//STRIP001
//STRIP001  virtual void    Undo();
//STRIP001  virtual void    Redo();
//STRIP001  virtual void    Repeat(SfxRepeatTarget& rTarget);
//STRIP001  virtual BOOL    CanRepeat(SfxRepeatTarget& rTarget) const;
//STRIP001
//STRIP001  virtual String  GetComment() const;
//STRIP001
//STRIP001 private:
//STRIP001  String          aNewString;
//STRIP001  USHORT*         pTabs;
//STRIP001  ScBaseCell**    ppOldCells;
//STRIP001  BOOL*           pHasFormat;
//STRIP001  ULONG*          pOldFormats;
//STRIP001  EditTextObject* pNewEditData;
//STRIP001  ULONG           nEndChangeAction;
//STRIP001  USHORT          nCol;
//STRIP001  USHORT          nRow;
//STRIP001  USHORT          nTab;
//STRIP001  USHORT          nCount;             //  markierte Tabellen
//STRIP001
//STRIP001  void            DoChange() const;
//STRIP001  void            SetChangeTrack();
//STRIP001 };


//STRIP001 class ScUndoEnterValue: public ScSimpleUndo
//STRIP001 {
//STRIP001 public:
//STRIP001                  TYPEINFO();
//STRIP001                  ScUndoEnterValue( ScDocShell* pNewDocShell,
//STRIP001                          const ScAddress& rNewPos,
//STRIP001                          ScBaseCell* pUndoCell, double nVal, BOOL bHeight );
//STRIP001  virtual         ~ScUndoEnterValue();
//STRIP001
//STRIP001  virtual void    Undo();
//STRIP001  virtual void    Redo();
//STRIP001  virtual void    Repeat(SfxRepeatTarget& rTarget);
//STRIP001  virtual BOOL    CanRepeat(SfxRepeatTarget& rTarget) const;
//STRIP001
//STRIP001  virtual String  GetComment() const;
//STRIP001
//STRIP001 private:
//STRIP001  ScAddress       aPos;
//STRIP001  ScBaseCell*     pOldCell;
//STRIP001  double          nValue;
//STRIP001  ULONG           nEndChangeAction;
//STRIP001  BOOL            bNeedHeight;
//STRIP001
//STRIP001  void            SetChangeTrack();
//STRIP001 };


class ScUndoPutCell: public ScSimpleUndo
{
public:
//STRIP001                  TYPEINFO();
                    ScUndoPutCell( ScDocShell* pNewDocShell,
                            const ScAddress& rNewPos,
                            ScBaseCell* pUndoCell, ScBaseCell* pRedoCell, BOOL bHeight );
    virtual         ~ScUndoPutCell();

//STRIP001  virtual void    Undo();
//STRIP001  virtual void    Redo();
//STRIP001  virtual void    Repeat(SfxRepeatTarget& rTarget);
    virtual BOOL    CanRepeat(SfxRepeatTarget& rTarget) const;

    virtual String  GetComment() const;

private:
    ScAddress       aPos;
    ScBaseCell*     pOldCell;
    ScBaseCell*     pEnteredCell;
    ULONG           nEndChangeAction;
    BOOL            bNeedHeight;

    void            SetChangeTrack();
};


//STRIP001 class ScUndoPageBreak: public ScSimpleUndo
//STRIP001 {
//STRIP001 public:
//STRIP001                  TYPEINFO();
//STRIP001                  ScUndoPageBreak( ScDocShell* pNewDocShell,
//STRIP001                          USHORT nNewCol, USHORT nNewRow, USHORT nNewTab,
//STRIP001                          BOOL bNewColumn, BOOL bNewInsert );
//STRIP001  virtual         ~ScUndoPageBreak();
//STRIP001
//STRIP001  virtual void    Undo();
//STRIP001  virtual void    Redo();
//STRIP001  virtual void    Repeat(SfxRepeatTarget& rTarget);
//STRIP001  virtual BOOL    CanRepeat(SfxRepeatTarget& rTarget) const;
//STRIP001
//STRIP001  virtual String  GetComment() const;
//STRIP001
//STRIP001 private:
//STRIP001  USHORT          nCol;
//STRIP001  USHORT          nRow;
//STRIP001  USHORT          nTab;
//STRIP001  BOOL            bColumn;        // Spalten- oder Zeilenumbruch
//STRIP001  BOOL            bInsert;        // Einfuegen oder Loeschen
//STRIP001
//STRIP001  void            DoChange( BOOL bInsert ) const;
//STRIP001 };

//STRIP001 class ScUndoPrintZoom: public ScSimpleUndo
//STRIP001 {
//STRIP001 public:
//STRIP001                  TYPEINFO();
//STRIP001                  ScUndoPrintZoom( ScDocShell* pNewDocShell, USHORT nT,
//STRIP001                                  USHORT nOS, USHORT nOP, USHORT nNS, USHORT nNP );
//STRIP001  virtual         ~ScUndoPrintZoom();
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
//STRIP001  USHORT          nOldScale;
//STRIP001  USHORT          nOldPages;
//STRIP001  USHORT          nNewScale;
//STRIP001  USHORT          nNewPages;
//STRIP001
//STRIP001  void            DoChange( BOOL bUndo );
//STRIP001 };

//STRIP001 class ScUndoThesaurus: public ScSimpleUndo
//STRIP001 {
//STRIP001 public:
//STRIP001                  TYPEINFO();
//STRIP001                  ScUndoThesaurus( ScDocShell* pNewDocShell,
//STRIP001                          USHORT nNewCol, USHORT nNewRow, USHORT nNewTab,
//STRIP001                          const String& rNewUndoStr, const EditTextObject* pUndoTObj,
//STRIP001                          const String& rNewRedoStr, const EditTextObject* pRedoTObj);
//STRIP001  virtual         ~ScUndoThesaurus();
//STRIP001
//STRIP001  virtual void    Undo();
//STRIP001  virtual void    Redo();
//STRIP001  virtual void    Repeat(SfxRepeatTarget& rTarget);
//STRIP001  virtual BOOL    CanRepeat(SfxRepeatTarget& rTarget) const;
//STRIP001
//STRIP001  virtual String  GetComment() const;
//STRIP001
//STRIP001 private:
//STRIP001  USHORT          nCol;
//STRIP001  USHORT          nRow;
//STRIP001  USHORT          nTab;
//STRIP001  String          aUndoStr;           // Daten bei StringZelle
//STRIP001  EditTextObject* pUndoTObject;       //       bei EditZelle
//STRIP001  String          aRedoStr;
//STRIP001  EditTextObject* pRedoTObject;
//STRIP001  ULONG           nEndChangeAction;
//STRIP001
//STRIP001  void            DoChange( BOOL bUndo, const String& rStr,
//STRIP001                              const EditTextObject* pTObj );
//STRIP001  void            SetChangeTrack( ScBaseCell* pOldCell );
//STRIP001 };


class ScUndoNote: public ScSimpleUndo
{
public:
//STRIP001                  TYPEINFO();
                    ScUndoNote( ScDocShell* pNewDocShell,
                                BOOL bShow, const ScAddress& rNewPos,
                                SdrUndoAction* pDraw );
    virtual         ~ScUndoNote();

//STRIP001  virtual void    Undo();
//STRIP001  virtual void    Redo();
//STRIP001  virtual void    Repeat(SfxRepeatTarget& rTarget);
//STRIP001  virtual BOOL    CanRepeat(SfxRepeatTarget& rTarget) const;

//STRIP001  virtual String  GetComment() const;

private:
    BOOL            bIsShow;
    ScAddress       aPos;
    SdrUndoAction*  pDrawUndo;
};


//STRIP001 class ScUndoEditNote: public ScSimpleUndo
//STRIP001 {
//STRIP001 public:
//STRIP001                  TYPEINFO();
//STRIP001                  ScUndoEditNote( ScDocShell* pNewDocShell,
//STRIP001                                  const ScAddress& rNewPos,
//STRIP001                                  const ScPostIt& rOld,
//STRIP001                                  const ScPostIt& rNew );
//STRIP001  virtual         ~ScUndoEditNote();
//STRIP001
//STRIP001  virtual void    Undo();
//STRIP001  virtual void    Redo();
//STRIP001  virtual void    Repeat(SfxRepeatTarget& rTarget);
//STRIP001  virtual BOOL    CanRepeat(SfxRepeatTarget& rTarget) const;
//STRIP001
//STRIP001  virtual String  GetComment() const;
//STRIP001
//STRIP001 private:
//STRIP001  ScAddress       aPos;
//STRIP001  ScPostIt        aOldNote;
//STRIP001  ScPostIt        aNewNote;
//STRIP001 };


//STRIP001 class ScUndoDetective: public ScSimpleUndo
//STRIP001 {
//STRIP001 public:
//STRIP001                  TYPEINFO();
//STRIP001                  ScUndoDetective( ScDocShell* pNewDocShell,
//STRIP001                                  SdrUndoAction* pDraw, const ScDetOpData* pOperation,
//STRIP001                                  ScDetOpList* pUndoList = NULL );
//STRIP001  virtual         ~ScUndoDetective();
//STRIP001
//STRIP001  virtual void    Undo();
//STRIP001  virtual void    Redo();
//STRIP001  virtual void    Repeat(SfxRepeatTarget& rTarget);
//STRIP001  virtual BOOL    CanRepeat(SfxRepeatTarget& rTarget) const;
//STRIP001
//STRIP001  virtual String  GetComment() const;
//STRIP001
//STRIP001 private:
//STRIP001  BOOL            bIsDelete;
//STRIP001  ScDetOpList*    pOldList;
//STRIP001  USHORT          nAction;
//STRIP001  ScAddress       aPos;
//STRIP001  SdrUndoAction*  pDrawUndo;
//STRIP001 };


class ScUndoRangeNames: public ScSimpleUndo
{
public:
//STRIP001                  TYPEINFO();
                    ScUndoRangeNames( ScDocShell* pNewDocShell,
                                        ScRangeName* pOld, ScRangeName* pNew );
    virtual         ~ScUndoRangeNames();

//STRIP001  virtual void    Undo();
//STRIP001  virtual void    Redo();
//STRIP001  virtual void    Repeat(SfxRepeatTarget& rTarget);
    virtual BOOL    CanRepeat(SfxRepeatTarget& rTarget) const;

    virtual String  GetComment() const;

private:
    ScRangeName*    pOldRanges;
    ScRangeName*    pNewRanges;

//STRIP001  void            DoChange( BOOL bUndo );
};



} //namespace binfilter
#endif

