/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svx_unoedacc.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 11:47:08 $
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

#ifdef _MSC_VER
#pragma hdrstop
#endif

//------------------------------------------------------------------------
//
// Global header
//
//------------------------------------------------------------------------

#include <limits.h>
#include <vector>
#include <algorithm>

#ifndef _VOS_MUTEX_HXX_
#include <vos/mutex.hxx>
#endif

#ifndef _SV_WINDOW_HXX
#include <vcl/window.hxx>
#endif

#ifndef _SV_SVAPP_HXX
#include <vcl/svapp.hxx>
#endif

#ifndef _COM_SUN_STAR_UNO_ANY_HXX_
#include <com/sun/star/uno/Any.hxx>
#endif

#ifndef _COM_SUN_STAR_UNO_REFERENCE_HXX_
#include <com/sun/star/uno/Reference.hxx>
#endif

#ifndef _CPPUHELPER_WEAKREF_HXX_
#include <cppuhelper/weakref.hxx>
#endif

#ifndef _CPPUHELPER_IMPLBASE6_HXX_
#include <cppuhelper/implbase6.hxx>
#endif

#ifndef _CPPUHELPER_TYPEPROVIDER_HXX_
#include <cppuhelper/typeprovider.hxx>
#endif

#ifndef _COM_SUN_STAR_AWT_POINT_HPP_
#include <com/sun/star/awt/Point.hpp>
#endif

#ifndef _COM_SUN_STAR_AWT_RECTANGLE_HPP_
#include <com/sun/star/awt/Rectangle.hpp>
#endif

#ifndef _COM_SUN_STAR_LANG_XCOMPONENT_HPP_
#include <com/sun/star/lang/XComponent.hpp>
#endif

#ifndef _COM_SUN_STAR_ACCESSIBILITY_ACCESSIBLEEVENTID_HPP_
#include <com/sun/star/accessibility/AccessibleEventId.hpp>
#endif

#ifndef _COM_SUN_STAR_ACCESSIBILITY_XACCESSIBLE_HPP_
#include <com/sun/star/accessibility/XAccessible.hpp>
#endif

#ifndef _COM_SUN_STAR_ACCESSIBILITY_XACCESSIBLECONTEXT_HPP_
#include <com/sun/star/accessibility/XAccessibleContext.hpp>
#endif

#ifndef _COM_SUN_STAR_ACCESSIBILITY_XACCESSIBLECOMPONENT_HPP_
#include <com/sun/star/accessibility/XAccessibleComponent.hpp>
#endif

#ifndef _COM_SUN_STAR_ACCESSIBILITY_ACCESSIBLEROLE_HPP_
#include <com/sun/star/accessibility/AccessibleRole.hpp>
#endif

#ifndef _COM_SUN_STAR_ACCESSIBILITY_ACCESSIBLETEXTTYPE_HPP_
#include <com/sun/star/accessibility/AccessibleTextType.hpp>
#endif

#ifndef _COM_SUN_STAR_ACCESSIBILITY_XACCESSIBLETEXT_HPP_
#include <com/sun/star/accessibility/XAccessibleText.hpp>
#endif

#ifndef _COM_SUN_STAR_ACCESSIBILITY_XACCESSIBLEEDITABLETEXT_HPP_
#include <com/sun/star/accessibility/XAccessibleEditableText.hpp>
#endif

#ifndef _COM_SUN_STAR_ACCESSIBILITY_ACCESSIBLESTATETYPE_HPP_
#include <com/sun/star/accessibility/AccessibleStateType.hpp>
#endif

#ifndef _UTL_ACCESSIBLESTATESETHELPER_HXX_
#include <unotools/accessiblestatesethelper.hxx>
#endif

//------------------------------------------------------------------------
//
// Project-local header
//
//------------------------------------------------------------------------

#ifndef _SVX_UNOEDACC_HXX_
#include "unoedacc.hxx"
#endif

#ifndef _SVX_UNOSHAPE_HXX
#include "unoshape.hxx"
#endif

#ifndef _UNO_LINGU_HXX
#include "unolingu.hxx"
#endif

#ifndef _SVX_UNOTEXT_HXX
#include "unotext.hxx"
#endif

#include "unoedhlp.hxx"
#include "svdmodel.hxx"
#include "svdpntv.hxx"
#include "editdata.hxx"
#include "editeng.hxx"
#include "editview.hxx"
namespace binfilter {

using namespace ::com::sun::star;


//------------------------------------------------------------------------
//
// Local helper classes for weak object references plus implementation
//
//------------------------------------------------------------------------

// is returned by WeakChild::get() and contains a hard reference
// and a reference to the c++ object. This combination prevents
// the c++ object from destruction during usage. Hold this object
// only as long as absolutely necessary, prevents paragraph object
// from vanishing otherwise
template < class UnoType, class CppType > class HardCppRef
{
public:

    typedef UnoType UnoInterfaceType;
    typedef CppType InterfaceType;

    HardCppRef( const uno::WeakReference< UnoInterfaceType >& xRef, InterfaceType* rPara ) :
        mxRef( xRef ),
        mpPara( rPara )
    {
    }

    sal_Bool is() const { return mxRef.is(); }
    InterfaceType* operator->() const { return mpPara; }
    uno::Reference< UnoInterfaceType >& getRef() { return mxRef; }

    // default copy constructor and assignment will do
    // HardCppRef( const HardCppRef& );
    // HardCppRef& operator= ( const HardCppRef& );

private:

    // the interface, hard reference to prevent object from vanishing
    uno::Reference< UnoInterfaceType >  mxRef;

    // the c++ object, for our internal stuff
    InterfaceType*                      mpPara;

};

// combine a weak reference (to facilitate automatic object
// disposal if user drops last reference to children) and hard
// reference to the c++ class (for fast access and bypassing of
// the UNO interface, which is needed e.g. for notifications)
template < class UnoType, class CppType > class WeakCppRef
{
public:

    typedef UnoType UnoInterfaceType;
    typedef CppType InterfaceType;
    typedef HardCppRef< UnoInterfaceType, InterfaceType >  HardRefType;

    WeakCppRef() : maWeakRef(), maUnsafeRef( NULL ) {}
    WeakCppRef( InterfaceType& rPara ) :
        maWeakRef( uno::Reference< UnoInterfaceType >( rPara, uno::UNO_QUERY ) ),
        maUnsafeRef( &rPara )
    {
    }

    WeakCppRef( HardRefType& rPara ) :
        maWeakRef( rPara.getRef() ),
        maUnsafeRef( rPara.operator->() )
    {
    }

    // get object with c++ object and hard reference (which
    // prevents the c++ object from destruction during use)
    HardRefType get() const { return HardRefType( maWeakRef, maUnsafeRef ); }

    // default copy constructor and assignment will do
    // WeakCppRef( const WeakCppRef& );
    // WeakCppRef& operator= ( const WeakCppRef& );

private:

    // the interface, hold weakly
    uno::WeakReference< UnoInterfaceType >  maWeakRef;

    // hard ref to c++ class, _only_ valid if maWeakRef.is() is true
    InterfaceType*                          maUnsafeRef;
};


class SvxAccessibleTextIndex
{
public:
    SvxAccessibleTextIndex() :
        mnIndex(0),
        mnEEIndex(0),
        mnFieldOffset(0),
        mbInField(sal_False),
        mnFieldLen(0),
        mnBulletOffset(0),
        mbInBullet(sal_False),
        mnBulletLen(0) {};
    ~SvxAccessibleTextIndex() {};

    /** Set the index in the UAA semantic

        @param nIndex
         The index from the UA API (fields and bullets are expanded)
     */
    void SetIndex( sal_Int32 nIndex ) { mnIndex = nIndex; }
    sal_Int32 GetIndex() const { return mnIndex; }

    /** Set the index in the edit engine semantic

        @param nEEIndex
         The index from the edit engine (fields span exactly one index increment)
     */
    void SetEEIndex( sal_Int32 nEEIndex )
    {
        mnEEIndex = nEEIndex;
        DBG_ASSERT(nEEIndex >= 0 && nEEIndex <= USHRT_MAX,
                   "SvxAccessibleTextIndex::SetEEIndex: index overflow");
    }
    sal_Int32 GetEEIndex() const { return mnEEIndex; }

    void SetFieldOffset( sal_Int32 nOffset, sal_Int32 nLen ) { mnFieldOffset = nOffset; mnFieldLen = nLen; }
    sal_Int32 GetFieldOffset() const { return mnFieldOffset; }
    sal_Int32 GetFieldLen() const { return mnFieldLen; }
    void AreInField( sal_Bool bInField = sal_True ) { mbInField = bInField; }
    sal_Bool InField() const { return mbInField; }

    void SetBulletOffset( sal_Int32 nOffset, sal_Int32 nLen ) { mnBulletOffset = nOffset; mnBulletLen = nLen; }
    sal_Int32 GetBulletOffset() const { return mnBulletOffset; }
    sal_Int32 GetBulletLen() const { return mnBulletLen; }
    void AreInBullet( sal_Bool bInBullet = sal_True ) { mbInBullet = bInBullet; }
    sal_Bool InBullet() const { return mbInBullet; }

    /// returns false if the current index contains non-editable text (e.g. bullets)
    sal_Bool IsEditable() const;

    /// returns false if the given range is non-editable (e.g. contains bullets or _parts_ of fields)
    sal_Bool IsEditableRange( const SvxAccessibleTextIndex& rEnd ) const;

private:
    sal_Int32 mnIndex;
    sal_Int32 mnEEIndex;
    sal_Int32 mnFieldOffset;
    sal_Int32 mnFieldLen;
    sal_Bool  mbInField;
    sal_Int32 mnBulletOffset;
    sal_Int32 mnBulletLen;
    sal_Bool  mbInBullet;
};

sal_Bool SvxAccessibleTextIndex::IsEditable() const
{
    if( InBullet() || InField() )
        return sal_False;

    return sal_True;
}

sal_Bool SvxAccessibleTextIndex::IsEditableRange( const SvxAccessibleTextIndex& rEnd ) const
{
    if( GetIndex() > rEnd.GetIndex() )
        return rEnd.IsEditableRange( *this );

    if( InBullet() || rEnd.InBullet() )
        return sal_False;

    if( InField() && GetFieldOffset() )
        return sal_False; // within field

    if( rEnd.InField() && rEnd.GetFieldOffset() >= rEnd.GetFieldLen() - 1 )
        return sal_False; // within field

    return sal_True;
}

//------------------------------------------------------------------------
//
// SvxAccessibleEditableTextPara declaration
//
//------------------------------------------------------------------------

typedef ::cppu::WeakImplHelper6< accessibility::XAccessible,
                                 accessibility::XAccessibleContext,
                                 accessibility::XAccessibleComponent,
                                 accessibility::XAccessibleEditableText,
                                 accessibility::XAccessibleEventBroadcaster,
                                 lang::XServiceInfo >  SvxTextParaInterfaceBase;

class SvxAccessibleEditableTextPara :   public SvxTextParaInterfaceBase
{

public:
    /// Create accessible object for given text shape and AccesibleRole
    SvxAccessibleEditableTextPara ( const uno::Reference< accessibility::XAccessible >& rParent );

    virtual ~SvxAccessibleEditableTextPara  ();

    // XInterface
    virtual uno::Any SAL_CALL queryInterface (const uno::Type & rType) throw (uno::RuntimeException);

    // XAccessible
    virtual uno::Reference< accessibility::XAccessibleContext > SAL_CALL getAccessibleContext(  ) throw (uno::RuntimeException);

    // XAccessibleContext
    virtual sal_Int32 SAL_CALL getAccessibleChildCount() throw (uno::RuntimeException);
    virtual uno::Reference< accessibility::XAccessible > SAL_CALL getAccessibleChild( sal_Int32 i ) throw (lang::IndexOutOfBoundsException, uno::RuntimeException);
    virtual uno::Reference< accessibility::XAccessible > SAL_CALL getAccessibleParent() throw (uno::RuntimeException);
    virtual sal_Int32 SAL_CALL getAccessibleIndexInParent() throw (uno::RuntimeException);
    virtual sal_Int16 SAL_CALL getAccessibleRole() throw (uno::RuntimeException);
    /// Maximal length of text returned by getAccessibleDescription()
    enum { MaxDescriptionLen = 40 };
    virtual ::rtl::OUString SAL_CALL getAccessibleDescription() throw (uno::RuntimeException);
    virtual ::rtl::OUString SAL_CALL getAccessibleName() throw (uno::RuntimeException);
    virtual uno::Reference< accessibility::XAccessibleRelationSet > SAL_CALL getAccessibleRelationSet() throw (uno::RuntimeException);
    virtual uno::Reference< accessibility::XAccessibleStateSet > SAL_CALL getAccessibleStateSet() throw (uno::RuntimeException);
    virtual lang::Locale SAL_CALL getLocale() throw (accessibility::IllegalAccessibleComponentStateException, uno::RuntimeException);

    // XAccessibleEventBroadcaster
    virtual void SAL_CALL addEventListener( const uno::Reference< accessibility::XAccessibleEventListener >& xListener ) throw (uno::RuntimeException);
    virtual void SAL_CALL removeEventListener( const uno::Reference< accessibility::XAccessibleEventListener >& xListener ) throw (uno::RuntimeException);

    // XAccessibleComponent
    virtual sal_Bool SAL_CALL containsPoint( const awt::Point& aPoint ) throw (uno::RuntimeException);
    virtual uno::Reference< accessibility::XAccessible > SAL_CALL getAccessibleAtPoint( const awt::Point& aPoint ) throw (uno::RuntimeException);
    virtual awt::Rectangle SAL_CALL getBounds(  ) throw (uno::RuntimeException);
    virtual awt::Point SAL_CALL getLocation(  ) throw (uno::RuntimeException);
    virtual awt::Point SAL_CALL getLocationOnScreen(  ) throw (uno::RuntimeException);
    virtual awt::Size SAL_CALL getSize(  ) throw (uno::RuntimeException);
    virtual sal_Bool SAL_CALL isShowing(  ) throw (uno::RuntimeException);
    virtual sal_Bool SAL_CALL isVisible(  ) throw (uno::RuntimeException);
    virtual sal_Bool SAL_CALL isFocusTraversable(  ) throw (uno::RuntimeException);
    virtual void SAL_CALL addFocusListener( const uno::Reference< awt::XFocusListener >& xListener ) throw (uno::RuntimeException);
    virtual void SAL_CALL removeFocusListener( const uno::Reference< awt::XFocusListener >& xListener ) throw (uno::RuntimeException);
    virtual void SAL_CALL grabFocus(  ) throw (uno::RuntimeException);
    virtual uno::Any SAL_CALL getAccessibleKeyBinding(  ) throw (uno::RuntimeException);

    // XAccessibleText (this comes implicitely inherited by XAccessibleEditableText)
    virtual sal_Int32 SAL_CALL getCaretPosition() throw (uno::RuntimeException);
    virtual sal_Unicode SAL_CALL getCharacter( sal_Int32 nIndex ) throw (lang::IndexOutOfBoundsException, uno::RuntimeException);
    virtual uno::Sequence< beans::PropertyValue > SAL_CALL getCharacterAttributes( sal_Int32 nIndex, const ::com::sun::star::uno::Sequence< ::rtl::OUString >getCharacterAttributes( sal_Int32 nIndex ) aRequestedAttributes ) throw (lang::IndexOutOfBoundsException, uno::RuntimeException);
    virtual awt::Rectangle SAL_CALL getCharacterBounds( sal_Int32 nIndex ) throw (lang::IndexOutOfBoundsException, uno::RuntimeException);
    virtual sal_Int32 SAL_CALL getCharacterCount() throw (uno::RuntimeException);
    virtual sal_Int32 SAL_CALL getIndexAtPoint( const awt::Point& aPoint ) throw (uno::RuntimeException);
    virtual ::rtl::OUString SAL_CALL getSelectedText() throw (uno::RuntimeException);
    virtual sal_Int32 SAL_CALL getSelectionStart() throw (uno::RuntimeException);
    virtual sal_Int32 SAL_CALL getSelectionEnd() throw (uno::RuntimeException);
    virtual sal_Bool SAL_CALL setSelection( sal_Int32 nStartIndex, sal_Int32 nEndIndex ) throw (lang::IndexOutOfBoundsException, uno::RuntimeException);
    virtual ::rtl::OUString SAL_CALL getText() throw (uno::RuntimeException);
    virtual ::rtl::OUString SAL_CALL getTextRange( sal_Int32 nStartIndex, sal_Int32 nEndIndex ) throw (lang::IndexOutOfBoundsException, uno::RuntimeException);
    /// Does not support AccessibleTextType::SENTENCE (missing feature in EditEngine)
    virtual ::com::sun::star::accessibility::TextSegment SAL_CALL getTextAtIndex( sal_Int32 nIndex, sal_Int16 aTextType ) throw (::com::sun::star::lang::IndexOutOfBoundsException, ::com::sun::star::lang::IllegalArgumentException, ::com::sun::star::uno::RuntimeException);
    /// Does not support AccessibleTextType::SENTENCE (missing feature in EditEngine)
    virtual ::com::sun::star::accessibility::TextSegment SAL_CALL getTextBeforeIndex( sal_Int32 nIndex, sal_Int16 aTextType ) throw (::com::sun::star::lang::IndexOutOfBoundsException, ::com::sun::star::lang::IllegalArgumentException, ::com::sun::star::uno::RuntimeException);
    /// Does not support AccessibleTextType::SENTENCE (missing feature in EditEngine)
    virtual ::com::sun::star::accessibility::TextSegment SAL_CALL getTextBehindIndex( sal_Int32 nIndex, sal_Int16 aTextType ) throw (::com::sun::star::lang::IndexOutOfBoundsException, ::com::sun::star::lang::IllegalArgumentException, ::com::sun::star::uno::RuntimeException);
    virtual sal_Bool SAL_CALL copyText( sal_Int32 nStartIndex, sal_Int32 nEndIndex ) throw (lang::IndexOutOfBoundsException, uno::RuntimeException);

