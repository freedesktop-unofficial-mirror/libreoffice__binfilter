/*************************************************************************
 *
 *  $RCSfile: undotab.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:30:18 $
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

#ifndef SC_UNDOTAB_HXX
#define SC_UNDOTAB_HXX

#ifndef SC_UNDOBASE_HXX
#include "undobase.hxx"
#endif
#ifndef SC_MARKDATA_HXX
#include "markdata.hxx"
#endif

#ifndef _SVSTDARR_USHORTS

#define _SVSTDARR_USHORTS
#include <svtools/svstdarr.hxx>

#endif

#ifndef _SVSTDARR_STRINGS

#define _SVSTDARR_STRINGS
#include <svtools/svstdarr.hxx>

#endif
namespace binfilter {
class ScDocShell;
class ScDocument;
class SdrUndoAction;
class ScPrintRangeSaver;
class SdrObject;

//----------------------------------------------------------------------------

class ScUndoInsertTab : public ScSimpleUndo
{
public:
//STRIP001                  TYPEINFO();
                    ScUndoInsertTab(
                            ScDocShell* pNewDocShell,
                            USHORT nTabNum,
                            BOOL bApp,
                            const String& rNewName);
    virtual         ~ScUndoInsertTab();

//STRIP001  virtual void    Undo();
//STRIP001  virtual void    Redo();
//STRIP001  virtual void    Repeat(SfxRepeatTarget& rTarget);
    virtual BOOL    CanRepeat(SfxRepeatTarget& rTarget) const;

    virtual String  GetComment() const;

private:
    String          sNewName;
    SdrUndoAction*  pDrawUndo;
    ULONG           nEndChangeAction;
    USHORT          nTab;
    BOOL            bAppend;

    void            SetChangeTrack();
};

//STRIP001 class ScUndoInsertTables : public ScSimpleUndo
//STRIP001 {
//STRIP001 public:
//STRIP001                  TYPEINFO();
//STRIP001                  ScUndoInsertTables(
//STRIP001                          ScDocShell* pNewDocShell,
//STRIP001                          USHORT nTabNum,
//STRIP001                          BOOL bApp,
//STRIP001                          SvStrings *pNewNameList);
//STRIP001  virtual         ~ScUndoInsertTables();
//STRIP001
//STRIP001  virtual void    Undo();
//STRIP001  virtual void    Redo();
//STRIP001  virtual void    Repeat(SfxRepeatTarget& rTarget);
//STRIP001  virtual BOOL    CanRepeat(SfxRepeatTarget& rTarget) const;
//STRIP001
//STRIP001  virtual String  GetComment() const;
//STRIP001
//STRIP001 private:
//STRIP001
//STRIP001  SdrUndoAction*  pDrawUndo;
//STRIP001  SvStrings*      pNameList;
//STRIP001  ULONG           nStartChangeAction;
//STRIP001  ULONG           nEndChangeAction;
//STRIP001  USHORT          nTab;
//STRIP001  BOOL            bAppend;
//STRIP001
//STRIP001  void            SetChangeTrack();
//STRIP001 };


//STRIP001 class ScUndoDeleteTab: public ScMoveUndo // Draw vom Move fuer geloeschte Tabelle
//STRIP001 {
//STRIP001 public:
//STRIP001                  TYPEINFO();
//STRIP001                  ScUndoDeleteTab(
//STRIP001                          ScDocShell* pNewDocShell,
//STRIP001                          const SvUShorts &theTabs,       //USHORT nNewTab,
//STRIP001                          ScDocument* pUndoDocument,
//STRIP001                          ScRefUndoData* pRefData );
//STRIP001  virtual         ~ScUndoDeleteTab();
//STRIP001
//STRIP001  virtual void    Undo();
//STRIP001  virtual void    Redo();
//STRIP001  virtual void    Repeat(SfxRepeatTarget& rTarget);
//STRIP001  virtual BOOL    CanRepeat(SfxRepeatTarget& rTarget) const;
//STRIP001
//STRIP001  virtual String  GetComment() const;
//STRIP001
//STRIP001 private:
//STRIP001  SvUShorts   theTabs;
//STRIP001  ULONG           nStartChangeAction;
//STRIP001  ULONG           nEndChangeAction;
//STRIP001
//STRIP001  void            SetChangeTrack();
//STRIP001 };


class ScUndoRenameTab: public ScSimpleUndo
{
public:
//STRIP001                  TYPEINFO();
                    ScUndoRenameTab(
                            ScDocShell* pNewDocShell,
                            USHORT nT,
                            const String& rOldName,
                            const String& rNewName);
    virtual         ~ScUndoRenameTab();

//STRIP001  virtual void    Undo();
//STRIP001  virtual void    Redo();
//STRIP001  virtual void    Repeat(SfxRepeatTarget& rTarget);
    virtual BOOL    CanRepeat(SfxRepeatTarget& rTarget) const;

    virtual String  GetComment() const;

private:
    USHORT  nTab;
    String  sOldName;
    String  sNewName;

//STRIP001  void DoChange( USHORT nTab, const String& rName ) const;
};


//STRIP001 class ScUndoMoveTab: public ScSimpleUndo
//STRIP001 {
//STRIP001 public:
//STRIP001                  TYPEINFO();
//STRIP001                  ScUndoMoveTab( ScDocShell* pNewDocShell,
//STRIP001                                const SvUShorts &aOldTab,
//STRIP001                                const SvUShorts &aNewTab);
//STRIP001  virtual         ~ScUndoMoveTab();
//STRIP001
//STRIP001  virtual void    Undo();
//STRIP001  virtual void    Redo();
//STRIP001  virtual void    Repeat(SfxRepeatTarget& rTarget);
//STRIP001  virtual BOOL    CanRepeat(SfxRepeatTarget& rTarget) const;
//STRIP001
//STRIP001  virtual String  GetComment() const;
//STRIP001
//STRIP001 private:
//STRIP001  SvUShorts   theOldTabs;
//STRIP001  SvUShorts   theNewTabs;
//STRIP001
//STRIP001  void DoChange( BOOL bUndo ) const;
//STRIP001 };


//STRIP001 class ScUndoCopyTab: public ScSimpleUndo
//STRIP001 {
//STRIP001 public:
//STRIP001                  TYPEINFO();
//STRIP001                  ScUndoCopyTab(ScDocShell* pNewDocShell,
//STRIP001                                const SvUShorts &aOldTab,
//STRIP001                                const SvUShorts &aNewTab);
//STRIP001
//STRIP001  virtual         ~ScUndoCopyTab();
//STRIP001
//STRIP001  virtual void    Undo();
//STRIP001  virtual void    Redo();
//STRIP001  virtual void    Repeat(SfxRepeatTarget& rTarget);
//STRIP001  virtual BOOL    CanRepeat(SfxRepeatTarget& rTarget) const;
//STRIP001
//STRIP001  virtual String  GetComment() const;
//STRIP001
//STRIP001 private:
//STRIP001  SdrUndoAction*  pDrawUndo;
//STRIP001  SvUShorts   theOldTabs;
//STRIP001  SvUShorts   theNewTabs;
//STRIP001
//STRIP001  void DoChange() const;
//STRIP001 };


//STRIP001 class ScUndoMakeScenario: public ScSimpleUndo
//STRIP001 {
//STRIP001 public:
//STRIP001                  TYPEINFO();
//STRIP001                  ScUndoMakeScenario(
//STRIP001                          ScDocShell* pNewDocShell,
//STRIP001                          USHORT nSrc, USHORT nDest,
//STRIP001                          ScDocument* pUndo,
//STRIP001                          const String& rN, const String& rC,
//STRIP001                          const Color& rCol, USHORT nF,
//STRIP001                          const ScMarkData& rMark );
//STRIP001  virtual         ~ScUndoMakeScenario();
//STRIP001
//STRIP001  virtual void    Undo();
//STRIP001  virtual void    Redo();
//STRIP001  virtual void    Repeat(SfxRepeatTarget& rTarget);
//STRIP001  virtual BOOL    CanRepeat(SfxRepeatTarget& rTarget) const;
//STRIP001
//STRIP001  virtual String  GetComment() const;
//STRIP001
//STRIP001 private:
//STRIP001  USHORT      nSrcTab;
//STRIP001  USHORT      nDestTab;
//STRIP001  ScDocument* pUndoDoc;
//STRIP001  String      aName;
//STRIP001  String      aComment;
//STRIP001  Color       aColor;
//STRIP001  USHORT      nFlags;
//STRIP001  ScMarkData  aMarkData;
//STRIP001 };


//STRIP001 class ScUndoImportTab : public ScSimpleUndo
//STRIP001 {
//STRIP001 public:
//STRIP001                  TYPEINFO();
//STRIP001                  ScUndoImportTab(
//STRIP001                          ScDocShell* pShell,
//STRIP001                          USHORT nNewTab, USHORT nNewCount,
//STRIP001                          BOOL bNewLink );
//STRIP001  virtual         ~ScUndoImportTab();
//STRIP001
//STRIP001  virtual void    Undo();
//STRIP001  virtual void    Redo();
//STRIP001  virtual void    Repeat(SfxRepeatTarget& rTarget);
//STRIP001  virtual BOOL    CanRepeat(SfxRepeatTarget& rTarget) const;
//STRIP001
//STRIP001  virtual String  GetComment() const;
//STRIP001
//STRIP001 private:
//STRIP001  USHORT      nTab;
//STRIP001  USHORT      nCount;
//STRIP001  BOOL        bLink;
//STRIP001  ScDocument* pRedoDoc;
//STRIP001  SdrUndoAction*  pDrawUndo;
//STRIP001
//STRIP001  void DoChange() const;
//STRIP001 };


//STRIP001 class ScUndoRemoveLink : public ScSimpleUndo
//STRIP001 {
//STRIP001 public:
//STRIP001                  TYPEINFO();
//STRIP001                  ScUndoRemoveLink(               // vor dem Loeschen aufrufen!
//STRIP001                          ScDocShell* pShell,
//STRIP001                          const String& rDoc );
//STRIP001  virtual         ~ScUndoRemoveLink();
//STRIP001
//STRIP001  virtual void    Undo();
//STRIP001  virtual void    Redo();
//STRIP001  virtual void    Repeat(SfxRepeatTarget& rTarget);
//STRIP001  virtual BOOL    CanRepeat(SfxRepeatTarget& rTarget) const;
//STRIP001
//STRIP001  virtual String  GetComment() const;
//STRIP001
//STRIP001 private:
//STRIP001  String  aDocName;
//STRIP001  String  aFltName;
//STRIP001  String  aOptions;
//STRIP001  ULONG   nRefreshDelay;
//STRIP001  USHORT  nCount;
//STRIP001  USHORT* pTabs;
//STRIP001  BYTE*   pModes;
//STRIP001  String* pTabNames;
//STRIP001
//STRIP001  void DoChange( BOOL bLink ) const;
//STRIP001 };


class ScUndoShowHideTab : public ScSimpleUndo
{
public:
//STRIP001                  TYPEINFO();
                    ScUndoShowHideTab(
                            ScDocShell* pShell,
                            USHORT nNewTab, BOOL bNewShow );
    virtual         ~ScUndoShowHideTab();

//STRIP001  virtual void    Undo();
//STRIP001  virtual void    Redo();
//STRIP001  virtual void    Repeat(SfxRepeatTarget& rTarget);
    virtual BOOL    CanRepeat(SfxRepeatTarget& rTarget) const;

    virtual String  GetComment() const;

private:
    USHORT  nTab;
    BOOL    bShow;

//STRIP001  void DoChange( BOOL bShow ) const;
};


//STRIP001 class ScUndoProtect : public ScSimpleUndo
//STRIP001 {
//STRIP001 public:
//STRIP001                  TYPEINFO();
//STRIP001                  ScUndoProtect( ScDocShell* pShell, USHORT nNewTab,
//STRIP001                                  BOOL bNewProtect, const ::com::sun::star::uno::Sequence<sal_Int8>& rNewPassword );
//STRIP001  virtual         ~ScUndoProtect();
//STRIP001
//STRIP001  virtual void    Undo();
//STRIP001  virtual void    Redo();
//STRIP001  virtual void    Repeat(SfxRepeatTarget& rTarget);
//STRIP001  virtual BOOL    CanRepeat(SfxRepeatTarget& rTarget) const;
//STRIP001
//STRIP001  virtual String  GetComment() const;
//STRIP001
//STRIP001 private:
//STRIP001  USHORT  nTab;
//STRIP001  BOOL    bProtect;
//STRIP001  ::com::sun::star::uno::Sequence<sal_Int8>   aPassword;
//STRIP001
//STRIP001  void    DoProtect( BOOL bDo );
//STRIP001 };


class ScUndoPrintRange : public ScSimpleUndo
{
public:
//STRIP001                  TYPEINFO();
                    ScUndoPrintRange( ScDocShell* pShell, USHORT nNewTab,
                                        ScPrintRangeSaver* pOld, ScPrintRangeSaver* pNew );
    virtual         ~ScUndoPrintRange();

//STRIP001  virtual void    Undo();
//STRIP001  virtual void    Redo();
//STRIP001  virtual void    Repeat(SfxRepeatTarget& rTarget);
//STRIP001  virtual BOOL    CanRepeat(SfxRepeatTarget& rTarget) const;
//STRIP001
//STRIP001  virtual String  GetComment() const;
//STRIP001
private:
    USHORT              nTab;
    ScPrintRangeSaver*  pOldRanges;
    ScPrintRangeSaver*  pNewRanges;

//STRIP001  void DoChange( BOOL bUndo );
};


//STRIP001 class ScUndoScenarioFlags: public ScSimpleUndo
//STRIP001 {
//STRIP001 public:
//STRIP001                  TYPEINFO();
//STRIP001                  ScUndoScenarioFlags(
//STRIP001                          ScDocShell* pNewDocShell, USHORT nT,
//STRIP001                          const String& rON, const String& rNN,
//STRIP001                          const String& rOC, const String& rNC,
//STRIP001                          const Color& rOCol, const Color& rNCol,
//STRIP001                          USHORT nOF, USHORT nNF );
//STRIP001
//STRIP001  virtual         ~ScUndoScenarioFlags();
//STRIP001
//STRIP001  virtual void    Undo();
//STRIP001  virtual void    Redo();
//STRIP001  virtual void    Repeat(SfxRepeatTarget& rTarget);
//STRIP001  virtual BOOL    CanRepeat(SfxRepeatTarget& rTarget) const;
//STRIP001
//STRIP001  virtual String  GetComment() const;
//STRIP001
//STRIP001 private:
//STRIP001  USHORT  nTab;
//STRIP001  String  aOldName;
//STRIP001  String  aNewName;
//STRIP001  String  aOldComment;
//STRIP001  String  aNewComment;
//STRIP001  Color   aOldColor;
//STRIP001  Color   aNewColor;
//STRIP001  USHORT  nOldFlags;
//STRIP001  USHORT  nNewFlags;
//STRIP001 };


//STRIP001 class ScUndoRenameObject: public ScSimpleUndo
//STRIP001 {
//STRIP001 public:
//STRIP001                  TYPEINFO();
//STRIP001                  ScUndoRenameObject(
//STRIP001                          ScDocShell* pNewDocShell, const String& rPN,
//STRIP001                          const String& rON, const String& rNN );
//STRIP001
//STRIP001  virtual         ~ScUndoRenameObject();
//STRIP001
//STRIP001  virtual void    Undo();
//STRIP001  virtual void    Redo();
//STRIP001  virtual void    Repeat(SfxRepeatTarget& rTarget);
//STRIP001  virtual BOOL    CanRepeat(SfxRepeatTarget& rTarget) const;
//STRIP001
//STRIP001  virtual String  GetComment() const;
//STRIP001
//STRIP001 private:
//STRIP001  String  aPersistName;       // to find object (works only for OLE objects)
//STRIP001  String  aOldName;
//STRIP001  String  aNewName;
//STRIP001
//STRIP001  SdrObject*  GetObject();
//STRIP001 };



} //namespace binfilter
#endif

