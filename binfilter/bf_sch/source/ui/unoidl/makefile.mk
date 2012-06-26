#
# This file is part of the LibreOffice project.
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.
#
# This file incorporates work covered by the following license notice:
#
#   Licensed to the Apache Software Foundation (ASF) under one or more
#   contributor license agreements. See the NOTICE file distributed
#   with this work for additional information regarding copyright
#   ownership. The ASF licenses this file to you under the Apache
#   License, Version 2.0 (the "License"); you may not use this file
#   except in compliance with the License. You may obtain a copy of
#   the License at http://www.apache.org/licenses/LICENSE-2.0 .
#

PRJ=..$/..$/..$/..
BFPRJ=..$/..$/..

PRJNAME					= binfilter
TARGET					= sch_chxchart
ENABLE_EXCEPTIONS		= TRUE
BOOTSTRAP_SERVICE		= FALSE

# --- Settings -----------------------------------------------------
.INCLUDE :  settings.mk
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
    sch_register.cxx										\
    sch_unodoc.cxx

SLOFILES =  \
    $(SLO)$/sch_ChXChartAxis.obj							\
    $(SLO)$/sch_ChXChartData.obj							\
    $(SLO)$/sch_ChXChartDataChangeEventListener.obj			\
    $(SLO)$/sch_ChXChartDocument.obj						\
    $(SLO)$/sch_ChXChartObject.obj							\
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
    $(SLO)$/sch_register.obj								\
    $(SLO)$/sch_unodoc.obj

# --- Targets ------------------------------------------------------

.INCLUDE :  target.mk
