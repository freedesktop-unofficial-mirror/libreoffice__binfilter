/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svx_svdhdl.cxx,v $
 *
 *  $Revision: 1.8 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-27 21:39:09 $
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

#include "svdetc.hxx"
#include "svdmrkv.hxx"







#include "svdstr.hrc"


// #105678#
namespace binfilter {

////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////





////////////////////////////////////////////////////////////////////////////////////////////////////


// #101928#

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ SdrHdl::SdrHdl()//STRIP001 :
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/ }

/*N*/ SdrHdl::SdrHdl(const Point& rPnt, SdrHdlKind eNewKind)//STRIP001 :
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/ }

/*N*/ SdrHdl::~SdrHdl()
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/ }











// #101928#




// #97016# II

////////////////////////////////////////////////////////////////////////////////////////////////////
// class SdrHdlColor









////////////////////////////////////////////////////////////////////////////////////////////////////
// class SdrHdlGradient







////////////////////////////////////////////////////////////////////////////////////////////////////





////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////






////////////////////////////////////////////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ class ImpSdrHdlListSorter: public ContainerSorter {
/*N*/ public:
/*N*/     ImpSdrHdlListSorter(Container& rNewCont): ContainerSorter(rNewCont) {}
/*N*/     virtual int Compare(const void* pElem1, const void* pElem2) const;
/*N*/ };

/*N*/ int ImpSdrHdlListSorter::Compare(const void* pElem1, const void* pElem2) const
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); return 0;//STRIP001
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////
// #97016# II

/*N*/ class ImplHdlListData
/*N*/ {
/*N*/ public:
/*N*/   sal_uInt32                  mnFocusIndex;
/*N*/   SdrMarkView*                pView;
/*N*/
/*N*/   ImplHdlListData(SdrMarkView* pV): mnFocusIndex(CONTAINER_ENTRY_NOTFOUND), pView(pV) {}
/*N*/ };


// #105678# Help struct for re-sorting handles
struct ImplHdlAndIndex
{
    SdrHdl*                     mpHdl;
    sal_uInt32                  mnIndex;
};

// #105678# Help method for sorting handles taking care of OrdNums, keeping order in
// single objects and re-sorting polygon handles intuitively

////////////////////////////////////////////////////////////////////////////////////////////////////
// #97016# II


/*N*/ SdrHdl* SdrHdlList::GetFocusHdl() const
/*N*/ {
/*N*/   if(pImpl->mnFocusIndex != CONTAINER_ENTRY_NOTFOUND && pImpl->mnFocusIndex < GetHdlCount())
/*?*/       return GetHdl(pImpl->mnFocusIndex);
/*N*/   else
/*?*/       return 0L;
/*N*/ }


/*N*/ void SdrHdlList::ResetFocusHdl()
/*N*/ {
/*N*/   SdrHdl* pHdl = GetFocusHdl();
/*N*/
/*N*/   pImpl->mnFocusIndex = CONTAINER_ENTRY_NOTFOUND;
/*N*/
/*N*/   if(pHdl)
/*N*/   {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/   }
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ SdrHdlList::SdrHdlList(SdrMarkView* pV)
/*N*/ : aList(1024,32,32),
/*N*/   pImpl(new ImplHdlListData(pV))
/*N*/   //#97016# II
/*N*/   //pView(pV)
/*N*/ {
/*N*/   nHdlSize = 3;
/*N*/   bRotateShear = FALSE;
/*N*/   bMoveOutside = FALSE;
/*N*/   bDistortShear = FALSE;
/*N*/   bFineHandles = FALSE;
/*N*/ }
/*N*/
/*N*/ SdrHdlList::~SdrHdlList()
/*N*/ {
/*N*/   Clear();
/*N*/   //#97016# II
/*N*/   delete pImpl;
/*N*/ }



/*N*/ void SdrHdlList::SetRotateShear(BOOL bOn)
/*N*/ {
/*N*/   bRotateShear = bOn;
/*N*/ }

/*N*/ void SdrHdlList::SetDistortShear(BOOL bOn)
/*N*/ {
/*N*/   bDistortShear = bOn;
/*N*/ }

/*N*/ void SdrHdlList::SetFineHdl(BOOL bOn)
/*N*/ {
/*N*/   if(bFineHandles != bOn)
/*N*/   {
/*N*/       // remember new state
/*N*/       bFineHandles = bOn;
/*N*/
/*N*/       // propagate change to IAOs
/*N*/       for(UINT32 i=0; i<GetHdlCount(); i++)
/*N*/       {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/       }
/*N*/   }
/*N*/ }


/*N*/ void SdrHdlList::Clear()
/*N*/ {
/*N*/   for (ULONG i=0; i<GetHdlCount(); i++)
/*N*/   {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/   }
/*N*/   aList.Clear();
/*N*/
/*N*/   // immediately remove from display
//STRIP012/*N*/     if(pImpl->pView)
//STRIP012/*N*/         pImpl->pView->RefreshAllIAOManagers();
/*N*/
/*N*/   bRotateShear=FALSE;
/*N*/   bDistortShear=FALSE;
/*N*/ }

/*N*/ void SdrHdlList::Sort()
/*N*/ {
/*N*/   // #97016# II: remember current focused handle
/*N*/   SdrHdl* pPrev = GetFocusHdl();
/*N*/
/*N*/     ImpSdrHdlListSorter aSort(aList);
/*N*/     aSort.DoSort();

    // #97016# II: get now and compare
/*N*/   SdrHdl* pNow = GetFocusHdl();
/*N*/
/*N*/   if(pPrev != pNow)
/*N*/   {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/   }
/*N*/ }



/*N*/ SdrHdl* SdrHdlList::HitTest(const Point& rPnt, const OutputDevice& rOut, BOOL bBack, BOOL bNext, SdrHdl* pHdl0) const
/*N*/ {
/*N*/    SdrHdl* pRet=NULL;
/*N*/    ULONG nAnz=GetHdlCount();
/*N*/    ULONG nNum=bBack ? 0 : nAnz;
/*N*/    while ((bBack ? nNum<nAnz : nNum>0) && pRet==NULL) {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/    }
/*N*/    return pRet;
/*N*/ }


}
