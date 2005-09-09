/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: gloslst.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 05:35:25 $
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
class SvStringsISortDtor;
namespace binfilter {

class SwGlossaries;


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
SV_DECL_PTRARR(AutoTextGroups, AutoTextGroupPtr, 4, 4)//STRIP008 ;

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

} //namespace binfilter
#endif






