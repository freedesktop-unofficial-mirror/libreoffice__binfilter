/*************************************************************************
 *
 *  $RCSfile: optgrid.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 21:22:47 $
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
#ifndef _SVX_OPTGRID_HXX
#define _SVX_OPTGRID_HXX

// include ---------------------------------------------------------------

// auto strip #ifndef _SFXTABDLG_HXX //autogen
// auto strip #include <bf_sfx2/tabdlg.hxx>
// auto strip #endif
// auto strip #ifndef _SFXENUMITEM_HXX //autogen
// auto strip #include <svtools/eitem.hxx>
// auto strip #endif
// auto strip #ifndef _SV_GROUP_HXX //autogen
// auto strip #include <vcl/group.hxx>
// auto strip #endif
// auto strip #ifndef _SV_FIXED_HXX //autogen
// auto strip #include <vcl/fixed.hxx>
// auto strip #endif
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

//STRIP001 class SvxGridItem : public SvxOptionsGrid, public SfxPoolItem
//STRIP001 {
//STRIP001  // #i9076#
//STRIP001  friend class SvxGridTabPage;
//STRIP001
//STRIP001 public:
//STRIP001  SvxGridItem( USHORT nWhich) : SfxPoolItem(nWhich){};
//STRIP001  SvxGridItem( const SvxGridItem& pTestItem );
//STRIP001
//STRIP001  virtual SfxPoolItem*    Clone( SfxItemPool *pPool = 0 ) const;
//STRIP001  virtual int             operator==( const SfxPoolItem& ) const;
//STRIP001
//STRIP001  virtual SfxItemPresentation GetPresentation( SfxItemPresentation ePres,
//STRIP001                                  SfxMapUnit eCoreMetric,
//STRIP001                                  SfxMapUnit ePresMetric,
//STRIP001                                     String &rText, const IntlWrapper * = 0 ) const;
//STRIP001
//STRIP001 };

// class SvxGridTabPage --------------------------------------------------

//STRIP001 class SvxGridTabPage : public SfxTabPage
//STRIP001 {
//STRIP001 public:
//STRIP001  SvxGridTabPage( Window* pParent, const SfxItemSet& rSet );
//STRIP001
//STRIP001  static SfxTabPage*  Create( Window* pParent, const SfxItemSet& rAttrSet );
//STRIP001
//STRIP001  virtual BOOL        FillItemSet( SfxItemSet& rSet );
//STRIP001  virtual void        Reset( const SfxItemSet& rSet );
//STRIP001
//STRIP001  virtual void        ActivatePage( const SfxItemSet& rSet );
//STRIP001  virtual int         DeactivatePage( SfxItemSet* pSet );
//STRIP001
//STRIP001 private:
//STRIP001  CheckBox            aCbxUseGridsnap;
//STRIP001  CheckBox            aCbxGridVisible;
//STRIP001
//STRIP001     FixedLine           aFlResolution;
//STRIP001  FixedText           aFtDrawX;
//STRIP001  MetricField         aMtrFldDrawX;
//STRIP001  FixedText           aFtDrawY;
//STRIP001  MetricField         aMtrFldDrawY;
//STRIP001
//STRIP001     FixedLine           aFlDivision;
//STRIP001     FixedText           aFtDivisionX;
//STRIP001     NumericField        aNumFldDivisionX;
//STRIP001     FixedText           aDivisionPointX;
//STRIP001
//STRIP001     FixedText           aFtDivisionY;
//STRIP001     NumericField        aNumFldDivisionY;
//STRIP001     FixedText           aDivisionPointY;
//STRIP001
//STRIP001     CheckBox            aCbxSynchronize;
//STRIP001     FixedLine           aGrpDrawGrid; // Neu
//STRIP001
//STRIP001 protected:
//STRIP001     //these controls are used in draw and impress
//STRIP001     FixedLine       aGrpSnap;
//STRIP001     CheckBox        aCbxSnapHelplines;
//STRIP001  CheckBox        aCbxSnapBorder;
//STRIP001  CheckBox        aCbxSnapFrame;
//STRIP001  CheckBox        aCbxSnapPoints;
//STRIP001  FixedText       aFtSnapArea;
//STRIP001  MetricField     aMtrFldSnapArea;
//STRIP001
//STRIP001     FixedLine       aSeparatorFL;
//STRIP001
//STRIP001     FixedLine       aGrpOrtho;
//STRIP001     CheckBox        aCbxOrtho;
//STRIP001  CheckBox        aCbxBigOrtho;
//STRIP001  CheckBox        aCbxRotate;
//STRIP001  MetricField     aMtrFldAngle;
//STRIP001  FixedText       aFtBezAngle;
//STRIP001  MetricField     aMtrFldBezAngle;
//STRIP001
//STRIP001 private:
//STRIP001     BOOL                bAttrModified;
//STRIP001  BOOL                bEqualGrid; // Neu
//STRIP001
//STRIP001 #ifdef _SVX_OPTGRID_CXX
//STRIP001     DECL_LINK( ClickRotateHdl_Impl, void * );
//STRIP001     DECL_LINK( ChangeDrawHdl_Impl, MetricField * );
//STRIP001     DECL_LINK( ChangeGridsnapHdl_Impl, void * );
//STRIP001     DECL_LINK( ChangeDivisionHdl_Impl, NumericField * );
//STRIP001
//STRIP001 #endif
//STRIP001 };

}//end of namespace binfilter
#endif

