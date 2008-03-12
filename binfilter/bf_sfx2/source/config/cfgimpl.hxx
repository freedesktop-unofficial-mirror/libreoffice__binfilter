/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: cfgimpl.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 08:03:30 $
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

// include ---------------------------------------------------------------

#include <tools/string.hxx>
#include <bf_svtools/svarray.hxx>

#include "cfgitem.hxx"
class SotStorage;
class SvStream;
namespace binfilter {

typedef SfxConfigItem* SfxConfigItemPtr;
SV_DECL_PTRARR( SfxConfigItems_Impl, SfxConfigItemPtr, 2, 2)//STRIP008 ;

struct SfxConfigItem_Impl
{
    SotStorageRef   xStorage;
    String          aName;              // old 5.0 format data
    String          aStreamName;
    SfxConfigItem*  pCItem;
    SfxConfigItems_Impl aItems;
    USHORT          nType;
    BOOL            bDefault;

                    SfxConfigItem_Impl( SfxConfigItem* pConf = NULL )
                        : pCItem( pConf )
                        , nType( pConf ? pConf->GetType() : 0 )
                        , bDefault( TRUE )
                    {}
};

typedef SfxConfigItem_Impl* SfxConfigItemPtr_Impl;
SV_DECL_PTRARR( SfxConfigItemArr_Impl, SfxConfigItemPtr_Impl, 2, 2)//STRIP008 ;

class SfxObjectShell;
class SfxIFConfig_Impl;
class SfxConfigManagerImExport_Impl
{
    SfxConfigItemArr_Impl*  pItemArr;
    SfxObjectShell*         pObjShell;
    SfxIFConfig_Impl*       pIFaceConfig;

    BOOL            ImportItem( SfxConfigItem_Impl* pItem, SvStream* pStream, SotStorage* pStor );
    BOOL            ExportItem( SfxConfigItem_Impl *pItem, SotStorage* pStor, SvStream* pStream );

public:
                    SfxConfigManagerImExport_Impl( SfxObjectShell* pDoc, SfxConfigItemArr_Impl* pArr )
                        : pItemArr( pArr )
                        , pObjShell( pDoc )
                        , pIFaceConfig( NULL )
                    {}

    USHORT          Import( SotStorage* pIn, SotStorage* pStor );
    USHORT          Export( SotStorage* pStor, SotStorage* pOut );

    static String   GetItemName( USHORT );
    static String   GetStreamName( USHORT nType );
    static USHORT   GetType( const String& rStreamName );
    static BOOL     HasConfiguration( SotStorage& rStorage );
};

}//end of namespace binfilter