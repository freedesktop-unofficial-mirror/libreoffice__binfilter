/*************************************************************************
 *
 *  $RCSfile: svx_svdetc.cxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 16:21:19 $
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

#ifndef _FORBIDDENCHARACTERSTABLE_HXX
#include "forbiddencharacterstable.hxx"
#endif

#include "svdetc.hxx"
#include "svditext.hxx"
// auto strip #include "svdmodel.hxx"
// auto strip #include "svdtrans.hxx"
// auto strip #include "svdglob.hxx"
#include "svdstr.hrc"
#include "svdviter.hxx"
#include "svdview.hxx"
#include "svdoutl.hxx"

#ifndef _SV_BMPACC_HXX //autogen
#include <vcl/bmpacc.hxx>
#endif

#ifndef _EEITEM_HXX //autogen
#include <eeitem.hxx>
#endif

// auto strip #ifndef _SFXITEMSET_HXX //autogen
// auto strip #include <svtools/itemset.hxx>
// auto strip #endif

// auto strip #ifndef _CONFIG_HXX
// auto strip #include <tools/config.hxx>
// auto strip #endif

#ifndef INCLUDED_SVTOOLS_CACHEOPTIONS_HXX
#include <svtools/cacheoptions.hxx>
#endif

// auto strip #ifndef _SFX_WHITER_HXX //autogen
// auto strip #include <svtools/whiter.hxx>
// auto strip #endif

// auto strip #ifndef _BIGINT_HXX //autogen
// auto strip #include <tools/bigint.hxx>
// auto strip #endif

// auto strip #ifndef _SVX_FONTITEM_HXX //autogen
// auto strip #include "fontitem.hxx"
// auto strip #endif

// auto strip #ifndef _SVX_COLRITEM_HXX //autogen
// auto strip #include "colritem.hxx"
// auto strip #endif

// auto strip #ifndef _SVX_FHGTITEM_HXX //autogen
// auto strip #include "fhgtitem.hxx"
// auto strip #endif

// auto strip #ifndef _SVX__XGRADIENT_HXX //autogen
// auto strip #include "xgrad.hxx"
// auto strip #endif

// auto strip #ifndef SVX_XFILLIT0_HXX //autogen
// auto strip #include "xfillit0.hxx"
// auto strip #endif

#ifndef _SVX_XFLCLIT_HXX //autogen
#include "xflclit.hxx"
#endif

#ifndef _SVX_XFLHTIT_HXX //autogen
#include "xflhtit.hxx"
#endif

#ifndef _SVX_XBTMPIT_HXX //autogen
#include "xbtmpit.hxx"
#endif

#ifndef _SVX_XFLGRIT_HXX //autogen
#include "xflgrit.hxx"
#endif

#ifndef _SVDOOLE2_HXX //autogen
#include "svdoole2.hxx"
#endif

// auto strip #ifndef _SFXITEMPOOL_HXX
// auto strip #include <svtools/itempool.hxx>
// auto strip #endif

// auto strip #ifndef _UNOTOOLS_LOCALEDATAWRAPPER_HXX
// auto strip #include <unotools/localedatawrapper.hxx>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_LANG_LOCALE_HPP_
// auto strip #include <com/sun/star/lang/Locale.hpp>
// auto strip #endif
// auto strip #ifndef _COMPHELPER_PROCESSFACTORY_HXX_
// auto strip #include <comphelper/processfactory.hxx>
// auto strip #endif
// auto strip #ifndef _ISOLANG_HXX
// auto strip #include <tools/isolang.hxx>
// auto strip #endif
// auto strip #ifndef _UNOTOOLS_CHARCLASS_HXX
// auto strip #include <unotools/charclass.hxx>
// auto strip #endif

#ifndef INCLUDED_SVTOOLS_SYSLOCALE_HXX
#include <svtools/syslocale.hxx>
#endif

// #97870#
#ifndef _SVX_XFLBCKIT_HXX
#include "xflbckit.hxx"
#endif
namespace binfilter {

/******************************************************************************
* Globale Daten der DrawingEngine
******************************************************************************/

/*N*/ SdrGlobalData::SdrGlobalData() :
/*N*/   pOutliner(NULL),
/*N*/   pDefaults(NULL),
/*N*/   pResMgr(NULL),
/*N*/   pStrCache(NULL),
/*N*/   nExchangeFormat(0)
/*N*/ {
/*N*/     pSysLocale = new SvtSysLocale;
/*N*/     pCharClass = pSysLocale->GetCharClassPtr();
/*N*/     pLocaleData = pSysLocale->GetLocaleDataPtr();
/*N*/ }

