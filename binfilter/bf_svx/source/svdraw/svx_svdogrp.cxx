/*************************************************************************
 *
 *  $RCSfile: svx_svdogrp.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:46:18 $
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

#ifndef _SVXLINKMGR_HXX //autogen
#include <linkmgr.hxx>
#endif

#ifndef _UCBHELPER_CONTENT_HXX_
#include <ucbhelper/content.hxx>
#endif
#ifndef _UCBHELPER_CONTENTBROKER_HXX_
#include <ucbhelper/contentbroker.hxx>
#endif
#ifndef _UNOTOOLS_DATETIME_HXX_
#include <unotools/datetime.hxx>
#endif

#include "svdogrp.hxx"

#ifndef SVX_LIGHT
#ifndef _LNKBASE_HXX //autogen
#include <so3/lnkbase.hxx>
#endif
#endif

#ifndef _URLOBJ_HXX
#include <tools/urlobj.hxx>
#endif

#include <svtools/urihelper.hxx>

#include "xpool.hxx"
#include "xpoly.hxx"

#include "svdxout.hxx"
#include "svdmodel.hxx"
#include "svdpage.hxx"
#include "svditer.hxx"
#include "svdobj.hxx"
#include "svdtrans.hxx"
#include "svdio.hxx"
#include "svdetc.hxx"
#include "svdattrx.hxx"  // NotPersistItems
#include "svdoedge.hxx"  // #32383# Die Verbinder nach Move nochmal anbroadcasten
#include "svdglob.hxx"   // StringCache
#include "svdstr.hrc"    // Objektname

#ifndef _PERSIST_HXX //autogen
#include <so3/persist.hxx>
#endif

#ifndef _SVX_SVXIDS_HRC
#include "svxids.hrc"
#endif

#ifndef _SFX_WHITER_HXX
#include <svtools/whiter.hxx>
#endif
namespace binfilter {

#ifndef SVX_LIGHT

////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  @@@@  @@@@@  @@@@@@   @@@@@ @@@@@   @@@@  @@  @@ @@@@@   @@    @@ @@  @@ @@  @@
// @@  @@ @@  @@     @@  @@     @@  @@ @@  @@ @@  @@ @@  @@  @@    @@ @@@ @@ @@ @@
// @@  @@ @@@@@      @@  @@ @@@ @@@@@  @@  @@ @@  @@ @@@@@   @@    @@ @@@@@@ @@@@
// @@  @@ @@  @@ @@  @@  @@  @@ @@  @@ @@  @@ @@  @@ @@      @@    @@ @@ @@@ @@ @@
//  @@@@  @@@@@   @@@@    @@@@@ @@  @@  @@@@   @@@@  @@      @@@@@ @@ @@  @@ @@  @@
//
// ImpSdrObjGroupLink zur Verbindung von SdrObjGroup und LinkManager
//
// Einem solchen Link merke ich mir als SdrObjUserData am Objekt. Im Gegensatz
// zum Grafik-Link werden die ObjektDaten jedoch kopiert (fuer Paint, etc.).
// Die Information ob das Objekt ein Link ist besteht genau darin, dass dem
// Objekt ein entsprechender UserData-Record angehaengt ist oder nicht.
//
////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 class ImpSdrObjGroupLink: public ::so3::SvBaseLink
//STRIP001 {
//STRIP001  SdrObject* pSdrObj;
//STRIP001 public:
//STRIP001  ImpSdrObjGroupLink( SdrObject* pObj1 )
//STRIP001      : ::so3::SvBaseLink( ::so3::LINKUPDATE_ONCALL, FORMAT_FILE ),
//STRIP001      pSdrObj( pObj1 )
//STRIP001  {}
//STRIP001  virtual ~ImpSdrObjGroupLink();
//STRIP001  virtual void Closed();
//STRIP001  virtual void DataChanged( const String& rMimeType,
//STRIP001                              const ::com::sun::star::uno::Any & rValue );
//STRIP001
//STRIP001  FASTBOOL     Connect() { return 0 != GetRealObject(); }
//STRIP001 };

////////////////////////////////////////////////////////////////////////////////////////////////////


//STRIP001 ImpSdrObjGroupLink::~ImpSdrObjGroupLink()
//STRIP001 {
//STRIP001 }

// Closed() wird gerufen, wenn die Verknüpfung geloesst wird.

//STRIP001 void ImpSdrObjGroupLink::Closed()
//STRIP001 {
//STRIP001  if (pSdrObj!=NULL) {
//STRIP001      // pLink des Objekts auf NULL setzen, da die Link-Instanz ja gerade destruiert wird.
//STRIP001      ImpSdrObjGroupLinkUserData* pData=((SdrObjGroup*)pSdrObj)->GetLinkUserData();
//STRIP001      if (pData!=NULL) pData->pLink=NULL;
//STRIP001      ((SdrObjGroup*)pSdrObj)->ReleaseGroupLink();
//STRIP001  }
//STRIP001  SvBaseLink::Closed();
//STRIP001 }


//STRIP001 void ImpSdrObjGroupLink::DataChanged( const String& ,
//STRIP001                                    const ::com::sun::star::uno::Any& )
//STRIP001 {
//STRIP001  FASTBOOL bForceReload=FALSE;
//STRIP001  SdrModel* pModel = pSdrObj ? pSdrObj->GetModel() : 0;
//STRIP001  SvxLinkManager* pLinkManager= pModel ? pModel->GetLinkManager() : 0;
//STRIP001  if( pLinkManager )
//STRIP001  {
//STRIP001      ImpSdrObjGroupLinkUserData* pData=
//STRIP001                              ((SdrObjGroup*)pSdrObj)->GetLinkUserData();
//STRIP001      if( pData )
//STRIP001      {
//STRIP001          String aFile;
//STRIP001          String aName;
//STRIP001          pLinkManager->GetDisplayNames( this, 0, &aFile, &aName, 0 );
//STRIP001
//STRIP001          if( !pData->aFileName.Equals( aFile ) ||
//STRIP001              !pData->aObjName.Equals( aName ))
//STRIP001          {
//STRIP001              pData->aFileName=aFile;
//STRIP001              pData->aObjName=aName;
//STRIP001              pSdrObj->SetChanged();
//STRIP001              bForceReload=TRUE;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  if( pSdrObj )
//STRIP001      ((SdrObjGroup*)pSdrObj)->ReloadLinkedGroup( bForceReload );
//STRIP001 }

#endif // SVX_LIGHT

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// @@    @@ @@  @@ @@  @@  @@  @@  @@@@@ @@@@@@ @@@@@   @@@@@   @@@@  @@@@@@  @@@@
// @@    @@ @@@ @@ @@ @@   @@  @@ @@     @@     @@  @@  @@  @@ @@  @@   @@   @@  @@
// @@    @@ @@@@@@ @@@@    @@  @@  @@@@  @@@@@  @@@@@   @@  @@ @@@@@@   @@   @@@@@@
// @@    @@ @@ @@@ @@@@@   @@  @@     @@ @@     @@  @@  @@  @@ @@  @@   @@   @@  @@
// @@@@@ @@ @@  @@ @@  @@   @@@@  @@@@@  @@@@@@ @@  @@  @@@@@  @@  @@   @@   @@  @@
//
////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ TYPEINIT1(ImpSdrObjGroupLinkUserData,SdrObjUserData);


/*N*/ ImpSdrObjGroupLinkUserData::ImpSdrObjGroupLinkUserData(SdrObject* pObj1):
/*N*/   SdrObjUserData(SdrInventor,SDRUSERDATA_OBJGROUPLINK,0),
/*N*/   pObj(pObj1),
/*N*/   nDrehWink0(0),
/*N*/   nShearWink0(0),
/*N*/   pLink(NULL),
/*N*/   nObjNum(0),
/*N*/   nPageNum(0),
/*N*/   bMasterPage(FALSE),
/*N*/   bOrigPos(FALSE),
/*N*/   bOrigSize(FALSE),
/*N*/   bOrigRotate(FALSE),
/*N*/   bOrigShear(FALSE)
/*N*/ {
/*N*/ }


/*N*/ ImpSdrObjGroupLinkUserData::~ImpSdrObjGroupLinkUserData()
/*N*/ {
/*N*/ #ifndef SVX_LIGHT
/*?*/   DBG_ASSERT(0, "STRIP"); //STRIP001 delete pLink;
/*N*/ #endif
/*N*/ }


/*N*/ SdrObjUserData* ImpSdrObjGroupLinkUserData::Clone(SdrObject* pObj1) const
/*N*/ {
/*N*/   ImpSdrObjGroupLinkUserData* pData=new ImpSdrObjGroupLinkUserData(pObj1);
/*N*/   pData->aFileName  =aFileName;
/*N*/   pData->aObjName   =aObjName;
/*N*/   pData->aFileDate0 =aFileDate0;
/*N*/   pData->aSnapRect0 =aSnapRect0;
/*N*/   pData->nDrehWink0 =nDrehWink0;
/*N*/   pData->nShearWink0=nShearWink0;
/*N*/   pData->nObjNum    =nObjNum;
/*N*/   pData->nPageNum   =nPageNum;
/*N*/   pData->bMasterPage=bMasterPage;
/*N*/   pData->bOrigPos   =bOrigPos;
/*N*/   pData->bOrigSize  =bOrigSize;
/*N*/   pData->bOrigRotate=bOrigRotate;
/*N*/   pData->bOrigShear =bOrigShear;
/*N*/   pData->pLink=NULL;
/*N*/   //pObj1->ImpLinkAnmeldung();
/*N*/   return pData;
/*N*/ }


