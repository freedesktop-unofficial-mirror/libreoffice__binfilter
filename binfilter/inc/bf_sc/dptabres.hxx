/*************************************************************************
 *
 *  $RCSfile: dptabres.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2004-05-05 16:29:55 $
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

#ifndef SC_DPTABRES_HXX
#define SC_DPTABRES_HXX

#ifndef _SVARRAY_HXX //autogen
#include <svtools/svarray.hxx>
#endif

#ifndef _STRING_HXX //autogen
#include <tools/string.hxx>
#endif

#ifndef _COM_SUN_STAR_SHEET_MEMBERRESULT_HPP_
#include <com/sun/star/sheet/MemberResult.hpp>
#endif
#ifndef _COM_SUN_STAR_SHEET_DATARESULT_HPP_
#include <com/sun/star/sheet/DataResult.hpp>
#endif
#ifndef _COM_SUN_STAR_UNO_SEQUENCE_HXX_
#include <com/sun/star/uno/Sequence.hxx>
#endif

#ifndef SC_SCGLOB_HXX
#include "global.hxx"       // enum ScSubTotalFunc
#endif
namespace binfilter {


class ScAddress;
class ScDocument;
class ScDPSource;
class ScDPDimension;
class ScDPLevel;
class ScDPMember;
class ScDPAggData;

struct ScDPValueData;

//
//  aggregated data
//! separate header file?
//

//STRIP001 class ScDPAggData
//STRIP001 {
//STRIP001 private:
//STRIP001  double          fVal;
//STRIP001  double          fSquare;
//STRIP001  long            nCount;
//STRIP001  ScDPAggData*    pChild;
//STRIP001
//STRIP001 public:
//STRIP001          ScDPAggData() : fVal(0.0), fSquare(0.0), nCount(0), pChild(NULL) {}
//STRIP001          ~ScDPAggData() { delete pChild; }

//STRIP001  void    Update( const ScDPValueData& rNext, ScSubTotalFunc eFunc );
//STRIP001  double  GetResult( ScSubTotalFunc eFunc ) const;
//STRIP001  BOOL    HasError( ScSubTotalFunc eFunc ) const;
//STRIP001  BOOL    HasData() const                         { return ( nCount != 0 ); }

//STRIP001  const ScDPAggData*  GetExistingChild() const    { return pChild; }
//STRIP001  ScDPAggData*        GetChild();
//STRIP001 };


// --------------------------------------------------------------------
//
//  results for a hierarchy dimension
//

#define SC_DP_RES_GROW  16

class ScDPResultDimension;
class ScDPDataDimension;
class ScDPDataMember;
struct ScDPItemData;


#define SC_DPMEASURE_ALL    -1
#define SC_DPMEASURE_ANY    -2

class ScDPResultData
{
//STRIP001 private:
//STRIP001  ScDPSource*             pSource;                //! Ref
//STRIP001  //! keep things like measure lists here
//STRIP001
//STRIP001  long                    nMeasCount;
//STRIP001  ScSubTotalFunc*         pMeasFuncs;
//STRIP001  String*                 pMeasNames;
//STRIP001  BOOL                    bDataAtCol;
//STRIP001  BOOL                    bDataAtRow;
//STRIP001
public:
    ScDPResultData( ScDPSource* pSrc ) {DBG_BF_ASSERT(0, "STRIP");} //STRIP001 ScDPResultData( ScDPSource* pSrc );      //! Ref
                        ~ScDPResultData(){DBG_BF_ASSERT(0, "STRIP");} //STRIP001 ~ScDPResultData();

//STRIP001  void                SetMeasureData( long nCount, const ScSubTotalFunc* pFunctions,
//STRIP001                                      const String* pNames );
//STRIP001  void                SetDataLayoutOrientation( USHORT nOrient );

//STRIP001  long                GetMeasureCount() const     { return nMeasCount; }
//STRIP001  ScSubTotalFunc      GetMeasureFunction(long nMeasure) const;
//STRIP001  String              GetMeasureString(long nMeasure, BOOL bForce, ScSubTotalFunc eForceFunc) const;
//STRIP001  String              GetMeasureDimensionName(long nMeasure) const;

//STRIP001  BOOL                IsDataAtCol() const             { return bDataAtCol; }
//STRIP001  BOOL                IsDataAtRow() const             { return bDataAtRow; }

//STRIP001  long                GetColStartMeasure() const;
//STRIP001  long                GetRowStartMeasure() const;

//STRIP001  long                GetCountForMeasure( long nMeas ) const
//STRIP001                              { return ( nMeas == SC_DPMEASURE_ALL ) ? nMeasCount : 1; }
};


class ScDPResultMember
{
//STRIP001 private:
//STRIP001  ScDPResultData*         pResultData;
//STRIP001  ScDPDimension*          pParentDim;             //! Ref
//STRIP001  ScDPLevel*              pParentLevel;           //! Ref
//STRIP001  ScDPMember*             pMemberDesc;            //! Ref
//STRIP001  ScDPResultDimension*    pChildDimension;
//STRIP001  ScDPDataMember*         pDataRoot;
//STRIP001  BOOL                    bHasElements;
//STRIP001  BOOL                    bForceSubTotal;
//STRIP001  BOOL                    bInitialized;

public:
                        ScDPResultMember( ScDPResultData* pData, ScDPDimension* pDim,
                                            ScDPLevel* pLev, ScDPMember* pDesc,
                                            BOOL bForceSub ) {DBG_BF_ASSERT(0, "STRIP");} //STRIP001 BOOL bForceSub );  //! Ref
                        ~ScDPResultMember(){DBG_BF_ASSERT(0, "STRIP");} //STRIP001 ~ScDPResultMember();

//STRIP001  void                InitFrom( ScDPDimension** ppDim, ScDPLevel** ppLev );
//STRIP001  void                LateInitFrom( ScDPDimension** ppDim, ScDPLevel** ppLev, ScDPItemData* pItemData );

//STRIP001  String              GetName() const;
//STRIP001  BOOL                IsValid() const;
//STRIP001  BOOL                IsVisible() const;
//STRIP001  long                GetSize(long nMeasure) const;

//  BOOL                SubTotalEnabled() const;
//STRIP001  long                GetSubTotalCount() const;

//STRIP001  BOOL                IsNamedItem( const ScDPItemData& r ) const;

//STRIP001  void                SetHasElements()    { bHasElements = TRUE; }

//STRIP001  void                ProcessData( const ScDPItemData* pChildMembers,
//STRIP001                                      ScDPResultDimension* pDataDim,
//STRIP001                                      const ScDPItemData* pDataMembers,
//STRIP001                                      const ScDPValueData* pValues );

//STRIP001  void                FillMemberResults( ::com::sun::star::uno::Sequence<
//STRIP001                                              ::com::sun::star::sheet::MemberResult>* pSequences,
//STRIP001                                          long& rPos, long nMeasure, BOOL bRoot,
//STRIP001                                          const String* pMemberName,
//STRIP001                                          const String* pMemberCaption );

//STRIP001  void                FillDataResults( const ScDPResultMember* pRefMember,
//STRIP001                                  ::com::sun::star::uno::Sequence<
//STRIP001                                      ::com::sun::star::uno::Sequence<
//STRIP001                                          ::com::sun::star::sheet::DataResult> >& rSequence,
//STRIP001                                  long& rRow, long nMeasure ) const;

                        //! this will be removed!
//STRIP001  const ScDPResultDimension*  GetChildDimension() const   { return pChildDimension; }
//STRIP001  ScDPResultDimension*        GetChildDimension()         { return pChildDimension; }
//STRIP001
//STRIP001  ScDPDimension*          GetParentDim()      { return pParentDim; }          //! Ref
//STRIP001  ScDPLevel*              GetParentLevel()    { return pParentLevel; }        //! Ref
};

//STRIP001 class ScDPDataMember
//STRIP001 {
//STRIP001 private:
//STRIP001  ScDPResultData*         pResultData;
//STRIP001  ScDPResultMember*       pResultMember;          //! Ref?
//STRIP001  ScDPDataDimension*      pChildDimension;
//STRIP001  ScDPAggData             aAggregate;
//STRIP001
//STRIP001  void                UpdateValues(const ScDPValueData* pValues);

//STRIP001 public:
//STRIP001                      ScDPDataMember( ScDPResultData* pData, ScDPResultMember* pRes );
//STRIP001                      ~ScDPDataMember();

//STRIP001  void                InitFrom( ScDPResultDimension* pDim );

//STRIP001  String              GetName() const;
//STRIP001  BOOL                HasData(long nMeasure) const;

//STRIP001  BOOL                IsNamedItem( const ScDPItemData& r ) const;

//STRIP001  void                ProcessData( const ScDPItemData* pChildMembers, const ScDPValueData* pValues );

//STRIP001  BOOL                HasError(long nMeasure) const;
//STRIP001  double              GetAggregate(long nMeasure) const;

//STRIP001  void                FillDataRow( const ScDPResultMember* pRefMember,
//STRIP001                                  ::com::sun::star::uno::Sequence< ::com::sun::star::sheet::DataResult>& rSequence,
//STRIP001                                  long& rCol, long nMeasure, BOOL bIsSubTotalRow ) const;

                        //! this will be removed!
//STRIP001  const ScDPDataDimension*    GetChildDimension() const   { return pChildDimension; }
//STRIP001  ScDPDataDimension*          GetChildDimension()         { return pChildDimension; }
//STRIP001 };

//! replace PtrArr with 32-bit array ????

//STRIP001 typedef ScDPResultMember* ScDPResultMemberPtr;
//STRIP001 SV_DECL_PTRARR_DEL(ScDPResultMembers, ScDPResultMemberPtr, SC_DP_RES_GROW, SC_DP_RES_GROW)//STRIP008 ;

//STRIP001 typedef ScDPDataMember* ScDPDataMemberPtr;
//STRIP001 SV_DECL_PTRARR_DEL(ScDPDataMembers, ScDPDataMemberPtr, SC_DP_RES_GROW, SC_DP_RES_GROW)//STRIP008 ;


//  result dimension contains only members

//STRIP001 class ScDPResultDimension
//STRIP001 {
//STRIP001 private:
//STRIP001  ScDPResultData*         pResultData;
//STRIP001  ScDPResultMembers       aMembers;
//STRIP001  BOOL                    bIsDataLayout;      //! or ptr to IntDimension?

//STRIP001 public:
//STRIP001                      ScDPResultDimension( ScDPResultData* pData );
//STRIP001                      ~ScDPResultDimension();

                        //  allocates new members
//STRIP001  void                InitFrom( ScDPDimension** ppDim, ScDPLevel** ppLev );
//STRIP001  void                LateInitFrom( ScDPDimension** ppDim, ScDPLevel** ppLev, ScDPItemData* pItemData );

//STRIP001  long                GetSize(long nMeasure) const;

//STRIP001  BOOL                IsValidEntry( const ScDPItemData* pMembers ) const;

                        //  modifies existing members, allocates data dimensions
//STRIP001  void                ProcessData( const ScDPItemData* pMembers,
//STRIP001                                      ScDPResultDimension* pDataDim,
//STRIP001                                      const ScDPItemData* pDataMembers,
//STRIP001                                      const ScDPValueData* pValues ); //! Test

//STRIP001  void                FillMemberResults( ::com::sun::star::uno::Sequence<
//STRIP001                                              ::com::sun::star::sheet::MemberResult>* pSequences,
//STRIP001                                          long nStart, long nMeasure );

//STRIP001  void                FillDataResults( const ScDPResultMember* pRefMember,
//STRIP001                                  ::com::sun::star::uno::Sequence<
//STRIP001                                      ::com::sun::star::uno::Sequence<
//STRIP001                                          ::com::sun::star::sheet::DataResult> >& rSequence,
//STRIP001                                  long nRow, long nMeasure ) const;

                        //  for ScDPDataDimension::InitFrom
//STRIP001  long                GetMemberCount() const;
//STRIP001  ScDPResultMember*   GetMember(long n) const;

//STRIP001  BOOL                IsDataLayout() const    { return bIsDataLayout; }

//STRIP001  ScDPResultDimension* GetFirstChildDimension() const;
//STRIP001 };

//STRIP001 class ScDPDataDimension
//STRIP001 {
//STRIP001 private:
//STRIP001  ScDPResultData*     pResultData;
//STRIP001  ScDPDataMembers     aMembers;
//STRIP001  BOOL                bIsDataLayout;      //! or ptr to IntDimension?
//STRIP001
//STRIP001 public:
//STRIP001                      ScDPDataDimension( ScDPResultData* pData );
//STRIP001                      ~ScDPDataDimension();

//STRIP001  void                InitFrom( ScDPResultDimension* pDim );      // recursive
//STRIP001  void                ProcessData( const ScDPItemData* pDataMembers, const ScDPValueData* pValues );

//STRIP001  void                FillDataRow( const ScDPResultDimension* pRefDim,
//STRIP001                                  ::com::sun::star::uno::Sequence< ::com::sun::star::sheet::DataResult>& rSequence,
//STRIP001                                  long nCol, long nMeasure, BOOL bIsSubTotalRow ) const;
//STRIP001 };

} //namespace binfilter
#endif

