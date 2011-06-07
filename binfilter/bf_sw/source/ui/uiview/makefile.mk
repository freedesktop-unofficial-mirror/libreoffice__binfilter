#*************************************************************************
#
# DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
# 
# Copyright 2000, 2010 Oracle and/or its affiliates.
#
# OpenOffice.org - a multi-platform office productivity suite
#
# This file is part of OpenOffice.org.
#
# OpenOffice.org is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License version 3
# only, as published by the Free Software Foundation.
#
# OpenOffice.org is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License version 3 for more details
# (a copy is included in the LICENSE file that accompanied this code).
#
# You should have received a copy of the GNU Lesser General Public License
# version 3 along with OpenOffice.org.  If not, see
# <http://www.openoffice.org/license.html>
# for a copy of the LGPLv3 License.
#
#*************************************************************************

EXTERNAL_WARNINGS_NOT_ERRORS := TRUE

PRJ=..$/..$/..$/..
BFPRJ=..$/..$/..

PRJNAME=binfilter
TARGET=sw_uiview

NO_HIDS=TRUE

# --- Settings -----------------------------------------------------

.INCLUDE :  $(PRJ)$/inc$/bf_sw$/swpre.mk
.INCLUDE :  settings.mk
.INCLUDE :  $(PRJ)$/inc$/bf_sw$/sw.mk

INC+= -I$(PRJ)$/inc$/bf_sw
# --- Files --------------------------------------------------------

SRS1NAME=$(TARGET)
SRC1FILES =  \
        sw_view.src \
        sw_pview.src

SLOFILES =  \
        $(SLO)$/sw_view0.obj \
        $(SLO)$/sw_view.obj \
        $(SLO)$/sw_view1.obj \
        $(SLO)$/sw_view2.obj \
        $(SLO)$/sw_viewdraw.obj \
        $(SLO)$/sw_viewmdi.obj \
        $(SLO)$/sw_pview.obj \
        $(SLO)$/sw_viewport.obj \
        $(SLO)$/sw_viewstat.obj \
        $(SLO)$/sw_viewtab.obj \
        $(SLO)$/sw_viewprt.obj \
        $(SLO)$/sw_scroll.obj \
        $(SLO)$/sw_swcli.obj  \
        $(SLO)$/sw_srcview.obj \
        $(SLO)$/sw_uivwimp.obj

EXCEPTIONSFILES= \
        $(SLO)$/sw_srcview.obj \
        $(SLO)$/sw_uivwimp.obj

# --- Tagets -------------------------------------------------------

.INCLUDE :  target.mk

$(SRS)$/sw_uiview.srs: $(PRJ)$/inc$/bf_svx$/globlmn.hrc
