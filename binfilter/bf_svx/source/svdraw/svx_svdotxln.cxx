/*************************************************************************
 *
 *  $RCSfile: svx_svdotxln.cxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2005-01-11 11:42:22 $
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

// auto strip #include <unotools/ucbstreamhelper.hxx>
// auto strip #include <unotools/localfilehelper.hxx>

// auto strip #ifndef _UCBHELPER_CONTENT_HXX_
// auto strip #include <ucbhelper/content.hxx>
// auto strip #endif
// auto strip #ifndef _UCBHELPER_CONTENTBROKER_HXX_
// auto strip #include <ucbhelper/contentbroker.hxx>
// auto strip #endif
// auto strip #ifndef _UNOTOOLS_DATETIME_HXX_
// auto strip #include <unotools/datetime.hxx>
// auto strip #endif

#include "svdotext.hxx"
// auto strip #include "svditext.hxx"
#include "svdmodel.hxx"
#include "svdio.hxx"
// auto strip #include "editdata.hxx"

#ifndef SVX_LIGHT
#ifndef _LNKBASE_HXX //autogen
#include <so3/lnkbase.hxx>
#endif
#endif

#ifndef _SVXLINKMGR_HXX //autogen
#include <linkmgr.hxx>
#endif

// auto strip #ifndef _URLOBJ_HXX
// auto strip #include <tools/urlobj.hxx>
// auto strip #endif

#include <svtools/urihelper.hxx>

// #90477#
#ifndef _TOOLS_TENCCVT_HXX
#include <tools/tenccvt.hxx>
#endif
#include "so3/staticbaseurl.hxx"
namespace binfilter {

#ifndef SVX_LIGHT
////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  @@@@  @@@@@  @@@@@@  @@@@@@ @@@@@@ @@  @@ @@@@@@  @@    @@ @@  @@ @@  @@
// @@  @@ @@  @@     @@    @@   @@      @@@@    @@    @@    @@ @@@ @@ @@ @@
// @@  @@ @@@@@      @@    @@   @@@@@    @@     @@    @@    @@ @@@@@@ @@@@
// @@  @@ @@  @@ @@  @@    @@   @@      @@@@    @@    @@    @@ @@ @@@ @@ @@
//  @@@@  @@@@@   @@@@     @@   @@@@@@ @@  @@   @@    @@@@@ @@ @@  @@ @@  @@
//
// ImpSdrObjTextLink zur Verbindung von SdrTextObj und LinkManager
//
// Einem solchen Link merke ich mir als SdrObjUserData am Objekt. Im Gegensatz
// zum Grafik-Link werden die ObjektDaten jedoch kopiert (fuer Paint, etc.).
// Die Information ob das Objekt ein Link ist besteht genau darin, dass dem
// Objekt ein entsprechender UserData-Record angehaengt ist oder nicht.
//
////////////////////////////////////////////////////////////////////////////////////////////////////

/*?*/ class ImpSdrObjTextLink: public ::so3::SvBaseLink
/*?*/ {
/*?*/   SdrTextObj*                 pSdrObj;
/*?*/
/*?*/ public:
/*?*/   ImpSdrObjTextLink( SdrTextObj* pObj1 )
/*?*/       : ::so3::SvBaseLink( ::so3::LINKUPDATE_ONCALL, FORMAT_FILE ),
/*?*/           pSdrObj( pObj1 )
/*?*/   {}
/*?*/   virtual ~ImpSdrObjTextLink();
/*?*/
/*?*/   virtual void Closed();
/*?*/   virtual void DataChanged( const String& rMimeType,
/*?*/                               const ::com::sun::star::uno::Any & rValue );
/*?*/
/*?*/   BOOL Connect() { return 0 != SvBaseLink::GetRealObject(); }
/*?*/ };

/*?*/ ImpSdrObjTextLink::~ImpSdrObjTextLink()
/*?*/ {
/*?*/ }

