#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.6 $
#
#   last change: $Author: rt $ $Date: 2006-07-25 09:08:05 $
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
TARGET=xmloff_core

ENABLE_EXCEPTIONS=TRUE

# --- Settings -----------------------------------------------------

.INCLUDE :  svpre.mk
.INCLUDE :  settings.mk
.INCLUDE :  sv.mk
CDEFS+=-DCONV_STAR_FONTS

INC+= -I$(PRJ)$/inc$/bf_xmloff

# --- to build xmlkywd.obj in obj, too -----------------------------

OBJFILES =  $(OBJ)$/xmloff_xmlkywd.obj
LIB2TARGET =$(LB)$/xmloff_xmlkywd.lib
LIB2OBJFILES  =$(OBJFILES)

# --- Files --------------------------------------------------------

SLOFILES =	\
        $(SLO)$/xmloff_facreg.obj		\
        $(SLO)$/xmloff_xmlcnitm.obj	\
        $(SLO)$/xmloff_attrlist.obj	\
        $(SLO)$/xmloff_i18nmap.obj		\
        $(SLO)$/xmloff_nmspmap.obj		\
        $(SLO)$/xmloff_unoatrcn.obj	\
        $(SLO)$/xmloff_xmlehelp.obj	\
        $(SLO)$/xmloff_xmlerror.obj	\
        $(SLO)$/xmloff_xmlexp.obj		\
        $(SLO)$/xmloff_xmlictxt.obj	\
        $(SLO)$/xmloff_xmlimp.obj		\
        $(SLO)$/xmloff_xmlkywd.obj		\
        $(SLO)$/xmloff_xmltkmap.obj	\
        $(SLO)$/xmloff_xmltoken.obj	\
        $(SLO)$/xmloff_xmluconv.obj	\
        $(SLO)$/xmloff_ProgressBarHelper.obj	\
        $(SLO)$/xmloff_PropertySetMerger.obj	\
        $(SLO)$/xmloff_SettingsExportHelper.obj	\
        $(SLO)$/xmloff_DocumentSettingsContext.obj \
        $(SLO)$/xmloff_XMLEmbeddedObjectExportFilter.obj \
        $(SLO)$/xmloff_XMLEmbeddedObjectImportContext.obj \
        $(SLO)$/xmloff_XMLBase64Export.obj \
        $(SLO)$/xmloff_XMLBase64ImportContext.obj \
        $(SLO)$/xmloff_XMLBasicExportFilter.obj

SVXLIGHTOBJFILES =	\
        $(OBJ)$/xmloff_facreg.obj		\
        $(OBJ)$/xmloff_xmlcnitm.obj	\
        $(OBJ)$/xmloff_attrlist.obj	\
        $(OBJ)$/xmloff_i18nmap.obj		\
        $(OBJ)$/xmloff_nmspmap.obj		\
        $(OBJ)$/xmloff_unoatrcn.obj	\
        $(OBJ)$/xmloff_xmlehelp.obj	\
        $(OBJ)$/xmloff_xmlerror.obj	\
        $(OBJ)$/xmloff_xmlictxt.obj	\
        $(OBJ)$/xmloff_xmlimp.obj		\
        $(OBJ)$/xmloff_xmlkywd.obj		\
        $(OBJ)$/xmloff_xmltkmap.obj	\
        $(OBJ)$/xmloff_xmltoken.obj	\
        $(OBJ)$/xmloff_xmluconv.obj	\
        $(OBJ)$/xmloff_ProgressBarHelper.obj	\
        $(OBJ)$/xmloff_PropertySetMerger.obj	\
        $(OBJ)$/xmloff_DocumentSettingsContext.obj \
        $(OBJ)$/xmloff_XMLEmbeddedObjectImportContext.obj \
        $(OBJ)$/xmloff_XMLBase64ImportContext.obj

CPPUMAKERFLAGS=

# --- Targets -------------------------------------------------------

.INCLUDE :  target.mk
