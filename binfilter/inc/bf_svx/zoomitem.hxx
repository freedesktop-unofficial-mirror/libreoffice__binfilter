/*************************************************************************
 *
 *  $RCSfile: zoomitem.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 08:29:50 $
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
#ifndef _SVX_ZOOMITEM_HXX
#define _SVX_ZOOMITEM_HXX

#ifndef _SFXINTITEM_HXX //autogen
#include <svtools/intitem.hxx>
#endif
#ifndef _SVX_SVXIDS_HRC
#include <bf_svx/svxids.hrc>
#endif
namespace binfilter {

//-------------------------------------------------------------------------

enum SvxZoomType
{
    SVX_ZOOM_PERCENT,       // GetValue() ist kein besonderer prozentualer Wert
    SVX_ZOOM_OPTIMAL,       // GetValue() entspricht der optimalen Gr"o\se
    SVX_ZOOM_WHOLEPAGE,     // GetValue() entspricht der ganzen Seite
    SVX_ZOOM_PAGEWIDTH,      // GetValue() entspricht der Seitenbreite
    SVX_ZOOM_PAGEWIDTH_NOBORDER  // GetValue() pagewidth without border
};

//-------------------------------------------------------------------------

class SvxZoomItem: public SfxUInt16Item
{
    USHORT                  nValueSet;  // erlaubte Werte (siehe #defines unten)
    SvxZoomType             eType;

public:
    TYPEINFO();

    SvxZoomItem( SvxZoomType eZoomType = SVX_ZOOM_PERCENT,
                 USHORT nVal = 0, USHORT nWhich = SID_ATTR_ZOOM );
    SvxZoomItem( const SvxZoomItem& );
    ~SvxZoomItem();

    void                    SetValueSet( USHORT nValues ) { nValueSet = nValues; }
    USHORT                  GetValueSet() const { return nValueSet; }
    FASTBOOL                IsValueAllowed( USHORT nValue ) const
                            { return nValue == ( nValue & nValueSet ); }

    SvxZoomType             GetType() const { return eType; }
    void                    SetType( SvxZoomType eNewType )
                            { eType = eNewType; }

    virtual SfxPoolItem*    Clone( SfxItemPool *pPool = 0 ) const;
//STRIP001  virtual SfxPoolItem*    Create( SvStream& rStrm, USHORT nVersion ) const;
//STRIP001  virtual SvStream&       Store( SvStream& rStrm , USHORT nItemVersion ) const;
    virtual int             operator==( const SfxPoolItem& ) const;
//STRIP001  virtual sal_Bool             QueryValue( ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 ) const;
//STRIP001  virtual sal_Bool             PutValue( const ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 );
};

//------------------------------------------------------------------------

#define SVX_ZOOM_ENABLE_50          0x0001
#define SVX_ZOOM_ENABLE_75          0x0002
#define SVX_ZOOM_ENABLE_100         0x0004
#define SVX_ZOOM_ENABLE_150         0x0008
#define SVX_ZOOM_ENABLE_200         0x0010
#define SVX_ZOOM_ENABLE_OPTIMAL     0x1000
#define SVX_ZOOM_ENABLE_WHOLEPAGE   0x2000
#define SVX_ZOOM_ENABLE_PAGEWIDTH   0x4000
#define SVX_ZOOM_ENABLE_ALL         0x701F

}//end of namespace binfilter
#endif
