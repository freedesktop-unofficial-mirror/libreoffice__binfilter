#*************************************************************************
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.1 $
#
#   last change: $Author: aw $ $Date: 2003-12-05 09:37:48 $
#
#   The Contents of this file are made available subject to the terms of
#   either of the following licenses
#
#          - GNU Lesser General Public License Version 2.1
#          - Sun Industry Standards Source License Version 1.1
#
#   Sun Microsystems Inc., October, 2000
#
#   GNU Lesser General Public License Version 2.1
#   =============================================
#   Copyright 2000 by Sun Microsystems, Inc.
#   901 San Antonio Road, Palo Alto, CA 94303, USA
#
#   This library is free software; you can redistribute it and/or
#   modify it under the terms of the GNU Lesser General Public
#   License version 2.1, as published by the Free Software Foundation.
#
#   This library is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#   Lesser General Public License for more details.
#
#   You should have received a copy of the GNU Lesser General Public
#   License along with this library; if not, write to the Free Software
#   Foundation, Inc., 59 Temple Place, Suite 330, Boston,
#   MA  02111-1307  USA
#
#
#   Sun Industry Standards Source License Version 1.1
#   =================================================
#   The contents of this file are subject to the Sun Industry Standards
#   Source License Version 1.1 (the "License"); You may not use this file
#   except in compliance with the License. You may obtain a copy of the
#   License at http://www.openoffice.org/license.html.
#
#   Software provided under this License is provided on an "AS IS" basis,
#   WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING,
#   WITHOUT LIMITATION, WARRANTIES THAT THE SOFTWARE IS FREE OF DEFECTS,
#   MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE, OR NON-INFRINGING.
#   See the License for the specific provisions governing your rights and
#   obligations concerning the Software.
#
#   The Initial Developer of the Original Code is: Sun Microsystems, Inc.
#
#   Copyright: 2000 by Sun Microsystems, Inc.
#
#   All Rights Reserved.
#
#   Contributor(s): _______________________________________
#
#
#
#*************************************************************************

PRJ=..$/..$/..

PRJNAME=binfilter
TARGET=xmloff_text
AUTOSEG=true

ENABLE_EXCEPTIONS=TRUE

# --- Settings -----------------------------------------------------

.INCLUDE :  svpre.mk
.INCLUDE :  settings.mk
.INCLUDE :  sv.mk
CDEFS += -DCONV_STAR_FONTS

INC+= -I$(PRJ)$/inc$/bf_xmloff

# --- Files --------------------------------------------------------


SLOFILES =	\
        $(SLO)$/xmloff_txtdrope.obj \
        $(SLO)$/xmloff_txtdropi.obj \
        $(SLO)$/xmloff_txtexppr.obj \
        $(SLO)$/xmloff_txtflde.obj \
        $(SLO)$/xmloff_txtfldi.obj \
        $(SLO)$/xmloff_txtftne.obj \
        $(SLO)$/xmloff_txtimp.obj \
        $(SLO)$/xmloff_txtimppr.obj \
        $(SLO)$/xmloff_txtparae.obj \
        $(SLO)$/xmloff_txtparai.obj \
        $(SLO)$/xmloff_txtprhdl.obj \
        $(SLO)$/xmloff_txtprmap.obj \
        $(SLO)$/xmloff_txtsecte.obj \
        $(SLO)$/xmloff_txtstyle.obj \
        $(SLO)$/xmloff_txtstyli.obj \
        $(SLO)$/xmloff_txtvfldi.obj \
        $(SLO)$/xmloff_XMLAutoMarkFileContext.obj \
        $(SLO)$/xmloff_XMLAutoTextEventExport.obj \
        $(SLO)$/xmloff_XMLAutoTextEventImport.obj \
        $(SLO)$/xmloff_XMLAutoTextContainerEventImport.obj \
        $(SLO)$/xmloff_XMLChangedRegionImportContext.obj \
        $(SLO)$/xmloff_XMLChangeElementImportContext.obj \
        $(SLO)$/xmloff_XMLChangeInfoContext.obj \
        $(SLO)$/xmloff_XMLFootnoteBodyImportContext.obj \
        $(SLO)$/xmloff_XMLFootnoteConfigurationImportContext.obj \
        $(SLO)$/xmloff_XMLFootnoteImportContext.obj \
        $(SLO)$/xmloff_XMLIndexAlphabeticalSourceContext.obj \
        $(SLO)$/xmloff_XMLIndexBodyContext.obj \
        $(SLO)$/xmloff_XMLIndexBibliographyConfigurationContext.obj \
        $(SLO)$/xmloff_XMLIndexBibliographyEntryContext.obj \
        $(SLO)$/xmloff_XMLIndexBibliographySourceContext.obj \
        $(SLO)$/xmloff_XMLIndexChapterInfoEntryContext.obj \
        $(SLO)$/xmloff_XMLIndexIllustrationSourceContext.obj \
        $(SLO)$/xmloff_XMLIndexMarkExport.obj \
        $(SLO)$/xmloff_XMLIndexObjectSourceContext.obj \
        $(SLO)$/xmloff_XMLIndexSimpleEntryContext.obj \
        $(SLO)$/xmloff_XMLIndexSpanEntryContext.obj \
        $(SLO)$/xmloff_XMLIndexSourceBaseContext.obj \
        $(SLO)$/xmloff_XMLIndexTOCContext.obj \
        $(SLO)$/xmloff_XMLIndexTOCSourceContext.obj \
        $(SLO)$/xmloff_XMLIndexTOCStylesContext.obj \
        $(SLO)$/xmloff_XMLIndexTableSourceContext.obj \
        $(SLO)$/xmloff_XMLIndexTabStopEntryContext.obj \
        $(SLO)$/xmloff_XMLIndexTemplateContext.obj \
        $(SLO)$/xmloff_XMLIndexTitleTemplateContext.obj \
        $(SLO)$/xmloff_XMLIndexUserSourceContext.obj \
        $(SLO)$/xmloff_XMLLineNumberingExport.obj \
        $(SLO)$/xmloff_XMLLineNumberingImportContext.obj \
        $(SLO)$/xmloff_XMLLineNumberingSeparatorImportContext.obj \
        $(SLO)$/xmloff_XMLPropertyBackpatcher.obj \
        $(SLO)$/xmloff_XMLRedlineExport.obj \
        $(SLO)$/xmloff_XMLSectionExport.obj \
        $(SLO)$/xmloff_XMLSectionFootnoteConfigExport.obj \
        $(SLO)$/xmloff_XMLSectionFootnoteConfigImport.obj \
        $(SLO)$/xmloff_XMLSectionImportContext.obj \
        $(SLO)$/xmloff_XMLSectionSourceDDEImportContext.obj \
        $(SLO)$/xmloff_XMLSectionSourceImportContext.obj \
        $(SLO)$/xmloff_XMLTextCharStyleNamesElementExport.obj \
        $(SLO)$/xmloff_XMLTextColumnsContext.obj \
        $(SLO)$/xmloff_XMLTextColumnsExport.obj \
        $(SLO)$/xmloff_XMLTextFrameContext.obj \
        $(SLO)$/xmloff_XMLTextFrameHyperlinkContext.obj \
        $(SLO)$/xmloff_XMLTextHeaderFooterContext.obj \
        $(SLO)$/xmloff_XMLTextListAutoStylePool.obj \
        $(SLO)$/xmloff_XMLTextListBlockContext.obj \
        $(SLO)$/xmloff_XMLTextListItemContext.obj \
        $(SLO)$/xmloff_XMLTextMarkImportContext.obj \
        $(SLO)$/xmloff_XMLTextMasterPageContext.obj \
        $(SLO)$/xmloff_XMLTextMasterPageExport.obj \
        $(SLO)$/xmloff_XMLTextMasterStylesContext.obj \
        $(SLO)$/xmloff_XMLTextNumRuleInfo.obj \
        $(SLO)$/xmloff_XMLTextPropertySetContext.obj \
        $(SLO)$/xmloff_XMLTextShapeImportHelper.obj \
        $(SLO)$/xmloff_XMLTextShapeStyleContext.obj \
        $(SLO)$/xmloff_XMLTextTableContext.obj \
        $(SLO)$/xmloff_XMLChangeImportContext.obj \
        $(SLO)$/xmloff_XMLStringBufferImportContext.obj \
        $(SLO)$/xmloff_XMLTrackedChangesImportContext.obj \
        $(SLO)$/xmloff_XMLCalculationSettingsContext.obj