/*N*/ void ImpSdrObjGroupLinkUserData::WriteData(SvStream& rOut)
/*N*/ {
/*N*/   SdrObjUserData::WriteData(rOut);
/*N*/
/*N*/   // Fuer Abwaertskompatibilitaet (Lesen neuer Daten mit altem Code)
/*N*/   SdrDownCompat aCompat(rOut, STREAM_WRITE);
/*N*/
/*N*/ #ifdef DBG_UTIL
/*N*/   aCompat.SetID("ImpSdrObjGroupLinkUserData");
/*N*/ #endif
/*N*/
/*N*/   String aRelFileName;
/*N*/
/*N*/   if( aFileName.Len() )
/*N*/   {
/*N*/       aRelFileName = INetURLObject::AbsToRel( aFileName,
/*N*/                                               INetURLObject::WAS_ENCODED,
/*N*/                                               INetURLObject::DECODE_UNAMBIGUOUS );
/*N*/   }
/*N*/
/*N*/   rOut.WriteByteString( aRelFileName );
/*N*/
/*N*/   // UNICODE: rOut << aObjName;
/*N*/   rOut.WriteByteString(aObjName);
/*N*/
/*N*/   rOut << UINT32(aFileDate0.GetDate());
/*N*/   rOut << UINT32(aFileDate0.GetTime());
/*N*/   rOut << aSnapRect0;
/*N*/   rOut << nDrehWink0;
/*N*/   rOut << nShearWink0;
/*N*/   rOut << BOOL(bMasterPage);
/*N*/   rOut << nPageNum;
/*N*/   rOut << nObjNum;
/*N*/   rOut << BOOL(bOrigPos);
/*N*/   rOut << BOOL(bOrigSize);
/*N*/   rOut << BOOL(bOrigRotate);
/*N*/   rOut << BOOL(bOrigShear);
/*N*/ }

/*N*/ void ImpSdrObjGroupLinkUserData::ReadData(SvStream& rIn)
/*N*/ {
/*N*/   SdrObjUserData::ReadData(rIn);
/*N*/   // Fuer Abwaertskompatibilitaet (Lesen neuer Daten mit altem Code)
/*N*/   SdrDownCompat aCompat(rIn, STREAM_READ);
/*N*/
/*N*/ #ifdef DBG_UTIL
/*N*/   aCompat.SetID("ImpSdrObjGroupLinkUserData");
/*N*/ #endif
/*N*/
/*N*/   BOOL bTmp;
/*N*/   UINT32 nTmp32;
/*N*/   String aFileNameRel;
/*N*/
/*N*/   rIn.ReadByteString(aFileNameRel);
/*N*/
/*N*/   if( aFileNameRel.Len() )
/*N*/   {
/*N*/       aFileName = ::URIHelper::SmartRelToAbs( aFileNameRel, FALSE,
/*N*/                                               INetURLObject::WAS_ENCODED,
/*N*/                                               INetURLObject::DECODE_UNAMBIGUOUS );
/*N*/   }
/*N*/   else
/*N*/       aFileName.Erase();
/*N*/
/*N*/   // UNICODE: rIn >> aObjName;
/*N*/   rIn.ReadByteString(aObjName);
/*N*/
/*N*/   rIn >> nTmp32; aFileDate0.SetDate(nTmp32);
/*N*/   rIn >> nTmp32; aFileDate0.SetTime(nTmp32);
/*N*/   rIn >> aSnapRect0;
/*N*/   rIn >> nDrehWink0;
/*N*/   rIn >> nShearWink0;
/*N*/   rIn >> bTmp; bMasterPage=bTmp;
/*N*/   rIn >> nPageNum;
/*N*/   rIn >> nObjNum;
/*N*/   rIn >> bTmp; bOrigPos   =bTmp;
/*N*/   rIn >> bTmp; bOrigSize  =bTmp;
/*N*/   rIn >> bTmp; bOrigRotate=bTmp;
/*N*/   rIn >> bTmp; bOrigShear =bTmp;
/*N*/ }


/*N*/ void ImpSdrObjGroupLinkUserData::AfterRead()
/*N*/ {
/*N*/   if (pObj!=NULL) {
/*N*/       ((SdrObjGroup*)pObj)->ImpLinkAnmeldung();
/*N*/       // lt. Anweisung von MB kein automatisches Reload mehr
/*N*/       //((SdrObjGroup*)pObj)->ReloadLinkedGroup();
/*N*/   }
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////
//
//   @@@@  @@@@@  @@@@@@   @@@@  @@@@@   @@@@  @@  @@ @@@@@
//  @@  @@ @@  @@     @@  @@     @@  @@ @@  @@ @@  @@ @@  @@
//  @@  @@ @@@@@      @@  @@ @@@ @@@@@  @@  @@ @@  @@ @@@@@
//  @@  @@ @@  @@ @@  @@  @@  @@ @@  @@ @@  @@ @@  @@ @@
//   @@@@  @@@@@   @@@@    @@@@@ @@  @@  @@@@   @@@@  @@
//
////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ TYPEINIT1(SdrObjGroup,SdrObject);


/*N*/ SdrObjGroup::SdrObjGroup()
/*N*/ {
/*N*/   pSub=new SdrObjList(NULL,NULL);
/*N*/   pSub->SetOwnerObj(this);
/*N*/   pSub->SetListKind(SDROBJLIST_GROUPOBJ);
/*N*/   bRefPoint=FALSE;
/*N*/   nDrehWink=0;
/*N*/   nShearWink=0;
/*N*/   bClosedObj=FALSE;
/*N*/   mpGroupItemSet = NULL;
/*N*/ }


/*N*/ SdrObjGroup::~SdrObjGroup()
/*N*/ {
/*N*/   ReleaseGroupLink();
/*N*/   delete pSub;
/*N*/   if(mpGroupItemSet)
/*?*/       delete mpGroupItemSet;
/*N*/ }


//STRIP001 void SdrObjGroup::SetGroupLink(const String& rFileName, const String& rObjName)
//STRIP001 {
//STRIP001  ImpSdrObjGroupLinkUserData* pData=GetLinkUserData();
//STRIP001  if (pData!=NULL) {
//STRIP001      nDrehWink-=pData->nDrehWink0;
//STRIP001      nShearWink-=pData->nShearWink0;
//STRIP001      ReleaseGroupLink();
//STRIP001  }
//STRIP001  aName=rObjName;
//STRIP001  pData=new ImpSdrObjGroupLinkUserData(this);
//STRIP001  pData->aFileName=rFileName;
//STRIP001  pData->aObjName=rObjName;
//STRIP001  InsertUserData(pData);
//STRIP001  ImpLinkAnmeldung();
//STRIP001 }


/*N*/ void SdrObjGroup::ReleaseGroupLink()
/*N*/ {
/*N*/   ImpLinkAbmeldung();
/*N*/   USHORT nAnz=GetUserDataCount();
/*N*/   for (USHORT nNum=nAnz; nNum>0;) {
/*N*/       nNum--;
/*N*/       SdrObjUserData* pData=GetUserData(nNum);
/*N*/       if (pData->GetInventor()==SdrInventor && pData->GetId()==SDRUSERDATA_OBJGROUPLINK) {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/            DeleteUserData(nNum);
/*N*/       }
/*N*/   }
/*N*/ }


/*N*/ ImpSdrObjGroupLinkUserData* SdrObjGroup::GetLinkUserData() const
/*N*/ {
/*N*/   ImpSdrObjGroupLinkUserData* pData=NULL;
/*N*/   USHORT nAnz=GetUserDataCount();
/*N*/   for (USHORT nNum=nAnz; nNum>0 && pData==NULL;) {
/*N*/       nNum--;
/*N*/       pData=(ImpSdrObjGroupLinkUserData*)GetUserData(nNum);
/*N*/       if (pData->GetInventor()!=SdrInventor || pData->GetId()!=SDRUSERDATA_OBJGROUPLINK) {
/*N*/           pData=NULL;
/*N*/       }
/*N*/   }
/*N*/   return pData;
/*N*/ }


//STRIP001 FASTBOOL SdrObjGroup::ReloadLinkedGroup(FASTBOOL bForceLoad)
//STRIP001 {
//STRIP001  ImpSdrObjGroupLinkUserData* pData=GetLinkUserData();
//STRIP001  FASTBOOL                    bRet=TRUE;
//STRIP001
//STRIP001  if( pData )
//STRIP001  {
//STRIP001      ::ucb::ContentBroker*   pBroker = ::ucb::ContentBroker::get();
//STRIP001      DateTime                aFileDT;
//STRIP001      BOOL                    bExists = FALSE, bLoad = FALSE;
//STRIP001
//STRIP001      if( pBroker )
//STRIP001      {
//STRIP001          bExists = TRUE;
//STRIP001
//STRIP001          try
//STRIP001          {
//STRIP001              INetURLObject aURL( pData->aFileName );
//STRIP001              DBG_ASSERT( aURL.GetProtocol() != INET_PROT_NOT_VALID, "invalid URL" );
//STRIP001
//STRIP001              ::ucb::Content aCnt( aURL.GetMainURL( INetURLObject::NO_DECODE ), ::com::sun::star::uno::Reference< ::com::sun::star::ucb::XCommandEnvironment >() );
//STRIP001              ::com::sun::star::uno::Any aAny( aCnt.getPropertyValue( ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "DateModified" ) ) ) );
//STRIP001              ::com::sun::star::util::DateTime aDateTime;
//STRIP001
//STRIP001              aAny >>= aDateTime;
//STRIP001              ::utl::typeConvert( aDateTime, aFileDT );
//STRIP001          }
//STRIP001          catch( ... )
//STRIP001          {
//STRIP001              bExists = FALSE;
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      if( bExists )
//STRIP001      {
//STRIP001          if( bForceLoad )
//STRIP001              bLoad = TRUE;
//STRIP001          else
//STRIP001              bLoad = ( aFileDT > pData->aFileDate0 );
//STRIP001
//STRIP001          pData->aFileDate0 = aFileDT;
//STRIP001      }
//STRIP001      else
//STRIP001          bLoad = ( pModel!=NULL && pModel->LoadModel(pData->aFileName)!=NULL );
//STRIP001
//STRIP001      if( bLoad )
//STRIP001      {
//STRIP001          Rectangle aMyRect(GetSnapRect());
//STRIP001          bRet=LoadGroup(pData->aFileName,pData->aObjName,&pData->nPageNum,&pData->bMasterPage,&pData->nObjNum);
//STRIP001          Rectangle aOrgRect(GetSnapRect());
//STRIP001          if (bRet && !aMyRect.IsEmpty() && !aOrgRect.IsEmpty())
//STRIP001          { // und nun noch zurechttransformieren
//STRIP001              if (aMyRect!=aOrgRect)
//STRIP001              {
//STRIP001                  // erstmal karo-einfach
//STRIP001                  NbcSetSnapRect(aMyRect);
//STRIP001              }
//STRIP001          }
//STRIP001          pData->aSnapRect0=aOrgRect; // letzte bekannte Groesse des Originalobjekts merken
//STRIP001      }
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }


