/*************************************************************************
 *
 *  $RCSfile: sch_typemap.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:32:51 $
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


#pragma hdrstop

#include <bf_svx/eeitem.hxx>

#include "eetext.hxx"
#ifndef _SVX_FONTITEM_HXX //autogen
#include <bf_svx/fontitem.hxx>
#endif
#ifndef _SVX_POSTITEM_HXX //autogen
#include <bf_svx/postitem.hxx>
#endif
#ifndef _SVX_WGHTITEM_HXX //autogen
#include <bf_svx/wghtitem.hxx>
#endif
#ifndef _SVX_SHDDITEM_HXX //autogen
#include <bf_svx/shdditem.hxx>
#endif
#ifndef _SVX_ITEM_HXX //autogen
#include <bf_svx/cntritem.hxx>
#endif
#ifndef _SVX_CRSDITEM_HXX //autogen
#include <bf_svx/crsditem.hxx>
#endif
#ifndef _SVX_UDLNITEM_HXX //autogen
#include <bf_svx/udlnitem.hxx>
#endif
#ifndef _SVX_FHGTITEM_HXX //autogen
#include <bf_svx/fhgtitem.hxx>
#endif
#ifndef _SVX_COLRITEM_HXX //autogen
#include <bf_svx/colritem.hxx>
#endif

#include <bf_svx/svxids.hrc>

#define ITEMID_FMTSPLIT     0
#define ITEMID_PAGEMODEL    0
#include <bf_svx/editdata.hxx>
#include "eetext.hxx"
#include "schattr.hxx"

#define ITEMID_LINE         0
#define ITEMID_BRUSH        0
#define ITEMID_FMTBREAK     0
#define ITEMID_FMTKEEP      0
#define ITEMID_SIZE         0
#include <bf_svx/sizeitem.hxx>

#define ITEMID_PAGE         0
#include <bf_svx/pageitem.hxx>

#include <bf_svx/rulritem.hxx>

#define ITEMID_AUTHOR       0
#define ITEMID_DATE         0
#define ITEMID_TEXT         0
#include <bf_svx/postattr.hxx>

#define ITEMID_SEARCH       0
#include <bf_svx/srchitem.hxx>

#define ITEMID_HORJUSTIFY   0
#define ITEMID_VERJUSTIFY   0
#define ITEMID_ORIENTATION  0
#include <bf_svx/algitem.hxx>

#include <bf_svx/zoomitem.hxx>

#define ITEMID_CHARTSTYLE   0
#ifndef _SVX_CHRTITEM_HXX //autogen
#include <bf_svx/chrtitem.hxx>
#endif
namespace binfilter {

/*?*/ typedef SfxVoidItem   CharSetItem;
/*?*/ typedef SfxVoidItem   FontFamilyItem;
/*?*/ typedef SfxVoidItem   FontPitchItem;
/*?*/ typedef SfxVoidItem   FontAlignItem;
/*?*/ typedef SfxVoidItem   FontWeightItem;
/*?*/ typedef SfxVoidItem   FontUnderlineItem;
/*?*/ typedef SfxVoidItem   FontStrikeoutItem;
/*?*/ typedef SfxVoidItem   FontItalicItem;
/*?*/ typedef SfxVoidItem   SvxDbTypeItem;
/*?*/ typedef SfxVoidItem SvxLineSpaceItem;
/*?*/ typedef SfxVoidItem   SvxInterLineSpaceItem;
/*?*/ typedef SfxVoidItem   SvxBreakItem;
/*?*/ typedef SfxVoidItem   BrushStyleItem;
/*?*/ typedef SfxVoidItem   SvxNumTypeItem;
/*?*/ typedef SfxVoidItem   SvxShadowLocationItem;
/*?*/ typedef SfxVoidItem   SvxChooseControlEnumItem;
/*?*/ typedef SfxVoidItem   SvxDrawToolEnumItem;
/*?*/ typedef SfxVoidItem   SvxChooseControlItem;
/*?*/ typedef SfxVoidItem   SvxDrawToolItem;
/*?*/ typedef SfxVoidItem   SvxCellHorJustifyEnumItem;
/*?*/ typedef SfxVoidItem   SvxCellVerJustifyEnumItem;
/*?*/ typedef SfxVoidItem   SvxCellOrientationEnumItem;
/*?*/ typedef SfxEnumItem   SvxStyleTypeItem;

#define SFX_TYPEMAP
#include "schslots.hxx"





}
