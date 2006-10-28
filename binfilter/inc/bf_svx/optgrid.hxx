/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: optgrid.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 03:48:56 $
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
#ifndef _SVX_OPTGRID_HXX
#define _SVX_OPTGRID_HXX

// include ---------------------------------------------------------------

#ifndef _SV_FIELD_HXX //autogen
#include <vcl/field.hxx>
#endif
namespace binfilter {

class SvxGridTabPage;

// class SvxOptionsGrid --------------------------------------------------

class SvxOptionsGrid
{
protected:
    UINT32  nFldDrawX;
    UINT32  nFldDivisionX;
    UINT32  nFldDrawY;
    UINT32  nFldDivisionY;
    UINT32  nFldSnapX;
    UINT32  nFldSnapY;
    BOOL    bUseGridsnap:1;
    BOOL    bSynchronize:1;
    BOOL    bGridVisible:1;
    BOOL    bEqualGrid:  1;

public:
    SvxOptionsGrid();
    ~SvxOptionsGrid();

    void    SetFldDrawX(    UINT32 nSet){nFldDrawX      = nSet;}
    void    SetFldDivisionX(UINT32 nSet){nFldDivisionX  = nSet;}
    void    SetFldDrawY   ( UINT32 nSet){nFldDrawY      = nSet;}
    void    SetFldDivisionY(UINT32 nSet){nFldDivisionY  = nSet;}
    void    SetFldSnapX(    UINT32 nSet){nFldSnapX      = nSet;}
    void    SetFldSnapY   ( UINT32 nSet){nFldSnapY      = nSet;}
    void    SetUseGridSnap( BOOL bSet ) {bUseGridsnap   = bSet;}
    void    SetSynchronize( BOOL bSet ) {bSynchronize   = bSet;}
    void    SetGridVisible( BOOL bSet ) {bGridVisible   = bSet;}
    void    SetEqualGrid( BOOL bSet )   {bEqualGrid     = bSet;}

    UINT32  GetFldDrawX(    ) const {  return nFldDrawX;    }
    UINT32  GetFldDivisionX() const {  return nFldDivisionX;}
    UINT32  GetFldDrawY   ( ) const {  return nFldDrawY;    }
    UINT32  GetFldDivisionY() const {  return nFldDivisionY;}
    UINT32  GetFldSnapX(    ) const {  return nFldSnapX;    }
    UINT32  GetFldSnapY   ( ) const {  return nFldSnapY;    }
    BOOL    GetUseGridSnap( ) const {  return bUseGridsnap; }
    BOOL    GetSynchronize( ) const {  return bSynchronize; }
    BOOL    GetGridVisible( ) const {  return bGridVisible; }
    BOOL    GetEqualGrid()    const {  return bEqualGrid;   }
};

// class SvxGridItem -----------------------------------------------------


// class SvxGridTabPage --------------------------------------------------


}//end of namespace binfilter
#endif

