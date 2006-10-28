/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: unoedacc.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 04:21:38 $
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

#ifndef _SVX_UNOEDACC_HXX_
#define _SVX_UNOEDACC_HXX_

#include <memory>

#ifndef _SV_GEN_HXX
#include <tools/gen.hxx>
#endif





#ifndef _COM_SUN_STAR_ACCESSIBILITY_XACCESSIBLECOMPONENT_HPP_
#include <com/sun/star/accessibility/XAccessibleComponent.hpp>
#endif

#ifndef _COM_SUN_STAR_ACCESSIBILITY_XACCESSIBLEEVENTBROADCASTER_HPP_
#include <com/sun/star/accessibility/XAccessibleEventBroadcaster.hpp>
#endif
namespace binfilter {


class SvxTextForwarder;
class SvxViewForwarder;
class SvxEditSource;
class SvxAccessibleTextHelper_Impl;

/** Helper class for objects containing EditEngine text

    This class provides the methods from the XAccessibleContext,
    XAccessibleEventBroadcaster and XAccessibleComponent interfaces,
    that are common to all accessible objects containing an edit
    engine.

    You have to implement the SvxEditSource, SvxTextForwarder,
    SvxViewForwarder and SvxEditViewForwarder interfaces in order to
    enable your object to cooperate with this class. SvxTextForwarder
    encapsulates the fact that text objects do not necessarily have an
    EditEngine at their disposal, SvxViewForwarder and
    SvxEditViewForwarder do the same for the document and the edit
    view.

    To support changes in edit mode or conversion of fixed text
    into EditEngine text, you can change the SvxEditSource this
    class is referring to. This might render all children invalid
    and change the child count.

    This class registers itself at the edit engine as a state
    listener and manages the state of its children (i.e. the
    paragraphs)

    @attention All public methods must not be called with any mutex
    hold, except when calling from the main thread (with holds the
    solar mutex), unless stated otherwise. This is because they
    themselves might need the solar mutex in addition to the object
    mutex, and the ordering of the locking must be: first solar mutex,
    then object mutex. Furthermore, state change events might be fired
    internally.

    @derive Use this class in an aggregation and forward, or derive
    from it and overwrite. If the Remove/AddEventListener methods are
    overwritten, make sure StateChange is adapted, too.
 */
class SvxAccessibleTextHelper
{

public:
    /** Create accessible text object for given edit source

        @param rInterface
        A reference to our interface. This is needed, since we are not
        necessarily the actual interface object (e.g. if we're just
        aggregated).

        @param pEditSource
        The edit source to use. Object ownership is transferred from
        the caller to the callee. The object listens on the
        SvxEditSource for object disposal, so no provisions have to be
        taken if the caller destroys the data (e.g. the model)
        contained in the given SvxEditSource.

        @param rViewWindow
        The window of the view this accessibility object is on.

     */
    SvxAccessibleTextHelper( const ::com::sun::star::uno::Reference< ::com::sun::star::accessibility::XAccessible >&    rInterface,
                             ::std::auto_ptr< SvxEditSource >                                                                   pEditSource );
    virtual ~SvxAccessibleTextHelper();

protected:

    // declared, but not defined
    SvxAccessibleTextHelper( const SvxAccessibleTextHelper& );
    // declared, but not defined
    SvxAccessibleTextHelper& operator= ( const SvxAccessibleTextHelper& );

public:
    /// Query the current edit source
    virtual SvxEditSource& GetEditSource() const throw (::com::sun::star::uno::RuntimeException);

    /** Set the current edit source

        @attention Might fire state change events, therefore, don't
        hold any mutex except solar mutex, which you are required to
        lock before. This method should only be called from the main
        office thread.

        The EditSource set here is required to broadcast out the
        following hints: EDITSOURCE_HINT_PARASMOVED,
        EDITSOURCE_HINT_SELECTIONCHANGED, TEXT_HINT_MODIFIED,
        TEXT_HINT_PARAINSERTED, TEXT_HINT_PARAREMOVED,
        TEXT_HINT_TEXTHEIGHTCHANGED,
        TEXT_HINT_VIEWSCROLLED. Otherwise, not all state changes will
        get noticed by the accessibility object. Further more, when
        the corresponding core object or the model is dying, either
        the edit source must be set to NULL or it has to broadcast a
        SFX_HINT_DYING hint.

        @param pEditSource
        The new edit source to set. Object ownership is transferred
        from the caller to the callee.
     */
    virtual void SetEditSource( ::std::auto_ptr< SvxEditSource > pEditSource ) throw (::com::sun::star::uno::RuntimeException);

