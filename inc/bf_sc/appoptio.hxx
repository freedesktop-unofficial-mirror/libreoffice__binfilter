/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file incorporates work covered by the following license notice:
 *
 *   Licensed to the Apache Software Foundation (ASF) under one or more
 *   contributor license agreements. See the NOTICE file distributed
 *   with this work for additional information regarding copyright
 *   ownership. The ASF licenses this file to you under the Apache
 *   License, Version 2.0 (the "License"); you may not use this file
 *   except in compliance with the License. You may obtain a copy of
 *   the License at http://www.apache.org/licenses/LICENSE-2.0 .
 */

#ifndef SC_APPOPTIO_HXX
#define SC_APPOPTIO_HXX

#include <bf_svtools/bf_solar.h>



#include <vcl/field.hxx>

#include <bf_svx/zoomitem.hxx>

#include <unotools/configitem.hxx>

#include "global.hxx"

#include "optutil.hxx"
namespace binfilter {


class ScAppOptions
{
public:
                ScAppOptions();
                ScAppOptions( const ScAppOptions& rCpy );
                ~ScAppOptions();

    void        SetDefaults();

    void        SetAppMetric( FieldUnit eUnit ) { eMetric = eUnit;      }
    FieldUnit   GetAppMetric() const            { return eMetric;       }
    void        SetZoom( USHORT nNew )          { nZoom = nNew;         }
    USHORT      GetZoom() const                 { return nZoom;         }
    void        SetZoomType( SvxZoomType eNew ) { eZoomType = eNew;     }
    SvxZoomType GetZoomType() const             { return eZoomType;     }
    USHORT      GetLRUFuncListCount() const     { return nLRUFuncCount; }
    USHORT*     GetLRUFuncList() const          { return pLRUList;      }
    void        SetLRUFuncList( const USHORT* pList,
                                const USHORT  nCount );
    void        SetStatusFunc( USHORT nNew )    { nStatusFunc = nNew;   }
    USHORT      GetStatusFunc() const           { return nStatusFunc;   }
    void        SetAutoComplete( BOOL bNew )    { bAutoComplete = bNew; }
    BOOL        GetAutoComplete() const         { return bAutoComplete; }
    void        SetDetectiveAuto( BOOL bNew )   { bDetectiveAuto = bNew; }
    BOOL        GetDetectiveAuto() const        { return bDetectiveAuto; }

    void        SetTrackContentColor(sal_uInt32 nNew) { nTrackContentColor = nNew; }
    sal_uInt32  GetTrackContentColor() const     { return nTrackContentColor; }
    void        SetTrackInsertColor(sal_uInt32 nNew)     { nTrackInsertColor = nNew;  }
    sal_uInt32  GetTrackInsertColor() const      { return nTrackInsertColor;  }
    void        SetTrackDeleteColor(sal_uInt32 nNew)     { nTrackDeleteColor = nNew;  }
    sal_uInt32  GetTrackDeleteColor() const      { return nTrackDeleteColor;  }
    void        SetTrackMoveColor(sal_uInt32 nNew)   { nTrackMoveColor = nNew;    }
    sal_uInt32  GetTrackMoveColor() const        { return nTrackMoveColor;    }

    ScLkUpdMode GetLinkMode() const             { return eLinkMode ;}
    void        SetLinkMode( ScLkUpdMode nSet ) {   eLinkMode  = nSet;}

    void        SetDefaultObjectSizeWidth(INT32 nNew)   { nDefaultObjectSizeWidth = nNew; }
    INT32       GetDefaultObjectSizeWidth() const       { return nDefaultObjectSizeWidth; }
    void        SetDefaultObjectSizeHeight(INT32 nNew)  { nDefaultObjectSizeHeight = nNew; }
    INT32       GetDefaultObjectSizeHeight() const      { return nDefaultObjectSizeHeight; }


    const ScAppOptions& operator=   ( const ScAppOptions& rOpt );
/*N*/   friend SvStream&    operator>>  ( SvStream& rStream, ScAppOptions& rOpt );
/*N*/   friend SvStream&    operator<<  ( SvStream& rStream, const ScAppOptions& rOpt );

private:
    FieldUnit   eMetric;
    USHORT      nLRUFuncCount;
    USHORT*     pLRUList;
    SvxZoomType eZoomType;
    USHORT      nZoom;
    USHORT      nStatusFunc;
    BOOL        bAutoComplete;
    BOOL        bDetectiveAuto;
    sal_uInt32  nTrackContentColor;
    sal_uInt32  nTrackInsertColor;
    sal_uInt32  nTrackDeleteColor;
    sal_uInt32  nTrackMoveColor;
    ScLkUpdMode eLinkMode;
    INT32       nDefaultObjectSizeWidth;
    INT32       nDefaultObjectSizeHeight;
};


//==================================================================
//  Config Item containing app options
//==================================================================

class ScAppCfg : public ScAppOptions
{
    //  spread about 5 config paths
    //! split ScAppOptions into different classes

    ScLinkConfigItem    aLayoutItem;
    ScLinkConfigItem    aInputItem;
    ScLinkConfigItem    aRevisionItem;
    ScLinkConfigItem    aContentItem;
    ScLinkConfigItem    aSortListItem;
    ScLinkConfigItem    aMiscItem;

    DECL_LINK( LayoutCommitHdl, void* );
    DECL_LINK( InputCommitHdl, void* );
    DECL_LINK( RevisionCommitHdl, void* );
    DECL_LINK( ContentCommitHdl, void* );
    DECL_LINK( SortListCommitHdl, void* );
    DECL_LINK( MiscCommitHdl, void* );

    ::com::sun::star::uno::Sequence<rtl::OUString> GetLayoutPropertyNames();
    ::com::sun::star::uno::Sequence<rtl::OUString> GetInputPropertyNames();
    ::com::sun::star::uno::Sequence<rtl::OUString> GetRevisionPropertyNames();
    ::com::sun::star::uno::Sequence<rtl::OUString> GetContentPropertyNames();
    ::com::sun::star::uno::Sequence<rtl::OUString> GetSortListPropertyNames();
    ::com::sun::star::uno::Sequence<rtl::OUString> GetMiscPropertyNames();

public:
    ScAppCfg();
};


} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