SVXLIGHTOBJFILES =	\
        $(OBJ)$/xmloff_txtdropi.obj \
        $(OBJ)$/xmloff_txtfldi.obj \
        $(OBJ)$/xmloff_txtimp.obj \
        $(OBJ)$/xmloff_txtimppr.obj \
        $(OBJ)$/xmloff_txtparai.obj \
        $(OBJ)$/xmloff_txtprhdl.obj \
        $(OBJ)$/xmloff_txtprmap.obj \
        $(OBJ)$/xmloff_txtstyli.obj \
        $(OBJ)$/xmloff_txtvfldi.obj \
        $(OBJ)$/xmloff_XMLAutoMarkFileContext.obj \
        $(OBJ)$/xmloff_XMLAutoTextEventImport.obj \
        $(OBJ)$/xmloff_XMLAutoTextContainerEventImport.obj \
        $(OBJ)$/xmloff_XMLChangedRegionImportContext.obj \
        $(OBJ)$/xmloff_XMLChangeElementImportContext.obj \
        $(OBJ)$/xmloff_XMLChangeInfoContext.obj \
        $(OBJ)$/xmloff_XMLLineNumberingExport.obj \
        $(OBJ)$/xmloff_XMLLineNumberingImportContext.obj \
        $(OBJ)$/xmloff_XMLLineNumberingSeparatorImportContext.obj \
        $(OBJ)$/xmloff_XMLPropertyBackpatcher.obj \
        $(SLO)$/xmloff_XMLTextCharStyleNamesElementExport.obj \
        $(OBJ)$/xmloff_XMLTextFrameContext.obj \
        $(OBJ)$/xmloff_XMLTextFrameHyperlinkContext.obj \
        $(OBJ)$/xmloff_XMLTextHeaderFooterContext.obj \
        $(OBJ)$/xmloff_XMLTextListAutoStylePool.obj \
        $(OBJ)$/xmloff_XMLTextListBlockContext.obj \
        $(OBJ)$/xmloff_XMLTextListItemContext.obj \
        $(OBJ)$/xmloff_XMLTextMarkImportContext.obj \
        $(OBJ)$/xmloff_XMLTextMasterPageContext.obj \
        $(OBJ)$/xmloff_XMLTextMasterPageExport.obj \
        $(OBJ)$/xmloff_XMLTextMasterStylesContext.obj \
        $(OBJ)$/xmloff_XMLTextNumRuleInfo.obj \
        $(OBJ)$/xmloff_XMLTextPropertySetContext.obj \
        $(OBJ)$/xmloff_XMLTextShapeImportHelper.obj \
        $(OBJ)$/xmloff_XMLTextShapeStyleContext.obj \
        $(OBJ)$/xmloff_XMLTextTableContext.obj \
        $(OBJ)$/xmloff_XMLChangeImportContext.obj \
        $(OBJ)$/xmloff_XMLStringBufferImportContext.obj

# --- Tagets -------------------------------------------------------

.INCLUDE :  target.mk