/*?*/ void ImpSdrObjTextLink::Closed()
/*?*/ {
/*?*/   if (pSdrObj )
/*?*/   {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/        // pLink des Objekts auf NULL setzen, da die Link-Instanz ja gerade destruiert wird.
//STRIP001 /*?*/        ImpSdrObjTextLinkUserData* pData=pSdrObj->GetLinkUserData();
//STRIP001 /*?*/        if (pData!=NULL) pData->pLink=NULL;
//STRIP001 /*?*/        pSdrObj->ReleaseTextLink();
/*?*/   }
/*?*/   SvBaseLink::Closed();
/*?*/ }


/*?*/ void ImpSdrObjTextLink::DataChanged( const String& rMimeType,
/*?*/                               const ::com::sun::star::uno::Any & rValue )
/*?*/ {
/*?*/   FASTBOOL bForceReload=FALSE;
/*?*/   SdrModel* pModel = pSdrObj ? pSdrObj->GetModel() : 0;
/*?*/   SvxLinkManager* pLinkManager= pModel ? pModel->GetLinkManager() : 0;
/*?*/   if( pLinkManager )
/*?*/   {
/*?*/       ImpSdrObjTextLinkUserData* pData=pSdrObj->GetLinkUserData();
/*?*/       if( pData )
/*?*/       {
/*?*/           String aFile;
/*?*/           String aFilter;
/*?*/           pLinkManager->GetDisplayNames( this, 0,&aFile, 0, &aFilter );
/*?*/
/*?*/           if( !pData->aFileName.Equals( aFile ) ||
/*?*/               !pData->aFilterName.Equals( aFilter ))
/*?*/           {
/*?*/               pData->aFileName = aFile;
/*?*/               pData->aFilterName = aFilter;
/*?*/               pSdrObj->SetChanged();
/*?*/               bForceReload = TRUE;
/*?*/           }
/*?*/       }
/*?*/   }
/*?*/   if (pSdrObj )
/*?*/   {DBG_BF_ASSERT(0, "STRIP"); }//STRIP001     pSdrObj->ReloadLinkedText( bForceReload );
/*?*/ }
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

/*N*/ TYPEINIT1(ImpSdrObjTextLinkUserData,SdrObjUserData);

/*N*/ ImpSdrObjTextLinkUserData::ImpSdrObjTextLinkUserData(SdrTextObj* pObj1):
/*N*/   SdrObjUserData(SdrInventor,SDRUSERDATA_OBJTEXTLINK,0),
/*N*/   pObj(pObj1),
/*N*/   pLink(NULL),
/*N*/   eCharSet(RTL_TEXTENCODING_DONTKNOW)
/*N*/ {
/*N*/ }

/*N*/ ImpSdrObjTextLinkUserData::~ImpSdrObjTextLinkUserData()
/*N*/ {
/*N*/ #ifndef SVX_LIGHT
/*?*/ DBG_BF_ASSERT(0, "STRIP"); //STRIP001     delete pLink;
/*N*/ #endif
/*N*/ }

/*N*/ SdrObjUserData* ImpSdrObjTextLinkUserData::Clone(SdrObject* pObj1) const
/*N*/ {
/*N*/   ImpSdrObjTextLinkUserData* pData=new ImpSdrObjTextLinkUserData((SdrTextObj*)pObj1);
/*N*/   pData->aFileName  =aFileName;
/*N*/   pData->aFilterName=aFilterName;
/*N*/   pData->aFileDate0 =aFileDate0;
/*N*/   pData->eCharSet   =eCharSet;
/*N*/   pData->pLink=NULL;
/*N*/   return pData;
/*N*/ }

