/*************************************************************************
 *
 *  $RCSfile: svdfield.hxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:23:42 $
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

#ifndef _SVDFIELD_HXX
#define _SVDFIELD_HXX

#ifndef _FLDITEM_HXX
#ifndef ITEMID_FIELD
#ifndef _EDITDATA_HXX
#include <bf_svx/editdata.hxx>  /* das include wird wg. EE_FEATURE_FIELD benoetigt */
#endif
#define ITEMID_FIELD EE_FEATURE_FIELD  /* wird fuer #include <bf_svx/flditem.hxx> benoetigt */
#endif
#include <bf_svx/flditem.hxx>
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
// Do not remove this, it is still used in src536a!
void SdrRegisterFieldClasses();
////////////////////////////////////////////////////////////////////////////////////////////////////

#define SDR_MEASUREFIELD 50

class SdrMeasureObj;

enum SdrMeasureFieldKind {SDRMEASUREFIELD_VALUE,SDRMEASUREFIELD_UNIT,SDRMEASUREFIELD_ROTA90BLANCS};

class SdrMeasureField: public SvxFieldData {
    SdrMeasureFieldKind eMeasureFieldKind;
public:
    SV_DECL_PERSIST1(SdrMeasureField,SvxFieldData,SDR_MEASUREFIELD)
    SdrMeasureField(): eMeasureFieldKind(SDRMEASUREFIELD_VALUE) {}
    SdrMeasureField(SdrMeasureFieldKind eNewKind): eMeasureFieldKind(eNewKind) {}
    virtual ~SdrMeasureField();
    virtual SvxFieldData* Clone() const;
    virtual int operator==(const SvxFieldData&) const;
    SdrMeasureFieldKind GetMeasureFieldKind() const { return eMeasureFieldKind; }
    void SetMeasureFieldKind(SdrMeasureFieldKind eNewKind) { eMeasureFieldKind=eNewKind; }
    void TakeRepresentation(const SdrMeasureObj& rObj, XubString& rStr) const;
};

////////////////////////////////////////////////////////////////////////////////////////////////////

#endif //_SVDFIELD_HXX

