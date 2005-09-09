/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: adjust.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 11:40:02 $
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

#ifndef _SCH_ADJUST_HXX
#define _SCH_ADJUST_HXX

/************************************************************************/
namespace binfilter {

enum ChartAdjust
{
    CHADJUST_TOP_LEFT,
    CHADJUST_TOP_RIGHT,
    CHADJUST_TOP_CENTER,
    CHADJUST_CENTER_LEFT,
    CHADJUST_CENTER_RIGHT,
    CHADJUST_CENTER_CENTER,
    CHADJUST_BOTTOM_LEFT,
    CHADJUST_BOTTOM_CENTER,
    CHADJUST_BOTTOM_RIGHT
};

#define CHADJUST_COUNT  CHADJUST_BOTTOM_RIGHT + 1

} //namespace binfilter
#endif