/*N*/ void ImpSdrObjTextLinkUserData::WriteData(SvStream& rOut)
/*N*/ {
/*N*/   SdrObjUserData::WriteData(rOut);
/*N*/   // Fuer Abwaertskompatibilitaet (Lesen neuer Daten mit altem Code)
/*N*/   SdrDownCompat aCompat(rOut, STREAM_WRITE);
/*N*/
/*N*/ #ifdef DBG_UTIL
/*N*/   aCompat.SetID("ImpSdrObjTextLinkUserData");
/*N*/ #endif
/*N*/
/*N*/   String aRelFileName;
/*N*/
/*N*/   if( aFileName.Len() )
/*N*/   {
/*N*/       aRelFileName = so3::StaticBaseUrl::AbsToRel( aFileName,
/*N*/                                               INetURLObject::WAS_ENCODED,
/*N*/                                               INetURLObject::DECODE_UNAMBIGUOUS );
/*N*/   }
/*N*/
/*N*/   rOut.WriteByteString( aRelFileName );
/*N*/
/*N*/   // UNICODE: rOut << aFilterName;
/*N*/   rOut.WriteByteString(aFilterName);
/*N*/
/*N*/   // #90477# rOut << UINT16(GetStoreCharSet(eCharSet));
/*N*/   rOut << UINT16(GetSOStoreTextEncoding(eCharSet, (sal_uInt16)rOut.GetVersion()));
/*N*/
/*N*/   rOut << UINT32(aFileDate0.GetDate());
/*N*/   rOut << UINT32(aFileDate0.GetTime());
/*N*/ }

/*N*/ void ImpSdrObjTextLinkUserData::ReadData(SvStream& rIn)
/*N*/ {
/*N*/   SdrObjUserData::ReadData(rIn);
/*N*/   // Fuer Abwaertskompatibilitaet (Lesen neuer Daten mit altem Code)
/*N*/   SdrDownCompat aCompat(rIn, STREAM_READ);
/*N*/
/*N*/ #ifdef DBG_UTIL
/*N*/   aCompat.SetID("ImpSdrObjTextLinkUserData");
/*N*/ #endif
/*N*/
/*N*/   UINT32 nTmp32;
/*N*/   UINT16 nTmp16;
/*N*/   String aFileNameRel;
/*N*/
/*N*/   rIn.ReadByteString(aFileNameRel);
/*N*/
/*N*/   if( aFileNameRel.Len() )
/*N*/   {
/*N*/
/*N*/       aFileName = so3::StaticBaseUrl::SmartRelToAbs( aFileNameRel, FALSE,
/*N*/                                               INetURLObject::WAS_ENCODED,
/*N*/                                               INetURLObject::DECODE_UNAMBIGUOUS );
/*N*/   }
/*N*/   else
/*N*/       aFileName.Erase();
/*N*/
/*N*/   // UNICODE: rIn >> aFilterName;
/*N*/   rIn.ReadByteString(aFilterName);
/*N*/
/*N*/   // #90477# rIn >> nTmp16; eCharSet = rtl_TextEncoding(nTmp16);
/*N*/   rIn >> nTmp16;
/*N*/   eCharSet = (rtl_TextEncoding)GetSOLoadTextEncoding((rtl_TextEncoding)nTmp16, (sal_uInt16)rIn.GetVersion());
/*N*/
/*N*/   rIn >> nTmp32; aFileDate0.SetDate(nTmp32);
/*N*/   rIn >> nTmp32; aFileDate0.SetTime(nTmp32);
/*N*/ }

