/*************************************************************************
 *
 *  $RCSfile: svx_fmpage.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 15:46:41 $
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

#pragma hdrstop

#define ENABLE_BYTESTRING_STREAM_OPERATORS

#ifndef _SVX_FMPAGE_HXX
#include "fmpage.hxx"
#endif

// auto strip #ifndef _COM_SUN_STAR_BEANS_XPROPERTYSET_HPP_
// auto strip #include <com/sun/star/beans/XPropertySet.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_CONTAINER_XNAMECONTAINER_HPP_
// auto strip #include <com/sun/star/container/XNameContainer.hpp>
// auto strip #endif


#ifndef _SVX_FMMODEL_HXX
#include "fmmodel.hxx"
#endif

#ifndef SVX_LIGHT
// auto strip #ifndef _SVX_FMOBJ_HXX
// auto strip #include "fmobj.hxx"
// auto strip #endif
#endif

#ifndef SVX_LIGHT
#ifndef _SVX_FMRESIDS_HRC
#include "fmresids.hrc"
#endif
#endif

// auto strip #ifndef _SHL_HXX
// auto strip #include <tools/shl.hxx>
// auto strip #endif

// auto strip #ifndef _SVX_DIALMGR_HXX
// auto strip #include "dialmgr.hxx"
// auto strip #endif

#ifndef SVX_LIGHT
#ifndef _SVX_FMPGEIMP_HXX
#include "fmpgeimp.hxx"
#endif
#endif

#ifndef _SVDIO_HXX //autogen
#include "svdio.hxx"
#endif

#ifndef SVX_LIGHT
// auto strip #ifndef _SFX_OBJSH_HXX //autogen
// auto strip #include <bf_sfx2/objsh.hxx>
// auto strip #endif
#endif

// auto strip #ifndef _SVDITER_HXX //autogen
// auto strip #include "svditer.hxx"
// auto strip #endif

// auto strip #ifndef _SVDVIEW_HXX //autogen
// auto strip #include <svdview.hxx>
// auto strip #endif

// auto strip #ifndef _URLOBJ_HXX //autogen
// auto strip #include <tools/urlobj.hxx>
// auto strip #endif

// auto strip #ifndef _SV_HELP_HXX //autogen
// auto strip #include <vcl/help.hxx>
// auto strip #endif


#ifndef SVX_LIGHT
// auto strip #ifndef _SVX_FMGLOB_HXX
// auto strip #include "fmglob.hxx"
// auto strip #endif
#ifndef _SVX_FMPROP_HRC
#include "fmprop.hrc"
#endif
// auto strip #ifndef _SVX_FMPROP_HXX
// auto strip #include "fmprop.hxx"
// auto strip #endif
#ifndef _SVX_FMUNDO_HXX
#include "fmundo.hxx"
#endif
// auto strip #ifndef _SVX_FMTOOLS_HXX
// auto strip #include "fmtools.hxx"
// auto strip #endif
using namespace ::binfilter::svxform;//STRIP008 using namespace ::svxform;
#endif

// auto strip #ifndef _COMPHELPER_PROPERTY_HXX_
// auto strip #include <comphelper/property.hxx>
// auto strip #endif
namespace binfilter {


/*N*/ TYPEINIT1(FmFormPage, SdrPage);

//------------------------------------------------------------------
/*N*/ FmFormPage::FmFormPage(FmFormModel& rModel, StarBASIC* _pBasic, FASTBOOL bMasterPage)
/*N*/          :SdrPage(rModel, bMasterPage)
/*N*/          ,pBasic(_pBasic)
/*N*/ #ifndef SVX_LIGHT
/*N*/          ,pImpl(new FmFormPageImpl(this))
/*N*/ #else
/*N*/          ,pImpl(NULL)
/*N*/ #endif
/*N*/ {
/*N*/ }

//------------------------------------------------------------------
//STRIP001 FmFormPage::FmFormPage(const FmFormPage& rPage)
//STRIP001         :SdrPage(rPage)
//STRIP001         ,pBasic(0)
//STRIP001 #ifndef SVX_LIGHT
//STRIP001         ,pImpl(new FmFormPageImpl(this, *rPage.GetImpl()))
//STRIP001 #else
//STRIP001         ,pImpl(NULL)
//STRIP001 #endif
//STRIP001 {
//STRIP001  aPageName = rPage.aPageName;
//STRIP001 }

