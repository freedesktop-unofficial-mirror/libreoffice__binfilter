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
TARGET=sw_utlui

NO_HIDS=TRUE

# --- Settings -----------------------------------------------------

.INCLUDE :  $(PRJ)$/inc$/bf_sw$/swpre.mk
.INCLUDE :  settings.mk
alllangiso=en-US
.INCLUDE :  $(PRJ)$/inc$/bf_sw$/sw.mk

INC+= -I$(PRJ)$/inc$/bf_sw

# --- Files --------------------------------------------------------

SRS1NAME=$(TARGET)
SRC1FILES =  \
        sw_initui.src \
        sw_gloslst.src \
        sw_navipi.src \
        sw_poolfmt.src \
        sw_attrdesc.src \
        sw_utlui.src

SLOFILES =  \
                $(SLO)$/sw_attrdesc.obj \
                $(SLO)$/sw_uiitems.obj \
                $(SLO)$/sw_uitool.obj \
                $(SLO)$/sw_initui.obj

# --- Tagets -------------------------------------------------------

.INCLUDE :  target.mk

