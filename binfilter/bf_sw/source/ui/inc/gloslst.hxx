/*************************************************************************
 *
 *  $RCSfile: gloslst.hxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:19:59 $
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

#ifndef _GLOSLST_HXX
#define _GLOSLST_HXX


#ifndef _DATETIME_HXX
#include <tools/datetime.hxx>
#endif
#ifndef _STRING_HXX //autogen
#include <tools/string.hxx>
#endif
#ifndef _TIMER_HXX //autogen
#include <vcl/timer.hxx>
#endif
#ifndef _SVARRAY_HXX //autogen
#include <svtools/svarray.hxx>
#endif

class SwGlossaries;
class SvStringsISortDtor;

struct AutoTextGroup
{
    USHORT      nCount;
    String      sName;
    String      sTitle;
    String      sLongNames;   // durch 0x0A getrennte Langnamen
    String      sShortNames;  // durch 0x0A getrennte Kurznamen
    DateTime    aDateModified;
};


typedef AutoTextGroup* AutoTextGroupPtr;
SV_DECL_PTRARR(AutoTextGroups, AutoTextGroupPtr, 4, 4);

class SwGlossaryList : public AutoTimer
{
    AutoTextGroups  aGroupArr;
    String          sPath;
    BOOL            bFilled;

//STRIP001  AutoTextGroup*  FindGroup(const String& rGroupName);
//STRIP001  void            FillGroup(AutoTextGroup* pGroup, SwGlossaries* pGloss);

public:
        SwGlossaryList();
        ~SwGlossaryList();

//STRIP001  BOOL            HasLongName(const String& rBegin, SvStringsISortDtor* pLongNames );
//STRIP001  BOOL            GetShortName(const String& rLongName,
//STRIP001                                      String& rShortName, String& rGroupName );

//STRIP001  USHORT          GetGroupCount();
//STRIP001  String          GetGroupName(USHORT nPos, BOOL bNoPath = TRUE, String* pTitle = 0);
//STRIP001  USHORT          GetBlockCount(USHORT nGroup);
//STRIP001  String          GetBlockName(USHORT nGroup, USHORT nBlock, String& rShortName);

//STRIP001  void            Update();

//STRIP001  virtual void    Timeout();

    void            ClearGroups();
};

#endif






