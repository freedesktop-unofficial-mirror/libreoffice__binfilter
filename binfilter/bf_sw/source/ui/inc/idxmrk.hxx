/*************************************************************************
 *
 *  $RCSfile: idxmrk.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:55:19 $
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
#ifndef _IDXMRK_HXX
#define _IDXMRK_HXX

#ifndef _COM_SUN_STAR_CONTAINER_XNAMEACCESS_HPP_
#include <com/sun/star/container/XNameAccess.hpp>
#endif
#ifndef _BASEDLGS_HXX
#include <bf_sfx2/basedlgs.hxx>
#endif

#ifndef _FIXED_HXX //autogen
#include <vcl/fixed.hxx>
#endif

#ifndef _SV_LSTBOX_HXX
#include <vcl/lstbox.hxx>
#endif
#ifndef _COMBOBOX_HXX //autogen
#include <vcl/combobox.hxx>
#endif
#ifndef _SVX_STDDLG_HXX
#include <bf_svx/stddlg.hxx>
#endif

#ifndef _FIELD_HXX //autogen
#include <vcl/field.hxx>
#endif

#ifndef _GROUP_HXX //autogen
#include <vcl/group.hxx>
#endif

#ifndef _BUTTON_HXX //autogen
#include <vcl/button.hxx>
#endif

#ifndef _IMAGEBTN_HXX //autogen
#include <vcl/imagebtn.hxx>
#endif
#ifndef _SFX_CHILDWIN_HXX //autogen
#include <bf_sfx2/childwin.hxx>
#endif
#ifndef _TOXE_HXX
#include "toxe.hxx"
#endif
#ifndef _STDCTRL_HXX
#include <svtools/stdctrl.hxx>
#endif
#ifndef  _COM_SUN_STAR_I18N_XEXTENDEDINDEXENTRYSUPPLIER_HPP_
#include <com/sun/star/i18n/XExtendedIndexEntrySupplier.hpp>
#endif
namespace binfilter {
class SwWrtShell;
class SwTOXMgr;
class SwTOXMark;
/*--------------------------------------------------------------------
     Beschreibung:  Markierung fuer Verzeichniseintrag einfuegen
 --------------------------------------------------------------------*/
