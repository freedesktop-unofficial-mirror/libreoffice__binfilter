/*************************************************************************
 *
 *  $RCSfile: sw_section.cxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: pjunck $ $Date: 2004-10-27 13:34:57 $
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

#include <stdlib.h>

#ifndef _HINTIDS_HXX
#include <hintids.hxx>
#endif

#ifndef _SFXINTITEM_HXX //autogen
#include <svtools/intitem.hxx>
#endif
#ifndef _SFXSTRITEM_HXX //autogen
#include <svtools/stritem.hxx>
#endif
#ifndef _SFXDOCFILE_HXX //autogen
#include <bf_sfx2/docfile.hxx>
#endif
#ifndef _SFX_DOCFILT_HACK_HXX //autogen
#include <bf_sfx2/docfilt.hxx>
#endif
#ifndef _SVX_PROTITEM_HXX //autogen
#include <bf_svx/protitem.hxx>
#endif
#ifndef _SVXLINKMGR_HXX
#include <bf_svx/linkmgr.hxx>
#endif
#ifndef _URLOBJ_HXX //autogen
#include <tools/urlobj.hxx>
#endif

#ifndef _DOCARY_HXX
#include <docary.hxx>
#endif
#ifndef _FMTCNTNT_HXX //autogen
#include <fmtcntnt.hxx>
#endif
// auto strip #ifndef _FMTPDSC_HXX //autogen
// auto strip #include <fmtpdsc.hxx>
// auto strip #endif
#ifndef _ERRHDL_HXX
#include <errhdl.hxx>
#endif

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

#ifndef _DOC_HXX
#include <doc.hxx>
#endif
// auto strip #ifndef _NODE_HXX
// auto strip #include <node.hxx>
// auto strip #endif
#ifndef _PAM_HXX
#include <pam.hxx>
#endif
// auto strip #ifndef _FRMTOOL_HXX
// auto strip #include <frmtool.hxx>
// auto strip #endif
#ifndef _EDITSH_HXX
#include <editsh.hxx>
#endif
#ifndef _HINTS_HXX
#include <hints.hxx>
#endif
#ifndef _DOCSH_HXX
#include <docsh.hxx>
#endif
#ifndef _NDTXT_HXX
#include <ndtxt.hxx>
#endif
// auto strip #ifndef _SECTION_HXX
// auto strip #include <section.hxx>
// auto strip #endif
#ifndef _SWSERV_HXX
#include <swserv.hxx>
#endif
#ifndef _SHELLIO_HXX
#include <shellio.hxx>
#endif
#ifndef _POOLFMT_HXX
#include <poolfmt.hxx>
#endif
// auto strip #ifndef _BOOKMRK_HXX
// auto strip #include <bookmrk.hxx>
// auto strip #endif
// auto strip #ifndef _EXPFLD_HXX
// auto strip #include <expfld.hxx>
// auto strip #endif
#ifndef _SWBASLNK_HXX
#include <swbaslnk.hxx>
#endif
#ifndef _MVSAVE_HXX
#include <mvsave.hxx>
#endif
#ifndef _SECTFRM_HXX
#include <sectfrm.hxx>
#endif
// auto strip #ifndef _FMTFTNTX_HXX
// auto strip #include <fmtftntx.hxx>
// auto strip #endif
#ifndef _FTNIDX_HXX
#include <ftnidx.hxx>
#endif
#ifndef _DOCTXM_HXX
#include <doctxm.hxx>
#endif

#ifndef _SWSWERROR_H
#include <swerror.h>
#endif

#ifndef _FRMATR_HXX
#include <frmatr.hxx>
#endif

namespace binfilter {

/*N*/ SV_IMPL_REF( SwServerObject )

//static const char __FAR_DATA sSectionFmtNm[] = "Section";
#define sSectionFmtNm aEmptyStr

/*N*/ class SwIntrnlSectRefLink : public SwBaseLink
/*N*/ {
/*N*/   SwSectionFmt& rSectFmt;
/*N*/ public:
/*N*/   SwIntrnlSectRefLink( SwSectionFmt& rFmt, USHORT nUpdateType, USHORT nFmt )
/*N*/       : SwBaseLink( nUpdateType, nFmt ),
/*N*/       rSectFmt( rFmt )
/*N*/   {}
/*N*/
//STRIP001  virtual void Closed();
/*N*/   virtual void DataChanged( const String& rMimeType,
/*N*/                               const ::com::sun::star::uno::Any & rValue );
/*N*/
//STRIP001  virtual const SwNode* GetAnchor() const;
/*N*/   virtual BOOL IsInRange( ULONG nSttNd, ULONG nEndNd, xub_StrLen nStt = 0,
/*N*/                           xub_StrLen nEnd = STRING_NOTFOUND ) const;
/*N*/ };


/*N*/ TYPEINIT1(SwSectionFmt,SwFrmFmt );
/*N*/ TYPEINIT1(SwSection,SwClient );

/*N*/ typedef SwSection* SwSectionPtr;

//STRIP001 SV_IMPL_PTRARR( SwSections, SwSection*)
/*N*/ SV_IMPL_PTRARR(SwSectionFmts,SwSectionFmt*)



/*N*/ SwSection::SwSection( SectionType eTyp, const String& rName,
/*N*/                   SwSectionFmt* pFmt )
/*N*/   : SwClient( pFmt ),
/*N*/   eType( eTyp ), sSectionNm( rName )
/*N*/ {
/*N*/   bHidden = FALSE;
/*N*/   bHiddenFlag = FALSE;
/*N*/   bProtectFlag = FALSE;
/*N*/   bCondHiddenFlag = TRUE;
/*N*/   bConnectFlag = TRUE;
/*N*/
/*N*/   SwSectionPtr pParentSect = GetParent();
/*N*/   if( pParentSect )
/*N*/   {
/*N*/       FASTBOOL bPHFlag = pParentSect->IsHiddenFlag();
/*N*/       if( pParentSect->IsHiddenFlag() )
/*?*/           SetHidden( TRUE );
/*N*/
/*N*/       _SetProtectFlag( pParentSect->IsProtectFlag() );
/*N*/   }
/*N*/
/*N*/   if( pFmt && !bProtectFlag )
/*N*/       _SetProtectFlag( pFmt->GetProtect().IsCntntProtected() );
/*N*/ }


/*N*/ SwSection::~SwSection()
/*N*/ {
/*N*/   SwSectionFmt* pFmt = GetFmt();
/*N*/   if( !pFmt )
/*N*/       return;
/*N*/
/*N*/   SwDoc* pDoc = pFmt->GetDoc();
/*N*/   if( pDoc->IsInDtor() )
/*N*/   {
/*N*/       // dann melden wir noch schnell unser Format um ans dflt FrameFmt,
/*N*/       // damit es keine Abhaengigkeiten gibt
/*N*/       if( pFmt->DerivedFrom() != pDoc->GetDfltFrmFmt() )
/*N*/           pDoc->GetDfltFrmFmt()->Add( pFmt );
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       pFmt->Remove( this );               // austragen,
/*N*/
/*N*/       if( CONTENT_SECTION != eType )      // den Link austragen
/*N*/           pDoc->GetLinkManager().Remove( refLink );
/*N*/
/*N*/       if( refObj.Is() )                   // als Server austragen
/*?*/           pDoc->GetLinkManager().RemoveServer( &refObj );
/*N*/
/*N*/       // ist die Section der letzte Client im Format, kann dieses
/*N*/       // geloescht werden
/*N*/       SwPtrMsgPoolItem aMsgHint( RES_REMOVE_UNO_OBJECT, pFmt );
/*N*/       pFmt->Modify( &aMsgHint, &aMsgHint );
/*N*/       if( !pFmt->GetDepends() )
/*N*/       {
/*?*/           // Bug: 28191 - nicht ins Undo aufnehmen, sollte schon vorher
/*?*/           //          geschehen sein!!
/*?*/           BOOL bUndo = pDoc->DoesUndo();
/*?*/           pDoc->DoUndo( FALSE );
/*?*/           pDoc->DelSectionFmt( pFmt );    // und loeschen
/*?*/           pDoc->DoUndo( bUndo );
/*N*/       }
/*N*/   }
/*N*/   if( refObj.Is() )
/*N*/       refObj->Closed();
/*N*/ }


/*N*/ SwSection& SwSection::operator=( const SwSection& rCpy )
/*N*/ {
/*N*/   sSectionNm = rCpy.sSectionNm;
/*N*/   sCondition = rCpy.sCondition;
/*N*/   sLinkFileName = rCpy.GetLinkFileName();
/*N*/   SetLinkFilePassWd( rCpy.GetLinkFilePassWd() );
/*N*/   SetConnectFlag( rCpy.IsConnectFlag() );
/*N*/   SetPasswd( rCpy.GetPasswd() );
/*N*/
/*N*/   eType = rCpy.eType;
/*N*/
/*N*/   if( !GetFmt() )
/*N*/       SetProtect( rCpy.IsProtect() );
/*N*/   else if( rCpy.GetFmt() )
/*?*/       _SetProtectFlag( rCpy.bProtectFlag );
/*N*/   else
/*N*/       SetProtect( rCpy.bProtectFlag );
/*N*/
/*N*/   bCondHiddenFlag = TRUE;     // sollte immer defaultet werden
/*N*/   SetHidden( rCpy.bHidden );
/*N*/
/*N*/   return *this;
/*N*/ }


