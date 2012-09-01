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

PRJNAME=binfilter
TARGET=sd_app

NO_HIDS=TRUE

# --- Settings -----------------------------------------------------

.INCLUDE :  settings.mk
alllangiso=en-US
.INCLUDE :  $(BFPRJ)$/util$/makefile.pmk
INC+= -I$(PRJ)$/inc$/bf_sd

# --- Update-Version -----------------------------------------------

RSCUPDVER=$(RSCREVISION)SV$(UPD)$(UPDMINOR)

# --- Files --------------------------------------------------------

SRS1NAME=$(TARGET)
SRC1FILES =	\
        sd_strings.src

SLOFILES =	\
        $(SLO)$/sd_sdmod.obj		\
        $(SLO)$/sd_sddll.obj		\
        $(SLO)$/sd_sdresid.obj		\
        $(SLO)$/sd_optsitem.obj

DEPOBJFILES= \
        $(SLO)$/sd_sdlib.obj
        
.IF "$(GUI)" == "WNT"

NOOPTFILES=\
    $(SLO)$/sd_optsitem.obj

.ENDIF

# --- Tagets -------------------------------------------------------

.INCLUDE :  target.mk

$(INCCOM)$/sddll0.hxx: makefile.mk
    @echo $@
.IF "$(GUI)"=="UNX"
    echo \#define DLL_NAME \"libbf_sd$(DLLPOSTFIX)$(DLLPOST)\" >$@
.ELSE			# "$(GUI)"=="UNX"
    echo \#define DLL_NAME \"bf_sd$(DLLPOSTFIX).DLL\" >$@
.ENDIF			# "$(GUI)"=="UNX"


ALLTAR : $(DEPOBJFILES)

$(SRS)$/sd_app.srs: $(PRJ)$/inc$/bf_svx$/globlmn.hrc

$(SLO)$/sd_sdlib.obj: $(INCCOM)$/sddll0.hxx
