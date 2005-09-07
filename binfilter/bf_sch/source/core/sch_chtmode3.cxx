/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sch_chtmode3.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-07 21:53:51 $
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

// auto strip #ifndef _XOUTX_HXX //autogen
// auto strip #include <bf_svx/xoutx.hxx>
// auto strip #endif
#ifndef _SVX_TAB_LINE_HXX
#include <bf_svx/tabline.hxx>
#endif
#ifndef _SVDOGRAF_HXX //autogen
#include <bf_svx/svdograf.hxx>
#endif
// auto strip #ifndef _E3D_POLYGON3D_HXX //autogen
// auto strip #include <bf_svx/polygn3d.hxx>
// auto strip #endif
#ifndef _SVDOPATH_HXX //autogen
#include <bf_svx/svdopath.hxx>
#endif
// auto strip #ifndef _SV_MSGBOX_HXX //autogen
// auto strip #include <vcl/msgbox.hxx>
// auto strip #endif
// auto strip #ifndef _SVX_XLNWTIT_HXX //autogen
// auto strip #include <bf_svx/xlnwtit.hxx>
// auto strip #endif
#ifndef _SFX_WHITER_HXX //autogen
#include <svtools/whiter.hxx>
#endif
// auto strip #ifndef _SFXITEMSET_HXX //autogen
// auto strip #include <svtools/itemset.hxx>
// auto strip #endif
#ifndef _SVX_XBTMPIT_HXX //autogen
#include <bf_svx/xbtmpit.hxx>
#endif
// auto strip #ifndef _SVDORECT_HXX //autogen
// auto strip #include <bf_svx/svdorect.hxx>
// auto strip #endif
// auto strip #ifndef _SVDPAGE_HXX //autogen
// auto strip #include <bf_svx/svdpage.hxx>
// auto strip #endif

#ifndef _EEITEM_HXX //autogen
#include <bf_svx/eeitem.hxx>
#endif
#ifndef _SVX_COLRITEM_HXX //autogen
#define ITEMID_COLOR       EE_CHAR_COLOR
// auto strip #include <bf_svx/colritem.hxx>
#endif
// auto strip #ifndef _SVX_XFLGRIT_HXX
// auto strip #include <bf_svx/xflgrit.hxx>
// auto strip #endif
#ifndef _SVX_XFLFTRIT_HXX
#include <bf_svx/xflftrit.hxx>
#endif
#ifndef _SVX_XFLHTIT_HXX
#include <bf_svx/xflhtit.hxx>
#endif
// auto strip #ifndef _SFXPOOLITEM_HXX //autogen
// auto strip #include <svtools/poolitem.hxx>
// auto strip #endif
#ifndef _XTABLE_HXX
#include <bf_svx/xtable.hxx>
#endif
#ifndef _SCHATTR_HXX
#include "schattr.hxx"
#endif
// auto strip #ifndef _SCH_MEMCHRT_HXX
// auto strip #include "memchrt.hxx"
// auto strip #endif

// header for SvxChartTextOrientItem
#ifndef _SVX_CHRTITEM_HXX
#define ITEMID_DOUBLE           0
#define ITEMID_CHARTTEXTORIENT  SCHATTR_TEXT_ORIENT

// auto strip #ifndef _SFXENUMITEM_HXX
// auto strip #include <svtools/eitem.hxx>
// auto strip #endif

// auto strip #include <bf_svx/chrtitem.hxx>
#endif
// auto strip #ifndef _SFXITEMITER_HXX //autogen
// auto strip #include <svtools/itemiter.hxx>
// auto strip #endif
#define ITEMID_FONTHEIGHT  EE_CHAR_FONTHEIGHT
// auto strip #include <bf_svx/fhgtitem.hxx>
#ifndef _CHTMODEL_HXX
// auto strip #include <chtmodel.hxx>
#include <globfunc.hxx>
#endif
// auto strip #ifndef _SCH_OBJID_HXX
// auto strip #include "objid.hxx"
// auto strip #endif
#ifndef _SVX_SVXIDS_HRC
#include <bf_svx/svxids.hrc>
#endif
// auto strip #ifndef _SCH_SCHRESID_HXX
// auto strip #include "schresid.hxx"
// auto strip #endif
// auto strip #ifndef _SCH_DATAROW_HXX
// auto strip #include "datarow.hxx"
// auto strip #endif
// auto strip #ifndef _SCH_DATAPOIN_HXX
// auto strip #include "datapoin.hxx"
// auto strip #endif

// auto strip #ifndef _SVX_XLNCLIT_HXX //autogen
// auto strip #include <bf_svx/xlnclit.hxx>
// auto strip #endif

// auto strip #ifndef _SVX_XFLCLIT_HXX //autogen
// auto strip #include <bf_svx/xflclit.hxx>
// auto strip #endif

#include "schattr.hxx"
#ifndef _SVX_BRSHITEM_HXX //autogen
#define ITEMID_BRUSH SCHATTR_SYMBOL_BRUSH
#include <bf_svx/brshitem.hxx>
#endif
#ifndef _SVX_SIZEITEM_HXX //autogen
#define ITEMID_SIZE 0
#include <bf_svx/sizeitem.hxx>
#endif
// header for SAL_STATIC_CAST
#ifndef _SAL_TYPES_H_
#include <sal/types.h>
#endif
// auto strip #ifndef   _OUTLOBJ_HXX
// auto strip #include "bf_svx/outlobj.hxx"
// auto strip #endif

#include "glob.hrc"

#include "chtscene.hxx"
#include "pairs.hxx"

#include "chaxis.hxx"

