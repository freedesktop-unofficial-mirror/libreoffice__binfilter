/*************************************************************************
 *
 *  $RCSfile: viewopti.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 08:25:08 $
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

#ifndef SC_VIEWOPTI_HXX
#define SC_VIEWOPTI_HXX

#ifndef _SVX_OPTGRID_HXX //autogen
#include <bf_svx/optgrid.hxx>
#endif

#ifndef _SVX_SVXIDS_HRC //autogen
#include <bf_svx/svxids.hrc>
#endif

#ifndef SC_OPTUTIL_HXX
#include "optutil.hxx"
#endif

#ifndef SC_SCGLOB_HXX
#include "global.hxx"
#endif
namespace binfilter {

//==================================================================
// View-Optionen
//==================================================================

enum ScViewOption
{
    VOPT_FORMULAS = 0,
    VOPT_NULLVALS,
    VOPT_SYNTAX,
    VOPT_NOTES,
    VOPT_VSCROLL,
    VOPT_HSCROLL,
    VOPT_TABCONTROLS,
    VOPT_OUTLINER,
    VOPT_HEADER,
    VOPT_GRID,
    VOPT_HELPLINES,
    VOPT_ANCHOR,
    VOPT_PAGEBREAKS,
    VOPT_SOLIDHANDLES,
    VOPT_CLIPMARKS,
    VOPT_BIGHANDLES
};

enum ScVObjType
{
    VOBJ_TYPE_OLE = 0,
    VOBJ_TYPE_CHART,
    VOBJ_TYPE_DRAW
};

#define MAX_OPT             (USHORT)VOPT_BIGHANDLES+1
#define MAX_TYPE            (USHORT)VOBJ_TYPE_DRAW+1

#define SC_STD_GRIDCOLOR    COL_LIGHTGRAY

//==================================================================
// SvxGrid-Optionen mit Standard-Operatoren
//==================================================================

class ScGridOptions : public SvxOptionsGrid
{
public:
                ScGridOptions() : SvxOptionsGrid() {}
                ScGridOptions( const SvxOptionsGrid& rOpt ) : SvxOptionsGrid( rOpt ) {}

    void                    SetDefaults();
    const ScGridOptions&    operator=  ( const ScGridOptions& rCpy );
    int                     operator== ( const ScGridOptions& rOpt ) const;
    int                     operator!= ( const ScGridOptions& rOpt ) const { return !(operator==(rOpt)); }

    friend SvStream&        operator>> ( SvStream& rStream, ScGridOptions& rOpt );
    friend SvStream&        operator<< ( SvStream& rStream, const ScGridOptions& rOpt );
};

//==================================================================
// Einstellungen - Ansicht
//==================================================================

class ScViewOptions
{
public:
                ScViewOptions();
                ScViewOptions( const ScViewOptions& rCpy );
                ~ScViewOptions();

    void                    SetDefaults();

    void                    SetOption( ScViewOption eOpt, BOOL bNew = TRUE )    { aOptArr[eOpt] = bNew; }
    BOOL                    GetOption( ScViewOption eOpt ) const                { return aOptArr[eOpt]; }

    void                    SetObjMode( ScVObjType eObj, ScVObjMode eMode ) { aModeArr[eObj] = eMode; }
    ScVObjMode              GetObjMode( ScVObjType eObj ) const             { return aModeArr[eObj]; }

    void                    SetGridColor( const Color& rCol, const String& rName ) { aGridCol = rCol; aGridColName = rName;}
    Color                   GetGridColor( String* pStrName = NULL ) const;

    const ScGridOptions&    GetGridOptions() const                      { return aGridOpt; }
    void                    SetGridOptions( const ScGridOptions& rNew ) { aGridOpt = rNew; }
//STRIP001  SvxGridItem*            CreateGridItem( USHORT nId = SID_ATTR_GRID_OPTIONS ) const;

    BOOL                    IsHideAutoSpell() const             { return bHideAutoSpell; }
    void                    SetHideAutoSpell( BOOL bSet )       { bHideAutoSpell = bSet; }

    const ScViewOptions&    operator=  ( const ScViewOptions& rCpy );
    int                     operator== ( const ScViewOptions& rOpt ) const;
    int                     operator!= ( const ScViewOptions& rOpt ) const { return !(operator==(rOpt)); }

    friend SvStream&        operator>> ( SvStream& rStream, ScViewOptions& rOpt );

    void                    Save(SvStream& rStream, BOOL bConfig = FALSE) const;

private:
    BOOL            aOptArr     [MAX_OPT];
    ScVObjMode      aModeArr    [MAX_TYPE];
    Color           aGridCol;
    String          aGridColName;
    ScGridOptions   aGridOpt;
    BOOL            bHideAutoSpell;
};

inline SvStream& operator<<( SvStream& rStream, const ScViewOptions& rOpt )
{
    rOpt.Save( rStream, FALSE );
    return rStream;
}

//==================================================================
// Item fuer Einstellungsdialog - Ansicht
//==================================================================

//STRIP001 class ScTpViewItem : public SfxPoolItem
//STRIP001 {
//STRIP001 public:
//STRIP001              TYPEINFO();
//STRIP001              ScTpViewItem( USHORT nWhich );
//STRIP001              ScTpViewItem( USHORT nWhich, const ScViewOptions& rOpt );
//STRIP001              ScTpViewItem( const ScTpViewItem&  rItem );
//STRIP001              ~ScTpViewItem();
//STRIP001
//STRIP001  virtual String          GetValueText() const;
//STRIP001  virtual int             operator==( const SfxPoolItem& ) const;
//STRIP001  virtual SfxPoolItem*    Clone( SfxItemPool *pPool = 0 ) const;
//STRIP001
//STRIP001  const ScViewOptions&    GetViewOptions() const { return theOptions; }
//STRIP001
//STRIP001 private:
//STRIP001  ScViewOptions   theOptions;
//STRIP001 };


//==================================================================
// CfgItem fuer View-Optionen
//==================================================================

class ScViewCfg : public ScViewOptions
{
    ScLinkConfigItem    aLayoutItem;
    ScLinkConfigItem    aDisplayItem;
    ScLinkConfigItem    aGridItem;

    DECL_LINK( LayoutCommitHdl, void* );
    DECL_LINK( DisplayCommitHdl, void* );
    DECL_LINK( GridCommitHdl, void* );

    ::com::sun::star::uno::Sequence<rtl::OUString> GetLayoutPropertyNames();
    ::com::sun::star::uno::Sequence<rtl::OUString> GetDisplayPropertyNames();
    ::com::sun::star::uno::Sequence<rtl::OUString> GetGridPropertyNames();

public:
            ScViewCfg();

//STRIP001  void            SetOptions( const ScViewOptions& rNew );
};


} //namespace binfilter
#endif


