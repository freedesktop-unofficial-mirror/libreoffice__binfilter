/*************************************************************************
 *
 *  $RCSfile: sw_fldmgr.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:54:35 $
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

#ifndef _CMDID_H
#include <cmdid.h>
#endif
#ifndef _HINTIDS_HXX
#include <hintids.hxx>
#endif

#ifndef _SFXSTRITEM_HXX
#include <svtools/stritem.hxx>
#endif
#ifndef _SVTOOLS_LANGUAGEOPTIONS_HXX
#include <svtools/languageoptions.hxx>
#endif

#ifndef _COM_SUN_STAR_LANG_XMULTISERVICEFACTORY_HPP_
#include <com/sun/star/lang/XMultiServiceFactory.hpp>
#endif
#ifndef _COM_SUN_STAR_CONTAINER_XNAMEACCESS_HPP_
#include <com/sun/star/container/XNameAccess.hpp>
#endif
#ifndef _COM_SUN_STAR_TEXT_XDEFAULTNUMBERINGPROVIDER_HPP_
#include <com/sun/star/text/XDefaultNumberingProvider.hpp>
#endif
#ifndef _COM_SUN_STAR_TEXT_XNUMBERINGTYPEINFO_HPP_
#include <com/sun/star/text/XNumberingTypeInfo.hpp>
#endif
#ifndef _COM_SUN_STAR_STYLE_NUMBERINGTYPE_HPP_
#include <com/sun/star/style/NumberingType.hpp>
#endif
#ifndef _COM_SUN_STAR_BEANS_XPROPERTYSET_HPP_
#include <com/sun/star/beans/XPropertySet.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBC_XCONNECTION_HPP_
#include <com/sun/star/sdbc/XConnection.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBC_XDATASOURCE_HPP_
#include <com/sun/star/sdbc/XDataSource.hpp>
#endif
#ifndef _COMPHELPER_PROCESSFACTORY_HXX_
#include <comphelper/processfactory.hxx>
#endif
#ifndef _UNO_LINGU_HXX
#include <bf_svx/unolingu.hxx>
#endif
#ifndef _UNOTOOLS_LOCALEDATAWRAPPER_HXX
#include <unotools/localedatawrapper.hxx>
#endif

#ifndef _SFXDISPATCH_HXX //autogen
#include <bf_sfx2/dispatch.hxx>
#endif
#ifndef _SFXDOCINF_HXX //autogen
#include <bf_sfx2/docinf.hxx>
#endif
#ifndef _SFX_OBJSH_HXX //autogen
#include <bf_sfx2/objsh.hxx>
#endif
#ifndef _LINKMGR_HXX //autogen
#include <so3/linkmgr.hxx>
#endif
#ifndef _BASMGR_HXX //autogen
#include <basic/basmgr.hxx>
#endif
#ifndef _SVX_LANGITEM_HXX //autogen
#include <bf_svx/langitem.hxx>
#endif
#ifndef _SFXMACITEM_HXX //autogen
#include <svtools/macitem.hxx>
#endif
#ifndef _SB_SBMOD_HXX //autogen
#include <basic/sbmod.hxx>
#endif
#ifndef _FMTRFMRK_HXX //autogen
#include <fmtrfmrk.hxx>
#endif
#ifndef _SFXAPP_HXX //autogen
#include <bf_sfx2/app.hxx>
#endif
#ifndef _SB_SBSTAR_HXX //autogen
#include <basic/sbstar.hxx>
#endif
#ifndef _SB_SBMETH_HXX //autogen
#include <basic/sbmeth.hxx>
#endif
#ifndef _SBXCLASS_HXX //autogen
#include <svtools/sbx.hxx>
#endif
#ifndef _OFF_APP_HXX //autogen
#include <bf_offmgr/app.hxx>
#endif
#ifndef _ZFORLIST_HXX //autogen
#include <svtools/zforlist.hxx>
#endif
#ifndef _ZFORMAT_HXX //autogen
#include <svtools/zformat.hxx>
#endif
#ifndef _SB_SBMOD_HXX //autogen
#include <basic/sbmod.hxx>
#endif
#ifndef _URLOBJ_HXX
#include <tools/urlobj.hxx>
#endif

#ifndef _VIEW_HXX
#include <view.hxx>
#endif
#ifndef _WRTSH_HXX
#include <wrtsh.hxx>        // Actives Fenster
#endif
#ifndef _DOC_HXX
#include <doc.hxx>      // Actives Fenster
#endif
#ifndef _DOCSH_HXX
#include <docsh.hxx>        // Actives Fenster
#endif
#ifndef _SWMODULE_HXX
#include <swmodule.hxx>
#endif
#ifndef _CHARATR_HXX
#include <charatr.hxx>
#endif
#ifndef _FMTINFMT_HXX //autogen
#include <fmtinfmt.hxx>
#endif
#ifndef _CELLATR_HXX
#include <cellatr.hxx>
#endif
#ifndef _DBMGR_HXX
#include <dbmgr.hxx>
#endif
#ifndef _SHELLRES_HXX
#include <shellres.hxx>
#endif
#ifndef _FLDBAS_HXX
#include <fldbas.hxx>
#endif
#ifndef _DOCUFLD_HXX
#include <docufld.hxx>
#endif
#ifndef _CHPFLD_HXX
#include <chpfld.hxx>
#endif
#ifndef _DDEFLD_HXX
#include <ddefld.hxx>
#endif
#ifndef _EXPFLD_HXX
#include <expfld.hxx>
#endif
#ifndef _REFFLD_HXX
#include <reffld.hxx>
#endif
#ifndef _USRFLD_HXX
#include <usrfld.hxx>
#endif
#ifndef _DBFLD_HXX
#include <dbfld.hxx>
#endif
#ifndef _AUTHFLD_HXX
#include <authfld.hxx>
#endif
#ifndef _FLDDAT_HXX
#include <flddat.hxx>
#endif
#ifndef _FLDMGR_HXX
#include <fldmgr.hxx>
#endif
#ifndef _CRSSKIP_HXX
#include <crsskip.hxx>
#endif

#ifndef _FLDUI_HRC
#include <fldui.hrc>
#endif
#ifndef _LEGACYBINFILTERMGR_HXX
#include <legacysmgr/legacy_binfilters_smgr.hxx>    //STRIP002
#endif
namespace binfilter {
using namespace rtl;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::container;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::beans;
using namespace ::com::sun::star::text;
using namespace ::com::sun::star::style;
using namespace ::com::sun::star::sdbc;

/*--------------------------------------------------------------------
    Beschreibung: Gruppen der Felder
 --------------------------------------------------------------------*/
/*N*/ enum
/*N*/ {
/*N*/   GRP_DOC_BEGIN   =  0,
/*N*/   GRP_DOC_END     =  GRP_DOC_BEGIN + 11,
/*N*/
/*N*/   GRP_FKT_BEGIN   =  GRP_DOC_END,
    GRP_FKT_END     =  GRP_FKT_BEGIN + 8,
/*N*/
/*N*/   GRP_REF_BEGIN   =  GRP_FKT_END,
/*N*/   GRP_REF_END     =  GRP_REF_BEGIN + 2,
/*N*/
/*N*/   GRP_REG_BEGIN   =  GRP_REF_END,
/*N*/   GRP_REG_END     =  GRP_REG_BEGIN + 1,
/*N*/
/*N*/   GRP_DB_BEGIN    =  GRP_REG_END,
/*N*/   GRP_DB_END      =  GRP_DB_BEGIN  + 5,
/*N*/
/*N*/   GRP_VAR_BEGIN   =  GRP_DB_END,
/*N*/   GRP_VAR_END     =  GRP_VAR_BEGIN + 9
/*N*/ };
/*N*/
/*N*/ enum
/*N*/ {
/*N*/   GRP_WEB_DOC_BEGIN   =  0,
/*N*/   GRP_WEB_DOC_END     =  GRP_WEB_DOC_BEGIN + 9,
/*N*/
/*N*/   GRP_WEB_FKT_BEGIN   =  GRP_WEB_DOC_END + 2,
/*N*/   GRP_WEB_FKT_END     =  GRP_WEB_FKT_BEGIN + 0,   // Die Gruppe ist leer!
/*N*/
/*N*/   GRP_WEB_REF_BEGIN   =  GRP_WEB_FKT_END + 6,     // Die Gruppe ist leer!
/*N*/   GRP_WEB_REF_END     =  GRP_WEB_REF_BEGIN + 0,
/*N*/
/*N*/   GRP_WEB_REG_BEGIN   =  GRP_WEB_REF_END + 2,
/*N*/   GRP_WEB_REG_END     =  GRP_WEB_REG_BEGIN + 1,
/*N*/
/*N*/   GRP_WEB_DB_BEGIN    =  GRP_WEB_REG_END,         // Die Gruppe ist leer!
/*N*/   GRP_WEB_DB_END      =  GRP_WEB_DB_BEGIN  + 0,
/*N*/
/*N*/   GRP_WEB_VAR_BEGIN   =  GRP_WEB_DB_END + 5,
/*N*/   GRP_WEB_VAR_END     =  GRP_WEB_VAR_BEGIN + 1
/*N*/ };

/*--------------------------------------------------------------------
     Beschreibung: Formate in der richtigen Reihenfolge
--------------------------------------------------------------------*/
/*N*/ static const USHORT __FAR_DATA aSetFmt[] =
/*N*/ {
/*N*/ // die Reihenfolge muss zu Beginn mit den ResourceIds fuer FMT_SETVAR_???
/*N*/ // uebereinstimmen
/*N*/   0,
/*N*/   0
/*N*/ };
/*N*/
/*N*/ static const USHORT __FAR_DATA aGetFmt[] =
/*N*/ {
/*N*/ // die Reihenfolge muss zu Beginn mit den ResourceIds fuer FMT_GETVAR_???
/*N*/ // uebereinstimmen
/*N*/   0
/*N*/ };
/*N*/
/*N*/ static const USHORT __FAR_DATA aUsrFmt[] =
/*N*/ {
/*N*/ // die Reihenfolge muss zu Beginn mit den ResourceIds fuer FMT_SETVAR_???
/*N*/ // uebereinstimmen
/*N*/   0,
/*N*/   SUB_CMD
/*N*/ };
/*N*/
/*N*/ static const USHORT __FAR_DATA aDBFmt[] =
/*N*/ {
/*N*/ // die Reihenfolge muss zu Beginn mit den ResourceIds fuer FMT_DBFLD_???
/*N*/ // uebereinstimmen
/*N*/   SUB_OWN_FMT
/*N*/ };
/*N*/
/*N*/ static const USHORT VF_COUNT      = sizeof(aGetFmt) / sizeof(USHORT);
/*N*/ static const USHORT VF_USR_COUNT  = sizeof(aUsrFmt) / sizeof(USHORT);
/*N*/ static const USHORT VF_DB_COUNT       = sizeof(aDBFmt)  / sizeof(USHORT);
/*N*/
/*--------------------------------------------------------------------
    Beschreibung: Feldtypen und Subtypes
 --------------------------------------------------------------------*/
struct SwFldPack
{
    USHORT  nTypeId;

    USHORT  nSubTypeStart;
    USHORT  nSubTypeEnd;

    ULONG   nFmtBegin;
    ULONG   nFmtEnd;
};

/*--------------------------------------------------------------------
    Beschreibung: Strings und Formate
 --------------------------------------------------------------------*/