//STRIP001 FASTBOOL SdrObjGroup::LoadGroup(const String& rFileName, const String& rObjName, USHORT* pnPgNum, FASTBOOL* pbMasterPg, ULONG* pnObjNum)
//STRIP001 {
//STRIP001  FASTBOOL bRet=FALSE;
//STRIP001
//STRIP001  if(pModel && rFileName.Len() && rObjName.Len())
//STRIP001  {
//STRIP001      const SdrModel* pTempModel=pModel->LoadModel(rFileName);
//STRIP001      if (pTempModel!=NULL) {
//STRIP001          SdrObjGroup* pRef=NULL;
//STRIP001          for (FASTBOOL bMPg=FALSE; bMPg!=TRUE && pRef==NULL;) {
//STRIP001              USHORT nPgAnz=bMPg ? pTempModel->GetMasterPageCount() : pTempModel->GetPageCount();
//STRIP001              for (USHORT nPgNum=0; nPgNum<nPgAnz && pRef==NULL; nPgNum++) {
//STRIP001                  const SdrPage* pPg=bMPg ? pTempModel->GetMasterPage(nPgNum) : pTempModel->GetPage(nPgNum);
//STRIP001                  ULONG nObjAnz=pPg->GetObjCount();
//STRIP001                  for (USHORT nObjNum=0; nObjNum<nObjAnz && pRef==NULL; nObjNum++) {
//STRIP001                      SdrObject* pObj=pPg->GetObj(nObjNum);
//STRIP001                      SdrObjGroup* pGrp=PTR_CAST(SdrObjGroup,pObj);
//STRIP001
//STRIP001                      if(pGrp && pGrp->GetName().Equals(rObjName))
//STRIP001                      {
//STRIP001                          pRef = pGrp;
//STRIP001
//STRIP001                          if(pnPgNum)
//STRIP001                              *pnPgNum = nPgNum;
//STRIP001
//STRIP001                          if(pbMasterPg)
//STRIP001                              *pbMasterPg = bMPg;
//STRIP001
//STRIP001                          if(pnObjNum)
//STRIP001                              *pnObjNum = nObjNum;
//STRIP001
//STRIP001                          bRet = TRUE;
//STRIP001                      }
//STRIP001                  }
//STRIP001              }
//STRIP001              bMPg=TRUE; // soz. von FALSE auf TRUE inkrementieren (fuer die obige for-Schleife)
//STRIP001          }
//STRIP001          if (pRef!=NULL) {
//STRIP001              Rectangle aBoundRect0; if (pUserCall!=NULL) aBoundRect0=GetBoundRect();
//STRIP001              SendRepaintBroadcast();
//STRIP001              // zunaechst diverse Daten des Obj kopieren
//STRIP001              nLayerId=pRef->GetLayer(); // hier noch ueberarbeiten !!!
//STRIP001              aAnchor =pRef->aAnchor;
//STRIP001              bVirtObj=pRef->bVirtObj;
//STRIP001              bSizProt=pRef->bSizProt;
//STRIP001              bMovProt=pRef->bMovProt;
//STRIP001              bNoPrint=pRef->bNoPrint;
//STRIP001              bEmptyPresObj=pRef->bEmptyPresObj;
//STRIP001              bNotVisibleAsMaster=pRef->bNotVisibleAsMaster;
//STRIP001              // und nun die Objekte rueberhohlen
//STRIP001              pSub->Clear();
//STRIP001              pSub->CopyObjects(*pRef->GetSubList());
//STRIP001              SetChanged();
//STRIP001              SendRepaintBroadcast();
//STRIP001              SendUserCall(SDRUSERCALL_RESIZE,aBoundRect0);
//STRIP001          }
//STRIP001          //delete pTempModel;
//STRIP001      }
//STRIP001      if (!pModel->IsLoading()) pModel->DisposeLoadedModels();
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }


/*N*/ void SdrObjGroup::ImpLinkAnmeldung()
/*N*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 #ifndef SVX_LIGHT
//STRIP001  ImpSdrObjGroupLinkUserData* pData=GetLinkUserData();
//STRIP001  SvxLinkManager* pLinkManager=pModel!=NULL ? pModel->GetLinkManager() : NULL;
//STRIP001  if ( pLinkManager         &&
//STRIP001       pData!=NULL          &&
//STRIP001       pData->pLink == NULL &&
//STRIP001       pModel->GetPersist() )
//STRIP001  {
//STRIP001      // Nicht 2x Anmelden
//STRIP001      INetURLObject aURLObj( ::URIHelper::SmartRelToAbs( pModel->GetPersist()->GetFileName(), FALSE,
//STRIP001                                                         INetURLObject::WAS_ENCODED,
//STRIP001                                                         INetURLObject::DECODE_UNAMBIGUOUS ) );
//STRIP001      INetURLObject aLinkURLObj( ::URIHelper::SmartRelToAbs( pData->aFileName, FALSE,
//STRIP001                                                             INetURLObject::WAS_ENCODED,
//STRIP001                                                             INetURLObject::DECODE_UNAMBIGUOUS ) );
//STRIP001
//STRIP001      if( !aURLObj.GetMainURL( INetURLObject::NO_DECODE ).Equals( aLinkURLObj.GetMainURL( INetURLObject::NO_DECODE ) ) )
//STRIP001      {
//STRIP001          // Keine gelinkten Objekte im eigenen Model
//STRIP001          pData->pLink = new ImpSdrObjGroupLink(this);
//STRIP001          pLinkManager->InsertFileLink(*pData->pLink,OBJECT_CLIENT_FILE,
//STRIP001                                       pData->aFileName,NULL,&pData->aObjName);
//STRIP001          pData->pLink->Connect();
//STRIP001      }
//STRIP001  }
//STRIP001 #endif // SVX_LIGHT
/*N*/ }


/*N*/ void SdrObjGroup::ImpLinkAbmeldung()
/*N*/ {
/*N*/ #ifndef SVX_LIGHT
/*N*/   ImpSdrObjGroupLinkUserData* pData=GetLinkUserData();
/*N*/   SvxLinkManager* pLinkManager=pModel!=NULL ? pModel->GetLinkManager() : NULL;
/*N*/   if (pLinkManager!=NULL && pData!=NULL && pData->pLink!=NULL) { // Nicht 2x Abmelden
/*N*/       // Bei Remove wird *pLink implizit deleted
/*?*/       DBG_ASSERT(0, "STRIP"); //STRIP001 pLinkManager->Remove( pData->pLink );
//STRIP001 /*?*/        pData->pLink=NULL;
/*N*/   }
/*N*/ #endif // SVX_LIGHT
/*N*/ }


