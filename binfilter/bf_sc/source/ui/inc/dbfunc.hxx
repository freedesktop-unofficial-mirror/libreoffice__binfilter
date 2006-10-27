/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: dbfunc.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-27 16:05:54 $
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

#ifndef SC_DBFUNC_HXX
#define SC_DBFUNC_HXX

#include "viewfunc.hxx"
namespace binfilter {

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







                    // DB-Bereich vom Cursor
    ScDBData*       GetDBData( BOOL bMarkArea = TRUE, ScGetDBMode eMode = SC_DB_MAKE );




    void            TestRemoveOutline( BOOL& rCol, BOOL& rRow );




    void            UpdateCharts(BOOL bAllCharts = FALSE);      // Default: am Cursor
};



} //namespace binfilter
#endif

