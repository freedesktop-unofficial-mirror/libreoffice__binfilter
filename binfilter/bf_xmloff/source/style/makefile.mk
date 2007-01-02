#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.5 $
#
#   last change: $Author: hr $ $Date: 2007-01-02 18:17:57 $
#
#   The Contents of this file are made available subject to
#   the terms of GNU Lesser General Public License Version 2.1.
#
#
#     GNU Lesser General Public License Version 2.1
#     =============================================
#     Copyright 2005 by Sun Microsystems, Inc.
#     901 San Antonio Road, Palo Alto, CA 94303, USA
#
#     This library is free software; you can redistribute it and/or
#     modify it under the terms of the GNU Lesser General Public
#     License version 2.1, as published by the Free Software Foundation.
#
#     This library is distributed in the hope that it will be useful,
#     but WITHOUT ANY WARRANTY; without even the implied warranty of
#     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#     Lesser General Public License for more details.
#
#     You should have received a copy of the GNU Lesser General Public
#     License along with this library; if not, write to the Free Software
#     Foundation, Inc., 59 Temple Place, Suite 330, Boston,
#     MA  02111-1307  USA
#
#*************************************************************************

EXTERNAL_WARNINGS_NOT_ERRORS := TRUE

PRJ=..$/..$/..

PRJNAME=binfilter
TARGET=xmloff_style

ENABLE_EXCEPTIONS=TRUE

# --- Settings -----------------------------------------------------

.INCLUDE :  svpre.mk
.INCLUDE :  settings.mk
.INCLUDE :  sv.mk
CDEFS += -DCONV_STAR_FONTS
INC+= -I$(PRJ)$/inc$/bf_xmloff

# --- Files --------------------------------------------------------

CXXFILES = \
        xmloff_XMLPercentOrMeasurePropertyHandler.cxx \
        xmloff_XMLIsPercentagePropertyHandler.cxx \
        xmloff_XMLRectangleMembersHandler.cxx \
        xmloff_adjushdl.cxx	\
        xmloff_backhdl.cxx		\
        xmloff_bordrhdl.cxx	\
        xmloff_breakhdl.cxx	\
        xmloff_cdouthdl.cxx	\
        xmloff_chrhghdl.cxx	\
        xmloff_chrlohdl.cxx	\
        xmloff_csmaphdl.cxx	\
        xmloff_escphdl.cxx		\
        xmloff_fonthdl.cxx		\
        xmloff_impastp1.cxx    \
        xmloff_impastp2.cxx    \
        xmloff_impastp3.cxx    \
        xmloff_impastp4.cxx    \
        xmloff_kernihdl.cxx	\
        xmloff_lspachdl.cxx	\
        xmloff_numehelp.cxx	\
        xmloff_opaquhdl.cxx	\
        xmloff_postuhdl.cxx	\
        xmloff_prhdlfac.cxx	\
        xmloff_prstylei.cxx	\
        xmloff_shadwhdl.cxx	\
        xmloff_shdwdhdl.cxx	\
        xmloff_styleexp.cxx	\
        xmloff_splithdl.cxx	\
        xmloff_tabsthdl.cxx	\
        xmloff_undlihdl.cxx	\
        xmloff_uniref.cxx		\
        xmloff_weighhdl.cxx	\
        xmloff_xmlaustp.cxx	\
        xmloff_xmlbahdl.cxx	\
        xmloff_xmlexppr.cxx	\
        xmloff_xmlimppr.cxx	\
        xmloff_xmlnume.cxx		\
        xmloff_xmlnumfe.cxx	\
        xmloff_xmlnumfi.cxx	\
        xmloff_xmlnumi.cxx		\
        xmloff_xmlprcon.cxx	\
        xmloff_xmlprhdl.cxx	\
        xmloff_xmlprmap.cxx	\
        xmloff_xmlstyle.cxx	\
        xmloff_xmltabe.cxx		\
        xmloff_xmltabi.cxx		\
        xmloff_DashStyle.cxx					\
        xmloff_EnumPropertyHdl.cxx				\
        xmloff_FillStyleContext.cxx			\
        xmloff_GradientStyle.cxx				\
        xmloff_HatchStyle.cxx					\
        xmloff_ImageStyle.cxx					\
        xmloff_MarkerStyle.cxx					\
        xmloff_MultiPropertySetHelper.cxx		\
        xmloff_SinglePropertySetInfoCache.cxx	\
        xmloff_DashStyle.cxx					\
        xmloff_AttributeContainerHandler.cxx	\
        xmloff_NamedBoolPropertyHdl.cxx		\
        xmloff_TransGradientStyle.cxx			\
        xmloff_XMLBackgroundImageContext.cxx	\
        xmloff_XMLBackgroundImageExport.cxx	\
        xmloff_XMLClipPropertyHandler.cxx		\
        xmloff_XMLConstantsPropertyHandler.cxx	\
        xmloff_XMLElementPropertyContext.cxx	\
        xmloff_XMLFootnoteSeparatorExport.cxx	\
        xmloff_XMLFootnoteSeparatorImport.cxx	\
        xmloff_XMLFontAutoStylePool.cxx		\
        xmloff_XMLFontStylesContext.cxx		\
        xmloff_XMLPageExport.cxx				\
        xmloff_PageMasterPropHdl.cxx			\
        xmloff_PageMasterPropHdlFactory.cxx	\
        xmloff_PageMasterStyleMap.cxx			\
        xmloff_PageMasterPropMapper.cxx		\
        xmloff_PageMasterExportPropMapper.cxx	\
        xmloff_PageMasterImportPropMapper.cxx	\
        xmloff_PageMasterImportContext.cxx		\
        xmloff_PagePropertySetContext.cxx		\
        xmloff_PageHeaderFooterContext.cxx		\
        xmloff_XMLBitmapRepeatOffsetPropertyHandler.cxx \
        xmloff_XMLFillBitmapSizePropertyHandler.cxx \
        xmloff_XMLBitmapLogicalSizePropertyHandler.cxx \
        xmloff_durationhdl.cxx \
        xmloff_VisAreaContext.cxx \
        xmloff_DrawAspectHdl.cxx