class SwIndexMarkFloatDlg;
class SwIndexMarkModalDlg;
//STRIP001 class SwIndexMarkDlg : public Window //SvxStandardDialog
//STRIP001 {
//STRIP001  friend class SwIndexMarkFloatDlg;
//STRIP001  friend class SwIndexMarkModalDlg;
//STRIP001  FixedText       aTypeFT;
//STRIP001  ListBox         aTypeDCB;
//STRIP001  ImageButton     aNewBT;
//STRIP001
//STRIP001  FixedText       aEntryFT;
//STRIP001  Edit            aEntryED;
//STRIP001  FixedText       aPhoneticFT0;
//STRIP001  Edit            aPhoneticED0;
//STRIP001
//STRIP001  FixedText       aKeyFT;
//STRIP001  ComboBox        aKeyDCB;
//STRIP001  FixedText       aPhoneticFT1;
//STRIP001  Edit            aPhoneticED1;
//STRIP001
//STRIP001  FixedText       aKey2FT;
//STRIP001  ComboBox        aKey2DCB;
//STRIP001  FixedText       aPhoneticFT2;
//STRIP001  Edit            aPhoneticED2;
//STRIP001
//STRIP001  FixedText       aLevelFT;
//STRIP001  NumericField    aLevelED;
//STRIP001      CheckBox        aMainEntryCB;
//STRIP001      CheckBox        aApplyToAllCB;
//STRIP001      CheckBox        aSearchCaseSensitiveCB;
//STRIP001      CheckBox        aSearchCaseWordOnlyCB;
//STRIP001
//STRIP001     FixedLine       aIndexFL;
//STRIP001
//STRIP001  OKButton        aOKBT;
//STRIP001  CancelButton    aCancelBT;
//STRIP001  HelpButton      aHelpBT;
//STRIP001  PushButton      aDelBT;
//STRIP001  //PushButton        aNewBT;
//STRIP001
//STRIP001  ImageButton     aPrevSameBT;
//STRIP001  ImageButton     aNextSameBT;
//STRIP001  ImageButton     aPrevBT;
//STRIP001  ImageButton     aNextBT;
//STRIP001
//STRIP001  String          aOrgStr;
//STRIP001  sal_Int32       nOptionsId;
//STRIP001  sal_Bool            bDel;
//STRIP001  sal_Bool            bNewMark;
//STRIP001  sal_Bool            bSelected;
//STRIP001
//STRIP001  BOOL            bPhoneticED0_ChangedByUser;
//STRIP001  BOOL            bPhoneticED1_ChangedByUser;
//STRIP001  BOOL            bPhoneticED2_ChangedByUser;
//STRIP001  LanguageType    nLangForPhoneticReading; //Language of current text used for phonetic reading proposal
//STRIP001  BOOL            bIsPhoneticReadingEnabled; //this value states wether phopentic reading is enabled in principle dependend of global cjk settings and language of current entry
//STRIP001  ::com::sun::star::uno::Reference< ::com::sun::star::i18n::XExtendedIndexEntrySupplier >
//STRIP001                  xExtendedIndexEntrySupplier;
//STRIP001
//STRIP001  SwTOXMgr*       pTOXMgr;
//STRIP001  SwWrtShell*     pSh;
//STRIP001
//STRIP001  void            Apply();
//STRIP001  void            InitControls();
//STRIP001  void            InsertMark();
//STRIP001  void            UpdateMark();
//STRIP001
//STRIP001  DECL_LINK( InsertHdl, Button * );
//STRIP001  DECL_LINK( CloseHdl, Button * );
//STRIP001  DECL_LINK( DelHdl, Button * );
//STRIP001  DECL_LINK( NextHdl, Button * );
//STRIP001  DECL_LINK( NextSameHdl, Button * );
//STRIP001  DECL_LINK( PrevHdl, Button * );
//STRIP001  DECL_LINK( PrevSameHdl, Button * );
//STRIP001  DECL_LINK( ModifyHdl, ListBox* pBox = 0 );
//STRIP001  DECL_LINK( KeyDCBModifyHdl, ComboBox * );
//STRIP001  DECL_LINK( NewUserIdxHdl, Button*);
//STRIP001  DECL_LINK( SearchTypeHdl, CheckBox*);
//STRIP001  DECL_LINK( PhoneticEDModifyHdl, Edit * );
//STRIP001
//STRIP001  //this method updates the values from 'nLangForPhoneticReading' and 'bIsPhoneticReadingEnabled'
//STRIP001  //it needs to be called ones if this dialog is opened to create a new entry (in InitControls),
//STRIP001  //or otherwise it has to be called for each changed TOXMark (in UpdateDialog)
//STRIP001  void            UpdateLanguageDependenciesForPhoneticReading();
//STRIP001  String          GetDefaultPhoneticReading( const String& rText );
//STRIP001
//STRIP001  void            UpdateKeyBoxes();
//STRIP001
//STRIP001  void            UpdateDialog();
//STRIP001  void            InsertUpdate();
//STRIP001
//STRIP001  virtual void    Activate();
//STRIP001
//STRIP001 public:
//STRIP001
//STRIP001  SwIndexMarkDlg( Window *pParent,
//STRIP001                  sal_Bool bNewDlg,
//STRIP001                  const ResId& rResId,
//STRIP001                  sal_Int32 _nOptionsId );
//STRIP001
//STRIP001
//STRIP001  ~SwIndexMarkDlg();
//STRIP001
//STRIP001     void    ReInitDlg(SwWrtShell& rWrtShell, SwTOXMark* pCurTOXMark = 0);
//STRIP001  sal_Bool    IsTOXType(const String& rName)
//STRIP001              {return LISTBOX_ENTRY_NOTFOUND != aTypeDCB.GetEntryPos(rName);}
//STRIP001 };
/* -----------------06.10.99 10:11-------------------

 --------------------------------------------------*/
//STRIP001 class SwIndexMarkFloatDlg : public SfxModelessDialog
//STRIP001 {
//STRIP001  SwIndexMarkDlg      aDlg;
//STRIP001  virtual void    Activate();
//STRIP001  public:
//STRIP001      SwIndexMarkFloatDlg(    SfxBindings* pBindings,
//STRIP001                              SfxChildWindow* pChild,
//STRIP001                              Window *pParent,
//STRIP001                              sal_Bool bNew=sal_True);
//STRIP001
//STRIP001      SwIndexMarkDlg&     GetDlg() {return aDlg;}
//STRIP001 };
/* -----------------06.10.99 10:33-------------------

 --------------------------------------------------*/
//STRIP001 class SwIndexMarkModalDlg : public SvxStandardDialog
//STRIP001 {
//STRIP001  SwIndexMarkDlg      aDlg;
//STRIP001 public:
//STRIP001     SwIndexMarkModalDlg(Window *pParent, SwWrtShell& rSh, SwTOXMark* pCurTOXMark);
//STRIP001
//STRIP001  SwIndexMarkDlg&     GetDlg() {return aDlg;}
//STRIP001  virtual void        Apply();
//STRIP001 };

/* -----------------07.09.99 08:02-------------------

 --------------------------------------------------*/
class SwInsertIdxMarkWrapper : public SfxChildWindow
{
protected:
    SwInsertIdxMarkWrapper( Window *pParentWindow,
                            sal_uInt16 nId,
                            SfxBindings* pBindings,
                            SfxChildWinInfo* pInfo );

    SFX_DECL_CHILDWINDOW(SwInsertIdxMarkWrapper);

public:
//STRIP001  void    ReInitDlg(SwWrtShell& rWrtShell)
//STRIP001      {((SwIndexMarkFloatDlg*)pWindow)->GetDlg().ReInitDlg(rWrtShell);}

};

