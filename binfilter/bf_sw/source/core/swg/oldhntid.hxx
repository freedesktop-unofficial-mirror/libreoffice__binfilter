/*************************************************************************
 *
 *  $RCSfile: oldhntid.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:50:59 $
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


#ifndef _OLDHNTID_HXX
#define _OLDHNTID_HXX
namespace binfilter {
// ID-s fuer die Formate

enum OLDRES_FMT
{
OLDRES_FMT_BEGIN = 1,   // HIER GEHT'S LOS !!!
OLDRES_CHRFMT = OLDRES_FMT_BEGIN,
// Id fuer den Text ( fuer die Text-Attribute ), CheckWhich()
OLDRES_CHRTEXT,
OLDRES_PARFMT,
OLDRES_FRMFMT,
OLDRES_FLYFRMFMT,
OLDRES_GRFFMT,
OLDRES_FMT_END
};

// Bereiche fuer die Id's der einzelnen Format-Attribute
// die Which-Werte fuer die Charakter-Format Attribute
enum OLDRES_CHRATR
{
OLDRES_CHRATR_BEGIN = OLDRES_FMT_END,
OLDRES_CHRATR_CASEMAP = OLDRES_CHRATR_BEGIN,
OLDRES_CHRATR_CHARWIDTH,
OLDRES_CHRATR_COLOR,
OLDRES_CHRATR_CONTOUR,
OLDRES_CHRATR_CROSSEDOUT,
OLDRES_CHRATR_ESCAPEMENT,
OLDRES_CHRATR_FONT,
OLDRES_CHRATR_FONTSIZE,
OLDRES_CHRATR_INVERTED,
OLDRES_CHRATR_KERNING,
OLDRES_CHRATR_LANGUAGE,
OLDRES_CHRATR_MIRRORED,
OLDRES_CHRATR_POSTURE,
OLDRES_CHRATR_PROPORTIONALFONTSIZE,
OLDRES_CHRATR_SHADOWED,
OLDRES_CHRATR_UNDERLINE,
OLDRES_CHRATR_WEIGHT,
OLDRES_CHRATR_WRITINGDIRECTION,
OLDRES_CHRATR_FIELD,
OLDRES_CHRATR_NOLINEBREAK,
OLDRES_CHRATR_NOHYPHEN,
OLDRES_CHRATR_SOFTHYPH,
OLDRES_CHRATR_FTN,
OLDRES_CHRATR_HARDBLANK,
OLDRES_CHRATR_END
};

// die Which-Werte fuer die Charakter-Text Attribute
// (diese wirken sich direkt auf den Font aus !!)
enum OLDFONT_TXTATR
{
OLDRES_TXTATR_BEGIN = OLDRES_CHRATR_END,
OLDFONT_TXTATR_BEGIN = OLDRES_TXTATR_BEGIN,
OLDRES_TXTATR_CHARWIDTH = OLDFONT_TXTATR_BEGIN,
OLDRES_TXTATR_COLOR,
OLDRES_TXTATR_CONTOUR,
OLDRES_TXTATR_CROSSEDOUT,
OLDRES_TXTATR_FONT,
OLDRES_TXTATR_FONTSIZE,
OLDRES_TXTATR_INVERTED,
OLDRES_TXTATR_LANGUAGE,
OLDRES_TXTATR_MIRRORED,
OLDRES_TXTATR_POSTURE,
OLDRES_TXTATR_PROPORTIONALFONTSIZE,
OLDRES_TXTATR_SHADOWED,
OLDRES_TXTATR_UNDERLINE,
OLDRES_TXTATR_WEIGHT,
OLDRES_TXTATR_CHARFMT,
OLDFONT_TXTATR_END
};

// diese Text-Attribute wirken sich !nicht! auf den Font aus!
enum OLDETC_TXTATR
{
OLDETC_TXTATR_BEGIN = OLDFONT_TXTATR_END,
OLDRES_TXTATR_WRITINGDIRECTION = OLDETC_TXTATR_BEGIN,
OLDRES_TXTATR_KERNING,
OLDRES_TXTATR_NOLINEBREAK,
OLDRES_TXTATR_NOHYPHEN,
OLDRES_TXTATR_INSERTED,
OLDRES_TXTATR_DELETED,
OLDRES_TXTATR_ESCAPEMENT,
OLDRES_TXTATR_CASEMAP,
OLDRES_TXTATR_FIELD,
OLDRES_TXTATR_FLYCNT,
OLDRES_TXTATR_TOXMARK,
OLDRES_TXTATR_SOFTHYPH,
OLDRES_TXTATR_FTN,
OLDRES_TXTATR_HARDBLANK,
OLDRES_TXTATR_REFMARK,
OLDETC_TXTATR_END,
OLDRES_TXTATR_END = OLDETC_TXTATR_END
};

enum OLDRES_PARATR
{
OLDRES_PARATR_BEGIN = OLDRES_TXTATR_END,
OLDRES_PARATR_LINESPACING = OLDRES_PARATR_BEGIN,
OLDRES_PARATR_FIRSTLINEOFFSET,
OLDRES_PARATR_ADJUST,
OLDRES_PARATR_SPLIT,
OLDRES_PARATR_WIDOWS,
OLDRES_PARATR_ORPHANS,
OLDRES_PARATR_TABSTOP,
OLDRES_PARATR_HYPHENZONE,
OLDRES_PARATR_DROP,
OLDRES_PARATR_END
};


// Id's fuer die Text Additives
enum OLDRES_ADD
{
OLDRES_ADD_BEGIN = OLDRES_PARATR_END,
UNUSED_OLDRES_ADD_POSTIT = OLDRES_ADD_BEGIN,
OLDRES_ADD_INSERTS,
OLDRES_ADD_AUTOTEXT,
OLDRES_ADD_OTHERCONTENT,
OLDRES_ADD_END
};

enum OLDRES_FRMATR
{
OLDRES_FRMATR_BEGIN = OLDRES_ADD_END,
OLDRES_FILL_ORDER = OLDRES_FRMATR_BEGIN,
OLDRES_FRM_SIZE,
OLDRES_PAGE_BREAK,
OLDRES_SEL_PAGE,
OLDRES_PAPER_TRAY,
OLDRES_FRM_RNDREQUEST,
OLDRES_FRM_RNDSUPPLY,
OLDRES_LR_SPACE,
OLDRES_UL_SPACE,
OLDRES_CNTNT,
OLDRES_HEADER,
OLDRES_FOOTER,
OLDRES_FLY_PRINT,
OLDRES_FLY_OPAQUE,
OLDRES_FLY_PROTECT,
OLDRES_FLY_MAINCNTNT,
OLDRES_FLY_VERT_ORIENT,
OLDRES_FLY_HORI_ORIENT,
OLDRES_FLY_GENERIC,
OLDRES_FLY_ANCHOR,
OLDRES_BACKGROUND,
OLDRES_BOX,
OLDRES_SHADOW,
OLDRES_PAGEDESC,
OLDRES_FRMMACRO,
OLDRES_COL_BREAK,
OLDRES_COL,
OLDRES_FRMATR_END
};

enum OLDRES_GRFATR
{
OLDRES_GRFATR_BEGIN = OLDRES_FRMATR_END,
OLDRES_GRFATR_GRFSIZE = OLDRES_GRFATR_BEGIN,
OLDRES_GRFATR_MIRRORGRF,
OLDRES_GRFATR_GRFOFFSET,
OLDRES_GRFATR_ALIGNGRF,
OLDRES_GRFATR_CROPGRF,
OLDRES_GRFATR_END
};

} //namespace binfilter
#endif
