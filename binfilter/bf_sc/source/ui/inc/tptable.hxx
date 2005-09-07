/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: tptable.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-07 20:24:20 $
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

#ifndef SC_TPTABLE_HXX
#define SC_TPTABLE_HXX

#ifndef _SFXTABDLG_HXX //autogen
#include <bf_sfx2/tabdlg.hxx>
#endif

#ifndef _SV_FIXED_HXX //autogen
#include <vcl/fixed.hxx>
#endif

#ifndef _SV_FIELD_HXX //autogen
#include <vcl/field.hxx>
#endif
namespace binfilter {

//===================================================================

class ScTablePage : public SfxTabPage
{
public:
    static  SfxTabPage* Create          ( Window*           pParent,
                                          const SfxItemSet& rCoreSet );
    static  USHORT*     GetRanges       ();
    virtual BOOL        FillItemSet     ( SfxItemSet& rCoreSet );
    virtual void        Reset           ( const SfxItemSet& rCoreSet );
    virtual int         DeactivatePage  ( SfxItemSet* pSet = NULL );
    virtual void        DataChanged     ( const DataChangedEvent& rDCEvt );

private:
           ScTablePage( Window*         pParent,
                         const SfxItemSet&  rCoreSet );
            ~ScTablePage();

    void            ShowImage();

private:
    FixedLine       aFlPageDir;
    RadioButton     aBtnTopDown;
    RadioButton     aBtnLeftRight;
    FixedImage      aBmpPageDir;
    Image           aImgLeftRight;
    Image           aImgTopDown;
    Image           aImgLeftRightHC;
    Image           aImgTopDownHC;
    CheckBox        aBtnPageNo;
    NumericField    aEdPageNo;

    FixedLine       aFlPrint;
    CheckBox        aBtnHeaders;
    CheckBox        aBtnGrid;
    CheckBox        aBtnNotes;
    CheckBox        aBtnObjects;
    CheckBox        aBtnCharts;
    CheckBox        aBtnDrawings;
    CheckBox        aBtnFormulas;
    CheckBox        aBtnNullVals;

    FixedLine       aFlScale;
    RadioButton     aBtnScaleAll;
    RadioButton     aBtnScalePageNum;
    MetricField     aEdScaleAll;
    NumericField    aEdScalePageNum;

#ifdef _TPTABLE_CXX
private:
    //------------------------------------
    // Handler:
    DECL_LINK( ScaleHdl,   RadioButton* );
    DECL_LINK( PageDirHdl, RadioButton* );
    DECL_LINK( PageNoHdl,  CheckBox* );
#endif
};



} //namespace binfilter
#endif // SC_TPTABLE_HXX