    // XAccessibleEditableText
    virtual sal_Bool SAL_CALL cutText( sal_Int32 nStartIndex, sal_Int32 nEndIndex ) throw (lang::IndexOutOfBoundsException, uno::RuntimeException);
    virtual sal_Bool SAL_CALL pasteText( sal_Int32 nIndex ) throw (lang::IndexOutOfBoundsException, uno::RuntimeException);
    virtual sal_Bool SAL_CALL deleteText( sal_Int32 nStartIndex, sal_Int32 nEndIndex ) throw (lang::IndexOutOfBoundsException, uno::RuntimeException);
    virtual sal_Bool SAL_CALL insertText( const ::rtl::OUString& sText, sal_Int32 nIndex ) throw (lang::IndexOutOfBoundsException, uno::RuntimeException);
    virtual sal_Bool SAL_CALL replaceText( sal_Int32 nStartIndex, sal_Int32 nEndIndex, const ::rtl::OUString& sReplacement ) throw (lang::IndexOutOfBoundsException, uno::RuntimeException);
    virtual sal_Bool SAL_CALL setAttributes( sal_Int32 nStartIndex, sal_Int32 nEndIndex, const uno::Sequence< beans::PropertyValue >& aAttributeSet ) throw (lang::IndexOutOfBoundsException, uno::RuntimeException);
    virtual sal_Bool SAL_CALL setText( const ::rtl::OUString& sText ) throw (uno::RuntimeException);

    // XServiceInfo
    virtual ::rtl::OUString SAL_CALL getImplementationName (void) throw (uno::RuntimeException);
    virtual sal_Bool SAL_CALL supportsService (const ::rtl::OUString& sServiceName) throw (uno::RuntimeException);
    virtual uno::Sequence< ::rtl::OUString> SAL_CALL getSupportedServiceNames (void) throw (uno::RuntimeException);

    // XServiceName
    virtual ::rtl::OUString SAL_CALL getServiceName (void) throw (uno::RuntimeException);

    /** Set the current index in the accessibility parent
     *
     *  @attention This method does not lock the SolarMutex, leaving
     *  that to the calling code. This is because only there potential
     *  deadlock situations can be resolved. Thus, make sure
     *  SolarMutex is locked when calling this.
     */
    void SetIndexInParent( sal_Int32 nIndex ) { mnIndexInParent = nIndex; }

    /** Get the current selection of this paragraph
     *
     *  @return sal_False, if nothing in this paragraph is selected
     */
    sal_Bool GetSelection( USHORT& nStartPos, USHORT& nEndPos ) throw (uno::RuntimeException);

    /** Get the current index in the accessibility parent
     *
     *  @attention This method does not lock the SolarMutex, leaving
     *  that to the calling code. This is because only there potential
     *  deadlock situations can be resolved. Thus, make sure
     *  SolarMutex is locked when calling this.
     */
    sal_Int32 GetIndexInParent() const { return mnIndexInParent; }

    /** Set the current paragraph number
     *
     *  @attention This method does not lock the SolarMutex, leaving
     *  that to the calling code. This is because only there potential
     *  deadlock situations can be resolved. Thus, make sure
     *  SolarMutex is locked when calling this.
     */
    void SetParagraphIndex( sal_Int32 nIndex );

    /** Query the current paragraph number (0 - nParas-1)
     *
     *  @attention This method does not lock the SolarMutex, leaving
     *  that to the calling code. This is because only there potential
     *  deadlock situations can be resolved. Thus, make sure
     *  SolarMutex is locked when calling this.
     */
    sal_Int32 GetParagraphIndex() const throw (uno::RuntimeException) { return mnParagraphIndex; }

    /** Set the edit source
     *
     *  @attention This method does not lock the SolarMutex, leaving
     *  that to the calling code. This is because only there potential
     *  deadlock situations can be resolved. Thus, make sure
     *  SolarMutex is locked when calling this.
     */
    void SetEEOffset( const Point& rOffset ) { maEEOffset = rOffset; }

    /** Set the EditEngine offset
     *
     *  @attention This method does not lock the SolarMutex, leaving
     *  that to the calling code. This is because only there potential
     *  deadlock situations can be resolved. Thus, make sure
     *  SolarMutex is locked when calling this.
     */
    void SetEditSource( SvxEditSource* pEditSource );

    /// Calls all Listener objects to tell them the change. Don't hold locks when calling this!
    virtual void StateChangeEvent(const sal_Int16 nEventId, const uno::Any& rNewValue = uno::Any(), const uno::Any& rOldValue = uno::Any() ) const;

private:

    // declared, but not defined
    SvxAccessibleEditableTextPara( const SvxAccessibleEditableTextPara& );
    SvxAccessibleEditableTextPara& operator= ( const SvxAccessibleEditableTextPara& );

    /** Convert between edit engine indices and position in text string
     *
     *  @param nEEIndex
     *  The index from the edit engine (fields span exactly one index increment)
     *
     *  @attention This method does not lock the SolarMutex, leaving
     *  that to the calling code. This is because only there potential
     *  deadlock situations can be resolved. Thus, make sure
     *  SolarMutex is locked when calling this.
     *
     *  @return the index as a position in the text string
     */
    SvxAccessibleTextIndex EEIndex2CharIndex( sal_Int32 nEEIndex ) const;

    /** Convert between position in text string and edit engine indices
     *
     *  @param nCharIndex
     *  The index as a position in the text string
     *
     *  @return the index in the edit engine semantics (fields span exactly one index increment)
     */
    SvxAccessibleTextIndex CharIndex2EEIndex( sal_Int32 nCharIndex ) const;

    /// Internal text range getter, working on already processed indices
    String GetTextRange( SvxAccessibleTextIndex aStartIndex, SvxAccessibleTextIndex aEndIndex ) throw (uno::RuntimeException);
    String GetTextRangeWithBullets( sal_Int32 nStartIndex, sal_Int32 nEndIndex ) throw (uno::RuntimeException);
    String GetText( SvxAccessibleTextIndex aIndex ) throw (uno::RuntimeException);
    String GetTextRange( sal_Int32 nStartIndex, sal_Int32 nEndIndex ) throw (uno::RuntimeException);

    /// Internal text len getter, returning EditEngine lengths
    USHORT GetTextLen() const throw (uno::RuntimeException);

    /** Query the visibility state
     *
     *  @attention This method does not lock the SolarMutex, leaving
     *  that to the calling code. This is because only there potential
     *  deadlock situations can be resolved. Thus, make sure
     *  SolarMutex is locked when calling this.
     *
     *  @return the visibility state. Per definition, a defunc object is no longer visible
     */
    sal_Bool IsVisible() const { return mpEditSource ? sal_True : sal_False ; }

    /** Query the SvxTextForwarder for EditEngine access.
     *
     *  @attention This method does not lock the SolarMutex, leaving
     *  that to the calling code. This is because only there potential
     *  deadlock situations can be resolved. Thus, make sure
     *  SolarMutex is locked when calling this.
     */
    SvxTextForwarder&   GetTextForwarder() const throw (uno::RuntimeException);

    /** Query the SvxViewForwarder for EditEngine access.
     *
     *  @attention This method does not lock the SolarMutex, leaving
     *  that to the calling code. This is because only there potential
     *  deadlock situations can be resolved. Thus, make sure
     *  SolarMutex is locked when calling this.
     */
    SvxViewForwarder&   GetViewForwarder() const throw (uno::RuntimeException);

    /** Query the SvxEditViewForwarder for EditEngine access.
     *
     *  @attention This method does not lock the SolarMutex, leaving
     *  that to the calling code. This is because only there potential
     *  deadlock situations can be resolved. Thus, make sure
     *  SolarMutex is locked when calling this.
     */
    SvxEditViewForwarder&   GetEditViewForwarder( sal_Bool bCreate = sal_False ) const throw (uno::RuntimeException);

    /// Do we have children? This is the case for image bullets
    sal_Bool HaveChildren();

    /** Query whether a GetEditViewForwarder( sal_False ) will return a forwarder
     *
     *  @attention This method does not lock the SolarMutex, leaving
     *  that to the calling code. This is because only there potential
     *  deadlock situations can be resolved. Thus, make sure
     *  SolarMutex is locked when calling this.
     */
    sal_Bool    HaveEditView() const;

    /// Is the underlying object in edit mode
    sal_Bool IsActive() const throw (uno::RuntimeException);

    SvxEditSource& GetEditSource() const throw (uno::RuntimeException);
    const Point& GetEEOffset() const { return maEEOffset; }

    /// check whether index value is within permitted range
    void CheckIndex( sal_Int32 nIndex ) throw (lang::IndexOutOfBoundsException, uno::RuntimeException);
    void CheckPosition( sal_Int32 nIndex ) throw (lang::IndexOutOfBoundsException, uno::RuntimeException);
    void CheckRange( sal_Int32 nStart, sal_Int32 nEnd ) throw (lang::IndexOutOfBoundsException, uno::RuntimeException);

    /** create EditEngine selection from Accessible selection.

        @attention the indices given must already be in edit engine format (converted with CharIndex2EEIndex)
     */
    ESelection  MakeEESelection( sal_Int32 nStartEEIndex, sal_Int32 nEndEEIndex );
    ESelection  MakeEESelection( sal_Int32 nEEIndex );

    // the paragraph index in the edit engine (guarded by solar mutex)
    sal_Int32   mnParagraphIndex;

    // our current index in the parent (guarded by solar mutex)
    sal_Int32   mnIndexInParent;

    // the current edit source (guarded by solar mutex)
    SvxEditSource* mpEditSource;

    // the offset of the underlying EditEngine from the shape/cell
    Point maEEOffset;

    mutable osl::Mutex  maMutex;

    /// The shape we're the accessible for (guarded by maMutex)
    uno::Reference< accessibility::XAccessible > mxParent;

    /// Our listeners (guarded by maMutex)
    ::cppu::OInterfaceContainerHelper maStateListeners;
};

//------------------------------------------------------------------------
//
// SvxAccessibleTextPropertySet declaration
//
//------------------------------------------------------------------------

/**
 * Wraps SvxUnoTextRangeBase and provides us with the text properties
 *
 * Inherits from SvxUnoTextRangeBase and provides XPropertySet and
 * XMultiPropertySet interfaces. Just set the selection to the
 * required text range and return a reference to a XPropertySet.
 */
class SvxAccessibleTextPropertySet : public SvxUnoTextRangeBase,
                                     public lang::XTypeProvider,
                                     public ::cppu::OWeakObject
{
public:
    SvxAccessibleTextPropertySet( const SvxEditSource*, const SfxItemPropertyMap* );
    virtual ~SvxAccessibleTextPropertySet() throw();

    // XTextRange
    virtual uno::Reference< text::XText > SAL_CALL getText() throw (uno::RuntimeException);

    // uno::XInterface
    virtual uno::Any SAL_CALL queryAggregation( const uno::Type & rType ) throw(uno::RuntimeException);
    virtual uno::Any SAL_CALL queryInterface( const uno::Type & rType ) throw(uno::RuntimeException);
    virtual void SAL_CALL acquire() throw();
    virtual void SAL_CALL release() throw();

    // lang::XServiceInfo
    virtual ::rtl::OUString SAL_CALL getImplementationName() throw(uno::RuntimeException);
    virtual sal_Bool SAL_CALL supportsService( const ::rtl::OUString& ) throw (uno::RuntimeException);
    virtual uno::Sequence< ::rtl::OUString > SAL_CALL getSupportedServiceNames() throw (uno::RuntimeException);

    // lang::XTypeProvider
    virtual uno::Sequence< uno::Type > SAL_CALL getTypes() throw(uno::RuntimeException);
    virtual uno::Sequence< sal_Int8 > SAL_CALL getImplementationId() throw(uno::RuntimeException);

    // XServiceName
    ::rtl::OUString SAL_CALL SvxAccessibleTextPropertySet::getServiceName() throw (uno::RuntimeException);
};


//------------------------------------------------------------------------
//
// SvxAccessibleTextPropertySet implementation
//
//------------------------------------------------------------------------

SvxAccessibleTextPropertySet::SvxAccessibleTextPropertySet( const SvxEditSource* pEditSrc, const SfxItemPropertyMap* pPropMap )
    : SvxUnoTextRangeBase( pEditSrc, pPropMap )
{
}

SvxAccessibleTextPropertySet::~SvxAccessibleTextPropertySet() throw()
{
}

uno::Reference< text::XText > SAL_CALL SvxAccessibleTextPropertySet::getText() throw (uno::RuntimeException)
{
  // TODO (empty?)
  return uno::Reference< text::XText > ();
}

uno::Any SAL_CALL SvxAccessibleTextPropertySet::queryAggregation( const uno::Type & rType ) throw(uno::RuntimeException)
{
  // TODO (empty?)
  return uno::Any();
}

uno::Any SAL_CALL SvxAccessibleTextPropertySet::queryInterface( const uno::Type & rType )
    throw(uno::RuntimeException)
{
    return OWeakObject::queryInterface(rType);
}

void SAL_CALL SvxAccessibleTextPropertySet::acquire()
    throw()
{
    OWeakObject::acquire();
}

void SAL_CALL SvxAccessibleTextPropertySet::release()
    throw()
{
    OWeakObject::release();
}

// XTypeProvider
uno::Sequence< uno::Type > SAL_CALL SvxAccessibleTextPropertySet::getTypes() throw ( uno::RuntimeException )
{
    static ::cppu::OTypeCollection* pTypeCollection = NULL ;

    // double-checked locking pattern.
    if ( pTypeCollection == NULL )
    {
        osl::MutexGuard aGuard( osl::Mutex::getGlobalMutex() ) ;

        // Control these pointer again ... it can be, that another instance will be faster then these!
        if ( pTypeCollection == NULL )
        {
            // Create a static typecollection ...
            static ::cppu::OTypeCollection aTypeCollection(
                ::getCppuType( static_cast< const uno::Reference< beans::XPropertySet >* > (0) ),
                ::getCppuType( static_cast< const uno::Reference< beans::XMultiPropertySet >* > (0) ),
                ::getCppuType( static_cast< const uno::Reference< beans::XPropertyState >* > (0) ),
                ::getCppuType( static_cast< const uno::Reference< lang::XServiceInfo >* > (0) ),
                ::getCppuType( static_cast< const uno::Reference< lang::XTypeProvider >* > (0) ) );

            // ... and set his address to static pointer!
            pTypeCollection = &aTypeCollection ;
        }
    }

    return pTypeCollection->getTypes() ;
}

uno::Sequence< sal_Int8 > SAL_CALL SvxAccessibleTextPropertySet::getImplementationId()
    throw (uno::RuntimeException)
{
    static uno::Sequence< sal_Int8 > aId;
    if( aId.getLength() == 0 )
    {
        aId.realloc( 16 );
        rtl_createUuid( reinterpret_cast< sal_uInt8* > (aId.getArray()), 0, sal_True );
    }
    return aId;
}

// XServiceInfo
::rtl::OUString SAL_CALL SAL_CALL SvxAccessibleTextPropertySet::getImplementationName (void) throw (uno::RuntimeException)
{
    return ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM ("SvxAccessibleTextPropertySet"));
}

sal_Bool SAL_CALL SvxAccessibleTextPropertySet::supportsService (const ::rtl::OUString& sServiceName) throw (uno::RuntimeException)
{
    //  Iterate over all supported service names and return true if on of them
    //  matches the given name.
    uno::Sequence< ::rtl::OUString> aSupportedServices (
        getSupportedServiceNames ());
    for (int i=0; i<aSupportedServices.getLength(); i++)
        if (sServiceName == aSupportedServices[i])
            return sal_True;
    return sal_False;
}

uno::Sequence< ::rtl::OUString> SAL_CALL SvxAccessibleTextPropertySet::getSupportedServiceNames (void) throw (uno::RuntimeException)
{
    // TODO
    return SvxUnoTextRangeBase::getSupportedServiceNames();
}

// XServiceName
::rtl::OUString SAL_CALL SvxAccessibleTextPropertySet::getServiceName() throw (uno::RuntimeException)
{
    return ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.beans.PropertyValue"));
}


//------------------------------------------------------------------------
//
// SvxAccessibleTextHelper_Impl declaration
//
//------------------------------------------------------------------------

class SvxAccessibleStringWrap
{
public:

    SvxAccessibleStringWrap( OutputDevice& rDev, SvxFont& rFont, const String& rText );

    sal_Bool GetCharacterBounds( sal_Int32 nIndex, Rectangle& rRect );
    sal_Int32 GetIndexAtPoint( const Point& rPoint );

private:

    OutputDevice&       mrDev;
    SvxFont&            mrFont;
    String              maText;
};

SvxAccessibleStringWrap::SvxAccessibleStringWrap( OutputDevice& rDev, SvxFont& rFont, const String& rText ) :
    mrDev( rDev ),
    mrFont( rFont ),
    maText( rText )
{
}

sal_Bool SvxAccessibleStringWrap::GetCharacterBounds( sal_Int32 nIndex, Rectangle& rRect )
{
    DBG_ASSERT(nIndex >= 0 && nIndex <= USHRT_MAX,
               "SvxAccessibleStringWrap::GetCharacterBounds: index value overflow");

    rRect.Left()   = 0;
    rRect.Top()    = 0;
    rRect.SetSize( mrFont.GetPhysTxtSize( &mrDev, maText.Copy(static_cast< USHORT >(nIndex), 1) ) );

    if( nIndex > 0 )
    {
        // TODO: CTL, BiDi
        Size aOffset = mrFont.GetPhysTxtSize( &mrDev, maText.Copy(0, static_cast< USHORT >(nIndex) ) );
        rRect.Move( aOffset.Width(), 0 );
    }

    return sal_True;
}

sal_Int32 SvxAccessibleStringWrap::GetIndexAtPoint( const Point& rPoint )
{
    // search for character bounding box containing given point
    Rectangle aRect;
    sal_Int32 i, nLen = maText.Len();
    for( i=0; i<nLen; ++i )
    {
        GetCharacterBounds(i, aRect);
        if( aRect.IsInside(rPoint) )
            return i;
    }

    return -1;
}


//------------------------------------------------------------------------
//
// SvxAccessibleTextHelper_Impl declaration
//
//------------------------------------------------------------------------

class SvxAccessibleTextHelper_Impl : public SfxListener
{

public:

    // receive pointer to our frontend class and view window
    SvxAccessibleTextHelper_Impl( const uno::Reference< accessibility::XAccessible >& rInterface );
    ~SvxAccessibleTextHelper_Impl();

    // XAccessibleContext child handling methods
    sal_Int32 SAL_CALL getAccessibleChildCount() throw (uno::RuntimeException);
    uno::Reference< accessibility::XAccessible > SAL_CALL getAccessibleChild( sal_Int32 i ) throw (lang::IndexOutOfBoundsException, uno::RuntimeException);

