/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svx_xmltxtexp.cxx,v $
 *
 *  $Revision: 1.7 $
 *
 *  last change: $Author: hr $ $Date: 2007-01-02 17:37:45 $
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

/** this file implements an export of a selected EditEngine content into
    a xml stream. See bf_svx/source/inc/xmledit.hxx for interface */

#ifndef _COM_SUN_STAR_UCB_XANYCOMPAREFACTORY_HPP_
#include <com/sun/star/ucb/XAnyCompareFactory.hpp>
#endif
#ifndef _COM_SUN_STAR_STYLE_XSTYLEFAMILIESSUPPLIER_HPP_
#include <com/sun/star/style/XStyleFamiliesSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_IO_XACTIVEDATASOURCE_HPP_
#include <com/sun/star/io/XActiveDataSource.hpp>
#endif











#ifndef _UTL_STREAM_WRAPPER_HXX_
#include <unotools/streamwrap.hxx>
#endif


#ifndef _XMLOFF_XMLEXP_HXX
#include "bf_xmloff/xmlexp.hxx"
#endif


#ifndef _SVX_UNOFORED_HXX
#include "unofored.hxx"
#endif

#ifndef _SVX_UNOTEXT_HXX
#include "unotext.hxx"
#endif

#ifndef _SVX_EDITSOURCE_HXX
#include "editsource.hxx"
#endif

#include <cppuhelper/implbase4.hxx>

#ifndef _SVX_UNOFIELD_HXX
#include "unofield.hxx"
#endif