    /** Set offset of EditEngine/Outliner from parent

        If the origin of the underlying EditEngine/Outliner does not
        correspond to the upper left corner of the object using this
        class, you have to specify the offset.

        @attention Might fire state change events, therefore, don't
        hold any mutex except solar mutex, which you are required to
        lock before. This method should only be called from the main
        office thread.

        @param rPoint
        The offset in screen coordinates (i.e. pixel)
     */
    virtual void SetOffset( const Point& rPoint );

    /** Query offset of EditEngine/Outliner from parent

        @return the offset in screen coordinates (i.e. pixel)
     */
    virtual const Point& GetOffset() const;

    /** Update the visible children

        @attention Might fire state change events, therefore, don't
        hold any mutex except solar mutex, which you are required to
        lock before. This method should only be called from the main
        office thread.

        This method reevaluates the visibility of all childrens. Call
        this method if your visibility state has changed somehow,
        e.g. if the visible area has changed and the
        SvxAccessibleTextHelper isn't notified internally. Normally,
        there should not be a need to call this method.
     */
    virtual void UpdateChildren() throw (::com::sun::star::uno::RuntimeException);

    /** Call this method to invoke all event listeners with the given event

        @attention Fires state change events, therefore, don't hold any mutex

        @param nEventId
        Id of the event to send, @see AccessibleEventId

        @param rNewValue
        The value we've changed into

        @param rOldValue
        The old value before the change
     */
    virtual void StateChangeEvent( const sal_Int16 nEventId,
                                   const ::com::sun::star::uno::Any& rNewValue = ::com::sun::star::uno::Any(),
                                   const ::com::sun::star::uno::Any& rOldValue = ::com::sun::star::uno::Any() ) const;

    /** Query select state of the text managed by this object

        @return sal_True, if the text or parts of it are currently selected
     */
    virtual sal_Bool IsSelected() const;

    // XAccessibleContext child handling methods
    //-----------------------------------------------------------------
    /** Implements getAccessibleChildCount

        @attention Don't call with locked mutexes
     */
    virtual sal_Int32 GetChildCount() throw (::com::sun::star::uno::RuntimeException);
    /** Implements getAccessibleChild

        @attention Don't call with locked mutexes
     */
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::accessibility::XAccessible > GetChild( sal_Int32 i ) throw (::com::sun::star::lang::IndexOutOfBoundsException, ::com::sun::star::uno::RuntimeException);

    // XAccessibleEventBroadcaster child related methods
    //-----------------------------------------------------------------
    /** Implements addEventListener

        @attention Don't call with locked mutexes
     */
    virtual void AddEventListener( const ::com::sun::star::uno::Reference< ::com::sun::star::accessibility::XAccessibleEventListener >& xListener ) throw (::com::sun::star::uno::RuntimeException);
    /** Implements removeEventListener

        @attention Don't call with locked mutexes
     */
    virtual void RemoveEventListener( const ::com::sun::star::uno::Reference< ::com::sun::star::accessibility::XAccessibleEventListener >& xListener ) throw (::com::sun::star::uno::RuntimeException);

    // XAccessibleComponent child related methods
    //-----------------------------------------------------------------
    /** Implements getAccessibleAt

        @attention Don't call with locked mutexes
     */
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::accessibility::XAccessible > SAL_CALL GetAt( const ::com::sun::star::awt::Point& aPoint ) throw (::com::sun::star::uno::RuntimeException);

private:

    /// @dyn
    const std::auto_ptr< SvxAccessibleTextHelper_Impl > mpImpl;

};

}//end of namespace binfilter
#endif /* _SVX_UNOEDACC_HXX_ */