/*N*/ int SwSection::operator==( const SwSection& rCmp ) const
/*N*/ {
/*N*/   return  sSectionNm == rCmp.sSectionNm &&
/*N*/           sCondition == rCmp.sCondition &&
/*N*/           eType == rCmp.eType &&
/*N*/           bHidden == rCmp.bHidden &&
/*N*/           IsProtect() == rCmp.IsProtect() &&
/*N*/           GetLinkFileName() == rCmp.GetLinkFileName() &&
/*N*/           GetLinkFilePassWd() == rCmp.GetLinkFilePassWd() &&
/*N*/           GetPasswd() == rCmp.GetPasswd() &&
/*N*/           ( !GetFmt() || !rCmp.GetFmt() || GetFmt() == rCmp.GetFmt());
/*N*/ }


void SwSection::_SetHiddenFlag( int bHidden, int bCondition )
{
    SwSectionFmt* pFmt = GetFmt();
    if( pFmt )
    {
        int bHide = bHidden && bCondition;

        if( bHide )                         // die Nodes also "verstecken"
        {
            if( !bHiddenFlag )              // ist nicht versteckt
            {
                // wie sieht es mit dem Parent aus, ist der versteckt ?
                // (eigentlich muesste das vom bHiddenFlag angezeigt werden!)

                // erstmal allen Childs sagen, das sie versteckt sind
                SwMsgPoolItem aMsgItem( RES_SECTION_HIDDEN );
                pFmt->Modify( &aMsgItem, &aMsgItem );

                // alle Frames loeschen
                pFmt->DelFrms();
            }
        }
        else if( bHiddenFlag )              // die Nodes wieder anzeigen
        {
            // alle Frames sichtbar machen ( Childs Sections werden vom
            // MakeFrms beruecksichtigt). Aber nur wenn die ParentSection
            // nichts dagegen hat !
            SwSection* pParentSect = pFmt->GetParentSection();
            if( !pParentSect || !pParentSect->IsHiddenFlag() )
            {
                // erstmal allen Childs sagen, das der Parent nicht mehr
                // versteckt ist
                SwMsgPoolItem aMsgItem( RES_SECTION_NOT_HIDDEN );
                pFmt->Modify( &aMsgItem, &aMsgItem );

                pFmt->MakeFrms();
            }
        }
    }
}

/*N*/ int SwSection::CalcHiddenFlag() const
/*N*/ {
/*N*/   const SwSection* pSect = this;
/*N*/   do {
/*N*/       if( pSect->IsHidden() && pSect->IsCondHidden() )
/*?*/           return TRUE;
/*N*/   } while( 0 != ( pSect = pSect->GetParent()) );
/*N*/
/*N*/   return FALSE;
/*N*/ }

/*N*/ int SwSection::_IsProtect() const
/*N*/ {
/*N*/   return GetFmt()->GetProtect().IsCntntProtected();
/*N*/ }


/*N*/ void SwSection::SetHidden( int bFlag )
/*N*/ {
/*N*/   if( bHidden == bFlag )
/*N*/       return;
/*N*/
/*?*/   bHidden = bFlag;
/*?*/   _SetHiddenFlag( bHidden, bCondHiddenFlag );
/*N*/ }


/*N*/ void SwSection::SetProtect( int bFlag )
/*N*/ {
/*N*/   if( GetFmt() )
/*N*/   {
/*N*/       SvxProtectItem aItem;
/*N*/       aItem.SetCntntProtect( (BOOL)bFlag );
/*N*/       GetFmt()->SetAttr( aItem );
/*N*/   }
/*N*/   else
/*N*/       bProtectFlag = bFlag;
/*N*/ }


/*N*/ void SwSection::Modify( SfxPoolItem* pOld, SfxPoolItem* pNew )
/*N*/ {
/*N*/   BOOL bRemake = FALSE, bUpdateFtn = FALSE;
/*N*/   switch( pOld ? pOld->Which() : pNew ? pNew->Which() : 0 )
/*N*/   {
/*N*/   case RES_ATTRSET_CHG:
/*N*/       {
/*N*/           SfxItemSet* pNewSet = ((SwAttrSetChg*)pNew)->GetChgSet();
/*N*/           SfxItemSet* pOldSet = ((SwAttrSetChg*)pOld)->GetChgSet();
/*N*/           const SfxPoolItem* pItem;
/*N*/
/*N*/           if( SFX_ITEM_SET == pNewSet->GetItemState(
/*N*/                       RES_PROTECT, FALSE, &pItem ) )
/*N*/           {
/*?*/               _SetProtectFlag( ((SvxProtectItem*)pItem)->IsCntntProtected() );
/*?*/               pNewSet->ClearItem( RES_PROTECT );
/*?*/               pOldSet->ClearItem( RES_PROTECT );
/*N*/           }
/*N*/
/*N*/           if( SFX_ITEM_SET == pNewSet->GetItemState(
/*N*/                       RES_FTN_AT_TXTEND, FALSE, &pItem ) ||
/*N*/               SFX_ITEM_SET == pNewSet->GetItemState(
/*N*/                       RES_END_AT_TXTEND, FALSE, &pItem ))
/*?*/                   bUpdateFtn = TRUE;
/*N*/
/*N*/           if( !pNewSet->Count() )
/*?*/               return;
/*N*/       }
/*N*/       break;
/*N*/
/*N*/   case RES_PROTECT:
/*N*/       if( pNew )
/*N*/       {
/*N*/           BOOL bNewFlag = ((SvxProtectItem*)pNew)->IsCntntProtected();
/*N*/           if( !bNewFlag )
/*N*/           {
/*N*/               // Abschalten: teste ob nicht vielleich ueber die Parents
/*N*/               //              doch ein Schutzt besteht!
/*N*/               const SwSection* pSect = this;
/*N*/               do {
/*N*/                   if( pSect->IsProtect() )
/*N*/                   {
/*N*/                       bNewFlag = TRUE;
/*N*/                       break;
/*N*/                   }
/*N*/               } while( 0 != ( pSect = pSect->GetParent()) );
/*N*/           }
/*N*/
/*N*/           _SetProtectFlag( bNewFlag );
/*N*/       }
/*N*/       return;
/*N*/
/*?*/   case RES_SECTION_HIDDEN:
/*?*/       bHiddenFlag = TRUE;
/*?*/       return;
/*?*/
/*?*/   case RES_SECTION_NOT_HIDDEN:
/*?*/   case RES_SECTION_RESETHIDDENFLAG:
/*?*/       bHiddenFlag = bHidden && bCondHiddenFlag;
/*?*/       return;
/*?*/
/*?*/   case RES_COL:
/*?*/       /* wird ggf. vom Layout erledigt */
/*?*/       break;
/*?*/
/*?*/   case RES_FTN_AT_TXTEND:
/*?*/       if( pNew && pOld )
/*?*/           bUpdateFtn = TRUE;
/*?*/       break;
/*?*/
/*?*/   case RES_END_AT_TXTEND:
/*?*/       if( pNew && pOld )
/*?*/           bUpdateFtn = TRUE;
/*?*/       break;
/*N*/   }
/*N*/
/*N*/   if( bRemake )
/*N*/   {
/*?*/       DBG_BF_ASSERT(0, "STRIP"); //STRIP001 GetFmt()->DelFrms();
//STRIP001 /*?*/        GetFmt()->MakeFrms();
/*N*/   }
/*N*/
/*N*/   if( bUpdateFtn )
/*N*/   {
/*?*/       SwSectionNode* pSectNd = GetFmt()->GetSectionNode( FALSE );
/*?*/       if( pSectNd )
/*?*/           pSectNd->GetDoc()->GetFtnIdxs().UpdateFtn(SwNodeIndex( *pSectNd ));
/*N*/   }
/*N*/   SwClient::Modify( pOld, pNew );
/*N*/ }

/*N*/ void SwSection::SetRefObject( SwServerObject* pObj )
/*N*/ {
/*N*/   refObj = pObj;
/*N*/ }


void SwSection::SetCondHidden( int bFlag )
{
    if( bCondHiddenFlag == bFlag )
        return;

    bCondHiddenFlag = bFlag;
    _SetHiddenFlag( bHidden, bCondHiddenFlag );
}