//STRIP001 void SdrObjGroup::TakeObjInfo(SdrObjTransformInfoRec& rInfo) const
//STRIP001 {
//STRIP001 //    rInfo.bCanConvToPath          =FALSE;
//STRIP001 //    rInfo.bCanConvToPoly          =FALSE;
//STRIP001 //    rInfo.bCanConvToPathLineToArea=FALSE;
//STRIP001 //    rInfo.bCanConvToPolyLineToArea=FALSE;
//STRIP001  rInfo.bNoContortion=FALSE;
//STRIP001  SdrObjList* pOL=pSub;
//STRIP001  ULONG nObjAnz=pOL->GetObjCount();
//STRIP001  for (ULONG i=0; i<nObjAnz; i++) {
//STRIP001      SdrObject* pObj=pOL->GetObj(i);
//STRIP001      SdrObjTransformInfoRec aInfo;
//STRIP001      pObj->TakeObjInfo(aInfo);
//STRIP001      if (!aInfo.bMoveAllowed            ) rInfo.bMoveAllowed            =FALSE;
//STRIP001      if (!aInfo.bResizeFreeAllowed      ) rInfo.bResizeFreeAllowed      =FALSE;
//STRIP001      if (!aInfo.bResizePropAllowed      ) rInfo.bResizePropAllowed      =FALSE;
//STRIP001      if (!aInfo.bRotateFreeAllowed      ) rInfo.bRotateFreeAllowed      =FALSE;
//STRIP001      if (!aInfo.bRotate90Allowed        ) rInfo.bRotate90Allowed        =FALSE;
//STRIP001      if (!aInfo.bMirrorFreeAllowed      ) rInfo.bMirrorFreeAllowed      =FALSE;
//STRIP001      if (!aInfo.bMirror45Allowed        ) rInfo.bMirror45Allowed        =FALSE;
//STRIP001      if (!aInfo.bMirror90Allowed        ) rInfo.bMirror90Allowed        =FALSE;
//STRIP001      if (!aInfo.bShearAllowed           ) rInfo.bShearAllowed           =FALSE;
//STRIP001      if (!aInfo.bEdgeRadiusAllowed      ) rInfo.bEdgeRadiusAllowed      =FALSE;
//STRIP001      if (!aInfo.bNoOrthoDesired         ) rInfo.bNoOrthoDesired         =FALSE;
//STRIP001      if (aInfo.bNoContortion            ) rInfo.bNoContortion           =TRUE;
//STRIP001      if (!aInfo.bCanConvToPath          ) rInfo.bCanConvToPath          =FALSE;
//STRIP001
//STRIP001      if(!aInfo.bCanConvToContour)
//STRIP001          rInfo.bCanConvToContour = FALSE;
//STRIP001
//STRIP001      if (!aInfo.bCanConvToPoly          ) rInfo.bCanConvToPoly          =FALSE;
//STRIP001      if (!aInfo.bCanConvToPathLineToArea) rInfo.bCanConvToPathLineToArea=FALSE;
//STRIP001      if (!aInfo.bCanConvToPolyLineToArea) rInfo.bCanConvToPolyLineToArea=FALSE;
//STRIP001  }
//STRIP001  if (nObjAnz==0) {
//STRIP001      rInfo.bRotateFreeAllowed=FALSE;
//STRIP001      rInfo.bRotate90Allowed  =FALSE;
//STRIP001      rInfo.bMirrorFreeAllowed=FALSE;
//STRIP001      rInfo.bMirror45Allowed  =FALSE;
//STRIP001      rInfo.bMirror90Allowed  =FALSE;
//STRIP001      rInfo.bTransparenceAllowed = FALSE;
//STRIP001      rInfo.bGradientAllowed = FALSE;
//STRIP001      rInfo.bShearAllowed     =FALSE;
//STRIP001      rInfo.bEdgeRadiusAllowed=FALSE;
//STRIP001      rInfo.bNoContortion     =TRUE;
//STRIP001  }
//STRIP001  if(nObjAnz != 1)
//STRIP001  {
//STRIP001      // only allowed if single object selected
//STRIP001      rInfo.bTransparenceAllowed = FALSE;
//STRIP001      rInfo.bGradientAllowed = FALSE;
//STRIP001  }
//STRIP001  if (pPlusData!=NULL && nObjAnz!=0) {
//STRIP001      ImpSdrObjGroupLinkUserData* pData=GetLinkUserData();
//STRIP001      if (pData!=NULL) {
//STRIP001          if (pData->bOrigPos   ) rInfo.bMoveAllowed =FALSE;
//STRIP001          if (pData->bOrigSize  ) { rInfo.bResizeFreeAllowed=FALSE; rInfo.bResizePropAllowed=FALSE; }
//STRIP001          if (pData->bOrigRotate) rInfo.bMoveAllowed =FALSE;
//STRIP001          if (pData->bOrigShear ) rInfo.bMoveAllowed =FALSE;
//STRIP001          // erstmal alles abschalten
//STRIP001          //rInfo.bResizeFreeAllowed=FALSE;
//STRIP001          //rInfo.bResizePropAllowed=FALSE;
//STRIP001          rInfo.bRotateFreeAllowed=FALSE;
//STRIP001          rInfo.bRotate90Allowed  =FALSE;
//STRIP001          rInfo.bMirrorFreeAllowed=FALSE;
//STRIP001          rInfo.bMirror45Allowed=FALSE;
//STRIP001          rInfo.bMirror90Allowed=FALSE;
//STRIP001          rInfo.bShearAllowed=FALSE;
//STRIP001          rInfo.bShearAllowed=FALSE;
//STRIP001          rInfo.bNoContortion=TRUE;
//STRIP001          // default: Proportionen beibehalten
//STRIP001          rInfo.bNoOrthoDesired=FALSE;
//STRIP001      }
//STRIP001  }
//STRIP001 }


/*N*/ UINT16 SdrObjGroup::GetObjIdentifier() const
/*N*/ {
/*N*/   return UINT16(OBJ_GRUP);
/*N*/ }


/*N*/ SdrLayerID SdrObjGroup::GetLayer() const
/*N*/ {
/*N*/   FASTBOOL b1st=TRUE;
/*N*/   SdrLayerID nLay=SdrLayerID(nLayerId);
/*N*/   SdrObjList* pOL=pSub;
/*N*/   ULONG nObjAnz=pOL->GetObjCount();
/*N*/   for (ULONG i=0; i<nObjAnz; i++) {
/*N*/       SdrLayerID nLay1=pOL->GetObj(i)->GetLayer();
/*N*/       if (b1st) { nLay=nLay1; b1st=FALSE; }
/*N*/       else if (nLay1!=nLay) return 0;
/*N*/   }
/*N*/   return nLay;
/*N*/ }


/*N*/ void SdrObjGroup::NbcSetLayer(SdrLayerID nLayer)
/*N*/ {
/*N*/   SdrObject::NbcSetLayer(nLayer);
/*N*/   SdrObjList* pOL=pSub;
/*N*/   ULONG nObjAnz=pOL->GetObjCount();
/*N*/   for (ULONG i=0; i<nObjAnz; i++) {
/*N*/       pOL->GetObj(i)->NbcSetLayer(nLayer);
/*N*/   }
/*N*/ }


/*N*/ void SdrObjGroup::SetObjList(SdrObjList* pNewObjList)
/*N*/ {
/*N*/   SdrObject::SetObjList(pNewObjList);
/*N*/   pSub->SetUpList(pNewObjList);
/*N*/ }


/*N*/ void SdrObjGroup::SetPage(SdrPage* pNewPage)
/*N*/ {
/*N*/   FASTBOOL bLinked=IsLinkedGroup();
/*N*/   FASTBOOL bRemove=pNewPage==NULL && pPage!=NULL;
/*N*/   FASTBOOL bInsert=pNewPage!=NULL && pPage==NULL;
/*N*/
/*N*/   if (bLinked && bRemove) {
/*?*/       ImpLinkAbmeldung();
/*N*/   }
/*N*/
/*N*/   SdrObject::SetPage(pNewPage);
/*N*/   pSub->SetPage(pNewPage);
/*N*/
/*N*/   if (bLinked && bInsert) {
/*?*/       ImpLinkAnmeldung();
/*N*/   }
/*N*/ }


/*N*/ void SdrObjGroup::SetModel(SdrModel* pNewModel)
/*N*/ {
/*N*/   FASTBOOL bLinked=IsLinkedGroup();
/*N*/   FASTBOOL bChg=pNewModel!=pModel;
/*N*/   if (bLinked && bChg) {
/*N*/       ImpLinkAbmeldung();
/*N*/   }
/*N*/
/*N*/   SdrObject::SetModel(pNewModel);
/*N*/   pSub->SetModel(pNewModel);
/*N*/
/*N*/   if (bLinked && bChg) {
/*?*/       ImpLinkAnmeldung();
/*N*/   }
/*N*/ }


//STRIP001 FASTBOOL SdrObjGroup::HasRefPoint() const
//STRIP001 {
//STRIP001  return bRefPoint;
//STRIP001 }


//STRIP001 Point SdrObjGroup::GetRefPoint() const
//STRIP001 {
//STRIP001  return aRefPoint;
//STRIP001 }


//STRIP001 void SdrObjGroup::SetRefPoint(const Point& rPnt)
//STRIP001 {
//STRIP001  bRefPoint=TRUE;
//STRIP001  aRefPoint=rPnt;
//STRIP001 }


/*N*/ SdrObjList* SdrObjGroup::GetSubList() const
/*N*/ {
/*N*/   return pSub;
/*N*/ }

//STRIP001 FASTBOOL SdrObjGroup::HasSetName() const
//STRIP001 {
//STRIP001  return TRUE;
//STRIP001 }


/*N*/ void SdrObjGroup::SetName(const XubString& rStr)
/*N*/ {
/*N*/   aName=rStr; SetChanged();
/*N*/ }


/*N*/ XubString SdrObjGroup::GetName() const
/*N*/ {
/*N*/   return aName;
/*N*/ }


/*N*/ const Rectangle& SdrObjGroup::GetBoundRect() const
/*N*/ {
/*N*/   if (pSub->GetObjCount()!=0) {
/*N*/       // hier auch das aOutRect=AllObjSnapRect setzen, da GetSnapRect zu selten gerufen wird.
/*N*/       ((SdrObjGroup*)this)->aOutRect=pSub->GetAllObjSnapRect();
/*N*/       return pSub->GetAllObjBoundRect();
/*N*/   } else {
/*N*/       return aOutRect;
/*N*/   }
/*N*/ }


/*N*/ const Rectangle& SdrObjGroup::GetSnapRect() const
/*N*/ {
/*N*/   if (pSub->GetObjCount()!=0) {
/*N*/       ((SdrObjGroup*)this)->aOutRect=pSub->GetAllObjSnapRect();
/*N*/   }
/*N*/   return aOutRect;
/*N*/ }


/*N*/ FASTBOOL SdrObjGroup::Paint(ExtOutputDevice& rXOut, const SdrPaintInfoRec& rInfoRec) const
/*N*/ {
/*N*/   FASTBOOL bOk=TRUE;
/*N*/   if (pSub->GetObjCount()!=0) {
/*N*/       bOk=pSub->Paint(rXOut,rInfoRec);
/*N*/   } else { // ansonsten ist es eine leere Gruppe
/*?*/       if (!rInfoRec.bPrinter && rInfoRec.aPaintLayer.IsSet(nLayerId)) {
/*?*/           OutputDevice* pOutDev=rXOut.GetOutDev();
/*?*/           pOutDev->SetFillInBrush(Brush(BRUSH_NULL));
/*?*/           pOutDev->SetPen(Color(COL_LIGHTGRAY));
/*?*/           pOutDev->DrawRect(aOutRect);
/*N*/       }
/*N*/   }
/*N*/   if (bOk && (rInfoRec.nPaintMode & SDRPAINTMODE_GLUEPOINTS) !=0) {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/        bOk=PaintGluePoints(rXOut,rInfoRec);
/*N*/   }
/*N*/   return bOk;
/*N*/ }


