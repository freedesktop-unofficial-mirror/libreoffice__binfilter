/*************************************************************************
 *
 *  $RCSfile: svx_fmmodel.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:43:40 $
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

#ifndef _TOOLS_DEBUG_HXX
#include <tools/debug.hxx>
#endif

#ifndef SVX_LIGHT
#ifndef _SFX_OBJSH_HXX //autogen
#include <bf_sfx2/objsh.hxx>
#endif
#else
class SfxObjectShell;
#endif

#pragma hdrstop

#ifndef _FM_FMMODEL_HXX
#include "fmmodel.hxx"
#endif

#ifndef _SVDIO_HXX
#include "svdio.hxx"
#endif

#ifndef _FM_PAGE_HXX
#include "fmpage.hxx"
#endif
#ifndef _SVX_FMUNDO_HXX
#include "fmundo.hxx"
#endif
#ifndef _SVX_SVDOBJ_HXX
#include "svdobj.hxx"
#endif
namespace binfilter {

/*N*/ TYPEINIT1(FmFormModel, SdrModel);

struct FmFormModelImplData
{
    FmXUndoEnvironment*     pUndoEnv;
    XubString               sNextPageId;
    sal_Bool                bOpenInDesignIsDefaulted;
    sal_Bool                bMovingPage;

    FmFormModelImplData()
        :pUndoEnv( NULL )
        ,bOpenInDesignIsDefaulted( sal_True )
        ,bMovingPage( sal_False )
    {
    }
};

/*************************************************************************
|*
|* Ctor
|*
\************************************************************************/
//STRIP001 FmFormModel::FmFormModel(SfxItemPool* pPool, SvPersist* pPers)
//STRIP001          :SdrModel(pPool, pPers, LOADREFCOUNTS)
//STRIP001          ,pObjShell(0)
//STRIP001          ,bStreamingOldVersion(sal_False)
//STRIP001          ,m_pImpl(NULL)
//STRIP001          ,m_bOpenInDesignMode(sal_False)
//STRIP001          ,m_bAutoControlFocus(sal_False)
//STRIP001 {
//STRIP001 #ifndef SVX_LIGHT
//STRIP001  m_pImpl = new FmFormModelImplData;
//STRIP001  m_pImpl->pUndoEnv = new FmXUndoEnvironment(*this);
//STRIP001  m_pImpl->pUndoEnv->acquire();
//STRIP001  m_pImpl->sNextPageId = '0';
//STRIP001 #endif
//STRIP001 }

/*************************************************************************
|*
|* Ctor
|*
\************************************************************************/
/*N*/ FmFormModel::FmFormModel(const XubString& rPath, SfxItemPool* pPool, SvPersist* pPers)
/*N*/           :SdrModel(rPath, pPool, pPers)
/*N*/           ,pObjShell(0)
/*N*/           ,bStreamingOldVersion(sal_False)
/*N*/           ,m_pImpl(NULL)
/*N*/           ,m_bOpenInDesignMode(sal_False)
/*N*/           ,m_bAutoControlFocus(sal_False)
/*N*/ {
/*N*/ #ifndef SVX_LIGHT
/*N*/   m_pImpl = new FmFormModelImplData;
/*N*/   m_pImpl->pUndoEnv = new FmXUndoEnvironment(*this);
/*N*/   m_pImpl->pUndoEnv->acquire();
/*N*/   m_pImpl->sNextPageId = '0';
/*N*/ #endif
/*N*/ }

