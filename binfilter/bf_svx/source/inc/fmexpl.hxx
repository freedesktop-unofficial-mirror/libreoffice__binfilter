/*************************************************************************
 *
 *  $RCSfile: fmexpl.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 15:56:28 $
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
#ifndef _SVX_FMEXPL_HXX
#define _SVX_FMEXPL_HXX

// auto strip #ifndef _SFXLSTNER_HXX //autogen
// auto strip #include <svtools/lstner.hxx>
// auto strip #endif

// auto strip #ifndef _SFXBRDCST_HXX //autogen
// auto strip #include <svtools/brdcst.hxx>
// auto strip #endif

// auto strip #ifndef _SV_WINDOW_HXX //autogen
// auto strip #include <vcl/window.hxx>
// auto strip #endif

// auto strip #ifndef _SFX_CHILDWIN_HXX //autogen
// auto strip #include <bf_sfx2/childwin.hxx>
// auto strip #endif

// auto strip #ifndef _SFXPOOLITEM_HXX //autogen
// auto strip #include <svtools/poolitem.hxx>
// auto strip #endif

// auto strip #ifndef _SFX_BINDINGS_HXX //autogen
// auto strip #include <bf_sfx2/bindings.hxx>
// auto strip #endif

#ifndef _SFXDOCKWIN_HXX //autogen
#include <bf_sfx2/dockwin.hxx>
#endif

// auto strip #ifndef _SFXCTRLITEM_HXX //autogen
// auto strip #include <bf_sfx2/ctrlitem.hxx>
// auto strip #endif

// auto strip #ifndef _SV_IMAGE_HXX
// auto strip #include <vcl/image.hxx>
// auto strip #endif

// auto strip #ifndef _COM_SUN_STAR_CONTAINER_XNAMECONTAINER_HPP_
// auto strip #include <com/sun/star/container/XNameContainer.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_FORM_XFORM_HPP_
// auto strip #include <com/sun/star/form/XForm.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_FORM_XFORMCOMPONENT_HPP_
// auto strip #include <com/sun/star/form/XFormComponent.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_BEANS_PROPERTYCHANGEEVENT_HPP_
// auto strip #include <com/sun/star/beans/PropertyChangeEvent.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_CONTAINER_XCONTAINERLISTENER_HPP_
// auto strip #include <com/sun/star/container/XContainerListener.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_CONTAINER_XCONTAINER_HPP_
// auto strip #include <com/sun/star/container/XContainer.hpp>
// auto strip #endif


// auto strip #ifndef _SVTREEBOX_HXX //autogen
// auto strip #include <svtools/svtreebx.hxx>
// auto strip #endif

// auto strip #ifndef _DIALOG_HXX //autogen
// auto strip #include <vcl/dialog.hxx>
// auto strip #endif

// auto strip #ifndef _GROUP_HXX //autogen
// auto strip #include <vcl/group.hxx>
// auto strip #endif

// auto strip #ifndef _BUTTON_HXX //autogen
// auto strip #include <vcl/button.hxx>
// auto strip #endif

// auto strip #ifndef _FIXED_HXX //autogen
// auto strip #include <vcl/fixed.hxx>
// auto strip #endif

// auto strip #ifndef _EDIT_HXX //autogen
// auto strip #include <vcl/edit.hxx>
// auto strip #endif

// auto strip #ifndef _SV_DOCKWIN_HXX //autogen
// auto strip #include <vcl/dockwin.hxx>
// auto strip #endif

#ifndef _SVX_FMVIEW_HXX
#include "fmview.hxx"
#endif

// auto strip #include "fmexch.hxx"

// auto strip #ifndef _SVX_FMTOOLS_HXX
// auto strip #include "fmtools.hxx"
// auto strip #endif
class SdrObjListIter;
namespace binfilter {

class FmFormShell;
class SdrObject;
class FmFormModel;

//========================================================================
//STRIP001 class FmEntryData;
//STRIP001 class FmNavInsertedHint : public SfxHint
//STRIP001 {
//STRIP001  FmEntryData* pEntryData;
//STRIP001  sal_uInt32 nPos;
//STRIP001
//STRIP001 public:
//STRIP001  TYPEINFO();
//STRIP001  FmNavInsertedHint( FmEntryData* pInsertedEntryData, sal_uInt32 nRelPos );
//STRIP001  virtual ~FmNavInsertedHint();
//STRIP001
//STRIP001  FmEntryData* GetEntryData() const { return pEntryData; }
//STRIP001  sal_uInt32 GetRelPos() const { return nPos; }
//STRIP001 };

//========================================================================
//STRIP001 class FmNavModelReplacedHint : public SfxHint
//STRIP001 {
//STRIP001  FmEntryData* pEntryData;    // die Daten des Eintrages, der ein neues Model bekommen hat
//STRIP001
//STRIP001 public:
//STRIP001  TYPEINFO();
//STRIP001  FmNavModelReplacedHint( FmEntryData* pAffectedEntryData );
//STRIP001  virtual ~FmNavModelReplacedHint();
//STRIP001
//STRIP001  FmEntryData* GetEntryData() const { return pEntryData; }
//STRIP001 };

//========================================================================
//STRIP001 class FmNavRemovedHint : public SfxHint
//STRIP001 {
//STRIP001  FmEntryData* pEntryData;
//STRIP001
//STRIP001 public:
//STRIP001  TYPEINFO();
//STRIP001  FmNavRemovedHint( FmEntryData* pInsertedEntryData );
//STRIP001  virtual ~FmNavRemovedHint();
//STRIP001
//STRIP001  FmEntryData* GetEntryData() const { return pEntryData; }
//STRIP001 };

//========================================================================
//STRIP001 class FmNavNameChangedHint : public SfxHint
//STRIP001 {
//STRIP001  FmEntryData*    pEntryData;
//STRIP001  ::rtl::OUString          aNewName;
//STRIP001
//STRIP001 public:
//STRIP001  TYPEINFO();
//STRIP001  FmNavNameChangedHint( FmEntryData* pData, const ::rtl::OUString& rNewName );
//STRIP001  virtual ~FmNavNameChangedHint();
//STRIP001
//STRIP001  FmEntryData*    GetEntryData() const { return pEntryData; }
//STRIP001  ::rtl::OUString          GetNewName() const { return aNewName; }
//STRIP001 };

//========================================================================
//STRIP001 class FmNavClearedHint : public SfxHint
//STRIP001 {
//STRIP001 public:
//STRIP001  TYPEINFO();
//STRIP001  FmNavClearedHint();
//STRIP001  virtual ~FmNavClearedHint();
//STRIP001 };

//========================================================================
class FmNavViewMarksChanged : public SfxHint
{
    FmFormView* pView;
public:
//STRIP001  TYPEINFO();
    FmNavViewMarksChanged(FmFormView* pWhichView) { pView = pWhichView; }
    virtual ~FmNavViewMarksChanged() {}

//STRIP001  FmFormView* GetAffectedView() { return pView; }
};

//========================================================================
//STRIP001 class FmEntryDataList;
//STRIP001 class FmEntryData
//STRIP001 {
//STRIP001 private:
//STRIP001  ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface >       m_xNormalizedIFace;
//STRIP001  ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet >   m_xProperties;
//STRIP001  ::com::sun::star::uno::Reference< ::com::sun::star::container::XChild >     m_xChild;
//STRIP001
//STRIP001 protected:
//STRIP001  Image               m_aNormalImage;
//STRIP001  Image               m_aHCImage;
//STRIP001  ::rtl::OUString     aText;
//STRIP001
//STRIP001  FmEntryDataList*    pChildList;
//STRIP001  FmEntryData*        pParent;
//STRIP001
//STRIP001 protected:
//STRIP001  void    newObject( const ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface >& _rxIFace );
//STRIP001
//STRIP001 public:
//STRIP001  TYPEINFO();
//STRIP001
//STRIP001  FmEntryData( FmEntryData* pParentData, const ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface >& _rIFace );
//STRIP001  FmEntryData( const FmEntryData& rEntryData );
//STRIP001  virtual ~FmEntryData();
//STRIP001
//STRIP001  void    Clear();
//STRIP001  void    SetText( const ::rtl::OUString& rText ){ aText = rText; }
//STRIP001  void    SetParent( FmEntryData* pParentData ){ pParent = pParentData; }
//STRIP001
//STRIP001  const Image&    GetNormalImage() const { return m_aNormalImage; }
//STRIP001  const Image&    GetHCImage() const { return m_aHCImage; }
//STRIP001
//STRIP001  ::rtl::OUString          GetText() const { return aText; }
//STRIP001  FmEntryData*    GetParent() const { return pParent; }
//STRIP001  FmEntryDataList* GetChildList() const { return pChildList; }
//STRIP001
//STRIP001  virtual sal_Bool IsEqualWithoutChilds( FmEntryData* pEntryData );
//STRIP001  virtual FmEntryData* Clone() = 0;
//STRIP001
//STRIP001  // note that the interface returned is normalized, i.e. querying the given XInterface of the object
//STRIP001  // for XInterface must return the interface itself.
//STRIP001  const ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface >& GetElement() const
//STRIP001  {
//STRIP001      return m_xNormalizedIFace;
//STRIP001  }
//STRIP001
//STRIP001  const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet >& GetPropertySet() const
//STRIP001  {
//STRIP001      return m_xProperties;
//STRIP001  }
//STRIP001
//STRIP001  const ::com::sun::star::uno::Reference< ::com::sun::star::container::XChild >& GetChildIFace() const
//STRIP001  {
//STRIP001      return m_xChild;
//STRIP001  }
//STRIP001 };

//========================================================================
//STRIP001 DECLARE_LIST( FmEntryDataBaseList, FmEntryData* ) //STRIP008 DECLARE_LIST( FmEntryDataBaseList, FmEntryData* );

//STRIP001 class FmEntryDataList : public FmEntryDataBaseList
//STRIP001 {
//STRIP001 public:
//STRIP001  FmEntryDataList();
//STRIP001  virtual ~FmEntryDataList();
//STRIP001 };

//========================================================================
// FmNavRequestSelectHint - jemand teilt dem NavigatorTree mit, dass er bestimmte Eintraege selektieren soll

//STRIP001 typedef FmEntryData* FmEntryDataPtr;
//STRIP001 SV_DECL_PTRARR_SORT( FmEntryDataArray, FmEntryDataPtr, 16, 16 )

//STRIP001 class FmNavRequestSelectHint : public SfxHint
//STRIP001 {
//STRIP001  FmEntryDataArray    m_arredToSelect;
//STRIP001  sal_Bool                m_bMixedSelection;
//STRIP001 public:
//STRIP001  TYPEINFO();
//STRIP001  FmNavRequestSelectHint() { }
//STRIP001  virtual ~FmNavRequestSelectHint() {}
//STRIP001
//STRIP001  void SetMixedSelection(sal_Bool bMixedSelection) { m_bMixedSelection = bMixedSelection; }
//STRIP001  sal_Bool IsMixedSelection() { return m_bMixedSelection; }
//STRIP001  void AddItem(FmEntryData* pEntry) { m_arredToSelect.Insert(pEntry); }
//STRIP001  void ClearItems() { m_arredToSelect.Remove(sal_uInt16(0), m_arredToSelect.Count()); }
//STRIP001  FmEntryDataArray& GetItems() { return m_arredToSelect; }
//STRIP001 };

//========================================================================
//STRIP001 class FmFormData : public FmEntryData
//STRIP001 {
//STRIP001  ::com::sun::star::uno::Reference< ::com::sun::star::form::XForm >           m_xForm;
//STRIP001  ::com::sun::star::uno::Reference< ::com::sun::star::container::XContainer > m_xContainer;
//STRIP001
//STRIP001 public:
//STRIP001  TYPEINFO();
//STRIP001
//STRIP001  FmFormData(
//STRIP001      const ::com::sun::star::uno::Reference< ::com::sun::star::form::XForm >& _rxForm,
//STRIP001      const ImageList& _rNormalImages,
//STRIP001      const ImageList& _rHCImages,
//STRIP001      FmFormData* _pParent = NULL
//STRIP001  );
//STRIP001
//STRIP001  FmFormData( const FmFormData& rFormData );
//STRIP001  virtual ~FmFormData();
//STRIP001
//STRIP001  void SetForm( const ::com::sun::star::uno::Reference< ::com::sun::star::form::XForm >& xForm )
//STRIP001  {
//STRIP001      m_xForm = xForm;
//STRIP001      m_xContainer = m_xContainer.query( m_xForm );
//STRIP001      newObject( m_xForm );
//STRIP001  }
//STRIP001
//STRIP001  const ::com::sun::star::uno::Reference< ::com::sun::star::form::XForm >& GetFormIface() const { return m_xForm; }
//STRIP001  const ::com::sun::star::uno::Reference< ::com::sun::star::container::XContainer >& GetContainer() const { return m_xContainer; }
//STRIP001
//STRIP001  virtual sal_Bool IsEqualWithoutChilds( FmEntryData* pEntryData );
//STRIP001  virtual FmEntryData* Clone();
//STRIP001 };


//========================================================================
//STRIP001 class FmControlData : public FmEntryData
//STRIP001 {
//STRIP001  ::com::sun::star::uno::Reference< ::com::sun::star::form::XFormComponent >  m_xFormComponent;
//STRIP001
//STRIP001  Image GetImage(const ImageList& ilNavigatorImages) const;
//STRIP001
//STRIP001 public:
//STRIP001  TYPEINFO();
//STRIP001
//STRIP001  FmControlData(
//STRIP001      const ::com::sun::star::uno::Reference< ::com::sun::star::form::XFormComponent >& _rxComponent,
//STRIP001      const ImageList& _rNormalImages,
//STRIP001      const ImageList& _rHCImages,
//STRIP001      FmFormData* _pParent
//STRIP001  );
//STRIP001  FmControlData( const FmControlData& rControlData );
//STRIP001  virtual ~FmControlData();
//STRIP001
//STRIP001  const ::com::sun::star::uno::Reference< ::com::sun::star::form::XFormComponent >& GetFormComponent() const { return m_xFormComponent; }
//STRIP001  virtual sal_Bool IsEqualWithoutChilds( FmEntryData* pEntryData );
//STRIP001  virtual FmEntryData* Clone();
//STRIP001
//STRIP001  void ModelReplaced(
//STRIP001      const ::com::sun::star::uno::Reference< ::com::sun::star::form::XFormComponent >& _rxNew,
//STRIP001      const ImageList& _rNormalImages,
//STRIP001      const ImageList& _rHCImages
//STRIP001  );
//STRIP001 };


//========================================================================
//............................................................................
namespace svxform
{
//............................................................................

//STRIP001  class NavigatorTreeModel;
    //========================================================================
    // class OFormComponentObserver
    //========================================================================
//STRIP001  class OFormComponentObserver
//STRIP001      :public ::cppu::WeakImplHelper2 <   ::com::sun::star::beans::XPropertyChangeListener
//STRIP001                                      ,   ::com::sun::star::container::XContainerListener
//STRIP001                                      >
//STRIP001  {
//STRIP001      ::svxform::NavigatorTreeModel*  m_pNavModel;
//STRIP001      sal_uInt32 m_nLocks;
//STRIP001      sal_Bool   m_bCanUndo;
//STRIP001
//STRIP001  public:
//STRIP001      OFormComponentObserver( ::svxform::NavigatorTreeModel* pModel );
//STRIP001
//STRIP001  // XEventListenerListener
//STRIP001      virtual void SAL_CALL disposing(const ::com::sun::star::lang::EventObject& Source) throw(::com::sun::star::uno::RuntimeException);
//STRIP001
//STRIP001  // ::com::sun::star::beans::XPropertyChangeListener
//STRIP001      virtual void SAL_CALL propertyChange(const ::com::sun::star::beans::PropertyChangeEvent& evt) throw(::com::sun::star::uno::RuntimeException);
//STRIP001
//STRIP001  // ::com::sun::star::container::XContainerListener
//STRIP001
//STRIP001      virtual void SAL_CALL elementInserted(const  ::com::sun::star::container::ContainerEvent& rEvent) throw(::com::sun::star::uno::RuntimeException);
//STRIP001      virtual void SAL_CALL elementReplaced(const  ::com::sun::star::container::ContainerEvent& rEvent) throw(::com::sun::star::uno::RuntimeException);
//STRIP001      virtual void SAL_CALL elementRemoved(const  ::com::sun::star::container::ContainerEvent& rEvent) throw(::com::sun::star::uno::RuntimeException);
//STRIP001
//STRIP001      void Lock() { m_nLocks++; }
//STRIP001      void UnLock() { m_nLocks--; }
//STRIP001      sal_Bool IsLocked() const { return m_nLocks != 0; }
//STRIP001      sal_Bool CanUndo() const { return m_bCanUndo; }
//STRIP001      void ReleaseModel() { m_pNavModel = NULL; }
//STRIP001  protected:
//STRIP001      void Insert(const ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface >& xIface, sal_Int32 nIndex);
//STRIP001      void Remove( const ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface >& _rxElement );
//STRIP001  };

    //========================================================================
    //= NavigatorTreeModel
    //========================================================================
//STRIP001  class NavigatorTreeModel : public SfxBroadcaster
//STRIP001                         ,public SfxListener
//STRIP001  {
//STRIP001      friend class NavigatorTree;
//STRIP001      friend class OFormComponentObserver;
//STRIP001
//STRIP001      FmEntryDataList*            m_pRootList;
//STRIP001      FmFormShell*                m_pFormShell;
//STRIP001      FmFormPage*                 m_pFormPage;
//STRIP001      FmFormModel*                m_pFormModel;
//STRIP001      OFormComponentObserver*     m_pPropChangeList;
//STRIP001
//STRIP001      ImageList                   m_aNormalImages;
//STRIP001      ImageList                   m_aHCImages;
//STRIP001
//STRIP001      void Update( const ::com::sun::star::uno::Reference< ::com::sun::star::container::XNameContainer >& xForms );
//STRIP001      FmControlData* CreateControlData( ::com::sun::star::form::XFormComponent* pFormComponent );
//STRIP001
//STRIP001      void InsertForm(const ::com::sun::star::uno::Reference< ::com::sun::star::form::XForm >& xForm, sal_uInt32 nRelPos);
//STRIP001      void RemoveForm(FmFormData* pFormData);
//STRIP001
//STRIP001      void InsertFormComponent(const ::com::sun::star::uno::Reference< ::com::sun::star::form::XFormComponent >& xComp, sal_uInt32 nRelPos);
//STRIP001      void RemoveFormComponent(FmControlData* pControlData);
//STRIP001      void InsertSdrObj(const SdrObject* pSdrObj);
//STRIP001      void RemoveSdrObj(const SdrObject* pSdrObj);
//STRIP001
//STRIP001      void ReplaceFormComponent(const ::com::sun::star::uno::Reference< ::com::sun::star::form::XFormComponent >& xOld, const ::com::sun::star::uno::Reference< ::com::sun::star::form::XFormComponent >& xNew);
//STRIP001
//STRIP001      void BroadcastMarkedObjects(const SdrMarkList& mlMarked);
//STRIP001          // einen RequestSelectHint mit den aktuell markierten Objekten broadcasten
//STRIP001      sal_Bool InsertFormComponent(FmNavRequestSelectHint& rHint, SdrObject* pObject);
//STRIP001          // ist ein Helper fuer vorherige, managet das Abteigen in SdrObjGroups
//STRIP001          // Rueckgabe sal_True, wenn das Objekt eine FormComponent ist (oder rekursiv nur aus solchen besteht)
//STRIP001
//STRIP001  public:
//STRIP001      NavigatorTreeModel( const ImageList& _rNormalImages, const ImageList& _rHCImages );
//STRIP001      virtual ~NavigatorTreeModel();
//STRIP001
//STRIP001      void FillBranch( FmFormData* pParentData );
//STRIP001      void ClearBranch( FmFormData* pParentData );
//STRIP001      void Update( FmFormShell* pNewShell );
//STRIP001
//STRIP001      void Insert( FmEntryData* pEntryData, sal_uInt32 nRelPos = LIST_APPEND,
//STRIP001                                            sal_Bool bAlterModel = sal_False );
//STRIP001      void Remove( FmEntryData* pEntryData, sal_Bool bAlterModel = sal_False );
//STRIP001
//STRIP001      sal_Bool Rename( FmEntryData* pEntryData, const ::rtl::OUString& rNewText );
//STRIP001      sal_Bool IsNameAlreadyDefined( const ::rtl::OUString& rName, FmFormData* pParentData );
//STRIP001      void Clear();
//STRIP001      sal_Bool CheckEntry( FmEntryData* pEntryData );
//STRIP001      void SetModified( sal_Bool bMod=sal_True );
//STRIP001
//STRIP001      ::com::sun::star::uno::Reference< ::com::sun::star::container::XNameContainer >    GetForms() const;
//STRIP001      FmFormShell*        GetFormShell() const { return m_pFormShell; }
//STRIP001      FmFormPage*         GetFormPage() const { return m_pFormPage; }
//STRIP001      FmEntryData*        FindData( const ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface >& xElement, FmEntryDataList* pDataList, sal_Bool bRecurs=sal_True );
//STRIP001      FmEntryData*        FindData( const ::rtl::OUString& rText, FmFormData* pParentData, sal_Bool bRecurs=sal_True );
//STRIP001      FmEntryDataList*    GetRootList() const { return m_pRootList; }
//STRIP001      ::com::sun::star::uno::Reference< ::com::sun::star::container::XIndexContainer >   GetFormComponents( FmFormData* pParentFormData );
//STRIP001      SdrObject*          GetSdrObj( FmControlData* pControlData );
//STRIP001      SdrObject*          Search(SdrObjListIter& rIter, const ::com::sun::star::uno::Reference< ::com::sun::star::form::XFormComponent >& xComp);
//STRIP001
//STRIP001      virtual void Notify( SfxBroadcaster& rBC, const SfxHint& rHint );
//STRIP001  };

    //========================================================================
//STRIP001  typedef SvLBoxEntry* SvLBoxEntryPtr;
//STRIP001  SV_DECL_PTRARR_SORT( SvLBoxEntrySortedArray, SvLBoxEntryPtr, 16, 16 )

//STRIP001  class NavigatorTree : public SvTreeListBox, public SfxListener
//STRIP001  {
//STRIP001      enum DROP_ACTION        { DA_SCROLLUP, DA_SCROLLDOWN, DA_EXPANDNODE };
//STRIP001      enum SELDATA_ITEMS      { SDI_DIRTY, SDI_ALL, SDI_NORMALIZED, SDI_NORMALIZED_FORMARK };
//STRIP001
//STRIP001      // beim Droppen will ich scrollen und Folder aufklappen koennen, dafuer :
//STRIP001      AutoTimer           m_aDropActionTimer;
//STRIP001      Timer               m_aSynchronizeTimer;
//STRIP001      // die Meta-Daten ueber meine aktuelle Selektion
//STRIP001      SvLBoxEntrySortedArray  m_arrCurrentSelection;
//STRIP001      // the entries which, in the view, are currently marked as "cut" (painted semi-transparent)
//STRIP001      SvLBoxEntrySortedArray  m_aCutEntries;
//STRIP001      // die Images, die ich brauche (und an FormDatas und EntryDatas weiterreiche)
//STRIP001      ImageList           m_aNavigatorImages;
//STRIP001      ImageList           m_aNavigatorImagesHC;
//STRIP001
//STRIP001      ::svxform::OControlExchangeHelper   m_aControlExchange;
//STRIP001
//STRIP001      ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >    m_xORB;
//STRIP001      NavigatorTreeModel*    m_pNavModel;
//STRIP001      SvLBoxEntry*        m_pRootEntry;
//STRIP001      SvLBoxEntry*        m_pEditEntry;
//STRIP001
//STRIP001      sal_uInt32              nEditEvent;
//STRIP001
//STRIP001      SELDATA_ITEMS       m_sdiState;
//STRIP001      Point               m_aTimerTriggered;      // die Position, an der der DropTimer angeschaltet wurde
//STRIP001      DROP_ACTION         m_aDropActionType;
//STRIP001
//STRIP001      sal_uInt16              m_nSelectLock;
//STRIP001      sal_uInt16              m_nFormsSelected;
//STRIP001      sal_uInt16              m_nControlsSelected;
//STRIP001      sal_uInt16              m_nHiddenControls;      // (die Zahl geht in m_nControlsSelected mit ein)
//STRIP001
//STRIP001      unsigned short      m_aTimerCounter;
//STRIP001
//STRIP001      sal_Bool                m_bDragDataDirty        : 1;        // dito
//STRIP001      sal_Bool                m_bPrevSelectionMixed   : 1;
//STRIP001      sal_Bool                m_bMarkingObjects       : 1;  // wenn das sal_True ist, brauche ich auf die RequestSelectHints nicht reagieren
//STRIP001      sal_Bool                m_bRootSelected         : 1;
//STRIP001      sal_Bool                m_bInitialUpdate        : 1;   // bin ich das erste Mal im Update ?
//STRIP001      sal_Bool                m_bKeyboardCut          : 1;
//STRIP001
//STRIP001
//STRIP001      void            Update();
//STRIP001      sal_Bool            IsDeleteAllowed();
//STRIP001      FmControlData*  NewControl( const ::rtl::OUString& rServiceName, SvLBoxEntry* pParentEntry, sal_Bool bEditName = sal_True );
//STRIP001      void            NewForm( SvLBoxEntry* pParentEntry );
//STRIP001      SvLBoxEntry*    Insert( FmEntryData* pEntryData, sal_uInt32 nRelPos=LIST_APPEND );
//STRIP001      void            Remove( FmEntryData* pEntryData );
//STRIP001
//STRIP001
//STRIP001      void CollectSelectionData(SELDATA_ITEMS sdiHow);
//STRIP001          // sammelt in m_arrCurrentSelection die aktuell selektierten Eintraege, normalisiert die Liste wenn verlangt
//STRIP001          // SDI_NORMALIZED bedeutet einfach, dass alle Eintraege, die schon einen selektierten Vorfahren haben, nicht mit gesammelt
//STRIP001          // werden.
//STRIP001          // SDI_NORMALIZED_FORMARK bedeutet, dass wie bei SDI_NORMALIZED verfahren wird, aber Eintraege, deren direktes Elter nicht
//STRIP001          // selektiert ist, aufgenommen werden (unabhaengig vom Status weiterer Vorfahren), desgleichen Formulare, die selektiert sind,
//STRIP001          // unabhaengig vom Status irgendwelcher Vorfahren
//STRIP001          // Bei beiden Normalized-Modi enthalten die m_nFormsSelected, ... die richtige Anzahl, auch wenn nicht alle dieser Eintraege
//STRIP001          // in m_arrCurrentSelection landen.
//STRIP001          // SDI_DIRTY ist natuerlich nicht erlaubt als Parameter
//STRIP001
//STRIP001      // ein einziges Interface fuer alle selektierten Eintraege zusammensetzen
//STRIP001      void    ShowSelectionProperties(sal_Bool bForce = sal_False);
//STRIP001      // alle selektierten Elemnte loeschen
//STRIP001      void    DeleteSelection();
//STRIP001
//STRIP001      void SynchronizeSelection(FmEntryDataArray& arredToSelect);
//STRIP001          // nach dem Aufruf dieser Methode sind genau die Eintraege selektiert, die in dem Array bezeichnet sind
//STRIP001      void SynchronizeSelection();
//STRIP001          // macht das selbe, nimmt die MarkList der ::com::sun::star::sdbcx::View
//STRIP001      void SynchronizeMarkList();
//STRIP001          // umgekehrte Richtung von SynchronizeMarkList : markiert in der ::com::sun::star::sdbcx::View alle der aktuellen Selektion entsprechenden Controls
//STRIP001
//STRIP001      // im Select aktualisiere ich normalerweise die Marklist der zugehoerigen ::com::sun::star::sdbcx::View, mit folgenden Funktionen
//STRIP001      // kann ich das Locking dieses Verhaltens steuern
//STRIP001      void LockSelectionHandling() { ++m_nSelectLock; }
//STRIP001      void UnlockSelectionHandling() { --m_nSelectLock; }
//STRIP001      sal_Bool IsSelectionHandlingLocked() const { return m_nSelectLock>0; }
//STRIP001
//STRIP001      sal_Bool IsHiddenControl(FmEntryData* pEntryData);
//STRIP001
//STRIP001      DECL_LINK( OnEdit, void* );
//STRIP001      DECL_LINK( OnDropActionTimer, void* );
//STRIP001
//STRIP001      DECL_LINK(OnEntrySelDesel, NavigatorTree*);
//STRIP001      DECL_LINK(OnSynchronizeTimer, void*);
//STRIP001
//STRIP001      DECL_LINK( OnClipboardAction, void* );
//STRIP001
//STRIP001  protected:
//STRIP001      virtual void    Command( const CommandEvent& rEvt );
//STRIP001
//STRIP001      virtual sal_Int8    AcceptDrop( const AcceptDropEvent& rEvt );
//STRIP001      virtual sal_Int8    ExecuteDrop( const ExecuteDropEvent& rEvt );
//STRIP001      virtual void        StartDrag( sal_Int8 nAction, const Point& rPosPixel );
//STRIP001
//STRIP001  public:
//STRIP001      NavigatorTree(const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >&   _xORB, Window* pParent );
//STRIP001      virtual ~NavigatorTree();
//STRIP001
//STRIP001      void Clear();
//STRIP001      void Update( FmFormShell* pFormShell );
//STRIP001      void MarkViewObj( FmFormData* pFormData, sal_Bool bMark, sal_Bool bDeep = sal_False );
//STRIP001      void MarkViewObj( FmControlData* pControlData, sal_Bool bMarkHandles, sal_Bool bMark );
//STRIP001      void UnmarkAllViewObj();
//STRIP001
//STRIP001      sal_Bool IsFormEntry( SvLBoxEntry* pEntry );
//STRIP001      sal_Bool IsFormComponentEntry( SvLBoxEntry* pEntry );
//STRIP001
//STRIP001      ::rtl::OUString GenerateName( FmEntryData* pEntryData );
//STRIP001
//STRIP001      NavigatorTreeModel*    GetNavModel() const { return m_pNavModel; }
//STRIP001      SvLBoxEntry*        FindEntry( FmEntryData* pEntryData );
//STRIP001
//STRIP001      virtual sal_Bool EditedEntry( SvLBoxEntry* pEntry, const XubString& rNewText );
//STRIP001      virtual sal_Bool Select( SvLBoxEntry* pEntry, sal_Bool bSelect=sal_True );
//STRIP001      virtual sal_Bool EditingEntry( SvLBoxEntry* pEntry, Selection& );
//STRIP001      virtual void Notify( SfxBroadcaster& rBC, const SfxHint& rHint );
//STRIP001      virtual void KeyInput( const KeyEvent& rKEvt );
//STRIP001
//STRIP001      virtual void ModelHasRemoved( SvListEntry* _pEntry );
//STRIP001
//STRIP001  private:
//STRIP001      sal_Int8    implAcceptDataTransfer( const DataFlavorExVector& _rFlavors, sal_Int8 _nAction, const Point& _rDropPos, sal_Bool _bDnD );
//STRIP001      sal_Int8    implAcceptDataTransfer( const DataFlavorExVector& _rFlavors, sal_Int8 _nAction, SvLBoxEntry* _pTargetEntry, sal_Bool _bDnD );
//STRIP001
//STRIP001      sal_Int8    implExecuteDataTransfer( const OControlTransferData& _rData, sal_Int8 _nAction, const Point& _rDropPos, sal_Bool _bDnD );
//STRIP001      sal_Int8    implExecuteDataTransfer( const OControlTransferData& _rData, sal_Int8 _nAction, SvLBoxEntry* _pTargetEntry, sal_Bool _bDnD );
//STRIP001
//STRIP001      // check if a cut, copy, or drag operation can be started in the current situation
//STRIP001      sal_Bool    implAllowExchange( sal_Int8 _nAction, sal_Bool* _pHasNonHidden = NULL );
//STRIP001      // check if a paste with the current clipboard content can be accepted
//STRIP001      sal_Bool    implAcceptPaste( );
//STRIP001
//STRIP001      // fills m_aControlExchange in preparation of a DnD or clipboard operation
//STRIP001      sal_Bool    implPrepareExchange( sal_Int8 _nAction );
//STRIP001
//STRIP001      void        doPaste();
//STRIP001      void        doCopy();
//STRIP001      void        doCut();
//STRIP001
//STRIP001      sal_Bool    doingKeyboardCut( ) const { return m_bKeyboardCut; }
//STRIP001  };

    //========================================================================
//STRIP001  class NavigatorFrame : public SfxDockingWindow, public SfxControllerItem
//STRIP001  {
//STRIP001  private:
//STRIP001      ::svxform::NavigatorTree* m_pNavigatorTree;
//STRIP001
//STRIP001  protected:
//STRIP001      virtual void Resize();
//STRIP001      virtual sal_Bool Close();
//STRIP001      virtual void GetFocus();
//STRIP001      virtual Size CalcDockingSize( SfxChildAlignment );
//STRIP001      virtual SfxChildAlignment CheckAlignment( SfxChildAlignment, SfxChildAlignment );
//STRIP001
//STRIP001  public:
//STRIP001      NavigatorFrame( SfxBindings *pBindings, SfxChildWindow *pMgr,
//STRIP001                     Window* pParent );
//STRIP001      virtual ~NavigatorFrame();
//STRIP001
//STRIP001      void Update( FmFormShell* pFormShell );
//STRIP001      void StateChanged( sal_uInt16 nSID, SfxItemState eState, const SfxPoolItem* pState );
//STRIP001      void FillInfo( SfxChildWinInfo& rInfo ) const;
//STRIP001  };

    //========================================================================
    class NavigatorFrameManager : public SfxChildWindow
    {
    public:
        NavigatorFrameManager( Window *pParent, sal_uInt16 nId, SfxBindings *pBindings,
                          SfxChildWinInfo *pInfo );
        SFX_DECL_CHILDWINDOW( NavigatorFrameManager );
    };

//............................................................................
}   // namespace svxform
//............................................................................

}//end of namespace binfilter
#endif // _SVX_FMEXPL_HXX