//STRIP001 SdrObject* SdrObjGroup::CheckHit(const Point& rPnt, USHORT nTol, const SetOfByte* pVisiLayer) const
//STRIP001 {
//STRIP001  if (pSub->GetObjCount()!=0) {
//STRIP001      return pSub->CheckHit(rPnt,nTol,pVisiLayer);
//STRIP001  } else { // ansonsten ist es eine leere Gruppe
//STRIP001      if (pVisiLayer==NULL || pVisiLayer->IsSet(nLayerId)) {
//STRIP001          Rectangle aAussen(aOutRect);
//STRIP001          aAussen.Top()   -=nTol;
//STRIP001          aAussen.Left()  -=nTol;
//STRIP001          aAussen.Bottom()+=nTol;
//STRIP001          aAussen.Right() +=nTol;
//STRIP001          nTol++;
//STRIP001          Rectangle aInnen(aOutRect);
//STRIP001          aInnen.Top()   +=nTol;
//STRIP001          aInnen.Left()  +=nTol;
//STRIP001          aInnen.Bottom()-=nTol;
//STRIP001          aInnen.Right() -=nTol;
//STRIP001          if (aAussen.IsInside(rPnt) && !aInnen.IsInside(rPnt)) {
//STRIP001              return (SdrObject*)this;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  return NULL;
//STRIP001 }

/*SdrObject* SdrObjGroup::Clone() const
{
    SdrObjGroup* pObj=new SdrObjGroup();
    if (pObj!=NULL) {
        *pObj=*this;
    }
    return pObj;
}*/


/*N*/ void SdrObjGroup::operator=(const SdrObject& rObj)
/*N*/ {
/*N*/   if (rObj.IsGroupObject()) {
/*N*/       SdrObject::operator=(rObj);
/*N*/       pSub->CopyObjects(*rObj.GetSubList());
/*N*/       nDrehWink  =((SdrObjGroup&)rObj).nDrehWink;
/*N*/       nShearWink =((SdrObjGroup&)rObj).nShearWink;
/*N*/       aName      =((SdrObjGroup&)rObj).aName;
/*N*/       aRefPoint  =((SdrObjGroup&)rObj).aRefPoint;
/*N*/       bRefPoint  =((SdrObjGroup&)rObj).bRefPoint;
/*N*/   }
/*N*/ }


//STRIP001 void SdrObjGroup::TakeObjNameSingul(XubString& rName) const
//STRIP001 {
//STRIP001  if(IsLinkedGroup())
//STRIP001  {
//STRIP001      rName = ImpGetResStr(STR_ObjNameSingulGRUPLNK);
//STRIP001  }
//STRIP001  else if(!pSub->GetObjCount())
//STRIP001  {
//STRIP001      rName = ImpGetResStr(STR_ObjNameSingulGRUPEMPTY);
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      rName = ImpGetResStr(STR_ObjNameSingulGRUP);
//STRIP001  }
//STRIP001
//STRIP001  if(aName.Len())
//STRIP001  {
//STRIP001      rName += sal_Unicode(' ');
//STRIP001      rName += sal_Unicode('\'');
//STRIP001      rName += aName;
//STRIP001      rName += sal_Unicode('\'');
//STRIP001  }
//STRIP001 }


//STRIP001 void SdrObjGroup::TakeObjNamePlural(XubString& rName) const
//STRIP001 {
//STRIP001  if (IsLinkedGroup()) {
//STRIP001      rName=ImpGetResStr(STR_ObjNamePluralGRUPLNK);
//STRIP001  } else if (pSub->GetObjCount()==0) {
//STRIP001      rName=ImpGetResStr(STR_ObjNamePluralGRUPEMPTY);
//STRIP001  } else {
//STRIP001      rName=ImpGetResStr(STR_ObjNamePluralGRUP);
//STRIP001  }
//STRIP001 }


/*N*/ void SdrObjGroup::RecalcSnapRect()
/*N*/ {
/*N*/   // nicht erforderlich, da die Rects von der SubList verwendet werden.
/*N*/ }


/*N*/ void MergePoly(XPolyPolygon& rDst, const XPolyPolygon& rSrc)
/*N*/ {
/*N*/   USHORT nAnz=rSrc.Count();
/*N*/   USHORT i;
/*N*/   for (i=0; i<nAnz; i++) {
/*N*/       rDst.Insert(rSrc.GetObject(i));
/*N*/   }
/*N*/ }


/*N*/ void SdrObjGroup::TakeXorPoly(XPolyPolygon& rPoly, FASTBOOL bDetail) const
/*N*/ {
/*N*/   rPoly.Clear();
/*N*/   ULONG nAnz=pSub->GetObjCount();
/*N*/   ULONG i=0;
/*N*/   while (i<nAnz) {
/*N*/       SdrObject* pObj=pSub->GetObj(i);
/*N*/       XPolyPolygon aPP;
/*N*/       pObj->TakeXorPoly(aPP,bDetail);
/*N*/       MergePoly(rPoly,aPP);
/*N*/       i++;
/*N*/   }
/*N*/   if (rPoly.Count()==0) {
/*?*/       rPoly.Insert(XPolygon(aOutRect));
/*N*/   }
/*N*/ }

//STRIP001 void SdrObjGroup::TakeContour(XPolyPolygon& rXPoly, SdrContourType eType) const
//STRIP001 {
//STRIP001 }


//STRIP001 FASTBOOL SdrObjGroup::BegDrag(SdrDragStat& rDrag) const
//STRIP001 {
//STRIP001  return FALSE;
//STRIP001 }


//STRIP001 FASTBOOL SdrObjGroup::BegCreate(SdrDragStat& rStat)
//STRIP001 {
//STRIP001  return FALSE;
//STRIP001 }


/*N*/ long SdrObjGroup::GetRotateAngle() const
/*N*/ {
/*N*/   return nDrehWink;
/*N*/ }


/*N*/ long SdrObjGroup::GetShearAngle(FASTBOOL bVertical) const
/*N*/ {
/*N*/   return nShearWink;
/*N*/ }


/*N*/ void SdrObjGroup::NbcSetSnapRect(const Rectangle& rRect)
/*N*/ {
/*N*/   Rectangle aOld(GetSnapRect());
/*N*/   long nMulX=rRect.Right()-rRect.Left();
/*N*/   long nDivX=aOld.Right()-aOld.Left();
/*N*/   long nMulY=rRect.Bottom()-rRect.Top();
/*N*/   long nDivY=aOld.Bottom()-aOld.Top();
/*N*/   if (nDivX==0) { nMulX=1; nDivX=1; }
/*N*/   if (nDivY==0) { nMulY=1; nDivY=1; }
/*N*/   if (nMulX!=nDivX || nMulY!=nDivY) {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/        Fraction aX(nMulX,nDivX);
//STRIP001 /*?*/        Fraction aY(nMulY,nDivY);
//STRIP001 /*?*/        NbcResize(aOld.TopLeft(),aX,aY);
/*N*/   }
/*N*/   if (rRect.Left()!=aOld.Left() || rRect.Top()!=aOld.Top()) {
/*N*/       NbcMove(Size(rRect.Left()-aOld.Left(),rRect.Top()-aOld.Top()));
/*N*/   }
/*N*/ }


/*N*/ void SdrObjGroup::NbcSetLogicRect(const Rectangle& rRect)
/*N*/ {
/*N*/   NbcSetSnapRect(rRect);
/*N*/ }


/*N*/ void SdrObjGroup::NbcMove(const Size& rSiz)
/*N*/ {
/*N*/   MovePoint(aRefPoint,rSiz);
/*N*/   if (pSub->GetObjCount()!=0) {
/*N*/       SdrObjList* pOL=pSub;
/*N*/       ULONG nObjAnz=pOL->GetObjCount();
/*N*/       for (ULONG i=0; i<nObjAnz; i++) {
/*N*/           SdrObject* pObj=pOL->GetObj(i);
/*N*/           pObj->NbcMove(rSiz);
/*N*/       }
/*N*/   } else {
/*?*/       MoveRect(aOutRect,rSiz);
/*?*/       SetRectsDirty();
/*N*/   }
/*N*/ }


/*N*/ void SdrObjGroup::NbcResize(const Point& rRef, const Fraction& xFact, const Fraction& yFact)
/*N*/ {
/*N*/   FASTBOOL bXMirr=(xFact.GetNumerator()<0) != (xFact.GetDenominator()<0);
/*N*/   FASTBOOL bYMirr=(yFact.GetNumerator()<0) != (yFact.GetDenominator()<0);
/*N*/   if (bXMirr || bYMirr) {
/*N*/       Point aRef1(GetSnapRect().Center());
/*N*/       if (bXMirr) {
/*N*/           Point aRef2(aRef1);
/*N*/           aRef2.Y()++;
/*N*/           NbcMirrorGluePoints(aRef1,aRef2);
/*N*/       }
/*N*/       if (bYMirr) {
/*N*/           Point aRef2(aRef1);
/*N*/           aRef2.X()++;
/*N*/           NbcMirrorGluePoints(aRef1,aRef2);
/*N*/       }
/*N*/   }
/*N*/   ResizePoint(aRefPoint,rRef,xFact,yFact);
/*N*/   if (pSub->GetObjCount()!=0) {
/*N*/       SdrObjList* pOL=pSub;
/*N*/       ULONG nObjAnz=pOL->GetObjCount();
/*N*/       for (ULONG i=0; i<nObjAnz; i++) {
/*N*/           SdrObject* pObj=pOL->GetObj(i);
/*N*/           pObj->NbcResize(rRef,xFact,yFact);
/*N*/       }
/*N*/   } else {
/*N*/       ResizeRect(aOutRect,rRef,xFact,yFact);
/*N*/       SetRectsDirty();
/*N*/   }
/*N*/ }


