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
TARGET=sw_app

NO_HIDS=TRUE


# --- Settings -----------------------------------------------------

.INCLUDE :  $(PRJ)$/inc$/bf_sw$/swpre.mk
.INCLUDE :  settings.mk
alllangiso=en-US
.INCLUDE :  $(PRJ)$/inc$/bf_sw$/sw.mk

INC+= -I$(PRJ)$/inc$/bf_sw
RSCUPDVER=$(RSCREVISION)(SV$(UPD)$(UPDMINOR))

# --- Files --------------------------------------------------------

SRS1NAME=$(TARGET)
SRC1FILES =\
        sw_app.src     \
        sw_error.src

SLOFILES = \
        $(SLO)$/sw_apphdl.obj   \
        $(SLO)$/sw_docsh.obj    \
        $(SLO)$/sw_docsh2.obj   \
        $(SLO)$/sw_docshdrw.obj \
        $(SLO)$/sw_docshini.obj \
        $(SLO)$/sw_docstyle.obj \
        $(SLO)$/sw_mainwn.obj   \
        $(SLO)$/sw_swmodule.obj \
        $(SLO)$/sw_swmodul1.obj \
        $(SLO)$/sw_swdll.obj


EXCEPTIONSFILES= \
        $(SLO)$/sw_swmodule.obj \
        $(SLO)$/sw_swmodul1.obj \
        $(SLO)$/sw_docsh2.obj


DEPOBJFILES= \
    $(SLO)$/sw_swlib.obj \
    $(SLO)$/sw_swcomlib.obj

# --- Targets ------------------------------------------------------

.INCLUDE :  target.mk

ALLTAR : $(DEPOBJFILES)

$(SLO)$/sw_swdll.obj : $(INCCOM)$/swdll0.hxx
$(SLO)$/sw_swlib.obj : $(INCCOM)$/swdll0.hxx
$(SLO)$/sw_swmodule.obj : $(INCCOM)$/swdll0.hxx

$(INCCOM)$/swdll0.hxx: makefile.mk
    echo \#define DLL_NAME \"$(DLLPRE)bf_sw$(DLLPOSTFIX)$(DLLPOST)\" >$@

$(SRS)$/sw_app.srs: $(PRJ)$/inc$/bf_svx$/globlmn.hrc

