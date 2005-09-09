/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svdoutl.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 14:43:05 $
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

#ifndef _SVDOUTL_HXX
#define _SVDOUTL_HXX

#ifndef _OUTLINER_HXX //autogen
#include <bf_svx/outliner.hxx>
#endif
namespace binfilter {

class SdrTextObj;

class SdrOutliner : public Outliner
{
protected:
    const SdrTextObj* pTextObj;

public:
//    TYPEINFO();

    SdrOutliner( SfxItemPool* pItemPool, USHORT nMode );
    virtual ~SdrOutliner() ;

    void  SetTextObj( const SdrTextObj* pObj );
    void SetTextObjNoInit( const SdrTextObj* pObj );

    const SdrTextObj* GetTextObj() const { return pTextObj; }

    virtual String  CalcFieldValue(const SvxFieldItem& rField, USHORT nPara, USHORT nPos, Color*& rpTxtColor, Color*& rpFldColor);
};

}//end of namespace binfilter
#endif //_SVDOUTL_HXX

