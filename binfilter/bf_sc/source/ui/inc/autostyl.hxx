/*************************************************************************
 *
 *  $RCSfile: autostyl.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 11:58:19 $
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

#ifndef SC_AUTOSTYL_HXX
#define SC_AUTOSTYL_HXX

// auto strip #ifndef _TIMER_HXX //autogen
// auto strip #include <vcl/timer.hxx>
// auto strip #endif
// auto strip #ifndef _LIST_HXX //autogen
// auto strip #include <tools/list.hxx>
// auto strip #endif
// auto strip #ifndef _STRING_HXX //autogen
// auto strip #include <tools/string.hxx>
// auto strip #endif
#include <tools/debug.hxx> //STRIP001
namespace binfilter {
class ScDocShell;
class ScRange;

class ScAutoStyleList
{
//STRIP001 private:
//STRIP001  ScDocShell*     pDocSh;
//STRIP001  Timer           aTimer;
//STRIP001  Timer           aInitTimer;
//STRIP001  ULONG           nTimerStart;
//STRIP001  List            aEntries;
//STRIP001  List            aInitials;
//STRIP001
//STRIP001  void    ExecuteEntries();
//STRIP001  void    AdjustEntries(ULONG nDiff);
//STRIP001  void    StartTimer(ULONG nNow);
//STRIP001  DECL_LINK( TimerHdl, Timer* );
//STRIP001  DECL_LINK( InitHdl, Timer* );

public:
            ScAutoStyleList(ScDocShell* pShell){DBG_BF_ASSERT(0, "STRIP");} //STRIP001 ScAutoStyleList(ScDocShell* pShell);
//STRIP001          ~ScAutoStyleList();
//STRIP001
//STRIP001  void    AddInitial( const ScRange& rRange, const String& rStyle1,
//STRIP001                      ULONG nTimeout, const String& rStyle2 );
//STRIP001  void    AddEntry( ULONG nTimeout, const ScRange& rRange, const String& rStyle );
//STRIP001
//STRIP001  void    ExecuteAllNow();
};



} //namespace binfilter
#endif

