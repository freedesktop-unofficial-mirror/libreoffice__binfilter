/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: zoomitem.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 04:33:41 $
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
    virtual int             operator==( const SfxPoolItem& ) const;
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
