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
TARGET=svx_dialogs

NO_HIDS=TRUE

# --- Settings -----------------------------------------------------

.INCLUDE :  settings.mk
alllangiso=en-US
INC+= -I$(PRJ)$/inc$/bf_svx

.IF "$(GUI)" != "MAC"
CFLAGS+=-DDG_DLL
.ELSE
CFLAGS+=-D DG_DLL
.ENDIF

# --- Files --------------------------------------------------------

BMP_IN=$(BFPRJ)$/win/res

SRS1NAME=svx_dialogs
SRC1FILES =  \
        svx_impgrf.src \
        svx_lingu.src

SRS2NAME=svx_drawdlgs
SRC2FILES =  \
        svx_sdstring.src

SLOFILES=\
        $(SLO)$/svx_dlgutil.obj  \
        $(SLO)$/svx_impgrf.obj   

.IF "$(COM)" == "C50"
EXCEPTIONSNOOPTFILES=$(SLO)$/svx_impgrf.obj
.ELSE
EXCEPTIONSFILES+=$(SLO)$/svx_impgrf.obj
.ENDIF

# --- Targets -------------------------------------------------------

.INCLUDE :  target.mk

