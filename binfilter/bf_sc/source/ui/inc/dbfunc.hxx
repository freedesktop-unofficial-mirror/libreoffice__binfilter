/*************************************************************************
 *
 *  $RCSfile: dbfunc.hxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:18:24 $
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

#ifndef SC_DBFUNC_HXX
#define SC_DBFUNC_HXX

#include "viewfunc.hxx"

struct ScSortParam;
struct ScQueryParam;
class ScDBData;
class ScDBCollection;
class ScDPObject;
class ScDPSaveData;

// ---------------------------------------------------------------------------

class ScDBFunc : public ScViewFunc
{
public:
                    ScDBFunc( Window* pParent, ScDocShell& rDocSh, ScTabViewShell* pViewShell );
                     ScDBFunc( Window* pParent, const ScDBFunc& rDBFunc, ScTabViewShell* pViewShell );
                    ~ScDBFunc();

                    //  nur UISort wiederholt bei Bedarf die Teilergebnisse

//STRIP001  void            UISort( const ScSortParam& rSortParam,
//STRIP001                        BOOL bRecord = TRUE );

//STRIP001  void            Sort( const ScSortParam& rSortParam,
//STRIP001                        BOOL bRecord = TRUE, BOOL bPaint = TRUE );
//STRIP001  void            Query( const ScQueryParam& rQueryParam,
//STRIP001                         const ScRange* pAdvSource, BOOL bRecord );
//STRIP001  void            DoSubTotals( const ScSubTotalParam& rParam, BOOL bRecord = TRUE,
//STRIP001                          const ScSortParam* pForceNewSort = NULL );

//STRIP001  void            ToggleAutoFilter();
//STRIP001  void            HideAutoFilter();

//STRIP001  void            RepeatDB( BOOL bRecord = TRUE );

//STRIP001  BOOL            ImportData( const ScImportParam& rParam, BOOL bRecord = TRUE );

//STRIP001  void            GotoDBArea( const String& rDBName );

                    // DB-Bereich vom Cursor
    ScDBData*       GetDBData( BOOL bMarkArea = TRUE, ScGetDBMode eMode = SC_DB_MAKE );

//STRIP001  void            NotifyCloseDbNameDlg( const ScDBCollection& rNewColl, const List& rDelAreaList );

//STRIP001  void            Consolidate( const ScConsolidateParam& rParam, BOOL bRecord = TRUE );

//STRIP001  void            MakePivotTable( const ScDPSaveData& rData, const ScRange& rDest, BOOL bNewTable,
//STRIP001                                  const ScDPObject& rSource, BOOL bApi = FALSE );
//STRIP001  void            DeletePivotTable();
//STRIP001  void            RecalcPivotTable();

//STRIP001  void            MakeOutline( BOOL bColumns, BOOL bRecord = TRUE );
//STRIP001  void            RemoveOutline( BOOL bColumns, BOOL bRecord = TRUE );
//STRIP001  void            RemoveAllOutlines( BOOL bRecord = TRUE );
    void            TestRemoveOutline( BOOL& rCol, BOOL& rRow );

//STRIP001  void            AutoOutline( BOOL bRecord = TRUE );

//STRIP001  void            SelectLevel( BOOL bColumns, USHORT nLevel,
//STRIP001                                  BOOL bRecord = TRUE, BOOL bPaint = TRUE );
//STRIP001  void            ShowOutline( BOOL bColumns, USHORT nLevel, USHORT nEntry,
//STRIP001                                  BOOL bRecord = TRUE, BOOL bPaint = TRUE );
//STRIP001  void            HideOutline( BOOL bColumns, USHORT nLevel, USHORT nEntry,
//STRIP001                                  BOOL bRecord = TRUE, BOOL bPaint = TRUE );

//STRIP001  void            ShowMarkedOutlines( BOOL bRecord = TRUE );
//STRIP001  void            HideMarkedOutlines( BOOL bRecord = TRUE );
//STRIP001  BOOL            OutlinePossible(BOOL bHide);

    void            UpdateCharts(BOOL bAllCharts = FALSE);      // Default: am Cursor
};



#endif