static const SwFldPack __FAR_DATA aSwFlds[] =
{
    // Dokument
    TYP_EXTUSERFLD,     FLD_EU_BEGIN,       FLD_EU_END,     0,                  0,
    TYP_AUTHORFLD,      0,                  0,              FMT_AUTHOR_BEGIN,   FMT_AUTHOR_END,
    TYP_DATEFLD,        FLD_DATE_BEGIN,     FLD_DATE_END,   0,                  0,
    TYP_TIMEFLD,        FLD_TIME_BEGIN,     FLD_TIME_END,   0,                  0,
    TYP_PAGENUMBERFLD,  0,                  0,              FMT_NUM_BEGIN,      FMT_NUM_END-1,
    TYP_NEXTPAGEFLD,    0,                  0,              FMT_NUM_BEGIN,      FMT_NUM_END,
    TYP_PREVPAGEFLD,    0,                  0,              FMT_NUM_BEGIN,      FMT_NUM_END,
    TYP_FILENAMEFLD,    0,                  0,              FMT_FF_BEGIN,       FMT_FF_END,
    TYP_DOCSTATFLD,     FLD_STAT_BEGIN,     FLD_STAT_END,   FMT_NUM_BEGIN,      FMT_NUM_END-1,

    TYP_CHAPTERFLD,     0,                  0,              FMT_CHAPTER_BEGIN,  FMT_CHAPTER_END,
    TYP_TEMPLNAMEFLD,   0,                  0,              FMT_FF_BEGIN,       FMT_FF_END,

    // Funktion
    TYP_CONDTXTFLD,     0,                  0,              0,                  0,
    TYP_DROPDOWN,       0,                  0,              0,                  0,
    TYP_INPUTFLD,       FLD_INPUT_BEGIN,    FLD_INPUT_END,  0,                  0,
    TYP_MACROFLD,       0,                  0,              0,                  0,
    TYP_JUMPEDITFLD,    0,                  0,              FMT_MARK_BEGIN,     FMT_MARK_END,
    TYP_COMBINED_CHARS,  0,                 0,              0,                  0,
    TYP_HIDDENTXTFLD,   0,                  0,              0,                  0,
    TYP_HIDDENPARAFLD,  0,                  0,              0,                  0,

    // Referenzen
    TYP_SETREFFLD,      0,                  0,              0,                  0,
    TYP_GETREFFLD,      0,                  0,              FMT_REF_BEGIN,      FMT_REF_END,

    // Ablage
    TYP_DOCINFOFLD,     0,                  0,              FMT_REG_BEGIN,      FMT_REG_END,

    // Datenbank
    TYP_DBFLD,          0,                  0,              FMT_DBFLD_BEGIN,    FMT_DBFLD_END,
    TYP_DBNEXTSETFLD,   0,                  0,              0,                  0,
    TYP_DBNUMSETFLD,    0,                  0,              0,                  0,
    TYP_DBSETNUMBERFLD, 0,                  0,              FMT_NUM_BEGIN,      FMT_NUM_END-2,
    TYP_DBNAMEFLD,      0,                  0,              0,                  0,

    // Variablen
    TYP_SETFLD,         0,                  0,              FMT_SETVAR_BEGIN,   FMT_SETVAR_END,

    TYP_GETFLD,         0,                  0,              FMT_GETVAR_BEGIN,   FMT_GETVAR_END,
    TYP_DDEFLD,         0,                  0,              FMT_DDE_BEGIN,      FMT_DDE_END,
    TYP_FORMELFLD,      0,                  0,              FMT_GETVAR_BEGIN,   FMT_GETVAR_END,
    TYP_INPUTFLD,       FLD_INPUT_BEGIN,    FLD_INPUT_END,  0,                  0,
    TYP_SEQFLD,         0,                  0,              FMT_NUM_BEGIN,      FMT_NUM_END-2,
    TYP_SETREFPAGEFLD,  FLD_PAGEREF_BEGIN,  FLD_PAGEREF_END,0,                  0,
    TYP_GETREFPAGEFLD,  0,                  0,              FMT_NUM_BEGIN,      FMT_NUM_END-1,
    TYP_USERFLD,        0,                  0,              FMT_USERVAR_BEGIN,  FMT_USERVAR_END
};

String* SwFldMgr::pDate = 0;
String* SwFldMgr::pTime = 0;


/*--------------------------------------------------------------------
    Beschreibung: Zugriff auf die Shell
 --------------------------------------------------------------------*/

