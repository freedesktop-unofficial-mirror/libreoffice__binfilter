/*************************************************************************
 *
 *  $RCSfile: starmath_command.cxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:19:17 $
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

#pragma hdrstop

#ifndef _TOOLS_RCID_H
#include <tools/rcid.h>
#endif

#ifndef MATH_COMMAND_HXX
#include "command.hxx"
#endif

SmCommandDesc::SmCommandDesc(const ResId& rResId) :
    Resource(rResId)
{
    if (IsAvailableRes(ResId(1).SetRT(RSC_STRING)))
        pSample = new String(ResId(1));
    else
        pSample = new String;

    if (IsAvailableRes(ResId(2).SetRT(RSC_STRING)))
        pCommand = new String(ResId(2));
    else
        pCommand = new String;

    if (IsAvailableRes(ResId(3).SetRT(RSC_STRING)))
        pText = new String(ResId(3));
    else
        pText = new String("sorry, no help available");

    if (IsAvailableRes(ResId(4).SetRT(RSC_STRING)))
        pHelp = new String(ResId(4));
    else
        pHelp = new String("sorry, no help available");

    if (IsAvailableRes(ResId(1).SetRT(RSC_BITMAP)))
        pGraphic =  new Bitmap(ResId(1));
    else
        pGraphic = new Bitmap();

    FreeResource();
}

SmCommandDesc::~SmCommandDesc()
{
    if (pText)      delete pText;
    if (pHelp)      delete pHelp;
    if (pSample)    delete pSample;
    if (pCommand)   delete pCommand;
    if (pGraphic)   delete pGraphic;
}


