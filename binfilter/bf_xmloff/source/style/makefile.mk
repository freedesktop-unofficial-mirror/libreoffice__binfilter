#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.6 $
#
#   last change: $Author: obo $ $Date: 2007-01-25 12:04:55 $
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

.INCLUDE :  settings.mk
CDEFS += -DCONV_STAR_FONTS
INC+= -I$(PRJ)$/inc$/bf_xmloff

# --- Files --------------------------------------------------------

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

# --- Tagets -------------------------------------------------------

.INCLUDE :  target.mk
