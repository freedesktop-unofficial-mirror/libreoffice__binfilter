/*************************************************************************
 *
 *  $RCSfile: outlobj.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 08:28:22 $
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

#ifndef _OUTLOBJ_HXX
#define _OUTLOBJ_HXX

#ifndef _SOLAR_H
#include <tools/solar.h>
#endif

#ifndef _STRING_HXX
#include <tools/string.hxx>
#endif

#ifndef _RSCSFX_HXX
#include <rsc/rscsfx.hxx>
#endif

#ifndef _SFXITEMSET_HXX
#include <svtools/itemset.hxx>
#endif

#include <bf_svx/eeitem.hxx>
class SvStream;
class SfxItemPool;
class SfxStyleSheetPool;
namespace binfilter {

class Outliner;
class EditTextObject;

class OutlinerParaObject
{
    friend class Outliner;

    EditTextObject*             pText;
    USHORT*                     pDepthArr;
    ULONG                       nCount;
    BOOL                        bIsEditDoc;
                                OutlinerParaObject( USHORT nParaCount );

public:
                                OutlinerParaObject( const OutlinerParaObject& );
//STRIP001                              OutlinerParaObject( const EditTextObject& rTObj );
                                ~OutlinerParaObject();

    OutlinerParaObject*         Clone() const;

    USHORT                      GetOutlinerMode() const;
    void                        SetOutlinerMode( USHORT n );

    BOOL                        IsVertical() const;
    void                        SetVertical( BOOL bVertical );

    ULONG                       Count() const                   { return nCount; }
    USHORT                      GetDepth( USHORT nPara ) const  { return pDepthArr[nPara]; }
    const EditTextObject&       GetTextObject() const           { return *pText; }
    void                        ClearPortionInfo();
    BOOL                        IsEditDoc() const               { return bIsEditDoc; }
    void                        Store( SvStream& ) const;
    static OutlinerParaObject*  Create( SvStream&, SfxItemPool* pTextObjectPool = 0 );

    BOOL                        ChangeStyleSheets(  const XubString& rOldName, SfxStyleFamily eOldFamily,
                                                    const XubString& rNewName, SfxStyleFamily eNewFamily );
    void                        ChangeStyleSheetName( SfxStyleFamily eFamily, const XubString& rOldName, const XubString& rNewName );
    void                        SetStyleSheets( USHORT nLevel, const XubString rNewName, const SfxStyleFamily& rNewFamily );

//STRIP001  BOOL                        RemoveCharAttribs( USHORT nWhich = 0 );
//STRIP001  BOOL                        RemoveParaAttribs( USHORT nWhich = 0 );

//STRIP001  void                        SetLRSpaceItemFlags( BOOL bOutlineMode );
    void                        MergeParaAttribs( const SfxItemSet& rAttribs, USHORT nStart = EE_CHAR_START, USHORT nEnd = EE_CHAR_END );

    void                        PrepareStore( SfxStyleSheetPool* pStyleSheetPool );
    void                        FinishStore();
    void                        FinishLoad( SfxStyleSheetPool* pStyleSheetPool );
};

}//end of namespace binfilter
#endif
