/*************************************************************************
 *
 *  $RCSfile: tpcalc.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 12:05:21 $
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

#ifndef SC_TPCALC_HXX
#define SC_TPCALC_HXX


// auto strip #ifndef _SFXTABDLG_HXX //autogen
// auto strip #include <bf_sfx2/tabdlg.hxx>
// auto strip #endif

// auto strip #ifndef _SV_FIXED_HXX //autogen
// auto strip #include <vcl/fixed.hxx>
// auto strip #endif

// auto strip #ifndef _SV_FIELD_HXX //autogen
// auto strip #include <vcl/field.hxx>
// auto strip #endif

// auto strip #ifndef _SV_GROUP_HXX //autogen
// auto strip #include <vcl/group.hxx>
// auto strip #endif

// auto strip #ifndef _STDCTRL_HXX //autogen
// auto strip #include <svtools/stdctrl.hxx>
// auto strip #endif
namespace binfilter {


//===================================================================

class ScDocOptions;

//STRIP001 class ScTpCalcOptions : public SfxTabPage
//STRIP001 {
//STRIP001 public:
//STRIP001  static  SfxTabPage* Create          ( Window*               pParent,
//STRIP001                                        const SfxItemSet&     rCoreSet );
//STRIP001  static  USHORT*     GetRanges       ();
//STRIP001  virtual BOOL        FillItemSet     ( SfxItemSet& rCoreSet );
//STRIP001  virtual void        Reset           ( const SfxItemSet& rCoreSet );
//STRIP001  virtual int         DeactivatePage  ( SfxItemSet* pSet = NULL );
//STRIP001
//STRIP001 private:
//STRIP001              ScTpCalcOptions( Window*            pParent,
//STRIP001                               const SfxItemSet&  rCoreSet );
//STRIP001              ~ScTpCalcOptions();
//STRIP001
//STRIP001 private:
//STRIP001     FixedLine       aGbZRefs;
//STRIP001     CheckBox        aBtnIterate;
//STRIP001  FixedText       aFtSteps;
//STRIP001  NumericField    aEdSteps;
//STRIP001  FixedText       aFtEps;
//STRIP001  Edit            aEdEps;
//STRIP001
//STRIP001     FixedLine       aSeparatorFL;
//STRIP001     FixedLine       aGbDate;
//STRIP001     RadioButton     aBtnDateStd;
//STRIP001  RadioButton     aBtnDateSc10;
//STRIP001  RadioButton     aBtnDate1904;
//STRIP001
//STRIP001     FixedLine       aHSeparatorFL;
//STRIP001     CheckBox        aBtnCase;
//STRIP001  CheckBox        aBtnCalc;
//STRIP001  CheckBox        aBtnMatch;
//STRIP001     CheckBox        aBtnRegex;
//STRIP001  CheckBox        aBtnLookUp;
//STRIP001
//STRIP001  FixedText       aFtPrec;
//STRIP001  NumericField    aEdPrec;
//STRIP001
//STRIP001  String          aDecSep;
//STRIP001
//STRIP001  ScDocOptions*   pOldOptions;
//STRIP001  ScDocOptions*   pLocalOptions;
//STRIP001  USHORT          nWhichCalc;
//STRIP001
//STRIP001 #ifdef _TPCALC_CXX
//STRIP001 private:
//STRIP001  void            Init();
//STRIP001  BOOL            CheckEps();
//STRIP001  BOOL            GetEps( double& rEps );
//STRIP001
//STRIP001  //------------------------------------
//STRIP001  // Handler:
//STRIP001  DECL_LINK( RadioClickHdl, RadioButton* );
//STRIP001  DECL_LINK( CheckClickHdl, CheckBox* );
//STRIP001
//STRIP001 #endif
//STRIP001 };


} //namespace binfilter
#endif