// setze/erfrage den gelinkten FileNamen
/*N*/ const String& SwSection::GetLinkFileName() const
/*N*/ {
/*N*/   if( refLink.Is() )
/*N*/   {
/*N*/       String sTmp;
/*N*/       switch( eType )
/*N*/       {
/*N*/       case DDE_LINK_SECTION:
/*?*/           sTmp = refLink->GetLinkSourceName();
/*?*/           break;
/*N*/
/*N*/       case FILE_LINK_SECTION:
/*N*/           {
/*N*/               String sRange, sFilter;
/*N*/               if( refLink->GetLinkManager() &&
/*N*/                   refLink->GetLinkManager()->GetDisplayNames(
/*N*/                       refLink, 0, &sTmp, &sRange, &sFilter ) )
/*N*/               {
/*N*/                     ( sTmp += ::so3::cTokenSeperator ) += sFilter;
/*N*/                     ( sTmp += ::so3::cTokenSeperator ) += sRange;
/*N*/               }
/*N*/               else if( GetFmt() && !GetFmt()->GetSectionNode() )
/*N*/               {
/*N*/                   // ist die Section im UndoNodesArray, dann steht
/*N*/                   // der Link nicht im LinkManager, kann also auch nicht
/*N*/                   // erfragt werden. Dann returne den akt. Namen
/*?*/                   return sLinkFileName;
/*N*/               }
/*N*/           }
/*N*/           break;
/*N*/       }
/*N*/       ((SwSection*)this)->sLinkFileName = sTmp;
/*N*/   }
/*N*/   return sLinkFileName;
/*N*/ }


/*N*/ void SwSection::SetLinkFileName( const String& rNew, const String* pPassWd )
/*N*/ {
/*N*/   if( refLink.Is() )
/*?*/       refLink->SetLinkSourceName( rNew );
/*N*/   else
/*N*/       sLinkFileName = rNew;
/*N*/   if( pPassWd )
/*?*/       SetLinkFilePassWd( *pPassWd );
/*N*/ }

// falls es ein gelinkter Bereich war, dann muessen alle
// Child-Verknuepfungen sichtbar bemacht werden.
//STRIP001 void SwSection::MakeChildLinksVisible( const SwSectionNode& rSectNd )
//STRIP001 {
//STRIP001  const SwNode* pNd;
//STRIP001  const ::so3::SvBaseLinks& rLnks = rSectNd.GetDoc()->GetLinkManager().GetLinks();
//STRIP001  for( USHORT n = rLnks.Count(); n; )
//STRIP001  {
//STRIP001      ::so3::SvBaseLink* pBLnk = &(*rLnks[ --n ]);
//STRIP001      if( pBLnk && !pBLnk->IsVisible() &&
//STRIP001          pBLnk->ISA( SwBaseLink ) &&
//STRIP001          0 != ( pNd = ((SwBaseLink*)pBLnk)->GetAnchor() ) )
//STRIP001      {
//STRIP001          pNd = pNd->FindStartNode(); // falls SectionNode ist!
//STRIP001          const SwSectionNode* pParent;
//STRIP001          while( 0 != ( pParent = pNd->FindSectionNode() ) &&
//STRIP001                  ( CONTENT_SECTION == pParent->GetSection().GetType()
//STRIP001                      || pNd == &rSectNd ))
//STRIP001                  pNd = pParent->FindStartNode();
//STRIP001
//STRIP001          // steht nur noch in einer normalen Section, also
//STRIP001          // wieder anzeigen
//STRIP001          if( !pParent )
//STRIP001              pBLnk->SetVisible( TRUE );
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 const SwTOXBase* SwSection::GetTOXBase() const
//STRIP001 {
//STRIP001  const SwTOXBase* pRet = 0;
//STRIP001  if( TOX_CONTENT_SECTION == GetType() )
//STRIP001      pRet = PTR_CAST( SwTOXBaseSection, this );
//STRIP001  return pRet;
//STRIP001 }

/*N*/ SwSectionFmt::SwSectionFmt( SwSectionFmt* pDrvdFrm, SwDoc *pDoc )
/*N*/   : SwFrmFmt( pDoc->GetAttrPool(), sSectionFmtNm, pDrvdFrm )
/*N*/ {
/*N*/   LockModify();
/*N*/   SetAttr( *GetDfltAttr( RES_COL ) );
/*N*/   UnlockModify();
/*N*/ }

/*N*/ SwSectionFmt::~SwSectionFmt()
/*N*/ {
/*N*/   if( !GetDoc()->IsInDtor() )
/*N*/   {
/*N*/       SwSectionNode* pSectNd;
/*N*/       const SwNodeIndex* pIdx = GetCntnt( FALSE ).GetCntntIdx();
/*N*/       if( pIdx && &GetDoc()->GetNodes() == &pIdx->GetNodes() &&
/*N*/           0 != (pSectNd = pIdx->GetNode().GetSectionNode() ))
/*N*/       {
/*?*/           DBG_BF_ASSERT(0, "STRIP"); //STRIP001 SwSection& rSect = pSectNd->GetSection();
//STRIP001 /*?*/            // falls es ein gelinkter Bereich war, dann muessen alle
//STRIP001 /*?*/            // Child-Verknuepfungen sichtbar bemacht werden.
//STRIP001 /*?*/            if( rSect.IsConnected() )
//STRIP001 /*?*/            {DBG_BF_ASSERT(0, "STRIP");} //STRIP001     rSect.MakeChildLinksVisible( *pSectNd );
//STRIP001 /*?*/
//STRIP001 /*?*/            // vorm loeschen der Nodes pruefe, ob wir uns nicht
//STRIP001 /*?*/            // noch anzeigen muessen!
//STRIP001 /*?*/            if( rSect.IsHiddenFlag() )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                SwSectionPtr pParentSect = rSect.GetParent();
//STRIP001 /*?*/                if( !pParentSect || !pParentSect->IsHiddenFlag() )
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    // Nodes wieder anzeigen
//STRIP001 /*?*/                    rSect.SetHidden( FALSE );
//STRIP001 /*?*/                }
//STRIP001 /*?*/            }
//STRIP001 /*?*/            SwClientIter aIter( *this );
//STRIP001 /*?*/            SwClient *pLast = aIter.GoStart();
//STRIP001 /*?*/            while ( pLast )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                if ( pLast->IsA( TYPE(SwFrm) ) )
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    SwSectionFrm *pFrm = (SwSectionFrm*)pLast;
//STRIP001 /*?*/                    SwSectionFrm::MoveCntntAndDelete( pFrm, TRUE );
//STRIP001 /*?*/                    pLast = aIter.GoStart();
//STRIP001 /*?*/                }
//STRIP001 /*?*/                else
//STRIP001 /*?*/                    pLast = aIter++;
//STRIP001 /*?*/            }
//STRIP001 /*?*/            // hebe die Section doch mal auf
//STRIP001 /*?*/            SwNodeRange aRg( *pSectNd, 0, *pSectNd->EndOfSectionNode() );
//STRIP001 /*?*/            GetDoc()->GetNodes().SectionUp( &aRg );
/*N*/       }
/*N*/       LockModify();
/*N*/       ResetAttr( RES_CNTNT );
/*N*/       UnlockModify();
/*N*/   }
/*N*/ }


/*N*/ SwSectionPtr SwSectionFmt::_GetSection() const
/*N*/ {
/*N*/   if( GetDepends() )
/*N*/   {
/*N*/       SwClientIter aIter( *(SwSectionFmt*)this );
/*N*/       return (SwSectionPtr)aIter.First( TYPE(SwSection) );
/*N*/   }
/*N*/
/*?*/   ASSERT( FALSE, "keine Section als Client." )
/*?*/   return 0;
/*N*/ }

/*N*/ extern void lcl_DeleteFtn( SwSectionNode *pNd, ULONG nStt, ULONG nEnd );

//Vernichtet alle Frms in aDepend (Frms werden per PTR_CAST erkannt).
/*N*/ void SwSectionFmt::DelFrms()
/*N*/ {
/*N*/   SwSectionNode* pSectNd;
/*N*/   const SwNodeIndex* pIdx = GetCntnt(FALSE).GetCntntIdx();
/*N*/   if( pIdx && &GetDoc()->GetNodes() == &pIdx->GetNodes() &&
/*N*/       0 != (pSectNd = pIdx->GetNode().GetSectionNode() ))
/*N*/   {
/*N*/       SwClientIter aIter( *this );
/*N*/       SwClient *pLast = aIter.GoStart();
/*N*/       while ( pLast )
/*N*/       {
/*N*/           if ( pLast->IsA( TYPE(SwFrm) ) )
/*N*/           {
/*N*/               SwSectionFrm *pFrm = (SwSectionFrm*)pLast;
/*N*/               SwSectionFrm::MoveCntntAndDelete( pFrm, FALSE );
/*N*/               pLast = aIter.GoStart();
/*N*/           }
/*N*/           else
/*N*/           {
/*N*/               if ( pLast->IsA( TYPE(SwSectionFmt) ) )
/*?*/                   ((SwSectionFmt*)pLast)->DelFrms();
/*N*/               pLast = aIter++;
/*N*/           }
/*N*/       }
/*N*/       ULONG nEnde = pSectNd->EndOfSectionIndex();
/*N*/       ULONG nStart = pSectNd->GetIndex()+1;
/*N*/       lcl_DeleteFtn( pSectNd, nStart, nEnde );
/*N*/   }
/*N*/   if( pIdx )
/*N*/   {
/*N*/       //JP 22.09.98:
/*N*/       //Hint fuer Pagedesc versenden. Das mueste eigntlich das Layout im
/*N*/       //Paste der Frames selbst erledigen, aber das fuehrt dann wiederum
/*N*/       //zu weiteren Folgefehlern, die mit Laufzeitkosten geloest werden
/*N*/       //muesten. #56977# #55001# #56135#
/*N*/       SwNodeIndex aNextNd( *pIdx );
/*N*/       SwCntntNode* pCNd = GetDoc()->GetNodes().GoNextSection( &aNextNd, TRUE, FALSE );
/*N*/       if( pCNd )
/*N*/       {
/*N*/           const SfxPoolItem& rItem = pCNd->GetSwAttrSet().Get( RES_PAGEDESC );
/*N*/           pCNd->Modify( (SfxPoolItem*)&rItem, (SfxPoolItem*)&rItem );
/*N*/       }
/*N*/   }
/*N*/ }


