/*************************************************************************
 *
 *  $RCSfile: editundo.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:43:03 $
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

#ifndef _EDITUNDO_HXX
#define _EDITUNDO_HXX

#include <editdoc.hxx>
#include <editund2.hxx>
#include <editdata.hxx>
namespace binfilter {

#define UNDO_NOACTION           0
#define UNDO_NEWUNDO            1
#define UNDO_UNDOSDELETED       2
#define UNDO_EMPTYGROUPDELETED  3
#define UNDO_INVALIDEND         4

class ImpEditEngine;
class EditView;

// -----------------------------------------------------------------------
// EditUndoDelContent
// ------------------------------------------------------------------------
//STRIP001 class EditUndoDelContent : public EditUndo
//STRIP001 {
//STRIP001 private:
//STRIP001  BOOL            bDelObject;
//STRIP001  USHORT          nNode;
//STRIP001  ContentNode*    pContentNode;   // Zeigt auf das gueltige,
//STRIP001                                  // nicht zerstoerte Objekt!
//STRIP001
//STRIP001 public:
//STRIP001                  TYPEINFO();
//STRIP001                  EditUndoDelContent( ImpEditEngine* pImpEE, ContentNode* pNode, USHORT nPortio );
//STRIP001                  ~EditUndoDelContent();
//STRIP001
//STRIP001  virtual void    Undo();
//STRIP001  virtual void    Redo();
//STRIP001  virtual void    Repeat();
//STRIP001 };

// -----------------------------------------------------------------------
// EditUndoConnectParas
// ------------------------------------------------------------------------
//STRIP001 class EditUndoConnectParas : public EditUndo
//STRIP001 {
//STRIP001 private:
//STRIP001  USHORT          nNode;
//STRIP001  USHORT          nSepPos;
//STRIP001  SfxItemSet      aLeftParaAttribs;
//STRIP001  SfxItemSet      aRightParaAttribs;
//STRIP001
//STRIP001  // 2 Pointer waeren schoener, aber dann muesste es ein SfxListener sein.
//STRIP001  String          aLeftStyleName;
//STRIP001  String          aRightStyleName;
//STRIP001  SfxStyleFamily  eLeftStyleFamily;
//STRIP001  SfxStyleFamily  eRightStyleFamily;
//STRIP001
//STRIP001  BOOL            bBackward;
//STRIP001
//STRIP001 public:
//STRIP001                  TYPEINFO();
//STRIP001                  EditUndoConnectParas( ImpEditEngine* pImpEE, USHORT nNode, USHORT nSepPos,
//STRIP001                                          const SfxItemSet& rLeftParaAttribs, const SfxItemSet& rRightParaAttribs,
//STRIP001                                          const SfxStyleSheet* pLeftStyle, const SfxStyleSheet* pRightStyle, BOOL bBackward );
//STRIP001                  ~EditUndoConnectParas();
//STRIP001
//STRIP001  virtual void    Undo();
//STRIP001  virtual void    Redo();
//STRIP001  virtual void    Repeat();
//STRIP001 };

// -----------------------------------------------------------------------
// EditUndoSplitPara
// ------------------------------------------------------------------------
class EditUndoSplitPara : public EditUndo
{
private:
    USHORT          nNode;
    USHORT          nSepPos;

public:
//STRIP001                  TYPEINFO();
                    EditUndoSplitPara( ImpEditEngine* pImpEE, USHORT nNode, USHORT nSepPos );
                    ~EditUndoSplitPara();

    virtual void    Undo();
    virtual void    Redo();
    virtual void    Repeat();
};

// -----------------------------------------------------------------------
// EditUndoInsertChars
// ------------------------------------------------------------------------
class EditUndoInsertChars : public EditUndo
{
private:
    EPaM            aEPaM;
    String          aText;

public:
                    TYPEINFO();
                    EditUndoInsertChars( ImpEditEngine* pImpEE, const EPaM& rEPaM, const String& rStr );

    const EPaM&     GetEPaM() { return aEPaM; }
    String&         GetStr() { return aText; }

    virtual void    Undo();
    virtual void    Redo();
    virtual void    Repeat();

    virtual BOOL    Merge( SfxUndoAction *pNextAction );
};

// -----------------------------------------------------------------------
// EditUndoRemoveChars
// ------------------------------------------------------------------------
//STRIP001 class EditUndoRemoveChars : public EditUndo
//STRIP001 {
//STRIP001 private:
//STRIP001  EPaM            aEPaM;
//STRIP001  String          aText;
//STRIP001
//STRIP001 public:
//STRIP001                  TYPEINFO();
//STRIP001                  EditUndoRemoveChars( ImpEditEngine* pImpEE, const EPaM& rEPaM, const String& rStr );
//STRIP001
//STRIP001 #if defined(MACOSX) && ( __GNUC__ < 3 )
//STRIP001         // implementations moved to impedit2.cxx
//STRIP001         // fixme revisit after gcc3
//STRIP001  const EPaM&     GetEPaM();
//STRIP001  String&         GetStr();
//STRIP001 #else
//STRIP001  const EPaM&     GetEPaM() { return aEPaM; }
//STRIP001  String&         GetStr() { return aText; }
//STRIP001 #endif
//STRIP001
//STRIP001  virtual void    Undo();
//STRIP001  virtual void    Redo();
//STRIP001  virtual void    Repeat();
//STRIP001 };

// -----------------------------------------------------------------------
// EditUndoInsertFeature
// ------------------------------------------------------------------------
class EditUndoInsertFeature : public EditUndo
{
private:
    EPaM            aEPaM;
    SfxPoolItem*    pFeature;

public:
//STRIP001                  TYPEINFO();
                    EditUndoInsertFeature( ImpEditEngine* pImpEE, const EPaM& rEPaM,
                                            const SfxPoolItem& rFeature);
                    ~EditUndoInsertFeature();

    virtual void    Undo();
    virtual void    Redo();
    virtual void    Repeat();
};

// -----------------------------------------------------------------------
// EditUndoMoveParagraphs
// ------------------------------------------------------------------------
//STRIP001 class EditUndoMoveParagraphs: public EditUndo
//STRIP001 {
//STRIP001 private:
//STRIP001  Range           nParagraphs;
//STRIP001  USHORT          nDest;
//STRIP001
//STRIP001 public:
//STRIP001                  TYPEINFO();
//STRIP001                  EditUndoMoveParagraphs( ImpEditEngine* pImpEE, const Range& rParas, USHORT nDest );
//STRIP001                  ~EditUndoMoveParagraphs();
//STRIP001
//STRIP001  virtual void    Undo();
//STRIP001  virtual void    Redo();
//STRIP001  virtual void    Repeat();
//STRIP001 };

// -----------------------------------------------------------------------
// EditUndoSetStyleSheet
// ------------------------------------------------------------------------
class EditUndoSetStyleSheet: public EditUndo
{
private:
    USHORT          nPara;
    XubString       aPrevName;
    XubString       aNewName;
    SfxStyleFamily  ePrevFamily;
    SfxStyleFamily  eNewFamily;
    SfxItemSet      aPrevParaAttribs;

public:
//STRIP001                  TYPEINFO();

                    EditUndoSetStyleSheet( ImpEditEngine* pImpEE, USHORT nPara,
                        const XubString& rPrevName, SfxStyleFamily ePrevFamily,
                        const XubString& rNewName, SfxStyleFamily eNewFamily,
                        const SfxItemSet& rPrevParaAttribs );
                    ~EditUndoSetStyleSheet();

    virtual void    Undo();
    virtual void    Redo();
    virtual void    Repeat();
};

// -----------------------------------------------------------------------
// EditUndoSetParaAttribs
// ------------------------------------------------------------------------
class EditUndoSetParaAttribs: public EditUndo
{
private:
    USHORT          nPara;
    SfxItemSet      aPrevItems;
    SfxItemSet      aNewItems;

public:
//STRIP001                  TYPEINFO();
                    EditUndoSetParaAttribs( ImpEditEngine* pImpEE, USHORT nPara, const SfxItemSet& rPrevItems, const SfxItemSet& rNewItems );
                    ~EditUndoSetParaAttribs();

    virtual void    Undo();
    virtual void    Redo();
    virtual void    Repeat();
};

// -----------------------------------------------------------------------
// EditUndoSetAttribs
// ------------------------------------------------------------------------
//STRIP001 class EditUndoSetAttribs: public EditUndo
//STRIP001 {
//STRIP001 private:
//STRIP001  ESelection          aESel;
//STRIP001  SfxItemSet          aNewAttribs;
//STRIP001  ContentInfoArray    aPrevAttribs;
//STRIP001
//STRIP001  BYTE                nSpecial;
//STRIP001  BOOL                bSetIsRemove;
//STRIP001  BOOL                bRemoveParaAttribs;
//STRIP001  USHORT              nRemoveWhich;
//STRIP001
//STRIP001  void                ImpSetSelection( EditView* pView );
//STRIP001
//STRIP001
//STRIP001 public:
//STRIP001                      TYPEINFO();
//STRIP001                      EditUndoSetAttribs( ImpEditEngine* pImpEE, const ESelection& rESel, const SfxItemSet& rNewItems );
//STRIP001                      ~EditUndoSetAttribs();
//STRIP001
//STRIP001  ContentInfoArray&   GetContentInfos()   { return aPrevAttribs; }
//STRIP001  SfxItemSet&         GetNewAttribs()     { return aNewAttribs; }
//STRIP001
//STRIP001  void                SetSpecial( BYTE n )            { nSpecial = n; }
//STRIP001  void                SetRemoveAttribs( BOOL b )      { bSetIsRemove = b; }
//STRIP001  void                SetRemoveParaAttribs( BOOL b )  { bRemoveParaAttribs = b; }
//STRIP001  void                SetRemoveWhich( USHORT n )      { nRemoveWhich = n; }
//STRIP001
//STRIP001  virtual void        Undo();
//STRIP001  virtual void        Redo();
//STRIP001  virtual void        Repeat();
//STRIP001 };

// -----------------------------------------------------------------------
// EditUndoTransliteration
// ------------------------------------------------------------------------
//STRIP001 class EditUndoTransliteration: public EditUndo
//STRIP001 {
//STRIP001 private:
//STRIP001  ESelection          aOldESel;
//STRIP001  ESelection          aNewESel;
//STRIP001
//STRIP001  sal_Int32           nMode;
//STRIP001  EditTextObject*     pTxtObj;
//STRIP001  String              aText;
//STRIP001
//STRIP001 public:
//STRIP001                      TYPEINFO();
//STRIP001                      EditUndoTransliteration( ImpEditEngine* pImpEE, const ESelection& rESel, sal_Int32 nMode );
//STRIP001                      ~EditUndoTransliteration();
//STRIP001
//STRIP001  void                SetText( const String& rText ) { aText = rText; }
//STRIP001  void                SetText( EditTextObject* pObj ) { pTxtObj = pObj; }
//STRIP001  void                SetNewSelection( const ESelection& rSel ) { aNewESel = rSel; }
//STRIP001
//STRIP001  virtual void        Undo();
//STRIP001  virtual void        Redo();
//STRIP001  virtual void        Repeat();
//STRIP001 };

// -----------------------------------------------------------------------
// EditUndoMarkSelection
// ------------------------------------------------------------------------
//STRIP001 class EditUndoMarkSelection: public EditUndo
//STRIP001 {
//STRIP001 private:
//STRIP001  ESelection      aSelection;
//STRIP001
//STRIP001 public:
//STRIP001                  TYPEINFO();
//STRIP001                  EditUndoMarkSelection( ImpEditEngine* pImpEE, const ESelection& rSel );
//STRIP001                  ~EditUndoMarkSelection();
//STRIP001
//STRIP001  virtual void    Undo();
//STRIP001  virtual void    Redo();
//STRIP001  virtual void    Repeat();
//STRIP001 };


}//end of namespace binfilter
#endif // _EDITUNDO_HXX