    // XAccessibleEventBroadcaster child related methods
    void SAL_CALL addEventListener( const uno::Reference< accessibility::XAccessibleEventListener >& xListener ) throw (uno::RuntimeException);
    void SAL_CALL removeEventListener( const uno::Reference< accessibility::XAccessibleEventListener >& xListener ) throw (uno::RuntimeException);

    // XAccessibleComponent child related methods
    uno::Reference< accessibility::XAccessible > SAL_CALL getAccessibleAtPoint( const awt::Point& aPoint ) throw (uno::RuntimeException);

    SvxEditSource& GetEditSource() const throw (uno::RuntimeException);
    void ShutdownEditSource() throw (uno::RuntimeException);
    void SetEditSource( ::std::auto_ptr< SvxEditSource > pEditSource ) throw (uno::RuntimeException);

    void SetOffset( const Point& );
    const Point& GetOffset() const { return maOffset; } // Strictly correct only with locked solar mutex!

    sal_Bool IsSelected() const;

    // do NOT hold object mutex when calling this! Danger of deadlock
    void StateChangeEvent( const sal_Int16 nEventId, const uno::Any& rNewValue = uno::Any(), const uno::Any& rOldValue = uno::Any() ) const;
    void StateChangeEvent( sal_Int32 nParagraph, const sal_Int16 nEventId, const uno::Any& rNewValue = uno::Any(), const uno::Any& rOldValue = uno::Any() ) const;

#ifdef DBG_UTIL
    void CheckInvariants() const;
#endif

    // checks all children for visibility, throws away invisible ones
    void UpdateVisibleChildren();

    virtual void Notify( SfxBroadcaster& rBC, const SfxHint& rHint );

    static Rectangle LogicToPixel( const Rectangle& rRect, const MapMode& rMapMode, SvxViewForwarder& rForwarder );

private:

    // lock solar mutex before
    SvxTextForwarder& GetTextForwarder() const throw (uno::RuntimeException);
    // lock solar mutex before
    SvxViewForwarder& GetViewForwarder() const throw (uno::RuntimeException);
    // lock solar mutex before
    SvxEditViewForwarder& GetEditViewForwarder( sal_Bool bCreate = sal_False ) const throw (uno::RuntimeException);

    // are we in edit mode?
    sal_Bool IsActive() const throw (uno::RuntimeException);

    // forward new edit engine offset to all our children
    void SetChildrenEEOffset( const Point& rOffset );

    // forward new edit source to all our children
    void SetChildrenEditSource( SvxEditSource* pEditSource );

    // for given range of paragraphs (0..numParagraphs), set current index in child
    void UpdateParagraphIndices( sal_Int32 nStart, sal_Int32 nAfterEnd ) const;

    // calls SetSelection on the forwarder and updates maLastSelection
    // cache. Caution: calls StateChangeEvent and sets object into
    // edit mode!
    void UpdateSelection( const ESelection& );

    /// our current edit source (guarded by solar mutex) @dyn
    ::std::auto_ptr< SvxEditSource > mpEditSource;

    /// our current offset to the containing shape/cell (guarded by solar mutex)
    Point maOffset;

    /// do we have a functional (i.e. not shut down) edit source
    sal_Bool mbHaveEditSource;

    // our frontend class (the one implementing the actual
    // interface). That's not necessarily the one containing the impl
    // pointer!
    const uno::Reference< accessibility::XAccessible > mxFrontEnd;

    // store last selection (to correctly report selection changes, guarded by solar mutex)
    ESelection maLastSelection;

    // cache range of visible children (guarded by solar mutex)
    mutable sal_Int32 mnFirstVisibleChild;
    mutable sal_Int32 mnLastVisibleChild;

    // vector the size of the paragraph number of the underlying EditEngine (guarded by solar mutex)
    typedef WeakCppRef < accessibility::XAccessible, SvxAccessibleEditableTextPara > WeakChildren;
    typedef ::std::vector< WeakChildren > VectorOfChildren;
    VectorOfChildren maChildren;

    // must be before maStateListeners, has to live longer
    mutable ::osl::Mutex maMutex;

    // handles our event listeners (guarded by maMutex)
    ::cppu::OInterfaceContainerHelper maStateListeners;

};

//------------------------------------------------------------------------
//
// SvxAccessibleTextHelper_Impl implementation
//
//------------------------------------------------------------------------

SvxAccessibleTextHelper_Impl::SvxAccessibleTextHelper_Impl( const uno::Reference< accessibility::XAccessible >&     rInterface ) :
    mpEditSource( NULL ),
    maOffset(0,0),
    mbHaveEditSource(sal_False),
    mxFrontEnd( rInterface ),
    maLastSelection( 0,0,0,0 ),
    mnFirstVisibleChild( -1 ),
    mnLastVisibleChild( -2 ),
    maStateListeners( maMutex )
{
}

SvxAccessibleTextHelper_Impl::~SvxAccessibleTextHelper_Impl()
{
    ::vos::OGuard aGuard( Application::GetSolarMutex() );

    try
    {
        // shutdown and release edit source
        SetEditSource( ::std::auto_ptr< SvxEditSource >() );
    }
    catch( const uno::RuntimeException& ) {}

    // owner is responsible for dispose and clear on listeners
}

SvxTextForwarder& SvxAccessibleTextHelper_Impl::GetTextForwarder() const throw (uno::RuntimeException)
{
    if( !mbHaveEditSource )
        throw uno::RuntimeException(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("Edit source was shut down")), mxFrontEnd);

    if( !mpEditSource.get() )
        throw uno::RuntimeException(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("Unknown edit source")), mxFrontEnd);

    SvxTextForwarder* pTextForwarder = mpEditSource->GetTextForwarder();

    if( !pTextForwarder )
        throw uno::RuntimeException(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("Unable to fetch text forwarder, model might be dead")), mxFrontEnd);

    if( pTextForwarder->IsValid() )
        return *pTextForwarder;
    else
        throw uno::RuntimeException(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("Text forwarder is invalid, model might be dead")), mxFrontEnd);
}

SvxViewForwarder& SvxAccessibleTextHelper_Impl::GetViewForwarder() const throw (uno::RuntimeException)
{
    if( !mbHaveEditSource )
        throw uno::RuntimeException(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("Edit source was shut down")), mxFrontEnd);

    if( !mpEditSource.get() )
        throw uno::RuntimeException(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("Unknown edit source")), mxFrontEnd);

    SvxViewForwarder* pViewForwarder = mpEditSource->GetViewForwarder();

    if( !pViewForwarder )
        throw uno::RuntimeException(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("Unable to fetch view forwarder, model might be dead")), mxFrontEnd);

    if( pViewForwarder->IsValid() )
        return *pViewForwarder;
    else
        throw uno::RuntimeException(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("View forwarder is invalid, model might be dead")), mxFrontEnd);
}

SvxEditViewForwarder& SvxAccessibleTextHelper_Impl::GetEditViewForwarder( sal_Bool bCreate ) const throw (uno::RuntimeException)
{
    if( !mbHaveEditSource )
        throw uno::RuntimeException(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("Edit source was shut down")), mxFrontEnd);

    if( !mpEditSource.get() )
        throw uno::RuntimeException(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("Unknown edit source")), mxFrontEnd);

    SvxEditViewForwarder* pViewForwarder = mpEditSource->GetEditViewForwarder( bCreate );

    if( !pViewForwarder )
    {
        if( bCreate )
            throw uno::RuntimeException(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("Unable to fetch edit view forwarder, model might be dead")), mxFrontEnd);
        else
            throw uno::RuntimeException(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("No edit view forwarder, object not in edit mode")), mxFrontEnd);
    }

    if( pViewForwarder->IsValid() )
        return *pViewForwarder;
    else
    {
        if( bCreate )
            throw uno::RuntimeException(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("View forwarder is invalid, model might be dead")), mxFrontEnd);
        else
            throw uno::RuntimeException(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("View forwarder is invalid, object not in edit mode")), mxFrontEnd);
    }
}

SvxEditSource& SvxAccessibleTextHelper_Impl::GetEditSource() const throw (uno::RuntimeException)
{
    if( !mbHaveEditSource )
        throw uno::RuntimeException(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("Edit source was shut down")), mxFrontEnd);

    if( mpEditSource.get() )
        return *mpEditSource.get();
    else
        throw uno::RuntimeException(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("SvxAccessibleTextHelper_Impl::GetEditSource: no edit source")), mxFrontEnd );
}

sal_Bool SvxAccessibleTextHelper_Impl::IsSelected() const
{
    sal_Bool bRet = sal_False;

    try
    {
        ESelection aSelection;
        bRet = GetEditViewForwarder().GetSelection( aSelection );
    }
    catch( const uno::RuntimeException& )
    {
    }

    return bRet;
}

sal_Bool SvxAccessibleTextHelper_Impl::IsActive() const throw (uno::RuntimeException)
{
    SvxEditSource& rEditSource = GetEditSource();
    SvxEditViewForwarder* pViewForwarder = rEditSource.GetEditViewForwarder();

    if( !pViewForwarder )
        return sal_False;

    if( pViewForwarder->IsValid() )
        return sal_True;
    else
        return sal_False;
}

void SvxAccessibleTextHelper_Impl::UpdateSelection( const ESelection& rSelection )
{
    if( maLastSelection.IsEqual( rSelection ) )
    {
        // notify all affected paragraphs (TODO: may be suboptimal,
        // since paragraphs might stay selected)

        // calc paragraph range loosing selection:
        USHORT nStart;
        USHORT nEnd;
        if( rSelection.nStartPara > maLastSelection.nStartPara )
            nStart = maLastSelection.nStartPara;
        else
            nStart = rSelection.nStartPara;

        if( rSelection.nEndPara > maLastSelection.nEndPara )
            nEnd = rSelection.nEndPara;
        else
            nEnd = maLastSelection.nEndPara;

        USHORT i;
        for( i=nStart; i<nEnd; ++i )
            StateChangeEvent( i, accessibility::AccessibleEventId::SELECTION_CHANGED );

        maLastSelection = rSelection;
    }
}

void SvxAccessibleTextHelper_Impl::SetChildrenEditSource( SvxEditSource* pEditSource )
{
    // WARNING: this can only be done without locking, if this method
    // is called exclusively from places where solar mutex is locked!
    VectorOfChildren::iterator aChildIter( maChildren.begin() );
    VectorOfChildren::iterator aChildIterLast( maChildren.end() );
    while( aChildIter != aChildIterLast )
    {
        // retrieve hard reference
        WeakChildren::HardRefType maChild( aChildIter->get() );
        if( maChild.is() )
        {
            maChild->SetEditSource( pEditSource );
        }

        ++aChildIter;
    }
}

void SvxAccessibleTextHelper_Impl::SetChildrenEEOffset( const Point& rOffset )
{
    // WARNING: this can only be done without locking, if this method
    // is called exclusively from places where solar mutex is locked!
    VectorOfChildren::iterator aChildIter( maChildren.begin() );
    VectorOfChildren::iterator aChildIterLast( maChildren.end() );
    while( aChildIter != aChildIterLast )
    {
        // retrieve hard reference
        WeakChildren::HardRefType maChild( aChildIter->get() );
        if( maChild.is() )
        {
            maChild->SetEEOffset( rOffset );
        }

        ++aChildIter;
    }
}

void SvxAccessibleTextHelper_Impl::ShutdownEditSource() throw (uno::RuntimeException)
{
    // This should only be called with solar mutex locked, i.e. from the main office thread

    // invalidate children
    SetChildrenEditSource( NULL );

    maChildren.clear();

    // quit listen on stale edit source
    if( mpEditSource.get() )
        EndListening( mpEditSource->GetBroadcaster() );

    mbHaveEditSource = sal_False;
}

void SvxAccessibleTextHelper_Impl::SetEditSource( ::std::auto_ptr< SvxEditSource > pEditSource ) throw (uno::RuntimeException)
{
    // This should only be called with solar mutex locked, i.e. from the main office thread

    // shutdown old edit source
    ShutdownEditSource();

    // set new edit source
    mpEditSource = pEditSource;

    // init child vector to the current child count
    if( mpEditSource.get() )
    {
        mbHaveEditSource = sal_True;

        maChildren.resize( GetTextForwarder().GetParagraphCount() );

        // listen on new edit source
        StartListening( mpEditSource->GetBroadcaster() );

        UpdateVisibleChildren();
    }

    // notify listeners. TODO: with some effort, might also be feasible
    // to retain children if not too much has changed.
    StateChangeEvent( accessibility::AccessibleEventId::CHILD );
    StateChangeEvent( accessibility::AccessibleEventId::TEXT_CHANGED );
}

void SvxAccessibleTextHelper_Impl::SetOffset( const Point& rPoint )
{
    maOffset = rPoint;
    SetChildrenEEOffset( rPoint );

    // in all cases, check visibility afterwards.
    UpdateVisibleChildren();
}

void SvxAccessibleTextHelper_Impl::UpdateVisibleChildren()
{
    try
    {
        SvxTextForwarder& rCacheTF = GetTextForwarder();
        SvxViewForwarder& rCacheVF = GetViewForwarder();

        Rectangle aViewArea = rCacheVF.GetVisArea();

        if( IsActive() )
        {
            // maybe the edit view scrolls, adapt aViewArea
            Rectangle aEditViewArea = GetEditViewForwarder().GetVisArea();
            aViewArea += aEditViewArea.TopLeft();

            // now determine intersection
            aViewArea.Intersection( aEditViewArea );
        }

        Rectangle aTmpBB, aParaBB;
        sal_Int32 nCurrPara, nLastVisible = -2;
        sal_Int32 nParas=rCacheTF.GetParagraphCount();
        sal_Int32 nFirstVisible = -1;
        for( nCurrPara=0; nCurrPara<nParas; ++nCurrPara )
        {
            DBG_ASSERT(nCurrPara >= 0 && nCurrPara <= USHRT_MAX,
                       "SvxAccessibleTextHelper_Impl::UpdateVisibleChildren: index value overflow");

            aTmpBB = rCacheTF.GetParaBounds( static_cast< USHORT >( nCurrPara ) );

            // convert to screen coordinates
            aParaBB = SvxAccessibleTextHelper_Impl::LogicToPixel( aTmpBB, rCacheTF.GetMapMode(), rCacheVF );

            if( aParaBB.IsOver( aViewArea ) )
            {
                // at least partially visible
                if( nFirstVisible < 0 )
                    nFirstVisible = nCurrPara;

                nLastVisible = nCurrPara;
            }
            else
            {
                // not or no longer visible, destroy if living

                // retrieve hard reference
                WeakChildren::HardRefType maChild( maChildren[ nCurrPara ].get() );
                if( maChild.is() )
                {
                    // make child defunct
                    maChild->SetEditSource( NULL );
                }

                // clear reference
                maChildren[ nCurrPara ] = WeakChildren();
            }
        }

        if( mnFirstVisibleChild != nFirstVisible ||
            mnLastVisibleChild != nLastVisible )
        {
            // notify listeners
            StateChangeEvent( accessibility::AccessibleEventId::CHILD );
        }

        // update caches
        mnFirstVisibleChild = nFirstVisible;
        mnLastVisibleChild = nLastVisible;
    }
    catch( const uno::RuntimeException& )
    {
        DBG_ERROR("SvxAccessibleTextHelper_Impl::UpdateVisibleChildren error while determining visible children");

        if( mnFirstVisibleChild != -1 || mnLastVisibleChild != -2 )
        {
            // notify listeners
            StateChangeEvent( accessibility::AccessibleEventId::CHILD );
        }

        // something failed - currently no children
        mnFirstVisibleChild = -1;
        mnLastVisibleChild = -2;
    }
}

void SvxAccessibleTextHelper_Impl::UpdateParagraphIndices( sal_Int32 nStart, sal_Int32 nAfterEnd ) const
{
    sal_Int32 nCurrPara;
    for( nCurrPara=nStart; nCurrPara < nAfterEnd; ++nCurrPara )
    {
        // change child index
        WeakChildren::HardRefType maChild( maChildren[ nCurrPara ].get() );
        if( maChild.is() )
        {
            maChild->SetParagraphIndex(nCurrPara);

            // is this paragraph visible?
            if( nCurrPara >= mnFirstVisibleChild &&
                nCurrPara <= mnLastVisibleChild )
            {
                // if we're the nParaIndex paragraph and the first visible one
                // is mnFirstVisibleChild, the index is:
                maChild->SetIndexInParent( nCurrPara - mnFirstVisibleChild );
            }
        }
    }
}

#ifdef DBG_UTIL
void SvxAccessibleTextHelper_Impl::CheckInvariants() const
{
    ::vos::OGuard aGuard( Application::GetSolarMutex() );

    if( !mxFrontEnd.is() )
        DBG_ERROR( "SvxAccessibleTextHelper: no frontend" );

    if( mnFirstVisibleChild >= 0 &&
        mnFirstVisibleChild > mnLastVisibleChild )
    {
        DBG_ERROR( "SvxAccessibleTextHelper: range invalid" );
    }

    try
    {
        sal_Int32 nCurrPara;
        sal_Int32 nParas = GetTextForwarder().GetParagraphCount();

        for( nCurrPara=0; nCurrPara < nParas; ++nCurrPara )
        {
            WeakChildren::HardRefType maChild( maChildren[ nCurrPara ].get() );
            if( maChild.is() && maChild.operator->() != NULL )
            {
                if( nCurrPara < mnFirstVisibleChild ||
                    nCurrPara > mnLastVisibleChild )
                {
                    DBG_ERROR( "SvxAccessibleTextHelper: valid children outside visible area" );
                }

                if( maChild->GetParagraphIndex() != nCurrPara )
                    DBG_ERROR( "SvxAccessibleTextHelper: child has wrong paragraph index" );

                if( maChild->GetIndexInParent() + mnFirstVisibleChild != nCurrPara )
                    DBG_ERROR( "SvxAccessibleTextHelper: child has wrong parent index" );
            }
        }
    }
    catch( const uno::RuntimeException& )
    {
    }
}
#endif