// auto strip #ifndef _SCH_PROPERTYCHANGEHINT_HXX
// auto strip #include "PropertyChangeHint.hxx"
// auto strip #endif
namespace binfilter {

/*************************************************************************
|*
|* Entscheidung, ob BuildChart notwendig
|*
\************************************************************************/
/*N*/ BOOL ChartModel::IsAttrChangeNeedsBuildChart(const SfxItemSet& rAttr)
/*N*/ {
/*N*/   // BM #60999# rebuild for all EE_CHAR attributes because of possibly red color for negative numbers. sorry :-(
/*N*/   return TRUE;

 /*
    BOOL bNeedBuild=FALSE;

    SfxWhichIter aWhichIter(rAttr);
    USHORT nWhich = aWhichIter.FirstWhich();
    while (nWhich != 0)
    {
       if (rAttr.GetItemState(nWhich) == SFX_ITEM_SET)
       {
           if(nWhich < XATTR_LINE_FIRST  || nWhich > XATTR_FILL_LAST)
           {

               switch(nWhich)
               {

               case EE_CHAR_COLOR:
               case EE_CHAR_UNDERLINE:
               case EE_CHAR_STRIKEOUT:
                   break;

               default:

                   bNeedBuild=TRUE;
                   break;
               }
           }
       }
       nWhich = aWhichIter.NextWhich();
    }
    return bNeedBuild;
*/
/*N*/ }

/*
    Set axis attributes.
    The attributes given by rAttr are set unconditionally to all axis,
    regardless of wether they are visible or not.
*/
//STRIP001 void ChartModel::PutAxisAttr(const SfxItemSet& rAttr,BOOL bMerge)
//STRIP001 {
//STRIP001 //   if( pChartXAxis->IsVisible() )
//STRIP001  {
//STRIP001      if( !bMerge )
//STRIP001          pChartXAxis->GetItemSet()->ClearItem();
//STRIP001      pChartXAxis->SetAttributes( rAttr );
//STRIP001  }
//STRIP001 //   if( CanAxis( CHART_AXIS_SECONDARY_X ) && pChartAAxis->IsVisible() )
//STRIP001  {
//STRIP001      if( !bMerge )
//STRIP001          pChartAAxis->GetItemSet()->ClearItem();
//STRIP001      pChartAAxis->SetAttributes( rAttr );
//STRIP001  }
//STRIP001
//STRIP001 //   if( pChartYAxis->IsVisible() )
//STRIP001  {
//STRIP001      if( !bMerge )
//STRIP001          pChartYAxis->GetItemSet()->ClearItem();
//STRIP001      pChartYAxis->SetAttributes( rAttr );
//STRIP001  }
//STRIP001 //   if( CanAxis( CHART_AXIS_SECONDARY_Y ) && pChartBAxis->IsVisible() )
//STRIP001  {
//STRIP001      if( !bMerge )
//STRIP001          pChartBAxis->GetItemSet()->ClearItem();
//STRIP001      pChartBAxis->SetAttributes( rAttr );
//STRIP001  }
//STRIP001
//STRIP001 //   if( Is3DChart() && pChartZAxis->IsVisible() )
//STRIP001  {
//STRIP001      if( !bMerge )
//STRIP001          pChartZAxis->GetItemSet()->ClearItem();
//STRIP001      pChartZAxis->SetAttributes( rAttr );
//STRIP001  }
//STRIP001 }

/*************************************************************************
|*
|* Achsen-Attribute ermitteln
|*
\************************************************************************/

//STRIP001 const SfxItemSet& ChartModel::GetAxisAttr(const SdrObjGroup* pAxisObj) const
//STRIP001 {
//STRIP001  if (pAxisObj)
//STRIP001  {
//STRIP001      SchObjectId* pObjId = GetObjectId(*pAxisObj);
//STRIP001
//STRIP001      if (pObjId)
//STRIP001      {
//STRIP001          long nId=GetObjectId(*pAxisObj)->GetObjId();
//STRIP001          switch (nId)
//STRIP001          {
//STRIP001              case CHOBJID_DIAGRAM_X_AXIS:
//STRIP001              case CHOBJID_DIAGRAM_Y_AXIS:
//STRIP001              case CHOBJID_DIAGRAM_Z_AXIS:
//STRIP001              case CHOBJID_DIAGRAM_A_AXIS:
//STRIP001              case CHOBJID_DIAGRAM_B_AXIS:
//STRIP001              case CHOBJID_DIAGRAM_C_AXIS:
//STRIP001                  return GetAttr(nId);
//STRIP001 /*                   return *pXAxisAttr;
//STRIP001                  return *pYAxisAttr;
//STRIP001                  return *pZAxisAttr;
//STRIP001 */
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  return *pAxisAttr;
//STRIP001 }

/*************************************************************************
|*
|* Achsen-Attribute ermitteln
|*
\************************************************************************/
/*N*/ ChartAxis* ChartModel::GetAxis(long nId)
/*N*/ {
/*N*/   switch(nId)
/*N*/   {
/*N*/       case CHOBJID_DIAGRAM_X_AXIS:
/*N*/           return pChartXAxis;
/*N*/       case CHOBJID_DIAGRAM_Y_AXIS:
/*N*/           return pChartYAxis;
/*N*/       case CHOBJID_DIAGRAM_Z_AXIS:
/*N*/           return pChartZAxis;
/*N*/       case CHOBJID_DIAGRAM_B_AXIS:
/*N*/           return pChartBAxis;
/*?*/       case CHOBJID_DIAGRAM_A_AXIS:
/*?*/           return pChartAAxis;
/*N*/   }
/*?*/   DBG_ERROR("ChartModel::GetAxis() illegal argument (nId=CHOBJID_)");
/*?*/   return pChartYAxis;
/*N*/ }



/*
    Get axis attributes.
    If pAxisObj is NULL then the intersection of the attributes of all five
    axes is taken, regardless of wether the axes are visible or not.
*/
/*N*/ SfxItemSet ChartModel::GetFullAxisAttr( const SdrObjGroup* pAxisObj, bool bOnlyInserted ) const
/*N*/ {
/*N*/   if (pAxisObj)
/*N*/   {
/*?*/       SchObjectId* pObjId = GetObjectId(*pAxisObj);
/*?*/
/*?*/       if (pObjId)
/*?*/       {
/*?*/           long nId=pObjId->GetObjId();
/*?*/
/*?*/           SfxItemSet aAttr(*pItemPool,nAxisWhichPairs);
/*?*/           aAttr.Put(GetAttr(nId));
/*?*/           ((ChartModel*)this)->GetAxis(nId)->GetMembersAsAttr(aAttr);
/*?*/           return aAttr;
/*?*/       }
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/         // clear member item set for all axes
/*N*/       pAxisAttr->ClearItem();
/*N*/         bool bIsFirst = true;
/*N*/
/*N*/         if( ! bOnlyInserted || HasAxis( CHOBJID_DIAGRAM_X_AXIS ))
/*N*/             if( bIsFirst )
/*N*/             {
/*N*/                 pAxisAttr->Set( GetAttr( CHOBJID_DIAGRAM_X_AXIS ));
/*N*/                 bIsFirst = false;
/*N*/             }
/*N*/             else
/*?*/                 IntersectSets( GetAttr( CHOBJID_DIAGRAM_X_AXIS ), *pAxisAttr );
/*N*/
/*N*/         if( ! bOnlyInserted || HasAxis( CHOBJID_DIAGRAM_Y_AXIS ))
/*N*/             if( bIsFirst )
/*N*/             {
/*?*/                 pAxisAttr->Set( GetAttr( CHOBJID_DIAGRAM_Y_AXIS ));
/*?*/                 bIsFirst = false;
/*N*/             }
/*N*/             else
/*N*/                 IntersectSets( GetAttr( CHOBJID_DIAGRAM_Y_AXIS ), *pAxisAttr );
/*N*/
/*N*/         if( ! bOnlyInserted || (Is3DChart() && HasAxis( CHOBJID_DIAGRAM_Z_AXIS )))
/*N*/             if( bIsFirst )
/*N*/             {
/*?*/                 pAxisAttr->Set( GetAttr( CHOBJID_DIAGRAM_Z_AXIS ));
/*?*/                 bIsFirst = false;
/*N*/             }
/*N*/             else
/*N*/                 IntersectSets( GetAttr( CHOBJID_DIAGRAM_Z_AXIS ), *pAxisAttr );
/*N*/
/*N*/         if( ! bOnlyInserted || HasAxis( CHOBJID_DIAGRAM_A_AXIS ))
/*?*/             if( bIsFirst )
/*?*/             {
/*?*/                 pAxisAttr->Set( GetAttr( CHOBJID_DIAGRAM_A_AXIS ));
/*?*/                 bIsFirst = false;
/*?*/             }
/*?*/             else
/*?*/                 IntersectSets( GetAttr( CHOBJID_DIAGRAM_A_AXIS ), *pAxisAttr );
/*N*/
/*N*/         if( ! bOnlyInserted || HasAxis( CHOBJID_DIAGRAM_B_AXIS ))
/*?*/             if( bIsFirst )
/*?*/             {
/*?*/                 pAxisAttr->Set( GetAttr( CHOBJID_DIAGRAM_B_AXIS ));
/*?*/                 bIsFirst = false;
/*?*/             }
/*?*/             else
/*?*/                 IntersectSets( GetAttr( CHOBJID_DIAGRAM_B_AXIS ), *pAxisAttr );
/*N*/   }
/*N*/
/*N*/ //     if( bOnlyInserted )
/*N*/ //         pAxisAttr->ClearItem( SCHATTR_AXIS_SHOWDESCR );
/*N*/
/*N*/   return *pAxisAttr;
/*N*/ }

/*************************************************************************
|*
|* Achsen-Attribute aendern;
|* Liefert bei geaenderten Attributen TRUE.
|*
\************************************************************************/

/*N*/ BOOL ChartModel::ChangeAxisAttr(const SfxItemSet &rAttr,SdrObjGroup *pAxisObj,BOOL bMerge)
/*N*/ {
/*N*/   if (pAxisObj)
/*N*/   {
/*N*/       SchObjectId *pObjId = GetObjectId(*pAxisObj);
/*N*/
/*N*/       if (! pObjId) return FALSE;
/*N*/       else
/*N*/       {
/*N*/           SfxItemSet aSet(*pItemPool,nAxisWhichPairs);
/*N*/           aSet.Put(rAttr);
/*N*/
/*N*/           const SfxPoolItem *pPoolItem  = NULL;
/*N*/
/*N*/           if(rAttr.GetItemState(SID_ATTR_NUMBERFORMAT_VALUE,TRUE,&pPoolItem)==SFX_ITEM_SET)
/*N*/           {
/*N*/               UINT32 nTmp=((const SfxUInt32Item*)pPoolItem)->GetValue();
/*N*/               aSet.Put(SfxUInt32Item(IsPercentChart()
/*N*/                   ? SCHATTR_AXIS_NUMFMTPERCENT : SCHATTR_AXIS_NUMFMT , nTmp));
/*N*/           }
/*N*/
/*N*/           long nId=pObjId->GetObjId();
/*N*/           SetAttributes( nId, aSet, bMerge );             // at the model
/*N*/           SetAxisAttributes( &GetAttr( nId ), pAxisObj ); // at the drawing object
/*N*/
/*N*/             // at the axis itself!
/*N*/             long nAxisUId = ChartAxis::GetUniqueIdByObjectId( nId );
/*N*/             if( nAxisUId != CHAXIS_AXIS_UNKNOWN )
/*N*/             {
/*N*/                 // this method always returns a valid pointer
/*N*/                 GetAxisByUID( nAxisUId )->SetAttributes( rAttr );
/*N*/             }
/*N*/             else
/*N*/                 DBG_ERROR( "ChartAxis not found for Object" );
/*N*/
/*N*/           if(IsAttrChangeNeedsBuildChart(aSet))
/*N*/              BuildChart(FALSE,nId); //z.B. auch Texte skalieren!
/*N*/           return TRUE;
/*N*/       }
/*N*/   }
/*N*/   else
/*N*/   {
/*?*/       DBG_BF_ASSERT(0, "STRIP"); //STRIP001 PutAxisAttr(rAttr,bMerge);
//STRIP001 /*?*/        return SetAllAxisAttributes ();
        return FALSE;
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|* Achsen-Attribute aendern;
|* Liefert bei geaenderten Attributen TRUE.
|*
\************************************************************************/

//STRIP001 BOOL ChartModel::ChangeAxisAttr(const SfxItemSet& rXAxisAttr,
//STRIP001                              const SfxItemSet& rYAxisAttr,
//STRIP001                              const SfxItemSet& rZAxisAttr,
//STRIP001                              BOOL              bMerge)
//STRIP001 {
//STRIP001  SetAttributes(CHOBJID_DIAGRAM_X_AXIS,rXAxisAttr,bMerge);
//STRIP001  SetAttributes(CHOBJID_DIAGRAM_Y_AXIS,rYAxisAttr,bMerge);
//STRIP001  SetAttributes(CHOBJID_DIAGRAM_Z_AXIS,rZAxisAttr,bMerge);
//STRIP001  return SetAllAxisAttributes ();
//STRIP001 }
/*************************************************************************
|*
|* Gitter-Attribute setzen
|*
\************************************************************************/

//STRIP001 void ChartModel::PutGridAttr(const SfxItemSet& rAttr,BOOL bMerge)
//STRIP001 {
//STRIP001  if(!bMerge)
//STRIP001  {
//STRIP001      pGridAttr->ClearItem();
//STRIP001      pXGridMainAttr->ClearItem();
//STRIP001      pYGridMainAttr->ClearItem();
//STRIP001      pZGridMainAttr->ClearItem();
//STRIP001      pXGridHelpAttr->ClearItem();
//STRIP001      pYGridHelpAttr->ClearItem();
//STRIP001      pZGridHelpAttr->ClearItem();
//STRIP001  }
//STRIP001  pGridAttr->Put(rAttr);
//STRIP001  pXGridMainAttr->Put(rAttr);
//STRIP001  pYGridMainAttr->Put(rAttr);
//STRIP001  pZGridMainAttr->Put(rAttr);
//STRIP001  pXGridHelpAttr->Put(rAttr);
//STRIP001  pYGridHelpAttr->Put(rAttr);
//STRIP001  pZGridHelpAttr->Put(rAttr);
//STRIP001 }

/*************************************************************************
|*
|* Gitter-Attribute ermitteln
|*
\************************************************************************/

//STRIP001 const SfxItemSet& ChartModel::GetGridAttr(const SdrObject* pGridObj) const
//STRIP001 {
//STRIP001     UINT16 nObjId = CHOBJID_ANY;
//STRIP001
//STRIP001     if( pGridObj )
//STRIP001  {
//STRIP001      SchObjectId* pObjId = GetObjectId( *pGridObj );
//STRIP001         if( pObjId )
//STRIP001             nObjId = pObjId->GetObjId();
//STRIP001     }
//STRIP001
//STRIP001     return GetGridAttr( nObjId );
//STRIP001 }


//STRIP001 const SfxItemSet& ChartModel::GetGridAttr( UINT16 nObjId ) const
//STRIP001 {
//STRIP001     switch( nObjId )
//STRIP001     {
//STRIP001         case CHOBJID_DIAGRAM_X_GRID_MAIN_GROUP:
//STRIP001             return *pXGridMainAttr;
//STRIP001         case CHOBJID_DIAGRAM_Y_GRID_MAIN_GROUP:
//STRIP001             return *pYGridMainAttr;
//STRIP001         case CHOBJID_DIAGRAM_Z_GRID_MAIN_GROUP:
//STRIP001             return *pZGridMainAttr;
//STRIP001         case CHOBJID_DIAGRAM_X_GRID_HELP_GROUP:
//STRIP001             return *pXGridHelpAttr;
//STRIP001         case CHOBJID_DIAGRAM_Y_GRID_HELP_GROUP:
//STRIP001             return *pYGridHelpAttr;
//STRIP001         case CHOBJID_DIAGRAM_Z_GRID_HELP_GROUP:
//STRIP001             return *pZGridHelpAttr;
//STRIP001         default:
//STRIP001             pGridAttr->ClearItem();
//STRIP001             pGridAttr->Put(*pXGridMainAttr);
//STRIP001
//STRIP001             CompareSets( *pYGridMainAttr, *pGridAttr );
//STRIP001             CompareSets( *pZGridMainAttr, *pGridAttr );
//STRIP001             CompareSets( *pXGridHelpAttr, *pGridAttr );
//STRIP001             CompareSets( *pYGridHelpAttr, *pGridAttr );
//STRIP001             CompareSets( *pZGridHelpAttr, *pGridAttr );
//STRIP001
//STRIP001             return *pGridAttr;
//STRIP001     }
//STRIP001 }

/*************************************************************************
|*
|* Diagramm-Gitter-Attribute aendern;
|* Liefert bei geaenderten Attributen TRUE.
|*
\************************************************************************/

//STRIP001 BOOL ChartModel::ChangeGridAttr(const SfxItemSet& rAttr,
//STRIP001                              SdrObject* pGridObj, BOOL bMerge)
//STRIP001 {
//STRIP001  if (pGridObj)
//STRIP001  {
//STRIP001      SchObjectId* pObjId = GetObjectId(*pGridObj);
//STRIP001
//STRIP001      if (pObjId) switch (pObjId->GetObjId())
//STRIP001                  {
//STRIP001                      case CHOBJID_DIAGRAM_X_GRID_MAIN_GROUP:
//STRIP001                          PutXGridMainAttr(rAttr,bMerge);
//STRIP001
//STRIP001 //-/                         pGridObj->SetAttributes(*pXGridMainAttr, FALSE);
//STRIP001                          pGridObj->SetItemSetAndBroadcast(*pXGridMainAttr);
//STRIP001                          break;
//STRIP001
//STRIP001                      case CHOBJID_DIAGRAM_Y_GRID_MAIN_GROUP:
//STRIP001                          PutYGridMainAttr(rAttr,bMerge);
//STRIP001
//STRIP001 //-/                         pGridObj->SetAttributes(*pYGridMainAttr, FALSE);
//STRIP001                          pGridObj->SetItemSetAndBroadcast(*pYGridMainAttr);
//STRIP001                          break;
//STRIP001
//STRIP001                      case CHOBJID_DIAGRAM_Z_GRID_MAIN_GROUP:
//STRIP001                          PutZGridMainAttr(rAttr,bMerge);
//STRIP001
//STRIP001 //-/                         pGridObj->SetAttributes(*pZGridMainAttr, FALSE);
//STRIP001                          pGridObj->SetItemSetAndBroadcast(*pZGridMainAttr);
//STRIP001                          break;
//STRIP001
//STRIP001                      case CHOBJID_DIAGRAM_X_GRID_HELP_GROUP:
//STRIP001                          PutXGridHelpAttr(rAttr,bMerge);
//STRIP001
//STRIP001 //-/                         pGridObj->SetAttributes(*pXGridHelpAttr, FALSE);
//STRIP001                          pGridObj->SetItemSetAndBroadcast(*pXGridHelpAttr);
//STRIP001                          break;
//STRIP001
//STRIP001                      case CHOBJID_DIAGRAM_Y_GRID_HELP_GROUP:
//STRIP001                          PutYGridHelpAttr(rAttr,bMerge);
//STRIP001
//STRIP001 //-/                         pGridObj->SetAttributes(*pYGridHelpAttr, FALSE);
//STRIP001                          pGridObj->SetItemSetAndBroadcast(*pYGridHelpAttr);
//STRIP001                          break;
//STRIP001
//STRIP001                      case CHOBJID_DIAGRAM_Z_GRID_HELP_GROUP:
//STRIP001                          PutZGridHelpAttr(rAttr,bMerge);
//STRIP001
//STRIP001 //-/                         pGridObj->SetAttributes(*pZGridHelpAttr, FALSE);
//STRIP001                          pGridObj->SetItemSetAndBroadcast(*pZGridHelpAttr);
//STRIP001                          break;
//STRIP001                  }
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      PutGridAttr(rAttr,bMerge);
//STRIP001
//STRIP001      SdrPage* pPage = GetPage(0);
//STRIP001
//STRIP001      if (pPage)
//STRIP001      {
//STRIP001          SdrObjGroup* pGroup = (SdrObjGroup*)GetObjWithId(CHOBJID_DIAGRAM, *pPage);
//STRIP001          DBG_ASSERT(pGroup, "ChartModel::ChangeGridAttr: diagram group not found");
//STRIP001
//STRIP001          SdrObjGroup* pGridGroup;
//STRIP001
//STRIP001          if (bShowXGridMain)
//STRIP001          {
//STRIP001              pGridGroup = (SdrObjGroup*)GetObjWithId(CHOBJID_DIAGRAM_X_GRID_MAIN_GROUP,
//STRIP001                                                      *pGroup->GetSubList());
//STRIP001
//STRIP001              if (pGridGroup)
//STRIP001              {
//STRIP001                  SdrObjListIter aIterator(*pGridGroup->GetSubList(), IM_FLAT);
//STRIP001                  while (aIterator.IsMore())
//STRIP001 //-/                     aIterator.Next()->SetAttributes(*pXGridMainAttr, FALSE);
//STRIP001                      aIterator.Next()->SetItemSetAndBroadcast(*pXGridMainAttr);
//STRIP001              }
//STRIP001          }
//STRIP001
//STRIP001          if (bShowYGridMain)
//STRIP001          {
//STRIP001              pGridGroup = (SdrObjGroup*)GetObjWithId(CHOBJID_DIAGRAM_Y_GRID_MAIN_GROUP,
//STRIP001                                                      *pGroup->GetSubList());
//STRIP001
//STRIP001              if (pGridGroup)
//STRIP001              {
//STRIP001                  SdrObjListIter aIterator(*pGridGroup->GetSubList(), IM_FLAT);
//STRIP001                  while (aIterator.IsMore())
//STRIP001 //-/                     aIterator.Next()->SetAttributes(*pYGridMainAttr, FALSE);
//STRIP001                      aIterator.Next()->SetItemSetAndBroadcast(*pYGridMainAttr);
//STRIP001              }
//STRIP001          }
//STRIP001
//STRIP001          if (bShowXGridHelp)
//STRIP001          {
//STRIP001              pGridGroup = (SdrObjGroup*)GetObjWithId(CHOBJID_DIAGRAM_X_GRID_HELP_GROUP,
//STRIP001                                                      *pGroup->GetSubList());
//STRIP001
//STRIP001              if (pGridGroup)
//STRIP001              {
//STRIP001                  SdrObjListIter aIterator(*pGridGroup->GetSubList(), IM_FLAT);
//STRIP001                  while (aIterator.IsMore())
//STRIP001 //-/                     aIterator.Next()->SetAttributes(*pXGridHelpAttr, FALSE);
//STRIP001                      aIterator.Next()->SetItemSetAndBroadcast(*pXGridHelpAttr);
//STRIP001              }
//STRIP001          }
//STRIP001
//STRIP001          if (bShowYGridHelp)
//STRIP001          {
//STRIP001              pGridGroup = (SdrObjGroup*)GetObjWithId(CHOBJID_DIAGRAM_Y_GRID_HELP_GROUP,
//STRIP001                                                      *pGroup->GetSubList());
//STRIP001              if (pGridGroup)
//STRIP001              {
//STRIP001                  SdrObjListIter aIterator(*pGridGroup->GetSubList(), IM_FLAT);
//STRIP001                  while (aIterator.IsMore())
//STRIP001 //-/                     aIterator.Next()->SetAttributes(*pYGridHelpAttr, FALSE);
//STRIP001                      aIterator.Next()->SetItemSetAndBroadcast(*pYGridHelpAttr);
//STRIP001              }
//STRIP001          }
//STRIP001
//STRIP001          if (Is3DChart())
//STRIP001          {
//STRIP001              if (bShowZGridMain)
//STRIP001              {
//STRIP001                  pGridGroup = (SdrObjGroup*)GetObjWithId(CHOBJID_DIAGRAM_Z_GRID_MAIN_GROUP,
//STRIP001                                                          *pGroup->GetSubList());
//STRIP001
//STRIP001                  if (pGridGroup)
//STRIP001                  {
//STRIP001                      SdrObjListIter aIterator(*pGridGroup->GetSubList(), IM_FLAT);
//STRIP001                      while (aIterator.IsMore())
//STRIP001 //-/                         aIterator.Next()->SetAttributes(*pZGridMainAttr, FALSE);
//STRIP001                          aIterator.Next()->SetItemSetAndBroadcast(*pZGridMainAttr);
//STRIP001                  }
//STRIP001              }
//STRIP001
//STRIP001              if (bShowZGridHelp)
//STRIP001              {
//STRIP001                  pGridGroup = (SdrObjGroup*)GetObjWithId(CHOBJID_DIAGRAM_Z_GRID_HELP_GROUP,
//STRIP001                                                          *pGroup->GetSubList());
//STRIP001                  if (pGridGroup)
//STRIP001                  {
//STRIP001                      SdrObjListIter aIterator(*pGridGroup->GetSubList(), IM_FLAT);
//STRIP001                      while (aIterator.IsMore())
//STRIP001 //-/                         aIterator.Next()->SetAttributes(*pZGridHelpAttr, FALSE);
//STRIP001                          aIterator.Next()->SetItemSetAndBroadcast(*pZGridHelpAttr);
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if(IsAttrChangeNeedsBuildChart(rAttr))
//STRIP001      BuildChart (FALSE);
//STRIP001
//STRIP001  return TRUE;
//STRIP001 }

/*************************************************************************
|*
|* Diagrammflaechen-Attribute aendern;
|* Liefert bei geaenderten Attributen TRUE.
|*
\************************************************************************/

//STRIP001 void ChartModel::ChangeDiagramAreaAttr(const SfxItemSet& rAttr,
//STRIP001                                     SdrRectObj* pDiagramAreaObj,
//STRIP001                                     BOOL bMerge)
//STRIP001 {
//STRIP001  if (!pDiagramAreaObj)
//STRIP001  {
//STRIP001      SdrPage* pPage = GetPage(0);
//STRIP001      DBG_ASSERT( pPage, "ChartModel::ChangeDiagramAreaAttr: page obj is NULL" );
//STRIP001
//STRIP001      pDiagramAreaObj = (SdrRectObj*)GetObjWithId(CHOBJID_DIAGRAM_AREA, *pPage);
//STRIP001      DBG_ASSERT( pDiagramAreaObj, "ChartModel::ChangeDiagramAreaAttr: empty diagram obj");
//STRIP001  }
//STRIP001
//STRIP001  PutDiagramAreaAttr(rAttr,bMerge);
//STRIP001
//STRIP001 //-/ pDiagramAreaObj->SetAttributes(rAttr, FALSE);
//STRIP001  pDiagramAreaObj->SetItemSetAndBroadcast(rAttr);
//STRIP001
//STRIP001  if(IsDonutChart())
//STRIP001     {
//STRIP001         if(IsAttrChangeNeedsBuildChart(rAttr))
//STRIP001          BuildChart (FALSE);
//STRIP001     }
//STRIP001     else
//STRIP001     {
//STRIP001         Broadcast( SchPropertyChangeHint( pDiagramAreaObj, rAttr ) );
//STRIP001     }
//STRIP001
//STRIP001 }

/*************************************************************************
|*
|* Diagrammwaende-Attribute aendern;
|* Liefert bei geaenderten Attributen TRUE.
|*
\************************************************************************/

//STRIP001 void ChartModel::ChangeDiagramWallAttr(const SfxItemSet& rAttr,
//STRIP001                                     SdrObject* pDiagramWallObj,
//STRIP001                                     BOOL bMerge)
//STRIP001 {
//STRIP001  if (!pDiagramWallObj)
//STRIP001  {
//STRIP001      SdrPage* pPage = GetPage(0);
//STRIP001      DBG_ASSERT( pPage, "ChartModel::ChangeDiagramWallAttr: page obj is NULL" );
//STRIP001
//STRIP001      SdrObjGroup* pGroup = (SdrObjGroup*)GetObjWithId(CHOBJID_DIAGRAM, *pPage);
//STRIP001      DBG_ASSERT( pGroup, "ChartModel::ChangeDiagramAreaAttr: empty diagram group obj");
//STRIP001
//STRIP001      pDiagramWallObj = (SdrObjGroup*)GetObjWithId(CHOBJID_DIAGRAM_WALL,
//STRIP001                                                   *pGroup->GetSubList());
//STRIP001      DBG_ASSERT( pDiagramWallObj, "ChartModel::ChangeDiagramWallAttr: diagram wall obj is NULL" );
//STRIP001  }
//STRIP001
//STRIP001  PutDiagramWallAttr(rAttr,bMerge);
//STRIP001
//STRIP001  if (pDiagramWallObj->ISA(SdrObjGroup))
//STRIP001  {
//STRIP001      if (((SdrObjGroup*)pDiagramWallObj)->GetSubList())
//STRIP001      {
//STRIP001          SdrObjListIter aIterator(*((SdrObjGroup*)pDiagramWallObj)->GetSubList(), IM_FLAT);
//STRIP001          while (aIterator.IsMore())
//STRIP001 //-/             aIterator.Next()->SetAttributes(*pDiagramWallAttr, FALSE);
//STRIP001              aIterator.Next()->SetItemSetAndBroadcast(*pDiagramWallAttr);
//STRIP001      }
//STRIP001 //-/     else pDiagramWallObj->SetAttributes(*pDiagramWallAttr, FALSE);
//STRIP001      else pDiagramWallObj->SetItemSetAndBroadcast(*pDiagramWallAttr);
//STRIP001  }
//STRIP001 //-/ else pDiagramWallObj->SetAttributes(*pDiagramWallAttr, FALSE);
//STRIP001  else pDiagramWallObj->SetItemSetAndBroadcast(*pDiagramWallAttr);
//STRIP001
//STRIP001  if(IsAttrChangeNeedsBuildChart(rAttr))
//STRIP001      BuildChart (FALSE);
//STRIP001  else if(Is3DChart())
//STRIP001  {
//STRIP001      SdrPage* pPage = GetPage(0);
//STRIP001      DBG_ASSERT(pPage, "ChartModel::ChangeDiagramWallAttr: No page available");
//STRIP001      SdrObjGroup* pGroup = (SdrObjGroup*)GetObjWithId(CHOBJID_DIAGRAM, *pPage);
//STRIP001      DBG_ASSERT(pGroup, "ChartModel::ChangeDiagramWallAttr: diagram group not found");
//STRIP001      SetAttrWithId(CHOBJID_DIAGRAM_WALL,*pGroup->GetSubList(),rAttr);
//STRIP001  }
//STRIP001 }

/*************************************************************************
|*
|* Diagrammboden-Attribute aendern;
|* Liefert bei geaenderten Attributen TRUE.
|*
\************************************************************************/

//STRIP001 void ChartModel::ChangeDiagramFloorAttr(const SfxItemSet& rAttr,
//STRIP001                                      E3dExtrudeObj* pDiagramFloorObj,
//STRIP001                                      BOOL bMerge)
//STRIP001 {
//STRIP001  if (!pDiagramFloorObj)
//STRIP001  {
//STRIP001      SdrPage* pPage = GetPage(0);
//STRIP001      DBG_ASSERT(pPage, "ChartModel::ChangeDiagramFloorAttr: No page available");
//STRIP001
//STRIP001      SdrObjGroup* pGroup = (SdrObjGroup*)GetObjWithId(CHOBJID_DIAGRAM, *pPage);
//STRIP001      DBG_ASSERT(pGroup, "ChartModel::ChangeDiagramFloorAttr: diagram group not found");
//STRIP001
//STRIP001      pDiagramFloorObj = SAL_STATIC_CAST( E3dExtrudeObj*, GetObjWithId( CHOBJID_DIAGRAM_FLOOR,
//STRIP001                                                                       *pGroup->GetSubList()) );
//STRIP001      DBG_ASSERT(pDiagramFloorObj, "ChartModel::ChangeDiagramFloorAttr: floor not found");
//STRIP001      if(!pDiagramFloorObj)
//STRIP001          return;
//STRIP001  }
//STRIP001
//STRIP001  PutDiagramFloorAttr(rAttr,bMerge);
//STRIP001
//STRIP001 //-/ pDiagramFloorObj->SetAttributes(*pDiagramFloorAttr, FALSE);
//STRIP001  pDiagramFloorObj->SetItemSetAndBroadcast(*pDiagramFloorAttr);
//STRIP001
//STRIP001  if(IsAttrChangeNeedsBuildChart(rAttr))
//STRIP001      BuildChart (FALSE);
//STRIP001 }

/*************************************************************************
|*
|* Datenreihen-Attribute setzen
|*
\************************************************************************/
/*N*/ void ChartModel::PutDataRowAttrAll(const SfxItemSet& rAttr,BOOL bMerge,BOOL bClearPoints)
/*N*/ {
/*N*/   long nCnt=aDataRowAttrList.Count();
/*N*/   while(nCnt--)
/*N*/       PutDataRowAttr(nCnt,rAttr,bMerge,bClearPoints);
/*N*/ }

/*N*/ void ChartModel::PutDataRowAttr(long nRow, const SfxItemSet& rAttr,BOOL bMerge,BOOL bClearPoints)
/*N*/ {
/*N*/
/*N*/   CHART_TRACE1( "ChartModel::PutDataRowAttr %smerge", bMerge? "": "NO " );
/*N*/ //    DBG_ITEMS((SfxItemSet&)rAttr,this);
/*N*/
/*N*/     if( aDataRowAttrList.Count() <= (unsigned long)nRow )
/*N*/     {
/*?*/         DBG_ERROR( "Invalid index to array requested" );
/*?*/         return;
/*N*/     }
/*N*/
/*N*/     if(!bMerge)
/*?*/       aDataRowAttrList.GetObject(nRow)->ClearItem();
/*N*/
/*N*/   PutItemSetWithNameCreation( *aDataRowAttrList.GetObject( nRow ), rAttr );
/*N*/
/*N*/   if(bClearPoints && (nRow < GetRowCount()))
/*N*/   {
/*N*/       long nCol,nColCnt=GetColCount();
/*N*/       for(nCol=0;nCol<nColCnt;nCol++)
/*N*/       {
/*N*/           ClearDataPointAttr(nCol,nRow,rAttr);
/*N*/       }
/*N*/   }
/*N*/ }
/*************************************************************************
|*
|* Datenreihen-Attribute ermitteln
|*
\************************************************************************/

/*N*/ const SfxItemSet& ChartModel::GetDataRowAttr( long nRow ) const
/*N*/ {
/*N*/   if( nRow < (long)aDataRowAttrList.Count() )
/*N*/   {
/*N*/       SfxItemSet* pSet = aDataRowAttrList.GetObject( nRow );
/*N*/       DBG_ASSERT( pSet, "Invalid ItemSet" );
/*N*/       return *pSet;
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       DBG_ERROR( "Requested data row attribute is unavailable" );
/*N*/
/*N*/       // return something
/*?*/       DBG_ASSERT( pChartAttr, "Invalid Chart-ItemSet" );
/*?*/       return *pChartAttr;
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|* SubRoutinen ChangeDataPointAttr, Legendenattributierung
|*
\************************************************************************/
//STRIP001 void ChartModel::ChangeLegendPointAttr(const long nDataCol,const SfxItemSet& rDataPointAttr)
//STRIP001 {
//STRIP001  CHART_TRACE( "ChartModel::ChangeLegendPointAttr" );
//STRIP001
//STRIP001  SfxItemSet aSymbolAttr(rDataPointAttr); //#54870#
//STRIP001  GenerateSymbolAttr(aSymbolAttr,0,SYMBOLMODE_LEGEND); //Achtung! 0 ist die Datenreihe (immer=0 bei Datenpunkt-Legende=Pie), das kann sich aber mal ändern!
//STRIP001
//STRIP001  const SdrPage* pPage=GetPage(0);
//STRIP001  SdrObjGroup* pLegendObj = (SdrObjGroup*)GetObjWithId(CHOBJID_LEGEND, *pPage);
//STRIP001  DBG_ASSERT(pLegendObj, "ChartModel::ChangeLegendPointAttr:Legenden-Objekt nicht gefunden!");
//STRIP001
//STRIP001  SdrObjListIter aIterator(*pLegendObj->GetSubList(), IM_FLAT);
//STRIP001  while (aIterator.IsMore())
//STRIP001  {
//STRIP001      SdrObject* pObj = aIterator.Next();
//STRIP001      SchObjectId* pId = GetObjectId(*pObj);
//STRIP001
//STRIP001      if (pId && (pId->GetObjId() == CHOBJID_LEGEND_SYMBOL_COL))
//STRIP001      {
//STRIP001          SchDataPoint* pSymPoint = GetDataPoint(*pObj);
//STRIP001          DBG_ASSERT(pSymPoint, "ChartModel::ChangeLegendPointAttr:Legenden-Symbol hat keine Datenpunkt-Information!")
//STRIP001          if (pSymPoint->GetCol() == nDataCol && pSymPoint->GetRow() == 0)
//STRIP001          {
//STRIP001 //-/             pObj->SetAttributes(aSymbolAttr, FALSE);
//STRIP001              pObj->SetItemSetAndBroadcast(aSymbolAttr);
//STRIP001
//STRIP001              DBG_ITEMS(aSymbolAttr,this);
//STRIP001              break;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 }
/*************************************************************************
|*
|* SubRoutine ChangeDataRowAttr, Legendenattributierung
|*
\************************************************************************/
//STRIP001 void ChartModel::ChangeLegendRowAttr(const long nDataRow,const SfxItemSet& rDataRowAttr)
//STRIP001 {
//STRIP001  CHART_TRACE( "ChartModel::ChangeLegendRowAttr" );
//STRIP001
//STRIP001  //Attributsets für die Symbole füllen:
//STRIP001  SfxItemSet aSymbolAttr(rDataRowAttr); //#54870#
//STRIP001  GenerateSymbolAttr(aSymbolAttr,nDataRow,SYMBOLMODE_LEGEND);
//STRIP001
//STRIP001  SdrPage* pPage=GetPage(0);
//STRIP001  SdrObjGroup* pLegendObj =(SdrObjGroup*)GetObjWithId(CHOBJID_LEGEND, *pPage);
//STRIP001  DBG_ASSERT(pLegendObj, "ChartModel::ChangeLegendRowAttr:Legenden-Objekt nicht gefunden!");
//STRIP001
//STRIP001  SdrObjListIter aIterator(*pLegendObj->GetSubList(), IM_FLAT);
//STRIP001  while (aIterator.IsMore())
//STRIP001  {
//STRIP001      SdrObject* pObj = aIterator.Next();
//STRIP001      SchObjectId* pId = GetObjectId(*pObj);
//STRIP001
//STRIP001      if (pId && (pId->GetObjId() == CHOBJID_LEGEND_SYMBOL_ROW))
//STRIP001      {
//STRIP001          SchDataRow* pSymRow = GetDataRow(*pObj);
//STRIP001          if (pSymRow && pSymRow->GetRow() == nDataRow)
//STRIP001          {
//STRIP001 //-/             pObj->SetAttributes(aSymbolAttr, FALSE);
//STRIP001              pObj->SetItemSetAndBroadcast(aSymbolAttr);
//STRIP001
//STRIP001              DBG_ITEMS(aSymbolAttr,this);
//STRIP001              break;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 }

/*************************************************************************
|*
|* ChangeDataRow-Submethode: Attributiere CHOBJID_DIAGRAM_DESCR_SYMBOL
|*
\************************************************************************/

//STRIP001 void ChartModel::ChangeRowDescrSymbolAttr(const long nDataRow,const SfxItemSet& rDataRowAttr)
//STRIP001 {
//STRIP001  CHART_TRACE( "ChartModel::ChangeRowDescrSymbolAttr" );
//STRIP001
//STRIP001  //Attributsets für die Symbole füllen:
//STRIP001  SfxItemSet aSymbolAttr(rDataRowAttr); //#54870#
//STRIP001  GenerateSymbolAttr(aSymbolAttr,nDataRow,SYMBOLMODE_DESCRIPTION);
//STRIP001
//STRIP001  SdrObjGroup* pDiagramObj
//STRIP001                  = (SdrObjGroup*)GetObjWithId(CHOBJID_DIAGRAM, *GetPage(0));
//STRIP001  DBG_ASSERT(pDiagramObj, "ChartModel::ChangeRowDescrSymbolAttr:Diagramm-Objekt nicht gefunden!");
//STRIP001
//STRIP001  BOOL bBreak = FALSE;
//STRIP001
//STRIP001  SdrObjListIter aIter1(*pDiagramObj->GetSubList(), IM_FLAT);
//STRIP001  while (!bBreak && aIter1.IsMore())
//STRIP001  {
//STRIP001      SdrObject* pObj1 = aIter1.Next();
//STRIP001
//STRIP001      if (pObj1)
//STRIP001      {
//STRIP001          SchObjectId* pId1 = GetObjectId(*pObj1);
//STRIP001
//STRIP001          if (pId1)
//STRIP001              if (pId1->GetObjId() == CHOBJID_DIAGRAM_DESCRGROUP)
//STRIP001              {
//STRIP001                  SdrObjListIter aIter2(*((SdrObjGroup*)pObj1)->GetSubList(),
//STRIP001                                        IM_FLAT);
//STRIP001                  while (aIter2.IsMore())
//STRIP001                  {
//STRIP001                      SdrObject* pObj2 = aIter2.Next();
//STRIP001                      SchObjectId* pId2 = GetObjectId(*pObj2);
//STRIP001
//STRIP001                      //#54870# auch _COL attributiert werden, BuildChart tut es schliesslich auch!
//STRIP001                      if (pId2
//STRIP001                          && ((pId2->GetObjId() == CHOBJID_DIAGRAM_DESCR_ROW)
//STRIP001                           || (pId2->GetObjId() == CHOBJID_DIAGRAM_DESCR_COL) )
//STRIP001                          && pObj2->ISA(SdrObjGroup))
//STRIP001                      {
//STRIP001                          SchDataRow*   pSymRow  = GetDataRow(*pObj2);
//STRIP001                          SchDataPoint* pSymPoint= GetDataPoint(*pObj2);
//STRIP001                          if( pSymRow || pSymPoint )
//STRIP001                          {
//STRIP001                              long nRow;
//STRIP001                              if(pSymRow)
//STRIP001                                  nRow=pSymRow->GetRow();
//STRIP001                              else
//STRIP001                                  nRow=pSymPoint->GetRow();
//STRIP001
//STRIP001                              if (nRow == nDataRow)
//STRIP001                              {
//STRIP001                                  SdrObjListIter aIter3
//STRIP001                                      (*((SdrObjGroup*)pObj2)->GetSubList(),
//STRIP001                                       IM_FLAT);
//STRIP001                                  while (aIter3.IsMore())
//STRIP001                                  {
//STRIP001                                      SdrObject* pObj3 = aIter3.Next();
//STRIP001                                      SchObjectId* pId3 = GetObjectId(*pObj3);
//STRIP001
//STRIP001                                      if (pId3 &&
//STRIP001                                          (pId3->GetObjId() == CHOBJID_DIAGRAM_DESCR_SYMBOL))
//STRIP001                                      {
//STRIP001 //-/                                         pObj3->SetAttributes(aSymbolAttr,FALSE);
//STRIP001                                          pObj3->SetItemSetAndBroadcast(aSymbolAttr);
//STRIP001                                          break;
//STRIP001                                      }
//STRIP001                                  }
//STRIP001                                  bBreak = TRUE;
//STRIP001                              }
//STRIP001                          }
//STRIP001                      }
//STRIP001                  }
//STRIP001              }
//STRIP001      }
//STRIP001  }
//STRIP001 }

/*************************************************************************
|*
|* ChangeDataRow-Submethode: GetDataRowObj
|*
\************************************************************************/
//STRIP001 SdrObject* ChartModel::CDRAGetDataRowObj(const long nDataRow)
//STRIP001 {
//STRIP001  SdrObject* pRetObj = NULL;
//STRIP001  SdrObjGroup* pDiagramObj = (SdrObjGroup*)GetObjWithId(CHOBJID_DIAGRAM, *GetPage(0));
//STRIP001  DBG_ASSERT(pDiagramObj, "ChartModel::CDRAGetDataRowObj:Diagramm-Objekt nicht gefunden!");
//STRIP001
//STRIP001  SdrObjListIter aIterator(*pDiagramObj->GetSubList(), IM_FLAT);
//STRIP001  while (aIterator.IsMore())
//STRIP001  {
//STRIP001      SdrObject* pObj = aIterator.Next();
//STRIP001      SchObjectId* pId = GetObjectId(*pObj);
//STRIP001
//STRIP001      if (pId)
//STRIP001      {
//STRIP001          UINT16 nId = pId->GetObjId();
//STRIP001          if (nId == CHOBJID_DIAGRAM_ROWGROUP || nId == CHOBJID_DIAGRAM_ROWS)
//STRIP001          {
//STRIP001              if (GetDataRow(*pObj)->GetRow() == nDataRow)
//STRIP001              {
//STRIP001                  pRetObj = pObj;
//STRIP001                  break;
//STRIP001              }
//STRIP001          }
//STRIP001          else if(nId==CHOBJID_DIAGRAM_STACKEDGROUP)
//STRIP001          {
//STRIP001              SdrObjListIter aIterator(*pObj->GetSubList(), IM_FLAT);
//STRIP001              while (aIterator.IsMore())
//STRIP001              {
//STRIP001                  SdrObject* pObj = aIterator.Next();
//STRIP001                  SchObjectId* pId = GetObjectId(*pObj);
//STRIP001
//STRIP001                  if (pId)
//STRIP001                  {
//STRIP001                      UINT16 nId = pId->GetObjId();
//STRIP001                      if (nId == CHOBJID_DIAGRAM_SPECIAL_GROUP)
//STRIP001                          if (GetDataRow(*pObj)->GetRow() == nDataRow)
//STRIP001                          {
//STRIP001                              pRetObj = pObj;
//STRIP001                              break;
//STRIP001                          }
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  return pRetObj;
//STRIP001 }

/*************************************************************************
|*
|* SubRoutine ChangeDataRowAttr, Attributiere Elemente
|*
\************************************************************************/
//STRIP001 void ChartModel::CDRAAttrGroup(SdrObject* pDataRowObj,const long nDataRow
//STRIP001                             ,const SfxItemSet& rDataRowAttr)
//STRIP001 {
//STRIP001
//STRIP001  BOOL bRepaint=FALSE;
//STRIP001
//STRIP001  SdrObjListIter aIterator(*((SdrObjGroup*)pDataRowObj)->
//STRIP001                              GetSubList(), IM_FLAT);
//STRIP001  while (aIterator.IsMore())
//STRIP001  {
//STRIP001      SdrObject* pObj = aIterator.Next();
//STRIP001      SchObjectId* pId = GetObjectId(*pObj);
//STRIP001
//STRIP001      if (pId)
//STRIP001      {
//STRIP001
//STRIP001          switch (pId->GetObjId())
//STRIP001          {
//STRIP001          case CHOBJID_DIAGRAM_DATA:
//STRIP001              {
//STRIP001                  bRepaint=TRUE;
//STRIP001                  if( HasSymbols(nDataRow) )
//STRIP001                  {
//STRIP001                      SfxItemSet aSymbolAttr(rDataRowAttr);
//STRIP001                      GenerateSymbolAttr(aSymbolAttr,nDataRow,SYMBOLMODE_ROW);
//STRIP001 //-/                     pObj->SetAttributes(aSymbolAttr, FALSE);
//STRIP001                      pObj->SetItemSetAndBroadcast(aSymbolAttr);
//STRIP001                  }
//STRIP001                  else
//STRIP001                  {
//STRIP001 //-/                     pObj->SetAttributes(rDataRowAttr, FALSE);
//STRIP001                      pObj->SetItemSetAndBroadcast(rDataRowAttr);
//STRIP001                  }
//STRIP001              }
//STRIP001              break;
//STRIP001
//STRIP001
//STRIP001          case CHOBJID_LINE:
//STRIP001          case CHOBJID_AREA:
//STRIP001          case CHOBJID_DIAGRAM_ROWSLINE:
//STRIP001          case CHOBJID_DIAGRAM_ROWS:
//STRIP001              bRepaint=TRUE;
//STRIP001 //-/             pObj->SetAttributes(rDataRowAttr,FALSE);
//STRIP001              pObj->SetItemSetAndBroadcast(rDataRowAttr);
//STRIP001              break;
//STRIP001
//STRIP001
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 //   if(bRepaint)
//STRIP001 //       pScene->SendRepaintBroadcast();
//STRIP001
//STRIP001 }
/*************************************************************************
|*
|* Erstelle Symbole fuer Diagrammtypen mit Symbolen
|*
\************************************************************************/

/*N*/ SdrObject* ChartModel::CreateSymbol (Point      aPoint,
/*N*/                                    int        nRow,
/*N*/                                    int        nColumn,
/*N*/                                    SfxItemSet &aDataAttr,
/*N*/                                    long       nSymbolSize,
/*N*/                                    BOOL       bInsert)
/*N*/ {
/*N*/   long nWhatSymbol=SVX_SYMBOLTYPE_AUTO;
/*N*/   SdrObject* pObj=NULL;
/*N*/   long nHalfSymbolSizeX = nSymbolSize / 4;
/*N*/   long nHalfSymbolSizeY = nSymbolSize / 4;
/*N*/   Size aSize(1,1);
/*N*/   long n1Pixel=pRefOutDev ? pRefOutDev->PixelToLogic(aSize).Width() : nHalfSymbolSizeY/2;
/*N*/
/*N*/   if(!bInsert)
/*N*/       n1Pixel=nHalfSymbolSizeY/2; //für Legende vergrößern
/*N*/
/*N*/   const SfxPoolItem* pPoolItem;
/*N*/   if(aDataAttr.GetItemState(SCHATTR_STYLE_SYMBOL, TRUE, &pPoolItem) == SFX_ITEM_SET)
/*N*/   {
/*N*/       nWhatSymbol = ((const SfxInt32Item*) pPoolItem)->GetValue();
/*N*/   }
/*N*/   if(nWhatSymbol<0)
/*N*/   {
/*N*/       BOOL bStock=FALSE;
/*N*/       switch(nWhatSymbol)
/*N*/       {
/*N*/           case SVX_SYMBOLTYPE_NONE:
/*N*/           {
/*N*/               //  Create a square as symbol.  Its fill and line style is
/*N*/               //  later to invisible.  This does not show the symbol but
/*N*/               //  leaves the data point selectable.
/*N*/               XPolygon aPolygon (5);
/*N*/               aPolygon[0].X() = aPoint.X() - nHalfSymbolSizeX;
/*N*/               aPolygon[0].Y() = aPoint.Y() - nHalfSymbolSizeY;
/*N*/               aPolygon[1].X() = aPoint.X() - nHalfSymbolSizeX;
/*N*/               aPolygon[1].Y() = aPoint.Y() + nHalfSymbolSizeY;
/*N*/               aPolygon[2].X() = aPoint.X() + nHalfSymbolSizeX;
/*N*/               aPolygon[2].Y() = aPoint.Y() + nHalfSymbolSizeY;
/*N*/               aPolygon[3].X() = aPoint.X() + nHalfSymbolSizeX;
/*N*/               aPolygon[3].Y() = aPoint.Y() - nHalfSymbolSizeY;
/*N*/               aPolygon[4].X() = aPolygon[0].X();
/*N*/               aPolygon[4].Y() = aPolygon[0].Y();
/*N*/               pObj = new SdrPathObj(OBJ_POLY, XPolyPolygon(aPolygon));
/*N*/               break;
/*N*/           }
/*N*/           case SVX_SYMBOLTYPE_UNKNOWN:
/*N*/           case SVX_SYMBOLTYPE_AUTO:
/*N*/               CHART_TRACE( "creating SVX_SYMBOLTYPE_AUTO" );
/*N*/
/*N*/
/*N*/               switch(eChartStyle)
/*N*/               {
/*N*/                       default:
/*N*/                       break;
/*N*/                       case CHSTYLE_2D_STOCK_2:
/*N*/                       case CHSTYLE_2D_STOCK_4:
/*N*/                           bStock=TRUE;
/*N*/                           nHalfSymbolSizeX=n1Pixel;
/*N*/                           break;
/*N*/                       case CHSTYLE_2D_STOCK_1:
/*N*/                           bStock=TRUE;
/*N*/                           if(nRow!=2)
/*N*/                               nHalfSymbolSizeX=n1Pixel;
/*N*/                           break;
/*N*/                       case CHSTYLE_2D_STOCK_3:
/*?*/                           bStock=TRUE;
/*?*/                           if(nRow!=3)
/*?*/                               nHalfSymbolSizeX=n1Pixel;
/*N*/                           break;
/*N*/               }
/*N*/               if(bStock)
/*N*/               {
/*N*/                   XPolygon aPolygon(2);
/*N*/
/*N*/                   aPolygon[0].X() = aPoint.X();
/*N*/                   aPolygon[0].Y() = aPoint.Y();
/*N*/                   aPolygon[1].X() = aPoint.X() + nHalfSymbolSizeX;
/*N*/                   aPolygon[1].Y() = aPoint.Y();
/*N*/                   pObj = new SdrPathObj(OBJ_POLY, XPolyPolygon(aPolygon));
/*N*/                   break;
/*N*/               }
/*N*/               nWhatSymbol=nRow;
/*N*/               aDataAttr.ClearItem(SCHATTR_SYMBOL_BRUSH);//Größe gegebenenfalls löschen
/*N*/               aDataAttr.ClearItem(SCHATTR_SYMBOL_SIZE);//Größe gegebenenfalls löschen
/*N*/               break;
/*N*/
/*N*/           case SVX_SYMBOLTYPE_BRUSHITEM:
/*N*/           {
/*?*/               if(aDataAttr.GetItemState(SCHATTR_SYMBOL_BRUSH,TRUE,&pPoolItem)==SFX_ITEM_SET)
/*?*/               {
/*?*/                   CHART_TRACE( "creating SVX_SYMBOLTYPE_BRUSHITEM" );
/*?*/                   const Graphic*  pGraphic = ((const SvxBrushItem *)pPoolItem)->GetGraphic();
/*?*/                   Size            aSize;
/*?*/
/*?*/                   if( pGraphic )
/*?*/                   {
/*?*/                       if(!pObj && aDataAttr.GetItemState(SCHATTR_SYMBOL_SIZE,TRUE,&pPoolItem)==SFX_ITEM_SET)
/*?*/                       {
/*?*/                           CHART_TRACE( "Size by Item" );
/*?*/                           aSize=((const SvxSizeItem*)pPoolItem)->GetSize();
/*?*/                       }
/*?*/                       else
/*?*/                       {
/*?*/                           CHART_TRACE( "Size by Graphic" );
/*?*/                           if( pGraphic )
/*?*/                               aSize = ( OutputDevice::LogicToLogic( pGraphic->GetPrefSize(),
/*?*/                                                                     pGraphic->GetPrefMapMode(),
/*?*/                                                                     MAP_100TH_MM ));
/*?*/                       }
/*?*/
/*?*/                       Rectangle   aRect(aPoint.X()-aSize.Width()/2,aPoint.Y()-aSize.Height()/2
/*?*/                                         ,aPoint.X()+aSize.Width()/2,aPoint.Y()+aSize.Height()/2);
/*?*/                       pObj      = new SdrGrafObj(*pGraphic);
/*?*/                       GetPage(0)->NbcInsertObject(pObj,0);
/*?*/                       pObj->NbcSetSnapRect(aRect);
/*?*/                       GetPage(0)->RemoveObject(0);
/*?*/                   }
/*?*/               }
/*?*/               else
/*?*/               {
/*?*/                   CHART_TRACE( "failed in SVX_SYMBOLTYPE_BRUSHITEM" );
/*?*/                   nWhatSymbol=nRow;
/*?*/               }
/*N*/           }
/*N*/           break;
/*N*/       }
/*N*/   }
/*N*/   else
/*N*/   {
/*?*/       CHART_TRACE1( "creating SVX_SYMBOLTYPE = %d", nWhatSymbol );
/*N*/   }
/*N*/
/*N*/
/*N*/   if(!pObj && aDataAttr.GetItemState(SCHATTR_SYMBOL_SIZE,TRUE,&pPoolItem)==SFX_ITEM_SET)
/*N*/   {
/*?*/       Size aSize=((const SvxSizeItem*)pPoolItem)->GetSize();
/*?*/       nHalfSymbolSizeX = aSize.Width() / 2;
/*?*/       nHalfSymbolSizeY = aSize.Height() / 2;
/*?*/       CHART_TRACE2( "reading SCHATTR_SYMBOL_SIZE -> Size = (%ld, %ld)", aSize.Width(), aSize.Height() );
/*N*/   }
/*N*/
/*N*/   if(!pObj) //dann default generieren
/*N*/   {
/*N*/       switch (nWhatSymbol % 8)
/*N*/       {
/*N*/           case 0 :
/*N*/           {
/*N*/               XPolygon aPolygon (5);
/*N*/
/*N*/               aPolygon[0].X() = aPoint.X() - nHalfSymbolSizeX;
/*N*/               aPolygon[0].Y() = aPoint.Y() - nHalfSymbolSizeY;
/*N*/               aPolygon[1].X() = aPoint.X() - nHalfSymbolSizeX;
/*N*/               aPolygon[1].Y() = aPoint.Y() + nHalfSymbolSizeY;
/*N*/               aPolygon[2].X() = aPoint.X() + nHalfSymbolSizeX;
/*N*/               aPolygon[2].Y() = aPoint.Y() + nHalfSymbolSizeY;
/*N*/               aPolygon[3].X() = aPoint.X() + nHalfSymbolSizeX;
/*N*/               aPolygon[3].Y() = aPoint.Y() - nHalfSymbolSizeY;
/*N*/               aPolygon[4].X() = aPolygon[0].X();
/*N*/               aPolygon[4].Y() = aPolygon[0].Y();
/*N*/
/*N*/               pObj = new SdrPathObj(OBJ_POLY, XPolyPolygon(aPolygon));
/*N*/               break;
/*N*/           }
/*N*/
/*N*/           case 1 :
/*N*/           {
/*N*/               XPolygon aPolygon (5);
/*N*/
/*N*/               aPolygon[0].X() = aPoint.X();
/*N*/               aPolygon[0].Y() = aPoint.Y() - nHalfSymbolSizeY;
/*N*/               aPolygon[1].X() = aPoint.X() + nHalfSymbolSizeX;
/*N*/               aPolygon[1].Y() = aPoint.Y();
/*N*/               aPolygon[2].X() = aPoint.X();
/*N*/               aPolygon[2].Y() = aPoint.Y() + nHalfSymbolSizeY;;
/*N*/               aPolygon[3].X() = aPoint.X() - nHalfSymbolSizeX;
/*N*/               aPolygon[3].Y() = aPoint.Y();
/*N*/               aPolygon[4].X() = aPolygon[0].X();
/*N*/               aPolygon[4].Y() = aPolygon[0].Y();
/*N*/
/*N*/               pObj = new SdrPathObj(OBJ_POLY, XPolyPolygon(aPolygon));
/*N*/               break;
/*N*/           }
/*N*/
/*N*/           case 2 :
/*N*/           {
/*N*/               XPolygon aPolygon (4);
/*N*/
/*N*/               aPolygon[0].X() = aPoint.X() - nHalfSymbolSizeX;
/*N*/               aPolygon[0].Y() = aPoint.Y() - nHalfSymbolSizeY;
/*N*/               aPolygon[1].X() = aPoint.X() + nHalfSymbolSizeX;
/*N*/               aPolygon[1].Y() = aPoint.Y() - nHalfSymbolSizeY;
/*N*/               aPolygon[2].X() = aPoint.X();
/*N*/               aPolygon[2].Y() = aPoint.Y() + nHalfSymbolSizeY;
/*N*/               aPolygon[3].X() = aPolygon[0].X();
/*N*/               aPolygon[3].Y() = aPolygon[0].Y();
/*N*/
/*N*/               pObj = new SdrPathObj(OBJ_POLY, XPolyPolygon(aPolygon));
/*N*/               break;
/*N*/           }
/*N*/
/*N*/           case 3 :
/*N*/           {
/*N*/               XPolygon aPolygon (4);
/*N*/
/*N*/               aPolygon[0].X() = aPoint.X() - nHalfSymbolSizeX;
/*N*/               aPolygon[0].Y() = aPoint.Y() + nHalfSymbolSizeY;
/*N*/               aPolygon[1].X() = aPoint.X() + nHalfSymbolSizeX;
/*N*/               aPolygon[1].Y() = aPoint.Y() + nHalfSymbolSizeY;
/*N*/               aPolygon[2].X() = aPoint.X();
/*N*/               aPolygon[2].Y() = aPoint.Y() - nHalfSymbolSizeY;
/*N*/               aPolygon[3].X() = aPolygon[0].X();
/*N*/               aPolygon[3].Y() = aPolygon[0].Y();
/*N*/
/*N*/               pObj = new SdrPathObj(OBJ_POLY, XPolyPolygon(aPolygon));
/*N*/               break;
/*N*/           }
/*N*/
/*N*/           case 4 :
/*N*/           {
/*?*/               XPolygon aPolygon (4);
/*?*/
/*?*/               aPolygon[0].X() = aPoint.X() - nHalfSymbolSizeX;
/*?*/               aPolygon[0].Y() = aPoint.Y() - nHalfSymbolSizeY;
/*?*/               aPolygon[1].X() = aPoint.X() + nHalfSymbolSizeX;
/*?*/               aPolygon[1].Y() = aPoint.Y();
/*?*/               aPolygon[2].X() = aPoint.X() - nHalfSymbolSizeX;
/*?*/               aPolygon[2].Y() = aPoint.Y() + nHalfSymbolSizeY;
/*?*/               aPolygon[3].X() = aPolygon[0].X();
/*?*/               aPolygon[3].Y() = aPolygon[0].Y();
/*?*/
/*?*/               pObj = new SdrPathObj(OBJ_POLY, XPolyPolygon(aPolygon));
/*?*/               break;
/*?*/           }
/*?*/
/*?*/           case 5 :
/*?*/           {
/*?*/               XPolygon aPolygon (4);
/*?*/
/*?*/               aPolygon[0].X() = aPoint.X() + nHalfSymbolSizeX;
/*?*/               aPolygon[0].Y() = aPoint.Y() - nHalfSymbolSizeY;
/*?*/               aPolygon[1].X() = aPoint.X() - nHalfSymbolSizeX;
/*?*/               aPolygon[1].Y() = aPoint.Y();
/*?*/               aPolygon[2].X() = aPoint.X() + nHalfSymbolSizeX;
/*?*/               aPolygon[2].Y() = aPoint.Y() + nHalfSymbolSizeY;
/*?*/               aPolygon[3].X() = aPolygon[0].X();
/*?*/               aPolygon[3].Y() = aPolygon[0].Y();
/*?*/
/*?*/               pObj = new SdrPathObj(OBJ_POLY, XPolyPolygon(aPolygon));
/*?*/               break;
/*?*/           }
/*?*/
/*?*/           case 6 :
/*?*/           {
/*?*/               XPolygon aPolygon (5);
/*?*/
/*?*/               aPolygon[0].X() = aPoint.X() - nHalfSymbolSizeX;
/*?*/               aPolygon[0].Y() = aPoint.Y() - nHalfSymbolSizeY;
/*?*/               aPolygon[1].X() = aPoint.X() + nHalfSymbolSizeX;
/*?*/               aPolygon[1].Y() = aPoint.Y() + nHalfSymbolSizeY;
/*?*/               aPolygon[2].X() = aPoint.X() + nHalfSymbolSizeX;
/*?*/               aPolygon[2].Y() = aPoint.Y() - nHalfSymbolSizeY;
/*?*/               aPolygon[3].X() = aPoint.X() - nHalfSymbolSizeX;
/*?*/               aPolygon[3].Y() = aPoint.Y() + nHalfSymbolSizeY;
/*?*/               aPolygon[4].X() = aPolygon[0].X();
/*?*/               aPolygon[4].Y() = aPolygon[0].Y();
/*?*/
/*?*/               pObj = new SdrPathObj(OBJ_POLY, XPolyPolygon(aPolygon));
/*?*/               break;
/*?*/           }
/*?*/
/*?*/           case 7 :
/*?*/           {
/*?*/               XPolygon aPolygon (5);
/*?*/
/*?*/               aPolygon[0].X() = aPoint.X() - nHalfSymbolSizeX;
/*?*/               aPolygon[0].Y() = aPoint.Y() - nHalfSymbolSizeY;
/*?*/               aPolygon[1].X() = aPoint.X() + nHalfSymbolSizeX;
/*?*/               aPolygon[1].Y() = aPoint.Y() + nHalfSymbolSizeY;
/*?*/               aPolygon[2].X() = aPoint.X() - nHalfSymbolSizeX;
/*?*/               aPolygon[2].Y() = aPoint.Y() + nHalfSymbolSizeY;
/*?*/               aPolygon[3].X() = aPoint.X() + nHalfSymbolSizeX;
/*?*/               aPolygon[3].Y() = aPoint.Y() - nHalfSymbolSizeY;
/*?*/               aPolygon[4].X() = aPolygon[0].X();
/*?*/               aPolygon[4].Y() = aPolygon[0].Y();
/*?*/
/*?*/               pObj = new SdrPathObj(OBJ_POLY, XPolyPolygon(aPolygon));
/*?*/               break;
/*?*/           }
/*?*/
/*N*/       }
/*N*/   }
/*N*/
/*N*/   if (bInsert)  //nur in CreateLegend FALSE!
/*N*/   {
/*N*/       SfxItemSet aSymbolAttr(aDataAttr);
/*N*/       GenerateSymbolAttr(aSymbolAttr,nRow,SYMBOLMODE_ROW);
/*N*/       if (nWhatSymbol == SVX_SYMBOLTYPE_NONE)
/*N*/       {
/*N*/           //  Don´t show the symbol.  It is only needed for selection of the
/*N*/           //  data point.
/*N*/           aSymbolAttr.Put(XFillStyleItem (XFILL_NONE));
/*N*/           aSymbolAttr.Put(XLineStyleItem (XLINE_NONE));
/*N*/       }
/*N*/       pObj->SetModel( this );
/*N*/       pObj = SetObjectAttr (pObj, CHOBJID_DIAGRAM_DATA, TRUE, TRUE, &aSymbolAttr);
/*N*/       pObj->InsertUserData(new SchDataPoint(nColumn, nRow));
/*N*/
/*N*/   }
/*N*/
/*N*/   return pObj;
/*N*/ }

/*N*/ void ChartModel::GenerateSymbolAttr(/*const SfxItemSet& rAttr,*/SfxItemSet& rSymbolAttr,const long nRow,const long nMode)
/*N*/ {
/*N*/   // Symbole immer gleiche Umrandung und Füllfarbe = Linienfarbe, wenn es sich um ein "echtes"
/*N*/   // Symbol handelt (d.h. nicht ein Symbol für Bars/Säulen,Pies etc.)
/*N*/
/*N*/   switch(nMode)
/*N*/   {
/*N*/       case SYMBOLMODE_LEGEND:
/*N*/       case SYMBOLMODE_ROW:
/*N*/
/*N*/           if(HasSymbols(nRow) && IsLine(nRow)) //Symbol und Linie => ein echtes Symbol wird angezeigt :)
/*N*/           {
/*N*/               rSymbolAttr.Put(XFillColorItem(String(),
/*N*/                                              ((XLineColorItem &)rSymbolAttr.Get(XATTR_LINECOLOR)).GetValue()));
/*N*/
/*N*/               rSymbolAttr.Put(XLineStyleItem(XLINE_SOLID));
/*N*/               rSymbolAttr.Put(XLineColorItem(String(),RGBColor(COL_BLACK)));
/*N*/               rSymbolAttr.Put(XLineWidthItem (0));
/*N*/
/*N*/           }
/*N*/           break;
/*N*/
/*N*/       case SYMBOLMODE_DESCRIPTION:
/*?*/           if(IsLine(nRow))
/*?*/           {
/*?*/               rSymbolAttr.Put(XFillColorItem(String(),
/*?*/                                              ((XLineColorItem &)rSymbolAttr.Get(XATTR_LINECOLOR)).GetValue()));
/*?*/
/*?*/               rSymbolAttr.Put(XLineStyleItem(XLINE_SOLID));
/*?*/               rSymbolAttr.Put(XLineColorItem(String(),RGBColor(COL_BLACK)));
/*?*/               rSymbolAttr.Put(XLineWidthItem (0));
/*?*/           }
/*?*/           else        // rectangle with border, if linesytle is NONE
/*?*/           {
/*?*/               XLineStyle eLineStyle =
/*?*/                   SAL_STATIC_CAST( const XLineStyleItem *, &(rSymbolAttr.Get( XATTR_LINESTYLE )) )->GetValue(); // bug in Win-C++ compiler: casting to pointer
/*?*/
/*?*/               if( eLineStyle == XLINE_NONE )            // clear items for defaults to take effect
/*?*/               {
/*?*/                   rSymbolAttr.ClearItem( XATTR_LINESTYLE );
/*?*/                   rSymbolAttr.ClearItem( XATTR_LINEWIDTH );
/*?*/                   rSymbolAttr.ClearItem( XATTR_LINECOLOR );
/*?*/               }
/*N*/           }
/*N*/
/*N*/           break;
/*N*/       case SYMBOLMODE_LINE:
/*N*/           break;
/*N*/   }
/*N*/
/*N*/ }

/*************************************************************************
|*
|* Datenreihen-Attribute aendern;
|* Liefert bei geaenderten Attributen TRUE.
|*
\************************************************************************/
//#54870# gravierende Änderung, notfalls mit BuildChart abschliessen!
//STRIP001 BOOL ChartModel::ChangeDataRowAttr(const SfxItemSet& rAttr, long nRow,BOOL bMerge)
//STRIP001 {
//STRIP001  if(nRow>=GetRowCount()) //Vermutlich unnötig, nur falls Undo schiefläuft
//STRIP001      return FALSE;
//STRIP001
//STRIP001  PutDataRowAttr(nRow, rAttr,bMerge);
//STRIP001
//STRIP001  const SfxPoolItem* pPoolItem=NULL;
//STRIP001  if(rAttr.GetItemState(SCHATTR_AXIS,TRUE, &pPoolItem) == SFX_ITEM_SET)
//STRIP001  {
//STRIP001      if(((const SfxInt32Item*)pPoolItem)->GetValue()==CHART_AXIS_SECONDARY_Y)
//STRIP001      {
//STRIP001          pChartBAxis->ShowDescr(TRUE);
//STRIP001          pChartBAxis->ShowAxis(TRUE);
//STRIP001
//STRIP001      }
//STRIP001      CheckForNewAxisNumFormat();     // #71678#
//STRIP001  }
//STRIP001
//STRIP001  if( (eChartStyle==CHSTYLE_3D_PIE) || IsAttrChangeNeedsBuildChart(rAttr))
//STRIP001  {
//STRIP001      BuildChart(FALSE);
//STRIP001      return TRUE;             //Dann kann man sich den ganzen Rest sparen!
//STRIP001  }
//STRIP001
//STRIP001  const SfxItemSet& rDataRowAttr = GetDataRowAttr(nRow);
//STRIP001
//STRIP001  //Legende attributieren
//STRIP001  if (GetShowLegend())
//STRIP001     ChangeLegendRowAttr(nRow,rDataRowAttr);//#54870# Legendensymbole attr.
//STRIP001
//STRIP001  //Beschriftungen attributieren
//STRIP001  if( (eDataDescr != CHDESCR_NONE) && bShowDataDescr) //alle anderen Symbole attr.
//STRIP001      ChangeRowDescrSymbolAttr(nRow,rDataRowAttr);
//STRIP001
//STRIP001  //Datenreihenobjekt(gruppe) holen
//STRIP001  SchObjectId* pObjId=NULL;
//STRIP001  SdrObject*   pDataRowObj = CDRAGetDataRowObj(nRow);
//STRIP001  if (pDataRowObj)
//STRIP001      pObjId = GetObjectId(*pDataRowObj);
//STRIP001  else
//STRIP001  {
//STRIP001      DBG_ERROR("ChartModel::ChangeDataRowAttr: no DataRowGroup! - calling BuildChart()");
//STRIP001      BuildChart(FALSE); //die BruteForce-Methode wirkt immer
//STRIP001      return TRUE;
//STRIP001  }
//STRIP001
//STRIP001  //ToDo: ab hier kann noch viel optimiert werden!!! z.B. Pies dürften nie betroffen sein
//STRIP001  if(pObjId)
//STRIP001  {
//STRIP001      BOOL bAuto=SetAttrAutoStorage(FALSE);
//STRIP001
//STRIP001      switch (pObjId->GetObjId())
//STRIP001      {
//STRIP001          case CHOBJID_DIAGRAM_ROWGROUP:
//STRIP001          case CHOBJID_DIAGRAM_SPECIAL_GROUP:
//STRIP001              CDRAAttrGroup(pDataRowObj,nRow,rDataRowAttr);
//STRIP001              break;
//STRIP001          case CHOBJID_DIAGRAM_ROWS:
//STRIP001          case CHOBJID_DIAGRAM_ROWSLINE:
//STRIP001 //-/             pDataRowObj->SetAttributes(rDataRowAttr, FALSE);
//STRIP001              pDataRowObj->SetItemSetAndBroadcast(rDataRowAttr);
//STRIP001              break;
//STRIP001      }
//STRIP001
//STRIP001 /*       if(   eChartStyle==CHSTYLE_3D_STRIPE
//STRIP001         || eChartStyle==CHSTYLE_2D_AREA
//STRIP001         || eChartStyle==CHSTYLE_2D_PERCENTAREA
//STRIP001         || eChartStyle==CHSTYLE_2D_STACKEDAREA
//STRIP001         )
//STRIP001          pDataRowObj->SetAttributes(rDataRowAttr, FALSE);      */
//STRIP001
//STRIP001      if(!IsLine(nRow) && !IsArea(nRow))
//STRIP001          if(Is3DChart())
//STRIP001              CopySpecialPointAttrToPage(nRow);
//STRIP001          else
//STRIP001              CopyPointAttrToPage(nRow);
//STRIP001
//STRIP001      SetAttrAutoStorage(bAuto);
//STRIP001      return TRUE;
//STRIP001  }
//STRIP001  else return FALSE;
//STRIP001 }

/*************************************************************************
|*
|* Datenpunkt-Attribute loeschen, die im Itemset (Argument) vorhanden sind
|*
\************************************************************************/

/*N*/ void ChartModel::ClearDataPointAttr( long nCol, long nRow, const SfxItemSet& rAttr )
/*N*/ {
/*N*/
/*N*/   CHART_TRACE( "ChartModel::ClearDataPointAttr" );
/*N*/
/*N*/   ItemSetList* pAttrList = IsDataSwitched()   //abhaengig vom Charttyp - statt bSwitchData
/*N*/                                ? &aSwitchDataPointAttrList
/*N*/                                : &aDataPointAttrList;
/*N*/
/*N*/   SfxItemSet* pItemSet = pAttrList->GetObject(nCol * GetRowCount() + nRow);
/*N*/   if (pItemSet != NULL)
/*?*/       {DBG_BF_ASSERT(0, "STRIP"); }//STRIP001 ClearDblItems(rAttr,*pItemSet);
/*N*/ }
/*************************************************************************
|*
|* Datenpunkt-Attribute setzen
|*
\************************************************************************/

/*N*/ void ChartModel::PutDataPointAttr( long nCol, long nRow,const SfxItemSet& rAttr, BOOL bMerge /*=TRUE*/)
/*N*/ {
/*N*/   CHART_TRACE( "ChartModel::PutDataPointAttr" );
/*N*/   DBG_ITEMS((SfxItemSet&)rAttr,this);
/*N*/
/*N*/   ItemSetList* pAttrList = IsDataSwitched()   //abhaengig vom Charttyp - statt bSwitchData
/*N*/                          ? &aSwitchDataPointAttrList
/*N*/                          : &aDataPointAttrList;
/*N*/
/*N*/   SfxItemSet* pItemSet = pAttrList->GetObject(nCol * GetRowCount() + nRow);
/*N*/   if (pItemSet == NULL)
/*N*/   {
/*N*/       pItemSet = new SfxItemSet(*pItemPool, nRowWhichPairs);
/*N*/       pAttrList->Replace (pItemSet, nCol * GetRowCount() + nRow);
/*N*/   }
/*N*/   if(!bMerge)
/*?*/       pItemSet->ClearItem();
/*N*/     PutItemSetWithNameCreation( *pItemSet, rAttr );
/*N*/ }

// this method exists in analogy to GetFullDataPointAttr
// it is necessary for API (=>XML) and pie charts
//STRIP001 void ChartModel::PutFullDataPointAttr(
//STRIP001  long nCol, long nRow,
//STRIP001  const SfxItemSet& rAttr )
//STRIP001 {
//STRIP001  PutDataPointAttr( nCol, nRow, rAttr );
//STRIP001
//STRIP001  if( IsPieChart())
//STRIP001  {
//STRIP001      // get only fill attribute
//STRIP001      SfxItemSet aColSet( *pItemPool, XATTR_FILLCOLOR, XATTR_FILLCOLOR );
//STRIP001      aColSet.Put( rAttr );
//STRIP001
//STRIP001      // set at series (only for pie charts)
//STRIP001      PutDataRowAttr( nCol % GetColCount(), rAttr, TRUE, FALSE );
//STRIP001  }
//STRIP001 }

/*************************************************************************
|*
|* Datenpunkt-Attribute ermitteln
|*
\************************************************************************/

/*N*/ const SfxItemSet& ChartModel::GetDataPointAttr( long nCol, long nRow) const
/*N*/ {
/*N*/   long nIdx = nCol * GetRowCount() + nRow;
/*N*/   ItemSetList& aAttrList = IsDataSwitched()
/*N*/       ? (class ItemSetList &) aSwitchDataPointAttrList
/*N*/       : (class ItemSetList &) aDataPointAttrList;
/*N*/
/*N*/   if( nIdx < (long)aAttrList.Count() )
/*N*/   {
/*N*/       SfxItemSet* pSet = aAttrList.GetObject( nIdx );
/*N*/       if (pSet == NULL)
/*N*/           return (GetDataRowAttr(nRow));
/*N*/       else
/*N*/           return *pSet;
/*N*/   }
/*N*/   else
/*N*/   {
/*?*/       DBG_ERROR( "Requested data point attribute is unavailable" );
/*?*/
/*?*/       // return something
/*?*/       DBG_ASSERT( pChartAttr, "Invalid Chart-ItemSet" );
/*?*/       return *pChartAttr;
/*N*/   }
/*N*/ }


/*N*/ const SfxItemSet * ChartModel::GetRawDataPointAttr    (long nCol,long nRow) const
/*N*/ {
/*N*/   long nIndex = nCol * GetRowCount() + nRow;
/*N*/   ItemSetList & aAttrList = IsDataSwitched()
/*N*/       ? (class ItemSetList &) aSwitchDataPointAttrList
/*N*/       : (class ItemSetList &) aDataPointAttrList;
/*N*/
/*N*/   if (nIndex < (long)aAttrList.Count())
/*N*/       return aAttrList.GetObject (nIndex);
/*N*/   else
/*N*/       return NULL;
/*N*/ }

/*************************************************************************
|*
|* Datenpunkt-Attribute ermitteln
|*
\************************************************************************/

/*N*/ SfxItemSet ChartModel::GetFullDataPointAttr( long nCol, long nRow ) const
/*N*/ {
/*N*/   ItemSetList* pAttrList = IsDataSwitched()
/*N*/         ? (class ItemSetList *) & aSwitchDataPointAttrList
/*N*/         : (class ItemSetList *) & aDataPointAttrList;
/*N*/
/*N*/   if( ! IsPieChart())
/*N*/   {
/*N*/         // get series' attributes and merge with data-point attributes if available
/*N*/       SfxItemSet aAttr( GetDataRowAttr( nRow ));
/*N*/       SfxItemSet *pObj=pAttrList->GetObject( nCol * GetRowCount() + nRow );
/*N*/       if( pObj )
/*N*/             aAttr.Put( *pObj );
/*N*/       return aAttr;
/*N*/   }

    /* the following code is for pie charts only

       data description attributes (SCHATTR_DATADESCR_DESCR and
       SCHATTR_DATADESCR_SHOW_SYM) are contained in data point item set while
       all other (graphical) attributes are contained in data series (data row)
       item set */

    // get data description attributes
/*N*/     SfxItemSet aDescrAttrib( *pItemPool, SCHATTR_DATADESCR_START, SCHATTR_DATADESCR_END );
/*N*/     aDescrAttrib.Put( GetDataRowAttr( 0 )); // a pie chart always has only one series
/*N*/
/*N*/     // the different pies use series attributes rather than data-point attributes
/*N*/     long nPieCount        = GetColCount();
/*N*/     long nSecondDimension = GetRowCount(); // pie has only one series, but the data may contain more
/*N*/
/*N*/   SfxItemSet aAttr( GetDataRowAttr( nCol % nPieCount ));
/*N*/
/*N*/     if( ( nCol >= nPieCount ) &&
/*N*/         pDefaultColors )
/*N*/     {
/*?*/         XColorEntry* pColEntry = SAL_STATIC_CAST( XColorEntry*, pDefaultColors->GetObject( nCol % pDefaultColors->Count()));
/*?*/         aAttr.Put( XFillColorItem( pColEntry->GetName(), pColEntry->GetColor()));
/*N*/     }
/*N*/
/*N*/     // add description attributes of series
/*N*/     aAttr.ClearItem( SCHATTR_DATADESCR_DESCR );
/*N*/     aAttr.ClearItem( SCHATTR_DATADESCR_SHOW_SYM );
/*N*/     aAttr.Put( aDescrAttrib );
/*N*/
/*N*/     SfxItemSet* pAttr = pAttrList->GetObject( nCol * nSecondDimension );
/*N*/     if( ( pAttr != NULL ) && pAttr->Count())
/*N*/         aAttr.Put( *pAttr );
/*N*/
/*N*/     return aAttr;
/*N*/ }

/*************************************************************************
|*
|* Datenpunkt-Attribute ermitteln
|*
\************************************************************************/

/*N*/ SfxItemSet& ChartModel::MergeDataPointAttr( SfxItemSet& rAttr, long nCol, long nRow ) const
/*N*/ {
/*N*/   CHART_TRACE2( "ChartModel::MergeDataPointAttr nCol=%ld, nRow=%ld", nCol, nRow );
/*N*/   ItemSetList* pAttrList = IsDataSwitched()   //abhaengig vom Charttyp - statt bSwitchData
/*N*/                                ? (class ItemSetList *) &aSwitchDataPointAttrList
/*N*/                                : (class ItemSetList *) &aDataPointAttrList;
/*N*/
/*N*/   SfxItemSet *pObj=pAttrList->GetObject(nCol * GetRowCount() + nRow);
/*N*/   if(pObj)
/*?*/       rAttr.Put(*pObj);
/*N*/   return rAttr;
/*N*/ }



/*N*/ BOOL  ChartModel::IsDataPointAttrSet  (long nCol, long nRow)  const
/*N*/ {
/*N*/   UINT32 nIndex = nCol * GetRowCount() + nRow;
/*N*/   ItemSetList& aAttrList = IsDataSwitched()
/*N*/       ? (class ItemSetList &) aSwitchDataPointAttrList
/*N*/       : (class ItemSetList &) aDataPointAttrList;
/*N*/
/*N*/   if (nIndex < static_cast<UINT32>(aAttrList.Count()))
/*N*/       return aAttrList.GetObject (nIndex) != NULL;
/*N*/   else
/*N*/       //  Specified data point does not exist.  Therefore an item set does not exist also.
/*?*/       return false;
/*N*/ }


/*************************************************************************
|*
|* ChangeDataPoint-Submethode: GetDataPointObj
|*
\************************************************************************/
//STRIP001 SdrObject* ChartModel::CDPAGetDataPointObj(const long nDataCol,const long nDataRow)
//STRIP001 {
//STRIP001
//STRIP001  SdrObject* pRetObj=NULL;
//STRIP001
//STRIP001  SdrObjGroup* pDiagramObj =
//STRIP001      (SdrObjGroup*)GetObjWithId(CHOBJID_DIAGRAM, *GetPage(0));
//STRIP001  DBG_ASSERT(pDiagramObj, "ChartModel::CDPAGetDataPointObj:Diagramm-Objekt nicht gefunden!");
//STRIP001
//STRIP001  SdrObjListIter aIterator(*pDiagramObj->GetSubList(), IM_FLAT);
//STRIP001  while (aIterator.IsMore())
//STRIP001  {
//STRIP001      SdrObject* pObj = aIterator.Next();
//STRIP001      SchObjectId* pId = GetObjectId(*pObj);
//STRIP001
//STRIP001      if (pId)
//STRIP001      {
//STRIP001          UINT16 nId = pId->GetObjId();
//STRIP001
//STRIP001          if (nId == CHOBJID_DIAGRAM_ROWGROUP)
//STRIP001          {
//STRIP001              SchDataRow* pRow = GetDataRow(*pObj);
//STRIP001              DBG_ASSERT(pRow, "ChartModel::CDPAGetDataPointObj:Objekt hat keine Datenreihen-Information!");
//STRIP001              if (pRow->GetRow() == nDataRow)
//STRIP001              {
//STRIP001                  SdrObjListIter aSubIter(*pObj->GetSubList(), IM_FLAT);
//STRIP001                  while (aSubIter.IsMore())
//STRIP001                  {
//STRIP001                      SdrObject* pSubObj = aSubIter.Next();
//STRIP001                      SchObjectId* pSubId = GetObjectId(*pSubObj);
//STRIP001
//STRIP001                      if (pSubId && (pSubId->GetObjId() == CHOBJID_DIAGRAM_DATA))
//STRIP001                      {
//STRIP001                          SchDataPoint* pPoint = GetDataPoint(*pSubObj);
//STRIP001                          DBG_ASSERT(pPoint, "ChartModel::CDPAGetDataPointObj:Objekt hat keine Datenpunkt-"
//STRIP001                                             "Information!");
//STRIP001                          if (pPoint->GetCol() == nDataCol &&
//STRIP001                              pPoint->GetRow() == 0)
//STRIP001                          {
//STRIP001                              pRetObj = pSubObj;
//STRIP001                              break;
//STRIP001                          }
//STRIP001                      }
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001          else if (nId == CHOBJID_DIAGRAM_DATA)
//STRIP001          {
//STRIP001              SchDataPoint* pPoint = GetDataPoint(*pObj);
//STRIP001              DBG_ASSERT(pPoint, "ChartModel::CDPAGetDataPointObj:Objekt hat keine Datenpunkt-"
//STRIP001                                 "Information!");
//STRIP001              if (pPoint->GetCol() == nDataCol &&
//STRIP001                  pPoint->GetRow() == 0)
//STRIP001              {
//STRIP001                  pRetObj = pObj;
//STRIP001                  break;
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  return pRetObj;
//STRIP001 }


/*************************************************************************
|*
|* ChangeDataPoint-Submethode: Attributiere CHOBJID_DIAGRAM_DESCR_SYMBOL
|*
\************************************************************************/

//STRIP001 void ChartModel::ChangePointDescrSymbolAttr(const long nCol,const long nRow,const SfxItemSet& rDataPointAttr)
//STRIP001 {
//STRIP001  CHART_TRACE( "ChartModel::ChangePointDescrSymbolAttr" );
//STRIP001
//STRIP001  //Attributsets für die Symbole füllen:
//STRIP001  SfxItemSet aSymbolAttr(rDataPointAttr); //#54870#
//STRIP001  GenerateSymbolAttr(aSymbolAttr,nRow,SYMBOLMODE_DESCRIPTION);
//STRIP001
//STRIP001  SdrObjGroup* pDiagramObj =
//STRIP001      (SdrObjGroup*)GetObjWithId(CHOBJID_DIAGRAM, *GetPage(0));
//STRIP001  DBG_ASSERT(pDiagramObj, "ChartModel::ChangePointDescrSymbolAttr:Diagramm-Objekt nicht gefunden!");
//STRIP001
//STRIP001  SdrObjListIter aIter1(*pDiagramObj->GetSubList(), IM_FLAT);
//STRIP001  while (aIter1.IsMore())
//STRIP001  {
//STRIP001      SdrObject* pObj1 = aIter1.Next();
//STRIP001      SchObjectId* pId1 = GetObjectId(*pObj1);
//STRIP001
//STRIP001      if (pId1 && (pId1->GetObjId() == CHOBJID_DIAGRAM_DESCR_COL) && pObj1->ISA(SdrObjGroup))
//STRIP001      {
//STRIP001          SchDataPoint* pSymPoint = GetDataPoint(*pObj1);
//STRIP001          if (pSymPoint &&
//STRIP001              pSymPoint->GetCol() == nCol &&
//STRIP001              pSymPoint->GetRow() == nRow)
//STRIP001              //#54870# Aus absolut unverständlichen Gründen stand oben statt nRow immer 0
//STRIP001          {
//STRIP001              SdrObjListIter aIter2
//STRIP001                  (*((SdrObjGroup*)pObj1)->GetSubList(), IM_FLAT);
//STRIP001              while (aIter2.IsMore())
//STRIP001              {
//STRIP001                  SdrObject* pObj2 = aIter2.Next();
//STRIP001                  SchObjectId* pId2 = GetObjectId(*pObj2);
//STRIP001
//STRIP001                  if (pId2 && (pId2->GetObjId() == CHOBJID_DIAGRAM_DESCR_SYMBOL))
//STRIP001                  {
//STRIP001 //-/                     pObj2->SetAttributes(aSymbolAttr, FALSE);
//STRIP001                      pObj2->SetItemSetAndBroadcast(aSymbolAttr);
//STRIP001                      break;
//STRIP001                  }
//STRIP001              }
//STRIP001
//STRIP001              break;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 }
/*************************************************************************
|*
|* Datenpunkt-Attribute aendern;
|* Liefert bei geaenderten Attributen TRUE.
|*
\************************************************************************/
//ToDo: der ganzen Quatsch da unten aufräumen
//STRIP001 BOOL ChartModel::ChangeDataPointAttr(const SfxItemSet& rAttr,
//STRIP001                                   SdrObject& rObj, BOOL bMerge,
//STRIP001                                   BOOL bBuildChart)
//STRIP001 {
//STRIP001  SchObjectId* pObjId = GetObjectId(rObj);
//STRIP001
//STRIP001
//STRIP001  if (pObjId)
//STRIP001  {
//STRIP001      SchDataPoint* pDataPoint = GetDataPoint(rObj);
//STRIP001      DBG_ASSERT(pDataPoint, "ChartModel::ChangeDataPointAttr:Objekt hat keine Datenpunkt-Information!");
//STRIP001
//STRIP001      short nDataCol = pDataPoint->GetCol();
//STRIP001      short nDataRow = pDataPoint->GetRow();
//STRIP001
//STRIP001      PutDataPointAttr(nDataCol, nDataRow, rAttr,bMerge);
//STRIP001
//STRIP001      SfxItemSet aDataPointAttr(GetFullDataPointAttr(nDataCol, nDataRow));
//STRIP001
//STRIP001      SdrObject* pDataPointObj;
//STRIP001      SdrPage* pPage = GetPage(0);
//STRIP001      DBG_ASSERT(pPage, "ChartModel::ChangeDataPointAttr:Keine Seite vorhanden!");
//STRIP001
//STRIP001      if (pObjId->GetObjId() == CHOBJID_LEGEND_SYMBOL_COL)
//STRIP001      {
//STRIP001 //-/         rObj.SetAttributes(aDataPointAttr, FALSE);
//STRIP001          rObj.SetItemSetAndBroadcast(aDataPointAttr);
//STRIP001          pDataPointObj = CDPAGetDataPointObj(nDataCol,nDataRow);
//STRIP001          if (!pDataPointObj)
//STRIP001              return TRUE;
//STRIP001          pObjId = GetObjectId(*pDataPointObj);
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          if (GetShowLegend())
//STRIP001              ChangeLegendPointAttr(nDataCol,aDataPointAttr);
//STRIP001
//STRIP001          pDataPointObj = &rObj;
//STRIP001      }
//STRIP001
//STRIP001      if( (eDataDescr != CHDESCR_NONE) && bShowDataDescr) //#54870#
//STRIP001         ChangePointDescrSymbolAttr(nDataCol,nDataRow,aDataPointAttr);
//STRIP001
//STRIP001      BOOL bOld=bAttrAutoStorage;
//STRIP001      SetAttrAutoStorage(FALSE);
//STRIP001
//STRIP001 //-/     pDataPointObj->SetAttributes(aDataPointAttr, FALSE);
//STRIP001      pDataPointObj->SetItemSetAndBroadcast(aDataPointAttr);
//STRIP001
//STRIP001      if(bBuildChart)
//STRIP001      {
//STRIP001          if(IsAttrChangeNeedsBuildChart(rAttr))
//STRIP001              BuildChart(FALSE);
//STRIP001          else
//STRIP001              if(Is3DChart())
//STRIP001 //-/                 rObj.SetAttributes(rAttr,FALSE);
//STRIP001                  rObj.SetItemSetAndBroadcast(rAttr);
//STRIP001      }
//STRIP001      SetAttrAutoStorage(bOld);
//STRIP001      return TRUE;
//STRIP001  }
//STRIP001  else return FALSE;
//STRIP001 }

/*************************************************************************
|*
|* Aendere die Attribute einer Achse
|*
\************************************************************************/

/*N*/ void ChartModel::SetAxisAttributes (const SfxItemSet* pAttr,const SdrObjGroup* pAxisObj)
/*N*/ {
/*N*/   if (pAttr && pAxisObj)
/*N*/   {
/*N*/       SfxItemSet aTextAttr(*pItemPool, nTextWhichPairs);
/*N*/
/*N*/       aTextAttr.Put(*pAttr);
/*N*/
/*N*/       SdrObjListIter aIterator(*pAxisObj->GetSubList(), IM_FLAT);
/*N*/       while (aIterator.IsMore())
/*N*/       {
/*N*/           SdrObject   *pObj   = aIterator.Next();
/*N*/           SchObjectId *pObjId = GetObjectId(*pObj);
/*N*/
/*N*/           if (pObjId)
/*N*/               switch (pObjId->GetObjId())
/*N*/               {
/*N*/                   case CHOBJID_LINE :
/*N*/ //-/                      pObj->SetAttributes(*pAttr, FALSE);
/*N*/                       pObj->SetItemSetAndBroadcast(*pAttr);
/*N*/                       break;
/*N*/
/*N*/                   case CHOBJID_TEXT :
/*?*/                       SetTextAttr(*(SdrTextObj*)pObj, aTextAttr);
/*N*/
/*N*/                   default :
/*N*/                       ;
/*N*/               }
/*N*/       }
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|* Aendere die Attribute einer Achse
|*
\************************************************************************/

//STRIP001 BOOL ChartModel::SetAllAxisAttributes ()
//STRIP001 {
//STRIP001  SdrPage *pPage=GetPage(0);
//STRIP001  if (!pPage) return FALSE;
//STRIP001  else
//STRIP001  {
//STRIP001      if (pChartXAxis->IsVisible())
//STRIP001          SetAxisAttributes(&GetAttr(CHOBJID_DIAGRAM_X_AXIS),
//STRIP001           (SdrObjGroup*)GetObjWithId(CHOBJID_DIAGRAM_X_AXIS,*pPage,0,IM_DEEPWITHGROUPS));
//STRIP001
//STRIP001      if (CanAxis(CHART_AXIS_SECONDARY_X) && pChartAAxis->IsVisible() )
//STRIP001          SetAxisAttributes(&GetAttr(CHOBJID_DIAGRAM_A_AXIS),
//STRIP001           (SdrObjGroup*)GetObjWithId(CHOBJID_DIAGRAM_A_AXIS,*pPage,0,IM_DEEPWITHGROUPS));
//STRIP001
//STRIP001      if (CanAxis(CHART_AXIS_SECONDARY_Y) && pChartBAxis->IsVisible() )
//STRIP001          SetAxisAttributes(&GetAttr(CHOBJID_DIAGRAM_B_AXIS),
//STRIP001           (SdrObjGroup*)GetObjWithId(CHOBJID_DIAGRAM_B_AXIS,*pPage,0,IM_DEEPWITHGROUPS));
//STRIP001
//STRIP001      if (pChartYAxis->IsVisible())
//STRIP001          SetAxisAttributes(&GetAttr(CHOBJID_DIAGRAM_Y_AXIS),
//STRIP001           (SdrObjGroup*)GetObjWithId(CHOBJID_DIAGRAM_Y_AXIS,*pPage,0,IM_DEEPWITHGROUPS));
//STRIP001
//STRIP001      if (Is3DChart () && pChartZAxis->IsVisible())
//STRIP001          SetAxisAttributes(&GetAttr(CHOBJID_DIAGRAM_Z_AXIS),
//STRIP001           (SdrObjGroup*)GetObjWithId(CHOBJID_DIAGRAM_Z_AXIS,*pPage,0,IM_DEEPWITHGROUPS));
//STRIP001
//STRIP001      BuildChart(FALSE);
//STRIP001      return TRUE;
//STRIP001    }
//STRIP001 }

/*N*/ void ChartModel::SetTextFromObject( SdrTextObj* pObj,OutlinerParaObject* pTextObject )
/*N*/ {
/*N*/   DBG_ASSERT( pObj, "ChartModel::SetTextFromObject: Object is NULL" );
/*N*/   if( !bAttrAutoStorage && pTextObject // not during BuildChart
/*N*/       || !pObj )
/*N*/       return;
/*N*/
/*N*/   CHART_TRACE( "ChartModel::SetTextFromObject" );
/*N*/
/*N*/   SchObjectId* pObjId = GetObjectId( *pObj );
/*N*/
/*N*/   SfxItemSet *pItemSet = NULL;
/*N*/   String* pStrToChange = NULL;
/*N*/
/*N*/   if( pTextObject )
/*N*/   {
/*N*/       if( pObjId )
/*N*/       {
/*N*/           pOutliner->SetText( *pTextObject );
/*N*/           String aTitle = pOutliner->GetText( pOutliner->GetParagraph( 0 ), pOutliner->GetParagraphCount() );
/*N*/           pOutliner->Clear();
/*N*/
/*N*/           long nId = pObjId->GetObjId();
/*N*/           switch( nId )
/*N*/           {
/*N*/               case CHOBJID_DIAGRAM_TITLE_X_AXIS:
/*N*/                   pItemSet = pXAxisTitleAttr;
/*N*/                   pStrToChange = &aXAxisTitle;
/*N*/                   break;
/*N*/               case CHOBJID_DIAGRAM_TITLE_Y_AXIS:
/*N*/                   pItemSet = pYAxisTitleAttr;
/*N*/                   pStrToChange = &aYAxisTitle;
/*N*/                   break;
/*N*/               case CHOBJID_DIAGRAM_TITLE_Z_AXIS:
/*N*/                   pItemSet = pZAxisTitleAttr;
/*N*/                   pStrToChange = &aZAxisTitle;
/*N*/                   break;
/*N*/               case CHOBJID_TITLE_MAIN:
/*N*/                   pItemSet = pMainTitleAttr;
/*N*/                   pStrToChange = &aMainTitle;
/*N*/                   break;
/*N*/               case CHOBJID_TITLE_SUB:
/*N*/                   pItemSet = pSubTitleAttr;
/*N*/                   pStrToChange = &aSubTitle;
/*N*/                   break;
/*N*/           }
/*N*/
/*N*/           // if stacked is set the string contains linefeeds which have to be removed
/*N*/           const SfxPoolItem* pPoolItem = NULL;
/*N*/           if( pItemSet &&
/*N*/               pItemSet->GetItemState( SCHATTR_TEXT_ORIENT, FALSE, &pPoolItem ) == SFX_ITEM_SET &&
/*N*/               SAL_STATIC_CAST( const SvxChartTextOrientItem*, pPoolItem )->GetValue() == CHTXTORIENT_STACKED )
/*N*/           {
/*?*/               DBG_BF_ASSERT(0, "STRIP"); //STRIP001 aTitle = UnstackString( aTitle );
/*N*/           }
/*N*/
/*N*/           if( pStrToChange )
/*N*/               *(pStrToChange) = aTitle;
/*N*/       }
/*N*/   }
/*N*/ }
/*N*/
/*N*/ //Achtung! diese Funktion sollte nur für 3-D-Objekte ausgeführt werden,
/*N*/ //bei z.B. Legendensymbolen führt der Aufruf zu einer Endlos-Schleife !!!!!!!!!!!!!
/*N*/ //Im BuildChart wird ueber bAttrAutoStorage=FALSE doppelte Ausfuehrung unterbunden
/*N*/ void ChartModel::StoreObjectsAttributes(SdrObject* pObj,const SfxItemSet& rAttr, FASTBOOL bReplaceAll)
/*N*/ {//#52277#
/*N*/   if(!bAttrAutoStorage)
/*N*/       return;
/*N*/   bAttrAutoStorage=FALSE; //Rekursionen verhindern
/*N*/
/*N*/   //Eventuell 3D-Materialfarbe in 2D-Füllfarbe konvertieren:
/*  const SfxPoolItem *pPoolItem;
    if( SFX_ITEM_SET == rAttr.GetItemState( SID_ATTR_3D_MAT_COLOR, TRUE, &pPoolItem ) )
    {
        Color aNew = ( ( const SvxColorItem* ) pPoolItem )->GetValue();
        ((SfxItemSet&)rAttr).Put(XFillColorItem(String(),aNew));
    }
*/
/*N*/   DBG_ITEMS(((SfxItemSet&)rAttr),this);
/*N*/
/*N*/   SchObjectId* pObjId = GetObjectId(*pObj);
/*N*/   if(!pObjId)
/*N*/   {
/*?*/       DBG_ERROR("ChartModel::StoreObjectsAttributes failed, no ObjId");
/*N*/   }
/*N*/   long nId=pObjId->GetObjId();
/*N*/
/*N*/   CHART_TRACE2( "ChartModel::StoreObjectsAttributes Id=%s %s", GetCHOBJIDName( nId ), bReplaceAll? "ReplaceAll" : "Merge" );
/*N*/
/*N*/   switch(nId)
/*N*/   {
/*N*/
/*N*/   case CHOBJID_DIAGRAM_SPECIAL_GROUP:
/*N*/   case CHOBJID_DIAGRAM_ROWGROUP:
/*N*/   case CHOBJID_LEGEND_SYMBOL_ROW:
/*N*/       {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/             SchDataRow* pDataRow =  GetDataRow(*pObj);
//STRIP001 /*?*/             if(pDataRow)
//STRIP001 /*?*/             {
//STRIP001 /*?*/                  long nDataRow=pDataRow->GetRow();
//STRIP001 /*?*/
//STRIP001 /*?*/                  PutDataRowAttr(nDataRow, rAttr,!bReplaceAll);
//STRIP001 /*?*/
//STRIP001 /*?*/                  if (GetShowLegend())
//STRIP001 /*?*/                        ChangeLegendRowAttr(nDataRow,rAttr);
//STRIP001 /*?*/
//STRIP001 /*?*/                  if( (eDataDescr != CHDESCR_NONE) && bShowDataDescr)
//STRIP001 /*?*/                          ChangeRowDescrSymbolAttr(nDataRow,rAttr);
//STRIP001 /*?*/             }
/*N*/       }
/*?*/       break;
/*?*/
/*?*/   case CHOBJID_DIAGRAM_DATA:
/*?*/   case CHOBJID_LEGEND_SYMBOL_COL:
/*?*/       {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/            SchDataPoint* pDataPoint = GetDataPoint(*pObj);
//STRIP001 /*?*/            if(pDataPoint)
//STRIP001 /*?*/            {
//STRIP001 /*?*/                PutDataPointAttr(pDataPoint->GetCol(), pDataPoint->GetRow(), rAttr,!bReplaceAll);
//STRIP001 /*?*/
//STRIP001 /*?*/                if (GetShowLegend())
//STRIP001 /*?*/                    ChangeLegendPointAttr(pDataPoint->GetCol(),rAttr);
//STRIP001 /*?*/
//STRIP001 /*?*/                if( (eDataDescr != CHDESCR_NONE) && bShowDataDescr)
//STRIP001 /*?*/                     ChangePointDescrSymbolAttr(pDataPoint->GetCol(),pDataPoint->GetRow(),rAttr);
//STRIP001 /*?*/            }
/*N*/       }
/*?*/       break;
/*?*/
/*?*/   case CHOBJID_DIAGRAM_STATISTICS_GROUP :
/*?*/   case CHOBJID_DIAGRAM_AVERAGEVALUE :
/*?*/   case CHOBJID_DIAGRAM_REGRESSION :
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); }//STRIP001
//STRIP001 /*?*/        if(bReplaceAll)
//STRIP001 /*?*/            GetAttr(pObj).ClearItem();
//STRIP001 /*?*/        GetAttr(pObj).Put(rAttr,TRUE);
/*?*/       break;
/*?*/
/*N*/   case CHOBJID_DIAGRAM_WALL:
/*N*/       {
/*N*/           //Spezialfall, 2.Wand suchen
/*N*/           ChartScene* pScene=GetScene();
/*N*/           if(pScene)
/*N*/           {
/*N*/               SdrObjListIter aIterator(*pScene->GetSubList(), IM_FLAT);
/*N*/               while (aIterator.IsMore())
/*N*/               {
/*N*/                   SdrObject   *pO   = aIterator.Next();
/*N*/                   SchObjectId *pI   = GetObjectId(*pO);
/*N*/                   if(pI && pI->GetObjId()==CHOBJID_DIAGRAM_WALL && pO!=pObj)
/*N*/ //-/                      pO->SetAttributes(rAttr,FALSE);
/*N*/                       pO->SetItemSetAndBroadcast(rAttr);
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/       if(bReplaceAll)
/*?*/           GetAttr(nId).ClearItem();
/*N*/       GetAttr(nId).Put(rAttr,TRUE);
/*N*/       break;
/*N*/   default:
/*N*/       if(bReplaceAll)
/*?*/           GetAttr(nId).ClearItem();
/*N*/       GetAttr(nId).Put(rAttr,TRUE);
/*N*/       break;
/*N*/   }
/*N*/
/*N*/   bAttrAutoStorage=TRUE;
/*N*/ }

/*************************************************************************
|*
|* Aendere die Attribute bestimmter Objekte in der Page und im Model, bzw.
|* lokalisiere bestimmte Objekte anhand der Id.
|* Wird derzeit nur fuer UNO verwendet, koennte aber allgemeiner und sollte vor
|* allem vollständiger werden
|*
|* ACHTUNG: es gibt weitere Methoden gleichen/ähnlichen Namens und anderen Argumenten,
|* die ähnlich wie diese Funktionen arbeiten!
|*
\************************************************************************/

/*N*/ void ChartModel::SetTitle(const long nId, const String& rTitle)
/*N*/ {
/*N*/   switch(nId)
/*N*/   {
/*N*/
/*N*/       case CHOBJID_TITLE_MAIN:
/*N*/           MainTitle()=rTitle;
/*N*/           //  Replace the current text object with a new one with the given text.
/*N*/           {
/*N*/               SdrObject * pGroupObject = GetObjWithId( CHOBJID_TITLE_MAIN, *GetPage(0) );
/*N*/               if (pGroupObject != NULL)
/*N*/               {
/*N*/                   aTitleTopCenter = pGroupObject->GetBoundRect().TopCenter();
/*N*/                   DeleteObject(pGroupObject);
/*N*/               }
/*N*/               SdrTextObj * pObj = CreateTextObj(CHOBJID_TITLE_MAIN, aTitleTopCenter,
/*N*/                   aMainTitle, *pMainTitleAttr, TRUE, CHADJUST_TOP_CENTER);
/*N*/               pObj->SetResizeProtect(TRUE);
/*N*/               GetPage(0)->NbcInsertObject(pObj);
/*N*/           }
/*N*/           break;
/*N*/       case CHOBJID_TITLE_SUB:
/*N*/           SubTitle()=rTitle;
/*N*/           //  Replace the current text object with a new one with the given text.
/*N*/           {
/*N*/
/*N*/               SdrObject * pGroupObject = GetObjWithId( CHOBJID_TITLE_SUB, *GetPage(0) );
/*N*/               if (pGroupObject != NULL)
/*N*/               {
/*N*/                   aSubTitleTopCenter = pGroupObject->GetBoundRect().TopCenter();
/*N*/                   DeleteObject(pGroupObject);
/*N*/               }
/*N*/               SdrTextObj * pObj = CreateTextObj(CHOBJID_TITLE_SUB, aSubTitleTopCenter,
/*N*/                   aSubTitle, *pSubTitleAttr, TRUE, CHADJUST_TOP_CENTER);
/*N*/               pObj->SetResizeProtect(TRUE);
/*N*/               GetPage(0)->NbcInsertObject(pObj);
/*N*/           }
/*N*/           break;
/*N*/       case CHOBJID_DIAGRAM_TITLE_X_AXIS:
/*N*/           XAxisTitle()=rTitle;
/*N*/           break;
/*N*/       case CHOBJID_DIAGRAM_TITLE_Y_AXIS:
/*N*/           YAxisTitle()=rTitle;
/*N*/           break;
/*N*/       case CHOBJID_DIAGRAM_TITLE_Z_AXIS:
/*N*/           ZAxisTitle()=rTitle;
/*N*/           break;
/*N*/       default:
/*?*/           CHART_TRACE2( "SetTitle: Title not found by id %ld (%s) ", nId, GetCHOBJIDName( nId ));
/*N*/           break;
/*N*/   }
/*N*/ }

/*N*/ String ChartModel::GetTitle( const long nId )
/*N*/ {
/*N*/   switch(nId)
/*N*/   {
/*N*/     case CHOBJID_TITLE_MAIN:
/*N*/         return MainTitle();
/*N*/     case CHOBJID_TITLE_SUB:
/*N*/         return SubTitle();
/*N*/     case CHOBJID_DIAGRAM_TITLE_X_AXIS:
/*N*/         return XAxisTitle();
/*N*/     case CHOBJID_DIAGRAM_TITLE_Y_AXIS:
/*N*/         return YAxisTitle();
/*N*/     case CHOBJID_DIAGRAM_TITLE_Z_AXIS:
/*N*/         return ZAxisTitle();
/*N*/     default:
/*?*/         CHART_TRACE2( "GetTitle: Title not found by id %ld (%s) ", nId, GetCHOBJIDName( nId ));
/*?*/         return String();
/*N*/   }
/*N*/ }

/*N*/ void ChartModel::SetHasBeenMoved(const long nId,BOOL bMoved)
/*N*/ {
/*N*/   switch(nId)
/*N*/   {
/*N*/
/*N*/       case CHOBJID_TITLE_MAIN:
/*N*/           SetMainTitleHasBeenMoved(bMoved);
/*N*/           break;
/*N*/       case CHOBJID_TITLE_SUB:
/*N*/           SetSubTitleHasBeenMoved(bMoved);
/*N*/           break;
/*N*/       case CHOBJID_DIAGRAM_TITLE_X_AXIS:
/*N*/           SetXAxisTitleHasBeenMoved(bMoved);
/*N*/           break;
/*N*/       case CHOBJID_DIAGRAM_TITLE_Y_AXIS:
/*N*/           SetYAxisTitleHasBeenMoved(bMoved);
/*N*/           break;
/*N*/       case CHOBJID_DIAGRAM_TITLE_Z_AXIS:
/*N*/           SetZAxisTitleHasBeenMoved(bMoved);
/*N*/           break;
/*N*/       case CHOBJID_LEGEND:
/*N*/           SetLegendHasBeenMoved(bMoved);
/*N*/           break;
/*N*/       default:
/*?*/           CHART_TRACE2( "SetHasBeenMoved: Object not found by id %ld (%s) ", nId, GetCHOBJIDName( nId ));
/*N*/           break;
/*N*/   }
/*N*/ }

/*N*/ SdrObject* ChartModel::GetObjectWithId(const long nId,const long nCol,const long nRow)
/*N*/ {
/*N*/   //ToDo: Das hier könnte man auch schöner machen (kein DEEP!)
/*N*/   SdrObject* pObj=(GetObjWithId ((USHORT)nId,*GetPage(0),0,IM_DEEPWITHGROUPS));
/*N*/ #ifdef DBG_UTIL
/*N*/   // there is no DBG_ASSERT2
/*N*/   if( !pObj )
/*N*/       DBG_ERROR2( "GetObjWithId: Object not found (id=%ld => %s)", nId, GetCHOBJIDName( nId ) );
/*N*/ #endif
/*N*/   return pObj;
/*N*/ }

// GetAttr-Methoden:
//GetAttr(id) Diese Methode sucht anhand der Id den passenden Model-eigenen AttrSet
//Achtung! Wenn zu einer ID kein Set existiert, wird *pDummyAttr returned!
//(ungefährlich, geringer Overhead, wirft daher nur DBG__TRACE)
//Nicht-Singuläre Objekte können nicht an der ID alleine identifiziert werden,
//in diesem Fall muss GetAttr(SdrObject*) statt GetAttr(long id) gerufen werden
// GetAttr(long id, SfxItemSet&) besorgt alle für ein Objekt verfügbaren und
// gültigen Attribute
//STRIP001 SfxItemSet& ChartModel::GetAttr(const SdrObject *pObj)
//STRIP001 {
//STRIP001  CHART_TRACE( "ChartModel::GetAttr" );
//STRIP001  SchObjectId* pObjId = GetObjectId(*pObj);
//STRIP001  long nId=pObjId->GetObjId();
//STRIP001
//STRIP001  switch(nId)
//STRIP001  {
//STRIP001  case CHOBJID_DIAGRAM_SPECIAL_GROUP:
//STRIP001  case CHOBJID_DIAGRAM_ROWGROUP:
//STRIP001  case CHOBJID_LEGEND_SYMBOL_ROW:
//STRIP001      {
//STRIP001           SchDataRow* pDataRow =  GetDataRow(*pObj);
//STRIP001           if(pDataRow)
//STRIP001           {
//STRIP001               return (SfxItemSet&)GetDataRowAttr(pDataRow->GetRow());
//STRIP001           }
//STRIP001      }
//STRIP001      break;
//STRIP001
//STRIP001  case CHOBJID_DIAGRAM_DATA :
//STRIP001  case CHOBJID_LEGEND_SYMBOL_COL:
//STRIP001      {
//STRIP001          SchDataPoint* pDataPoint = GetDataPoint(*pObj);
//STRIP001          if(pDataPoint)
//STRIP001          {
//STRIP001              return (SfxItemSet&)GetDataPointAttr(pDataPoint->GetCol(),pDataPoint->GetRow());
//STRIP001          }
//STRIP001      }
//STRIP001      break;
//STRIP001  case SID_DIAGRAM_ERROR :
//STRIP001      {
//STRIP001           SchDataRow* pDataRow =  GetDataRow(*pObj);
//STRIP001           if(pDataRow)
//STRIP001           {
//STRIP001               return (SfxItemSet&)GetErrorAttr(pDataRow->GetRow());
//STRIP001           }
//STRIP001      }
//STRIP001      break;
//STRIP001
//STRIP001  case SID_DIAGRAM_AVERAGEVALUE :
//STRIP001      {
//STRIP001           SchDataRow* pDataRow =  GetDataRow(*pObj);
//STRIP001           if(pDataRow)
//STRIP001           {
//STRIP001               return (SfxItemSet&)GetAverageAttr(pDataRow->GetRow());
//STRIP001           }
//STRIP001      }
//STRIP001      break;
//STRIP001
//STRIP001  case SID_DIAGRAM_REGRESSION :
//STRIP001      {
//STRIP001           SchDataRow* pDataRow =  GetDataRow(*pObj);
//STRIP001           if(pDataRow)
//STRIP001           {
//STRIP001               return (SfxItemSet&)GetRegressAttr(pDataRow->GetRow());
//STRIP001           }
//STRIP001      }
//STRIP001      break;
//STRIP001
//STRIP001  default:
//STRIP001      return  GetAttr(nId);
//STRIP001      break;
//STRIP001  }
//STRIP001  CHART_TRACE1( "GetAttr illegal Object Id (%ld), returning dummy", nId );
//STRIP001  return *pDummyAttr;
//STRIP001 }

/*
Fehlen evtl. noch in GetAttr(ID):

#define        CHOBJID_DIAGRAM                   13
#define        CHOBJID_DIAGRAM_X_GRID_MAIN       22
#define        CHOBJID_DIAGRAM_Y_GRID_MAIN       23
#define        CHOBJID_DIAGRAM_Z_GRID_MAIN       24
#define        CHOBJID_DIAGRAM_X_GRID_HELP       25
#define        CHOBJID_DIAGRAM_Y_GRID_HELP       26
#define        CHOBJID_DIAGRAM_Z_GRID_HELP       27
#define        CHOBJID_DIAGRAM_ROWS              29
#define        CHOBJID_DIAGRAM_ROWSLINE          30
#define        CHOBJID_DIAGRAM_DESCRGROUP        32
#define        CHOBJID_DIAGRAM_DESCR_ROW         33
#define        CHOBJID_DIAGRAM_DESCR_COL         38
#define        CHOBJID_DIAGRAM_DESCR_SYMBOL      39
#define        CHOBJID_DIAGRAM_NET               41
#define        CHOBJID_DIAGRAM_STACKEDGROUP      46
#define        CHOBJID_DIAGRAM_STATISTICS_GROUP  48


  nur GetAttr(pObj):
#define        CHOBJID_DIAGRAM_AVERAGEVALUE      42
#define        CHOBJID_DIAGRAM_REGRESSION        45
#define        CHOBJID_DIAGRAM_ERROR             43

#define        CHOBJID_LEGEND_SYMBOL_ROW         36
#define        CHOBJID_LEGEND_SYMBOL_COL         37
#define        CHOBJID_DIAGRAM_DATA              31
#define        CHOBJID_DIAGRAM_SPECIAL_GROUP     55
#define        CHOBJID_DIAGRAM_ROWGROUP          28

  */

/*N*/ void ChartModel::SetAttributes(const long nId,const SfxItemSet& rAttr,BOOL bMerge)
/*N*/ {
/*N*/   CHART_TRACE( "ChartModel::SetAttributes" );
/*N*/   SfxItemSet& rItemSet=GetAttr(nId);
/*N*/
/*N*/   if(!bMerge)
/*N*/       rItemSet.ClearItem();


    //sobald die member bShow*Descr endlich entfallen, kann das hier alles weg
/*  if(nId==CHOBJID_DIAGRAM_X_AXIS || nId==CHOBJID_DIAGRAM_Y_AXIS || nId==CHOBJID_DIAGRAM_Z_AXIS)
    {
        const SfxPoolItem *pPoolItem=NULL;
        if( rAttr.GetItemState( SCHATTR_AXIS_SHOWDESCR, FALSE, &pPoolItem ) == SFX_ITEM_SET )
        {
            BOOL bShow = ( (const SfxBoolItem*) pPoolItem)->GetValue();
            switch(nId)
            {
                case CHOBJID_DIAGRAM_X_AXIS:
                    bShowXDescr=bShow;
                    break;
                case CHOBJID_DIAGRAM_Y_AXIS:
                    bShowYDescr=bShow;
                    break;
                case CHOBJID_DIAGRAM_Z_AXIS:
                    bShowZDescr=bShow;
                    break;
            }
        }
    }*/


/*N*/   rItemSet.Put(rAttr);
/*N*/ }
/*N*/ SfxItemSet& ChartModel::GetAttr(const long nObjId,const long nIndex1/*=-1*/) const
/*N*/ {
/*N*/   CHART_TRACE( "ChartModel::GetAttr(const long nObjId)" );
/*N*/
/*N*/   switch(nObjId)
/*N*/   {
/*N*/       case CHOBJID_DIAGRAM_STOCKLINE_GROUP:
/*?*/           return *pStockLineAttr;
/*N*/
/*N*/       case CHOBJID_DIAGRAM_STOCKPLUS_GROUP:
/*N*/           return *pStockPlusAttr;
/*N*/
/*N*/       case CHOBJID_DIAGRAM_STOCKLOSS_GROUP:
/*N*/           return *pStockLossAttr;
/*N*/
/*N*/       case CHOBJID_DIAGRAM_X_GRID_MAIN_GROUP:
/*N*/           return *pXGridMainAttr;
/*N*/
/*N*/       case CHOBJID_DIAGRAM_Y_GRID_MAIN_GROUP:
/*N*/           return *pYGridMainAttr;
/*N*/
/*N*/       case CHOBJID_DIAGRAM_Z_GRID_MAIN_GROUP:
/*N*/           return *pZGridMainAttr;
/*N*/
/*N*/       case CHOBJID_DIAGRAM_X_GRID_HELP_GROUP:
/*?*/           return *pXGridHelpAttr;
/*N*/
/*N*/       case CHOBJID_DIAGRAM_Y_GRID_HELP_GROUP:
/*?*/           return *pYGridHelpAttr;
/*N*/
/*N*/       case CHOBJID_DIAGRAM_Z_GRID_HELP_GROUP:
/*?*/           return *pZGridHelpAttr;
/*N*/
/*N*/       case CHOBJID_DIAGRAM_AREA:
/*N*/           return *pDiagramAreaAttr;
/*N*/
/*N*/       case CHOBJID_DIAGRAM:          //Leider mmehrfache bedeutung, im 2D ist das wohl das selbe
/*N*/       case CHOBJID_DIAGRAM_WALL:
/*N*/           return *pDiagramWallAttr;
/*N*/
/*N*/       case CHOBJID_DIAGRAM_FLOOR:
/*N*/           return *pDiagramFloorAttr;
/*N*/
/*N*/       case CHOBJID_DIAGRAM_TITLE_X_AXIS:
/*N*/           return *pXAxisTitleAttr;
/*N*/       case CHOBJID_DIAGRAM_TITLE_Y_AXIS:
/*N*/           return *pYAxisTitleAttr;
/*N*/       case CHOBJID_DIAGRAM_TITLE_Z_AXIS:
/*N*/           return *pZAxisTitleAttr;
/*N*/
/*N*/       case CHOBJID_TITLE_MAIN:
/*N*/           return *pMainTitleAttr;
/*N*/       case CHOBJID_TITLE_SUB:
/*N*/           return *pSubTitleAttr;
/*N*/
/*N*/       case CHOBJID_DIAGRAM_X_AXIS:
/*N*/           return *pChartXAxis->GetItemSet();
/*N*/       case CHOBJID_DIAGRAM_Y_AXIS:
/*N*/           return *pChartYAxis->GetItemSet();
/*N*/       case CHOBJID_DIAGRAM_Z_AXIS:
/*N*/           return *pChartZAxis->GetItemSet();
/*N*/       case CHOBJID_DIAGRAM_B_AXIS:
/*N*/           return *pChartBAxis->GetItemSet();
/*N*/       case CHOBJID_DIAGRAM_A_AXIS:
/*N*/           return *pChartAAxis->GetItemSet();
/*N*/
/*N*/       case CHOBJID_LEGEND_BACK: //Achtung, dies ist nur das Drawing-Objekt, normalerweise erhält man die andere ID für das Gruppenobjekt
/*N*/       case CHOBJID_LEGEND:
/*N*/           return *pLegendAttr;
/*N*/
            /*return *pTitleAttr;
            return *pAxisAttr;
            return *pGridAttr;
             return *pChartAttr;*/
/*N*/
/*N*/       case CHOBJID_DIAGRAM_REGRESSION:
/*?*/           return *aRegressAttrList.GetObject(nIndex1);
/*N*/       case CHOBJID_DIAGRAM_ERROR:
/*?*/           return *aErrorAttrList.GetObject(nIndex1);
/*N*/       case CHOBJID_DIAGRAM_AVERAGEVALUE:
/*?*/           return *aAverageAttrList.GetObject(nIndex1);
/*N*/
/*N*/       default:
/*N*/           CHART_TRACE1( "GetAttr illegal Object Id (%ld), returning dummy", nObjId );
/*N*/           return *pDummyAttr;
/*N*/   }
/*N*/ }


//  This method fills rAttr with the items stored at the object specified
//  by nObjId.  Effectively calls GetAttr(long,long) but handles diagram
//  axes as special case.
//  The item set of the graphical object representation is not merged in
//  anymore.
/*N*/ void ChartModel::GetAttr( const long nObjId, SfxItemSet& rAttr, const long nIndex1 /*=-1*/ )
/*N*/ {
/*N*/   CHART_TRACE( "ChartModel::GetAttr( long nObjId, SfxItemSet& rAttr)" );
/*N*/
/*N*/ #if 0
/*N*/   SdrObject* pObj=NULL;
/*N*/
/*N*/   //Objektattribute aus der Seite holen
/*N*/   //aber keine indizierten Objekte auf diese Weise suchen !
/*N*/   if(nIndex1==-1)
/*N*/   {
/*N*/       pObj=(GetObjWithId ((USHORT)nObjId,*GetPage(0),0,IM_DEEPWITHGROUPS));
/*N*/       if(pObj)
/*N*/           rAttr.Put(pObj->GetItemSet());
/*N*/   }
/*N*/ #endif
/*N*/
/*N*/   // items at model (and axis object)
/*N*/   switch( nObjId )
/*N*/   {
/*N*/       case CHOBJID_DIAGRAM_X_AXIS:
/*N*/       case CHOBJID_DIAGRAM_Y_AXIS:
/*N*/       case CHOBJID_DIAGRAM_A_AXIS:
/*N*/       case CHOBJID_DIAGRAM_B_AXIS:
/*N*/       case CHOBJID_DIAGRAM_Z_AXIS:
/*N*/           {
/*N*/               // general item set
/*N*/               rAttr.Put( *pAxisAttr );
/*N*/
/*N*/               // specialized item set and members
/*N*/               ChartAxis* pAxis = GetAxis( nObjId );
/*N*/               if( pAxis )
/*N*/               {
/*N*/                   rAttr.Put( *(pAxis->GetItemSet()));
/*N*/                   pAxis->GetMembersAsAttr( rAttr );
/*N*/               }
/*N*/               // ChartModel members for axes
/*N*/               GetTextRotation( rAttr );
/*N*/               switch( nObjId )
/*N*/               {
/*N*/                   case CHOBJID_DIAGRAM_X_AXIS:
/*N*/                   case CHOBJID_DIAGRAM_A_AXIS:
/*N*/                       rAttr.Put( SfxBoolItem( SID_TEXTBREAK, GetFormatXAxisTextInMultipleLinesIfNecessary() ) );
/*N*/                       break;
/*N*/                   case CHOBJID_DIAGRAM_Y_AXIS:
/*N*/                   case CHOBJID_DIAGRAM_B_AXIS:
/*N*/                       rAttr.Put( SfxBoolItem( SID_TEXTBREAK, GetFormatYAxisTextInMultipleLinesIfNecessary() ) );
/*N*/                       break;
/*N*/                   case CHOBJID_DIAGRAM_Z_AXIS:
/*N*/                       rAttr.Put( SfxBoolItem( SID_TEXTBREAK, GetFormatZAxisTextInMultipleLinesIfNecessary() ) );
/*N*/                       break;
/*N*/               }
/*N*/           }
/*N*/           break;
/*N*/
/*N*/       default:
/*N*/           rAttr.Put( GetAttr( nObjId, nIndex1 ));
/*N*/           break;
/*N*/   }
/*N*/ }

/*N*/ BOOL ChartModel::ChangeAttr(const SfxItemSet& rAttr,const long nId,const long nIndex1/*=-1*/)
/*N*/ {
/*N*/   BOOL bNeedChanges=TRUE; //noch ungenutzt, zur evtl. Optimierung
/*N*/
/*N*/
/*N*/   //ToDo: optimieren! klappt wegen XChartView so nicht:
/*N*/   //BOOL bForceBuild=FALSE;
/*N*/   BOOL bForceBuild=TRUE;
/*N*/
/*N*/
/*N*/   SdrObject* pObj=NULL;
/*N*/   //Objektattribute am Objekt setzen, falls nicht indiziert
/*N*/   if(nIndex1==-1)
/*N*/   {
/*N*/       pObj=(GetObjWithId ((USHORT)nId,*GetPage(0),0,IM_DEEPWITHGROUPS));
/*N*/      if(pObj)
/*N*/ //-/          pObj->SetAttributes(rAttr,FALSE);
/*N*/           pObj->SetItemSetAndBroadcast(rAttr);
/*N*/   }
/*N*/
/*N*/
/*N*/   //und auch am Model
/*N*/   switch(nId)
/*N*/   {
/*N*/       case CHOBJID_DIAGRAM_X_AXIS:
/*N*/       case CHOBJID_DIAGRAM_Y_AXIS:
/*N*/       case CHOBJID_DIAGRAM_A_AXIS:
/*N*/       case CHOBJID_DIAGRAM_B_AXIS:
/*N*/       case CHOBJID_DIAGRAM_Z_AXIS:
/*N*/           {
/*N*/               const SfxPoolItem *pPoolItem;
/*N*/               if(pObj)
/*N*/               {
/*N*/                   ChangeAxisAttr(rAttr,(SdrObjGroup*)pObj);
/*N*/               }
/*N*/               else
/*N*/               {
/*N*/                   const SfxPoolItem* pPoolItem=NULL;
/*N*/                   if(rAttr.GetItemState(SID_ATTR_NUMBERFORMAT_VALUE,TRUE,&pPoolItem)==SFX_ITEM_SET)
/*N*/                   {
/*N*/                       SfxItemSet aSet(rAttr);
/*N*/                       UINT32 nTmp=((const SfxUInt32Item*)pPoolItem)->GetValue();
/*N*/                       aSet.Put(SfxUInt32Item(IsPercentChart()
/*N*/                           ? SCHATTR_AXIS_NUMFMTPERCENT : SCHATTR_AXIS_NUMFMT , nTmp));
/*N*/                       SetAttributes(nId,aSet); //im Model
/*N*/                   }
/*N*/                   else
/*N*/                   {
/*N*/                       SetAttributes(nId,rAttr); //im Model
/*N*/                   }
/*N*/
/*N*/               }
/*N*/
/*N*/               if( SFX_ITEM_SET == rAttr.GetItemState( SID_TEXTBREAK, TRUE, &pPoolItem ) )
/*N*/               {
/*N*/                   switch(nId)
/*N*/                   {
/*N*/                       case CHOBJID_DIAGRAM_X_AXIS:
/*N*/                       case CHOBJID_DIAGRAM_A_AXIS:
/*N*/                           SetFormatXAxisTextInMultipleLinesIfNecessary(((const SfxBoolItem*)pPoolItem)->GetValue());
/*N*/                           break;
/*N*/                       case CHOBJID_DIAGRAM_Y_AXIS:
/*N*/                       case CHOBJID_DIAGRAM_B_AXIS:
/*N*/                           SetFormatYAxisTextInMultipleLinesIfNecessary(((const SfxBoolItem*)pPoolItem)->GetValue());
/*N*/                           break;
/*N*/                       case CHOBJID_DIAGRAM_Z_AXIS:
/*N*/                           SetFormatZAxisTextInMultipleLinesIfNecessary(((const SfxBoolItem*)pPoolItem)->GetValue());
/*N*/                           break;
/*N*/                   }
/*N*/               }
/*N*/           }
/*N*/           break;
/*N*/         case CHOBJID_AREA:
/*?*/             DBG_BF_ASSERT(0, "STRIP"); //STRIP001 ChangeDiagramAreaAttr( rAttr );
/*?*/             break;
/*N*/       default:
/*N*/           GetAttr(nId,nIndex1).Put(rAttr,TRUE);
/*N*/           break;
/*N*/   }
/*N*/
/*N*/     // calculate result here because BuildChart will delete pObj (dangling pointer)
/*N*/     BOOL bResult = ( pObj != NULL || nIndex1 != -1 );
/*N*/
/*N*/   if(bForceBuild || nIndex1!=-1)
/*N*/       BuildChart(FALSE);
/*N*/   else if(bNeedChanges && IsAttrChangeNeedsBuildChart(rAttr))
/*?*/       BuildChart(FALSE);
/*N*/
/*N*/   return bResult;
/*N*/ }
/* Anmerkungen zu GetObjectAttr,SetObjectAttr:

-  das koennte bei get(????) fehlen:
        CompareSets (*pYGridMainAttr, *pGridAttr);
        CompareSets (*pZGridMainAttr, *pGridAttr);
        CompareSets (*pXGridHelpAttr, *pGridAttr);
        CompareSets (*pYGridHelpAttr, *pGridAttr);
        CompareSets (*pZGridHelpAttr, *pGridAttr);

-  evtl. sollten default-itemwerte erkannt und wieder entfert werden (SET)

- erweitern auf DataRowPoint!

- Das koennte man mal alles oben hineintun....

#define        CHOBJID_TEXT                       1
#define        CHOBJID_AREA                       2
#define        CHOBJID_LINE                       3



#define        CHOBJID_TITLE_MAIN                11
#define        CHOBJID_TITLE_SUB                 12
#define        CHOBJID_DIAGRAM                   13

#define        CHOBJID_DIAGRAM_TITLE_X_AXIS      16
#define        CHOBJID_DIAGRAM_TITLE_Y_AXIS      17
#define        CHOBJID_DIAGRAM_TITLE_Z_AXIS      18


#define        CHOBJID_DIAGRAM_ROWGROUP          28
#define        CHOBJID_DIAGRAM_ROWS              29
#define        CHOBJID_DIAGRAM_ROWSLINE          30
#define        CHOBJID_DIAGRAM_DATA              31
#define        CHOBJID_DIAGRAM_DESCRGROUP        32
#define        CHOBJID_DIAGRAM_DESCR_ROW         33
#define        CHOBJID_DIAGRAM_DESCR_COL         38
#define        CHOBJID_DIAGRAM_DESCR_SYMBOL      39
#define        CHOBJID_LEGEND                    34
#define        CHOBJID_LEGEND_BACK               35
#define        CHOBJID_LEGEND_SYMBOL_ROW         36
#define        CHOBJID_LEGEND_SYMBOL_COL         37
#define        CHOBJID_DIAGRAM_NET               41
#define        CHOBJID_DIAGRAM_AVERAGEVALUE      42
#define        CHOBJID_DIAGRAM_ERROR             43
#define        CHOBJID_DIAGRAM_REGRESSION        45
#define        CHOBJID_DIAGRAM_STACKEDGROUP      46
#define        CHOBJID_DIAGRAM_STATISTICS_GROUP  48
#define        CHOBJID_DIAGRAM_X_GRID_MAIN_GROUP 49
#define        CHOBJID_DIAGRAM_Y_GRID_MAIN_GROUP 50
#define        CHOBJID_DIAGRAM_Z_GRID_MAIN_GROUP 51
#define        CHOBJID_DIAGRAM_X_GRID_HELP_GROUP 52
#define        CHOBJID_DIAGRAM_Y_GRID_HELP_GROUP 53
#define        CHOBJID_DIAGRAM_Z_GRID_HELP_GROUP 54
#define        CHOBJID_DIAGRAM_SPECIAL_GROUP     55

pYGridMainAttr->Put(rAttr);
*/

//STRIP001 BOOL ChartModel::MoveRow(long nRow,BOOL bUp)
//STRIP001 {
//STRIP001  BOOL bOK;
//STRIP001
//STRIP001  if(bUp)
//STRIP001      nRow--;
//STRIP001  if(!bSwitchData)
//STRIP001      bOK=pChartData->SwapRowTranslation(nRow,nRow+1);
//STRIP001  else
//STRIP001      bOK=pChartData->SwapColTranslation(nRow,nRow+1);
//STRIP001
//STRIP001  if(bOK)
//STRIP001  {
//STRIP001      SetAttrAutoStorage(FALSE);//sonst gehen Datenpunktattr verloren
//STRIP001      SwapRowAttr(nRow,nRow+1);
//STRIP001  }
//STRIP001
//STRIP001  return bOK;
//STRIP001 }
//STRIP001 void ChartModel::SwapRowAttr(long nRow1,long nRow2)
//STRIP001 {
//STRIP001  SfxItemSet aSet(*pItemPool,nRowWhichPairs);
//STRIP001  long nCol,nColCnt=GetColCount();
//STRIP001
//STRIP001  for(nCol=0;nCol<nColCnt;nCol++)
//STRIP001  {
//STRIP001      aSet.Put(GetDataPointAttr(nCol,nRow2));
//STRIP001      PutDataPointAttr(nCol,nRow2,GetDataPointAttr(nCol,nRow1),FALSE);
//STRIP001      PutDataPointAttr(nCol,nRow1,aSet,FALSE);
//STRIP001      aSet.ClearItem();
//STRIP001  }
//STRIP001  aSet.Put(GetDataRowAttr(nRow2));
//STRIP001  PutDataRowAttr(nRow2,GetDataRowAttr(nRow1),FALSE,FALSE);
//STRIP001  PutDataRowAttr(nRow1,aSet,FALSE,FALSE);
//STRIP001 }



/*N*/ UINT32 ChartModel::GetNumFmt(long nObjId,BOOL bPercent)
/*N*/ {
/*N*/   return ((const SfxUInt32Item&)GetAttr(nObjId).Get(bPercent
/*N*/           ? SCHATTR_AXIS_NUMFMTPERCENT:SCHATTR_AXIS_NUMFMT)).GetValue();
/*N*/ }
/*N*/ void ChartModel::SetNumFmt(long nObjId,UINT32 nFmt,BOOL bPercent)
/*N*/ {
/*N*/   SfxItemSet aSet(*pItemPool,SCHATTR_AXIS_NUMFMT,SCHATTR_AXIS_NUMFMTPERCENT);
/*N*/   aSet.Put(SfxUInt32Item(bPercent? SCHATTR_AXIS_NUMFMTPERCENT:SCHATTR_AXIS_NUMFMT,nFmt));
/*N*/   SetAttributes(nObjId,aSet);
/*N*/ }


// Prerequisite: rOutAttributes is empty but can hold all interesting attributes
// Result:       All Items that are contained in all data row item sets are set
//               (using the Intersect method of the SfxItemSet)
/*N*/ void ChartModel::GetDataRowAttrAll( SfxItemSet& rOutAttributes )
/*N*/ {
/*N*/     long nListSize = aDataRowAttrList.Count();
/*N*/
/*N*/     // no itemsets => result stays empty
/*N*/     if( nListSize == 0 )
/*N*/         return;
/*N*/
/*N*/     // set items of first data row and then intersect with all remaining
/*N*/     rOutAttributes.Put( *aDataRowAttrList.GetObject( 0 ));
/*N*/   for( long nRow = 1; nRow < nListSize; nRow++ )
/*N*/         rOutAttributes.Intersect( *aDataRowAttrList.GetObject( nRow ));
/*N*/ }

/*N*/ void ChartModel::SetItemWithNameCreation( SfxItemSet& rDestItemSet, const SfxPoolItem* pNewItem )
/*N*/ {
/*N*/     if( pNewItem == NULL )
/*N*/         return;
/*N*/
/*N*/     const SfxPoolItem* pItemToSet = pNewItem;
/*N*/
/*N*/     // this code comes from bf_svx/source/svdraw/svdoattr.cxx: SdrAttrObj::ItemChange()
/*N*/     switch( pItemToSet->Which())
/*N*/     {
/*N*/       case XATTR_FILLBITMAP:
/*N*/           pItemToSet = ((XFillBitmapItem*)pItemToSet)->checkForUniqueItem( this );
/*N*/           break;
/*N*/       case XATTR_LINEDASH:
/*N*/           pItemToSet = ((XLineDashItem*)pItemToSet)->checkForUniqueItem( this );
/*N*/           break;
/*N*/       case XATTR_LINESTART:
/*N*/           pItemToSet = ((XLineStartItem*)pItemToSet)->checkForUniqueItem( this );
/*N*/           break;
/*N*/       case XATTR_LINEEND:
/*N*/           pItemToSet = ((XLineEndItem*)pItemToSet)->checkForUniqueItem( this );
/*N*/           break;
/*N*/       case XATTR_FILLGRADIENT:
/*N*/           pItemToSet = ((XFillGradientItem*)pItemToSet)->checkForUniqueItem( this );
/*N*/           break;
/*N*/       case XATTR_FILLFLOATTRANSPARENCE:
/*N*/           pItemToSet = ((XFillFloatTransparenceItem*)pItemToSet)->checkForUniqueItem( this );
/*N*/           break;
/*N*/       case XATTR_FILLHATCH:
/*N*/           pItemToSet = ((XFillHatchItem*)pItemToSet)->checkForUniqueItem( this );
/*N*/           break;
/*N*/     }
/*N*/
/*N*/     if( pItemToSet )
/*N*/         rDestItemSet.Put( *pItemToSet );
/*N*/
/*N*/     // delete item if it was a generated one
/*N*/     if( pNewItem != pItemToSet )
/*N*/         delete pItemToSet;
/*N*/ }

/*N*/ void ChartModel::PutItemSetWithNameCreation( SfxItemSet& rDestItemSet, const SfxItemSet& rNewItemSet )
/*N*/ {
/*N*/     // copy all attributes
/*N*/     rDestItemSet.Put( rNewItemSet );
/*N*/
/*N*/     // check for items that need name creation
/*N*/     SfxWhichIter        aIter( rNewItemSet );
/*N*/     sal_uInt16          nWhich = aIter.FirstWhich();
/*N*/     const SfxPoolItem*  pPoolItem = NULL;
/*N*/
/*N*/     while( nWhich )
/*N*/     {
/*N*/         switch( nWhich )
/*N*/         {
/*N*/             case XATTR_FILLBITMAP:
/*N*/             case XATTR_LINEDASH:
/*N*/             case XATTR_LINESTART:
/*N*/             case XATTR_LINEEND:
/*N*/             case XATTR_FILLGRADIENT:
/*N*/             case XATTR_FILLFLOATTRANSPARENCE:
/*N*/             case XATTR_FILLHATCH:
/*N*/                 if( SFX_ITEM_SET == rNewItemSet.GetItemState( nWhich, TRUE, &pPoolItem ))
/*N*/                     SetItemWithNameCreation( rDestItemSet, pPoolItem );
/*N*/         }
/*N*/         nWhich = aIter.NextWhich();
/*N*/     }
/*N*/ }
}
