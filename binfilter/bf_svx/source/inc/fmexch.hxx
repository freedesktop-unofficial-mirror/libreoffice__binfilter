/*************************************************************************
 *
 *  $RCSfile: fmexch.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 15:56:17 $
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
#ifndef _SVX_FMEXCH_HXX
#define _SVX_FMEXCH_HXX

#ifndef _COMPHELPER_STLTYPES_HXX_
#include <comphelper/stl_types.hxx>
#endif

#ifndef _TRANSFER_HXX
#include <svtools/transfer.hxx>
#endif

// auto strip #ifndef _COM_SUN_STAR_UNO_SEQUENCE_HXX_
// auto strip #include <com/sun/star/uno/Sequence.hxx>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_CONTAINER_XNAMECONTAINER_HPP_
// auto strip #include <com/sun/star/container/XNameContainer.hpp>
// auto strip #endif
// auto strip #ifndef _LINK_HXX
// auto strip #include <tools/link.hxx>
// auto strip #endif
class SvTreeListBox;
namespace binfilter {

class FmFormShell;
class FmFormPage;
class SvLBoxEntry;

//========================================================================
// Exchange types
#define SVX_FM_FIELD_EXCH           String("SvxFormFieldExch",              sizeof("SvxFormFieldExch"))
#define SVX_FM_CONTROL_EXCH         String("SvxFormExplCtrlExch",           sizeof("SvxFormExplCtrlExch"))
#define SVX_FM_CONTROLS_AS_PATH     String("SvxFormControlsAsPathExchange", sizeof("SvxFormControlsAsPathExchange"))
#define SVX_FM_HIDDEN_CONTROLS      String("SvxFormHiddenControlsExchange", sizeof("SvxFormHiddenControlsExchange"))
#define SVX_FM_FILTER_FIELDS        String("SvxFilterFieldExchange",        sizeof("SvxFilterFieldExchange"))

//========================================================================

//........................................................................
namespace svxform
{
//........................................................................

    //====================================================================

    DECLARE_STL_VECTOR( SvLBoxEntry*, ListBoxEntryArray );

    //====================================================================
    //= OLocalExchange
    //====================================================================
//STRIP001  class OLocalExchange : public TransferableHelper
//STRIP001  {
//STRIP001  private:
//STRIP001      Link                m_aClipboardListener;
//STRIP001      sal_Bool            m_bDragging         : 1;
//STRIP001      sal_Bool            m_bClipboardOwner   : 1;
//STRIP001
//STRIP001  public:
//STRIP001      class GrantAccess
//STRIP001      {
//STRIP001          friend class OLocalExchangeHelper;
//STRIP001      };
//STRIP001
//STRIP001  public:
//STRIP001      OLocalExchange( );
//STRIP001
//STRIP001      sal_Bool    isDragging() const { return m_bDragging; }
//STRIP001      sal_Bool    isClipboardOwner() const { return m_bClipboardOwner; }
//STRIP001
//STRIP001      void        startDrag( Window* pWindow, sal_Int8 nDragSourceActions, const GrantAccess& );
//STRIP001      void        copyToClipboard( Window* _pWindow, const GrantAccess& );
//STRIP001
//STRIP001      void        setClipboardListener( const Link& _rListener ) { m_aClipboardListener = _rListener; }
//STRIP001
//STRIP001      void        clear();
//STRIP001
//STRIP001      static  sal_Bool    hasFormat( const DataFlavorExVector& _rFormats, sal_uInt32 _nFormatId );
//STRIP001
//STRIP001  protected:
//STRIP001      // XClipboardOwner
//STRIP001      virtual void SAL_CALL lostOwnership( const ::com::sun::star::uno::Reference< ::com::sun::star::datatransfer::clipboard::XClipboard >& _rxClipboard, const ::com::sun::star::uno::Reference< ::com::sun::star::datatransfer::XTransferable >& _rxTrans ) throw(::com::sun::star::uno::RuntimeException);
//STRIP001
//STRIP001      // TransferableHelper
//STRIP001      virtual void        DragFinished( sal_Int8 nDropAction );
//STRIP001      virtual sal_Bool    GetData( const ::com::sun::star::datatransfer::DataFlavor& rFlavor );
//STRIP001
//STRIP001  private:
//STRIP001      void StartDrag( Window* pWindow, sal_Int8 nDragSourceActions, sal_Int32 nDragPointer = DND_POINTER_NONE, sal_Int32 nDragImage = DND_IMAGE_NONE )
//STRIP001      {   // don't allow this base class method to be called from outside
//STRIP001          TransferableHelper::StartDrag(pWindow, nDragSourceActions, nDragPointer, nDragImage);
//STRIP001      }
//STRIP001  };

    //====================================================================
    //= OLocalExchangeHelper
    //====================================================================
    /// a helper for navigator windows (SvTreeListBox'es) which allow DnD within themself
    class OLocalExchangeHelper
    {
    protected:
        Window*             m_pDragSource;
//STRIP001      OLocalExchange*     m_pTransferable;

    public:
        OLocalExchangeHelper( Window* _pDragSource );
        ~OLocalExchangeHelper();

        void        prepareDrag( );

        void        startDrag( sal_Int8 nDragSourceActions );
        void        copyToClipboard( ) const;

//STRIP001      inline  sal_Bool    isDragSource() const { return m_pTransferable && m_pTransferable->isDragging(); }
//STRIP001      inline  sal_Bool    isClipboardOwner() const { return m_pTransferable && m_pTransferable->isClipboardOwner(); }
//STRIP001      inline  sal_Bool    isDataExchangeActive( ) const { return isDragSource() || isClipboardOwner(); }

//STRIP001      void        setClipboardListener( const Link& _rListener ) { if ( m_pTransferable ) m_pTransferable->setClipboardListener( _rListener ); }

    protected:
//STRIP001      virtual OLocalExchange* createExchange() const = 0;

    protected:
        void implReset();
    };

    //====================================================================
    //= OControlTransferData
    //====================================================================
//STRIP001  class OControlTransferData
//STRIP001  {
//STRIP001  private:
//STRIP001      typedef ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Sequence< sal_uInt32 > > ControlPaths;
//STRIP001
//STRIP001  private:
//STRIP001      DataFlavorExVector  m_aCurrentFormats;
//STRIP001
//STRIP001  protected:
//STRIP001      ListBoxEntryArray   m_aSelectedEntries;
//STRIP001      ControlPaths        m_aControlPaths;
//STRIP001      ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface > >
//STRIP001                          m_aHiddenControlModels;
//STRIP001
//STRIP001      ::com::sun::star::uno::Reference< ::com::sun::star::container::XNameContainer >
//STRIP001                          m_xFormsRoot;       // the root of the forms collection where the entries we represent reside
//STRIP001                                              // this uniquely identifies the page and the document
//STRIP001
//STRIP001      SvLBoxEntry*        m_pFocusEntry;
//STRIP001
//STRIP001  protected:
//STRIP001      // updates m_aCurrentFormats with all formats we currently could supply
//STRIP001      void    updateFormats( );
//STRIP001
//STRIP001  public:
//STRIP001      OControlTransferData( );
//STRIP001
//STRIP001      // ctor to construct the data from an arbitrary Transferable (usually clipboard data)
//STRIP001      OControlTransferData(
//STRIP001          const ::com::sun::star::uno::Reference< ::com::sun::star::datatransfer::XTransferable >& _rxTransferable
//STRIP001      );
//STRIP001
//STRIP001      inline const DataFlavorExVector&    GetDataFlavorExVector() const;
//STRIP001
//STRIP001      void addSelectedEntry( SvLBoxEntry* _pEntry );
//STRIP001      void setFocusEntry( SvLBoxEntry* _pFocusEntry );
//STRIP001
//STRIP001      void setFormsRoot(
//STRIP001          const ::com::sun::star::uno::Reference< ::com::sun::star::container::XNameContainer >& _rxFormsRoot
//STRIP001          ) { m_xFormsRoot = _rxFormsRoot; }
//STRIP001
//STRIP001      void buildPathFormat(SvTreeListBox* pTreeBox, SvLBoxEntry* pRoot);
//STRIP001          // baut aus m_aSelectedEntries m_aControlPaths auf
//STRIP001          // (es wird davon ausgegangen, dass die Eintraege in m_aSelectedEntries sortiert sind in Bezug auf die Nachbar-Beziehung)
//STRIP001
//STRIP001
//STRIP001      void buildListFromPath(SvTreeListBox* pTreeBox, SvLBoxEntry* pRoot);
//STRIP001          // der umgekehrte Weg : wirft alles aus m_aSelectedEntries weg und baut es mittels m_aControlPaths neu auf
//STRIP001
//STRIP001      void addHiddenControlsFormat(const ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface > > seqInterfaces);
//STRIP001          // fuegt ein SVX_FML_HIDDEN_CONTROLS-Format hinzu und merk sich dafuer die uebergebenen Interfaces
//STRIP001          // (es erfolgt KEINE Ueberpruefung, ob dadurch auch tatsaechlich nur hidden Controls bezeichnet werden, dass muss der
//STRIP001          // Aufrufer sicherstellen)
//STRIP001
//STRIP001      SvLBoxEntry*                focused() const { return m_pFocusEntry; }
//STRIP001      const ListBoxEntryArray&    selected() const { return m_aSelectedEntries; }
//STRIP001      ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface > >
//STRIP001                                  hiddenControls() const { return m_aHiddenControlModels; }
//STRIP001
//STRIP001      ::com::sun::star::uno::Reference< ::com::sun::star::container::XNameContainer >
//STRIP001                              getFormsRoot() const { return m_xFormsRoot; }
//STRIP001  };

    //====================================================================
//STRIP001  inline const DataFlavorExVector& OControlTransferData::GetDataFlavorExVector() const
//STRIP001  {
//STRIP001      const_cast< OControlTransferData* >( this )->updateFormats( );
//STRIP001      return m_aCurrentFormats;
//STRIP001  }

    //====================================================================
    //= OControlExchange
    //====================================================================
//STRIP001  class OControlExchange : public OLocalExchange, public OControlTransferData
//STRIP001  {
//STRIP001  public:
//STRIP001      OControlExchange( );
//STRIP001
//STRIP001  public:
//STRIP001      static sal_uInt32       getFieldExchangeFormatId( );
//STRIP001      static sal_uInt32       getControlPathFormatId( );
//STRIP001      static sal_uInt32       getHiddenControlModelsFormatId( );
//STRIP001
//STRIP001      inline static sal_Bool  hasFieldExchangeFormat( const DataFlavorExVector& _rFormats );
//STRIP001      inline static sal_Bool  hasControlPathFormat( const DataFlavorExVector& _rFormats );
//STRIP001      inline static sal_Bool  hasHiddenControlModelsFormat( const DataFlavorExVector& _rFormats );
//STRIP001
//STRIP001  protected:
//STRIP001      virtual sal_Bool    GetData( const ::com::sun::star::datatransfer::DataFlavor& rFlavor );
//STRIP001      virtual void        AddSupportedFormats();
//STRIP001  };

    //====================================================================
    //= OControlExchangeHelper
    //====================================================================
/*N*/   class OControlExchangeHelper : public OLocalExchangeHelper
/*N*/   {
/*N*/   public:
/*N*/       OControlExchangeHelper(Window* _pDragSource) : OLocalExchangeHelper(_pDragSource) { }
/*N*/
//STRIP001      OControlExchange* operator->() const { return static_cast< OControlExchange* >( m_pTransferable ); }
//STRIP001      OControlExchange& operator*() const { return *static_cast< OControlExchange* >( m_pTransferable ); }
/*N*/
/*N*/   protected:
//STRIP001      virtual OLocalExchange* createExchange() const;
/*N*/   };

    //====================================================================
    //====================================================================
//STRIP001  inline sal_Bool OControlExchange::hasFieldExchangeFormat( const DataFlavorExVector& _rFormats )
//STRIP001  {
//STRIP001      return hasFormat( _rFormats, getFieldExchangeFormatId() );
//STRIP001  }
//STRIP001
//STRIP001  inline sal_Bool OControlExchange::hasControlPathFormat( const DataFlavorExVector& _rFormats )
//STRIP001  {
//STRIP001      return hasFormat( _rFormats, getControlPathFormatId() );
//STRIP001  }
//STRIP001
//STRIP001  inline sal_Bool OControlExchange::hasHiddenControlModelsFormat( const DataFlavorExVector& _rFormats )
//STRIP001  {
//STRIP001      return hasFormat( _rFormats, getHiddenControlModelsFormatId() );
//STRIP001  }

//........................................................................
}   // namespace svxform
//........................................................................

}//end of namespace binfilter
#endif