/*************************************************************************
|*
|* Ctor
|*
\************************************************************************/
//STRIP001 FmFormModel::FmFormModel(SfxItemPool* pPool, SvPersist* pPers,
//STRIP001                       FASTBOOL bUseExtColorTable
//STRIP001                       )
//STRIP001          :SdrModel(pPool, pPers, bUseExtColorTable, LOADREFCOUNTS)
//STRIP001          ,pObjShell(0)
//STRIP001          ,bStreamingOldVersion(sal_False)
//STRIP001          ,m_pImpl(NULL)
//STRIP001 {
//STRIP001 #ifndef SVX_LIGHT
//STRIP001  m_pImpl = new FmFormModelImplData;
//STRIP001  m_pImpl->pUndoEnv = new FmXUndoEnvironment(*this);
//STRIP001  m_pImpl->pUndoEnv->acquire();
//STRIP001  m_pImpl->sNextPageId = '0';
//STRIP001 #endif
//STRIP001 }

/*************************************************************************
|*
|* Ctor
|*
\************************************************************************/
/*N*/ FmFormModel::FmFormModel(const XubString& rPath, SfxItemPool* pPool, SvPersist* pPers,
/*N*/                        FASTBOOL bUseExtColorTable)
/*N*/           :SdrModel(rPath, pPool, pPers, bUseExtColorTable, LOADREFCOUNTS)
/*N*/           ,pObjShell(0)
/*N*/           ,bStreamingOldVersion(sal_False)
/*N*/           ,m_bOpenInDesignMode(sal_False)
/*N*/           ,m_bAutoControlFocus(sal_False)
/*N*/ {
/*N*/ #ifndef SVX_LIGHT
/*N*/   m_pImpl = new FmFormModelImplData;
/*N*/   m_pImpl->pUndoEnv = new FmXUndoEnvironment(*this);
/*N*/   m_pImpl->pUndoEnv->acquire();
/*N*/   m_pImpl->sNextPageId = '0';
/*N*/ #endif
/*N*/ }

/*************************************************************************
|*
|* Dtor
|*
\************************************************************************/
/*N*/ FmFormModel::~FmFormModel()
/*N*/ {
/*N*/ #ifndef SVX_LIGHT
/*N*/   if (pObjShell && m_pImpl->pUndoEnv->IsListening(*pObjShell))
/*N*/       SetObjectShell(NULL);
/*N*/
/*N*/   ClearUndoBuffer();
/*N*/   // minimale grenze fuer undos
/*N*/   SetMaxUndoActionCount(1);
/*N*/
/*N*/   m_pImpl->pUndoEnv->release();
/*N*/   delete m_pImpl;
/*N*/
/*N*/ #endif
/*N*/ }

/*************************************************************************
|*
|* Copy-Ctor
|*
\************************************************************************/
//STRIP001 FmFormModel::FmFormModel(const FmFormModel&)
//STRIP001 {
//STRIP001  DBG_ERROR("FmFormModel: CopyCtor not implemented");
//STRIP001 }

/*************************************************************************
|*
|* Operator=
|*
\************************************************************************/
//STRIP001 void FmFormModel::operator=(const FmFormModel&)
//STRIP001 {
//STRIP001  DBG_ERROR("FmFormModel: operator= not implemented");
//STRIP001 }

/*************************************************************************
|*
|* Operator==
|*
\************************************************************************/
//STRIP001 FASTBOOL FmFormModel::operator==(const FmFormModel&) const
//STRIP001 {
//STRIP001  DBG_ERROR("FmFormModel: operator== not implemented");
//STRIP001  return sal_False;
//STRIP001 }


/*************************************************************************
|*
|* Erzeugt eine neue Seite
|*
\************************************************************************/
//STRIP001 SdrPage* FmFormModel::AllocPage(FASTBOOL bMasterPage)
//STRIP001 {
//STRIP001  return new FmFormPage(*this, NULL, bMasterPage);
//STRIP001 }

/*************************************************************************
|*
|* WriteData
|*
\************************************************************************/