//Erzeugt die Ansichten
void SwSectionFmt::MakeFrms()
{
    SwSectionNode* pSectNd;
    const SwNodeIndex* pIdx = GetCntnt(FALSE).GetCntntIdx();

    if( pIdx && &GetDoc()->GetNodes() == &pIdx->GetNodes() &&
        0 != (pSectNd = pIdx->GetNode().GetSectionNode() ))
    {
        SwNodeIndex aIdx( *pIdx );
        pSectNd->MakeFrms( &aIdx );
    }
}

/*N*/ void lcl_ClientIter( SwSectionFmt* pFmt, const SfxPoolItem* pOld,
/*N*/                                       const SfxPoolItem* pNew )
/*N*/ {
/*N*/   SwClientIter aIter( *pFmt );
/*N*/   SwClient * pLast = aIter.GoStart();
/*N*/   if( pLast )
/*N*/       do {
/*N*/           pLast->Modify( (SfxPoolItem*)pOld, (SfxPoolItem*)pNew );
/*N*/       } while( 0 != ( pLast = aIter++ ));
/*N*/ }

/*N*/ void SwSectionFmt::Modify( SfxPoolItem* pOld, SfxPoolItem* pNew )
/*N*/ {
/*N*/   BOOL bClients = FALSE;
/*N*/   USHORT nWhich = pOld ? pOld->Which() : pNew ? pNew->Which() : 0;
/*N*/   switch( nWhich )
/*N*/   {
/*N*/   case RES_ATTRSET_CHG:
/*N*/       if( GetDepends() )
/*N*/       {
/*N*/           SfxItemSet* pNewSet = ((SwAttrSetChg*)pNew)->GetChgSet();
/*N*/           SfxItemSet* pOldSet = ((SwAttrSetChg*)pOld)->GetChgSet();
/*N*/           const SfxPoolItem *pItem;
/*N*/           if( SFX_ITEM_SET == pNewSet->GetItemState(
/*N*/                                       RES_PROTECT, FALSE, &pItem ))
/*N*/           {
/*N*/               lcl_ClientIter( this, pItem, pItem );
/*N*/               pNewSet->ClearItem( RES_PROTECT );
/*N*/               pOldSet->ClearItem( RES_PROTECT );
/*N*/           }
/*N*/           if( SFX_ITEM_SET == pNewSet->GetItemState(
/*N*/                                   RES_FTN_AT_TXTEND, FALSE, &pItem ))
/*N*/           {
/*?*/               lcl_ClientIter( this, &pOldSet->Get( RES_FTN_AT_TXTEND ),
/*?*/                                       pItem );
/*?*/               pNewSet->ClearItem( RES_FTN_AT_TXTEND );
/*?*/               pOldSet->ClearItem( RES_FTN_AT_TXTEND );
/*N*/           }
/*N*/           if( SFX_ITEM_SET == pNewSet->GetItemState(
/*N*/                                   RES_END_AT_TXTEND, FALSE, &pItem ))
/*N*/           {
/*?*/               lcl_ClientIter( this, &pOldSet->Get( RES_END_AT_TXTEND ),
/*?*/                                       pItem );
/*?*/               pNewSet->ClearItem( RES_END_AT_TXTEND );
/*?*/               pOldSet->ClearItem( RES_END_AT_TXTEND );
/*N*/           }
/*N*/           if( !((SwAttrSetChg*)pOld)->GetChgSet()->Count() )
/*N*/               return;
/*N*/       }
/*N*/       break;
/*N*/
/*?*/   case RES_SECTION_RESETHIDDENFLAG:
/*?*/   case RES_FTN_AT_TXTEND:
/*?*/   case RES_END_AT_TXTEND : bClients = TRUE;
/*?*/                           // no break !!
/*?*/   case RES_SECTION_HIDDEN:
/*?*/   case RES_SECTION_NOT_HIDDEN:
/*?*/       {
/*?*/           SwSection* pSect = GetSection();
/*?*/           if( pSect && ( bClients || ( RES_SECTION_HIDDEN == nWhich ?
/*?*/                           !pSect->IsHiddenFlag() : pSect->IsHiddenFlag() ) ) )
/*?*/           {
/*?*/               // selbst ueber die Clients iterieren, sollte schneller sein!
/*?*/               SwClientIter aIter( *this );
/*?*/               SwClient * pLast = aIter.GoStart();
/*?*/               do {
/*?*/                   pLast->Modify( pOld, pNew );
/*?*/               } while( 0 != ( pLast = aIter++ ));
/*?*/           }
/*?*/       }
/*?*/       return ;
/*?*/
/*?*/
/*?*/   case RES_PROTECT:
/*?*/       // diese Messages bis zum Ende des Baums durchreichen !
/*?*/       if( GetDepends() )
/*?*/       {
/*?*/           SwClientIter aIter( *this );
/*?*/           SwClient * pLast = aIter.GoStart();
/*?*/           if( pLast )     // konnte zum Anfang gesprungen werden ??
/*?*/               do {
/*?*/                   pLast->Modify( pOld, pNew );
/*?*/               } while( 0 != ( pLast = aIter++ ));
/*?*/       }
/*?*/       return;     // das wars
/*?*/
/*?*/   case RES_OBJECTDYING:
/*?*/       if( !GetDoc()->IsInDtor() &&
/*?*/           ((SwPtrMsgPoolItem *)pOld)->pObject == (void*)GetRegisteredIn() )
/*?*/       {
/*?*/           // mein Parent wird vernichtet, dann an den Parent vom Parent
/*?*/           // umhaengen und wieder aktualisieren
/*?*/           DBG_BF_ASSERT(0, "STRIP"); //STRIP001 SwFrmFmt::Modify( pOld, pNew );   //  erst umhaengen !!!
//STRIP001 /*?*/            UpdateParent();
//STRIP001 /*?*/            return;
/*?*/       }
/*?*/       break;
/*N*/
/*N*/   case RES_FMT_CHG:
/*N*/       if( !GetDoc()->IsInDtor() &&
/*N*/           ((SwFmtChg*)pNew)->pChangedFmt == (void*)GetRegisteredIn() &&
/*N*/           ((SwFmtChg*)pNew)->pChangedFmt->IsA( TYPE( SwSectionFmt )) )
/*N*/       {
/*?*/           // mein Parent wird veraendert, muss mich aktualisieren
/*?*/           DBG_BF_ASSERT(0, "STRIP"); //STRIP001 SwFrmFmt::Modify( pOld, pNew );   //  erst umhaengen !!!
//STRIP001 /*?*/            UpdateParent();
//STRIP001 /*?*/            return;
/*N*/       }
/*N*/       break;
/*N*/   }
/*N*/   SwFrmFmt::Modify( pOld, pNew );
/*N*/ }

        // erfrage vom Format Informationen
//STRIP001 BOOL SwSectionFmt::GetInfo( SfxPoolItem& rInfo ) const
//STRIP001 {
//STRIP001  switch( rInfo.Which() )
//STRIP001  {
//STRIP001  case RES_FINDNEARESTNODE:
//STRIP001      if( ((SwFmtPageDesc&)GetAttr( RES_PAGEDESC )).GetPageDesc() )
//STRIP001      {
//STRIP001          const SwSectionNode* pNd = GetSectionNode();
//STRIP001          if( pNd )
//STRIP001              ((SwFindNearestNode&)rInfo).CheckNode( *pNd );
//STRIP001      }
//STRIP001      return TRUE;
//STRIP001
//STRIP001  case RES_CONTENT_VISIBLE:
//STRIP001      {
//STRIP001          SwFrm* pFrm = (SwFrm*)SwClientIter( *(SwSectionFmt*)this ).First( TYPE(SwFrm) );
//STRIP001          // if the current section has no own frame search for the children
//STRIP001          if(!pFrm)
//STRIP001          {
//STRIP001              SwClientIter aFormatIter( *(SwSectionFmt*)this );
//STRIP001              SwSectionFmt* pChild = (SwSectionFmt*)aFormatIter.
//STRIP001                                              First( TYPE(SwSectionFmt) );
//STRIP001              while(pChild && !pFrm)
//STRIP001              {
//STRIP001                  pFrm = (SwFrm*)SwClientIter( *pChild ).First( TYPE(SwFrm) );
//STRIP001                  pChild = (SwSectionFmt*)aFormatIter.Next();
//STRIP001              }
//STRIP001          }
//STRIP001          ((SwPtrMsgPoolItem&)rInfo).pObject = pFrm;
//STRIP001      }
//STRIP001      return FALSE;
//STRIP001  }
//STRIP001  return SwModify::GetInfo( rInfo );
//STRIP001 }

