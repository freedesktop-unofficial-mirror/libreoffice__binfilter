/*************************************************************************
 *
 *  $RCSfile: sxtraitm.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 08:29:16 $
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
#ifndef _SXTRAITM_HXX
#define _SXTRAITM_HXX

#ifndef _SVDDEF_HXX //autogen
#include <bf_svx/svddef.hxx>
#endif

#ifndef _SDMETITM_HXX
#include <bf_svx/sdmetitm.hxx>
#endif
namespace binfilter {

//------------------------------
// class SdrTransformRef1XItem
//------------------------------
class SdrTransformRef1XItem: public SdrMetricItem {
public:
    SdrTransformRef1XItem(long nHgt=0): SdrMetricItem(SDRATTR_TRANSFORMREF1X,nHgt)  {}
    SdrTransformRef1XItem(SvStream& rIn): SdrMetricItem(SDRATTR_TRANSFORMREF1X,rIn) {}
};

//------------------------------
// class SdrTransformRef1YItem
//------------------------------
class SdrTransformRef1YItem: public SdrMetricItem {
public:
    SdrTransformRef1YItem(long nHgt=0): SdrMetricItem(SDRATTR_TRANSFORMREF1Y,nHgt)  {}
    SdrTransformRef1YItem(SvStream& rIn): SdrMetricItem(SDRATTR_TRANSFORMREF1Y,rIn) {}
};

//------------------------------
// class SdrTransformRef2XItem
//------------------------------
class SdrTransformRef2XItem: public SdrMetricItem {
public:
    SdrTransformRef2XItem(long nHgt=0): SdrMetricItem(SDRATTR_TRANSFORMREF2X,nHgt)  {}
    SdrTransformRef2XItem(SvStream& rIn): SdrMetricItem(SDRATTR_TRANSFORMREF2X,rIn) {}
};

//------------------------------
// class SdrTransformRef2YItem
//------------------------------
class SdrTransformRef2YItem: public SdrMetricItem {
public:
    SdrTransformRef2YItem(long nHgt=0): SdrMetricItem(SDRATTR_TRANSFORMREF2Y,nHgt)  {}
    SdrTransformRef2YItem(SvStream& rIn): SdrMetricItem(SDRATTR_TRANSFORMREF2Y,rIn) {}
};

}//end of namespace binfilter
#endif
