/*************************************************************************
 *
 *  $RCSfile: content.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 11:58:43 $
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

#ifndef SC_CONTENT_HXX
#define SC_CONTENT_HXX

#ifndef _SVTREEBOX_HXX //autogen
#include <svtools/svtreebx.hxx>
#endif

// auto strip #ifndef SC_SCGLOB_HXX
// auto strip #include "global.hxx"
// auto strip #endif
namespace binfilter {

//STRIP001 class ScNavigatorDlg;
//STRIP001 class ScNavigatorSettings;
//STRIP001 class ScDocument;
//STRIP001 class ScDocShell;
//STRIP001 class ScAreaLink;
//STRIP001
/*N*/ #define SC_CONTENT_ROOT           0
/*N*/ #define SC_CONTENT_TABLE      1
/*N*/ #define SC_CONTENT_RANGENAME  2
/*N*/ #define SC_CONTENT_DBAREA     3
/*N*/ #define SC_CONTENT_GRAPHIC        4
/*N*/ #define SC_CONTENT_OLEOBJECT  5
/*N*/ #define SC_CONTENT_NOTE           6
/*N*/ #define SC_CONTENT_AREALINK       7
/*N*/ #define SC_CONTENT_DRAWING        8
/*N*/ #define SC_CONTENT_COUNT      9

const ULONG SC_CONTENT_NOCHILD  = ~0UL;

//
//  TreeListBox fuer Inhalte
//

//STRIP001 class ScContentTree : public SvTreeListBox
//STRIP001 {
//STRIP001  ScNavigatorDlg*     pParentWindow;
//STRIP001  ImageList           aEntryImages;
//STRIP001  ImageList           aHCEntryImages;
//STRIP001  SvLBoxEntry*        pRootNodes[SC_CONTENT_COUNT];
//STRIP001  USHORT              nRootType;          // als Root eingestellt
//STRIP001  String              aManualDoc;         // im Navigator umgeschaltet (Title)
//STRIP001  BOOL                bHiddenDoc;         // verstecktes aktiv?
//STRIP001  String              aHiddenName;        // URL zum Laden
//STRIP001  String              aHiddenTitle;       // fuer Anzeige
//STRIP001  ScDocument*         pHiddenDocument;    // temporaer
//STRIP001
//STRIP001  USHORT              pPosList[SC_CONTENT_COUNT];     // fuer die Reihenfolge
//STRIP001
//STRIP001  static BOOL bIsInDrag;      // static, falls der Navigator im ExecuteDrag geloescht wird
//STRIP001
//STRIP001  ScDocShell* GetManualOrCurrent();
//STRIP001
//STRIP001  void    InitRoot(USHORT nType);
//STRIP001  void    ClearType(USHORT nType);
//STRIP001  void    ClearAll();
//STRIP001  void    InsertContent( USHORT nType, const String& rValue );
//STRIP001  void    GetDrawNames( USHORT nType, USHORT nId );
//STRIP001
//STRIP001  void    GetTableNames();
//STRIP001  void    GetAreaNames();
//STRIP001  void    GetDbNames();
//STRIP001  void    GetLinkNames();
//STRIP001  void    GetGraphicNames();
//STRIP001  void    GetOleNames();
//STRIP001  void    GetGroupNames();
//STRIP001  void    GetNoteStrings();
//STRIP001
//STRIP001  BOOL    DrawNamesChanged( USHORT nType, USHORT nId );
//STRIP001  BOOL    NoteStringsChanged();
//STRIP001
//STRIP001  ScAddress GetNotePos( ULONG nIndex );
//STRIP001  const ScAreaLink* GetLink( ULONG nIndex );
//STRIP001
//STRIP001     /** Returns the indexes of the specified listbox entry.
//STRIP001         @param rnRootIndex  Root index of specified entry is returned.
//STRIP001         @param rnChildIndex  Index of the entry inside its root is returned (or SC_CONTENT_NOCHILD if entry is root).
//STRIP001         @param pEntry  The entry to examine. */
//STRIP001     void    GetEntryIndexes( USHORT& rnRootIndex, ULONG& rnChildIndex, SvLBoxEntry* pEntry ) const;
//STRIP001
//STRIP001     /** Returns the child index of the specified listbox entry.
//STRIP001         @param pEntry  The entry to examine or NULL for the selected entry.
//STRIP001         @return  Index of the entry inside its root or SC_CONTENT_NOCHILD if entry is root. */
//STRIP001     ULONG   GetChildIndex( SvLBoxEntry* pEntry ) const;
//STRIP001
//STRIP001  void    DoDrag();
//STRIP001  void    AdjustTitle();
//STRIP001
//STRIP001  ScDocument* GetSourceDocument();
//STRIP001
//STRIP001  DECL_LINK( DoubleClickHdl, ScContentTree* );
//STRIP001  DECL_STATIC_LINK( ScContentTree, ExecDragHdl, void* );
//STRIP001
//STRIP001 protected:
//STRIP001 //   virtual BOOL    Drop( const DropEvent& rEvt );
//STRIP001 //   virtual BOOL    QueryDrop( DropEvent& rEvt );
//STRIP001
//STRIP001  virtual sal_Int8    AcceptDrop( const AcceptDropEvent& rEvt );
//STRIP001  virtual sal_Int8    ExecuteDrop( const ExecuteDropEvent& rEvt );
//STRIP001  virtual void        StartDrag( sal_Int8 nAction, const Point& rPosPixel );
//STRIP001  virtual void        DragFinished( sal_Int8 nAction );
//STRIP001
//STRIP001  virtual void    Command( const CommandEvent& rCEvt );
//STRIP001  virtual void    RequestHelp( const HelpEvent& rHEvt );
//STRIP001
//STRIP001 public:
//STRIP001          ScContentTree( Window* pParent, const ResId& rResId );
//STRIP001          ~ScContentTree();
//STRIP001
//STRIP001     virtual void    MouseButtonDown( const MouseEvent& rMEvt );
//STRIP001     virtual void    KeyInput( const KeyEvent& rKEvt );
//STRIP001
//STRIP001  void    InitWindowBits( BOOL bButtons );
//STRIP001
//STRIP001     void    Refresh( USHORT nType = 0 );
//STRIP001
//STRIP001  void    ToggleRoot();
//STRIP001  void    SetRootType( USHORT nNew );
//STRIP001  USHORT  GetRootType() const             { return nRootType; }
//STRIP001
//STRIP001  void    ActiveDocChanged();
//STRIP001  void    ResetManualDoc();
//STRIP001  void    SetManualDoc(const String& rName);
//STRIP001  BOOL    LoadFile(const String& rUrl);
//STRIP001  void    SelectDoc(const String& rName);
//STRIP001
//STRIP001  const String& GetHiddenTitle() const    { return aHiddenTitle; }
//STRIP001
//STRIP001     /** Applies the navigator settings to the listbox. */
//STRIP001     void                        ApplySettings();
//STRIP001     /** Stores the current listbox state in the navigator settings. */
//STRIP001     void                        StoreSettings() const;
//STRIP001
//STRIP001  static BOOL IsInDrag()  { return bIsInDrag; }
//STRIP001 };




} //namespace binfilter
#endif // SC_NAVIPI_HXX

