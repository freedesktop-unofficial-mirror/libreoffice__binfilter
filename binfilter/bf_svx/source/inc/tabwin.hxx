/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: tabwin.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-08 06:11:22 $
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
#ifndef _SVX_TABWIN_HXX
#define _SVX_TABWIN_HXX

// auto strip #ifndef _SVTREEBOX_HXX //autogen
// auto strip #include <svtools/svtreebx.hxx>
// auto strip #endif

// auto strip #ifndef _SV_FLOATWIN_HXX //autogen
// auto strip #include <vcl/floatwin.hxx>
// auto strip #endif

// auto strip #ifndef _BASEDLGS_HXX //autogen
// auto strip #include <bf_sfx2/basedlgs.hxx>
// auto strip #endif

#ifndef _SFX_CHILDWIN_HXX //autogen
#include <bf_sfx2/childwin.hxx>
#endif

// auto strip #ifndef _SFXCTRLITEM_HXX //autogen
// auto strip #include <bf_sfx2/ctrlitem.hxx>
// auto strip #endif

// auto strip #ifndef _COM_SUN_STAR_FORM_XFORM_HPP_
// auto strip #include <com/sun/star/form/XForm.hpp>
// auto strip #endif

//#ifndef _SVX_FMTOOLS_HXX
//#include "fmtools.hxx"
//#endif

// auto strip #ifndef _COMPHELPER_PROPERTY_MULTIPLEX_HXX_
// auto strip #include <comphelper/propmultiplex.hxx>
// auto strip #endif
// auto strip #ifndef _TRANSFER_HXX
// auto strip #include <svtools/transfer.hxx>
// auto strip #endif
// auto strip #ifndef SVX_DBTOOLSCLIENT_HXX
// auto strip #include "dbtoolsclient.hxx"
// auto strip #endif
namespace binfilter {
//end of namespace binfilter
//==================================================================
class FmFieldWin;
//STRIP001 class FmFieldWinListBox
//STRIP001                  :public SvTreeListBox
//STRIP001 {
//STRIP001  FmFieldWin* pTabWin;
//STRIP001
//STRIP001 protected:
//STRIP001 //   virtual void Command( const CommandEvent& rEvt );
//STRIP001
//STRIP001 public:
//STRIP001  FmFieldWinListBox( FmFieldWin* pParent );
//STRIP001  virtual ~FmFieldWinListBox();
//STRIP001
//STRIP001  sal_Int8 AcceptDrop( const AcceptDropEvent& rEvt );
//STRIP001  sal_Int8 ExecuteDrop( const ExecuteDropEvent& rEvt );
//STRIP001
//STRIP001 protected:
//STRIP001  // DragSourceHelper
//STRIP001  virtual void StartDrag( sal_Int8 nAction, const Point& rPosPixel );
//STRIP001
//STRIP001  // SvLBox
//STRIP001  virtual BOOL DoubleClickHdl();
//STRIP001 };

//========================================================================
class FmFormShell;
//STRIP001 class FmFieldWinData
//STRIP001 {
//STRIP001 public:
//STRIP001  FmFieldWinData();
//STRIP001  ~FmFieldWinData();
//STRIP001 };

//========================================================================
//STRIP001 class FmFieldWin :public SfxFloatingWindow
//STRIP001                  ,public SfxControllerItem
//STRIP001                  ,public ::comphelper::OPropertyChangeListener
//STRIP001                  ,public ::svxform::OStaticDataAccessTools
//STRIP001 {
//STRIP001  ::osl::Mutex        m_aMutex;
//STRIP001  FmFieldWinListBox* pListBox;
//STRIP001  FmFieldWinData*    pData;
//STRIP001  ::rtl::OUString    m_aDatabaseName,
//STRIP001                     m_aObjectName;
//STRIP001  sal_Int32          m_nObjectType;
//STRIP001
//STRIP001  ::comphelper::OPropertyChangeMultiplexer*   m_pChangeListener;
//STRIP001
//STRIP001 public:
//STRIP001  FmFieldWin(SfxBindings *pBindings,
//STRIP001             SfxChildWindow *pMgr, Window* pParent);
//STRIP001
//STRIP001  virtual ~FmFieldWin();
//STRIP001  virtual void Resize();
//STRIP001  virtual sal_Bool Close();
//STRIP001  virtual void GetFocus();
//STRIP001  virtual long PreNotify( NotifyEvent& _rNEvt );
//STRIP001  virtual void StateChanged(sal_uInt16 nSID, SfxItemState eState,
//STRIP001                            const SfxPoolItem* pState);
//STRIP001
//STRIP001  FmFieldWinData* GetData()  const {return pData;}
//STRIP001
//STRIP001  sal_Bool Update(FmFormShell*);
//STRIP001  sal_Bool Update(const ::com::sun::star::uno::Reference< ::com::sun::star::form::XForm > &);
//STRIP001  void FillInfo( SfxChildWinInfo& rInfo ) const;
//STRIP001
//STRIP001  const ::rtl::OUString&  GetDatabaseName() const { return m_aDatabaseName; }
//STRIP001  const ::rtl::OUString&  GetObjectName() const { return m_aObjectName; }
//STRIP001  sal_Int32               GetObjectType() const { return m_nObjectType; }
//STRIP001
//STRIP001  sal_Bool    createSelectionControls( );
//STRIP001
//STRIP001 protected:
//STRIP001  // FmXChangeListener
//STRIP001  virtual void _propertyChanged(const ::com::sun::star::beans::PropertyChangeEvent& evt) throw( ::com::sun::star::uno::RuntimeException );
//STRIP001
//STRIP001 protected:
//STRIP001  inline          SfxBindings&    GetBindings()       { return SfxControllerItem::GetBindings(); }
//STRIP001  inline  const   SfxBindings&    GetBindings() const { return SfxControllerItem::GetBindings(); }
//STRIP001 };

//========================================================================
class FmFieldWinMgr : public SfxChildWindow
{
public:
    FmFieldWinMgr(Window *pParent, sal_uInt16 nId,
        SfxBindings *pBindings, SfxChildWinInfo *pInfo);
    SFX_DECL_CHILDWINDOW(FmFieldWinMgr);
};


}
#endif