//STRIP001 SwWrtShell* lcl_GetShell()
//STRIP001 {
//STRIP001  SwView* pView;
//STRIP001  if ( 0 != (pView = ::GetActiveView()) )
//STRIP001      return pView->GetWrtShellPtr();
//STRIP001  return 0;
//STRIP001 }
//STRIP001
//STRIP001 inline USHORT GetPackCount() {   return sizeof(aSwFlds) / sizeof(SwFldPack); }
//STRIP001
//STRIP001 /*--------------------------------------------------------------------
//STRIP001  Beschreibung: FieldManager regelt das Einfuegen und Updaten
//STRIP001                von Feldern
//STRIP001  --------------------------------------------------------------------*/
//STRIP001
//STRIP001 SwFldMgr::SwFldMgr(SwWrtShell* pSh ) :
//STRIP001  bEvalExp(TRUE),
//STRIP001  pModule(0),
//STRIP001  pMacroItem(0),
//STRIP001  pWrtShell(pSh)
//STRIP001 {
//STRIP001  // aktuelles Feld ermitteln falls vorhanden
//STRIP001  GetCurFld();
//STRIP001 }
//STRIP001
//STRIP001
//STRIP001 SwFldMgr::~SwFldMgr()
//STRIP001 {
//STRIP001  aSubLst.DeleteAndDestroy(0, aSubLst.Count());
//STRIP001 }
//STRIP001
//STRIP001 /*--------------------------------------------------------------------
//STRIP001  Beschreibung: RefMark ueber Namen organisieren
//STRIP001  --------------------------------------------------------------------*/
//STRIP001
//STRIP001 BOOL  SwFldMgr::CanInsertRefMark( const String& rStr )
//STRIP001 {
//STRIP001  SwWrtShell &rSh = pWrtShell ? *pWrtShell : *lcl_GetShell();
//STRIP001  USHORT nCnt = rSh.GetCrsrCnt();
//STRIP001
//STRIP001  // der letzte Crsr muss keine aufgespannte Selektion
//STRIP001  if( 1 < nCnt && !rSh.SwCrsrShell::HasSelection() )
//STRIP001      --nCnt;
//STRIP001
//STRIP001  return 2 > nCnt && 0 == rSh.GetRefMark( rStr );
//STRIP001 }
//STRIP001
//STRIP001 /*--------------------------------------------------------------------
//STRIP001  Beschreibung: Alle DBTypes loeschen
//STRIP001  --------------------------------------------------------------------*/
//STRIP001
//STRIP001 void SwFldMgr::RemoveDBTypes()
//STRIP001 {
//STRIP001  SwWrtShell &rSh = pWrtShell ? *pWrtShell : *lcl_GetShell();
//STRIP001  USHORT nCount = rSh.GetFldTypeCount(RES_DBFLD);
//STRIP001  for ( USHORT i=0; i < nCount ; ++i )
//STRIP001  {
//STRIP001      SwFieldType* pType = rSh.GetFldType( i, RES_DBFLD );
//STRIP001      if( !pType->GetDepends() )
//STRIP001      {
//STRIP001          rSh.RemoveFldType( i--, RES_DBFLD );
//STRIP001          nCount--;
//STRIP001      }
//STRIP001  }
//STRIP001 }
//STRIP001
//STRIP001 /*--------------------------------------------------------------------
//STRIP001  Beschreibung: Zugriff ueber ResIds
//STRIP001  --------------------------------------------------------------------*/
//STRIP001
//STRIP001 USHORT SwFldMgr::GetFldTypeCount(USHORT nResId) const
//STRIP001 {
//STRIP001  return pWrtShell ?
//STRIP001          pWrtShell->GetFldTypeCount(nResId) :
//STRIP001              ::lcl_GetShell()->GetFldTypeCount(nResId);
//STRIP001 }
//STRIP001
//STRIP001
//STRIP001 SwFieldType* SwFldMgr::GetFldType(USHORT nResId, USHORT nId) const
//STRIP001 {
//STRIP001  return pWrtShell ?
//STRIP001          pWrtShell->GetFldType(nId, nResId) :
//STRIP001              ::lcl_GetShell()->GetFldType(nId, nResId);
//STRIP001 }
//STRIP001
//STRIP001
//STRIP001 SwFieldType* SwFldMgr::GetFldType(USHORT nResId, const String& rName) const
//STRIP001 {
//STRIP001  return pWrtShell ?
//STRIP001          pWrtShell->GetFldType(nResId, rName) :
//STRIP001              ::lcl_GetShell()->GetFldType(nResId, rName);
//STRIP001 }
//STRIP001
//STRIP001
//STRIP001 void SwFldMgr::RemoveFldType(USHORT nResId, USHORT nId)
//STRIP001 {
//STRIP001  pWrtShell ?
//STRIP001          pWrtShell->RemoveFldType(nId, nResId) :
//STRIP001              ::lcl_GetShell()->RemoveFldType(nId, nResId);
//STRIP001 }
//STRIP001
//STRIP001
//STRIP001 void SwFldMgr::RemoveFldType(USHORT nResId, const String& rName )
//STRIP001 {
//STRIP001  pWrtShell ?
//STRIP001          pWrtShell->RemoveFldType(nResId, rName) :
//STRIP001              ::lcl_GetShell()->RemoveFldType(nResId, rName);
//STRIP001 }
//STRIP001
//STRIP001 /*--------------------------------------------------------------------
//STRIP001  Beschreibung: Aktuelles Feld ermitteln
//STRIP001  --------------------------------------------------------------------*/
//STRIP001
//STRIP001
//STRIP001 SwField* SwFldMgr::GetCurFld()
//STRIP001 {
//STRIP001  SwWrtShell *pSh = pWrtShell ? pWrtShell : ::lcl_GetShell();
//STRIP001  if ( pSh )
//STRIP001      pCurFld = pSh->GetCurFld();
//STRIP001  else
//STRIP001      pCurFld = NULL;
//STRIP001
//STRIP001  // Strings und Format initialisieren
//STRIP001  //
//STRIP001  aCurPar1.Erase();
//STRIP001  aCurPar2.Erase();
//STRIP001  sCurFrame.Erase();
//STRIP001  nCurFmt = 0;
//STRIP001
//STRIP001  if(!pCurFld)
//STRIP001      return 0;
//STRIP001
//STRIP001  // Aktuelle Werte aufbereiten Parameter 1 und Parameter 2
//STRIP001  // als auch das Format ermitteln
//STRIP001  //
//STRIP001  const USHORT nTypeId = pCurFld->GetTypeId();
//STRIP001
//STRIP001  nCurFmt     = pCurFld->GetFormat();
//STRIP001  aCurPar1    = pCurFld->GetPar1();
//STRIP001  aCurPar2    = pCurFld->GetPar2();
//STRIP001
//STRIP001  switch( nTypeId )
//STRIP001  {
//STRIP001      case TYP_PAGENUMBERFLD:
//STRIP001      case TYP_NEXTPAGEFLD:
//STRIP001      case TYP_PREVPAGEFLD:
//STRIP001      case TYP_GETREFPAGEFLD:
//STRIP001          if( nCurFmt == SVX_NUM_PAGEDESC )
//STRIP001              nCurFmt -= 2;
//STRIP001          break;
//STRIP001  }
//STRIP001  return pCurFld;
//STRIP001 }
//STRIP001
//STRIP001 /*--------------------------------------------------------------------
//STRIP001  Beschreibung: Gruppen-Bereich liefern
//STRIP001  --------------------------------------------------------------------*/
//STRIP001
//STRIP001
//STRIP001 const SwFldGroupRgn& SwFldMgr::GetGroupRange(BOOL bHtmlMode, USHORT nGrpId) const
//STRIP001 {
//STRIP001 static SwFldGroupRgn __READONLY_DATA aRanges[] =
//STRIP001 {
//STRIP001  /* Dokument     */  GRP_DOC_BEGIN,  GRP_DOC_END,
//STRIP001  /* Funktionen   */  GRP_FKT_BEGIN,  GRP_FKT_END,
//STRIP001  /* Referenzen   */  GRP_REF_BEGIN,  GRP_REF_END,
//STRIP001  /* Ablage       */  GRP_REG_BEGIN,  GRP_REG_END,
//STRIP001  /* DB           */  GRP_DB_BEGIN,   GRP_DB_END,
//STRIP001  /* User         */  GRP_VAR_BEGIN,  GRP_VAR_END,
//STRIP001 };
//STRIP001 static SwFldGroupRgn __READONLY_DATA aWebRanges[] =
//STRIP001 {
//STRIP001  /* Dokument     */  GRP_WEB_DOC_BEGIN,  GRP_WEB_DOC_END,
//STRIP001  /* Funktionen   */  GRP_WEB_FKT_BEGIN,  GRP_WEB_FKT_END,
//STRIP001  /* Referenzen   */  GRP_WEB_REF_BEGIN,  GRP_WEB_REF_END,
//STRIP001  /* Ablage       */  GRP_WEB_REG_BEGIN,  GRP_WEB_REG_END,
//STRIP001  /* DB           */  GRP_WEB_DB_BEGIN,   GRP_WEB_DB_END,
//STRIP001  /* User         */  GRP_WEB_VAR_BEGIN,  GRP_WEB_VAR_END,
//STRIP001 };
//STRIP001
//STRIP001  if (bHtmlMode)
//STRIP001      return aWebRanges[(USHORT)nGrpId];
//STRIP001  else
//STRIP001      return aRanges[(USHORT)nGrpId];
//STRIP001 }
//STRIP001
//STRIP001 /*--------------------------------------------------------------------
//STRIP001  Beschreibung: GroupId bestimmen
//STRIP001  --------------------------------------------------------------------*/
//STRIP001
//STRIP001 USHORT SwFldMgr::GetGroup(BOOL bHtmlMode, USHORT nTypeId, USHORT nSubType) const
//STRIP001 {
//STRIP001  if (nTypeId == TYP_SETINPFLD)
//STRIP001      nTypeId = TYP_SETFLD;
//STRIP001
//STRIP001  if (nTypeId == TYP_INPUTFLD && (nSubType & INP_USR))
//STRIP001      nTypeId = TYP_USERFLD;
//STRIP001
//STRIP001  if (nTypeId == TYP_FIXDATEFLD)
//STRIP001      nTypeId = TYP_DATEFLD;
//STRIP001
//STRIP001  if (nTypeId == TYP_FIXTIMEFLD)
//STRIP001      nTypeId = TYP_TIMEFLD;
//STRIP001
//STRIP001  for (USHORT i = GRP_DOC; i <= GRP_VAR; i++)
//STRIP001  {
//STRIP001      const SwFldGroupRgn& rRange = GetGroupRange(bHtmlMode, i);
//STRIP001      for (USHORT nPos = rRange.nStart; nPos < rRange.nEnd; nPos++)
//STRIP001      {
//STRIP001          if (aSwFlds[nPos].nTypeId == nTypeId)
//STRIP001              return i;
//STRIP001      }
//STRIP001  }
//STRIP001  return USHRT_MAX;
//STRIP001 }
//STRIP001
//STRIP001 /*--------------------------------------------------------------------
//STRIP001  Beschreibung: Namen zur TypeId ermitteln
//STRIP001                ZUGRIFF ueber TYP_....
//STRIP001  --------------------------------------------------------------------*/
//STRIP001
//STRIP001
//STRIP001 USHORT SwFldMgr::GetTypeId(USHORT nPos) const
//STRIP001 {
//STRIP001  ASSERT(nPos < ::GetPackCount(), "unzulaessige Pos");
//STRIP001  return aSwFlds[ nPos ].nTypeId;
//STRIP001 }
//STRIP001
//STRIP001
//STRIP001 const String& SwFldMgr::GetTypeStr(USHORT nPos) const
//STRIP001 {
//STRIP001  ASSERT(nPos < ::GetPackCount(), "unzulaessige TypeId");
//STRIP001
//STRIP001  USHORT nFldWh = aSwFlds[ nPos ].nTypeId;
//STRIP001
//STRIP001  // Sonderbehandlung fuer Datum/Zeit Felder (ohne var/fix)
//STRIP001  if( TYP_DATEFLD == nFldWh )
//STRIP001  {
//STRIP001      if( !pDate )
//STRIP001          pDate = new SW_RESSTR( STR_DATEFLD );
//STRIP001      return *pDate;
//STRIP001  }
//STRIP001  if( TYP_TIMEFLD == nFldWh )
//STRIP001  {
//STRIP001      if( !pTime )
//STRIP001          pTime = new SW_RESSTR( STR_TIMEFLD );
//STRIP001      return *pTime;
//STRIP001  }
//STRIP001
//STRIP001  return *SwFieldType::GetFldNames()->GetObject( nFldWh );
//STRIP001 }
//STRIP001
//STRIP001 /*--------------------------------------------------------------------
//STRIP001  Beschreibung: Pos in der Liste bestimmen
//STRIP001  --------------------------------------------------------------------*/
//STRIP001
//STRIP001
//STRIP001 USHORT SwFldMgr::GetPos(USHORT nTypeId) const
//STRIP001 {
//STRIP001  switch( nTypeId )
//STRIP001  {
//STRIP001      case TYP_FIXDATEFLD:        nTypeId = TYP_DATEFLD;      break;
//STRIP001      case TYP_FIXTIMEFLD:        nTypeId = TYP_TIMEFLD;      break;
//STRIP001      case TYP_SETINPFLD:         nTypeId = TYP_SETFLD;       break;
//STRIP001      case TYP_USRINPFLD:         nTypeId = TYP_USERFLD;      break;
//STRIP001  }
//STRIP001
//STRIP001  for(USHORT i = 0; i < GetPackCount(); i++)
//STRIP001      if(aSwFlds[i].nTypeId == nTypeId)
//STRIP001          return i;
//STRIP001
//STRIP001  return USHRT_MAX;
//STRIP001 }
//STRIP001
//STRIP001 /*--------------------------------------------------------------------
//STRIP001  Beschreibung: Subtypen eines Feldes lokalisieren
//STRIP001  --------------------------------------------------------------------*/
//STRIP001
//STRIP001 SvStringsDtor& SwFldMgr::GetSubTypes(USHORT nTypeId)
//STRIP001 {
//STRIP001  // aSubLst.DeleteAndDestroy(0, aSubLst.Count());
//STRIP001  for (USHORT i=0; i < aSubLst.Count();  )
//STRIP001  {
//STRIP001      String* pStr = aSubLst[i];
//STRIP001      DELETEZ(pStr);
//STRIP001      aSubLst.Remove(i);
//STRIP001  }
//STRIP001
//STRIP001  const USHORT nPos = GetPos(nTypeId);
//STRIP001
//STRIP001  switch(nTypeId)
//STRIP001  {
//STRIP001      case TYP_SETREFFLD:
//STRIP001      case TYP_GETREFFLD:
//STRIP001      {
//STRIP001          // Referenzen sind keine Felder
//STRIP001          pWrtShell ?
//STRIP001              pWrtShell->GetRefMarks( &aSubLst ) :
//STRIP001                  ::lcl_GetShell()->GetRefMarks( &aSubLst );
//STRIP001          break;
//STRIP001      }
//STRIP001      case TYP_MACROFLD:
//STRIP001      {
//STRIP001          if (sMacroPath.Len())
//STRIP001          {
//STRIP001              String sPath = sMacroPath.Copy(sMacroPath.Search('.', 0));
//STRIP001              if (pModule)
//STRIP001              {
//STRIP001                  SbxArray* pSbxArray = pModule->GetMethods();
//STRIP001
//STRIP001                  for (USHORT nMethod = 0; nMethod < pSbxArray->Count(); nMethod++)
//STRIP001                  {
//STRIP001                      SbMethod* pMethod = (SbMethod*)pSbxArray->Get(nMethod);
//STRIP001                      DBG_ASSERT( pMethod, "Methode nicht gefunden! (NULL)" );
//STRIP001
//STRIP001                      String* pNew = new String(pMethod->GetName());
//STRIP001                      *pNew += sPath;
//STRIP001                      aSubLst.Insert(pNew, aSubLst.Count());
//STRIP001                  }
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  String* pNew = new String(sMacroPath);
//STRIP001                  aSubLst.Insert(pNew, aSubLst.Count());
//STRIP001              }
//STRIP001          }
//STRIP001          break;
//STRIP001      }
//STRIP001      case TYP_INPUTFLD:
//STRIP001      {   String* pNew = new SW_RESSTR(aSwFlds[nPos].nSubTypeStart);
//STRIP001          aSubLst.Insert(pNew, aSubLst.Count());
//STRIP001          // Weiter bei generischen Typen
//STRIP001      }
//STRIP001      case TYP_DDEFLD:
//STRIP001      case TYP_SEQFLD:
//STRIP001      case TYP_FORMELFLD:
//STRIP001      case TYP_GETFLD:
//STRIP001      case TYP_SETFLD:
//STRIP001      case TYP_USERFLD:
//STRIP001      {
//STRIP001          SwWrtShell &rSh = pWrtShell ? *pWrtShell : *::lcl_GetShell();
//STRIP001          const USHORT nCount = rSh.GetFldTypeCount();
//STRIP001          for(USHORT i = 0; i < nCount; ++i)
//STRIP001          {
//STRIP001              SwFieldType* pFldType = rSh.GetFldType( i );
//STRIP001              const USHORT nWhich = pFldType->Which();
//STRIP001
//STRIP001              if((nTypeId == TYP_DDEFLD && pFldType->Which() == RES_DDEFLD) ||
//STRIP001
//STRIP001                 (nTypeId == TYP_USERFLD && nWhich == RES_USERFLD) ||
//STRIP001
//STRIP001                 (nTypeId == TYP_GETFLD && nWhich == RES_SETEXPFLD &&
//STRIP001                  !(((SwSetExpFieldType*)pFldType)->GetType() & GSE_SEQ)) ||
//STRIP001
//STRIP001                 (nTypeId == TYP_SETFLD && nWhich == RES_SETEXPFLD &&
//STRIP001                  !(((SwSetExpFieldType*)pFldType)->GetType() & GSE_SEQ)) ||
//STRIP001
//STRIP001                 (nTypeId == TYP_SEQFLD && nWhich == RES_SETEXPFLD  &&
//STRIP001                 (((SwSetExpFieldType*)pFldType)->GetType() & GSE_SEQ)) ||
//STRIP001
//STRIP001                 ((nTypeId == TYP_INPUTFLD  || nTypeId == TYP_FORMELFLD) &&
//STRIP001                   (nWhich == RES_USERFLD ||
//STRIP001                    nWhich == RES_SETEXPFLD &&
//STRIP001                    !(((SwSetExpFieldType*)pFldType)->GetType() & GSE_SEQ)) ) )
//STRIP001              {
//STRIP001                  String* pNew = new String(pFldType->GetName());
//STRIP001                  aSubLst.Insert(pNew, aSubLst.Count());
//STRIP001              }
//STRIP001          }
//STRIP001          break;
//STRIP001      }
//STRIP001      case TYP_DBNEXTSETFLD:
//STRIP001      case TYP_DBNUMSETFLD:
//STRIP001      case TYP_DBNAMEFLD:
//STRIP001      case TYP_DBSETNUMBERFLD:
//STRIP001          break;
//STRIP001
//STRIP001      default:
//STRIP001      {
//STRIP001          // statische SubTypes
//STRIP001          if(nPos != USHRT_MAX)
//STRIP001          {
//STRIP001              USHORT nCount;
//STRIP001              if (nTypeId == TYP_DOCINFOFLD)
//STRIP001                  nCount = DI_SUBTYPE_END - DI_SUBTYPE_BEGIN;
//STRIP001              else
//STRIP001                  nCount = aSwFlds[nPos].nSubTypeEnd - aSwFlds[nPos].nSubTypeStart;
//STRIP001
//STRIP001              SwWrtShell &rSh = pWrtShell ? *pWrtShell : *::lcl_GetShell();
//STRIP001              for(USHORT i = 0; i < nCount; ++i)
//STRIP001              {
//STRIP001                  String* pNew;
//STRIP001                  if (nTypeId == TYP_DOCINFOFLD)
//STRIP001                  {
//STRIP001                      if (i >= DI_INFO1 && i <= DI_INFO4)
//STRIP001                          pNew = new String( rSh.GetInfo()->GetUserKey(i-DI_INFO1).GetTitle());
//STRIP001                      else
//STRIP001                          pNew = new String(*ViewShell::GetShellRes()->aDocInfoLst[i]);
//STRIP001                  }
//STRIP001                  else
//STRIP001                      pNew = new SW_RESSTR(aSwFlds[nPos].nSubTypeStart + i);
//STRIP001
//STRIP001                  aSubLst.Insert(pNew, aSubLst.Count());
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  return aSubLst;
//STRIP001 }
//STRIP001
//STRIP001 /*--------------------------------------------------------------------
//STRIP001  Beschreibung: Format ermitteln
//STRIP001                ZUGRIFF ueber TYP_....
//STRIP001  --------------------------------------------------------------------*/
//STRIP001
//STRIP001
//STRIP001 USHORT SwFldMgr::GetFormatCount(USHORT nTypeId, BOOL bIsText, BOOL bHtmlMode) const
//STRIP001 {
//STRIP001  ASSERT(nTypeId < TYP_END, "unzulaessige TypeId");
//STRIP001
//STRIP001  {
//STRIP001      const USHORT nPos = GetPos(nTypeId);
//STRIP001
//STRIP001      if(nPos == USHRT_MAX || (bHtmlMode && nTypeId == TYP_SETFLD))
//STRIP001          return 0;
//STRIP001
//STRIP001      ULONG nStart = aSwFlds[nPos].nFmtBegin;
//STRIP001      ULONG nEnd   = aSwFlds[nPos].nFmtEnd;
//STRIP001
//STRIP001      if (bIsText && nEnd - nStart >= 2)
//STRIP001          return 2;
//STRIP001
//STRIP001      if (nTypeId == TYP_FILENAMEFLD)
//STRIP001          nEnd -= 2;  // Kein Bereich oder Vorlage
//STRIP001
//STRIP001      switch(nStart)
//STRIP001      {
//STRIP001          case FMT_GETVAR_BEGIN:
//STRIP001          case FMT_SETVAR_BEGIN:  return VF_COUNT;
//STRIP001          case FMT_USERVAR_BEGIN: return VF_USR_COUNT;
//STRIP001          case FMT_DBFLD_BEGIN:   return VF_DB_COUNT;
//STRIP001          case FMT_NUM_BEGIN:
//STRIP001          {
//STRIP001              USHORT nCount = (USHORT)(nEnd - nStart);
//STRIP001              GetNumberingInfo();
//STRIP001                 SvtLanguageOptions aLangOpt;
//STRIP001                 if(xNumberingInfo.is() &&
//STRIP001                     (aLangOpt.IsCJKFontEnabled()||aLangOpt.IsCTLFontEnabled()))
//STRIP001              {
//STRIP001                  Sequence<sal_Int16> aTypes = xNumberingInfo->getSupportedNumberingTypes();
//STRIP001                  const sal_Int16* pTypes = aTypes.getConstArray();
//STRIP001                  for(sal_Int32 nType = 0; nType < aTypes.getLength(); nType++)
//STRIP001                  {
//STRIP001                      sal_Int16 nCurrent = pTypes[nType];
//STRIP001                      //skip all values below or equal to CHARS_LOWER_LETTER_N
//STRIP001                      if(nCurrent > NumberingType::CHARS_LOWER_LETTER_N)
//STRIP001                      {
//STRIP001                          nCount += aTypes.getLength() - nType;
//STRIP001                          break;
//STRIP001                      }
//STRIP001                  }
//STRIP001              }
//STRIP001              return nCount;
//STRIP001          }
//STRIP001
//STRIP001      }
//STRIP001      return (USHORT)(nEnd - nStart);
//STRIP001  }
//STRIP001 }
//STRIP001
//STRIP001 /*--------------------------------------------------------------------
//STRIP001  Beschreibung:   FormatString zu einem Typ ermitteln
//STRIP001  --------------------------------------------------------------------*/
//STRIP001
//STRIP001
//STRIP001 String SwFldMgr::GetFormatStr(USHORT nTypeId, ULONG nFormatId) const
//STRIP001 {
//STRIP001  String aRet;
//STRIP001  SwWrtShell *pSh = pWrtShell ? pWrtShell : ::lcl_GetShell();
//STRIP001  ASSERT(nTypeId < TYP_END, "unzulaessige TypeId");
//STRIP001
//STRIP001  const USHORT nPos = GetPos(nTypeId);
//STRIP001
//STRIP001  if(nPos == USHRT_MAX)
//STRIP001      return aRet;
//STRIP001
//STRIP001  ULONG nStart;
//STRIP001
//STRIP001  nStart = aSwFlds[nPos].nFmtBegin;
//STRIP001
//STRIP001  if (TYP_AUTHORFLD == nTypeId|| TYP_FILENAMEFLD == nTypeId)
//STRIP001      nFormatId &= ~FF_FIXED;     // Fixed-Flag ausmaskieren
//STRIP001
//STRIP001  if((nStart + nFormatId) < aSwFlds[nPos].nFmtEnd)
//STRIP001      aRet = SW_RESSTR((USHORT)(nStart + nFormatId));
//STRIP001  else if( FMT_NUM_BEGIN == nStart)
//STRIP001  {
//STRIP001      if(xNumberingInfo.is())
//STRIP001      {
//STRIP001          Sequence<sal_Int16> aTypes = xNumberingInfo->getSupportedNumberingTypes();
//STRIP001          const sal_Int16* pTypes = aTypes.getConstArray();
//STRIP001          for(sal_Int32 nType = 0; nType < aTypes.getLength(); nType++)
//STRIP001          {
//STRIP001              sal_Int16 nCurrent = pTypes[nType];
//STRIP001              if(nCurrent > NumberingType::CHARS_LOWER_LETTER_N)
//STRIP001              {
//STRIP001                  sal_Int32 nOffset = nFormatId - (aSwFlds[nPos].nFmtEnd - nStart);
//STRIP001                  if(aTypes.getLength() > (nOffset + nType))
//STRIP001                      aRet = xNumberingInfo->getNumberingIdentifier( pTypes[nOffset + nType] );
//STRIP001                  break;
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  return aRet;
//STRIP001 }
//STRIP001
//STRIP001 /*--------------------------------------------------------------------
//STRIP001  Beschreibung:   FormatId aus Pseudo-ID ermitteln
//STRIP001  --------------------------------------------------------------------*/
//STRIP001
//STRIP001 USHORT SwFldMgr::GetFormatId(USHORT nTypeId, ULONG nFormatId) const
//STRIP001 {
//STRIP001  USHORT nId = (USHORT)nFormatId;
//STRIP001
//STRIP001  switch( nTypeId )
//STRIP001  {
//STRIP001  case TYP_DOCINFOFLD:
//STRIP001      switch( aSwFlds[ GetPos( nTypeId ) ].nFmtBegin + nFormatId )
//STRIP001      {
//STRIP001      case FMT_REG_AUTHOR:    nId = DI_SUB_AUTHOR;    break;
//STRIP001      case FMT_REG_TIME:      nId = DI_SUB_TIME;      break;
//STRIP001      case FMT_REG_DATE:      nId = DI_SUB_DATE;      break;
//STRIP001      }
//STRIP001      break;
//STRIP001
//STRIP001  case TYP_PAGENUMBERFLD:
//STRIP001  case TYP_NEXTPAGEFLD:
//STRIP001  case TYP_PREVPAGEFLD:
//STRIP001  case TYP_DOCSTATFLD:
//STRIP001  case TYP_DBSETNUMBERFLD:
//STRIP001  case TYP_SEQFLD:
//STRIP001  case TYP_GETREFPAGEFLD:
//STRIP001  {
//STRIP001      USHORT nPos = GetPos( nTypeId );
//STRIP001      ULONG nBegin = aSwFlds[ nPos ].nFmtBegin;
//STRIP001      ULONG nEnd = aSwFlds[nPos].nFmtEnd;
//STRIP001      if((nBegin + nFormatId) < nEnd)
//STRIP001      {
//STRIP001          switch( nBegin + nFormatId )
//STRIP001          {
//STRIP001          case FMT_NUM_ABC:               nId = SVX_NUM_CHARS_UPPER_LETTER;   break;
//STRIP001          case FMT_NUM_SABC:              nId = SVX_NUM_CHARS_LOWER_LETTER;   break;
//STRIP001          case FMT_NUM_ROMAN:             nId = SVX_NUM_ROMAN_UPPER;          break;
//STRIP001          case FMT_NUM_SROMAN:            nId = SVX_NUM_ROMAN_LOWER;          break;
//STRIP001          case FMT_NUM_ARABIC:            nId = SVX_NUM_ARABIC;               break;
//STRIP001          case FMT_NUM_PAGEDESC:          nId = SVX_NUM_PAGEDESC;             break;
//STRIP001          case FMT_NUM_PAGESPECIAL:       nId = SVX_NUM_CHAR_SPECIAL;         break;
//STRIP001          case FMT_NUM_ABC_N:             nId = SVX_NUM_CHARS_UPPER_LETTER_N; break;
//STRIP001          case FMT_NUM_SABC_N:            nId = SVX_NUM_CHARS_LOWER_LETTER_N; break;
//STRIP001          }
//STRIP001      }
//STRIP001      else if(xNumberingInfo.is())
//STRIP001      {
//STRIP001          Sequence<sal_Int16> aTypes = xNumberingInfo->getSupportedNumberingTypes();
//STRIP001          const sal_Int16* pTypes = aTypes.getConstArray();
//STRIP001          for(sal_Int32 nType = 0; nType < aTypes.getLength(); nType++)
//STRIP001          {
//STRIP001              sal_Int16 nCurrent = pTypes[nType];
//STRIP001              //skip all values below or equal to CHARS_LOWER_LETTER_N
//STRIP001              if(nCurrent > NumberingType::CHARS_LOWER_LETTER_N)
//STRIP001              {
//STRIP001                  sal_Int32 nOffset = nFormatId + nBegin - aSwFlds[nPos].nFmtEnd;
//STRIP001                  if((nOffset + nType) < aTypes.getLength())
//STRIP001                  {
//STRIP001                      nId = pTypes[nOffset + nType];
//STRIP001                      break;
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  break;
//STRIP001  case TYP_DDEFLD:
//STRIP001      switch ( aSwFlds[ GetPos( nTypeId ) ].nFmtBegin + nFormatId )
//STRIP001      {
//STRIP001         case FMT_DDE_NORMAL:    nId = ::so3::LINKUPDATE_ONCALL; break;
//STRIP001         case FMT_DDE_HOT:       nId = ::so3::LINKUPDATE_ALWAYS; break;
//STRIP001      }
//STRIP001      break;
//STRIP001  }
//STRIP001
//STRIP001  return nId;
//STRIP001
//STRIP001 }
//STRIP001
//STRIP001 /*--------------------------------------------------------------------
//STRIP001  Beschreibung: Traveling
//STRIP001  --------------------------------------------------------------------*/
//STRIP001
//STRIP001
//STRIP001 BOOL SwFldMgr::GoNextPrev( BOOL bNext, SwFieldType* pTyp )
//STRIP001 {
//STRIP001  SwWrtShell* pSh = pWrtShell ? pWrtShell : ::lcl_GetShell();
//STRIP001
//STRIP001  if( !pTyp && pCurFld )
//STRIP001  {
//STRIP001      const USHORT nTypeId = pCurFld->GetTypeId();
//STRIP001      if( TYP_SETINPFLD == nTypeId || TYP_USRINPFLD == nTypeId )
//STRIP001          pTyp = pSh->GetFldType( 0, RES_INPUTFLD );
//STRIP001      else
//STRIP001          pTyp = pCurFld->GetTyp();
//STRIP001  }
//STRIP001
//STRIP001  if (pTyp && pTyp->Which() == RES_DBFLD)
//STRIP001  {
//STRIP001      // Fuer Feldbefehl-bearbeiten (alle DB-Felder anspringen)
//STRIP001      return pSh->MoveFldType( 0, bNext, USHRT_MAX, RES_DBFLD );
//STRIP001  }
//STRIP001
//STRIP001  return pTyp && pSh ? pSh->MoveFldType( pTyp, bNext ) : FALSE;
//STRIP001 }
//STRIP001
//STRIP001 /*--------------------------------------------------------------------
//STRIP001  Beschreibung: Feldtypen einfuegen
//STRIP001  --------------------------------------------------------------------*/
//STRIP001
//STRIP001
//STRIP001 void SwFldMgr::InsertFldType(SwFieldType& rType)
//STRIP001 {
//STRIP001  pWrtShell ?
//STRIP001          pWrtShell->InsertFldType(rType) :
//STRIP001              ::lcl_GetShell()->InsertFldType(rType);
//STRIP001 }
//STRIP001
//STRIP001 /*--------------------------------------------------------------------
//STRIP001  Beschreibung: Aktuelle TypeId ermitteln
//STRIP001  --------------------------------------------------------------------*/
//STRIP001
//STRIP001
//STRIP001 USHORT SwFldMgr::GetCurTypeId() const
//STRIP001 {
//STRIP001  return pCurFld->GetTypeId();
//STRIP001 }
//STRIP001
//STRIP001 /*--------------------------------------------------------------------
//STRIP001  Beschreibung: Ueber String  Feld einfuegen oder Update
//STRIP001  --------------------------------------------------------------------*/
//STRIP001
//STRIP001
//STRIP001 BOOL SwFldMgr::InsertFld(  const SwInsertFld_Data& rData )
//STRIP001 {
//STRIP001     SwField* pFld   = 0;
//STRIP001  BOOL bExp = FALSE;
//STRIP001  BOOL bTbl = FALSE;
//STRIP001  BOOL bPageVar = FALSE;
//STRIP001     ULONG nFormatId = rData.nFormatId;
//STRIP001     USHORT nSubType = rData.nSubType;
//STRIP001     sal_Unicode cSeparator = rData.cSeparator;
//STRIP001     SwWrtShell* pCurShell = rData.pSh;
//STRIP001     if(!pCurShell)
//STRIP001         pCurShell = pWrtShell ? pWrtShell : ::lcl_GetShell();
//STRIP001
//STRIP001     switch(rData.nTypeId)
//STRIP001  {   // ACHTUNG dieses Feld wird ueber einen gesonderten Dialog eingefuegt
//STRIP001      case TYP_POSTITFLD:
//STRIP001      {
//STRIP001          SwPostItFieldType* pType =
//STRIP001                 (SwPostItFieldType*)pCurShell->GetFldType(0, RES_POSTITFLD);
//STRIP001             pFld = new SwPostItField(pType, rData.sPar1, rData.sPar2, Date());
//STRIP001          break;
//STRIP001      }
//STRIP001      case TYP_SCRIPTFLD:
//STRIP001      {
//STRIP001          SwScriptFieldType* pType =
//STRIP001                 (SwScriptFieldType*)pCurShell->GetFldType(0, RES_SCRIPTFLD);
//STRIP001             pFld = new SwScriptField(pType, rData.sPar1, rData.sPar2, (BOOL)nFormatId);
//STRIP001          break;
//STRIP001      }
//STRIP001      case TYP_COMBINED_CHARS:
//STRIP001      {
//STRIP001          SwCombinedCharFieldType* pType = (SwCombinedCharFieldType*)
//STRIP001                                 pCurShell->GetFldType( 0, RES_COMBINED_CHARS );
//STRIP001             pFld = new SwCombinedCharField( pType, rData.sPar1 );
//STRIP001      }
//STRIP001      break;
//STRIP001      case TYP_AUTHORITY:
//STRIP001      {
//STRIP001          SwAuthorityFieldType* pType =
//STRIP001                 (SwAuthorityFieldType*)pCurShell->GetFldType(0, RES_AUTHORITY);
//STRIP001          if(!pType)
//STRIP001          {
//STRIP001              pType =
//STRIP001                     (SwAuthorityFieldType*)pCurShell->InsertFldType(
//STRIP001                                     SwAuthorityFieldType(pCurShell->GetDoc()));
//STRIP001          }
//STRIP001             pFld = new SwAuthorityField(pType, rData.sPar1);
//STRIP001      }
//STRIP001      break;
//STRIP001      case TYP_DATEFLD:
//STRIP001      case TYP_TIMEFLD:
//STRIP001      {
//STRIP001             USHORT nSub = (rData.nTypeId == TYP_DATEFLD) ? DATEFLD : TIMEFLD;
//STRIP001             nSub |= nSubType == DATE_VAR ? 0 : FIXEDFLD;
//STRIP001
//STRIP001          SwDateTimeFieldType* pTyp =
//STRIP001                 (SwDateTimeFieldType*)pCurShell->GetFldType(0, RES_DATETIMEFLD);
//STRIP001             pFld = new SwDateTimeField(pTyp, nSub, nFormatId);
//STRIP001             pFld->SetPar2(rData.sPar2);
//STRIP001          break;
//STRIP001      }
//STRIP001      case TYP_FILENAMEFLD:
//STRIP001      {
//STRIP001          SwFileNameFieldType* pTyp =
//STRIP001                 (SwFileNameFieldType*)pCurShell->GetFldType(0, RES_FILENAMEFLD);
//STRIP001             pFld = new SwFileNameField(pTyp, nFormatId);
//STRIP001          break;
//STRIP001      }
//STRIP001      case TYP_TEMPLNAMEFLD:
//STRIP001      {
//STRIP001          SwTemplNameFieldType* pTyp =
//STRIP001                 (SwTemplNameFieldType*)pCurShell->GetFldType(0, RES_TEMPLNAMEFLD);
//STRIP001             pFld = new SwTemplNameField(pTyp, nFormatId);
//STRIP001          break;
//STRIP001      }
//STRIP001      case TYP_CHAPTERFLD:
//STRIP001         {
//STRIP001             USHORT nByte = (USHORT)rData.sPar2.ToInt32();
//STRIP001          SwChapterFieldType* pTyp =
//STRIP001                 (SwChapterFieldType*)pCurShell->GetFldType(0, RES_CHAPTERFLD);
//STRIP001             pFld = new SwChapterField(pTyp, nFormatId);
//STRIP001          nByte = Max(USHORT(1), nByte);
//STRIP001          nByte = Min(nByte, USHORT(MAXLEVEL));
//STRIP001          nByte -= 1;
//STRIP001          ((SwChapterField*)pFld)->SetLevel((BYTE)nByte);
//STRIP001          break;
//STRIP001      }
//STRIP001      case TYP_NEXTPAGEFLD:
//STRIP001      case TYP_PREVPAGEFLD:
//STRIP001      case TYP_PAGENUMBERFLD:
//STRIP001      {
//STRIP001             short nOff  = (short)rData.sPar2.ToInt32();
//STRIP001
//STRIP001             if(rData.nTypeId == TYP_NEXTPAGEFLD)
//STRIP001          {
//STRIP001                 if( SVX_NUM_CHAR_SPECIAL == nFormatId )
//STRIP001                  nOff = 1;
//STRIP001              else
//STRIP001                  nOff += 1;
//STRIP001                 nSubType = PG_NEXT;
//STRIP001          }
//STRIP001             else if(rData.nTypeId == TYP_PREVPAGEFLD)
//STRIP001          {
//STRIP001                 if( SVX_NUM_CHAR_SPECIAL == nFormatId )
//STRIP001                  nOff = -1;
//STRIP001              else
//STRIP001                  nOff -= 1;
//STRIP001                 nSubType =  PG_PREV;
//STRIP001          }
//STRIP001          else
//STRIP001                 nSubType = PG_RANDOM;
//STRIP001
//STRIP001          SwPageNumberFieldType* pTyp =
//STRIP001                 (SwPageNumberFieldType*)pCurShell->GetFldType(0, RES_PAGENUMBERFLD);
//STRIP001             pFld = new SwPageNumberField(pTyp, nSubType, nFormatId, nOff);
//STRIP001
//STRIP001             if( SVX_NUM_CHAR_SPECIAL == nFormatId &&
//STRIP001                 ( PG_PREV == nSubType || PG_NEXT == nSubType ) )
//STRIP001                 ((SwPageNumberField*)pFld)->SetUserString( rData.sPar2 );
//STRIP001          break;
//STRIP001      }
//STRIP001      case TYP_DOCSTATFLD:
//STRIP001      {   SwDocStatFieldType* pTyp =
//STRIP001                 (SwDocStatFieldType*)pCurShell->GetFldType(0, RES_DOCSTATFLD);
//STRIP001             pFld = new SwDocStatField(pTyp, nSubType, nFormatId);
//STRIP001          break;
//STRIP001      }
//STRIP001      case TYP_AUTHORFLD:
//STRIP001      {   SwAuthorFieldType* pTyp =
//STRIP001                 (SwAuthorFieldType*)pCurShell->GetFldType(0, RES_AUTHORFLD);
//STRIP001             pFld = new SwAuthorField(pTyp, nFormatId);
//STRIP001          break;
//STRIP001      }
//STRIP001      case TYP_CONDTXTFLD:
//STRIP001      case TYP_HIDDENTXTFLD:
//STRIP001      {
//STRIP001          SwHiddenTxtFieldType* pTyp =
//STRIP001                 (SwHiddenTxtFieldType*)pCurShell->GetFldType(0, RES_HIDDENTXTFLD);
//STRIP001             pFld = new SwHiddenTxtField(pTyp, TRUE, rData.sPar1, rData.sPar2, FALSE, rData.nTypeId);
//STRIP001          bExp = TRUE;
//STRIP001          break;
//STRIP001      }
//STRIP001      case TYP_HIDDENPARAFLD:
//STRIP001      {
//STRIP001          SwHiddenParaFieldType* pTyp =
//STRIP001                 (SwHiddenParaFieldType*)pCurShell->GetFldType(0, RES_HIDDENPARAFLD);
//STRIP001             pFld = new SwHiddenParaField(pTyp, rData.sPar1);
//STRIP001          bExp = TRUE;
//STRIP001          break;
//STRIP001      }
//STRIP001      case TYP_SETREFFLD:
//STRIP001      {
//STRIP001             if( rData.sPar1.Len() > 0 && CanInsertRefMark( rData.sPar1 ) )
//STRIP001          {
//STRIP001                 pCurShell->SetAttr( SwFmtRefMark( rData.sPar1 ) );
//STRIP001              return TRUE;
//STRIP001          }
//STRIP001          return FALSE;
//STRIP001      }
//STRIP001      case TYP_GETREFFLD:
//STRIP001      {
//STRIP001          SwGetRefFieldType* pTyp =
//STRIP001                 (SwGetRefFieldType*)pCurShell->GetFldType(0, RES_GETREFFLD);
//STRIP001             USHORT nSeqNo = (USHORT)rData.sPar2.ToInt32();
//STRIP001             pFld = new SwGetRefField(pTyp, rData.sPar1, nSubType, nSeqNo, nFormatId);
//STRIP001          bExp = TRUE;
//STRIP001          break;
//STRIP001      }
//STRIP001      case TYP_DDEFLD:
//STRIP001      {
//STRIP001          //JP 28.08.95: DDE-Topics/-Items koennen Blanks in ihren
//STRIP001          //              Namen haben! Wird hier noch nicht beachtet.
//STRIP001             String sCmd( rData.sPar2 );
//STRIP001             USHORT nTmpPos = sCmd.SearchAndReplace( ' ', ::so3::cTokenSeperator );
//STRIP001             sCmd.SearchAndReplace( ' ', ::so3::cTokenSeperator, nTmpPos );
//STRIP001
//STRIP001             SwDDEFieldType* pTyp = (SwDDEFieldType*)pCurShell->InsertFldType(
//STRIP001                     SwDDEFieldType( rData.sPar1, sCmd, (USHORT)nFormatId ));
//STRIP001          pFld = new SwDDEField( pTyp );
//STRIP001          break;
//STRIP001      }
//STRIP001      case TYP_MACROFLD:
//STRIP001      {
//STRIP001          SwMacroFieldType* pTyp =
//STRIP001                 (SwMacroFieldType*)pCurShell->GetFldType(0, RES_MACROFLD);
//STRIP001
//STRIP001             pFld = new SwMacroField(pTyp, rData.sPar1, rData.sPar2);
//STRIP001          break;
//STRIP001      }
//STRIP001      case TYP_INTERNETFLD:
//STRIP001      {
//STRIP001             SwFmtINetFmt aFmt( rData.sPar1, sCurFrame );
//STRIP001          if( pMacroItem )
//STRIP001              aFmt.SetMacroTbl( &pMacroItem->GetMacroTable() );
//STRIP001             return pCurShell->InsertURL( aFmt, rData.sPar2 );
//STRIP001      }
//STRIP001      case TYP_JUMPEDITFLD:
//STRIP001      {
//STRIP001          SwJumpEditFieldType* pTyp =
//STRIP001                 (SwJumpEditFieldType*)pCurShell->GetFldType(0, RES_JUMPEDITFLD);
//STRIP001
//STRIP001             pFld = new SwJumpEditField(pTyp, nFormatId, rData.sPar1, rData.sPar2 );
//STRIP001          break;
//STRIP001      }
//STRIP001      case TYP_DOCINFOFLD:
//STRIP001      {
//STRIP001             SwDocInfoFieldType* pTyp = (SwDocInfoFieldType*)pCurShell->GetFldType(
//STRIP001                                          0, RES_DOCINFOFLD );
//STRIP001             pFld = new SwDocInfoField(pTyp, nSubType, nFormatId);
//STRIP001          break;
//STRIP001      }
//STRIP001      case TYP_EXTUSERFLD:
//STRIP001      {
//STRIP001             SwExtUserFieldType* pTyp = (SwExtUserFieldType*)pCurShell->GetFldType(
//STRIP001                                          0, RES_EXTUSERFLD);
//STRIP001             pFld = new SwExtUserField(pTyp, nSubType, nFormatId);
//STRIP001          break;
//STRIP001      }
//STRIP001      case TYP_DBFLD:
//STRIP001      {
//STRIP001          SwDBData aDBData;
//STRIP001          String sPar1;
//STRIP001
//STRIP001             if (rData.sPar1.Search(DB_DELIM) == STRING_NOTFOUND)
//STRIP001          {
//STRIP001                 aDBData = pCurShell->GetDBData();
//STRIP001                 sPar1 = rData.sPar1;
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001                 aDBData.sDataSource = rData.sPar1.GetToken(0, DB_DELIM);
//STRIP001                 aDBData.sCommand = rData.sPar1.GetToken(1, DB_DELIM);
//STRIP001                 aDBData.nCommandType = rData.sPar1.GetToken(2, DB_DELIM).ToInt32();
//STRIP001                 sPar1 = rData.sPar1.GetToken(3, DB_DELIM);
//STRIP001          }
//STRIP001
//STRIP001             if(aDBData.sDataSource.getLength() && pCurShell->GetDBData() != aDBData)
//STRIP001                 pCurShell->ChgDBData(aDBData);
//STRIP001
//STRIP001             SwDBFieldType* pTyp = (SwDBFieldType*)pCurShell->InsertFldType(
//STRIP001                     SwDBFieldType(pCurShell->GetDoc(), sPar1, aDBData) );
//STRIP001          pFld = new SwDBField(pTyp);
//STRIP001             pFld->SetSubType(nSubType);
//STRIP001
//STRIP001             if( !(nSubType & SUB_OWN_FMT) ) // Datenbankformat ermitteln
//STRIP001          {
//STRIP001                 Reference< XDataSource> xSource;
//STRIP001                 rData.aDBDataSource >>= xSource;
//STRIP001                 Reference<XConnection> xConnection;
//STRIP001                 rData.aDBConnection >>= xConnection;
//STRIP001                 Reference<XPropertySet> xColumn;
//STRIP001                 rData.aDBColumn >>= xColumn;
//STRIP001                 if(xColumn.is())
//STRIP001                 {
//STRIP001                     nFormatId = pCurShell->GetNewDBMgr()->GetColumnFmt(xSource, xConnection, xColumn,
//STRIP001                                         pCurShell->GetNumberFormatter(), GetCurrLanguage() );
//STRIP001                 }
//STRIP001                 else
//STRIP001                     nFormatId = pCurShell->GetNewDBMgr()->GetColumnFmt(
//STRIP001                                         aDBData.sDataSource, aDBData.sCommand, sPar1,
//STRIP001                                         pCurShell->GetNumberFormatter(), GetCurrLanguage() );
//STRIP001          }
//STRIP001             pFld->ChangeFormat( nFormatId );
//STRIP001
//STRIP001          bExp = TRUE;
//STRIP001          break;
//STRIP001      }
//STRIP001      case TYP_DBSETNUMBERFLD:
//STRIP001      case TYP_DBNUMSETFLD:
//STRIP001      case TYP_DBNEXTSETFLD:
//STRIP001      case TYP_DBNAMEFLD:
//STRIP001      {
//STRIP001          USHORT nPos, nTablePos, nCmdTypePos, nExpPos;
//STRIP001          String sPar1;
//STRIP001          SwDBData aDBData;
//STRIP001
//STRIP001             // DBName aus rData.sPar1 extrahieren. Format: DBName.TableName.CommandType.ExpStrg
//STRIP001             if ((nTablePos = rData.sPar1.Search(DB_DELIM)) != STRING_NOTFOUND)
//STRIP001                 aDBData.sDataSource = rData.sPar1.Copy(0, nTablePos++);
//STRIP001             if ((nCmdTypePos = rData.sPar1.Search(DB_DELIM, nTablePos)) != STRING_NOTFOUND)
//STRIP001          {
//STRIP001                 aDBData.sCommand = rData.sPar1.Copy(nTablePos, nCmdTypePos++ - nTablePos);
//STRIP001          }
//STRIP001             if ((nExpPos = rData.sPar1.Search(DB_DELIM, nCmdTypePos)) != STRING_NOTFOUND)
//STRIP001          {
//STRIP001                 aDBData.nCommandType = rData.sPar1.Copy(nCmdTypePos, nExpPos++ - nCmdTypePos).ToInt32();
//STRIP001          }
//STRIP001          if (nExpPos != STRING_NOTFOUND)
//STRIP001              nPos = nExpPos;
//STRIP001          else if (nTablePos != STRING_NOTFOUND)
//STRIP001              nPos = nTablePos;
//STRIP001          else
//STRIP001              nPos = 0;
//STRIP001             sPar1 = rData.sPar1.Copy(nPos);
//STRIP001
//STRIP001             if (aDBData.sDataSource.getLength() && pCurShell->GetDBData() != aDBData)
//STRIP001                 pCurShell->ChgDBData(aDBData);
//STRIP001
//STRIP001             switch(rData.nTypeId)
//STRIP001          {
//STRIP001              case TYP_DBNAMEFLD:
//STRIP001              {
//STRIP001                  SwDBNameFieldType* pTyp =
//STRIP001                         (SwDBNameFieldType*)pCurShell->GetFldType(0, RES_DBNAMEFLD);
//STRIP001                  pFld = new SwDBNameField(pTyp, aDBData);
//STRIP001
//STRIP001                  break;
//STRIP001              }
//STRIP001              case TYP_DBNEXTSETFLD:
//STRIP001              {
//STRIP001                     SwDBNextSetFieldType* pTyp = (SwDBNextSetFieldType*)pCurShell->GetFldType(
//STRIP001                                                  0, RES_DBNEXTSETFLD);
//STRIP001                     pFld = new SwDBNextSetField(pTyp, sPar1, rData.sPar2, aDBData);
//STRIP001                  bExp = TRUE;
//STRIP001                  break;
//STRIP001              }
//STRIP001              case TYP_DBNUMSETFLD:
//STRIP001              {
//STRIP001                     SwDBNumSetFieldType* pTyp = (SwDBNumSetFieldType*)pCurShell->GetFldType(
//STRIP001                                                  0, RES_DBNUMSETFLD);
//STRIP001                     pFld = new SwDBNumSetField( pTyp, sPar1, rData.sPar2, aDBData);
//STRIP001                  bExp = TRUE;
//STRIP001                  break;
//STRIP001              }
//STRIP001              case TYP_DBSETNUMBERFLD:
//STRIP001              {
//STRIP001                  SwDBSetNumberFieldType* pTyp = (SwDBSetNumberFieldType*)
//STRIP001                                                 pCurShell->GetFldType(0, RES_DBSETNUMBERFLD);
//STRIP001                     pFld = new SwDBSetNumberField( pTyp, aDBData, nFormatId);
//STRIP001                  bExp = TRUE;
//STRIP001                  break;
//STRIP001              }
//STRIP001          }
//STRIP001          break;
//STRIP001      }
//STRIP001      case TYP_USERFLD:
//STRIP001      {
//STRIP001          SwUserFieldType* pTyp =
//STRIP001                 (SwUserFieldType*)pCurShell->GetFldType(RES_USERFLD, rData.sPar1);
//STRIP001
//STRIP001          // nur wenn vorhanden
//STRIP001          if(!pTyp)
//STRIP001          {
//STRIP001                 pTyp = (SwUserFieldType*)pCurShell->InsertFldType(
//STRIP001                         SwUserFieldType(pCurShell->GetDoc(), rData.sPar1));
//STRIP001          }
//STRIP001             if (pTyp->GetContent(nFormatId) != rData.sPar2)
//STRIP001                 pTyp->SetContent(rData.sPar2, nFormatId);
//STRIP001             pFld = new SwUserField(pTyp, 0, nFormatId);
//STRIP001             if (pFld->GetSubType() != nSubType)
//STRIP001                 pFld->SetSubType(nSubType);
//STRIP001          bTbl = TRUE;
//STRIP001          break;
//STRIP001      }
//STRIP001      case TYP_INPUTFLD:
//STRIP001      {
//STRIP001             if ((nSubType & 0x00ff) == INP_VAR)
//STRIP001          {
//STRIP001              SwSetExpFieldType* pTyp = (SwSetExpFieldType*)
//STRIP001                                     pCurShell->GetFldType(RES_SETEXPFLD, rData.sPar1);
//STRIP001
//STRIP001              // kein Experssion Type mit dem Namen vorhanden -> anlegen
//STRIP001              if(pTyp)
//STRIP001              {
//STRIP001                  SwSetExpField* pExpFld =
//STRIP001                         new SwSetExpField(pTyp, aEmptyStr, nFormatId);
//STRIP001
//STRIP001                  // Typ vom SwSetExpFieldType nicht veraendern:
//STRIP001                  USHORT nOldSubType = pExpFld->GetSubType();
//STRIP001                     pExpFld->SetSubType(nOldSubType | (nSubType & 0xff00));
//STRIP001
//STRIP001                     pExpFld->SetPromptText(rData.sPar2);
//STRIP001                  pExpFld->SetInputFlag(TRUE) ;
//STRIP001                  bExp = TRUE;
//STRIP001                  pFld = pExpFld;
//STRIP001              }
//STRIP001              else
//STRIP001                  return FALSE;
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              SwInputFieldType* pTyp =
//STRIP001                     (SwInputFieldType*)pCurShell->GetFldType(0, RES_INPUTFLD);
//STRIP001
//STRIP001              SwInputField* pInpFld =
//STRIP001                     new SwInputField(pTyp, rData.sPar1, rData.sPar2, nSubType|SUB_INVISIBLE, nFormatId);
//STRIP001              pFld = pInpFld;
//STRIP001          }
//STRIP001
//STRIP001          // Dialog starten
//STRIP001          //
//STRIP001             pCurShell->StartInputFldDlg(pFld, FALSE);
//STRIP001          break;
//STRIP001      }
//STRIP001      case TYP_SETFLD:
//STRIP001      {
//STRIP001             if (!rData.sPar2.Len())   // Leere Variablen sind nicht erlaubt
//STRIP001              return FALSE;
//STRIP001
//STRIP001             SwSetExpFieldType* pTyp = (SwSetExpFieldType*)pCurShell->InsertFldType(
//STRIP001                     SwSetExpFieldType(pCurShell->GetDoc(), rData.sPar1) );
//STRIP001
//STRIP001             SwSetExpField* pExpFld = new SwSetExpField( pTyp, rData.sPar2, nFormatId);
//STRIP001             pExpFld->SetSubType(nSubType);
//STRIP001             pExpFld->SetPar2(rData.sPar2);
//STRIP001          bExp = TRUE;
//STRIP001          pFld = pExpFld;
//STRIP001          break;
//STRIP001      }
//STRIP001      case TYP_SEQFLD:
//STRIP001      {
//STRIP001             SwSetExpFieldType* pTyp = (SwSetExpFieldType*)pCurShell->InsertFldType(
//STRIP001                     SwSetExpFieldType(pCurShell->GetDoc(), rData.sPar1, GSE_SEQ));
//STRIP001
//STRIP001             BYTE nLevel = nSubType & 0xff;
//STRIP001
//STRIP001          pTyp->SetOutlineLvl(nLevel);
//STRIP001             if (nLevel != 0x7f && cSeparator == 0)
//STRIP001                 cSeparator = '.';
//STRIP001
//STRIP001             pTyp->SetDelimiter(cSeparator);
//STRIP001             SwSetExpField* pExpFld = new SwSetExpField(pTyp, rData.sPar2, nFormatId);
//STRIP001          bExp = TRUE;
//STRIP001          pFld = pExpFld;
//STRIP001             nSubType = GSE_SEQ;
//STRIP001          break;
//STRIP001      }
//STRIP001      case TYP_GETFLD:
//STRIP001      {
//STRIP001          // gibt es ein entprechendes SetField
//STRIP001          SwSetExpFieldType* pSetTyp = (SwSetExpFieldType*)
//STRIP001                                     pCurShell->GetFldType(RES_SETEXPFLD, rData.sPar1);
//STRIP001
//STRIP001          if(pSetTyp)
//STRIP001          {
//STRIP001                 SwGetExpFieldType* pTyp = (SwGetExpFieldType*)pCurShell->GetFldType(
//STRIP001                                              0, RES_GETEXPFLD);
//STRIP001                 pFld = new SwGetExpField(pTyp, rData.sPar1, pSetTyp->GetType(), nFormatId);
//STRIP001                 pFld->SetSubType(nSubType | pSetTyp->GetType());
//STRIP001              bExp = TRUE;
//STRIP001          }
//STRIP001          else
//STRIP001              return FALSE;
//STRIP001          break;
//STRIP001      }
//STRIP001      case TYP_FORMELFLD:
//STRIP001      {
//STRIP001             if(pCurShell->GetFrmType(0,FALSE) & FRMTYPE_TABLE)
//STRIP001          {
//STRIP001                 pCurShell->StartAllAction();
//STRIP001
//STRIP001                 SvNumberFormatter* pFormatter = pCurShell->GetDoc()->GetNumberFormatter();
//STRIP001                 const SvNumberformat* pEntry = pFormatter->GetEntry(nFormatId);
//STRIP001
//STRIP001              if (pEntry)
//STRIP001              {
//STRIP001                  SfxStringItem aFormat(FN_NUMBER_FORMAT, pEntry->GetFormatstring());
//STRIP001                     pCurShell->GetView().GetViewFrame()->GetDispatcher()->
//STRIP001                      Execute(FN_NUMBER_FORMAT, SFX_CALLMODE_SYNCHRON, &aFormat, 0L);
//STRIP001              }
//STRIP001
//STRIP001                 SfxItemSet aBoxSet( pCurShell->GetAttrPool(),
//STRIP001                              RES_BOXATR_FORMULA, RES_BOXATR_FORMULA );
//STRIP001
//STRIP001                 String sFml( rData.sPar2 );
//STRIP001              if( sFml.EraseLeadingChars().Len() &&
//STRIP001                  '=' == sFml.GetChar( 0 ) )
//STRIP001                  sFml.Erase( 0, 1 );
//STRIP001
//STRIP001              aBoxSet.Put( SwTblBoxFormula( sFml ));
//STRIP001                 pCurShell->SetTblBoxFormulaAttrs( aBoxSet );
//STRIP001                 pCurShell->UpdateTable();
//STRIP001
//STRIP001                 pCurShell->EndAllAction();
//STRIP001              return TRUE;
//STRIP001
//STRIP001 /*               // In der Tabelle Tabellenformeln einfuegen
//STRIP001                 SwTblFieldType* pTyp = (SwTblFieldType*)pCurShell->GetFldType(
//STRIP001                                                      0, RES_TABLEFLD);
//STRIP001                 pFld = new SwTblField(pTyp, rData.sPar2, GSE_EXPR, nFormatId);
//STRIP001              bTbl = TRUE;*/
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              SwGetExpFieldType* pTyp = (SwGetExpFieldType*)
//STRIP001                                             pCurShell->GetFldType(0, RES_GETEXPFLD);
//STRIP001                 pFld = new SwGetExpField(pTyp, rData.sPar2, GSE_FORMULA, nFormatId);
//STRIP001                 pFld->SetSubType(nSubType);
//STRIP001              bExp = TRUE;
//STRIP001          }
//STRIP001          break;
//STRIP001      }
//STRIP001      case TYP_SETREFPAGEFLD:
//STRIP001          pFld = new SwRefPageSetField( (SwRefPageSetFieldType*)
//STRIP001                                 pCurShell->GetFldType( 0, RES_REFPAGESETFLD ),
//STRIP001                                 (short)rData.sPar2.ToInt32(), 0 != nSubType  );
//STRIP001          bPageVar = TRUE;
//STRIP001          break;
//STRIP001
//STRIP001      case TYP_GETREFPAGEFLD:
//STRIP001          pFld = new SwRefPageGetField( (SwRefPageGetFieldType*)
//STRIP001                             pCurShell->GetFldType( 0, RES_REFPAGEGETFLD ), nFormatId );
//STRIP001          bPageVar = TRUE;
//STRIP001          break;
//STRIP001         case TYP_DROPDOWN :
//STRIP001         {
//STRIP001             pFld = new SwDropDownField(pCurShell->GetFldType( 0, RES_DROPDOWN ));
//STRIP001             xub_StrLen nTokenCount = rData.sPar2.Len() ? rData.sPar2.GetTokenCount(DB_DELIM) : 0;
//STRIP001             Sequence<OUString> aEntries(nTokenCount);
//STRIP001             OUString* pArray = aEntries.getArray();
//STRIP001             for(xub_StrLen nToken = 0; nToken < nTokenCount; nToken++)
//STRIP001                 pArray[nToken] = rData.sPar2.GetToken(nToken, DB_DELIM);
//STRIP001             ((SwDropDownField*)pFld)->SetItems(aEntries);
//STRIP001             ((SwDropDownField*)pFld)->SetName(rData.sPar1);
//STRIP001         }
//STRIP001         break;
//STRIP001      default:
//STRIP001      {   ASSERT(!this, "Falscher Feldtyp");
//STRIP001          return FALSE;
//STRIP001      }
//STRIP001  }
//STRIP001  ASSERT(pFld, "Feld nicht vorhanden");
//STRIP001
//STRIP001
//STRIP001      //the auto language flag has to be set prior to the language!
//STRIP001      pFld->SetAutomaticLanguage(rData.bIsAutomaticLanguage);
//STRIP001      USHORT nLang = GetCurrLanguage();
//STRIP001      pFld->SetLanguage(nLang);
//STRIP001
//STRIP001  // Einfuegen
//STRIP001     pCurShell->StartAllAction();
//STRIP001
//STRIP001     pCurShell->Insert(*pFld);
//STRIP001
//STRIP001  if(bExp && bEvalExp)
//STRIP001         pCurShell->UpdateExpFlds(TRUE);
//STRIP001
//STRIP001  if(bTbl)
//STRIP001  {
//STRIP001         pCurShell->Left(CRSR_SKIP_CHARS, FALSE, 1, FALSE );
//STRIP001         pCurShell->UpdateFlds(*pFld);
//STRIP001         pCurShell->Right(CRSR_SKIP_CHARS, FALSE, 1, FALSE );
//STRIP001  }
//STRIP001  else if( bPageVar )
//STRIP001         ((SwRefPageGetFieldType*)pCurShell->GetFldType( 0, RES_REFPAGEGETFLD ))->UpdateFlds();
//STRIP001     else if( TYP_GETREFFLD == rData.nTypeId )
//STRIP001      pFld->GetTyp()->Modify( 0, 0 );
//STRIP001
//STRIP001  // temporaeres Feld loeschen
//STRIP001  delete pFld;
//STRIP001
//STRIP001     pCurShell->EndAllAction();
//STRIP001  return TRUE;
//STRIP001 }
//STRIP001
//STRIP001 /*--------------------------------------------------------------------
//STRIP001  Beschreibung: Felder Update
//STRIP001  --------------------------------------------------------------------*/
//STRIP001
//STRIP001
//STRIP001 void SwFldMgr::UpdateCurFld(ULONG nFormat,
//STRIP001                          const String& rPar1,
//STRIP001                          const String& rPar2)
//STRIP001 {
//STRIP001  // Format aendern
//STRIP001  ASSERT(pCurFld, "kein Feld an der CursorPos");
//STRIP001
//STRIP001  SwFieldType* pType   = pCurFld->GetTyp();
//STRIP001  const USHORT nTypeId = pCurFld->GetTypeId();
//STRIP001
//STRIP001  SwWrtShell &rSh = pWrtShell ? *pWrtShell : *::lcl_GetShell();
//STRIP001  rSh.StartAllAction();
//STRIP001
//STRIP001  BOOL bSetPar2 = TRUE;
//STRIP001  BOOL bSetPar1 = TRUE;
//STRIP001  String sPar1( rPar1 );
//STRIP001  String sPar2( rPar2 );
//STRIP001
//STRIP001  // Order to Format
//STRIP001  switch( nTypeId )
//STRIP001  {
//STRIP001      case TYP_DDEFLD:
//STRIP001      {
//STRIP001          //JP 28.08.95: DDE-Topics/-Items koennen Blanks in ihren
//STRIP001          //              Namen haben! Wird hier noch nicht beachtet.
//STRIP001             USHORT nTmpPos = sPar2.SearchAndReplace( ' ', ::so3::cTokenSeperator );
//STRIP001             sPar2.SearchAndReplace( ' ', ::so3::cTokenSeperator, nTmpPos );
//STRIP001          break;
//STRIP001      }
//STRIP001
//STRIP001      case TYP_CHAPTERFLD:
//STRIP001      {
//STRIP001             USHORT nByte = (USHORT)rPar2.ToInt32();
//STRIP001          nByte = Max(USHORT(1), nByte);
//STRIP001          nByte = Min(nByte, USHORT(MAXLEVEL));
//STRIP001          nByte -= 1;
//STRIP001          ((SwChapterField*)pCurFld)->SetLevel((BYTE)nByte);
//STRIP001          bSetPar2 = FALSE;
//STRIP001          break;
//STRIP001      }
//STRIP001
//STRIP001      case TYP_SCRIPTFLD:
//STRIP001          ((SwScriptField*)pCurFld)->SetCodeURL((BOOL)nFormat);
//STRIP001          break;
//STRIP001
//STRIP001      case TYP_NEXTPAGEFLD:
//STRIP001          if( SVX_NUM_CHAR_SPECIAL == nFormat )
//STRIP001          {
//STRIP001              ((SwPageNumberField*)pCurFld)->SetUserString( sPar2 );
//STRIP001              sPar2 = 1;
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              if( nFormat + 2 == SVX_NUM_PAGEDESC )
//STRIP001                  nFormat = SVX_NUM_PAGEDESC;
//STRIP001                 short nOff = (short)sPar2.ToInt32();
//STRIP001              nOff += 1;
//STRIP001              sPar2 = nOff;
//STRIP001          }
//STRIP001          break;
//STRIP001
//STRIP001      case TYP_PREVPAGEFLD:
//STRIP001          if( SVX_NUM_CHAR_SPECIAL == nFormat )
//STRIP001          {
//STRIP001              ((SwPageNumberField*)pCurFld)->SetUserString( sPar2 );
//STRIP001              sPar2 = -1;
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              if( nFormat + 2 == SVX_NUM_PAGEDESC )
//STRIP001                  nFormat = SVX_NUM_PAGEDESC;
//STRIP001                 short nOff = (short)sPar2.ToInt32();
//STRIP001              nOff -= 1;
//STRIP001              sPar2 = nOff;
//STRIP001          }
//STRIP001          break;
//STRIP001
//STRIP001      case TYP_PAGENUMBERFLD:
//STRIP001      case TYP_GETREFPAGEFLD:
//STRIP001          if( nFormat + 2 == SVX_NUM_PAGEDESC )
//STRIP001              nFormat = SVX_NUM_PAGEDESC;
//STRIP001          break;
//STRIP001
//STRIP001      case TYP_GETREFFLD:
//STRIP001          {
//STRIP001              bSetPar2 = FALSE;
//STRIP001                 ((SwGetRefField*)pCurFld)->SetSubType( (USHORT)rPar2.ToInt32() );
//STRIP001              USHORT nPos = rPar2.Search( '|' );
//STRIP001              if( STRING_NOTFOUND != nPos )
//STRIP001                     ((SwGetRefField*)pCurFld)->SetSeqNo( (USHORT)rPar2.Copy( nPos + 1 ).ToInt32());
//STRIP001          }
//STRIP001          break;
//STRIP001      case TYP_DROPDOWN:
//STRIP001      {
//STRIP001             xub_StrLen nTokenCount = sPar2.Len() ? sPar2.GetTokenCount(DB_DELIM) : 0;
//STRIP001             Sequence<OUString> aEntries(nTokenCount);
//STRIP001             OUString* pArray = aEntries.getArray();
//STRIP001             for(xub_StrLen nToken = 0; nToken < nTokenCount; nToken++)
//STRIP001                 pArray[nToken] = sPar2.GetToken(nToken, DB_DELIM);
//STRIP001             ((SwDropDownField*)pCurFld)->SetItems(aEntries);
//STRIP001             ((SwDropDownField*)pCurFld)->SetName(sPar1);
//STRIP001          bSetPar1 = bSetPar2 = FALSE;
//STRIP001      }
//STRIP001      break;
//STRIP001  }
//STRIP001
//STRIP001  // Format setzen
//STRIP001  // Format wegen NumberFormatter vor SetPar2 einstellen!
//STRIP001  pCurFld->ChangeFormat(nFormat);
//STRIP001
//STRIP001  if(bSetPar1)
//STRIP001  pCurFld->SetPar1( sPar1 );
//STRIP001  if( bSetPar2 )
//STRIP001      pCurFld->SetPar2( sPar2 );
//STRIP001
//STRIP001  // Update anschmeissen
//STRIP001  if(nTypeId == TYP_DDEFLD ||
//STRIP001     nTypeId == TYP_USERFLD ||
//STRIP001     nTypeId == TYP_USRINPFLD)
//STRIP001  {
//STRIP001      pType->UpdateFlds();
//STRIP001      rSh.SetModified();
//STRIP001  }
//STRIP001  else
//STRIP001      rSh.SwEditShell::UpdateFlds(*pCurFld);
//STRIP001
//STRIP001  rSh.EndAllAction();
//STRIP001 }
//STRIP001
//STRIP001 /*------------------------------------------------------------------------
//STRIP001  Beschreibung:   Setzen / Erfragen Werte von Benutzerfeldern aus BASIC
//STRIP001 ------------------------------------------------------------------------*/
//STRIP001
//STRIP001
//STRIP001 BOOL SwFldMgr::SetFieldValue(const String &rFieldName,
//STRIP001                           const String &rValue)
//STRIP001 {
//STRIP001  SwWrtShell* pSh = pWrtShell ? pWrtShell : ::lcl_GetShell();
//STRIP001  SwUserFieldType* pType = (SwUserFieldType*)pWrtShell->InsertFldType(
//STRIP001                                  SwUserFieldType( pSh->GetDoc(), rFieldName ));
//STRIP001
//STRIP001  if(pType)
//STRIP001      pType->SetContent(rValue);
//STRIP001  return 0 != pType;
//STRIP001 }
//STRIP001
//STRIP001 /*------------------------------------------------------------------------
//STRIP001  Beschreibung: Wert Datenbankfeld erfragen
//STRIP001 ------------------------------------------------------------------------*/
//STRIP001 #if 0
//STRIP001
//STRIP001 String SwFldMgr::GetDataBaseFieldValue(const String &rDBName, const String &rFieldName, SwWrtShell* pSh)
//STRIP001 {
//STRIP001  String sFieldName(rFieldName);
//STRIP001
//STRIP001  if (rDBName.Len())
//STRIP001      sFieldName = rDBName;
//STRIP001  else
//STRIP001      sFieldName = pSh->GetDBName();
//STRIP001  sFieldName += DB_DELIM;
//STRIP001  sFieldName += rFieldName;
//STRIP001
//STRIP001  SwFieldList aLst(pWrtShell ? pWrtShell : ::lcl_GetShell());
//STRIP001
//STRIP001  aLst.InsertFields(RES_DBFLD, &sFieldName);
//STRIP001  SwField* pFld = aLst.GetLastField();
//STRIP001
//STRIP001  if(!pFld)
//STRIP001      pFld = aLst.GetNextField();
//STRIP001
//STRIP001  if(pFld)
//STRIP001      return pFld->Expand();
//STRIP001
//STRIP001  return aEmptyStr;
//STRIP001 }
//STRIP001 #endif
//STRIP001
//STRIP001
//STRIP001 /*--------------------------------------------------------------------
//STRIP001  Beschreibung: ExpressionFields explizit evaluieren
//STRIP001  --------------------------------------------------------------------*/
//STRIP001 void SwFldMgr::EvalExpFlds(SwWrtShell* pSh)
//STRIP001 {
//STRIP001  if (pSh == NULL)
//STRIP001      pSh = pWrtShell ? pWrtShell : ::lcl_GetShell();
//STRIP001
//STRIP001  if(pSh)
//STRIP001  {
//STRIP001      pSh->StartAllAction();
//STRIP001      pSh->UpdateExpFlds(TRUE);
//STRIP001      pSh->EndAllAction();
//STRIP001  }
//STRIP001 }
//STRIP001 USHORT SwFldMgr::GetCurrLanguage() const
//STRIP001 {
//STRIP001  SwWrtShell* pSh = pWrtShell ? pWrtShell : ::lcl_GetShell();
//STRIP001  if( pSh )
//STRIP001      return pSh->GetCurLang();
//STRIP001  return SvxLocaleToLanguage( GetAppLocaleData().getLocale() );
//STRIP001 }