#ifndef SVX_UNOMOD_HXX
#include "unomod.hxx"
#endif
#include "unonrule.hxx"
#ifndef _LEGACYBINFILTERMGR_HXX
#include <legacysmgr/legacy_binfilters_smgr.hxx>    //STRIP002
#endif
namespace binfilter {
using namespace ::com::sun::star;
using namespace ::com::sun::star::container;
using namespace ::com::sun::star::document;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::awt;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::xml::sax;
using namespace ::rtl;
using namespace cppu;

///////////////////////////////////////////////////////////////////////

class SvxEditEngineSourceImpl;

///////////////////////////////////////////////////////////////////////

/*N*/ class SvxEditEngineSourceImpl
/*N*/ {
/*N*/ private:
/*N*/   oslInterlockedCount maRefCount;
/*N*/
/*N*/   EditEngine*             mpEditEngine;
/*N*/   SvxTextForwarder*       mpTextForwarder;
/*N*/
/*N*/   ~SvxEditEngineSourceImpl();
/*N*/
/*N*/ public:
/*N*/   SvxEditEngineSourceImpl( EditEngine* pEditEngine );
/*N*/
/*N*/   void SAL_CALL acquire();
/*N*/   void SAL_CALL release();
/*N*/
/*N*/   SvxTextForwarder*       GetTextForwarder();
/*N*/ };
/*N*/
/*N*/ ///////////////////////////////////////////////////////////////////////
/*N*/
/*N*/
/*N*/ //------------------------------------------------------------------------
/*N*/
/*N*/ SvxEditEngineSourceImpl::SvxEditEngineSourceImpl( EditEngine* pEditEngine )
/*N*/ : mpEditEngine( pEditEngine ),
/*N*/   mpTextForwarder(NULL),
/*N*/   maRefCount(0)
/*N*/ {
/*N*/ }
/*N*/
/*N*/ //------------------------------------------------------------------------
/*N*/
/*N*/ SvxEditEngineSourceImpl::~SvxEditEngineSourceImpl()
/*N*/ {
/*N*/   delete mpTextForwarder;
/*N*/ }
/*N*/
/*N*/ //------------------------------------------------------------------------
/*N*/
/*N*/ void SAL_CALL SvxEditEngineSourceImpl::acquire()
/*N*/ {
/*N*/   osl_incrementInterlockedCount( &maRefCount );
/*N*/ }
/*N*/
/*N*/ //------------------------------------------------------------------------
/*N*/
/*N*/ void SAL_CALL SvxEditEngineSourceImpl::release()
/*N*/ {
/*N*/   if( ! osl_decrementInterlockedCount( &maRefCount ) )
/*N*/       delete this;
/*N*/ }
/*N*/
/*N*/ //------------------------------------------------------------------------
/*N*/
/*N*/ SvxTextForwarder* SvxEditEngineSourceImpl::GetTextForwarder()
/*N*/ {
/*N*/   if (!mpTextForwarder)
/*N*/       mpTextForwarder = new SvxEditEngineForwarder( *mpEditEngine );
/*N*/
/*N*/   return mpTextForwarder;
/*N*/ }
/*N*/
/*N*/ // --------------------------------------------------------------------
/*N*/ // SvxTextEditSource
/*N*/ // --------------------------------------------------------------------
/*N*/
/*N*/ SvxEditEngineSource::SvxEditEngineSource( EditEngine* pEditEngine )
/*N*/ {
/*N*/   mpImpl = new SvxEditEngineSourceImpl( pEditEngine );
/*N*/   mpImpl->acquire();
/*N*/ }
/*N*/
/*N*/ // --------------------------------------------------------------------
/*N*/
/*N*/ SvxEditEngineSource::SvxEditEngineSource( SvxEditEngineSourceImpl* pImpl )
/*N*/ {
/*N*/   mpImpl = pImpl;
/*N*/   mpImpl->acquire();
/*N*/ }
/*N*/
/*N*/ //------------------------------------------------------------------------
/*N*/
/*N*/ SvxEditEngineSource::~SvxEditEngineSource()
/*N*/ {
/*N*/   mpImpl->release();
/*N*/ }
/*N*/
/*N*/ //------------------------------------------------------------------------
/*N*/
/*N*/ SvxEditSource* SvxEditEngineSource::Clone() const
/*N*/ {
/*N*/   return new SvxEditEngineSource( mpImpl );
/*N*/ }
/*N*/
/*N*/ //------------------------------------------------------------------------
/*N*/
/*N*/ SvxTextForwarder* SvxEditEngineSource::GetTextForwarder()
/*N*/ {
/*N*/     return mpImpl->GetTextForwarder();
/*N*/ }
/*N*/
/*N*/ //------------------------------------------------------------------------
/*N*/
/*N*/ void SvxEditEngineSource::UpdateData()
/*N*/ {
/*N*/ }
/*N*/
/*N*/ class SvxSimpleUnoModel : public cppu::WeakAggImplHelper4<
/*N*/                                   ::com::sun::star::frame::XModel,
/*N*/                                   ::com::sun::star::ucb::XAnyCompareFactory,
/*N*/                                   ::com::sun::star::style::XStyleFamiliesSupplier,
/*N*/                                   ::com::sun::star::lang::XMultiServiceFactory >
/*N*/ {
/*N*/ public:
/*N*/   SvxSimpleUnoModel();
/*N*/   virtual ~SvxSimpleUnoModel();
/*N*/
/*N*/
/*N*/   // XMultiServiceFactory
/*N*/     virtual ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface > SAL_CALL createInstance( const ::rtl::OUString& aServiceSpecifier ) throw(::com::sun::star::uno::Exception, ::com::sun::star::uno::RuntimeException);
/*N*/     virtual ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface > SAL_CALL createInstanceWithArguments( const ::rtl::OUString& ServiceSpecifier, const ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Any >& Arguments ) throw (::com::sun::star::uno::Exception, ::com::sun::star::uno::RuntimeException);
/*N*/     virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getAvailableServiceNames(  ) throw(::com::sun::star::uno::RuntimeException);
/*N*/
/*N*/   // XStyleFamiliesSupplier
/*N*/     virtual ::com::sun::star::uno::Reference< ::com::sun::star::container::XNameAccess > SAL_CALL getStyleFamilies(  ) throw(::com::sun::star::uno::RuntimeException);
/*N*/
/*N*/   // XAnyCompareFactory
/*N*/     virtual ::com::sun::star::uno::Reference< ::com::sun::star::ucb::XAnyCompare > SAL_CALL createAnyCompareByName( const ::rtl::OUString& PropertyName ) throw(::com::sun::star::uno::RuntimeException);
/*N*/
/*N*/     // XModel
/*N*/     virtual sal_Bool SAL_CALL attachResource( const ::rtl::OUString& aURL, const ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue >& aArgs ) throw (::com::sun::star::uno::RuntimeException);
/*N*/     virtual ::rtl::OUString SAL_CALL getURL(  ) throw (::com::sun::star::uno::RuntimeException);
/*N*/     virtual ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue > SAL_CALL getArgs(  ) throw (::com::sun::star::uno::RuntimeException);
/*N*/     virtual void SAL_CALL connectController( const ::com::sun::star::uno::Reference< ::com::sun::star::frame::XController >& xController ) throw (::com::sun::star::uno::RuntimeException);
/*N*/     virtual void SAL_CALL disconnectController( const ::com::sun::star::uno::Reference< ::com::sun::star::frame::XController >& xController ) throw (::com::sun::star::uno::RuntimeException);
/*N*/     virtual void SAL_CALL lockControllers(  ) throw (::com::sun::star::uno::RuntimeException);
/*N*/     virtual void SAL_CALL unlockControllers(  ) throw (::com::sun::star::uno::RuntimeException);
/*N*/     virtual sal_Bool SAL_CALL hasControllersLocked(  ) throw (::com::sun::star::uno::RuntimeException);
/*N*/     virtual ::com::sun::star::uno::Reference< ::com::sun::star::frame::XController > SAL_CALL getCurrentController(  ) throw (::com::sun::star::uno::RuntimeException);
/*N*/     virtual void SAL_CALL setCurrentController( const ::com::sun::star::uno::Reference< ::com::sun::star::frame::XController >& xController ) throw (::com::sun::star::container::NoSuchElementException, ::com::sun::star::uno::RuntimeException);
/*N*/     virtual ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface > SAL_CALL getCurrentSelection(  ) throw (::com::sun::star::uno::RuntimeException);
/*N*/
/*N*/     // XComponent
/*N*/     virtual void SAL_CALL dispose(  ) throw (::com::sun::star::uno::RuntimeException);
/*N*/     virtual void SAL_CALL addEventListener( const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XEventListener >& xListener ) throw (::com::sun::star::uno::RuntimeException);
/*N*/     virtual void SAL_CALL removeEventListener( const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XEventListener >& aListener ) throw (::com::sun::star::uno::RuntimeException);
/*N*/
/*N*/ };
/*N*/
/*N*/ SvxSimpleUnoModel::SvxSimpleUnoModel()
/*N*/ {
/*N*/ }
/*N*/
/*N*/ SvxSimpleUnoModel::~SvxSimpleUnoModel()
/*N*/ {
/*N*/ }
/*N*/
/*N*/ // XMultiServiceFactory ( SvxFmMSFactory )
/*N*/ uno::Reference< uno::XInterface > SAL_CALL SvxSimpleUnoModel::createInstance( const OUString& aServiceSpecifier )
/*N*/   throw(uno::Exception, uno::RuntimeException)
/*N*/ {
/*N*/   if( 0 == aServiceSpecifier.reverseCompareToAsciiL( RTL_CONSTASCII_STRINGPARAM("com.sun.star.text.NumberingRules" ) ) )
/*N*/   {
/*N*/       return SvxCreateNumRule( (SdrModel*)NULL );
/*N*/   }
/*N*/   if( 0 == aServiceSpecifier.reverseCompareToAsciiL( RTL_CONSTASCII_STRINGPARAM("com.sun.star.text.TextField.DateTime") ) )
/*N*/   {
/*N*/       return (::cppu::OWeakObject * )new SvxUnoTextField( ID_EXT_DATEFIELD );
/*N*/   }
/*N*/
/*N*/   return SvxUnoDrawMSFactory::createTextField( aServiceSpecifier );
/*N*/
/*N*/ }
/*N*/
/*N*/ Reference< ::com::sun::star::uno::XInterface > SAL_CALL SvxSimpleUnoModel::createInstanceWithArguments( const ::rtl::OUString& ServiceSpecifier, const ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Any >& Arguments ) throw (::com::sun::star::uno::Exception, ::com::sun::star::uno::RuntimeException)
/*N*/ {
/*N*/   return createInstance( ServiceSpecifier );
/*N*/ }
/*N*/
/*N*/ Sequence< ::rtl::OUString > SAL_CALL SvxSimpleUnoModel::getAvailableServiceNames(  ) throw(::com::sun::star::uno::RuntimeException)
/*N*/ {
/*N*/   Sequence< OUString > aSeq;
/*N*/   return aSeq;
/*N*/ }
/*N*/
/*N*/ // XAnyCompareFactory
/*N*/ uno::Reference< ::com::sun::star::ucb::XAnyCompare > SAL_CALL SvxSimpleUnoModel::createAnyCompareByName( const OUString& PropertyName )
/*N*/   throw(uno::RuntimeException)
/*N*/ {
/*N*/   return SvxCreateNumRuleCompare();
/*N*/ }
/*N*/
/*N*/ // XStyleFamiliesSupplier
/*N*/ uno::Reference< container::XNameAccess > SAL_CALL SvxSimpleUnoModel::getStyleFamilies(  )
/*N*/   throw(uno::RuntimeException)
/*N*/ {
/*N*/   uno::Reference< container::XNameAccess > xStyles;
/*N*/   return xStyles;
/*N*/ }
/*N*/
/*N*/ // XModel
/*N*/ sal_Bool SAL_CALL SvxSimpleUnoModel::attachResource( const ::rtl::OUString& aURL, const ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue >& aArgs ) throw (::com::sun::star::uno::RuntimeException)
/*N*/ {
/*N*/   return sal_False;
/*N*/ }
/*N*/
/*N*/ ::rtl::OUString SAL_CALL SvxSimpleUnoModel::getURL(  ) throw (::com::sun::star::uno::RuntimeException)
/*N*/ {
/*N*/   OUString aStr;
/*N*/   return aStr;
/*N*/ }
/*N*/
/*N*/ ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue > SAL_CALL SvxSimpleUnoModel::getArgs(  ) throw (::com::sun::star::uno::RuntimeException)
/*N*/ {
/*N*/   Sequence< beans::PropertyValue > aSeq;
/*N*/   return aSeq;
/*N*/ }
/*N*/
/*N*/ void SAL_CALL SvxSimpleUnoModel::connectController( const ::com::sun::star::uno::Reference< ::com::sun::star::frame::XController >& xController ) throw (::com::sun::star::uno::RuntimeException)
/*N*/ {
/*N*/ }
/*N*/
/*N*/ void SAL_CALL SvxSimpleUnoModel::disconnectController( const ::com::sun::star::uno::Reference< ::com::sun::star::frame::XController >& xController ) throw (::com::sun::star::uno::RuntimeException)
/*N*/ {
/*N*/ }
/*N*/
/*N*/ void SAL_CALL SvxSimpleUnoModel::lockControllers(  ) throw (::com::sun::star::uno::RuntimeException)
/*N*/ {
/*N*/ }
/*N*/
/*N*/ void SAL_CALL SvxSimpleUnoModel::unlockControllers(  ) throw (::com::sun::star::uno::RuntimeException)
/*N*/ {
/*N*/ }
/*N*/
/*N*/ sal_Bool SAL_CALL SvxSimpleUnoModel::hasControllersLocked(  ) throw (::com::sun::star::uno::RuntimeException)
/*N*/ {
/*N*/   return sal_True;
/*N*/ }
/*N*/
/*N*/ ::com::sun::star::uno::Reference< ::com::sun::star::frame::XController > SAL_CALL SvxSimpleUnoModel::getCurrentController(  ) throw (::com::sun::star::uno::RuntimeException)
/*N*/ {
/*N*/   Reference< frame::XController > xRet;
/*N*/   return xRet;
/*N*/ }
/*N*/
/*N*/ void SAL_CALL SvxSimpleUnoModel::setCurrentController( const ::com::sun::star::uno::Reference< ::com::sun::star::frame::XController >& xController ) throw (::com::sun::star::container::NoSuchElementException, ::com::sun::star::uno::RuntimeException)
/*N*/ {
/*N*/ }
/*N*/
/*N*/ ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface > SAL_CALL SvxSimpleUnoModel::getCurrentSelection(  ) throw (::com::sun::star::uno::RuntimeException)
/*N*/ {
/*N*/   Reference< XInterface > xRet;
/*N*/   return xRet;
/*N*/ }
/*N*/
/*N*/
/*N*/ // XComponent
/*N*/ void SAL_CALL SvxSimpleUnoModel::dispose(  ) throw (::com::sun::star::uno::RuntimeException)
/*N*/ {
/*N*/ }
/*N*/
/*N*/ void SAL_CALL SvxSimpleUnoModel::addEventListener( const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XEventListener >& xListener ) throw (::com::sun::star::uno::RuntimeException)
/*N*/ {
/*N*/ }
/*N*/
/*N*/ void SAL_CALL SvxSimpleUnoModel::removeEventListener( const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XEventListener >& aListener ) throw (::com::sun::star::uno::RuntimeException)
/*N*/ {
/*N*/ }
/*N*/
/*N*/ ///////////////////////////////////////////////////////////////////////
/*N*/
/*N*/ class SvxXMLTextExportComponent : public SvXMLExport
/*N*/ {
/*N*/ public:
/*N*/   // #110680#
/*N*/   SvxXMLTextExportComponent(
/*N*/       const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory > xServiceFactory,
/*N*/       EditEngine* pEditEngine,
/*N*/       const ESelection& rSel,
/*N*/       const ::rtl::OUString& rFileName,
/*N*/       const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XDocumentHandler > & xHandler );
/*N*/
/*N*/   ~SvxXMLTextExportComponent();
/*N*/
/*N*/   // methods without content:
/*N*/   virtual void _ExportAutoStyles();
/*N*/   virtual void _ExportMasterStyles();
/*N*/   virtual void _ExportContent();
/*N*/
/*N*/ private:
/*N*/   ::com::sun::star::uno::Reference< ::com::sun::star::text::XText > mxText;
/*N*/   EditEngine* mpEditEngine;
/*N*/   ESelection maSelection;
/*N*/ };
/*N*/
/*N*/ ///////////////////////////////////////////////////////////////////////
/*N*/
// #110680#
/*N*/ SvxXMLTextExportComponent::SvxXMLTextExportComponent(
/*N*/   const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory > xServiceFactory,
/*N*/   EditEngine* pEditEngine,
/*N*/   const ESelection& rSel,
/*N*/   const ::rtl::OUString& rFileName,
/*N*/   const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XDocumentHandler > & xHandler)
/*N*/ : SvXMLExport( xServiceFactory, rFileName, xHandler, ((frame::XModel*)new SvxSimpleUnoModel()), MAP_CM ),
/*N*/   mpEditEngine( pEditEngine ),
/*N*/   maSelection( rSel )
/*N*/ {
/*N*/   SvxEditEngineSource aEditSource( pEditEngine );
/*N*/
/*N*/   static const SfxItemPropertyMap SvxXMLTextExportComponentPropertyMap[] =
/*N*/   {
/*N*/       SVX_UNOEDIT_CHAR_PROPERTIES,
/*N*/       SVX_UNOEDIT_FONT_PROPERTIES,
/*N*/ //        SVX_UNOEDIT_OUTLINER_PROPERTIES,
/*N*/       {MAP_CHAR_LEN(UNO_NAME_NUMBERING_RULES),        EE_PARA_NUMBULLET,  &::getCppuType((const ::com::sun::star::uno::Reference< ::com::sun::star::container::XIndexReplace>*)0), 0, 0 },
/*N*/       {MAP_CHAR_LEN(UNO_NAME_NUMBERING),              EE_PARA_BULLETSTATE,&::getBooleanCppuType(), 0, 0 },
/*N*/       {MAP_CHAR_LEN(UNO_NAME_NUMBERING_LEVEL),        EE_PARA_OUTLLEVEL,  &::getCppuType((const sal_Int16*)0), 0, 0 },
/*N*/       SVX_UNOEDIT_PARA_PROPERTIES,
/*N*/       {0,0}
/*N*/   };
/*N*/
/*N*/   SvxUnoText* pUnoText = new SvxUnoText( &aEditSource, SvxXMLTextExportComponentPropertyMap, mxText );
/*N*/   pUnoText->SetSelection( rSel );
/*N*/   mxText = pUnoText;
/*N*/
/*N*/   setExportFlags( EXPORT_AUTOSTYLES|EXPORT_CONTENT );
/*N*/ }
/*N*/
/*N*/ SvxXMLTextExportComponent::~SvxXMLTextExportComponent()
/*N*/ {
/*N*/ }
/*N*/
/*N*/ // methods without content:
/*N*/ void SvxXMLTextExportComponent::_ExportAutoStyles()
/*N*/ {
/*N*/   UniReference< XMLTextParagraphExport > xTextExport( GetTextParagraphExport() );
/*N*/
/*N*/   xTextExport->collectTextAutoStyles( mxText );
/*N*/   xTextExport->exportTextAutoStyles();
/*N*/ }
/*N*/
/*N*/ void SvxXMLTextExportComponent::_ExportContent()
/*N*/ {
/*N*/   UniReference< XMLTextParagraphExport > xTextExport( GetTextParagraphExport() );
/*N*/
/*N*/   xTextExport->exportText( mxText );
/*N*/ }
/*N*/
/*N*/ void SvxXMLTextExportComponent::_ExportMasterStyles() {}
}
