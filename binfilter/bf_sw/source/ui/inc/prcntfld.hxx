/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: prcntfld.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 05:48:13 $
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
#ifndef _PRCNTFLD_HXX
#define _PRCNTFLD_HXX

#ifndef _FIELD_HXX //autogen
#include <vcl/field.hxx>
#endif
namespace binfilter {

class PercentField : public MetricField
{
    long        nRefValue;      // 100%-Wert fuer Umrechnung (in Twips)
    long        nOldMax, nOldMin, nOldSpinSize, nOldBaseValue;
    long        nLastPercent, nLastValue;
    USHORT      nOldDigits;
    FieldUnit   eOldUnit;
    sal_Bool    bLockAutoCalculation; //prevent recalcution of percent values when the
                                        //reference value is changed

//STRIP001  long        ImpPower10(USHORT n);

//STRIP001    virtual void  SetValue(long nNewValue, FieldUnit eInUnit = FUNIT_NONE);
public:
     PercentField( Window* pWin, const ResId& rResId );

//STRIP001     void        SetPrcntValue(long nNewValue, FieldUnit eInUnit = FUNIT_NONE);
//STRIP001     void        SetUserValue(long nNewValue, FieldUnit eInUnit = FUNIT_NONE);
//STRIP001  void        SetBaseValue(long nNewValue, FieldUnit eInUnit = FUNIT_NONE);
//STRIP001  long        GetValue(FieldUnit eOutUnit = FUNIT_NONE);
//STRIP001  BOOL        IsValueModified();

//STRIP001  void        SetMax(long nNewMax, FieldUnit eInUnit = FUNIT_NONE);
//STRIP001  void        SetMin(long nNewMin, FieldUnit eInUnit = FUNIT_NONE);

//STRIP001  long        Normalize(long nValue);
//STRIP001  long        Denormalize(long nValue);

//STRIP001  void        SetRefValue(long nValue);
//STRIP001  inline long GetRefValue() const { return nRefValue; }
//STRIP001  long        GetRealValue(FieldUnit eOutUnit = FUNIT_NONE);

//STRIP001  long        Convert(long nValue, FieldUnit eInUnit, FieldUnit eOutUnit);

//STRIP001  void        ShowPercent(BOOL bPercent);

//STRIP001  USHORT      GetOldDigits() const {return nOldDigits;}

    void        LockAutoCalculation(sal_Bool bLock) {bLockAutoCalculation = bLock;}
    sal_Bool    IsAutoCalculationLocked()const {return bLockAutoCalculation;}
};

} //namespace binfilter
#endif // _PRCNTFLD_HXX