void SvxAccessibleTextHelper_Impl::Notify( SfxBroadcaster& rBC, const SfxHint& rHint )
{
    const SfxSimpleHint* pSimpleHint = PTR_CAST( SfxSimpleHint, &rHint );
    const TextHint* pTextHint = PTR_CAST( TextHint, &rHint );
    const SvxViewHint* pViewHint = PTR_CAST( SvxViewHint, &rHint );
    const SvxEditSourceHint* pEditSourceHint = PTR_CAST( SvxEditSourceHint, &rHint );

    try
    {
        // precondition: solar mutex locked
        if( pEditSourceHint )
        {
            if( pEditSourceHint->GetValue() < GetTextForwarder().GetParagraphCount() )
            {
                switch( pEditSourceHint->GetId() )
                {
                    case EDITSOURCE_HINT_PARASMOVED:
                    {
                        DBG_ASSERT( pEditSourceHint->GetStartValue() < GetTextForwarder().GetParagraphCount() &&
                                    pEditSourceHint->GetEndValue() < GetTextForwarder().GetParagraphCount(),
                                    "SvxAccessibleTextHelper_Impl::NotifyHdl: Invalid notification");

                        const sal_Int32 nParas = GetTextForwarder().GetParagraphCount();

                        // rotate paragraphs
                        VectorOfChildren::iterator aChildIter_First( maChildren.begin() );
                        VectorOfChildren::iterator aChildIter_Middle( maChildren.begin() );
                        VectorOfChildren::iterator aChildIter_Last( maChildren.begin() );
                        sal_Int32 nFirst, nMiddle, nLast;

                        /* Three cases:
                         *
                         * 1.
                         *   ... nParagraph ... nParam1 ... nParam2 ...
                         *       |______________[xxxxxxxxxxx]
                         *              becomes
                         *       [xxxxxxxxxxx]|______________
                         *
                         * tail is 0
                         *
                         * 2.
                         *   ... nParam1 ... nParagraph ... nParam2 ...
                         *       [xxxxxxxxxxx|xxxxxxxxxxxxxx]____________
                         *              becomes
                         *       ____________[xxxxxxxxxxx|xxxxxxxxxxxxxx]
                         *
                         * tail is nParagraph - nParam1
                         *
                         * 3.
                         *   ... nParam1 ... nParam2 ... nParagraph ...
                         *       [xxxxxxxxxxx]___________|____________
                         *              becomes
                         *       ___________|____________[xxxxxxxxxxx]
                         *
                         * tail is nParam2 - nParam1
                         */

                        // sort nParagraph, nParam1 and nParam2 in ascending order, calc range
                        if( pEditSourceHint->GetValue() < pEditSourceHint->GetStartValue() )
                        {
                            nFirst = pEditSourceHint->GetValue();
                            nMiddle = pEditSourceHint->GetStartValue();
                            nLast = pEditSourceHint->GetEndValue();
                        }
                        else if( pEditSourceHint->GetValue() < pEditSourceHint->GetEndValue() )
                        {
                            nFirst = pEditSourceHint->GetStartValue();
                            nMiddle = pEditSourceHint->GetValue();
                            nLast = pEditSourceHint->GetEndValue() + nMiddle - nFirst;
                        }
                        else
                        {
                            nFirst = pEditSourceHint->GetStartValue();
                            nMiddle = pEditSourceHint->GetEndValue();
                            nLast = pEditSourceHint->GetValue() + nMiddle - nFirst;
                        }

                        if( nFirst < nParas && nMiddle < nParas && nLast < nParas )
                        {
                            aChildIter_First += nFirst;
                            aChildIter_Middle += nMiddle;
                            aChildIter_Last += nLast;
                            ::std::rotate< VectorOfChildren::iterator > ( aChildIter_First, aChildIter_Middle, aChildIter_Last );
                        }
#ifdef DBG_UTIL
                        else
                        {
                            DBG_ERROR("SvxAccessibleTextHelper_Impl::NotifyHdl: Invalid move ranges");
                        }
#endif

                        // update para index
                        UpdateParagraphIndices( nFirst, nLast+1 );

                        // notify listeners
                        StateChangeEvent( accessibility::AccessibleEventId::CHILD );
                        break;
                    }

                    case EDITSOURCE_HINT_SELECTIONCHANGED:
                        // notify listeners
                        ESelection aSelection;
                        try
                        {
                            if( GetEditViewForwarder().GetSelection( aSelection ) )
                                UpdateSelection( aSelection );
                        }
                        catch( const uno::RuntimeException& ) {}

                        UpdateSelection( aSelection );
                        break;
                }

                // in all cases, check visibility afterwards.
                UpdateVisibleChildren();
            }
#ifdef DBG_UTIL
            else
            {
                DBG_ERROR("SvxAccessibleTextHelper_Impl::NotifyHdl: Invalid notification");
            }
#endif
        }
        else if( pTextHint )
        {
            if( pTextHint->GetValue() < GetTextForwarder().GetParagraphCount() )
            {
                switch( pTextHint->GetId() )
                {
                    case TEXT_HINT_MODIFIED:
                        // notify listeners
                        StateChangeEvent( pTextHint->GetValue(), accessibility::AccessibleEventId::TEXT_CHANGED );
                        break;

                    case TEXT_HINT_PARAINSERTED:
                    {
                        // resize child vector to the current child count
                        const sal_Int32 nParas = GetTextForwarder().GetParagraphCount();

                        maChildren.resize( nParas );

                        // move successors of inserted paragraph one position further
                        VectorOfChildren::reverse_iterator aReversedChildIter_Source( maChildren.rbegin() );
                        VectorOfChildren::reverse_iterator aReversedChildIter_Dest( maChildren.rbegin() );

                        const sal_Int32 nParas2Move = nParas - pTextHint->GetValue() - 1;

                        if( nParas2Move > 0 )
                        {
                            --aReversedChildIter_Source;
                            ::std::copy_n< VectorOfChildren::reverse_iterator, sal_Int32, VectorOfChildren::reverse_iterator > ( aReversedChildIter_Source,
                                                                                                                                 nParas2Move,
                                                                                                                                 aReversedChildIter_Dest );
                            // update para index
                            UpdateParagraphIndices( pTextHint->GetValue()+1, nParas );
                        }

                        // notify listeners
                        StateChangeEvent( accessibility::AccessibleEventId::CHILD );
                        break;
                    }

                    case TEXT_HINT_PARAREMOVED:
                    {
                        const sal_Int32 nParas = GetTextForwarder().GetParagraphCount();

                        // move successors of removed paragraph one position closer
                        VectorOfChildren::const_iterator aChildIter_Source( maChildren.begin() );
                        VectorOfChildren::iterator aChildIter_Dest( maChildren.begin() );

                        const sal_Int32 nParas2Move = nParas - pTextHint->GetValue() - 1;

                        if( nParas2Move > 0 )
                        {
                            aChildIter_Source += pTextHint->GetValue()+1;
                            aChildIter_Dest += pTextHint->GetValue();
                            ::std::copy_n< VectorOfChildren::const_iterator, sal_Int32, VectorOfChildren::iterator > ( aChildIter_Source,
                                                                                                                       nParas2Move,
                                                                                                                       aChildIter_Dest );
                            // update para index
                            UpdateParagraphIndices( pTextHint->GetValue(), nParas-1 );
                        }

                        // resize child vector to the current child count
                        maChildren.resize( nParas );

                        // notify listeners
                        StateChangeEvent( accessibility::AccessibleEventId::CHILD );
                        break;
                    }

                    case TEXT_HINT_TEXTHEIGHTCHANGED:
                        // just check visibility
                        break;

                    case TEXT_HINT_VIEWSCROLLED:
                        // just check visibility
                        break;
                }

                // in all cases, check visibility afterwards.
                UpdateVisibleChildren();
            }
#ifdef DBG_UTIL
            else
            {
                DBG_ERROR("SvxAccessibleTextHelper_Impl::NotifyHdl: Invalid notification");

            }
#endif
        }
        else if( pViewHint )
        {
            switch( pViewHint->GetId() )
            {
                case SVX_HINT_VIEWCHANGED:
                    // just check visibility
                    break;
            }

            // in all cases, check visibility afterwards.
            UpdateVisibleChildren();
        }
        // it's VITAL to keep the SfxSimpleHint last! It's the base of some classes above!
        else if( pSimpleHint )
        {
            switch( pSimpleHint->GetId() )
            {
                case SFX_HINT_DYING:
                    // edit source is dying under us, become defunc then
                    try
                    {
                        // make edit source inaccessible
                        // Note: cannot destroy it here, since we're called from there!
                        ShutdownEditSource();
                    }
                    catch( const uno::RuntimeException& ) {}

                    break;
            }
        }
    }
    catch( const uno::RuntimeException& )
    {
#ifdef DBG_UTIL
        DBG_ERROR("SvxAccessibleTextHelper_Impl::Notify: Unhandled exception.");
#endif
    }
}

Rectangle SvxAccessibleTextHelper_Impl::LogicToPixel( const Rectangle& rRect, const MapMode& rMapMode, SvxViewForwarder& rForwarder )
{
    // convert to screen coordinates
    return Rectangle( rForwarder.LogicToPixel( rRect.TopLeft(), rMapMode ),
                      rForwarder.LogicToPixel( rRect.BottomRight(), rMapMode ) );
}

void SvxAccessibleTextHelper_Impl::StateChangeEvent( const sal_Int16 nEventId, const uno::Any& rNewValue, const uno::Any& rOldValue ) const
{
// -- object locked --
    ::osl::ClearableMutexGuard aGuard( maMutex );

    accessibility::AccessibleEventObject aEvent(mxFrontEnd, nEventId, rNewValue, rOldValue);

    ::cppu::OInterfaceIteratorHelper aIter( const_cast< SvxAccessibleTextHelper_Impl* >(this)->maStateListeners );

    // no locking necessary, OInterfaceIteratorHelper copies listeners if someone removes/adds in between
    // Further locking, actually, might lead to deadlocks, since we're calling out of this object
    aGuard.clear();
// -- until here --

    while( aIter.hasMoreElements() )
    {
        uno::Reference < accessibility::XAccessibleEventListener > xListener( aIter.next(), uno::UNO_QUERY );

        if( xListener.is() )
        {
            try
            {
                xListener->notifyEvent( aEvent );
            }
            catch( const uno::RuntimeException& )
            {
#ifdef DBG_UTIL
                DBG_ERROR("SvxAccessibleTextHelper_Impl::StateChangeEvent: Caught runtime exception from listener (bridge/listener dead?).");
#endif
            }
        }
    }
}

void SvxAccessibleTextHelper_Impl::StateChangeEvent( sal_Int32 nParagraph, const sal_Int16 nEventId, const uno::Any& rNewValue, const uno::Any& rOldValue ) const
{
    WeakChildren::HardRefType maChild( maChildren[ nParagraph ].get() );
    if( maChild.is() )
    {
        maChild->StateChangeEvent( nEventId, rNewValue, rOldValue );
    }
}

// XAccessibleContext
sal_Int32 SAL_CALL SvxAccessibleTextHelper_Impl::getAccessibleChildCount() throw (uno::RuntimeException)
{
    ::vos::OGuard aGuard( Application::GetSolarMutex() );

    return mnLastVisibleChild - mnFirstVisibleChild + 1;
}

uno::Reference< accessibility::XAccessible > SAL_CALL SvxAccessibleTextHelper_Impl::getAccessibleChild( sal_Int32 i ) throw (lang::IndexOutOfBoundsException, uno::RuntimeException)
{
    ::vos::OGuard aGuard( Application::GetSolarMutex() );

    if( 0 > i || i > getAccessibleChildCount() ||
        GetTextForwarder().GetParagraphCount() <= i )
    {
        throw lang::IndexOutOfBoundsException(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("Invalid child index")), mxFrontEnd);
    }

    // retrieve hard reference from weak one
    WeakChildren::HardRefType aChild( maChildren[i].get() );

    if( !aChild.is() )
    {
        // there is no hard reference available, create object then
        SvxAccessibleEditableTextPara* pChild = new SvxAccessibleEditableTextPara( mxFrontEnd );
        uno::Reference< accessibility::XAccessible > xChild( static_cast< ::cppu::OWeakObject* > (pChild), uno::UNO_QUERY );

        if( !xChild.is() )
            throw uno::RuntimeException(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("Child creation failed")), mxFrontEnd);

        aChild = WeakChildren::HardRefType( xChild, pChild );

        maChildren[i] = aChild;
        aChild->SetEditSource( &GetEditSource() );
        aChild->SetIndexInParent(i);
        aChild->SetParagraphIndex( mnFirstVisibleChild + i );
    }

    return aChild.getRef();
}

void SAL_CALL SvxAccessibleTextHelper_Impl::addEventListener( const uno::Reference< accessibility::XAccessibleEventListener >& xListener ) throw (uno::RuntimeException)
{
    maStateListeners.addInterface( xListener );
}

void SAL_CALL SvxAccessibleTextHelper_Impl::removeEventListener( const uno::Reference< accessibility::XAccessibleEventListener >& xListener ) throw (uno::RuntimeException)
{
    maStateListeners.removeInterface( xListener );
}

uno::Reference< accessibility::XAccessible > SAL_CALL SvxAccessibleTextHelper_Impl::getAccessibleAtPoint( const awt::Point& _aPoint ) throw (uno::RuntimeException)
{
    // make given position relative
    if( !mxFrontEnd.is() )
        throw uno::RuntimeException(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("SvxAccessibleTextHelper_Impl::getAccessibleAt: frontend invalid")), mxFrontEnd );

    uno::Reference< accessibility::XAccessibleContext > xFrontEndContext = mxFrontEnd->getAccessibleContext();

    if( !xFrontEndContext.is() )
        throw uno::RuntimeException(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("SvxAccessibleTextHelper_Impl::getAccessibleAt: frontend invalid")), mxFrontEnd );

    uno::Reference< accessibility::XAccessibleComponent > xFrontEndComponent( xFrontEndContext, uno::UNO_QUERY );

    if( !xFrontEndComponent.is() )
        throw uno::RuntimeException(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("SvxAccessibleTextHelper_Impl::getAccessibleAt: frontend is no XAccessibleComponent")),
                                    mxFrontEnd );

    Point aPoint( _aPoint.X, _aPoint.Y );
    awt::Point aRefPoint = xFrontEndComponent->getLocationOnScreen();
    aPoint -= Point( aRefPoint.X, aRefPoint.Y );

    // respect EditEngine offset to surrounding shape/cell
    aPoint -= GetOffset();

    // convert to EditEngine coordinate system
    SvxTextForwarder& rCacheTF = GetTextForwarder();
    Point aLogPoint( GetViewForwarder().PixelToLogic( aPoint, rCacheTF.GetMapMode() ) );

    // iterate over all visible children (including those not yet created)
    sal_Int32 nChild;
    for( nChild=mnFirstVisibleChild; nChild <= mnLastVisibleChild; ++nChild )
    {
        DBG_ASSERT(nChild >= 0 && nChild <= USHRT_MAX,
                   "SvxAccessibleTextHelper_Impl::getAccessibleAt: index value overflow");

        Rectangle aParaBounds( rCacheTF.GetParaBounds( static_cast< USHORT > (nChild) ) );

        if( aParaBounds.IsInside( aLogPoint ) )
        {
            DBG_ASSERT(nChild - mnFirstVisibleChild >= 0 && nChild - mnFirstVisibleChild <= USHRT_MAX,
                       "SvxAccessibleTextHelper_Impl::getAccessibleAt: index value overflow");

            return getAccessibleChild( static_cast< USHORT > (nChild - mnFirstVisibleChild) );
        }
    }

    // found none
    return uno::Reference< accessibility::XAccessible >();
}

//------------------------------------------------------------------------
//
// SvxAccessibleTextHelper implementation
//
//------------------------------------------------------------------------

SvxAccessibleTextHelper::SvxAccessibleTextHelper( const uno::Reference< accessibility::XAccessible >&   rInterface,
                                                  ::std::auto_ptr< SvxEditSource >                      pEditSource ) :
    mpImpl( new SvxAccessibleTextHelper_Impl( rInterface ) )
{
    ::vos::OGuard aGuard( Application::GetSolarMutex() );

    SetEditSource( pEditSource );
}

SvxAccessibleTextHelper::~SvxAccessibleTextHelper()
{
}

SvxEditSource& SvxAccessibleTextHelper::GetEditSource() const throw (uno::RuntimeException)
{
#ifdef DBG_UTIL
    mpImpl->CheckInvariants();

    SvxEditSource& aEditSource = mpImpl->GetEditSource();

    mpImpl->CheckInvariants();

    return aEditSource;
#else
    return mpImpl->GetEditSource();
#endif
}

void SvxAccessibleTextHelper::SetEditSource( ::std::auto_ptr< SvxEditSource > pEditSource ) throw (uno::RuntimeException)
{
#ifdef DBG_UTIL
    mpImpl->CheckInvariants();

    mpImpl->SetEditSource( pEditSource );

    mpImpl->CheckInvariants();
#else
    mpImpl->SetEditSource( pEditSource );
#endif
}

void SvxAccessibleTextHelper::StateChangeEvent( const sal_Int16 nEventId, const uno::Any& rNewValue, const uno::Any& rOldValue ) const
{
#ifdef DBG_UTIL
    mpImpl->CheckInvariants();

    mpImpl->StateChangeEvent( nEventId, rNewValue, rOldValue );

    mpImpl->CheckInvariants();
#else
    mpImpl->StateChangeEvent( nEventId, rNewValue, rOldValue );
#endif
}

void SvxAccessibleTextHelper::SetOffset( const Point& rPoint )
{
#ifdef DBG_UTIL
    mpImpl->CheckInvariants();

    mpImpl->SetOffset( rPoint );

    mpImpl->CheckInvariants();
#else
    mpImpl->SetOffset( rPoint );
#endif
}

const Point& SvxAccessibleTextHelper::GetOffset() const
{
#ifdef DBG_UTIL
    mpImpl->CheckInvariants();

    const Point& rRef = mpImpl->GetOffset();

    mpImpl->CheckInvariants();

    return rRef;
#else
    return mpImpl->GetOffset();
#endif
}

void SvxAccessibleTextHelper::UpdateChildren() throw (::com::sun::star::uno::RuntimeException)
{
#ifdef DBG_UTIL
    mpImpl->CheckInvariants();

    mpImpl->UpdateVisibleChildren();

    mpImpl->CheckInvariants();
#else
    mpImpl->UpdateVisibleChildren();
#endif
}

sal_Bool SvxAccessibleTextHelper::IsSelected() const
{
#ifdef DBG_UTIL
    mpImpl->CheckInvariants();

    sal_Bool aRet = mpImpl->IsSelected();

    mpImpl->CheckInvariants();

    return aRet;
#else
    return mpImpl->IsSelected();
#endif
}