SLOFILES =	\
        $(SLO)$/xmloff_XMLPercentOrMeasurePropertyHandler.obj \
        $(SLO)$/xmloff_XMLIsPercentagePropertyHandler.obj \
        $(SLO)$/xmloff_XMLRectangleMembersHandler.obj \
        $(SLO)$/xmloff_adjushdl.obj	\
        $(SLO)$/xmloff_backhdl.obj		\
        $(SLO)$/xmloff_bordrhdl.obj	\
        $(SLO)$/xmloff_breakhdl.obj	\
        $(SLO)$/xmloff_cdouthdl.obj	\
        $(SLO)$/xmloff_chrhghdl.obj	\
        $(SLO)$/xmloff_chrlohdl.obj	\
        $(SLO)$/xmloff_csmaphdl.obj	\
        $(SLO)$/xmloff_escphdl.obj		\
        $(SLO)$/xmloff_fonthdl.obj		\
        $(SLO)$/xmloff_impastp1.obj    \
        $(SLO)$/xmloff_impastp2.obj    \
        $(SLO)$/xmloff_impastp3.obj    \
        $(SLO)$/xmloff_impastp4.obj    \
        $(SLO)$/xmloff_kernihdl.obj	\
        $(SLO)$/xmloff_lspachdl.obj	\
        $(SLO)$/xmloff_numehelp.obj	\
        $(SLO)$/xmloff_opaquhdl.obj	\
        $(SLO)$/xmloff_postuhdl.obj	\
        $(SLO)$/xmloff_prhdlfac.obj	\
        $(SLO)$/xmloff_prstylei.obj	\
        $(SLO)$/xmloff_shadwhdl.obj	\
        $(SLO)$/xmloff_shdwdhdl.obj	\
        $(SLO)$/xmloff_styleexp.obj	\
        $(SLO)$/xmloff_splithdl.obj	\
        $(SLO)$/xmloff_tabsthdl.obj	\
        $(SLO)$/xmloff_undlihdl.obj	\
        $(SLO)$/xmloff_uniref.obj		\
        $(SLO)$/xmloff_weighhdl.obj	\
        $(SLO)$/xmloff_xmlaustp.obj	\
        $(SLO)$/xmloff_xmlbahdl.obj	\
        $(SLO)$/xmloff_xmlexppr.obj	\
        $(SLO)$/xmloff_xmlimppr.obj	\
        $(SLO)$/xmloff_xmlnume.obj		\
        $(SLO)$/xmloff_xmlnumfe.obj	\
        $(SLO)$/xmloff_xmlnumfi.obj	\
        $(SLO)$/xmloff_xmlnumi.obj		\
        $(SLO)$/xmloff_xmlprcon.obj	\
        $(SLO)$/xmloff_xmlprhdl.obj	\
        $(SLO)$/xmloff_xmlprmap.obj	\
        $(SLO)$/xmloff_xmlstyle.obj	\
        $(SLO)$/xmloff_xmltabe.obj		\
        $(SLO)$/xmloff_xmltabi.obj		\
        $(SLO)$/xmloff_DashStyle.obj					\
        $(SLO)$/xmloff_EnumPropertyHdl.obj				\
        $(SLO)$/xmloff_FillStyleContext.obj			\
        $(SLO)$/xmloff_GradientStyle.obj				\
        $(SLO)$/xmloff_HatchStyle.obj					\
        $(SLO)$/xmloff_ImageStyle.obj					\
        $(SLO)$/xmloff_MarkerStyle.obj					\
        $(SLO)$/xmloff_MultiPropertySetHelper.obj		\
        $(SLO)$/xmloff_SinglePropertySetInfoCache.obj	\
        $(SLO)$/xmloff_NamedBoolPropertyHdl.obj		\
        $(SLO)$/xmloff_TransGradientStyle.obj			\
        $(SLO)$/xmloff_XMLBackgroundImageContext.obj	\
        $(SLO)$/xmloff_XMLBackgroundImageExport.obj	\
        $(SLO)$/xmloff_XMLClipPropertyHandler.obj		\
        $(SLO)$/xmloff_XMLConstantsPropertyHandler.obj	\
        $(SLO)$/xmloff_AttributeContainerHandler.obj	\
        $(SLO)$/xmloff_XMLElementPropertyContext.obj	\
        $(SLO)$/xmloff_XMLFootnoteSeparatorExport.obj	\
        $(SLO)$/xmloff_XMLFootnoteSeparatorImport.obj	\
        $(SLO)$/xmloff_XMLFontAutoStylePool.obj		\
        $(SLO)$/xmloff_XMLFontStylesContext.obj		\
        $(SLO)$/xmloff_XMLPageExport.obj				\
        $(SLO)$/xmloff_PageMasterPropHdl.obj			\
        $(SLO)$/xmloff_PageMasterPropHdlFactory.obj	\
        $(SLO)$/xmloff_PageMasterStyleMap.obj			\
        $(SLO)$/xmloff_PageMasterPropMapper.obj		\
        $(SLO)$/xmloff_PageMasterExportPropMapper.obj	\
        $(SLO)$/xmloff_PageMasterImportPropMapper.obj	\
        $(SLO)$/xmloff_PageMasterImportContext.obj		\
        $(SLO)$/xmloff_PagePropertySetContext.obj		\
        $(SLO)$/xmloff_PageHeaderFooterContext.obj		\
        $(SLO)$/xmloff_XMLBitmapRepeatOffsetPropertyHandler.obj \
        $(SLO)$/xmloff_XMLFillBitmapSizePropertyHandler.obj	\
        $(SLO)$/xmloff_XMLBitmapLogicalSizePropertyHandler.obj	\
        $(SLO)$/xmloff_durationhdl.obj	\
        $(SLO)$/xmloff_VisAreaContext.obj \
        $(SLO)$/xmloff_DrawAspectHdl.obj