/*N*/ void ImpSdrObjTextLinkUserData::AfterRead()
/*N*/ {
/*N*/   if (pObj!=NULL) {
/*N*/       pObj->ImpLinkAnmeldung();
/*N*/       // lt. Anweisung von MB kein automatisches Reload mehr
/*N*/       //pObj->ReloadLinkedText();
/*N*/   }
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  @@@@@@ @@@@@ @@   @@ @@@@@@  @@@@  @@@@@  @@@@@@
//    @@   @@    @@@ @@@   @@   @@  @@ @@  @@     @@
//    @@   @@     @@@@@    @@   @@  @@ @@  @@     @@
//    @@   @@@@    @@@     @@   @@  @@ @@@@@      @@
//    @@   @@     @@@@@    @@   @@  @@ @@  @@     @@
//    @@   @@    @@@ @@@   @@   @@  @@ @@  @@ @@  @@
//    @@   @@@@@ @@   @@   @@    @@@@  @@@@@   @@@@
//
////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 void SdrTextObj::SetTextLink(const String& rFileName, const String& rFilterName, rtl_TextEncoding eCharSet)
//STRIP001 {
//STRIP001  if(eCharSet == RTL_TEXTENCODING_DONTKNOW)
//STRIP001      eCharSet = gsl_getSystemTextEncoding();
//STRIP001
//STRIP001  ImpSdrObjTextLinkUserData* pData=GetLinkUserData();
//STRIP001  if (pData!=NULL) {
//STRIP001      ReleaseTextLink();
//STRIP001  }
//STRIP001  pData=new ImpSdrObjTextLinkUserData(this);
//STRIP001  pData->aFileName=rFileName;
//STRIP001  pData->aFilterName=rFilterName;
//STRIP001  pData->eCharSet=eCharSet;
//STRIP001  InsertUserData(pData);
//STRIP001  ImpLinkAnmeldung();
//STRIP001 }

//STRIP001 void SdrTextObj::ReleaseTextLink()
//STRIP001 {
//STRIP001  ImpLinkAbmeldung();
//STRIP001  USHORT nAnz=GetUserDataCount();
//STRIP001  for (USHORT nNum=nAnz; nNum>0;) {
//STRIP001      nNum--;
//STRIP001      SdrObjUserData* pData=GetUserData(nNum);
//STRIP001      if (pData->GetInventor()==SdrInventor && pData->GetId()==SDRUSERDATA_OBJTEXTLINK) {
//STRIP001          DeleteUserData(nNum);
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 FASTBOOL SdrTextObj::ReloadLinkedText(FASTBOOL bForceLoad)
//STRIP001 {
//STRIP001  ImpSdrObjTextLinkUserData*  pData = GetLinkUserData();
//STRIP001  FASTBOOL                    bRet = TRUE;
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
//STRIP001          if( bLoad )
//STRIP001          {
//STRIP001              bRet = LoadText( pData->aFileName, pData->aFilterName, pData->eCharSet );
//STRIP001          }
//STRIP001
//STRIP001          pData->aFileDate0 = aFileDT;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  return bRet;
//STRIP001 }

//STRIP001 FASTBOOL SdrTextObj::LoadText(const String& rFileName, const String& rFilterName, rtl_TextEncoding eCharSet)
//STRIP001 {
//STRIP001  INetURLObject   aFileURL( rFileName );
//STRIP001  BOOL            bRet = FALSE;
//STRIP001
//STRIP001  if( aFileURL.GetProtocol() == INET_PROT_NOT_VALID )
//STRIP001  {
//STRIP001      String aFileURLStr;
//STRIP001
//STRIP001      if( ::utl::LocalFileHelper::ConvertPhysicalNameToURL( rFileName, aFileURLStr ) )
//STRIP001          aFileURL = INetURLObject( aFileURLStr );
//STRIP001      else
//STRIP001          aFileURL.SetSmartURL( rFileName );
//STRIP001  }
//STRIP001
//STRIP001  DBG_ASSERT( aFileURL.GetProtocol() != INET_PROT_NOT_VALID, "invalid URL" );
//STRIP001
//STRIP001  SvStream* pIStm = ::utl::UcbStreamHelper::CreateStream( aFileURL.GetMainURL( INetURLObject::NO_DECODE ), STREAM_READ );
//STRIP001
//STRIP001  if( pIStm )
//STRIP001  {
//STRIP001      // #90477# pIStm->SetStreamCharSet( eCharSet );
//STRIP001      pIStm->SetStreamCharSet(GetSOLoadTextEncoding(eCharSet, (sal_uInt16)pIStm->GetVersion()));
//STRIP001
//STRIP001      char cRTF[5];
//STRIP001      cRTF[4] = 0;
//STRIP001      pIStm->Read(cRTF, 5);
//STRIP001
//STRIP001      BOOL bRTF = cRTF[0] == '{' && cRTF[1] == '\\' && cRTF[2] == 'r' && cRTF[3] == 't' && cRTF[4] == 'f';
//STRIP001
//STRIP001      pIStm->Seek(0);
//STRIP001
//STRIP001      if( !pIStm->GetError() )
//STRIP001      {
//STRIP001          SetText( *pIStm, bRTF ? EE_FORMAT_RTF : EE_FORMAT_TEXT );
//STRIP001          bRet = TRUE;
//STRIP001      }
//STRIP001
//STRIP001      delete pIStm;
//STRIP001  }
//STRIP001
//STRIP001  return bRet;
//STRIP001 }

/*N*/ ImpSdrObjTextLinkUserData* SdrTextObj::GetLinkUserData() const
/*N*/ {
/*N*/   ImpSdrObjTextLinkUserData* pData=NULL;
/*N*/   USHORT nAnz=GetUserDataCount();
/*N*/   for (USHORT nNum=nAnz; nNum>0 && pData==NULL;) {
/*N*/       nNum--;
/*N*/       pData=(ImpSdrObjTextLinkUserData*)GetUserData(nNum);
/*N*/       if (pData->GetInventor()!=SdrInventor || pData->GetId()!=SDRUSERDATA_OBJTEXTLINK) {
/*N*/           pData=NULL;
/*N*/       }
/*N*/   }
/*N*/   return pData;
/*N*/ }

/*N*/ void SdrTextObj::ImpLinkAnmeldung()
/*N*/ {
/*N*/ #ifndef SVX_LIGHT
/*N*/   ImpSdrObjTextLinkUserData* pData=GetLinkUserData();
/*N*/   SvxLinkManager* pLinkManager=pModel!=NULL ? pModel->GetLinkManager() : NULL;
/*N*/   if (pLinkManager!=NULL && pData!=NULL && pData->pLink==NULL) { // Nicht 2x Anmelden
/*N*/       pData->pLink=new ImpSdrObjTextLink(this);
/*N*/ #ifdef GCC
/*N*/       pLinkManager->InsertFileLink(*pData->pLink,OBJECT_CLIENT_FILE,pData->aFileName,
/*N*/                                    pData->aFilterName.Len() ?
/*N*/                                     &pData->aFilterName : (const String *)NULL,
/*N*/                                    (const String *)NULL);
/*N*/ #else
/*N*/       pLinkManager->InsertFileLink(*pData->pLink,OBJECT_CLIENT_FILE,pData->aFileName,
/*N*/                                    pData->aFilterName.Len() ? &pData->aFilterName : NULL,NULL);
/*N*/ #endif
/*N*/       pData->pLink->Connect();
/*N*/   }
/*N*/ #endif // SVX_LIGHT
/*N*/ }

/*N*/ void SdrTextObj::ImpLinkAbmeldung()
/*N*/ {
/*N*/ #ifndef SVX_LIGHT
/*N*/   ImpSdrObjTextLinkUserData* pData=GetLinkUserData();
/*N*/   SvxLinkManager* pLinkManager=pModel!=NULL ? pModel->GetLinkManager() : NULL;
/*N*/   if (pLinkManager!=NULL && pData!=NULL && pData->pLink!=NULL) { // Nicht 2x Abmelden
/*N*/       // Bei Remove wird *pLink implizit deleted
/*?*/   DBG_BF_ASSERT(0, "STRIP"); //STRIP001   pLinkManager->Remove( pData->pLink );
//STRIP001 /*?*/        pData->pLink=NULL;
/*N*/   }
/*N*/ #endif // SVX_LIGHT
/*N*/ }

}