// XAccessibleContext
sal_Int32 SvxAccessibleTextHelper::GetChildCount() throw (uno::RuntimeException)
{
#ifdef DBG_UTIL
    mpImpl->CheckInvariants();

    sal_Int32 nRet = mpImpl->getAccessibleChildCount();

    mpImpl->CheckInvariants();

    return nRet;
#else
    return mpImpl->getAccessibleChildCount();
#endif
}

uno::Reference< accessibility::XAccessible > SvxAccessibleTextHelper::GetChild( sal_Int32 i ) throw (lang::IndexOutOfBoundsException, uno::RuntimeException)
{
#ifdef DBG_UTIL
    mpImpl->CheckInvariants();

    uno::Reference< accessibility::XAccessible > xRet = mpImpl->getAccessibleChild( i );

    mpImpl->CheckInvariants();

    return xRet;
#else
    return mpImpl->getAccessibleChild( i );
#endif
}

void SvxAccessibleTextHelper::AddEventListener( const uno::Reference< accessibility::XAccessibleEventListener >& xListener ) throw (uno::RuntimeException)
{
#ifdef DBG_UTIL
    mpImpl->CheckInvariants();

    mpImpl->addEventListener( xListener );

    mpImpl->CheckInvariants();
#else
    mpImpl->addEventListener( xListener );
#endif
}

void SvxAccessibleTextHelper::RemoveEventListener( const uno::Reference< accessibility::XAccessibleEventListener >& xListener ) throw (uno::RuntimeException)
{
#ifdef DBG_UTIL
    mpImpl->CheckInvariants();

    mpImpl->removeEventListener( xListener );

    mpImpl->CheckInvariants();
#else
    mpImpl->removeEventListener( xListener );
#endif
}

// XAccessibleComponent
uno::Reference< accessibility::XAccessible > SvxAccessibleTextHelper::GetAt( const awt::Point& aPoint ) throw (uno::RuntimeException)
{
#ifdef DBG_UTIL
    mpImpl->CheckInvariants();

    uno::Reference< accessibility::XAccessible > xChild = mpImpl->getAccessibleAtPoint( aPoint );

    mpImpl->CheckInvariants();

    return xChild;
#else
    return mpImpl->getAccessibleAtPoint( aPoint );
#endif
}

//------------------------------------------------------------------------
//
// SvxAccessibleEditableTextPara implementation
//
//------------------------------------------------------------------------

SvxAccessibleEditableTextPara::SvxAccessibleEditableTextPara( const uno::Reference< accessibility::XAccessible >& rParent ) :
    mnParagraphIndex( 0 ),
    mnIndexInParent( 0 ),
    mpEditSource( NULL ),
    maEEOffset( 0, 0 ),
    mxParent( rParent ),
    maStateListeners( maMutex )
{
}

SvxAccessibleEditableTextPara::~SvxAccessibleEditableTextPara()
{
}

void SvxAccessibleEditableTextPara::SetParagraphIndex( sal_Int32 nIndex )
{
    sal_Int32 nOldIndex = mnParagraphIndex;

    mnParagraphIndex = nIndex;

    if( nOldIndex != nIndex )
    {
        // index and therefore description changed
        StateChangeEvent( accessibility::AccessibleEventId::DESCRIPTION_CHANGED );

        // index and therefore name changed
        StateChangeEvent( accessibility::AccessibleEventId::NAME_CHANGED );
    }
}

void SvxAccessibleEditableTextPara::SetEditSource( SvxEditSource* pEditSource )
{
    mpEditSource = pEditSource;

    if( !mpEditSource )
    {
        // going defunc
        StateChangeEvent( accessibility::AccessibleEventId::STATE_CHANGED );

        try
        {
            uno::Reference < accessibility::XAccessibleContext > xThis = getAccessibleContext();

            lang::EventObject aEvent (xThis);
            maStateListeners.disposeAndClear( aEvent );
        }
        catch( const uno::RuntimeException& ) {}
    }
}

ESelection SvxAccessibleEditableTextPara::MakeEESelection( sal_Int32 nStartEEIndex, sal_Int32 nEndEEIndex )
{
    // check overflow
    DBG_ASSERT(nStartEEIndex >= 0 && nStartEEIndex <= USHRT_MAX &&
               nEndEEIndex >= 0 && nEndEEIndex <= USHRT_MAX &&
               GetParagraphIndex() >= 0 && GetParagraphIndex() <= USHRT_MAX,
               "SvxAccessibleEditableTextPara::MakeEESelection: index value overflow");

    return ESelection( static_cast< USHORT >( GetParagraphIndex() ), static_cast< USHORT >( nStartEEIndex ),
                       static_cast< USHORT >( GetParagraphIndex() ), static_cast< USHORT >( nEndEEIndex ) );
}

ESelection SvxAccessibleEditableTextPara::MakeEESelection( sal_Int32 nEEIndex )
{
    return MakeEESelection( nEEIndex, nEEIndex+1 );
}

void SvxAccessibleEditableTextPara::CheckIndex( sal_Int32 nIndex ) throw (lang::IndexOutOfBoundsException, uno::RuntimeException)
{
    if( nIndex < 0 || nIndex >= getCharacterCount() )
        throw lang::IndexOutOfBoundsException(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("SvxAccessibleEditableTextPara: character index out of bounds")),
                                              uno::Reference< uno::XInterface >
                                              ( static_cast< ::cppu::OWeakObject* > (this) ) ); // disambiguate hierarchy
}

void SvxAccessibleEditableTextPara::CheckPosition( sal_Int32 nIndex ) throw (lang::IndexOutOfBoundsException, uno::RuntimeException)
{
    if( nIndex < 0 || nIndex > getCharacterCount() )
        throw lang::IndexOutOfBoundsException(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("SvxAccessibleEditableTextPara: character position out of bounds")),
                                              uno::Reference< uno::XInterface >
                                              ( static_cast< ::cppu::OWeakObject* > (this) ) ); // disambiguate hierarchy
}

void SvxAccessibleEditableTextPara::CheckRange( sal_Int32 nStart, sal_Int32 nEnd ) throw (lang::IndexOutOfBoundsException, uno::RuntimeException)
{
    CheckPosition( nStart );
    CheckPosition( nEnd );
}

SvxAccessibleTextIndex SvxAccessibleEditableTextPara::EEIndex2CharIndex( sal_Int32 nEEIndex ) const
{
    SvxTextForwarder&   rCacheTF = GetTextForwarder();
    sal_Int32           nParaIndex = GetParagraphIndex();

    DBG_ASSERT(nParaIndex >= 0 && nParaIndex <= USHRT_MAX,
               "SvxAccessibleEditableTextPara::EEIndex2CharIndex: index value overflow");

    USHORT                  nCurrField, nFieldCount = rCacheTF.GetFieldCount( static_cast< USHORT > (nParaIndex) );
    sal_Int32               nTmp;
    SvxAccessibleTextIndex  aIndex;

    aIndex.SetIndex( nEEIndex );

    EBulletInfo aBulletInfo = GetTextForwarder().GetBulletInfo( static_cast< USHORT >(GetParagraphIndex()) );

    // any text bullets?
    if( aBulletInfo.nParagraph != EE_PARA_NOT_FOUND &&
        aBulletInfo.bVisible &&
        aBulletInfo.nType != SVX_NUM_BITMAP )
    {
        aIndex.SetIndex( aIndex.GetIndex() + aBulletInfo.aText.Len() );
    }

    for( nCurrField=0; nCurrField < nFieldCount; ++nCurrField )
    {
        EFieldInfo aFieldInfo( rCacheTF.GetFieldInfo( static_cast< USHORT > (nParaIndex), nCurrField ) );

        if( aFieldInfo.aPosition.nIndex > nEEIndex )
            return aIndex;

        if( aFieldInfo.aPosition.nIndex == nEEIndex )
        {
            aIndex.AreInField();
            return aIndex;
        }

        // nCharIndex = Max(aFieldInfo.aCurrentText.Len(), 1);
        nTmp = aFieldInfo.aCurrentText.Len();
        aIndex.SetIndex( aIndex.GetIndex() + nTmp > 1 ? nTmp-1 : 0 );
    }

    return aIndex;
}

SvxAccessibleTextIndex SvxAccessibleEditableTextPara::CharIndex2EEIndex( sal_Int32 nIndex ) const
{
    SvxTextForwarder&   rCacheTF = GetTextForwarder();
    sal_Int32           nParaIndex = GetParagraphIndex();

    DBG_ASSERT(nParaIndex >= 0 && nParaIndex <= USHRT_MAX,
               "SvxAccessibleEditableTextPara::CharIndex2EEIndex: index value overflow");

    USHORT                  nCurrField, nFieldCount = rCacheTF.GetFieldCount( static_cast< USHORT > (nParaIndex) );
    sal_Int32               nTmp;
    SvxAccessibleTextIndex  aIndex;

    aIndex.SetEEIndex( nIndex );

    EBulletInfo aBulletInfo = GetTextForwarder().GetBulletInfo( static_cast< USHORT >(GetParagraphIndex()) );

    // any text bullets?
    if( aBulletInfo.nParagraph != EE_PARA_NOT_FOUND &&
        aBulletInfo.bVisible &&
        aBulletInfo.nType != SVX_NUM_BITMAP )
    {
        sal_Int32 nBulletLen = aBulletInfo.aText.Len();

        if( nIndex < nBulletLen )
        {
            aIndex.AreInBullet();
            aIndex.SetBulletOffset( nIndex, nBulletLen );
            return aIndex;
        }

        aIndex.SetEEIndex( aIndex.GetEEIndex() - nBulletLen );
    }

    for( nCurrField=0; nCurrField < nFieldCount; ++nCurrField )
    {
        EFieldInfo aFieldInfo( rCacheTF.GetFieldInfo( static_cast< USHORT > (nParaIndex), nCurrField ) );

        // we're before a field
        if( aFieldInfo.aPosition.nIndex > aIndex.GetEEIndex() )
            break;

        // this is: nEEIndex = Max(aFieldInfo.aCurrentText.Len(), 1);
        nTmp = aFieldInfo.aCurrentText.Len();
        aIndex.SetEEIndex( aIndex.GetEEIndex() - nTmp > 1 ? nTmp : 1 );

        // we're within a field
        if( aFieldInfo.aPosition.nIndex > aIndex.GetEEIndex() )
        {
            aIndex.AreInField();
            aIndex.SetFieldOffset( aFieldInfo.aCurrentText.Len() - aFieldInfo.aPosition.nIndex + aIndex.GetEEIndex(), aFieldInfo.aCurrentText.Len() );
            aIndex.SetEEIndex( aFieldInfo.aPosition.nIndex );
            break;
        }

        // now we're after the field
        aIndex.SetEEIndex( aIndex.GetEEIndex() + 1 );
    }

    return aIndex;
}

String SvxAccessibleEditableTextPara::GetTextRange( sal_Int32 nStartIndex, sal_Int32 nEndIndex ) throw (uno::RuntimeException)
{
    return GetTextForwarder().GetText( MakeEESelection(nStartIndex, nEndIndex) );
}

String SvxAccessibleEditableTextPara::GetTextRangeWithBullets( sal_Int32 nStartIndex, sal_Int32 nEndIndex ) throw (uno::RuntimeException)
{
    EBulletInfo aBulletInfo = GetTextForwarder().GetBulletInfo( static_cast< USHORT >(GetParagraphIndex()) );

    String sStr = GetTextForwarder().GetText( MakeEESelection(nStartIndex, nEndIndex) );

    if( aBulletInfo.nParagraph != EE_PARA_NOT_FOUND &&
        aBulletInfo.bVisible &&
        aBulletInfo.nType != SVX_NUM_BITMAP &&
        nStartIndex == 0 )
    {
        String sBullet = aBulletInfo.aText;

        sBullet += sStr;
        sStr = sBullet;
    }

    return sStr;
}

String SvxAccessibleEditableTextPara::GetTextRange( SvxAccessibleTextIndex aStartIndex, SvxAccessibleTextIndex aEndIndex ) throw (uno::RuntimeException)
{
    String aStr = GetTextRange( aStartIndex.GetEEIndex(), aEndIndex.GetEEIndex() );

    // have to append bullet text?
    if( aStartIndex.GetIndex() > aEndIndex.GetIndex() )
        ::std::swap< SvxAccessibleTextIndex >( aStartIndex, aEndIndex );

    if( aStartIndex.InBullet() )
    {
        EBulletInfo aBulletInfo = GetTextForwarder().GetBulletInfo( static_cast< USHORT >(GetParagraphIndex()) );
        String sBullet = aBulletInfo.aText;

        DBG_ASSERT(aStartIndex.GetBulletOffset() >= 0 && aStartIndex.GetBulletOffset() <= USHRT_MAX &&
                   aEndIndex.GetBulletOffset() >= 0 && aEndIndex.GetBulletOffset() <= USHRT_MAX,
                   "SvxAccessibleEditableTextPara::GetTextRange: index value overflow");

        if( aEndIndex.InBullet() )
        {
            aStr = sBullet.Copy( static_cast< xub_StrLen >(aStartIndex.GetBulletOffset()),
                                 static_cast< xub_StrLen >(aEndIndex.GetBulletOffset()) - static_cast< xub_StrLen >(aStartIndex.GetBulletOffset()) );
        }
        else
        {
            sBullet = sBullet.Copy( static_cast< xub_StrLen >(aStartIndex.GetBulletOffset()) );

            sBullet += aStr;
            aStr = sBullet;
        }
    }

    return aStr;
}

String SvxAccessibleEditableTextPara::GetText( SvxAccessibleTextIndex aIndex ) throw (uno::RuntimeException)
{
    SvxAccessibleTextIndex aEndIndex;

    // prevent access behind EE text. The range returned might
    // actually be non-empty, since e.g. bullet text is before EE
    // index 0
    if( GetTextLen() > 0 )
        aEndIndex.SetEEIndex( aIndex.GetEEIndex() + 1 );
    else
        aEndIndex.SetEEIndex( aIndex.GetEEIndex() );

    return GetTextRange( aIndex, aEndIndex );
}

USHORT SvxAccessibleEditableTextPara::GetTextLen() const throw (uno::RuntimeException)
{
    return GetTextForwarder().GetTextLen( static_cast< USHORT >( GetParagraphIndex() ) );
}

SvxEditSource& SvxAccessibleEditableTextPara::GetEditSource() const throw (uno::RuntimeException)
{
    if( mpEditSource )
        return *mpEditSource;
    else
        throw uno::RuntimeException(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("No edit source, object is defunct")),
                                    uno::Reference< uno::XInterface >
                                    ( static_cast< ::cppu::OWeakObject* >
                                      ( const_cast< SvxAccessibleEditableTextPara* > (this) ) ) );  // disambiguate hierarchy
}

SvxTextForwarder& SvxAccessibleEditableTextPara::GetTextForwarder() const throw (uno::RuntimeException)
{
    SvxEditSource& rEditSource = GetEditSource();
    SvxTextForwarder* pTextForwarder = rEditSource.GetTextForwarder();

    if( !pTextForwarder )
        throw uno::RuntimeException(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("Unable to fetch text forwarder, object is defunct")),
                                    uno::Reference< uno::XInterface >
                                    ( static_cast< ::cppu::OWeakObject* >
                                      ( const_cast< SvxAccessibleEditableTextPara* > (this) ) ) );  // disambiguate hierarchy

    if( pTextForwarder->IsValid() )
        return *pTextForwarder;
    else
        throw uno::RuntimeException(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("Text forwarder is invalid, object is defunct")),
                                    uno::Reference< uno::XInterface >
                                    ( static_cast< ::cppu::OWeakObject* >
                                      ( const_cast< SvxAccessibleEditableTextPara* > (this) ) ) );  // disambiguate hierarchy
}

SvxViewForwarder& SvxAccessibleEditableTextPara::GetViewForwarder() const throw (uno::RuntimeException)
{
    SvxEditSource& rEditSource = GetEditSource();
    SvxViewForwarder* pViewForwarder = rEditSource.GetViewForwarder();

    if( !pViewForwarder )
    {
        throw uno::RuntimeException(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("Unable to fetch view forwarder, object is defunct")),
                                    uno::Reference< uno::XInterface >
                                    ( static_cast< ::cppu::OWeakObject* >
                                      ( const_cast< SvxAccessibleEditableTextPara* > (this) ) ) );  // disambiguate hierarchy
    }

    if( pViewForwarder->IsValid() )
        return *pViewForwarder;
    else
        throw uno::RuntimeException(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("View forwarder is invalid, object is defunct")),
                                    uno::Reference< uno::XInterface >
                                    ( static_cast< ::cppu::OWeakObject* >
                                      ( const_cast< SvxAccessibleEditableTextPara* > (this) )  ) ); // disambiguate hierarchy
}

SvxEditViewForwarder& SvxAccessibleEditableTextPara::GetEditViewForwarder( sal_Bool bCreate ) const throw (uno::RuntimeException)
{
    SvxEditSource& rEditSource = GetEditSource();
    SvxEditViewForwarder* pViewForwarder = rEditSource.GetEditViewForwarder( bCreate );

    if( !pViewForwarder )
    {
        if( bCreate )
            throw uno::RuntimeException(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("Unable to fetch view forwarder, object is defunct")),
                                        uno::Reference< uno::XInterface >
                                        ( static_cast< ::cppu::OWeakObject* >
                                          ( const_cast< SvxAccessibleEditableTextPara* > (this) ) ) );  // disambiguate hierarchy
        else
            throw uno::RuntimeException(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("No view forwarder, object not in edit mode")),
                                        uno::Reference< uno::XInterface >
                                        ( static_cast< ::cppu::OWeakObject* >
                                          ( const_cast< SvxAccessibleEditableTextPara* > (this) ) ) );  // disambiguate hierarchy
    }

    if( pViewForwarder->IsValid() )
        return *pViewForwarder;
    else
    {
        if( bCreate )
            throw uno::RuntimeException(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("View forwarder is invalid, object is defunct")),
                                        uno::Reference< uno::XInterface >
                                        ( static_cast< ::cppu::OWeakObject* >
                                          ( const_cast< SvxAccessibleEditableTextPara* > (this) )  ) ); // disambiguate hierarchy
        else
            throw uno::RuntimeException(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("View forwarder is invalid, object not in edit mode")),
                                        uno::Reference< uno::XInterface >
                                        ( static_cast< ::cppu::OWeakObject* >
                                          ( const_cast< SvxAccessibleEditableTextPara* > (this) )  ) ); // disambiguate hierarchy
    }
}