SVXLIGHTOBJFILES =	\
        $(OBJ)$/xmloff_XMLPercentOrMeasurePropertyHandler.obj \
        $(OBJ)$/xmloff_XMLIsPercentagePropertyHandler.obj \
        $(OBJ)$/xmloff_XMLRectangleMembersHandler.obj \
        $(OBJ)$/xmloff_adjushdl.obj	\
        $(OBJ)$/xmloff_backhdl.obj		\
        $(OBJ)$/xmloff_bordrhdl.obj	\
        $(OBJ)$/xmloff_breakhdl.obj	\
        $(OBJ)$/xmloff_cdouthdl.obj	\
        $(OBJ)$/xmloff_chrhghdl.obj	\
        $(OBJ)$/xmloff_chrlohdl.obj	\
        $(OBJ)$/xmloff_csmaphdl.obj	\
        $(OBJ)$/xmloff_escphdl.obj		\
        $(OBJ)$/xmloff_fonthdl.obj		\
        $(OBJ)$/xmloff_impastp1.obj    \
        $(OBJ)$/xmloff_impastp2.obj    \
        $(OBJ)$/xmloff_impastp3.obj    \
        $(OBJ)$/xmloff_impastp4.obj    \
        $(OBJ)$/xmloff_kernihdl.obj	\
        $(OBJ)$/xmloff_lspachdl.obj	\
        $(OBJ)$/xmloff_numehelp.obj	\
        $(OBJ)$/xmloff_opaquhdl.obj	\
        $(OBJ)$/xmloff_postuhdl.obj	\
        $(OBJ)$/xmloff_prhdlfac.obj	\
        $(OBJ)$/xmloff_prstylei.obj	\
        $(OBJ)$/xmloff_shadwhdl.obj	\
        $(OBJ)$/xmloff_shdwdhdl.obj	\
        $(OBJ)$/xmloff_splithdl.obj	\
        $(OBJ)$/xmloff_tabsthdl.obj	\
        $(OBJ)$/xmloff_undlihdl.obj	\
        $(OBJ)$/xmloff_uniref.obj		\
        $(OBJ)$/xmloff_weighhdl.obj	\
        $(OBJ)$/xmloff_xmlaustp.obj	\
        $(OBJ)$/xmloff_xmlbahdl.obj	\
        $(OBJ)$/xmloff_xmlimppr.obj	\
        $(OBJ)$/xmloff_xmlnumfi.obj	\
        $(OBJ)$/xmloff_xmlnumi.obj		\
        $(OBJ)$/xmloff_xmlprcon.obj	\
        $(OBJ)$/xmloff_xmlprhdl.obj	\
        $(OBJ)$/xmloff_xmlprmap.obj	\
        $(OBJ)$/xmloff_xmlstyle.obj	\
        $(OBJ)$/xmloff_xmltabi.obj		\
        $(OBJ)$/xmloff_DashStyle.obj					\
        $(OBJ)$/xmloff_EnumPropertyHdl.obj				\
        $(OBJ)$/xmloff_FillStyleContext.obj			\
        $(OBJ)$/xmloff_GradientStyle.obj				\
        $(OBJ)$/xmloff_HatchStyle.obj					\
        $(OBJ)$/xmloff_ImageStyle.obj					\
        $(OBJ)$/xmloff_MarkerStyle.obj					\
        $(OBJ)$/xmloff_MultiPropertySetHelper.obj		\
        $(SLO)$/xmloff_SinglePropertySetInfoCache.obj	\
        $(OBJ)$/xmloff_xmloff_NamedBoolPropertyHdl.obj		\
        $(OBJ)$/xmloff_xmloff_TransGradientStyle.obj			\
        $(OBJ)$/xmloff_XMLBackgroundImageContext.obj	\
        $(OBJ)$/xmloff_XMLClipPropertyHandler.obj		\
        $(OBJ)$/xmloff_XMLConstantsPropertyHandler.obj	\
        $(OBJ)$/xmloff_AttributeContainerHandler.obj	\
        $(OBJ)$/xmloff_XMLElementPropertyContext.obj	\
        $(OBJ)$/xmloff_XMLFontAutoStylePool.obj		\
        $(OBJ)$/xmloff_XMLFontStylesContext.obj		\
        $(OBJ)$/xmloff_PageMasterPropHdl.obj			\
        $(OBJ)$/xmloff_PageMasterPropHdlFactory.obj	\
        $(OBJ)$/xmloff_PageMasterStyleMap.obj			\
        $(OBJ)$/xmloff_PageMasterPropMapper.obj		\
        $(OBJ)$/xmloff_PageMasterImportPropMapper.obj	\
        $(OBJ)$/xmloff_PageMasterImportContext.obj		\
        $(OBJ)$/xmloff_PagePropertySetContext.obj		\
        $(OBJ)$/xmloff_PageHeaderFooterContext.obj		\
        $(OBJ)$/xmloff_XMLBitmapRepeatOffsetPropertyHandler.obj \
        $(OBJ)$/xmloff_XMLFillBitmapSizePropertyHandler.obj	\
        $(OBJ)$/xmloff_XMLBitmapLogicalSizePropertyHandler.obj	\
        $(OBJ)$/xmloff_durationhdl.obj	\
        $(OBJ)$/xmloff_VisAreaContext.obj \
        $(OBJ)$/xmloff_DrawAspectHdl.obj

# --- Tagets -------------------------------------------------------

.INCLUDE :  target.mk