/*N*/ void FmFormModel::WriteData(SvStream& rOut) const
/*N*/ {
/*N*/ #ifndef SVX_LIGHT
/*N*/
/*N*/   if( rOut.GetVersion() < SOFFICE_FILEFORMAT_50 )
/*N*/       ((FmFormModel*)this)->bStreamingOldVersion = sal_True;
/*N*/
/*N*/   SdrModel::WriteData( rOut );
/*N*/
/*N*/   //////////////////////////////////////////////////////////////////////
/*N*/   // Speichern der Option OpenInDesignMode
/*N*/   if (!bStreamingOldVersion)
/*N*/   {
/*N*/       SdrDownCompat aModelFormatCompat(rOut,STREAM_WRITE);
/*N*/
/*N*/       sal_uInt8 nTemp = m_bOpenInDesignMode;
/*N*/       rOut << nTemp;
/*N*/
/*N*/       nTemp = m_bAutoControlFocus;
/*N*/       rOut << nTemp;
/*N*/   }
/*N*/
/*N*/   ((FmFormModel*)this)->bStreamingOldVersion = sal_False;
/*N*/
/*N*/ #endif
/*N*/ }


/*************************************************************************
|*
|* ReadData
|*
\************************************************************************/
/*N*/ void FmFormModel::ReadData(const SdrIOHeader& rHead, SvStream& rIn)
/*N*/ {
/*N*/   if( rIn.GetVersion() < SOFFICE_FILEFORMAT_50 )
/*N*/       ((FmFormModel*)this)->bStreamingOldVersion = sal_True;
/*N*/
/*N*/   SdrModel::ReadData( rHead, rIn );
/*N*/
/*N*/   //////////////////////////////////////////////////////////////////////
/*N*/   // Lesen der Option OpenInDesignMode
/*N*/   if (!bStreamingOldVersion)
/*N*/   {
/*N*/       SdrDownCompat aCompat(rIn,STREAM_READ);
/*N*/       sal_uInt8 nTemp = 0;
/*N*/       rIn >> nTemp;
/*N*/
/*N*/       implSetOpenInDesignMode( nTemp ? sal_True : sal_False, sal_True );
/*N*/
/*N*/       if (aCompat.GetBytesLeft())
/*N*/       {   // it is a version which already wrote the AutoControlFocus flag
/*N*/           rIn >> nTemp;
/*N*/           m_bAutoControlFocus = nTemp ? sal_True : sal_False;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   ((FmFormModel*)this)->bStreamingOldVersion = sal_False;
/*N*/ }


/*************************************************************************
|*
|* InsertPage
|*
\************************************************************************/
/*N*/ void FmFormModel::InsertPage(SdrPage* pPage, sal_uInt16 nPos)
/*N*/ {
/*N*/ #ifndef SVX_LIGHT
/*N*/   // hack solange Methode intern
/*N*/   if (pObjShell && !m_pImpl->pUndoEnv->IsListening( *pObjShell ))
/*?*/       SetObjectShell(pObjShell);
/*N*/ #endif
/*N*/
/*N*/   SdrModel::InsertPage( pPage, nPos );
/*N*/
/*N*/ #ifndef SVX_LIGHT
/*N*/   if ( !m_pImpl->bMovingPage )
/*N*/   {
/*N*/       // this flag here is kind of a hack.
/*N*/       // When a page is moved, the SdrModel::MovePage calls an InsertPage only, but
/*N*/       // no preceding RemovePage. Thus, we (as a derivee) don't have a chance to see
/*N*/       // that the page which is just being inserted is (in real) already a part of the
/*N*/       // model. Especially, we do not have a change to notice that the UndoEnvironment
/*N*/       // already _knows_ the forms we're just going to add below.
/*N*/       //
/*N*/       // The real solution to this would have been to fix SdrModel::MovePage, which
/*N*/       // is buggy in it's current form (as it violates the semantics of InsertPage, which
/*N*/       // is: insert a page which /currently is not part of any model/).
/*N*/       // However, this change in the SdrModel is much too risky.
/*N*/       //
/*N*/       // Another solution to this would have been to track (in the UndoEnv) which pages
/*N*/       // we know, and ignore any AddForms calls which are for such a page.
/*N*/       // But I refuse to do this (much more) work to hack a bug in the SdrModel.
/*N*/       //
/*N*/       // I the decision is to do this "small hack" here (which I don't consider really
/*N*/       // bad).
/*N*/       //
/*N*/       // 2002-01-10 - #i3235# - fs@openoffice.org
/*N*/       //
/*N*/       if ( pPage )
/*N*/           m_pImpl->pUndoEnv->AddForms( static_cast< FmFormPage* >( pPage )->GetForms() );
/*N*/   }
/*N*/ #endif
/*N*/ }

/*************************************************************************
|*
|* MovePage
|*
\************************************************************************/
/*?*/ void FmFormModel::MovePage( USHORT nPgNum, USHORT nNewPos )
/*?*/ {DBG_ASSERT(0, "STRIP");//STRIP001
//STRIP001 #ifndef SVX_LIGHT
//STRIP001  m_pImpl->bMovingPage = sal_True;
//STRIP001      // see InsertPage for this
//STRIP001 #endif
//STRIP001
//STRIP001  SdrModel::MovePage( nPgNum, nNewPos );
//STRIP001
//STRIP001 #ifndef SVX_LIGHT
//STRIP001  m_pImpl->bMovingPage = sal_False;
//STRIP001 #endif
/*?*/ }

/*************************************************************************
|*
|* RemovePage
|*
\************************************************************************/
/*N*/ SdrPage* FmFormModel::RemovePage(sal_uInt16 nPgNum)
/*N*/ {
/*N*/   FmFormPage* pPage = (FmFormPage*)SdrModel::RemovePage(nPgNum);
/*N*/
/*N*/ #ifndef SVX_LIGHT
/*N*/   if (pPage)
/*N*/       m_pImpl->pUndoEnv->RemoveForms(pPage->GetForms());
/*N*/ #endif
/*N*/
/*N*/   return pPage;
/*N*/ }

/*************************************************************************
|*
|* InsertMasterPage
|*
\************************************************************************/
/*N*/ void FmFormModel::InsertMasterPage(SdrPage* pPage, sal_uInt16 nPos)
/*N*/ {
/*N*/ #ifndef SVX_LIGHT
/*N*/   // hack solange Methode intern
/*N*/   if (pObjShell && !m_pImpl->pUndoEnv->IsListening( *pObjShell ))
/*N*/       SetObjectShell(pObjShell);
/*N*/ #endif
/*N*/
/*N*/   SdrModel::InsertMasterPage(pPage, nPos);
/*N*/
/*N*/ #ifndef SVX_LIGHT
/*N*/   if (pPage)
/*N*/       m_pImpl->pUndoEnv->AddForms(((FmFormPage*)pPage)->GetForms());
/*N*/ #endif
/*N*/ }

/*************************************************************************
|*
|* RemoveMasterPage
|*
\************************************************************************/
/*N*/ SdrPage* FmFormModel::RemoveMasterPage(sal_uInt16 nPgNum)
/*N*/ {
/*N*/   FmFormPage* pPage = (FmFormPage*)SdrModel::RemoveMasterPage(nPgNum);
/*N*/
/*N*/ #ifndef SVX_LIGHT
/*N*/   if (pPage)
/*N*/       m_pImpl->pUndoEnv->RemoveForms(pPage->GetForms());
/*N*/ #endif
/*N*/
/*N*/   return pPage;
/*N*/ }

//------------------------------------------------------------------------
/*N*/ SdrLayerID FmFormModel::GetControlExportLayerId( const SdrObject& rObj ) const
/*N*/ {
/*N*/   return rObj.GetLayer();
/*N*/ }

//------------------------------------------------------------------------
/*N*/ void FmFormModel::implSetOpenInDesignMode( sal_Bool _bOpenDesignMode, sal_Bool _bForce )
/*N*/ {
/*N*/   if( ( _bOpenDesignMode != m_bOpenInDesignMode ) || _bForce )
/*N*/   {
/*N*/       m_bOpenInDesignMode = _bOpenDesignMode;
/*N*/
/*N*/       if ( pObjShell )
/*N*/           pObjShell->SetModified( sal_True );
/*N*/   }
/*N*/   // no matter if we really did it or not - from now on, it does not count as defaulted anymore
/*N*/   m_pImpl->bOpenInDesignIsDefaulted = sal_False;
/*N*/ }

//------------------------------------------------------------------------
/*N*/ void FmFormModel::SetOpenInDesignMode( sal_Bool bOpenDesignMode )
/*N*/ {
/*N*/ #ifndef SVX_LIGHT
/*N*/   implSetOpenInDesignMode( bOpenDesignMode, sal_False );
/*N*/ #endif
/*N*/ }

#ifndef SVX_LIGHT
//------------------------------------------------------------------------
/*N*/ sal_Bool FmFormModel::OpenInDesignModeIsDefaulted( )
/*N*/ {
/*N*/   return m_pImpl->bOpenInDesignIsDefaulted;
/*N*/ }
#endif

//------------------------------------------------------------------------
/*N*/ void FmFormModel::SetAutoControlFocus( sal_Bool _bAutoControlFocus )
/*N*/ {
/*N*/ #ifndef SVX_LIGHT
/*N*/   if( _bAutoControlFocus != m_bAutoControlFocus )
/*N*/   {
/*?*/       m_bAutoControlFocus = _bAutoControlFocus;
/*?*/       pObjShell->SetModified( sal_True );
/*N*/   }
/*N*/ #endif
/*N*/ }

//------------------------------------------------------------------------
/*N*/ void FmFormModel::SetObjectShell( SfxObjectShell* pShell )
/*N*/ {
/*N*/ #ifndef SVX_LIGHT
/*N*/   if (pShell == pObjShell)
/*N*/       return;
/*N*/
/*N*/   if (pObjShell)
/*N*/   {
/*N*/       m_pImpl->pUndoEnv->EndListening( *this );
/*N*/       m_pImpl->pUndoEnv->EndListening( *pObjShell );
/*N*/   }
/*N*/
/*N*/   pObjShell = pShell;
/*N*/
/*N*/   if (pObjShell)
/*N*/   {
/*N*/       m_pImpl->pUndoEnv->SetReadOnly(pObjShell->IsReadOnly() || pObjShell->IsReadOnlyUI());
/*N*/
/*N*/       if (!m_pImpl->pUndoEnv->IsReadOnly())
/*N*/            m_pImpl->pUndoEnv->StartListening(*this);
/*N*/
/*N*/       m_pImpl->pUndoEnv->StartListening( *pObjShell );
/*N*/   }
/*N*/ #endif
/*N*/ }

//------------------------------------------------------------------------
/*N*/ FmXUndoEnvironment&   FmFormModel::GetUndoEnv()
/*N*/ {
/*N*/   return *m_pImpl->pUndoEnv;
/*N*/ }

//------------------------------------------------------------------------
/*N*/ XubString FmFormModel::GetUniquePageId()
/*N*/ {
/*N*/   XubString sReturn = m_pImpl->sNextPageId;
/*N*/
/*N*/   xub_Unicode aNextChar = m_pImpl->sNextPageId.GetChar(m_pImpl->sNextPageId.Len() - 1);
/*N*/   sal_Bool bNeedNewChar = sal_False;
/*N*/   switch (aNextChar)
/*N*/   {
/*N*/       case '9' : aNextChar = 'A'; break;
/*N*/       case 'Z' : aNextChar = 'a'; break;
/*N*/       case 'z' : aNextChar = '0'; bNeedNewChar = sal_True; break;
/*N*/       default: ++aNextChar; break;
/*N*/   }
/*N*/   m_pImpl->sNextPageId.SetChar(m_pImpl->sNextPageId.Len() - 1, aNextChar);
/*N*/   if (bNeedNewChar)
/*N*/       m_pImpl->sNextPageId += '0';
/*N*/
/*N*/   return sReturn;
/*N*/ }


}