sal_Bool SvxAccessibleEditableTextPara::HaveEditView() const
{
    SvxEditSource& rEditSource = GetEditSource();
    SvxEditViewForwarder* pViewForwarder = rEditSource.GetEditViewForwarder();

    if( !pViewForwarder )
        return sal_False;

    if( !pViewForwarder->IsValid() )
        return sal_False;

    return sal_True;
}

sal_Bool SvxAccessibleEditableTextPara::HaveChildren()
{
    DBG_ASSERT(GetParagraphIndex() >= 0 && GetParagraphIndex() <= USHRT_MAX,
               "SvxAccessibleEditableTextPara::HaveChildren: paragraph index value overflow");

    EBulletInfo aBulletInfo = GetTextForwarder().GetBulletInfo( static_cast< USHORT >(GetParagraphIndex()) );

    if( aBulletInfo.nParagraph != EE_PARA_NOT_FOUND &&
        aBulletInfo.bVisible &&
        aBulletInfo.nType == SVX_NUM_BITMAP )
    {
        return sal_True;
    }
    else
    {
        return sal_False;
    }
}

sal_Bool SvxAccessibleEditableTextPara::IsActive() const throw (uno::RuntimeException)
{
    SvxEditSource& rEditSource = GetEditSource();
    SvxEditViewForwarder* pViewForwarder = rEditSource.GetEditViewForwarder();

    if( !pViewForwarder )
        return sal_False;

    if( pViewForwarder->IsValid() )
        return sal_False;
    else
        return sal_True;
}

void SvxAccessibleEditableTextPara::StateChangeEvent(const sal_Int16 nEventId, const uno::Any& rNewValue, const uno::Any& rOldValue) const
{
    uno::Reference < accessibility::XAccessibleContext > xThis( const_cast< SvxAccessibleEditableTextPara* > (this)->getAccessibleContext() );

    accessibility::AccessibleEventObject aEvent(xThis, nEventId, rNewValue, rOldValue);

    // no locking necessary, OInterfaceIteratorHelper copies listeners if someone removes/adds in between
    ::cppu::OInterfaceIteratorHelper aIter( const_cast< SvxAccessibleEditableTextPara* >(this)->maStateListeners );
    while( aIter.hasMoreElements() )
    {
        uno::Reference < accessibility::XAccessibleEventListener > xListener( aIter.next(), uno::UNO_QUERY );

        if( xListener.is() )
        {
            try
            {
                xListener->notifyEvent( aEvent );
            }
            catch( const uno::RuntimeException& )
            {
#ifdef DBG_UTIL
                DBG_ERROR("SvxAccessibleEditableTextPara::StateChangeEvent: Caught runtime exception from listener, removing object (bridge/listener dead?)");
#endif
                // optimization to prevent dead objects from flooding us with exceptions
                aIter.remove();
            }
        }
    }
}

uno::Any SAL_CALL SvxAccessibleEditableTextPara::queryInterface (const uno::Type & rType) throw (uno::RuntimeException)
{
    uno::Any aRet;

    // must provide XAccesibleText by hand, since it comes publicly inherited by XAccessibleEditableText
    if ( rType == ::getCppuType((uno::Reference< accessibility::XAccessibleText > *)0) )
    {
        uno::Reference< accessibility::XAccessibleText > aAccText = this;
        aRet <<= aAccText;
    }
    else if ( rType == ::getCppuType((uno::Reference< accessibility::XAccessibleEditableText > *)0) )
    {
        uno::Reference< accessibility::XAccessibleEditableText > aAccEditText = this;
        aRet <<= aAccEditText;
    }
    else
    {
        aRet = SvxTextParaInterfaceBase::queryInterface(rType);
    }

    return aRet;
}

// XAccessible
uno::Reference< accessibility::XAccessibleContext > SAL_CALL SvxAccessibleEditableTextPara::getAccessibleContext() throw (uno::RuntimeException)
{
    // We implement the XAccessibleContext interface in the same object
    return uno::Reference< accessibility::XAccessibleContext > ( this );
}

// XAccessibleContext
sal_Int32 SAL_CALL SvxAccessibleEditableTextPara::getAccessibleChildCount() throw (uno::RuntimeException)
{
    ::vos::OGuard aGuard( Application::GetSolarMutex() );

    return HaveChildren() ? 1 : 0;
}

uno::Reference< accessibility::XAccessible > SAL_CALL SvxAccessibleEditableTextPara::getAccessibleChild( sal_Int32 i ) throw (lang::IndexOutOfBoundsException, uno::RuntimeException)
{
    ::vos::OGuard aGuard( Application::GetSolarMutex() );

    if( !HaveChildren() )
        throw lang::IndexOutOfBoundsException(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("No childs available")),
                                              uno::Reference< uno::XInterface >
                                              ( static_cast< ::cppu::OWeakObject* > (this) ) ); // static_cast: disambiguate hierarchy

    // create accessible object for bitmap bullet
    // TODO
    return uno::Reference< accessibility::XAccessible >();
}

uno::Reference< accessibility::XAccessible > SAL_CALL SvxAccessibleEditableTextPara::getAccessibleParent() throw (uno::RuntimeException)
{
    return mxParent;
}

sal_Int32 SAL_CALL SvxAccessibleEditableTextPara::getAccessibleIndexInParent() throw (uno::RuntimeException)
{
    return mnIndexInParent;
}

sal_Int16 SAL_CALL SvxAccessibleEditableTextPara::getAccessibleRole() throw (uno::RuntimeException)
{
    // TODO
    return accessibility::AccessibleRole::TEXT;
}

::rtl::OUString SAL_CALL SvxAccessibleEditableTextPara::getAccessibleDescription() throw (uno::RuntimeException)
{
    ::vos::OGuard aGuard( Application::GetSolarMutex() );

    ::rtl::OUString aStr( RTL_CONSTASCII_USTRINGPARAM("Paragraph containing: ") );

    // append first 40 characters from text, or first line, if shorter
    // (writer takes first sentence here, but that's not supported
    // from EditEngine)
    ::rtl::OUString aLine = getTextAtIndex(0, accessibility::AccessibleTextType::LINE).SegmentText;

    if( aLine.getLength() > MaxDescriptionLen )
    {
        ::rtl::OUString aCurrWord;
        sal_Int32 i;

        // search backward from MaxDescriptionLen for previous word start
        for( aCurrWord=getTextAtIndex(MaxDescriptionLen, accessibility::AccessibleTextType::WORD).SegmentText,
                 i=MaxDescriptionLen,
                 aLine=::rtl::OUString();
             i>=0;
             --i )
        {
            if( getTextAtIndex(i, accessibility::AccessibleTextType::WORD).SegmentText != aCurrWord )
            {
                if( i == 0 )
                    // prevent completely empty string
                    aLine = getTextAtIndex(0, accessibility::AccessibleTextType::WORD).SegmentText;
                else
                    aLine = getTextRange(0, i);
            }
        }
    }

    return aStr + aLine;
}

::rtl::OUString SAL_CALL SvxAccessibleEditableTextPara::getAccessibleName() throw (uno::RuntimeException)
{
    ::vos::OGuard aGuard( Application::GetSolarMutex() );

    ::rtl::OUString aStr( RTL_CONSTASCII_USTRINGPARAM("Paragraph ") );

    aStr += ::rtl::OUString::valueOf( GetParagraphIndex() );

    return aStr;
}

uno::Reference< accessibility::XAccessibleRelationSet > SAL_CALL SvxAccessibleEditableTextPara::getAccessibleRelationSet() throw (uno::RuntimeException)
{
    // no relations, therefore empty
    return uno::Reference< accessibility::XAccessibleRelationSet >();
}

uno::Reference< accessibility::XAccessibleStateSet > SAL_CALL SvxAccessibleEditableTextPara::getAccessibleStateSet() throw (uno::RuntimeException)
{
    ::vos::OGuard aGuard( Application::GetSolarMutex() );

    utl::AccessibleStateSetHelper* aStateSet = new ::utl::AccessibleStateSetHelper();
    uno::Reference< accessibility::XAccessibleStateSet > xStateSet( static_cast< cppu::OWeakObject* > (aStateSet), uno::UNO_QUERY );

    // are we defunc?
    if( !mpEditSource )
    {
        aStateSet->AddState( accessibility::AccessibleStateType::DEFUNC );
        aStateSet->AddState( accessibility::AccessibleStateType::INVALID );
    }

    // are we editable?
    if( IsActive() )
    {
        aStateSet->AddState( accessibility::AccessibleStateType::ACTIVE );
        aStateSet->AddState( accessibility::AccessibleStateType::SELECTED );
        aStateSet->AddState( accessibility::AccessibleStateType::EDITABLE );
    }

    // these are always on
    aStateSet->AddState( accessibility::AccessibleStateType::MULTILINE );
    // meaningful only for XAccessibleSelection interface
    // aStateSet->AddState( accessibility::AccessibleStateType::SELECTABLE );

    // are we visible?
    if( IsVisible() )
    {
        aStateSet->AddState( accessibility::AccessibleStateType::SHOWING );
        aStateSet->AddState( accessibility::AccessibleStateType::VISIBLE );
    }

    return xStateSet;
}

lang::Locale SAL_CALL SvxAccessibleEditableTextPara::getLocale() throw (accessibility::IllegalAccessibleComponentStateException, uno::RuntimeException)
{
    ::vos::OGuard aGuard( Application::GetSolarMutex() );

    lang::Locale        aLocale;

    DBG_ASSERT(GetParagraphIndex() >= 0 && GetParagraphIndex() <= USHRT_MAX,
               "SvxAccessibleEditableTextPara::getLocale: paragraph index value overflow");

    // return locale of first character in the paragraph
    return SvxLanguageToLocale(aLocale, GetTextForwarder().GetLanguage( static_cast< USHORT >( GetParagraphIndex() ), 0 ));
}

void SAL_CALL SvxAccessibleEditableTextPara::addEventListener( const uno::Reference< accessibility::XAccessibleEventListener >& xListener ) throw (uno::RuntimeException)
{
    maStateListeners.addInterface( xListener );
}

void SAL_CALL SvxAccessibleEditableTextPara::removeEventListener( const uno::Reference< accessibility::XAccessibleEventListener >& xListener ) throw (uno::RuntimeException)
{
    maStateListeners.removeInterface( xListener );
}

// XAccessibleComponent
sal_Bool SAL_CALL SvxAccessibleEditableTextPara::containsPoint( const awt::Point& aTmpPoint ) throw (uno::RuntimeException)
{
    ::vos::OGuard aGuard( Application::GetSolarMutex() );

    DBG_ASSERT(GetParagraphIndex() >= 0 && GetParagraphIndex() <= USHRT_MAX,
               "SvxAccessibleEditableTextPara::contains: index value overflow");

    awt::Rectangle aTmpRect = getBounds();
    Rectangle aRect( Point(aTmpRect.X, aTmpRect.Y), Size(aTmpRect.Width, aTmpRect.Height) );
    Point aPoint( aTmpPoint.X, aTmpPoint.Y );

    return aRect.IsInside( aPoint );
}

uno::Reference< accessibility::XAccessible > SAL_CALL SvxAccessibleEditableTextPara::getAccessibleAtPoint( const awt::Point& aPoint ) throw (uno::RuntimeException)
{
    ::vos::OGuard aGuard( Application::GetSolarMutex() );

    if( HaveChildren() )
    {
        // create accessible object for bitmap bullet
        // TODO
        return uno::Reference< accessibility::XAccessible >();
    }
    else
    {
        // as we have no children, empty reference
        return uno::Reference< accessibility::XAccessible >();
    }
}

awt::Rectangle SAL_CALL SvxAccessibleEditableTextPara::getBounds() throw (uno::RuntimeException)
{
    ::vos::OGuard aGuard( Application::GetSolarMutex() );

    DBG_ASSERT(GetParagraphIndex() >= 0 && GetParagraphIndex() <= USHRT_MAX,
               "SvxAccessibleEditableTextPara::getBounds: index value overflow");

    SvxTextForwarder& rCacheTF = GetTextForwarder();
    Rectangle aRect = rCacheTF.GetParaBounds( static_cast< USHORT >( GetParagraphIndex() ) );

    // convert to screen coordinates
    Rectangle aScreenRect = SvxAccessibleTextHelper_Impl::LogicToPixel( aRect,
                                                                        rCacheTF.GetMapMode(),
                                                                        GetViewForwarder() );

    // offset from shape/cell
    Point aOffset = GetEEOffset();

    return awt::Rectangle( aScreenRect.Left() + aOffset.X(),
                           aScreenRect.Top() + aOffset.Y(),
                           aScreenRect.GetSize().Width(),
                           aScreenRect.GetSize().Height() );
}

awt::Point SAL_CALL SvxAccessibleEditableTextPara::getLocation(  ) throw (uno::RuntimeException)
{
    ::vos::OGuard aGuard( Application::GetSolarMutex() );

    awt::Rectangle aRect = getBounds();

    return awt::Point( aRect.X, aRect.Y );
}

awt::Point SAL_CALL SvxAccessibleEditableTextPara::getLocationOnScreen(  ) throw (uno::RuntimeException)
{
    ::vos::OGuard aGuard( Application::GetSolarMutex() );

    // relate us to parent
    uno::Reference< accessibility::XAccessible > xParent = getAccessibleParent();
    if( xParent.is() )
    {
        uno::Reference< accessibility::XAccessibleComponent > xParentComponent( xParent, uno::UNO_QUERY );
        if( xParentComponent.is() )
        {
            awt::Point aRefPoint = xParentComponent->getLocationOnScreen();
            awt::Point aPoint = getLocation();
            aPoint.X += aRefPoint.X;
            aPoint.Y += aRefPoint.Y;

            return aPoint;
        }
    }

    throw uno::RuntimeException(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("Cannot access parent")),
                                uno::Reference< uno::XInterface >
                                ( static_cast< accessibility::XAccessible* > (this) ) );    // disambiguate hierarchy
}

awt::Size SAL_CALL SvxAccessibleEditableTextPara::getSize(  ) throw (uno::RuntimeException)
{
    ::vos::OGuard aGuard( Application::GetSolarMutex() );

    awt::Rectangle aRect = getBounds();

    return awt::Size( aRect.Width, aRect.Height );
}

sal_Bool SAL_CALL SvxAccessibleEditableTextPara::isShowing(  ) throw (uno::RuntimeException)
{
    // to be removed (AF)
    return IsVisible();
}

sal_Bool SAL_CALL SvxAccessibleEditableTextPara::isVisible(  ) throw (uno::RuntimeException)
{
    // to be removed (AF)
    return IsVisible();
}

sal_Bool SAL_CALL SvxAccessibleEditableTextPara::isFocusTraversable(  ) throw (uno::RuntimeException)
{
    // to be removed (AF)
    return sal_False;
}

void SAL_CALL SvxAccessibleEditableTextPara::addFocusListener( const uno::Reference< awt::XFocusListener >& xListener ) throw (uno::RuntimeException)
{
    // can be removed? (AF)
    throw uno::RuntimeException(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("Not focusable")),
                                uno::Reference< uno::XInterface >
                                ( static_cast< accessibility::XAccessible* > (this) ) );    // disambiguate hierarchy
}

void SAL_CALL SvxAccessibleEditableTextPara::removeFocusListener( const uno::Reference< awt::XFocusListener >& xListener ) throw (uno::RuntimeException)
{
    // can be removed? (AF)
    throw uno::RuntimeException(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("Not focusable")),
                                uno::Reference< uno::XInterface >
                                ( static_cast< accessibility::XAccessible* > (this) ) );    // disambiguate hierarchy
}

void SAL_CALL SvxAccessibleEditableTextPara::grabFocus(  ) throw (uno::RuntimeException)
{
    throw uno::RuntimeException(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("Not focusable")),
                                uno::Reference< uno::XInterface >
                                ( static_cast< accessibility::XAccessible* > (this) ) );    // disambiguate hierarchy
}

uno::Any SAL_CALL SvxAccessibleEditableTextPara::getAccessibleKeyBinding(  ) throw (uno::RuntimeException)
{
    // AFAIK, none.
    return uno::Any();
}

// XAccessibleText
sal_Int32 SAL_CALL SvxAccessibleEditableTextPara::getCaretPosition() throw (uno::RuntimeException)
{
    ::vos::OGuard aGuard( Application::GetSolarMutex() );

    if( !HaveEditView() )
        return -1;

    ESelection aSelection;
    if( GetEditViewForwarder().GetSelection( aSelection ) &&
        GetParagraphIndex() == aSelection.nEndPara )
    {
        // caret is always nEndPara,nEndPos
        return EEIndex2CharIndex( aSelection.nEndPos ).GetIndex();
    }

    // not within this paragraph
    return -1;
}

sal_Unicode SAL_CALL SvxAccessibleEditableTextPara::getCharacter( sal_Int32 nIndex ) throw (lang::IndexOutOfBoundsException, uno::RuntimeException)
{
    ::vos::OGuard aGuard( Application::GetSolarMutex() );

    DBG_ASSERT(GetParagraphIndex() >= 0 && GetParagraphIndex() <= USHRT_MAX,
               "SvxAccessibleEditableTextPara::getCharacter: index value overflow");

    CheckIndex( nIndex );

    SvxAccessibleTextIndex aIndex = CharIndex2EEIndex( nIndex );

    return GetText( aIndex ).GetChar(static_cast< USHORT > ( aIndex.GetFieldOffset() ) );
}