//STRIP001 void SdrObjGroup::NbcRotate(const Point& rRef, long nWink, double sn, double cs)
//STRIP001 {
//STRIP001  SetGlueReallyAbsolute(TRUE);
//STRIP001  nDrehWink=NormAngle360(nDrehWink+nWink);
//STRIP001  RotatePoint(aRefPoint,rRef,sn,cs);
//STRIP001  SdrObjList* pOL=pSub;
//STRIP001  ULONG nObjAnz=pOL->GetObjCount();
//STRIP001  for (ULONG i=0; i<nObjAnz; i++) {
//STRIP001      SdrObject* pObj=pOL->GetObj(i);
//STRIP001      pObj->NbcRotate(rRef,nWink,sn,cs);
//STRIP001  }
//STRIP001  NbcRotateGluePoints(rRef,nWink,sn,cs);
//STRIP001  SetGlueReallyAbsolute(FALSE);
//STRIP001 }


//STRIP001 void SdrObjGroup::NbcMirror(const Point& rRef1, const Point& rRef2)
//STRIP001 {
//STRIP001  SetGlueReallyAbsolute(TRUE);
//STRIP001  MirrorPoint(aRefPoint,rRef1,rRef2); // fehlende Implementation in SvdEtc !!!
//STRIP001  SdrObjList* pOL=pSub;
//STRIP001  ULONG nObjAnz=pOL->GetObjCount();
//STRIP001  for (ULONG i=0; i<nObjAnz; i++) {
//STRIP001      SdrObject* pObj=pOL->GetObj(i);
//STRIP001      pObj->NbcMirror(rRef1,rRef2);
//STRIP001  }
//STRIP001  NbcMirrorGluePoints(rRef1,rRef2);
//STRIP001  SetGlueReallyAbsolute(FALSE);
//STRIP001 }


//STRIP001 void SdrObjGroup::NbcShear(const Point& rRef, long nWink, double tn, FASTBOOL bVShear)
//STRIP001 {
//STRIP001  SetGlueReallyAbsolute(TRUE);
//STRIP001  nShearWink+=nWink;
//STRIP001  ShearPoint(aRefPoint,rRef,tn);
//STRIP001  SdrObjList* pOL=pSub;
//STRIP001  ULONG nObjAnz=pOL->GetObjCount();
//STRIP001  for (ULONG i=0; i<nObjAnz; i++) {
//STRIP001      SdrObject* pObj=pOL->GetObj(i);
//STRIP001      pObj->NbcShear(rRef,nWink,tn,bVShear);
//STRIP001  }
//STRIP001  NbcShearGluePoints(rRef,nWink,tn,bVShear);
//STRIP001  SetGlueReallyAbsolute(FALSE);
//STRIP001 }


/*N*/ void SdrObjGroup::NbcSetAnchorPos(const Point& rPnt)
/*N*/ {
/*N*/   aAnchor=rPnt;
/*N*/   Size aSiz(rPnt.X()-aAnchor.X(),rPnt.Y()-aAnchor.Y());
/*N*/   MovePoint(aRefPoint,aSiz);
/*N*/   SdrObjList* pOL=pSub;
/*N*/   ULONG nObjAnz=pOL->GetObjCount();
/*N*/   for (ULONG i=0; i<nObjAnz; i++) {
/*N*/       SdrObject* pObj=pOL->GetObj(i);
/*N*/       pObj->NbcSetAnchorPos(rPnt);
/*N*/   }
/*N*/ }


/*N*/ void SdrObjGroup::SetSnapRect(const Rectangle& rRect)
/*N*/ {
/*N*/   Rectangle aBoundRect0; if (pUserCall!=NULL) aBoundRect0=GetBoundRect();
/*N*/   Rectangle aOld(GetSnapRect());
/*N*/   long nMulX=rRect.Right()-rRect.Left();
/*N*/   long nDivX=aOld.Right()-aOld.Left();
/*N*/   long nMulY=rRect.Bottom()-rRect.Top();
/*N*/   long nDivY=aOld.Bottom()-aOld.Top();
/*N*/   if (nDivX==0) { nMulX=1; nDivX=1; }
/*N*/   if (nDivY==0) { nMulY=1; nDivY=1; }
/*N*/   if (nMulX!=nDivX || nMulY!=nDivY) {
/*N*/       Fraction aX(nMulX,nDivX);
/*N*/       Fraction aY(nMulY,nDivY);
/*N*/       Resize(aOld.TopLeft(),aX,aY);
/*N*/   }
/*N*/   if (rRect.Left()!=aOld.Left() || rRect.Top()!=aOld.Top()) {
/*?*/       Move(Size(rRect.Left()-aOld.Left(),rRect.Top()-aOld.Top()));
/*N*/   }
/*N*/   SendRepaintBroadcast(TRUE);
/*N*/   SetChanged();
/*N*/   SendUserCall(SDRUSERCALL_RESIZE,aBoundRect0);
/*N*/ }


//STRIP001 void SdrObjGroup::SetLogicRect(const Rectangle& rRect)
//STRIP001 {
//STRIP001  SetSnapRect(rRect);
//STRIP001 }


/*N*/ void SdrObjGroup::Move(const Size& rSiz)
/*N*/ {
/*N*/   if (rSiz.Width()!=0 || rSiz.Height()!=0) {
/*N*/       Rectangle aBoundRect0; if (pUserCall!=NULL) aBoundRect0=GetBoundRect();
/*N*/       MovePoint(aRefPoint,rSiz);
/*N*/       if (pSub->GetObjCount()!=0) {
/*N*/           // #32383# Erst die Verbinder verschieben, dann den Rest
/*N*/           SdrObjList* pOL=pSub;
/*N*/           ULONG nObjAnz=pOL->GetObjCount();
/*N*/           ULONG i;
/*N*/           for (i=0; i<nObjAnz; i++) {
/*N*/               SdrObject* pObj=pOL->GetObj(i);
/*N*/               if (pObj->IsEdgeObj()) pObj->Move(rSiz);
/*N*/           }
/*N*/           for (i=0; i<nObjAnz; i++) {
/*N*/               SdrObject* pObj=pOL->GetObj(i);
/*N*/               if (!pObj->IsEdgeObj()) pObj->Move(rSiz);
/*N*/           }
/*N*/           SendRepaintBroadcast(TRUE);
/*N*/       } else {
/*N*/           SendRepaintBroadcast();
/*N*/           MoveRect(aOutRect,rSiz);
/*N*/           SetRectsDirty();
/*N*/           SendRepaintBroadcast();
/*N*/       }
/*N*/       SetChanged();
/*N*/       SendUserCall(SDRUSERCALL_MOVEONLY,aBoundRect0);
/*N*/   }
/*N*/ }


/*N*/ void SdrObjGroup::Resize(const Point& rRef, const Fraction& xFact, const Fraction& yFact)
/*N*/ {
/*N*/   if (xFact.GetNumerator()!=xFact.GetDenominator() || yFact.GetNumerator()!=yFact.GetDenominator()) {
/*N*/       FASTBOOL bXMirr=(xFact.GetNumerator()<0) != (xFact.GetDenominator()<0);
/*N*/       FASTBOOL bYMirr=(yFact.GetNumerator()<0) != (yFact.GetDenominator()<0);
/*N*/       if (bXMirr || bYMirr) {
/*N*/           Point aRef1(GetSnapRect().Center());
/*N*/           if (bXMirr) {
/*N*/               Point aRef2(aRef1);
/*N*/               aRef2.Y()++;
/*N*/               NbcMirrorGluePoints(aRef1,aRef2);
/*N*/           }
/*N*/           if (bYMirr) {
/*N*/               Point aRef2(aRef1);
/*N*/               aRef2.X()++;
/*N*/               NbcMirrorGluePoints(aRef1,aRef2);
/*N*/           }
/*N*/       }
/*N*/       Rectangle aBoundRect0; if (pUserCall!=NULL) aBoundRect0=GetBoundRect();
/*N*/       ResizePoint(aRefPoint,rRef,xFact,yFact);
/*N*/       if (pSub->GetObjCount()!=0) {
/*?*/           // #32383# Erst die Verbinder verschieben, dann den Rest
/*?*/           SdrObjList* pOL=pSub;
/*?*/           ULONG nObjAnz=pOL->GetObjCount();
/*?*/           ULONG i;
/*?*/           for (i=0; i<nObjAnz; i++) {
/*?*/               SdrObject* pObj=pOL->GetObj(i);
/*?*/               if (pObj->IsEdgeObj()) pObj->Resize(rRef,xFact,yFact);
/*?*/           }
/*?*/           for (i=0; i<nObjAnz; i++) {
/*?*/               SdrObject* pObj=pOL->GetObj(i);
/*?*/               if (!pObj->IsEdgeObj()) pObj->Resize(rRef,xFact,yFact);
/*?*/           }
/*?*/           SendRepaintBroadcast(TRUE);
/*N*/       } else {
/*N*/           SendRepaintBroadcast();
/*N*/           ResizeRect(aOutRect,rRef,xFact,yFact);
/*N*/           SetRectsDirty();
/*N*/           SendRepaintBroadcast();
/*N*/       }
/*N*/       SetChanged();
/*N*/       SendUserCall(SDRUSERCALL_RESIZE,aBoundRect0);
/*N*/   }
/*N*/ }