//------------------------------------------------------------------
/*N*/ FmFormPage::~FmFormPage()
/*N*/ {
/*N*/ #ifndef SVX_LIGHT
/*N*/   delete pImpl;
/*N*/ #endif
/*N*/ }

//------------------------------------------------------------------
/*N*/ void FmFormPage::WriteData(SvStream& rOut) const
/*N*/ {
/*N*/ #ifndef SVX_LIGHT
/*N*/   {
/*N*/       {
/*N*/           SdrDownCompat aVCCompat1( rOut, STREAM_WRITE );
/*N*/           sal_uInt16 n = 0;
/*N*/           rOut << n;
/*N*/       }
/*N*/       SdrPage::WriteData( rOut );
/*N*/       SdrDownCompat aVCCompat2( rOut, STREAM_WRITE );
/*N*/
/*N*/       rOut << ByteString(aPageName, gsl_getSystemTextEncoding());
/*N*/       rOut << (sal_uInt32)0x11051967;
/*N*/       rOut << (sal_uInt32)0x19670511;
/*N*/       sal_uInt16 nVer = 1;
/*N*/       rOut << nVer;
/*N*/       {
/*N*/           SdrDownCompat aVCCompat3( rOut, STREAM_WRITE);
/*N*/           sal_uInt32 nFormCount = 0;
/*N*/           rOut << nFormCount;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   // dont use the flag in that way: if (rOut.GetVersion() >= SOFFICE_FILEFORMAT_40)
/*N*/   if (rOut.GetVersion() >= 3830)
/*N*/   {
/*N*/       SdrDownCompat aCompat(rOut, STREAM_WRITE); // Fuer Abwaertskompatibilitaet (Lesen neuer Daten mit altem Code)
/*N*/       pImpl->WriteData(rOut);
/*N*/   }
/*N*/ #else
/*N*/   DBG_ERROR( "FmFormPage::WriteData: not to be called in SVX_LIGHT version!" );
/*N*/ #endif
/*N*/ }

//------------------------------------------------------------------
/*N*/ void FmFormPage::ReadData(const SdrIOHeader& rHead, SvStream& rIn)
/*N*/ {
/*N*/   {
/*N*/       {
/*N*/           SdrDownCompat aVCCompat1( rIn, STREAM_READ );
/*N*/       }
/*N*/       SdrPage::ReadData( rHead, rIn );
/*N*/       {
/*N*/           SdrDownCompat aVCCompat2( rIn, STREAM_READ );
/*N*/           ByteString aByteStringName;
/*N*/           rIn >> aByteStringName;
/*N*/           aPageName = String(aByteStringName, gsl_getSystemTextEncoding());
/*N*/       }
/*N*/   }
/*N*/
/*N*/   // dont use the flag in that way: if (rIn.GetVersion() >= SOFFICE_FILEFORMAT_40)
/*N*/   if (rIn.GetVersion() >= 3830 && rHead.GetVersion() >=14)
/*N*/   {
/*N*/       SdrDownCompat aCompat(rIn, STREAM_READ);    // Fuer Abwaertskompatibilitaet (Lesen neuer Daten mit altem Code)
/*N*/ #ifndef SVX_LIGHT
/*N*/       DBG_ASSERT( aCompat.GetBytesLeft(), "FmFormPage::ReadData: invalid file format!" );
/*N*/       if ( aCompat.GetBytesLeft() )
/*N*/           pImpl->ReadData(rHead, rIn);
/*N*/       // some old (corrupted) versions between 511 and 554 wrote an empty block here - and some of these documents
/*N*/       // are still out there
/*N*/       // So we allow for such an empty block ...
/*N*/ #endif
/*N*/   }
/*N*/ }

//------------------------------------------------------------------
/*N*/ void FmFormPage::SetModel(SdrModel* pNewModel)
/*N*/ {
/*N*/   SdrPage::SetModel( pNewModel );
/*N*/ }

//------------------------------------------------------------------
/*N*/ SdrPage* FmFormPage::Clone() const
/*N*/ {
/*N*/   return new FmFormPage(*this);
/*N*/   // hier fehlt noch ein kopieren der Objekte
/*N*/ }

//------------------------------------------------------------------
/*N*/ void FmFormPage::NbcInsertObject(SdrObject* pObj,
/*N*/                                sal_uInt32 nPos,
/*N*/                                const SdrInsertReason* pReason)
/*N*/ {
/*N*/   SdrPage::NbcInsertObject(pObj, nPos, pReason);
/*N*/ }

//------------------------------------------------------------------
/*N*/ void FmFormPage::InsertObject(SdrObject* pObj, sal_uInt32 nPos,
/*N*/                             const SdrInsertReason* pReason)
/*N*/ {
/*N*/   SdrPage::InsertObject( pObj, nPos, pReason );
/*N*/ #ifndef SVX_LIGHT
/*N*/   if (GetModel() && (!pReason || pReason->GetReason() != SDRREASON_STREAMING))
/*N*/       ((FmFormModel*)GetModel())->GetUndoEnv().Inserted(pObj);
/*N*/ #endif
/*N*/ }

#ifndef SVX_LIGHT
//------------------------------------------------------------------
//STRIP001 void FmFormPage::InsertFormObjectEnsureEnv(const SdrObject* _pSourceObject, SdrObject* _pClone, sal_Bool _bTryPreserveName, sal_uInt32 _nPos,
//STRIP001  const SdrInsertReason* _pReason)
//STRIP001 {
//STRIP001  DBG_ERROR("FmFormPage::InsertFormObjectEnsureEnv : obsolete method used (maybe I should write a changes mail ?) !");
//STRIP001  InsertObject(_pClone, _nPos, _pReason);
//STRIP001  return;
//STRIP001 }

//------------------------------------------------------------------
//STRIP001 sal_Bool FmFormPage::EnsureFormObjectEnv(const SdrObject* _pObj)
//STRIP001 {
//STRIP001  DBG_ERROR("FmFormPage::EnsureFormObjectEnv : obsolete method used (maybe I should write a changes mail ?) !");
//STRIP001  return sal_False;
//STRIP001 }
#endif

//------------------------------------------------------------------
/*N*/ const ::com::sun::star::uno::Reference< ::com::sun::star::container::XNameContainer > & FmFormPage::GetForms() const
/*N*/ {
/*N*/ #ifndef SVX_LIGHT
/*N*/   return pImpl->getForms();
/*N*/ #else
/*N*/   static ::com::sun::star::uno::Reference< ::com::sun::star::container::XNameContainer >  aRef;
/*N*/   return aRef;
/*N*/ #endif
/*N*/ }

//------------------------------------------------------------------
//STRIP001 sal_Bool FmFormPage::RequestHelp( Window* pWindow, SdrView* pView,
//STRIP001                            const HelpEvent& rEvt )
//STRIP001 {
//STRIP001 #ifndef SVX_LIGHT
//STRIP001  if( !pView->IsAction() )
//STRIP001  {
//STRIP001      Point aPos = rEvt.GetMousePosPixel();
//STRIP001      aPos = pWindow->ScreenToOutputPixel( aPos );
//STRIP001      aPos = pWindow->PixelToLogic( aPos );
//STRIP001
//STRIP001      SdrObject* pObj = NULL;
//STRIP001      SdrPageView* pPV = NULL;
//STRIP001      if( pView->PickObj( aPos, 0, pObj, pPV, SDRSEARCH_DEEP ) )
//STRIP001      {
//STRIP001          // Ein Object getroffen
//STRIP001          if( pObj->ISA(FmFormObj) )
//STRIP001          {
//STRIP001              UniString aHelpText;
//STRIP001              ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet >  xSet(((FmFormObj*)pObj)->GetUnoControlModel(), ::com::sun::star::uno::UNO_QUERY);
//STRIP001              if (xSet.is())
//STRIP001              {
//STRIP001                  if (::comphelper::hasProperty(FM_PROP_HELPTEXT, xSet))
//STRIP001                      aHelpText = ::comphelper::getString(xSet->getPropertyValue(FM_PROP_HELPTEXT)).getStr();
//STRIP001
//STRIP001                  if (!aHelpText.Len() && ::comphelper::hasProperty(FM_PROP_TARGET_URL, xSet))
//STRIP001                  {
//STRIP001                      ::rtl::OUString aText = ::comphelper::getString(xSet->getPropertyValue(FM_PROP_TARGET_URL));
//STRIP001                      INetURLObject aUrl(aText);
//STRIP001
//STRIP001                      // testen, ob es ein Protokoll-Typ ist, den ich anzeigen will
//STRIP001                      INetProtocol aProtocol = aUrl.GetProtocol();
//STRIP001                      static const INetProtocol s_aQuickHelpSupported[] =
//STRIP001                          {   INET_PROT_FTP, INET_PROT_HTTP, INET_PROT_FILE, INET_PROT_MAILTO, INET_PROT_NEWS,
//STRIP001                              INET_PROT_HTTPS, INET_PROT_JAVASCRIPT, INET_PROT_IMAP, INET_PROT_POP3,
//STRIP001                              INET_PROT_VIM, INET_PROT_LDAP
//STRIP001                          };
//STRIP001                      for (sal_uInt16 i=0; i<sizeof(s_aQuickHelpSupported)/sizeof(s_aQuickHelpSupported[0]); ++i)
//STRIP001                          if (s_aQuickHelpSupported[i] == aProtocol)
//STRIP001                          {
//STRIP001                              aHelpText = INetURLObject::decode(aUrl.GetURLNoPass(), '%', INetURLObject::DECODE_UNAMBIGUOUS);
//STRIP001                              break;
//STRIP001                          }
//STRIP001                  }
//STRIP001              }
//STRIP001              if ( aHelpText.Len() != 0 )
//STRIP001              {
//STRIP001                  // Hilfe anzeigen
//STRIP001                  Rectangle aItemRect = pObj->GetBoundRect();
//STRIP001                  aItemRect = pWindow->LogicToPixel( aItemRect );
//STRIP001                  Point aPt = pWindow->OutputToScreenPixel( aItemRect.TopLeft() );
//STRIP001                  aItemRect.Left()   = aPt.X();
//STRIP001                  aItemRect.Top()    = aPt.Y();
//STRIP001                  aPt = pWindow->OutputToScreenPixel( aItemRect.BottomRight() );
//STRIP001                  aItemRect.Right()  = aPt.X();
//STRIP001                  aItemRect.Bottom() = aPt.Y();
//STRIP001                  if( rEvt.GetMode() == HELPMODE_BALLOON )
//STRIP001                      Help::ShowBalloon( pWindow, aItemRect.Center(), aItemRect, aHelpText);
//STRIP001                  else
//STRIP001                      Help::ShowQuickHelp( pWindow, aItemRect, aHelpText );
//STRIP001              }
//STRIP001              return sal_True;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 #endif
//STRIP001  return sal_False;
//STRIP001 }

//------------------------------------------------------------------
//STRIP001 SdrObject* FmFormPage::NbcRemoveObject(sal_uInt32 nObjNum)
//STRIP001 {
//STRIP001  return SdrPage::NbcRemoveObject(nObjNum);
//STRIP001 }

//------------------------------------------------------------------
/*N*/ SdrObject* FmFormPage::RemoveObject(sal_uInt32 nObjNum)
/*N*/ {
/*N*/   SdrObject* pObj = SdrPage::RemoveObject(nObjNum);
/*N*/ #ifndef SVX_LIGHT
/*N*/   if (pObj && GetModel())
/*N*/       ((FmFormModel*)GetModel())->GetUndoEnv().Removed(pObj);
/*N*/ #endif
/*N*/   return pObj;
/*N*/ }

//------------------------------------------------------------------
//STRIP001 SdrObject* FmFormPage::NbcReplaceObject(SdrObject* pNewObj, sal_uInt32 nObjNum)
//STRIP001 {
//STRIP001  return SdrPage::NbcReplaceObject(pNewObj, nObjNum);
//STRIP001 }

//------------------------------------------------------------------
/*N*/ SdrObject* FmFormPage::ReplaceObject(SdrObject* pNewObj, sal_uInt32 nObjNum)
/*N*/ {
/*N*/   return SdrPage::ReplaceObject(pNewObj, nObjNum);
/*N*/ }


//------------------------------------------------------------------
//STRIP001 void FmFormPage::SetBasic( StarBASIC* pBas )
//STRIP001 {
//STRIP001 }

//STRIP001 void FmFormPage::RequestBasic()
//STRIP001 {
//STRIP001 }

//STRIP001 XubString FmFormPage::GetLinkData( const XubString& rLinkName )
//STRIP001 {
//STRIP001  return XubString();
//STRIP001 }

//STRIP001 void FmFormPage::SetLinkData( const XubString& rLinkName, const XubString& rLinkData )
//STRIP001 {
//STRIP001 }
//STRIP001
//STRIP001 void FmFormPage::UpdateLinkData( const XubString& rLinkName, const XubString& rLinkData )
//STRIP001 {
//STRIP001 }
//STRIP001
//STRIP001 SfxJSArray* FmFormPage::GetFormsArray() const
//STRIP001 {
//STRIP001  return 0;
//STRIP001 }




}