uno::Sequence< beans::PropertyValue > SAL_CALL SvxAccessibleEditableTextPara::getCharacterAttributes( sal_Int32 nIndex, const ::com::sun::star::uno::Sequence< ::rtl::OUString >getCharacterAttributes( sal_Int32 nIndex ) aRequestedAttributes ) throw (lang::IndexOutOfBoundsException, uno::RuntimeException)
{
    ::vos::OGuard aGuard( Application::GetSolarMutex() );

    SvxTextForwarder& rCacheTF = GetTextForwarder();
    USHORT nPara = static_cast< USHORT >( GetParagraphIndex() );

    DBG_ASSERT(GetParagraphIndex() >= 0 && GetParagraphIndex() <= USHRT_MAX,
               "SvxAccessibleEditableTextPara::getCharacterAttributes: index value overflow");

    CheckIndex(nIndex);

    // use the portion property map, we're working on single characters
    // TODO: hold it as a member?
    SvxAccessibleTextPropertySet aPropSet( &GetEditSource(),
                                           ImplGetSvxTextPortionPropertyMap() );

    aPropSet.SetSelection( MakeEESelection( CharIndex2EEIndex( nIndex ).GetEEIndex() ) );

    // fetch property names
    uno::Reference< beans::XPropertySetInfo > xPropSetInfo = aPropSet.getPropertySetInfo();

    // convert from Any to PropertyValue
    if( !xPropSetInfo.is() )
        throw uno::RuntimeException(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("Cannot query XPropertySetInfo")),
                                    uno::Reference< uno::XInterface >
                                    ( static_cast< accessibility::XAccessible* > (this) ) );    // disambiguate hierarchy

    uno::Sequence< beans::Property > aPropertyNames = xPropSetInfo->getProperties();
    sal_Int32 i, nLength( aPropertyNames.getLength() );
    uno::Sequence< beans::PropertyValue > aOutSequence(nLength);
    const beans::Property*  pPropArray = aPropertyNames.getConstArray();
    beans::PropertyValue* pOutArray = aOutSequence.getArray();
    for(i=0; i<nLength; ++i)
    {
        pOutArray->Name = pPropArray->Name;
        pOutArray->Handle = pPropArray->Handle;
        pOutArray->Value = aPropSet.getPropertyValue( pPropArray->Name );
        pOutArray->State = aPropSet.getPropertyState( pPropArray->Name );

        ++pPropArray;
        ++pOutArray;
    }

    return aOutSequence;
}

awt::Rectangle SAL_CALL SvxAccessibleEditableTextPara::getCharacterBounds( sal_Int32 nIndex ) throw (lang::IndexOutOfBoundsException, uno::RuntimeException)
{
    ::vos::OGuard aGuard( Application::GetSolarMutex() );

    DBG_ASSERT(GetParagraphIndex() >= 0 && GetParagraphIndex() <= USHRT_MAX,
               "SvxAccessibleEditableTextPara::getCharacterBounds: index value overflow");

    CheckIndex( nIndex );

    SvxAccessibleTextIndex aIndex = CharIndex2EEIndex( nIndex );

    SvxTextForwarder& rCacheTF = GetTextForwarder();
    Rectangle aRect;

    if( aIndex.InBullet() )
    {
        EBulletInfo aBulletInfo = rCacheTF.GetBulletInfo( static_cast< USHORT >(GetParagraphIndex()) );

        OutputDevice* pOutDev = rCacheTF.GetRefDevice();

        DBG_ASSERT(pOutDev!=NULL, "SvxAccessibleEditableTextPara::getCharacterBounds: No ref device");

        // preset if anything goes wrong below
        aRect = aBulletInfo.aBounds; // better than nothing
        if( pOutDev )
        {
            SvxAccessibleStringWrap aStringWrap( *pOutDev, aBulletInfo.aFont, aBulletInfo.aText );

            if( aStringWrap.GetCharacterBounds( aIndex.GetBulletOffset(), aRect ) )
                aRect.Move( aBulletInfo.aBounds.Left(), aBulletInfo.aBounds.Top() );
        }
    }
    else
    {
        // preset if anything goes wrong below
        // n-th char in GetParagraphIndex's paragraph
        aRect = rCacheTF.GetCharBounds( static_cast< USHORT >( GetParagraphIndex() ), static_cast< USHORT >( aIndex.GetEEIndex() ) );

        // handle field content manually
        if( aIndex.InField() )
        {
            OutputDevice* pOutDev = rCacheTF.GetRefDevice();

            DBG_ASSERT(pOutDev!=NULL, "SvxAccessibleEditableTextPara::getCharacterBounds: No ref device");

            if( pOutDev )
            {
                SvxFont aFont = EditEngine::CreateSvxFontFromItemSet( rCacheTF.GetAttribs( MakeEESelection( aIndex.GetEEIndex() ) ) );
                SvxAccessibleStringWrap aStringWrap( *pOutDev,
                                                     aFont,
                                                     rCacheTF.GetText( MakeEESelection( aIndex.GetEEIndex() ) ) );

                if( !aStringWrap.GetCharacterBounds( aIndex.GetFieldOffset(), aRect ) )
                    aRect = rCacheTF.GetCharBounds( static_cast< USHORT >( GetParagraphIndex() ), static_cast< USHORT >( aIndex.GetEEIndex() ) );
            }
        }
    }

    // convert to screen
    Rectangle aScreenRect = SvxAccessibleTextHelper_Impl::LogicToPixel( aRect,
                                                                        rCacheTF.GetMapMode(),
                                                                        GetViewForwarder() );
    // offset from shape/cell
    Point aOffset = GetEEOffset();

    return awt::Rectangle( aScreenRect.Left() + aOffset.X(),
                           aScreenRect.Top() + aOffset.Y(),
                           aScreenRect.GetSize().Width(),
                           aScreenRect.GetSize().Height() );
}

sal_Int32 SAL_CALL SvxAccessibleEditableTextPara::getCharacterCount() throw (uno::RuntimeException)
{
    ::vos::OGuard aGuard( Application::GetSolarMutex() );

    DBG_ASSERT(GetParagraphIndex() >= 0 && GetParagraphIndex() <= USHRT_MAX,
               "SvxAccessibleEditableTextPara::getCharacterCount: index value overflow");

    return EEIndex2CharIndex( GetTextLen() ).GetIndex();
}

sal_Int32 SAL_CALL SvxAccessibleEditableTextPara::getIndexAtPoint( const awt::Point& rPoint ) throw (uno::RuntimeException)
{
    ::vos::OGuard aGuard( Application::GetSolarMutex() );

    USHORT nPara, nIndex;

    // offset from surrounding cell/shape
    Point aOffset( GetEEOffset() );
    Point aPoint( rPoint.X - aOffset.X(), rPoint.Y - aOffset.Y() );

    // convert to logical coordinates
    SvxTextForwarder& rCacheTF = GetTextForwarder();
    Point aLogPoint( GetViewForwarder().PixelToLogic( aPoint, rCacheTF.GetMapMode() ) );

    EBulletInfo aBulletInfo = GetTextForwarder().GetBulletInfo( static_cast< USHORT >(GetParagraphIndex()) );

    // any text bullets?
    if( aBulletInfo.nParagraph != EE_PARA_NOT_FOUND &&
        aBulletInfo.bVisible &&
        aBulletInfo.nType != SVX_NUM_BITMAP )
    {
        if( aBulletInfo.aBounds.IsInside( aLogPoint) )
        {
            OutputDevice* pOutDev = rCacheTF.GetRefDevice();

            DBG_ASSERT(pOutDev!=NULL, "SvxAccessibleEditableTextPara::getIndexAtPoint: No ref device");

            if( pOutDev )
            {
                SvxAccessibleStringWrap aStringWrap( *pOutDev, aBulletInfo.aFont, aBulletInfo.aText );

                aLogPoint.Move( -aBulletInfo.aBounds.Left(), -aBulletInfo.aBounds.Top() );

                return aStringWrap.GetIndexAtPoint( aLogPoint );
            }
        }
    }

    if( rCacheTF.GetIndexAtPoint( aLogPoint, nPara, nIndex ) &&
        GetParagraphIndex() == nPara )
    {
        SvxAccessibleTextIndex aIndex = EEIndex2CharIndex(nIndex);

        if( aIndex.InField() )
        {
            OutputDevice* pOutDev = rCacheTF.GetRefDevice();

            DBG_ASSERT(pOutDev!=NULL, "SvxAccessibleEditableTextPara::getCharacterBounds: No ref device");

            if( pOutDev )
            {
                SvxFont aFont = EditEngine::CreateSvxFontFromItemSet( rCacheTF.GetAttribs( MakeEESelection( aIndex.GetEEIndex() ) ) );
                SvxAccessibleStringWrap aStringWrap( *pOutDev,
                                                     aFont,
                                                     rCacheTF.GetText( MakeEESelection( aIndex.GetEEIndex() ) ) );

                return aStringWrap.GetIndexAtPoint( aLogPoint );
            }
        }

        return aIndex.GetIndex();
    }
    else
    {
        // not within our paragraph
        return -1;
    }
}

sal_Bool SvxAccessibleEditableTextPara::GetSelection( USHORT& nStartPos, USHORT& nEndPos ) throw (uno::RuntimeException)
{
    ESelection aSelection;
    USHORT nPara = static_cast< USHORT > ( GetParagraphIndex() );
    if( !GetEditViewForwarder().GetSelection( aSelection ) )
        return sal_False;

    if( aSelection.nStartPara < aSelection.nEndPara )
    {
        if( aSelection.nStartPara > nPara ||
            aSelection.nEndPara < nPara )
            return sal_False;

        if( nPara == aSelection.nStartPara )
            nStartPos = aSelection.nStartPos;
        else
            nStartPos = 0;

        if( nPara == aSelection.nEndPara )
            nEndPos = aSelection.nEndPos;
        else
            nEndPos = GetTextLen();
    }
    else
    {
        if( aSelection.nStartPara < nPara ||
            aSelection.nEndPara > nPara )
            return sal_False;

        if( nPara == aSelection.nStartPara )
            nStartPos = aSelection.nStartPos;
        else
            nStartPos = GetTextLen();

        if( nPara == aSelection.nEndPara )
            nEndPos = aSelection.nEndPos;
        else
            nEndPos = 0;
    }

    return sal_True;
}

::rtl::OUString SAL_CALL SvxAccessibleEditableTextPara::getSelectedText() throw (uno::RuntimeException)
{
    ::vos::OGuard aGuard( Application::GetSolarMutex() );

    DBG_ASSERT(GetParagraphIndex() >= 0 && GetParagraphIndex() <= USHRT_MAX,
               "SvxAccessibleEditableTextPara::getSelectedText: index value overflow");

    if( !HaveEditView() )
        return ::rtl::OUString();

    USHORT nStartPos, nEndPos;
    if( GetSelection( nStartPos, nEndPos ) )
        return GetTextRange( nStartPos, nEndPos );

    return ::rtl::OUString();
}

sal_Int32 SAL_CALL SvxAccessibleEditableTextPara::getSelectionStart() throw (uno::RuntimeException)
{
    ::vos::OGuard aGuard( Application::GetSolarMutex() );

    DBG_ASSERT(GetParagraphIndex() >= 0 && GetParagraphIndex() <= USHRT_MAX,
               "SvxAccessibleEditableTextPara::getSelectionStart: index value overflow");

    if( !HaveEditView() )
        return -1;

    USHORT nStartPos, nEndPos;
    if( GetSelection( nStartPos, nEndPos) )
        return EEIndex2CharIndex(nStartPos).GetIndex();
    else
        return -1;
}

sal_Int32 SAL_CALL SvxAccessibleEditableTextPara::getSelectionEnd() throw (uno::RuntimeException)
{
    ::vos::OGuard aGuard( Application::GetSolarMutex() );

    DBG_ASSERT(GetParagraphIndex() >= 0 && GetParagraphIndex() <= USHRT_MAX,
               "SvxAccessibleEditableTextPara::getSelectionEnd: index value overflow");

    if( !HaveEditView() )
        return -1;

    USHORT nStartPos, nEndPos;
    if( GetSelection( nStartPos, nEndPos) )
        return EEIndex2CharIndex(nEndPos).GetIndex();
    else
        return -1;
}

sal_Bool SAL_CALL SvxAccessibleEditableTextPara::setSelection( sal_Int32 nStartIndex, sal_Int32 nEndIndex ) throw (lang::IndexOutOfBoundsException, uno::RuntimeException)
{
    ::vos::OGuard aGuard( Application::GetSolarMutex() );

    DBG_ASSERT(GetParagraphIndex() >= 0 && GetParagraphIndex() <= USHRT_MAX,
               "SvxAccessibleEditableTextPara::setSelection: paragraph index value overflow");

    CheckRange(nStartIndex, nEndIndex);

    return GetEditViewForwarder( sal_True ).SetSelection( MakeEESelection(CharIndex2EEIndex(nStartIndex).GetEEIndex(),
                                                                          CharIndex2EEIndex(nEndIndex).GetEEIndex()) );
}

::rtl::OUString SAL_CALL SvxAccessibleEditableTextPara::getText() throw (uno::RuntimeException)
{
    ::vos::OGuard aGuard( Application::GetSolarMutex() );

    DBG_ASSERT(GetParagraphIndex() >= 0 && GetParagraphIndex() <= USHRT_MAX,
               "SvxAccessibleEditableTextPara::getText: paragraph index value overflow");

    return GetTextRangeWithBullets( 0, GetTextLen() );
}

::rtl::OUString SAL_CALL SvxAccessibleEditableTextPara::getTextRange( sal_Int32 nStartIndex, sal_Int32 nEndIndex ) throw (lang::IndexOutOfBoundsException, uno::RuntimeException)
{
    ::vos::OGuard aGuard( Application::GetSolarMutex() );

    DBG_ASSERT(GetParagraphIndex() >= 0 && GetParagraphIndex() <= USHRT_MAX,
               "SvxAccessibleEditableTextPara::getTextRange: paragraph index value overflow");

    CheckRange(nStartIndex, nEndIndex);

    return GetTextRange(CharIndex2EEIndex(nStartIndex), CharIndex2EEIndex(nEndIndex));
}

::com::sun::star::accessibility::TextSegment SAL_CALL SvxAccessibleEditableTextPara::getTextAtIndex( sal_Int32 nIndex, sal_Int16 aTextType ) throw (::com::sun::star::lang::IndexOutOfBoundsException, ::com::sun::star::lang::IllegalArgumentException, ::com::sun::star::uno::RuntimeException)
{
    ::vos::OGuard aGuard( Application::GetSolarMutex() );
    SvxTextForwarder&   rCacheTF = GetTextForwarder();
    sal_Int32           nParaIndex = GetParagraphIndex();

    DBG_ASSERT(nParaIndex >= 0 && nParaIndex <= USHRT_MAX,
               "SvxAccessibleEditableTextPara::getTextAtIndex: paragraph index value overflow");

    sal_Int32 nTextLen = rCacheTF.GetTextLen( static_cast< USHORT >( nParaIndex ) );

    CheckIndex(nIndex);

    SvxAccessibleTextIndex aIndex = CharIndex2EEIndex(nIndex);

    ::com::sun::star::accessibility::TextSegment aResult;
    aResult.SegmentStart = -1;
    aResult.SegmentEnd = -1;

    switch( aTextType )
    {
        case accessibility::AccessibleTextType::CHARACTER:
            aResult.SegmentText = String( getCharacter( nIndex ) );
            aResult.SegmentStart = nIndex;
            aResult.SegmentEnd = nIndex+1;
            break;

        case accessibility::AccessibleTextType::WORD:
        {
            USHORT nStart, nEnd;
            if( rCacheTF.GetWordIndices( static_cast< USHORT >( nParaIndex ), static_cast< USHORT >( aIndex.GetEEIndex() ), nStart, nEnd ) )
            {
                aResult.SegmentText = GetTextRangeWithBullets( nStart, nEnd );
                aResult.SegmentStart = nStart;
                aResult.SegmentEnd = nEnd;
            }
            break;
        }

        case accessibility::AccessibleTextType::LINE:
        {
            USHORT nLine, nLineCount=rCacheTF.GetLineCount( static_cast< USHORT >( nParaIndex ) );
            sal_Int32 nCurIndex;
            for( nLine=0, nCurIndex=0; nLine<nLineCount; ++nLine )
            {
                nCurIndex += rCacheTF.GetLineLen( static_cast< USHORT >( nParaIndex ), nLine);

                if( nCurIndex > aIndex.GetEEIndex() )
                {
                    aResult.SegmentStart = nCurIndex - rCacheTF.GetLineLen(static_cast< USHORT >( nParaIndex ), nLine);
                    aResult.SegmentEnd = nCurIndex  ;
                    aResult.SegmentText = GetTextRangeWithBullets( aResult.SegmentStart, aResult.SegmentEnd );
                    break;
                }
            }
            break;
        }

        case accessibility::AccessibleTextType::SENTENCE:
            // TODO. currently fallback to paragraph.
        case accessibility::AccessibleTextType::PARAGRAPH:
            aResult.SegmentText = getText();
            aResult.SegmentStart = 0;
            aResult.SegmentEnd = aResult.SegmentText.getLength();
            break;

        default:
            throw lang::IndexOutOfBoundsException(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("Text type value out of range")),
                                                  uno::Reference< uno::XInterface >
                                                  ( static_cast< ::cppu::OWeakObject* > (this) ) ); // disambiguate hierarchy
    } /* end of switch( aTextType ) */

    return aResult;
}

