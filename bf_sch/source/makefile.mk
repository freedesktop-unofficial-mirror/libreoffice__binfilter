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

PRJ=..$/..
BFPRJ=..

PRJNAME=binfilter
TARGET=sch

NO_HIDS=TRUE

LIBTARGET=NO

# --- Settings -----------------------------------------------------

.INCLUDE :  settings.mk
INC+= -I$(PRJ)$/inc$/bf_sch
.IF "$(GUI)$(COM)" == "WINMSC"
LIBFLAGS+=/PAGE:128
.ENDIF


# --- Files --------------------------------------------------------

# --- ui Lib

LIB1TARGET= $(SLB)$/ui.lib
LIB1FILES= \
    $(SLB)$/app.lib \
    $(SLB)$/dlg.lib \
    $(SLB)$/docshell.lib \
    $(SLB)$/func.lib \
    $(SLB)$/view.lib \
    $(SLB)$/chxchart.lib 


# --- Targets -------------------------------------------------------

.INCLUDE :  target.mk
