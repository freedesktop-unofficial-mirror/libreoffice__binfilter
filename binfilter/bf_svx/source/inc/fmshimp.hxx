/*************************************************************************
 *
 *  $RCSfile: fmshimp.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 15:57:15 $
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
#ifndef _SVX_FMSHIMP_HXX
#define _SVX_FMSHIMP_HXX

// auto strip #ifndef _COM_SUN_STAR_SDBC_XROWSETLISTENER_HPP_
// auto strip #include <com/sun/star/sdbc/XRowSetListener.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_CONTAINER_XNAMECONTAINER_HPP_
// auto strip #include <com/sun/star/container/XNameContainer.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_SDBC_XRESULTSET_HPP_
// auto strip #include <com/sun/star/sdbc/XResultSet.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_SDB_XSQLQUERYCOMPOSER_HPP_
// auto strip #include <com/sun/star/sdb/XSQLQueryComposer.hpp>
// auto strip #endif

// auto strip #ifndef _COM_SUN_STAR_FRAME_XSTATUSLISTENER_HPP_
// auto strip #include <com/sun/star/frame/XStatusListener.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_CONTAINER_CONTAINEREVENT_HPP_
// auto strip #include <com/sun/star/container/ContainerEvent.hpp>
// auto strip #endif
#ifndef _COM_SUN_STAR_CONTAINER_XCONTAINERLISTENER_HPP_
#include <com/sun/star/container/XContainerListener.hpp>
#endif
// auto strip #ifndef _COM_SUN_STAR_AWT_XCONTROL_HPP_
// auto strip #include <com/sun/star/awt/XControl.hpp>
// auto strip #endif
#ifndef _COM_SUN_STAR_UTIL_XMODIFYLISTENER_HPP_
#include <com/sun/star/util/XModifyListener.hpp>
#endif
#ifndef _COM_SUN_STAR_FORM_XFORM_HPP_
#include <com/sun/star/form/XForm.hpp>
#endif
#ifndef _COM_SUN_STAR_FORM_XFORMCONTROLLER_HPP_
#include <com/sun/star/form/XFormController.hpp>
#endif
// auto strip #ifndef _COM_SUN_STAR_FORM_XFORMCOMPONENT_HPP_
// auto strip #include <com/sun/star/form/XFormComponent.hpp>
// auto strip #endif
#ifndef _COM_SUN_STAR_FORM_NAVIGATIONBARMODE_HPP_
#include <com/sun/star/form/NavigationBarMode.hpp>
#endif
// auto strip #ifndef _COM_SUN_STAR_FRAME_XFRAME_HPP_
// auto strip #include <com/sun/star/frame/XFrame.hpp>
// auto strip #endif
#ifndef _COM_SUN_STAR_VIEW_XSELECTIONCHANGELISTENER_HPP_
#include <com/sun/star/view/XSelectionChangeListener.hpp>
#endif
// auto strip #ifndef _COM_SUN_STAR_BEANS_XPROPERTYSET_HPP_
// auto strip #include <com/sun/star/beans/XPropertySet.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_BEANS_XFASTPROPERTYSET_HPP_
// auto strip #include <com/sun/star/beans/XFastPropertySet.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_BEANS_XPROPERTYCHANGELISTENER_HPP_
// auto strip #include <com/sun/star/beans/XPropertyChangeListener.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_BEANS_PROPERTYCHANGEEVENT_HPP_
// auto strip #include <com/sun/star/beans/PropertyChangeEvent.hpp>
// auto strip #endif

// auto strip #ifndef _SV_TIMER_HXX //autogen
// auto strip #include <vcl/timer.hxx>
// auto strip #endif

// auto strip #ifndef _SFXAPP_HXX //autogen wg. SFX_APP
// auto strip #include <bf_sfx2/app.hxx>
// auto strip #endif

#ifndef _SVDMARK_HXX
#include "svdmark.hxx"
#endif

#ifndef _SVX_SVXIDS_HRC
#include "svxids.hrc"
#endif

// auto strip #ifndef _SVARRAY_HXX //autogen
// auto strip #include <svtools/svarray.hxx>
// auto strip #endif
// auto strip #ifndef SVX_DBTOOLSCLIENT_HXX
// auto strip #include "dbtoolsclient.hxx"
// auto strip #endif
// auto strip #ifndef _SFXLSTNER_HXX //autogen
// auto strip #include <svtools/lstner.hxx>
// auto strip #endif

#define _SVSTDARR_BOOLS
#define _SVSTDARR_BYTES
#define _SVSTDARR_LONGS
#define _SVSTDARR_ULONGS
#define _SVSTDARR_USHORTS
// auto strip #include <svtools/svstdarr.hxx>

#ifndef _SFXMNUITEM_HXX //autogen
#include <bf_sfx2/mnuitem.hxx>
#endif
#ifndef _SVX_FMTOOLS_HXX
#include "fmtools.hxx"
#endif
#ifndef _FMSEARCH_HXX
#include "fmsearch.hxx"
#endif
// auto strip #ifndef _FMSRCCF_HXX_
// auto strip #include "fmsrccfg.hxx"
// auto strip #endif
// auto strip #ifndef _OSL_MUTEX_HXX_
// auto strip #include <osl/mutex.hxx>
// auto strip #endif
// auto strip #ifndef _VOS_THREAD_HXX_ //autogen
// auto strip #include <vos/thread.hxx>
// auto strip #endif
// auto strip #ifndef _SFXCANCEL_HXX //autogen
// auto strip #include <svtools/cancel.hxx>
// auto strip #endif
// auto strip #ifndef _TOOLS_DEBUG_HXX //autogen wg. DBG_WARNING
// auto strip #include <tools/debug.hxx>
// auto strip #endif
// auto strip #ifndef _CPPUHELPER_COMPONENT_HXX_
// auto strip #include <cppuhelper/component.hxx>
// auto strip #endif
// auto strip #ifndef _COMPHELPER_STLTYPES_HXX_
// auto strip #include <comphelper/stl_types.hxx>
// auto strip #endif
// auto strip #ifndef _COMPHELPER_CONTAINER_HXX_
// auto strip #include <comphelper/container.hxx>
// auto strip #endif
// auto strip #ifndef _FM_IMPLEMENTATION_IDS_HXX_
// auto strip #include "fmimplids.hxx"
// auto strip #endif
#ifndef _CPPUHELPER_COMPBASE6_HXX_
#include <cppuhelper/compbase6.hxx>
#endif
#ifndef _UTL_CONFIGITEM_HXX_
#include <unotools/configitem.hxx>
#endif
#ifndef SVX_DBTOOLSCLIENT_HXX
#include "dbtoolsclient.hxx"
#endif

#include <queue>
namespace binfilter {

SV_DECL_PTRARR(SdrObjArray, SdrObject*, 32, 16)//STRIP008 ;
//  SV_DECL_OBJARR(FmFormArray, ::com::sun::star::uno::Reference< ::com::sun::star::form::XForm>, 32, 16);
DECLARE_STL_VECTOR( ::com::sun::star::uno::Reference< ::com::sun::star::form::XForm > ,FmFormArray);

// catch databse exceptions if occur
#define DO_SAFE(statement) try { statement; } catch( const Exception& ) { DBG_ERROR("unhandled exception (I tried to move a cursor (or something like that).)"); }

#define GA_DISABLE_SYNC     1
#define GA_FORCE_SYNC       2
#define GA_ENABLE_SYNC      3
#define GA_SYNC_MASK        3
#define GA_DISABLE_ROCTRLR  4
#define GA_ENABLE_ROCTRLR   8


// flags for controlling the behaviour when calling loadForms
#define FORMS_LOAD          0x0000      // default: simply load
#define FORMS_SYNC          0x0000      // default: do in synchronous

#define FORMS_UNLOAD        0x0001      // unload
#define FORMS_RESET         0x0002      // reset after the load/unload
#define FORMS_ASYNC         0x0004      // do this async

//==============================================================================
// FmFormNavigationDispatcher - a dispatcher responsible for a form navigation slot
//==============================================================================

class FmFormNavigationDispatcher : public FmSlotDispatch
{
//STRIP001  ::com::sun::star::frame::FeatureStateEvent  m_aNonActiveState;  // the state to report to the listeners if we're inactive
//STRIP001  ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XResultSet>       m_xCursor;          // the cursor we're responsible for
//STRIP001  sal_Bool                m_bActive;          // forward the StateChanged as statusChanged to our listeners ?
//STRIP001  UniString               m_sAccessPath;      // the access path of m_xCursor (redundant but more performant)
//STRIP001
//STRIP001 public:
//STRIP001  ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XResultSet>       getForm() const { return m_xCursor; }
//STRIP001  UniString               getFormAccessPath() const { return m_sAccessPath; }
//STRIP001
//STRIP001 public:
//STRIP001  FmFormNavigationDispatcher(const  ::com::sun::star::util::URL& _rUrl, sal_Int16 _nSlotId, SfxBindings& _rBindings, const ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XResultSet>& _xForm, const UniString& _rAccessPath);
//STRIP001
//STRIP001  void SetActive(sal_Bool bEnable);
//STRIP001  sal_Bool IsActive() const  { return m_bActive; }
//STRIP001
//STRIP001  // set a specific state which will be broadcasted to the listeners (no matter if we are active or not)
//STRIP001  void SetStatus(SfxItemState eState, const SfxPoolItem* pState);
//STRIP001
//STRIP001  // XComponent
//STRIP001     virtual void SAL_CALL dispose(  ) throw(::com::sun::star::uno::RuntimeException);
//STRIP001
//STRIP001 protected:
//STRIP001  // SfxControllerItem
//STRIP001  virtual void StateChanged(USHORT nSID, SfxItemState eState, const SfxPoolItem* pState);
//STRIP001
//STRIP001  virtual void NotifyState(SfxItemState eState, const SfxPoolItem* pState, const ::com::sun::star::uno::Reference< ::com::sun::star::frame::XStatusListener>& rListener = ::com::sun::star::uno::Reference< ::com::sun::star::frame::XStatusListener>());
};

//==============================================================================
// a class iterating through all fields of a form which are bound to a field
// sub forms are ignored, grid columns (where the grid is a direct child of the form) are included
//STRIP001 class FmXBoundFormFieldIterator : public ::comphelper::IndexAccessIterator
//STRIP001 {
//STRIP001 public:
//STRIP001  FmXBoundFormFieldIterator(const ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface>& _rStartingPoint) : ::comphelper::IndexAccessIterator(_rStartingPoint) { }
//STRIP001
//STRIP001 protected:
//STRIP001  virtual sal_Bool ShouldHandleElement(const ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface>& _rElement);
//STRIP001  virtual sal_Bool ShouldStepInto(const ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface>& _rContainer) const;
//STRIP001 };

//========================================================================
// I would prefer this to be a struct local to FmXFormShell but unfortunately local structs/classes
// are somewhat difficult with some of our compilers
class FmCursorActionThread;
struct CursorActionDescription
{
    FmCursorActionThread*   pThread;
    sal_uInt32                  nFinishedEvent;
        // we want to do the cleanup of the thread in the main thread so we post an event to ourself
    sal_Bool                    bCanceling;
        // this thread is being canceled

    CursorActionDescription() : pThread(NULL), nFinishedEvent(0), bCanceling(sal_False) { }
};

class FmFormPage;
//========================================================================
struct FmLoadAction
{
    FmFormPage* pPage;
    sal_uInt32  nEventId;
    sal_uInt16  nFlags;

    FmLoadAction( ) : pPage( NULL ), nFlags( 0 ), nEventId( 0 ) { }
    FmLoadAction( FmFormPage* _pPage, sal_uInt16 _nFlags, sal_uInt32 _nEventId )
        :pPage( _pPage ), nFlags( _nFlags ), nEventId( _nEventId )
    {
    }
};

//========================================================================
class SfxViewFrame;
typedef ::cppu::WeakComponentImplHelper6<   ::com::sun::star::sdbc::XRowSetListener,
                                            ::com::sun::star::beans::XPropertyChangeListener,
                                            ::com::sun::star::util::XModifyListener,
                                            ::com::sun::star::container::XContainerListener,
                                            ::com::sun::star::view::XSelectionChangeListener,
                                            ::com::sun::star::form::XFormControllerListener> FmXFormShell_BD_BASE;

//========================================================================
class FmXFormShell_Base_Disambiguation : public FmXFormShell_BD_BASE
{
protected:
    FmXFormShell_Base_Disambiguation( ::osl::Mutex& _rMutex );
    virtual void SAL_CALL disposing();
};

//========================================================================
typedef FmXFormShell_Base_Disambiguation    FmXFormShell_BASE;
typedef ::utl::ConfigItem                   FmXFormShell_CFGBASE;

class FmXFormShell  :public FmXFormShell_BASE
                    ,public FmXFormShell_CFGBASE
                    ,public FmDispatchInterceptor
                    ,public ::binfilter::svxform::OStaticDataAccessTools//STRIP008                  ,public ::svxform::OStaticDataAccessTools
{
    friend class FmFormShell;
    friend class FmFormView;
    friend class WizardUsageConfigItem;

    class SuspendPropertyTracking;
    friend class SuspendPropertyTracking;

    // Timer um verzoegerte Markierung vorzunehmen
    Timer              m_aMarkTimer;
    SdrObjArray         m_arrSearchedControls;
        // We enable a permanent cursor for the grid we found a searched text, it's disabled in the next "found" event.
    FmFormArray         m_arrSearchContexts;

        // some typedefs :
    // all dispatchers belonging to a form
    DECLARE_STL_VECTOR(FmFormNavigationDispatcher*, SingleFormDispatchers);

    // a map from a form access path (like "1/4/2") to the dispatchers array for this form
    DECLARE_STL_USTRINGACCESS_MAP(SingleFormDispatchers, FormsDispatchers);
    FormsDispatchers        m_aNavigationDispatcher;

    ::binfilter::form::OImplementationIdsRef    m_aHoldImplIdHelper;//STRIIP008 ::form::OImplementationIdsRef   m_aHoldImplIdHelper;

    SvUShorts   m_arrInvalidSlots;
    SvBytes     m_arrInvalidSlots_Flags;
        // we explicitly switch off the propbrw before leaving the design mode
        // this flag tells us if we have to switch it on again when reentering

    DECLARE_STL_USTRINGACCESS_MAP(CursorActionDescription, CursorActions);
    CursorActions   m_aCursorActions;
        // all actions on async cursors

    SvBools     m_aControlLocks;
        // while doing a async cursor action we have to lock all controls of the active controller.
        // m_aControlLocks remembers the previous lock states to be restored afterwards.
    ::osl::Mutex    m_aAsyncSafety;
        // secure the access to our thread related members
    ::osl::Mutex    m_aInvalidationSafety;
        // secure the access to all our slot invalidation related members

    ::com::sun::star::form::NavigationBarMode   m_eNavigate;                // Art der Navigation

        // da ich beim Suchen fuer die Behandlung des "gefunden" ein SdrObject markieren will, besorge ich mir vor dem
        // Hochreissen des Suchen-Dialoges alle relevanten Objekte
        // (das Array ist damit auch nur waehrend des Suchvorganges gueltig)
    SvLongs             m_arrRelativeGridColumn;

    ::osl::Mutex    m_aMutex;
    sal_uInt32      m_nInvalidationEvent;
    ::std::queue< FmLoadAction >
                    m_aLoadingPages;

    FmFormShell*    m_pShell;

    // aktuelle Form, Controller
    // nur im alive mode verfuegbar
    ::com::sun::star::uno::Reference< ::com::sun::star::form::XFormController>  m_xActiveController;
    ::com::sun::star::uno::Reference< ::com::sun::star::form::XFormController>  m_xNavigationController;
    ::com::sun::star::uno::Reference< ::com::sun::star::form::XForm>            m_xActiveForm;
    ::com::sun::star::uno::Reference< ::com::sun::star::sdb::XSQLQueryComposer> m_xParser;

    // Aktueller container einer Page
    // nur im designmode verfuegbar
    ::com::sun::star::uno::Reference< ::com::sun::star::container::XIndexAccess> m_xForms;

    // aktuell selektiertes Object (Form oder Control)
    ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface>       m_xSelObject;

    // aktuelles Control, keine Form
    ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface>       m_xCurControl;

    // aktuelle Form
    ::com::sun::star::uno::Reference< ::com::sun::star::form::XForm>           m_xCurForm;


        // und das ist ebenfalls fuer's 'gefunden' : Beim Finden in GridControls brauche ich die Spalte, bekomme aber
        // nur die Nummer des Feldes, die entspricht der Nummer der Spalte + <offset>, wobei der Offset von der Position
        // des GridControls im Formular abhaengt. Also hier eine Umrechnung.
    ::com::sun::star::uno::Reference< ::com::sun::star::awt::XControlModel>         m_xLastGridFound;
        // we want to be a DispatchInterceptor within our frame
    ::com::sun::star::uno::Reference< ::com::sun::star::frame::XFrame>              m_xAttachedFrame;
        // Administration of external form views (see the SID_FM_VIEW_AS_GRID-slot)
    ::com::sun::star::uno::Reference< ::com::sun::star::frame::XController>         m_xExternalViewController;      // the controller for the external form view
    ::com::sun::star::uno::Reference< ::com::sun::star::form::XFormController>      m_xExtViewTriggerController;    // the nav controller at the time the external display was triggered
    ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XResultSet>           m_xExternalDisplayedForm;       // the form which the external view is based on

    FmXDispatchInterceptorImpl*     m_pMainFrameInterceptor;
    FmXDispatchInterceptorImpl*     m_pExternalViewInterceptor;

    sal_Int16       m_nLockSlotInvalidation;
    sal_Bool        m_bHadPropBrw:1;

    sal_Bool        m_bTrackProperties  : 1;
        // soll ich (bzw. der Owner diese Impl-Klasse) mich um die Aktualisierung des ::com::sun::star::beans::Property-Browsers kuemmern ?

    sal_Bool        m_bUseWizards : 1;

    sal_Bool        m_bActiveModified   : 1;    // Controller modifiziert
    sal_Bool        m_bDatabaseBar      : 1;    // Gibt es eine Datenbankleiste
    sal_Bool        m_bInActivate       : 1;    // Wird ein Controller aktiviert
    sal_Bool        m_bSetFocus         : 1;    // Darf der Focus umgesetzt werden
    sal_Bool        m_bFilterMode       : 1;    // Wird gerade ein Filter auf die Controls angesetzt
    sal_Bool        m_bChangingDesignMode:1;    // sal_True within SetDesignMode
    sal_Bool        m_bPreparedClose    : 1;    // for the current modification state of the current form
                                                //  PrepareClose had been called and the user denied to save changes

public:
    FmXFormShell(FmFormShell* _pShell, SfxViewFrame* _pViewFrame);
    ~FmXFormShell();

    // UNO Anbindung
    DECLARE_UNO3_DEFAULTS(FmXFormShell, FmXFormShell_BASE);
//STRIP001  virtual ::com::sun::star::uno::Any SAL_CALL queryInterface( const ::com::sun::star::uno::Type& type) throw ( ::com::sun::star::uno::RuntimeException );
    virtual ::com::sun::star::uno::Sequence< sal_Int8 > SAL_CALL getImplementationId() throw(::com::sun::star::uno::RuntimeException);
//STRIP001  ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Type > SAL_CALL getTypes(  ) throw(::com::sun::star::uno::RuntimeException);

// EventListener
    virtual void SAL_CALL disposing(const ::com::sun::star::lang::EventObject& Source) throw( ::com::sun::star::uno::RuntimeException );

// ::com::sun::star::container::XContainerListener
    virtual void SAL_CALL elementInserted(const ::com::sun::star::container::ContainerEvent& rEvent) throw( ::com::sun::star::uno::RuntimeException );
    virtual void SAL_CALL elementReplaced(const ::com::sun::star::container::ContainerEvent& rEvent) throw( ::com::sun::star::uno::RuntimeException );
    virtual void SAL_CALL elementRemoved(const ::com::sun::star::container::ContainerEvent& rEvent) throw( ::com::sun::star::uno::RuntimeException );

// XSelectionChangeListener
    virtual void SAL_CALL selectionChanged(const ::com::sun::star::lang::EventObject& rEvent) throw( ::com::sun::star::uno::RuntimeException );

// ::com::sun::star::beans::XPropertyChangeListener
    virtual void SAL_CALL propertyChange(const ::com::sun::star::beans::PropertyChangeEvent& evt) throw( ::com::sun::star::uno::RuntimeException );

// ::com::sun::star::sdbc::XRowSetListener
    virtual void SAL_CALL cursorMoved(const ::com::sun::star::lang::EventObject& event) throw( ::com::sun::star::uno::RuntimeException );
    virtual void SAL_CALL rowChanged(const ::com::sun::star::lang::EventObject& event) throw( ::com::sun::star::uno::RuntimeException ) { }
    virtual void SAL_CALL rowSetChanged(const ::com::sun::star::lang::EventObject& event) throw( ::com::sun::star::uno::RuntimeException ) { }

// ::com::sun::star::util::XModifyListener    -> modify setzen
    virtual void SAL_CALL modified(const ::com::sun::star::lang::EventObject& Source) throw( ::com::sun::star::uno::RuntimeException );

// ::com::sun::star::frame::XDispatchProviderInterceptor
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::frame::XDispatch> interceptedQueryDispatch(sal_uInt16 _nId,
        const  ::com::sun::star::util::URL& aURL, const ::rtl::OUString& aTargetFrameName, sal_Int32 nSearchFlags) throw( ::com::sun::star::uno::RuntimeException );
    virtual ::osl::Mutex* getInterceptorMutex() { return &m_aAsyncSafety; }

// ::com::sun::star::form::XFormControllerListener
    virtual void SAL_CALL formActivated(const ::com::sun::star::lang::EventObject& rEvent) throw( ::com::sun::star::uno::RuntimeException );
    virtual void SAL_CALL formDeactivated(const ::com::sun::star::lang::EventObject& rEvent) throw( ::com::sun::star::uno::RuntimeException );

// OComponentHelper
    virtual void SAL_CALL disposing();

    void EnableTrackProperties( sal_Bool bEnable) { m_bTrackProperties = bEnable; }
    sal_Bool IsTrackPropertiesEnabled() {return m_bTrackProperties;}

public:
    // activation handling
            void        viewActivated( FmFormView* _pCurrentView, sal_Bool _bSyncAction = sal_False );
            void        viewDeactivated( FmFormView* _pCurrentView, sal_Bool _bDeactivateController = sal_True );

protected:
    // form handling
    /// load or unload the forms on a page
            void        loadForms( FmFormPage* _pPage, const sal_uInt16 _nBehaviour = FORMS_LOAD | FORMS_SYNC );
//STRIP001          void        smartControlReset( const ::com::sun::star::uno::Reference< ::com::sun::star::container::XIndexAccess >& _rxModels );


    // stuff
    void ResetForms(const ::com::sun::star::uno::Reference< ::com::sun::star::container::XIndexAccess>& _xForms = ::com::sun::star::uno::Reference< ::com::sun::star::container::XIndexAccess>(), sal_Bool bInvalidate = sal_False);
    void AddElement(const ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface>& Element);
    void RemoveElement(const ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface>& Element);

//STRIP001  void startListening();
//STRIP001  void stopListening();

//STRIP001  void ExecuteSearch();       // execute SID_FM_SEARCH

//STRIP001  void CreateExternalView();  // execute SID_FM_VIEW_AS_GRID

//STRIP001  sal_Bool    GetY2KState(sal_uInt16& n);
//STRIP001  void    SetY2KState(sal_uInt16 n);

//STRIP001  ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet> GetBoundField(const ::com::sun::star::uno::Reference< ::com::sun::star::awt::XControl>& _xControl, const ::com::sun::star::uno::Reference< ::com::sun::star::form::XForm>& _xForm) const;

//STRIP001  ::com::sun::star::uno::Reference< ::com::sun::star::awt::XControl>  GetControlFromModel(const ::com::sun::star::uno::Reference< ::com::sun::star::awt::XControlModel>& xModel);
        // liefert das Control, welches das angegebene Model hat
//STRIP001  void CollectFormContexts(const ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface>& xStartingPoint, const UniString& strCurrentLevelPrefix, UniString& strNames);
        // sammelt in strNames die Namen aller Formulare, fuegt die entsprechenden XFormRefs in m_arrSearchContexts ein

//STRIP001  static sal_Bool CanMoveRight(const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet>& _xControllerModel);
//STRIP001  static sal_Bool CanMoveLeft(const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet>& _xControllerModel);
//STRIP001  static sal_Bool SaveModified(const ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XResultSetUpdate>& _xCursor, ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet>& _xSet, sal_Bool& _rRecordInserted);
//STRIP001  static sal_Bool MoveRight(const ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XResultSetUpdate>& _xCursor);
//STRIP001  static sal_Bool MoveLeft(const ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XResultSetUpdate>& _xCursor);

public:
//STRIP001  static sal_Bool CanMoveRight(const ::com::sun::star::uno::Reference< ::com::sun::star::form::XFormController>& xController);
//STRIP001  static sal_Bool CanMoveLeft(const ::com::sun::star::uno::Reference< ::com::sun::star::form::XFormController>& xController);
//STRIP001  static sal_Bool MoveRight(const ::com::sun::star::uno::Reference< ::com::sun::star::form::XFormController>& xController);
//STRIP001  static sal_Bool MoveLeft(const ::com::sun::star::uno::Reference< ::com::sun::star::form::XFormController>& xController);
    static sal_Bool CommitCurrent(const ::com::sun::star::uno::Reference< ::com::sun::star::form::XFormController>& _xController);
//STRIP001  static sal_Bool IsModified(const ::com::sun::star::uno::Reference< ::com::sun::star::form::XFormController>& xController);
//STRIP001  static void ResetCurrent(const ::com::sun::star::uno::Reference< ::com::sun::star::form::XFormController>& _xController);
//STRIP001         void ResetAll(const ::com::sun::star::uno::Reference< ::com::sun::star::form::XForm>& _xForm);
//STRIP001  static sal_Bool SaveModified(const ::com::sun::star::uno::Reference< ::com::sun::star::form::XFormController>& xController, sal_Bool bCommit = sal_True);

    // methode fuer nicht designmode (alive mode)
    void setActiveController( const ::com::sun::star::uno::Reference< ::com::sun::star::form::XFormController>& _xController, sal_Bool _bNoSaveOldContent = sal_False );
    const ::com::sun::star::uno::Reference< ::com::sun::star::form::XFormController>& getActiveController() const {return m_xActiveController;}
    const ::com::sun::star::uno::Reference< ::com::sun::star::form::XFormController>& getActiveInternalController() const { return m_xActiveController == m_xExternalViewController ? m_xExtViewTriggerController : m_xActiveController; }
    const ::com::sun::star::uno::Reference< ::com::sun::star::form::XForm>& getActiveForm() const {return m_xActiveForm;}
    const ::com::sun::star::uno::Reference< ::com::sun::star::form::XFormController>& getNavController() const {return m_xNavigationController;}
    ::com::sun::star::uno::Reference< ::com::sun::star::sdb::XSQLQueryComposer> getParser() const { return m_xParser; }

    // nur im design mode verwenden, aktuell selektiertes Formular oder Control
//STRIP001  void    setCurForm(const ::com::sun::star::uno::Reference< ::com::sun::star::form::XForm>& xF);
    void    setCurControl(const ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface>& xObj);
    void    setCurControl(const SdrMarkList& rMarkList);
    void    setSelObject(const ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface>& xObj);

    const   ::com::sun::star::uno::Reference< ::com::sun::star::form::XForm>& getCurForm() const {return m_xCurForm;}
    const   ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface>& getCurControl() const {return m_xCurControl;}
    const   ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface>& getSelObject() const {return m_xSelObject;}

    sal_Bool hasForms() const {return m_xForms.is() && m_xForms->getCount() != 0;}
    sal_Bool isActiveModified() const {return m_bActiveModified;}
    sal_Bool hasDatabaseBar() const {return m_bDatabaseBar;}
    sal_Bool canNavigate() const    {return m_xNavigationController.is();}
    sal_Bool isParsable() const     {return m_xParser.is() && m_xParser->getQuery().getLength();}
    sal_Bool hasFilter() const      { return isParsable() &&
                                        (m_xParser->getFilter().getLength() || m_xParser->getOrder().getLength()); }

//STRIP001  void ShowProperties( const ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface>& rxObject, sal_Bool bShow=sal_True );
    sal_Bool IsPropBrwOpen() const;

    void DetermineSelection(const SdrMarkList& rMarkList);
    ::com::sun::star::uno::Reference< ::com::sun::star::form::XForm> DetermineCurForm(const SdrMarkList& rMarkList, sal_Bool&);
    void SetSelection(const SdrMarkList& rMarkList);
    void SetSelectionDelayed(FmFormView* pView);

    void SetDesignMode(sal_Bool bDesign);

    sal_Bool    GetWizardUsing() const { return m_bUseWizards; }
//STRIP001  void        SetWizardUsing(sal_Bool _bUseThem);

        // Setzen des Filtermodus
    sal_Bool isInFilterMode() const {return m_bFilterMode;}
//STRIP001  void startFiltering();
//STRIP001  void stopFiltering(sal_Bool bSave);
//STRIP001  void clearFilter();

//STRIP001  static PopupMenu* GetConversionMenu();
        // ein Menue, das alle ControlConversion-Eintraege enthaelt
//STRIP001  sal_Bool ConvertControlTo(const ::com::sun::star::uno::Reference< ::com::sun::star::form::XFormComponent>& xModel, sal_uInt16 nTargetObjectId);
        // umwandeln eines Controls
//STRIP001  static  sal_Bool IsControlConversionSlot(sal_uInt16 nSlotId);
        // ein gueltiger ControlConversionSlot
//STRIP001  static  sal_Bool IsConversionPossible(const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet>& xContext, sal_Int16 nConversionSlot);
        // Konvertierung der Komponente mit geg. Slot moeglich
//STRIP001  static  void CheckControlConversionSlots(const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet>& xContext, Menu& rMenu);
        // iteriertes IsConversionPossible
//STRIP001  sal_Bool ExecuteControlConversionSlot(const ::com::sun::star::uno::Reference< ::com::sun::star::form::XFormComponent>& xContext, sal_uInt16 nSlotId);
        // verkapptes ConvertControlTo

private:
//STRIP001  static sal_Bool SaveModified(const ::com::sun::star::uno::Reference< ::com::sun::star::form::XFormController>& xController,
//STRIP001                              ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XResultSetUpdate>& xCursor,
//STRIP001                              ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet>& xSet,
//STRIP001                              sal_Bool& rRecordInserted);


    DECL_LINK(OnFoundData, FmFoundRecordInformation*);
    DECL_LINK(OnCanceledNotFound, FmFoundRecordInformation*);
    DECL_LINK(OnSearchContextRequest, FmSearchContext*);
    DECL_LINK(OnTimeOut, void*);

//STRIP001  void LoopGrids(sal_Int16 nWhat);

    // das Setzen des curObject/selObject/curForm erfolgt verzoegert (SetSelectionDelayed), mit den folgenden
    // Funktionen laesst sich das abfragen/erzwingen
    inline sal_Bool IsSelectionUpdatePending();
//STRIP001  void        ForceUpdateSelection(sal_Bool bLockInvalidation);

    // Invalidierung von Slots
//STRIP001  void    InvalidateSlot(sal_Int16 nId, sal_Bool bWithItem = sal_True, sal_Bool bWithId = sal_False);
    // Locking der Invalidierung - wenn der interne Locking-Counter auf 0 geht, werden alle aufgelaufenen Slots
    // (asynchron) invalidiert
//STRIP001  void    LockSlotInvalidation(sal_Bool bLock);

    DECL_LINK(OnInvalidateSlots, void*);

//STRIP001  ::com::sun::star::uno::Reference< ::com::sun::star::form::XForm>            getInternalForm(const ::com::sun::star::uno::Reference< ::com::sun::star::form::XForm>& _xForm) const;
//STRIP001  ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XResultSet>       getInternalForm(const ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XResultSet>& _xForm) const;
        // if the form belongs to the controller (extern) displaying a grid, the according internal form will
        // be displayed, _xForm else

    void    CloseExternalFormViewer();
        // closes the task-local beamer displaying a grid view for a form

    // ConfigItem related stuff
//STRIP001  virtual void Notify( const ::com::sun::star::uno::Sequence< ::rtl::OUString >& _rPropertyNames);
    void implAdjustConfigCache();

    // ---------------------------------------------------
    // asyncronous cursor actions/navigation slot handling

//STRIP001  void ActivateDispatchers(const UniString& sNavFormAccess, sal_Bool bActivate);
        // (de)activate all dispatchers belonging to the form with the given access path
    DECL_LINK(OnExecuteNavSlot, FmFormNavigationDispatcher*);

//STRIP001  UniString GetAccessPathFromForm(const ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XResultSet>& _xForm, const UniString& rAssumedPagePrefix = UniString()) const;
        // return the access path of the given form (if rAssumedPagePrefix the current page's id is taken as page prefix)
//STRIP001  ::com::sun::star::uno::Reference< ::com::sun::star::container::XNameContainer> GetPageForms(const UniString sPageId) const;
        // return the forms collection of the page with the given id
//STRIP001  UniString GetPageId(const ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XResultSet>& _xForm) const;
        // get the id of the page to which's forms collection _xForms belongs

//STRIP001  sal_Bool    PathsInterfere(const UniString& _rPathLeft, const UniString& _rPathRight) const;

//STRIP001  void UpdateFormDispatcher(FmFormNavigationDispatcher* _pDisp);
//STRIP001  void UpdateAllFormDispatchers(const UniString& _rPath);

//STRIP001  void setControlLocks();     // lock all controls of the active controller
//STRIP001  void restoreControlLocks(); // restore the lock state of all controls of the active controller

    enum CURSOR_ACTION { CA_MOVE_TO_LAST, CA_MOVE_ABSOLUTE };
//STRIP001  void DoAsyncCursorAction(const ::com::sun::star::uno::Reference< ::com::sun::star::form::XFormController>& _xController, CURSOR_ACTION _eWhat);
//STRIP001  void DoAsyncCursorAction(const ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XResultSet>& _xForm, CURSOR_ACTION _eWhat);

    sal_Bool HasAnyPendingCursorAction() const;
//STRIP001  void CancelAnyPendingCursorAction();

//STRIP001  sal_Bool HasPendingCursorAction(const ::com::sun::star::uno::Reference< ::com::sun::star::form::XFormController>& _xController) const;
//STRIP001  sal_Bool HasPendingCursorAction(const ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XResultSet>& _xForm) const;
//STRIP001  sal_Bool HasPendingCursorAction(const UniString& _rAccessPath) const;

    DECL_LINK(OnCursorActionDone, FmCursorActionThread*);
    DECL_LINK(OnCursorActionDoneMainThread, FmCursorActionThread*);

    DECL_LINK( OnLoadForms, FmFormPage* );
};

//------------------------------------------------------------------------------
inline sal_Bool FmXFormShell::IsSelectionUpdatePending()
{
    return m_aMarkTimer.IsActive();
}

// ========================================================================
// = ein Iterator, der ausgehend von einem Interface ein Objekt sucht, dessen
// = ::com::sun::star::beans::Property-Set eine ControlSource- sowie eine BoundField-Eigenschaft hat,
// = wobei letztere einen Wert ungleich NULL haben muss.
// = Wenn das Interface selber diese Bedingung nicht erfuellt, wird getestet,
// = ob es ein Container ist (also ueber eine ::com::sun::star::container::XIndexAccess verfuegt), dann
// = wird dort abgestiegen und fuer jedes Element des Containers das selbe
// = versucht (wiederum eventuell mit Abstieg).
// = Wenn irgendein Objekt dabei die geforderte Eigenschaft hat, entfaellt
// = der Teil mit dem Container-Test fuer dieses Objekt.
// =

//STRIP001 class SearchableControlIterator : public ::comphelper::IndexAccessIterator
//STRIP001 {
//STRIP001  ::rtl::OUString         m_sCurrentValue;
//STRIP001      // der aktuelle Wert der ControlSource-::com::sun::star::beans::Property
//STRIP001
//STRIP001 public:
//STRIP001  ::rtl::OUString     getCurrentValue() const { return m_sCurrentValue; }
//STRIP001
//STRIP001 public:
//STRIP001  SearchableControlIterator(::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface> xStartingPoint);
//STRIP001
//STRIP001  virtual sal_Bool ShouldHandleElement(const ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface>& rElement);
//STRIP001  virtual sal_Bool ShouldStepInto(const ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface>& xContainer) const;
//STRIP001  virtual void Invalidate() { IndexAccessIterator::Invalidate(); m_sCurrentValue = ::rtl::OUString(); }
//STRIP001 };

// ========================================================================
SV_DECL_PTRARR_DEL(StatusForwarderArray, SfxStatusForwarder*, 16, 0)
class ControlConversionMenuController : public SfxMenuControl
{
protected:
    StatusForwarderArray    m_aStatusForwarders;
    Menu*                   m_pMainMenu;
    PopupMenu*              m_pConversionMenu;

public:
    ControlConversionMenuController(sal_uInt16 nId, Menu& rMenu, SfxBindings& rBindings);
//STRIP001  virtual ~ControlConversionMenuController();
    SFX_DECL_MENU_CONTROL();

//STRIP001  virtual void StateChanged(sal_uInt16 nSID, SfxItemState eState, const SfxPoolItem* pState);
};

//==================================================================
// FmCursorActionThread
//==================================================================

//STRIP001 class FmCursorActionThread : public ::vos::OThread
//STRIP001 {
//STRIP001  Link                    m_aTerminationHandler;      // the handler to be called upon termination
//STRIP001  ::com::sun::star::sdbc::SQLException            m_aRunException;            // the database exception thrown by RunImpl
//STRIP001  ::osl::Mutex    m_aAccessSafety;            // for securing the multi-thread access
//STRIP001  ::osl::Mutex    m_aFinalExitControl;        // see StopItWait
//STRIP001
//STRIP001 protected:
//STRIP001  ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XResultSet>           m_xDataSource;              // the cursor which we work with
//STRIP001  UniString                   m_sAccessPath;
//STRIP001
//STRIP001 private:
//STRIP001
//STRIP001  UniString                   m_sStopperCaption;          // the caption for the ThreadStopper
//STRIP001  sal_Bool                    m_bCanceled:1;              // StopIt has been called ?
//STRIP001  sal_Bool                    m_bDeleteMyself:1;          // delete the thread upon termination (defaults to sal_False) ?
//STRIP001  sal_Bool                    m_bDisposeCursor:1;         // dispose the cursor upon termination (defaults to sal_False) ?
//STRIP001  sal_Bool                    m_bTerminated:1;                // onTerminated already called ?
//STRIP001  sal_Bool                    m_bRunFailed:1;             // a database execption occured in RunImpl ?
//STRIP001
//STRIP001  // a ThreadStopper will be instantiated so that the open can be canceled via the UI
//STRIP001  class ThreadStopper : protected SfxCancellable
//STRIP001  {
//STRIP001      FmCursorActionThread*   m_pOwner;
//STRIP001
//STRIP001      virtual ~ThreadStopper() { }
//STRIP001
//STRIP001  public:
//STRIP001      ThreadStopper(FmCursorActionThread* pOwner, const UniString& rTitle);
//STRIP001
//STRIP001      virtual void    Cancel();
//STRIP001
//STRIP001      virtual void OwnerTerminated();
//STRIP001      // Normally the Owner (a FmCursorActionThread) would delete the stopper when terminated.
//STRIP001      // Unfortunally the application doesn't remove the 'red light' when a SfxCancellable is deleted
//STRIP001      // if it (the app) can't acquire the solar mutex. The deletion is IGNORED then. So we have make
//STRIP001      // sure that a) the stopper is deleted from inside the main thread (where the solar mutex is locked)
//STRIP001      // and b) that in the time between the termination of the thread and the deletion of the stopper
//STRIP001      // the latter doesn't access the former.
//STRIP001      // The OwnerTerminated cares for both aspects.
//STRIP001      // SO DON'T DELETE THE STOPPER EXPLICITLY !
//STRIP001
//STRIP001  protected:
//STRIP001      // HACK HACK HACK HACK HACK : this should be private, but MSVC doesn't accept the LINK-macro then ....
//STRIP001      DECL_LINK(OnDeleteInMainThread, ThreadStopper*);
//STRIP001  };
//STRIP001  friend class FmCursorActionThread::ThreadStopper;
//STRIP001
//STRIP001
//STRIP001 public:
//STRIP001  ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XResultSet> getDataSource() const { return m_xDataSource; }
//STRIP001  UniString getAccessPath() const { return m_sAccessPath; }
//STRIP001
//STRIP001 private:
//STRIP001  sal_Bool Terminated() { ::osl::MutexGuard aGuard(m_aAccessSafety); return m_bTerminated; }
//STRIP001
//STRIP001 public:
//STRIP001  FmCursorActionThread(const ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XResultSet>& _xDataSource, const UniString& _rStopperCaption, const UniString& _rPath);
//STRIP001  virtual ~FmCursorActionThread() {}
//STRIP001
//STRIP001  // control of self-deletion
//STRIP001  sal_Bool                IsSelfDeleteEnabled()               { ::osl::MutexGuard aGuard(m_aAccessSafety); return m_bDeleteMyself; }
//STRIP001  void                EnableSelfDelete(sal_Bool bEnable)      { ::osl::MutexGuard aGuard(m_aAccessSafety); m_bDeleteMyself = bEnable; }
//STRIP001
//STRIP001  // control of cursor-dipose
//STRIP001  sal_Bool                IsCursorDisposeEnabled()            { ::osl::MutexGuard aGuard(m_aAccessSafety); return m_bDisposeCursor; }
//STRIP001  void                EnableCursorDispose(sal_Bool bEnable)   { ::osl::MutexGuard aGuard(m_aAccessSafety); m_bDisposeCursor = bEnable; }
//STRIP001
//STRIP001  // error-access
//STRIP001  sal_Bool                RunFailed()                         { ::osl::MutexGuard aGuard(m_aAccessSafety); return m_bRunFailed; }
//STRIP001  ::com::sun::star::sdbc::SQLException        GetRunException()                   { ::osl::MutexGuard aGuard(m_aAccessSafety); return m_aRunException; }
//STRIP001
//STRIP001  /// the excution (within the method "run") was canceled ?
//STRIP001  sal_Bool                WasCanceled(sal_Bool bEnable)           { ::osl::MutexGuard aGuard(m_aAccessSafety); return m_bCanceled; }
//STRIP001
//STRIP001  /// the handler will be called synchronously (the parameter is a pointer to the thread)
//STRIP001  void                SetTerminationHdl(const Link& aTermHdl) { ::osl::MutexGuard aGuard(m_aAccessSafety); m_aTerminationHandler = aTermHdl; }
//STRIP001
//STRIP001  /// cancels the process. returns to the caller immediately. to be called from another thread (of course ;)
//STRIP001  void                StopIt();
//STRIP001
//STRIP001  /// cancels the process. does not return to the caller until the thread is terminated.
//STRIP001  void                StopItWait();
//STRIP001
//STRIP001 protected:
//STRIP001  virtual void SAL_CALL run();
//STRIP001  virtual void SAL_CALL onTerminated();
//STRIP001
//STRIP001  /// called from within run. run itself handles (de)initialisation of the cancel handling.
//STRIP001  virtual void RunImpl() = 0;
//STRIP001 };

//------------------------------------------------------------------------------

#define DECL_CURSOR_ACTION_THREAD(classname)            \
                                                        \
class classname : public FmCursorActionThread           \
{                                                       \
public:                                                 \
    classname(const ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XResultSet>& _xDataSource,        \
            const UniString& _rPath);                       \
protected:                                              \
    virtual void RunImpl();                             \
};                                                      \


//------------------------------------------------------------------------------

#define IMPL_CURSOR_ACTION_THREAD(classname, caption, action)   \
                                                                \
classname::classname(const ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XResultSet>& _xDataSource,         \
        const UniString& _rPath)                                    \
    :FmCursorActionThread(_xDataSource, caption, _rPath)        \
{                                                               \
}                                                               \
                                                                \
void classname::RunImpl()                                       \
{                                                               \
    m_xDataSource->action;                                      \
}                                                               \



}//end of namespace binfilter
#endif          // _SVX_FMSHIMP_HXX