//STRIP001 extern "C" {
//STRIP001
//STRIP001  int
//STRIP001 #if defined( WNT )
//STRIP001      __cdecl
//STRIP001 #endif
//STRIP001 #if defined( ICC )
//STRIP001      _Optlink
//STRIP001 #endif
//STRIP001      lcl_SectionCmpPos( const void *pFirst, const void *pSecond)
//STRIP001  {
//STRIP001      const SwSectionFmt* pFSectFmt = (*(SwSectionPtr*)pFirst)->GetFmt();
//STRIP001      const SwSectionFmt* pSSectFmt = (*(SwSectionPtr*)pSecond)->GetFmt();
//STRIP001      ASSERT( pFSectFmt && pSSectFmt &&
//STRIP001              pFSectFmt->GetCntnt(FALSE).GetCntntIdx() &&
//STRIP001              pSSectFmt->GetCntnt(FALSE).GetCntntIdx(),
//STRIP001                  "ungueltige Sections" );
//STRIP001      return (int)((long)pFSectFmt->GetCntnt(FALSE).GetCntntIdx()->GetIndex()) -
//STRIP001                  pSSectFmt->GetCntnt(FALSE).GetCntntIdx()->GetIndex();
//STRIP001  }
//STRIP001
//STRIP001  int
//STRIP001 #if defined( WNT )
//STRIP001      __cdecl
//STRIP001 #endif
//STRIP001 #if defined( ICC )
//STRIP001      _Optlink
//STRIP001 #endif
//STRIP001      lcl_SectionCmpNm( const void *pFirst, const void *pSecond)
//STRIP001  {
//STRIP001      const SwSectionPtr pFSect = *(SwSectionPtr*)pFirst;
//STRIP001      const SwSectionPtr pSSect = *(SwSectionPtr*)pSecond;
//STRIP001      ASSERT( pFSect && pSSect, "ungueltige Sections" );
//STRIP001      StringCompare eCmp = pFSect->GetName().CompareTo( pSSect->GetName() );
//STRIP001      return eCmp == COMPARE_EQUAL ? 0
//STRIP001                          : eCmp == COMPARE_LESS ? 1 : -1;
//STRIP001  }
//STRIP001 }

    // alle Sections, die von dieser abgeleitet sind
/*N*/ USHORT SwSectionFmt::GetChildSections( SwSections& rArr,
/*N*/                                       SectionSort eSort,
/*N*/                                       int bAllSections ) const
/*N*/ {
/*N*/   rArr.Remove( 0, rArr.Count() );
/*N*/
/*N*/   if( GetDepends() )
/*N*/   {
/*N*/       SwClientIter aIter( *(SwSectionFmt*)this );
/*N*/       SwClient * pLast;
/*N*/       const SwNodeIndex* pIdx;
/*N*/       for( pLast = aIter.First(TYPE(SwSectionFmt)); pLast; pLast = aIter.Next() )
/*N*/           if( bAllSections ||
/*N*/               ( 0 != ( pIdx = ((SwSectionFmt*)pLast)->GetCntnt(FALSE).
/*N*/               GetCntntIdx()) && &pIdx->GetNodes() == &GetDoc()->GetNodes() ))
/*N*/           {
/*N*/               const SwSection* Dummy=((SwSectionFmt*)pLast)->GetSection();
/*N*/               rArr.C40_INSERT( SwSection,
/*N*/                   Dummy,
/*N*/                   rArr.Count() );
/*N*/           }
/*N*/
/*N*/       // noch eine Sortierung erwuenscht ?
/*N*/       if( 1 < rArr.Count() )
/*N*/       {DBG_BF_ASSERT(0, "STRIP");} //STRIP001     switch( eSort )
//STRIP001 /*?*/            {
//STRIP001 /*?*/            case SORTSECT_NAME:
//STRIP001 /*?*/                qsort( (void*)rArr.GetData(),
//STRIP001 /*?*/                        rArr.Count(),
//STRIP001 /*?*/                        sizeof( SwSectionPtr ),
//STRIP001 /*?*/                        lcl_SectionCmpNm );
//STRIP001 /*?*/                break;
//STRIP001 /*?*/
//STRIP001 /*?*/            case SORTSECT_POS:
//STRIP001 /*?*/                qsort( (void*)rArr.GetData(),
//STRIP001 /*?*/                        rArr.Count(),
//STRIP001 /*?*/                        sizeof( SwSectionPtr ),
//STRIP001 /*?*/                        lcl_SectionCmpPos );
//STRIP001 /*?*/                break;
//STRIP001 /*N*/            }
/*N*/   }
/*N*/   return rArr.Count();
/*N*/ }

    // erfrage, ob sich die Section im Nodes-Array oder UndoNodes-Array
    // befindet.
/*N*/ int SwSectionFmt::IsInNodesArr() const
/*N*/ {
/*N*/   const SwNodeIndex* pIdx = GetCntnt(FALSE).GetCntntIdx();
/*N*/   return pIdx && &pIdx->GetNodes() == &GetDoc()->GetNodes();
/*N*/ }


//STRIP001 void SwSectionFmt::UpdateParent()        // Parent wurde veraendert
//STRIP001 {
//STRIP001  if( !GetDepends() )
//STRIP001      return;
//STRIP001
//STRIP001  SwSectionPtr pSection = 0;
//STRIP001  const SvxProtectItem* pProtect;
//STRIP001  int bIsHidden = FALSE;
//STRIP001
//STRIP001  SwClientIter aIter( *this );
//STRIP001  SwClient * pLast = aIter.GoStart();
//STRIP001  if( pLast )     // konnte zum Anfang gesprungen werden ??
//STRIP001      do {
//STRIP001          if( pLast->IsA( TYPE(SwSectionFmt) ) )
//STRIP001          {
//STRIP001              if( !pSection )
//STRIP001              {
//STRIP001                  pSection = GetSection();
//STRIP001                  if( GetRegisteredIn() )
//STRIP001                  {
//STRIP001                      const SwSectionPtr pPS = GetParentSection();
//STRIP001                      pProtect = &pPS->GetFmt()->GetProtect();
//STRIP001                      bIsHidden = pPS->IsHiddenFlag();
//STRIP001                  }
//STRIP001                  else
//STRIP001                  {
//STRIP001                      pProtect = &GetProtect();
//STRIP001                      bIsHidden = pSection->IsHidden();
//STRIP001                  }
//STRIP001              }
//STRIP001              if( pProtect->IsCntntProtected() !=
//STRIP001                  pSection->IsProtectFlag() )
//STRIP001                  pLast->Modify( (SfxPoolItem*)pProtect,
//STRIP001                                  (SfxPoolItem*)pProtect );
//STRIP001
//STRIP001              if( bIsHidden == pSection->IsHiddenFlag() )
//STRIP001              {
//STRIP001                  SwMsgPoolItem aMsgItem( bIsHidden
//STRIP001                              ? RES_SECTION_HIDDEN
//STRIP001                              : RES_SECTION_NOT_HIDDEN );
//STRIP001                  pLast->Modify( &aMsgItem, &aMsgItem );
//STRIP001              }
//STRIP001          }
//STRIP001          else if( !pSection &&
//STRIP001                  pLast->IsA( TYPE(SwSection) ) )
//STRIP001          {
//STRIP001              pSection = (SwSectionPtr)pLast;
//STRIP001              if( GetRegisteredIn() )
//STRIP001              {
//STRIP001                  const SwSectionPtr pPS = GetParentSection();
//STRIP001                  pProtect = &pPS->GetFmt()->GetProtect();
//STRIP001                  bIsHidden = pPS->IsHiddenFlag();
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  pProtect = &GetProtect();
//STRIP001                  bIsHidden = pSection->IsHidden();
//STRIP001              }
//STRIP001          }
//STRIP001      } while( 0 != ( pLast = aIter++ ));
//STRIP001 }


/*N*/ SwSectionNode* SwSectionFmt::GetSectionNode( BOOL bAlways )
/*N*/ {
/*N*/   const SwNodeIndex* pIdx = GetCntnt(FALSE).GetCntntIdx();
/*N*/   if( pIdx && ( bAlways || &pIdx->GetNodes() == &GetDoc()->GetNodes() ))
/*N*/       return pIdx->GetNode().GetSectionNode();
/*N*/   return 0;
/*N*/ }

    // ist die Section eine gueltige fuers GlobalDocument?
/*N*/ const SwSection* SwSectionFmt::GetGlobalDocSection() const
/*N*/ {
/*N*/   const SwSectionNode* pNd = GetSectionNode();
/*N*/   if( pNd &&
/*N*/       ( FILE_LINK_SECTION == pNd->GetSection().GetType() ||
/*N*/         TOX_CONTENT_SECTION == pNd->GetSection().GetType() ) &&
/*N*/       pNd->GetIndex() > pNd->GetNodes().GetEndOfExtras().GetIndex() &&
/*N*/       !pNd->FindStartNode()->IsSectionNode() &&
/*N*/       !pNd->FindStartNode()->FindSectionNode() )
/*N*/       return &pNd->GetSection();
/*N*/   return 0;
/*N*/ }

