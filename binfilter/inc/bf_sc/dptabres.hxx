/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: dptabres.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 02:34:49 $
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
public:
    ScDPResultData( ScDPSource* pSrc ) {DBG_BF_ASSERT(0, "STRIP");} //STRIP001 ScDPResultData( ScDPSource* pSrc );      //! Ref
                        ~ScDPResultData(){DBG_BF_ASSERT(0, "STRIP");} //STRIP001 ~ScDPResultData();





};


class ScDPResultMember
{

public:
                        ScDPResultMember( ScDPResultData* pData, ScDPDimension* pDim,
                                            ScDPLevel* pLev, ScDPMember* pDesc,
                                            BOOL bForceSub ) {DBG_BF_ASSERT(0, "STRIP");} //STRIP001 BOOL bForceSub );  //! Ref
                        ~ScDPResultMember(){DBG_BF_ASSERT(0, "STRIP");} //STRIP001 ~ScDPResultMember();



//  BOOL                SubTotalEnabled() const;






                        //! this will be removed!
};









                        //! this will be removed!

//! replace PtrArr with 32-bit array ????




//  result dimension contains only members



                        //  allocates new members



                        //  modifies existing members, allocates data dimensions



                        //  for ScDPDataDimension::InitFrom






} //namespace binfilter
#endif

