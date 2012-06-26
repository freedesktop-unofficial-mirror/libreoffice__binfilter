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
SUBPRJ=..$/..

PRJINC=$(SUBPRJ)

PRJNAME=binfilter
TARGET=so3_inplace

# --- Settings -----------------------------------------------------
.INCLUDE :  settings.mk
.INCLUDE :  $(SUBPRJ)$/util$/makefile.pmk

# --- Files --------------------------------------------------------

SLOFILES= \
    $(SLO)$/applet2.obj		\
    $(SLO)$/outplace.obj	\
    $(SLO)$/embobj.obj                           \
    $(SLO)$/client.obj                           \
    $(SLO)$/ipobj.obj                            \
    $(SLO)$/ipclient.obj                         \
    $(SLO)$/protocol.obj                         \
    $(SLO)$/soconv.obj		\
    $(SLO)$/ipenv.obj		\
    $(SLO)$/plugin.obj		


EXCEPTIONSFILES= \
    $(SLO)$/applet2.obj \
    $(SLO)$/plugin.obj


# --- Tagets -------------------------------------------------------


.INCLUDE :  target.mk