//STRIP001 void SdrObjGroup::Rotate(const Point& rRef, long nWink, double sn, double cs)
//STRIP001 {
//STRIP001  if (nWink!=0) {
//STRIP001      SetGlueReallyAbsolute(TRUE);
//STRIP001      Rectangle aBoundRect0; if (pUserCall!=NULL) aBoundRect0=GetBoundRect();
//STRIP001      nDrehWink=NormAngle360(nDrehWink+nWink);
//STRIP001      RotatePoint(aRefPoint,rRef,sn,cs);
//STRIP001      // #32383# Erst die Verbinder verschieben, dann den Rest
//STRIP001      SdrObjList* pOL=pSub;
//STRIP001      ULONG nObjAnz=pOL->GetObjCount();
//STRIP001      ULONG i;
//STRIP001      for (i=0; i<nObjAnz; i++) {
//STRIP001          SdrObject* pObj=pOL->GetObj(i);
//STRIP001          if (pObj->IsEdgeObj()) pObj->Rotate(rRef,nWink,sn,cs);
//STRIP001      }
//STRIP001      for (i=0; i<nObjAnz; i++) {
//STRIP001          SdrObject* pObj=pOL->GetObj(i);
//STRIP001          if (!pObj->IsEdgeObj()) pObj->Rotate(rRef,nWink,sn,cs);
//STRIP001      }
//STRIP001      NbcRotateGluePoints(rRef,nWink,sn,cs);
//STRIP001      SetGlueReallyAbsolute(FALSE);
//STRIP001      SendRepaintBroadcast(TRUE);
//STRIP001      SetChanged();
//STRIP001      SendUserCall(SDRUSERCALL_RESIZE,aBoundRect0);
//STRIP001  }
//STRIP001 }


//STRIP001 void SdrObjGroup::Mirror(const Point& rRef1, const Point& rRef2)
//STRIP001 {
//STRIP001  SetGlueReallyAbsolute(TRUE);
//STRIP001  Rectangle aBoundRect0; if (pUserCall!=NULL) aBoundRect0=GetBoundRect();
//STRIP001  MirrorPoint(aRefPoint,rRef1,rRef2); // fehlende Implementation in SvdEtc !!!
//STRIP001  // #32383# Erst die Verbinder verschieben, dann den Rest
//STRIP001  SdrObjList* pOL=pSub;
//STRIP001  ULONG nObjAnz=pOL->GetObjCount();
//STRIP001  ULONG i;
//STRIP001  for (i=0; i<nObjAnz; i++) {
//STRIP001      SdrObject* pObj=pOL->GetObj(i);
//STRIP001      if (pObj->IsEdgeObj()) pObj->Mirror(rRef1,rRef2);
//STRIP001  }
//STRIP001  for (i=0; i<nObjAnz; i++) {
//STRIP001      SdrObject* pObj=pOL->GetObj(i);
//STRIP001      if (!pObj->IsEdgeObj()) pObj->Mirror(rRef1,rRef2);
//STRIP001  }
//STRIP001  NbcMirrorGluePoints(rRef1,rRef2);
//STRIP001  SetGlueReallyAbsolute(FALSE);
//STRIP001  SendRepaintBroadcast(TRUE);
//STRIP001  SetChanged();
//STRIP001  SendUserCall(SDRUSERCALL_RESIZE,aBoundRect0);
//STRIP001 }


//STRIP001 void SdrObjGroup::Shear(const Point& rRef, long nWink, double tn, FASTBOOL bVShear)
//STRIP001 {
//STRIP001  if (nWink!=0) {
//STRIP001      SetGlueReallyAbsolute(TRUE);
//STRIP001      Rectangle aBoundRect0; if (pUserCall!=NULL) aBoundRect0=GetBoundRect();
//STRIP001      nShearWink+=nWink;
//STRIP001      ShearPoint(aRefPoint,rRef,tn);
//STRIP001      // #32383# Erst die Verbinder verschieben, dann den Rest
//STRIP001      SdrObjList* pOL=pSub;
//STRIP001      ULONG nObjAnz=pOL->GetObjCount();
//STRIP001      ULONG i;
//STRIP001      for (i=0; i<nObjAnz; i++) {
//STRIP001          SdrObject* pObj=pOL->GetObj(i);
//STRIP001          if (pObj->IsEdgeObj()) pObj->Shear(rRef,nWink,tn,bVShear);
//STRIP001      }
//STRIP001      for (i=0; i<nObjAnz; i++) {
//STRIP001          SdrObject* pObj=pOL->GetObj(i);
//STRIP001          if (!pObj->IsEdgeObj()) pObj->Shear(rRef,nWink,tn,bVShear);
//STRIP001      }
//STRIP001      NbcShearGluePoints(rRef,nWink,tn,bVShear);
//STRIP001      SetGlueReallyAbsolute(FALSE);
//STRIP001      SendRepaintBroadcast(TRUE);
//STRIP001      SetChanged();
//STRIP001      SendUserCall(SDRUSERCALL_RESIZE,aBoundRect0);
//STRIP001  }
//STRIP001 }


/*N*/ void SdrObjGroup::SetAnchorPos(const Point& rPnt)
/*N*/ {
/*N*/   Rectangle aBoundRect0; if (pUserCall!=NULL) aBoundRect0=GetBoundRect();
/*N*/   FASTBOOL bChg=aAnchor!=rPnt;
/*N*/   aAnchor=rPnt;
/*N*/   Size aSiz(rPnt.X()-aAnchor.X(),rPnt.Y()-aAnchor.Y());
/*N*/   MovePoint(aRefPoint,aSiz);
/*N*/   // #32383# Erst die Verbinder verschieben, dann den Rest
/*N*/   SdrObjList* pOL=pSub;
/*N*/   ULONG nObjAnz=pOL->GetObjCount();
/*N*/   ULONG i;
/*N*/   for (i=0; i<nObjAnz; i++) {
/*N*/       SdrObject* pObj=pOL->GetObj(i);
/*N*/       if (pObj->IsEdgeObj()) pObj->SetAnchorPos(rPnt);
/*N*/   }
/*N*/   for (i=0; i<nObjAnz; i++) {
/*N*/       SdrObject* pObj=pOL->GetObj(i);
/*N*/       if (!pObj->IsEdgeObj()) pObj->SetAnchorPos(rPnt);
/*N*/   }
/*N*/   if (bChg) {
/*N*/       SendRepaintBroadcast(TRUE);
/*N*/       SetChanged();
/*N*/       SendUserCall(SDRUSERCALL_MOVEONLY,aBoundRect0);
/*N*/   }
/*N*/ }



//STRIP001 void SdrObjGroup::NbcSetRelativePos(const Point& rPnt)
//STRIP001 {
//STRIP001  Point aRelPos0(GetSnapRect().TopLeft()-aAnchor);
//STRIP001  Size aSiz(rPnt.X()-aRelPos0.X(),rPnt.Y()-aRelPos0.Y());
//STRIP001  NbcMove(aSiz); // Der ruft auch das SetRectsDirty()
//STRIP001 }


/*N*/ void SdrObjGroup::SetRelativePos(const Point& rPnt)
/*N*/ {
/*N*/   Point aRelPos0(GetSnapRect().TopLeft()-aAnchor);
/*N*/   Size aSiz(rPnt.X()-aRelPos0.X(),rPnt.Y()-aRelPos0.Y());
/*N*/   if (aSiz.Width()!=0 || aSiz.Height()!=0) Move(aSiz); // Der ruft auch das SetRectsDirty() und Broadcast, ...
/*N*/ }


////////////////////////////////////////////////////////////////////////////////////////////////////
// ItemSet access

/*N*/ const SfxItemSet& SdrObjGroup::GetItemSet() const
/*N*/ {
/*N*/   // prepare ItemSet
/*N*/   if(mpGroupItemSet)
/*N*/       mpGroupItemSet->ClearItem();
/*N*/   else
/*N*/   {
/*N*/       ((SdrObjGroup*)this)->mpGroupItemSet =
/*N*/           ((SdrObjGroup*)this)->CreateNewItemSet((SfxItemPool&)(*GetItemPool()));
/*N*/       DBG_ASSERT(mpGroupItemSet, "Could not create an SfxItemSet(!)");
/*N*/   }
/*N*/
/*N*/   // collect all ItemSets in mpGroupItemSet
/*N*/   sal_uInt32 nCount(pSub->GetObjCount());
/*N*/   for(sal_uInt32 a(0); a < nCount; a++)
/*N*/   {
/*N*/       const SfxItemSet& rSet = pSub->GetObj(a)->GetItemSet();
/*N*/       SfxWhichIter aIter(rSet);
/*N*/       sal_uInt16 nWhich(aIter.FirstWhich());
/*N*/
/*N*/       while(nWhich)
/*N*/       {
/*N*/           if(SFX_ITEM_DONTCARE == rSet.GetItemState(nWhich, FALSE))
/*N*/               mpGroupItemSet->InvalidateItem(nWhich);
/*N*/           else
/*N*/               mpGroupItemSet->MergeValue(rSet.Get(nWhich), TRUE);
/*N*/
/*N*/           nWhich = aIter.NextWhich();
/*N*/       }
/*N*/   }
/*N*/
/*N*/   return *mpGroupItemSet;
/*N*/ }

