#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.5 $
#
#   last change: $Author: vg $ $Date: 2007-02-06 12:50:38 $
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

PRJ					= ..$/..$/..
PRJNAME				= binfilter
TARGET				= xmloff_chart
ENABLE_EXCEPTIONS	= TRUE

# --- Settings -----------------------------------------------------

.INCLUDE : settings.mk

INC+= -I$(PRJ)$/inc$/bf_xmloff

# --- Files --------------------------------------------------------

SLOFILES =	$(SLO)$/xmloff_SchXMLExport.obj \
            $(SLO)$/xmloff_SchXMLImport.obj \
            $(SLO)$/xmloff_contexts.obj \
            $(SLO)$/xmloff_SchXMLTableContext.obj \
            $(SLO)$/xmloff_SchXMLChartContext.obj \
            $(SLO)$/xmloff_SchXMLPlotAreaContext.obj \
            $(SLO)$/xmloff_SchXMLParagraphContext.obj \
            $(SLO)$/xmloff_PropertyMaps.obj \
            $(SLO)$/xmloff_XMLChartStyleContext.obj \
            $(SLO)$/xmloff_XMLErrorIndicatorPropertyHdl.obj \
            $(SLO)$/xmloff_SchXMLAutoStylePoolP.obj \
            $(SLO)$/xmloff_XMLChartPropertyContext.obj \
            $(SLO)$/xmloff_XMLSymbolImageContext.obj \
            $(SLO)$/xmloff_XMLTextOrientationHdl.obj

# --- Targets --------------------------------------------------------------

.INCLUDE : target.mk

