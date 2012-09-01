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

PRJ=..$/..$/..
BFPRJ=..$/..

PRJNAME=binfilter
TARGET=sd_core

NO_HIDS=TRUE

# --- Settings -----------------------------------------------------

.INCLUDE :  settings.mk
alllangiso=en-US
.INCLUDE :  $(BFPRJ)$/util$/makefile.pmk
INC+= -I$(PRJ)$/inc$/bf_sd
IENV+=-I..\ui\inc

# --- Files --------------------------------------------------------


SRS1NAME=$(TARGET)
SRC1FILES = sd_glob.src

SLOFILES = $(SLO)$/sd_stlsheet.obj  \
           $(SLO)$/sd_stlpool.obj	\
           $(SLO)$/sd_drawdoc.obj \
           $(SLO)$/sd_drawdoc2.obj \
           $(SLO)$/sd_drawdoc3.obj \
           $(SLO)$/sd_drawdoc4.obj \
           $(SLO)$/sd_sdpage.obj \
           $(SLO)$/sd_sdattr.obj \
           $(SLO)$/sd_sdobjfac.obj \
           $(SLO)$/sd_anminfo.obj	\
           $(SLO)$/sd_sdiocmpt.obj	\
           $(SLO)$/sd_sdpage2.obj	\
           $(SLO)$/sd_cusshow.obj

EXCEPTIONSFILES= \
           $(SLO)$/sd_drawdoc.obj

# --- Tagets -------------------------------------------------------

.INCLUDE :  target.mk