::com::sun::star::accessibility::TextSegment SAL_CALL SvxAccessibleEditableTextPara::getTextBeforeIndex( sal_Int32 nIndex, sal_Int16 aTextType ) throw (::com::sun::star::lang::IndexOutOfBoundsException, ::com::sun::star::lang::IllegalArgumentException, ::com::sun::star::uno::RuntimeException)
{
    ::vos::OGuard aGuard( Application::GetSolarMutex() );
    SvxTextForwarder&   rCacheTF = GetTextForwarder();
    sal_Int32           nParaIndex = GetParagraphIndex();

    DBG_ASSERT(nParaIndex >= 0 && nParaIndex <= USHRT_MAX,
               "SvxAccessibleEditableTextPara::getTextBeforeIndex: paragraph index value overflow");

    sal_Int32 nTextLen( rCacheTF.GetTextLen( static_cast< USHORT >( nParaIndex ) ) );

    CheckIndex(nIndex);

    SvxAccessibleTextIndex aIndex = CharIndex2EEIndex(nIndex);

    ::com::sun::star::accessibility::TextSegment aResult;
    aResult.SegmentStart = -1;
    aResult.SegmentEnd = -1;

    switch( aTextType )
    {
        case accessibility::AccessibleTextType::CHARACTER:
        {
            if ( nIdex > 0 )
            {
                aResult.SegmentText = getCharacter( nIndex-1 );
                aResult.SegmentStart = nIndex-1;
                aResult.SegmentEnd = nIndex;
            }
        }
        break;

        case accessibility::AccessibleTextType::WORD:
        {
            USHORT nStart, nEnd;
            if( rCacheTF.GetWordIndices( static_cast< USHORT >( nParaIndex ), static_cast< USHORT >( aIndex.GetEEIndex() ), nStart, nEnd ) )
            {
                // semantics:
                //
                // word w|ord word # word |word word # word| word
                // ^^^^              ^^^^              ^^^^
                //

                // already at the left border
                if( nStart == 0 )
                    break;

                // one word to the left
                if( rCacheTF.GetWordIndices( static_cast< USHORT >( nParaIndex ), static_cast< USHORT >( nStart ), nStart, nEnd ) )
                {
                    aResult.SegmentText = GetTextRangeWithBullets( nStart, nEnd );
                    aResult.SegmentStart = nStart;
                    aResult.SegmentEnd = nEnd;
                }

                break;
            }
        }

        case accessibility::AccessibleTextType::LINE:
        {
            USHORT nLine, nLineCount=rCacheTF.GetLineCount( static_cast< USHORT >( nParaIndex ) );
            sal_Int32 nCurIndex, nLastIndex, nCurLineLen;
            // get the line before the line the index points into
            for( nLine=0, nCurIndex=0, nLastIndex=0; nLine<nLineCount; ++nLine )
            {
                nLastIndex = nCurIndex;
                nCurLineLen = rCacheTF.GetLineLen(static_cast< USHORT >( nParaIndex ), nLine);
                nCurIndex += nCurLineLen;

                if( nCurIndex > aIndex.GetEEIndex() &&
                    nLastIndex > nCurLineLen )
                {
                    aResult.SegmentStart = nLastIndex - nCurLineLen
                    aResult.SegmentEnd = static_cast< USHORT >( nLastIndex );
                    aResult.SegmentText = GetTextRangeWithBullets( aResult.SegmentStart, aResult.SegmentEnd );
                    break;
                }
            }
            break;
        }

        case accessibility::AccessibleTextType::SENTENCE:
            // TODO. currently fallback to paragraph.
        case accessibility::AccessibleTextType::PARAGRAPH:
            // get paragraph before (convenience? bug? feature?)
            if( nParaIndex )
            {
                uno::Reference< accessibility::XAccessible > xParent = getAccessibleParent();
                if( xParent.is() )
                {
                    uno::Reference< accessibility::XAccessibleContext > xParentContext = xParent->getAccessibleContext();
                    if( xParentContext.is() )
                    {
                        uno::Reference< accessibility::XAccessible > xPara = xParentContext->getAccessibleChild( nParaIndex - 1 );
                        if( xPara.is() )
                        {
                            uno::Reference< accessibility::XAccessibleText > xParaContext( xPara, uno::UNO_QUERY );
                            if( xParaContext.is() )
                            {
                                aResult.SegmentText = xParaContext->getText();
                                aResult.SegmentStart = 0;
                                aResult.SegmentEnd = aResult.SegmentText.getLength();
                            }
                        }
                    }
                }
            }
            break;

        default:
            throw lang::IndexOutOfBoundsException(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("Text type value out of range")),
                                                  uno::Reference< uno::XInterface >
                                                  ( static_cast< ::cppu::OWeakObject* > (this) ) ); // disambiguate hierarchy
    } /* end of switch( aTextType ) */

    return aResult;
}

::com::sun::star::accessibility::TextSegment SAL_CALL SvxAccessibleEditableTextPara::getTextBehindIndex( sal_Int32 nIndex, sal_Int16 aTextType ) throw (::com::sun::star::lang::IndexOutOfBoundsException, ::com::sun::star::lang::IllegalArgumentException, ::com::sun::star::uno::RuntimeException)
{
    ::vos::OGuard aGuard( Application::GetSolarMutex() );
    SvxTextForwarder& rCacheTF = GetTextForwarder();
    sal_Int32 nParaIndex = GetParagraphIndex();

    DBG_ASSERT(nParaIndex >= 0 && nParaIndex <= USHRT_MAX,
               "SvxAccessibleEditableTextPara::getTextBehindIndex: paragraph index value overflow");

    sal_Int32 nTextLen( rCacheTF.GetTextLen( static_cast< USHORT >( nParaIndex ) ) );

    CheckIndex(nIndex);

    SvxAccessibleTextIndex aIndex = CharIndex2EEIndex(nIndex);

    ::com::sun::star::accessibility::TextSegment aResult;
    aResult.SegmentStart = -1;
    aResult.SegmentEnd = -1;

    switch( aTextType )
    {
        case accessibility::AccessibleTextType::CHARACTER:
        {
            if ( nIndex < nTextLen-1 )
            {
                aResult.SegmentText = getCharacter( nIndex+1 );
                aResult.SegmentStart = nIndex+1;
                aResult.SegmentEnd = nIndex+2;
            }
        }
        break;

        case accessibility::AccessibleTextType::WORD:
        {
            USHORT nStart, nEnd;
            if( rCacheTF.GetWordIndices( static_cast< USHORT >( nParaIndex ), static_cast< USHORT >( aIndex.GetEEIndex() ), nStart, nEnd ) )
            {
                // semantics:
                //
                // word w|ord word # word |word # word word| word
                //            ^^^^         ^^^^              ^^^^
                //

                // already at the right border
                if( nEnd >= nTextLen-2 )
                break;

                // one word to the right
                if( rCacheTF.GetWordIndices( static_cast< USHORT >( nParaIndex ), nEnd+1, nStart, nEnd ) )
                {
                    aResult.SegmentText = GetTextRangeWithBullets( nStart, nEnd );
                    aResult.SegmentStart = nStart;
                    aResult.SegmentEnd = nEnd;
                }

                break;
            }
        }

        case accessibility::AccessibleTextType::LINE:
        {
            USHORT nLine, nLineCount=rCacheTF.GetLineCount( static_cast< USHORT >( nParaIndex ) );
            sal_Int32 nCurIndex;
            // get the line after the line the index points into
            for( nLine=0, nCurIndex=0; nLine<nLineCount; ++nLine )
            {
                nCurIndex += rCacheTF.GetLineLen(static_cast< USHORT >( nParaIndex ), nLine);

                if( nCurIndex > aIndex.GetEEIndex() &&
                    nLine < nLineCount-1 )
                {
                    aResult.SegmentStart = nCurIndex;
                    aResult.SegmentEnd = nCurIndex + rCacheTF.GetLineLen(static_cast< USHORT >( nParaIndex ), nLine+1);
                    aResult.SegmentText = GetTextRangeWithBullets( aResult.SegmentStart, aResult.SegmentEnd );
                    break;
                }
            }
            break;
        }

        case accessibility::AccessibleTextType::SENTENCE:
            // TODO. currently fallback to paragraph.
        case accessibility::AccessibleTextType::PARAGRAPH:
            // get paragraph behind (convenience? bug? feature?)
            if( nParaIndex < rCacheTF.GetParagraphCount() - 1 )
            {
                uno::Reference< accessibility::XAccessible > xParent = getAccessibleParent();
                if( xParent.is() )
                {
                    uno::Reference< accessibility::XAccessibleContext > xParentContext = xParent->getAccessibleContext();
                    if( xParentContext.is() )
                    {
                        uno::Reference< accessibility::XAccessible > xPara = xParentContext->getAccessibleChild( nParaIndex + 1 );
                        if( xPara.is() )
                        {
                            uno::Reference< accessibility::XAccessibleText > xParaContext( xPara, uno::UNO_QUERY );
                            if( xParaContext.is() )
                            {
                                aResult.SegmentText = xParaContext->getText();
                                aResult.SegmentStart = 0;
                                aResult.SegmentEnd = aResult.SegmentText.getLength();
                            }
                        }
                    }
                }
            }
            break;

        default:
            throw lang::IndexOutOfBoundsException(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("Text type value out of range")),
                                                  uno::Reference< uno::XInterface >
                                                  ( static_cast< ::cppu::OWeakObject* > (this) ) ); // disambiguate hierarchy
    } /* end of switch( aTextType ) */

    return aResult;
}

sal_Bool SAL_CALL SvxAccessibleEditableTextPara::copyText( sal_Int32 nStartIndex, sal_Int32 nEndIndex ) throw (lang::IndexOutOfBoundsException, uno::RuntimeException)
{
    ::vos::OGuard aGuard( Application::GetSolarMutex() );
    SvxEditViewForwarder& rCacheVF = GetEditViewForwarder( sal_True );
    SvxTextForwarder& rCacheTF = GetTextForwarder();    // MUST be after GetEditViewForwarder(), see method docs
    sal_Bool aRetVal;

    DBG_ASSERT(GetParagraphIndex() >= 0 && GetParagraphIndex() <= USHRT_MAX,
               "SvxAccessibleEditableTextPara::copyText: index value overflow");

    CheckRange(nStartIndex, nEndIndex);

    // save current selection
    ESelection aOldSelection;

    rCacheVF.GetSelection( aOldSelection );
    rCacheVF.SetSelection( MakeEESelection(CharIndex2EEIndex(nStartIndex).GetEEIndex(),
                                           CharIndex2EEIndex(nEndIndex).GetEEIndex()) );
    aRetVal = rCacheVF.Copy();
    rCacheVF.SetSelection( aOldSelection ); // restore

    return aRetVal;
}

// XAccessibleEditableText
sal_Bool SAL_CALL SvxAccessibleEditableTextPara::cutText( sal_Int32 nStartIndex, sal_Int32 nEndIndex ) throw (lang::IndexOutOfBoundsException, uno::RuntimeException)
{
    ::vos::OGuard aGuard( Application::GetSolarMutex() );
    SvxEditViewForwarder& rCacheVF = GetEditViewForwarder( sal_True );
    SvxTextForwarder& rCacheTF = GetTextForwarder();    // MUST be after GetEditViewForwarder(), see method docs

    DBG_ASSERT(GetParagraphIndex() >= 0 && GetParagraphIndex() <= USHRT_MAX,
               "SvxAccessibleEditableTextPara::cutText: index value overflow");

    CheckRange(nStartIndex, nEndIndex);

    SvxAccessibleTextIndex aStartIndex = CharIndex2EEIndex(nStartIndex);
    SvxAccessibleTextIndex aEndIndex = CharIndex2EEIndex(nEndIndex);

    if( !aStartIndex.IsEditableRange( aEndIndex ) )
        return sal_False;

    // don't save selection, might become invalid after cut!
    rCacheVF.SetSelection( MakeEESelection(aStartIndex.GetEEIndex(), aEndIndex.GetEEIndex()) );

    return rCacheVF.Cut();
}

sal_Bool SAL_CALL SvxAccessibleEditableTextPara::pasteText( sal_Int32 nIndex ) throw (lang::IndexOutOfBoundsException, uno::RuntimeException)
{
    ::vos::OGuard aGuard( Application::GetSolarMutex() );
    SvxEditViewForwarder& rCacheVF = GetEditViewForwarder( sal_True );
    SvxTextForwarder& rCacheTF = GetTextForwarder();    // MUST be after GetEditViewForwarder(), see method docs

    DBG_ASSERT(GetParagraphIndex() >= 0 && GetParagraphIndex() <= USHRT_MAX,
               "SvxAccessibleEditableTextPara::pasteText: index value overflow");

    CheckPosition(nIndex);

    SvxAccessibleTextIndex aIndex = CharIndex2EEIndex(nIndex);

    if( !aIndex.IsEditable() )
        return sal_False;

    // set empty selection (=> cursor) to given index
    rCacheVF.SetSelection( MakeEESelection(aIndex.GetEEIndex()) );

    return rCacheVF.Paste();
}

sal_Bool SAL_CALL SvxAccessibleEditableTextPara::deleteText( sal_Int32 nStartIndex, sal_Int32 nEndIndex ) throw (lang::IndexOutOfBoundsException, uno::RuntimeException)
{
    ::vos::OGuard aGuard( Application::GetSolarMutex() );
    SvxTextForwarder& rCacheTF = GetTextForwarder();

    DBG_ASSERT(GetParagraphIndex() >= 0 && GetParagraphIndex() <= USHRT_MAX,
               "SvxAccessibleEditableTextPara::deleteText: index value overflow");

    CheckRange(nStartIndex, nEndIndex);

    SvxAccessibleTextIndex aStartIndex = CharIndex2EEIndex(nStartIndex);
    SvxAccessibleTextIndex aEndIndex = CharIndex2EEIndex(nEndIndex);

    if( !aStartIndex.IsEditableRange( aEndIndex ) )
        return sal_False;

    sal_Bool nRet = rCacheTF.Delete( MakeEESelection(aStartIndex.GetEEIndex(), aEndIndex.GetEEIndex()) );

    GetEditSource().UpdateData();

    return nRet;
}

sal_Bool SAL_CALL SvxAccessibleEditableTextPara::insertText( const ::rtl::OUString& sText, sal_Int32 nIndex ) throw (lang::IndexOutOfBoundsException, uno::RuntimeException)
{
    ::vos::OGuard aGuard( Application::GetSolarMutex() );
    SvxTextForwarder& rCacheTF = GetTextForwarder();

    DBG_ASSERT(GetParagraphIndex() >= 0 && GetParagraphIndex() <= USHRT_MAX,
               "SvxAccessibleEditableTextPara::insertText: index value overflow");

    CheckPosition(nIndex);

    SvxAccessibleTextIndex aIndex = CharIndex2EEIndex(nIndex);

    if( !aIndex.IsEditable() )
        return sal_False;

    // insert given text at empty selection (=> cursor)
    sal_Bool nRet = rCacheTF.InsertText( sText, MakeEESelection(aIndex.GetEEIndex()) );

    rCacheTF.QuickFormatDoc();
    GetEditSource().UpdateData();

    return nRet;
}

sal_Bool SAL_CALL SvxAccessibleEditableTextPara::replaceText( sal_Int32 nStartIndex, sal_Int32 nEndIndex, const ::rtl::OUString& sReplacement ) throw (lang::IndexOutOfBoundsException, uno::RuntimeException)
{
    ::vos::OGuard aGuard( Application::GetSolarMutex() );
    SvxTextForwarder& rCacheTF = GetTextForwarder();

    DBG_ASSERT(GetParagraphIndex() >= 0 && GetParagraphIndex() <= USHRT_MAX,
               "SvxAccessibleEditableTextPara::replaceText: index value overflow");

    CheckRange(nStartIndex, nEndIndex);

    SvxAccessibleTextIndex aStartIndex = CharIndex2EEIndex(nStartIndex);
    SvxAccessibleTextIndex aEndIndex = CharIndex2EEIndex(nEndIndex);

    if( !aStartIndex.IsEditableRange( aEndIndex ) )
        return sal_False;

    // insert given text into given range => replace
    sal_Bool nRet = rCacheTF.InsertText( sReplacement, MakeEESelection(aStartIndex.GetEEIndex(), aEndIndex.GetEEIndex()) );

    rCacheTF.QuickFormatDoc();
    GetEditSource().UpdateData();

    return nRet;
}

sal_Bool SAL_CALL SvxAccessibleEditableTextPara::setAttributes( sal_Int32 nStartIndex, sal_Int32 nEndIndex, const uno::Sequence< beans::PropertyValue >& aAttributeSet ) throw (lang::IndexOutOfBoundsException, uno::RuntimeException)
{
    ::vos::OGuard aGuard( Application::GetSolarMutex() );
    SvxTextForwarder& rCacheTF = GetTextForwarder();
    USHORT nPara = static_cast< USHORT >( GetParagraphIndex() );

    DBG_ASSERT(GetParagraphIndex() >= 0 && GetParagraphIndex() <= USHRT_MAX,
               "SvxAccessibleEditableTextPara::setAttributes: index value overflow");

    CheckRange(nStartIndex, nEndIndex);

    SvxAccessibleTextIndex aStartIndex = CharIndex2EEIndex(nStartIndex);
    SvxAccessibleTextIndex aEndIndex = CharIndex2EEIndex(nEndIndex);

    if( !aStartIndex.IsEditableRange( aEndIndex ) )
        return sal_False;

    // do the indices span the whole paragraph? Then use the outliner map
    // TODO: hold it as a member?
    SvxAccessibleTextPropertySet aPropSet( &GetEditSource(),
                                           0 == aStartIndex.GetEEIndex() &&
                                           rCacheTF.GetTextLen(nPara) == aEndIndex.GetEEIndex() ?
                                           ImplGetSvxUnoOutlinerTextCursorPropertyMap() :
                                           ImplGetSvxTextPortionPropertyMap() );

    aPropSet.SetSelection( MakeEESelection(aStartIndex.GetEEIndex(), aEndIndex.GetEEIndex()) );

    // convert from PropertyValue to Any
    sal_Int32 i, nLength( aAttributeSet.getLength() );
    const beans::PropertyValue* pPropArray = aAttributeSet.getConstArray();
    for(i=0; i<nLength; ++i)
    {
        try
        {
            aPropSet.setPropertyValue(pPropArray->Name, pPropArray->Value);
        }
        catch( const uno::Exception& )
        {
            DBG_ERROR("SvxAccessibleEditableTextPara::setAttributes exception in setPropertyValue");
        }

        ++pPropArray;
    }

    rCacheTF.QuickFormatDoc();
    GetEditSource().UpdateData();

    return sal_True;
}

sal_Bool SAL_CALL SvxAccessibleEditableTextPara::setText( const ::rtl::OUString& sText ) throw (uno::RuntimeException)
{
    ::vos::OGuard aGuard( Application::GetSolarMutex() );

    return replaceText(0, getCharacterCount(), sText);
}

// XServiceInfo
::rtl::OUString SAL_CALL SvxAccessibleEditableTextPara::getImplementationName (void) throw (uno::RuntimeException)
{
    return ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM ("SvxAccessibleEditableTextPara"));
}

sal_Bool SAL_CALL SvxAccessibleEditableTextPara::supportsService (const ::rtl::OUString& sServiceName) throw (uno::RuntimeException)
{
    //  Iterate over all supported service names and return true if on of them
    //  matches the given name.
    uno::Sequence< ::rtl::OUString> aSupportedServices (
        getSupportedServiceNames ());
    for (int i=0; i<aSupportedServices.getLength(); i++)
        if (sServiceName == aSupportedServices[i])
            return sal_True;
    return sal_False;
}

uno::Sequence< ::rtl::OUString> SAL_CALL SvxAccessibleEditableTextPara::getSupportedServiceNames (void) throw (uno::RuntimeException)
{
    const ::rtl::OUString sServiceName (RTL_CONSTASCII_USTRINGPARAM ("com.sun.star.accessibility.AccessibleContext"));
    return uno::Sequence< ::rtl::OUString > (&sServiceName, 1);
}

// XServiceName
::rtl::OUString SAL_CALL SvxAccessibleEditableTextPara::getServiceName (void) throw (uno::RuntimeException)
{
    return ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.accessibility.AccessibleContext"));
}

//------------------------------------------------------------------------
}
