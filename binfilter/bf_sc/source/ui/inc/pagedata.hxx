/*************************************************************************
 *
 *  $RCSfile: pagedata.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2004-05-05 16:39:44 $
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

#ifndef SC_PAGEDATA_HXX
#define SC_PAGEDATA_HXX

#ifndef SC_SCGLOB_HXX
#include "global.hxx"
#endif
namespace binfilter {

//STRIP001 class ScDocShell;

//============================================================================

//STRIP001 class ScPrintRangeData
//STRIP001 {
//STRIP001 private:
//STRIP001  ScRange     aPrintRange;
//STRIP001  USHORT      nPagesX;
//STRIP001  USHORT*     pPageEndX;
//STRIP001  USHORT      nPagesY;
//STRIP001  USHORT*     pPageEndY;
//STRIP001  long        nFirstPage;
//STRIP001  BOOL        bTopDown;
//STRIP001  BOOL        bAutomatic;
//STRIP001
//STRIP001 public:
//STRIP001              ScPrintRangeData();
//STRIP001              ~ScPrintRangeData();
//STRIP001
//STRIP001  void            SetPrintRange( const ScRange& rNew )    { aPrintRange = rNew; }
//STRIP001  const ScRange&  GetPrintRange() const                   { return aPrintRange; }
//STRIP001
//STRIP001  void            SetPagesX( USHORT nCount, const USHORT* pEnd );
//STRIP001  void            SetPagesY( USHORT nCount, const USHORT* pEnd );
//STRIP001
//STRIP001  USHORT          GetPagesX() const       { return nPagesX;   }
//STRIP001  const USHORT*   GetPageEndX() const     { return pPageEndX; }
//STRIP001  USHORT          GetPagesY() const       { return nPagesY;   }
//STRIP001  const USHORT*   GetPageEndY() const     { return pPageEndY; }
//STRIP001
//STRIP001  void            SetFirstPage( long nNew )   { nFirstPage = nNew; }
//STRIP001  long            GetFirstPage() const        { return nFirstPage; }
//STRIP001  void            SetTopDown( BOOL bSet )     { bTopDown = bSet; }
//STRIP001  BOOL            IsTopDown() const           { return bTopDown; }
//STRIP001  void            SetAutomatic( BOOL bSet )   { bAutomatic = bSet; }
//STRIP001  BOOL            IsAutomatic() const         { return bAutomatic; }
//STRIP001 };

class ScPageBreakData
{
//STRIP001 private:
//STRIP001  USHORT              nAlloc;
//STRIP001  USHORT              nUsed;
//STRIP001  ScPrintRangeData*   pData;          // Array

public:
                ScPageBreakData(USHORT nMax){DBG_BF_ASSERT(0, "STRIP");} //STRIP001 ScPageBreakData(USHORT nMax);
//STRIP001              ~ScPageBreakData();
//STRIP001
//STRIP001  USHORT              GetCount() const            { return nUsed; }
//STRIP001  ScPrintRangeData&   GetData(USHORT i);
//STRIP001
//STRIP001  BOOL                IsEqual( const ScPageBreakData& rOther ) const;
//STRIP001
//STRIP001  void                AddPages();
};



} //namespace binfilter
#endif