/*N*/ SfxItemSet* SdrObjGroup::CreateNewItemSet(SfxItemPool& rPool)
/*N*/ {
/*N*/   // include ALL items
/*N*/   return new SfxItemSet(rPool, SDRATTR_START, SDRATTR_END);
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////
// private support routines for ItemSet access

/*N*/ void SdrObjGroup::ItemChange(const sal_uInt16 nWhich, const SfxPoolItem* pNewItem)
/*N*/ {
/*N*/   if(!IsLinkedGroup())
/*N*/   {
/*N*/       // ItemChange at all contained objects
/*N*/       List aPostItemChangeList;
/*N*/       sal_uInt32 nCount(pSub->GetObjCount());
/*N*/
/*N*/       for(sal_uInt32 a(0); a < nCount; a++)
/*N*/       {
/*N*/           SdrObject* pObj = pSub->GetObj(a);
/*N*/           if(pObj->AllowItemChange(nWhich, pNewItem))
/*N*/           {
/*N*/               pObj->ItemChange(nWhich, pNewItem);
/*N*/               aPostItemChangeList.Insert((void*)pObj, LIST_APPEND);
/*N*/           }
/*N*/       }
/*N*/
/*N*/       for(a = 0; a < aPostItemChangeList.Count(); a++)
/*N*/       {
/*N*/           SdrObject* pObj = (SdrObject*)aPostItemChangeList.GetObject(a);
/*N*/           pObj->PostItemChange(nWhich);
/*N*/       }
/*N*/   }
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////
// ItemSet was changed, maybe user wants to react

/*N*/ void SdrObjGroup::ItemSetChanged(const SfxItemSet& rSet)
/*N*/ {
/*N*/   if(!IsLinkedGroup())
/*N*/   {
/*N*/       sal_uInt32 nCount(pSub->GetObjCount());
/*N*/       for(sal_uInt32 a(0); a < nCount; a++)
/*N*/           pSub->GetObj(a)->ItemSetChanged(rSet);
/*N*/   }
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////
// pre- and postprocessing for objects for saving

/*N*/ void SdrObjGroup::PreSave()
/*N*/ {
/*N*/   // call parent
/*N*/   SdrObject::PreSave();
/*N*/
/*N*/   if(!IsLinkedGroup())
/*N*/   {
/*N*/       sal_uInt32 nCount(pSub->GetObjCount());
/*N*/       for(sal_uInt32 a(0); a < nCount; a++)
/*N*/           pSub->GetObj(a)->PreSave();
/*N*/   }
/*N*/ }

/*N*/ void SdrObjGroup::PostSave()
/*N*/ {
/*N*/   // call parent
/*N*/   SdrObject::PostSave();
/*N*/
/*N*/   if(!IsLinkedGroup())
/*N*/   {
/*N*/       sal_uInt32 nCount(pSub->GetObjCount());
/*N*/       for(sal_uInt32 a(0); a < nCount; a++)
/*N*/           pSub->GetObj(a)->PostSave();
/*N*/   }
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ SfxStyleSheet* SdrObjGroup::GetStyleSheet() const
/*N*/ {
/*N*/   // Hier mit 'nem Iterator. Es koennte sonst passieren dass ein
/*N*/   // verschachteltes Gruppenobjekt wegen DontCare NULL liefert.
/*N*/   // Das koennte ich dann nicht unterscheiden von NotSet.
/*N*/   SfxStyleSheet* pRet=NULL;
/*N*/   FASTBOOL b1st=TRUE;
/*N*/   SdrObjListIter aIter(*this,IM_DEEPNOGROUPS);
/*N*/   while (aIter.IsMore()) {
/*N*/       SdrObject* pObj=aIter.Next();
/*N*/       if (b1st) {
/*N*/           b1st=FALSE;
/*N*/           pRet=pObj->GetStyleSheet(); // Der Erste
/*N*/       } else {
/*N*/           if (pObj->GetStyleSheet()!=pRet) return NULL; // Unterschiedlich!
/*N*/       }
/*N*/   }
/*N*/   // Wenn hier angekommen, sind alle gleich.
/*N*/   return pRet;
/*N*/ }


/*N*/ void SdrObjGroup::NbcSetStyleSheet(SfxStyleSheet* pNewStyleSheet, FASTBOOL bDontRemoveHardAttr)
/*N*/ {
/*N*/   if (!IsLinkedGroup()) {
/*N*/       SdrObjList* pOL=pSub;
/*N*/       ULONG nObjAnz=pOL->GetObjCount();
/*N*/       for (ULONG i=0; i<nObjAnz; i++) {
/*N*/           pOL->GetObj(i)->NbcSetStyleSheet(pNewStyleSheet,bDontRemoveHardAttr);
/*N*/       }
/*N*/   }
/*N*/ }


/*N*/ void SdrObjGroup::SetStyleSheet(SfxStyleSheet* pNewStyleSheet, FASTBOOL bDontRemoveHardAttr)
/*N*/ {
/*N*/   if (!IsLinkedGroup()) {
/*N*/       SdrObjList* pOL=pSub;
/*N*/       ULONG nObjAnz=pOL->GetObjCount();
/*N*/       for (ULONG i=0; i<nObjAnz; i++) {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/            pOL->GetObj(i)->SetStyleSheet(pNewStyleSheet,bDontRemoveHardAttr);
/*N*/       }
/*N*/   }
/*N*/ }


//STRIP001 void SdrObjGroup::NbcReformatText()
//STRIP001 {
//STRIP001  pSub->NbcReformatAllTextObjects();
//STRIP001 }


/*N*/ void SdrObjGroup::ReformatText()
/*N*/ {
/*N*/   pSub->ReformatAllTextObjects();
/*N*/ }


//STRIP001 void SdrObjGroup::BurnInStyleSheetAttributes( BOOL bPseudoSheetsOnly )
//STRIP001 {
//STRIP001  pSub->BurnInStyleSheetAttributes( bPseudoSheetsOnly );
//STRIP001 }


/*N*/ void SdrObjGroup::RestartAnimation(SdrPageView* pPageView) const
/*N*/ {
/*N*/   pSub->RestartAllAnimations(pPageView);
/*N*/ }


//STRIP001 SdrObject* SdrObjGroup::DoConvertToPolyObj(BOOL bBezier) const
//STRIP001 {
//STRIP001  SdrObject* pGroup = new SdrObjGroup;
//STRIP001  pGroup->SetModel(GetModel());
//STRIP001
//STRIP001  for(UINT32 a=0;a<pSub->GetObjCount();a++)
//STRIP001  {
//STRIP001      SdrObject* pIterObj = pSub->GetObj(a);
//STRIP001         SdrObject* pResult = pIterObj->DoConvertToPolyObj(bBezier);
//STRIP001
//STRIP001         // pResult can be NULL e.g. for empty objects
//STRIP001         if( pResult )
//STRIP001             pGroup->GetSubList()->NbcInsertObject(pResult);
//STRIP001  }
//STRIP001
//STRIP001  return pGroup;
//STRIP001 }


/*N*/ void SdrObjGroup::WriteData(SvStream& rOut) const
/*N*/ {
/*N*/   SdrObject::WriteData(rOut);
/*N*/   // Fuer Abwaertskompatibilitaet (Lesen neuer Daten mit altem Code)
/*N*/   SdrDownCompat aCompat(rOut, STREAM_WRITE);
/*N*/
/*N*/ #ifdef DBG_UTIL
/*N*/   aCompat.SetID("SdrObjGroup");
/*N*/ #endif
/*N*/
/*N*/   // UNICODE: rOut << aName;
/*N*/   rOut.WriteByteString(aName);
/*N*/
/*N*/   UINT8 nTemp = bRefPoint; rOut << nTemp;
/*N*/   rOut << aRefPoint;
/*N*/   pSub->Save(rOut);
/*N*/   rOut << INT32(nDrehWink);
/*N*/   rOut << INT32(nShearWink);
/*N*/ }


/*N*/ void SdrObjGroup::ReadData(const SdrObjIOHeader& rHead, SvStream& rIn)
/*N*/ {
/*N*/   if(rIn.GetError())
/*N*/       return;
/*N*/
/*N*/   SdrObject::ReadData(rHead, rIn);
/*N*/   // Fuer Abwaertskompatibilitaet (Lesen neuer Daten mit altem Code)
/*N*/   SdrDownCompat aCompat(rIn, STREAM_READ);
/*N*/
/*N*/ #ifdef DBG_UTIL
/*N*/   aCompat.SetID("SdrObjGroup");
/*N*/ #endif
/*N*/
/*N*/   // UNICODE: rIn >> aName;
/*N*/   rIn.ReadByteString(aName);
/*N*/
/*N*/   UINT8 nTemp; rIn >> nTemp; bRefPoint = nTemp;
/*N*/   rIn >> aRefPoint;
/*N*/   pSub->Load(rIn, *pPage);
/*N*/
/*N*/   if(rHead.GetVersion() >= 2)
/*N*/   {
/*N*/       INT32 n32;
/*N*/
/*N*/       rIn >> n32; nDrehWink = n32;
/*N*/       rIn >> n32; nShearWink = n32;
/*N*/   }
/*N*/ }


/*N*/ void SdrObjGroup::AfterRead()
/*N*/ {
/*N*/   SdrObject::AfterRead();
/*N*/   pSub->AfterRead();
/*N*/
/*N*/   // #80049# as fix for errors after #69055#
/*N*/   if(aAnchor.X() || aAnchor.Y())
/*N*/       NbcSetAnchorPos(aAnchor);
/*N*/ }

// ItemPool fuer dieses Objekt wechseln
//STRIP001 void SdrObjGroup::MigrateItemPool(SfxItemPool* pSrcPool, SfxItemPool* pDestPool, SdrModel* pNewModel )
//STRIP001 {
//STRIP001  if(pSrcPool && pDestPool && (pSrcPool != pDestPool))
//STRIP001  {
//STRIP001      // call parent
//STRIP001      SdrObject::MigrateItemPool(pSrcPool, pDestPool, pNewModel );
//STRIP001
//STRIP001      // own reaction
//STRIP001      SdrObjList* pOL = pSub;
//STRIP001      sal_uInt32 nObjAnz(pOL->GetObjCount());
//STRIP001
//STRIP001      for(sal_uInt32 a(0); a < nObjAnz; a++)
//STRIP001      {
//STRIP001          pOL->GetObj(a)->MigrateItemPool(pSrcPool, pDestPool, pNewModel );
//STRIP001      }
//STRIP001  }
//STRIP001 }

}
