#*************************************************************************
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.1.1.1 $
#
#   last change: $Author: hjs $ $Date: 2003-10-01 12:17:37 $
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
PRJ=..$/..$/..$/..
BFPRJ=..$/..$/..

PRJNAME					= bf_sch
PROJECTPCH				= sch
PROJECTPCHSOURCE		= $(BFPRJ)$/util$/sch_sch
TARGET					= sch_chxchart
ENABLE_EXCEPTIONS		= TRUE
BOOTSTRAP_SERVICE		= FALSE

# --- Settings -----------------------------------------------------
.INCLUDE :  svpre.mk
.INCLUDE :  settings.mk
.INCLUDE :  sv.mk
INC+= -I$(PRJ)$/inc$/bf_sch

.IF "$(GUI)" == "WNT"
CFLAGS+=-Zm500
.ENDIF

# --- Files --------------------------------------------------------

CXXFILES = \
    sch_ChXChartAxis.cxx									\
    sch_ChXChartData.cxx									\
    sch_ChXChartDataChangeEventListener.cxx					\
    sch_ChXChartDocument.cxx								\
    sch_ChXChartObject.cxx									\
    sch_ChXChartView.cxx									\
    sch_ChXDataPoint.cxx									\
    sch_ChXDataRow.cxx										\
    sch_ChXDiagram.cxx										\
    sch_mapprov.cxx											\
    sch_ChXChartDrawPage.cxx								\
    sch_ChartLegend.cxx										\
    sch_ChartTitle.cxx										\
    sch_ChartLegend.cxx										\
    sch_ChartArea.cxx										\
    sch_ChartLine.cxx										\
    sch_ChartGrid.cxx										\
    sch_ViewPropertySet.cxx									\
    sch_register.cxx										\
    sch_unodoc.cxx

SLOFILES =  \
    $(SLO)$/sch_ChXChartAxis.obj							\
    $(SLO)$/sch_ChXChartData.obj							\
    $(SLO)$/sch_ChXChartDataChangeEventListener.obj			\
    $(SLO)$/sch_ChXChartDocument.obj						\
    $(SLO)$/sch_ChXChartObject.obj							\
    $(SLO)$/sch_ChXChartView.obj							\
    $(SLO)$/sch_ChXDataPoint.obj							\
    $(SLO)$/sch_ChXDataRow.obj								\
    $(SLO)$/sch_ChXDiagram.obj								\
    $(SLO)$/sch_mapprov.obj									\
    $(SLO)$/sch_ChXChartDrawPage.obj						\
    $(SLO)$/sch_ChartLegend.obj								\
    $(SLO)$/sch_ChartTitle.obj								\
    $(SLO)$/sch_ChartArea.obj								\
    $(SLO)$/sch_ChartLine.obj								\
    $(SLO)$/sch_ChartGrid.obj								\
    $(SLO)$/sch_ViewPropertySet.obj							\
    $(SLO)$/sch_register.obj								\
    $(SLO)$/sch_unodoc.obj

# --- Targets ------------------------------------------------------

.INCLUDE :  target.mk
