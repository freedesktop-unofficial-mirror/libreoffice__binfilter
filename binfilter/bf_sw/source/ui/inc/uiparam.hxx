/*************************************************************************
 *
 *  $RCSfile: uiparam.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:55:47 $
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
#ifndef _UIPARAM_HXX
#define _UIPARAM_HXX

#ifndef _SVX_DIALOGS_HRC
#include <bf_svx/dialogs.hrc>
#endif
namespace binfilter {

/*--------------------------------------------------------------------
    Beschreibung:   Mapping fuer UI-Paramter
 --------------------------------------------------------------------*/

#define ITEMID_FONTLIST         SID_ATTR_CHAR_FONTLIST
#define ITEMID_TABPOS           SID_ATTR_TABSTOP_POS
#define ITEMID_DEFTABS          SID_ATTR_TABSTOP_DEFAULTS
#define ITEMID_TABOFFSET        SID_ATTR_TABSTOP_OFFSET
#define ITEMID_SEARCH           SID_SEARCH_ITEM
#define ITEMID_PARADLGLIMITS    SID_ATTR_PARA_DLGLIMITS
#define ITEMID_INFRAME          SID_ATTR_PARA_INFRAME

#define ITEMID_PAGEMODEL        SID_ATTR_PARA_MODEL
#define ITEMID_PAGE             SID_ATTR_PAGE
#define ITEMID_SIZE             SID_ATTR_PAGE_SIZE
#define ITEMID_SETITEM          SID_ATTR_PAGE_HEADERSET
#define ITEMID_PTR              SID_ATTR_PAGE_BSP
#define ITEMID_SPELLCHECK       SID_ATTR_SPELL
#define ITEMID_HYPHENREGION     SID_ATTR_HYPHENREGION
#define ITEMID_HYPHENZONE       RES_PARATR_HYPHENZONE
#define ITEMID_LINE             SID_ATTR_LINE_STYLE
#define ITEMID_BOXINFO          SID_ATTR_BORDER_INNER

#define ITEMID_AUTHOR           SID_ATTR_POSTIT_AUTHOR
#define ITEMID_DATE             SID_ATTR_POSTIT_DATE
#define ITEMID_TEXT             SID_ATTR_POSTIT_TEXT

#define ITEMID_NUMBERINFO       SID_ATTR_NUMBERFORMAT_INFO

} //namespace binfilter
#endif // _UIPARAM_HXX