/* -----------------15.09.99 08:39-------------------

 --------------------------------------------------*/
class SwAuthMarkModalDlg;
//STRIP001 class SwAuthMarkDlg : public Window
//STRIP001 {
//STRIP001  static sal_Bool     bIsFromComponent;
//STRIP001
//STRIP001  friend class SwAuthMarkModalDlg;
//STRIP001     friend class SwAuthMarkFloatDlg;
//STRIP001
//STRIP001     RadioButton     aFromComponentRB;
//STRIP001  RadioButton     aFromDocContentRB;
//STRIP001  FixedText       aAuthorFT;
//STRIP001  FixedInfo       aAuthorFI;
//STRIP001  FixedText       aTitleFT;
//STRIP001  FixedInfo       aTitleFI;
//STRIP001  FixedText       aEntryFT;
//STRIP001  Edit            aEntryED;
//STRIP001  ListBox         aEntryLB;
//STRIP001
//STRIP001     FixedLine       aEntryFL;
//STRIP001
//STRIP001  OKButton        aOKBT;
//STRIP001  CancelButton    aCancelBT;
//STRIP001  HelpButton      aHelpBT;
//STRIP001  PushButton      aCreateEntryPB;
//STRIP001  PushButton      aEditEntryPB;
//STRIP001
//STRIP001  String          sChangeST;
//STRIP001  sal_Bool            bNewEntry;
//STRIP001  sal_Bool            bBibAccessInitialized;
//STRIP001
//STRIP001  SwWrtShell*     pSh;
//STRIP001
//STRIP001  String          m_sColumnTitles[AUTH_FIELD_END];
//STRIP001  String          m_sFields[AUTH_FIELD_END];
//STRIP001
//STRIP001  String          m_sCreatedEntry[AUTH_FIELD_END];
//STRIP001
//STRIP001  ::com::sun::star::uno::Reference< ::com::sun::star::container::XNameAccess >    xBibAccess;
//STRIP001
//STRIP001  DECL_LINK(InsertHdl, PushButton*);
//STRIP001  DECL_LINK(CloseHdl, PushButton*);
//STRIP001  DECL_LINK(CreateEntryHdl, PushButton*);
//STRIP001  DECL_LINK(CompEntryHdl, ListBox*);
//STRIP001  DECL_LINK(ChangeSourceHdl, RadioButton*);
//STRIP001  DECL_LINK(IsEntryAllowedHdl, Edit*);
//STRIP001     DECL_LINK(EditModifyHdl, Edit*);
//STRIP001
//STRIP001  void InitControls();
//STRIP001     virtual void    Activate();
//STRIP001 public:
//STRIP001
//STRIP001  SwAuthMarkDlg( Window *pParent,
//STRIP001                  const ResId& rResId,
//STRIP001                  sal_Bool bNew=sal_True);
//STRIP001  ~SwAuthMarkDlg();
//STRIP001
//STRIP001  void    ReInitDlg(SwWrtShell& rWrtShell);
//STRIP001 };
/* -----------------07.09.99 08:02-------------------

 --------------------------------------------------*/
class SwInsertAuthMarkWrapper : public SfxChildWindow
{
protected:
    SwInsertAuthMarkWrapper(    Window *pParentWindow,
                            sal_uInt16 nId,
                            SfxBindings* pBindings,
                            SfxChildWinInfo* pInfo );

    SFX_DECL_CHILDWINDOW(SwInsertAuthMarkWrapper);

public:
//STRIP001  void    ReInitDlg(SwWrtShell& rWrtShell);
};
/* -----------------06.10.99 10:11-------------------

 --------------------------------------------------*/
//STRIP001 class SwAuthMarkFloatDlg : public SfxModelessDialog
//STRIP001 {
//STRIP001  SwAuthMarkDlg       aDlg;
//STRIP001  virtual void    Activate();
//STRIP001  public:
//STRIP001      SwAuthMarkFloatDlg(     SfxBindings* pBindings,
//STRIP001                              SfxChildWindow* pChild,
//STRIP001                              Window *pParent,
//STRIP001                              sal_Bool bNew=sal_True);
//STRIP001
//STRIP001      SwAuthMarkDlg&      GetDlg() {return aDlg;}
//STRIP001 };
/* -----------------06.10.99 10:33-------------------

 --------------------------------------------------*/
//STRIP001 class SwAuthMarkModalDlg : public SvxStandardDialog
//STRIP001 {
//STRIP001  SwAuthMarkDlg       aDlg;
//STRIP001 public:
//STRIP001  SwAuthMarkModalDlg(Window *pParent, SwWrtShell& rSh);
//STRIP001
//STRIP001  SwAuthMarkDlg&      GetDlg() {return aDlg;}
//STRIP001  virtual void        Apply();
//STRIP001 };


} //namespace binfilter
#endif // _IDXMRK_HXX

