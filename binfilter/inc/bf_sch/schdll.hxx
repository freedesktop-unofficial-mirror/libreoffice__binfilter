/*************************************************************************
 *
 *  $RCSfile: schdll.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 08:25:32 $
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

#ifndef _SCH_DLL_HXX
#define _SCH_DLL_HXX

#include <bf_sfx2/sfxdefs.hxx>

// header for class SfxModule
#ifndef _SFXMODULE_HXX
#include <bf_sfx2/module.hxx>
#endif
// header for class SvInPlaceObject
#ifndef _IPOBJ_HXX
#include <so3/ipobj.hxx>
#endif

#include <bf_sch/chattr.hxx>    // to do: remove this line and replace most of the schdll.hxx includes to chattr.hxx
class SvFactory;
class SvInPlaceObjectRef;
class OutputDevice;
class Window;
class SvStream;
namespace binfilter {

#define extern_c extern "C"

/*-------------------------------------------------------------------------

  The class SchDLL initializes the data, interfaces, controls, etc.
  that are needed by the shared library.

  It also maintains the ressource manager.

  to use the shared chart library SchDLL must be instanciated.

-------------------------------------------------------------------------*/

class SchDragServer;
class SchMemChart;
class SfxMedium;
class SfxFilter;
class XOutdevItemPool;
class SfxTabDialog;
class ChartModel;

class SchDLL
{
public:

    SchDLL();
    ~SchDLL();

    static void     Init();
    static void     Exit();
    static void     LibInit();
    static void     LibExit();

    static ULONG DetectFilter( SfxMedium& rMedium, const SfxFilter **pFilter,
                               SfxFilterFlags nMust, SfxFilterFlags nDont );

    static void     Update( SvInPlaceObjectRef aIPObj, SchMemChart* pData, OutputDevice* pOut=NULL);
    static void     Update( SvInPlaceObjectRef aIPObj, SchMemChart* pData,
                            const SfxItemSet& rAttr, OutputDevice* pOut = NULL );

    static ModalDialog* CreateAutoPilotDlg( Window* pParent, SchMemChart* pData,
                                            const SfxItemSet& rInAttrs,
                                            SfxItemSet& rOutAttrs,
                                            BOOL bPrePage = FALSE );
    static void ChangeChartData( ModalDialog* pDlg, SchMemChart* pData );

    static SfxTabDialog* CreateOptionsDlg( Window* pParent, const SfxItemSet& rInAttrs, XOutdevItemPool* pItemPool );
    static SchMemChart*  GetChartData( SvInPlaceObjectRef aIPObj );

    static SchMemChart* NewMemChart();
    static SchMemChart* NewMemChart( short nCols, short nRows );
    static SchMemChart* NewMemChart( const SchMemChart &rMemChart );
    static ChartModel*  GetModel( SvInPlaceObjectRef aIPObj );

    static void SetTransparentBackground( SvInPlaceObjectRef aIPObj, BOOL bTransp = TRUE );
    static void GetDefaultForColumnText( const SchMemChart& rMemChart, sal_Int32 nCol, String& aResult );
    static void GetDefaultForRowText( const SchMemChart& rMemChart, sal_Int32 nRow, String& aResult );

    static void ConvertChartRangeForWriter( SchMemChart& rMemChart,
                                            BOOL bOldToNew );
    static void ConvertChartRangeForCalc( SchMemChart& rMemChart,
                                            BOOL bOldToNew );

    static void MemChartResetTranslation( SchMemChart& rMemChart,
                                            long *pTable,long nCnt );
    static void MemChartUpdateTranslation( SchMemChart& rMemChart,
                                               long *pTable,long nCnt );

    static void MemChartInsertCols( SchMemChart& rMemChart,
                                    short nAtCol, short nCount);
    static void MemChartRemoveCols( SchMemChart& rMemChart,
                                    short nAtCol, short nCount);

    static void MemChartInsertRows( SchMemChart& rMemChart,
                                    short nAtRow, short nCount);
    static void MemChartRemoveRows( SchMemChart& rMemChart,
                                    short nAtRow, short nCount);

    static void MemChartSwapCols( SchMemChart& rMemChart,
                                  int nAtCol1, int nAtCol2);
    static void MemChartSwapRows( SchMemChart& rMemChart,
                                  int nAtRow1,int nAtRow2);

};

/*-------------------------------------------------------------------------

  The following functions are called from the static interface (above)
  after the shared library has been loaded

-------------------------------------------------------------------------*/

extern_c void __LOADONCALLAPI SchUpdate( SvInPlaceObjectRef aIPObj, SchMemChart* pData, OutputDevice* pOut = NULL );
extern_c void __LOADONCALLAPI SchUpdateAttr( SvInPlaceObjectRef aIPObj, SchMemChart* pData,
                                             const SfxItemSet& rAttr, OutputDevice* pOut = NULL );
extern_c ModalDialog* __LOADONCALLAPI SchCreateDiagramAutoPilotDlg( Window* pParent, SchMemChart* pData,
                                                                    const SfxItemSet& rInAttrs,
                                                                    SfxItemSet& rOutAttrs,
                                                                    BOOL bPrePage = FALSE );
extern_c void __LOADONCALLAPI SchChangeChartData( ModalDialog* pDlg, SchMemChart* pData );
extern_c SfxTabDialog* __LOADONCALLAPI SchCreateOptionsDlg( Window* pParent,
                                                            const SfxItemSet& rInAttrs,
                                                            XOutdevItemPool* pItemPool );
extern_c SchMemChart* __LOADONCALLAPI SchGetChartData( SvInPlaceObjectRef aIPObj );
extern_c SchMemChart* __LOADONCALLAPI SchNewMemChartNone();
extern_c SchMemChart* __LOADONCALLAPI SchNewMemChartXY( short nCols, short nRows );
extern_c SchMemChart* __LOADONCALLAPI SchNewMemChartCopy( const SchMemChart &rMemChart );
//STRIP001 extern_c ChartModel*  __LOADONCALLAPI SchGetModel( SvInPlaceObjectRef aIPObj );
extern_c void __LOADONCALLAPI SetTransparentBackground( SvInPlaceObjectRef aIPObj, BOOL bTransp = TRUE );
extern_c void __LOADONCALLAPI SchGetDefaultForColumnText( const SchMemChart& rMemChart, sal_Int32 nCol, String& aResult );
extern_c void __LOADONCALLAPI SchGetDefaultForRowText( const SchMemChart& rMemChart, sal_Int32 nRow, String& aResult );

} //namespace binfilter
#endif          // _SCH_DLL_HXX

