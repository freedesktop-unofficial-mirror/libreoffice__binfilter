/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: refundo.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-07 20:10:58 $
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

#ifndef SC_REFUNDO_HXX
#define SC_REFUNDO_HXX

#ifndef _SOLAR_H
#include <tools/solar.h>
#endif
#include <tools/debug.hxx>
namespace binfilter {
class ScDocument;
//STRIP001 class ScDBCollection;
//STRIP001 class ScRangeName;
//STRIP001 class ScPrintRangeSaver;
//STRIP001 class ScPivotCollection;
//STRIP001 class ScDPCollection;
//STRIP001 class ScChartCollection;
//STRIP001 class ScConditionalFormatList;
//STRIP001 class ScDetOpList;
//STRIP001 class ScChartListenerCollection;
//STRIP001 class ScAreaLinkSaveCollection;

class ScRefUndoData
{
private:
//STRIP001  ScDBCollection*             pDBCollection;
//STRIP001  ScRangeName*                pRangeName;
//STRIP001  ScPrintRangeSaver*          pPrintRanges;
//STRIP001  ScPivotCollection*          pPivotCollection;
//STRIP001  ScDPCollection*             pDPCollection;
//STRIP001  ScConditionalFormatList*    pCondFormList;
//STRIP001  ScDetOpList*                pDetOpList;
//STRIP001  ScChartListenerCollection*  pChartListenerCollection;
//STRIP001  ScAreaLinkSaveCollection*   pAreaLinks;

public:
                ScRefUndoData( const ScDocument* pDoc ){DBG_BF_ASSERT(0, "STRIP");} //STRIP001 ScRefUndoData( const ScDocument* pDoc );
//STRIP001              ~ScRefUndoData();

//STRIP001  void        DeleteUnchanged( const ScDocument* pDoc );
//STRIP001  void        DoUndo( ScDocument* pDoc, BOOL bUndoRefFirst );
};



} //namespace binfilter
#endif