/*N*/ void lcl_UpdateLinksInSect( SwBaseLink& rUpdLnk, SwSectionNode& rSectNd )
/*N*/ {
/*N*/   SwDoc* pDoc = rSectNd.GetDoc();
/*N*/   SwDocShell* pDShell = pDoc->GetDocShell();
/*N*/   if( !pDShell || !pDShell->GetMedium() )
/*?*/       return ;
/*N*/
/*N*/   String sName( pDShell->GetMedium()->GetName() );
/*N*/   SwBaseLink* pBLink;
/*N*/   String sMimeType( SotExchange::GetFormatMimeType( FORMAT_FILE ));
/*N*/   ::com::sun::star::uno::Any aValue;
/*N*/   aValue <<= ::rtl::OUString( sName );                        // beliebiger Name
/*N*/
/*N*/   const ::so3::SvBaseLinks& rLnks = pDoc->GetLinkManager().GetLinks();
/*N*/   for( USHORT n = rLnks.Count(); n; )
/*N*/   {
/*N*/       ::so3::SvBaseLink* pLnk = &(*rLnks[ --n ]);
/*N*/       if( pLnk && pLnk != &rUpdLnk &&
/*N*/           OBJECT_CLIENT_FILE == pLnk->GetObjType() &&
/*N*/           pLnk->ISA( SwBaseLink ) &&
/*N*/           ( pBLink = (SwBaseLink*)pLnk )->IsInRange( rSectNd.GetIndex(),
/*N*/                                               rSectNd.EndOfSectionIndex() ) )
/*N*/       {
/*?*/           // liegt in dem Bereich: also updaten. Aber nur wenns nicht
/*?*/           // im gleichen File liegt
/*?*/           DBG_BF_ASSERT(0, "STRIP"); //STRIP001 String sFName;
//STRIP001 /*?*/            pDoc->GetLinkManager().GetDisplayNames( pBLink, 0, &sFName, 0, 0 );
//STRIP001 /*?*/            if( sFName != sName )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                pBLink->DataChanged( sMimeType, aValue );
//STRIP001 /*?*/
//STRIP001 /*?*/                // ggfs. neu den Link-Pointer wieder suchen, damit nicht einer
//STRIP001 /*?*/                // ausgelassen oder doppelt gerufen wird.
//STRIP001 /*?*/                if( n >= rLnks.Count() && 0 != ( n = rLnks.Count() ))
//STRIP001 /*?*/                    --n;
//STRIP001 /*?*/
//STRIP001 /*?*/                if( n && pLnk != &(*rLnks[ n ]) )
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    // suchen - kann nur davor liegen!!
//STRIP001 /*?*/                    while( n )
//STRIP001 /*?*/                        if( pLnk == &(*rLnks[ --n ] ) )
//STRIP001 /*?*/                            break;
//STRIP001 /*?*/                }
//STRIP001 /*?*/            }
/*N*/       }
/*N*/   }
/*N*/ }


// sucht sich die richtige DocShell raus oder erzeugt eine neue:
// Der Return-Wert gibt an, was mit der Shell zu geschehen hat:
//  0 - Fehler, konnte DocShell nicht finden
//  1 - DocShell ist ein existieren Document
//  2 - DocShell wurde neu angelegt, muss also wieder geschlossen werden

/*N*/ int lcl_FindDocShell( SfxObjectShellRef& xDocSh,
/*N*/                       const String& rFileName,
/*N*/                       const String& rPasswd,
/*N*/                       String& rFilter,
/*N*/                       INT16 nVersion,
/*N*/                       SwDocShell* pDestSh )
/*N*/ {
/*N*/   if( !rFileName.Len() )
/*?*/       return 0;
/*N*/
/*N*/   // 1. existiert die Datei schon in der Liste aller Dokumente?
/*N*/   INetURLObject aTmpObj( rFileName );
/*N*/   aTmpObj.SetMark( aEmptyStr );
/*N*/
/*N*/   // erstmal nur ueber die DocumentShells laufen und die mit dem
/*N*/   // Namen heraussuchen:
/*N*/   TypeId aType( TYPE(SwDocShell) );
/*N*/
/*N*/   SfxObjectShell* pShell = pDestSh;
/*N*/   BOOL bFirst = 0 != pShell;
/*N*/
/*N*/   if( !bFirst )
/*N*/       // keine DocShell uebergeben, also beginne mit der ersten aus der
/*N*/       // DocShell Liste
/*?*/       pShell = SfxObjectShell::GetFirst( &aType );
/*N*/
/*N*/   while( pShell )
/*N*/   {
/*N*/       // die wollen wir haben
/*N*/       SfxMedium* pMed = pShell->GetMedium();
/*N*/       if( pMed && pMed->GetURLObject() == aTmpObj )
/*N*/       {
/*?*/           const SfxPoolItem* pItem;
/*?*/           if( ( SFX_ITEM_SET == pMed->GetItemSet()->GetItemState(
/*?*/                                           SID_VERSION, FALSE, &pItem ) )
/*?*/                   ? (nVersion == ((SfxInt16Item*)pItem)->GetValue())
/*?*/                   : !nVersion )
/*?*/           {
/*?*/               // gefunden also returnen
/*?*/               xDocSh = pShell;
/*?*/               return 1;
/*?*/           }
/*N*/       }
/*N*/
/*N*/       if( bFirst )
/*N*/       {
/*N*/           bFirst = FALSE;
/*N*/           pShell = SfxObjectShell::GetFirst( &aType );
/*N*/       }
/*N*/       else
/*?*/           pShell = SfxObjectShell::GetNext( *pShell, &aType );
/*N*/   }
/*N*/
/*N*/   // 2. selbst die Date oeffnen
/*N*/   SfxMedium* pMed = new SfxMedium( aTmpObj.GetMainURL(
/*N*/                            INetURLObject::NO_DECODE ), STREAM_READ, TRUE );
/*N*/   if( INET_PROT_FILE == aTmpObj.GetProtocol() )
/*N*/       pMed->DownLoad();     // nur mal das Medium anfassen (DownLoaden)
/*N*/
/*N*/   const SfxFilter* pSfxFlt = 0;
/*N*/   if( !pMed->GetError() )
/*N*/   {
/*N*/       // kein Filter, dann suche ihn. Ansonsten teste, ob der angegebene
/*N*/       // ein gueltiger ist
/*N*/       if( rFilter.Len() )
/*N*/       {
/*N*/           pSfxFlt =  SwIoSystem::GetFilterOfFilterTxt( rFilter );
/*N*/           if( pSfxFlt && !SwIoSystem::IsFileFilter( *pMed, pSfxFlt->GetUserData() ) && (pSfxFlt->GetFilterFlags() & SFX_FILTER_STARONEFILTER) == 0 )
/*N*/               pSfxFlt = 0;        // dann neu detecten lassen
/*N*/       }
/*N*/
/*N*/       if( !pSfxFlt )
/*N*/           pSfxFlt = SwIoSystem::GetFileFilter( pMed->GetPhysicalName(), aEmptyStr );
/*N*/
/*N*/       if( pSfxFlt )
/*N*/       {
/*N*/           // ohne Filter geht gar nichts
/*N*/           pMed->SetFilter( pSfxFlt );
/*N*/
/*N*/           if( nVersion )
/*?*/               pMed->GetItemSet()->Put( SfxInt16Item( SID_VERSION, nVersion ));
/*N*/
/*N*/           if( rPasswd.Len() )
/*?*/               pMed->GetItemSet()->Put( SfxStringItem( SID_PASSWORD, rPasswd ));
/*N*/
/*N*/           xDocSh = new SwDocShell( SFX_CREATE_MODE_INTERNAL );
/*N*/           if( xDocSh->DoLoad( pMed ) )
/*N*/               return 2;
/*N*/       }
/*N*/   }
/*N*/
/*?*/   if( !xDocSh.Is() )      // Medium muss noch geloescht werden
/*?*/       delete pMed;
/*?*/
/*?*/   return 0;   // das war wohl nichts
/*N*/ }