/*N*/ void SwFieldType::_GetFldName()
/*N*/ {
/*N*/   static const USHORT coFldCnt = STR_TYPE_END - STR_TYPE_BEGIN;
/*N*/
/*N*/   static USHORT __READONLY_DATA coFldNms[ coFldCnt ] = {
/*N*/       FLD_DATE_STD,
/*N*/       FLD_TIME_STD,
/*N*/       STR_FILENAMEFLD,
/*N*/       STR_DBNAMEFLD,
/*N*/       STR_CHAPTERFLD,
/*N*/       STR_PAGENUMBERFLD,
/*N*/       STR_DOCSTATFLD,
/*N*/       STR_AUTHORFLD,
/*N*/       STR_SETFLD,
/*N*/       STR_GETFLD,
/*N*/       STR_FORMELFLD,
/*N*/       STR_HIDDENTXTFLD,
/*N*/       STR_SETREFFLD,
/*N*/       STR_GETREFFLD,
/*N*/       STR_DDEFLD,
/*N*/       STR_MACROFLD,
/*N*/       STR_INPUTFLD,
/*N*/       STR_HIDDENPARAFLD,
/*N*/       STR_DOCINFOFLD,
/*N*/       STR_DBFLD,
/*N*/       STR_USERFLD,
/*N*/       STR_POSTITFLD,
/*N*/       STR_TEMPLNAMEFLD,
/*N*/       STR_SEQFLD,
/*N*/       STR_DBNEXTSETFLD,
/*N*/       STR_DBNUMSETFLD,
/*N*/       STR_DBSETNUMBERFLD,
/*N*/       STR_CONDTXTFLD,
/*N*/       STR_NEXTPAGEFLD,
/*N*/       STR_PREVPAGEFLD,
/*N*/       STR_EXTUSERFLD,
/*N*/       FLD_DATE_FIX,
/*N*/       FLD_TIME_FIX,
/*N*/       STR_SETINPUTFLD,
/*N*/       STR_USRINPUTFLD,
/*N*/       STR_SETREFPAGEFLD,
/*N*/       STR_GETREFPAGEFLD,
/*N*/       STR_INTERNETFLD,
/*N*/       STR_JUMPEDITFLD,
/*N*/       STR_SCRIPTFLD,
/*N*/       STR_AUTHORITY,
/*N*/       STR_COMBINED_CHARS,
/*N*/       STR_DROPDOWN
/*N*/   };
/*N*/
/*N*/   // Infos fuer Felder einfuegen
/*N*/   SwFieldType::pFldNames = new SvStringsDtor( (BYTE)coFldCnt, 2 );
/*N*/   for( USHORT nIdx = 0; nIdx < coFldCnt; ++nIdx )
/*N*/   {
/*N*/       String* pTmp = new SW_RESSTR( coFldNms[ nIdx ] );
/*N*/       pTmp->EraseAllChars('~');
/*N*/       SwFieldType::pFldNames->Insert(pTmp, nIdx );
/*N*/   }
/*N*/ }


