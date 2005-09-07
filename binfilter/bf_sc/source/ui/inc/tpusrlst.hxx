/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: tpusrlst.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-07 20:24:36 $
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

#ifndef SC_TPUSRLST_HXX
#define SC_TPUSRLST_HXX

// auto strip #ifndef _SFXTABDLG_HXX //autogen
// auto strip #include <bf_sfx2/tabdlg.hxx>
// auto strip #endif

// auto strip #ifndef _SV_FIXED_HXX //autogen
// auto strip #include <vcl/fixed.hxx>
// auto strip #endif

// auto strip #ifndef _SV_LSTBOX_HXX //autogen
// auto strip #include <vcl/lstbox.hxx>
// auto strip #endif

// auto strip #ifndef _SVEDIT_HXX //autogen
// auto strip #include <svtools/svmedit.hxx>
// auto strip #endif
namespace binfilter {

#define SC_MAXFIELDS 200

//========================================================================
// Benutzerdefinierte Listen:

class ScUserList;
class ScDocument;
class ScViewData;
class ScRangeUtil;

//STRIP001 class ScTpUserLists : public SfxTabPage
//STRIP001 {
//STRIP001 public:
//STRIP001  static  SfxTabPage* Create          ( Window*               pParent,
//STRIP001                                        const SfxItemSet&     rAttrSet );
//STRIP001  static  USHORT*     GetRanges       ();
//STRIP001  virtual BOOL        FillItemSet     ( SfxItemSet& rCoreAttrs );
//STRIP001  virtual void        Reset           ( const SfxItemSet& rCoreAttrs );
//STRIP001  virtual int         DeactivatePage  ( SfxItemSet* pSet = NULL );
//STRIP001
//STRIP001 private:
//STRIP001          ScTpUserLists( Window*              pParent,
//STRIP001                         const SfxItemSet&    rArgSet );
//STRIP001          ~ScTpUserLists();
//STRIP001
//STRIP001 private:
//STRIP001  FixedText       aFtLists;
//STRIP001  ListBox         aLbLists;
//STRIP001  FixedText       aFtEntries;
//STRIP001  MultiLineEdit   aEdEntries;
//STRIP001  FixedText       aFtCopyFrom;
//STRIP001  Edit            aEdCopyFrom;
//STRIP001  PushButton      aBtnNew;
//STRIP001  PushButton      aBtnAdd;
//STRIP001  PushButton      aBtnRemove;
//STRIP001  PushButton      aBtnCopy;
//STRIP001
//STRIP001  const String    aStrQueryRemove;
//STRIP001  const String    aStrNew;
//STRIP001  const String    aStrCancel;
//STRIP001  const String    aStrAdd;
//STRIP001  const String    aStrModify;
//STRIP001  const String    aStrCopyList;
//STRIP001  const String    aStrCopyFrom;
//STRIP001  const String    aStrCopyErr;
//STRIP001
//STRIP001  const USHORT    nWhichUserLists;
//STRIP001  ScUserList*     pUserLists;
//STRIP001
//STRIP001  ScDocument*     pDoc;
//STRIP001  ScViewData*     pViewData;
//STRIP001  ScRangeUtil*    pRangeUtil;
//STRIP001  String          aStrSelectedArea;
//STRIP001
//STRIP001  BOOL            bModifyMode;
//STRIP001  BOOL            bCancelMode;
//STRIP001  BOOL            bCopyDone;
//STRIP001  USHORT          nCancelPos;
//STRIP001
//STRIP001 #ifdef _TPUSRLST_CXX
//STRIP001 private:
//STRIP001  void    Init                ();
//STRIP001  USHORT  UpdateUserListBox   ();
//STRIP001  void    UpdateEntries       ( USHORT nList );
//STRIP001  void    MakeListStr         ( String& rListStr );
//STRIP001  void    AddNewList          ( const String& rEntriesStr );
//STRIP001  void    RemoveList          ( USHORT nList );
//STRIP001  void    ModifyList          ( USHORT        nSelList,
//STRIP001                                const String& rEntriesStr );
//STRIP001  void    CopyListFromArea    ( const ScRefTripel& rStartPos,
//STRIP001                                const ScRefTripel& rEndPos );
//STRIP001
//STRIP001  // Handler:
//STRIP001  DECL_LINK( LbSelectHdl,     ListBox* );
//STRIP001  DECL_LINK( BtnClickHdl,     PushButton* );
//STRIP001  DECL_LINK( EdEntriesModHdl, MultiLineEdit* );
//STRIP001 #endif
//STRIP001 };



} //namespace binfilter
#endif // SC_TPUSRLST_HXX