/*N*/ void SwIntrnlSectRefLink::DataChanged( const String& rMimeType,
/*N*/                               const ::com::sun::star::uno::Any & rValue )
/*N*/ {
/*N*/   SwSectionNode* pSectNd = rSectFmt.GetSectionNode( FALSE );
/*N*/   SwDoc* pDoc = rSectFmt.GetDoc();
/*N*/
/*N*/   ULONG nDataFormat = SotExchange::GetFormatIdFromMimeType( rMimeType );
/*N*/
/*N*/   if( !pSectNd || !pDoc || pDoc->IsInDtor() || ChkNoDataFlag() ||
/*N*/       SvxLinkManager::RegisterStatusInfoId() == nDataFormat )
/*N*/   {
/*N*/       // sollten wir schon wieder im Undo stehen?
/*?*/       return ;
/*N*/   }
/*N*/
/*N*/   // Undo immer abschalten
/*N*/   BOOL bWasUndo = pDoc->DoesUndo();
/*N*/   pDoc->DoUndo( FALSE );
/*N*/   BOOL bWasVisibleLinks = pDoc->IsVisibleLinks();
/*N*/   pDoc->SetVisibleLinks( FALSE );
/*N*/
/*N*/   SwPaM* pPam;
/*N*/   ViewShell* pVSh = 0;
/*N*/   SwEditShell* pESh = pDoc->GetEditShell( &pVSh );
/*N*/   pDoc->LockExpFlds();
/*N*/   {
/*N*/       // am Anfang des Bereichs einen leeren TextNode einfuegen
/*N*/       SwNodeIndex aIdx( *pSectNd, +1 );
/*N*/       SwNodeIndex aEndIdx( *pSectNd->EndOfSectionNode() );
/*N*/       SwTxtNode* pNewNd = pDoc->GetNodes().MakeTxtNode( aIdx,
/*N*/                       pDoc->GetTxtCollFromPool( RES_POOLCOLL_TEXT ) );
/*N*/
/*N*/       if( pESh )
/*N*/           pESh->StartAllAction();
/*N*/       else if( pVSh )
/*?*/           pVSh->StartAction();
/*N*/
/*N*/       SwPosition aPos( aIdx, SwIndex( pNewNd, 0 ));
/*N*/       aPos.nNode--;
/*N*/       pDoc->CorrAbs( aIdx, aEndIdx, aPos, TRUE );
/*N*/
/*N*/       pPam = new SwPaM( aPos );
/*N*/
/*N*/       //und alles dahinter liegende loeschen
/*N*/       aIdx--;
/*N*/       DelFlyInRange( aIdx, aEndIdx );
/*N*/       _DelBookmarks( aIdx, aEndIdx );
/*N*/       aIdx++;
/*N*/
/*N*/       pDoc->GetNodes().Delete( aIdx, aEndIdx.GetIndex() - aIdx.GetIndex() );
/*N*/   }
/*N*/
/*N*/   SwSection& rSection = pSectNd->GetSection();
/*N*/   rSection.SetConnectFlag( FALSE );
/*N*/
/*N*/   ::rtl::OUString sNewFileName;
/*N*/   Reader* pRead = 0;
/*N*/   switch( nDataFormat )
/*N*/   {
/*N*/   case FORMAT_STRING:
/*?*/       pRead = ReadAscii;
/*?*/       break;
/*?*/
/*?*/   case FORMAT_RTF:
/*?*/       pRead = ReadRtf;
/*?*/       break;
/*N*/
/*N*/   case FORMAT_FILE:
/*N*/       if( rValue.hasValue() && ( rValue >>= sNewFileName ) )
/*N*/       {
/*N*/           String sFilter, sRange, sFileName( sNewFileName );
/*N*/           pDoc->GetLinkManager().GetDisplayNames( this, 0, &sFileName,
/*N*/                                                   &sRange, &sFilter );
/*N*/
/*N*/           SwRedlineMode eOldRedlineMode = REDLINE_NONE;
/*N*/           SfxObjectShellRef xDocSh;
/*N*/           int nRet;
/*N*/           if( !sFileName.Len() )
/*N*/           {
/*N*/               xDocSh = pDoc->GetDocShell();
/*N*/               nRet = 1;
/*N*/           }
/*N*/           else
/*N*/           {
/*N*/               nRet = lcl_FindDocShell( xDocSh, sFileName,
/*N*/                                   rSection.GetLinkFilePassWd(),
/*N*/                                   sFilter, 0, pDoc->GetDocShell() );
/*N*/               if( nRet )
/*N*/               {
/*N*/                   SwDoc* pSrcDoc = ((SwDocShell*)&xDocSh)->GetDoc();
/*N*/                   eOldRedlineMode = pSrcDoc->GetRedlineMode();
/*N*/                   pSrcDoc->SetRedlineMode( REDLINE_SHOW_INSERT );
/*N*/               }
/*N*/           }
/*N*/
/*N*/           if( nRet )
/*N*/           {
/*N*/               rSection.SetConnectFlag( TRUE );
/*N*/
/*N*/               SwNodeIndex aSave( pPam->GetPoint()->nNode, -1 );
/*N*/               SwNodeRange* pCpyRg = 0;
/*N*/
/*N*/               if( xDocSh->GetMedium() &&
/*N*/                   !rSection.GetLinkFilePassWd().Len() )
/*N*/               {
/*N*/                   const SfxPoolItem* pItem;
/*N*/                   if( SFX_ITEM_SET == xDocSh->GetMedium()->GetItemSet()->
/*N*/                       GetItemState( SID_PASSWORD, FALSE, &pItem ) )
/*?*/                       rSection.SetLinkFilePassWd(
/*?*/                               ((SfxStringItem*)pItem)->GetValue() );
/*N*/               }
/*N*/
/*N*/               SwDoc* pSrcDoc = ((SwDocShell*)&xDocSh)->GetDoc();
/*N*/
/*N*/               if( sRange.Len() )
/*N*/               {
/*N*/                   // Rekursionen abfangen
/*N*/                   BOOL bRecursion = FALSE;
/*N*/                   if( pSrcDoc == pDoc )
/*N*/                   {
/*N*/                       SwServerObjectRef refObj( (SwServerObject*)
/*N*/                                       pDoc->CreateLinkSource( sRange ));
/*N*/                       if( refObj.Is() )
/*N*/                       {
/*N*/                           bRecursion = refObj->IsLinkInServer( this ) ||
/*N*/                                       ChkNoDataFlag();
/*N*/                       }
/*N*/                   }
/*N*/
/*N*/                   SwNodeIndex& rInsPos = pPam->GetPoint()->nNode;
/*N*/
/*N*/                   SwPaM* pCpyPam = 0;
/*N*/                   if( !bRecursion &&
/*N*/                       pSrcDoc->SelectServerObj( sRange, pCpyPam, pCpyRg )
/*N*/                       && pCpyPam )
/*N*/                   {
/*?*/                       if( pSrcDoc != pDoc ||
/*?*/                           pCpyPam->Start()->nNode > rInsPos ||
/*?*/                           rInsPos >= pCpyPam->End()->nNode )
/*?*/                           pSrcDoc->Copy( *pCpyPam, *pPam->GetPoint() );
/*?*/                       delete pCpyPam;
/*N*/                   }
/*N*/                   if( pCpyRg && pSrcDoc == pDoc &&
/*N*/                       pCpyRg->aStart < rInsPos && rInsPos < pCpyRg->aEnd )
/*?*/                       delete pCpyRg, pCpyRg = 0;
/*N*/               }
/*N*/               else if( pSrcDoc != pDoc )
/*N*/                   pCpyRg = new SwNodeRange( pSrcDoc->GetNodes().GetEndOfExtras(), 2,
/*N*/                                         pSrcDoc->GetNodes().GetEndOfContent() );
/*N*/
/*N*/               if( pCpyRg )
/*N*/               {
/*N*/                   SwNodeIndex& rInsPos = pPam->GetPoint()->nNode;
/*N*/                   BOOL bCreateFrm = rInsPos.GetIndex() <=
/*N*/                               pDoc->GetNodes().GetEndOfExtras().GetIndex() ||
/*N*/                               rInsPos.GetNode().FindTableNode();
/*N*/
/*N*/                   SwTblNumFmtMerge aTNFM( *pSrcDoc, *pDoc );
/*N*/
/*N*/                   pSrcDoc->CopyWithFlyInFly( *pCpyRg, rInsPos, bCreateFrm );
/*N*/                   aSave++;
/*N*/
/*N*/                   if( !bCreateFrm )
/*N*/                       ::binfilter::MakeFrms( pDoc, aSave, rInsPos );
/*N*/
/*N*/                   // den letzten Node noch loeschen, aber nur wenn
/*N*/                   // erfolgreich kopiert werden konnte, also der Bereich
/*N*/                   // mehr als 1 Node enthaelt
/*N*/                   if( 2 < pSectNd->EndOfSectionIndex() - pSectNd->GetIndex() )
/*N*/                   {
/*N*/                       aSave = rInsPos;
/*N*/                       pPam->Move( fnMoveBackward, fnGoNode );
/*N*/                       pPam->SetMark();    // beide SwPositions ummelden!
/*N*/
/*N*/                       pDoc->CorrAbs( aSave, *pPam->GetPoint(), 0, TRUE );
/*N*/                       pDoc->GetNodes().Delete( aSave, 1 );
/*N*/                   }
/*N*/                   delete pCpyRg;
/*N*/               }
/*N*/
/*N*/               // update alle Links in diesem Bereich
/*N*/               lcl_UpdateLinksInSect( *this, *pSectNd );
/*N*/           }
/*N*/           if( xDocSh.Is() )
/*N*/           {
/*N*/               if( 2 == nRet )
/*N*/                   xDocSh->DoClose();
/*N*/                 else if( ((SwDocShell*)&xDocSh)->GetDoc() )
/*N*/                   ((SwDocShell*)&xDocSh)->GetDoc()->SetRedlineMode(
/*N*/                               eOldRedlineMode );
/*N*/           }
/*N*/       }
/*N*/       break;
/*N*/   }
/*N*/
/*N*/   // !!!! DDE nur updaten wenn Shell vorhanden ist??
/*N*/   ::com::sun::star::uno::Sequence< sal_Int8 > aSeq;
/*N*/   if( pRead && rValue.hasValue() && ( rValue >>= aSeq ) )
/*N*/   {
/*?*/       DBG_BF_ASSERT(0, "STRIP"); //STRIP001 if( pESh )
//STRIP001 /*?*/        {
//STRIP001 /*?*/            pESh->Push();
//STRIP001 /*?*/            SwPaM* pCrsr = pESh->GetCrsr();
//STRIP001 /*?*/            *pCrsr->GetPoint() = *pPam->GetPoint();
//STRIP001 /*?*/            delete pPam;
//STRIP001 /*?*/            pPam = pCrsr;
//STRIP001 /*?*/        }
//STRIP001 /*?*/
//STRIP001 /*?*/        SvMemoryStream aStrm( (void*)aSeq.getConstArray(), aSeq.getLength(),
//STRIP001 /*?*/                                STREAM_READ );
//STRIP001 /*?*/        aStrm.Seek( 0 );
//STRIP001 /*?*/
//STRIP001 /*?*/ #if OSL_DEBUG_LEVEL > 1
//STRIP001 /*?*/        {
//STRIP001 /*?*/            SvFileStream aDeb( String::CreateFromAscii(
//STRIP001 /*?*/                    "file:///d|/temp/update.txt" ), STREAM_WRITE );
//STRIP001 /*?*/            aDeb << aStrm;
//STRIP001 /*?*/        }
//STRIP001 /*?*/        aStrm.Seek( 0 );
//STRIP001 /*?*/ #endif
//STRIP001 /*?*/
//STRIP001 /*?*/        SwReader aTmpReader( aStrm, aEmptyStr, *pPam );
//STRIP001 /*?*/
//STRIP001 /*?*/        if( !IsError( aTmpReader.Read( *pRead ) ))
//STRIP001 /*?*/            rSection.SetConnectFlag( TRUE );
//STRIP001 /*?*/
//STRIP001 /*?*/        if( pESh )
//STRIP001 /*?*/        {
//STRIP001 /*?*/            pESh->Pop( FALSE );
//STRIP001 /*?*/            pPam = 0;                   // pam is deleted before
//STRIP001 /*?*/        }
/*N*/   }
/*N*/
/*N*/
/*N*/   // Alle UndoActions entfernen und Undo wieder einschalten
/*N*/   pDoc->DelAllUndoObj();
/*N*/   pDoc->DoUndo( bWasUndo );
/*N*/   pDoc->SetVisibleLinks( bWasVisibleLinks );
/*N*/
/*N*/   pDoc->UnlockExpFlds();
/*N*/   if( !pDoc->IsExpFldsLocked() )
/*N*/       pDoc->UpdateExpFlds();
/*N*/
/*N*/   if( pESh )
/*N*/       pESh->EndAllAction();
/*N*/   else if( pVSh )
/*?*/       pVSh->EndAction();
/*N*/   delete pPam;            // wurde am Anfang angelegt
/*N*/ }


