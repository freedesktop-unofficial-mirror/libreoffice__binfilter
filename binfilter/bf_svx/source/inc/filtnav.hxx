/*************************************************************************
 *
 *  $RCSfile: filtnav.hxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:22:00 $
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
#ifndef _SVX_FILTNAV_HXX
#define _SVX_FILTNAV_HXX

#ifndef _COM_SUN_STAR_AWT_XTEXTCOMPONENT_HPP_
#include <com/sun/star/awt/XTextComponent.hpp>
#endif
#ifndef _COM_SUN_STAR_FORM_XFORM_HPP_
#include <com/sun/star/form/XForm.hpp>
#endif

#ifndef _SFXLSTNER_HXX //autogen
#include <svtools/lstner.hxx>
#endif

#ifndef _SFXBRDCST_HXX //autogen
#include <svtools/brdcst.hxx>
#endif

#ifndef _SV_WINDOW_HXX //autogen
#include <vcl/window.hxx>
#endif

#ifndef _SFX_CHILDWIN_HXX //autogen
#include <bf_sfx2/childwin.hxx>
#endif

#ifndef _SFXPOOLITEM_HXX //autogen
#include <svtools/poolitem.hxx>
#endif

#ifndef _SFX_BINDINGS_HXX //autogen
#include <bf_sfx2/bindings.hxx>
#endif

#ifndef _SFXDOCKWIN_HXX //autogen
#include <bf_sfx2/dockwin.hxx>
#endif

#ifndef _SFXCTRLITEM_HXX //autogen
#include <bf_sfx2/ctrlitem.hxx>
#endif

#ifndef _SV_IMAGE_HXX
#include <vcl/image.hxx>
#endif

#ifndef _SVTREEBOX_HXX //autogen
#include <svtools/svtreebx.hxx>
#endif

#ifndef _DIALOG_HXX //autogen
#include <vcl/dialog.hxx>
#endif

#ifndef _GROUP_HXX //autogen
#include <vcl/group.hxx>
#endif

#ifndef _SV_DOCKWIN_HXX //autogen
#include <vcl/dockwin.hxx>
#endif

#ifndef _SVX_FMTOOLS_HXX
#include "fmtools.hxx"
#endif
#ifndef _SVX_FMEXCH_HXX
#include "fmexch.hxx"
#endif
#ifndef _CONNECTIVITY_SQLPARSE_HXX
#include <connectivity/sqlparse.hxx>
#endif
#ifndef _SVX_FMEXCH_HXX
#include "fmexch.hxx"
#endif
#ifndef SVX_SQLPARSERCLIENT_HXX
#include "sqlparserclient.hxx"
#endif

class FmFormShell;

//........................................................................
namespace svxform
{
//........................................................................

class FmFilterItem;
class FmFilterItems;
//STRIP001 class FmParentData;
class FmFilterAdapter;

//========================================================================
// data structure for the filter model
//========================================================================
//STRIP001 class FmFilterData
//STRIP001 {
//STRIP001  ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory > m_xORB;
//STRIP001  FmParentData*           m_pParent;
//STRIP001  ::rtl::OUString         m_aText;
//STRIP001
//STRIP001 public:
//STRIP001  TYPEINFO();
//STRIP001  FmFilterData(const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >& _rxFactory,FmParentData* pParent = NULL, const ::rtl::OUString& rText = ::rtl::OUString())
//STRIP001      :m_pParent(pParent)
//STRIP001      ,m_aText(rText)
//STRIP001      ,m_xORB()
//STRIP001  {}
//STRIP001  virtual ~FmFilterData(){}
//STRIP001
//STRIP001  void    SetText( const ::rtl::OUString& rText ){ m_aText = rText; }
//STRIP001  ::rtl::OUString  GetText() const { return m_aText; }
//STRIP001  FmParentData* GetParent() const {return m_pParent;}
//STRIP001
//STRIP001  virtual Image GetImage( BmpColorMode _eMode = BMP_COLOR_NORMAL ) const;
//STRIP001 };

//========================================================================
//STRIP001 class FmParentData : public FmFilterData
//STRIP001 {
//STRIP001 protected:
//STRIP001  vector<FmFilterData*> m_aChilds;
//STRIP001
//STRIP001
//STRIP001 public:
//STRIP001  TYPEINFO();
//STRIP001  FmParentData(const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >& _rxFactory,FmParentData* pParent, const ::rtl::OUString& rText)
//STRIP001      : FmFilterData(_rxFactory,pParent, rText)
//STRIP001  {}
//STRIP001  virtual ~FmParentData();
//STRIP001
//STRIP001  vector<FmFilterData*>& GetChilds() {return m_aChilds;}
//STRIP001 };

//========================================================================
// Item representing the forms and subforms
//STRIP001 class FmFormItem : public FmParentData
//STRIP001 {
//STRIP001  ::com::sun::star::uno::Reference< ::com::sun::star::form::XFormController >     m_xController;
//STRIP001  sal_Int32           m_nCurrent;
//STRIP001
//STRIP001 public:
//STRIP001  TYPEINFO();
//STRIP001  FmFormItem(const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >& _rxFactory):FmParentData(_rxFactory,NULL, ::rtl::OUString()){}
//STRIP001  FmFormItem(const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >& _rxFactory,FmParentData* _pParent,
//STRIP001               const ::com::sun::star::uno::Reference< ::com::sun::star::form::XFormController > & _xController,
//STRIP001               const ::rtl::OUString& _rText):FmParentData(_rxFactory,_pParent, _rText)
//STRIP001                                   ,m_xController(_xController)
//STRIP001                                   ,m_nCurrent(0){}
//STRIP001
//STRIP001  const ::com::sun::star::uno::Reference< ::com::sun::star::form::XFormController > & GetController(){return m_xController;}
//STRIP001  void SetCurrentPosition(sal_Int32 nCurrent){m_nCurrent = nCurrent;}
//STRIP001  sal_Int32 GetCurrentPosition() const {return m_nCurrent;}
//STRIP001  virtual Image GetImage( BmpColorMode _eMode = BMP_COLOR_NORMAL ) const;
//STRIP001 };

//========================================================================
//STRIP001 class FmFilterItems : public FmParentData
//STRIP001 {
//STRIP001 public:
//STRIP001  TYPEINFO();
//STRIP001  FmFilterItems(const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >& _rxFactory):FmParentData(_rxFactory,NULL, ::rtl::OUString()){}
//STRIP001  FmFilterItems(const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >& _rxFactory,FmFormItem* pParent, const ::rtl::OUString& rText ):FmParentData(_rxFactory,pParent, rText){}
//STRIP001
//STRIP001  FmFilterItem* Find(const ::com::sun::star::uno::Reference< ::com::sun::star::awt::XTextComponent > & xText) const;
//STRIP001  virtual Image GetImage( BmpColorMode _eMode = BMP_COLOR_NORMAL ) const;
//STRIP001 };

//========================================================================
//STRIP001 class FmFilterItem : public FmFilterData
//STRIP001 {
//STRIP001  ::rtl::OUString m_aFieldName;
//STRIP001  ::com::sun::star::uno::Reference< ::com::sun::star::awt::XTextComponent > m_xText;
//STRIP001
//STRIP001 public:
//STRIP001  TYPEINFO();
//STRIP001  FmFilterItem(const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >& _rxFactory,
//STRIP001              FmFilterItems* pParent,
//STRIP001            const ::rtl::OUString& aFieldName,
//STRIP001            const ::rtl::OUString& aCondition,
//STRIP001            const ::com::sun::star::uno::Reference< ::com::sun::star::awt::XTextComponent > & xText);
//STRIP001
//STRIP001  const ::rtl::OUString& GetFieldName() const {return m_aFieldName;}
//STRIP001  const ::com::sun::star::uno::Reference< ::com::sun::star::awt::XTextComponent > & GetTextComponent() const {return m_xText;}
//STRIP001
//STRIP001  virtual Image GetImage( BmpColorMode _eMode = BMP_COLOR_NORMAL ) const;
//STRIP001 };

//========================================================================
//STRIP001 class FmFilterModel : public FmParentData
//STRIP001                   ,public SfxBroadcaster
//STRIP001                   ,public ::svxform::OSQLParserClient
//STRIP001 {
//STRIP001  friend class FmFilterAdapter;
//STRIP001
//STRIP001  ::com::sun::star::uno::Reference< ::com::sun::star::container::XIndexAccess >       m_xControllers;
//STRIP001  ::com::sun::star::uno::Reference< ::com::sun::star::form::XFormController >         m_xController;
//STRIP001  ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >    m_xORB;
//STRIP001  FmFilterAdapter*        m_pAdapter;
//STRIP001  FmFilterItems*          m_pCurrentItems;
//STRIP001
//STRIP001 public:
//STRIP001  TYPEINFO();
//STRIP001  FmFilterModel(const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >& _rxFactory);
//STRIP001  virtual ~FmFilterModel();
//STRIP001
//STRIP001  void Update(const ::com::sun::star::uno::Reference< ::com::sun::star::container::XIndexAccess > & xControllers, const ::com::sun::star::uno::Reference< ::com::sun::star::form::XFormController > & xCurrent);
//STRIP001  void Clear();
//STRIP001  sal_Bool ValidateText(FmFilterItem* pItem, UniString& rText, UniString& rErrorMsg) const;
//STRIP001  void Append(FmFilterItems* pItems, FmFilterItem* pFilterItem);
//STRIP001  void SetText(FmFilterItem* pItem, const ::rtl::OUString& rText);
//STRIP001
//STRIP001  FmFormItem* GetCurrentForm() const {return m_pCurrentItems ? (FmFormItem*)m_pCurrentItems->GetParent() : NULL;}
//STRIP001  FmFilterItems* GetCurrentItems() const {return m_pCurrentItems;}
//STRIP001  void SetCurrentItems(FmFilterItems* pCurrent);
//STRIP001  ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory > getORB() const { return m_xORB; }
//STRIP001
//STRIP001  const ::com::sun::star::uno::Reference< ::com::sun::star::container::XIndexAccess > & GetControllers() const {return m_xControllers;}
//STRIP001  const ::com::sun::star::uno::Reference< ::com::sun::star::form::XFormController > & GetCurrentController() const {return m_xController;}
//STRIP001  void SetCurrentController(const ::com::sun::star::uno::Reference< ::com::sun::star::form::XFormController > & xController);
//STRIP001
//STRIP001  void Remove(FmFilterData* pFilterItem);
//STRIP001  void AppendFilterItems(FmFormItem* pItem);
//STRIP001  void CheckIntegrity(FmParentData* pItem);
//STRIP001
//STRIP001 protected:
//STRIP001  void Insert(const vector<FmFilterData*>::iterator& rPos, FmFilterData* pFilterItem);
//STRIP001  void Remove(const vector<FmFilterData*>::iterator& rPos, FmFilterData* pFilterItem);
//STRIP001  FmFormItem* Find(const ::std::vector<FmFilterData*>& rItems, const ::com::sun::star::uno::Reference< ::com::sun::star::form::XFormController > & xController) const;
//STRIP001  FmFormItem* Find(const ::std::vector<FmFilterData*>& rItems, const ::com::sun::star::uno::Reference< ::com::sun::star::form::XForm >& xForm) const;
//STRIP001  void Update(const ::com::sun::star::uno::Reference< ::com::sun::star::container::XIndexAccess > & xControllers, FmParentData* pParent);
//STRIP001 };

//========================================================================
//========================================================================
//STRIP001 class OFilterItemExchange : public OLocalExchange
//STRIP001 {
//STRIP001  vector<FmFilterItem*>   m_aDraggedEntries;
//STRIP001  FmFormItem*             m_pFormItem;        // ensure that we drop on the same form
//STRIP001
//STRIP001 public:
//STRIP001  OFilterItemExchange();
//STRIP001
//STRIP001  static sal_uInt32       getFormatId( );
//STRIP001  inline static sal_Bool  hasFormat( const DataFlavorExVector& _rFormats );
//STRIP001
//STRIP001  const vector<FmFilterItem*>& getDraggedEntries() const { return m_aDraggedEntries; }
//STRIP001  void setDraggedEntries(const vector<FmFilterItem*>& _rList) { m_aDraggedEntries = _rList; }
//STRIP001  FmFormItem* getFormItem() const { return m_pFormItem; }
//STRIP001
//STRIP001  void setFormItem( FmFormItem* _pItem ) { m_pFormItem = _pItem; }
//STRIP001  void addSelectedItem( FmFilterItem* _pItem) { m_aDraggedEntries.push_back(_pItem); }
//STRIP001
//STRIP001 protected:
//STRIP001  virtual void AddSupportedFormats();
//STRIP001 };

//STRIP001 inline sal_Bool OFilterItemExchange::hasFormat( const DataFlavorExVector& _rFormats )
//STRIP001 {
//STRIP001  return OLocalExchange::hasFormat( _rFormats, getFormatId() );
//STRIP001 }

//====================================================================
//= OFilterExchangeHelper
//====================================================================
//STRIP001 class OFilterExchangeHelper : public OLocalExchangeHelper
//STRIP001 {
//STRIP001 public:
//STRIP001  OFilterExchangeHelper(Window* _pDragSource) : OLocalExchangeHelper(_pDragSource) { }
//STRIP001
//STRIP001  OFilterItemExchange* operator->() const { return static_cast<OFilterItemExchange*>(m_pTransferable); }
//STRIP001
//STRIP001 protected:
//STRIP001  virtual OLocalExchange* createExchange() const;
//STRIP001 };

//========================================================================
//STRIP001 class FmFilterNavigator : public SvTreeListBox, public SfxListener
//STRIP001 {
//STRIP001  enum DROP_ACTION{ DA_SCROLLUP, DA_SCROLLDOWN, DA_EXPANDNODE };
//STRIP001
//STRIP001  FmFilterModel*          m_pModel;
//STRIP001  SvLBoxEntry*            m_pEditingCurrently;
//STRIP001  OFilterExchangeHelper   m_aControlExchange;
//STRIP001
//STRIP001
//STRIP001  AutoTimer           m_aDropActionTimer;
//STRIP001  unsigned short      m_aTimerCounter;
//STRIP001  Point               m_aTimerTriggered;      // die Position, an der der DropTimer angeschaltet wurde
//STRIP001  DROP_ACTION         m_aDropActionType;
//STRIP001
//STRIP001 public:
//STRIP001  FmFilterNavigator( Window* pParent );
//STRIP001  virtual ~FmFilterNavigator();
//STRIP001
//STRIP001  void Update(const ::com::sun::star::uno::Reference< ::com::sun::star::container::XIndexAccess > & xControllers, const ::com::sun::star::uno::Reference< ::com::sun::star::form::XFormController > & xCurrent);
//STRIP001  FmFilterModel* const GetFilterModel() const {return m_pModel;}
//STRIP001
//STRIP001 protected:
//STRIP001  virtual void KeyInput( const KeyEvent& rKEvt );
//STRIP001  virtual void Command( const CommandEvent& rEvt );
//STRIP001  virtual void Notify( SfxBroadcaster& rBC, const SfxHint& rHint );
//STRIP001  virtual void InitEntry(SvLBoxEntry* pEntry, const XubString& rStr, const Image& rImg1, const Image& rImg2);
//STRIP001  virtual sal_Bool Select( SvLBoxEntry* pEntry, sal_Bool bSelect=sal_True );
//STRIP001  virtual sal_Bool EditingEntry( SvLBoxEntry* pEntry, Selection& rSelection );
//STRIP001  virtual sal_Bool EditedEntry( SvLBoxEntry* pEntry, const XubString& rNewText );
//STRIP001
//STRIP001  virtual sal_Int8    AcceptDrop( const AcceptDropEvent& rEvt );
//STRIP001  virtual sal_Int8    ExecuteDrop( const ExecuteDropEvent& rEvt );
//STRIP001  virtual void        StartDrag( sal_Int8 nAction, const Point& rPosPixel );
//STRIP001
//STRIP001  void DeleteSelection();
//STRIP001  void Clear();
//STRIP001  SvLBoxEntry* FindEntry(FmFilterData* pItem);
//STRIP001  void Insert(FmFilterData* pItem, sal_Int32 nPos);
//STRIP001  void Remove(FmFilterData* pItem);
//STRIP001
//STRIP001  DECL_LINK(OnRemove, SvLBoxEntry*);
//STRIP001  DECL_LINK(OnEdited, SvLBoxEntry*);
//STRIP001  DECL_LINK(OnDropActionTimer, void*);
//STRIP001
//STRIP001 private:
//STRIP001  /** returns the first form item and the selected FilterItems in the vector
//STRIP001      @param  _rItemList
//STRIP001          Is filled inside. <OUT/>
//STRIP001      @return
//STRIP001          The first form item.
//STRIP001  */
//STRIP001  FmFormItem* getSelectedFilterItems(::std::vector<FmFilterItem*>& _rItemList);
//STRIP001  /* inserts the filter items into the tree model and creates new FilterItems if needed.
//STRIP001      @param  _rFilterList
//STRIP001          The items which should be inserted.
//STRIP001      @param  _pTargetItems
//STRIP001          The target where to insert the items.
//STRIP001      @param  _bCopy
//STRIP001          If <TRUE/> the items will not be removed from the model, otherwise they will.
//STRIP001  */
//STRIP001  void insertFilterItem(const ::std::vector<FmFilterItem*>& _rFilterList,FmFilterItems* _pTargetItems,sal_Bool _bCopy = sal_False);
//STRIP001  SvLBoxEntry* getPrevEntry(SvLBoxEntry* _pStartWith = NULL);
//STRIP001  SvLBoxEntry* getNextEntry(SvLBoxEntry* _pStartWith = NULL);
//STRIP001 };

