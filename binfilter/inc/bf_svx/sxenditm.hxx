/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sxenditm.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 04:16:23 $
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
#ifndef _SXENDITM_HXX
#define _SXENDITM_HXX

#ifndef _SVDDEF_HXX //autogen
#include <bf_svx/svddef.hxx>
#endif

#ifndef _SDMETITM_HXX
#include <bf_svx/sdmetitm.hxx>
#endif
namespace binfilter {

class SdrEdgeNode1HorzDistItem: public SdrMetricItem {
public:
    SdrEdgeNode1HorzDistItem(long nVal=0): SdrMetricItem(SDRATTR_EDGENODE1HORZDIST,nVal)  {}
    SdrEdgeNode1HorzDistItem(SvStream& rIn): SdrMetricItem(SDRATTR_EDGENODE1HORZDIST,rIn) {}
};

class SdrEdgeNode1VertDistItem: public SdrMetricItem {
public:
    SdrEdgeNode1VertDistItem(long nVal=0): SdrMetricItem(SDRATTR_EDGENODE1VERTDIST,nVal)  {}
    SdrEdgeNode1VertDistItem(SvStream& rIn): SdrMetricItem(SDRATTR_EDGENODE1VERTDIST,rIn) {}
};

class SdrEdgeNode2HorzDistItem: public SdrMetricItem {
public:
    SdrEdgeNode2HorzDistItem(long nVal=0): SdrMetricItem(SDRATTR_EDGENODE2HORZDIST,nVal)  {}
    SdrEdgeNode2HorzDistItem(SvStream& rIn): SdrMetricItem(SDRATTR_EDGENODE2HORZDIST,rIn) {}
};

class SdrEdgeNode2VertDistItem: public SdrMetricItem {
public:
    SdrEdgeNode2VertDistItem(long nVal=0): SdrMetricItem(SDRATTR_EDGENODE2VERTDIST,nVal)  {}
    SdrEdgeNode2VertDistItem(SvStream& rIn): SdrMetricItem(SDRATTR_EDGENODE2VERTDIST,rIn) {}
};

class SdrEdgeNode1GlueDistItem: public SdrMetricItem {
public:
    SdrEdgeNode1GlueDistItem(long nVal=0): SdrMetricItem(SDRATTR_EDGENODE1GLUEDIST,nVal)  {}
    SdrEdgeNode1GlueDistItem(SvStream& rIn): SdrMetricItem(SDRATTR_EDGENODE1GLUEDIST,rIn) {}
};

class SdrEdgeNode2GlueDistItem: public SdrMetricItem {
public:
    SdrEdgeNode2GlueDistItem(long nVal=0): SdrMetricItem(SDRATTR_EDGENODE2GLUEDIST,nVal)  {}
    SdrEdgeNode2GlueDistItem(SvStream& rIn): SdrMetricItem(SDRATTR_EDGENODE2GLUEDIST,rIn) {}
};

}//end of namespace binfilter
#endif