/*N*/ SdrGlobalData::~SdrGlobalData()
/*N*/ {
/*N*/   delete pOutliner;
/*N*/   delete pDefaults;
/*N*/   delete pResMgr;
/*N*/   delete [] pStrCache;
/*N*/     //! do NOT delete pCharClass and pLocaleData
/*N*/     delete pSysLocale;
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ OLEObjCache::OLEObjCache()
/*N*/ : Container( 0 )
/*N*/ {
/*N*/   SvtCacheOptions aCacheOptions;
/*N*/
/*N*/   nSize = aCacheOptions.GetDrawingEngineOLE_Objects();
/*N*/   pTimer = new AutoTimer();
/*N*/     Link aLink = LINK(this, OLEObjCache, UnloadCheckHdl);
/*N*/
/*N*/     pTimer->SetTimeoutHdl(aLink);
/*N*/     pTimer->SetTimeout(20000);
/*N*/     pTimer->Start();
/*N*/
/*N*/   aLink.Call(pTimer);
/*N*/ }

/*N*/ OLEObjCache::~OLEObjCache()
/*N*/ {
/*N*/   pTimer->Stop();
/*N*/   delete pTimer;
/*N*/   // Kein Unload notwendig, da zu diesem Zeitpunkt
/*N*/   // die Objekte nicht mehr vorhanden sind
/*N*/ }

//STRIP001 void OLEObjCache::SetSize(ULONG nNewSize)
//STRIP001 {
//STRIP001  nSize = nNewSize;
//STRIP001 }

/*N*/ void OLEObjCache::InsertObj(SdrOle2Obj* pObj)
/*N*/ {
/*N*/   if (nSize <= Count())
/*N*/   {
/*?*/       // Eintraege reduzieren
/*?*/       ULONG nIndex = Count() - 1;
/*?*/
/*?*/       for (ULONG i = nIndex; i + 1 >= nSize; i--)
/*?*/       {
/*?*/           // Pruefen, ob Objekte entfernt werden koennen
/*?*/           SdrOle2Obj* pCacheObj = (SdrOle2Obj*) GetObject(i);
/*?*/
/*?*/           if ( pCacheObj != pObj &&  UnloadObj(pCacheObj) )
/*?*/           {
/*?*/               Remove(i);
/*?*/           }
/*?*/       }
/*N*/   }
/*N*/
/*N*/   // Objekt ggf. entfernen und an erster Position einfuegen
/*N*/   Remove(pObj);
/*N*/   Insert(pObj, (ULONG) 0L);
/*N*/ }

/*N*/ void OLEObjCache::RemoveObj(SdrOle2Obj* pObj)
/*N*/ {
/*N*/   UnloadObj( (SdrOle2Obj*) Remove(pObj) );
/*N*/ }

/*N*/ BOOL OLEObjCache::UnloadObj(SdrOle2Obj* pObj)
/*N*/ {
/*N*/   BOOL bUnloaded = FALSE;
/*N*/
/*N*/   if (pObj)
/*N*/   {
/*N*/       BOOL bVisible = FALSE;
/*N*/           SdrViewIter aIter(pObj);
/*N*/       SdrView* pView = aIter.FirstView();
/*N*/
/*N*/       while (!bVisible && pView!=NULL)
/*N*/       {
/*?*/           bVisible = !pView->IsGrafDraft();
/*?*/
/*?*/           if (!bVisible)
/*?*/               pView = aIter.NextView();
/*N*/       }
/*N*/
/*N*/       if (!bVisible)
/*N*/           bUnloaded = pObj->Unload();
/*N*/   }
/*N*/
/*N*/   return bUnloaded;
/*N*/ }

/*N*/ IMPL_LINK(OLEObjCache, UnloadCheckHdl, AutoTimer*, pTim)
/*N*/ {
/*N*/   if (nSize <= Count())
/*N*/   {
/*?*/       // Eintraege reduzieren
/*?*/       ULONG nIndex = Count() - 1;
/*?*/
/*?*/       for (ULONG i = nIndex; i + 1 >= nSize; i--)
/*?*/       {
/*?*/           // Pruefen, ob Objekte entfernt werden koennen
/*?*/           SdrOle2Obj* pCacheObj = (SdrOle2Obj*) GetObject(i);
/*?*/
/*?*/           if ( UnloadObj(pCacheObj) )
/*?*/               Remove(i);
/*?*/       }
/*?*/   }
/*N*/
/*N*/     return 0;
/*N*/ }



/*N*/ void ContainerSorter::DoSort(ULONG a, ULONG b) const
/*N*/ {
/*N*/   ULONG nAnz=rCont.Count();
/*N*/   if (b>nAnz) b=nAnz;
/*N*/   if (b>0) b--;
/*N*/   if (a<b) ImpSubSort(a,b);
/*N*/ }

//STRIP001 void ContainerSorter::Is1stLessThan2nd(const void* pElem1, const void* pElem2) const
//STRIP001 {
//STRIP001 }

/*?*/ void ContainerSorter::ImpSubSort(long nL, long nR) const
/*?*/ {
/*?*/   long i,j;
/*?*/   const void* pX;
/*?*/   void* pI;
/*?*/   void* pJ;
/*?*/   i=nL;
/*?*/   j=nR;
/*?*/   pX=rCont.GetObject((nL+nR)/2);
/*?*/   do {
/*?*/       pI=rCont.Seek(i);
/*?*/       while (pI!=pX && Compare(pI,pX)<0) { i++; pI=rCont.Next(); }
/*?*/       pJ=rCont.Seek(j);
/*?*/       while (pJ!=pX && Compare(pX,pJ)<0) { j--; pJ=rCont.Prev(); }
/*?*/       if (i<=j) {
/*?*/           rCont.Replace(pJ,i);
/*?*/           rCont.Replace(pI,j);
/*?*/           i++;
/*?*/           j--;
/*?*/       }
/*?*/   } while (i<=j);
/*?*/   if (nL<j) ImpSubSort(nL,j);
/*?*/   if (i<nR) ImpSubSort(i,nR);
/*?*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 class ImpUShortContainerSorter: public ContainerSorter {
//STRIP001 public:
//STRIP001  ImpUShortContainerSorter(Container& rNewCont): ContainerSorter(rNewCont) {}
//STRIP001  virtual int Compare(const void* pElem1, const void* pElem2) const;
//STRIP001 };

//STRIP001 int ImpUShortContainerSorter::Compare(const void* pElem1, const void* pElem2) const
//STRIP001 {
//STRIP001  USHORT n1=USHORT(ULONG(pElem1));
//STRIP001  USHORT n2=USHORT(ULONG(pElem2));
//STRIP001  return n1<n2 ? -1 : n1>n2 ? 1 : 0;
//STRIP001 }

//STRIP001 void UShortCont::Sort()
//STRIP001 {
//STRIP001  ImpUShortContainerSorter aSorter(aArr);
//STRIP001  aSorter.DoSort();
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*?*/ class ImpClipMerk {
/*?*/   Region aClip;
/*?*/   FASTBOOL   bClip;
/*?*/ public:
/*?*/   ImpClipMerk(const OutputDevice& rOut): aClip(rOut.GetClipRegion()),bClip(rOut.IsClipRegion()) {}
/*?*/   void Restore(OutputDevice& rOut)
/*?*/   {
/*?*/       // Kein Clipping in die Metafileaufzeichnung
/*?*/       GDIMetaFile* pMtf=rOut.GetConnectMetaFile();
/*?*/       if (pMtf!=NULL && (!pMtf->IsRecord() || pMtf->IsPause())) pMtf=NULL;
/*?*/       if (pMtf!=NULL) pMtf->Pause(TRUE);
/*?*/       if (bClip) rOut.SetClipRegion(aClip);
/*?*/       else rOut.SetClipRegion();
/*?*/       if (pMtf!=NULL) pMtf->Pause(FALSE);
/*?*/   }
/*?*/ };
/*?*/
/*?*/ class ImpColorMerk {
/*?*/   Color aLineColor;
/*?*/   Color aFillColor;
/*?*/   Color aBckgrdColor;
/*?*/   Font  aFont;
/*?*/ public:
/*?*/   ImpColorMerk(const OutputDevice& rOut):
/*?*/       aLineColor( rOut.GetLineColor() ),
/*?*/       aFillColor( rOut.GetFillColor() ),
/*?*/       aBckgrdColor( rOut.GetBackground().GetColor() ),
/*?*/       aFont (rOut.GetFont()) {}
/*?*/
/*?*/   ImpColorMerk(const OutputDevice& rOut, USHORT nMode)
/*?*/   {
/*?*/       if ( (nMode & SDRHDC_SAVEPEN) == SDRHDC_SAVEPEN )
/*?*/           aLineColor = rOut.GetLineColor();
/*?*/
/*?*/       if ( (nMode & SDRHDC_SAVEBRUSH) == SDRHDC_SAVEBRUSH)
/*?*/       {
/*?*/           aFillColor = rOut.GetFillColor();
/*?*/           aBckgrdColor = rOut.GetBackground().GetColor();
/*?*/       }
/*?*/
/*?*/       if ( (nMode & SDRHDC_SAVEFONT) == SDRHDC_SAVEFONT)
/*?*/           aFont=rOut.GetFont();
/*?*/   }
/*?*/
/*?*/   void Restore(OutputDevice& rOut, USHORT nMode=SDRHDC_SAVEPENANDBRUSHANDFONT)
/*?*/   {
/*?*/       if ( (nMode & SDRHDC_SAVEPEN) == SDRHDC_SAVEPEN)
/*?*/           rOut.SetLineColor( aLineColor );
/*?*/
/*?*/       if ( (nMode & SDRHDC_SAVEBRUSH) == SDRHDC_SAVEBRUSH)
/*?*/       {
/*?*/           rOut.SetFillColor( aFillColor );
/*?*/           rOut.SetBackground( Wallpaper( aBckgrdColor ) );
/*?*/       }
/*?*/       if ((nMode & SDRHDC_SAVEFONT) ==SDRHDC_SAVEFONT)
/*?*/       {
/*?*/           if (!rOut.GetFont().IsSameInstance(aFont))
/*?*/           {
/*?*/               rOut.SetFont(aFont);
/*?*/           }
/*?*/       }
/*?*/   }
/*?*/
/*?*/   const Color& GetLineColor() const { return aLineColor; }
/*?*/ };

/*N*/ ImpSdrHdcMerk::ImpSdrHdcMerk(const OutputDevice& rOut, USHORT nNewMode, FASTBOOL bAutoMerk):
/*N*/   pFarbMerk(NULL),
/*N*/   pClipMerk(NULL),
/*N*/   pLineColorMerk(NULL),
/*N*/   nMode(nNewMode)
/*N*/ {
/*N*/   if (bAutoMerk) Save(rOut);
/*N*/ }

/*N*/ ImpSdrHdcMerk::~ImpSdrHdcMerk()
/*N*/ {
/*N*/   if (pFarbMerk!=NULL) delete pFarbMerk;
/*N*/   if (pClipMerk!=NULL) delete pClipMerk;
/*N*/   if (pLineColorMerk !=NULL) delete pLineColorMerk;
/*N*/ }

/*N*/ void ImpSdrHdcMerk::Save(const OutputDevice& rOut)
/*N*/ {
/*N*/   if (pFarbMerk!=NULL)
/*N*/   {
/*N*/       delete pFarbMerk;
/*N*/       pFarbMerk=NULL;
/*N*/   }
/*N*/   if (pClipMerk!=NULL)
/*N*/   {
/*N*/       delete pClipMerk;
/*N*/       pClipMerk=NULL;
/*N*/   }
/*N*/   if (pLineColorMerk !=NULL)
/*N*/   {
/*N*/       delete pLineColorMerk ;
/*N*/       pLineColorMerk =NULL;
/*N*/   }
/*N*/   if ((nMode & SDRHDC_SAVECLIPPING) ==SDRHDC_SAVECLIPPING)
/*N*/       pClipMerk=new ImpClipMerk(rOut);
/*N*/
/*N*/   USHORT nCol=nMode & SDRHDC_SAVEPENANDBRUSHANDFONT;
/*N*/
/*N*/   if (nCol==SDRHDC_SAVEPEN)
/*N*/       pLineColorMerk=new Color( rOut.GetLineColor() );
/*N*/   else if (nCol==SDRHDC_SAVEPENANDBRUSHANDFONT)
/*N*/       pFarbMerk=new ImpColorMerk(rOut);
/*N*/   else if (nCol!=0)
/*N*/       pFarbMerk=new ImpColorMerk(rOut,nCol);
/*N*/ }

/*N*/ void ImpSdrHdcMerk::Restore(OutputDevice& rOut, USHORT nMask) const
/*N*/ {
/*N*/   nMask&=nMode; // nur restaurieren, was auch gesichert wurde
/*N*/
/*N*/   if ((nMask & SDRHDC_SAVECLIPPING) ==SDRHDC_SAVECLIPPING && pClipMerk!=NULL)
/*N*/       pClipMerk->Restore(rOut);
/*N*/
/*N*/   USHORT nCol=nMask & SDRHDC_SAVEPENANDBRUSHANDFONT;
/*N*/
/*N*/   if (nCol==SDRHDC_SAVEPEN)
/*N*/   {
/*N*/       if (pLineColorMerk!=NULL)
/*N*/           rOut.SetLineColor(*pLineColorMerk);
/*N*/       else if (pFarbMerk!=NULL)
/*N*/           rOut.SetLineColor( pFarbMerk->GetLineColor() );
/*N*/   } else if (nCol!=0 && pFarbMerk!=NULL)
/*N*/       pFarbMerk->Restore(rOut,nCol);
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ void SdrLinkList::Clear()
/*N*/ {
/*N*/   unsigned nAnz=GetLinkCount();
/*N*/   for (unsigned i=0; i<nAnz; i++) {
/*N*/       delete (Link*)aList.GetObject(i);
/*N*/   }
/*N*/   aList.Clear();
/*N*/ }

/*N*/ unsigned SdrLinkList::FindEntry(const Link& rLink) const
/*N*/ {
/*N*/   unsigned nAnz=GetLinkCount();
/*N*/   for (unsigned i=0; i<nAnz; i++) {
/*N*/       if (GetLink(i)==rLink) return i;
/*N*/   }
/*N*/   return 0xFFFF;
/*N*/ }

/*N*/ void SdrLinkList::InsertLink(const Link& rLink, unsigned nPos)
/*N*/ {
/*N*/   unsigned nFnd=FindEntry(rLink);
/*N*/   if (nFnd==0xFFFF) {
/*N*/       if (rLink.IsSet()) {
/*N*/           aList.Insert(new Link(rLink),nPos);
/*N*/       } else {
/*N*/           DBG_ERROR("SdrLinkList::InsertLink(): Versuch, einen nicht gesetzten Link einzufuegen");
/*N*/       }
/*N*/   } else {
/*N*/       DBG_ERROR("SdrLinkList::InsertLink(): Link schon vorhanden");
/*N*/   }
/*N*/ }
/*N*/
/*N*/ void SdrLinkList::RemoveLink(const Link& rLink)
/*N*/ {
/*N*/   unsigned nFnd=FindEntry(rLink);
/*N*/   if (nFnd!=0xFFFF) {
/*N*/       Link* pLink=(Link*)aList.Remove(nFnd);
/*N*/       delete pLink;
/*N*/   } else {
/*N*/       DBG_ERROR("SdrLinkList::RemoveLink(): Link nicht gefunden");
/*N*/   }
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////
// #98988# Re-implement GetDraftFillColor(...)

/*N*/ FASTBOOL GetDraftFillColor(const SfxItemSet& rSet, Color& rCol)
/*N*/ {
/*N*/   XFillStyle eFill=((XFillStyleItem&)rSet.Get(XATTR_FILLSTYLE)).GetValue();
/*N*/   FASTBOOL bRetval(FALSE);
/*N*/
/*N*/   switch(eFill)
/*N*/   {
/*N*/       case XFILL_SOLID:
/*N*/       {
/*N*/           rCol = ((XFillColorItem&)rSet.Get(XATTR_FILLCOLOR)).GetValue();
/*N*/           bRetval = TRUE;
/*N*/
/*N*/           break;
/*N*/       }
/*N*/       case XFILL_HATCH:
/*N*/       {
/*?*/           Color aCol1(((XFillHatchItem&)rSet.Get(XATTR_FILLHATCH)).GetValue().GetColor());
/*?*/           Color aCol2(COL_WHITE);
/*?*/
/*?*/           // #97870# when hatch background is activated, use object fill color as hatch color
/*?*/           sal_Bool bFillHatchBackground = ((const XFillBackgroundItem&)(rSet.Get(XATTR_FILLBACKGROUND))).GetValue();
/*?*/           if(bFillHatchBackground)
/*?*/           {
/*?*/               aCol2 = ((const XFillColorItem&)(rSet.Get(XATTR_FILLCOLOR))).GetValue();
/*?*/           }
/*?*/
/*?*/           ((B3dColor&)rCol).CalcMiddle(aCol1, aCol2);
/*?*/           bRetval = TRUE;
/*?*/
/*?*/           break;
/*N*/       }
/*N*/       case XFILL_GRADIENT: {
/*N*/           const XGradient& rGrad=((XFillGradientItem&)rSet.Get(XATTR_FILLGRADIENT)).GetValue();
/*N*/           Color aCol1(rGrad.GetStartColor());
/*N*/           Color aCol2(rGrad.GetEndColor());
/*N*/           ((B3dColor&)rCol).CalcMiddle(aCol1, aCol2);
/*N*/           bRetval = TRUE;
/*N*/
/*N*/           break;
/*N*/       }
/*N*/       case XFILL_BITMAP:
/*N*/       {
/*?*/           const Bitmap& rBitmap = ((XFillBitmapItem&)rSet.Get(XATTR_FILLBITMAP)).GetValue().GetBitmap();
/*?*/           const Size aSize(rBitmap.GetSizePixel());
/*?*/           const sal_uInt32 nWidth = aSize.Width();
/*?*/           const sal_uInt32 nHeight = aSize.Height();
/*?*/           Bitmap aBitmap(rBitmap);
/*?*/           BitmapReadAccess* pAccess = aBitmap.AcquireReadAccess();
/*?*/
/*?*/           if(pAccess && nWidth > 0 && nHeight > 0)
/*?*/           {
/*?*/               sal_uInt32 nRt(0L);
/*?*/               sal_uInt32 nGn(0L);
/*?*/               sal_uInt32 nBl(0L);
/*?*/               const sal_uInt32 nMaxSteps(8L);
/*?*/               const sal_uInt32 nXStep((nWidth > nMaxSteps) ? nWidth / nMaxSteps : 1L);
/*?*/               const sal_uInt32 nYStep((nHeight > nMaxSteps) ? nHeight / nMaxSteps : 1L);
/*?*/               sal_uInt32 nAnz(0L);
/*?*/
/*?*/               for(sal_uInt32 nY(0L); nY < nHeight; nY += nYStep)
/*?*/               {
/*?*/                   for(sal_uInt32 nX(0L); nX < nWidth; nX += nXStep)
/*?*/                   {
/*?*/                       const BitmapColor& rCol = (pAccess->HasPalette())
/*?*/                           ? pAccess->GetPaletteColor((BYTE)pAccess->GetPixel(nY, nX))
/*?*/                           : pAccess->GetPixel(nY, nX);
/*?*/
/*?*/                       nRt += rCol.GetRed();
/*?*/                       nGn += rCol.GetGreen();
/*?*/                       nBl += rCol.GetBlue();
/*?*/                       nAnz++;
/*?*/                   }
/*?*/               }
/*?*/
/*?*/               nRt /= nAnz;
/*?*/               nGn /= nAnz;
/*?*/               nBl /= nAnz;
/*?*/
/*?*/               rCol = Color(UINT8(nRt), UINT8(nGn), UINT8(nBl));
/*?*/
/*?*/               bRetval = TRUE;
/*?*/           }
/*?*/
/*?*/           if(pAccess)
/*?*/           {
/*?*/               aBitmap.ReleaseAccess(pAccess);
/*?*/           }
/*?*/
/*?*/           break;
/*?*/       }
/*N*/   }
/*N*/
/*N*/   return bRetval;
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ SdrEngineDefaults::SdrEngineDefaults():
/*N*/   aFontName( OutputDevice::GetDefaultFont( DEFAULTFONT_SERIF, LANGUAGE_SYSTEM, DEFAULTFONT_FLAGS_ONLYONE ).GetName() ),
/*N*/   eFontFamily(FAMILY_ROMAN),
/*N*/   aFontColor(COL_AUTO),
/*N*/   nFontHeight(847),             // 847/100mm = ca. 24 Point
/*N*/   eMapUnit(MAP_100TH_MM),
/*N*/   aMapFraction(1,1)
/*N*/ {
/*N*/ }
/*N*/
/*N*/ SdrEngineDefaults& SdrEngineDefaults::GetDefaults()
/*N*/ {
/*N*/   SdrGlobalData& rGlobalData=GetSdrGlobalData();
/*N*/   if (rGlobalData.pDefaults==NULL) {
/*N*/       rGlobalData.pDefaults=new SdrEngineDefaults;
/*N*/   }
/*N*/   return *rGlobalData.pDefaults;
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 void SdrEngineDefaults::LanguageHasChanged()
//STRIP001 {
//STRIP001  SdrGlobalData& rGlobalData=GetSdrGlobalData();
//STRIP001  if (rGlobalData.pResMgr!=NULL) {
//STRIP001      delete rGlobalData.pResMgr;
//STRIP001      rGlobalData.pResMgr=NULL;
//STRIP001  }
//STRIP001  if (rGlobalData.pStrCache!=NULL) {
//STRIP001      delete [] rGlobalData.pStrCache;
//STRIP001      rGlobalData.pStrCache=NULL;
//STRIP001  }
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ SdrOutliner* SdrMakeOutliner( USHORT nOutlinerMode, SdrModel* pModel )
/*N*/ {
/*N*/   SdrEngineDefaults& rDefaults = SdrEngineDefaults::GetDefaults();

/*
    MapUnit  eUn( (pMod==NULL) ? rDefaults.eMapUnit : pMod->GetScaleUnit());
    Fraction aFr( *((pMod==NULL) ? &rDefaults.aMapFraction : &pMod->GetScaleFraction()));

    if ( pMod->GetRefDevice() )
        pOutl->SetRefDevice( pMod->GetRefDevice() );
    else
    {
        MapMode aMapMode(eUn,Point(0,0),aFr,aFr);
        pOutl->SetRefMapMode( aMapMode );
    }

    SfxItemSet aSet(pOutl->GetEmptyItemSet());
    aSet.Put(SvxFontItem(rDefaults.eFontFamily, rDefaults.aFontName, String(), PITCH_DONTKNOW, gsl_getSystemTextEncoding() ) );
    aSet.Put(SvxColorItem(rDefaults.aFontColor));
    ULONG nHgt=rDefaults.nFontHeight;
    FASTBOOL bDifUn=(eUn!=rDefaults.eMapUnit); // different MapUnits
    FASTBOOL bDifFr=(aFr!=rDefaults.aMapFraction); // different MapFractions
    if (bDifUn || bDifFr) { // Wenn pMod!=NULL und pMod->Map!=rDef.Map
        long nTmpLong=long(nHgt); // caasting im Ctor bringt unter MSVC sehr merkwuerdige Fehlermeldungen
        BigInt aHgt1(nTmpLong); // umrechnen von DefMap in ModMap
        FrPair aUnitMul(GetMapFactor(rDefaults.eMapUnit,eUn));

        if (bDifUn) aHgt1*=aUnitMul.Y().GetNumerator();
        if (bDifFr) aHgt1*=aFr.GetNumerator();
        if (bDifFr) aHgt1*=rDefaults.aMapFraction.GetDenominator();
        if (bDifUn) aHgt1/=aUnitMul.Y().GetDenominator();
        if (bDifFr) aHgt1/=aFr.GetDenominator();
        if (bDifFr) aHgt1/=rDefaults.aMapFraction.GetNumerator();

        nHgt=ULONG(long(aHgt1));
    }
    aSet.Put(SvxFontHeightItem(nHgt));
    pOutl->SetDefaults(aSet);
*/

/*N*/   SfxItemPool* pPool = &pModel->GetItemPool();
/*N*/   SdrOutliner* pOutl = new SdrOutliner( pPool, nOutlinerMode );
/*N*/   pOutl->SetEditTextObjectPool( pPool );
/*N*/   pOutl->SetStyleSheetPool( (SfxStyleSheetPool*) pModel->GetStyleSheetPool() );
/*N*/   pOutl->SetDefTab( pModel->GetDefaultTabulator() );
/*N*/   pOutl->SetForbiddenCharsTable( pModel->GetForbiddenCharsTable() );
/*N*/   pOutl->SetAsianCompressionMode( pModel->GetCharCompressType() );
/*N*/   pOutl->SetKernAsianPunctuation( pModel->IsKernAsianPunctuation() );
/*N*/
/*N*/   return pOutl;
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////


/*N*/ SdrLinkList& ImpGetUserMakeObjHdl()
/*N*/ {
/*N*/   SdrGlobalData& rGlobalData=GetSdrGlobalData();
/*N*/   return rGlobalData.aUserMakeObjHdl;
/*N*/ }

/*N*/ SdrLinkList& ImpGetUserMakeObjUserDataHdl()
/*N*/ {
/*N*/   SdrGlobalData& rGlobalData=GetSdrGlobalData();
/*N*/   return rGlobalData.aUserMakeObjUserDataHdl;
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ ResMgr* ImpGetResMgr()
/*N*/ {
/*N*/   SdrGlobalData& rGlobalData = GetSdrGlobalData();
/*N*/
/*N*/   if(!rGlobalData.pResMgr)
/*N*/   {
/*N*/ #ifndef SVX_LIGHT
/*N*/       ByteString aName("bf_svx");         //STRIP005
/*N*/ #else
/*N*/       ByteString aName("bf_svl");         //STRIP005
/*N*/ #endif
/*N*/       INT32 nSolarUpd(SOLARUPD);
/*N*/       aName += ByteString::CreateFromInt32( nSolarUpd );
/*N*/       rGlobalData.pResMgr =
/*N*/             ResMgr::CreateResMgr( aName.GetBuffer(), Application::GetSettings().GetUILocale() );
/*N*/   }
/*N*/
/*N*/   return rGlobalData.pResMgr;
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ const XubString& ImpGetResStr(USHORT nResID)
/*N*/ {
/*N*/   SdrGlobalData& rGlobalData=GetSdrGlobalData();
/*N*/   if (rGlobalData.pStrCache==NULL) {
/*N*/       USHORT nAnz=SDR_StringCacheEnd-SDR_StringCacheBegin+1;
/*N*/       rGlobalData.pStrCache=new XubString[nAnz];
/*N*/       XubString* pStr=rGlobalData.pStrCache;
/*N*/       ResMgr* pResMgr=ImpGetResMgr();
/*N*/       for (USHORT i=0; i<nAnz; i++) {
/*N*/           USHORT nResNum=SDR_StringCacheBegin+i;
/*N*/           {
/*N*/               pStr[i]=XubString(ResId(nResNum,pResMgr));
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/   if (nResID>=SDR_StringCacheBegin && nResID<=SDR_StringCacheEnd) {
/*N*/       return rGlobalData.pStrCache[nResID-SDR_StringCacheBegin];
/*N*/   } else {
/*N*/ #ifdef DBG_UTIL
/*N*/       DBG_ERROR("ImpGetResStr(): ResourceID outside of cache range!");
/*N*/ #endif
/*N*/       static String aEmpty;
/*N*/       return aEmpty;
/*N*/   }
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 BOOL SearchOutlinerItems(const SfxItemSet& rSet, BOOL bInklDefaults, BOOL* pbOnlyEE)
//STRIP001 {
//STRIP001  BOOL bHas=FALSE;
//STRIP001  BOOL bOnly=TRUE;
//STRIP001  BOOL bLookOnly=pbOnlyEE!=NULL;
//STRIP001  SfxWhichIter aIter(rSet);
//STRIP001  USHORT nWhich=aIter.FirstWhich();
//STRIP001  while (((bLookOnly && bOnly) || !bHas) && nWhich!=0) {
//STRIP001      // bei bInklDefaults ist der gesamte Which-Range
//STRIP001      // ausschlaggebend, ansonsten nur die gesetzten Items
//STRIP001      // Disabled und DontCare wird als Loch im Which-Range betrachtet
//STRIP001      SfxItemState eState=rSet.GetItemState(nWhich);
//STRIP001      if ((eState==SFX_ITEM_DEFAULT && bInklDefaults) || eState==SFX_ITEM_SET) {
//STRIP001          if (nWhich<EE_ITEMS_START || nWhich>EE_ITEMS_END) bOnly=FALSE;
//STRIP001          else bHas=TRUE;
//STRIP001      }
//STRIP001      nWhich=aIter.NextWhich();
//STRIP001  }
//STRIP001  if (!bHas) bOnly=FALSE;
//STRIP001  if (pbOnlyEE!=NULL) *pbOnlyEE=bOnly;
//STRIP001  return bHas;
//STRIP001 }

//STRIP001 USHORT* RemoveWhichRange(const USHORT* pOldWhichTable, USHORT nRangeBeg, USHORT nRangeEnd)
//STRIP001 {
//STRIP001  // insgesamt sind 6 Faelle moeglich (je Range):
//STRIP001  //         [Beg..End]          zu entfernender Range
//STRIP001  // [b..e]    [b..e]    [b..e]  Fall 1,3,2: egal, ganz weg, egal  + Ranges
//STRIP001  // [b........e]  [b........e]  Fall 4,5  : Bereich verkleinern   | in
//STRIP001  // [b......................e]  Fall 6    : Splitting             + pOldWhichTable
//STRIP001  USHORT nAnz=0;
//STRIP001  while (pOldWhichTable[nAnz]!=0) nAnz++;
//STRIP001  nAnz++; // nAnz muesste nun in jedem Fall eine ungerade Zahl sein (0 am Ende des Arrays)
//STRIP001  DBG_ASSERT((nAnz&1)==1,"Joe: RemoveWhichRange: WhichTable hat keine ungerade Anzahl von Eintraegen");
//STRIP001  USHORT nAlloc=nAnz;
//STRIP001  // benoetigte Groesse des neuen Arrays ermitteln
//STRIP001  USHORT nNum=nAnz-1;
//STRIP001  while (nNum!=0) {
//STRIP001      nNum-=2;
//STRIP001      USHORT nBeg=pOldWhichTable[nNum];
//STRIP001      USHORT nEnd=pOldWhichTable[nNum+1];
//STRIP001      if (nEnd<nRangeBeg)  /*nCase=1*/ ;
//STRIP001      else if (nBeg>nRangeEnd) /* nCase=2 */ ;
//STRIP001      else if (nBeg>=nRangeBeg && nEnd<=nRangeEnd) /* nCase=3 */ nAlloc-=2;
//STRIP001      else if (nEnd<=nRangeEnd) /* nCase=4 */;
//STRIP001      else if (nBeg>=nRangeBeg) /* nCase=5*/ ;
//STRIP001      else /* nCase=6 */ nAlloc+=2;
//STRIP001  }
//STRIP001
//STRIP001  USHORT* pNewWhichTable=new USHORT[nAlloc];
//STRIP001  memcpy(pNewWhichTable,pOldWhichTable,nAlloc*sizeof(USHORT));
//STRIP001  pNewWhichTable[nAlloc-1]=0; // im Falle 3 fehlt die 0 am Ende
//STRIP001  // nun die unerwuenschten Ranges entfernen
//STRIP001  nNum=nAlloc-1;
//STRIP001  while (nNum!=0) {
//STRIP001      nNum-=2;
//STRIP001      USHORT nBeg=pNewWhichTable[nNum];
//STRIP001      USHORT nEnd=pNewWhichTable[nNum+1];
//STRIP001      unsigned nCase=0;
//STRIP001      if (nEnd<nRangeBeg) nCase=1;
//STRIP001      else if (nBeg>nRangeEnd) nCase=2;
//STRIP001      else if (nBeg>=nRangeBeg && nEnd<=nRangeEnd) nCase=3;
//STRIP001      else if (nEnd<=nRangeEnd) nCase=4;
//STRIP001      else if (nBeg>=nRangeBeg) nCase=5;
//STRIP001      else nCase=6;
//STRIP001      switch (nCase) {
//STRIP001          case 3: {
//STRIP001              unsigned nTailBytes=(nAnz-(nNum+2))*sizeof(USHORT);
//STRIP001              memcpy(&pNewWhichTable[nNum],&pNewWhichTable[nNum+2],nTailBytes);
//STRIP001              nAnz-=2; // Merken: Array hat sich verkleinert
//STRIP001          } break;
//STRIP001          case 4: pNewWhichTable[nNum+1]=nRangeBeg-1; break;
//STRIP001          case 5: pNewWhichTable[nNum]=nRangeEnd+1;     break;
//STRIP001          case 6: {
//STRIP001              unsigned nTailBytes=(nAnz-(nNum+2))*sizeof(USHORT);
//STRIP001              memcpy(&pNewWhichTable[nNum+4],&pNewWhichTable[nNum+2],nTailBytes);
//STRIP001              nAnz+=2; // Merken: Array hat sich vergroessert
//STRIP001              pNewWhichTable[nNum+2]=nRangeEnd+1;
//STRIP001              pNewWhichTable[nNum+3]=pNewWhichTable[nNum+1];
//STRIP001              pNewWhichTable[nNum+1]=nRangeBeg-1;
//STRIP001          } break;
//STRIP001      } // switch
//STRIP001  }
//STRIP001  return pNewWhichTable;
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 SvdProgressInfo::SvdProgressInfo( Link *_pLink )
//STRIP001 {
//STRIP001  DBG_ASSERT(_pLink!=NULL,"SvdProgressInfo(): Kein Link angegeben!!");
//STRIP001
//STRIP001  pLink = _pLink;
//STRIP001  nSumActionCount = 0;
//STRIP001  nSumCurAction   = 0;
//STRIP001
//STRIP001  nObjCount = 0;
//STRIP001  nCurObj   = 0;
//STRIP001
//STRIP001  nActionCount = 0;
//STRIP001  nCurAction   = 0;
//STRIP001
//STRIP001  nInsertCount = 0;
//STRIP001  nCurInsert   = 0;
//STRIP001 }

//STRIP001 void SvdProgressInfo::Init( ULONG _nSumActionCount, ULONG _nObjCount )
//STRIP001 {
//STRIP001  nSumActionCount = _nSumActionCount;
//STRIP001  nObjCount = _nObjCount;
//STRIP001 }

//STRIP001 BOOL SvdProgressInfo::ReportActions( ULONG nAnzActions )
//STRIP001 {
//STRIP001  nSumCurAction += nAnzActions;
//STRIP001  nCurAction += nAnzActions;
//STRIP001  if(nCurAction > nActionCount)
//STRIP001      nCurAction = nActionCount;
//STRIP001
//STRIP001  return pLink->Call(NULL) == 1L;
//STRIP001 }

//STRIP001 BOOL SvdProgressInfo::ReportInserts( ULONG nAnzInserts )
//STRIP001 {
//STRIP001  nSumCurAction += nAnzInserts;
//STRIP001  nCurInsert += nAnzInserts;
//STRIP001
//STRIP001  return pLink->Call(NULL) == 1L;
//STRIP001 }

//STRIP001 BOOL SvdProgressInfo::ReportRescales( ULONG nAnzRescales )
//STRIP001 {
//STRIP001  nSumCurAction += nAnzRescales;
//STRIP001  return pLink->Call(NULL) == 1L;
//STRIP001 }

//STRIP001 void SvdProgressInfo::SetActionCount( ULONG _nActionCount )
//STRIP001 {
//STRIP001  nActionCount = _nActionCount;
//STRIP001 }

//STRIP001 void SvdProgressInfo::SetInsertCount( ULONG _nInsertCount )
//STRIP001 {
//STRIP001  nInsertCount = _nInsertCount;
//STRIP001 }

//STRIP001 BOOL SvdProgressInfo::SetNextObject()
//STRIP001 {
//STRIP001  nActionCount = 0;
//STRIP001  nCurAction   = 0;
//STRIP001
//STRIP001  nInsertCount = 0;
//STRIP001  nCurInsert   = 0;
//STRIP001
//STRIP001  nCurObj++;
//STRIP001  return ReportActions(0);
//STRIP001 }

//STRIP001 void SvdProgressInfo::ReportError()
//STRIP001 {
//STRIP001  pLink->Call((void *)1L);
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////



}