//========================================================================
//STRIP001 class FmFilterNavigatorWin : public SfxDockingWindow, public SfxControllerItem
//STRIP001 {
//STRIP001 private:
//STRIP001  FmFilterNavigator* m_pNavigator;
//STRIP001
//STRIP001 protected:
//STRIP001  virtual void Resize();
//STRIP001  virtual sal_Bool Close();
//STRIP001  virtual Size CalcDockingSize( SfxChildAlignment );
//STRIP001  virtual SfxChildAlignment CheckAlignment( SfxChildAlignment, SfxChildAlignment );
//STRIP001
//STRIP001 public:
//STRIP001  FmFilterNavigatorWin( SfxBindings *pBindings, SfxChildWindow *pMgr,
//STRIP001                 Window* pParent );
//STRIP001  virtual ~FmFilterNavigatorWin();
//STRIP001
//STRIP001  void Update( FmFormShell* pFormShell );
//STRIP001  void StateChanged( sal_uInt16 nSID, SfxItemState eState, const SfxPoolItem* pState );
//STRIP001  void FillInfo( SfxChildWinInfo& rInfo ) const;
//STRIP001
//STRIP001  virtual void GetFocus();
//STRIP001 };

//========================================================================
class FmFilterNavigatorWinMgr : public SfxChildWindow
{
public:
    FmFilterNavigatorWinMgr( Window *pParent, sal_uInt16 nId, SfxBindings *pBindings,
                      SfxChildWinInfo *pInfo );
    SFX_DECL_CHILDWINDOW( FmFilterNavigatorWinMgr );
};

//........................................................................
}   // namespace svxform
//........................................................................

#endif // _SVX_FILTNAV_HXX