//STRIP001 BOOL SwFldMgr::SetUserSubType(const String& rName, USHORT nType)
//STRIP001 {
//STRIP001  BOOL bRet = FALSE;
//STRIP001  SwUserFieldType *pType =
//STRIP001      (SwUserFieldType *) (pWrtShell ?
//STRIP001          pWrtShell->GetFldType(RES_USERFLD, rName) :
//STRIP001              ::lcl_GetShell()->GetFldType(RES_USERFLD, rName));
//STRIP001
//STRIP001  if(pType)
//STRIP001  {
//STRIP001      pType->SetType(nType);
//STRIP001      bRet = TRUE;
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }
//STRIP001
//STRIP001 BOOL SwFldMgr::InsertURL(  const String& rName,
//STRIP001                              const String& rVal,
//STRIP001                              const String& rFrame,
//STRIP001                              const SvxMacroItem* pItem)
//STRIP001 {
//STRIP001  sCurFrame = rFrame;
//STRIP001  pMacroItem = pItem;
//STRIP001     SwInsertFld_Data aData(TYP_INTERNETFLD, 0, rName, rVal, 0);
//STRIP001     BOOL bRet = InsertFld(aData);
//STRIP001  sCurFrame = aEmptyStr;
//STRIP001  pMacroItem = 0;
//STRIP001  return bRet;
//STRIP001
//STRIP001 }
//STRIP001
//STRIP001 /*--------------------------------------------------------------------
//STRIP001  Beschreibung:
//STRIP001  --------------------------------------------------------------------*/
//STRIP001
//STRIP001 BOOL SwFldMgr::ChooseMacro(const String &rSelMacro)
//STRIP001 {
//STRIP001     BOOL bRet = FALSE;
//STRIP001     String sSelMacro(rSelMacro);
//STRIP001  SfxApplication* pSfxApp = SFX_APP();
//STRIP001
//STRIP001  if (sSelMacro.GetToken(0) == pSfxApp->GetName())
//STRIP001  {   // Malte arbeitet (faelschlicherweise) in ChooseMacro mit
//STRIP001      // GetTitle statt GetName, daher diese Konvertierung:
//STRIP001      sSelMacro.SetToken( 0, ';', Application::GetAppName());
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      SwWrtShell *pSh = pWrtShell ? pWrtShell : ::lcl_GetShell();
//STRIP001      if (pSh)
//STRIP001      {
//STRIP001          SwDocShell* pDocSh = pSh->GetView().GetDocShell();
//STRIP001
//STRIP001          if (sSelMacro.GetToken(0) == pDocSh->GetName())
//STRIP001          {   // Malte arbeitet (faelschlicherweise) in ChooseMacro mit
//STRIP001              // GetTitle statt GetName, daher diese Konvertierung:
//STRIP001              sSelMacro.SetToken( 0, ';', pDocSh->GetTitle( SFX_TITLE_FILENAME ));
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001     // choose macro dialog
//STRIP001     String aScriptURL = OfficeApplication::ChooseMacro(FALSE, TRUE, sSelMacro);
//STRIP001
//STRIP001  // aScriptURL has the following format:
//STRIP001     // vnd.sun.star.script:language=[language],macro=[macro],location=[location]
//STRIP001     // [language] = StarBasic
//STRIP001     // [macro] = libname.modulename.macroname
//STRIP001     // [location] = application|document
//STRIP001     // e.g. 'vnd.sun.star.script:language=StarBasic,macro=Standard.Module1.Main,location=document'
//STRIP001     //
//STRIP001  // but for the UI we need this format:
//STRIP001  // 'macroname.modulename.libname.[appname|docname]'
//STRIP001
//STRIP001  if ( aScriptURL.Len() != 0 )
//STRIP001  {
//STRIP001      // parse script URL
//STRIP001         BOOL bFound;
//STRIP001         String aValue;
//STRIP001         INetURLObject aINetScriptURL( aScriptURL );
//STRIP001
//STRIP001         // get language
//STRIP001         String aLanguage;
//STRIP001         bFound = aINetScriptURL.getParameter( String( RTL_CONSTASCII_USTRINGPARAM("language") ), &aValue );
//STRIP001         if ( bFound )
//STRIP001             aLanguage = aValue;
//STRIP001
//STRIP001         // get macro
//STRIP001         String aMacro;
//STRIP001         String aLibName;
//STRIP001         String aModuleName;
//STRIP001         String aMacroName;
//STRIP001         bFound = aINetScriptURL.getParameter( String( RTL_CONSTASCII_USTRINGPARAM("macro") ), &aValue );
//STRIP001         if ( bFound )
//STRIP001         {
//STRIP001             aMacro = aValue;
//STRIP001             aLibName    = aMacro.GetToken(0, sal_Unicode('.'));
//STRIP001          aModuleName = aMacro.GetToken(1, sal_Unicode('.'));
//STRIP001          aMacroName  = aMacro.GetToken(2, sal_Unicode('.'));
//STRIP001         }
//STRIP001
//STRIP001         // get location
//STRIP001         String aLocation;
//STRIP001         bFound = aINetScriptURL.getParameter( String( RTL_CONSTASCII_USTRINGPARAM("location") ), &aValue );
//STRIP001         if ( bFound )
//STRIP001             aLocation = aValue;
//STRIP001
//STRIP001      pSfxApp->EnterBasicCall();
//STRIP001
//STRIP001      // find doc shell and basic manager
//STRIP001      SfxObjectShell* pShell = 0;
//STRIP001      BasicManager* pBasMgr = 0;
//STRIP001         if ( aLocation.EqualsIgnoreCaseAscii( "application" ) )
//STRIP001         {
//STRIP001          // application basic
//STRIP001          pBasMgr = pSfxApp->GetBasicManager();
//STRIP001      }
//STRIP001         else if ( aLocation.EqualsIgnoreCaseAscii( "document" ) )
//STRIP001         {
//STRIP001          // document basic
//STRIP001          SwWrtShell *pSh = pWrtShell ? pWrtShell : ::lcl_GetShell();
//STRIP001          if (pSh)
//STRIP001          {
//STRIP001              pShell = (SfxObjectShell*)pSh->GetView().GetDocShell();
//STRIP001              pBasMgr = ( pShell ? pShell->GetBasicManager() : 0 );
//STRIP001          }
//STRIP001      }
//STRIP001         ASSERT(pBasMgr, "SwFldMgr::ChooseMacro: No BasicManager found!");
//STRIP001
//STRIP001      if ( pBasMgr)
//STRIP001      {
//STRIP001          StarBASIC* pBasic = pBasMgr->GetLib( aLibName );
//STRIP001          ASSERT(pBasic, "SwFldMgr::ChooseMacro: No Basic found!");
//STRIP001
//STRIP001          if ( pBasic )
//STRIP001          {
//STRIP001              SbModule* pModule = pBasic->FindModule( aModuleName );
//STRIP001
//STRIP001              if ( pModule )
//STRIP001              {
//STRIP001                  SetMacroModule( pModule );
//STRIP001
//STRIP001                  // construct macro path
//STRIP001                  String aMacroPath( aMacroName );
//STRIP001                  aMacroPath += '.';
//STRIP001                  aMacroPath += aModuleName;
//STRIP001                  aMacroPath += '.';
//STRIP001                  aMacroPath += aLibName;
//STRIP001                  aMacroPath += '.';
//STRIP001
//STRIP001                  if ( pShell )
//STRIP001                      aMacroPath += pShell->GetName();
//STRIP001                  else
//STRIP001                      aMacroPath += pSfxApp->GetName();
//STRIP001
//STRIP001                  SetMacroPath( aMacroPath );
//STRIP001                  bRet = TRUE;
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001      pSfxApp->LeaveBasicCall();
//STRIP001  }
//STRIP001
//STRIP001  return bRet;
//STRIP001 }
//STRIP001
//STRIP001 /*--------------------------------------------------------------------
//STRIP001  Beschreibung:
//STRIP001  --------------------------------------------------------------------*/
//STRIP001
//STRIP001 ULONG SwFldMgr::GetDefaultFormat(USHORT nTypeId, BOOL bIsText, SvNumberFormatter* pFormatter, double* pVal)
//STRIP001 {
//STRIP001  double fValue;
//STRIP001  short  nDefFormat;
//STRIP001
//STRIP001  switch (nTypeId)
//STRIP001  {
//STRIP001      case TYP_TIMEFLD:
//STRIP001      case TYP_DATEFLD:
//STRIP001      {
//STRIP001          Date aDate;
//STRIP001          Date* pNullDate = pFormatter->GetNullDate();
//STRIP001
//STRIP001          fValue = aDate - *pNullDate;
//STRIP001
//STRIP001          Time aTime;
//STRIP001
//STRIP001          ULONG nNumFmtTime = (ULONG)aTime.GetSec() + (ULONG)aTime.GetMin() * 60L +
//STRIP001                        (ULONG)aTime.GetHour() * 3600L;
//STRIP001
//STRIP001          fValue += (double)nNumFmtTime / 86400.0;
//STRIP001
//STRIP001          nDefFormat = (nTypeId == TYP_DATEFLD) ? NUMBERFORMAT_DATE : NUMBERFORMAT_TIME;
//STRIP001      }
//STRIP001      break;
//STRIP001
//STRIP001      default:
//STRIP001          if (bIsText)
//STRIP001          {
//STRIP001              fValue = 0.0;
//STRIP001              nDefFormat = NUMBERFORMAT_TEXT;
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              fValue = 0.0;
//STRIP001              nDefFormat = NUMBERFORMAT_ALL;
//STRIP001          }
//STRIP001          break;
//STRIP001  }
//STRIP001
//STRIP001  if (pVal)
//STRIP001      *pVal = fValue;
//STRIP001
//STRIP001  return pFormatter->GetStandardFormat(nDefFormat, GetCurrLanguage());
//STRIP001 }
//STRIP001 /* -----------------------------23.06.00 17:32--------------------------------
//STRIP001
//STRIP001  ---------------------------------------------------------------------------*/
//STRIP001 Reference<XNameAccess> SwFldMgr::GetDBContext()
//STRIP001 {
//STRIP001  if(!xDBContext.is())
//STRIP001  {
//STRIP001      Reference< XMultiServiceFactory > xMgr( ::legacy_binfilters::getLegacyProcessServiceFactory() );
//STRIP001      if( xMgr.is() )
//STRIP001      {
//STRIP001          Reference<XInterface> xInstance = xMgr->createInstance(
//STRIP001                  ::rtl::OUString::createFromAscii(
//STRIP001                                  "com.sun.star.sdb.DatabaseContext" ));
//STRIP001          xDBContext = Reference<XNameAccess>(xInstance, UNO_QUERY) ;
//STRIP001      }
//STRIP001      DBG_ASSERT(xDBContext.is(), "com.sun.star.sdb.DataBaseContext: service not available")
//STRIP001  }
//STRIP001  return xDBContext;
//STRIP001 }
//STRIP001 /* -----------------------------01.03.01 16:46--------------------------------
//STRIP001
//STRIP001  ---------------------------------------------------------------------------*/
//STRIP001 Reference<XNumberingTypeInfo> SwFldMgr::GetNumberingInfo() const
//STRIP001 {
//STRIP001  if(!xNumberingInfo.is())
//STRIP001  {
//STRIP001      Reference< XMultiServiceFactory > xMSF = ::legacy_binfilters::getLegacyProcessServiceFactory();
//STRIP001      Reference < XInterface > xI = xMSF->createInstance(
//STRIP001          ::rtl::OUString::createFromAscii(
//STRIP001                          "com.sun.star.text.DefaultNumberingProvider" ));
//STRIP001      Reference<XDefaultNumberingProvider> xDefNum(xI, UNO_QUERY);
//STRIP001      DBG_ASSERT(xDefNum.is(), "service missing: \"com.sun.star.text.DefaultNumberingProvider\"")
//STRIP001      ((SwFldMgr*)this)->xNumberingInfo = Reference<XNumberingTypeInfo>(xDefNum, UNO_QUERY);
//STRIP001  }
//STRIP001  return xNumberingInfo;
//STRIP001 }
}