//STRIP001 void SwIntrnlSectRefLink::Closed()
//STRIP001 {
//STRIP001  SwDoc* pDoc = rSectFmt.GetDoc();
//STRIP001  if( pDoc && !pDoc->IsInDtor() )
//STRIP001  {
//STRIP001      // Advise verabschiedet sich, den Bereich als nicht geschuetzt
//STRIP001      // kennzeichnen und das Flag umsetzen
//STRIP001
//STRIP001      const SwSectionFmts& rFmts = pDoc->GetSections();
//STRIP001      for( USHORT n = rFmts.Count(); n; )
//STRIP001          if( rFmts[ --n ] == &rSectFmt )
//STRIP001          {
//STRIP001              ViewShell* pSh;
//STRIP001              SwEditShell* pESh = pDoc->GetEditShell( &pSh );
//STRIP001
//STRIP001              if( pESh )
//STRIP001                  pESh->StartAllAction();
//STRIP001              else
//STRIP001                  pSh->StartAction();
//STRIP001
//STRIP001              SwSection aSect( CONTENT_SECTION, aEmptyStr );
//STRIP001              aSect = *rSectFmt.GetSection();
//STRIP001              aSect.SetType( CONTENT_SECTION );
//STRIP001              aSect.SetLinkFileName( aEmptyStr );
//STRIP001              aSect.SetHidden( FALSE );
//STRIP001              aSect.SetProtect( FALSE );
//STRIP001              aSect.SetConnectFlag( FALSE );
//STRIP001
//STRIP001              pDoc->ChgSection( n, aSect );
//STRIP001
//STRIP001              // alle in der Section liegenden Links werden sichtbar
//STRIP001              SwSectionNode* pSectNd = rSectFmt.GetSectionNode( FALSE );
//STRIP001              if( pSectNd )
//STRIP001                  pSectNd->GetSection().MakeChildLinksVisible( *pSectNd );
//STRIP001
//STRIP001              if( pESh )
//STRIP001                  pESh->EndAllAction();
//STRIP001              else
//STRIP001                  pSh->EndAction();
//STRIP001              break;
//STRIP001          }
//STRIP001  }
//STRIP001  SvBaseLink::Closed();
//STRIP001 }


/*N*/ void SwSection::CreateLink( LinkCreateType eCreateType )
/*N*/ {
/*N*/   SwSectionFmt* pFmt = GetFmt();
/*N*/   if( !pFmt || CONTENT_SECTION == eType )
/*?*/       return ;
/*N*/
/*N*/     USHORT nUpdateType = ::so3::LINKUPDATE_ALWAYS;
/*N*/
/*N*/   if( !refLink.Is() )
/*N*/       // dann mal den BaseLink aufbauen
/*N*/       refLink = new SwIntrnlSectRefLink( *pFmt, nUpdateType, FORMAT_RTF );
/*N*/   else
/*N*/       // sonst aus dem Linkmanager entfernen
/*?*/       pFmt->GetDoc()->GetLinkManager().Remove( refLink );
/*N*/
/*N*/   SwIntrnlSectRefLink* pLnk = (SwIntrnlSectRefLink*)&refLink;
/*N*/
/*N*/   String sCmd( sLinkFileName );
/*N*/   xub_StrLen nPos;
/*N*/   while( STRING_NOTFOUND != (nPos = sCmd.SearchAscii( "  " )) )
/*?*/       sCmd.Erase( nPos, 1 );
/*N*/
/*N*/   pLnk->SetUpdateMode( nUpdateType );
/*N*/   pLnk->SetVisible( pFmt->GetDoc()->IsVisibleLinks() );
/*N*/
/*N*/   switch( eType )
/*N*/   {
/*N*/   case DDE_LINK_SECTION:
/*?*/       pLnk->SetLinkSourceName( sCmd );
/*?*/       pFmt->GetDoc()->GetLinkManager().InsertDDELink( pLnk );
/*?*/       break;
/*N*/   case FILE_LINK_SECTION:
/*N*/       {
/*N*/           pLnk->SetContentType( FORMAT_FILE );
/*N*/             String sFltr( sCmd.GetToken( 1, ::so3::cTokenSeperator ) );
/*N*/             String sRange( sCmd.GetToken( 2, ::so3::cTokenSeperator ) );
/*N*/           pFmt->GetDoc()->GetLinkManager().InsertFileLink( *pLnk, eType,
/*N*/                                 sCmd.GetToken( 0, ::so3::cTokenSeperator ),
/*N*/                               ( sFltr.Len() ? &sFltr : 0 ),
/*N*/                               ( sRange.Len() ? &sRange : 0 ) );
/*N*/       }
/*N*/       break;
/*N*/   default:
/*?*/       ASSERT( !this, "Was ist das fuer ein Link?" )
/*N*/   }
/*N*/
/*N*/   switch( eCreateType )
/*N*/   {
/*N*/   case CREATE_CONNECT:            // Link gleich connecten
/*N*/       pLnk->Connect();
/*N*/       break;
/*N*/
/*N*/   case CREATE_UPDATE:         // Link connecten und updaten
/*N*/       pLnk->Update();
/*N*/       break;
/*N*/   }
/*N*/ }

//STRIP001 const SwNode* SwIntrnlSectRefLink::GetAnchor() const
//STRIP001 {
//STRIP001  return rSectFmt.GetSectionNode( FALSE );
//STRIP001 }


/*N*/ BOOL SwIntrnlSectRefLink::IsInRange( ULONG nSttNd, ULONG nEndNd,
/*N*/                                    xub_StrLen nStt, xub_StrLen nEnd ) const
/*N*/ {
/*N*/   SwStartNode* pSttNd = rSectFmt.GetSectionNode( FALSE );
/*N*/   return pSttNd &&
/*N*/           nSttNd < pSttNd->GetIndex() &&
/*N*/           pSttNd->EndOfSectionIndex() < nEndNd;
/*N*/ }



}
