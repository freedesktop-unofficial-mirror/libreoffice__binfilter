#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.3 $
#
#   last change: $Author: rt $ $Date: 2005-09-09 09:18:11 $
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

PRJ=..$/..$/..

PRJNAME=binfilter
TARGET=xmloff_script
AUTOSEG=true

ENABLE_EXCEPTIONS=TRUE

# --- Settings -----------------------------------------------------

.INCLUDE :  settings.mk
INC+= -I$(PRJ)$/inc$/bf_xmloff
# --- Files --------------------------------------------------------

SLOFILES =	\
        $(SLO)$/xmloff_XMLEventExport.obj \
        $(SLO)$/xmloff_XMLEventImportHelper.obj \
        $(SLO)$/xmloff_XMLEventsImportContext.obj \
        $(SLO)$/xmloff_XMLScriptContextFactory.obj \
        $(SLO)$/xmloff_XMLScriptExportHandler.obj \
        $(SLO)$/xmloff_XMLStarBasicContextFactory.obj \
        $(SLO)$/xmloff_XMLStarBasicExportHandler.obj \
        $(SLO)$/xmloff_xmlscripte.obj \
        $(SLO)$/xmloff_xmlscripti.obj \
        $(SLO)$/xmloff_xmlbasici.obj

SVXLIGHTOBJFILES =	\
        $(OBJ)$/xmloff_xmlscripti.obj \
        $(OBJ)$/xmloff_XMLEventImportHelper.obj \
        $(OBJ)$/xmloff_XMLEventsImportContext.obj


# --- Tagets -------------------------------------------------------

.INCLUDE :  target.mk

